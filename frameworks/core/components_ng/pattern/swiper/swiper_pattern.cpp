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
#include <optional>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/log/dump_log.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/utils.h"
#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/animation/spring_curve.h"
#include "core/common/container_scope.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/swiper/swiper_layout_algorithm.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/pattern/swiper/swiper_utils.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_arrow_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/ace_events.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

// TODO use theme.
constexpr int32_t MIN_TURN_PAGE_VELOCITY = 1200;
constexpr int32_t NEW_MIN_TURN_PAGE_VELOCITY = 780;
constexpr Dimension INDICATOR_BORDER_RADIUS = 16.0_vp;

constexpr Dimension SWIPER_MARGIN = 16.0_vp;
constexpr Dimension SWIPER_GUTTER = 16.0_vp;
constexpr float PX_EPSILON = 0.01f;
constexpr float FADE_DURATION = 500.0f;
constexpr float SPEING_DURATION = 600.0f;
const std::string SWIPER_DRAG_SCENE = "swiper_drag_scene";
const std::string FADE_PROPERTY_NAME = "fade";
const std::string SPRING_PROPERTY_NAME = "spring";
const std::string INDICATOR_PROPERTY_NAME = "indicator";
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

void SwiperPattern::OnDetachFromFrameNode(FrameNode* node)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (HasSurfaceChangedCallback()) {
        pipeline->UnregisterSurfaceChangedCallback(surfaceChangedCallbackId_.value_or(-1));
    }
}

RefPtr<LayoutAlgorithm> SwiperPattern::CreateLayoutAlgorithm()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto swiperLayoutProperty = host->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, nullptr);

    auto swiperLayoutAlgorithm = MakeRefPtr<SwiperLayoutAlgorithm>();
    if (swiperLayoutProperty->GetIsCustomAnimation().value_or(false)) {
        swiperLayoutAlgorithm->SetUseCustomAnimation(true);
        swiperLayoutAlgorithm->SetCustomAnimationToIndex(customAnimationToIndex_);
        swiperLayoutAlgorithm->SetIndexsInAnimation(indexsInAnimation_);
        swiperLayoutAlgorithm->SetNeedUnmountIndexs(needUnmountIndexs_);
        return swiperLayoutAlgorithm;
    }

    if (jumpIndex_) {
        swiperLayoutAlgorithm->SetJumpIndex(jumpIndex_.value());
    } else if (targetIndex_) {
        swiperLayoutAlgorithm->SetTargetIndex(targetIndex_.value());
    }
    swiperLayoutAlgorithm->SetContentCrossSize(contentCrossSize_);
    swiperLayoutAlgorithm->SetMainSizeIsMeasured(mainSizeIsMeasured_);
    swiperLayoutAlgorithm->SetContentMainSize(contentMainSize_);
    swiperLayoutAlgorithm->SetCurrentDelta(currentDelta_);
    swiperLayoutAlgorithm->SetItemsPosition(itemPosition_);
    swiperLayoutAlgorithm->SetIsNeedResetPrevMarginAndNextMargin();
    if (IsOutOfBoundary() && !IsLoop()) {
        swiperLayoutAlgorithm->SetOverScrollFeature();
    }
    swiperLayoutAlgorithm->SetTotalItemCount(TotalCount());
    swiperLayoutAlgorithm->SetIsLoop(IsLoop());

    auto swiperPaintProperty = host->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(host, nullptr);
    auto effect = swiperPaintProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING);
    bool canOverScroll = effect == EdgeEffect::SPRING;
    swiperLayoutAlgorithm->SetCanOverScroll(canOverScroll);
    return swiperLayoutAlgorithm;
}

void SwiperPattern::OnIndexChange()
{
    auto totalCount = TotalCount();
    if (NonPositive(totalCount)) {
        return;
    }

    auto oldIndex = GetLoopIndex(oldIndex_);
    if (oldChildrenSize_.has_value() && oldChildrenSize_.value() != totalCount) {
        oldIndex = GetLoopIndex(oldIndex_, oldChildrenSize_.value());
        oldChildrenSize_ = totalCount;
    }

    auto targetIndex = GetLoopIndex(CurrentIndex());
    if (oldIndex != targetIndex) {
        auto swiperEventHub = GetEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(swiperEventHub);
        swiperEventHub->FireChangeEvent(targetIndex);
        swiperEventHub->FireIndicatorChangeEvent(targetIndex);
        swiperEventHub->FireChangeDoneEvent(moveDirection_);
        // lazyBuild feature.
        SetLazyLoadFeature(true);
    }
}

void SwiperPattern::StopAndResetSpringAnimation()
{
    if (springAnimationIsRunning_) {
        AnimationUtils::StopAnimation(springAnimation_);
        currentDelta_ = 0.0f;
        itemPosition_.clear();
        isVoluntarilyClear_ = true;
        jumpIndex_ = currentIndex_;
        springAnimationIsRunning_ = false;
    }
}

void SwiperPattern::OnLoopChange()
{
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    if (!preLoop_.has_value()) {
        preLoop_ = layoutProperty->GetLoop().value_or(true);
        return;
    }

    if (preLoop_.value() != layoutProperty->GetLoop().value_or(true) &&
        (layoutProperty->GetPrevMargin().has_value() || layoutProperty->GetNextMargin().has_value())) {
        jumpIndex_ = GetLoopIndex(currentIndex_);
        preLoop_ = layoutProperty->GetLoop().value_or(true);
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
    InitIndicator();
    InitArrow();
    SetLazyLoadIsLoop();
    RegisterVisibleAreaChange();
    InitSwiperController();
    InitTouchEvent(gestureHub);
    InitHoverMouseEvent();
    StopAndResetSpringAnimation();
    OnLoopChange();
    if ((layoutProperty->GetPropertyChangeFlag() & PROPERTY_UPDATE_MEASURE) == PROPERTY_UPDATE_MEASURE) {
        StopPropertyTranslateAnimation(isFinishAnimation_);
        StopTranslateAnimation();
        StopSpringAnimation();
        StopFadeAnimation();
        StopIndicatorAnimation();
        currentOffset_ = 0.0f;
        mainSizeIsMeasured_ = false;
        itemPosition_.clear();
        isVoluntarilyClear_ = true;
        jumpIndex_ = currentIndex_;
        for (const auto& child : host->GetChildren()) {
            if (child->GetTag() == V2::JS_LAZY_FOR_EACH_ETS_TAG) {
                auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(child);
                CHECK_NULL_VOID(lazyForEachNode);
                lazyForEachNode->SetFlagForGeneratedItem(PROPERTY_UPDATE_MEASURE);
            }
        }
    }

    UpdateSwiperPanEvent(IsDisableSwipe());

    auto focusHub = host->GetFocusHub();
    if (focusHub) {
        InitOnKeyEvent(focusHub);
        InitOnFocusInternal(focusHub);
    }

    SetSwiperEventCallback(IsDisableSwipe());

    auto updateCubicCurveCallback = [weak = WeakClaim(this)]() {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        auto host = swiperPattern->GetHost();
        CHECK_NULL_VOID(host);
        auto swiperPaintProperty = host->GetPaintProperty<SwiperPaintProperty>();
        CHECK_NULL_VOID(swiperPaintProperty);
        auto curve = MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
        swiperPaintProperty->UpdateCurve(curve);
    };
    swiperController_->SetUpdateCubicCurveCallback(std::move(updateCubicCurveCallback));

    if (IsAutoPlay()) {
        StartAutoPlay();
    } else {
        translateTask_.Cancel();
    }

    SetAccessibilityAction();
}

void SwiperPattern::OnAfterModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    if (!inspectorId.empty()) {
        Recorder::NodeDataCache::Get().PutInt(inspectorId, CurrentIndex());
    }
}

