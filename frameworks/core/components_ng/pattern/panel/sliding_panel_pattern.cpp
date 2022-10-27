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

#include "core/components_ng/pattern/panel/sliding_panel_pattern.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/animation/friction_motion.h"
#include "core/animation/spring_animation.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

constexpr int32_t ANIMATION_BASE_DURATION = 256;
constexpr Dimension BLANK_MIN_HEIGHT = 8.0_vp;
constexpr Dimension DRAG_BAR_HEIGHT = 8.0_vp;
constexpr Dimension DRAG_UP_THRESHOLD = 48.0_vp;
constexpr double VELOCITY_THRESHOLD = 1000.0; // Move 1000px per second.

} // namespace

void SlidingPanelPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    InitPanEvent(gestureHub);
    Update();
}

void SlidingPanelPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

bool SlidingPanelPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<SlidingPanelLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    InitializeLayoutProps();
    currentOffset_ = layoutAlgorithm->GetCurrentOffset();
    isFirstLayout_ = layoutAlgorithm->GetIsFirstLayout();
    fullHeight_ = layoutAlgorithm->GetFullHeight();
    halfHeight_ = layoutAlgorithm->GetHalfHeight();
    miniHeight_ = layoutAlgorithm->GetMiniHeight();
    return true;
}

void SlidingPanelPattern::Update()
{
    previousMode_ = mode_;
    auto layoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    mode_ = layoutProperty->GetPanelMode() == PanelMode::AUTO
                ? PanelMode::FULL
                : layoutProperty->GetPanelMode().value_or(PanelMode::HALF);
    type_ = layoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR);
}

void SlidingPanelPattern::InitializeLayoutProps()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto child = host->GetChildren();
    if (child.empty() || child.size() != 1) {
        LOGE("Children size wrong in slide panel modal");
        return;
    }

    auto maxSize = host->GetGeometryNode()->GetFrameSize();
    auto layoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    auto defaultFullHeight = Dimension(maxSize.Height() - BLANK_MIN_HEIGHT.ConvertToPx());
    auto fullHeight = layoutProperty->GetFullHeight().value_or(defaultFullHeight).ConvertToPx();
    auto halfHeight = layoutProperty->GetHalfHeight().value_or(Dimension(maxSize.Height() / 2)).ConvertToPx();
    auto miniHeight =
        layoutProperty->GetMiniHeight().value_or(Dimension(DRAG_UP_THRESHOLD.ConvertToPx())).ConvertToPx();
    if (defaultBlankHeights_.empty()) {
        defaultBlankHeights_[PanelMode::FULL] = maxSize.Height() - fullHeight;
        defaultBlankHeights_[PanelMode::HALF] = maxSize.Height() - halfHeight;
        defaultBlankHeights_[PanelMode::MINI] = maxSize.Height() - miniHeight;
        CheckHeightValidity();
        fullHalfBoundary_ = defaultBlankHeights_[PanelMode::FULL] +
                            (defaultBlankHeights_[PanelMode::HALF] - defaultBlankHeights_[PanelMode::FULL]) / 2.0;
        halfMiniBoundary_ = defaultBlankHeights_[PanelMode::HALF] +
                            (defaultBlankHeights_[PanelMode::MINI] - defaultBlankHeights_[PanelMode::HALF]) / 2.0;
        fullMiniBoundary_ = defaultBlankHeights_[PanelMode::FULL] +
                            (defaultBlankHeights_[PanelMode::MINI] - defaultBlankHeights_[PanelMode::FULL]) / 2.0;
    }
    minBlankHeight_ = BLANK_MIN_HEIGHT.ConvertToPx();

    if (isFirstLayout_) {
        CheckPanelModeandType();
        AnimateTo(defaultBlankHeights_[mode_], mode_);
        if (previousMode_ != mode_) {
            FireSizeChangeEvent();
        }
        auto dragBar = GetDragBarNode();
        auto dragBarPattern = dragBar->GetPattern<DragBarPattern>();
        CHECK_NULL_VOID(dragBarPattern);
        dragBarPattern->ShowInPanelMode(mode_);
        isFirstLayout_ = false;
    }
}

