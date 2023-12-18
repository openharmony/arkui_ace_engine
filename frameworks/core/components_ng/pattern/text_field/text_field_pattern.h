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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_PATTERN_H

#include <cstdint>
#include <optional>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/rect.h"
#include "base/memory/referenced.h"
#include "base/mousestyle/mouse_style.h"
#include "base/view_data/view_data_wrap.h"
#include "core/common/clipboard/clipboard.h"
#include "core/common/ime/text_edit_controller.h"
#include "core/common/ime/text_input_action.h"
#include "core/common/ime/text_input_client.h"
#include "core/common/ime/text_input_configuration.h"
#include "core/common/ime/text_input_connection.h"
#include "core/common/ime/text_input_formatter.h"
#include "core/common/ime/text_input_proxy.h"
#include "core/common/ime/text_input_type.h"
#include "core/common/ime/text_selection.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/text_menu_extension.h"
#include "core/components_ng/pattern/text_area/text_area_layout_algorithm.h"
#include "core/components_ng/pattern/text_drag/text_drag_base.h"
#include "core/components_ng/pattern/text_field/content_controller.h"
#include "core/components_ng/pattern/text_field/text_editing_value_ng.h"
#include "core/components_ng/pattern/text_field/text_field_accessibility_property.h"
#include "core/components_ng/pattern/text_field/text_field_controller.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_paint_method.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/pattern/text_field/text_input_response_area.h"
#include "core/components_ng/pattern/text_field/text_select_controller.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/pattern/text_input/text_input_layout_algorithm.h"
#include "core/components_ng/property/property.h"

#if not defined(ACE_UNITTEST)
#if defined(ENABLE_STANDARD_INPUT)
#include "commonlibrary/c_utils/base/include/refbase.h"

namespace OHOS::MiscServices {
class OnTextChangedListener;
struct TextConfig;
} // namespace OHOS::MiscServices
#endif
#endif

namespace OHOS::Ace::NG {

enum class FocuseIndex { TEXT = 0, CANCEL, UNIT };

enum class SelectionMode { SELECT, SELECT_ALL, NONE };

enum class DragStatus { DRAGGING, ON_DROP, NONE };

enum class CaretStatus { SHOW, HIDE, NONE };

enum class InputOperation {
    INSERT,
    DELETE_BACKWARD,
    DELETE_FORWARD,
    CURSOR_UP,
    CURSOR_DOWN,
    CURSOR_LEFT,
    CURSOR_RIGHT
};

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

struct PasswordModeStyle {
    Color bgColor;
    Color textColor;
    BorderWidthProperty borderwidth;
    BorderColorProperty borderColor;
    BorderRadiusProperty radius;
    PaddingProperty padding;
    MarginProperty margin;
};

struct PreInlineState {
    Color textColor;
    Color bgColor;
    BorderRadiusProperty radius;
    BorderWidthProperty borderWidth;
    BorderColorProperty borderColor;
    PaddingProperty padding;
    MarginProperty margin;
    RectF frameRect;
    bool setHeight = false;
    bool saveInlineState = false;
    bool hasBorderColor = false;
};

struct ShowSelectOverlayParams {
    std::optional<RectF> firstHandle;
    std::optional<RectF> secondHandle;
    bool animation = false;
    bool isShowMenu = true;
    bool isUpdateMenu = true;
};

class TextFieldPattern : public ScrollablePattern,
                         public TextDragBase,
                         public ValueChangeObserver,
                         public TextInputClient,
                         public TextBase {
    DECLARE_ACE_TYPE(TextFieldPattern, ScrollablePattern, TextDragBase, ValueChangeObserver, TextInputClient, TextBase);

public:
    TextFieldPattern();
    ~TextFieldPattern() override;

    // TextField needs softkeyboard, override function.
    bool NeedSoftKeyboard() const override
    {
        return true;
    }

    bool CheckBlurReason();

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<TextFieldLayoutProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<TextFieldEventHub>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<TextFieldPaintProperty>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<TextFieldAccessibilityProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        if (IsTextArea()) {
            return MakeRefPtr<TextAreaLayoutAlgorithm>();
        }
        return MakeRefPtr<TextInputLayoutAlgorithm>();
    }

    void OnModifyDone() override;
    void UpdateSelectionOffset();
    void CalcCaretMetricsByPosition(
        int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity = TextAffinity::DOWNSTREAM);
    int32_t ConvertTouchOffsetToCaretPosition(const Offset& localOffset);
    int32_t ConvertTouchOffsetToCaretPositionNG(const Offset& localOffset);

    // Obtain the systemWindowsId when switching between windows
    uint32_t GetSCBSystemWindowId();

    void InsertValue(const std::string& insertValue) override;
    void InsertValueOperation(const std::string& insertValue);
    void UpdateCounterTextColor();
    void UpdateCounterMargin();
    void CleanCounterNode();
    void UltralimitShake();
    void UpdateCounterBorderStyle(uint32_t& textLength, uint32_t& maxLength);
    void UpdateAreaBorderStyle(BorderWidthProperty& currentBorderWidth, BorderWidthProperty& overCountBorderWidth,
    BorderColorProperty& overCountBorderColor, BorderColorProperty& currentBorderColor);
    void DeleteBackward(int32_t length) override;
    void DeleteBackwardOperation(int32_t length);
    void DeleteForward(int32_t length) override;
    void DeleteForwardOperation(int32_t length);
    void UpdateRecordCaretIndex(int32_t index);
    void CreateHandles() override;