void SwiperPattern::BeforeCreateLayoutWrapper()
{
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    oldIndex_ = currentIndex_;
    auto userSetCurrentIndex = CurrentIndex();
    auto oldIndex = GetLoopIndex(oldIndex_);
    if (oldChildrenSize_.has_value() && oldChildrenSize_.value() != TotalCount()) {
        oldIndex = GetLoopIndex(oldIndex_, oldChildrenSize_.value());
        if (HasIndicatorNode()) {
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            auto indicatorNode = DynamicCast<FrameNode>(
                host->GetChildAtIndex(host->GetChildIndexById(GetIndicatorId())));
            if (indicatorNode && indicatorNode->GetTag() == V2::SWIPER_INDICATOR_ETS_TAG) {
                indicatorNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            }
        }
    }
    if (userSetCurrentIndex < 0 || userSetCurrentIndex >= TotalCount()) {
        currentIndex_ = 0;
        layoutProperty->UpdateIndexWithoutMeasure(GetLoopIndex(currentIndex_));
    } else {
        if (oldIndex != userSetCurrentIndex) {
            currentIndex_ = userSetCurrentIndex;
            propertyAnimationIndex_ = GetLoopIndex(propertyAnimationIndex_);
        }
    }
    if (oldIndex_ != currentIndex_ || (itemPosition_.empty() && !isVoluntarilyClear_)) {
        jumpIndex_ = GetLoopIndex(currentIndex_);
        currentFirstIndex_ = jumpIndex_.value_or(0);
        turnPageRate_ = 0.0f;
    }
    isVoluntarilyClear_ = false;
    if (jumpIndex_) {
        if ((jumpIndex_.value() < 0 || jumpIndex_.value() >= TotalCount()) && !IsLoop()) {
            jumpIndex_ = 0;
        }
        targetIndex_.reset();
        if (usePropertyAnimation_) {
            StopPropertyTranslateAnimation(false, true);
            currentDelta_ = 0.0f;
            StopIndicatorAnimation();
        }
    }
    if (mainSizeIsMeasured_ && isNeedResetPrevMarginAndNextMargin_) {
        layoutProperty->UpdatePrevMarginWithoutMeasure(0.0_px);
        layoutProperty->UpdateNextMarginWithoutMeasure(0.0_px);
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
                if (type == WindowSizeChangeReason::UNDEFINED) {
                    return;
                }
                auto swiper = weak.Upgrade();
                if (!swiper) {
                    return;
                }

                if (type == WindowSizeChangeReason::ROTATION) {
                    swiper->windowSizeChangeReason_ = type;
                    swiper->StopAutoPlay();
                }

                swiper->StopPropertyTranslateAnimation(swiper->isFinishAnimation_);
                swiper->StopTranslateAnimation();
                swiper->StopSpringAnimation();
                swiper->StopFadeAnimation();
                swiper->StopIndicatorAnimation();

                const auto& surfaceChangeCallback = swiper->swiperController_->GetSurfaceChangeCallback();
                if (surfaceChangeCallback) {
                    surfaceChangeCallback();
                }
                swiper->currentOffset_ = 0.0f;
                swiper->itemPosition_.clear();
                swiper->isVoluntarilyClear_ = true;
                swiper->jumpIndex_ = swiper->currentIndex_;
                swiper->MarkDirtyNodeSelf();
                auto swiperNode = swiper->GetHost();
                CHECK_NULL_VOID(swiperNode);
                for (const auto& child : swiperNode->GetChildren()) {
                    if (child->GetTag() == V2::JS_LAZY_FOR_EACH_ETS_TAG) {
                        auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(child);
                        CHECK_NULL_VOID(lazyForEachNode);
                        lazyForEachNode->SetFlagForGeneratedItem(PROPERTY_UPDATE_MEASURE);
                    }
                }
            });
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
    if ((GetDirection() == Axis::HORIZONTAL && step == FocusStep::UP) ||
        (GetDirection() == Axis::HORIZONTAL && step == FocusStep::SHIFT_TAB) ||
        (GetDirection() == Axis::VERTICAL && step == FocusStep::LEFT)) {
        return PreviousFocus(curFocusNode);
    }
    if ((GetDirection() == Axis::HORIZONTAL && step == FocusStep::DOWN) ||
        (GetDirection() == Axis::HORIZONTAL && step == FocusStep::TAB) ||
        (GetDirection() == Axis::VERTICAL && step == FocusStep::RIGHT)) {
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
        (!IsLoop() && GetLoopIndex(currentIndex_) == 0) ? curFocusNode->SetParentFocusable(false)
                                                        : curFocusNode->SetParentFocusable(true);
        return nullptr;
    }
    if (curFocusNode->GetFrameName() == V2::SWIPER_INDICATOR_ETS_TAG) {
        if (!HasLeftButtonNode() || (!IsLoop() && GetLoopIndex(currentIndex_) == 0) ||
            layoutProperty->GetHoverShowValue(false)) {
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
        if (!IsLoop() && GetLoopIndex(currentIndex_) == 0) {
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
        if (!IsLoop() && GetLoopIndex(currentIndex_) == TotalCount() - 1) {
            curFocusNode->SetParentFocusable(true);
            return nullptr;
        }
        isLastIndicatorFocused_ = true;
        rightArrowNode->SetParentFocusable(true);
        return AceType::WeakClaim(AceType::RawPtr(rightArrowNode));
    }
    if (curFocusNode->GetFrameName() == V2::SWIPER_INDICATOR_ETS_TAG) {
        if (!HasRightButtonNode() || (!IsLoop() && GetLoopIndex(currentIndex_) == TotalCount() - 1) ||
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
        (!IsLoop() && GetLoopIndex(currentIndex_) == TotalCount() - 1) ? curFocusNode->SetParentFocusable(false)
                                                                       : curFocusNode->SetParentFocusable(true);
        return nullptr;
    }
    curFocusNode->SetParentFocusable(true);
    return nullptr;
}

int32_t SwiperPattern::GetLoopIndex(int32_t originalIndex) const
{
    if (TotalCount() <= 0) {
        return originalIndex;
    }
    auto loopIndex = originalIndex;
    while (loopIndex < 0) {
        loopIndex = loopIndex + TotalCount();
    }
    loopIndex %= TotalCount();
    return loopIndex;
}

bool SwiperPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (!isDragging_) {
        SetLazyLoadFeature(true);
    }

    auto isNotInit = true;
    if (isInit_) {
        isNotInit = false;
        isInit_ = false;
        // first load Swiper to preload page.
        SetLazyLoadFeature(true);
    } else {
        OnIndexChange();
        oldIndex_ = currentIndex_;
    }

    if (!IsAutoPlay() && config.skipMeasure && config.skipLayout) {
        return false;
    }

    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto layoutAlgorithmWrapper = dirty->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto swiperLayoutAlgorithm = DynamicCast<SwiperLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(swiperLayoutAlgorithm, false);

    if (layoutProperty->GetIsCustomAnimation().value_or(false)) {
        needUnmountIndexs_ = swiperLayoutAlgorithm->GetNeedUnmountIndexs();
        return false;
    }

    autoLinearReachBoundary = false;
    bool isJump = false;
    itemPosition_ = std::move(swiperLayoutAlgorithm->GetItemPosition());
    currentOffset_ -= swiperLayoutAlgorithm->GetCurrentOffset();
    if (!itemPosition_.empty()) {
        const auto& turnPageRateCallback = swiperController_->GetTurnPageRateCallback();
        if (turnPageRateCallback && isDragging_ && !NearZero(GetTranslateLength())) {
            turnPageRateCallback(
                itemPosition_.begin()->first, -itemPosition_.begin()->second.startPos / GetTranslateLength());
        }
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (!targetIndex_) {
        CheckMarkDirtyNodeForRenderIndicator();
    }

    if (jumpIndex_) {
        isJump = true;
        UpdateCurrentIndex(swiperLayoutAlgorithm->GetCurrentIndex());
        auto curChild = dirty->GetOrCreateChildByIndex(GetLoopIndex(currentIndex_));
        if (curChild) {
            auto curChildFrame = curChild->GetHostNode();
            CHECK_NULL_RETURN(curChildFrame, false);
            FlushFocus(curChildFrame);
            currentFocusIndex_ = GetLoopIndex(currentIndex_);
        }
        currentIndexOffset_ = 0.0f;
        if (isNotInit) {
            OnIndexChange();
        }
        jumpIndex_.reset();
        auto delayTime = GetInterval() - GetDuration();
        delayTime = std::clamp(delayTime, 0, delayTime);
        if (NeedAutoPlay() && isUserFinish_) {
            PostTranslateTask(delayTime);
        }
    } else if (targetIndex_) {
        auto targetIndexValue = IsLoop() ? targetIndex_.value() : GetLoopIndex(targetIndex_.value());
        auto iter = itemPosition_.find(targetIndexValue);
        if (iter != itemPosition_.end()) {
            float targetPos = 0.0f;
            targetPos = iter->second.startPos;
            auto context = PipelineContext::GetCurrentContext();
            if (context) {
                // displayCount is auto, loop is false, if the content width less than windows size
                // need offset to keep right aligned
                bool isNeedOffset = (GetLoopIndex(iter->first) == TotalCount() - 1)
                    && !layoutProperty->GetDisplayCount().has_value() && !IsLoop()
                    && LessNotEqual(iter->second.endPos - iter->second.startPos, CalculateVisibleSize());
                float offset = isNeedOffset
                    ? CalculateVisibleSize() - iter->second.endPos + iter->second.startPos : 0.0;
                targetPos -= offset;

                auto nextIndex = iter->first;
                auto stopAutoPlay = false;
                if (AutoLinearAnimationNeedReset(targetPos)) {
                    auto firstItem = GetFirstItemInfoInVisibleArea();
                    nextIndex = firstItem.first;
                    targetPos = firstItem.second.startPos;
                    stopAutoPlay = true;
                    autoLinearReachBoundary = true;
                }

                context->AddAfterLayoutTask([weak = WeakClaim(this), targetPos, velocity = velocity_.value_or(0.0f),
                                                nextIndex, stopAutoPlay]() {
                    auto swiper = weak.Upgrade();
                    CHECK_NULL_VOID(swiper);
                    swiper->PlayPropertyTranslateAnimation(-targetPos, nextIndex, velocity, stopAutoPlay);
                    swiper->PlayIndicatorTranslateAnimation(-targetPos);
                });
            } else {
                PlayTranslateAnimation(
                    currentOffset_, currentOffset_ - targetPos, iter->first, false, velocity_.value_or(0.0f));
            }
            velocity_.reset();
        }
        pauseTargetIndex_ = targetIndex_;
    }
    mainSizeIsMeasured_ = swiperLayoutAlgorithm->GetMainSizeIsMeasured();
    isNeedResetPrevMarginAndNextMargin_ = swiperLayoutAlgorithm->GetIsNeedResetPrevMarginAndNextMargin();
    contentCrossSize_ = swiperLayoutAlgorithm->GetContentCrossSize();
    currentDelta_ = 0.0f;
    contentMainSize_ = swiperLayoutAlgorithm->GetContentMainSize();
    startMainPos_ = swiperLayoutAlgorithm->GetStartPosition();
    endMainPos_ = swiperLayoutAlgorithm->GetEndPosition();
    startIndex_ = swiperLayoutAlgorithm->GetStartIndex();
    endIndex_ = swiperLayoutAlgorithm->GetEndIndex();
    crossMatchChild_ = swiperLayoutAlgorithm->IsCrossMatchChild();
    oldIndex_ = currentIndex_;
    oldChildrenSize_ = TotalCount();

    if (windowSizeChangeReason_ == WindowSizeChangeReason::ROTATION) {
        StartAutoPlay();
        windowSizeChangeReason_ = WindowSizeChangeReason::UNDEFINED;
    }

    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    return GetEdgeEffect() == EdgeEffect::FADE || paddingProperty != nullptr;
}

bool SwiperPattern::IsAutoLinear() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, false);
    return !SwiperUtils::IsStretch(swiperLayoutProperty);
}

bool SwiperPattern::AutoLinearAnimationNeedReset(float translate) const
{
    if (!IsAutoLinear()) {
        return false;
    }

    if (itemPosition_.empty() || static_cast<int32_t>(itemPosition_.size()) < TotalCount()) {
        return false;
    }

    if (NonPositive(translate)) {
        return false;
    }

    auto iter = itemPosition_.rbegin();
    auto endPos = iter->second.endPos;
    if (endPos - CalculateVisibleSize() < translate) {
        return true;
    }

    return false;
}

void SwiperPattern::OnAnimationTranslateZero(int32_t nextIndex, bool stopAutoPlay)
{
    ResetAndUpdateIndexOnAnimationEnd(nextIndex);

    if (!NeedAutoPlay() || !isUserFinish_) {
        return;
    }

    if (stopAutoPlay) {
        MarkDirtyNodeSelf();
    } else {
        auto delayTime = GetInterval() - GetDuration();
        delayTime = std::clamp(delayTime, 0, delayTime);
        PostTranslateTask(delayTime);
    }
}

void SwiperPattern::FireChangeEvent() const
{
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireChangeEvent(GetLoopIndex(currentIndex_));
    swiperEventHub->FireIndicatorChangeEvent(GetLoopIndex(currentIndex_));
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
    if (IsVisibleChildrenSizeLessThanSwiper()) {
        return;
    }

    if (usePropertyAnimation_) {
        StopPropertyTranslateAnimation(isFinishAnimation_);
    }

    StopFadeAnimation();
    StopSpringAnimation();
    jumpIndex_ = index;
    uiCastJumpIndex_ = index;
    MarkDirtyNodeSelf();
    FireAndCleanScrollingListener();
}

void SwiperPattern::StopSpringAnimationAndFlushImmediately()
{
    if (springAnimationIsRunning_) {
        AnimationUtils::StopAnimation(springAnimation_);
        currentDelta_ = 0.0f;
        itemPosition_.clear();
        isVoluntarilyClear_ = true;
        jumpIndex_ = currentIndex_;
        springAnimationIsRunning_ = false;
        MarkDirtyNodeSelf();
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    }
}

bool SwiperPattern::IsUseCustomAnimation() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, false);
    return swiperLayoutProperty->GetIsCustomAnimation().value_or(false);
}

void SwiperPattern::SwipeTo(int32_t index)
{
    auto targetIndex = IsLoop() ? index : (index < 0 || index > (TotalCount() - 1)) ? 0 : index;
    targetIndex = IsLoop() ? targetIndex : std::clamp(targetIndex, 0, TotalCount() - GetDisplayCount());

    if (IsUseCustomAnimation()) {
        OnCustomContentTransition(targetIndex);
        MarkDirtyNodeSelf();
        return;
    }

    if (IsVisibleChildrenSizeLessThanSwiper()) {
        return;
    }

    // If targetIndex_ has a value, means animation is still running, stop it before play new animation.
    if (currentIndex_ == targetIndex && !targetIndex_.has_value()) {
        return;
    }
    StopFadeAnimation();
    if (springAnimationIsRunning_) {
        AnimationUtils::StopAnimation(springAnimation_);
        jumpIndex_ = currentIndex_;
        springAnimationIsRunning_ = false;
        MarkDirtyNodeSelf();
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    }
    StopAutoPlay();
    StopTranslateAnimation();
    StopIndicatorAnimation();
    if (usePropertyAnimation_) {
        StopPropertyTranslateAnimation(isFinishAnimation_);
    }

    targetIndex_ = targetIndex;

    if (GetDuration() == 0 || !isVisible_) {
        SwipeToWithoutAnimation(index);
        return;
    }

    MarkDirtyNodeSelf();
}

void SwiperPattern::ShowNext()
{
    if (IsVisibleChildrenSizeLessThanSwiper()) {
        return;
    }
    indicatorDoingAnimation_ = false;
    auto childrenSize = TotalCount();
    std::optional<int32_t> preIndex;
    if (preTargetIndex_.has_value()) {
        if (GetLoopIndex(preTargetIndex_.value()) >= childrenSize - GetDisplayCount() && !IsLoop()) {
            return;
        }
        preIndex = preTargetIndex_.value();
    } else if (GetLoopIndex(currentIndex_) >= childrenSize - GetDisplayCount() && !IsLoop()) {
        return;
    }
    if (childrenSize <= 0 || GetDisplayCount() == 0) {
        return;
    }
    StopAutoPlay();
    StopTranslateAnimation();

    StopSpringAnimationAndFlushImmediately();
    StopFadeAnimation();
    StopIndicatorAnimation();
    if (preIndex) {
        isUserFinish_ = false;
        FinishAnimation();
    }
    moveDirection_ = true;

    if (isVisible_) {
        targetIndex_ = currentIndex_ + 1;
        preTargetIndex_ = targetIndex_;
        MarkDirtyNodeSelf();
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    } else {
        SwipeToWithoutAnimation(currentIndex_ + 1);
    }
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireIndicatorChangeEvent(GetLoopIndex(currentIndex_));
}

void SwiperPattern::ShowPrevious()
{
    if (IsVisibleChildrenSizeLessThanSwiper()) {
        return;
    }

    if (IsAutoLinear() && static_cast<int32_t>(itemPosition_.size()) == TotalCount() && !autoLinearReachBoundary) {
        return;
    }

    indicatorDoingAnimation_ = false;
    auto childrenSize = TotalCount();
    std::optional<int32_t> preIndex;
    if (preTargetIndex_.has_value()) {
        if (GetLoopIndex(preTargetIndex_.value()) <= 0 && !IsLoop()) {
            return;
        }
        preIndex = preTargetIndex_.value();
    } else if (GetLoopIndex(currentIndex_) <= 0 && !IsLoop()) {
        return;
    }
    if (childrenSize <= 0 || GetDisplayCount() == 0) {
        return;
    }
    StopAutoPlay();
    StopTranslateAnimation();
    StopSpringAnimationAndFlushImmediately();
    StopFadeAnimation();
    StopIndicatorAnimation();

    if (preIndex) {
        isUserFinish_ = false;
        FinishAnimation();
    }
    moveDirection_ = false;

    if (isVisible_) {
        targetIndex_ = currentIndex_ - 1;
        preTargetIndex_ = targetIndex_;
        MarkDirtyNodeSelf();
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    } else {
        SwipeToWithoutAnimation(currentIndex_ - 1);
    }
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireIndicatorChangeEvent(GetLoopIndex(currentIndex_));
}

