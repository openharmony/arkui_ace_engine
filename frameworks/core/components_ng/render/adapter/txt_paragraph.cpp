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

#include "core/components_ng/render/adapter/txt_paragraph.h"

#include "base/utils/utils.h"
#include "core/components/font/constants_converter.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/render/adapter/txt_font_collection.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
namespace {
const std::u16string ELLIPSIS = u"\u2026";
constexpr char16_t NEWLINE_CODE = u'\n';
} // namespace
RefPtr<Paragraph> Paragraph::Create(const ParagraphStyle& paraStyle, const RefPtr<FontCollection>& fontCollection)
{
    auto txtFontCollection = DynamicCast<TxtFontCollection>(fontCollection);
    CHECK_NULL_RETURN(txtFontCollection, nullptr);
    auto sharedFontCollection = txtFontCollection->GetRawFontCollection();
    return AceType::MakeRefPtr<TxtParagraph>(paraStyle, sharedFontCollection);
}

bool TxtParagraph::IsValid()
{
    return paragraph_ != nullptr;
}

void TxtParagraph::CreateBuilder()
{
    txt::ParagraphStyle style;
    style.text_direction = Constants::ConvertTxtTextDirection(paraStyle_.direction);
    style.text_align = Constants::ConvertTxtTextAlign(paraStyle_.align);
    style.max_lines = paraStyle_.maxLines;
    style.locale = paraStyle_.fontLocale;
    if (paraStyle_.textOverflow == TextOverflow::ELLIPSIS) {
        style.ellipsis = ELLIPSIS;
    }
#if !defined(FLUTTER_2_5) && !defined(NEW_SKIA)
    // keep WordBreak define same with WordBreakType in minikin
    style.word_break_type = static_cast<minikin::WordBreakType>(paraStyle_.wordBreak);
#endif
    builder_ = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection_);
}

void TxtParagraph::PushStyle(const TextStyle& style)
{
    if (!builder_) {
        CreateBuilder();
    }

    txt::TextStyle txtStyle;
    Constants::ConvertTxtStyle(style, PipelineContext::GetCurrentContext(), txtStyle);
    builder_->PushStyle(txtStyle);
}

void TxtParagraph::PopStyle()
{
    CHECK_NULL_VOID(builder_);
    builder_->Pop();
}

void TxtParagraph::AddText(const std::u16string& text)
{
    if (!builder_) {
        CreateBuilder();
    }
    text_ += text;
    builder_->AddText(text);
}

int32_t TxtParagraph::AddPlaceholder(const PlaceholderRun& span)
{
    if (!builder_) {
        CreateBuilder();
    }
    txt::PlaceholderRun txtSpan;
    Constants::ConvertPlaceholderRun(span, txtSpan);
    builder_->AddPlaceholder(txtSpan);
    return ++placeHolderIndex_;
}

void TxtParagraph::Build()
{
    CHECK_NULL_VOID_NOLOG(builder_);
    paragraph_ = builder_->Build();
}

void TxtParagraph::Reset()
{
    paragraph_.reset();
    builder_.reset();
    fontCollection_.reset();
}

void TxtParagraph::Layout(float width)
{
    CHECK_NULL_VOID(paragraph_);
    paragraph_->Layout(width);
}

float TxtParagraph::GetHeight()
{
    CHECK_NULL_RETURN(paragraph_, 0.0f);
    return static_cast<float>(paragraph_->GetHeight());
}

float TxtParagraph::GetTextWidth()
{
    CHECK_NULL_RETURN(paragraph_, 0.0f);
    if (GetLineCount() == 1) {
        return std::max(paragraph_->GetLongestLine(), paragraph_->GetMaxIntrinsicWidth());
    }
    return paragraph_->GetLongestLine();
}

float TxtParagraph::GetMaxIntrinsicWidth()
{
    CHECK_NULL_RETURN(paragraph_, 0.0f);
    return static_cast<float>(paragraph_->GetMaxIntrinsicWidth());
}

bool TxtParagraph::DidExceedMaxLines()
{
    CHECK_NULL_RETURN(paragraph_, false);
    return paragraph_->DidExceedMaxLines();
}

float TxtParagraph::GetLongestLine()
{
    CHECK_NULL_RETURN(paragraph_, 0.0f);
    return static_cast<float>(paragraph_->GetLongestLine());
}

float TxtParagraph::GetMaxWidth()
{
    CHECK_NULL_RETURN(paragraph_, 0.0f);
    return static_cast<float>(paragraph_->GetMaxWidth());
}

float TxtParagraph::GetAlphabeticBaseline()
{
    CHECK_NULL_RETURN(paragraph_, 0.0f);
    return static_cast<float>(paragraph_->GetAlphabeticBaseline());
}

size_t TxtParagraph::GetLineCount()
{
    auto* paragraphTxt = static_cast<txt::ParagraphTxt*>(paragraph_.get());
    CHECK_NULL_RETURN(paragraphTxt, 0);
    return paragraphTxt->GetLineCount();
}

void TxtParagraph::Paint(const RSCanvas& canvas, float x, float y)
{
    CHECK_NULL_VOID(paragraph_);
    SkCanvas* skCanvas = canvas.GetImpl<RSSkCanvas>()->ExportSkCanvas();
    CHECK_NULL_VOID(skCanvas);
    paragraph_->Paint(skCanvas, x, y);
}

void TxtParagraph::Paint(SkCanvas* skCanvas, float x, float y)
{
    CHECK_NULL_VOID(skCanvas);
    paragraph_->Paint(skCanvas, x, y);
}

