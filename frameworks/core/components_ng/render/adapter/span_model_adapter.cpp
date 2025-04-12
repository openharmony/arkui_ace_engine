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

#include "base/utils/utf_helper.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {


#define UPDATE_SPAN_FONT_STYLE_ITEM(item, name, value) (item)->fontStyle->Update##name(value)

#define UPDATE_SPAN_TEXT_LINE_STYLE_ITEM(item, name, value) (item)->textLineStyle->Update##name(value)

RefPtr<SpanItem> SpanModelNG::CreateSpanItem(ArkUI_SpanItem* item)
{
    if (!item) {
        return nullptr;
    }
    if (item->placeholder) {
        auto* drawingPlaceholder = reinterpret_cast<Rosen::PlaceholderSpan*>(item->placeholder);
        auto placeholder = AceType::MakeRefPtr<PlaceholderSpanItem>();
        placeholder->run_.width = drawingPlaceholder->width;
        placeholder->run_.height = drawingPlaceholder->height;
        placeholder->run_.alignment = static_cast<PlaceholderAlignment>(drawingPlaceholder->alignment);
        placeholder->run_.baseline = static_cast<TextBaseline>(drawingPlaceholder->baseline);
        placeholder->run_.baseline_offset = drawingPlaceholder->baselineOffset;
        return placeholder;
    }
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = UtfUtils::Str8DebugToStr16(item->content);
    auto* textStyle = reinterpret_cast<RSTextStyle*>(item->textStyle);
    if (!textStyle) {
        return spanItem;
    }
    spanItem->fontStyle = std::make_unique<FontStyle>();
    spanItem->textLineStyle = std::make_unique<TextLineStyle>();
    UPDATE_SPAN_FONT_STYLE_ITEM(spanItem, FontSize, Dimension(textStyle->fontSize));
    UPDATE_SPAN_FONT_STYLE_ITEM(spanItem, TextColor,
        Color::FromARGB(textStyle->color.GetAlpha(), textStyle->color.GetRed(), textStyle->color.GetGreen(),
            textStyle->color.GetBlue()));
    UPDATE_SPAN_FONT_STYLE_ITEM(spanItem, ItalicFontStyle, static_cast<Ace::FontStyle>(textStyle->fontStyle));
    UPDATE_SPAN_FONT_STYLE_ITEM(spanItem, FontWeight, static_cast<FontWeight>(textStyle->fontWeight));
    UPDATE_SPAN_FONT_STYLE_ITEM(spanItem, FontFamily, textStyle->fontFamilies);
    auto decoration = TextDecoration::INHERIT;
    switch (textStyle->decoration) {
        case Rosen::NONE:
            decoration = TextDecoration::NONE;
            break;
        case Rosen::UNDERLINE:
            decoration = TextDecoration::UNDERLINE;
            break;
        case Rosen::OVERLINE:
            decoration = TextDecoration::OVERLINE;
            break;
        case Rosen::LINE_THROUGH:
            decoration = TextDecoration::LINE_THROUGH;
            break;
            break;
    }
    UPDATE_SPAN_FONT_STYLE_ITEM(spanItem, TextDecoration, {decoration});
    UPDATE_SPAN_FONT_STYLE_ITEM(
        spanItem, TextDecorationStyle, static_cast<TextDecorationStyle>(textStyle->decorationStyle));
    UPDATE_SPAN_FONT_STYLE_ITEM(spanItem, TextDecorationColor,
        Color::FromARGB(textStyle->decorationColor.GetAlpha(), textStyle->decorationColor.GetRed(),
            textStyle->decorationColor.GetGreen(), textStyle->decorationColor.GetBlue()));
    const auto& fontFeatures = textStyle->fontFeatures.GetFontFeatures();
    FONT_FEATURES_LIST list;
    for (const auto& item : fontFeatures) {
        list.emplace_back(item.first, item.second);
    }
    UPDATE_SPAN_FONT_STYLE_ITEM(spanItem, FontFeature, list);
    std::vector<Shadow> shadows;
    shadows.reserve(textStyle->shadows.size());
    for (const auto& shadow : textStyle->shadows) {
        shadows.emplace_back(shadow.blurRadius, 0, Offset { shadow.offset.GetX(), shadow.offset.GetY() },
            Color::FromARGB(
                shadow.color.GetAlpha(), shadow.color.GetRed(), shadow.color.GetGreen(), shadow.color.GetBlue()));
    }
    UPDATE_SPAN_FONT_STYLE_ITEM(spanItem, TextShadow, shadows);
    UPDATE_SPAN_FONT_STYLE_ITEM(spanItem, LetterSpacing, Dimension(textStyle->letterSpacing));
    UPDATE_SPAN_TEXT_LINE_STYLE_ITEM(spanItem, TextBaseline, static_cast<TextBaseline>(textStyle->baseline));
    UPDATE_SPAN_TEXT_LINE_STYLE_ITEM(spanItem, BaselineOffset, Dimension(textStyle->baseLineShift));
    UPDATE_SPAN_TEXT_LINE_STYLE_ITEM(spanItem, EllipsisMode, static_cast<EllipsisMode>(textStyle->ellipsisModal));
    return spanItem;
}

ParagraphStyle SpanModelNG::CreateParagraphStyle(ArkUI_StyledString* styledString)
{
    auto typoStyle = reinterpret_cast<Rosen::TypographyStyle*>(styledString->paragraphStyle);
    TextDirection textDirection;
    switch (typoStyle->textDirection) {
        case Rosen::TextDirection::RTL:
            textDirection = TextDirection::RTL;
            break;
        case Rosen::TextDirection::LTR:
            textDirection = TextDirection::LTR;
            break;
        default:
            textDirection = TextDirection::LTR;
            break;
    }
    TextAlign textAlign;
    switch (typoStyle->textAlign) {
        case Rosen::TextAlign::LEFT:
            textAlign = TextAlign::LEFT;
            break;
        case Rosen::TextAlign::RIGHT:
            textAlign = TextAlign::RIGHT;
            break;
        case Rosen::TextAlign::CENTER:
            textAlign = TextAlign::CENTER;
            break;
        case Rosen::TextAlign::JUSTIFY:
            textAlign = TextAlign::JUSTIFY;
            break;
        case Rosen::TextAlign::START:
            textAlign = TextAlign::START;
            break;
        case Rosen::TextAlign::END:
            textAlign = TextAlign::END;
            break;
        default:
            textAlign = TextAlign::START;
            break;
    }
    std::u16string ELLIPSIS = u"\u2026";
    ParagraphStyle style = { .direction = textDirection,
        .align = textAlign,
        .maxLines = typoStyle->maxLines,
        .fontLocale = typoStyle->locale,
        .wordBreak = static_cast<WordBreak>(typoStyle->wordBreakType),
        .ellipsisMode = static_cast<EllipsisMode>(typoStyle->ellipsisModal),
        .lineBreakStrategy = static_cast<LineBreakStrategy>(typoStyle->breakStrategy),
        .textOverflow = typoStyle->ellipsis == ELLIPSIS ? TextOverflow::ELLIPSIS : TextOverflow::CLIP };
    return style;
}

} // namespace OHOS::Ace::NG