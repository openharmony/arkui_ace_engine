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
#include <string>
#include <utility>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
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

#if defined(ENABLE_STANDARD_INPUT)
#include "commonlibrary/c_utils/base/include/refbase.h"

namespace OHOS::MiscServices {
class OnTextChangedListener;
} // namespace OHOS::MiscServices
#endif

namespace OHOS::Ace::NG {

constexpr Dimension CURSOR_WIDTH = 1.5_vp;

enum class SelectionMode { SELECT, SELECT_ALL, NONE };

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

class TextFieldPattern : public Pattern, public ValueChangeObserver {
    DECLARE_ACE_TYPE(TextFieldPattern, Pattern, ValueChangeObserver);

public:
    TextFieldPattern();
    ~TextFieldPattern() override;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<TextFieldPaintMethod>(WeakClaim(this));
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

    CaretMetricsF CalcCursorOffsetByPosition(int32_t position);

    bool ComputeOffsetForCaretDownstream(int32_t extent, CaretMetricsF& result);

    bool ComputeOffsetForCaretUpstream(int32_t extent, CaretMetricsF& result) const;

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
    void UpdateEditingValue(std::string value, int32_t caretPosition)
    {
        textEditingValue_.text = std::move(value);
        textEditingValue_.caretPosition = caretPosition;
    }
    void SetEditingValueToProperty(const std::string& newValueText);

    void UpdatePositionOfParagraph(int32_t pos);
    void UpdateCaretPositionByTouch(const Offset& offset);
    void UpdateCaretOffsetByEvent();

