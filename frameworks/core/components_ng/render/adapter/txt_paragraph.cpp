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

#include "base/log/ace_performance_monitor.h"
#include "core/components/font/constants_converter.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/adapter/txt_font_collection.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
const std::u16string ELLIPSIS = u"\u2026";
const std::u16string SYMBOL_TRANS = u"\uF0001";
const int32_t LENGTH_INCREMENT = 2;
constexpr int32_t THOUSAND = 1000;
constexpr char16_t NEWLINE_CODE = u'\n';
constexpr float TEXT_SPLIT_RATIO = 0.6f;
} // namespace
RefPtr<Paragraph> Paragraph::Create(const ParagraphStyle& paraStyle, const RefPtr<FontCollection>& fontCollection)
{
    auto txtFontCollection = DynamicCast<TxtFontCollection>(fontCollection);
    CHECK_NULL_RETURN(txtFontCollection, nullptr);
    auto sharedFontCollection = txtFontCollection->GetRawFontCollection();
    return AceType::MakeRefPtr<TxtParagraph>(paraStyle, sharedFontCollection);
}

RefPtr<Paragraph> Paragraph::Create(void* rsParagraph)
{
    return AceType::MakeRefPtr<TxtParagraph>(rsParagraph);
}

void TxtParagraph::SetParagraphSymbolAnimation(const RefPtr<FrameNode>& frameNode)
{
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(frameNode->GetRenderContext());
    CHECK_NULL_VOID(context);
    auto rsNode = context->GetRSNode();
    rsSymbolAnimation_ = RSSymbolAnimation();
    rsSymbolAnimation_.SetNode(rsNode);

    std::function<bool(const std::shared_ptr<RSSymbolAnimationConfig>& symbolAnimationConfig)> scaleCallback =
        std::bind(&RSSymbolAnimation::SetSymbolAnimation, rsSymbolAnimation_, std::placeholders::_1);

    SetAnimation(scaleCallback);
}

bool TxtParagraph::IsValid()
{
    return GetParagraph() != nullptr;
}

void TxtParagraph::CreateBuilder()
{
    ACE_TEXT_SCOPED_TRACE("TxtParagraph::CreateBuilder");
    CHECK_NULL_VOID(!hasExternalParagraph_);
    placeholderPosition_.clear();
    Rosen::TypographyStyle style;
    ConvertTypographyStyle(style, paraStyle_);
    builder_ = Rosen::TypographyCreate::Create(style, fontCollection_);
}

void TxtParagraph::ConvertTypographyStyle(Rosen::TypographyStyle& style, const ParagraphStyle& paraStyle)
{
    style.textDirection = Constants::ConvertTxtTextDirection(paraStyle.direction);
    style.textAlign = Constants::ConvertTxtTextAlign(paraStyle.align);
    style.verticalAlignment = Constants::ConvertTxtTextVerticalAlign(paraStyle.verticalAlign);
    style.maxLines = paraStyle.maxLines == UINT32_MAX ? UINT32_MAX - 1 : paraStyle.maxLines;
    style.fontSize = paraStyle.fontSize; // Rosen style.fontSize
    style.wordBreakType = static_cast<Rosen::WordBreakType>(paraStyle.wordBreak);
    style.ellipsisModal = static_cast<Rosen::EllipsisModal>(paraStyle.ellipsisMode);
    style.textSplitRatio = TEXT_SPLIT_RATIO;
    style.breakStrategy = static_cast<Rosen::BreakStrategy>(paraStyle.lineBreakStrategy);
    style.lineStyleHalfLeading = paraStyle.halfLeading;
    style.isEndAddParagraphSpacing = paraStyle.isEndAddParagraphSpacing;
    style.paragraphSpacing = paraStyle.paragraphSpacing.ConvertToPx();
    style.locale = paraStyle.fontLocale;
    if (paraStyle.textOverflow == TextOverflow::ELLIPSIS) {
        style.ellipsis = ELLIPSIS;
    }
    style.enableAutoSpace = paraStyle.enableAutoSpacing;
    style.defaultTextStyleUid = paraStyle.textStyleUid;
    if (paraStyle.isOnlyBetweenLines) {
        style.textHeightBehavior =
            paraStyle.isFirstParagraphLineSpacing
                ? static_cast<OHOS::Rosen::TextHeightBehavior>(TextHeightBehavior::DISABLE_ALL)
                : static_cast<OHOS::Rosen::TextHeightBehavior>(TextHeightBehavior::DISABLE_LAST_ASCENT);
    }
    style.isTrailingSpaceOptimized = paraStyle.optimizeTrailingSpace;
#if !defined(FLUTTER_2_5) && !defined(NEW_SKIA)
    // keep WordBreak define same with WordBreakType in minikin
    style.wordBreakType = static_cast<Rosen::WordBreakType>(paraStyle.wordBreak);
    style.breakStrategy = static_cast<Rosen::BreakStrategy>(paraStyle.lineBreakStrategy);
#endif
}

void TxtParagraph::PushStyle(const TextStyle& style)
{
    ACE_TEXT_SCOPED_TRACE("TxtParagraph::PushStyle");
    CHECK_NULL_VOID(!hasExternalParagraph_);
    if (!builder_) {
        CreateBuilder();
    }

    Rosen::TextStyle txtStyle;
    textAlign_ = style.GetTextAlign();
    Constants::ConvertTxtStyle(style, PipelineContext::GetCurrentContextSafelyWithCheck(), txtStyle);
    builder_->PushStyle(txtStyle);
}

void TxtParagraph::PopStyle()
{
    ACE_TEXT_SCOPED_TRACE("TxtParagraph::PopStyle");
    CHECK_NULL_VOID(!hasExternalParagraph_ && builder_);
    builder_->PopStyle();
}

