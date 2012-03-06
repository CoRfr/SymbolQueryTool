cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME SymbolQueryTool)

project(${PROJECT_NAME})

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${PROJECT_SOURCE_DIR}/cmake_modules
)


find_package(LibXml2 REQUIRED)
find_package(LibDw REQUIRED)
 
include_directories(
        ${LIBXML2_INCLUDE_DIR}
        ${LIBDW_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME}
        ${LIBXML2_LIBRARIES}
        ${LIBDW_LIBRARIES}
)
