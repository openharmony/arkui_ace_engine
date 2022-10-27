/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/scroll_bar/scroll_bar_view.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
}

RefPtr<FrameNode> ScrollBarView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_BAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ScrollBarPattern>(); });
    stack->Push(frameNode);
    return frameNode;
}

void ScrollBarView::SetAxis(Axis axis)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ScrollBarLayoutProperty, Axis, axis);
}

void ScrollBarView::SetDisplayMode(int displayMode)
{
    if (displayMode < 0 || displayMode >= static_cast<int32_t>(DISPLAY_MODE.size())) {
        return;
    }
    // auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    // CHECK_NULL_VOID(frameNode);
    // auto pattern = frameNode->GetPattern<ScrollBarPattern>();
    // CHECK_NULL_VOID(pattern);
    // pattern->SetDisplayMode(DISPLAY_MODE[displayMode]);
    ACE_UPDATE_LAYOUT_PROPERTY(ScrollBarLayoutProperty, DisplayMode, DISPLAY_MODE[displayMode]);
    auto visible = (DISPLAY_MODE[displayMode] == DisplayMode::OFF) ? VisibleType::INVISIBLE : VisibleType::VISIBLE;
    ACE_UPDATE_LAYOUT_PROPERTY(ScrollBarLayoutProperty, Visibility, visible);
}

} // namespace OHOS::Ace::NG
