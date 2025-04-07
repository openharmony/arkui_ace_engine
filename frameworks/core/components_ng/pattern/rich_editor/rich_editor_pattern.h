/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_PATTERN_H

#include <cstdint>
#include <map>
#include <optional>
#include <set>
#include <string>

#include "base/log/event_report.h"
#include "base/utils/device_config.h"
#include "core/common/ai/ai_write_adapter.h"
#include "core/common/ime/text_edit_controller.h"
#include "core/common/ime/text_input_action.h"
#include "core/common/ime/text_input_client.h"
#include "core/common/ime/text_input_configuration.h"
#include "core/common/ime/text_input_connection.h"
#include "core/common/ime/text_input_formatter.h"
#include "core/common/ime/text_input_proxy.h"
#include "core/common/ime/text_input_type.h"
#include "core/common/ime/text_selection.h"
#include "core/components/common/properties/text_layout_info.h"
#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_accessibility_property.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_content_modifier.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_controller.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_layout_algorithm.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_layout_property.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_overlay_modifier.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_paint_method.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_select_overlay.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_styled_string_controller.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/select_overlay/magnifier.h"
#include "core/components_ng/pattern/select_overlay/magnifier_controller.h"
#include "core/components_ng/pattern/text/layout_info_interface.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/text/text_emoji_processor.h"

#ifndef ACE_UNITTEST
#ifdef ENABLE_STANDARD_INPUT
#include "refbase.h"

namespace OHOS::MiscServices {
class OnTextChangedListener;
struct TextConfig;
} // namespace OHOS::MiscServices
#endif
#endif

#define COPY_SPAN_STYLE_IF_PRESENT(sourceNode, targetNode, styleType) \
    do {                                                                            \
        if ((sourceNode)->Has##styleType()) {                                       \
            (targetNode)->Update##styleType(*((sourceNode)->Get##styleType()));     \
        }                                                                           \
    } while (false)
#define CONTENT_MODIFY_LOCK(patternPtr) ContentModifyLock contentModifyLock(patternPtr)

#define IF_TRUE(cond, func) \
    do {                    \
        if (cond) {         \
            func;           \
        }                   \
    } while (false)

#define IF_PRESENT(opt, func) \
    do {                      \
        if (opt) {            \
            opt->func;        \
        }                     \
    } while (false)

namespace OHOS::Ace::NG {
class InspectorFilter;
class OneStepDragController;
class RichEditorUndoManager;
struct UndoRedoRecord;

// TextPattern is the base class for text render node to perform paint text.
enum class MoveDirection { FORWARD, BACKWARD };

enum class AutoScrollEvent { HANDLE, DRAG, MOUSE, NONE, CARET };
enum class EdgeDetectionStrategy { OUT_BOUNDARY, IN_BOUNDARY, DISABLE };
struct AutoScrollParam {
    AutoScrollEvent autoScrollEvent = AutoScrollEvent::NONE;
    RectF handleRect;
    bool isFirstHandle = false;
    float offset = 0.0f;
    bool showScrollbar = false;
    Offset eventOffset;
    bool isFirstRun_ = true;
};
enum class RecordType { DEL_FORWARD = 0, DEL_BACKWARD = 1, INSERT = 2, UNDO = 3, REDO = 4, DRAG = 5 };
enum class SelectorAdjustPolicy { INCLUDE = 0, EXCLUDE };
enum class HandleType { FIRST = 0, SECOND };
enum class SelectType { SELECT_FORWARD = 0, SELECT_BACKWARD, SELECT_NOTHING };
enum class CaretAffinityPolicy { DEFAULT = 0, UPSTREAM_FIRST, DOWNSTREAM_FIRST };
enum class OperationType { DEFAULT = 0, DRAG, IME };
const std::map<std::pair<HandleType, SelectorAdjustPolicy>, MoveDirection> SELECTOR_ADJUST_DIR_MAP = {
    {{ HandleType::FIRST, SelectorAdjustPolicy::INCLUDE }, MoveDirection::BACKWARD },
    {{ HandleType::FIRST, SelectorAdjustPolicy::EXCLUDE }, MoveDirection::FORWARD },
    {{ HandleType::SECOND, SelectorAdjustPolicy::INCLUDE }, MoveDirection::FORWARD },
    {{ HandleType::SECOND, SelectorAdjustPolicy::EXCLUDE }, MoveDirection::BACKWARD }
};
struct CaretOffsetInfo {
    // caret front offset info
    OffsetF caretOffsetUp;
    // caret end offset info
    OffsetF caretOffsetDown;
    // caret position offset info
    OffsetF caretOffsetLine;
    float caretHeightUp = 0.0f;
    float caretHeightDown = 0.0f;
    float caretHeightLine = 0.0f;
};
enum class PositionType { DEFAULT, PARAGRAPH_START, PARAGRAPH_END, LINE_START, LINE_END };
struct SysScale {
    double dipScale = 1.0;
    double logicScale = 1.0;
    double fontScale = 1.0;
    double fontWeightScale = 1.0;
    bool operator==(const SysScale& rhs) const
    {
        return NearEqual(dipScale, rhs.dipScale)
            && NearEqual(logicScale, rhs.logicScale)
            && NearEqual(fontScale, rhs.fontScale)
            && NearEqual(fontWeightScale, rhs.fontWeightScale);
    }
    bool operator!=(const SysScale& rhs) const
    {
        return !operator==(rhs);
    }
    std::string ToString()
    {
        std::stringstream ss;
        ss << dipScale << ", " << logicScale << ", " << fontScale << ", " << fontWeightScale;
        return ss.str();
    }
};

class RichEditorPattern
    : public TextPattern, public ScrollablePattern, public TextInputClient, public SpanWatcher {
    DECLARE_ACE_TYPE(RichEditorPattern, TextPattern, ScrollablePattern, TextInputClient, SpanWatcher);

public:
    RichEditorPattern();
    ~RichEditorPattern() override;

    struct OperationRecord {
        OperationRecord() : beforeCaretPosition(-1), afterCaretPosition(-1), deleteCaretPostion(-1) {}
        std::optional<std::u16string> addText;
        std::optional<std::u16string> deleteText;
        int32_t beforeCaretPosition;
        int32_t afterCaretPosition;
        int32_t deleteCaretPostion;
    };

    struct PreviewTextRecord {
        int32_t startOffset = INVALID_VALUE;
        int32_t endOffset = INVALID_VALUE;
        bool previewTextHasStarted = false;
        std::u16string previewContent;
        std::u16string newPreviewContent;
        bool needReplacePreviewText = false;
        bool needReplaceText = false;
        PreviewRange replacedRange;
        bool isSpanSplit = false;
        bool needUpdateCaret = true;
        bool previewTextExiting = false;

        std::string ToString() const
        {
            auto jsonValue = JsonUtil::Create(true);
            JSON_STRING_PUT_STRING(jsonValue, previewContent);
            JSON_STRING_PUT_BOOL(jsonValue, previewTextHasStarted);
            JSON_STRING_PUT_INT(jsonValue, startOffset);
            JSON_STRING_PUT_INT(jsonValue, endOffset);
            JSON_STRING_PUT_BOOL(jsonValue, isSpanSplit);
            JSON_STRING_PUT_BOOL(jsonValue, needUpdateCaret);
            JSON_STRING_PUT_BOOL(jsonValue, previewTextExiting);

            return jsonValue->ToString();
        }

        void Reset()
        {
            startOffset = INVALID_VALUE;
            endOffset = INVALID_VALUE;
            previewContent.clear();
            previewTextHasStarted = false;
            needReplacePreviewText = false;
            needReplaceText = false;
            replacedRange.Set(INVALID_VALUE, INVALID_VALUE);
            isSpanSplit = false;
            previewTextExiting = false;
        }

        bool IsValid() const
        {
            return !previewContent.empty() && previewTextHasStarted && startOffset >= 0 && endOffset >= startOffset;
        }

        bool NeedReplace() const
        {
            return needReplacePreviewText || needReplaceText;
        }
    };

    struct TouchAndMoveCaretState {
        bool isTouchCaret = false;
        bool isMoveCaret = false;
        Offset touchDownOffset;
        const Dimension minDistance = 5.0_vp;
        std::optional<int32_t> touchFingerId = std::nullopt;

        void Reset()
        {
            isTouchCaret = false;
            isMoveCaret = false;
            touchDownOffset.Reset();
            touchFingerId.reset();
        }
    };

    struct FloatingCaretState {
        bool isFloatingCaretVisible = false;
        bool isOriginCaretVisible = false;
        std::optional<Offset> touchMoveOffset = std::nullopt;
        Color originCaretColor = Color(0x4D000000);
        const Dimension showFloatingCaretDistance = 10.0_vp;

        void Reset()
        {
            isFloatingCaretVisible = false;
            isOriginCaretVisible = false;
            touchMoveOffset.reset();
        }

        void UpdateOriginCaretColor(ColorMode colorMode)
        {
            originCaretColor = colorMode == ColorMode::DARK ? Color(0x4DFFFFFF) : Color(0x4D000000);
        }

        void UpdateByTouchMove(const Offset& offset, double distance, const RectF& boundaryRect)
        {
            isFloatingCaretVisible = true;
            touchMoveOffset = offset;
            bool isCaretAtBoundaryLeft = LessOrEqual(touchMoveOffset->GetX(), boundaryRect.Left());
            bool isCaretAtBoundaryRight = GreatOrEqual(touchMoveOffset->GetX(), boundaryRect.Right());
            if (!isCaretAtBoundaryLeft && !isCaretAtBoundaryRight) {
                isOriginCaretVisible = GreatNotEqual(distance, showFloatingCaretDistance.ConvertToPx());
            } else {
                touchMoveOffset->SetX(isCaretAtBoundaryLeft ? boundaryRect.Left() : boundaryRect.Right());
                isOriginCaretVisible = true;
            }
        }
    };

    const FloatingCaretState& GetFloatingCaretState() const
    {
        return floatingCaretState_;
    }

    void ResetFloatingCaretState()
    {
        floatingCaretState_.Reset();
    }

    class ContentModifyLock {
    public:
        ContentModifyLock();
        ContentModifyLock(RichEditorPattern* pattern)
        {
            pattern->isModifyingContent_ = true;
            pattern_ = WeakClaim(pattern);
        }
        ~ContentModifyLock()
        {
            auto pattern = pattern_.Upgrade();
            if (!pattern) {
                TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "pattern is null, unlock failed");
                return;
            }
            pattern->isModifyingContent_ = false;
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    private:
        WeakPtr<RichEditorPattern> pattern_;
    };

    bool NotUpdateCaretInPreview(int32_t caret, const PreviewTextRecord& record);
    int32_t SetPreviewText(const std::u16string& previewTextValue, const PreviewRange range) override;

    const PreviewTextInfo GetPreviewTextInfo() const;

    void FinishTextPreview() override;

    void ReceivePreviewTextStyle(const std::string& style) override
    {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "previewTextStyle: [%{public}s]", style.c_str());
        auto property = GetLayoutProperty<RichEditorLayoutProperty>();
        CHECK_NULL_VOID(property && !style.empty());
        property->UpdatePreviewTextStyle(style);
    }

