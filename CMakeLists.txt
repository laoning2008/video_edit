cmake_minimum_required(VERSION 3.5)
include(ExternalProject)
include(FetchContent)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

project(VideoEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 

set(VCPKG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
set(VCPKG_PACKAGE ${VCPKG_DIR}/packages)


IF (WIN32)
    set(VCPKG_EXE_FILE ${VCPKG_DIR}/vcpkg.exe)
    set(VCPKG_INSTALL_FILE ${VCPKG_DIR}/bootstrap-vcpkg.bat)
    set(ZLIB_LIBRARY_NAME zlib_x86-windows)
    set(FFMPEG_LIBRARY_NAME ffmpeg_x86-windows)
    set(ZEROMQ_LIBRARY_NAME zeromq_x86-windows)
ELSEIF (APPLE)
    set(VCPKG_EXE_FILE ${VCPKG_DIR}/vcpkg.exe)
    set(VCPKG_INSTALL_FILE ${VCPKG_DIR}/bootstrap-vcpkg.sh)
    set(ZLIB_LIBRARY_NAME zlib_x86-windows)
    set(FFMPEG_LIBRARY_NAME ffmpeg_x86-windows)
    set(ZEROMQ_LIBRARY_NAME zeromq_x86-windows)

    set(COMPLIER_FLAGS "-Wno-reserved-user-defined-literal")
    list(APPEND CMAKE_C_FLAGS ${COMPLIER_FLAGS})
    list(APPEND CMAKE_CXX_FLAGS ${COMPLIER_FLAGS})
ELSE ()
    MESSAGE(STATUS "unsuport system: ${CMAKE_SYSTEM}")
ENDIF ()

IF (NOT EXISTS ${VCPKG_EXE_FILE})
    message(STATUS "install vcpkg")
    execute_process(COMMAND ${VCPKG_INSTALL_FILE}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
ENDIF()

IF (NOT EXISTS ${VCPKG_PACKAGE}/${ZLIB_LIBRARY_NAME}/lib)
    message(STATUS "install zlib")
    execute_process(COMMAND ${VCPKG_EXE_FILE} install zlib
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
ENDIF()

IF (NOT EXISTS ${VCPKG_PACKAGE}/${FFMPEG_LIBRARY_NAME}/lib)
    message(STATUS "install ffmpeg")
    execute_process(COMMAND ${VCPKG_EXE_FILE} install ffmpeg
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
ENDIF()

IF (NOT EXISTS ${VCPKG_PACKAGE}/${ZEROMQ_LIBRARY_NAME}/lib)
    message(STATUS "install zeromq")
    execute_process(COMMAND ${VCPKG_EXE_FILE} install zeromq
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
ENDIF()
#set(ZeroMQ_LIBRARIES ${VCPKG_PACKAGE}/${ZEROMQ_LIBRARY_NAME}/lib)
#set(ZeroMQ_INCLUDE_DIR ${VCPKG_PACKAGE}/${ZEROMQ_LIBRARY_NAME}/include)


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