void SwiperPattern::FinishAnimation()
{
    StopTranslateAnimation();
    StopSpringAnimation();
    StopFadeAnimation();
    StopIndicatorAnimation();

    if (usePropertyAnimation_) {
        isFinishAnimation_ = true;
        StopPropertyTranslateAnimation(isFinishAnimation_);
    }
    if (isUserFinish_) {
        if (swiperController_ && swiperController_->GetFinishCallback()) {
            auto finishCallback = swiperController_->GetFinishCallback();
            finishCallback();
            swiperController_->SetFinishCallback(nullptr);
        }
    } else {
        isUserFinish_ = true;
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
    AnimationUtils::StopAnimation(springAnimation_);
    if (springAnimationIsRunning_) {
        springAnimationIsRunning_ = false;
    }
}

void SwiperPattern::StopFadeAnimation()
{
    AnimationUtils::StopAnimation(fadeAnimation_);
    if (fadeAnimationIsRunning_) {
        fadeAnimationIsRunning_ = false;
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
        if (!IsShowIndicator()) {
            return;
        }
        indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, GetIndicatorId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        swiperNode->AddChild(indicatorNode);
    } else {
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
        auto pattern = weak.Upgrade();
        if (pattern) {
            if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
                return;
            }
            pattern->FireAndCleanScrollingListener();
            TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper drag start");
            pattern->HandleDragStart(info);
            // notify scrollStart upwards
            pattern->NotifyParentScrollStart(pattern->direction_ == Axis::HORIZONTAL ? info.GetGlobalLocation().GetX()
                                                                                     : info.GetGlobalLocation().GetY());
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
        auto pattern = weak.Upgrade();
        if (pattern) {
            if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
                return;
            }
            TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper drag end. Velocity: %{public}f px/s", info.GetMainVelocity());
            pattern->HandleDragEnd(info.GetMainVelocity());
        }
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper drag cancel");
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

void SwiperPattern::InitOnFocusInternal(const RefPtr<FocusHub>& focusHub)
{
    auto focusTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleFocusInternal();
        }
    };
    focusHub->SetOnFocusInternal(std::move(focusTask));
}

void SwiperPattern::HandleFocusInternal()
{
    currentFocusIndex_ = currentIndex_;
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
    if ((GetDirection() == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_LEFT) ||
        (GetDirection() == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_UP)) {
        auto onlyFlushFocus = GetDisplayCount() > 1 && currentFocusIndex_ > GetLoopIndex(currentIndex_);
        if (onlyFlushFocus) {
            currentFocusIndex_ = GetLoopIndex(currentFocusIndex_ - 1);
            FlushFocus(GetCurrentFrameNode(currentFocusIndex_));
        } else {
            ShowPrevious();
            currentFocusIndex_ = GetLoopIndex(currentFocusIndex_ - 1);
        }

        return true;
    }
    if ((GetDirection() == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_RIGHT) ||
        (GetDirection() == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_DOWN)) {
        auto onlyFlushFocus =
            GetDisplayCount() > 1 && currentFocusIndex_ < GetLoopIndex(currentIndex_ + GetDisplayCount() - 1);
        if (onlyFlushFocus) {
            currentFocusIndex_ = GetLoopIndex(currentFocusIndex_ + 1);
            FlushFocus(GetCurrentFrameNode(currentFocusIndex_));
        } else {
            ShowNext();
            currentFocusIndex_ = GetLoopIndex(currentFocusIndex_ + 1);
        }

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
    if (itemPosition_.empty()) {
        return;
    }
    if (!IsLoop() && (isDragging_ || childScrolling_)) {
        // handle edge effects
        if (CheckOverScroll(offset)) {
            return;
        }
    }
    currentDelta_ = currentDelta_ - offset;
    currentIndexOffset_ += offset;
    if (isDragging_) {
        AnimationCallbackInfo callbackInfo;
        callbackInfo.currentOffset =
            GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
        FireGestureSwipeEvent(GetLoopIndex(gestureSwipeIndex_), callbackInfo);
    }
    MarkDirtyNodeSelf();
}

bool SwiperPattern::CheckOverScroll(float offset)
{
    switch (GetEdgeEffect()) {
        case EdgeEffect::SPRING:
            if (SpringOverScroll(offset)) {
                return true;
            }
            break;
        case EdgeEffect::FADE:
            if (FadeOverScroll(offset)) {
                return true;
            }
            break;
        case EdgeEffect::NONE:
            if (IsOutOfBoundary(offset)) {
                currentDelta_ = currentDelta_ - offset;
                MarkDirtyNodeSelf();
                return true;
            }
            break;
    }
    return false;
}

bool SwiperPattern::SpringOverScroll(float offset)
{
    bool outOfBounds = isTouchPad_ ? IsOutOfBoundary(offset) : IsOutOfBoundary();
    if (!outOfBounds) {
        return false;
    }
    targetIndex_.reset();

    auto visibleSize = CalculateVisibleSize();
    if (LessOrEqual(visibleSize, 0.0)) {
        return true;
    }
    auto friction = currentIndexOffset_ > 0
                        ? CalculateFriction(itemPosition_.begin()->second.startPos / visibleSize)
                        : CalculateFriction((visibleSize - itemPosition_.rbegin()->second.endPos) / visibleSize);

    currentDelta_ = currentDelta_ - friction * offset;
    currentIndexOffset_ += friction * offset;
    AnimationCallbackInfo callbackInfo;
    callbackInfo.currentOffset =
        GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    FireGestureSwipeEvent(GetLoopIndex(gestureSwipeIndex_), callbackInfo);
    MarkDirtyNodeSelf();
    return true;
}

bool SwiperPattern::FadeOverScroll(float offset)
{
    if (IsOutOfBoundary(fadeOffset_ + offset)) {
        auto onlyUpdateFadeOffset = (itemPosition_.begin()->first == 0 && offset < 0.0f) ||
                               (itemPosition_.rbegin()->first == TotalCount() - 1 && offset > 0.0f);
        if (!IsVisibleChildrenSizeLessThanSwiper() && !onlyUpdateFadeOffset) {
            currentDelta_ = currentDelta_ - offset;
        }
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        if (itemPosition_.begin()->first == 0 || itemPosition_.rbegin()->first == TotalCount() - 1) {
            auto remainOffset = GetDistanceToEdge();
            fadeOffset_ += (offset - remainOffset);
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        MarkDirtyNodeSelf();
        return true;
    }

    fadeOffset_ = 0.0f;
    return false;
}

void SwiperPattern::HandleTouchBottomLoop()
{
    auto currentFirstIndex = GetLoopIndex(currentFirstIndex_);
    auto currentIndex = GetLoopIndex(currentIndex_);
    bool commTouchBottom = (currentFirstIndex == TotalCount() - 1);
    bool followTouchBottom = (commTouchBottom && (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT ||
                                                     gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT));
    bool leftReleaseTouchBottom = (commTouchBottom && (currentIndex == 0 && gestureState_ ==
        GestureState::GESTURE_STATE_RELEASE_LEFT));
    bool rightReleaseTouchBottom = ((currentFirstIndex == 0) && (currentIndex == TotalCount() - 1) &&
                                    gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT);
    if (followTouchBottom || leftReleaseTouchBottom || rightReleaseTouchBottom) {
        if (currentIndex == 0) {
            // left bottom
            touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
        } else if (currentIndex == TotalCount() - 1) {
            // right bottom
            touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
        }
    }
    return;
}

void SwiperPattern::CalculateGestureState(float additionalOffset, float currentTurnPageRate)
{
    if (gestureState_ == GestureState::GESTURE_STATE_INIT) {
        return;
    }
    gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    if (GreatNotEqual(additionalOffset, 0.0f)) {
        gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    } else if (LessNotEqual(additionalOffset, 0.0f)) {
        gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    } else if ((GetLoopIndex(currentFirstIndex_) == GetLoopIndex(currentIndex_)) &&
               GreatNotEqual(std::abs(currentTurnPageRate), std::abs(turnPageRate_))) {
        gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    } else if (currentTurnPageRate == 0 && turnPageRate_ == 0) {
        gestureState_ = GestureState::GESTURE_STATE_NONE;
    } else if (GetLoopIndex(currentFirstIndex_) != GetLoopIndex(currentIndex_)) {
        gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    }
    return;
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

    float currentTurnPageRate = FLT_MAX;
    for (const auto& iter : itemPosition_) {
        if (LessNotEqual((iter.second.startPos + additionalOffset), 0) &&
            LessNotEqual((iter.second.endPos + additionalOffset), 0)) {
            continue;
        }
        if (GreatOrEqual((iter.second.startPos + additionalOffset), 0) &&
            GreatNotEqual((iter.second.endPos + additionalOffset), 0)) {
            currentFirstIndex_ = iter.first;
            currentTurnPageRate = 0.0f;
            break;
        }
        if (GreatNotEqual((iter.second.endPos + additionalOffset), 0)) {
            currentFirstIndex_ = iter.first;
            currentTurnPageRate = (NearEqual(iter.second.endPos, iter.second.startPos) ? 0 :
                ((iter.second.startPos + additionalOffset) / (iter.second.endPos - iter.second.startPos)));
            break;
        }
    }

    currentFirstIndex_ = GetLoopIndex(currentFirstIndex_);
    CalculateGestureState(additionalOffset, currentTurnPageRate);
    turnPageRate_ = (currentTurnPageRate == FLT_MAX ? turnPageRate_ : currentTurnPageRate);

    touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    if (!IsLoop() && ((currentFirstIndex_ == 0 && GreatNotEqualCustomPrecision(turnPageRate_, 0.0f)) ||
        (currentFirstIndex_ == TotalCount() - 1 && LessNotEqualCustomPrecision(turnPageRate_, 0.0f)))) {
        return;
    }
    HandleTouchBottomLoop();

    if (!indicatorDoingAnimation_) {
        child->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    if (GetLoopIndex(currentIndex_) != currentFirstIndex_) {
        auto swiperEventHub = GetEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(swiperEventHub);
        swiperEventHub->FireIndicatorChangeEvent(currentFirstIndex_);
    }
}

void SwiperPattern::UpdateAnimationProperty(float velocity)
{
    if (isDragging_ || childScrolling_) {
        targetIndex_ = ComputeNextIndexByVelocity(velocity);
        velocity_ = velocity;
    } else {
        targetIndex_ = pauseTargetIndex_;
        velocity_ = velocity;
    }

    MarkDirtyNodeSelf();
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
    }
}

void SwiperPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    if (info.GetTouches().empty()) {
        return;
    }
    auto locationInfo = info.GetTouches().front();
    auto touchType = locationInfo.GetTouchType();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown(locationInfo);
    } else if (touchType == TouchType::UP) {
        HandleTouchUp();
    } else if (touchType == TouchType::CANCEL) {
        HandleTouchUp();
    }
}

void SwiperPattern::HandleTouchDown(const TouchLocationInfo& locationInfo)
{
    isTouchDown_ = true;
    if (HasIndicatorNode()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto indicatorNode = DynamicCast<FrameNode>(host->GetChildAtIndex(host->GetChildIndexById(GetIndicatorId())));
        CHECK_NULL_VOID(indicatorNode);
        if (indicatorNode->GetTag() == V2::SWIPER_INDICATOR_ETS_TAG) {
            auto geometryNode = indicatorNode->GetGeometryNode();
            CHECK_NULL_VOID(geometryNode);
            auto hotRegion = geometryNode->GetFrameRect();
            auto touchPoint = PointF(static_cast<float>(locationInfo.GetLocalLocation().GetX()),
                static_cast<float>(locationInfo.GetLocalLocation().GetY()));
            if (hotRegion.IsInRegion(touchPoint)) {
                return;
            }
        }
    }

    if (childScrolling_) {
        // Even if the child fails to notify scrollEnd, we reset childScrolling_ flag on TouchDown to ensure its
        // value is correct.
        childScrolling_ = false;
    }

    StopIndicatorAnimation();
    if (usePropertyAnimation_) {
        StopPropertyTranslateAnimation(isFinishAnimation_);
    }

    indicatorDoingAnimation_ = false;
    // Stop translate animation when touch down.
    if (controller_ && controller_->IsRunning()) {
        controller_->Stop();
    }

    AnimationUtils::PauseAnimation(springAnimation_);
    if (springAnimationIsRunning_) {
        isTouchDownSpringAnimation_ = true;
        springAnimationIsRunning_ = false;
    }

    // Stop auto play when touch down.
    StopAutoPlay();
}

