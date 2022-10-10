/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "base/geometry/ng/offset_t.h"
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
#include "core/components_ng/pattern/text_field/text_field_controller.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_paint_method.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/drawing.h"

#if defined(ENABLE_STANDARD_INPUT)
#include "commonlibrary/c_utils/base/include/refbase.h"

namespace OHOS::MiscServices {
class OnTextChangedListener;
}
#endif

namespace OHOS::Ace::NG {

enum class SelectionMode { SELECT, SELECT_ALL, NONE };

enum class CaretUpdateType { CLICK, EVENT, INPUT, NONE };

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
    void UpdateCaretPositionByTouchOffset();
    void UpdateSelectionOffset();

    void CalcCursorOffsetXByPosition(int32_t position);

    bool ComputeOffsetForCaretDownstream(
        const TextEditingValueNG& TextEditingValueNG, int32_t extent, CaretMetrics& result) const;

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

    void SetEditingValueToProperty(const std::string& newValueText);

    void UpdatePositionOfParagraph(int32_t pos);
    void UpdateCaretPositionByTouch(const Offset& offset);
    void UpdateCaretOffsetByKeyEvent();

    bool RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard);
    bool CloseKeyboard(bool forceClose);

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true };
    }

    void UpdateConfiguration();
    void PerformAction(TextInputAction action, bool forceCloseKeyboard = false);
    void OnValueChanged(bool needFireChangeEvent = true, bool needFireSelectChangeEvent = true) override;

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

    float GetSelectionBaseOffsetX() const
    {
        return selectionBaseOffsetX_;
    }

    float GetSelectionDestinationOffsetX() const
    {
        return selectionDestinationOffsetX_;
    }

    float GetCaretOffsetX() const
    {
        return caretOffsetX_;
    }

    void SetCaretOffsetX(float offsetX)
    {
        caretOffsetX_ = offsetX;
    }

    CaretUpdateType GetCaretUpdateType() const
    {
        return caretUpdateType_;
    }

    void SetBasicPadding(float padding)
    {
        basicPadding_ = padding;
    }

    float GetBasicPadding() const
    {
        return basicPadding_;
    }

    const RectF& GetTextRect()
    {
        return textRect_;
    }

    const TextSelector& GetTextSelector()
    {
        return textSelector_;
    }

    void SetInSelectMode(SelectionMode selectionMode)
    {
        selectionMode_ = selectionMode;
    }

    bool InSelectMode() const
    {
        return selectionMode_ != SelectionMode::NONE;
    }

    void CursorMoveLeft();
    void CursorMoveRight();
    void CursorMoveUp();
    void CursorMoveDown();

private:
    bool IsTextArea();
    void HandleBlurEvent();
    bool OnKeyEvent(const KeyEvent& event);
    bool HandleKeyEvent(const KeyEvent& keyEvent);
    void HandleDirectionalKey(const KeyEvent& keyEvent);
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchDown(const Offset& offset);
    void HandleTouchUp();
    void InitClickEvent();
    void HandleClickEvent(const GestureEvent& info);
    void InitFocusEvent();
    void InitTouchEvent();
    void CursorMoveOnClick(const Offset& offset);

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

    void FireEventHubOnChange(const std::string& text);

    void UpdateSelection(int32_t both);
    void UpdateSelection(int32_t start, int32_t end);

    void ScheduleCursorTwinkling();
    void OnCursorTwinkling();
    void StartTwinkling();
    void StopTwinkling();

    void UpdateTextFieldManager(const Offset& offset);
    void OnTextInputActionUpdate(TextInputAction value);
    void Delete(int32_t start, int32_t end);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void FilterWithRegex(const std::string& filter, std::string& valueToUpdate);
    void EditingValueFilter(std::string& valueToUpdate);
    float PreferredLineHeight();

    RectF textRect_;
    RectF imageRect_;
    std::shared_ptr<RSParagraph> paragraph_;
    TextStyle lineHeightMeasureUtilTextStyle_;
    std::shared_ptr<RSParagraph> lineHeightMeasureUtilParagraph_;

    RefPtr<ImageLoadingContext> ShowPasswordImageLoadingCtx_;
    RefPtr<ImageLoadingContext> HidePasswordImageLoadingCtx_;

    // password icon image related
    RefPtr<CanvasImage> ShowPasswordImageCanvas_;
    RefPtr<CanvasImage> HidePasswordImageCanvas_;

    RefPtr<ClickEvent> clickListener_;
    RefPtr<TouchEventImpl> touchListener_;
    CursorPositionType cursorPositionType_ = CursorPositionType::NORMAL;

    // What the keyboard should appears.
    TextInputType keyboard_ = TextInputType::UNSPECIFIED;
    // Action when "enter" pressed.
    TextInputAction action_ = TextInputAction::UNSPECIFIED;
    TextDirection textDirection_ = TextDirection::LTR;

    Offset lastTouchOffset_;
    float basicPadding_ = 0.0f;
    float baselineOffset_ = 0.0f;
    float selectionBaseOffsetX_ = 0.0f;
    float selectionDestinationOffsetX_ = 0.0f;
    float caretOffsetX_ = 0.0f;
    float caretOffsetY_ = 0.0f;
    bool focusRequested_ = false;
    bool cursorVisible_ = false;
    bool focusEventInitialized_ = false;
    bool preferredLineHeightNeedToUpdate = true;

    SelectionMode selectionMode_ = SelectionMode::NONE;
    CaretUpdateType caretUpdateType_ = CaretUpdateType::NONE;
    uint32_t twinklingInterval_ = 0;
    int32_t obscureTickCountDown_ = 0;

    Offset lastClickOffset_;

    CancelableCallback<void()> cursorTwinklingTask_;

    std::list<std::unique_ptr<TextInputFormatter>> textInputFormatters_;

    RefPtr<TextFieldController> textFieldController_;
    RefPtr<TextEditController> textEditingController_;
    TextEditingValueNG textEditingValue_;
    TextSelector textSelector_;
    ACE_DISALLOW_COPY_AND_MOVE(TextFieldPattern);

    CopyOptions copyOption_ = CopyOptions::Distributed;
    RefPtr<Clipboard> clipboard_;
    std::vector<TextEditingValueNG> operationRecords_;
    std::vector<TextEditingValueNG> redoOperationRecords_;
    std::vector<TextSelector> textSelectorRecords_;
    std::vector<TextSelector> redoTextSelectorRecords_;
#if defined(ENABLE_STANDARD_INPUT)
    sptr<OHOS::MiscServices::OnTextChangedListener> textChangeListener_;
#endif
    int32_t instanceId_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_PATTERN_H