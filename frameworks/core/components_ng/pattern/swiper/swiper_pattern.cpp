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
#include "base/log/ace_trace.h"
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
#include "core/components_ng/pattern/swiper/swiper_helper.h"
#include "core/components_ng/pattern/swiper/swiper_node.h"
#include "core/components_ng/pattern/swiper/swiper_paint_method.h"
#include "core/components_ng/pattern/swiper/swiper_theme.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/arc_swiper_indicator_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_arrow_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_node.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/render/adapter/component_snapshot.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"

namespace OHOS::Ace::NG {
namespace {

// TODO use theme.
constexpr int32_t MAX_DISPLAY_COUNT_MIN = 6;
constexpr int32_t MAX_DISPLAY_COUNT_MAX = 9;
constexpr int32_t MIN_TURN_PAGE_VELOCITY = 1200;
constexpr int32_t NEW_MIN_TURN_PAGE_VELOCITY = 780;
constexpr Dimension INDICATOR_BORDER_RADIUS = 16.0_vp;

constexpr float PX_EPSILON = 0.01f;
constexpr float FADE_DURATION = 500.0f;
constexpr float SPRING_DURATION = 600.0f;
constexpr float DEFAULT_MINIMUM_AMPLITUDE_PX = 1.0f;
constexpr int32_t INDEX_DIFF_TWO = 2;
constexpr int32_t FIRST_CAPTURE_DELAY_TIME = 30;
const std::string SWIPER_DRAG_SCENE = "swiper_drag_scene";
const std::string FADE_PROPERTY_NAME = "fade";
const std::string SPRING_PROPERTY_NAME = "spring";
const std::string INDICATOR_PROPERTY_NAME = "indicator";
const std::string TRANSLATE_PROPERTY_NAME = "translate";
constexpr uint16_t CAPTURE_PIXEL_ROUND_VALUE = static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_START) |
                                              static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_TOP) |
                                              static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_END) |
                                              static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM);
constexpr int32_t CAPTURE_COUNT = 2;
constexpr char APP_SWIPER_NO_ANIMATION_SWITCH[] = "APP_SWIPER_NO_ANIMATION_SWITCH";
constexpr char APP_SWIPER_FRAME_ANIMATION[] = "APP_SWIPER_FRAME_ANIMATION";
constexpr char APP_TABS_FLING[] = "APP_TABS_FLING";
constexpr char APP_TABS_SCROLL[] = "APP_TABS_SCROLL";
constexpr char APP_TABS_NO_ANIMATION_SWITCH[] = "APP_TABS_NO_ANIMATION_SWITCH";
constexpr char APP_TABS_FRAME_ANIMATION[] = "APP_TABS_FRAME_ANIMATION";

constexpr int32_t COMPONENT_SWIPER_FLING = 1;
constexpr int32_t PAGE_FLIP_MODE_SIZE = 2;
const RefPtr<FrameRateRange> SWIPER_DEFAULT_FRAME_RATE =
    AceType::MakeRefPtr<FrameRateRange>(0, 0, 0, COMPONENT_SWIPER_FLING);

} // namespace

SwiperPattern::SwiperPattern()
{
    swiperController_ = MakeRefPtr<SwiperController>();
    SwiperHelper::InitSwiperController(swiperController_, WeakClaim(this));
}

void SwiperPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetClipToFrame(true);
    renderContext->SetClipToBounds(true);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto indicatorTheme = pipeline->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(indicatorTheme);
    renderContext->UpdateClipEdge(indicatorTheme->GetClipEdge());
    InitSurfaceChangedCallback();
}

void SwiperPattern::OnDetachFromFrameNode(FrameNode* node)
{
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    if (HasSurfaceChangedCallback()) {
        pipeline->UnregisterSurfaceChangedCallback(surfaceChangedCallbackId_.value_or(-1));
    }
    pipeline->RemoveWindowStateChangedCallback(node->GetId());
}

void SwiperPattern::OnAttachToMainTree()
{
    if (!isInit_) {
        SetOnHiddenChangeForParent();
    }
}

void SwiperPattern::OnDetachFromMainTree()
{
    RemoveOnHiddenChange();
}

RefPtr<LayoutAlgorithm> SwiperPattern::CreateLayoutAlgorithm()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto props = host->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, nullptr);

    auto algo = MakeRefPtr<SwiperLayoutAlgorithm>();
    if (props->GetIsCustomAnimation().value_or(false)) {
        algo->SetUseCustomAnimation(true);
        algo->SetCustomAnimationToIndex(customAnimationToIndex_);
        algo->SetIndexsInAnimation(indexsInAnimation_);
        algo->SetNeedUnmountIndexs(needUnmountIndexs_);
        return algo;
    }
    if (SupportSwiperCustomAnimation()) {
        algo->SetNeedUnmountIndexs(needUnmountIndexs_);
        algo->SetItemsPositionInAnimation(itemPositionInAnimation_);
    }

    if (jumpIndex_) {
        algo->SetJumpIndex(jumpIndex_.value());
    } else if (targetIndex_) {
        algo->SetTargetIndex(targetIndex_.value());
    }
    algo->SetCachedShow(IsCachedShow());
    algo->SetCurrentIndex(currentIndex_);
    algo->SetMainSizeIsMeasured(mainSizeIsMeasured_);
    oldContentMainSize_ = contentMainSize_;
    algo->SetContentMainSize(contentMainSize_);
    algo->SetDuringInteraction(isDragging_ || RunningTranslateAnimation());
    if (!propertyAnimationIsRunning_) {
        algo->SetCurrentDelta(currentDelta_);
    }
    algo->SetItemsPosition(itemPosition_);
    if (IsOutOfBoundary() && !IsLoop()) {
        algo->SetOverScrollFeature();
    }
    algo->SetTotalItemCount(TotalCount());
    algo->SetIsLoop(IsLoop());
    algo->SetSwipeByGroup(IsSwipeByGroup());
    algo->SetRealTotalCount(RealTotalCount());
    algo->SetPlaceItemWidth(placeItemWidth_);
    algo->SetIsFrameAnimation(translateAnimationIsRunning_);

    auto swiperPaintProperty = host->GetPaintProperty<SwiperPaintProperty>();
    const auto effect = swiperPaintProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING);
    algo->SetCanOverScroll(effect == EdgeEffect::SPRING);
    algo->SetHasCachedCapture(hasCachedCapture_);
    algo->SetIsCaptureReverse(isCaptureReverse_);
    algo->SetCachedCount(GetCachedCount());
    algo->SetIgnoreBlankOffset(ignoreBlankOffset_);
    return algo;
}

void SwiperPattern::OnIndexChange(bool isInLayout)
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
        FireChangeEvent(oldIndex, targetIndex, isInLayout);
        // lazyBuild feature.
        SetLazyLoadFeature(true);
    }
}

void SwiperPattern::StopAndResetSpringAnimation()
{
    if (springAnimationIsRunning_ && !isTouchDownSpringAnimation_) {
        StopSpringAnimation();
        currentDelta_ = 0.0f;
        itemPosition_.clear();
        isVoluntarilyClear_ = true;
        jumpIndex_ = currentIndex_;
    }
}

void SwiperPattern::CheckLoopChange()
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(props);
    auto currentLoopValue = props->GetLoop().value_or(true);
    if (!preLoop_.has_value()) {
        preLoop_ = currentLoopValue;
        return;
    }

    if (preLoop_.value() != currentLoopValue) {
        currentIndex_ =
            GetLoopIndex(currentIndex_, oldChildrenSize_.has_value() ? oldChildrenSize_.value() : TotalCount());
        if (props->GetPrevMargin().has_value() || props->GetNextMargin().has_value()) {
            jumpIndex_ = jumpIndex_.value_or(currentIndex_);
        }
        preLoop_ = currentLoopValue;
    }
}

void SwiperPattern::AdjustCurrentIndexOnSwipePage(int32_t index)
{
    auto adjustIndex = SwiperUtils::ComputePageIndex(index, GetDisplayCount());
    const auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateIndexWithoutMeasure(GetLoopIndex(adjustIndex));
    currentIndex_ = GetLoopIndex(adjustIndex);
}

void SwiperPattern::InitCapture()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(props);
    bool hasCachedCapture = SwiperUtils::IsStretch(props) && props->GetLoop().value_or(true) && !IsSwipeByGroup() &&
                            GetDisplayCount() == TotalCount() - 1 &&
                            (Positive(props->GetPrevMarginValue(0.0_px).ConvertToPx()) ||
                                Positive(props->GetNextMarginValue(0.0_px).ConvertToPx()));
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
        auto imageLayoutProperty = leftCaptureNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdatePixelRound(CAPTURE_PIXEL_ROUND_VALUE);
        leftCaptureNode->MarkModifyDone();
        host->AddChild(leftCaptureNode, -number);

        auto rightCaptureNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_CAPTURE_ETS_TAG, GetRightCaptureId(),
            []() { return AceType::MakeRefPtr<ImagePattern>(); });
        imageLayoutProperty = rightCaptureNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdatePixelRound(CAPTURE_PIXEL_ROUND_VALUE);
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

void SwiperPattern::SetLazyForEachFlag() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto targetNode = FindLazyForEachNode(host);
    if (targetNode.has_value()) {
        auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(targetNode.value());
        CHECK_NULL_VOID(lazyForEachNode);
        lazyForEachNode->SetFlagForGeneratedItem(PROPERTY_UPDATE_MEASURE);
    }
}

void SwiperPattern::ResetOnForceMeasure()
{
    resetLayoutTask_.Cancel();
    StopPropertyTranslateAnimation(isFinishAnimation_, false, true);
    StopTranslateAnimation();
    StopSpringAnimationImmediately();
    StopFadeAnimation();
    StopIndicatorAnimation(true);
    currentOffset_ = 0.0f;
    mainSizeIsMeasured_ = false;
    currentDelta_ = 0.0f;
    itemPosition_.clear();
    isVoluntarilyClear_ = true;
    jumpIndex_ = jumpIndex_.value_or(currentIndex_);
    SetLazyForEachFlag();
    MarkDirtyNodeSelf();
}

void SwiperPattern::UpdateTabBarIndicatorCurve()
{
    CHECK_NULL_VOID(swiperController_);
    auto updateCubicCurveCallback = [weak = WeakClaim(this)]() {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        auto host = swiperPattern->GetHost();
        CHECK_NULL_VOID(host);
        auto props = host->GetPaintProperty<SwiperPaintProperty>();
        CHECK_NULL_VOID(props);
        auto curve = MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
        props->UpdateCurve(curve);
    };
    swiperController_->SetUpdateCubicCurveCallback(std::move(updateCubicCurveCallback));
}

bool SwiperPattern::NeedForceMeasure() const
{
    const auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, false);

    return ((props->GetPropertyChangeFlag() & PROPERTY_UPDATE_MEASURE) == PROPERTY_UPDATE_MEASURE) ||
           (isSwipeByGroup_.has_value() && isSwipeByGroup_.value() != IsSwipeByGroup());
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

    auto index = CurrentIndex();
    if (currentIndex_ != index && index >= 0) {
        AceAsyncTraceBeginCommercial(
            0, hasTabsAncestor_ ? APP_TABS_NO_ANIMATION_SWITCH : APP_SWIPER_NO_ANIMATION_SWITCH);
    }

    if (!isBindIndicator_) {
        InitIndicator();
    }
    InitArrow();
    InitCapture();
    CheckSpecialItemCount();
    SetLazyLoadIsLoop();
    RegisterVisibleAreaChange();
    InitTouchEvent(gestureHub);
    InitHoverMouseEvent();
    StopAndResetSpringAnimation();

    if (NeedForceMeasure()) {
        ResetOnForceMeasure();
    }

    isSwipeByGroup_ = IsSwipeByGroup();

    bool disableSwipe = IsDisableSwipe();
    UpdateSwiperPanEvent(disableSwipe);

    auto focusHub = host->GetFocusHub();
    if (focusHub) {
        InitOnKeyEvent(focusHub);
        InitOnFocusInternal(focusHub);
    }
#ifdef SUPPORT_DIGITAL_CROWN
        InitOnCrownEventInternal(focusHub);
#endif

    SetSwiperEventCallback(disableSwipe);
    UpdateTabBarIndicatorCurve();

    if (IsAutoPlay()) {
        StartAutoPlay();
    } else {
        translateTask_.Cancel();
        isInAutoPlay_ = false;
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

int32_t SwiperPattern::CheckUserSetIndex(int32_t index)
{
    if (!IsAutoLinear()) {
        return index;
    }

    if (index < 0 || index >= RealTotalCount()) {
        index = 0;
        UpdateCurrentIndex(index);
    }

    auto childNode = GetCurrentFrameNode(GetLoopIndex(index));
    CHECK_NULL_RETURN(childNode, index);
    auto childLayoutProperty = childNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_RETURN(childLayoutProperty, index);
    if (childLayoutProperty->GetVisibility().value_or(VisibleType::VISIBLE) != VisibleType::GONE) {
        return index;
    }

    return CheckTargetIndex(index + 1);
}

void SwiperPattern::UpdateIndicatorOnChildChange()
{
    if (HasIndicatorNode()) {
        StopIndicatorAnimation();
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto indicatorNode = GetCommonIndicatorNode();
        if (indicatorNode && IsIndicator(indicatorNode->GetTag())) {
            indicatorNode->MarkModifyDone();
            indicatorNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    }
}

void SwiperPattern::UpdateDigitalIndicator()
{
    if (!HasIndicatorNode() || GetIndicatorType() != SwiperIndicatorType::DIGIT) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto indicatorNode = DynamicCast<FrameNode>(host->GetChildAtIndex(host->GetChildIndexById(GetIndicatorId())));
    CHECK_NULL_VOID(indicatorNode);

    if (indicatorNode->GetTag() != V2::SWIPER_INDICATOR_ETS_TAG) {
        return;
    }

    indicatorNode->MarkModifyDone();
    indicatorNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void SwiperPattern::BeforeCreateLayoutWrapper()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hadCachedCapture = hasCachedCapture_;
    if (host->GetChildrenUpdated() != -1) {
        InitCapture();
        if (NeedAutoPlay() && !translateTask_) {
            StartAutoPlay();
        }
        UpdateCurrentFocus();
        host->ChildrenUpdatedFrom(-1);
    }

    CheckLoopChange();
    oldIndex_ = currentIndex_;
    auto userSetCurrentIndex = CurrentIndex();
    userSetCurrentIndex = CheckUserSetIndex(userSetCurrentIndex);
    auto oldIndex = GetLoopIndex(oldIndex_);
    if (oldChildrenSize_.has_value() && oldChildrenSize_.value() != TotalCount()) {
        oldIndex = GetLoopIndex(oldIndex_, oldChildrenSize_.value());
        UpdateIndicatorOnChildChange();
        StartAutoPlay();
        InitArrow();
        if (IsLoop() && oldIndex != GetLoopIndex(currentIndex_)) {
            currentIndex_ = oldIndex >= TotalCount() ? 0 : oldIndex;
        }
    } else if (oldRealTotalCount_ && oldRealTotalCount_.value() != RealTotalCount()) {
        UpdateDigitalIndicator();
    }
    auto index = CheckIndexRange(userSetCurrentIndex);
    if (index != userSetCurrentIndex) {
        UpdateCurrentIndex(index);
    } else if (oldIndex != userSetCurrentIndex) {
        currentIndex_ = userSetCurrentIndex;
        propertyAnimationIndex_ = GetLoopIndex(propertyAnimationIndex_);
    }

    if (IsSwipeByGroup() && needAdjustIndex_) {
        AdjustCurrentIndexOnSwipePage(CurrentIndex());
        needAdjustIndex_ = false;
    }

    if (oldIndex_ != currentIndex_ || (itemPosition_.empty() && !isVoluntarilyClear_)
        || hadCachedCapture != hasCachedCapture_) {
        jumpIndex_ = GetLoopIndex(currentIndex_);
        currentFirstIndex_ = jumpIndex_.value_or(0);
        turnPageRate_ = 0.0f;
        SetIndicatorJumpIndex(jumpIndex_);
    }
    isVoluntarilyClear_ = false;
    if (jumpIndex_) {
        if ((jumpIndex_.value() < 0 || jumpIndex_.value() >= TotalCount()) && !IsLoop()) {
            jumpIndex_ = 0;
        }
        targetIndex_.reset();
        nextIndex_ = jumpIndex_.value();
        StopAutoPlay();
        StopTranslateAnimation();
        StopFadeAnimation();
        StopSpringAnimation();
        if (propertyAnimationIsRunning_) {
            StopPropertyTranslateAnimation(false, true);
            StopIndicatorAnimation();
        }
        currentDelta_ = 0.0f;
    }
    if (oldIndex_ != currentIndex_ && !isInit_ && !IsUseCustomAnimation()) {
        FireWillShowEvent(currentIndex_);
        FireWillHideEvent(oldIndex_);
    }

    UpdateIgnoreBlankOffsetWithIndex();
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
    auto callback = [weak = WeakClaim(this), captureId, targetIndex, hostInstanceId = GetHostInstanceId()](
                        std::shared_ptr<Media::PixelMap> pixelMap) {
        ContainerScope scope(hostInstanceId);
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        auto piplineContext = swiper->GetContext();
        CHECK_NULL_VOID(piplineContext);
        auto taskExecutor = piplineContext->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [weak, pixelMap, captureId, targetIndex]() mutable {
                auto swiper = weak.Upgrade();
                CHECK_NULL_VOID(swiper);
                swiper->UpdateCaptureSource(pixelMap, captureId, targetIndex);
            },
            TaskExecutor::TaskType::UI, "ArkUISwiperUpdateCaptureSource",
            TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    };
    if (forceUpdate) {
        // The size changes caused by layout need to wait for rendering before taking a screenshot
        auto piplineContext = GetContext();
        CHECK_NULL_VOID(piplineContext);
        auto taskExecutor = piplineContext->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostDelayedTask(
            [weakTarget = WeakClaim(RawPtr(targetNode)), callback]() {
                auto target = weakTarget.Upgrade();
                CHECK_NULL_VOID(target);
                ComponentSnapshot::GetNormalCapture(target, std::move(callback));
            },
            TaskExecutor::TaskType::UI, FIRST_CAPTURE_DELAY_TIME, "ArkUISwiperGetNormalCapture");
    } else {
        ComponentSnapshot::GetNormalCapture(targetNode, std::move(callback));
    }
}

void SwiperPattern::UpdateCaptureSource(
    std::shared_ptr<Media::PixelMap> pixelMap, int32_t captureId, int32_t targetIndex)
{
    // Async tasks require verifying if the pixel map is the correct target
    if (!(captureId == GetLeftCaptureId() && leftCaptureIndex_.has_value() &&
            targetIndex == leftCaptureIndex_.value()) &&
        !(captureId == GetRightCaptureId() && rightCaptureIndex_.has_value() &&
            targetIndex == rightCaptureIndex_.value())) {
        return;
    }
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
    auto imageLayoutProperty = captureNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(PixelMap::CreatePixelMap(&pixelMap)));
    imageLayoutProperty->UpdateMargin(margin);
    captureNode->MarkModifyDone();
    captureNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void SwiperPattern::InitSurfaceChangedCallback()
{
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    if (!HasSurfaceChangedCallback()) {
        auto callbackId = pipeline->RegisterSurfaceChangedCallback(
            [weak = WeakClaim(this)](int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight,
                WindowSizeChangeReason type) {
                if (type == WindowSizeChangeReason::UNDEFINED && newWidth == prevWidth && newHeight == prevHeight) {
                    return;
                }
                auto swiper = weak.Upgrade();
                if (!swiper) {
                    return;
                }

                if (type == WindowSizeChangeReason::ROTATION || type == WindowSizeChangeReason::UNDEFINED) {
                    swiper->windowSizeChangeReason_ = type;
                    swiper->StopAutoPlay();
                }
                auto currentIndex =
                    swiper->targetIndex_.has_value() ? swiper->targetIndex_.value() : swiper->currentIndex_;

                swiper->needFireCustomAnimationEvent_ = swiper->translateAnimationIsRunning_;
                if (swiper->SupportSwiperCustomAnimation() && swiper->needFireCustomAnimationEvent_) {
                    swiper->indexsInAnimation_.insert(swiper->GetLoopIndex(currentIndex));
                }

                swiper->StopPropertyTranslateAnimation(swiper->isFinishAnimation_);
                swiper->StopTranslateAnimation();
                swiper->StopSpringAnimationImmediately();
                swiper->StopFadeAnimation();
                swiper->StopIndicatorAnimation();
                const auto& surfaceChangeCallback = swiper->swiperController_->GetSurfaceChangeCallback();
                if (surfaceChangeCallback) {
                    surfaceChangeCallback();
                }
                swiper->currentOffset_ = 0.0f;
                swiper->itemPosition_.clear();
                swiper->placeItemWidth_.reset();
                swiper->isVoluntarilyClear_ = true;
                swiper->jumpIndex_ = currentIndex;
                swiper->SetIndicatorJumpIndex(currentIndex);
                swiper->MarkDirtyNodeSelf();
                swiper->SetLazyForEachFlag();
            });
        UpdateSurfaceChangedCallbackId(callbackId);
    }
}

bool SwiperPattern::IsFocusNodeInItemPosition(const RefPtr<FocusHub>& targetFocusHub)
{
    for (const auto& item : itemPosition_) {
        auto itemNode = GetCurrentFrameNode(item.first);
        if (!itemNode) {
            continue;
        }
        if (itemNode->GetFirstFocusHubChild() == targetFocusHub) {
            return true;
        }
    }
    return false;
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
    int32_t skipCnt = 0;
    if (IsShowIndicator()) {
        ++skipCnt;
    }
    if (HasLeftButtonNode()) {
        ++skipCnt;
    }
    if (HasRightButtonNode()) {
        ++skipCnt;
    }
    std::list<RefPtr<FocusHub>> focusNodes;
    swiperFocusHub->FlushChildrenFocusHub(focusNodes);
    for (auto iter = focusNodes.rbegin(); iter != focusNodes.rend(); ++iter) {
        const auto& node = *iter;
        if (skipCnt > 0 || !node) {
            --skipCnt;
            continue;
        }
        if (IsUseCustomAnimation() && hasTabsAncestor_) {
            node->SetParentFocusable(node == showChildFocusHub);
        } else {
            node->SetParentFocusable(IsFocusNodeInItemPosition(node));
        }
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
        if (swiperFocusHub->AcceptFocusOfPriorityChild()) {
            return;
        }
        swiperFocusHub->SetLastWeakFocusNode(AceType::WeakClaim(AceType::RawPtr(needFocusNode)));
    }
}
RefPtr<FocusHub> SwiperPattern::GetFocusHubChild(std::string childFrameName)
{
    auto swiperHost = GetHost();
    CHECK_NULL_RETURN(swiperHost, nullptr);
    auto swiperFocusHub = swiperHost->GetFocusHub();
    CHECK_NULL_RETURN(swiperFocusHub, nullptr);
    RefPtr<FocusHub> target;
    swiperFocusHub->AnyChildFocusHub([&target, childFrameName](const RefPtr<FocusHub>& child) {
        CHECK_NULL_RETURN(child, true);
        if (child->GetFrameName() == childFrameName) {
            target = child;
            return true;
        }
        return false;
    });
    return target;
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
    const auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, nullptr);
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
            props->GetHoverShowValue(false)) {
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
    const auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, nullptr);
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
            props->GetHoverShowValue(false)) {
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
    auto totalCount = TotalCount();
    if (totalCount <= 0) {
        return originalIndex;
    }
    auto loopIndex = originalIndex;
    while (loopIndex < 0) {
        loopIndex = loopIndex + totalCount;
    }
    loopIndex %= totalCount;
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

void SwiperPattern::CheckAndFireCustomAnimation()
{
    if (!SupportSwiperCustomAnimation() || !needFireCustomAnimationEvent_) {
        return;
    }

    itemPositionInAnimation_.clear();
    for (const auto& item : itemPosition_) {
        auto index = GetLoopIndex(item.first);
        itemPositionInAnimation_[index] = item.second;
    }
    FireSwiperCustomAnimationEvent();
    FireContentDidScrollEvent();
    itemPositionInAnimation_.clear();
}

bool SwiperPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (!isDragging_ || isInit_) {
        SetLazyLoadFeature(true);
    }
    if (!isInit_) {
        OnIndexChange(true);
        oldIndex_ = currentIndex_;
    }

    auto isInit = isInit_;
    isInit_ = false;

    if (!IsAutoPlay() && config.skipMeasure && config.skipLayout) {
        return false;
    }

    const auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, false);
    auto layoutAlgorithmWrapper = dirty->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto algo = DynamicCast<SwiperLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(algo, false);

    // set tabs invisible item freeze state.
    HandleTabsAncestor();

    if (props->GetIsCustomAnimation().value_or(false)) {
        needUnmountIndexs_ = algo->GetNeedUnmountIndexs();
        return false;
    }
    if (SupportSwiperCustomAnimation()) {
        needUnmountIndexs_ = algo->GetNeedUnmountIndexs();
        itemPositionInAnimation_ = algo->GetItemsPositionInAnimation();
        FireContentDidScrollEvent();
    }

    UpdateLayoutProperties(algo);
    PostIdleTask(GetHost());

    if (!itemPosition_.empty()) {
        const auto& turnPageRateCallback = swiperController_->GetTurnPageRateCallback();
        auto firstItem = GetFirstItemInfoInVisibleArea();
        auto translateLength = firstItem.second.endPos - firstItem.second.startPos;
        if (turnPageRateCallback && isDragging_ && !NearZero(translateLength)) {
            turnPageRateCallback(firstItem.first, -firstItem.second.startPos / translateLength);
        }

        placeItemWidth_ = translateLength;
    }
    if (hasCachedCapture_) {
        isCaptureReverse_ = algo->GetIsCaptureReverse();
        UpdateTargetCapture(algo->GetIsNeedUpdateCapture());
    }

    if (!targetIndex_) {
        if (isUserFinish_) {
            SetIndicatorJumpIndex(jumpIndex_);
        }

        CheckMarkDirtyNodeForRenderIndicator();
    }

    PlayScrollAnimation(currentDelta_);
    if (jumpIndex_) {
        auto pipeline = GetContext();
        if (pipeline) {
            pipeline->AddAfterRenderTask([weak = WeakClaim(this)]() {
                auto swiper = weak.Upgrade();
                CHECK_NULL_VOID(swiper);
                PerfMonitor::GetPerfMonitor()->End(PerfConstants::APP_TAB_SWITCH, true);
                AceAsyncTraceEndCommercial(
                    0, swiper->hasTabsAncestor_ ? APP_TABS_NO_ANIMATION_SWITCH : APP_SWIPER_NO_ANIMATION_SWITCH);
            });
        }
        UpdateCurrentIndex(algo->GetCurrentIndex());
        AdjustCurrentFocusIndex();
        auto curChild = dirty->GetOrCreateChildByIndex(GetLoopIndex(currentFocusIndex_));
        if (curChild && IsContentFocused()) {
            auto curChildFrame = curChild->GetHostNode();
            CHECK_NULL_RETURN(curChildFrame, false);
            FlushFocus(curChildFrame);
        }
        currentIndexOffset_ = 0.0f;
        springOffset_ = 0.0f;
        if (!isInit) {
            OnIndexChange(true);
        }

        if (SupportSwiperCustomAnimation() && prevFrameAnimationRunning_) {
            for (const auto& item : itemPosition_) {
                auto index = GetLoopIndex(item.first);
                indexsInAnimation_.insert(index);
            }
        }

        jumpIndex_.reset();
        pauseTargetIndex_.reset();
        auto delayTime = GetInterval() - GetDuration();
        delayTime = std::clamp(delayTime, 0, delayTime);
        if (NeedAutoPlay() && isUserFinish_) {
            PostTranslateTask(delayTime);
        }

        CheckAndFireCustomAnimation();
    } else if (RunningTranslateAnimation() && !NearEqual(oldContentMainSize_, algo->GetContentMainSize())) {
        HandleRunningTranslateAnimation();
    } else if (targetIndex_) {
        HandleTargetIndex(dirty, algo);
#ifdef SUPPORT_DIGITAL_CROWN
        if (IsCrownSpring()) {
            SetIsCrownSpring(false);
        }
#endif
        velocity_.reset();
        pauseTargetIndex_ = targetIndex_;
    } else if (algo->GetJumpIndex().has_value()) {
        // jumpIndex_ is set inside layout algorithm to reset layout, need reset currentIndexOffset_
        currentIndexOffset_ = 0.0f;
        springOffset_ = 0.0f;
    }
    mainSizeIsMeasured_ = algo->GetMainSizeIsMeasured();
    contentCrossSize_ = algo->GetContentCrossSize();
    currentDelta_ = 0.0f;
    contentMainSize_ = algo->GetContentMainSize();
    oldContentMainSize_ = contentMainSize_;
    crossMatchChild_ = algo->IsCrossMatchChild();
    ignoreBlankOffset_ = algo->GetIgnoreBlankOffset();
    oldIndex_ = currentIndex_;
    oldChildrenSize_ = TotalCount();
    oldRealTotalCount_ = RealTotalCount();
    needFireCustomAnimationEvent_ = true;
    prevFrameAnimationRunning_ = false;

    if (windowSizeChangeReason_ == WindowSizeChangeReason::ROTATION) {
        StartAutoPlay();
        windowSizeChangeReason_ = WindowSizeChangeReason::UNDEFINED;
    }

    if (onContentDidScroll_) {
        indexsInAnimation_.clear();
    }

    const auto& paddingProperty = props->GetPaddingProperty();
    return GetEdgeEffect() == EdgeEffect::FADE || paddingProperty != nullptr;
}

