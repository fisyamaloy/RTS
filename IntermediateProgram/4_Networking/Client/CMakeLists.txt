add_subdirectory(Client.CLI)
add_subdirectory(Client.Core)

set(TARGET Client)

add_library(${TARGET} INTERFACE)
