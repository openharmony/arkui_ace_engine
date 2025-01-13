/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/text_field/text_select_controller.h"

#include "base/geometry/ng/rect_t.h"
#include "base/geometry/offset.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utf_helper.h"
#include "base/utils/utils.h"
#include "core/common/ai/data_detector_mgr.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text_field/text_input_ai_checker.h"

namespace OHOS::Ace::NG {
namespace {
const std::string NEWLINE = "\n";
const std::u16string WIDE_NEWLINE = UtfUtils::Str8DebugToStr16(NEWLINE);
} // namespace
void TextSelectController::UpdateHandleIndex(int32_t firstHandleIndex, int32_t secondHandleIndex)
{
    firstHandleInfo_.index = firstHandleIndex;
    secondHandleInfo_.index = secondHandleIndex;
    caretInfo_.index = std::max(firstHandleInfo_.index, secondHandleInfo_.index);
    CalculateHandleOffset();
    UpdateCaretOffset();
}

void TextSelectController::UpdateCaretIndex(int32_t index)
{
    auto newIndex = std::clamp(index, 0, static_cast<int32_t>(contentController_->GetTextUtf16Value().length()));
    caretInfo_.index = newIndex;
    TAG_LOGD(AceLogTag::ACE_TEXT_FIELD, "newIndex change to %{public}d", newIndex);
    firstHandleInfo_.index = newIndex;
    secondHandleInfo_.index = newIndex;
}

RectF TextSelectController::CalculateEmptyValueCaretRect(float width)
{
    RectF rect;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, rect);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textField, rect);
    auto layoutProperty = textField->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, rect);
    rect.SetOffset(contentRect_.GetOffset());
    rect.SetHeight(textField->PreferredLineHeight());
    rect.SetWidth(GreatNotEqual(width, 0.0f) ? width : caretInfo_.rect.Width());
    auto textAlign = layoutProperty->GetTextAlignValue(TextAlign::START);
    auto direction = layoutProperty->GetNonAutoLayoutDirection();
    textField->CheckTextAlignByDirection(textAlign, direction);

    switch (textAlign) {
        case TextAlign::START:
            rect.SetLeft(contentRect_.GetX());
            break;
        case TextAlign::CENTER:
            if (layoutProperty->GetPlaceholderValue(u"").empty() || !paragraph_) {
                rect.SetLeft(static_cast<float>(contentRect_.GetX()) + contentRect_.Width() / 2.0f);
            } else {
                CaretMetricsF caretMetrics;
                CalcCaretMetricsByPosition(0, caretMetrics, TextAffinity::DOWNSTREAM);
                rect.SetLeft(caretMetrics.offset.GetX());
            }
            break;
        case TextAlign::END:
            rect.SetLeft(static_cast<float>(contentRect_.GetX()) + contentRect_.Width() -
                         static_cast<float>(rect.Width()));
            break;
        default:
            break;
    }

    auto align = textField->IsTextArea() ? Alignment::TOP_CENTER : Alignment::CENTER;
    if (layoutProperty->GetPositionProperty()) {
        align = layoutProperty->GetPositionProperty()->GetAlignment().value_or(align);
    }
    OffsetF offset = Alignment::GetAlignPosition(contentRect_.GetSize(), rect.GetSize(), align);
    rect.SetTop(offset.GetY() + contentRect_.GetY());
    if (textAlign != TextAlign::END) {
        AdjustHandleAtEdge(rect);
    }
    return rect;
}

void TextSelectController::FitCaretMetricsToTouchPoint(CaretMetricsF& caretMetrics, const Offset& touchOffset)
{
    auto index = ConvertTouchOffsetToPosition(touchOffset);
    // adust Y to align in one line center.
    AdjustCursorPosition(index, touchOffset);
    CalcCaretMetricsByPositionNearTouchOffset(index, caretMetrics,
        OffsetF(static_cast<float>(touchOffset.GetX()), static_cast<float>(touchOffset.GetY())));

    // ajust X to support display caret at anywhere
    caretMetrics.offset.SetX(touchOffset.GetX());
}

void TextSelectController::FitCaretMetricsToContentRect(CaretMetricsF& caretMetrics)
{
    if (GreatNotEqual(caretMetrics.height, contentRect_.Height())) {
        caretMetrics.offset.SetY(caretMetrics.offset.GetY() + caretMetrics.height - contentRect_.Height());
        caretMetrics.height = contentRect_.Height();
    }
}

