# from arduino
import datetime
import mraa
import time

postureIn = mraa.Gpio(25)
sessionIn = mraa.Gpio(34)
breakSense = mraa.Gpio(31)


postureIn.dir(mraa.DIR_IN)
sessionIn.dir(mraa.DIR_IN)
breakSense.dir(mraa.DIR_IN)

while True:
    totalCount = 0
    badCount = 0.0
    
    print(sessionIn.read())
    print(postureIn.read())
    
    while sessionIn.read():
        if postureIn.read():
            badCount += 1
        totalCount += 1
    
        print(badCount/totalCount)
        #print(badCount)
        
        if breakSense.read():
            break
        
        time.sleep(1)
    
    if totalCount > 0:
        import emailBot
        emailBot.send("your posture is "+str(badCount/totalCount)+"% bad posture", "deltahackskawaiicheese@gmail.com", ["limb1@mcmaster.ca"])
    else:
        print("didnt run")
        time.sleep(1)
    
