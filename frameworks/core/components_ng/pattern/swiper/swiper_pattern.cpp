/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "base/error/error_code.h"
#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/perfmonitor/perf_monitor.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/utils.h"
#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/animation/spring_curve.h"
#include "core/common/container_scope.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_layout_algorithm.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/pattern/swiper/swiper_utils.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_arrow_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_node.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/adapter/component_snapshot.h"
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
constexpr float SPRING_DURATION = 600.0f;
constexpr int32_t INDEX_DIFF_TWO = 2;
constexpr int32_t FIRST_CAPTURE_DELAY_TIME = 30;
const std::string SWIPER_DRAG_SCENE = "swiper_drag_scene";
const std::string FADE_PROPERTY_NAME = "fade";
const std::string SPRING_PROPERTY_NAME = "spring";
const std::string INDICATOR_PROPERTY_NAME = "indicator";
const std::string TRANSLATE_PROPERTY_NAME = "translate";
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
    InitSwiperController();
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
    pipeline->RemoveWindowStateChangedCallback(node->GetId());
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
    if (SupportSwiperCustomAnimation()) {
        swiperLayoutAlgorithm->SetNeedUnmountIndexs(needUnmountIndexs_);
        swiperLayoutAlgorithm->SetItemsPositionInAnimation(itemPositionInAnimation_);
    }

    if (jumpIndex_) {
        swiperLayoutAlgorithm->SetJumpIndex(jumpIndex_.value());
    } else if (targetIndex_) {
        swiperLayoutAlgorithm->SetTargetIndex(targetIndex_.value());
    }
    swiperLayoutAlgorithm->SetCurrentIndex(currentIndex_);
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
    swiperLayoutAlgorithm->SetSwipeByGroup(IsSwipeByGroup());
    swiperLayoutAlgorithm->SetRealTotalCount(RealTotalCount());
    swiperLayoutAlgorithm->SetPlaceItemWidth(placeItemWidth_);

    auto swiperPaintProperty = host->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(host, nullptr);
    auto effect = swiperPaintProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING);
    bool canOverScroll = effect == EdgeEffect::SPRING;
    swiperLayoutAlgorithm->SetCanOverScroll(canOverScroll);
    swiperLayoutAlgorithm->SetHasCachedCapture(hasCachedCapture_);
    swiperLayoutAlgorithm->SetIsCaptureReverse(isCaptureReverse_);
    return swiperLayoutAlgorithm;
}

void SwiperPattern::OnIndexChange()
{
    auto totalCount = RealTotalCount();
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

void SwiperPattern::AdjustCurrentIndexOnSwipePage(int32_t index)
{
    auto adjustIndex = SwiperUtils::ComputePageIndex(index, GetDisplayCount());
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateIndexWithoutMeasure(GetLoopIndex(adjustIndex));
    currentIndex_ = GetLoopIndex(adjustIndex);
}

void SwiperPattern::InitCapture()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    bool hasCachedCapture = SwiperUtils::IsStretch(layoutProperty) && layoutProperty->GetLoop().value_or(true) &&
                            !IsSwipeByGroup() && GetDisplayCount() == TotalCount() - 1 &&
                            (Positive(layoutProperty->GetPrevMarginValue(0.0_px).ConvertToPx()) ||
                                Positive(layoutProperty->GetNextMarginValue(0.0_px).ConvertToPx()));
    if (hasCachedCapture) {
        leftCaptureIndex_ = std::nullopt;
        rightCaptureIndex_ = std::nullopt;
    }

    if (!hasCachedCapture_ && hasCachedCapture) {
        // Screenshot nodes need to be added at the forefront of all special nodes to display at the bottom
        uint32_t number = static_cast<uint32_t>(HasIndicatorNode()) + static_cast<uint32_t>(HasLeftButtonNode()) +
                          static_cast<uint32_t>(HasRightButtonNode()) + 1;
        auto leftCaptureNode = FrameNode::GetOrCreateFrameNode(
            V2::SWIPER_LEFT_CAPTURE_ETS_TAG, GetLeftCaptureId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
        leftCaptureNode->MarkModifyDone();
        host->AddChild(leftCaptureNode, -number);

        auto rightCaptureNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_CAPTURE_ETS_TAG, GetRightCaptureId(),
            []() { return AceType::MakeRefPtr<ImagePattern>(); });
        rightCaptureNode->MarkModifyDone();
        host->AddChild(rightCaptureNode, -number);
    }
    if (hasCachedCapture_ && !hasCachedCapture) {
        RemoveAllCaptureNode();
    }
    if (SupportSwiperCustomAnimation() && hasCachedCapture) {
        needUnmountIndexs_.clear();
        itemPositionInAnimation_.clear();
    }
    hasCachedCapture_ = hasCachedCapture;
}

void SwiperPattern::ResetOnForceMeasure()
{
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

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    for (const auto& child : host->GetChildren()) {
        if (child->GetTag() == V2::JS_LAZY_FOR_EACH_ETS_TAG) {
            auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(child);
            CHECK_NULL_VOID(lazyForEachNode);
            lazyForEachNode->SetFlagForGeneratedItem(PROPERTY_UPDATE_MEASURE);
        }
    }
}

void SwiperPattern::UpdateTabBarIndicatorCurve()
{
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
}

void SwiperPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    InitIndicator();
    InitArrow();
    InitCapture();
    SetLazyLoadIsLoop();
    RegisterVisibleAreaChange();
    InitTouchEvent(gestureHub);
    InitHoverMouseEvent();
    StopAndResetSpringAnimation();
    OnLoopChange();
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if ((layoutProperty->GetPropertyChangeFlag() & PROPERTY_UPDATE_MEASURE) == PROPERTY_UPDATE_MEASURE) {
        ResetOnForceMeasure();
    }

    bool disableSwipe = IsDisableSwipe();
    UpdateSwiperPanEvent(disableSwipe);

    auto focusHub = host->GetFocusHub();
    if (focusHub) {
        InitOnKeyEvent(focusHub);
        InitOnFocusInternal(focusHub);
    }

    SetSwiperEventCallback(disableSwipe);
    UpdateTabBarIndicatorCurve();

    if (IsAutoPlay()) {
        StartAutoPlay();
    } else {
        translateTask_.Cancel();
    }

    SetAccessibilityAction();
    placeItemWidth_.reset();

    if (IsSwipeByGroup()) {
        needAdjustIndex_ = true;
    }
}

void SwiperPattern::OnAfterModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    if (!inspectorId.empty()) {
        Recorder::NodeDataCache::Get().PutInt(host, inspectorId, CurrentIndex());
    }
}

void SwiperPattern::BeforeCreateLayoutWrapper()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->GetChildrenUpdated() != -1) {
        if (hasCachedCapture_) {
            InitCapture();
        }
        if (NeedAutoPlay() && !translateTask_) {
            StartAutoPlay();
        }
        host->ChildrenUpdatedFrom(-1);
    }

    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    oldIndex_ = currentIndex_;
    auto userSetCurrentIndex = CurrentIndex();
    auto oldIndex = GetLoopIndex(oldIndex_);
    if (oldChildrenSize_.has_value() && oldChildrenSize_.value() != RealTotalCount()) {
        oldIndex = GetLoopIndex(oldIndex_, oldChildrenSize_.value());
        if (HasIndicatorNode()) {
            StopIndicatorAnimation();
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            auto indicatorNode = DynamicCast<FrameNode>(
                host->GetChildAtIndex(host->GetChildIndexById(GetIndicatorId())));
            if (indicatorNode && indicatorNode->GetTag() == V2::SWIPER_INDICATOR_ETS_TAG) {
                indicatorNode->MarkModifyDone();
                indicatorNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            }
        }
        StartAutoPlay();
    }
    if (userSetCurrentIndex < 0 || userSetCurrentIndex >= RealTotalCount()
        || GetDisplayCount() >= RealTotalCount()) {
        currentIndex_ = 0;
        layoutProperty->UpdateIndexWithoutMeasure(GetLoopIndex(currentIndex_));
    } else {
        if (oldIndex != userSetCurrentIndex) {
            currentIndex_ = userSetCurrentIndex;
            propertyAnimationIndex_ = GetLoopIndex(propertyAnimationIndex_);
        }
    }

    if (IsSwipeByGroup() && needAdjustIndex_) {
        AdjustCurrentIndexOnSwipePage(CurrentIndex());
        needAdjustIndex_ = false;
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
        StopAutoPlay();
        StopTranslateAnimation();
        StopFadeAnimation();
        StopSpringAnimation();
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
    if (oldIndex_ != currentIndex_ && !isInit_ && !IsUseCustomAnimation()) {
        FireWillShowEvent(currentIndex_);
        FireWillHideEvent(oldIndex_);
    }
}

void SwiperPattern::UpdateTargetCapture(bool forceUpdate)
{
    if (itemPosition_.empty()) {
        return;
    }
    auto leftTargetIndex = GetLoopIndex(itemPosition_.rbegin()->first);
    auto rightTargetIndex = GetLoopIndex(itemPosition_.begin()->first);
    if (isCaptureReverse_) {
        leftTargetIndex = GetLoopIndex(itemPosition_.begin()->first);
        rightTargetIndex = GetLoopIndex(itemPosition_.rbegin()->first);
    }
    if (forceUpdate || !leftCaptureIndex_.has_value() || leftCaptureIndex_.value() != leftTargetIndex) {
        CreateCaptureCallback(leftTargetIndex, GetLeftCaptureId(), forceUpdate);
        leftCaptureIndex_ = leftTargetIndex;
    }
    if (forceUpdate || !rightCaptureIndex_.has_value() || rightCaptureIndex_.value() != rightTargetIndex) {
        CreateCaptureCallback(rightTargetIndex, GetRightCaptureId(), forceUpdate);
        rightCaptureIndex_ = rightTargetIndex;
    }
}

