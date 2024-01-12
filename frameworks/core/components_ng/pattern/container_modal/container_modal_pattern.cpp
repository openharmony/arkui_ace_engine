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

#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t LEFT_SPLIT_BUTTON_INDEX = 0;
constexpr int32_t MAX_RECOVER_BUTTON_INDEX = 1;
constexpr int32_t MINIMIZE_BUTTON_INDEX = 2;
constexpr int32_t CLOSE_BUTTON_INDEX = 3;
constexpr int32_t TITLE_POPUP_DURATION = 200;
constexpr double MOUSE_MOVE_POPUP_DISTANCE = 5.0; // 5.0px
constexpr double MOVE_POPUP_DISTANCE_X = 40.0;    // 40.0px
constexpr double MOVE_POPUP_DISTANCE_Y = 20.0;    // 20.0px
constexpr double TITLE_POPUP_DISTANCE = 37.0;     // 37vp height of title
} // namespace

void UpdateRowHeight(const RefPtr<FrameNode>& row, int height)
{
    CHECK_NULL_VOID(row);
    auto layoutProperty = row->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(height, DimensionUnit::PX)));
    row->MarkModifyDone();
    row->MarkDirtyNode();
}

void ContainerModalPattern::ShowTitle(bool isShow, bool hasDeco, bool needUpdate)
{
    auto containerNode = GetHost();
    CHECK_NULL_VOID(containerNode);
    auto customTitleRow = GetCustomTitleRow();
    CHECK_NULL_VOID(customTitleRow);
    auto floatingTitleRow = GetFloatingTitleRow();
    CHECK_NULL_VOID(floatingTitleRow);
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
    hasDeco_ = hasDeco;
    LOGI("ShowTitle isShow: %{public}d, windowMode: %{public}d, hasDeco: %{public}d", isShow, windowMode_, hasDeco_);
    if (!hasDeco_) {
        isShow = false;
    }

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
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(isShow ? CONTAINER_OUTER_RADIUS : 0.0_vp);
    renderContext->UpdateBorderRadius(borderRadius);
    BorderColorProperty borderColor;
    borderColor.SetColor(isShow ? CONTAINER_BORDER_COLOR : Color::TRANSPARENT);
    renderContext->UpdateBorderColor(borderColor);

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
    customTitleLayoutProperty->UpdateVisibility(
        (isShow && customTitleSettedShow_) ? VisibleType::VISIBLE : VisibleType::GONE);
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

void ContainerModalPattern::InitContainerEvent()
{
    bool isChangeTitleStyle = SystemProperties::GetTitleStyleEnabled();
    if (isChangeTitleStyle) {
        return;
    }
    auto containerNode = GetHost();
    CHECK_NULL_VOID(containerNode);
    auto touchEventHub = containerNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(touchEventHub);
    auto controlButtonsNode = GetControlButtonRow();
    CHECK_NULL_VOID(controlButtonsNode);
    auto controlButtonsLayoutProperty = controlButtonsNode->GetLayoutProperty();
    CHECK_NULL_VOID(controlButtonsLayoutProperty);
    auto controlButtonsContext = controlButtonsNode->GetRenderContext();
    CHECK_NULL_VOID(controlButtonsContext);

    auto floatingTitleRow = GetFloatingTitleRow();
    CHECK_NULL_VOID(floatingTitleRow);
    auto floatingLayoutProperty = floatingTitleRow->GetLayoutProperty();
    CHECK_NULL_VOID(floatingLayoutProperty);
    auto floatingContext = floatingTitleRow->GetRenderContext();
    CHECK_NULL_VOID(floatingContext);

    auto titlePopupDistance = TITLE_POPUP_DISTANCE * containerNode->GetContext()->GetDensity();
    AnimationOption option;
    option.SetDuration(TITLE_POPUP_DURATION);
    option.SetCurve(Curves::EASE_IN_OUT);

    // init touch event
    touchEventHub->SetTouchEvent([controlButtonsLayoutProperty, floatingLayoutProperty, controlButtonsContext,
                                     floatingContext, option, titlePopupDistance,
                                     weak = WeakClaim(this)](TouchEventInfo& info) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        if (!container->hasDeco_) {
            return;
        }
        if (info.GetChangedTouches().begin()->GetGlobalLocation().GetY() <= titlePopupDistance) {
            // step1. Record the coordinates of the start of the touch.
            if (info.GetChangedTouches().begin()->GetTouchType() == TouchType::DOWN) {
                container->moveX_ = static_cast<float>(info.GetChangedTouches().begin()->GetGlobalLocation().GetX());
                container->moveY_ = static_cast<float>(info.GetChangedTouches().begin()->GetGlobalLocation().GetY());
                return;
            }
            if (info.GetChangedTouches().begin()->GetTouchType() != TouchType::MOVE ||
                !container->CanShowFloatingTitle()) {
                return;
            }

            // step2. Calculate the coordinates of touch move relative to touch down.
            auto deltaMoveX = fabs(info.GetChangedTouches().begin()->GetGlobalLocation().GetX() - container->moveX_);
            auto deltaMoveY = info.GetChangedTouches().begin()->GetGlobalLocation().GetY() - container->moveY_;
            // step3. If the horizontal distance of the touch move does not exceed 10px and the vertical distance
            // exceeds 20px, the floating title will be displayed.
            if (deltaMoveX <= MOVE_POPUP_DISTANCE_X && deltaMoveY >= MOVE_POPUP_DISTANCE_Y) {
                controlButtonsContext->OnTransformTranslateUpdate(
                    { 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
                controlButtonsLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
                AnimationUtils::Animate(option, [controlButtonsContext]() {
                    controlButtonsContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
                });
                floatingContext->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
                floatingLayoutProperty->UpdateVisibility(
                    container->floatingTitleSettedShow_ ? VisibleType::VISIBLE : VisibleType::GONE);
                AnimationUtils::Animate(option, [floatingContext]() {
                    floatingContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
                });
            }
            return;
        }
        if (info.GetChangedTouches().begin()->GetTouchType() != TouchType::DOWN) {
            return;
        }
        if (floatingLayoutProperty->GetVisibilityValue(VisibleType::GONE) != VisibleType::VISIBLE) {
            return;
        }
        // step4. Touch other area to hide floating title.
        AnimationUtils::Animate(
            option,
            [controlButtonsContext, floatingContext, titlePopupDistance]() {
                controlButtonsContext->OnTransformTranslateUpdate(
                    { 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
                floatingContext->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
            },
            [floatingLayoutProperty, id = Container::CurrentId()]() {
                ContainerScope scope(id);
                auto pipeline = PipelineBase::GetCurrentContext();
                CHECK_NULL_VOID(pipeline);
                auto taskExecutor = pipeline->GetTaskExecutor();
                CHECK_NULL_VOID(taskExecutor);
                taskExecutor->PostTask(
                    [floatingLayoutProperty, id]() {
                        ContainerScope scope(id);
                        floatingLayoutProperty->UpdateVisibility(VisibleType::GONE);
                    },
                    TaskExecutor::TaskType::UI);
            });
    });

    // init mouse event
    auto mouseEventHub = containerNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(mouseEventHub);
    mouseEventHub->SetMouseEvent([controlButtonsLayoutProperty, floatingLayoutProperty, controlButtonsContext,
                                     floatingContext, option, titlePopupDistance,
                                     weak = WeakClaim(this)](MouseInfo& info) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        auto action = info.GetAction();
        if ((action != MouseAction::MOVE && action != MouseAction::WINDOW_LEAVE) || !container->hasDeco_) {
            return;
        }
        if (info.GetLocalLocation().GetY() <= MOUSE_MOVE_POPUP_DISTANCE && container->CanShowFloatingTitle()) {
            controlButtonsContext->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
            controlButtonsLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
            AnimationUtils::Animate(option, [controlButtonsContext]() {
                controlButtonsContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
            });
            floatingContext->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
            floatingLayoutProperty->UpdateVisibility(
                container->floatingTitleSettedShow_ ? VisibleType::VISIBLE : VisibleType::GONE);
            AnimationUtils::Animate(option, [floatingContext]() {
                floatingContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
            });
        }

        if (!container->CanHideFloatingTitle()) {
            return;
        }
        if ((info.GetLocalLocation().GetY() >= titlePopupDistance || action == MouseAction::WINDOW_LEAVE) &&
            floatingLayoutProperty->GetVisibilityValue(VisibleType::GONE) == VisibleType::VISIBLE) {
            AnimationUtils::Animate(
                option,
                [controlButtonsContext, floatingContext, titlePopupDistance]() {
                    controlButtonsContext->OnTransformTranslateUpdate(
                        { 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
                    floatingContext->OnTransformTranslateUpdate(
                        { 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
                },
                [floatingLayoutProperty, id = Container::CurrentId()]() {
                    ContainerScope scope(id);
                    auto pipeline = PipelineBase::GetCurrentContext();
                    CHECK_NULL_VOID(pipeline);
                    auto taskExecutor = pipeline->GetTaskExecutor();
                    CHECK_NULL_VOID(taskExecutor);
                    taskExecutor->PostTask(
                        [floatingLayoutProperty, id]() {
                            ContainerScope scope(id);
                            floatingLayoutProperty->UpdateVisibility(VisibleType::GONE);
                        },
                        TaskExecutor::TaskType::UI);
                });
        }
    });
}

void ContainerModalPattern::AddOrRemovePanEvent(const RefPtr<FrameNode>& controlButtonsNode)
{
    auto eventHub = controlButtonsNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(eventHub);
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;

    if (!panEvent_) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto windowManager = pipeline->GetWindowManager();
        CHECK_NULL_VOID(windowManager);
        // touch the title to move the floating window
        auto panActionStart = [wk = WeakClaim(RawPtr(windowManager))](const GestureEvent&) {
            auto windowManager = wk.Upgrade();
            CHECK_NULL_VOID(windowManager);
            if (windowManager->GetCurrentWindowMaximizeMode() != MaximizeMode::MODE_AVOID_SYSTEM_BAR) {
                windowManager->WindowStartMove();
                SubwindowManager::GetInstance()->ClearToastInSubwindow();
            }
        };
        panEvent_ = MakeRefPtr<PanEvent>(std::move(panActionStart), nullptr, nullptr, nullptr);
    }
    if (windowMode_ != WindowMode::WINDOW_MODE_FULLSCREEN) {
        eventHub->AddPanEvent(panEvent_, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
    } else {
        eventHub->RemovePanEvent(panEvent_);
    }
}

void ContainerModalPattern::OnWindowFocused()
{
    WindowFocus(true);
}

void ContainerModalPattern::OnWindowUnfocused()
{
    WindowFocus(false);
}

void ContainerModalPattern::OnWindowForceUnfocused() {}

void ContainerModalPattern::WindowFocus(bool isFocus)
{
    isFocus_ = isFocus;
    auto containerNode = GetHost();
    CHECK_NULL_VOID(containerNode);

    // update container modal background
    auto renderContext = containerNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(isFocus ? CONTAINER_BACKGROUND_COLOR : CONTAINER_BACKGROUND_COLOR_LOST_FOCUS);
    BorderColorProperty borderColor;
    borderColor.SetColor(isFocus ? CONTAINER_BORDER_COLOR : CONTAINER_BORDER_COLOR_LOST_FOCUS);
    renderContext->UpdateBorderColor(borderColor);

    ChangeCustomTitle(isFocus);
    ChangeFloatingTitle(isFocus);
    ChangeControlButtons(isFocus);
}

void ContainerModalPattern::ChangeCustomTitle(bool isFocus)
{
    // update custom title label
    auto customTitleNode = GetCustomTitleNode();
    CHECK_NULL_VOID(customTitleNode);
    isFocus ? customTitleNode->FireOnWindowFocusedCallback() : customTitleNode->FireOnWindowUnfocusedCallback();
}

void ContainerModalPattern::ChangeControlButtons(bool isFocus)
{
    auto containerNode = GetHost();
    CHECK_NULL_VOID(containerNode);
    auto controlButtonsNode = GetControlButtonRow();
    CHECK_NULL_VOID(controlButtonsNode);

    // update leftSplit button
    auto leftSplitButton =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, LEFT_SPLIT_BUTTON_INDEX));
    ChangeTitleButtonIcon(leftSplitButton,
        isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_SPLIT_LEFT
                : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_SPLIT_LEFT,
        isFocus);

    // hide leftSplit button when window mode is WINDOW_MODE_SPLIT_PRIMARY type or split button can not show
    bool hideLeftSplit = hideSplitButton_ || windowMode_ == WindowMode::WINDOW_MODE_SPLIT_PRIMARY;
    leftSplitButton->GetLayoutProperty()->UpdateVisibility(hideLeftSplit ? VisibleType::GONE : VisibleType::VISIBLE);

    // update maximize button
    auto maximizeButton =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MAX_RECOVER_BUTTON_INDEX));
    auto pipeline = PipelineContext::GetCurrentContext();
    auto windowManager = pipeline->GetWindowManager();
    MaximizeMode mode = windowManager->GetCurrentWindowMaximizeMode();
    InternalResource::ResourceId maxId = InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE;
    if (mode == MaximizeMode::MODE_AVOID_SYSTEM_BAR || windowMode_ == WindowMode::WINDOW_MODE_FULLSCREEN) {
        maxId = isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_RECOVER
                        : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_RECOVER;
    } else {
        maxId = isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE
                        : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MAXIMIZE;
    }

    ChangeTitleButtonIcon(maximizeButton, maxId, isFocus);
    // update minimize button
    auto minimizeButton =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MINIMIZE_BUTTON_INDEX));
    ChangeTitleButtonIcon(minimizeButton,
        isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MINIMIZE
                : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MINIMIZE,
        isFocus);

    // update close button
    auto closeButton = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, CLOSE_BUTTON_INDEX));
    ChangeTitleButtonIcon(closeButton,
        isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_CLOSE
                : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_CLOSE,
        isFocus);
}

