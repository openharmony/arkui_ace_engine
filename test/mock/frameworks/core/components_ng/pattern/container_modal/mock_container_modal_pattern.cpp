/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/button/button_event_hub.h"

namespace OHOS::Ace::NG {
void ContainerModalPattern::OnColorConfigurationUpdate() {}

void ContainerModalPattern::CallSetContainerWindow(bool considerFloatingWindow)
{
    (void)considerFloatingWindow;
}

void ContainerModalPattern::OnWindowActivated()
{
    isFocus_ = true;
}

void ContainerModalPattern::OnWindowDeactivated()
{
    isFocus_ = false;
}

void ContainerModalPattern::OnWindowForceUnfocused()
{
}

void ContainerModalPattern::Init() {}

void ContainerModalPattern::ShowTitle(bool isShow, bool hasDeco, bool needUpdate)
{
    (void)needUpdate;
    isTitleShow_ = isShow;
    hasDeco_ = hasDeco;
}

void ContainerModalPattern::SetAppTitle(const std::string& title)
{
    appLabel_ = title;
}

void ContainerModalPattern::SetAppIcon(const RefPtr<PixelMap>& icon)
{
    (void)icon;
}

void ContainerModalPattern::SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose)
{
    (void)hideMaximize;
    (void)hideMinimize;
    (void)hideClose;
    hideSplitButton_ = hideSplit;
}

void ContainerModalPattern::SetCloseButtonStatus(bool isEnabled)
{
    auto host = GetHost();
    if (!host || host->GetChildren().empty()) {
        return;
    }
    auto columnNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    if (!columnNode || columnNode->GetChildren().empty()) {
        return;
    }
    auto titleNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    if (!titleNode) {
        return;
    }
    auto closeButton = AceType::DynamicCast<FrameNode>(titleNode->GetChildAtIndex(5));
    if (!closeButton) {
        return;
    }
    auto buttonEvent = closeButton->GetEventHub<ButtonEventHub>();
    if (buttonEvent) {
        buttonEvent->SetEnabled(isEnabled);
    }
}

void ContainerModalPattern::SetWindowContainerColor(const Color& activeColor, const Color& inactiveColor)
{
    activeColor_ = activeColor;
    inactiveColor_ = inactiveColor;
}

void ContainerModalPattern::SetContainerModalTitleHeight(int32_t height)
{
    titleHeight_ = Dimension(static_cast<double>(height));
}

bool ContainerModalPattern::GetContainerModalButtonsRect(RectF& containerModal, RectF& buttons)
{
    containerModal = RectF();
    buttons = RectF();
    return false;
}

void ContainerModalPattern::SubscribeContainerModalButtonsRectChange(
    std::function<void(RectF& containerModal, RectF& buttons)>&& callback)
{
    controlButtonsRectChangeCallback_ = std::move(callback);
}

void ContainerModalPattern::WindowFocus(bool isFocus)
{
    isFocus_ = isFocus;
}

void ContainerModalPattern::SetContainerModalTitleVisible(bool customTitleSettedShow, bool floatingTitleSettedShow)
{
    customTitleSettedShow_ = customTitleSettedShow;
    floatingTitleSettedShow_ = floatingTitleSettedShow;
}

bool ContainerModalPattern::GetContainerModalTitleVisible(bool isImmersive)
{
    return isImmersive ? floatingTitleSettedShow_ : customTitleSettedShow_;
}

void ContainerModalPattern::SetContainerModalTitleWithoutButtonsHeight(Dimension height)
{
    (void)height;
}

void ContainerModalPattern::SetControlButtonsRowHeight(Dimension height)
{
    (void)height;
}

int32_t ContainerModalPattern::GetContainerModalTitleHeight()
{
    return 0;
}

Dimension ContainerModalPattern::GetCustomTitleHeight()
{
    return Dimension(0.0);
}

void ContainerModalPattern::GetWindowPaintRectWithoutMeasureAndLayout(RectInt& rect)
{
    rect = RectInt();
}

void ContainerModalPattern::GetWindowPaintRectWithoutMeasureAndLayout(Rect& rect, bool isContainerModal)
{
    (void)isContainerModal;
    rect = Rect();
}

void ContainerModalPattern::CallButtonsRectChange() {}

bool ContainerModalPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>&, const DirtySwapConfig&)
{
    return false;
}

void ContainerModalPattern::OnLanguageConfigurationUpdate() {}

void ContainerModalPattern::InitColumnTouchTestFunc() {}

CalcLength ContainerModalPattern::GetControlButtonRowWidth()
{
    return CalcLength(0.0);
}

bool ContainerModalPattern::IsContainerModalTransparent() const
{
    return false;
}

bool ContainerModalPattern::CheckNodeOnContainerModalTitle(const RefPtr<FrameNode>& node)
{
    (void)node;
    return false;
}

void ContainerModalPattern::SetToolbarTitleHeight() {}

void ContainerModalPattern::SetControlButtonsRowHeight() {}

void ContainerModalPattern::UpdateRowHeight(const RefPtr<FrameNode>& row, Dimension height)
{
    (void)row;
    (void)height;
}

void ContainerModalPattern::UpdateGestureRowVisible() {}

void ContainerModalPattern::InitAllTitleRowLayoutProperty() {}

void ContainerModalPattern::AddPanEvent(const RefPtr<FrameNode>& controlButtonsNode)
{
    (void)controlButtonsNode;
}

void ContainerModalPattern::RemovePanEvent(const RefPtr<FrameNode>& controlButtonsNode)
{
    (void)controlButtonsNode;
}

void ContainerModalPattern::ChangeFloatingTitle(bool isFocus)
{
    (void)isFocus;
}

void ContainerModalPattern::ChangeCustomTitle(bool isFocus)
{
    (void)isFocus;
}

void ContainerModalPattern::ChangeControlButtons(bool isFocus)
{
    (void)isFocus;
}

void ContainerModalPattern::ChangeTitleButtonIcon(
    const RefPtr<FrameNode>& buttonNode, InternalResource::ResourceId icon, bool isFocus, bool isCloseBtn)
{
    (void)buttonNode;
    (void)icon;
    (void)isFocus;
    (void)isCloseBtn;
}

void ContainerModalPattern::InitButtonsLayoutProperty() {}
} // namespace OHOS::Ace::NG
