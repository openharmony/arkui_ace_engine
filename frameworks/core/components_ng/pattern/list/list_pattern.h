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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_PATTERN_H

#include "core/animation/chain_animation.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/list/list_accessibility_property.h"
#include "core/components_ng/pattern/list/list_content_modifier.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_paint_method.h"
#include "core/components_ng/pattern/list/list_paint_property.h"
#include "core/components_ng/pattern/list/list_position_controller.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/render/render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class ListPattern : public ScrollablePattern {
    DECLARE_ACE_TYPE(ListPattern, ScrollablePattern);

public:
    ListPattern() = default;
    ~ListPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    bool IsAtomicNode() const override
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

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<ListAccessibilityProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

    void FromJson(const std::unique_ptr<JsonValue>& json) override;

    bool UpdateCurrentOffset(float offset, int32_t source) override;

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

    bool IsScrollable() const override
    {
        return scrollable_;
    }

    bool IsAtTop() const override;
    bool IsAtBottom() const override;
    bool OutBoundaryCallback() override;
    OverScrollOffset GetOverScrollOffset(double delta) const override;

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
        return ScopeFocusAlgorithm(property->GetListDirection().value_or(Axis::VERTICAL) == Axis::VERTICAL, true,
            ScopeType::OTHERS,
            [wp = WeakClaim(this)](
                FocusStep step, const WeakPtr<FocusHub>& currFocusNode, WeakPtr<FocusHub>& nextFocusNode) {
                auto list = wp.Upgrade();
                if (list) {
                    nextFocusNode = list->GetNextFocusNode(step, currFocusNode);
                }
            });
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
        return currentOffset_;
    }

    // scroller
    void AnimateTo(float position, float duration, const RefPtr<Curve>& curve);
    void StartSpringMotion(float start, float end, float velocity);
    void ScrollTo(float position, bool smooth);
    void ScrollToIndex(int32_t index, bool smooth = false, ScrollAlign align = ScrollAlign::START);
    void ScrollToIndex(int32_t index, int32_t indexInGroup, ScrollAlign align);
    void ScrollToEdge(ScrollEdgeType scrollEdgeType);
    bool ScrollPage(bool reverse);
    void ScrollBy(float offset);
    Offset GetCurrentOffset() const;

    void UpdateScrollBarOffset() override;
    // chain animation
    void SetChainAnimation();
    void SetChainAnimationOptions(const ChainAnimationOptions& options);
    float FlushChainAnimation(float dragOffset);
    void ProcessDragStart(float startPosition);
    void ProcessDragUpdate(float dragOffset, int32_t source);
    float GetChainDelta(int32_t index) const;

    // multiSelectable
    void SetMultiSelectable(bool multiSelectable)
    {
        multiSelectable_ = multiSelectable;
    }

    void SetSwiperItem(WeakPtr<ListItemPattern> swiperItem);

    void SetPredictSnapOffset(float predictSnapOffset)
    {
        predictSnapOffset_ = predictSnapOffset;
    }
    bool OnScrollSnapCallback(double targetOffset, double velocity) override;

    int32_t GetItemIndexByPosition(float xOffset, float yOffset);

