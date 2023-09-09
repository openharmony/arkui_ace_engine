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

#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/button/button_event_hub.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t TITLE_LABEL_INDEX = 1;
constexpr int32_t LEFT_SPLIT_BUTTON_INDEX = 2;
constexpr int32_t MAX_RECOVER_BUTTON_INDEX = 3;
constexpr int32_t MINIMIZE_BUTTON_INDEX = 4;
constexpr int32_t CLOSE_BUTTON_INDEX = 5;
constexpr int32_t TITLE_POPUP_DURATION = 200;
constexpr double MOUSE_MOVE_POPUP_DISTANCE = 5.0; // 5.0px
constexpr double MOVE_POPUP_DISTANCE_X = 10.0;    // 10.0px
constexpr double MOVE_POPUP_DISTANCE_Y = 20.0;    // 20.0px
constexpr double TITLE_POPUP_DISTANCE = 37.0;     // 37vp height of title

} // namespace

void ContainerModalPattern::ShowTitle(bool isShow, bool hasDeco)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto containerNode = GetHost();
    CHECK_NULL_VOID(containerNode);
    auto columnNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildren().front());
    CHECK_NULL_VOID(columnNode);
    auto titleNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    CHECK_NULL_VOID(titleNode);
    auto stackNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().back());
    CHECK_NULL_VOID(stackNode);
    auto floatingTitleNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildren().back());
    CHECK_NULL_VOID(floatingTitleNode);
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
    if (isShow) {
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

    auto titleLayoutProperty = titleNode->GetLayoutProperty();
    CHECK_NULL_VOID(titleLayoutProperty);
    titleLayoutProperty->UpdateVisibility(isShow ? VisibleType::VISIBLE : VisibleType::GONE);

    auto floatingLayoutProperty = floatingTitleNode->GetLayoutProperty();
    CHECK_NULL_VOID(floatingLayoutProperty);
    ChangeFloatingTitle(floatingTitleNode, isFocus_);
    floatingLayoutProperty->UpdateVisibility(VisibleType::GONE);
}

void ContainerModalPattern::InitContainerEvent()
{
    auto containerNode = GetHost();
    CHECK_NULL_VOID(containerNode);
    auto touchEventHub = containerNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(touchEventHub);
    auto floatingTitleNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildren().back());
    CHECK_NULL_VOID(floatingTitleNode);
    auto floatingLayoutProperty = floatingTitleNode->GetLayoutProperty();
    CHECK_NULL_VOID(floatingLayoutProperty);
    auto context = floatingTitleNode->GetRenderContext();
    CHECK_NULL_VOID(context);

    auto titlePopupDistance = TITLE_POPUP_DISTANCE * containerNode->GetContext()->GetDensity();
    AnimationOption option;
    option.SetDuration(TITLE_POPUP_DURATION);
    option.SetCurve(Curves::EASE_IN_OUT);

    // init touch event
    touchEventHub->SetTouchEvent([floatingLayoutProperty, context, option, titlePopupDistance, weak = WeakClaim(this)](
                                     TouchEventInfo& info) {
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
                context->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
                floatingLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
                AnimationUtils::Animate(option, [context]() {
                    context->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
                });
            }
            return;
        }
        if (info.GetChangedTouches().begin()->GetTouchType() != TouchType::DOWN) {
            return;
        }
        if (floatingLayoutProperty->GetVisibilityValue() != VisibleType::VISIBLE) {
            return;
        }
        // step4. Touch other area to hide floating title.
        AnimationUtils::Animate(
            option,
            [context, titlePopupDistance]() {
                context->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
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
    mouseEventHub->SetMouseEvent([floatingLayoutProperty, context, option, titlePopupDistance, weak = WeakClaim(this)](
                                     MouseInfo& info) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        auto action = info.GetAction();
        if ((action != MouseAction::MOVE && action != MouseAction::WINDOW_LEAVE) || !container->hasDeco_) {
            return;
        }
        if (info.GetLocalLocation().GetY() <= MOUSE_MOVE_POPUP_DISTANCE && container->CanShowFloatingTitle()) {
            context->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
            floatingLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
            AnimationUtils::Animate(option, [context]() { context->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f }); });
        }

        if (!container->CanHideFloatingTitle()) {
            return;
        }
        if ((info.GetLocalLocation().GetY() >= titlePopupDistance || action == MouseAction::WINDOW_LEAVE) &&
            floatingLayoutProperty->GetVisibilityValue() == VisibleType::VISIBLE) {
            AnimationUtils::Animate(
                option,
                [context, titlePopupDistance]() {
                    context->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
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

void ContainerModalPattern::OnWindowFocused()
{
    WindowFocus(true);
}

void ContainerModalPattern::OnWindowUnfocused()
{
    WindowFocus(false);
}

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

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);

    // update normal title
    auto columnNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildren().front());
    CHECK_NULL_VOID(columnNode);
    auto titleNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    CHECK_NULL_VOID(titleNode);
    ChangeTitle(titleNode, isFocus);

    // update floating title
    auto floatingTitleNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildren().back());
    CHECK_NULL_VOID(floatingTitleNode);
    ChangeFloatingTitle(floatingTitleNode, isFocus);
}

