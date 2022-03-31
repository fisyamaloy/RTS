set(TARGET WidgetsFactoryAbstract)

set(SOURCE_FILES
   main.cpp
   Factory/WidgetsFactoryAbstract.hpp
   Factory/LinuxWidgetsFactory.hpp
   Factory/WindowsWidgetsFactory.hpp)

add_executable(${TARGET} ${SOURCE_FILES})
