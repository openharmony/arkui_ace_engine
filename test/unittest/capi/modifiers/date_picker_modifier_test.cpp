/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include <gtest/gtest.h>

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/picker/datepicker_event_hub.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/picker/picker_theme.h"
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
// Attribute names
const auto ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME = "disappearTextStyle";
const auto ATTRIBUTE_TEXT_STYLE_NAME = "textStyle";
const auto ATTRIBUTE_SELECTED_TEXT_STYLE_NAME = "selectedTextStyle";
const auto ATTRIBUTE_LUNAR_NAME = "lunar";
const auto ATTRIBUTE_COLOR_NAME = "color";
const auto ATTRIBUTE_FONT_NAME = "font";
const auto ATTRIBUTE_FONT_SIZE_NAME = "size";
const auto ATTRIBUTE_FONT_WEIGHT_NAME = "weight";
const auto ATTRIBUTE_FONT_STYLE_NAME = "style";
const auto ATTRIBUTE_FONT_FAMILY_NAME = "family";
const auto ATTRIBUTE_CONSTRUCTOR_NAME = "constructor";
const auto ATTRIBUTE_DATE_START_NAME = "start";
const auto ATTRIBUTE_DATE_END_NAME = "end";
const auto ATTRIBUTE_DATE_SELECT_NAME = "selected";

// Expected values
const std::string COLOR_BLACK = "#FF000000";
const std::string COLOR_TRANSPARENT = "#00000000";

// Default values
const auto ATTRIBUTE_LUNAR_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "14.00px";
const auto ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE = "FontWeight.Normal";
const auto ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE = "FontStyle.Normal";
const auto ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE = "";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_DATE_START_DEFAULT_VALUE = PickerDate(1970, 1, 1);
const auto ATTRIBUTE_DATE_END_DEFAULT_VALUE = PickerDate(2100, 12, 31);
const auto ATTRIBUTE_DATE_SELECTED_DEFAULT_VALUE = PickerDate::Current();
const auto ATTRIBUTE_FONT_SIZE_DISAPPEAR_DEFAULT_VALUE = "14.00fp";
const auto ATTRIBUTE_FONT_SIZE_NORMAL_DEFAULT_VALUE = "16.00fp";
const auto ATTRIBUTE_FONT_SIZE_SELECTED_DEFAULT_VALUE = "20.00fp";
const auto ATTRIBUTE_FONT_WEIGHT_DISAPPEAR_DEFAULT_VALUE = "FontWeight.Regular";
const auto ATTRIBUTE_FONT_WEIGHT_NORMAL_DEFAULT_VALUE = "FontWeight.Regular";
const auto ATTRIBUTE_FONT_WEIGHT_SELECTED_DEFAULT_VALUE = "FontWeight.Medium";
const auto ATTRIBUTE_TEXT_COLOR_DISAPPEAR_DEFAULT_VALUE = "#FF182431";
const auto ATTRIBUTE_TEXT_COLOR_NORMAL_DEFAULT_VALUE = "#FF182431";
const auto ATTRIBUTE_TEXT_COLOR_SELECTED_DEFAULT_VALUE = "#FF007DFF";
#ifdef SUPPORT_DIGITAL_CROWN
const auto ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE = "1"; // equal "CrownSensitivity.MEDIUM"
const auto ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_NAME = "digitalCrownSensitivity";
#endif

// Test plans
// size
const Ark_Float32 AFLT32_POS(1.23f);
const Ark_Float32 AFLT32_NEG(-5.6789f);
const auto CHECK_AFLT32_POS = "1.23vp";

// color res
const auto RES_COLOR_ID = IntResourceId{102001, ResourceType::COLOR};
const auto RES_COLOR_ID_VALUE = Color(0xFF654321);
const auto RES_COLOR_NAME = NamedResourceId{"color_name", ResourceType::COLOR};
const auto RES_COLOR_NAME_VALUE = Color(0xFF123456);
const auto RES_COLOR_INVALID_ID = IntResourceId{-1, ResourceType::COLOR};
const auto RES_COLOR_INVALID_ID_VALUE = "#FFFF0000";


