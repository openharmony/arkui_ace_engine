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

#include "core/components_ng/pattern/list/list_pattern.h"

#include <optional>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SCROLL_STATE_IDLE = 0;
constexpr int32_t SCROLL_STATE_SCROLL = 1;
constexpr int32_t SCROLL_STATE_FLING = 2;
constexpr float SCROLL_MAX_TIME = 300.0f; // Scroll Animate max time 0.3 second
} // namespace

void ListPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

void ListPattern::OnModifyDone()
{
    if (!isInitialized_) {
        jumpIndex_ = GetLayoutProperty<ListLayoutProperty>()->GetInitialIndex().value_or(0);
        isInitialized_ = true;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_VOID(listLayoutProperty);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto axis = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    if (!scrollableEvent_) {
        scrollableEvent_ = MakeRefPtr<ScrollableEvent>(axis);
        auto task = [weak = WeakClaim(this)](double offset, int32_t source) -> bool {
            auto pattern = weak.Upgrade();
            CHECK_NULL_RETURN(pattern, false);
            pattern->SetScrollStop(false);
            pattern->SetScrollState(source);
            if (source != SCROLL_FROM_START) {
                pattern->UpdateCurrentOffset(static_cast<float>(offset));
            }
            return true;
        };
        scrollableEvent_->SetScrollPositionCallback(std::move(task));

        auto scrollEnd = [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->ProcessScrollEnd();
        };
        scrollableEvent_->SetScrollEndCallback(std::move(scrollEnd));

        auto listEventHub = host->GetEventHub<ListEventHub>();
        auto onScrollBegin = listEventHub->GetOnScrollBegin();
        if (onScrollBegin) {
            auto scrollBeginTask = [weak = WeakClaim(this)](Dimension dx, Dimension dy) {
                ScrollInfo scrollInfo;
                scrollInfo.dx = dx;
                scrollInfo.dy = dy;
                auto pattern = weak.Upgrade();
                CHECK_NULL_RETURN(pattern, scrollInfo);
                auto host = pattern->GetHost();
                CHECK_NULL_RETURN(host, scrollInfo);
                auto listEventHub = host->GetEventHub<ListEventHub>();
                CHECK_NULL_RETURN(listEventHub, scrollInfo);
                auto onScrollBegin = listEventHub->GetOnScrollBegin();
                if (onScrollBegin) {
                    scrollInfo = onScrollBegin(dx, dy);
                }
                return scrollInfo;
            };
            scrollableEvent_->SetScrollBeginCallback(std::move(scrollBeginTask));
        }
        gestureHub->AddScrollableEvent(scrollableEvent_);
    } else {
        if (scrollableEvent_->GetAxis() != axis) {
            scrollableEvent_->SetAxis(axis);
            gestureHub->RemoveScrollableEvent(scrollableEvent_);
            gestureHub->AddScrollableEvent(scrollableEvent_);
        }
    }

    auto edgeEffect = listLayoutProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING);
    if (edgeEffect == EdgeEffect::SPRING && !scrollEffect_) {
        auto scrollEdgeEffect = AceType::MakeRefPtr<NG::ScrollSpringEffect>();
        SetScrollEdgeEffect(scrollEdgeEffect);
        gestureHub->AddScrollEdgeEffect(GetDirection(), scrollEffect_);
    }

    auto focusHub = host->GetFocusHub();
    if (focusHub) {
        InitOnKeyEvent(focusHub);
    }
}

