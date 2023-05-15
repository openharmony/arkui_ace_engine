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

#include "core/components_ng/pattern/text_field/text_field_pattern.h"

#include <algorithm>
#include <cstdint>
#include <optional>
#include <regex>
#include <string>
#include <utility>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/offset.h"
#include "base/i18n/localization.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
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
#include "core/components/common/layout/constants.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/pattern/search/search_event_hub.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_controller.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/paragraph.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_v2/inspector/utils.h"
#include "core/image/image_source_info.h"
#if defined(ENABLE_STANDARD_INPUT)
#include "core/components_ng/pattern/text_field/on_text_changed_listener_impl.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension DEFAULT_FONT = Dimension(16, DimensionUnit::FP);
constexpr float HOVER_ANIMATION_OPACITY = 0.05f;
constexpr float PRESS_ANIMATION_OPACITY = 0.1f;
constexpr uint32_t TWINKLING_INTERVAL_MS = 500;
constexpr uint32_t RECORD_MAX_LENGTH = 20;
constexpr uint32_t OBSCURE_SHOW_TICKS = 3;
constexpr char16_t OBSCURING_CHARACTER = u'•';
constexpr char16_t OBSCURING_CHARACTER_FOR_AR = u'*';
const std::string NEWLINE = "\n";
const std::wstring WIDE_NEWLINE = StringUtils::ToWstring(NEWLINE);
const std::string DIGIT_WHITE_LIST = "^[0-9]*$";
const std::string PHONE_WHITE_LIST = "[\\d\\-\\+\\*\\#]+";
const std::string EMAIL_WHITE_LIST = "[\\w.]";
const std::string URL_WHITE_LIST = "[a-zA-z]+://[^\\s]*";

void RemoveErrorTextFromValue(const std::string& value, const std::string& errorText, std::string& result)
{
    int32_t valuePtr = 0;
    int32_t errorTextPtr = 0;
    auto valueSize = static_cast<int32_t>(value.length());
    auto errorTextSize = static_cast<int32_t>(errorText.length());
    while (errorTextPtr < errorTextSize) {
        while (value[valuePtr] != errorText[errorTextPtr] && valuePtr < valueSize) {
            result += value[valuePtr];
            valuePtr++;
        }
        // no more text left to remove in value
        if (valuePtr >= valueSize) {
            return;
        }
        // increase both value ptr and error text ptr if char in value is removed
        valuePtr++;
        errorTextPtr++;
    }
    result += value.substr(valuePtr);
}

std::string ConvertFontFamily(const std::vector<std::string>& fontFamily)
{
    std::string result;
    for (const auto& item : fontFamily) {
        result += item;
        result += ",";
    }
    result = result.substr(0, result.length() - 1);
    return result;
}

} // namespace

std::u16string TextFieldPattern::CreateObscuredText(int32_t len)
{
    std::u16string obscuredText;
    if (Localization::GetInstance()->GetLanguage() == "ar") { // ar is the abbreviation of Arabic.
        obscuredText = std::u16string(len, OBSCURING_CHARACTER_FOR_AR);
    } else {
        obscuredText = std::u16string(len, OBSCURING_CHARACTER);
    }
    return obscuredText;
}

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
    Dimension fontSize;
    if (textFieldLayoutProperty->HasFontSize() &&
        textFieldLayoutProperty->GetFontSizeValue(Dimension()).IsNonNegative()) {
        fontSize = textFieldLayoutProperty->GetFontSizeValue(Dimension());
    } else {
        return textFieldTheme ? static_cast<float>(textFieldTheme->GetFontSize().ConvertToPx())
                              : static_cast<float>(DEFAULT_FONT.ConvertToPx());
    }
    return std::min(static_cast<float>(fontSize.ConvertToPx()), contentRect_.Height());
}

TextFieldPattern::TextFieldPattern() : twinklingInterval_(TWINKLING_INTERVAL_MS) {}

TextFieldPattern::~TextFieldPattern()
{
    LOGI("Destruction of text field.");
    if (textEditingController_) {
        textEditingController_->Clear();
        textEditingController_->RemoveObserver(WeakClaim(this));
    }
    CloseSelectOverlay();
    // If soft keyboard is still exist, close it.
    if (HasConnection()) {
#if defined(ENABLE_STANDARD_INPUT)
        LOGI("Destruction of text field, close input method.");
        MiscServices::InputMethodController::GetInstance()->HideTextInput();
        MiscServices::InputMethodController::GetInstance()->Close();
#endif
    }
}

#if defined(ENABLE_STANDARD_INPUT)
void TextFieldPattern::UpdateConfiguration()
{
    MiscServices::Configuration configuration;
    LOGI("UpdateConfiguration: Enter key type %{public}d", (int32_t)GetTextInputActionValue(TextInputAction::DONE));
    LOGI("UpdateConfiguration: Enter keyboard type %{public}d", static_cast<int32_t>(keyboard_));
    configuration.SetEnterKeyType(
        static_cast<MiscServices::EnterKeyType>(static_cast<int32_t>(GetTextInputActionValue(TextInputAction::DONE))));
    configuration.SetTextInputType(static_cast<MiscServices::TextInputType>(static_cast<int32_t>(keyboard_)));
    MiscServices::InputMethodController::GetInstance()->OnConfigurationChange(configuration);
}
#endif

bool TextFieldPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    contentRect_ = dirty->GetGeometryNode()->GetContentRect();
    frameRect_ = dirty->GetGeometryNode()->GetFrameRect();
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto textFieldLayoutAlgorithm = DynamicCast<TextFieldLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(textFieldLayoutAlgorithm, false);
    auto paragraph = textFieldLayoutAlgorithm->GetParagraph();
    if (paragraph) {
        paragraph_ = paragraph;
    }
    textRect_ = textFieldLayoutAlgorithm->GetTextRect();
    imageRect_ = textFieldLayoutAlgorithm->GetImageRect();
    parentGlobalOffset_ = textFieldLayoutAlgorithm->GetParentGlobalOffset();
    auto textRectNotNeedToChange = UpdateCaretPosition();
    UpdateCaretInfoToController();
    if (mouseStatus_ == MouseStatus::RELEASED) {
        mouseStatus_ = MouseStatus::NONE;
    }
    if (textRectNotNeedToChange) {
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
    SetHandlerOnMoveDone();
    return true;
}

bool TextFieldPattern::HasFocus() const
{
    auto focusHub = GetHost()->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->IsCurrentFocus();
}

void TextFieldPattern::UpdateCaretInfoToController() const
{
    CHECK_NULL_VOID_NOLOG(HasFocus());
#if defined(ENABLE_STANDARD_INPUT)
    auto pipeline = GetHost()->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto windowRect = pipeline->GetCurrentWindowRect();
    MiscServices::CursorInfo cursorInfo { .left = caretRect_.Left() + windowRect.Left() + parentGlobalOffset_.GetX(),
        .top = caretRect_.Top() + windowRect.Top() + parentGlobalOffset_.GetY(),
        .width = CURSOR_WIDTH.ConvertToPx(),
        .height = caretRect_.Height() };
    LOGD("UpdateCaretInfoToController, left %{public}f, top %{public}f, width %{public}f, height %{public}f",
        cursorInfo.left, cursorInfo.top, cursorInfo.width, cursorInfo.height);
    MiscServices::InputMethodController::GetInstance()->OnCursorUpdate(cursorInfo);
    auto value = GetEditingValue();
    LOGD("Start %{public}d, end %{public}d", textSelector_.GetStart(), textSelector_.GetEnd());
    MiscServices::InputMethodController::GetInstance()->OnSelectionChange(
        StringUtils::Str8ToStr16(value.text), textSelector_.GetStart(), textSelector_.GetEnd());

#endif
}

// return: true if text rect offset will NOT be further changed by caret position
bool TextFieldPattern::UpdateCaretPosition()
{
    // If the parent node is a Search, do not check whether it is a focus state.
    if (!IsSearchParentNode()) {
        auto focusHub = GetHost()->GetOrCreateFocusHub();
        if (focusHub && !focusHub->IsCurrentFocus()) {
            CloseSelectOverlay();
            LOGW("Not on focus, cannot update caret");
            return true;
        }
    }
    // text input has higher priority than events such as mouse press
    if (caretUpdateType_ == CaretUpdateType::INPUT) {
        UpdateCaretPositionByTextEdit();
        StartTwinkling();
    } else if (caretUpdateType_ == CaretUpdateType::PRESSED || caretUpdateType_ == CaretUpdateType::LONG_PRESSED) {
        UpdateCaretByPressOrLongPress();
    } else if (caretUpdateType_ == CaretUpdateType::EVENT || caretUpdateType_ == CaretUpdateType::DEL) {
        UpdateCaretOffsetByEvent();
        if (!NeedShowPasswordIcon()) {
            StartTwinkling();
        }
    } else if (caretUpdateType_ == CaretUpdateType::NONE) {
        if (GetEditingValue().text.empty()) {
            UpdateSelection(0);
            SetCaretOffsetForEmptyTextOrPositionZero();
        }
        return true;
    } else if (caretUpdateType_ == CaretUpdateType::RIGHT_CLICK) {
        UpdateCaretByRightClick();
    }
    return false;
}

float TextFieldPattern::GetIconSize()
{
    auto pipeline = GetHost()->GetContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, 0.0f);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    return static_cast<float>(textFieldTheme->GetIconSize().ConvertToPx());
}

float TextFieldPattern::GetIconHotZoneSize()
{
    auto pipeline = GetHost()->GetContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, 0.0f);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    return static_cast<float>(textFieldTheme->GetIconHotZoneSize().ConvertToPx());
}

float TextFieldPattern::GetIconRightOffset()
{
    auto iconSize = GetIconSize();
    auto iconHotZoneSize = GetIconHotZoneSize();
    if (NearZero(iconSize) || NearZero(iconHotZoneSize)) {
        return 0.0f;
    }
    return (iconHotZoneSize - iconSize) / 2.0f;
}

void TextFieldPattern::CreateSingleHandle()
{
    RectF secondHandle;
    auto secondHandleMetrics = CalcCursorOffsetByPosition(textEditingValue_.caretPosition);
    OffsetF emptyOffset;
#if defined(PREVIEW)
    emptyOffset = MakeEmptyOffset();
#endif
    OffsetF secondHandleOffset(secondHandleMetrics.offset.GetX() + parentGlobalOffset_.GetX() + emptyOffset.GetX(),
        secondHandleMetrics.offset.GetY() + parentGlobalOffset_.GetY() + emptyOffset.GetY());
    SizeF handlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), caretRect_.Height() };
    secondHandle.SetOffset(secondHandleOffset);
    secondHandle.SetSize(handlePaintSize);
    ShowSelectOverlay(std::nullopt, secondHandle);
    selectionMode_ = SelectionMode::NONE;
    StopTwinkling();
}

bool TextFieldPattern::UpdateCaretByPressOrLongPress()
{
    if (CaretPositionCloseToTouchPosition() && !SelectOverlayIsOn() &&
        caretUpdateType_ != CaretUpdateType::LONG_PRESSED && !isMousePressed_) {
        isSingleHandle_ = true;
        CreateSingleHandle();
        return true;
    }
    // caret offset updated by gesture will not cause textRect to change offset
    UpdateCaretPositionByPressOffset();
    if (caretUpdateType_ == CaretUpdateType::PRESSED) {
        StartTwinkling();
        CloseSelectOverlay();
    }
    // in long press case, we have caret and one handle at pressed location and another handle at -1 or +1 position
    if (caretUpdateType_ == CaretUpdateType::LONG_PRESSED) {
        ProcessOverlay();
    }
    return true;
}

void TextFieldPattern::UpdateCaretByRightClick()
{
    ProcessOverlay();
}

bool TextFieldPattern::CaretPositionCloseToTouchPosition()
{
    auto xInRange = GreatOrEqual(lastTouchOffset_.GetX(), caretRect_.GetX() - PreferredLineHeight()) &&
                    LessOrEqual(lastTouchOffset_.GetX(), caretRect_.GetX() + PreferredLineHeight());
    auto yInRange = GreatOrEqual(lastTouchOffset_.GetY(), caretRect_.GetY()) &&
                    LessOrEqual(lastTouchOffset_.GetY(), caretRect_.GetY() + PreferredLineHeight());
    return xInRange && yInRange;
}

