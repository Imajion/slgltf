import trimesh


def add_nodes(scene: trimesh.Scene, node, node_count=0, parent_name=None):

    node_name = f'node_{node_count}'

    if not parent_name:
        scene.graph.update(frame_to=node_name, transform=node.matrix)
    else:
        scene.graph.update(frame_from=parent_name, frame_to=node_name, transform=node.matrix)

    if node.mesh:
        for primitive in node.mesh.primitives:

            indices = primitive.indices
            faces = indices.dataUShort
            face_count = len(faces) // 3
            faces = faces.reshape((face_count, 3))

            vertices = None
            normals = None

            for attr in primitive.attributes:
                if attr.type.name == 'position':
                    vertices = attr.data.dataFloat
                if attr.type.name == 'normal':
                    normals = attr.data.dataFloat

            if vertices is not None and normals is not None:
                mesh = trimesh.Trimesh(vertices=vertices, normals=normals, faces=faces, process=False)
                scene.add_geometry(mesh, node_name=node_name, parent_node_name=parent_name)

    for child in node.children:
        add_nodes(scene, child, node_count + 1, node_name)
