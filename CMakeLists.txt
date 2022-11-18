cmake_minimum_required(VERSION 3.5)
include(ExternalProject)
include(FetchContent)


list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")
#set(VCPKG_LIBRARY_LINKAGE dynamic)
#set(VCPKG_CRT_LINKAGE dynamic)
#set(VCPKG_BUILD_TYPE release)

project(VideoEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VCPKG_TARGET_TRIPLET "x64-osx-dynamic")


set(VCPKG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
set(VCPKG_PACKAGE ${VCPKG_DIR}/packages)

#list(APPEND CMAKE_SYSTEM_PROGRAM_PATH "/usr/local/Cellar/nasm/2.15.05/bin")
#message(STATUS "CMAKE_SYSTEM_PROGRAM_PATH:" ${CMAKE_SYSTEM_PROGRAM_PATH})
#vcpkg_host_path_list(PREPEND PATH "/usr/local/Cellar/nasm/2.15.05/bin")

IF (WIN32)
    set(VCPKG_EXE_FILE ${VCPKG_DIR}/vcpkg.exe)
    set(VCPKG_INSTALL_FILE ${VCPKG_DIR}/bootstrap-vcpkg.bat)
ELSEIF (APPLE)
    set(VCPKG_EXE_FILE ${VCPKG_DIR}/vcpkg)
    set(VCPKG_INSTALL_FILE ${VCPKG_DIR}/bootstrap-vcpkg.sh)

    set(COMPLIER_FLAGS "-Wno-reserved-user-defined-literal")
    list(APPEND CMAKE_C_FLAGS ${COMPLIER_FLAGS})
    list(APPEND CMAKE_CXX_FLAGS ${COMPLIER_FLAGS})

    set (ENV{PATH}  /opt/local/bin:$ENV{PATH})
ELSE ()
    MESSAGE(STATUS "unsuport system: ${CMAKE_SYSTEM}")
ENDIF ()



set(ZLIB_LIBRARY_NAME zlib)
set(FFMPEG_LIBRARY_NAME ffmpeg)
set(ZEROMQ_LIBRARY_NAME zeromq)

set(ZLIB_PACKAGE_NAME ${ZLIB_LIBRARY_NAME}_${VCPKG_TARGET_TRIPLET})
set(FFMPEG_PACKAGE_NAME ${FFMPEG_LIBRARY_NAME}_${VCPKG_TARGET_TRIPLET})
set(ZEROMQ_PACKAGE_NAME ${ZEROMQ_LIBRARY_NAME}_${VCPKG_TARGET_TRIPLET})


IF (NOT EXISTS ${VCPKG_EXE_FILE})
    message(STATUS "install vcpkg")
    execute_process(COMMAND ${VCPKG_INSTALL_FILE}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
ENDIF()

IF (NOT EXISTS ${VCPKG_PACKAGE}/${ZLIB_PACKAGE_NAME}/lib)
    message(STATUS "install zlib")
    execute_process(COMMAND ${VCPKG_EXE_FILE} install ${ZLIB_LIBRARY_NAME})
ENDIF()

IF (NOT EXISTS ${VCPKG_PACKAGE}/${FFMPEG_PACKAGE_NAME}/lib)
    message(STATUS "install ffmpeg")
    execute_process(COMMAND ${VCPKG_EXE_FILE} install ${FFMPEG_LIBRARY_NAME})
ENDIF()

IF (NOT EXISTS ${VCPKG_PACKAGE}/${ZEROMQ_PACKAGE_NAME}/lib)
    message(STATUS "install zeromq")
    execute_process(COMMAND ${VCPKG_EXE_FILE} install ${ZEROMQ_LIBRARY_NAME})
ENDIF()

message(STATUS "VCPKG_CXX_FLAGS:" ${VCPKG_CXX_FLAGS})
message(STATUS "VCPKG_LINKER_FLAGS:" ${VCPKG_LINKER_FLAGS})


#ffmpegthumbnailer option
set(ENABLE_TESTS OFF)

#libopenshot-audio option
set(ENABLE_AUDIO_DOCS OFF)
set(AUTO_INSTALL_DOCS OFF)

#libopenshot option
set(ENABLE_LIB_DOCS OFF)
set(ENABLE_PARALLEL_CTEST OFF)
set(USE_SYSTEM_JSONCPP OFF)
set(ENABLE_MAGICK OFF)
set(ENABLE_OPENCV OFF)

set(ENABLE_COVERAGE OFF)
set(ENABLE_PARALLEL_CTEST OFF)
set(ENABLE_LIB_DOCS OFF)
set(ENABLE_TESTS OFF)
set(DISABLE_TESTS ON)

execute_process(COMMAND git apply ${CMAKE_CURRENT_SOURCE_DIR}/patch/0001-do-not-build-examples-and-bindings.patch
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libopenshot)

add_subdirectory(libopenshot-audio)

add_subdirectory(libopenshot)
add_subdirectory(ffmpegthumbnailer)
add_subdirectory(editor)

