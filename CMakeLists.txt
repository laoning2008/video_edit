cmake_minimum_required(VERSION 3.24)
include(ExternalProject)
include(FetchContent)

project(VideoEditor VERSION 0.1 LANGUAGES CXX)

set(CUSTOM_TRIPLETS triplets/community)
set(VCPKG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
set(VCPKG_PACKAGE ${VCPKG_DIR}/packages)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules )
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

IF (WIN32)
    set(VCPKG_EXE_FILE ${VCPKG_DIR}/vcpkg.exe)
    set(VCPKG_INSTALL_FILE ${VCPKG_DIR}/bootstrap-vcpkg.bat)

    set(VCPKG_TARGET_TRIPLET "x86-windows-dynamic")
ELSEIF (APPLE)
    set(VCPKG_EXE_FILE ${VCPKG_DIR}/vcpkg)
    set(VCPKG_INSTALL_FILE ${VCPKG_DIR}/bootstrap-vcpkg.sh)

    set(COMPLIER_FLAGS "-Wno-reserved-user-defined-literal")
    list(APPEND CMAKE_C_FLAGS ${COMPLIER_FLAGS})
    list(APPEND CMAKE_CXX_FLAGS ${COMPLIER_FLAGS})

    set (ENV{PATH}  $ENV{PATH}:/opt/local/bin)
    set(Qt5_DIR /Users/laoning/Qt5.12.12/5.12.12/clang_64/lib/cmake/Qt5)

    set(VCPKG_TARGET_TRIPLET "x64-osx-dynamic")
ELSE ()
    MESSAGE(STATUS "unsuport system: ${CMAKE_SYSTEM}")
ENDIF ()


list(APPEND CMAKE_PREFIX_PATH ${VCPKG_DIR}/installed/${VCPKG_TARGET_TRIPLET})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(ZLIB_LIBRARY_NAME ZLIB)
set(OpenSSL_LIBRARY_NAME OpenSSL)
set(FFMPEG_LIBRARY_NAME FFmpeg)
set(JPEG_LIBRARY_NAME libjpeg-turbo)
set(PNG_LIBRARY_NAME libpng)
set(ZEROMQ_LIBRARY_NAME zeromq)
set(OMP_LIBRARY_NAME libomp)
set(ZLIB_PACKAGE_NAME ${ZLIB_LIBRARY_NAME}:${VCPKG_TARGET_TRIPLET})
set(OPENSSL_PACKAGE_NAME ${OpenSSL_LIBRARY_NAME}:${VCPKG_TARGET_TRIPLET})
set(FFMPEG_PACKAGE_NAME ${FFMPEG_LIBRARY_NAME}:${VCPKG_TARGET_TRIPLET})
set(JPEG_PACKAGE_NAME ${JPEG_LIBRARY_NAME}:${VCPKG_TARGET_TRIPLET})
set(PNG_PACKAGE_NAME ${PNG_LIBRARY_NAME}:${VCPKG_TARGET_TRIPLET})
set(ZEROMQ_PACKAGE_NAME ${ZEROMQ_LIBRARY_NAME}:${VCPKG_TARGET_TRIPLET})
set(OMP_PACKAGE_NAME ${OMP_LIBRARY_NAME}:${VCPKG_TARGET_TRIPLET})


IF (NOT EXISTS ${VCPKG_EXE_FILE})
    message(STATUS "install vcpkg")
    execute_process(COMMAND ${VCPKG_INSTALL_FILE}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
ENDIF()

find_package(${ZLIB_LIBRARY_NAME})
IF (NOT ${ZLIB_LIBRARY_NAME}_FOUND)
    message(STATUS "install zlib")
    execute_process(COMMAND ${VCPKG_EXE_FILE} install ${ZLIB_PACKAGE_NAME}
        --overlay-triplets=${CUSTOM_TRIPLETS}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
ENDIF()

find_package(${OpenSSL_LIBRARY_NAME})
IF (NOT ${OpenSSL_LIBRARY_NAME}_FOUND)
    message(STATUS "install openssl")
    execute_process(COMMAND ${VCPKG_EXE_FILE} install ${OPENSSL_PACKAGE_NAME}
        --overlay-triplets=${CUSTOM_TRIPLETS}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
ENDIF()

find_package(${FFMPEG_LIBRARY_NAME})
IF (NOT ${FFMPEG_LIBRARY_NAME}_FOUND)
    message(STATUS "install libjpeg")
    execute_process(COMMAND ${VCPKG_EXE_FILE} install ${JPEG_PACKAGE_NAME}
        --overlay-triplets=${CUSTOM_TRIPLETS}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
ENDIF()

find_package(${PNG_LIBRARY_NAME})
IF (NOT ${PNG_LIBRARY_NAME}_FOUND)
    message(STATUS "install libpng")
    execute_process(COMMAND ${VCPKG_EXE_FILE} install ${PNG_PACKAGE_NAME}
        --overlay-triplets=${CUSTOM_TRIPLETS}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
ENDIF()

find_package(${JPEG_LIBRARY_NAME})
IF (NOT ${JPEG_LIBRARY_NAME}_FOUND)
    message(STATUS "install jpeg")
    execute_process(COMMAND ${VCPKG_EXE_FILE} install ${JPEG_PACKAGE_NAME}
        --overlay-triplets=${CUSTOM_TRIPLETS}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
ENDIF()

find_package(${ZEROMQ_LIBRARY_NAME})
IF (NOT ${ZEROMQ_LIBRARY_NAME}_FOUND)
    message(STATUS "install zeromq")
    execute_process(COMMAND ${VCPKG_EXE_FILE} install ${ZEROMQ_PACKAGE_NAME}
        --overlay-triplets=${CUSTOM_TRIPLETS}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
ENDIF()


find_package(${OMP_LIBRARY_NAME})
IF (NOT ${OMP_LIBRARY_NAME}_FOUND)
    message(STATUS "install openmp")
    execute_process(COMMAND ${VCPKG_EXE_FILE} install ${OMP_PACKAGE_NAME}
        --overlay-triplets=${CUSTOM_TRIPLETS}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
ENDIF()


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

