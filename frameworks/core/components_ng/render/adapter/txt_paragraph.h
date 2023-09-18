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
#include "core/components_ng/render/drawing.h"
#endif

#include "base/utils/noncopyable.h"
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
#else
    TxtParagraph(const ParagraphStyle& paraStyle, std::shared_ptr<RSFontCollection> fontCollection)
        : paraStyle_(paraStyle), fontCollection_(std::move(fontCollection))
    {}
#endif
    ~TxtParagraph() override = default;

    // whether the paragraph has been build
    bool IsValid() override;

    // interfaces for build text paragraph
    void PushStyle(const TextStyle& style) override;
    void PopStyle() override;

    void AddText(const std::u16string& text) override;
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
    float GetMaxWidth() override;
    float GetAlphabeticBaseline() override;

    // interfaces for painting
    void Paint(RSCanvas& canvas, float x, float y) override;
    void Paint(SkCanvas* skCanvas, float x, float y) override;

    // interfaces for calculate the the specified paragraph position
    int32_t GetHandlePositionForClick(const Offset& offset) override;
    void GetRectsForRange(int32_t start, int32_t end, std::vector<Rect>& selectedRects) override;
    void GetRectsForPlaceholders(std::vector<Rect>& selectedRects) override;
    bool ComputeOffsetForCaretDownstream(int32_t extent, CaretMetrics& result) override;
    bool ComputeOffsetForCaretUpstream(int32_t extent, CaretMetrics& result) override;
    void SetIndents(const std::vector<float>& indents) override;
    bool GetWordBoundary(int32_t offset, int32_t& start, int32_t& end) override;

private:
    void CreateBuilder();
    inline size_t GetParagraphLength() const
    {
        return text_.length() + placeHolderIndex_ + 1;
    }

    ParagraphStyle paraStyle_;
#ifndef USE_GRAPHIC_TEXT_GINE
    std::unique_ptr<txt::Paragraph> paragraph_;
    std::unique_ptr<txt::ParagraphBuilder> builder_;
    std::shared_ptr<txt::FontCollection> fontCollection_;
#else
    std::unique_ptr<RSParagraph> paragraph_;
    std::unique_ptr<RSParagraphBuilder> builder_;
    std::shared_ptr<RSFontCollection> fontCollection_;
#endif
    std::u16string text_;
    int32_t placeHolderIndex_ = -1;

    ACE_DISALLOW_COPY_AND_MOVE(TxtParagraph);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_TXT_PARAGRAPH_H