    int32_t CheckPreviewTextValidate(const std::string& previewTextValue, const PreviewRange range) override;

    int32_t CheckPreviewTextValidate(const std::u16string& previewTextValue, const PreviewRange range) override;

    const Color& GetPreviewTextDecorationColor() const;

    bool IsPreviewTextInputting()
    {
        return previewTextRecord_.IsValid();
    }

    std::vector<RectF> GetPreviewTextRects();

    float GetPreviewTextUnderlineWidth() const;

    PreviewTextStyle GetPreviewTextStyle() const;

    void SetSupportPreviewText(bool isTextPreviewSupported)
    {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "enablePreviewText=%{public}d", isTextPreviewSupported);
        isTextPreviewSupported_ = isTextPreviewSupported;
    }

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(TextInputAction, TextInputAction)
    TextInputAction GetDefaultTextInputAction() const;

    // RichEditor needs softkeyboard, override function.
    bool NeedSoftKeyboard() const override
    {
        return true;
    }

    BlurReason GetBlurReason();

    uint32_t GetSCBSystemWindowId();

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<RichEditorEventHub>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<RichEditorLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        HandleSysScaleChanged();
        return MakeRefPtr<RichEditorLayoutAlgorithm>(spans_, &paragraphs_, typingTextStyle_, &paragraphCache_);
    }

    void HandleSysScaleChanged()
    {
        auto ctx = GetContext();
        if (!ctx) {
            TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "context is nullptr, handle scale failed");
            return;
        }
        SysScale sysScale{ ctx->GetDipScale(), ctx->GetLogicScale(), ctx->GetFontScale(), ctx->GetFontWeightScale() };
        if (sysScale != lastSysScale_) {
            TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "sys scale changed, %{public}s -> %{public}s",
                lastSysScale_.ToString().c_str(), sysScale.ToString().c_str());
            lastSysScale_ = sysScale;
            paragraphCache_.Clear();
        }
    }

    FocusPattern GetFocusPattern() const override
    {
        FocusPattern focusPattern = { FocusType::NODE, true, FocusStyleType::INNER_BORDER };
        focusPattern.SetIsFocusActiveWhenFocused(true);
        return focusPattern;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    const RefPtr<RichEditorController>& GetRichEditorController()
    {
        return richEditorController_;
    }

    void SetRichEditorController(const RefPtr<RichEditorController>& controller)
    {
        richEditorController_ = controller;
    }

    const RefPtr<RichEditorStyledStringController>& GetRichEditorStyledStringController()
    {
        return richEditorStyledStringController_;
    }

    void SetRichEditorStyledStringController(const RefPtr<RichEditorStyledStringController>& controller)
    {
        richEditorStyledStringController_ = controller;
    }

    long long GetTimestamp() const
    {
        return timestamp_;
    }

    void SetMaxLength(std::optional<int32_t> maxLength)
    {
        if (maxLength != INT_MAX) {
            DeleteToMaxLength(maxLength);
        }
        maxLength_ = maxLength;
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "maxLength: [%{public}d]", maxLength_.value_or(INT_MAX));
    }

    int32_t GetMaxLength()
    {
        return maxLength_.value_or(INT_MAX);
    }
    
    void SetMaxLines(int32_t maxLines)
    {
        maxLines_ = maxLines;
    }

    int32_t GetMaxLines()
    {
        return maxLines_;
    }

    void SetMaxLinesHeight(float maxLinesHeight)
    {
        maxLinesHeight_ = maxLinesHeight;
    }

    float GetMaxLinesHeight()
    {
        return maxLinesHeight_;
    }

    void UpdateSpanPosition()
    {
        uint32_t spanTextLength = 0;
        for (auto& span : spans_) {
            span->rangeStart = static_cast<int32_t>(spanTextLength);
            spanTextLength += span->content.length();
            span->position = static_cast<int32_t>(spanTextLength);
        }
    }

    void OnAttachToMainTree() override
    {
        TextPattern::OnAttachToMainTree();
    }

    void RegisterCaretChangeListener(std::function<void(int32_t)>&& listener)
    {
        caretChangeListener_ = listener;
    }

    void SetStyledString(const RefPtr<SpanString>& value);

    RefPtr<MutableSpanString> GetStyledString() const
    {
        return styledString_;
    }

    bool IsStyledStringModeEnabled()
    {
        return isSpanStringMode_ && styledString_;
    }

    void UpdateSpanItems(const std::list<RefPtr<NG::SpanItem>>& spanItems) override;
    void ProcessStyledString();
    void MountImageNode(const RefPtr<ImageSpanItem>& imageItem);
    void SetImageLayoutProperty(RefPtr<ImageSpanNode> imageNode, const ImageSpanOptions& options);
    void InsertValueInStyledString(
        const std::u16string& insertValue, bool shouldCommitInput = false, bool isPaste = false);
    void HandleStyledStringInsertion(RefPtr<SpanString> insertStyledString, const UndoRedoRecord& record,
        std::u16string& subValue, bool needReplaceInTextPreview, bool shouldCommitInput);
    RefPtr<SpanString> CreateStyledStringByTextStyle(
        const std::u16string& insertValue, const struct UpdateSpanStyle& updateSpanStyle, const TextStyle& textStyle);
    RefPtr<FontSpan> CreateFontSpanByTextStyle(
        const struct UpdateSpanStyle& updateSpanStyle, const TextStyle& textStyle, int32_t length);
    RefPtr<DecorationSpan> CreateDecorationSpanByTextStyle(
        const struct UpdateSpanStyle& updateSpanStyle, const TextStyle& textStyle, int32_t length);
    void DeleteBackwardInStyledString(int32_t length);
    void DeleteForwardInStyledString(int32_t length, bool isIME = true);
    void DeleteValueInStyledString(int32_t start, int32_t length, bool isIME = true, bool isUpdateCaret = true);

    RefPtr<SpanString> CreateStyledStringByStyleBefore(int32_t start, const std::u16string& string);
    bool BeforeStyledStringChange(const UndoRedoRecord& record, bool isUndo = false);
    bool BeforeStyledStringChange(int32_t start, int32_t length, const std::u16string& string);
    bool BeforeStyledStringChange(int32_t start, int32_t length, const RefPtr<SpanString>& styledString);
    void AfterStyledStringChange(const UndoRedoRecord& record, bool isUndo = false);
    void AfterStyledStringChange(int32_t start, int32_t length, const std::u16string& string);
    void HandleUndoInStyledString(const UndoRedoRecord& record);
    void HandleRedoInStyledString(const UndoRedoRecord& record);
    void ApplyRecordInStyledString(const UndoRedoRecord& record);

    void ResetBeforePaste();
    void ResetAfterPaste();

    void OnVisibleChange(bool isVisible) override;
    void OnModifyDone() override;
    void BeforeCreateLayoutWrapper() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void HandleSelectOverlayOnLayoutSwap();
    void FireOnReady();
    void MoveCaretOnLayoutSwap();

    void UpdateEditingValue(const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent = true) override;
    void PerformAction(TextInputAction action, bool forceCloseKeyboard = true) override;
    bool IsIMEOperation(OperationType operationType);
    void InsertValue(const std::string& insertValue, bool isIME = false) override;
    void InsertValue(const std::u16string& insertValue, bool isIME = false) override;
    void InsertValueByOperationType(const std::u16string& insertValue,
        OperationType operationType = OperationType::DEFAULT);
    void InsertValueOperation(const std::u16string& insertValue, OperationRecord* const record = nullptr,
        OperationType operationType = OperationType::IME);
    void DeleteSelectOperation(OperationRecord* const record);
    void DeleteByRange(OperationRecord* const record, int32_t start, int32_t end);
    void InsertDiffStyleValueInSpan(RefPtr<SpanNode>& spanNode, const TextInsertValueInfo& info,
        const std::u16string& insertValue, bool isIME = true);
    void InsertValueByPaste(const std::u16string& insertValue);
    bool IsLineSeparatorInLast(RefPtr<SpanNode>& spanNode);
    void InsertValueToSpanNode(
        RefPtr<SpanNode>& spanNode, const std::u16string& insertValue, const TextInsertValueInfo& info);
    void SpanNodeFission(RefPtr<SpanNode>& spanNode);
    void CreateTextSpanNode(RefPtr<SpanNode>& spanNode, const TextInsertValueInfo& info,
        const std::u16string& insertValue, bool isIME = true);
    void SetDefaultColor(RefPtr<SpanNode>& spanNode);
    void HandleOnDelete(bool backward) override;
    std::pair<bool, bool> IsEmojiOnCaretPosition(int32_t& emojiLength, bool isBackward, int32_t length);
    int32_t CalculateDeleteLength(int32_t length, bool isBackward);
    void DeleteBackward(int32_t length = 1) override;
    std::u16string DeleteBackwardOperation(int32_t length);
    void DeleteForward(int32_t length = 1) override;
    std::u16string DeleteForwardOperation(int32_t length);
    void SetInputMethodStatus(bool keyboardShown) override;
    bool ClickAISpan(const PointF& textOffset, const AISpan& aiSpan) override;
    WindowMode GetWindowMode();
    bool GetIsMidScene();
    void NotifyKeyboardClosedByUser() override
    {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "KeyboardClosedByUser");
        FocusHub::LostFocusToViewRoot();
    }
    void NotifyKeyboardClosed() override
    {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "KeyboardClosed");
        CHECK_NULL_VOID(HasFocus());
        CHECK_NULL_VOID(!customKeyboardBuilder_ || !isCustomKeyboardAttached_);

        // lost focus in floating window mode
        auto windowMode = GetWindowMode();
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "KeyboardClosed windowMode = %{public}d", windowMode);
        if (windowMode == WindowMode::WINDOW_MODE_FLOATING || windowMode == WindowMode::WINDOW_MODE_SPLIT_PRIMARY ||
            windowMode == WindowMode::WINDOW_MODE_SPLIT_SECONDARY) {
            FocusHub::LostFocusToViewRoot();
        }
    }
    void ClearOperationRecords();
    void ClearRedoOperationRecords();
    void AddOperationRecord(const OperationRecord& record);
    void UpdateShiftFlag(const KeyEvent& keyEvent)override;
    bool HandleOnEscape() override;
    void HandleOnUndoAction() override;
    void HandleOnRedoAction() override;
    void CursorMove(CaretMoveIntent direction) override;
    void HandleSetSelection(int32_t start, int32_t end, bool showHandle) override;
    void HandleExtendAction(int32_t action) override;
    bool BeforeStatusCursorMove(bool isLeft);
    bool CursorMoveLeft();
    bool CursorMoveRight();
    bool CursorMoveUp();
    bool CursorMoveDown();
    void CursorMoveToNextWord(CaretMoveIntent direction);
    int32_t GetLeftWordIndex(int32_t index);
    int32_t GetRightWordIndex(int32_t index);
    bool CursorMoveToParagraphBegin();
    bool CursorMoveToParagraphEnd();
    bool CursorMoveHome();
    bool CursorMoveEnd();
    void CalcLineSidesIndexByPosition(int32_t& startIndex, int32_t& endIndex);
    RectF CalcLineInfoByPosition();
    CaretOffsetInfo GetCaretOffsetInfoByPosition(int32_t position = -1);
    int32_t CalcMoveUpPos(float& leadingMarginOffset);
    int32_t CalcMoveDownPos(float& leadingMarginOffset);
    int32_t CalcLineBeginPosition();
    float GetTextThemeFontSize();
    int32_t CalcLineEndPosition(int32_t index = -1);
    int32_t CalcSingleLineBeginPosition(int32_t fixedPos);
    int32_t CalcSingleLineEndPosition(int32_t fixedPos);
    bool CursorMoveLineBegin();
    bool CursorMoveLineEnd();
    void HandleSelectFontStyle(KeyCode code) override;
    void HandleSelectFontStyleWrapper(KeyCode code, TextStyle& spanStyle);
    void HandleOnShowMenu() override;
    int32_t HandleKbVerticalSelection(bool isUp);
    int32_t HandleSelectParagraghPos(bool direction);
    PositionType GetPositionTypeFromLine();
    int32_t HandleSelectWrapper(CaretMoveIntent direction, int32_t fixedPos);
    void AIDeleteComb(int32_t start, int32_t end, int32_t& aiPosition, bool direction);
    bool HandleOnDeleteComb(bool backward) override;
    void DeleteBackwardWord();
    void DeleteForwardWord();
    int32_t GetLeftWordPosition(int32_t caretPosition);
    int32_t GetRightWordPosition(int32_t caretPosition);
    int32_t GetParagraphBeginPosition(int32_t caretPosition);
    int32_t GetParagraphEndPosition(int32_t caretPosition);
    int32_t CaretPositionSelectEmoji(CaretMoveIntent direction);
    void HandleSelect(CaretMoveIntent direction) override;
    void SetCaretPositionWithAffinity(PositionWithAffinity positionWithAffinity);
    bool SetCaretPosition(int32_t pos, bool needNotifyImf = true);
    int32_t GetCaretPosition();
    int32_t GetTextContentLength() override;
    bool GetCaretVisible() const;
    OffsetF CalcCursorOffsetByPosition(int32_t position, float& selectLineHeight,
        bool downStreamFirst = false, bool needLineHighest = true);
    void HandleCurrentPositionParagraphInfo(float& lastLineTop, float& paragraphSpacing);
    bool IsCustomSpanInCaretPos(int32_t position, bool downStreamFirst);
    void CopyTextSpanStyle(RefPtr<SpanNode>& source, RefPtr<SpanNode>& target, bool needLeadingMargin = false);
    void CopyTextSpanFontStyle(RefPtr<SpanNode>& source, RefPtr<SpanNode>& target);
    void CopyTextSpanLineStyle(RefPtr<SpanNode>& source, RefPtr<SpanNode>& target, bool needLeadingMargin = false);
    void CopyTextSpanUrlStyle(RefPtr<SpanNode>& source, RefPtr<SpanNode>& target);
    void CopyGestureOption(const RefPtr<SpanNode>& source, RefPtr<SpanNode>& target);
    int32_t TextSpanSplit(int32_t position, bool needLeadingMargin = false);
    SpanPositionInfo GetSpanPositionInfo(int32_t position);
    std::function<ImageSourceInfo()> CreateImageSourceInfo(const ImageSpanOptions& options);
    void DeleteSpans(const RangeOptions& options);
    void DeleteSpansOperation(int32_t start, int32_t end);
    void DeleteSpanByRange(int32_t start, int32_t end, SpanPositionInfo info);
    void DeleteSpansByRange(int32_t start, int32_t end, SpanPositionInfo startInfo, SpanPositionInfo endInfo);
    void ClearContent(const RefPtr<UINode>& child);
    void CloseSelectionMenu();
    bool SetCaretOffset(int32_t caretPosition) override;
    bool DoDeleteActions(int32_t currentPosition, int32_t length, RichEditorDeleteValue& info);

    void UpdateSpanStyle(int32_t start, int32_t end, const TextStyle& textStyle, const ImageSpanAttribute& imageStyle);
    void GetContentBySpans(std::u16string& u16Str);
    void SetSelectSpanStyle(int32_t start, int32_t end, KeyCode code, bool isStart);
    void GetSelectSpansPositionInfo(
        int32_t& start, int32_t& end, SpanPositionInfo& startPositionSpanInfo, SpanPositionInfo& endPositionSpanInfo);
    std::list<RefPtr<UINode>>::const_iterator GetSpanNodeIter(int32_t index);
    std::list<SpanPosition> GetSelectSpanSplit(
        SpanPositionInfo& startPositionSpanInfo, SpanPositionInfo& endPositionSpanInfo);
    std::list<SpanPosition> GetSelectSpanInfo(int32_t start, int32_t end);
    SelectionInfo GetSpansInfoByRange(int32_t start, int32_t end);
    void UpdateSelectSpanStyle(int32_t start, int32_t end, KeyCode code);
    bool CheckStyledStringRangeValid(int32_t start, int32_t length);
    void UpdateSelectStyledStringStyle(int32_t start, int32_t end, KeyCode code);
    template<typename T>
    void UpdateSpansStyleInRange(int32_t start, int32_t end, const RefPtr<SpanBase>& baseSpan,
        std::function<RefPtr<T>(const RefPtr<T>&)>&& updateSpanFunc);
    void UpdateStyledStringFontStyle(int32_t start, int32_t end, const Font& font);
    void UpdateStyledStringDecorationType(int32_t start, int32_t end, const TextDecoration& type);
    bool SymbolSpanUpdateStyle(RefPtr<SpanNode>& spanNode, struct UpdateSpanStyle updateSpanStyle, TextStyle textStyle);
    void SetUpdateSpanStyle(struct UpdateSpanStyle updateSpanStyle);
    struct UpdateSpanStyle GetUpdateSpanStyle();
    void UpdateParagraphStyle(int32_t start, int32_t end, const struct UpdateParagraphStyle& style);
    void UpdateParagraphStyle(RefPtr<SpanNode> spanNode, const struct UpdateParagraphStyle& style);
    std::vector<ParagraphInfo> GetParagraphInfo(int32_t start, int32_t end);
    void SetTypingStyle(std::optional<struct UpdateSpanStyle> typingStyle, std::optional<TextStyle> textStyle);
    std::optional<struct UpdateSpanStyle> GetTypingStyle();
    int32_t AddImageSpan(const ImageSpanOptions& options, bool isPaste = false, int32_t index = -1,
        bool updateCaret = true);
    int32_t AddTextSpan(TextSpanOptions options, bool isPaste = false, int32_t index = -1);
    int32_t AddTextSpanOperation(const TextSpanOptions& options, bool isPaste = false, int32_t index = -1,
        bool needLeadingMargin = false, bool updateCaretPosition = true);
    void AdjustAddPosition(TextSpanOptions& options);
    int32_t AddSymbolSpan(SymbolSpanOptions options, bool isPaste = false, int32_t index = -1);
    int32_t AddSymbolSpanOperation(const SymbolSpanOptions& options, bool isPaste = false, int32_t index = -1);
    void AddSpanItem(const RefPtr<SpanItem>& item, int32_t offset);
    int32_t AddPlaceholderSpan(const RefPtr<UINode>& customNode, const SpanOptionBase& options);
    void AddOnPlaceholderHoverEvent(const RefPtr<PlaceholderSpanNode>& placeholderSpanNode);
    void OnPlaceholderHover(bool isHover);
    void SetSelection(int32_t start, int32_t end, const std::optional<SelectionOptions>& options = std::nullopt,
        bool isForward = false) override;
    bool ResetOnInvalidSelection(int32_t start, int32_t end);
    bool IsShowHandle();
    void UpdateSelectionInfo(int32_t start, int32_t end);
    bool IsEditing();
    std::u16string GetLeftTextOfCursor(int32_t number) override;
    std::u16string GetRightTextOfCursor(int32_t number) override;
    int32_t GetTextIndexAtCursor() override;
    void ShowSelectOverlay(const RectF& firstHandle, const RectF& secondHandle, bool isCopyAll = false,
        TextResponseType responseType = TextResponseType::LONG_PRESS, bool handlReverse = false);
    void CheckEditorTypeChange();
    int32_t GetHandleIndex(const Offset& offset) const override;
    void OnAreaChangedInner() override;
    void UpdateParentOffsetAndOverlay();
    void OnParentOffsetChange();
    void CreateHandles() override;
    void ShowHandles(const bool isNeedShowHandles) override;
    void ShowHandles() override;
    void HandleMenuCallbackOnSelectAll(bool isShowMenu = true);
    void HandleOnSelectAll() override;
    void OnCopyOperation(bool isUsingExternalKeyboard = false);
    void HandleOnCopy(bool isUsingExternalKeyboard = false) override;
    void HandleOnShare();
    void HandleDraggableFlag(bool isTouchSelectArea);
    void SetIsTextDraggable(bool isTextDraggable = true) override;
    bool JudgeContentDraggable();
    std::pair<OffsetF, float> CalculateCaretOffsetAndHeight();
    std::pair<OffsetF, float> CalculateEmptyValueCaretRect();
    void UpdateModifierCaretOffsetAndHeight();
    void NotifyCaretChange();
    TextAlign GetTextAlignByDirection();
    void RemoveEmptySpan(std::set<int32_t, std::greater<int32_t>>& deleteSpanIndexs);
    void RemoveEmptySpanItems();
    void RemoveEmptySpanNodes();
    void RemoveEmptySpans();
    RefPtr<GestureEventHub> GetGestureEventHub();
    void OnWindowHide() override;
    bool BeforeAddImage(RichEditorChangeValue& changeValue, const ImageSpanOptions& options, int32_t insertIndex);
    RefPtr<SpanString> ToStyledString(int32_t start, int32_t end);
    SelectionInfo FromStyledString(const RefPtr<SpanString>& spanString);
    bool BeforeAddSymbol(RichEditorChangeValue& changeValue, const SymbolSpanOptions& options);
    void AfterContentChange(RichEditorChangeValue& changeValue);
    void DeleteToMaxLength(std::optional<int32_t> length);
    void DeleteContent(int32_t length);

    void ResetIsMousePressed()
    {
        isMousePressed_ = false;
    }

    OffsetF GetSelectionMenuOffset() const
    {
        return selectionMenuOffsetByMouse_;
    }

    void SetLastClickOffset(const OffsetF& lastClickOffset)
    {
        lastClickOffset_ = lastClickOffset;
    }

    void ResetLastClickOffset()
    {
        lastClickOffset_.SetX(-1);
        lastClickOffset_.SetY(-1);
    }

    int32_t GetCaretSpanIndex()
    {
        return caretSpanIndex_;
    }

    std::vector<ParagraphManager::ParagraphInfo> GetParagraphs() const override
    {
        return paragraphs_.GetParagraphs();
    }

    std::optional<SelectHandleInfo> GetFirstHandleInfo() const
    {
        return selectOverlay_->GetFirstHandleInfo();
    }

    std::optional<SelectHandleInfo> GetSecondHandleInfo() const
    {
        return selectOverlay_->GetSecondHandleInfo();
    }

    RectF GetCaretRect() const override;
    void OnDragNodeFloating() override;
    void CloseSelectOverlay() override;
    void CloseHandleAndSelect() override;
    void CalculateHandleOffsetAndShowOverlay(bool isUsingMouse = false);
    void CalculateDefaultHandleHeight(float& height) override;
    bool IsSingleHandle();
    bool IsHandlesShow() override;
    void CopySelectionMenuParams(SelectOverlayInfo& selectInfo, TextResponseType responseType);
    std::function<void(Offset)> GetThumbnailCallback() override;
    void CreateDragNode();
    float GetMaxSelectedWidth();
    void InitDragShadow(const RefPtr<FrameNode>& host, const RefPtr<FrameNode>& dragNode, bool isDragShadowNeeded,
        bool hasDragBackgroundColor);
    void HandleOnDragStatusCallback(
        const DragEventType& dragEventType, const RefPtr<NotifyDragEvent>& notifyDragEvent) override;
    void ResetSelection();
    bool BetweenSelection(const Offset& globalOffset);
    bool InRangeRect(const Offset& globalOffset, const std::pair<int32_t, int32_t>& range);
    bool BetweenSelectedPosition(const Offset& globalOffset) override;
    void HandleSurfaceChanged(int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight,
        WindowSizeChangeReason type) override;
    void HandleSurfacePositionChanged(int32_t posX, int32_t posY) override;
    bool RequestCustomKeyboard();
    bool CloseCustomKeyboard();
    void UpdateUrlStyle(RefPtr<SpanNode>& spanNode, const std::optional<std::u16string>& urlAddressOpt);
    const std::u16string& GetPasteStr() const
    {
        return pasteStr_;
    }
    void AddPasteStr(const std::string& addedStr)
    {
        pasteStr_.append(UtfUtils::Str8ToStr16(addedStr));
    }
    void ClearPasteStr()
    {
        pasteStr_.clear();
    }
    void SetCustomKeyboard(const std::function<void()>&& keyboardBuilder)
    {
        if (customKeyboardBuilder_ && isCustomKeyboardAttached_ && !keyboardBuilder) {
            // close customKeyboard and request system keyboard
            CloseCustomKeyboard();
            customKeyboardBuilder_ = keyboardBuilder; // refresh current keyboard
            RequestKeyboard(false, true, true);
            return;
        }
        if (!customKeyboardBuilder_ && keyboardBuilder) {
            // close system keyboard and request custom keyboard
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
            if (isEditing_) {
                CloseKeyboard(true);
                customKeyboardBuilder_ = keyboardBuilder; // refresh current keyboard
                RequestKeyboard(false, true, true);
                return;
            }
#endif
        }
        customKeyboardBuilder_ = keyboardBuilder;
    }
    void BindSelectionMenu(TextResponseType type, TextSpanType richEditorType, std::function<void()>& menuBuilder,
        const SelectMenuParam& menuParam);
    void ClearSelectionMenu()
    {
        selectionMenuMap_.clear();
    }
    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) override {}
    void RichEditorErrorReport(RichEditorInfo& info);
    void MouseDoubleClickParagraphEnd(int32_t& index);
    void AdjustSelectionExcludeSymbol(int32_t& start, int32_t& end);
    void InitSelection(const Offset& pos);
    bool HasFocus() const;
    void OnColorConfigurationUpdate() override;
    bool OnThemeScopeUpdate(int32_t themeScopeId) override;
    void OnCommonColorChange();
    bool IsDisabled() const;
    float GetLineHeight() const override;
    size_t GetLineCount() const override;
    std::vector<ParagraphManager::TextBox> GetRectsForRange(int32_t start, int32_t end,
        RectHeightStyle heightStyle, RectWidthStyle widthStyle) override;
    TextLineMetrics GetLineMetrics(int32_t lineNumber) override;
    float GetLetterSpacing() const;
    std::vector<RectF> GetTextBoxes() override;
    bool OnBackPressed() override;

    RectF GetCaretRelativeRect();
    // Add for Scroll

    void OnAttachToFrameNode() override;

    void OnDetachFromFrameNode(FrameNode* node) override;

    bool IsAtBottom(bool considerRepeat = false) const override
    {
        return true;
    }

    bool IsAtTop() const override
    {
        return true;
    }

    bool UpdateCurrentOffset(float offset, int32_t source) override
    {
        return true;
    }

    const RectF& GetTextRect() override
    {
        return richTextRect_;
    }

    float GetScrollOffset() const
    {
        return scrollOffset_;
    }

    RefPtr<ScrollBar> GetScrollControllerBar()
    {
        return GetScrollBar();
    }

    bool OnScrollCallback(float offset, int32_t source) override;
    void OnScrollEndCallback() override;
    bool IsScrollable() const override
    {
        return scrollable_;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    bool IsShowSelectMenuUsingMouse();

    bool IsShowPlaceholder() const
    {
        return isShowPlaceholder_;
    }

    bool IsSelectAreaVisible();

    bool SetPlaceholder(std::vector<std::list<RefPtr<SpanItem>>>& spanItemList);

    std::string GetPlaceHolder() const;

    void HandleOnCameraInput() override;
    void HandleOnAIWrite();
    void GetAIWriteInfo(AIWriteInfo& info);
    void HandleAIWriteResult(int32_t start, int32_t end, std::vector<uint8_t>& buffer);
    void InsertSpanByBackData(RefPtr<SpanString>& spanString);
    void AddSpansAndReplacePlaceholder(RefPtr<SpanString>& spanString);
    void ReplacePlaceholderWithRawSpans(const RefPtr<SpanItem>& spanItem, size_t& index, size_t& textIndex);
    void SetSubSpansWithAIWrite(RefPtr<SpanString>& spanString, int32_t start, int32_t end);
    SymbolSpanOptions GetSymbolSpanOptions(const RefPtr<SpanItem>& spanItem);
    bool IsShowTranslate();
    bool IsShowSearch();
    bool IsShowAIWrite();
    RefPtr<FocusHub> GetFocusHub() const;
    void ResetDragOption() override;
    bool NeedShowAIDetect() override;

    TextSpanType GetEditorType() const
    {
        return selectedType_.value_or(TextSpanType::NONE);
    }
    void GetCaretMetrics(CaretMetricsF& caretCaretMetric) override;

    void SetShowSelect(bool isShowSelect)
    {
        showSelect_ = isShowSelect;
    }

    const std::list<RefPtr<UINode>>& GetAllChildren() const override;

    void OnVirtualKeyboardAreaChanged() override;

    void SetCaretColor(const Color& caretColor)
    {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "setCaretColor=%{public}s", caretColor.ToString().c_str());
        caretColor_ = caretColor;
        IF_TRUE(SelectOverlayIsOn(), selectOverlay_->UpdateHandleColor());
    }

    Color GetCaretColor();

    void SetSelectedBackgroundColor(const Color& selectedBackgroundColor)
    {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "SetSelectedBackgroundColor=%{public}s",
            selectedBackgroundColor.ToString().c_str());
        selectedBackgroundColor_ = selectedBackgroundColor;
    }

    Color GetSelectedBackgroundColor();

    void SetCustomKeyboardOption(bool supportAvoidance);
    void StopEditing();
    void ResetKeyboardIfNeed();

    void HandleOnEnter() override
    {
        PerformAction(GetTextInputActionValue(GetDefaultTextInputAction()), false);
    }

    RefPtr<Clipboard> GetClipboard() override
    {
        return clipboard_;
    }

    int32_t GetCaretIndex() const override
    {
        return caretPosition_;
    }

    int32_t GetContentWideTextLength() override
    {
        return GetTextContentLength();
    }

    OffsetF GetParentGlobalOffset() const override
    {
        return parentGlobalOffset_;
    }

    OffsetF GetFirstHandleOffset() const override
    {
        return textSelector_.firstHandle.GetOffset();
    }

    OffsetF GetSecondHandleOffset() const override
    {
        return textSelector_.secondHandle.GetOffset();
    }

    OffsetF GetTextPaintOffset() const override;
    OffsetF GetPaintRectGlobalOffset() const;
    // original local point to transformed global point.
    void HandlePointWithTransform(OffsetF& point);

    float GetCrossOverHeight() const;

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<RichEditorAccessibilityProperty>();
    }

    void AdjustSelector(int32_t& index, HandleType handleType,
        SelectorAdjustPolicy policy = SelectorAdjustPolicy::INCLUDE);
    void AdjustSelector(int32_t& start, int32_t& end, SelectorAdjustPolicy policy = SelectorAdjustPolicy::INCLUDE);
    bool AdjustSelectorForSymbol(int32_t& index, HandleType handleType, SelectorAdjustPolicy policy);
    bool AdjustSelectorForEmoji(int32_t& index, HandleType handleType, SelectorAdjustPolicy policy);
    EmojiRelation GetEmojiRelation(int index);
    void UpdateSelector(int32_t start, int32_t end);
    void UpdateSelectionType(const SelectionInfo& textSelectInfo);
    std::list<RefPtr<SpanItem>>::iterator GetSpanIter(int32_t index);
    SpanItemType GetSpanType(int32_t index);

    void DumpAdvanceInfo() override {}
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override  {}

    void SetContentChange(bool onChange)
    {
        contentChange_ = onChange;
    }

    void HideMenu();
    PositionWithAffinity GetGlyphPositionAtCoordinate(int32_t x, int32_t y) override;
    void OnSelectionMenuOptionsUpdate(
        const NG::OnCreateMenuCallback&& onCreateMenuCallback, const NG::OnMenuItemClickCallback&& onMenuItemClick);
    RectF GetTextContentRect(bool isActualText = false) const override
    {
        return contentRect_;
    }

    void PreferredParagraph();

    const RefPtr<Paragraph>& GetPresetParagraph()
    {
        return presetParagraph_;
    }

    void OnFrameNodeChanged(FrameNodeChangeInfoFlag flag) override
    {
        selectOverlay_->OnAncestorNodeChanged(flag);
    }

    bool IsResponseRegionExpandingNeededForStylus(const TouchEvent& touchEvent) const override;

    RectF ExpandDefaultResponseRegion(RectF& rect) override;
    bool ConsumeChildrenAdjustment(const OffsetF& /* offset */) override
    {
        return true;
    }

    TextStyle GetDefaultTextStyle();
    void SetEnableHapticFeedback(bool isEnabled)
    {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "setEnableHapticFeedback=%{public}d", isEnabled);
        isEnableHapticFeedback_ = isEnabled;
    }

    bool InsertOrDeleteSpace(int32_t index) override;

    void DeleteRange(int32_t start, int32_t end, bool isIME = true) override;
    void HandleOnPageUp() override;
    void HandleOnPageDown() override;
    void HandlePageScroll(bool isPageUp);

    void SetRequestKeyboardOnFocus(bool needToRequest)
    {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "SetRequestKeyboardOnFocus=%{public}d", needToRequest);
        needToRequestKeyboardOnFocus_ = needToRequest;
    }

    bool IsTextEditableForStylus() const override;

    NG::DragDropInfo HandleDragStart(const RefPtr<Ace::DragEvent>& event, const std::string& extraParams);

    void SetPreviewMenuParam(TextSpanType spanType, std::function<void()>& builder, const SelectMenuParam& menuParam);

    void RequestFocusWhenSelected()
    {
        CHECK_NULL_VOID(!HasFocus());
        CHECK_NULL_VOID(IsSelected());
        auto focusHub = GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        isOnlyRequestFocus_ = true;
        IF_TRUE(!focusHub->RequestFocusImmediately(), isOnlyRequestFocus_ = false);
    }

    DisplayMode GetBarDisplayMode() const
    {
        return barDisplayMode_.value_or(DisplayMode::AUTO);
    }

    Color GetUrlSpanColor() override;

    void TriggerAvoidOnCaretChange();

    void ForceTriggerAvoidOnCaretChange(bool isMoveContent = false)
    {
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline && pipeline->UsingCaretAvoidMode());
        IF_TRUE(isMoveContent, MoveCaretToContentRect());
        isTriggerAvoidOnCaretAvoidMode_ = true;
    }

    void TriggerAvoidOnCaretChangeNextFrame()
    {
        ForceTriggerAvoidOnCaretChange(true);
        isTriggerAvoidOnCaretAvoidMode_ = false;
        UpdateModifierCaretOffsetAndHeight();
        TriggerAvoidOnCaretChange();
    }

    void ResetTriggerAvoidFlagOnCaretChange()
    {
        isTriggerAvoidOnCaretAvoidMode_ = false;
    }

    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;

    bool IsTriggerAvoidOnCaretAvoidMode()
    {
        return isTriggerAvoidOnCaretAvoidMode_;
    }

    void SetAvoidFlagOnCaretAvoidMode(bool isTriggerAvoidOnCaretAvoidMode)
    {
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline && pipeline->UsingCaretAvoidMode());
        isTriggerAvoidOnCaretAvoidMode_ = isTriggerAvoidOnCaretAvoidMode;
    }

    void ChangeLastRichTextRect()
    {
        lastRichTextRect_ = richTextRect_;
    }

    const RectF& GetLastTextRect()
    {
        return lastRichTextRect_;
    }
    HoverInfo CreateHoverInfo(const MouseInfo& info);
    std::pair<int32_t, int32_t> GetSpanRangeByLocalOffset(Offset localOffset);
    void SetStopBackPress(bool isStopBackPress)
    {
        isStopBackPress_ = isStopBackPress;
    }

    bool IsStopBackPress() const override
    {
        return isStopBackPress_;
    }

    void SetKeyboardAppearance(KeyboardAppearance value)
    {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "SetKeyboardAppearance=%{public}d", value);
        keyboardAppearance_ = value;
    }

    KeyboardAppearance GetKeyboardAppearance() const
    {
        return keyboardAppearance_;
    }

    bool IsDragging() const override
    {
        return status_ == Status::DRAGGING || status_ == Status::FLOATING;
    }

    const RefPtr<SpanItem> GetSpanItemByPosition(int32_t position)
    {
        CHECK_NULL_RETURN(position >= 0, nullptr);
        auto it = GetSpanIter(position);
        CHECK_NULL_RETURN(it != spans_.end(), nullptr);
        return *it;
    }

    ColorMode GetColorMode()
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(!host, host->GetLocalColorMode());
        auto context = GetContext();
        CHECK_NULL_RETURN(context, ColorMode::COLOR_MODE_UNDEFINED);
        return context->GetLocalColorMode();
    }

    ColorMode GetDisplayColorMode()
    {
        auto colorMode = GetColorMode();
        return colorMode == ColorMode::COLOR_MODE_UNDEFINED ? Container::CurrentColorMode() : colorMode;
    }

    template<typename T>
    RefPtr<T> GetTheme()
    {
        auto pipelineContext = GetContext();
        CHECK_NULL_RETURN(pipelineContext, {});
        if (isAPI20Plus) {
            return pipelineContext->GetTheme<T>(GetThemeScopeId());
        }
        return pipelineContext->GetTheme<T>();
    }

    const std::map<int32_t, AISpan>& GetAISpanMap() override
    {
        auto& aiSpanMap = dataDetectorAdapter_->aiSpanMap_;
        if (aiSpanMap != lastAISpanMap_) {
            paragraphCache_.Clear();
            lastAISpanMap_ = aiSpanMap;
        }
        return aiSpanMap;
    }

    void SetTextDetectEnable(bool enable) override
    {
        auto currentEnable = textDetectEnable_;
        TextPattern::SetTextDetectEnable(enable);
        CHECK_NULL_VOID(enable && !currentEnable && CanStartAITask());
        IF_TRUE(!dataDetectorAdapter_->aiDetectInitialized_, dataDetectorAdapter_->StartAITask());
    }

