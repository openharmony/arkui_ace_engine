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

#include "core/components_ng/pattern/navigation/title_bar_pattern.h"

#include "core/animation/spring_curve.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t DEFAULT_ANIMATION_DURATION = 200;
constexpr int32_t TITLE_RATIO = 2;

void HandlePlatformVersionAboveTen(
    const RefPtr<FrameNode>& backButtonNode, const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    // API >= 10
    auto backButtonImageNode = AceType::DynamicCast<FrameNode>(backButtonNode->GetChildren().front());
    CHECK_NULL_VOID(backButtonImageNode);
    RefPtr<ImageLayoutProperty> backButtonImageLayoutProperty =
        backButtonImageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(backButtonImageLayoutProperty);

    bool noPixelMap = titleBarLayoutProperty->GetNoPixMapValue();
    if (noPixelMap && titleBarLayoutProperty->HasImageSource()) {
        backButtonImageLayoutProperty->UpdateImageSourceInfo(titleBarLayoutProperty->GetImageSourceValue());
        backButtonImageNode->MarkModifyDone();
        return;
    }

    if (!noPixelMap &&  titleBarLayoutProperty->HasPixelMap()) {
        auto pixelMap = titleBarLayoutProperty->GetPixelMapValue();
        backButtonImageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(pixelMap));
        backButtonImageNode->MarkModifyDone();
    }
}

void HandlePlatformVersionBelowTen(
    const RefPtr<FrameNode>& backButtonNode, const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    // API < 10
    RefPtr<ImageLayoutProperty> backButtonImageLayoutProperty =
        backButtonNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(backButtonImageLayoutProperty);
    if (titleBarLayoutProperty->HasImageSource()) {
        backButtonImageLayoutProperty->UpdateImageSourceInfo(titleBarLayoutProperty->GetImageSourceValue());
        backButtonNode->MarkModifyDone();
    }
}

void HandleDefaultIconForNavDestination(
    const RefPtr<TitleBarNode>& hostNode, const RefPtr<FrameNode>& backButtonImageNode)
{
    auto navDestinationNode = AceType::DynamicCast<FrameNode>(hostNode->GetParent());
    CHECK_NULL_VOID(navDestinationNode);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto navDestinationEventHub = navDestinationNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(navDestinationEventHub);
    auto paintProperty = backButtonImageNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(paintProperty);
    // If use defalut icon, need to set fill-color
    if (!navDestinationEventHub->IsEnabled()) {
        paintProperty->UpdateSvgFillColor(theme->GetBackButtonIconColor().BlendOpacity(theme->GetAlphaDisabled()));
    } else {
        paintProperty->UpdateSvgFillColor(theme->GetBackButtonIconColor());
    }
    backButtonImageNode->MarkModifyDone();
}

void MountBackButton(const RefPtr<TitleBarNode>& hostNode)
{
    auto titleBarLayoutProperty = hostNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(hostNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    auto backButtonImageNode = AceType::DynamicCast<FrameNode>(backButtonNode->GetChildren().front());
    CHECK_NULL_VOID(backButtonImageNode);
    auto parentType = titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR);
    if (parentType == TitleBarParentType::NAVBAR) {
        auto backButtonImageLayoutProperty = backButtonImageNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(backButtonImageLayoutProperty);

        if (titleBarLayoutProperty->HasNoPixMap()) {
            bool noPixelMap = titleBarLayoutProperty->GetNoPixMapValue();
            if (noPixelMap && titleBarLayoutProperty->HasImageSource()) {
                backButtonImageLayoutProperty->UpdateImageSourceInfo(titleBarLayoutProperty->GetImageSourceValue());
            }
            if (!noPixelMap && titleBarLayoutProperty->HasPixelMap()) {
                auto pixelMap = titleBarLayoutProperty->GetPixelMapValue();
                backButtonImageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(pixelMap));
                backButtonImageNode->MarkModifyDone();
            }
        }

        auto navBarNode = AceType::DynamicCast<FrameNode>(hostNode->GetParent());
        CHECK_NULL_VOID(navBarNode);
        auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
        CHECK_NULL_VOID(navBarLayoutProperty);
        auto hideBackButton = navBarLayoutProperty->GetHideBackButtonValue(false);
        auto backButtonLayoutProperty = AceType::DynamicCast<FrameNode>(backButtonNode)->GetLayoutProperty();
        CHECK_NULL_VOID(backButtonLayoutProperty);
        backButtonLayoutProperty->UpdateVisibility(hideBackButton ? VisibleType::GONE : VisibleType::VISIBLE);
        backButtonNode->SetActive(hideBackButton ? false : true);
        backButtonImageNode->MarkModifyDone();
        return;
    }

    if (!titleBarLayoutProperty->HasNoPixMap()) {
        if (parentType == TitleBarParentType::NAV_DESTINATION) {
            HandleDefaultIconForNavDestination(hostNode, backButtonImageNode);
        }
        backButtonNode->MarkModifyDone();
        return;
    }
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        HandlePlatformVersionBelowTen(backButtonNode, titleBarLayoutProperty);
    } else {
        HandlePlatformVersionAboveTen(backButtonNode, titleBarLayoutProperty);
    }
}

