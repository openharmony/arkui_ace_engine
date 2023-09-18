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

#include "core/components_ng/test/pattern/text/mock/mock_txt_paragraph.h"

#include "core/components_ng/render/adapter/txt_font_collection.h"
#include "core/components_ng/render/adapter/txt_paragraph.h"

namespace OHOS::Ace::NG {
namespace LayoutWidth {
float layoutWidth = 0.0f;
}
namespace {
bool textParapraphCanConstruct = true;
std::vector<bool> textParapraphDidExceedMaxLines;
} // namespace

void MockTxtParagraph::SetCanConstruct(bool canConstruct)
{
    textParapraphCanConstruct = canConstruct;
}

void MockTxtParagraph::SetDidExceedMaxLines(const std::vector<bool>& didExceedMaxLines)
{
    textParapraphDidExceedMaxLines = didExceedMaxLines;
}

RefPtr<Paragraph> Paragraph::Create(const ParagraphStyle& paraStyle, const RefPtr<FontCollection>& fontCollection)
{
    if (!textParapraphCanConstruct) {
        return nullptr;
    }
    auto txtFontCollection = DynamicCast<TxtFontCollection>(fontCollection);
    CHECK_NULL_RETURN(txtFontCollection, nullptr);
    auto sharedFontCollection = txtFontCollection->GetRawFontCollection();
    return AceType::MakeRefPtr<TxtParagraph>(paraStyle, sharedFontCollection);
}

bool TxtParagraph::IsValid()
{
    return paragraph_ != nullptr;
}

void TxtParagraph::CreateBuilder() {}

void TxtParagraph::PushStyle(const TextStyle& style) {}

void TxtParagraph::PopStyle() {}

void TxtParagraph::AddText(const std::u16string& text) {}

void TxtParagraph::Build() {}

void TxtParagraph::Reset() {}

void TxtParagraph::Layout(float width)
{
    LayoutWidth::layoutWidth = width;
}

float TxtParagraph::GetHeight()
{
    return 50.0f;
}

float TxtParagraph::GetTextWidth()
{
    return 150.0f;
}

float TxtParagraph::GetMaxIntrinsicWidth()
{
    return 150.0f;
}

bool TxtParagraph::DidExceedMaxLines()
{
    if (textParapraphDidExceedMaxLines.empty()) {
        return true;
    }
    bool result = *textParapraphDidExceedMaxLines.begin();
    textParapraphDidExceedMaxLines.erase(textParapraphDidExceedMaxLines.begin());
    return result;
}

float TxtParagraph::GetLongestLine()
{
    return 100.0f;
}

float TxtParagraph::GetMaxWidth()
{
    return LayoutWidth::layoutWidth;
}

float TxtParagraph::GetAlphabeticBaseline()
{
    return 0.0f;
}

size_t TxtParagraph::GetLineCount()
{
    return 1;
}

void TxtParagraph::Paint(RSCanvas& canvas, float x, float y) {}

void TxtParagraph::Paint(SkCanvas* skCanvas, float x, float y) {}

int32_t TxtParagraph::GetHandlePositionForClick(const Offset& offset)
{
    return 0;
}

void TxtParagraph::GetRectsForRange(int32_t start, int32_t end, std::vector<Rect>& selectedRects)
{
    selectedRects = { Rect(start, start, end - start, end - start) };
}

bool TxtParagraph::ComputeOffsetForCaretDownstream(int32_t extent, CaretMetrics& result)
{
    return true;
}
bool TxtParagraph::ComputeOffsetForCaretUpstream(int32_t extent, CaretMetrics& result)
{
    return true;
}

int32_t TxtParagraph::AddPlaceholder(const PlaceholderRun& span)
{
    placeHolderIndex_ = -1;
    return -1;
}

void TxtParagraph::GetRectsForPlaceholders(std::vector<Rect>& selectedRects) {}

void TxtParagraph::SetIndents(const std::vector<float>& indents) {}

bool TxtParagraph::GetWordBoundary(int32_t offset, int32_t& start, int32_t& end)
{
    return false;
}
} // namespace OHOS::Ace::NG