void SwiperPattern::CreateCaptureCallback(int32_t targetIndex, int32_t captureId, bool forceUpdate)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto targetNode = AceType::DynamicCast<FrameNode>(host->GetOrCreateChildByIndex(targetIndex));
    CHECK_NULL_VOID(targetNode);
    auto callback = [weak = WeakClaim(this), id = Container::CurrentId(), captureId, targetIndex](
                        std::shared_ptr<Media::PixelMap> pixelMap) {
        ContainerScope scope(id);
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->UpdateCaptureSource(pixelMap, captureId, targetIndex);
    };
    if (forceUpdate) {
        // The size changes caused by layout need to wait for rendering before taking a screenshot
        auto piplineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(piplineContext);
        auto taskExecutor = piplineContext->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostDelayedTask(
            [targetNode, callback]() { ComponentSnapshot::GetNormalCapture(targetNode, std::move(callback)); },
            TaskExecutor::TaskType::UI, FIRST_CAPTURE_DELAY_TIME);
    } else {
        ComponentSnapshot::GetNormalCapture(targetNode, std::move(callback));
    }
}

void SwiperPattern::UpdateCaptureSource(
    std::shared_ptr<Media::PixelMap> pixelMap, int32_t captureId, int32_t targetIndex)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto targetNode = AceType::DynamicCast<FrameNode>(host->GetOrCreateChildByIndex(targetIndex));
    CHECK_NULL_VOID(targetNode);
    auto targetLayoutProperty = targetNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(targetLayoutProperty);
    auto targetMargin = targetLayoutProperty->CreateMargin();
    MarginProperty margin;
    margin.left = CalcLength(targetMargin.left.has_value() ? targetMargin.left.value() : 0.0f);
    margin.right = CalcLength(targetMargin.right.has_value() ? targetMargin.right.value() : 0.0f);
    margin.top = CalcLength(targetMargin.top.has_value() ? targetMargin.top.value() : 0.0f);
    margin.bottom = CalcLength(targetMargin.bottom.has_value() ? targetMargin.bottom.value() : 0.0f);

    auto captureNode = DynamicCast<FrameNode>(host->GetChildAtIndex(host->GetChildIndexById(captureId)));
    CHECK_NULL_VOID(captureNode);
    auto piplineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(piplineContext);
    auto taskExecutor = piplineContext->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [captureNode, pixelMap, margin]() mutable {
            auto imageLayoutProperty = captureNode->GetLayoutProperty<ImageLayoutProperty>();
            CHECK_NULL_VOID(imageLayoutProperty);
            imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(PixelMap::CreatePixelMap(&pixelMap)));
            imageLayoutProperty->UpdateMargin(margin);
            captureNode->MarkModifyDone();
            captureNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        },
        TaskExecutor::TaskType::UI);
}

void SwiperPattern::InitSurfaceChangedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
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
                auto currentIndex =
                    swiper->targetIndex_.has_value() ? swiper->targetIndex_.value() : swiper->currentIndex_;

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
                swiper->jumpIndex_ = currentIndex;
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

