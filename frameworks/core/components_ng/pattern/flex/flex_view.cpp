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

#include "core/components_ng/pattern/flex/flex_view.h"

#include "base/log/log_wrapper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void FlexView::Create(FlexDirection direction, FlexAlign mainAxisAlign, FlexAlign crossAxisAlign)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::FLEX_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::FlexLayoutPattern>(); });
    stack->Push(frameNode);

    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, FlexDirection, direction);
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAxisAlign, mainAxisAlign);
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAxisAlign, crossAxisAlign);
}

void FlexView::Direction(const FlexDirection& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, FlexDirection, value);
}

void FlexView::MainAxisAlign(const FlexAlign& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAxisAlign, value);
}

void FlexView::CrossAxisAlign(const FlexAlign& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAxisAlign, value);
}

void FlexView::CreateWrap(
    WrapDirection direction, WrapAlignment mainAxisAlign, WrapAlignment crossAxisAlign, WrapAlignment alignment)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::FLEX_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::FlexLayoutPattern>(true); });
    stack->Push(frameNode);

    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, WrapDirection, direction);
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, Alignment, alignment);
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAlignment, mainAxisAlign);
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAlignment, crossAxisAlign);
}

void FlexView::SetWrapDirection(WrapDirection value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, WrapDirection, value);
}

void FlexView::SetWrapAlignment(WrapAlignment value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, Alignment, value);
}

void FlexView::SetWrapMainAlignment(WrapAlignment value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAlignment, value);
}

void FlexView::SetWrapCrossAlignment(WrapAlignment value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAlignment, value);
}

} // namespace OHOS::Ace::NG
