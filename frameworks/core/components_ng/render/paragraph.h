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

#ifdef USE_ROSEN_DRAWING
#include "include/core/SkCanvas.h"
#endif

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/render/font_collection.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

struct ParagraphStyle {
    TextDirection direction = TextDirection::AUTO;
    TextAlign align = TextAlign::LEFT;
    uint32_t maxLines = 1;
    std::string fontLocale;
    WordBreak wordBreak = WordBreak::NORMAL;
    TextOverflow textOverflow = TextOverflow::CLIP;
};

// Paragraph is interface for drawing text and text paragraph.
class Paragraph : public virtual AceType {
    DECLARE_ACE_TYPE(NG::Paragraph, AceType)

public:
    static RefPtr<Paragraph> Create(const ParagraphStyle& paraStyle, const RefPtr<FontCollection>& fontCollection);

    // whether the paragraph has been build
    virtual bool IsValid() = 0;

    // interfaces for build text paragraph
    virtual void PushStyle(const TextStyle& style) = 0;
    virtual void PopStyle() = 0;
    virtual void AddText(const std::u16string& text) = 0;
    virtual int32_t AddPlaceholder(const PlaceholderRun& span) = 0;
    virtual void Build() = 0;
    virtual void Reset() = 0;

    // interfaces for layout
    virtual void Layout(float width) = 0;
    virtual float GetHeight() = 0;
    virtual float GetTextWidth() = 0;
    virtual size_t GetLineCount() = 0;
    virtual float GetMaxIntrinsicWidth() = 0;
    virtual bool DidExceedMaxLines() = 0;
    virtual float GetLongestLine() = 0;
    virtual float GetMaxWidth() = 0;
    virtual float GetAlphabeticBaseline() = 0;
    virtual int32_t GetHandlePositionForClick(const Offset& offset) = 0;
    virtual void GetRectsForRange(int32_t start, int32_t end, std::vector<Rect>& selectedRects) = 0;
    virtual void GetRectsForPlaceholders(std::vector<Rect>& selectedRects) = 0;
    virtual bool ComputeOffsetForCaretDownstream(int32_t extent, CaretMetrics& result) = 0;
    virtual bool ComputeOffsetForCaretUpstream(int32_t extent, CaretMetrics& result) = 0;
    virtual void SetIndents(const std::vector<float>& indents) = 0;
#ifndef USE_GRAPHIC_TEXT_GINE
    virtual bool GetWordBoundary(int32_t offset, int32_t& start, int32_t& end) = 0;
#endif

    // interfaces for painting
    virtual void Paint(const RSCanvas& canvas, float x, float y) = 0;
    virtual void Paint(SkCanvas* skCanvas, float x, float y) = 0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_PAPAGRAPH_H