protected:
    bool CanStartAITask() override;
    std::vector<RectF> GetSelectedRects(int32_t start, int32_t end) override;
    PointF GetTextOffset(const Offset& localLocation, const RectF& contentRect) override;
    std::pair<int32_t, int32_t> GetStartAndEnd(int32_t start, const RefPtr<SpanItem>& spanItem) override;

private:
    friend class RichEditorSelectOverlay;
    friend class OneStepDragController;
    friend class RichEditorUndoManager;
    bool HandleUrlSpanClickEvent(const GestureEvent& info);
    void HandleUrlSpanForegroundClear();
    bool HandleUrlSpanShowShadow(const Offset& localLocation, const Offset& globalOffset, const Color& color);
    Color GetUrlHoverColor();
    Color GetUrlPressColor();
    RefPtr<RichEditorSelectOverlay> selectOverlay_;
    Offset ConvertGlobalToLocalOffset(const Offset& globalOffset);
    void UpdateSelectMenuInfo(SelectMenuInfo& selectInfo);
    void HandleOnPaste() override;
    void PasteStr(const std::string& text);
    void HandleOnCut() override;
    void InitClickEvent(const RefPtr<GestureEventHub>& gestureHub) override;
    void InitFocusEvent(const RefPtr<FocusHub>& focusHub);
    void HandleBlurEvent();
    void HandleFocusEvent();
    void OnFocusNodeChange(FocusReason focusReason) override;
    void HandleClickEvent(GestureEvent& info);
    void HandleSingleClickEvent(GestureEvent& info);
    bool HandleClickSelection(const OHOS::Ace::GestureEvent& info);
    bool IsClickEventOnlyForMenuToggle(const OHOS::Ace::GestureEvent& info);
    Offset ConvertTouchOffsetToTextOffset(const Offset& touchOffset);
    bool IsShowSingleHandleByClick(const OHOS::Ace::GestureEvent& info, int32_t lastCaretPosition,
        const RectF& lastCaretRect, bool isCaretTwinkling);
    bool RepeatClickCaret(const Offset& offset, const RectF& lastCaretRect);
    void CreateAndShowSingleHandle();
    void MoveCaretAndStartFocus(const Offset& offset);
    void HandleDoubleClickEvent(GestureEvent& info);
    bool HandleUserClickEvent(GestureEvent& info);
    bool HandleUserLongPressEvent(GestureEvent& info);
    bool HandleUserDoubleClickEvent(GestureEvent& info);
    bool HandleUserGestureEvent(
        GestureEvent& info, std::function<bool(RefPtr<SpanItem> item, GestureEvent& info)>&& gestureFunc);
    void CalcCaretInfoByClick(const Offset& touchOffset);
    std::pair<OffsetF, float> CalcAndRecordLastClickCaretInfo(const Offset& textOffset);
    void HandleEnabled();
    void HandleAISpanHoverEvent(const MouseInfo& info) override;
    void InitMouseEvent();
    void ScheduleCaretTwinkling();
    void OnCaretTwinkling();
    void StartTwinkling();
    void ShowCaretWithoutTwinkling();
    void StopTwinkling();
    void UpdateFontFeatureTextStyle(
        RefPtr<SpanNode>& spanNode, struct UpdateSpanStyle& updateSpanStyle, TextStyle& textStyle);
    void UpdateDecoration(RefPtr<SpanNode>& spanNode, struct UpdateSpanStyle& updateSpanStyle, TextStyle& textStyle);
    void UpdateTextStyle(RefPtr<SpanNode>& spanNode, struct UpdateSpanStyle updateSpanStyle, TextStyle textStyle);
    void UpdateSymbolStyle(RefPtr<SpanNode>& spanNode, struct UpdateSpanStyle updateSpanStyle, TextStyle textStyle);
    void UpdateImageStyle(RefPtr<FrameNode>& imageNode, const ImageSpanAttribute& imageStyle);
    void UpdateImageAttribute(RefPtr<FrameNode>& imageNode, const ImageSpanAttribute& imageStyle);
    TextStyle CreateTextStyleByTypingStyle();
    void InitTouchEvent();
    void InitPanEvent();
    bool SelectOverlayIsOn();
    void HandleLongPress(GestureEvent& info);
    void HandleDoubleClickOrLongPress(GestureEvent& info);
    void HandleDoubleClickOrLongPress(GestureEvent& info, RefPtr<FrameNode> host);
    void StartVibratorByLongPress();
    std::string GetPositionSpansText(int32_t position, int32_t& startSpan);
    void FireOnSelect(int32_t selectStart, int32_t selectEnd);
    void FireOnSelectionChange(const int32_t caretPosition);
    void FireOnSelectionChange(const TextSelector& selector);
    void FireOnSelectionChange(int32_t selectStart, int32_t selectEnd, bool isForced = false);
    void MouseRightFocus(const MouseInfo& info);
    bool IsScrollBarPressed(const MouseInfo& info);
    void HandleMouseLeftButtonMove(const MouseInfo& info);
    void HandleMouseSelect(const Offset& localOffset);
    void HandleMouseLeftButtonPress(const MouseInfo& info);
    void HandleShiftSelect(int32_t position);
    void HandleMouseLeftButtonRelease(const MouseInfo& info);
    void HandleMouseLeftButton(const MouseInfo& info);
    void HandleMouseRightButton(const MouseInfo& info);
    void HandleMouseEvent(const MouseInfo& info);
    void HandleImageHoverEvent(const MouseInfo& info);
    void HandleTouchEvent(const TouchEventInfo& info);
    std::optional<TouchLocationInfo> GetAcceptedTouchLocationInfo(const TouchEventInfo& info);
    void HandleTouchDown(const TouchLocationInfo& info);
    void HandleTouchUp();
    void StartFloatingCaretLand();
    void ResetTouchAndMoveCaretState();
    void ResetTouchSelectState();
    void HandleTouchUpAfterLongPress();
    void HandleTouchCancelAfterLongPress();
    void HandleTouchMove(const TouchLocationInfo& info);
    void OnMoveCaretStart(int32_t fingerId);
    void UpdateCaretByTouchMove(const Offset& offset);
    void SetCaretTouchMoveOffset(const Offset& localOffset);
    RectF GetCaretBoundaryRect();
    Offset AdjustLocalOffsetOnMoveEvent(const Offset& originalOffset);
    void StartVibratorByIndexChange(int32_t currentIndex, int32_t preIndex);
    void InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub);
    void UseHostToUpdateTextFieldManager();
    void UpdateTextFieldManager(const Offset& offset, float height);
    void ScrollToSafeArea() const override;
    void InitDragDropEvent();
    void OnDragStartAndEnd();
    void onDragDropAndLeave();
    void ClearDragDropEvent();
    void OnDragMove(const RefPtr<OHOS::Ace::DragEvent>& event);
    void OnDragEnd(const RefPtr<Ace::DragEvent>& event);
    void ResetDragSpanItems();
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    std::string GetPlaceHolderInJson() const;
    std::string GetTextColorInJson(const std::optional<Color>& value) const;
    void FillPreviewMenuInJson(const std::unique_ptr<JsonValue>& jsonValue) const override;
    void ResetSelectionAfterAddSpan(bool isPaste);
    RefPtr<UINode> GetChildByIndex(int32_t index) const override;
    void SetResultObjectText(ResultObject& resultObject, const RefPtr<SpanItem>& spanItem) override;
    SelectionInfo GetAdjustedSelectionInfo(const SelectionInfo& textSelectInfo);
    void ResetAfterTextChange() override {};
    void AddOprationWhenAddImage(int32_t beforeCaretPos);
    void UpdateSpanNode(RefPtr<SpanNode> spanNode, const TextSpanOptions& options);
    void UpdateTextBackgroundStyle(RefPtr<SpanNode>& spanNode, const std::optional<TextBackgroundStyle>& style);
    void InitPlaceholderSpansMap(
        RefPtr<SpanItem>& newSpanItem, const RefPtr<SpanItem>& spanItem, size_t& index, size_t& placeholderGains);
    void ReplacePlaceholderWithCustomSpan(const RefPtr<SpanItem>& spanItem, size_t& index, size_t& textIndex);
    void ReplacePlaceholderWithSymbolSpan(const RefPtr<SpanItem>& spanItem, size_t& index, size_t& textIndex);
    void ReplacePlaceholderWithImageSpan(const RefPtr<SpanItem>& spanItem, size_t& index, size_t& textIndex);
    void AddDragFrameNodeToManager(const RefPtr<FrameNode>& frameNode)
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto dragDropManager = context->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        dragDropManager->AddDragFrameNode(frameNode->GetId(), AceType::WeakClaim(AceType::RawPtr(frameNode)));
    }

    void RemoveDragFrameNodeFromManager(const RefPtr<FrameNode>& frameNode)
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto dragDropManager = context->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        dragDropManager->RemoveDragFrameNode(frameNode->GetId());
    }

    void HandleCursorOnDragMoved(const RefPtr<NotifyDragEvent>& notifyDragEvent);
    void HandleCursorOnDragLeaved(const RefPtr<NotifyDragEvent>& notifyDragEvent);
    void HandleCursorOnDragEnded(const RefPtr<NotifyDragEvent>& notifyDragEvent);

    int32_t GetParagraphLength(const std::list<RefPtr<UINode>>& spans) const;
    // REQUIRES: 0 <= start < end
    std::vector<RefPtr<SpanNode>> GetParagraphNodes(int32_t start, int32_t end) const;
    void OnHover(bool isHover);
    void ChangeMouseStyle(MouseFormat format, bool freeMouseHoldNode = false);
    bool RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard,
        SourceType sourceType = SourceType::NONE);
    void UpdateCaretInfoToController();
