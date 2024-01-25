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

#include "core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.h"

#include "base/memory/referenced.h"
#include "base/subwindow/subwindow.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MAX_RECOVER_BUTTON_INDEX = 0;
constexpr int32_t MINIMIZE_BUTTON_INDEX = 1;
constexpr int32_t CLOSE_BUTTON_INDEX = 2;
constexpr double UNFOCUS_ALPHA = 0.4;
constexpr double FOCUS_ALPHA = 1.0;
constexpr int32_t TITLE_POPUP_DURATION = 200;
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
    auto stackNode = GetStackNode();
    CHECK_NULL_VOID(stackNode);
    auto windowManager = pipelineContext->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    windowMode_ = windowManager->GetWindowMode();
    isShow =isShow && hasDeco;
    // set container window show state to RS
    pipelineContext->SetContainerWindow(isShow);
    // update container modal padding and border
    auto layoutProperty = containerNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateAlignment(Alignment::TOP_LEFT);
    PaddingProperty padding;
    if (isShow && customTitleSettedShow_) {
        padding = { CalcLength(CONTENT_PADDING), CalcLength(CONTENT_PADDING), std::nullopt,
            CalcLength(CONTENT_PADDING) };
    }
    layoutProperty->UpdatePadding(padding);
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(isShow ? CONTAINER_BORDER_WIDTH : 0.0_vp);
    layoutProperty->UpdateBorderWidth(borderWidth);
    auto renderContext = containerNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(isFocus_ ? CONTAINER_BACKGROUND_COLOR : CONTAINER_BACKGROUND_COLOR_LOST_FOCUS);

    // update stack content border
    auto stackLayoutProperty = stackNode->GetLayoutProperty();
    CHECK_NULL_VOID(stackLayoutProperty);
    stackLayoutProperty->UpdateLayoutWeight(1.0f);
    auto stackRenderContext = stackNode->GetRenderContext();
    CHECK_NULL_VOID(stackRenderContext);
    BorderRadiusProperty stageBorderRadius;
    stageBorderRadius.SetRadius(isShow ? CONTAINER_INNER_RADIUS : 0.0_vp);
    stackRenderContext->UpdateBorderRadius(stageBorderRadius);
    stackRenderContext->SetClipToBounds(true);
    auto customTitleLayoutProperty = customTitleRow->GetLayoutProperty();
    CHECK_NULL_VOID(customTitleLayoutProperty);
    customTitleLayoutProperty->UpdateVisibility((isShow && customTitleSettedShow_) ? VisibleType::VISIBLE
        : VisibleType::GONE);

    auto floatingLayoutProperty = floatingTitleRow->GetLayoutProperty();
    CHECK_NULL_VOID(floatingLayoutProperty);
    floatingLayoutProperty->UpdateVisibility(VisibleType::GONE);
    auto controlButtonsNode = GetControlButtonRow();
    CHECK_NULL_VOID(controlButtonsNode);
    auto controlButtonsLayoutProperty = controlButtonsNode->GetLayoutProperty();
    CHECK_NULL_VOID(controlButtonsLayoutProperty);
    AddOrRemovePanEvent(controlButtonsNode);
    ChangeFloatingTitle(isFocus_);
    ChangeControlButtons(isFocus_);
    auto controlButtonsContext = controlButtonsNode->GetRenderContext();
    CHECK_NULL_VOID(controlButtonsContext);
    controlButtonsContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
    controlButtonsLayoutProperty->UpdateVisibility(isShow ? VisibleType::VISIBLE : VisibleType::GONE);
}

RefPtr<UINode> ContainerModalPatternEnhance::GetTitleItemByIndex(
    const RefPtr<FrameNode>& controlButtonsNode, int32_t originIndex)
{
    return controlButtonsNode->GetChildAtIndex(originIndex);
}

void ContainerModalPatternEnhance::OnWindowFocused()
{
    ContainerModalPattern::OnWindowFocused();
}

void ContainerModalPatternEnhance::OnWindowUnfocused()
{
    if (SubwindowManager::GetInstance()->GetCurrentWindow() &&
        SubwindowManager::GetInstance()->GetCurrentWindow()->GetShown()) {
        SetIsFocus(false);
        return;
    }
    ContainerModalPattern::OnWindowUnfocused();
}

