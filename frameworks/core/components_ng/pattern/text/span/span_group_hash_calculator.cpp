/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/span/span_group_hash_calculator.h"

#include <cmath>
#include <cstdint>
#include <functional>
#include <limits>
#include <optional>

#include "core/components_ng/pattern/text/paragraph_util.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double DIMENSION_EPSILON = 0.00001f;
constexpr double DOUBLE_EPSILON = 0.001f;

template<typename T>
uint64_t CombineHash(uint64_t seed, const T& value)
{
    constexpr uint64_t MAGIC_NUMBER = 0x9e3779b9;
    constexpr int32_t LEFT_SHIFT = 6;
    constexpr int32_t RIGHT_SHIFT = 2;
    return seed ^ (static_cast<uint64_t>(value) + MAGIC_NUMBER + (seed << LEFT_SHIFT) + (seed >> RIGHT_SHIFT));
}

uint64_t HashString(uint64_t seed, const std::string& value)
{
    return CombineHash(seed, std::hash<std::string> {}(value));
}

uint64_t HashQuantizedDouble(uint64_t seed, double value, double epsilon = DOUBLE_EPSILON)
{
    if (std::isnan(value)) {
        return CombineHash(seed, std::numeric_limits<int64_t>::min());
    }
    if (std::isinf(value)) {
        return CombineHash(seed, value > 0 ? std::numeric_limits<int64_t>::max() :
            std::numeric_limits<int64_t>::min() + 1);
    }
    if (epsilon == 0.0) {
        return seed;
    }
    return CombineHash(seed, static_cast<int64_t>(std::llround(value / epsilon)));
}

uint64_t HashDimension(uint64_t seed, const Dimension& value)
{
    seed = CombineHash(seed, static_cast<int32_t>(value.Unit()));
    if (value.Unit() == DimensionUnit::PERCENT || value.Unit() == DimensionUnit::AUTO ||
        value.Unit() == DimensionUnit::CALC) {
        return HashQuantizedDouble(seed, value.Value(), DIMENSION_EPSILON);
    }
    return HashQuantizedDouble(seed, value.ConvertToPx(), DIMENSION_EPSILON);
}

template<typename T>
uint64_t HashOptionalEnum(uint64_t seed, const std::optional<T>& value)
{
    seed = CombineHash(seed, value.has_value() ? 1U : 0U);
    if (value.has_value()) {
        seed = CombineHash(seed, static_cast<uint64_t>(value.value()));
    }
    return seed;
}

template<typename T>
uint64_t HashOptionalNumber(uint64_t seed, const std::optional<T>& value)
{
    seed = CombineHash(seed, value.has_value() ? 1U : 0U);
    if (value.has_value()) {
        seed = CombineHash(seed, std::hash<T> {}(value.value()));
    }
    return seed;
}

uint64_t HashOptionalDimension(uint64_t seed, const std::optional<Dimension>& value)
{
    seed = CombineHash(seed, value.has_value() ? 1U : 0U);
    if (value.has_value()) {
        seed = HashDimension(seed, value.value());
    }
    return seed;
}

uint64_t HashOptionalColor(uint64_t seed, const std::optional<Color>& value)
{
    seed = CombineHash(seed, value.has_value() ? 1U : 0U);
    if (value.has_value()) {
        seed = CombineHash(seed, value->GetValue());
    }
    return seed;
}

uint64_t HashTextDecorationTypes(uint64_t seed, const std::optional<std::vector<TextDecoration>>& value)
{
    seed = CombineHash(seed, value.has_value() ? 1U : 0U);
    if (!value.has_value()) {
        return seed;
    }
    seed = CombineHash(seed, static_cast<uint64_t>(value->size()));
    for (const auto& item : value.value()) {
        seed = CombineHash(seed, static_cast<uint64_t>(item));
    }
    return seed;
}

uint64_t HashTextShadows(uint64_t seed, const std::optional<std::vector<Shadow>>& value)
{
    seed = CombineHash(seed, value.has_value() ? 1U : 0U);
    if (!value.has_value()) {
        return seed;
    }
    seed = CombineHash(seed, static_cast<uint64_t>(value->size()));
    for (const auto& item : value.value()) {
        seed = CombineHash(seed, static_cast<uint64_t>(item.GetColor().GetValue()));
        seed = HashQuantizedDouble(seed, item.GetBlurRadius());
        seed = HashQuantizedDouble(seed, item.GetOffset().GetX());
        seed = HashQuantizedDouble(seed, item.GetOffset().GetY());
    }
    return seed;
}

uint64_t HashFontFamilies(uint64_t seed, const std::optional<std::vector<std::string>>& value)
{
    seed = CombineHash(seed, value.has_value() ? 1U : 0U);
    if (!value.has_value()) {
        return seed;
    }
    seed = CombineHash(seed, static_cast<uint64_t>(value->size()));
    for (const auto& item : value.value()) {
        seed = HashString(seed, item);
    }
    return seed;
}