void SwiperPattern::HandleRunningTranslateAnimation()
{
    auto pipeline = GetContext();
    RefPtr<TaskExecutor> taskExecutor = pipeline ? pipeline->GetTaskExecutor() : nullptr;
    if (taskExecutor) {
        resetLayoutTask_.Cancel();
        resetLayoutTask_.Reset([weak = AceType::WeakClaim(this)] {
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            if (swiper->RunningTranslateAnimation()) {
                swiper->isUserFinish_ = false;
                swiper->FinishAnimation();
                swiper->currentDelta_ = 0.0f;
                swiper->itemPosition_.clear();
                swiper->isVoluntarilyClear_ = true;
                swiper->jumpIndex_ = swiper->currentIndex_;
                swiper->MarkDirtyNodeSelf();
            }
        });
        taskExecutor->PostTask(resetLayoutTask_, TaskExecutor::TaskType::UI, "ArkUISwiperResetLayout",
            TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    }
}

void SwiperPattern::HandleTargetIndex(const RefPtr<LayoutWrapper>& dirty, const RefPtr<SwiperLayoutAlgorithm>& algo)
{
    auto targetIndexValue = IsLoop() ? targetIndex_.value() : GetLoopIndex(targetIndex_.value());
    auto iter = itemPosition_.find(targetIndexValue);
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(props);

    if (iter == itemPosition_.end()) {
        HandleTargetItemNotFound(props, targetIndexValue, algo);
        return;
    }

    float targetPos = iter->second.startPos;
    bool isNeedForwardTranslate = IsNeedForwardTranslate(props, targetIndexValue);
    bool isNeedBackwardTranslate = IsNeedBackwardTranslate(props, targetIndexValue);
    bool isNeedPlayTranslateAnimation = translateAnimationIsRunning_ || isNeedForwardTranslate ||
                                        isNeedBackwardTranslate || AutoLinearAnimationNeedReset(targetPos);
    auto context = GetContext();
    if (context && !isNeedPlayTranslateAnimation && !SupportSwiperCustomAnimation()) {
        auto props = GetLayoutProperty<SwiperLayoutProperty>();
        bool isNeedOffset = (GetLoopIndex(iter->first) == TotalCount() - 1) && !props->GetDisplayCount().has_value() &&
                            !IsLoop() &&
                            LessNotEqual(iter->second.endPos - iter->second.startPos, CalculateVisibleSize());
        float offset = isNeedOffset ? CalculateVisibleSize() - iter->second.endPos + iter->second.startPos : 0.0;
        targetPos -= offset;
        if (propertyAnimationIsRunning_ && targetIndex_ == runningTargetIndex_) {
            // If property animation is running and the target index is the same as the running target index, the
            // animation is not played
            return;
        }
        context->AddAfterLayoutTask(
            [weak = WeakClaim(this), targetPos, velocity = velocity_.value_or(0.0f), nextIndex = iter->first]() {
                auto swiper = weak.Upgrade();
                CHECK_NULL_VOID(swiper);
                swiper->PlayPropertyTranslateAnimation(-targetPos, nextIndex, velocity, false);
                swiper->PlayIndicatorTranslateAnimation(-targetPos, nextIndex);
            });
        runningTargetIndex_ = targetIndex_;
    } else {
        PlayTranslateAnimation(
            currentOffset_, currentOffset_ - targetPos, iter->first, false, velocity_.value_or(0.0f));
    }
}

void SwiperPattern::HandleTargetItemNotFound(
    const RefPtr<SwiperLayoutProperty>& props, int32_t targetIndexValue, const RefPtr<SwiperLayoutAlgorithm>& algo)
{
    if (!itemPosition_.empty() && SwiperUtils::IsStretch(props)) {
        auto firstItem = GetFirstItemInfoInVisibleArea();
        auto targetPos = firstItem.second.startPos +
                         (targetIndexValue - firstItem.first) * (placeItemWidth_.value_or(0.0f) + GetItemSpace());
        PlayTranslateAnimation(
            currentOffset_, currentOffset_ - targetPos, targetIndexValue, false, velocity_.value_or(0.0f));
    } else {
        PlayTranslateAnimation(currentOffset_, currentOffset_ - algo->GetTargetStartPos(), targetIndexValue, false,
            velocity_.value_or(0.0f));
    }
}

bool SwiperPattern::IsNeedForwardTranslate(const RefPtr<SwiperLayoutProperty>& props, int32_t targetIndexValue)
{
    if (!IsLoop()) {
        return false;
    }

    auto lastItemIndex = Positive(props->GetCalculatedNextMargin()) ? targetIndexValue + GetDisplayCount()
                                                                    : targetIndexValue + GetDisplayCount() - 1;
    return itemPosition_.find(lastItemIndex) == itemPosition_.end();
}

bool SwiperPattern::IsNeedBackwardTranslate(const RefPtr<SwiperLayoutProperty>& props, int32_t targetIndexValue)
{
    if (!IsLoop() || targetIndexValue >= currentIndex_) {
        return false;
    }

    auto firstItemIndex = Positive(props->GetCalculatedPrevMargin()) ? targetIndexValue + TotalCount() - 1
                                                                     : targetIndexValue + TotalCount();
    return itemPosition_.find(firstItemIndex) != itemPosition_.end();
}

void SwiperPattern::HandleTabsAncestor()
{
    if (hasTabsAncestor_) {
        for (int32_t index = 0; index < RealTotalCount(); index++) {
            auto childFrameNode = GetCurrentFrameNode(index);
            if (childFrameNode) {
                auto isActive = childFrameNode->IsActive();
                childFrameNode->SetFreeze(!isActive);
            }
        }
    }
}

void SwiperPattern::UpdateLayoutProperties(const RefPtr<SwiperLayoutAlgorithm>& algo)
{
    autoLinearReachBoundary_ = false;
    startMainPos_ = algo->GetStartPosition();
    endMainPos_ = algo->GetEndPosition();
    startIndex_ = algo->GetStartIndex();
    endIndex_ = algo->GetEndIndex();
    cachedItems_ = algo->GetCachedItems();
    layoutConstraint_ = algo->GetLayoutConstraint();
    itemPosition_ = std::move(algo->GetItemPosition());
    currentOffset_ -= algo->GetCurrentOffset();
}

float SwiperPattern::AdjustIgnoreBlankOverScrollOffSet(bool isStartOverScroll) const
{
    if (!NeedEnableIgnoreBlankOffset()) {
        return 0.0f;
    }
    if (isStartOverScroll && NonNegative(ignoreBlankOffset_)) {
        return prevMarginIgnoreBlank_ ? GetPrevMarginWithItemSpace() + ignoreBlankOffset_ : ignoreBlankOffset_;
    }
    if (!isStartOverScroll && NonPositive(ignoreBlankOffset_)) {
        return nextMarginIgnoreBlank_ ? -GetNextMarginWithItemSpace() + ignoreBlankOffset_ : ignoreBlankOffset_;
    }
    return 0.0f;
}

void SwiperPattern::UpdateIgnoreBlankOffsetWithIndex()
{
    if (!NeedEnableIgnoreBlankOffset()) {
        auto lastIgnoreBlankOffset = ignoreBlankOffset_;
        ignoreBlankOffset_ = 0.0f;
        UpdateIgnoreBlankOffsetInMap(lastIgnoreBlankOffset);
        return;
    }

    if (targetIndex_.has_value()) {
        float lastIgnoreBlankOffset = ignoreBlankOffset_;
        if (prevMarginIgnoreBlank_ && targetIndex_.value() == 0) {
            ignoreBlankOffset_ = -GetPrevMarginWithItemSpace();
        } else if (nextMarginIgnoreBlank_ && targetIndex_.value() >= (TotalCount() - GetDisplayCount())) {
            ignoreBlankOffset_ = GetNextMarginWithItemSpace();
        } else {
            ignoreBlankOffset_ = 0.0f;
        }
        UpdateIgnoreBlankOffsetInMap(lastIgnoreBlankOffset);
    }
}

void SwiperPattern::UpdateIgnoreBlankOffsetWithDrag(bool overScrollDirection)
{
    if (!NeedEnableIgnoreBlankOffset()) {
        return;
    }
    float lastIgnoreBlankOffset = ignoreBlankOffset_;
    if (prevMarginIgnoreBlank_ && overScrollDirection) {
        ignoreBlankOffset_ = -GetPrevMarginWithItemSpace();
    } else if (nextMarginIgnoreBlank_ && !overScrollDirection) {
        ignoreBlankOffset_ = GetNextMarginWithItemSpace();
    } else {
        ignoreBlankOffset_ = 0.0f;
    }

    UpdateIgnoreBlankOffsetInMap(lastIgnoreBlankOffset);
}

void SwiperPattern::UpdateIgnoreBlankOffsetInMap(float lastIgnoreBlankOffset)
{
    if (NearEqual(ignoreBlankOffset_, lastIgnoreBlankOffset)) {
        return;
    }

    float adjustOffset = ignoreBlankOffset_ - lastIgnoreBlankOffset;
    for (auto& item : itemPosition_) {
        item.second.startPos -= adjustOffset;
        item.second.endPos -= adjustOffset;
    }
}

bool SwiperPattern::IsAutoLinear() const
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, false);
    return !SwiperUtils::IsStretch(props);
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

void SwiperPattern::FireChangeEvent(int32_t preIndex, int32_t currentIndex, bool isInLayout) const
{
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireChangeEvent(preIndex, currentIndex, isInLayout);
    swiperEventHub->FireIndicatorChangeEvent(currentIndex);
    swiperEventHub->FireChangeDoneEvent(moveDirection_);
    if (swiperController_) {
        swiperController_->FireOnChangeEvent(currentIndex);
    }

    if (jumpIndex_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
    }
}

void SwiperPattern::FireAnimationStartEvent(
    int32_t currentIndex, int32_t nextIndex, const AnimationCallbackInfo& info) const
{
    TAG_LOGI(AceLogTag::ACE_SWIPER, "FireAnimationStartEvent, currentIndex: %{public}d, nextIndex: %{public}d",
        currentIndex, nextIndex);
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireAnimationStartEvent(currentIndex, nextIndex, info);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_START);
}

void SwiperPattern::FireAnimationEndEvent(
    int32_t currentIndex, const AnimationCallbackInfo& info, bool isInterrupt) const
{
    TAG_LOGI(AceLogTag::ACE_SWIPER,
        "FireAnimationEndEvent currentIndex: %{public}d, currentOffset: has_value %{public}d, value %{public}fvp, "
        "isForce: %{public}d",
        currentIndex, info.currentOffset.has_value(), info.currentOffset.value_or(0.0), info.isForceStop);
    if (currentIndex == -1) {
        return;
    }
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    isInterrupt ? swiperEventHub->FireAnimationEndOnForceEvent(currentIndex, info)
                : swiperEventHub->FireAnimationEndEvent(currentIndex, info);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
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

    auto visibleIndex = CalcVisibleIndex();
    auto visibleIndexWithOffset = CalcVisibleIndex(offset);
    std::set<int32_t> unmountIndexs;
    for (auto& item : itemPositionInAnimation_) {
        if (indexsInAnimation_.find(item.first) == indexsInAnimation_.end() &&
            needUnmountIndexs_.find(item.first) == needUnmountIndexs_.end() &&
            visibleIndex.find(item.first) != visibleIndex.end() &&
            visibleIndexWithOffset.find(item.first) == visibleIndexWithOffset.end()) {
            indexsInAnimation_.insert(item.first);
            needUnmountIndexs_.insert(item.first);
            item.second.startPos += offset;
            item.second.endPos += offset;
            unmountIndexs.insert(item.first);
        }
    }
    for (const auto& index : unmountIndexs) {
        auto iter = itemPositionInAnimation_.find(index);
        if (iter == itemPositionInAnimation_.end()) {
            continue;
        }

        OnSwiperCustomAnimationFinish(iter->second.task, index, iter->second.isFinishAnimation);
    }

    FireSwiperCustomAnimationEvent();
}

std::set<int32_t> SwiperPattern::CalcVisibleIndex(float offset) const
{
    auto visibleSize = CalculateVisibleSize();
    auto itemSpace = GetItemSpace();
    auto isLoop = IsLoop();
    auto displayCount = GetDisplayCount();
    auto swipeByGroup = IsSwipeByGroup();
    std::set<int32_t> visibleIndex;

    for (auto& item : itemPosition_) {
        auto index = item.first;
        auto startPos = item.second.startPos + offset;
        auto endPos = item.second.endPos + offset;
        auto itemPosDiff = endPos - startPos + itemSpace;
        auto pageStartIndex = swipeByGroup ? SwiperUtils::ComputePageIndex(index, displayCount) : index;
        auto pageEndIndex = swipeByGroup ? SwiperUtils::ComputePageEndIndex(index, displayCount) : index;
        auto pageStartPos = swipeByGroup ? startPos - itemPosDiff * (index - pageStartIndex) : startPos;
        auto pageEndPos = swipeByGroup ? endPos + itemPosDiff * (pageEndIndex - index) : endPos;

        if (LessOrEqual(pageEndPos, -GetPrevMarginWithItemSpace())) {
            continue;
        }
        if (GreatOrEqual(pageStartPos, visibleSize + GetNextMarginWithItemSpace())) {
            continue;
        }

        if (GreatNotEqual(startPos - itemSpace, -GetPrevMarginWithItemSpace()) &&
            itemPosition_.find(index - 1) == itemPosition_.end() && (isLoop || index > 0)) {
            pageStartIndex = swipeByGroup ? SwiperUtils::ComputePageIndex(index - 1, displayCount) : index - 1;
        }
        if (LessNotEqual(endPos + itemSpace, visibleSize + GetNextMarginWithItemSpace()) &&
            itemPosition_.find(index + 1) == itemPosition_.end() && (isLoop || index < RealTotalCount() - 1)) {
            pageEndIndex = swipeByGroup ? SwiperUtils::ComputePageEndIndex(index + 1, displayCount) : index + 1;
        }
        auto currentIndex = index - 1;
        while (currentIndex >= pageStartIndex && itemPosition_.find(currentIndex) == itemPosition_.end()) {
            visibleIndex.insert(GetLoopIndex(currentIndex));
            currentIndex--;
        }
        currentIndex = index + 1;
        while (currentIndex <= pageEndIndex && itemPosition_.find(currentIndex) == itemPosition_.end()) {
            visibleIndex.insert(GetLoopIndex(currentIndex));
            currentIndex++;
        }
        visibleIndex.insert(GetLoopIndex(index));
    }

    return visibleIndex;
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

        if (LessOrEqual(pageEndPos, NearZero(prevMargin) ? 0.0f : -prevMargin - itemSpace)) {
            continue;
        }
        if (GreatOrEqual(pageStartPos, NearZero(nextMargin) ? visibleSize : visibleSize + nextMargin + itemSpace)) {
            continue;
        }

        if (GreatNotEqual(startPos - itemSpace, NearZero(prevMargin) ? 0.0f : -prevMargin - itemSpace) &&
            itemPosition_.find(index - 1) == itemPosition_.end() && (isLoop || index > 0)) {
            pageStartIndex = swipeByGroup ? SwiperUtils::ComputePageIndex(index - 1, displayCount) : index - 1;
        }
        if (LessNotEqual(
                endPos + itemSpace, NearZero(nextMargin) ? visibleSize : visibleSize + nextMargin + itemSpace) &&
            itemPosition_.find(index + 1) == itemPosition_.end() && (isLoop || index < RealTotalCount() - 1)) {
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
        itemPositionInAnimation_[index] = { startPos, endPos, nullptr };
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
        if (IsHorizontalAndRightToLeft()) {
            offset = Dimension(-item.second.startPos, DimensionUnit::PX).ConvertToVp();
        }
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
            swiper->OnSwiperCustomAnimationFinish(item->second.task, index, true);
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
    CHECK_NULL_VOID(event);
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
}

void SwiperPattern::OnSwiperCustomAnimationFinish(
    CancelableCallback<void()>& task, int32_t index, bool isFinishAnimation)
{
    if (needUnmountIndexs_.find(index) == needUnmountIndexs_.end()) {
        return;
    }
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    if (task) {
        task.Cancel();
    }

    int32_t timeout = 0;
    if (onSwiperCustomContentTransition_ && !isFinishAnimation) {
        timeout = onSwiperCustomContentTransition_->timeout;
    }

    if (timeout == 0) {
        needUnmountIndexs_.erase(index);
        itemPositionInAnimation_.erase(index);
        MarkDirtyNodeSelf();
        return;
    }

    task.Reset([weak = AceType::WeakClaim(this), index] {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->needUnmountIndexs_.erase(index);
        swiper->itemPositionInAnimation_.erase(index);
        swiper->MarkDirtyNodeSelf();
    });
    taskExecutor->PostDelayedTask(task, TaskExecutor::TaskType::UI, timeout, "ArkUISwiperDelayedCustomAnimation");
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

    if (propertyAnimationIsRunning_) {
        StopPropertyTranslateAnimation(isFinishAnimation_);
    }

    StopTranslateAnimation();
    StopFadeAnimation();
    StopSpringAnimationImmediately();
    StopIndicatorAnimation(true);
    jumpIndex_ = index;
    AceAsyncTraceBeginCommercial(0, hasTabsAncestor_ ? APP_TABS_NO_ANIMATION_SWITCH : APP_SWIPER_NO_ANIMATION_SWITCH);
    uiCastJumpIndex_ = index;
    MarkDirtyNodeSelf();
    FireAndCleanScrollingListener();
}

void SwiperPattern::StopSpringAnimationAndFlushImmediately()
{
    if (springAnimationIsRunning_) {
        StopSpringAnimationImmediately();
        currentDelta_ = 0.0f;
        itemPosition_.clear();
        isVoluntarilyClear_ = true;
        jumpIndex_ = currentIndex_;
        MarkDirtyNodeSelf();
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->FlushUITasks();
    }
}

bool SwiperPattern::IsUseCustomAnimation() const
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, false);
    return props->GetIsCustomAnimation().value_or(false);
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
        StopSpringAnimationImmediately();
        jumpIndex_ = currentIndex_;
        MarkDirtyNodeSelf();
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->FlushUITasks();
    }
    StopAutoPlay();
    StopTranslateAnimation();

    StopIndicatorAnimation();
    if (propertyAnimationIsRunning_) {
        StopPropertyTranslateAnimation(isFinishAnimation_);
    }

    targetIndex_ = targetIndex;

    UpdateTabBarAnimationDuration(index);
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

