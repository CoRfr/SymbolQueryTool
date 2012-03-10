cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME SymbolQueryTool)
set(EXEC_NAME symbol-query)

project(${PROJECT_NAME})

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${PROJECT_SOURCE_DIR}/cmake_modules
)

find_package(LibDw REQUIRED)
 
include_directories(
        ${LIBDW_INCLUDE_DIRS}
)

add_executable(${EXEC_NAME}
    main.cpp
    DwarfFile.cpp
    DwarfCu.cpp
    DwarfDie.cpp
    DwarfTag.cpp
    DwarfAttrib.cpp
    DwarfObj.cpp
    DieVisitor.cpp
    XmlVisitor/XmlExporter.cpp
    XmlVisitor/XmlVisitor.cpp
    XmlVisitor/XmlDieVisitor.cpp
    TinyXml/tinyxml2.cpp)

target_link_libraries(${EXEC_NAME}
        ${LIBDW_LIBRARIES}
)
