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

#include "core/components_ng/pattern/divider/divider_view.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void DividerView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::DIVIDER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    stack->Push(frameNode);
}

void DividerView::Vertical(bool value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(DividerLayoutProperty, Vertical, value);
}

void DividerView::DividerColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(DividerRenderProperty, DividerColor, value);
}

void DividerView::StrokeWidth(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(DividerLayoutProperty, StrokeWidth, value);
}

void DividerView::LineCap(const Ace::LineCap& value)
{
    ACE_UPDATE_PAINT_PROPERTY(DividerRenderProperty, LineCap, value);
}
} // namespace OHOS::Ace::NG