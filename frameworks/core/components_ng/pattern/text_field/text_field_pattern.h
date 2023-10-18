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
#include <stdint.h>
#include <string>
#include <utility>
#include <vector>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/rect.h"
#include "base/memory/referenced.h"
#include "base/mousestyle/mouse_style.h"
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
#include "core/gestures/gesture_info.h"

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

constexpr Dimension CURSOR_WIDTH = 1.5_vp;
constexpr Dimension SCROLL_BAR_MIN_HEIGHT = 4.0_vp;
constexpr Dimension UNDERLINE_WIDTH = 1.0_px;
constexpr Dimension ERROR_UNDERLINE_WIDTH = 2.0_px;
constexpr Dimension ACTIVED_UNDERLINE_WIDTH = 2.0_px;
constexpr Dimension TYPING_UNDERLINE_WIDTH = 2.0_px;
constexpr uint32_t INLINE_DEFAULT_VIEW_MAXLINE = 3;
constexpr float ERROR_TEXT_BOUNDSRECT_MARGIN = 33.0f;

enum class SelectionMode { SELECT, SELECT_ALL, NONE };

enum class DragStatus { DRAGGING, ON_DROP, NONE };

enum class CaretStatus { SHOW, HIDE, NONE };

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

class TextFieldPattern : public ScrollablePattern,
                         public TextDragBase,
                         public ValueChangeObserver,
                         public TextInputClient,
                         public TextBase {
    DECLARE_ACE_TYPE(TextFieldPattern, ScrollablePattern, TextDragBase, ValueChangeObserver, TextInputClient, TextBase);

public:
    TextFieldPattern();
    ~TextFieldPattern() override;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!textFieldContentModifier_) {
            textFieldContentModifier_ = AceType::MakeRefPtr<TextFieldContentModifier>(WeakClaim(this));
        }
        auto textFieldOverlayModifier = AceType::DynamicCast<TextFieldOverlayModifier>(GetScrollBarOverlayModifier());
        if (!textFieldOverlayModifier) {
            textFieldOverlayModifier =
                AceType::MakeRefPtr<TextFieldOverlayModifier>(WeakClaim(this), GetScrollEdgeEffect());
            SetScrollBarOverlayModifier(textFieldOverlayModifier);
        }
        if (isCustomFont_) {
            textFieldContentModifier_->SetIsCustomFont(true);
        }
        auto paint =
            MakeRefPtr<TextFieldPaintMethod>(WeakClaim(this), textFieldOverlayModifier, textFieldContentModifier_);
        auto scrollBar = GetScrollBar();
        if (scrollBar) {
            paint->SetScrollBar(scrollBar);
            if (scrollBar->NeedPaint()) {
                textFieldOverlayModifier->SetRect(scrollBar->GetActiveRect());
            }
        }
        auto host = GetHost();
        CHECK_NULL_RETURN(host, paint);
        auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_RETURN(layoutProperty, paint);
        auto geometryNode = host->GetGeometryNode();
        auto frameOffset = geometryNode->GetFrameOffset();
        auto frameSize = geometryNode->GetFrameSize();
        if (layoutProperty->GetShowErrorTextValue(false) && errorParagraph_) {
            auto contentOffset = geometryNode->GetContentOffset();
            auto errorTextWidth = errorParagraph_->GetLongestLine();
            RectF boundsRect(contentOffset.GetX(), frameOffset.GetY(), errorTextWidth,
                frameSize.Height() + ERROR_TEXT_BOUNDSRECT_MARGIN);
            textFieldOverlayModifier->SetBoundsRect(boundsRect);
        } else {
            if (NearEqual(maxFrameOffsetY_, 0.0f) && NearEqual(maxFrameHeight_, 0.0f)) {
                maxFrameOffsetY_ = frameOffset.GetY();
                maxFrameHeight_ = frameSize.Height();
            }
            maxFrameOffsetY_ = LessOrEqual(frameOffset.GetY(), maxFrameOffsetY_)
                                   ? frameOffset.GetY()
                                   : maxFrameOffsetY_ - frameOffset.GetY();
            maxFrameHeight_ = LessOrEqual(frameSize.Height(), maxFrameHeight_) ? maxFrameHeight_ : frameSize.Height();
            RectF boundsRect(frameOffset.GetX(), maxFrameOffsetY_, frameSize.Width(), maxFrameHeight_);
            textFieldOverlayModifier->SetBoundsRect(boundsRect);
        }
        return paint;
    }

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
        } else {
            return MakeRefPtr<TextInputLayoutAlgorithm>();
        }
    }

    void OnModifyDone() override;
    void UpdateSelectionOffset();
    void CalcCaretMetricsByPosition(
        int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity = TextAffinity::DOWNSTREAM);
    int32_t ConvertTouchOffsetToCaretPosition(const Offset& localOffset);
    int32_t ConvertTouchOffsetToCaretPositionNG(const Offset& localOffset);

    void InsertValue(const std::string& insertValue) override;
    void DeleteBackward(int32_t length) override;
    void DeleteForward(int32_t length) override;
    void UpdateRecordCaretIndex(int32_t index);
    void CreateHandles() override;

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

    const TextEditingValueNG& GetEditingValue() const;
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

    void UpdateEditingValue(const std::string& value, int32_t caretPosition)
    {
        contentController_->SetTextValue(value);
        selectController_->UpdateCaretIndex(caretPosition);
    }
    void SetEditingValueToProperty(const std::string& newValueText);
    void UpdateCaretPositionByTouch(const Offset& offset);
    bool IsReachedBoundary(float offset);

    virtual TextInputAction GetDefaultTextInputAction();
    bool RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard);
    bool CloseKeyboard(bool forceClose) override;

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true };
    }

    void PerformAction(TextInputAction action, bool forceCloseKeyboard = true) override;
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

    int32_t GetCaretIndex()
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

    bool DisplayPlaceHolder();

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

    void AdjustTextSelectionRectOffsetX();

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
        return textEditingValue_.ToString().length() > 1;
    }

    bool CursorMoveLeft() override;
    bool CursorMoveLeftWord();
    bool CursorMoveLineBegin();
    bool CursorMoveToParagraphBegin();
    bool CursorMoveHome();
    bool CursorMoveRight() override;
    bool CursorMoveRightWord();
    bool CursorMoveLineEnd();
    bool CursorMoveToParagraphEnd();
    bool CursorMoveEnd();
    bool CursorMoveUp() override;
    bool CursorMoveDown() override;
    void SetCaretPosition(int32_t position);
    void HandleSetSelection(int32_t start, int32_t end, bool showHandle = true) override;
    void HandleExtendAction(int32_t action) override;
    void HandleSelect(int32_t keyCode, int32_t cursorMoveSkip) override;
    OffsetF GetDragUpperLeftCoordinates() override;

    std::vector<RectF> GetTextBoxes() override
    {
        return selectController_->GetSelectedRects();
    }
    // void CaretMoveToLastNewLineChar();
    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;
    void FromJson(const std::unique_ptr<JsonValue>& json) override;
    void InitEditingValueText(std::string content);

    void CloseSelectOverlay() override;
    void CloseSelectOverlay(bool animation);
    void SetInputMethodStatus(bool keyboardShown) override
    {
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        imeShown_ = keyboardShown;
        if (!keyboardShown && isKeyboardClosedByUser_) {
            FocusHub::LostFocusToViewRoot();
        }
        isKeyboardClosedByUser_ = true;
#endif
    }
    std::u16string GetLeftTextOfCursor(int32_t number) override;
    std::u16string GetRightTextOfCursor(int32_t number) override;
    int32_t GetTextIndexAtCursor() override;

    bool HasConnection() const
    {
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        return imeAttached_;
#else
        return connection_;
#endif
    }
    float PreferredLineHeight();

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
        return layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::VISIBLE_PASSWORD &&
               layoutProperty->GetShowPasswordIconValue(true);
    }

    void SetEnableTouchAndHoverEffect(bool enable)
    {
        enableTouchAndHoverEffect_ = enable;
    }

    RectF GetCaretRect() const
    {
        return selectController_->GetCaretRect();
    }

    float GetIconRightOffset();
    float GetIconHotZoneSize();
    float GetIconSize();

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
    void OnCursorMoveDone();
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
        return true;
    }

    bool IsAtTop() const override
    {
        return true;
    }

    bool IsAtBottom() const override
    {
        return true;
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

    RefPtr<FrameNode> MoveDragNode() override
    {
        return std::move(dragNode_);
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
    bool OnBackPressed();
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
    void HandleOnUndoAction();
    void HandleOnRedoAction();
    void HandleOnSelectAll(bool isKeyEvent, bool inlineStyle = false);
    void HandleOnCopy();
    void HandleOnPaste();
    void HandleOnCut();
    void StripNextLine(std::wstring& data);
    bool OnKeyEvent(const KeyEvent& event);
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
    void SetUnitNode(const RefPtr<NG::UINode>& unitNode);
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
    void UpdateRectByAlignment(RectF& rect);

    void EditingValueFilterChange();

    void SetCustomKeyboard(const std::function<void()>&& keyboardBuilder)
    {
        if (customKeyboardBulder_ && isCustomKeyboardAttached_ && !keyboardBuilder) {
            CloseCustomKeyboard();
        }
        customKeyboardBulder_ = keyboardBuilder;
    }

    void DumpAdvanceInfo() override;
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

    bool IsFocus()
    {
        return HasFocus();
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
    bool CheckSelectionRectVisible() override;
    bool OnPreShowSelectOverlay(SelectOverlayInfo& overlayInfo, OverlayExtraInfo& extra) override;
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
        }
    }

    RefPtr<FrameNode> GetClientHost() const override
    {
        return GetHost();
    }

    void OnObscuredChanged(bool isObscured);

    void SetResponseArea(const RefPtr<TextInputResponseArea>& responseArea)
    {
        if (responseArea_) {
            responseArea_->DestoryArea();
            responseArea_.Reset();
        }
        responseArea_ = responseArea;
    }

    const RefPtr<TextInputResponseArea>& GetResponseArea()
    {
        return responseArea_;
    }

private:
    void GetTextSelectRectsInRangeAndWillChange();
    bool HasFocus() const;
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchDown(const Offset& offset);
    void HandleTouchUp();

    void InitFocusEvent();
    void InitTouchEvent();
    void InitLongPressEvent();
    void InitClickEvent();
#ifdef ENABLE_DRAG_FRAMEWORK
    void InitDragEvent();
    void InitDragDropEvent();
    std::function<DragDropInfo(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> OnDragStart();
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> OnDragDrop();
    void ClearDragDropEvent();
    std::function<void(Offset)> GetThumbnailCallback();
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
    void HandleMouseEvent(MouseInfo& info);
    void HandleRightMouseEvent(MouseInfo& info);
    void HandleLeftMouseEvent(MouseInfo& info);
    void HandleLeftMousePressEvent(MouseInfo& info);
    void HandleLeftMouseMoveEvent(MouseInfo& info);
    void HandleLeftMouseReleaseEvent(MouseInfo& info);
    void HandleLongPress(GestureEvent& info);
    void UpdateCaretPositionWithClamp(const int32_t& pos);
    void ShowSelectOverlay(const std::optional<RectF>& firstHandle, const std::optional<RectF>& secondHandle,
        bool animation = false, bool isMenuShow = true);

    void CursorMoveOnClick(const Offset& offset);
    void UpdateCaretInfoToController() const;

    void ProcessOverlay(bool animation = false, bool isShowMenu = true);
    SelectHandleInfo GetSelectHandleInfo(OffsetF info);
    void UpdateFirstHandlePosition(bool needLayout = false);
    void UpdateSecondHandlePosition(bool needLayout = false);
    void UpdateDoubleHandlePosition(bool firstNeedLayout = false, bool secondNeedLayout = false);

    // when moving one handle causes shift of textRect, update x position of the other handle
    void SetHandlerOnMoveDone();
    void OnDetachFromFrameNode(FrameNode* node) override;
    void UpdateSelectionByMouseDoubleClick();

    void AfterSelection();

    void FireEventHubOnChange(const std::string& text);
    void FireOnChangeIfNeeded();
    void FireOnTextChangeEvent();

    void FilterInitializeText();

    void UpdateSelection(int32_t both);
    void UpdateSelection(int32_t start, int32_t end);
    void FireOnSelectionChange(int32_t start, int32_t end);
    void UpdateCaretPositionByLastTouchOffset();
    bool UpdateCaretPosition();
    void UpdateCaretRect();
    void AdjustTextInReasonableArea();
    bool CharLineChanged(int32_t caretPosition);

    void ScheduleCursorTwinkling();
    void OnCursorTwinkling();
    void StartTwinkling();
    void StopTwinkling();
    void CheckIfNeedToResetKeyboard();

    float PreferredTextHeight(bool isPlaceholder);

    void SetCaretOffsetForEmptyTextOrPositionZero();
    void UpdateTextFieldManager(const Offset& offset, float height);
    void OnTextInputActionUpdate(TextInputAction value);

    void Delete(int32_t start, int32_t end);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    bool CursorInContentRegion();
    float FitCursorInSafeArea();
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
    void SetTextRectOffset();

    bool ResetObscureTickCountDown();
    bool IsInPasswordMode() const;
    bool IsTouchAtLeftOffset(float currentOffsetX);
    void FilterExistText();
    void UpdateErrorTextMargin();
    OffsetF GetTextPaintOffset() const;
    void UpdateSelectController();
#if defined(ENABLE_STANDARD_INPUT)
    std::optional<MiscServices::TextConfig> GetMiscTextConfig() const;
#endif
    bool IsSingleHandle() const;
    void SetIsSingleHandle(bool isSingleHandle)
    {
        isSingleHandle_ = isSingleHandle;
    }

    RectF frameRect_;
    RectF contentRect_;
    RectF textRect_;
    RefPtr<Paragraph> paragraph_;
    RefPtr<Paragraph> errorParagraph_;
    RefPtr<Paragraph> dragParagraph_;
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
    Dimension underlineWidth_ = UNDERLINE_WIDTH;
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
    std::vector<RectF> textBoxes_;
    // controls redraw of overlay modifier, update when need to redraw
    bool changeSelectedRects_ = false;
    RefPtr<TextFieldOverlayModifier> textFieldOverlayModifier_;
    RefPtr<TextFieldContentModifier> textFieldContentModifier_;
    ACE_DISALLOW_COPY_AND_MOVE(TextFieldPattern);

    int32_t dragTextStart_ = 0;
    int32_t dragTextEnd_ = 0;
    RefPtr<FrameNode> dragNode_;
    DragStatus dragStatus_ = DragStatus::NONE;          // The status of the dragged initiator
    DragStatus dragRecipientStatus_ = DragStatus::NONE; // Drag the recipient's state
    std::vector<std::string> dragContents_;
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
    std::function<void()> customKeyboardBulder_;
    bool isCustomFont_ = false;
    bool hasClicked_ = false;
    bool isDoubleClick_ = false;
    TimeStamp lastClickTimeStamp_;
    float paragraphWidth_ = 0.0f;

    bool leftMouseCanMove_ = false;
    bool isSingleHandle_ = true;
    RefPtr<ContentController> contentController_;
    RefPtr<TextSelectController> selectController_;
    CaretStatus caretStatus_ = CaretStatus::NONE;
    RefPtr<TextInputResponseArea> responseArea_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_PATTERN_H
