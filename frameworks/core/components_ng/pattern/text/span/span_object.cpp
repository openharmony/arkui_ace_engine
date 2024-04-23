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
#include "core/components/common/layout/constants.h"
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

// DecorationSpan
DecorationSpan::DecorationSpan(
    TextDecoration type, std::optional<Color> color, std::optional<TextDecorationStyle> style)
    : SpanBase(0, 0), type_(type), color_(color), style_(style)
{}

DecorationSpan::DecorationSpan(TextDecoration type, std::optional<Color> color,
    std::optional<TextDecorationStyle> style, int32_t start, int32_t end)
    : SpanBase(start, end), type_(type), color_(color), style_(style)
{}

TextDecoration DecorationSpan::GetTextDecorationType() const
{
    return type_;
}

std::optional<Color> DecorationSpan::GetColor() const
{
    return color_;
}

std::optional<TextDecorationStyle> DecorationSpan::GetTextDecorationStyle() const
{
    return style_;
}

void DecorationSpan::ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const
{
    switch (operation) {
        case SpanOperation::ADD:
            AddDecorationStyle(spanItem);
            break;
        case SpanOperation::REMOVE:
            RemoveDecorationStyle(spanItem);
    }
}

RefPtr<SpanBase> DecorationSpan::GetSubSpan(int32_t start, int32_t end)
{
    RefPtr<SpanBase> spanBase = MakeRefPtr<DecorationSpan>(type_, color_, style_, start, end);
    return spanBase;
}

void DecorationSpan::AddDecorationStyle(const RefPtr<NG::SpanItem>& spanItem) const
{
    spanItem->fontStyle->UpdateTextDecoration(type_);
    if (color_.has_value()) {
        spanItem->fontStyle->UpdateTextDecorationColor(color_.value());
    }
    if (style_.has_value()) {
        spanItem->fontStyle->UpdateTextDecorationStyle(style_.value());
    }
}

void DecorationSpan::RemoveDecorationStyle(const RefPtr<NG::SpanItem>& spanItem)
{
    spanItem->fontStyle->ResetTextDecoration();
    spanItem->fontStyle->ResetTextDecorationColor();
    spanItem->fontStyle->ResetTextDecorationStyle();
}

SpanType DecorationSpan::GetSpanType() const
{
    return SpanType::Decoration;
}

std::string DecorationSpan::ToString() const
{
    std::stringstream str;
    str << "DecorationSpan ( start:";
    str << GetStartIndex();
    str << " end:";
    str << GetEndIndex();
    str << "]";
    std::string output = str.str();
    return output;
}

bool DecorationSpan::IsAttributesEqual(const RefPtr<SpanBase>& other) const
{
    auto decorationSpan = DynamicCast<DecorationSpan>(other);
    if (!decorationSpan) {
        return false;
    }
    std::optional<Color> color = decorationSpan->GetColor();
    std::optional<TextDecorationStyle> style = decorationSpan->GetTextDecorationStyle();
    TextDecoration type = decorationSpan->GetTextDecorationType();
    return color == color_ && style == style_ && type == type_;
}

// BaselineOffsetSpan
BaselineOffsetSpan::BaselineOffsetSpan(Dimension baselineOffset) : SpanBase(0, 0), baselineOffset_(baselineOffset) {}

BaselineOffsetSpan::BaselineOffsetSpan(Dimension baselineOffset, int32_t start, int32_t end)
    : SpanBase(start, end), baselineOffset_(baselineOffset)
{}

Dimension BaselineOffsetSpan::GetBaselineOffset() const
{
    return baselineOffset_;
}

void BaselineOffsetSpan::ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const
{
    switch (operation) {
        case SpanOperation::ADD:
            AddBaselineOffsetStyle(spanItem);
            break;
        case SpanOperation::REMOVE:
            RemoveBaselineOffsetStyle(spanItem);
    }
}

RefPtr<SpanBase> BaselineOffsetSpan::GetSubSpan(int32_t start, int32_t end)
{
    RefPtr<SpanBase> spanBase = MakeRefPtr<BaselineOffsetSpan>(baselineOffset_, start, end);
    return spanBase;
}

void BaselineOffsetSpan::AddBaselineOffsetStyle(const RefPtr<NG::SpanItem>& spanItem) const
{
    spanItem->textLineStyle->UpdateBaselineOffset(baselineOffset_);
}

