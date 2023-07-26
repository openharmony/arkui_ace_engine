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
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_controller.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/paragraph.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_v2/inspector/utils.h"
#include "core/image/image_source_info.h"
#include "core/pipeline_ng/pipeline_context.h"
#if not defined(ACE_UNITTEST)
#if defined(ENABLE_STANDARD_INPUT)
#include "core/components_ng/pattern/text_field/on_text_changed_listener_impl.h"
#endif
#endif
#ifdef ENABLE_DRAG_FRAMEWORK
#include "core/common/udmf/udmf_client.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension BORDER_DEFAULT_WIDTH = 0.0_vp;
constexpr Dimension ERROR_BORDER_WIDTH = 1.0_vp;
constexpr Dimension OVER_COUNT_BORDER_WIDTH = 1.0_vp;
constexpr Dimension INLINE_BORDER_WIDTH = 2.0_vp;
constexpr Dimension DEFAULT_FONT = Dimension(16, DimensionUnit::FP);
constexpr float HOVER_ANIMATION_OPACITY = 0.05f;
constexpr float PRESS_ANIMATION_OPACITY = 0.1f;
// uncertainty range when comparing selectedTextBox to contentRect
constexpr float BOX_EPSILON = 0.5f;
constexpr uint32_t TWINKLING_INTERVAL_MS = 500;
constexpr uint32_t RECORD_MAX_LENGTH = 20;
constexpr uint32_t OBSCURE_SHOW_TICKS = 3;
constexpr uint32_t FIND_TEXT_ZERO_INDEX = 1;
constexpr char16_t OBSCURING_CHARACTER = u'•';
constexpr char16_t OBSCURING_CHARACTER_FOR_AR = u'*';
const std::string NEWLINE = "\n";
const std::wstring WIDE_NEWLINE = StringUtils::ToWstring(NEWLINE);
const std::string DIGIT_WHITE_LIST = "[0-9]";
const std::string PHONE_WHITE_LIST = "[\\d\\-\\+\\*\\#]+";
const std::string EMAIL_WHITE_LIST = "[\\w.]";
const std::string URL_WHITE_LIST = "[a-zA-z]+://[^\\s]*";
const std::string SHOW_PASSWORD_SVG = "SYS_SHOW_PASSWORD_SVG";
const std::string HIDE_PASSWORD_SVG = "SYS_HIDE_PASSWORD_SVG";

void SwapIfLarger(int32_t& a, int32_t& b)
{
    if (a > b) {
        std::swap(a, b);
    }
}

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

TextFieldPattern::TextFieldPattern() : twinklingInterval_(TWINKLING_INTERVAL_MS)
{
    // add version protection, enable keyboard as default start from API 10 or higher
    if (PipelineBase::GetCurrentContext() && PipelineBase::GetCurrentContext()->GetMinPlatformVersion() > 9) {
        needToRequestKeyboardOnFocus_ = true;
    }
}

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
#else
        connection_->Close(GetInstanceId());
        connection_ = nullptr;
#endif
    }
}

bool TextFieldPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    contentRect_ = dirty->GetGeometryNode()->GetContentRect();
    frameRect_ = dirty->GetGeometryNode()->GetFrameRect();
    if (!inlineState_.saveInlineState) {
        inlineState_.saveInlineState = true;
        inlineState_.frameRect = frameRect_;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto textFieldLayoutAlgorithm = DynamicCast<TextFieldLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(textFieldLayoutAlgorithm, false);
    auto paragraph = textFieldLayoutAlgorithm->GetParagraph();
    if (paragraph) {
        paragraph_ = paragraph;
    }
    auto counterParagraph = textFieldLayoutAlgorithm->GetCounterParagraph();
    if (counterParagraph) {
        counterParagraph_ = counterParagraph;
        countHeight_ = counterParagraph->GetHeight();
    }
    auto errorParagraph = textFieldLayoutAlgorithm->GetErrorParagraph();
    if (errorParagraph) {
        errorParagraph_ = errorParagraph;
    }
    if (!IsDragging()) {
        dragParagraph_ = paragraph_;
    }
    textRect_ = textFieldLayoutAlgorithm->GetTextRect();
    imageRect_ = textFieldLayoutAlgorithm->GetImageRect();
    unitWidth_ = textFieldLayoutAlgorithm->GetUnitWidth();
    parentGlobalOffset_ = textFieldLayoutAlgorithm->GetParentGlobalOffset();
    UpdateTextFieldManager(Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY()), frameRect_.Height());
    auto textRectNotNeedToChange = UpdateCaretPosition();
    UpdateCaretInfoToController();
    auto hostLayoutProperty =
        dirty->GetHostNode() ? dirty->GetHostNode()->GetLayoutProperty<TextFieldLayoutProperty>() : nullptr;
    if (hostLayoutProperty) {
        hostLayoutProperty->ResetTextAlignChanged();
    }
    if (needToRefreshSelectOverlay_) {
        ProcessOverlay();
        StopTwinkling();
        needToRefreshSelectOverlay_ = false;
    }
    if (setSelectionFlag_) {
        SetTextSelection(selectionStart_, selectionEnd_);
        setSelectionFlag_ = false;
    }
    if (inlineSelectAllFlag_) {
        inlineSelectAllFlag_ = false;
        HandleOnSelectAll(true);
    }
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
    float dx = AdjustTextRectOffsetX();
    float dy = AdjustTextAreaOffsetY();
    UpdateSelectionOffset();
    if (caretUpdateType_ == CaretUpdateType::HANDLE_MOVE) {
        if (!NearZero(dx) || !NearZero(dy)) {
            UpdateOtherHandleOnMove(dx, dy);
        }
        // trigger selection box repaint
        MarkRedrawOverlay();
    } else if (caretUpdateType_ == CaretUpdateType::HANDLE_MOVE_DONE) {
        SetHandlerOnMoveDone();
    } else if ((!NearZero(dx) || !NearZero(dy)) && SelectOverlayIsOn()) {
        SelectHandleInfo firstInfo, secondInfo;
        SizeF handlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), caretRect_.Height() };
        textSelector_.firstHandleOffset_.AddX(dx);
        textSelector_.firstHandleOffset_.AddY(dy);
        firstInfo.paintRect = { textSelector_.firstHandleOffset_, handlePaintSize };
        textSelector_.secondHandleOffset_.AddX(dx);
        textSelector_.secondHandleOffset_.AddY(dy);
        secondInfo.paintRect = { textSelector_.secondHandleOffset_, handlePaintSize };
        selectOverlayProxy_->UpdateFirstAndSecondHandleInfo(firstInfo, secondInfo);
    }
    if (IsTextArea()) {
        CheckScrollable();
    } else {
        SetScrollEnable(GreatNotEqual(textRect_.Width(), contentRect_.Width()));
    }
    UpdateScrollBarOffset();
    caretUpdateType_ = CaretUpdateType::NONE;
    return true;
}

bool TextFieldPattern::HasFocus() const
{
    auto focusHub = GetHost()->GetOrCreateFocusHub();

    if (IsSearchParentNode()) {
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(GetHost()->GetParent());
        focusHub = parentFrameNode->GetOrCreateFocusHub();
    }

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

#else
    if (HasConnection()) {
        TextEditingValue value;
        value.text = textEditingValue_.text;
        value.hint = GetPlaceHolder();
        value.selection.Update(textSelector_.baseOffset, textSelector_.destinationOffset);
        connection_->SetEditingState(value, GetInstanceId());
    }
#endif
}

// return: true if text rect offset will NOT be further changed by caret position
bool TextFieldPattern::UpdateCaretPosition()
{
    auto focusHub = GetHost()->GetOrCreateFocusHub();
    if (IsSearchParentNode()) {
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(GetHost()->GetParent());
        focusHub = parentFrameNode->GetOrCreateFocusHub();
    }
    if (focusHub && !focusHub->IsCurrentFocus()) {
        CloseSelectOverlay();
        LOGW("Not on focus, cannot update caret");
        return true;
    }
    UpdateCaretRectByPosition(textEditingValue_.caretPosition);
    // text input has higher priority than events such as mouse press
    if (caretUpdateType_ == CaretUpdateType::INPUT) {
        UpdateCaretPositionByTextEdit();
        StartTwinkling();
    } else if (caretUpdateType_ == CaretUpdateType::PRESSED || caretUpdateType_ == CaretUpdateType::LONG_PRESSED) {
        UpdateCaretByPressOrLongPress();
        MarkRedrawOverlay();
    } else if (caretUpdateType_ == CaretUpdateType::EVENT || caretUpdateType_ == CaretUpdateType::DEL ||
               caretUpdateType_ == CaretUpdateType::ICON_PRESSED) {
        UpdateCaretOffsetByEvent();
        if (!NeedShowPasswordIcon() && !needToRefreshSelectOverlay_ && GetCursorVisible()) {
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
    isSingleHandle_ = true;
    auto renderContext = GetHost()->GetRenderContext();
    if (renderContext) {
        AnimatePressAndHover(renderContext, 0.0f);
    }
    RectF secondHandle;
    auto secondHandleMetrics = CalcCursorOffsetByPosition(textEditingValue_.caretPosition);
    OffsetF secondHandleOffset(secondHandleMetrics.offset.GetX() + parentGlobalOffset_.GetX(),
        secondHandleMetrics.offset.GetY() + parentGlobalOffset_.GetY());
    if (textEditingValue_.Empty()) {
        auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
        auto align = layoutProperty ? layoutProperty->GetTextAlignValue(TextAlign::START) : TextAlign::START;
        float offsetX = contentRect_.GetX();
        auto baseWidth = frameRect_.Width();
        auto showingPasswordIcon = (layoutProperty ? layoutProperty->GetShowPasswordIcon().value_or(true) : false) &&
                                   (layoutProperty ? layoutProperty->GetTextInputTypeValue(
                                                         TextInputType::UNSPECIFIED) == TextInputType::VISIBLE_PASSWORD
                                                   : false);
        baseWidth -= showingPasswordIcon ? GetIconSize() + GetIconRightOffset() : 0.0f;
        switch (align) {
            case TextAlign::CENTER:
                offsetX = baseWidth * 0.5f;
                break;
            case TextAlign::END:
                offsetX = baseWidth - GetPaddingRight();
                break;
            case TextAlign::START:
            default:
                break;
        }
        secondHandleOffset =
            OffsetF(offsetX + parentGlobalOffset_.GetX(), contentRect_.GetY() + parentGlobalOffset_.GetY());
    }
    textSelector_.secondHandleOffset_ = secondHandleOffset;
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
        return true;
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
    UpdateSelection(textSelector_.GetStart(), textEditingValue_.caretPosition);
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
    UpdateSelection(textSelector_.GetStart(), textEditingValue_.caretPosition);
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
                    textBoxes_.begin()->rect_.GetTop() + (IsTextArea() ? textRect_.GetY() : contentRect_.GetY()) +
                        BOX_EPSILON);
            auto textBoxLocalOffsetEnd =
                OffsetF(textBoxes_.rbegin()->rect_.GetRight() + (IsTextArea() ? contentRect_.GetX() : textRect_.GetX()),
                    textBoxes_.rbegin()->rect_.GetTop() + (IsTextArea() ? textRect_.GetY() : contentRect_.GetY()) +
                        BOX_EPSILON);
            if (contentRect_.IsInRegion({ textBoxLocalOffsetBegin.GetX(), textBoxLocalOffsetBegin.GetY() })) {
                OffsetF firstHandleOffset(textBoxLocalOffsetBegin.GetX() + parentGlobalOffset_.GetX(),
                    textBoxLocalOffsetBegin.GetY() + parentGlobalOffset_.GetY() - BOX_EPSILON);
                textSelector_.firstHandleOffset_ = firstHandleOffset;
                RectF firstHandle;
                firstHandle.SetOffset(firstHandleOffset);
                firstHandle.SetSize(handlePaintSize);
                firstHandleOption = firstHandle;
            }
            if (contentRect_.IsInRegion({ textBoxLocalOffsetEnd.GetX(), textBoxLocalOffsetEnd.GetY() })) {
                OffsetF secondHandleOffset(textBoxLocalOffsetEnd.GetX() + parentGlobalOffset_.GetX(),
                    textBoxLocalOffsetEnd.GetY() + parentGlobalOffset_.GetY() - BOX_EPSILON);
                textSelector_.secondHandleOffset_ = secondHandleOffset;
                RectF secondHandle;
                secondHandle.SetOffset(secondHandleOffset);
                secondHandle.SetSize(handlePaintSize);
                secondHandleOption = secondHandle;
            }
            if (firstHandleOption.has_value() || secondHandleOption.has_value()) {
                ShowSelectOverlay(firstHandleOption, secondHandleOption);
            }
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
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCaretPosition(textEditingValue_.caretPosition);
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
            caretRect_.SetLeft(static_cast<float>(contentRect_.GetX()) + contentRect_.Width() -
                               static_cast<float>(CURSOR_WIDTH.ConvertToPx()));
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
        UpdateSelection(textEditingValue_.caretPosition);
        return;
    }
    UpdateCaretOffsetByLastTouchOffset();
    if (caretUpdateType_ == CaretUpdateType::LONG_PRESSED && !textEditingValue_.CaretAtLast()) {
        int32_t oneWord = GetGraphemeClusterLength(GetEditingValue().GetWideText(), 1);
        textSelector_.Update(textEditingValue_.caretPosition, textEditingValue_.caretPosition + oneWord);
    } else {
        UpdateSelection(textEditingValue_.caretPosition);
    }
    GetTextRectsInRange(textSelector_.GetStart(), textSelector_.GetEnd(), textBoxes_);
    if (caretUpdateType_ == CaretUpdateType::LONG_PRESSED && !textEditingValue_.CaretAtLast()) {
        FireOnSelectionChange(textSelector_.GetStart(), textSelector_.GetEnd());
    }

    selectionMode_ = SelectionMode::NONE;
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCaretPosition(textEditingValue_.caretPosition);
}

CaretMetricsF TextFieldPattern::CalcCursorOffsetByPosition(int32_t position, bool isStart)
{
    // this function will calculate caret offset and height by caret position
    CaretMetricsF result;
    CaretMetricsF resultDownstream;
    CaretMetricsF resultUpstream;
    auto isSuccessDownstream = ComputeOffsetForCaretDownstream(position, resultDownstream);
    auto isSuccessUpstream = ComputeOffsetForCaretUpstream(position, resultUpstream);
    LOGD("position : %{public}d resultDownstream: %{public}s resultUpstream: %{public}s", position,
        resultDownstream.offset.ToString().c_str(), resultUpstream.offset.ToString().c_str());
    if (!(isSuccessDownstream || isSuccessUpstream)) {
        LOGW("Get caret offset failed, set it to text start");
        auto offsetX = contentRect_.GetX();
        auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
        switch (layoutProperty->GetTextAlignValue(TextAlign::START)) {
            case TextAlign::CENTER:
                offsetX = static_cast<float>(contentRect_.GetX()) + contentRect_.Width() / 2.0f;
                break;
            case TextAlign::END:
                offsetX = static_cast<float>(contentRect_.GetX()) + contentRect_.Width() -
                          static_cast<float>(CURSOR_WIDTH.ConvertToPx());
                break;
            default:
                break;
        }
        result.offset = OffsetF(offsetX, contentRect_.GetY());
        result.height = textBoxes_.empty() ? PreferredLineHeight() : textBoxes_.begin()->rect_.GetHeight();
        return result;
    }
    if (isSuccessDownstream && isStart && resultUpstream.offset.GetY() < resultDownstream.offset.GetY()) {
        result = resultDownstream;
    } else if (isSuccessUpstream && !isStart && resultUpstream.offset.GetY() < resultDownstream.offset.GetY()) {
        result = resultUpstream;
    } else {
        if (isSuccessDownstream) {
            result = resultDownstream;
        } else {
            result = resultUpstream;
        }
    }
    LOGD("result stream: %{public}s ", result.ToString().c_str());
    result.offset.AddX(IsTextArea() ? contentRect_.GetX() : textRect_.GetX());
    result.offset.AddY(IsTextArea() ? textRect_.GetY() : contentRect_.GetY());
    return result;
}

