/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.h"

#include "base/memory/referenced.h"
#include "base/subwindow/subwindow.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MAX_RECOVER_BUTTON_INDEX = 0;
constexpr int32_t MINIMIZE_BUTTON_INDEX = 1;
constexpr int32_t CLOSE_BUTTON_INDEX = 2;
constexpr int32_t TITLE_POPUP_DURATION = 400;
} // namespace

void ContainerModalPatternEnhance::ShowTitle(bool isShow, bool hasDeco, bool needUpdate)
{
    auto containerNode = GetHost();
    CHECK_NULL_VOID(containerNode);
    auto customTitleRow = GetCustomTitleRow();
    CHECK_NULL_VOID(customTitleRow);
    auto floatingTitleRow = GetFloatingTitleRow();
    CHECK_NULL_VOID(floatingTitleRow);
    bool isFocus_ = GetIsFocus();
    if (needUpdate) {
        LOGI("title is need update, isFocus_: %{public}d", isFocus_);
        ChangeCustomTitle(isFocus_);
        ChangeControlButtons(isFocus_);
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ContainerModalTheme>();
    auto stackNode = GetStackNode();
    CHECK_NULL_VOID(stackNode);
    auto windowManager = pipelineContext->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    windowMode_ = windowManager->GetWindowMode();
    isShow = isShow && hasDeco;
    // set container window show state to RS
    pipelineContext->SetContainerWindow(isShow);
    // update container modal padding and border
    auto layoutProperty = containerNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateAlignment(Alignment::TOP_LEFT);
    bool isFloatingWindow = windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth((isFloatingWindow && isShow) ? CONTAINER_BORDER_WIDTH : 0.0_vp);
    layoutProperty->UpdateBorderWidth(borderWidth);
    auto renderContext = containerNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(theme->GetBackGroundColor(isFocus_));
    // only floating window show border
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius((isFloatingWindow && isShow) ? CONTAINER_OUTER_RADIUS : 0.0_vp);
    renderContext->UpdateBorderRadius(borderRadius);
    BorderColorProperty borderColor;
    borderColor.SetColor((isFloatingWindow && isShow) ? CONTAINER_BORDER_COLOR : Color::TRANSPARENT);
    renderContext->UpdateBorderColor(borderColor);

    // update stack content border
    auto stackLayoutProperty = stackNode->GetLayoutProperty();
    CHECK_NULL_VOID(stackLayoutProperty);
    stackLayoutProperty->UpdateLayoutWeight(1.0f);
    auto stackRenderContext = stackNode->GetRenderContext();
    CHECK_NULL_VOID(stackRenderContext);
    BorderRadiusProperty stageBorderRadius;
    stageBorderRadius.SetRadius((isFloatingWindow && isShow) ? GetStackNodeRadius() : 0.0_vp);
    stackRenderContext->UpdateBorderRadius(stageBorderRadius);
    stackRenderContext->SetClipToBounds(true);
    auto customTitleLayoutProperty = customTitleRow->GetLayoutProperty();
    CHECK_NULL_VOID(customTitleLayoutProperty);
    customTitleLayoutProperty->UpdateVisibility(
        (isShow && customTitleSettedShow_) ? VisibleType::VISIBLE : VisibleType::GONE);

    auto floatingLayoutProperty = floatingTitleRow->GetLayoutProperty();
    CHECK_NULL_VOID(floatingLayoutProperty);
    floatingLayoutProperty->UpdateVisibility(VisibleType::GONE);
    auto controlButtonsNode = GetControlButtonRow();
    CHECK_NULL_VOID(controlButtonsNode);
    auto controlButtonsLayoutProperty = controlButtonsNode->GetLayoutProperty();
    CHECK_NULL_VOID(controlButtonsLayoutProperty);
    ChangeFloatingTitle(isFocus_);
    ChangeControlButtons(isFocus_);
    auto controlButtonsContext = controlButtonsNode->GetRenderContext();
    CHECK_NULL_VOID(controlButtonsContext);
    controlButtonsContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
    controlButtonsLayoutProperty->UpdateVisibility(isShow ? VisibleType::VISIBLE : VisibleType::GONE);
    SetControlButtonVisibleBeforeAnim(isShow ? VisibleType::VISIBLE : VisibleType::GONE);
    auto gestureRow = GetGestureRow();
    CHECK_NULL_VOID(gestureRow);
    AddPanEvent(customTitleRow);
    AddPanEvent(gestureRow);
    UpdateGestureRowVisible();
    InitColumnTouchTestFunc();
    controlButtonsNode->SetHitTestMode(HitTestMode::HTMTRANSPARENT_SELF);
    auto stack = GetStackNode();
    CHECK_NULL_VOID(stack);
    stack->UpdateInspectorId(CONTAINER_MODAL_STACK_ID);
}

void ContainerModalPatternEnhance::ClearTapGestureEvent(RefPtr<FrameNode>& containerTitleRow)
{
    auto eventHub = containerTitleRow->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearGesture();
    eventHub->OnModifyDone();
}

RefPtr<UINode> ContainerModalPatternEnhance::GetTitleItemByIndex(
    const RefPtr<FrameNode>& controlButtonsNode, int32_t originIndex)
{
    return controlButtonsNode->GetChildAtIndex(originIndex);
}

void ContainerModalPatternEnhance::OnWindowFocused()
{
    ContainerModalPattern::OnWindowFocused();
    ContainerModalPattern::SetIsHoveredMenu(false);
}

void ContainerModalPatternEnhance::OnWindowUnfocused()
{
    if (SubwindowManager::GetInstance()->GetCurrentWindow() &&
        SubwindowManager::GetInstance()->GetCurrentWindow()->GetShown()) {
        SetIsFocus(false);
        ContainerModalPattern::SetIsHoveredMenu(true);
        return;
    }
    ContainerModalPattern::OnWindowUnfocused();
    ContainerModalPattern::SetIsHoveredMenu(false);
}

void ContainerModalPatternEnhance::OnWindowForceUnfocused()
{
    if (!GetIsFocus()) {
        ContainerModalPattern::SetIsHoveredMenu(false);
        ContainerModalPattern::OnWindowUnfocused();
    }
}

void ContainerModalPatternEnhance::ChangeCustomTitle(bool isFocus)
{
    // update custom title label
    auto customTitleNode = GetCustomTitleNode();
    CHECK_NULL_VOID(customTitleNode);
    isFocus ? customTitleNode->FireOnWindowFocusedCallback() : customTitleNode->FireOnWindowUnfocusedCallback();
}

void ContainerModalPatternEnhance::ChangeControlButtons(bool isFocus)
{
    auto controlButtonsNode = GetControlButtonRow();
    CHECK_NULL_VOID(controlButtonsNode);

    // update maximize button
    auto maximizeButton =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MAX_RECOVER_BUTTON_INDEX));
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    MaximizeMode mode = windowManager->GetCurrentWindowMaximizeMode();
    InternalResource::ResourceId maxId =
        (mode == MaximizeMode::MODE_AVOID_SYSTEM_BAR || windowMode_ == WindowMode::WINDOW_MODE_FULLSCREEN ||
            windowMode_ == WindowMode::WINDOW_MODE_SPLIT_PRIMARY ||
            windowMode_ == WindowMode::WINDOW_MODE_SPLIT_SECONDARY)
            ? InternalResource::ResourceId::IC_WINDOW_RESTORES
            : InternalResource::ResourceId::IC_WINDOW_MAX;
    ChangeTitleButtonIcon(maximizeButton, maxId, isFocus, false);

    // update minimize button
    auto minimizeButton =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MINIMIZE_BUTTON_INDEX));
    ChangeTitleButtonIcon(minimizeButton, InternalResource::ResourceId::IC_WINDOW_MIN, isFocus, false);

    // update close button
    auto closeButton = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, CLOSE_BUTTON_INDEX));
    ChangeTitleButtonIcon(closeButton, InternalResource::ResourceId::IC_WINDOW_CLOSE, isFocus, true);
}