void ContainerModalPattern::ChangeFloatingTitle(bool isFocus)
{
    // update floating custom title label
    auto customFloatingTitleNode = GetFloatingTitleNode();
    CHECK_NULL_VOID(customFloatingTitleNode);
    isFocus ? customFloatingTitleNode->FireOnWindowFocusedCallback()
            : customFloatingTitleNode->FireOnWindowUnfocusedCallback();
}

void ContainerModalPattern::ChangeTitleButtonIcon(
    const RefPtr<FrameNode>& buttonNode, InternalResource::ResourceId icon, bool isFocus)
{
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(
        isFocus ? TITLE_BUTTON_BACKGROUND_COLOR : TITLE_BUTTON_BACKGROUND_COLOR_LOST_FOCUS);
    auto buttonIcon = AceType::DynamicCast<FrameNode>(buttonNode->GetChildren().front());
    CHECK_NULL_VOID(buttonIcon);
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(icon);
    auto imageLayoutProperty = buttonIcon->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    buttonIcon->MarkModifyDone();
}

bool ContainerModalPattern::CanShowFloatingTitle()
{
    auto floatingTitleRow = GetFloatingTitleRow();
    CHECK_NULL_RETURN(floatingTitleRow, false);
    auto floatingLayoutProperty = floatingTitleRow->GetLayoutProperty();
    CHECK_NULL_RETURN(floatingLayoutProperty, false);

    if (windowMode_ != WindowMode::WINDOW_MODE_FULLSCREEN && windowMode_ != WindowMode::WINDOW_MODE_SPLIT_PRIMARY &&
        windowMode_ != WindowMode::WINDOW_MODE_SPLIT_SECONDARY) {
        LOGI("Window is not full screen or split screen, can not show floating title.");
        return false;
    }

    if (floatingLayoutProperty->GetVisibilityValue(VisibleType::GONE) == VisibleType::VISIBLE) {
        LOGI("Floating tittle is visible now, no need to show again.");
        return false;
    }
    return true;
}

