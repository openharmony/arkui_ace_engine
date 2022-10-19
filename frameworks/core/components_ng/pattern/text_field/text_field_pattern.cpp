/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_field/text_field_pattern.h"

#include <string>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/offset.h"
#include "base/i18n/localization.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/clipboard/clipboard_proxy.h"
#include "core/common/container_scope.h"
#include "core/common/font_manager.h"
#include "core/common/ime/text_edit_controller.h"
#include "core/common/ime/text_input_client.h"
#include "core/common/ime/text_input_connection.h"
#include "core/common/ime/text_input_formatter.h"
#include "core/common/ime/text_input_type.h"
#include "core/common/ime/text_selection.h"
#include "core/components_ng/pattern/search/search_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_controller.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/paragraph.h"

#if defined(ENABLE_STANDARD_INPUT)
#include "core/components_ng/pattern/text_field/on_text_changed_listener_impl.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t TWINKLING_INTERVAL_MS = 500;
const std::string DIGIT_FORMATTER = "-[0-9]+(.[0-9]+)?|[0-9]+(.[0-9]+)?";
const std::string PHONE_FORMATTER = "\\d{3}-\\d{8}|\\d{4}-\\d{7}|\\d{11}";
const std::string EMAIL_FORMATTER = "\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*";
const std::string URL_FORMATTER = "[a-zA-z]+://[^\\s]*";
const std::string SINGLE_LINE_FORMATTER = "\\n";

std::string WstringSearch(const std::string& wideText, const std::regex& regex)
{
    std::string result;
    std::smatch matchResults;
    std::regex_search(wideText, matchResults, regex);
    for (auto&& mr : matchResults) {
        result.append(mr);
    }
    return result;
}

} // namespace

float TextFieldPattern::GetTextOrPlaceHolderFontSize()
{
    auto pipeline = GetHost()->GetContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto textFieldLayoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, 0.0f);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, 0.0f);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    auto fontSize =
        textFieldLayoutProperty->GetFontSizeValue(textFieldTheme ? textFieldTheme->GetFontSize() : Dimension(-1));
    return static_cast<float>(fontSize.ConvertToPx());
}

TextFieldPattern::TextFieldPattern() : twinklingInterval_(TWINKLING_INTERVAL_MS) {}

TextFieldPattern::~TextFieldPattern()
{
    LOGI("Destruction of text field.");
    if (textEditingController_) {
        textEditingController_->Clear();
        textEditingController_->RemoveObserver(WeakClaim(this));
    }

    // If soft keyboard is still exist, close it.
#if defined(ENABLE_STANDARD_INPUT)
    LOGI("Destruction text field, close input method.");
    MiscServices::InputMethodController::GetInstance()->Close();
#endif
}

#if defined(ENABLE_STANDARD_INPUT)
void TextFieldPattern::UpdateConfiguration()
{
    MiscServices::Configuration configuration;
    LOGI("Enter key type %{public}d", (int32_t)GetTextInputActionValue(TextInputAction::DONE));
    configuration.SetEnterKeyType(
        static_cast<MiscServices::EnterKeyType>(static_cast<int32_t>(GetTextInputActionValue(TextInputAction::DONE))));
    configuration.SetTextInputType(static_cast<MiscServices::TextInputType>(static_cast<int32_t>(keyboard_)));
    MiscServices::InputMethodController::GetInstance()->OnConfigurationChange(configuration);
}
#endif

bool TextFieldPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    contentRect_ = dirty->GetGeometryNode()->GetContentRect();
    frameRect_ = dirty->GetGeometryNode()->GetFrameRect();
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto textFieldLayoutAlgorithm = DynamicCast<TextFieldLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(textFieldLayoutAlgorithm, false);
    auto paragraph = textFieldLayoutAlgorithm->GetParagraph();
    if (!paragraph) {
        LOGD("OnDirtyLayoutWrapperSwap paragraph is null");
        return false;
    }
    paragraph_ = paragraph;
    textRect_ = textFieldLayoutAlgorithm->GetTextRect();
    imageRect_ = textFieldLayoutAlgorithm->GetImageRect();
    if (caretUpdateType_ == CaretUpdateType::INPUT) {
        UpdateCaretPositionByTextEdit();
    } else if (caretUpdateType_ == CaretUpdateType::CLICK) {
        // caret offset updated by gesture will not cause textRect to change offset
        UpdateCaretPositionByTouchOffset();
        return true;
    } else if (caretUpdateType_ == CaretUpdateType::EVENT || caretUpdateType_ == CaretUpdateType::DEL) {
        UpdateCaretOffsetByEvent();
    } else if (caretUpdateType_ == CaretUpdateType::NONE) {
        caretOffsetX_ = GetPaddingLeft();
        return true;
    }
    // after new text input or events such as left right key,
    // the procedure will be:
    // caret position change (such as move left)
    // caret get offset from typographic algorithm
    // if caret position exceeds constrained content region, adjust both caret position and text rect offset
    AdjustTextRectOffsetX();
    AdjustTextAreaOffsetY();
    UpdateSelectionOffset();
    return true;
}

bool TextFieldPattern::IsTextArea()
{
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->HasMaxLines() ? layoutProperty->GetMaxLinesValue(1) > 1 : false;
}

void TextFieldPattern::UpdateCaretOffsetByEvent()
{
    // set caret and text rect to basic padding if caret is at position 0 or text not exists
    if (textEditingValue_.text.empty() || textEditingValue_.caretPosition == 0) {
        caretOffsetX_ = GetPaddingLeft();
        textRect_.SetLeft(GetPaddingLeft());
        return;
    }
    // simplify calculation if caret at the end and paragraph length not exceeding content width
    if (textEditingValue_.caretPosition == static_cast<int32_t>(textEditingValue_.text.size()) &&
        LessOrEqual(paragraph_->GetLongestLine(), contentRect_.Width())) {
        caretOffsetX_ = static_cast<float>(paragraph_->GetLongestLine());
        return;
    }
    // offsetToParagraphBeginning indicates the cursor position to paragraph beginning
    auto offsetToParagraphBeginning = CalcCursorOffsetXByPosition(textEditingValue_.caretPosition);
    // layout caret for the first time to the position by assuming text rect is at basic padding
    caretOffsetX_ = offsetToParagraphBeginning + contentRect_.GetX();
    // layout text rect by caret offset - offsetToParagraphBeginning
    textRect_.SetLeft(caretOffsetX_ - offsetToParagraphBeginning);
}