void ContainerModalPatternEnhance::ChangeFloatingTitle(bool isFocus)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);

    if (windowManager->GetWindowMode() != WindowMode::WINDOW_MODE_FLOATING &&
        windowManager->GetWindowMode() != WindowMode::WINDOW_MODE_FULLSCREEN) {
        windowManager->SetCurrentWindowMaximizeMode(MaximizeMode::MODE_RECOVER);
    }

    auto floatingTitleRow = GetFloatingTitleRow();
    CHECK_NULL_VOID(floatingTitleRow);
    auto floatingContext = floatingTitleRow->GetRenderContext();
    CHECK_NULL_VOID(floatingContext);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ContainerModalTheme>();
    floatingContext->UpdateBackgroundColor(theme->GetBackGroundColor(isFocus));
    // update floating custom title label
    auto customFloatingTitleNode = GetFloatingTitleNode();
    CHECK_NULL_VOID(customFloatingTitleNode);
    isFocus ? customFloatingTitleNode->FireOnWindowFocusedCallback()
            : customFloatingTitleNode->FireOnWindowUnfocusedCallback();
}

void ContainerModalPatternEnhance::ChangeTitleButtonIcon(
    const RefPtr<FrameNode>& buttonNode, InternalResource::ResourceId icon, bool isFocus, bool isCloseBtn)
{
    ContainerModalPattern::ChangeTitleButtonIcon(buttonNode, icon, isFocus, isCloseBtn);
}