void ContainerModalPattern::SetAppTitle(const std::string& title)
{
    LOGI("SetAppTitle successfully, title is %{public}s", title.c_str());
    auto customTitleNode = GetCustomTitleNode();
    CHECK_NULL_VOID(customTitleNode);
    customTitleNode->FireAppTitleCallback(title);

    auto customFloatingTitleNode = GetFloatingTitleNode();
    CHECK_NULL_VOID(customFloatingTitleNode);
    customFloatingTitleNode->FireAppTitleCallback(title);
}

void ContainerModalPattern::SetAppIcon(const RefPtr<PixelMap>& icon)
{
    CHECK_NULL_VOID(icon);
    LOGI("SetAppIcon successfully");
    auto customTitleNode = GetCustomTitleNode();
    CHECK_NULL_VOID(customTitleNode);
    customTitleNode->FireAppIconCallback(icon);

    auto customFloatingTitleNode = GetFloatingTitleNode();
    CHECK_NULL_VOID(customFloatingTitleNode);
    customFloatingTitleNode->FireAppIconCallback(icon);
}

void ContainerModalPattern::SetTitleButtonHide(
    const RefPtr<FrameNode>& controlButtonsNode, bool hideSplit, bool hideMaximize, bool hideMinimize)
{
    auto leftSplitButton =
        AceType::DynamicCast<FrameNode>(controlButtonsNode->GetChildAtIndex(LEFT_SPLIT_BUTTON_INDEX));
    CHECK_NULL_VOID(leftSplitButton);
    leftSplitButton->GetLayoutProperty()->UpdateVisibility(hideSplit ? VisibleType::GONE : VisibleType::VISIBLE);
    leftSplitButton->MarkDirtyNode();

    auto maximizeButton =
        AceType::DynamicCast<FrameNode>(controlButtonsNode->GetChildAtIndex(MAX_RECOVER_BUTTON_INDEX));
    CHECK_NULL_VOID(maximizeButton);
    maximizeButton->GetLayoutProperty()->UpdateVisibility(hideMaximize ? VisibleType::GONE : VisibleType::VISIBLE);
    maximizeButton->MarkDirtyNode();

    auto minimizeButton = AceType::DynamicCast<FrameNode>(controlButtonsNode->GetChildAtIndex(MINIMIZE_BUTTON_INDEX));
    CHECK_NULL_VOID(minimizeButton);
    minimizeButton->GetLayoutProperty()->UpdateVisibility(hideMinimize ? VisibleType::GONE : VisibleType::VISIBLE);
    minimizeButton->MarkDirtyNode();
}

