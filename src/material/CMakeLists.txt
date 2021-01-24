add_library(materials STATIC material.cpp checkerBoard.cpp crossHatchModifier.cpp simpleTexture.cpp)
target_link_directories(materials PUBLIC .)