float TextFieldPattern::AdjustTextRectOffsetX()
{
    auto cursorWidth = static_cast<float>(CURSOR_WIDTH.ConvertToPx());
    auto contentLeftBoundary = contentRect_.GetX();
    auto contentRightBoundary = contentRect_.GetX() + contentRect_.GetSize().Width() - unitWidth_;
    if (IsTextArea()) {
        caretRect_.SetLeft(std::clamp(caretRect_.GetX(), contentLeftBoundary, contentRightBoundary - cursorWidth));
        return 0.0f;
    }
    // text rect length exceeds content length, but cursor is still in the region
    if (CursorInContentRegion()) {
        return 0.0f;
    }
    auto offsetToParagraphBeginning = caretRect_.GetX() - textRect_.GetX();
    float dx = 0.0f;
    if (caretRect_.GetX() < contentLeftBoundary) {
        dx = contentLeftBoundary - caretRect_.GetX();
        caretRect_.SetLeft(caretRect_.GetX() + dx);
        textRect_.SetLeft(caretRect_.GetX() - offsetToParagraphBeginning);
    } else if (caretRect_.GetX() + cursorWidth > contentRightBoundary) {
        dx = (contentRightBoundary - static_cast<float>(cursorWidth)) - caretRect_.GetX();
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

    if (caretRect_.GetY() < contentRect_.GetY()) {
        auto dy = contentRect_.GetY() - caretRect_.GetY();
        caretRect_.SetTop(caretRect_.GetY() + dy);
        textRect_.SetOffset(OffsetF(textRect_.GetX(), textRect_.GetY() + dy));
        return dy;
    }
    auto dy = contentRect_.GetY() + contentRect_.Height() - (caretRect_.Height() + caretRect_.GetY());
    // caret does not exceed bottom boundary, still need to check against safeArea
    if (GreatOrEqual(dy, 0.0f)) {
        return FitCursorInSafeArea();
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
           LessOrEqual(
               caretRect_.GetX() + CURSOR_WIDTH.ConvertToPx(), contentRect_.GetX() + contentRect_.Width() - unitWidth_);
}

float TextFieldPattern::FitCursorInSafeArea()
{
    // check if caret is below safeArea
    auto pipeline = PipelineContext::GetCurrentContext();
    auto safeAreaBottom = pipeline->GetSafeArea().bottom_;
    safeAreaBottom = safeAreaBottom.Combine(pipeline->GetSafeAreaManager()->GetKeyboardInset());
    CHECK_NULL_RETURN_NOLOG(safeAreaBottom.IsValid(), 0.0f);
    // get global height of caret
    auto host = GetHost();
    auto globalBottom = host->GetPaintRectOffset().GetY() + caretRect_.Bottom();
    if (globalBottom > safeAreaBottom.start) {
        auto dy = safeAreaBottom.start - globalBottom;
        caretRect_.SetTop(caretRect_.GetY() + dy);
        textRect_.SetOffset(OffsetF(textRect_.GetX(), textRect_.GetY() + dy));
        return dy;
    }
    return 0.0f;
}

bool TextFieldPattern::OffsetInContentRegion(const Offset& offset)
{
    // real content region will minus basic padding on left and right
    return GreatOrEqual(offset.GetX(), contentRect_.GetX()) &&
           LessOrEqual(offset.GetX(), contentRect_.GetX() + contentRect_.Width());
}

void TextFieldPattern::OnScrollEndCallback()
{
    auto selectOverlayProxy = GetSelectOverlay();
    CHECK_NULL_VOID_NOLOG(selectOverlayProxy);
    selectOverlayProxy->ShowOrHiddenMenu(false);
}

void TextFieldPattern::OnTextAreaScroll(float offset)
{
    LOGI("OnTextAreaScroll with offset %{public}f", offset);
    if (!IsTextArea() || textRect_.Height() <= contentRect_.Height()) {
        return;
    }
    if (textRect_.GetY() + offset > contentRect_.GetY()) {
        offset = contentRect_.GetY() - textRect_.GetY();
    } else if (textRect_.GetY() + textRect_.Height() + offset < contentRect_.GetY() + contentRect_.Height()) {
        offset = contentRect_.GetY() + contentRect_.Height() - textRect_.GetY() - textRect_.Height();
    }
    caretRect_.SetTop(caretRect_.GetY() + offset);
    currentOffset_ = textRect_.GetY() + offset;
    textRect_.SetOffset(OffsetF(textRect_.GetX(), currentOffset_));
    UpdateSelectionOffset();
    if (SelectOverlayIsOn()) {
        SizeF handlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), caretRect_.Height() };
        textSelector_.firstHandleOffset_.SetY(textSelector_.firstHandleOffset_.GetY() + offset);
        std::optional<RectF> firstHandle = RectF(textSelector_.firstHandleOffset_, handlePaintSize);

        std::optional<RectF> secondHandle;
        if (!isSingleHandle_) {
            textSelector_.secondHandleOffset_.SetY(textSelector_.secondHandleOffset_.GetY() + offset);
            secondHandle = { textSelector_.secondHandleOffset_, handlePaintSize };
        }
        auto firstHandleHeight = 0.0f;
        auto secondHandleHeight = 0.0f;
        auto firstHandleOffset = textSelector_.firstHandleOffset_ - parentGlobalOffset_;
        auto secondHandleOffset = textSelector_.secondHandleOffset_ - parentGlobalOffset_;
        if (GreatOrEqual(offset, 0.0f) && GreatNotEqual(firstHandleOffset.GetY(), contentRect_.GetY())) {
            firstHandleHeight = firstHandle->Height();
        }
        if (LessNotEqual(offset, 0.0f) && GreatNotEqual(firstHandleOffset.GetY() + firstHandle->Height(),
                                              contentRect_.GetY() + contentRect_.Height())) {
            firstHandleHeight = firstHandle->Height();
        }
        if (!isSingleHandle_) {
            if (GreatOrEqual(offset, 0.0f) && GreatNotEqual(secondHandleOffset.GetY(), contentRect_.GetY())) {
                secondHandleHeight = secondHandle->Height();
            }
            if (LessNotEqual(offset, 0.0f) && GreatNotEqual(secondHandleOffset.GetY() + secondHandle->Height(),
                                                  contentRect_.GetY() + contentRect_.Height())) {
                secondHandleHeight = secondHandle->Height();
            }
        }
        CheckHandles(firstHandle, secondHandle, firstHandleHeight, secondHandleHeight);
        ShowSelectOverlay(firstHandle, secondHandle);
    }
    UpdateScrollBarOffset();
}

void TextFieldPattern::OnTextInputScroll(float offset)
{
    if (IsTextArea() || textRect_.Width() <= contentRect_.Width() ||
        (textRect_.GetX() + offset) > contentRect_.GetX()) {
        return;
    }
    if ((std::abs(((textRect_.GetX() + offset) - contentRect_.Width() - GetPaddingRight())) > textRect_.Width()) &&
        LessNotEqual(offset, 0.0f)) {
        return;
    }
    caretRect_.SetLeft(caretRect_.GetX() + offset);
    currentOffset_ = textRect_.GetX() + offset;
    textRect_.SetOffset(OffsetF(currentOffset_, textRect_.GetY()));
    UpdateSelectionOffset();
    if (SelectOverlayIsOn()) {
        SizeF handlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), caretRect_.Height() };
        textSelector_.firstHandleOffset_.SetX(textSelector_.firstHandleOffset_.GetX() + offset);
        std::optional<RectF> firstHandle = RectF(textSelector_.firstHandleOffset_, handlePaintSize);

        std::optional<RectF> secondHandle;
        if (!isSingleHandle_) {
            textSelector_.secondHandleOffset_.SetX(textSelector_.secondHandleOffset_.GetX() + offset);
            secondHandle = { textSelector_.secondHandleOffset_, handlePaintSize };
        }
        CheckHandles(firstHandle, secondHandle);
        ShowSelectOverlay(firstHandle, secondHandle);
    }
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::GetTextRectsInRange(
    int32_t base, int32_t destination, std::vector<RSTypographyProperties::TextBox>& textBoxes)
{
    SwapIfLarger(base, destination);
    if (!paragraph_) {
        return;
    }

    textBoxes = paragraph_->GetRectsForRange(
        base, destination, RSTypographyProperties::RectHeightStyle::MAX, RSTypographyProperties::RectWidthStyle::TIGHT);
    if (textBoxes.size() == 1 && caretUpdateType_ == CaretUpdateType::LONG_PRESSED) {
        Offset offset = GetLastTouchOffset() - Offset(textRect_.GetX(), textRect_.GetY());
        if (offset.GetX() < textBoxes[0].rect_.GetLeft() || offset.GetY() < textBoxes[0].rect_.GetTop()) {
            auto tmp = paragraph_->GetRectsForRange(base - 1, destination - 1,
                RSTypographyProperties::RectHeightStyle::MAX, RSTypographyProperties::RectWidthStyle::TIGHT);
            if (tmp.size() != 1) {
                return;
            }
            bool isInRange = offset.GetX() >= tmp[0].rect_.GetLeft() && offset.GetX() <= tmp[0].rect_.GetRight() &&
                             offset.GetY() >= tmp[0].rect_.GetTop() && offset.GetY() <= tmp[0].rect_.GetBottom();
            if (isInRange) {
                textBoxes = tmp;
                UpdateSelectorByPosition(base - 1);
            }
        }
    }
}

bool TextFieldPattern::ComputeOffsetForCaretDownstream(int32_t extent, CaretMetricsF& result)
{
    CHECK_NULL_RETURN_NOLOG(paragraph_, false);
    auto wideText = textEditingValue_.GetWideText();
    if (!IsTextArea() && static_cast<size_t>(extent) >= wideText.length()) {
        return false;
    }

    result.Reset();
    const int32_t graphemeClusterLength = 1;
    const int32_t next = extent + graphemeClusterLength;
    auto textBoxes = paragraph_->GetRectsForRange(
        extent, next, RSTypographyProperties::RectHeightStyle::MAX, RSTypographyProperties::RectWidthStyle::TIGHT);

    if (textBoxes.empty()) {
        LOGD("Box empty");
        return false;
    }

    const auto& textBox = *textBoxes.begin();
    auto lastStringBeforeCursor = wideText.substr(
        std::clamp(textEditingValue_.caretPosition - 1, 0, static_cast<int32_t>(wideText.length()) - 1), 1);
    // Caret is within width of the downstream glyphs.
    if (lastStringBeforeCursor == WIDE_NEWLINE &&
        (caretUpdateType_ == CaretUpdateType::INPUT || caretUpdateType_ == CaretUpdateType::DEL)) {
        result.offset.SetX(MakeEmptyOffset().GetX());
        result.offset.SetY(textBox.rect_.GetTop());
        result.height = textBox.rect_.GetHeight();
        return true;
    }

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
        LOGD("Empty box");
        return false;
    }

    const auto& textBox = *boxes.begin();
    auto caretPosition = textEditingValue_.caretPosition;
    auto maxPos = static_cast<int32_t>(wideText.length()) - 1;
    auto lastStringBeforeCursor = wideText.substr(std::clamp(caretPosition - 1, 0, maxPos), 1);
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
    return static_cast<int32_t>(paragraph_->GetGlyphPositionAtCoordinate(localOffset.GetX(), localOffset.GetY()).pos_);
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

#if defined(IOS_PLATFORM)
Offset TextFieldPattern::GetGlobalOffset() const
{
    Offset offset;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, {});
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, {});
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto globalOffset = host->GetPaintRectOffset() - rootOffset;
    offset = Offset(globalOffset.GetX(), globalOffset.GetY());
    return offset;
}

double TextFieldPattern::GetEditingBoxY() const
{
    return GetGlobalOffset().GetY() + frameRect_.Height();
};

double TextFieldPattern::GetEditingBoxTopY() const
{
    return GetGlobalOffset().GetY();
};

bool TextFieldPattern::GetEditingBoxModel() const
{
    bool isDeclarative = false;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    if (pipeline && pipeline->GetIsDeclarative()) {
        isDeclarative = true;
    }
    return isDeclarative;
};
#endif

void TextFieldPattern::HandleFocusEvent()
{
    LOGI("TextField %{public}d on focus", GetHost()->GetId());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto globalOffset = GetHost()->GetPaintRectOffset() - context->GetRootRect().GetOffset();
    UpdateTextFieldManager(Offset(globalOffset.GetX(), globalOffset.GetY()), frameRect_.Height());
    if (caretUpdateType_ != CaretUpdateType::PRESSED) {
        if (caretUpdateType_ == CaretUpdateType::LONG_PRESSED) {
            // Long press after out of focus, flash the cursor and request keyboard.
            caretUpdateType_ = CaretUpdateType::PRESSED;
            if (RequestKeyboard(false, true, true)) {
                auto eventHub = host->GetEventHub<TextFieldEventHub>();
                CHECK_NULL_VOID(eventHub);
                eventHub->FireOnEditChanged(true);
            }
        } else {
            caretUpdateType_ = CaretUpdateType::EVENT;
            needToRequestKeyboardInner_ = !(dragRecipientStatus_ == DragStatus::DRAGGING);
        }
    }
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (paintProperty->GetInputStyleValue(InputStyle::DEFAULT) == InputStyle::INLINE &&
        !textEditingValue_.GetWideText().empty()) {
        ApplyInlineStates(true);
        inlineSelectAllFlag_ = true;
        inlineFocusState_ = true;
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    } else {
        StartTwinkling();
    }
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnEditChanged(true);
    CloseSelectOverlay();
    auto visible = layoutProperty->GetShowErrorTextValue(false);
    if (!visible && layoutProperty->GetShowUnderlineValue(false)) {
        auto renderContext = GetHost()->GetRenderContext();
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(textFieldTheme);
        auto radius = textFieldTheme->GetBorderRadiusSize();
        underlineColor_ = textFieldTheme->GetUnderlineTypingColor();
        underlineWidth_ = TYPING_UNDERLINE_WIDTH;
        renderContext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
    }
    GetHost()->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                      : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::HandleSetSelection(int32_t start, int32_t end, bool showHandle)
{
    LOGI("HandleSetSelection %{public}d, %{public}d", start, end);
    CloseSelectOverlay();
    UpdateSelection(start, end);
    textEditingValue_.caretPosition =
        std::clamp(end, 0, static_cast<int32_t>(textEditingValue_.GetWideText().length()));
    selectionMode_ = start == end ? SelectionMode::NONE : SelectionMode::SELECT;
    GetTextRectsInRange(textSelector_.GetStart(), textSelector_.GetEnd(), textBoxes_);
    AdjustTextSelectionRectOffsetX();
    UpdateCaretRectByPosition(textEditingValue_.caretPosition);
    if (showHandle) {
        if (start == end) {
            CreateSingleHandle();
        } else {
            CreateHandles();
        }
    }
    UpdateCaretInfoToController();
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::AdjustTextSelectionRectOffsetX()
{
    if (textBoxes_.empty()) {
        return;
    }
    auto contentLeftBoundary = contentRect_.GetX();
    auto contentRightBoundary = contentRect_.GetX() + contentRect_.GetSize().Width() - unitWidth_;
    auto selectionStart = textBoxes_.begin()->rect_.GetLeft() + textRect_.GetX();
    auto selectionEnd = textBoxes_.begin()->rect_.GetRight() + textRect_.GetX();

    float dx = 0.0f;
    if (selectionEnd < contentLeftBoundary) {
        if (selectionStart < selectionEnd) {
            dx = contentLeftBoundary - selectionStart;
        } else {
            dx = contentLeftBoundary - selectionEnd;
        }
    } else if (selectionEnd > contentRightBoundary) {
        if (selectionStart < selectionEnd) {
            dx = selectionEnd - contentRightBoundary;
        } else {
            dx = selectionStart - contentRightBoundary;
        }
    }
    textRect_.SetLeft(textRect_.GetX() + dx);
}

void TextFieldPattern::HandleExtendAction(int32_t action)
{
    LOGI("HandleExtendAction %{public}d", action);
    switch (action) {
        case ACTION_SELECT_ALL: {
            HandleOnSelectAll();
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
    LOGI("HandleSelect, current caret position %{public}d", textEditingValue_.caretPosition);
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
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto visible = layoutProperty->GetShowErrorTextValue(false);
    if (!visible && layoutProperty->GetShowUnderlineValue(false)) {
        auto renderContext = GetHost()->GetRenderContext();
        renderContext->UpdateBorderRadius(borderRadius_);
        underlineColor_ = textFieldTheme->GetUnderlineColor();
        underlineWidth_ = UNDERLINE_WIDTH;
    }
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->GetInputStyleValue(InputStyle::DEFAULT) == InputStyle::INLINE &&
        !textEditingValue_.GetWideText().empty()) {
        if (IsTextArea() && isTextInput_) {
            layoutProperty->UpdateMaxLines(1);
        }
        inlineSelectAllFlag_ = false;
        inlineFocusState_ = false;
        RestorePreInlineStates();
    }
    needToRequestKeyboardInner_ = false;
    caretRect_.Reset();
    StopTwinkling();
    CloseKeyboard(true);
    MarkRedrawOverlay();
    textSelector_.Update(-1);
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
    if (redoOperationRecords_.size() >= RECORD_MAX_LENGTH && !(redoOperationRecords_.empty())) {
        redoOperationRecords_.erase(redoOperationRecords_.begin());
    }
    redoOperationRecords_.push_back(value);
    if (operationRecords_.empty()) {
        LOGW("No record left, clear");
        FireEventHubOnChange("");
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

void TextFieldPattern::HandleOnSelectAll(bool inlineStyle)
{
    LOGI("TextFieldPattern::HandleOnSelectAll");
    auto textSize = static_cast<int32_t>(GetEditingValue().GetWideText().length());
    if (inlineStyle == true) {
        if (GetEditingValue().GetWideText().rfind(L".") < textSize - FIND_TEXT_ZERO_INDEX) {
            textSize = GetEditingValue().GetWideText().rfind(L".");
        }
        UpdateSelection(0, textSize);
    } else {
        UpdateSelection(0, textSize);
    }
    textEditingValue_.caretPosition = textSize;
    selectionMode_ = SelectionMode::SELECT_ALL;
    caretUpdateType_ = CaretUpdateType::EVENT;
    MarkRedrawOverlay();
    GetTextRectsInRange(textSelector_.GetStart(), textSelector_.GetEnd(), textBoxes_);
    isSingleHandle_ = textEditingValue_.text.empty();
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
    if (layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::VISIBLE_PASSWORD) {
        LOGW("Cannot copy in password mode");
        selectionMode_ = SelectionMode::NONE;
        UpdateCaretPositionWithClamp(textSelector_.GetEnd());
        UpdateSelection(textEditingValue_.caretPosition);
        StartTwinkling();
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
        clipboard_->SetData(value, layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed));
    }

    UpdateCaretPositionWithClamp(textSelector_.GetEnd());
    UpdateSelection(textEditingValue_.caretPosition);
    UpdateCaretRectByPosition(textEditingValue_.caretPosition);
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
            SwapIfLarger(start, end);
        } else {
            start = value.caretPosition;
            end = value.caretPosition;
        }
        std::string result;
        std::string valueToUpdate(data);
        textfield->EditingValueFilter(valueToUpdate, result);
        LOGD("After filter paste value is %{private}s", result.c_str());
        CHECK_NULL_VOID_NOLOG(!result.empty());
        std::wstring pasteData;
        std::wstring wData = StringUtils::ToWstring(result);
        textfield->StripNextLine(wData);
        if (wData.length() + valueLength - (end - start) > textfield->GetMaxLength()) {
            pasteData = wData.substr(0, textfield->GetMaxLength() - valueLength + (end - start));
        } else {
            pasteData = wData;
        }
        value.text =
            value.GetValueBeforePosition(start) + StringUtils::ToString(pasteData) + value.GetValueAfterPosition(end);
        auto newCaretPosition = std::clamp(std::min(start, end) + static_cast<int32_t>(pasteData.length()), 0,
            static_cast<int32_t>(StringUtils::ToWstring(value.text).length()));
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
        textfield->StartTwinkling();
    };
    CHECK_NULL_VOID(clipboard_);
    clipboard_->GetData(pasteCallback);
}

void TextFieldPattern::StripNextLine(std::wstring& data)
{
    CHECK_NULL_VOID(!(data.empty() || IsTextArea()));
    std::wstring result;
    bool dataChanged = false;
    int32_t dataPtr = 0;
    while (dataPtr < static_cast<int32_t>(data.length())) {
        if (data[dataPtr] != WIDE_NEWLINE[0]) {
            result += data[dataPtr];
        } else {
            dataChanged = true;
        }
        dataPtr++;
    }
    CHECK_NULL_VOID(dataChanged);
    data = result;
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
    auto start = textSelector_.GetStart();
    auto end = textSelector_.GetEnd();
    SwapIfLarger(start, end);
    if (!InSelectMode() || (textSelector_.IsValid() && start == end)) {
        LOGW("HandleOnCut nothing Selected");
        return;
    }
    auto value = GetEditingValue();
    auto selectedText = value.GetSelectedText(start, end);
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) != CopyOptions::None) {
        LOGI("Cut value is %{private}s", selectedText.c_str());
        clipboard_->SetData(selectedText, layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed));
    }
    textEditingValue_.text =
        textEditingValue_.GetValueBeforePosition(start) + textEditingValue_.GetValueAfterPosition(end);
    textEditingValue_.CursorMoveToPosition(start);
    SetEditingValueToProperty(textEditingValue_.text);
    selectionMode_ = SelectionMode::NONE;
    caretUpdateType_ = CaretUpdateType::EVENT;
    CloseSelectOverlay();
    UpdateEditingValueToRecord();
    UpdateSelection(textEditingValue_.caretPosition);
    MarkRedrawOverlay();
    cursorVisible_ = true;

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
    if (start != textSelector_.GetStart() || end != textSelector_.GetEnd()) {
        FireOnSelectionChange(start, end);
        textSelector_.Update(start, end);
    }
}

