set(TARGET Builder)

set(SOURCE_FILES
	BlogPost.hpp
	BlogPostBuilderCRTP.hpp
	BlogPostBuilder.hpp)

add_library(${TARGET} INTERFACE)
target_sources(${TARGET} INTERFACE ${SOURCE_FILES})
