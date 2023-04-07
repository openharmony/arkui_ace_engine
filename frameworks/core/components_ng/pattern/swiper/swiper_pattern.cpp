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
#include "base/ressched/ressched_report.h"
#include "base/utils/utils.h"
#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/pattern/swiper/swiper_layout_algorithm.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/pattern/swiper/swiper_utils.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

// TODO use theme.
constexpr Dimension MIN_TURN_PAGE_VELOCITY = 10.0_vp;
constexpr Dimension MIN_DRAG_DISTANCE = 25.0_vp;
constexpr Dimension INDICATOR_BORDER_RADIUS = 16.0_vp;

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
    }
}

void SwiperPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    oldIndex_ = currentIndex_;
    InitSwiperIndicator();

    auto childrenSize = TotalCount();
    if (layoutProperty->GetIndex().has_value() && CurrentIndex() >= 0) {
        currentIndex_ = CurrentIndex();
        layoutProperty->UpdateIndexWithoutMeasure(currentIndex_);
    } else {
        LOGE("index is not valid: %{public}d, items size: %{public}d", CurrentIndex(), childrenSize);
    }

    CalculateCacheRange();
    RegisterVisibleAreaChange();
    InitSwiperController();
    InitTouchEvent(gestureHub);
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
            gestureHub->AddPanEvent(
                swiperPattern->panEvent_, swiperPattern->panDirection_, 1, swiperPattern->distance_);
        }
    };
    swiperController_->SetAddSwiperEventCallback(std::move(addSwiperEventCallback));
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
        needFocusNode = focusChildren.back();
    }
    CHECK_NULL_VOID(needFocusNode);
    lastWeakShowNode_ = AceType::WeakClaim(AceType::RawPtr(curShowFrame));
    if (swiperFocusHub->IsCurrentFocus()) {
        needFocusNode->RequestFocusImmediately();
    } else {
        swiperFocusHub->SetLastWeakFocusNode(AceType::WeakClaim(AceType::RawPtr(needFocusNode)));
    }
}

WeakPtr<FocusHub> SwiperPattern::GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode)
{
    auto swiperHost = GetHost();
    CHECK_NULL_RETURN(swiperHost, nullptr);
    auto swiperFocusHub = swiperHost->GetFocusHub();
    CHECK_NULL_RETURN(swiperFocusHub, nullptr);
    auto focusChildren = swiperFocusHub->GetChildren();
    CHECK_NULL_RETURN_NOLOG(!focusChildren.empty(), nullptr);
    CHECK_NULL_RETURN_NOLOG(IsShowIndicator(), nullptr);
    auto indicatorNode = focusChildren.back();
    CHECK_NULL_RETURN(indicatorNode, nullptr);
    auto lastShowNode = lastWeakShowNode_.Upgrade();
    CHECK_NULL_RETURN(lastShowNode, nullptr);
    auto lastShowFocusHub = lastShowNode->GetFocusHub();
    CHECK_NULL_RETURN(lastShowFocusHub, nullptr);

    auto curFocusNode = currentFocusNode.Upgrade();
    CHECK_NULL_RETURN(curFocusNode, nullptr);

    if ((curFocusNode == indicatorNode) && ((direction_ == Axis::HORIZONTAL && step == FocusStep::UP) ||
                                               (direction_ == Axis::VERTICAL && step == FocusStep::LEFT))) {
        isLastIndicatorFocused_ = false;
        return lastShowFocusHub;
    }
    if ((curFocusNode != indicatorNode) && ((direction_ == Axis::HORIZONTAL && step == FocusStep::DOWN) ||
                                               (direction_ == Axis::VERTICAL && step == FocusStep::RIGHT))) {
        isLastIndicatorFocused_ = true;
        return AceType::WeakClaim(AceType::RawPtr(indicatorNode));
    }
    return nullptr;
}

