cmake_minimum_required(VERSION 3.1)
project(score_addon_video LANGUAGES CXX)

###  General initialization of always necessary stuff (AUTOMOC, etc) ###
score_common_setup()
if(NOT TARGET score_plugin_engine)
    return()
endif()

find_package(Qt5 COMPONENTS Multimedia MultimediaWidgets)

### Files & main target ###
set(HDRS
  "VideoProcess/Commands/VideoCommandFactory.hpp"
  "VideoProcess/Commands/SetVideo.hpp"
  "VideoProcess/Inspector/VideoInspectorWidget.hpp"
  "VideoProcess/Inspector/VideoInspectorFactory.hpp"
  "VideoProcess/VideoLayerModel.hpp"
  "VideoProcess/VideoPanelProxy.hpp"
  "VideoProcess/VideoView.hpp"
  "VideoProcess/VideoPresenter.hpp"
  "VideoProcess/VideoProcessMetadata.hpp"
  "VideoProcess/VideoFactory.hpp"
  "VideoProcess/VideoModel.hpp"
  "score_addon_video.hpp"
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

"${CMAKE_CURRENT_SOURCE_DIR}/score_addon_video.cpp"
)

add_library(${PROJECT_NAME} ${SRCS} ${HDRS} ${QRCS})
#score_moc_headers(${PROJECT_NAME} "${HDRS}")

### If there are commands this will generate the files showcased in score_plugin_video.cpp ###
score_generate_command_list_file(${PROJECT_NAME} "${HDRS}")

target_link_libraries(${PROJECT_NAME} PUBLIC score_lib_process score_plugin_engine Qt5::Multimedia Qt5::MultimediaWidgets)

### Setup of the target ###
setup_score_plugin(${PROJECT_NAME})
