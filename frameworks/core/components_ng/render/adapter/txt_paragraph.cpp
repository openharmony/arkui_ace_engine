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
#include "core/components_ng/render/adapter/pixelmap_image.h"
#include "core/components_ng/render/adapter/txt_font_collection.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

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
#ifndef USE_GRAPHIC_TEXT_GINE
    txt::ParagraphStyle style;
    style.text_direction = Constants::ConvertTxtTextDirection(paraStyle_.direction);
    style.text_align = Constants::ConvertTxtTextAlign(paraStyle_.align);
    style.max_lines = paraStyle_.maxLines;
    style.font_size = paraStyle_.fontSize; // libtxt style.font_size
    style.word_break_type = static_cast<minikin::WordBreakType>(paraStyle_.wordBreak);
#else
    Rosen::TypographyStyle style;
    style.textDirection = Constants::ConvertTxtTextDirection(paraStyle_.direction);
    style.textAlign = Constants::ConvertTxtTextAlign(paraStyle_.align);
    style.maxLines = paraStyle_.maxLines;
    style.fontSize = paraStyle_.fontSize; // Rosen style.fontSize
    style.wordBreakType = static_cast<Rosen::WordBreakType>(paraStyle_.wordBreak);
#endif
    style.locale = paraStyle_.fontLocale;
    if (paraStyle_.textOverflow == TextOverflow::ELLIPSIS) {
        style.ellipsis = ELLIPSIS;
    }
#if !defined(FLUTTER_2_5) && !defined(NEW_SKIA)
    // keep WordBreak define same with WordBreakType in minikin
#ifndef USE_GRAPHIC_TEXT_GINE
    style.word_break_type = static_cast<minikin::WordBreakType>(paraStyle_.wordBreak);
#else
    style.wordBreakType = static_cast<Rosen::WordBreakType>(paraStyle_.wordBreak);
#endif
#endif
#ifndef USE_GRAPHIC_TEXT_GINE
    builder_ = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection_);
#else
    builder_ = Rosen::TypographyCreate::Create(style, fontCollection_);
#endif
}

void TxtParagraph::PushStyle(const TextStyle& style)
{
    if (!builder_) {
        CreateBuilder();
    }

#ifndef USE_GRAPHIC_TEXT_GINE
    txt::TextStyle txtStyle;
#else
    Rosen::TextStyle txtStyle;
#endif
    textAlign_ = style.GetTextAlign();
    Constants::ConvertTxtStyle(style, PipelineContext::GetCurrentContext(), txtStyle);
    builder_->PushStyle(txtStyle);
}

void TxtParagraph::PopStyle()
{
    CHECK_NULL_VOID(builder_);
#ifndef USE_GRAPHIC_TEXT_GINE
    builder_->Pop();
#else
    builder_->PopStyle();
#endif
}

void TxtParagraph::AddText(const std::u16string& text)
{
    if (!builder_) {
        CreateBuilder();
    }
    text_ += text;
#ifndef USE_GRAPHIC_TEXT_GINE
    builder_->AddText(text);
#else
    builder_->AppendText(text);
#endif
}

int32_t TxtParagraph::AddPlaceholder(const PlaceholderRun& span)
{
    if (!builder_) {
        CreateBuilder();
    }
#ifndef USE_GRAPHIC_TEXT_GINE
    txt::PlaceholderRun txtSpan;
#else
    OHOS::Rosen::PlaceholderSpan txtSpan;
#endif
    Constants::ConvertPlaceholderRun(span, txtSpan);
#ifndef USE_GRAPHIC_TEXT_GINE
    builder_->AddPlaceholder(txtSpan);
#else
    builder_->AppendPlaceholder(txtSpan);
#endif
    return ++placeHolderIndex_;
}

void TxtParagraph::Build()
{
    CHECK_NULL_VOID(builder_);
#ifndef USE_GRAPHIC_TEXT_GINE
    paragraph_ = builder_->Build();
#else
    paragraph_ = builder_->CreateTypography();
#endif

    if (paraStyle_.leadingMargin) {
        SetIndents({ paraStyle_.leadingMargin->size.Width() });
    }
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
#ifndef USE_GRAPHIC_TEXT_GINE
        return std::max(paragraph_->GetLongestLine(), paragraph_->GetMaxIntrinsicWidth());
#else
        return std::max(paragraph_->GetActualWidth(), paragraph_->GetMaxIntrinsicWidth());
#endif
    }
#ifndef USE_GRAPHIC_TEXT_GINE
    return paragraph_->GetLongestLine();
#else
    return paragraph_->GetActualWidth();
