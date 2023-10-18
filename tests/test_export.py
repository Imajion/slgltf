import os

import trimesh

import pyglTFast


def setup_module(module):
    os.makedirs('tmp', exist_ok=True)
    for file in os.listdir('tmp'):
        os.remove(os.path.join('tmp', file))


def test_export_box():
    scene = trimesh.Scene()
    box = trimesh.creation.box(extents=[1, 1, 1])
    transform = trimesh.transformations.translation_matrix([4, 0, 0])
    scene.add_geometry(box, transform=transform, node_name='box')

    pyglTFast.export(scene, 'tmp/box.glb')
