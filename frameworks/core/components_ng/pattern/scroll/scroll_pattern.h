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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_PATTERN_H

#include "base/geometry/axis.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/scroll_accessibility_property.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/components_ng/pattern/scroll/scroll_layout_algorithm.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_paint_property.h"
#include "core/components_ng/pattern/scroll/scroll_paint_method.h"
#include "core/components_ng/pattern/scroll/scroll_position_controller.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace::NG {

class ScrollPattern : public ScrollablePattern {
    DECLARE_ACE_TYPE(ScrollPattern, ScrollablePattern);

public:
    ScrollPattern() = default;
    ~ScrollPattern() override
    {
        positionController_ = nullptr;
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
        return MakeRefPtr<ScrollLayoutProperty>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<ScrollPaintProperty>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<ScrollAccessibilityProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<ScrollLayoutAlgorithm>(currentOffset_);
        return layoutAlgorithm;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto paint = MakeRefPtr<ScrollPaintMethod>();
        auto scrollBarOverlayModifier = GetScrollBarOverlayModifier();
        if (!scrollBarOverlayModifier) {
            scrollBarOverlayModifier = AceType::MakeRefPtr<ScrollBarOverlayModifier>();
            SetScrollBarOverlayModifier(scrollBarOverlayModifier);
        }
        paint->SetScrollBarOverlayModifier(scrollBarOverlayModifier);
        auto scrollBar = GetScrollBar();
        if (scrollBar) {
            paint->SetScrollBar(scrollBar);
        }
        auto scrollEffect = GetScrollEdgeEffect();
        if (scrollEffect && scrollEffect->IsFadeEffect()) {
            paint->SetEdgeEffect(scrollEffect);
        }
        return paint;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<ScrollEventHub>();
    }

    virtual bool ReachMaxCount() const
    {
        return true;
    }

    bool IsScrollable() const override
    {
        return GetAxis() != Axis::NONE;
    }

    bool OnScrollCallback(float offset, int32_t source) override;
    void OnScrollEndCallback() override;

    double GetCurrentPosition() const
    {
        return currentOffset_;
    }

    float GetTotalOffset() const override
    {
        return -currentOffset_;
    }

    void ResetPosition();

    Offset GetCurrentOffset() const
    {
        if (GetAxis() == Axis::HORIZONTAL) {
            return Offset{currentOffset_, 0};
        }
        return Offset{0, currentOffset_};
    }

    float GetScrollableDistance() const
    {
        return scrollableDistance_;
    }

    bool IsRowReverse() const
    {
        // TODO: not consider rightToLeft
        return direction_ == FlexDirection::ROW_REVERSE;
    }

    bool IsColReverse() const
    {
        return  direction_ == FlexDirection::COLUMN_REVERSE;
    }

    RefPtr<ScrollPositionController> GetScrollPositionController() const
    {
        return positionController_;
    }

    void SetScrollPositionController(const RefPtr<ScrollPositionController>& positionController)
    {
        positionController_ = positionController;
    }

    void SetDirection(FlexDirection direction)
    {
        direction_ = direction;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    bool ScrollToNode(const RefPtr<FrameNode>& focusFrameNode) override;

    void SetScrollState(int32_t source)
    {
        source_ = source;
    }

    int32_t GetScrollState() const
    {
        return source_;
    }

    bool IsAtTop() const override;
    bool IsAtBottom() const override;
    bool IsOutOfBoundary() const;
    OverScrollOffset GetOverScrollOffset(double delta) const override;

    void OnAnimateStop() override;
    bool UpdateCurrentOffset(float offset, int32_t source) override;
    void AnimateTo(float position, float duration, const RefPtr<Curve>& curve, bool smooth) override;
    void ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth);
    void ScrollBy(float pixelX, float pixelY, bool smooth, const std::function<void()>& onFinish = nullptr);
    bool ScrollPage(bool reverse, bool smooth, const std::function<void()>& onFinish = nullptr);
    void ScrollTo(float position) override;
    void JumpToPosition(float position, int32_t source = SCROLL_FROM_JUMP);
    bool ScrollPageCheck(float delta, int32_t source);
    void AdjustOffset(float& delta, int32_t source);
    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

