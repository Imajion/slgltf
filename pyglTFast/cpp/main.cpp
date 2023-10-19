
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <cgltf_write.h>
#include "slgltf.h"

namespace py = pybind11;
namespace SLGLTF_NS
{

// typedef struct accessor
// {
// 	char*   name;
//     float   min[3];
//     float   max[3];
// } accessor;

PYBIND11_MODULE(APPNAMERAW, m)
{
    m.doc() = APPDESC;
    m.attr("__version__") = APPVER;
    m.attr("__build__") = APPBUILD;
    m.def("version", [] () { return APPVER; });
    m.def("build", [] () { return APPBUILD; });

    // types
    py::class_<cgltf_size>(m, "cgltf_size")
        .def(py::init<>());
    py::class_<cgltf_ssize>(m, "cgltf_ssize")
        .def(py::init<>());
    py::class_<cgltf_float>(m, "cgltf_float")
        .def(py::init<>());
    py::class_<cgltf_int>(m, "cgltf_int")
        .def(py::init<>());
    py::class_<cgltf_uint>(m, "cgltf_uint")
        .def(py::init<>());
    // py::class_<cgltf_bool>(m, "cgltf_bool")
    //     .def(py::init<>());


    // cgltf_file_type
    py::enum_<cgltf_file_type>(m, "cgltf_file_type")
            .value("cgltf_file_type_invalid", cgltf_file_type::cgltf_file_type_invalid)
            .value("cgltf_file_type_gltf", cgltf_file_type::cgltf_file_type_gltf)
            .value("cgltf_file_type_glb", cgltf_file_type::cgltf_file_type_glb)
            .value("cgltf_file_type_max_enum", cgltf_file_type::cgltf_file_type_max_enum)
            .export_values();

    // cgltf_result
    py::enum_<cgltf_result>(m, "cgltf_result")
            .value("success", cgltf_result_success)
            .value("data_too_short", cgltf_result_data_too_short)
            .value("unknown_format", cgltf_result_unknown_format)
            .value("invalid_json", cgltf_result_invalid_json)
            .value("invalid_gltf", cgltf_result_invalid_gltf)
            .value("invalid_options", cgltf_result_invalid_options)
            .value("file_not_found", cgltf_result_file_not_found)
            .value("io_error", cgltf_result_io_error)
            .value("out_of_memory", cgltf_result_out_of_memory)
            .value("legacy_gltf", cgltf_result_legacy_gltf)
            .value("max_enum", cgltf_result_max_enum)
            .export_values();

    // // cgltf_memory_options
    // py::class_<cgltf_memory_options>(m, "cgltf_memory_options")
    //     .def(py::init<>())
    //     .def_readwrite("alloc_func", &cgltf_memory_options::alloc_func)
    //     .def_readwrite("free_func", &cgltf_memory_options::free_func)
    //     .def_readwrite("user_data", &cgltf_memory_options::user_data);

    // // cgltf_file_options
    // py::class_<cgltf_file_options>(m, "cgltf_file_options")
    //     .def(py::init<>())
    //     .def_readwrite("read", &cgltf_file_options::read)
    //     .def_readwrite("release", &cgltf_file_options::release)
    //     .def_readwrite("user_data", &cgltf_file_options::user_data);

    // cgltf_options
    py::class_<cgltf_options>(m, "cgltf_options")
        .def(py::init<>())
        .def_readwrite("type", &cgltf_options::type)
        .def_readwrite("json_token_count", &cgltf_options::json_token_count)
        .def_readwrite("memory", &cgltf_options::memory)
        .def_readwrite("file", &cgltf_options::file);

    // cgltf_buffer_view_type
    py::enum_<cgltf_buffer_view_type>(m, "cgltf_buffer_view_type")
        .value("invalid", cgltf_buffer_view_type_invalid)
        .value("indices", cgltf_buffer_view_type_indices)
        .value("vertices", cgltf_buffer_view_type_vertices)
        .value("max_enum", cgltf_buffer_view_type_max_enum)
        .export_values();

    // cgltf_attribute_type
    py::enum_<cgltf_attribute_type>(m, "cgltf_attribute_type")
        .value("invalid", cgltf_attribute_type_invalid)
        .value("position", cgltf_attribute_type_position)
        .value("normal", cgltf_attribute_type_normal)
        .value("tangent", cgltf_attribute_type_tangent)
        .value("texcoord", cgltf_attribute_type_texcoord)
        .value("color", cgltf_attribute_type_color)
        .value("joints", cgltf_attribute_type_joints)
        .value("weights", cgltf_attribute_type_weights)
        .value("custom", cgltf_attribute_type_custom)
        .value("max_enum", cgltf_attribute_type_max_enum)
        .export_values();

    // cgltf_component_type
    py::enum_<cgltf_component_type>(m, "cgltf_component_type")
        .value("invalid", cgltf_component_type_invalid)
        .value("r_8", cgltf_component_type_r_8)
        .value("r_8u", cgltf_component_type_r_8u)
        .value("r_16", cgltf_component_type_r_16)
        .value("r_16u", cgltf_component_type_r_16u)
        .value("r_32u", cgltf_component_type_r_32u)
        .value("r_32f", cgltf_component_type_r_32f)
        .value("max_enum", cgltf_component_type_max_enum)
        .export_values();

    // cgltf_type
    py::enum_<cgltf_type>(m, "cgltf_type")
        .value("invalid", cgltf_type_invalid)
        .value("scalar", cgltf_type_scalar)
        .value("vec2", cgltf_type_vec2)
        .value("vec3", cgltf_type_vec3)
        .value("vec4", cgltf_type_vec4)
        .value("mat2", cgltf_type_mat2)
        .value("mat3", cgltf_type_mat3)
        .value("mat4", cgltf_type_mat4)
        .value("max_enum", cgltf_type_max_enum)
        .export_values();

    // cgltf_primitive_type
    py::enum_<cgltf_primitive_type>(m, "cgltf_primitive_type")
        .value("points", cgltf_primitive_type::cgltf_primitive_type_points)
        .value("lines", cgltf_primitive_type::cgltf_primitive_type_lines)
        .value("line_loop", cgltf_primitive_type::cgltf_primitive_type_line_loop)
        .value("line_strip", cgltf_primitive_type::cgltf_primitive_type_line_strip)
        .value("triangles", cgltf_primitive_type::cgltf_primitive_type_triangles)
        .value("triangle_strip", cgltf_primitive_type::cgltf_primitive_type_triangle_strip)
        .value("triangle_fan", cgltf_primitive_type::cgltf_primitive_type_triangle_fan)
        .value("max_enum", cgltf_primitive_type::cgltf_primitive_type_max_enum)
        .export_values();

    // cgltf_alpha_mode
    py::enum_<cgltf_alpha_mode>(m, "cgltf_alpha_mode")
        .value("opaque", cgltf_alpha_mode::cgltf_alpha_mode_opaque)
        .value("mask", cgltf_alpha_mode::cgltf_alpha_mode_mask)
        .value("blend", cgltf_alpha_mode::cgltf_alpha_mode_blend)
        .value("max_enum", cgltf_alpha_mode::cgltf_alpha_mode_max_enum)
        .export_values();

    // cgltf_animation_path_type
    py::enum_<cgltf_animation_path_type>(m, "cgltf_animation_path_type")
        .value("invalid", cgltf_animation_path_type_invalid)
        .value("translation", cgltf_animation_path_type_translation)
        .value("rotation", cgltf_animation_path_type_rotation)
        .value("scale", cgltf_animation_path_type_scale)
        .value("weights", cgltf_animation_path_type_weights)
        .value("max_enum", cgltf_animation_path_type_max_enum)
        .export_values();

    // cgltf_interpolation_type
    py::enum_<cgltf_interpolation_type>(m, "cgltf_interpolation_type")
        .value("linear", cgltf_interpolation_type_linear)
        .value("step", cgltf_interpolation_type_step)
        .value("cubic_spline", cgltf_interpolation_type_cubic_spline)
        .value("max_enum", cgltf_interpolation_type_max_enum)
        .export_values();

    // cgltf_camera_type
    py::enum_<cgltf_camera_type>(m, "cgltf_camera_type")
        .value("invalid", cgltf_camera_type_invalid)
        .value("perspective", cgltf_camera_type_perspective)
        .value("orthographic", cgltf_camera_type_orthographic)
        .value("max_enum", cgltf_camera_type_max_enum)
        .export_values();

    // cgltf_light_type
    py::enum_<cgltf_light_type>(m, "cgltf_light_type")
        .value("invalid", cgltf_light_type_invalid)
        .value("directional", cgltf_light_type_directional)
        .value("point", cgltf_light_type_point)
        .value("spot", cgltf_light_type_spot)
        .value("max_enum", cgltf_light_type_max_enum)
        .export_values();

    // cgltf_data_free_method
    py::enum_<cgltf_data_free_method>(m, "cgltf_data_free_method")
        .value("none", cgltf_data_free_method::cgltf_data_free_method_none)
        .value("file_release", cgltf_data_free_method::cgltf_data_free_method_file_release)
        .value("memory_free", cgltf_data_free_method::cgltf_data_free_method_memory_free)
        .value("max_enum", cgltf_data_free_method::cgltf_data_free_method_max_enum)
        .export_values();

    // cgltf_extras
    py::class_<cgltf_extras>(m, "cgltf_extras")
        .def(py::init<>())
        .def_readwrite("start_offset", &cgltf_extras::start_offset)  // Deprecated
        .def_readwrite("end_offset", &cgltf_extras::end_offset)      // Deprecated
        .def_readwrite("data", &cgltf_extras::data);

    // cgltf_extension
    py::class_<cgltf_extension>(m, "cgltf_extension")
        .def(py::init<>())
        .def_readwrite("name", &cgltf_extension::name)
        .def_readwrite("data", &cgltf_extension::data);

    // cgltf_buffer
    py::class_<cgltf_buffer>(m, "cgltf_buffer")
        .def(py::init<>())
        .def_readwrite("name", &cgltf_buffer::name)
        .def_readwrite("size", &cgltf_buffer::size)
        .def_readwrite("uri", &cgltf_buffer::uri)
        .def_readwrite("data", &cgltf_buffer::data)
        .def_readwrite("data_free_method", &cgltf_buffer::data_free_method)
        .def_readwrite("extras", &cgltf_buffer::extras)
        .def_readwrite("extensions_count", &cgltf_buffer::extensions_count)
        .def_readwrite("extensions", &cgltf_buffer::extensions);

    // cgltf_meshopt_compression_mode
    py::enum_<cgltf_meshopt_compression_mode>(m, "cgltf_meshopt_compression_mode")
        .value("invalid", cgltf_meshopt_compression_mode_invalid)
        .value("attributes", cgltf_meshopt_compression_mode_attributes)
        .value("triangles", cgltf_meshopt_compression_mode_triangles)
        .value("indices", cgltf_meshopt_compression_mode_indices)
        .value("max_enum", cgltf_meshopt_compression_mode_max_enum);

    // cgltf_meshopt_compression_filter
    py::enum_<cgltf_meshopt_compression_filter>(m, "cgltf_meshopt_compression_filter")
        .value("none", cgltf_meshopt_compression_filter_none)
        .value("octahedral", cgltf_meshopt_compression_filter_octahedral)
        .value("quaternion", cgltf_meshopt_compression_filter_quaternion)
        .value("exponential", cgltf_meshopt_compression_filter_exponential)
        .value("max_enum", cgltf_meshopt_compression_filter_max_enum)
        .export_values();

    // cgltf_meshopt_compression
    py::class_<cgltf_meshopt_compression>(m, "cgltf_meshopt_compression")
        .def(py::init<>())
        .def_readwrite("buffer", &cgltf_meshopt_compression::buffer)
        .def_readwrite("offset", &cgltf_meshopt_compression::offset)
        .def_readwrite("size", &cgltf_meshopt_compression::size)
        .def_readwrite("stride", &cgltf_meshopt_compression::stride)
        .def_readwrite("count", &cgltf_meshopt_compression::count)
        .def_readwrite("mode", &cgltf_meshopt_compression::mode)
        .def_readwrite("filter", &cgltf_meshopt_compression::filter);

    // cgltf_buffer_view
    py::class_<cgltf_buffer_view>(m, "cgltf_buffer_view")
        .def(py::init<>())
        .def_readwrite("name", &cgltf_buffer_view::name)
        .def_readwrite("buffer", &cgltf_buffer_view::buffer)
        .def_readwrite("offset", &cgltf_buffer_view::offset)
        .def_readwrite("size", &cgltf_buffer_view::size)
        .def_readwrite("stride", &cgltf_buffer_view::stride)
        .def_readwrite("type", &cgltf_buffer_view::type)
        .def_readwrite("data", &cgltf_buffer_view::data)
/*        .def_property("dataFloat",
            [](const cgltf_buffer_view &v) -> py::array_t<float> {
                char* raw = v.data ? (char*)v.data : (char*)v.buffer->data;
                float *data = (float*)(raw + v.offset);
                cgltf_size sz = cgltf_num_components(v.type);
                if (v.size % (sz * sizeof(float)) != 0) {
                    throw std::runtime_error("Buffer view size is not a multiple of the component size");
                }
                // return py::array_t<float>(v.size / sizeof(float), data);
                return py::array_t<float>({v.size / sizeof(float) / sz, sz}, data);
            },
            [](cgltf_buffer_view &v, py::array_t<float> value) {
                char* raw = v.data ? (char*)v.data : (char*)v.buffer->data;
                float *data = (float*)(raw + v.offset);
                size_t expectedFloats = v.size / sizeof(float);

                if (value.ndim() == 1) {
                    auto r = value.unchecked<1>();
                    if (r.size() != expectedFloats) {
                        throw std::runtime_error("Mismatched array sizes");
                    }
                    for (size_t i = 0; i < r.size(); ++i) {
                        data[i] = r(i);
                    }
                }
                else if (value.ndim() == 2) {
                    auto r = value.unchecked<2>();
                    size_t totalFloats = r.shape(0) * r.shape(1);
                    if (totalFloats != expectedFloats) {
                        throw std::runtime_error("Mismatched array sizes");
                    }
                    size_t index = 0;
                    for (ssize_t i = 0; i < r.shape(0); ++i) {
                        for (ssize_t j = 0; j < r.shape(1); ++j) {
                            data[index++] = r(i, j);
                        }
                    }
                }
                else {
                    throw std::runtime_error("Array dimensions must be 1 or 2");
                }
            })
*/
        .def_readwrite("has_meshopt_compression", &cgltf_buffer_view::has_meshopt_compression)
        .def_readwrite("meshopt_compression", &cgltf_buffer_view::meshopt_compression)
        .def_readwrite("extras", &cgltf_buffer_view::extras)
        .def_readwrite("extensions_count", &cgltf_buffer_view::extensions_count)
        .def_readwrite("extensions", &cgltf_buffer_view::extensions);

    // cgltf_accessor_sparse
    py::class_<cgltf_accessor_sparse>(m, "cgltf_accessor_sparse")
        .def(py::init<>())
        .def_readwrite("count", &cgltf_accessor_sparse::count)
        .def_readwrite("indices_buffer_view", &cgltf_accessor_sparse::indices_buffer_view)
        .def_readwrite("indices_byte_offset", &cgltf_accessor_sparse::indices_byte_offset)
        .def_readwrite("indices_component_type", &cgltf_accessor_sparse::indices_component_type)
        .def_readwrite("values_buffer_view", &cgltf_accessor_sparse::values_buffer_view)
        .def_readwrite("values_byte_offset", &cgltf_accessor_sparse::values_byte_offset)
        .def_readwrite("extras", &cgltf_accessor_sparse::extras)
        .def_readwrite("indices_extras", &cgltf_accessor_sparse::indices_extras)
        .def_readwrite("values_extras", &cgltf_accessor_sparse::values_extras)
        .def_readwrite("extensions_count", &cgltf_accessor_sparse::extensions_count)
        .def_readwrite("extensions", &cgltf_accessor_sparse::extensions)
        .def_readwrite("indices_extensions_count", &cgltf_accessor_sparse::indices_extensions_count)
        .def_readwrite("indices_extensions", &cgltf_accessor_sparse::indices_extensions)
        .def_readwrite("values_extensions_count", &cgltf_accessor_sparse::values_extensions_count)
        .def_readwrite("values_extensions", &cgltf_accessor_sparse::values_extensions);

    // cgltf_accessor
    py::class_<cgltf_accessor>(m, "cgltf_accessor")
        .def(py::init<>())
        .def_readwrite("name", &cgltf_accessor::name)
        .def_readwrite("component_type", &cgltf_accessor::component_type)
        .def_readwrite("normalized", &cgltf_accessor::normalized)
        .def_readwrite("type", &cgltf_accessor::type)
        .def_readwrite("offset", &cgltf_accessor::offset)
        .def_readwrite("count", &cgltf_accessor::count)
        .def_readwrite("stride", &cgltf_accessor::stride)
        .def_readwrite("buffer_view", &cgltf_accessor::buffer_view)
        .def_property("dataUShort",
            [](const cgltf_accessor &v) -> py::array_t<uint16_t>
            {
                if (v.component_type != cgltf_component_type_r_16u)  // Assume this is the correct enum value for int32.
                    throw std::runtime_error("Accessor component type is not int32");

                if (v.is_sparse || 0 >= v.count)
                    return py::array_t<uint16_t>();

                cgltf_size sz = cgltf_num_components(v.type);
                const uint8_t *temp_view = cgltf_buffer_view_data(v.buffer_view);
                uint16_t *view = v.buffer_view ? reinterpret_cast<uint16_t*>(const_cast<uint8_t*>(temp_view)) : nullptr;
                if (view == nullptr)
                    if (1 == sz)
                        return py::array_t<uint16_t>(v.count, nullptr);
                    else
                        return py::array_t<uint16_t>({v.count / sz, sz}, nullptr);

                uint16_t *data = reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(view) + v.offset);
                if ((v.offset + v.count * sizeof(uint16_t)) > v.buffer_view->size)
                    throw std::runtime_error("Accessor data out of range");

                if (v.count % sz != 0)
                    throw std::runtime_error("Buffer view size is not a multiple of the component size");

                return py::array_t<uint16_t>({v.count / sz, sz}, data, py::capsule(data, [](void* data) {}));
            },
            [](cgltf_accessor &v, py::array_t<uint16_t> value)
            {
                if (v.component_type != cgltf_component_type_r_16u)
                    throw std::runtime_error("Accessor component type is not int32");

                if (v.is_sparse || 0 >= v.count)
                    return;

                cgltf_size sz = cgltf_num_components(v.type);
                const uint8_t *temp_view = cgltf_buffer_view_data(v.buffer_view);
                uint16_t *view = v.buffer_view ? reinterpret_cast<uint16_t*>(const_cast<uint8_t*>(temp_view)) : nullptr;
                if (view == nullptr)
                    return;

                uint16_t *data = reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(view) + v.offset);
                if (value.ndim() == 1) {
                    auto r = value.unchecked<1>();
                    if (r.size() != v.count) {
                        throw std::runtime_error("Mismatched array sizes");
                    }
                    for (size_t i = 0; i < r.size(); ++i) {
                        data[i] = r(i);
                    }
                }
                else if (value.ndim() == 2) {
                    auto r = value.unchecked<2>();
                    size_t totalInts = r.shape(0) * r.shape(1);
                    if (totalInts != v.count) {
                        throw std::runtime_error("Mismatched array sizes");
                    }
                    size_t index = 0;
                    for (ssize_t i = 0; i < r.shape(0); ++i) {
                        for (ssize_t j = 0; j < r.shape(1); ++j) {
                            data[index++] = r(i, j);
                        }
                    }
                }
                else {
                    throw std::runtime_error("Array dimensions must be 1 or 2");
                }
            })
            .def_property("dataFloat",
            [](const cgltf_accessor &v) -> py::array_t<float>
            {
                if (v.component_type != cgltf_component_type_r_32f)
                {   throw std::runtime_error("Accessor component type is not float32");
                }

                if (v.is_sparse || 0 >= v.count)
                    return py::array_t<float>();

                cgltf_size sz = cgltf_num_components(v.type);
                uint8_t *view = v.buffer_view ? const_cast<uint8_t*>(cgltf_buffer_view_data(v.buffer_view)) : nullptr;
                if (view == nullptr)
                    if (1 == sz)
                        return py::array_t<float>(v.count, nullptr);
                    else
                        return py::array_t<float>({v.count, sz}, nullptr);

                float *data = reinterpret_cast<float*>(view + v.offset);
                if ((v.offset + v.count * sizeof(float)) > v.buffer_view->size)
                {   throw std::runtime_error("Accessor data out of range");
                }

//                if (v.count % sz != 0)
//                {   throw std::runtime_error("Buffer view size is not a multiple of the component size");
//                }

                return py::array_t<float>({v.count, sz}, data, py::capsule(data, [](void* data) {}));
            },
            [](cgltf_accessor &v, py::array_t<float> value)
            {
                if (v.component_type != cgltf_component_type_r_32f)
                {   throw std::runtime_error("Accessor component type is not float32");
                }

                if (v.is_sparse || 0 >= v.count)
                    return;

                cgltf_size sz = cgltf_num_components(v.type);
                uint8_t *view = v.buffer_view ? const_cast<uint8_t*>(cgltf_buffer_view_data(v.buffer_view)) : nullptr;
                if (view == nullptr)
                    return;

                float *data = reinterpret_cast<float*>(view + v.offset);
                if (value.ndim() == 1) {
                    auto r = value.unchecked<1>();
                    if (r.size() != v.count) {
                        throw std::runtime_error("Mismatched array sizes");
                    }
                    for (size_t i = 0; i < r.size(); ++i) {
                        data[i] = r(i);
                    }
                }
                else if (value.ndim() == 2) {
                    auto r = value.unchecked<2>();
                    size_t totalFloats = r.shape(0) * r.shape(1);
                    if (totalFloats != v.count) {
                        throw std::runtime_error("Mismatched array sizes");
                    }
                    size_t index = 0;
                    for (ssize_t i = 0; i < r.shape(0); ++i) {
                        for (ssize_t j = 0; j < r.shape(1); ++j) {
                            data[index++] = r(i, j);
                        }
                    }
                }
                else {
                    throw std::runtime_error("Array dimensions must be 1 or 2");
                }
            })
        .def_readwrite("has_min", &cgltf_accessor::has_min)
        .def_property("min",
            [](const cgltf_accessor &a) -> py::array_t<cgltf_float>
            {
                return py::array_t<cgltf_float>(sizeof(cgltf_accessor::min)/sizeof(cgltf_float), a.min);
            },
            [](cgltf_accessor &a, py::array_t<cgltf_float> value)
            {
                auto r = value.unchecked<1>();
                for (size_t i = 0; i < sizeof(cgltf_accessor::min)/sizeof(cgltf_float); ++i)
                {
                    a.min[i] = r(i);
                }
            }
        )
        .def_readwrite("has_max", &cgltf_accessor::has_max)
        .def_property("max",
            [](const cgltf_accessor &a) -> py::array_t<cgltf_float>
            {
                return py::array_t<cgltf_float>(sizeof(cgltf_accessor::max)/sizeof(cgltf_float), a.max);
            },
            [](cgltf_accessor &a, py::array_t<cgltf_float> value)
            {
                auto r = value.unchecked<1>();
                for (size_t i = 0; i < sizeof(cgltf_accessor::max)/sizeof(cgltf_float); ++i)
                {
                    a.max[i] = r(i);
                }
            }
        )
        .def_readwrite("is_sparse", &cgltf_accessor::is_sparse)
        .def_readwrite("sparse", &cgltf_accessor::sparse)
        .def_readwrite("extras", &cgltf_accessor::extras)
        .def_readwrite("extensions_count", &cgltf_accessor::extensions_count)
        .def_readwrite("extensions", &cgltf_accessor::extensions);

    // cgltf_attribute
    py::class_<cgltf_attribute>(m, "cgltf_attribute")
        .def(py::init<>())
        .def_readwrite("name", &cgltf_attribute::name)
        .def_readwrite("type", &cgltf_attribute::type)
        .def_readwrite("index", &cgltf_attribute::index)
        .def_readwrite("data", &cgltf_attribute::data);

    // cgltf_image
    py::class_<cgltf_image>(m, "cgltf_image")
        .def(py::init<>())
        .def_readwrite("name", &cgltf_image::name)
        .def_readwrite("uri", &cgltf_image::uri)
        .def_readwrite("buffer_view", &cgltf_image::buffer_view)
        .def_readwrite("mime_type", &cgltf_image::mime_type)
        .def_readwrite("extras", &cgltf_image::extras)
        .def_readwrite("extensions_count", &cgltf_image::extensions_count)
        .def_readwrite("extensions", &cgltf_image::extensions);

    // cgltf_sampler
    py::class_<cgltf_sampler>(m, "cgltf_sampler")
        .def(py::init<>())
        .def_readwrite("name", &cgltf_sampler::name)
        .def_readwrite("mag_filter", &cgltf_sampler::mag_filter)
        .def_readwrite("min_filter", &cgltf_sampler::min_filter)
        .def_readwrite("wrap_s", &cgltf_sampler::wrap_s)
        .def_readwrite("wrap_t", &cgltf_sampler::wrap_t)
        .def_readwrite("extras", &cgltf_sampler::extras)
        .def_readwrite("extensions_count", &cgltf_sampler::extensions_count)
        .def_readwrite("extensions", &cgltf_sampler::extensions);

    // cgltf_texture
    py::class_<cgltf_texture>(m, "cgltf_texture")
        .def(py::init<>())
        .def_readwrite("name", &cgltf_texture::name)
        .def_readwrite("image", &cgltf_texture::image)
        .def_readwrite("sampler", &cgltf_texture::sampler)
        .def_readwrite("has_basisu", &cgltf_texture::has_basisu)
        .def_readwrite("basisu_image", &cgltf_texture::basisu_image)
        .def_readwrite("extras", &cgltf_texture::extras)
        .def_readwrite("extensions_count", &cgltf_texture::extensions_count)
        .def_readwrite("extensions", &cgltf_texture::extensions);

    // cgltf_texture_transform
    py::class_<cgltf_texture_transform>(m, "cgltf_texture_transform")
        .def(py::init<>())
        .def_property("offset",
            [](const cgltf_texture_transform &t) -> py::array_t<cgltf_float> {
                return py::array_t<cgltf_float>(sizeof(cgltf_texture_transform::offset)/sizeof(cgltf_float), t.offset);
            },
            [](cgltf_texture_transform &t, py::array_t<cgltf_float> value) {
                auto r = value.unchecked<1>();
                for (size_t i = 0; i < sizeof(cgltf_texture_transform::offset)/sizeof(cgltf_float); ++i)
                {
                    t.offset[i] = r(i);
                }
            })
        .def_readwrite("rotation", &cgltf_texture_transform::rotation)
        .def_property("scale",
            [](const cgltf_texture_transform &t) -> py::array_t<cgltf_float> {
                return py::array_t<cgltf_float>(sizeof(cgltf_texture_transform::scale)/sizeof(cgltf_float), t.scale);
            },
            [](cgltf_texture_transform &t, py::array_t<cgltf_float> value) {
                auto r = value.unchecked<1>();
                for (size_t i = 0; i < sizeof(cgltf_texture_transform::scale)/sizeof(cgltf_float); ++i)
                {
                    t.scale[i] = r(i);
                }
            })
        .def_readwrite("has_texcoord", &cgltf_texture_transform::has_texcoord)
        .def_readwrite("texcoord", &cgltf_texture_transform::texcoord);

    // cgltf_texture_view
    py::class_<cgltf_texture_view>(m, "cgltf_texture_view")
        .def(py::init<>())
        .def_readwrite("texture", &cgltf_texture_view::texture)
        .def_readwrite("texcoord", &cgltf_texture_view::texcoord)
        .def_readwrite("scale", &cgltf_texture_view::scale)
        .def_readwrite("has_transform", &cgltf_texture_view::has_transform)
        .def_readwrite("transform", &cgltf_texture_view::transform)
        .def_readwrite("extras", &cgltf_texture_view::extras)
        .def_readwrite("extensions_count", &cgltf_texture_view::extensions_count)
        .def_readwrite("extensions", &cgltf_texture_view::extensions);

    // cgltf_material_pbr_metallic_roughness
    py::class_<cgltf_pbr_metallic_roughness>(m, "cgltf_pbr_metallic_roughness")
        .def(py::init<>())
        .def_readwrite("base_color_texture", &cgltf_pbr_metallic_roughness::base_color_texture)
        .def_readwrite("metallic_roughness_texture", &cgltf_pbr_metallic_roughness::metallic_roughness_texture)
        .def_property("base_color_factor",
            [](const cgltf_pbr_metallic_roughness &p) -> py::array_t<cgltf_float> {
                return py::array_t<cgltf_float>(sizeof(cgltf_pbr_metallic_roughness::base_color_factor)/sizeof(cgltf_float), p.base_color_factor);
            },
            [](cgltf_pbr_metallic_roughness &p, py::array_t<cgltf_float> value) {
                auto r = value.unchecked<1>();
                for (size_t i = 0; i < sizeof(cgltf_pbr_metallic_roughness::base_color_factor)/sizeof(cgltf_float); ++i)
                {
                    p.base_color_factor[i] = r(i);
                }
            })
        .def_readwrite("metallic_factor", &cgltf_pbr_metallic_roughness::metallic_factor)
        .def_readwrite("roughness_factor", &cgltf_pbr_metallic_roughness::roughness_factor);

    // cgltf_material_pbr_specular_glossiness
    py::class_<cgltf_pbr_specular_glossiness>(m, "cgltf_pbr_specular_glossiness")
        .def(py::init<>())
        .def_readwrite("diffuse_texture", &cgltf_pbr_specular_glossiness::diffuse_texture)
        .def_readwrite("specular_glossiness_texture", &cgltf_pbr_specular_glossiness::specular_glossiness_texture)
        .def_property("diffuse_factor", [](const cgltf_pbr_specular_glossiness &s) -> py::array_t<cgltf_float> {
            return py::array_t<cgltf_float>(sizeof(cgltf_pbr_specular_glossiness::diffuse_factor)/sizeof(cgltf_float), s.diffuse_factor);
        }, [](cgltf_pbr_specular_glossiness &s, py::array_t<cgltf_float> value) {
            auto r = value.unchecked<1>();
            for (size_t i = 0; i < sizeof(cgltf_pbr_specular_glossiness::diffuse_factor)/sizeof(cgltf_float); ++i)
            {
                s.diffuse_factor[i] = r(i);
            }
        })
        .def_property("specular_factor", [](const cgltf_pbr_specular_glossiness &s) -> py::array_t<cgltf_float> {
            return py::array_t<cgltf_float>(sizeof(cgltf_pbr_specular_glossiness::specular_factor)/sizeof(cgltf_float), s.specular_factor);
        }, [](cgltf_pbr_specular_glossiness &s, py::array_t<cgltf_float> value) {
            auto r = value.unchecked<1>();
            for (size_t i = 0; i < sizeof(cgltf_pbr_specular_glossiness::specular_factor)/sizeof(cgltf_float); ++i)
            {
                s.specular_factor[i] = r(i);
            }
        })
        .def_readwrite("glossiness_factor", &cgltf_pbr_specular_glossiness::glossiness_factor);

    // cgltf_material_clearcoat
    py::class_<cgltf_clearcoat>(m, "cgltf_clearcoat")
        .def(py::init<>())
        .def_readwrite("clearcoat_texture", &cgltf_clearcoat::clearcoat_texture)
        .def_readwrite("clearcoat_roughness_texture", &cgltf_clearcoat::clearcoat_roughness_texture)
        .def_readwrite("clearcoat_normal_texture", &cgltf_clearcoat::clearcoat_normal_texture)
        .def_readwrite("clearcoat_factor", &cgltf_clearcoat::clearcoat_factor)
        .def_readwrite("clearcoat_roughness_factor", &cgltf_clearcoat::clearcoat_roughness_factor);

    // cgltf_transmission
    py::class_<cgltf_transmission>(m, "cgltf_transmission")
        .def(py::init<>())
        .def_readwrite("transmission_texture", &cgltf_transmission::transmission_texture)
        .def_readwrite("transmission_factor", &cgltf_transmission::transmission_factor);

    // cgltf_ior
    py::class_<cgltf_ior>(m, "cgltf_ior")
        .def(py::init<>())
        .def_readwrite("ior", &cgltf_ior::ior);

    // cgltf_specular
    py::class_<cgltf_specular>(m, "cgltf_specular")
        .def(py::init<>())
        .def_readwrite("specular_texture", &cgltf_specular::specular_texture)
        .def_readwrite("specular_color_texture", &cgltf_specular::specular_color_texture)
        .def_property("specular_color_factor", [](const cgltf_specular &s) -> py::array_t<cgltf_float> {
            return py::array_t<cgltf_float>(sizeof(cgltf_specular::specular_color_factor)/sizeof(cgltf_float), s.specular_color_factor);
        }, [](cgltf_specular &s, py::array_t<cgltf_float> value) {
            auto r = value.unchecked<1>();
            for (size_t i = 0; i < sizeof(cgltf_specular::specular_color_factor)/sizeof(cgltf_float); ++i)
            {
                s.specular_color_factor[i] = r(i);
            }
        })
        .def_readwrite("specular_factor", &cgltf_specular::specular_factor);

    // cgltf_volume
    py::class_<cgltf_volume>(m, "cgltf_volume")
        .def(py::init<>())
        .def_readwrite("thickness_texture", &cgltf_volume::thickness_texture)
        .def_readwrite("thickness_factor", &cgltf_volume::thickness_factor)
        .def_property("attenuation_color", [](const cgltf_volume &v) -> py::array_t<cgltf_float> {
            return py::array_t<cgltf_float>(sizeof(cgltf_volume::attenuation_color)/sizeof(cgltf_float), v.attenuation_color);
        }, [](cgltf_volume &v, py::array_t<cgltf_float> value) {
            auto r = value.unchecked<1>();
            for (size_t i = 0; i < sizeof(cgltf_volume::attenuation_color)/sizeof(cgltf_float); ++i)
            {
                v.attenuation_color[i] = r(i);
            }
        })
        .def_readwrite("attenuation_distance", &cgltf_volume::attenuation_distance);

    // cgltf_sheen
    py::class_<cgltf_sheen>(m, "cgltf_sheen")
        .def(py::init<>())
        .def_readwrite("sheen_color_texture", &cgltf_sheen::sheen_color_texture)
        .def_property("sheen_color_factor", [](const cgltf_sheen &s) -> py::array_t<cgltf_float> {
            return py::array_t<cgltf_float>(sizeof(cgltf_sheen::sheen_color_factor)/sizeof(cgltf_float), s.sheen_color_factor);
        }, [](cgltf_sheen &s, py::array_t<cgltf_float> value) {
            auto r = value.unchecked<1>();
            for (size_t i = 0; i < sizeof(cgltf_sheen::sheen_color_factor)/sizeof(cgltf_float); ++i)
            {
                s.sheen_color_factor[i] = r(i);
            }
        })
        .def_readwrite("sheen_roughness_texture", &cgltf_sheen::sheen_roughness_texture)
        .def_readwrite("sheen_roughness_factor", &cgltf_sheen::sheen_roughness_factor);

    // cgltf_emissive_strength
    py::class_<cgltf_emissive_strength>(m, "cgltf_emissive_strength")
        .def(py::init<>())
        .def_readwrite("emissive_strength", &cgltf_emissive_strength::emissive_strength);

    // cgltf_iridescense
    py::class_<cgltf_iridescence>(m, "cgltf_iridescence")
        .def(py::init<>())
        .def_readwrite("iridescence_factor", &cgltf_iridescence::iridescence_factor)
        .def_readwrite("iridescence_texture", &cgltf_iridescence::iridescence_texture)
        .def_readwrite("iridescence_ior", &cgltf_iridescence::iridescence_ior)
        .def_readwrite("iridescence_thickness_min", &cgltf_iridescence::iridescence_thickness_min)
        .def_readwrite("iridescence_thickness_max", &cgltf_iridescence::iridescence_thickness_max)
        .def_readwrite("iridescence_thickness_texture", &cgltf_iridescence::iridescence_thickness_texture);

    // cgltf_anisotropy
    py::class_<cgltf_anisotropy>(m, "cgltf_anisotropy")
        .def(py::init<>())
        .def_readwrite("anisotropy_strength", &cgltf_anisotropy::anisotropy_strength)
        .def_readwrite("anisotropy_rotation", &cgltf_anisotropy::anisotropy_rotation)
        .def_readwrite("anisotropy_texture", &cgltf_anisotropy::anisotropy_texture);

    // cgltf_material
    py::class_<cgltf_material>(m, "cgltf_material")
        .def(py::init<>())
        .def_readwrite("name", &cgltf_material::name)
        .def_readwrite("has_pbr_metallic_roughness", &cgltf_material::has_pbr_metallic_roughness)
        .def_readwrite("has_pbr_specular_glossiness", &cgltf_material::has_pbr_specular_glossiness)
        .def_readwrite("has_clearcoat", &cgltf_material::has_clearcoat)
        .def_readwrite("has_transmission", &cgltf_material::has_transmission)
        .def_readwrite("has_volume", &cgltf_material::has_volume)
        .def_readwrite("has_ior", &cgltf_material::has_ior)
        .def_readwrite("has_specular", &cgltf_material::has_specular)
        .def_readwrite("has_sheen", &cgltf_material::has_sheen)
        .def_readwrite("has_emissive_strength", &cgltf_material::has_emissive_strength)
        .def_readwrite("has_iridescence", &cgltf_material::has_iridescence)
        .def_readwrite("has_anisotropy", &cgltf_material::has_anisotropy)
        .def_readwrite("pbr_metallic_roughness", &cgltf_material::pbr_metallic_roughness)
        .def_readwrite("pbr_specular_glossiness", &cgltf_material::pbr_specular_glossiness)
        .def_readwrite("clearcoat", &cgltf_material::clearcoat)
        .def_readwrite("ior", &cgltf_material::ior)
        .def_readwrite("specular", &cgltf_material::specular)
        .def_readwrite("sheen", &cgltf_material::sheen)
        .def_readwrite("transmission", &cgltf_material::transmission)
        .def_readwrite("volume", &cgltf_material::volume)
        .def_readwrite("emissive_strength", &cgltf_material::emissive_strength)
        .def_readwrite("iridescence", &cgltf_material::iridescence)
        .def_readwrite("anisotropy", &cgltf_material::anisotropy)
        .def_readwrite("normal_texture", &cgltf_material::normal_texture)
        .def_readwrite("occlusion_texture", &cgltf_material::occlusion_texture)
        .def_readwrite("emissive_texture", &cgltf_material::emissive_texture)
        .def_property("emissive_factor",
                      [](const cgltf_material &a) -> py::array_t<cgltf_float> {
                          return py::array_t<cgltf_float>(sizeof(cgltf_material::emissive_factor)/sizeof(cgltf_float), a.emissive_factor);
                      },
                      [](cgltf_material &a, py::array_t<cgltf_float> value) {
                          auto r = value.unchecked<1>();
                          for (size_t i = 0; i < sizeof(cgltf_material::emissive_factor)/sizeof(cgltf_float); ++i) {
                              a.emissive_factor[i] = r(i);
                          }
                      }
        )
        .def_readwrite("alpha_mode", &cgltf_material::alpha_mode)
        .def_readwrite("alpha_cutoff", &cgltf_material::alpha_cutoff)
        .def_readwrite("double_sided", &cgltf_material::double_sided)
        .def_readwrite("unlit", &cgltf_material::unlit)
        .def_readwrite("extras", &cgltf_material::extras)
        .def_readwrite("extensions_count", &cgltf_material::extensions_count)
        .def_property_readonly("extensions", [](const cgltf_material &a) -> py::list {
            py::list extensions_list;
            for (size_t i = 0; i < a.extensions_count; ++i) {
                extensions_list.append(py::cast(a.extensions[i]));
            }
            return extensions_list;
        });

    // cgltf_material_mapping
    py::class_<cgltf_material_mapping>(m, "cgltf_material_mapping")
        .def(py::init<>())
        .def_readwrite("variant", &cgltf_material_mapping::variant)
        .def_readwrite("material", &cgltf_material_mapping::material)
        .def_readwrite("extras", &cgltf_material_mapping::extras);

    // cgltf_morph_target
    py::class_<cgltf_morph_target>(m, "cgltf_morph_target")
        .def(py::init<>())
        .def_readwrite("attributes", &cgltf_morph_target::attributes)
        .def_readwrite("attributes_count", &cgltf_morph_target::attributes_count);

    // cgltf_draco_mesh_compression
    py::class_<cgltf_draco_mesh_compression>(m, "cgltf_draco_mesh_compression")
        .def(py::init<>())
        .def_readwrite("buffer_view", &cgltf_draco_mesh_compression::buffer_view)
        .def_readwrite("attributes", &cgltf_draco_mesh_compression::attributes)
        .def_readwrite("attributes_count", &cgltf_draco_mesh_compression::attributes_count);

    // cgltf_mesh_gpu_instancing
    py::class_<cgltf_mesh_gpu_instancing>(m, "cgltf_mesh_gpu_instancing")
        .def(py::init<>())
        .def_readwrite("attributes", &cgltf_mesh_gpu_instancing::attributes)
        .def_readwrite("attributes_count", &cgltf_mesh_gpu_instancing::attributes_count);

    // cgltf_primitive
    py::class_<cgltf_primitive>(m, "cgltf_primitive")
        .def(py::init<>())
        .def_readwrite("type", &cgltf_primitive::type)
        .def_readwrite("indices", &cgltf_primitive::indices)
        .def_readwrite("material", &cgltf_primitive::material)
        .def_readwrite("attributes_count", &cgltf_primitive::attributes_count)
        .def_property_readonly("attributes", [](const cgltf_primitive &a) -> py::list {
            py::list attributes_list;
            for (size_t i = 0; i < a.attributes_count; ++i) {
                attributes_list.append(py::cast(a.attributes[i]));
            }
            return attributes_list;
        })
        .def_readwrite("targets", &cgltf_primitive::targets)
        .def_readwrite("targets_count", &cgltf_primitive::targets_count)
        .def_readwrite("extras", &cgltf_primitive::extras)
        .def_readwrite("has_draco_mesh_compression", &cgltf_primitive::has_draco_mesh_compression)
        .def_readwrite("draco_mesh_compression", &cgltf_primitive::draco_mesh_compression)
        .def_readwrite("mappings", &cgltf_primitive::mappings)
        .def_readwrite("mappings_count", &cgltf_primitive::mappings_count)
        .def_readwrite("extensions_count", &cgltf_primitive::extensions_count)
        .def_property_readonly("extensions", [](const cgltf_primitive &a) -> py::list {
            py::list extensions_list;
            for (size_t i = 0; i < a.extensions_count; ++i) {
                extensions_list.append(py::cast(a.extensions[i]));
            }
            return extensions_list;
        });

        // cgltf_mesh
        py::class_<cgltf_mesh>(m, "cgltf_mesh")
            .def(py::init<>())
            .def_readwrite("name", &cgltf_mesh::name)
            .def_readonly("primitives_count", &cgltf_mesh::primitives_count)
            .def_property_readonly("primitives", [](const cgltf_mesh &a) -> py::list {
                py::list primitives_list;
                for (size_t i = 0; i < a.primitives_count; ++i) {
                    primitives_list.append(py::cast(a.primitives[i]));
                }
                return primitives_list;
            })

            .def_property_readonly("weights", [](const cgltf_mesh &mesh) -> py::array_t<cgltf_float> {
                return py::array_t<cgltf_float>(mesh.weights_count, mesh.weights);
            })
            .def_readonly("weights_count", &cgltf_mesh::weights_count)
            // .def_property_readonly("target_names", [](const cgltf_mesh &mesh) -> py::array_t<char*> {
            //     return py::array_t<char*>(mesh.target_names_count, mesh.target_names);
            // })
            .def_readonly("target_names_count", &cgltf_mesh::target_names_count)
            .def_readwrite("extras", &cgltf_mesh::extras)
            // .def_property_readonly("extensions", [](const cgltf_mesh &mesh) -> py::array_t<cgltf_extension*> {
            //     return py::array_t<cgltf_extension*>(mesh.extensions_count, mesh.extensions);
            // })
            // .def_property_readonly("extensions", [](const cgltf_mesh &mesh) {
            //     return std::vector<cgltf_extension*>(mesh.extensions, mesh.extensions + mesh.extensions_count);
            // })
            .def_readonly("extensions_count", &cgltf_mesh::extensions_count);



    // cgltf_skin
    py::class_<cgltf_skin>(m, "cgltf_skin")
        .def(py::init<>())
        .def_readwrite("name", &cgltf_skin::name)
        //.def_readwrite("joints", &cgltf_skin::joints)
        .def_readwrite("joints_count", &cgltf_skin::joints_count)
        .def_readwrite("skeleton", &cgltf_skin::skeleton)
        .def_readwrite("inverse_bind_matrices", &cgltf_skin::inverse_bind_matrices)
        .def_readwrite("extras", &cgltf_skin::extras)
        .def_readwrite("extensions_count", &cgltf_skin::extensions_count)
        .def_property_readonly("extensions", [](const cgltf_skin &a) -> py::list {
            py::list extensions_list;
            for (size_t i = 0; i < a.extensions_count; ++i) {
                extensions_list.append(py::cast(a.extensions[i]));
            }
            return extensions_list;
        });

    // cgltf_camera_perspective
    py::class_<cgltf_camera_perspective>(m, "cgltf_camera_perspective")
        .def(py::init<>())
        .def_readwrite("has_aspect_ratio", &cgltf_camera_perspective::has_aspect_ratio)
        .def_readwrite("aspect_ratio", &cgltf_camera_perspective::aspect_ratio)
        .def_readwrite("yfov", &cgltf_camera_perspective::yfov)
        .def_readwrite("has_zfar", &cgltf_camera_perspective::has_zfar)
        .def_readwrite("zfar", &cgltf_camera_perspective::zfar)
        .def_readwrite("znear", &cgltf_camera_perspective::znear)
        .def_readwrite("extras", &cgltf_camera_perspective::extras);

    // cgltf_camera_orthographic
    py::class_<cgltf_camera_orthographic>(m, "cgltf_camera_orthographic")
        .def(py::init<>())
        .def_readwrite("xmag", &cgltf_camera_orthographic::xmag)
        .def_readwrite("ymag", &cgltf_camera_orthographic::ymag)
        .def_readwrite("zfar", &cgltf_camera_orthographic::zfar)
        .def_readwrite("znear", &cgltf_camera_orthographic::znear)
        .def_readwrite("extras", &cgltf_camera_orthographic::extras);

    // cgltf_camera
    py::class_<cgltf_camera>(m, "cgltf_camera")
        .def(py::init<>())
        .def_readwrite("name", &cgltf_camera::name)
        .def_readwrite("type", &cgltf_camera::type)
        .def_readwrite("data", &cgltf_camera::data)
        .def_readwrite("extras", &cgltf_camera::extras)
        .def_readwrite("extensions_count", &cgltf_camera::extensions_count)
        .def_property_readonly("extensions", [](const cgltf_camera &a) -> py::list {
            py::list extensions_list;
            for (size_t i = 0; i < a.extensions_count; ++i) {
                extensions_list.append(py::cast(a.extensions[i]));
            }
            return extensions_list;
        });

    // cgltf_light
    py::class_<cgltf_light>(m, "cgltf_light")
        .def(py::init<>())
        .def_readwrite("name", &cgltf_light::name)
        .def_property("color",
                      [](const cgltf_light &l) -> py::array_t<cgltf_float>
                      { return py::array_t<cgltf_float>(sizeof(cgltf_light::color)/sizeof(cgltf_float), l.color); },
                      [](cgltf_light &l, py::array_t<cgltf_float> value)
                      {
                          auto r = value.unchecked<1>();
                          for (size_t i = 0; i < sizeof(cgltf_light::color)/sizeof(cgltf_float); ++i)
                          {
                              l.color[i] = r(i);
                          }
                      })
        .def_readwrite("intensity", &cgltf_light::intensity)
        .def_readwrite("type", &cgltf_light::type)
        .def_readwrite("range", &cgltf_light::range)
        .def_readwrite("spot_inner_cone_angle", &cgltf_light::spot_inner_cone_angle)
        .def_readwrite("spot_outer_cone_angle", &cgltf_light::spot_outer_cone_angle)
        .def_readwrite("extras", &cgltf_light::extras);

    // cgltf_node
    py::class_<cgltf_node>(m, "cgltf_node")
        .def(py::init<>())
        .def_readwrite("name", &cgltf_node::name)
        .def_readwrite("parent", &cgltf_node::parent, py::return_value_policy::reference)
        .def_property("children",
                       [](const cgltf_node &n) -> py::list {
                           py::list children_list;
                           for (size_t i = 0; i < n.children_count; ++i) {
                               children_list.append(py::cast(n.children[i], py::return_value_policy::reference));
                           }
                           return children_list;
                       }, [](cgltf_node &n, py::list value) {
                           n.children_count = value.size();
                           n.children = new cgltf_node*[n.children_count];
                           for (size_t i = 0; i < n.children_count; ++i) {
                               n.children[i] = value[i].cast<cgltf_node*>();
                           }
                       })
        .def("append_child", [](cgltf_node &n, cgltf_node* child) {
            cgltf_node** new_children_array = new cgltf_node*[n.children_count + 1];

            // Copy old children pointers
            for (size_t i = 0; i < n.children_count; ++i) {
                new_children_array[i] = n.children[i];
            }

            // Append the new child
            new_children_array[n.children_count] = child;

            // Clean up old array and update pointers
            delete[] n.children;
            n.children = new_children_array;
            n.children_count += 1;
        }, "Appends a child node to this node.")
        .def_readwrite("children_count", &cgltf_node::children_count)
        .def_readwrite("skin", &cgltf_node::skin)
        .def_readwrite("mesh", &cgltf_node::mesh)
        .def_readwrite("camera", &cgltf_node::camera)
        .def_readwrite("light", &cgltf_node::light)
        .def_readwrite("weights", &cgltf_node::weights)
        .def_readwrite("weights_count", &cgltf_node::weights_count)
        .def_readwrite("has_translation", &cgltf_node::has_translation)
        .def_readwrite("has_rotation", &cgltf_node::has_rotation)
        .def_readwrite("has_scale", &cgltf_node::has_scale)
        .def_readwrite("has_matrix", &cgltf_node::has_matrix)
        .def_readwrite("extras", &cgltf_node::extras)
        .def_readwrite("has_mesh_gpu_instancing", &cgltf_node::has_mesh_gpu_instancing)
        .def_readwrite("mesh_gpu_instancing", &cgltf_node::mesh_gpu_instancing)
        .def_readwrite("extensions_count", &cgltf_node::extensions_count)
        .def_readwrite("extensions", &cgltf_node::extensions)
        .def_property("translation",
                      [](const cgltf_node &n) -> py::array_t<cgltf_float> {
                          return py::array_t<cgltf_float>(sizeof(cgltf_node::translation)/sizeof(cgltf_float), n.translation);
                      },
                      [](cgltf_node &n, py::array_t<cgltf_float> value) {
                          auto r = value.unchecked<1>();
                          for (size_t i = 0; i < sizeof(cgltf_node::translation)/sizeof(cgltf_float); ++i) {
                              n.translation[i] = r(i);
                          }
                      })
        .def_property("rotation",
                      [](const cgltf_node &n) -> py::array_t<cgltf_float> {
                          return py::array_t<cgltf_float>(sizeof(cgltf_node::rotation)/sizeof(cgltf_float), n.rotation);
                      },
                      [](cgltf_node &n, py::array_t<cgltf_float> value) {
                          auto r = value.unchecked<1>();
                          for (size_t i = 0; i < sizeof(cgltf_node::rotation)/sizeof(cgltf_float); ++i) {
                              n.rotation[i] = r(i);
                          }
                      })
        .def_property("scale",
                      [](const cgltf_node &n) -> py::array_t<cgltf_float> {
                          return py::array_t<cgltf_float>(sizeof(cgltf_node::scale)/sizeof(cgltf_float), n.scale);
                      },
                      [](cgltf_node &n, py::array_t<cgltf_float> value) {
                          auto r = value.unchecked<1>();
                          for (size_t i = 0; i < sizeof(cgltf_node::scale)/sizeof(cgltf_float); ++i) {
                              n.scale[i] = r(i);
                          }
                      })
        .def_property("matrix",
                      [](const cgltf_node &n) -> py::array_t<cgltf_float> {
                          return py::array_t<cgltf_float>(sizeof(cgltf_node::matrix)/sizeof(cgltf_float), n.matrix);
                      },
                      [](cgltf_node &n, py::array_t<cgltf_float> value) {
                          auto r = value.unchecked<1>();
                          for (size_t i = 0; i < sizeof(cgltf_node::matrix)/sizeof(cgltf_float); ++i) {
                              n.matrix[i] = r(i);
                          }
                      });

    // cgltf_scene
    py::class_<cgltf_scene>(m, "cgltf_scene")
        .def(py::init<>())
        .def_readwrite("name", &cgltf_scene::name)
        .def_property("nodes",
            [](const cgltf_scene &s) -> py::list {
                py::list nodes_list;
                for (size_t i = 0; i < s.nodes_count; ++i) {
                    nodes_list.append(py::cast(s.nodes[i], py::return_value_policy::reference));
                }
                return nodes_list;
            }, [](cgltf_scene &s, py::list value) {
                s.nodes_count = value.size();
                s.nodes = new cgltf_node*[s.nodes_count];
                for (size_t i = 0; i < s.nodes_count; ++i) {
                    s.nodes[i] = value[i].cast<cgltf_node*>();
                }
            })
            .def("append_node", [](cgltf_scene &s, cgltf_node* new_node) {
                // Allocate new array of node pointers
                cgltf_node** new_nodes_array = new cgltf_node*[s.nodes_count + 1];

                // Copy old node pointers to the new array
                for (size_t i = 0; i < s.nodes_count; ++i) {
                    new_nodes_array[i] = s.nodes[i];
                }

                // Append the new node pointer to the end of the new array
                new_nodes_array[s.nodes_count] = new_node;

                // Clean up old array and update the nodes pointer in cgltf_scene
                delete[] s.nodes;
                s.nodes = new_nodes_array;

                // Update the node count
                s.nodes_count += 1;
            }, "Appends a new node to the nodes array.")
        .def_readwrite("nodes_count", &cgltf_scene::nodes_count)
        .def_readwrite("extras", &cgltf_scene::extras)
        .def_readwrite("extensions_count", &cgltf_scene::extensions_count)
        .def_property_readonly("extensions", [](const cgltf_scene &a) -> py::list {
            py::list extensions_list;
            for (size_t i = 0; i < a.extensions_count; ++i) {
                extensions_list.append(py::cast(a.extensions[i]));
            }
            return extensions_list;
        });

    // cgltf_animation_sampler
    py::class_<cgltf_animation_sampler>(m, "cgltf_animation_sampler")
        .def(py::init<>())
        .def_readwrite("input", &cgltf_animation_sampler::input)
        .def_readwrite("output", &cgltf_animation_sampler::output)
        .def_readwrite("interpolation", &cgltf_animation_sampler::interpolation)
        .def_readwrite("extras", &cgltf_animation_sampler::extras)
        .def_readwrite("extensions_count", &cgltf_animation_sampler::extensions_count)
        .def_property_readonly("extensions", [](const cgltf_animation_sampler &a) -> py::list {
            py::list extensions_list;
            for (size_t i = 0; i < a.extensions_count; ++i) {
                extensions_list.append(py::cast(a.extensions[i]));
            }
            return extensions_list;
        });

    // cgltf_animation_channel
    py::class_<cgltf_animation_channel>(m, "cgltf_animation_channel")
        .def(py::init<>())
        .def_readwrite("sampler", &cgltf_animation_channel::sampler)
        .def_readwrite("target_node", &cgltf_animation_channel::target_node)
        .def_readwrite("target_path", &cgltf_animation_channel::target_path)
        .def_readwrite("extras", &cgltf_animation_channel::extras)
        .def_readwrite("extensions_count", &cgltf_animation_channel::extensions_count)
        .def_readwrite("extensions", &cgltf_animation_channel::extensions);

    // cgltf_animation
    py::class_<cgltf_animation>(m, "cgltf_animation")
        .def(py::init<>())
        .def_readwrite("name", &cgltf_animation::name)
        .def_readwrite("samplers", &cgltf_animation::samplers)
        .def_readwrite("samplers_count", &cgltf_animation::samplers_count)
        .def_readwrite("channels", &cgltf_animation::channels)
        .def_readwrite("channels_count", &cgltf_animation::channels_count)
        .def_readwrite("extras", &cgltf_animation::extras)
        .def_readwrite("extensions_count", &cgltf_animation::extensions_count)
        .def_readwrite("extensions", &cgltf_animation::extensions);

    // cgltf_material_variant
    py::class_<cgltf_material_variant>(m, "cgltf_material_variant")
        .def(py::init<>())
        .def_readwrite("name", &cgltf_material_variant::name)
        .def_readwrite("extras", &cgltf_material_variant::extras);

    // cgltf_asset
    py::class_<cgltf_asset>(m, "cgltf_asset")
        .def(py::init<>())
        .def_readwrite("copyright", &cgltf_asset::copyright)
        .def_property("generator",
                      [](const cgltf_asset& asset) -> std::string {
                          return asset.generator ? std::string(asset.generator) : "";
                      },
                      [](cgltf_asset& asset, const std::string& value) {
                          asset.generator = strdup(value.c_str());
                      })
        .def_property("version",
                      [](const cgltf_asset& asset) -> std::string {
                          return asset.version ? std::string(asset.version) : "";
                      },
                      [](cgltf_asset& asset, const std::string& value) {
                          asset.version = strdup(value.c_str());
                      })
        .def_readwrite("min_version", &cgltf_asset::min_version)
        .def_readwrite("extras", &cgltf_asset::extras)
        .def_readwrite("extensions_count", &cgltf_asset::extensions_count)
        .def_readwrite("extensions", &cgltf_asset::extensions);


    py::class_<cgltf_data>(m, "cgltf_data")
        .def(py::init<>())
        .def_readwrite("file_type", &cgltf_data::file_type)
        .def_readwrite("file_data", &cgltf_data::file_data)
        .def_readwrite("asset", &cgltf_data::asset)
        .def_readwrite("meshes_count", &cgltf_data::meshes_count)
        .def_property_readonly("meshes", [](const cgltf_data &a) {
            py::list meshes_list(a.meshes_count);
            for (size_t i = 0; i < a.meshes_count; ++i) {
                meshes_list[i] = py::cast(a.meshes[i]);
            }
            return meshes_list;
        })
        .def_readwrite("materials_count", &cgltf_data::materials_count)
        .def_property_readonly("materials", [](const cgltf_data &a) -> py::list {
            py::list materials_list;
            for (size_t i = 0; i < a.materials_count; ++i) {
                materials_list.append(py::cast(a.materials[i]));
            }
            return materials_list;
        })
        .def_readwrite("accessors_count", &cgltf_data::accessors_count)
        .def_property_readonly("accessors", [](const cgltf_data &a) -> py::list {
            py::list accessors_list;
            for (size_t i = 0; i < a.accessors_count; ++i) {
                accessors_list.append(py::cast(a.accessors[i]));
            }
            return accessors_list;
        })
        .def_readwrite("buffer_views_count", &cgltf_data::buffer_views_count)
        .def_property_readonly("buffer_views", [](const cgltf_data &a) -> py::list {
            py::list buffer_views_list;
            for (size_t i = 0; i < a.buffer_views_count; ++i) {
                buffer_views_list.append(py::cast(a.buffer_views[i]));
            }
            return buffer_views_list;
        })
        .def_readwrite("buffers_count", &cgltf_data::buffers_count)
        .def_property_readonly("buffers", [](const cgltf_data &a) -> py::list {
            py::list buffers_list;
            for (size_t i = 0; i < a.buffers_count; ++i) {
                buffers_list.append(py::cast(a.buffers[i]));
            }
            return buffers_list;
        })
        .def_readwrite("images_count", &cgltf_data::images_count)
        .def_property_readonly("images", [](const cgltf_data &a) -> py::list {
            py::list images_list;
            for (size_t i = 0; i < a.images_count; ++i) {
                images_list.append(py::cast(a.images[i]));
            }
            return images_list;
        })
        .def_readwrite("textures_count", &cgltf_data::textures_count)
        .def_property_readonly("textures", [](const cgltf_data &a) -> py::list {
            py::list textures_list;
            for (size_t i = 0; i < a.textures_count; ++i) {
                textures_list.append(py::cast(a.textures[i]));
            }
            return textures_list;
        })
        .def_readwrite("samplers_count", &cgltf_data::samplers_count)
        .def_property_readonly("samplers", [](const cgltf_data &a) -> py::list {
            py::list samplers_list;
            for (size_t i = 0; i < a.samplers_count; ++i) {
                samplers_list.append(py::cast(a.samplers[i]));
            }
            return samplers_list;
        })
        .def_readwrite("skins_count", &cgltf_data::skins_count)
        .def_property_readonly("skins", [](const cgltf_data &a) -> py::list {
            py::list skins_list;
            for (size_t i = 0; i < a.skins_count; ++i) {
                skins_list.append(py::cast(a.skins[i]));
            }
            return skins_list;
        })
        .def_readwrite("cameras_count", &cgltf_data::cameras_count)
        .def_property_readonly("cameras", [](const cgltf_data &a) -> py::list {
            py::list cameras_list;
            for (size_t i = 0; i < a.cameras_count; ++i) {
                cameras_list.append(py::cast(a.cameras[i]));
            }
            return cameras_list;
        })
        .def_readwrite("lights_count", &cgltf_data::lights_count)
        .def_property_readonly("lights", [](const cgltf_data &a) -> py::list {
            py::list lights_list;
            for (size_t i = 0; i < a.lights_count; ++i) {
                lights_list.append(py::cast(a.lights[i]));
            }
            return lights_list;
        })
        .def_readwrite("nodes_count", &cgltf_data::nodes_count)
        .def_property_readonly("nodes", [](const cgltf_data &a) -> py::list {
            py::list nodes_list;
            for (size_t i = 0; i < a.nodes_count; ++i) {
                nodes_list.append(py::cast(a.nodes[i], py::return_value_policy::reference));
            }
            return nodes_list;
        })
        .def("append_node", [](cgltf_data &data, const cgltf_node& new_node) {
            // Increase the nodes_count
            size_t new_count = data.nodes_count + 1;

            // Reallocate the memory for the new size
            cgltf_node* new_nodes = (cgltf_node*) realloc(data.nodes, new_count * sizeof(cgltf_node));

            if (!new_nodes) {
                throw std::runtime_error("Failed to allocate memory for new node.");
            }

            // Update the pointer (since realloc might move the memory)
            data.nodes = new_nodes;

            // Copy the new node data to the last position (this assumes shallow copy is okay)
            data.nodes[data.nodes_count] = new_node;

            // Update the count
            data.nodes_count = new_count;
        })
        .def_readwrite("scenes_count", &cgltf_data::scenes_count)
        .def_property_readonly("scenes", [](const cgltf_data &a) -> py::list {
            py::list scenes_list;
            for (size_t i = 0; i < a.scenes_count; ++i) {
                scenes_list.append(py::cast(a.scenes[i]));
            }
            return scenes_list;
        })
        .def("append_scene", [](cgltf_data &a, cgltf_scene* new_scene) {
            // Allocate new array of scene pointers
            cgltf_scene** new_scenes_array = new cgltf_scene*[a.scenes_count + 1];

            // Copy old scene pointers to the new array
            for (size_t i = 0; i < a.scenes_count; ++i) {
                new_scenes_array[i] = &a.scenes[i];
            }

            // Append the new scene pointer to the end of the new array
            new_scenes_array[a.scenes_count] = new_scene;

            // Clean up old array and update the scenes pointer in cgltf_data
            delete[] a.scenes;
            a.scenes = *new_scenes_array;

            // Update the scene count
            a.scenes_count += 1;
        }, "Appends a new scene to the scenes array.")
        .def_readwrite("scene", &cgltf_data::scene)
        .def_readwrite("animations_count", &cgltf_data::animations_count)
        .def_property_readonly("animations", [](const cgltf_data &a) -> py::list {
            py::list animations_list;
            for (size_t i = 0; i < a.animations_count; ++i) {
                animations_list.append(py::cast(a.animations[i]));
            }
            return animations_list;
        })
        .def_readwrite("variants_count", &cgltf_data::variants_count)
        .def_property_readonly("variants", [](const cgltf_data &a) -> py::list {
            py::list variants_list;
            for (size_t i = 0; i < a.variants_count; ++i) {
                variants_list.append(py::cast(a.variants[i]));
            }
            return variants_list;
        })
        .def_readwrite("extras", &cgltf_data::extras)
        .def_readwrite("data_extensions_count", &cgltf_data::data_extensions_count)
        .def_property_readonly("data_extensions", [](const cgltf_data &a) -> py::list {
            py::list data_extensions_list;
            for (size_t i = 0; i < a.data_extensions_count; ++i) {
                data_extensions_list.append(py::cast(a.data_extensions[i]));
            }
            return data_extensions_list;
        })
        //.def_readwrite("extensions_used", &cgltf_data::extensions_used)
        .def_readwrite("extensions_used_count", &cgltf_data::extensions_used_count)
        //.def_readwrite("extensions_required", &cgltf_data::extensions_required)
        .def_readwrite("extensions_required_count", &cgltf_data::extensions_required_count)
        .def_readwrite("json_size", &cgltf_data::json_size)
        .def_property_readonly("json", [](const cgltf_data& self) {
            return py::str(self.json, self.json_size);
        })
        .def_readwrite("bin_size", &cgltf_data::bin_size)
        .def_property_readonly("bin", [](const cgltf_data& self) {
            return py::bytes(static_cast<const char*>(self.bin), self.bin_size);
        })
        .def_readwrite("memory", &cgltf_data::memory)
        .def_readwrite("file", &cgltf_data::file);


    // cgltf_parse
    m.def("cgltf_parse", [](const cgltf_options& options, py::bytes py_data) -> std::pair<cgltf_result, py::object>
        {
            const char* data_ptr = PYBIND11_BYTES_AS_STRING(py_data.ptr());
            cgltf_size size = PYBIND11_BYTES_SIZE(py_data.ptr());
            cgltf_data* out_data = nullptr;

            cgltf_result result = cgltf_parse(&options, static_cast<const void*>(data_ptr), size, &out_data);
            if (result == cgltf_result_success && out_data != nullptr)
                return { result, py::cast(out_data) };
            else
                return { result, py::none() };
        },
        "Parse gltf data from a buffer", py::arg("options"), py::arg("data")
    );

    // cgltf_parse_file
    m.def("cgltf_parse_file", [](const cgltf_options& options, const std::string& path) -> py::tuple
        {
            cgltf_data* out_data = nullptr;
            cgltf_result result = cgltf_parse_file(&options, path.c_str(), &out_data);
            if (result == cgltf_result_success && out_data != nullptr)
                return py::make_tuple(result, py::cast(out_data));
            else
                return py::make_tuple(result, py::none());
        },
        "Parse gltf file", py::arg("options"), py::arg("path")
    );

    // cgltf_load_buffers
    m.def("cgltf_load_buffers",
        [](const cgltf_options& options, cgltf_data* data, const std::string& gltf_path)
        {
            return cgltf_load_buffers(&options, data, gltf_path.c_str());
        },
        "Load buffers", py::arg("options"), py::arg("data"), py::arg("gltf_path")
    );

    // cgltf_validate
    m.def("cgltf_validate",
        []( cgltf_data* data)
        {
            return cgltf_validate(data);
        },
        "Validate data", py::arg("data")
    );

    // cgltf_free
    m.def("cgltf_free",
        [](cgltf_data* data)
        {
            cgltf_free(data);
        },
        "Free data", py::arg("data")
    );

    // OOP wrapper
    py::class_<gltf>(m, "gltf")
        .def(py::init<>())
        .def("load", &gltf::load)
        .def("save", &gltf::save)
        .def("release", &gltf::release)
        .def("error", &gltf::error)
        .def_property("data",
            [](const gltf &g) -> py::object {
                cgltf_data* data_ptr = g.data();
                if (data_ptr != nullptr)
                    return py::cast(data_ptr);
                else
                    return py::none();
            },
            [](gltf &g, py::object value) {
                if (value.is_none())
                    g.setData(nullptr);
                else
                    g.setData(value.cast<cgltf_data*>());
            }
        );
}

}; // end namespace