void SwiperPattern::HandleTouchUp()
{
    isTouchDown_ = false;
    auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
    if (!isDragging_ && !childScrolling_ && !NearZero(firstItemInfoInVisibleArea.second.startPos)) {
        UpdateAnimationProperty(0.0);
    }

    if (!springAnimationIsRunning_ && isTouchDownSpringAnimation_) {
        isTouchDownSpringAnimation_ = false;
        springAnimationIsRunning_ = true;
        AnimationUtils::ResumeAnimation(springAnimation_);
    }

    if (!isDragging_) {
        StartAutoPlay();
    }
}

void SwiperPattern::HandleDragStart(const GestureEvent& info)
{
    UpdateDragFRCSceneInfo(info.GetMainVelocity(), SceneStatus::START);

    StopAnimationOnScrollStart(
        info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::TOUCHPAD);
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
    mainDeltaSum_ = 0.0f;
    // in drag process, close lazy feature.
    SetLazyLoadFeature(false);
}

void SwiperPattern::StopAnimationOnScrollStart(bool flushImmediately)
{
    if (usePropertyAnimation_) {
        StopPropertyTranslateAnimation(isFinishAnimation_);
    }

    StopIndicatorAnimation();
    StopTranslateAnimation();
    if (flushImmediately) {
        StopSpringAnimationAndFlushImmediately();
    } else {
        StopSpringAnimation();
    }
}

void SwiperPattern::HandleDragUpdate(const GestureEvent& info)
{
    UpdateDragFRCSceneInfo(info.GetMainVelocity(), SceneStatus::RUNNING);
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::TOUCHPAD) {
        isTouchPad_ = true;
        auto mainSize = CalculateVisibleSize();
        if (std::abs(mainDelta) > mainSize) {
            mainDelta = mainDelta > 0 ? mainSize : -mainSize;
        }

        if ((std::abs(mainDeltaSum_ + mainDelta)) > mainSize) {
            mainDelta = GreatNotEqual((mainDeltaSum_ + mainDelta), 0) ? (mainSize - mainDeltaSum_) :
                (-mainDeltaSum_ - mainSize);
        }

        mainDeltaSum_ += mainDelta;
    }

    PointF dragPoint(static_cast<float>(info.GetGlobalLocation().GetX()),
        static_cast<float>(info.GetGlobalLocation().GetY()));
    NGGestureRecognizer::Transform(dragPoint, GetHost(), true);
    if (IsOutOfHotRegion(dragPoint)) {
        isTouchPad_ = false;
        return;
    }

    if (IsAutoLinear() && AutoLinearIsOutOfBoundary(static_cast<float>(mainDelta))) {
        return;
    }

    HandleScroll(static_cast<float>(mainDelta), SCROLL_FROM_UPDATE, NestedState::GESTURE);
    UpdateItemRenderGroup(true);
    isTouchPad_ = false;
}

void SwiperPattern::HandleDragEnd(double dragVelocity)
{
    UpdateDragFRCSceneInfo(dragVelocity, SceneStatus::END);
    const auto& addEventCallback = swiperController_->GetAddTabBarEventCallback();
    if (addEventCallback) {
        addEventCallback();
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        pipeline->FlushUITasks();
    }
    if (itemPosition_.empty()) {
        return;
    }

    if (IsAutoLinear() && AutoLinearIsOutOfBoundary(0.0f)) {
        return;
    }

    auto edgeEffect = GetEdgeEffect();
    // edge effect is NONE and reached boundary
    bool noneOutOfBoundary = (itemPosition_.begin()->first == 0 || itemPosition_.rbegin()->first == TotalCount() - 1) &&
                             NearZero(GetDistanceToEdge()) && edgeEffect == EdgeEffect::NONE;
    if (!IsLoop() && (IsOutOfBoundary() || !NearZero(fadeOffset_) || noneOutOfBoundary)) {
        isDragging_ = false;

        if (edgeEffect == EdgeEffect::SPRING) {
            PlaySpringAnimation(dragVelocity);
            return;
        }

        if (edgeEffect == EdgeEffect::FADE) {
            PlayFadeAnimation();
            return;
        }

        auto nextIndex = ComputeNextIndexByVelocity(static_cast<float>(dragVelocity), true);
        if (currentIndex_ != nextIndex) {
            UpdateCurrentIndex(nextIndex);
            do {
                auto curChildFrame = GetCurrentFrameNode(currentIndex_);
                if (!curChildFrame) {
                    break;
                }
                FlushFocus(curChildFrame);
                currentFocusIndex_ = GetLoopIndex(currentIndex_);
            } while (0);
            OnIndexChange();
            oldIndex_ = currentIndex_;
        }

        if (edgeEffect == EdgeEffect::NONE) {
            auto parent = parent_.Upgrade();
            if (parent) {
                parent->HandleScrollVelocity(dragVelocity);
            }
            UpdateItemRenderGroup(false);
            return;
        }
    }

#ifdef OHOS_PLATFORM
    ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
#endif

    // nested and reached end, need to pass velocity to parent scrollable
    auto parent = parent_.Upgrade();
    if (!IsLoop() && parent && NearZero(GetDistanceToEdge())) {
        parent->HandleScrollVelocity(dragVelocity);
    } else {
        UpdateAnimationProperty(static_cast<float>(dragVelocity));
        NotifyParentScrollEnd();
    }
    if (pipeline) {
        pipeline->FlushUITasks();
    }

    isDragging_ = false;
}

void SwiperPattern::UpdateCurrentIndex(int32_t index)
{
    currentIndex_ = index;
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateIndexWithoutMeasure(GetLoopIndex(currentIndex_));
}

int32_t SwiperPattern::ComputeNextIndexByVelocity(float velocity, bool onlyDistance) const
{
    auto nextIndex = currentIndex_;
    auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
    auto firstItemLength = firstItemInfoInVisibleArea.second.endPos - firstItemInfoInVisibleArea.second.startPos;
    if (LessOrEqual(firstItemLength, 0)) {
        return nextIndex;
    }

    auto direction = GreatNotEqual(velocity, 0.0);
    auto dragThresholdFlag = direction ? firstItemInfoInVisibleArea.second.endPos > firstItemLength / 2
                                       : firstItemInfoInVisibleArea.second.endPos < firstItemLength / 2;
    auto turnVelocity = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) ? NEW_MIN_TURN_PAGE_VELOCITY
                                                                                           : MIN_TURN_PAGE_VELOCITY;
    if ((!onlyDistance && std::abs(velocity) > turnVelocity) || dragThresholdFlag) {
        nextIndex = direction ? firstItemInfoInVisibleArea.first : firstItemInfoInVisibleArea.first + 1;
    } else {
        nextIndex = direction ? firstItemInfoInVisibleArea.first + 1 : firstItemInfoInVisibleArea.first;
    }

    if (!IsAutoLinear() && nextIndex > currentIndex_ + GetDisplayCount()) {
        nextIndex = currentIndex_ + GetDisplayCount();
    }

    if (!IsLoop()) {
        nextIndex = std::clamp(nextIndex, 0, std::max(0, TotalCount() - GetDisplayCount()));
    }
    return nextIndex;
}

void SwiperPattern::PlayPropertyTranslateAnimation(
    float translate, int32_t nextIndex, float velocity, bool stopAutoPlay)
{
    if (NearZero(translate)) {
        OnAnimationTranslateZero(nextIndex, stopAutoPlay);
        return;
    }

    AnimationOption option;
    option.SetDuration(GetDuration());
    motionVelocity_ = velocity / translate;
    option.SetCurve(GetCurveIncludeMotion());
    option.SetFinishCallbackType(GetFinishCallbackType());
    OffsetF offset;
    if (GetDirection() == Axis::HORIZONTAL) {
        offset.AddX(translate);
    } else {
        offset.AddY(translate);
    }
    if (usePropertyAnimation_) {
        auto startNewAnimationFlag = false;
        if (itemPositionInAnimation_.empty()) {
            startNewAnimationFlag = true;
        }
        if (!startNewAnimationFlag) {
            for (const auto& animationItem : itemPositionInAnimation_) {
                auto iter = itemPosition_.find(animationItem.first);
                if (iter == itemPosition_.end()) {
                    startNewAnimationFlag = true;
                    break;
                }
                if (animationItem.second.finialOffset != offset ||
                    !NearEqual(animationItem.second.startPos, iter->second.startPos) ||
                    !NearEqual(animationItem.second.endPos, iter->second.endPos)) {
                    startNewAnimationFlag = true;
                    break;
                }
            }
        }
        if (!startNewAnimationFlag) {
            stopIndicatorAnimation_ = false;
            return;
        }
        std::optional<int32_t> targetIndex;
        if (targetIndex_) {
            targetIndex = targetIndex_;
        }
        StopPropertyTranslateAnimation(isFinishAnimation_);
        StopIndicatorAnimation();

        if (targetIndex) {
            targetIndex_ = targetIndex;
            MarkDirtyNodeSelf();
            return;
        }
    }
    auto finishCallback = [id = Container::CurrentId(), weak = WeakClaim(this), offset]() {
        ContainerScope scope(id);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto task = [weak, offset]() {
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            swiper->targetIndex_.reset();
            swiper->OnPropertyTranslateAnimationFinish(offset);
        };
        context->PostSyncEvent(task);
    };
    // initial translate info.
    for (auto& item : itemPosition_) {
        auto frameNode = item.second.node;
        if (frameNode) {
            frameNode->GetRenderContext()->UpdateTranslateInXY(item.second.finialOffset);
        }
    }
    // property callback will call immediately.
    auto propertyUpdateCallback = [swiper = WeakClaim(this), offset]() {
        auto swiperPattern = swiper.Upgrade();
        if (!swiperPattern) {
            return;
        }
        for (auto& item : swiperPattern->itemPosition_) {
            auto frameNode = item.second.node;
            if (frameNode) {
                frameNode->GetRenderContext()->UpdateTranslateInXY(offset);
                item.second.finialOffset = offset;
            }
        }
        swiperPattern->itemPositionInAnimation_ = swiperPattern->itemPosition_;
    };
    usePropertyAnimation_ = true;
    propertyAnimationIndex_ = nextIndex;
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost(), option);
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
            swiper->FireAnimationStartEvent(swiper->GetLoopIndex(swiper->currentIndex_), nextIndex, info);
            swiper->FireAndCleanScrollingListener();
        });
    }

    // enable lazy load feature.
    SetLazyLoadFeature(true);
    UpdateItemRenderGroup(true);
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
    for (auto& item : itemPositionInAnimation_) {
        auto frameNode = item.second.node;
        if (frameNode) {
            frameNode->GetRenderContext()->UpdateTranslateInXY(OffsetF());
        }
        item.second.finialOffset = OffsetF();
    }
    itemPositionInAnimation_.clear();
    // update postion info.
    UpdateOffsetAfterPropertyAnimation(offset.GetMainOffset(GetDirection()));
    OnTranslateFinish(propertyAnimationIndex_, false, isFinishAnimation_);
}

void SwiperPattern::StopPropertyTranslateAnimation(bool isFinishAnimation, bool isBeforeCreateLayoutWrapper)
{
    if (!usePropertyAnimation_) {
        return;
    }
    usePropertyAnimation_ = false;

    // Stop CurrentAnimationProperty.
    AnimationOption option;
    option.SetDuration(0);
    option.SetCurve(Curves::LINEAR);
    auto propertyUpdateCallback = [weak = WeakClaim(this)]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        for (auto& item : swiper->itemPositionInAnimation_) {
            auto frameNode = item.second.node;
            if (!frameNode) {
                continue;
            }
            frameNode->GetRenderContext()->CancelTranslateXYAnimation();
        }
    };
    AnimationUtils::Animate(option, propertyUpdateCallback);
    OffsetF currentOffset;
    for (auto& item : itemPositionInAnimation_) {
        auto frameNode = item.second.node;
        if (!frameNode) {
            continue;
        }
        currentOffset = frameNode->GetRenderContext()->GetTranslateXYProperty();
        frameNode->GetRenderContext()->UpdateTranslateInXY(OffsetF());
        item.second.finialOffset = OffsetF();
    }
    itemPositionInAnimation_.clear();
    if (!isBeforeCreateLayoutWrapper) {
        UpdateOffsetAfterPropertyAnimation(currentOffset.GetMainOffset(GetDirection()));
    }
    OnTranslateFinish(propertyAnimationIndex_, false, isFinishAnimation, true);
}

