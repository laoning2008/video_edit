cmake_minimum_required(VERSION 3.5)
include(ExternalProject)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)
set(COMPLIER_FLAGS "-Wno-reserved-user-defined-literal")
list(APPEND CMAKE_C_FLAGS ${COMPLIER_FLAGS})
list(APPEND CMAKE_CXX_FLAGS ${COMPLIER_FLAGS})

project(VideoEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 

#IF (WIN32)
#    set (Qt5_DIR "/Users/laoning/Qt5.12.12/5.12.12/clang_64/lib/cmake/Qt5")
#ELSEIF (APPLE)
#    set (Qt5_DIR "/Users/laoning/Qt5.12.12/5.12.12/clang_64/lib/cmake/Qt5")
#ELSE ()
#    MESSAGE(STATUS "unsuport system: ${CMAKE_SYSTEM}")
#ENDIF ()



set(FFMPEG_GIT              git@github.com:FFmpeg/FFmpeg.git)
set(FFMPEG_BRANCH           origin/release/5.1)
set(FFMPEG_ROOT             ${CMAKE_BINARY_DIR}/ffmpeg)
set(FFMPEG_SRC              ${FFMPEG_ROOT}/src/ffmpeg)
set(FFMPEG_BUILD_DIR        ${FFMPEG_ROOT}/src/ffmpeg-build)
set(FFMPEG_CONFIGURE        cd ${FFMPEG_BUILD_DIR} && ${FFMPEG_SRC}/configure --prefix=${FFMPEG_ROOT}
    --enable-shared --disable-static --disable-x86asm --disable-programs --disable-doc )
set(FFMPEG_BUILD            cd ${FFMPEG_BUILD_DIR} && make -j16)
set(FFMPEG_INSTALL          cd ${FFMPEG_BUILD_DIR} && make install)
set(FFMPEG_LIB_DIR          ${FFMPEG_ROOT}/lib)
set(FFMPEG_INCLUDE_DIR      ${FFMPEG_ROOT}/include)
set(FFMPEG_DIR              ${FFMPEG_ROOT})
set(FFmpeg_DIR              ${FFMPEG_ROOT})
IF (NOT EXISTS ${FFMPEG_LIB_DIR})
    ExternalProject_Add(ffmpeg
        GIT_REPOSITORY          ${FFMPEG_GIT}
        GIT_TAG                 ${FFMPEG_BRANCH}
        PREFIX                  ${FFMPEG_ROOT}
        CONFIGURE_COMMAND       ${FFMPEG_CONFIGURE}
        BUILD_COMMAND           ${FFMPEG_BUILD}
        INSTALL_COMMAND         ${FFMPEG_INSTALL}
        )
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


list(APPEND CMAKE_PREFIX_PATH ${FFMPEG_ROOT})

add_subdirectory(libopenshot-audio)
add_subdirectory(libopenshot)
add_subdirectory(ffmpegthumbnailer)
add_subdirectory(editor)

