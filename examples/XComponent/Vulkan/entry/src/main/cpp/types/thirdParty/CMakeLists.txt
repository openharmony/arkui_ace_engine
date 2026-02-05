cmake_minimum_required(VERSION 3.5.0 FATAL_ERROR)
cmake_policy(VERSION 3.5.0)

set(GLM_VERSION "0.9.9")
project(glm VERSION ${GLM_VERSION} LANGUAGES CXX)

set (LIBRARY_OUTPUT_PATH ${DYNAMIC_LIB_PATH})

add_subdirectory(glm/glm)
add_library(glm::glm ALIAS glm)
