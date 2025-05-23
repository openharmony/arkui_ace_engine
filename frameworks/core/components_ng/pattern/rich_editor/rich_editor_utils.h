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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_UTILS_H

namespace OHOS::Ace::NG {

static std::string ToBriefString(const TextStyle& style, const ImageSpanAttribute& imageStyle,
    struct UpdateSpanStyle opt)
{
    std::stringstream ss;
    /* text style */
    ss << "te={";
    IF_TRUE(opt.updateTextColor, ss << style.GetTextColor().ToString() << ",");
    IF_TRUE(opt.updateFontSize, ss << "FS" << style.GetFontSize().ConvertToFp() << ",");
    IF_TRUE(opt.updateItalicFontStyle, ss << StringUtils::ToString(style.GetFontStyle()) << ",");
    IF_TRUE(opt.updateFontWeight, ss << StringUtils::ToString(style.GetFontWeight()) << ",");
    IF_TRUE(opt.updateTextDecoration, ss << StringUtils::ToString(style.GetTextDecorationFirst()) << ",");
    IF_TRUE(opt.updateLineHeight, ss << "LH" << style.GetLineHeight().ConvertToFp() << ",");
    IF_TRUE(opt.updateLetterSpacing, ss << "LS" << style.GetLetterSpacing().ConvertToFp() << ",");
    ss << "},";

    /* symbol style */
    ss << "sb={";
    IF_TRUE(opt.updateSymbolFontSize, ss << opt.updateSymbolFontSize->ConvertToFp() << ",");
    IF_TRUE(opt.updateSymbolFontWeight, ss  << StringUtils::ToString(*opt.updateSymbolFontWeight) << ",");
    IF_TRUE(opt.updateSymbolRenderingStrategy, ss << "RS" << *opt.updateSymbolRenderingStrategy  << ",");
    IF_TRUE(opt.updateSymbolEffectStrategy, ss << "ES" << *opt.updateSymbolEffectStrategy  << ",");
    ss << "},";

    /* image style */
    ss << "im={[";
    IF_TRUE(opt.updateImageWidth, ss << opt.updateImageWidth->ToString() << ",");
    IF_TRUE(opt.updateImageHeight, ss << opt.updateImageHeight->ToString());
    ss << "],";
    IF_TRUE(opt.updateImageFit, ss << StringUtils::ToString(*opt.updateImageFit) << ",");
    IF_TRUE(opt.updateImageVerticalAlign, ss << StringUtils::ToString(*opt.updateImageVerticalAlign) << ",");
    ss << "}";
    return ss.str();
}

static std::string ToBriefString(const TextStyle& style)
{
    std::stringstream ss;
    ss << "{";
    ss << style.GetTextColor().ToString() << ",";
    ss << "FS" << style.GetFontSize().ConvertToFp() << ",";
    ss << StringUtils::ToString(style.GetFontStyle()) << ",";
    ss << StringUtils::ToString(style.GetFontWeight()) << ",";
    ss << StringUtils::ToString(style.GetTextDecorationFirst()) << ",";
    ss << "LH" << style.GetLineHeight().ConvertToFp() << ",";
    ss << "LS" << style.GetLetterSpacing().ConvertToFp();
    ss << "}";
    return ss.str();
}

static std::string ToBriefString(const TextSpanOptions& opts)
{
    std::stringstream ss;
    ss << "{";
    ss << "index=" << opts.offset.value_or(-1) << ", ";
    ss << "len=" << opts.value.size() << ", ";
    if (opts.style) {
        ss << "ts=" << ToBriefString(opts.style.value()) << ", ";
    }
    if (opts.paraStyle) {
        ss << "ps={" << opts.paraStyle->ToString() << "}, ";
    }
    ss << "themeFC=" << static_cast<int32_t>(opts.useThemeFontColor);
    ss << "}";
    return ss.str();
}

static std::string ToBriefString(const SymbolSpanOptions& opts)
{
    std::stringstream ss;
    ss << "{";
    ss << "index=" << opts.offset.value_or(-1) << ", ";
    if (opts.style) {
        ss << "ts=" << ToBriefString(opts.style.value()) << ", ";
    }
    if (opts.paraStyle) {
        ss << "ps={" << opts.paraStyle->ToString() << "}, ";
    }
    ss << "}";
    return ss.str();
}

}

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_UTILS_H