RefPtr<Curve> SwiperPattern::GetCurveIncludeMotion() const
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
                springCurve->UpdateVelocity(motionVelocity_);
            }
        }
        if (InstanceOf<InterpolatingSpring>(curve)) {
            auto interpolatingSpring = DynamicCast<InterpolatingSpring>(curve);
            // check velocity to judge if this current velocity.
            if (interpolatingSpring->GetVelocity() < 0) {
                return AceType::MakeRefPtr<InterpolatingSpring>(motionVelocity_, interpolatingSpring->GetMass(),
                    interpolatingSpring->GetStiffness(), interpolatingSpring->GetDamping());
            }
        }
        return curve;
    }
    // use spring motion feature.
    // interpolatingSpring: (mass: 1, stiffness:328, damping: 34)
    return AceType::MakeRefPtr<InterpolatingSpring>(motionVelocity_, 1, 328, 34);
}

void SwiperPattern::PlayIndicatorTranslateAnimation(float translate)
{
    if (!stopIndicatorAnimation_) {
        stopIndicatorAnimation_ = true;
        return;
    }
    const auto& turnPageRateCallback = swiperController_->GetTurnPageRateCallback();
    if (!indicatorId_.has_value() && !turnPageRateCallback) {
        return;
    }
    CheckMarkDirtyNodeForRenderIndicator(translate);
    AnimationUtils::StopAnimation(indicatorAnimation_);
    indicatorAnimationIsRunning_ = false;
    if (itemPosition_.empty()) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto weak = AceType::WeakClaim(this);
    host->CreateAnimatablePropertyFloat(INDICATOR_PROPERTY_NAME, 0, [weak](float value) {
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            auto currentContentOffset = -(swiper->itemPosition_.begin()->second.startPos);
            auto index = swiper->itemPosition_.begin()->first;
            const auto& turnPageRateCallback = swiper->swiperController_->GetTurnPageRateCallback();
            if (turnPageRateCallback && !NearZero(swiper->GetTranslateLength())) {
                turnPageRateCallback(index, (currentContentOffset - value) / swiper->GetTranslateLength());
            }
        });

    AnimationOption option;
    option.SetDuration(GetDuration());
    option.SetCurve(Curves::LINEAR);

    host->UpdateAnimatablePropertyFloat(INDICATOR_PROPERTY_NAME, 0);
    indicatorAnimationIsRunning_ = true;
    indicatorAnimation_ = AnimationUtils::StartAnimation(
        option, [host, translate]() { host->UpdateAnimatablePropertyFloat(INDICATOR_PROPERTY_NAME, translate); },
        [weak]() {
            auto swiperPattern = weak.Upgrade();
            CHECK_NULL_VOID(swiperPattern);
            swiperPattern->indicatorAnimationIsRunning_ = false;
        });
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
        swiper->FireAnimationStartEvent(
            swiper->GetLoopIndex(swiper->currentIndex_), swiper->GetLoopIndex(nextIndex), info);
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
            swiper->OnTranslateFinish(nextIndex, restartAutoPlay, swiper->isFinishAnimation_);
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
        swiper->OnTranslateFinish(nextIndex, restartAutoPlay, swiper->isFinishAnimation_);
    });
    controller_->PlayMotion(scrollMotion);
}

void SwiperPattern::OnSpringAnimationStart(float velocity)
{
    AnimationCallbackInfo info;
    info.velocity = Dimension(velocity, DimensionUnit::PX).ConvertToVp();
    info.currentOffset = GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();

    nextIndex_ = ComputeNextIndexByVelocity(velocity);
    if (GetLoopIndex(currentIndex_) == GetLoopIndex(nextIndex_)) {
        info.targetOffset = info.currentOffset;
    } else {
        auto iter = itemPosition_.find(nextIndex_);
        auto nextOffset = iter != itemPosition_.end() ? iter->second.startPos : 0.0f;
        info.targetOffset = GetCustomPropertyOffset() + Dimension(nextOffset, DimensionUnit::PX).ConvertToVp();
    }

    FireAnimationStartEvent(GetLoopIndex(currentIndex_), GetLoopIndex(nextIndex_), info);
}

void SwiperPattern::OnSpringAndFadeAnimationFinish()
{
    auto itemInfoInVisibleArea = std::make_pair(0, SwiperItemInfo {});
    if (!itemPosition_.empty()) {
        auto item = itemPosition_.find(nextIndex_);
        itemInfoInVisibleArea = std::make_pair(item->first,
            SwiperItemInfo { item->second.startPos, item->second.endPos });
    }
    if (GetLoopIndex(currentIndex_) != GetLoopIndex(nextIndex_)) {
        UpdateCurrentIndex(nextIndex_);
        do {
            auto curChildFrame = GetCurrentFrameNode(currentIndex_);
            if (!curChildFrame) {
                break;
            }
            FlushFocus(curChildFrame);
            currentFocusIndex_ = GetLoopIndex(currentIndex_);
        } while (0);
        OnIndexChange();
        oldIndex_ = currentIndex_;
    }
    AnimationCallbackInfo info;
    auto indexStartPos = itemInfoInVisibleArea.second.startPos;
    info.currentOffset = GetCustomPropertyOffset() + Dimension(indexStartPos, DimensionUnit::PX).ConvertToVp();
    FireAnimationEndEvent(GetLoopIndex(currentIndex_), info);
    currentIndexOffset_ = indexStartPos;
    UpdateItemRenderGroup(false);
    NotifyParentScrollEnd();
    StartAutoPlay();
    fadeAnimationIsRunning_ = false;
}

void SwiperPattern::OnFadeAnimationStart()
{
    AnimationCallbackInfo info;
    info.currentOffset = GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    nextIndex_ = ComputeNextIndexByVelocity(0.0);
    if (GetLoopIndex(currentIndex_) == GetLoopIndex(nextIndex_)) {
        info.targetOffset = info.currentOffset;
    } else {
        info.targetOffset = GetCustomPropertyOffset();
    }

    FireAnimationStartEvent(GetLoopIndex(currentIndex_), GetLoopIndex(nextIndex_), info);
    fadeAnimationIsRunning_ = true;
}

void SwiperPattern::PlayFadeAnimation()
{
    if (NearZero(fadeOffset_)) {
        fadeAnimationIsRunning_ = false;
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto weak = AceType::WeakClaim(this);
    host->CreateAnimatablePropertyFloat(FADE_PROPERTY_NAME, 0, Animation<double>::ValueCallback([weak](float value) {
        auto swiper = weak.Upgrade();
        if (swiper && swiper->GetHost()) {
            swiper->fadeOffset_ = value;
            swiper->GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }));

    AnimationOption option;
    option.SetDuration(FADE_DURATION);
    option.SetCurve(Curves::LINEAR);

    host->UpdateAnimatablePropertyFloat(FADE_PROPERTY_NAME, fadeOffset_);
    constexpr float end = 0.0f;
    nextIndex_ = currentIndex_;
    fadeAnimation_ = AnimationUtils::StartAnimation(option,
        [weak, host, end]() {
            auto swiperPattern = weak.Upgrade();
            CHECK_NULL_VOID(swiperPattern);
            swiperPattern->OnFadeAnimationStart();
            host->UpdateAnimatablePropertyFloat(FADE_PROPERTY_NAME, end);
        },
        [weak]() {
            auto swiperPattern = weak.Upgrade();
            CHECK_NULL_VOID(swiperPattern);
            swiperPattern->OnSpringAndFadeAnimationFinish();
        });
}

void SwiperPattern::PlaySpringAnimation(double dragVelocity)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto mainSize = CalculateVisibleSize();
    if (LessOrEqual(mainSize, 0)) {
        return;
    }
    if (itemPosition_.empty()) {
        return;
    }
    childScrolling_ = false;

    ExtentPair extentPair = ExtentPair(currentOffset_ + mainSize - itemPosition_.rbegin()->second.endPos,
        currentOffset_ - itemPosition_.begin()->second.startPos);

    host->CreateAnimatablePropertyFloat(SPRING_PROPERTY_NAME, 0, [weak = AceType::WeakClaim(this)](float position) {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        if (!swiper->isTouchDown_) {
            swiper->UpdateCurrentOffset(static_cast<float>(position) - swiper->currentOffset_);
        }
    });

    host->UpdateAnimatablePropertyFloat(SPRING_PROPERTY_NAME, currentOffset_);
    auto delta = dragVelocity < 0.0f ? extentPair.Leading() : extentPair.Trailing();

    // spring curve: (velocity: 0.0, mass: 1.0, stiffness: 228.0, damping: 30.0)
    auto springCurve = MakeRefPtr<SpringCurve>(0.0f, 1.0f, 228.0f, 30.0f);
    AnimationOption option;
    option.SetCurve(springCurve);
    option.SetDuration(SPEING_DURATION);

    nextIndex_ = currentIndex_;
    springAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this), dragVelocity, host, delta]() {
            auto swiperPattern = weak.Upgrade();
            CHECK_NULL_VOID(swiperPattern);
            swiperPattern->springAnimationIsRunning_ = true;
            swiperPattern->OnSpringAnimationStart(static_cast<float>(dragVelocity));
            host->UpdateAnimatablePropertyFloat(SPRING_PROPERTY_NAME, delta);
        },
        [weak = AceType::WeakClaim(this)]() {
            auto swiperPattern = weak.Upgrade();
            CHECK_NULL_VOID(swiperPattern);
            swiperPattern->springAnimationIsRunning_ = false;
            swiperPattern->isTouchDownSpringAnimation_ = false;
            swiperPattern->OnSpringAndFadeAnimationFinish();
        });
}

bool SwiperPattern::IsOutOfBoundary(float mainOffset) const
{
    if (IsLoop() || itemPosition_.empty()) {
        return false;
    }

    auto startPos = itemPosition_.begin()->second.startPos;
    startPos = NearZero(startPos, PX_EPSILON) ? 0.0 : startPos;
    auto isOutOfStart = itemPosition_.begin()->first == 0 && GreatNotEqual(startPos + mainOffset, 0.0);

    auto visibleWindowSize = CalculateVisibleSize();
    auto endPos = itemPosition_.rbegin()->second.endPos + mainOffset;
    endPos = NearEqual(endPos, visibleWindowSize, PX_EPSILON) ? visibleWindowSize : endPos;
    auto isOutOfEnd = itemPosition_.rbegin()->first == TotalCount() - 1 && LessNotEqual(endPos, visibleWindowSize);

    return isOutOfStart || isOutOfEnd;
}

bool SwiperPattern::AutoLinearIsOutOfBoundary(float mainOffset) const
{
    if (itemPosition_.empty() || static_cast<int32_t>(itemPosition_.size()) < TotalCount()) {
        return false;
    }

    auto startPos = itemPosition_.begin()->second.startPos;
    auto isOutOfStart = GreatNotEqual(startPos + mainOffset, 0.0);

    auto visibleWindowSize = CalculateVisibleSize();
    auto endPos = itemPosition_.rbegin()->second.endPos + mainOffset;
    auto isOutOfEnd = LessNotEqual(endPos, visibleWindowSize);

    return isOutOfStart || isOutOfEnd;
}

float SwiperPattern::GetDistanceToEdge() const
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
    CHECK_NULL_RETURN(swiperLayoutProperty, 0.0f);
    return SwiperUtils::IsStretch(swiperLayoutProperty) ?
        ConvertToPx(swiperLayoutProperty->GetPrevMargin().value_or(0.0_vp),
        swiperLayoutProperty->GetLayoutConstraint()->scaleProperty, 0).value_or(0) : 0.0f;
}

float SwiperPattern::GetNextMargin() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, 0.0f);
    return SwiperUtils::IsStretch(swiperLayoutProperty) ?
        ConvertToPx(swiperLayoutProperty->GetNextMargin().value_or(0.0_vp),
        swiperLayoutProperty->GetLayoutConstraint()->scaleProperty, 0).value_or(0) : 0.0f;
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
        float contentWidth = GetMainContentSize();
        auto displayCount =
            CalculateCount(contentWidth, minSize, SWIPER_MARGIN.ConvertToPx(), SWIPER_GUTTER.ConvertToPx());
        if (LessOrEqual(minSize, 0)) {
            displayCount = 1;
        }
        displayCount = displayCount > 0 ? displayCount : 1;
        auto totalCount = TotalCount();
        displayCount = displayCount > totalCount ? totalCount : displayCount;
        auto displayCountProperty = swiperLayoutProperty->GetDisplayCount().value_or(1);

        if (displayCountProperty != displayCount) {
            swiperLayoutProperty->UpdateDisplayCount(displayCount);
            auto host = GetHost();
            CHECK_NULL_RETURN(host, 1);
            host->MarkDirtyNode(
                (crossMatchChild_ ? PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD : PROPERTY_UPDATE_MEASURE_SELF) |
                PROPERTY_UPDATE_RENDER);
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
    return swiperLayoutProperty->GetMinSize().has_value();
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
    if (TotalDisPlayCount() >= TotalCount()) {
        return false;
    }
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, true);
    return swiperLayoutProperty->GetLoop().value_or(true);
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
        swiperParameters_->itemWidth = swiperIndicatorTheme->GetSize();
        swiperParameters_->itemHeight = swiperIndicatorTheme->GetSize();
        swiperParameters_->selectedItemWidth = swiperIndicatorTheme->GetSize();
        swiperParameters_->selectedItemHeight = swiperIndicatorTheme->GetSize();
        swiperParameters_->maskValue = false;
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

