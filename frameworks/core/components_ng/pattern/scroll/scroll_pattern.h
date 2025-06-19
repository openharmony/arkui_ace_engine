/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/pattern/scroll/scroll_accessibility_property.h"
#include "core/components_ng/pattern/scroll/scroll_content_modifier.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/components_ng/pattern/scroll/scroll_layout_algorithm.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_paint_method.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

#ifdef SUPPORT_DIGITAL_CROWN
#include "core/common/vibrator/vibrator_utils.h"
#endif

namespace OHOS::Ace::NG {
class InspectorFilter;

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
        return MakeRefPtr<ScrollLayoutAlgorithm>(currentOffset_, crossOffset_);
    }

    RefPtr<PaintProperty> CreatePaintProperty() override;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    OPINC_TYPE_E OpIncType() override
    {
        return OPINC_PARENT_POSSIBLE;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<ScrollEventHub>();
    }

    bool IsScrollable() const override
    {
        return GetAxis() != Axis::NONE;
    }

    bool IsPositiveScrollableDistance()
    {
        return Positive(scrollableDistance_);
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
    ScrollOffsetAbility GetScrollOffsetAbility() override;

    bool IsAtTop() const override;
    bool IsAtBottom(bool considerRepeat = false) const override;
    bool IsOutOfBoundary(bool useCurrentDelta = true) override;
    OverScrollOffset GetOverScrollOffset(double delta) const override;

    void OnAnimateStop() override;
    bool UpdateCurrentOffset(float offset, int32_t source) override;
    void ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth) override;

    void CheckScrollToEdge();

    ScrollEdgeType GetScrollEdgeType() const override
    {
        return scrollEdgeType_;
    }

    void SetScrollEdgeType(ScrollEdgeType scrollEdgeType) override
    {
        scrollEdgeType_ = scrollEdgeType;
    }

    void ScrollBy(float pixelX, float pixelY, bool smooth, const std::function<void()>& onFinish = nullptr);
    void ScrollPage(bool reverse, bool smooth = false,
        AccessibilityScrollType scrollType = AccessibilityScrollType::SCROLL_FULL) override;
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
    std::optional<float> CalcPredictSnapOffset(float delta, float dragDistance = 0.f, float velocity = 0.f,
        SnapDirection snapDirection = SnapDirection::NONE) override;
    std::optional<float> CalcPredictNextSnapOffset(float delta, SnapDirection snapDirection);
    bool NeedScrollSnapToSide(float delta) override;
    void CaleSnapOffsets();
    void CaleSnapOffsetsByInterval(ScrollSnapAlign scrollSnapAlign);
    void CaleSnapOffsetsByPaginations(ScrollSnapAlign scrollSnapAlign);

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
            TAG_LOGI(AceLogTag::ACE_SCROLL, "scroll setIntervalSize:%{public}f", intervalSize.Value());
            scrollSnapUpdate_ = true;
        }
    }

#ifdef SUPPORT_DIGITAL_CROWN
    void StartVibrateFeedback();

    void SetReachBoundary(bool flag)
    {
        reachBoundary_ = flag;
    }
