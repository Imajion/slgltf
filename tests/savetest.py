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


def main():

    #---------------------------------------------------------------
    # Parse command line arguments
    ap = argparse.ArgumentParser(description='Test')
    ap.add_argument('--input', '-i', default='', type=str, help='Input file')
    ap.add_argument('--output', '-o', default='', type=str, help='Output file')
    _p = vars(ap.parse_args())

    try:

        if not _p['input']:
            raise "No input file specified"

        import slgltf
        if hasattr(slgltf, "slgltf"):
            slgltf = slgltf.slgltf

        gltf = slgltf.gltf()
        if not gltf.load(_p['input']):
            raise f"Failed to load gltf file: {_p['input']}"
        Log(f"Loaded gltf file: {_p['input']}")

        if _p['output']:
            if not gltf.save(_p['output']):
                raise f"Failed to save gltf file: {_p['output']}"
            Log(f"Saved gltf file: {_p['output']}")

    except Exception as e:
        Log(e)
        raise e

if __name__ == '__main__':
    main()