std::pair<int32_t, SwiperItemInfo> SwiperPattern::GetLastItemInfoInVisibleArea() const
{
    if (itemPosition_.empty()) {
        return std::make_pair(0, SwiperItemInfo {});
    }
    auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
    auto targetVisableIndex = firstItemInfoInVisibleArea.first;
    targetVisableIndex += GetDisplayCount() - 1;
    auto iter = itemPosition_.find(targetVisableIndex);
    if (iter != itemPosition_.end()) {
        return std::make_pair(iter->first, SwiperItemInfo { iter->second.startPos, iter->second.endPos });
    }
    return std::make_pair(itemPosition_.rbegin()->first,
        SwiperItemInfo { itemPosition_.rbegin()->second.startPos, itemPosition_.rbegin()->second.endPos });
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
    auto context = host->GetRenderContext();
    CHECK_NULL_RETURN(context, true);

    auto hotRegion = context->GetPaintRectWithoutTransform();
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
    layoutProperty->ResetIndicatorLayoutStyle();
    if (swiperParameters->dimLeft.has_value()) {
        layoutProperty->UpdateLeft(swiperParameters->dimLeft.value());
    }
    if (swiperParameters->dimTop.has_value()) {
        layoutProperty->UpdateTop(swiperParameters->dimTop.value());
    }
    if (swiperParameters->dimRight.has_value()) {
        layoutProperty->UpdateRight(swiperParameters->dimRight.value());
    }
    if (swiperParameters->dimBottom.has_value()) {
        layoutProperty->UpdateBottom(swiperParameters->dimBottom.value());
    }
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

    MarkDirtyNodeSelf();
    indicatorNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
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
    layoutProperty->ResetIndicatorLayoutStyle();
    if (swiperDigitalParameters->dimLeft.has_value()) {
        layoutProperty->UpdateLeft(swiperDigitalParameters->dimLeft.value());
    }
    if (swiperDigitalParameters->dimTop.has_value()) {
        layoutProperty->UpdateTop(swiperDigitalParameters->dimTop.value());
    }
    if (swiperDigitalParameters->dimRight.has_value()) {
        layoutProperty->UpdateRight(swiperDigitalParameters->dimRight.value());
    }
    if (swiperDigitalParameters->dimBottom.has_value()) {
        layoutProperty->UpdateBottom(swiperDigitalParameters->dimBottom.value());
    }
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
            if (!swiper->IsLoop() && swiper->GetLoopIndex(swiper->currentIndex_) + 1 > (childrenSize - displayCount)) {
                return;
            }
            swiper->targetIndex_ = swiper->currentIndex_ + 1;
            swiper->MarkDirtyNodeSelf();
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
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    pipeline->AddWindowStateChangedCallback(host->GetId());

    if (hasVisibleChangeRegistered_ || !IsAutoPlay()) {
        return;
    }

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
    pipeline->RemoveVisibleAreaChangeNode(host->GetId());
    pipeline->AddVisibleAreaChangeNode(host, 0.0f, callback);
    hasVisibleChangeRegistered_ = true;
}

bool SwiperPattern::NeedAutoPlay() const
{
    bool reachEnd = GetLoopIndex(CurrentIndex()) >= TotalCount() - 1 && !IsLoop();
    return IsAutoPlay() && !reachEnd && isVisible_ && !isIndicatorLongPress_;
}

void SwiperPattern::TriggerAnimationEndOnSwipeToLeft()
{
    auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
    auto firstItemLength = firstItemInfoInVisibleArea.second.endPos - firstItemInfoInVisibleArea.second.startPos;
    auto firstIndexStartPos = firstItemInfoInVisibleArea.second.startPos;
    if (std::abs(firstIndexStartPos) < (firstItemLength / 2)) {
        currentIndexOffset_ = firstItemInfoInVisibleArea.second.startPos;
        UpdateCurrentIndex(firstItemInfoInVisibleArea.first);
    } else {
        auto secondItemInfoInVisibleArea = GetSecondItemInfoInVisibleArea();
        currentIndexOffset_ = secondItemInfoInVisibleArea.second.startPos;
        UpdateCurrentIndex(secondItemInfoInVisibleArea.first);
    }
}

void SwiperPattern::TriggerAnimationEndOnSwipeToRight()
{
    auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
    auto firstItemLength = firstItemInfoInVisibleArea.second.endPos - firstItemInfoInVisibleArea.second.startPos;
    auto secondItemInfoInVisibleArea = GetSecondItemInfoInVisibleArea();
    auto secondIndexStartPos = secondItemInfoInVisibleArea.second.startPos;
    if (std::abs(secondIndexStartPos) < (firstItemLength / 2)) {
        currentIndexOffset_ = secondItemInfoInVisibleArea.second.startPos;
        UpdateCurrentIndex(secondItemInfoInVisibleArea.first);
    } else {
        currentIndexOffset_ = firstItemInfoInVisibleArea.second.startPos;
        UpdateCurrentIndex(firstItemInfoInVisibleArea.first);
    }
}

void SwiperPattern::TriggerAnimationEndOnForceStop()
{
    auto pauseTargetIndex = pauseTargetIndex_.has_value() ? pauseTargetIndex_.value() : currentIndex_;
    if (currentIndex_ != pauseTargetIndex) {
        auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
        if (currentIndex_ == firstItemInfoInVisibleArea.first) {
            // swipe to left
            TriggerAnimationEndOnSwipeToLeft();
        } else {
            // swipe to right
            TriggerAnimationEndOnSwipeToRight();
        }
        do {
            auto curChildFrame = GetCurrentFrameNode(currentIndex_);
            if (!curChildFrame) {
                break;
            }
            FlushFocus(curChildFrame);
            currentFocusIndex_ = GetLoopIndex(currentIndex_);
        } while (0);

        OnIndexChange();
        oldIndex_ = currentIndex_;
    }
    AnimationCallbackInfo info;
    info.currentOffset = GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    FireAnimationEndEvent(GetLoopIndex(currentIndex_), info);
    UpdateItemRenderGroup(false);
}

void SwiperPattern::TriggerEventOnFinish(int32_t nextIndex)
{
    ResetAndUpdateIndexOnAnimationEnd(nextIndex);

    AnimationCallbackInfo info;
    info.currentOffset = GetCustomPropertyOffset();
    FireAnimationEndEvent(GetLoopIndex(currentIndex_), info);
}

void SwiperPattern::SetLazyLoadFeature(bool useLazyLoad) const
{
    SetLazyForEachLongPredict(useLazyLoad);

    if (useLazyLoad) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto layoutProperty = host->GetLayoutProperty<SwiperLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto cacheCount = layoutProperty->GetCachedCountValue(1);
        std::set<int32_t> forEachIndexSet;
        for (auto count = 1; count <= cacheCount; count++) {
            forEachIndexSet.emplace(GetLoopIndex(currentIndex_ + count));
            forEachIndexSet.emplace(GetLoopIndex(currentIndex_ - count));
        }
        if (forEachIndexSet.empty()) {
            return;
        }

        const auto& children = host->GetChildren();
        for (const auto& child : children) {
            if (child->GetTag() != V2::JS_FOR_EACH_ETS_TAG) {
                continue;
            }
            auto pipeline = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto taskExecutor = pipeline->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [weak = WeakClaim(RawPtr(child)), forEachIndexSet]() {
                    auto node = weak.Upgrade();
                    CHECK_NULL_VOID(node);
                    auto forEachNode = AceType::DynamicCast<ForEachNode>(node);
                    CHECK_NULL_VOID(forEachNode);
                    for (auto index : forEachIndexSet) {
                        auto childNode = forEachNode->GetChildAtIndex(index);
                        CHECK_NULL_VOID(childNode);
                        childNode->Build(nullptr);
                    }
                },
                TaskExecutor::TaskType::UI);
        }
    }
}

void SwiperPattern::SetLazyForEachLongPredict(bool useLazyLoad) const
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

void SwiperPattern::SetLazyLoadIsLoop() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& children = host->GetChildren();
    for (auto&& child : children) {
        auto lazyForEach = DynamicCast<LazyForEachNode>(child);
        if (lazyForEach) {
            lazyForEach->SetIsLoop(IsLoop());
        }
    }
}

bool SwiperPattern::IsVisibleChildrenSizeLessThanSwiper()
{
    if (itemPosition_.empty()) {
        return true;
    }
    auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
    auto lastItemInfoInVisibleArea = GetLastItemInfoInVisibleArea();
    auto calcDisPlayCount = lastItemInfoInVisibleArea.first - firstItemInfoInVisibleArea.first + 1;
    if (Positive(TotalCount() - calcDisPlayCount)) {
        return false;
    }
    if (static_cast<int32_t>(itemPosition_.size()) == TotalCount()) {
        auto totalChildrenSize = lastItemInfoInVisibleArea.second.endPos - firstItemInfoInVisibleArea.second.startPos;
        if (NonPositive(totalChildrenSize)) {
            return true;
        }
        auto prevMargin = GetPrevMargin();
        auto nextMargin = GetNextMargin();
        auto itemSpace = GetItemSpace();
        auto host = GetHost();
        CHECK_NULL_RETURN(host, true);
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, true);
        auto mainSize = geometryNode->GetFrameSize().MainSize(GetDirection());
        if (itemSpace > mainSize) {
            itemSpace = 0.0f;
        }
        auto prevMarginMontage = Positive(prevMargin) ? prevMargin + itemSpace : 0.0f;
        auto nextMarginMontage = Positive(nextMargin) ? nextMargin + itemSpace : 0.0f;

        if (totalChildrenSize <= (contentMainSize_ - prevMarginMontage - nextMarginMontage)) {
            return true;
        }
    }
    return false;
}

void SwiperPattern::UpdateItemRenderGroup(bool itemRenderGroup)
{
    for (auto& item : itemPosition_) {
        if (auto frameNode = item.second.node) {
            auto context = frameNode->GetRenderContext();
            CHECK_NULL_VOID(context);
            context->UpdateSuggestedRenderGroup(itemRenderGroup);
        }
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    for (auto child : host->GetChildren()) {
        auto frameNode = DynamicCast<FrameNode>(child);
        if (!frameNode || child->GetTag() == V2::SWIPER_INDICATOR_ETS_TAG) {
            continue;
        }
        auto context = frameNode->GetRenderContext();
        CHECK_NULL_VOID(context);
        context->UpdateSuggestedRenderGroup(itemRenderGroup);
    }
}

void SwiperPattern::OnTranslateFinish(int32_t nextIndex, bool restartAutoPlay, bool isFinishAnimation, bool forceStop)
{
    if (forceStop && !isFinishAnimation) {
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
            MarkDirtyNodeSelf();
        }
    }

    auto delayTime = GetInterval() - GetDuration();
    delayTime = std::clamp(delayTime, 0, delayTime);
    if (NeedAutoPlay() && isUserFinish_ && !forceStop) {
        PostTranslateTask(delayTime);
    }
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
    UpdateItemRenderGroup(false);
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

    if (isDragging_) {
        HandleDragEnd(0.0);
    }

    StopSpringAnimationAndFlushImmediately();
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
        leftArrowPattern->SetButtonVisible(hoverFlag);
        auto rightArrowNode =
            DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(swiperNode->GetChildIndexById(GetRightButtonId())));
        CHECK_NULL_VOID(rightArrowNode);
        auto rightArrowPattern = rightArrowNode->GetPattern<SwiperArrowPattern>();
        CHECK_NULL_VOID(rightArrowPattern);
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
    arrowLayoutProperty->UpdateLoop(layoutProperty->GetLoop().value_or(true));
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

    auto mouseEvent = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(info);
        }
    };
    if (mouseEvent_) {
        inputHub->RemoveOnMouseEvent(mouseEvent_);
    }
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseEvent));
    inputHub->AddOnMouseEvent(mouseEvent_);
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

    if (!IsLoop() && GetLoopIndex(currentIndex_) == 0) {
        leftNodeRect = GetArrowFrameRect(GetIndicatorId());
    }

    if (!IsLoop() && GetLoopIndex(currentIndex_) == TotalCount() - 1) {
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
    auto paddingAndBorderValue = GetDirection() == Axis::HORIZONTAL
                                     ? paddingAndBorder.left.value_or(0.0) + tabsPaddingAndBorder_.left.value_or(0.0)
                                     : paddingAndBorder.top.value_or(0.0) + tabsPaddingAndBorder_.top.value_or(0.0);

    auto preMarginPX = GetPrevMargin();
    if (layoutProperty->GetPrevMargin().has_value() && preMarginPX > 0.0) {
        preMarginPX += GetItemSpace();
    }

    return Dimension(paddingAndBorderValue + preMarginPX, DimensionUnit::PX).ConvertToVp();
}