#endif

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
    void SetKeepSnapPaginations(const std::vector<Dimension>& snapPaginations)
    {
        keepSnapPaginations_ = snapPaginations;
    }

    std::vector<Dimension> GetKeepSnapPaginations()
    {
        return keepSnapPaginations_;
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

    void SetHasOptionWidth(bool hasOptionWidth)
    {
        hasOptionWidth_ = hasOptionWidth;
    }

    bool GetHasOptionWidth()
    {
        return hasOptionWidth_;
    }

    void SetEnablePaging(ScrollPagingStatus status)
    {
        enablePagingStatus_ =  status;
    }

    ScrollPagingStatus GetEnablePaging()
    {
        return enablePagingStatus_;
    }

    bool IsScrollSnap() override
    {
        return !snapOffsets_.empty() &&
               (GetScrollSnapAlign() != ScrollSnapAlign::NONE || enablePagingStatus_ == ScrollPagingStatus::VALID);
    }

    SnapType GetSnapType() override
    {
        return (!snapOffsets_.empty() &&
                   (GetScrollSnapAlign() != ScrollSnapAlign::NONE || enablePagingStatus_ == ScrollPagingStatus::VALID))
                   ? SnapType::SCROLL_SNAP
                   : SnapType::NONE_SNAP;
    }

    void TriggerModifyDone();

    void SetInitialOffset(const OffsetT<CalcDimension>& offset)
    {
        initialOffset_ = offset;
    }

    OffsetT<CalcDimension> GetInitialOffset() const
    {
        return initialOffset_.has_value() ? initialOffset_.value() : OffsetT(CalcDimension(), CalcDimension());
    }

    bool NeedSetInitialOffset()
    {
        return !isInitialized_ && initialOffset_.has_value();
    }

    void AddScrollMeasureInfo(const std::optional<LayoutConstraintF>& parentConstraint,
        const std::optional<LayoutConstraintF>& childConstraint, const SizeF& selfSize, const SizeF& childSize);

    void AddScrollLayoutInfo();

    void GetScrollSnapAlignDumpInfo();
    void GetScrollSnapAlignDumpInfo(std::unique_ptr<JsonValue>& json);

    void GetScrollPagingStatusDumpInfo();
    void GetScrollPagingStatusDumpInfo(std::unique_ptr<JsonValue>& json);
    void DumpAdvanceInfo() override;
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override;

    SizeF GetViewSize() const
    {
        return viewSize_;
    }

    SizeF GetViewPortExtent() const
    {
        return viewPortExtent_;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    bool StartSnapAnimation(SnapAnimationOptions snapAnimationOptions) override;

    void StartScrollSnapAnimation(float scrollSnapDelta, float scrollSnapVelocity, bool fromScrollBar);

    SizeF GetChildrenExpandedSize() override;

    void TriggerScrollBarDisplay();

    bool IsEnablePagingValid() override
    {
        return enablePagingStatus_ == ScrollPagingStatus::VALID && GetScrollSnapAlign() == ScrollSnapAlign::NONE;
    }

protected:
    void DoJump(float position, int32_t source = SCROLL_FROM_JUMP);

private:
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    bool IsCrashTop() const;
    bool IsCrashBottom() const;
    bool ReachStart(bool firstLayout) const;
    bool ReachEnd(bool firstLayout) const;
    bool IsScrollOutOnEdge(float delta) const;
    void HandleCrashTop();
    void HandleCrashBottom();

    void RegisterScrollBarEventTask();
    void HandleScrollEffect();
    void ValidateOffset(int32_t source);
    float ValidateOffset(int32_t source, float willScrollOffset);
    void HandleScrollPosition(float scroll);
    float FireTwoDimensionOnWillScroll(float scroll);
    void FireOnDidScroll(float scroll);
    void FireOnReachStart(const OnReachEvent& onReachStart, const OnReachEvent& onJSFrameNodeReachStart) override;
    void FireOnReachEnd(const OnReachEvent& onReachEnd, const OnReachEvent& onJSFrameNodeReachEnd) override;
    void SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect) override;
    void UpdateScrollBarOffset() override;
    void SetAccessibilityAction() override;
    bool ScrollSnapTrigger();
    void CheckScrollable();
    OffsetF GetOffsetToScroll(const RefPtr<FrameNode>& childFrame) const;
    bool SetScrollProperties(const RefPtr<LayoutWrapper>& dirty);
    std::string GetScrollSnapPagination() const;

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

    /* ============================= Free Scroll Enhancements ============================= */
public:
    /**
     * @return Pan gesture recognizer configured for Axis::FREE mode
     */
    RefPtr<NGGestureRecognizer> GetOverrideRecognizer() const
    {
        return freePanGesture_;
    }

private:
    void InitFreeScroll();

    RefPtr<PanRecognizer> freePanGesture_; // all-direction pan recognizer for free scroll mode
    float crossOffset_ = 0.0f; // offset on the vertical axis (currentOffset_ represents horizontal axis in Free Scroll mode)
    /* ============================================================================== */

    // scrollSnap
    std::vector<float> snapOffsets_;
    std::vector<Dimension> snapPaginations_;
    std::vector<Dimension> keepSnapPaginations_;
    std::pair<bool, bool> enableSnapToSide_ = { true, true };
    Dimension intervalSize_;
    bool scrollSnapUpdate_ = false;

    bool isWidthModifiedBySelect_ = false;
    bool isSelectScroll_ = false;
    bool hasOptionWidth_ = false;

    // enablePaging
    ScrollPagingStatus enablePagingStatus_ = ScrollPagingStatus::NONE;
    float lastPageLength_ = 0.0f;
    float GetPagingOffset(float delta, float dragDistance, float velocity)  const;
    float GetPagingDelta(float dragDistance, float velocity, float pageLength) const;

    RefPtr<ScrollContentModifier> scrollContentModifier_;

    //initialOffset
    std::optional<OffsetT<CalcDimension>> initialOffset_;

    //scrollToEdge
    ScrollEdgeType scrollEdgeType_ = ScrollEdgeType::SCROLL_NONE;

    // dump info
    std::list<ScrollLayoutInfo> scrollLayoutInfos_;
    std::list<ScrollMeasureInfo> scrollMeasureInfos_;

#ifdef SUPPORT_DIGITAL_CROWN
    int32_t crownEventNum_ = 0;
    bool reachBoundary_ = false;
    int64_t lastTime_ = 0;
#endif
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_PATTERN_H
