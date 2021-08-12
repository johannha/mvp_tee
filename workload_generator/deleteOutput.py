import os
import glob

dir = 'output'
filelist = glob.glob(os.path.join(dir, "*"))
for f in filelist:
    os.remove(f)

tee = '../tee/output'
teeList = glob.glob(os.path.join(tee, "*"))
for x in teeList:
    os.remove(x)