bool SwiperPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (isInit_) {
        isInit_ = false;
    } else {
        OnIndexChange();
    }

    auto curChild = dirty->GetOrCreateChildByIndex(currentIndex_);
    CHECK_NULL_RETURN(curChild, false);
    auto curChildFrame = curChild->GetHostNode();
    CHECK_NULL_RETURN(curChildFrame, false);
    FlushFocus(curChildFrame);

    if (config.skipMeasure && config.skipLayout) {
        return false;
    }

    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto swiperLayoutAlgorithm = DynamicCast<SwiperLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(swiperLayoutAlgorithm, false);
    preItemRange_ = swiperLayoutAlgorithm->GetItemRange();
    currentIndex_ = swiperLayoutAlgorithm->GetCurrentIndex();
    oldIndex_ = currentIndex_;
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    layoutProperty->UpdateIndexWithoutMeasure(currentIndex_);
    maxChildSize_ = swiperLayoutAlgorithm->GetMaxChildSize();
    return GetEdgeEffect() == EdgeEffect::FADE || paddingProperty != nullptr;
}

void SwiperPattern::CalculateCacheRange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = host->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    auto displayCount = GetDisplayCount();
    auto cacheCount = layoutProperty->GetCachedCount().value_or(1);
    auto loadCount = cacheCount * 2 + displayCount;
    auto totalCount = TotalCount();
    if (totalCount <= 0) {
        LOGE("Total count of swiper children is not positive.");
        return;
    }

    if (loadCount >= totalCount) { // Load all items.
        startIndex_ = 0;
        endIndex_ = totalCount - 1;
        LOGD("Load all items, range [%{public}d - %{public}d]", startIndex_, endIndex_);
        return;
    }

    if (!IsLoop()) {
        startIndex_ = std::max(currentIndex_ - cacheCount, 0);
        endIndex_ = std::min(currentIndex_ + displayCount + cacheCount - 1, totalCount - 1);
    } else {
        startIndex_ = (currentIndex_ - cacheCount + totalCount) % totalCount;
        endIndex_ = (currentIndex_ + displayCount + cacheCount - 1 + totalCount) % totalCount;
    }

    LOGD("Cache range [%{public}d - %{public}d], totalCount: %{public}d", startIndex_, endIndex_, totalCount);
}

void SwiperPattern::FireChangeEvent() const
{
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireChangeEvent(currentIndex_);
    swiperEventHub->FireIndicatorChangeEvent(currentIndex_);
    swiperEventHub->FireChangeDoneEvent(moveDirection_);
}

void SwiperPattern::FireAnimationStartEvent() const
{
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireAnimationStartEvent(currentIndex_);
}

void SwiperPattern::FireAnimationEndEvent() const
{
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireAnimationEndEvent(currentIndex_);
}