void TextSelectController::CalcCaretMetricsByPosition(
    int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity)
{
    CHECK_NULL_VOID(paragraph_);
    paragraph_->CalcCaretMetricsByPosition(extent, caretCaretMetric, textAffinity);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    auto textRect = textField->GetTextRect();
    caretCaretMetric.offset.AddX(textRect.GetX());
    caretCaretMetric.offset.AddY(textRect.GetY());
    FitCaretMetricsToContentRect(caretCaretMetric);
}

void TextSelectController::CalcCaretMetricsByPositionNearTouchOffset(
    int32_t extent, CaretMetricsF& caretMetrics, const OffsetF& touchOffset)
{
    CHECK_NULL_VOID(paragraph_);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    auto textRect = textField->GetTextRect();
    paragraph_->CalcCaretMetricsByPosition(extent, caretMetrics, touchOffset - textRect.GetOffset(), textAffinity_);
    caretMetrics.offset.AddX(textRect.GetX());
    caretMetrics.offset.AddY(textRect.GetY());
    FitCaretMetricsToContentRect(caretMetrics);
}

void TextSelectController::UpdateCaretRectByPositionNearTouchOffset(int32_t position, const Offset& touchOffset)
{
    CaretMetricsF caretMetrics;
    CalcCaretMetricsByPositionNearTouchOffset(position, caretMetrics,
        OffsetF(static_cast<float>(touchOffset.GetX()), static_cast<float>(touchOffset.GetY())));

    caretInfo_.UpdateOffset(caretMetrics.offset);
    UpdateCaretHeight(caretMetrics.height);
}

void TextSelectController::UpdateCaretInfoByOffset(const Offset& localOffset, bool moveContent, bool floatCaret)
{
    auto index = ConvertTouchOffsetToPosition(localOffset);
    AdjustCursorPosition(index, localOffset);
    UpdateCaretIndex(index);
    if (!contentController_->IsEmpty()) {
        UpdateCaretRectByPositionNearTouchOffset(index, localOffset);
        auto offset = caretInfo_.rect.GetOffset();
        if (moveContent) {
            MoveHandleToContentRect(caretInfo_.rect, 0.0f);
        } else {
            AdjustHandleAtEdge(caretInfo_.rect);
        }
        UpdateCaretOriginalRect(offset);
    } else {
        SetCaretRectAtEmptyValue();
    }

    CHECK_NULL_VOID(floatCaret);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    textField->AdjustFloatingCaretInfo(localOffset, caretInfo_, floatingCaretInfo_);
}

OffsetF TextSelectController::CalcCaretOffsetByOffset(const Offset& localOffset)
{
    auto index = ConvertTouchOffsetToPosition(localOffset);
    AdjustCursorPosition(index, localOffset);
    if (!contentController_->IsEmpty()) {
        CaretMetricsF caretMetrics;
        CalcCaretMetricsByPositionNearTouchOffset(index, caretMetrics,
            OffsetF(static_cast<float>(localOffset.GetX()), static_cast<float>(localOffset.GetY())));
        return caretMetrics.offset;
    } else {
        return CalculateEmptyValueCaretRect().GetOffset();
    }
}

int32_t TextSelectController::ConvertTouchOffsetToPosition(const Offset& localOffset, bool isSelectionPos) const
{
    CHECK_NULL_RETURN(paragraph_, 0);
    if (contentController_->IsEmpty()) {
        return 0;
    }
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, 0);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textField, 0);
    auto textRect = textField->GetTextRect();
    auto offset = localOffset - Offset(textRect.GetX(), textRect.GetY());
    return paragraph_->GetGlyphIndexByCoordinate(offset, isSelectionPos);
}

void TextSelectController::UpdateSelectByOffset(const Offset& localOffset)
{
    CHECK_NULL_VOID(paragraph_ && !contentController_->IsEmpty());
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    auto textRect = textField->GetTextRect();
    auto contentRect = textField->GetTextContentRect();
    auto touchLocalOffset = localOffset;
    if (textField->IsTextArea() && GreatNotEqual(touchLocalOffset.GetY(), textRect.Bottom())) {
        // click at end of a paragraph.
        touchLocalOffset.SetX(textField->IsLTRLayout() ? contentRect.Right() : textRect.Left());
    }

    auto range = GetSelectRangeByOffset(touchLocalOffset);
    int32_t start = range.first;
    int32_t end = range.second;
    UpdateHandleIndex(start, end);
    if (IsSelected()) {
        MoveFirstHandleToContentRect(GetFirstHandleIndex());
        MoveSecondHandleToContentRect(GetSecondHandleIndex());
    } else {
        MoveCaretToContentRect(GetCaretIndex());
    }
}