void SwiperPattern::AdjustCurrentFocusIndex()
{
    if (GetDisplayCount() <= 1) {
        currentFocusIndex_ = currentIndex_;
        return;
    }

    if (currentFocusIndex_ >= currentIndex_ && currentFocusIndex_ < currentIndex_ + GetDisplayCount()) {
        return;
    }

    currentFocusIndex_ = currentIndex_;
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
    if (SupportSwiperCustomAnimation()) {
        needUnmountIndexs_ = swiperLayoutAlgorithm->GetNeedUnmountIndexs();
        itemPositionInAnimation_ = swiperLayoutAlgorithm->GetItemsPositionInAnimation();
        FireContentDidScrollEvent();
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

        placeItemWidth_ = itemPosition_.begin()->second.endPos - itemPosition_.begin()->second.startPos;
    }
    if (hasCachedCapture_) {
        isCaptureReverse_ = swiperLayoutAlgorithm->GetIsCaptureReverse();
        UpdateTargetCapture(swiperLayoutAlgorithm->GetIsNeedUpdateCapture());
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (!targetIndex_) {
        CheckMarkDirtyNodeForRenderIndicator();
    }

    if (jumpIndex_) {
        isJump = true;
        UpdateCurrentIndex(swiperLayoutAlgorithm->GetCurrentIndex());
        AdjustCurrentFocusIndex();
        auto curChild = dirty->GetOrCreateChildByIndex(GetLoopIndex(currentFocusIndex_));
        if (curChild && IsContentFocused()) {
            auto curChildFrame = curChild->GetHostNode();
            CHECK_NULL_RETURN(curChildFrame, false);
            FlushFocus(curChildFrame);
        }
        currentIndexOffset_ = 0.0f;
        if (isNotInit) {
            OnIndexChange();
        }
        jumpIndex_.reset();
        pauseTargetIndex_.reset();
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
            auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
            auto lastItemIndex = Positive(swiperLayoutProperty->GetNextMarginValue(0.0_px).ConvertToPx())
                                     ? targetIndexValue + GetDisplayCount()
                                     : targetIndexValue + GetDisplayCount() - 1;
            bool isNeedBackwardTranslate = false;
            if (IsLoop() && targetIndexValue < currentIndex_) {
                auto firstItemIndex = Positive(swiperLayoutProperty->GetPrevMarginValue(0.0_px).ConvertToPx())
                                          ? targetIndexValue + TotalCount() - 1
                                          : targetIndexValue + TotalCount();
                isNeedBackwardTranslate = itemPosition_.find(firstItemIndex) != itemPosition_.end();
            }
            bool isNeedPlayTranslateAnimation =
                translateAnimationIsRunning_ ||
                (IsLoop() && itemPosition_.find(lastItemIndex) == itemPosition_.end()) || isNeedBackwardTranslate;
            targetPos += IgnoreBlankOffset(false);
            if (context && !isNeedPlayTranslateAnimation && !SupportSwiperCustomAnimation()) {
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
        } else if (!itemPosition_.empty() && SwiperUtils::IsStretch(layoutProperty)) {
            auto targetPos =
                itemPosition_.begin()->second.startPos +
                (targetIndexValue - itemPosition_.begin()->first) * (placeItemWidth_.value() + GetItemSpace());
            PlayTranslateAnimation(
                currentOffset_, currentOffset_ - targetPos, targetIndexValue, false, velocity_.value_or(0.0f));
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
    oldChildrenSize_ = RealTotalCount();

    if (windowSizeChangeReason_ == WindowSizeChangeReason::ROTATION) {
        StartAutoPlay();
        windowSizeChangeReason_ = WindowSizeChangeReason::UNDEFINED;
    }

    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    return GetEdgeEffect() == EdgeEffect::FADE || paddingProperty != nullptr;
}

float SwiperPattern::IgnoreBlankOffset(bool isJump)
{
    float result = 0.0f;
    if (!isJump && targetIndex_) {
        auto targetIndexValue = IsLoop() ? targetIndex_.value() : GetLoopIndex(targetIndex_.value());
        if (!IsLoop()) {
            if (targetIndexValue == 0 && prevMarginIgnoreBlank_) {
                result += GetPrevMargin();
            }
            if (targetIndexValue == (TotalCount() - GetDisplayCount()) && nextMarginIgnoreBlank_) {
                result -= GetNextMargin();
            }
        }
    }

    if (jumpIndex_) {
        auto targetIndexValue = IsLoop() ? jumpIndex_.value() : GetLoopIndex(jumpIndex_.value());
        if (!IsLoop()) {
            if (targetIndexValue == 0 && prevMarginIgnoreBlank_) {
                result += GetPrevMargin();
            }
            if (targetIndexValue == (TotalCount() - GetDisplayCount()) && nextMarginIgnoreBlank_) {
                result -= GetNextMargin();
            }
        }
    }

    return result;
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_START);
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

void SwiperPattern::HandleSwiperCustomAnimation(float offset)
{
    if (!SupportSwiperCustomAnimation()) {
        return;
    }
    if (itemPosition_.empty()) {
        needUnmountIndexs_.clear();
        itemPositionInAnimation_.clear();
        return;
    }
    if (NearZero(offset)) {
        return;
    }

    if (itemPositionInAnimation_.empty()) {
        for (auto& item : itemPosition_) {
            UpdateItemInfoInCustomAnimation(item.first, item.second.startPos, item.second.endPos);
        }
    }
    indexsInAnimation_.clear();
    CalculateAndUpdateItemInfo(offset);

    SwiperLayoutAlgorithm::PositionMap itemsAnimationFinished;
    for (auto& item : itemPositionInAnimation_) {
        if (indexsInAnimation_.find(item.first) == indexsInAnimation_.end() &&
            needUnmountIndexs_.find(item.first) == needUnmountIndexs_.end()) {
            indexsInAnimation_.insert(item.first);
            needUnmountIndexs_.insert(item.first);
            item.second.startPos += offset;
            item.second.endPos += offset;
            itemsAnimationFinished.insert(item);
        }
    }
    for (auto& item : itemsAnimationFinished) {
        OnSwiperCustomAnimationFinish(item);
    }

    FireSwiperCustomAnimationEvent();
}

void SwiperPattern::CalculateAndUpdateItemInfo(float offset)
{
    auto prevMargin = GetPrevMargin();
    auto nextMargin = GetNextMargin();
    auto visibleSize = CalculateVisibleSize();
    auto itemSpace = GetItemSpace();
    auto isLoop = IsLoop();
    auto displayCount = GetDisplayCount();
    auto swipeByGroup = IsSwipeByGroup();

    for (auto& item : itemPosition_) {
        auto index = item.first;
        auto startPos = item.second.startPos + offset;
        auto endPos = item.second.endPos + offset;
        auto itemPosDiff = endPos - startPos + itemSpace;
        auto pageStartIndex = swipeByGroup ? SwiperUtils::ComputePageIndex(index, displayCount) : index;
        auto pageEndIndex = swipeByGroup ? SwiperUtils::ComputePageEndIndex(index, displayCount) : index;
        auto pageStartPos = swipeByGroup ? startPos - itemPosDiff * (index - pageStartIndex) : startPos;
        auto pageEndPos = swipeByGroup ? endPos + itemPosDiff * (pageEndIndex - index) : endPos;

        if (LessOrEqual(pageEndPos, NearZero(prevMargin) ? 0.0f : - prevMargin - itemSpace)) {
            continue;
        }
        if (GreatOrEqual(pageStartPos, NearZero(nextMargin) ? visibleSize : visibleSize + nextMargin + itemSpace)) {
            continue;
        }

        if (GreatNotEqual(startPos - itemSpace, NearZero(prevMargin) ? 0.0f : - prevMargin - itemSpace) &&
            itemPosition_.find(index - 1) == itemPosition_.end() && (isLoop || index > 0)) {
            pageStartIndex = swipeByGroup ? SwiperUtils::ComputePageIndex(index - 1, displayCount) : index - 1;
        }
        if (LessNotEqual(endPos + itemSpace, NearZero(nextMargin) ? visibleSize :
            visibleSize + nextMargin + itemSpace) && itemPosition_.find(index + 1) == itemPosition_.end() &&
            (isLoop || index < RealTotalCount() - 1)) {
            pageEndIndex = swipeByGroup ? SwiperUtils::ComputePageEndIndex(index + 1, displayCount) : index + 1;
        }
        auto currentIndex = index - 1;
        while (currentIndex >= pageStartIndex && itemPosition_.find(currentIndex) == itemPosition_.end()) {
            UpdateItemInfoInCustomAnimation(currentIndex, startPos - itemPosDiff * (index - currentIndex),
                endPos - itemPosDiff * (index - currentIndex));
            currentIndex--;
        }
        currentIndex = index + 1;
        while (currentIndex <= pageEndIndex && itemPosition_.find(currentIndex) == itemPosition_.end()) {
            UpdateItemInfoInCustomAnimation(currentIndex, startPos + itemPosDiff * (currentIndex - index),
                endPos + itemPosDiff * (currentIndex - index));
            currentIndex++;
        }
        UpdateItemInfoInCustomAnimation(index, startPos, endPos);
    }
}

void SwiperPattern::UpdateItemInfoInCustomAnimation(int32_t index, float startPos, float endPos)
{
    index = GetLoopIndex(index);
    if (IsSwipeByGroup() && index >= RealTotalCount()) {
        return;
    }
    indexsInAnimation_.insert(index);
    needUnmountIndexs_.erase(index);
    auto itemInAnimation = itemPositionInAnimation_.find(index);
    if (itemInAnimation == itemPositionInAnimation_.end()) {
        itemPositionInAnimation_[index] = {startPos, endPos, nullptr};
    } else {
        itemInAnimation->second.startPos = startPos;
        itemInAnimation->second.endPos = endPos;
        if (itemInAnimation->second.task) {
            itemInAnimation->second.task.Cancel();
        }
    }
}

void SwiperPattern::FireSwiperCustomAnimationEvent()
{
    CHECK_NULL_VOID(onSwiperCustomContentTransition_);
    auto transition = onSwiperCustomContentTransition_->transition;
    CHECK_NULL_VOID(transition);

    auto selectedIndex = GetCurrentIndex();
    for (auto& item : itemPositionInAnimation_) {
        if (indexsInAnimation_.find(item.first) == indexsInAnimation_.end()) {
            continue;
        }
        auto offset = Dimension(item.second.startPos, DimensionUnit::PX).ConvertToVp();
        auto mainAxisLength = Dimension(item.second.endPos - item.second.startPos, DimensionUnit::PX).ConvertToVp();
        if (NonPositive(mainAxisLength)) {
            continue;
        }
        auto position = offset / mainAxisLength;
        auto proxy = AceType::MakeRefPtr<SwiperContentTransitionProxy>();
        proxy->SetSelectedIndex(selectedIndex);
        proxy->SetIndex(item.first);
        proxy->SetPosition(position);
        proxy->SetMainAxisLength(mainAxisLength);
        proxy->SetFinishTransitionEvent([weak = WeakClaim(this), index = item.first]() {
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            auto item = swiper->itemPositionInAnimation_.find(index);
            if (item == swiper->itemPositionInAnimation_.end()) {
                return;
            }
            item->second.isFinishAnimation = true;
            swiper->OnSwiperCustomAnimationFinish(*item);
        });
        transition(proxy);
    }
}

void SwiperPattern::FireContentDidScrollEvent()
{
    if (indexsInAnimation_.empty()) {
        return;
    }

    CHECK_NULL_VOID(onContentDidScroll_);
    auto event = *onContentDidScroll_;
    auto selectedIndex = GetCurrentIndex();
    for (auto& item : itemPositionInAnimation_) {
        if (indexsInAnimation_.find(item.first) == indexsInAnimation_.end()) {
            continue;
        }
        auto offset = Dimension(item.second.startPos, DimensionUnit::PX).ConvertToVp();
        auto mainAxisLength = Dimension(item.second.endPos - item.second.startPos, DimensionUnit::PX).ConvertToVp();
        if (NonPositive(mainAxisLength)) {
            continue;
        }
        auto position = offset / mainAxisLength;
        event(selectedIndex, item.first, position, mainAxisLength);
    }
    indexsInAnimation_.clear();
}

void SwiperPattern::OnSwiperCustomAnimationFinish(std::pair<int32_t, SwiperItemInfo> item)
{
    if (needUnmountIndexs_.find(item.first) == needUnmountIndexs_.end()) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    if (item.second.task) {
        item.second.task.Cancel();
    }
    item.second.task.Reset([weak = AceType::WeakClaim(this), index = item.first] {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->needUnmountIndexs_.erase(index);
        swiper->itemPositionInAnimation_.erase(index);
        swiper->MarkDirtyNodeSelf();
    });
    int32_t timeout = 0;
    if (onSwiperCustomContentTransition_ && !item.second.isFinishAnimation) {
        timeout = onSwiperCustomContentTransition_->timeout;
    }
    taskExecutor->PostDelayedTask(item.second.task, TaskExecutor::TaskType::UI, timeout);
}

void SwiperPattern::SwipeToWithoutAnimation(int32_t index)
{
    if (currentIndex_ != index) {
        FireWillShowEvent(index);
        FireWillHideEvent(currentIndex_);
    }
    if (IsVisibleChildrenSizeLessThanSwiper()) {
        return;
    }

    if (usePropertyAnimation_) {
        StopPropertyTranslateAnimation(isFinishAnimation_);
    }

    StopTranslateAnimation();
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
    if (!ContentWillChange(targetIndex)) {
        return;
    }

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

    if (currentIndex_ != targetIndex_.value_or(0)) {
        FireWillShowEvent(targetIndex_.value_or(0));
        FireWillHideEvent(currentIndex_);
    }
    MarkDirtyNodeSelf();
}

int32_t SwiperPattern::CheckTargetIndex(int32_t targetIndex, bool isForceBackward)
{
    if (!IsAutoLinear()) {
        return targetIndex;
    }
    while (GetLoopIndex(targetIndex) != GetLoopIndex(currentIndex_)) {
        auto currentFrameNode = GetCurrentFrameNode(GetLoopIndex(targetIndex));
        CHECK_NULL_RETURN(currentFrameNode, targetIndex);
        auto swiperLayoutProperty = currentFrameNode->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_RETURN(swiperLayoutProperty, targetIndex);
        if (swiperLayoutProperty->GetVisibility().value_or(VisibleType::VISIBLE) != VisibleType::GONE) {
            return targetIndex;
        }
        if (isForceBackward || currentIndex_ < targetIndex) {
            ++targetIndex;
        } else {
            --targetIndex;
        }
        if (!IsLoop() && (targetIndex < 0 || targetIndex >= TotalCount())) {
            return currentIndex_;
        }
    }
    return targetIndex;
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

    StopSpringAnimationAndFlushImmediately();
    StopFadeAnimation();
    StopIndicatorAnimation();
    if (preIndex) {
        isUserFinish_ = false;
        FinishAnimation();
        if (!ContentWillChange(currentIndex_ + 1)) {
            return;
        }
    }
    moveDirection_ = true;

    auto stepItems = IsSwipeByGroup() ? GetDisplayCount() : 1;
    if (isVisible_) {
        targetIndex_ = CheckTargetIndex(currentIndex_ + stepItems);
        preTargetIndex_ = targetIndex_;
        MarkDirtyNodeSelf();
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    } else {
        SwipeToWithoutAnimation(currentIndex_ + stepItems);
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
    StopSpringAnimationAndFlushImmediately();
    StopFadeAnimation();
    StopIndicatorAnimation();

    if (preIndex) {
        isUserFinish_ = false;
        FinishAnimation();
        if (!ContentWillChange(currentIndex_ - 1)) {
            return;
        }
    }
    moveDirection_ = false;

    auto stepItems = IsSwipeByGroup() ? GetDisplayCount() : 1;
    if (isVisible_) {
        targetIndex_ = CheckTargetIndex(currentIndex_ - stepItems);
        preTargetIndex_ = targetIndex_;
        MarkDirtyNodeSelf();
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    } else {
        SwipeToWithoutAnimation(currentIndex_ - stepItems);
    }
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireIndicatorChangeEvent(GetLoopIndex(currentIndex_));
}

void SwiperPattern::ChangeIndex(int32_t index, bool useAnimation)
{
    auto displayCount = GetDisplayCount();
    if (RealTotalCount() <= 0 || displayCount == 0 || index < 0 || index >= RealTotalCount()) {
        return;
    }
    auto itemCount = TotalCount();
    auto loopCount = std::abs(currentIndex_ / itemCount);
    auto targetIndex = currentIndex_ >= 0 ? loopCount * itemCount + index : -(loopCount + 1) * itemCount + index;
    targetIndex = IsSwipeByGroup() ? SwiperUtils::ComputePageIndex(targetIndex, displayCount) : targetIndex;
    if (targetIndex_.has_value() && targetIndex_.value() == targetIndex) {
        return;
    }

    if (useAnimation) {
        SwipeTo(targetIndex);
    } else {
        SwipeToWithoutAnimation(targetIndex);
    }
}

void SwiperPattern::FinishAnimation()
{
    if (translateAnimationIsRunning_) {
        isFinishAnimation_ = true;
        StopTranslateAnimation();
    }
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

void SwiperPattern::PreloadItems(const std::set<int32_t>& indexSet)
{
    std::set<int32_t> validIndexSet;
    auto childrenSize = RealTotalCount();
    auto errorCode = ERROR_CODE_NO_ERROR;
    for (const auto& index : indexSet) {
        if (index < 0 || index >= childrenSize) {
            errorCode = ERROR_CODE_PARAM_INVALID;
            break;
        }

        validIndexSet.emplace(index);
    }

    if (errorCode != ERROR_CODE_PARAM_INVALID) {
        DoPreloadItems(validIndexSet, errorCode);
        return;
    }

    FirePreloadFinishEvent(errorCode);
}

void SwiperPattern::FirePreloadFinishEvent(int32_t errorCode)
{
    if (swiperController_ && swiperController_->GetPreloadFinishCallback()) {
        auto preloadFinishCallback = swiperController_->GetPreloadFinishCallback();
        swiperController_->SetPreloadFinishCallback(nullptr);
        preloadFinishCallback(errorCode);
    }
}

void SwiperPattern::DoPreloadItems(const std::set<int32_t>& indexSet, int32_t errorCode)
{
    if (indexSet.empty()) {
        FirePreloadFinishEvent(ERROR_CODE_PARAM_INVALID);
        return;
    }

    auto preloadTask = [weak = WeakClaim(this), indexSet, errorCode]() {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        auto host = swiperPattern->GetHost();
        CHECK_NULL_VOID(host);
        const auto& children = host->GetChildren();
        for (const auto& child : children) {
            if (child->GetTag() != V2::JS_FOR_EACH_ETS_TAG && child->GetTag() != V2::JS_LAZY_FOR_EACH_ETS_TAG) {
                continue;
            }

            auto forEachNode = AceType::DynamicCast<ForEachNode>(child);
            auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(child);
            for (auto index : indexSet) {
                if (forEachNode && forEachNode->GetChildAtIndex(index)) {
                    forEachNode->GetChildAtIndex(index)->Build(nullptr);
                    continue;
                }

                if (lazyForEachNode) {
                    lazyForEachNode->GetFrameChildByIndex(index, true);
                }
            }
        }

        swiperPattern->FirePreloadFinishEvent(errorCode);
    };
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(preloadTask, TaskExecutor::TaskType::UI);
}

void SwiperPattern::OnTranslateAnimationFinish()
{
    if (!translateAnimationIsRunning_) {
        return;
    }
    translateAnimationIsRunning_ = false;
    OnTranslateFinish(propertyAnimationIndex_, false, isFinishAnimation_);
}

void SwiperPattern::StopTranslateAnimation()
{
    if (translateAnimationIsRunning_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        translateAnimationIsRunning_ = false;

        if (NearZero(translateAnimationEndPos_ - currentOffset_)) {
            AnimationUtils::StopAnimation(translateAnimation_);
            targetIndex_.reset();
        } else {
            AnimationOption option;
            option.SetCurve(Curves::LINEAR);
            option.SetDuration(0);
            translateAnimation_ = AnimationUtils::StartAnimation(
                option, [host, weak = WeakClaim(this)]() {
                    auto swiper = weak.Upgrade();
                    CHECK_NULL_VOID(swiper);
                    host->UpdateAnimatablePropertyFloat(TRANSLATE_PROPERTY_NAME, swiper->currentOffset_);
                });
            }

        OnTranslateFinish(propertyAnimationIndex_, false, isFinishAnimation_, true);
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
            auto swiperNode = swiper->GetHost();
            CHECK_NULL_VOID(swiperNode);
            TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper ShowNext, id:%{public}d", swiperNode->GetId());
            swiper->ShowNext();
        }
    });

    swiperController_->SetShowPrevImpl([weak = WeakClaim(this)]() {
        auto swiper = weak.Upgrade();
        if (swiper) {
            auto swiperNode = swiper->GetHost();
            CHECK_NULL_VOID(swiperNode);
            TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper SetShowPrevImpl, id:%{public}d", swiperNode->GetId());
            swiper->ShowPrevious();
        }
    });

    swiperController_->SetChangeIndexImpl([weak = WeakClaim(this)](int32_t index, bool useAnimation) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->ChangeIndex(index, useAnimation);
        }
    });

    swiperController_->SetFinishImpl([weak = WeakClaim(this)]() {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->FinishAnimation();
        }
    });

    swiperController_->SetPreloadItemsImpl([weak = WeakClaim(this)](const std::set<int32_t>& indexSet) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->PreloadItems(indexSet);
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

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->SetIndicatorInteractive(isIndicatorInteractive_);

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
        pattern->InitIndexCanChangeMap();
        if (pattern) {
            TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper drag start. SourceTool: %{public}d", info.GetSourceTool());
            if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
                return;
            }
            pattern->FireAndCleanScrollingListener();
            pattern->HandleDragStart(info);
            // notify scrollStart upwards
            pattern->NotifyParentScrollStart(pattern->direction_ == Axis::HORIZONTAL ? info.GetGlobalLocation().GetX()
                                                                                     : info.GetGlobalLocation().GetY());
        }
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (!pattern->CheckSwiperPanEvent(info)) {
            return;
        }
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
        if (!pattern->CheckSwiperPanEvent(info)) {
            pattern->HandleDragEnd(0.0);
            return;
        }
        if (pattern) {
            TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper drag end. Velocity: %{public}f px/s, SourceTool: %{public}d",
                info.GetMainVelocity(), info.GetSourceTool());
            if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
                return;
            }
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

    AddPanEvent(gestureHub, std::move(actionStartTask), std::move(actionUpdateTask),
        std::move(actionEndTask), std::move(actionCancelTask));
}

