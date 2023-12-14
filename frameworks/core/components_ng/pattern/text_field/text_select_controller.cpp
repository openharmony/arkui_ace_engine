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
#include "base/utils/utils.h"
#include "core/common/ai/data_detector_mgr.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text_field/text_input_ai_checker.h"

namespace OHOS::Ace::NG {
void TextSelectController::UpdateHandleIndex(int32_t firstHandleIndex, int32_t secondHandleIndex)
{
    firstHandleInfo_.index = firstHandleIndex;
    secondHandleInfo_.index = secondHandleIndex;
    caretInfo_.index = std::max(firstHandleInfo_.index, secondHandleInfo_.index);
    CalculateHandleOffset();
    UpdateCaretOffset();
    FireSelectEvent();
}

void TextSelectController::UpdateCaretIndex(int32_t index)
{
    auto newIndex = std::clamp(index, 0, static_cast<int32_t>(contentController_->GetWideText().length()));
    caretInfo_.index = newIndex;
    firstHandleInfo_.index = newIndex;
    secondHandleInfo_.index = newIndex;
    UpdateRecordCaretIndex(caretInfo_.index);
    FireSelectEvent();
}

RectF TextSelectController::CalculateEmptyValueCaretRect() const
{
    RectF rect;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, rect);
    auto textFiled = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textFiled, rect);
    auto layoutProperty = textFiled->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, rect);
    rect.SetLeft(contentRect_.Left());
    rect.SetTop(contentRect_.Top());
    rect.SetHeight(textFiled->PreferredLineHeight());
    rect.SetWidth(caretInfo_.rect.Width());
    switch (layoutProperty->GetTextAlignValue(TextAlign::START)) {
        case TextAlign::START:
            rect.SetLeft(contentRect_.GetX());
            break;
        case TextAlign::CENTER:
            rect.SetLeft(static_cast<float>(contentRect_.GetX()) + contentRect_.Width() / 2.0f);
            break;
        case TextAlign::END:
            rect.SetLeft(static_cast<float>(contentRect_.GetX()) + contentRect_.Width() -
                         static_cast<float>(caretInfo_.rect.Width()));
            break;
        default:
            break;
    }

    auto align = Alignment::TOP_CENTER;
    if (layoutProperty->GetPositionProperty()) {
        align = layoutProperty->GetPositionProperty()->GetAlignment().value_or(align);
    }
    OffsetF offset = Alignment::GetAlignPosition(contentRect_.GetSize(), rect.GetSize(), align);
    rect.SetTop(offset.GetY() + contentRect_.GetY());

    AdjustHandleAtEdge(rect);
    return rect;
}

void TextSelectController::FitCaretMetricsToContentRect(CaretMetricsF& caretMetrics)
{
    if (caretMetrics.height > contentRect_.Height()) {
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
    auto textFiled = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFiled);
    auto textRect = textFiled->GetTextRect();
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
    auto textFiled = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFiled);
    auto textRect = textFiled->GetTextRect();
    paragraph_->CalcCaretMetricsByPosition(extent, caretMetrics, touchOffset - textRect.GetOffset());
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

void TextSelectController::UpdateCaretInfoByOffset(const Offset& localOffset)
{
    auto index = ConvertTouchOffsetToPosition(localOffset);
    AdjustCursorPosition(index, localOffset);
    UpdateCaretIndex(index);
    if (!contentController_->IsEmpty()) {
        UpdateCaretRectByPositionNearTouchOffset(index, localOffset);
        MoveHandleToContentRect(caretInfo_.rect, 0.0f, true);
        UpdateRecordCaretIndex(caretInfo_.index);
    } else {
        caretInfo_.rect = CalculateEmptyValueCaretRect();
    }
}

int32_t TextSelectController::ConvertTouchOffsetToPosition(const Offset& localOffset)
{
    CHECK_NULL_RETURN(paragraph_, 0);
    if (contentController_->IsEmpty()) {
        return 0;
    }
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, 0);
    auto textFiled = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textFiled, 0);
    auto textRect = textFiled->GetTextRect();
    auto offset = localOffset - Offset(textRect.GetX(), textRect.GetY());
    return paragraph_->GetGlyphIndexByCoordinate(offset);
}