void TextSelectController::UpdateSelectPragraphByOffset(const Offset& localOffset)
{
    CHECK_NULL_VOID(paragraph_ && !contentController_->IsEmpty());

    auto range = GetSelectParagraphByOffset(localOffset);
    int32_t start = range.first;
    int32_t end = range.second;
    UpdateHandleIndex(start, end);
    if (IsSelected()) {
        MoveFirstHandleToContentRect(GetFirstHandleIndex());
        MoveSecondHandleToContentRect(GetSecondHandleIndex());
    } else {
        MoveCaretToContentRect(GetCaretIndex());
    }
}

std::pair<int32_t, int32_t> TextSelectController::GetSelectRangeByOffset(const Offset& localOffset)
{
    std::pair<int32_t, int32_t> err(-1, -1);
    CHECK_NULL_RETURN(paragraph_ && !contentController_->IsEmpty(), err);
    int32_t start = 0;
    int32_t end = 0;
    auto pos = ConvertTouchOffsetToPosition(localOffset, true);
    // Ensure that the end is selected.
    if (pos >= static_cast<int32_t>(paragraph_->GetParagraphText().length())) {
        pos -= 1;
    }

    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, err);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textField, err);
    bool smartSelect = false;
    if (!textField->IsUsingMouse()) {
        smartSelect = AdjustWordSelection(pos, start, end, localOffset);
    }

    if (!smartSelect && !paragraph_->GetWordBoundary(pos, start, end)) {
        start = pos;
        end = std::min(static_cast<int32_t>(contentController_->GetTextUtf16Value().length()),
            pos + GetGraphemeClusterLength(contentController_->GetTextUtf16Value(), pos, true));
    }
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_TEXT,
            "current word position = %{public}d, select position {start:%{public}d, end:%{public}d}", pos, start, end);
    }
    return { start, end };
}

std::pair<int32_t, int32_t> TextSelectController::GetSelectParagraphByOffset(const Offset& localOffset)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
    std::pair<int32_t, int32_t> err(-1, -1);
    CHECK_NULL_RETURN(paragraph_ && !contentController_->IsEmpty(), err);
    int32_t start = 0;
    int32_t end = 0;
    auto pos = ConvertTouchOffsetToPosition(localOffset, true);
    // Ensure that the end is selected.
    if (pos >= static_cast<int32_t>(paragraph_->GetParagraphText().length())) {
        pos -= 1;
    }

    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, err);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textField, err);
    bool smartSelect = false;
    if (!textField->IsUsingMouse()) {
        smartSelect = AdjustWordSelection(pos, start, end, localOffset);
    }

    GetSubParagraphByOffset(pos, start, end);

    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_TEXT,
            "current word position = %{public}d, select position {start:%{public}d, end:%{public}d}", pos, start, end);
    }
    return { start, end };
}

void TextSelectController::GetSubParagraphByOffset(int32_t pos, int32_t &start, int32_t &end)
{
    auto data = contentController_->GetTextUtf16Value();
    auto dataLen = static_cast<int32_t>(data.length());
    bool leftContinue = true;
    bool rightContinue = true;
    int32_t offset = 0;
    if (pos <= 0) {
        leftContinue = false;
        start = 0;
    }
    while (leftContinue || rightContinue) {
        if (leftContinue) {
            if (pos - offset < 0 || data[pos - offset] == WIDE_NEWLINE[0]) {
                start = pos - offset + 1;
                leftContinue = false;
            }
        }
        if (rightContinue) {
            if (pos + offset >= dataLen || data[pos + offset] == WIDE_NEWLINE[0]) {
                end = pos + offset;
                rightContinue = false;
            }
        }
        ++offset;
    }
}

int32_t TextSelectController::GetGraphemeClusterLength(const std::u16string& text, int32_t extend, bool checkPrev)
{
    char16_t aroundChar = 0;
    if (static_cast<size_t>(extend) <= text.length()) {
        if (checkPrev) {
            aroundChar = text[std::max(0, extend - 1)];
        } else {
            aroundChar = text[std::min(static_cast<int32_t>(text.length() - 1), extend)];
        }
    }
    return StringUtils::NotInUtf16Bmp(aroundChar) ? 2 : 1;
}

