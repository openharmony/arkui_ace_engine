/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper/swiper_pattern.h"

#include <algorithm>
#include <cmath>
#include <cstdint>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/utils.h"
#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/animation/spring_curve.h"
#include "core/common/container_scope.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/swiper/swiper_layout_algorithm.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_arrow_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/ace_events.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

// TODO use theme.
constexpr int32_t MIN_TURN_PAGE_VELOCITY = 180;
constexpr Dimension INDICATOR_BORDER_RADIUS = 16.0_vp;

constexpr Dimension SWIPER_MARGIN = 16.0_vp;
constexpr Dimension SWIPER_GUTTER = 16.0_vp;
// TODO define as common method
float CalculateFriction(float gamma)
{
    constexpr float SCROLL_RATIO = 0.72f;
    if (GreatOrEqual(gamma, 1.0)) {
        gamma = 1.0;
    }
    return SCROLL_RATIO * static_cast<float>(std::pow(1.0 - gamma, SQUARE));
}

} // namespace

SwiperPattern::SwiperPattern()
{
    swiperController_ = MakeRefPtr<SwiperController>();
}

void SwiperPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    host->GetRenderContext()->SetClipToBounds(true);
    host->GetRenderContext()->UpdateClipEdge(true);
    InitSurfaceChangedCallback();
}

RefPtr<LayoutAlgorithm> SwiperPattern::CreateLayoutAlgorithm()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto swiperPaintProperty = host->GetPaintProperty<SwiperPaintProperty>();
    auto swiperLayoutProperty = host->GetLayoutProperty<SwiperLayoutProperty>();
    auto swiperLayoutAlgorithm = MakeRefPtr<SwiperLayoutAlgorithm>();
    if (jumpIndex_) {
        if (jumpIndex_.value() < 0 || jumpIndex_.value() >= TotalCount()) {
            jumpIndex_ = 0;
            currentIndex_ = 0;
            currentFirstIndex_ = 0;
            swiperLayoutProperty->UpdateIndexWithoutMeasure(0);
        }
        swiperLayoutAlgorithm->SetJumpIndex(jumpIndex_.value());
    } else if (targetIndex_) {
        swiperLayoutAlgorithm->SetTargetIndex(targetIndex_.value());
    }
    swiperLayoutAlgorithm->SetContentCrossSize(contentCrossSize_);
    swiperLayoutAlgorithm->SetMainSizeIsMeasured(mainSizeIsMeasured_);
    swiperLayoutAlgorithm->SetContentMainSize(contentMainSize_);
    swiperLayoutAlgorithm->SetCurrentDelta(currentDelta_);
    swiperLayoutAlgorithm->SetItemsPosition(itemPosition_);
    if (IsOutOfBoundary() && !IsLoop()) {
        swiperLayoutAlgorithm->SetOverScrollFeature();
    }
    swiperLayoutAlgorithm->SetTotalItemCount(TotalCount());
    swiperLayoutAlgorithm->SetIsLoop(IsLoop());
    auto effect = swiperPaintProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING);
    bool canOverScroll = effect == EdgeEffect::SPRING;
    swiperLayoutAlgorithm->SetCanOverScroll(canOverScroll);
    return swiperLayoutAlgorithm;
}

void SwiperPattern::OnIndexChange() const
{
    auto totalCount = TotalCount();
    if (NonPositive(totalCount)) {
        return;
    }

    auto oldIndex = (oldIndex_ + totalCount) % totalCount;
    auto targetIndex = (CurrentIndex() + totalCount) % totalCount;
    if (oldIndex != targetIndex) {
        auto swiperEventHub = GetEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(swiperEventHub);
        swiperEventHub->FireChangeEvent(targetIndex);
        // lazyBuild feature.
        SetLazyLoadFeature(true);
    }
}

void SwiperPattern::OnModifyDone()
{
    currentOffset_ = 0.0f;
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    oldIndex_ = currentIndex_;
    InitIndicator();
    InitArrow();

    auto childrenSize = TotalCount();
    if (CurrentIndex() >= 0) {
        currentIndex_ = CurrentIndex();
        layoutProperty->UpdateIndexWithoutMeasure(currentIndex_);
    } else {
        LOGE("index is not valid: %{public}d, items size: %{public}d", CurrentIndex(), childrenSize);
    }
    if (oldIndex_ != currentIndex_) {
        jumpIndex_ = currentIndex_;
        currentFirstIndex_ = jumpIndex_.value_or(0);
        turnPageRate_ = 0.0f;
    }

    RegisterVisibleAreaChange();
    InitSwiperController();
    InitTouchEvent(gestureHub);
    InitHoverMouseEvent();
    if (IsDisableSwipe()) {
        if (panEvent_) {
            gestureHub->RemovePanEvent(panEvent_);
            panEvent_.Reset();
        }
        return;
    }
    InitPanEvent(gestureHub);
    auto focusHub = host->GetFocusHub();
    if (focusHub) {
        InitOnKeyEvent(focusHub);
    }
    auto removeSwiperEventCallback = [weak = WeakClaim(this)]() {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        auto host = swiperPattern->GetHost();
        CHECK_NULL_VOID(host);
        auto hub = host->GetEventHub<EventHub>();
        CHECK_NULL_VOID(hub);
        auto gestureHub = hub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->RemoveTouchEvent(swiperPattern->touchEvent_);
        if (!swiperPattern->IsDisableSwipe()) {
            gestureHub->RemovePanEvent(swiperPattern->panEvent_);
        }
    };
    swiperController_->SetRemoveSwiperEventCallback(std::move(removeSwiperEventCallback));

    auto addSwiperEventCallback = [weak = WeakClaim(this)]() {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        auto host = swiperPattern->GetHost();
        CHECK_NULL_VOID(host);
        auto hub = host->GetEventHub<EventHub>();
        CHECK_NULL_VOID(hub);
        auto gestureHub = hub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->AddTouchEvent(swiperPattern->touchEvent_);
        if (!swiperPattern->IsDisableSwipe()) {
            gestureHub->AddPanEvent(swiperPattern->panEvent_, swiperPattern->panDirection_, 1, DEFAULT_PAN_DISTANCE);
        }
    };
    swiperController_->SetAddSwiperEventCallback(std::move(addSwiperEventCallback));

    if (IsAutoPlay()) {
        StartAutoPlay();
    } else {
        translateTask_.Cancel();
    }
    SetAccessibilityAction();
    if ((layoutProperty->GetPropertyChangeFlag() & PROPERTY_UPDATE_MEASURE) == PROPERTY_UPDATE_MEASURE) {
        mainSizeIsMeasured_ = false;
        itemPosition_.clear();
        jumpIndex_ = currentIndex_;
        for (const auto& child : host->GetChildren()) {
            if (child->GetTag() == V2::JS_LAZY_FOR_EACH_ETS_TAG) {
                auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(child);
                CHECK_NULL_VOID(lazyForEachNode);
                lazyForEachNode->SetFlagForGeneratedItem(PROPERTY_UPDATE_MEASURE);
            }
        }
    }
}

void SwiperPattern::InitSurfaceChangedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (!HasSurfaceChangedCallback()) {
        auto callbackId = pipeline->RegisterSurfaceChangedCallback(
            [weak = WeakClaim(this)](int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight,
                WindowSizeChangeReason type) {
                auto swiper = weak.Upgrade();
                if (!swiper) {
                    return;
                }
                if (type == WindowSizeChangeReason::ROTATION) {
                    swiper->currentOffset_ = 0.0f;
                    swiper->itemPosition_.clear();
                    swiper->jumpIndex_ = swiper->currentIndex_;
                }
            });
        LOGD("Add surface changed callback id %{public}d", callbackId);
        UpdateSurfaceChangedCallbackId(callbackId);
    }
}

void SwiperPattern::FlushFocus(const RefPtr<FrameNode>& curShowFrame)
{
    CHECK_NULL_VOID(curShowFrame);
    auto swiperHost = GetHost();
    CHECK_NULL_VOID(swiperHost);
    auto swiperFocusHub = swiperHost->GetFocusHub();
    CHECK_NULL_VOID(swiperFocusHub);
    auto showChildFocusHub = curShowFrame->GetFirstFocusHubChild();
    CHECK_NULL_VOID(showChildFocusHub);
    auto focusChildren = swiperFocusHub->GetChildren();
    CHECK_NULL_VOID(!focusChildren.empty());
    auto iter = focusChildren.rbegin();
    if (IsShowIndicator()) {
        ++iter;
    }
    if (HasLeftButtonNode()) {
        ++iter;
    }
    if (HasRightButtonNode()) {
        ++iter;
    }
    while (iter != focusChildren.rend()) {
        auto child = *iter;
        if (!child) {
            ++iter;
            continue;
        }
        if (child != showChildFocusHub) {
            child->SetParentFocusable(false);
        } else {
            child->SetParentFocusable(true);
        }
        ++iter;
    }

    RefPtr<FocusHub> needFocusNode = showChildFocusHub;
    if (IsShowIndicator() && isLastIndicatorFocused_) {
        needFocusNode = GetFocusHubChild(V2::SWIPER_INDICATOR_ETS_TAG);
    }
    CHECK_NULL_VOID(needFocusNode);
    lastWeakShowNode_ = AceType::WeakClaim(AceType::RawPtr(curShowFrame));
    if (swiperFocusHub->IsCurrentFocus()) {
        needFocusNode->RequestFocusImmediately();
    } else {
        swiperFocusHub->SetLastWeakFocusNode(AceType::WeakClaim(AceType::RawPtr(needFocusNode)));
    }
}
RefPtr<FocusHub> SwiperPattern::GetFocusHubChild(std::string childFrameName)
{
    auto swiperHost = GetHost();
    CHECK_NULL_RETURN(swiperHost, nullptr);
    auto swiperFocusHub = swiperHost->GetFocusHub();
    CHECK_NULL_RETURN(swiperFocusHub, nullptr);
    auto focusChildren = swiperFocusHub->GetChildren();
    CHECK_NULL_RETURN(!focusChildren.empty(), nullptr);
    for (const auto& child : focusChildren) {
        CHECK_NULL_RETURN(child, nullptr);
        if (child->GetFrameName() == childFrameName) {
            return child;
        }
    }
    return nullptr;
}

WeakPtr<FocusHub> SwiperPattern::GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode)
{
    auto curFocusNode = currentFocusNode.Upgrade();
    CHECK_NULL_RETURN(curFocusNode, nullptr);
    if ((direction_ == Axis::HORIZONTAL && step == FocusStep::UP) ||
        (direction_ == Axis::VERTICAL && step == FocusStep::LEFT)) {
        return PreviousFocus(curFocusNode);
    }
    if ((direction_ == Axis::HORIZONTAL && step == FocusStep::DOWN) ||
        (direction_ == Axis::VERTICAL && step == FocusStep::RIGHT)) {
        return NextFocus(curFocusNode);
    }
    return nullptr;
}

