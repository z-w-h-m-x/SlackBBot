include(ExternalProject)

ExternalProject_Add(json
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)