void TextSelectController::UpdateSelectByOffset(const Offset& localOffset)
{
    CHECK_NULL_VOID(paragraph_ && !contentController_->IsEmpty());
    int32_t start = 0;
    int32_t end = 0;
    auto pos = ConvertTouchOffsetToPosition(localOffset);
    // Ensure that the end is selected.
    if (pos >= static_cast<int32_t>(paragraph_->GetParagraphText().length())) {
        pos -= 1;
    }

    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFiled = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFiled);
    bool smartSelect = false;
    if (!textFiled->IsUsingMouse()) {
        smartSelect = AdjustWordSelection(pos, start, end, localOffset);
    }
    
    if (!smartSelect && !paragraph_->GetWordBoundary(pos, start, end)) {
        start = pos;
        end = std::min(static_cast<int32_t>(contentController_->GetWideText().length()),
            pos + GetGraphemeClusterLength(contentController_->GetWideText(), pos, true));
    }

    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGI(AceLogTag::ACE_TEXT,
            "current word position = %{public}d, select position {start:%{public}d, end:%{public}d}", pos, start, end);
    }
    UpdateHandleIndex(start, end);
    auto index = ConvertTouchOffsetToPosition(localOffset);
    auto textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    if (index == textLength && GreatNotEqual(localOffset.GetX(), caretInfo_.rect.GetOffset().GetX())) {
        UpdateHandleIndex(GetCaretIndex());
    }
    if (IsSelected()) {
        MoveSecondHandleToContentRect(GetSecondHandleIndex());
    } else {
        MoveCaretToContentRect(GetCaretIndex());
    }
}

int32_t TextSelectController::GetGraphemeClusterLength(const std::wstring& text, int32_t extend, bool checkPrev)
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

void TextSelectController::CalculateHandleOffset()
{
    // calculate firstHandleOffset, secondHandleOffset and handlePaintSize
    if (contentController_->IsEmpty()) {
        caretInfo_.rect = CalculateEmptyValueCaretRect();
        return;
    }
    CaretMetricsF secondHandleMetrics;
    CalcCaretMetricsByPosition(GetSecondHandleIndex(), secondHandleMetrics, TextAffinity::UPSTREAM);
    OffsetF secondHandleOffset = secondHandleMetrics.offset;
    RectF secondHandle;
    secondHandle.SetOffset(secondHandleOffset);
    secondHandle.SetSize({ SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), secondHandleMetrics.height });
    secondHandle.SetHeight(secondHandleMetrics.height);
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

void TextSelectController::MoveHandleToContentRect(
    RectF& handleRect, float boundaryAdjustment, bool isAdjustUnconditionally) const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFiled = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFiled);
    auto textRect = textFiled->GetTextRect();
    if (textRect.Height() > contentRect_.Height()) {
        auto contentBottomBoundary = contentRect_.GetY() + contentRect_.Height();
        if (LessNotEqual(handleRect.GetY(), contentRect_.GetY()) &&
            LessOrEqual(handleRect.Height(), contentRect_.Height())) {
            auto dy = contentRect_.GetY() - handleRect.GetY();
            textRect.SetOffset(OffsetF(textRect.GetX(), textRect.GetY() + dy));
            handleRect.SetOffset(OffsetF(handleRect.GetX(), handleRect.GetY() + dy));
        } else if (GreatNotEqual(handleRect.GetY() + handleRect.Height(), contentBottomBoundary)) {
            auto dy = handleRect.GetY() + handleRect.Height() - contentBottomBoundary;
            textRect.SetOffset(OffsetF(textRect.GetX(), textRect.GetY() - dy));
            handleRect.SetOffset(OffsetF(handleRect.GetX(), handleRect.GetY() - dy));
        }
    }

    if (textRect.Width() > contentRect_.Width()) {
        auto contentRightBoundary = contentRect_.GetX() + contentRect_.Width() - boundaryAdjustment;
        if (handleRect.GetX() < contentRect_.GetX()) {
            auto dx = contentRect_.GetX() - handleRect.GetX();
            textRect.SetOffset(OffsetF(textRect.GetX() + dx, textRect.GetY()));
            handleRect.SetOffset(OffsetF(handleRect.GetX() + dx, handleRect.GetY()));
        } else if (handleRect.GetX() > contentRightBoundary) {
            auto dx = handleRect.GetX() - contentRightBoundary;
            textRect.SetOffset(OffsetF(textRect.GetX() - dx, textRect.GetY()));
            handleRect.SetOffset(OffsetF(handleRect.GetX() - dx, handleRect.GetY()));
        }
    }
    textFiled->SetTextRect(textRect);
    AdjustHandleAtEdge(handleRect, isAdjustUnconditionally);
}