WeakPtr<FocusHub> SwiperPattern::PreviousFocus(const RefPtr<FocusHub>& curFocusNode)
{
    CHECK_NULL_RETURN(curFocusNode, nullptr);
    RefPtr<FocusHub> indicatorNode;
    RefPtr<FocusHub> leftArrowNode;
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    if (HasLeftButtonNode()) {
        leftArrowNode = GetFocusHubChild(V2::SWIPER_LEFT_ARROW_ETS_TAG);
        CHECK_NULL_RETURN(leftArrowNode, nullptr);
    }
    if (HasIndicatorNode()) {
        indicatorNode = GetFocusHubChild(V2::SWIPER_INDICATOR_ETS_TAG);
        CHECK_NULL_RETURN(indicatorNode, nullptr);
    }
    if (curFocusNode->GetFrameName() == V2::SWIPER_LEFT_ARROW_ETS_TAG) {
        isLastIndicatorFocused_ = false;
        (!IsLoop() && currentIndex_ == 0) ? curFocusNode->SetParentFocusable(false)
                                          : curFocusNode->SetParentFocusable(true);
        return nullptr;
    }
    if (curFocusNode->GetFrameName() == V2::SWIPER_INDICATOR_ETS_TAG) {
        if (!HasLeftButtonNode() || (!IsLoop() && currentIndex_ == 0) || layoutProperty->GetHoverShowValue(false)) {
            isLastIndicatorFocused_ = true;
            curFocusNode->SetParentFocusable(true);
            return nullptr;
        }
        isLastIndicatorFocused_ = false;
        leftArrowNode->SetParentFocusable(true);
        return AceType::WeakClaim(AceType::RawPtr(leftArrowNode));
    }
    if (curFocusNode->GetFrameName() == V2::SWIPER_RIGHT_ARROW_ETS_TAG) {
        if (HasIndicatorNode()) {
            isLastIndicatorFocused_ = true;
            indicatorNode->SetParentFocusable(true);
            return AceType::WeakClaim(AceType::RawPtr(indicatorNode));
        }
        if (!IsLoop() && currentIndex_ == 0) {
            curFocusNode->SetParentFocusable(true);
            return nullptr;
        }
        isLastIndicatorFocused_ = true;
        leftArrowNode->SetParentFocusable(true);
        return AceType::WeakClaim(AceType::RawPtr(leftArrowNode));
    }
    curFocusNode->SetParentFocusable(true);
    return nullptr;
}

WeakPtr<FocusHub> SwiperPattern::NextFocus(const RefPtr<FocusHub>& curFocusNode)
{
    CHECK_NULL_RETURN(curFocusNode, nullptr);
    RefPtr<FocusHub> indicatorNode;
    RefPtr<FocusHub> rightArrowNode;
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    if (HasIndicatorNode()) {
        indicatorNode = GetFocusHubChild(V2::SWIPER_INDICATOR_ETS_TAG);
        CHECK_NULL_RETURN(indicatorNode, nullptr);
    }
    if (HasRightButtonNode()) {
        rightArrowNode = GetFocusHubChild(V2::SWIPER_RIGHT_ARROW_ETS_TAG);
        CHECK_NULL_RETURN(rightArrowNode, nullptr);
    }
    if (curFocusNode->GetFrameName() == V2::SWIPER_LEFT_ARROW_ETS_TAG) {
        if (HasIndicatorNode()) {
            isLastIndicatorFocused_ = true;
            indicatorNode->SetParentFocusable(true);
            return AceType::WeakClaim(AceType::RawPtr(indicatorNode));
        }
        if (!IsLoop() && currentIndex_ == TotalCount() - 1) {
            curFocusNode->SetParentFocusable(true);
            return nullptr;
        }
        isLastIndicatorFocused_ = true;
        rightArrowNode->SetParentFocusable(true);
        return AceType::WeakClaim(AceType::RawPtr(rightArrowNode));
    }
    if (curFocusNode->GetFrameName() == V2::SWIPER_INDICATOR_ETS_TAG) {
        if (!HasRightButtonNode() || (!IsLoop() && currentIndex_ == TotalCount() - 1) ||
            layoutProperty->GetHoverShowValue(false)) {
            isLastIndicatorFocused_ = true;
            curFocusNode->SetParentFocusable(true);
            return nullptr;
        }
        isLastIndicatorFocused_ = false;
        rightArrowNode->SetParentFocusable(true);
        return AceType::WeakClaim(AceType::RawPtr(rightArrowNode));
    }
    if (curFocusNode->GetFrameName() == V2::SWIPER_RIGHT_ARROW_ETS_TAG) {
        isLastIndicatorFocused_ = false;
        (!IsLoop() && currentIndex_ == TotalCount() - 1) ? curFocusNode->SetParentFocusable(false)
                                                         : curFocusNode->SetParentFocusable(true);
        return nullptr;
    }
    curFocusNode->SetParentFocusable(true);
    return nullptr;
}

int32_t SwiperPattern::GetLoopIndex(int32_t originalIndex) const
{
    auto loopIndex = originalIndex;
    while (loopIndex < 0) {
        loopIndex = loopIndex + TotalCount();
    }
    loopIndex %= TotalCount();
    return loopIndex;
}

bool SwiperPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    auto isNotInit = true;
    if (isInit_) {
        isNotInit = false;
        isInit_ = false;
        // first load Swiper to preload page.
        SetLazyLoadFeature(true);
    } else {
        OnIndexChange();
    }

    auto curChild = dirty->GetOrCreateChildByIndex(currentIndex_);
    if (curChild) {
        auto curChildFrame = curChild->GetHostNode();
        CHECK_NULL_RETURN(curChildFrame, false);
        FlushFocus(curChildFrame);
    }

    if (config.skipMeasure && config.skipLayout) {
        return false;
    }

    bool isJump = false;
    auto layoutAlgorithmWrapper = dirty->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto swiperLayoutAlgorithm = DynamicCast<SwiperLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(swiperLayoutAlgorithm, false);
    itemPosition_ = std::move(swiperLayoutAlgorithm->GetItemPosition());
    currentOffset_ -= swiperLayoutAlgorithm->GetCurrentOffset();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    CheckMarkDirtyNodeForRenderIndicator();
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    if (jumpIndex_) {
        isJump = true;
        currentIndex_ = swiperLayoutAlgorithm->GetCurrentIndex();
        currentIndexOffset_ = 0.0f;
        layoutProperty->UpdateIndexWithoutMeasure(currentIndex_);
        if (isNotInit) {
            OnIndexChange();
        }
        jumpIndex_.reset();
    } else if (targetIndex_) {
        auto iter = itemPosition_.find(targetIndex_.value());
        if (iter != itemPosition_.end()) {
            float targetPos = 0.0f;
            targetPos = iter->second.startPos;
            auto context = PipelineContext::GetCurrentContext();
            if (context) {
                context->AddAfterLayoutTask([weak = WeakClaim(this), targetPos, velocity = velocity_.value_or(0.0f),
                                                nextIndex = GetLoopIndex(iter->first)]() {
                    auto swiper = weak.Upgrade();
                    CHECK_NULL_VOID(swiper);
                    swiper->PlayPropertyTranslateAnimation(-targetPos, nextIndex, velocity);
                    swiper->PlayIndicatorTranslateAnimation(-targetPos);
                });
            } else {
                PlayTranslateAnimation(currentOffset_, currentOffset_ - targetPos, GetLoopIndex(iter->first), false,
                    velocity_.value_or(0.0f));
            }
            velocity_.reset();
        }
        pauseTargetIndex_ = targetIndex_;
        targetIndex_.reset();
    }
    mainSizeIsMeasured_ = swiperLayoutAlgorithm->GetMainSizeIsMeasured();
    contentCrossSize_ = swiperLayoutAlgorithm->GetContentCrossSize();
    currentDelta_ = 0.0f;
    contentMainSize_ = swiperLayoutAlgorithm->GetContentMainSize();
    startMainPos_ = swiperLayoutAlgorithm->GetStartPosition();
    endMainPos_ = swiperLayoutAlgorithm->GetEndPosition();
    startIndex_ = swiperLayoutAlgorithm->GetStartIndex();
    endIndex_ = swiperLayoutAlgorithm->GetEndIndex();
    oldIndex_ = currentIndex_;
    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    return GetEdgeEffect() == EdgeEffect::FADE || paddingProperty != nullptr;
}

void SwiperPattern::FireChangeEvent() const
{
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireChangeEvent(currentIndex_);
    swiperEventHub->FireIndicatorChangeEvent(currentIndex_);
    swiperEventHub->FireChangeDoneEvent(moveDirection_);
}

void SwiperPattern::FireAnimationStartEvent(
    int32_t currentIndex, int32_t nextIndex, const AnimationCallbackInfo& info) const
{
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireAnimationStartEvent(currentIndex, nextIndex, info);
}

void SwiperPattern::FireAnimationEndEvent(int32_t currentIndex, const AnimationCallbackInfo& info) const
{
    if (currentIndex == -1) {
        return;
    }
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireAnimationEndEvent(currentIndex, info);
}

void SwiperPattern::FireGestureSwipeEvent(int32_t currentIndex, const AnimationCallbackInfo& info) const
{
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireGestureSwipeEvent(currentIndex, info);
}