int32_t TxtParagraph::GetHandlePositionForClick(const Offset& offset)
{
    if (!paragraph_) {
        return 0;
    }
    return static_cast<int32_t>(paragraph_->GetGlyphPositionAtCoordinate(offset.GetX(), offset.GetY()).position);
}

bool TxtParagraph::ComputeOffsetForCaretUpstream(int32_t extent, CaretMetrics& result)
{
    if (!paragraph_ || (text_.empty() && placeHolderIndex_ == -1)) {
        return false;
    }
    if (static_cast<size_t>(extent) > GetParagraphLength()) {
        extent = GetParagraphLength();
    }

    char16_t prevChar = 0;
    if (static_cast<size_t>(extent) <= text_.length()) {
        prevChar = text_[std::max(0, extent - 1)];
    }

    result.Reset();
    int32_t graphemeClusterLength = StringUtils::NotInUtf16Bmp(prevChar) ? 2 : 1;
    int32_t prev = extent - graphemeClusterLength;
    auto boxes = paragraph_->GetRectsForRange(
        prev, extent, txt::Paragraph::RectHeightStyle::kMax, txt::Paragraph::RectWidthStyle::kTight);
    while (boxes.empty() && !text_.empty()) {
        graphemeClusterLength *= 2;
        prev = extent - graphemeClusterLength;
        if (prev < 0) {
            boxes = paragraph_->GetRectsForRange(
                0, extent, txt::Paragraph::RectHeightStyle::kMax, txt::Paragraph::RectWidthStyle::kTight);
            break;
        }
        boxes = paragraph_->GetRectsForRange(
            prev, extent, txt::Paragraph::RectHeightStyle::kMax, txt::Paragraph::RectWidthStyle::kTight);
    }
    if (boxes.empty()) {
        LOGD("boxes is empty.");
        return false;
    }

    const auto& textBox = *boxes.begin();

    if (prevChar == NEWLINE_CODE) {
        // Return the start of next line.
        result.offset.SetX(0.0);
        result.offset.SetY(textBox.rect.fBottom);
        return true;
    }

    bool isLtr = textBox.direction == txt::TextDirection::ltr;
    // Caret is within width of the downstream glyphs.
    double caretStart = isLtr ? textBox.rect.fRight : textBox.rect.fLeft;
    double offsetX = std::min(caretStart, paragraph_->GetMaxWidth());
    result.offset.SetX(offsetX);
    result.offset.SetY(textBox.rect.fTop);
    result.height = textBox.rect.fBottom - textBox.rect.fTop;

    return true;
}

bool TxtParagraph::ComputeOffsetForCaretDownstream(int32_t extent, CaretMetrics& result)
{
    if (!paragraph_ || static_cast<size_t>(extent) >= GetParagraphLength()) {
        return false;
    }

    result.Reset();
    const int32_t graphemeClusterLength = 1;
    const int32_t next = extent + graphemeClusterLength;
    auto boxes = paragraph_->GetRectsForRange(
        extent, next, txt::Paragraph::RectHeightStyle::kMax, txt::Paragraph::RectWidthStyle::kTight);
    if (boxes.empty()) {
        return false;
    }

    const auto& textBox = *boxes.begin();
    bool isLtr = textBox.direction == txt::TextDirection::ltr;
    // Caret is within width of the downstream glyphs.
    double caretStart = isLtr ? textBox.rect.fLeft : textBox.rect.fRight;
    double offsetX = std::min(caretStart, paragraph_->GetMaxWidth());
    result.offset.SetX(offsetX);
    result.offset.SetY(textBox.rect.fTop);
    result.height = textBox.rect.fBottom - textBox.rect.fTop;

    return true;
}

void TxtParagraph::GetRectsForRange(int32_t start, int32_t end, std::vector<Rect>& selectedRects)
{
    CHECK_NULL_VOID(paragraph_);
    const auto& boxes = paragraph_->GetRectsForRange(
        start, end, txt::Paragraph::RectHeightStyle::kMax, txt::Paragraph::RectWidthStyle::kTight);
    if (boxes.empty()) {
        return;
    }
    for (const auto& box : boxes) {
        auto selectionRect = Constants::ConvertSkRect(box.rect);
        selectedRects.emplace_back(selectionRect);
    }
}

void TxtParagraph::GetRectsForPlaceholders(std::vector<Rect>& selectedRects)
{
    CHECK_NULL_VOID(paragraph_);
    const auto& boxes = paragraph_->GetRectsForPlaceholders();
    if (boxes.empty()) {
        return;
    }
    for (const auto& box : boxes) {
        auto selectionRect = Constants::ConvertSkRect(box.rect);
        selectedRects.emplace_back(selectionRect);
    }
}

void TxtParagraph::SetIndents(const std::vector<float>& indents)
{
    auto* paragraphTxt = static_cast<txt::ParagraphTxt*>(paragraph_.get());
    CHECK_NULL_VOID(paragraphTxt);
    paragraphTxt->SetIndents(indents);
}

bool TxtParagraph::GetWordBoundary(int32_t offset, int32_t& start, int32_t& end)
{
    auto* paragraphTxt = static_cast<txt::ParagraphTxt*>(paragraph_.get());
    CHECK_NULL_RETURN(paragraphTxt, false);
    auto range = paragraphTxt->GetWordBoundary(static_cast<size_t>(offset));
    start = static_cast<int32_t>(range.start);
    end = static_cast<int32_t>(range.end);
    return true;
}
} // namespace OHOS::Ace::NG