private:
    void OnScrollEndCallback() override;

    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    float CalculateTargetPos(float startPos, float endPos, ScrollAutoType scrollAutoType);

    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    bool HandleDirectionKey(const KeyEvent& event);
    WeakPtr<FocusHub> GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode);
    WeakPtr<FocusHub> GetChildFocusNodeByIndex(int32_t tarMainIndex, int32_t tarGroupIndex);

    void MarkDirtyNodeSelf();
    SizeF GetContentSize() const;
    void ProcessEvent(bool indexChanged, float finalOffset, bool isJump, float prevStartOffset, float prevEndOffset);
    void CheckScrollable();
    bool IsOutOfBoundary(bool useCurrentDelta = true);
    bool OnScrollCallback(float offset, int32_t source) override;
    void InitScrollableEvent();
    void SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect) override;
    void HandleScrollEffect(float offset);
    void FireOnScrollStart();
    void CheckRestartSpring();
    void StopAnimate();
    void StartDefaultOrCustomSpringMotion(float start, float end, const RefPtr<InterpolatingSpring>& curve);
    void UpdateScrollSnap();
    bool IsScrollSnapAlignCenter() const;
    void SetChainAnimationLayoutAlgorithm(
        RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm, RefPtr<ListLayoutProperty> listLayoutProperty);
    bool NeedScrollSnapAlignEffect() const;
    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;
    void RegistOritationListener();

    // multiSelectable
    void UninitMouseEvent();
    void InitMouseEvent();
    void HandleMouseEventWithoutKeyboard(const MouseInfo& info);
    void ClearMultiSelect();
    void ClearSelectedZone();
    RectF ComputeSelectedZone(const OffsetF& startOffset, const OffsetF& endOffset);
    void MultiSelectWithoutKeyboard(const RectF& selectedZone);
    void HandleCardModeSelectedEvent(
        const RectF& selectedZone, const RefPtr<FrameNode>& itemGroupNode, float itemGroupTop);

    void DrivenRender(const RefPtr<LayoutWrapper>& layoutWrapper);
    void SetAccessibilityAction();

    bool CheckWhetherCurvesRelyOnDuration(const RefPtr<Curve>& curve);
    void PlayCustomSpringCurverDoNotRelyOnDuration(float position, const RefPtr<Curve>& curve);

    RefPtr<ListContentModifier> listContentModifier_;

    RefPtr<Animator> animator_;
    RefPtr<ListPositionController> positionController_;
    int32_t maxListItemIndex_ = 0;
    int32_t startIndex_ = -1;
    int32_t endIndex_ = -1;
    float startMainPos_;
    float endMainPos_;
    bool isInitialized_ = false;
    float currentOffset_ = 0.0f;
    float spaceWidth_ = 0.0f;
    float contentMainSize_ = 0.0f;

    float currentDelta_ = 0.0f;
    bool crossMatchChild_ = false;
    bool smooth_ = false;
    float scrollSnapVelocity_ = 0.0f;

    std::optional<int32_t> jumpIndex_;
    std::optional<int32_t> jumpIndexInGroup_;
    std::optional<int32_t> targetIndex_;
    std::optional<float> predictSnapOffset_;
    ScrollAlign scrollAlign_ = ScrollAlign::START;
    bool scrollable_ = true;
    bool paintStateFlag_ = false;
    bool isFramePaintStateValid_ = false;

    ListLayoutAlgorithm::PositionMap itemPosition_;
    bool scrollStop_ = false;
    bool scrollAbort_ = false;
    int32_t scrollState_ = SCROLL_FROM_NONE;

    std::list<WeakPtr<FrameNode>> itemGroupList_;
    std::map<int32_t, int32_t> lanesItemRange_;
    int32_t lanes_ = 1;

    // chain animation
    RefPtr<ChainAnimation> chainAnimation_;
    bool dragFromSpring_ = false;
    RefPtr<SpringProperty> springProperty_;
    std::optional<ChainAnimationOptions> chainAnimationOptions_;

    // multiSelectable
    bool multiSelectable_ = false;
    bool isMouseEventInit_ = false;
    bool mousePressed_ = false;

    bool isOritationListenerRegisted_ = false;
    OffsetF mouseStartOffset_;
    OffsetF mouseEndOffset_;
    OffsetF mousePressOffset_;

    // ListItem swiperAction
    WeakPtr<ListItemPattern> swiperItem_;
    RefPtr<SpringMotion> scrollToIndexMotion_;
    RefPtr<SpringMotion> scrollSnapMotion_;
    RefPtr<Scrollable> scrollableTouchEvent_;

    bool isScrollEnd_ = false;

    RefPtr<SpringMotion> springMotion_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_PATTERN_H
