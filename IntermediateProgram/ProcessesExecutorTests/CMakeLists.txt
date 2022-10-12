set(TARGET ProcessesExecutorTests)

set(SOURCE_FILES
   main.cpp)

add_executable(${TARGET} ${SOURCE_FILES})
target_link_libraries(${TARGET} PUBLIC IntermediateProgram) 
target_link_libraries(${TARGET} PUBLIC CONAN_PKG::boost)
target_link_libraries(${TARGET} PUBLIC CONAN_PKG::gtest)