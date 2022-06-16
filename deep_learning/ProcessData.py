import numpy as np
import pandas as pd
import os
import scipy.io as spio
import math
from random import sample
from datetime import datetime


class ProcessData:
    def __init__(self, data_set_directory, columns_to_use, file_create_time):
        self.directory = data_set_directory
        self.selected_columns = columns_to_use
        self.datasets = []
        self.all_common_sensors = []
        self.file_create_time = file_create_time

    # x = current data, just before data
    # y = fire_label
    # time = current time
    def process_data(self, df):
        x = []
        for i in range(1, len(self.selected_columns)+1):
            x.append(np.array([np.array(df.iloc[1:, i:i + 1]),
                     np.array(df.iloc[:-1, i:i + 1])])[:, :, 0].T[:, :, np.newaxis])

        y = np.array(df.iloc[1:, -1:])
        time = np.array(df.iloc[1:, 0:1])
        return [x, y, time]

    # make datasets
    # [data file num][3:data, target, time][sensor num][data file's sample num][2:current data, just before data]
    def read_data(self, considered_files):
        for file in considered_files:
            if file.endswith(".csv"):
                print(file, end=" ")
                df = pd.read_csv(self.directory+'/'+file)
                columns = ["'TIME  '"] + self.selected_columns
                df = df[columns]
                df['fire_label'] = (df.iloc[:, 0] > 10)*1
                data = self.process_data(df)
                self.datasets.append(data)
                with open("../Result/result_" + str(datetime.fromtimestamp(self.file_create_time)) + ".txt", "a+") as f:
                    f.write(file+'\n')

    # Merge data sets divided into files into one
    def shape_to_input_output(self, sensors):
        x = []

        for j in sensors:
            count = 0
            for i in range(len(self.datasets)):
                if count == 0:
                    x.append(self.datasets[i][0][j])
                    y = self.datasets[i][1]
                    time = self.datasets[i][2]
                else:
                    x[-1] = np.concatenate((x[-1],
                                           self.datasets[i][0][j]), axis=0)
                    y = np.concatenate((y, self.datasets[i][1]), axis=0)
                    time = np.concatenate((time, self.datasets[i][2]), axis=0)
                count += 1
            x[-1] = x[-1]/np.max(x[-1])
        # '''
        rand_samples = sample(range(y.shape[0]), y.shape[0])
        spio.savemat('rand_indices_ex.mat', {'indices': rand_samples})
        # '''
        # To load the previously saved random indices
        # rand_samples = spio.loadmat('rand_indices.mat')
        # rand_samples = list(rand_samples['indices'][0])

        y = y[rand_samples, :]
        time = time[rand_samples, :]
        for j in sensors:
            x[j] = x[j][rand_samples, :, :]

        return x, y, time
