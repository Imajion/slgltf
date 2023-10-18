import os
import pyglTFast
import trimesh

def setup_module(module):
    """ setup any state specific to the execution of the given module."""
    print('setup')
    if not os.path.exists("glTF-Sample-Models/"):
        os.system("git init glTF-Sample-Models")
        os.chdir("glTF-Sample-Models")
        os.system("git remote add origin https://github.com/KhronosGroup/glTF-Sample-Models.git")
        os.system("git config core.sparsecheckout true")
        f = open(".git/info/sparse-checkout", "w+")
        f.write("2.0/*\n")
        f.close()
        os.system("git pull --depth=1 origin master")
        os.chdir("..")


def test_import():
    scene = pyglTFast.load('./glTF-Sample-Models/2.0/Box/glTF/Box.gltf')
    scene.export('./tmp/box_out.glb')
