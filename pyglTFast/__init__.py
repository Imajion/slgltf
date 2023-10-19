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
    if path.endswith('.glb'):
        c_data.file_type = pyglTFastLib.cgltf_file_type.cgltf_file_type_glb
    else:
        c_data.file_type = pyglTFastLib.cgltf_file_type.cgltf_file_type_gltf
    c_data.asset.generator = "sitelink"
    c_data.asset.version = "2.0"

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
    c_scene.nodes_count = 1

    c_data.append_node(c_root)

    for edge_key in edge_data.keys():
        (parent, child) = edge_key
        edge = edge_data[edge_key]
        c_parent = node_data[parent]

        c_child = pyglTFastLib.cgltf_node()
        c_child.parent = c_parent
        c_parent.append_child(c_child)
        c_data.append_node(c_child)

        if 'matrix' in edge:
            matrix = edge['matrix']
            c_child.matrix = matrix.flatten()


        if 'geometry' in edge:
            geometry_name = edge['geometry']
            tri_mesh = scene.geometry[geometry_name]
            c_mesh = pyglTFastLib.cgltf_mesh()
            c_primitive = pyglTFastLib.cgltf_primitive()

            # Faces accessor
            c_accessor_attribute = pyglTFastLib.cgltf_accessor()
            c_accessor_attribute.type = pyglTFastLib.cgltf_type.scalar
            c_accessor_attribute.component_type = pyglTFastLib.cgltf_component_type.r_16u

            c_primitive.indices = c_accessor_attribute
            c_accessor_attribute.dataUShort = tri_mesh.faces.flatten()

            # Vertex attributes
            c_vertex_attribute = pyglTFastLib.cgltf_attribute()
            c_vertex_attribute.index = 0
            c_vertex_attribute.name = 'POSITION'
            c_vertex_attribute.type = pyglTFastLib.cgltf_attribute_type.position

            c_vertex_accessor = pyglTFastLib.cgltf_accessor()
            c_vertex_accessor.type = pyglTFastLib.cgltf_type.vec3
            c_vertex_accessor.component_type = pyglTFastLib.cgltf_component_type.r_32f
            c_vertex_accessor.dataFloat = tri_mesh.vertices

            c_vertex_attribute.data = c_vertex_accessor

            # Normal attributes
            c_normal_attribute = pyglTFastLib.cgltf_attribute()
            c_normal_attribute.name = 'NORMAL'
            c_normal_attribute.index = 0
            c_normal_attribute.type = pyglTFastLib.cgltf_attribute_type.normal

            c_normal_accessor = pyglTFastLib.cgltf_accessor()
            c_normal_accessor.type = pyglTFastLib.cgltf_type.vec3
            c_normal_accessor.component_type = pyglTFastLib.cgltf_component_type.r_32f
            c_normal_accessor.dataFloat = tri_mesh.vertex_normals
            c_normal_attribute.data = c_normal_accessor

            c_mesh.primitives.append(c_primitive)

            c_child.mesh = c_mesh


    gltf.save(str(path))