bool TextFieldPattern::IsTextArea() const
{
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, true);
    return layoutProperty->HasMaxLines() ? layoutProperty->GetMaxLinesValue(1) > 1 : true;
}

void TextFieldPattern::UpdateDestinationToCaretByEvent()
{
    CHECK_NULL_VOID_NOLOG(isMousePressed_);
    textSelector_.destinationOffset = textEditingValue_.caretPosition;
    if (textSelector_.destinationOffset != textSelector_.baseOffset) {
        selectionMode_ = SelectionMode::SELECT;
    }
}

void TextFieldPattern::UpdateCaretOffsetByLastTouchOffset()
{
    Offset offset = GetLastTouchOffset() - Offset(textRect_.GetX(), textRect_.GetY());
    auto position = ConvertTouchOffsetToCaretPosition(offset);
    textEditingValue_.CursorMoveToPosition(position);
    UpdateCaretRectByPosition(position);
}

// return bool that caret might move out of content rect and need adjust position
bool TextFieldPattern::UpdateCaretPositionByMouseMovement()
{
    if (GetEditingValue().text.empty()) {
        caretRect_.SetLeft(textRect_.GetX());
        caretRect_.SetTop(textRect_.GetY());
        selectionMode_ = SelectionMode::NONE;
        UpdateSelection(0, 0);
        return false;
    }
    bool needToShiftCaretAndTextRect = false;
    // if mouse keep at position out of content rect, caret will keep moving left or right
    if (lastTouchOffset_.GetX() < contentRect_.GetX() ||
        lastTouchOffset_.GetX() > contentRect_.GetX() + contentRect_.Width()) {
        needToShiftCaretAndTextRect = true;
    }
    UpdateCaretOffsetByLastTouchOffset();
    textSelector_.destinationOffset = textEditingValue_.caretPosition;
    GetTextRectsInRange(textSelector_.GetStart(), textSelector_.GetEnd(), textBoxes_);
    selectionMode_ =
        textSelector_.destinationOffset == textSelector_.baseOffset ? SelectionMode::NONE : SelectionMode::SELECT;
    return needToShiftCaretAndTextRect;
}

void TextFieldPattern::UpdateCaretOffsetByEvent()
{
    if (textEditingValue_.text.empty()) {
        UpdateSelection(0, 0);
        SetCaretOffsetForEmptyTextOrPositionZero();
        return;
    }
    if (isMousePressed_) {
        // handle mouse event only
        UpdateCaretPositionByMouseMovement();
        return;
    }
    if (!InSelectMode()) {
        UpdateSelection(textEditingValue_.caretPosition);
    }
    UpdateCaretRectByPosition(textEditingValue_.caretPosition);
}

void TextFieldPattern::UpdateSelectionOffset()
{
    CHECK_NULL_VOID_NOLOG(InSelectMode());
    if (textSelector_.baseOffset == textSelector_.destinationOffset) {
        textSelector_.selectionBaseOffset.SetX(caretRect_.GetX());
        textSelector_.selectionDestinationOffset.SetX(caretRect_.GetX());
        return;
    }
    if (selectionMode_ == SelectionMode::SELECT_ALL) {
        textSelector_.selectionBaseOffset.SetX(textRect_.GetX());
        textSelector_.selectionDestinationOffset.SetX(textRect_.GetX() + textRect_.Width());
        std::optional<RectF> firstHandleOption;
        std::optional<RectF> secondHandleOption;
        if (textBoxes_.empty()) {
            return;
        }
        if (SelectOverlayIsOn()) {
            SizeF handlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), caretRect_.Height() };
            auto textBoxLocalOffsetBegin =
                OffsetF(textBoxes_.begin()->rect_.GetLeft() + (IsTextArea() ? contentRect_.GetX() : textRect_.GetX()),
                    textBoxes_.begin()->rect_.GetTop() + (IsTextArea() ? textRect_.GetY() : contentRect_.GetY()));
            auto textBoxLocalOffsetEnd =
                OffsetF(textBoxes_.rbegin()->rect_.GetRight() + (IsTextArea() ? contentRect_.GetX() : textRect_.GetX()),
                    textBoxes_.rbegin()->rect_.GetTop() + (IsTextArea() ? textRect_.GetY() : contentRect_.GetY()));
            if (GreatOrEqual(textBoxLocalOffsetBegin.GetX(), contentRect_.GetX()) &&
                LessOrEqual(textBoxLocalOffsetBegin.GetX(), contentRect_.GetX() + contentRect_.Width())) {
                OffsetF firstHandleOffset(textBoxLocalOffsetBegin.GetX() + parentGlobalOffset_.GetX(),
                    textBoxLocalOffsetBegin.GetY() + parentGlobalOffset_.GetY());
                RectF firstHandle;
                firstHandle.SetOffset(firstHandleOffset);
                firstHandle.SetSize(handlePaintSize);
                firstHandleOption = firstHandle;
            }
            if (GreatOrEqual(textBoxLocalOffsetEnd.GetX(), contentRect_.GetX()) &&
                LessOrEqual(textBoxLocalOffsetEnd.GetX(), contentRect_.GetX() + contentRect_.Width())) {
                OffsetF secondHandleOffset(textBoxLocalOffsetEnd.GetX() + parentGlobalOffset_.GetX(),
                    textBoxLocalOffsetEnd.GetY() + parentGlobalOffset_.GetY());
                RectF secondHandle;
                secondHandle.SetOffset(secondHandleOffset);
                secondHandle.SetSize(handlePaintSize);
                secondHandleOption = secondHandle;
            }
            ShowSelectOverlay(firstHandleOption, secondHandleOption);
        }
        return;
    }
}

void TextFieldPattern::UpdateCaretPositionByTextEdit()
{
    if (textEditingValue_.text.empty()) {
        UpdateSelection(0);
        SetCaretOffsetForEmptyTextOrPositionZero();
        return;
    }
    if (textEditingValue_.caretPosition == 0) {
        SetCaretOffsetForEmptyTextOrPositionZero();
        return;
    }
    UpdateCaretRectByPosition(textEditingValue_.caretPosition);
    UpdateSelection(textEditingValue_.caretPosition);
}

void TextFieldPattern::UpdateCaretRectByPosition(int32_t position)
{
    auto caretMetrics = CalcCursorOffsetByPosition(position);
    caretRect_.SetLeft(caretMetrics.offset.GetX());
    // add 1.0f here for offsetToParagraphBeginning offsetY is negative when caret position is zero
    caretRect_.SetTop(caretMetrics.offset.GetY());
    caretRect_.SetHeight(caretMetrics.height);
}

int32_t TextFieldPattern::GetLineNumber(float offsetY)
{
    auto bottomBoundary = textRect_.GetY() + textRect_.Height();
    int32_t lineNum = 0;
    auto accumulatedLineHeight = 0.0f;
    while (LessOrEqual((lineNum + 1) * PreferredLineHeight(), offsetY) &&
           LessOrEqual((lineNum + 1) * PreferredLineHeight(), bottomBoundary)) {
        accumulatedLineHeight += PreferredLineHeight();
        lineNum++;
    }
    return lineNum;
}

void TextFieldPattern::SetCaretOffsetForEmptyTextOrPositionZero()
{
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    caretRect_.SetLeft(IsTextArea() ? contentRect_.Left() : textRect_.GetX());
    caretRect_.SetTop(IsTextArea() ? textRect_.GetY() : contentRect_.Top());
    caretRect_.SetHeight(PreferredLineHeight());
    switch (layoutProperty->GetTextAlignValue(TextAlign::START)) {
        case TextAlign::START:
            caretRect_.SetLeft(textRect_.GetX());
            return;
        case TextAlign::CENTER:
            caretRect_.SetLeft(static_cast<float>(contentRect_.GetX()) + contentRect_.Width() / 2.0f);
            return;
        case TextAlign::END:
            caretRect_.SetLeft(static_cast<float>(contentRect_.GetX()) + contentRect_.Width());
            return;
        default:
            caretRect_.SetLeft(textRect_.GetX());
            return;
    }
}

void TextFieldPattern::UpdateCaretPositionByPressOffset()
{
    if (GetEditingValue().text.empty()) {
        SetCaretOffsetForEmptyTextOrPositionZero();
        return;
    }
    UpdateCaretOffsetByLastTouchOffset();
    UpdateSelection(textEditingValue_.caretPosition);
}

CaretMetricsF TextFieldPattern::CalcCursorOffsetByPosition(int32_t position)
{
    // this function will calculate caret offset and height by caret position
    CaretMetricsF result;
    if (!(ComputeOffsetForCaretDownstream(position, result) || ComputeOffsetForCaretUpstream(position, result))) {
        LOGW("Get caret offset failed, set it to text start");
        if (IsTextArea()) {
            result.offset = OffsetF(contentRect_.GetX(), textRect_.GetY());
        } else {
            result.offset = OffsetF(textRect_.GetX(), contentRect_.GetY());
        }
        result.height = textBoxes_.empty() ? PreferredLineHeight() : textBoxes_.begin()->rect_.GetHeight();
        return result;
    }
    result.offset.AddX(IsTextArea() ? contentRect_.GetX() : textRect_.GetX());
    result.offset.AddY(IsTextArea() ? textRect_.GetY() : contentRect_.GetY());
    return result;
}

float TextFieldPattern::AdjustTextRectOffsetX()
{
    if (IsTextArea()) {
        return 0.0f;
    }
    // text rect length exceeds content length, but cursor is still in the region
    if (CursorInContentRegion()) {
        return 0.0f;
    }
    auto offsetToParagraphBeginning = caretRect_.GetX() - textRect_.GetX();
    auto contentLeftBoundary = contentRect_.GetX();
    auto contentRightBoundary = contentRect_.GetX() + contentRect_.GetSize().Width();
    float dx = 0.0f;
    if (caretRect_.GetX() < contentLeftBoundary) {
        dx = contentLeftBoundary - caretRect_.GetX();
        caretRect_.SetLeft(caretRect_.GetX() + dx);
        textRect_.SetLeft(caretRect_.GetX() - offsetToParagraphBeginning);
    } else if (caretRect_.GetX() + CURSOR_WIDTH.ConvertToPx() > contentRightBoundary) {
        dx = (contentRightBoundary - static_cast<float>(CURSOR_WIDTH.ConvertToPx())) - caretRect_.GetX();
        caretRect_.SetLeft(caretRect_.GetX() + dx);
        textRect_.SetLeft(caretRect_.GetX() - offsetToParagraphBeginning);
    }
    return dx;
}

float TextFieldPattern::AdjustTextAreaOffsetY()
{
    if (!IsTextArea()) {
        return 0.0f;
    }
    // text rect height exceeds content region but caret is still in region
    if (CursorInContentRegion()) {
        return 0.0f;
    }
    if (caretRect_.GetY() < contentRect_.GetY()) {
        auto dy = contentRect_.GetY() - caretRect_.GetY();
        caretRect_.SetTop(caretRect_.GetY() + dy);
        textRect_.SetOffset(OffsetF(textRect_.GetX(), textRect_.GetY() + dy));
        return dy;
    }
    auto dy = contentRect_.GetY() + contentRect_.Height() - (GetTextOrPlaceHolderFontSize() + caretRect_.GetY());
    // caret does not exceed bottom boundary, no need to shift text rect and caret rect
    if (GreatOrEqual(dy, 0.0f)) {
        return dy;
    }
    caretRect_.SetTop(caretRect_.GetY() + dy);
    textRect_.SetOffset(OffsetF(textRect_.GetX(), textRect_.GetY() + dy));
    return dy;
}

