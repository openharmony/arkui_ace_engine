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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_TXT_PARAGRAPH_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_TXT_PARAGRAPH_H

#ifndef USE_GRAPHIC_TEXT_GINE
#include "txt/font_collection.h"
#include "txt/paragraph_builder.h"
#include "txt/paragraph_txt.h"
#else
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/drawing.h"
#endif

#include "base/utils/noncopyable.h"
#include "core/components/common/properties/text_layout_info.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {

// Paragraph is interface for drawing text and text paragraph.
class TxtParagraph : public Paragraph {
    DECLARE_ACE_TYPE(NG::TxtParagraph, NG::Paragraph)

public:
#ifndef USE_GRAPHIC_TEXT_GINE
    TxtParagraph(const ParagraphStyle& paraStyle, std::shared_ptr<txt::FontCollection> fontCollection)
        : paraStyle_(paraStyle), fontCollection_(std::move(fontCollection))
    {}

    TxtParagraph(void* paragraph) : hasExternalParagraph_(true)
    {}

    void SetParagraphSymbolAnimation(const RefPtr<FrameNode>& frameNode) override
    {}
#else
    TxtParagraph(const ParagraphStyle& paraStyle, std::shared_ptr<RSFontCollection> fontCollection)
        : paraStyle_(paraStyle), fontCollection_(std::move(fontCollection))
    {}

    TxtParagraph(void* paragraph)
    {
        hasExternalParagraph_ = true;
        externalParagraph_ = reinterpret_cast<RSParagraph*>(paragraph);
    }

    void SetParagraphSymbolAnimation(const RefPtr<FrameNode>& frameNode) override
    {
        auto context = AceType::DynamicCast<NG::RosenRenderContext>(frameNode->GetRenderContext());
        auto rsNode = context->GetRSNode();
        rsSymbolAnimation_ = RSSymbolAnimation();
        rsSymbolAnimation_.SetNode(rsNode);

        std::function<bool(
            const std::shared_ptr< RSSymbolAnimationConfig>& symbolAnimationConfig)>
            scaleCallback = std::bind(&RSSymbolAnimation::SetSymbolAnimation,
            rsSymbolAnimation_,
            std::placeholders::_1);

        SetAnimation(scaleCallback);
    }

    void SetAnimation(
        std::function<bool(
            const std::shared_ptr<Rosen::TextEngine::SymbolAnimationConfig>&)>& animationFunc)
    {
        if (animationFunc == nullptr) {
            TAG_LOGE(AceLogTag::ACE_TEXT_FIELD, "HmSymbol txt_paragraph::SetAnimation failed ");
        } else {
            auto paragraph = GetParagraph();
            CHECK_NULL_VOID(paragraph);
            paragraph->SetAnimation(animationFunc);
            TAG_LOGD(AceLogTag::ACE_TEXT_FIELD, "HmSymbol txt_paragraph::SetAnimation success ");
        }
    }
#endif
    ~TxtParagraph() override;

    // whether the paragraph has been build
    bool IsValid() override;

    // interfaces for build text paragraph
    void PushStyle(const TextStyle& style) override;
    void PopStyle() override;

    void AddText(const std::u16string& text) override;
    void AddSymbol(const uint32_t& symbolId) override;
    int32_t AddPlaceholder(const PlaceholderRun& span) override;
    void Build() override;
    void Reset() override;

    // interfaces for layout
    void Layout(float width) override;
    float GetHeight() override;
    float GetTextWidth() override;
    size_t GetLineCount() override;
    float GetMaxIntrinsicWidth() override;
    bool DidExceedMaxLines() override;
    float GetLongestLine() override;
    float GetLongestLineWithIndent() override;
    float GetMaxWidth() override;
    float GetAlphabeticBaseline() override;
    float GetCharacterWidth(int32_t index) override;

    // interfaces for painting
    void Paint(RSCanvas& canvas, float x, float y) override;
#ifndef USE_ROSEN_DRAWING
    void Paint(SkCanvas* skCanvas, float x, float y) override;
#endif

