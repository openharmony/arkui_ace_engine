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

#include "core/components_ng/pattern/text/paragraph_util.h"

#include "text_layout_adapter.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
ParagraphStyle ParagraphUtil::GetParagraphStyle(const TextStyle& textStyle)
{
    return { .direction = textStyle.GetTextDirection(),
        .align = textStyle.GetTextAlign(),
        .verticalAlign = textStyle.GetParagraphVerticalAlign(),
        .maxLines = static_cast<int32_t>(textStyle.GetMaxLines()) < 0 ? UINT32_MAX : textStyle.GetMaxLines(),
        .fontLocale = textStyle.GetLocale(),
        .wordBreak = textStyle.GetWordBreak(),
        .ellipsisMode = textStyle.GetEllipsisMode(),
        .lineBreakStrategy = textStyle.GetLineBreakStrategy(),
        .textOverflow = textStyle.GetTextOverflow(),
        .indent = textStyle.GetTextIndent(),
        .halfLeading = textStyle.GetHalfLeading(),
        .paragraphSpacing = textStyle.GetParagraphSpacing(),
        .isOnlyBetweenLines = textStyle.GetIsOnlyBetweenLines(),
        .optimizeTrailingSpace = textStyle.GetOptimizeTrailingSpace(),
        .enableAutoSpacing = textStyle.GetEnableAutoSpacing()
        };
}

TextDirection ParagraphUtil::GetTextDirection(
    const std::u16string& content, LayoutWrapper* layoutWrapper)
{
    if (!layoutWrapper) {
        return GetTextDirectionByContent(content);
    }
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textLayoutProperty, TextDirection::LTR);

    auto direction = textLayoutProperty->GetLayoutDirection();
    if (direction == TextDirection::LTR || direction == TextDirection::RTL) {
        return direction;
    }
    return GetTextDirectionByContent(content);
}

TextDirection ParagraphUtil::GetTextDirectionByContent(const std::u16string& content)
{
    bool isRTL = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto textDirection = isRTL ? TextDirection::RTL : TextDirection::LTR;
    for (const auto& charOfShowingText : content) {
        if (TextLayoutadapter::IsLeftToRight(charOfShowingText)) {
            return TextDirection::LTR;
        } else if (TextLayoutadapter::IsRightToLeft(charOfShowingText)) {
            return TextDirection::RTL;
        } else if (TextLayoutadapter::IsRightTOLeftArabic(charOfShowingText)) {
            return TextDirection::RTL;
        }
    }
    return textDirection;
}

void ParagraphUtil::GetSpanParagraphStyle(
    LayoutWrapper* layoutWrapper, const RefPtr<SpanItem>& spanItem, ParagraphStyle& pStyle)
{
    const auto& lineStyle = spanItem->textLineStyle;
    CHECK_NULL_VOID(lineStyle);
    if (lineStyle->HasTextAlign()) {
        pStyle.align = lineStyle->GetTextAlignValue();
    }
    if (lineStyle->HasTextVerticalAlign()) {
        pStyle.verticalAlign = lineStyle->GetTextVerticalAlignValue();
    }
    if (lineStyle->HasMaxLines()) {
        pStyle.maxLines = std::min(lineStyle->GetMaxLinesValue(), pStyle.maxLines);
    }
    if (lineStyle->HasWordBreak()) {
        pStyle.wordBreak = lineStyle->GetWordBreakValue();
    }
    if (lineStyle->HasEllipsisMode()) {
        pStyle.ellipsisMode = lineStyle->GetEllipsisModeValue();
    }
    if (lineStyle->HasTextOverflow()) {
        pStyle.textOverflow = lineStyle->GetTextOverflowValue();
    }
    if (lineStyle->HasTextIndent()) {
        pStyle.indent = lineStyle->GetTextIndentValue();
    }
    if (lineStyle->HasLineBreakStrategy()) {
        pStyle.lineBreakStrategy = lineStyle->GetLineBreakStrategyValue();
    }
    if (lineStyle->HasLeadingMargin()) {
        pStyle.leadingMargin = lineStyle->GetLeadingMarginValue();
    }
    if (lineStyle->HasLineHeight()) {
        pStyle.lineHeight = lineStyle->GetLineHeightValue();
    }
    if (lineStyle->HasHalfLeading()) {
        pStyle.halfLeading = lineStyle->GetHalfLeadingValue();
    }
    if (lineStyle->HasParagraphSpacing()) {
        pStyle.paragraphSpacing = lineStyle->GetParagraphSpacingValue();
    }
    pStyle.direction = GetTextDirection(spanItem->content, layoutWrapper);
}