bool TextFieldPattern::CursorInContentRegion()
{
    if (IsTextArea()) {
        return GreatOrEqual(caretRect_.Top(), contentRect_.GetY()) &&
               LessOrEqual(
                   caretRect_.Top() + GetTextOrPlaceHolderFontSize(), contentRect_.GetY() + contentRect_.Height());
    }
    return GreatOrEqual(caretRect_.GetX(), contentRect_.GetX()) &&
           LessOrEqual(caretRect_.GetX() + CURSOR_WIDTH.ConvertToPx(), contentRect_.GetX() + contentRect_.Width());
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
    CHECK_NULL_VOID_NOLOG(!scrollableEvent_);
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    auto scrollCallback = [weak = WeakClaim(this)](Dimension x, Dimension y) {
        auto textFieldPattern = weak.Upgrade();
        CHECK_NULL_VOID(textFieldPattern);
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
    if (base > destination) {
        std::swap(base, destination);
    }
    textBoxes = paragraph_->GetRectsForRange(
        base, destination, RSTypographyProperties::RectHeightStyle::MAX, RSTypographyProperties::RectWidthStyle::TIGHT);
}

bool TextFieldPattern::ComputeOffsetForCaretDownstream(int32_t extent, CaretMetricsF& result)
{
    CHECK_NULL_RETURN_NOLOG(paragraph_, false);
    if (!IsTextArea() && static_cast<size_t>(extent) >= textEditingValue_.GetWideText().length()) {
        return false;
    }

    result.Reset();
    const int32_t graphemeClusterLength = 1;
    const int32_t next = extent + graphemeClusterLength;
    auto textBoxes = paragraph_->GetRectsForRange(
        next, extent, RSTypographyProperties::RectHeightStyle::MAX, RSTypographyProperties::RectWidthStyle::TIGHT);

    if (textBoxes.empty()) {
        LOGD("Box empty");
        return false;
    }

    const auto& textBox = *textBoxes.begin();
    // Caret is within width of the downstream glyphs.
    float offsetX = textBox.rect_.GetLeft();
    result.offset.SetX(offsetX);
    result.offset.SetY(textBox.rect_.GetTop());
    result.height = textBox.rect_.GetHeight();
    return true;
}

bool TextFieldPattern::ComputeOffsetForCaretUpstream(int32_t extent, CaretMetricsF& result) const
{
    auto text = textEditingValue_.text;
    auto wideText = textEditingValue_.GetWideText();
    if (!paragraph_ || wideText.empty() || textEditingValue_.caretPosition == 0 ||
        textEditingValue_.caretPosition > static_cast<int32_t>(wideText.length())) {
        return false;
    }

    char16_t prevChar = 0;
    if (static_cast<size_t>(extent) <= textEditingValue_.GetWideText().length()) {
        prevChar = text[std::max(0, extent - 1)];
    }

    result.Reset();
    int32_t graphemeClusterLength = StringUtils::NotInUtf16Bmp(prevChar) ? 2 : 1;
    int32_t prev = extent - graphemeClusterLength;
    auto boxes = paragraph_->GetRectsForRange(
        prev, extent, RSTypographyProperties::RectHeightStyle::MAX, RSTypographyProperties::RectWidthStyle::TIGHT);
    while (boxes.empty() && !textEditingValue_.text.empty()) {
        graphemeClusterLength *= 2;
        prev = extent - graphemeClusterLength;
        if (prev < 0) {
            boxes = paragraph_->GetRectsForRange(
                0, extent, RSTypographyProperties::RectHeightStyle::MAX, RSTypographyProperties::RectWidthStyle::TIGHT);
            break;
        }
        boxes = paragraph_->GetRectsForRange(
            prev, extent, RSTypographyProperties::RectHeightStyle::MAX, RSTypographyProperties::RectWidthStyle::TIGHT);
    }
    if (boxes.empty()) {
        return false;
    }

    const auto& textBox = *boxes.begin();
    auto lastStringBeforeCursor = wideText.substr(textEditingValue_.caretPosition - 1, 1);
    // Caret is within width of the downstream glyphs.
    if (lastStringBeforeCursor == WIDE_NEWLINE &&
        (caretUpdateType_ == CaretUpdateType::INPUT || caretUpdateType_ == CaretUpdateType::DEL)) {
        result.offset.SetX(MakeEmptyOffset().GetX());
        result.offset.SetY(textBox.rect_.GetBottom());
        result.height = textBox.rect_.GetHeight();
        return true;
    }
    result.offset.SetX(textBox.rect_.GetRight());
    result.offset.SetY(textBox.rect_.GetTop());
    result.height = textBox.rect_.GetHeight();
    return true;
}

OffsetF TextFieldPattern::MakeEmptyOffset() const
{
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, {});
    switch (layoutProperty->GetTextAlignValue(TextAlign::START)) {
        case TextAlign::CENTER:
            return OffsetF(contentRect_.Width() * 0.5f, 0.0f);
        case TextAlign::END:
            return OffsetF(contentRect_.Width(), 0.0f);
        case TextAlign::START:
        default:
            return {};
    }
}

int32_t TextFieldPattern::ConvertTouchOffsetToCaretPosition(const Offset& localOffset)
{
    CHECK_NULL_RETURN(paragraph_, 0);
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

void TextFieldPattern::HandleFocusEvent()
{
    LOGI("TextField %{public}d on focus", GetHost()->GetId());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    bool focusEventConsumed = false;
    if (IsSearchParentNode()) {
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(GetHost()->GetParent());
        auto searchPattern = parentFrameNode->GetPattern<SearchPattern>();
        CHECK_NULL_VOID(searchPattern);
        focusEventConsumed = searchPattern->HandleInputChildOnFocus();
    }
    if (!focusEventConsumed) {
        auto globalOffset = GetHost()->GetPaintRectOffset() - context->GetRootRect().GetOffset();
        UpdateTextFieldManager(Offset(globalOffset.GetX(), globalOffset.GetY()), frameRect_.Height());
        caretUpdateType_ = CaretUpdateType::EVENT;
        CloseSelectOverlay();
        auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        GetHost()->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                          : PROPERTY_UPDATE_MEASURE);
    }
}

void TextFieldPattern::HandleSetSelection(int32_t start, int32_t end)
{
    LOGI("HandleSetSelection %{public}d, %{public}d", start, end);
    UpdateSelection(start, end);
    textEditingValue_.caretPosition = end;
    selectionMode_ = SelectionMode::SELECT;
    caretUpdateType_ = CaretUpdateType::EVENT;
    GetTextRectsInRange(textSelector_.GetStart(), textSelector_.GetEnd(), textBoxes_);
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void TextFieldPattern::HandleExtendAction(int32_t action)
{
    LOGI("HandleExtendAction %{public}d", action);
    switch (action) {
        case ACTION_SELECT_ALL: {
            auto end = GetEditingValue().GetWideText().length();
            UpdateSelection(0, static_cast<int32_t>(end));
            break;
        }
        case ACTION_CUT: {
            HandleOnCut();
            break;
        }
        case ACTION_COPY: {
            HandleOnCopy();
            break;
        }
        case ACTION_PASTE: {
            HandleOnPaste();
            break;
        }
        default: {
            break;
        }
    }
}

void TextFieldPattern::HandleSelect(int32_t keyCode, int32_t cursorMoveSkip)
{
    KeyCode code = static_cast<KeyCode>(keyCode);
    caretUpdateType_ = CaretUpdateType::EVENT;
    switch (code) {
        case KeyCode::KEY_DPAD_LEFT: {
            HandleSelectionLeft();
            break;
        }
        case KeyCode::KEY_DPAD_RIGHT: {
            HandleSelectionRight();
            break;
        }
        case KeyCode::KEY_DPAD_UP: {
            HandleSelectionUp();
            break;
        }
        case KeyCode::KEY_DPAD_DOWN: {
            HandleSelectionDown();
            break;
        }
        default: {
            break;
        }
    }
}

void TextFieldPattern::InitFocusEvent()
{
    CHECK_NULL_VOID_NOLOG(!focusEventInitialized_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    auto focusTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleFocusEvent();
        }
    };
    focusHub->SetOnFocusInternal(focusTask);
    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleBlurEvent();
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    LOGI("TextField %{public}d OnBlur", host->GetId());
    auto context = PipelineContext::GetCurrentContext();
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    if (textFieldManager) {
        textFieldManager->ClearOnFocusTextField();
    }
    StopTwinkling();
    CloseKeyboard(true);
    auto pos = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    UpdateSelection(pos);
    selectionMode_ = SelectionMode::NONE;
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    eventHub->FireOnEditChanged(false);
    ResetBackgroundColor();
    CloseSelectOverlay();
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool TextFieldPattern::OnKeyEvent(const KeyEvent& event)
{
    caretUpdateType_ = CaretUpdateType::EVENT;
    CloseSelectOverlay();
    auto context = PipelineContext::GetCurrentContext();
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_RETURN(textFieldManager, false);
    auto keyEventHandler = textFieldManager->GetKeyEventHandler();
    keyEventHandler->UpdateWeakPattern(AceType::WeakClaim(this));
    return keyEventHandler->HandleKeyEvent(event);
}

void TextFieldPattern::HandleOnUndoAction()
{
    LOGI("TextFieldPattern::HandleOnUndoAction");
    if (operationRecords_.empty()) {
        LOGW("Operation records empty, cannot undo");
        return;
    }
    auto value = operationRecords_.back();
    operationRecords_.pop_back();
    redoOperationRecords_.push_back(value);
    if (operationRecords_.empty()) {
        LOGW("No record left, clear");
        ClearEditingValue();
        return;
    }
    textEditingValue_ = operationRecords_.back();
    SetEditingValueToProperty(textEditingValue_.text);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    GetHost()->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                      : PROPERTY_UPDATE_MEASURE);
    FireEventHubOnChange(GetEditingValue().text);
}

void TextFieldPattern::HandleOnRedoAction()
{
    LOGI("TextFieldPattern::HandleOnRedoAction");
    if (redoOperationRecords_.empty()) {
        LOGW("Redo operation records empty, cannot undo");
        return;
    }
    textEditingValue_ = redoOperationRecords_.back();
    redoOperationRecords_.pop_back();
    operationRecords_.push_back(textEditingValue_);
    SetEditingValueToProperty(textEditingValue_.text);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    GetHost()->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                      : PROPERTY_UPDATE_MEASURE);
    FireEventHubOnChange(GetEditingValue().text);
}

void TextFieldPattern::HandleOnSelectAll()
{
    LOGI("TextFieldPattern::HandleOnSelectAll");
    auto textSize = static_cast<int32_t>(GetEditingValue().GetWideText().length());
    UpdateSelection(0, textSize);
    textEditingValue_.caretPosition = textSize;
    selectionMode_ = SelectionMode::SELECT_ALL;
    caretUpdateType_ = CaretUpdateType::EVENT;
    GetTextRectsInRange(textSelector_.GetStart(), textSelector_.GetEnd(), textBoxes_);
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TextFieldPattern::HandleOnCopy()
{
    LOGI("TextFieldPattern::HandleOnCopy");
    CHECK_NULL_VOID(clipboard_);
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    caretUpdateType_ = CaretUpdateType::NONE;
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) == CopyOptions::None) {
        LOGW("Copy option not allowed");
        return;
    }
    if (!InSelectMode() || (textSelector_.IsValid() && textSelector_.GetStart() == textSelector_.GetEnd())) {
        LOGW("Nothing to select");
        return;
    }
    LOGI("On copy, text selector %{public}s", textSelector_.ToString().c_str());
    auto value = GetEditingValue().GetSelectedText(textSelector_.GetStart(), textSelector_.GetEnd());
    if (value.empty()) {
        LOGW("Copy value is empty");
        return;
    }
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) != CopyOptions::None) {
        LOGI("Copy value is %{private}s", value.c_str());
#if defined(PREVIEW)
        if (clipRecords_.size() >= RECORD_MAX_LENGTH) {
            clipRecords_.erase(clipRecords_.begin());
        }
        clipRecords_.emplace_back(StringUtils::ToWstring(value));
#else
        clipboard_->SetData(value, layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed));
