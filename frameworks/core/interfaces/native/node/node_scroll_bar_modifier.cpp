/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_scroll_bar_modifier.h"

#include "interfaces/native/node/node_model.h"

#include "base/geometry/calc_dimension.h"
#include "base/utils/utils.h"
#include "core/animation/curves.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components/scroll/scroll_position_controller.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_layout_property.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/interfaces/native/node/node_api.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::NG {
namespace {
const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
}

void SetScrollBarState(ArkUINodeHandle node, ArkUI_Int32 state)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (state < 0 || state >= static_cast<ArkUI_Int32>(DISPLAY_MODE.size())) {
        state = static_cast<ArkUI_Int32>(DisplayMode::AUTO);
    }
    auto displayMode = DISPLAY_MODE[state];
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollBarLayoutProperty, DisplayMode, displayMode, frameNode);
    auto visible = displayMode == DisplayMode::OFF ? VisibleType::INVISIBLE : VisibleType::VISIBLE;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollBarLayoutProperty, Visibility, visible, frameNode);
}

ArkUI_Int32 GetScrollBarState(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, static_cast<ArkUI_Int32>(DisplayMode::AUTO));
    auto layoutProperty = frameNode->GetLayoutProperty<ScrollBarLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, static_cast<ArkUI_Int32>(DisplayMode::AUTO));
    return static_cast<ArkUI_Int32>(layoutProperty->GetDisplayMode().value_or(DisplayMode::AUTO));
}

void ResetScrollBarState(ArkUINodeHandle node)
{
    SetScrollBarState(node, static_cast<ArkUI_Int32>(DisplayMode::AUTO));
}

void SetScrollBarScroller(ArkUINodeHandle node, ArkUINodeHandle scrollable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* scrollableNode = reinterpret_cast<FrameNode*>(scrollable);
    CHECK_NULL_VOID(scrollableNode);
    auto scrollBarPattern = frameNode->GetPattern<ScrollBarPattern>();
    CHECK_NULL_VOID(scrollBarPattern);
    auto scrollablePattern = scrollableNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(scrollablePattern);

    auto proxy = scrollablePattern->GetScrollBarProxy();
    if (!proxy) {
        proxy = AceType::MakeRefPtr<ScrollBarProxy>();
        scrollablePattern->SetScrollBarProxy(proxy);
    }
    CHECK_NULL_VOID(proxy);
    proxy->RegisterScrollBar(scrollBarPattern);
    scrollBarPattern->SetScrollBarProxy(proxy);
}

ArkUINodeHandle GetScrollBarScroller(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollBarPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto proxy = pattern->GetScrollBarProxy();
    CHECK_NULL_RETURN(proxy, nullptr);
    auto scrollablePattern = proxy->GetScrollableNodeInfo().scrollableNode.Upgrade();
    CHECK_NULL_RETURN(scrollablePattern, nullptr);
    auto scrollableNode = scrollablePattern->GetHost();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(scrollableNode));
}

void ResetScrollBarScroller(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollBarPattern>();
    CHECK_NULL_VOID(pattern);
    auto proxy = pattern->GetScrollBarProxy();
    CHECK_NULL_VOID(proxy);
    proxy->UnRegisterScrollBar(pattern);
    pattern->SetScrollBarProxy(nullptr);
}

void setScrollBarEnableNestedScroll(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollBarModelNG::SetEnableNestedScroll(frameNode, static_cast<bool>(value));
}

void resetScrollBarEnableNestedScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollBarModelNG::SetEnableNestedScroll(frameNode, false);
}

void CreateScrollBarScrollBarColorWithResourceObj(ArkUINodeHandle node, void* colorRawPtr)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* colorPtr = reinterpret_cast<ResourceObject*>(colorRawPtr);
    auto colorResObj = AceType::Claim(colorPtr);
    ScrollBarModelNG::HandleSetScrollBarColor(frameNode, colorResObj);
}

void SetScrollBarScrollBarColor(ArkUINodeHandle node, ArkUI_Int32 color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollBarModelNG::SetScrollBarColor(frameNode, Color(color));
}

void ResetScrollBarScrollBarColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollBarModelNG::ResetScrollBarColor(frameNode);

    CreateScrollBarScrollBarColorWithResourceObj(node, nullptr);
}

namespace NodeModifier {
const ArkUIScrollBarModifier* GetScrollBarModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIScrollBarModifier modifier = {
        .setScrollBarDirection = nullptr,
        .resetScrollBarDirection = nullptr,
        .setScrollBarState = SetScrollBarState,
        .getScrollBarState = GetScrollBarState,
        .resetScrollBarState = ResetScrollBarState,
        .setScrollBarScroller = SetScrollBarScroller,
        .getScrollBarScroller = GetScrollBarScroller,
        .resetScrollBarScroller = ResetScrollBarScroller,
        .setScrollBarEnableNestedScroll = setScrollBarEnableNestedScroll,
        .resetScrollBarEnableNestedScroll = resetScrollBarEnableNestedScroll,
        .setScrollBarScrollBarColor = SetScrollBarScrollBarColor,
        .resetScrollBarScrollBarColor = ResetScrollBarScrollBarColor,
        .createScrollBarScrollBarColorWithResourceObj = CreateScrollBarScrollBarColorWithResourceObj,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    /* clang-format on */
    return &modifier;
}

const CJUIScrollBarModifier* GetCJUIScrollBarModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIScrollBarModifier modifier = {
        .setScrollBarDirection = nullptr,
        .resetScrollBarDirection = nullptr,
        .setScrollBarState = nullptr,
        .resetScrollBarState = nullptr,
        .setScrollBarScroller = nullptr,
        .setScrollBarEnableNestedScroll = setScrollBarEnableNestedScroll,
        .resetScrollBarEnableNestedScroll = resetScrollBarEnableNestedScroll,
        .setScrollBarScrollBarColor = SetScrollBarScrollBarColor,
        .resetScrollBarScrollBarColor = ResetScrollBarScrollBarColor,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    /* clang-format on */
    return &modifier;
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