void TextSelectController::AdjustHandleAtEdge(RectF& handleRect, bool isAdjustUnconditionally) const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFiled = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFiled);
    handleRect.SetOffset(OffsetF(handleRect.GetX() - handleRect.Width() / 2, handleRect.GetY()));
    // Adjusted handle to the content area when they are at the content area boundary.
    if (handleRect.GetX() < contentRect_.GetX()) {
        handleRect.SetOffset(OffsetF(contentRect_.GetX(), handleRect.GetY()));
    }

    auto textRectRightBoundary = contentRect_.GetX() + contentRect_.Width();
    if (GreatNotEqual(handleRect.GetX() + handleRect.Width(), textRectRightBoundary) &&
        GreatNotEqual(contentRect_.Width(), 0.0) && !textFiled->GetTextValue().empty()) {
        handleRect.SetLeft(textRectRightBoundary - handleRect.Width());
    }
}

void TextSelectController::MoveFirstHandleToContentRect(int32_t index)
{
    CaretMetricsF firstHandleMetrics;
    firstHandleInfo_.index = index;
    CalcCaretMetricsByPosition(GetFirstHandleIndex(), firstHandleMetrics, TextAffinity::DOWNSTREAM);
    OffsetF firstHandleOffset = firstHandleMetrics.offset;
    RectF firstHandle;
    firstHandle.SetOffset(firstHandleOffset);
    firstHandle.SetSize({ SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), firstHandleMetrics.height });
    MoveHandleToContentRect(firstHandle);
    firstHandleInfo_.rect = firstHandle;

    caretInfo_.index = std::max(firstHandleInfo_.index, secondHandleInfo_.index);
    UpdateCaretOffset();
    UpdateSecondHandleOffset();
    FireSelectEvent();
}

void TextSelectController::MoveSecondHandleToContentRect(int32_t index)
{
    CaretMetricsF secondHandleMetrics;
    secondHandleInfo_.index = index;
    CalcCaretMetricsByPosition(GetSecondHandleIndex(), secondHandleMetrics, TextAffinity::UPSTREAM);
    OffsetF secondHandleOffset = secondHandleMetrics.offset;
    RectF secondHandle;
    secondHandle.SetOffset(secondHandleOffset);
    secondHandle.SetSize({ SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), secondHandleMetrics.height });
    MoveHandleToContentRect(secondHandle);
    secondHandleInfo_.rect = secondHandle;

    caretInfo_.index = std::max(firstHandleInfo_.index, secondHandleInfo_.index);
    UpdateCaretOffset();
    UpdateFirstHandleOffset();
    FireSelectEvent();
}

void TextSelectController::MoveCaretToContentRect(int32_t index, TextAffinity textAffinity, bool isEditorValueChanged)
{
    index = std::clamp(index, 0, static_cast<int32_t>(contentController_->GetWideText().length()));
    CaretMetricsF CaretMetrics;
    caretInfo_.index = index;
    firstHandleInfo_.index = index;
    secondHandleInfo_.index = index;
    if (contentController_->IsEmpty()) {
        caretInfo_.rect = CalculateEmptyValueCaretRect();
        return;
    }
    CalcCaretMetricsByPosition(GetCaretIndex(), CaretMetrics, textAffinity);
    OffsetF CaretOffset = CaretMetrics.offset;
    RectF caretRect;
    caretRect.SetOffset(CaretOffset);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFiled = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFiled);
    caretRect.SetSize({ caretInfo_.rect.Width(),
        LessOrEqual(CaretMetrics.height, 0.0) ? textFiled->PreferredLineHeight() : CaretMetrics.height });

    // Adjusts one character width.
    float boundaryAdjustment = 0.0f;
    if (isEditorValueChanged) {
        auto textRect = textFiled->GetTextRect();
        if (GreatNotEqual(textRect.Width(), contentRect_.Width()) && GreatNotEqual(contentRect_.Width(), 0.0) &&
            caretInfo_.index < static_cast<int32_t>(contentController_->GetWideText().length())) {
            boundaryAdjustment = paragraph_->GetCharacterWidth(caretInfo_.index);
            if (SystemProperties::GetDebugEnabled()) {
                TAG_LOGI(AceLogTag::ACE_TEXT, "caretInfo_.index = %{public}d, boundaryAdjustment =%{public}f",
                    caretInfo_.index, boundaryAdjustment);
            }
        }
    }

    MoveHandleToContentRect(caretRect, boundaryAdjustment);
    caretInfo_.rect = caretRect;
    caretRect.SetWidth(SelectHandleInfo::GetDefaultLineWidth().ConvertToPx());
    UpdateRecordCaretIndex(caretInfo_.index);
}

