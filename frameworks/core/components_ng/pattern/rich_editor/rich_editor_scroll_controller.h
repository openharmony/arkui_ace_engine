/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_SCROLL_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_SCROLL_MANAGER_H

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/text/text_free_scroll_controller.h"
#include "core/components_ng/pattern/text/text_scroll_bar_2d.h"

namespace OHOS::Ace {
class TaskExecutor;
}

namespace OHOS::Ace::NG {

// Dual-axis scrollbar manager with custom appearance and hit-testing for RichEditor.
class RichEditorScrollBar2D : public TextScrollBar2D {
    DECLARE_ACE_TYPE(RichEditorScrollBar2D, TextScrollBar2D);
public:
    explicit RichEditorScrollBar2D(const WeakPtr<ScrollablePattern>& pattern);

    void SetMinHeight(const Dimension& height);
    void SetColor(const Color& foregroundColor, const Color& backgroundColor);
    void SetHostBorderRadius(const BorderRadiusProperty& radius);

    // Mouse hit region extends each bar's narrow strip to the full frame extent.
    bool IsPointInScrollBar(const Point& point, const SizeF& frameSize) const;
    bool IsPressedOrHovered() const;
    void UpdateBars(const Color& barColor);
    void DisableVerticalBar();
    void AttachPropertiesToModifier(const RefPtr<OverlayModifier>& modifier);

private:
    template <typename BarOperation>
    void ApplyToBars(BarOperation&& operation) const
    {
        auto verticalBar = GetVerticalBar();
        if (verticalBar) {
            operation(verticalBar);
        }
        auto horizontalBar = GetHorizontalBar();
        if (horizontalBar) {
            operation(horizontalBar);
        }
    }
    bool IsPointInScrollBar(const Point& point, const SizeF& frameSize, bool isVertical) const;
    void UpdateBarAxis(bool isVertical, const Color& barColor);
};

// Pure geometry helper for scroll boundary checks and offset clamping.
class ScrollGeometryEvaluator {
    ACE_DISALLOW_COPY_AND_MOVE(ScrollGeometryEvaluator);
public:
    ScrollGeometryEvaluator(RectF& contentRect, RectF& textRect, RectF& frameRect, bool& isSingleLine)
        : contentRect_(contentRect), textRect_(textRect), frameRect_(frameRect), isSingleLine_(isSingleLine) {}

    bool IsReachTop() const;
    bool IsReachBottom() const;
    bool IsReachLeft() const;
    bool IsReachRight() const;
    bool IsReachBoundary(bool isVertical) const;
    bool IsReachLowerBoundary(bool isVertical) const;
    bool IsReachUpperBoundary(bool isVertical) const;
    bool IsReachAvoidBoundary(float offset, Axis axis, float keyboardOffset) const;
    bool NeedScroll(bool isVertical, float keyboardOffset = 0.0f) const;
    float ClampVerticalOffset(float offset, float keyboardOffset) const;
    float ClampHorizontalOffset(float offset) const;
    bool IsScrollDirectionValid(bool isVertical) const;
    bool IsHotAreaOverflow(bool isDragging, float edgeThreshold) const;
    static OffsetF GetOffset2d(float offset, bool isVertical);
    RectF GetSafeAreaRect(bool isDragging) const;
    float CalCaretToContentRectDistanceVertical(
        const OffsetF& caretOffset, float caretHeight, float keyboardOffset) const;
    float CalCaretToContentRectDistanceHorizontal(const OffsetF& caretOffset, float caretWidth) const;
    static float CalcDragSpeed(float hotAreaStart, float hotAreaEnd, float point);
private:
    RectF& contentRect_;
    RectF& textRect_;
    RectF& frameRect_;
    bool& isSingleLine_;
};

// Resolves auto-scroll direction based on which boundary hot area the point enters.
class BoundaryScrollResolver {
    ACE_DISALLOW_COPY_AND_MOVE(BoundaryScrollResolver);
public:
    explicit BoundaryScrollResolver(RectF& frameRect) : frameRect_(frameRect) {}