void TextFieldPattern::FireOnSelectionChange(int32_t start, int32_t end)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    eventHub->FireOnSelectionChange(start, end);
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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto visible = layoutProperty->GetShowErrorTextValue(false);
    if (!visible && layoutProperty->GetShowUnderlineValue(false)) {
        underlineColor_ = textFieldTheme->GetUnderlineTypingColor();
        underlineWidth_ = TYPING_UNDERLINE_WIDTH;
    }
    if (IsTextArea() && layoutProperty->HasMaxLength()) {
        HandleCounterBorder();
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
    if (HasStateStyle(UI_STATE_PRESSED)) {
        return;
    }
    if (enableTouchAndHoverEffect_ && !isMousePressed_) {
        auto textfieldPaintProperty = GetPaintProperty<TextFieldPaintProperty>();
        CHECK_NULL_VOID(textfieldPaintProperty);
        auto renderContext = GetHost()->GetRenderContext();
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(textFieldTheme);
        auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        if (layoutProperty->GetShowUnderlineValue(false)) {
            auto radius = textFieldTheme->GetBorderRadiusSize();
            renderContext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
        }
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
    if (enableTouchAndHoverEffect_ && !HasStateStyle(UI_STATE_PRESSED)) {
        auto renderContext = GetHost()->GetRenderContext();
        if (isOnHover_) {
            AnimatePressAndHover(renderContext, HOVER_ANIMATION_OPACITY);
        } else {
            auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            if (layoutProperty->GetShowUnderlineValue(false)) {
                renderContext->UpdateBorderRadius(borderRadius_);
            }
            if (layoutProperty->GetShowUnderlineValue(false) && HasFocus()) {
                auto pipeline = PipelineBase::GetCurrentContext();
                CHECK_NULL_VOID(pipeline);
                auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
                CHECK_NULL_VOID(textFieldTheme);
                auto radius = textFieldTheme->GetBorderRadiusSize();
                renderContext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
            }
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

#ifdef ENABLE_DRAG_FRAMEWORK
std::function<void(Offset)> TextFieldPattern::GetThumbnailCallback()
{
    auto callback = [weak = WeakClaim(this)](const Offset& point) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        if (pattern->BetweenSelectedPosition(point)) {
            pattern->dragNode_ = TextDragPattern::CreateDragNode(frameNode);
            FrameNode::ProcessOffscreenNode(pattern->dragNode_);
        }
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->SetPixelMap(nullptr);
    };
    return callback;
}

void TextFieldPattern::InitDragDropEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->InitDragDropEvent();
    gestureHub->SetTextDraggable(true);
    auto callback = GetThumbnailCallback();
    gestureHub->SetThumbnailCallback(std::move(callback));
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onDragStart = [weakPtr = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& event,
                           const std::string& extraParams) -> NG::DragDropInfo {
        NG::DragDropInfo itemInfo;
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_RETURN(pattern, itemInfo);
        auto host = pattern->GetHost();
        CHECK_NULL_RETURN(host, itemInfo);
        auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_RETURN(layoutProperty, itemInfo);
        pattern->dragStatus_ = DragStatus::DRAGGING;
        pattern->textFieldContentModifier_->ChangeDragStatus();
        pattern->selectionMode_ = SelectionMode::NONE;
        pattern->dragTextStart_ = std::min(pattern->textSelector_.GetStart(), pattern->textSelector_.GetEnd());
        pattern->dragTextEnd_ = std::max(pattern->textSelector_.GetStart(), pattern->textSelector_.GetEnd());
        auto textEditingValue = pattern->GetEditingValue();
        std::string beforeStr = textEditingValue.GetValueBeforePosition(pattern->dragTextStart_);
        std::string selectedStr = textEditingValue.GetSelectedText(pattern->dragTextStart_, pattern->dragTextEnd_);
        std::string afterStr = textEditingValue.GetValueAfterPosition(pattern->dragTextEnd_);
        pattern->dragContents_ = { beforeStr, selectedStr, afterStr };
        itemInfo.extraInfo = selectedStr;
        RefPtr<UnifiedData> unifiedData = UdmfClient::GetInstance()->CreateUnifiedData();
        UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
        event->SetData(unifiedData);
        host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                     : PROPERTY_UPDATE_MEASURE);
        return itemInfo;
    };
    if (!eventHub->HasOnDragStart()) {
        eventHub->SetOnDragStart(std::move(onDragStart));
    }

    auto onDragEnter = [weakPtr = WeakClaim(this)](
                           const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->dragStatus_ == DragStatus::ON_DROP) {
            pattern->dragStatus_ = DragStatus::NONE;
        }

        pattern->dragRecipientStatus_ = DragStatus::DRAGGING;
    };
    eventHub->SetOnDragEnter(std::move(onDragEnter));

    auto onDragMove = [weakPtr = WeakClaim(this)](
                          const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto touchX = Dimension(event->GetX(), DimensionUnit::VP).ConvertToPx();
        auto touchY = Dimension(event->GetY(), DimensionUnit::VP).ConvertToPx();
        Offset offset = Offset(touchX, touchY) - Offset(pattern->textRect_.GetX(), pattern->textRect_.GetY()) -
                        Offset(pattern->parentGlobalOffset_.GetX(), pattern->parentGlobalOffset_.GetY());
        auto position = pattern->ConvertTouchOffsetToCaretPosition(offset);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto focusHub = host->GetOrCreateFocusHub();
        if (pattern->IsSearchParentNode()) {
            auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
            focusHub = parentFrameNode->GetOrCreateFocusHub();
        }
        focusHub->RequestFocusImmediately();
        pattern->SetCaretPosition(position);
        pattern->StartTwinkling();
    };
    eventHub->SetOnDragMove(std::move(onDragMove));

    auto onDragLeave = [weakPtr = WeakClaim(this)](
                           const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->StopTwinkling();
        pattern->dragRecipientStatus_ = DragStatus::NONE;
    };
    eventHub->SetOnDragLeave(std::move(onDragLeave));

    auto onDragEnd = [weakPtr = WeakClaim(this), id = Container::CurrentId()](
                         const RefPtr<OHOS::Ace::DragEvent>& event) {
        ContainerScope scope(id);
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        LOGD("TextFieldPattern  onDragEnd result: %{public}d dragStatus: %{public}d", event->GetResult(),
            pattern->dragStatus_);
        if (pattern->dragStatus_ == DragStatus::DRAGGING) {
            pattern->dragStatus_ = DragStatus::NONE;
            pattern->MarkContentChange();
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    };
    eventHub->SetOnDragEnd(std::move(onDragEnd));

    auto onDrop = [weakPtr = WeakClaim(this)](
                      const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (extraParams.empty()) {
            pattern->dragStatus_ = DragStatus::ON_DROP;
            pattern->textFieldContentModifier_->ChangeDragStatus();
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                         : PROPERTY_UPDATE_MEASURE);
            return;
        }
        auto data = event->GetData();
        CHECK_NULL_VOID(data);
        std::string str = UdmfClient::GetInstance()->GetSinglePlainTextRecord(data);
        pattern->needToRequestKeyboardInner_ = true;
        pattern->dragRecipientStatus_ = DragStatus::NONE;
        if (pattern->dragStatus_ == DragStatus::NONE) {
            pattern->InsertValue(str);
        } else {
            auto current = pattern->textEditingValue_.caretPosition;
            float dragTextStart = pattern->dragTextStart_;
            float dragTextEnd = pattern->dragTextEnd_;
            if (current < dragTextStart) {
                pattern->textEditingValue_.text = pattern->textEditingValue_.GetValueBeforePosition(dragTextStart) +
                                                  pattern->textEditingValue_.GetValueAfterPosition(dragTextEnd);
                pattern->InsertValue(str);
            } else if (current > dragTextEnd) {
                pattern->textEditingValue_.text = pattern->textEditingValue_.GetValueBeforePosition(dragTextStart) +
                                                  pattern->textEditingValue_.GetValueAfterPosition(dragTextEnd);
                pattern->textEditingValue_.caretPosition = current - (dragTextEnd - dragTextStart);
                pattern->InsertValue(str);
            }
            pattern->dragStatus_ = DragStatus::NONE;
        }
    };
    eventHub->SetOnDrop(std::move(onDrop));
}
#endif

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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto globalOffset = host->GetPaintRectOffset() - context->GetRootRect().GetOffset();
    // emulate clicking bottom of the textField
    UpdateTextFieldManager(Offset(globalOffset.GetX(), globalOffset.GetY()), frameRect_.Height());
    auto focusHub = host->GetOrCreateFocusHub();

    if (IsSearchParentNode()) {
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
        focusHub = parentFrameNode->GetOrCreateFocusHub();
    }

    if (!focusHub->IsFocusable()) {
        LOGI("Textfield %{public}d is not focusable ,cannot request keyboard", host->GetId());
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
        LOGI("Password Icon pressed, change text to be shown only");
        textObscured_ = !textObscured_;
        ProcessPasswordIcon();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        caretUpdateType_ = CaretUpdateType::ICON_PRESSED;
        return;
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
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
        auto eventHub = host->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnEditChanged(true);
    }
}

void TextFieldPattern::ScheduleCursorTwinkling()
{
    if (isTransparent_) {
        return;
    }
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
    if (isTransparent_) {
        return;
    }
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

void TextFieldPattern::CheckIfNeedToResetKeyboard()
{
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    bool needToResetKeyboard = false;
    // check unspecified  for first time entrance
    if (keyboard_ != layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED)) {
        LOGI("Keyboard type changed to %{public}d", layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED));
        keyboard_ = layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED);
        needToResetKeyboard = true;
    }
    if (action_ != TextInputAction::UNSPECIFIED) {
        needToResetKeyboard = action_ != GetTextInputActionValue(TextInputAction::DONE);
    }
    action_ = GetTextInputActionValue(TextInputAction::DONE);
    LOGI("Keyboard action is %{public}d", action_);
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    // if keyboard attached and keyboard is shown, pull up keyboard again
    if (needToResetKeyboard && imeAttached_ && imeShown_) {
        CloseKeyboard(true);
        RequestKeyboard(false, true, true);
    }
#endif
}

void TextFieldPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    instanceId_ = context->GetInstanceId();
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    CheckIfNeedToResetKeyboard();
    if (layoutProperty->GetShowUnderlineValue(false)) {
        underlineWidth_ = UNDERLINE_WIDTH;
        underlineColor_ = textFieldTheme->GetUnderlineColor();
        SaveUnderlineStates();
    }

    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    isTransparent_ = renderContext->GetOpacityValue(1.0f) == 0.0f;
    SavePasswordModeStates();
    InitClickEvent();
    InitLongPressEvent();
    InitFocusEvent();
    InitMouseEvent();
    InitTouchEvent();
    SetAccessibilityAction();
#ifdef ENABLE_DRAG_FRAMEWORK
    if (layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) != TextInputType::VISIBLE_PASSWORD) {
        InitDragDropEvent();
        AddDragFrameNodeToManager(host);
    }
#endif // ENABLE_DRAG_FRAMEWORK
    ProcessPasswordIcon();
    context->AddOnAreaChangeNode(host->GetId());
    if (!clipboard_ && context) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
    }
    obscureTickCountDown_ = OBSCURE_SHOW_TICKS;
    ProcessInnerPadding();
    textRect_.SetLeft(textRect_.GetX() + offsetDifference_.GetX());
    textRect_.SetTop(textRect_.GetY() + offsetDifference_.GetY());
    CalculateDefaultCursor();
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    if (renderContext->HasBackgroundColor()) {
        paintProperty->UpdateBackgroundColor(renderContext->GetBackgroundColorValue());
    }
    auto textWidth = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    if (SelectOverlayIsOn()) {
        needToRefreshSelectOverlay_ = true;
        UpdateSelection(
            std::clamp(textSelector_.GetStart(), 0, textWidth), std::clamp(textSelector_.GetEnd(), 0, textWidth));
        UpdateCaretPositionWithClamp(textSelector_.GetEnd());
        if (!textSelector_.StartEqualToDest()) {
            selectionMode_ = SelectionMode::SELECT;
        }
    }
    if (layoutProperty->GetTypeChangedValue(false)) {
        ClearEditingValue();
        layoutProperty->ResetTypeChanged();
        operationRecords_.clear();
        redoOperationRecords_.clear();
    }
#if defined(ENABLE_STANDARD_INPUT)
    auto maxLength = GetMaxLength();
    if (GreatOrEqual(textWidth, maxLength)) {
        textEditingValue_.text = StringUtils::ToString(textEditingValue_.GetWideText().substr(0, maxLength));
        UpdateCaretPositionWithClamp(textEditingValue_.caretPosition);
        SetEditingValueToProperty(textEditingValue_.text);
    }
