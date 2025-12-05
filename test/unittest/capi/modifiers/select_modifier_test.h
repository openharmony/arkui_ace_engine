/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GENERATED_FOUNDATION_ACE_CAPI_TEST_SELECT_H
#define GENERATED_FOUNDATION_ACE_CAPI_TEST_SELECT_H
#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "generated/test_fixtures.h"
#include "generated/type_helpers.h"

#include "core/components/select/select_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_pattern.h"

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;

namespace SelectTest {
enum ResIntegerID {
    INT_RES_0_ID,
    INT_RES_1_ID,
    INT_RES_2_ID,
    INT_RES_3_ID,
    INT_RES_4_ID,
    INT_RES_5_ID,
    INT_RES_6_ID,
    STR_RES_0_ID,
    STR_RES_1_ID,
    COLOR_RES_0_ID,
    FONT_FAMILY_RES_1_ID,
    VALUE_RES_1_ID,
    OPTIONS_VALUE_RES_1_ID,
    OPTIONS_ICON_RES_1_ID,
};

constexpr auto COLOR_RES_0_STR = "COLOR_RES_0_STR";
constexpr auto INT_RES_0_STR = "INTEGER_RES_0_STR";
constexpr auto INT_RES_1_STR = "INTEGER_RES_1_STR";
constexpr auto INT_RES_2_STR = "INTEGER_RES_2_STR";
constexpr auto INT_RES_3_STR = "INTEGER_RES_3_STR";
constexpr auto INT_RES_4_STR = "INTEGER_RES_4_STR";
constexpr auto INT_RES_5_STR = "INTEGER_RES_5_STR";
constexpr auto INT_RES_6_STR = "INTEGER_RES_6_STR";
constexpr auto STR_RES_0_STR = "STRING_RES_0_STR";
constexpr auto STR_RES_1_STR = "STRING_RES_1_STR";
const auto FONT_FAMILY_RES_NAME = "Family resource name";
const auto FONT_FAMILY_RES_VALUE = "FontFamilyA,FontFamilyB,   FontFamilyC";

const auto VALUE_RES_NAME = "Value resource name";
const auto VALUE_RES_VALUE = "Select value";

const auto OPTIONS_VALUE_RES_NAME = "SelectOption value resource name";
const auto OPTIONS_VALUE_RES_VALUE = "SelectOption value";

const auto OPTIONS_ICON_RES_NAME = "SelectOption icon resource name";
const auto OPTIONS_ICON_RES_VALUE = "SelectOption icon";

const auto THEME_SPACE = Dimension(23, DimensionUnit::PX);
const double THEME_FONT_OPACITY = 0.5;
const Color THEME_BACKGROUND_COLOR(0xFFAABBC1);
const Color THEME_FONT_COLOR(0xFFAABBC3);
const Color THEME_SELECTED_OPTION_FONT_COLOR(0xFFAABBC4);
const Color DEFAULT_FONT_COLOR = THEME_FONT_COLOR.BlendOpacity(THEME_FONT_OPACITY);

const auto DEFAULT_FONT_SIZE = "16.00fp";
const auto DEFAULT_FONT_WEIGHT = "FontWeight.Normal";
const auto DEFAULT_FONT_FAMILY = "";
const auto DEFAULT_FONT_STYLE = "FontStyle.Normal";
const auto EXPECTED_FONT_SIZE = "12.00px";
const auto EXPECTED_FONT_WEIGHT = "FontWeight.Bold";
const auto EXPECTED_FONT_FAMILY = "TestFontFamily";
const auto EXPECTED_FONT_STYLE = "FontStyle.Italic";

const auto SELECTED_INDEX = ArkUnion<Opt_Union_I32_Resource_Bindable_I32_Bindable_Resource, Ark_Int32>(1);
const auto INVALID_INDEX = ArkUnion<Opt_Union_I32_Resource_Bindable_I32_Bindable_Resource, Ark_Int32>(-1);

// length values
const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);
const auto ALEN_VP_POS = ArkValue<Ark_Length>(AFLT32_POS);
const auto ALEN_VP_NEG = ArkValue<Ark_Length>(AFLT32_NEG);
const auto OPT_LEN_VP_POS = ArkValue<Opt_Length>(AFLT32_POS);
const auto OPT_LEN_VP_NEG = ArkValue<Opt_Length>(AFLT32_NEG);
const auto OPT_DIM_VP_POS = ArkValue<Opt_Dimension>(AFLT32_POS);
const auto OPT_DIM_VP_NEG = ArkValue<Opt_Dimension>(AFLT32_NEG);

// check length
const std::string CHECK_POSITIVE_VALUE_INT("1234.00px");
const std::string CHECK_NEGATIVE_VALUE_INT("-2147483648.00px");
const std::string CHECK_POSITIVE_VALUE_FLOAT("1.23vp");
const std::string CHECK_POSITIVE_VALUE_FLOAT_PX("1.23px");
const std::string CHECK_NEGATIVE_VALUE_FLOAT("-5.68vp");