    // Returns true if a scroll handler was invoked; false if point is outside all hot areas
    bool ResolveBoundaryScroll(AutoScrollParam& param, const RectF& safeAreaRect,
        const PointF& point, bool isSingleLineMode);
private:
    void HandleInHorizontalHotArea(AutoScrollParam& param, const RectF& safeAreaRect, const PointF& point);
    void HandleInVerticalHotArea(AutoScrollParam& param, const RectF& safeAreaRect, const PointF& point);
    // Resolve corner scrolling: pick dominant axis by displacement, then delegate to H/V handler
    void HandleCornerScrolling(AutoScrollParam& param, const RectF& safeAreaRect, const PointF& point);
    static bool IsInHorizontalHotArea(const RectF& safeAreaRect, const PointF& point);
    static bool IsInVerticalHotArea(const RectF& safeAreaRect, const PointF& point);
    static float CalcHorizontalBeyond(const RectF& safeAreaRect, const PointF& point);
    static float CalcVerticalBeyond(const RectF& safeAreaRect, const PointF& point);
    RectF& frameRect_;
};

// Timer-driven scheduler that periodically fires auto-scroll steps until stopped.
class AutoScrollScheduler : public AceType {
    DECLARE_ACE_TYPE(AutoScrollScheduler, AceType);
public:
    using OnAutoScrollStep = std::function<void()>;
    using OnAutoScrollStop = std::function<void()>;
    using BoundaryChecker = std::function<bool(bool)>;

    // taskExecutor is passed per Schedule call, so the scheduler holds no pattern ref.
    AutoScrollScheduler(OnAutoScrollStep onAutoScrollStep, OnAutoScrollStop onAutoScrollStop,
        BoundaryChecker reachLower, BoundaryChecker reachUpper)
        : onAutoScrollStep_(std::move(onAutoScrollStep)),
          onAutoScrollStop_(std::move(onAutoScrollStop)),
          reachLower_(std::move(reachLower)), reachUpper_(std::move(reachUpper)) {}
    void Schedule(AutoScrollParam param, bool isSingleLine, const RefPtr<TaskExecutor>& taskExecutor);
    void Stop();
    bool IsRunning() const { return isAutoScrollRunning_; }
    const AutoScrollParam& CurrentParam() const { return currentScrollParam_; }
private:
    OnAutoScrollStep onAutoScrollStep_;
    OnAutoScrollStop onAutoScrollStop_;
    BoundaryChecker reachLower_;
    BoundaryChecker reachUpper_;
    bool isAutoScrollRunning_ = false;
    AutoScrollParam currentScrollParam_;
    CancelableCallback<void()> autoScrollTask_;
};

class RichEditorScrollController : public AceType {
    DECLARE_ACE_TYPE(RichEditorScrollController, AceType);
public:
    explicit RichEditorScrollController(RichEditorPattern* pattern);
    static RefPtr<RichEditorScrollController> Create(bool isFree, RichEditorPattern* pattern);

    void ScheduleAutoScroll(AutoScrollParam param);
    void StopAutoScroll();
    // Must be called before strategy switch: releases pending timers/animations deterministically.
    void Dispose();
    bool IsAutoScrollRunning() const { return autoScrollScheduler_->IsRunning(); }
    // Fixed derives axis from isSingleLineMode_, Free from scroll event.
    void MoveHandlesOnScroll(float offset, Axis axis);
    void MoveHandleWithAxisOnScroll(float offset, bool isFirst, Axis axis);
    float MoveTextRectHorizontal(float offset);
    float MoveTextRectVertical(float offset, float keyboardOffset);
    float GetScrollOffset() const;
    void HandleScrollStart();
    void UpdateScrollBarColor(std::optional<Color> color, bool isUpdateProperty = false);
    bool UpdateScrollState();
    bool UpdateVerticalScrollState();
    bool UpdateHorizontalScrollState();
    bool IsSupportHorizontalScroll();
    OffsetF CalculateDestination(int32_t start, int32_t end, bool isRTL);
    void ScrollToVisible(int32_t start, int32_t end);
    void InitScrollBar(DisplayMode barMode);