void ContainerModalPatternEnhance::SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize)
{
    auto controlButtonsNode = GetControlButtonRow();
    CHECK_NULL_VOID(controlButtonsNode);
    ContainerModalViewEnhance::SetEnableSplit(!hideSplit);

    auto maximizeBtn =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MAX_RECOVER_BUTTON_INDEX));
    CHECK_NULL_VOID(maximizeBtn);
    maximizeBtn->GetLayoutProperty()->UpdateVisibility(hideMaximize ? VisibleType::GONE : VisibleType::VISIBLE);
    maximizeBtn->MarkDirtyNode();

    auto minimizeBtn =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MINIMIZE_BUTTON_INDEX));
    CHECK_NULL_VOID(minimizeBtn);
    minimizeBtn->GetLayoutProperty()->UpdateVisibility(hideMinimize ? VisibleType::GONE : VisibleType::VISIBLE);
    minimizeBtn->MarkDirtyNode();

    auto closeBtn = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, CLOSE_BUTTON_INDEX));
    InitTitleRowLayoutProperty(GetCustomTitleRow());
}

void ContainerModalPatternEnhance::UpdateTitleInTargetPos(bool isShow, int32_t height)
{
    auto floatingTitleNode = GetFloatingTitleRow();
    CHECK_NULL_VOID(floatingTitleNode);
    auto floatingLayoutProperty = floatingTitleNode->GetLayoutProperty();
    CHECK_NULL_VOID(floatingLayoutProperty);
    auto floatingContext = floatingTitleNode->GetRenderContext();
    CHECK_NULL_VOID(floatingContext);

    auto controlButtonsNode = GetControlButtonRow();
    CHECK_NULL_VOID(controlButtonsNode);
    auto controlButtonsLayoutProperty = controlButtonsNode->GetLayoutProperty();
    CHECK_NULL_VOID(controlButtonsLayoutProperty);
    auto buttonsContext = controlButtonsNode->GetRenderContext();
    CHECK_NULL_VOID(buttonsContext);

    auto titlePopupDistance = titleHeight_.ConvertToPx();
    auto cubicBezierCurve = AceType::MakeRefPtr<CubicCurve>(0.00, 0.00, 0.20, 1.00);
    AnimationOption option;
    option.SetDuration(TITLE_POPUP_DURATION);
    option.SetCurve(cubicBezierCurve);

    if (isShow && CanShowFloatingTitle()) {
        floatingContext->OnTransformTranslateUpdate({ 0.0f, height - static_cast<float>(titlePopupDistance), 0.0f });
        floatingLayoutProperty->UpdateVisibility(floatingTitleSettedShow_ ? VisibleType::VISIBLE : VisibleType::GONE);
        AnimationUtils::Animate(option, [floatingContext, height]() {
            auto rect = floatingContext->GetPaintRectWithoutTransform();
            floatingContext->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(height - rect.GetY()), 0.0f });
        });
        buttonsContext->OnTransformTranslateUpdate({ 0.0f, height - static_cast<float>(titlePopupDistance), 0.0f });
        SetControlButtonVisibleBeforeAnim(controlButtonsLayoutProperty->GetVisibilityValue());
        controlButtonsLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        AnimationUtils::Animate(option, [buttonsContext, titlePopupDistance, height]() {
            auto rect = buttonsContext->GetPaintRectWithoutTransform();
            buttonsContext->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(height -
                (titlePopupDistance - CONTAINER_TITLE_HEIGHT.ConvertToPx())/2 - rect.GetY()), 0.0f });
        });
    }

    if (!isShow && CanHideFloatingTitle()) {
        auto beforeVisible = GetControlButtonVisibleBeforeAnim();
        AnimationUtils::Animate(
            option,
            [floatingContext, buttonsContext, titlePopupDistance, beforeVisible]() {
                floatingContext->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
                buttonsContext->OnTransformTranslateUpdate({ 0.0f,
                    beforeVisible == VisibleType::VISIBLE ? 0.0f : static_cast<float>(-titlePopupDistance), 0.0f });
            },
            [floatingLayoutProperty, controlButtonsLayoutProperty, beforeVisible, weak = WeakClaim(this)]() {
                auto containerModal = weak.Upgrade();
                CHECK_NULL_VOID(containerModal);
                floatingLayoutProperty->UpdateVisibility(VisibleType::GONE);
                controlButtonsLayoutProperty->UpdateVisibility(containerModal->GetControlButtonVisibleBeforeAnim());
            });
    }
}