void SwiperPattern::UpdateTabBarAnimationDuration(int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    tabBarPattern->UpdateAnimationDuration();
}

int32_t SwiperPattern::CheckTargetIndex(int32_t targetIndex, bool isForceBackward)
{
    if (!IsAutoLinear()) {
        return targetIndex;
    }
    while (GetLoopIndex(targetIndex) != GetLoopIndex(currentIndex_)) {
        auto currentFrameNode = GetCurrentFrameNode(GetLoopIndex(targetIndex));
        CHECK_NULL_RETURN(currentFrameNode, targetIndex);
        auto props = currentFrameNode->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_RETURN(props, targetIndex);
        if (props->GetVisibility().value_or(VisibleType::VISIBLE) != VisibleType::GONE) {
            return targetIndex;
        }
        if (isForceBackward || currentIndex_ < targetIndex) {
            if (IsHorizontalAndRightToLeft()) {
                --targetIndex;
            } else {
                ++targetIndex;
            }
        } else {
            if (IsHorizontalAndRightToLeft()) {
                ++targetIndex;
            } else {
                --targetIndex;
            }
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
    auto displayCount = GetDisplayCount();
    if (childrenSize <= 0 || displayCount == 0) {
        return;
    }

    auto stepItems = IsSwipeByGroup() ? displayCount : 1;
    auto fromIndex = targetIndex_.value_or(currentIndex_);
    auto nextIndex = fromIndex + stepItems;
    if (fromIndex >= childrenSize - displayCount && !IsLoop()) {
        return;
    }

    StopAutoPlay();
    StopSpringAnimationAndFlushImmediately();
    StopFadeAnimation();
    StopIndicatorAnimation();
    if (propertyAnimationIsRunning_ || translateAnimationIsRunning_) {
        isUserFinish_ = false;
        FinishAnimation();
        if (!ContentWillChange(currentIndex_ + 1)) {
            return;
        }
    }
    moveDirection_ = true;

    if (isVisibleArea_) {
        targetIndex_ = CheckTargetIndex(nextIndex);
        MarkDirtyNodeSelf();
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->FlushUITasks();
    } else {
        SwipeToWithoutAnimation(nextIndex);
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

    if (IsAutoLinear() && static_cast<int32_t>(itemPosition_.size()) == TotalCount() && !autoLinearReachBoundary_) {
        return;
    }

    indicatorDoingAnimation_ = false;
    auto childrenSize = TotalCount();
    auto displayCount = GetDisplayCount();
    if (childrenSize <= 0 || displayCount == 0) {
        return;
    }

    auto stepItems = IsSwipeByGroup() ? displayCount : 1;
    auto fromIndex = targetIndex_.value_or(currentIndex_);
    auto prevIndex = fromIndex - stepItems;
    if (fromIndex <= 0 && !IsLoop()) {
        return;
    }

    StopAutoPlay();
    StopSpringAnimationAndFlushImmediately();
    StopFadeAnimation();
    StopIndicatorAnimation();

    if (propertyAnimationIsRunning_ || translateAnimationIsRunning_) {
        isUserFinish_ = false;
        FinishAnimation();
        if (!ContentWillChange(currentIndex_ - 1)) {
            return;
        }
    }
    moveDirection_ = false;

    if (isVisibleArea_) {
        targetIndex_ = CheckTargetIndex(prevIndex);
        MarkDirtyNodeSelf();
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->FlushUITasks();
    } else {
        SwipeToWithoutAnimation(prevIndex);
    }
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireIndicatorChangeEvent(GetLoopIndex(currentIndex_));
}

void SwiperPattern::ChangeIndex(int32_t index, bool useAnimation)
{
    index = CheckIndexRange(index);
    auto itemCount = TotalCount();
    auto displayCount = GetDisplayCount();
    auto loopCount = itemCount == 0 ? 0 : std::abs(currentIndex_ / itemCount);
    auto targetIndex = currentIndex_ >= 0 ? loopCount * itemCount + index : -(loopCount + 1) * itemCount + index;
    targetIndex = IsSwipeByGroup() ? SwiperUtils::ComputePageIndex(targetIndex, displayCount) : targetIndex;
    if (targetIndex_.has_value() && targetIndex_.value() == targetIndex) {
        return;
    }

    targetIndex = CheckTargetIndex(targetIndex);
    if (useAnimation) {
        if (GetMaxDisplayCount() > 0) {
            SetIndicatorChangeIndexStatus(true);
        }

        SwipeTo(targetIndex);
    } else {
        needFireCustomAnimationEvent_ = translateAnimationIsRunning_;

        if (GetMaxDisplayCount() > 0) {
            SetIndicatorChangeIndexStatus(false);
        }

        SwipeToWithoutAnimation(GetLoopIndex(targetIndex));
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
    StopIndicatorAnimation(true);
    if (propertyAnimationIsRunning_) {
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
    for (const auto& index : indexSet) {
        if (index < 0 || index >= childrenSize) {
            FirePreloadFinishEvent(ERROR_CODE_PARAM_INVALID,
                "BusinessError 401: Parameter error. Each value in indices must be valid index value of child.");
            return;
        }
        validIndexSet.emplace(index);
    }

    if (validIndexSet.empty()) {
        FirePreloadFinishEvent(ERROR_CODE_PARAM_INVALID,
            "BusinessError 401: Parameter error. The parameter indices must be a non-empty array.");
        return;
    }

    auto preloadTask = [weak = WeakClaim(this), indexSet]() {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        auto host = swiperPattern->GetHost();
        CHECK_NULL_VOID(host);
        auto parent = host->GetParent();
        if (AceType::InstanceOf<TabsNode>(parent)) {
            swiperPattern->DoTabsPreloadItems(indexSet);
        } else {
            swiperPattern->DoSwiperPreloadItems(indexSet);
        }

        swiperPattern->FirePreloadFinishEvent(ERROR_CODE_NO_ERROR);
    };

    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(preloadTask, TaskExecutor::TaskType::UI, "ArkUIFirePreloadFinish",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}

void SwiperPattern::FirePreloadFinishEvent(int32_t errorCode, std::string message)
{
    if (swiperController_ && swiperController_->GetPreloadFinishCallback()) {
        auto preloadFinishCallback = swiperController_->GetPreloadFinishCallback();
        swiperController_->SetPreloadFinishCallback(nullptr);
        preloadFinishCallback(errorCode, message);
    }
}

void SwiperPattern::DoTabsPreloadItems(const std::set<int32_t>& indexSet)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto props = host->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(props);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto contentConstraint = props->GetContentLayoutConstraint();
    auto frameSize = OptionalSizeF(geometryNode->GetPaddingSize());
    auto childConstraint = SwiperUtils::CreateChildConstraint(props, frameSize, false);
    for (auto index : indexSet) {
        auto tabContent = GetCurrentFrameNode(index);
        if (!tabContent) {
            continue;
        }
        if (!tabContent->GetChildren().empty()) {
            continue;
        }
        auto tabContentPattern = tabContent->GetPattern<TabContentPattern>();
        if (!tabContentPattern) {
            continue;
        }
        tabContentPattern->BeforeCreateLayoutWrapper();

        for (const auto& child : tabContent->GetChildren()) {
            child->Build(nullptr);
        }
        if (contentConstraint.has_value() && tabContent->GetGeometryNode()) {
            tabContent->GetGeometryNode()->SetParentLayoutConstraint(childConstraint);
            FrameNode::ProcessOffscreenNode(tabContent);
        }
    }
}

void SwiperPattern::BuildForEachChild(const std::set<int32_t>& indexSet, const RefPtr<UINode>& child)
{
    auto childNode = FindForEachNode(child);
    if (!childNode) {
        return;
    }

    auto forEachNode = AceType::DynamicCast<ForEachNode>(childNode.value());
    auto repeatNode = AceType::DynamicCast<RepeatVirtualScrollNode>(childNode.value());
    for (auto index : indexSet) {
        if (forEachNode && forEachNode->GetChildAtIndex(index)) {
            TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper preload item index: %{public}d", index);
            forEachNode->GetChildAtIndex(index)->Build(nullptr);
            continue;
        }

        if (repeatNode) {
            repeatNode->GetFrameChildByIndex(index, true);
        }
    }
}

void SwiperPattern::DoSwiperPreloadItems(const std::set<int32_t>& indexSet)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto targetNode = FindLazyForEachNode(host);
    if (targetNode.has_value()) {
        auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(targetNode.value());
        for (auto index : indexSet) {
            if (lazyForEachNode) {
                lazyForEachNode->GetFrameChildByIndex(index, true);
            }
        }
    }
    const auto& children = host->GetChildren();
    for (const auto& child : children) {
        BuildForEachChild(indexSet, child);
    }
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
        prevFrameAnimationRunning_ = true;

        if (NearZero(translateAnimationEndPos_ - currentOffset_)) {
            AnimationUtils::StopAnimation(translateAnimation_);
            targetIndex_.reset();
        } else {
            AnimationOption option;
            option.SetCurve(Curves::LINEAR);
            option.SetDuration(0);
            translateAnimation_ = AnimationUtils::StartAnimation(option, [weak = WeakClaim(this)]() {
                auto swiper = weak.Upgrade();
                CHECK_NULL_VOID(swiper);
                auto host = swiper->GetHost();
                CHECK_NULL_VOID(host);
                host->UpdateAnimatablePropertyFloat(TRANSLATE_PROPERTY_NAME, swiper->currentOffset_);
            });
        }

        OnTranslateFinish(propertyAnimationIndex_, false, isFinishAnimation_, true);
    }
}

void SwiperPattern::StopSpringAnimationImmediately()
{
    if (!springAnimationIsRunning_) {
        return;
    }
    AnimationOption option;
    option.SetCurve(Curves::LINEAR);
    option.SetDuration(0);
    springAnimation_ = AnimationUtils::StartAnimation(option, [weak = WeakClaim(this)]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        auto host = swiper->GetHost();
        CHECK_NULL_VOID(host);
        host->UpdateAnimatablePropertyFloat(SPRING_PROPERTY_NAME, swiper->currentIndexOffset_);
    });
    OnSpringAnimationFinish();
}

void SwiperPattern::StopSpringAnimation()
{
    if (springAnimationIsRunning_) {
        AnimationUtils::StopAnimation(springAnimation_);
    }
}

void SwiperPattern::StopFadeAnimation()
{
    AnimationUtils::StopAnimation(fadeAnimation_);
    if (fadeAnimationIsRunning_) {
        fadeAnimationIsRunning_ = false;
    }
}

void SwiperPattern::SaveIndicatorProperty(
    const RefPtr<FrameNode>& indicatorNode, SwiperIndicatorType swiperIndicatorType)
{
    if (swiperIndicatorType == SwiperIndicatorType::DOT) {
        SwiperHelper::SaveDotIndicatorProperty(indicatorNode, *this);
    } else if (swiperIndicatorType == SwiperIndicatorType::ARC_DOT) {
        SaveCircleDotIndicatorProperty(indicatorNode);
    } else {
        SwiperHelper::SaveDigitIndicatorProperty(indicatorNode, *this);
    }
}

void SwiperPattern::InitIndicator()
{
    auto swiperNode = GetHost();
    CHECK_NULL_VOID(swiperNode);
    RefPtr<FrameNode> indicatorNode;
    auto indicatorType = GetIndicatorType();
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!HasIndicatorNode()) {
        if (!IsShowIndicator()) {
            return;
        }
        if (layoutProperty->GetIndicatorTypeValue(SwiperIndicatorType::DOT) == SwiperIndicatorType::ARC_DOT) {
            indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, CreateIndicatorId(),
                []() { return AceType::MakeRefPtr<ArcSwiperIndicatorPattern>(); });
        } else {
            indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, CreateIndicatorId(),
                []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        }
        swiperNode->AddChild(indicatorNode);
    } else {
        indicatorNode =
            DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(swiperNode->GetChildIndexById(GetIndicatorId())));
        CHECK_NULL_VOID(indicatorNode);
        if (!IsShowIndicator()) {
            RemoveIndicatorNode();
            return;
        }
        if (indicatorType == SwiperIndicatorType::DIGIT && lastSwiperIndicatorType_ == SwiperIndicatorType::DOT) {
            RemoveIndicatorNode();
            indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, CreateIndicatorId(),
                [indicatorType]() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(indicatorType); });
            swiperNode->AddChild(indicatorNode);
        }
    }
    lastSwiperIndicatorType_ = indicatorType;
    CHECK_NULL_VOID(indicatorNode);
    SaveIndicatorProperty(indicatorNode, layoutProperty->GetIndicatorTypeValue(SwiperIndicatorType::DOT));

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

SwiperPattern::PanEventFunction SwiperPattern::ActionStartTask()
{
    return [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper drag start. SourceTool: %{public}d", info.GetSourceTool());
        if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
            pattern->isFirstAxisAction_ = true;
            return;
        }
        pattern->FireAndCleanScrollingListener();
        pattern->HandleDragStart(info);
        // notify scrollStart upwards
        pattern->NotifyParentScrollStart(weak, pattern->direction_ == Axis::HORIZONTAL
                                                    ? info.GetGlobalLocation().GetX()
                                                    : info.GetGlobalLocation().GetY());
    };
}

SwiperPattern::PanEventFunction SwiperPattern::ActionUpdateTask()
{
    return [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto infoChecked = info;
        // Reverse velocity and delta when receiving.
        if (pattern->IsHorizontalAndRightToLeft()) {
            infoChecked.SetMainVelocity(-info.GetMainVelocity());
            infoChecked.SetMainDelta(-info.GetMainDelta());
        }
        if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
            if (pattern->isFirstAxisAction_) {
                pattern->isFirstAxisAction_ = false;
            } else if (pattern->pageFlipMode_ == PageFlipMode::SINGLE &&
                       (pattern->propertyAnimationIsRunning_ || pattern->translateAnimationIsRunning_)) {
                return;
            }
            if (!pattern->CheckSwiperPanEvent(infoChecked.GetMainDelta())) {
                return;
            }
            if (GreatNotEqual(infoChecked.GetMainDelta(), 0.0)) {
                pattern->ShowPrevious();
            } else if (LessNotEqual(infoChecked.GetMainDelta(), 0.0)) {
                pattern->ShowNext();
            }
        } else {
            pattern->HandleDragUpdate(infoChecked);
        }
    };
}

SwiperPattern::PanEventFunction SwiperPattern::ActionEndTask()
{
    return [weak = WeakClaim(this)](const GestureEvent& info) {
        TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper drag end. Velocity: %{public}f px/s, SourceTool: %{public}d",
            info.GetMainVelocity(), info.GetSourceTool());
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
            pattern->InitIndexCanChangeMap();
            return;
        }
        bool isUsingTouchPad =
            (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::TOUCHPAD);
        auto velocity =
            isUsingTouchPad ? info.GetMainVelocity() * pattern->GetVelocityCoefficient() : info.GetMainVelocity();
        // Reverse velocity when receiving.
        pattern->HandleDragEnd(pattern->IsHorizontalAndRightToLeft() ? -velocity : velocity);
        pattern->InitIndexCanChangeMap();
    };
}

void SwiperPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (direction_ == GetDirection() && panEvent_) {
        return;
    }
    // fade offset need to be reset when is still dragging
    if (direction_ != GetDirection()) {
        fadeOffset_ = 0.f;
    }
    direction_ = GetDirection();

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper drag cancel");
            pattern->HandleDragEnd(0.0);
            pattern->InitIndexCanChangeMap();
        }
    };

    AddPanEvent(gestureHub, ActionStartTask(), ActionUpdateTask(), ActionEndTask(), std::move(actionCancelTask));
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

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto lastFocusNode = focusHub->GetLastWeakFocusNode().Upgrade();
    CHECK_NULL_VOID(lastFocusNode);
    for (const auto& item : itemPosition_) {
        auto itemNode = GetCurrentFrameNode(item.first);
        if (!itemNode) {
            continue;
        }
        if (itemNode->GetFirstFocusHubChild() == lastFocusNode) {
            currentFocusIndex_ = item.first;
            return;
        }
    }
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
    auto swiperHost = GetHost();
    CHECK_NULL_RETURN(swiperHost, true);
    auto swiperFocusHub = swiperHost->GetFocusHub();
    CHECK_NULL_RETURN(swiperFocusHub, true);
    bool ret = true;
    swiperFocusHub->AnyChildFocusHub([&ret](const RefPtr<FocusHub>& child) {
        if (!child || !child->IsCurrentFocus()) {
            return false;
        }
        auto frameName = child->GetFrameName();
        if (frameName == V2::SWIPER_INDICATOR_ETS_TAG || frameName == V2::SWIPER_RIGHT_ARROW_ETS_TAG ||
            frameName == V2::SWIPER_LEFT_ARROW_ETS_TAG) {
            ret = false;
        }
        return true;
    });
    return ret;
}

bool SwiperPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if ((GetDirection() == Axis::HORIZONTAL && event.code == (IsHorizontalAndRightToLeft() ? KeyCode::KEY_DPAD_RIGHT :
        KeyCode::KEY_DPAD_LEFT)) || (GetDirection() == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_UP)) {
        auto onlyFlushFocus = IsContentFocused() && GetDisplayCount() > 1 && currentFocusIndex_ > currentIndex_;
        if (onlyFlushFocus) {
            currentFocusIndex_ =
                IsLoop() ? currentFocusIndex_ - 1 : std::clamp(currentFocusIndex_ - 1, 0, TotalCount() - 1);
            FlushFocus(GetCurrentFrameNode(currentFocusIndex_));
        } else {
            ShowPrevious();
            currentFocusIndex_ =
                IsLoop() ? currentFocusIndex_ - 1 : std::clamp(currentFocusIndex_ - 1, 0, TotalCount() - 1);
        }

        return true;
    }
    if ((GetDirection() == Axis::HORIZONTAL && event.code == (IsHorizontalAndRightToLeft() ? KeyCode::KEY_DPAD_LEFT :
        KeyCode::KEY_DPAD_RIGHT)) || (GetDirection() == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_DOWN)) {
        auto onlyFlushFocus =
            IsContentFocused() && GetDisplayCount() > 1 && currentFocusIndex_ < currentIndex_ + GetDisplayCount() - 1;
        if (onlyFlushFocus) {
            currentFocusIndex_ =
                IsLoop() ? currentFocusIndex_ + 1 : std::clamp(currentFocusIndex_ + 1, 0, TotalCount() - 1);
            FlushFocus(GetCurrentFrameNode(currentFocusIndex_));
        } else {
            ShowNext();
            currentFocusIndex_ =
                IsLoop() ? currentFocusIndex_ + 1 : std::clamp(currentFocusIndex_ + 1, 0, TotalCount() - 1);
        }

        return true;
    }
    return false;
}

void SwiperPattern::StopAutoPlay()
{
    if (IsAutoPlay()) {
        isInAutoPlay_ = false;
        translateTask_.Cancel();
    }
}

