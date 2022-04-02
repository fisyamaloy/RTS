set(TARGET Factory)

set(SOURCE_FILES
        LinuxWidgetsFactory.hpp
        WidgetsFactoryAbstract.hpp
        WindowsWidgetsFactory.hpp
        WidgetsAbstract/ButtonAbstract.hpp
        WidgetsAbstract/CheckBoxAbstract.hpp
        WidgetsAbstract/FieldAbstract.hpp)

add_library(${TARGET} INTERFACE)
target_sources(${TARGET} INTERFACE ${SOURCE_FILES})
target_include_directories(${TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/WidgetsAbstract)

add_subdirectory(LinuxWidgets)
add_subdirectory(WindowsWidgets)
add_subdirectory(WidgetsAbstract)
