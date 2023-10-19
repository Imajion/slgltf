import os

import trimesh
import pyglTFastLib

from helper import create_wkwargs


def load(path: os.PathLike) -> trimesh.Scene:
    gltf = pyglTFastLib.gltf()
    gltf.load(str(path))
    data = gltf.data()

    kwargs = create_wkwargs(data)

    scene = trimesh.exchange.load.load_kwargs(**kwargs)
    return scene


def export(scene, param):
    return None