void ContainerModalPattern::SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize)
{
    auto controlButtonsRow = GetControlButtonRow();
    CHECK_NULL_VOID(controlButtonsRow);
    SetTitleButtonHide(controlButtonsRow, hideSplit, hideMaximize, hideMinimize);
    hideSplitButton_ = hideSplit;
    LOGI("Set containerModal button status successfully, hideSplit: %{public}d, hideMaximize: %{public}d, "
         "hideMinimize: %{public}d",
        hideSplit, hideMaximize, hideMinimize);
}

void ContainerModalPattern::SetCloseButtonStatus(bool isEnabled)
{
    auto controlButtonsRow = GetControlButtonRow();
    CHECK_NULL_VOID(controlButtonsRow);

    // set closeButton enable or disable
    auto closeButton = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsRow, CLOSE_BUTTON_INDEX));
    CHECK_NULL_VOID(closeButton);
    auto buttonEvent = closeButton->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEvent);
    buttonEvent->SetEnabled(isEnabled);
}

void ContainerModalPattern::SetContainerModalTitleVisible(bool customTitleSettedShow, bool floatingTitleSettedShow)
{
    customTitleSettedShow_ = customTitleSettedShow;
    auto customTitleRow = GetCustomTitleRow();
    CHECK_NULL_VOID(customTitleRow);
    auto customTitleLayoutProperty = customTitleRow->GetLayoutProperty();
    CHECK_NULL_VOID(customTitleLayoutProperty);
    auto containerModalLayoutProperty = GetHost()->GetLayoutProperty();
    PaddingProperty padding;
    if (customTitleLayoutProperty->GetVisibilityValue(VisibleType::GONE) == VisibleType::VISIBLE &&
        !customTitleSettedShow) {
        customTitleLayoutProperty->UpdateVisibility(VisibleType::GONE);
    } else if (windowMode_ != WindowMode::WINDOW_MODE_FULLSCREEN &&
               windowMode_ != WindowMode::WINDOW_MODE_SPLIT_PRIMARY &&
               windowMode_ != WindowMode::WINDOW_MODE_SPLIT_SECONDARY && customTitleSettedShow) {
        customTitleLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        padding = { CalcLength(CONTENT_PADDING), CalcLength(CONTENT_PADDING), std::nullopt,
            CalcLength(CONTENT_PADDING) };
    }
    containerModalLayoutProperty->UpdatePadding(padding);

    floatingTitleSettedShow_ = floatingTitleSettedShow;
    auto floatingTitleRow = GetFloatingTitleRow();
    CHECK_NULL_VOID(floatingTitleRow);
    auto floatingTitleLayoutProperty = floatingTitleRow->GetLayoutProperty();
    CHECK_NULL_VOID(floatingTitleLayoutProperty);
    if (floatingTitleLayoutProperty->GetVisibilityValue(VisibleType::GONE) == VisibleType::VISIBLE &&
        !floatingTitleSettedShow) {
        floatingTitleLayoutProperty->UpdateVisibility(VisibleType::GONE);
    }

    auto buttonsRow = GetControlButtonRow();
    CHECK_NULL_VOID(buttonsRow);
    buttonsRow->SetHitTestMode(HitTestMode::HTMTRANSPARENT_SELF);
}

