# from arduino
import datetime
import mraa
import time

postureIn = mraa.Gpio(27)
sessionIn = mraa.Gpio(29)

postureIn.dir(mraa.DIR_IN)
sessionIn.dir(mraa.DIR_IN)

totalCount = 0
badCount = 0
#while sessionIn.read():
while True:
    if not postureIn.read():
        badCount += 1
    totalCount += 1

    print(postureIn.read())
    time.sleep(1)