void ContainerModalPatternEnhance::OnWindowForceUnfocused()
{
    if (!GetIsFocus()) {
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
    auto windowManager = pipeline->GetWindowManager();
    MaximizeMode mode = windowManager->GetCurrentWindowMaximizeMode();
    InternalResource::ResourceId maxId =
        (mode == MaximizeMode::MODE_AVOID_SYSTEM_BAR
            || windowMode_ == WindowMode::WINDOW_MODE_FULLSCREEN
            || windowMode_ == WindowMode::WINDOW_MODE_SPLIT_PRIMARY
            || windowMode_ == WindowMode::WINDOW_MODE_SPLIT_SECONDARY)
            ? InternalResource::ResourceId::IC_WINDOW_RESTORES
            : InternalResource::ResourceId::IC_WINDOW_MAX;
    ChangeTitleButtonIcon(maximizeButton, maxId, isFocus);

    // update minimize button
    auto minimizeButton =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MINIMIZE_BUTTON_INDEX));
    ChangeTitleButtonIcon(minimizeButton, InternalResource::ResourceId::IC_WINDOW_MIN, isFocus);

    // update close button
    auto closeButton = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, CLOSE_BUTTON_INDEX));
    ChangeTitleButtonIcon(closeButton, InternalResource::ResourceId::IC_WINDOW_CLOSE, isFocus);
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

    // update floating custom title label
    auto customFloatingTitleNode = GetFloatingTitleNode();
    CHECK_NULL_VOID(customFloatingTitleNode);
    isFocus ? customFloatingTitleNode->FireOnWindowFocusedCallback()
            : customFloatingTitleNode->FireOnWindowUnfocusedCallback();
}

void ContainerModalPatternEnhance::ChangeTitleButtonIcon(
    const RefPtr<FrameNode>& buttonNode, InternalResource::ResourceId icon, bool isFocus)
{
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateOpacity(isFocus ? FOCUS_ALPHA : UNFOCUS_ALPHA);
    ContainerModalPattern::ChangeTitleButtonIcon(buttonNode, icon, isFocus);
}

void ContainerModalPatternEnhance::SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize)
{
    auto controlButtonsNode = GetControlButtonRow();
    CHECK_NULL_VOID(controlButtonsNode);
    ContainerModalViewEnhance::SetEnableSplit(!hideSplit);

    if (hideMaximize) {
        auto maximizeBtn =
            AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MAX_RECOVER_BUTTON_INDEX));
        CHECK_NULL_VOID(maximizeBtn);
        maximizeBtn->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
        maximizeBtn->MarkDirtyNode();
    }

    if (hideMinimize) {
        auto minimizeBtn =
            AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MINIMIZE_BUTTON_INDEX));
        CHECK_NULL_VOID(minimizeBtn);
        minimizeBtn->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
        minimizeBtn->MarkDirtyNode();
    }
}

bool ContainerModalPatternEnhance::CanHideFloatingTitle()
{
    auto controlButtonsNode = GetControlButtonRow();
    CHECK_NULL_RETURN(controlButtonsNode, true);
    auto maximizeBtn = GetTitleItemByIndex(controlButtonsNode, MAX_RECOVER_BUTTON_INDEX);
    CHECK_NULL_RETURN(maximizeBtn, true);
    auto subwindowManager = SubwindowManager::GetInstance();
    CHECK_NULL_RETURN(subwindowManager, true);
    auto subwindow = subwindowManager->GetSubwindow(Container::CurrentId());
    CHECK_NULL_RETURN(subwindow, true);
    auto overlayManager = subwindow->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, true);
    auto menu = overlayManager->GetMenuNode(maximizeBtn->GetId());
    // current MaximizeBtnMenu is null!
    if (menu == nullptr) {
        return true;
    }
    return !subwindow->GetShown();
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

    auto titlePopupDistance = CONTAINER_TITLE_HEIGHT.ConvertToPx();
    AnimationOption option;
    option.SetDuration(TITLE_POPUP_DURATION);
    option.SetCurve(Curves::EASE_IN_OUT);

    if (isShow && this->CanShowFloatingTitle()) {
        floatingContext->OnTransformTranslateUpdate({ 0.0f, height - static_cast<float>(titlePopupDistance), 0.0f });
        floatingLayoutProperty->UpdateVisibility(floatingTitleSettedShow_ ? VisibleType::VISIBLE : VisibleType::GONE);
        AnimationUtils::Animate(option, [floatingContext, height]() {
            floatingContext->OnTransformTranslateUpdate({ 0.0f, height, 0.0f });
        });
        buttonsContext->OnTransformTranslateUpdate({ 0.0f, height - static_cast<float>(titlePopupDistance), 0.0f });
        controlButtonsLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        AnimationUtils::Animate(option, [buttonsContext, height]() {
            buttonsContext->OnTransformTranslateUpdate({ 0.0f, height, 0.0f });
        });
    }

    if (!isShow && this->CanHideFloatingTitle()) {
        AnimationUtils::Animate(
            option,
            [floatingContext, buttonsContext, titlePopupDistance, height]() {
                floatingContext->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(titlePopupDistance)- height,
                    0.0f });
                buttonsContext->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(titlePopupDistance) - height,
                    0.0f });
            },
            [floatingLayoutProperty, id = Container::CurrentId()]() {
                ContainerScope scope(id);
                auto taskExecutor = Container::CurrentTaskExecutor();
                CHECK_NULL_VOID(taskExecutor);
                taskExecutor->PostTask(
                    [floatingLayoutProperty]() { floatingLayoutProperty->UpdateVisibility(VisibleType::GONE); },
                    TaskExecutor::TaskType::UI);
            });
    }
}
} // namespace OHOS::Ace::NG
