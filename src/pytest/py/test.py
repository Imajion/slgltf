#!/usr/bin/env python3

import os
import sys
import time
import argparse
import inspect
import traceback

try:
    import sparen
    Log = sparen.log
except Exception as e:
    Log = print


isNumpy = False
try:
    import numpy
    isNumpy = True
except Exception as e:
    isNumpy = False

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


def runTests(_p):

    # Load config
    prjroot = os.getcwd()
    cfgfile = findFile("PROJECT.txt", [os.getcwd(), libPath()])
    if cfgfile:
        prjroot = os.path.dirname(cfgfile)
        loadConfig(cfgfile)

    Log("\n------------------------- Starting tests -------------------------")
    Log("PARAMETERS  : %s" % _p)
    Log("PYTHON      : %s" % sys.version.replace("\n", ""))
    Log("WORKING DIR : %s" % os.getcwd())
    Log("PROJECT DIR : %s" % prjroot)
    Log("------------------------------------------------------------------")

    # Assert macros
    assert True
    assert not False

    Log("Importing pyglTFast")
    import pyglTFast

    Log("Checking pyglTFast")
    if hasattr(pyglTFast, "pyglTFast"):
        pyglTFast = pyglTFast.pyglTFast # <-- Debugging case only, don't do this in production

    # Show module path
    Log("[%s ] %s" % (pyglTFast.__name__, pyglTFast.__file__))

    # Show module version
    Log("[version] %s [%s]" % (pyglTFast.__version__, pyglTFast.__build__))

    datadir = os.path.join(prjroot, "data")
    if not os.path.isdir(datadir):
        Log(f"Data directory not found: {datadir}")
        assert False

    # Get a list of files in testdir that don't start with _
    testfiles = [f for f in os.listdir(datadir) if os.path.isfile(os.path.join(datadir, f)) and not f.startswith("_")]
    if not testfiles:
        Log(f"No test files found in: {datadir}")
        assert False

    # Test with oop wrapper
    Log("----------------------------------------")
    Log("Testing oop wrapper")
    Log("----------------------------------------")

    for f in testfiles:
        full = os.path.join(datadir, f)
        out = os.path.join(datadir, f"_{f}")
        if os.path.isfile(full):
            gltf = pyglTFast.gltf()
            if not gltf.load(full):
                Log(f"Failed to load gltf file: {full}")
                assert False
            Log(f"Loaded gltf file: {full}")
            if not gltf.save(out):
                Log(f"Failed to save gltf file: {out}")
                assert False
            Log(f"Saved gltf file: {out}")


    # # Test with static methods
    # Log("----------------------------------------")
    # Log("Testing static methods")
    # Log("----------------------------------------")

    # for f in testfiles:
    #     full = os.path.join(datadir, f)
    #     out = os.path.join(datadir, f"_{f}")
    #     if os.path.isfile(full):

    #         options = pyglTFast.cgltf_options
    #         [res, data] = pyglTFast.cgltf_parse_file(options, full)
    #         if res != pyglTFast.cgltf_result_success:
    #             Log(f"Failed to load gltf file: {full}")
    #             assert False
    #         Log(f"Loaded gltf file: {full}")

    # Iterate objects
    Log("----------------------------------------")
    Log("Iterating objects")
    Log("----------------------------------------")

    for f in testfiles:
        full = os.path.join(datadir, f)
        out = os.path.join(datadir, f"_{f}")
        if os.path.isfile(full):

            gltf = pyglTFast.gltf()
            if not gltf.load(full):
                Log(f"Failed to load gltf file: {full}")
                assert False
            Log(f"Loaded gltf file: {full}")

            data = gltf.data()
            if not data:
                Log(f"Failed to get gltf data")
                assert False

            Log(f"Data: {data}")

            Log(f"Mesh count: {data.meshes_count}")
            Log(f"meshes: {len(data.meshes)}")

            for mesh in data.meshes:
                Log(f"Mesh: {mesh.name}")
                for prim in mesh.primitives:
                    Log(f"  Primitive Type: {prim.type}")
                    Log(f"  Attributes    : {len(prim.attributes)}")
                    for attr in prim.attributes:
                        Log(f"    {attr.name}")
                        if attr.data:
                            Log(f"      Type      : {attr.data.type}")
                            Log(f"      Count     : {attr.data.count}")
                            Log(f"      Stride    : {attr.data.stride}")
                            dFloat = attr.data.dataFloat
                            Log(f"      Shape     : {dFloat.shape}")

                            # !!! Attempt to modify the first element of the data
                            # dFloat[0] = numpy.arange(1, dFloat.shape[1]+1, dtype=float)

                            Log(f"      Data Size : {len(dFloat)}")
                            Log(f"      Data      : {attr.data.dataFloat}")
                            if attr.data.buffer_view:
                                Log(f"        BView Type  : {attr.data.buffer_view.type}")
                                Log(f"        BView Offset: {attr.data.buffer_view.offset}")
                                Log(f"        BView Size  : {attr.data.buffer_view.size}/{attr.data.buffer_view.stride}={attr.data.buffer_view.size/attr.data.buffer_view.stride if attr.data.buffer_view.stride else 0}")
                                if attr.data.buffer_view.buffer:
                                    Log(f"          Buffer Size  : {attr.data.buffer_view.buffer.size}")


    Log("--- SUCCESS --- ")


def main():

    #---------------------------------------------------------------
    # Parse command line arguments
    ap = argparse.ArgumentParser(description='Test')
    ap.add_argument('--output', '-o', default='', type=str, help='Output file or directory')
    _p = vars(ap.parse_args())

    try:
        runTests(_p)

    except Exception as e:
        Log(e)
        raise e

if __name__ == '__main__':
    main()

