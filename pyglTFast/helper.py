import collections

import trimesh
import numpy as np


_EYE = trimesh.transformations.identity_matrix()

def create_wkwargs(data):
    nodes = data.nodes

    meshes = collections.OrderedDict()

    # visited, kwargs for scene.graph.update
    graph = collections.deque()
    # unvisited, pairs of node indexes
    queue = collections.deque()

    name_index = {}

    for i, n in enumerate(nodes):
        name = str(i)
        name_index[name] = n

    names = {v: k for k, v in name_index.items()}

    base_frame = "world"
    if base_frame in names:
        base_frame = str(int(np.random.random() * 1e10))
    names[base_frame] = base_frame

    for scene in data.scenes:
        for root in scene.nodes:
            queue.append((None, root))

    consumed = set()


    while len(queue) > 0:
        # (int, int) pair of node indexes
        edge = queue.pop()

        # avoid looping forever if someone specified
        # recursive nodes
        if edge in consumed:
            continue

        consumed.add(edge)
        a, child = edge
        if a is None:
            # if we're at the root node
            # parent name is the base frame
            parent_name = names[base_frame]
        else:
            parent_name = names[a]

        child_name = names[child]

        # dict of child node
        # parent = nodes[a]
        # add edges of children to be processed
        if len(child.children):
            queue.extend([(child, i) for i in child.children])

        # kwargs to be passed to scene.graph.update
        kwargs = {"frame_from": parent_name, "frame_to": child_name}

        # grab matrix from child
        # parent -> child relationships have matrix stored in child
        # for the transform from parent to child
        if child.matrix.any():
            kwargs["matrix"] = np.array(
                child.matrix,
                dtype=np.float64).reshape((4, 4)).T
        else:
            # if no matrix set identity
            kwargs["matrix"] = trimesh.transformations.identity_matrix()

        # Now apply keyword translations
        # GLTF applies these in order: T * R * S
        # if "translation" in child:
        #     kwargs["matrix"] = np.dot(
        #         kwargs["matrix"],
        #         trimesh.transformations.translation_matrix(child["translation"]))
        # if "rotation" in child:
        #     # GLTF rotations are stored as (4,) XYZW unit quaternions
        #     # we need to re- order to our quaternion style, WXYZ
        #     quat = np.reshape(child["rotation"], 4)[[3, 0, 1, 2]]
        #     # add the rotation to the matrix
        #     kwargs["matrix"] = np.dot(
        #         kwargs["matrix"], trimesh.transformations.quaternion_matrix(quat))
        # if "scale" in child:
        #     # add scale to the matrix
        #     kwargs["matrix"] = np.dot(
        #         kwargs["matrix"],
        #         np.diag(np.concatenate((child['scale'], [1.0]))))

        # treat node metadata similarly to mesh metadata
        # if isinstance(child.get("extras"), dict):
        #     kwargs["metadata"] = child.extras

        # put any node extensions in a field of the metadata
        # if "extensions" in child:
        #     if "metadata" not in kwargs:
        #         kwargs["metadata"] = {}
        #     kwargs["metadata"]["gltf_extensions"] = child["extensions"]

        if child.mesh:
            primitives = child.mesh.primitives

            # if the node has a mesh associated with it
            if len(primitives) > 1:
                # append root node
                graph.append(kwargs.copy())
                # put primitives as children
                for primative in primitives:
                    # save the name of the geometry
                    geometry_name = '{}_{}'.format(
                        child_name, trimesh.util.unique_id(length=6))
                    kwargs["geometry"] = geometry_name
                    # no transformations
                    kwargs["matrix"] = _EYE
                    kwargs['frame_from'] = child_name
                    # if we have more than one primitive assign a new UUID
                    # frame name for the primitives after the first one
                    frame_to = geometry_name
                    kwargs['frame_to'] = frame_to
                    # append the edge with the mesh frame
                    graph.append(kwargs.copy())
                    meshes[geometry_name] = primitive_to_kwarg(primative)

            elif len(primitives) == 1:
                geometry_name = '{}_{}'.format(
                    child_name, trimesh.util.unique_id(length=6))
                kwargs["geometry"] = geometry_name
                kwargs['frame_to'] = child_name
                graph.append(kwargs.copy())
                meshes[geometry_name] = primitive_to_kwarg(primitives[0])
        else:
            # if the node doesn't have any geometry just add
            graph.append(kwargs)

    kwargs = {
        'class': 'Scene',
        'geometry': meshes,
        'graph': graph,
        'base_frame': base_frame,
        'metadata': {},
    }

    return kwargs


def primitive_to_kwarg(primitive):
    indices = primitive.indices
    faces = indices.dataUShort
    faces = faces.reshape((-1, 3))

    vertices = None
    normals = None

    for attr in primitive.attributes:
        if attr.type.name == 'position':
            vertices = attr.data.dataFloat
            continue
        if attr.type.name == 'normal':
            normals = attr.data.dataFloat
            continue

    if vertices is not None and normals is not None:
        geometry_kwargs = {
            'vertices': vertices,
            'faces': faces,
            'normals': normals,
            'process': False
        }
        return geometry_kwargs
    return None
