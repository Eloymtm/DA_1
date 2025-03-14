cmake_minimum_required(VERSION 3.10)
project(G03_1)

set(CMAKE_CXX_STANDARD 17)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)

add_executable(G03_1 main.cpp
        classes/Parser.h
        classes/Parser.cpp
        classes/City.cpp
        classes/City.h
        classes/Reservoir.cpp
        classes/Reservoir.h
        classes/Station.cpp
        classes/Station.h
        classes/Graph.h
        classes/Dataset.cpp
        classes/Dataset.h
        classes/Menu.cpp
        classes/Menu.h
)