void TextFieldPattern::UpdateSelectionOffset()
{
    if (!InSelectMode()) {
        return;
    }
    if (selectionMode_ == SelectionMode::SELECT_ALL) {
        selectionBaseOffsetX_ = textRect_.GetX();
        selectionDestinationOffsetX_ = textRect_.GetX() + static_cast<float>(paragraph_->GetLongestLine());
        return;
    }
    selectionDestinationOffsetX_ = caretOffsetX_;
    auto offsetToParagraphBeginning = CalcCursorOffsetXByPosition(textSelector_.baseOffset);
    selectionBaseOffsetX_ = offsetToParagraphBeginning + textRect_.GetX();
}

void TextFieldPattern::UpdateCaretPositionByTextEdit()
{
    if (textEditingValue_.text.empty() || textEditingValue_.caretPosition == 0) {
        caretOffsetX_ = GetPaddingLeft();
        textRect_.SetLeft(GetPaddingLeft());
        return;
    }
    // simplify calculation for scene of inserting text to tail when text width not exceeding content width
    if (textEditingValue_.caretPosition == static_cast<int32_t>(textEditingValue_.text.size()) &&
        paragraph_->GetLongestLine() <= contentRect_.Width()) {
        caretOffsetX_ = static_cast<float>(paragraph_->GetLongestLine()) + GetPaddingLeft();
        return;
    }
    // scene of insert in the middle
    // after text insert, selection will update both base and extend offset to the same value
    auto offsetToParagraphBeginning = CalcCursorOffsetXByPosition(textEditingValue_.caretPosition);
    caretOffsetX_ = offsetToParagraphBeginning + GetPaddingLeft();
    textRect_.SetLeft(caretOffsetX_ - offsetToParagraphBeginning);
}

void TextFieldPattern::UpdateCaretPositionByTouchOffset()
{
    if (GetEditingValue().text.empty()) {
        caretOffsetX_ = GetPaddingLeft();
        return;
    }
    // skip updating caret if touch position is in the left or right half ellipse parts
    if (!OffsetInContentRegion(lastTouchOffset_)) {
        return;
    }
    Offset offset = GetLastTouchOffset() - Offset(textRect_.GetX(), 0.0f);
    // simplify calculation when text not filling the textfield yet and touch out of boundary edge case
    if (textRect_.Width() <= contentRect_.Width() && GreatOrEqual(offset.GetX(), paragraph_->GetLongestLine())) {
        textEditingValue_.CursorMoveToPosition(static_cast<int32_t>(textEditingValue_.GetWideText().length()));
        caretOffsetX_ = static_cast<float>(paragraph_->GetLongestLine()) + GetPaddingLeft();
        return;
    }
    auto position = ConvertTouchOffsetToCaretPosition(offset);
    textEditingValue_.CursorMoveToPosition(position);
    caretOffsetX_ = CalcCursorOffsetXByPosition(position) + GetPaddingLeft();
}

float TextFieldPattern::CalcCursorOffsetXByPosition(int32_t position)
{
    // this function will calculate proto caret offset x aligned with paragraph_
    CaretMetrics downStreamMetrics;
    if (!ComputeOffsetForCaretDownstream(GetEditingValue(), position, downStreamMetrics)) {
        LOGW("Get caret offset failed, set it to text tail");
        return textRect_.Width();
    }
    return static_cast<float>(downStreamMetrics.offset.GetX());
}

float TextFieldPattern::AdjustTextRectOffsetX()
{
    if (IsTextArea() || LessOrEqual(textRect_.Width(), contentRect_.Width())) {
        return 0.0f;
    }
    // text rect length exceeds content length, but cursor is still in the region
    if (CursorInContentRegion()) {
        return 0.0f;
    }
    auto offsetToParagraphBeginning = caretOffsetX_ - textRect_.GetX();
    auto contentLeftBoundary = contentRect_.GetX();
    auto contentRightBoundary = contentRect_.GetX() + contentRect_.GetSize().Width();
    float dx = 0.0f;
    if (caretOffsetX_ < contentLeftBoundary) {
        dx = contentLeftBoundary - caretOffsetX_;
        caretOffsetX_ += dx;
        textRect_.SetLeft(caretOffsetX_ - offsetToParagraphBeginning);
    } else if (caretOffsetX_ + CURSOR_WIDTH.ConvertToPx() > contentRightBoundary) {
        dx = (contentRightBoundary - static_cast<float>(CURSOR_WIDTH.ConvertToPx())) - caretOffsetX_;
        caretOffsetX_ += dx;
        textRect_.SetLeft(caretOffsetX_ - offsetToParagraphBeginning);
    }
    return dx;
}

float TextFieldPattern::AdjustTextAreaOffsetY()
{
    if (!IsTextArea() || LessOrEqual(textRect_.Height(), contentRect_.Height())) {
        return 0.0f;
    }
    // text rect height exceeds content region but caret is still in region
    if (CursorInContentRegion()) {
        return 0.0f;
    }
    if (caretOffsetY_ < contentRect_.GetY()) {
        auto dy = contentRect_.GetY() - caretOffsetY_;
        caretOffsetY_ += dy;
        textRect_.SetOffset(OffsetF(textRect_.GetX(), textRect_.GetY() + dy));
        return dy;
    }
    auto dy = contentRect_.GetY() + contentRect_.Height() - (caretHeight_ + caretOffsetY_);
    caretOffsetY_ -= dy;
    textRect_.SetOffset(OffsetF(textRect_.GetX(), textRect_.GetY() - dy));
    return dy;
}

