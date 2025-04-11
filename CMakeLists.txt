cmake_minimum_required(VERSION 3.20)
project(PlutoFramework)

set(PLUTO_VERSION_MAJOR 1)
set(PLUTO_VERSION_MINOR 0)
set(PLUTO_VERSION_PATCH 0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options go here

# End of options

# Preparation
add_compile_definitions(_PLUTO_VERSION_MAJOR_=${PLUTO_VERSION_MAJOR})
add_compile_definitions(_PLUTO_VERSION_MINOR_=${PLUTO_VERSION_MINOR})
add_compile_definitions(_PLUTO_VERSION_PATCH_=${PLUTO_VERSION_PATCH})

set(LIBTYPE STATIC)
if(BUILD_SHARED_LIBS)
	set(LIBTYPE SHARED)
	if(WIN32)
		add_compile_definitions(_PLUTO_EXPORT_DLL_)
	endif()
endif()

set(CORE_SRC
src/c_api.h
src/c_application.h
src/c_core.h
src/c_coreptr.h
src/c_intdef.h
src/c_main.h
src/c_module.h
src/c_msgbox.h
src/c_task.h
src/i_system.h
src/m_misc.h
src/m_string.h
src/PlutoFramework.h
src/c_application.cpp
src/c_core.cpp
src/m_string.cpp
)

if(WIN32)
	set(CORE_SYS_SRC
	src/system/windows/i_system.cpp
	src/system/windows/i_msgbox.cpp
	src/system/generic/i_log.cpp
	src/system/generic/i_task.cpp
	src/system/generic/i_wait.cpp
	)
elseif(APPLE)
	find_library(FOUNDATION_FRAMEWORK Foundation)
	find_library(APPKIT_FRAMEWORK AppKit)
	set(CORE_SYS_SRC
	src/system/osx/i_system.mm
	src/system/osx/i_log.mm
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
if(APPLE)
	target_link_libraries(Pluto ${FOUNDATION_FRAMEWORK} ${APPKIT_FRAMEWORK})
endif()