    WeakPtr<LayoutWrapper> GetCounterNode()
    {
        return counterTextNode_;
    }

    bool GetCounterState() const
    {
        return counterChange_;
    }

    void SetCounterState(bool counterChange)
    {
        counterChange_ = counterChange;
    }

    float GetTextOrPlaceHolderFontSize();

    void SetTextFieldController(const RefPtr<TextFieldController>& controller)
    {
        textFieldController_ = controller;
    }

    const RefPtr<TextFieldController>& GetTextFieldController()
    {
        return textFieldController_;
    }

    void SetTextEditController(const RefPtr<TextEditController>& textEditController)
    {
        textEditingController_ = textEditController;
    }

    std::string GetTextValue() const
    {
        return contentController_->GetTextValue();
    }

#if defined(IOS_PLATFORM)
    const TextEditingValue& GetInputEditingValue() const override
    {
        static TextEditingValue value;
        return value;
    };
    Offset GetGlobalOffset() const;
    double GetEditingBoxY() const override;
    double GetEditingBoxTopY() const override;
    bool GetEditingBoxModel() const override;
#endif

    bool ShouldDelayChildPressedState() const override
    {
        return false;
    }

    void UpdateEditingValue(const std::string& value, int32_t caretPosition)
    {
        contentController_->SetTextValue(value);
        selectController_->UpdateCaretIndex(caretPosition);
    }
    void UpdateCaretPositionByTouch(const Offset& offset);
    bool IsReachedBoundary(float offset);

    virtual TextInputAction GetDefaultTextInputAction();
    bool RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard);
    bool CloseKeyboard(bool forceClose) override;

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true };
    }

    void PerformAction(TextInputAction action, bool forceCloseKeyboard = false) override;
    void UpdateEditingValue(const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent = true) override;
    void UpdateInputFilterErrorText(const std::string& errorText) override;

    void OnValueChanged(bool needFireChangeEvent = true, bool needFireSelectChangeEvent = true) override;

    void OnAreaChangedInner() override;
    void OnVisibleChange(bool isVisible) override;
    void ClearEditingValue();
    void HandleCounterBorder();
    std::wstring GetWideText()
    {
        return contentController_->GetWideText();
    }

    int32_t GetCaretIndex() const
    {
        return selectController_->GetCaretIndex();
    }

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(TextInputAction, TextInputAction)

    const RefPtr<Paragraph>& GetParagraph() const
    {
        return paragraph_;
    }

    const RefPtr<Paragraph>& GetErrorParagraph() const
    {
        return errorParagraph_;
    }

    bool GetCursorVisible() const
    {
        return cursorVisible_;
    }

#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    bool GetImeAttached() const
    {
        return imeAttached_;
    }
