set(TARGET 1_ReadWriteFile)

set(SOURCE_FILES
   main.cpp)

find_package(Threads)
add_executable(${TARGET} ${SOURCE_FILES})

target_link_libraries(${TARGET} PUBLIC ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${TARGET} PRIVATE CONAN_PKG::gtest)
target_link_libraries(${TARGET} PUBLIC IntermediateProgram)