#endif
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
#ifndef USE_GRAPHIC_TEXT_GINE
    return static_cast<float>(paragraph_->GetLongestLine());
#else
    return static_cast<float>(paragraph_->GetActualWidth());
#endif
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
#ifndef USE_GRAPHIC_TEXT_GINE
    auto* paragraphTxt = static_cast<txt::ParagraphTxt*>(paragraph_.get());
    CHECK_NULL_RETURN(paragraphTxt, 0);
    return paragraphTxt->GetLineCount();
#else
    CHECK_NULL_RETURN(paragraph_, 0);
    return paragraph_->GetLineCount();
#endif
}

void TxtParagraph::Paint(RSCanvas& canvas, float x, float y)
{
    CHECK_NULL_VOID(paragraph_);
#ifndef USE_ROSEN_DRAWING
    SkCanvas* skCanvas = canvas.GetImpl<RSSkCanvas>()->ExportSkCanvas();
    CHECK_NULL_VOID(skCanvas);
    paragraph_->Paint(skCanvas, x, y);
#else
    paragraph_->Paint(&canvas, x, y);
#endif
    if (paraStyle_.leadingMargin && paraStyle_.leadingMargin->pixmap) {
        auto canvasImage = PixelMapImage::Create(paraStyle_.leadingMargin->pixmap);
        auto pixelMapImage = DynamicCast<PixelMapImage>(canvasImage);
        CHECK_NULL_VOID(pixelMapImage);
        auto& rsCanvas = const_cast<RSCanvas&>(canvas);
        auto size = paraStyle_.leadingMargin->size;
        auto width = size.Width();
        auto height = size.Height();
        pixelMapImage->DrawRect(rsCanvas, ToRSRect(RectF(x, y, width, height)));
    }
}

void TxtParagraph::Paint(SkCanvas* skCanvas, float x, float y)
{
    CHECK_NULL_VOID(skCanvas);
#ifndef USE_ROSEN_DRAWING
    paragraph_->Paint(skCanvas, x, y);
#else
    LOGE("Drawing is not supported");
#endif
}

// ToDo:adjust index
int32_t TxtParagraph::GetGlyphIndexByCoordinate(const Offset& offset)
{
    if (!paragraph_) {
        return 0;
    }
    int32_t index;
#ifndef USE_GRAPHIC_TEXT_GINE
    index = static_cast<int32_t>(paragraph_->GetGlyphPositionAtCoordinate(offset.GetX(), offset.GetY()).position);
#else
    index = static_cast<int32_t>(paragraph_->GetGlyphIndexByCoordinate(offset.GetX(), offset.GetY()).index);
#endif
    return index;
}