#endif
    }

    textEditingValue_.caretPosition = textSelector_.GetEnd();
    selectionMode_ = SelectionMode::NONE;
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // If the parent node is a Search, the Search callback is executed.
    if (IsSearchParentNode()) {
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(GetHost()->GetParent());
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
    LOGI("TextFieldPattern::HandleOnPaste");
    auto pasteCallback = [weak = WeakClaim(this), textSelector = textSelector_](const std::string& data) {
        if (data.empty()) {
            LOGW("Paste value is empty");
            return;
        }
        auto textfield = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(textfield);
        auto layoutProperty = textfield->GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto value = textfield->GetEditingValue();
        auto valueLength = textfield->GetEditingValue().GetWideText().length();
        int32_t start = 0;
        int32_t end = 0;
        if (textfield->InSelectMode()) {
            start = textSelector.GetStart();
            end = textSelector.GetEnd();
        } else {
            start = value.caretPosition;
            end = value.caretPosition;
        }
        std::wstring pasteData;
        std::wstring wData = StringUtils::ToWstring(data);
        if (wData.length() + valueLength > textfield->GetMaxLength()) {
            pasteData = wData.substr(0, textfield->GetMaxLength() - valueLength);
        } else {
            pasteData = wData;
        }
        value.text =
            value.GetValueBeforePosition(start) + StringUtils::ToString(pasteData) + value.GetValueAfterPosition(end);
        auto newCaretPosition = std::min(start, end) + static_cast<int32_t>(pasteData.length());
        textfield->UpdateEditingValue(value.text, newCaretPosition);
        textfield->UpdateSelection(newCaretPosition);
        textfield->SetEditingValueToProperty(value.text);
        textfield->SetInSelectMode(SelectionMode::NONE);
        textfield->SetCaretUpdateType(CaretUpdateType::INPUT);
        textfield->UpdateEditingValueToRecord();
        auto host = textfield->GetHost();
        CHECK_NULL_VOID(host);
        // If the parent node is a Search, the Search callback is executed.
        if (textfield->IsSearchParentNode()) {
            auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
            auto eventHub = parentFrameNode->GetEventHub<SearchEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->FireOnPaste(StringUtils::ToString(pasteData));
            textfield->FireEventHubOnChange(value.text);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            return;
        }

        auto eventHub = textfield->GetHost()->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnPaste(StringUtils::ToString(pasteData));
        textfield->FireEventHubOnChange(value.text);
        host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                     : PROPERTY_UPDATE_MEASURE);
    };
#if defined(PREVIEW)
    pasteCallback(clipRecords_.empty() ? "" : StringUtils::ToString((*clipRecords_.rbegin())));
#else
    CHECK_NULL_VOID(clipboard_);
    clipboard_->GetData(pasteCallback);
#endif
}

void TextFieldPattern::HandleOnCut()
{
    LOGI("TextFieldPattern::HandleOnCut");
#if !defined(PREVIEW)
    CHECK_NULL_VOID(clipboard_);
#endif
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    caretUpdateType_ = CaretUpdateType::NONE;
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
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) != CopyOptions::None) {
        LOGI("Cut value is %{private}s", selectedText.c_str());
#if defined(PREVIEW)
        if (clipRecords_.size() >= RECORD_MAX_LENGTH) {
            clipRecords_.erase(clipRecords_.begin());
        }
        clipRecords_.emplace_back(StringUtils::ToWstring(selectedText));
#else
        clipboard_->SetData(selectedText, layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed));
#endif
    }
    textEditingValue_.text = textEditingValue_.GetValueBeforePosition(textSelector_.GetStart()) +
                             textEditingValue_.GetValueAfterPosition(textSelector_.GetEnd());
    textEditingValue_.CursorMoveToPosition(textSelector_.GetStart());
    SetEditingValueToProperty(textEditingValue_.text);
    selectionMode_ = SelectionMode::NONE;
    caretUpdateType_ = CaretUpdateType::EVENT;
    CloseSelectOverlay();
    UpdateEditingValueToRecord();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // If the parent node is a Search, the Search callback is executed.
    if (IsSearchParentNode()) {
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
        auto eventHub = parentFrameNode->GetEventHub<SearchEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnCut(selectedText);
        FireEventHubOnChange(textEditingValue_.text);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        return;
    }

    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnCut(selectedText);
    FireEventHubOnChange(textEditingValue_.text);
    host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                 : PROPERTY_UPDATE_MEASURE);
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
    if (IsSearchParentNode()) {
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
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
    if (SelectOverlayIsOn()) {
        return;
    }
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown(info.GetTouches().front().GetLocalLocation());
    } else if (touchType == TouchType::UP) {
        HandleTouchUp();
    }
}

void TextFieldPattern::HandleTouchDown(const Offset& offset)
{
    LOGI("HandleTouchDown");
    if (enableTouchAndHoverEffect_ && !isMousePressed_) {
        auto textfieldPaintProperty = GetPaintProperty<TextFieldPaintProperty>();
        CHECK_NULL_VOID(textfieldPaintProperty);
        auto renderContext = GetHost()->GetRenderContext();
        AnimatePressAndHover(renderContext, PRESS_ANIMATION_OPACITY);
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void TextFieldPattern::HandleTouchUp()
{
    LOGI("HandleTouchUp");
    if (isMousePressed_) {
        LOGI("TextFieldPattern::HandleTouchUp of mouse");
        isMousePressed_ = false;
    }
    if (enableTouchAndHoverEffect_) {
        auto renderContext = GetHost()->GetRenderContext();
        if (isOnHover_) {
            AnimatePressAndHover(renderContext, HOVER_ANIMATION_OPACITY);
        } else {
            AnimatePressAndHover(renderContext, 0.0f);
        }
    }
}

void TextFieldPattern::ResetBackgroundColor()
{
    auto renderContext = GetHost()->GetRenderContext();
    AnimatePressAndHover(renderContext, 0.0f);
}

void TextFieldPattern::AnimatePressAndHover(RefPtr<RenderContext>& renderContext, float endOpacity, bool isHoverChange)
{
    AnimationOption option = AnimationOption();
    if (isHoverChange) {
        option.SetDuration(HOVER_DURATION);
        option.SetCurve(Curves::FRICTION);
    } else {
        option.SetDuration(PRESS_DURATION);
        option.SetCurve(Curves::SHARP);
    }
    Color endBlendColor = Color::FromRGBO(0, 0, 0, endOpacity);
    AnimationUtils::Animate(option, [renderContext, endBlendColor]() { renderContext->BlendBgColor(endBlendColor); });
}

void TextFieldPattern::InitTouchEvent()
{
    CHECK_NULL_VOID_NOLOG(!touchListener_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleTouchEvent(info);
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gesture->AddTouchEvent(touchListener_);
}

void TextFieldPattern::InitClickEvent()
{
    CHECK_NULL_VOID_NOLOG(!clickListener_);
    auto gesture = GetHost()->GetOrCreateGestureEventHub();
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleClickEvent(info);
    };

    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void TextFieldPattern::HandleClickEvent(GestureEvent& info)
{
    LOGI("TextFieldPattern::HandleClickEvent");
    UpdateTextFieldManager(info.GetGlobalLocation(), frameRect_.Height());
    auto focusHub = GetHost()->GetOrCreateFocusHub();
    if (!focusHub->IsFocusable()) {
        return;
    }
    lastTouchOffset_ = info.GetLocalLocation();
    caretUpdateType_ = CaretUpdateType::PRESSED;
    selectionMode_ = SelectionMode::NONE;
    isUsingMouse_ = false;
    CloseSelectOverlay();
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    if (lastTouchOffset_.GetX() > frameRect_.Width() - imageRect_.Width() - GetIconRightOffset() &&
        NeedShowPasswordIcon()) {
        textObscured_ = !textObscured_;
        ProcessPasswordIcon();
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        caretUpdateType_ = CaretUpdateType::EVENT;
        return;
    }
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    StartTwinkling();

    if (isMousePressed_) {
        LOGI("TextFieldPattern::HandleTouchUp of mouse");
        isMousePressed_ = false;
        return;
    }
    if (!focusHub->IsFocusOnTouch().value_or(true) || !focusHub->RequestFocusImmediately()) {
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
        CHECK_NULL_VOID_NOLOG(client);
        client->OnCursorTwinkling();
    });
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(cursorTwinklingTask_, TaskExecutor::TaskType::UI, twinklingInterval_);
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
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (keyboard_ != layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED)) {
        LOGI("Keyboard type changed to %{public}d", layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED));
        CloseKeyboard(true);
        keyboard_ = layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED);
    }
    InitClickEvent();
    InitLongPressEvent();
    InitFocusEvent();
    InitMouseEvent();
    InitTouchEvent();
    ProcessPasswordIcon();
    context->AddOnAreaChangeNode(host->GetId());
    if (!clipboard_ && context) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
    }
    obscureTickCountDown_ = OBSCURE_SHOW_TICKS;
    ProcessInnerPadding();
    textRect_.SetOffset(OffsetF(GetPaddingLeft(), GetPaddingTop()));
    caretRect_.SetWidth(static_cast<float>(CURSOR_WIDTH.ConvertToPx()));
    caretRect_.SetHeight(GetTextOrPlaceHolderFontSize());
    if (textEditingValue_.caretPosition == 0) {
        caretRect_.SetLeft(GetPaddingLeft());
        caretRect_.SetTop(GetPaddingTop());
        caretRect_.SetHeight(PreferredLineHeight());
    }
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    auto renderContext = GetHost()->GetRenderContext();
    if (renderContext->HasBackgroundColor()) {
        paintProperty->UpdateBackgroundColor(renderContext->GetBackgroundColorValue());
    }
    CloseSelectOverlay();
    if (layoutProperty->GetTypeChangedValue(false)) {
        ClearEditingValue();
        layoutProperty->ResetTypeChanged();
        operationRecords_.clear();
        redoOperationRecords_.clear();
    }
    auto maxLength = GetMaxLength();
    if (GreatOrEqual(textEditingValue_.GetWideText().length(), maxLength)) {
        textEditingValue_.text = StringUtils::ToString(textEditingValue_.GetWideText().substr(0, maxLength));
        textEditingValue_.caretPosition = std::clamp(
            textEditingValue_.caretPosition, 0, static_cast<int32_t>(textEditingValue_.GetWideText().length()));
        SetEditingValueToProperty(textEditingValue_.text);
    }
    FireOnChangeIfNeeded();
    caretUpdateType_ = CaretUpdateType::INPUT;
    host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                 : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::FireOnChangeIfNeeded()
{
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->GetNeedFireOnChangeWhenCreateValue(false)) {
        return;
    }
    layoutProperty->UpdateNeedFireOnChangeWhenCreate(false);
    auto eventHub = GetHost()->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnChange(textEditingValue_.text);
}

bool TextFieldPattern::IsDisabled()
{
    auto eventHub = GetHost()->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    return !eventHub->IsEnabled();
}

void TextFieldPattern::ProcessInnerPadding()
{
    auto pipeline = GetHost()->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto themePadding = textFieldTheme->GetPadding();
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    utilPadding_.left = layoutProperty->GetPaddingProperty()->left->GetDimension().ConvertToPx();
    utilPadding_.top = layoutProperty->GetPaddingProperty()->top->GetDimension().ConvertToPx();
    utilPadding_.bottom = layoutProperty->GetPaddingProperty()->bottom->GetDimension().ConvertToPx();
    utilPadding_.right = layoutProperty->GetPaddingProperty()->right->GetDimension().ConvertToPx();
}

void TextFieldPattern::InitLongPressEvent()
{
    CHECK_NULL_VOID_NOLOG(!longPressEvent_);
    auto gesture = GetHost()->GetOrCreateGestureEventHub();
    auto longPressCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleLongPress(info);
    };
    longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressCallback));
    gesture->SetLongPressEvent(longPressEvent_);
}

