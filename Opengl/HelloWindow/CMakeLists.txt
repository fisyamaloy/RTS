set(TARGET HelloWindow)

file(GLOB SRCS CONFIGURE_DEPENDS *.cpp *.h *.hpp *.vert *.frag *.glsl *.geom)

if (NOT MSVC)
	add_compile_options(-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl)
endif()

add_executable(${TARGET} ${SRCS} ${PROJECT_SOURCE_DIR}/conanfile.txt)
conan_target_link_libraries(${TARGET})
target_precompile_headers(${TARGET} PRIVATE ${PROJECT_SOURCE_DIR}/Opengl/Include/pch.h)