void SwiperPattern::SwipeToWithoutAnimation(int32_t index)
{
    LOGD("Swipe to index: %{public}d without animation", index);
    if (IsChildrenSizeLessThanSwiper()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    jumpIndex_ = index;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void SwiperPattern::SwipeTo(int32_t index)
{
    LOGD("Swipe to index: %{public}d with animation, duration: %{public}d", index, GetDuration());
    if (IsChildrenSizeLessThanSwiper()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto targetIndex = (index < 0 || index > (TotalCount() - 1)) ? 0 : index;
    targetIndex = IsLoop() ? targetIndex : std::clamp(targetIndex, 0, TotalCount() - GetDisplayCount());
    if (currentIndex_ == targetIndex) {
        LOGD("Target index is same with current index.");
        return;
    }

    StopAutoPlay();
    StopTranslateAnimation();

    if (indicatorController_) {
        indicatorController_->Stop();
    }
    if (usePropertyAnimation_) {
        StopPropertyTranslateAnimation();
    }

    targetIndex_ = targetIndex;

    if (GetDuration() == 0 || !isVisible_) {
        SwipeToWithoutAnimation(index);
        return;
    }

    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void SwiperPattern::ShowNext()
{
    LOGI("SwiperPattern::ShowNext");
    if (IsChildrenSizeLessThanSwiper()) {
        return;
    }
    indicatorDoingAnimation_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childrenSize = TotalCount();
    std::optional<int32_t> preIndex;
    std::optional<int32_t> newTargetIndex;
    if (preTargetIndex_.has_value()) {
        if (GetLoopIndex(preTargetIndex_.value()) >= childrenSize - GetDisplayCount() && !IsLoop()) {
            LOGW("already last one, can't show next");
            return;
        }
        preIndex = preTargetIndex_.value();
    } else if (currentIndex_ >= childrenSize - GetDisplayCount() && !IsLoop()) {
        LOGW("already last one, can't show next");
        return;
    }
    if (childrenSize <= 0 || GetDisplayCount() == 0) {
        return;
    }
    if (isVisible_) {
        if (preIndex.has_value()) {
            newTargetIndex = preIndex.value() + 1;
        } else {
            newTargetIndex = itemPosition_.begin()->first + 1;
        }
        if (GetLoopIndex(newTargetIndex.value()) == currentIndex_) {
            return;
        }
    }
    StopAutoPlay();
    StopTranslateAnimation();

    if (indicatorController_) {
        indicatorController_->Stop();
    }
    if (usePropertyAnimation_) {
        StopPropertyTranslateAnimation();
    }

    if (isVisible_) {
        targetIndex_ = newTargetIndex;
        preTargetIndex_ = targetIndex_;
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    } else {
        SwipeToWithoutAnimation((currentIndex_ + 1) % childrenSize);
    }
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireIndicatorChangeEvent(currentIndex_);
}

void SwiperPattern::ShowPrevious()
{
    if (IsChildrenSizeLessThanSwiper()) {
        return;
    }
    indicatorDoingAnimation_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childrenSize = TotalCount();
    std::optional<int32_t> preIndex;
    std::optional<int32_t> newTargetIndex;
    if (preTargetIndex_.has_value()) {
        if (GetLoopIndex(preTargetIndex_.value()) <= 0 && !IsLoop()) {
            LOGW("already last one, can't show next");
            return;
        }
        preIndex = preTargetIndex_.value();
    } else if (currentIndex_ <= 0 && !IsLoop()) {
        LOGW("already last one, can't show next");
        return;
    }
    if (childrenSize <= 0 || GetDisplayCount() == 0) {
        return;
    }
    if (isVisible_) {
        if (preIndex.has_value()) {
            newTargetIndex = preIndex.value() - 1;
        } else {
            newTargetIndex = itemPosition_.begin()->first - 1;
        }
        if (GetLoopIndex(newTargetIndex.value()) == currentIndex_) {
            return;
        }
    }
    StopAutoPlay();
    StopTranslateAnimation();

    if (indicatorController_) {
        indicatorController_->Stop();
    }
    if (usePropertyAnimation_) {
        StopPropertyTranslateAnimation();
    }

    if (isVisible_) {
        targetIndex_ = newTargetIndex;
        preTargetIndex_ = targetIndex_;
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    } else {
        SwipeToWithoutAnimation((currentIndex_ + childrenSize - 1) % childrenSize);
    }
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireIndicatorChangeEvent(currentIndex_);
}

void SwiperPattern::FinishAnimation()
{
    StopTranslateAnimation();
    if (indicatorController_) {
        indicatorController_->Stop();
    }
    if (usePropertyAnimation_) {
        isFinishAnimation_ = true;
        StopPropertyTranslateAnimation();
    }
    if (swiperController_ && swiperController_->GetFinishCallback()) {
        swiperController_->GetFinishCallback()();
    }
}

void SwiperPattern::StopTranslateAnimation()
{
    if (controller_ && !controller_->IsStopped()) {
        isFinishAnimation_ = true;
        controller_->Stop();
    }
}

void SwiperPattern::StopSpringAnimation()
{
    if (springController_ && !springController_->IsStopped()) {
        springController_->Stop();
    }
}

void SwiperPattern::StopFadeAnimation()
{
    if (fadeController_ && !fadeController_->IsStopped()) {
        fadeController_->Stop();
    }
}

void SwiperPattern::InitSwiperController()
{
    if (swiperController_->HasInitialized()) {
        return;
    }

    swiperController_->SetSwipeToImpl([weak = WeakClaim(this)](int32_t index, bool reverse) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->SwipeTo(index);
        }
    });

    swiperController_->SetSwipeToWithoutAnimationImpl([weak = WeakClaim(this)](int32_t index) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->SwipeToWithoutAnimation(index);
        }
    });

    swiperController_->SetShowNextImpl([weak = WeakClaim(this)]() {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->ShowNext();
        }
    });

    swiperController_->SetShowPrevImpl([weak = WeakClaim(this)]() {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->ShowPrevious();
        }
    });

    swiperController_->SetFinishImpl([weak = WeakClaim(this)]() {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->FinishAnimation();
        }
    });
}

void SwiperPattern::InitIndicator()
{
    auto swiperNode = GetHost();
    CHECK_NULL_VOID(swiperNode);
    RefPtr<FrameNode> indicatorNode;
    if (!HasIndicatorNode()) {
        LOGI("Swiper create new indicator");
        if (!IsShowIndicator()) {
            return;
        }
        indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, GetIndicatorId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        swiperNode->AddChild(indicatorNode);
    } else {
        LOGI("Swiper indicator already exist");
        indicatorNode =
            DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(swiperNode->GetChildIndexById(GetIndicatorId())));
        CHECK_NULL_VOID(indicatorNode);
        if (!IsShowIndicator()) {
            RemoveIndicatorNode();
            return;
        }
        if (GetIndicatorType() == SwiperIndicatorType::DIGIT && lastSwiperIndicatorType_ == SwiperIndicatorType::DOT) {
            RemoveIndicatorNode();
            indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, GetIndicatorId(),
                []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
            swiperNode->AddChild(indicatorNode);
        }
    }
    lastSwiperIndicatorType_ = GetIndicatorType();
    CHECK_NULL_VOID(indicatorNode);
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetIndicatorTypeValue(SwiperIndicatorType::DOT) == SwiperIndicatorType::DOT) {
        SaveDotIndicatorProperty(indicatorNode);
    } else {
        SaveDigitIndicatorProperty(indicatorNode);
    }

    auto renderContext = indicatorNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    BorderRadiusProperty radius;
    radius.SetRadius(INDICATOR_BORDER_RADIUS);
    renderContext->UpdateBorderRadius(radius);

    indicatorNode->MarkModifyDone();
    indicatorNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwiperPattern::InitArrow()
{
    auto swiperNode = GetHost();
    CHECK_NULL_VOID(swiperNode);
    RefPtr<FrameNode> leftArrow;
    RefPtr<FrameNode> rightArrow;
    if (!HasLeftButtonNode() && !HasRightButtonNode()) {
        if (!IsShowArrow()) {
            return;
        }
        leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, GetLeftButtonId(),
            []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
        swiperNode->AddChild(leftArrow);
        rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, GetRightButtonId(),
            []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
        swiperNode->AddChild(rightArrow);
    } else {
        leftArrow =
            DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(swiperNode->GetChildIndexById(GetLeftButtonId())));
        CHECK_NULL_VOID(leftArrow);
        rightArrow =
            DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(swiperNode->GetChildIndexById(GetRightButtonId())));
        CHECK_NULL_VOID(rightArrow);
        if (!IsShowArrow()) {
            RemoveLeftButtonNode();
            RemoveRightButtonNode();
            return;
        }
    }

    SaveArrowProperty(leftArrow);
    SaveArrowProperty(rightArrow);

    leftArrow->MarkModifyDone();
    rightArrow->MarkModifyDone();
}

void SwiperPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (direction_ == GetDirection() && panEvent_) {
        return;
    }
    direction_ = GetDirection();

    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        LOGD("Pan event start");
        auto pattern = weak.Upgrade();
        if (pattern) {
            if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
                return;
            }
            pattern->HandleDragStart();
        }
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
                if (GreatNotEqual(info.GetMainDelta(), 0.0)) {
                    pattern->ShowPrevious();
                } else if (LessNotEqual(info.GetMainDelta(), 0.0)) {
                    pattern->ShowNext();
                }
            } else {
                pattern->HandleDragUpdate(info);
            }
        }
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        LOGD("Pan event end mainVelocity: %{public}lf", info.GetMainVelocity());
        auto pattern = weak.Upgrade();
        if (pattern) {
            if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
                return;
            }
            pattern->HandleDragEnd(info.GetMainVelocity());
        }
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        LOGD("Pan event cancel");
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragEnd(0.0);
        }
    };

    if (GetDirection() == Axis::VERTICAL) {
        panDirection_.type = PanDirection::VERTICAL;
    } else {
        panDirection_.type = PanDirection::HORIZONTAL;
    }
    if (panEvent_) {
        gestureHub->RemovePanEvent(panEvent_);
    }

    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->AddPanEvent(panEvent_, panDirection_, 1, DEFAULT_PAN_DISTANCE);
}

void SwiperPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (touchEvent_) {
        return;
    }

    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleTouchEvent(info);
        }
    };

    if (touchEvent_) {
        gestureHub->RemoveTouchEvent(touchEvent_);
    }
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

void SwiperPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (pattern) {
            return pattern->OnKeyEvent(event);
        }
        return false;
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool SwiperPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if ((direction_ == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_LEFT) ||
        (direction_ == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_UP)) {
        ShowPrevious();
        return true;
    }
    if ((direction_ == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_RIGHT) ||
        (direction_ == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_DOWN)) {
        ShowNext();
        return true;
    }
    return false;
}

void SwiperPattern::StopAutoPlay()
{
    if (IsAutoPlay()) {
        translateTask_.Cancel();
    }
}

void SwiperPattern::StartAutoPlay()
{
    if (NeedAutoPlay()) {
        PostTranslateTask(GetInterval());
    }
}

void SwiperPattern::OnVisibleChange(bool isVisible)
{
    isVisible_ = isVisible;
    if (isInit_) {
        return;
    }

    if (!isVisible_) {
        StopAutoPlay();
        return;
    }

    if (NeedStartAutoPlay()) {
        StartAutoPlay();
    }
}

