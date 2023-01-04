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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_PATTERN_H

#include "core/animation/bilateral_spring_adapter.h"
#include "core/animation/simple_spring_chain.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_paint_method.h"
#include "core/components_ng/pattern/list/list_paint_property.h"
#include "core/components_ng/pattern/list/list_position_controller.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/render/render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

class ListPattern : public Pattern {
    DECLARE_ACE_TYPE(ListPattern, Pattern);

public:
    ListPattern() = default;
    ~ListPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto listLayoutProperty = GetHost()->GetLayoutProperty<ListLayoutProperty>();
        V2::ItemDivider itemDivider;
        auto divider = listLayoutProperty->GetDivider().value_or(itemDivider);
        auto axis = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
        auto drawVertical = (axis == Axis::HORIZONTAL);
        auto paint =  MakeRefPtr<ListPaintMethod>(divider, drawVertical, lanes_, spaceWidth_, itemPosition_);
        paint->SetScrollBar(AceType::WeakClaim(AceType::RawPtr(scrollBar_)));
        paint->SetTotalItemCount(maxListItemIndex_ + 1);
        if (scrollEffect_ && scrollEffect_->IsFadeEffect()) {
            paint->SetEdgeEffect(scrollEffect_);
        }
        return paint;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }
    
    bool UsResRegion() override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ListLayoutProperty>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<ListPaintProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<ListEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    bool UpdateCurrentOffset(float offset);

    int32_t GetStartIndex() const
    {
        return startIndex_;
    }

    int32_t GetEndIndex() const
    {
        return endIndex_;
    }

    int32_t GetMaxListItemIndex() const
    {
        return maxListItemIndex_;
    }

    void SetScrollState(int32_t scrollState)
    {
        scrollState_ = scrollState;
    }

    int32_t GetScrollState() const
    {
        return scrollState_;
    }

    Axis GetDirection() const;

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override
    {
        auto property = GetLayoutProperty<ListLayoutProperty>();
        if (!property) {
            return {};
        }
        auto isVertical = property->GetListDirection().value_or(Axis::VERTICAL) == Axis::VERTICAL;
        return { isVertical, true, ScopeType::OTHERS };
    }

    const ListLayoutAlgorithm::PositionMap& GetItemPosition() const
    {
        return itemPosition_;
    }

    void SetPositionController(RefPtr<ListPositionController> control)
    {
        positionController_ = control;
        if (control) {
            control->SetScrollPattern(AceType::WeakClaim<ListPattern>(this));
        }
    }

    float GetTotalOffset() const
    {
        return estimateOffset_ - currentOffset_;
    }

    // scroller
    void AnimateTo(float position, float duration, const RefPtr<Curve>& curve);
    void ScrollTo(float position);
    void ScrollToIndex(int32_t index, ScrollIndexAlignment align = ScrollIndexAlignment::ALIGN_TOP);
    void ScrollToEdge(ScrollEdgeType scrollEdgeType);
    bool ScrollPage(bool reverse);
    Offset GetCurrentOffset() const;

    // scrollBar
    void SetScrollBar();
    void UpdateScrollBarOffset();
    void RegisterScrollBarEventTask();
    void SetScrollBarProxy(const RefPtr<ScrollBarProxy>& scrollBarProxy);
    float GetScrollableDistance() const
    {
        return scrollableDistance_;
    }
    float GetCurrentPosition() const
    {
        return currentPosition_;
    }

    // chain animation
    void SetChainAnimation(bool enable);
    void InitChainAnimation(int32_t nodeCount);
    float FlushChainAnimation(float dragOffset);
    void ProcessDragStart(float startPosition);
    void ProcessDragUpdate(float dragOffset);
    float GetChainDelta(int32_t index) const;

    // multiSelectable
    void SetMultiSelectable(bool multiSelectable)
    {
        multiSelectable_ = multiSelectable;
    }

private:
    void ProcessScrollEnd();

    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    bool HandleDirectionKey(KeyCode code);

    void MarkDirtyNodeSelf();
    SizeF GetContentSize() const;
    float GetMainContentSize() const;
    void ProcessEvent(bool indexChanged, float finalOffset, bool isJump);
    void CheckScrollable();
    bool IsOutOfBoundary(bool useCurrentDelta = true);
    bool ScrollPositionCallback(float offset, int32_t source);
    void InitScrollableEvent();
    void SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect);
    void SetEdgeEffect(const RefPtr<GestureEventHub>& gestureHub, EdgeEffect edgeEffect);
    void HandleScrollEffect(float offset);

    // multiSelectable
    void InitMouseEvent();
    void HandleMouseEventWithoutKeyboard(const MouseInfo& info);
    void ClearSelectedZone();
    RectF ComputeSelectedZone(const OffsetF& startOffset, const OffsetF& endOffset);
    void MultiSelectWithoutKeyboard(const RectF& selectedZone);

    RefPtr<Animator> animator_;
    RefPtr<ScrollableEvent> scrollableEvent_;
    RefPtr<ScrollEdgeEffect> scrollEffect_;
    RefPtr<ListPositionController> positionController_;
    int32_t maxListItemIndex_ = 0;
    int32_t startIndex_ = -1;
    int32_t endIndex_ = -1;
    float startMainPos_;
    float endMainPos_;
    bool isInitialized_ = false;
    float estimateOffset_ = 0.0f;
    float currentOffset_ = 0.0f;
    float lastOffset_ = 0.0f;
    float spaceWidth_ = 0.0f;

    float currentDelta_ = 0.0f;

    std::optional<int32_t> jumpIndex_;
    ScrollIndexAlignment scrollIndexAlignment_ = ScrollIndexAlignment::ALIGN_TOP;
    int32_t scrollIndex_ = 0;
    bool scrollable_ = true;

    RefPtr<ScrollBar> scrollBar_;
    RefPtr<TouchEventImpl> touchEvent_;
    bool isScrollContent_ = true;
    RefPtr<ScrollBarProxy> scrollBarProxy_;
    float scrollableDistance_ = 0.0f;
    float currentPosition_ = 0.0f;

    ListLayoutAlgorithm::PositionMap itemPosition_;
    bool scrollStop_ = false;
    int32_t scrollState_ = SCROLL_FROM_NONE;

    std::list<WeakPtr<FrameNode>> itemGroupList_;
    std::map<int32_t, int32_t> lanesItemRange_;
    int32_t lanes_ = 1;

    // chain animation
    SpringChainProperty chainProperty_;
    RefPtr<SpringProperty> overSpringProperty_;
    RefPtr<BilateralSpringAdapter> chainAdapter_;
    RefPtr<SimpleSpringChain> chain_;
    bool chainOverScroll_ = false;
    int32_t dragStartIndexPending_ = 0;
    int32_t dragStartIndex_ = 0;

    // multiSelectable
    bool multiSelectable_ = false;
    bool isMouseEventInit_ = false;
    OffsetF mouseStartOffset_;
    OffsetF mouseEndOffset_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_PATTERN_H
