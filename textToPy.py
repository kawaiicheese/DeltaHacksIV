# get file
inFile = open("", "r")

## assuming first line is time
num = inFile.readline() 
date = inFile
session = {
    "x":    [],
    "y":    [],
    "z":    [],
    "gx":   [],
    "gy":   [],
    "gz":   []
}


for i in range(num):
    ## assuming 8 lines
    #    date
    #    time
    #    percent good posture
    nextline = inFile.readline().split("\t")

    (session[key].append(nextline[i]) for i, key in enumerate(session.keys))



##Plot Graph with time() and goodPositions()
