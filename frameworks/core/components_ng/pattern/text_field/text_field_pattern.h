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
#include <string>
#include <utility>
#include <vector>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/rect.h"
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
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/text_menu_extension.h"
#include "core/components_ng/pattern/text_drag/text_drag_base.h"
#include "core/components_ng/pattern/text_field/text_editing_value_ng.h"
#include "core/components_ng/pattern/text_field/text_field_accessibility_property.h"
#include "core/components_ng/pattern/text_field/text_field_controller.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_paint_method.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/property/property.h"
#include "core/gestures/gesture_info.h"
#ifdef USE_GRAPHIC_TEXT_GINE
#include "rosen_text/typography.h"
#endif

#if not defined(ACE_UNITTEST)
#if defined(ENABLE_STANDARD_INPUT)
#include "commonlibrary/c_utils/base/include/refbase.h"

namespace OHOS::MiscServices {
class OnTextChangedListener;
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

enum class SelectionMode { SELECT, SELECT_ALL, NONE };

enum class DragStatus { DRAGGING, ON_DROP, NONE };

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

struct CaretMetricsF {
    void Reset()
    {
        offset.Reset();
        height = 0.0;
    }

    OffsetF offset;
    // When caret is close to different glyphs, the height will be different.
    float height = 0.0;
    std::string ToString() const
    {
        std::string result = "Offset: ";
        result += offset.ToString();
        result += ", height: ";
        result += std::to_string(height);
        return result;
    }
};

struct PasswordModeStyle {
    Color bgColor;
    Color textColor;
    BorderWidthProperty borderwidth;
    BorderColorProperty borderColor;
    BorderRadiusProperty radius;
    PaddingProperty padding;
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
        auto paint =
            MakeRefPtr<TextFieldPaintMethod>(WeakClaim(this), textFieldOverlayModifier, textFieldContentModifier_);
        auto scrollBar = GetScrollBar();
        if (scrollBar) {
            paint->SetScrollBar(scrollBar);
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
        return MakeRefPtr<TextFieldLayoutAlgorithm>();
    }

    void OnModifyDone() override;
    int32_t GetInstanceId() const
    {
        return instanceId_;
    }

    void UpdateCaretPositionByTextEdit();
    void UpdateCaretPositionByPressOffset();
    void UpdateSelectionOffset();

    CaretMetricsF CalcCursorOffsetByPosition(int32_t position, bool isStart = true);

    bool ComputeOffsetForCaretDownstream(int32_t extent, CaretMetricsF& result);

    bool ComputeOffsetForCaretUpstream(int32_t extent, CaretMetricsF& result) const;

    uint32_t GetDrawOverlayFlag() const
    {
        return drawOverlayFlag_;
    }

    OffsetF MakeEmptyOffset() const;

    int32_t ConvertTouchOffsetToCaretPosition(const Offset& localOffset);

    void InsertValue(const std::string& insertValue);
    void DeleteBackward(int32_t length);
    void DeleteForward(int32_t length);

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

    void UpdateEditingValue(std::string value, int32_t caretPosition)
    {
        textEditingValue_.text = std::move(value);
        textEditingValue_.caretPosition = caretPosition;
    }
    void SetEditingValueToProperty(const std::string& newValueText);

    void UpdatePositionOfParagraph(int32_t pos);
    void UpdateCaretPositionByTouch(const Offset& offset);
    void UpdateCaretOffsetByEvent();

