/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/text/span/span_object.h"

#include <optional>
#include <utility>

#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace {
// SpanBase
std::optional<std::pair<int32_t, int32_t>> SpanBase::GetIntersectionInterval(std::pair<int32_t, int32_t> interval) const
{
    // 检查相交情况
    if (end_ <= interval.first || interval.second <= start_) {
        return std::nullopt;
    }

    // 计算相交区间
    int start = std::max(start_, interval.first);
    int end = std::min(end_, interval.second);
    return std::make_optional<std::pair<int32_t, int32_t>>(std::make_pair(start, end));
}

int32_t SpanBase::GetStartIndex() const
{
    return start_;
}

int32_t SpanBase::GetEndIndex() const
{
    return end_;
}
void SpanBase::UpdateStartIndex(int32_t startIndex)
{
    start_ = startIndex;
}

void SpanBase::UpdateEndIndex(int32_t endIndex)
{
    end_ = endIndex;
}

int32_t SpanBase::GetLength() const
{
    return end_ - start_;
}

// FontSpan
FontSpan::FontSpan(Font font) : SpanBase(0, 0), font_(std::move(font)) {}

FontSpan::FontSpan(Font font, int32_t start, int32_t end) : SpanBase(start, end), font_(std::move(font)) {}

void FontSpan::ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const
{
    switch (operation) {
        case SpanOperation::ADD:
            AddSpanStyle(spanItem);
            break;
        case SpanOperation::REMOVE:
            RemoveSpanStyle(spanItem);
    }
}

RefPtr<SpanBase> FontSpan::GetSubSpan(int32_t start, int32_t end)
{
    RefPtr<SpanBase> spanBase = MakeRefPtr<FontSpan>(font_, start, end);
    return spanBase;
}

void FontSpan::AddSpanStyle(const RefPtr<NG::SpanItem>& spanItem) const
{
    if (font_.fontColor.has_value()) {
        spanItem->fontStyle->UpdateTextColor(font_.fontColor.value());
    }

    if (font_.fontFamiliesNG.has_value()) {
        spanItem->fontStyle->UpdateFontFamily(font_.fontFamiliesNG.value());
    }

    if (font_.fontSize.has_value()) {
        spanItem->fontStyle->UpdateFontSize(font_.fontSize.value());
    }

    if (font_.fontStyle.has_value()) {
        spanItem->fontStyle->UpdateItalicFontStyle(font_.fontStyle.value());
    }

    if (font_.fontWeight.has_value()) {
        spanItem->fontStyle->UpdateFontWeight(font_.fontWeight.value());
    }
}

void FontSpan::RemoveSpanStyle(const RefPtr<NG::SpanItem>& spanItem)
{
    spanItem->fontStyle->ResetTextColor();
    spanItem->fontStyle->ResetFontFamily();
    spanItem->fontStyle->ResetFontSize();
    spanItem->fontStyle->ResetItalicFontStyle();
    spanItem->fontStyle->ResetFontWeight();
}

Font FontSpan::GetFont() const
{
    return font_;
}

SpanType FontSpan::GetSpanType() const
{
    return SpanType::Font;
}

std::string FontSpan::ToString() const
{
    std::stringstream str;
    str << "FontSpan ( start:";
    str << GetStartIndex();
    str << " end:";
    str << GetEndIndex();
    str << "]";
    std::string output = str.str();
    return output;
}

bool FontSpan::IsAttributesEqual(const RefPtr<SpanBase>& other) const
{
    auto fontSpan = DynamicCast<FontSpan>(other);
    if (!fontSpan) {
        return false;
    }
    auto font = fontSpan->GetFont();
    return font_.IsEqual(font);
}

// ImageSpan
ImageSpan::ImageSpan(const NG::ImageSpanOptions& options) : SpanBase(0, 1), imageOptions_(options) {}

bool ImageSpan::IsAttributesEqual(const RefPtr<SpanBase>& other) const
{
    auto imageSpan = DynamicCast<ImageSpan>(other);
    if (!imageSpan) {
        return false;
    }
    if (imageOptions_.imageAttribute.has_value() && imageSpan->GetImageAttribute().has_value()) {
        return imageOptions_.imageAttribute.value() == imageSpan->GetImageAttribute().value();
    }
    return false;
}

RefPtr<SpanBase> ImageSpan::GetSubSpan(int32_t start, int32_t end)
{
    if (end - start > 1) {
        return nullptr;
    }
    auto spanBase = MakeRefPtr<ImageSpan>(imageOptions_);
    spanBase->UpdateStartIndex(start);
    spanBase->UpdateEndIndex(end);
    return spanBase;
}

SpanType ImageSpan::GetSpanType() const
{
    return SpanType::Image;
}

void ImageSpan::ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const
{
    auto imageItem = DynamicCast<NG::ImageSpanItem>(spanItem);
    if (!imageItem) {
        return;
    }

    switch (operation) {
        case SpanOperation::ADD:
            imageItem->SetImageSpanOptions(imageOptions_);
            break;
        case SpanOperation::REMOVE:
            imageItem->ResetImageSpanOptions();
    }
}

std::string ImageSpan::ToString() const
{
    return "";
}

const NG::ImageSpanOptions& ImageSpan::GetImageSpanOptions()
{
    return imageOptions_;
}

const std::optional<NG::ImageSpanAttribute>& ImageSpan::GetImageAttribute() const
{
    return imageOptions_.imageAttribute;
}
} // namespace OHOS::Ace