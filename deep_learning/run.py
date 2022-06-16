from rTPNN import rTPNN
from ProcessData import ProcessData
from CrossValidation import CrossValidation
import math
import time
import numpy as np
from datetime import datetime

FILE_CREATE_TIME = time.time()
EPOCHS = 4000
BATCH_SIZE = 64
predictor_arch = [10, 5, 2]
sensors_considered = ["'TCB_1 '", "'GASB_3'", "'GASB_5'"]
NIST_data_file = '../Dataset/rtpnn'
files = ["sdc40.csv"]  # "sdc38.csv",


# Read and shape data
print('\n ============ DATASET ============')

num_sensors = len(sensors_considered)
sensors_considered_int = np.array(range(num_sensors))

data_processor = ProcessData(
    NIST_data_file, sensors_considered, FILE_CREATE_TIME)

data_processor.read_data(
    considered_files=files)

datasets = data_processor.datasets
x, y, relative_time = data_processor.shape_to_input_output(
    sensors_considered_int)
all_indices = range(y.shape[0])

print(type(x), type(x[0]), type(x[0][0]), type(x[0][0][0]))
print(type(datasets), type(datasets[0]), type(
    datasets[0][0]), type(datasets[0][0][0]))
print(len(datasets), len(datasets[0]), len(
    datasets[0][0]), len(datasets[0][0][0]))

r_tpnn = rTPNN(num_sensors, predictor_arch, activation_name='relu')
r_tpnn.model.load_weights('model_architecture.h5')

CV_rtpnn = CrossValidation(x, y, relative_time, all_indices,
                           sensors_considered_int, file_create_time=FILE_CREATE_TIME,
                           epoch=EPOCHS, batch_size=BATCH_SIZE, set_weight=False)
CV_rtpnn.threshold = 0.2

x_test, y_test, relative_time = CV_rtpnn.get_input_output(
    all_indices)

prediction = r_tpnn.model.predict(x_test)
print(prediction)
