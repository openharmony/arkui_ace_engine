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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_event_hub.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
// Prop names
const auto PROP_NAME_USE_MILITARY_TIME = "useMilitaryTime";
const auto PROP_NAME_LOOP = "loop";
const auto PROP_NAME_DISAPPEAR_TEXT_STYLE = "disappearTextStyle";
const auto PROP_NAME_TEXT_STYLE = "textStyle";
const auto PROP_NAME_SELECTED_TEXT_STYLE = "selectedTextStyle";
const auto PROP_NAME_DATETIMEOPTIONS = "dateTimeOptions";
const auto PROP_NAME_HOUR = "hour";
const auto PROP_NAME_MINUTE = "minute";
const auto PROP_NAME_FONT = "font";
const auto PROP_NAME_COLOR = "color";
const auto PROP_NAME_FONT_SIZE = "size";
const auto PROP_NAME_FONT_WEIGHT = "weight";
const auto PROP_NAME_FONT_STYLE = "style";
const auto PROP_NAME_FONT_FAMILY = "family";
const auto PROP_NAME_ENABLE_CASCADE = "enableCascade";
const auto PROP_NAME_DIGITAL_CROWN_SENSITIVITY = "digitalCrownSensitivity";

// Expected values
static const std::string EXPECTED_TRUE("true");
static const std::string EXPECTED_FALSE("false");
const std::string COLOR_BLACK = "#FF000000";
const std::string COLOR_TRANSPARENT = "#00000000";

const auto OPT_TRUE = Converter::ArkValue<Opt_Boolean>(true);
const auto OPT_FALSE = Converter::ArkValue<Opt_Boolean>(false);

// Default values
const auto ATTRIBUTE_USE_MILITARY_TIME_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_LOOP_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "14.00px";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = COLOR_BLACK;
const auto ATTRIBUTE_HAPTIC_FEEDBACK_DEFAULT_VALUE = true;
const auto ATTRIBUTE_ENABLE_CASCADE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE = "1";
const auto ATTRIBUTE_DATETIMEOPTIONS_HOUR_DEFAULT_VALUE = "numeric";
const auto ATTRIBUTE_DATETIMEOPTIONS_MINUTE_DEFAULT_VALUE = "2-digit";

// Test plans
const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);
const auto CHECK_AFLT32_POS = "1.23vp";

const auto RES_CONTENT_STR = "aa.bb.cc";
const auto RES_CONTENT = Converter::ArkValue<Ark_String>(RES_CONTENT_STR);
const auto RES_NAME = NamedResourceId{"res_name", ResourceType::STRING};
const Opt_Union_String_Resource OPT_UNION_RESOURCE_RESOURCE = CreateResourceUnion<Opt_Union_String_Resource>(RES_NAME);
const std::string CHECK_RESOURCE_STR(RES_CONTENT_STR);

typedef std::pair<Opt_Union_String_Resource, std::string> UnionStringResourceTestStep;
const std::vector<UnionStringResourceTestStep> UNION_RESOURCE_STRING_PLAN = {
    { Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(RES_CONTENT), CHECK_RESOURCE_STR },
    { OPT_UNION_RESOURCE_RESOURCE, CHECK_RESOURCE_STR }
};

typedef std::pair<Opt_Length, std::string> OptLengthTestStep;
const std::vector<OptLengthTestStep> FONT_SIZE_TEST_PLAN = {
    { Converter::ArkValue<Opt_Length>(AFLT32_POS), CHECK_AFLT32_POS },
    { Converter::ArkValue<Opt_Length>(AFLT32_NEG), ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE },
};

typedef std::pair<Opt_FontStyle, std::string> ArkFontStyleTestStep;
const std::vector<ArkFontStyleTestStep> FONT_STYLE_TEST_PLAN = {
    { Converter::ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_NORMAL), "FontStyle.Normal" },
    { Converter::ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_ITALIC), "FontStyle.Italic" },
    { Converter::ArkValue<Opt_FontStyle>(static_cast<Ark_FontStyle>(-1)), "FontStyle.Normal" },
};

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
        "FontWeight.Bolder" }
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

typedef std::tuple<Ark_ResourceColor, std::string> ColorTestStep;
const std::vector<ColorTestStep> COLOR_TEST_PLAN = {
    { Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE),
        "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0.5f), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("incorrect_color"), COLOR_BLACK },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""), COLOR_BLACK }
};

