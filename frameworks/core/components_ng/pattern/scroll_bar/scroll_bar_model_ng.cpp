/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/scroll_bar/scroll_bar_model_ng.h"
#ifdef ARKUI_CIRCLE_FEATURE
#include "core/components_ng/pattern/arc_scroll_bar/arc_scroll_bar_pattern.h"
#endif

namespace OHOS::Ace::NG {
namespace {
const std::vector<Axis> AXIS = { Axis::VERTICAL, Axis::HORIZONTAL, Axis::NONE };
const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
}
RefPtr<ScrollProxy> ScrollBarModelNG::GetScrollBarProxy(const RefPtr<ScrollProxy>& scrollProxy)
{
    auto proxy = AceType::DynamicCast<NG::ScrollBarProxy>(scrollProxy);
    if (!proxy) {
        proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    }

    return proxy;
}

void ScrollBarModelNG::Create(const RefPtr<ScrollProxy>& proxy, bool infoflag, bool proxyFlag,
    int directionValue, int stateValue, bool isCreateArc)
{
    CHECK_NULL_VOID(proxy);
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto nodeId = stack->ClaimNodeId();
    RefPtr<FrameNode> frameNode = nullptr;
    if (isCreateArc) {
        ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::ARC_SCROLL_BAR_ETS_TAG, nodeId);
        #ifdef ARKUI_CIRCLE_FEATURE
        frameNode = FrameNode::GetOrCreateFrameNode(
            V2::ARC_SCROLL_BAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ArcScrollBarPattern>(); });
        #endif
    } else {
        ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::SCROLL_BAR_ETS_TAG, nodeId);
        frameNode = FrameNode::GetOrCreateFrameNode(
            V2::SCROLL_BAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ScrollBarPattern>(); });
    }
    CHECK_NULL_VOID(frameNode);
    stack->Push(frameNode);
    auto scrollbarpattern = frameNode->GetPattern();
    CHECK_NULL_VOID(scrollbarpattern);
    auto pattern = AceType::DynamicCast<NG::ScrollBarPattern>(scrollbarpattern);
    CHECK_NULL_VOID(pattern);
    if (infoflag) {
        if (proxyFlag) {
            auto scrollBarProxy = AceType::DynamicCast<NG::ScrollBarProxy>(proxy);
            CHECK_NULL_VOID(scrollBarProxy);
            scrollBarProxy->RegisterScrollBar(pattern);
            pattern->SetScrollBarProxy(scrollBarProxy);
        }

        if (directionValue < 0 || directionValue >= static_cast<int32_t>(AXIS.size())) {
            directionValue = static_cast<int32_t>(Axis::VERTICAL);
        }

        if (stateValue < 0 || stateValue >= static_cast<int32_t>(DISPLAY_MODE.size())) {
            stateValue = static_cast<int32_t>(DisplayMode::AUTO);
        }

        ACE_UPDATE_LAYOUT_PROPERTY(ScrollBarLayoutProperty, Axis, AXIS[directionValue]);
        ACE_UPDATE_LAYOUT_PROPERTY(ScrollBarLayoutProperty, DisplayMode, DISPLAY_MODE[stateValue]);
        auto visible = (DISPLAY_MODE[stateValue] == DisplayMode::OFF) ? VisibleType::INVISIBLE : VisibleType::VISIBLE;
        ACE_UPDATE_LAYOUT_PROPERTY(ScrollBarLayoutProperty, Visibility, visible);
    }
}

RefPtr<FrameNode> ScrollBarModelNG::CreateFrameNode(int32_t nodeId)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_RETURN(stack, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(
        V2::SCROLL_BAR_ETS_TAG, nodeId, AceType::MakeRefPtr<ScrollBarPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    stack->Push(frameNode);
    UpdateLayoutProperty();
    return frameNode;
}

void ScrollBarModelNG::UpdateLayoutProperty()
{
    ACE_UPDATE_LAYOUT_PROPERTY(ScrollBarLayoutProperty, Axis, Axis::VERTICAL);
    ACE_UPDATE_LAYOUT_PROPERTY(ScrollBarLayoutProperty, DisplayMode, DisplayMode::AUTO);
    ACE_UPDATE_LAYOUT_PROPERTY(ScrollBarLayoutProperty, Visibility, VisibleType::VISIBLE);
}

void ScrollBarModelNG::SetScrollBarProxy(FrameNode* frameNode, const  RefPtr<ScrollProxy>& proxy)
{
    CHECK_NULL_VOID(proxy);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollBarPattern>();
    CHECK_NULL_VOID(pattern);
    auto scrollBarProxy = AceType::DynamicCast<NG::ScrollBarProxy>(proxy);
    CHECK_NULL_VOID(scrollBarProxy);
    scrollBarProxy->RegisterScrollBar(pattern);
    pattern->SetScrollBarProxy(scrollBarProxy);
}

void ScrollBarModelNG::SetDirection(FrameNode* frameNode, std::optional<Axis> axis)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollBarLayoutProperty, Axis, axis.value_or(Axis::VERTICAL), frameNode);
}