const auto FONT_ATTR("font");
const auto SELECTED_OPTION_FONT_ATTR("selectedOptionFont");
const auto OPTION_FONT_ATTR("optionFont");
const auto FONT_SIZE("size");
const auto FONT_FAMILY("family");
const auto FONT_WEIGHT("weight");
const auto FONT_STYLE("style");

const auto ATTRIBUTE_FONT_NAME = "font";
const auto ATTRIBUTE_SELECTED_OPTION_FONT_NAME = "selectedOptionFont";
const auto ATTRIBUTE_OPTION_FONT_NAME = "optionFont";
const auto ATTRIBUTE_DIVIDER_NAME = "divider";
const auto ATTRIBUTE_MENU_ALIGN_NAME = "menuAlign";
const auto ATTRIBUTE_MENU_ALIGN_I_OFFSET_NAME = "offset";
const auto ATTRIBUTE__NAME = "options";
const auto ATTRIBUTE_SELECTED_NAME = "selected";
const auto ATTRIBUTE_SELECTED_DEFAULT_VALUE = "-1";
const auto ATTRIBUTE_VALUE_NAME = "value";
const auto ATTRIBUTE_VALUE_DEFAULT_VALUE = "";
const auto ATTRIBUTE_FONT_I_SIZE_NAME = "size";
const auto ATTRIBUTE_FONT_I_SIZE_DEFAULT_VALUE = "14.00px";
const auto ATTRIBUTE_FONT_I_WEIGHT_NAME = "weight";
const auto ATTRIBUTE_FONT_I_WEIGHT_DEFAULT_VALUE = "FontWeight.Normal";
const auto ATTRIBUTE_FONT_I_FAMILY_NAME = "family";
const auto ATTRIBUTE_FONT_I_FAMILY_DEFAULT_VALUE = "";
const auto ATTRIBUTE_FONT_I_STYLE_NAME = "style";
const auto ATTRIBUTE_FONT_I_STYLE_DEFAULT_VALUE = "FontStyle.Normal";
const auto ATTRIBUTE_FONT_COLOR_NAME = "fontColor";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = DEFAULT_FONT_COLOR.ToString();
const auto ATTRIBUTE_SELECTED_OPTION_BG_COLOR_NAME = "selectedOptionBgColor";
const auto ATTRIBUTE_SELECTED_OPTION_BG_COLOR_DEFAULT_VALUE = "";
const auto ATTRIBUTE_SELECTED_OPTION_FONT_I_SIZE_NAME = "size";
const auto ATTRIBUTE_SELECTED_OPTION_FONT_I_SIZE_DEFAULT_VALUE = "14.00px";
const auto ATTRIBUTE_SELECTED_OPTION_FONT_I_WEIGHT_NAME = "weight";
const auto ATTRIBUTE_SELECTED_OPTION_FONT_I_WEIGHT_DEFAULT_VALUE = "FontWeight.Normal";
const auto ATTRIBUTE_SELECTED_OPTION_FONT_I_FAMILY_NAME = "family";
const auto ATTRIBUTE_SELECTED_OPTION_FONT_I_FAMILY_DEFAULT_VALUE = "";
const auto ATTRIBUTE_SELECTED_OPTION_FONT_I_STYLE_NAME = "style";
const auto ATTRIBUTE_SELECTED_OPTION_FONT_I_STYLE_DEFAULT_VALUE = "FontStyle.Normal";
const auto ATTRIBUTE_SELECTED_OPTION_FONT_COLOR_NAME = "selectedOptionFontColor";
const auto ATTRIBUTE_SELECTED_OPTION_FONT_COLOR_DEFAULT_VALUE = "#FFAABBC4";
const auto ATTRIBUTE_OPTION_BG_COLOR_NAME = "optionBgColor";
const auto ATTRIBUTE_OPTION_BG_COLOR_DEFAULT_VALUE = "#00000000";
const auto ATTRIBUTE_OPTION_FONT_I_SIZE_NAME = "size";
const auto ATTRIBUTE_OPTION_FONT_I_SIZE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_OPTION_FONT_I_WEIGHT_NAME = "weight";
const auto ATTRIBUTE_OPTION_FONT_I_WEIGHT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_OPTION_FONT_I_FAMILY_NAME = "family";
const auto ATTRIBUTE_OPTION_FONT_I_FAMILY_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_OPTION_FONT_I_STYLE_NAME = "style";
const auto ATTRIBUTE_OPTION_FONT_I_STYLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_OPTION_FONT_COLOR_NAME = "optionFontColor";
const auto ATTRIBUTE_OPTION_FONT_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SPACE_NAME = "space";
const auto ATTRIBUTE_SPACE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ARROW_POSITION_NAME = "arrowPosition";
const auto ATTRIBUTE_ARROW_POSITION_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_OPTION_WIDTH_NAME = "optionWidth";
const auto ATTRIBUTE_OPTION_WIDTH_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_OPTION_HEIGHT_NAME = "optionHeight";
const auto ATTRIBUTE_OPTION_HEIGHT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MENU_BACKGROUND_COLOR_NAME = "menuBackgroundColor";
const auto ATTRIBUTE_MENU_BACKGROUND_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MENU_BACKGROUND_BLUR_STYLE_NAME = "menuBackgroundBlurStyle";
const auto ATTRIBUTE_MENU_BACKGROUND_BLUR_STYLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_CONTROL_SIZE_NAME = "controlSize";
const auto ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_DIVIDER_I_STROKE_WIDTH_NAME = "strokeWidth";
const auto ATTRIBUTE_DIVIDER_I_STROKE_WIDTH_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_DIVIDER_I_COLOR_NAME = "color";
const auto ATTRIBUTE_DIVIDER_I_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_DIVIDER_I_START_MARGIN_NAME = "startMargin";
const auto ATTRIBUTE_DIVIDER_I_START_MARGIN_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_DIVIDER_I_END_MARGIN_NAME = "endMargin";
const auto ATTRIBUTE_DIVIDER_I_END_MARGIN_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MENU_ALIGN_I_ALIGN_TYPE_NAME = "alignType";
const auto ATTRIBUTE_MENU_ALIGN_I_ALIGN_TYPE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MENU_ALIGN_I_OFFSET_I_DX_NAME = "dx";
const auto ATTRIBUTE_MENU_ALIGN_I_OFFSET_I_DX_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MENU_ALIGN_I_OFFSET_I_DY_NAME = "dy";
const auto ATTRIBUTE_MENU_ALIGN_I_OFFSET_I_DY_DEFAULT_VALUE = "!NOT-DEFINED!";