void ContainerModalPattern::SetContainerModalTitleHeight(int32_t height)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (height < 0) {
        height = 0;
    }
    titleHeight_ = Dimension(Dimension(height, DimensionUnit::PX).ConvertToVp(), DimensionUnit::VP);
    auto column = host->GetChildAtIndex(0);
    CHECK_NULL_VOID(column);
    auto customTitleRow = GetCustomTitleRow();
    UpdateRowHeight(customTitleRow, height);
    auto floatingTitleRow = GetFloatingTitleRow();
    UpdateRowHeight(floatingTitleRow, height);
    auto controlButtonsRow = GetControlButtonRow();
    UpdateRowHeight(controlButtonsRow, height);
    CallButtonsRectChange();
}

int32_t ContainerModalPattern::GetContainerModalTitleHeight()
{
    return static_cast<int32_t>(ceil(titleHeight_.ConvertToPx()));
}

bool ContainerModalPattern::GetContainerModalButtonsRect(RectF& containerModal, RectF& buttons)
{
    auto column = GetColumnNode();
    CHECK_NULL_RETURN(column, false);
    auto columnRect = column->GetGeometryNode()->GetFrameRect();
    containerModal = columnRect;
    if (columnRect.Width() == 0) {
        LOGW("Get rect of buttons failed, the rect is measuring.");
        return false;
    }

    auto controlButtonsRow = GetControlButtonRow();
    CHECK_NULL_RETURN(controlButtonsRow, false);
    auto children = controlButtonsRow->GetChildren();
    RectF firstButtonRect;
    RectF lastButtonRect;
    for (auto& child : children) {
        auto node = AceType::DynamicCast<FrameNode>(child);
        if (node->GetLayoutProperty()->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::VISIBLE) {
            continue;
        }
        auto rect = node->GetGeometryNode()->GetFrameRect();
        if (firstButtonRect.Width() == 0) {
            firstButtonRect = rect;
        }
        lastButtonRect = rect;
    }
    buttons = firstButtonRect.CombineRectT(lastButtonRect);
    if (buttons.Width() == 0) {
        LOGW("Get rect of buttons failed, buttons are hidden");
        return false;
    }

    auto widthByPx = (TITLE_PADDING_START + TITLE_PADDING_END).ConvertToPx() + buttons.Width();
    buttons.SetLeft(containerModal.Width() - widthByPx);
    buttons.SetTop(0);
    buttons.SetWidth(widthByPx);
    buttons.SetHeight(titleHeight_.ConvertToPx());
    return true;
}