void TextFieldPattern::HandleLongPress(GestureEvent& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    lastTouchOffset_ = info.GetLocalLocation();
    caretUpdateType_ = isMousePressed_ ? CaretUpdateType::PRESSED : CaretUpdateType::LONG_PRESSED;
    selectionMode_ = SelectionMode::SELECT;
    isSingleHandle_ = false;
    isUsingMouse_ = false;
    LOGI("TextField %{public}d handle long press", GetHost()->GetId());
    auto focusHub = GetHost()->GetOrCreateFocusHub();
    if (!focusHub->IsFocusOnTouch().value_or(true) || !focusHub->RequestFocusImmediately()) {
        LOGE("Long press request focus failed");
        StopTwinkling();
        return;
    }
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TextFieldPattern::ProcessOverlay()
{
    StopTwinkling();
    auto renderContext = GetHost()->GetRenderContext();
    if (renderContext) {
        AnimatePressAndHover(renderContext, 0.0f);
    }
    if (textEditingValue_.text.empty()) {
        CreateSingleHandle();
        return;
    }
    selectionMode_ = SelectionMode::SELECT;
    if (caretUpdateType_ == CaretUpdateType::LONG_PRESSED) {
        if (textEditingValue_.caretPosition == 0) {
            UpdateSelection(0, 0);
        } else if (textEditingValue_.CaretAtLast()) {
            UpdateSelection(textEditingValue_.caretPosition, textEditingValue_.caretPosition);
        } else {
            UpdateSelection(textEditingValue_.caretPosition, textEditingValue_.caretPosition + 1);
        }
    }
    std::vector<RSTypographyProperties::TextBox> tmp;
    GetTextRectsInRange(textSelector_.GetStart(), textSelector_.GetEnd(), tmp);
    auto firstHandlePosition = CalcCursorOffsetByPosition(textSelector_.GetStart());
    OffsetF firstHandleOffset(firstHandlePosition.offset.GetX() + parentGlobalOffset_.GetX(),
        firstHandlePosition.offset.GetY() + parentGlobalOffset_.GetY());
    auto secondHandlePosition = CalcCursorOffsetByPosition(textSelector_.GetEnd());
    OffsetF secondHandleOffset(secondHandlePosition.offset.GetX() + parentGlobalOffset_.GetX(),
        secondHandlePosition.offset.GetY() + parentGlobalOffset_.GetY());
    SizeF handlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), caretRect_.Height() };
    RectF firstHandle;
    firstHandle.SetOffset(firstHandleOffset);
    firstHandle.SetSize(handlePaintSize);
    RectF secondHandle;
    secondHandle.SetOffset(secondHandleOffset);
    secondHandle.SetSize(handlePaintSize);
    LOGD("First handle %{public}s, second handle %{public}s", firstHandle.ToString().c_str(),
        secondHandle.ToString().c_str());
    ShowSelectOverlay(firstHandle, secondHandle);
    textBoxes_ = tmp;
}

void TextFieldPattern::ShowSelectOverlay(
    const std::optional<RectF>& firstHandle, const std::optional<RectF>& secondHandle)
{
    if (!firstHandle.has_value() && !secondHandle.has_value()) {
        LOGW("No handler available");
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto hasDataCallback = [weak = WeakClaim(this), pipeline, firstHandle, secondHandle](bool hasData) {
        auto pattern = weak.Upgrade();
        SelectOverlayInfo selectInfo;
        if (!pattern->IsUsingMouse()) {
            if (firstHandle.has_value()) {
                selectInfo.firstHandle.paintRect = firstHandle.value();
            } else {
                selectInfo.firstHandle.isShow = false;
            }
            if (secondHandle.has_value()) {
                selectInfo.secondHandle.paintRect = secondHandle.value();
            } else {
                selectInfo.secondHandle.isShow = false;
            }
        }
        selectInfo.isSingleHandle = !firstHandle.has_value() || !secondHandle.has_value();
        selectInfo.onHandleMove = [weak](const RectF& handleRect, bool isFirst) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnHandleMove(handleRect, isFirst);
        };
        selectInfo.onHandleMoveDone = [weak](const RectF& handleRect, bool isFirst) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnHandleMoveDone(handleRect, isFirst);
        };
        selectInfo.isUsingMouse = pattern->IsUsingMouse();
        selectInfo.rightClickOffset = pattern->GetRightClickOffset();
        selectInfo.singleLineHeight = pattern->PreferredLineHeight();
        selectInfo.menuInfo.showCopy = !pattern->GetEditingValue().text.empty() && pattern->AllowCopy();
        selectInfo.menuInfo.showCut = !pattern->GetEditingValue().text.empty();
        selectInfo.menuInfo.showCopyAll = !pattern->GetEditingValue().text.empty();
        selectInfo.menuInfo.showPaste = hasData;
        selectInfo.menuInfo.menuIsShow = !pattern->GetEditingValue().text.empty() || hasData;
        selectInfo.menuCallback.onCopy = [weak]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleOnCopy();
            pattern->CloseSelectOverlay();
        };

        selectInfo.menuCallback.onCut = [weak]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleOnCut();
            pattern->CloseSelectOverlay();
        };

        selectInfo.menuCallback.onPaste = [weak]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleOnPaste();
            pattern->CloseSelectOverlay();
        };
        selectInfo.menuCallback.onSelectAll = [weak]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleOnSelectAll();
            pattern->SetNeedCloseOverlay(false);
        };
        auto host = pattern->GetHost();
        CHECK_NULL_VOID_NOLOG(host);
        auto gesture = host->GetOrCreateGestureEventHub();
        gesture->RemoveTouchEvent(pattern->GetTouchListener());

        pattern->SetSelectOverlay(pipeline->GetSelectOverlayManager()->CreateAndShowSelectOverlay(selectInfo));
    };
#if defined(PREVIEW)
    hasDataCallback(!clipRecords_.empty());
#else
    clipboard_->HasData(hasDataCallback);
#endif
}

bool TextFieldPattern::AllowCopy()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) != CopyOptions::None;
}

void TextFieldPattern::OnDetachFromFrameNode(FrameNode* /*node*/)
{
    CloseSelectOverlay();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (HasSurfaceChangedCallback()) {
        LOGD("Unregister surface change callback with id %{public}d", surfaceChangedCallbackId_.value_or(-1));
        pipeline->UnregisterSurfaceChangedCallback(surfaceChangedCallbackId_.value_or(-1));
    }
    if (HasSurfacePositionChangedCallback()) {
        LOGD("Unregister surface position change callback with id %{public}d",
            surfacePositionChangedCallbackId_.value_or(-1));
        pipeline->UnregisterSurfacePositionChangedCallback(surfacePositionChangedCallbackId_.value_or(-1));
    }
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    if (textFieldManager) {
        textFieldManager->ClearOnFocusTextField();
    }
}

void TextFieldPattern::CloseSelectOverlay()
{
    if (selectOverlayProxy_) {
        LOGI("Close select overlay");
        selectOverlayProxy_->Close();
    }
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    gesture->AddTouchEvent(GetTouchListener());
}

bool TextFieldPattern::SelectOverlayIsOn()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN_NOLOG(selectOverlayProxy_, false);
    auto overlayId = selectOverlayProxy_->GetSelectOverlayId();
    return pipeline->GetSelectOverlayManager()->HasSelectOverlay(overlayId);
}

void TextFieldPattern::OnHandleMove(const RectF& handleRect, bool isFirstHandle)
{
    CHECK_NULL_VOID_NOLOG(SelectOverlayIsOn());
    auto localOffset = handleRect.GetOffset() - parentGlobalOffset_;
    auto position = UpdateCaretPositionOnHandleMove(localOffset);
    textEditingValue_.CursorMoveToPosition(position);
    auto caretMetrics = CalcCursorOffsetByPosition(position);
    caretRect_.SetOffset(OffsetF(caretMetrics.offset.GetX(), caretMetrics.offset.GetY()));
    selectionMode_ = isSingleHandle_ ? SelectionMode::NONE : SelectionMode::SELECT;
    caretUpdateType_ = CaretUpdateType::HANDLE_MOVE;
    UpdateTextSelectorByHandleMove(isFirstHandle, position, caretMetrics.offset);
    GetTextRectsInRange(textSelector_.GetStart(), textSelector_.GetEnd(), textBoxes_);
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

int32_t TextFieldPattern::UpdateCaretPositionOnHandleMove(const OffsetF& localOffset)
{
    int32_t position = 0;
    if (!IsTextArea()) {
        if (localOffset.GetX() < contentRect_.GetX()) {
            position = std::max(static_cast<int32_t>(textEditingValue_.caretPosition - 1), 0);
        } else if (GreatOrEqual(localOffset.GetX(), contentRect_.GetX() + contentRect_.Width())) {
            position = std::min(static_cast<int32_t>(textEditingValue_.caretPosition + 1),
                static_cast<int32_t>(textEditingValue_.GetWideText().length()));
        } else {
            Offset offset(localOffset.GetX() - textRect_.GetX(), 0.0f);
            position = ConvertTouchOffsetToCaretPosition(offset);
        }
        return position;
    }
    if (localOffset.GetY() < contentRect_.GetY()) {
        position = ConvertTouchOffsetToCaretPosition(Offset(
            localOffset.GetX() - GetPaddingLeft(), localOffset.GetY() - textRect_.GetY() - PreferredLineHeight()));
    } else if (GreatOrEqual(localOffset.GetY(), contentRect_.GetY() + contentRect_.Height())) {
        position = ConvertTouchOffsetToCaretPosition(Offset(
            localOffset.GetX() - GetPaddingLeft(), localOffset.GetY() - textRect_.GetY() + PreferredLineHeight()));
    } else {
        position = ConvertTouchOffsetToCaretPosition(
            Offset(localOffset.GetX() - GetPaddingLeft(), localOffset.GetY() - textRect_.GetY()));
    }
    return position;
}

void TextFieldPattern::UpdateTextSelectorByHandleMove(
    bool isMovingBase, int32_t position, OffsetF& offsetToParagraphBeginning)
{
    if (isSingleHandle_) {
        textSelector_.selectionBaseOffset = offsetToParagraphBeginning;
        textSelector_.selectionDestinationOffset = textSelector_.selectionBaseOffset;
        UpdateSelection(position);
        return;
    }
    if (isMovingBase) {
        textSelector_.baseOffset = position;
        textSelector_.selectionBaseOffset = offsetToParagraphBeginning;
        return;
    }
    textSelector_.destinationOffset = position;
    textSelector_.selectionDestinationOffset = offsetToParagraphBeginning;
}

void TextFieldPattern::OnHandleMoveDone(const RectF& handleRect, bool isFirstHandle)
{
    CHECK_NULL_VOID_NOLOG(SelectOverlayIsOn());
    caretUpdateType_ = CaretUpdateType::HANDLE_MOVE_DONE;
    isFirstHandle_ = isFirstHandle;
    StopTwinkling();
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TextFieldPattern::SetHandlerOnMoveDone()
{
    if (caretUpdateType_ != CaretUpdateType::HANDLE_MOVE_DONE) {
        return;
    }
    SelectHandleInfo info;
    auto newHandleOffset = parentGlobalOffset_;
    auto handleOffset =
        CalcCursorOffsetByPosition(isFirstHandle_ ? textSelector_.baseOffset : textSelector_.destinationOffset);
    newHandleOffset += handleOffset.offset;
    SizeF handlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), caretRect_.Height() };
    RectF newHandle;
    newHandle.SetOffset(newHandleOffset);
    newHandle.SetSize(handlePaintSize);
    info.paintRect = newHandle;
    selectionMode_ = isSingleHandle_ ? SelectionMode::NONE : SelectionMode::SELECT;
    if (isFirstHandle_) {
        selectOverlayProxy_->UpdateFirstSelectHandleInfo(info);
        return;
    }
    selectOverlayProxy_->UpdateSecondSelectHandleInfo(info);
}

void TextFieldPattern::InitEditingValueText(std::string content)
{
    textEditingValue_.text = std::move(content);
    textEditingValue_.caretPosition = textEditingValue_.GetWideText().length();
    SetEditingValueToProperty(textEditingValue_.text);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateNeedFireOnChangeWhenCreate(true);
}

void TextFieldPattern::InitCaretPosition(std::string content)
{
    textEditingValue_.caretPosition = static_cast<int32_t>(StringUtils::ToWstring(content).length());
}

void TextFieldPattern::InitMouseEvent()
{
    CHECK_NULL_VOID_NOLOG(!mouseEvent_ || !hoverEvent_);
    auto eventHub = GetHost()->GetEventHub<TextFieldEventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();

    auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(info);
        }
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent_);

    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->OnHover(isHover);
        }
    };
    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent_);
}

