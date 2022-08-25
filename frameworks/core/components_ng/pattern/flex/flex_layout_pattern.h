//
// Created by 陆泽辉 on 2022/8/8.
//

#ifndef ARKUI_ACE_ENGINE_FLEX_LAYOUT_PATTERN_H
#define ARKUI_ACE_ENGINE_FLEX_LAYOUT_PATTERN_H

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"

namespace OHOS::Ace::NG {
class FlexLayoutPattern : public Pattern {
    
public:
    explicit FlexLayoutPattern() = default;
    ~FlexLayoutPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override {
        return MakeRefPtr<FlexLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override {
        return MakeRefPtr<FlexLayoutAlgorithm>();
    }

    bool IsAtomicNode() const override {
        return false;
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(FlexLayoutPattern);
};
} // namespace OHOS::Ace::NG

#endif // ARKUI_ACE_ENGINE_FLEX_LAYOUT_PATTERN_H
