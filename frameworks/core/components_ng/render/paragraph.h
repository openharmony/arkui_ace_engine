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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_PAPAGRAPH_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_PAPAGRAPH_H

#include "base/geometry/ng/size_t.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/text_layout_info.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/render/font_collection.h"
#include "core/components_v2/inspector/utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

enum RectHeightPolicy {
    COVER_TEXT,
    COVER_LINE
};

class LeadingMarginSize {
public:
    LeadingMarginSize() = default;
    ~LeadingMarginSize() = default;

    LeadingMarginSize(Dimension width, Dimension height)
    {
        width_ = UnitFilter(width);
        height_ = UnitFilter(height);
    }

    std::string ToString() const
    {
        static const int32_t precision = 2;
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision);
        ss << "width: " << width_.ToString();
        ss << " height: " << height_.ToString();
        return ss.str();
    }

    bool operator==(const LeadingMarginSize& size) const
    {
        return NearEqual(width_, size.width_) && NearEqual(height_, size.height_);
    }

    Dimension Width() const
    {
        return width_;
    }

    Dimension Height() const
    {
        return height_;
    }

private:
    Dimension UnitFilter(Dimension& value)
    {
        return value.Unit() == DimensionUnit::PERCENT ? Dimension(0.0) : value;
    }

    Dimension width_;
    Dimension height_;
};

struct LineMetrics {
    float ascender = 0.0f;
    float descender = 0.0f;
    float capHeight = 0.0f;
    float xHeight = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    float x = 0.0f;
    float y = 0.0f;
    int32_t startIndex = 0;
    int32_t endIndex = 0;
};

struct LeadingMargin {
    LeadingMarginSize size;
    RefPtr<PixelMap> pixmap;

    bool operator==(const LeadingMargin& other) const
    {
        return size == other.size && pixmap == other.pixmap;
    }

    bool IsValid()
    {
        return size.Width().IsValid() || size.Height().IsValid();
    }

    std::string ToString() const
    {
        auto jsonValue = JsonUtil::Create(true);
        JSON_STRING_PUT_STRINGABLE(jsonValue, size);
        jsonValue->Put("pixmap",
            pixmap ? ("size=" + std::to_string(pixmap->GetWidth()) + "," + std::to_string(pixmap->GetHeight())).c_str()
                   : "nullptr");
        return jsonValue->ToString();
    }

    bool CheckLeadingMargin(const LeadingMargin& other) const
    {
        auto flag = size == other.size;
        if (pixmap && other.pixmap) {
            flag &= pixmap->GetRawPixelMapPtr() == other.pixmap->GetRawPixelMapPtr();
        } else if (!other.pixmap && !pixmap) {
            flag &= true;
        } else {
            flag &= false;
        }
        return flag;
    }
};

enum TextHeightBehavior {
    ALL = 0x0,
    DISABLE_FIRST_ASCENT = 0x1,
    DISABLE_LAST_ASCENT = 0x2,
    DISABLE_ALL = 0x1 | 0x2,
};

struct ParagraphStyle {
    TextDirection direction = TextDirection::AUTO;
    TextAlign align = TextAlign::LEFT;
    TextVerticalAlign verticalAlign = TextVerticalAlign::BASELINE;
    uint32_t maxLines = UINT32_MAX;
    std::string fontLocale;
    WordBreak wordBreak = WordBreak::NORMAL;
    EllipsisMode ellipsisMode = EllipsisMode::TAIL;
    LineBreakStrategy lineBreakStrategy = LineBreakStrategy::GREEDY;
    TextOverflow textOverflow = TextOverflow::CLIP;
    std::optional<LeadingMargin> leadingMargin;
    double fontSize = 14.0;
    Dimension lineHeight;
    Dimension indent;
    bool halfLeading = false;
    Alignment leadingMarginAlign = Alignment::TOP_CENTER;
    Dimension paragraphSpacing;
    bool isEndAddParagraphSpacing = false;
    int32_t textStyleUid = 0;
    bool isOnlyBetweenLines = false;
    bool isFirstParagraphLineSpacing = true;
    bool optimizeTrailingSpace = false;
    bool enableAutoSpacing = false;

    bool operator==(const ParagraphStyle others) const
    {
        return direction == others.direction && align == others.align && verticalAlign == others.verticalAlign &&
               maxLines == others.maxLines && fontLocale == others.fontLocale && wordBreak == others.wordBreak &&
               ellipsisMode == others.ellipsisMode && textOverflow == others.textOverflow &&
               leadingMargin == others.leadingMargin && fontSize == others.fontSize &&
               halfLeading == others.halfLeading && indent == others.indent &&
               paragraphSpacing == others.paragraphSpacing && isOnlyBetweenLines == others.isOnlyBetweenLines &&
               enableAutoSpacing == others.enableAutoSpacing;
    }

    bool operator!=(const ParagraphStyle others) const
    {
        return !(*this == others);
    }

    std::string ToString() const
    {
        std::string result = "TextAlign: ";
        result += V2::ConvertWrapTextAlignToString(align);
        result += ", TextVerticalAlign: ";
        result += V2::ConvertWrapTextVerticalAlignToString(verticalAlign);
        result += ", maxLines: ";
        result += std::to_string(maxLines);
        result += ", wordBreak: ";
        result += V2::ConvertWrapWordBreakToString(wordBreak);
        result += ", textOverflow: ";
        result += V2::ConvertWrapTextOverflowToString(textOverflow);
        result += ", leadingMargin: ";
        result += leadingMargin.has_value() ? leadingMargin.value().ToString().c_str() : "nullptr";
        result += ", fontSize: ";
        result += std::to_string(fontSize);
        result += ", indent: ";
        result += ", paragraphSpacing: ";
        result += paragraphSpacing.ToString();
        result += indent.ToString();
        result += ", enableAutoSpacing: ";
        result += enableAutoSpacing;
        return result;
    }
};