void SwiperPattern::StartAutoPlay()
{
    if (NeedAutoPlay() && !translateAnimationIsRunning_ && !propertyAnimationIsRunning_) {
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
            ResetCurrentFrameNodeAnimation();
            return;
        }
    }
    if (!IsLoop() && GetEdgeEffect() != EdgeEffect::SPRING && IsOutOfBoundary(offset)) {
        offset = IsOutOfStart(offset) ? -itemPosition_.begin()->second.startPos
                                      : CalculateVisibleSize() - itemPosition_.rbegin()->second.endPos;
    }
    currentDelta_ -= offset;
    currentIndexOffset_ += offset;
    if (isDragging_ || childScrolling_) {
        AnimationCallbackInfo callbackInfo;
        callbackInfo.currentOffset =
            GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
        if (IsHorizontalAndRightToLeft()) {
            callbackInfo.currentOffset =
                GetCustomPropertyOffset() + Dimension(-currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
        }
        bool skipGestureSwipe = TotalCount() == 1 && GetEdgeEffect() == EdgeEffect::NONE;
        if (!skipGestureSwipe) {
            FireGestureSwipeEvent(GetLoopIndex(gestureSwipeIndex_), callbackInfo);
        }
    }
    HandleSwiperCustomAnimation(-currentDelta_);
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
                auto realOffset = IsOutOfStart(offset) ? -itemPosition_.begin()->second.startPos
                                                       : CalculateVisibleSize() - itemPosition_.rbegin()->second.endPos;
                currentDelta_ -= realOffset;
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
    bool outOfBounds = IsOutOfBoundary(offset);
    if (!outOfBounds) {
        springOffset_ = 0.0f;
        return false;
    }

    ResetParentNodeColor();
    auto visibleSize = CalculateVisibleSize();
    if (LessOrEqual(visibleSize, 0.0)) {
        return true;
    }
    auto currentRealOffset = springOffset_ * SwiperHelper::CalculateFriction(std::abs(springOffset_ / visibleSize));
    auto delta = 0.0f;
    if (IsOutOfBoundary()) {
        springOffset_ += offset;
    } else {
        if (offset > 0) {
            springOffset_ = itemPosition_.begin()->second.startPos + offset + AdjustIgnoreBlankOverScrollOffSet(true);
        } else {
            springOffset_ =
                itemPosition_.rbegin()->second.endPos + offset - visibleSize + AdjustIgnoreBlankOverScrollOffSet(false);
        }
        delta = offset - springOffset_;
    }
    if (std::abs(springOffset_) > visibleSize) {
        springOffset_ = springOffset_ > 0 ? visibleSize : -visibleSize;
    }
    auto realOffset = springOffset_ * SwiperHelper::CalculateFriction(std::abs(springOffset_ / visibleSize));
    delta += (realOffset - currentRealOffset);
    currentDelta_ -= delta;
    currentIndexOffset_ += delta;
    AnimationCallbackInfo callbackInfo;
    callbackInfo.currentOffset =
        GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    if (IsHorizontalAndRightToLeft()) {
        callbackInfo.currentOffset =
            GetCustomPropertyOffset() + Dimension(-currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    }

    FireGestureSwipeEvent(GetLoopIndex(gestureSwipeIndex_), callbackInfo);
    HandleSwiperCustomAnimation(delta);
    MarkDirtyNodeSelf();
    return true;
}

bool SwiperPattern::FadeOverScroll(float offset)
{
    if (IsOutOfBoundary(fadeOffset_ + offset)) {
        if (!IsVisibleChildrenSizeLessThanSwiper() && NearZero(fadeOffset_)) {
            UpdateIgnoreBlankOffsetWithDrag(IsOutOfStart(offset));
            auto realOffset = IsOutOfStart(offset) ? -itemPosition_.begin()->second.startPos
                                                   : CalculateVisibleSize() - itemPosition_.rbegin()->second.endPos;
            currentDelta_ -= realOffset;
            offset -= realOffset;
            HandleSwiperCustomAnimation(realOffset);
        }
        fadeOffset_ += offset;
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        MarkDirtyNodeSelf();
        return true;
    }
    fadeOffset_ = 0.0f;
    return false;
}

bool SwiperPattern::IsHorizontalAndRightToLeft() const
{
    auto host = GetHost();
    if (hasTabsAncestor_ && host) {
        host = AceType::DynamicCast<FrameNode>(host->GetParent());
    }
    CHECK_NULL_RETURN(host, false);
    CHECK_NULL_RETURN(host->GetLayoutProperty(), false);
    return GetDirection() == Axis::HORIZONTAL &&
           host->GetLayoutProperty()->GetNonAutoLayoutDirection() == TextDirection::RTL;
}

TextDirection SwiperPattern::GetNonAutoLayoutDirection() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, TextDirection::LTR);
    CHECK_NULL_RETURN(host->GetLayoutProperty(), TextDirection::LTR);
    return host->GetLayoutProperty()->GetNonAutoLayoutDirection();
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

void SwiperPattern::CheckMarkDirtyNodeForRenderIndicator(float additionalOffset, std::optional<int32_t> nextIndex)
{
    additionalOffset = IsHorizontalAndRightToLeft() ? -additionalOffset : additionalOffset;
    if (!HasIndicatorNode()) {
        return;
    }
    auto child = GetCommonIndicatorNode();
    CHECK_NULL_VOID(child);

    if (!IsIndicator(child->GetTag())) {
        return;
    }

    int32_t preFirstIndex = currentFirstIndex_;
    auto currentPageStatus = (IsHorizontalAndRightToLeft() && GetMaxDisplayCount() > 0)
                                 ? CalcCurrentPageStatusOnRTL(additionalOffset)
                                 : CalcCurrentPageStatus(additionalOffset);
    float currentTurnPageRate = currentPageStatus.first;
    currentFirstIndex_ = currentPageStatus.second;

    groupTurnPageRate_ =
        (IsSwipeByGroup() && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN) ?
        CalculateGroupTurnPageRate(additionalOffset) : 0.0f);
    currentFirstIndex_ = nextIndex.value_or(currentFirstIndex_);
    UpdateNextValidIndex();
    currentFirstIndex_ = GetLoopIndex(currentFirstIndex_);
    auto isRtl = IsHorizontalAndRightToLeft() && GetMaxDisplayCount() <= 0;
    isRtl ? CalculateGestureStateOnRTL(additionalOffset, currentTurnPageRate, preFirstIndex)
          : CalculateGestureState(additionalOffset, currentTurnPageRate, preFirstIndex);
    turnPageRate_ = (currentTurnPageRate == FLT_MAX ? turnPageRate_ : currentTurnPageRate);
    turnPageRate_ = isRtl ? std::abs(turnPageRate_) - 1.0f : turnPageRate_;
    touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    CheckMarkForIndicatorBoundary();
    isRtl ? HandleTouchBottomLoopOnRTL() : HandleTouchBottomLoop();

    if (IsVisibleChildrenSizeLessThanSwiper()) {
        turnPageRate_ = 0.0f;
        gestureState_ = GestureState::GESTURE_STATE_NONE;
        touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    }

    if (!indicatorDoingAnimation_) {
        child->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    if (GetLoopIndex(currentIndex_) != currentFirstIndex_) {
        auto swiperEventHub = GetEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(swiperEventHub);
        swiperEventHub->FireIndicatorChangeEvent(currentFirstIndex_);
    }
}

void SwiperPattern::CheckMarkForIndicatorBoundary()
{
    bool isRtl = IsHorizontalAndRightToLeft();

    auto startIndex = isRtl ? TotalCount() - 1 : 0;
    auto endIndex = isRtl ? 0 : TotalCount() - 1;
    if (!IsLoop() && ((currentFirstIndex_ == startIndex && GreatNotEqualCustomPrecision(turnPageRate_, 0.0f)) ||
                         (currentFirstIndex_ == endIndex && LessNotEqualCustomPrecision(turnPageRate_, 0.0f)))) {
        return;
    }
}

float SwiperPattern::CalculateGroupTurnPageRate(float additionalOffset)
{
    auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
    auto firstItemLength = firstItemInfoInVisibleArea.second.endPos - firstItemInfoInVisibleArea.second.startPos;
    auto firstItemIndex = firstItemInfoInVisibleArea.first;
    auto displayCount = GetDisplayCount();
    auto itemSpace = GetItemSpace();
    auto swiperWidth = CalculateVisibleSize();
    auto totalCount = TotalCount();
    float groupTurnPageRate = FLT_MAX;
    float currentStartPos = 0.0f;

    if (swiperWidth == 0 || displayCount == 0 || totalCount == 0) {
        return 0.0f;
    }
    if (itemPosition_.empty() || itemPosition_.find(firstItemIndex) == itemPosition_.end()) {
        return 0.0f;
    }
    if (firstItemIndex >= currentIndex_) {
        currentStartPos = itemPosition_[firstItemIndex].startPos -
            (itemSpace + firstItemLength) * (firstItemIndex - currentIndex_);

        if (currentStartPos > 0) {
            return 0.0f;
        }
        if (!IsLoop() && firstItemIndex % totalCount >= totalCount - displayCount) {
            return 0.0f;
        }

        groupTurnPageRate = NearZero(swiperWidth) ? 0 : (currentStartPos + additionalOffset) / swiperWidth;
    } else if (firstItemIndex < currentIndex_) {
        currentStartPos = itemPosition_[firstItemIndex].startPos - (itemSpace + firstItemLength) *
            (displayCount - ((currentIndex_ - firstItemIndex) - 1) % displayCount - 1);

        if (currentStartPos > 0) {
            return 0.0f;
        }

        groupTurnPageRate = NearZero(swiperWidth) ? 0 :(currentStartPos + additionalOffset) / swiperWidth;
    } else {
        groupTurnPageRate = 0.0f;
    }

    if (IsHorizontalAndRightToLeft()) {
        groupTurnPageRate = std::abs(groupTurnPageRate) <= 1.0f ? std::abs(groupTurnPageRate) - 1.0f : 0.0f;
    }

    return (groupTurnPageRate == FLT_MAX ? groupTurnPageRate_ : groupTurnPageRate);
}

std::pair<int32_t, int32_t> SwiperPattern::CalculateStepAndItemCount() const
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
        return { RealTotalCount(), 1 };
    }

    auto displaycount = GetDisplayCount();

    int32_t itemCount = (IsSwipeByGroup() ? TotalCount() : DisplayIndicatorTotalCount());
    int32_t step = (IsSwipeByGroup() ? displaycount : 1);

    return { itemCount, step };
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

bool SwiperPattern::InsideIndicatorRegion(const TouchLocationInfo& locationInfo)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto indicatorNode = DynamicCast<FrameNode>(host->GetChildAtIndex(host->GetChildIndexById(GetIndicatorId())));
    if (!indicatorNode || !IsIndicator(indicatorNode->GetTag())) {
        return false;
    }
    auto geometryNode = indicatorNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto hotRegion = geometryNode->GetFrameRect();
    auto touchPoint = PointF(static_cast<float>(locationInfo.GetLocalLocation().GetX()),
        static_cast<float>(locationInfo.GetLocalLocation().GetY()));
    return hotRegion.IsInRegion(touchPoint);
}

void SwiperPattern::UpdateOverlongForceStopPageRate(float forceStopPageRate)
{
    CHECK_NULL_VOID(updateOverlongForceStopPageRateFunc_);
    updateOverlongForceStopPageRateFunc_(forceStopPageRate);
}

void SwiperPattern::HandleTouchDown(const TouchLocationInfo& locationInfo)
{
    ACE_SCOPED_TRACE("Swiper HandleTouchDown");
    TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper HandleTouchDown");
    isTouchDown_ = true;
    isTouchDownOnOverlong_ = true;
    if (InsideIndicatorRegion(locationInfo)) {
        return;
    }

    if (childScrolling_) {
        // Even if the child fails to notify scrollEnd, we reset childScrolling_ flag on TouchDown to ensure its
        // value is correct.
        childScrolling_ = false;
    }

    if (!stopWhenTouched_) {
        return;
    }
    auto isOverlongIndicator = GetMaxDisplayCount() > 0;
    if (!isOverlongIndicator) {
        StopIndicatorAnimation(true);
    }

    if (propertyAnimationIsRunning_) {
        StopPropertyTranslateAnimation(isFinishAnimation_);
    }

    if (isOverlongIndicator) {
        UpdateOverlongForceStopPageRate(CalcCurrentTurnPageRate());
        StopIndicatorAnimation(true);
    }

    indicatorDoingAnimation_ = false;
    // Stop translate animation when touch down.
    if (translateAnimationIsRunning_) {
        StopTranslateAnimation();
    }

    if (springAnimationIsRunning_) {
        AnimationUtils::PauseAnimation(springAnimation_);
        isTouchDownSpringAnimation_ = true;
    }

    AnimationUtils::PauseAnimation(fadeAnimation_);
    if (fadeAnimationIsRunning_) {
        isTouchDownFadeAnimation_ = true;
    }

    // Stop auto play when touch down.
    StopAutoPlay();
}

void SwiperPattern::HandleTouchUp()
{
    ACE_SCOPED_TRACE("Swiper HandleTouchUp");
    TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper HandleTouchUp");
    isTouchDown_ = false;
    isTouchDownOnOverlong_ = false;
    auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
    if (!isDragging_ && !childScrolling_ && !NearZero(firstItemInfoInVisibleArea.second.startPos) &&
        !springAnimationIsRunning_) {
        UpdateAnimationProperty(0.0);
    }

    if (springAnimationIsRunning_ && isTouchDownSpringAnimation_) {
        isTouchDownSpringAnimation_ = false;
        AnimationUtils::ResumeAnimation(springAnimation_);
    }

    if (fadeAnimationIsRunning_ && isTouchDownFadeAnimation_) {
        isTouchDownFadeAnimation_ = false;
        AnimationUtils::ResumeAnimation(fadeAnimation_);
    }

    if (!isDragging_) {
        StartAutoPlay();
    }

    if (GetMaxDisplayCount() > 0) {
        UpdateOverlongForceStopPageRate(FLT_MAX);
    }
}

void SwiperPattern::HandleDragStart(const GestureEvent& info)
{
    if (!hasTabsAncestor_) {
        PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_SWIPER_SCROLL, PerfActionType::FIRST_MOVE, "");
    } else {
        AceAsyncTraceBeginCommercial(0, APP_TABS_SCROLL);
    }
    UpdateDragFRCSceneInfo(info.GetMainVelocity(), SceneStatus::START);
    StopAnimationOnScrollStart(
        info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::TOUCHPAD, true);
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
    isTouchDownOnOverlong_ = true;
    mainDeltaSum_ = 0.0f;
    ResetAnimationParam();
    // in drag process, close lazy feature.
    SetLazyLoadFeature(false);
}

void SwiperPattern::StopAnimationOnScrollStart(bool flushImmediately, bool stopLongPointAnimation)
{
    if (propertyAnimationIsRunning_) {
        StopPropertyTranslateAnimation(isFinishAnimation_);
    }
    StopIndicatorAnimation(stopLongPointAnimation);
    StopTranslateAnimation();
    StopFadeAnimation();
    if (flushImmediately) {
        StopSpringAnimationAndFlushImmediately();
    } else {
        StopSpringAnimationImmediately();
    }
}

void SwiperPattern::HandleDragUpdate(const GestureEvent& info)
{
    isTouchDownOnOverlong_ = true;
    auto velocity = info.GetMainVelocity();
    UpdateDragFRCSceneInfo(velocity, SceneStatus::RUNNING);
    UpdateNodeRate();
    if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::TOUCHPAD) {
        isTouchPad_ = true;
    }

    PointF dragPoint(
        static_cast<float>(info.GetGlobalLocation().GetX()), static_cast<float>(info.GetGlobalLocation().GetY()));
    NGGestureRecognizer::Transform(dragPoint, GetHost(), true, info.GetIsPostEventResult(), info.GetPostEventNodeId());
    if (IsOutOfHotRegion(dragPoint)) {
        isTouchPad_ = false;
        return;
    }

    auto mainDelta = static_cast<float>(info.GetMainDelta());
    ProcessDelta(mainDelta, contentMainSize_, mainDeltaSum_);
    mainDeltaSum_ += mainDelta;

    if (IsAutoLinear() && AutoLinearIsOutOfBoundary(static_cast<float>(mainDelta))) {
        return;
    }

    if (propertyAnimationIsRunning_) {
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
    } else {
        AceAsyncTraceEndCommercial(0, APP_TABS_SCROLL);
    }
    isTouchDown_ = false;
    isTouchDownOnOverlong_ = false;
    if (!CheckSwiperPanEvent(dragVelocity)) {
        dragVelocity = 0.0;
    }
    if (!childScrolling_) {
        UpdateDragFRCSceneInfo(dragVelocity, SceneStatus::END);
    }
    const auto& addEventCallback = swiperController_->GetAddTabBarEventCallback();
    if (addEventCallback) {
        addEventCallback();
    }

    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->FlushUITasks();
    if (itemPosition_.empty()) {
        return;
    }

    if (IsAutoLinear() && AutoLinearIsOutOfBoundary(0.0f)) {
        return;
    }

    if (CheckDragOutOfBoundary(dragVelocity)) {
        return;
    }

    UpdateAnimationProperty(static_cast<float>(dragVelocity));
    // nested and reached end (but not out of bounds), need to pass velocity to parent scrollable
    auto parent = GetNestedScrollParent();
    if (NearZero(GetDistanceToEdge())) {
        ResetCurrentFrameNodeAnimation();
    }
    if (!IsLoop() && parent && NearZero(GetDistanceToEdge())) {
        parent->HandleScrollVelocity(dragVelocity);
        StartAutoPlay();
    } else {
        NotifyParentScrollEnd();
    }
    if (pipeline) {
        pipeline->FlushUITasks();
        pipeline->FlushMessages();
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
    const auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateIndexWithoutMeasure(GetLoopIndex(currentIndex_));
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
    auto dragThresholdFlag = dragForward ? dragDistance > swiperWidth / swiperProportion_ :
        dragDistance < swiperWidth / swiperProportion_;
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

float SwiperPattern::GetVelocityCoefficient()
{
    auto pipelineContext = GetContext();
    CHECK_NULL_RETURN(pipelineContext, 1);
    auto swiperTheme = pipelineContext->GetTheme<SwiperTheme>();
    CHECK_NULL_RETURN(swiperTheme, 1);
    auto velocityCoefficient = swiperTheme->GetTouchPadVelocityCoefficient();
    return velocityCoefficient;
}

int32_t SwiperPattern::ComputeNextIndexInSinglePage(float velocity, bool onlyDistance) const
{
    auto firstItemInfo = GetFirstItemInfoInVisibleArea();
    auto swiperWidthHalf = (firstItemInfo.second.endPos - firstItemInfo.second.startPos) / swiperProportion_;
    if (LessOrEqual(swiperWidthHalf, 0)) {
        return currentIndex_;
    }
    // if direction is true, expected index to decrease by 1
    bool direction = Positive(velocity);
    bool overTurnPageVelocity =
        !onlyDistance && (std::abs(velocity) > (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)
                                                       ? NEW_MIN_TURN_PAGE_VELOCITY
                                                       : MIN_TURN_PAGE_VELOCITY));

    auto firstIndex = firstItemInfo.first;
    auto baseIndex = -firstItemInfo.second.startPos < swiperWidthHalf ? firstIndex : firstIndex + 1;
    if (overTurnPageVelocity) {
        return direction ? baseIndex - 1 : baseIndex + 1;
    }
    return baseIndex;
}

int32_t SwiperPattern::ComputeNextIndexByVelocity(float velocity, bool onlyDistance) const
{
#ifdef SUPPORT_DIGITAL_CROWN
    if (IsCrownSpring() && velocity == 0.0f) {
        return currentIndex_;
    }
#endif
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
        direction ? dragDistance > firstItemLength / swiperProportion_ :
        firstItemInfoInVisibleArea.second.endPos < firstItemLength / swiperProportion_;
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
        nextIndex =
            std::clamp(ComputeNextIndexInSinglePage(velocity, onlyDistance), currentIndex_ - 1, currentIndex_ + 1);
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
    const bool noneOutOfBoundary =
        (itemPosition_.begin()->first == 0 || itemPosition_.rbegin()->first == TotalCount() - 1) &&
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
            FireWillShowEvent(nextIndex_);
            FireWillHideEvent(currentIndex_);

            UpdateCurrentIndex(nextIndex);
            UpdateCurrentFocus();
            OnIndexChange();
            oldIndex_ = currentIndex_;
        }

        if (edgeEffect == EdgeEffect::NONE) {
            auto parent = GetNestedScrollParent();
            const bool isForward = NonPositive(dragVelocity);
            if (parent && GetNestedScroll().NeedParent(isForward)) {
                parent->HandleScrollVelocity(dragVelocity);
            }
            StartAutoPlay();
            UpdateItemRenderGroup(false);
            return true;
        }
    }

    return false;
}

void SwiperPattern::UpdateTranslateForCaptureNode(const OffsetF& offset, bool cancel)
{
    CHECK_NULL_VOID(hasCachedCapture_);
    auto leftCaptureNode = GetLeftCaptureNode();
    CHECK_NULL_VOID(leftCaptureNode);
    auto rightCaptureNode = GetRightCaptureNode();
    CHECK_NULL_VOID(rightCaptureNode);
    auto leftRenderContext = leftCaptureNode->GetRenderContext();
    CHECK_NULL_VOID(leftRenderContext);
    auto rightRenderContext = rightCaptureNode->GetRenderContext();
    CHECK_NULL_VOID(rightRenderContext);
    if (cancel) {
        leftRenderContext->CancelTranslateXYAnimation();
        rightRenderContext->CancelTranslateXYAnimation();
    } else {
        leftRenderContext->UpdateTranslateInXY(offset);
        rightRenderContext->UpdateTranslateInXY(offset);
        captureFinalOffset_ = offset;
    }
}

void SwiperPattern::UpdateFinalTranslateForSwiperItem(const SwiperLayoutAlgorithm::PositionMap& itemPosition)
{
    for (const auto& item : itemPosition) {
        auto frameNode = item.second.node;
        if (!frameNode) {
            continue;
        }
        auto renderContext = frameNode->GetRenderContext();
        if (!renderContext) {
            continue;
        }
        renderContext->UpdateTranslateInXY(item.second.finalOffset);
    }
}

void SwiperPattern::UpdateTranslateForSwiperItem(SwiperLayoutAlgorithm::PositionMap& itemPosition,
    const OffsetF& offset, bool cancel)
{
    for (auto& item : itemPosition) {
        auto frameNode = item.second.node;
        if (!frameNode) {
            continue;
        }
        auto renderContext = frameNode->GetRenderContext();
        if (!renderContext) {
            continue;
        }
        if (cancel) {
            renderContext->CancelTranslateXYAnimation();
        } else {
            renderContext->UpdateTranslateInXY(offset);
            item.second.finalOffset = offset;
        }
    }
}

