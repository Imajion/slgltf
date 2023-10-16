import os
from . import pyglTFast

def findFile(fname, dirlist):
    if not isinstance(dirlist, list):
        dirlist = [dirlist]
    for dir in dirlist:
        if os.path.isfile(dir):
            dir = os.path.dirname(dir)
        while dir and os.path.isdir(dir):
            f = os.path.join(dir, fname)
            if os.path.isfile(f):
                return f
            last = dir
            dir = os.path.dirname(dir)
            if last == dir or 3 > len(dir):
                break
    return None

def loadConfig(fname):
    globals()["__info__"] = {}
    if not fname or not os.path.isfile(fname):
        return
    with open(fname) as f:
        lines = f.readlines()
        for line in lines:
            parts = line.strip().replace("\t", " ").split(" ")
            k = parts.pop(0).strip()
            if '#' != k[0]:
                globals()["__%s__"%k] = " ".join(parts).strip()
                globals()["__info__"][k] = " ".join(parts).strip()

def libPath(p=None):
    return os.path.join(os.path.dirname(__file__), p) if p else os.path.dirname(__file__)

# Load config
loadConfig(libPath("PROJECT.txt"))