    TextInputAction GetDefaultTextInputAction();
    bool RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard);
    bool CloseKeyboard(bool forceClose) override;

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true };
    }

    void PerformAction(TextInputAction action, bool forceCloseKeyboard = true) override;
    void UpdateEditingValue(const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent = true) override;

    void OnValueChanged(bool needFireChangeEvent = true, bool needFireSelectChangeEvent = true) override;

    void OnAreaChangedInner() override;
    void OnVisibleChange(bool isVisible) override;
    void ClearEditingValue();
    void HandleCounterBorder();

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(TextInputAction, TextInputAction)

    float GetBaseLineOffset() const
    {
        return baselineOffset_;
    }

    const std::shared_ptr<RSParagraph>& GetParagraph() const
    {
        return paragraph_;
    }

    const std::shared_ptr<RSParagraph>& GetCounterParagraph() const
    {
        return counterParagraph_;
    }

    const std::shared_ptr<RSParagraph>& GetErrorParagraph() const
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

    const Offset& GetLastTouchOffset()
    {
        return lastTouchOffset_;
    }

    const OffsetF& GetRightClickOffset()
    {
        return rightClickOffset_;
    }

    float GetSelectionBaseOffsetX() const
    {
        return textSelector_.selectionBaseOffset.GetX();
    }

    float GetSelectionDestinationOffsetX() const
    {
        return textSelector_.selectionDestinationOffset.GetX();
    }

    OffsetF GetCaretOffset() const
    {
        return OffsetF(caretRect_.GetX(), caretRect_.GetY());
    }

    float GetCaretOffsetX() const
    {
        return caretRect_.GetX();
    }

    void SetCaretOffsetX(float offsetX)
    {
        caretRect_.SetLeft(offsetX);
    }

    const RefPtr<SelectOverlayProxy>& GetSelectOverlay()
    {
        return selectOverlayProxy_;
    }

    void SetSelectOverlay(const RefPtr<SelectOverlayProxy>& proxy)
    {
        selectOverlayProxy_ = proxy;
    }

    CaretUpdateType GetCaretUpdateType() const
    {
        return caretUpdateType_;
    }

    void SetCaretUpdateType(CaretUpdateType type)
    {
        caretUpdateType_ = type;
    }

    float AdjustTextRectOffsetX();
    float AdjustTextAreaOffsetY();
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

    float GetHorizontalPaddingSum() const
    {
        return utilPadding_.left.value_or(0.0f) + utilPadding_.right.value_or(0.0f);
    }

    float GetVerticalPaddingSum() const
    {
        return utilPadding_.top.value_or(0.0f) + utilPadding_.bottom.value_or(0.0f);
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

    const TextSelector& GetTextSelector()
    {
        return textSelector_;
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
        return selectionMode_ != SelectionMode::NONE && !textSelector_.StartEqualToDest();
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
        if (textEditingValue_.ToString().length() > 1) {
            return true;
        }
        return false;
    }

    bool CursorMoveLeft();
    bool CursorMoveLeftWord();
    bool CursorMoveLineBegin();
    bool CursorMoveToParagraphBegin();
    bool CursorMoveHome();
    bool CursorMoveRight();
    bool CursorMoveRightWord();
    bool CursorMoveLineEnd();
    bool CursorMoveToParagraphEnd();
    bool CursorMoveEnd();
    bool CursorMoveUp();
    bool CursorMoveDown();
    void SetCaretPosition(int32_t position);
    void SetTextSelection(int32_t selectionStart, int32_t selectionEnd);
    void HandleSetSelection(int32_t start, int32_t end, bool showHandle = true);
    void HandleExtendAction(int32_t action);
    void HandleSelect(int32_t keyCode, int32_t cursorMoveSkip);

#ifndef USE_GRAPHIC_TEXT_GINE
    std::vector<RSTypographyProperties::TextBox> GetTextBoxes() override
#else
    std::vector<RSTextRect> GetTextBoxes() override
#endif
    {
        return textBoxes_;
    }
    void CaretMoveToLastNewLineChar();
    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;
    void FromJson(const std::unique_ptr<JsonValue>& json) override;
    void InitEditingValueText(std::string content);
    void InitCaretPosition(std::string content);
    const TextEditingValueNG& GetTextEditingValue()
    {
        return textEditingValue_;
    }

    bool SelectOverlayIsOn();
    void CloseSelectOverlay() override;
    void CloseSelectOverlay(bool animation);
    void SetInputMethodStatus(bool keyboardShown)
    {
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        imeShown_ = keyboardShown;
#endif
    }
    std::u16string GetLeftTextOfCursor(int32_t number);
    std::u16string GetRightTextOfCursor(int32_t number);
    int32_t GetTextIndexAtCursor();

    bool HasConnection() const
    {
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        return imeAttached_;
#else
        return connection_;
#endif
    }
    float PreferredLineHeight();
    void SetNeedCloseOverlay(bool needClose)
    {
        needCloseOverlay_ = needClose;
    }
    const RefPtr<ImageLoadingContext>& GetShowPasswordIconCtx() const
    {
        return showPasswordImageLoadingCtx_;
    }

    void SearchRequestKeyboard();

    const RefPtr<CanvasImage>& GetShowPasswordIconCanvasImage() const
    {
        return showPasswordCanvasImage_;
    }

    const RefPtr<ImageLoadingContext>& GetHidePasswordIconCtx() const
    {
        return hidePasswordImageLoadingCtx_;
    }

    const RefPtr<CanvasImage>& GetHidePasswordIconCanvasImage() const
    {
        return hidePasswordCanvasImage_;
    }

    bool GetTextObscured() const
    {
        return textObscured_;
    }

    void SetTextObscured(bool obscured)
    {
        textObscured_ = obscured;
    }

    static std::u16string CreateObscuredText(int32_t len);
    static std::u16string CreateDisplayText(
        const std::string& content, int32_t nakedCharPosition, bool needObscureText);
    bool IsTextArea() const override;
    const RectF& GetImageRect() const
    {
        return imageRect_;
    }

    const RefPtr<TouchEventImpl>& GetTouchListener()
    {
        return touchListener_;
    }

    bool NeedShowPasswordIcon()
    {
        auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_RETURN_NOLOG(layoutProperty, false);
        return layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::VISIBLE_PASSWORD &&
               layoutProperty->GetShowPasswordIconValue(true);
    }

    void SetShowUserDefinedIcon(bool enable)
    {
        showUserDefinedIcon_ = enable;
    }

    void SetHideUserDefinedIcon(bool enable)
    {
        hideUserDefinedIcon_ = enable;
    }

    void SetEnableTouchAndHoverEffect(bool enable)
    {
        enableTouchAndHoverEffect_ = enable;
    }

    const RectF& GetCaretRect() const
    {
        return caretRect_;
    }

    void UpdateCaretRectByPosition(int32_t position);
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
        return caretRect_.Height();
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

    void CreateHandles() override;

    void CreateHandles(bool animation);

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
        for (const auto& textBoxes : textBoxes_) {
#ifndef USE_GRAPHIC_TEXT_GINE
            bool isInRange = LessOrEqual(textBoxes.rect_.GetLeft(), offset.GetX()) &&
                             LessOrEqual(offset.GetX(), textBoxes.rect_.GetRight()) &&
                             LessOrEqual(textBoxes.rect_.GetTop(), offset.GetY()) &&
                             LessOrEqual(offset.GetY(), textBoxes.rect_.GetBottom());
#else
            bool isInRange = LessOrEqual(textBoxes.rect.GetLeft(), offset.GetX()) &&
                             LessOrEqual(offset.GetX(), textBoxes.rect.GetRight()) &&
                             LessOrEqual(textBoxes.rect.GetTop(), offset.GetY()) &&
                             LessOrEqual(offset.GetY(), textBoxes.rect.GetBottom());
#endif
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
    static int32_t GetGraphemeClusterLength(const std::wstring& text, int32_t extend, bool checkPrev = false);
    void SetUnitNode(const RefPtr<NG::UINode>& unitNode);
    void SetShowError();

    float GetUnitWidth() const
    {
        return unitWidth_;
    }

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
        return abs(textSelector_.GetStart() - textSelector_.GetEnd()) >=
               static_cast<int32_t>(StringUtils::ToWstring(textEditingValue_.text).length());
    }

    SelectMenuInfo GetSelectMenuInfo() const
    {
        return selectMenuInfo_;
    }

    void UpdateSelectMenuInfo(bool hasData)
    {
        selectMenuInfo_.showCopy = !GetEditingValue().text.empty() && AllowCopy() && IsSelected();
        selectMenuInfo_.showCut = selectMenuInfo_.showCopy && !GetEditingValue().text.empty() && IsSelected();
        selectMenuInfo_.showCopyAll = !GetEditingValue().text.empty() && !IsSelectAll();
        selectMenuInfo_.showPaste = hasData;
        selectMenuInfo_.menuIsShow = !GetEditingValue().text.empty() || hasData;
    }

    bool IsSearchParentNode() const;

    void MarkRedrawOverlay()
    {
        ++drawOverlayFlag_;
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

    bool GetContChange()
    {
        return contChange_;
    }
    std::string GetShowResultImageSrc() const;
    std::string GetHideResultImageSrc() const;
    void OnAttachToFrameNode() override
    {
        caretUpdateType_ = CaretUpdateType::EVENT;
    }

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

    void ResetTouchAtLeftOffsetFlag()
    {
        isTouchAtLeftOffset_ = true;
    }

    bool IsNormalInlineState() const;
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

    void DumpInfo() override;

private:
    bool HasFocus() const;
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchDown(const Offset& offset);
    void HandleTouchUp();

    void InitFocusEvent();
    void InitTouchEvent();
    void InitLongPressEvent();
    void InitClickEvent();
#ifdef ENABLE_DRAG_FRAMEWORK
    void InitDragDropEvent();
    std::function<void(Offset)> GetThumbnailCallback();
#endif
    bool CaretPositionCloseToTouchPosition();
    void CreateSingleHandle(bool animation = false, bool isMenuShow = true);
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
    void HandleLongPress(GestureEvent& info);
    void UpdateCaretPositionWithClamp(const int32_t& pos);
    void UpdateSelectorByPosition(const int32_t& pos);
    // assert handles are inside the contentRect, reset them if not
    void CheckHandles(std::optional<RectF>& firstHandle, std::optional<RectF>& secondHandle,
        float firstHandleSize = 0.0f, float secondHandleSize = 0.0f);
    void ShowSelectOverlay(const std::optional<RectF>& firstHandle, const std::optional<RectF>& secondHandle,
        bool animation = false, bool isMenuShow = true);

    void CursorMoveOnClick(const Offset& offset);
    void UpdateCaretInfoToController() const;

    void ProcessOverlay(bool animation = false);
    void OnHandleMove(const RectF& handleRect, bool isFirstHandle);
    void OnHandleMoveDone(const RectF& handleRect, bool isFirstHandle);
    // when moving one handle causes shift of textRect, update x position of the other handle
    void UpdateOtherHandleOnMove(float dx, float dy);
    void SetHandlerOnMoveDone();
    void OnDetachFromFrameNode(FrameNode* node) override;
    bool UpdateCaretByPressOrLongPress();
    void UpdateTextSelectorByHandleMove(bool isMovingBase, int32_t position, OffsetF& offsetToParagraphBeginning);
    void UpdateCaretByRightClick();

    void AfterSelection();

    void FireEventHubOnChange(const std::string& text);
    void FireOnChangeIfNeeded();

    void UpdateSelection(int32_t both);
    void UpdateSelection(int32_t start, int32_t end);
    void FireOnSelectionChange(int32_t start, int32_t end);
    void UpdateDestinationToCaretByEvent();
    void UpdateCaretOffsetByLastTouchOffset();
    bool UpdateCaretPositionByMouseMovement();
    bool UpdateCaretPosition();
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

    bool FilterWithRegex(
        const std::string& filter, const std::string& valueToUpdate, std::string& result, bool needToEscape = false);
    bool FilterWithAscii(const std::string& valueToUpdate, std::string& result);
    void EditingValueFilter(std::string& valueToUpdate, std::string& result, bool isInsertValue = false);
#ifndef USE_GRAPHIC_TEXT_GINE
    bool LastTouchIsInSelectRegion(const std::vector<RSTypographyProperties::TextBox>& boxes);
    void GetTextRectsInRange(int32_t begin, int32_t end, std::vector<RSTypographyProperties::TextBox>& textBoxes);
#else
    bool LastTouchIsInSelectRegion(const std::vector<RSTextRect>& boxes);
    void GetTextRectsInRange(int32_t begin, int32_t end, std::vector<RSTextRect>& textBoxes);
#endif
    bool CursorInContentRegion();
    float FitCursorInSafeArea();
    bool OffsetInContentRegion(const Offset& offset);
    void SetDisabledStyle();

    void ProcessPasswordIcon();
    void UpdateUserDefineResource(ImageSourceInfo& sourceInfo);
    void UpdateInternalResource(ImageSourceInfo& sourceInfo);
    ImageSourceInfo GetImageSourceInfoFromTheme(bool checkHidePasswordIcon);
    LoadSuccessNotifyTask CreateLoadSuccessCallback(bool checkHidePasswordIcon);
    DataReadyNotifyTask CreateDataReadyCallback(bool checkHidePasswordIcon);
    LoadFailNotifyTask CreateLoadFailCallback(bool checkHidePasswordIcon);
    void OnImageDataReady(bool checkHidePasswordIcon);
    void OnImageLoadSuccess(bool checkHidePasswordIcon);
    void OnImageLoadFail(bool checkHidePasswordIcon);
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
    bool CheckHandleVisible(const RectF& paintRect);
    void SetTextRectOffset();

    bool ResetObscureTickCountDown();
    bool IsInPasswordMode() const;
#ifndef USE_GRAPHIC_TEXT_GINE
    void GetWordBoundaryPositon(int32_t offset, int32_t& start, int32_t& end);
#endif
    bool IsTouchAtLeftOffset(float currentOffsetX);
    void FilterExistText();
    void UpdateErrorTextMargin();

    RectF frameRect_;
    RectF contentRect_;
    RectF textRect_;
    RectF imageRect_;
    std::shared_ptr<RSParagraph> paragraph_;
    std::shared_ptr<RSParagraph> counterParagraph_;
    std::shared_ptr<RSParagraph> errorParagraph_;
    std::shared_ptr<RSParagraph> dragParagraph_;
    std::shared_ptr<RSParagraph> textLineHeightUtilParagraph_;
    std::shared_ptr<RSParagraph> placeholderLineHeightUtilParagraph_;
    TextStyle nextLineUtilTextStyle_;
    std::shared_ptr<RSParagraph> nextLineUtilParagraph_;

    RefPtr<ImageLoadingContext> showPasswordImageLoadingCtx_;
    RefPtr<ImageLoadingContext> hidePasswordImageLoadingCtx_;

    // password icon image related
    RefPtr<CanvasImage> showPasswordCanvasImage_;
    RefPtr<CanvasImage> hidePasswordCanvasImage_;

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
    Offset lastTouchOffset_;
    PaddingPropertyF utilPadding_;
    OffsetF rightClickOffset_;
    OffsetF offsetDifference_;

    BorderWidthProperty lastBorderWidth_;

    bool setBorderFlag_ = true;
    BorderWidthProperty lastDiffBorderWidth_;
    BorderColorProperty lastDiffBorderColor_;

    bool showUserDefinedIcon_ = false;
    bool hideUserDefinedIcon_ = false;
    bool isSingleHandle_ = false;
    bool isFirstHandle_ = false;
    float baselineOffset_ = 0.0f;
    // relative to frameRect
    RectF caretRect_;
    bool cursorVisible_ = false;
    bool focusEventInitialized_ = false;
    bool isMousePressed_ = false;
    bool needCloseOverlay_ = true;
#if defined(ENABLE_STANDARD_INPUT) || defined(PREVIEW)
    bool textObscured_ = true;
#else
    bool textObscured_ = false;
#endif
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
    float paragraphWidth_ = 0.0f;

    SelectionMode selectionMode_ = SelectionMode::NONE;
    CaretUpdateType caretUpdateType_ = CaretUpdateType::NONE;
    bool setSelectionFlag_ = false;
    bool scrollable_ = true;
    int32_t selectionStart_ = 0;
    int32_t selectionEnd_ = 0;
    // controls redraw of overlay modifier, update when need to redraw
    int32_t drawOverlayFlag_ = 0;
    bool isTextInput_ = false;
    bool inlineSelectAllFlag_ = false;
    bool inlineFocusState_ = false;
    bool blockPress_ = false;
    float inlineSingleLineHeight_ = 0.0f;
    float inlinePadding_ = 0.0f;
    float previewWidth_ = 0.0f;
    float lastTextRectY_ = 0.0f;
    std::optional<DisplayMode> barState_;
    InputStyle preInputStyle_ = InputStyle::DEFAULT;
    bool preErrorState_ = false;
    float preErrorMargin_ = 0.0f;

    uint32_t twinklingInterval_ = 0;
    int32_t obscureTickCountDown_ = 0;
    int32_t nakedCharPosition_ = -1;
    bool updateSelectionAfterObscure_ = false;
    float currentOffset_ = 0.0f;
    float unitWidth_ = 0.0f;
    float countHeight_ = 0.0f;
    Dimension underlineWidth_ = UNDERLINE_WIDTH;
    Color underlineColor_;
    bool scrollBarVisible_ = false;

    CancelableCallback<void()> cursorTwinklingTask_;

    std::list<std::unique_ptr<TextInputFormatter>> textInputFormatters_;

    RefPtr<TextFieldController> textFieldController_;
    RefPtr<TextEditController> textEditingController_;
    TextEditingValueNG textEditingValue_;
    RefPtr<SelectOverlayProxy> selectOverlayProxy_;
#ifndef USE_GRAPHIC_TEXT_GINE
    std::vector<RSTypographyProperties::TextBox> textBoxes_;
#else
    std::vector<RSTextRect> textBoxes_;
#endif
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
    std::vector<TextSelector> textSelectorRecords_;
    std::vector<TextSelector> redoTextSelectorRecords_;
    std::vector<MenuOptionsParam> menuOptionItems_;
    BorderRadiusProperty borderRadius_;
    PasswordModeStyle passwordModeStyle_;
    PreInlineState inlineState_;

    SelectMenuInfo selectMenuInfo_;

#if defined(ENABLE_STANDARD_INPUT)
    sptr<OHOS::MiscServices::OnTextChangedListener> textChangeListener_;
#else
    RefPtr<TextInputConnection> connection_;
#endif
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    bool imeAttached_ = false;
    bool imeShown_ = false;
#endif
    int32_t instanceId_ = -1;
    bool isFocusedBeforeClick_ = false;
    bool originalIsMenuShow_ = false;
    bool isCustomKeyboardAttached_ = false;
    std::function<void()> customKeyboardBulder_;
    bool isTouchAtLeftOffset_ = true;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_PATTERN_H