void SwiperPattern::PlayPropertyTranslateAnimation(
    float translate, int32_t nextIndex, float velocity, bool stopAutoPlay)
{
    if (NearZero(translate)) {
        SetIndicatorChangeIndexStatus(false, GetLoopIndex(currentIndex_));
        OnAnimationTranslateZero(nextIndex, stopAutoPlay);
        return;
    }

    AnimationOption option;
    option.SetDuration(GetDuration());
    auto iter = frameRateRange_.find(SwiperDynamicSyncSceneType::ANIMATE);
    if (iter != frameRateRange_.end()) {
        TAG_LOGI(AceLogTag::ACE_SWIPER,
            "Property translate animation frame rate range: {min: %{public}d, max: %{public}d, expected: %{public}d}",
            iter->second->min_, iter->second->max_, iter->second->preferred_);
        iter->second->componentScene_ = COMPONENT_SWIPER_FLING;
        option.SetFrameRateRange(iter->second);
    } else {
        option.SetFrameRateRange(SWIPER_DEFAULT_FRAME_RATE);
    }
    motionVelocity_ = velocity / translate;
    auto curve = GetCurveIncludeMotion();
    auto minimumAmplitudeRatio = DEFAULT_MINIMUM_AMPLITUDE_PX / translate;
    if (InstanceOf<InterpolatingSpring>(curve) &&
        LessNotEqualCustomPrecision(
            minimumAmplitudeRatio, InterpolatingSpring::DEFAULT_INTERPOLATING_SPRING_AMPLITUDE_RATIO)) {
        auto interpolatingSpring = AceType::DynamicCast<InterpolatingSpring>(curve);
        interpolatingSpring->UpdateMinimumAmplitudeRatio(minimumAmplitudeRatio);
    }
    option.SetCurve(curve);
    option.SetFinishCallbackType(GetFinishCallbackType());
    OffsetF offset;
    if (GetDirection() == Axis::HORIZONTAL) {
        offset.AddX(translate);
    } else {
        offset.AddY(translate);
    }
    if (propertyAnimationIsRunning_) {
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
        if (swiper->isInAutoPlay_) {
            ResSchedReport::GetInstance().ResSchedDataReport("auto_play_off");
        }
#endif
        if (!swiper->hasTabsAncestor_) {
            PerfMonitor::GetPerfMonitor()->End(PerfConstants::APP_SWIPER_FLING, true);
        } else {
            AceAsyncTraceEndCommercial(0, APP_TABS_FLING);
        }
        swiper->OnPropertyTranslateAnimationFinish(offset);
    };
    // initial translate info use final offset
    UpdateFinalTranslateForSwiperItem(itemPosition_);
    UpdateTranslateForCaptureNode(captureFinalOffset_);
    auto adOffset = offset;
    if (IsHorizontalAndRightToLeft()) {
        if (GetDirection() == Axis::HORIZONTAL) {
            adOffset.SetX(-adOffset.GetX());
        } else {
            adOffset.SetY(-adOffset.GetY());
        }
    }
    // property callback will call immediately.
    auto propertyUpdateCallback = [swiper = WeakClaim(this), offset = adOffset]() {
        auto swiperPattern = swiper.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
#ifdef OHOS_PLATFORM
        if (swiperPattern->isInAutoPlay_) {
            ResSchedReport::GetInstance().ResSchedDataReport("auto_play_on");
        }
#endif
        if (!swiperPattern->hasTabsAncestor_) {
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_SWIPER_FLING, PerfActionType::LAST_UP, "");
        } else {
            AceAsyncTraceBeginCommercial(0, APP_TABS_FLING);
        }
        TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper start property animation with offsetX: %{public}f, offsetY: %{public}f",
            offset.GetX(), offset.GetY());
        ACE_SCOPED_TRACE_COMMERCIAL("%s start property animation, X: %f, Y: %f",
            swiperPattern->hasTabsAncestor_ ? V2::TABS_ETS_TAG : V2::SWIPER_ETS_TAG, offset.GetX(), offset.GetY());
        swiperPattern->UpdateTranslateForSwiperItem(swiperPattern->itemPosition_, offset);
        swiperPattern->itemPositionInAnimation_ = swiperPattern->itemPosition_;
        swiperPattern->UpdateTranslateForCaptureNode(offset);
    };
    propertyAnimationIsRunning_ = true;
    propertyAnimationIndex_ = nextIndex;
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost(), option);
    AnimationUtils::Animate(option, propertyUpdateCallback, finishCallback);
    AnimationCallbackInfo info;
    info.velocity = Dimension(velocity, DimensionUnit::PX).ConvertToVp();
    info.currentOffset = GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    info.targetOffset = GetCustomPropertyTargetOffset() - Dimension(translate, DimensionUnit::PX).ConvertToVp();
    if (IsHorizontalAndRightToLeft()) {
        info.currentOffset =
            GetCustomPropertyOffset() + Dimension(-currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
        info.targetOffset = GetCustomPropertyTargetOffset() - Dimension(-translate, DimensionUnit::PX).ConvertToVp();
    }

    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    if (GetDuration() == 0) {
        // if the duration is 0, the animation will be end immediately, so the start event should be triggered
        // after Layout Task to ensure the timing of events.
        pipeline->AddAfterLayoutTask([weak = WeakClaim(this), info, nextIndex = GetLoopIndex(nextIndex)]() {
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            swiper->FireAnimationStartEvent(swiper->GetLoopIndex(swiper->currentIndex_), nextIndex, info);
            swiper->FireAndCleanScrollingListener();
        });
    } else {
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetLayoutDirtyMarked(true);
    auto context = host->GetContext();
    if (context) {
        context->FlushUITaskWithSingleDirtyNode(host);
        context->FlushSyncGeometryNodeTasks();
    }
}

void SwiperPattern::OnPropertyTranslateAnimationFinish(const OffsetF& offset)
{
    if (!propertyAnimationIsRunning_) {
        // force stop.
        return;
    }
    OffsetF finalOffset =
        itemPositionInAnimation_.empty() ? OffsetF()
        : itemPositionInAnimation_.begin()->second.node
            ? itemPositionInAnimation_.begin()->second.node->GetRenderContext()->GetTranslateXYProperty()
            : OffsetF();
    TAG_LOGI(AceLogTag::ACE_SWIPER,
        "Swiper finish property animation with offsetX: %{public}f, offsetY: %{public}f isVerifiedSuc %{public}d",
        finalOffset.GetX(), finalOffset.GetY(), !IsItemOverlay());
    ACE_SCOPED_TRACE_COMMERCIAL("%s finish property animation, X: %f, Y: %f isVerifiedSuc %d",
        hasTabsAncestor_ ? V2::TABS_ETS_TAG : V2::SWIPER_ETS_TAG, finalOffset.GetX(), finalOffset.GetY(),
        !IsItemOverlay());
    propertyAnimationIsRunning_ = false;
    syncCancelAniIsFailed_ = false;
    targetIndex_.reset();
    // reset translate.
    UpdateTranslateForSwiperItem(itemPositionInAnimation_, OffsetF());
    itemPositionInAnimation_.clear();
    UpdateTranslateForCaptureNode(OffsetF());
    // update postion info.
    UpdateOffsetAfterPropertyAnimation(offset.GetMainOffset(GetDirection()));
    OnTranslateFinish(propertyAnimationIndex_, false, isFinishAnimation_);
}

void SwiperPattern::PropertyCancelAnimationFinish(
    bool isFinishAnimation, bool isBeforeCreateLayoutWrapper, bool isInterrupt)
{
    targetIndex_.reset();
    OffsetF currentOffset;
    for (auto iter = itemPositionInAnimation_.rbegin(); iter != itemPositionInAnimation_.rend(); ++iter) {
        auto frameNode = iter->second.node;
        auto renderContext = frameNode ? frameNode->GetRenderContext() : nullptr;
        if (renderContext) {
            currentOffset = renderContext->GetTranslateXYProperty();
            break;
        }
    }
    if (IsHorizontalAndRightToLeft()) {
        if (GetDirection() == Axis::HORIZONTAL) {
            currentOffset.SetX(-currentOffset.GetX());
        } else {
            currentOffset.SetY(-currentOffset.GetY());
        }
    }
    ACE_SCOPED_TRACE("Swiper stop propertyAni offset %f", currentOffset.GetMainOffset(GetDirection()));
    TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper stop propertyAni offset %{public}f",
        currentOffset.GetMainOffset(GetDirection()));
    UpdateTranslateForSwiperItem(itemPositionInAnimation_, OffsetF());
    itemPositionInAnimation_.clear();
    UpdateTranslateForCaptureNode(OffsetF());
    if (!isBeforeCreateLayoutWrapper) {
        UpdateOffsetAfterPropertyAnimation(currentOffset.GetMainOffset(GetDirection()));
    }
    OnTranslateFinish(propertyAnimationIndex_, false, isFinishAnimation, true, isInterrupt);
}

void SwiperPattern::StopPropertyTranslateAnimation(
    bool isFinishAnimation, bool isBeforeCreateLayoutWrapper, bool isInterrupt)
{
    if (!propertyAnimationIsRunning_ || syncCancelAniIsFailed_) {
        return;
    }
    propertyAnimationIsRunning_ = false;
    AnimationOption option;
    option.SetDuration(0);
    option.SetCurve(Curves::LINEAR);
    auto propertyUpdateCallback = [weak = WeakClaim(this)]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        // cancel translate for swiper item and capture node
        swiper->UpdateTranslateForSwiperItem(swiper->itemPositionInAnimation_, OffsetF(), true);
        swiper->UpdateTranslateForCaptureNode(OffsetF(), true);
    };
    AnimationUtils::OpenImplicitAnimation(option, Curves::LINEAR, nullptr);
    propertyUpdateCallback();
    bool isSyncSuc = AnimationUtils::CloseImplicitCancelAnimation();
    if (!isSyncSuc) {
        ACE_SCOPED_TRACE("Swiper stop propertyAni sync failed");
        TAG_LOGW(AceLogTag::ACE_SWIPER, "Swiper stop propertyAni sync failed");
        // sync cancel animation failed, need to wait for the animation to finish completely
        syncCancelAniIsFailed_ = true;
        propertyAnimationIsRunning_ = true;
        return;
    }
    PropertyCancelAnimationFinish(isFinishAnimation, isBeforeCreateLayoutWrapper, isInterrupt);
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
#ifdef SUPPORT_DIGITAL_CROWN
    if (IsCrownSpring()) {
        return AceType::MakeRefPtr<InterpolatingSpring>(motionVelocity_, 1.0f, 228.0f, 30.0f);
    }
#endif
    // use spring motion feature.
    // interpolatingSpring: (mass: 1, stiffness:328, damping: 34)
    return AceType::MakeRefPtr<InterpolatingSpring>(motionVelocity_, 1, 328, 34);
}

void SwiperPattern::PlayIndicatorTranslateAnimation(float translate, std::optional<int32_t> nextIndex)
{
    if (!stopIndicatorAnimation_) {
        stopIndicatorAnimation_ = true;
        return;
    }
    const auto& turnPageRateCallback = swiperController_->GetTurnPageRateCallback();
    if (!HasIndicatorNode() && !turnPageRateCallback) {
        return;
    }
    CheckMarkDirtyNodeForRenderIndicator(translate, nextIndex);
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
        const auto& turnPageRateCallback = swiper->swiperController_->GetTurnPageRateCallback();
        auto firstItem = swiper->GetFirstItemInfoInVisibleArea();
        auto translateLength = firstItem.second.endPos - firstItem.second.startPos;
        if (turnPageRateCallback && !NearZero(translateLength)) {
            turnPageRateCallback(firstItem.first, (-firstItem.second.startPos - value) / translateLength);
        }
    });

    AnimationOption option;
    option.SetDuration(GetDuration());
    option.SetCurve(Curves::LINEAR);

    host->UpdateAnimatablePropertyFloat(INDICATOR_PROPERTY_NAME, 0);
    indicatorAnimationIsRunning_ = true;
    indicatorAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weakHost = WeakClaim(RawPtr(host)), translate]() {
            auto host = weakHost.Upgrade();
            CHECK_NULL_VOID(host);
            host->UpdateAnimatablePropertyFloat(INDICATOR_PROPERTY_NAME, translate);
        },
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

    if (HasIndicatorNode()) {
        CheckMarkDirtyNodeForRenderIndicator(endPos - startPos, nextIndex);
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto weak = AceType::WeakClaim(this);
    host->CreateAnimatablePropertyFloat(
        TRANSLATE_PROPERTY_NAME, 0,
        [weak](float value) {
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            swiper->UpdateCurrentOffset(static_cast<float>(value - swiper->currentOffset_));
        },
        PropertyUnit::PIXEL_POSITION);

    AnimationOption option;
    auto duration = GetDuration();
    bool finishAnimation = (duration == 0);
    motionVelocity_ = velocity / (endPos - startPos);
    option.SetCurve(GetCurveIncludeMotion());
    option.SetDuration(duration);
    auto iter = frameRateRange_.find(SwiperDynamicSyncSceneType::ANIMATE);
    if (iter != frameRateRange_.end()) {
        TAG_LOGI(AceLogTag::ACE_SWIPER,
            "Translate animation frame rate range: {min: %{public}d, max: %{public}d, expected: %{public}d}",
            iter->second->min_, iter->second->max_, iter->second->preferred_);
        iter->second->componentScene_ = COMPONENT_SWIPER_FLING;
        option.SetFrameRateRange(iter->second);
    } else {
        option.SetFrameRateRange(SWIPER_DEFAULT_FRAME_RATE);
    }
    host->UpdateAnimatablePropertyFloat(TRANSLATE_PROPERTY_NAME, startPos);
    translateAnimationIsRunning_ = true;
    propertyAnimationIndex_ = nextIndex;
    translateAnimationEndPos_ = endPos;
    translateAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weak, startPos, endPos, nextIndex, velocity]() {
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            auto host = swiper->GetHost();
            CHECK_NULL_VOID(host);
            host->UpdateAnimatablePropertyFloat(TRANSLATE_PROPERTY_NAME, endPos);
            AceAsyncTraceBeginCommercial(
                0, swiper->hasTabsAncestor_ ? APP_TABS_FRAME_ANIMATION : APP_SWIPER_FRAME_ANIMATION);
            AnimationCallbackInfo info;
            info.velocity = Dimension(velocity, DimensionUnit::PX).ConvertToVp();
            info.currentOffset = swiper->GetCustomPropertyOffset() +
                                 Dimension(swiper->currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
            info.targetOffset =
                swiper->GetCustomPropertyTargetOffset() + Dimension(startPos - endPos, DimensionUnit::PX).ConvertToVp();
            if (swiper->IsHorizontalAndRightToLeft()) {
                info.currentOffset = swiper->GetCustomPropertyOffset() +
                                     Dimension(-swiper->currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
            }
            swiper->FireAnimationStartEvent(
                swiper->GetLoopIndex(swiper->currentIndex_), swiper->GetLoopIndex(nextIndex), info);
            swiper->FireAndCleanScrollingListener();
        },
        [weak, finishAnimation]() {
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            AceAsyncTraceEndCommercial(
                0, swiper->hasTabsAncestor_ ? APP_TABS_FRAME_ANIMATION : APP_SWIPER_FRAME_ANIMATION);
            if (finishAnimation && swiper->translateAnimationIsRunning_) {
                swiper->isFinishAnimation_ = true;
            }
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
    if (IsHorizontalAndRightToLeft()) {
        info.currentOffset =
            GetCustomPropertyOffset() + Dimension(-currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    }

    nextIndex_ = ComputeNextIndexByVelocity(velocity, true);
    if (GetLoopIndex(currentIndex_) == GetLoopIndex(nextIndex_)) {
        info.targetOffset = info.currentOffset;
    } else {
        FireWillShowEvent(nextIndex_);
        FireWillHideEvent(currentIndex_);
        auto iter = itemPosition_.find(nextIndex_);
        auto nextOffset = iter != itemPosition_.end() ? iter->second.startPos : 0.0f;
        info.targetOffset = GetCustomPropertyTargetOffset() + Dimension(nextOffset, DimensionUnit::PX).ConvertToVp();
    }

    FireAnimationStartEvent(GetLoopIndex(currentIndex_), GetLoopIndex(nextIndex_), info);
}

void SwiperPattern::OnSpringAnimationFinish()
{
    if (!springAnimationIsRunning_) {
        return;
    }
    PerfMonitor::GetPerfMonitor()->End(PerfConstants::APP_LIST_FLING, false);
    AceAsyncTraceEndCommercial(0, TRAILING_ANIMATION);
    TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper finish spring animation offset %{public}f", currentIndexOffset_);
    ACE_SCOPED_TRACE_COMMERCIAL("%s finish spring animation, offset: %f",
        hasTabsAncestor_ ? V2::TABS_ETS_TAG : V2::SWIPER_ETS_TAG, currentIndexOffset_);
    springAnimationIsRunning_ = false;
    isTouchDownSpringAnimation_ = false;
    OnSpringAndFadeAnimationFinish();
}

float SwiperPattern::EstimateSpringOffset(float realOffset)
{
    float springOffset = 0.0f;
    if (GetEdgeEffect() != EdgeEffect::SPRING || !IsOutOfBoundary() || NearEqual(realOffset, 0.0f)) {
        return springOffset;
    }
    auto visibleSize = CalculateVisibleSize();
    if (LessOrEqual(visibleSize, 0.0f)) {
        return springOffset;
    }
    constexpr float MIN_FRICTION = 0.419f;
    auto absRealOffset = std::abs(realOffset);
    auto start = absRealOffset;
    auto end = std::min(visibleSize, absRealOffset / MIN_FRICTION);
    while (LessNotEqual(start, end)) {
        constexpr float factor = 0.5f;
        springOffset = (start + end) * factor;
        auto estimate = springOffset * SwiperHelper::CalculateFriction(springOffset / visibleSize);
        if (NearEqual(estimate, absRealOffset)) {
            break;
        }
        if (estimate < absRealOffset) {
            start = springOffset;
        } else {
            end = springOffset;
        }
    }
    if (springOffset > 0 && realOffset < 0) {
        springOffset = -springOffset;
    }
    if (NearZero(springOffset)) {
        springOffset = 0.0f;
    }
    return springOffset;
}

void SwiperPattern::OnSpringAndFadeAnimationFinish()
{
    auto itemInfoInVisibleArea = std::make_pair(0, SwiperItemInfo {});
    if (!itemPosition_.empty()) {
        auto item = itemPosition_.find(nextIndex_);
        itemInfoInVisibleArea =
            std::make_pair(item->first, SwiperItemInfo { item->second.startPos, item->second.endPos });
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
    if (IsHorizontalAndRightToLeft()) {
        info.currentOffset = GetCustomPropertyOffset() + Dimension(-indexStartPos, DimensionUnit::PX).ConvertToVp();
    }
    FireAnimationEndEvent(GetLoopIndex(currentIndex_), info);
    currentIndexOffset_ = indexStartPos;
    springOffset_ = EstimateSpringOffset(currentIndexOffset_);
    UpdateItemRenderGroup(false);
    NotifyParentScrollEnd();

    if (!isTouchDown_) {
        StartAutoPlay();
    }

    fadeAnimationIsRunning_ = false;
    isTouchDownFadeAnimation_ = false;
}

void SwiperPattern::OnFadeAnimationStart()
{
    AnimationCallbackInfo info;
    info.currentOffset = GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    if (IsHorizontalAndRightToLeft()) {
        info.currentOffset =
            GetCustomPropertyOffset() + Dimension(-currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    }
    nextIndex_ = ComputeNextIndexByVelocity(0.0);
    if (GetLoopIndex(currentIndex_) == GetLoopIndex(nextIndex_)) {
        info.targetOffset = info.currentOffset;
    } else {
        FireWillShowEvent(nextIndex_);
        FireWillHideEvent(currentIndex_);
        info.targetOffset = GetCustomPropertyTargetOffset();
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
    nextIndex_ = currentIndex_;
    fadeAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weak]() {
            auto swiperPattern = weak.Upgrade();
            CHECK_NULL_VOID(swiperPattern);
            swiperPattern->OnFadeAnimationStart();
            auto host = swiperPattern->GetHost();
            CHECK_NULL_VOID(host);
            host->UpdateAnimatablePropertyFloat(FADE_PROPERTY_NAME, 0.f);
        },
        [weak]() {
            auto swiperPattern = weak.Upgrade();
            CHECK_NULL_VOID(swiperPattern);
            swiperPattern->OnSpringAndFadeAnimationFinish();
        });
}

void SwiperPattern::CreateSpringProperty()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->CreateAnimatablePropertyFloat(
        SPRING_PROPERTY_NAME, 0,
        [weak = AceType::WeakClaim(this)](float position) {
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            auto positionDelta = static_cast<float>(position) - swiper->currentIndexOffset_;
            swiper->UpdateCurrentOffset(positionDelta);
            if (LessNotEqual(std::abs(positionDelta), 1) && !NearZero(positionDelta)) {
                AceAsyncTraceBeginCommercial(0, TRAILING_ANIMATION);
            }
        },
        PropertyUnit::PIXEL_POSITION);
}

void SwiperPattern::PlaySpringAnimation(double dragVelocity)
{
    UpdateIgnoreBlankOffsetWithDrag(IsOutOfStart());
    if (RunningTranslateAnimation()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto mainSize = CalculateVisibleSize();
    if (LessOrEqual(mainSize, 0) || itemPosition_.empty()) {
        return;
    }
    childScrolling_ = false;
    auto leading = currentIndexOffset_ + mainSize - itemPosition_.rbegin()->second.endPos;
    auto trailing = currentIndexOffset_ - itemPosition_.begin()->second.startPos;
    ExtentPair extentPair = ExtentPair(leading, trailing);
    CreateSpringProperty();
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
        [weak = AceType::WeakClaim(this), delta]() {
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_LIST_FLING, PerfActionType::FIRST_MOVE, "");
            TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper start spring animation with offset:%{public}f", delta);
            auto swiperPattern = weak.Upgrade();
            CHECK_NULL_VOID(swiperPattern);
            ACE_SCOPED_TRACE_COMMERCIAL(
                "%s start spring animation", swiperPattern->hasTabsAncestor_ ? V2::TABS_ETS_TAG : V2::SWIPER_ETS_TAG);
            auto host = swiperPattern->GetHost();
            CHECK_NULL_VOID(host);
            host->UpdateAnimatablePropertyFloat(SPRING_PROPERTY_NAME, delta);
        },
        [weak = AceType::WeakClaim(this)]() {
            auto swiperPattern = weak.Upgrade();
            CHECK_NULL_VOID(swiperPattern);
            swiperPattern->OnSpringAnimationFinish();
        });
    OnSpringAnimationStart(static_cast<float>(dragVelocity));
    springAnimationIsRunning_ = true;
}

bool SwiperPattern::IsOutOfBoundary(float mainOffset) const
{
    if (IsLoop() || itemPosition_.empty()) {
        return false;
    }

    auto startPos = itemPosition_.begin()->second.startPos + AdjustIgnoreBlankOverScrollOffSet(true);
    startPos = NearZero(startPos, PX_EPSILON) ? 0.0 : startPos;
    auto isOutOfStart = itemPosition_.begin()->first == 0 && GreatNotEqual(startPos + mainOffset, 0.0);
    auto visibleWindowSize = CalculateVisibleSize();
    auto endPos = itemPosition_.rbegin()->second.endPos + mainOffset + AdjustIgnoreBlankOverScrollOffSet(false);
    endPos = NearEqual(endPos, visibleWindowSize, PX_EPSILON) ? visibleWindowSize : endPos;
    auto isOutOfEnd = itemPosition_.rbegin()->first == TotalCount() - 1 && LessNotEqual(endPos, visibleWindowSize);
    return isOutOfStart || isOutOfEnd;
}

bool SwiperPattern::IsOutOfStart(float mainOffset) const
{
    if (IsLoop() || itemPosition_.empty()) {
        return false;
    }

    auto startPos = itemPosition_.begin()->second.startPos + AdjustIgnoreBlankOverScrollOffSet(true);
    startPos = NearZero(startPos, PX_EPSILON) ? 0.f : startPos;
    return itemPosition_.begin()->first == 0 && GreatNotEqual(startPos + mainOffset, 0.f);
}

bool SwiperPattern::IsOutOfEnd(float mainOffset) const
{
    if (IsLoop() || itemPosition_.empty()) {
        return false;
    }

    auto visibleWindowSize = CalculateVisibleSize();
    auto endPos = itemPosition_.rbegin()->second.endPos + mainOffset + AdjustIgnoreBlankOverScrollOffSet(false);
    endPos = NearEqual(endPos, visibleWindowSize, PX_EPSILON) ? visibleWindowSize : endPos;
    return itemPosition_.rbegin()->first == TotalCount() - 1 && LessNotEqual(endPos, visibleWindowSize);
}

bool SwiperPattern::IsAtStart() const
{
    if (IsLoop() || itemPosition_.empty()) {
        return false;
    }

    auto startPos = itemPosition_.begin()->second.startPos;
    startPos = NearZero(startPos, PX_EPSILON) ? 0.f : startPos;
    return itemPosition_.begin()->first == 0 && GreatOrEqual(startPos, 0.f);
}

bool SwiperPattern::IsAtEnd() const
{
    if (IsLoop() || itemPosition_.empty()) {
        return false;
    }

    auto visibleWindowSize = CalculateVisibleSize();
    auto endPos = itemPosition_.rbegin()->second.endPos;
    endPos = NearEqual(endPos, visibleWindowSize, PX_EPSILON) ? visibleWindowSize : endPos;
    return itemPosition_.rbegin()->first == TotalCount() - 1 && LessOrEqual(endPos, visibleWindowSize);
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
        return -itemPosition_.begin()->second.startPos + AdjustIgnoreBlankOverScrollOffSet(true);
    }
    auto visibleWindowSize = CalculateVisibleSize();
    return itemPosition_.rbegin()->second.endPos - visibleWindowSize + AdjustIgnoreBlankOverScrollOffSet(false);
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

float SwiperPattern::GetItemSpace() const
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, 0.0f);
    if (props->IgnoreItemSpace()) {
        return 0.0f;
    }
    auto itemSpace = props->GetItemSpace().value_or(0.0_vp).ConvertToPx();
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

bool SwiperPattern::IsCachedShow() const
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, false);
    return props->GetCachedIsShown().value_or(false);
}