bool ListPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto listLayoutAlgorithm = DynamicCast<ListLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(listLayoutAlgorithm, false);
    itemPosition_ = listLayoutAlgorithm->GetItemPosition();
    maxListItemIndex_ = listLayoutAlgorithm->GetMaxListItemIndex();
    if (jumpIndex_) {
        estimateOffset_ = listLayoutAlgorithm->GetEstimateOffset();
        if (!itemPosition_.empty()) {
            currentOffset_ = itemPosition_.begin()->second.first;
        }
        jumpIndex_.reset();
    }
    auto finalOffset = listLayoutAlgorithm->GetCurrentOffset();
    lastOffset_ = currentOffset_;
    currentOffset_ = currentOffset_ - finalOffset;
    currentDelta_ = 0.0f;
    startMainPos_ = listLayoutAlgorithm->GetStartPosition();
    endMainPos_ = listLayoutAlgorithm->GetEndPosition();
    CheckScrollable();

    bool indexChanged =
        (startIndex_ != listLayoutAlgorithm->GetStartIndex()) || (endIndex_ != listLayoutAlgorithm->GetEndIndex());
    startIndex_ = listLayoutAlgorithm->GetStartIndex();
    endIndex_ = listLayoutAlgorithm->GetEndIndex();
    if (currentOffset_ != lastOffset_) {
        ProcessEvent(indexChanged, finalOffset);
    }

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    return listLayoutProperty && listLayoutProperty->GetDivider().has_value();
}

void ListPattern::ProcessEvent(bool indexChanged, float finalOffset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listEventHub = host->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(listEventHub);

    auto onScroll = listEventHub->GetOnScroll();
    if (onScroll) {
        auto source = GetScrollState();
        auto offsetPX = Dimension(finalOffset);
        auto offsetVP = Dimension(offsetPX.ConvertToVp(), DimensionUnit::VP);
        if (source == SCROLL_FROM_UPDATE) {
            onScroll(offsetVP, static_cast<V2::ScrollState>(SCROLL_STATE_SCROLL));
        } else if (source == SCROLL_FROM_ANIMATION || source == SCROLL_FROM_ANIMATION_SPRING) {
            onScroll(offsetVP, static_cast<V2::ScrollState>(SCROLL_STATE_FLING));
        } else {
            onScroll(offsetVP, static_cast<V2::ScrollState>(SCROLL_STATE_IDLE));
        }
    }

    if (indexChanged) {
        auto onScrollIndex = listEventHub->GetOnScrollIndex();
        if (onScrollIndex) {
            onScrollIndex(startIndex_, endIndex_);
        }
    }

    bool scrollUpToCrossLine = GreatNotEqual(lastOffset_, 0.0) && LessOrEqual(currentOffset_, 0.0);
    bool scrollDownToCrossLine = LessNotEqual(lastOffset_, 0.0) && GreatOrEqual(currentOffset_, 0.0);
    if ((startIndex_ == 0) && (scrollUpToCrossLine || scrollDownToCrossLine)) {
        auto onReachStart = listEventHub->GetOnReachStart();
        if (onReachStart) {
            onReachStart();
        }
    }
    if ((endIndex_ == maxListItemIndex_) && (scrollUpToCrossLine || scrollDownToCrossLine)) {
        auto onReachEnd = listEventHub->GetOnReachEnd();
        if (onReachEnd) {
            onReachEnd();
        }
    }
}

void ListPattern::CheckScrollable()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    if (itemPosition_.empty()) {
        scrollable_ = false;
    } else {
        if ((itemPosition_.begin()->first == 0) && (itemPosition_.rbegin()->first == maxListItemIndex_)) {
            scrollable_ = GreatNotEqual((endMainPos_ - startMainPos_), GetMainContentSize());
        } else {
            scrollable_ = true;
        }
    }

    if (scrollableEvent_) {
        scrollableEvent_->SetEnabled(scrollable_);
    }
}

RefPtr<LayoutAlgorithm> ListPattern::CreateLayoutAlgorithm()
{
    auto listLayoutAlgorithm = MakeRefPtr<ListLayoutAlgorithm>(startIndex_, endIndex_);
    if (jumpIndex_) {
        listLayoutAlgorithm->SetIndex(jumpIndex_.value());
        listLayoutAlgorithm->SetIndexAlignment(scrollIndexAlignment_);
    }
    listLayoutAlgorithm->SetCurrentOffset(currentDelta_);
    listLayoutAlgorithm->SetItemsPosition(itemPosition_);
    if (IsOutOfBoundary(false)) {
        listLayoutAlgorithm->SetOverScrollFeature();
    }
    return listLayoutAlgorithm;
}