uint64_t HashFontFeatures(uint64_t seed, const std::optional<FONT_FEATURES_LIST>& value)
{
    seed = CombineHash(seed, value.has_value() ? 1U : 0U);
    if (!value.has_value()) {
        return seed;
    }
    seed = CombineHash(seed, static_cast<uint64_t>(value->size()));
    for (const auto& item : value.value()) {
        seed = HashString(seed, item.first);
        seed = CombineHash(seed, static_cast<uint64_t>(item.second));
    }
    return seed;
}

uint64_t HashFontVariations(uint64_t seed, const std::optional<FONT_VARIATIONS_LIST>& value)
{
    seed = CombineHash(seed, value.has_value() ? 1U : 0U);
    if (!value.has_value()) {
        return seed;
    }
    seed = CombineHash(seed, static_cast<uint64_t>(value->size()));
    for (const auto& item : value.value()) {
        seed = HashString(seed, item.axis);
        seed = CombineHash(seed, std::hash<float> {}(item.value));
        seed = CombineHash(seed, item.isNormalized.has_value() ? 1U : 0U);
        if (item.isNormalized.has_value()) {
            seed = CombineHash(seed, item.isNormalized.value() ? 1U : 0U);
        }
    }
    return seed;
}

uint64_t HashTextDecorationOptions(uint64_t seed, const std::optional<TextDecorationOptions>& value)
{
    seed = CombineHash(seed, value.has_value() ? 1U : 0U);
    if (value.has_value()) {
        seed = CombineHash(seed, value->enableMultiType.has_value() ? 1U : 0U);
        if (value->enableMultiType.has_value()) {
            seed = CombineHash(seed, value->enableMultiType.value() ? 1U : 0U);
        }
    }
    return seed;
}

uint64_t HashLeadingMargin(uint64_t seed, const std::optional<LeadingMargin>& value)
{
    seed = CombineHash(seed, value.has_value() ? 1U : 0U);
    if (value.has_value()) {
        seed = HashDimension(seed, value->size.Width());
        seed = HashDimension(seed, value->size.Height());
        seed = CombineHash(seed, value->pixmap ? 1U : 0U);
        if (value->pixmap) {
            seed = CombineHash(seed, reinterpret_cast<uintptr_t>(AceType::RawPtr(value->pixmap)));
        }
    }
    return seed;
}

uint64_t HashDrawableLeadingMargin(uint64_t seed, const std::optional<DrawableLeadingMargin>& value)
{
    seed = CombineHash(seed, value.has_value() ? 1U : 0U);
    if (value.has_value()) {
        seed = HashDimension(seed, value->size.Width());
        seed = HashDimension(seed, value->size.Height());
    }
    return seed;
}

uint64_t HashOptionalBorderRadius(uint64_t seed, const std::optional<BorderRadiusProperty>& value)
{
    seed = CombineHash(seed, value.has_value() ? 1U : 0U);
    if (value.has_value()) {
        seed = HashOptionalDimension(seed, value->radiusTopLeft);
        seed = HashOptionalDimension(seed, value->radiusTopRight);
        seed = HashOptionalDimension(seed, value->radiusBottomLeft);
        seed = HashOptionalDimension(seed, value->radiusBottomRight);
    }
    return seed;
}

uint64_t HashTextBackgroundStyle(uint64_t seed, const std::optional<TextBackgroundStyle>& value)
{
    seed = CombineHash(seed, value.has_value() ? 1U : 0U);
    if (value.has_value()) {
        seed = HashOptionalColor(seed, value->backgroundColor);
        // Keep hash semantics aligned with TextBackgroundStyle::operator==.
        seed = HashOptionalBorderRadius(seed, value->backgroundRadius);
    }
    return seed;
}
} // namespace

SpanGroupHashResult SpanGroupHashCalculator::Calculate(const std::list<RefPtr<SpanItem>>& spans)
{
    SpanGroupHashResult result;
    uint64_t contentHash = 0;
    uint64_t styleHash = 0;
    bool hasSpanInGroup = false;
    auto it = spans.begin();
    while (it != spans.end()) {
        const auto& span = *it;
        if (span) {
            contentHash = HashSpanContent(contentHash, span);
            styleHash = HashSpanStyle(styleHash, span);
            hasSpanInGroup = true;
        }
        const bool needSplit =
            span && !span->content.empty() && span->content.back() == u'\n' && std::next(it) != spans.end();
        if (needSplit) {
            result.contentHashes.emplace_back(contentHash);
            result.styleHashes.emplace_back(styleHash);
            contentHash = 0;
            styleHash = 0;
            hasSpanInGroup = false;
        }
        ++it;
    }
    if (hasSpanInGroup) {
        result.contentHashes.emplace_back(contentHash);
        result.styleHashes.emplace_back(styleHash);
    }
    return result;
}