// font family res
const auto RES_FONT_FAMILY_NAME = NamedResourceId{"res_font_family_id", ResourceType::STRARRAY};
const auto RES_FONT_FAMILY_NAME_VALUE = "res_font_family_string_id";
const auto RES_FONT_FAMILY_ID = IntResourceId{102002, ResourceType::STRARRAY};
const auto RES_FONT_FAMILY_ID_VALUE = "res_font_family_number_id";
const auto RES_FONT_FAMILY_INVALID_ID = IntResourceId{-1, ResourceType::STRARRAY};
const auto RES_FONT_FAMILY_INVALID_ID_VALUE = ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE;

// font family
const auto FONT_FAMILY_STRING = "font_family_string";

// font family
typedef std::pair<Opt_Union_String_Resource, std::string> UnionStringResourceTestStep;
const std::vector<UnionStringResourceTestStep> FONT_FAMILY_TEST_PLAN = {
    { Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(CreateResource(RES_FONT_FAMILY_NAME)),
        RES_FONT_FAMILY_NAME_VALUE },
    { Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(CreateResource(RES_FONT_FAMILY_ID)),
        RES_FONT_FAMILY_ID_VALUE },
    { Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(CreateResource(RES_FONT_FAMILY_INVALID_ID)),
        RES_FONT_FAMILY_INVALID_ID_VALUE },
    { Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(FONT_FAMILY_STRING), FONT_FAMILY_STRING },
    { Converter::ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr), ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE },
};

// size ark=ok
typedef std::pair<Opt_Length, std::string> OptLengthTestStep;
const std::vector<OptLengthTestStep> FONT_SIZE_TEST_PLAN = {
    { Converter::ArkValue<Opt_Length>(AFLT32_POS), CHECK_AFLT32_POS },
    { Converter::ArkValue<Opt_Length>(AFLT32_NEG), ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Length>(Ark_Empty()), ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE },
};

// style ark=ok
typedef std::pair<Opt_FontStyle, std::string> ArkFontStyleTestStep;
const std::vector<ArkFontStyleTestStep> FONT_STYLE_TEST_PLAN = {
    { Converter::ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_NORMAL), "FontStyle.Normal" },
    { Converter::ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_ITALIC), "FontStyle.Italic" },
    { Converter::ArkValue<Opt_FontStyle>(static_cast<Ark_FontStyle>(-1)), ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_FontStyle>(static_cast<Ark_FontStyle>(INT_MAX)), ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_FontStyle>(Ark_Empty()), ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE },
};

// weight ark, string = ok
typedef std::pair<Opt_Union_FontWeight_I32_String, std::string> ArkFontWeightTest;
const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN = {
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_LIGHTER),
        "FontWeight.Lighter" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_NORMAL),
        "FontWeight.Normal" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_REGULAR),
        "FontWeight.Regular" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_MEDIUM),
        "FontWeight.Medium" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLD),
        "FontWeight.Bold" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLDER),
        "FontWeight.Bolder" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>(Converter::ArkValue<Ark_String>("lighter")),
        "FontWeight.Lighter" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>(Converter::ArkValue<Ark_String>("normal")),
        "FontWeight.Normal" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>(Converter::ArkValue<Ark_String>("regular")),
        "FontWeight.Regular" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>(Converter::ArkValue<Ark_String>("medium")),
        "FontWeight.Medium" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>(Converter::ArkValue<Ark_String>("bold")),
        "FontWeight.Bold" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>(Converter::ArkValue<Ark_String>("bolder")),
        "FontWeight.Bolder" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(static_cast<Ark_FontWeight>(-1)),
        ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(static_cast<Ark_FontWeight>(INT_MAX)),
        ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Empty>(nullptr),
        ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE },
};

const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN2 = {
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(100), "100" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(200), "200" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(300), "300" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(400), "400" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(500), "500" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(600), "600" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(700), "700" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(800), "800" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(900), "900" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("100"), "100" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("200"), "200" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("300"), "300" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("400"), "400" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("500"), "500" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("600"), "600" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("700"), "700" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("800"), "800" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("900"), "900" },
};

