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
    const ParagraphStyle& paraStyle, const RefPtr<FontCollection>& fontCollection)
{
    auto txtFontCollection = DynamicCast<TxtFontCollection>(fontCollection);
    CHECK_NULL_RETURN(txtFontCollection, nullptr);
    auto sharedFontCollection = txtFontCollection->GetRawFontCollection();
    return AceType::MakeRefPtr<RichEditorParagraph>(paraStyle, sharedFontCollection);
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
}

float RichEditorParagraph::GetHeight()
{
    return height_;
}

} // namespace OHOS::Ace::NG