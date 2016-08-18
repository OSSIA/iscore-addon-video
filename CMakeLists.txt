cmake_minimum_required(VERSION 3.1)
project(iscore_addon_video LANGUAGES CXX)

###  General initialization of always necessary stuff (AUTOMOC, etc) ###
iscore_common_setup()
if(NOT TARGET iscore_plugin_engine)
    return()
endif()

find_package(Qt5 COMPONENTS Multimedia MultimediaWidgets)

### Files & main target ###
file(GLOB_RECURSE HDRS
    "${CMAKE_CURRENT_SOURCE_DIR}/VideoProcess/*.hpp"
)
set(SRCS
"${CMAKE_CURRENT_SOURCE_DIR}/VideoProcess/VideoSerialization.cpp"

"${CMAKE_CURRENT_SOURCE_DIR}/VideoProcess/VideoModel.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/VideoProcess/VideoPresenter.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/VideoProcess/VideoView.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/VideoProcess/VideoPanelProxy.cpp"

"${CMAKE_CURRENT_SOURCE_DIR}/VideoProcess/Commands/SetVideo.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/VideoProcess/Commands/VideoCommandFactory.cpp"

"${CMAKE_CURRENT_SOURCE_DIR}/VideoProcess/Inspector/VideoInspectorWidget.cpp"

"${CMAKE_CURRENT_SOURCE_DIR}/iscore_addon_video.cpp"
)

add_library(${PROJECT_NAME} ${SRCS} ${HDRS} ${QRCS})

### If there are commands this will generate the files showcased in iscore_plugin_video.cpp ###
iscore_generate_command_list_file(${PROJECT_NAME} "${HDRS}")

target_link_libraries(${PROJECT_NAME} PUBLIC iscore_lib_process iscore_plugin_engine Qt5::Multimedia Qt5::MultimediaWidgets)

### Setup of the target ###
setup_iscore_plugin(${PROJECT_NAME})