void BaselineOffsetSpan::RemoveBaselineOffsetStyle(const RefPtr<NG::SpanItem>& spanItem)
{
    spanItem->textLineStyle->ResetBaselineOffset();
}

SpanType BaselineOffsetSpan::GetSpanType() const
{
    return SpanType::BaselineOffset;
}

std::string BaselineOffsetSpan::ToString() const
{
    std::stringstream str;
    str << "BaselineOffsetSpan ( start:";
    str << GetStartIndex();
    str << " end:";
    str << GetEndIndex();
    str << "]";
    std::string output = str.str();
    return output;
}

bool BaselineOffsetSpan::IsAttributesEqual(const RefPtr<SpanBase>& other) const
{
    auto baselineOffsetSpan = DynamicCast<BaselineOffsetSpan>(other);
    if (!baselineOffsetSpan) {
        return false;
    }
    auto baselineOffset = baselineOffsetSpan->GetBaselineOffset();
    return baselineOffset == baselineOffset_;
}

// LetterSpacingSpan
LetterSpacingSpan::LetterSpacingSpan(Dimension letterSpacing) : SpanBase(0, 0), letterSpacing_(letterSpacing) {}

LetterSpacingSpan::LetterSpacingSpan(Dimension letterSpacing, int32_t start, int32_t end)
    : SpanBase(start, end), letterSpacing_(letterSpacing)
{}

Dimension LetterSpacingSpan::GetLetterSpacing() const
{
    return letterSpacing_;
}

void LetterSpacingSpan::ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const
{
    switch (operation) {
        case SpanOperation::ADD:
            AddLetterSpacingStyle(spanItem);
            break;
        case SpanOperation::REMOVE:
            RemoveLetterSpacingStyle(spanItem);
    }
}

RefPtr<SpanBase> LetterSpacingSpan::GetSubSpan(int32_t start, int32_t end)
{
    RefPtr<SpanBase> spanBase = MakeRefPtr<LetterSpacingSpan>(letterSpacing_, start, end);
    return spanBase;
}

void LetterSpacingSpan::AddLetterSpacingStyle(const RefPtr<NG::SpanItem>& spanItem) const
{
    spanItem->fontStyle->UpdateLetterSpacing(letterSpacing_);
}

void LetterSpacingSpan::RemoveLetterSpacingStyle(const RefPtr<NG::SpanItem>& spanItem)
{
    spanItem->fontStyle->ResetLetterSpacing();
}

SpanType LetterSpacingSpan::GetSpanType() const
{
    return SpanType::LetterSpacing;
}

std::string LetterSpacingSpan::ToString() const
{
    std::stringstream str;
    str << "LetterSpacingSpan ( start:";
    str << GetStartIndex();
    str << " end:";
    str << GetEndIndex();
    str << "]";
    std::string output = str.str();
    return output;
}

bool LetterSpacingSpan::IsAttributesEqual(const RefPtr<SpanBase>& other) const
{
    auto letterSpacingSpan = DynamicCast<LetterSpacingSpan>(other);
    if (!letterSpacingSpan) {
        return false;
    }
    auto letterSpacing = letterSpacingSpan->GetLetterSpacing();
    return letterSpacing == letterSpacing_;
}

// GestureSpan
GestureSpan::GestureSpan(GestureStyle gestureInfo) : SpanBase(0, 0), gestureInfo_(std::move(gestureInfo)) {}

GestureSpan::GestureSpan(GestureStyle gestureInfo, int32_t start, int32_t end)
    : SpanBase(start, end), gestureInfo_(std::move(gestureInfo))
{}

GestureStyle GestureSpan::GetGestureStyle() const
{
    return gestureInfo_;
}

RefPtr<SpanBase> GestureSpan::GetSubSpan(int32_t start, int32_t end)
{
    RefPtr<SpanBase> spanBase = MakeRefPtr<GestureSpan>(gestureInfo_, start, end);
    return spanBase;
}

bool GestureSpan::IsAttributesEqual(const RefPtr<SpanBase>& other) const
{
    auto gestureSpan = DynamicCast<GestureSpan>(other);
    if (!gestureSpan) {
        return false;
    }
    auto gestureInfo = gestureSpan->GetGestureStyle();
    return gestureInfo_.IsEqual(gestureInfo);
}

