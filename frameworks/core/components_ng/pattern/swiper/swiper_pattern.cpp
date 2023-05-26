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
#include <string>

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
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_arrow_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

// TODO use theme.
constexpr float MIN_TURN_PAGE_VELOCITY = 1200.0f; // Pixels per second
constexpr Dimension INDICATOR_BORDER_RADIUS = 16.0_vp;
constexpr char PROPERTY_NAME[] = "CurrentOffsetTimes";

} // namespace

SwiperPattern::SwiperPattern()
{
    swiperController_ = MakeRefPtr<SwiperController>();
}

void SwiperPattern::FromJson(const std::unique_ptr<JsonValue>& json)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto currentOffsetTimes = static_cast<float>(json->GetDouble("currentOffsetTimes"));
    if (currentOffsetTimes != currentOffsetTimes_) {
        LOGD("UITree currentOffsetTimes=%{public}f", currentOffsetTimes);
        currentOffsetTimes_ = currentOffsetTimes;
        OnlyUpdateAnimatableProperty();
    }
    Pattern::FromJson(json);
}

bool SwiperPattern::CalculateItemRange()
{
    bool needMeasure = false;
    auto property = GetLayoutProperty<SwiperLayoutProperty>();
    bool isStretch =
        property->GetDisplayCount().has_value() ||
        property->GetDisplayMode().value_or(SwiperDisplayMode::STRETCH) == SwiperDisplayMode::STRETCH;
    auto prevMargin = static_cast<float>(property->GetPrevMarginValue(0.0_px).ConvertToPx());
    auto nextMargin = static_cast<float>(property->GetNextMarginValue(0.0_px).ConvertToPx());
    int32_t prevCount = Positive(prevMargin) && isStretch ? 1 : 0;
    int32_t nextCount = Positive(nextMargin) && isStretch ? 1 : 0;

    for (int32_t index = std::floor(currentOffsetTimes_) - prevCount;
         static_cast<float>(index) < (currentOffsetTimes_ + GetDisplayCount() + nextCount); ++index) {
        if (itemRange_.find((index + TotalCount()) % TotalCount()) == itemRange_.end()) {
            itemRange_.insert((index + TotalCount()) % TotalCount());
            needMeasure = true;
        }
    }
    return needMeasure;
}

void SwiperPattern::AttachNodeAnimatableProperty()
{
    std::function<void(float)> onCallbackEvent = [weak = WeakClaim(this)](float value) {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        swiperPattern->UpdateCurrentOffsetTimes(value);
    };

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->CreateAnimatablePropertyFloat(PROPERTY_NAME, 0.0f, onCallbackEvent);
}