#endif
    FireOnChangeIfNeeded();
    if (IsTextArea() || paintProperty->GetInputStyleValue(InputStyle::DEFAULT) == InputStyle::INLINE) {
        SetAxis(Axis::VERTICAL);
        if (!GetScrollableEvent()) {
            AddScrollEvent();
        }
        SetScrollBar(layoutProperty->GetDisplayModeValue(DisplayMode::AUTO));
        auto scrollBar = GetScrollBar();
        if (scrollBar) {
            scrollBar->SetMinHeight(SCROLL_BAR_MIN_HEIGHT);
            scrollBar->SetStartReservedHeight(0.0_px);
            scrollBar->SetEndReservedHeight(0.0_px);
        }
    } else {
        SetAxis(Axis::HORIZONTAL);
        if (!GetScrollableEvent()) {
            AddScrollEvent();
            SetScrollEnable(false);
        }
    }

    SetShowError();
    if (IsTextArea() && layoutProperty->HasMaxLength()) {
        if (setBorderFlag_) {
            auto pipeline = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto themeManager = pipeline->GetThemeManager();
            CHECK_NULL_VOID(themeManager);
            auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
            lastDiffBorderColor_.SetColor(textFieldTheme->GetOverCountBorderColor());
            lastDiffBorderWidth_.SetBorderWidth(OVER_COUNT_BORDER_WIDTH);
            setBorderFlag_ = false;
        }
        HandleCounterBorder();
    }
    if (!IsTextArea()) {
        isTextInput_ = true;
    }
    auto inputStyle = paintProperty->GetInputStyleValue(InputStyle::DEFAULT);
    if ((!IsSelected() && inputStyle == InputStyle::INLINE) ||
        ((inputStyle == InputStyle::DEFAULT) && preInputStyle_ != InputStyle::INLINE)) {
        inlineState_.saveInlineState = false;
        SaveInlineStates();
    }
    if (IsSelected() && inputStyle == InputStyle::INLINE) {
        preInputStyle_ == InputStyle::DEFAULT ? ApplyInlineStates(true) : ApplyInlineStates(false);
    }
    if (preInputStyle_ == InputStyle::INLINE && inputStyle == InputStyle::DEFAULT) {
        RestorePreInlineStates();
    }
    preInputStyle_ = inputStyle;
    host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                 : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::CalculateDefaultCursor()
{
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    float caretWidth = paintProperty->GetCursorWidth().has_value()
                           ? static_cast<float>(paintProperty->GetCursorWidthValue().ConvertToPx())
                           : static_cast<float>(CURSOR_WIDTH.ConvertToPx());
    caretRect_.SetWidth(caretWidth);
    if (textEditingValue_.caretPosition != 0) {
        return;
    }
    caretRect_.SetLeft(GetPaddingLeft());
    caretRect_.SetTop(GetPaddingTop());
    caretRect_.SetHeight(PreferredLineHeight());
    CHECK_NULL_VOID(layoutProperty->GetCalcLayoutConstraint());
    CHECK_NULL_VOID(layoutProperty->GetCalcLayoutConstraint()->selfIdealSize.has_value());
    CHECK_NULL_VOID(layoutProperty->GetCalcLayoutConstraint()->selfIdealSize.value().Height().has_value());
    auto alignment = layoutProperty->GetPositionProperty()
                         ? layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER)
                         : Alignment::CENTER;
    auto idealHeight = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize.value().Height().value();
    caretRect_.SetTop(
        (1.0 + alignment.GetVertical()) * (idealHeight.GetDimension().ConvertToPx() - PreferredLineHeight()) / 2.0);
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
    auto left = layoutProperty->GetPaddingProperty()
                    ->left.value_or(CalcLength(themePadding.Left()))
                    .GetDimension()
                    .ConvertToPx();
    offsetDifference_.SetX(left - GetPaddingLeft());
    utilPadding_.left = left;
    auto top =
        layoutProperty->GetPaddingProperty()->top.value_or(CalcLength(themePadding.Top())).GetDimension().ConvertToPx();
    offsetDifference_.SetY(top - GetPaddingTop());
    utilPadding_.top = top;

    utilPadding_.bottom = layoutProperty->GetPaddingProperty()
                              ->bottom.value_or(CalcLength(themePadding.Bottom()))
                              .GetDimension()
                              .ConvertToPx();
    utilPadding_.right = layoutProperty->GetPaddingProperty()
                             ->right.value_or(CalcLength(themePadding.Right()))
                             .GetDimension()
                             .ConvertToPx();
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

    auto onTextSelectorChange = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        frameNode->OnAccessibilityEvent(AccessibilityEventType::TEXT_SELECTION_UPDATE);
    };
    textSelector_.SetOnAccessibility(std::move(onTextSelectorChange));
}

void TextFieldPattern::HandleLongPress(GestureEvent& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    lastTouchOffset_ = info.GetLocalLocation();
    if (BetweenSelectedPosition(info.GetGlobalLocation())) {
        return;
    }
    caretUpdateType_ = isMousePressed_ ? CaretUpdateType::PRESSED : CaretUpdateType::LONG_PRESSED;
    selectionMode_ = SelectionMode::SELECT;
    isSingleHandle_ = false;
    isUsingMouse_ = false;
    LOGI("TextField %{public}d handle long press", GetHost()->GetId());
    auto focusHub = GetHost()->GetOrCreateFocusHub();
    CloseSelectOverlay();
    if (IsSearchParentNode()) {
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(GetHost()->GetParent());
        focusHub = parentFrameNode->GetOrCreateFocusHub();
    }

    if (!focusHub->IsFocusOnTouch().value_or(true) || !focusHub->RequestFocusImmediately()) {
        LOGE("Long press request focus failed");
        StopTwinkling();
        return;
    }
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TextFieldPattern::UpdateSelectorByPosition(const int32_t& pos)
{
    CHECK_NULL_VOID(paragraph_);
    int32_t extendEnd = pos + GetGraphemeClusterLength(GetEditingValue().GetWideText(), pos);
    textSelector_.Update(pos, extendEnd);
}

int32_t TextFieldPattern::GetGraphemeClusterLength(const std::wstring& text, int32_t extend, bool checkPrev)
{
    char16_t aroundChar = 0;
    if (checkPrev) {
        if (static_cast<size_t>(extend) <= text.length()) {
            aroundChar = text[std::max(0, extend - 1)];
        }
    } else {
        if (static_cast<size_t>(extend) <= (text.length())) {
            aroundChar = text[std::min(static_cast<int32_t>(text.length() - 1), extend)];
        }
    }
    return StringUtils::NotInUtf16Bmp(aroundChar) ? 2 : 1;
}

void TextFieldPattern::UpdateCaretPositionWithClamp(const int32_t& pos)
{
    textEditingValue_.caretPosition =
        std::clamp(pos, 0, static_cast<int32_t>(GetEditingValue().GetWideText().length()));
}

void TextFieldPattern::ProcessOverlay()
{
    if (caretUpdateType_ != CaretUpdateType::RIGHT_CLICK) {
        StopTwinkling();
    }
    if (textEditingValue_.text.empty()) {
        CreateSingleHandle();
        return;
    }
    auto renderContext = GetHost()->GetRenderContext();
    if (renderContext) {
        AnimatePressAndHover(renderContext, 0.0f);
    }
    selectionMode_ = SelectionMode::SELECT;
    if (caretUpdateType_ == CaretUpdateType::LONG_PRESSED) {
        if (textEditingValue_.caretPosition == 0 && GetLastTouchOffset().GetX() < textRect_.GetX()) {
            UpdateSelection(0, 0);
            CreateSingleHandle();
            return;
        } else if (textEditingValue_.CaretAtLast() && GetLastTouchOffset().GetX() > textRect_.GetX()) {
            UpdateSelection(textEditingValue_.caretPosition, textEditingValue_.caretPosition);
            CreateSingleHandle();
            return;
        } else {
            UpdateSelectorByPosition(textEditingValue_.caretPosition);
        }
    }
    CreateHandles();
}

void TextFieldPattern::CreateHandles()
{
    std::vector<RSTypographyProperties::TextBox> tmp;
    MarkRedrawOverlay();
    GetTextRectsInRange(textSelector_.GetStart(), textSelector_.GetEnd(), tmp);
    auto firstHandlePosition = CalcCursorOffsetByPosition(textSelector_.GetStart());
    OffsetF firstHandleOffset(firstHandlePosition.offset.GetX() + parentGlobalOffset_.GetX(),
        firstHandlePosition.offset.GetY() + parentGlobalOffset_.GetY());
    textSelector_.firstHandleOffset_ = firstHandleOffset;
    auto secondHandlePosition = CalcCursorOffsetByPosition(textSelector_.GetEnd(), false);
    OffsetF secondHandleOffset(secondHandlePosition.offset.GetX() + parentGlobalOffset_.GetX(),
        secondHandlePosition.offset.GetY() + parentGlobalOffset_.GetY());
    textSelector_.secondHandleOffset_ = secondHandleOffset;
    SizeF handlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), caretRect_.Height() };
    std::optional<RectF> firstHandle = RectF(firstHandleOffset, handlePaintSize);
    std::optional<RectF> secondHandle = RectF(secondHandleOffset, handlePaintSize);
    LOGD("First handle %{public}s, second handle %{public}s", firstHandle->ToString().c_str(),
        secondHandle->ToString().c_str());
    CheckHandles(firstHandle, secondHandle);
    ShowSelectOverlay(firstHandle, secondHandle);
    textBoxes_ = tmp;
}

void TextFieldPattern::ShowSelectOverlay(
    const std::optional<RectF>& firstHandle, const std::optional<RectF>& secondHandle)
{
    CloseSelectOverlay();
    if (isTransparent_) {
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
        if (selectInfo.isSingleHandle && pattern->IsTextArea() &&
            pattern->GetSelectMode() == SelectionMode::SELECT_ALL) {
            auto contentRect = pattern->GetContentRect();
            auto parentGlobalOffset = pattern->GetParentGlobalOffset();
            selectInfo.menuInfo.menuOffset =
                OffsetF(contentRect.GetOffset().GetX() + contentRect.Width() / 2.0 + parentGlobalOffset.GetX(),
                    contentRect.GetOffset().GetY() + parentGlobalOffset.GetY());
        }
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

        auto host = pattern->GetHost();
        CHECK_NULL_VOID_NOLOG(host);
        auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);

        selectInfo.isUsingMouse = pattern->IsUsingMouse();

        if (layoutProperty->GetSelectionMenuHiddenValue(false) && selectInfo.isUsingMouse) {
            return;
        }

        selectInfo.rightClickOffset = pattern->GetRightClickOffset();
        selectInfo.singleLineHeight = pattern->PreferredLineHeight();
        pattern->UpdateSelectMenuInfo(hasData);
        selectInfo.menuInfo = pattern->GetSelectMenuInfo();
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
            pattern->UpdateCopyAllStatus();
            pattern->SetNeedCloseOverlay(false);
        };
        selectInfo.onClose = [weak](bool closedByGlobalEvent) {
            if (closedByGlobalEvent) {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                auto host = pattern->GetHost();
                CHECK_NULL_VOID(host);
                auto current = pattern->GetTextSelector().GetEnd();
                pattern->SetInSelectMode(SelectionMode::NONE);
                pattern->UpdateSelection(current);
                pattern->MarkRedrawOverlay();
                pattern->StartTwinkling();
                host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            }
        };

        if (!pattern->GetMenuOptionItems().empty()) {
            selectInfo.menuOptionItems = pattern->GetMenuOptionItems();
        }
        auto gesture = host->GetOrCreateGestureEventHub();
        gesture->RemoveTouchEvent(pattern->GetTouchListener());
        pattern->SetSelectOverlay(
            pipeline->GetSelectOverlayManager()->CreateAndShowSelectOverlay(selectInfo, WeakClaim(RawPtr(pattern))));

        auto selectOverlay = pattern->GetSelectOverlay();
        CHECK_NULL_VOID_NOLOG(selectOverlay);
        auto start = pattern->GetTextSelector().GetStart();
        auto end = pattern->GetTextSelector().GetEnd();
        selectOverlay->SetSelectInfo(pattern->GetTextEditingValue().GetSelectedText(start, end));

        selectOverlay->ShowOrHiddenMenu(layoutProperty->GetSelectionMenuHiddenValue(false));
        selectOverlay->DisableMenu(layoutProperty->GetSelectionMenuHiddenValue(false));
    };
    clipboard_->HasData(hasDataCallback);
}

bool TextFieldPattern::AllowCopy()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) != CopyOptions::None &&
           layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) != TextInputType::VISIBLE_PASSWORD;
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
    CHECK_NULL_VOID_NOLOG(!textEditingValue_.Empty());
    isFirstHandle_ = isFirstHandle;
    auto localOffset = handleRect.GetOffset() - parentGlobalOffset_;
    auto position = UpdateCaretPositionOnHandleMove(localOffset);
    textEditingValue_.CursorMoveToPosition(position);
    auto caretMetrics = CalcCursorOffsetByPosition(position);
    caretRect_.SetOffset(caretMetrics.offset);
    selectionMode_ = isSingleHandle_ ? SelectionMode::NONE : SelectionMode::SELECT;
    caretUpdateType_ = CaretUpdateType::HANDLE_MOVE;
    UpdateTextSelectorByHandleMove(isFirstHandle, position, caretMetrics.offset);

    auto selectOverlay = GetSelectOverlay();
    CHECK_NULL_VOID_NOLOG(selectOverlay);
    auto start = GetTextSelector().GetStart();
    auto end = GetTextSelector().GetEnd();
    selectOverlay->SetSelectInfo(GetTextEditingValue().GetSelectedText(start, end));

    GetTextRectsInRange(start, end, textBoxes_);
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

