set(TARGET 1_ReadWriteFile)

set(SOURCE_FILES
   main.cpp
   CopyingTool.cpp
   CopyingTool.hpp
   FileReader.hpp
   FileWriter.hpp
   SafeQueue.hpp)

add_executable(${TARGET} ${SOURCE_FILES})