void SwiperPattern::UpdateCurrentOffsetTimes(float value)
{
    if (!needUpdateCurrentOffsetTimes_) {
        return;
    }
    currentOffsetTimes_ = IsLoop() ? std::fmod(value + TotalCount(), TotalCount()) : value;
    bool needMeasure = CalculateItemRange();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(needMeasure ? PROPERTY_UPDATE_MEASURE_SELF : PROPERTY_UPDATE_LAYOUT);
    onlyNeedMeasurePages_ = true;

    if (!IsLoop() && GetEdgeEffect() == EdgeEffect::FADE) {
        overstepBoundaryOffsetTimes_ =
            value - std::clamp(value, 0.0f, static_cast<float>(TotalCount() - GetDisplayCount()));
        if (overstepBoundaryOffsetTimes_ != 0.0f) {
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }
    if (host->GetLastChild()->GetTag() == V2::SWIPER_INDICATOR_ETS_TAG && !indicatorDoingAnimation_) {
        auto indicatorNode = DynamicCast<FrameNode>(host->GetLastChild());
        indicatorNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void SwiperPattern::HandleAnimationEnds()
{
    if (!needUpdateCurrentOffsetTimes_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    oldIndex_ = currentIndex_;
    targetIndex_ = IsLoop() ? (targetIndex_ + TotalCount()) % TotalCount() : targetIndex_;
    host->UpdateAnimatablePropertyFloat(PROPERTY_NAME, static_cast<float>(targetIndex_));
    currentIndex_ = targetIndex_;
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateIndexWithoutMeasure(currentIndex_);
    moveDirection_ = MoveDirection::STATIC;
    animation_ = nullptr;
    OnIndexChange();
    oldIndex_ = currentIndex_;
    FireAnimationEndEvent();

    if (NeedAutoPlay()) {
        GoAutoPlay();
    }
}

void SwiperPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    host->GetRenderContext()->SetClipToBounds(true);
    AttachNodeAnimatableProperty();
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
        swiperEventHub->FireIndicatorChangeEvent(targetIndex);
        swiperEventHub->FireChangeDoneEvent(moveDirection_);
    }
}

void SwiperPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    oldIndex_ = currentIndex_;
    InitIndicator();
    InitArrow();

    auto childrenSize = TotalCount();
    if (layoutProperty->GetIndex().has_value() && CurrentIndex() >= 0) {
        currentIndex_ = CurrentIndex();
        layoutProperty->UpdateIndexWithoutMeasure(currentIndex_);
    } else {
        LOGE("index is not valid: %{public}d, items size: %{public}d", CurrentIndex(), childrenSize);
    }

    targetIndex_ = currentIndex_;
    currentOffsetTimes_ = currentIndex_;
    OnlyUpdateAnimatableProperty();
    CalculateItemRange();
    RegisterVisibleAreaChange();
    InitSwiperController();
    InitTouchEvent();
    InitPanEvent();
    InitOnKeyEvent();

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

    if (IsAutoPlay()) {
        StartAutoPlay();
    } else {
        translateTask_.Cancel();
    }
    SetAccessibilityAction();
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
    auto swiperHost = GetHost();
    CHECK_NULL_RETURN(swiperHost, nullptr);
    auto swiperFocusHub = swiperHost->GetFocusHub();
    CHECK_NULL_RETURN(swiperFocusHub, nullptr);
    auto focusChildren = swiperFocusHub->GetChildren();
    CHECK_NULL_RETURN_NOLOG(!focusChildren.empty(), nullptr);
    auto lastShowNode = lastWeakShowNode_.Upgrade();
    CHECK_NULL_RETURN(lastShowNode, nullptr);
    auto lastShowFocusHub = lastShowNode->GetFocusHub();
    CHECK_NULL_RETURN(lastShowFocusHub, nullptr);
    auto curFocusNode = currentFocusNode.Upgrade();
    CHECK_NULL_RETURN(curFocusNode, nullptr);
    if ((direction_ == Axis::HORIZONTAL && step == FocusStep::UP) ||
        (direction_ == Axis::VERTICAL && step == FocusStep::LEFT)) {
        return PreviousFocus(curFocusNode);
    } else if ((direction_ == Axis::HORIZONTAL && step == FocusStep::DOWN) ||
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
        curFocusNode->SetParentFocusable(true);
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
        curFocusNode->SetParentFocusable(true);
        return nullptr;
    }
    curFocusNode->SetParentFocusable(true);
    return nullptr;
}

bool SwiperPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (isInit_) {
        isInit_ = false;
    } else {
        OnIndexChange();
    }

    oldIndex_ = currentIndex_;
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
    auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    layoutProperty->UpdateIndexWithoutMeasure(currentIndex_);
    maxChildSize_ = swiperLayoutAlgorithm->GetMaxChildSize();
    itemRange_ = swiperLayoutAlgorithm->GetItemRange();
    onlyNeedMeasurePages_ = false;
    return GetEdgeEffect() == EdgeEffect::FADE || paddingProperty != nullptr;
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
    targetIndex_ = index;
    PlayTranslateAnimation(0);
}

void SwiperPattern::SwipeTo(int32_t index)
{
    ForcedStopTranslateAnimation();
    LOGD("Swipe to index: %{public}d with animation, duration: %{public}d", index, GetDuration());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    targetIndex_ = (index < 0 || index > (TotalCount() - 1)) ? DEFAULT_INDEX : index;
    targetIndex_ = IsLoop() ? targetIndex_ : std::clamp(targetIndex_, 0, TotalCount() - GetDisplayCount());
    if (currentIndex_ == targetIndex_) {
        LOGD("Target index is same with current index.");
        return;
    }
    PlayTranslateAnimation(GetDuration());
}

void SwiperPattern::ShowNext()
{
    ForcedStopTranslateAnimation();
    indicatorDoingAnimation_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childrenSize = TotalCount();
    if (currentIndex_ >= childrenSize - GetDisplayCount() && !IsLoop()) {
        LOGW("already last one, can't show next");
        return;
    }
    if (childrenSize <= 0 || GetDisplayCount() <= 0) {
        return;
    }

    targetIndex_ = playingAutoPlay_ ? currentIndex_ + 1 : targetIndex_ + 1;
    targetIndex_ = !IsLoop() ? std::clamp(targetIndex_, 0, TotalCount() - GetDisplayCount()) : targetIndex_;
    moveDirection_ = MoveDirection::ADVANCE;
    PlayTranslateAnimation(GetDuration());

    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireIndicatorChangeEvent(currentIndex_);
}