float SwiperPattern::GetPrevMargin() const
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, 0.0f);
    return props->GetCalculatedPrevMargin();
}

float SwiperPattern::GetNextMargin() const
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, 0.0f);
    return props->GetCalculatedNextMargin();
}

Axis SwiperPattern::GetDirection() const
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, Axis::HORIZONTAL);
    return props->GetDirection().value_or(Axis::HORIZONTAL);
}

int32_t SwiperPattern::CurrentIndex() const
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, 0);
    return props->GetIndex().value_or(0);
}

int32_t SwiperPattern::GetDisplayCount() const
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, 1);
    auto displayCount = CalculateDisplayCount();
    return displayCount;
}

int32_t SwiperPattern::CalculateDisplayCount() const
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, 1);
    bool isAutoFill = IsAutoFill();
    if (isAutoFill) {
        auto minSize = props->GetMinSize()->ConvertToPx();
        float contentWidth = GetMainContentSize();
        auto displayCount =
            CalculateCount(contentWidth, minSize, SWIPER_MARGIN.ConvertToPx(), SWIPER_GUTTER.ConvertToPx());
        if (LessOrEqual(minSize, 0)) {
            displayCount = 1;
        }

        displayCount = displayCount > 0 ? displayCount : 1;
        auto totalCount = TotalCount();
        displayCount = displayCount > totalCount ? totalCount : displayCount;
        auto displayCountProperty = props->GetDisplayCount().value_or(1);
        if (displayCountProperty != displayCount) {
            props->UpdateDisplayCount(displayCount);
            auto host = GetHost();
            CHECK_NULL_RETURN(host, 1);
            host->MarkDirtyNode(
                (crossMatchChild_ ? PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD : PROPERTY_UPDATE_MEASURE_SELF) |
                PROPERTY_UPDATE_RENDER);
        }
        return displayCount;
    } else {
        return props->GetDisplayCount().value_or(1);
    }
}

int32_t SwiperPattern::CalculateCount(
    float contentWidth, float minSize, float margin, float gutter, float swiperPadding) const
{
    return static_cast<int32_t>(floor((contentWidth - 2 * margin + gutter - 2 * swiperPadding) / (minSize + gutter)));
}

bool SwiperPattern::IsAutoFill() const
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, false);
    return props->GetMinSize().has_value();
}

bool SwiperPattern::IsAutoPlay() const
{
    auto props = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(props, false);
    return props->GetAutoPlay().value_or(false);
}

int32_t SwiperPattern::GetDuration() const
{
    const int32_t DEFAULT_DURATION = 400;
    auto props = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(props, DEFAULT_DURATION);
    return props->GetDuration().value_or(DEFAULT_DURATION);
}

int32_t SwiperPattern::GetInterval() const
{
    const int32_t DEFAULT_INTERVAL = 3000;
    auto props = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(props, DEFAULT_INTERVAL);
    return props->GetAutoPlayInterval().value_or(DEFAULT_INTERVAL);
}

RefPtr<Curve> SwiperPattern::GetCurve() const
{
    auto props = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(props, nullptr);
    return props->GetCurve().value_or(nullptr);
}

bool SwiperPattern::IsLoop() const
{
    if (hasCachedCapture_) {
        return true;
    }
    const auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, true);
    if (TotalDisPlayCount() > TotalCount() ||
        (TotalDisPlayCount() == TotalCount() && SwiperUtils::IsStretch(props) &&
            (NonPositive(props->GetCalculatedPrevMargin()) || NonPositive(props->GetCalculatedNextMargin())))) {
        return false;
    }
    return props->GetLoop().value_or(true);
}

bool SwiperPattern::IsEnabled() const
{
    auto props = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(props, true);
    return props->GetEnabled().value_or(true);
}

EdgeEffect SwiperPattern::GetEdgeEffect() const
{
    auto props = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(props, EdgeEffect::SPRING);
    return props->GetEdgeEffect().value_or(EdgeEffect::SPRING);
}

bool SwiperPattern::IsDisableSwipe() const
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, false);
    return props->GetDisableSwipe().value_or(false);
}

bool SwiperPattern::IsShowIndicator() const
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, true);
    return props->GetShowIndicatorValue(true);
}

bool SwiperPattern::IsShowArrow() const
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, true);
    return props->GetDisplayArrowValue(false);
}

SwiperIndicatorType SwiperPattern::GetIndicatorType() const
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, SwiperIndicatorType::DOT);
    return props->GetIndicatorTypeValue(SwiperIndicatorType::DOT);
}

std::shared_ptr<SwiperParameters> SwiperPattern::GetSwiperParameters() const
{
    if (swiperParameters_ == nullptr) {
        swiperParameters_ = std::make_shared<SwiperParameters>();
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, swiperParameters_);
        auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        CHECK_NULL_RETURN(swiperIndicatorTheme, swiperParameters_);
        swiperParameters_->itemWidth = swiperIndicatorTheme->GetSize();
        swiperParameters_->itemHeight = swiperIndicatorTheme->GetSize();
        swiperParameters_->selectedItemWidth = swiperIndicatorTheme->GetSize();
        swiperParameters_->selectedItemHeight = swiperIndicatorTheme->GetSize();
        swiperParameters_->maskValue = false;
        swiperParameters_->colorVal = swiperIndicatorTheme->GetColor();
        swiperParameters_->selectedColorVal = swiperIndicatorTheme->GetSelectedColor();
        swiperParameters_->maxDisplayCountVal = 0;
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
    const auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, 1);
    auto displayCount = props->GetDisplayCount().value_or(1);
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
    if (!isBindIndicator_ && IsShowIndicator() && HasIndicatorNode()) {
        num += 1;
    }
    if (HasLeftButtonNode()) {
        num += 1;
    }
    if (HasRightButtonNode()) {
        num += 1;
    }
    if (hasCachedCapture_ && leftCaptureId_.has_value() && rightCaptureId_.has_value()) {
        num += CAPTURE_COUNT;
    }
    return host->TotalChildCount() - num;
}

int32_t SwiperPattern::DisplayIndicatorTotalCount() const
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
        return RealTotalCount();
    }

    auto displayCount = GetDisplayCount();
    auto realTotalCount = RealTotalCount();
    if (realTotalCount <= displayCount) {
        return 1;
    }
    if (IsSwipeByGroup() && displayCount != 0) {
        int32_t totalPages = 0;
        totalPages = realTotalCount / displayCount;

        if (realTotalCount % displayCount) {
            totalPages++;
        }

        return totalPages;
    } else {
        if (IsLoop()) {
            return realTotalCount;
        } else {
            return realTotalCount - displayCount + 1;
        }
    }
}

std::pair<int32_t, SwiperItemInfo> SwiperPattern::GetFirstItemInfoInVisibleArea() const
{
    if (itemPosition_.empty()) {
        return std::make_pair(0, SwiperItemInfo {});
    }
    for (const auto& item : itemPosition_) {
        if (item.second.startPos < 0 && item.second.endPos < 0) {
            continue;
        }
        if (item.second.startPos <= 0 && item.second.endPos > 0) {
            return std::make_pair(item.first, SwiperItemInfo { item.second.startPos, item.second.endPos });
        }
        if (item.second.startPos > 0 && item.second.endPos > 0) {
            return std::make_pair(item.first, SwiperItemInfo { item.second.startPos, item.second.endPos });
        }
    }
    return std::make_pair(itemPosition_.begin()->first,
        SwiperItemInfo { itemPosition_.begin()->second.startPos, itemPosition_.begin()->second.endPos });
}

int32_t SwiperPattern::GetFirstIndexInVisibleArea() const
{
    if (itemPosition_.empty()) {
        return 0;
    }
    for (const auto& item : itemPosition_) {
        if (Negative(item.second.startPos) && Negative(item.second.endPos)) {
            continue;
        }
        if (Positive(item.second.endPos)) {
            return item.first;
        }
    }
    return itemPosition_.begin()->first;
}

std::pair<int32_t, SwiperItemInfo> SwiperPattern::GetLastItemInfoInVisibleArea() const
{
    if (itemPosition_.empty()) {
        return std::make_pair(0, SwiperItemInfo {});
    }
    auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
    auto lastItemIndex = firstItemInfoInVisibleArea.first + GetDisplayCount() - 1;
    auto iter = itemPosition_.find(lastItemIndex);
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
    auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
    auto secondItemIndex = firstItemInfoInVisibleArea.first + 1;
    auto iter = itemPosition_.find(secondItemIndex);
    if (iter != itemPosition_.end()) {
        return std::make_pair(iter->first, SwiperItemInfo { iter->second.startPos, iter->second.endPos });
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

void SwiperPattern::UpdatePaintProperty(const RefPtr<FrameNode>& indicatorNode)
{
    CHECK_NULL_VOID(indicatorNode);
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    auto swiperParameters = GetSwiperParameters();
    CHECK_NULL_VOID(swiperParameters);
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
    paintProperty->UpdateIsCustomSize(isCustomSize_);

    MarkDirtyNodeSelf();
    indicatorNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void SwiperPattern::SetDigitStartAndEndProperty(const RefPtr<FrameNode>& indicatorNode)
{
    CHECK_NULL_VOID(indicatorNode);
    auto indicatorProps = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(indicatorProps);
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(props);
    const auto digitalParams = GetSwiperDigitalParameters();
    CHECK_NULL_VOID(digitalParams);
    bool isRtl = GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (digitalParams->dimStart.has_value()) {
        auto dimValue = digitalParams->dimStart.value().Value() >= 0.0 ? digitalParams->dimStart.value()
                                                                       : Dimension(0.0, DimensionUnit::VP);
        isRtl ? indicatorProps->UpdateRight(dimValue) : indicatorProps->UpdateLeft(dimValue);
        isRtl ? props->UpdateRight(dimValue) : props->UpdateLeft(digitalParams->dimLeft.value_or(0.0_vp));
        ;
    } else if (digitalParams->dimEnd.has_value()) {
        auto dimValue = digitalParams->dimEnd.value().Value() >= 0.0 ? digitalParams->dimEnd.value()
                                                                     : Dimension(0.0, DimensionUnit::VP);
        isRtl ? indicatorProps->UpdateLeft(dimValue) : indicatorProps->UpdateRight(dimValue);
        isRtl ? props->UpdateLeft(dimValue) : props->UpdateRight(digitalParams->dimRight.value_or(0.0_vp));
    }
}

void SwiperPattern::PostTranslateTask(uint32_t delayTime)
{
    auto pipeline = GetContext();
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
            swiper->isInAutoPlay_ = true;
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
            ACE_SCOPED_TRACE("Swiper autoPlay delayTime %d targetIndex %d isVisibleArea_ %d isWindowShow_ %d",
                delayTime, swiper->targetIndex_.value(), swiper->isVisibleArea_, swiper->isWindowShow_);
            swiper->MarkDirtyNodeSelf();
        }
    });

    taskExecutor->PostDelayedTask(translateTask_, TaskExecutor::TaskType::UI, delayTime, "ArkUISwiperTranslate");
}

void SwiperPattern::HandleVisibleChange(bool visible)
{
    isVisibleArea_ = visible;
    if (!visible) {
        translateTask_.Cancel();
        isInAutoPlay_ = false;
        return;
    }

    if (NeedStartAutoPlay()) {
        StartAutoPlay();
    }
}

void SwiperPattern::RegisterVisibleAreaChange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(host->GetId());

    if (hasVisibleChangeRegistered_) {
        return;
    }

    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        swiperPattern->HandleVisibleChange(visible);
    };
    pipeline->RemoveVisibleAreaChangeNode(host->GetId());
    std::vector<double> ratioList = { 0.0 };
    pipeline->AddVisibleAreaChangeNode(host, ratioList, callback, false, true);
    hasVisibleChangeRegistered_ = true;

    auto isFormRender = pipeline->IsFormRender();
    auto formMgr = pipeline->GetFormVisibleManager();
    if (!isFormRender || !formMgr) {
        return;
    }
    formMgr->RemoveFormVisibleChangeNode(host->GetId());
    auto formCallback = [weak = WeakClaim(this)](bool visible) {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        swiperPattern->HandleVisibleChange(visible);
    };
    formMgr->AddFormVisibleChangeNode(host, formCallback);
}

bool SwiperPattern::NeedAutoPlay() const
{
    bool reachEnd = GetLoopIndex(CurrentIndex()) >= TotalCount() - 1 && !IsLoop();
    return IsAutoPlay() && !reachEnd && NeedStartAutoPlay() && !isIndicatorLongPress_;
}

void SwiperPattern::TriggerAnimationEndOnSwipeToLeft()
{
    auto firstItemInfoInVisibleArea = GetFirstItemInfoInVisibleArea();
    auto firstItemLength = firstItemInfoInVisibleArea.second.endPos - firstItemInfoInVisibleArea.second.startPos;
    auto firstIndexStartPos = firstItemInfoInVisibleArea.second.startPos;
    if (std::abs(firstIndexStartPos) < (firstItemLength / swiperProportion_)) {
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
    if (std::abs(secondIndexStartPos) < (firstItemLength / swiperProportion_)) {
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
    if (std::abs(currentOffset) < (swiperWidth / swiperProportion_)) {
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

void SwiperPattern::TriggerAnimationEndOnForceStop(bool isInterrupt)
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
    info.isForceStop = true;
    info.currentOffset = GetCustomPropertyOffset() + Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    if (IsHorizontalAndRightToLeft()) {
        info.currentOffset =
            GetCustomPropertyOffset() + Dimension(-currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    }
    FireAnimationEndEvent(GetLoopIndex(currentIndex_), info, isInterrupt);
    UpdateItemRenderGroup(false);
}

void SwiperPattern::TriggerEventOnFinish(int32_t nextIndex)
{
    ResetAndUpdateIndexOnAnimationEnd(nextIndex);

    AnimationCallbackInfo info;
    info.isForceStop = false;
    info.currentOffset = GetCustomPropertyOffset();
    FireAnimationEndEvent(GetLoopIndex(currentIndex_), info);
}

int32_t SwiperPattern::GetCachedCount() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 1);
    auto props = host->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, 1);
    auto cachedCount = props->GetCachedCount().value_or(1);

    if (IsSwipeByGroup()) {
        cachedCount *= GetDisplayCount();
    }

    return cachedCount;
}

void SwiperPattern::SetLazyLoadFeature(bool useLazyLoad)
{
    requestLongPredict_ = useLazyLoad;
    SetLazyForEachLongPredict(useLazyLoad);

    if (!useLazyLoad) {
        return;
    }
    auto cacheCount = std::min(GetCachedCount(), RealTotalCount());
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
        auto pipeline = GetContext();
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
            TaskExecutor::TaskType::UI, "ArkUISwiperSetLazyLoadFeature");
    }
}

void SwiperPattern::SetLazyForEachLongPredict(bool useLazyLoad) const
{
    // lazyBuild feature.
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto targetNode = FindLazyForEachNode(host);
    if (targetNode.has_value()) {
        auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(targetNode.value());
        CHECK_NULL_VOID(lazyForEachNode);
        lazyForEachNode->SetRequestLongPredict(useLazyLoad);
    }
}

void SwiperPattern::SetLazyLoadIsLoop() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto targetNode = FindLazyForEachNode(host);
    if (targetNode.has_value()) {
        auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(targetNode.value());
        if (lazyForEachNode) {
            lazyForEachNode->SetIsLoop(IsLoop());
        }
        auto repeatVirtualNode = AceType::DynamicCast<RepeatVirtualScrollNode>(targetNode.value());
        if (repeatVirtualNode) {
            repeatVirtualNode->SetIsLoop(IsLoop());
        }
    }
}

void SwiperPattern::PostIdleTask(const RefPtr<FrameNode>& frameNode)
{
    if (cachedItems_.empty()) {
        return;
    }
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddPredictTask(
        [weak = WeakClaim(RawPtr(frameNode))](int64_t deadline, bool canUseLongPredictTask) {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            auto pattern = frameNode->GetPattern<SwiperPattern>();
            CHECK_NULL_VOID(pattern);
            if (!canUseLongPredictTask || !pattern->GetRequestLongPredict()) {
                pattern->PostIdleTask(frameNode);
                return;
            }
            auto cachedItems = pattern->GetCachedItems();
            for (auto it = cachedItems.begin(); it != cachedItems.end();) {
                if (GetSysTimestamp() > deadline) {
                    break;
                }
                ACE_SCOPED_TRACE("Swiper cached self index: %d", *it);
                auto wrapper = frameNode->GetOrCreateChildByIndex(*it, false, true);
                if (!wrapper) {
                    it = cachedItems.erase(it);
                    continue;
                }
                auto childNode = wrapper->GetHostNode();
                if (childNode && childNode->GetGeometryNode()) {
                    childNode->GetGeometryNode()->SetParentLayoutConstraint(pattern->GetLayoutConstraint());
                    FrameNode::ProcessOffscreenNode(childNode);
                }
                it = cachedItems.erase(it);
            }
            pattern->SetCachedItems(cachedItems);
            if (!cachedItems.empty()) {
                pattern->PostIdleTask(frameNode);
            }
        });
}

bool SwiperPattern::IsVisibleChildrenSizeLessThanSwiper() const
{
    if (itemPosition_.empty() || GetDisplayCount() > TotalCount()) {
        return true;
    }
    const auto firstItem = GetFirstItemInfoInVisibleArea();
    const auto lastItem = GetLastItemInfoInVisibleArea();
    const int32_t visibleItemCnt = lastItem.first - firstItem.first + 1;
    if (TotalCount() != visibleItemCnt) {
        return false;
    }
    const float childrenLength = lastItem.second.endPos - firstItem.second.startPos;
    if (NonPositive(childrenLength)) {
        return true;
    }
    return LessOrEqual(childrenLength, CalculateVisibleSize());
}