// color
typedef std::tuple<Opt_ResourceColor, std::string> ColorTestStep;
const std::vector<ColorTestStep> COLOR_TEST_PLAN = {
    { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0.5f), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Opt_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { Converter::ArkUnion<Opt_ResourceColor, Ark_String>("incorrect_color"), COLOR_BLACK },
    { Converter::ArkUnion<Opt_ResourceColor, Ark_String>(""), COLOR_BLACK },
    { Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_ID)),
        RES_COLOR_ID_VALUE.ColorToString() },
    { Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_NAME)),
        RES_COLOR_NAME_VALUE.ColorToString() },
    { Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_INVALID_ID)),
        RES_COLOR_INVALID_ID_VALUE },
    { Converter::ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr), ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE },
};

typedef std::pair<PickerDate, PickerDate> PickerDateTest;
const std::vector<PickerDateTest> CHANGE_EVENT_TEST_PLAN = {
    { PickerDate(1970, 1, 1), PickerDate(1970, 1, 1) },
    { PickerDate(2020, 12, 10), PickerDate(2020, 12, 10) },
    { PickerDate(2200, 12, 31), PickerDate(1970, 1, 1) },
    { PickerDate(0, -1, -5), PickerDate(1970, 1, 1) },
    { PickerDate(-1, 24, 64), PickerDate(1970, 1, 1) },
};
typedef std::pair<Ark_Boolean, std::string> BoolTest;
const std::vector<BoolTest> BOOL_TEST_PLAN = {
    { false, "false" },
    { true, "true" },
    { 0, "false" },
    { -25, "true" },
    { 25, "true" },
};
typedef std::pair<Opt_Boolean, std::string> OptBoolTest;
const std::vector<OptBoolTest> OPT_BOOL_TEST_PLAN = {
    { Converter::ArkValue<Opt_Boolean>(false), "false" },
    { Converter::ArkValue<Opt_Boolean>(true), "true" },
    { Converter::ArkValue<Opt_Boolean>(Ark_Empty()), "false" },
};

typedef std::tuple<PickerDate, PickerDate, PickerDate> PickerDateStepTest;
typedef std::tuple<std::string, std::string, std::string> PickerStringStepTest;
typedef std::pair<PickerDateStepTest, PickerStringStepTest> PickerDateOptionsStepTest;
const std::vector<PickerDateOptionsStepTest> PICKER_DATE_OPTIONS_TEST_PLAN = {
    { { PickerDate(1970, 1, 1), PickerDate(2100, 12, 31), PickerDate(2023, 7, 21) },
        { "1970-1-1", "2100-12-31", "2023-7-21" } },
    { { PickerDate(1975, 4, 3), PickerDate(2008, 11, 21), PickerDate(2007, 11, 22) },
        { "1975-4-3", "2008-11-21", "2007-11-22" } },
    { { PickerDate(2019, 7, 5), PickerDate(2024, 5, 4), PickerDate(2021, 1, 2) },
        { "2019-7-5", "2024-5-4", "2021-1-2" } },
    { { PickerDate(2018, 10, 115), PickerDate(2021, 111, 2), PickerDate(2119, 6, 8) },
        { "1970-1-1", "1970-1-1", "1970-1-1" } },
    { { PickerDate(-2019, 3, 2), PickerDate(2021, -5, 6), PickerDate(2024, 9, -10) },
        { "1970-1-1", "1970-1-1", "1970-1-1" } }
};

#ifdef SUPPORT_DIGITAL_CROWN
std::vector<std::tuple<std::string, Opt_CrownSensitivity, std::string>> testFixtureEnumCrownSensitivityTestPlan = {
    { "CrownSensitivity.LOW", Converter::ArkValue<Opt_CrownSensitivity>(ARK_CROWN_SENSITIVITY_LOW),
        "0" },
    { "CrownSensitivity.MEDIUM", Converter::ArkValue<Opt_CrownSensitivity>(ARK_CROWN_SENSITIVITY_MEDIUM),
        "1" },
    { "CrownSensitivity.HIGH", Converter::ArkValue<Opt_CrownSensitivity>(ARK_CROWN_SENSITIVITY_HIGH),
        "2" },
    { "-1", Converter::ArkValue<Opt_CrownSensitivity>(static_cast<Ark_CrownSensitivity>(-1)),
        ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE },
    { "INT_MAX", Converter::ArkValue<Opt_CrownSensitivity>(static_cast<Ark_CrownSensitivity>(INT_MAX)),
        ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE },
    { "Ark_Empty", Converter::ArkValue<Opt_CrownSensitivity>(static_cast<Ark_CrownSensitivity>(INT_MAX)),
        ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE },
};
#endif