void MountSubTitle(const RefPtr<TitleBarNode>& hostNode)
{
    CHECK_NULL_VOID(hostNode);
    auto titleBarLayoutProperty = hostNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    auto subtitleNode = AceType::DynamicCast<FrameNode>(hostNode->GetSubtitle());
    CHECK_NULL_VOID(subtitleNode);
    auto titleLayoutProperty = subtitleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(titleLayoutProperty);

    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
        auto theme = NavigationGetTheme();
        CHECK_NULL_VOID(theme);
        titleLayoutProperty->UpdateAdaptMinFontSize(MIN_ADAPT_SUBTITLE_FONT_SIZE);
        titleLayoutProperty->UpdateAdaptMaxFontSize(theme->GetSubTitleFontSize());
        titleLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    }

    subtitleNode->MarkModifyDone();
}

} // namespace

void TitleBarPattern::InitTitleParam()
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    if (titleBarNode->GetSubtitle()) {
        tempTitleBarHeight_ = static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    } else {
        tempTitleBarHeight_ = static_cast<float>(FULL_SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    }
    overDragOffset_ = 0.0f;
    tempTitleOffsetY_ = 0.0f;
    fontSize_.reset();
    opacity_.reset();
    isFreeTitleUpdated_ = false;
}

bool TitleBarPattern::IsHidden()
{
    auto host = GetHost();
    auto navBarNode = AceType::DynamicCast<NavBarNode>(host->GetParent());
    CHECK_NULL_RETURN(navBarNode, false);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_RETURN(navBarLayoutProperty, false);
    return navBarLayoutProperty->GetHideTitleBar().value_or(false);
}

void TitleBarPattern::MountTitle(const RefPtr<TitleBarNode>& hostNode)
{
    auto titleBarLayoutProperty = hostNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    auto titleNode = AceType::DynamicCast<FrameNode>(hostNode->GetTitle());
    CHECK_NULL_VOID(titleNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetParent());
    CHECK_NULL_VOID(navBarNode);
    // if title node is custom node markModifyDone and return
    if (navBarNode->GetPrevTitleIsCustomValue(false)) {
        titleNode->MarkModifyDone();
        return;
    }

    auto titleLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(titleLayoutProperty);

    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto currentFontSize = titleLayoutProperty->GetFontSizeValue(Dimension(0));
    auto currentMaxLine = titleLayoutProperty->GetMaxLinesValue(0);
    auto titleMode = titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);
    if (titleMode == NavigationTitleMode::MINI) {
        if (titleBarLayoutProperty->HasHideBackButton() && titleBarLayoutProperty->GetHideBackButtonValue()) {
            titleLayoutProperty->UpdateFontSize(theme->GetTitleFontSize());
            titleLayoutProperty->UpdateAdaptMaxFontSize(theme->GetTitleFontSize());
        } else {
            titleLayoutProperty->UpdateFontSize(theme->GetTitleFontSizeMin());
            titleLayoutProperty->UpdateAdaptMaxFontSize(theme->GetTitleFontSizeMin());
        }
        UpdateSubTitleOpacity(1.0);
    } else if (titleMode == NavigationTitleMode::FULL) {
        titleLayoutProperty->UpdateFontSize(theme->GetTitleFontSizeBig());
        titleLayoutProperty->UpdateAdaptMaxFontSize(theme->GetTitleFontSizeBig());
        UpdateSubTitleOpacity(1.0);
    } else {
        if (fontSize_.has_value()) {
            titleLayoutProperty->UpdateFontSize(Dimension(fontSize_.value(), DimensionUnit::PX));
            titleLayoutProperty->UpdateAdaptMaxFontSize(Dimension(fontSize_.value(), DimensionUnit::PX));
        } else {
            titleLayoutProperty->UpdateFontSize(theme->GetTitleFontSizeBig());
            titleLayoutProperty->UpdateAdaptMaxFontSize(theme->GetTitleFontSizeBig());
        }
        if (opacity_.has_value()) {
            UpdateSubTitleOpacity(opacity_.value());
        } else {
            UpdateSubTitleOpacity(1.0);
        }
    }

    titleLayoutProperty->UpdateAdaptMinFontSize(MIN_ADAPT_TITLE_FONT_SIZE);
    titleLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    auto maxLines = hostNode->GetSubtitle() ? 1 : TITLEBAR_MAX_LINES;
    titleLayoutProperty->UpdateMaxLines(maxLines);
    if (currentFontSize != titleLayoutProperty->GetFontSizeValue(Dimension(0)) ||
        currentMaxLine != titleLayoutProperty->GetMaxLinesValue(0)) {
        titleNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
    titleNode->MarkModifyDone();
}

void TitleBarPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    if (isInitialTitle_) {
        InitTitleParam();
    }
    auto hostNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    MountBackButton(hostNode);
    MountTitle(hostNode);
    MountSubTitle(hostNode);
}

void TitleBarPattern::ProcessTitleDragStart(float offset)
{
    if (Positive(overDragOffset_)) {
        return;
    }
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::FREE ||
        IsHidden()) {
        return;
    }
    if (springController_ && !springController_->IsStopped()) {
        // clear stop listener before stop
        springController_->ClearStopListeners();
        springController_->Stop();
    }
    if (animator_ && !animator_->IsStopped()) {
        animator_->Stop();
    }

    defaultTitleBarHeight_ = currentTitleBarHeight_;
    SetMaxTitleBarHeight();
    SetTempTitleBarHeight(offset);
    minTitleOffsetY_ = (static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - minTitleHeight_) / 2.0f;
    maxTitleOffsetY_ = initialTitleOffsetY_;
    moveRatio_ = (maxTitleOffsetY_ - minTitleOffsetY_) /
                 (maxTitleBarHeight_ - static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    titleMoveDistance_ = (tempTitleBarHeight_ - defaultTitleBarHeight_) * moveRatio_;
    defaultTitleOffsetY_ = currentTitleOffsetY_;
    SetTempTitleOffsetY();
    defaultSubtitleOffsetY_ = GetSubTitleOffsetY();
    SetTempSubTitleOffsetY();
    titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);

    // title font size
    SetDefaultTitleFontSize();
    auto mappedOffset = GetMappedOffset(offset);
    auto tempFontSize = GetFontSize(mappedOffset);
    UpdateTitleFontSize(Dimension(tempFontSize, DimensionUnit::PX));

    // subTitle Opacity
    SetDefaultSubtitleOpacity();
    auto tempOpacity = GetSubtitleOpacity();
    UpdateSubTitleOpacity(tempOpacity);

    isFreeTitleUpdated_ = true;
}

void TitleBarPattern::ProcessTitleDragUpdate(float offset)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::FREE ||
        IsHidden()) {
        return;
    }
    SetTempTitleBarHeight(offset);
    titleMoveDistance_ = (tempTitleBarHeight_ - defaultTitleBarHeight_) * moveRatio_;
    SetTempTitleOffsetY();
    SetTempSubTitleOffsetY();
    titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);

    // title font size
    auto mappedOffset = GetMappedOffset(offset);
    fontSize_ = GetFontSize(mappedOffset);
    UpdateTitleFontSize(Dimension(fontSize_.value(), DimensionUnit::PX));

    // subTitle Opacity
    opacity_ = GetSubtitleOpacity();
    UpdateSubTitleOpacity(opacity_.value());
}

