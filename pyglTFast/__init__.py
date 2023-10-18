import os

import trimesh
import pyglTFastLib

from helper import add_nodes


def load(path: os.PathLike) -> trimesh.Scene:
    gltf = pyglTFastLib.gltf()
    gltf.load(str(path))
    data = gltf.data()
    root = data.nodes[0]

    scene = trimesh.Scene()

    add_nodes(scene, root)

    return scene


def export(scene, param):
    return None