void TxtParagraph::AddText(const std::u16string& text)
{
    ACE_TEXT_SCOPED_TRACE("TxtParagraph::AddText:%d", static_cast<uint32_t>(text.length()));
    if (!builder_) {
        CreateBuilder();
    }
    text_ += text;
    CHECK_NULL_VOID(!hasExternalParagraph_);
    builder_->AppendText(text);
}

void TxtParagraph::AddSymbol(const std::uint32_t& symbolId)
{
    ACE_TEXT_SCOPED_TRACE("TxtParagraph::AddSymbol");
    CHECK_NULL_VOID(!hasExternalParagraph_);
    if (!builder_) {
        CreateBuilder();
    }
    text_ += SYMBOL_TRANS;
    builder_->AppendSymbol(symbolId);
}

int32_t TxtParagraph::AddPlaceholder(const PlaceholderRun& span)
{
    ACE_TEXT_SCOPED_TRACE("TxtParagraph::AddPlaceholder");
    CHECK_NULL_RETURN(!hasExternalParagraph_, 0);
    if (!builder_) {
        CreateBuilder();
    }
    OHOS::Rosen::PlaceholderSpan txtSpan;
    Constants::ConvertPlaceholderRun(span, txtSpan);
    builder_->AppendPlaceholder(txtSpan);
    auto position = static_cast<size_t>(placeholderCnt_) + text_.length();
    placeholderPosition_.emplace_back(position);
    return placeholderCnt_++;
}

void TxtParagraph::Build()
{
    int32_t id = -1;
    if (SystemProperties::GetAcePerformanceMonitorEnabled()) {
        id = Container::CurrentId();
    }
    OTHER_DURATION(id);
    ACE_TEXT_SCOPED_TRACE("TxtParagraph::Build");
    CHECK_NULL_VOID(!hasExternalParagraph_ && builder_);
    paragraph_ = builder_->CreateTypography();
}

uint32_t TxtParagraph::destructCount = 0;

TxtParagraph::~TxtParagraph()
{
    if (destructCount % THOUSAND == 0) {
        TAG_LOGW(AceLogTag::ACE_TEXT,
            "destroy TxtParagraph with placeholderCnt_ %{public}d, textAlign_ %{public}d, count %{public}u",
            placeholderCnt_, static_cast<int>(textAlign_), destructCount);
    }
    destructCount++;
}

void TxtParagraph::Reset()
{
    paragraph_.reset();
    builder_.reset();
    fontCollection_.reset();
}

void TxtParagraph::Layout(float width)
{
    int32_t id = -1;
    if (SystemProperties::GetAcePerformanceMonitorEnabled()) {
        id = Container::CurrentId();
    }
    OTHER_DURATION(id);
    ACE_TEXT_SCOPED_TRACE("TxtParagraph::Layout, width:%f", width);
    CHECK_NULL_VOID(!hasExternalParagraph_ && paragraph_);
    paragraph_->Layout(width);
}

void TxtParagraph::ReLayout(float width, const ParagraphStyle& paraStyle, const std::vector<TextStyle>& textStyles)
{
    CHECK_NULL_VOID(!hasExternalParagraph_ && paragraph_);
    paraStyle_ = paraStyle;
    std::stringstream nodeID;
    nodeID << "[";

    std::vector<Rosen::TextStyle> txtStyles;
    for (auto textStyle : textStyles) {
        Rosen::TextStyle txtStyle;
        Constants::ConvertTxtStyle(textStyle, PipelineContext::GetCurrentContextSafelyWithCheck(), txtStyle);
        nodeID << std::to_string(txtStyle.textStyleUid);
        nodeID << ", ";
        txtStyles.emplace_back(txtStyle);
    }
    nodeID << "]";
    if (SystemProperties::GetTextTraceEnabled() && !txtStyles.empty()) {
        ACE_TEXT_SCOPED_TRACE(
            "TxtParagraph::ReLayout node size:%d id:%s paraStyle id:%d paragraphStyleBitmap:%s width:%f",
            static_cast<uint32_t>(txtStyles.size()), nodeID.str().c_str(), paraStyle.textStyleUid,
            textStyles.front().GetReLayoutParagraphStyleBitmap().to_string().c_str(), width);
    }
    Rosen::TypographyStyle style;
    ConvertTypographyStyle(style, paraStyle_);
    auto bitmap = textStyles.front().GetReLayoutParagraphStyleBitmap();
    auto size = std::min(bitmap.size(), style.relayoutChangeBitmap.size());
    for (size_t i = 0; i < size; ++i) {
        style.relayoutChangeBitmap.set(i, bitmap.test(i));
    }
    paragraph_->Relayout(width, style, txtStyles);
}

void TxtParagraph::ReLayoutForeground(const TextStyle& textStyle)
{
    CHECK_NULL_VOID(!hasExternalParagraph_ && paragraph_);
    Rosen::TextStyle txtStyle;
    Constants::ConvertForegroundPaint(textStyle, paragraph_->GetMaxWidth(), paragraph_->GetHeight(), txtStyle);
    std::vector<Rosen::TextStyle> txtStyles;
    txtStyles.emplace_back(txtStyle);
    Rosen::TypographyStyle style;
    ConvertTypographyStyle(style, paraStyle_);
    bool isTextStyleChange = std::any_of(txtStyles.begin(), txtStyles.end(), [](const Rosen::TextStyle& style) {
        return style.relayoutChangeBitmap.any();
    });
    if (SystemProperties::GetTextTraceEnabled()) {
        TAG_LOGI(AceLogTag::ACE_TEXT,
            "ReLayoutForeground id:%{public}d ReLayoutForeground: %{public}s parid:%{public}d "
            "isTextStyleChange:%{public}d",
            textStyle.GetTextStyleUid(), txtStyles.front().relayoutChangeBitmap.to_string().c_str(),
            paraStyle_.textStyleUid, isTextStyleChange);
    }
    paragraph_->Relayout(paragraph_->GetMaxWidth(), style, txtStyles);
}

