cmake_minimum_required(VERSION 3.0.0)
project(obj_raytracer VERSION 0.1.0)

include(CTest)
enable_testing()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(GLM REQUIRED)
message(STATUS "GLM at ${GLM_INCLUDE_DIR}")
include_directories(${GLM_INCLUDE_DIRS})
set(EXTERNAL_LIBRARIES ${EXTERNAL_LIBRARIES} ${GLM_LIBRARIES})
if (UNIX)
	set(EXTERNAL_LIBRARIES ${EXTERNAL_LIBRARIES} pthread)
endif()


set(SOURCE_FILES
    src/shape.cpp
    src/scene.cpp
    src/sphere.cpp
    src/math.cpp
    src/main.cpp)

add_executable(obj_raytracer ${SOURCE_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
