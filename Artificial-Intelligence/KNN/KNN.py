import os
import os.path
import operator
from numpy import *
import numpy as np
import datetime

def createDataSet():
    
    #采用numpy函数库，可以方便快捷的实现分割转化
    fileHandle = open('./combF/1.feature', 'r')
    list_arr = fileHandle.readlines()
    l = len(list_arr)
    for i in range(l):
        list_arr[i] = list_arr[i].strip()           #strip(rm)：删除list_arr[i]字符串中开头、结尾处，rm字符。
        list_arr[i] = list_arr[i].strip('[]')
        list_arr[i] = list_arr[i].replace('?', '0') #replace是替换函数，把字符串结尾的\ｎ去掉。
        list_arr[i] = list_arr[i].split(',')        #split是分片函数，用于对指定位置的分割

    #字符串数组转换为浮点型数组
    dataset = np.array(list_arr)
    dataset = dataset.astype(float)
    fileHandle.close()


    fileHandle = open('./combL/1.label', 'r')
    list_arr = fileHandle.readlines()
    l = len(list_arr)
    for i in range(l):
        list_arr[i] = list_arr[i].strip()
        list_arr[i] = list_arr[i].strip('[]')
        
    #字符串数组转换为浮点型数组
    labels = np.array(list_arr)
    labels = labels.astype(int)
    fileHandle.close()


    #采用numpy函数库，可以方便快捷的实现分割转化
    fileHandle = open('test.feature', 'r')
    list_arr = fileHandle.readlines()
    l = len(list_arr)
    for i in range(l):
        list_arr[i] = list_arr[i].strip()           #strip(rm)：删除list_arr[i]字符串中开头、结尾处，rm字符。
        list_arr[i] = list_arr[i].strip('[]')
        list_arr[i] = list_arr[i].replace('?', '0') #replace是替换函数，把字符串结尾的\ｎ去掉。
        list_arr[i] = list_arr[i].split(',')        #split是分片函数，用于对指定位置的分割

    #字符串数组转换为浮点型数组
    inX = np.array(list_arr)
    inX = inX.astype(float)
    fileHandle.close()

    #print(dataset)
    #print(labels)
    #print(inX)

    return dataset, labels, inX


def classify0(inX, dataset, labels, k):
    #inX 是输入的测试样本，型如[x, y]
    #dataset 是训练样本集
    #labels 是训练样本标签
    #k 是top k最邻近

    #获取样本数，即行数
    dataSetSize = dataset.shape[0]

    #按照欧式距离计算公式计算，根号(x^2+y^2)
    diffMat = tile(inX, (dataSetSize, 1)) - dataset
    sqDiffMat = diffMat ** 2
    sqDistance = sqDiffMat.sum(axis = 1)
    distance = sqDistance ** 0.5

    #按照升序排序
    sortedDistIndicies = distance.argsort()

    #存放最终分类的结果及相应的投票数
    classCount = {}

    #投票的过程就是统计前K个最近样本所属类别包含的样本个数
    for i in range(k):
        #index = sortedDistIndicies[i]是第i个最邻近的样本下标
        #voteIlabel = labels[index]是样本index对应的分类结果('A' or 'B')
        voteIlabel = labels[sortedDistIndicies[i]]
        #classCount.get(voteIlabel, 0)返回voteIlabel的值，如果不存在， 则返回0
        #然后将票数增加1
        classCount[voteIlabel] = classCount.get(voteIlabel, 0) + 1

    print(classCount)
    #把分类的结果进行排序， 然后返回得票数最多的分类结果
    sortedClassCount = sorted(classCount.items(), key = operator.itemgetter(1), reverse = True)

    return sortedClassCount[0][0]

if __name__=="__main__":
    
    #计算程序运行时间
    starttime = datetime.datetime.now()
    
    #导入数据
    dataset, labels, inX = createDataSet()

    #简单分类 inX label 0 1 17 4 24
    inXSetSize = inX.shape[0]
    
    #循环比对
    for i in range(inXSetSize):
        className = classify0(inX[i], dataset, labels, 15)
        #print('The class of test sample is %s' %className)

    #输出程序运行时间
    endtime = datetime.datetime.now()
    print(endtime - starttime)