    bool RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard);
    bool CloseKeyboard(bool forceClose);

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true, FocusStyleType::INNER_BORDER };
    }

    void UpdateConfiguration();
    void PerformAction(TextInputAction action, bool forceCloseKeyboard = true);
    void OnValueChanged(bool needFireChangeEvent = true, bool needFireSelectChangeEvent = true) override;

    void OnAreaChangedInner() override;
    void OnVisibleChange(bool isVisible) override;
    void ClearEditingValue();

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(TextInputAction, TextInputAction)

    float GetBaseLineOffset() const
    {
        return baselineOffset_;
    }

    const std::shared_ptr<RSParagraph>& GetParagraph() const
    {
        return paragraph_;
    }

    bool GetCursorVisible() const
    {
        return cursorVisible_;
    }

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

    const RectF& GetTextRect()
    {
        return textRect_;
    }

    const RectF& GetFrameRect()
    {
        return frameRect_;
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

    bool InSelectMode() const
    {
        return selectionMode_ != SelectionMode::NONE && !textSelector_.StartEqualToDest();
    }

    bool IsUsingMouse() const
    {
        return isUsingMouse_;
    }

    void CursorMoveLeft();
    void CursorMoveRight();
    void CursorMoveUp();
    void CursorMoveDown();
    void SetCaretPosition(int32_t position);
    void HandleSetSelection(int32_t start, int32_t end);
    void HandleExtendAction(int32_t action);
    void HandleSelect(int32_t keyCode, int32_t cursorMoveSkip);

    const std::vector<RSTypographyProperties::TextBox>& GetTextBoxes()
    {
        return textBoxes_;
    }
    void CaretMoveToLastNewLineChar();
    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;
    void InitEditingValueText(std::string content);
    void InitCaretPosition(std::string content);
    const TextEditingValueNG& GetTextEditingValue()
    {
        return textEditingValue_;
    }

    bool SelectOverlayIsOn();
    void CloseSelectOverlay();
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    void SetInputMethodStatus(bool imeAttached)
    {
        imeAttached_ = imeAttached;
    }

#endif
    bool HasConnection() const
    {
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        return imeAttached_;
#endif
        return false;
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
    bool IsTextArea() const;
    const RectF& GetImageRect()
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

    void SetEnableTouchAndHoverEffect(bool enable)
    {
        enableTouchAndHoverEffect_ = enable;
    }

    const RectF& GetCaretRect()
    {
        return caretRect_;
    }

    void UpdateCaretRectByPosition(int32_t position);
    float GetIconRightOffset();
    float GetIconHotZoneSize();
    float GetIconSize();

    void HandleSurfaceChanged(int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight) const;
    void HandleSurfacePositionChanged(int32_t posX, int32_t posY) const;

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
    void UpdateEditingValueToRecord();

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
    std::string GetInputFilter() const;

    void HandleSelectionUp();
    void HandleSelectionDown();
    void HandleSelectionLeft();
    void HandleSelectionRight();

    void HandleOnUndoAction();
    void HandleOnRedoAction();
    void HandleOnSelectAll();
    void HandleOnCopy();
    void HandleOnPaste();
    void HandleOnCut();
    bool OnKeyEvent(const KeyEvent& event);
    
    TextInputType GetKeyboard()
    {
        return keyboard_;
    }
    TextInputAction GetAction()
    {
        return action_;
    }

private:
    void HandleBlurEvent();
    bool HasFocus() const;
    void HandleFocusEvent();
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchDown(const Offset& offset);
    void HandleTouchUp();
    void HandleClickEvent(GestureEvent& info);

    void InitFocusEvent();
    void InitTouchEvent();
    void InitLongPressEvent();
    void InitClickEvent();
    bool CaretPositionCloseToTouchPosition();
    void CreateSingleHandle();
    int32_t UpdateCaretPositionOnHandleMove(const OffsetF& localOffset);

    void AddScrollEvent();
    void OnTextAreaScroll(float dy);
    void InitMouseEvent();
    void OnHover(bool isHover);
    void HandleMouseEvent(MouseInfo& info);
    void HandleLongPress(GestureEvent& info);
    void ShowSelectOverlay(const std::optional<RectF>& firstHandle, const std::optional<RectF>& secondHandle);

    void CursorMoveOnClick(const Offset& offset);
    void UpdateCaretInfoToController() const;

    void ProcessOverlay();
    void OnHandleMove(const RectF& handleRect, bool isFirstHandle);
    void OnHandleMoveDone(const RectF& handleRect, bool isFirstHandle);
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
    void UpdateDestinationToCaretByEvent();
    void UpdateCaretOffsetByLastTouchOffset();
    bool UpdateCaretPositionByMouseMovement();
    bool UpdateCaretPosition();
    int32_t GetLineNumber(float offsetY);

    void ScheduleCursorTwinkling();
    void OnCursorTwinkling();
    void StartTwinkling();
    void StopTwinkling();

    float PreferredTextHeight(bool isPlaceholder);

    void SetCaretOffsetForEmptyTextOrPositionZero();
    void UpdateTextFieldManager(const Offset& offset, float height);
    void OnTextInputActionUpdate(TextInputAction value);

    void Delete(int32_t start, int32_t end);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    bool FilterWithRegex(
        const std::string& filter, const std::string& valueToUpdate, std::string& result, bool needToEscape = false);
    void EditingValueFilter(std::string& valueToUpdate, std::string& result);
    void GetTextRectsInRange(int32_t begin, int32_t end, std::vector<RSTypographyProperties::TextBox>& textBoxes);
    bool CursorInContentRegion();
    bool OffsetInContentRegion(const Offset& offset);
    void SetDisabledStyle();
    void ResetBackgroundColor();
    void AnimatePressAndHover(RefPtr<RenderContext>& renderContext, float endOpacity, bool isHoverChange = false);

    void ProcessPasswordIcon();
    void UpdateInternalResource(ImageSourceInfo& sourceInfo);
    ImageSourceInfo GetImageSourceInfoFromTheme(bool checkHidePasswordIcon);
    LoadSuccessNotifyTask CreateLoadSuccessCallback(bool checkHidePasswordIcon);
    DataReadyNotifyTask CreateDataReadyCallback(bool checkHidePasswordIcon);
    LoadFailNotifyTask CreateLoadFailCallback(bool checkHidePasswordIcon);
    void OnImageDataReady(bool checkHidePasswordIcon);
    void OnImageLoadSuccess(bool checkHidePasswordIcon);
    void OnImageLoadFail(bool checkHidePasswordIcon);

    bool IsSearchParentNode();

    RectF frameRect_;
    RectF contentRect_;
    RectF textRect_;
    RectF imageRect_;
    std::shared_ptr<RSParagraph> paragraph_;
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

    bool isSingleHandle_ = false;
    bool isFirstHandle_ = false;
    float baselineOffset_ = 0.0f;
    RectF caretRect_;
    bool cursorVisible_ = false;
    bool focusEventInitialized_ = false;
    bool isMousePressed_ = false;
    MouseStatus mouseStatus_ = MouseStatus::NONE;
    bool needCloseOverlay_ = true;
    bool textObscured_ = true;
    bool enableTouchAndHoverEffect_ = true;
    bool isUsingMouse_ = false;
    bool isOnHover_ = false;
    std::optional<int32_t> surfaceChangedCallbackId_;
    std::optional<int32_t> surfacePositionChangedCallbackId_;

    SelectionMode selectionMode_ = SelectionMode::NONE;
    CaretUpdateType caretUpdateType_ = CaretUpdateType::NONE;
    uint32_t twinklingInterval_ = 0;
    int32_t obscureTickCountDown_ = 0;

    CancelableCallback<void()> cursorTwinklingTask_;

    std::list<std::unique_ptr<TextInputFormatter>> textInputFormatters_;

    RefPtr<TextFieldController> textFieldController_;
    RefPtr<TextEditController> textEditingController_;
    TextEditingValueNG textEditingValue_;
    TextSelector textSelector_;
    RefPtr<SelectOverlayProxy> selectOverlayProxy_;
    std::vector<RSTypographyProperties::TextBox> textBoxes_;
    ACE_DISALLOW_COPY_AND_MOVE(TextFieldPattern);

    RefPtr<Clipboard> clipboard_;
    std::vector<TextEditingValueNG> operationRecords_;
    std::vector<TextEditingValueNG> redoOperationRecords_;
    std::vector<TextSelector> textSelectorRecords_;
    std::vector<TextSelector> redoTextSelectorRecords_;
#if defined(ENABLE_STANDARD_INPUT)
    sptr<OHOS::MiscServices::OnTextChangedListener> textChangeListener_;

#endif
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    bool imeAttached_ = false;
#endif
    int32_t instanceId_ = -1;
#if defined(PREVIEW)
    std::vector<std::wstring> clipRecords_;
#endif
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_PATTERN_H