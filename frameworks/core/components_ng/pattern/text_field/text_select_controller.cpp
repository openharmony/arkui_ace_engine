/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <string>
#include <vector>

#include "base/geometry/ng/rect_t.h"
#include "base/geometry/offset.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {

void TextSelectController::UpdateHandleIndex(int32_t firstHandleIndex, int32_t secondHandleIndex)
{
    firstHandleInfo_.index = firstHandleIndex;
    secondHandleInfo_.index = secondHandleIndex;
    caretInfo_.index = secondHandleInfo_.index;
    CalculateHandleOffset();
    FireSelectEvent();
}

void TextSelectController::UpdateCaretIndex(int32_t index)
{
    auto newIndex = std::clamp(index, 0, static_cast<int32_t>(contentController_->GetWideText().length()));
    caretInfo_.index = newIndex;
    firstHandleInfo_.index = newIndex;
    secondHandleInfo_.index = newIndex;
    UpdateRecordCaretIndex(caretInfo_.index);
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
    rect.SetHeight(caretInfo_.rect.Height());
    rect.SetWidth(caretInfo_.rect.Width());
    switch (layoutProperty->GetTextAlignValue(TextAlign::START)) {
        case TextAlign::START:
            rect.SetLeft(contentRect_.GetX());
            return rect;
        case TextAlign::CENTER:
            rect.SetLeft(static_cast<float>(contentRect_.GetX()) + contentRect_.Width() / 2.0f);
            return rect;
        case TextAlign::END:
            rect.SetLeft(static_cast<float>(contentRect_.GetX()) + contentRect_.Width() -
                         static_cast<float>(caretInfo_.rect.Width()));
            return rect;
        default:
            return rect;
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
}

void TextSelectController::UpdateCaretRectByPositionNearTouchOffset(int32_t position, const Offset& touchOffset)
{
    CaretMetricsF caretMetrics;
    CalcCaretMetricsByPositionNearTouchOffset(position, caretMetrics,
        OffsetF(static_cast<float>(touchOffset.GetX()), static_cast<float>(touchOffset.GetY())));

    CaretMetricsF CaretMetrics;
    paragraph_->CalcCaretMetricsByPosition(position, CaretMetrics, TextAffinity::UPSTREAM);
    caretInfo_.UpdateOffset(caretMetrics.offset);
    UpdateCaretHeight(caretMetrics.height);
}

void TextSelectController::UpdateCaretInfoByOffset(const Offset& localOffset)
{
    auto index = ConvertTouchOffsetToPosition(localOffset);
    UpdateCaretIndex(index);
    if (!contentController_->IsEmpty()) {
        UpdateCaretRectByPositionNearTouchOffset(index, localOffset);
    }
    MoveCaretToContentRect(GetCaretIndex());
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
    if (!paragraph_->GetWordBoundary(pos, start, end)) {
        start = pos;
        end = std::min(static_cast<int32_t>(contentController_->GetWideText().length()),
            pos + GetGraphemeClusterLength(contentController_->GetWideText(), pos, true));
    }
    UpdateHandleIndex(start, end);
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

void TextSelectController::MoveHandleToContentRect(RectF& handleRect)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFiled = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFiled);
    auto textRect = textFiled->GetTextRect();
    if (textRect.Height() > contentRect_.Height()) {
        auto contentBottomBoundary = contentRect_.GetY() + contentRect_.Height();
        if (handleRect.GetY() < contentRect_.GetY()) {
            auto dy = contentRect_.GetY() - handleRect.GetY();
            textRect.SetOffset(OffsetF(textRect.GetX(), textRect.GetY() + dy));
            handleRect.SetOffset(OffsetF(handleRect.GetX(), handleRect.GetY() + dy));
        } else if (handleRect.GetY() + handleRect.Height() > contentBottomBoundary) {
            auto dy = handleRect.GetY() + handleRect.Height() - contentBottomBoundary;
            textRect.SetOffset(OffsetF(textRect.GetX(), textRect.GetY() - dy));
            handleRect.SetOffset(OffsetF(handleRect.GetX(), handleRect.GetY() - dy));
        }
    }

    auto contentRightBoundary = contentRect_.GetX() + contentRect_.Width();
    if (textRect.Width() > contentRect_.Width()) {
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
    if (GreatNotEqual(handleRect.GetX() + handleRect.Width(), contentRightBoundary) &&
        LessOrEqual(handleRect.Width(), contentRect_.Width())) {
        handleRect.SetOffset(OffsetF(contentRightBoundary - handleRect.Width(), handleRect.GetY()));
    }
    textFiled->SetTextRect(textRect);
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
    UpdateFirstHandleOffset();
    FireSelectEvent();
}

void TextSelectController::MoveCaretToContentRect(int32_t index)
{
    CaretMetricsF CaretMetrics;
    caretInfo_.index = index;
    firstHandleInfo_.index = index;
    secondHandleInfo_.index = index;
    CalcCaretMetricsByPosition(GetCaretIndex(), CaretMetrics, TextAffinity::UPSTREAM);
    OffsetF CaretOffset = CaretMetrics.offset;
    RectF caretRect;
    caretRect.SetOffset(CaretOffset);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFiled = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFiled);
    caretRect.SetSize({ caretInfo_.rect.Width(),
        LessOrEqual(CaretMetrics.height, 0.0) ? textFiled->PreferredLineHeight() : CaretMetrics.height });
    MoveHandleToContentRect(caretRect);
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
    MoveHandleToContentRect(caretRect);
    caretInfo_.rect = caretRect;
}

void TextSelectController::UpdateCaretOffset(const OffsetF& offset)
{
    caretInfo_.rect.SetOffset(offset);
}

void TextSelectController::UpdateSecondHandleInfoByMouseOffset(const Offset& localOffset)
{
    auto index = ConvertTouchOffsetToPosition(localOffset);
    caretInfo_.index = index;
    UpdateCaretOffset();
    MoveSecondHandleToContentRect(index);
}

void TextSelectController::FireSelectEvent()
{
    if (!onAccessibilityCallback_ || !IsSelected()) {
        return;
    }
    bool needReport = false;
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
}
} // namespace OHOS::Ace::NG