struct CaretMetricsF {
    CaretMetricsF() = default;
    CaretMetricsF(const OffsetF& position, float h)
    {
        offset = position;
        height = h;
    }
    void Reset()
    {
        offset.Reset();
        height = 0.0;
    }

    OffsetF offset;
    // When caret is close to different glyphs, the height will be different.
    float height = 0.0f;
    std::string ToString() const
    {
        std::string result = "Offset: ";
        result += offset.ToString();
        result += ", height: ";
        result += std::to_string(height);
        return result;
    }
};

struct PositionWithAffinity {
    PositionWithAffinity(size_t pos, TextAffinity affinity)
    {
        position_ = pos;
        affinity_ = affinity;
    }
    size_t position_;
    TextAffinity affinity_;
};

// Paragraph is interface for drawing text and text paragraph.
class Paragraph : public virtual AceType {
    DECLARE_ACE_TYPE(NG::Paragraph, AceType);

public:
    static RefPtr<Paragraph> Create(const ParagraphStyle& paraStyle, const RefPtr<FontCollection>& fontCollection);
    static RefPtr<Paragraph> CreateRichEditorParagraph(
        const ParagraphStyle& paraStyle, const RefPtr<FontCollection>& fontCollection);

    static RefPtr<Paragraph> Create(void* paragraph);
    // whether the paragraph has been build
    virtual bool IsValid() = 0;

    // interfaces for build text paragraph
    virtual void PushStyle(const TextStyle& style) = 0;
    virtual void PopStyle() = 0;
    virtual void AddText(const std::u16string& text) = 0;
    virtual void AddSymbol(const std::uint32_t& symbolId) = 0;
    virtual int32_t AddPlaceholder(const PlaceholderRun& span) = 0;
    virtual void Build() = 0;
    virtual void Reset() = 0;

    // interfaces for layout
    virtual void Layout(float width) = 0;
    // interfaces for reLayout
    virtual void ReLayout(float width, const ParagraphStyle& paraStyle, const std::vector<TextStyle>& textStyles) = 0;
    virtual void ReLayoutForeground(const TextStyle& textStyle) = 0;
    virtual float GetHeight() = 0;
    virtual float GetTextWidth() = 0;
    virtual size_t GetLineCount() = 0;
    virtual float GetMaxIntrinsicWidth() = 0;
    virtual bool DidExceedMaxLines() = 0;
    virtual float GetLongestLine() = 0;
    virtual float GetLongestLineWithIndent() = 0;
    virtual float GetMaxWidth() = 0;
    virtual float GetAlphabeticBaseline() = 0;
    virtual float GetCharacterWidth(int32_t index) = 0;
    virtual int32_t GetGlyphIndexByCoordinate(const Offset& offset, bool isSelectionPos = false) = 0;
    virtual PositionWithAffinity GetGlyphPositionAtCoordinate(const Offset& offset)
    {
        PositionWithAffinity finalResult(0, TextAffinity::UPSTREAM);
        return finalResult;
    }
    virtual void GetRectsForRange(int32_t start, int32_t end, std::vector<RectF>& selectedRects) = 0;
    virtual std::pair<size_t, size_t> GetEllipsisTextRange() = 0;
    virtual void GetTightRectsForRange(int32_t start, int32_t end, std::vector<RectF>& selectedRects) = 0;
    virtual void GetRectsForPlaceholders(std::vector<RectF>& selectedRects) = 0;
    virtual bool ComputeOffsetForCaretDownstream(
        int32_t extent, CaretMetricsF& result, bool needLineHighest = true) = 0;
    virtual bool ComputeOffsetForCaretUpstream(int32_t extent, CaretMetricsF& result, bool needLineHighest = true) = 0;
    virtual bool CalcCaretMetricsByPosition(
        int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity, bool needLineHighest = true) = 0;
    virtual bool CalcCaretMetricsByPosition(int32_t extent, CaretMetricsF& caretCaretMetric,
        const OffsetF& lastTouchOffset, TextAffinity& textAffinity) = 0;
    virtual void SetIndents(const std::vector<float>& indents) = 0;
    virtual bool GetWordBoundary(int32_t offset, int32_t& start, int32_t& end) = 0;
    virtual std::u16string GetParagraphText() = 0;
    virtual const ParagraphStyle& GetParagraphStyle() const = 0;
    // interfaces for pass on Symbol Animation interface
    virtual void SetParagraphSymbolAnimation(const RefPtr<FrameNode>& frameNode) = 0;
    // interfaces for painting
    virtual void Paint(RSCanvas& canvas, float x, float y) = 0;
#ifndef USE_ROSEN_DRAWING
    virtual void Paint(SkCanvas* skCanvas, float x, float y) = 0;
#endif
    virtual LineMetrics GetLineMetricsByRectF(RectF& rect) = 0;
    virtual TextLineMetrics GetLineMetrics(size_t lineNumber) = 0;
    virtual RectF GetPaintRegion(float x, float y) = 0;
    virtual bool GetLineMetricsByCoordinate(const Offset& offset, LineMetrics& lineMetrics) = 0;
    virtual void UpdateColor(size_t from, size_t to, const Color& color) = 0;
    virtual void TxtGetRectsForRange(int32_t start, int32_t end,
        RectHeightStyle heightStyle, RectWidthStyle widthStyle,
        std::vector<RectF>& selectedRects, std::vector<TextDirection>& textDirections) = 0;
    virtual bool empty() const
    {
        return false;
    };
    virtual bool DidExceedMaxLinesInner()
    {
        return false;
    }
    virtual std::string GetDumpInfo()
    {
        return "";
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_PAPAGRAPH_H