void TextFieldPattern::OnHover(bool isHover)
{
    auto frame = GetHost();
    CHECK_NULL_VOID(frame);
    auto frameId = frame->GetId();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    isOnHover_ = isHover;
    LOGI("Textfield %{public}d %{public}s", GetHost()->GetId(), isHover ? "on hover" : "exit hover");
    if (enableTouchAndHoverEffect_) {
        auto textfieldPaintProperty = GetPaintProperty<TextFieldPaintProperty>();
        CHECK_NULL_VOID(textfieldPaintProperty);
        auto renderContext = GetHost()->GetRenderContext();
        if (isOnHover_) {
            pipeline->SetMouseStyleHoldNode(frameId);
            pipeline->ChangeMouseStyle(frameId, HasFocus() ? MouseFormat::TEXT_CURSOR : MouseFormat::HAND_POINTING);
            AnimatePressAndHover(renderContext, HOVER_ANIMATION_OPACITY, true);
            GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
            return;
        }
        isOnHover_ = false;
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        pipeline->FreeMouseStyleHoldNode(frameId);
        if (!isMousePressed_) {
            AnimatePressAndHover(renderContext, 0.0f, true);
        }
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void TextFieldPattern::HandleMouseEvent(MouseInfo& info)
{
    auto frame = GetHost();
    CHECK_NULL_VOID(frame);
    auto frameId = frame->GetId();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    if (!IsSearchParentNode()) {
        info.SetStopPropagation(true);
    }
    auto focusHub = GetHost()->GetOrCreateFocusHub();
    if (info.GetButton() == MouseButton::RIGHT_BUTTON) {
        LOGI("Handle mouse right click");
        if (info.GetAction() == MouseAction::PRESS) {
            isMousePressed_ = true;
        }
        if (info.GetAction() == MouseAction::PRESS || info.GetAction() == MouseAction::RELEASE) {
            CloseSelectOverlay();
        }

        if (info.GetAction() == MouseAction::RELEASE) {
            rightClickOffset_ = OffsetF(static_cast<float>(info.GetGlobalLocation().GetX()),
                static_cast<float>(info.GetGlobalLocation().GetY()));
            lastTouchOffset_ = info.GetLocalLocation();
            caretUpdateType_ = CaretUpdateType::RIGHT_CLICK;
            selectionMode_ = SelectionMode::NONE;
            isSingleHandle_ = false;
            isUsingMouse_ = true;
            mouseStatus_ = MouseStatus::RELEASED;
            GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        return;
    }
    if (info.GetAction() == MouseAction::PRESS) {
        LOGI("Handle mouse press");
        CloseSelectOverlay();
        if (!focusHub->IsFocusable()) {
            return;
        }
        isMousePressed_ = true;
        mouseStatus_ = MouseStatus::PRESSED;
        StartTwinkling();
        lastTouchOffset_ = info.GetLocalLocation();
        caretUpdateType_ = CaretUpdateType::PRESSED;
        selectionMode_ = SelectionMode::NONE;
        if (!focusHub->IsFocusOnTouch().value_or(true) || !focusHub->RequestFocusImmediately()) {
            LOGE("Request focus failed, cannot open input method");
            StopTwinkling();
            pipeline->ChangeMouseStyle(frameId, MouseFormat::HAND_GRABBING);
            return;
        }
        pipeline->ChangeMouseStyle(frameId, MouseFormat::TEXT_CURSOR);
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        return;
    }
    if (info.GetAction() == MouseAction::RELEASE) {
        LOGI("Handle mouse release");
        CloseSelectOverlay();
        caretUpdateType_ = CaretUpdateType::NONE;
        isMousePressed_ = false;
        mouseStatus_ = MouseStatus::RELEASED;
        pipeline->ChangeMouseStyle(frameId, HasFocus() ? MouseFormat::TEXT_CURSOR : MouseFormat::HAND_POINTING);
        if (!focusHub->IsCurrentFocus()) {
            return;
        }
        if (RequestKeyboard(false, true, true)) {
            auto eventHub = GetHost()->GetEventHub<TextFieldEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->FireOnEditChanged(true);
            GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    }

    if (info.GetAction() == MouseAction::MOVE) {
        if (!isMousePressed_) {
            return;
        }
        caretUpdateType_ = CaretUpdateType::EVENT;
        lastTouchOffset_ = info.GetLocalLocation();
        mouseStatus_ = MouseStatus::MOVE;
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void TextFieldPattern::UpdatePositionOfParagraph(int32_t position)
{
    textEditingValue_.CursorMoveToPosition(position);
}

void TextFieldPattern::UpdateTextFieldManager(const Offset& offset, float height)
{
    auto context = GetHost()->GetContext();
    CHECK_NULL_VOID(context);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    textFieldManager->SetClickPosition(offset);
    textFieldManager->SetHeight(height);
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
        UpdateConfiguration();
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
        MiscServices::InputAttribute inputAttribute;
        inputAttribute.inputPattern = (int32_t)keyboard_;
        inputAttribute.enterKeyType = (int32_t)GetTextInputActionValue(TextInputAction::DONE);
        inputMethod->Attach(textChangeListener_, needShowSoftKeyboard, inputAttribute);
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        imeAttached_ = true;
#endif
#endif
    }
    return true;
}

bool TextFieldPattern::CloseKeyboard(bool forceClose)
{
    LOGI("Request close soft keyboard");
    if (forceClose) {
        StopTwinkling();
#if defined(ENABLE_STANDARD_INPUT)
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        if (!imeAttached_) {
            return false;
        }
#endif
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        if (!inputMethod) {
            LOGE("Request close soft keyboard failed because input method is null.");
            return false;
        }
        inputMethod->HideTextInput();
        inputMethod->Close();
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        imeAttached_ = false;
#endif
#endif
        return true;
    }
    return false;
}

void TextFieldPattern::ProcessPasswordIcon()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) != TextInputType::VISIBLE_PASSWORD) {
        return;
    }
    bool showPasswordIcon = layoutProperty->GetShowPasswordIconValue(true);
    if (!showPasswordIcon) {
        return;
    }
    if ((!layoutProperty->HasHidePasswordSourceInfo() || !hidePasswordImageLoadingCtx_) && textObscured_) {
        ImageSourceInfo hidePasswordSourceInfo = GetImageSourceInfoFromTheme(textObscured_);
        UpdateInternalResource(hidePasswordSourceInfo);
        LoadNotifier hideIconLoadNotifier(CreateDataReadyCallback(textObscured_),
            CreateLoadSuccessCallback(textObscured_), CreateLoadFailCallback(textObscured_));
        hidePasswordImageLoadingCtx_ =
            AceType::MakeRefPtr<ImageLoadingContext>(hidePasswordSourceInfo, std::move(hideIconLoadNotifier));
        hidePasswordImageLoadingCtx_->LoadImageData();
        return;
    }
    if ((!layoutProperty->HasShowPasswordSourceInfo() || !showPasswordImageLoadingCtx_) && !textObscured_) {
        ImageSourceInfo showPasswordSourceInfo = GetImageSourceInfoFromTheme(textObscured_);
        UpdateInternalResource(showPasswordSourceInfo);
        LoadNotifier showIconLoadNotifier(CreateDataReadyCallback(textObscured_),
            CreateLoadSuccessCallback(textObscured_), CreateLoadFailCallback(textObscured_));
        showPasswordImageLoadingCtx_ =
            AceType::MakeRefPtr<ImageLoadingContext>(showPasswordSourceInfo, std::move(showIconLoadNotifier));
        showPasswordImageLoadingCtx_->LoadImageData();
        return;
    }
}

ImageSourceInfo TextFieldPattern::GetImageSourceInfoFromTheme(bool checkHidePasswordIcon)
{
    auto context = GetHost()->GetContext();
    CHECK_NULL_RETURN(context, {});
    ImageSourceInfo imageSourceInfo;
    auto theme = context->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(theme, imageSourceInfo);
    if (checkHidePasswordIcon) {
        imageSourceInfo.SetResourceId(InternalResource::ResourceId::HIDE_PASSWORD_SVG);
        return imageSourceInfo;
    }
    imageSourceInfo.SetResourceId(InternalResource::ResourceId::SHOW_PASSWORD_SVG);
    return imageSourceInfo;
}

void TextFieldPattern::UpdateInternalResource(ImageSourceInfo& sourceInfo)
{
    CHECK_NULL_VOID_NOLOG(sourceInfo.IsInternalResource());
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    CHECK_NULL_VOID(iconTheme);
    auto iconPath = iconTheme->GetIconPath(sourceInfo.GetResourceId());
    if (iconPath.empty()) {
        LOGE("Icon path empty");
        return;
    }
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    if (IsDisabled()) {
        sourceInfo.SetSrc(iconPath, theme->GetDisabledIconFillColor());
    } else {
        sourceInfo.SetSrc(iconPath);
    }
    sourceInfo.SetDimension(DEFAULT_FONT, DEFAULT_FONT);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (textObscured_) {
        layoutProperty->UpdateHidePasswordSourceInfo(sourceInfo);
        return;
    }
    layoutProperty->UpdateShowPasswordSourceInfo(sourceInfo);
}

LoadSuccessNotifyTask TextFieldPattern::CreateLoadSuccessCallback(bool checkHidePasswordIcon)
{
    auto task = [weak = WeakClaim(this), checkHidePasswordIcon](const ImageSourceInfo& /* sourceInfo */) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnImageLoadSuccess(checkHidePasswordIcon);
    };
    return task;
}

DataReadyNotifyTask TextFieldPattern::CreateDataReadyCallback(bool checkHidePasswordIcon)
{
    auto task = [weak = WeakClaim(this), checkHidePasswordIcon](const ImageSourceInfo& /* sourceInfo */) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnImageDataReady(checkHidePasswordIcon);
    };
    return task;
}

LoadFailNotifyTask TextFieldPattern::CreateLoadFailCallback(bool checkHidePasswordIcon)
{
    auto task = [weak = WeakClaim(this), checkHidePasswordIcon](const ImageSourceInfo& /* sourceInfo */) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnImageLoadFail(checkHidePasswordIcon);
    };
    return task;
}

void TextFieldPattern::OnImageLoadFail(bool checkHidePasswordIcon)
{
    LOGE("Image data load fail for %{public}s", checkHidePasswordIcon ? "hide icon" : "show icon");
}

