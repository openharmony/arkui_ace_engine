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

namespace OHOS::Ace::NG {
namespace {
constexpr float MAX_DRAG_SCROLL_SPEED = 2400.0f;
constexpr int32_t AUTO_SCROLL_INTERVAL = 15;
constexpr float TIME_UNIT = 1000.0f;
constexpr Dimension AUTO_SCROLL_DRAG_EDGE_DIS = 58.0_vp;
constexpr Dimension AUTO_SCROLL_EDGE_DIS = 15.0_vp;
constexpr Dimension CARET_BOTTOM_DISTANCE = 16.0_vp;
}

class RichEditorScrollController final : public AceType {
    DECLARE_ACE_TYPE(RichEditorScrollController, AceType);
public:
    RichEditorScrollController(RichEditorPattern* pattern);
    bool IsReachTop();
    bool IsReachBottom();
    bool IsReachLeft();
    bool IsReachRight();
    bool IsReachLowerBoundary();
    bool IsReachUpperBoundary();
    bool IsReachBoundary();
    bool IsReachLowerBoundary(const Offset& textOffset);
    bool IsReachUpperBoundary(const Offset& textOffset, const SizeF& contentSize);
    bool IsReachAvoidBoundary(float offset);
    static float CalcDragSpeed(float hotAreaStart, float hotAreaEnd, float point);
    void ScheduleAutoScroll(AutoScrollParam param);
    void StopAutoScroll();
    float GetAutoScrollOffsetDiff(const OffsetF& offset);
    bool GetHotAreaOverflow(bool isDragging, float edgeThreshold);
    void AutoScrollByEdgeDetection(AutoScrollParam param, OffsetF offset, EdgeDetectionStrategy strategy);
    OffsetF GetOffset2d(float offset);
    void MoveHandleOnScroll(float offset);
    void MoveHandleOnScroll(float offset, bool isFirst);
    void MoveFirstHandleOnScroll(const OffsetF& offset);
    void MoveSecondHandleOnScroll(const OffsetF& offset);
    float MoveTextRect(float offset);
    float MoveTextRectHorizontal(float offset);
    float MoveTextRectVertical(float offset);
    float CalCaretToContentRectDistanceVertical(const OffsetF& caretOffset, float caretHeight, float keyboardOffset);
    float CalCaretToContentRectDistanceHorizontal(const OffsetF& caretOffset, float caretWidth);
    bool NeedScroll();
    float GetScrollOffset();
    // add for horizontal scroll
    bool IsFreeScrollEnabled() const;
    RefPtr<NGGestureRecognizer> GetScrollGestureRecognizer() const;
    void InitFreeScrollController();
    void HandleScrollCallback(float offset, int32_t source, bool isVertical);
    bool OnScrollWithAxisCallback(float offset, int32_t source, Axis axis);
    void HandleEndScrollCallback(bool isVertical);
    void SyncOffset();
    bool IsReachAvoidBoundary(float offset, Axis axis);
    float MoveTextRectWithAxis(float offset, Axis axis);
    OffsetF GetOffset2d(float offset, bool isVertical);
    void MoveHandleOnScrollWithAxis(float offset, Axis axis);
    void MoveHandleOnScrollWithAxis(float offset, bool isFirst, Axis axis);
    void MoveCaretToContentRect(const RectF& caretRect);
    bool IsHotAreaOverflow(bool isDragging, float edgeThreshold, bool isVertical);
    void HandleAutoScrollNearBoundary(AutoScrollParam param, OffsetF offset);
    void HandleInHorizontalHotArea(AutoScrollParam& param, const RectF& safeAreaRect, const PointF& point);
    void HandleInVerticalHotArea(AutoScrollParam& param, const RectF& safeAreaRect, const PointF& point);
    void HandleCornerScrolling(AutoScrollParam& param, const RectF& safeAreaRect, const PointF& point);
    void ProcessAutoScroll();
    float CalculateAngle(const PointF& origin, const PointF& target);
    bool IsReachBoundary(bool isVertical);
    bool IsReachLowerBoundary(bool isVertical);
    bool IsReachUpperBoundary(bool isVertical);
    void ResetFreeScrollController();
    void PlayScrollBarAppearAnimation(Axis axis);
    void ScheduleDisappearDelayTask();
    void ScheduleDisappearDelayTask(Axis axis);
    void StopScrolling();
    void OnDrawScrollBar(DrawingContext& context);
    void UpdateScrollBarColor(std::optional<Color> color);
    bool IsMouseOverScrollBar(const MouseInfo& info);
    bool IsPointInScrollBarRect(const Point& point, bool isVertical);
    void CheckScrollEnabled();
    void SetScrollBar(DisplayMode displayMode);
    void UpdateBorderRadius();
    void UpdateScrollBar();
    void UpdateScrollBarOffset();
    void PlayScrollBarUpdateAnimation(Axis axis);
    void UpdateScrollBarOffsetWithAxis(Axis axis, bool needAnimation = true);
    void SetMinHeight(const Dimension& height);
    bool IsAttachedModifier() const;
    void AttachModifier(const RefPtr<OverlayModifier>& modifier);
    bool UpdateScrollState();
    bool UpdateVerticalScrollState();
    bool UpdateHorizontalScrollState();
    bool IsSupportHorizontalScroll();
    OffsetF CalculateDestination(int32_t start, int32_t end, bool isRTL);
    void ScrollToVisible(int32_t start, int32_t end);

private:
    friend class RichEditorPattern;
    WeakPtr<RichEditorPattern> weakPattern_;
    bool& isSingleLineMode_;
    RectF& contentRect_;
    RectF& textRect_;
    RectF& frameRect_;
    RefPtr<RichEditorSelectOverlay>& selectOverlay_;
    TextSelector& textSelector_;

    float scrollOffset_ = 0.0f;
    bool isAutoScrollRunning_ = false;
    AutoScrollParam currentScrollParam_;
    CancelableCallback<void()> autoScrollTask_;
    OffsetF prevAutoScrollOffset_;

    RefPtr<TextFreeScrollController> freeScrollController_;
    RefPtr<TextScrollBar2D> scrollBar_;
    Axis scrollingAxis_ = Axis::NONE;
    bool isScrollBarModifierPropertyAttached_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_SCROLL_MANAGER_H