void SwiperPattern::UpdateCurrentOffset(float offset)
{
    if (IsChildrenSizeLessThanSwiper() && !IsAutoFill()) {
        return;
    }
    if (itemPosition_.empty()) {
        return;
    }
    auto edgeEffect = GetEdgeEffect();
    if (!IsLoop() && IsOutOfBoundary() && edgeEffect == EdgeEffect::SPRING) {
        LOGD("Swiper has reached boundary, can't drag any more, effect spring.");
        auto visibleSize = CalculateVisibleSize();
        if (LessOrEqual(visibleSize, 0.0)) {
            return;
        }
        auto friction = currentOffset_ > 0
                            ? CalculateFriction(itemPosition_.begin()->second.startPos / visibleSize)
                            : CalculateFriction((visibleSize - itemPosition_.rbegin()->second.endPos) / visibleSize);

        currentDelta_ = currentDelta_ - friction * offset;
        if (isDragging_) {
            currentIndexOffset_ += friction * offset;
        }
    } else if (!IsLoop() && IsOutOfBoundary(offset) &&
               (edgeEffect == EdgeEffect::FADE || edgeEffect == EdgeEffect::NONE)) {
        currentDelta_ = currentDelta_ - offset;
        if (edgeEffect == EdgeEffect::FADE) {
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            if (itemPosition_.begin()->first == 0 || itemPosition_.rbegin()->first == TotalCount() - 1) {
                auto remainOffset = GetRemainingOffset();
                fadeOffset_ += (offset - remainOffset);
            }
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    } else {
        currentDelta_ = currentDelta_ - offset;
        if (isDragging_) {
            currentIndexOffset_ += offset;
        }
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void SwiperPattern::CheckMarkDirtyNodeForRenderIndicator(float additionalOffset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!indicatorId_.has_value()) {
        return;
    }
    auto child = DynamicCast<FrameNode>(host->GetChildAtIndex(host->GetChildIndexById(GetIndicatorId())));
    CHECK_NULL_VOID(child);

    if (child->GetTag() != V2::SWIPER_INDICATOR_ETS_TAG) {
        return;
    }
    auto currentShowIndex = 0;
    for (const auto& iter : itemPosition_) {
        if ((iter.second.startPos + additionalOffset) < 0 && (iter.second.endPos + additionalOffset) < 0) {
            continue;
        }
        if ((iter.second.endPos + additionalOffset) > 0) {
            currentShowIndex = iter.first;
            turnPageRate_ = (iter.second.startPos + additionalOffset) / (iter.second.endPos - iter.second.startPos);
            break;
        }
    }
    currentFirstIndex_ = GetLoopIndex(currentShowIndex);
    if (!IsLoop() && ((currentFirstIndex_ == 0 && turnPageRate_ > 0.0f) ||
                         (currentFirstIndex_ == TotalCount() - 1 && turnPageRate_ < 0.0f))) {
        return;
    }

    if (!indicatorDoingAnimation_) {
        child->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void SwiperPattern::UpdateAnimationProperty(float velocity)
{
    if (isDragging_) {
        auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
        auto firstItemLength = firstItemInfoInVisibleArea.second.endPos - firstItemInfoInVisibleArea.second.startPos;
        if (LessOrEqual(firstItemLength, 0)) {
            LOGE("Main size is not positive.");
            return;
        }

        int32_t nextIndex = currentIndex_;
        auto direction = GreatNotEqual(velocity, 0.0);

        auto dragThresholdFlag = direction ? firstItemInfoInVisibleArea.second.endPos > firstItemLength / 2
                                           : firstItemInfoInVisibleArea.second.endPos < firstItemLength / 2;
        if ((std::abs(velocity) > MIN_TURN_PAGE_VELOCITY) || dragThresholdFlag) {
            nextIndex = direction ? firstItemInfoInVisibleArea.first : firstItemInfoInVisibleArea.first + 1;
        } else {
            nextIndex = direction ? firstItemInfoInVisibleArea.first + 1 : firstItemInfoInVisibleArea.first;
        }

        targetIndex_ = nextIndex;
        velocity_ = velocity;
    } else {
        targetIndex_ = pauseTargetIndex_;
        velocity_ = velocity;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    moveDirection_ = velocity <= 0;
}

void SwiperPattern::OnTouchTestHit(SourceType hitTestType)
{
    // in mouse hover test case.
    if (hitTestType == SourceType::MOUSE) {
        return;
    }
    if (!isTouchDown_) {
        isTouchDown_ = true;
        if (indicatorController_) {
            indicatorController_->Stop();
        }
        if (usePropertyAnimation_) {
            StopPropertyTranslateAnimation();
        }
    }
}

void SwiperPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown();
    } else if (touchType == TouchType::UP) {
        HandleTouchUp();
    } else if (touchType == TouchType::CANCEL) {
        HandleTouchUp();
    }
}

void SwiperPattern::HandleTouchDown()
{
    indicatorDoingAnimation_ = false;
    // Stop translate animation when touch down.
    if (controller_ && controller_->IsRunning()) {
        controller_->Stop();
    }

    if (springController_ && springController_->IsRunning()) {
        springController_->Pause();
    }

    // Stop auto play when touch down.
    StopAutoPlay();
}

void SwiperPattern::HandleTouchUp()
{
    isTouchDown_ = false;
    if (!isDragging_ && !NearZero(GetCurrentFirstIndexStartPos())) {
        UpdateAnimationProperty(0.0);
    }

    if (springController_ && springController_->GetStatus() == Animator::Status::PAUSED) {
        springController_->Resume();
    }

    StartAutoPlay();
}

void SwiperPattern::HandleDragStart()
{
    StopTranslateAnimation();
    StopSpringAnimation();
    StopAutoPlay();

    const auto& tabBarFinishCallback = swiperController_->GetTabBarFinishCallback();
    if (tabBarFinishCallback) {
        tabBarFinishCallback();
    }

    const auto& removeEventCallback = swiperController_->GetRemoveTabBarEventCallback();
    if (removeEventCallback) {
        removeEventCallback();
    }
#ifdef OHOS_PLATFORM
    // Increase the cpu frequency when sliding.
    ResSchedReport::GetInstance().ResSchedDataReport("slide_on");
#endif

    gestureSwipeIndex_ = currentIndex_;
    isDragging_ = true;
    // in drag process, close lazy feature.
    SetLazyLoadFeature(false);
}

void SwiperPattern::HandleDragUpdate(const GestureEvent& info)
{
    auto mainDelta = static_cast<float>(info.GetMainDelta());

    auto dragPoint =
        PointF(static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()));
    if (IsOutOfHotRegion(dragPoint)) {
        return;
    }

    if (!IsOutOfIndicatorZone(dragPoint)) {
        return;
    }

    UpdateCurrentOffset(static_cast<float>(mainDelta));
    AnimationCallbackInfo callbackInfo;
    callbackInfo.currentOffset =
        GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    FireGestureSwipeEvent(gestureSwipeIndex_, callbackInfo);
}

void SwiperPattern::HandleDragEnd(double dragVelocity)
{
    if (IsChildrenSizeLessThanSwiper()) {
        return;
    }
    const auto& addEventCallback = swiperController_->GetAddTabBarEventCallback();
    if (addEventCallback) {
        addEventCallback();
    }
    LOGD("Drag end velocity: %{public}lf, currentOffset: %{public}lf", dragVelocity, currentOffset_);

    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        pipeline->FlushUITasks();
    }
    if (itemPosition_.empty()) {
        return;
    }

    // Play edge effect animation.
    auto edgeEffect = GetEdgeEffect();
    bool noneOutOfBoundary = (itemPosition_.begin()->first == 0 || itemPosition_.rbegin()->first == TotalCount() - 1) &&
                             NearZero(GetRemainingOffset()) && edgeEffect == EdgeEffect::NONE;
    if (!IsLoop() && (IsOutOfBoundary() || !NearZero(fadeOffset_) || noneOutOfBoundary)) {
        if (edgeEffect == EdgeEffect::SPRING) {
            PlaySpringAnimation(dragVelocity);
            return;
        }

        if (edgeEffect == EdgeEffect::FADE) {
            PlayFadeAnimation();
            return;
        }

        if (edgeEffect == EdgeEffect::NONE) {
            return;
        }
    }

#ifdef OHOS_PLATFORM
    ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
#endif

    UpdateAnimationProperty(static_cast<float>(dragVelocity));

    if (pipeline) {
        pipeline->FlushUITasks();
    }

    isDragging_ = false;
}

void SwiperPattern::PlayPropertyTranslateAnimation(float translate, int32_t nextIndex, float velocity)
{
    StopPropertyTranslateAnimation();

#ifdef OHOS_PLATFORM
    ResSchedReport::GetInstance().ResSchedDataReport("slide_on");
#endif

    AnimationOption option;
    option.SetDuration(GetDuration());
    option.SetCurve(GetCurveIncludeMotion(velocity / translate));
    OffsetF offset;
    if (GetDirection() == Axis::HORIZONTAL) {
        offset.AddX(translate);
    } else {
        offset.AddY(translate);
    }
    auto finishCallback = [id = Container::CurrentId(), weak = WeakClaim(this), offset]() {
        ContainerScope scope(id);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto task = [weak, offset]() {
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            swiper->OnPropertyTranslateAnimationFinish(offset);
        };
        context->PostSyncEvent(task);
    };
    // initial translate info.
    for (auto& item : itemPosition_) {
        auto frameNode = item.second.node;
        if (frameNode) {
            frameNode->GetRenderContext()->UpdateTranslateInXY(OffsetF());
        }
    }
    // property callback will call immediately.
    auto propertyUpdateCallback = [this, offset]() {
        for (auto& item : itemPosition_) {
            auto frameNode = item.second.node;
            if (frameNode) {
                frameNode->GetRenderContext()->UpdateTranslateInXY(offset);
                item.second.finialOffset = offset;
            }
        }
    };
    usePropertyAnimation_ = true;
    propertyAnimationIndex_ = nextIndex;
    AnimationUtils::Animate(option, propertyUpdateCallback, finishCallback);
    AnimationCallbackInfo info;
    info.velocity = Dimension(velocity, DimensionUnit::PX).ConvertToVp();
    info.currentOffset = GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    info.targetOffset = GetCustomPropertyOffset() - Dimension(translate, DimensionUnit::PX).ConvertToVp();

    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        pipeline->AddAfterRenderTask([weak = WeakClaim(this), info, nextIndex = GetLoopIndex(nextIndex)]() {
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            swiper->FireAnimationStartEvent(swiper->currentIndex_, nextIndex, info);
        });
    }

    // enable lazy load feature.
    SetLazyLoadFeature(true);
}

void SwiperPattern::UpdateOffsetAfterPropertyAnimation(float offset)
{
    UpdateCurrentOffset(offset);
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        pipeline->FlushUITasks();
    }
}

void SwiperPattern::OnPropertyTranslateAnimationFinish(const OffsetF& offset)
{
    if (!usePropertyAnimation_) {
        // force stop.
        return;
    }
    usePropertyAnimation_ = false;
    // reset translate.
    for (auto& item : itemPosition_) {
        auto frameNode = item.second.node;
        if (frameNode) {
            frameNode->GetRenderContext()->UpdateTranslateInXY(OffsetF());
        }
    }
    // update postion info.
    UpdateOffsetAfterPropertyAnimation(offset.GetMainOffset(GetDirection()));
    OnTranslateFinish(propertyAnimationIndex_, false);
}

void SwiperPattern::StopPropertyTranslateAnimation()
{
    if (!usePropertyAnimation_) {
        return;
    }
    usePropertyAnimation_ = false;
    // Stop CurrentAnimationProperty.
    OffsetF currentOffset;
    for (auto& item : itemPosition_) {
        auto frameNode = item.second.node;
        if (!frameNode) {
            continue;
        }
        currentOffset = frameNode->GetRenderContext()->GetShowingTranslateProperty();
        frameNode->GetRenderContext()->UpdateTranslateInXY(OffsetF());
        item.second.finialOffset = OffsetF();
    }
    UpdateOffsetAfterPropertyAnimation(currentOffset.GetMainOffset(GetDirection()));
    OnTranslateFinish(propertyAnimationIndex_, false, true);
}