void ScrollBarModelNG::SetState(FrameNode* frameNode, std::optional<DisplayMode> displayMode)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        ScrollBarLayoutProperty, DisplayMode, displayMode.value_or(DisplayMode::AUTO), frameNode);
    auto visible =
        displayMode.value_or(DisplayMode::AUTO) == DisplayMode::OFF ? VisibleType::INVISIBLE : VisibleType::VISIBLE;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        ScrollBarLayoutProperty, Visibility, visible, frameNode);
}

void ScrollBarModelNG::SetNestedScroll(RefPtr<FrameNode>& frameNode, RefPtr<ScrollablePattern>& pattern)
{
    CHECK_NULL_VOID(frameNode);
    if (frameNode->IsOnMainTree()) {
        pattern->SearchAndSetParentNestedScroll(frameNode);
    }
}

void ScrollBarModelNG::UnSetNestedScroll(RefPtr<FrameNode>& frameNode, RefPtr<ScrollablePattern>& pattern)
{
    CHECK_NULL_VOID(frameNode);
    if (frameNode->IsOnMainTree()) {
        pattern->SearchAndUnsetParentNestedScroll(frameNode);
    }
}

void ScrollBarModelNG::SetEnableNestedScroll(bool enableNestedSroll)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto scrollBarPattern = frameNode->GetPattern<ScrollBarPattern>();
    CHECK_NULL_VOID(scrollBarPattern);
    auto enableNested = scrollBarPattern->GetEnableNestedSorll();
    auto scrollBarProxy = scrollBarPattern->GetScrollBarProxy();
    CHECK_NULL_VOID(scrollBarProxy);
    scrollBarPattern->SetEnableNestedSorll(enableNestedSroll);
    auto info = scrollBarProxy->GetScrollableNodeInfo();
    auto pattern = info.scrollableNode.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto node = pattern->GetHost();
    CHECK_NULL_VOID(node);
    if (enableNestedSroll == true && enableNestedSroll != enableNested) {
        SetNestedScroll(node, pattern);
    }
    if (enableNestedSroll == false && enableNestedSroll != enableNested) {
        UnSetNestedScroll(node, pattern);
    }
}

void ScrollBarModelNG::SetEnableNestedScroll(FrameNode* frameNode, bool enableNestedSroll)
{
    CHECK_NULL_VOID(frameNode);
    auto scrollBarPattern = frameNode->GetPattern<ScrollBarPattern>();
    CHECK_NULL_VOID(scrollBarPattern);
    auto enableNested = scrollBarPattern->GetEnableNestedSorll();
    auto scrollBarProxy = scrollBarPattern->GetScrollBarProxy();
    CHECK_NULL_VOID(scrollBarProxy);
    scrollBarPattern->SetEnableNestedSorll(enableNestedSroll);
    auto info = scrollBarProxy->GetScrollableNodeInfo();
    auto pattern = info.scrollableNode.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto node = pattern->GetHost();
    CHECK_NULL_VOID(node);
    if (enableNestedSroll == true && enableNestedSroll != enableNested) {
        SetNestedScroll(node, pattern);
    }
    if (enableNestedSroll == false && enableNestedSroll != enableNested) {
        UnSetNestedScroll(node, pattern);
    }
}

void ScrollBarModelNG::SetEnableNestedScroll(FrameNode* frameNode, std::optional<bool> enableNestedSroll)
{
    SetEnableNestedScroll(frameNode, enableNestedSroll.value_or(false));
}
} // namespace OHOS::Ace::NG