void ContainerModalPattern::ChangeTitle(const RefPtr<FrameNode>& titleNode, bool isFocus)
{
    CHECK_NULL_VOID(titleNode);
    // update title label
    auto titleLabel = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(titleNode, TITLE_LABEL_INDEX));
    auto textLayoutProperty = titleLabel->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateTextColor(isFocus ? TITLE_TEXT_COLOR : TITLE_TEXT_COLOR_LOST_FOCUS);
    titleLabel->MarkModifyDone();
    titleLabel->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    // update leftSplit button
    auto leftSplitButton = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(titleNode, LEFT_SPLIT_BUTTON_INDEX));
    ChangeTitleButtonIcon(leftSplitButton,
        isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_SPLIT_LEFT
                : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_SPLIT_LEFT, isFocus);

    // update maximize button
    auto maximizeButton = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(titleNode, MAX_RECOVER_BUTTON_INDEX));
    auto pipeline = PipelineContext::GetCurrentContext();
    auto windowManager = pipeline->GetWindowManager();
    MaximizeMode mode = windowManager->GetCurrentWindowMaximizeMode();
    InternalResource::ResourceId maxId = InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE;
    if (mode == MaximizeMode::MODE_AVOID_SYSTEM_BAR) {
        maxId = isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_RECOVER
            : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_RECOVER;
    } else {
        maxId = isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE
            : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MAXIMIZE;
    }

    ChangeTitleButtonIcon(maximizeButton, maxId, isFocus);
    // update minimize button
    auto minimizeButton = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(titleNode, MINIMIZE_BUTTON_INDEX));
    ChangeTitleButtonIcon(minimizeButton,
        isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MINIMIZE
                : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MINIMIZE, isFocus);

    // update close button
    auto closeButton = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(titleNode, CLOSE_BUTTON_INDEX));
    ChangeTitleButtonIcon(closeButton,
        isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_CLOSE
                : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_CLOSE, isFocus);
}