RefPtr<Curve> SwiperPattern::GetCurveIncludeMotion(float velocity) const
{
    auto curve = GetCurve();
    auto container = Container::Current();
    bool isLauncherFeature = container ? container->IsLauncherContainer() : false;
    if (!curve && !isLauncherFeature) {
        curve = Curves::LINEAR;
    }
    if (curve) {
        if (InstanceOf<SpringCurve>(curve)) {
            auto springCurve = DynamicCast<SpringCurve>(curve);
            // check velocity to judge if this current velocity.
            if (springCurve->GetCurrentVelocity() < 0) {
                springCurve->UpdateVelocity(velocity);
            }
        }
        if (InstanceOf<InterpolatingSpring>(curve)) {
            auto interpolatingSpring = DynamicCast<InterpolatingSpring>(curve);
            // check velocity to judge if this current velocity.
            if (interpolatingSpring->GetVelocity() < 0) {
                interpolatingSpring->UpdateVelocity(velocity);
            }
        }
        return curve;
    }
    // use spring motion feature.
    // interpolatingSpring: (mass: 1, stiffness:328, damping: 34)
    return AceType::MakeRefPtr<InterpolatingSpring>(velocity, 1, 328, 34);
}

void SwiperPattern::PlayIndicatorTranslateAnimation(float translate)
{
    if (!indicatorId_.has_value()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!indicatorController_) {
        indicatorController_ = CREATE_ANIMATOR(host->GetContext());
    }
    indicatorController_->Stop();
    indicatorController_->ClearStartListeners();
    indicatorController_->ClearStopListeners();
    indicatorController_->ClearInterpolators();

    auto translateAnimation = AceType::MakeRefPtr<CurveAnimation<double>>(0, translate, Curves::LINEAR);
    translateAnimation->AddListener(Animation<double>::ValueCallback([weak = WeakClaim(this)](double value) {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->CheckMarkDirtyNodeForRenderIndicator(static_cast<float>(value));
    }));
    indicatorController_->SetDuration(GetDuration());
    indicatorController_->AddInterpolator(translateAnimation);
    indicatorController_->Play();
}

void SwiperPattern::PlayTranslateAnimation(
    float startPos, float endPos, int32_t nextIndex, bool restartAutoPlay, float velocity)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto curve = GetCurve();

    // If animation is still running, stop it before play new animation.
    StopSpringAnimation();
    StopFadeAnimation();
    StopTranslateAnimation();
    StopAutoPlay();

    SetLazyLoadFeature(false);

#ifdef OHOS_PLATFORM
    ResSchedReport::GetInstance().ResSchedDataReport("slide_on");
#endif

    if (!controller_) {
        controller_ = CREATE_ANIMATOR(host->GetContext());
    }
    controller_->ClearStartListeners();
    controller_->ClearStopListeners();
    controller_->ClearInterpolators();

    auto weak = WeakClaim(this);
    auto targetOffset = Dimension(startPos - endPos, DimensionUnit::PX).ConvertToVp();
    controller_->AddStartListener([weak, nextIndex, targetOffset, velocity]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        AnimationCallbackInfo info;
        info.velocity = Dimension(velocity, DimensionUnit::PX).ConvertToVp();
        info.currentOffset =
            swiper->GetCustomPropertyOffset() + Dimension(swiper->currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
        info.targetOffset = swiper->GetCustomPropertyOffset() + targetOffset;
        swiper->FireAnimationStartEvent(swiper->currentIndex_, nextIndex, info);
    });

    auto container = Container::Current();
    bool isLauncherFeature = container ? container->IsLauncherContainer() : false;
    if (!curve && !isLauncherFeature) {
        curve = Curves::LINEAR;
    }

    if (curve) {
        auto currentIndexStartPos = currentIndexOffset_;
        auto translate = AceType::MakeRefPtr<CurveAnimation<double>>(startPos, endPos, curve);
        translate->AddListener(
            Animation<double>::ValueCallback([weak, startPos, endPos, currentIndexStartPos](double value) {
                auto swiper = weak.Upgrade();
                CHECK_NULL_VOID(swiper);
                if (!NearEqual(value, startPos) && !NearEqual(value, endPos) && !NearEqual(startPos, endPos)) {
                    float moveRate =
                        Curves::EASE_OUT->MoveInternal(static_cast<float>((value - startPos) / (endPos - startPos)));
                    value = startPos + (endPos - startPos) * moveRate;
                    auto moveOffset = (endPos - startPos) * moveRate;
                    swiper->currentIndexOffset_ = currentIndexStartPos + moveOffset;
                }
                swiper->UpdateCurrentOffset(static_cast<float>(value - swiper->currentOffset_));
            }));
        controller_->AddStopListener([weak, nextIndex, restartAutoPlay]() {
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            swiper->OnTranslateFinish(nextIndex, restartAutoPlay);
        });
        controller_->SetDuration(GetDuration());
        controller_->AddInterpolator(translate);
        controller_->Play();
        return;
    }
    // use spring motion feature.
    // interpolatingSpring: (mass: 1, stiffness:328, damping: 34)
    static const auto springProperty = AceType::MakeRefPtr<SpringProperty>(1, 328, 34);
    auto scrollMotion = AceType::MakeRefPtr<SpringMotion>(startPos, endPos, velocity, springProperty);
    scrollMotion->AddListener([weak](double value) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->UpdateCurrentOffset(static_cast<float>(value) - swiper->currentOffset_);
        }
    });
    controller_->AddStopListener([weak, nextIndex, restartAutoPlay]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->OnTranslateFinish(nextIndex, restartAutoPlay);
    });
    controller_->PlayMotion(scrollMotion);
}

void SwiperPattern::PlaySpringAnimation(double dragVelocity)
{
    LOGD("Play spring animation start");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!springController_) {
        springController_ = CREATE_ANIMATOR(host->GetContext());
    }
    springController_->ClearStartListeners();
    springController_->ClearStopListeners();
    springController_->ClearInterpolators();

    auto mainSize = CalculateVisibleSize();
    if (LessOrEqual(mainSize, 0)) {
        LOGE("Main size is not positive.");
        return;
    }
    if (itemPosition_.empty()) {
        return;
    }

    // TODO use theme.
    constexpr float SPRING_SCROLL_MASS = 0.5f;
    constexpr float SPRING_SCROLL_STIFFNESS = 100.0f;
    constexpr float SPRING_SCROLL_DAMPING = 15.55635f;
    const RefPtr<SpringProperty> DEFAULT_OVER_SPRING_PROPERTY =
        AceType::MakeRefPtr<SpringProperty>(SPRING_SCROLL_MASS, SPRING_SCROLL_STIFFNESS, SPRING_SCROLL_DAMPING);
    ExtentPair extentPair = ExtentPair(currentOffset_ + mainSize - itemPosition_.rbegin()->second.endPos,
        currentOffset_ - itemPosition_.begin()->second.startPos);
    float friction = currentOffset_ > 0
                         ? CalculateFriction(itemPosition_.begin()->second.startPos / mainSize)
                         : CalculateFriction((mainSize - itemPosition_.rbegin()->second.endPos) / mainSize);
    auto scrollMotion = AceType::MakeRefPtr<ScrollMotion>(
        currentOffset_, dragVelocity * friction, extentPair, extentPair, DEFAULT_OVER_SPRING_PROPERTY);
    scrollMotion->AddListener([weak = AceType::WeakClaim(this)](double position) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->UpdateCurrentOffset(static_cast<float>(position) - swiper->currentOffset_);
        }
    });
    springController_->AddStartListener([weak = AceType::WeakClaim(this), dragVelocity]() {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        AnimationCallbackInfo info;
        info.velocity = dragVelocity;
        info.currentOffset = swiperPattern->GetCustomPropertyOffset() + swiperPattern->currentOffset_;
        info.targetOffset = swiperPattern->GetCustomPropertyOffset() + swiperPattern->currentOffset_;
        swiperPattern->FireAnimationStartEvent(swiperPattern->currentIndex_, swiperPattern->currentIndex_, info);
    });
    springController_->AddStopListener([weak = AceType::WeakClaim(this)]() {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        AnimationCallbackInfo info;
        swiperPattern->FireAnimationEndEvent(swiperPattern->currentIndex_, info);
    });
    springController_->PlayMotion(scrollMotion);
}

void SwiperPattern::PlayFadeAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (NearZero(fadeOffset_)) {
        return;
    }

    LOGD("Play fade animation start");
    if (!fadeController_) {
        fadeController_ = CREATE_ANIMATOR(host->GetContext());
    }
    fadeController_->ClearAllListeners();

    auto translate = AceType::MakeRefPtr<CurveAnimation<double>>(fadeOffset_, 0.0, Curves::LINEAR);
    auto weak = AceType::WeakClaim(this);
    translate->AddListener(Animation<double>::ValueCallback([weak](double value) {
        auto swiper = weak.Upgrade();
        if (swiper && swiper->GetHost()) {
            swiper->fadeOffset_ = static_cast<float>(value);
            swiper->GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }));

    fadeController_->AddStartListener([weak]() {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        AnimationCallbackInfo info;
        swiperPattern->FireAnimationStartEvent(swiperPattern->currentIndex_, swiperPattern->currentIndex_, info);
    });
    fadeController_->AddStopListener([weak]() {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        AnimationCallbackInfo info;
        swiperPattern->FireAnimationEndEvent(swiperPattern->currentIndex_, info);
    });
    constexpr float FADE_DURATION = 500.0f;
    fadeController_->SetDuration(FADE_DURATION);
    fadeController_->AddInterpolator(translate);
    fadeController_->Play();
}

bool SwiperPattern::IsOutOfBoundary(float mainOffset) const
{
    if (IsLoop() || itemPosition_.empty()) {
        return false;
    }
    auto isOutOfStart =
        itemPosition_.begin()->first == 0 && GreatNotEqual(itemPosition_.begin()->second.startPos + mainOffset, 0.0);
    auto visibleWindowSize = CalculateVisibleSize();
    auto isOutOfEnd = itemPosition_.rbegin()->first == TotalCount() - 1 &&
                      LessNotEqual(itemPosition_.rbegin()->second.endPos + mainOffset, visibleWindowSize);
    return isOutOfStart || isOutOfEnd;
}

float SwiperPattern::GetRemainingOffset() const
{
    if (IsLoop() || itemPosition_.empty()) {
        return 0.0f;
    }
    if (itemPosition_.begin()->first == 0) {
        return -itemPosition_.begin()->second.startPos;
    }
    auto visibleWindowSize = CalculateVisibleSize();
    return itemPosition_.rbegin()->second.endPos - visibleWindowSize;
}

float SwiperPattern::MainSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    return geometryNode->GetFrameSize().MainSize(GetDirection());
}