void TitleBarPattern::ProcessTitleDragEnd()
{
    if (Positive(overDragOffset_)) {
        return;
    }
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::FREE ||
        IsHidden()) {
        return;
    }

    if (Positive(overDragOffset_)) {
        SpringAnimation(overDragOffset_, 0);
    }
    if (CanOverDrag_ || isTitleScaleChange_) {
        auto titleMiddleValue =
            (static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) + maxTitleBarHeight_) / TITLE_RATIO;
        if (LessNotEqual(tempTitleBarHeight_, titleMiddleValue) || NearEqual(tempTitleBarHeight_, titleMiddleValue)) {
            AnimateTo(static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - defaultTitleBarHeight_);
            return;
        } else if (GreatNotEqual(tempTitleBarHeight_, titleMiddleValue)) {
            AnimateTo(maxTitleBarHeight_ - defaultTitleBarHeight_);
            return;
        }
    }
}

float TitleBarPattern::GetSubtitleOpacity()
{
    auto titleBarHeightDiff = maxTitleBarHeight_ - static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    opacityRatio_ = 1.0f / titleBarHeightDiff;
    auto tempOpacity = static_cast<float>(
        (tempTitleBarHeight_ - static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx())) * opacityRatio_ + 0.0f);
    return tempOpacity;
}

float TitleBarPattern::GetFontSize(float offset)
{
    auto titleBarHeight = defaultTitleBarHeight_ + offset;
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, 0.0f);
    auto titleFontSizeDiff = theme->GetTitleFontSizeBig() - theme->GetTitleFontSize();
    auto titleBarHeightDiff = maxTitleBarHeight_ - static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    fontSizeRatio_ = titleFontSizeDiff.ConvertToPx() / titleBarHeightDiff;
    auto tempFontSize = static_cast<float>(
        (titleBarHeight - static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx())) * fontSizeRatio_ +
        theme->GetTitleFontSize().ConvertToPx());
    if (GreatNotEqual(tempFontSize, theme->GetTitleFontSizeBig().ConvertToPx())) {
        tempFontSize = theme->GetTitleFontSizeBig().ConvertToPx();
    }
    if (LessNotEqual(tempFontSize, theme->GetTitleFontSize().ConvertToPx())) {
        tempFontSize = theme->GetTitleFontSize().ConvertToPx();
    }
    return tempFontSize;
}

float TitleBarPattern::GetMappedOffset(float offset)
{
    auto titleOffset = offset + defaultTitleBarHeight_ - static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    auto heightDiff = maxTitleBarHeight_ - static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    float moveRatio = Curves::SHARP->MoveInternal(std::clamp(titleOffset / heightDiff, 0.0f, 1.0f));
    auto mappedTitleOffset = moveRatio * heightDiff;
    auto mappedOffset =
        mappedTitleOffset - defaultTitleBarHeight_ + static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    return mappedOffset;
}

void TitleBarPattern::SpringAnimation(float startPos, float endPos)
{
    float mass = 1.0f;        // The move animation spring curve mass is 1.0f
    float stiffness = 228.0f; // The move animation spring curve stiffness is 228.0f
    float damping = 30.0f;    // The move animation spring curve damping is 30.0f
    const RefPtr<SpringProperty> DEFAULT_OVER_SPRING_PROPERTY =
        AceType::MakeRefPtr<SpringProperty>(mass, stiffness, damping);
    if (!springMotion_) {
        springMotion_ = AceType::MakeRefPtr<SpringMotion>(overDragOffset_, 0, 0, DEFAULT_OVER_SPRING_PROPERTY);
    } else {
        springMotion_->Reset(overDragOffset_, 0, 0, DEFAULT_OVER_SPRING_PROPERTY);
        springMotion_->ClearListeners();
    }
    springMotion_->AddListener([weak = AceType::WeakClaim(this)](float value) {
        auto titlebar = weak.Upgrade();
        CHECK_NULL_VOID(titlebar);
        titlebar->SetOverDragOffset(value);
        titlebar->tempTitleBarHeight_ = titlebar->maxTitleBarHeight_ + value / 6.0f;
        titlebar->UpdateScaleByDragOverDragOffset(value);
        auto host = titlebar->GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    });

    if (!springController_) {
        springController_ = AceType::MakeRefPtr<Animator>(PipelineBase::GetCurrentContext());
    }
    springController_->ClearStopListeners();
    springController_->PlayMotion(springMotion_);
    springController_->AddStopListener([weak = AceType::WeakClaim(this)]() {
        auto titlebar = weak.Upgrade();
        CHECK_NULL_VOID(titlebar);
        titlebar->ClearDragState();
        auto host = titlebar->GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    });
}

