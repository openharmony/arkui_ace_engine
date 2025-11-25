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
    RichEditorScrollController(RichEditorPattern* pattern) :
        weakPattern_(AceType::WeakClaim(pattern)),
        isSingleLineMode_(pattern->isSingleLineMode_),
        contentRect_(pattern->contentRect_),
        textRect_(pattern->richTextRect_),
        frameRect_(pattern->frameRect_),
        selectOverlay_(pattern->selectOverlay_),
        textSelector_(pattern->textSelector_)
    {}

    inline bool IsReachTop()
    {
        return NearEqual(textRect_.GetY(), contentRect_.GetY());
    }

    inline bool IsReachBottom()
    {
        return NearEqual(textRect_.Bottom(), contentRect_.Bottom());
    }

    inline bool IsReachLeft()
    {
        return NearEqual(textRect_.GetX(), contentRect_.GetX());
    }

    inline bool IsReachRight()
    {
        return NearEqual(textRect_.Right(), contentRect_.Right());
    }

    inline bool IsReachLowerBoundary()
    {
        return isSingleLineMode_ ? IsReachLeft() : IsReachTop();
    }

    inline bool IsReachUpperBoundary()
    {
        return isSingleLineMode_ ? IsReachRight() : IsReachBottom();
    }

    inline bool IsReachBoundary()
    {
        return IsReachLowerBoundary() || IsReachUpperBoundary();
    }

    inline bool IsReachLowerBoundary(const Offset& textOffset)
    {
        return isSingleLineMode_ ? LessOrEqual(textOffset.GetX(), 0) : LessOrEqual(textOffset.GetY(), 0);
    }

    inline bool IsReachUpperBoundary(const Offset& textOffset, const SizeF& contentSize)
    {
        return isSingleLineMode_ ? GreatOrEqual(textOffset.GetX(), contentSize.Width())
                                 : GreatOrEqual(textOffset.GetY(), contentSize.Height());
    }

    bool IsReachAvoidBoundary(float offset)
    {
        if (isSingleLineMode_) {
            return (IsReachLeft() && GreatNotEqual(offset, 0.0f)) || (IsReachRight() && LessNotEqual(offset, 0.0f));
        }
        auto pattern = weakPattern_.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        auto keyboardOffset = pattern->GetCrossOverHeight();
        return (IsReachTop() && GreatNotEqual(offset, 0.0f)) ||
           (NearEqual(textRect_.Bottom(), contentRect_.Bottom() - keyboardOffset) && LessNotEqual(offset, 0.0f));
    }

    static float CalcDragSpeed(float hotAreaStart, float hotAreaEnd, float point)
    {
        CHECK_NULL_RETURN(hotAreaStart != hotAreaEnd, 0.0f);
        auto distanceRatio = (point - hotAreaStart) / (hotAreaEnd - hotAreaStart);
        auto speedFactor = Curves::SHARP->MoveInternal(distanceRatio);
        return ((MAX_DRAG_SCROLL_SPEED * speedFactor) / TIME_UNIT) * AUTO_SCROLL_INTERVAL;
    }

    void ScheduleAutoScroll(AutoScrollParam param)
    {
        bool aboutToBeyondLower = IsReachLowerBoundary() && GreatNotEqual(param.offset, 0.0f);
        bool aboutToBeyondUpper = IsReachUpperBoundary() && LessNotEqual(param.offset, 0.0f);
        CHECK_NULL_VOID(!aboutToBeyondLower && !aboutToBeyondUpper);

        auto pattern = weakPattern_.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto context = pattern->GetContext();
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        if (param.isFirstRun_) {
            param.isFirstRun_ = false;
            currentScrollParam_ = param;
            CHECK_NULL_VOID(!isAutoScrollRunning_);
        }
        autoScrollTask_.Reset([weakPattern = weakPattern_, weakController = WeakClaim(this)]() {
            auto pattern = weakPattern.Upgrade();
            auto controller = weakController.Upgrade();
            CHECK_NULL_VOID(pattern && controller);
            pattern->OnAutoScroll(controller->currentScrollParam_);
            if (controller->IsReachBoundary()) {
                controller->StopAutoScroll();
            }
        });
        isAutoScrollRunning_ = true;
        taskExecutor->PostDelayedTask(autoScrollTask_, TaskExecutor::TaskType::UI, AUTO_SCROLL_INTERVAL,
            "ArkUIRichEditorScheduleAutoScroll");
    }

    void StopAutoScroll()
    {
        isAutoScrollRunning_ = false;
        autoScrollTask_.Cancel();
        prevAutoScrollOffset_ = OffsetF(0.0f, 0.0f);
        auto pattern = weakPattern_.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto scrollBar = pattern->GetScrollBar();
        IF_PRESENT(scrollBar, ScheduleDisappearDelayTask());
    }

    inline float GetAutoScrollOffsetDiff(const OffsetF& offset)
    {
        return isSingleLineMode_
            ? prevAutoScrollOffset_.GetX() - offset.GetX()
            : prevAutoScrollOffset_.GetY() - offset.GetY();
    }

    inline bool GetHotAreaOverflow(bool isDragging, float edgeThreshold)
    {
        auto maxHeight = isDragging ? frameRect_.Height() : contentRect_.Height();
        auto maxWidth = isDragging ? frameRect_.Width() : contentRect_.Width();
        auto doubleThreshold = edgeThreshold * 2;
        return isSingleLineMode_ ? GreatNotEqual(doubleThreshold, maxWidth) : GreatNotEqual(doubleThreshold, maxHeight);
    }

    void AutoScrollByEdgeDetection(AutoScrollParam param, OffsetF offset, EdgeDetectionStrategy strategy)
    {
        auto scrollOffsetDiff = GetAutoScrollOffsetDiff(offset);
        CHECK_NULL_VOID(!NearZero(scrollOffsetDiff));
        prevAutoScrollOffset_ = offset;
        auto contentRect = contentRect_;
        auto isDragging = param.autoScrollEvent == AutoScrollEvent::DRAG;
        float edgeThreshold = isDragging ? AUTO_SCROLL_DRAG_EDGE_DIS.ConvertToPx() : AUTO_SCROLL_EDGE_DIS.ConvertToPx();
        bool hotAreaOverflow = GetHotAreaOverflow(isDragging, edgeThreshold);
        if (hotAreaOverflow) {
            LOGE("xytest, HotAreaOverflow %{public}d", hotAreaOverflow);
            TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "AutoScrollByEdgeDetection: hot area height is great than max height.");
            return;
        }
        float topEdgeThreshold = isDragging ? edgeThreshold : edgeThreshold + contentRect.GetY();
        float leftEdgeThreshold = isDragging ? edgeThreshold : edgeThreshold + contentRect.GetX();
        float bottomThreshold = isDragging ? frameRect_.Height() - edgeThreshold : contentRect.Bottom() - edgeThreshold;
        float rightThreshold = isDragging ? frameRect_.Width() - edgeThreshold : contentRect.Right() - edgeThreshold;
        RectF handleRect{ offset, param.handleRect.GetSize() };
        auto lowerThreshold = isSingleLineMode_ ? leftEdgeThreshold : topEdgeThreshold;
        auto upperThreshold = isSingleLineMode_ ? rightThreshold : bottomThreshold;
        auto handleLower = isSingleLineMode_ ? handleRect.Left() : handleRect.Top();
        auto handleUpper = isSingleLineMode_ ? handleRect.Right() : handleRect.Bottom();
        if (param.autoScrollEvent == AutoScrollEvent::HANDLE) {
            if (GreatNotEqual(handleUpper, upperThreshold)) {
                param.offset = upperThreshold - handleUpper;
                ScheduleAutoScroll(param);
            } else if (LessNotEqual(handleLower, lowerThreshold)) {
                param.offset = lowerThreshold - handleLower;
                ScheduleAutoScroll(param);
            } else {
                StopAutoScroll();
            }
            return;
        }
        // drag and mouse
        if (GreatNotEqual(handleLower, upperThreshold)) {
            auto frameRectLen = isSingleLineMode_ ? frameRect_.Width() : frameRect_.Height();
            param.offset = isDragging ? -CalcDragSpeed(upperThreshold, frameRectLen, handleLower)
                        : upperThreshold - handleLower;
            ScheduleAutoScroll(param);
        } else if (LessNotEqual(handleLower, lowerThreshold)) {
            param.offset = isDragging ? CalcDragSpeed(lowerThreshold, 0, handleLower) : lowerThreshold - handleLower;
            ScheduleAutoScroll(param);
        } else {
            StopAutoScroll();
        }
    }

    inline OffsetF GetOffset2d(float offset)
    {
        float offsetX = isSingleLineMode_ ? offset : 0.0f;
        float offsetY = isSingleLineMode_ ? 0.0f : offset;
        return { offsetX, offsetY };
    }

    void MoveHandleOnScroll(float offset)
    {
        CHECK_NULL_VOID(!NearEqual(offset, 0.0f) && selectOverlay_->SelectOverlayIsOn());
        OffsetF offset2d = GetOffset2d(offset);
        MoveFirstHandleOnScroll(offset2d);
        MoveSecondHandleOnScroll(offset2d);
    }

    void MoveHandleOnScroll(float offset, bool isFirst)
    {
        CHECK_NULL_VOID(!NearEqual(offset, 0.0f) && selectOverlay_->SelectOverlayIsOn());
        OffsetF offset2d = GetOffset2d(offset);
        isFirst ? MoveFirstHandleOnScroll(offset2d) : MoveSecondHandleOnScroll(offset2d);
    }

    void MoveFirstHandleOnScroll(const OffsetF& offset)
    {
        textSelector_.selectionBaseOffset += offset;
        auto firstHandleOffset = textSelector_.firstHandle.GetOffset();
        firstHandleOffset += offset;
        textSelector_.firstHandle.SetOffset(firstHandleOffset);
        selectOverlay_->UpdateFirstHandleOffset();
    }

    void MoveSecondHandleOnScroll(const OffsetF& offset)
    {
        textSelector_.selectionDestinationOffset += offset;
        auto secondHandleOffset = textSelector_.secondHandle.GetOffset();
        secondHandleOffset += offset;
        textSelector_.secondHandle.SetOffset(secondHandleOffset);
        selectOverlay_->UpdateSecondHandleOffset();
    }

    float MoveTextRect(float offset)
    {
        return isSingleLineMode_ ? MoveTextRectHorizontal(offset) : MoveTextRectVertical(offset);
    }

    float MoveTextRectHorizontal(float offset)
    {
        if (textRect_.GetX() + offset > contentRect_.GetX()) {
            offset = contentRect_.GetX() - textRect_.GetX();
        } else if (textRect_.Right() + offset < contentRect_.Right()) {
            offset = contentRect_.Right() - textRect_.Right();
        }
        scrollOffset_ = textRect_.GetX() + offset;
        textRect_.SetOffset(OffsetF(scrollOffset_, textRect_.GetY()));
        return offset;
    }

    float MoveTextRectVertical(float offset)
    {
        auto pattern = weakPattern_.Upgrade();
        CHECK_NULL_RETURN(pattern, 0.0f);
        auto keyboardOffset = pattern->GetCrossOverHeight();
        if (GreatNotEqual(textRect_.Height(), contentRect_.Height() - keyboardOffset)) {
            if (GreatNotEqual(textRect_.GetY() + offset, contentRect_.GetY())) {
                offset = contentRect_.GetY() - textRect_.GetY();
            } else if (LessNotEqual(textRect_.Bottom() + offset, contentRect_.Bottom() - keyboardOffset)) {
                offset = contentRect_.Bottom() - keyboardOffset - textRect_.Bottom();
            }
        } else if (!NearEqual(textRect_.GetY(), contentRect_.GetY())) {
            offset = contentRect_.GetY() - textRect_.GetY();
        } else {
            return 0.0f;
        }
        if (NearEqual(offset, 0.0f)) {
            return offset;
        }
        scrollOffset_ = textRect_.GetY() + offset;
        textRect_.SetOffset(OffsetF(textRect_.GetX(), scrollOffset_));
        return offset;
    }

    float CalCaretToContentRectDistanceVertical(const OffsetF& caretOffset, float caretHeight, float keyboardOffset)
    {
        if (LessNotEqual(contentRect_.GetSize().Height(), caretHeight) &&
            !NearEqual(caretOffset.GetY() + caretHeight, contentRect_.Bottom() - keyboardOffset)) {
            return contentRect_.Bottom() - keyboardOffset - caretOffset.GetY() - caretHeight;
        }
        if (LessNotEqual(contentRect_.GetSize().Height(), caretHeight)) {
            return 0.0f;
        }
        if (LessNotEqual(caretOffset.GetY(), contentRect_.GetY())) {
            if (LessOrEqual(caretOffset.GetX(), textRect_.GetX())) {
                return contentRect_.GetY() - caretOffset.GetY() + caretHeight;
            } else {
                return contentRect_.GetY() - caretOffset.GetY();
            }
        } else if (GreatNotEqual(caretOffset.GetY() + caretHeight, contentRect_.Bottom() - keyboardOffset)) {
            return contentRect_.Bottom() - keyboardOffset - caretOffset.GetY() - caretHeight -
                CARET_BOTTOM_DISTANCE.ConvertToPx();
        }
        return 0.0f;
    }

    float CalCaretToContentRectDistanceHorizontal(const OffsetF& caretOffset, float caretWidth)
    {
        float caretLeft = caretOffset.GetX();
        float caretRight = caretOffset.GetX() + caretWidth;
        float distanceLeft = std::max(contentRect_.Left() - caretLeft, 0.0f);
        float distanceRight = std::min(contentRect_.Right() - caretRight, 0.0f);
        return distanceLeft + distanceRight;
    }

    bool NeedScroll()
    {
        return isSingleLineMode_ ? GreatNotEqual(textRect_.Width(), contentRect_.Width())
                                 : GreatNotEqual(textRect_.Height(), contentRect_.Height());
    }


    float GetScrollOffset()
    {
        return scrollOffset_;
    }

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
    bool isAutoScrollRunning_;
    AutoScrollParam currentScrollParam_;
    CancelableCallback<void()> autoScrollTask_;
    OffsetF prevAutoScrollOffset_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_SCROLL_MANAGER_H