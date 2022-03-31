set(TARGET WidgetsAbstract)

set(SOURCE_FILES
        ButtonAbstract.hpp
        CheckBoxAbstract.hpp
        FieldAbstract.hpp)

add_library(${TARGET} INTERFACE)
target_sources(${TARGET} INTERFACE ${SOURCE_FILES})
target_include_directories(${TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/WidgetsAbstract)
