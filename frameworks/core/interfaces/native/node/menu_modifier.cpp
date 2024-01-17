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
#include "core/interfaces/native/node/menu_modifier.h"

#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/menu/menu_model_ng.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::NG {
const char DELIMITER = '|';
constexpr int32_t SIZE_OF_FONT_INFO = 3;
static const char* ERR_CODE = "-1";
const std::string DEFAULT_FONT_WEIGHT = "normal";
const std::string DEFAULT_FONT_FAMILY = "HarmonyOS Sans";
const Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };
void SetMenuFontColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuModelNG::SetFontColor(frameNode, Color(color));
}

void ResetMenuFontColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> color = std::nullopt;
    MenuModelNG::SetFontColor(frameNode, color);
}

void SetMenuFont(NodeHandle node, const char* fontInfo, int32_t styleVal)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DELIMITER, res);
    if (res.empty() || res.size() != SIZE_OF_FONT_INFO) {
        return;
    }

    CalcDimension fontSize;
    if (res[0] != ERR_CODE) { // 0: index of font size data
        fontSize = StringUtils::StringToCalcDimension(res[0], false, DimensionUnit::FP);
    }
    MenuModelNG::SetFontSize(frameNode, fontSize);

    if (res[1] != ERR_CODE) { // 1: index of font weight data
        MenuModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(res[1]));
    } else {
        MenuModelNG::SetFontWeight(frameNode, FontWeight::NORMAL);
    }

    if (styleVal >= 0 && styleVal < static_cast<int32_t>(FONT_STYLES.size())) {
        MenuModelNG::SetFontStyle(frameNode, FONT_STYLES[styleVal]);
    } else {
        MenuModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
    }

    if (res[2] != ERR_CODE) { // 2: index of font family data
        MenuModelNG::SetFontFamily(frameNode, Framework::ConvertStrToFontFamilies(res[2]));
    } else {
        MenuModelNG::SetFontFamily(frameNode, Framework::ConvertStrToFontFamilies(DEFAULT_FONT_FAMILY));
    }
}

void ResetMenuFont(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension fontSize;
    FontWeight fontWeight = StringUtils::StringToFontWeight(DEFAULT_FONT_WEIGHT);
    MenuModelNG::SetFontSize(frameNode, fontSize);
    MenuModelNG::SetFontWeight(frameNode, fontWeight);
    MenuModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
    MenuModelNG::SetFontFamily(frameNode, Framework::ConvertStrToFontFamilies(DEFAULT_FONT_FAMILY));
}

void SetRadius(NodeHandle node, const double* values, const int32_t* units)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto topLeft =
        Dimension(values[0], static_cast<OHOS::Ace::DimensionUnit>(units[0])); // 0: index of top left value
    auto topRight =
        Dimension(values[1], static_cast<OHOS::Ace::DimensionUnit>(units[1])); // 1: index of top right value
    auto bottomLeft =
        Dimension(values[2], static_cast<OHOS::Ace::DimensionUnit>(units[2])); // 2: index of bottom left value
    auto bottomRight =
        Dimension(values[3], static_cast<OHOS::Ace::DimensionUnit>(units[3])); // 3: index of bottom right value
    MenuModelNG::SetBorderRadius(frameNode, topLeft, topRight, bottomLeft, bottomRight);
}

void ResetRadius(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::CalcDimension reset;
    MenuModelNG::SetBorderRadius(frameNode, reset);
}

void SetMenuWidth(NodeHandle node, double value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    MenuModelNG::SetWidth(frameNode, width);
}

void ResetMenuWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::CalcDimension reset;
    MenuModelNG::SetWidth(frameNode, reset);
}

ArkUIMenuModifierAPI GetMenuModifier()
{
    static const ArkUIMenuModifierAPI modifier = { SetMenuFontColor, ResetMenuFontColor, SetMenuFont, ResetMenuFont,
        SetRadius, ResetRadius, SetMenuWidth, ResetMenuWidth };

    return modifier;
}
} // namespace OHOS::Ace::NG