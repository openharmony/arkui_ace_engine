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
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_event_hub.h"
#include "core/components/picker/picker_theme.h"
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
static const std::string EXPECTED_TRUE("true");
static const std::string EXPECTED_FALSE("false");
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
const auto RES_COLOR_ID = IntResourceId{102001, Converter::ResourceType::COLOR};
const auto RES_COLOR_ID_VALUE = Color(0xFF654321);
const auto RES_COLOR_NAME = NamedResourceId{"color_name", Converter::ResourceType::COLOR};
const auto RES_COLOR_NAME_VALUE = Color(0xFF123456);
const auto RES_COLOR_INVALID_ID = IntResourceId{-1, Converter::ResourceType::COLOR};
const auto RES_COLOR_INVALID_ID_VALUE = "#FFFF0000";


// font family res
const auto RES_FONT_FAMILY_NAME = NamedResourceId{"res_font_family_id", Converter::ResourceType::STRARRAY};
const auto RES_FONT_FAMILY_NAME_VALUE = "res_font_family_string_id";
const auto RES_FONT_FAMILY_ID = IntResourceId{102002, Converter::ResourceType::STRARRAY};
const auto RES_FONT_FAMILY_ID_VALUE = "res_font_family_number_id";
const auto RES_FONT_FAMILY_INVALID_ID = IntResourceId{-1, Converter::ResourceType::STRARRAY};
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
typedef std::pair<Opt_Union_FontWeight_Number_String, std::string> ArkFontWeightTest;
const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN = {
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_LIGHTER),
        "FontWeight.Lighter" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_NORMAL),
        "FontWeight.Normal" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_REGULAR),
        "FontWeight.Regular" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_MEDIUM),
        "FontWeight.Medium" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLD),
        "FontWeight.Bold" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLDER),
        "FontWeight.Bolder" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("lighter")),
        "FontWeight.Lighter" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("normal")),
        "FontWeight.Normal" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("regular")),
        "FontWeight.Regular" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("medium")),
        "FontWeight.Medium" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("bold")),
        "FontWeight.Bold" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("bolder")),
        "FontWeight.Bolder" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(static_cast<Ark_FontWeight>(-1)),
        ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(static_cast<Ark_FontWeight>(INT_MAX)),
        ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Empty>(nullptr),
        ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE },
};

const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN2 = {
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(100)),
        "100" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(200)),
        "200" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(300)),
        "300" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(400)),
        "400" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(500)),
        "500" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(600)),
        "600" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(700)),
        "700" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(800)),
        "800" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(900)),
        "900" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("100")),
        "100" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("200")),
        "200" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("300")),
        "300" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("400")),
        "400" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("500")),
        "500" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("600")),
        "600" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("700")),
        "700" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("800")),
        "800" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("900")),
        "900" }
};

// color
typedef std::tuple<Opt_ResourceColor, std::string> ColorTestStep;
const std::vector<ColorTestStep> COLOR_TEST_PLAN = {
    { Converter::ArkUnion<Opt_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0.5f), COLOR_TRANSPARENT },
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
 * @tc.name: setLunarTest
 * @tc.desc: Check the functionality of DatePickerModifier.LunarImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setLunarTest, TestSize.Level1)
{
    auto initialValue = GetAttrValue<std::string>(node_, ATTRIBUTE_LUNAR_NAME);
    EXPECT_EQ(initialValue, ATTRIBUTE_LUNAR_DEFAULT_VALUE);

    for (auto lunar : BOOL_TEST_PLAN) {
        auto inputValue = Converter::ArkValue<Opt_Boolean>(lunar.first);
        modifier_->setLunar0(node_, &inputValue);
        auto checkValue = GetAttrValue<std::string>(node_, ATTRIBUTE_LUNAR_NAME);
        EXPECT_EQ(checkValue, lunar.second);
    }
}