int32_t TextFieldPattern::UpdateCaretPositionOnHandleMove(const OffsetF& localOffset)
{
    int32_t position = 0;
    if (!IsTextArea()) {
        if (localOffset.GetX() < contentRect_.GetX()) {
            position = std::max(static_cast<int32_t>(textEditingValue_.caretPosition -
                                                     GetGraphemeClusterLength(GetEditingValue().GetWideText(),
                                                         GetEditingValue().caretPosition, true)),
                0);
        } else if (GreatOrEqual(localOffset.GetX(), contentRect_.GetX() + contentRect_.Width())) {
            position = std::min(static_cast<int32_t>(textEditingValue_.caretPosition +
                                                     GetGraphemeClusterLength(GetEditingValue().GetWideText(),
                                                         GetEditingValue().caretPosition)),
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

void TextFieldPattern::UpdateCopyAllStatus()
{
    selectMenuInfo_.showCopyAll = !IsSelectAll();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (selectOverlayProxy_ && !layoutProperty->GetSelectionMenuHiddenValue(false)) {
        selectOverlayProxy_->UpdateSelectMenuInfo(selectMenuInfo_);
    }
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
        UpdateSelection(position, textSelector_.GetEnd());
        textSelector_.selectionBaseOffset = offsetToParagraphBeginning;
        return;
    }
    UpdateSelection(textSelector_.GetStart(), position);
    textSelector_.selectionDestinationOffset = offsetToParagraphBeginning;
}

void TextFieldPattern::OnHandleMoveDone(const RectF& /* handleRect */, bool isFirstHandle)
{
    CHECK_NULL_VOID_NOLOG(SelectOverlayIsOn());
    caretUpdateType_ = CaretUpdateType::HANDLE_MOVE_DONE;
    isFirstHandle_ = isFirstHandle;
    StopTwinkling();
    UpdateCopyAllStatus();
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TextFieldPattern::UpdateOtherHandleOnMove(float dx, float dy)
{
    SelectHandleInfo firstInfo, secondInfo;
    SizeF handlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), caretRect_.Height() };
    if (isFirstHandle_) {
        // update position of the other handle
        textSelector_.secondHandleOffset_.AddX(dx);
        textSelector_.secondHandleOffset_.AddY(dy);
        secondInfo.paintRect = { textSelector_.secondHandleOffset_, handlePaintSize };
        // hide the other handle if it's outside content rect
        auto handleOffset = textSelector_.secondHandleOffset_ - parentGlobalOffset_;
        secondInfo.isShow =
            contentRect_.IsInRegion({ handleOffset.GetX(), handleOffset.GetY() + caretRect_.Height() / 2 });
        selectOverlayProxy_->UpdateSecondSelectHandleInfo(secondInfo);
    } else {
        textSelector_.firstHandleOffset_.AddX(dx);
        textSelector_.firstHandleOffset_.AddY(dy);
        firstInfo.paintRect = { textSelector_.firstHandleOffset_, handlePaintSize };

        auto handleOffset = textSelector_.firstHandleOffset_ - parentGlobalOffset_;
        firstInfo.isShow =
            contentRect_.IsInRegion({ handleOffset.GetX(), handleOffset.GetY() + caretRect_.Height() / 2 });
        selectOverlayProxy_->UpdateFirstSelectHandleInfo(firstInfo);
    }
}

void TextFieldPattern::SetHandlerOnMoveDone()
{
    SelectHandleInfo info;
    auto newHandleOffset = parentGlobalOffset_;
    auto handleOffset = CalcCursorOffsetByPosition(
        isFirstHandle_ ? textSelector_.baseOffset : textSelector_.destinationOffset, isFirstHandle_ ? true : false);
    newHandleOffset += handleOffset.offset;
    SizeF handlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), caretRect_.Height() };
    RectF newHandle;
    newHandle.SetOffset(newHandleOffset);
    newHandle.SetSize(handlePaintSize);
    info.paintRect = newHandle;
    info.needLayout = true;
    selectionMode_ = isSingleHandle_ ? SelectionMode::NONE : SelectionMode::SELECT;
    if (isFirstHandle_) {
        textSelector_.firstHandleOffset_ = newHandleOffset;
        selectOverlayProxy_->UpdateFirstSelectHandleInfo(info);
        return;
    }
    textSelector_.secondHandleOffset_ = newHandleOffset;
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
    LOGI("Textfield %{public}d %{public}s", GetHost()->GetId(), isHover ? "on hover" : "exit hover");
    auto frame = GetHost();
    CHECK_NULL_VOID(frame);
    auto frameId = frame->GetId();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    if (isHover) {
        pipeline->SetMouseStyleHoldNode(frameId);
        pipeline->ChangeMouseStyle(frameId, MouseFormat::TEXT_CURSOR);
    } else {
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        pipeline->FreeMouseStyleHoldNode(frameId);
    }
    isOnHover_ = isHover;
    if (enableTouchAndHoverEffect_) {
        auto textfieldPaintProperty = GetPaintProperty<TextFieldPaintProperty>();
        CHECK_NULL_VOID(textfieldPaintProperty);
        auto renderContext = GetHost()->GetRenderContext();
        auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        if (isOnHover_) {
            if (layoutProperty->GetShowUnderlineValue(false)) {
                auto radius = textFieldTheme->GetBorderRadiusSize();
                renderContext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
            }
            AnimatePressAndHover(renderContext, HOVER_ANIMATION_OPACITY, true);
            GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
            return;
        }
        isOnHover_ = false;
        if (!isMousePressed_) {
            if (layoutProperty->GetShowUnderlineValue(false)) {
                renderContext->UpdateBorderRadius(borderRadius_);
            }
            if (layoutProperty->GetShowUnderlineValue(false) && HasFocus()) {
                auto radius = textFieldTheme->GetBorderRadiusSize();
                renderContext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
            }
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
    pipeline->SetMouseStyleHoldNode(frameId);

    if (!IsSearchParentNode()) {
        info.SetStopPropagation(true);
    }

    if (info.GetLocalLocation().GetX() > (frameRect_.Width() - imageRect_.Width() - GetIconRightOffset()) &&
        NeedShowPasswordIcon()) {
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        return;
    } else {
        pipeline->ChangeMouseStyle(frameId, MouseFormat::TEXT_CURSOR);
    }

    auto focusHub = GetHost()->GetOrCreateFocusHub();

    if (IsSearchParentNode()) {
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(GetHost()->GetParent());
        focusHub = parentFrameNode->GetOrCreateFocusHub();
    }

    if (info.GetButton() == MouseButton::RIGHT_BUTTON) {
        if (info.GetAction() == MouseAction::PRESS) {
            LOGI("Handle mouse right button press");
            isMousePressed_ = true;
        }
        if (info.GetAction() == MouseAction::PRESS || info.GetAction() == MouseAction::RELEASE) {
            CloseSelectOverlay();
        }

        if (info.GetAction() == MouseAction::RELEASE) {
            LOGI("Handle mouse right button release");
            rightClickOffset_ = OffsetF(static_cast<float>(info.GetGlobalLocation().GetX()),
                static_cast<float>(info.GetGlobalLocation().GetY()));
            lastTouchOffset_ = info.GetLocalLocation();
            caretUpdateType_ = CaretUpdateType::RIGHT_CLICK;
            selectionMode_ = SelectionMode::NONE;
            isSingleHandle_ = false;
            isUsingMouse_ = true;
            mouseStatus_ = MouseStatus::RELEASED;
            isMousePressed_ = false;
            GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        return;
    }
    if (info.GetAction() == MouseAction::PRESS) {
        LOGI("Handle mouse left button press");
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
        UpdateCaretPositionByPressOffset();
        if (!focusHub->IsFocusOnTouch().value_or(true) || !focusHub->RequestFocusImmediately()) {
            LOGE("Request focus failed, cannot open input method");
            StopTwinkling();
            return;
        }
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        return;
    }
    if (info.GetAction() == MouseAction::RELEASE) {
        LOGI("Handle mouse left button release");
        CloseSelectOverlay();
        caretUpdateType_ = CaretUpdateType::NONE;
        isMousePressed_ = false;
        mouseStatus_ = MouseStatus::RELEASED;
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
        MarkRedrawOverlay();
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void TextFieldPattern::UpdatePositionOfParagraph(int32_t position)
{
    textEditingValue_.CursorMoveToPosition(position);
}

void TextFieldPattern::UpdateTextFieldManager(const Offset& offset, float height)
{
    if (!HasFocus()) {
        return;
    }
    auto context = GetHost()->GetContext();
    CHECK_NULL_VOID(context);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    textFieldManager->SetClickPosition(offset);
    textFieldManager->SetHeight(height);
    textFieldManager->SetOnFocusTextField(WeakClaim(this));
}

TextInputAction TextFieldPattern::GetDefaultTextInputAction()
{
    TextInputAction defaultTextInputAction = TextInputAction::DONE;
    if (IsSearchParentNode()) {
        defaultTextInputAction = TextInputAction::SEARCH;
    } else if (IsTextArea()) {
        defaultTextInputAction = TextInputAction::UNSPECIFIED;
    } else {
        defaultTextInputAction = TextInputAction::DONE;
    }
    return defaultTextInputAction;
}

bool TextFieldPattern::RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard)
{
    auto context = GetHost()->GetContext();
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
        MiscServices::InputAttribute inputAttribute = { .inputPattern = (int32_t)keyboard_,
            .enterKeyType = (int32_t)GetTextInputActionValue(TextInputAction::DONE) };
        MiscServices::TextConfig textConfig = { .inputAttribute = inputAttribute,
            .windowId = context->GetFocusWindowId() };
        LOGI("RequestKeyboard set calling window id is : %{public}u", textConfig.windowId);
        inputMethod->Attach(textChangeListener_, needShowSoftKeyboard, textConfig);
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        imeAttached_ = true;
#endif
#else
        if (!HasConnection()) {
            TextInputConfiguration config;
            config.type = keyboard_;
            config.action = GetTextInputActionValue(GetDefaultTextInputAction());
            config.inputFilter = GetInputFilter();
            config.maxLength = GetMaxLength();
            config.obscureText = textObscured_;
            LOGI("Request keyboard configuration: type=%{private}d action=%{private}d obscureText=%{private}d",
                keyboard_, config.action, textObscured_);
            connection_ = TextInputProxy::GetInstance().Attach(
                WeakClaim(this), config, context->GetTaskExecutor(), GetInstanceId());

            if (!HasConnection()) {
                LOGE("Get TextInput connection error");
                return false;
            }
            TextEditingValue value;
            value.text = textEditingValue_.text;
            value.hint = GetPlaceHolder();
            value.selection.Update(textSelector_.baseOffset, textSelector_.destinationOffset);
            connection_->SetEditingState(value, GetInstanceId());
        }
        connection_->Show(isFocusViewChanged, GetInstanceId());
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
#else
        if (HasConnection()) {
            connection_->Close(GetInstanceId());
            connection_ = nullptr;
        }
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
    if (textObscured_) {
        ImageSourceInfo hidePasswordSourceInfo = GetImageSourceInfoFromTheme(textObscured_);
        if (hideUserDefinedIcon_) {
            UpdateUserDefineResource(hidePasswordSourceInfo);
        } else {
            UpdateInternalResource(hidePasswordSourceInfo);
        }
        LoadNotifier hideIconLoadNotifier(CreateDataReadyCallback(textObscured_),
            CreateLoadSuccessCallback(textObscured_), CreateLoadFailCallback(textObscured_));
        hidePasswordImageLoadingCtx_ =
            AceType::MakeRefPtr<ImageLoadingContext>(hidePasswordSourceInfo, std::move(hideIconLoadNotifier), true);
        hidePasswordImageLoadingCtx_->LoadImageData();
        return;
    }
    if (!textObscured_) {
        ImageSourceInfo showPasswordSourceInfo = GetImageSourceInfoFromTheme(textObscured_);
        if (showUserDefinedIcon_) {
            UpdateUserDefineResource(showPasswordSourceInfo);
        } else {
            UpdateInternalResource(showPasswordSourceInfo);
        }
        LoadNotifier showIconLoadNotifier(CreateDataReadyCallback(textObscured_),
            CreateLoadSuccessCallback(textObscured_), CreateLoadFailCallback(textObscured_));
        showPasswordImageLoadingCtx_ =
            AceType::MakeRefPtr<ImageLoadingContext>(showPasswordSourceInfo, std::move(showIconLoadNotifier), true);
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
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, imageSourceInfo);
    if (checkHidePasswordIcon && hideUserDefinedIcon_) {
        return layoutProperty->GetHidePasswordSourceInfoValue(imageSourceInfo);
    }
    if (checkHidePasswordIcon) {
        imageSourceInfo.SetResourceId(InternalResource::ResourceId::HIDE_PASSWORD_SVG);
        return imageSourceInfo;
    }
    if (showUserDefinedIcon_) {
        return layoutProperty->GetShowPasswordSourceInfoValue(imageSourceInfo);
    }
    imageSourceInfo.SetResourceId(InternalResource::ResourceId::SHOW_PASSWORD_SVG);
    return imageSourceInfo;
}

void TextFieldPattern::UpdateUserDefineResource(ImageSourceInfo& sourceInfo)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto iconPath = sourceInfo.GetSrc();
    if (iconPath.empty()) {
        LOGE("Icon path empty");
        return;
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkNeedRenderOnly();
    if (checkHidePasswordIcon) {
        LOGI("Load hide icon successfully");
        hidePasswordCanvasImage_ = hidePasswordImageLoadingCtx_->MoveCanvasImage();
        config.srcRect_ = hidePasswordImageLoadingCtx_->GetSrcRect();
        config.dstRect_ = hidePasswordImageLoadingCtx_->GetDstRect();
        config.isSvg_ = hidePasswordImageLoadingCtx_->GetSourceInfo().IsSvg();
        hidePasswordCanvasImage_->SetPaintConfig(config);
        return;
    }
    LOGI("Load show icon successfully");
    showPasswordCanvasImage_ = showPasswordImageLoadingCtx_->MoveCanvasImage();
    config.srcRect_ = showPasswordImageLoadingCtx_->GetSrcRect();
    config.dstRect_ = showPasswordImageLoadingCtx_->GetDstRect();
    config.isSvg_ = showPasswordImageLoadingCtx_->GetSourceInfo().IsSvg();
    showPasswordCanvasImage_->SetPaintConfig(config);
}

void TextFieldPattern::OnTextInputActionUpdate(TextInputAction value) {}

void TextFieldPattern::InsertValue(const std::string& insertValue)
{
    LOGD("Insert value '%{public}s'", insertValue.c_str());
    auto wideInsertValue = StringUtils::ToWstring(insertValue);
    LOGD("Insert length %{public}d", static_cast<int32_t>(wideInsertValue.length()));
    auto originLength = static_cast<uint32_t>(textEditingValue_.GetWideText().length());
    if (originLength >= GetMaxLength() && !InSelectMode()) {
        LOGW("Max length reached");
        return;
    }

    std::string valueToUpdate;
    if (originLength + wideInsertValue.length() >= GetMaxLength() && !InSelectMode()) {
        valueToUpdate = StringUtils::ToString(wideInsertValue.substr(0, GetMaxLength() - originLength));
    } else {
        valueToUpdate = insertValue;
    }
    std::string oldText = textEditingValue_.text;
    auto caretStart = 0;
    std::string result;
    auto textFieldLayoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto start = textSelector_.GetStart();
    auto end = textSelector_.GetEnd();
    SwapIfLarger(start, end);
    if (InSelectMode()) {
        LOGI("In select mode, replace selected text");
        caretStart = start;
    } else {
        caretStart = textEditingValue_.caretPosition;
    }
    EditingValueFilter(valueToUpdate, result);
    if (result.empty()) {
        return;
    }
    if (InSelectMode()) {
        textEditingValue_.text =
            textEditingValue_.GetValueBeforePosition(start) + result + textEditingValue_.GetValueAfterPosition(end);
    } else {
        textEditingValue_.text =
            textEditingValue_.GetValueBeforeCursor() + result + textEditingValue_.GetValueAfterCursor();
    }
    textEditingValue_.CursorMoveToPosition(caretStart + static_cast<int32_t>(StringUtils::ToWstring(result).length()));
    SetEditingValueToProperty(textEditingValue_.text);
    UpdateEditingValueToRecord();
    caretUpdateType_ = CaretUpdateType::INPUT;
    cursorVisible_ = true;
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
    if (IsTextArea() && layoutProperty->HasMaxLength()) {
        HandleCounterBorder();
    }
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
    auto textFieldAccessibilityProperty = GetHost()->GetAccessibilityProperty<TextFieldAccessibilityProperty>();
    CHECK_NULL_RETURN(textFieldAccessibilityProperty, false);
    textFieldAccessibilityProperty->SetErrorText(errorText);
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
                auto charExists = textEditingValue_.text.find('@') != std::string::npos;
                result = charExists ? "" : valueToUpdate;
                return;
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
        TextFieldLayoutAlgorithm::UpdateTextStyle(GetHost(), layoutProperty, textFieldTheme, textStyle, false);
        textContent = "a";
    } else {
        TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyle(layoutProperty, textFieldTheme, textStyle, false);
        textContent = "b";
    }
    if (textStyle.GetFontSize().IsNonPositive()) {
        textStyle.SetFontSize(DEFAULT_FONT);
    }
    RSParagraphStyle paraStyle;
    paraStyle.textDirection_ = ToRSTextDirection(TextFieldLayoutAlgorithm::GetTextDirection(textEditingValue_.text));
    paraStyle.textAlign_ = ToRSTextAlign(textStyle.GetTextAlign());
    paraStyle.maxLines_ = textStyle.GetMaxLines();
    paraStyle.locale_ = Localization::GetInstance()->GetFontLocale();
    paraStyle.wordBreakType_ = ToRSWordBreakType(textStyle.GetWordBreak());
    paraStyle.fontSize_ = textStyle.GetFontSize().ConvertToPx();
    if (LessOrEqual(paraStyle.fontSize_, 0.0f)) {
        paraStyle.fontSize_ = DEFAULT_FONT.ConvertToPx();
    }
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
    UpdateSelection(textEditingValue_.caretPosition);
    GetTextRectsInRange(textSelector_.GetStart(), textSelector_.GetEnd(), textBoxes_);
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

int32_t TextFieldPattern::GetWordLength(int32_t originCaretPosition, int32_t directionMove)
{
    if (textEditingValue_.text.empty()) {
        return 0;
    }
    int32_t textLength = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    if (originCaretPosition < 0 || originCaretPosition > textLength) {
        LOGD("Get word length failed, the origin caret position is out of range");
        return 0;
    }
    // directionMove == 0 left, directionMove == 1 right
    // cannot get word length by current caret position and direction
    if ((directionMove == 0 && originCaretPosition == 0) ||
        (directionMove == 1 && originCaretPosition == textLength)) {
        return 0;
    }
    int32_t offset = 0;
    int32_t strIndex = 0;
    auto wideTextValue = textEditingValue_.GetWideText();
    for (directionMove == 0 ? strIndex = (originCaretPosition - 1) : strIndex = originCaretPosition;
         directionMove == 0 ? strIndex >= 0 : strIndex <= textLength;) {
        if ((wideTextValue[strIndex] >= L'0' && wideTextValue[strIndex] <= L'9') ||
            (wideTextValue[strIndex] >= L'a' && wideTextValue[strIndex] <= L'z') ||
            (wideTextValue[strIndex] >= L'A' && wideTextValue[strIndex] <= L'Z')) {
            offset++;
        } else {
            if (offset > 0) {
                break;
            }
            offset = 1;
            break;
        }
        if (directionMove == 0) {
            strIndex--;
        } else {
            strIndex++;
        }
    }
    return offset;
}

int32_t TextFieldPattern::GetLineBeginPosition(int32_t originCaretPosition, bool needToCheckLineChanged)
{
    if (textEditingValue_.text.empty()) {
        return 0;
    }
    int32_t textLength = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    if (originCaretPosition < 0 || originCaretPosition > textLength) {
        LOGD("Get begin position failed, the origin caret position is out of range");
        return 0;
    }
    if (originCaretPosition == 0) {
        return originCaretPosition;
    }
    int32_t moveLineBeginOffset = 0;
    int32_t strIndex = originCaretPosition;
    auto wideTextValue = textEditingValue_.GetWideText();
    do {
        moveLineBeginOffset++;
        strIndex--;
        // stop moving caret if reaches \n, text head or caret line changed
    } while (((strIndex > 0) && (wideTextValue[strIndex] != L'\n')) ||
             (needToCheckLineChanged && !CharLineChanged(strIndex)));
    if (wideTextValue[strIndex] == L'\n') {
        moveLineBeginOffset--;
    }
    if (moveLineBeginOffset > originCaretPosition) {
        return 0;
    }
    return originCaretPosition - moveLineBeginOffset;
}

int32_t TextFieldPattern::GetLineEndPosition(int32_t originCaretPosition, bool needToCheckLineChanged)
{
    if (textEditingValue_.text.empty()) {
        return 0;
    }
    int32_t textLength = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    if (originCaretPosition < 0 || originCaretPosition > textLength) {
        LOGD("Get line end position failed, the origin caret position is out of range");
        return originCaretPosition;
    }
    if (originCaretPosition == textLength) {
        return originCaretPosition;
    }
    int32_t moveLineEndOffset = 0;
    int32_t strIndex = 0;
    auto wideTextValue = textEditingValue_.GetWideText();
    for (strIndex = originCaretPosition + 1; (strIndex <= textLength && wideTextValue[strIndex] != L'\n') ||
                                         (needToCheckLineChanged && !CharLineChanged(strIndex));
        strIndex++) {
        moveLineEndOffset++;
    }
    if (moveLineEndOffset > textLength - originCaretPosition) {
        return textLength;
    }
    return originCaretPosition + moveLineEndOffset;
}

bool TextFieldPattern::CharLineChanged(int32_t caretPosition)
{
    if (caretPosition < 0 || caretPosition > static_cast<int32_t>(textEditingValue_.GetWideText().length())) {
        return true;
    }
    auto caretMetrics = CalcCursorOffsetByPosition(caretPosition);
    return !NearEqual(caretMetrics.offset.GetY(), caretRect_.GetY());
}

bool TextFieldPattern::CursorMoveLeft()
{
    LOGI("Handle cursor move left");
    auto originCaretPosition = textEditingValue_.caretPosition;
    if (InSelectMode() && selectionMode_ == SelectionMode::SELECT_ALL) {
        textEditingValue_.caretPosition = 0;
    } else if (InSelectMode()) {
        textBoxes_.clear();
    } else {
        UpdateCaretPositionWithClamp(
            textEditingValue_.caretPosition -
            GetGraphemeClusterLength(textEditingValue_.GetWideText(), textEditingValue_.caretPosition, true));
    }
    OnCursorMoveDone();
    if (originCaretPosition == textEditingValue_.caretPosition) {
        return false;
    }
    return true;
}

bool TextFieldPattern::CursorMoveLeftWord()
{
    if (textEditingValue_.caretPosition == 0) {
        LOGW("Caret position at beginning, cannot move to left");
        return true;
    }
    int32_t originCaretPosition = textEditingValue_.caretPosition;
    int32_t textLength = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    int32_t leftWordLength = GetWordLength(originCaretPosition, 0);
    if (leftWordLength < 0 || leftWordLength > textLength || textEditingValue_.caretPosition - leftWordLength < 0) {
        LOGD("Get left word length faild, the left word offset is out of range");
        return false;
    }
    if (InSelectMode() && selectionMode_ == SelectionMode::SELECT_ALL) {
        textEditingValue_.caretPosition = 0;
    } else if (InSelectMode()) {
        textBoxes_.clear();
    } else {
        UpdateCaretPositionWithClamp(originCaretPosition - leftWordLength);
    }
    OnCursorMoveDone();
    return originCaretPosition != textEditingValue_.caretPosition;
}

bool TextFieldPattern::CursorMoveLineBegin()
{
    if (textEditingValue_.caretPosition == 0) {
        LOGW("Caret position at beginning, cannot move to left");
        return true;
    }
    int32_t textLength = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    int32_t originCaretPosition = textEditingValue_.caretPosition;
    int32_t lineBeginPosition = GetLineBeginPosition(originCaretPosition);
    if (lineBeginPosition < 0 || lineBeginPosition > textLength) {
        LOGD("Cursor move to line begin faild, the line begin offset is out of range");
        return false;
    }
    if (InSelectMode() && selectionMode_ == SelectionMode::SELECT_ALL) {
        textEditingValue_.caretPosition = 0;
    } else if (IsTextArea()) {
        UpdateCaretPositionWithClamp(lineBeginPosition);
    } else {
        UpdateCaretPositionWithClamp(0);
    }
    OnCursorMoveDone();
    return originCaretPosition != textEditingValue_.caretPosition;
}

bool TextFieldPattern::CursorMoveToParagraphBegin()
{
    if (textEditingValue_.caretPosition == 0) {
        LOGW("Caret position at beginning, cannot move to left");
        return true;
    }
    auto originCaretPosition = textEditingValue_.caretPosition;
    UpdateCaretPositionWithClamp(GetLineBeginPosition(originCaretPosition, false));
    OnCursorMoveDone();
    return originCaretPosition != textEditingValue_.caretPosition;
}

bool TextFieldPattern::CursorMoveHome()
{
    // ctrl + home, caret move to position 0
    if (textEditingValue_.caretPosition == 0) {
        LOGW("Caret position at beginning, cannot move to left");
        return true;
    }
    int32_t originCaretPosition = textEditingValue_.caretPosition;
    UpdateCaretPositionWithClamp(0);
    OnCursorMoveDone();
    return originCaretPosition != textEditingValue_.caretPosition;
}

bool TextFieldPattern::CursorMoveRight()
{
    LOGI("Handle cursor move right");
    auto originCaretPosition = textEditingValue_.caretPosition;
    if (InSelectMode() && selectionMode_ == SelectionMode::SELECT_ALL) {
        textEditingValue_.caretPosition = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    } else if (InSelectMode()) {
        textBoxes_.clear();
    } else {
        UpdateCaretPositionWithClamp(
            textEditingValue_.caretPosition +
            GetGraphemeClusterLength(textEditingValue_.GetWideText(), textEditingValue_.caretPosition));
    }
    OnCursorMoveDone();
    if (originCaretPosition == textEditingValue_.caretPosition) {
        return false;
    }
    return true;
}

bool TextFieldPattern::CursorMoveRightWord()
{
    if (textEditingValue_.caretPosition == static_cast<int32_t>(textEditingValue_.GetWideText().length())) {
        LOGW("Caret position at the end, cannot move to right");
        return true;
    }
    int32_t originCaretPosition = textEditingValue_.caretPosition;
    int32_t textLength = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    int32_t rightWordLength = GetWordLength(originCaretPosition, 1);
    if (rightWordLength < 0 || rightWordLength > textLength ||
        rightWordLength + textEditingValue_.caretPosition > textLength) {
        LOGD("Get right word length failed, the right word offset is out of range");
        return false;
    }
    if (InSelectMode() && selectionMode_ == SelectionMode::SELECT_ALL) {
        textEditingValue_.caretPosition = textLength;
    } else {
        UpdateCaretPositionWithClamp(originCaretPosition + rightWordLength);
    }
    OnCursorMoveDone();
    return originCaretPosition != textEditingValue_.caretPosition;
}

bool TextFieldPattern::CursorMoveLineEnd()
{
    if (textEditingValue_.caretPosition == static_cast<int32_t>(textEditingValue_.GetWideText().length())) {
        LOGW("Caret position at the end, cannot move to right");
        return true;
    }
    int32_t originCaretPosition = textEditingValue_.caretPosition;
    int32_t textLength = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    int32_t lineEndPosition = GetLineEndPosition(originCaretPosition);
    if (lineEndPosition < 0 || lineEndPosition > textLength) {
        LOGD("Handle cursor move to line end failed, the line end position is out of range");
        return false;
    }
    if (InSelectMode() && selectionMode_ == SelectionMode::SELECT_ALL) {
        textEditingValue_.caretPosition = textLength;
    } else if (IsTextArea()) {
        UpdateCaretPositionWithClamp(lineEndPosition);
    } else {
        UpdateCaretPositionWithClamp(textLength);
    }
    OnCursorMoveDone();
    return originCaretPosition != textEditingValue_.caretPosition;
}

bool TextFieldPattern::CursorMoveToParagraphEnd()
{
    if (textEditingValue_.caretPosition == static_cast<int32_t>(textEditingValue_.GetWideText().length())) {
        LOGW("Caret position at the end, cannot move to right");
        return true;
    }
    auto originCaretPosition = textEditingValue_.caretPosition;
    UpdateCaretPositionWithClamp(GetLineEndPosition(originCaretPosition, false));
    OnCursorMoveDone();
    return originCaretPosition != textEditingValue_.caretPosition;
}

bool TextFieldPattern::CursorMoveEnd()
{
    // ctrl end, caret to the very end
    if (textEditingValue_.caretPosition == static_cast<int32_t>(textEditingValue_.GetWideText().length())) {
        LOGW("Caret position at the end, cannot move to right");
        return true;
    }
    int32_t originCaretPosition = textEditingValue_.caretPosition;
    int32_t textLength = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    UpdateCaretPositionWithClamp(textLength);
    OnCursorMoveDone();
    return originCaretPosition != textEditingValue_.caretPosition;
}

bool TextFieldPattern::CursorMoveUp()
{
    LOGI("Handle cursor move up");
    CHECK_NULL_RETURN_NOLOG(IsTextArea(), false);
    auto originCaretPosition = textEditingValue_.caretPosition;
    auto offsetX = caretRect_.GetX() - contentRect_.GetX();
    auto offsetY = caretRect_.GetY() - textRect_.GetY();
    // multiply by 0.5f to convert to the grapheme center point of the previous line.
    float verticalOffset = offsetY - PreferredLineHeight() * 0.5f;
    textEditingValue_.caretPosition = static_cast<int32_t>(
#ifndef NEW_SKIA
        paragraph_->GetGlyphPositionAtCoordinateWithCluster(caretRect_.GetX(), verticalOffset).pos_);
#else
        paragraph_->GetGlyphPositionAtCoordinate(offsetX, verticalOffset).pos_);
#endif
    OnCursorMoveDone();
    if (originCaretPosition == textEditingValue_.caretPosition) {
        return false;
    }
    return true;
}

bool TextFieldPattern::CursorMoveDown()
{
    LOGI("Handle cursor move down");
    CHECK_NULL_RETURN_NOLOG(IsTextArea(), false);
    auto originCaretPosition = textEditingValue_.caretPosition;
    auto offsetX = caretRect_.GetX() - contentRect_.GetX();
    auto offsetY = caretRect_.GetY() - textRect_.GetY();
    // multiply by 1.5f to convert to the grapheme center point of the next line.
    float verticalOffset = offsetY + PreferredLineHeight() * 1.5f;
    textEditingValue_.caretPosition = static_cast<int32_t>(
#ifndef NEW_SKIA
        paragraph_->GetGlyphPositionAtCoordinateWithCluster(caretRect_.GetX(), verticalOffset).pos_);
#else
        paragraph_->GetGlyphPositionAtCoordinate(offsetX, verticalOffset).pos_);
#endif
    OnCursorMoveDone();
    if (originCaretPosition == textEditingValue_.caretPosition) {
        return false;
    }
    return true;
}

void TextFieldPattern::Delete(int32_t start, int32_t end)
{
    SwapIfLarger(start, end);
    LOGI("Handle Delete within [%{public}d, %{public}d]", start, end);
    textEditingValue_.text =
        textEditingValue_.GetValueBeforePosition(start) + textEditingValue_.GetValueAfterPosition(end);
    UpdateCaretPositionWithClamp(start);
    SetEditingValueToProperty(textEditingValue_.text);
    FireEventHubOnChange(GetEditingValue().text);
    selectionMode_ = SelectionMode::NONE;
    caretUpdateType_ = CaretUpdateType::DEL;
    CloseSelectOverlay();
    cursorVisible_ = true;
    UpdateEditingValueToRecord();
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (IsTextArea() && layoutProperty->HasMaxLength()) {
        HandleCounterBorder();
    }
    // trigger repaint of select mask
    ++drawOverlayFlag_;
    GetHost()->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                      : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::SetEditingValueToProperty(const std::string& newValueText)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto textCache = layoutProperty->GetValueValue("");
    layoutProperty->UpdateValue(newValueText);
    if (textCache != newValueText) {
        host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, textCache, newValueText.c_str());
    }
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

void TextFieldPattern::HandleCounterBorder()
{
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto maxLength = GetMaxLength();
    auto currentLength = static_cast<uint32_t>(textEditingValue_.GetWideText().length());

    BorderWidthProperty currentBorderWidth;
    if (layoutProperty->GetBorderWidthProperty() != nullptr) {
        currentBorderWidth = *(layoutProperty->GetBorderWidthProperty());
    } else {
        currentBorderWidth.SetBorderWidth(BORDER_DEFAULT_WIDTH);
    }
    BorderWidthProperty overCountBorderWidth;
    overCountBorderWidth.SetBorderWidth(OVER_COUNT_BORDER_WIDTH);

    BorderColorProperty currentBorderColor;
    auto renderContext = GetHost()->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->HasBorderColor()) {
        currentBorderColor = renderContext->GetBorderColor().value();
    }
    BorderColorProperty overCountBorderColor;
    overCountBorderColor.SetColor(textFieldTheme->GetOverCountBorderColor());
    if (currentLength == maxLength) {
        if (!(currentBorderWidth == overCountBorderWidth)) {
            lastDiffBorderWidth_ = currentBorderWidth;
            layoutProperty->UpdateBorderWidth(overCountBorderWidth);
            renderContext->UpdateBorderWidth(overCountBorderWidth);
        }
        if (!(currentBorderColor == overCountBorderColor)) {
            lastDiffBorderColor_ = currentBorderColor;
            renderContext->UpdateBorderColor(overCountBorderColor);
        }
    } else {
        if (currentBorderWidth == overCountBorderWidth) {
            layoutProperty->UpdateBorderWidth(lastDiffBorderWidth_);
            renderContext->UpdateBorderWidth(lastDiffBorderWidth_);
        }
        if (currentBorderColor == overCountBorderColor) {
            renderContext->UpdateBorderColor(lastDiffBorderColor_);
        }
    }
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

    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    if (paintProperty->GetInputStyleValue(InputStyle::DEFAULT) == InputStyle::INLINE) {
        HandleBlurEvent();
        eventHub->FireOnSubmit(static_cast<int32_t>(action));
        return;
    }

    if (IsTextArea()) {
        if (GetInputFilter() != "\n") {
            InsertValue("\n");
        }
        return;
    }
    eventHub->FireOnSubmit(static_cast<int32_t>(action));
    CloseKeyboard(forceCloseKeyboard);
}

void TextFieldPattern::UpdateEditingValue(const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent)
{
    textEditingValue_.text = value->text;
    textEditingValue_.caretPosition = value->selection.baseOffset;
    ContainerScope scope(GetInstanceId());
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

    if (needFireChangeEvent) {
        auto eventHub = host->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnChange(textEditingValue_.text);
    }

    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                 : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::OnValueChanged(bool needFireChangeEvent, bool needFireSelectChangeEvent) {}

void TextFieldPattern::OnAreaChangedInner()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto parentGlobalOffset = host->GetPaintRectOffset() - context->GetRootRect().GetOffset();
    if (parentGlobalOffset != parentGlobalOffset_) {
        parentGlobalOffset_ = parentGlobalOffset;
        UpdateTextFieldManager(Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY()), frameRect_.Height());
        CHECK_NULL_VOID_NOLOG(SelectOverlayIsOn());
        textSelector_.selectionBaseOffset.SetX(CalcCursorOffsetByPosition(textSelector_.GetStart()).offset.GetX());
        textSelector_.selectionDestinationOffset.SetX(
            CalcCursorOffsetByPosition(textSelector_.GetEnd(), false).offset.GetX());
        UpdateSelection(textSelector_.GetStart(), textSelector_.GetEnd());
        if (isSingleHandle_) {
            CreateSingleHandle();
            RequestKeyboardOnFocus();
            return;
        }
        ProcessOverlay();
        selectionMode_ = SelectionMode::SELECT;
    }
    RequestKeyboardOnFocus();
}