bool TextFieldPattern::CursorInContentRegion()
{
    if (IsTextArea()) {
        return GreatOrEqual(caretOffsetY_, contentRect_.GetY()) &&
               LessOrEqual(caretOffsetY_ + caretHeight_, contentRect_.GetY() + contentRect_.Height());
    }
    return GreatOrEqual(caretOffsetX_, contentRect_.GetX()) &&
           LessOrEqual(caretOffsetX_ + CURSOR_WIDTH.ConvertToPx(), contentRect_.GetX() + contentRect_.Width());
}

bool TextFieldPattern::OffsetInContentRegion(const Offset& offset)
{
    // real content region will minus basic padding on left and right
    return GreatOrEqual(offset.GetX(), contentRect_.GetX()) &&
           LessOrEqual(offset.GetX(), contentRect_.GetX() + contentRect_.Width());
}

void TextFieldPattern::AddScrollEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollableEvent_) {
        return;
    }
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    auto scrollCallback = [weak = WeakClaim(this)](Dimension x, Dimension y) {
        auto textFieldPattern = weak.Upgrade();
        if (!textFieldPattern) {
            LOGE("textField pattern upgrade fail when try handle scroll event.");
            return;
        }
        textFieldPattern->OnTextAreaScroll(static_cast<float>(y.ConvertToPx()));
    };
    scrollableEvent_->SetOnScrollCallback(std::move(scrollCallback));
    gestureHub->AddScrollableEvent(scrollableEvent_);
}

void TextFieldPattern::OnTextAreaScroll(float dy)
{
    if (!IsTextArea() || textRect_.Height() < contentRect_.Height()) {
        return;
    }
    auto textRectOffsetTop = textRect_.GetY();
    auto textRectOffsetBottom = textRect_.GetY() + textRect_.Height();
    // scroll down
    if (dy > 0) {
        // text rect min positionY is content offsetY
        textRect_.SetOffset(OffsetF(textRect_.GetX(), std::min(textRectOffsetTop - dy, 0.0f)));
    } else {
        // scroll up
        // text rect bottom max positionY is content offsetY + content height
        textRectOffsetBottom = std::max(textRectOffsetBottom + dy, contentRect_.GetY() + contentRect_.Height());
        textRectOffsetTop = textRectOffsetBottom == contentRect_.GetY() + contentRect_.Height()
                                ? contentRect_.GetY() + contentRect_.Height() - textRect_.Height()
                                : textRectOffsetTop + dy;
        textRect_.SetOffset(OffsetF(textRect_.GetX(), textRectOffsetTop));
    }
}

void TextFieldPattern::GetTextRectsInRange(
    int32_t base, int32_t destination, std::vector<RSTypographyProperties::TextBox>& textBoxes)
{
    textBoxes = paragraph_->GetRectsForRange(
        base, destination, RSTypographyProperties::RectHeightStyle::MAX, RSTypographyProperties::RectWidthStyle::TIGHT);
}

bool TextFieldPattern::ComputeOffsetForCaretDownstream(
    const TextEditingValueNG& TextEditingValueNG, int32_t extent, CaretMetrics& result)
{
    if (!paragraph_ || static_cast<size_t>(extent) >= TextEditingValueNG.GetWideText().length()) {
        return false;
    }

    result.Reset();
    const int32_t graphemeClusterLength = 1;
    const int32_t next = extent + graphemeClusterLength;
    GetTextRectsInRange(extent, next, textBoxes_);

    if (textBoxes_.empty()) {
        LOGW("Box empty");
        return false;
    }

    const auto& textBox = *textBoxes_.begin();
    // Caret is within width of the downstream glyphs.
    float caretStart = textBox.rect_.GetLeft();
    float offsetX = std::min(caretStart, static_cast<float>(paragraph_->GetLongestLine()));
    result.offset.SetX(offsetX);
    result.offset.SetY(textBox.rect_.GetTop());
    result.height = textBox.rect_.GetHeight();
    return true;
}

int32_t TextFieldPattern::ConvertTouchOffsetToCaretPosition(const Offset& localOffset)
{
    if (!paragraph_) {
        LOGW("Paragraph is empty");
        return 0;
    }
    return static_cast<int32_t>(
        paragraph_->GetGlyphPositionAtCoordinateWithCluster(localOffset.GetX(), localOffset.GetY()).pos_);
}

bool TextFieldPattern::DisplayPlaceHolder()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto value = layoutProperty->GetValueValue("");
    return value.empty();
}

const TextEditingValueNG& TextFieldPattern::GetEditingValue() const
{
    return textEditingValue_;
}

void TextFieldPattern::InitFocusEvent()
{
    if (focusEventInitialized_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleBlurEvent();
        }
    };
    focusHub->SetOnBlurInternal(blurTask);

    auto keyTask = [weak = WeakClaim(this)](const KeyEvent& keyEvent) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(keyEvent);
    };
    focusHub->SetOnKeyEventInternal(keyTask);
    focusEventInitialized_ = true;
}

void TextFieldPattern::HandleBlurEvent()
{
    LOGI("TextField %{public}d OnBlur", GetHost()->GetId());
    StopTwinkling();
    CloseKeyboard(true);
    auto eventHub = GetHost()->GetEventHub<TextFieldEventHub>();
    eventHub->FireOnEditChanged(false);
}

bool TextFieldPattern::OnKeyEvent(const KeyEvent& event)
{
    caretUpdateType_ = CaretUpdateType::EVENT;
    return HandleKeyEvent(event);
}

