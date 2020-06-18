#!/usr/bin/env python3
import sys
import helper

class simpleTable(helper.generator):
    newline = '\r\n'
    fileName= 'simpleTable.csv'


    def generate(openFile):
        def makeRow(a,b):
            return (str(a) + ',' + str(b) + ',' + str(a*b))
        upperLimit = 100
        openFile.write('a,b,times')
        for i in range(upperLimit + 1):
            for j in range(i,upperLimit + 1):
                openFile.write('\n') # This is put HERE to avoid trailing newlines
                openFile.write(makeRow(i,j))

if (__name__ == "__main__"):
    helper.generateFile(simpleTable)
