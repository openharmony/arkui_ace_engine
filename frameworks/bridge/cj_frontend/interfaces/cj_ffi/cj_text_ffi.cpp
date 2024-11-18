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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_text_ffi.h"


#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<TextCase> TEXT_CASES = { TextCase::NORMAL, TextCase::LOWERCASE, TextCase::UPPERCASE };
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::CLIP, TextOverflow::ELLIPSIS, TextOverflow::NONE };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END, TextAlign::LEFT,
    TextAlign::RIGHT, TextAlign::JUSTIFY };
const std::vector<TextDecoration> TEXT_DECORATIONS = { TextDecoration::NONE, TextDecoration::UNDERLINE,
    TextDecoration::OVERLINE, TextDecoration::LINE_THROUGH };
} // namespace

extern "C" {
void FfiOHOSAceFrameworkTextCreate(const char* content)
{
    TextModel::GetInstance()->Create(content);
}

void FfiOHOSAceFrameworkTextSetWidth(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));
    ViewAbstractModel::GetInstance()->SetWidth(value);
    TextModel::GetInstance()->OnSetWidth();
}

void FfiOHOSAceFrameworkTextSetHeight(double height, int32_t unit)
{
    Dimension value(height, static_cast<DimensionUnit>(unit));
    ViewAbstractModel::GetInstance()->SetHeight(value);
    TextModel::GetInstance()->OnSetHeight();
}

void FfiOHOSAceFrameworkTextSetFontSize(double fontSize, int32_t unit)
{
    Dimension value(fontSize, static_cast<DimensionUnit>(unit));
    TextModel::GetInstance()->SetFontSize(value);
}

void FfiOHOSAceFrameworkTextSetFontWeight(const char* fontWeight)
{
    TextModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(fontWeight));
}

void FfiOHOSAceFrameworkTextSetFontColor(uint32_t textColor)
{
    TextModel::GetInstance()->SetTextColor(Color(textColor));
}

void FfiOHOSAceFrameworkTextSetTextOverflow(int32_t overflow)
{
    if (!Utils::CheckParamsValid(overflow, TEXT_OVERFLOWS.size())) {
        LOGE("invalid value for over flow");
        return;
    }
    TextModel::GetInstance()->SetTextOverflow(TEXT_OVERFLOWS[overflow]);
}

void FfiOHOSAceFrameworkTextSetMaxLines(int32_t maxLines)
{
    TextModel::GetInstance()->SetMaxLines(maxLines);
}

void FfiOHOSAceFrameworkTextSetFontStyle(int32_t fontStyle)
{
    if (!Utils::CheckParamsValid(fontStyle, FONT_STYLES.size())) {
        LOGE("invalid value for font style");
        return;
    }
    TextModel::GetInstance()->SetItalicFontStyle(FONT_STYLES[fontStyle]);
}

void FfiOHOSAceFrameworkTextSetTextAlign(int32_t textAlign)
{
    if (!Utils::CheckParamsValid(textAlign, TEXT_ALIGNS.size())) {
        LOGE("invalid value for text align");
        return;
    }
    TextModel::GetInstance()->SetTextAlign(TEXT_ALIGNS[textAlign]);
}

void FfiOHOSAceFrameworkTextSetLineHeight(double lineHeight, int32_t unit)
{
    Dimension dimValue(lineHeight, static_cast<DimensionUnit>(unit));
    TextModel::GetInstance()->SetLineHeight(dimValue);
}

void FfiOHOSAceFrameworkTextSetFontFamily(const char* fontFamily)
{
    std::vector<std::string> fontFamilies;
    fontFamilies = ConvertStrToFontFamilies(fontFamily);
    TextModel::GetInstance()->SetFontFamily(fontFamilies);
}

void FfiOHOSAceFrameworkTextSetDecoration(int32_t typeValue, uint32_t colorValue)
{
    if (!Utils::CheckParamsValid(typeValue, TEXT_DECORATIONS.size())) {
        LOGE("invalid value for text decoration");
        return;
    }
    TextModel::GetInstance()->SetTextDecoration(TEXT_DECORATIONS[typeValue]);
    TextModel::GetInstance()->SetTextDecorationColor(Color(colorValue));
}

void FfiOHOSAceFrameworkTextSetMinFontSize(double fontSize, int32_t unit)
{
    Dimension dimValue(fontSize, static_cast<DimensionUnit>(unit));
    TextModel::GetInstance()->SetAdaptMinFontSize(dimValue);
}

void FfiOHOSAceFrameworkTextSetMaxFontSize(double fontSize, int32_t unit)
{
    Dimension dimValue(fontSize, static_cast<DimensionUnit>(unit));
    TextModel::GetInstance()->SetAdaptMaxFontSize(dimValue);
}

void FfiOHOSAceFrameworkTextSetTextCase(int32_t textCase)
{
    if (!Utils::CheckParamsValid(textCase, TEXT_CASES.size())) {
        LOGE("invalid value for text case");
        return;
    }
    TextModel::GetInstance()->SetTextCase(TEXT_CASES[textCase]);
}

void FfiOHOSAceFrameworkTextSetBaselineOffset(double baseLine, int32_t unit)
{
    Dimension dimValue(baseLine, static_cast<DimensionUnit>(unit));
    TextModel::GetInstance()->SetBaselineOffset(dimValue);
}

void FfiOHOSAceFrameworkTextOnClick(void (*callback)(CJClickInfo clickInfo)) {}

void FfiTextSetResponseRegion(CJResponseRegion value)
{
    std::vector<DimensionRect> result;
    ParseCJResponseRegion(value, result);
    ViewAbstractModel::GetInstance()->SetResponseRegion(result);
    TextModel::GetInstance()->SetResponseRegion(true);
}

void FfiTextSetResponseRegionArray(VectorStringPtr vecContent)
{
    std::vector<DimensionRect> result;
    ParseVectorStringPtr(vecContent, result);
    ViewAbstractModel::GetInstance()->SetResponseRegion(result);
    TextModel::GetInstance()->SetResponseRegion(true);
}
}