void SwiperPattern::UpdateItemRenderGroup(bool itemRenderGroup)
{
    for (auto& item : itemPosition_) {
        if (auto frameNode = item.second.node) {
            groupedItems_.insert(frameNode);
        }
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    for (auto child : host->GetChildren()) {
        auto frameNode = DynamicCast<FrameNode>(child);
        if (!frameNode || child->GetTag() == V2::SWIPER_INDICATOR_ETS_TAG) {
            continue;
        }
        groupedItems_.insert(frameNode);
    }
    for (auto iter = groupedItems_.begin(); iter != groupedItems_.end();) {
        if (auto node = iter->Upgrade()) {
            auto context = node->GetRenderContext();
            CHECK_NULL_VOID(context);
            context->UpdateSuggestedRenderGroup(itemRenderGroup);
            ++iter;
        } else {
            iter = groupedItems_.erase(iter);
        }
    }
}

void SwiperPattern::OnTranslateFinish(
    int32_t nextIndex, bool restartAutoPlay, bool isFinishAnimation, bool forceStop, bool isInterrupt)
{
    runningTargetIndex_.reset();
    if (forceStop && !isFinishAnimation) {
        TriggerAnimationEndOnForceStop(isInterrupt);
    } else {
        TriggerEventOnFinish(nextIndex);
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (HasIndicatorNode()) {
        auto indicatorNode = GetCommonIndicatorNode();
        CHECK_NULL_VOID(indicatorNode);
        if (IsIndicator(indicatorNode->GetTag())) {
            indicatorNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            MarkDirtyNodeSelf();
        }
    }

    auto delayTime = GetInterval() - GetDuration();
    delayTime = std::clamp(delayTime, 0, delayTime);
    if (NeedAutoPlay() && isUserFinish_ && !forceStop) {
        PostTranslateTask(delayTime);
    }
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
    const auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(props);
    const auto paintProps = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(props);
    const auto arrowProps = arrowNode->GetLayoutProperty<SwiperArrowLayoutProperty>();
    CHECK_NULL_VOID(arrowProps);
    arrowProps->UpdateDirection(props->GetDirection().value_or(Axis::HORIZONTAL));
    arrowProps->UpdateIndex(props->GetIndex().value_or(0));
    arrowProps->UpdateLoop(props->GetLoop().value_or(true));
    arrowProps->UpdateEnabled(paintProps->GetEnabled().value_or(true));
    arrowProps->UpdateDisplayArrow(props->GetDisplayArrowValue());
    arrowProps->UpdateHoverShow(props->GetHoverShowValue());
    arrowProps->UpdateIsShowBackground(props->GetIsShowBackgroundValue());
    arrowProps->UpdateBackgroundSize(props->GetBackgroundSizeValue());
    arrowProps->UpdateBackgroundColor(props->GetBackgroundColorValue());
    arrowProps->UpdateArrowSize(props->GetArrowSizeValue());
    arrowProps->UpdateArrowColor(props->GetArrowColorValue());
    arrowProps->UpdateIsSidebarMiddle(props->GetIsSidebarMiddleValue());
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
    return isWindowShow_ && isVisibleArea_;
}

std::string SwiperPattern::ProvideRestoreInfo()
{
    auto jsonObj = JsonUtil::Create(true);
    CHECK_NULL_RETURN(jsonObj, "");
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, "");
    jsonObj->Put("Index", props->GetIndex().value_or(0));
    return jsonObj->ToString();
}

void SwiperPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(props);
    auto info = JsonUtil::ParseJsonString(restoreInfo);
    if (!info || !info->IsValid() || !info->IsObject()) {
        return;
    }
    auto jsonIsOn = info->GetValue("Index");
    props->UpdateIndex(jsonIsOn->GetInt());
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

    const auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(props);
    if (props->GetIsSidebarMiddleValue(false)) {
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
    const auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, 0.0);
    auto paddingAndBorder = props->CreatePaddingAndBorder();
    auto paddingAndBorderValue = GetDirection() == Axis::HORIZONTAL
                                     ? paddingAndBorder.left.value_or(0.0) + tabsPaddingAndBorder_.left.value_or(0.0)
                                     : paddingAndBorder.top.value_or(0.0) + tabsPaddingAndBorder_.top.value_or(0.0);
    return Dimension(paddingAndBorderValue + GetPrevMarginWithItemSpace(), DimensionUnit::PX).ConvertToVp();
}

float SwiperPattern::GetCustomPropertyTargetOffset() const
{
    const auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, 0.0);
    auto paddingAndBorder = props->CreatePaddingAndBorder();
    auto paddingAndBorderValue = GetDirection() == Axis::HORIZONTAL
                                     ? paddingAndBorder.left.value_or(0.0) + tabsPaddingAndBorder_.left.value_or(0.0)
                                     : paddingAndBorder.top.value_or(0.0) + tabsPaddingAndBorder_.top.value_or(0.0);

    auto preMarginPX = GetPrevMarginWithItemSpace();
    if (IsHorizontalAndRightToLeft()) {
        return Dimension(paddingAndBorderValue - preMarginPX, DimensionUnit::PX).ConvertToVp();
    }
    return Dimension(paddingAndBorderValue + preMarginPX, DimensionUnit::PX).ConvertToVp();
}

int32_t SwiperPattern::TotalDisPlayCount() const
{
    auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, 1);
    auto displayCount = GetDisplayCount();
    if (SwiperUtils::IsStretch(props)) {
        if (Positive(props->GetCalculatedPrevMargin())) {
            displayCount++;
        }
        if (Positive(props->GetCalculatedNextMargin())) {
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
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);

    targetIndex_.reset();

    if (isFinishAnimation_) {
        currentDelta_ = 0.0f;
        itemPosition_.clear();
        isVoluntarilyClear_ = true;
        jumpIndex_ = nextIndex;
        MarkDirtyNodeSelf();
        pipeline->FlushUITasks();
        isFinishAnimation_ = false;
    } else if (currentIndex_ != nextIndex) {
        UpdateCurrentIndex(nextIndex);
        if (currentFocusIndex_ < currentIndex_ || currentFocusIndex_ >= currentIndex_ + GetDisplayCount()) {
            currentFocusIndex_ = currentIndex_;
        }
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        do {
            auto curChildFrame =
                DynamicCast<FrameNode>(host->GetOrCreateChildByIndex(GetLoopIndex(currentFocusIndex_)));
            if (!curChildFrame || !IsContentFocused()) {
                break;
            }
            FlushFocus(curChildFrame);
        } while (0);
        auto tempOldIndex = oldIndex_;
        oldIndex_ = nextIndex;
        currentFirstIndex_ = GetLoopIndex(nextIndex);
        turnPageRate_ = 0.0f;
        currentIndexOffset_ = 0.0f;
        if (pipeline->IsLayouting()) {
            pipeline->FlushUITaskWithSingleDirtyNode(host);
            pipeline->FlushSyncGeometryNodeTasks();
        } else {
            pipeline->FlushUITasks();
            pipeline->FlushMessages();
        }

        FireChangeEvent(tempOldIndex, GetLoopIndex(currentIndex_));
        // lazyBuild feature.
        SetLazyLoadFeature(true);
    }
}

void SwiperPattern::OnScrollStartRecursive(WeakPtr<NestableScrollContainer> child, float position, float /* velocity */)
{
    SetIsNestedInterrupt(false);
    if (IsDisableSwipe()) {
        return;
    }
    childScrolling_ = true;
    gestureSwipeIndex_ = currentIndex_;
    StopAnimationOnScrollStart(false);
    NotifyParentScrollStart(child, position);
}

void SwiperPattern::NotifyParentScrollStart(WeakPtr<NestableScrollContainer> child, float position)
{
    if (!GetIsFixedNestedScrollMode()) {
        SetParentScrollable();
    }
    auto parent = GetNestedScrollParent();
    CHECK_NULL_VOID(parent);
    const auto& nestedScroll = GetNestedScroll();
    if (parent && nestedScroll.NeedParent()) {
        parent->OnScrollStartRecursive(child, position);
    }
}

void SwiperPattern::OnScrollEndRecursive(const std::optional<float>& velocity)
{
    if (IsDisableSwipe()) {
        return;
    }
    // in case child didn't call swiper's HandleScrollVelocity
    if (!DuringTranslateAnimation() && !DuringFadeAnimation()) {
        HandleDragEnd(velocity.value_or(0.0f));
    }
    SetIsNestedInterrupt(false);
    childScrolling_ = false;
    InitIndexCanChangeMap();
}

void SwiperPattern::OnScrollDragEndRecursive()
{
    NestableScrollContainer::OnScrollDragEndRecursive();
    if (IsDisableSwipe()) {
        return;
    }
    // Swiper and child handle drag end event together.
    if (!DuringTranslateAnimation() && !DuringFadeAnimation()) {
        HandleDragEnd(0.0f);
    }
}

void SwiperPattern::NotifyParentScrollEnd()
{
    auto parent = GetNestedScrollParent();
    const auto& nestedScroll = GetNestedScroll();
    if (parent && (nestedScroll.NeedParent() || GetIsNestedInterrupt())) {
        parent->OnScrollEndRecursive(std::nullopt);
    }
}

inline bool SwiperPattern::DuringTranslateAnimation() const
{
    return (springAnimation_ && springAnimationIsRunning_ && !isTouchDownSpringAnimation_) || targetIndex_ ||
           propertyAnimationIsRunning_ || translateAnimationIsRunning_;
}

inline bool SwiperPattern::RunningTranslateAnimation() const
{
    return springAnimationIsRunning_ || propertyAnimationIsRunning_ || translateAnimationIsRunning_;
}

inline bool SwiperPattern::DuringFadeAnimation() const
{
    return fadeAnimation_ && fadeAnimationIsRunning_ && !isTouchDownFadeAnimation_;
}

bool SwiperPattern::HandleScrollVelocity(float velocity, const RefPtr<NestableScrollContainer>& child)
{
    if (IsDisableSwipe()) {
        return false;
    }
    DestructSetter<bool> scope(childScrolling_, false);
    // haven't reached edge
    if (GetDistanceToEdge() > 0.0f || IsLoop()) {
        HandleDragEnd(velocity);
        return true;
    }

    auto parent = GetNestedScrollParent();
    const auto nestedScroll = GetNestedScroll();
    if (parent && nestedScroll.NeedParent(NonPositive(velocity))) {
        // after reach end, parent handle velocity first
        if (parent->HandleScrollVelocity(velocity)) {
            return true;
        }
    }
    HandleDragEnd(velocity);
    // after reached end, NONE doesn't consume velocity, other edge effects do
    return GetEdgeEffect() != EdgeEffect::NONE;
}

void SwiperPattern::HandleOutBoundarySelf(float offset, float& selfOffset, float& remainOffset)
{
    if (IsLoop()) {
        return;
    }
    if (GetEdgeEffect() == EdgeEffect::FADE && !NearZero(fadeOffset_)) {
        if ((Negative(offset) && Positive(fadeOffset_)) || (Positive(offset) && Negative(fadeOffset_))) {
            if (GreatNotEqual(std::abs(fadeOffset_), std::abs(offset))) {
                remainOffset = 0.0f;
                selfOffset = offset;
            } else {
                remainOffset += fadeOffset_;
                selfOffset = -fadeOffset_;
            }
        }
    }
    if (GetEdgeEffect() == EdgeEffect::SPRING && !itemPosition_.empty()) {
        if (Negative(offset) && itemPosition_.begin()->first == 0) {
            auto startPos = itemPosition_.begin()->second.startPos + AdjustIgnoreBlankOverScrollOffSet(true);
            startPos = NearZero(startPos, PX_EPSILON) ? 0.f : startPos;
            if (Positive(startPos)) {
                selfOffset = -std::min(startPos, -offset);
                remainOffset -= selfOffset;
            }
        } else if (Positive(offset) && itemPosition_.rbegin()->first == TotalCount() - 1) {
            auto visibleWindowSize = CalculateVisibleSize();
            auto endPos = itemPosition_.rbegin()->second.endPos + AdjustIgnoreBlankOverScrollOffSet(false);
            endPos = NearEqual(endPos, visibleWindowSize, PX_EPSILON) ? visibleWindowSize : endPos;
            if (LessNotEqual(endPos, visibleWindowSize)) {
                selfOffset = std::min(visibleWindowSize - endPos, offset);
                remainOffset -= selfOffset;
            }
        }
    }
}

ScrollResult SwiperPattern::HandleOutBoundary(float offset, int32_t source, float velocity)
{
    float selfOffset = 0.0f;
    float remainOffset = offset;
    HandleOutBoundarySelf(offset, selfOffset, remainOffset);
    auto parent = GetNestedScrollParent();
    if (!NearZero(remainOffset) && parent) {
        auto res = parent->HandleScroll(remainOffset, source, NestedState::CHILD_CHECK_OVER_SCROLL, velocity);
        remainOffset = res.remain;
    }
    if (!NearZero(selfOffset)) {
        UpdateCurrentOffset(selfOffset);
    }
    return { remainOffset, true };
}

ScrollResult SwiperPattern::HandleScroll(float offset, int32_t source, NestedState state, float velocity)
{
    if (state == NestedState::CHILD_CHECK_OVER_SCROLL) {
        return HandleOutBoundary(offset, source, velocity);
    }
    if (IsDisableSwipe() || (source == SCROLL_FROM_ANIMATION && DuringTranslateAnimation()) ||
        !CheckSwiperPanEvent(offset)) {
        // deny conflicting animation from child
        return { offset, true };
    }
    if (state != NestedState::GESTURE) {
        // handle situations when multiple children are notifying scrollStart / scrollEnd
        // reset flag and animations to correct states when scroll happens
        childScrolling_ = true;
        if (DuringTranslateAnimation()) {
            StopAnimationOnScrollStart(false);
        }
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
    if (!parent) {
        return { 0.0f, true };
    }
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
        if (!parent) {
            return { 0.0f, true };
        }

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

void SwiperPattern::UpdateDragFRCSceneInfo(float speed, SceneStatus sceneStatus)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->AddFRCSceneInfo(SWIPER_DRAG_SCENE, speed, sceneStatus);
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

void SwiperPattern::DumpAdvanceInfo()
{
    SwiperHelper::DumpAdvanceInfo(*this);
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

bool SwiperPattern::IsSwipeByGroup() const
{
    const auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, false);
    return props->GetSwipeByGroup().value_or(false);
}

RefPtr<FrameNode> SwiperPattern::GetCurrentFrameNode(int32_t currentIndex) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto currentLayoutWrapper = host->GetChildByIndex(GetLoopIndex(currentIndex), true);
    CHECK_NULL_RETURN(currentLayoutWrapper, nullptr);
    return currentLayoutWrapper->GetHostNode();
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

        FireChangeEvent(CurrentIndex(), fromIndex);

        UpdateCurrentIndex(fromIndex);
        oldIndex_ = fromIndex;

        AnimationCallbackInfo info;
        info.currentOffset = GetCustomPropertyOffset();
        FireAnimationEndEvent(fromIndex, info);

        currentProxyInAnimation_->SetHasOnChanged(true);
    }
    if (fromIndex != toIndex) {
        FireWillShowEvent(toIndex);
        FireWillHideEvent(fromIndex);
    }
    auto pipelineContext = GetContext();
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
    info.targetOffset = GetCustomPropertyTargetOffset();
    FireAnimationStartEvent(fromIndex, toIndex, info);

    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    auto timeout = tabContentAnimatedTransition.timeout;
    auto timeoutTask = [weak = AceType::WeakClaim(AceType::RawPtr(proxy))] {
        auto transitionProxy = weak.Upgrade();
        CHECK_NULL_VOID(transitionProxy);
        transitionProxy->FinishTransition();
    };

    taskExecutor->PostDelayedTask(timeoutTask, TaskExecutor::TaskType::UI, timeout, "ArkUISwiperFinishTransition");
}

void SwiperPattern::OnCustomAnimationFinish(int32_t fromIndex, int32_t toIndex, bool hasOnChanged)
{
    customAnimationToIndex_.reset();
    needUnmountIndexs_.insert(fromIndex);
    indexsInAnimation_.erase(toIndex);

    if (!hasOnChanged) {
        const auto props = GetLayoutProperty<SwiperLayoutProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateIndexWithoutMeasure(GetLoopIndex(toIndex));
        oldIndex_ = fromIndex;

        AnimationCallbackInfo info;
        info.currentOffset = GetCustomPropertyOffset();
        FireAnimationEndEvent(toIndex, info);
    }

    if (indexsInAnimation_.empty()) {
        currentProxyInAnimation_ = nullptr;
    }
    auto curChildFrame = GetCurrentFrameNode(toIndex);
    if (curChildFrame) {
        FlushFocus(curChildFrame);
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->FlushUITasks();
    pipeline->FlushMessages();
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
        TAG_LOGI(AceLogTag::ACE_SWIPER, "Remove pan event when disable swipe.");
        gestureHub->RemovePanEvent(panEvent_);
        panEvent_.Reset();
        if (isDragging_) {
            HandleDragEnd(0.0);
        }
    }
}

void SwiperPattern::ProcessDelta(float& delta, float mainSize, float deltaSum)
{
    if (std::abs(delta) > mainSize) {
        delta = delta > 0 ? mainSize : -mainSize;
    }

    if ((std::abs(deltaSum + delta)) > mainSize) {
        delta = GreatNotEqual((deltaSum + delta), 0) ? (mainSize - deltaSum) : (-deltaSum - mainSize);
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
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, true);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_RETURN(tabBarPattern, true);
    if (!tabBarPattern->GetTabContentWillChangeFlag() && tabsPattern->GetInterceptStatus() &&
        currentIndex != comingIndex) {
        tabBarPattern->ResetTabContentWillChangeFlag();
        auto ret = tabsPattern->OnContentWillChange(currentIndex, comingIndex);
        return ret.has_value() ? ret.value() : true;
    }
    tabBarPattern->ResetTabContentWillChangeFlag();
    return true;
}

bool SwiperPattern::CheckSwiperPanEvent(float mainDeltaOrVelocity)
{
    int32_t currentIndex = GetCurrentIndex();
    int32_t comingIndex = currentIndex;
    if (GreatNotEqual(mainDeltaOrVelocity, 0.0)) {
        comingIndex = comingIndex < 1 ? 0 : comingIndex - 1;
    } else if (LessNotEqual(mainDeltaOrVelocity, 0.0)) {
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

void SwiperPattern::HandleTouchBottomLoopOnRTL()
{
    auto currentFirstIndex = GetLoopIndex(currentFirstIndex_);
    auto currentIndex = GetLoopIndex(currentIndex_);
    auto totalCount = TotalCount();
    auto displayCount = GetDisplayCount();
    bool commTouchBottom = (currentFirstIndex == totalCount - 1);
    bool releaseLeftTouchBottomStart = (currentIndex == totalCount - 1);
    bool releaseLeftTouchBottomEnd = (currentFirstIndex == 0);
    bool releaseRightTouchBottom = (currentFirstIndex == totalCount - 1);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN) && IsSwipeByGroup()) {
        commTouchBottom = (currentFirstIndex >= totalCount - displayCount);
        releaseLeftTouchBottomStart = (currentIndex == totalCount - displayCount);
        releaseRightTouchBottom = (currentFirstIndex >= totalCount - displayCount);
        releaseLeftTouchBottomEnd = (currentFirstIndex <= displayCount);
    }
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

    if (releaseLeftTouchBottomEnd && releaseLeftTouchBottomStart &&
        gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT) {
        touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
        return;
    }

    if (releaseRightTouchBottom && currentIndex == 0 &&
        gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT) {
        touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
        return;
    }
}

void SwiperPattern::HandleTouchBottomLoop()
{
    auto currentFirstIndex = GetLoopIndex(currentFirstIndex_);
    auto currentIndex = GetLoopIndex(currentIndex_);
    if (IsHorizontalAndRightToLeft()) {
        currentFirstIndex = TotalCount() - 1 - currentFirstIndex;
        currentIndex = TotalCount() - 1 - currentIndex;
    }

    bool commTouchBottom = (currentFirstIndex == TotalCount() - 1);
    bool releaseTouchBottom = (currentIndex == TotalCount() - 1);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN) && IsSwipeByGroup()) {
        commTouchBottom = currentFirstIndex >= TotalCount() - GetDisplayCount();
        releaseTouchBottom = currentIndex >= TotalCount() - GetDisplayCount();
    }
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

    bool leftReleaseTouchBottom =
        (commTouchBottom && (currentIndex == 0 && gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT));
    bool rightReleaseTouchBottom = ((currentFirstIndex == 0) && (releaseTouchBottom) &&
                                    gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT);
    if (leftReleaseTouchBottom || rightReleaseTouchBottom) {
        if (currentIndex == 0) {
            // left bottom
            touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
        } else if (releaseTouchBottom) {
            // right bottom
            touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
        }
    }
    return;
}

void SwiperPattern::CalculateGestureStateOnRTL(float additionalOffset, float currentTurnPageRate, int32_t preFirstIndex)
{
    if (GreatNotEqual(additionalOffset, 0.0f)) {
        gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
        needTurn_ = false;
        return;
    }

    if (LessNotEqual(additionalOffset, 0.0f)) {
        gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
        needTurn_ = false;
        return;
    }

    auto currentIndex = GetLoopIndex(currentIndex_);
    auto currentFirstIndex = GetLoopIndex(currentFirstIndex_);
    if (preFirstIndex == 0 && currentFirstIndex == TotalCount() - 1) {
        needTurn_ = true;
        if (isTouchDown_ && GreatOrEqual(mainDeltaSum_, 0.0f)) {
            needTurn_ = false;
        }
    } else if (preFirstIndex == TotalCount() - 1 && currentFirstIndex == 0) {
        needTurn_ = true;
        if (isTouchDown_ && (LessOrEqual(mainDeltaSum_, 0.0f) || currentIndex == 0)) {
            needTurn_ = false;
        }
    }

    if (!IsLoop()) {
        needTurn_ = false;
    }

    if (currentFirstIndex >= currentIndex) {
        gestureState_ = needTurn_ ? GestureState::GESTURE_STATE_FOLLOW_RIGHT : GestureState::GESTURE_STATE_FOLLOW_LEFT;
        return;
    }

    gestureState_ = needTurn_ ? GestureState::GESTURE_STATE_FOLLOW_LEFT : GestureState::GESTURE_STATE_FOLLOW_RIGHT;
}

void SwiperPattern::CalculateGestureState(float additionalOffset, float currentTurnPageRate, int32_t preFirstIndex)
{
    auto currentIndex = GetLoopIndex(currentIndex_);
    auto currentFirstIndex = GetLoopIndex(currentFirstIndex_);
    if (IsHorizontalAndRightToLeft()) {
        preFirstIndex = TotalCount() - 1 - preFirstIndex;
        currentFirstIndex = TotalCount() - 1 - currentFirstIndex;
        currentIndex = TotalCount() - 1 - currentIndex;
    }

    // Keep follow hand
    if (preFirstIndex == 0 && currentFirstIndex == TotalCount() - 1) {
        needTurn_ = true;
        if (isTouchDown_ && LessOrEqual(mainDeltaSum_, 0.0f) && !childScrolling_) {
            needTurn_ = false;
        }
    } else if (preFirstIndex == TotalCount() - 1 && currentFirstIndex == 0) {
        needTurn_ = true;
        if (isTouchDown_ && (GreatOrEqual(mainDeltaSum_, 0.0f) || currentIndex == 0)) {
            needTurn_ = false;
        }
    }

    if (GreatNotEqual(additionalOffset, 0.0f)) {
        gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
        needTurn_ = false;
    } else if (LessNotEqual(additionalOffset, 0.0f)) {
        gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
        needTurn_ = false;
    } else if (currentFirstIndex >= currentIndex) {
        gestureState_ = needTurn_ ? GestureState::GESTURE_STATE_FOLLOW_LEFT : GestureState::GESTURE_STATE_FOLLOW_RIGHT;

        if (!IsLoop() && currentFirstIndex == 0 && GreatOrEqual(mainDeltaSum_, 0.0f)) {
            gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
            needTurn_ = false;
        }

        if (!IsLoop() && currentFirstIndex == TotalCount() - 1 && LessOrEqual(mainDeltaSum_, 0.0f)) {
            gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
            needTurn_ = false;
        }
    } else if (currentFirstIndex < currentIndex) {
        gestureState_ = needTurn_ ? GestureState::GESTURE_STATE_FOLLOW_RIGHT : GestureState::GESTURE_STATE_FOLLOW_LEFT;
    }
    return;
}

