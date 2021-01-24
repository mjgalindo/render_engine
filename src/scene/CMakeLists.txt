add_subdirectory(geometry)
add_subdirectory(lighting)
add_subdirectory(materials)
add_subdirectory(sensors)

add_library(scene STATIC scene.cpp participatingMedia.cpp)