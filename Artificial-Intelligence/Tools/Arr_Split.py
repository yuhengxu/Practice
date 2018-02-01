import os
import os.path
import numpy as np


#把文本内容转换成二维数组
'''
#这种方法只能分割成字符串型的数组
fileHandle = open('test.feature')
lines = fileHandle.readlines()
feature_ary = []
for line in lines:
    temp = line.replace('\n', '').split(',')    #replace是替换函数，把字符串结尾的\ｎ去掉。split是分片函数，用于对指定位置的分割
    del(temp[0])    #删除变量
    del(temp[2])
    feature_ary.append(temp)    #在结尾添加元素
'''
#采用numpy函数库，可以方便快捷的实现分割转化
fileHandle = open('test.feature', 'r')
list_arr = fileHandle.readlines()
l = len(list_arr)
for i in range(l):
    list_arr[i] = list_arr[i].strip()
    list_arr[i] = list_arr[i].strip('[]')
    list_arr[i] = list_arr[i].replace('?', '0')
    list_arr[i] = list_arr[i].split(',')

a = np.array(list_arr)
a = a.astype(float)
print(a)