float TxtParagraph::GetHeight()
{
    auto paragrah = GetParagraph();
    CHECK_NULL_RETURN(paragrah, 0.0f);
    return static_cast<float>(paragrah->GetHeight());
}

float TxtParagraph::GetTextWidth()
{
    auto paragrah = GetParagraph();
    CHECK_NULL_RETURN(paragrah, 0.0f);
    if (GetLineCount() == 1) {
        return std::max(paragrah->GetLongestLineWithIndent(), paragrah->GetMaxIntrinsicWidth());
    }
    return paragrah->GetLongestLineWithIndent();
}

float TxtParagraph::GetMaxIntrinsicWidth()
{
    auto paragrah = GetParagraph();
    CHECK_NULL_RETURN(paragrah, 0.0f);
    return static_cast<float>(paragrah->GetMaxIntrinsicWidth());
}

bool TxtParagraph::DidExceedMaxLines()
{
    auto paragrah = GetParagraph();
    CHECK_NULL_RETURN(paragrah, false);
    return paragrah->DidExceedMaxLines();
}

float TxtParagraph::GetLongestLine()
{
    auto paragrah = GetParagraph();
    CHECK_NULL_RETURN(paragrah, 0.0f);
    return static_cast<float>(paragrah->GetActualWidth());
}

float TxtParagraph::GetLongestLineWithIndent()
{
    auto paragrah = GetParagraph();
    CHECK_NULL_RETURN(paragrah, 0.0f);
    return static_cast<float>(paragrah->GetLongestLineWithIndent());
}

float TxtParagraph::GetMaxWidth()
{
    auto paragrah = GetParagraph();
    CHECK_NULL_RETURN(paragrah, 0.0f);
    return static_cast<float>(paragrah->GetMaxWidth());
}

float TxtParagraph::GetAlphabeticBaseline()
{
    auto paragrah = GetParagraph();
    CHECK_NULL_RETURN(paragrah, 0.0f);
    return static_cast<float>(paragrah->GetAlphabeticBaseline());
}

size_t TxtParagraph::GetLineCount()
{
    auto paragrah = GetParagraph();
    CHECK_NULL_RETURN(paragrah, 0);
    return paragrah->GetLineCount();
}

float TxtParagraph::GetCharacterWidth(int32_t index)
{
    auto paragrah = GetParagraph();
    CHECK_NULL_RETURN(paragrah, 0.0f);
    auto next = index + 1;
    auto boxes = paragrah->GetTextRectsByBoundary(
        index, next, Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM, Rosen::TextRectWidthStyle::TIGHT);
    if (boxes.empty()) {
        return 0.0f;
    }
    const auto& textBox = *boxes.begin();
    return textBox.rect.GetRight() - textBox.rect.GetLeft();
}

void TxtParagraph::Paint(RSCanvas& canvas, float x, float y)
{
    ACE_TEXT_SCOPED_TRACE("TxtParagraph::Paint");
    auto paragrah = GetParagraph();
    CHECK_NULL_VOID(paragrah);
    paragrah->Paint(&canvas, x, y);
    if (paraStyle_.leadingMargin && paraStyle_.leadingMargin->pixmap) {
        CalculateLeadingMarginOffest(x, y);
        auto canvasImage = PixelMapImage::Create(paraStyle_.leadingMargin->pixmap);
        auto pixelMapImage = DynamicCast<PixelMapImage>(canvasImage);
        CHECK_NULL_VOID(pixelMapImage);
        auto& rsCanvas = const_cast<RSCanvas&>(canvas);
        auto size = paraStyle_.leadingMargin->size;
        auto width = static_cast<float>(size.Width().ConvertToPx());
        auto height = static_cast<float>(size.Height().ConvertToPx());
        pixelMapImage->DrawRect(rsCanvas, ToRSRect(RectF(x, y, width, height)));
    }
}

void TxtParagraph::CalculateLeadingMarginOffest(float& x, float& y)
{
    auto paragrah = GetParagraph();
    CHECK_NULL_VOID(paragrah);
    auto lineCount = static_cast<int32_t>(GetLineCount());
    CHECK_NULL_VOID(lineCount);
    auto firstLineMetrics = GetLineMetrics(0);
    auto size = paraStyle_.leadingMargin->size;
    auto start = x;
    if (paraStyle_.direction == TextDirection::RTL) {
        x += static_cast<float>(firstLineMetrics.x + firstLineMetrics.width);
    } else {
        x += static_cast<float>(firstLineMetrics.x - size.Width().ConvertToPx());
    }
    x = std::max(start, x);
    auto sizeRect =
        SizeF(static_cast<float>(size.Width().ConvertToPx()), static_cast<float>(size.Height().ConvertToPx()));
    y += Alignment::GetAlignPosition(
        SizeF(sizeRect.Width(), static_cast<float>(firstLineMetrics.height)), sizeRect, paraStyle_.leadingMarginAlign)
             .GetY();
}

// ToDo:adjust index
int32_t TxtParagraph::GetGlyphIndexByCoordinate(const Offset& offset, bool isSelectionPos)
{
    auto paragrah = GetParagraph();
    if (!paragrah) {
        return 0;
    }
    int32_t index = static_cast<int32_t>(paragrah->GetGlyphIndexByCoordinate(offset.GetX(), offset.GetY()).index);
    if (isSelectionPos) {
        AdjustIndexForward(offset, true, index);
    }
    return index;
}

