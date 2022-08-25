//
// Created by 陆泽辉 on 2022/8/4.
//

#include "core/components_ng/pattern/flex/flex_view.h"
#include "base/log/log_wrapper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void FlexView::Create(FlexDirection direction, FlexAlign mainAxisAlign, FlexAlign crossAxisAlign) {
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::FLEX_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::FlexLayoutPattern>(); });
    stack->Push(frameNode);

    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, FlexDirection, direction);
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAxisAlign, mainAxisAlign);
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAxisAlign, crossAxisAlign);
}

void FlexView::Direction(const FlexDirection& value) {
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, FlexDirection, value);
}

void FlexView::MainAxisAlign(const FlexAlign& value) {
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAxisAlign, value);
}

void FlexView::CrossAxisAlign(const FlexAlign& value) {
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAxisAlign, value);
}
} // namespace OHOS::Ace::NG