void SwiperPattern::ShowPrevious()
{
    ForcedStopTranslateAnimation();
    indicatorDoingAnimation_ = false;
    auto childrenSize = TotalCount();
    if (currentIndex_ <= 0 && !IsLoop()) {
        LOGW("already first one, can't show previous");
        return;
    }
    if (childrenSize <= 0 || GetDisplayCount() <= 0) {
        return;
    }
    targetIndex_ = playingAutoPlay_ ? currentIndex_ - 1 : targetIndex_ - 1;
    targetIndex_ = !IsLoop() ? std::clamp(targetIndex_, 0, TotalCount() - GetDisplayCount()) : targetIndex_;
    moveDirection_ = MoveDirection::RETREAT;
    PlayTranslateAnimation(GetDuration());

    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireIndicatorChangeEvent(currentIndex_);
}

void SwiperPattern::FinishAnimation()
{
    PlayTranslateAnimation(0);

    if (swiperController_ && swiperController_->GetFinishCallback()) {
        swiperController_->GetFinishCallback()();
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
    CHECK_NULL_VOID(swiperNode->GetLastChild());
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

void SwiperPattern::InitPanEvent()
{
    auto gestureHub = GetGestureHub();
    CHECK_NULL_VOID(gestureHub);
    if (IsDisableSwipe()) {
        if (panEvent_) {
            gestureHub->RemovePanEvent(panEvent_);
            panEvent_.Reset();
        }
        return;
    }
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

void SwiperPattern::InitTouchEvent()
{
    auto gestureHub = GetGestureHub();
    CHECK_NULL_VOID(gestureHub);
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

void SwiperPattern::InitOnKeyEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID_NOLOG(focusHub);
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

void SwiperPattern::StartAutoPlay()
{
    if (NeedAutoPlay() && !animation_) {
        GoAutoPlay();
    }
}

void SwiperPattern::OnVisibleChange(bool isVisible)
{
    if (isInit_) {
        return;
    }

    if (isVisible) {
        isVisible_ = true;
        StartAutoPlay();
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
    if (!IsLoop() && GetEdgeEffect() == EdgeEffect::SPRING) {
        overstepBoundaryOffsetTimes_ = 0.0f;
    }
    ForcedStopTranslateAnimation();
}

void SwiperPattern::HandleTouchUp()
{
    if (!IsLoop() && GetEdgeEffect() == EdgeEffect::SPRING) {
        overstepBoundaryOffsetTimes_ = 0.0f;
    }

    float duration =
        static_cast<float>(GetDuration()) * (static_cast<float>(targetIndex_) > currentOffsetTimes_
                                                    ? static_cast<float>(targetIndex_) - currentOffsetTimes_
                                                    : currentOffsetTimes_ - static_cast<float>(targetIndex_));

    if (duration == 0.0f && !IsAutoPlay()) {
        return;
    }
    if (returnToOriginalAnimation_) {
        targetIndex_ = !IsLoop() ? std::clamp(targetIndex_, 0, TotalCount() - GetDisplayCount()) : targetIndex_;
        PlayTranslateAnimation(std::round(duration));
    }
}

void SwiperPattern::HandleDragStart()
{
    returnToOriginalAnimation_ = false;

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
}

void SwiperPattern::HandleDragUpdate(const GestureEvent& info)
{
    auto dragPoint =
        PointF(static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()));
    if (IsOutOfHotRegion(dragPoint)) {
        return;
    }

    if (!IsOutOfIndicatorZone(dragPoint)) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto edgeEffect = GetEdgeEffect();
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    float dragOffsetTimes =
        maxChildSize_.MainSize(GetDirection()) != 0 ? mainDelta * -1.0f / maxChildSize_.MainSize(GetDirection()) : 0;

    ForcedStopTranslateAnimation();
    float targetOffsetTimes = currentOffsetTimes_;
    if (IsLoop()) {
        targetOffsetTimes = std::fmod(targetOffsetTimes + dragOffsetTimes + TotalCount(), TotalCount());
    } else if (!IsLoop() && edgeEffect == EdgeEffect::SPRING) {
        if (0 <= targetOffsetTimes && targetOffsetTimes <= static_cast<float>(TotalCount() - GetDisplayCount())) {
            float boundary = std::clamp(
                targetOffsetTimes + dragOffsetTimes, 0.0f, static_cast<float>(TotalCount() - GetDisplayCount()));
            dragOffsetTimes = targetOffsetTimes + dragOffsetTimes - boundary;
            targetOffsetTimes = boundary;
        }
        overstepBoundaryOffsetTimes_ = dragOffsetTimes == 0.0f ? 0.0f : overstepBoundaryOffsetTimes_ + dragOffsetTimes;
        float dampingMagnification = std::exp(-1.884 * std::fabs(overstepBoundaryOffsetTimes_ / GetDisplayCount()));
        targetOffsetTimes = targetOffsetTimes + dragOffsetTimes * dampingMagnification;
    } else if (!IsLoop() && edgeEffect == EdgeEffect::FADE) {
        targetOffsetTimes += dragOffsetTimes;
    } else if (!IsLoop() && edgeEffect == EdgeEffect::NONE) {
        targetOffsetTimes =
            std::clamp(targetOffsetTimes + dragOffsetTimes, 0.0f, static_cast<float>(TotalCount() - GetDisplayCount()));
    }
    targetOffsetTimes = IsLoop() ? std::fmod(targetOffsetTimes + TotalCount(), TotalCount()) : targetOffsetTimes;
    host->UpdateAnimatablePropertyFloat(PROPERTY_NAME, targetOffsetTimes);
}

void SwiperPattern::HandleDragEnd(double dragVelocity)
{
    const auto& addEventCallback = swiperController_->GetAddTabBarEventCallback();
    if (addEventCallback) {
        addEventCallback();
    }
    LOGD("Drag end velocity: %{public}lf", dragVelocity);
    Dimension dragVelocityVp(dragVelocity, DimensionUnit::VP);

    if (dragVelocityVp.ConvertToPx() >= MIN_TURN_PAGE_VELOCITY) {
        targetIndex_ = std::floor(currentOffsetTimes_);
    } else if (dragVelocityVp.ConvertToPx() <= (-1 * MIN_TURN_PAGE_VELOCITY)) {
        targetIndex_ = std::ceil(currentOffsetTimes_);
    } else {
        targetIndex_ = std::round(currentOffsetTimes_);
    }
    targetIndex_ = !IsLoop() ? std::clamp(targetIndex_, 0, TotalCount() - GetDisplayCount()) : targetIndex_;
    if (targetIndex_ > currentOffsetTimes_) {
        moveDirection_ = MoveDirection::ADVANCE;
    } else if (targetIndex_ < currentOffsetTimes_) {
        moveDirection_ = MoveDirection::RETREAT;
    }
    PlayTranslateAnimation(GetDuration());
    returnToOriginalAnimation_ = true;

#ifdef OHOS_PLATFORM
    ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
#endif
}

void SwiperPattern::PlayTranslateAnimation(int32_t duration)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::string propertyName = PROPERTY_NAME;
    AnimationOption option;
    option.SetDuration(isVisible_ ? duration : 0);
    option.SetCurve(GetCurve());
    animation_ = AnimationUtils::StartAnimation(
        option,
        [weak = WeakClaim(this), host, propertyName]() {
            auto swiperPattern = weak.Upgrade();
            CHECK_NULL_VOID(swiperPattern);
            swiperPattern->FireAnimationStartEvent();
            host->UpdateAnimatablePropertyFloat(propertyName, static_cast<float>(swiperPattern->targetIndex_));
        },
        [weak = WeakClaim(this)]() {
            auto swiperPattern = weak.Upgrade();
            CHECK_NULL_VOID(swiperPattern);
            swiperPattern->HandleAnimationEnds();
        });
}

void SwiperPattern::ForcedStopTranslateAnimation()
{
    if (!AnimationUtils::IsRunning(animation_)) {
        animation_ = nullptr;
        return;
    }
    OnlyUpdateAnimatableProperty();
}

void SwiperPattern::OnlyUpdateAnimatableProperty()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::string propertyName = PROPERTY_NAME;
    AnimationOption option;
    option.SetDuration(0);
    option.SetCurve(Curves::LINEAR);
    AnimationUtils::Animate(
        option,
        [weak = WeakClaim(this), host, propertyName, offsetTimes = currentOffsetTimes_]() {
            auto swiperPattern = weak.Upgrade();
            CHECK_NULL_VOID(swiperPattern);
            swiperPattern->needUpdateCurrentOffsetTimes_ = false;
            host->UpdateAnimatablePropertyFloat(propertyName, offsetTimes);
        },
        [weak = WeakClaim(this)]() {
            auto swiperPattern = weak.Upgrade();
            CHECK_NULL_VOID(swiperPattern);
            swiperPattern->needUpdateCurrentOffsetTimes_ = true;
        });
    animation_ = nullptr;
}

void SwiperPattern::GoAutoPlay()
{
    if (!isVisible_) {
        return;
    }
    if (AnimationUtils::IsRunning(animation_)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto delayTime = GetInterval() - GetDuration();
    delayTime = std::clamp(delayTime, 0, delayTime);
    std::string propertyName = PROPERTY_NAME;
    targetIndex_ = currentIndex_ + 1;
    targetIndex_ = !IsLoop() ? std::clamp(targetIndex_, 0, TotalCount() - GetDisplayCount()) : targetIndex_;
    AnimationOption option;
    option.SetDuration(GetDuration());
    option.SetCurve(Curves::LINEAR);
    option.SetDelay(delayTime);
    animation_ = AnimationUtils::StartAnimation(
        option,
        [weak = WeakClaim(this), host, propertyName]() {
            auto swiperPattern = weak.Upgrade();
            CHECK_NULL_VOID(swiperPattern);
            swiperPattern->playingAutoPlay_ = true;
            swiperPattern->FireAnimationStartEvent();
            host->UpdateAnimatablePropertyFloat(propertyName, static_cast<float>(swiperPattern->targetIndex_));
        },
        [weak = WeakClaim(this)]() {
            auto swiperPattern = weak.Upgrade();
            CHECK_NULL_VOID(swiperPattern);
            swiperPattern->playingAutoPlay_ = false;
            swiperPattern->HandleAnimationEnds();
        });
}

void SwiperPattern::ForcedFinishAutoPlay()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::string propertyName = PROPERTY_NAME;
    AnimationOption option;
    option.SetDuration(0);
    option.SetCurve(Curves::LINEAR);
    animation_ = AnimationUtils::StartAnimation(option, [weak = WeakClaim(this), host, propertyName]() {
        auto swiperPattern = weak.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        host->UpdateAnimatablePropertyFloat(propertyName, static_cast<float>(swiperPattern->targetIndex_));
    });
}

RefPtr<GestureEventHub> SwiperPattern::GetGestureHub() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(hub, nullptr);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, nullptr);
    return gestureHub;
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

int32_t SwiperPattern::GetCachedCount() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, 1);
    return swiperLayoutProperty->GetCachedCount().value_or(1);
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
    CHECK_NULL_RETURN(swiperPaintProperty, Curves::LINEAR);
    return swiperPaintProperty->GetCurve().value_or(Curves::LINEAR);
}