    virtual bool IsFreeScrollEnabled() const = 0;
    virtual void ScheduleDisappearDelayTask() = 0;
    virtual void StopScrolling() = 0;
    virtual bool IsMouseOverScrollBar(const MouseInfo& info) = 0;
    virtual void UpdateScrollBarOffset() = 0;
    virtual void MoveCaretToContentRect(const OffsetF& caretOffset, float caretHeight) = 0;
    virtual void HandleAutoScrollNearBoundary(AutoScrollParam param, OffsetF offset) = 0;
    virtual bool OnScrollWithAxisCallback(float offset, int32_t source, Axis axis) = 0;
    virtual void SetScrollBar(DisplayMode displayMode) = 0;
    virtual void SetMinHeight(const Dimension& height) = 0;
    virtual void CheckScrollEnabled() = 0;
    virtual void UpdateScrollBarColor(const Color& foregroundColor, const Color& backgroundColor) = 0;

    virtual bool IsAttachedModifier() const { return false; }
    virtual void UpdateScrollBarOffsetWithAxis(Axis axis, bool needAnimation = true) {}
    virtual RefPtr<NGGestureRecognizer> GetScrollGestureRecognizer() const { return nullptr; }

    // Override only in subclasses that self-draw the scrollbar (e.g. FreeScroll); empty no-op for Fixed.
    virtual void OnDrawScrollBar(DrawingContext& context, const RefPtr<OverlayModifier>& modifier) {}
    virtual void UpdateScrollBar() {}
    virtual void AttachModifier(const RefPtr<OverlayModifier>& modifier) {}

protected:
    friend class RichEditorPattern;
    WeakPtr<RichEditorPattern> weakPattern_;
    bool& isSingleLineMode_;
    RectF& contentRect_;
    RectF& textRect_; // bound to pattern->richTextRect_
    RectF& frameRect_;
    RefPtr<RichEditorSelectOverlay>& selectOverlay_;
    TextSelector& textSelector_;

    ScrollGeometryEvaluator geometryEvaluator_;

    float scrollOffset_ = 0.0f;
    OffsetF prevAutoScrollOffset_;

    void DoAutoScrollStep();
    // Default 0.0f is intentional: horizontal axis ignores keyboardOffset entirely.
    float MoveTextRectWithAxis(float offset, Axis axis, float keyboardOffset = 0.0f);

    void MoveHandleOnScroll(const OffsetF& offset, bool isFirst);

    virtual void PlayScrollBarAppearAnimation(Axis axis) = 0;
    // FixedScroll ignores axis (derives from isSingleLineMode_).
    virtual float MoveTextRectForAutoScroll(float offset, Axis axis) = 0;

    // Weak-capture callbacks; called from initializer list.
    RefPtr<AutoScrollScheduler> CreateAutoScrollScheduler();

    RefPtr<AutoScrollScheduler> autoScrollScheduler_;
};

// Relies on ScrollablePattern base class for scrollbar and scroll events
class RichEditorFixedScrollController final : public RichEditorScrollController {
    DECLARE_ACE_TYPE(RichEditorFixedScrollController, RichEditorScrollController);
public:
    explicit RichEditorFixedScrollController(RichEditorPattern* pattern);
    bool IsFreeScrollEnabled() const override { return false; }
    void ScheduleDisappearDelayTask() override;
    void StopScrolling() override;
    bool IsMouseOverScrollBar(const MouseInfo& info) override;
    void UpdateScrollBarOffset() override;
    void MoveCaretToContentRect(const OffsetF& caretOffset, float caretHeight) override;
    void HandleAutoScrollNearBoundary(AutoScrollParam param, OffsetF offset) override;
    void SetScrollBar(DisplayMode displayMode) override;
    void SetMinHeight(const Dimension& height) override;
    void CheckScrollEnabled() override;
    void UpdateScrollBarColor(const Color& foregroundColor, const Color& backgroundColor) override;
    bool OnScrollWithAxisCallback(float offset, int32_t source, Axis axis) override;
private:
    // lower* = near edge (Left in single-line, Top otherwise); upper* = far edge.
    struct ScrollBoundaryGeometry {
        ScrollBoundaryGeometry(bool isVertical, const RectF& safeAreaRect, const RectF& handleRect)
            : lowerThreshold(isVertical ? safeAreaRect.Top() : safeAreaRect.Left()),
              upperThreshold(isVertical ? safeAreaRect.Bottom() : safeAreaRect.Right()),
              handleLower(isVertical ? handleRect.Top() : handleRect.Left()),
              handleUpper(isVertical ? handleRect.Bottom() : handleRect.Right()) {}
        float lowerThreshold;
        float upperThreshold;
        float handleLower;
        float handleUpper;
    };

