#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT PageLayoutAlgorithm: public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(PageLayoutAlgorithm, PageLayoutAlgorithm)
public:
    PageLayoutAlgorithm() = default;
    ~PageLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;
};
} // namespace OHOS::Ace::NG