PositionWithAffinity TxtParagraph::GetGlyphPositionAtCoordinate(const Offset& offset)
{
    PositionWithAffinity finalResult(0, TextAffinity::UPSTREAM);
    auto paragrah = GetParagraph();
    CHECK_NULL_RETURN(paragrah, finalResult);
    auto result = paragrah->GetGlyphIndexByCoordinate(offset.GetX(), offset.GetY());
    finalResult.position_ = result.index;
    finalResult.affinity_ = static_cast<TextAffinity>(result.affinity);
    return finalResult;
}

void TxtParagraph::AdjustIndexForward(const Offset& offset, bool compareOffset, int32_t& index)
{
    if (index < 0) {
        index = 0;
        return;
    }
    auto totalLen = static_cast<size_t>(placeholderCnt_) + text_.length();
    if (static_cast<unsigned int>(index) == totalLen) {
        --index;
        AdjustIndexForward(offset, false, index);
        return;
    }
    auto next = index + 1;
    auto start = 0;
    auto end = 0;
    if (IsIndexInEmoji(index, start, end)) {
        index = start;
        next = end;
    }
    auto paragrah = GetParagraph();
    auto boxes = paragrah->GetTextRectsByBoundary(
        index, next, Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM, Rosen::TextRectWidthStyle::TIGHT);
    if (boxes.empty()) {
        if (IsTargetCharAtIndex(NEWLINE_CODE, index)) {
            --index;
            AdjustIndexForward(offset, false, index);
        } else if (IsIndexAtLineEnd(offset, index)) {
            --index;
        }
        return;
    }
    const auto& textBox = *boxes.begin();
    auto left = textBox.rect.GetLeft();
    auto right = textBox.rect.GetRight();
    auto top = textBox.rect.GetTop();
    if (compareOffset && (LessNotEqual(offset.GetY(), top) || LessNotEqual(offset.GetX(), left))) {
        --index;
        AdjustIndexForward(offset, false, index);
    } else if (NearEqual(left, right)) {
        --index;
        AdjustIndexForward(offset, false, index);
    }
}

bool TxtParagraph::CalCulateAndCheckPreIsPlaceholder(int32_t index, int32_t& extent)
{
    for (auto placeholderIndex : placeholderPosition_) {
        if (placeholderIndex == static_cast<size_t>(index)) {
            return true;
        } else if (placeholderIndex < static_cast<size_t>(index)) {
            extent--;
        }
    }
    return false;
}

bool TxtParagraph::ComputeOffsetForCaretUpstream(int32_t extent, CaretMetricsF& result, bool needLineHighest)
{
    auto paragrah = GetParagraph();
    if (!paragrah) {
        return false;
    }
    if (empty()) {
        return HandleCaretWhenEmpty(result, needLineHighest);
    }
    if (static_cast<size_t>(extent) > GetParagraphLength()) {
        extent = static_cast<int32_t>(GetParagraphLength());
    }

    extent = AdjustIndexForEmoji(extent);
    char16_t prevChar = 0;
    if (static_cast<size_t>(extent) <= text_.length()) {
        prevChar = text_[std::max(0, extent - 1)];
    }

    result.Reset();
    int32_t graphemeClusterLength = StringUtils::NotInUtf16Bmp(prevChar) ? 2 : 1;
    int32_t prev = extent - graphemeClusterLength;
    auto boxes = paragrah->GetTextRectsByBoundary(prev, extent,
        needLineHighest ? Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM : Rosen::TextRectHeightStyle::TIGHT,
        Rosen::TextRectWidthStyle::TIGHT);
    while (boxes.empty() && !text_.empty()) {
        graphemeClusterLength *= 2;
        prev = extent - graphemeClusterLength;
        if (prev < 0) {
            boxes = paragrah->GetTextRectsByBoundary(0, extent,
                needLineHighest ? Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM : Rosen::TextRectHeightStyle::TIGHT,
                Rosen::TextRectWidthStyle::TIGHT);
            break;
        }
        boxes = paragrah->GetTextRectsByBoundary(prev, static_cast<size_t>(extent),
            needLineHighest ? Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM : Rosen::TextRectHeightStyle::TIGHT,
            Rosen::TextRectWidthStyle::TIGHT);
    }
    if (boxes.empty()) {
        return false;
    }

    const auto& textBox = boxes.back();

    // when text_ ends with a \n, return the top position of the next line.
    auto preIsPlaceholder = CalCulateAndCheckPreIsPlaceholder(extent - 1, extent);
    prevChar = text_[std::max(0, extent - 1)];
    if (prevChar == NEWLINE_CODE && !text_[static_cast<size_t>(extent)] && !preIsPlaceholder) {
        // Return the start of next line.
        float y = 0.0f;
        y = textBox.rect.GetBottom();
        result.height = textBox.rect.GetBottom() - textBox.rect.GetTop();
        bool isLtr = textBox.direction == Rosen::TextDirection::LTR;
        if (LessNotEqual(y, paragrah->GetHeight())) {
            result.offset.SetX(MakeEmptyOffsetX(isLtr));
            result.offset.SetY(y);
            return true;
        }
    }

    if (isnan(textBox.rect.GetRight()) || isnan(textBox.rect.GetLeft())) {
        LOGI("Right or left of textBox is NaN.");
        return false;
    }
    bool isLtr = textBox.direction == Rosen::TextDirection::LTR;
    // Caret is within width of the downstream glyphs.
    double caretStart = isLtr ? textBox.rect.GetRight() : textBox.rect.GetLeft();
    float offsetX = std::min(
        static_cast<float>(caretStart), std::max(GetLongestLine(), static_cast<float>(paragrah->GetMaxWidth())));
    result.offset.SetX(offsetX);
    result.offset.SetY(textBox.rect.GetTop());
    result.height = textBox.rect.GetBottom() - textBox.rect.GetTop();

    return true;
}