    // scrollSnap
    std::optional<float> CalePredictSnapOffset(float delta) override;
    bool NeedScrollSnapToSide(float delta) override;
    void CaleSnapOffsets();
    void CaleSnapOffsetsByInterval(ScrollSnapAlign scrollSnapAlign);
    void CaleSnapOffsetsByPaginations();

    bool IsSnapToInterval() const
    {
        return snapPaginations_.empty();
    }

    std::vector<float> GetSnapOffsets() const
    {
        return snapOffsets_;
    }

    void SetSnapOffsets(const std::vector<float>& snapOffset)
    {
        snapOffsets_ = snapOffset;
    }

    void SetIntervalSize(const Dimension& intervalSize)
    {
        if (intervalSize_ != intervalSize) {
            intervalSize_ = intervalSize;
            scrollSnapUpdate_ = true;
        }
    }

    Dimension GetIntervalSize() const
    {
        return intervalSize_;
    }

    void SetSnapPaginations(const std::vector<Dimension>& snapPaginations)
    {
        if (snapPaginations_ != snapPaginations) {
            snapPaginations_ = snapPaginations;
            scrollSnapUpdate_ = true;
        }
    }

    std::vector<Dimension> GetSnapPaginations() const
    {
        return snapPaginations_;
    }

    void SetEnableSnapToSide(const std::pair<bool, bool>& enableSnapToSide)
    {
        enableSnapToSide_ = enableSnapToSide;
    }

    std::pair<bool, bool> GetEnableSnapToSide() const
    {
        return enableSnapToSide_;
    }

    void SetScrollSnapUpdate(bool scrollSnapUpdate)
    {
        scrollSnapUpdate_ = scrollSnapUpdate;
    }

    bool GetScrollSnapUpdate() const
    {
        return scrollSnapUpdate_;
    }

    ScrollSnapAlign GetScrollSnapAlign() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN_NOLOG(host, ScrollSnapAlign::NONE);
        auto scrollLayoutProperty = host->GetLayoutProperty<ScrollLayoutProperty>();
        CHECK_NULL_RETURN_NOLOG(scrollLayoutProperty, ScrollSnapAlign::NONE);
        return scrollLayoutProperty->GetScrollSnapAlign().value_or(ScrollSnapAlign::NONE);
    }

protected:
    void DoJump(float position, int32_t source = SCROLL_FROM_JUMP);

private:
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    bool IsCrashTop() const;
    bool IsCrashBottom() const;
    bool IsScrollOutOnEdge(float delta) const;
    void HandleCrashTop() const;
    void HandleCrashBottom() const;

    void RegisterScrollEventTask();
    void RegisterScrollBarEventTask();
    void HandleScrollEffect();
    void HandleScrollBarOutBoundary();
    void ValidateOffset(int32_t source);
    void HandleScrollPosition(float scroll, int32_t scrollState);
    void SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect) override;
    void AddScrollEdgeEffect(RefPtr<ScrollEdgeEffect> scrollEffect);
    void UpdateScrollBarOffset() override;
    void FireOnScrollStart();
    void FireOnScrollStop();
    void SetAccessibilityAction();
    void CheckScrollable();
    OffsetF GetOffsetToScroll(const RefPtr<FrameNode>& childFrame) const;

    RefPtr<ScrollPositionController> positionController_;
    float currentOffset_ = 0.0f;
    float lastOffset_ = 0.0f;
    float scrollableDistance_ = 0.0f;
    float viewPortLength_ = 0.0f;
    SizeF viewPort_;
    SizeF viewSize_;
    SizeF viewPortExtent_;
    FlexDirection direction_ { FlexDirection::COLUMN };
    bool scrollStop_ = false;
    int32_t source_ = SCROLL_FROM_NONE;

    // scrollSnap
    std::vector<float> snapOffsets_;
    std::vector<Dimension> snapPaginations_;
    std::pair<bool, bool> enableSnapToSide_ = { true, true };
    Dimension intervalSize_;
    bool scrollSnapUpdate_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_PATTERN_H
