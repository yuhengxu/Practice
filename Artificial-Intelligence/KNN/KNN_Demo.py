#coding=UTF8
from numpy import *
import operator

def createDataSet():

    #函数作用：构建一组训练集，共四个样本
    #同时给出这四个样本的标签labels
    
    group = array([[1.0, 1.1], [1.0, 1.0], [0.0, 0.0], [0.0, 0.1]])
    labels = ['A', 'A', 'B', 'B']
    return group, labels

def classify0(inX, dataset, labels, k):
    
    #inX 是输入的测试样本，型如[x, y]
    #dataset 是训练样本集
    #labels 是训练样本标签
    #k 是top k最邻近
    
    #shape 返回矩阵的[行数， 列数]
    #那么shape[0]获取数据集的行数
    #行数就是样本的数量
    dataSetSize = dataset.shape[0]
    #列数，shape数组只有两项
    dataSetSize_col = dataset.shape[1]

    #按照欧式距离的计算公式计算距离
    #根号(x^2+y^2)

    #tile属于numpy模块下的函数
    #tile(A, reps)返回一个shape=reps的矩阵，每个矩阵的元素是A
    #比如A = [0, 1, 2]
    #那么tile(A, 2) = [0, 1, 2, 0, 1, 2]
    #tile(A, (2, 2)) = [[0, 1, 2, 0, 1, 2], [0, 1, 2, 0, 1, 2]]
    #tile(A, (2,1,2)) = [[[0, 1, 2, 0, 1, 2]], [[0, 1, 2, 0, 1, 2]]]
    
    #上面的结果分开理解为：
    #最外层是2个元素， 及最外层的[]中包含两个元素， 类似于[C, D], 而此处C=D， 因为是复制出来的
    #然后C包含一个元素， 及C=[E]， 同理D=[E]
    #最后E包含两个元素， 即E=[F, G], 此处F=G， 同理是复制出来的
    #F=A 是基础元素，带入即可
    #综合起来就是(2, 1, 2) = (C, C) = [[E], [E]] = [[[F, F]], [[F, F]]] = [[[A, A]], [[A, A]]]
    #这个地方就是为了把输入的测试样本扩展为和dataset的shape一样， 然后就可以直接做矩阵剪发了
    #比如， dataset有4个样本， 那就是4*2的矩阵， 输入的测试样本肯定是一个， 就是1*2，为了计算输入样本于训练集样本的距离
    #那么，需要对这个数据进行做差。这是一次比较，因为训练样本有N个，所以要进行N次对比
    #为了方便计算，需要吧输入样本复制N次，直接与训练样本作矩阵查运算， 就可以一次比较N个样本
    #比如inX = [0， 1]，dataset 就用函数返回的结果，那么
    #tile(inX, (4, 1)) = [[0.0, 1.0], [0.0, 1.0], [0.0, 1.0], [0.0, 1.0]]
    #做差之后
    #diffMat = [[-1.0, -0.1], [-1.0, 0.0], [0.0, 1.0], [0.0, 0.9]]
    diffMat = tile(inX, (dataSetSize, 1)) - dataset
    
    
    #diffMat就是输入样本与每个训练样本之间的差值， 然后对其每个x和y的差值进行平方运算
    #diffMat是一个矩阵， 矩阵××2表示对矩阵的每个元素进行平方操作
    sqDiffMat = diffMat ** 2

    #axis = 1表示按照横轴， sum表示累加， 即按照行进行累加
    #sqDistance = [[1.01], [1.0], [1.0], [0.81]]
    sqDistance = sqDiffMat.sum(axis=1)

    #对平方和进行开根号
    distance = sqDistance ** 0.5

    #按照升序进行快速排序，返回的是原数组的下标。
    #比如， x = [30, 10, 20, 40]
    #升序排序后应该是[10, 20, 30 ,40], 他们的原下标是[1, 2, 0 ,3]
    #那么， munpy.argsort(x) = [1, 2, 0 ,3]
    sortedDistIndicies = distance.argsort()

    #存放最终的分类结果及相应的投票数
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
    inX = [0.1, 0.1]
    #简单分类
    className = classify0(inX, dataset, labels, 3)
    print('The class of test sample is %s' %className)