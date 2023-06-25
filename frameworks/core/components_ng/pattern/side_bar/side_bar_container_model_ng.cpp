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

#include "core/components_ng/pattern/side_bar/side_bar_container_model_ng.h"

#include "base/geometry/dimension.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_property.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_MIN_CHILDREN_SIZE_WITHOUT_BUTTON_AND_DIVIDER = 1;
constexpr Dimension DEFAULT_DIVIDER_STROKE_WIDTH = 1.0_vp;
constexpr Color DEFAULT_DIVIDER_COLOR = Color(0x08000000);
constexpr Dimension DEFAULT_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MAX_SIDE_BAR_WIDTH = 280.0_vp;
constexpr Dimension DEFAULT_MIN_CONTENT_WIDTH = 360.0_vp;
} // namespace

void SideBarContainerModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto sideBarContainerNode = FrameNode::GetOrCreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SideBarContainerPattern>(); });

    CHECK_NULL_VOID(sideBarContainerNode);

    stack->Push(sideBarContainerNode);
}

void SideBarContainerModelNG::Pop()
{
    auto sideBarContainerNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(sideBarContainerNode);

    auto children = sideBarContainerNode->GetChildren();
    if (children.size() < DEFAULT_MIN_CHILDREN_SIZE_WITHOUT_BUTTON_AND_DIVIDER) {
        LOGE("SideBarContainerView::Pop children's size is wrong[%{public}zu].", children.size());
        return;
    }

    auto pattern = sideBarContainerNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(pattern);

    if (pattern->HasControlButton()) {
        return;
    }

    auto sideBarNode = children.front();
    sideBarNode->MovePosition(DEFAULT_NODE_SLOT);
    sideBarContainerNode->RebuildRenderContextTree();

    CreateAndMountDivider(sideBarContainerNode);
    CreateAndMountControlButton(sideBarContainerNode);
    NG::ViewStackProcessor::GetInstance()->PopContainer();
}

void SideBarContainerModelNG::CreateAndMountControlButton(const RefPtr<NG::FrameNode>& parentNode)
{
    auto layoutProperty = parentNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto showSideBar = layoutProperty->GetShowSideBar().value_or(true);

    ImageSourceInfo info((std::string()));
    if (showSideBar) {
        if (layoutProperty->GetControlButtonShowIconStr().has_value()) {
            info.SetSrc(layoutProperty->GetControlButtonShowIconStr().value());
        } else {
            info.SetResourceId(InternalResource::ResourceId::SIDE_BAR);
        }
    } else {
        if (layoutProperty->GetControlButtonHiddenIconStr().has_value()) {
            info.SetSrc(layoutProperty->GetControlButtonHiddenIconStr().value());
        } else {
            info.SetResourceId(InternalResource::ResourceId::SIDE_BAR);
        }
    }

    int32_t imgNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imgNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, imgNodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });

    auto imgHub = imgNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(imgHub);
    auto gestureHub = imgHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto parentPattern = parentNode->GetPattern<SideBarContainerPattern>();
    parentPattern->SetHasControlButton(true);
    parentPattern->InitControlButtonTouchEvent(gestureHub);

    auto imageLayoutProperty = imgNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    imageLayoutProperty->UpdateImageSourceInfo(info);
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);

    imgNode->MountToParent(parentNode);
    imgNode->MarkModifyDone();
}

void SideBarContainerModelNG::CreateAndMountDivider(const RefPtr<NG::FrameNode>& parentNode)
{
    CHECK_NULL_VOID(parentNode);
    auto layoutProperty = parentNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto dividerColor = layoutProperty->GetDividerColor().value_or(DEFAULT_DIVIDER_COLOR);
    auto dividerStrokeWidth = layoutProperty->GetDividerStrokeWidth().value_or(DEFAULT_DIVIDER_STROKE_WIDTH);

    int32_t dividerNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dividerNode = FrameNode::GetOrCreateFrameNode(
        V2::DIVIDER_ETS_TAG, dividerNodeId, []() { return AceType::MakeRefPtr<DividerPattern>(); });

    auto dividerHub = dividerNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(dividerHub);
    auto inputHub = dividerHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto parentPattern = parentNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(parentPattern);
    parentPattern->InitDividerMouseEvent(inputHub);

    auto dividerRenderProperty = dividerNode->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_VOID(dividerRenderProperty);
    dividerRenderProperty->UpdateDividerColor(dividerColor);

    auto dividerLayoutProperty = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_VOID(dividerLayoutProperty);
    dividerLayoutProperty->UpdateVertical(true);
    dividerLayoutProperty->UpdateStrokeWidth(dividerStrokeWidth);

    dividerNode->MountToParent(parentNode);
    dividerNode->MarkModifyDone();
}

