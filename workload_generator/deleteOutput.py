import os
import glob

dir = 'output'
filelist = glob.glob(os.path.join(dir, "*"))
for f in filelist:
    os.remove(f)