#if defined(ENABLE_STANDARD_INPUT)
    bool EnableStandardInput(bool needShowSoftKeyboard, SourceType sourceType = SourceType::NONE);
    std::optional<MiscServices::TextConfig> GetMiscTextConfig();
#else
    bool UnableStandardInput(bool isFocusViewChanged);
#endif

    bool HasConnection() const;
    bool CloseKeyboard(bool forceClose) override;
    void CalcInsertValueObj(TextInsertValueInfo& info);
    void CalcDeleteValueObj(int32_t currentPosition, int32_t length, RichEditorDeleteValue& info);
    RefPtr<SpanNode> GetSpanNodeBySpanItem(const RefPtr<SpanItem> spanItem);
    int32_t DeleteValueSetBuilderSpan(const RefPtr<SpanItem>& spanItem, RichEditorAbstractSpanResult& spanResult);
    int32_t DeleteValueSetImageSpan(const RefPtr<SpanItem>& spanItem, RichEditorAbstractSpanResult& spanResult);
    int32_t DeleteValueSetSymbolSpan(const RefPtr<SpanItem>& spanItem, RichEditorAbstractSpanResult& spanResult);
    int32_t DeleteValueSetTextSpan(const RefPtr<SpanItem>& spanItem, int32_t currentPosition, int32_t length,
        RichEditorAbstractSpanResult& spanResult);
    void DeleteByDeleteValueInfo(const RichEditorDeleteValue& info);
    int32_t ProcessDeleteNodes(std::list<RichEditorAbstractSpanResult>& deleteSpans);
    bool OnKeyEvent(const KeyEvent& keyEvent);
    void MoveCaretAfterTextChange();
    bool BeforeIMEInsertValue(const std::u16string& insertValue);
    void AfterInsertValue(
        const RefPtr<SpanNode>& spanNode, int32_t insertValueLength, bool isCreate, bool isIme = true);
    bool AfterIMEInsertValue(const RefPtr<SpanNode>& spanNode, int32_t moveLength, bool isCreate);
    RefPtr<SpanNode> InsertValueToBeforeSpan(RefPtr<SpanNode>& spanNodeBefore, const std::u16string& insertValue);
    void SetCaretSpanIndex(int32_t index);
    bool HasSameTypingStyle(const RefPtr<SpanNode>& spanNode);

    void GetChangeSpanStyle(RichEditorChangeValue& changeValue, std::optional<TextStyle>& spanTextStyle,
        std::optional<struct UpdateParagraphStyle>& spanParaStyle, std::optional<std::u16string>& urlAddress,
        const RefPtr<SpanNode>& spanNode, int32_t spanIndex);
    void GetReplacedSpan(RichEditorChangeValue& changeValue, int32_t& innerPosition, const std::u16string& insertValue,
        int32_t textIndex, std::optional<TextStyle> textStyle, std::optional<struct UpdateParagraphStyle> paraStyle,
        std::optional<std::u16string> urlAddress = std::nullopt, bool isCreate = false, bool fixDel = true);
    void GetReplacedSpanFission(RichEditorChangeValue& changeValue, int32_t& innerPosition, std::u16string& content,
        int32_t startSpanIndex, int32_t offsetInSpan, std::optional<TextStyle> textStyle,
        std::optional<struct UpdateParagraphStyle> paraStyle, const std::optional<std::u16string>& urlAddress);
    void CreateSpanResult(RichEditorChangeValue& changeValue, int32_t& innerPosition, int32_t spanIndex,
        int32_t offsetInSpan, int32_t endInSpan, std::u16string content, std::optional<TextStyle> textStyle,
        std::optional<struct UpdateParagraphStyle> paraStyle, const std::optional<std::u16string>& urlAddress);
    void SetTextStyleToRet(RichEditorAbstractSpanResult& retInfo, const TextStyle& textStyle);
    void CalcInsertValueObj(TextInsertValueInfo& info, int textIndex, bool isCreate = false);
    void GetDeletedSpan(RichEditorChangeValue& changeValue, int32_t& innerPosition, int32_t length,
        RichEditorDeleteDirection direction = RichEditorDeleteDirection::FORWARD);
    RefPtr<SpanItem> GetDelPartiallySpanItem(
        RichEditorChangeValue& changeValue, std::u16string& originalStr, int32_t& originalPos);
    void FixMoveDownChange(RichEditorChangeValue& changeValue, int32_t delLength);
    bool BeforeChangeText(
        RichEditorChangeValue& changeValue, const OperationRecord& record, RecordType type, int32_t delLength = 0);
    void BeforeUndo(RichEditorChangeValue& changeValue, int32_t& innerPosition, const OperationRecord& record);
    void BeforeRedo(RichEditorChangeValue& changeValue, int32_t& innerPosition, const OperationRecord& record);
    void BeforeDrag(RichEditorChangeValue& changeValue, int32_t& innerPosition, const OperationRecord& record);
    bool BeforeChangeText(RichEditorChangeValue& changeValue, const TextSpanOptions& options);

    // add for scroll.
    void UpdateChildrenOffset();
    void MoveFirstHandle(float offset);
    void MoveSecondHandle(float offset);
    void InitScrollablePattern();
    bool IsReachedBoundary(float offset);
    void UpdateScrollBarOffset() override;
    void CheckScrollable();
    void UpdateMagnifierStateAfterLayout(bool frameSizeChange);
    void UpdateScrollStateAfterLayout(bool shouldDisappear);
    void ScheduleAutoScroll(AutoScrollParam param);
    void OnAutoScroll(AutoScrollParam param);
    void StopAutoScroll();
    void AutoScrollByEdgeDetection(AutoScrollParam param, OffsetF offset, EdgeDetectionStrategy strategy);
    float CalcDragSpeed(float hotAreaStart, float hotAreaEnd, float point);
    float MoveTextRect(float offset);
    void SetNeedMoveCaretToContentRect();
    void MoveCaretToContentRect();
    void MoveCaretToContentRect(const OffsetF& caretOffset, float caretHeight);
    void MoveCaretToContentRect(float offset, int32_t source);
    bool IsCaretInContentArea();
    bool IsTextArea() const override
    {
        return true;
    }
    void ProcessInnerPadding();
    bool IsReachTop()
    {
        return NearEqual(richTextRect_.GetY(), contentRect_.GetY());
    }

    bool IsReachBottom()
    {
        return NearEqual(richTextRect_.Bottom(), contentRect_.Bottom());
    }
    // ai analysis fun
    bool NeedAiAnalysis(
        const CaretUpdateType targeType, const int32_t pos, const int32_t& spanStart, const std::string& content);
    bool IsIndexAfterOrInSymbolOrEmoji(int32_t index);
    void AdjustCursorPosition(int32_t& pos);
    void AdjustPlaceholderSelection(int32_t& start, int32_t& end, const Offset& pos);
    bool AdjustWordSelection(int32_t& start, int32_t& end);
    bool IsTouchAtLineEnd(int32_t caretPos, const Offset& textOffset);
    bool IsTouchBeforeCaret(int32_t caretPos, const Offset& textOffset);
    bool IsClickBoundary(const int32_t position);
    void SetSelfAndChildDraggableFalse(const RefPtr<UINode>& customNode);
    RefPtr<SpanItem> GetSameSpanItem(const RefPtr<SpanItem>& spanItem);
    RefPtr<ImageSpanNode> GetImageSpanNodeBySpanItem(const RefPtr<ImageSpanItem>& spanItem);

    void AdjustSelectRects(SelectRectsType pos, std::vector<RectF>& selectRects);
    RectF GetSelectArea(SelectRectsType pos);
    void AppendSelectRect(std::vector<RectF>& selectRects);
    bool IsTouchInFrameArea(const PointF& touchPoint);
    void HandleOnDragDrop(const RefPtr<OHOS::Ace::DragEvent>& event, bool isCopy = false);
    void DeleteForward(int32_t currentPosition, int32_t length);
    int32_t HandleOnDragDeleteForward();
    void HandleOnDragDropTextOperation(const std::u16string& insertValue, bool isDeleteSelect, bool isCopy = false);
    void UndoDrag(const OperationRecord& record);
    void RedoDrag(const OperationRecord& record);
    void HandleOnDragInsertValueOperation(const std::u16string& insertValue);
    void HandleOnDragInsertValue(const std::u16string& str);
    void HandleOnEditChanged(bool isEditing);
    void OnTextInputActionUpdate(TextInputAction value);
    void CloseSystemMenu();
    void SetAccessibilityAction() override;
    void SetAccessibilityEditAction();
    bool IsAccessibilityClick();
    void HandleTripleClickEvent(OHOS::Ace::GestureEvent& info);
    void UpdateSelectionByTouchMove(const Offset& offset);
    bool CheckTripClickEvent(GestureEvent& info);
    void HandleSelect(GestureEvent& info, int32_t selectStart, int32_t selectEnd);
    TextStyleResult GetTextStyleBySpanItem(const RefPtr<SpanItem>& spanItem);
    ImageStyleResult GetImageStyleBySpanItem(const RefPtr<SpanItem>& spanItem);
    void SetSubSpans(RefPtr<SpanString>& spanString, int32_t start, int32_t end);
    void SetSubMap(RefPtr<SpanString>& spanString);
    void OnCopyOperationExt(RefPtr<PasteDataMix>& pasteData);
    void AddSpanByPasteData(const RefPtr<SpanString>& spanString);
    void CompleteStyledString(RefPtr<SpanString>& spanString);
    void InsertStyledStringByPaste(const RefPtr<SpanString>& spanString);
    void HandleOnDragInsertStyledString(const RefPtr<SpanString>& spanString, bool isCopy = false);
    void AddSpansByPaste(const std::list<RefPtr<NG::SpanItem>>& spans);
    TextSpanOptions GetTextSpanOptions(const RefPtr<SpanItem>& spanItem);
    void HandleOnCopyStyledString();
    void HandleOnDragDropStyledString(const RefPtr<OHOS::Ace::DragEvent>& event, bool isCopy = false);
    void NotifyExitTextPreview(bool deletePreviewText = true);
    void NotifyImfFinishTextPreview();
    int32_t CalculateTruncationLength(const std::u16string& insertValue, int32_t start);
    bool ProcessTextTruncationOperation(std::u16string& text, bool shouldCommitInput);
    void ProcessInsertValueMore(const std::u16string& text, OperationRecord record, OperationType operationType,
        RichEditorChangeValue changeValue, PreviewTextRecord preRecord);
    void ProcessInsertValue(const std::u16string& insertValue, OperationType operationType = OperationType::DEFAULT,
        bool shouldCommitInput = false);
    void FinishTextPreviewInner(bool deletePreviewText = true);
    void TripleClickSection(GestureEvent& info, int32_t start, int32_t end, int32_t pos);
    void ProcessOverlayOnSetSelection(const std::optional<SelectionOptions>& options);
    std::pair<int32_t, SelectType> JudgeSelectType(const Offset& pos);
    bool IsSelectEmpty(int32_t start, int32_t end);
    bool AdjustIndexSkipLineSeparator(int32_t& currentPosition);
    bool AdjustIndexSkipSpace(int32_t& currentPosition, const MoveDirection direction);
    void RequestKeyboardToEdit();
    void HandleTasksOnLayoutSwap()
    {
        while (!tasks_.empty()) {
            const auto& task = tasks_.front();
            if (task) {
                task();
            }
            tasks_.pop();
        }
    }
    void PostTaskToLayutSwap(std::function<void()>&& task)
    {
        tasks_.emplace(std::forward<std::function<void()>>(task));
    }

    OffsetF GetGlobalOffset() const;
    void MergeAdjacentSpans(int32_t caretPosition);
    void HandleImageDrag(const RefPtr<ImageSpanNode>& imageNode);
    void DisableDrag(const RefPtr<ImageSpanNode>& imageNode);
    void SetGestureOptions(UserGestureOptions userGestureOptions, RefPtr<SpanItem> spanItem);
    void AddSpanHoverEvent(
        RefPtr<SpanItem> spanItem, const RefPtr<FrameNode>& frameNode, const SpanOptionBase& options);
    void UpdateGestureHotZone(const RefPtr<LayoutWrapper>& dirty);
    void ClearOnFocusTextField(FrameNode* node);
    void ProcessResultObject(RefPtr<PasteDataMix> pasteData, const ResultObject& result);
    void EncodeTlvDataByResultObject(const ResultObject& result, std::vector<uint8_t>& tlvData);
    bool InitPreviewText(const std::u16string& previewTextValue, const PreviewRange& range);
    bool ReplaceText(const std::u16string& previewTextValue, const PreviewRange& range);
    bool UpdatePreviewText(const std::u16string& previewTextValue, const PreviewRange& range);
    bool IsEnPreview();
    void SetMagnifierLocalOffset(Offset localOffset);
    void SetMagnifierOffsetWithAnimation(Offset offset);
    void UpdateSelectionAndHandleVisibility();
    void SetIsEnableSubWindowMenu();
    void OnReportRichEditorEvent(const std::string& event);

