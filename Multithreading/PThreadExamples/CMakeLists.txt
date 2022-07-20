set(TARGET PThreadExamples)

set(SOURCE_FILES
   main.cpp
   PThreadExamples.hpp)

add_executable(${TARGET} ${SOURCE_FILES})

IF (WIN32)
	target_link_libraries(${TARGET} PRIVATE ${EXTRA_LIBS} CONAN_PKG::pthreads4w)
ENDIF()