void TextFieldPattern::HandleDirectionalKey(const KeyEvent& keyEvent)
{
    bool updateSelection = false;
    if (keyEvent.IsKey({ KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_DPAD_UP }) ||
        keyEvent.IsKey({ KeyCode::KEY_SHIFT_RIGHT, KeyCode::KEY_DPAD_UP })) {
        HandleSelectionUp();
        updateSelection = true;
    } else if (keyEvent.IsKey({ KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_DPAD_DOWN }) ||
               keyEvent.IsKey({ KeyCode::KEY_SHIFT_RIGHT, KeyCode::KEY_DPAD_DOWN })) {
        HandleSelectionDown();
        updateSelection = true;
    } else if (keyEvent.IsKey({ KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_DPAD_LEFT }) ||
               keyEvent.IsKey({ KeyCode::KEY_SHIFT_RIGHT, KeyCode::KEY_DPAD_LEFT })) {
        HandleSelectionLeft();
        updateSelection = true;
    } else if (keyEvent.IsKey({ KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_DPAD_RIGHT }) ||
               keyEvent.IsKey({ KeyCode::KEY_SHIFT_RIGHT, KeyCode::KEY_DPAD_RIGHT })) {
        HandleSelectionRight();
        updateSelection = true;
    }
}

bool TextFieldPattern::HandleKeyEvent(const KeyEvent& keyEvent)
{
    if (keyEvent.action == KeyAction::DOWN) {
        if (keyEvent.code == KeyCode::KEY_ENTER || keyEvent.code == KeyCode::KEY_NUMPAD_ENTER ||
            keyEvent.code == KeyCode::KEY_DPAD_CENTER) {
            if (keyboard_ != TextInputType::MULTILINE) {
                PerformAction(action_, false);
            }
        } else if (keyEvent.IsDirectionalKey()) {
            HandleDirectionalKey(keyEvent);
        } else if (keyEvent.IsLetterKey()) {
            if (keyEvent.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_Z }) ||
                keyEvent.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_SHIFT_RIGHT, KeyCode::KEY_Z }) ||
                keyEvent.IsKey({ KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_Z }) ||
                keyEvent.IsKey({ KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_SHIFT_RIGHT, KeyCode::KEY_Z }) ||
                keyEvent.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_Y }) ||
                keyEvent.IsKey({ KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_Y })) {
                HandleOnRedoAction();
            } else if (keyEvent.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_Z }) ||
                       keyEvent.IsKey({ KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_Z })) {
                HandleOnUndoAction();
            } else if (keyEvent.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A }) ||
                       keyEvent.IsKey({ KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_A })) {
                HandleOnSelectAll();
            } else if (keyEvent.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_C }) ||
                       keyEvent.IsKey({ KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_C })) {
                HandleOnCopy();
            } else if (keyEvent.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_V }) ||
                       keyEvent.IsKey({ KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_V })) {
                HandleOnPaste();
            } else if (keyEvent.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_X }) ||
                       keyEvent.IsKey({ KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_X })) {
                HandleOnCut();
            }
        }
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    return true;
}

void TextFieldPattern::HandleOnUndoAction()
{
    if (operationRecords_.empty()) {
        LOGW("Operation records empty, cannot undo");
        return;
    }
    auto value = operationRecords_.back();
    operationRecords_.pop_back();
    redoOperationRecords_.push_back(value);
    if (operationRecords_.empty()) {
        LOGD("No record left, clear");
        ClearEditingValue();
    } else {
        textEditingValue_ = operationRecords_.back();
        SetEditingValueToProperty(textEditingValue_.text);
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    FireEventHubOnChange(GetEditingValue().text);
}

void TextFieldPattern::HandleOnRedoAction()
{
    if (redoOperationRecords_.empty()) {
        LOGW("Redo operation records empty, cannot undo");
        return;
    }
    textEditingValue_ = redoOperationRecords_.back();
    redoOperationRecords_.pop_back();
    operationRecords_.push_back(textEditingValue_);
    SetEditingValueToProperty(textEditingValue_.text);
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FireEventHubOnChange(GetEditingValue().text);
}

void TextFieldPattern::HandleOnSelectAll()
{
    auto textSize = GetEditingValue().GetWideText().length();
    UpdateSelection(0, static_cast<int32_t>(textSize));
    textEditingValue_.caretPosition = static_cast<int32_t>(textEditingValue_.text.size());
    selectionMode_ = SelectionMode::SELECT_ALL;
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::HandleOnCopy()
{
    CHECK_NULL_VOID(clipboard_);
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) == CopyOptions::None) {
        LOGW("Copy option not allowed");
        return;
    }
    if (!InSelectMode() || (textSelector_.IsValid() && textSelector_.GetStart() == textSelector_.GetEnd())) {
        LOGW("Nothing to select");
        return;
    }
    auto value = GetEditingValue().GetSelectedText(textSelector_.GetStart(), textSelector_.GetEnd());
    if (value.empty()) {
        LOGW("Copy value is empty");
        return;
    }
    if (copyOption_ != CopyOptions::None) {
        LOGI("Copy value is %{private}s", value.c_str());
        clipboard_->SetData(value, copyOption_);
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // If the parent node is a Search, the Search callback is executed.
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
    if (parentFrameNode && parentFrameNode->GetTag() == V2::SEARCH_ETS_TAG) {
        auto eventHub = parentFrameNode->GetEventHub<SearchEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnCopy(value);
        return;
    }

    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnCopy(value);
}

void TextFieldPattern::HandleOnPaste()
{
    CHECK_NULL_VOID(clipboard_);
    auto pasteCallback = [weak = WeakClaim(this), textSelector = textSelector_](const std::string& data) {
        if (data.empty()) {
            LOGW("Paste value is empty");
            return;
        }
        auto textfield = weak.Upgrade();
        if (!textfield) {
            return;
        }
        auto layoutProperty = textfield->GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) == CopyOptions::None) {
            LOGW("Copy option not allowed");
            return;
        }
        auto value = textfield->GetEditingValue();
        int32_t start = 0;
        int32_t end = 0;
        if (textfield->InSelectMode()) {
            start = textSelector.GetStart();
            end = textSelector.GetEnd();
        } else {
            start = value.caretPosition;
            end = value.caretPosition;
        }
        value.text = value.GetValueBeforePosition(start) + data + value.GetValueAfterPosition(end);
        value.CursorMoveToPosition(start + static_cast<int32_t>(StringUtils::Str8ToStr16(data).length()));
        LOGI("Paste value %{private}s", value.text.c_str());
        textfield->textEditingValue_ = value;
        textfield->SetEditingValueToProperty(value.text);
        textfield->SetInSelectMode(SelectionMode::NONE);
        textfield->operationRecords_.emplace_back(value);

        auto host = textfield->GetHost();
        CHECK_NULL_VOID(host);
        // If the parent node is a Search, the Search callback is executed.
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
        if (parentFrameNode && parentFrameNode->GetTag() == V2::SEARCH_ETS_TAG) {
            auto eventHub = parentFrameNode->GetEventHub<SearchEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->FireOnPaste(data);
            textfield->FireEventHubOnChange(data);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            return;
        }

        auto eventHub = textfield->GetHost()->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnPaste(data);
        textfield->FireEventHubOnChange(data);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };
    clipboard_->GetData(pasteCallback);
}