std::vector<uint64_t> SpanGroupHashCalculator::CalculateStyleHashes(const std::list<RefPtr<SpanItem>>& spans)
{
    std::vector<uint64_t> styleHashes;
    uint64_t styleHash = 0;
    bool hasSpanInGroup = false;
    auto it = spans.begin();
    while (it != spans.end()) {
        const auto& span = *it;
        if (span) {
            styleHash = HashSpanStyle(styleHash, span);
            hasSpanInGroup = true;
        }
        const bool needSplit =
            span && !span->content.empty() && span->content.back() == u'\n' && std::next(it) != spans.end();
        if (needSplit) {
            styleHashes.emplace_back(styleHash);
            styleHash = 0;
            hasSpanInGroup = false;
        }
        ++it;
    }
    if (hasSpanInGroup) {
        styleHashes.emplace_back(styleHash);
    }
    return styleHashes;
}

uint64_t SpanGroupHashCalculator::HashSpanContent(uint64_t hash, const RefPtr<SpanItem>& span)
{
    CHECK_NULL_RETURN(span, hash);
    hash = CombineHash(hash, static_cast<uint64_t>(span->nodeId_));
    hash = CombineHash(hash, static_cast<uint64_t>(span->interval.first));
    hash = CombineHash(hash, static_cast<uint64_t>(span->interval.second));
    for (const auto& ch : span->content) {
        hash = CombineHash(hash, static_cast<uint64_t>(ch));
    }
    return hash;
}

uint64_t SpanGroupHashCalculator::HashSpanStyle(uint64_t hash, const RefPtr<SpanItem>& span)
{
    CHECK_NULL_RETURN(span, hash);
    auto& fontStyle = span->fontStyle;
    if (fontStyle) {
        hash = HashOptionalColor(hash, fontStyle->GetTextColor());
        hash = HashOptionalDimension(hash, fontStyle->GetFontSize());
        hash = HashOptionalEnum(hash, fontStyle->GetItalicFontStyle());
        hash = HashOptionalEnum(hash, fontStyle->GetSuperscript());
        hash = HashOptionalEnum(hash, fontStyle->GetFontWeight());
        hash = HashOptionalNumber(hash, fontStyle->GetVariableFontWeight());
        hash = HashOptionalNumber(hash, fontStyle->GetEnableVariableFontWeight());
        hash = HashOptionalNumber(hash, fontStyle->GetEnableDeviceFontWeightCategory());
        hash = HashFontFamilies(hash, fontStyle->GetFontFamily());
        hash = HashFontFeatures(hash, fontStyle->GetFontFeature());
        hash = HashFontVariations(hash, fontStyle->GetFontVariations());
        hash = HashTextDecorationTypes(hash, fontStyle->GetTextDecoration());
        hash = HashOptionalColor(hash, fontStyle->GetTextDecorationColor());
        hash = HashOptionalDimension(hash, fontStyle->GetStrokeWidth());
        hash = HashOptionalColor(hash, fontStyle->GetStrokeColor());
        hash = HashOptionalEnum(hash, fontStyle->GetTextDecorationStyle());
        hash = HashTextDecorationOptions(hash, fontStyle->GetTextDecorationOptions());
        hash = HashOptionalDimension(hash, fontStyle->GetLetterSpacing());
        hash = HashTextShadows(hash, fontStyle->GetTextShadow());
        hash = HashOptionalNumber(hash, fontStyle->GetLineThicknessScale());
        hash = HashOptionalNumber(hash, fontStyle->GetFontSizeScale());
    }

    auto& textLineStyle = span->textLineStyle;
    if (textLineStyle) {
        hash = HashOptionalDimension(hash, textLineStyle->GetLineHeight());
        hash = HashOptionalNumber(hash, textLineStyle->GetLineHeightMultiply());
        hash = HashOptionalDimension(hash, textLineStyle->GetBaselineOffset());
        hash = HashOptionalEnum(hash, textLineStyle->GetTextOverflow());
        hash = HashOptionalEnum(hash, textLineStyle->GetTextAlign());
        hash = HashOptionalEnum(hash, textLineStyle->GetTextVerticalAlign());
        hash = HashOptionalNumber(hash, textLineStyle->GetMaxLines());
        hash = HashOptionalDimension(hash, textLineStyle->GetTextIndent());
        hash = HashLeadingMargin(hash, textLineStyle->GetLeadingMargin());
        hash = HashDrawableLeadingMargin(hash, textLineStyle->GetDrawableLeadingMargin());
        hash = HashOptionalEnum(hash, textLineStyle->GetWordBreak());
        hash = HashOptionalDimension(hash, textLineStyle->GetLineSpacing());
        hash = HashOptionalNumber(hash, textLineStyle->GetIsOnlyBetweenLines());
        hash = HashOptionalNumber(hash, textLineStyle->GetHalfLeading());
        hash = HashOptionalDimension(hash, textLineStyle->GetParagraphSpacing());
        hash = HashOptionalEnum(hash, textLineStyle->GetTextDirection());
    }
    hash = HashTextBackgroundStyle(hash, span->backgroundStyle);
    return hash;
}
} // namespace OHOS::Ace::NG
