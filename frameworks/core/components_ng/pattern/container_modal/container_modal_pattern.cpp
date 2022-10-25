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

#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

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

void ContainerModalPattern::OnModifyDone()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    windowMode_ = windowManager->FireWindowGetModeCallBack();
    ShowTitle(windowMode_ == WindowMode::WINDOW_MODE_FLOATING);
}

bool ContainerModalPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, false);
    if (!config.frameSizeChange || windowMode_ == windowManager->FireWindowGetModeCallBack()) {
        LOGI("container modal node no need to render");
        return false;
    }

    windowMode_ = windowManager->FireWindowGetModeCallBack();
    ShowTitle(windowMode_ == WindowMode::WINDOW_MODE_FLOATING);
    return true;
}

void ContainerModalPattern::ShowTitle(bool isShow)
{
    auto containerNode = GetHost();
    CHECK_NULL_VOID(containerNode);
    auto columnNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildren().front());
    CHECK_NULL_VOID(columnNode);
    auto titleNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    CHECK_NULL_VOID(titleNode);
    auto contentNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().back());
    CHECK_NULL_VOID(contentNode);
    auto floatingTitleNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildren().back());
    CHECK_NULL_VOID(floatingTitleNode);

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
    renderContext->UpdateBackgroundColor(CONTAINER_BACKGROUND_COLOR);
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(isShow ? CONTAINER_OUTER_RADIUS : 0.0_vp);
    renderContext->UpdateBorderRadius(borderRadius);
    BorderColorProperty borderColor;
    borderColor.SetColor(isShow ? CONTAINER_BORDER_COLOR : Color::TRANSPARENT);
    renderContext->UpdateBorderColor(borderColor);

    // update stage content border
    auto contentLayoutProperty = contentNode->GetLayoutProperty();
    CHECK_NULL_VOID(contentLayoutProperty);
    contentLayoutProperty->UpdateLayoutWeight(1.0f);

    auto contentRenderContext = contentNode->GetRenderContext();
    CHECK_NULL_VOID(contentRenderContext);
    BorderRadiusProperty stageBorderRadius;
    stageBorderRadius.SetRadius(isShow ? CONTAINER_INNER_RADIUS : 0.0_vp);
    contentRenderContext->UpdateBorderRadius(stageBorderRadius);
    contentRenderContext->SetClipToBounds(true);

    auto titleLayoutProperty = titleNode->GetLayoutProperty();
    CHECK_NULL_VOID(titleLayoutProperty);
    titleLayoutProperty->UpdateVisibility(isShow ? VisibleType::VISIBLE : VisibleType::GONE);

    auto floatingLayoutProperty = floatingTitleNode->GetLayoutProperty();
    CHECK_NULL_VOID(floatingLayoutProperty);
    ChangeFloatingTitle(floatingTitleNode);
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
    TranslateOptions translate;
    translate.y = Dimension(-titlePopupDistance);
    TransitionOptions transOptions;
    transOptions.UpdateTranslate(translate);

    AnimationOption option;
    option.SetDuration(TITLE_POPUP_DURATION);
    option.SetCurve(Curves::EASE_IN_OUT);

    // init touch event
    touchEventHub->SetTouchEvent([floatingLayoutProperty, context, option, transOptions, titlePopupDistance,
                                     weak = WeakClaim(this)](TouchEventInfo& info) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
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
                floatingLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
                context->NotifyTransition(option, transOptions, true);
            }
            return;
        }
        if (info.GetChangedTouches().begin()->GetTouchType() != TouchType::DOWN) {
            return;
        }
        if (floatingLayoutProperty->GetVisibilityValue() != VisibleType::VISIBLE) {
            return;
        }

        // TODO: transition out animation
        // step4. Touch other area to hide floating title.
        floatingLayoutProperty->UpdateVisibility(VisibleType::GONE);
    });

    // init mouse event
    auto mouseEventHub = containerNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(mouseEventHub);
    mouseEventHub->SetMouseEvent([floatingLayoutProperty, context, option, transOptions, titlePopupDistance,
                                     weak = WeakClaim(this)](MouseInfo& info) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        if (info.GetAction() != MouseAction::MOVE) {
            return;
        }
        if (info.GetLocalLocation().GetY() <= MOUSE_MOVE_POPUP_DISTANCE && container->CanShowFloatingTitle()) {
            floatingLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
            context->NotifyTransition(option, transOptions, true);
        }

        if (info.GetLocalLocation().GetY() >= titlePopupDistance &&
            floatingLayoutProperty->GetVisibilityValue() == VisibleType::VISIBLE) {
            floatingLayoutProperty->UpdateVisibility(VisibleType::GONE);
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
    if (windowManager->FireWindowGetModeCallBack() == WindowMode::WINDOW_MODE_FLOATING) {
        auto columnNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildren().front());
        CHECK_NULL_VOID(columnNode);
        auto titleNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
        CHECK_NULL_VOID(titleNode);
        ChangeTitle(titleNode, isFocus);
        return;
    }

    // update floating title
    auto floatingTitleNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildren().back());
    CHECK_NULL_VOID(floatingTitleNode);
    ChangeFloatingTitle(floatingTitleNode, isFocus);
}