void TextFieldPattern::OnImageDataReady(bool checkHidePasswordIcon)
{
    ACE_SCOPED_TRACE("TextFieldPattern::OnImageDataReady");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    LOGI("Image data ready for %{public}s", checkHidePasswordIcon ? "hide icon" : "show icon");

    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TextFieldPattern::OnImageLoadSuccess(bool checkHidePasswordIcon)
{
    ACE_SCOPED_TRACE("TextFieldPattern::OnImageLoadSuccess");
    ImagePaintConfig config;
    if (checkHidePasswordIcon) {
        LOGI("Load hide icon successfully");
        hidePasswordCanvasImage_ = hidePasswordImageLoadingCtx_->MoveCanvasImage();
        config.srcRect_ = hidePasswordImageLoadingCtx_->GetSrcRect();
        config.dstRect_ = hidePasswordImageLoadingCtx_->GetDstRect();
        config.isSvg_ = true;
        hidePasswordCanvasImage_->SetPaintConfig(config);
        return;
    }
    LOGI("Load show icon successfully");
    showPasswordCanvasImage_ = showPasswordImageLoadingCtx_->MoveCanvasImage();
    config.srcRect_ = showPasswordImageLoadingCtx_->GetSrcRect();
    config.dstRect_ = showPasswordImageLoadingCtx_->GetDstRect();
    config.isSvg_ = true;
    showPasswordCanvasImage_->SetPaintConfig(config);
}

void TextFieldPattern::OnTextInputActionUpdate(TextInputAction value) {}

void TextFieldPattern::InsertValue(const std::string& insertValue)
{
    LOGD("Insert value '%{public}s'", insertValue.c_str());
    auto originLength = static_cast<uint32_t>(textEditingValue_.GetWideText().length());
    if (originLength >= GetMaxLength()) {
        LOGW("Max length reached");
        return;
    }

    std::string valueToUpdate;
    auto wideInsertValue = StringUtils::ToWstring(insertValue);
    if (originLength + wideInsertValue.length() >= GetMaxLength()) {
        valueToUpdate = StringUtils::ToString(wideInsertValue.substr(0, GetMaxLength() - originLength));
    } else {
        valueToUpdate = insertValue;
    }
    std::string oldText = textEditingValue_.text;
    auto caretStart = 0;
    std::string result;
    auto textFieldLayoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    if (InSelectMode()) {
        caretStart = textSelector_.GetStart();
    } else {
        caretStart = textEditingValue_.caretPosition;
    }
    EditingValueFilter(valueToUpdate, result);
    if (result.empty()) {
        return;
    }
    if (InSelectMode()) {
        textEditingValue_.text = textEditingValue_.GetValueBeforePosition(textSelector_.GetStart()) + result +
                                 textEditingValue_.GetValueAfterPosition(textSelector_.GetEnd());
    } else {
        textEditingValue_.text =
            textEditingValue_.GetValueBeforeCursor() + result + textEditingValue_.GetValueAfterCursor();
    }
    textEditingValue_.CursorMoveToPosition(caretStart + static_cast<int32_t>(StringUtils::ToWstring(result).length()));
    SetEditingValueToProperty(textEditingValue_.text);
    UpdateEditingValueToRecord();
    caretUpdateType_ = CaretUpdateType::INPUT;
    selectionMode_ = SelectionMode::NONE;
    CloseSelectOverlay();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // If the parent node is a Search, the Search callback is executed.
    if (IsSearchParentNode()) {
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
        auto eventHub = parentFrameNode->GetEventHub<SearchEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->UpdateChangeEvent(textEditingValue_.text);
        parentFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }

    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnChange(textEditingValue_.text);
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                 : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::UpdateEditingValueToRecord()
{
    if (operationRecords_.size() >= RECORD_MAX_LENGTH) {
        // case of max length is 0
        if (operationRecords_.empty()) {
            return;
        }
        operationRecords_.erase(operationRecords_.begin());
    }
    operationRecords_.emplace_back(textEditingValue_);
}

bool TextFieldPattern::FilterWithRegex(
    const std::string& filter, const std::string& valueToUpdate, std::string& result, bool needToEscape)
{
    if (filter.empty() || valueToUpdate.empty()) {
        LOGD("Text is empty or filter is empty");
        return false;
    }
    std::string escapeFilter;
    if (needToEscape && !TextFieldControllerBase::EscapeString(filter, escapeFilter)) {
        LOGE("Escape filter string failed");
        return false;
    }
    if (!needToEscape) {
        escapeFilter = filter;
    }
    std::regex filterRegex(escapeFilter);
    auto errorText = regex_replace(valueToUpdate, filterRegex, "");
    RemoveErrorTextFromValue(valueToUpdate, errorText, result);
    if (!errorText.empty()) {
        auto textFieldEventHub = GetHost()->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_RETURN(textFieldEventHub, false);
        LOGI("Error text %{private}s", errorText.c_str());
        textFieldEventHub->FireOnInputFilterError(errorText);
    }
    return !errorText.empty();
}

void TextFieldPattern::EditingValueFilter(std::string& valueToUpdate, std::string& result)
{
    auto textFieldLayoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    // filter text editing value with user defined filter first
    auto inputFilter = textFieldLayoutProperty->GetInputFilterValue("");
    bool textChanged = false;
    if (!inputFilter.empty()) {
        textChanged |= FilterWithRegex(inputFilter, valueToUpdate, result);
    }
    if (textChanged) {
        valueToUpdate = result;
        result = "";
        textChanged = false;
    }
    switch (textFieldLayoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED)) {
        case TextInputType::NUMBER: {
            textChanged |= FilterWithRegex(DIGIT_WHITE_LIST, valueToUpdate, result);
            break;
        }
        case TextInputType::PHONE: {
            textChanged |= FilterWithRegex(PHONE_WHITE_LIST, valueToUpdate, result);
            break;
        }
        case TextInputType::EMAIL_ADDRESS: {
            if (valueToUpdate == "@") {
                auto charExists = valueToUpdate.find('@') != std::string::npos;
                textChanged = !charExists;
                result = charExists ? "" : valueToUpdate;
            } else {
                textChanged |= FilterWithRegex(EMAIL_WHITE_LIST, valueToUpdate, result);
            }
            break;
        }
        case TextInputType::URL: {
            textChanged |= FilterWithRegex(URL_WHITE_LIST, valueToUpdate, result);
            break;
        }
        default: {
            // No need limit.
        }
    }
    if (!textChanged) {
        result = valueToUpdate;
    }
}

float TextFieldPattern::PreferredTextHeight(bool isPlaceholder)
{
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0.0f);
    // check if util paragraph need to update
    if (!isPlaceholder &&
        (textLineHeightUtilParagraph_ && !layoutProperty->GetPreferredTextLineHeightNeedToUpdateValue(true))) {
        return static_cast<float>(textLineHeightUtilParagraph_->GetHeight());

    } else if (isPlaceholder && (placeholderLineHeightUtilParagraph_ &&
                                    !layoutProperty->GetPreferredPlaceholderLineHeightNeedToUpdateValue(true))) {
        return static_cast<float>(placeholderLineHeightUtilParagraph_->GetHeight());
    }
    auto pipeline = GetHost()->GetContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, 0.0f);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    std::string textContent;
    TextStyle textStyle;
    // use text or placeHolder value if exists, space otherwise
    if (!isPlaceholder) {
        TextFieldLayoutAlgorithm::UpdateTextStyle(layoutProperty, textFieldTheme, textStyle, false);
        textContent = "a";
    } else {
        TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyle(layoutProperty, textFieldTheme, textStyle, false);
        textContent = "b";
    }
    RSParagraphStyle paraStyle;
    paraStyle.textDirection_ = ToRSTextDirection(TextFieldLayoutAlgorithm::GetTextDirection(textEditingValue_.text));
    paraStyle.textAlign_ = ToRSTextAlign(textStyle.GetTextAlign());
    paraStyle.maxLines_ = textStyle.GetMaxLines();
    paraStyle.locale_ = Localization::GetInstance()->GetFontLocale();
    paraStyle.wordBreakType_ = ToRSWordBreakType(textStyle.GetWordBreak());
    paraStyle.fontSize_ = textStyle.GetFontSize().ConvertToPx();
    if (textStyle.GetTextOverflow() == TextOverflow::ELLIPSIS) {
        paraStyle.ellipsis_ = RSParagraphStyle::ELLIPSIS;
    }
    auto builder = RSParagraphBuilder::CreateRosenBuilder(paraStyle, RSFontCollection::GetInstance(false));
    builder->PushStyle(ToRSTextStyle(PipelineContext::GetCurrentContext(), textStyle));
    StringUtils::TransformStrCase(textEditingValue_.text, static_cast<int32_t>(textStyle.GetTextCase()));
    builder->AddText(StringUtils::Str8ToStr16(textContent));
    builder->Pop();
    if (!isPlaceholder) {
        textLineHeightUtilParagraph_ = builder->Build();
        textLineHeightUtilParagraph_->Layout(std::numeric_limits<double>::infinity());
        layoutProperty->UpdatePreferredTextLineHeightNeedToUpdate(false);
        return static_cast<float>(textLineHeightUtilParagraph_->GetHeight());
    }
    placeholderLineHeightUtilParagraph_ = builder->Build();
    placeholderLineHeightUtilParagraph_->Layout(std::numeric_limits<double>::infinity());
    layoutProperty->UpdatePreferredPlaceholderLineHeightNeedToUpdate(false);
    return static_cast<float>(placeholderLineHeightUtilParagraph_->GetHeight());
}

float TextFieldPattern::PreferredLineHeight()
{
    return PreferredTextHeight(textEditingValue_.text.empty());
}