float SwiperPattern::GetCurrentFirstIndexStartPos() const
{
    if (itemPosition_.empty()) {
        return 0.0;
    }

    return itemPosition_.begin()->second.startPos;
}

int32_t SwiperPattern::TotalDisPlayCount() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, 1);
    auto displayCount = GetDisplayCount();
    if (SwiperUtils::IsStretch(swiperLayoutProperty)) {
        if (Positive(swiperLayoutProperty->GetPrevMarginValue(0.0_px).ConvertToPx())) {
            displayCount++;
        }
        if (Positive(swiperLayoutProperty->GetNextMarginValue(0.0_px).ConvertToPx())) {
            displayCount++;
        }
    }
    return displayCount;
}

void SwiperPattern::MarkDirtyNodeSelf()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!crossMatchChild_) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    } else {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    }
}

void SwiperPattern::ResetAndUpdateIndexOnAnimationEnd(int32_t nextIndex)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    targetIndex_.reset();
    if (preTargetIndex_.has_value()) {
        preTargetIndex_.reset();
    }

    if (currentIndex_ == nextIndex) {
        return;
    }

    if (isFinishAnimation_) {
        currentDelta_ = 0.0f;
        itemPosition_.clear();
        isVoluntarilyClear_ = true;
        jumpIndex_ = nextIndex;
        MarkDirtyNodeSelf();
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
        isFinishAnimation_ = false;
    } else {
        UpdateCurrentIndex(nextIndex);
        do {
            auto curChildFrame = GetCurrentFrameNode(currentFocusIndex_);
            if (!curChildFrame) {
                break;
            }
            FlushFocus(curChildFrame);
        } while (0);
        oldIndex_ = nextIndex;
        currentFirstIndex_ = GetLoopIndex(nextIndex);
        turnPageRate_ = 0.0f;
        currentIndexOffset_ = 0.0f;
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

void SwiperPattern::UpdateDragFRCSceneInfo(float speed, SceneStatus sceneStatus)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->AddFRCSceneInfo(SWIPER_DRAG_SCENE, speed, sceneStatus);
}

void SwiperPattern::OnScrollStartRecursive(float position)
{
    if (IsDisableSwipe()) {
        return;
    }
    childScrolling_ = true;
    gestureSwipeIndex_ = currentIndex_;
    StopAnimationOnScrollStart(false);
    NotifyParentScrollStart(position);
}

void SwiperPattern::NotifyParentScrollStart(float position)
{
    auto parent = enableNestedScroll_ ? SearchParent() : nullptr;
    if (parent) {
        parent->OnScrollStartRecursive(position);
    }
    parent_ = parent;
}

void SwiperPattern::OnScrollEndRecursive(const std::optional<float>& velocity)
{
    if (IsDisableSwipe()) {
        return;
    }
    // in case child didn't call swiper's HandleScrollVelocity
    if (!AnimationRunning()) {
        HandleDragEnd(velocity.value_or(0.0f));
    }

    childScrolling_ = false;
}

void SwiperPattern::NotifyParentScrollEnd()
{
    auto parent = parent_.Upgrade();
    if (parent && enableNestedScroll_) {
        parent->OnScrollEndRecursive(std::nullopt);
    }
}

inline bool SwiperPattern::AnimationRunning() const
{
    return (controller_ && controller_->IsRunning()) || (springAnimation_ && springAnimationIsRunning_) ||
           fadeAnimationIsRunning_ || targetIndex_ || usePropertyAnimation_;
}

bool SwiperPattern::HandleScrollVelocity(float velocity)
{
    if (IsDisableSwipe()) {
        return false;
    }

    // haven't reached edge
    if (GetDistanceToEdge() > 0.0f || IsLoop()) {
        HandleDragEnd(velocity);
        return true;
    }

    auto parent = parent_.Upgrade();
    if (parent && enableNestedScroll_) {
        // after reach end, parent handle velocity first
        if (parent->HandleScrollVelocity(velocity)) {
            return true;
        }
    }
    HandleDragEnd(velocity);
    // after reached end, NONE doesn't consume velocity, other edge effects do
    return GetEdgeEffect() != EdgeEffect::NONE;
}

ScrollResult SwiperPattern::HandleScroll(float offset, int32_t source, NestedState state)
{
    if (IsDisableSwipe()) {
        return { offset, false };
    }

    if (source == SCROLL_FROM_ANIMATION && AnimationRunning()) {
        // deny conflicting animation from child
        return { offset, false };
    }
    // mouse scroll triggers showNext / showPrev instead of updating offset
    if (source == SCROLL_FROM_AXIS) {
        auto targetBfr = targetIndex_;
        (offset > 0) ? ShowPrevious() : ShowNext();
        if (targetBfr == targetIndex_) {
            // unchanged targetIndex_ implies Swiper has reached the edge and the mouse scroll isn't consumed.
            return { offset, true };
        }
        return { 0.0f, false };
    }
    auto parent = parent_.Upgrade();
    if (!parent || !enableNestedScroll_) {
        if (IsOutOfBoundary(offset) && ChildFirst(state)) {
            CloseTheGap(offset);
            return { offset, true };
        }
        UpdateCurrentOffset(offset);
        return { 0.0f, !IsLoop() && GetDistanceToEdge() <= 0.0f };
    }
    return HandleScrollSelfFirst(offset, source, state);
}

ScrollResult SwiperPattern::HandleScrollSelfFirst(float offset, int32_t source, NestedState state)
{
    // priority: self scroll > parent scroll > parent overScroll > self overScroll
    if (IsOutOfBoundary(offset)) {
        CloseTheGap(offset);
        // skip CHECK_NULL, already checked in HandleScroll
        auto parent = parent_.Upgrade();

        // reached edge, pass offset to parent
        auto res = parent->HandleScroll(offset, source, NestedState::CHILD_SCROLL);
        if (res.remain == 0.0f) {
            return { 0.0f, true };
        }
        // parent handle overScroll first
        if (res.reachEdge) {
            res = parent->HandleScroll(res.remain, source, NestedState::CHILD_OVER_SCROLL);
        }

        if (ChildFirst(state)) {
            return { res.remain, true };
        }
        if (res.remain != 0.0f) {
            // self overScroll
            UpdateCurrentOffset(res.remain);
        }
    } else {
        // regular scroll
        UpdateCurrentOffset(offset);
    }
    return { 0.0f, !IsLoop() && GetDistanceToEdge() <= 0.0f };
}

void SwiperPattern::CloseTheGap(float offset)
{
    float distanceToEdge = GetDistanceToEdge();
    if (distanceToEdge > 0.0f) {
        UpdateCurrentOffset(offset > 0 ? distanceToEdge : -distanceToEdge);
    }
}

inline bool SwiperPattern::ChildFirst(NestedState state)
{
    // SELF/CHILD priority: self scroll > child scroll > self overScroll > child overScroll
    return state == NestedState::CHILD_SCROLL // child hasn't reach edge
           || GetEdgeEffect() == EdgeEffect::NONE;
}

