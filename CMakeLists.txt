
add_library(mcp2517_driver INTERFACE)
target_sources(mcp2517_driver PUBLIC MCP2517.cpp SPI_RP2040.cpp)
target_link_libraries(mcp2517_driver INTERFACE pico_stdlib hardware_spi hardware_dma)
target_include_directories(mcp2517_driver INTERFACE ${CMAKE_CURRENT_LIST_DIR})