float TxtParagraph::MakeEmptyOffsetX(bool isLtr)
{
    auto width = GetMaxWidth();
    switch (textAlign_) {
        case TextAlign::CENTER:
            return width * 0.5f;
        case TextAlign::END:
            return isLtr ? width : 0.0f;
        case TextAlign::START:
        default:
            return isLtr ? 0.0f : width;
    }
}

bool TxtParagraph::ComputeOffsetForCaretDownstream(int32_t extent, CaretMetricsF& result, bool needLineHighest)
{
    auto paragrah = GetParagraph();
    if (!paragrah || static_cast<size_t>(extent) >= GetParagraphLength()) {
        return false;
    }

    result.Reset();
    auto getTextRects = [parapraph = paragrah, needLineHighest](int32_t extent, int32_t next) {
        return parapraph->GetTextRectsByBoundary(extent, next,
            needLineHighest ? Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM : Rosen::TextRectHeightStyle::TIGHT,
            Rosen::TextRectWidthStyle::TIGHT);
    };
    extent = AdjustIndexForEmoji(extent);
    auto boxes = getTextRects(extent, extent + 1);
    if (boxes.empty() && !text_.empty()) {
        boxes = getTextRects(extent, extent + LENGTH_INCREMENT);

        int32_t start = 0;
        int32_t end = 0;
        // it could be emoji.
        if (boxes.empty() && GetWordBoundary(extent, start, end)) {
            boxes = getTextRects(extent, end);
        }
    }
    
    if (boxes.empty()) {
        return false;
    }

    const auto& textBox = *boxes.begin();
    bool isLtr = textBox.direction == Rosen::TextDirection::LTR;
    double caretStart = isLtr ? textBox.rect.GetLeft() : textBox.rect.GetRight();
    // Caret is within width of the downstream glyphs.
    double offsetX = std::min(caretStart, paragrah->GetMaxWidth());
    result.offset.SetX(offsetX);
    result.offset.SetY(textBox.rect.GetTop());
    result.height = textBox.rect.GetBottom() - textBox.rect.GetTop();

    return true;
}

void TxtParagraph::GetRectsForRange(int32_t start, int32_t end, std::vector<RectF>& selectedRects)
{
    auto adjustStart = AdjustIndexForEmoji(start);
    auto adjustEnd = AdjustIndexForEmoji(end);
    GetRectsForRangeInner(adjustStart, adjustEnd, selectedRects, RectHeightPolicy::COVER_LINE);
}

std::pair<size_t, size_t> TxtParagraph::GetEllipsisTextRange()
{
    auto paragrah = GetParagraph();
    CHECK_NULL_RETURN(paragrah, std::make_pair(std::numeric_limits<size_t>::max(), 0));
    const auto& range = paragrah->GetEllipsisTextRange();
    auto start = std::min(range.leftIndex, range.rightIndex);
    auto end = std::max(range.leftIndex, range.rightIndex);
    return std::make_pair(start, end);
}

void TxtParagraph::GetTightRectsForRange(int32_t start, int32_t end, std::vector<RectF>& selectedRects)
{
    auto adjustStart = AdjustIndexForEmoji(start);
    auto adjustEnd = AdjustIndexForEmoji(end);
    GetRectsForRangeInner(adjustStart, adjustEnd, selectedRects, RectHeightPolicy::COVER_TEXT);
}

void TxtParagraph::GetRectsForRangeInner(int32_t start, int32_t end, std::vector<RectF>& selectedRects,
    RectHeightPolicy rectHeightPolicy)
{
    auto paragrah = GetParagraph();
    CHECK_NULL_VOID(paragrah);
    auto heightStyle = rectHeightPolicy == RectHeightPolicy::COVER_TEXT
        ? Rosen::TextRectHeightStyle::TIGHT
        : Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM;
    const auto& boxes = paragrah->GetTextRectsByBoundary(start, end, heightStyle, Rosen::TextRectWidthStyle::TIGHT);
    if (boxes.empty()) {
        return;
    }
    for (const auto& box : boxes) {
        auto rect = Constants::ConvertSkRect(box.rect);
        RectF selectionRect(static_cast<float>(rect.Left()), static_cast<float>(rect.Top()),
            static_cast<float>(std::abs(rect.Width())), static_cast<float>(rect.Height()));
        selectedRects.emplace_back(selectionRect);
    }
}

void TxtParagraph::TxtGetRectsForRange(int32_t start, int32_t end,
    RectHeightStyle heightStyle, RectWidthStyle widthStyle,
    std::vector<RectF>& selectedRects, std::vector<TextDirection>& textDirections)
{
    auto paragrah = GetParagraph();
    CHECK_NULL_VOID(paragrah);
    const auto& boxes = paragrah->GetTextRectsByBoundary(
        start, end, Constants::ConvertTxtRectHeightStyle(heightStyle), Constants::ConvertTxtRectWidthStyle(widthStyle));
    if (boxes.empty()) {
        return;
    }
    for (const auto& box : boxes) {
        auto rect = Constants::ConvertSkRect(box.rect);
        auto textDirection = box.direction;
        RectF selectionRect(static_cast<float>(rect.Left()), static_cast<float>(rect.Top()),
            static_cast<float>(rect.Width()), static_cast<float>(rect.Height()));
        selectedRects.emplace_back(selectionRect);
        textDirections.emplace_back(static_cast<OHOS::Ace::TextDirection>(textDirection));
    }
}

int32_t TxtParagraph::AdjustIndexForEmoji(int32_t index)
{
    int32_t start = 0;
    int32_t end = 0;
    if (IsIndexInEmoji(index, start, end)) {
        return end;
    }
    return index;
}

