import pymysql
import requests
from rTPNN import rTPNN
import numpy as np
from CrossValidation import CrossValidation
import time
import os

predictor_arch = [10, 5, 2]
# ["'TCB_1 '", "'GASB_3'", "'GASB_5'"], [temparature, co2, oxy]
num_sensors = 3
threshold = 0.2
DATABASE_IP = DATABASE_IP
DATABASE_PORT = DATABASE_PORT
USERNAME = USERNAME
PASSWD = PASSWD
DATABASE_NAME = DATABASE_NAME
ALERT_API = ALERT_API
TEMP_MAX = 400
CO2_MAX = 5
OXY_MAX = 25
SYNC_TIME = 2

User = []
Status = []


def connection():  # connect to the database
    conn = pymysql.connect(host=DATABASE_IP, port=DATABASE_PORT, user=USERNAME,
                           passwd=PASSWD, db=DATABASE_NAME, charset='utf8')
    cursor = conn.cursor()
    return conn, cursor


def loadModel():  # load RTPNN model's architecture and weights
    r_tpnn = rTPNN(num_sensors, predictor_arch, activation_name='relu')
    r_tpnn.model.load_weights('model_architecture.h5')
    return r_tpnn.model


def predictFireStatus(model, data):  # predict fire status
    prediction = model.predict(data)
    print("predict:", prediction[0][0], end="")
    prediction[prediction >= threshold] = 1
    prediction[prediction < threshold] = 0
    print(" result:", prediction[0][0])

    return prediction


def showTable(cursor):  # show all tables in the database
    cursor.execute("SHOW TABLES")
    tables = cursor.fetchall()
    for table in tables:
        print(table)


def selectSensor(cursor):  # show all columns in the Sensor table
    cursor.execute("SELECT * FROM sensor")
    sensors = cursor.fetchall()
    for sensor in sensors:
        print(sensor)


def showSensorColumns(cursor):  # show all column name in the Sensor table
    cursor.execute("SHOW COLUMNS FROM sensor")
    sensors = cursor.fetchall()
    for sensor in sensors:
        print(sensor)


def makeUser(cursor):
    cursor.execute("SELECT device_id FROM sensor GROUP BY device_id")
    global User, Status
    User = list(cursor.fetchall())
    Status = [0 for i in range(len(User))]


def getData(cursor):  # get co2, oxy, temp data from the Sensor table
    cursor.execute(
        "SELECT device_id, temp, co2, oxy FROM sensor WHERE measure_time BETWEEN DATE_ADD(NOW(), INTERVAL -12 SECOND ) AND NOW() ORDER BY measure_time DESC, device_id ASC")
    sensors = cursor.fetchall()

    rv = [np.array([[[0.], [0.]]]), np.array(
        [[[0.], [0.]]]), np.array([[[0.], [0.]]])]

    cnt = 0
    MAX_VALUE = [TEMP_MAX, CO2_MAX, OXY_MAX]

    print("----------------------------------------")
    for i in range(0, len(sensors), 2):
        cnt = 0
        for a, b in zip(sensors[i], sensors[i+1]):
            rv[cnt][i % 2][0] = a/MAX_VALUE[cnt]
            rv[cnt][i % 2][1] = b/MAX_VALUE[cnt]
            cnt += 1

    return rv


def updateFireStatus(predict):  # update fire status
    onFire = []

    for i in range(len(predict)):
        if predict[i] == 0:
            Status[i] = 0
        else:
            Status[i] += predict[i]
            if Status[i] >= 4:
                onFire.append(User[i])
                Status[i] = 0

    sendFireStatus(onFire)


def sendFireStatus(onFire):  # send FireStatusJson to the server
    data = {
        "fire": onFire
    }

    response = requests.post(
        ALERT_API, data=data)
    print(response)


if __name__ == '__main__':
    conn, cursor = connection()
    makeUser(cursor)
    model = loadModel()

    cnt = 0
    fire_cnt = 0

    while True:
        conn, cursor = connection()
        data = getData(cursor)
        rv = predictFireStatus(model, data)
        updateFireStatus(rv)
        time.sleep(5)
