/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_BASE_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/clipboard/clipboard.h"
#include "core/components_ng/manager/select_overlay/select_overlay_client.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {

enum class MouseStatus { PRESSED, RELEASED, MOVE, NONE };
enum {
    ACTION_SELECT_ALL, // Smallest code unit.
    ACTION_UNDO,
    ACTION_REDO,
    ACTION_CUT,
    ACTION_COPY,
    ACTION_PASTE,
    ACTION_SHARE,
    ACTION_PASTE_AS_PLAIN_TEXT,
    ACTION_REPLACE,
    ACTION_ASSIST,
    ACTION_AUTOFILL,
};

struct HandleMoveStatus {
    bool isFirsthandle = false;
    int32_t position = -1;
    OffsetF handleOffset;

    void Reset()
    {
        isFirsthandle = false;
        position = -1;
    }

    bool IsValid()
    {
        return position >= 0;
    }
};

template<typename T>
void GetTextCaretMetrics(RefPtr<FrameNode>& targetNode, CaretMetricsF& caretMetrics)
{
    CHECK_NULL_VOID(targetNode);
    if (targetNode->GetTag() == V2::SEARCH_ETS_TAG) {
        auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(targetNode->GetChildren().front());
        CHECK_NULL_VOID(textFieldFrameNode);
        auto textPattern = textFieldFrameNode->GetPattern<T>();
        CHECK_NULL_VOID(textPattern);
        textPattern->GetCaretMetrics(caretMetrics);
    } else {
        auto textPattern = targetNode->GetPattern<T>();
        CHECK_NULL_VOID(textPattern);
        textPattern->GetCaretMetrics(caretMetrics);
    }
}

class TextGestureSelector : public virtual AceType {
    DECLARE_ACE_TYPE(TextGestureSelector, AceType);

public:
    virtual void StartGestureSelection(int32_t start, int32_t end, const Offset& startOffset)
    {
        start_ = start;
        end_ = end;
        isStarted_ = start_ <= end_;
        startOffset_ = startOffset;
    }

    void CancelGestureSelection()
    {
        DoTextSelectionTouchCancel();
        ResetGestureSelection();
    }

    void EndGestureSelection(const TouchLocationInfo& locationInfo)
    {
        OnTextGenstureSelectionEnd(locationInfo);
        ResetGestureSelection();
    }

    void DoGestureSelection(const TouchEventInfo& info);

protected:
    virtual int32_t GetTouchIndex(const OffsetF& offset)
    {
        return -1;
    }
    virtual void OnTextGestureSelectionUpdate(int32_t start, int32_t end, const TouchEventInfo& info) {}
    virtual void OnTextGenstureSelectionEnd(const TouchLocationInfo& locationInfo) {}
    virtual void DoTextSelectionTouchCancel() {}
    int32_t GetSelectingFingerId()
    {
        return selectingFingerId_;
    }

    bool IsGestureSelectingText()
    {
        return isSelecting_;
    }
private:
    void ResetGestureSelection()
    {
        start_ = -1;
        end_ = -1;
        isStarted_ = false;
        startOffset_.Reset();
        isSelecting_ = false;
        selectingFingerId_ = -1;
    }
    void DoTextSelectionTouchMove(const TouchEventInfo& info);
    int32_t start_ = -1;
    int32_t end_ = -1;
    bool isStarted_ = false;
    bool isSelecting_ = false;
    Dimension minMoveDistance_ = 5.0_vp;
    Offset startOffset_;
    int32_t selectingFingerId_ = -1;
};

class TextBase : public SelectOverlayClient {
    DECLARE_ACE_TYPE(TextBase, SelectOverlayClient);

public:
    TextBase() = default;
    ~TextBase() override = default;

    virtual OffsetF GetContentOffset()
    {
        return OffsetF(0, 0);
    }

    virtual bool OnBackPressed()
    {
        return false;
    }

