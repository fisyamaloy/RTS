set(TARGET Widgets.Static)

set(SOURCE_FILES
        Include/WidgetsAbstract/ButtonAbstract.hpp
        Include/WidgetsAbstract/CheckBoxAbstract.hpp
        Include/WidgetsAbstract/FieldAbstract.hpp)

add_library(${TARGET} INTERFACE)
target_sources(${TARGET} INTERFACE ${SOURCE_FILES})
target_include_directories(${TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Include)
