set(TARGET IntermediateProgram)

set(SOURCE_FILES
    Include/FileReader.cpp
    Include/FileReader.hpp
    Include/FileWriter.cpp
    Include/FileWriter.hpp
    Include/SafeQueue.hpp)

add_library(${TARGET} INTERFACE)
target_sources(${TARGET} INTERFACE ${SOURCE_FILES})
target_include_directories(${TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Include)

add_subdirectory(1_ReadWriteFile)
add_subdirectory(2_ReadWriteShMem)
add_subdirectory(3_ExceptionHandling)
add_subdirectory(4_Networking)
add_subdirectory(Network.Test)
add_subdirectory(ProcessesExecutorTests)
