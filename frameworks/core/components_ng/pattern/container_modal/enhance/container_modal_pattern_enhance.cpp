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
    auto containerNode = GetHost();
    CHECK_NULL_VOID(containerNode);
    auto columnNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildren().front());
    CHECK_NULL_VOID(columnNode);
    auto rowNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    CHECK_NULL_VOID(rowNode);
    auto customTitleNode = AceType::DynamicCast<CustomTitleNode>(rowNode->GetChildren().front());
    CHECK_NULL_VOID(customTitleNode);
    isFocus ? customTitleNode->FireOnWindowFocusedCallback() : customTitleNode->FireOnWindowUnfocusedCallback();
}

void ContainerModalPatternEnhance::ChangeControlButtons(bool isFocus)
{
    auto containerNode = GetHost();
    CHECK_NULL_VOID(containerNode);
    auto controlButtonsNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildren().back());
    CHECK_NULL_VOID(controlButtonsNode);

    // update maximize button
    auto maximizeButton =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MAX_RECOVER_BUTTON_INDEX));
    auto pipeline = PipelineContext::GetCurrentContext();
    auto windowManager = pipeline->GetWindowManager();
    MaximizeMode mode = windowManager->GetCurrentWindowMaximizeMode();
    InternalResource::ResourceId maxId =
        (mode == MaximizeMode::MODE_AVOID_SYSTEM_BAR || windowMode_ == WindowMode::WINDOW_MODE_FULLSCREEN)
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
    auto containerNode = GetHost();
    CHECK_NULL_VOID(containerNode);
    auto floatingNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildAtIndex(1));
    CHECK_NULL_VOID(floatingNode);
    auto customFloatingTitleNode = AceType::DynamicCast<CustomTitleNode>(floatingNode->GetChildren().front());
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto controlButtonsNode = AceType::DynamicCast<FrameNode>(host->GetChildren().back());
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
    auto containerNode = GetHost();
    CHECK_NULL_RETURN(containerNode, true);
    auto controlButtonsNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildren().back());
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
    auto containerNode = GetHost();
    CHECK_NULL_VOID(containerNode);
    auto floatingTitleNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildAtIndex(1));
    CHECK_NULL_VOID(floatingTitleNode);
    auto floatingLayoutProperty = floatingTitleNode->GetLayoutProperty();
    CHECK_NULL_VOID(floatingLayoutProperty);
    auto floatingContext = floatingTitleNode->GetRenderContext();
    CHECK_NULL_VOID(floatingContext);

    auto controlButtonsNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildren().back());
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
        floatingLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
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
            [floatingContext, buttonsContext, titlePopupDistance]() {
                floatingContext->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
                buttonsContext->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
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