void SwiperPattern::AddPanEvent(const RefPtr<GestureEventHub>& gestureHub, GestureEventFunc&& actionStart,
    GestureEventFunc&& actionUpdate, GestureEventFunc&& actionEnd, GestureEventNoParameter&& actionCancel)
{
    if (GetDirection() == Axis::VERTICAL) {
        panDirection_.type = PanDirection::VERTICAL;
    } else {
        panDirection_.type = PanDirection::HORIZONTAL;
    }
    if (panEvent_) {
        gestureHub->RemovePanEvent(panEvent_);
    }

    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStart), std::move(actionUpdate), std::move(actionEnd), std::move(actionCancel));
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

bool SwiperPattern::IsContentFocused()
{
    RefPtr<FocusHub> indicatorNode = GetFocusHubChild(V2::SWIPER_INDICATOR_ETS_TAG);
    RefPtr<FocusHub> rightArrowNode = GetFocusHubChild(V2::SWIPER_RIGHT_ARROW_ETS_TAG);
    RefPtr<FocusHub> leftArrowNode = GetFocusHubChild(V2::SWIPER_LEFT_ARROW_ETS_TAG);

    return !((indicatorNode && indicatorNode->IsCurrentFocus()) ||
             (rightArrowNode && rightArrowNode->IsCurrentFocus()) ||
             (leftArrowNode && leftArrowNode->IsCurrentFocus()));
}