bool TxtParagraph::IsIndexInEmoji(int32_t index, int32_t& emojiStart, int32_t& emojiEnd)
{
    auto paragrah = GetParagraph();
    CHECK_NULL_RETURN(paragrah, false);
    int32_t start = 0;
    int32_t end = 0;
    if (!GetWordBoundary(index, start, end)) {
        return false;
    }
    std::vector<RectF> selectedRects;
    // if index in emoji or the first or the last, selectedRects is empty and
    // 'end' will be emoji's end index or 0 or the max index.
    GetRectsForRangeInner(index, end, selectedRects);
    if (selectedRects.empty()) {
        emojiStart = start;
        emojiEnd = end;
        return true;
    }
    return false;
}

void TxtParagraph::GetRectsForPlaceholders(std::vector<RectF>& selectedRects)
{
    auto paragrah = GetParagraph();
    CHECK_NULL_VOID(paragrah);
    const auto& boxes = paragrah->GetTextRectsOfPlaceholders();
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
    int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity, bool needLineHighest)
{
    CaretMetricsF metrics;
    bool computeSuccess = false;
    if (textAffinity == TextAffinity::DOWNSTREAM) {
        computeSuccess = ComputeOffsetForCaretDownstream(extent, metrics, needLineHighest) ||
                         ComputeOffsetForCaretUpstream(extent, metrics, needLineHighest);
    } else {
        computeSuccess = ComputeOffsetForCaretUpstream(extent, metrics, needLineHighest) ||
                         ComputeOffsetForCaretDownstream(extent, metrics, needLineHighest);
    }
    if (computeSuccess) {
        if (metrics.height <= 0 || std::isnan(metrics.height)) {
            // The reason may be text lines is exceed the paragraph maxline.
            return false;
        }
        caretCaretMetric = metrics;
        return true;
    }
    return false;
}

bool TxtParagraph::CalcCaretMetricsByPosition(
    int32_t extent, CaretMetricsF& caretCaretMetric, const OffsetF& lastTouchOffset, TextAffinity& textAffinity)
{
    CaretMetricsF metricsUpstream;
    CaretMetricsF metricsDownstream;
    auto downStreamSuccess = ComputeOffsetForCaretDownstream(extent, metricsDownstream);
    auto upStreamSuccess = ComputeOffsetForCaretUpstream(extent, metricsUpstream);
    if (downStreamSuccess || upStreamSuccess) {
        if ((metricsDownstream.offset.GetY() < lastTouchOffset.GetY()) && downStreamSuccess) {
            caretCaretMetric = metricsDownstream;
            textAffinity = TextAffinity::DOWNSTREAM;
        } else if (upStreamSuccess) {
            caretCaretMetric = metricsUpstream;
            textAffinity = TextAffinity::UPSTREAM;
        } else {
            caretCaretMetric = metricsDownstream;
            textAffinity = TextAffinity::DOWNSTREAM;
        }
        return true;
    }
    textAffinity = TextAffinity::DOWNSTREAM;
    return false;
}

void TxtParagraph::SetIndents(const std::vector<float>& indents)
{
    auto* paragraphTxt = static_cast<OHOS::Rosen::Typography*>(GetParagraph());
    CHECK_NULL_VOID(paragraphTxt);
    paragraphTxt->SetIndents(indents);
}

bool TxtParagraph::GetWordBoundary(int32_t offset, int32_t& start, int32_t& end)
{
    auto paragrah = GetParagraph();
    CHECK_NULL_RETURN(paragrah, false);
    auto* paragraphTxt = static_cast<OHOS::Rosen::Typography*>(paragrah);
    CHECK_NULL_RETURN(paragraphTxt, false);
    auto range = paragraphTxt->GetWordBoundaryByIndex(static_cast<size_t>(offset));
    start = static_cast<int32_t>(range.leftIndex);
    end = static_cast<int32_t>(range.rightIndex);
    return true;
}

void TxtParagraph::HandleTextAlign(CaretMetricsF& result, TextAlign align)
{
    auto width = GetMaxWidth();
    float offsetX = 0.0f;
    switch (align) {
        case TextAlign::CENTER:
            offsetX = width * 0.5f;
            break;
        case TextAlign::END:
            offsetX = width;
            break;
        case TextAlign::START:
        default:
            break;
    }
    result.offset.SetX(offsetX);
}

void TxtParagraph::HandleLeadingMargin(CaretMetricsF& result, LeadingMargin leadingMargin)
{
    result.offset.SetX(leadingMargin.size.Width().ConvertToPx());
}

Rosen::TextRectHeightStyle TxtParagraph::GetHeightStyle(bool needLineHighest)
{
    return Rosen::TextRectHeightStyle::TIGHT;
}

bool TxtParagraph::HandleCaretWhenEmpty(CaretMetricsF& result, bool needLineHighest)
{
    auto paragrah = GetParagraph();
    if (!paragrah || paragrah->GetLineCount() == 0) {
        return false;
    }

    result.offset.Reset();
    auto boxes = paragrah->GetTextRectsByBoundary(0, 1, GetHeightStyle(needLineHighest),
        Rosen::TextRectWidthStyle::TIGHT);
    if (boxes.empty()) {
        result.height = paragrah->GetHeight();
        auto lineHeight = paraStyle_.lineHeight;
        if (lineHeight.IsValid()) {
            result.offset.SetY(std::max(lineHeight.ConvertToPx() - result.height, 0.0));
        }
    } else {
        const auto& textBox = boxes.back();
        result.height = textBox.rect.GetBottom() - textBox.rect.GetTop();
        result.offset.SetY(textBox.rect.GetTop());
    }

    auto textAlign = paraStyle_.align;
    if (paraStyle_.direction == TextDirection::RTL) {
        if (textAlign == TextAlign::START) {
            textAlign = TextAlign::END;
        } else if (textAlign == TextAlign::END) {
            textAlign = TextAlign::START;
        }
    }
    if (textAlign != TextAlign::START) {
        HandleTextAlign(result, textAlign);
    } else {
        if (paraStyle_.leadingMargin) {
            HandleLeadingMargin(result, *(paraStyle_.leadingMargin));
        }
        result.offset.SetX(result.offset.GetX() + paraStyle_.indent.ConvertToPx());
    }
    return true;
}

