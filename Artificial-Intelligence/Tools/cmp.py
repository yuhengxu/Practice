import os
import os.path
import numpy as np
from numpy import *

def createI(fileHandle):
    
    #将feature中的字符串转换成二维数组
    list_arr = fileHandle.readlines()
    l = len(list_arr)
    for i in range(l):
        list_arr[i] = list_arr[i].strip()
        list_arr[i] = list_arr[i].strip('[]')
        
    #字符串数组转换为浮点型数组
    labels = np.array(list_arr)
    labels = labels.astype(int)
    fileHandle.close()

    return labels
    

if __name__=="__main__":

    fileHandleR = open('./combR/result.label')
    fileHandleT = open('./combT/test.label')

    result = createI(fileHandleR)    
    test = createI(fileHandleT)

    fileHandleR.close()
    fileHandleT.close()

    num = 0
    l = len(test)
    for i in range(l):
        if test[i] == result[i]:
            num += 1

    print(num / l)