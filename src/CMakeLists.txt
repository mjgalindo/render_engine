add_library(container STATIC coloredLightRay.cpp 
                             image.cpp
                             kdtree.cpp
                             lightRay.cpp
                             photon.cpp
                             point.cpp
                             vect.cpp)
target_include_directories(container PUBLIC .)

add_library(geometry STATIC  box.cpp 
                             mesh.cpp 
                             meshTriangle.cpp 
                             plane.cpp 
                             rectangle.cpp 
                             sphere.cpp 
                             triangle.cpp 
                             compositeShape.cpp 
                             mengerSponge.cpp)
target_include_directories(geometry PUBLIC .)

add_library(lighting STATIC pointLight.cpp 
                            simpleAreaLight.cpp)
target_include_directories(lighting PUBLIC .)

add_library(material STATIC material.cpp 
                            checkerBoard.cpp 
                            crossHatchModifier.cpp 
                            simpleTexture.cpp)
target_include_directories(material PUBLIC .)

add_library(sensors STATIC camera.cpp 
                           pinhole.cpp)
target_include_directories(sensors PUBLIC .)

add_library(scene STATIC scene.cpp 
                         participatingMedia.cpp)
target_include_directories(scene PUBLIC .)

add_library(utils STATIC intersections.cpp
                         poseTransformationMatrix.cpp
                         matrix.cpp
                         transformationMatrix.cpp
                         visibleNormal.cpp)
target_include_directories(utils PUBLIC .)

target_link_libraries(container PRIVATE geometry utils)
target_link_libraries(geometry PRIVATE material utils)
target_link_libraries(lighting PRIVATE utils)
target_link_libraries(material PRIVATE utils)
target_link_libraries(sensors PRIVATE container)
target_link_libraries(scene PRIVATE geometry container)
target_link_libraries(utils PRIVATE container)