LineMetrics TxtParagraph::GetLineMetricsByRectF(RectF& rect)
{
    auto* paragraphTxt = static_cast<OHOS::Rosen::Typography*>(GetParagraph());
    LineMetrics lineMetrics;
    CHECK_NULL_RETURN(paragraphTxt, lineMetrics);
    auto metrics = paragraphTxt->GetLineMetrics();
    if (metrics.empty()) {
        return lineMetrics;
    }
    auto top = std::floor(rect.Top() + 0.5);
    auto bottom = std::floor(rect.Bottom() + 0.5);
    auto res = metrics.size() - 1;
    for (size_t index = 0; index < metrics.size() - 1; index++) {
        if (metrics[index].y <= top && metrics[index + 1].y >= bottom) {
            res = index;
            break;
        }
    }
    auto resMetric = metrics[res];
    lineMetrics.x = resMetric.x;
    lineMetrics.y = resMetric.y;
    lineMetrics.ascender = resMetric.ascender;
    lineMetrics.height = resMetric.height;
    return lineMetrics;
}

TextLineMetrics TxtParagraph::GetLineMetrics(size_t lineNumber)
{
    auto* paragraphTxt = static_cast<OHOS::Rosen::Typography*>(GetParagraph());
    TextLineMetrics lineMetrics;
    OHOS::Rosen::LineMetrics resMetric;
    CHECK_NULL_RETURN(paragraphTxt, lineMetrics);
    paragraphTxt->GetLineMetricsAt(lineNumber, &resMetric);

    lineMetrics.ascender = resMetric.ascender;
    lineMetrics.descender = resMetric.descender;
    lineMetrics.capHeight = resMetric.capHeight;
    lineMetrics.xHeight = resMetric.xHeight;
    lineMetrics.width = resMetric.width;
    lineMetrics.height = resMetric.height;
    lineMetrics.x = resMetric.x;
    lineMetrics.y = resMetric.y;
    lineMetrics.startIndex = resMetric.startIndex;
    lineMetrics.endIndex = resMetric.endIndex;
    lineMetrics.baseline = resMetric.baseline;
    lineMetrics.lineNumber = resMetric.lineNumber;

    if (resMetric.runMetrics.empty()) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "GetLineMetrics runMetrics is empty.");
        return lineMetrics;
    }

    auto runMetricsResMap = resMetric.runMetrics;
    for (const auto& it : runMetricsResMap) {
        RunMetrics runMetrics;
        auto runMetricsRes = it.second;
        SetRunMetrics(runMetrics, runMetricsRes);
        lineMetrics.runMetrics.insert(std::map<size_t, RunMetrics>::value_type(it.first, runMetrics));
    }
    return lineMetrics;
}

RectF TxtParagraph::GetPaintRegion(float x, float y)
{
    auto* paragraphTxt = static_cast<OHOS::Rosen::Typography*>(GetParagraph());
    CHECK_NULL_RETURN(paragraphTxt, RectF());
    auto region = paragraphTxt->GeneratePaintRegion(x, y);
    return RectF(region.GetLeft(), region.GetTop(), region.GetWidth(), region.GetHeight());
}

void TxtParagraph::SetRunMetrics(RunMetrics& runMetrics, const OHOS::Rosen::RunMetrics& runMetricsRes)
{
    auto textStyleRes = runMetricsRes.textStyle;
    runMetrics.textStyle.SetTextDecoration(static_cast<TextDecoration>(textStyleRes->decoration));
    Color color;
    color.SetValue(textStyleRes->color.CastToColorQuad());
    runMetrics.textStyle.SetTextColor(color);
    runMetrics.textStyle.SetFontWeight(static_cast<FontWeight>(textStyleRes->fontWeight));
    runMetrics.textStyle.SetFontStyle(static_cast<FontStyle>(textStyleRes->fontStyle));
    runMetrics.textStyle.SetTextBaseline(static_cast<TextBaseline>(textStyleRes->baseline));
    runMetrics.textStyle.SetFontFamilies(textStyleRes->fontFamilies);
    runMetrics.textStyle.SetFontSize(Dimension(textStyleRes->fontSize, DimensionUnit::VP));
    runMetrics.textStyle.SetLetterSpacing(Dimension(textStyleRes->letterSpacing, DimensionUnit::VP));
    runMetrics.textStyle.SetWordSpacing(Dimension(textStyleRes->wordSpacing, DimensionUnit::VP));
    runMetrics.textStyle.SetHeightScale(textStyleRes->heightScale);
    runMetrics.textStyle.SetHalfLeading(textStyleRes->halfLeading);
    runMetrics.textStyle.SetHeightOnly(textStyleRes->heightOnly);
    auto& ellipsis = textStyleRes->ellipsis;
    if (ellipsis == StringUtils::DEFAULT_USTRING || ellipsis.empty()) {
        runMetrics.textStyle.SetEllipsis(u"");
    } else {
        runMetrics.textStyle.SetEllipsis(ellipsis);
    }
    runMetrics.textStyle.SetEllipsisMode(static_cast<EllipsisMode>(textStyleRes->ellipsisModal));
    runMetrics.textStyle.SetLocale(textStyleRes->locale);

    auto fontMetricsRes = runMetricsRes.fontMetrics;
    runMetrics.fontMetrics.fFlags = fontMetricsRes.fFlags;
    runMetrics.fontMetrics.fTop = fontMetricsRes.fTop;
    runMetrics.fontMetrics.fAscent = fontMetricsRes.fAscent;
    runMetrics.fontMetrics.fDescent = fontMetricsRes.fDescent;
    runMetrics.fontMetrics.fBottom = fontMetricsRes.fBottom;
    runMetrics.fontMetrics.fLeading = fontMetricsRes.fLeading;
    runMetrics.fontMetrics.fAvgCharWidth = fontMetricsRes.fAvgCharWidth;
    runMetrics.fontMetrics.fMaxCharWidth = fontMetricsRes.fMaxCharWidth;
    runMetrics.fontMetrics.fXMin = fontMetricsRes.fXMin;
    runMetrics.fontMetrics.fXMax = fontMetricsRes.fXMax;
    runMetrics.fontMetrics.fXHeight = fontMetricsRes.fXHeight;
    runMetrics.fontMetrics.fCapHeight = fontMetricsRes.fCapHeight;
    runMetrics.fontMetrics.fUnderlineThickness = fontMetricsRes.fUnderlineThickness;
    runMetrics.fontMetrics.fUnderlinePosition = fontMetricsRes.fUnderlinePosition;
    runMetrics.fontMetrics.fStrikeoutThickness = fontMetricsRes.fStrikeoutThickness;
    runMetrics.fontMetrics.fStrikeoutPosition = fontMetricsRes.fStrikeoutPosition;
}

