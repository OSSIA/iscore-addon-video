#pragma once
#include <Process/Inspector/ProcessInspectorWidgetDelegateFactory.hpp>
#include <VideoProcess/VideoModel.hpp>
#include <VideoProcess/Inspector/VideoInspectorWidget.hpp>

namespace Video
{
class InspectorFactory final :
        public Process::InspectorWidgetDelegateFactory_T<ProcessModel, InspectorWidget>
{
        ISCORE_CONCRETE("4747cece-dfd8-40c3-b83c-094abbf06f71")
};
}