bool SwiperPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if ((GetDirection() == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_LEFT) ||
        (GetDirection() == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_UP)) {
        auto onlyFlushFocus = IsContentFocused() && GetDisplayCount() > 1 && currentFocusIndex_ > currentIndex_;
        if (onlyFlushFocus) {
            currentFocusIndex_ = IsLoop() ? currentFocusIndex_ - 1 :
                                            std::clamp(currentFocusIndex_ - 1, 0, TotalCount() - 1);
            FlushFocus(GetCurrentFrameNode(currentFocusIndex_));
        } else {
            ShowPrevious();
            currentFocusIndex_ = IsLoop() ? currentFocusIndex_ - 1 :
                                            std::clamp(currentFocusIndex_ - 1, 0, TotalCount() - 1);
        }

        return true;
    }
    if ((GetDirection() == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_RIGHT) ||
        (GetDirection() == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_DOWN)) {
        auto onlyFlushFocus =
            IsContentFocused() && GetDisplayCount() > 1 && currentFocusIndex_ < currentIndex_ + GetDisplayCount() - 1;
        if (onlyFlushFocus) {
            currentFocusIndex_ = IsLoop() ? currentFocusIndex_ + 1 :
                                            std::clamp(currentFocusIndex_ + 1, 0, TotalCount() - 1);
            FlushFocus(GetCurrentFrameNode(currentFocusIndex_));
        } else {
            ShowNext();
            currentFocusIndex_ = IsLoop() ? currentFocusIndex_ + 1 :
                                            std::clamp(currentFocusIndex_ + 1, 0, TotalCount() - 1);
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
    if (NeedAutoPlay() && !translateAnimationIsRunning_ && !usePropertyAnimation_) {
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
        MarkDirtyNodeSelf();
        return;
    }
    if (!IsLoop() && (isDragging_ || childScrolling_)) {
        // handle edge effects
        if (CheckOverScroll(offset)) {
            return;
        }
    }
    if (!IsLoop() && GetEdgeEffect() != EdgeEffect::SPRING) {
        if (IsOutOfStart(offset)) {
            offset = - itemPosition_.begin()->second.startPos;
        } else if (IsOutOfEnd(offset)) {
            offset = CalculateVisibleSize() - itemPosition_.rbegin()->second.endPos;
        }
    }
    currentDelta_ = currentDelta_ - offset;
    currentIndexOffset_ += offset;
    if (isDragging_ || childScrolling_) {
        AnimationCallbackInfo callbackInfo;
        callbackInfo.currentOffset =
            GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
        FireGestureSwipeEvent(GetLoopIndex(gestureSwipeIndex_), callbackInfo);
    }
    HandleSwiperCustomAnimation(offset);
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
                auto realOffset = IsOutOfStart(offset) ? - itemPosition_.begin()->second.startPos :
                    CalculateVisibleSize() - itemPosition_.rbegin()->second.endPos;
                currentDelta_ = currentDelta_ - realOffset;
                HandleSwiperCustomAnimation(realOffset);
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
    HandleSwiperCustomAnimation(friction * offset);
    MarkDirtyNodeSelf();
    return true;
}

bool SwiperPattern::FadeOverScroll(float offset)
{
    if (IsOutOfBoundary(fadeOffset_ + offset)) {
        auto onlyUpdateFadeOffset = (itemPosition_.begin()->first == 0 && offset < 0.0f) ||
                               (itemPosition_.rbegin()->first == TotalCount() - 1 && offset > 0.0f);
        if (!IsVisibleChildrenSizeLessThanSwiper() && !onlyUpdateFadeOffset) {
            auto realOffset = IsOutOfStart(offset) ? - itemPosition_.begin()->second.startPos :
                CalculateVisibleSize() - itemPosition_.rbegin()->second.endPos;
            currentDelta_ = currentDelta_ - realOffset;
            HandleSwiperCustomAnimation(realOffset);
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
    if (followTouchBottom) {
        if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT) {
            touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
        } else if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
            touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
        }
        return;
    }
    bool leftReleaseTouchBottom = (commTouchBottom && (currentIndex == 0 && gestureState_ ==
        GestureState::GESTURE_STATE_RELEASE_LEFT));
    bool rightReleaseTouchBottom = ((currentFirstIndex == 0) && (currentIndex == TotalCount() - 1) &&
                                    gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT);
    if (leftReleaseTouchBottom || rightReleaseTouchBottom) {
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

void SwiperPattern::CalculateGestureState(float additionalOffset, float currentTurnPageRate, int32_t preFirstIndex)
{
    // Keep follow hand
    if ((preFirstIndex == 0 && currentFirstIndex_ == TotalCount() - 1) ||
        (preFirstIndex == TotalCount() - 1 && currentFirstIndex_ == 0)) {
        needTurn_ = true;
    }

    if (GreatNotEqual(additionalOffset, 0.0f)) {
        gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
        needTurn_ = false;
    } else if (LessNotEqual(additionalOffset, 0.0f)) {
        gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
        needTurn_ = false;
    } else if (GetLoopIndex(currentFirstIndex_) >= GetLoopIndex(currentIndex_)) {
        gestureState_ = needTurn_ ? GestureState::GESTURE_STATE_FOLLOW_LEFT : GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    } else if (GetLoopIndex(currentFirstIndex_) < GetLoopIndex(currentIndex_)) {
        gestureState_ = needTurn_ ? GestureState::GESTURE_STATE_FOLLOW_RIGHT : GestureState::GESTURE_STATE_FOLLOW_LEFT;
    }
    return;
}

void SwiperPattern::UpdateNextValidIndex()
{
    // item may be invalid in auto linear scene, mark next valid item
    if (IsAutoLinear()) {
        currentFirstIndex_ = CheckTargetIndex(currentFirstIndex_, true);
        nextValidIndex_ = GetLoopIndex(CheckTargetIndex(currentFirstIndex_ + 1, true));
    } else {
        nextValidIndex_ = -1;
    }
}

void SwiperPattern::CheckMarkDirtyNodeForRenderIndicator(float additionalOffset)
{
    if (!indicatorId_.has_value()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto child = DynamicCast<FrameNode>(host->GetChildAtIndex(host->GetChildIndexById(GetIndicatorId())));
    if (!child || child->GetTag() != V2::SWIPER_INDICATOR_ETS_TAG) {
        return;
    }

    int32_t preFirstIndex = currentFirstIndex_;
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

    UpdateNextValidIndex();
    currentFirstIndex_ = GetLoopIndex(currentFirstIndex_);
    CalculateGestureState(additionalOffset, currentTurnPageRate, preFirstIndex);
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
        targetIndex_ = CheckTargetIndex(ComputeNextIndexByVelocity(velocity));
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

    StopIndicatorAnimation(true);
    if (usePropertyAnimation_) {
        StopPropertyTranslateAnimation(isFinishAnimation_);
    }

    indicatorDoingAnimation_ = false;
    // Stop translate animation when touch down.
    if (translateAnimationIsRunning_) {
        StopTranslateAnimation();
    }

    AnimationUtils::PauseAnimation(springAnimation_);
    if (springAnimationIsRunning_) {
        isTouchDownSpringAnimation_ = true;
        springAnimationIsRunning_ = false;
    }

    AnimationUtils::PauseAnimation(fadeAnimation_);
    if (fadeAnimationIsRunning_) {
        fadeAnimationIsRunning_ = false;
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

    if (!fadeAnimationIsRunning_) {
        fadeAnimationIsRunning_ = true;
        AnimationUtils::ResumeAnimation(fadeAnimation_);
    }

    if (!isDragging_) {
        StartAutoPlay();
    }
}

void SwiperPattern::HandleDragStart(const GestureEvent& info)
{
    if (!hasTabsAncestor_) {
        PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_SWIPER_SCROLL, PerfActionType::FIRST_MOVE, "");
    }
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

    gestureSwipeIndex_ = currentIndex_;
    isDragging_ = true;
    isTouchDown_ = true;
    mainDeltaSum_ = 0.0f;
    // in drag process, close lazy feature.
    SetLazyLoadFeature(false);
    StopFadeAnimation();
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
    auto velocity = info.GetMainVelocity();
    UpdateDragFRCSceneInfo(velocity, SceneStatus::RUNNING);
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::TOUCHPAD) {
        isTouchPad_ = true;
    }
    auto mainSize = CalculateVisibleSize();
    ProcessDelta(mainDelta, mainSize, mainDeltaSum_);
    mainDeltaSum_ += mainDelta;

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

    HandleScroll(static_cast<float>(mainDelta), SCROLL_FROM_UPDATE, NestedState::GESTURE, velocity);
    UpdateItemRenderGroup(true);
    isTouchPad_ = false;
}

void SwiperPattern::HandleDragEnd(double dragVelocity)
{
    if (!hasTabsAncestor_) {
        PerfMonitor::GetPerfMonitor()->End(PerfConstants::APP_SWIPER_SCROLL, false);
    }
    isTouchDown_ = false;
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

    if (CheckDragOutOfBoundary(dragVelocity)) {
        return;
    }

    // nested and reached end, need to pass velocity to parent scrollable
    auto parent = GetNestedScrollParent();
    if (!IsLoop() && parent && NearZero(GetDistanceToEdge())) {
        parent->HandleScrollVelocity(dragVelocity);
        StartAutoPlay();
    } else {
        UpdateAnimationProperty(static_cast<float>(dragVelocity));
        NotifyParentScrollEnd();
    }
    if (pipeline) {
        pipeline->FlushUITasks();
    }

    isDragging_ = false;

    if (currentIndex_ != pauseTargetIndex_.value_or(0)) {
        FireWillShowEvent(pauseTargetIndex_.value_or(0));
        FireWillHideEvent(currentIndex_);
    }
}

void SwiperPattern::UpdateCurrentIndex(int32_t index)
{
    currentIndex_ = index;
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateIndexWithoutMeasure(GetLoopIndex(currentIndex_));
}

int32_t SwiperPattern::ComputeSwipePageNextIndex(float velocity, bool onlyDistance) const
{
    auto swiperWidth = CalculateVisibleSize();
    if (LessOrEqual(swiperWidth, 0)) {
        return currentIndex_;
    }

    auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
    auto firstIndex = firstItemInfoInVisibleArea.first;
    auto displayCount = GetDisplayCount();
    auto endIndex = SwiperUtils::ComputePageEndIndex(firstIndex, displayCount);
    auto iter = itemPosition_.find(endIndex);
    if (iter == itemPosition_.end()) {
        return currentIndex_;
    }

    auto dragDistance = iter->second.endPos;
    auto dragForward = currentIndex_ > firstIndex;
    auto dragThresholdFlag = dragForward ? dragDistance > swiperWidth / 2 : dragDistance < swiperWidth / 2;
    auto nextIndex = currentIndex_;
    if (dragThresholdFlag) {
        nextIndex = dragForward ? currentIndex_ - displayCount : currentIndex_ + displayCount;
    }

    if (!onlyDistance && std::abs(velocity) > NEW_MIN_TURN_PAGE_VELOCITY && velocity != 0.0f) {
        auto direction = GreatNotEqual(velocity, 0.0f);
        if (dragForward != direction || !dragThresholdFlag) {
            nextIndex = velocity > 0.0f ? nextIndex - displayCount : nextIndex + displayCount;
        }
    }

    if (!IsAutoLinear() && nextIndex > currentIndex_ + displayCount) {
        nextIndex = currentIndex_ + displayCount;
    }

    if (!IsLoop()) {
        nextIndex = std::clamp(nextIndex, 0, std::max(0, TotalCount() - displayCount));
    }

    return nextIndex;
}

int32_t SwiperPattern::ComputeNextIndexInSinglePage(float velocity, bool onlyDistance) const
{
    auto swiperWidth = CalculateVisibleSize();
    if (LessOrEqual(swiperWidth, 0)) {
        return currentIndex_;
    }
    // if direction is true, expected index to decrease by 1
    bool direction = Positive(velocity);
    bool overTurnPageVelocity =
        !onlyDistance && (std::abs(velocity) > (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)
                                                       ? NEW_MIN_TURN_PAGE_VELOCITY
                                                       : MIN_TURN_PAGE_VELOCITY));
    auto iter = itemPosition_.find(currentIndex_);
    if (iter == itemPosition_.end() || overTurnPageVelocity) {
        return direction ? currentIndex_ - 1 : currentIndex_ + 1;
    }
    if (-iter->second.startPos > swiperWidth / 2) {
        return currentIndex_ + 1;
    }
    if (iter->second.startPos > swiperWidth / 2) {
        return currentIndex_ - 1;
    }
    return currentIndex_;
}

int32_t SwiperPattern::ComputeNextIndexByVelocity(float velocity, bool onlyDistance) const
{
    if (IsSwipeByGroup()) {
        return ComputeSwipePageNextIndex(velocity, onlyDistance);
    }

    auto nextIndex = currentIndex_;
    auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
    auto firstItemLength = firstItemInfoInVisibleArea.second.endPos - firstItemInfoInVisibleArea.second.startPos;
    if (LessOrEqual(firstItemLength, 0)) {
        return nextIndex;
    }

    auto firstIndex = firstItemInfoInVisibleArea.first;
    auto dragDistance = firstItemInfoInVisibleArea.second.endPos;
    if (firstIndex == currentIndex_ && firstItemInfoInVisibleArea.second.startPos > 0) {
        firstIndex--;
        dragDistance = firstItemInfoInVisibleArea.second.startPos;
    }
    auto direction = GreatNotEqual(velocity, 0.0);
    auto dragThresholdFlag =
        direction ? dragDistance > firstItemLength / 2 : firstItemInfoInVisibleArea.second.endPos < firstItemLength / 2;
    auto turnVelocity = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) ? NEW_MIN_TURN_PAGE_VELOCITY
                                                                                           : MIN_TURN_PAGE_VELOCITY;
    if ((!onlyDistance && std::abs(velocity) > turnVelocity) || dragThresholdFlag) {
        nextIndex = direction ? firstIndex : firstItemInfoInVisibleArea.first + 1;
    } else {
        nextIndex = direction ? firstIndex + 1 : firstItemInfoInVisibleArea.first;
    }

    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    // don't run this in nested scroll. Parallel nested scroll can deviate > 1 page from currentIndex_
    if (!childScrolling_ && SwiperUtils::IsStretch(props) && GetDisplayCount() == 1) {
        nextIndex = ComputeNextIndexInSinglePage(velocity, onlyDistance);
    }

    if (!IsAutoLinear() && nextIndex > currentIndex_ + GetDisplayCount()) {
        nextIndex = currentIndex_ + GetDisplayCount();
    }

    if (!IsLoop()) {
        nextIndex = std::clamp(nextIndex, 0, std::max(0, TotalCount() - GetDisplayCount()));
    }
    return nextIndex;
}

bool SwiperPattern::NeedStartNewAnimation(const OffsetF& offset) const
{
    if (itemPositionInAnimation_.empty()) {
        return true;
    }

    for (const auto& animationItem : itemPositionInAnimation_) {
        auto iter = itemPosition_.find(animationItem.first);
        if (iter == itemPosition_.end()) {
            return true;
        }
        if ((animationItem.second.node && animationItem.second.finalOffset != offset) ||
            !NearEqual(animationItem.second.startPos, iter->second.startPos) ||
            !NearEqual(animationItem.second.endPos, iter->second.endPos)) {
            return true;
        }
    }

    return false;
}

void SwiperPattern::UpdateCurrentFocus()
{
    do {
        auto curChildFrame = GetCurrentFrameNode(currentIndex_);
        if (!curChildFrame) {
            break;
        }
        FlushFocus(curChildFrame);
        currentFocusIndex_ = currentIndex_;
    } while (0);
}

bool SwiperPattern::CheckDragOutOfBoundary(double dragVelocity)
{
    if (IsLoop()) {
        return false;
    }

    auto edgeEffect = GetEdgeEffect();
    // edge effect is NONE and reached boundary
    bool noneOutOfBoundary = (itemPosition_.begin()->first == 0 || itemPosition_.rbegin()->first == TotalCount() - 1) &&
                             NearZero(GetDistanceToEdge()) && edgeEffect == EdgeEffect::NONE;
    if (IsOutOfBoundary() || !NearZero(fadeOffset_) || noneOutOfBoundary) {
        isDragging_ = false;

        if (edgeEffect == EdgeEffect::SPRING) {
            PlaySpringAnimation(dragVelocity);
            return true;
        }

        if (edgeEffect == EdgeEffect::FADE) {
            PlayFadeAnimation();
            return true;
        }

        auto nextIndex = ComputeNextIndexByVelocity(static_cast<float>(dragVelocity), true);
        if (currentIndex_ != nextIndex) {
            UpdateCurrentIndex(nextIndex);
            UpdateCurrentFocus();
            OnIndexChange();
            oldIndex_ = currentIndex_;
        }

        if (edgeEffect == EdgeEffect::NONE) {
            auto parent = GetNestedScrollParent();
            if (parent) {
                parent->HandleScrollVelocity(dragVelocity);
            }
            StartAutoPlay();
            UpdateItemRenderGroup(false);
            return true;
        }
    }

    return false;
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
        if (!NeedStartNewAnimation(offset)) {
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
    auto finishCallback = [weak = WeakClaim(this), offset]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
#ifdef OHOS_PLATFORM
        ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
#endif
        if (!swiper->hasTabsAncestor_) {
            PerfMonitor::GetPerfMonitor()->End(PerfConstants::APP_SWIPER_FLING, false);
        }
        swiper->targetIndex_.reset();
        swiper->OnPropertyTranslateAnimationFinish(offset);
    };
    // initial translate info.
    for (auto& item : itemPosition_) {
        auto frameNode = item.second.node;
        if (frameNode) {
            frameNode->GetRenderContext()->UpdateTranslateInXY(item.second.finalOffset);
        }
    }
    if (IsCaptureNodeValid()) {
        GetLeftCaptureNode()->GetRenderContext()->UpdateTranslateInXY(captureFinalOffset_);
        GetRightCaptureNode()->GetRenderContext()->UpdateTranslateInXY(captureFinalOffset_);
    }
    // property callback will call immediately.
    auto propertyUpdateCallback = [swiper = WeakClaim(this), offset]() {
        auto swiperPattern = swiper.Upgrade();
        if (!swiperPattern) {
            return;
        }
#ifdef OHOS_PLATFORM
        ResSchedReport::GetInstance().ResSchedDataReport("slide_on");
#endif
        if (!swiperPattern->hasTabsAncestor_) {
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_SWIPER_FLING, PerfActionType::FIRST_MOVE, "");
        }
        for (auto& item : swiperPattern->itemPosition_) {
            auto frameNode = item.second.node;
            if (frameNode) {
                frameNode->GetRenderContext()->UpdateTranslateInXY(offset);
                item.second.finalOffset = offset;
            }
        }
        swiperPattern->itemPositionInAnimation_ = swiperPattern->itemPosition_;
        if (swiperPattern->IsCaptureNodeValid()) {
            swiperPattern->GetLeftCaptureNode()->GetRenderContext()->UpdateTranslateInXY(offset);
            swiperPattern->GetRightCaptureNode()->GetRenderContext()->UpdateTranslateInXY(offset);
            swiperPattern->captureFinalOffset_ = offset;
        }
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
        item.second.finalOffset = OffsetF();
    }
    itemPositionInAnimation_.clear();
    if (IsCaptureNodeValid()) {
        GetLeftCaptureNode()->GetRenderContext()->UpdateTranslateInXY(OffsetF());
        GetRightCaptureNode()->GetRenderContext()->UpdateTranslateInXY(OffsetF());
        captureFinalOffset_ = OffsetF();
    }
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
        if (swiper->IsCaptureNodeValid()) {
            swiper->GetLeftCaptureNode()->GetRenderContext()->CancelTranslateXYAnimation();
            swiper->GetRightCaptureNode()->GetRenderContext()->CancelTranslateXYAnimation();
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
        item.second.finalOffset = OffsetF();
    }
    itemPositionInAnimation_.clear();
    if (IsCaptureNodeValid()) {
        GetLeftCaptureNode()->GetRenderContext()->UpdateTranslateInXY(OffsetF());
        GetRightCaptureNode()->GetRenderContext()->UpdateTranslateInXY(OffsetF());
        captureFinalOffset_ = OffsetF();
    }
    if (!isBeforeCreateLayoutWrapper) {
        UpdateOffsetAfterPropertyAnimation(currentOffset.GetMainOffset(GetDirection()));
    }
    OnTranslateFinish(propertyAnimationIndex_, false, isFinishAnimation, true);
}

