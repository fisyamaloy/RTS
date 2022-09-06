set(TARGET 1_ReadWriteFile)

set(SOURCE_FILES
   main.cpp
   CopyingTool.cpp
   CopyingTool.hpp
   FileReader.hpp
   FileWriter.hpp
   SafeQueue.hpp)

add_compile_options(-pthread)

add_executable(${TARGET} ${SOURCE_FILES})

target_link_libraries(${TARGET} INTERFACE Utility.Public CONAN_PKG::boost)