std::pair<float, float> SwiperPattern::CalcCurrentPageStatusOnRTL(float additionalOffset) const
{
    float currentTurnPageRate = FLT_MAX;
    auto firstIndex = currentFirstIndex_;
    auto itemMainSize = CalculateVisibleSize();
    for (auto iter = itemPosition_.rbegin(); iter != itemPosition_.rend(); iter++) {
        auto startPos = itemMainSize - iter->second.endPos;
        auto endPos = itemMainSize - iter->second.startPos;
        if (LessNotEqual((startPos + additionalOffset), 0) && LessNotEqual((endPos + additionalOffset), 0)) {
            continue;
        }
        if (GreatOrEqual((startPos + additionalOffset), 0) && GreatNotEqual((endPos + additionalOffset), 0)) {
            firstIndex = iter->first;
            currentTurnPageRate = 0.0f;
            break;
        }
        if (GreatNotEqual((endPos + additionalOffset), 0)) {
            firstIndex = iter->first;
            currentTurnPageRate =
                (NearEqual(endPos, startPos) ? 0 : ((startPos + additionalOffset) / (endPos - startPos)));
            break;
        }
    }

    return std::make_pair(currentTurnPageRate, firstIndex);
}

float SwiperPattern::CalcCurrentTurnPageRate() const
{
    if (IsHorizontalAndRightToLeft()) {
        return CalcCurrentPageStatusOnRTL(0.0f).first;
    }

    return CalcCurrentPageStatus(0.0f).first;
}

std::pair<float, float> SwiperPattern::CalcCurrentPageStatus(float additionalOffset) const
{
    float currentTurnPageRate = FLT_MAX;
    auto firstIndex = currentFirstIndex_;
    for (const auto& iter : itemPosition_) {
        if (LessNotEqual((iter.second.startPos + additionalOffset), 0) &&
            LessNotEqual((iter.second.endPos + additionalOffset), 0)) {
            continue;
        }
        if (GreatOrEqual((iter.second.startPos + additionalOffset), 0) &&
            GreatNotEqual((iter.second.endPos + additionalOffset), 0)) {
            firstIndex = iter.first;
            currentTurnPageRate = 0.0f;
            break;
        }
        if (GreatNotEqual((iter.second.endPos + additionalOffset), 0)) {
            firstIndex = iter.first;
            currentTurnPageRate =
                (NearEqual(iter.second.endPos, iter.second.startPos)
                        ? 0
                        : ((iter.second.startPos + additionalOffset) / (iter.second.endPos - iter.second.startPos)));
            break;
        }
    }

    return std::make_pair(currentTurnPageRate, firstIndex);
}

void SwiperPattern::StopIndicatorAnimation(bool ifImmediately)
{
    AnimationUtils::StopAnimation(indicatorAnimation_);

    if (stopIndicatorAnimationFunc_) {
        stopIndicatorAnimationFunc_(ifImmediately);
    }
}

void SwiperPattern::FireWillHideEvent(int32_t willHideIndex) const
{
    if (!hasTabsAncestor_) {
        return;
    }
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
    if (!hasTabsAncestor_) {
        return;
    }
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
    auto parent = host->GetAncestorNodeOfFrame(false);
    CHECK_NULL_VOID(parent);
    while (parent) {
        if (parent->GetTag() == V2::PAGE_ETS_TAG || parent->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            break;
        }
        parent = parent->GetAncestorNodeOfFrame(false);
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
        pagePattern->AddOnHiddenChange(host->GetId(), std::move(onHiddenChange));
    }

    if (parent->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
        auto navDestinationePattern = parent->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationePattern);
        auto navDestinationEventHub = navDestinationePattern->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(navDestinationEventHub);
        navDestinationEventHub->AddOnHiddenChange(host->GetId(), std::move(onHiddenChange));
    }
}

void SwiperPattern::RemoveOnHiddenChange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto parent = host->GetAncestorNodeOfFrame(false);
    CHECK_NULL_VOID(parent);
    while (parent) {
        if (parent->GetTag() == V2::PAGE_ETS_TAG || parent->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            break;
        }
        parent = parent->GetAncestorNodeOfFrame(false);
    }
    CHECK_NULL_VOID(parent);
    if (parent->GetTag() == V2::PAGE_ETS_TAG) {
        auto pagePattern = parent->GetPattern<PagePattern>();
        CHECK_NULL_VOID(pagePattern);
        pagePattern->RemoveOnHiddenChange(host->GetId());
    }
    if (parent->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
        auto navDestinationePattern = parent->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationePattern);
        auto navDestinationEventHub = navDestinationePattern->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(navDestinationEventHub);
        navDestinationEventHub->RemoveOnHiddenChange(host->GetId());
    }
}

std::optional<RefPtr<UINode>> SwiperPattern::FindLazyForEachNode(RefPtr<UINode> baseNode, bool isSelfNode) const
{
    if (AceType::DynamicCast<LazyForEachNode>(baseNode)) {
        return baseNode;
    }
    if (AceType::DynamicCast<RepeatVirtualScrollNode>(baseNode)) {
        return baseNode;
    }
    if (!isSelfNode && AceType::DynamicCast<FrameNode>(baseNode)) {
        return std::nullopt;
    }
    for (const auto& child : baseNode->GetChildren()) {
        auto targetNode = FindLazyForEachNode(child, false);
        if (targetNode.has_value()) {
            return targetNode;
        }
    }
    return std::nullopt;
}

std::optional<RefPtr<UINode>> SwiperPattern::FindForEachNode(const RefPtr<UINode>& baseNode, bool isSelfNode) const
{
    if (AceType::DynamicCast<ForEachNode>(baseNode)) {
        return baseNode;
    }

    if (AceType::DynamicCast<RepeatVirtualScrollNode>(baseNode)) {
        return baseNode;
    }

    if (!isSelfNode && AceType::DynamicCast<FrameNode>(baseNode)) {
        return std::nullopt;
    }

    for (const auto& child : baseNode->GetChildren()) {
        auto targetNode = FindForEachNode(child, false);
        if (targetNode.has_value()) {
            return targetNode;
        }
    }

    return std::nullopt;
}

RefPtr<NodePaintMethod> SwiperPattern::CreateNodePaintMethod()
{
    const auto props = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, nullptr);
    const auto& paddingProperty = props->GetPaddingProperty();
    bool needClipPadding = paddingProperty != nullptr;
    bool needPaintFade = !IsLoop() && GetEdgeEffect() == EdgeEffect::FADE && !NearZero(fadeOffset_);
    auto paintMethod =
        MakeRefPtr<SwiperPaintMethod>(GetDirection(), IsHorizontalAndRightToLeft() ? -fadeOffset_ : fadeOffset_);
    paintMethod->SetNeedPaintFade(needPaintFade);
    paintMethod->SetNeedClipPadding(needClipPadding);
    return paintMethod;
}

void SwiperPattern::UpdateNodeRate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto frameRateManager = pipelineContext->GetFrameRateManager();
    CHECK_NULL_VOID(frameRateManager);
    auto nodeId = host->GetId();
    auto iter = frameRateRange_.find(SwiperDynamicSyncSceneType::GESTURE);
    if (iter != frameRateRange_.end() && iter->second->IsValid()) {
        auto expectedRate = iter->second->preferred_;
        TAG_LOGI(AceLogTag::ACE_SWIPER, "Expected gesture frame rate is: %{public}d", expectedRate);
        frameRateManager->UpdateNodeRate(nodeId, expectedRate);
    }
}

int32_t SwiperPattern::GetMaxDisplayCount() const
{
    if (!swiperParameters_ || !swiperParameters_->maxDisplayCountVal.has_value()) {
        return 0;
    }

    auto maxDisplayCount = swiperParameters_->maxDisplayCountVal.value();
    if (maxDisplayCount < MAX_DISPLAY_COUNT_MIN || maxDisplayCount > MAX_DISPLAY_COUNT_MAX) {
        return 0;
    }

    auto childrenSize = RealTotalCount();
    if (childrenSize <= maxDisplayCount) {
        return 0;
    }

    return maxDisplayCount;
}

void SwiperPattern::SetIndicatorChangeIndexStatus(bool withAnimation, std::optional<int32_t> startIndex)
{
    auto indicatorNode = GetCommonIndicatorNode();
    if (!indicatorNode || !IsIndicator(indicatorNode->GetTag())) {
        return;
    }

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    CHECK_NULL_VOID(indicatorPattern);

    indicatorPattern->SetChangeIndexWithAnimation(withAnimation);
    indicatorPattern->SetStartIndex(startIndex);
}

void SwiperPattern::SetIndicatorJumpIndex(std::optional<int32_t> jumpIndex)
{
    if (GetMaxDisplayCount() <= 0) {
        return;
    }
    auto indicatorNode = GetCommonIndicatorNode();
    if (!indicatorNode || !IsIndicator(indicatorNode->GetTag())) {
        return;
    }

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    CHECK_NULL_VOID(indicatorPattern);

    indicatorPattern->SetJumpIndex(jumpIndex);
}

void SwiperPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    CHECK_NULL_VOID(json);
    Pattern::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }

    auto nestedScroll = GetNestedScroll().forward;
    json->PutExtAttr("nestedScroll",
        nestedScroll == NestedScrollMode::SELF_ONLY ? "SwiperNestedScrollMode.SELF_ONLY"
                                                    : "SwiperNestedScrollMode.SELF_FIRST",
        filter);
    json->PutExtAttr("stopWhenTouched", IsStopWhenTouched() ? "true" : "false", filter);
    json->PutExtAttr("currentIndex", currentIndex_, filter);
    json->PutExtAttr("currentOffset", currentOffset_, filter);
    json->PutExtAttr("uiCastJumpIndex", uiCastJumpIndex_.value_or(-1), filter);

    if (indicatorIsBoolean_) {
        return;
    }

    auto indicatorType = GetIndicatorType();
    const char* indicator = "indicator";
    if (indicatorType == SwiperIndicatorType::DOT) {
        json->PutExtAttr(indicator, SwiperHelper::GetDotIndicatorStyle(GetSwiperParameters()).c_str(), filter);
    } else if (indicatorType == SwiperIndicatorType::ARC_DOT) {
            json->PutExtAttr(indicator, SwiperPattern::GetArcDotIndicatorStyle().c_str(), filter);
    } else {
        json->PutExtAttr(
            indicator, SwiperHelper::GetDigitIndicatorStyle(GetSwiperDigitalParameters()).c_str(), filter);
    }
}

void SwiperPattern::FromJson(const std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(json);
    currentIndex_ = json->GetInt("currentIndex");
    auto currentOffset = json->GetDouble("currentOffset");
    auto jumpIndex = json->GetInt("uiCastJumpIndex");
    if (currentOffset != currentOffset_) {
        auto delta = currentOffset - currentOffset_;
        UpdateCurrentOffset(delta);
    } else if (jumpIndex >= 0) {
        jumpIndex_ = jumpIndex;
        MarkDirtyNodeSelf();
    }
    Pattern::FromJson(json);
}

GestureState SwiperPattern::GetGestureState()
{
    auto gestureState = gestureState_;
    if (gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT ||
        gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT) {
        gestureState_ = GestureState::GESTURE_STATE_NONE;
    }

    return gestureState;
}

void SwiperPattern::SetSwiperController(const RefPtr<SwiperController>& controller)
{
    CHECK_NULL_VOID(controller);
    swiperController_ = controller;
    SwiperHelper::InitSwiperController(controller, WeakClaim(this));
}

void SwiperPattern::SetPropertyAnimationIsRunning(bool propertyAnimationIsRunning)
{
    propertyAnimationIsRunning_ = propertyAnimationIsRunning;
}

bool SwiperPattern::GetPropertyAnimationIsRunning()
{
    return propertyAnimationIsRunning_;
}

bool SwiperPattern::IsItemOverlay() const
{
    if (itemPosition_.empty()) {
        return false;
    }
    float lastItemEndPos = 0.0f;
    for (auto& item : itemPosition_) {
        auto frameNode = item.second.node;
        if (!frameNode) {
            continue;
        }
        auto renderContext = frameNode->GetRenderContext();
        if (!renderContext) {
            continue;
        }
        RectF rect = renderContext->GetPaintRectWithoutTransform();
        if (item.first == itemPosition_.begin()->first) {
            lastItemEndPos = direction_ == Axis::HORIZONTAL ? rect.Right() : rect.Bottom();
            continue;
        }
        float currentItemStartPos = direction_ == Axis::HORIZONTAL ? rect.Left() : rect.Top();
        if (GreatNotEqual(lastItemEndPos, currentItemStartPos)) {
            return true;
        }
        lastItemEndPos = direction_ == Axis::HORIZONTAL ? rect.Right() : rect.Bottom();
    }
    return false;
}

void SwiperPattern::CheckSpecialItemCount() const
{
    auto swiperNode = AceType::DynamicCast<SwiperNode>(GetHost());
    CHECK_NULL_VOID(swiperNode);
    swiperNode->SetSpecialItemCount(indicatorId_.has_value() + leftButtonId_.has_value() + rightButtonId_.has_value() +
                                    leftCaptureId_.has_value() + rightCaptureId_.has_value());
}

int32_t SwiperPattern::CheckIndexRange(int32_t index) const
{
    auto itemCount = TotalCount();
    auto displayCount = GetDisplayCount();
    if (index < 0 || index >= itemCount || displayCount >= itemCount) {
        index = 0;
    } else if (!IsLoop() && index > itemCount - displayCount) {
        index = itemCount - displayCount;
    }
    return index;
}

void SwiperPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("isLastIndicatorFocused", isLastIndicatorFocused_);
    json->Put("moveDirection", moveDirection_);
    json->Put("indicatorDoingAnimation", indicatorDoingAnimation_);
    json->Put("hasVisibleChangeRegistered", hasVisibleChangeRegistered_);
    json->Put("isVisible", isVisible_);
    json->Put("isVisibleArea", isVisibleArea_);
    json->Put("isWindowShow", isWindowShow_);
    json->Put("IsCustomSize", isCustomSize_);
    json->Put("indicatorIsBoolean", indicatorIsBoolean_);
    json->Put("isAtHotRegion", isAtHotRegion_);
    json->Put("isDragging", isDragging_);
    json->Put("isTouchDown", isTouchDown_);
    json->Put("preLoop", preLoop_.has_value() ? std::to_string(preLoop_.value()).c_str() : "null");
    json->Put("indicatorId", indicatorId_.has_value() ? std::to_string(indicatorId_.value()).c_str() : "null");
    json->Put("leftButtonId", leftButtonId_.has_value() ? std::to_string(leftButtonId_.value()).c_str() : "null");
    json->Put("rightButtonId", rightButtonId_.has_value() ? std::to_string(rightButtonId_.value()).c_str() : "null");
    json->Put("crossMatchChild", crossMatchChild_);
    json->Put(
        "uiCastJumpIndex", uiCastJumpIndex_.has_value() ? std::to_string(uiCastJumpIndex_.value()).c_str() : "null");
    json->Put("jumpIndex", jumpIndex_.has_value() ? std::to_string(jumpIndex_.value()).c_str() : "null");
    json->Put("targetIndex", targetIndex_.has_value() ? std::to_string(targetIndex_.value()).c_str() : "null");
    json->Put(
        "pauseTargetIndex", pauseTargetIndex_.has_value() ? std::to_string(pauseTargetIndex_.value()).c_str() : "null");
    json->Put("velocity", velocity_.has_value() ? std::to_string(velocity_.value()).c_str() : "null");
    json->Put("curve", GetCurveIncludeMotion() ? GetCurveIncludeMotion()->ToString().c_str() : "null");
    json->Put("isFinishAnimation", isFinishAnimation_);
    json->Put("mainSizeIsMeasured", mainSizeIsMeasured_);
    json->Put("usePropertyAnimation", propertyAnimationIsRunning_);
    json->Put("isUserFinish", isUserFinish_);
    json->Put("isVoluntarilyClear", isVoluntarilyClear_);
    json->Put("isIndicatorLongPress", isIndicatorLongPress_);
    json->Put("stopIndicatorAnimation", stopIndicatorAnimation_);
    json->Put("isTouchPad", isTouchPad_);
    json->Put("surfaceChangedCallbackId",
        surfaceChangedCallbackId_.has_value() ? std::to_string(surfaceChangedCallbackId_.value()).c_str() : "null");
    json->Put("currentIndex", currentIndex_);
    json->Put("oldIndex", oldIndex_);
    BuildOffsetInfo(json);
    BuildIndicatorTypeInfo(json);
    BuildItemPositionInfo(json);
    BuildPanDirectionInfo(json);
    BuildAxisInfo(json);
}

void SwiperPattern::BuildOffsetInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("currentOffset", std::to_string(currentOffset_).c_str());
    json->Put("fadeOffset", std::to_string(fadeOffset_).c_str());
    json->Put("touchBottomRate", std::to_string(touchBottomRate_).c_str());
    json->Put("currentIndexOffset", std::to_string(currentIndexOffset_).c_str());
    json->Put("gestureSwipeIndex", gestureSwipeIndex_);
    json->Put("currentFirstIndex", currentFirstIndex_);
    json->Put("startMainPos", startMainPos_);
    json->Put("endMainPos", endMainPos_);
    json->Put("contentMainSize", contentMainSize_);
    json->Put("contentCrossSize", contentCrossSize_);
    json->Put("propertyAnimationIndex", propertyAnimationIndex_);
    json->Put("mainDeltaSum", mainDeltaSum_);
}

void SwiperPattern::BuildAxisInfo(std::unique_ptr<JsonValue>& json)
{
    switch (direction_) {
        case Axis::NONE: {
            json->Put("Axis", "NONE");
            break;
        }
        case Axis::HORIZONTAL: {
            json->Put("Axis", "HORIZONTAL");
            break;
        }
        case Axis::FREE: {
            json->Put("Axis", "FREE");
            break;
        }
        case Axis::VERTICAL: {
            json->Put("Axis", "VERTICAL");
            break;
        }
        default: {
            break;
        }
    }
}

void SwiperPattern::BuildItemPositionInfo(std::unique_ptr<JsonValue>& json)
{
    if (!itemPosition_.empty()) {
        std::unique_ptr<JsonValue> children = JsonUtil::Create(true);
        for (auto item : itemPosition_) {
            std::unique_ptr<JsonValue> child = JsonUtil::CreateArray(true);
            child->Put("id", item.first);
            child->Put("startPos", std::to_string(item.second.startPos).c_str());
            child->Put("endPos", std::to_string(item.second.endPos).c_str());
            children->Put(child);
        }
        json->Put("itemPosition", children);
    }
    if (!itemPositionInAnimation_.empty()) {
        std::unique_ptr<JsonValue> children = JsonUtil::CreateArray(true);
        for (auto item : itemPositionInAnimation_) {
            std::unique_ptr<JsonValue> child = JsonUtil::Create(true);
            child->Put("id", item.first);
            child->Put("startPos", std::to_string(item.second.startPos).c_str());
            child->Put("endPos", std::to_string(item.second.endPos).c_str());
            children->Put(child);
        }
        json->Put("itemPositionInAnimation", children);
    }
}

void SwiperPattern::BuildIndicatorTypeInfo(std::unique_ptr<JsonValue>& json)
{
    if (lastSwiperIndicatorType_.has_value()) {
        switch (lastSwiperIndicatorType_.value()) {
            case SwiperIndicatorType::DOT: {
                json->Put("SwiperIndicatorType", "DOT");
                break;
            }
            case SwiperIndicatorType::DIGIT: {
                json->Put("SwiperIndicatorType", "DIGIT");
                break;
            }
            default: {
                break;
            }
        }
    } else {
        json->Put("lastSwiperIndicatorType", "null");
    }
}

void SwiperPattern::BuildPanDirectionInfo(std::unique_ptr<JsonValue>& json)
{
    switch (panDirection_.type) {
        case PanDirection::NONE: {
            json->Put("PanDirection", "NONE");
            break;
        }
        case PanDirection::LEFT: {
            json->Put("PanDirection", "LEFT");
            break;
        }
        case PanDirection::RIGHT: {
            json->Put("PanDirection", "RIGHT");
            break;
        }
        case PanDirection::HORIZONTAL: {
            json->Put("PanDirection", "HORIZONTAL");
            break;
        }
        case PanDirection::UP: {
            json->Put("PanDirection", "UP");
            break;
        }
        case PanDirection::DOWN: {
            json->Put("PanDirection", "DOWN");
            break;
        }
        case PanDirection::VERTICAL: {
            json->Put("PanDirection", "VERTICAL");
            break;
        }
        case PanDirection::ALL: {
            json->Put("PanDirection", "ALL");
            break;
        }
        default: {
            break;
        }
    }
}

void SwiperPattern::SetPageFlipMode(int32_t pageFlipMode)
{
    if (pageFlipMode < 0 || pageFlipMode > PAGE_FLIP_MODE_SIZE - 1) {
        pageFlipMode_ = PageFlipMode::CONTINUOUS;
        return;
    }
    pageFlipMode_ = static_cast<PageFlipMode>(pageFlipMode);
}

RefPtr<FrameNode> SwiperPattern::GetCommonIndicatorNode()
{
    if (isBindIndicator_) {
        return GetIndicatorNode();
    } else {
        CHECK_NULL_RETURN(indicatorId_.has_value(), nullptr);
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        return DynamicCast<FrameNode>(host->GetChildAtIndex(host->GetChildIndexById(GetIndicatorId())));
    }
}
} // namespace OHOS::Ace::NG