bool TxtParagraph::ComputeOffsetForCaretUpstream(int32_t extent, CaretMetricsF& result)
{
    if (!paragraph_) {
        return false;
    }
    if (text_.empty() && placeHolderIndex_ == -1) {
        if (paragraph_->GetLineCount() > 0) {
            result.offset.Reset();
            result.height = paragraph_->GetHeight();
            return true;
        }
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
#ifndef USE_GRAPHIC_TEXT_GINE
    auto boxes = paragraph_->GetRectsForRange(
        prev, extent, txt::Paragraph::RectHeightStyle::kMax, txt::Paragraph::RectWidthStyle::kTight);
#else
    auto boxes = paragraph_->GetTextRectsByBoundary(
        prev, extent, Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM, Rosen::TextRectWidthStyle::TIGHT);
#endif
    while (boxes.empty() && !text_.empty()) {
        graphemeClusterLength *= 2;
        prev = extent - graphemeClusterLength;
        if (prev < 0) {
#ifndef USE_GRAPHIC_TEXT_GINE
            boxes = paragraph_->GetRectsForRange(
                0, extent, txt::Paragraph::RectHeightStyle::kMax, txt::Paragraph::RectWidthStyle::kTight);
#else
            boxes = paragraph_->GetTextRectsByBoundary(
                0, extent, Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM, Rosen::TextRectWidthStyle::TIGHT);
#endif
            break;
        }
#ifndef USE_GRAPHIC_TEXT_GINE
        boxes = paragraph_->GetRectsForRange(
            prev, extent, txt::Paragraph::RectHeightStyle::kMax, txt::Paragraph::RectWidthStyle::kTight);
#else
        boxes = paragraph_->GetTextRectsByBoundary(
            prev, extent, Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM, Rosen::TextRectWidthStyle::TIGHT);
#endif
    }
    if (boxes.empty()) {
        LOGD("boxes is empty.");
        return false;
    }

    const auto& textBox = *boxes.begin();
    // when text_ ends with a \n, return the top position of the next line.
    auto last = extent - placeHolderIndex_ - 1;
    auto index = static_cast<size_t>(last) == text_.length() ? last : extent;
    prevChar = text_[std::max(0, index - 1)];
    if (prevChar == NEWLINE_CODE) {
        // Return the start of next line.
        result.offset.SetX(MakeEmptyOffsetX());
#ifndef USE_GRAPHIC_TEXT_GINE
        result.offset.SetY(textBox.rect.fBottom);
        result.height = textBox.rect.fBottom - textBox.rect.fTop;
#else
        result.offset.SetY(textBox.rect.GetBottom());
        result.height = textBox.rect.GetBottom() - textBox.rect.GetTop();
#endif
        return true;
    }

#ifndef USE_GRAPHIC_TEXT_GINE
    bool isLtr = textBox.direction == txt::TextDirection::ltr;
#else
    bool isLtr = textBox.direction == Rosen::TextDirection::LTR;
#endif
    // Caret is within width of the downstream glyphs.
#ifndef USE_GRAPHIC_TEXT_GINE
    double caretStart = isLtr ? textBox.rect.fRight : textBox.rect.fLeft;
#else
    double caretStart = isLtr ? textBox.rect.GetRight() : textBox.rect.GetLeft();
#endif
    double offsetX = std::min(caretStart, paragraph_->GetMaxWidth());
    result.offset.SetX(offsetX);
#ifndef USE_GRAPHIC_TEXT_GINE
    result.offset.SetY(textBox.rect.fTop);
    result.height = textBox.rect.fBottom - textBox.rect.fTop;
#else
    result.offset.SetY(textBox.rect.GetTop());
    result.height = textBox.rect.GetBottom() - textBox.rect.GetTop();
#endif

    return true;
}

float TxtParagraph::MakeEmptyOffsetX()
{
    auto width = GetMaxWidth();
    switch (textAlign_) {
        case TextAlign::CENTER:
            return width * 0.5f;
        case TextAlign::END:
            return width;
        case TextAlign::START:
        default:
            return 0.0f;
    }
}

bool TxtParagraph::ComputeOffsetForCaretDownstream(int32_t extent, CaretMetricsF& result)
{
    if (!paragraph_ || static_cast<size_t>(extent) >= GetParagraphLength()) {
        return false;
    }

    result.Reset();
    const int32_t graphemeClusterLength = 1;
    const int32_t next = extent + graphemeClusterLength;
#ifndef USE_GRAPHIC_TEXT_GINE
    auto boxes = paragraph_->GetRectsForRange(
        extent, next, txt::Paragraph::RectHeightStyle::kMax, txt::Paragraph::RectWidthStyle::kTight);
#else
    auto boxes = paragraph_->GetTextRectsByBoundary(
        extent, next, Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM, Rosen::TextRectWidthStyle::TIGHT);
#endif
    if (boxes.empty()) {
        return false;
    }

    const auto& textBox = *boxes.begin();
#ifndef USE_GRAPHIC_TEXT_GINE
    bool isLtr = textBox.direction == txt::TextDirection::ltr;
#else
    bool isLtr = textBox.direction == Rosen::TextDirection::LTR;
#endif
    // Caret is within width of the downstream glyphs.
#ifndef USE_GRAPHIC_TEXT_GINE
    double caretStart = isLtr ? textBox.rect.fLeft : textBox.rect.fRight;
#else
    double caretStart = isLtr ? textBox.rect.GetLeft() : textBox.rect.GetRight();
#endif
    double offsetX = std::min(caretStart, paragraph_->GetMaxWidth());
    result.offset.SetX(offsetX);
#ifndef USE_GRAPHIC_TEXT_GINE
    result.offset.SetY(textBox.rect.fTop);
    result.height = textBox.rect.fBottom - textBox.rect.fTop;
#else
    result.offset.SetY(textBox.rect.GetTop());
    result.height = textBox.rect.GetBottom() - textBox.rect.GetTop();
#endif

    return true;
}

void TxtParagraph::GetRectsForRange(int32_t start, int32_t end, std::vector<RectF>& selectedRects)
{
#ifndef USE_GRAPHIC_TEXT_GINE
    CHECK_NULL_VOID(paragraph_);
    const auto& boxes = paragraph_->GetRectsForRange(
        start, end, txt::Paragraph::RectHeightStyle::kMax, txt::Paragraph::RectWidthStyle::kTight);
#else
    const auto& boxes = paragraph_->GetTextRectsByBoundary(
        start, end, Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM, Rosen::TextRectWidthStyle::TIGHT);
#endif
    if (boxes.empty()) {
        return;
    }
    for (const auto& box : boxes) {
        auto rect = Constants::ConvertSkRect(box.rect);
        RectF selectionRect(static_cast<float>(rect.Left()), static_cast<float>(rect.Top()),
            static_cast<float>(rect.Width()), static_cast<float>(rect.Height()));
        selectedRects.emplace_back(selectionRect);
    }
}

void TxtParagraph::GetRectsForPlaceholders(std::vector<RectF>& selectedRects)
{
    CHECK_NULL_VOID(paragraph_);
#ifndef USE_GRAPHIC_TEXT_GINE
    const auto& boxes = paragraph_->GetRectsForPlaceholders();
#else
    const auto& boxes = paragraph_->GetTextRectsOfPlaceholders();
#endif
    if (boxes.empty()) {
        return;
    }
    for (const auto& box : boxes) {
        auto rect = Constants::ConvertSkRect(box.rect);
        RectF selectionRect(static_cast<float>(rect.Left()), static_cast<float>(rect.Top()),
            static_cast<float>(rect.Width()), static_cast<float>(rect.Height()));
        selectedRects.emplace_back(selectionRect);
    }
}

bool TxtParagraph::CalcCaretMetricsByPosition(
    int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity)
{
    CaretMetricsF metrics;
    bool computeSuccess = false;
    if (textAffinity == TextAffinity::DOWNSTREAM) {
        computeSuccess =
            ComputeOffsetForCaretDownstream(extent, metrics) || ComputeOffsetForCaretUpstream(extent, metrics);
    } else {
        computeSuccess =
            ComputeOffsetForCaretUpstream(extent, metrics) || ComputeOffsetForCaretDownstream(extent, metrics);
    }
    if (computeSuccess) {
        if (metrics.height <= 0 || std::isnan(metrics.height)) {
            // The reason may be text lines is exceed the paragraph maxline.
            LOGD("Illegal caret height. Consider release restriction of paragraph max_line.");
            return false;
        }
        caretCaretMetric = metrics;
        return true;
    }
    return false;
}

bool TxtParagraph::CalcCaretMetricsByPosition(
    int32_t extent, CaretMetricsF& caretCaretMetric, const OffsetF& lastTouchOffset)
{
    CaretMetricsF metricsUpstream;
    CaretMetricsF metricsDownstream;
    auto downStreamSuccess = ComputeOffsetForCaretDownstream(extent, metricsDownstream);
    auto upStreamSuccess = ComputeOffsetForCaretUpstream(extent, metricsUpstream);
    if (downStreamSuccess || upStreamSuccess) {
        if (metricsDownstream.offset.GetY() < lastTouchOffset.GetY() && downStreamSuccess) {
            caretCaretMetric = metricsDownstream;
        } else if (upStreamSuccess) {
            caretCaretMetric = metricsUpstream;
        } else {
            caretCaretMetric = metricsDownstream;
        }
        return true;
    }
    return false;
}

void TxtParagraph::SetIndents(const std::vector<float>& indents)
{
#ifndef USE_GRAPHIC_TEXT_GINE
    auto* paragraphTxt = static_cast<txt::ParagraphTxt*>(paragraph_.get());
#else
    auto* paragraphTxt = static_cast<OHOS::Rosen::Typography*>(paragraph_.get());
#endif
    CHECK_NULL_VOID(paragraphTxt);
    paragraphTxt->SetIndents(indents);
}

bool TxtParagraph::GetWordBoundary(int32_t offset, int32_t& start, int32_t& end)
{
#ifndef USE_GRAPHIC_TEXT_GINE
    auto* paragraphTxt = static_cast<txt::ParagraphTxt*>(paragraph_.get());
#else
    auto* paragraphTxt = static_cast<OHOS::Rosen::Typography*>(paragraph_.get());
#endif
    CHECK_NULL_RETURN(paragraphTxt, false);
#ifndef USE_GRAPHIC_TEXT_GINE
    auto range = paragraphTxt->GetWordBoundary(static_cast<size_t>(offset));
    start = static_cast<int32_t>(range.start);
    end = static_cast<int32_t>(range.end);
#else
    auto range = paragraphTxt->GetWordBoundaryByIndex(static_cast<size_t>(offset));
    start = static_cast<int32_t>(range.leftIndex);
    end = static_cast<int32_t>(range.rightIndex);
#endif
    return true;
}

std::u16string TxtParagraph::GetParagraphText()
{
    return text_;
}
} // namespace OHOS::Ace::NG
