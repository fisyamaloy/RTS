set(TARGET WidgetsAbstract)

set(SOURCE_FILES
        ButtonAbstract.hpp
        CheckBoxAbstract.hpp
        FieldAbstract.hpp)

add_library(${TARGET} STATIC ${SOURCE_FILES})

set_target_properties(${TARGET} PROPERTIES
    LINKER_LANGUAGE CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})