void TextSelectController::CalculateHandleOffset()
{
    // calculate firstHandleOffset, secondHandleOffset and handlePaintSize
    if (contentController_->IsEmpty()) {
        SetCaretRectAtEmptyValue();
        return;
    }
    CaretMetricsF secondHandleMetrics;
    CalcCaretMetricsByPosition(GetSecondHandleIndex(), secondHandleMetrics, TextAffinity::UPSTREAM);
    RectF secondHandle;
    secondHandle.SetOffset(secondHandleMetrics.offset);
    secondHandle.SetSize({ SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), secondHandleMetrics.height });
    secondHandle.SetHeight(secondHandleMetrics.height);
    AdjustHandleOffset(secondHandle);
    secondHandleInfo_.rect = secondHandle;

    if (!IsSelected()) {
        return;
    }

    CaretMetricsF firstHandleMetrics;
    CalcCaretMetricsByPosition(GetFirstHandleIndex(), firstHandleMetrics, TextAffinity::DOWNSTREAM);
    OffsetF firstHandleOffset = firstHandleMetrics.offset;

    RectF firstHandle;
    firstHandle.SetOffset(firstHandleOffset);
    firstHandle.SetSize({ SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), firstHandleMetrics.height });
    AdjustHandleOffset(firstHandle);
    firstHandleInfo_.rect = firstHandle;
}

std::string TextSelectController::ToString() const
{
    std::string result;
    result.append("first handle offset: ");
    result.append(std::to_string(firstHandleInfo_.index));
    result.append(", second handle offset: ");
    result.append(std::to_string(secondHandleInfo_.index));
    return result;
}

std::vector<RectF> TextSelectController::GetSelectedRects() const
{
    if (!IsSelected()) {
        return {};
    }
    std::vector<RectF> selectedRects;
    CHECK_NULL_RETURN(paragraph_, selectedRects);
    paragraph_->GetRectsForRange(GetStartIndex(), GetEndIndex(), selectedRects);
    return selectedRects;
}

void TextSelectController::MoveHandleToContentRect(RectF& handleRect, float boundaryAdjustment) const
{
    TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "before move, handleRect.GetX():%{public}f,handleRect.GetY():%{public}f",
        handleRect.GetX(), handleRect.GetY());
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    auto textRect = textField->GetTextRect();
    if (GreatNotEqual(textRect.Height(), contentRect_.Height())) {
        auto contentBottomBoundary = contentRect_.GetY() + contentRect_.Height();
        if (LessNotEqual(handleRect.GetY(), contentRect_.GetY()) &&
            LessOrEqual(handleRect.Height(), contentRect_.Height())) {
            auto dy = contentRect_.GetY() - handleRect.GetY();
            textRect.SetTop(textRect.GetY() + dy);
            handleRect.SetTop(handleRect.GetY() + dy);
        } else if (GreatNotEqual(handleRect.GetY() + handleRect.Height(), contentBottomBoundary)) {
            auto dy = handleRect.GetY() + handleRect.Height() - contentBottomBoundary;
            textRect.SetTop(textRect.GetY() - dy);
            handleRect.SetTop(handleRect.GetY() - dy);
        }
    }

    if (GreatNotEqual(textRect.Width(), contentRect_.Width())) {
        auto contentRightBoundary = contentRect_.GetX() + contentRect_.Width() - boundaryAdjustment;
        if (LessNotEqual(handleRect.GetX(), contentRect_.GetX())) {
            auto dx = contentRect_.GetX() - handleRect.GetX();
            textRect.SetLeft(textRect.GetX() + dx);
            handleRect.SetLeft(handleRect.GetX() + dx);
        } else if (GreatNotEqual(handleRect.GetX(), contentRightBoundary)) {
            auto dx = handleRect.GetX() - contentRightBoundary;
            textRect.SetLeft(textRect.GetX() - dx);
            handleRect.SetLeft(handleRect.GetX() - dx);
        }
    }
    textField->SetTextRect(textRect);
    AdjustHandleAtEdge(handleRect);
    textField->UpdateScrollBarOffset();
    TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "after move, handleRect.GetX():%{public}f,handleRect.GetY():%{public}f",
        handleRect.GetX(), handleRect.GetY());
}

void TextSelectController::AdjustHandleAtEdge(RectF& handleRect) const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    AdjustHandleOffset(handleRect);
    // Adjusted handle to the content area when they are at the content area boundary.
    if (LessNotEqual(handleRect.GetX(), contentRect_.GetX())) {
        handleRect.SetOffset(OffsetF(contentRect_.GetX(), handleRect.GetY()));
    }

    auto textRectRightBoundary = contentRect_.GetX() + contentRect_.Width();
    if (GreatNotEqual(handleRect.GetX() + handleRect.Width(), textRectRightBoundary) &&
        GreatNotEqual(contentRect_.Width(), 0.0) && !textField->GetTextUtf16Value().empty()) {
        handleRect.SetLeft(textRectRightBoundary - handleRect.Width());
    }
}