extern std::vector<std::tuple<std::string, Ark_Resource, std::string>> testColorsResValidValues;
extern std::vector<std::tuple<std::string, Ark_Resource, std::string>> testStringResValidValues;
extern std::vector<std::tuple<std::string, Ark_Resource, std::string>> testIntResValidValues;
extern std::vector<std::tuple<std::string, Ark_String, std::string>> testWeightStringValidValues;
extern std::vector<std::tuple<ResIntegerID, std::string, OHOS::Ace::ResRawValue>> resourceInitTable;

const Ark_arkui_component_units_Font TEST_ARK_FONT = {
    .size = ArkValue<Opt_Length>("12.0px"),
    .weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLD),
    .family = ArkUnion<Opt_Union_String_Resource, Ark_String>("TestFontFamily"),
    .style = ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_ITALIC),
};

const std::vector<Ark_SelectOption> SELECT_PARAMS = {
    { .value = ArkUnion<Ark_ResourceStr, Ark_String>("Option A") },
    { .value = ArkUnion<Ark_ResourceStr, Ark_String>("Option B") },
    { .value = ArkUnion<Ark_ResourceStr, Ark_String>("Option C") },
};
}

class SelectModifierTest : public ModifierTestBase<GENERATED_ArkUISelectModifier,
    &GENERATED_ArkUINodeModifiers::getSelectModifier, GENERATED_ARKUI_SELECT> {
public:
    static void SetUpTestCase()
    {
        using namespace SelectTest;
        ModifierTestBase::SetUpTestCase();

        // set test values to Theme Pattern as data for the Theme building
        auto themeStyle = SetupThemeStyle("select_pattern");
        themeStyle->SetAttr("content_spinner_padding", { .value = THEME_SPACE });
        themeStyle->SetAttr("bg_color", { .value = THEME_BACKGROUND_COLOR });
        themeStyle->SetAttr("text_color", { .value = THEME_FONT_COLOR });
        themeStyle->SetAttr("text_color_selected", { .value = THEME_SELECTED_OPTION_FONT_COLOR });
        themeStyle->SetAttr("menu_text_primary_alpha", { .value = THEME_FONT_OPACITY });

        SetupTheme<SelectTheme>();
        SetupTheme<TextTheme>();
        SetupTheme<IconTheme>();
        for (auto& [id, strid, res] : resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }

    void SetUp(void) override
    {
        using namespace SelectTest;
        ModifierTestBase::SetUp();

        ASSERT_NE(modifier_->setSelectOptions, nullptr);
        auto arrayHolder = ArkArrayHolder<Array_SelectOption>(SELECT_PARAMS);
        auto arkArray = arrayHolder.ArkValue();
        modifier_->setSelectOptions(node_, &arkArray);

        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_TRUE(frameNode);
        auto selectPattern = frameNode->GetPatternPtr<SelectPattern>();
        ASSERT_TRUE(selectPattern);
        std::vector<RefPtr<FrameNode>> options = selectPattern->GetOptions();
        ASSERT_FALSE(options.empty());
        auto optionFrameNode = options[0];
        ASSERT_TRUE(optionFrameNode);
        auto pattern = optionFrameNode->GetPattern();
        ASSERT_TRUE(pattern);
        pattern->OnModifyDone(); // Init selectTheme
    }
};

} // namespace OHOS::Ace::NG

#endif // GENERATED_FOUNDATION_ACE_CAPI_TEST_SELECT_H