void ContainerModalPattern::SubscribeContainerModalButtonsRectChange(
    std::function<void(RectF& containerModal, RectF& buttons)>&& callback)
{
    controlButtonsRectChangeCallback_ = std::move(callback);
}

void ContainerModalPattern::CallButtonsRectChange()
{
    CHECK_NULL_VOID(controlButtonsRectChangeCallback_);
    RectF containerModal;
    RectF buttons;
    GetContainerModalButtonsRect(containerModal, buttons);
    if (buttonsRect_ == buttons) {
        return;
    }
    buttonsRect_ = buttons;
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [containerModal, buttons, cb = controlButtonsRectChangeCallback_]() mutable {
            if (cb) {
                cb(containerModal, buttons);
            }
        },
        TaskExecutor::TaskType::JS);
}

void ContainerModalPattern::InitTitle()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_VOID(themeConstants);
    auto id = pipeline->GetWindowManager()->GetAppIconId();
    auto pixelMap = themeConstants->GetPixelMap(id);
    if (pixelMap) {
        RefPtr<PixelMap> icon = PixelMap::CreatePixelMap(&pixelMap);
        SetAppIcon(icon);
    } else {
        LOGW("Cannot get pixelmap, try media path."); // use themeConstants GetMediaPath
    }
    SetAppTitle(themeConstants->GetString(pipeline->GetWindowManager()->GetAppLabelId()));
}