void SlidingPanelPattern::CheckHeightValidity()
{
    auto minBlank = BLANK_MIN_HEIGHT.ConvertToPx();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();

    auto maxBlank = geometryNode->GetFrameSize().Height() - DRAG_BAR_HEIGHT.ConvertToPx();
    defaultBlankHeights_[PanelMode::MINI] = std::clamp(defaultBlankHeights_[PanelMode::MINI], minBlank, maxBlank);
    defaultBlankHeights_[PanelMode::HALF] = std::clamp(defaultBlankHeights_[PanelMode::HALF], minBlank, maxBlank);
    defaultBlankHeights_[PanelMode::FULL] = std::clamp(defaultBlankHeights_[PanelMode::FULL], minBlank, maxBlank);
}

void SlidingPanelPattern::CheckPanelModeandType()
{
    // This parameter does not take effect when PanelMode is set to Half and PanelType is set to minibar
    if (mode_ == PanelMode::HALF && type_ == PanelType::MINI_BAR) {
        mode_ = PanelMode::MINI;
    }

    // This parameter does not take effect when PanelMode is set to Mini and PanelType is set to temporary
    if (mode_ == PanelMode::MINI && type_ == PanelType::TEMP_DISPLAY) {
        mode_ = PanelMode::HALF;
    }
}

void SlidingPanelPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (panEvent_) {
        return;
    }
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& startInfo) {
        LOGI("Pan event start");
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragStart(startInfo.GetLocalLocation());
        }
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragUpdate(info);
        }
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        LOGI("Pan event end mainVelocity: %{public}lf", info.GetMainVelocity());
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragEnd(info.GetMainVelocity());
        }
    };

    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    float distance = DEFAULT_PAN_DISTANCE;
    auto host = GetHost();
    if (host) {
        auto context = host->GetContext();
        if (context) {
            distance = static_cast<float>(
                context->NormalizeToPx(Dimension(DEFAULT_PAN_DISTANCE, DimensionUnit::VP))); // convert VP to Px
        }
    }
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), nullptr);
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, distance);
}

void SlidingPanelPattern::HandleDragStart(const Offset& startPoint) // const GestureEvent& info
{
    if (isAnimating_) {
        return;
    }
    dragStartCurrentOffset_ = currentOffset_;
}

