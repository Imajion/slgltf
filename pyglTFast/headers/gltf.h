#pragma once

namespace SLGLTF_NS
{

class gltf
{
public:

    /// Constructor
    gltf();

    /// Destructor
    ~gltf();

    /// Load gltf file
    bool load(const std::string &filename);

    /// Save gltf file
    bool save(const std::string &filename);

    /// Release gltf data
    void release();

    /// Get error string
    const std::string& error() const { return m_sError; }

    /// Get gltf data
    cgltf_data* data() const { return m_data; }

    /// Set gltf data
    void setData(cgltf_data* data) { m_data = data; }  // This is the setter

    /// Get gltf options
    cgltf_options* options() { return &m_options; }

private:

    /// gltf options
    cgltf_options           m_options;

    /// gltf data
    cgltf_data              *m_data;

    /// Error string
    std::string             m_sError;

};

} // namespace SLGLTF_NS
