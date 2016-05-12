#pragma once
#include <Process/Inspector/ProcessInspectorWidgetDelegateFactory.hpp>

class InspectorWidgetBase;
class QObject;
class QString;
class QWidget;
namespace iscore {
struct DocumentContext;
}  // namespace iscore


namespace Video
{
class InspectorFactory final : public Process::InspectorWidgetDelegateFactory
{
        ISCORE_CONCRETE_FACTORY_DECL("4747cece-dfd8-40c3-b83c-094abbf06f71")
    public:
        InspectorFactory() = default;

    private:
        Process::InspectorWidgetDelegate* make(
                const Process::ProcessModel&,
                const iscore::DocumentContext& doc,
                QWidget* parent) const override;
        bool matches(const Process::ProcessModel&) const override;

};
}
