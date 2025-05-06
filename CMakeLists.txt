cmake_minimum_required(VERSION 3.20)
project(PlutoFramework)

# 64-bit host?
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	message("-- Host is 64-bit")
    add_compile_definitions(_PLUTO_64BIT_)
else()
	message("-- Host is 32-bit")
endif()

# Main repo displays the version as a git commit hash,
# rather than a definitive number
set(PLUTO_VERSION_MAJOR 0)
set(PLUTO_VERSION_MINOR 0)
set(PLUTO_VERSION_PATCH 0)

# Get commit hash if version string is set to 0.0.0
if(PLUTO_VERSION_MAJOR EQUAL 0 AND PLUTO_VERSION_MINOR EQUAL 0 AND PLUTO_VERSION_PATCH EQUAL 0)
	# Cheers, Jonathan!
	# https://jonathanhamberg.com/post/cmake-embedding-git-hash
	execute_process(
		COMMAND git log -1 --format=%h
		WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
		OUTPUT_VARIABLE PLUTO_GIT_HASH
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	add_compile_definitions(_PLUTO_GIT_HASH_="${PLUTO_GIT_HASH}")
	set(PLUTO_VERSION_STRING "Git ${PLUTO_GIT_HASH}")
else()
	add_compile_definitions(_PLUTO_VERSION_MAJOR_=${PLUTO_VERSION_MAJOR})
	add_compile_definitions(_PLUTO_VERSION_MINOR_=${PLUTO_VERSION_MINOR})
	add_compile_definitions(_PLUTO_VERSION_PATCH_=${PLUTO_VERSION_PATCH})
	set(PLUTO_VERSION_STRING "${PLUTO_VERSION_MAJOR}.${PLUTO_VERSION_MINOR}.${PLUTO_VERSION_PATCH}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -- Options go here
option(PLUTO_DEBUG "Compile library with debug flags" OFF)
option(PLUTO_DEBUG_ASAN "Use Address Sanitizer library (must be supported by and installed on host)" OFF)
option(PLUTO_BUILD_EXAMPLES "Build example programs" OFF)
option(PLUTO_NO_CSTDINT "Don't use C's stdint/stddef headers for integer sizes.\nThis should always be left off unless you have a\nreason to use the custom definitions." OFF)
# -- End of options

# Preparation

# Debug flags
if(PLUTO_DEBUG)
	set(CMAKE_BUILD_TYPE "Debug")
	add_compile_definitions(_DEBUG)
	if(NOT MSVC)
		add_compile_options(-g)
	endif()
	if(PLUTO_DEBUG_ASAN)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fsanitize-recover=address")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize-recover=address")
	endif()
else()
	if(NOT MSVC)
		add_compile_options(-O2 -Wall)
	else()
		add_compile_options(/O2 /Wall)
	endif()
endif()

#if(NOT MSVC)
#	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
#	if(PLUTO_DEBUG)
#		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")
#		if(PLUTO_DEBUG_ASAN)
#			message("-- Compiling with Address Sanitizer")
#			add_compile_options(-fsanitize=address)
#			add_link_options(-fsanitize=address)
#		endif()
#	else()
#		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O2")
#	endif()
#endif()

set(LIBTYPE STATIC)
if(BUILD_SHARED_LIBS)
	set(LIBTYPE SHARED)
	if(WIN32)
		# This is needed to export functions marked with 'PLUTO_API'
		add_compile_definitions(_PLUTO_EXPORT_DLL_)
	endif()
else()
		add_compile_definitions(_PLUTO_STATIC_BUILD_)
endif()

set(CORE_SRC
src/c_api.h
src/c_application.h src/c_application.cpp
src/c_core.h src/c_core.cpp
src/c_coreptr.h
src/c_intdef.h
src/c_main.h
src/c_module.h
src/c_msgbox.h
src/c_task.h
src/i_system.h
src/m_misc.h
src/m_string.h src/m_string.cpp
src/PlutoFramework.h
)

if(WIN32)
	set(RC_FILE "")
	if(BUILD_SHARED_LIBS)
		configure_file(src/system/windows/pluto.rc.in pluto.rc)

		# Just to help get around include shenanigans
		configure_file(src/system/windows/resource.h.in resource.h)
		set(RC_FILE "${PROJECT_BINARY_DIR}/pluto.rc")
	endif()
	set(CORE_SYS_SRC
	src/system/windows/i_system.cpp
	src/system/windows/i_msgbox.cpp
	src/system/generic/i_log.cpp
	src/system/generic/i_task.cpp
	src/system/generic/i_wait.cpp
	${RC_FILE}
	)
elseif(APPLE)
	# NSLog or printf?
	option(PLUTO_USE_NSLOG "Use NSLog() from Apple's Cocoa API for logging [macOS only]" OFF)
	if(PLUTO_USE_NSLOG)
		set(CORE_SYS_LOG src/system/osx/i_log.mm)
	else()
		set(CORE_SYS_LOG src/system/generic/i_log.cpp)
	endif()
	find_library(FOUNDATION_FRAMEWORK Foundation)
	find_library(APPKIT_FRAMEWORK AppKit)
	set(CORE_SYS_SRC
	src/system/osx/i_system.mm
	${CORE_SYS_LOG}
	src/system/osx/i_msgbox.mm
	src/system/generic/i_task.cpp
	src/system/generic/i_wait.cpp
	)
else()
	# Assuming POSIX
	set(CORE_SYS_SRC
	src/system/posix/i_system.cpp
	src/system/posix/i_wait.cpp
	src/system/generic/i_log.cpp
	src/system/generic/i_task.cpp
	src/system/stub_msgbox.cpp
	)
endif()

	

# Build
add_library(Pluto ${LIBTYPE} ${CORE_SRC} ${CORE_SYS_SRC})
if(${PLUTO_DEBUG})
	set_target_properties(Pluto PROPERTIES OUTPUT_NAME PlutoFrameworkDebug)
else()
	set_target_properties(Pluto PROPERTIES OUTPUT_NAME PlutoFramework)
endif()
set_target_properties(Pluto PROPERTIES PREFIX "")
if(WIN32 AND BUILD_SHARED_LIBS)
	target_include_directories(Pluto PRIVATE ${PROJECT_BINARY_DIR})
endif()

if(APPLE)
	target_link_libraries(Pluto ${FOUNDATION_FRAMEWORK} ${APPKIT_FRAMEWORK})
endif()

if(PLUTO_BUILD_EXAMPLES)
	add_executable(HelloWorld examples/helloworld.cpp)
	target_include_directories(HelloWorld PRIVATE "${CMAKE_SOURCE_DIR}/src")
	target_link_libraries(HelloWorld Pluto)
endif()
