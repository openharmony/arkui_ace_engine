/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "flutter/third_party/txt/src/txt/font_collection.h"
#include "flutter/third_party/txt/src/txt/paragraph_builder.h"
#include "flutter/third_party/txt/src/txt/paragraph_txt.h"

#include "base/utils/noncopyable.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {

// Paragraph is interface for drawing text and text paragraph.
class TxtParagraph : public Paragraph {
    DECLARE_ACE_TYPE(NG::TxtParagraph, NG::Paragraph)

public:
    TxtParagraph(const WeakPtr<PipelineContext>& context, const ParagraphStyle& paraStyle,
        std::shared_ptr<txt::FontCollection> fontCollection)
        : context_(context), paraStyle_(paraStyle), fontCollection_(std::move(fontCollection))
    {}
    ~TxtParagraph() override = default;

    // whether the paragraph has been build
    bool IsValid() override;

    // interfaces for build text paragraph
    void PushStyle(const TextStyle& style) override;
    void PopStyle() override;

    void AddText(const std::u16string& text) override;
    void Build() override;
    void Reset() override;

    // interfaces for layout
    void Layout(float width) override;
    float GetHeight() override;
    float GetTextWidth() override;
    size_t GetLineCount() override;

    // interfaces for painting
    void Paint(const RefPtr<Canvas>& canvas, float x, float y) override;

private:
    void CreateBuilder();
    const WeakPtr<PipelineContext>& context_;
    ParagraphStyle paraStyle_;
    std::unique_ptr<txt::Paragraph> paragraph_;
    std::unique_ptr<txt::ParagraphBuilder> builder_;
    std::shared_ptr<txt::FontCollection> fontCollection_;

    ACE_DISALLOW_COPY_AND_MOVE(TxtParagraph);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_TXT_PARAGRAPH_H
