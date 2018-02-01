import os
import os.path

with open('./combF/5.feature') as reader, open('test.feature', 'w') as writer:
    for index, line in enumerate(reader):
        if index % 1000 == 0:
            writer.write(line)

with open('./combL/5.label') as reader, open('test.label', 'w') as writer:
    for index, line in enumerate(reader):
        if index % 1000 == 0:
            writer.write(line)