bool TxtParagraph::GetLineMetricsByCoordinate(const Offset& offset, LineMetrics& lineMetrics)
{
    auto* paragraphTxt = static_cast<OHOS::Rosen::Typography*>(GetParagraph());
    CHECK_NULL_RETURN(paragraphTxt, false);
    auto lineCount = static_cast<int32_t>(GetLineCount());
    if (lineCount <= 0) {
        return false;
    }
    auto height = GetHeight();
    if (height <= 0) {
        return false;
    }
    auto averageLineHeight = height / lineCount;
    auto lineNumber = std::clamp(static_cast<int32_t>(offset.GetY() / averageLineHeight), 0, lineCount - 1);
    Rosen::LineMetrics resMetric;
    auto ret = paragraphTxt->GetLineMetricsAt(lineNumber, &resMetric);
    while (ret) {
        if (GreatOrEqual(offset.GetY(), resMetric.y) && LessOrEqual(offset.GetY(), resMetric.y + resMetric.height)) {
            break;
        }
        if (LessNotEqual(offset.GetY(), resMetric.y)) {
            lineNumber--;
            ret = paragraphTxt->GetLineMetricsAt(lineNumber, &resMetric);
            continue;
        }
        if (GreatNotEqual(offset.GetY(), resMetric.y + resMetric.height)) {
            lineNumber++;
            ret = paragraphTxt->GetLineMetricsAt(lineNumber, &resMetric);
            continue;
        }
        ret = false;
    }
    if (ret) {
        lineMetrics.x = resMetric.x;
        lineMetrics.y = resMetric.y;
        lineMetrics.ascender = resMetric.ascender;
        lineMetrics.width = resMetric.width;
        lineMetrics.height = resMetric.height;
        lineMetrics.descender = resMetric.descender;
        lineMetrics.capHeight = resMetric.capHeight;
        lineMetrics.xHeight = resMetric.xHeight;
        lineMetrics.startIndex = static_cast<int32_t>(resMetric.startIndex);
        lineMetrics.endIndex = static_cast<int32_t>(resMetric.endIndex);
    }
    return ret;
}

std::u16string TxtParagraph::GetParagraphText()
{
    return text_;
}

const ParagraphStyle& TxtParagraph::GetParagraphStyle() const
{
    return paraStyle_;
}

RSParagraph* TxtParagraph::GetParagraph()
{
    if (paragraph_) {
        return paragraph_.get();
    }
    return externalParagraph_;
}

std::unique_ptr<RSParagraph> TxtParagraph::GetParagraphUniquePtr()
{
    return std::move(paragraph_);
}

void TxtParagraph::UpdateColor(size_t from, size_t to, const Color& color)
{
    auto paragrah = GetParagraph();
    CHECK_NULL_VOID(paragrah);
    if (SystemProperties::GetTextTraceEnabled()) {
        ACE_TEXT_SCOPED_TRACE("TxtParagraph::UpdateColor[id:%d][from:%d][to:%d][color:%s]", paraStyle_.textStyleUid,
            static_cast<int32_t>(from), static_cast<int32_t>(to), color.ColorToString().c_str());
    }
    auto* paragraphTxt = static_cast<OHOS::Rosen::Typography*>(paragrah);
    CHECK_NULL_VOID(paragraphTxt);
    paragraphTxt->UpdateColor(from, to, ToRSColor(color));
}

int32_t TxtParagraph::GetIndexWithoutPlaceHolder(int32_t index)
{
    int32_t newIndex = index;
    for (auto placeholderIndex : placeholderPosition_) {
        if (placeholderIndex < static_cast<size_t>(index)) {
            newIndex--;
        }
    }
    return newIndex;
}

bool TxtParagraph::IsTargetCharAtIndex(char16_t targetChar, int32_t index)
{
    auto textIndex = GetIndexWithoutPlaceHolder(index);
    return text_[std::max(0, textIndex)] == targetChar;
}

bool TxtParagraph::IsIndexAtLineEnd(const Offset& offset, int32_t index)
{
    LineMetrics lineMetrics;
    return GetLineMetricsByCoordinate(offset, lineMetrics) && (index == lineMetrics.endIndex);
}

bool TxtParagraph::DidExceedMaxLinesInner()
{
    auto paragrah = GetParagraph();
    CHECK_NULL_RETURN(paragrah, false);
    return !paragrah->CanPaintAllText();
}

std::string TxtParagraph::GetDumpInfo()
{
    auto paragrah = GetParagraph();
    CHECK_NULL_RETURN(paragrah, "");
    return paragrah->GetDumpInfo();
}
} // namespace OHOS::Ace::NG
