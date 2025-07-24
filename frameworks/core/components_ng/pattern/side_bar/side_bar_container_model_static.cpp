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

#include "core/components_ng/pattern/side_bar/side_bar_container_model_static.h"

#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"

namespace OHOS::Ace::NG {
namespace {
static Dimension DEFAULT_MIN_CONTENT_WIDTH = 0.0_vp;
static Dimension DEFAULT_SIDE_BAR_WIDTH = 200.0_vp;
static Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
ImageSourceInfo CreateSourceInfo(const std::string& src, bool isPixelMap, RefPtr<PixelMap>& pixMap)
{
#if defined(PIXEL_MAP_SUPPORTED)
    if (isPixelMap && pixMap) {
        return ImageSourceInfo(pixMap);
    }
#endif
    return ImageSourceInfo(src);
}
} // namespace
bool SideBarContainerModelStatic::sideBarWidthDoubleBind_ = false;

RefPtr<FrameNode> SideBarContainerModelStatic::CreateFrameNode(int32_t nodeId)
{
    DEFAULT_SIDE_BAR_WIDTH = 240.0_vp;
    DEFAULT_MIN_SIDE_BAR_WIDTH = 240.0_vp;
    DEFAULT_MIN_CONTENT_WIDTH = 360.0_vp;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SideBarContainerPattern>(); });
    CHECK_NULL_RETURN(frameNode, frameNode);
    return frameNode;
}

void SideBarContainerModelStatic::SetSideBarContainerType(
    FrameNode* frameNode, const std::optional<SideBarContainerType>& type)
{
    if (type.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarContainerType, type.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarContainerType, frameNode);
    }
}

void SideBarContainerModelStatic::SetSideBarWidth(FrameNode* frameNode, const std::optional<Dimension>& sideBarWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(pattern);
    if (IsDoubleBindBlock(pattern)) {
        return;
    }
    MarkNeedInitRealSideBarWidth(frameNode);
    if (sideBarWidth.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarWidth, sideBarWidth.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarWidth, frameNode);
    }
}

void SideBarContainerModelStatic::SetMinSideBarWidth(
    FrameNode* frameNode, const std::optional<Dimension>& minSideBarWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(pattern);
    if (IsDoubleBindBlock(pattern)) {
        return;
    }
    MarkNeedInitRealSideBarWidth(frameNode);
    if (minSideBarWidth.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SideBarContainerLayoutProperty, MinSideBarWidth, minSideBarWidth.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinSideBarWidth, frameNode);
    }
}

void SideBarContainerModelStatic::SetControlButtonWidth(FrameNode* frameNode, const std::optional<Dimension>& width)
{
    if (width.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonWidth, width.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonWidth, frameNode);
    }
}

void SideBarContainerModelStatic::SetControlButtonHeight(FrameNode* frameNode, const std::optional<Dimension>& height)
{
    if (height.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonHeight, height.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonHeight, frameNode);
    }
}

void SideBarContainerModelStatic::SetControlButtonLeft(FrameNode* frameNode, const Dimension& left)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonLeft, left, frameNode);
}

void SideBarContainerModelStatic::SetControlButtonTop(FrameNode* frameNode, const Dimension& top)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonTop, top, frameNode);
}

void SideBarContainerModelStatic::SetControlButtonShowIconInfo(
    FrameNode* frameNode, const std::string& showIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    auto controlButtonShowIconInfo = CreateSourceInfo(showIconStr, isPixelMap, pixMap);
    if (controlButtonShowIconInfo.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SideBarContainerLayoutProperty, ControlButtonShowIconInfo, controlButtonShowIconInfo, frameNode);
    }
}

void SideBarContainerModelStatic::SetControlButtonHiddenIconInfo(
    FrameNode* frameNode, const std::string& hiddenIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    auto controlButtonHiddenIconInfo = CreateSourceInfo(hiddenIconStr, isPixelMap, pixMap);
    if (controlButtonHiddenIconInfo.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SideBarContainerLayoutProperty, ControlButtonHiddenIconInfo, controlButtonHiddenIconInfo, frameNode);
    }
}

