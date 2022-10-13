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
    isInitialized_ = listLayoutAlgorithm->GetIsInitialized();
    itemPosition_ = listLayoutAlgorithm->GetItemPosition();
    maxListItemIndex_ = listLayoutAlgorithm->GetMaxListItemIndex();
    auto finalOffset = listLayoutAlgorithm->GetCurrentOffset();
    auto adjustOffset = currentDelta_ - finalOffset;
    totalOffset_ = totalOffset_ - adjustOffset;

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto listEventHub = host->GetEventHub<ListEventHub>();
    CHECK_NULL_RETURN(listEventHub, false);
    jumpIndex_.reset();
    currentDelta_ = 0.0f;
    CheckScrollable();

    bool indexChanged =
        (startIndex_ != listLayoutAlgorithm->GetStartIndex()) || (endIndex_ != listLayoutAlgorithm->GetEndIndex());
    startIndex_ = listLayoutAlgorithm->GetStartIndex();
    endIndex_ = listLayoutAlgorithm->GetEndIndex();
    if (totalOffset_ != lastOffset_) {
        if (indexChanged) {
            auto onScrollIndex = listEventHub->GetOnScrollIndex();
            if (onScrollIndex) {
                onScrollIndex(startIndex_, endIndex_);
            }
        }
        bool scrollUpToCrossLine = GreatNotEqual(lastOffset_, 0.0) && LessOrEqual(totalOffset_, 0.0);
        bool scrollDownToCrossLine = LessNotEqual(lastOffset_, 0.0) && GreatOrEqual(totalOffset_, 0.0);
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

    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    return listLayoutProperty && listLayoutProperty->GetDivider().has_value();
}

void ListPattern::CheckScrollable()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    bool scrollable = true;
    if (itemPosition_.empty()) {
        scrollable = false;
    } else {
        if ((itemPosition_.begin()->first == 0) && (itemPosition_.rbegin()->first == maxListItemIndex_)) {
            scrollable = LessOrEqual(
                (itemPosition_.rbegin()->second.second - itemPosition_.begin()->second.first), GetMainContentSize());
        }
    }

    if (scrollableEvent_) {
        scrollableEvent_->SetEnabled(scrollable);
    }
}

RefPtr<LayoutAlgorithm> ListPattern::CreateLayoutAlgorithm()
{
    auto listLayoutAlgorithm = MakeRefPtr<ListLayoutAlgorithm>(startIndex_, endIndex_);
    if (jumpIndex_) {
        listLayoutAlgorithm->SetIndex(jumpIndex_.value());
    }
    listLayoutAlgorithm->SetCurrentOffset(currentDelta_);
    listLayoutAlgorithm->SetIsInitialized(isInitialized_);
    listLayoutAlgorithm->SetItemsPosition(itemPosition_);

    // check overlay scroll.
    std::optional<float> overlayScroll;
    if (!itemPosition_.empty() && (!NearZero(currentDelta_) || (scrollState_ == SCROLL_FROM_ANIMATION_SPRING))) {
        if ((itemPosition_.begin()->first == 0) && GreatOrEqual(itemPosition_.begin()->second.first, 0.0)) {
            overlayScroll = itemPosition_.begin()->second.first - 0.0;
        } else if ((itemPosition_.rbegin()->first == maxListItemIndex_) &&
                   LessOrEqual(itemPosition_.rbegin()->second.second, GetMainContentSize())) {
            overlayScroll = GetMainContentSize() - itemPosition_.rbegin()->second.second;
        }
    }
    if (overlayScroll) {
        if (scrollState_ == SCROLL_FROM_UPDATE) {
            // adjust offset.
            auto friction = CalculateFriction(std::abs(overlayScroll.value()) / GetMainContentSize());
            listLayoutAlgorithm->SetCurrentOffset(currentDelta_ * friction);
        }
        listLayoutAlgorithm->SetOverScrollFeature();
    }

    return listLayoutAlgorithm;
}

void ListPattern::UpdateCurrentOffset(float offset)
{
    currentDelta_ = currentDelta_ - offset;
    lastOffset_ = totalOffset_;
    totalOffset_ = totalOffset_ - offset;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

    auto listEventHub = host->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(listEventHub);
    auto onScroll = listEventHub->GetOnScroll();
    if (onScroll) {
        auto source = GetScrollState();
        auto offsetPX = Dimension(offset);
        auto offsetVP = Dimension(offsetPX.ConvertToVp(), DimensionUnit::VP);
        if (source == SCROLL_FROM_UPDATE) {
            onScroll(offsetVP, static_cast<V2::ScrollState>(SCROLL_STATE_SCROLL));
        } else if (source == SCROLL_FROM_ANIMATION || source == SCROLL_FROM_ANIMATION_SPRING) {
            onScroll(offsetVP, static_cast<V2::ScrollState>(SCROLL_STATE_FLING));
        } else {
            onScroll(offsetVP, static_cast<V2::ScrollState>(SCROLL_STATE_IDLE));
        }
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

bool ListPattern::IsOutOfBoundary()
{
    bool outOfStart = false;
    bool outOfEnd = false;
    if (!itemPosition_.empty()) {
        outOfStart = (itemPosition_.begin()->first == 0) && (itemPosition_.begin()->second.first > 0);
        outOfEnd = (itemPosition_.rbegin()->first == maxListItemIndex_) &&
                   (itemPosition_.rbegin()->second.second < GetMainContentSize());
    }
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
            return list->itemPosition_.begin()->second.first - list->currentDelta_;
        }
        return 0.0;
    });
    scrollEffect->SetLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        auto itemPosition = list->GetItemPosition();
        return list->GetMainContentSize() -
               (itemPosition.rbegin()->second.second - list->currentDelta_ - itemPosition.begin()->second.first);
    });
    scrollEffect->SetTrailingCallback([]() -> double { return 0.0; });
    scrollEffect->SetInitLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        auto itemPosition = list->GetItemPosition();
        return list->GetMainContentSize() -
               (itemPosition.rbegin()->second.second - list->currentDelta_ - itemPosition.begin()->second.first);
    });
    scrollEffect->SetInitTrailingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        return 0.0f;
    });
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
    if (event.code == KeyCode::KEY_DPAD_UP || event.code == KeyCode::KEY_DPAD_DOWN) {
        HandleDirectionKey(event.code);
        return true;
    }
    return false;
}

bool ListPattern::HandleDirectionKey(KeyCode code)
{
    if (code == KeyCode::KEY_DPAD_UP) {
        // Need to update: current selection
        return true;
    }
    if (code == KeyCode::KEY_DPAD_DOWN) {
        // Need to update: current selection
        return true;
    }
    return false;
}
} // namespace OHOS::Ace::NG
