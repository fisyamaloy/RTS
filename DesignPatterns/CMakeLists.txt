set(TARGET DesignPatterns)

set(SOURCE_FILES
   main.cpp
   Factory/WidgetsFactoryAbstract.hpp
   Factory/LinuxWidgetsFactory.hpp
   Factory/WindowsWidgetsFactory.hpp)

add_subdirectory(Factory)
add_subdirectory(Builder)

add_executable(${TARGET} ${SOURCE_FILES})
