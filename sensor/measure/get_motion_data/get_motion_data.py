import RPi.GPIO as gpio
import time
from datetime import datetime

MOTION_DATA_FILE_PATH = "/home/pi/smartnotice/src/sensor/measure/get_motion_data/motion_data.txt"
NO_GPIO = 5
time_cnt = 0
cnt = 0

if __name__ == '__main__':
    # set up GPIO
    gpio.setmode(gpio.BCM)
    NO_GPIO = 5
    gpio.setmode(gpio.BCM)
    gpio.setup(NO_GPIO, gpio.IN)
    file = open(MOTION_DATA_FILE_PATH, "w+")

    while 1:
        if time_cnt % 50 == 0:
            file.seek(0)
            file.write(str(cnt) + "\n")
            
        if time_cnt == 250:
            time_cnt = 0
            cnt = 0

        try:            # count number of times motion detected
            if not gpio.input(NO_GPIO):
                cnt += 1    
                
        except:
            print("get motion data Error")
            gpio.cleanup()
            file.close()
        
        time.sleep(0.02)
        time_cnt += 1
        
    gpio.cleanup()
    file.close()