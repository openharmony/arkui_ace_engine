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

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/menu/menu_model_ng.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::NG {
const char DELIMITER = '|';
constexpr int32_t SIZE_OF_FONT_INFO = 3;
const int NUM_0 = 0;
const int NUM_1 = 1;
const int NUM_2 = 2;
const int NUM_3 = 3;
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
    if (res[NUM_0] != ERR_CODE) {
        fontSize = StringUtils::StringToCalcDimension(res[NUM_0], false, DimensionUnit::FP);
    }
    MenuModelNG::SetFontSize(frameNode, fontSize);

    if (res[NUM_1] != ERR_CODE) {
        MenuModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(res[NUM_1]));
    } else {
        MenuModelNG::SetFontWeight(frameNode, FontWeight::NORMAL);
    }

    if (styleVal >= 0 && styleVal < static_cast<int32_t>(FONT_STYLES.size())) {
        MenuModelNG::SetFontStyle(frameNode, FONT_STYLES[styleVal]);
    } else {
        MenuModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
    }

    if (res[NUM_2] != ERR_CODE) {
        MenuModelNG::SetFontFamily(frameNode, Framework::ConvertStrToFontFamilies(res[NUM_2]));
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
void SetRadius(NodeHandle node, const double* values, const int* units)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto topLeft = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    auto topRight = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    auto bottomLeft = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    auto bottomRight = Dimension(values[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]));
    MenuModelNG::SetBorderRadius(frameNode, topLeft, topRight, bottomLeft, bottomRight);
}
void ResetRadius(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::CalcDimension reset;
    MenuModelNG::SetBorderRadius(frameNode, reset);
}
ArkUIMenuModifierAPI GetMenuModifier()
{
    static const ArkUIMenuModifierAPI modifier = { SetMenuFontColor, ResetMenuFontColor, SetMenuFont, ResetMenuFont,
        SetRadius, ResetRadius };

    return modifier;
}
} // namespace OHOS::Ace::NG