void TextSelectController::UpdateFirstHandleOffset()
{
    CaretMetricsF caretMetrics;
    CalcCaretMetricsByPosition(GetFirstHandleIndex(), caretMetrics, TextAffinity::DOWNSTREAM);
    firstHandleInfo_.rect.SetOffset(caretMetrics.offset);
    firstHandleInfo_.rect.SetHeight(caretMetrics.height);
}

void TextSelectController::UpdateSecondHandleOffset()
{
    CaretMetricsF caretMetrics;
    CalcCaretMetricsByPosition(GetSecondHandleIndex(), caretMetrics, TextAffinity::UPSTREAM);
    secondHandleInfo_.rect.SetOffset(caretMetrics.offset);
    secondHandleInfo_.rect.SetHeight(caretMetrics.height);
}

void TextSelectController::UpdateCaretOffset()
{
    if (contentController_->IsEmpty()) {
        caretInfo_.rect = CalculateEmptyValueCaretRect();
        return;
    }
    CaretMetricsF caretMetrics;
    CalcCaretMetricsByPosition(GetCaretIndex(), caretMetrics, TextAffinity::DOWNSTREAM);

    RectF caretRect;
    caretRect.SetOffset(caretMetrics.offset);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFiled = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFiled);
    caretRect.SetSize(SizeF(caretInfo_.rect.Width(),
        LessOrEqual(caretMetrics.height, 0.0) ? textFiled->PreferredLineHeight() : caretMetrics.height));
    caretInfo_.rect = caretRect;
}

void TextSelectController::UpdateCaretOffset(const OffsetF& offset)
{
    caretInfo_.rect.SetOffset(offset);
    secondHandleInfo_.UpdateOffset(offset);
}

void TextSelectController::UpdateSecondHandleInfoByMouseOffset(const Offset& localOffset)
{
    auto index = ConvertTouchOffsetToPosition(localOffset);
    MoveSecondHandleToContentRect(index);
    caretInfo_.index = index;
    UpdateCaretOffset();
}

void TextSelectController::MoveSecondHandleByKeyBoard(int32_t index)
{
    MoveSecondHandleToContentRect(index);
    caretInfo_.index = index;
    UpdateCaretOffset();
}

void TextSelectController::FireSelectEvent()
{
    if (!onAccessibilityCallback_) {
        return;
    }
    bool needReport = !GetFirstIndex().has_value() || !GetSecondIndex().has_value();
    if (GetFirstIndex().has_value()) {
        needReport |= GetFirstIndex().value() != firstHandleInfo_.index;
    }

    if (GetSecondIndex().has_value()) {
        needReport |= GetFirstIndex().value() != secondHandleInfo_.index;
    }

    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFiled = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFiled);
    auto eventHub = textFiled->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);

    if (needReport) {
        UpdateFirstIndex(firstHandleInfo_.index);
        UpdateSecondIndex(secondHandleInfo_.index);
        onAccessibilityCallback_();
        eventHub->FireOnSelectionChange(firstHandleInfo_.index, secondHandleInfo_.index);
    }
}

void TextSelectController::UpdateRecordCaretIndex(int32_t index) const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFiled = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFiled);
    textFiled->UpdateRecordCaretIndex(index);
    textFiled->UpdateCaretInfoToController();
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
    if (!InputAIChecker::NeedAIAnalysis(contentController_->GetTextValue(), targetType, timeout)) {
        return false;
    }
    if (IsClickAtBoundary(index, touchOffset) && targetType == CaretUpdateType::PRESSED) {
        TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "NeedAIAnalysis IsClickAtBoundary is boundary ,return!");
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
        DataDetectorMgr::GetInstance().AdjustWordSelection(subIndex, content, start, end);
        TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "after ai ,startIndex:%{public}d-sub:%{public}d", start, end);
        if (start < 0 || end < 0) {
            return false;
        }
        index = startIndex + subIndex;
        start = startIndex + start;
        end = startIndex + end;
        return true;
    }

    return false;
}

bool TextSelectController::IsClickAtBoundary(int32_t index, const OHOS::Ace::Offset& touchOffset)
{
    if (InputAIChecker::IsSingleClickAtBoundary(index, contentController_->GetWideText().length())) {
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

    if (InputAIChecker::IsMultiClickAtBoundary(caretMetrics.offset, textRect)) {
        return true;
    }

    return false;
}

const TimeStamp& TextSelectController::GetLastClickTime()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, lastAiPosTimeStamp_);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textField, lastAiPosTimeStamp_);
    return textField->GetLastClickTime();
}
} // namespace OHOS::Ace::NG