void TextSelectController::AdjustHandleOffset(RectF& handleRect) const
{
    handleRect.SetOffset(OffsetF(handleRect.GetX() - handleRect.Width() / 2.0f, handleRect.GetY()));
    // The handle position does not extend beyond the left edge of the text.
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    auto textRect = textField->GetTextRect();
    if (LessNotEqual(handleRect.GetX(), textRect.GetX())) {
        handleRect.SetOffset(OffsetF(textRect.GetX(), handleRect.GetY()));
    }
}

void TextSelectController::MoveFirstHandleToContentRect(int32_t index, bool moveHandle, bool moveContent)
{
    CaretMetricsF firstHandleMetrics;
    firstHandleInfo_.index = index;
    CalcCaretMetricsByPosition(
        GetFirstHandleIndex(), firstHandleMetrics, HasReverse() ? TextAffinity::UPSTREAM : TextAffinity::DOWNSTREAM);
    OffsetF firstHandleOffset = firstHandleMetrics.offset;
    RectF firstHandle;
    firstHandle.SetOffset(firstHandleOffset);
    firstHandle.SetSize({ SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), firstHandleMetrics.height });
    if (moveContent) {
        MoveHandleToContentRect(firstHandle);
    } else {
        AdjustHandleAtEdge(firstHandle);
    }
    firstHandleInfo_.rect = firstHandle;

    caretInfo_.index = std::max(firstHandleInfo_.index, secondHandleInfo_.index);
    UpdateCaretOffset(TextAffinity::DOWNSTREAM, moveHandle);
    UpdateSecondHandleOffset();
}

void TextSelectController::MoveSecondHandleToContentRect(int32_t index, bool moveHandle, bool moveContent)
{
    CaretMetricsF secondHandleMetrics;
    secondHandleInfo_.index = index;
    CalcCaretMetricsByPosition(
        GetSecondHandleIndex(), secondHandleMetrics, HasReverse() ? TextAffinity::DOWNSTREAM : TextAffinity::UPSTREAM);
    RectF secondHandle;
    secondHandle.SetOffset(secondHandleMetrics.offset);
    secondHandle.SetSize({ SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), secondHandleMetrics.height });
    if (moveContent) {
        MoveHandleToContentRect(secondHandle);
    } else {
        AdjustHandleAtEdge(secondHandle);
    }
    secondHandleInfo_.rect = secondHandle;

    caretInfo_.index = std::max(firstHandleInfo_.index, secondHandleInfo_.index);
    UpdateCaretOffset(TextAffinity::DOWNSTREAM, moveHandle);
    UpdateFirstHandleOffset();
}

void TextSelectController::MoveCaretToContentRect(
    int32_t index, TextAffinity textAffinity, bool isEditorValueChanged, bool moveContent)
{
    if (isEditorValueChanged) {
        textAffinity_ = textAffinity;
    }
    index = std::clamp(index, 0, static_cast<int32_t>(contentController_->GetTextUtf16Value().length()));
    CaretMetricsF caretMetrics;
    caretInfo_.index = index;
    firstHandleInfo_.index = index;
    secondHandleInfo_.index = index;
    if (contentController_->IsEmpty()) {
        SetCaretRectAtEmptyValue();
        return;
    }
    CalcCaretMetricsByPosition(GetCaretIndex(), caretMetrics, textAffinity_);
    OffsetF caretOffset = caretMetrics.offset;
    RectF caretRect;
    caretRect.SetOffset(caretOffset);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    caretRect.SetSize({ caretInfo_.rect.Width(),
        LessOrEqual(caretMetrics.height, 0.0) ? textField->PreferredLineHeight() : caretMetrics.height });

    // Adjusts one character width.
    float boundaryAdjustment = 0.0f;
    auto textRect = textField->GetTextRect();
    if (isEditorValueChanged && GreatNotEqual(textRect.Width(), contentRect_.Width()) &&
        GreatNotEqual(contentRect_.Width(), 0.0) &&
        caretInfo_.index < static_cast<int32_t>(contentController_->GetTextUtf16Value().length()) && paragraph_) {
        boundaryAdjustment = paragraph_->GetCharacterWidth(caretInfo_.index);
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGD(AceLogTag::ACE_TEXT, "caretInfo_.index = %{public}d, boundaryAdjustment =%{public}f",
                caretInfo_.index, boundaryAdjustment);
        }
    }
    if (moveContent) {
        MoveHandleToContentRect(caretRect, boundaryAdjustment);
    } else {
        AdjustHandleAtEdge(caretRect);
    }
    caretInfo_.rect = caretRect;
    UpdateCaretOriginalRect(caretMetrics.offset);
}

