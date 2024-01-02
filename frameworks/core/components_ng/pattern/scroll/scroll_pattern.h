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
#include "core/components_ng/pattern/scroll/scroll_accessibility_property.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/components_ng/pattern/scroll/scroll_layout_algorithm.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_paint_method.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/web/scroll_update_listener.h"

namespace OHOS::Ace::NG {

class ScrollPattern : public ScrollablePattern {
    DECLARE_ACE_TYPE(ScrollPattern, ScrollablePattern);

public:
    ScrollPattern() : ScrollablePattern(EdgeEffect::NONE, true) {}

    ~ScrollPattern() override = default;

    bool UsResRegion() override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ScrollLayoutProperty>();
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
        paint->SetScrollBar(GetScrollBar());
        CreateScrollBarOverlayModifier();
        paint->SetScrollBarOverlayModifier(GetScrollBarOverlayModifier());
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

    RefPtr<ScrollableController> GetScrollPositionController() const
    {
        return positionController_;
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

    bool IsAtTop() const override;
    bool IsAtBottom() const override;
    bool IsOutOfBoundary(bool useCurrentDelta = true) override;
    OverScrollOffset GetOverScrollOffset(double delta) const override;

    void OnAnimateStop() override;
    bool UpdateCurrentOffset(float offset, int32_t source) override;
    void ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth) override;
    void ScrollBy(float pixelX, float pixelY, bool smooth, const std::function<void()>& onFinish = nullptr);
    bool ScrollPage(bool reverse, bool smooth, const std::function<void()>& onFinish = nullptr);
    void ScrollTo(float position) override;
    void JumpToPosition(float position, int32_t source = SCROLL_FROM_JUMP);
    float GetMainContentSize() const override
    {
        return viewPortLength_;
    }
    bool SupportScrollToIndex() const override
    {
        return false;
    }
    bool ScrollPageCheck(float delta, int32_t source);
    void AdjustOffset(float& delta, int32_t source);
    Rect GetItemRect(int32_t index) const override;

    // scrollSnap
    std::optional<float> CalePredictSnapOffset(float delta, float dragDistance = 0.f, float velocity = 0.f) override;
    bool NeedScrollSnapToSide(float delta) override;
    void CaleSnapOffsets();
    void CaleSnapOffsetsByInterval(ScrollSnapAlign scrollSnapAlign);
    void CaleSnapOffsetsByPaginations();

    float GetSelectScrollWidth();

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
        CHECK_NULL_RETURN(host, ScrollSnapAlign::NONE);
        auto scrollLayoutProperty = host->GetLayoutProperty<ScrollLayoutProperty>();
        CHECK_NULL_RETURN(scrollLayoutProperty, ScrollSnapAlign::NONE);
        return scrollLayoutProperty->GetScrollSnapAlign().value_or(ScrollSnapAlign::NONE);
    }

    void registerScrollUpdateListener(const std::shared_ptr<IScrollUpdateCallback>& listener);

    std::string ProvideRestoreInfo() override;
    void OnRestoreInfo(const std::string& restoreInfo) override;
	
    void SetIsWidthModifiedBySelect(bool isModified)
    {
        isWidthModifiedBySelect_ = isModified;
    }
    
    bool IsWidthModifiedBySelect() const
    {
        return isWidthModifiedBySelect_;
    }
    
    void SetIsSelectScroll(bool isSelect)
    {
        isSelectScroll_ = isSelect;
    }
    
    bool IsSelectScroll() const
    {
        return isSelectScroll_;
    }

    void SetEnablePaging(ScrollPagingStatus status)
    {
        CHECK_NULL_VOID(enablePagingStatus_ != ScrollPagingStatus::INVALID);
        enablePagingStatus_ =  status;
    }

    ScrollPagingStatus GetEnablePaging()
    {
        return enablePagingStatus_;
    }

    bool IsScrollSnap() override
    {
        return !snapOffsets_.empty() && GetScrollSnapAlign() != ScrollSnapAlign::NONE;
    }

protected:
    void DoJump(float position, int32_t source = SCROLL_FROM_JUMP);

private:
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    bool IsCrashTop() const;
    bool IsCrashBottom() const;
    bool ReachStart() const;
    bool ReachEnd() const;
    bool IsScrollOutOnEdge(float delta) const;
    void HandleCrashTop() const;
    void HandleCrashBottom() const;

    void RegisterScrollEventTask();
    void RegisterScrollBarEventTask();
    void HandleScrollEffect();
    void ValidateOffset(int32_t source);
    void HandleScrollPosition(float scroll, int32_t scrollState);
    void SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect) override;
    void UpdateScrollBarOffset() override;
    void SetAccessibilityAction();
    bool SetScrollProperties(const RefPtr<LayoutWrapper>& dirty);
    void ScrollSnapTrigger();
    void CheckScrollable();
    OffsetF GetOffsetToScroll(const RefPtr<FrameNode>& childFrame) const;
    float GetPagingOffset(float delta, float dragDistance, float velocity)  const;
    float GetPagingDelta(float dragDistance, float velocity) const;

    float currentOffset_ = 0.0f;
    float lastOffset_ = 0.0f;
    // keep lastOffset_ for compatibility, use prevOffset_ for onReachStart/onReachEnd
    float prevOffset_ = 0.0f;
    float scrollableDistance_ = 0.0f;
    float viewPortLength_ = 0.0f;
    SizeF viewPort_;
    SizeF viewSize_;
    SizeF viewPortExtent_;
    FlexDirection direction_ { FlexDirection::COLUMN };
    std::vector<std::shared_ptr<IScrollUpdateCallback>> listenerVector_;

    // scrollSnap
    std::vector<float> snapOffsets_;
    std::vector<Dimension> snapPaginations_;
    std::pair<bool, bool> enableSnapToSide_ = { true, true };
    Dimension intervalSize_;
    bool scrollSnapUpdate_ = false;
    
    bool isWidthModifiedBySelect_ = false;
    bool isSelectScroll_ = false;
    ScrollPagingStatus enablePagingStatus_ = ScrollPagingStatus::NONE;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_PATTERN_H
