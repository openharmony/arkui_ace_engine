/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/date_picker_modifier.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "frameworks/core/components/common/properties/text_style.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
constexpr int POS_0 = 0;
constexpr int POS_1 = 1;
constexpr int POS_2 = 2;
const char DEFAULT_DELIMITER = '|';
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };
void SetSelectedTextStyle(
    NodeHandle node, const char* fontInfo, uint32_t color, int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);
    textStyle.fontSize =
        StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.fontFamily = Framework::ConvertStrToFontFamilies(res[POS_2]);
    textStyle.fontWeight = StringUtils::StringToFontWeight(res[POS_1]);
    textStyle.textColor = Color(color);
    DatePickerModelNG::SetSelectedTextStyle(frameNode, theme, textStyle);
}

void ResetSelectedTextStyle(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    auto selectedStyle = theme->GetOptionStyle(true, false);
    textStyle.textColor = selectedStyle.GetTextColor();
    textStyle.fontSize = selectedStyle.GetFontSize();
    textStyle.fontWeight = selectedStyle.GetFontWeight();
    DatePickerModelNG::SetSelectedTextStyle(frameNode, theme, textStyle);
}

void SetDatePickerTextStyle(
    NodeHandle node, const char* fontInfo, uint32_t color, int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);
    
    textStyle.fontSize =
        StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.fontFamily = Framework::ConvertStrToFontFamilies(res[POS_2]);
    textStyle.fontWeight=StringUtils::StringToFontWeight(res[POS_1]);
    textStyle.textColor = Color(color);
    DatePickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);
}

void ResetDatePickerTextStyle(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    auto normalStyle = theme->GetOptionStyle(false, false);
    textStyle.textColor = normalStyle.GetTextColor();
    textStyle.fontSize = normalStyle.GetFontSize();
    textStyle.fontWeight = normalStyle.GetFontWeight();
    DatePickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);
}

void SetDisappearTextStyle(
    NodeHandle node, const char* fontInfo, uint32_t color, int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);
    
    textStyle.fontSize =
        StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.fontFamily = Framework::ConvertStrToFontFamilies(res[POS_2]);
    textStyle.fontWeight=StringUtils::StringToFontWeight(res[POS_1]);
    textStyle.textColor = Color(color);
    DatePickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);
}

void ResetDisappearTextStyle(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    auto disappearStyle = theme->GetDisappearOptionStyle();
    textStyle.textColor = disappearStyle.GetTextColor();
    textStyle.fontSize = disappearStyle.GetFontSize();
    textStyle.fontWeight = disappearStyle.GetFontWeight();
    DatePickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);
}

void SetLunar(NodeHandle node, bool lunar)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetShowLunar(frameNode, lunar);
}

void ResetLunar(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetShowLunar(frameNode, false);
}

ArkUIDatePickerModifierAPI GetDatePickerModifier()
{
    static const ArkUIDatePickerModifierAPI modifier = { SetSelectedTextStyle, ResetSelectedTextStyle,
        SetDatePickerTextStyle, ResetDatePickerTextStyle, SetDisappearTextStyle,
        ResetDisappearTextStyle, SetLunar, ResetLunar };

    return modifier;
}
} // namespace OHOS::Ace::NG