#endif

    const OffsetF& GetLastTouchOffset()
    {
        return lastTouchOffset_;
    }

    const OffsetF& GetRightClickOffset()
    {
        return rightClickOffset_;
    }

    OffsetF GetCaretOffset() const
    {
        return selectController_->GetCaretRect().GetOffset();
    }

    float GetCaretOffsetX() const
    {
        return selectController_->GetCaretRect().GetX();
    }

    CaretUpdateType GetCaretUpdateType() const
    {
        return caretUpdateType_;
    }

    void SetCaretUpdateType(CaretUpdateType type)
    {
        caretUpdateType_ = type;
    }

    float GetPaddingTop() const
    {
        return utilPadding_.top.value_or(0.0f);
    }

    float GetPaddingBottom() const
    {
        return utilPadding_.bottom.value_or(0.0f);
    }

    float GetPaddingLeft() const
    {
        return utilPadding_.left.value_or(0.0f);
    }

    float GetPaddingRight() const
    {
        return utilPadding_.right.value_or(0.0f);
    }

    const PaddingPropertyF& GetUtilPadding() const
    {
        return utilPadding_;
    }

    float GetHorizontalPaddingAndBorderSum() const
    {
        return utilPadding_.left.value_or(0.0f) + utilPadding_.right.value_or(0.0f) + GetBorderLeft() +
               GetBorderRight();
    }

    float GetVerticalPaddingAndBorderSum() const
    {
        return utilPadding_.top.value_or(0.0f) + utilPadding_.bottom.value_or(0.0f) + GetBorderTop() +
               GetBorderBottom();
    }

    float GetBorderLeft() const
    {
        return lastBorderWidth_.leftDimen.value_or(Dimension(0.0f)).ConvertToPx();
    }

    float GetBorderTop() const
    {
        return lastBorderWidth_.topDimen.value_or(Dimension(0.0f)).ConvertToPx();
    }

    float GetBorderBottom() const
    {
        return lastBorderWidth_.bottomDimen.value_or(Dimension(0.0f)).ConvertToPx();
    }

    float GetBorderRight() const
    {
        return lastBorderWidth_.rightDimen.value_or(Dimension(0.0f)).ConvertToPx();
    }

    const RectF& GetTextRect() override
    {
        return textRect_;
    }

    void SetTextRect(const RectF& textRect)
    {
        textRect_ = textRect;
    }

    const RectF& GetContentRect() const
    {
        return contentRect_;
    }

    const RectF& GetFrameRect() const
    {
        return frameRect_;
    }

    float GetCountHeight() const
    {
        return countHeight_;
    }

    const RefPtr<TextSelectController>& GetTextSelectController()
    {
        return selectController_;
    }

    void SetInSelectMode(SelectionMode selectionMode)
    {
        selectionMode_ = selectionMode;
    }

    SelectionMode GetSelectMode() const
    {
        return selectionMode_;
    }

    bool IsSelected() const override
    {
        return selectController_->IsSelected();
    }

    bool IsUsingMouse() const
    {
        return isUsingMouse_;
    }
    int32_t GetWordLength(int32_t originCaretPosition, int32_t directionalMove);
    int32_t GetLineBeginPosition(int32_t originCaretPosition, bool needToCheckLineChanged = true);
    int32_t GetLineEndPosition(int32_t originCaretPosition, bool needToCheckLineChanged = true);
    bool IsOperation() const
    {
        return !contentController_->IsEmpty();
    }

    void CursorMove(CaretMoveIntent direction) override;
    bool CursorMoveLeft();
    bool CursorMoveLeftOperation();
    bool CursorMoveLeftWord();
    bool CursorMoveLineBegin();
    bool CursorMoveToParagraphBegin();
    bool CursorMoveHome();
    bool CursorMoveRight();
    bool CursorMoveRightOperation();
    bool CursorMoveRightWord();
    bool CursorMoveLineEnd();
    bool CursorMoveToParagraphEnd();
    bool CursorMoveEnd();
    bool CursorMoveUp();
    bool CursorMoveDown();
    bool CursorMoveUpOperation();
    bool CursorMoveDownOperation();
    void SetCaretPosition(int32_t position);
    void HandleSetSelection(int32_t start, int32_t end, bool showHandle = true) override;
    void HandleExtendAction(int32_t action) override;
    void HandleSelect(CaretMoveIntent direction) override;
    OffsetF GetDragUpperLeftCoordinates() override;

    std::vector<RectF> GetTextBoxes() override
    {
        return selectController_->GetSelectedRects();
    }
    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;
    void FromJson(const std::unique_ptr<JsonValue>& json) override;
    void InitEditingValueText(std::string content);

    void CloseSelectOverlay() override;
    void CloseSelectOverlay(bool animation);
    void SetInputMethodStatus(bool keyboardShown) override
    {
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        imeShown_ = keyboardShown;
#endif
    }
    void NotifyKeyboardClosedByUser() override
    {
        FocusHub::LostFocusToViewRoot();
    }
    std::u16string GetLeftTextOfCursor(int32_t number) override;
    std::u16string GetRightTextOfCursor(int32_t number) override;
    int32_t GetTextIndexAtCursor() override;

    bool HasConnection() const
    {
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        return imeShown_;
#else
        return connection_;
#endif
    }
    float PreferredLineHeight(bool isAlgorithmMeasure = false);

    void SearchRequestKeyboard();

    bool GetTextObscured() const
    {
        return textObscured_;
    }

    static std::u16string CreateObscuredText(int32_t len);
    static std::u16string CreateDisplayText(
        const std::string& content, int32_t nakedCharPosition, bool needObscureText);
    bool IsTextArea() const override;

    const RefPtr<TouchEventImpl>& GetTouchListener()
    {
        return touchListener_;
    }

    bool NeedShowPasswordIcon()
    {
        auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_RETURN(layoutProperty, false);
        return IsInPasswordMode() && layoutProperty->GetShowPasswordIconValue(true);
    }

    void SetEnableTouchAndHoverEffect(bool enable)
    {
        enableTouchAndHoverEffect_ = enable;
    }

    RectF GetCaretRect() const override
    {
        return selectController_->GetCaretRect();
    }

    void HandleSurfaceChanged(int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight);
    void HandleSurfacePositionChanged(int32_t posX, int32_t posY) const;

    void InitSurfaceChangedCallback();
    void InitSurfacePositionChangedCallback();

    bool HasSurfaceChangedCallback()
    {
        return surfaceChangedCallbackId_.has_value();
    }
    void UpdateSurfaceChangedCallbackId(int32_t id)
    {
        surfaceChangedCallbackId_ = id;
    }

    bool HasSurfacePositionChangedCallback()
    {
        return surfacePositionChangedCallbackId_.has_value();
    }
    void UpdateSurfacePositionChangedCallbackId(int32_t id)
    {
        surfacePositionChangedCallbackId_ = id;
    }

    void ProcessInnerPadding();
    void OnCursorMoveDone(TextAffinity textAffinity = TextAffinity::UPSTREAM);
    bool IsDisabled();
    bool AllowCopy();

    bool GetIsMousePressed() const
    {
        return isMousePressed_;
    }

    MouseStatus GetMouseStatus() const
    {
        return mouseStatus_;
    }

    void SetMenuOptionItems(std::vector<MenuOptionsParam>&& menuOptionItems)
    {
        menuOptionItems_ = std::move(menuOptionItems);
    }

    const std::vector<MenuOptionsParam>&& GetMenuOptionItems() const
    {
        return std::move(menuOptionItems_);
    }

    void UpdateEditingValueToRecord();
    void UpdateScrollBarOffset() override;

    bool UpdateCurrentOffset(float offset, int32_t source) override
    {
        OnScrollCallback(offset, source);
        return true;
    }

    bool IsAtTop() const override
    {
        return contentRect_.GetY() == textRect_.GetY();
    }

    bool IsAtBottom() const override
    {
        return contentRect_.GetY() + contentRect_.Height() == textRect_.GetY() + textRect_.Height();
    }

    bool IsScrollable() const override
    {
        return scrollable_;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    float GetCurrentOffset() const
    {
        return currentOffset_;
    }

    RefPtr<TextFieldContentModifier> GetContentModifier()
    {
        return textFieldContentModifier_;
    }

    double GetScrollBarWidth();

    float GetLineHeight() const override
    {
        return selectController_->GetCaretRect().Height();
    }

    OffsetF GetParentGlobalOffset() const override
    {
        return parentGlobalOffset_;
    }

    const RectF& GetTextContentRect() const override
    {
        return contentRect_;
    }

    ParagraphT GetDragParagraph() const override
    {
        return { dragParagraph_ };
    }

    const RefPtr<FrameNode>& MoveDragNode() override
    {
        return dragNode_;
    }

    const std::vector<std::string>& GetDragContents() const
    {
        return dragContents_;
    }

    void AddDragFrameNodeToManager(const RefPtr<FrameNode>& frameNode)
    {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto dragDropManager = context->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        dragDropManager->AddDragFrameNode(frameNode->GetId(), AceType::WeakClaim(AceType::RawPtr(frameNode)));
    }

    void RemoveDragFrameNodeFromManager(const RefPtr<FrameNode>& frameNode)
    {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto dragDropManager = context->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        dragDropManager->RemoveDragFrameNode(frameNode->GetId());
    }

    bool IsDragging() const
    {
        return dragStatus_ == DragStatus::DRAGGING;
    }

    bool IsTouchTestPointInArea(const Offset& touchOffset, bool isTouchPointHits) override
    {
        return isTouchPointHits && BetweenSelectedPosition(touchOffset);
    }

    bool BetweenSelectedPosition(const Offset& globalOffset) override
    {
        if (!IsSelected()) {
            return false;
        }
        Offset offset = globalOffset -
                        Offset(IsTextArea() ? contentRect_.GetX() : textRect_.GetX(),
                            IsTextArea() ? textRect_.GetY() : contentRect_.GetY()) -
                        Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY());
        for (const auto& rect : selectController_->GetSelectedRects()) {
            bool isInRange = rect.IsInRegion({ offset.GetX(), offset.GetY() });
            if (isInRange) {
                return true;
            }
        }
        return false;
    }

    bool RequestCustomKeyboard();
    bool CloseCustomKeyboard();

    // xts
    std::string TextInputTypeToString() const;
    std::string TextInputActionToString() const;
    std::string GetPlaceholderFont() const;
    RefPtr<TextFieldTheme> GetTheme() const;
    std::string GetTextColor() const;
    std::string GetCaretColor() const;
    std::string GetPlaceholderColor() const;
    std::string GetFontSize() const;
    Ace::FontStyle GetItalicFontStyle() const;
    FontWeight GetFontWeight() const;
    std::string GetFontFamily() const;
    TextAlign GetTextAlign() const;
    std::string GetPlaceHolder() const;
    uint32_t GetMaxLength() const;
    uint32_t GetMaxLines() const;
    std::string GetInputFilter() const;
    std::string GetCopyOptionString() const;
    std::string GetInputStyleString() const;
    std::string GetErrorTextString() const;
    std::string GetBarStateString() const;
    bool GetErrorTextState() const;
    std::string GetShowPasswordIconString() const;
    int32_t GetNakedCharPosition() const;
    void SetSelectionFlag(int32_t selectionStart, int32_t selectionEnd);
    void HandleBlurEvent();
    void HandleFocusEvent();
    bool OnBackPressed() override;
    void CheckScrollable();
    void HandleClickEvent(GestureEvent& info);
    void HandleDoubleClickEvent(GestureEvent& info);
    void HandleSingleClickEvent(GestureEvent& info);

    void HandleSelectionUp();
    void HandleSelectionDown();
    void HandleSelectionLeft();
    void HandleSelectionLeftWord();
    void HandleSelectionLineBegin();
    void HandleSelectionHome();
    void HandleSelectionRight();
    void HandleSelectionRightWord();
    void HandleSelectionLineEnd();
    void HandleSelectionEnd();
    bool HandleOnEscape() override;
    bool HandleOnTab(bool backward) override;
    void HandleOnUndoAction() override;
    void HandleOnRedoAction() override;
    void HandleOnSelectAll(bool isKeyEvent, bool inlineStyle = false);
    void HandleOnSelectAll() override
    {
        HandleOnSelectAll(true);
    }
    void HandleOnCopy() override;
    void HandleOnPaste() override;
    void HandleOnCut() override;
    void HandleOnCameraInput();
    void StripNextLine(std::wstring& data);
    bool OnKeyEvent(const KeyEvent& event);
    int32_t GetLineCount() const;
    TextInputType GetKeyboard()
    {
        return keyboard_;
    }
    TextInputAction GetAction()
    {
        return action_;
    }

    void SetNeedToRequestKeyboardOnFocus(bool needToRequest)
    {
        needToRequestKeyboardOnFocus_ = needToRequest;
    }
    void SetUnitNode(const RefPtr<NG::UINode>& unitNode)
    {
        unitNode_ = unitNode;
    }
    void AddCounterNode();
    void ClearCounterNode();
    void SetShowError();

    float GetUnderlineWidth() const
    {
        return static_cast<float>(underlineWidth_.Value());
    }

    const Color& GetUnderlineColor() const
    {
        return underlineColor_;
    }

    float GetMarginBottom() const;

    void SetUnderlineColor(Color underlineColor)
    {
        underlineColor_ = underlineColor;
    }

    void SetUnderlineWidth(Dimension underlineWidth)
    {
        underlineWidth_ = underlineWidth;
    }

    bool IsSelectAll()
    {
        return abs(selectController_->GetStartIndex() - selectController_->GetEndIndex()) >=
               static_cast<int32_t>(contentController_->GetWideText().length());
    }

    void StopEditing();

    void MarkContentChange()
    {
        contChange_ = true;
    }

    void ResetContChange()
    {
        contChange_ = false;
    }

    bool GetContChange() const
    {
        return contChange_;
    }
    std::string GetShowResultImageSrc() const;
    std::string GetHideResultImageSrc() const;
    void OnAttachToFrameNode() override;

    bool GetTextInputFlag() const
    {
        return isTextInput_;
    }

    void SetSingleLineHeight(float height)
    {
        inlineSingleLineHeight_ = height;
    }

    float GetSingleLineHeight() const
    {
        return inlineSingleLineHeight_;
    }

    float GetInlinePadding() const
    {
        return inlinePadding_;
    }

    bool GetScrollBarVisible() const
    {
        return scrollBarVisible_;
    }

    float GetPreviewWidth() const
    {
        return inlineState_.frameRect.Width();
    }

    bool IsNormalInlineState() const;
    bool IsUnspecifiedOrTextType() const;
    void TextIsEmptyRect(RectF& rect);
    void TextAreaInputRectUpdate(RectF& rect);
    void UpdateRectByTextAlign(RectF& rect);

    void EditingValueFilterChange();

    void SetCustomKeyboard(const std::function<void()>&& keyboardBuilder)
    {
        if (customKeyboardBuilder_ && isCustomKeyboardAttached_ && !keyboardBuilder) {
            CloseCustomKeyboard();
        }
        customKeyboardBuilder_ = keyboardBuilder;
    }

    void DumpAdvanceInfo() override;
    void DumpViewDataPageNode(RefPtr<ViewDataWrap> viewDataWrap) override;
    void NotifyFillRequestSuccess(RefPtr<PageNodeInfoWrap> nodeWrap, AceAutoFillType autoFillType) override;
    void NotifyFillRequestFailed(int32_t errCode) override;
    bool CheckAutoSave() override;
    void OnColorConfigurationUpdate() override;
    bool NeedPaintSelect();

    void SetIsCustomFont(bool isCustomFont)
    {
        isCustomFont_ = isCustomFont;
    }

    bool GetIsCustomFont() const
    {
        return isCustomFont_;
    }

    void SetISCounterIdealHeight(bool IsIdealHeight)
    {
        isCounterIdealheight_ = IsIdealHeight;
    }

    bool GetIsCounterIdealHeight() const
    {
        return isCounterIdealheight_;
    }

    virtual RefPtr<FocusHub> GetFocusHub() const;

    // override SelectOverlayClient methods.
    void OnHandleMove(const RectF& handleRect, bool isFirstHandle) override;
    void OnHandleMoveDone(const RectF& handleRect, bool isFirstHandle) override;
    void OnHandleClosed(bool closedByGlobalEvent) override;
    bool CheckHandleVisible(const RectF& paintRect) override;
    void UpdateCaretInfoToController() const;
    bool OnPreShowSelectOverlay(
        SelectOverlayInfo& overlayInfo, const ClientOverlayInfo& clientInfo, bool isSelectOverlayOn) override;
    void OnObscuredChanged(bool isObscured);
    void OnSelectOverlayMenuClicked(SelectOverlayMenuId menuId) override
    {
        switch (menuId) {
            case SelectOverlayMenuId::COPY:
                HandleOnCopy();
                return;
            case SelectOverlayMenuId::CUT:
                HandleOnCut();
                return;
            case SelectOverlayMenuId::SELECT_ALL:
                HandleOnSelectAll(false);
                return;
            case SelectOverlayMenuId::PASTE:
                HandleOnPaste();
                return;
            case SelectOverlayMenuId::CAMERA_INPUT:
                HandleOnCameraInput();
                return;
        }
    }

    RefPtr<FrameNode> GetClientHost() const override
    {
        return GetHost();
    }

    const RefPtr<TextInputResponseArea>& GetResponseArea()
    {
        return responseArea_;
    }

    const RefPtr<TextInputResponseArea>& GetCleanNodeResponseArea()
    {
        return cleanNodeResponseArea_;
    }

    bool IsShowUnit() const;
    bool IsShowPasswordIcon() const;
    bool IsInPasswordMode() const;
    bool IsShowCancelButtonMode() const;

    bool GetShowSelect() const
    {
        return showSelect_;
    }

    bool UpdateFocusForward();

    bool UpdateFocusBackward();

    bool HandleSpaceEvent();

    RefPtr<PixelMap> GetPixelMap();

    void UpdateShowMagnifier(bool isShowMagnifier = false)
    {
        if (isShowMagnifier_ == isShowMagnifier) {
            return;
        }
        isShowMagnifier_ = isShowMagnifier;
        if (isShowMagnifier_) {
            MakeHighZIndex();
        } else {
            MakeZIndexRollBack();
        }
    }

    bool GetShowMagnifier() const
    {
        return isShowMagnifier_;
    }

    void SetLocalOffset(OffsetF localOffset)
    {
        localOffset_.SetX(localOffset.GetX());
        localOffset_.SetY(localOffset.GetY());
        UpdateShowMagnifier(true);
    }

    OffsetF GetLocalOffset() const
    {
        return localOffset_;
    }

    int32_t GetContentWideTextLength()
    {
        return static_cast<int32_t>(contentController_->GetWideText().length());
    }

    void ShowMenu();
    bool HasFocus() const;
    void StopTwinkling();

    const TimeStamp& GetLastClickTime()
    {
        return lastClickTimeStamp_;
    }