#if defined(ENABLE_STANDARD_INPUT)
    sptr<OHOS::MiscServices::OnTextChangedListener> richEditTextChangeListener_;
#else
    RefPtr<TextInputConnection> connection_ = nullptr;
#endif
    const bool isAPI14Plus;
    const bool isAPI16Plus;
    const bool isAPI18Plus;
    const bool isAPI20Plus;
    bool shiftFlag_ = false;
    bool isMouseSelect_ = false;
    bool isMousePressed_ = false;
    bool isFirstMouseSelect_ = true;
    bool leftMousePress_ = false;
    bool isLongPress_ = false;
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    bool imeAttached_ = false;
    bool imeShown_ = false;
#endif
    bool isTextChange_ = false;
    bool caretVisible_ = false;
    bool caretTwinkling_ = false;
    bool isRichEditorInit_ = false;
    bool clickEventInitialized_ = false;
    bool focusEventInitialized_ = false;
    bool blockPress_ = false;
    bool isCustomKeyboardAttached_ = false;
    bool usingMouseRightButton_ = false;
    bool isCursorAlwaysDisplayed_ = false;
    bool isClickOnAISpan_ = false;
    bool isOnlyRequestFocus_ = false;

    int32_t moveLength_ = 0;
    int32_t insertValueLength_ = 0;
    int32_t lastCaretPosition_ = 0;
    int32_t caretPosition_ = 0;
    int32_t caretSpanIndex_ = -1;
    long long timestamp_ = 0;
    CaretAffinityPolicy caretAffinityPolicy_ = CaretAffinityPolicy::DEFAULT;
    OffsetF selectionMenuOffsetByMouse_;
    OffsetF selectionMenuOffsetClick_;
    OffsetF lastClickOffset_;
    std::u16string pasteStr_;

    // still in progress
    RichEditorParagraphManager paragraphs_;
    RefPtr<Paragraph> presetParagraph_;
    std::vector<OperationRecord> operationRecords_;
    std::vector<OperationRecord> redoOperationRecords_;
    std::list<WeakPtr<ImageSpanNode>> hoverableNodes;
    RefPtr<ImageSpanItem> lastHoverSpanItem_ = nullptr;
    HoverInfo lastHoverInfo_;

    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<PanEvent> panEvent_;
    struct UpdateSpanStyle updateSpanStyle_;
    CancelableCallback<void()> caretTwinklingTask_;
    RefPtr<RichEditorController> richEditorController_;
    RefPtr<RichEditorStyledStringController> richEditorStyledStringController_;
    MoveDirection moveDirection_ = MoveDirection::FORWARD;
    RectF frameRect_;
    std::optional<struct UpdateSpanStyle> typingStyle_;
    std::optional<TextStyle> typingTextStyle_;
    std::list<ResultObject> dragResultObjects_;
    std::optional<Color> caretColor_;
    std::optional<Color> selectedBackgroundColor_;
    std::function<void()> customKeyboardBuilder_;
    std::function<void(int32_t)> caretChangeListener_;
    RefPtr<OverlayManager> keyboardOverlay_;
    RefPtr<AIWriteAdapter> aiWriteAdapter_ = MakeRefPtr<AIWriteAdapter>();
    Offset selectionMenuOffset_;
    // add for scroll
    RectF richTextRect_;
    float scrollOffset_ = 0.0f;
    bool isFirstCallOnReady_ = false;
    bool scrollable_ = true;
    CancelableCallback<void()> autoScrollTask_;
    OffsetF prevAutoScrollOffset_;
    AutoScrollParam currentScrollParam_;
    bool isAutoScrollRunning_ = false;
    // add for ai input analysis
    bool hasClicked_ = false;
    CaretUpdateType caretUpdateType_ = CaretUpdateType::NONE;
    TimeStamp lastClickTimeStamp_;
    TimeStamp lastAiPosTimeStamp_;
    bool adjusted_ = false;
    bool isShowMenu_ = true;
    bool isShowPlaceholder_ = false;
    bool isSingleHandle_ = false;
    TouchAndMoveCaretState moveCaretState_;
    FloatingCaretState floatingCaretState_;
    std::shared_ptr<AnimationUtils::Animation> magnifierAnimation_;
    // Recorded when touch down or mouse left button press.
    OffsetF globalOffsetOnMoveStart_;
    SelectionRangeInfo lastSelectionRange_{-1, -1};
    bool isDragSponsor_ = false;
    std::pair<int32_t, int32_t> dragRange_ { 0, 0 };
    bool isInterceptMouseRightRelease_ = false;
    bool isEditing_ = false;
    int32_t dragPosition_ = 0;
    // Action when "enter" pressed.
    TextInputAction action_ = TextInputAction::NEW_LINE;
    // What the keyboard appears.
    TextInputType keyboard_ = TextInputType::UNSPECIFIED;
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorPattern);
    bool keyboardAvoidance_ = false;
    int32_t richEditorInstanceId_ = -1;
    int32_t frameId_ = -1;
    bool contentChange_ = false;
    PreviewTextRecord previewTextRecord_;
    bool isTextPreviewSupported_ = true;
    OffsetF movingHandleOffset_;
    std::pair<int32_t, int32_t> initSelector_ = { 0, 0 };
    std::vector<TimeStamp> clickInfo_;
    int32_t selectingFingerId_ = -1;
    bool isTouchSelecting_ = false;
    bool previewLongPress_ = false;
    bool editingLongPress_ = false;
    bool needMoveCaretToContentRect_ = false;
    std::queue<std::function<void()>> tasks_;
    bool isModifyingContent_ = false;
    bool needToRequestKeyboardOnFocus_ = true;
    bool isEnableHapticFeedback_ = true;
    float maxLinesHeight_ = FLT_MAX;
    int32_t maxLines_ = INT32_MAX;
    std::unordered_map<std::u16string, RefPtr<SpanItem>> placeholderSpansMap_;
    std::optional<DisplayMode> barDisplayMode_ = std::nullopt;
    uint32_t twinklingInterval_ = 0;
    bool isTriggerAvoidOnCaretAvoidMode_ = false;
    RectF lastRichTextRect_;
    std::optional<int32_t> maxLength_ = std::nullopt;
    std::unique_ptr<OneStepDragController> oneStepDragController_;
    std::unique_ptr<RichEditorUndoManager> undoManager_;
    std::list<WeakPtr<ImageSpanNode>> imageNodes;
    std::list<WeakPtr<PlaceholderSpanNode>> builderNodes;
    bool isStopBackPress_ = true;
    bool blockKbInFloatingWindow_ = false;
    KeyboardAppearance keyboardAppearance_ = KeyboardAppearance::NONE_IMMERSIVE;
    LRUMap<std::uintptr_t, RefPtr<Paragraph>> paragraphCache_;
    SysScale lastSysScale_;
    std::map<int32_t, AISpan> lastAISpanMap_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_PATTERN_H
