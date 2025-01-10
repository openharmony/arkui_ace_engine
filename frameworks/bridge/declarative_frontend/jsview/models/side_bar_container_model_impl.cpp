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

#include "bridge/declarative_frontend/jsview/models/side_bar_container_model_impl.h"

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {
void SideBarContainerModelImpl::SetSideBarContainerType(SideBarContainerType type)
{
    std::list<RefPtr<Component>> children;
    auto sideBarContainer = AceType::MakeRefPtr<OHOS::Ace::SideBarContainerComponent>(children);
    ViewStackProcessor::GetInstance()->ClaimElementId(sideBarContainer);
    sideBarContainer->SetMainStackSize(MainStackSize::MAX);
    sideBarContainer->SetSideBarContainerType(type);

    auto stack = ViewStackProcessor::GetInstance();
    stack->Push(sideBarContainer);
    JSInteractableView::SetFocusable(false);
    JSInteractableView::SetFocusNode(true);
}

void SideBarContainerModelImpl::SetShowSideBar(bool isShow)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetShowSideBar(isShow);
}

void SideBarContainerModelImpl::SetShowControlButton(bool showControlButton)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetShowControlButton(showControlButton);
}

void SideBarContainerModelImpl::ParseAndSetWidth(WidthType widthType, Dimension& width, bool isDoubleBind)
{
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    if (width.Unit() == DimensionUnit::PERCENT) {
        component->SetIsPercentSize(width.Unit() == DimensionUnit::PERCENT);
    }
    switch (widthType) {
        case WidthType::SIDEBAR_WIDTH:
            component->SetSideBarWidth(width);
            break;
        case WidthType::MIN_SIDEBAR_WIDTH:
            component->SetSideBarMinWidth(width);
            break;
        case WidthType::MAX_SIDEBAR_WIDTH:
            component->SetSideBarMaxWidth(width);
            break;
        default:
            break;
    }
}

void SideBarContainerModelImpl::SetSideBarWidth(const Dimension& sideBarWidth, bool isDoubleBind) {}

void SideBarContainerModelImpl::SetMinSideBarWidth(const Dimension& minSideBarWidth) {}

void SideBarContainerModelImpl::SetMaxSideBarWidth(const Dimension& maxSideBarWidth) {}

void SideBarContainerModelImpl::SetAutoHide(bool autoHide)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetAutoHide(autoHide);
}

void SideBarContainerModelImpl::SetSideBarPosition(SideBarPosition sideBarPosition)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<SideBarContainerComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetSideBarPosition(sideBarPosition);
}

void SideBarContainerModelImpl::SetControlButtonWidth(const Dimension& width)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto buttonWidth = width.ConvertToVp();
    component->SetButtonWidth(buttonWidth);
}

void SideBarContainerModelImpl::SetControlButtonHeight(const Dimension& height)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto buttonHeight = height.ConvertToVp();
    component->SetButtonHeight(buttonHeight);
}

void SideBarContainerModelImpl::SetControlButtonLeft(const Dimension& left)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto buttonLeft = left.ConvertToVp();
    component->SetButtonLeft(buttonLeft);
}

void SideBarContainerModelImpl::SetControlButtonTop(const Dimension& top)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto buttonTop = top.ConvertToVp();
    component->SetButtonTop(buttonTop);
}

void SideBarContainerModelImpl::SetControlButtonShowIconInfo(
    const std::string& showIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetShowIcon(showIconStr);
}

void SideBarContainerModelImpl::SetControlButtonHiddenIconInfo(
    const std::string& hiddenIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetHiddenIcon(hiddenIconStr);
}

void SideBarContainerModelImpl::SetControlButtonSwitchingIconInfo(
    const std::string& switchingIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetSwitchIcon(switchingIconStr);
}

void SideBarContainerModelImpl::ResetControlButtonIconInfo() {}

void SideBarContainerModelImpl::SetOnChange(std::function<void(const bool)>&& onChange)
{
    JSViewSetProperty(&SideBarContainerComponent::SetOnChange, std::move(onChange));
}

void SideBarContainerModelImpl::SetDividerStrokeWidth(const Dimension& strokeWidth) {}

void SideBarContainerModelImpl::SetDividerColor(const Color& color) {}

void SideBarContainerModelImpl::SetDividerStartMargin(const Dimension& startMargin) {}

void SideBarContainerModelImpl::SetDividerEndMargin(const Dimension& endMargin) {}

void SideBarContainerModelImpl::SetMinContentWidth(const Dimension& minContentWidth) {};

void SideBarContainerModelImpl::MarkNeedInitRealSideBarWidth() {}

void SideBarContainerModelImpl::ResetControlButton() {}
} // namespace OHOS::Ace::Framework