float SwiperPattern::GetMainContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    return geometryNode->GetPaddingSize().Width();
}

float SwiperPattern::CalculateVisibleSize() const
{
    auto prevMargin = GetPrevMargin();
    auto nextMargin = GetNextMargin();
    auto itemSpace = GetItemSpace();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    auto mainSize = geometryNode->GetFrameSize().MainSize(GetDirection());
    if (itemSpace > mainSize) {
        itemSpace = 0.0f;
    }
    if (prevMargin != 0.0f) {
        if (nextMargin != 0.0f) {
            return contentMainSize_ - prevMargin - nextMargin - 2 * itemSpace;
        }
        return contentMainSize_ - prevMargin - itemSpace;
    }

    if (nextMargin != 0.0f) {
        return contentMainSize_ - nextMargin - itemSpace;
    }
    return contentMainSize_;
}

float SwiperPattern::GetItemSpace() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, 0);
    return ConvertToPx(swiperLayoutProperty->GetItemSpace().value_or(0.0_vp),
        swiperLayoutProperty->GetLayoutConstraint()->scaleProperty, 0)
        .value_or(0);
}

float SwiperPattern::GetPrevMargin() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, 0);
    return ConvertToPx(swiperLayoutProperty->GetPrevMargin().value_or(0.0_vp),
        swiperLayoutProperty->GetLayoutConstraint()->scaleProperty, 0)
        .value_or(0);
}

float SwiperPattern::GetNextMargin() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, 0);
    return ConvertToPx(swiperLayoutProperty->GetNextMargin().value_or(0.0_vp),
        swiperLayoutProperty->GetLayoutConstraint()->scaleProperty, 0)
        .value_or(0);
}

Axis SwiperPattern::GetDirection() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, Axis::HORIZONTAL);
    return swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
}

int32_t SwiperPattern::CurrentIndex() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, 0);
    return swiperLayoutProperty->GetIndex().value_or(0);
}

int32_t SwiperPattern::GetDisplayCount() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, 1);
    auto displayCount = CalculateDisplayCount();
    return displayCount;
}

int32_t SwiperPattern::CalculateDisplayCount() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, 1);
    bool isAutoFill = IsAutoFill();
    if (isAutoFill) {
        auto minSize = swiperLayoutProperty->GetMinSize()->ConvertToPx();
        if (LessOrEqual(minSize, 0)) {
            return 1;
        }
        float contentWidth = GetMainContentSize();
        auto displayCount =
            CalculateCount(contentWidth, minSize, SWIPER_MARGIN.ConvertToPx(), SWIPER_GUTTER.ConvertToPx());

        displayCount = displayCount > 0 ? displayCount : 1;
        auto totalCount = TotalCount();
        displayCount = displayCount > totalCount ? totalCount : displayCount;
        auto displayCountProperty = swiperLayoutProperty->GetDisplayCount().value_or(1);

        if (displayCountProperty != displayCount) {
            swiperLayoutProperty->UpdateDisplayCount(displayCount);
            auto host = GetHost();
            CHECK_NULL_RETURN(host, 1);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF | PROPERTY_UPDATE_RENDER);
        }
        return displayCount;
    } else {
        return swiperLayoutProperty->GetDisplayCount().value_or(1);
    }
}

int32_t SwiperPattern::CalculateCount(
    float contentWidth, float minSize, float margin, float gutter, float swiperPadding) const
{
    return static_cast<int32_t>(floor((contentWidth - 2 * margin + gutter - 2 * swiperPadding) / (minSize + gutter)));
}

bool SwiperPattern::IsAutoFill() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, false);
    return swiperLayoutProperty->GetMinSize().has_value() &&
           !LessOrEqual(swiperLayoutProperty->GetMinSize()->ConvertToPx(), 0);
}

bool SwiperPattern::IsAutoPlay() const
{
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, false);
    return swiperPaintProperty->GetAutoPlay().value_or(false);
}

int32_t SwiperPattern::GetDuration() const
{
    const int32_t DEFAULT_DURATION = 400;
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, DEFAULT_DURATION);
    return swiperPaintProperty->GetDuration().value_or(DEFAULT_DURATION);
}

int32_t SwiperPattern::GetInterval() const
{
    const int32_t DEFAULT_INTERVAL = 3000;
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, DEFAULT_INTERVAL);
    return swiperPaintProperty->GetAutoPlayInterval().value_or(DEFAULT_INTERVAL);
}

RefPtr<Curve> SwiperPattern::GetCurve() const
{
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, nullptr);
    return swiperPaintProperty->GetCurve().value_or(nullptr);
}

bool SwiperPattern::IsLoop() const
{
    if (GetDisplayCount() >= TotalCount()) {
        return false;
    }
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, true);
    return swiperPaintProperty->GetLoop().value_or(true);
}

bool SwiperPattern::IsEnabled() const
{
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, true);
    return swiperPaintProperty->GetEnabled().value_or(true);
}

EdgeEffect SwiperPattern::GetEdgeEffect() const
{
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, EdgeEffect::SPRING);
    return swiperPaintProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING);
}

bool SwiperPattern::IsDisableSwipe() const
{
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, false);
    return swiperPaintProperty->GetDisableSwipe().value_or(false);
}

bool SwiperPattern::IsShowIndicator() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, true);
    return swiperLayoutProperty->GetShowIndicatorValue(true);
}

bool SwiperPattern::IsShowArrow() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, true);
    return swiperLayoutProperty->GetDisplayArrowValue(false);
}

SwiperIndicatorType SwiperPattern::GetIndicatorType() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, SwiperIndicatorType::DOT);
    return swiperLayoutProperty->GetIndicatorTypeValue(SwiperIndicatorType::DOT);
}

std::shared_ptr<SwiperParameters> SwiperPattern::GetSwiperParameters() const
{
    if (swiperParameters_ == nullptr) {
        swiperParameters_ = std::make_shared<SwiperParameters>();
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, swiperParameters_);
        auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        swiperParameters_->dimLeft = 0.0_vp;
        swiperParameters_->dimTop = 0.0_vp;
        swiperParameters_->dimRight = 0.0_vp;
        swiperParameters_->dimBottom = 0.0_vp;
        swiperParameters_->itemWidth = swiperIndicatorTheme->GetSize();
        swiperParameters_->itemHeight = swiperIndicatorTheme->GetSize();
        swiperParameters_->selectedItemWidth = swiperIndicatorTheme->GetSize();
        swiperParameters_->selectedItemHeight = swiperIndicatorTheme->GetSize();
        swiperParameters_->maskValue = true;
        swiperParameters_->colorVal = swiperIndicatorTheme->GetColor();
        swiperParameters_->selectedColorVal = swiperIndicatorTheme->GetSelectedColor();
    }
    return swiperParameters_;
}

std::shared_ptr<SwiperDigitalParameters> SwiperPattern::GetSwiperDigitalParameters() const
{
    if (swiperDigitalParameters_ == nullptr) {
        swiperDigitalParameters_ = std::make_shared<SwiperDigitalParameters>();
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, swiperDigitalParameters_);
        auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        swiperDigitalParameters_->dimLeft = 0.0_vp;
        swiperDigitalParameters_->dimTop = 0.0_vp;
        swiperDigitalParameters_->dimRight = 0.0_vp;
        swiperDigitalParameters_->dimBottom = 0.0_vp;
        swiperDigitalParameters_->fontColor = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
        swiperDigitalParameters_->selectedFontColor =
            swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
        swiperDigitalParameters_->fontSize = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize();
        swiperDigitalParameters_->selectedFontSize = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize();
        swiperDigitalParameters_->fontWeight = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
        swiperDigitalParameters_->selectedFontWeight =
            swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
    }
    return swiperDigitalParameters_;
}

int32_t SwiperPattern::TotalCount() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    // last child is swiper indicator
    int num = 0;
    if (IsShowIndicator()) {
        num += 1;
    }
    if (HasLeftButtonNode()) {
        num += 1;
    }
    if (HasRightButtonNode()) {
        num += 1;
    }

    return host->TotalChildCount() - num;
}

float SwiperPattern::GetTranslateLength() const
{
    if (itemPosition_.empty()) {
        return 0.0f;
    }
    return itemPosition_.begin()->second.endPos - itemPosition_.begin()->second.startPos;
}

std::pair<int32_t, SwiperItemInfo> SwiperPattern::GetFirstItemInfoInVisibleArea() const
{
    if (itemPosition_.empty()) {
        return std::make_pair(0, SwiperItemInfo {});
    }
    auto targetIndex = 0;
    if (GetPrevMargin() != 0.0f) {
        for (const auto& item : itemPosition_) {
            if (item.second.startPos < 0 && item.second.endPos < 0) {
                continue;
            }
            if (item.second.startPos <= 0 && item.second.endPos > 0) {
                targetIndex = item.first;
                return std::make_pair(targetIndex, SwiperItemInfo { item.second.startPos, item.second.endPos });
            }
            if (item.second.startPos > 0 && item.second.endPos > 0) {
                targetIndex = item.first;
                return std::make_pair(targetIndex, SwiperItemInfo { item.second.startPos, item.second.endPos });
            }
        }
    }
    return std::make_pair(itemPosition_.begin()->first,
        SwiperItemInfo { itemPosition_.begin()->second.startPos, itemPosition_.begin()->second.endPos });
}

std::pair<int32_t, SwiperItemInfo> SwiperPattern::GetSecondItemInfoInVisibleArea() const
{
    if (itemPosition_.empty()) {
        return std::make_pair(0, SwiperItemInfo {});
    }
    auto targetIndex = itemPosition_.begin()->first;
    if (GetPrevMargin() != 0.0f) {
        for (const auto& item : itemPosition_) {
            if (item.second.startPos < 0 && item.second.endPos < 0) {
                continue;
            }
            if (item.second.startPos <= 0 && item.second.endPos > 0) {
                targetIndex = item.first;
                break;
            }
            if (item.second.startPos > 0 && item.second.endPos > 0) {
                targetIndex = item.first;
                break;
            }
        }
    }

    targetIndex++;
    auto iter = itemPosition_.find(targetIndex);
    if (iter != itemPosition_.end()) {
        return std::make_pair(targetIndex, SwiperItemInfo { iter->second.startPos, iter->second.endPos });
    }
    return std::make_pair(itemPosition_.begin()->first,
        SwiperItemInfo { itemPosition_.begin()->second.startPos, itemPosition_.begin()->second.endPos });
}

bool SwiperPattern::IsOutOfHotRegion(const PointF& dragPoint) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, true);

    auto hotRegion = geometryNode->GetFrameRect();
    return !hotRegion.IsInRegion(dragPoint + OffsetF(hotRegion.GetX(), hotRegion.GetY()));
}

