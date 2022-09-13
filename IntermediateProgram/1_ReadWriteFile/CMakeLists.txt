set(TARGET 1_ReadWriteFile)

set(SOURCE_FILES
   main.cpp)

add_executable(${TARGET} ${SOURCE_FILES})

target_link_libraries(${TARGET} PRIVATE CONAN_PKG::gtest)

target_link_libraries(${TARGET} PUBLIC IntermediateProgram)