void SideBarContainerModelStatic::SetControlButtonSwitchingIconInfo(
    FrameNode* frameNode, const std::string& switchingIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    auto controlButtonSwitchingIconInfo = CreateSourceInfo(switchingIconStr, isPixelMap, pixMap);
    if (controlButtonSwitchingIconInfo.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SideBarContainerLayoutProperty, ControlButtonSwitchingIconInfo, controlButtonSwitchingIconInfo, frameNode);
    }
}

void SideBarContainerModelStatic::MarkNeedInitRealSideBarWidth(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->MarkNeedInitRealSideBarWidth(true);
}

void SideBarContainerModelStatic::SetShowControlButton(FrameNode* frameNode, bool showControlButton)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ShowControlButton, showControlButton, frameNode);
}

void SideBarContainerModelStatic::SetAutoHide(FrameNode* frameNode, bool autoHide)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, AutoHide, autoHide, frameNode);
}

void SideBarContainerModelStatic::SetMaxSideBarWidth(
    FrameNode* frameNode, const std::optional<Dimension>& maxSideBarWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(pattern);
    if (IsDoubleBindBlock(pattern)) {
        return;
    }
    MarkNeedInitRealSideBarWidth(frameNode);
    if (maxSideBarWidth.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SideBarContainerLayoutProperty, MaxSideBarWidth, maxSideBarWidth.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MaxSideBarWidth, frameNode);
    }
}

void SideBarContainerModelStatic::SetMinContentWidth(
    FrameNode* frameNode, const std::optional<Dimension>& minContentWidth)
{
    if (minContentWidth.has_value()) {
        if (minContentWidth->IsNonNegative()) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(
                SideBarContainerLayoutProperty, MinContentWidth, minContentWidth.value(), frameNode);
        } else {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(
                SideBarContainerLayoutProperty, MinContentWidth, DEFAULT_MIN_CONTENT_WIDTH, frameNode);
        }
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinContentWidth, frameNode);
    }
}

void SideBarContainerModelStatic::SetSideBarPosition(
    FrameNode* frameNode, const std::optional<SideBarPosition>& sideBarPosition)
{
    if (sideBarPosition.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SideBarContainerLayoutProperty, SideBarPosition, sideBarPosition.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarPosition, frameNode);
    }
}

void SideBarContainerModelStatic::SetShowSideBar(FrameNode* frameNode, bool isShow)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ShowSideBar, isShow, frameNode);
}

void SideBarContainerModelStatic::SetDividerStrokeWidth(
    FrameNode* frameNode, const std::optional<Dimension>& strokeWidth)
{
    if (strokeWidth.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SideBarContainerLayoutProperty, DividerStrokeWidth, strokeWidth.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerStrokeWidth, frameNode);
    }
}

void SideBarContainerModelStatic::SetDividerColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerColor, color, frameNode);
}

void SideBarContainerModelStatic::SetDividerStartMargin(FrameNode* frameNode, const Dimension& startMargin)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerStartMargin, startMargin, frameNode);
}

void SideBarContainerModelStatic::SetDividerEndMargin(FrameNode* frameNode, const Dimension& endMargin)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerEndMargin, endMargin, frameNode);
}

void SideBarContainerModelStatic::SetOnChange(FrameNode* frameNode, std::function<void(const bool)>&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SideBarContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void SideBarContainerModelStatic::SetOnChangeEvent(
    FrameNode* frameNode, std::function<void(const bool)>&& onChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SideBarContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}

void SideBarContainerModelStatic::ResetControlButtonLeft(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
        SideBarContainerLayoutProperty, ControlButtonLeft, PROPERTY_UPDATE_LAYOUT, frameNode);
}

void SideBarContainerModelStatic::ResetControlButtonIconInfo(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
        SideBarContainerLayoutProperty, ControlButtonShowIconInfo, PROPERTY_UPDATE_LAYOUT, frameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
        SideBarContainerLayoutProperty, ControlButtonHiddenIconInfo, PROPERTY_UPDATE_LAYOUT, frameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
        SideBarContainerLayoutProperty, ControlButtonSwitchingIconInfo, PROPERTY_UPDATE_LAYOUT, frameNode);
}
bool SideBarContainerModelStatic::IsDoubleBindBlock(const RefPtr<SideBarContainerPattern>& sideBarContainerPattern)
{
    return sideBarWidthDoubleBind_ && sideBarContainerPattern->GetIsInDividerDrag();
}
} // namespace OHOS::Ace::NG