bool SwiperPattern::IsLoop() const
{
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
    if (HasLeftButtonNode() && HasRightButtonNode()) {
        num += 2;
    }

    return host->TotalChildCount() - num;
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

void SwiperPattern::OnWindowShow()
{
    isVisible_ = true;
    StartAutoPlay();
}

void SwiperPattern::OnWindowHide()
{
    isVisible_ = false;
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

void SwiperPattern::IndicatorHover(bool hoverFlag)
{
    if (HasLeftButtonNode() && HasRightButtonNode()) {
        auto swiperNode = GetHost();
        CHECK_NULL_VOID(swiperNode);
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        CHECK_NULL_VOID(swiperIndicatorTheme);
        hoverRatio_ = hoverFlag ? swiperIndicatorTheme->GetArrowZoomOutScale() : 1.0f;
        swiperNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
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
    arrowLayoutProperty->UpdateIsShowBoard(layoutProperty->GetIsShowBoardValue());
    arrowLayoutProperty->UpdateBoardSize(layoutProperty->GetBoardSizeValue());
    arrowLayoutProperty->UpdateBoardColor(layoutProperty->GetBoardColorValue());
    arrowLayoutProperty->UpdateArrowSize(layoutProperty->GetArrowSizeValue());
    arrowLayoutProperty->UpdateArrowColor(layoutProperty->GetArrowColorValue());
    arrowLayoutProperty->UpdateIsSiderMiddle(layoutProperty->GetIsSiderMiddleValue());
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
} // namespace OHOS::Ace::NG
