

#define CGLTF_IMPLEMENTATION
#define CGLTF_WRITE_IMPLEMENTATION
#include <cgltf_write.h>

#include "slgltf.h"

namespace SLGLTF_NS
{

gltf::gltf()
{
    m_data = nullptr;
    memset(&m_options, 0, sizeof(m_options));
}

gltf::~gltf()
{
    release();
}

void gltf::release()
{
    if (m_data)
        cgltf_free(m_data), m_data = nullptr;

    memset(&m_options, 0, sizeof(m_options));
}

bool gltf::load(const std::string &filename)
{
    release();

    cgltf_result result = cgltf_parse_file(&m_options, filename.c_str(), &m_data);
    if (result != cgltf_result_success)
    {
        release();
        m_sError = "Failed to parse gltf file";
        return false;
    }

    result = cgltf_load_buffers(&m_options, m_data, filename.c_str());
    if (result != cgltf_result_success)
    {
        release();
        m_sError = "Failed to load gltf buffers";
        return false;
    }

    result = cgltf_validate(m_data);
    if (result != cgltf_result_success)
    {
        release();
        m_sError = "Failed to validate gltf data";
        return false;
    }

    return true;
}

bool gltf::save(const std::string &filename)
{
    if (!m_data)
    {
        m_sError = "No gltf data to save";
        return false;
    }

    cgltf_result result = cgltf_write_file(&m_options, filename.c_str(), m_data);
    if (result != cgltf_result_success)
    {
        m_sError = "Failed to save gltf file";
        return false;
    }

    return true;
}

}; // end namespace