void SwiperPattern::DumpAdvanceInfo()
{
    isLastIndicatorFocused_ ? DumpLog::GetInstance().AddDesc("isLastIndicatorFocused:true")
                            : DumpLog::GetInstance().AddDesc("isLastIndicatorFocused:false");
    moveDirection_ ? DumpLog::GetInstance().AddDesc("moveDirection:true")
                   : DumpLog::GetInstance().AddDesc("moveDirection:false");
    indicatorDoingAnimation_ ? DumpLog::GetInstance().AddDesc("indicatorDoingAnimation:true")
                             : DumpLog::GetInstance().AddDesc("indicatorDoingAnimation:false");
    hasVisibleChangeRegistered_ ? DumpLog::GetInstance().AddDesc("hasVisibleChangeRegistered:true")
                                : DumpLog::GetInstance().AddDesc("hasVisibleChangeRegistered:false");
    isVisible_ ? DumpLog::GetInstance().AddDesc("isVisible:true") : DumpLog::GetInstance().AddDesc("isVisible:false");
    isVisibleArea_ ? DumpLog::GetInstance().AddDesc("isVisibleArea:true")
                   : DumpLog::GetInstance().AddDesc("isVisibleArea:false");
    isWindowShow_ ? DumpLog::GetInstance().AddDesc("isWindowShow:true")
                  : DumpLog::GetInstance().AddDesc("isWindowShow:false");
    IsCustomSize_ ? DumpLog::GetInstance().AddDesc("IsCustomSize:true")
                  : DumpLog::GetInstance().AddDesc("IsCustomSize:false");
    indicatorIsBoolean_ ? DumpLog::GetInstance().AddDesc("indicatorIsBoolean:true")
                        : DumpLog::GetInstance().AddDesc("indicatorIsBoolean:false");
    isAtHotRegion_ ? DumpLog::GetInstance().AddDesc("isAtHotRegion:true")
                   : DumpLog::GetInstance().AddDesc("isAtHotRegion:false");
    isDragging_ ? DumpLog::GetInstance().AddDesc("isDragging:true")
                : DumpLog::GetInstance().AddDesc("isDragging:false");
    isTouchDown_ ? DumpLog::GetInstance().AddDesc("isTouchDown:true")
                 : DumpLog::GetInstance().AddDesc("isTouchDown:false");
    preLoop_.has_value() ? DumpLog::GetInstance().AddDesc("preLoop:" + std::to_string(preLoop_.value()))
                         : DumpLog::GetInstance().AddDesc("preLoop:null");
    indicatorId_.has_value() ? DumpLog::GetInstance().AddDesc("indicatorId:" + std::to_string(indicatorId_.value()))
                             : DumpLog::GetInstance().AddDesc("indicatorId:null");
    leftButtonId_.has_value() ? DumpLog::GetInstance().AddDesc("leftButtonId:" + std::to_string(leftButtonId_.value()))
                              : DumpLog::GetInstance().AddDesc("leftButtonId:null");
    rightButtonId_.has_value()
        ? DumpLog::GetInstance().AddDesc("rightButtonId:" + std::to_string(rightButtonId_.value()))
        : DumpLog::GetInstance().AddDesc("rightButtonId:null");
    crossMatchChild_ ? DumpLog::GetInstance().AddDesc("crossMatchChild:true")
                     : DumpLog::GetInstance().AddDesc("crossMatchChild:false");
    uiCastJumpIndex_.has_value()
        ? DumpLog::GetInstance().AddDesc("uiCastJumpIndex:" + std::to_string(uiCastJumpIndex_.value()))
        : DumpLog::GetInstance().AddDesc("uiCastJumpIndex:null");
    jumpIndex_.has_value() ? DumpLog::GetInstance().AddDesc("jumpIndex:" + std::to_string(jumpIndex_.value()))
                           : DumpLog::GetInstance().AddDesc("jumpIndex:null");
    targetIndex_.has_value() ? DumpLog::GetInstance().AddDesc("targetIndex:" + std::to_string(targetIndex_.value()))
                             : DumpLog::GetInstance().AddDesc("targetIndex:null");
    preTargetIndex_.has_value()
        ? DumpLog::GetInstance().AddDesc("preTargetIndex:" + std::to_string(preTargetIndex_.value()))
        : DumpLog::GetInstance().AddDesc("preTargetIndex:null");
    pauseTargetIndex_.has_value()
        ? DumpLog::GetInstance().AddDesc("pauseTargetIndex:" + std::to_string(pauseTargetIndex_.value()))
        : DumpLog::GetInstance().AddDesc("pauseTargetIndex:null");
    velocity_.has_value() ? DumpLog::GetInstance().AddDesc("velocity:" + std::to_string(velocity_.value()))
                          : DumpLog::GetInstance().AddDesc("velocity:null");
    isFinishAnimation_ ? DumpLog::GetInstance().AddDesc("isFinishAnimation:true")
                       : DumpLog::GetInstance().AddDesc("isFinishAnimation:false");
    mainSizeIsMeasured_ ? DumpLog::GetInstance().AddDesc("mainSizeIsMeasured:true")
                        : DumpLog::GetInstance().AddDesc("mainSizeIsMeasured:false");
    isNeedResetPrevMarginAndNextMargin_ ? DumpLog::GetInstance().AddDesc("isNeedResetPrevMarginAndNextMargin:true")
                                        : DumpLog::GetInstance().AddDesc("isNeedResetPrevMarginAndNextMargin:false");
    usePropertyAnimation_ ? DumpLog::GetInstance().AddDesc("usePropertyAnimation:true")
                          : DumpLog::GetInstance().AddDesc("usePropertyAnimation:false");
    isUserFinish_ ? DumpLog::GetInstance().AddDesc("isUserFinish:true")
                  : DumpLog::GetInstance().AddDesc("isUserFinish:false");
    isVoluntarilyClear_ ? DumpLog::GetInstance().AddDesc("isVoluntarilyClear:true")
                        : DumpLog::GetInstance().AddDesc("isVoluntarilyClear:false");
    isIndicatorLongPress_ ? DumpLog::GetInstance().AddDesc("isIndicatorLongPress:true")
                          : DumpLog::GetInstance().AddDesc("isIndicatorLongPress:false");
    stopIndicatorAnimation_ ? DumpLog::GetInstance().AddDesc("stopIndicatorAnimation:true")
                            : DumpLog::GetInstance().AddDesc("stopIndicatorAnimation:false");
    isTouchPad_ ? DumpLog::GetInstance().AddDesc("isTouchPad:true")
                : DumpLog::GetInstance().AddDesc("isTouchPad:false");
    surfaceChangedCallbackId_.has_value()
        ? DumpLog::GetInstance().AddDesc(
              "surfaceChangedCallbackId:" + std::to_string(surfaceChangedCallbackId_.value()))
        : DumpLog::GetInstance().AddDesc("surfaceChangedCallbackId:null");
    if (lastSwiperIndicatorType_.has_value()) {
        switch (lastSwiperIndicatorType_.value()) {
            case SwiperIndicatorType::DOT: {
                DumpLog::GetInstance().AddDesc("SwiperIndicatorType:DOT");
                break;
            }
            case SwiperIndicatorType::DIGIT: {
                DumpLog::GetInstance().AddDesc("SwiperIndicatorType:DIGIT");
                break;
            }
            default: {
                break;
            }
        }
    } else {
        DumpLog::GetInstance().AddDesc("lastSwiperIndicatorType:null");
    }
    DumpLog::GetInstance().AddDesc("currentIndex:" + std::to_string(currentIndex_));
    DumpLog::GetInstance().AddDesc("oldIndex:" + std::to_string(oldIndex_));
    DumpLog::GetInstance().AddDesc("currentOffset:" + std::to_string(currentOffset_));
    DumpLog::GetInstance().AddDesc("fadeOffset:" + std::to_string(fadeOffset_));
    DumpLog::GetInstance().AddDesc("touchBottomRate:" + std::to_string(touchBottomRate_));
    DumpLog::GetInstance().AddDesc("currentIndexOffset:" + std::to_string(currentIndexOffset_));
    DumpLog::GetInstance().AddDesc("gestureSwipeIndex:" + std::to_string(gestureSwipeIndex_));
    DumpLog::GetInstance().AddDesc("currentFirstIndex:" + std::to_string(currentFirstIndex_));
    DumpLog::GetInstance().AddDesc("startMainPos:" + std::to_string(startMainPos_));
    DumpLog::GetInstance().AddDesc("endMainPos:" + std::to_string(endMainPos_));
    DumpLog::GetInstance().AddDesc("contentMainSize:" + std::to_string(contentMainSize_));
    DumpLog::GetInstance().AddDesc("contentCrossSize:" + std::to_string(contentCrossSize_));
    DumpLog::GetInstance().AddDesc("currentDelta:" + std::to_string(currentDelta_));
    DumpLog::GetInstance().AddDesc("propertyAnimationIndex:" + std::to_string(propertyAnimationIndex_));
    DumpLog::GetInstance().AddDesc("mainDeltaSum:" + std::to_string(mainDeltaSum_));
    if (!itemPosition_.empty()) {
        DumpLog::GetInstance().AddDesc("-----------start print itemPosition------------");
        for (auto item : itemPosition_) {
            DumpLog::GetInstance().AddDesc(std::string("id:")
                                               .append(std::to_string(item.first))
                                               .append(",startPos:")
                                               .append(std::to_string(item.second.startPos))
                                               .append(",endPos:" + std::to_string(item.second.endPos)));
        }
        DumpLog::GetInstance().AddDesc("-----------end print itemPosition------------");
    }
    if (!itemPositionInAnimation_.empty()) {
        DumpLog::GetInstance().AddDesc("-----------start print itemPositionInAnimation------------");

        for (auto item : itemPositionInAnimation_) {
            DumpLog::GetInstance().AddDesc(std::string("id:")
                                               .append(std::to_string(item.first))
                                               .append(",startPos:")
                                               .append(std::to_string(item.second.startPos))
                                               .append(",endPos:")
                                               .append(std::to_string(item.second.endPos)));
        }
        DumpLog::GetInstance().AddDesc("-----------end print itemPositionInAnimation------------");
    }
    switch (panDirection_.type) {
        case PanDirection::NONE: {
            DumpLog::GetInstance().AddDesc("PanDirection:NONE");
            break;
        }
        case PanDirection::LEFT: {
            DumpLog::GetInstance().AddDesc("PanDirection:LEFT");
            break;
        }
        case PanDirection::RIGHT: {
            DumpLog::GetInstance().AddDesc("PanDirection:RIGHT");
            break;
        }
        case PanDirection::HORIZONTAL: {
            DumpLog::GetInstance().AddDesc("PanDirection:HORIZONTAL");
            break;
        }
        case PanDirection::UP: {
            DumpLog::GetInstance().AddDesc("PanDirection:UP");
            break;
        }
        case PanDirection::DOWN: {
            DumpLog::GetInstance().AddDesc("PanDirection:DOWN");
            break;
        }
        case PanDirection::VERTICAL: {
            DumpLog::GetInstance().AddDesc("PanDirection:VERTICAL");
            break;
        }
        case PanDirection::ALL: {
            DumpLog::GetInstance().AddDesc("PanDirection:ALL");
            break;
        }
        default: {
            break;
        }
    }
    switch (direction_) {
        case Axis::NONE: {
            DumpLog::GetInstance().AddDesc("Axis:NONE");
            break;
        }
        case Axis::HORIZONTAL: {
            DumpLog::GetInstance().AddDesc("Axis:HORIZONTAL");
            break;
        }
        case Axis::FREE: {
            DumpLog::GetInstance().AddDesc("Axis:FREE");
            break;
        }
        case Axis::VERTICAL: {
            DumpLog::GetInstance().AddDesc("Axis:VERTICAL");
            break;
        }
        default: {
            break;
        }
    }
}

int32_t SwiperPattern::GetLoopIndex(int32_t index, int32_t childrenSize) const
{
    if (childrenSize <= 0) {
        return index;
    }
    auto loopIndex = index;
    while (loopIndex < 0) {
        loopIndex = loopIndex + childrenSize;
    }
    loopIndex %= childrenSize;
    return loopIndex;
}

void SwiperPattern::RegisterScrollingListener(const RefPtr<ScrollingListener> listener)
{
    CHECK_NULL_VOID(listener);
    scrollingListener_.emplace_back(listener);
}

void SwiperPattern::FireAndCleanScrollingListener()
{
    for (auto listener : scrollingListener_) {
        CHECK_NULL_VOID(listener);
        listener->NotifyScrollingEvent();
    }
    scrollingListener_.clear();
}

void SwiperPattern::StopIndicatorAnimation()
{
    AnimationUtils::StopAnimation(indicatorAnimation_);

    if (stopIndicatorAnimationFunc_) {
        stopIndicatorAnimationFunc_();
    }
}

void SwiperPattern::OnCustomContentTransition(int32_t toIndex)
{
    if (!currentProxyInAnimation_ && toIndex == CurrentIndex()) {
        return;
    }

    customAnimationToIndex_ = toIndex;
    indexsInAnimation_.insert(toIndex);
    auto fromIndex = CurrentIndex();
    if (currentProxyInAnimation_) {
        fromIndex = currentProxyInAnimation_->GetToIndex();

        auto swiperEventHub = GetEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(swiperEventHub);
        swiperEventHub->FireChangeEvent(fromIndex);
        swiperEventHub->FireIndicatorChangeEvent(fromIndex);
        swiperEventHub->FireChangeDoneEvent(moveDirection_);

        UpdateCurrentIndex(fromIndex);
        oldIndex_ = fromIndex;

        AnimationCallbackInfo info;
        info.currentOffset = GetCustomPropertyOffset();
        FireAnimationEndEvent(fromIndex, info);

        currentProxyInAnimation_->SetHasOnChanged(true);
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);

    pipelineContext->AddAfterLayoutTask([weak = WeakClaim(this), fromIndex, toIndex]() {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        swiperPattern->TriggerCustomContentTransitionEvent(fromIndex, toIndex);
    });

    MarkDirtyNodeSelf();
}

void SwiperPattern::TriggerCustomContentTransitionEvent(int32_t fromIndex, int32_t toIndex)
{
    CHECK_NULL_VOID(onCustomContentTransition_);

    auto tabContentAnimatedTransition = (*onCustomContentTransition_)(fromIndex, toIndex);
    auto transition = tabContentAnimatedTransition.transition;

    if (!transition) {
        OnCustomAnimationFinish(fromIndex, toIndex, false);
        return;
    }

    auto proxy = AceType::MakeRefPtr<TabContentTransitionProxy>();
    proxy->SetFromIndex(fromIndex);
    proxy->SetToIndex(toIndex);
    proxy->SetFinishTransitionEvent([weak = WeakClaim(this), fromIndex, toIndex](bool hasOnChanged) {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        swiperPattern->OnCustomAnimationFinish(fromIndex, toIndex, hasOnChanged);
    });

    transition(proxy);
    currentProxyInAnimation_ = proxy;

    AnimationCallbackInfo info;
    info.currentOffset = GetCustomPropertyOffset();
    info.targetOffset = GetCustomPropertyOffset();
    FireAnimationStartEvent(fromIndex, toIndex, info);

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    auto timeout = tabContentAnimatedTransition.timeout;
    auto timeoutTask = [weak = AceType::WeakClaim(AceType::RawPtr(proxy)), fromIndex, toIndex] {
        auto transitionProxy = weak.Upgrade();
        CHECK_NULL_VOID(transitionProxy);
        transitionProxy->FinishTransition();
    };

    taskExecutor->PostDelayedTask(timeoutTask, TaskExecutor::TaskType::UI, timeout);
}

void SwiperPattern::OnCustomAnimationFinish(int32_t fromIndex, int32_t toIndex, bool hasOnChanged)
{
    customAnimationToIndex_.reset();
    needUnmountIndexs_.insert(fromIndex);
    indexsInAnimation_.erase(toIndex);

    if (!hasOnChanged) {
        auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateIndexWithoutMeasure(GetLoopIndex(toIndex));
        oldIndex_ = fromIndex;

        AnimationCallbackInfo info;
        info.currentOffset = GetCustomPropertyOffset();
        FireAnimationEndEvent(toIndex, info);
    }

    if (indexsInAnimation_.empty()) {
        currentProxyInAnimation_ = nullptr;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        pipeline->FlushUITasks();
        pipeline->FlushMessages();
    }
}

void SwiperPattern::SetSwiperEventCallback(bool disableSwipe)
{
    CHECK_NULL_VOID(swiperController_);
    auto removeSwiperEventCallback = [weak = WeakClaim(this), disableSwipe]() {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        auto host = swiperPattern->GetHost();
        CHECK_NULL_VOID(host);
        auto hub = host->GetEventHub<EventHub>();
        CHECK_NULL_VOID(hub);
        auto gestureHub = hub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->RemoveTouchEvent(swiperPattern->touchEvent_);
        if (!disableSwipe) {
            gestureHub->RemovePanEvent(swiperPattern->panEvent_);
        }
    };
    swiperController_->SetRemoveSwiperEventCallback(std::move(removeSwiperEventCallback));

    auto addSwiperEventCallback = [weak = WeakClaim(this), disableSwipe]() {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        auto host = swiperPattern->GetHost();
        CHECK_NULL_VOID(host);
        auto hub = host->GetEventHub<EventHub>();
        CHECK_NULL_VOID(hub);
        auto gestureHub = hub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->AddTouchEvent(swiperPattern->touchEvent_);
        if (!disableSwipe) {
            gestureHub->AddPanEvent(swiperPattern->panEvent_, swiperPattern->panDirection_, 1, DEFAULT_PAN_DISTANCE);
        }
    };
    swiperController_->SetAddSwiperEventCallback(std::move(addSwiperEventCallback));
}

void SwiperPattern::UpdateSwiperPanEvent(bool disableSwipe)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    if (!disableSwipe) {
        InitPanEvent(gestureHub);
    } else if (panEvent_) {
        gestureHub->RemovePanEvent(panEvent_);
        panEvent_.Reset();
    }
}

RefPtr<FrameNode> SwiperPattern::GetCurrentFrameNode(int32_t currentIndex) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto currentLayoutWrapper = host->GetChildByIndex(GetLoopIndex(currentIndex));
    CHECK_NULL_RETURN(currentLayoutWrapper, nullptr);
    return currentLayoutWrapper->GetHostNode();
}
} // namespace OHOS::Ace::NG