RefPtr<Curve> SwiperPattern::GetCurveIncludeMotion()
{
    auto curve = GetCurve();
    auto container = Container::Current();
    bool isLauncherFeature = container ? container->IsLauncherContainer() : false;

    if (isLauncherFeature) {
        finishCallbackType_ = FinishCallbackType::LOGICALLY;
    }

    if (curve) {
        if (InstanceOf<SpringCurve>(curve)) {
            auto springCurve = DynamicCast<SpringCurve>(curve);
            // check velocity to judge if this current velocity.
            if (springCurve->GetCurrentVelocity() < 0) {
                return AceType::MakeRefPtr<SpringCurve>(
                    motionVelocity_, springCurve->GetMass(), springCurve->GetStiffness(), springCurve->GetDamping());
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
    if (translateAnimationIsRunning_) {
        return;
    }
    if (NearZero(endPos - startPos)) {
        OnAnimationTranslateZero(nextIndex, restartAutoPlay);
        return;
    }

    if (indicatorId_.has_value()) {
        CheckMarkDirtyNodeForRenderIndicator(endPos - startPos);
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto weak = AceType::WeakClaim(this);
    host->CreateAnimatablePropertyFloat(TRANSLATE_PROPERTY_NAME, 0, [weak](float value) {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->UpdateCurrentOffset(static_cast<float>(value - swiper->currentOffset_));
    });

    AnimationOption option;
    motionVelocity_ = velocity / (endPos - startPos);
    option.SetCurve(GetCurveIncludeMotion());
    option.SetDuration(GetDuration());

    host->UpdateAnimatablePropertyFloat(TRANSLATE_PROPERTY_NAME, startPos);
    translateAnimationIsRunning_ = true;
    propertyAnimationIndex_ = nextIndex;
    translateAnimationEndPos_ = endPos;
    translateAnimation_ = AnimationUtils::StartAnimation(
        option, [host, weak, startPos, endPos, nextIndex, velocity]() {
            host->UpdateAnimatablePropertyFloat(TRANSLATE_PROPERTY_NAME, endPos);
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            AnimationCallbackInfo info;
            info.velocity = Dimension(velocity, DimensionUnit::PX).ConvertToVp();
            info.currentOffset = swiper->GetCustomPropertyOffset() +
                                 Dimension(swiper->currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
            info.targetOffset =
                swiper->GetCustomPropertyOffset() + Dimension(startPos - endPos, DimensionUnit::PX).ConvertToVp();
            swiper->FireAnimationStartEvent(
                swiper->GetLoopIndex(swiper->currentIndex_), swiper->GetLoopIndex(nextIndex), info);
            swiper->FireAndCleanScrollingListener();
        },
        [weak, nextIndex, restartAutoPlay]() {
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            swiper->targetIndex_.reset();
            swiper->OnTranslateAnimationFinish();
        });

    SetLazyLoadFeature(true);
    UpdateItemRenderGroup(true);
}

void SwiperPattern::OnSpringAnimationStart(float velocity)
{
    AnimationCallbackInfo info;
    info.velocity = Dimension(velocity, DimensionUnit::PX).ConvertToVp();
    info.currentOffset = GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();

    nextIndex_ = ComputeNextIndexByVelocity(velocity, true);
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
        UpdateCurrentFocus();
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
        if (swiper && swiper->GetHost() && !swiper->isTouchDown_) {
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
    auto leading = currentIndexOffset_ + mainSize - itemPosition_.rbegin()->second.endPos;
    auto trailing = currentIndexOffset_ - itemPosition_.begin()->second.startPos;
    ExtentPair extentPair = ExtentPair(leading, trailing);

    host->CreateAnimatablePropertyFloat(SPRING_PROPERTY_NAME, 0, [weak = AceType::WeakClaim(this)](float position) {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        if (!swiper->isTouchDown_) {
            swiper->UpdateCurrentOffset(static_cast<float>(position) - swiper->currentIndexOffset_);
        }
    }, PropertyUnit::PIXEL_POSITION);

    host->UpdateAnimatablePropertyFloat(SPRING_PROPERTY_NAME, currentIndexOffset_);
    auto delta = currentIndexOffset_ < 0.0f ? extentPair.Leading() : extentPair.Trailing();
    if (IsVisibleChildrenSizeLessThanSwiper()) {
        delta = extentPair.Trailing();
    }

    // spring curve: (velocity: 0.0, mass: 1.0, stiffness: 228.0, damping: 30.0)
    auto springCurve = MakeRefPtr<SpringCurve>(0.0f, 1.0f, 228.0f, 30.0f);
    AnimationOption option;
    option.SetCurve(springCurve);
    option.SetDuration(SPRING_DURATION);

    nextIndex_ = currentIndex_;
    springAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this), dragVelocity, host, delta]() {
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_LIST_FLING, PerfActionType::FIRST_MOVE, "");
            auto swiperPattern = weak.Upgrade();
            CHECK_NULL_VOID(swiperPattern);
            swiperPattern->springAnimationIsRunning_ = true;
            swiperPattern->OnSpringAnimationStart(static_cast<float>(dragVelocity));
            host->UpdateAnimatablePropertyFloat(SPRING_PROPERTY_NAME, delta);
        },
        [weak = AceType::WeakClaim(this)]() {
            PerfMonitor::GetPerfMonitor()->End(PerfConstants::APP_LIST_FLING, false);
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

bool SwiperPattern::IsOutOfStart(float mainOffset) const
{
    if (IsLoop() || itemPosition_.empty()) {
        return false;
    }

    auto startPos = itemPosition_.begin()->second.startPos;
    startPos = NearZero(startPos, PX_EPSILON) ? 0.f : startPos;
    return itemPosition_.begin()->first == 0 && GreatNotEqual(startPos + mainOffset, 0.f);
}

bool SwiperPattern::IsOutOfEnd(float mainOffset) const
{
    if (IsLoop() || itemPosition_.empty()) {
        return false;
    }

    auto visibleWindowSize = CalculateVisibleSize();
    auto endPos = itemPosition_.rbegin()->second.endPos + mainOffset;
    endPos = NearEqual(endPos, visibleWindowSize, PX_EPSILON) ? visibleWindowSize : endPos;
    return itemPosition_.rbegin()->first == TotalCount() - 1 && LessNotEqual(endPos, visibleWindowSize);
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
    CHECK_NULL_RETURN(swiperLayoutProperty, 0.0f);
    if (swiperLayoutProperty->IgnoreItemSpace()) {
        return 0.0f;
    }
    auto itemSpace = ConvertToPx(swiperLayoutProperty->GetItemSpace().value_or(0.0_vp),
        swiperLayoutProperty->GetLayoutConstraint()->scaleProperty, 0.0f).value_or(0.0f);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);
    auto mainSize = geometryNode->GetFrameSize().MainSize(GetDirection());
    if (itemSpace > mainSize) {
        itemSpace = 0.0f;
    }
    return itemSpace;
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
    if (hasCachedCapture_) {
        return true;
    }
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, true);
    if (TotalDisPlayCount() > TotalCount() ||
        (TotalDisPlayCount() == TotalCount() && SwiperUtils::IsStretch(layoutProperty) &&
            (NonPositive(layoutProperty->GetPrevMarginValue(0.0_px).ConvertToPx()) ||
                NonPositive(layoutProperty->GetNextMarginValue(0.0_px).ConvertToPx())))) {
        return false;
    }
    return layoutProperty->GetLoop().value_or(true);
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
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, false);
    return props->GetDisableSwipe().value_or(false);
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
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 1);
    auto displayCount = layoutProperty->GetDisplayCount().value_or(1);
    auto totalCount = RealTotalCount();
    if (IsSwipeByGroup() && displayCount != 0) {
        totalCount =
            static_cast<int32_t>(std::ceil(static_cast<float>(totalCount) / static_cast<float>(displayCount))) *
            displayCount;
    }

    return totalCount;
}

int32_t SwiperPattern::RealTotalCount() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    // last child is swiper indicator
    int num = 0;
    if (IsShowIndicator() && HasIndicatorNode()) {
        num += 1;
    }
    if (HasLeftButtonNode()) {
        num += 1;
    }
    if (HasRightButtonNode()) {
        num += 1;
    }
    if (hasCachedCapture_ && leftCaptureId_.has_value() && rightCaptureId_.has_value()) {
        num += 2;
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
            auto stepItems = swiper->IsSwipeByGroup() ? displayCount : 1;
            swiper->targetIndex_ = swiper->CheckTargetIndex(swiper->currentIndex_ + stepItems);
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
    std::vector<double> ratioList = {0.0};
    pipeline->AddVisibleAreaChangeNode(host, ratioList, callback, false);
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

void SwiperPattern::UpdateIndexOnAnimationStop()
{
    auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
    if (currentIndex_ == firstItemInfoInVisibleArea.first) {
        // swipe to left
        TriggerAnimationEndOnSwipeToLeft();
    } else {
        // swipe to right
        TriggerAnimationEndOnSwipeToRight();
    }
}

void SwiperPattern::UpdateIndexOnSwipePageStop(int32_t pauseTargetIndex)
{
    auto iter = itemPosition_.find(currentIndex_);
    if (iter == itemPosition_.end()) {
        UpdateCurrentIndex(pauseTargetIndex);
        if (itemPosition_.find(pauseTargetIndex) != itemPosition_.end()) {
            currentIndexOffset_ = itemPosition_.find(pauseTargetIndex)->second.startPos;
        }
        return;
    }

    auto swiperWidth = MainSize();
    auto currentOffset = iter->second.startPos;
    if (std::abs(currentOffset) < (swiperWidth / 2)) {
        return;
    }

    if (currentOffset < 0.0f) {
        auto nextPageIndex = currentIndex_ + GetDisplayCount();
        auto nextIter = itemPosition_.find(nextPageIndex);
        if (nextIter == itemPosition_.end()) {
            return;
        }

        auto nextPageOffset = nextIter->second.startPos;
        currentIndexOffset_ = nextPageOffset;
        UpdateCurrentIndex(nextPageIndex);
    } else {
        auto prevPageIndex = currentIndex_ - GetDisplayCount();
        auto prevIter = itemPosition_.find(prevPageIndex);
        if (prevIter == itemPosition_.end()) {
            return;
        }

        auto prevPageOffset = prevIter->second.startPos;
        currentIndexOffset_ = prevPageOffset;
        UpdateCurrentIndex(prevPageIndex);
    }
}

void SwiperPattern::TriggerAnimationEndOnForceStop()
{
    auto pauseTargetIndex = pauseTargetIndex_.has_value() ? pauseTargetIndex_.value() : currentIndex_;
    if (currentIndex_ != pauseTargetIndex) {
        if (IsSwipeByGroup()) {
            UpdateIndexOnSwipePageStop(pauseTargetIndex);
        } else {
            UpdateIndexOnAnimationStop();
        }

        UpdateCurrentFocus();
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

int32_t SwiperPattern::GetCachedCount() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 1);
    auto layoutProperty = host->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 1);
    auto cachedCount = layoutProperty->GetCachedCount().value_or(1);

    if (IsSwipeByGroup()) {
        cachedCount *= GetDisplayCount();
    }

    return cachedCount;
}

void SwiperPattern::SetLazyLoadFeature(bool useLazyLoad) const
{
    SetLazyForEachLongPredict(useLazyLoad);

    if (useLazyLoad) {
        auto cacheCount = GetCachedCount();
        std::set<int32_t> forEachIndexSet;
        for (auto count = 1; count <= cacheCount; count++) {
            forEachIndexSet.emplace(GetLoopIndex(currentIndex_ + count));
            forEachIndexSet.emplace(GetLoopIndex(currentIndex_ - count));
        }
        if (forEachIndexSet.empty()) {
            return;
        }

        auto host = GetHost();
        CHECK_NULL_VOID(host);
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
    if (!isParentHiddenChange_) {
        FireWillShowEvent(currentIndex_);
    }
    isWindowShow_ = true;
    if (NeedStartAutoPlay()) {
        StartAutoPlay();
    }
}

void SwiperPattern::OnWindowHide()
{
    if (!isParentHiddenChange_) {
        FireWillHideEvent(currentIndex_);
    }
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
        if (currentFocusIndex_ < currentIndex_ || currentFocusIndex_ >= currentIndex_ + GetDisplayCount()) {
            currentFocusIndex_ = currentIndex_;
        }
        do {
            auto curChildFrame = DynamicCast<FrameNode>(
                host->GetOrCreateChildByIndex(GetLoopIndex(currentFocusIndex_)));
            if (!curChildFrame || !IsContentFocused()) {
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

void SwiperPattern::OnScrollStartRecursive(float position, float velocity)
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
    if (!GetIsFixedNestedScrollMode()) {
        SetParentScrollable();
    }
    auto parent = GetNestedScrollParent();
    CHECK_NULL_VOID(parent);
    if (parent) {
        parent->OnScrollStartRecursive(position);
    }
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
    auto parent = GetNestedScrollParent();
    auto nestedScroll = GetNestedScroll();
    if (parent && nestedScroll.NeedParent()) {
        parent->OnScrollEndRecursive(std::nullopt);
    }
}

inline bool SwiperPattern::AnimationRunning() const
{
    return (controller_ && controller_->IsRunning()) || (springAnimation_ && springAnimationIsRunning_) ||
           (fadeAnimation_ && fadeAnimationIsRunning_) || targetIndex_ || usePropertyAnimation_;
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

    auto parent = GetNestedScrollParent();
    auto nestedScroll = GetNestedScroll();
    if (parent && nestedScroll.NeedParent()) {
        // after reach end, parent handle velocity first
        if (parent->HandleScrollVelocity(velocity)) {
            return true;
        }
    }
    HandleDragEnd(velocity);
    // after reached end, NONE doesn't consume velocity, other edge effects do
    return GetEdgeEffect() != EdgeEffect::NONE;
}

ScrollResult SwiperPattern::HandleScroll(float offset, int32_t source, NestedState state, float velocity)
{
    if (IsDisableSwipe()) {
        return { offset, true };
    }
    if (source == SCROLL_FROM_ANIMATION && AnimationRunning()) {
        // deny conflicting animation from child
        return { offset, true };
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
    auto parent = GetNestedScrollParent();
    auto nestedScroll = GetNestedScroll();
    if (!parent || !nestedScroll.NeedParent()) {
        if (IsOutOfBoundary(offset) && ChildFirst(state)) {
            CloseTheGap(offset);
            return { offset, true };
        }
        UpdateCurrentOffset(offset);
        return { 0.0f, !IsLoop() && GetDistanceToEdge() <= 0.0f };
    }
    ScrollResult result = { 0.f, !IsLoop() && GetDistanceToEdge() <= 0.f };
    if (parent && ((Negative(offset) && nestedScroll.forward == NestedScrollMode::PARENT_FIRST) ||
                      (Positive(offset) && nestedScroll.backward == NestedScrollMode::PARENT_FIRST))) {
        result = HandleScrollParentFirst(offset, source, state, velocity);
    } else if (parent && ((Negative(offset) && nestedScroll.forward == NestedScrollMode::SELF_FIRST) ||
                             (Positive(offset) && nestedScroll.backward == NestedScrollMode::SELF_FIRST))) {
        result = HandleScrollSelfFirst(offset, source, state, velocity);
    }
    return result;
}

ScrollResult SwiperPattern::HandleScrollParentFirst(float offset, int32_t source, NestedState state, float velocity)
{
    // priority: parent scroll > self scroll > self overScroll > parent overScroll
    auto parent = GetNestedScrollParent();
    // skip CHECK_NULL, already checked in HandleScroll
    auto result = parent->HandleScroll(offset, source, NestedState::CHILD_SCROLL, velocity);
    offset = result.remain;
    if (IsOutOfBoundary(offset)) {
        if (NearZero(offset)) {
            return { 0.f, true };
        }
        CloseTheGap(offset);
        if (ChildFirst(state)) {
            if (result.reachEdge) {
                result = parent->HandleScroll(offset, source, NestedState::CHILD_OVER_SCROLL, velocity);
            }
            return { result.remain, true };
        }
    }
    // self Scroll && self overScroll
    UpdateCurrentOffset(offset);
    return { 0.0f, !IsLoop() && GetDistanceToEdge() <= 0.0f };
}

ScrollResult SwiperPattern::HandleScrollSelfFirst(float offset, int32_t source, NestedState state, float velocity)
{
    // priority: self scroll > parent scroll > parent overScroll > self overScroll
    if ((IsOutOfStart(offset) && Positive(offset)) || (IsOutOfEnd(offset) && Negative(offset))) {
        CloseTheGap(offset);
        // skip CHECK_NULL, already checked in HandleScroll
        auto parent = GetNestedScrollParent();

        // reached edge, pass offset to parent
        auto res = parent->HandleScroll(offset, source, NestedState::CHILD_SCROLL, velocity);
        if (res.remain == 0.0f) {
            return { 0.0f, true };
        }
        // parent handle overScroll first
        if (res.reachEdge) {
            res = parent->HandleScroll(res.remain, source, NestedState::CHILD_OVER_SCROLL, velocity);
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

void SwiperPattern::CloseTheGap(float& offset)
{
    float distanceToEdge = GetDistanceToEdge();
    if (Positive(distanceToEdge)) {
        if (GreatOrEqual(std::abs(offset), distanceToEdge)) {
            UpdateCurrentOffset(Positive(offset) ? distanceToEdge : -distanceToEdge);
            offset = Positive(offset) ? offset - distanceToEdge : offset + distanceToEdge;
        }
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

void SwiperPattern::CleanScrollingListener()
{
    scrollingListener_.clear();
}

void SwiperPattern::StopIndicatorAnimation(bool ifImmediately)
{
    AnimationUtils::StopAnimation(indicatorAnimation_);

    if (stopIndicatorAnimationFunc_) {
        stopIndicatorAnimationFunc_(ifImmediately);
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
    FireWillShowEvent(toIndex);
    FireWillHideEvent(fromIndex);
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
    CHECK_NULL_VOID(onTabsCustomContentTransition_);

    auto tabContentAnimatedTransition = (*onTabsCustomContentTransition_)(fromIndex, toIndex);
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
        if (isDragging_) {
            HandleDragEnd(0.0);
        }
    }
}

bool SwiperPattern::IsSwipeByGroup() const
{
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetSwipeByGroup().value_or(false);
}

RefPtr<FrameNode> SwiperPattern::GetCurrentFrameNode(int32_t currentIndex) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto currentLayoutWrapper = host->GetChildByIndex(GetLoopIndex(currentIndex));
    CHECK_NULL_RETURN(currentLayoutWrapper, nullptr);
    return currentLayoutWrapper->GetHostNode();
}

void SwiperPattern::ProcessDelta(float& delta, float mainSize, float deltaSum)
{
    if (std::abs(delta) > mainSize) {
        delta = delta > 0 ? mainSize : -mainSize;
    }

    if ((std::abs(deltaSum + delta)) > mainSize) {
        delta = GreatNotEqual((deltaSum + delta), 0) ? (mainSize - deltaSum) :
            (-deltaSum - mainSize);
    }
}

bool SwiperPattern::ContentWillChange(int32_t comingIndex)
{
    return ContentWillChange(GetCurrentIndex(), comingIndex);
}

bool SwiperPattern::ContentWillChange(int32_t currentIndex, int32_t comingIndex)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_RETURN(tabsNode, true);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_RETURN(tabsPattern, true);
    if (tabsPattern->GetInterceptStatus()) {
        auto ret = tabsPattern->OnContentWillChange(currentIndex, comingIndex);
        return ret.has_value() ? ret.value() : true;
    }
    return true;
}

bool SwiperPattern::CheckSwiperPanEvent(const GestureEvent& info)
{
    int32_t currentIndex = GetCurrentIndex();
    int32_t comingIndex = currentIndex;
    if (GreatNotEqual(info.GetMainDelta(), 0.0)) {
        comingIndex = comingIndex < 1 ? 0 : comingIndex - 1;
    } else if (LessNotEqual(info.GetMainDelta(), 0.0)) {
        comingIndex = comingIndex > TotalCount() - INDEX_DIFF_TWO ? TotalCount() - 1 : comingIndex + 1;
    }

    auto iter = indexCanChangeMap_.find(comingIndex);
    if (iter != indexCanChangeMap_.end()) {
        return iter->second;
    }
    bool ret = ContentWillChange(currentIndex, comingIndex);
    indexCanChangeMap_.emplace(comingIndex, ret);
    return ret;
}

void SwiperPattern::FireWillHideEvent(int32_t willHideIndex) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(host->GetChildByIndex(willHideIndex));
    CHECK_NULL_VOID(tabContentNode);
    auto tabContentEventHub = tabContentNode->GetEventHub<TabContentEventHub>();
    CHECK_NULL_VOID(tabContentEventHub);
    tabContentEventHub->FireWillHideEvent();
}

void SwiperPattern::FireWillShowEvent(int32_t willShowIndex) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(host->GetChildByIndex(willShowIndex));
    CHECK_NULL_VOID(tabContentNode);
    auto tabContentEventHub = tabContentNode->GetEventHub<TabContentEventHub>();
    CHECK_NULL_VOID(tabContentEventHub);
    tabContentEventHub->FireWillShowEvent();
}

void SwiperPattern::SetOnHiddenChangeForParent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto parent = host->GetAncestorNodeOfFrame();
    CHECK_NULL_VOID(parent);
    while (parent) {
        if (parent->GetTag() == V2::PAGE_ETS_TAG || parent->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            break;
        }
        parent = parent->GetAncestorNodeOfFrame();
    }
    auto onHiddenChange = [weak = WeakClaim(this)](bool isShow) {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        auto index = swiperPattern->GetCurrentIndex();

        if (isShow) {
            swiperPattern->FireWillShowEvent(index);
        } else {
            swiperPattern->FireWillHideEvent(index);
        }
        swiperPattern->isParentHiddenChange_ = true;
    };
    CHECK_NULL_VOID(parent);
    if (parent->GetTag() == V2::PAGE_ETS_TAG) {
        auto pagePattern = parent->GetPattern<PagePattern>();
        CHECK_NULL_VOID(pagePattern);
        pagePattern->SetOnHiddenChange(std::move(onHiddenChange));
    }

    if (parent->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
        auto navDestinationePattern = parent->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationePattern);
        auto navDestinationEventHub = navDestinationePattern->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(navDestinationEventHub);
        navDestinationEventHub->SetOnHiddenChange(std::move(onHiddenChange));
    }
}
} // namespace OHOS::Ace::NG