void SideBarContainerModelNG::SetSideBarContainerType(SideBarContainerType type)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarContainerType, type);
}

void SideBarContainerModelNG::SetShowSideBar(bool isShow)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ShowSideBar, isShow);
}

void SideBarContainerModelNG::SetShowControlButton(bool showControlButton)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ShowControlButton, showControlButton);
}

void SideBarContainerModelNG::ParseAndSetWidth(WidthType widthType, Dimension& width)
{
    switch (widthType) {
        case WidthType::SIDEBAR_WIDTH:
            SetSideBarWidth(width.IsNonNegative() ? width : DEFAULT_SIDE_BAR_WIDTH);
            break;
        case WidthType::MIN_SIDEBAR_WIDTH:
            SetMinSideBarWidth(width.IsNonNegative() ? width : DEFAULT_MIN_SIDE_BAR_WIDTH);
            break;
        case WidthType::MAX_SIDEBAR_WIDTH:
            SetMaxSideBarWidth(width.IsNonNegative() ? width : DEFAULT_MAX_SIDE_BAR_WIDTH);
            break;
        default:
            break;
    }
}

void SideBarContainerModelNG::SetSideBarWidth(const Dimension& sideBarWidth)
{
    MarkNeedInitRealSideBarWidth();
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarWidth, sideBarWidth);
}

void SideBarContainerModelNG::SetMinSideBarWidth(const Dimension& minSideBarWidth)
{
    MarkNeedInitRealSideBarWidth();
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinSideBarWidth, minSideBarWidth);
}

void SideBarContainerModelNG::SetMaxSideBarWidth(const Dimension& maxSideBarWidth)
{
    MarkNeedInitRealSideBarWidth();
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MaxSideBarWidth, maxSideBarWidth);
}

void SideBarContainerModelNG::SetAutoHide(bool autoHide)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, AutoHide, autoHide);
}

void SideBarContainerModelNG::SetSideBarPosition(SideBarPosition sideBarPosition)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarPosition, sideBarPosition);
}

void SideBarContainerModelNG::SetControlButtonWidth(const Dimension& width)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonWidth, width);
}

void SideBarContainerModelNG::SetControlButtonHeight(const Dimension& height)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonHeight, height);
}

void SideBarContainerModelNG::SetControlButtonLeft(const Dimension& left)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonLeft, left);
}

void SideBarContainerModelNG::SetControlButtonTop(const Dimension& top)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonTop, top);
}

void SideBarContainerModelNG::SetControlButtonShowIconStr(const std::string& showIconStr)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonShowIconStr, showIconStr);
}

void SideBarContainerModelNG::SetControlButtonHiddenIconStr(const std::string& hiddenIconStr)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonHiddenIconStr, hiddenIconStr);
}

void SideBarContainerModelNG::SetControlButtonSwitchingIconStr(const std::string& switchingIconStr)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonSwitchingIconStr, switchingIconStr);
}

void SideBarContainerModelNG::SetDividerStrokeWidth(const Dimension& strokeWidth)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerStrokeWidth, strokeWidth);
}

void SideBarContainerModelNG::SetDividerColor(const Color& color)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerColor, color);
}

void SideBarContainerModelNG::SetDividerStartMargin(const Dimension& startMargin)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerStartMargin, startMargin);
}

void SideBarContainerModelNG::SetDividerEndMargin(const Dimension& endMargin)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerEndMargin, endMargin);
}

void SideBarContainerModelNG::SetMinContentWidth(const Dimension& minContentWidth)
{
    if (minContentWidth.IsNonNegative()) {
        ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinContentWidth, minContentWidth);
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinContentWidth, DEFAULT_MIN_CONTENT_WIDTH);
    }
}

void SideBarContainerModelNG::SetOnChange(std::function<void(const bool)>&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SideBarContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void SideBarContainerModelNG::MarkNeedInitRealSideBarWidth()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->MarkNeedInitRealSideBarWidth(true);
}

void SideBarContainerModelNG::SetOnChangeEvent(std::function<void(const bool)>&& onChangeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SideBarContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}
} // namespace OHOS::Ace::NG