void SwiperPattern::SwipeToWithoutAnimation(int32_t index)
{
    LOGD("Swipe to index: %{public}d without animation", index);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    currentIndex_ = index;
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateIndexWithoutMeasure(currentIndex_);
    FireChangeEvent();
    oldIndex_ = currentIndex_;
    CalculateCacheRange();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void SwiperPattern::SwipeTo(int32_t index)
{
    LOGD("Swipe to index: %{public}d with animation, duration: %{public}d", index, GetDuration());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto targetIndex = std::clamp(index, 0, TotalCount() - 1);
    if (currentIndex_ == targetIndex) {
        LOGD("Target index is same with current index.");
        return;
    }

    StopAutoPlay();
    StopTranslateAnimation();
    targetIndex_ = targetIndex;

    if (GetDuration() == 0 || !isVisible_) {
        SwipeToWithoutAnimation(index);
        return;
    }

    // TODO Adapt displayCount.
    auto translateOffset = targetIndex_.value() > currentIndex_ ? -GetTranslateLength() : GetTranslateLength();
    PlayTranslateAnimation(0, translateOffset, targetIndex_.value(), true);
}

void SwiperPattern::ShowNext()
{
    indicatorDoingAnimation_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childrenSize = TotalCount();
    if (currentIndex_ >= childrenSize - GetDisplayCount() && !IsLoop()) {
        LOGW("already last one, can't show next");
        return;
    }
    StopAutoPlay();
    StopTranslateAnimation();
    if (childrenSize > 0 && GetDisplayCount() != 0) {
        if (isVisible_) {
            auto endPosition = GetTranslateLength();
            PlayTranslateAnimation(0, -endPosition, (currentIndex_ + 1) % childrenSize, true);
        } else {
            SwipeToWithoutAnimation((currentIndex_ + 1) % childrenSize);
        }
    }
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireIndicatorChangeEvent(currentIndex_);
}

void SwiperPattern::ShowPrevious()
{
    indicatorDoingAnimation_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childrenSize = TotalCount();
    if (currentIndex_ <= 0 && !IsLoop()) {
        LOGW("already first one, can't show previous");
        return;
    }
    StopAutoPlay();
    StopTranslateAnimation();
    if (childrenSize > 0 && GetDisplayCount() != 0) {
        if (isVisible_) {
            auto endPosition = GetTranslateLength();
            PlayTranslateAnimation(0, endPosition, (currentIndex_ + childrenSize - 1) % childrenSize, true);
        } else {
            SwipeToWithoutAnimation((currentIndex_ + childrenSize - 1) % childrenSize);
        }
    }
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireIndicatorChangeEvent(currentIndex_);
}

void SwiperPattern::FinishAnimation()
{
    StopTranslateAnimation();
    if (swiperController_ && swiperController_->GetFinishCallback()) {
        swiperController_->GetFinishCallback()();
    }
}

void SwiperPattern::StopTranslateAnimation()
{
    if (controller_ && !controller_->IsStopped()) {
        controller_->Stop();
    }
}

void SwiperPattern::StopSpringAnimation()
{
    if (springController_ && !springController_->IsStopped()) {
        springController_->Stop();
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

void SwiperPattern::InitSwiperIndicator()
{
    auto swiperNode = GetHost();
    CHECK_NULL_VOID(swiperNode);
    RefPtr<FrameNode> indicatorNode;
    CHECK_NULL_VOID(swiperNode->GetLastChild());
    if (swiperNode->GetLastChild()->GetTag() != V2::SWIPER_INDICATOR_ETS_TAG) {
        LOGI("Swiper create new indicator");
        if (!IsShowIndicator()) {
            return;
        }
        indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        swiperNode->AddChild(indicatorNode);
    } else {
        LOGI("Swiper indicator already exist");
        indicatorNode = DynamicCast<FrameNode>(swiperNode->GetLastChild());
        if (!IsShowIndicator()) {
            swiperNode->RemoveChild(indicatorNode);
            return;
        }
    }
    CHECK_NULL_VOID(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    CHECK_NULL_VOID(indicatorPattern);
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = indicatorNode->GetPaintProperty<SwiperIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (swiperParameters_.dimLeft.has_value()) {
        layoutProperty->UpdateLeft(swiperParameters_.dimLeft.value());
    }
    if (swiperParameters_.dimTop.has_value()) {
        layoutProperty->UpdateTop(swiperParameters_.dimTop.value());
    }
    if (swiperParameters_.dimRight.has_value()) {
        layoutProperty->UpdateRight(swiperParameters_.dimRight.value());
    }
    if (swiperParameters_.dimBottom.has_value()) {
        layoutProperty->UpdateBottom(swiperParameters_.dimBottom.value());
    }
    if (swiperParameters_.dimSize.has_value()) {
        paintProperty->UpdateSize(swiperParameters_.dimSize.value());
    }
    if (swiperParameters_.maskValue.has_value()) {
        paintProperty->UpdateIndicatorMask(swiperParameters_.maskValue.value());
    }
    if (swiperParameters_.colorVal.has_value()) {
        paintProperty->UpdateColor(swiperParameters_.colorVal.value());
    }
    if (swiperParameters_.selectedColorVal.has_value()) {
        paintProperty->UpdateSelectedColor(swiperParameters_.selectedColorVal.value());
    }

    auto renderContext = indicatorNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    BorderRadiusProperty radius;
    radius.SetRadius(INDICATOR_BORDER_RADIUS);
    renderContext->UpdateBorderRadius(radius);

    indicatorNode->MarkModifyDone();
    indicatorNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
            if (info.GetInputEventType() == InputEventType::AXIS) {
                return;
            }
            pattern->HandleDragStart();
        }
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            if (info.GetInputEventType() == InputEventType::AXIS) {
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
            if (info.GetInputEventType() == InputEventType::AXIS) {
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

    distance_ = DEFAULT_PAN_DISTANCE;
    auto host = GetHost();
    if (host) {
        auto context = host->GetContext();
        if (context) {
            distance_ = static_cast<float>(context->NormalizeToPx(Dimension(DEFAULT_PAN_DISTANCE, DimensionUnit::VP)));
        }
    }
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->AddPanEvent(panEvent_, panDirection_, 1, distance_);
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
    if (isVisible) {
        isVisible_ = true;
        StartAutoPlay();
    } else {
        StopAutoPlay();
    }
}

void SwiperPattern::UpdateCurrentOffset(float offset)
{
    currentOffset_ = currentOffset_ + offset;
    float contentSize = MainSize() - GetBorderAndPaddingWidth();
    turnPageRate_ = currentOffset_ / contentSize;
    if (NearEqual(GetTranslateLength(), 0.0f)) {
        turnPageRate_ = 0.0f;
    } else {
        turnPageRate_ = currentOffset_ / GetTranslateLength();
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    if (host->GetLastChild()->GetTag() == V2::SWIPER_INDICATOR_ETS_TAG && !indicatorDoingAnimation_) {
        auto indicatorNode = DynamicCast<FrameNode>(host->GetLastChild());
        indicatorNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

float SwiperPattern::GetBorderAndPaddingWidth()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, 0);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    return GetDirection() == Axis::HORIZONTAL ? padding.left.value_or(0.0f) + padding.right.value_or(0.0f)
                                              : padding.top.value_or(0.0f) + padding.bottom.value_or(0.0f);
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
        controller_->Pause();
    }

    if (springController_ && springController_->IsRunning()) {
        springController_->Pause();
    }

    // Stop auto play when touch down.
    StopAutoPlay();
}

void SwiperPattern::HandleTouchUp()
{
    if (controller_ && controller_->GetStatus() == Animator::Status::PAUSED) {
        controller_->Resume();
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
    currentOffset_ = std::fmod(currentOffset_, MainSize());
}

void SwiperPattern::HandleDragUpdate(const GestureEvent& info)
{
    auto mainDelta = static_cast<float>(info.GetMainDelta());

    auto dragPoint =
        PointF(static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()));
    if (IsOutOfHotRegion(dragPoint)) {
        return;
    }

    auto isOutOfBoundary = IsOutOfBoundary(mainDelta + currentOffset_);
    if (!IsLoop() && isOutOfBoundary) {
        auto edgeEffect = GetEdgeEffect();
        if (edgeEffect == EdgeEffect::SPRING) {
            LOGD("Swiper has reached boundary, can't drag any more, effect spring.");
            auto mainOffset = std::fmod(currentOffset_, MainSize());
            auto friction = CalculateFriction(std::abs(mainOffset) / MainSize());
            UpdateCurrentOffset(friction * mainDelta);
            return;
        }

        if (edgeEffect == EdgeEffect::FADE) {
            LOGD("Swiper has reached boundary, can't drag any more, effect fade");
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            currentOffset_ += mainDelta;
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
            return;
        }

        if (edgeEffect == EdgeEffect::NONE) {
            LOGD("Swiper has reached boundary, can't drag any more.");
            return;
        }
    }

    UpdateCurrentOffset(static_cast<float>(mainDelta));
}

void SwiperPattern::HandleDragEnd(double dragVelocity)
{
    const auto& addEventCallback = swiperController_->GetAddTabBarEventCallback();
    if (addEventCallback) {
        addEventCallback();
    }
    LOGD("Drag end velocity: %{public}lf, currentOffset: %{public}lf", dragVelocity, currentOffset_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    // Play edge effect animation.
    if (!IsLoop() && IsOutOfBoundary(currentOffset_)) {
        auto edgeEffect = GetEdgeEffect();
        if (edgeEffect == EdgeEffect::SPRING) {
            PlaySpringAnimation(dragVelocity);
            return;
        }

        if (edgeEffect == EdgeEffect::FADE) {
            PlayFadeAnimation();
            return;
        }

        if (edgeEffect == EdgeEffect::NONE) {
            UpdateCurrentOffset(0.0f);
            return;
        }
    }

#ifdef OHOS_PLATFORM
    ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
#endif
    // Play translate animation.
    auto mainSize = GetTranslateLength();
    if (LessOrEqual(mainSize, 0)) {
        LOGE("Main size is not positive.");
        return;
    }

    int32_t nextIndex = currentIndex_;
    float start = currentOffset_;
    float end = 0.0f;
    if ((std::abs(dragVelocity) > MIN_TURN_PAGE_VELOCITY.ConvertToPx() &&
            std::abs(currentOffset_) > MIN_DRAG_DISTANCE.ConvertToPx() &&
            GreatNotEqual(dragVelocity * currentOffset_, 0.0)) ||
        (std::abs(currentOffset_) > mainSize / 2 && std::abs(dragVelocity) <= MIN_TURN_PAGE_VELOCITY.ConvertToPx())) {
        auto intervalSize = static_cast<int32_t>(std::floor(std::abs(currentOffset_) / mainSize)) + 1;
        auto direction = GreatNotEqual(
            std::abs(dragVelocity) > MIN_TURN_PAGE_VELOCITY.ConvertToPx() ? dragVelocity : currentOffset_, 0.0);
        end = direction ? mainSize * intervalSize : -mainSize * intervalSize;
        nextIndex = direction ? (nextIndex - intervalSize) : (nextIndex + intervalSize);
    }

    // Adjust next item index when loop and index is out of range.
    auto childrenSize = TotalCount();
    if (IsLoop()) {
        if (nextIndex < 0) {
            nextIndex = childrenSize + nextIndex;
        } else if (nextIndex >= childrenSize && childrenSize > 0) {
            nextIndex = nextIndex % childrenSize;
        }
    } else {
        nextIndex = std::clamp(nextIndex, 0, childrenSize - 1);
    }

    PlayTranslateAnimation(start, end, nextIndex);
    moveDirection_ = dragVelocity <= 0;
}

void SwiperPattern::PlayTranslateAnimation(float startPos, float endPos, int32_t nextIndex, bool restartAutoPlay)
{
    LOGD("Play translate animation startPos: %{public}lf, endPos: %{public}lf, nextIndex: %{public}d", startPos, endPos,
        nextIndex);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto curve = GetCurve();
    if (!curve) {
        curve = Curves::LINEAR;
    }

    // If animation is still running, stop it before play new animation.
    StopTranslateAnimation();
    StopAutoPlay();

    auto translate = AceType::MakeRefPtr<CurveAnimation<double>>(startPos, endPos, curve);
    auto weak = AceType::WeakClaim(this);
    translate->AddListener(Animation<double>::ValueCallback([weak, startPos, endPos](double value) {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        if (!NearEqual(value, startPos) && !NearEqual(value, endPos) && !NearEqual(startPos, endPos)) {
            float moveRate =
                Curves::EASE_OUT->MoveInternal(static_cast<float>((value - startPos) / (endPos - startPos)));
            value = startPos + (endPos - startPos) * moveRate;
        }
        swiper->UpdateCurrentOffset(static_cast<float>(value - swiper->currentOffset_));
    }));

    if (!controller_) {
        controller_ = AceType::MakeRefPtr<Animator>(host->GetContext());
    }
    controller_->ClearStartListeners();
    controller_->ClearStopListeners();
    controller_->ClearInterpolators();

    controller_->AddStartListener([weak]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->FireAnimationStartEvent();
    });

    controller_->AddStopListener([weak, nextIndex, restartAutoPlay]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->OnTranslateFinish(nextIndex, restartAutoPlay);
    });
    controller_->SetDuration(GetDuration());
    controller_->AddInterpolator(translate);
    controller_->Play();
}

void SwiperPattern::PlaySpringAnimation(double dragVelocity)
{
    LOGD("Play spring animation start");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!springController_) {
        springController_ = AceType::MakeRefPtr<Animator>(host->GetContext());
    }
    springController_->ClearStartListeners();
    springController_->ClearStopListeners();
    springController_->ClearInterpolators();

    auto mainSize = MainSize();
    if (LessOrEqual(mainSize, 0)) {
        LOGE("Main size is not positive.");
        return;
    }

    // TODO use theme.
    constexpr float SPRING_SCROLL_MASS = 0.5f;
    constexpr float SPRING_SCROLL_STIFFNESS = 100.0f;
    constexpr float SPRING_SCROLL_DAMPING = 15.55635f;
    const RefPtr<SpringProperty> DEFAULT_OVER_SPRING_PROPERTY =
        AceType::MakeRefPtr<SpringProperty>(SPRING_SCROLL_MASS, SPRING_SCROLL_STIFFNESS, SPRING_SCROLL_DAMPING);
    ExtentPair extentPair = ExtentPair(0.0, 0.0);
    float friction = CalculateFriction(std::abs(currentOffset_) / mainSize);
    auto scrollMotion = AceType::MakeRefPtr<ScrollMotion>(
        currentOffset_, dragVelocity * friction, extentPair, extentPair, DEFAULT_OVER_SPRING_PROPERTY);
    scrollMotion->AddListener([weak = AceType::WeakClaim(this)](double position) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->UpdateCurrentOffset(static_cast<float>(position) - swiper->currentOffset_);
        }
    });
    springController_->AddStartListener([weak = AceType::WeakClaim(this)]() {
        auto swiperPattern = weak.Upgrade();
        if (swiperPattern) {
            swiperPattern->FireAnimationStartEvent();
        }
    });
    springController_->AddStopListener([weak = AceType::WeakClaim(this)]() {
        auto swiperPattern = weak.Upgrade();
        if (swiperPattern) {
            swiperPattern->FireAnimationEndEvent();
        }
    });
    springController_->PlayMotion(scrollMotion);
}

void SwiperPattern::PlayFadeAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (NearZero(currentOffset_)) {
        return;
    }

    LOGD("Play fade animation start");
    if (!fadeController_) {
        fadeController_ = AceType::MakeRefPtr<Animator>(host->GetContext());
    }
    fadeController_->ClearAllListeners();

    auto translate = AceType::MakeRefPtr<CurveAnimation<double>>(currentOffset_, 0, Curves::LINEAR);
    auto weak = AceType::WeakClaim(this);
    translate->AddListener(Animation<double>::ValueCallback([weak](double value) {
        auto swiper = weak.Upgrade();
        if (swiper && swiper->GetHost()) {
            swiper->currentOffset_ = static_cast<float>(value);
            swiper->GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }));

    fadeController_->AddStartListener([weak]() {
        auto swiperPattern = weak.Upgrade();
        if (swiperPattern) {
            swiperPattern->FireAnimationStartEvent();
        }
    });
    fadeController_->AddStopListener([weak]() {
        auto swiperPattern = weak.Upgrade();
        if (swiperPattern) {
            swiperPattern->FireAnimationEndEvent();
        }
    });
    constexpr float FADE_DURATION = 500.0f;
    fadeController_->SetDuration(FADE_DURATION);
    fadeController_->AddInterpolator(translate);
    fadeController_->Play();
}

bool SwiperPattern::IsOutOfBoundary(float mainOffset) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);

    if (IsLoop()) {
        return false;
    }

    auto index = currentIndex_;
    auto positiveAxis = Positive(mainOffset);
    auto mainSize = MainSize();
    if (Positive(mainSize)) {
        auto interval = mainOffset / mainSize;
        index -= static_cast<int32_t>(positiveAxis ? floorf(interval) : ceilf(interval));
    }

    auto isOutOfStart = index == 0 && NonNegative(mainOffset);
    auto isOutOfEnd = index == TotalCount() - GetDisplayCount() && NonPositive(mainOffset);
    return isOutOfStart || isOutOfEnd;
}

