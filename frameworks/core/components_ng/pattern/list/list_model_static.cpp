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

#include "core/components_ng/pattern/list/list_model_static.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"

namespace OHOS::Ace::NG {

const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };

void ListModelStatic::SetListItemAlign(FrameNode* frameNode, const std::optional<V2::ListItemAlign>& listItemAlign)
{
    if (listItemAlign.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ListItemAlign, listItemAlign.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ListItemAlign, frameNode);
    }
}

void ListModelStatic::SetListDirection(FrameNode* frameNode, const std::optional<int32_t>& axis)
{
    if (axis.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ListDirection, static_cast<Axis>(axis.value()), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ListDirection, frameNode);
    }
}

void ListModelStatic::SetListScrollBar(FrameNode* frameNode, const std::optional<int32_t>& barState)
{
    CHECK_NULL_VOID(frameNode);
    int32_t displayNumber;

    if (!barState.has_value() || (barState.has_value() &&
        (barState.value() < 0 || barState.value() >= static_cast<int32_t>(DISPLAY_MODE.size())))) {
        displayNumber = static_cast<int32_t>(DisplayMode::AUTO);
    } else {
        displayNumber = barState.value();
    }

    ScrollableModelNG::SetScrollBarMode(frameNode, displayNumber);
}

void ListModelStatic::SetDivider(FrameNode* frameNode, const std::optional<V2::ItemDivider>& divider)
{
    if (divider.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, divider.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, frameNode);
    }
}

void ListModelStatic::SetSticky(FrameNode* frameNode, const std::optional<int32_t>& stickyStyle)
{
    if (stickyStyle.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, StickyStyle,
            static_cast<V2::StickyStyle>(stickyStyle.value()), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, StickyStyle, frameNode);
    }
}

void ListModelStatic::SetScrollSnapAlign(FrameNode* frameNode, const std::optional<ScrollSnapAlign>& scrollSnapAlign)
{
    if (scrollSnapAlign.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ScrollSnapAlign, scrollSnapAlign.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ScrollSnapAlign, frameNode);
    }
}

void ListModelStatic::SetListFriction(FrameNode* frameNode, const std::optional<double>& friction)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    auto frictionValue = friction.value_or(FRICTION);
    if (LessOrEqual(frictionValue, 0.0)) {
        frictionValue = FRICTION;
    }
    pattern->SetFriction(frictionValue);
}
} // namespace OHOS::Ace::NG