void TitleBarPattern::ClearDragState()
{
    overDragOffset_ = 0.0f;
}

void TitleBarPattern::UpdateScaleByDragOverDragOffset(float overDragOffset)
{
    if (Negative(overDragOffset)) {
        return;
    }
    auto host = GetHost();
    auto navBarNode = AceType::DynamicCast<NavBarNode>(host->GetParent());
    CHECK_NULL_VOID(navBarNode);
    if (navBarNode->GetPrevTitleIsCustomValue(true)) {
        return;
    }
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    if (navBarLayoutProperty->GetHideTitleBar().value_or(false)) {
        return;
    }

    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleNode = titleBarNode->GetTitle();
    CHECK_NULL_VOID(titleNode);
    auto title = AceType::DynamicCast<FrameNode>(titleNode);
    TransformScale(overDragOffset, title);
    auto subtitleNode = titleBarNode->GetSubtitle();
    if (subtitleNode) {
        auto subtitle = AceType::DynamicCast<FrameNode>(subtitleNode);
        TransformScale(overDragOffset, subtitle);
    }

    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TitleBarPattern::TransformScale(float overDragOffset, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto renderCtx = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderCtx);
    auto offset = std::clamp(overDragOffset, 0.0f, static_cast<float>(MAX_OVER_DRAG_OFFSET.ConvertToPx()));
    auto scaleRatio = offset / static_cast<float>(MAX_OVER_DRAG_OFFSET.ConvertToPx());
    VectorF scaleValue = VectorF(scaleRatio * 0.1f + 1.0f, scaleRatio * 0.1f + 1.0f);
    renderCtx->UpdateTransformScale(scaleValue);
}

void TitleBarPattern::AnimateTo(float offset)
{
    if (!animator_) {
        animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    }
    auto animation = AceType::MakeRefPtr<CurveAnimation<float>>(GetCurrentOffset(), offset, Curves::FAST_OUT_SLOW_IN);
    animation->AddListener([weakScroll = AceType::WeakClaim(this)](float value) {
        auto titlebar = weakScroll.Upgrade();
        CHECK_NULL_VOID(titlebar);
        titlebar->ProcessTitleDragUpdate(value);
        auto host = titlebar->GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    });
    animator_->ClearInterpolators();
    animator_->AddInterpolator(animation);
    animator_->SetDuration(DEFAULT_ANIMATION_DURATION);
    animator_->Play();
}

void TitleBarPattern::SetMaxTitleBarHeight()
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    if (titleBarNode->GetSubtitle()) {
        maxTitleBarHeight_ = static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    } else {
        maxTitleBarHeight_ = static_cast<float>(FULL_SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    }
}

void TitleBarPattern::SetTempTitleBarHeight(float offsetY)
{
    tempTitleBarHeight_ = defaultTitleBarHeight_ + offsetY;
    if (tempTitleBarHeight_ < static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx())) {
        tempTitleBarHeight_ = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    }
    if (tempTitleBarHeight_ > maxTitleBarHeight_) {
        tempTitleBarHeight_ = maxTitleBarHeight_;
    }
}

void TitleBarPattern::SetTempTitleOffsetY()
{
    tempTitleOffsetY_ = defaultTitleOffsetY_ + titleMoveDistance_;
    if (tempTitleOffsetY_ < minTitleOffsetY_) {
        tempTitleOffsetY_ = minTitleOffsetY_;
    }
    if (tempTitleOffsetY_ > maxTitleOffsetY_) {
        tempTitleOffsetY_ = maxTitleOffsetY_;
    }
}

void TitleBarPattern::SetTempSubTitleOffsetY()
{
    tempSubTitleOffsetY_ = tempTitleOffsetY_ + GetTitleHeight();
    if (tempTitleOffsetY_ < minTitleOffsetY_) {
        tempSubTitleOffsetY_ = minTitleOffsetY_;
    }
    if (tempTitleOffsetY_ > maxTitleOffsetY_) {
        tempSubTitleOffsetY_ = maxTitleOffsetY_;
    }
}

