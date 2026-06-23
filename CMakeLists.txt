cmake_minimum_required(VERSION 3.16)

project(stock VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

# ----------------------------------------------------------------------------
# Build Configuration
# ----------------------------------------------------------------------------
# Build Type
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type config" FORCE)
endif()
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

# set output path
if (NOT EXECUTABLE_OUTPUT_PATH)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
endif()
if (NOT LIBRARY_OUTPUT_DIRECTORY)
    set(LIBRARY_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
endif()
if (NOT RUNTIME_OUTPUT_DIRECTORY)
    set(RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
endif()

# print build info
message(STATUS "Project: stock")
message(STATUS "Build type:                                       ${CMAKE_BUILD_TYPE}")
message(STATUS "C flags, Debug configuration:                     ${CMAKE_C_FLAGS_DEBUG}")
message(STATUS "C flags, Release configuration:                   ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "C flags, Release configuration with Debug info:   ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
message(STATUS "C flags, minimal Release configuration:           ${CMAKE_C_FLAGS_MINSIZEREL}")
message(STATUS "C++ flags, Debug configuration:                   ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "C++ flags, Release configuration:                 ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "C++ flags, Release configuration with Debug info: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message(STATUS "C++ flags, minimal Release configuration:         ${CMAKE_CXX_FLAGS_MINSIZEREL}")

# ----------------------------------------------------------------------------
# Source Code
# ----------------------------------------------------------------------------

# set plugin common file directory
if (NOT PLUGIN_ROOT_DIR)
    set(PLUGIN_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/plugins)
endif()
message(STATUS "Plugin root dir: ${PLUGIN_ROOT_DIR}")

add_library(stock MODULE
  Stock.h
  Stock.cpp
  Stock.ui
  
  ${PLUGIN_ROOT_DIR}/Bus.cpp
  ${PLUGIN_ROOT_DIR}/Bus.h
  ${PLUGIN_ROOT_DIR}/PluginInterface.h
)

target_link_libraries(stock PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(stock PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PLUGIN_ROOT_DIR}
)

target_compile_definitions(stock PRIVATE STOCK_LIBRARY)

# Export all symbols for Windows DLL
set_target_properties(stock PROPERTIES 
    WINDOWS_EXPORT_ALL_SYMBOLS ON
    LIBRARY_OUTPUT_DIRECTORY "${LIBRARY_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY "${RUNTIME_OUTPUT_DIRECTORY}"
)

# ----------------------------------------------------------------------------
# Resource Files
# ----------------------------------------------------------------------------
file(GLOB STOCK_RESOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.png"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.svg"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.jpg"
)
if (STOCK_RESOURCE_FILES)
    add_custom_target(stock_copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${LIBRARY_OUTPUT_DIRECTORY}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${STOCK_RESOURCE_FILES}
            "${LIBRARY_OUTPUT_DIRECTORY}"
        DEPENDS ${STOCK_RESOURCE_FILES}
        COMMENT "Copying stock resource files to output dir ${LIBRARY_OUTPUT_DIRECTORY}"
    )
else()
    message(STATUS "No stock resource files to copy for ${PROJECT_NAME}")
endif()