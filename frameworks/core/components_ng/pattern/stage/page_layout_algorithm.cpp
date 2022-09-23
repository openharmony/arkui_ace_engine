#include "core/components_ng/pattern/stage/page_layout_algorithm.h"

namespace OHOS::Ace::NG {

void PageLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    LOGD("%s, PageLayoutAlgorithm::Measure, %s", OHOS::Ace::DEVTAG.c_str(), layoutConstraint.ToString().c_str());
    if(layoutWrapper->GetGeometryNode()->Measure(layoutWrapper)) {
        BoxLayoutAlgorithm::PerformMeasureSelf(layoutWrapper);
    } else {
        BoxLayoutAlgorithm::Measure(layoutWrapper);
    }
}

void PageLayoutAlgorithm::Layout(LayoutWrapper *layoutWrapper)
{
    BoxLayoutAlgorithm::PerformLayout(layoutWrapper);
    if(layoutWrapper->GetGeometryNode()->Layout(layoutWrapper)) {
    } else {
        LOGD("%s, PageLayoutAlgorithm::Layout, default layout", OHOS::Ace::DEVTAG.c_str());
        for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
            child->Layout();
        }
    }
}

} // namespace OHOS::Ace::NG