void TitleBarPattern::SetDefaultTitleFontSize()
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    CHECK_NULL_VOID(titleBarNode->GetTitle());
    auto titleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
    CHECK_NULL_VOID(titleNode);
    auto textLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    defaultTitleFontSize_ = theme->GetTitleFontSize();
}

void TitleBarPattern::SetDefaultSubtitleOpacity()
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    CHECK_NULL_VOID(titleBarNode->GetSubtitle());
    auto subtitleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
    CHECK_NULL_VOID(subtitleNode);
    auto context = subtitleNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    if (defaultTitleBarHeight_ == maxTitleBarHeight_) {
        defaultSubtitleOpacity_ = context->GetOpacityValue(1.0f);
    } else {
        defaultSubtitleOpacity_ = context->GetOpacityValue(0.0f);
    }
}

float TitleBarPattern::GetTitleHeight()
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_RETURN(titleBarNode, 0.0f);
    auto titleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
    CHECK_NULL_RETURN(titleNode, 0.0f);
    auto geometryNode = titleNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);
    return geometryNode->GetFrameSize().Height();
}

float TitleBarPattern::GetSubTitleOffsetY()
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_RETURN(titleBarNode, 0.0f);
    auto subTitleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
    CHECK_NULL_RETURN(subTitleNode, 0.0f);
    auto geometryNode = subTitleNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);
    return geometryNode->GetMarginFrameOffset().GetY();
}

void TitleBarPattern::UpdateTitleFontSize(const Dimension& tempTitleFontSize)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
    CHECK_NULL_VOID(titleNode);
    auto textLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateFontSize(tempTitleFontSize);
    textLayoutProperty->UpdateAdaptMaxFontSize(tempTitleFontSize);
    titleNode->MarkModifyDone();
}

void TitleBarPattern::UpdateSubTitleOpacity(const double& value)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto subTitleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
    CHECK_NULL_VOID(subTitleNode);
    auto context = subTitleNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateOpacity(value);
}

bool TitleBarPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto titleBarLayoutAlgorithm = DynamicCast<TitleBarLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(titleBarLayoutAlgorithm, false);
    UpdateTitleModeChange();

    initialTitleOffsetY_ = titleBarLayoutAlgorithm->GetInitialTitleOffsetY();
    isInitialTitle_ = titleBarLayoutAlgorithm->IsInitialTitle();
    initialSubtitleOffsetY_ = titleBarLayoutAlgorithm->GetInitialSubtitleOffsetY();
    isInitialSubtitle_ = titleBarLayoutAlgorithm->IsInitialSubtitle();
    minTitleHeight_ = titleBarLayoutAlgorithm->GetMinTitleHeight();
    return true;
}

void TitleBarPattern::UpdateTitleModeChange()
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    auto geometryNode = titleBarNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto titleBarHeight = geometryNode->GetFrameSize().Height();
    if ((titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::FREE) &&
        !NearZero(maxTitleBarHeight_)) {
        if (titleBarHeight >= maxTitleBarHeight_) {
            titleMode_ = NavigationTitleMode::FULL;
        } else if (NearEqual(titleBarHeight, static_cast<float>(TITLEBAR_HEIGHT_MINI.ConvertToPx()))) {
            titleMode_ = NavigationTitleMode::MINI;
        }
    }
}

void TitleBarPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);

    SetBackgroundAndBlur();

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        SafeAreaExpandOpts opts = {.type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_TOP};
        host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    }
}

void TitleBarPattern::OnCoordScrollStart()
{
    coordScrollOffset_ = 0.0f;
    coordScrollFinalOffset_ = 0.0f;
    isFreeTitleUpdated_ = true;

    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::FREE) {
        return;
    }
    if (springController_ && !springController_->IsStopped()) {
        // clear stop listener before stop
        springController_->ClearStopListeners();
        springController_->Stop();
    }
    if (animator_ && !animator_->IsStopped()) {
        animator_->Stop();
    }

    defaultTitleBarHeight_ = currentTitleBarHeight_;
    defaultTitleOffsetY_ = currentTitleOffsetY_;
    SetMaxTitleBarHeight();
    SetTempTitleBarHeight(0);
    minTitleOffsetY_ = (static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - minTitleHeight_) / 2.0f;
    maxTitleOffsetY_ = initialTitleOffsetY_;
    moveRatio_ = (maxTitleOffsetY_ - minTitleOffsetY_) /
                 (maxTitleBarHeight_ - static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    titleMoveDistance_ = (tempTitleBarHeight_ - defaultTitleBarHeight_) * moveRatio_;
}