SpanType GestureSpan::GetSpanType() const
{
    return SpanType::Gesture;
}

std::string GestureSpan::ToString() const
{
    std::stringstream str;
    str << "GestureSpan [ start:";
    str << GetStartIndex();
    str << " end:";
    str << GetEndIndex();
    str << "]";
    std::string output = str.str();
    return output;
}

void GestureSpan::ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const
{
    switch (operation) {
        case SpanOperation::ADD:
            AddSpanStyle(spanItem);
            break;
        case SpanOperation::REMOVE:
            RemoveSpanStyle(spanItem);
    }
}

void GestureSpan::AddSpanStyle(const RefPtr<NG::SpanItem>& spanItem) const
{
    if (gestureInfo_.onClick.has_value()) {
        spanItem->onClick = gestureInfo_.onClick.value();
    } else {
        spanItem->onClick = nullptr;
    }

    if (gestureInfo_.onLongPress.has_value()) {
        spanItem->onLongPress = gestureInfo_.onLongPress.value();
    } else {
        spanItem->onLongPress = nullptr;
    }
}
void GestureSpan::RemoveSpanStyle(const RefPtr<NG::SpanItem>& spanItem)
{
    spanItem->onClick = nullptr;
    spanItem->onLongPress = nullptr;
}

// TextShadowSpan
TextShadowSpan::TextShadowSpan(std::vector<Shadow> textShadow) : SpanBase(0, 0), textShadow_(std::move(textShadow)) {}

TextShadowSpan::TextShadowSpan(std::vector<Shadow> textShadow, int32_t start, int32_t end)
    : SpanBase(start, end), textShadow_(std::move(textShadow)) {}

void TextShadowSpan::ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const
{
    switch (operation) {
        case SpanOperation::ADD:
            AddSpanStyle(spanItem);
            break;
        case SpanOperation::REMOVE:
            RemoveSpanStyle(spanItem);
    }
}

RefPtr<SpanBase> TextShadowSpan::GetSubSpan(int32_t start, int32_t end)
{
    RefPtr<SpanBase> spanBase = MakeRefPtr<TextShadowSpan>(GetTextShadow(), start, end);
    return spanBase;
}

void TextShadowSpan::AddSpanStyle(const RefPtr<NG::SpanItem>& spanItem) const
{
    if (textShadow_.has_value()) {
        spanItem->fontStyle->UpdateTextShadow(textShadow_.value());
    }
}

void TextShadowSpan::RemoveSpanStyle(const RefPtr<NG::SpanItem>& spanItem)
{
    spanItem->fontStyle->ResetTextShadow();
}

std::vector<Shadow> TextShadowSpan::GetTextShadow() const
{
    return textShadow_.value_or(std::vector<Shadow>());
}

SpanType TextShadowSpan::GetSpanType() const
{
    return SpanType::TextShadow;
}

std::string TextShadowSpan::ToString() const
{
    std::stringstream str;
    str << "TextShadowSpan ( start:";
    str << GetStartIndex();
    str << " end:";
    str << GetEndIndex();
    str << "]";
    std::string output = str.str();
    return output;
}

bool TextShadowSpan::IsAttributesEqual(const RefPtr<SpanBase>& other) const
{
    auto textShadowSpan = DynamicCast<TextShadowSpan>(other);
    if (!textShadowSpan) {
        return false;
    }
    auto textShadow = textShadowSpan->GetTextShadow();
    auto selfTextShadow = GetTextShadow();
    if (textShadow.size() != selfTextShadow.size()) {
        return false;
    }
    for (size_t i = 0; i < selfTextShadow.size(); ++i) {
        if (selfTextShadow[i] != textShadow[i]) {
            return false;
        }
    }
    return true;
}

// ImageSpan
ImageSpan::ImageSpan(const ImageSpanOptions& options) : SpanBase(0, 1), imageOptions_(options) {}

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

const ImageSpanOptions& ImageSpan::GetImageSpanOptions()
{
    return imageOptions_;
}

const std::optional<ImageSpanAttribute>& ImageSpan::GetImageAttribute() const
{
    return imageOptions_.imageAttribute;
}
} // namespace OHOS::Ace