void ListPattern::UpdateCurrentOffset(float offset)
{
    currentDelta_ = currentDelta_ - offset;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

    if (!IsOutOfBoundary() || !scrollable_) {
        return;
    }

    // over scroll in drag update from normal to over scroll.
    float overScroll = 0.0f;
    // over scroll in drag update during over scroll.
    auto startPos = startMainPos_ - currentDelta_;
    if ((itemPosition_.begin()->first == 0) && Positive(startPos)) {
        overScroll = startPos;
    } else {
        overScroll = GetMainContentSize() - (endMainPos_ - currentDelta_);
    }

    if (scrollState_ == SCROLL_FROM_UPDATE) {
        // adjust offset.
        auto friction = CalculateFriction(std::abs(overScroll) / GetMainContentSize());
        currentDelta_ = currentDelta_ * friction;
    }
}

void ListPattern::ProcessScrollEnd()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listEventHub = host->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(listEventHub);
    auto onScrollStop = listEventHub->GetOnScrollStop();
    if (onScrollStop) {
        onScrollStop();
    }
    SetScrollStop(true);
}

float ListPattern::GetMainContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    return geometryNode->GetPaddingSize().MainSize(GetDirection());
}

Axis ListPattern::GetDirection() const
{
    auto listLayoutProperty = GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(listLayoutProperty, Axis::VERTICAL);
    return listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
}

bool ListPattern::IsOutOfBoundary(bool useCurrentDelta)
{
    if (itemPosition_.empty()) {
        return false;
    }
    auto startPos = useCurrentDelta ? startMainPos_ - currentDelta_ : startMainPos_;
    auto endPos = useCurrentDelta ? endMainPos_ - currentDelta_ : endMainPos_;
    bool outOfStart = (startIndex_ == 0) && Positive(startPos);
    bool outOfEnd = (endIndex_ == maxListItemIndex_) && LessNotEqual(endPos, GetMainContentSize());
    return outOfStart || outOfEnd;
}

void ListPattern::SetScrollEdgeEffect(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    if (scrollEffect && scrollEffect->IsSpringEffect()) {
        auto springEffect = AceType::DynamicCast<ScrollSpringEffect>(scrollEffect);
        CHECK_NULL_VOID(springEffect);
        springEffect->SetOutBoundaryCallback([weak = AceType::WeakClaim(this)]() {
            auto list = weak.Upgrade();
            if (list) {
                return list->IsOutOfBoundary();
            }
            return false;
        });
        // add callback to springEdgeEffect
        SetEdgeEffectCallback(scrollEffect);
        scrollEffect_ = scrollEffect;
    }
}

void ListPattern::SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    scrollEffect->SetCurrentPositionCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        if (list) {
            return list->startMainPos_ - list->currentDelta_;
        }
        return 0.0;
    });
    scrollEffect->SetLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        return list->GetMainContentSize() - (list->endMainPos_ - list->startMainPos_);
    });
    scrollEffect->SetTrailingCallback([]() -> double { return 0.0; });
    scrollEffect->SetInitLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        return list->GetMainContentSize() - (list->endMainPos_ - list->startMainPos_);
    });
    scrollEffect->SetInitTrailingCallback([]() -> double { return 0.0; });
}

void ListPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
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

bool ListPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code == KeyCode::KEY_PAGE_DOWN) {
        LOGD("Keycode is PgDn. Scroll to next page");
        ScrollPage(false);
        return true;
    }
    if (event.code == KeyCode::KEY_PAGE_UP) {
        LOGD("Keycode is PgDn. Scroll to next page");
        ScrollPage(true);
        return true;
    }
    if (event.IsDirectionalKey()) {
        HandleDirectionKey(event.code);
        return true;
    }
    return false;
}