    void AutoScrollForHandleEvent(AutoScrollParam& param, const ScrollBoundaryGeometry& geometry);
    void AutoScrollForDragEvent(AutoScrollParam& param, const ScrollBoundaryGeometry& geometry, bool isDragging);

    float GetAutoScrollOffsetDiff(const OffsetF& offset);
    float MoveTextRect(float offset, float keyboardOffset);
    void PlayScrollBarAppearAnimation(Axis axis) override;
    float MoveTextRectForAutoScroll(float offset, Axis axis) override;
    void MoveCaretToContentRectHorizontal(const OffsetF& caretOffset);
    void MoveCaretToContentRectVertical(const OffsetF& caretOffset, float caretHeight);
};

class RichEditorFreeScrollController final : public RichEditorScrollController {
    DECLARE_ACE_TYPE(RichEditorFreeScrollController, RichEditorScrollController);
public:
    explicit RichEditorFreeScrollController(RichEditorPattern* pattern);
    ~RichEditorFreeScrollController() override;
    bool IsFreeScrollEnabled() const override { return true; }
    void ScheduleDisappearDelayTask() override;
    void StopScrolling() override;
    bool IsMouseOverScrollBar(const MouseInfo& info) override;
    void UpdateScrollBarOffset() override;
    void MoveCaretToContentRect(const OffsetF& caretOffset, float caretHeight) override;
    void HandleAutoScrollNearBoundary(AutoScrollParam param, OffsetF offset) override;
    void SetScrollBar(DisplayMode displayMode) override;
    void SetMinHeight(const Dimension& height) override;
    void CheckScrollEnabled() override;
    bool IsAttachedModifier() const override;
    bool OnScrollWithAxisCallback(float offset, int32_t source, Axis axis) override;
    void UpdateScrollBarOffsetWithAxis(Axis axis, bool needAnimation = true) override;
    RefPtr<NGGestureRecognizer> GetScrollGestureRecognizer() const override;
    void UpdateScrollBarColor(const Color& foregroundColor, const Color& backgroundColor) override;
    void AttachModifier(const RefPtr<OverlayModifier>& modifier) override;
    void UpdateScrollBar() override;
    void OnDrawScrollBar(DrawingContext& context, const RefPtr<OverlayModifier>& modifier) override;
    void InitFreeScrollController(bool forceRecreate = false);
private:
    void ResetFreeScrollController();
    void ScheduleDisappearDelayTask(Axis axis);
    void PlayScrollBarAppearAnimation(Axis axis) override;
    void HandleScrollCallback(float offset, int32_t source, bool isVertical);
    void HandleEndScrollCallback(bool isVertical);
    void SyncOffset();
    float MoveTextRectForAutoScroll(float offset, Axis axis) override;
    void MoveCaretToContentRect(const RectF& caretRect);
    void UpdateBorderRadius();
    void RegisterScrollBarCallbacks();
    void PlayScrollBarUpdateAnimation(Axis axis);
    void MoveCaretToContentRectWithAxis(bool isVertical, const OffsetF& caretOffset, float caretSize,
        float keyboardOffset = 0.0f);
    BoundaryScrollResolver boundaryScrollResolver_;
    RefPtr<TextFreeScrollController> freeScrollController_;
    RefPtr<RichEditorScrollBar2D> scrollBar_;
    Axis scrollingAxis_ = Axis::NONE;
    bool isScrollBarModifierPropertyAttached_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_SCROLL_MANAGER_H