void ParagraphUtil::ConstructParagraphSpanGroup(std::list<RefPtr<SpanItem>>& spans,
    std::vector<std::list<RefPtr<SpanItem>>>& spanGroupVec,
    bool& spanStringHasMaxLines)
{
    // split spans into groups by mew paragraph style
    auto it = spans.begin();
    ParagraphStyle pStyle;
    GetSpanParagraphStyle(nullptr, (*it), pStyle);
    while (it != spans.end()) {
        auto spanItem = *it;
        if (!spanItem) {
            ++it;
            continue;
        }
        spanItem->SetNeedRemoveNewLine(false);
        if (spanItem->content.back() == u'\n') {
            if (std::next(it) == spans.end()) {
                break;
            }
            auto next = *(std::next(it));
            ParagraphStyle nextSpanParagraphStyle;
            if (next) {
                GetSpanParagraphStyle(nullptr, next, nextSpanParagraphStyle);
            } else {
                break;
            }
            if (pStyle != nextSpanParagraphStyle ||
                (pStyle.leadingMargin.has_value() && pStyle.leadingMargin->pixmap) || Positive(pStyle.indent.Value()) ||
                pStyle.maxLines != UINT32_MAX) {
                std::list<RefPtr<SpanItem>> newGroup;
                spanItem->SetNeedRemoveNewLine(true);
                newGroup.splice(newGroup.begin(), spans, spans.begin(), std::next(it));
                spanStringHasMaxLines |= pStyle.maxLines != UINT32_MAX;
                spanGroupVec.emplace_back(std::move(newGroup));
                it = spans.begin();
                pStyle = nextSpanParagraphStyle;
                continue;
            }
        }
        ++it;
    }
    if (!spans.empty()) {
        auto maxlines = spans.front()->textLineStyle->GetMaxLines().value_or(UINT32_MAX);
        spanStringHasMaxLines |= maxlines != UINT32_MAX;
        spanGroupVec.emplace_back(std::move(spans));
    }
}

void ParagraphUtil::HandleEmptyParagraph(RefPtr<Paragraph> paragraph,
    const std::list<RefPtr<SpanItem>>& spanGroup)
{
    CHECK_NULL_VOID(paragraph && spanGroup.size() == 1);
    auto spanItem = spanGroup.front();
    CHECK_NULL_VOID(spanItem);
    auto content = spanItem->GetSpanContent(spanItem->GetSpanContent());
    CHECK_NULL_VOID(content.empty());
    auto textStyle = spanItem->GetTextStyle();
    CHECK_NULL_VOID(textStyle.has_value());
    paragraph->PushStyle(textStyle.value());
}

void ParagraphUtil::ApplyIndent(
    ParagraphStyle& paragraphStyle, const RefPtr<Paragraph>& paragraph, double width, const TextStyle& textStyle)
{
    auto indentValue = paragraphStyle.indent;
    CHECK_NULL_VOID(paragraph);
    double value = 0.0;
    if (GreatNotEqual(indentValue.Value(), 0.0)) {
        // first line indent
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        if (indentValue.Unit() != DimensionUnit::PERCENT) {
            value = indentValue.ConvertToPxDistribute(
                textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
        } else {
            value = static_cast<float>(width * indentValue.Value());
            paragraphStyle.indent = Dimension(value);
        }
    }
    auto indent = static_cast<float>(value);
    auto leadingMarginValue = 0.0f;
    std::vector<float> indents;
    if (paragraphStyle.leadingMargin.has_value()) {
        leadingMarginValue = paragraphStyle.leadingMargin->size.Width().ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    }
    indents.emplace_back(indent + leadingMarginValue);
    indents.emplace_back(leadingMarginValue);
    paragraph->SetIndents(indents);
}

ImageSourceInfo ParagraphUtil::CreateImageSourceInfo(const ImageSpanOptions& options)
{
    std::string src;
    RefPtr<PixelMap> pixMap = nullptr;
    std::string bundleName;
    std::string moduleName;
    if (options.image.has_value()) {
        src = options.image.value();
    }
    if (options.imagePixelMap.has_value()) {
        pixMap = options.imagePixelMap.value();
    }
    if (options.bundleName.has_value()) {
        bundleName = options.bundleName.value();
    }
    if (options.moduleName.has_value()) {
        moduleName = options.moduleName.value();
    }
    ImageSourceInfo info;
#if defined(PIXEL_MAP_SUPPORTED)
    if (!options.imagePixelMap.has_value()) {
        info = ImageSourceInfo{ src, bundleName, moduleName };
    } else {
        info = ImageSourceInfo(pixMap);
    }
#else
    info = ImageSourceInfo{ src, bundleName, moduleName };
#endif
    info.SetIsUriPureNumber(options.isUriPureNumber.value_or(false));
    return info;
}
} // namespace OHOS::Ace::NG