bool ListPattern::HandleDirectionKey(KeyCode code)
{
    if ((GetDirection() == Axis::VERTICAL && code == KeyCode::KEY_DPAD_UP) ||
        (GetDirection() == Axis::HORIZONTAL && code == KeyCode::KEY_DPAD_LEFT)) {
        auto nextIndex = std::clamp(scrollIndex_ - 1, 0, maxListItemIndex_);
        if (nextIndex == scrollIndex_) {
            return false;
        }
        scrollIndex_ = nextIndex;
        LOGD("Scorll to next index: %{public}d", scrollIndex_);
        // Need to update: current selection
        ScrollToIndex(scrollIndex_, ScrollIndexAlignment::ALIGN_TOP);
        return true;
    }
    if ((GetDirection() == Axis::VERTICAL && code == KeyCode::KEY_DPAD_DOWN) ||
        (GetDirection() == Axis::HORIZONTAL && code == KeyCode::KEY_DPAD_RIGHT)) {
        auto nextIndex = std::clamp(scrollIndex_ + 1, 0, maxListItemIndex_);
        if (nextIndex == scrollIndex_) {
            return false;
        }
        scrollIndex_ = nextIndex;
        LOGD("Scorll to previous index: %{public}d", scrollIndex_);
        // Need to update: current selection
        ScrollToIndex(scrollIndex_, ScrollIndexAlignment::ALIGN_BUTTON);
        return true;
    }
    return false;
}

void ListPattern::AnimateTo(float position, float duration, const RefPtr<Curve>& curve, bool limitDuration)
{
    LOGI("AnimateTo:%f, duration:%f", position, duration);
    if (!animator_) {
        animator_ = AceType::MakeRefPtr<Animator>(PipelineBase::GetCurrentContext());
    }
    if (!animator_->IsStopped()) {
        animator_->Stop();
    }
    animator_->ClearInterpolators();

    auto animation = AceType::MakeRefPtr<CurveAnimation<float>>(GetTotalOffset(), position, curve);
    animation->AddListener([weakScroll = AceType::WeakClaim(this)](float value) {
        auto list = weakScroll.Upgrade();
        if (list) {
            list->UpdateCurrentOffset(list->GetTotalOffset() - value);
        }
    });
    animator_->AddInterpolator(animation);
    animator_->SetDuration(static_cast<int32_t>(limitDuration ? std::min(duration, SCROLL_MAX_TIME) : duration));
    animator_->Play();
}

void ListPattern::ScrollTo(float position)
{
    LOGI("ScrollTo:%{public}f", position);
    UpdateCurrentOffset(GetTotalOffset() - position);
}

void ListPattern::ScrollToIndex(int32_t index, ScrollIndexAlignment align)
{
    LOGI("ScrollToIndex:%{public}d", index);
    if (index >= 0 && index <= maxListItemIndex_) {
        jumpIndex_ = index;
        scrollIndexAlignment_ = align;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void ListPattern::ScrollToEdge(ScrollEdgeType scrollEdgeType)
{
    LOGI("ScrollToEdge:%{public}zu", scrollEdgeType);
    if (((scrollEdgeType == ScrollEdgeType::SCROLL_TOP) && GetDirection() == Axis::VERTICAL) ||
        ((scrollEdgeType == ScrollEdgeType::SCROLL_LEFT) && GetDirection() == Axis::HORIZONTAL)) {
        ScrollToIndex(0, ScrollIndexAlignment::ALIGN_TOP);
    } else if (((scrollEdgeType == ScrollEdgeType::SCROLL_BOTTOM) && GetDirection() == Axis::VERTICAL) ||
        ((scrollEdgeType == ScrollEdgeType::SCROLL_RIGHT) && GetDirection() == Axis::HORIZONTAL)) {
        ScrollToIndex(maxListItemIndex_, ScrollIndexAlignment::ALIGN_BUTTON);
    }
}

bool ListPattern::ScrollPage(bool reverse)
{
    LOGI("ScrollPage:%{public}d", reverse);
    float distance = reverse ? GetMainContentSize() : -GetMainContentSize();
    UpdateCurrentOffset(distance);
    return true;
}

Offset ListPattern::GetCurrentOffset() const
{
    if (GetDirection() == Axis::HORIZONTAL) {
        return {GetTotalOffset(), 0.0};
    }
    return {0.0, GetTotalOffset()};
}
} // namespace OHOS::Ace::NG