void TextFieldPattern::RequestKeyboardOnFocus()
{
    if (!needToRequestKeyboardOnFocus_ || !needToRequestKeyboardInner_) {
        return;
    }
    LOGI("RequestKeyboardOnFocus");
    if (!RequestKeyboard(false, true, true)) {
        return;
    }
    StartTwinkling();
    LOGI("RequestKeyboardOnFocus ok, reset flag");
    auto eventHub = GetHost()->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnEditChanged(true);
    needToRequestKeyboardInner_ = false;
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

void TextFieldPattern::HandleSurfaceChanged(int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight)
{
    LOGI("Textfield handle surface change, new width %{public}d, new height %{public}d, prev width %{public}d, prev "
         "height %{public}d",
        newWidth, newHeight, prevWidth, prevHeight);
    CloseSelectOverlay();
    if (HasFocus() && isSingleHandle_) {
        StartTwinkling();
    }
    UpdateCaretInfoToController();
}

void TextFieldPattern::HandleSurfacePositionChanged(int32_t posX, int32_t posY) const
{
    LOGI("Textfield handle surface position change, posX %{public}d, posY %{public}d", posX, posY);
    UpdateCaretInfoToController();
}

void TextFieldPattern::InitSurfaceChangedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (!HasSurfaceChangedCallback()) {
        auto callbackId = pipeline->RegisterSurfaceChangedCallback(
            [weak = WeakClaim(this)](int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight,
                WindowSizeChangeReason type) {
                auto pattern = weak.Upgrade();
                if (pattern) {
                    pattern->HandleSurfaceChanged(newWidth, newHeight, prevWidth, prevHeight);
                }
            });
        LOGI("Add surface changed callback id %{public}d", callbackId);
        UpdateSurfaceChangedCallbackId(callbackId);
    }
}

void TextFieldPattern::InitSurfacePositionChangedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (!HasSurfacePositionChangedCallback()) {
        auto callbackId =
            pipeline->RegisterSurfacePositionChangedCallback([weak = WeakClaim(this)](int32_t posX, int32_t posY) {
                auto pattern = weak.Upgrade();
                if (pattern) {
                    pattern->HandleSurfacePositionChanged(posX, posY);
                }
            });
        LOGI("Add position changed callback id %{public}d", callbackId);
        UpdateSurfacePositionChangedCallbackId(callbackId);
    }
}

