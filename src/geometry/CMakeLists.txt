# ${PROJECT_SOURCE_DIR}/include/scene/geometry

add_library(geometry STATIC 
            box.cpp 
            mesh.cpp 
            meshTriangle.cpp 
            plane.cpp 
            rectangle.cpp 
            sphere.cpp 
            triangle.cpp 
            compositeShape.cpp 
            mengerSponge.cpp) 

target_link_libraries(geometry materials)