typedef std::pair<Opt_String, std::string> TimeDateTestStep;
const std::vector<TimeDateTestStep> DATETIMEOPTIONS_HOUR_TEST_PLAN = {
    { Converter::ArkValue<Opt_String>("numeric"), "numeric" },
    { Converter::ArkValue<Opt_String>("2-digit"), "2-digit" },
    { Converter::ArkValue<Opt_String>("digit"), "numeric" },
    { Converter::ArkValue<Opt_String>("text"), "numeric" },
    { Converter::ArkValue<Opt_String>(Ark_Empty()), "numeric" }
};
const std::vector<TimeDateTestStep> DATETIMEOPTIONS_MINUTE_TEST_PLAN = {
    { Converter::ArkValue<Opt_String>("numeric"), "numeric" },
    { Converter::ArkValue<Opt_String>("2-digit"), "2-digit" },
    { Converter::ArkValue<Opt_String>("digit"), "2-digit" },
    { Converter::ArkValue<Opt_String>("text"), "2-digit" },
    { Converter::ArkValue<Opt_String>(Ark_Empty()), "2-digit" }
};

const std::vector<PickerTime> CHANGE_EVENT_TEST_PLAN = {
    PickerTime(0, 1, 2),
    PickerTime(10, 20, 30),
    PickerTime(15, 59, 0),
    PickerTime(23, 0, 15)
};

typedef std::tuple<Opt_CrownSensitivity, std::string> CrouwnSensitivityTestStep;
const std::vector<CrouwnSensitivityTestStep> SENSITIVITY_TEST_PLAN = {
    {Converter::ArkValue<Opt_CrownSensitivity>(ARK_CROWN_SENSITIVITY_LOW), "0"},
    {Converter::ArkValue<Opt_CrownSensitivity>(ARK_CROWN_SENSITIVITY_MEDIUM), "1"},
    {Converter::ArkValue<Opt_CrownSensitivity>(ARK_CROWN_SENSITIVITY_HIGH), "2"},
};
} // namespace

class TimePickerModifierTest
    : public ModifierTestBase<GENERATED_ArkUITimePickerModifier,
          &GENERATED_ArkUINodeModifiers::getTimePickerModifier, GENERATED_ARKUI_TIME_PICKER> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<PickerTheme>();
    }
};

