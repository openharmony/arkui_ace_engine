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

#include "core/components_ng/pattern/side_bar/side_bar_container_view.h"

#include "base/geometry/dimension.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_property.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

namespace {
constexpr Dimension DEFAULT_CONTROL_BUTTON_WIDTH = 32.0_vp;
constexpr Dimension DEFAULT_CONTROL_BUTTON_HEIGHT = 32.0_vp;
} // namespace

void SideBarContainerView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto sideBarContainerNode = FrameNode::GetOrCreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SideBarContainerPattern>(); });

    ViewStackProcessor::GetInstance()->Push(sideBarContainerNode);
}

void SideBarContainerView::Pop()
{
    auto sideBarContainerNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(sideBarContainerNode);

    auto children = sideBarContainerNode->GetChildren();
    if (children.empty()) {
        LOGE("SideBarContainerView::Pop children is null.");
        return;
    }

    auto sideBarNode = children.front();
    sideBarNode->MovePosition(DEFAULT_NODE_SLOT);
    sideBarContainerNode->RebuildRenderContextTree();

    CreateAndMountControlButton(sideBarContainerNode);
}

void SideBarContainerView::CreateAndMountControlButton(const RefPtr<FrameNode>& parentNode)
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

    auto imgWidth = layoutProperty->GetControlButtonWidth().value_or(DEFAULT_CONTROL_BUTTON_WIDTH);
    auto imgHeight = layoutProperty->GetControlButtonHeight().value_or(DEFAULT_CONTROL_BUTTON_HEIGHT);
    info.SetDimension(imgWidth, imgHeight);

    int32_t imgNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imgNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imgNodeId, AceType::MakeRefPtr<ImagePattern>());

    auto imgHub = imgNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(imgHub);
    auto gestureHub = imgHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto parentPattern = parentNode->GetPattern<SideBarContainerPattern>();
    parentPattern->InitControlButtonTouchEvent(gestureHub);

    auto imageLayoutProperty = imgNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    imageLayoutProperty->UpdateImageSourceInfo(info);
    auto showControlButton = layoutProperty->GetShowControlButton().value_or(true);
    if (!showControlButton) {
        imageLayoutProperty->UpdateVisibility(VisibleType::GONE);
    }

    auto imgRenderContext = imgNode->GetRenderContext();
    imgRenderContext->UpdateBackgroundColor(Color::RED);

    imgNode->MountToParent(parentNode);
}

void SideBarContainerView::SetSideBarContainerType(SideBarContainerType type)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarContainerType, type);
}

void SideBarContainerView::SetShowSideBar(bool isShow)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ShowSideBar, isShow);
}

void SideBarContainerView::SetShowControlButton(bool showControlButton)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ShowControlButton, showControlButton);
}

void SideBarContainerView::SetSideBarWidth(const Dimension& sideBarWidth)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarWidth, sideBarWidth);
}

void SideBarContainerView::SetMinSideBarWidth(const Dimension& minSideBarWidth)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinSideBarWidth, minSideBarWidth);
}

void SideBarContainerView::SetMaxSideBarWidth(const Dimension& maxSideBarWidth)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MaxSideBarWidth, maxSideBarWidth);
}

void SideBarContainerView::SetAutoHide(bool autoHide)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, AutoHide, autoHide);
}

void SideBarContainerView::SetSideBarPosition(SideBarPosition sideBarPosition)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarPosition, sideBarPosition);
}

void SideBarContainerView::SetControlButtonWidth(const Dimension& width)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonWidth, width);
}

void SideBarContainerView::SetControlButtonHeight(const Dimension& height)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonHeight, height);
}

void SideBarContainerView::SetControlButtonLeft(const Dimension& left)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonLeft, left);
}

void SideBarContainerView::SetControlButtonTop(const Dimension& top)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonTop, top);
}

void SideBarContainerView::SetControlButtonShowIconStr(const std::string& showIconStr)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonShowIconStr, showIconStr);
}

void SideBarContainerView::SetControlButtonHiddenIconStr(const std::string& hiddenIconStr)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonHiddenIconStr, hiddenIconStr);
}

void SideBarContainerView::SetControlButtonSwitchingIconStr(const std::string& switchingIconStr)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonSwitchingIconStr, switchingIconStr);
}

void SideBarContainerView::SetOnChange(ChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SideBarContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

} // namespace OHOS::Ace::NG
