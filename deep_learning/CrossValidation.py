from sklearn.model_selection import KFold
import numpy as np
from keras.callbacks import EarlyStopping, ModelCheckpoint
from sklearn.metrics import accuracy_score
import time
from keras.metrics import BinaryAccuracy
from Metrics import Metrics
from datetime import datetime


class CrossValidation:
    def __init__(self, x, y, relative_time, avaliable_dataset_indices, sensors, file_create_time, epoch, batch_size, num_fold=10, set_weight=False):
        #self.kfold = StratifiedKFold(n_splits=num_fold)
        self.kfold = KFold(n_splits=num_fold, shuffle=False)
        self.x = x
        self.y = y
        self.relative_time = relative_time
        self.avaliable_dataset_indices = avaliable_dataset_indices
        self.es = EarlyStopping(
            monitor="loss", patience=400, verbose=1, mode="min", restore_best_weights=True)
        self.checkpoint_cb = ModelCheckpoint('best-model_' + str(datetime.fromtimestamp(time.time())) + ".h5",
                                             monitor="loss", save_best_only=True)
        self.sensors = sensors
        self.metrics = Metrics()
        self.threshold = 0.5
        self.file_create_time = file_create_time
        self.epoch = epoch
        self.batch_size = batch_size
        self.set_weight = set_weight
        self.class_weight = None

    def set_class_weight(self):
        neg = len(self.y[self.y == 0])
        pos = len(self.y[self.y == 1])
        total = neg + pos

        weight_0 = 0.5  # (1 / neg) * (total / 2.0)
        weight_1 = 0.5  # (1 / pos) * (total / 2.0)

        self.class_weight = {0: weight_0, 1: weight_1}

    def run(self, model):
        accuracy, conf_mat, alarming_time, execution_time = [], [], [], []
        accuracy_train, conf_mat_train, alarming_time_train, time_train = [], [], [], []
        cnt = 0

        model.save_weights('initial_weights.h5')
        weight_file = 'initial_weights.h5'
        # weight_file = 'best-model2022-04-20 15:50:18.979670_sensor4-38.h5'
        if(self.set_weight):
            self.set_class_weight()
        for train_indices, test_indices in self.kfold.split(self.avaliable_dataset_indices):
            cnt += 1
            global_train_ind = train_indices
            global_test_ind = test_indices

            # TRAIN
            print("start time:", datetime.fromtimestamp(time.time()))
            model.load_weights(weight_file)
            model.compile(optimizer='adam', loss='mse',
                          metrics=[BinaryAccuracy()])

            model, train_time = self.train(
                model, global_train_ind)
            self.threshold = self.select_threshold(model, global_train_ind)

            accuracy_cv, conf_mat_cv, alarming_time_cv, execution_time_cv = self.test(
                model, global_train_ind)
            accuracy_train.append(accuracy_cv)
            conf_mat_train.append(conf_mat_cv)
            alarming_time_train.append(alarming_time_cv)
            time_train.append(train_time)

            # TEST
            accuracy_cv, conf_mat_cv, alarming_time_cv, execution_time_cv = self.test(
                model, global_test_ind)
            accuracy.append(accuracy_cv)
            conf_mat.append(conf_mat_cv)
            alarming_time.append(alarming_time_cv)
            execution_time.append(execution_time_cv)

            print("end time:", datetime.fromtimestamp(time.time()))

            print_text = 'CV: ' + str(cnt) + ' Train Accuracy: ' + str(np.mean(accuracy_train[-1])) + ' Mean Accuracy: ' + str(np.mean(accuracy_cv)) + ' False Positive: ' + str(
                np.mean(conf_mat_cv[0, 1])) + ' False Negative: ' + str(np.mean(conf_mat_cv[1, 0])) + ' Mean Alarm Time: ' + str(np.mean(alarming_time_cv)) + ' \n'
            print(print_text)

            folder = '../Result/'
            with open(folder + "result_" + str(datetime.fromtimestamp(self.file_create_time)) + ".txt", "a+") as f:
                f.write(print_text)

        return [accuracy_train, conf_mat_train, alarming_time_train, time_train], [accuracy, conf_mat, alarming_time, execution_time]

    def get_input_output(self, indices):
        inputs = []
        outputs = self.y[indices, :]
        times = self.relative_time[indices, :]
        for j in self.sensors:
            inputs.append(self.x[j][indices, :, :])

        return inputs, outputs, times

    def train(self, model, train_indices):
        x_train, y_train, _ = self.get_input_output(train_indices)

        start_train_time = time.time()

        model.fit(x_train, y_train, epochs=self.epoch, batch_size=self.batch_size,
                  verbose=0, callbacks=[self.es, self.checkpoint_cb], class_weight=self.class_weight)

        train_time = time.time() - start_train_time
        return model, train_time

    def convert_to_binary(self, p):
        p[p >= self.threshold] = 1
        p[p < self.threshold] = 0
        return p

    def select_threshold(self, model, test_indices):
        x, d, relative_time = self.get_input_output(test_indices)
        y = model.predict(x)
        unit = 20

        acc = []
        threshold_vals = np.array(range(unit)) / unit
        for threshold in threshold_vals:
            self.threshold = threshold
            y_pred = np.copy(y)
            y_binary = self.convert_to_binary(y_pred)
            acc.append(accuracy_score(y_binary, d))
        best_threshold = threshold_vals[np.argmax(np.array(acc))]
        return best_threshold

    def test(self, model, test_indices):
        x_test, y_test, relative_time = self.get_input_output(test_indices)

        start_exacution_time = time.time()
        prediction = model.predict(x_test)
        execution_time = time.time()-start_exacution_time

        prediction = self.convert_to_binary(prediction)

        alarming_time = self.metrics.calc_alarming_time(
            y_test, prediction, relative_time)
        accuracy, conf_mat = self.metrics.calc_conf_mat(y_test, prediction)

        return accuracy, conf_mat, alarming_time, execution_time
