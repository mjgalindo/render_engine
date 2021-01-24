add_library(container STATIC containers/coloredLightRay.cpp 
                             containers/image.cpp
                             containers/kdtree.cpp
                             containers/lightRay.cpp
                             containers/photon.cpp
                             containers/point.cpp
                             containers/vect.cpp)
target_include_directories(container PUBLIC containers)


add_library(geometry STATIC  geometry/box.cpp 
                             geometry/mesh.cpp 
                             geometry/meshTriangle.cpp 
                             geometry/plane.cpp 
                             geometry/rectangle.cpp 
                             geometry/sphere.cpp 
                             geometry/triangle.cpp 
                             geometry/compositeShape.cpp 
                             geometry/mengerSponge.cpp)
target_include_directories(geometry PUBLIC geometry)
                    

add_library(lighting STATIC lighting/pointLight.cpp 
                            lighting/simpleAreaLight.cpp)
target_include_directories(lighting PUBLIC lighting)
                


add_library(material STATIC material/material.cpp 
                            material/checkerBoard.cpp 
                            material/crossHatchModifier.cpp 
                            material/simpleTexture.cpp)
target_include_directories(material PUBLIC material)
                    

add_library(sensors STATIC sensors/camera.cpp 
                           sensors/pinhole.cpp)
target_include_directories(sensors PUBLIC sensors)
                


add_library(scene STATIC scene/scene.cpp 
                         scene/participatingMedia.cpp)
target_include_directories(scene PUBLIC scene)
                

add_library(utils STATIC utils/intersections.cpp
                         utils/poseTransformationMatrix.cpp
                         utils/matrix.cpp
                         utils/transformationMatrix.cpp
                         utils/visibleNormal.cpp)
target_include_directories(utils PUBLIC utils)

target_link_libraries(container PRIVATE geometry utils)
target_link_libraries(geometry PRIVATE material utils)
target_link_libraries(lighting PRIVATE utils)
target_link_libraries(material PRIVATE utils)
target_link_libraries(sensors PRIVATE container)
target_link_libraries(scene PRIVATE geometry container)
target_link_libraries(utils PRIVATE container)