float TitleBarPattern::OnCoordScrollUpdate(float offset)
{
    float lastOffset = coordScrollOffset_;
    coordScrollOffset_ += offset;

    float offsetHandled = 0.0f;
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    float titleBarOffset = coordScrollOffset_;
    if (LessNotEqual(defaultTitleBarHeight_ + titleBarOffset, minHeight)) {
        // The target height is smaller than the minHeight, so the titleBarOffset is adjusted to modify the height to
        // the minHeight.
        titleBarOffset = minHeight - defaultTitleBarHeight_;
        overDragOffset_ = 0.0f;
        offsetHandled = CalculateHandledOffsetMinTitle(offset, lastOffset);
    } else if (GreatNotEqual(defaultTitleBarHeight_ + titleBarOffset, maxTitleBarHeight_)) {
        // The target height is greater than the maxTitleBarHeight_, so overDragOffset_ needs to be updated.
        overDragOffset_ = defaultTitleBarHeight_ + titleBarOffset - maxTitleBarHeight_;
        offsetHandled = CalculateHandledOffsetMaxTitle(offset, lastOffset);
    } else {
        // The target height is between the minHeight and the maxTitleBarHeight_.
        overDragOffset_ = 0.0f;
        offsetHandled = CalculateHandledOffsetBetweenMinAndMaxTitle(offset, lastOffset);
    }
    UpdateTitleBarByCoordScroll(titleBarOffset);
    coordScrollFinalOffset_ = titleBarOffset;

    return offsetHandled;
}

void TitleBarPattern::OnCoordScrollEnd()
{
    if (NearZero(coordScrollOffset_)) {
        return;
    }
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    float middleHeight =
        (static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) + maxTitleBarHeight_) / TITLE_RATIO;
    float finalHeight = defaultTitleBarHeight_ + coordScrollFinalOffset_;
    if (GreatNotEqual(finalHeight, minHeight) && LessOrEqual(finalHeight, middleHeight)) {
        // The finalHeight is between the minHeight and the middleHeight, so animate to min title.
        AnimateTo(static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - defaultTitleBarHeight_);
    } else if (GreatNotEqual(finalHeight, middleHeight) && LessNotEqual(finalHeight, maxTitleBarHeight_)) {
        // The finalHeight is between the middleHeight and the maxTitleBarHeight_, so animate to max title.
        AnimateTo(maxTitleBarHeight_ - defaultTitleBarHeight_);
    } else if (GreatNotEqual(finalHeight, maxTitleBarHeight_)) {
        // The finalHeight is bigger than the maxTitleBarHeight_, so animate to max title.
        SpringAnimation(finalHeight - maxTitleBarHeight_, 0);
    }
}

void TitleBarPattern::UpdateTitleBarByCoordScroll(float offset)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::FREE) {
        return;
    }
    SetTitleStyleByCoordScrollOffset(offset);
    UpdateScaleByDragOverDragOffset(overDragOffset_);
}

void TitleBarPattern::SetTitleStyleByCoordScrollOffset(float offset)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::FREE) {
        return;
    }
    if (Positive(overDragOffset_)) {
        tempTitleBarHeight_ = maxTitleBarHeight_ + overDragOffset_ / 6.0f;
        titleMoveDistance_ = (maxTitleBarHeight_ - defaultTitleBarHeight_) * moveRatio_ + overDragOffset_ / 6.0f;
    } else {
        SetTempTitleBarHeight(offset);
        titleMoveDistance_ = (tempTitleBarHeight_ - defaultTitleBarHeight_) * moveRatio_;
    }

    SetTempTitleOffsetY();
    SetTempSubTitleOffsetY();
    titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);

    // title font size
    auto mappedOffset = GetMappedOffset(offset);
    fontSize_ = GetFontSize(mappedOffset);
    UpdateTitleFontSize(Dimension(fontSize_.value(), DimensionUnit::PX));

    // subTitle Opacity
    opacity_ = GetSubtitleOpacity();
    UpdateSubTitleOpacity(opacity_.value());
}