void TextFieldPattern::DeleteBackward(int32_t length)
{
    LOGI("Handle DeleteBackward %{public}d characters", length);
    if (InSelectMode()) {
        Delete(textSelector_.GetStart(), textSelector_.GetEnd());
        return;
    }
    if (textEditingValue_.caretPosition <= 0) {
        LOGW("Caret position at the beginning , cannot DeleteBackward");
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
    cursorVisible_ = true;
    UpdateEditingValueToRecord();
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (IsTextArea() && layoutProperty->HasMaxLength()) {
        HandleCounterBorder();
    }
    GetHost()->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                      : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::DeleteForward(int32_t length)
{
    LOGI("Handle DeleteForward %{public}d characters", length);
    if (InSelectMode()) {
        Delete(textSelector_.GetStart(), textSelector_.GetEnd());
        return;
    }
    if (textEditingValue_.caretPosition >= static_cast<int32_t>(textEditingValue_.GetWideText().length())) {
        LOGW("Caret position at the end , cannot DeleteForward");
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
    if (IsTextArea() && layoutProperty->HasMaxLength()) {
        HandleCounterBorder();
    }
    GetHost()->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                      : PROPERTY_UPDATE_MEASURE);
}

std::u16string TextFieldPattern::GetLeftTextOfCursor(int32_t number)
{
    auto start = textEditingValue_.caretPosition;
    if (InSelectMode()) {
        start = std::min(textSelector_.GetStart(), textSelector_.GetEnd());
    }
    auto stringText = textEditingValue_.GetSelectedText(start - number, start);
    return StringUtils::Str8ToStr16(stringText);
}

std::u16string TextFieldPattern::GetRightTextOfCursor(int32_t number)
{
    auto end = textEditingValue_.caretPosition;
    if (InSelectMode()) {
        end = std::max(textSelector_.GetStart(), textSelector_.GetEnd());
    }
    auto stringText = textEditingValue_.GetSelectedText(end, end + number);
    return StringUtils::Str8ToStr16(stringText);
}

int32_t TextFieldPattern::GetTextIndexAtCursor()
{
    return textEditingValue_.caretPosition;
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
#ifndef NEW_SKIA
        static_cast<int32_t>(paragraph_->GetGlyphPositionAtCoordinateWithCluster(caretRect_.GetX(), newOffsetY).pos_);
#else
        static_cast<int32_t>(paragraph_->GetGlyphPositionAtCoordinate(caretRect_.GetX(), newOffsetY).pos_);
#endif
    UpdateSelection(textSelector_.GetStart(), textEditingValue_.caretPosition);
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
#ifndef NEW_SKIA
        static_cast<int32_t>(paragraph_->GetGlyphPositionAtCoordinateWithCluster(caretRect_.GetX(), newOffsetY).pos_);
#else
        static_cast<int32_t>(paragraph_->GetGlyphPositionAtCoordinate(caretRect_.GetX(), newOffsetY).pos_);
#endif
    UpdateSelection(textSelector_.GetStart(), textEditingValue_.caretPosition);
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
        UpdateSelection(textEditingValue_.caretPosition,
            std::max(textSelector_.baseOffset -
                         GetGraphemeClusterLength(GetEditingValue().GetWideText(), textSelector_.baseOffset, true),
                0));
        UpdateCaretPositionWithClamp(textSelector_.destinationOffset);
        selectionMode_ = SelectionMode::SELECT;
    } else {
        textSelector_.destinationOffset =
            std::max(textSelector_.destinationOffset - GetGraphemeClusterLength(GetEditingValue().GetWideText(),
                                                           textSelector_.destinationOffset, true),
                0);
        UpdateCaretPositionWithClamp(textSelector_.destinationOffset);
        if (textSelector_.destinationOffset == textSelector_.baseOffset) {
            selectionMode_ = SelectionMode::NONE;
        }
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionLeftWord()
{
    if (textEditingValue_.caretPosition == 0) {
        LOGW("Caret position at beginning, cannot update selection to left");
        return;
    }
    int32_t textLength = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    int32_t leftWordLength = GetWordLength(textEditingValue_.caretPosition, 0);
    if (leftWordLength < 0 || leftWordLength > textLength || textEditingValue_.caretPosition - leftWordLength < 0) {
        LOGD("Handle select a left word failed, the left word offset is out of range");
        return;
    }
    if (!InSelectMode()) {
        textSelector_.destinationOffset = textEditingValue_.caretPosition - leftWordLength;
        UpdateSelection(textEditingValue_.caretPosition, textSelector_.destinationOffset);
        UpdateCaretPositionWithClamp(textSelector_.destinationOffset);
        selectionMode_ = SelectionMode::SELECT;
    } else {
        textSelector_.destinationOffset = textEditingValue_.caretPosition - leftWordLength;
        UpdateCaretPositionWithClamp(textSelector_.destinationOffset);
        if (textSelector_.destinationOffset == textSelector_.baseOffset) {
            selectionMode_ = SelectionMode::NONE;
        }
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionLineBegin()
{
    if (textEditingValue_.caretPosition == 0) {
        LOGW("Caret position at beginning, cannot update selection to left");
        return;
    }
    int32_t textLength = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    int32_t lineBeginPosition = GetLineBeginPosition(textEditingValue_.caretPosition);
    if (lineBeginPosition < 0 || lineBeginPosition > textLength) {
        LOGD("Handle select line begin failed, the line begin offset is out of range");
        return;
    }
    if (!InSelectMode()) {
        textSelector_.destinationOffset = lineBeginPosition;
        UpdateSelection(textEditingValue_.caretPosition, textSelector_.destinationOffset);
        UpdateCaretPositionWithClamp(textSelector_.destinationOffset);
        selectionMode_ = SelectionMode::SELECT;
    } else {
        textSelector_.destinationOffset = lineBeginPosition;
        UpdateCaretPositionWithClamp(textSelector_.destinationOffset);
        if (textSelector_.destinationOffset == textSelector_.baseOffset) {
            selectionMode_ = SelectionMode::NONE;
        }
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionHome()
{
    if (textEditingValue_.caretPosition == 0) {
        LOGW("Caret position at beginning, cannot update selection to left");
        return;
    }
    if (!InSelectMode()) {
        textSelector_.destinationOffset = 0;
        UpdateSelection(textEditingValue_.caretPosition, textSelector_.destinationOffset);
        UpdateCaretPositionWithClamp(textSelector_.destinationOffset);
        selectionMode_ = SelectionMode::SELECT;
    } else {
        textSelector_.destinationOffset = 0;
        UpdateCaretPositionWithClamp(textSelector_.destinationOffset);
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
        UpdateSelection(textEditingValue_.caretPosition,
            std::min(textSelector_.baseOffset +
                         GetGraphemeClusterLength(GetEditingValue().GetWideText(), textSelector_.baseOffset),
                static_cast<int32_t>(textEditingValue_.GetWideText().length())));
        UpdateCaretPositionWithClamp(textSelector_.destinationOffset);
        selectionMode_ = SelectionMode::SELECT;
    } else {
        // if currently not in select mode, move destinationOffset and caret position only
        textSelector_.destinationOffset =
            std::min(textSelector_.destinationOffset +
                         GetGraphemeClusterLength(GetEditingValue().GetWideText(), textSelector_.destinationOffset),
                static_cast<int32_t>(textEditingValue_.GetWideText().length()));
        UpdateCaretPositionWithClamp(textSelector_.destinationOffset);
        if (textSelector_.destinationOffset == textSelector_.baseOffset) {
            selectionMode_ = SelectionMode::NONE;
        }
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionRightWord()
{
    int32_t textLength = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    if (textEditingValue_.caretPosition == textLength) {
        LOGW("Caret position at the end, cannot update selection to right");
        return;
    }
    int32_t rightWordLength = GetWordLength(textEditingValue_.caretPosition, 1);
    if (rightWordLength < 0 || rightWordLength > textLength ||
        rightWordLength + textEditingValue_.caretPosition > textLength) {
        LOGD("Handle select a right word failed, the right word offset is out of range");
        return;
    }
    if (!InSelectMode()) {
        textSelector_.destinationOffset = textEditingValue_.caretPosition + rightWordLength;
        UpdateSelection(textEditingValue_.caretPosition, textSelector_.destinationOffset);
        UpdateCaretPositionWithClamp(textSelector_.destinationOffset);
        selectionMode_ = SelectionMode::SELECT;
    } else {
        textSelector_.destinationOffset = textEditingValue_.caretPosition + rightWordLength;
        UpdateCaretPositionWithClamp(textSelector_.destinationOffset);
        if (textSelector_.destinationOffset == textSelector_.baseOffset) {
            selectionMode_ = SelectionMode::NONE;
        }
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionLineEnd()
{
    int32_t textLength = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    if (textEditingValue_.caretPosition == textLength) {
        LOGW("Caret position at the end, cannot update selection to right");
        return;
    }
    int32_t lineEndPosition = GetLineEndPosition(textEditingValue_.caretPosition);
    if (lineEndPosition < 0 || lineEndPosition > textLength) {
        LOGD("Handle select a line end failed, the line end offset is out of range");
        return;
    }
    if (!InSelectMode()) {
        textSelector_.destinationOffset = lineEndPosition;
        UpdateSelection(textEditingValue_.caretPosition, textSelector_.destinationOffset);
        UpdateCaretPositionWithClamp(textSelector_.destinationOffset);
        selectionMode_ = SelectionMode::SELECT;
    } else {
        textSelector_.destinationOffset = lineEndPosition;
        UpdateCaretPositionWithClamp(textSelector_.destinationOffset);
        if (textSelector_.destinationOffset == textSelector_.baseOffset) {
            selectionMode_ = SelectionMode::NONE;
        }
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionEnd()
{
    // shift end, select to the end of current line
    int32_t endPos = static_cast<int32_t>(textEditingValue_.GetWideText().length());
    if (textEditingValue_.caretPosition == endPos) {
        LOGW("Caret position at the end, cannot update selection to right");
        return;
    }
    if (!InSelectMode()) {
        textSelector_.destinationOffset = endPos;
        UpdateSelection(textEditingValue_.caretPosition, textSelector_.destinationOffset);
        UpdateCaretPositionWithClamp(textSelector_.destinationOffset);
        selectionMode_ = SelectionMode::SELECT;
    } else {
        textSelector_.destinationOffset = endPos;
        UpdateCaretPositionWithClamp(textSelector_.destinationOffset);
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

void TextFieldPattern::SetTextSelection(int32_t selectionStart, int32_t selectionEnd)
{
    selectionStart = selectionStart < 0 ? 0 : selectionStart;
    selectionEnd = std::clamp(selectionEnd, 0, static_cast<int32_t>(textEditingValue_.GetWideText().length()));
    if (selectionStart > selectionEnd) {
        selectionStart = selectionEnd;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto instanceId = GetInstanceId();
    ContainerScope scope(instanceId);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto task = [weak = WeakClaim(this), selectionStart, selectionEnd] {
        auto client = AceType::DynamicCast<TextFieldPattern>(weak.Upgrade());
        if (!client) {
            LOGE("text field is null");
            return;
        }
        ContainerScope scope(client->GetInstanceId());
        client->HandleSetSelection(selectionStart, selectionEnd);
        if (selectionStart == selectionEnd) {
            client->SetInSelectMode(SelectionMode::NONE);
            client->StartTwinkling();
        } else {
            client->SetInSelectMode(SelectionMode::SELECT);
            client->StopTwinkling();
        }
        client->isUsingMouse_ = false;
        client->SetCaretUpdateType(CaretUpdateType::EVENT);
        client->CloseSelectOverlay();
        client->MarkRedrawOverlay();
        if (client->RequestKeyboard(false, true, true)) {
            auto textFieldFrameNode = client->GetHost();
            CHECK_NULL_VOID(textFieldFrameNode);
            auto eventHub = textFieldFrameNode->GetEventHub<TextFieldEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->FireOnEditChanged(true);
        }
    };
    taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
}

void TextFieldPattern::SetSelectionFlag(int32_t selectionStart, int32_t selectionEnd)
{
    if (!HasFocus()) {
        return;
    }
    setSelectionFlag_ = true;
    cursorVisible_ = false;
    MarkRedrawOverlay();
    selectionStart_ = selectionStart;
    selectionEnd_ = selectionEnd;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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

bool TextFieldPattern::OnBackPressed()
{
    LOGI("Textfield %{public}d receives back press event", GetHost()->GetId());
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (!imeAttached_ || (imeAttached_ && !imeShown_)) {
        LOGI("Ime is not attached or is hidden, return for not consuming the back press event");
        return false;
    }
#endif
    LOGI("Closing keyboard on back press");
    CloseKeyboard(true);
#if defined(ANDROID_PLATFORM)
    return false;
#else
    return true;
#endif
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

std::string TextFieldPattern::GetShowPasswordIconString() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "false");
    return layoutProperty->GetShowPasswordIconValue(false) ? "true" : "false";
}

std::string TextFieldPattern::GetInputStyleString() const
{
    std::string result = isTextInput_ ? "TextInputStyle.Default" : "TextContentStyle.DEFAULT";
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, result);
    switch (paintProperty->GetInputStyleValue(InputStyle::DEFAULT)) {
        case InputStyle::INLINE:
            result = isTextInput_ ? "TextInputStyle.Inline" : "TextContentStyle.INLINE";
            break;
        case InputStyle::DEFAULT:
        default:
            break;
    }
    return result;
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

uint32_t TextFieldPattern::GetMaxLines() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, Infinity<uint32_t>());
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, Infinity<uint32_t>());
    if (paintProperty->GetInputStyleValue(InputStyle::DEFAULT) == InputStyle::INLINE) {
        return layoutProperty->GetMaxViewLinesValue(INLINE_DEFAULT_VIEW_MAXLINE);
    }
    return layoutProperty->HasMaxLines() ? layoutProperty->GetMaxLinesValue(Infinity<uint32_t>())
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

std::string TextFieldPattern::GetErrorTextString() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return layoutProperty->GetErrorTextValue("");
}

bool TextFieldPattern::GetErrorTextState() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetShowErrorTextValue(false);
}

bool TextFieldPattern::IsSearchParentNode() const
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

std::string TextFieldPattern::GetCopyOptionString() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    std::string copyOptionString = "CopyOptions.None";
    switch (layoutProperty->GetCopyOptionsValue(CopyOptions::None)) {
        case CopyOptions::InApp:
            copyOptionString = "CopyOptions.InApp";
            break;
        case CopyOptions::Local:
            copyOptionString = "CopyOptions.Local";
            break;
        case CopyOptions::Distributed:
            copyOptionString = "CopyOptions.Distributed";
            break;
        case CopyOptions::None:
        default:
            break;
    }
    return copyOptionString;
}

std::string TextFieldPattern::GetBarStateString() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    std::string displayModeString;
    switch (layoutProperty->GetDisplayModeValue(DisplayMode::AUTO)) {
        case DisplayMode::OFF:
            displayModeString = "BarState.OFF";
            break;
        case DisplayMode::ON:
            displayModeString = "BarState.ON";
            break;
        case DisplayMode::AUTO:
        default:
            displayModeString = "BarState.AUTO";
            break;
    }
    return displayModeString;
}

void TextFieldPattern::UpdateScrollBarOffset()
{
    if (textEditingValue_.text.empty()) {
        return;
    }
    if (!GetScrollBar() && !GetScrollBarProxy()) {
        return;
    }
    auto paddingHeight = GetPaddingTop() + GetPaddingBottom();
    Size size(contentRect_.Width() + GetPaddingRight(), contentRect_.Height() + paddingHeight);
    UpdateScrollBarRegion(
        contentRect_.GetY() - textRect_.GetY(), textRect_.Height() + paddingHeight, size, Offset(0.0, 0.0));
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool TextFieldPattern::OnScrollCallback(float offset, int32_t source)
{
    if (source == SCROLL_FROM_START) {
        return true;
    }
    OnTextInputScroll(offset);
    OnTextAreaScroll(offset);
    auto selectOverlayProxy = GetSelectOverlay();
    CHECK_NULL_RETURN_NOLOG(selectOverlayProxy, true);
    selectOverlayProxy->ShowOrHiddenMenu(true);
    return true;
}

void TextFieldPattern::CheckScrollable()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    if (textEditingValue_.text.empty()) {
        scrollable_ = false;
    } else {
        if (layoutProperty->GetShowCounterValue(false) && counterParagraph_) {
            scrollable_ = GreatNotEqual(textRect_.Height(), contentRect_.Height() - counterParagraph_->GetHeight());
        } else {
            scrollable_ = GreatNotEqual(textRect_.Height(), contentRect_.Height());
        }
    }
    SetScrollEnable(scrollable_);
}

bool TextFieldPattern::HasStateStyle(UIState state) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(hub, false);
    return hub->HasStateStyle(state);
}

double TextFieldPattern::GetScrollBarWidth()
{
    auto scrollBar = GetScrollBar();
    double scrollBarWidth = 0.0;
    if (scrollBar) {
        scrollBarWidth = scrollBar->GetBarRect().Width();
    }
    return scrollBarWidth;
}

void TextFieldPattern::SetUnitNode(const RefPtr<NG::UINode>& unitNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(unitNode);
    if (host->GetChildren().size() != 0) {
        host->Clean();
    }
    unitNode->MountToParent(host);
}

void TextFieldPattern::SetShowError()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto passWordMode =
        layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::VISIBLE_PASSWORD;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto renderContext = GetHost()->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto visible = layoutProperty->GetShowErrorTextValue(false);

    if (visible && layoutProperty->GetShowUnderlineValue(false)) {
        underlineColor_ = textFieldTheme->GetErrorUnderlineColor();
        underlineWidth_ = ERROR_UNDERLINE_WIDTH;
    }
    if (!visible && layoutProperty->GetShowUnderlineValue(false)) {
        underlineColor_ = textFieldTheme->GetUnderlineColor();
        underlineWidth_ = UNDERLINE_WIDTH;
    }

    if (visible && passWordMode) {
        BorderWidthProperty borderWidth;
        BorderColorProperty borderColor;
        borderWidth.SetBorderWidth(ERROR_BORDER_WIDTH);
        layoutProperty->UpdateBorderWidth(borderWidth);
        borderColor.SetColor(textFieldTheme->GetPasswordErrorBorderColor());
        renderContext->UpdateBorderColor(borderColor);
        layoutProperty->UpdatePadding({ CalcLength(0.0), CalcLength(0.0), CalcLength(0.0), CalcLength(0.0) });
        renderContext->UpdateBackgroundColor(textFieldTheme->GetPasswordErrorInputColor());
        layoutProperty->UpdateTextColor(textFieldTheme->GetPasswordErrorTextColor());
    }
    if (!visible && passWordMode) {
        layoutProperty->UpdateBorderWidth(passwordModeStyle_.borderwidth);
        renderContext->UpdateBorderColor(passwordModeStyle_.borderColor);
        layoutProperty->UpdatePadding(passwordModeStyle_.padding);
        renderContext->UpdateBackgroundColor(passwordModeStyle_.bgColor);
        layoutProperty->UpdateTextColor(passwordModeStyle_.textColor);
        underlineColor_ = textFieldTheme->GetUnderlineColor();
        underlineWidth_ = UNDERLINE_WIDTH;
    }
}

void TextFieldPattern::SavePasswordModeStates()
{
    auto renderContext = GetHost()->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    bool passWordMode =
        layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::VISIBLE_PASSWORD;
    if (!passWordMode) {
        return;
    }
    passwordModeStyle_.bgColor = renderContext->GetBackgroundColor().value_or(textFieldTheme->GetBgColor());
    passwordModeStyle_.textColor = layoutProperty->GetTextColorValue(textFieldTheme->GetTextColor());
    if (layoutProperty->GetBorderWidthProperty() != nullptr) {
        passwordModeStyle_.borderwidth = *(layoutProperty->GetBorderWidthProperty());
    } else {
        BorderWidthProperty borderWidth;
        borderWidth.SetBorderWidth(BORDER_DEFAULT_WIDTH);
        passwordModeStyle_.borderwidth = borderWidth;
    }
    BorderColorProperty borderColor;
    borderColor.SetColor(Color::TRANSPARENT);
    passwordModeStyle_.borderColor = renderContext->GetBorderColor().value_or(borderColor);
    auto radius = textFieldTheme->GetBorderRadius();
    BorderRadiusProperty borderRadius { radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() };
    passwordModeStyle_.radius = renderContext->GetBorderRadius().value_or(borderRadius);

    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    if (paddingProperty) {
        passwordModeStyle_.padding.left = CalcLength(paddingProperty->left->GetDimension().ConvertToPx());
        passwordModeStyle_.padding.top = CalcLength(paddingProperty->top->GetDimension().ConvertToPx());
        passwordModeStyle_.padding.bottom = CalcLength(paddingProperty->bottom->GetDimension().ConvertToPx());
        passwordModeStyle_.padding.right = CalcLength(paddingProperty->right->GetDimension().ConvertToPx());
    } else {
        passwordModeStyle_.padding.left = CalcLength(0.0);
        passwordModeStyle_.padding.top = CalcLength(0.0);
        passwordModeStyle_.padding.bottom = CalcLength(0.0);
        passwordModeStyle_.padding.right = CalcLength(0.0);
    }
}

void TextFieldPattern::SaveUnderlineStates()
{
    auto renderContext = GetHost()->GetRenderContext();
    Radius radius;
    BorderRadiusProperty borderRadius { radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() };
    borderRadius_ = renderContext->GetBorderRadius().value_or(borderRadius);
}

float TextFieldPattern::GetMarginBottom() const
{
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0.0f);
    auto& getMargin = layoutProperty->GetMarginProperty();
    if (getMargin && getMargin->bottom.has_value()) {
        return getMargin->bottom->GetDimension().ConvertToPx();
    }
    return 0.0f;
}

std::string TextFieldPattern::GetShowResultImageSrc() const
{
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    if (showUserDefinedIcon_ && layoutProperty->HasShowPasswordSourceInfo()) {
        return layoutProperty->GetShowPasswordSourceInfo()->GetSrc();
    }
    return SHOW_PASSWORD_SVG;
}

std::string TextFieldPattern::GetHideResultImageSrc() const
{
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    if (hideUserDefinedIcon_ && layoutProperty->HasHidePasswordSourceInfo()) {
        return layoutProperty->GetHidePasswordSourceInfo()->GetSrc();
    }
    return HIDE_PASSWORD_SVG;
}

void TextFieldPattern::SaveInlineStates()
{
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto renderContext = GetHost()->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
    inlineState_.textColor = layoutProperty->GetTextColorValue(theme->GetTextColor());
    inlineState_.bgColor = renderContext->GetBackgroundColor().value_or(theme->GetBgColor());
    auto radius = theme->GetBorderRadius();
    BorderRadiusProperty borderRadius { radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() };
    inlineState_.radius = renderContext->GetBorderRadius().value_or(borderRadius);
    if (layoutProperty->GetBorderWidthProperty() != nullptr) {
        inlineState_.borderWidth = *(layoutProperty->GetBorderWidthProperty());
    } else {
        inlineState_.borderWidth.SetBorderWidth(BORDER_DEFAULT_WIDTH);
    }
    if (renderContext->HasBorderColor()) {
        inlineState_.borderColor = renderContext->GetBorderColor().value();
    }
    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    if (paddingProperty) {
        inlineState_.padding.left = CalcLength(paddingProperty->left->GetDimension().ConvertToPx());
        inlineState_.padding.top = CalcLength(paddingProperty->top->GetDimension().ConvertToPx());
        inlineState_.padding.bottom = CalcLength(paddingProperty->bottom->GetDimension().ConvertToPx());
        inlineState_.padding.right = CalcLength(paddingProperty->right->GetDimension().ConvertToPx());
    } else {
        inlineState_.padding.left = CalcLength(0.0_vp);
        inlineState_.padding.top = CalcLength(0.0_vp);
        inlineState_.padding.bottom = CalcLength(0.0_vp);
        inlineState_.padding.right = CalcLength(0.0_vp);
    }
    const auto& marginProperty = layoutProperty->GetMarginProperty();
    if (marginProperty) {
        inlineState_.margin.left = CalcLength(marginProperty->left->GetDimension().ConvertToPx());
        inlineState_.margin.top = CalcLength(marginProperty->top->GetDimension().ConvertToPx());
        inlineState_.margin.bottom = CalcLength(marginProperty->bottom->GetDimension().ConvertToPx());
        inlineState_.margin.right = CalcLength(marginProperty->right->GetDimension().ConvertToPx());
    } else {
        inlineState_.margin.left = CalcLength(0.0_vp);
        inlineState_.margin.top = CalcLength(0.0_vp);
        inlineState_.margin.bottom = CalcLength(0.0_vp);
        inlineState_.margin.right = CalcLength(0.0_vp);
    }
}

void TextFieldPattern::ApplyInlineStates(bool focusStatus)
{
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto renderContext = GetHost()->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    layoutProperty->UpdateTextColor(theme->GetInlineTextColor());
    auto radius = theme->GetInlineRadiusSize();
    renderContext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
    renderContext->UpdateBackgroundColor(theme->GetInlineBgColor());
    BorderWidthProperty inlineBorderWidth;
    inlineBorderWidth.SetBorderWidth(INLINE_BORDER_WIDTH);
    layoutProperty->UpdateBorderWidth(inlineBorderWidth);
    renderContext->UpdateBorderWidth(inlineBorderWidth);
    BorderColorProperty inlineBorderColor;
    inlineBorderColor.SetColor(theme->GetInlineBorderColor());
    renderContext->UpdateBorderColor(inlineBorderColor);
    auto padding = theme->GetInlineBorderWidth();
    layoutProperty->UpdatePadding(
        { CalcLength(padding), CalcLength(padding), CalcLength(padding), CalcLength(padding) });
    ProcessInnerPadding();
    textRect_.SetOffset(OffsetF(GetPaddingLeft(), GetPaddingTop()));
    MarginProperty margin;
    margin.bottom =
        CalcLength(inlineState_.padding.bottom->GetDimension() + inlineState_.margin.bottom->GetDimension());
    margin.right = CalcLength(inlineState_.padding.right->GetDimension() + inlineState_.margin.right->GetDimension());
    margin.left = CalcLength(inlineState_.padding.left->GetDimension() + inlineState_.margin.left->GetDimension());
    margin.top = CalcLength(inlineState_.padding.top->GetDimension() + inlineState_.margin.top->GetDimension());
    layoutProperty->UpdateMargin(margin);
    CalcSize idealSize;
    inlinePadding_ = padding.ConvertToPx() + padding.ConvertToPx();
    if (focusStatus) {
        previewWidth_ = paragraph_->GetLongestLine() + inlinePadding_;
        std::optional<CalcLength> width(previewWidth_);
        idealSize.SetWidth(width);
    } else {
        std::optional<CalcLength> width(previewWidth_);
        idealSize.SetWidth(width);
    }
    layoutProperty->UpdateUserDefinedIdealSize(idealSize);
    auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (layoutConstraint && layoutConstraint->selfIdealSize && layoutConstraint->selfIdealSize->Height()) {
        layoutProperty->ClearUserDefinedIdealSize(false, true);
        inlineState_.setHeight = true;
    }
    if (!IsTextArea()) {
        layoutProperty->ResetMaxLines();
    }
}

void TextFieldPattern::RestorePreInlineStates()
{
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto renderContext = GetHost()->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    layoutProperty->UpdateTextColor(inlineState_.textColor);
    auto radius = theme->GetInlineRadiusSize();
    renderContext->UpdateBorderRadius(inlineState_.radius);
    renderContext->UpdateBackgroundColor(inlineState_.bgColor);
    layoutProperty->UpdateBorderWidth(inlineState_.borderWidth);
    renderContext->UpdateBorderWidth(inlineState_.borderWidth);
    renderContext->UpdateBorderColor(inlineState_.borderColor);
    layoutProperty->UpdatePadding(inlineState_.padding);
    ProcessInnerPadding();
    inlinePadding_ = 0.0f;
    textRect_.SetOffset(OffsetF(GetPaddingLeft(), GetPaddingTop()));
    layoutProperty->UpdateMargin(inlineState_.margin);
    CalcSize idealSize;
    std::optional<CalcLength> width(inlineState_.frameRect.Width());
    idealSize.SetWidth(width);
    if (inlineState_.setHeight) {
        std::optional<CalcLength> height(inlineState_.frameRect.Height());
        idealSize.SetHeight(height);
    }
    layoutProperty->UpdateUserDefinedIdealSize(idealSize);
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
    json->Put("copyOption", GetCopyOptionString().c_str());
    json->Put("style", GetInputStyleString().c_str());
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("onIconSrc", GetShowResultImageSrc().c_str());
    jsonValue->Put("offIconSrc", GetHideResultImageSrc().c_str());
    json->Put("passwordIcon", jsonValue->ToString().c_str());
    json->Put("showError", GetErrorTextState() ? GetErrorTextString().c_str() : "undefined");
    auto maxLines = GetMaxLines();
    json->Put("maxLines", GreatOrEqual(maxLines, Infinity<uint32_t>()) ? "INF" : std::to_string(maxLines).c_str());
    json->Put("barState", GetBarStateString().c_str());
}

void TextFieldPattern::FromJson(const std::unique_ptr<JsonValue>& json)
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdatePlaceholder(json->GetString("placeholder"));
    UpdateEditingValue(json->GetString("text"), StringUtils::StringToInt(json->GetString("caretPosition")));
    SetEditingValueToProperty(textEditingValue_.text);
    UpdateSelection(textEditingValue_.caretPosition);
    auto maxLines = json->GetString("maxLines");
    if (!maxLines.empty() && maxLines != "INF") {
        layoutProperty->UpdateMaxLines(StringUtils::StringToUint(maxLines));
    }
    static const std::unordered_map<std::string, CopyOptions> uMap = {
        { "CopyOptions.None", CopyOptions::None },
        { "CopyOptions.InApp", CopyOptions::InApp },
        { "CopyOptions.Local", CopyOptions::Local },
        { "CopyOptions.Distributed", CopyOptions::Distributed },
    };
    auto copyOption = json->GetString("copyOption");
    layoutProperty->UpdateCopyOptions(uMap.count(copyOption) ? uMap.at(copyOption) : CopyOptions::None);
    Pattern::FromJson(json);
}

void TextFieldPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionSetText([weakPtr = WeakClaim(this)](const std::string& value) {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->InsertValue(value);
    });

    accessibilityProperty->SetActionSetSelection([weakPtr = WeakClaim(this)](int32_t start, int32_t end) {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetSelectionFlag(start, end);
    });

    accessibilityProperty->SetActionCopy([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->AllowCopy()) {
            pattern->HandleOnCopy();
            pattern->CloseSelectOverlay();
        }
    });

    accessibilityProperty->SetActionCut([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->AllowCopy()) {
            pattern->HandleOnCut();
            pattern->CloseSelectOverlay();
        }
    });

    accessibilityProperty->SetActionPaste([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleOnPaste();
        pattern->CloseSelectOverlay();
    });

    accessibilityProperty->SetActionClearSelection([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto current = pattern->GetTextSelector().GetEnd();
        pattern->SetInSelectMode(SelectionMode::NONE);
        pattern->UpdateSelection(current);
        pattern->SetSelectionFlag(current, current);
        pattern->CloseSelectOverlay();
        pattern->StartTwinkling();
    });
    SetAccessibilityScrollAction();
    SetAccessibilityMoveTextAction();
}

void TextFieldPattern::SetAccessibilityMoveTextAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionMoveText([weakPtr = WeakClaim(this)](int32_t moveUnit, bool forward) {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        if (pattern->GetEditingValue().GetWideText().empty()) {
            return;
        }
        int range = 0;
        if (moveUnit == 1) {
            range = 1;
        }
        auto caretPosition = forward ? pattern->textEditingValue_.caretPosition + range
                                     : pattern->textEditingValue_.caretPosition - range;
        auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
        layoutProperty->UpdateCaretPosition(caretPosition);
        pattern->SetCaretPosition(caretPosition);
        pattern->UpdateCaretPositionByTextEdit();
    });
}

void TextFieldPattern::SetAccessibilityScrollAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->IsScrollable()) {
            auto frameNode = pattern->GetHost();
            CHECK_NULL_VOID(frameNode);
            auto offset = pattern->GetTextContentRect().Height();
            float scrollDistance =
                pattern->GetTextRect().Height() - (std::abs((pattern->GetTextRect().GetY() - offset)));
            if (offset > scrollDistance) {
                pattern->OnTextAreaScroll(-scrollDistance);
                frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
                return;
            }
            pattern->OnTextAreaScroll(-offset);
            frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
        }
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->IsScrollable()) {
            auto frameNode = pattern->GetHost();
            CHECK_NULL_VOID(frameNode);
            auto offset = pattern->GetTextContentRect().Height();
            float scrollDistance = std::abs(pattern->GetTextRect().GetY() - pattern->GetTextContentRect().GetY());
            if (offset > scrollDistance) {
                pattern->OnTextAreaScroll(scrollDistance);
                frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
                return;
            }
            pattern->OnTextAreaScroll(offset);
            frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
        }
    });
}

