import os

import trimesh
import pyglTFastLib

from helper import create_wkwargs


def load(path: os.PathLike) -> trimesh.Scene:
    gltf = pyglTFastLib.gltf()
    gltf.load(str(path))
    data = gltf.data

    kwargs = create_wkwargs(data)

    scene = trimesh.exchange.load.load_kwargs(**kwargs)
    return scene


def export(scene, path):
    c_scene = pyglTFastLib.cgltf_scene()
    gltf = pyglTFastLib.gltf()
    c_data = pyglTFastLib.cgltf_data()
    gltf.data = c_data

    c_data.scene = c_scene
    c_data.append_scene(c_scene)

    node_data = {}
    edge_data = scene.graph.transforms.edge_data
    base_frame = scene.graph.base_frame

    c_root = pyglTFastLib.cgltf_node()
    c_root.append_child(c_root)
    node_data[base_frame] = c_root
    c_scene.append_node(c_root)

    for edge_key in edge_data.keys():
        (parent, child) = edge_key
        edge = edge_data[edge_key]
        c_parent = node_data[parent]

        c_child = pyglTFastLib.cgltf_node()
        c_child.parent = c_parent
        c_scene.append_node(c_child)
        c_parent.append_child(c_child)

        if 'matrix' in edge:
            matrix = edge['matrix']
            c_child.matrix = matrix.flatten()


        if 'geometry' in edge:
            geometry_name = edge['geometry']
            tri_mesh = scene.geometry[geometry_name]
            c_mesh = pyglTFastLib.cgltf_mesh()
            c_primitive = pyglTFastLib.cgltf_primitive()

            c_index_attribute = pyglTFastLib.cgltf_accessor()
            c_index_attribute.type = pyglTFastLib.cgltf_type.scalar
            c_index_attribute.component_type = pyglTFastLib.cgltf_component_type.r_16u

            c_primitive.indices = c_index_attribute
            c_index_attribute.dataUShort = tri_mesh.faces.flatten()

            c_vertex_attribute = pyglTFastLib.cgltf_attribute()
            c_vertex_attribute.dataFloat = tri_mesh.vertices.flatten()

            c_normal_attribute = pyglTFastLib.cgltf_attribute()
            c_normal_attribute.dataFloat = tri_mesh.vertex_normals.flatten()

            c_primitive.attributes.append(c_vertex_attribute)
            c_primitive.attributes.append(c_normal_attribute)

            c_mesh.primitives.append(c_primitive)

            c_child.mesh = c_mesh


    gltf.save(str(path))