void TextSelectController::MoveCaretAnywhere(const Offset& touchOffset)
{
    CaretMetricsF caretMetrics;
    if (contentController_->IsEmpty()) {
        SetCaretRectAtEmptyValue();
        return;
    }
    FitCaretMetricsToTouchPoint(caretMetrics, touchOffset);
    OffsetF caretOffset = caretMetrics.offset;
    RectF caretRect;
    caretRect.SetOffset(caretOffset);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    caretRect.SetSize({ caretInfo_.rect.Width(),
        LessOrEqual(caretMetrics.height, 0.0) ? textField->PreferredLineHeight() : caretMetrics.height });

    // Adjusts one character width.
    float boundaryAdjustment = 0.0f;
    MoveHandleToContentRect(caretRect, boundaryAdjustment);
    caretInfo_.rect = caretRect;
    UpdateCaretOriginalRect(caretMetrics.offset);
    auto index = ConvertTouchOffsetToPosition(touchOffset);
    AdjustCursorPosition(index, touchOffset);
    UpdateCaretIndex(index);
}

void TextSelectController::UpdateFirstHandleOffset()
{
    CaretMetricsF caretMetrics;
    CalcCaretMetricsByPosition(
        GetFirstHandleIndex(), caretMetrics, HasReverse() ? TextAffinity::UPSTREAM : TextAffinity::DOWNSTREAM);
    firstHandleInfo_.rect.SetOffset(caretMetrics.offset);
    firstHandleInfo_.rect.SetHeight(caretMetrics.height);
    AdjustHandleOffset(firstHandleInfo_.rect);
}

void TextSelectController::UpdateSecondHandleOffset()
{
    CaretMetricsF caretMetrics;
    CalcCaretMetricsByPosition(
        GetSecondHandleIndex(), caretMetrics, HasReverse() ? TextAffinity::DOWNSTREAM : TextAffinity::UPSTREAM);
    secondHandleInfo_.rect.SetOffset(caretMetrics.offset);
    secondHandleInfo_.rect.SetHeight(caretMetrics.height);
    AdjustHandleOffset(secondHandleInfo_.rect);
}

void TextSelectController::UpdateCaretOffset(TextAffinity textAffinity, bool moveHandle)
{
    textAffinity_ = textAffinity;
    if (contentController_->IsEmpty()) {
        SetCaretRectAtEmptyValue();
        return;
    }
    CaretMetricsF caretMetrics;
    CalcCaretMetricsByPosition(GetCaretIndex(), caretMetrics, textAffinity);

    RectF caretRect;
    caretRect.SetOffset(caretMetrics.offset);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    caretRect.SetSize(SizeF(caretInfo_.rect.Width(),
        LessOrEqual(caretMetrics.height, 0.0) ? textField->PreferredLineHeight() : caretMetrics.height));
    caretInfo_.rect = caretRect;
    if (moveHandle) {
        MoveHandleToContentRect(caretInfo_.rect, 0.0f);
    } else {
        AdjustHandleAtEdge(caretInfo_.rect);
    }
    UpdateCaretOriginalRect(caretMetrics.offset);
}

void TextSelectController::UpdateCaretOffset(const OffsetF& offset)
{
    caretInfo_.rect.SetOffset(caretInfo_.rect.GetOffset() + offset);
    caretInfo_.originalRect.SetOffset(caretInfo_.originalRect.GetOffset() + offset);
    secondHandleInfo_.UpdateOffset(caretInfo_.rect.GetOffset() + offset);
}

void TextSelectController::UpdateSecondHandleInfoByMouseOffset(const Offset& localOffset)
{
    auto index = ConvertTouchOffsetToPosition(localOffset);
    if (GreatNotEqual(localOffset.GetX(), contentRect_.GetX() + contentRect_.Width()) && paragraph_) {
        float boundaryAdjustment = paragraph_->GetCharacterWidth(caretInfo_.index);
        index = ConvertTouchOffsetToPosition({localOffset.GetX() + boundaryAdjustment, localOffset.GetY()});
    }
    MoveSecondHandleToContentRect(index, false, false);
    caretInfo_.index = index;
    UpdateCaretRectByPositionNearTouchOffset(index, localOffset);
    auto caretRect = GetCaretRect();
    MoveHandleToContentRect(caretRect);
    caretInfo_.rect = caretRect;
}

void TextSelectController::MoveSecondHandleByKeyBoard(int32_t index, std::optional<TextAffinity> textAffinity)
{
    index = std::clamp(index, 0, static_cast<int32_t>(contentController_->GetTextUtf16Value().length()));
    MoveSecondHandleToContentRect(index);
    caretInfo_.index = index;
    auto caretTextAffinity = HasReverse() ? TextAffinity::DOWNSTREAM : TextAffinity::UPSTREAM;
    if (textAffinity) {
        caretTextAffinity = textAffinity.value();
    }
    UpdateCaretOffset(caretTextAffinity);
    auto caretRect = GetCaretRect();
    MoveHandleToContentRect(caretRect);
    caretInfo_.rect = caretRect;
}

