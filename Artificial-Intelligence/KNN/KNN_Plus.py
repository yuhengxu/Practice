import os
import os.path
import operator
from numpy import *
import numpy as np
import datetime

#Top K
k = 3

def createInX():
    
    #采用numpy函数库，可以方便快捷的实现分割转化
    fileHandle = open('./combT/test.feature', 'r')
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

    #print(inX)

    return inX


def createDataSet(fileHandleF, fileHandleL):
    
    #将feature中的字符串转换成二维数组
    list_arr = fileHandleF.readlines()
    l = len(list_arr)
    for i in range(l):
        list_arr[i] = list_arr[i].strip()           #strip(rm)：删除list_arr[i]字符串中开头、结尾处，rm字符。
        list_arr[i] = list_arr[i].strip('[]')
        list_arr[i] = list_arr[i].replace('?', '0') #replace是替换函数，把字符串结尾的\ｎ去掉。
        list_arr[i] = list_arr[i].split(',')        #split是分片函数，用于对指定位置的分割

    #字符串数组转换为浮点型数组
    dataset = np.array(list_arr)
    dataset = dataset.astype(float)
    fileHandleF.close()

    #将feature中的字符串转换成二维数组
    list_arr = fileHandleL.readlines()
    l = len(list_arr)
    for i in range(l):
        list_arr[i] = list_arr[i].strip()
        list_arr[i] = list_arr[i].strip('[]')
        
    #字符串数组转换为浮点型数组
    labels = np.array(list_arr)
    labels = labels.astype(int)
    fileHandleL.close()

    #print(dataset)
    #print(labels)

    return dataset, labels


def classify0(inX, dataset, labels, k, classCount):
    
    #inX是输入的测试样本。形如[x, y]
    #dataset是训练集样本
    #labels是训练集样本标签
    #K是top K最邻近

    #shape返回矩阵的[行数， 列数]
    #行数就是样本的数量
    dataSetSize = dataset.shape[0]
    
    #按照欧式距离公式计算距离 根号(x^2+y^2)
    diffMat = tile(inX, (dataSetSize, 1)) - dataset
    sqDiffMat = diffMat ** 2
    sqDistance = sqDiffMat.sum(axis=1)
    distance = sqDistance ** 0.5

    #按照升序进行快速排序， 返回的数组原下标
    sortedDistIndicies = distance.argsort()
    
    #投票的过程就是统计前K个最近样本所属类别包含的样本个数
    for i in range(k):
        #index = sortedDistIndicies[i]是第i个最邻近的样本下标
        #voteIlabel = labels[index]是样本index对应的分类结果('A' or 'B')
        voteIlabel = labels[sortedDistIndicies[i]]
        #classCount.get(voteIlabel, 0)返回voteIlabel的值，如果不存在， 则返回0
        #然后将票数增加1
        classCount[voteIlabel] = classCount.get(voteIlabel, 0) + 1
    
    return classCount


if __name__=="__main__":
    
    #计算程序的运行时间
    starttime = datetime.datetime.now()

    #清空result.label的内容
    fileHandle = open('./combR/result.label', 'w')
    fileHandle.truncate()
    fileHandle.close()

    #导入测试集,并记录测试数目
    inX = createInX()
    inXSetSize = inX.shape[0]

    #训练集1
    fileHandleF1 = open('./combF/1.feature', 'r')
    fileHandleL1 = open('./combL/1.label', 'r')
    dataset1, labels1 = createDataSet(fileHandleF1, fileHandleL1)
    fileHandleF1.close()
    fileHandleL1.close()

    #训练集2
    fileHandleF2 = open('./combF/2.feature', 'r')
    fileHandleL2 = open('./combL/2.label', 'r')
    dataset2, labels2 = createDataSet(fileHandleF2, fileHandleL2)
    fileHandleF2.close()
    fileHandleL2.close()
    
    #训练集3
    fileHandleF3 = open('./combF/3.feature', 'r')
    fileHandleL3 = open('./combL/3.label', 'r')
    dataset3, labels3 = createDataSet(fileHandleF3, fileHandleL3)
    fileHandleF3.close()
    fileHandleL3.close()

    #训练集4
    fileHandleF4 = open('./combF/4.feature', 'r')
    fileHandleL4 = open('./combL/4.label', 'r')
    dataset4, labels4 = createDataSet(fileHandleF4, fileHandleL4)
    fileHandleF4.close()
    fileHandleL4.close()

    #训练集5
    fileHandleF5 = open('./combF/5.feature', 'r')
    fileHandleL5 = open('./combL/5.label', 'r')
    dataset5, labels5 = createDataSet(fileHandleF5, fileHandleL5)
    fileHandleF5.close()
    fileHandleL5.close()

    #循环对比
    for i in range(inXSetSize):
        
        #存放最终的分类结果及相应的投票数    
        classCount0 = {}

        #进行投票1
        
        classCount1 = classify0(inX[i], dataset1, labels1, k, classCount0)
        #print(classCount1)
        
        #进行投票2
        
        classCount2 = classify0(inX[i], dataset2, labels2, k, classCount1)
        #print(classCount2)

        #进行投票3
        
        classCount3 = classify0(inX[i], dataset3, labels3, k, classCount2)
        #print(classCount3)
        
        #进行投票4
        
        classCount4 = classify0(inX[i], dataset4, labels4, k, classCount3)
        #print(classCount4)
        
        #进行投票5
        
        classCount5 = classify0(inX[i], dataset5, labels5, k, classCount4)
        #print(classCount5)
        
        
        #把分类的结果进行排序， 然后返回得票数最多的分类结果
        sortedClassCount = sorted(classCount5.items(), key = operator.itemgetter(1), reverse = True)
        className = sortedClassCount[0][0]

        #print('The class of test sample is %s' %className)
        fileHandle = open('./combR/result.label', 'a')
        fileHandle.write(str(className))
        fileHandle.write('\n')
        fileHandle.close()
        

    #输出运行时间
    endtime = datetime.datetime.now()
    print(endtime - starttime)