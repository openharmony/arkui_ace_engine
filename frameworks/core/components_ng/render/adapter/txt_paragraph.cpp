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

#include "core/components_ng/render/adapter/txt_paragraph.h"

#include "base/utils/utils.h"
#include "core/components/font/constants_converter.h"
#include "core/components_ng/render/adapter/skia_canvas.h"
#include "core/components_ng/render/adapter/txt_font_collection.h"

namespace OHOS::Ace::NG {

RefPtr<Paragraph> Paragraph::Create(const WeakPtr<PipelineContext>& context, const ParagraphStyle& paraStyle,
    const RefPtr<FontCollection>& fontCollection)
{
    auto txtFontCollection = DynamicCast<TxtFontCollection>(fontCollection);
    CHECK_NULL_RETURN(txtFontCollection, nullptr);
    auto sharedFontCollection = txtFontCollection->GetRawFontCollection();
    return AceType::MakeRefPtr<TxtParagraph>(context, paraStyle, sharedFontCollection);
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
#ifndef NG_BUILD
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
    Constants::ConvertTxtStyle(style, context_, txtStyle);
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
    builder_->AddText(text);
}

void TxtParagraph::Build()
{
    if (builder_) {
        paragraph_ = builder_->Build();
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
        return std::max(paragraph_->GetLongestLine(), paragraph_->GetMaxIntrinsicWidth());
    }
    return paragraph_->GetLongestLine();
}

size_t TxtParagraph::GetLineCount()
{
    auto* paragraphTxt = static_cast<txt::ParagraphTxt*>(paragraph_.get());
    CHECK_NULL_RETURN(paragraphTxt, 0);
    return paragraphTxt->GetLineCount();
}

void TxtParagraph::Paint(const RefPtr<Canvas>& canvas, float x, float y)
{
    CHECK_NULL_VOID(paragraph_);
    auto skiaCanvas = AceType::DynamicCast<SkiaCanvas>(canvas);
    CHECK_NULL_VOID(skiaCanvas);
    auto* skCanvas = skiaCanvas->RawCanvas();
    CHECK_NULL_VOID(skCanvas);
    paragraph_->Paint(skCanvas, x, y);
}

} // namespace OHOS::Ace::NG
