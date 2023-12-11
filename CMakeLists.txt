
add_library(mcp2517_driver STATIC)
target_sources(mcp2517_driver PUBLIC communication_base.h MCP2517.h MCP2517.cpp SPI_RP2040.h SPI_RP2040.cpp)
