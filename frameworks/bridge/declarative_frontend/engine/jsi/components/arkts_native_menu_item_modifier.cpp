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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_menu_item_modifier.h"

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::NG {
constexpr uint32_t DEFAULT_MENUITEM_LABELFONTCOLOR_COLOR = 0xFF182431;
constexpr uint32_t DEFAULT_MENUITEM_FONTCOLOR_COLOR = 0xFF182431;
const char DELIMITER = '|';
constexpr int32_t SIZE_OF_FONT_INFO = 4;
const int POS_0 = 0;
const int POS_1 = 1;
const int POS_2 = 2;
const int POS_3 = 3;
static const char* ERR_CODE = "-1";
const std::string DEFAULT_SIZE = "24.0vp";
const std::string DEFAULT_FONT_WEIGHT = "normal";
const std::string DEFAULT_FONT_FAMILY = "HarmonyOS Sans";
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };
void SetMenuItemSelected(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelNG::SetSelected(frameNode, value);
}
void ResetMenuItemSelected(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelNG::SetSelected(frameNode, false);
}
void SetLabelFontColor(NodeHandle node, const uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelNG::SetLabelFontColor(frameNode, Color(color));
}
void ResetLabelFontColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelNG::SetLabelFontColor(frameNode, Color(DEFAULT_MENUITEM_LABELFONTCOLOR_COLOR));
}
void SetContentFontColor(NodeHandle node, const uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelNG::SetFontColor(frameNode, Color(color));
}
void ResetContentFontColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelNG::SetFontColor(frameNode, Color(DEFAULT_MENUITEM_FONTCOLOR_COLOR));
}
void SetLabelFont(NodeHandle node, const char* fontInfo, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DELIMITER, res);
    if (res.empty() || res.size() != SIZE_OF_FONT_INFO) {
        return;
    }
    CalcDimension fontSize = Dimension(-1.0);
    if (res[POS_0] != ERR_CODE) {
        fontSize = CalcDimension(res[POS_0], static_cast<OHOS::Ace::DimensionUnit>(unit));
    }
    MenuItemModelNG::SetLabelFontSize(frameNode, fontSize);

    if (res[POS_1] != ERR_CODE) {
        MenuItemModelNG::SetLabelFontWeight(frameNode, Framework::ConvertStrToFontWeight(res[POS_1]));
    } else {
        MenuItemModelNG::SetLabelFontWeight(frameNode, FontWeight::NORMAL);
    }

    if (res[POS_2] != ERR_CODE) {
        MenuItemModelNG::SetLabelFontStyle(frameNode, Framework::ConvertStrToFontStyle(res[POS_2]));
    } else {
        MenuItemModelNG::SetLabelFontStyle(frameNode, FONT_STYLES[0]);
    }

    if (res[POS_3] != ERR_CODE) {
        MenuItemModelNG::SetLabelFontFamily(frameNode, Framework::ConvertStrToFontFamilies(res[POS_3]));
    }
}
void ResetLabelFont(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension fontSize =
        StringUtils::StringToCalcDimension(DEFAULT_SIZE, false, DimensionUnit::FP);
    FontWeight fontWeight = StringUtils::StringToFontWeight(DEFAULT_FONT_WEIGHT);
    std::vector<std::string> fontFamily =
        Framework::ConvertStrToFontFamilies(std::string(DEFAULT_FONT_FAMILY));
    OHOS::Ace::FontStyle fontStyle = FONT_STYLES[0];

    MenuItemModelNG::SetLabelFontSize(frameNode, fontSize);
    MenuItemModelNG::SetLabelFontWeight(frameNode, fontWeight);
    MenuItemModelNG::SetLabelFontFamily(frameNode, fontFamily);
    MenuItemModelNG::SetLabelFontStyle(frameNode, fontStyle);
}
void SetContentFont(NodeHandle node, const char* fontInfo, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DELIMITER, res);
    if (res.empty() || res.size() != SIZE_OF_FONT_INFO) {
        return;
    }

    CalcDimension fontSize = Dimension(-1.0);
    if (res[POS_0] != ERR_CODE) {
        fontSize = CalcDimension(res[POS_0], static_cast<OHOS::Ace::DimensionUnit>(unit));
    }
    MenuItemModelNG::SetFontSize(frameNode, fontSize);

    if (res[POS_1] != ERR_CODE) {
        MenuItemModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(res[POS_1]));
    } else {
        MenuItemModelNG::SetFontWeight(frameNode, FontWeight::NORMAL);
    }

    if (res[POS_2] != ERR_CODE) {
        MenuItemModelNG::SetFontStyle(frameNode, Framework::ConvertStrToFontStyle(res[POS_2]));
    } else {
        MenuItemModelNG::SetFontStyle(frameNode, FONT_STYLES[0]);
    }

    if (res[POS_3] != ERR_CODE) {
        MenuItemModelNG::SetFontFamily(frameNode, Framework::ConvertStrToFontFamilies(res[POS_3]));
    }
}
void ResetContentFont(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension fontSize =
        StringUtils::StringToCalcDimension(DEFAULT_SIZE, false, DimensionUnit::FP);
    FontWeight fontWeight = StringUtils::StringToFontWeight(DEFAULT_FONT_WEIGHT);
    std::vector<std::string> fontFamily =
        Framework::ConvertStrToFontFamilies(std::string(DEFAULT_FONT_FAMILY));
    OHOS::Ace::FontStyle fontStyle = FONT_STYLES[0];

    MenuItemModelNG::SetFontSize(frameNode, fontSize);
    MenuItemModelNG::SetFontWeight(frameNode, fontWeight);
    MenuItemModelNG::SetFontFamily(frameNode, fontFamily);
    MenuItemModelNG::SetFontStyle(frameNode, fontStyle);
}

ArkUIMenuItemModifierAPI GetMenuItemModifier()
{
    static const ArkUIMenuItemModifierAPI modifier = { SetMenuItemSelected, ResetMenuItemSelected, SetLabelFontColor,
        ResetLabelFontColor, SetContentFontColor, ResetContentFontColor, SetLabelFont, ResetLabelFont, SetContentFont,
        ResetContentFont };

    return modifier;
}
} // namespace OHOS::Ace::NG