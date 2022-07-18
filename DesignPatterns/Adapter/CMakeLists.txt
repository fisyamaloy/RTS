set(TARGET Adapter)

set(SOURCE_FILES
	Adapter.hpp)

add_library(${TARGET} INTERFACE)
target_sources(${TARGET} INTERFACE ${SOURCE_FILES})