void TextFieldPattern::HandleOnCut()
{
    CHECK_NULL_VOID(clipboard_);
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) == CopyOptions::None) {
        LOGW("Copy option not allowed");
        return;
    }
    if (!InSelectMode() || (textSelector_.IsValid() && textSelector_.GetStart() == textSelector_.GetEnd())) {
        LOGW("HandleOnCut nothing Selected");
        return;
    }
    auto value = GetEditingValue();
    auto selectedText = value.GetSelectedText(textSelector_.GetStart(), textSelector_.GetEnd());
    if (copyOption_ != CopyOptions::None) {
        LOGI("Cut value is %{private}s", selectedText.c_str());
        clipboard_->SetData(selectedText, copyOption_);
    }
    textEditingValue_.text = textEditingValue_.GetValueBeforePosition(textSelector_.GetStart()) +
                             textEditingValue_.GetValueAfterPosition(textSelector_.GetEnd());
    textEditingValue_.CursorMoveToPosition(textSelector_.GetStart());
    SetEditingValueToProperty(textEditingValue_.text);
    selectionMode_ = SelectionMode::NONE;
    operationRecords_.emplace_back(textEditingValue_);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // If the parent node is a Search, the Search callback is executed.
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
    if (parentFrameNode && parentFrameNode->GetTag() == V2::SEARCH_ETS_TAG) {
        auto eventHub = parentFrameNode->GetEventHub<SearchEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnCut(selectedText);
        FireEventHubOnChange(selectedText);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }

    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnCut(selectedText);
    FireEventHubOnChange(selectedText);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::UpdateSelection(int32_t both)
{
    UpdateSelection(both, both);
}

void TextFieldPattern::UpdateSelection(int32_t start, int32_t end)
{
    textSelector_.Update(start, end);
}

void TextFieldPattern::FireEventHubOnChange(const std::string& text)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // If the parent node is a Search, the Search callback is executed.
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
    if (parentFrameNode && parentFrameNode->GetTag() == V2::SEARCH_ETS_TAG) {
        auto eventHub = parentFrameNode->GetEventHub<SearchEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->UpdateChangeEvent(text);
        return;
    }

    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnChange(text);
}

void TextFieldPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown(info.GetTouches().front().GetLocalLocation());
        UpdateTextFieldManager(info.GetTouches().front().GetGlobalLocation());
    } else if (touchType == TouchType::UP) {
        HandleTouchUp();
    }
}

