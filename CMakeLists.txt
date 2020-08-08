cmake_minimum_required(VERSION 3.0.0)
project(obj_raytracer VERSION 0.1.0)

include(CTest)
enable_testing()

set(SOURCE_FILES
    main.cpp)

add_executable(obj_raytracer ${SOURCE_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
