cmake_minimum_required(VERSION 3.5)
project(Ray_Tracer)

ADD_DEFINITIONS( -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\" )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Ofast -fpermissive -Wall")

add_executable(render main.cpp)

add_subdirectory(src)

target_link_libraries(render
                      container
                      geometry
                      lighting
                      scene
                      sensors
                      utils
                      pthread)
