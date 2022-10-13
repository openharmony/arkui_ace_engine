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

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t TITLE_POPUP_DURATION = 200;
constexpr double TITLE_POPUP_DISTANCE = 37.0; // 37vp height of title

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
    ChangeFloatingTitleIcon(floatingTitleNode);
    floatingLayoutProperty->UpdateVisibility(VisibleType::GONE);
}

void ContainerModalPattern::InitContainerEvent()
{
    auto containerNode = GetHost();
    CHECK_NULL_VOID(containerNode);
    auto pipeline = containerNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    auto touchEventHub = containerNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(touchEventHub);
    auto floatingTitleNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildren().back());
    CHECK_NULL_VOID(floatingTitleNode);
    auto floatingLayoutProperty = floatingTitleNode->GetLayoutProperty();
    CHECK_NULL_VOID(floatingLayoutProperty);
    auto context = floatingTitleNode->GetRenderContext();
    CHECK_NULL_VOID(context);

    auto titlePopupDistance = TITLE_POPUP_DISTANCE * pipeline->GetDensity();
    TranslateOptions translate;
    translate.y = Dimension(-titlePopupDistance);
    TransitionOptions transOptions;
    transOptions.UpdateTranslate(translate);

    AnimationOption option;
    option.SetDuration(TITLE_POPUP_DURATION);
    option.SetCurve(Curves::EASE_IN_OUT);

    touchEventHub->SetTouchEvent([floatingLayoutProperty, context, windowManager, option, transOptions,
                                     titlePopupDistance](TouchEventInfo& info) {
        auto windowMode = windowManager->FireWindowGetModeCallBack();

        if (info.GetChangedTouches().begin()->GetGlobalLocation().GetY() <= titlePopupDistance) {
            if (info.GetChangedTouches().begin()->GetTouchType() != TouchType::MOVE) {
                return;
            }
            if (windowMode != WindowMode::WINDOW_MODE_FULLSCREEN &&
                windowMode != WindowMode::WINDOW_MODE_SPLIT_PRIMARY &&
                windowMode != WindowMode::WINDOW_MODE_SPLIT_SECONDARY) {
                return;
            }
            if (floatingLayoutProperty->GetVisibilityValue() == VisibleType::VISIBLE) {
                return;
            }
            floatingLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
            context->NotifyTransition(option, transOptions, true);
            return;
        }
        if (info.GetChangedTouches().begin()->GetTouchType() != TouchType::DOWN) {
            return;
        }
        if (floatingLayoutProperty->GetVisibilityValue() != VisibleType::VISIBLE) {
            return;
        }

        // TODO: transition out animation
        floatingLayoutProperty->UpdateVisibility(VisibleType::GONE);
    });
}

void ContainerModalPattern::ChangeFloatingTitleIcon(const RefPtr<FrameNode>& floatingNode)
{
    auto maxRecoverButton = AceType::DynamicCast<FrameNode>(floatingNode->GetChildAtIndex(3));
    CHECK_NULL_VOID(maxRecoverButton);
    auto iconImage = AceType::DynamicCast<FrameNode>(maxRecoverButton->GetChildren().front());
    CHECK_NULL_VOID(iconImage);

    auto imageLayoutProperty = iconImage->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    ImageSourceInfo imageSourceInfo;
    auto maxRecoverIcon = windowMode_ == WindowMode::WINDOW_MODE_FULLSCREEN
                              ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_RECOVER
                              : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE;
    imageSourceInfo.SetResourceId(maxRecoverIcon);
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    iconImage->MarkModifyDone();
}

void ContainerModalPattern::OnWindowFocused()
{
    LOGE("ContainerModalPattern::OnWindowFocused()");
}
void ContainerModalPattern::OnWindowUnfocused()
{
    LOGE("ContainerModalPattern::OnWindowUnfocused()");
}

} // namespace OHOS::Ace::NG