void TextSelectController::FireSelectEvent()
{
    if (!onAccessibilityCallback_) {
        return;
    }
    bool needReport = !GetFirstIndex().has_value() || !GetSecondIndex().has_value();
    bool secondIndexChange = false;
    if (GetFirstIndex().has_value()) {
        needReport |= GetFirstIndex().value() != firstHandleInfo_.index;
    }

    if (GetSecondIndex().has_value()) {
        needReport |= GetSecondIndex().value() != secondHandleInfo_.index;
        secondIndexChange = GetSecondIndex().value() != secondHandleInfo_.index;
    }

    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    auto eventHub = textField->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);

    if (needReport && textField->IsModifyDone() && (textField->HasFocus()
        || (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)))) {
        UpdateFirstIndex(firstHandleInfo_.index);
        UpdateSecondIndex(secondHandleInfo_.index);
        onAccessibilityCallback_();
        eventHub->FireOnSelectionChange(std::min(firstHandleInfo_.index, secondHandleInfo_.index),
            std::max(firstHandleInfo_.index, secondHandleInfo_.index));
        if (secondIndexChange) {
            // when second index change, avoid caret in time
            textField->TriggerAvoidWhenCaretGoesDown();
        }
    }
}

void TextSelectController::ResetHandles()
{
    firstHandleInfo_.index = caretInfo_.index;
    secondHandleInfo_.index = caretInfo_.index;
    UpdateFirstHandleOffset();
    UpdateSecondHandleOffset();
}

bool TextSelectController::NeedAIAnalysis(int32_t& index, const CaretUpdateType targetType, const Offset& touchOffset,
    std::chrono::duration<float, std::ratio<1, SECONDS_TO_MILLISECONDS>> timeout)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textField, false);

    if (!InputAIChecker::NeedAIAnalysis(contentController_->GetTextUtf16Value().empty(), targetType, timeout)) {
        return false;
    }
    if (IsClickAtBoundary(index, touchOffset) && targetType == CaretUpdateType::PRESSED) {
        TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "NeedAIAnalysis IsClickAtBoundary is boundary, return!");
        return false;
    }

    if (textField->IsInPasswordMode()) {
        TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "NeedAIAnalysis IsInPasswordMode, return!");
        return false;
    }

    if (contentController_->IsIndexBeforeOrInEmoji(index)) {
        TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "NeedAIAnalysis IsIndexBeforeOrInEmoji, return!");
        return false;
    }
    return true;
}

void TextSelectController::AdjustCursorPosition(int32_t& index, const OHOS::Ace::Offset& touchOffset)
{
    auto timeout = GetLastClickTime() - lastAiPosTimeStamp_;
    if (NeedAIAnalysis(index, CaretUpdateType::PRESSED, touchOffset, timeout)) {
        // consider to limit the whole string length
        int32_t startIndex = -1;
        int32_t subIndex = index;
        // the subindex match the sub content,we do choose the subtext to ai analysis to avoid the content too large
        std::string content = contentController_->GetSelectedLimitValue(subIndex, startIndex);
        DataDetectorMgr::GetInstance().AdjustCursorPosition(subIndex, content, lastAiPosTimeStamp_, GetLastClickTime());
        index = startIndex + subIndex;
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "ai pos, startIndex:%{public}d,subIndex:%{public}d", startIndex, subIndex);
    }
}

bool TextSelectController::AdjustWordSelection(
    int32_t& index, int32_t& start, int32_t& end, const OHOS::Ace::Offset& touchOffset)
{
    auto timeout = GetLastClickTime() - lastAiPosTimeStamp_;
    if (NeedAIAnalysis(index, CaretUpdateType::DOUBLE_CLICK, touchOffset, timeout)) {
        // consider the limint the whole string length
        int32_t startIndex = -1;
        int32_t subIndex = index;
        // to avoid the content too large
        std::string content = contentController_->GetSelectedLimitValue(subIndex, startIndex);
        int32_t aiPosStart = -1;
        int32_t aiPosEnd = -1;
        DataDetectorMgr::GetInstance().AdjustWordSelection(subIndex, content, aiPosStart, aiPosEnd);
        TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "after ai ,startIndex:%{public}d-sub:%{public}d", aiPosStart, aiPosEnd);
        if (aiPosStart >= 0 && aiPosEnd >= 0) {
            index = startIndex + subIndex;
            start = startIndex + aiPosStart;
            end = startIndex + aiPosEnd;
            return true;
        }
    }
    return false;
}

