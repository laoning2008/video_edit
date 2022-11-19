list(APPEND CMAKE_MODULE_PATH ${FFMPEGTHUMBNAILER_SRC}/cmake)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(TS_FILES ui/VideoEditor_zh_CN.ts)
set(PROJECT_SOURCES
        main.cpp
        ui/mainwindow.cpp
        ui/mainwindow.h
        ui/mainwindow.ui
        ui/MediaItem.cpp
        ui/MediaItem.h
        ui/MediaItemDelegate.cpp
        ui/MediaItemDelegate.h
        ${TS_FILES}
)

add_executable(VideoEditor ${PROJECT_SOURCES})

find_package(Qt5 COMPONENTS Core Gui Widgets LinguistTools REQUIRED)
qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

find_package(FFmpeg REQUIRED)

target_link_libraries(VideoEditor PRIVATE Qt5::Widgets
    FFmpeg::avformat
    FFmpeg::avcodec
    FFmpeg::avutil
    FFmpeg::avfilter
    libffmpegthumbnailer
    openshot)

set_target_properties(VideoEditor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)