void TitleBarPattern::OnColorConfigurationUpdate()
{
    SetBackgroundAndBlur();

    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto backButton = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_VOID(backButton);
    if (backButton->GetTag() == "Navigator") {
        backButton = AceType::DynamicCast<FrameNode>(backButton->GetChildren().front());
        CHECK_NULL_VOID(backButton);
    }
    auto backButtonImgNode = AceType::DynamicCast<FrameNode>(backButton->GetChildren().front());
    CHECK_NULL_VOID(backButtonImgNode);
    auto backButtonImgRender = backButtonImgNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(backButtonImgRender);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    backButtonImgRender->UpdateSvgFillColor(theme->GetBackButtonIconColor());
    backButtonImgNode->MarkModifyDone();
}

float TitleBarPattern::CalculateHandledOffsetMinTitle(float offset, float lastCordScrollOffset)
{
    float offsetHandled = 0.0f;
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    if (LessOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, minHeight)) {
        // The starting height of this update is smaller than the minHeight, so the navigation component does
        // not handle the offset.
        offsetHandled = 0.0f;
    } else if (GreatOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, maxTitleBarHeight_)) {
        // The starting position height of this update is greater than the maxTitleBarHeight_, so the navigation
        // component only handles offsets from maxTitleBarHeight_ to minHeight.
        offsetHandled = minHeight - maxTitleBarHeight_;
    } else {
        // The starting position height of this update is between the minHeight and the maxTitleBarHeight_, so the
        // navigation component only handles offsets from defaultTitleBarHeight_ to minHeight.
        offsetHandled = offset - (coordScrollOffset_ - (minHeight - defaultTitleBarHeight_));
    }
    return offsetHandled;
}

float TitleBarPattern::CalculateHandledOffsetMaxTitle(float offset, float lastCordScrollOffset)
{
    float offsetHandled = 0.0f;
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    if (GreatOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, maxTitleBarHeight_)) {
        // The starting height of this update is greater than the maxTitleBarHeight_, so the navigation component
        // does not handle the offset.
        offsetHandled = 0.0f;
    } else if (LessOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, minHeight)) {
        // The starting position height of this update is smaller than the minHeight, so the navigation component
        // only handles offsets from minHeight to maxTitleBarHeight_.
        offsetHandled = maxTitleBarHeight_ - minHeight;
    } else {
        // The starting position height of this update is between the minHeight and the maxTitleBarHeight_, so the
        // navigation component only handles offsets from defaultTitleBarHeight_ to maxTitleBarHeight_.
        offsetHandled = offset - (coordScrollOffset_ - (maxTitleBarHeight_ - defaultTitleBarHeight_));
    }
    return offsetHandled;
}

float TitleBarPattern::CalculateHandledOffsetBetweenMinAndMaxTitle(float offset, float lastCordScrollOffset)
{
    float offsetHandled = 0.0f;
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    if (LessOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, minHeight)) {
        // The starting height of this update is smaller than the minHeight, so the navigation component only
        // handles offsets from minHeight to target height.
        offsetHandled = coordScrollOffset_ - (defaultTitleBarHeight_ - minHeight);
    } else if (GreatOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, maxTitleBarHeight_)) {
        // The starting position height of this update is greater than the maxTitleBarHeight_, so the navigation
        // component only handles offsets from maxTitleBarHeight_ to target height.
        offsetHandled = coordScrollOffset_ - (maxTitleBarHeight_ - defaultTitleBarHeight_);
    } else {
        // The starting position height of this update is between the minHeight and the maxTitleBarHeight_, so the
        // navigation component handles all of the offset.
        offsetHandled = offset;
    }
    return offsetHandled;
}

void TitleBarPattern::SetBackgroundAndBlur()
{
    if (SystemProperties::GetNavigationBlurEnabled() &&
        Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        auto theme = NavigationGetTheme();
        CHECK_NULL_VOID(theme);
        renderContext->UpdateBackgroundColor(theme->GetBackgroundBlurColor());

        BlurStyleOption blur;
        blur.blurStyle = BlurStyle::COMPONENT_THICK;
        renderContext->UpdateBackBlurStyle(blur);
    }
}
} // namespace OHOS::Ace::NG