bool TextSelectController::IsClickAtBoundary(int32_t index, const OHOS::Ace::Offset& touchOffset)
{
    if (InputAIChecker::IsSingleClickAtBoundary(index, contentController_->GetTextUtf16Value().length())) {
        return true;
    }

    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textField, false);
    auto textRect = textField->GetTextRect();

    CaretMetricsF caretMetrics;
    CalcCaretMetricsByPositionNearTouchOffset(
        index, caretMetrics, OffsetF(static_cast<float>(touchOffset.GetX()), static_cast<float>(touchOffset.GetY())));

    return InputAIChecker::IsMultiClickAtBoundary(caretMetrics.offset, textRect);
}

const TimeStamp& TextSelectController::GetLastClickTime() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, lastAiPosTimeStamp_);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textField, lastAiPosTimeStamp_);
    return textField->GetLastClickTime();
}

bool TextSelectController::IsTouchAtLineEnd(const Offset& localOffset) const
{
    CHECK_NULL_RETURN(paragraph_ && !contentController_->IsEmpty(), false);
    auto index = ConvertTouchOffsetToPosition(localOffset);
    if (index == static_cast<int32_t>(contentController_->GetTextUtf16Value().length())) {
        return true;
    }
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textField, false);
    auto textRect = textField->GetTextRect();
    auto offset = localOffset - Offset(textRect.GetX(), textRect.GetY());
    LineMetrics lineMetrics;
    if (paragraph_->GetLineMetricsByCoordinate(offset, lineMetrics)) {
        if (textField->IsLTRLayout()) {
            return GreatNotEqual(offset.GetX(), lineMetrics.x + lineMetrics.width);
        } else {
            return LessNotEqual(offset.GetX(), lineMetrics.x);
        }
    }
    return false;
}

TouchPosition TextSelectController::GetTouchLinePos(const Offset& localOffset)
{
    CHECK_NULL_RETURN(paragraph_, TouchPosition::MID);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, TouchPosition::MID);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textField, TouchPosition::MID);
    if (contentController_->IsEmpty()) {
        return textField->IsLTRLayout() ? TouchPosition::RIGHT : TouchPosition::LEFT;
    }
    auto index = ConvertTouchOffsetToPosition(localOffset);
    if (index == 0) {
        return textField->IsLTRLayout() ? TouchPosition::LEFT : TouchPosition::RIGHT;
    }
    if (index == static_cast<int32_t>(contentController_->GetTextUtf16Value().length())) {
        return textField->IsLTRLayout() ? TouchPosition::RIGHT : TouchPosition::LEFT;
    }
    auto textRect = textField->GetTextRect();
    auto offset = localOffset - Offset(textRect.GetX(), textRect.GetY());
    LineMetrics lineMetrics;
    if (paragraph_->GetLineMetricsByCoordinate(offset, lineMetrics)) {
        if (GreatNotEqual(offset.GetX(), lineMetrics.x + lineMetrics.width)) {
            return TouchPosition::RIGHT;
        }
        if (LessNotEqual(offset.GetX(), lineMetrics.x)) {
            return TouchPosition::LEFT;
        }
    }
    return TouchPosition::MID;
}

void TextSelectController::UpdateSelectWithBlank(const Offset& localOffset)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    auto textRect = textField->GetTextRect();
    auto contentRect = textField->GetTextContentRect();
    auto touchLocalOffset = localOffset;
    if (textField->IsTextArea() && GreatNotEqual(touchLocalOffset.GetY(), textRect.Bottom())) {
        // click at end of a paragraph.
        touchLocalOffset.SetX(textField->IsLTRLayout() ? contentRect.Right() : textRect.Left());
    }
    if (IsTouchAtLineEnd(touchLocalOffset)) {
        UpdateCaretInfoByOffset(touchLocalOffset);
    } else {
        UpdateSelectByOffset(localOffset);
    }
}

void TextSelectController::SetCaretRectAtEmptyValue()
{
    caretInfo_.rect = CalculateEmptyValueCaretRect();
    caretInfo_.originalRect = CalculateEmptyValueCaretRect(caretInfo_.originalRect.Width());
}

void TextSelectController::UpdateCaretOriginalRect(const OffsetF& offset)
{
    caretInfo_.originalRect.SetOffset(OffsetF(offset.GetX(), caretInfo_.rect.Top()));
    caretInfo_.originalRect.SetHeight(caretInfo_.rect.Height());
    AdjustHandleAtEdge(caretInfo_.originalRect);
}
} // namespace OHOS::Ace::NG