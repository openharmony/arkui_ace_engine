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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_PATTERN_H

#include <memory>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/pattern/grid/grid_accessibility_property.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_paint_method.h"
#include "core/components_ng/pattern/grid/grid_position_controller.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT GridPattern : public ScrollablePattern {
    DECLARE_ACE_TYPE(GridPattern, ScrollablePattern);

public:
    GridPattern() = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<GridLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    RefPtr<PaintProperty> CreatePaintProperty() override;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<GridAccessibilityProperty>();
    }

    bool IsScrollable() const override
    {
        return isConfigScrollable_;
    }

    void SetMultiSelectable(bool multiSelectable)
    {
        multiSelectable_ = multiSelectable;
    }

    bool MultiSelectable() const
    {
        return multiSelectable_;
    }

    void SetSupportAnimation(bool supportAnimation)
    {
        supportAnimation_ = supportAnimation;
    }

    bool SupportAnimation() const
    {
        return supportAnimation_;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override
    {
        auto property = GetLayoutProperty<GridLayoutProperty>();
        if (!property) {
            return ScopeFocusAlgorithm();
        }
        return ScopeFocusAlgorithm(property->IsVertical(), true, ScopeType::OTHERS,
            [wp = WeakClaim(this)](
                FocusStep step, const WeakPtr<FocusHub>& currFocusNode, WeakPtr<FocusHub>& nextFocusNode) {
                auto grid = wp.Upgrade();
                if (grid) {
                    nextFocusNode = grid->GetNextFocusNode(step, currFocusNode);
                }
            });
    }

    int32_t GetFocusNodeIndex(const RefPtr<FocusHub>& focusNode) override;

    void ScrollToFocusNodeIndex(int32_t index) override;

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<GridEventHub>();
    }

    bool UsResRegion() override
    {
        return false;
    }

    GridLayoutInfo GetGridLayoutInfo() const
    {
        return gridLayoutInfo_;
    }

    void ResetGridLayoutInfo()
    {
        gridLayoutInfo_.lineHeightMap_.clear();
        gridLayoutInfo_.gridMatrix_.clear();
        gridLayoutInfo_.endIndex_ = gridLayoutInfo_.startIndex_ - 1;
        gridLayoutInfo_.endMainLineIndex_ = 0;
        gridLayoutInfo_.ResetPositionFlags();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

    bool UpdateCurrentOffset(float offset, int32_t source) override;

    bool IsAtTop() const override
    {
        return gridLayoutInfo_.reachStart_;
    }

    bool IsAtBottom() const override
    {
        return gridLayoutInfo_.offsetEnd_;
    }

    OverScrollOffset GetOverScrollOffset(double delta) const override;

    void SetScrollState(int32_t scrollState)
    {
        scrollState_ = scrollState;
    }

    bool OutBoundaryCallback() override;

    void SetPositionController(const RefPtr<ScrollableController>& controller);

    void ScrollPage(bool reverse);

    bool UpdateStartIndex(int32_t index);

    bool UpdateStartIndex(int32_t index, ScrollAlign align);

    float GetTotalOffset() const override
    {
        return EstimateHeight();
    }

    void OnAnimateStop() override;

    void AnimateTo(float position, float duration, const RefPtr<Curve>& curve, bool smooth) override;
    void ScrollTo(float position) override;

    void ScrollBy(float offset);

    bool OnScrollCallback(float offset, int32_t source) override;

    int32_t GetOriginalIndex() const;
    int32_t GetCrossCount() const;
    int32_t GetChildrenCount() const;
    void MoveItems(int32_t itemIndex, int32_t insertIndex);
    void ClearDragState();
    float EstimateHeight() const;

private:
    float GetMainGap();
    float GetAllDelta();
    void CheckRestartSpring();
    void CheckScrollable();
    bool IsOutOfBoundary();
    void SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect) override;
    SizeF GetContentSize() const;
    void OnAttachToFrameNode() override;
    void OnModifyDone() override;
    float GetMainContentSize() const;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    WeakPtr<FocusHub> GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode);
    std::pair<int32_t, int32_t> GetNextIndexByStep(
        int32_t curMainIndex, int32_t curCrossIndex, int32_t curMainSpan, int32_t curCrossSpan, FocusStep step);
    WeakPtr<FocusHub> SearchFocusableChildInCross(int32_t tarMainIndex, int32_t tarCrossIndex, int32_t maxCrossCount,
        int32_t curMainIndex = -1, int32_t curCrossIndex = -1);
    WeakPtr<FocusHub> GetChildFocusNodeByIndex(int32_t tarMainIndex, int32_t tarCrossIndex, int32_t tarIndex = -1);
    std::unordered_set<int32_t> GetFocusableChildCrossIndexesAt(int32_t tarMainIndex);
    void ScrollToFocusNode(const WeakPtr<FocusHub>& focusNode);
    void FlushCurrentFocus();
    void FlushFocusOnScroll(const GridLayoutInfo& gridLayoutInfo);
    std::pair<bool, bool> IsFirstOrLastFocusableChild(int32_t curMainIndex, int32_t curCrossIndex);
    std::pair<FocusStep, FocusStep> GetFocusSteps(int32_t curMainIndex, int32_t curCrossIndex, FocusStep step);
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    bool HandleDirectionKey(KeyCode code);

    void ClearMultiSelect() override;
    void MultiSelectWithoutKeyboard(const RectF& selectedZone) override;
    void UpdateScrollBarOffset() override;
    void UpdateRectOfDraggedInItem(int32_t insertIndex);
    void SetAccessibilityAction();

    GridLayoutInfo gridLayoutInfo_;
    void ProcessEvent(bool indexChanged, float finalOffset, bool offsetEnd);
    void MarkDirtyNodeSelf();
    void OnScrollEndCallback() override;
    void FireOnScrollStart();
    void InitScrollableEvent();

    RefPtr<GridPositionController> positionController_;
    float animatorOffset_ = 0.0f;
    bool scrollStop_ = false;

    bool supportAnimation_ = false;
    bool isConfigScrollable_ = false;

    bool scrollable_ = true;
    int32_t scrollState_ = SCROLL_FROM_NONE;

    bool firstShow_ = true;

    int32_t lastFocusItemMainIndex_ = 0;
    int32_t lastFocusItemCrossIndex_ = 0;

    std::pair<std::optional<float>, std::optional<float>> scrollbarInfo_;

    ACE_DISALLOW_COPY_AND_MOVE(GridPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_PATTERN_H
