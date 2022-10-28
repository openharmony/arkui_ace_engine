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

#include <optional>

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_paint_method.h"
#include "core/components_ng/pattern/list/list_position_controller.h"
#include "core/components_ng/pattern/pattern.h"
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
        auto lanes = listLayoutProperty->GetLanes().value_or(1);
        auto drawVertical = (axis == Axis::HORIZONTAL);
        return MakeRefPtr<ListPaintMethod>(divider, drawVertical, lanes, spaceWidth_, itemPosition_);
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ListLayoutProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<ListEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    void UpdateCurrentOffset(float offset);

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

    void SetIsScroll(bool isScroll)
    {
        isScroll_ = isScroll;
    }

    bool GetIsScroll() const
    {
        return isScroll_;
    }

    void SetScrollStop(bool scrollStop)
    {
        scrollStop_ = scrollStop;
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

    void AnimateTo(float position, float duration, const RefPtr<Curve>& curve, bool limitDuration = true);
    void ScrollTo(float position);
    void ScrollToIndex(int32_t index, ScrollIndexAlignment align = ScrollIndexAlignment::ALIGN_TOP);
    void ScrollToEdge(ScrollEdgeType scrollEdgeType);
    bool ScrollPage(bool reverse);
    Offset GetCurrentOffset() const;

private:
    void ProcessScrollEnd();

    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    bool HandleDirectionKey(KeyCode code);

    float GetMainContentSize() const;
    void ProcessEvent(bool indexChanged, float finalOffset);
    void CheckScrollable();
    bool IsOutOfBoundary(bool useCurrentDelta = true);
    void SetScrollEdgeEffect(const RefPtr<ScrollEdgeEffect>& scrollEffect);
    void SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect);

    RefPtr<Animator> animator_;
    RefPtr<ScrollableEvent> scrollableEvent_;
    RefPtr<ScrollEdgeEffect> scrollEffect_;
    RefPtr<Animator> springController_;
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

    ListLayoutAlgorithm::PositionMap itemPosition_;
    bool isScroll_ = false;
    bool scrollStop_ = false;
    int32_t scrollState_ = SCROLL_FROM_NONE;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_PATTERN_H
