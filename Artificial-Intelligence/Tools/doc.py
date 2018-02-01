import  os
import os.path

#以写的方式打开文件
fileHandle = open('1.txt', 'w')
#\n表示换行
fileHandle.write('Ths is a test.\nReally, it is.')
#关闭文件
fileHandle.close()

#在文件结尾添加内容'ａ'
fileHandle = open('1.txt', 'a')
fileHandle.write('\nBottom line.')
fileHandle.close()

#读取文件内容并显示
fileHandle = open('1.txt')
print(fileHandle.read())
fileHandle.close()

####基于行的读写#####
fileHandle = open('A.feature')
print(fileHandle.readline())
fileHandle.close()

#也可以将文件内容把保存到一个ｌｉｓｔ中
fileHandle = open('1.txt')
fileList = fileHandle.readlines()
for fileLine in fileList:
    print ('>>', fileLine)
fileHandle.close()

#在文件中一次读取几个字节的内容
fileHandle = open('1.txt')
print(fileHandle.read(1))
fileHandle.seek(4)
print(fileHandle.read(1))

#随机访问文件中的位置seek
#python在读取一个文件时，会记住其在文件中的位置
fileHandle = open('1.txt')
garbage = fileHandle.readline()
print(garbage)
print(fileHandle.readline())
fileHandle.close()

#可以通过让Ｐｙｔｈｏｎ从头开始读来解决问题
fileHandle = open('1.txt')
garbage = fileHandle.readline()
print(garbage)
#指定读取的开始位置
fileHandle.seek(0)
print(fileHandle.readline())
fileHandle.close()

"""
文件操作：
os.mknod("test.txt") 创建空文件
fp = open("test.txt",w) 直接打开一个文件，如果文件不存在则创建文件

关于open 模式：

w 以写方式打开，
a 以追加模式打开 (从 EOF 开始, 必要时创建新文件)
r+ 以读写模式打开
w+ 以读写模式打开 (参见 w )
a+ 以读写模式打开 (参见 a )
rb 以二进制读模式打开
wb 以二进制写模式打开 (参见 w )
ab 以二进制追加模式打开 (参见 a )
rb+ 以二进制读写模式打开 (参见 r+ )
wb+ 以二进制读写模式打开 (参见 w+ )
ab+ 以二进制读写模式打开 (参见 a+ )

 

fp.read([size]) #size为读取的长度，以byte为单位

fp.readline([size]) #读一行，如果定义了size，有可能返回的只是一行的一部分

fp.readlines([size]) #把文件每一行作为一个list的一个成员，并返回这个list。其实它的内部是通过循环调用readline()来实现的。如果提供size参数，size是表示读取内容的总长，也就是说可能只读到文件的一部分。

fp.write(str) #把str写到文件中，write()并不会在str后加上一个换行符

fp.writelines(seq) #把seq的内容全部写到文件中(多行一次性写入)。这个函数也只是忠实地写入，不会在每行后面加上任何东西。

fp.close() #关闭文件。python会在一个文件不用后自动关闭文件，不过这一功能没有保证，最好还是养成自己关闭的习惯。 如果一个文件在关闭后还对其进行操作会产生ValueError

fp.flush() #把缓冲区的内容写入硬盘

fp.fileno() #返回一个长整型的”文件标签“

fp.isatty() #文件是否是一个终端设备文件（unix系统中的）

fp.tell() #返回文件操作标记的当前位置，以文件的开头为原点

fp.next() #返回下一行，并将文件操作标记位移到下一行。把一个file用于for … in file这样的语句时，就是调用next()函数来实现遍历的。

fp.seek(offset[,whence]) #将文件打操作标记移到offset的位置。这个offset一般是相对于文件的开头来计算的，一般为正数。但如果提供了whence参数就不一定了，whence可以为0表示从头开始计算，1表示以当前位置为原点计算。2表示以文件末尾为原点进行计算。需要注意，如果文件以a或a+的模式打开，每次进行写操作时，文件操作标记会自动返回到文件末尾。

fp.truncate([size]) #把文件裁成规定的大小，默认的是裁到当前文件操作标记的位置。如果size比文件的大小还要大，依据系统的不同可能是不改变文件，也可能是用0把文件补到相应的大小，也可能是以一些随机的内容加上去。

 

目录操作：
os.mkdir("file") 创建目录
复制文件：
shutil.copyfile("oldfile","newfile") oldfile和newfile都只能是文件
shutil.copy("oldfile","newfile") oldfile只能是文件夹，newfile可以是文件，也可以是目标目录
复制文件夹：
shutil.copytree("olddir","newdir") olddir和newdir都只能是目录，且newdir必须不存在
重命名文件（目录）
os.rename("oldname","newname") 文件或目录都是使用这条命令
移动文件（目录）
shutil.move("oldpos","newpos") 
删除文件
os.remove("file")
删除目录
os.rmdir("dir")只能删除空目录
shutil.rmtree("dir") 空目录、有内容的目录都可以删
转换目录
os.chdir("path") 换路径

 

ps: 文件操作时，常常配合正则表达式：

img_dir = img_dir.replace('\\','/')
"""