void TextFieldPattern::HandleTouchDown(const Offset& offset)
{
    StartTwinkling();
    lastTouchOffset_ = offset;
    caretUpdateType_ = CaretUpdateType::CLICK;
    selectionMode_ = SelectionMode::NONE;
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::HandleTouchUp()
{
    auto focusHub = GetHost()->GetOrCreateFocusHub();
    if (!focusHub->RequestFocusImmediately()) {
        LOGE("Request focus failed, cannot open input method");
        StopTwinkling();
        return;
    }
    if (RequestKeyboard(false, true, true)) {
        auto eventHub = GetHost()->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnEditChanged(true);
    }
}

void TextFieldPattern::InitTouchEvent()
{
    if (touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleTouchEvent(info);
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gesture->AddTouchEvent(touchListener_);
}

void TextFieldPattern::ScheduleCursorTwinkling()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    if (!context->GetTaskExecutor()) {
        LOGW("context has no task executor.");
        return;
    }

    auto weak = WeakClaim(this);
    cursorTwinklingTask_.Reset([weak] {
        auto client = weak.Upgrade();
        if (client) {
            client->OnCursorTwinkling();
        }
    });
    auto taskExecutor = context->GetTaskExecutor();
    if (taskExecutor) {
        taskExecutor->PostDelayedTask(cursorTwinklingTask_, TaskExecutor::TaskType::UI, twinklingInterval_);
    } else {
        LOGE("the task executor is nullptr");
    }
}

void TextFieldPattern::StartTwinkling()
{
    // Ignore the result because all ops are called on this same thread (ACE UI).
    // The only reason failed is that the task has finished.
    cursorTwinklingTask_.Cancel();

    // Show cursor right now.
    cursorVisible_ = true;
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    ScheduleCursorTwinkling();
}

void TextFieldPattern::OnCursorTwinkling()
{
    cursorTwinklingTask_.Cancel();
    cursorVisible_ = !cursorVisible_;
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    ScheduleCursorTwinkling();
}

void TextFieldPattern::StopTwinkling()
{
    cursorTwinklingTask_.Cancel();

    // Repaint only if cursor is visible for now.
    if (cursorVisible_) {
        cursorVisible_ = false;
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void TextFieldPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    instanceId_ = context->GetInstanceId();
#if defined(ENABLE_STANDARD_INPUT)
    UpdateConfiguration();
#endif
    InitTouchEvent();
    InitFocusEvent();
    if (!clipboard_ && context) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
    }
    caretHeight_ = GetTextOrPlaceHolderFontSize() + static_cast<float>(CURSOR_PADDING.ConvertToPx()) * 2.0f;
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    utilPadding_ = layoutProperty->CreatePaddingAndBorderWithDefault(basicPaddingLeft_, 0.0f, 0.0f, 0.0f);
}

void TextFieldPattern::UpdatePositionOfParagraph(int32_t position)
{
    textEditingValue_.CursorMoveToPosition(position);
}

void TextFieldPattern::UpdateTextFieldManager(const Offset& offset)
{
    auto context = GetHost()->GetContext();
    CHECK_NULL_VOID(context);
    auto textFieldManager = DynamicCast<TextFieldManager>(context->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    textFieldManager->SetClickPosition(offset);
    textFieldManager->SetOnFocusTextField(WeakClaim(this));
}

bool TextFieldPattern::RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard)
{
    auto host = GetHost();
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    if (needShowSoftKeyboard) {
        LOGI("Start to request keyboard");
#if defined(ENABLE_STANDARD_INPUT)
        if (textChangeListener_ == nullptr) {
            textChangeListener_ = new OnTextChangedListenerImpl(WeakClaim(this));
        }
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        if (!inputMethod) {
            LOGE("Request open soft keyboard failed because input method is null.");
            return false;
        }
        if (context) {
            LOGI("RequestKeyboard set calling window id is : %{public}d", context->GetWindowId());
            inputMethod->SetCallingWindow(context->GetWindowId());
        }
        inputMethod->Attach(textChangeListener_, needShowSoftKeyboard);
#endif
    }
    return true;
}

bool TextFieldPattern::CloseKeyboard(bool forceClose)
{
    LOGI("Close kb");
    if (forceClose) {
        StopTwinkling();
        LOGI("Request close soft keyboard");
#if defined(ENABLE_STANDARD_INPUT)
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        if (!inputMethod) {
            LOGE("Request close soft keyboard failed because input method is null.");
            return false;
        }
        inputMethod->HideTextInput();
#endif
        return true;
    }
    return false;
}

void TextFieldPattern::OnTextInputActionUpdate(TextInputAction value) {}

void TextFieldPattern::InsertValue(const std::string& insertValue)
{
    std::string oldText = textEditingValue_.text;
    if (InSelectMode()) {
        textEditingValue_.text = textEditingValue_.GetValueBeforePosition(textSelector_.GetStart()) + insertValue +
                                 textEditingValue_.GetValueAfterPosition(textSelector_.GetEnd());
        textEditingValue_.caretPosition = static_cast<int32_t>(insertValue.size() + textSelector_.GetStart());
    } else {
        auto textToUpdate =
            textEditingValue_.GetValueBeforeCursor() + insertValue + textEditingValue_.GetValueAfterCursor();
        // TODO: change counter style
        selectionMode_ = SelectionMode::NONE;
        if (textToUpdate == oldText) {
            return;
        }
        textEditingValue_.text = textToUpdate;
        textEditingValue_.CursorMoveRight();
    }
    // TODO: update obscure pending for password input
    SetEditingValueToProperty(textEditingValue_.text);
    operationRecords_.emplace_back(textEditingValue_);
    caretUpdateType_ = CaretUpdateType::INPUT;

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // If the parent node is a Search, the Search callback is executed.
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
    if (parentFrameNode && parentFrameNode->GetTag() == V2::SEARCH_ETS_TAG) {
        auto eventHub = parentFrameNode->GetEventHub<SearchEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->UpdateChangeEvent(textEditingValue_.text);
        return;
    }

    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnChange(textEditingValue_.text);
}

void TextFieldPattern::FilterWithRegex(const std::string& filter, std::string& valueToUpdate)
{
    if (filter.empty() || valueToUpdate.empty()) {
        LOGD("Text is empty or filter is empty");
        return;
    }
    std::regex filterRegex(filter);

    auto textError = std::regex_replace(valueToUpdate, filterRegex, "");
    if (!textError.empty()) {
        auto textFieldEventHub = GetHost()->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_VOID(textFieldEventHub);
        LOGD("FireOnInputFilterError text %{public}s", textError.c_str());
        textFieldEventHub->FireOnInputFilterError(textError);
    }
    valueToUpdate = WstringSearch(valueToUpdate, filterRegex);
}

void TextFieldPattern::EditingValueFilter(std::string& valueToUpdate)
{
    auto textFieldLayoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    // filter text editing value with user defined filter first
    auto inputFilter = textFieldLayoutProperty->GetInputFilterValue("");
    if (!inputFilter.empty()) {
        std::regex filterRegex(inputFilter);
        valueToUpdate = std::regex_replace(valueToUpdate, filterRegex, "");
    }
    if (textFieldLayoutProperty->GetMaxLinesValue(1) == 1) {
        std::regex filterRegex(SINGLE_LINE_FORMATTER);
        valueToUpdate = std::regex_replace(valueToUpdate, filterRegex, "");
    }
    switch (textFieldLayoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED)) {
        case TextInputType::NUMBER: {
            FilterWithRegex(DIGIT_FORMATTER, valueToUpdate);
            break;
        }
        case TextInputType::PHONE: {
            FilterWithRegex(PHONE_FORMATTER, valueToUpdate);
            break;
        }
        case TextInputType::EMAIL_ADDRESS: {
            FilterWithRegex(EMAIL_FORMATTER, valueToUpdate);
            break;
        }
        case TextInputType::URL: {
            FilterWithRegex(URL_FORMATTER, valueToUpdate);
            break;
        }
        default: {
            // No need limit.
        }
    }
}