void ContainerModalPatternEnhance::EnablePanEventOnNode(
    RefPtr<FrameNode>& node, bool isEnable, const std::string& rowName)
{
    if (!node) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "%{public}s is not exist when set pan event", rowName.c_str());
        return;
    }
    
    if (isEnable) {
        AddPanEvent(node);
    } else {
        RemovePanEvent(node);
    }
}


void ContainerModalPatternEnhance::EnableTapGestureOnNode(
    RefPtr<FrameNode>& node, bool isEnable, const std::string& rowName)
{
    if (!node) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "%{public}s is not exist when set tap gesture", rowName.c_str());
        return;
    }
    
    if (isEnable) {
        SetTapGestureEvent(node);
    } else {
        ClearTapGestureEvent(node);
    }
}

void ContainerModalPatternEnhance::EnableContainerModalGesture(bool isEnable)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "set event on container modal is %{public}d", isEnable);

    auto floatingTitleRow = GetFloatingTitleRow();
    auto customTitleRow = GetCustomTitleRow();
    auto gestureRow = GetGestureRow();
    EnableTapGestureOnNode(floatingTitleRow, isEnable, "floating title row");
    EnablePanEventOnNode(customTitleRow, isEnable, "custom title row");
    EnableTapGestureOnNode(customTitleRow, isEnable, "custom title row");
    EnablePanEventOnNode(gestureRow, isEnable, "gesture row");
    EnableTapGestureOnNode(gestureRow, isEnable, "gesture row");
}

bool ContainerModalPatternEnhance::GetFloatingTitleVisible()
{
    auto floatingTitleRow = GetFloatingTitleRow();
    CHECK_NULL_RETURN(floatingTitleRow, false);
    auto floatingTitleRowProp = floatingTitleRow->GetLayoutProperty();
    CHECK_NULL_RETURN(floatingTitleRowProp, false);
    return (floatingTitleRowProp->GetVisibilityValue() == VisibleType::VISIBLE);
}

bool ContainerModalPatternEnhance::GetCustomTitleVisible()
{
    auto customTitleRow = GetCustomTitleRow();
    CHECK_NULL_RETURN(customTitleRow, false);
    auto customTitleRowProp = customTitleRow->GetLayoutProperty();
    CHECK_NULL_RETURN(customTitleRowProp, false);
    return (customTitleRowProp->GetVisibilityValue() == VisibleType::VISIBLE);
}

bool ContainerModalPatternEnhance::GetControlButtonVisible()
{
    auto controlButtonRow = GetControlButtonRow();
    CHECK_NULL_RETURN(controlButtonRow, false);
    auto controlButtonRowProp = controlButtonRow->GetLayoutProperty();
    CHECK_NULL_RETURN(controlButtonRowProp, false);
    return (controlButtonRowProp->GetVisibilityValue() == VisibleType::VISIBLE);
}
} // namespace OHOS::Ace::NG
