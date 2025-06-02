/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/flex/flex_model_ng_static.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"

namespace OHOS::Ace::NG {

void FlexModelNGStatic::SetMainAxisAlign(FrameNode* frameNode, std::optional<FlexAlign>& align)
{
    CHECK_NULL_VOID(frameNode);
    if (align.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAxisAlign, align.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAxisAlign, frameNode);
    }
}

void FlexModelNGStatic::SetWrapMainAlignment(FrameNode* frameNode, std::optional<WrapAlignment>& align)
{
    CHECK_NULL_VOID(frameNode);
    if (align.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAlignment, align.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAlignment, frameNode);
    }
}

void FlexModelNGStatic::SetWrapCrossAlignment(FrameNode* frameNode, std::optional<WrapAlignment>& align)
{
    CHECK_NULL_VOID(frameNode);
    if (align.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAlignment, align.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAlignment, frameNode);
    }
}

void FlexModelNGStatic::SetFlexDirection(FrameNode* frameNode, std::optional<FlexDirection>& layoutDirection)
{
    CHECK_NULL_VOID(frameNode);
    if (layoutDirection) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, FlexDirection, layoutDirection.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, FlexDirection, frameNode);
    }
}

void FlexModelNGStatic::SetCrossAxisAlign(FrameNode* frameNode, std::optional<FlexAlign>& align)
{
    CHECK_NULL_VOID(frameNode);
    if (align.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAxisAlign, align.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAxisAlign, frameNode);
    }
}

void FlexModelNGStatic::SetFlexAlignContent(FrameNode* frameNode, std::optional<WrapAlignment>& align)
{
    CHECK_NULL_VOID(frameNode);
    if (align.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, Alignment, align.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, Alignment, frameNode);
    }
}

}  // namespace OHOS::Ace::NG