void ContainerModalPattern::ChangeFloatingTitle(const RefPtr<FrameNode>& floatingNode, bool isFocus)
{
    CHECK_NULL_VOID(floatingNode);

    // update title label
    auto titleLabel = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(floatingNode, TITLE_LABEL_INDEX));
    auto textLayoutProperty = titleLabel->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateTextColor(isFocus ? TITLE_TEXT_COLOR : TITLE_TEXT_COLOR_LOST_FOCUS);
    titleLabel->MarkModifyDone();
    titleLabel->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    // update leftSplit button
    auto leftSplitButton = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(floatingNode, LEFT_SPLIT_BUTTON_INDEX));
    ChangeTitleButtonIcon(leftSplitButton,
        isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_SPLIT_LEFT
                : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_SPLIT_LEFT, isFocus);

    // hide leftSplit button when window mode is WINDOW_MODE_SPLIT_PRIMARY type or split button can not show
    bool hideLeftSplit = hideSplitButton_ || windowMode_ == WindowMode::WINDOW_MODE_SPLIT_PRIMARY;
    leftSplitButton->GetLayoutProperty()->UpdateVisibility(hideLeftSplit ? VisibleType::GONE : VisibleType::VISIBLE);

    // update maxRecover button
    auto maxRecoverIconFocused = windowMode_ == WindowMode::WINDOW_MODE_FULLSCREEN
                                     ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_RECOVER
                                     : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE;
    auto maxRecoverIconUnfocused = windowMode_ == WindowMode::WINDOW_MODE_FULLSCREEN
                                       ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_RECOVER
                                       : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MAXIMIZE;
    auto maxRecover = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(floatingNode, MAX_RECOVER_BUTTON_INDEX));
    ChangeTitleButtonIcon(maxRecover, isFocus ? maxRecoverIconFocused : maxRecoverIconUnfocused, isFocus);

    // update minimize button
    auto minimizeButton = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(floatingNode, MINIMIZE_BUTTON_INDEX));
    ChangeTitleButtonIcon(minimizeButton,
        isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MINIMIZE
                : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MINIMIZE, isFocus);

    // update close button
    auto closeButton = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(floatingNode, CLOSE_BUTTON_INDEX));
    ChangeTitleButtonIcon(closeButton,
        isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_CLOSE
                : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_CLOSE, isFocus);
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
    auto floatingTitleNode = AceType::DynamicCast<FrameNode>(GetHost()->GetChildren().back());
    CHECK_NULL_RETURN(floatingTitleNode, false);
    auto floatingLayoutProperty = floatingTitleNode->GetLayoutProperty();
    CHECK_NULL_RETURN(floatingLayoutProperty, false);

    if (windowMode_ != WindowMode::WINDOW_MODE_FULLSCREEN && windowMode_ != WindowMode::WINDOW_MODE_SPLIT_PRIMARY &&
        windowMode_ != WindowMode::WINDOW_MODE_SPLIT_SECONDARY) {
        LOGI("Window is not full screen or split screen, can not show floating title.");
        return false;
    }

    if (floatingLayoutProperty->GetVisibilityValue() == VisibleType::VISIBLE) {
        LOGI("Floating tittle is visible now, no need to show again.");
        return false;
    }
    return true;
}

void ContainerModalPattern::SetAppTitle(const std::string& title)
{
    LOGI("SetAppTitle successfully, title is %{public}s", title.c_str());
    auto titleNode = AceType::DynamicCast<FrameNode>(GetHost()->GetChildren().front()->GetChildren().front());
    CHECK_NULL_VOID(titleNode);
    auto titleLabel = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(titleNode, TITLE_LABEL_INDEX));
    titleLabel->GetLayoutProperty<TextLayoutProperty>()->UpdateContent(title);
    titleLabel->MarkModifyDone();
    titleLabel->MarkDirtyNode();

    auto floatingNode = AceType::DynamicCast<FrameNode>(GetHost()->GetChildren().back());
    CHECK_NULL_VOID(floatingNode);
    auto floatingTitleLabel = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(floatingNode, TITLE_LABEL_INDEX));
    floatingTitleLabel->GetLayoutProperty<TextLayoutProperty>()->UpdateContent(title);
    floatingTitleLabel->MarkModifyDone();
    floatingTitleLabel->MarkDirtyNode();
}