    // interfaces for calculate the the specified paragraph position
    int32_t GetGlyphIndexByCoordinate(const Offset& offset, bool isSelectionPos = false) override;
    PositionWithAffinity GetGlyphPositionAtCoordinate(const Offset& offset) override;
    void AdjustIndexForward(const Offset& offset, bool compareOffset, int32_t& index);
    void GetRectsForRange(int32_t start, int32_t end, std::vector<RectF>& selectedRects) override;
    std::pair<size_t, size_t> GetEllipsisTextRange() override;
    void GetTightRectsForRange(int32_t start, int32_t end, std::vector<RectF>& selectedRects) override;
    void GetRectsForPlaceholders(std::vector<RectF>& selectedRects) override;
    bool ComputeOffsetForCaretDownstream(int32_t extent, CaretMetricsF& result, bool needLineHighest = true) override;
    bool ComputeOffsetForCaretUpstream(int32_t extent, CaretMetricsF& result, bool needLineHighest = true) override;
    bool CalcCaretMetricsByPosition(int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity,
        bool needLineHighest = true) override;
    bool CalcCaretMetricsByPosition(int32_t extent, CaretMetricsF& caretCaretMetric, const OffsetF& lastTouchOffset,
        TextAffinity& textAffinity) override;
    void SetIndents(const std::vector<float>& indents) override;
    bool GetWordBoundary(int32_t offset, int32_t& start, int32_t& end) override;
    std::u16string GetParagraphText() override;
    const ParagraphStyle& GetParagraphStyle() const override;
    bool empty() const
    {
        return GetParagraphLength() == 0;
    }
    void SetParagraphId(uint32_t id) override
    {
        auto paragraph = GetParagraph();
        if (paragraph) {
            paragraph->SetParagraghId(id);
        }
    }
    LineMetrics GetLineMetricsByRectF(RectF& rect) override;
    TextLineMetrics GetLineMetrics(size_t lineNumber) override;
    void SetRunMetrics(RunMetrics& runMetrics, const OHOS::Rosen::RunMetrics& runMetricsRes);
    bool GetLineMetricsByCoordinate(const Offset& offset, LineMetrics& lineMetrics) override;
    void UpdateColor(size_t from, size_t to, const Color& color) override;
    void TxtGetRectsForRange(int32_t start, int32_t end,
        RectHeightStyle heightStyle, RectWidthStyle widthStyle,
        std::vector<RectF>& selectedRects, std::vector<TextDirection>& textDirections) override;

private:
    void CreateBuilder();
    bool CalCulateAndCheckPreIsPlaceholder(int32_t index, int32_t& extent);
    inline size_t GetParagraphLength() const
    {
        return text_.length() + placeholderCnt_;
    }
    float MakeEmptyOffsetX();
    bool HandleCaretWhenEmpty(CaretMetricsF& result);
    void HandleTextAlign(CaretMetricsF& result, TextAlign align);
    void HandleLeadingMargin(CaretMetricsF& result, LeadingMargin leadingMargin);
    void GetRectsForRangeInner(int32_t start, int32_t end, std::vector<RectF>& selectedRects,
        RectHeightPolicy rectHeightPolicy = RectHeightPolicy::COVER_LINE);
    int32_t AdjustIndexForEmoji(int32_t index);
    bool IsIndexInEmoji(int32_t index, int32_t& emojiStart, int32_t& emojiEnd);
    void CalculateLeadingMarginOffest(float& x, float& y);

    ParagraphStyle paraStyle_;
#ifndef USE_GRAPHIC_TEXT_GINE
    txt::Paragraph* GetParagraph();
    std::unique_ptr<txt::Paragraph> paragraph_;
    std::unique_ptr<txt::ParagraphBuilder> builder_;
    std::shared_ptr<txt::FontCollection> fontCollection_;
#else
    RSParagraph* GetParagraph();
    Rosen::RSSymbolAnimation rsSymbolAnimation_;
    std::unique_ptr<RSParagraph> paragraph_;
    RSParagraph* externalParagraph_ = nullptr;
    std::unique_ptr<RSParagraphBuilder> builder_;
    std::shared_ptr<RSFontCollection> fontCollection_;
#endif
    std::u16string text_;
    int32_t placeholderCnt_ = 0;
    TextAlign textAlign_ = TextAlign::START;
    static uint32_t destructCount;
    std::list<size_t> placeholderPosition_;
    bool hasExternalParagraph_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(TxtParagraph);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_TXT_PARAGRAPH_H
