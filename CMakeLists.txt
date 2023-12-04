cmake_minimum_required(VERSION 2.8.9...3.27)
project(Advent C CXX)


#
# Variables
#

# Project generator
if(CMAKE_GENERATOR MATCHES Ninja)
    set(NINJA 1)
endif()

# Compiler
if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    set(CLANG 1)
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(GCC 1)
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(MSVC 1)
endif()

# OS
if(CMAKE_SYSTEM_NAME MATCHES Linux)
    set(LINUX 1)
endif()
if(CMAKE_SYSTEM_NAME MATCHES FreeBSD)
    set(FREEBSD 1)
endif()
if(CMAKE_SYSTEM_NAME MATCHES NetBSD)
    set(NETBSD 1)
endif()

# Build type
set(IS_DEBUG
    "$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>")
set(IS_RELEASE
    "$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>,$<CONFIG:RelWithDebInfo>>")


#
# Sources
#

set(HERE ${CMAKE_CURRENT_LIST_DIR}/carob)
set(ADVENT ${CMAKE_CURRENT_LIST_DIR})

set(CAROB_SOURCES ${CAROB_SOURCES}
    ${HERE}/src/os/c.h
    ${HERE}/src/os/chrono.h
    ${HERE}/src/os/io.h
    ${HERE}/src/os/mapped-file.h
    ${HERE}/src/os/mutex.h
    ${HERE}/src/os/thread.h
    ${HERE}/src/os/os.h
)
set(PACK_TOOL_SOURCES ${PACK_TOOL_SOURCES}
    ${HERE}/src/os/c.h
    ${HERE}/src/os/condition-variable.h
    ${HERE}/src/os/mapped-file.h
    ${HERE}/src/os/mutex.h
    ${HERE}/src/os/os.h
    ${HERE}/src/os/thread.h
)

if (WIN32)
    set(CAROB_SOURCES ${CAROB_SOURCES}
        ${HERE}/src/os/memmove.cpp
        ${HERE}/src/os/windows/c.cpp
        ${HERE}/src/os/windows/c.h
        ${HERE}/src/os/windows/chrono.cpp
        ${HERE}/src/os/windows/io.cpp
        ${HERE}/src/os/windows/io.h
        ${HERE}/src/os/windows/mapped-file.cpp
        ${HERE}/src/os/windows/mapped-file.h
        ${HERE}/src/os/windows/windows.cpp
        ${HERE}/src/os/windows/windows.h
    )
elseif(APPLE)
    set(CAROB_SOURCES ${CAROB_SOURCES}
        ${HERE}/src/os/mac/c.h
        ${HERE}/src/os/mac/chrono.cpp
        ${HERE}/src/os/mac/gui.mm
        ${HERE}/src/os/mac/gui.h
        ${HERE}/src/os/mac/thread.cpp
        ${HERE}/src/os/mac/thread.h
        ${HERE}/src/os/unix/io.cpp
        ${HERE}/src/os/unix/io.h
        ${HERE}/src/os/unix/mapped-file.cpp
        ${HERE}/src/os/unix/mapped-file.h
        ${HERE}/src/os/unix/mutex.h
        ${HERE}/src/os/unix/unix.cpp
    )
else()
    set(CAROB_SOURCES ${CAROB_SOURCES}
        ${HERE}/src/os/linux/c.h
        ${HERE}/src/os/unix/chrono.cpp
        ${HERE}/src/os/unix/io.cpp
        ${HERE}/src/os/unix/io.h
        ${HERE}/src/os/unix/mapped-file.cpp
        ${HERE}/src/os/unix/mutex.h
        ${HERE}/src/os/unix/thread.h
        ${HERE}/src/os/unix/unix.cpp
    )
endif()

set(CAROB_SOURCES ${CAROB_SOURCES}
    ${HERE}/src/util/align.h
    ${HERE}/src/util/assert.h
    ${HERE}/src/util/compiler.h
    ${HERE}/src/util/fnv.cpp
    ${HERE}/src/util/fnv.h
    ${HERE}/src/util/function.h
    ${HERE}/src/util/hash.cpp
    ${HERE}/src/util/hash.h
    ${HERE}/src/util/hashtable.h
    ${HERE}/src/util/int.h
    ${HERE}/src/util/io.cpp
    ${HERE}/src/util/io.h
    ${HERE}/src/util/jobs.cpp
    ${HERE}/src/util/jobs.h
    ${HERE}/src/util/json.cpp
    ${HERE}/src/util/json.h
    ${HERE}/src/util/likely.h
    ${HERE}/src/util/list.h
    ${HERE}/src/util/markable.h
    ${HERE}/src/util/math2.h
    ${HERE}/src/util/measure.cpp
    ${HERE}/src/util/measure.h
    ${HERE}/src/util/move.h
    ${HERE}/src/util/new.cpp
    ${HERE}/src/util/new.h
    ${HERE}/src/util/pool.h
    ${HERE}/src/util/random.cpp
    ${HERE}/src/util/random.h
    ${HERE}/src/util/string-view.cpp
    ${HERE}/src/util/string-view.h
    ${HERE}/src/util/string.cpp
    ${HERE}/src/util/string.h
    ${HERE}/src/util/string2.cpp
    ${HERE}/src/util/string2.h
    ${HERE}/src/util/transform.c
    ${HERE}/src/util/transform.h
    ${HERE}/src/util/vector.h
)