/**
 * @tc.name: setUseMilitaryTime
 * @tc.desc: Check the functionality of TimePickerModifierTest.UseMilitaryTimeImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, setUseMilitaryTime, TestSize.Level1)
{
    ASSERT_NE(modifier_->setUseMilitaryTime, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, PROP_NAME_USE_MILITARY_TIME);
    EXPECT_EQ(checkInitial, ATTRIBUTE_USE_MILITARY_TIME_DEFAULT_VALUE);

    modifier_->setUseMilitaryTime(node_, &OPT_TRUE);
    auto checkVal2 = GetAttrValue<std::string>(node_, PROP_NAME_USE_MILITARY_TIME);
    EXPECT_EQ(checkVal2, EXPECTED_TRUE);

    modifier_->setUseMilitaryTime(node_, &OPT_FALSE);
    auto checkVal3 = GetAttrValue<std::string>(node_, PROP_NAME_USE_MILITARY_TIME);
    EXPECT_EQ(checkVal3, EXPECTED_FALSE);
}

/**
 * @tc.name: setLoop
 * @tc.desc: Check the functionality of TimePickerModifierTest.LoopImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, setLoop, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLoop, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, PROP_NAME_LOOP);
    EXPECT_EQ(checkInitial, ATTRIBUTE_LOOP_DEFAULT_VALUE);

    modifier_->setLoop(node_, &OPT_TRUE);
    auto checkVal2 = GetAttrValue<std::string>(node_, PROP_NAME_LOOP);
    EXPECT_EQ(checkVal2, EXPECTED_TRUE);

    modifier_->setLoop(node_, &OPT_FALSE);
    auto checkVal3 = GetAttrValue<std::string>(node_, PROP_NAME_LOOP);
    EXPECT_EQ(checkVal3, EXPECTED_FALSE);
}

/**
 * @tc.name: setDisappearTextStyle
 * @tc.desc: Check the functionality of TimePickerModifierTest.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, DISABLED_setDisappearTextStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        pickerStyle.font.value = font;
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DISAPPEAR_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setDisappearTextWeight
 * @tc.desc: Check the functionality of TimePickerModifierTest.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, DISABLED_setDisappearTextWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DISAPPEAR_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DISAPPEAR_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: setDisappearTextFamily
 * @tc.desc: Check the functionality of TimePickerModifierTest.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, DISABLED_setDisappearTextFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
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

    for (auto family : UNION_RESOURCE_STRING_PLAN) {
        font.family = family.first;
        pickerStyle.font.value = font;
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DISAPPEAR_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setDisappearTextSize
 * @tc.desc: Check the functionality of TimePickerModifierTest.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, DISABLED_setDisappearTextSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        pickerStyle.font.value = font;
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DISAPPEAR_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setDisappearTextColor
 * @tc.desc: Check the functionality of TimePickerModifierTest.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, DISABLED_setDisappearTextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DISAPPEAR_TEXT_STYLE);
    auto checkVal = GetAttrValue<std::string>(styleObject, PROP_NAME_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        pickerStyle.color = { .value = value };
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DISAPPEAR_TEXT_STYLE);
        checkVal = GetAttrValue<std::string>(styleObject, PROP_NAME_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setTextStyle
 * @tc.desc: Check the functionality of TimePickerModifierTest.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, DISABLED_setTextStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        pickerStyle.font.value = font;
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setTextWeight
 * @tc.desc: Check the functionality of TimePickerModifierTest.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, DISABLED_setTextWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: setTextFamily
 * @tc.desc: Check the functionality of TimePickerModifierTest.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, DISABLED_setTextFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
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

    for (auto family : UNION_RESOURCE_STRING_PLAN) {
        font.family = family.first;
        pickerStyle.font.value = font;
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setTextSize
 * @tc.desc: Check the functionality of TimePickerModifierTest.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, DISABLED_setTextSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        pickerStyle.font.value = font;
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setTextColor
 * @tc.desc: Check the functionality of TimePickerModifierTest.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, DISABLED_setTextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_TEXT_STYLE);
    auto checkVal = GetAttrValue<std::string>(styleObject, PROP_NAME_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        pickerStyle.color = { .value = value };
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_TEXT_STYLE);
        checkVal = GetAttrValue<std::string>(styleObject, PROP_NAME_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setSelectedTextStyle
 * @tc.desc: Check the functionality of TimePickerModifierTest.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, DISABLED_setSelectedTextStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        pickerStyle.font.value = font;
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setSelectedTextWeight
 * @tc.desc: Check the functionality of TimePickerModifierTest.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, DISABLED_setSelectedTextWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: setSelectedTextFamily
 * @tc.desc: Check the functionality of TimePickerModifierTest.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, DISABLED_setSelectedTextFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
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

    for (auto family : UNION_RESOURCE_STRING_PLAN) {
        font.family = family.first;
        pickerStyle.font.value = font;
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setSelectedTextSize
 * @tc.desc: Check the functionality of TimePickerModifierTest.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, DISABLED_setSelectedTextSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        pickerStyle.font.value = font;
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setSelectedTextColor
 * @tc.desc: Check the functionality of TimePickerModifierTest.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, DISABLED_setSelectedTextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_TEXT_STYLE);
    auto checkVal = GetAttrValue<std::string>(styleObject, PROP_NAME_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        pickerStyle.color = { .value = value };
        auto optStyle =  Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &optStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_TEXT_STYLE);
        checkVal = GetAttrValue<std::string>(styleObject, PROP_NAME_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setDateTimeOptions
 * @tc.desc: Check the functionality of TimePickerModifierTest.DateTimeOptionsImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, setDateTimeOptions, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDateTimeOptions, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto optionsObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DATETIMEOPTIONS);
    auto hourStr = GetAttrValue<std::string>(optionsObject, PROP_NAME_HOUR);
    EXPECT_EQ(hourStr, ATTRIBUTE_DATETIMEOPTIONS_HOUR_DEFAULT_VALUE);
    auto minuteStr = GetAttrValue<std::string>(optionsObject, PROP_NAME_MINUTE);
    EXPECT_EQ(minuteStr, ATTRIBUTE_DATETIMEOPTIONS_MINUTE_DEFAULT_VALUE);

    for (const auto& [val, expectVal] : DATETIMEOPTIONS_HOUR_TEST_PLAN) {
        Ark_intl_DateTimeOptions dateTimeOptions {.hour = val };
        auto optOptions = Converter::ArkValue<Opt_intl_DateTimeOptions>(dateTimeOptions);
        modifier_->setDateTimeOptions(node_, &optOptions);
        auto fullJson = GetJsonValue(node_);
        optionsObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DATETIMEOPTIONS);
        hourStr = GetAttrValue<std::string>(optionsObject, PROP_NAME_HOUR);
        EXPECT_EQ(hourStr, expectVal);
    }

    for (const auto& [val, expectVal] : DATETIMEOPTIONS_MINUTE_TEST_PLAN) {
        Ark_intl_DateTimeOptions dateTimeOptions {.minute = val };
        auto optOptions = Converter::ArkValue<Opt_intl_DateTimeOptions>(dateTimeOptions);
        modifier_->setDateTimeOptions(node_, &optOptions);
        auto fullJson = GetJsonValue(node_);
        optionsObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DATETIMEOPTIONS);
        minuteStr = GetAttrValue<std::string>(optionsObject, PROP_NAME_MINUTE);
        EXPECT_EQ(minuteStr, expectVal);
    }
}

/**
 * @tc.name: setOnChange
 * @tc.desc: onChange event test
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, setOnChange, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnChange, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TimePickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t resourceId;
        PickerTime selectedTime;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onChange = [](const Ark_Int32 resourceId, const Ark_TimePickerResult value) {
        PickerTime selectedTime;
        selectedTime.SetHour(Converter::Convert<int32_t>(value.hour));
        selectedTime.SetMinute(Converter::Convert<int32_t>(value.minute));
        selectedTime.SetSecond(Converter::Convert<int32_t>(value.second));
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .selectedTime = selectedTime
        };
    };
    auto arkCallback = Converter::ArkValue<OnTimePickerChangeCallback>(onChange, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_OnTimePickerChangeCallback>(arkCallback);
    modifier_->setOnChange(node_, &optCallback);

    for (const auto time : CHANGE_EVENT_TEST_PLAN) {
        checkEvent = std::nullopt;
        EXPECT_FALSE(checkEvent);
        DatePickerChangeEvent event(time.ToString(true, true));
        eventHub->FireChangeEvent(&event);
        ASSERT_TRUE(checkEvent);
        EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
        EXPECT_EQ(checkEvent->selectedTime.GetHour(), time.GetHour());
        EXPECT_EQ(checkEvent->selectedTime.GetMinute(), time.GetMinute());
        EXPECT_EQ(checkEvent->selectedTime.GetSecond(), time.GetSecond());

        checkEvent = std::nullopt;
        EXPECT_FALSE(checkEvent);
        DatePickerChangeEvent eventWithoutSeconds(time.ToString(true, false));
        eventHub->FireChangeEvent(&eventWithoutSeconds);
        ASSERT_TRUE(checkEvent);
        EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
        EXPECT_EQ(checkEvent->selectedTime.GetHour(), time.GetHour());
        EXPECT_EQ(checkEvent->selectedTime.GetMinute(), time.GetMinute());
        EXPECT_EQ(checkEvent->selectedTime.GetSecond(), 0);
    };
}

/**
 * @tc.name: setEnableHapticFeedback
 * @tc.desc: Check the functionality of TimePickerModifierTest.EnableHapticFeedbackImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, setEnableHapticFeedback, TestSize.Level1)
{
    // static const std::string& DEFAULT_VALUE(ATTRIBUTE_HAPTIC_FEEDBACK_DEFAULT_VALUE);
    ASSERT_NE(modifier_->setEnableHapticFeedback, nullptr);
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto checkVal = static_cast<bool>(TimePickerModelNG::getEnableHapticFeedback(frameNode));
    EXPECT_EQ(checkVal, ATTRIBUTE_HAPTIC_FEEDBACK_DEFAULT_VALUE);

    modifier_->setEnableHapticFeedback(node_, &OPT_FALSE);
    checkVal = static_cast<bool>(TimePickerModelNG::getEnableHapticFeedback(frameNode));
    EXPECT_EQ(checkVal, false);

    modifier_->setEnableHapticFeedback(node_, &OPT_TRUE);
    checkVal = static_cast<bool>(TimePickerModelNG::getEnableHapticFeedback(frameNode));
    EXPECT_EQ(checkVal, true);
}

#ifdef WRONG_OLD_GEN
/*
 * @tc.name: setOnChangeEventSelectedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, setOnChangeEventSelectedTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->set_onChangeEvent_selected, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<TimePickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static std::optional<PickerTime> selectedTime = std::nullopt;
    auto onTimeChange = [](const Ark_Int32 resourceId, const Ark_Date parameter) {
        selectedTime = Converter::OptConvert<PickerTime>(parameter);
    };
    Callback_Date_Void func = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onTimeChange
    };

    modifier_->set_onChangeEvent_selected(node_, &func);

    for (const auto time : CHANGE_EVENT_TEST_PLAN) {
        DatePickerChangeEvent event(time.ToString(true, true));
        eventHub->FireChangeEvent(&event);
        ASSERT_EQ(selectedTime.has_value(), true);
        EXPECT_EQ(selectedTime->GetHour(), time.GetHour());
        EXPECT_EQ(selectedTime->GetMinute(), time.GetMinute());
        EXPECT_EQ(selectedTime->GetSecond(), time.GetSecond());

        DatePickerChangeEvent eventWithoutSeconds(time.ToString(true, false));
        eventHub->FireChangeEvent(&eventWithoutSeconds);
        ASSERT_EQ(selectedTime.has_value(), true);
        EXPECT_EQ(selectedTime->GetHour(), time.GetHour());
        EXPECT_EQ(selectedTime->GetMinute(), time.GetMinute());
        EXPECT_EQ(selectedTime->GetSecond(), 0);
    };
}
#endif

/**
 * @tc.name: enableCascadeTest
 * @tc.desc: Check the functionality of TimePickerModifierTest.LoopImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, enableCascadeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEnableCascade, nullptr);

    auto checkValue = GetAttrValue<std::string>(node_, PROP_NAME_ENABLE_CASCADE);
    EXPECT_EQ(checkValue, ATTRIBUTE_ENABLE_CASCADE_DEFAULT_VALUE);
    auto value = Converter::ArkValue<Ark_Boolean>(true);
    modifier_->setEnableCascade(node_, &OPT_TRUE);
    checkValue = GetAttrValue<std::string>(node_, PROP_NAME_ENABLE_CASCADE);
    EXPECT_EQ(checkValue, EXPECTED_TRUE);
    value = Converter::ArkValue<Ark_Boolean>(false);
    modifier_->setEnableCascade(node_, &OPT_FALSE);
    checkValue = GetAttrValue<std::string>(node_, PROP_NAME_ENABLE_CASCADE);
    EXPECT_EQ(checkValue, EXPECTED_FALSE);
}
/**
 * @tc.name: digitalCrownSensitivity
 * @tc.desc: Check the functionality of TimePickerModifierTest.digitalCrownSensitivity
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, digitalCrownSensitivity, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDigitalCrownSensitivity, nullptr);
    auto checkValue = GetAttrValue<std::string>(node_, PROP_NAME_DIGITAL_CROWN_SENSITIVITY);
    EXPECT_EQ(checkValue, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE);
        for (const auto& [value, expectVal] : SENSITIVITY_TEST_PLAN) {
        modifier_->setDigitalCrownSensitivity(node_, &value);
        auto checkValue = GetAttrValue<std::string>(node_, PROP_NAME_DIGITAL_CROWN_SENSITIVITY);
        EXPECT_EQ(checkValue, expectVal);
    }
}

/**
 * @tc.name: setOnEnterSelectedArea
 * @tc.desc: onEnterSelectedArea event test
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, setOnEnterSelectedArea, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnEnterSelectedArea, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TimePickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t resourceId;
        PickerTime selectedTime;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onChange = [](const Ark_Int32 resourceId, const Ark_TimePickerResult value) {
        PickerTime selectedTime;
        selectedTime.SetHour(Converter::Convert<int32_t>(value.hour));
        selectedTime.SetMinute(Converter::Convert<int32_t>(value.minute));
        selectedTime.SetSecond(Converter::Convert<int32_t>(value.second));
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .selectedTime = selectedTime
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_TimePickerResult_Void>(onChange, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_Callback_TimePickerResult_Void>(arkCallback);
    modifier_->setOnEnterSelectedArea(node_, &optCallback);

    for (const auto time : CHANGE_EVENT_TEST_PLAN) {
        checkEvent = std::nullopt;
        EXPECT_FALSE(checkEvent);
        DatePickerChangeEvent event(time.ToString(true, true));
        eventHub->FireEnterSelectedAreaEvent(&event);
        ASSERT_TRUE(checkEvent);
        EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
        EXPECT_EQ(checkEvent->selectedTime.GetHour(), time.GetHour());
        EXPECT_EQ(checkEvent->selectedTime.GetMinute(), time.GetMinute());
        EXPECT_EQ(checkEvent->selectedTime.GetSecond(), time.GetSecond());

        checkEvent = std::nullopt;
        EXPECT_FALSE(checkEvent);
        DatePickerChangeEvent eventWithoutSeconds(time.ToString(true, false));
        eventHub->FireEnterSelectedAreaEvent(&eventWithoutSeconds);
        ASSERT_TRUE(checkEvent);
        EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
        EXPECT_EQ(checkEvent->selectedTime.GetHour(), time.GetHour());
        EXPECT_EQ(checkEvent->selectedTime.GetMinute(), time.GetMinute());
        EXPECT_EQ(checkEvent->selectedTime.GetSecond(), 0);
    };
}
} // namespace OHOS::Ace::NG
