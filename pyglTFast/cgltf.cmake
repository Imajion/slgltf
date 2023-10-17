
find_package(cgltf QUIET)

if(cgltf_FOUND)

    message(STATUS "Found cgltf ${cgltf_VERSION}")
    include_directories("${cgltf_INCLUDE_DIRS}")
    link_directories("${cgltf_LIBRARIES}")

else()

    message(STATUS "Fetch cgltf")
    include(FetchContent)
    FetchContent_Declare(
        cgltf
        GIT_REPOSITORY      https://github.com/ru-imajion/cgltf
        GIT_TAG             master
        GIT_PROGRESS        TRUE
    )
    FetchContent_MakeAvailable(cgltf)

    if(NOT cgltf_POPULATED)
        message(FATAL_ERROR "cgltf not found")
    endif()

    include_directories(${cgltf_SOURCE_DIR})

endif()
