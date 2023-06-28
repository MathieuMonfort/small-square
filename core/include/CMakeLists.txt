
add_library(glad glad/glad.c)
add_library(stb_image stb_image/stb_image.h)


SET_TARGET_PROPERTIES(stb_image PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(stb_image PUBLIC "stb_image")