std::string ToJsonString(const PickerDate& pickerDate)
{
    return std::to_string(pickerDate.GetYear()) + "-" + std::to_string(pickerDate.GetMonth()) + "-" +
           std::to_string(pickerDate.GetDay());
}
} // namespace

class DatePickerModifierTest : public ModifierTestBase<GENERATED_ArkUIDatePickerModifier,
    &GENERATED_ArkUINodeModifiers::getDatePickerModifier, GENERATED_ARKUI_DATE_PICKER> {
    public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<PickerTheme>();

        AddResource(RES_FONT_FAMILY_NAME, RES_FONT_FAMILY_NAME_VALUE);
        AddResource(RES_FONT_FAMILY_ID, RES_FONT_FAMILY_ID_VALUE);
        AddResource(RES_FONT_FAMILY_INVALID_ID, RES_FONT_FAMILY_INVALID_ID_VALUE);
        AddResource(RES_COLOR_ID, RES_COLOR_ID_VALUE);
        AddResource(RES_COLOR_NAME, RES_COLOR_NAME_VALUE);
        AddResource(RES_COLOR_INVALID_ID, RES_COLOR_INVALID_ID_VALUE);
    }
};

/*
 * @tc.name: setDisappearTextStyleTestFontStyle
 * @tc.desc: Check the functionality of DatePickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setDisappearTextStyleTestFontStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    Ark_Font font = {
        .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_THAT(checkSize, Eq(sizeStr));
        EXPECT_THAT(checkFamily, Eq(familyStr));
        EXPECT_THAT(checkStyle, Eq(style.second));
        EXPECT_THAT(checkWeight, Eq(weightStr));
    }
}

/*
 * @tc.name: setDisappearTextStyleTestFontWeight
 * @tc.desc: Check the functionality of DatePickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setDisappearTextStyleTestFontWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    Ark_Font font = {
        .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_THAT(checkSize, Eq(sizeStr));
        EXPECT_THAT(checkFamily, Eq(familyStr));
        EXPECT_THAT(checkStyle, Eq(styleStr));
        EXPECT_THAT(checkWeight, Eq(weight.second));
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_THAT(checkSize, Eq(sizeStr));
        EXPECT_THAT(checkFamily, Eq(familyStr));
        EXPECT_THAT(checkStyle, Eq(styleStr));
        EXPECT_THAT(checkWeight, Eq(weight.second));
    }
}

/*
 * @tc.name: setDisappearTextStyleTestFontFamily
 * @tc.desc: Check the functionality of DatePickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setDisappearTextStyleTestFontFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    Ark_Font font = {
        .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto family : FONT_FAMILY_TEST_PLAN) {
        font.family = family.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_THAT(checkSize, Eq(sizeStr));
        EXPECT_THAT(checkFamily, Eq(family.second));
        EXPECT_THAT(checkStyle, Eq(styleStr));
        EXPECT_THAT(checkWeight, Eq(weightStr));
    }
}

/*
 * @tc.name: setDisappearTextStyleTestFontSize
 * @tc.desc: Check the functionality of DatePickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setDisappearTextStyleTestFontSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    Ark_Font font = {
        .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_THAT(checkSize, Eq(size.second));
        EXPECT_THAT(checkFamily, Eq(familyStr));
        EXPECT_THAT(checkStyle, Eq(styleStr));
        EXPECT_THAT(checkWeight, Eq(weightStr));
    }
}

/*
 * @tc.name: setDisappearTextStyleTestColor
 * @tc.desc: Check the functionality of DatePickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setDisappearTextStyleTestColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
    auto checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_THAT(checkVal, Eq(ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE));
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        pickerStyle.color = value;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
        EXPECT_THAT(checkVal, Eq(expectVal));
    }
}

/*
 * @tc.name: textStyleTestDefaultValues
 * @tc.desc: Check the functionality of DatePickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_textStyleTestDefaultValues, TestSize.Level1)
{
        auto fullJson = GetJsonValue(node_);

        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);

        EXPECT_THAT(checkSize, Eq(ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE));
        EXPECT_THAT(checkWeight, Eq(ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE));
        EXPECT_THAT(checkStyle, Eq(ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE));
        EXPECT_THAT(checkFamily, Eq(ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE));
        EXPECT_THAT(checkColor, Eq(ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE));
}

/*
 * @tc.name: setTextStyleTestFontStyle
 * @tc.desc: Check the functionality of DatePickerModifier.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setTextStyleTestFontStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    Ark_Font font = {
        .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_THAT(checkSize, Eq(sizeStr));
        EXPECT_THAT(checkFamily, Eq(familyStr));
        EXPECT_THAT(checkStyle, Eq(style.second));
        EXPECT_THAT(checkWeight, Eq(weightStr));
    }
}

/*
 * @tc.name: setTextStyleTestFontWeight
 * @tc.desc: Check the functionality of DatePickerModifier.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setTextStyleTestFontWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    Ark_Font font = {
        .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_THAT(checkSize, Eq(sizeStr));
        EXPECT_THAT(checkFamily, Eq(familyStr));
        EXPECT_THAT(checkStyle, Eq(styleStr));
        EXPECT_THAT(checkWeight, Eq(weight.second));
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_THAT(checkSize, Eq(sizeStr));
        EXPECT_THAT(checkFamily, Eq(familyStr));
        EXPECT_THAT(checkStyle, Eq(styleStr));
        EXPECT_THAT(checkWeight, Eq(weight.second));
    }
}

/*
 * @tc.name: setTextStyleTestFontFamily
 * @tc.desc: Check the functionality of DatePickerModifier.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setTextStyleTestFontFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    Ark_Font font = {
        .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto family : FONT_FAMILY_TEST_PLAN) {
        font.family = family.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_THAT(checkSize, Eq(sizeStr));
        EXPECT_THAT(checkFamily, Eq(family.second));
        EXPECT_THAT(checkStyle, Eq(styleStr));
        EXPECT_THAT(checkWeight, Eq(weightStr));
    }
}

/*
 * @tc.name: setTextStyleTestFontSize
 * @tc.desc: Check the functionality of DatePickerModifier.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setTextStyleTestFontSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    Ark_Font font = {
        .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_THAT(checkSize, Eq(size.second));
        EXPECT_THAT(checkFamily, Eq(familyStr));
        EXPECT_THAT(checkStyle, Eq(styleStr));
        EXPECT_THAT(checkWeight, Eq(weightStr));
    }
}

/*
 * @tc.name: setTextStyleTestColor
 * @tc.desc: Check the functionality of DatePickerModifier.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setTextStyleTestColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
    auto checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_THAT(checkVal, Eq(ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE));
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        pickerStyle.color = value;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
        EXPECT_THAT(checkVal, Eq(expectVal));
    }
}

/*
 * @tc.name: selectedTextStyleTestDefaultValues
 * @tc.desc: Check the functionality of DatePickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_selectedTextStyleTestDefaultValues, TestSize.Level1)
{
        auto fullJson = GetJsonValue(node_);

        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);

        EXPECT_THAT(checkSize, Eq(ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE));
        EXPECT_THAT(checkWeight, Eq(ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE));
        EXPECT_THAT(checkStyle, Eq(ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE));
        EXPECT_THAT(checkFamily, Eq(ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE));
        EXPECT_THAT(checkColor, Eq(ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE));
}

/*
 * @tc.name: setSelectedTextStyleTestFontStyle
 * @tc.desc: Check the functionality of DatePickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setSelectedTextStyleTestFontStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    Ark_Font font = {
        .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_THAT(checkSize, Eq(sizeStr));
        EXPECT_THAT(checkFamily, Eq(familyStr));
        EXPECT_THAT(checkStyle, Eq(style.second));
        EXPECT_THAT(checkWeight, Eq(weightStr));
    }
}

/*
 * @tc.name: setSelectedTextStyleTestFontWeight
 * @tc.desc: Check the functionality of DatePickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setSelectedTextStyleTestFontWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    Ark_Font font = {
        .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_THAT(checkSize, Eq(sizeStr));
        EXPECT_THAT(checkFamily, Eq(familyStr));
        EXPECT_THAT(checkStyle, Eq(styleStr));
        EXPECT_THAT(checkWeight, Eq(weight.second));
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_THAT(checkSize, Eq(sizeStr));
        EXPECT_THAT(checkFamily, Eq(familyStr));
        EXPECT_THAT(checkStyle, Eq(styleStr));
        EXPECT_THAT(checkWeight, Eq(weight.second));
    }
}

/*
 * @tc.name: setSelectedTextStyleTestFontFamily
 * @tc.desc: Check the functionality of DatePickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setSelectedTextStyleTestFontFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    Ark_Font font = {
        .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto family : FONT_FAMILY_TEST_PLAN) {
        font.family = family.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_THAT(checkSize, Eq(sizeStr));
        EXPECT_THAT(checkFamily, Eq(family.second));
        EXPECT_THAT(checkStyle, Eq(styleStr));
        EXPECT_THAT(checkWeight, Eq(weightStr));
    }
}

/*
 * @tc.name: setSelectedTextStyleTestFontSize
 * @tc.desc: Check the functionality of DatePickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setSelectedTextStyleTestFontSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    Ark_Font font = {
        .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_THAT(checkSize, Eq(size.second));
        EXPECT_THAT(checkFamily, Eq(familyStr));
        EXPECT_THAT(checkStyle, Eq(styleStr));
        EXPECT_THAT(checkWeight, Eq(weightStr));
    }
}

/*
 * @tc.name: setSelectedTextStyleTestColor
 * @tc.desc: Check the functionality of DatePickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setSelectedTextStyleTestColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
    auto checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_THAT(checkVal, Eq(ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE));
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        pickerStyle.color = value;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
        EXPECT_THAT(checkVal, Eq(expectVal));
    }
}

/*
 * @tc.name: setDatePickerOptionsTestDefaultValues
 * @tc.desc: Check the functionality of DatePickerModifier.SetDatePickerOptionsImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDatePickerOptionsTestDefaultValues, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);

    auto constructor = GetAttrObject(fullJson, ATTRIBUTE_CONSTRUCTOR_NAME);
    auto checkStart = GetAttrValue<std::string>(constructor, ATTRIBUTE_DATE_START_NAME);
    auto checkEnd = GetAttrValue<std::string>(constructor, ATTRIBUTE_DATE_END_NAME);
    auto checkSelected = GetAttrValue<std::string>(constructor, ATTRIBUTE_DATE_SELECT_NAME);
    auto defaultStart = ToJsonString(ATTRIBUTE_DATE_START_DEFAULT_VALUE);
    auto defaultEnd = ToJsonString(ATTRIBUTE_DATE_END_DEFAULT_VALUE);
    auto defaultSelected = ToJsonString(ATTRIBUTE_DATE_SELECTED_DEFAULT_VALUE);

    EXPECT_THAT(checkStart, Eq(defaultStart));
    EXPECT_THAT(checkEnd, Eq(defaultEnd));
    EXPECT_THAT(checkSelected, Eq(defaultSelected));
}

/*
 * @tc.name: setDatePickerOptionsTest
 * @tc.desc: Check the functionality of DatePickerModifier.SetDatePickerOptionsImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDatePickerOptionsTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDatePickerOptions, nullptr);

    for (const auto& [actual, expected] : PICKER_DATE_OPTIONS_TEST_PLAN) {
        Ark_DatePickerOptions arkOptions = {
            .start = Converter::ArkValue<Opt_Date>(std::get<0>(actual)),
            .end = Converter::ArkValue<Opt_Date>(std::get<1>(actual)),
            .selected = Converter::ArkUnion<Opt_Union_Date_Bindable, Ark_Date>(std::get<2>(actual)),
        };
        auto optOptions = Converter::ArkValue<Opt_DatePickerOptions>(arkOptions);
        modifier_->setDatePickerOptions(node_, &optOptions);
        auto fullJson = GetJsonValue(node_);
        auto constructor = GetAttrObject(fullJson, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto checkStart = GetAttrValue<std::string>(constructor, ATTRIBUTE_DATE_START_NAME);
        auto checkEnd = GetAttrValue<std::string>(constructor, ATTRIBUTE_DATE_END_NAME);
        auto checkSelected = GetAttrValue<std::string>(constructor, ATTRIBUTE_DATE_SELECT_NAME);
        EXPECT_THAT(checkStart, Eq(std::get<0>(expected)));
        EXPECT_THAT(checkEnd, Eq(std::get<1>(expected)));
        EXPECT_THAT(checkSelected, Eq(std::get<2>(expected)));
    }
}

/*
 * @tc.name: setOnDateChangeTest
 * @tc.desc: Check the functionality of DatePickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setOnDateChangeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnDateChange, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<DatePickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static std::optional<PickerDate> selectedDate = std::nullopt;
    auto onDateChange = [](const Ark_Int32 resourceId, const Ark_Date parameter) {
        selectedDate = Converter::OptConvert<PickerDate>(parameter);
    };
    Callback_Date_Void func = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onDateChange
    };
    auto optFunc = Converter::ArkValue<Opt_Callback_Date_Void>(func);

    modifier_->setOnDateChange(node_, &optFunc);

    for (const auto& testValue : CHANGE_EVENT_TEST_PLAN) {
        DatePickerChangeEvent event(testValue.first.ToString(true));
        eventHub->FireChangeEvent(&event);

        EXPECT_TRUE(selectedDate.has_value());
        EXPECT_EQ(selectedDate->GetYear(), testValue.second.GetYear());
        EXPECT_EQ(selectedDate->GetMonth(), testValue.second.GetMonth());
        EXPECT_EQ(selectedDate->GetDay(), testValue.second.GetDay());
    };
}

/*
 * @tc.name: setLunarTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setLunarTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLunar, nullptr);
    auto initialValue = GetAttrValue<std::string>(node_, ATTRIBUTE_LUNAR_NAME);
    EXPECT_THAT(initialValue, Eq(ATTRIBUTE_LUNAR_DEFAULT_VALUE));

    for (auto& [actual, expected] : OPT_BOOL_TEST_PLAN) {
        modifier_->setLunar(node_, &actual);
        auto result = GetAttrValue<std::string>(node_, ATTRIBUTE_LUNAR_NAME);
        EXPECT_THAT(result, Eq(expected));
    }
}

/*
 * @tc.name: setDisappearTextStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setDisappearTextStyleTestDefaultValues, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);

    auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
    auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
    auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);

    EXPECT_THAT(checkSize, Eq(ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE));
    EXPECT_THAT(checkWeight, Eq(ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE));
    EXPECT_THAT(checkStyle, Eq(ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE));
    EXPECT_THAT(checkFamily, Eq(ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE));
    EXPECT_THAT(checkColor, Eq(ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE));
}

/*
 * @tc.name: setDisappearTextStyleTestInvalidValue
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setDisappearTextStyleTestInvalidValue, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);

    auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(Ark_Empty());
    modifier_->setDisappearTextStyle(node_, &optPickerStyle);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
    auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_THAT(checkSize, Eq(ATTRIBUTE_FONT_SIZE_DISAPPEAR_DEFAULT_VALUE));
    EXPECT_THAT(checkWeight, Eq(ATTRIBUTE_FONT_WEIGHT_DISAPPEAR_DEFAULT_VALUE));
    EXPECT_THAT(checkColor, Eq(ATTRIBUTE_TEXT_COLOR_DISAPPEAR_DEFAULT_VALUE));
}

/*
 * @tc.name: setTextStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setTextStyleTestDefaultValues, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);

    auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
    auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
    auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);

    EXPECT_THAT(checkSize, Eq(ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE));
    EXPECT_THAT(checkWeight, Eq(ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE));
    EXPECT_THAT(checkStyle, Eq(ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE));
    EXPECT_THAT(checkFamily, Eq(ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE));
    EXPECT_THAT(checkColor, Eq(ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE));
}

/*
 * @tc.name: setTextStyleTestInvalidValue
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setTextStyleTestInvalidValue, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);

    auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(Ark_Empty());
    modifier_->setTextStyle(node_, &optPickerStyle);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
    auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_THAT(checkSize, Eq(ATTRIBUTE_FONT_SIZE_NORMAL_DEFAULT_VALUE));
    EXPECT_THAT(checkWeight, Eq(ATTRIBUTE_FONT_WEIGHT_NORMAL_DEFAULT_VALUE));
    EXPECT_THAT(checkColor, Eq(ATTRIBUTE_TEXT_COLOR_NORMAL_DEFAULT_VALUE));
}

/*
 * @tc.name: setSelectedTextStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setSelectedTextStyleTestDefaultValues, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);

    auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
    auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
    auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);

    EXPECT_THAT(checkSize, Eq(ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE));
    EXPECT_THAT(checkWeight, Eq(ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE));
    EXPECT_THAT(checkStyle, Eq(ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE));
    EXPECT_THAT(checkFamily, Eq(ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE));
    EXPECT_THAT(checkColor, Eq(ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE));
}

/*
 * @tc.name: setSelectedTextStyleTestInvalidValue
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_setSelectedTextStyleTestInvalidValue, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);

    auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(Ark_Empty());
    modifier_->setSelectedTextStyle(node_, &optPickerStyle);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrObject(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
    auto fontObject = GetAttrObject(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_THAT(checkSize, Eq(ATTRIBUTE_FONT_SIZE_SELECTED_DEFAULT_VALUE));
    EXPECT_THAT(checkWeight, Eq(ATTRIBUTE_FONT_WEIGHT_SELECTED_DEFAULT_VALUE));
    EXPECT_THAT(checkColor, Eq(ATTRIBUTE_TEXT_COLOR_SELECTED_DEFAULT_VALUE));
}

#ifdef SUPPORT_DIGITAL_CROWN
/*
 * @tc.name: setDigitalCrownSensitivityTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDigitalCrownSensitivityTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_NAME);
    EXPECT_THAT(resultStr, Eq(ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE)) <<
        "Default value for attribute 'digitalCrownSensitivity'";
}

/*
 * @tc.name: setDigitalCrownSensitivityTestValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDigitalCrownSensitivityTestValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDigitalCrownSensitivity, nullptr);
    Opt_CrownSensitivity initValueDigitalCrownSensitivity;
    // Initial setup
    initValueDigitalCrownSensitivity = std::get<1>(testFixtureEnumCrownSensitivityTestPlan[0]);
    auto checkValue = [this, &initValueDigitalCrownSensitivity](
                          const std::string& input, const std::string& expectedStr, const Opt_CrownSensitivity& value) {
        Opt_CrownSensitivity inputValueDigitalCrownSensitivity = initValueDigitalCrownSensitivity;
        inputValueDigitalCrownSensitivity = value;
        modifier_->setDigitalCrownSensitivity(node_, &inputValueDigitalCrownSensitivity);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_NAME);
        EXPECT_THAT(resultStr, Eq(expectedStr)) << "Input value is: " << input <<
                                          ", method: setDigitalCrownSensitivity, attribute: digitalCrownSensitivity";
    };
    for (auto& [input, value, expected] : testFixtureEnumCrownSensitivityTestPlan) {
        checkValue(input, expected, value);
    }
}
#endif

/*
 * @tc.name: set_onChangeEvent_selectedTestOnChangeEventSelected
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, DISABLED_set_onChangeEvent_selectedTestOnChangeEventSelected, TestSize.Level1)
{
#ifdef WRONG_GEN
    ASSERT_NE(modifier_->set_onChangeEvent_selected, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<DatePickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static std::optional<PickerDate> selectedDate = std::nullopt;
    auto onDateChange = [](const Ark_Int32 resourceId, const Ark_Date parameter) {
        selectedDate = Converter::OptConvert<PickerDate>(parameter);
    };
    Callback_Date_Void func = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onDateChange
    };

    modifier_->set_onChangeEvent_selected(node_, &func);

    for (const auto& testValue : CHANGE_EVENT_TEST_PLAN) {
        DatePickerChangeEvent event(testValue.first.ToString(true));
        eventHub->FireChangeEvent(&event);

        ASSERT_TRUE(selectedDate.has_value());
        EXPECT_EQ(selectedDate->GetYear(), testValue.second.GetYear());
        EXPECT_EQ(selectedDate->GetMonth(), testValue.second.GetMonth());
        EXPECT_EQ(selectedDate->GetDay(), testValue.second.GetDay());
    };
#endif
}
} // namespace OHOS::Ace::NG