void ContainerModalPattern::Init()
{
    InitContainerEvent();
    InitTitle();
    InitLayoutProperty();
}

void ContainerModalPattern::InitLayoutProperty()
{
    auto containerModal = GetHost();
    containerModal->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);

    auto column = GetColumnNode();
    column->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);

    auto content = GetContentNode();
    auto contentProperty = content->GetLayoutProperty();
    contentProperty->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    contentProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(1.0, DimensionUnit::PERCENT)));

    auto stack = GetStackNode();
    stack->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);

    auto buttonsRow = GetControlButtonRow();
    auto buttonsRowProperty = buttonsRow->GetLayoutProperty<LinearLayoutProperty>();
    buttonsRowProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    buttonsRowProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(CONTAINER_TITLE_HEIGHT)));
    buttonsRowProperty->UpdateMainAxisAlign(FlexAlign::FLEX_END);
    buttonsRowProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);

    InitTitleRowLayoutProperty(GetCustomTitleRow());
    InitTitleRowLayoutProperty(GetFloatingTitleRow());

    containerModal->MarkModifyDone();
}

void ContainerModalPattern::InitTitleRowLayoutProperty(RefPtr<FrameNode> titleRow)
{
    auto titleRowProperty = titleRow->GetLayoutProperty<LinearLayoutProperty>();
    titleRowProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    titleRowProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(CONTAINER_TITLE_HEIGHT)));
    titleRowProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    titleRowProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    PaddingProperty padding { std::nullopt, GetControlButtonRowWidth(), std::nullopt, std::nullopt };
    titleRowProperty->UpdatePadding(padding);
}

CalcLength ContainerModalPattern::GetControlButtonRowWidth()
{
    auto row = GetControlButtonRow();
    int32_t buttonNum = row->GetChildren().size();

    return CalcLength(TITLE_ELEMENT_MARGIN_HORIZONTAL * (buttonNum - 1) + TITLE_BUTTON_SIZE * buttonNum +
                      TITLE_PADDING_START + TITLE_PADDING_END);
}
} // namespace OHOS::Ace::NG