void TextFieldPattern::OnCursorMoveDone()
{
    CloseSelectOverlay();
    caretUpdateType_ = CaretUpdateType::EVENT;
    selectionMode_ = SelectionMode::NONE;
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TextFieldPattern::CursorMoveLeft()
{
    LOGI("Handle cursor move left");
    if (InSelectMode() && selectionMode_ == SelectionMode::SELECT_ALL) {
        textEditingValue_.caretPosition = 0;
    } else if (InSelectMode()) {
        textBoxes_.clear();
    } else {
        textEditingValue_.CursorMoveLeft();
    }
    OnCursorMoveDone();
}

void TextFieldPattern::CursorMoveRight()
{
    LOGI("Handle cursor move right");
    if (InSelectMode() && selectionMode_ == SelectionMode::SELECT_ALL) {
        textEditingValue_.caretPosition = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    } else if (InSelectMode()) {
        textBoxes_.clear();
    } else {
        textEditingValue_.CursorMoveRight();
    }
    OnCursorMoveDone();
}

void TextFieldPattern::CursorMoveUp()
{
    LOGI("Handle cursor move up");
    CHECK_NULL_VOID_NOLOG(IsTextArea());
    float verticalOffset = caretRect_.GetY() - PreferredLineHeight();
    textEditingValue_.caretPosition = static_cast<int32_t>(
        paragraph_->GetGlyphPositionAtCoordinateWithCluster(caretRect_.GetX(), verticalOffset).pos_);
    OnCursorMoveDone();
}

void TextFieldPattern::CursorMoveDown()
{
    LOGI("Handle cursor move down");
    CHECK_NULL_VOID_NOLOG(IsTextArea());
    float verticalOffset = caretRect_.GetY() + PreferredLineHeight();
    textEditingValue_.caretPosition = static_cast<int32_t>(
        paragraph_->GetGlyphPositionAtCoordinateWithCluster(caretRect_.GetX(), verticalOffset).pos_);
    OnCursorMoveDone();
}

void TextFieldPattern::Delete(int32_t start, int32_t end)
{
    LOGI("Handle Delete within [%{public}d, %{public}d]", start, end);
    textEditingValue_.text =
        textEditingValue_.GetValueBeforePosition(start) + textEditingValue_.GetValueAfterPosition(end);
    textEditingValue_.caretPosition = start;
    SetEditingValueToProperty(textEditingValue_.text);
    FireEventHubOnChange(GetEditingValue().text);
    selectionMode_ = SelectionMode::NONE;
    caretUpdateType_ = CaretUpdateType::DEL;
    CloseSelectOverlay();
    UpdateEditingValueToRecord();
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    GetHost()->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                      : PROPERTY_UPDATE_MEASURE);
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
    UpdateEditingValueToRecord();
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    GetHost()->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                      : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::PerformAction(TextInputAction action, bool forceCloseKeyboard)
{
    LOGI("PerformAction  %{public}d", static_cast<int32_t>(action));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // If the parent node is a Search, the Search callback is executed.
    if (IsSearchParentNode()) {
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
        auto eventHub = parentFrameNode->GetEventHub<SearchEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->UpdateSubmitEvent(textEditingValue_.text);
        CloseKeyboard(forceCloseKeyboard);
        return;
    }

    if (IsTextArea()) {
        if (GetInputFilter() != "\n") {
            InsertValue("\n");
        }
        return;
    }
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    eventHub->FireOnSubmit(static_cast<int32_t>(action));
    CloseKeyboard(forceCloseKeyboard);
}

void TextFieldPattern::OnValueChanged(bool needFireChangeEvent, bool needFireSelectChangeEvent) {}

void TextFieldPattern::OnAreaChangedInner()
{
    CHECK_NULL_VOID_NOLOG(SelectOverlayIsOn());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto parentGlobalOffset = host->GetPaintRectOffset() - context->GetRootRect().GetOffset();
    if (parentGlobalOffset != parentGlobalOffset_) {
        parentGlobalOffset_ = parentGlobalOffset;
        textSelector_.selectionBaseOffset.SetX(CalcCursorOffsetByPosition(textSelector_.GetStart()).offset.GetX());
        textSelector_.selectionDestinationOffset.SetX(CalcCursorOffsetByPosition(textSelector_.GetEnd()).offset.GetX());
        UpdateSelection(textSelector_.GetStart(), textSelector_.GetEnd());
        if (isSingleHandle_) {
            CloseSelectOverlay();
            CreateSingleHandle();
            return;
        }
        ProcessOverlay();
        selectionMode_ = SelectionMode::SELECT;
    }
}

void TextFieldPattern::OnVisibleChange(bool isVisible)
{
    LOGI("visible change to %{public}d", isVisible);
    if (!isVisible) {
        LOGI("TextField is not visible");
        caretUpdateType_ = CaretUpdateType::INPUT;
        selectionMode_ = SelectionMode::NONE;
        CloseKeyboard(true);
        CloseSelectOverlay();
    }
}

void TextFieldPattern::HandleSurfaceChanged(
    int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight) const
{
    LOGI("Textfield handle surface change, new width %{public}d, new height %{public}d, prev width %{public}d, prev "
         "height %{public}d",
        newWidth, newHeight, prevWidth, prevHeight);
    UpdateCaretInfoToController();
}

void TextFieldPattern::HandleSurfacePositionChanged(int32_t posX, int32_t posY) const
{
    LOGI("Textfield handle surface position change, posX %{public}d, posY %{public}d", posX, posY);
    UpdateCaretInfoToController();
}

void TextFieldPattern::DeleteForward(int32_t length)
{
    LOGI("Handle DeleteForward %{public}d characters", length);
    if (textEditingValue_.caretPosition <= 0) {
        LOGW("Caret position at the beginning , cannot DeleteForward");
        return;
    }
    if (InSelectMode()) {
        Delete(textSelector_.GetStart(), textSelector_.GetEnd());
        return;
    }
    auto start = std::max(textEditingValue_.caretPosition - length, 0);
    auto end =
        std::min(textEditingValue_.caretPosition, static_cast<int32_t>(textEditingValue_.GetWideText().length()));
    textEditingValue_.text =
        textEditingValue_.GetValueBeforePosition(start) + textEditingValue_.GetValueAfterPosition(end);
    textEditingValue_.CursorMoveToPosition(textEditingValue_.caretPosition - length);
    SetEditingValueToProperty(textEditingValue_.text);
    FireEventHubOnChange(GetEditingValue().text);
    selectionMode_ = SelectionMode::NONE;
    caretUpdateType_ = CaretUpdateType::DEL;
    CloseSelectOverlay();
    UpdateEditingValueToRecord();
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    GetHost()->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                      : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::DeleteBackward(int32_t length)
{
    LOGI("Handle DeleteBackward %{public}d characters", length);
    if (textEditingValue_.caretPosition >= static_cast<int32_t>(textEditingValue_.GetWideText().length())) {
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
    CloseSelectOverlay();
    UpdateEditingValueToRecord();
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    GetHost()->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                      : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::AfterSelection()
{
    LOGI("Selection %{public}s, caret position %{public}d", textSelector_.ToString().c_str(),
        textEditingValue_.caretPosition);
    GetTextRectsInRange(textSelector_.GetStart(), textSelector_.GetEnd(), textBoxes_);
    caretUpdateType_ = CaretUpdateType::EVENT;
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    GetHost()->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                      : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::HandleSelectionUp()
{
    LOGI("Handle selection up");
    if (!IsTextArea()) {
        LOGW("Unsupported operation for text field");
        return;
    }
    if (selectionMode_ != SelectionMode::SELECT) {
        UpdateSelection(textEditingValue_.caretPosition);
    }
    auto newOffsetY = caretRect_.GetY() - PreferredLineHeight() * 0.5 - textRect_.GetY();
    textEditingValue_.caretPosition =
        static_cast<int32_t>(paragraph_->GetGlyphPositionAtCoordinateWithCluster(caretRect_.GetX(), newOffsetY).pos_);
    textSelector_.destinationOffset = textEditingValue_.caretPosition;
    selectionMode_ = SelectionMode::SELECT;
    if (textSelector_.baseOffset == textSelector_.destinationOffset) {
        selectionMode_ = SelectionMode::NONE;
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionDown()
{
    LOGI("Handle selection down");
    if (!IsTextArea()) {
        LOGW("Unsupported operation for text field");
        return;
    }
    if (selectionMode_ != SelectionMode::SELECT) {
        UpdateSelection(textEditingValue_.caretPosition);
    }
    auto newOffsetY = caretRect_.GetY() + PreferredLineHeight() * 1.5 - textRect_.GetY();
    textEditingValue_.caretPosition =
        static_cast<int32_t>(paragraph_->GetGlyphPositionAtCoordinateWithCluster(caretRect_.GetX(), newOffsetY).pos_);
    textSelector_.destinationOffset = textEditingValue_.caretPosition;
    selectionMode_ = SelectionMode::SELECT;
    if (textSelector_.baseOffset == textSelector_.destinationOffset) {
        selectionMode_ = SelectionMode::NONE;
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionLeft()
{
    LOGI("Handle selection left");
    if (!InSelectMode()) {
        if (textEditingValue_.caretPosition == 0) {
            LOGW("Caret position at beginning, cannot update selection to left");
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
    AfterSelection();
}

void TextFieldPattern::HandleSelectionRight()
{
    LOGI("Handle selection right");
    // if currently not in select mode, reset baseOffset and move destinationOffset and caret position
    if (!InSelectMode()) {
        if (textEditingValue_.caretPosition == static_cast<int32_t>(textEditingValue_.GetWideText().length())) {
            LOGW("Caret position at the end, cannot update selection to right");
            return;
        }
        textSelector_.baseOffset = textEditingValue_.caretPosition;
        textSelector_.destinationOffset =
            std::min(textSelector_.baseOffset + 1, static_cast<int32_t>(textEditingValue_.GetWideText().length()));
        textEditingValue_.caretPosition = textSelector_.destinationOffset;
        selectionMode_ = SelectionMode::SELECT;
    } else {
        // if currently not in select mode, move destinationOffset and caret position only
        textSelector_.destinationOffset = std::min(
            textSelector_.destinationOffset + 1, static_cast<int32_t>(textEditingValue_.GetWideText().length()));
        textEditingValue_.caretPosition = textSelector_.destinationOffset;
        if (textSelector_.destinationOffset == textSelector_.baseOffset) {
            selectionMode_ = SelectionMode::NONE;
        }
    }
    AfterSelection();
}

void TextFieldPattern::SetCaretPosition(int32_t position)
{
    LOGI("Set caret position to %{public}d", position);
    textEditingValue_.caretPosition =
        std::clamp(position, 0, static_cast<int32_t>(textEditingValue_.GetWideText().length()));
    selectionMode_ = SelectionMode::NONE;
    caretUpdateType_ = CaretUpdateType::EVENT;
    CloseSelectOverlay();
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
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

std::string TextFieldPattern::TextInputTypeToString() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    switch (layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED)) {
        case TextInputType::NUMBER:
            return "InputType.Number";
        case TextInputType::EMAIL_ADDRESS:
            return "InputType.Email";
        case TextInputType::VISIBLE_PASSWORD:
            return "InputType.Password";
        default:
            return "InputType.Normal";
    }
}

std::string TextFieldPattern::TextInputActionToString() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    switch (GetTextInputActionValue(TextInputAction::DONE)) {
        case TextInputAction::GO:
            return "EnterKeyType.Go";
        case TextInputAction::SEARCH:
            return "EnterKeyType.Search";
        case TextInputAction::SEND:
            return "EnterKeyType.Send";
        case TextInputAction::NEXT:
            return "EnterKeyType.Next";
        default:
            return "EnterKeyType.Done";
    }
}

std::string TextFieldPattern::GetPlaceholderFont() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    auto context = GetHost()->GetContext();
    CHECK_NULL_RETURN(context, "");
    auto theme = context->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(theme, "");
    auto jsonValue = JsonUtil::Create(true);
    if (layoutProperty->GetPlaceholderItalicFontStyle().value_or(Ace::FontStyle::NORMAL) == Ace::FontStyle::NORMAL) {
        jsonValue->Put("style", "FontStyle.Normal");
    } else {
        jsonValue->Put("style", "FontStyle.Italic");
    }
    // placeholder font size not exist in theme, use normal font size by default
    if (!layoutProperty->GetPlaceholderFontSize()) {
        jsonValue->Put("size", GetFontSize().c_str());
    } else {
        jsonValue->Put("size", layoutProperty->GetPlaceholderFontSize()->ToString().c_str());
    }
    auto weight = layoutProperty->GetPlaceholderFontWeightValue(theme->GetFontWeight());
    switch (weight) {
        case FontWeight::W100:
            jsonValue->Put("weight", "100");
            break;
        case FontWeight::W200:
            jsonValue->Put("weight", "200");
            break;
        case FontWeight::W300:
            jsonValue->Put("weight", "300");
            break;
        case FontWeight::W400:
            jsonValue->Put("weight", "400");
            break;
        case FontWeight::W500:
            jsonValue->Put("weight", "500");
            break;
        case FontWeight::W600:
            jsonValue->Put("weight", "600");
            break;
        case FontWeight::W700:
            jsonValue->Put("weight", "700");
            break;
        case FontWeight::W800:
            jsonValue->Put("weight", "800");
            break;
        case FontWeight::W900:
            jsonValue->Put("weight", "900");
            break;
        default:
            jsonValue->Put("fontWeight", V2::ConvertWrapFontWeightToStirng(weight).c_str());
    }
    auto family = layoutProperty->GetPlaceholderFontFamilyValue({ "sans-serif" });
    std::string jsonFamily = ConvertFontFamily(family);
    jsonValue->Put("fontFamily", jsonFamily.c_str());
    return jsonValue->ToString();
}

RefPtr<TextFieldTheme> TextFieldPattern::GetTheme() const
{
    auto context = GetHost()->GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto theme = context->GetTheme<TextFieldTheme>();
    return theme;
}

std::string TextFieldPattern::GetTextColor() const
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, "");
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return layoutProperty->GetTextColorValue(theme->GetTextColor()).ColorToString();
}

std::string TextFieldPattern::GetCaretColor() const
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, "");
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, "");
    return paintProperty->GetCursorColorValue(theme->GetCursorColor()).ColorToString();
}

std::string TextFieldPattern::GetPlaceholderColor() const
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, "");
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return layoutProperty->GetPlaceholderTextColorValue(theme->GetTextColor()).ColorToString();
}

std::string TextFieldPattern::GetFontSize() const
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, "");
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return layoutProperty->GetFontSizeValue(theme->GetFontSize()).ToString();
}

Ace::FontStyle TextFieldPattern::GetItalicFontStyle() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, Ace::FontStyle::NORMAL);
    return layoutProperty->GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL);
}

FontWeight TextFieldPattern::GetFontWeight() const
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, FontWeight::NORMAL);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, FontWeight::NORMAL);
    return layoutProperty->GetFontWeightValue(theme->GetFontWeight());
}

std::string TextFieldPattern::GetFontFamily() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "HarmonyOS Sans");
    auto family = layoutProperty->GetFontFamilyValue({ "HarmonyOS Sans" });
    return ConvertFontFamily(family);
}

TextAlign TextFieldPattern::GetTextAlign() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, TextAlign::START);
    return layoutProperty->GetTextAlign().value_or(TextAlign::START);
}

uint32_t TextFieldPattern::GetMaxLength() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, Infinity<uint32_t>());
    return layoutProperty->HasMaxLength() ? layoutProperty->GetMaxLengthValue(Infinity<uint32_t>())
                                          : Infinity<uint32_t>();
}

std::string TextFieldPattern::GetPlaceHolder() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return layoutProperty->GetPlaceholderValue("");
}

std::string TextFieldPattern::GetInputFilter() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return layoutProperty->GetInputFilterValue("");
}

bool TextFieldPattern::IsSearchParentNode()
{
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(GetHost()->GetParent());
    return parentFrameNode && parentFrameNode->GetTag() == V2::SEARCH_ETS_TAG;
}

void TextFieldPattern::SearchRequestKeyboard()
{
    StartTwinkling();
    caretUpdateType_ = CaretUpdateType::PRESSED;
    selectionMode_ = SelectionMode::NONE;
    if (RequestKeyboard(false, true, true)) {
        auto eventHub = GetHost()->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnEditChanged(true);
    }
}

void TextFieldPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("placeholder", GetPlaceHolder().c_str());
    json->Put("text", textEditingValue_.text.c_str());
    json->Put("fontSize", GetFontSize().c_str());
    json->Put("fontColor", GetTextColor().c_str());
    json->Put("fontStyle", GetItalicFontStyle() == Ace::FontStyle::NORMAL ? "FontStyle.Normal" : "FontStyle.Italic");
    json->Put("fontWeight", V2::ConvertWrapFontWeightToStirng(GetFontWeight()).c_str());
    json->Put("fontFamily", GetFontFamily().c_str());
    json->Put("textAlign", V2::ConvertWrapTextAlignToString(GetTextAlign()).c_str());
    json->Put("caretColor", GetCaretColor().c_str());
    json->Put("type", TextInputTypeToString().c_str());
    json->Put("placeholderColor", GetPlaceholderColor().c_str());
    json->Put("placeholderFont", GetPlaceholderFont().c_str());
    json->Put("enterKeyType", TextInputActionToString().c_str());
    auto maxLength = GetMaxLength();
    json->Put("maxLength", GreatOrEqual(maxLength, Infinity<uint32_t>()) ? "INF" : std::to_string(maxLength).c_str());
    json->Put("inputFilter", GetInputFilter().c_str());
}

} // namespace OHOS::Ace::NG
