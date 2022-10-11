set(TARGET 2_ReadWriteShMem)

set(SOURCE_FILES
   main.cpp
   CopyingTool.hpp
   CopyingTool.cpp)

find_package(Threads)
add_executable(${TARGET} ${SOURCE_FILES})

target_link_libraries(${TARGET} PUBLIC ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${TARGET} PUBLIC IntermediateProgram)
target_link_libraries(${TARGET} PUBLIC CONAN_PKG::boost)
target_link_libraries(${TARGET} PUBLIC CONAN_PKG::gtest)