void SlidingPanelPattern::HandleDragUpdate(const GestureEvent& info)
{
    if (isAnimating_) {
        return;
    }
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto tempOffset = currentOffset_;
    UpdateCurrentOffset(mainDelta);
    if (NearEqual(currentOffset_, tempOffset)) {
        LOGI("Offset is not changed, needn't measure.");
        return;
    }
    FireHeightChangeEvent();
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void SlidingPanelPattern::HandleDragEnd(float dragVelocity)
{
    if (isAnimating_) {
        return;
    }
    auto dragLen = currentOffset_ - dragStartCurrentOffset_;
    type_ = GetPanelType();
    switch (type_) {
        case PanelType::MINI_BAR: { // FULL & MINI
            CalculateModeTypeMini(dragLen, dragVelocity);
            break;
        }
        case PanelType::FOLDABLE_BAR: { // FULL & HALF & MINI
            CalculateModeTypeFold(dragLen, dragVelocity);
            break;
        }
        case PanelType::TEMP_DISPLAY: { // FULL & HALF
            CalculateModeTypeTemp(dragLen, dragVelocity);
            break;
        }
        default: {
            LOGE("Unsupported type:%{public}d", type_);
            return;
        }
    }
    AnimateTo(defaultBlankHeights_[mode_], mode_);
    if (previousMode_ != mode_) {
        FireSizeChangeEvent();
        previousMode_ = mode_;
    }
}

void SlidingPanelPattern::CalculateModeTypeMini(float dragLen, float velocity) // FULL & MINI
{
    float currentPostion = currentOffset_;
    if (std::abs(velocity) < VELOCITY_THRESHOLD) {
        // Drag velocity not reached to threshold, mode based on the location.
        if (currentPostion < fullMiniBoundary_) {
            mode_ = PanelMode::FULL;
        } else {
            mode_ = PanelMode::MINI;
        }
    } else {
        // Drag velocity reached to threshold, mode based on the drag direction.
        if (velocity > 0.0) {
            mode_ = PanelMode::MINI;
        } else {
            mode_ = PanelMode::FULL;
        }
    }
}

void SlidingPanelPattern::CalculateModeTypeFold(float dragLen, float velocity) // // FULL & HALF & MINI
{
    float currentPostion = currentOffset_;
    if (std::abs(velocity) < VELOCITY_THRESHOLD) {
        // Drag velocity not reached to threshold, mode based on the location.
        if (currentPostion < fullHalfBoundary_) {
            mode_ = PanelMode::FULL;
        } else if (currentPostion < halfMiniBoundary_) {
            mode_ = PanelMode::HALF;
        } else {
            mode_ = PanelMode::MINI;
        }
    } else {
        // Drag velocity reached to threshold, mode based on the drag direction.
        if (velocity > 0.0) {
            if (currentPostion < defaultBlankHeights_[PanelMode::HALF]) {
                mode_ = PanelMode::HALF;
            } else {
                mode_ = PanelMode::MINI;
            }
        } else {
            if (currentPostion > defaultBlankHeights_[PanelMode::HALF]) {
                mode_ = PanelMode::HALF;
            } else {
                mode_ = PanelMode::FULL;
            }
        }
    }
}

void SlidingPanelPattern::CalculateModeTypeTemp(float dragLen, float velocity) // FULL & HALF
{
    float currentPostion = currentOffset_;
    if (std::abs(velocity) < VELOCITY_THRESHOLD) {
        // Drag velocity not reached to threshold, mode based on the location.
        if (currentPostion < fullHalfBoundary_) {
            mode_ = PanelMode::FULL;
        } else {
            mode_ = PanelMode::HALF;
        }
    } else {
        // Drag velocity reached to threshold, mode based on the drag direction.
        if (velocity > 0.0) {
            mode_ = PanelMode::HALF;
        } else {
            mode_ = PanelMode::FULL;
        }
    }
}

void SlidingPanelPattern::AnimateTo(float targetLocation, PanelMode mode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    animator_ = AceType::MakeRefPtr<Animator>(host->GetContext());
    isAnimating_ = true;
    animator_->ClearInterpolators();
    animator_->ClearAllListeners();
    if (animator_->IsRunning()) {
        animator_->Stop();
    }
    animator_->AddStopListener([weak = WeakClaim(this), mode]() {
        auto panel = weak.Upgrade();
        CHECK_NULL_VOID(panel);
        auto dragBar = panel->GetDragBarNode();
        panel->OnAnimationStop();
        auto dragBarPattern = dragBar->GetPattern<DragBarPattern>();
        CHECK_NULL_VOID(dragBarPattern);
        dragBarPattern->ShowInPanelMode(mode);
    });
    AppendBlankHeightAnimation(targetLocation, mode);
    auto geometryNode = host->GetGeometryNode();
    auto frameSize = geometryNode->GetFrameSize();
    auto dragRange = frameSize.Height();
    animator_->SetDuration(GetAnimationDuration(targetLocation - currentOffset_, dragRange)); // inner
    animator_->SetFillMode(FillMode::FORWARDS);
    animator_->Forward();
}

void SlidingPanelPattern::AppendBlankHeightAnimation(float targetLocation, PanelMode mode)
{
    auto springProperty = AceType::MakeRefPtr<SpringProperty>(1.0f, 100.0f, 20.0f);
    auto heightAnimation = AceType::MakeRefPtr<SpringAnimation>(springProperty);
    heightAnimation->AddListener(
        [weak = AceType::WeakClaim(this), start = currentOffset_, end = targetLocation, mode](float value) {
            auto panel = weak.Upgrade();
            if (!panel) {
                LOGE("Panel is null.");
                return;
            }
            if (value > 1.0) {
                auto dragBar = panel->GetDragBarNode();
                auto dragBarPattern = dragBar->GetPattern<DragBarPattern>();
                CHECK_NULL_VOID(dragBarPattern);
                dragBarPattern->ShowInPanelMode(mode);
            }
            panel->UpdateCurrentOffsetOnAnimate((end - start) * value + start);
            panel->FireHeightChangeEvent();
            panel->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        });
    animator_->AddInterpolator(heightAnimation);
}

RefPtr<FrameNode> SlidingPanelPattern::GetDragBarNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto column = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0));
    CHECK_NULL_RETURN(column, nullptr);
    auto dragBar = AceType::DynamicCast<FrameNode>(column->GetChildAtIndex(0));
    CHECK_NULL_RETURN(dragBar, nullptr);
    return dragBar;
}