if(MSVC OR ${CMAKE_VERSION} VERSION_LESS 3.1)
    # MSVC 2017 and below, and CMake 3.0 and below cannot vary source files by
    # configuration.
    set(CAROB_SOURCES ${CAROB_SOURCES}
        ${HERE}/src/util/assert.cpp
    )
    set(PACK_TOOL_SOURCES ${PACK_TOOL_SOURCES}
        ${HERE}/src/util/assert.cpp
    )
else()
    set(CAROB_SOURCES ${CAROB_SOURCES}
        $<${IS_DEBUG}:${HERE}/src/util/assert.cpp>
    )
    set(PACK_TOOL_SOURCES ${PACK_TOOL_SOURCES}
        $<${IS_DEBUG}:${HERE}/src/util/assert.cpp>
    )
endif()


#
# Targets
#

add_library(carob ${CAROB_SOURCES})

add_executable(01a ${ADVENT}/src/01a.cpp)
target_link_libraries(01a carob)
add_executable(01b ${ADVENT}/src/01b.cpp)
target_link_libraries(01b carob)

add_executable(02a ${ADVENT}/src/02a.cpp)
target_link_libraries(02a carob)
add_executable(02b ${ADVENT}/src/02b.cpp)
target_link_libraries(02b carob)

add_executable(03a ${ADVENT}/src/03a.cpp)
target_link_libraries(03a carob)
#add_executable(03b ${ADVENT}/src/03b.cpp)
#target_link_libraries(03b carob)

include_directories(${HERE}/src)


#
# Compilation options
#

if(CLANG OR GCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# Disable C++ exceptions
if(CLANG OR GCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
elseif(MSVC)
    string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif()

# Disable C++ run-time type information
if(CLANG OR GCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
elseif(MSVC)
    string(REPLACE "/GR" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR-")
endif()

# Hide most symbols
if(CLANG OR GCC)
    set(CMAKE_CXX_FLAGS_RELEASE
        "${CMAKE_CXX_FLAGS_RELEASE} -fvisibility=hidden")
    set(CMAKE_CXX_FLAGS_MINSIZEREL
        "${CMAKE_CXX_FLAGS_MINSIZEREL} -fvisibility=hidden")
endif()

# Reduce code size
if(CLANG)
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -Oz")
endif()

# Enable floating point optimizations
if(CLANG OR GCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:fast")
endif()

# Disable stack canary
if(CLANG OR GCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-stack-protector")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GS-")
endif()

# Optimize at link time
if(CLANG OR GCC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -flto")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO
        "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -flto")
endif()

# Enable NDEBUG anything not a debug build.
if(${CMAKE_VERSION} VERSION_LESS 2.8.10)
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
else()
    target_compile_definitions(carob PUBLIC $<$<NOT:${IS_DEBUG}>:NDEBUG>)
endif()

# Enable color within compiler's output
if(NOT DEFINED ENV{CI})
    if(NINJA AND CLANG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
    endif()
    if(NINJA AND GCC AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
    endif()
endif()


#
# Linking and externally-managed dependencies
#

# Optimize at link time
if(CLANG OR GCC)
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE
        "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto=full")
    set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL
        "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} -flto=full")
    set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO
        "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} -flto=thin")
endif()

# Do not link to libstdc++ or libc++
if(APPLE OR LINUX OR FREEBSD OR NETBSD)
    set(CMAKE_CXX_LINK_EXECUTABLE
        "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
endif()

# Strip symbols
if(LINUX OR FREEBSD OR NETBSD)
    # GNU binutils
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE
        "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wl,--strip-all")
    set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL
        "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} -Wl,--strip-all")
elseif(APPLE)
    # macOS linker
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE
        "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wl,-x -Wl,-dead_strip")
    set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL
        "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} -Wl,-x -Wl,-dead_strip")
endif()

if(APPLE)
    set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} --no-standard-libraries -lSystem")
endif()

if(LINUX AND NOT AV_EM)
    execute_process(COMMAND ldd --version
                    OUTPUT_VARIABLE LDD_OUT
                    ERROR_VARIABLE LDD_ERR)

    set(LDD_VERSION "${LDD_OUT}${LDD_ERR}")

    if("${LDD_VERSION}" MATCHES "GLIBC (2.[0-9]*)")
        set(GLIBC_VERSION "${CMAKE_MATCH_1}")
    elseif("${LDD_VERSION}" MATCHES "GNU libc. (2.[0-9]*)")
        set(GLIBC_VERSION "${CMAKE_MATCH_1}")
    elseif("${LDD_VERSION}" MATCHES "Version ([1-9][0-9.]*)")
        set(MUSL_VERSION "${CMAKE_MATCH_1}")
    else()
        message(WARNING "Could not determine libc version")
        message(WARNING "${LDD_VERSION}")
    endif()

    if("${GLIBC_VERSION}" VERSION_LESS "2.17")
        target_link_libraries(carob rt)
    endif()

    if(GLIBC_VERSION)
        target_link_libraries(carob m pthread)
    endif()
endif()

if(FREEBSD OR NETBSD)
    target_link_libraries(carob PUBLIC  m pthread)
endif()
if(AV_EM)
    target_link_libraries(carob PUBLIC  pthread)
endif()


#
# Policies
#

# Do not turn on -rdynamic. Also solved with CMP0065 in CMake 3.4
# FIXME: Apply it only to local targets, or possibly just try to
#        remove -rdynamic from these.
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