float TextFieldPattern::PreferredLineHeight()
{
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0.0f);
    // check if util paragraph need to update
    if (lineHeightMeasureUtilParagraph_ && !layoutProperty->GetPreferredLineHeightNeedToUpdateValue(true)) {
        return static_cast<float>(lineHeightMeasureUtilParagraph_->GetHeight());
    }
    auto pipeline = GetHost()->GetContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, 0.0f);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    std::string textContent;
    // use text or placeHolder value if exists, space otherwise
    if (!layoutProperty->GetValueValue("").empty()) {
        TextFieldLayoutAlgorithm::UpdateTextStyle(layoutProperty, textFieldTheme, lineHeightMeasureUtilTextStyle_);
        textContent = layoutProperty->GetValueValue(" ");
    } else {
        TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyle(
            layoutProperty, textFieldTheme, lineHeightMeasureUtilTextStyle_);
        textContent = layoutProperty->GetPlaceholderValue(" ");
    }
    RSParagraphStyle paraStyle;
    paraStyle.textDirection_ = ToRSTextDirection(TextFieldLayoutAlgorithm::GetTextDirection(textEditingValue_.text));
    paraStyle.textAlign_ = ToRSTextAlign(lineHeightMeasureUtilTextStyle_.GetTextAlign());
    paraStyle.maxLines_ = lineHeightMeasureUtilTextStyle_.GetMaxLines();
    paraStyle.locale_ = Localization::GetInstance()->GetFontLocale();
    paraStyle.wordBreakType_ = ToRSWordBreakType(lineHeightMeasureUtilTextStyle_.GetWordBreak());
    if (lineHeightMeasureUtilTextStyle_.GetTextOverflow() == TextOverflow::ELLIPSIS) {
        paraStyle.ellipsis_ = RSParagraphStyle::ELLIPSIS;
    }
    auto builder = RSParagraphBuilder::CreateRosenBuilder(paraStyle, RSFontCollection::GetInstance(false));
    builder->PushStyle(ToRSTextStyle(PipelineContext::GetCurrentContext(), lineHeightMeasureUtilTextStyle_));
    StringUtils::TransformStrCase(
        textEditingValue_.text, static_cast<int32_t>(lineHeightMeasureUtilTextStyle_.GetTextCase()));
    builder->AddText(StringUtils::Str8ToStr16(textContent));
    builder->Pop();
    lineHeightMeasureUtilParagraph_ = builder->Build();
    lineHeightMeasureUtilParagraph_->Layout(Size::INFINITE_SIZE);
    layoutProperty->UpdatePreferredLineHeightNeedToUpdate(false);
    return static_cast<float>(lineHeightMeasureUtilParagraph_->GetHeight());
}

