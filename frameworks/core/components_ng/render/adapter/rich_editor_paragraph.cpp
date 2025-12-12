/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/adapter/rich_editor_paragraph.h"

namespace OHOS::Ace::NG {
RefPtr<Paragraph> Paragraph::CreateRichEditorParagraph(
    const ParagraphStyle& paraStyle, const RefPtr<FontCollection>& fontCollection, bool isSingleLineMode)
{
    auto txtFontCollection = DynamicCast<TxtFontCollection>(fontCollection);
    CHECK_NULL_RETURN(txtFontCollection, nullptr);
    auto sharedFontCollection = txtFontCollection->GetRawFontCollection();
    return AceType::MakeRefPtr<RichEditorParagraph>(paraStyle, sharedFontCollection, isSingleLineMode);
}

Rosen::TextRectHeightStyle RichEditorParagraph::GetHeightStyle(bool needLineHighest)
{
    return needLineHighest ? Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM : Rosen::TextRectHeightStyle::TIGHT;
}

void RichEditorParagraph::Layout(float width)
{
    CHECK_NULL_VOID(width != layoutWidth_);
    TxtParagraph::Layout(width);
    CHECK_NULL_VOID(paragraph_);
    layoutWidth_ = width;
    height_ = paragraph_->GetHeight();
    lineCount_ = static_cast<size_t>(std::max(paragraph_->GetLineCount(), 0));
}

void RichEditorParagraph::ReLayout(float width, const ParagraphStyle& paraStyle,
    const std::vector<TextStyle>& textStyles)
{
    ACE_SCOPED_TRACE("RichEditorParagraph::ReLayout");
    TxtParagraph::ReLayout(width, paraStyle, textStyles);
    CHECK_NULL_VOID(paragraph_);
    layoutWidth_ = width;
    height_ = paragraph_->GetHeight();
    lineCount_ = static_cast<size_t>(std::max(paragraph_->GetLineCount(), 0));
}

float RichEditorParagraph::GetHeight()
{
    return height_;
}

size_t RichEditorParagraph::GetLineCount()
{
    return lineCount_;
}

void RichEditorParagraph::AddText(const std::u16string& text)
{
    if (isSingleLineMode_ && !text.empty() && text.back() == u'\n') {
        TxtParagraph::AddText(text.substr(0, text.size() - 1) + u" ");
        return;
    }
    TxtParagraph::AddText(text);
}

bool RichEditorParagraph::IsSingleLineMode()
{
    return isSingleLineMode_;
}

} // namespace OHOS::Ace::NG