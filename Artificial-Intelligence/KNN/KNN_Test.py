import os
import os.path
import operator
from numpy import *
import numpy as np

def createFeature():
    #函数作用，从A.feature中提取一部分作为训练集test.feature
    with open('A.feature') as reader, open('test.feature', 'w') as writer:
        for index, line in enumerate(reader):
            if index % 10 == 0:
                writer.write(line)

def createLabel():
    #同时给出这样本的标签test.label    
    with open('A.label') as reader, open('test.label', 'w') as writer:
        for index, line in enumerate(reader):
            if index % 10 == 0:
                writer.write(line)

def createDataSet():
    #函数作用，将test样本和标签转变成数组   
    createFeature()
    createLabel()

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
    dataset = np.array(list_arr)
    dataset = dataset.astype(float)
    fileHandle.close()

    fileHandle = open('test.label', 'r')
    list_arr = fileHandle.readlines()
    l = len(list_arr)
    for i in range(l):
        list_arr[i] = list_arr[i].strip()
        list_arr[i] = list_arr[i].strip('[]')
        
    #字符串数组转换为浮点型数组
    labels = np.array(list_arr)
    labels = labels.astype(int)
    fileHandle.close()

    print(dataset)
    print(labels)

    return dataset, labels

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

    #把分类的结果进行排序， 然后返回得票数最多的分类结果
    sortedClassCount = sorted(classCount.items(), key = operator.itemgetter(1), reverse = True)

    return sortedClassCount[0][0]

if __name__=="__main__":
    #导入数据
    dataset, labels = createDataSet()
    #测试数据
    #inX = [8.39,0,30,2.18837,8.5656,3.66179,2.39494,8.55081,3.64207,-0.0244132,0.0477585,0.00647434,14.8991,-69.2224,-5.82311,31.8125,0.31953,9.61282,-1.49328,0.234939,9.78539,-1.42846,0.013685,0.00148646,-0.0415218,1.0169,-50.3966,43.1768,30.3125,9.6937,-1.57902,-0.215687,9.6167,-1.6163,0.280488,-0.00657665,-0.00463778,0.00036825,-59.8479,-38.8919,-58.5253]
    #inX = [44.48,102,30.4375,-2.83932,8.4244,4.6646,-2.92798,8.63586,5.0517,-0.210817,-0.02033,0.0218961,3.98513,-68.3479,0.792113,32.25,-1.56251,9.35197,-1.99118,-1.87707,9.3079,-1.94604,0.00937732,0.0123717,-0.0168636,-5.13862,-49.9859,45.1678,30.8125,9.92185,-1.31531,-0.137805,9.76746,-1.26826,0.384515,-0.0220445,0.0171173,0.00683347,-58.8116,-40.8053,-58.4304]
    inX = [554.23,0,32.6875,2.70484,8.86134,3.24517,2.96828,8.87868,3.38406,0.0189218,-0.013613,-0.0325428,-19.5159,-38.2417,-59.6033,34.3125,0.498594,9.73127,-0.599835,0.376263,9.81392,-0.462024,-0.00740253,0.0101419,-0.0280513,19.1671,-59.9837,-25.4495,33.0625,9.87207,-0.512912,-0.722139,9.87054,-0.361431,-0.178953,0.00555381,0.00434606,-0.0286619,-85.0662,38.8589,-5.25512]
    #简单分类
    className = classify0(inX, dataset, labels, 5)

    print('The class of test sample is %s' %className)