void TextFieldPattern::CursorMoveLeft()
{
    LOGD("Handle cursor move left");
    if (InSelectMode() && selectionMode_ == SelectionMode::SELECT_ALL) {
        textEditingValue_.caretPosition = 0;
    } else if (InSelectMode()) {
        textEditingValue_.caretPosition = textSelector_.GetStart();
    } else {
        textEditingValue_.CursorMoveLeft();
    }
    selectionMode_ = SelectionMode::NONE;
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::CursorMoveRight()
{
    LOGD("Handle cursor move right");
    if (InSelectMode() && selectionMode_ == SelectionMode::SELECT_ALL) {
        textEditingValue_.caretPosition = static_cast<int32_t>(textEditingValue_.text.size());
    } else if (InSelectMode()) {
        textEditingValue_.caretPosition = textSelector_.GetEnd();
    } else {
        textEditingValue_.CursorMoveRight();
    }
    selectionMode_ = SelectionMode::NONE;
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::CursorMoveUp()
{
    LOGD("Handle cursor move up");
    if (!IsTextArea()) {
        return;
    }
    float verticalOffset = caretOffsetY_ - PreferredLineHeight();
    textEditingValue_.caretPosition =
        static_cast<int32_t>(paragraph_->GetGlyphPositionAtCoordinateWithCluster(caretOffsetX_, verticalOffset).pos_);
}

void TextFieldPattern::CursorMoveDown()
{
    LOGD("Handle cursor move down");
    if (!IsTextArea()) {
        return;
    }
    float verticalOffset = caretOffsetY_ + PreferredLineHeight();
    textEditingValue_.caretPosition =
        static_cast<int32_t>(paragraph_->GetGlyphPositionAtCoordinateWithCluster(caretOffsetX_, verticalOffset).pos_);
}

void TextFieldPattern::Delete(int32_t start, int32_t end)
{
    LOGD("Handle Delete within [%{public}d, %{public}d]", start, end);
    textEditingValue_.text =
        textEditingValue_.GetValueBeforePosition(start) + textEditingValue_.GetValueAfterPosition(end);
    textEditingValue_.caretPosition = start;
    SetEditingValueToProperty(textEditingValue_.text);
    FireEventHubOnChange(GetEditingValue().text);
    selectionMode_ = SelectionMode::NONE;
    caretUpdateType_ = CaretUpdateType::INPUT;
    operationRecords_.emplace_back(textEditingValue_);
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::SetEditingValueToProperty(const std::string& newValueText)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateValue(newValueText);
}

void TextFieldPattern::ClearEditingValue()
{
    textEditingValue_.Reset();
    SetEditingValueToProperty("");
    operationRecords_.emplace_back(textEditingValue_);
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::PerformAction(TextInputAction action, bool forceCloseKeyboard)
{
    LOGD("PerformAction  %{public}d", static_cast<int32_t>(action));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // If the parent node is a Search, the Search callback is executed.
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
    if (parentFrameNode && parentFrameNode->GetTag() == V2::SEARCH_ETS_TAG) {
        auto eventHub = parentFrameNode->GetEventHub<SearchEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->UpdateSubmitEvent(textEditingValue_.text);
        return;
    }

    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    eventHub->FireOnSubmit(static_cast<int32_t>(action));
}

void TextFieldPattern::OnValueChanged(bool needFireChangeEvent, bool needFireSelectChangeEvent) {}

void TextFieldPattern::DeleteForward(int32_t length)
{
    LOGD("Handle DeleteForward %{public}d characters", length);
    if (textEditingValue_.caretPosition <= 0) {
        LOGW("Caret position at the beginning , cannot DeleteForward");
        return;
    }
    if (InSelectMode()) {
        Delete(textSelector_.GetStart(), textSelector_.GetEnd());
        return;
    }
    textEditingValue_.text =
        textEditingValue_.GetValueBeforePosition(std::max(textEditingValue_.caretPosition - length, 0)) +
        textEditingValue_.GetValueAfterPosition(std::max(textEditingValue_.caretPosition, 0));
    textEditingValue_.CursorMoveToPosition(textEditingValue_.caretPosition - length);
    SetEditingValueToProperty(textEditingValue_.text);
    FireEventHubOnChange(GetEditingValue().text);
    selectionMode_ = SelectionMode::NONE;
    caretUpdateType_ = CaretUpdateType::INPUT;
    operationRecords_.emplace_back(textEditingValue_);
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::DeleteBackward(int32_t length)
{
    LOGD("Handle DeleteBackward %{public}d characters", length);
    if (textEditingValue_.caretPosition >= static_cast<int32_t>(textEditingValue_.text.size())) {
        LOGW("Caret position at the end , cannot DeleteBackward");
        return;
    }
    if (InSelectMode()) {
        Delete(textSelector_.GetStart(), textSelector_.GetEnd());
        return;
    }
    textEditingValue_.text = textEditingValue_.GetValueBeforePosition(textEditingValue_.caretPosition) +
                             textEditingValue_.GetValueAfterPosition(textEditingValue_.caretPosition + length);
    SetEditingValueToProperty(textEditingValue_.text);
    FireEventHubOnChange(GetEditingValue().text);
    selectionMode_ = SelectionMode::NONE;
    caretUpdateType_ = CaretUpdateType::INPUT;
    operationRecords_.emplace_back(textEditingValue_);
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::HandleSelectionUp()
{
    LOGD("Handle selection up");
    if (!IsTextArea()) {
        LOGW("Unsupported operation for text field");
        return;
    }
    if (selectionMode_ != SelectionMode::SELECT) {
        textSelector_.baseOffset = textEditingValue_.caretPosition;
    }
    auto newOffsetY = caretOffsetY_ - PreferredLineHeight();
    textEditingValue_.caretPosition =
        static_cast<int32_t>(paragraph_->GetGlyphPositionAtCoordinateWithCluster(caretOffsetX_, newOffsetY).pos_);
    textSelector_.destinationOffset = textEditingValue_.caretPosition;
    if (textSelector_.baseOffset == textSelector_.destinationOffset) {
        selectionMode_ = SelectionMode::NONE;
    }
}

void TextFieldPattern::HandleSelectionDown()
{
    LOGD("Handle selection down");
    if (!IsTextArea()) {
        LOGW("Unsupported operation for text field");
        return;
    }
    if (selectionMode_ != SelectionMode::SELECT) {
        textSelector_.baseOffset = textEditingValue_.caretPosition;
    }
    auto newOffsetY = caretOffsetY_ + PreferredLineHeight();
    textEditingValue_.caretPosition =
        static_cast<int32_t>(paragraph_->GetGlyphPositionAtCoordinateWithCluster(caretOffsetX_, newOffsetY).pos_);
    if (textSelector_.baseOffset == textSelector_.destinationOffset) {
        selectionMode_ = SelectionMode::NONE;
    }
}

void TextFieldPattern::HandleSelectionLeft()
{
    if (!InSelectMode()) {
        if (textEditingValue_.caretPosition == 0) {
            LOGD("Caret position at beginning, cannot update selection to left");
            return;
        }
        textSelector_.baseOffset = textEditingValue_.caretPosition;
        textSelector_.destinationOffset = std::max(textSelector_.baseOffset - 1, 0);
        textEditingValue_.caretPosition = textSelector_.destinationOffset;
        selectionMode_ = SelectionMode::SELECT;
    } else {
        textSelector_.destinationOffset = std::max(textSelector_.destinationOffset - 1, 0);
        textEditingValue_.caretPosition = textSelector_.destinationOffset;
        if (textSelector_.destinationOffset == textSelector_.baseOffset) {
            selectionMode_ = SelectionMode::NONE;
        }
    }
}

void TextFieldPattern::HandleSelectionRight()
{
    // if currently not in select mode, reset baseOffset and move destinationOffset and caret position
    if (!InSelectMode()) {
        if (textEditingValue_.caretPosition == static_cast<int32_t>(textEditingValue_.text.size())) {
            LOGD("Caret position at the end, cannot update selection to right");
            return;
        }
        textSelector_.baseOffset = textEditingValue_.caretPosition;
        textSelector_.destinationOffset =
            std::min(textSelector_.baseOffset + 1, static_cast<int32_t>(textEditingValue_.text.size()));
        textEditingValue_.caretPosition = textSelector_.destinationOffset;
        selectionMode_ = SelectionMode::SELECT;
    } else {
        // if currently not in select mode, move destinationOffset and caret position only
        textSelector_.destinationOffset =
            std::min(textSelector_.destinationOffset + 1, static_cast<int32_t>(textEditingValue_.text.size()));
        textEditingValue_.caretPosition = textSelector_.destinationOffset;
        if (textSelector_.destinationOffset == textSelector_.baseOffset) {
            selectionMode_ = SelectionMode::NONE;
        }
    }
}

void TextFieldPattern::SetCaretPosition(int32_t position)
{
    if (position < 0 || position > static_cast<int32_t>(textEditingValue_.text.size())) {
        LOGE("Illegal caret position");
        return;
    }
    textEditingValue_.caretPosition = position;
    selectionMode_ = SelectionMode::NONE;
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::CaretMoveToLastNewLineChar()
{
    while (textEditingValue_.caretPosition > 0) {
        textEditingValue_.caretPosition -= 1;
        if (textEditingValue_.text.substr(textEditingValue_.caretPosition, 1) == "\n") {
            break;
        }
    }
}

} // namespace OHOS::Ace::NG