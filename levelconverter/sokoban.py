# This script converts sokoban text files into arrays that are readable 
# by the sokoban gba game. Levels can be found at http://sneezingtiger.com/sokoban/levels.html
# Download the text file version of the level and run 'python sokoban.py path_to_file_here.txt'

import sys

f = open(sys.argv[1],'r')
maxX = 0
maxY = 0
for line in f:
    maxY+=1
    if (len(line) > maxX):
        maxX = len(line)
indentX = (15-maxX)/2
indentY = (10-maxY)/2
start = [0,0]
rocks = []

x = 0
y = 0
for i in range(indentY):
    for j in range(15):
        print "0,",
    print ""
    y+=1

f = open(sys.argv[1],'r')
for line in f:
    for i in range(indentX):
        x+=1
        print "0,",
    for char in line:
        if (char == ' '):
            print "1,",
        elif (char == '.'):
            print "2,",
        elif (char == '#'):
            print "3,",
        elif (char == '@'):
            start[0] = x
            start[1] = y
            print "1,",
        elif (char == '$'):
            temp = [x,y]
            rocks += [temp]
            print "1,",
        else:
            print "0,",
        x+=1
    for i in range(15-x):
        print "0,",
    print ""
    y+=1
    x=0
for i in range(10-y):
    for j in range(15):
        print "0,",
    print ""
print start, rocks