void ContainerModalPattern::SetAppIcon(const RefPtr<PixelMap>& icon)
{
    CHECK_NULL_VOID(icon);
    LOGI("SetAppIcon successfully");
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetPixMap(icon);
    auto titleNode = AceType::DynamicCast<FrameNode>(GetHost()->GetChildren().front()->GetChildren().front());
    CHECK_NULL_VOID(titleNode);
    auto titleIcon = AceType::DynamicCast<FrameNode>(titleNode->GetChildren().front());
    titleIcon->GetLayoutProperty<ImageLayoutProperty>()->UpdateImageSourceInfo(imageSourceInfo);
    titleIcon->MarkModifyDone();

    auto floatingNode = AceType::DynamicCast<FrameNode>(GetHost()->GetChildren().back());
    CHECK_NULL_VOID(floatingNode);
    auto floatingTitleIcon = AceType::DynamicCast<FrameNode>(floatingNode->GetChildren().front());
    floatingTitleIcon->GetLayoutProperty<ImageLayoutProperty>()->UpdateImageSourceInfo(imageSourceInfo);
    floatingTitleIcon->MarkModifyDone();
}

void ContainerModalPattern::SetTitleButtonHide(
    const RefPtr<FrameNode>& titleNode, bool hideSplit, bool hideMaximize, bool hideMinimize)
{
    auto leftSplitButton = AceType::DynamicCast<FrameNode>(titleNode->GetChildAtIndex(LEFT_SPLIT_BUTTON_INDEX));
    CHECK_NULL_VOID(leftSplitButton);
    leftSplitButton->GetLayoutProperty()->UpdateVisibility(hideSplit ? VisibleType::GONE : VisibleType::VISIBLE);
    leftSplitButton->MarkDirtyNode();

    auto maximizeButton = AceType::DynamicCast<FrameNode>(titleNode->GetChildAtIndex(MAX_RECOVER_BUTTON_INDEX));
    CHECK_NULL_VOID(maximizeButton);
    maximizeButton->GetLayoutProperty()->UpdateVisibility(hideMaximize ? VisibleType::GONE : VisibleType::VISIBLE);
    maximizeButton->MarkDirtyNode();

    auto minimizeButton = AceType::DynamicCast<FrameNode>(titleNode->GetChildAtIndex(MINIMIZE_BUTTON_INDEX));
    CHECK_NULL_VOID(minimizeButton);
    minimizeButton->GetLayoutProperty()->UpdateVisibility(hideMinimize ? VisibleType::GONE : VisibleType::VISIBLE);
    minimizeButton->MarkDirtyNode();
}

void ContainerModalPattern::SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto titleNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front()->GetChildren().front());
    CHECK_NULL_VOID(titleNode);
    SetTitleButtonHide(titleNode, hideSplit, hideMaximize, hideMinimize);
    auto floatingTitleNode = AceType::DynamicCast<FrameNode>(host->GetChildren().back());
    CHECK_NULL_VOID(floatingTitleNode);
    SetTitleButtonHide(floatingTitleNode, hideSplit, hideMaximize, hideMinimize);
    hideSplitButton_ = hideSplit;
    LOGI("Set containerModal button status successfully, hideSplit: %{public}d, hideMaximize: %{public}d, "
         "hideMinimize: %{public}d",
        hideSplit, hideMaximize, hideMinimize);
}

void ContainerModalPattern::SetCloseButtonStatus(bool isEnabled)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto titleNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front()->GetChildren().front());
    CHECK_NULL_VOID(titleNode);
    auto floatingTitleNode = AceType::DynamicCast<FrameNode>(host->GetChildren().back());
    CHECK_NULL_VOID(floatingTitleNode);

    // set closeButton enable or disable
    auto closeButton = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(titleNode, CLOSE_BUTTON_INDEX));
    CHECK_NULL_VOID(closeButton);
    auto buttonEvent = closeButton->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEvent);
    buttonEvent->SetEnabled(isEnabled);

    // set closeButton in floatingTitle enable or disable
    auto floatingCloseButton = AceType::DynamicCast<FrameNode>(
        GetTitleItemByIndex(floatingTitleNode, CLOSE_BUTTON_INDEX));
    CHECK_NULL_VOID(floatingCloseButton);
    auto floatingButtonEvent = floatingCloseButton->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(floatingButtonEvent);
    floatingButtonEvent->SetEnabled(isEnabled);
}

} // namespace OHOS::Ace::NG