float SwiperPattern::MainSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    return geometryNode->GetFrameSize().MainSize(GetDirection());
}

float SwiperPattern::GetItemSpace() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, 0);
    return ConvertToPx(swiperLayoutProperty->GetItemSpace().value_or(0.0_vp),
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
    return swiperLayoutProperty->GetDisplayCount().value_or(1);
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
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, true);
    return swiperPaintProperty->GetLoop().value_or(true);
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

int32_t SwiperPattern::TotalCount() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    // last child is swiper indicator
    return IsShowIndicator() ? host->TotalChildCount() - 1 : host->TotalChildCount();
}

float SwiperPattern::GetTranslateLength() const
{
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0.0);

    auto itemSpace = SwiperUtils::GetItemSpace(layoutProperty);
    auto translateLength = GetDirection() == Axis::HORIZONTAL ? maxChildSize_.Width() : maxChildSize_.Height();
    return translateLength + itemSpace;
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
void SwiperPattern::PostTranslateTask(uint32_t delayTime)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    auto weak = AceType::WeakClaim(this);
    translateTask_.Reset([weak, delayTime] {
        auto swiper = weak.Upgrade();
        if (swiper) {
            auto childrenSize = swiper->TotalCount();
            auto displayCount = swiper->GetDisplayCount();
            if (childrenSize <= 0 || displayCount <= 0) {
                return;
            }
            auto endPosition = swiper->GetTranslateLength();
            swiper->PlayTranslateAnimation(0, -endPosition, (swiper->currentIndex_ + 1) % childrenSize, false);
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
        if (visible) {
            swiperPattern->isVisible_ = true;
            swiperPattern->StartAutoPlay();
        } else {
            swiperPattern->isVisible_ = false;
            swiperPattern->translateTask_.Cancel();
        }
    };
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    pipeline->RemoveVisibleAreaChangeNode(host->GetId());
    pipeline->AddVisibleAreaChangeNode(host, 0.0f, callback);
    hasVisibleChangeRegistered_ = true;
}

bool SwiperPattern::NeedAutoPlay() const
{
    bool reachEnd = currentIndex_ >= TotalCount() - 1 && !IsLoop();
    return IsAutoPlay() && !reachEnd && isVisible_;
}

void SwiperPattern::OnTranslateFinish(int32_t nextIndex, bool restartAutoPlay)
{
    currentOffset_ = 0.0;
    targetIndex_.reset();
    if (currentIndex_ != nextIndex) {
        currentIndex_ = nextIndex;
        auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateIndexWithoutMeasure(nextIndex);
        FireChangeEvent();
        oldIndex_ = nextIndex;
        CalculateCacheRange();
    }
    if (restartAutoPlay) {
        StartAutoPlay();
    }
    FireAnimationEndEvent();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto indicatorNode = host->GetLastChild();
    CHECK_NULL_VOID(indicatorNode);
    if (indicatorNode->GetTag() == V2::SWIPER_INDICATOR_ETS_TAG) {
        indicatorNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }

    auto delayTime = GetInterval() - GetDuration();
    delayTime = std::clamp(delayTime, 0, delayTime);
    if (NeedAutoPlay()) {
        PostTranslateTask(delayTime);
    }
}

} // namespace OHOS::Ace::NG