void ContainerModalPattern::ChangeTitle(const RefPtr<FrameNode>& titleNode, bool isFocus)
{
    CHECK_NULL_VOID(titleNode);
    // update title label
    auto titleLabel = AceType::DynamicCast<FrameNode>(titleNode->GetChildAtIndex(TITLE_LABEL_INDEX));
    auto textLayoutProperty = titleLabel->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateTextColor(isFocus ? TITLE_TEXT_COLOR : TITLE_TEXT_COLOR_LOST_FOCUS);
    titleLabel->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    // update leftSplit button
    auto leftSplitButton = AceType::DynamicCast<FrameNode>(titleNode->GetChildAtIndex(LEFT_SPLIT_BUTTON_INDEX));
    ChangeTitleButtonIcon(leftSplitButton,
        isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_SPLIT_LEFT
                : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_SPLIT_LEFT, isFocus);

    // update maximize button
    auto maximizeButton = AceType::DynamicCast<FrameNode>(titleNode->GetChildAtIndex(MAX_RECOVER_BUTTON_INDEX));
    ChangeTitleButtonIcon(maximizeButton,
        isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE
                : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MAXIMIZE, isFocus);

    // update minimize button
    auto minimizeButton = AceType::DynamicCast<FrameNode>(titleNode->GetChildAtIndex(MINIMIZE_BUTTON_INDEX));
    ChangeTitleButtonIcon(minimizeButton,
        isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MINIMIZE
                : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MINIMIZE, isFocus);

    // update close button
    auto closeButton = AceType::DynamicCast<FrameNode>(titleNode->GetChildAtIndex(CLOSE_BUTTON_INDEX));
    ChangeTitleButtonIcon(closeButton,
        isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_CLOSE
                : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_CLOSE, isFocus);
}

void ContainerModalPattern::ChangeFloatingTitle(const RefPtr<FrameNode>& floatingNode, bool isFocus)
{
    CHECK_NULL_VOID(floatingNode);

    // update title label
    auto titleLabel = AceType::DynamicCast<FrameNode>(floatingNode->GetChildAtIndex(TITLE_LABEL_INDEX));
    auto textLayoutProperty = titleLabel->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateTextColor(isFocus ? TITLE_TEXT_COLOR : TITLE_TEXT_COLOR_LOST_FOCUS);
    titleLabel->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    // update leftSplit button
    auto leftSplitButton = AceType::DynamicCast<FrameNode>(floatingNode->GetChildAtIndex(LEFT_SPLIT_BUTTON_INDEX));
    ChangeTitleButtonIcon(leftSplitButton,
        isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_SPLIT_LEFT
                : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_SPLIT_LEFT, isFocus);

    // hide leftSplit button when window mode is WINDOW_MODE_SPLIT_PRIMARY type
    leftSplitButton->GetRenderContext()->SetVisible(windowMode_ != WindowMode::WINDOW_MODE_SPLIT_PRIMARY);

    // update maxRecover button
    auto maxRecoverIconFocused = windowMode_ == WindowMode::WINDOW_MODE_FULLSCREEN
                                     ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_RECOVER
                                     : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE;
    auto maxRecoverIconUnfocused = windowMode_ == WindowMode::WINDOW_MODE_FULLSCREEN
                                       ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_RECOVER
                                       : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MAXIMIZE;
    auto maxRecover = AceType::DynamicCast<FrameNode>(floatingNode->GetChildAtIndex(MAX_RECOVER_BUTTON_INDEX));
    ChangeTitleButtonIcon(maxRecover, isFocus ? maxRecoverIconFocused : maxRecoverIconUnfocused, isFocus);

    // update minimize button
    auto minimizeButton = AceType::DynamicCast<FrameNode>(floatingNode->GetChildAtIndex(MINIMIZE_BUTTON_INDEX));
    ChangeTitleButtonIcon(minimizeButton,
        isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MINIMIZE
                : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MINIMIZE, isFocus);

    // update close button
    auto closeButton = AceType::DynamicCast<FrameNode>(floatingNode->GetChildAtIndex(CLOSE_BUTTON_INDEX));
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

} // namespace OHOS::Ace::NG