int32_t SlidingPanelPattern::GetAnimationDuration(float delta, float dragRange) const
{
    if (NearZero(dragRange)) {
        return 0;
    }
    // duration is in millisecond
    return static_cast<int32_t>(((std::abs(delta) / dragRange) + 1.0) * ANIMATION_BASE_DURATION);
}

void SlidingPanelPattern::OnAnimationStop()
{
    isAnimating_ = false;
}

void SlidingPanelPattern::UpdateCurrentOffset(float offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    currentOffset_ = currentOffset_ + offset;
    auto frameSize = host->GetGeometryNode()->GetFrameSize();
    currentOffset_ = std::clamp(currentOffset_, static_cast<float>(BLANK_MIN_HEIGHT.ConvertToPx()),
        static_cast<float>((frameSize.Height() - DRAG_UP_THRESHOLD.ConvertToPx())));
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void SlidingPanelPattern::UpdateCurrentOffsetOnAnimate(float currentOffset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    currentOffset_ = currentOffset;
    auto frameSize = host->GetGeometryNode()->GetFrameSize();
    currentOffset_ = std::clamp(currentOffset_, static_cast<float>(BLANK_MIN_HEIGHT.ConvertToPx()),
        static_cast<float>((frameSize.Height() - DRAG_UP_THRESHOLD.ConvertToPx())));
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

PanelType SlidingPanelPattern::GetPanelType() const
{
    auto slidingLayoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    CHECK_NULL_RETURN(slidingLayoutProperty, PanelType::FOLDABLE_BAR);
    return slidingLayoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR);
}

PanelMode SlidingPanelPattern::GetPanelMode() const
{
    auto slidingLayoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    CHECK_NULL_RETURN(slidingLayoutProperty, PanelMode::HALF);
    return slidingLayoutProperty->GetPanelMode().value_or(PanelMode::HALF);
}

void SlidingPanelPattern::FireSizeChangeEvent()
{
    auto slidingPanelEventHub = GetEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(slidingPanelEventHub);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto frameSize = host->GetGeometryNode()->GetFrameSize();
    auto dragBar = GetDragBarNode();
    CHECK_NULL_VOID(dragBar);
    auto dragBarFrameSize = dragBar->GetGeometryNode()->GetFrameSize();
    float height = std::floor(frameSize.Height() - defaultBlankHeights_[mode_] - dragBarFrameSize.Height());
    float width = std::floor(frameSize.Width());
    slidingPanelEventHub->FireSizeChangeEvent(mode_, width, height);
}

void SlidingPanelPattern::FireHeightChangeEvent()
{
    auto slidingPanelEventHub = GetEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(slidingPanelEventHub);
    auto slidingLayoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    auto layoutConstraint = slidingLayoutProperty->GetLayoutConstraint();

    auto currentHeight = static_cast<float>(layoutConstraint->maxSize.Height() - currentOffset_);
    slidingPanelEventHub->FireHeightChangeEvent(currentHeight);
}

void SlidingPanelPattern::MarkDirtyNode(PropertyChangeFlag extraFlag)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(extraFlag);
}

void SlidingPanelPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    Pattern::ToJsonValue(json);
    auto layoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    static const char* PANEL_TYPE[] = { "PanelType.Minibar", "PanelType.Foldable", "PanelType.Temporary" };
    json->Put(
        "type", PANEL_TYPE[static_cast<int32_t>(layoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR))]);
    static const char* PANEL_MODE[] = { "PanelMode.Mini", "PanelMode.Half", "PanelMode.Full" };
    json->Put("mode", PANEL_MODE[static_cast<int32_t>(layoutProperty->GetPanelMode().value_or(PanelMode::HALF))]);
    json->Put("dragBar", layoutProperty->GetHasDragBar().value_or(true) ? "true" : "false");
    json->Put(
        "miniHeight", std::to_string(layoutProperty->GetMiniHeight().value_or(miniHeight_).ConvertToPx()).c_str());
    json->Put(
        "halfHeight", std::to_string(layoutProperty->GetHalfHeight().value_or(halfHeight_).ConvertToPx()).c_str());
    json->Put(
        "fullHeight", std::to_string(layoutProperty->GetFullHeight().value_or(fullHeight_).ConvertToPx()).c_str());
}

} // namespace OHOS::Ace::NG