/*
 * @tc.name: disappearTextStyleTestDefaultValues
 * @tc.desc: Check the functionality of DatePickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, disappearTextStyleTestDefaultValues, TestSize.Level1)
{
        auto fullJson = GetJsonValue(node_);

        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);

        EXPECT_EQ(checkSize, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
        EXPECT_EQ(checkWeight, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE);
        EXPECT_EQ(checkStyle, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE);
        EXPECT_EQ(checkFamily, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE);
        EXPECT_EQ(checkColor, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setDisappearTexFontStyle
 * @tc.desc: Check the functionality of DatePickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDisappearTexFontStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle0, nullptr);
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
        modifier_->setDisappearTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setDisappearTexFontWeight
 * @tc.desc: Check the functionality of DatePickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDisappearTexFontWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle0, nullptr);
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
        modifier_->setDisappearTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/*
 * @tc.name: setDisappearTextFontFamily
 * @tc.desc: Check the functionality of DatePickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDisappearTextFontFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle0, nullptr);
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
        modifier_->setDisappearTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setDisappearTextFontSize
 * @tc.desc: Check the functionality of DatePickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDisappearTextFontSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle0, nullptr);
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
        modifier_->setDisappearTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setDisappearTextColor
 * @tc.desc: Check the functionality of DatePickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDisappearTextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle0, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
    auto checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        pickerStyle.color = value;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/*
 * @tc.name: textStyleTestDefaultValues
 * @tc.desc: Check the functionality of DatePickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, textStyleTestDefaultValues, TestSize.Level1)
{
        auto fullJson = GetJsonValue(node_);

        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);

        EXPECT_EQ(checkSize, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
        EXPECT_EQ(checkWeight, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE);
        EXPECT_EQ(checkStyle, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE);
        EXPECT_EQ(checkFamily, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE);
        EXPECT_EQ(checkColor, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setTexFontStyle
 * @tc.desc: Check the functionality of DatePickerModifier.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setTexFontStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle0, nullptr);
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
        modifier_->setTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setTexFontWeight
 * @tc.desc: Check the functionality of DatePickerModifier.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setTexFontWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle0, nullptr);
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
        modifier_->setTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/*
 * @tc.name: setTextFontFamily
 * @tc.desc: Check the functionality of DatePickerModifier.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setTextFontFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle0, nullptr);
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
        modifier_->setTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setTextFontSize
 * @tc.desc: Check the functionality of DatePickerModifier.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setTextFontSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle0, nullptr);
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
        modifier_->setTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setTextColor
 * @tc.desc: Check the functionality of DatePickerModifier.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setTextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle0, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
    auto checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        pickerStyle.color = value;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/*
 * @tc.name: selectedTextStyleTestDefaultValues
 * @tc.desc: Check the functionality of DatePickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, selectedTextStyleTestDefaultValues, TestSize.Level1)
{
        auto fullJson = GetJsonValue(node_);

        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);

        EXPECT_EQ(checkSize, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
        EXPECT_EQ(checkWeight, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE);
        EXPECT_EQ(checkStyle, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE);
        EXPECT_EQ(checkFamily, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE);
        EXPECT_EQ(checkColor, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setSelectedTexFontStyle
 * @tc.desc: Check the functionality of DatePickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setSelectedTexFontStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle0, nullptr);
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
        modifier_->setSelectedTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setSelectedTexFontWeight
 * @tc.desc: Check the functionality of DatePickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setSelectedTexFontWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle0, nullptr);
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
        modifier_->setSelectedTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/*
 * @tc.name: setSelectedTextFontFamily
 * @tc.desc: Check the functionality of DatePickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setSelectedTextFontFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle0, nullptr);
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
        modifier_->setSelectedTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setSelectedTextFontSize
 * @tc.desc: Check the functionality of DatePickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setSelectedTextFontSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle0, nullptr);
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
        modifier_->setSelectedTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setSelectedTextColor
 * @tc.desc: Check the functionality of DatePickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setSelectedTextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle0, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
    auto checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        pickerStyle.color = value;
        auto optValue = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle0(node_, &optValue);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/*
 * @tc.name: setOnChangeTest
 * @tc.desc: Check the functionality of DatePickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setOnChangeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnChange, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateEventHub<DatePickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t resourceId;
        PickerDate selectedDate;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onChange = [](Ark_Int32 nodeId, Ark_DatePickerResult arkResult) {
        PickerDate selectedDate;
        if (auto opt = Converter::OptConvert<int32_t>(arkResult.year); opt) {
            selectedDate.SetYear(*opt);
        }
        if (auto opt = Converter::OptConvert<int32_t>(arkResult.month); opt) {
            selectedDate.SetMonth(*opt);
        }
        if (auto opt = Converter::OptConvert<int32_t>(arkResult.day); opt) {
            selectedDate.SetDay(*opt);
        }
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(nodeId),
            .selectedDate = selectedDate,
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_DatePickerResult_Void>(onChange, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_Callback_DatePickerResult_Void>(arkCallback);
    modifier_->setOnChange(node_, &optCallback);

    for (const auto& testValue : CHANGE_EVENT_TEST_PLAN) {
        DatePickerChangeEvent event(testValue.first.ToString(true));

        eventHub->FireChangeEvent(&event);
        ASSERT_TRUE(checkEvent);
        EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
        EXPECT_EQ(checkEvent->selectedDate.GetYear(), testValue.second.GetYear());
        EXPECT_EQ(checkEvent->selectedDate.GetMonth(), testValue.second.GetMonth());
        EXPECT_EQ(checkEvent->selectedDate.GetDay(), testValue.second.GetDay());
    };
}

/*
 * @tc.name: setDatePickerOptionsDefaultValuesTest
 * @tc.desc: Check the functionality of DatePickerModifier.SetDatePickerOptionsImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDatePickerOptionsDefaultValuesTest, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);

    auto constructor = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_CONSTRUCTOR_NAME);
    auto checkStart = GetAttrValue<std::string>(constructor, ATTRIBUTE_DATE_START_NAME);
    auto checkEnd = GetAttrValue<std::string>(constructor, ATTRIBUTE_DATE_END_NAME);
    auto checkSelected = GetAttrValue<std::string>(constructor, ATTRIBUTE_DATE_SELECT_NAME);
    auto defaultStart = ToJsonString(ATTRIBUTE_DATE_START_DEFAULT_VALUE);
    auto defaultEnd = ToJsonString(ATTRIBUTE_DATE_END_DEFAULT_VALUE);
    auto defaultSelected = ToJsonString(ATTRIBUTE_DATE_SELECTED_DEFAULT_VALUE);

    EXPECT_EQ(checkStart, defaultStart);
    EXPECT_EQ(checkEnd, defaultEnd);
    EXPECT_EQ(checkSelected, defaultSelected);
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
            .selected = Converter::ArkValue<Opt_Date>(std::get<2>(actual)),
        };
        auto optOptions = Converter::ArkValue<Opt_DatePickerOptions>(arkOptions);
        modifier_->setDatePickerOptions(node_, &optOptions);
        auto fullJson = GetJsonValue(node_);
        auto constructor = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto checkStart = GetAttrValue<std::string>(constructor, ATTRIBUTE_DATE_START_NAME);
        auto checkEnd = GetAttrValue<std::string>(constructor, ATTRIBUTE_DATE_END_NAME);
        auto checkSelected = GetAttrValue<std::string>(constructor, ATTRIBUTE_DATE_SELECT_NAME);
        EXPECT_EQ(checkStart, std::get<0>(expected));
        EXPECT_EQ(checkEnd, std::get<1>(expected));
        EXPECT_EQ(checkSelected, std::get<2>(expected));
    }
}

/*
 * @tc.name: setOnDateChangeTest
 * @tc.desc: Check the functionality of DatePickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setOnDateChangeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnDateChange0, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateEventHub<DatePickerEventHub>();
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

    modifier_->setOnDateChange0(node_, &optFunc);

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
 * @tc.name: setLunar1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setLunar1Test, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLunar1, nullptr);
    auto initialValue = GetAttrValue<std::string>(node_, ATTRIBUTE_LUNAR_NAME);
    EXPECT_EQ(initialValue, ATTRIBUTE_LUNAR_DEFAULT_VALUE);

    for (auto& [actual, expected] : OPT_BOOL_TEST_PLAN) {
        modifier_->setLunar1(node_, &actual);
        auto result = GetAttrValue<std::string>(node_, ATTRIBUTE_LUNAR_NAME);
        EXPECT_EQ(result, expected);
    }
}

/*
 * @tc.name: setDisappearTextStyle1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDisappearTextStyle1TestDefaultValues, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);

    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
    auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
    auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);

    EXPECT_EQ(checkSize, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
    EXPECT_EQ(checkWeight, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE);
    EXPECT_EQ(checkStyle, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE);
    EXPECT_EQ(checkFamily, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE);
    EXPECT_EQ(checkColor, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setDisappearTextStyle1FontStyle
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDisappearTextStyle1FontStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle1, nullptr);
    Ark_Font font = { .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        pickerStyle.font.value = font;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setDisappearTextStyle1FontWeight
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDisappearTextStyle1FontWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle1, nullptr);
    Ark_Font font = { .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/*
 * @tc.name: setDisappearTextStyle1FontFamily
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDisappearTextStyle1FontFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle1, nullptr);
    Ark_Font font = { .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first };
    Ark_PickerTextStyle pickerStyle;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto family : FONT_FAMILY_TEST_PLAN) {
        font.family = family.first;
        pickerStyle.font.value = font;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setDisappearTextStyle1TextFontSize
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDisappearTextStyle1TextFontSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle1, nullptr);
    Ark_Font font = { .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        pickerStyle.font.value = font;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setDisappearTextColor
 * @tc.desc: Check the functionality of DatePickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDisappearTextStyle1TextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle1, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
    auto checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        pickerStyle.color = value;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/*
 * @tc.name: setDisappearTextStyle1InvalidValue
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDisappearTextStyle1InvalidValue, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle1, nullptr);

    auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(Ark_Empty());
    modifier_->setDisappearTextStyle1(node_, &optPickerStyle);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
    auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkSize, ATTRIBUTE_FONT_SIZE_DISAPPEAR_DEFAULT_VALUE);
    EXPECT_EQ(checkWeight, ATTRIBUTE_FONT_WEIGHT_DISAPPEAR_DEFAULT_VALUE);
    EXPECT_EQ(checkColor, ATTRIBUTE_TEXT_COLOR_DISAPPEAR_DEFAULT_VALUE);
}

/*
 * @tc.name: setTextStyle1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setTextStyle1TestDefaultValues, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);

    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
    auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
    auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);

    EXPECT_EQ(checkSize, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
    EXPECT_EQ(checkWeight, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE);
    EXPECT_EQ(checkStyle, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE);
    EXPECT_EQ(checkFamily, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE);
    EXPECT_EQ(checkColor, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setTextStyle1FontStyle
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setTextStyle1FontStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle1, nullptr);
    Ark_Font font = { .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        pickerStyle.font.value = font;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setTextStyle1FontWeight
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setTextStyle1FontWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle1, nullptr);
    Ark_Font font = { .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/*
 * @tc.name: setTextStyle1FontFamily
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setTextStyle1FontFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle1, nullptr);
    Ark_Font font = { .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first };
    Ark_PickerTextStyle pickerStyle;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto family : FONT_FAMILY_TEST_PLAN) {
        font.family = family.first;
        pickerStyle.font.value = font;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setTextStyle1FontSize
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setTextStyle1FontSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle1, nullptr);
    Ark_Font font = { .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        pickerStyle.font.value = font;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setTextStyle1TextColor
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setTextStyle1TextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle1, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
    auto checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        pickerStyle.color = value;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/*
 * @tc.name: setTextStyle1TextColor
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setTextStyle1InvalidValue, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle1, nullptr);

    auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(Ark_Empty());
    modifier_->setTextStyle1(node_, &optPickerStyle);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
    auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkSize, ATTRIBUTE_FONT_SIZE_NORMAL_DEFAULT_VALUE);
    EXPECT_EQ(checkWeight, ATTRIBUTE_FONT_WEIGHT_NORMAL_DEFAULT_VALUE);
    EXPECT_EQ(checkColor, ATTRIBUTE_TEXT_COLOR_NORMAL_DEFAULT_VALUE);
}

/*
 * @tc.name: setSelectedTextStyle1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setSelectedTextStyle1TestDefaultValues, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);

    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
    auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
    auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);

    EXPECT_EQ(checkSize, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
    EXPECT_EQ(checkWeight, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE);
    EXPECT_EQ(checkStyle, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE);
    EXPECT_EQ(checkFamily, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE);
    EXPECT_EQ(checkColor, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setSelectedTextStyle1FontStyle
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setSelectedTextStyle1FontStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle1, nullptr);
    Ark_Font font = { .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        pickerStyle.font.value = font;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setSelectedTextStyle1FontWeight
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setSelectedTextStyle1FontWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle1, nullptr);
    Ark_Font font = { .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/*
 * @tc.name: setSelectedTextStyle1FontFamily
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setSelectedTextStyle1FontFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle1, nullptr);
    Ark_Font font = { .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first };
    Ark_PickerTextStyle pickerStyle;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto family : FONT_FAMILY_TEST_PLAN) {
        font.family = family.first;
        pickerStyle.font.value = font;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setSelectedTextStyle1FontSize
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setSelectedTextStyle1FontSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle1, nullptr);
    Ark_Font font = { .family = FONT_FAMILY_TEST_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = FONT_FAMILY_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        pickerStyle.font.value = font;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/*
 * @tc.name: setSelectedTextStyle1TextColor
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setSelectedTextStyle1TextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle1, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
    auto checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        pickerStyle.color = value;
        auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle1(node_, &optPickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/*
 * @tc.name: setSelectedTextStyle1InvalidValue
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setSelectedTextStyle1InvalidValue, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle1, nullptr);

    auto optPickerStyle = Converter::ArkValue<Opt_PickerTextStyle>(Ark_Empty());
    modifier_->setSelectedTextStyle1(node_, &optPickerStyle);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
    auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkSize, ATTRIBUTE_FONT_SIZE_SELECTED_DEFAULT_VALUE);
    EXPECT_EQ(checkWeight, ATTRIBUTE_FONT_WEIGHT_SELECTED_DEFAULT_VALUE);
    EXPECT_EQ(checkColor, ATTRIBUTE_TEXT_COLOR_SELECTED_DEFAULT_VALUE);
}

/*
 * @tc.name: setOnDateChange1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setOnDateChange1Test, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnDateChange1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateEventHub<DatePickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static std::optional<PickerDate> selectedDate = std::nullopt;
    auto onDateChange = [](const Ark_Int32 resourceId, const Ark_Date parameter) {
        selectedDate = Converter::OptConvert<PickerDate>(parameter);
    };
    Callback_Date_Void func = { .resource =
                                    Ark_CallbackResource {
                                        .resourceId = frameNode->GetId(),
                                        .hold = nullptr,
                                        .release = nullptr,
                                    },
        .call = onDateChange };
    auto optFunc = Converter::ArkValue<Opt_Callback_Date_Void>(Ark_Empty());
    modifier_->setOnDateChange1(node_, &optFunc);
    for (const auto& testValue : CHANGE_EVENT_TEST_PLAN) {
        selectedDate.reset();
        DatePickerChangeEvent event(testValue.first.ToString(true));
        eventHub->FireChangeEvent(&event);
        EXPECT_FALSE(selectedDate.has_value());
    };
    optFunc = Converter::ArkValue<Opt_Callback_Date_Void>(func);
    modifier_->setOnDateChange1(node_, &optFunc);
    for (const auto& testValue : CHANGE_EVENT_TEST_PLAN) {
        selectedDate.reset();
        DatePickerChangeEvent event(testValue.first.ToString(true));
        eventHub->FireChangeEvent(&event);
        EXPECT_TRUE(selectedDate.has_value());
        EXPECT_EQ(selectedDate->GetYear(), testValue.second.GetYear());
        EXPECT_EQ(selectedDate->GetMonth(), testValue.second.GetMonth());
        EXPECT_EQ(selectedDate->GetDay(), testValue.second.GetDay());
    };
}

#ifdef SUPPORT_DIGITAL_CROWN
/*
 * @tc.name: setDigitalCrownSensitivityDefaultValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDigitalCrownSensitivityDefaultValuesTest, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE)
        << "Default value for attribute 'digitalCrownSensitivity'";
}

/*
 * @tc.name: setDigitalCrownSensitivityValidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setDigitalCrownSensitivityValuesTest, TestSize.Level1)
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
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input
                                          << ", method: setDigitalCrownSensitivity, attribute: digitalCrownSensitivity";
    };
    for (auto& [input, value, expected] : testFixtureEnumCrownSensitivityTestPlan) {
        checkValue(input, expected, value);
    }
}
#endif

/*
 * @tc.name: setOnChangeEventSelectedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerModifierTest, setOnChangeEventSelectedTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->set_onChangeEvent_selected, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateEventHub<DatePickerEventHub>();
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
}
} // namespace OHOS::Ace::NG