void TextFieldPattern::CheckHandles(std::optional<RectF>& firstHandle, std::optional<RectF>& secondHandle,
    float firstHandleSize, float secondHandleSize)
{
    auto firstHandleOffset = textSelector_.firstHandleOffset_ - parentGlobalOffset_;
    if (!contentRect_.IsInRegion(
            { firstHandleOffset.GetX(), firstHandleOffset.GetY() + BOX_EPSILON + firstHandleSize })) {
        // hide firstHandle when it's out of content region
        firstHandle = std::nullopt;
    }
    auto secondHandleOffset = textSelector_.secondHandleOffset_ - parentGlobalOffset_;
    if (!contentRect_.IsInRegion(
            { secondHandleOffset.GetX(), secondHandleOffset.GetY() + BOX_EPSILON + secondHandleSize })) {
        // hide secondHandle when it's out of content region
        secondHandle = std::nullopt;
    }
    LOGD("firstHandleOffset %{public}s, secondHandleOffset %{public}s contentRect: %{public}s",
        firstHandleOffset.ToString().c_str(), secondHandleOffset.ToString().c_str(), contentRect_.ToString().c_str());
}

void TextFieldPattern::StopEditing()
{
    LOGI("TextFieldPattern: StopEditing");
    if (!HasFocus()) {
        return;
    }
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (GetImeAttached()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto eventHub = host->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnEditChanged(false);
    }
#endif
    HandleSetSelection(textEditingValue_.caretPosition, textEditingValue_.caretPosition);
    StopTwinkling();
    MarkRedrawOverlay();
    CloseSelectOverlay();
    CloseKeyboard(true);
}
} // namespace OHOS::Ace::NG
