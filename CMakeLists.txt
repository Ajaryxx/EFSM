cmake_minimum_required(VERSION 3.31.6)

project(EFSM
VERSION 0.1.0
LANGUAGES CXX)

#global settings
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#project vars

set(EXE_NAME "EFSM")
set(BUILD_SHARED_LIBS OFF)

include(FetchContent)

FetchContent_Declare(
	wxWidgets
	GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets
	GIT_TAG v3.3.1
	GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(wxWidgets)


add_executable(${EXE_NAME} "src/App.cpp" "src/Application.cpp")
target_include_directories(${EXE_NAME} PRIVATE "include/")
target_precompile_headers(${EXE_NAME} PRIVATE "include/PCH.hpp")
target_link_libraries(${EXE_NAME} PRIVATE wx::core wx::base)

#set subsystem for windows

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
set_target_properties(${EXE_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)

endif()

add_subdirectory(src)