#ifdef ENABLE_DRAG_FRAMEWORK
    void HandleOnDragStatusCallback(
        const DragEventType& dragEventType, const RefPtr<NotifyDragEvent>& notifyDragEvent) override;
protected:
    virtual void InitDragEvent();
#endif

private:
    void GetTextSelectRectsInRangeAndWillChange();
    void OnAfterModifyDone() override;
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchDown(const Offset& offset);
    void HandleTouchUp();
    void HandleTouchMove(const TouchEventInfo& info);
    void UpdateCaretByTouchMove(const TouchEventInfo& info);
    void InitDisableColor();
    void InitFocusEvent();
    void InitTouchEvent();
    void InitLongPressEvent();
    void InitClickEvent();
#ifdef ENABLE_DRAG_FRAMEWORK
    void InitDragDropEvent();
    std::function<DragDropInfo(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> OnDragStart();
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> OnDragDrop();
    void ClearDragDropEvent();
    std::function<void(Offset)> GetThumbnailCallback();
    void HandleCursorOnDragMoved(const RefPtr<NotifyDragEvent>& notifyDragEvent);
    void HandleCursorOnDragLeaved(const RefPtr<NotifyDragEvent>& notifyDragEvent);
    void HandleCursorOnDragEnded(const RefPtr<NotifyDragEvent>& notifyDragEvent);
#endif
    int32_t UpdateCaretPositionOnHandleMove(const OffsetF& localOffset);
    bool HasStateStyle(UIState state) const;

    void OnTextInputScroll(float offset);
    void OnTextAreaScroll(float offset);
    bool OnScrollCallback(float offset, int32_t source) override;
    void OnScrollEndCallback() override;
    void InitMouseEvent();
    void HandleHoverEffect(MouseInfo& info, bool isHover);
    void OnHover(bool isHover);
    void ChangeMouseState(const Offset location, const RefPtr<PipelineContext>& pipeline, int32_t frameId);
    void HandleMouseEvent(MouseInfo& info);
    void FocusAndUpdateCaretByMouse(MouseInfo& info);
    void HandleRightMouseEvent(MouseInfo& info);
    void HandleRightMousePressEvent(MouseInfo& info);
    void HandleRightMouseReleaseEvent(MouseInfo& info);
    void HandleLeftMouseEvent(MouseInfo& info);
    void HandleLeftMousePressEvent(MouseInfo& info);
    void HandleLeftMouseMoveEvent(MouseInfo& info);
    void HandleLeftMouseReleaseEvent(MouseInfo& info);
    void HandleLongPress(GestureEvent& info);
    void UpdateCaretPositionWithClamp(const int32_t& pos);
    void ShowSelectOverlay(const ShowSelectOverlayParams& params);
    void ShowSelectOverlayAfterDrag();
    void CursorMoveOnClick(const Offset& offset);

    void ProcessOverlay(
        bool isUpdateMenu = true, bool animation = false, bool isShowMenu = true, bool isHiddenHandle = false);
    void DelayProcessOverlay(bool isUpdateMenu = true, bool animation = false, bool isShowMenu = true);
    SelectHandleInfo GetSelectHandleInfo(OffsetF info);
    void UpdateSelectOverlaySecondHandle(bool needLayout = false);
    void UpdateSelectOverlayDoubleHandle(bool firstNeedLayout = false, bool secondNeedLayout = false);

    // when moving one handle causes shift of textRect, update x position of the other handle
    void SetHandlerOnMoveDone();
    void OnDetachFromFrameNode(FrameNode* node) override;
    void UpdateSelectionByMouseDoubleClick();

    void AfterSelection();

    void FireEventHubOnChange(const std::string& text);
    void FireOnChangeIfNeeded();
    // The return value represents whether the editor content has change.
    bool FireOnTextChangeEvent();

    void FilterInitializeText();

    void UpdateSelection(int32_t both);
    void UpdateSelection(int32_t start, int32_t end);
    void FireOnSelectionChange(int32_t start, int32_t end);
    void UpdateCaretPositionByLastTouchOffset();
    bool UpdateCaretPosition();
    void UpdateCaretRect(bool isEditorValueChanged);
    void AdjustTextInReasonableArea();
    bool CharLineChanged(int32_t caretPosition);

    void ScheduleCursorTwinkling();
    void OnCursorTwinkling();
    void StartTwinkling();
    void CheckIfNeedToResetKeyboard();

    float PreferredTextHeight(bool isPlaceholder, bool isAlgorithmMeasure = false);

    void SetCaretOffsetForEmptyTextOrPositionZero();
    void UpdateTextFieldManager(const Offset& offset, float height);
    void OnTextInputActionUpdate(TextInputAction value);

    void Delete(int32_t start, int32_t end);
    void BeforeCreateLayoutWrapper() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    bool CursorInContentRegion();
    bool OffsetInContentRegion(const Offset& offset);
    void SetDisabledStyle();

    void CalculateDefaultCursor();
    void RequestKeyboardOnFocus();
    void SetNeedToRequestKeyboardOnFocus();
    void SaveUnderlineStates();
    void ApplyUnderlineStates();
    void SavePasswordModeStates();
    void SetAccessibilityAction();
    void SetAccessibilityMoveTextAction();
    void SetAccessibilityScrollAction();

    void UpdateCopyAllStatus();
    void SaveInlineStates();
    void ApplyInlineStates(bool focusStatus);
    void RestorePreInlineStates();
    void CalcInlineScrollRect(Rect& inlineScrollRect);

    bool ResetObscureTickCountDown();

    bool IsTouchAtLeftOffset(float currentOffsetX);
    void FilterExistText();
    void CreateErrorParagraph(const std::string& content);
    void UpdateErrorTextMargin();
    OffsetF GetTextPaintOffset() const;
    void UpdateSelectController();
    void UpdateHandlesOffsetOnScroll(float offset);
    void CloseHandleAndSelect() override;
    bool RepeatClickCaret(const Offset& offset, int32_t lastCaretIndex);
    void PaintTextRect();
    void GetIconPaintRect(const RefPtr<TextInputResponseArea>& responseArea, RoundRect& paintRect);
    void GetInnerFocusPaintRect(RoundRect& paintRect);
    void PaintResponseAreaRect();
    void PaintCancelRect();
    void PaintUnitRect();
    void PaintPasswordRect();
    bool CancelNodeIsShow()
    {
        auto cleanNodeArea = AceType::DynamicCast<CleanNodeResponseArea>(cleanNodeResponseArea_);
        CHECK_NULL_RETURN(cleanNodeArea, false);
        return cleanNodeArea->IsShow();
    }
    void CleanNodeResponseKeyEvent();
    void PasswordResponseKeyEvent();
    void UnitResponseKeyEvent();
#if defined(ENABLE_STANDARD_INPUT)
    std::optional<MiscServices::TextConfig> GetMiscTextConfig() const;
#endif
    bool IsSingleHandle() const;
    void SetIsSingleHandle(bool isSingleHandle)
    {
        isSingleHandle_ = isSingleHandle;
    }
    void NotifyOnEditChanged(bool isChanged);
    void StartRequestSelectOverlay(const ShowSelectOverlayParams& params, bool isShowPaste = false);
    void ProcessResponseArea();
    bool HasInputOperation();
    AceAutoFillType ConvertToAceAutoFillType(TextInputType type);
    bool CheckAutoFill();
    bool ProcessAutoFill();
    void ScrollToSafeArea() const override;
    void RecordSubmitEvent() const;
    void UpdateCancelNode();
    void MakeHighZIndex();
    void MakeZIndexRollBack();
    void GetMaxZIndex(const RefPtr<UINode>& parent, const RefPtr<FrameNode>& pattern);

    RectF frameRect_;
    RectF contentRect_;
    RectF textRect_;
    RefPtr<Paragraph> paragraph_;
    RefPtr<Paragraph> errorParagraph_;
    RefPtr<Paragraph> dragParagraph_;
    InlineMeasureItem inlineMeasureItem_;
    TextStyle nextLineUtilTextStyle_;

    RefPtr<ClickEvent> clickListener_;
    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<ScrollableEvent> scrollableEvent_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<InputEvent> hoverEvent_;
    RefPtr<LongPressEvent> longPressEvent_;
    CursorPositionType cursorPositionType_ = CursorPositionType::NORMAL;

    // What the keyboard should appears.
    TextInputType keyboard_ = TextInputType::UNSPECIFIED;
    // Action when "enter" pressed.
    TextInputAction action_ = TextInputAction::UNSPECIFIED;
    TextDirection textDirection_ = TextDirection::LTR;

    OffsetF parentGlobalOffset_;
    OffsetF lastTouchOffset_;
    PaddingPropertyF utilPadding_;
    OffsetF rightClickOffset_;

    BorderWidthProperty lastBorderWidth_;

    bool setBorderFlag_ = true;
    BorderWidthProperty lastDiffBorderWidth_;
    BorderColorProperty lastDiffBorderColor_;

    HandleMoveStatus handleMoveStatus_;
    bool cursorVisible_ = false;
    bool focusEventInitialized_ = false;
    bool isMousePressed_ = false;
    bool textObscured_ = true;
    bool enableTouchAndHoverEffect_ = true;
    bool isUsingMouse_ = false;
    bool isOnHover_ = false;
    bool needToRefreshSelectOverlay_ = false;
    bool needToRequestKeyboardInner_ = false;
    bool needToRequestKeyboardOnFocus_ = false;
    bool isTransparent_ = false;
    bool contChange_ = false;
    bool counterChange_ = false;
    WeakPtr<LayoutWrapper> counterTextNode_;
    bool hasCounterMargin_ = false;
    bool isCursorAlwaysDisplayed_ = false;
    std::optional<int32_t> surfaceChangedCallbackId_;
    std::optional<int32_t> surfacePositionChangedCallbackId_;

    SelectionMode selectionMode_ = SelectionMode::NONE;
    CaretUpdateType caretUpdateType_ = CaretUpdateType::NONE;
    bool scrollable_ = true;
    bool blockPress_ = false;
    float previewWidth_ = 0.0f;
    float lastTextRectY_ = 0.0f;
    std::optional<DisplayMode> barState_;
    InputStyle preInputStyle_ = InputStyle::DEFAULT;
    bool preErrorState_ = false;
    float preErrorMargin_ = 0.0f;
    bool restoreMarginState_ = false;

    uint32_t twinklingInterval_ = 0;
    int32_t obscureTickCountDown_ = 0;
    int32_t nakedCharPosition_ = -1;
    bool updateSelectionAfterObscure_ = false;
    float currentOffset_ = 0.0f;
    float countHeight_ = 0.0f;
    Dimension underlineWidth_ = 1.0_px;
    Color underlineColor_;
    bool scrollBarVisible_ = false;
    bool isCounterIdealheight_ = false;
    float maxFrameOffsetY_ = 0.0f;
    float maxFrameHeight_ = 0.0f;

    CancelableCallback<void()> cursorTwinklingTask_;

    std::list<std::unique_ptr<TextInputFormatter>> textInputFormatters_;

    RefPtr<TextFieldController> textFieldController_;
    RefPtr<TextEditController> textEditingController_;
    TextEditingValueNG textEditingValue_;
    // controls redraw of overlay modifier, update when need to redraw
    bool changeSelectedRects_ = false;
    RefPtr<TextFieldOverlayModifier> textFieldOverlayModifier_;
    RefPtr<TextFieldContentModifier> textFieldContentModifier_;
    ACE_DISALLOW_COPY_AND_MOVE(TextFieldPattern);

    int32_t dragTextStart_ = 0;
    int32_t dragTextEnd_ = 0;
    RefPtr<FrameNode> dragNode_;
    DragStatus dragStatus_ = DragStatus::NONE; // The status of the dragged initiator
    RefPtr<Clipboard> clipboard_;
    std::vector<TextEditingValueNG> operationRecords_;
    std::vector<TextEditingValueNG> redoOperationRecords_;
    std::vector<MenuOptionsParam> menuOptionItems_;
    BorderRadiusProperty borderRadius_;
    PasswordModeStyle passwordModeStyle_;
    SelectMenuInfo selectMenuInfo_;

    // inline
    bool isTextInput_ = false;
    bool inlineSelectAllFlag_ = false;
    bool inlineFocusState_ = false;
    float inlineSingleLineHeight_ = 0.0f;
    float inlinePadding_ = 0.0f;
    bool needApplyInlineSize_ = false;
    PreInlineState inlineState_;
    // inline --end

#if defined(ENABLE_STANDARD_INPUT)
    sptr<OHOS::MiscServices::OnTextChangedListener> textChangeListener_;
#else
    RefPtr<TextInputConnection> connection_;
#endif
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    bool imeAttached_ = false;
    bool imeShown_ = false;
#endif
    bool isFocusedBeforeClick_ = false;
    bool isCustomKeyboardAttached_ = false;
    std::function<void()> customKeyboardBuilder_;
    bool isCustomFont_ = false;
    bool hasClicked_ = false;
    bool isDoubleClick_ = false;
    TimeStamp lastClickTimeStamp_;
    float paragraphWidth_ = 0.0f;

    std::queue<int32_t> deleteBackwardOperations_;
    std::queue<int32_t> deleteForwardOperations_;
    std::queue<std::string> insertValueOperations_;
    std::queue<InputOperation> inputOperations_;
    bool leftMouseCanMove_ = false;
    bool isSingleHandle_ = true;
    bool showSelect_ = false;
    bool isLongPress_ = false;
    RefPtr<ContentController> contentController_;
    RefPtr<TextSelectController> selectController_;
    RefPtr<NG::UINode> unitNode_;
    RefPtr<TextInputResponseArea> responseArea_;
    RefPtr<TextInputResponseArea> cleanNodeResponseArea_;
    std::string lastAutoFillPasswordTextValue_;
    bool isSupportCameraInput_ = false;
    std::function<void()> processOverlayDelayTask_;
    FocuseIndex focusIndex_ = FocuseIndex::TEXT;
    bool isShowMagnifier_ = false;
    OffsetF localOffset_;
    bool isTouchCaret_ = false;
    std::list<int32_t> zIndexRollBack_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_PATTERN_H
