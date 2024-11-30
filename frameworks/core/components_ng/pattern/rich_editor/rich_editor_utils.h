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

static std::string ToBriefString(const TextStyle& style, const ImageSpanAttribute& imageStyle, struct UpdateSpanStyle updateOpt)
{
    std::stringstream ss;
    /* text style */
    ss << "te={";
    IF_TRUE(updateOpt.updateTextColor, ss << style.GetTextColor().ToString() << ", ");
    IF_TRUE(updateOpt.updateFontSize, ss << style.GetFontSize().ConvertToFp() << ", ");
    IF_TRUE(updateOpt.updateItalicFontStyle, ss << StringUtils::ToString(style.GetFontStyle()) << ", ");
    IF_TRUE(updateOpt.updateFontWeight, ss << StringUtils::ToString(style.GetFontWeight()) << ", ");
    IF_TRUE(updateOpt.updateTextDecoration, ss << StringUtils::ToString(style.GetTextDecoration()) << ", ");
    IF_TRUE(updateOpt.updateLineHeight, ss << style.GetLineHeight().ConvertToFp() << ", ");
    IF_TRUE(updateOpt.updateLetterSpacing, ss << style.GetLetterSpacing().ConvertToFp() << " ,");
    ss << "}, ";

    /* symbol style */
    ss << "sb={";
    IF_TRUE(updateOpt.updateSymbolFontSize, ss << updateOpt.updateSymbolFontSize->ConvertToFp() << ", ");
    IF_TRUE(updateOpt.updateSymbolFontWeight, ss  << StringUtils::ToString(*updateOpt.updateSymbolFontWeight) << ", ");
    IF_TRUE(updateOpt.updateSymbolRenderingStrategy, ss  << *updateOpt.updateSymbolRenderingStrategy  << ", ");
    IF_TRUE(updateOpt.updateSymbolEffectStrategy, ss << *updateOpt.updateSymbolEffectStrategy  << ", ");
    ss << "}, ";

    /* image style */
    ss << "im={[";
    IF_TRUE(updateOpt.updateImageWidth, ss << updateOpt.updateImageWidth->ToString() << ",");
    IF_TRUE(updateOpt.updateImageHeight, ss << updateOpt.updateImageHeight->ToString());
    ss << "], ";
    IF_TRUE(updateOpt.updateImageFit, ss << StringUtils::ToString(*updateOpt.updateImageFit) << ", ");
    IF_TRUE(updateOpt.updateImageVerticalAlign, ss << StringUtils::ToString(*updateOpt.updateImageVerticalAlign) << ", ");
    ss << "}";
    return ss.str();
}
}

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_UTILS_H