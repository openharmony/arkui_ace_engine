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

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_date_picker_modifier.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "frameworks/core/components/common/properties/text_style.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };
void SetSelectedTextStyle(
    NodeHandle node, const char* weightChar, const char* familiesChar, const int* values, double size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    textStyle.textColor = Color(values[NUM_0]);
    textStyle.fontSize = Dimension(size, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_1]));
    textStyle.fontStyle = FONT_STYLES[values[NUM_2]];
    std::string weight = weightChar;
    std::string families = familiesChar;
    textStyle.fontWeight = Framework::ConvertStrToFontWeight(weight);
    textStyle.fontFamily = Framework::ConvertStrToFontFamilies(families);
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
    NodeHandle node, const char* weightChar, const char* familiesChar, const int* values, double size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    textStyle.textColor = Color(values[NUM_0]);
    textStyle.fontSize = Dimension(size, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_1]));
    textStyle.fontStyle = FONT_STYLES[values[NUM_2]];
    std::string weight = weightChar;
    std::string families = familiesChar;
    textStyle.fontWeight = Framework::ConvertStrToFontWeight(weight);
    textStyle.fontFamily = Framework::ConvertStrToFontFamilies(families);

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
    NodeHandle node, const char* weightChar, const char* familiesChar, const int* values, double size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    textStyle.textColor = Color(values[NUM_0]);
    textStyle.fontSize = Dimension(size, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_1]));
    textStyle.fontStyle = FONT_STYLES[values[NUM_2]];
    std::string weight = weightChar;
    std::string families = familiesChar;
    textStyle.fontWeight = Framework::ConvertStrToFontWeight(weight);
    textStyle.fontFamily = Framework::ConvertStrToFontFamilies(families);
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