    virtual bool IsSelected() const
    {
        return textSelector_.IsValid() && !textSelector_.StartEqualToDest();
    }

    MouseStatus GetMouseStatus() const
    {
        return mouseStatus_;
    }

    // The methods that need to be implemented for input class components
    virtual RectF GetCaretRect() const
    {
        return { 0, 0, 0, 0 };
    }

    virtual void ScrollToSafeArea() const {}

    virtual void GetCaretMetrics(CaretMetricsF& caretCaretMetric) {}

    virtual void OnVirtualKeyboardAreaChanged() {}

    virtual RefPtr<Clipboard> GetClipboard()
    {
        return nullptr;
    }

    const RectF& GetContentRect() const
    {
        return contentRect_;
    }

    virtual RectF GetPaintContentRect()
    {
        return contentRect_;
    }

    virtual int32_t GetContentWideTextLength()
    {
        return 0;
    }

    virtual int32_t GetCaretIndex() const
    {
        return 0;
    }

    virtual OffsetF GetCaretOffset() const
    {
        return OffsetF();
    }

    virtual OffsetF GetTextPaintOffset() const
    {
        return OffsetF();
    }

    virtual OffsetF GetFirstHandleOffset() const
    {
        return OffsetF();
    }

    virtual OffsetF GetSecondHandleOffset() const
    {
        return OffsetF();
    }

    TextSelector GetTextSelector() const
    {
        return textSelector_;
    }

    virtual void GetSelectIndex(int32_t& start, int32_t& end) const
    {
        start = textSelector_.GetTextStart();
        end = textSelector_.GetTextEnd();
    }

    virtual const Dimension& GetAvoidSoftKeyboardOffset() const
    {
        return avoidKeyboardOffset_;
    }

    virtual void OnHandleAreaChanged() {}
    virtual void SetIsTextDraggable(bool isTextDraggable = true) {}

    virtual bool IsStopBackPress() const
    {
        return true;
    }

    static void SetSelectionNode(const SelectedByMouseInfo& info);
    static int32_t GetGraphemeClusterLength(const std::u16string& text, int32_t extend, bool checkPrev = false);
    static void CalculateSelectedRect(
        std::vector<RectF>& selectedRect, float longestLine, TextDirection direction = TextDirection::LTR);
    static float GetSelectedBlankLineWidth();
    static void CalculateSelectedRectEx(std::vector<RectF>& selectedRect, float lastLineBottom,
        const std::optional<TextDirection>& direction = std::nullopt);
    static bool UpdateSelectedBlankLineRect(RectF& rect, float blankWidth, TextAlign textAlign, float longestLine);
    static void SelectedRectsToLineGroup(const std::vector<RectF>& selectedRect,
        std::map<float, std::pair<RectF, std::vector<RectF>>>& lineGroup);
    static TextAlign CheckTextAlignByDirection(TextAlign textAlign, TextDirection direction);

    static void RevertLocalPointWithTransform(const RefPtr<FrameNode>& targetNode, OffsetF& point);
    static bool HasRenderTransform(const RefPtr<FrameNode>& targetNode);
    virtual bool IsTextEditableForStylus() const
    {
        return false;
    }
    static std::u16string ConvertStr8toStr16(const std::string& value);
    static bool isMouseOrTouchPad(SourceTool sourceTool)
    {
        return (sourceTool == SourceTool::MOUSE || sourceTool == SourceTool::TOUCHPAD);
    }

protected:
    TextSelector textSelector_;
    bool showSelect_ = true;
    bool afterDragSelect_ = false;
    bool releaseInDrop_ = false;
    SourceTool sourceTool_ = SourceTool::UNKNOWN;
    std::vector<std::u16string> dragContents_;
    MouseStatus mouseStatus_ = MouseStatus::NONE;
    RectF contentRect_;
    Dimension avoidKeyboardOffset_ = 24.0_vp;
    ACE_DISALLOW_COPY_AND_MOVE(TextBase);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_BASE_H