bool SwiperPattern::IsOutOfIndicatorZone(const PointF& dragPoint)
{
    if (!HasIndicatorNode() || !IsShowIndicator() || (GetIndicatorType() != SwiperIndicatorType::DOT)) {
        return true;
    }

    auto swiperNode = GetHost();
    CHECK_NULL_RETURN(swiperNode, true);
    auto indicatorNode = swiperNode->GetChildAtIndex(swiperNode->GetChildIndexById(GetIndicatorId()));
    CHECK_NULL_RETURN(indicatorNode, true);
    auto indicatorFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode);
    CHECK_NULL_RETURN(indicatorFrameNode, true);
    auto geometryNode = indicatorFrameNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, true);

    auto hotRegion = geometryNode->GetFrameRect();
    return !hotRegion.IsInRegion(dragPoint + OffsetF(hotRegion.GetX(), hotRegion.GetY()));
}

void SwiperPattern::SaveDotIndicatorProperty(const RefPtr<FrameNode>& indicatorNode)
{
    CHECK_NULL_VOID(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    CHECK_NULL_VOID(indicatorPattern);
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    auto swiperParameters = GetSwiperParameters();
    CHECK_NULL_VOID(swiperParameters);
    layoutProperty->UpdateLeft(swiperParameters->dimLeft.value_or(0.0_vp));
    layoutProperty->UpdateTop(swiperParameters->dimTop.value_or(0.0_vp));
    layoutProperty->UpdateRight(swiperParameters->dimRight.value_or(0.0_vp));
    layoutProperty->UpdateBottom(swiperParameters->dimBottom.value_or(0.0_vp));
    paintProperty->UpdateItemWidth(swiperParameters->itemWidth.value_or(swiperIndicatorTheme->GetSize()));
    paintProperty->UpdateItemHeight(swiperParameters->itemHeight.value_or(swiperIndicatorTheme->GetSize()));
    paintProperty->UpdateSelectedItemWidth(
        swiperParameters->selectedItemWidth.value_or(swiperIndicatorTheme->GetSize()));
    paintProperty->UpdateSelectedItemHeight(
        swiperParameters->selectedItemHeight.value_or(swiperIndicatorTheme->GetSize()));
    paintProperty->UpdateIndicatorMask(swiperParameters->maskValue.value_or(false));
    paintProperty->UpdateColor(swiperParameters->colorVal.value_or(swiperIndicatorTheme->GetColor()));
    paintProperty->UpdateSelectedColor(
        swiperParameters->selectedColorVal.value_or(swiperIndicatorTheme->GetSelectedColor()));
    paintProperty->UpdateIsCustomSize(IsCustomSize_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void SwiperPattern::SaveDigitIndicatorProperty(const RefPtr<FrameNode>& indicatorNode)
{
    CHECK_NULL_VOID(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    CHECK_NULL_VOID(indicatorPattern);
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    auto swiperDigitalParameters = GetSwiperDigitalParameters();
    CHECK_NULL_VOID(swiperDigitalParameters);
    layoutProperty->UpdateLeft(swiperDigitalParameters->dimLeft.value_or(0.0_vp));
    layoutProperty->UpdateTop(swiperDigitalParameters->dimTop.value_or(0.0_vp));
    layoutProperty->UpdateRight(swiperDigitalParameters->dimRight.value_or(0.0_vp));
    layoutProperty->UpdateBottom(swiperDigitalParameters->dimBottom.value_or(0.0_vp));
    layoutProperty->UpdateFontColor(swiperDigitalParameters->fontColor.value_or(
        swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor()));
    layoutProperty->UpdateSelectedFontColor(swiperDigitalParameters->selectedFontColor.value_or(
        swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor()));
    layoutProperty->UpdateFontSize(
        swiperDigitalParameters->fontSize.value_or(swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize()));
    layoutProperty->UpdateSelectedFontSize(swiperDigitalParameters->selectedFontSize.value_or(
        swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize()));
    layoutProperty->UpdateFontWeight(swiperDigitalParameters->fontWeight.value_or(
        swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight()));
    layoutProperty->UpdateSelectedFontWeight(swiperDigitalParameters->selectedFontWeight.value_or(
        swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight()));
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    swiperLayoutProperty->UpdateLeft(swiperDigitalParameters->dimLeft.value_or(0.0_vp));
    swiperLayoutProperty->UpdateTop(swiperDigitalParameters->dimTop.value_or(0.0_vp));
    swiperLayoutProperty->UpdateRight(swiperDigitalParameters->dimRight.value_or(0.0_vp));
    swiperLayoutProperty->UpdateBottom(swiperDigitalParameters->dimBottom.value_or(0.0_vp));
}

void SwiperPattern::PostTranslateTask(uint32_t delayTime)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    if (translateTask_) {
        translateTask_.Cancel();
    }

    auto weak = AceType::WeakClaim(this);
    translateTask_.Reset([weak, delayTime] {
        auto swiper = weak.Upgrade();
        if (swiper) {
            auto childrenSize = swiper->TotalCount();
            auto displayCount = swiper->GetDisplayCount();
            if (childrenSize <= 0 || displayCount <= 0 || swiper->itemPosition_.empty()) {
                return;
            }
            if (!swiper->IsLoop() && (swiper->itemPosition_.begin()->first + 1) > (childrenSize - displayCount)) {
                return;
            }
            swiper->targetIndex_ = swiper->itemPosition_.begin()->first + 1;
            auto host = swiper->GetHost();
            CHECK_NULL_VOID(host);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            auto pipeline = PipelineContext::GetCurrentContext();
            if (pipeline) {
                pipeline->FlushUITasks();
            }
        }
    });

    taskExecutor->PostDelayedTask(translateTask_, TaskExecutor::TaskType::UI, delayTime);
}

void SwiperPattern::RegisterVisibleAreaChange()
{
    if (hasVisibleChangeRegistered_ || !IsAutoPlay()) {
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        swiperPattern->isVisibleArea_ = visible;
        if (!visible) {
            swiperPattern->translateTask_.Cancel();
            return;
        }

        if (swiperPattern->NeedStartAutoPlay()) {
            swiperPattern->StartAutoPlay();
        }
    };
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    pipeline->RemoveVisibleAreaChangeNode(host->GetId());
    pipeline->AddVisibleAreaChangeNode(host, 0.0f, callback);

    pipeline->AddWindowStateChangedCallback(host->GetId());
    hasVisibleChangeRegistered_ = true;
}

bool SwiperPattern::NeedAutoPlay() const
{
    bool reachEnd = currentIndex_ >= TotalCount() - 1 && !IsLoop();
    return IsAutoPlay() && !reachEnd && isVisible_;
}

void SwiperPattern::TriggerAnimationEndOnSwipeToLeft()
{
    auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
    auto firstItemLength = firstItemInfoInVisibleArea.second.endPos - firstItemInfoInVisibleArea.second.startPos;
    auto firstIndexStartPos = firstItemInfoInVisibleArea.second.startPos;
    if (std::abs(firstIndexStartPos) < (firstItemLength / 2)) {
        currentIndexOffset_ = firstItemInfoInVisibleArea.second.startPos;
        currentIndex_ = GetLoopIndex(firstItemInfoInVisibleArea.first);
    } else {
        auto secondItemInfoInVisibleArea = GetSecondItemInfoInVisibleArea();
        currentIndexOffset_ = secondItemInfoInVisibleArea.second.startPos;
        currentIndex_ = GetLoopIndex(secondItemInfoInVisibleArea.first);
    }

    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateIndexWithoutMeasure(GetLoopIndex(currentIndex_));
    AnimationCallbackInfo info;
    info.currentOffset = GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    FireAnimationEndEvent(GetLoopIndex(currentIndex_), info);
}

void SwiperPattern::TriggerAnimationEndOnSwipeToRight()
{
    auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
    auto firstItemLength = firstItemInfoInVisibleArea.second.endPos - firstItemInfoInVisibleArea.second.startPos;
    auto secondItemInfoInVisibleArea = GetSecondItemInfoInVisibleArea();
    auto secondIndexStartPos = secondItemInfoInVisibleArea.second.startPos;
    if (std::abs(secondIndexStartPos) < (firstItemLength / 2)) {
        currentIndexOffset_ = secondItemInfoInVisibleArea.second.startPos;
        currentIndex_ = GetLoopIndex(secondItemInfoInVisibleArea.first);
    } else {
        currentIndexOffset_ = firstItemInfoInVisibleArea.second.startPos;
        currentIndex_ = GetLoopIndex(firstItemInfoInVisibleArea.first);
    }

    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateIndexWithoutMeasure(GetLoopIndex(currentIndex_));
    AnimationCallbackInfo info;
    info.currentOffset = GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    FireAnimationEndEvent(GetLoopIndex(currentIndex_), info);
}

void SwiperPattern::TriggerAnimationEndOnForceStop()
{
    auto pauseTargetIndex = pauseTargetIndex_.has_value() ? pauseTargetIndex_.value() : currentIndex_;
    if (GetLoopIndex(currentIndex_) == GetLoopIndex(pauseTargetIndex)) {
        AnimationCallbackInfo info;
        info.currentOffset =
            GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
        FireAnimationEndEvent(currentIndex_, info);
    } else {
        auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
        if (GetLoopIndex(currentIndex_) == GetLoopIndex(firstItemInfoInVisibleArea.first)) {
            // swipe to left
            TriggerAnimationEndOnSwipeToLeft();
        } else {
            // swipe to right
            TriggerAnimationEndOnSwipeToRight();
        }

        OnIndexChange();
        oldIndex_ = currentIndex_;
    }
}

void SwiperPattern::TriggerEventOnFinish(int32_t nextIndex)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    targetIndex_.reset();
    if (preTargetIndex_.has_value()) {
        preTargetIndex_.reset();
    }
    if (currentIndex_ != nextIndex) {
        if (isFinishAnimation_) {
            jumpIndex_ = nextIndex;
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            auto pipeline = PipelineContext::GetCurrentContext();
            if (pipeline) {
                pipeline->FlushUITasks();
            }
            isFinishAnimation_ = false;
        } else {
            currentIndex_ = nextIndex;
            oldIndex_ = nextIndex;
            currentFirstIndex_ = nextIndex;
            turnPageRate_ = 0.0f;
            currentIndexOffset_ = 0.0f;
            auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            layoutProperty->UpdateIndexWithoutMeasure(nextIndex);
            auto pipeline = PipelineContext::GetCurrentContext();
            if (pipeline) {
                pipeline->FlushUITasks();
                pipeline->FlushMessages();
            }
            FireChangeEvent();
            // lazyBuild feature.
            SetLazyLoadFeature(true);
        }
    }

    AnimationCallbackInfo info;
    info.currentOffset = GetCustomPropertyOffset();
    FireAnimationEndEvent(currentIndex_, info);
}

void SwiperPattern::SetLazyLoadFeature(bool useLazyLoad) const
{
    // lazyBuild feature.
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& children = host->GetChildren();
    for (auto&& child : children) {
        auto lazyForEach = DynamicCast<LazyForEachNode>(child);
        if (lazyForEach) {
            lazyForEach->SetRequestLongPredict(useLazyLoad);
        }
    }
}

bool SwiperPattern::IsChildrenSizeLessThanSwiper()
{
    if (static_cast<int32_t>(itemPosition_.size()) == TotalCount() && !itemPosition_.empty()) {
        auto totalChildrenSize = 0.0f;
        totalChildrenSize = itemPosition_.rbegin()->second.endPos - itemPosition_.begin()->second.startPos;
        auto prevMargin = GetPrevMargin();
        auto nextMargin = GetNextMargin();
        auto itemSpace = GetItemSpace();
        auto host = GetHost();
        CHECK_NULL_RETURN(host, 0.0f);
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, 0.0);
        auto mainSize = geometryNode->GetFrameSize().MainSize(GetDirection());
        if (itemSpace > mainSize) {
            itemSpace = 0.0f;
        }
        if (prevMargin != 0.0f) {
            if (nextMargin != 0.0f) {
                totalChildrenSize += prevMargin + nextMargin + 2 * itemSpace;
            } else {
                totalChildrenSize += prevMargin + itemSpace;
            }
        } else {
            if (nextMargin != 0.0f) {
                totalChildrenSize += nextMargin + itemSpace;
            }
        }

        if (totalChildrenSize <= contentMainSize_) {
            return true;
        }
    }
    return false;
}

void SwiperPattern::OnTranslateFinish(int32_t nextIndex, bool restartAutoPlay, bool forceStop)
{
    if (forceStop && !isFinishAnimation_) {
        TriggerAnimationEndOnForceStop();
    } else {
        TriggerEventOnFinish(nextIndex);
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (HasIndicatorNode()) {
        auto indicatorNode = DynamicCast<FrameNode>(host->GetChildAtIndex(host->GetChildIndexById(GetIndicatorId())));
        CHECK_NULL_VOID(indicatorNode);
        if (indicatorNode->GetTag() == V2::SWIPER_INDICATOR_ETS_TAG) {
            indicatorNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    }

    auto delayTime = GetInterval() - GetDuration();
    delayTime = std::clamp(delayTime, 0, delayTime);
    if (NeedAutoPlay()) {
        PostTranslateTask(delayTime);
    }
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);

#ifdef OHOS_PLATFORM
    ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
#endif
}

void SwiperPattern::OnWindowShow()
{
    isWindowShow_ = true;
    if (NeedStartAutoPlay()) {
        StartAutoPlay();
    }
}

void SwiperPattern::OnWindowHide()
{
    isWindowShow_ = false;
    StopAutoPlay();
}

int32_t SwiperPattern::ComputeLoadCount(int32_t cacheCount)
{
    auto displayCount = GetDisplayCount();
    if (IsLoop()) {
        return cacheCount * 2 + displayCount;
    }

    auto preCount = std::min(cacheCount, currentIndex_);
    auto nextCount = std::min(cacheCount, TotalCount() - currentIndex_ - displayCount);

    return preCount + nextCount + displayCount;
}

void SwiperPattern::ArrowHover(bool hoverFlag)
{
    if (HasLeftButtonNode() && HasRightButtonNode()) {
        auto swiperNode = GetHost();
        CHECK_NULL_VOID(swiperNode);
        auto leftArrowNode =
            DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(swiperNode->GetChildIndexById(GetLeftButtonId())));
        CHECK_NULL_VOID(leftArrowNode);
        auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
        CHECK_NULL_VOID(leftArrowPattern);
        leftArrowPattern->SetArrowHover(hoverFlag);
        leftArrowPattern->SetButtonVisible(hoverFlag);
        auto rightArrowNode =
            DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(swiperNode->GetChildIndexById(GetRightButtonId())));
        CHECK_NULL_VOID(rightArrowNode);
        auto rightArrowPattern = rightArrowNode->GetPattern<SwiperArrowPattern>();
        CHECK_NULL_VOID(rightArrowPattern);
        rightArrowPattern->SetArrowHover(hoverFlag);
        rightArrowPattern->SetButtonVisible(hoverFlag);
    }
}

void SwiperPattern::SaveArrowProperty(const RefPtr<FrameNode>& arrowNode)
{
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(swiperPaintProperty);
    auto arrowLayoutProperty = arrowNode->GetLayoutProperty<SwiperArrowLayoutProperty>();
    CHECK_NULL_VOID(arrowLayoutProperty);
    arrowLayoutProperty->UpdateDirection(layoutProperty->GetDirection().value_or(Axis::HORIZONTAL));
    arrowLayoutProperty->UpdateIndex(layoutProperty->GetIndex().value_or(0));
    arrowLayoutProperty->UpdateLoop(swiperPaintProperty->GetLoop().value_or(true));
    arrowLayoutProperty->UpdateEnabled(swiperPaintProperty->GetEnabled().value_or(true));
    arrowLayoutProperty->UpdateDisplayArrow(layoutProperty->GetDisplayArrowValue());
    arrowLayoutProperty->UpdateHoverShow(layoutProperty->GetHoverShowValue());
    arrowLayoutProperty->UpdateIsShowBackground(layoutProperty->GetIsShowBackgroundValue());
    arrowLayoutProperty->UpdateBackgroundSize(layoutProperty->GetBackgroundSizeValue());
    arrowLayoutProperty->UpdateBackgroundColor(layoutProperty->GetBackgroundColorValue());
    arrowLayoutProperty->UpdateArrowSize(layoutProperty->GetArrowSizeValue());
    arrowLayoutProperty->UpdateArrowColor(layoutProperty->GetArrowColorValue());
    arrowLayoutProperty->UpdateIsSidebarMiddle(layoutProperty->GetIsSidebarMiddleValue());
}

void SwiperPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward(
        [weakPtr = WeakClaim(this), accessibility = WeakClaim(RawPtr(accessibilityProperty))]() {
            const auto& pattern = weakPtr.Upgrade();
            CHECK_NULL_VOID(pattern);
            const auto& accessibilityProperty = accessibility.Upgrade();
            CHECK_NULL_VOID(accessibilityProperty);
            if (!accessibilityProperty->IsScrollable()) {
                return;
            }
            pattern->ShowNext();
        });

    accessibilityProperty->SetActionScrollBackward(
        [weakPtr = WeakClaim(this), accessibility = WeakClaim(RawPtr(accessibilityProperty))]() {
            const auto& pattern = weakPtr.Upgrade();
            CHECK_NULL_VOID(pattern);
            const auto& accessibilityProperty = accessibility.Upgrade();
            CHECK_NULL_VOID(accessibilityProperty);
            if (!accessibilityProperty->IsScrollable()) {
                return;
            }
            pattern->ShowPrevious();
        });
}

bool SwiperPattern::NeedStartAutoPlay() const
{
    return isWindowShow_ && isVisibleArea_ && isVisible_;
}

std::string SwiperPattern::ProvideRestoreInfo()
{
    auto jsonObj = JsonUtil::Create(true);
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, "");
    jsonObj->Put("Index", swiperLayoutProperty->GetIndex().value_or(0));
    return jsonObj->ToString();
}

void SwiperPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto info = JsonUtil::ParseJsonString(restoreInfo);
    if (!info->IsValid() || !info->IsObject()) {
        return;
    }
    auto jsonIsOn = info->GetValue("Index");
    swiperLayoutProperty->UpdateIndex(jsonIsOn->GetInt());
    OnModifyDone();
}

void SwiperPattern::InitHoverMouseEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);

    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->IsShowIndicator()) {
            pattern->ArrowHover(isHover);
        }
    };

    if (!hoverEvent_) {
        hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
        inputHub->AddOnHoverEvent(hoverEvent_);
    }

    inputHub->SetMouseEvent([weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(info);
        }
    });
}

void SwiperPattern::HandleMouseEvent(const MouseInfo& info)
{
    auto mouseOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
    auto mouseOffsetY = static_cast<float>(info.GetLocalLocation().GetY());
    auto mousePoint = PointF(mouseOffsetX, mouseOffsetY);
    if (IsShowIndicator()) {
        CheckAndSetArrowHoverState(mousePoint);
    }
}

void SwiperPattern::CheckAndSetArrowHoverState(const PointF& mousePoint)
{
    if (!HasLeftButtonNode() || !HasRightButtonNode() || !HasIndicatorNode()) {
        return;
    }

    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetIsSidebarMiddleValue(false)) {
        return;
    }

    RectF leftNodeRect;
    RectF rightNodeRect;

    leftNodeRect = GetArrowFrameRect(GetLeftButtonId());
    rightNodeRect = GetArrowFrameRect(GetRightButtonId());

    if (!IsLoop() && currentIndex_ == 0) {
        leftNodeRect = GetArrowFrameRect(GetIndicatorId());
    }

    if (!IsLoop() && currentIndex_ == TotalCount() - 1) {
        rightNodeRect = GetArrowFrameRect(GetIndicatorId());
    }
    RectF newNodeRect;
    if (GetDirection() == Axis::HORIZONTAL) {
        newNodeRect = RectF(leftNodeRect.Left(), leftNodeRect.Top(), rightNodeRect.Right() - leftNodeRect.Left(),
            std::min(rightNodeRect.Height(), leftNodeRect.Height()));
    } else {
        newNodeRect = RectF(leftNodeRect.Left(), leftNodeRect.Top(),
            std::min(rightNodeRect.Width(), leftNodeRect.Width()), rightNodeRect.Bottom() - leftNodeRect.Top());
    }

    isAtHotRegion_ = newNodeRect.IsInRegion(mousePoint);
    ArrowHover(isAtHotRegion_);
}

RectF SwiperPattern::GetArrowFrameRect(const int32_t index) const
{
    auto swiperNode = GetHost();
    CHECK_NULL_RETURN(swiperNode, RectF(0, 0, 0, 0));
    auto arrowNode = DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(swiperNode->GetChildIndexById(index)));
    CHECK_NULL_RETURN(arrowNode, RectF(0, 0, 0, 0));
    auto arrowGeometryNode = arrowNode->GetGeometryNode();
    CHECK_NULL_RETURN(arrowGeometryNode, RectF(0, 0, 0, 0));
    return arrowGeometryNode->GetFrameRect();
}

float SwiperPattern::GetCustomPropertyOffset() const
{
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0.0);
    auto paddingAndBorder = layoutProperty->CreatePaddingAndBorder();
    auto preMargin = layoutProperty->GetPrevMargin().value_or(0.0_vp);
    auto paddingAndBorderValue =
        GetDirection() == Axis::HORIZONTAL ? paddingAndBorder.left.value_or(0.0) : paddingAndBorder.top.value_or(0.0);
    return Dimension(paddingAndBorderValue, DimensionUnit::PX).ConvertToVp() + preMargin.Value();
}

float SwiperPattern::GetCurrentFirstIndexStartPos() const
{
    if (itemPosition_.empty()) {
        return 0.0;
    }

    return itemPosition_.begin()->second.startPos;
}
} // namespace OHOS::Ace::NG
