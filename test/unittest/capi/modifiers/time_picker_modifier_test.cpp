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
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
struct EventsTracker {
    static inline GENERATED_ArkUITimePickerEventsReceiver timePickerEventReceiver {};

    static inline const GENERATED_ArkUIEventsAPI eventsApiImpl {
        .getTimePickerEventsReceiver = []() -> const GENERATED_ArkUITimePickerEventsReceiver* {
            return &timePickerEventReceiver;
        }
    };
}; // EventsTracker

// Prop names
const auto PROP_NAME_USE_MILITARY_TIME = "useMilitaryTime";
const auto PROP_NAME_LOOP = "loop";
const auto PROP_NAME_DISAPPEAR_TEXT_STYLE = "disappearTextStyle";
const auto PROP_NAME_TEXT_STYLE = "textStyle";
const auto PROP_NAME_SELECTED_TEXT_STYLE = "selectedTextStyle";
const auto PROP_NAME_FONT = "font";
const auto PROP_NAME_COLOR = "color";
const auto PROP_NAME_FONT_SIZE = "size";
const auto PROP_NAME_FONT_WEIGHT = "weight";
const auto PROP_NAME_FONT_STYLE = "style";
const auto PROP_NAME_FONT_FAMILY = "family";

// Expected values
static const std::string EXPECTED_TRUE("true");
static const std::string EXPECTED_FALSE("false");
const std::string COLOR_BLACK = "#FF000000";
const std::string COLOR_TRANSPARENT = "#00000000";

// Default values
const auto ATTRIBUTE_USE_MILITARY_TIME_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_LOOP_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "14.00px";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = COLOR_BLACK;
const auto ATTRIBUTE_HAPTIC_FEEDBACK_DEFAULT_VALUE = true;

// Test plans
const Ark_Int32 AINT32_POS(70);
const Ark_Int32 AINT32_NEG(INT_MIN);
const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);
const auto CHECK_AINT32_POS = "70.00px";
const auto CHECK_AFLT32_POS = "1.23vp";

const auto RES_CONTENT_STR = "aa.bb.cc";
const auto RES_CONTENT = Converter::ArkValue<Ark_String>(RES_CONTENT_STR);
const auto RES_NAME = NamedResourceId{"res_name", NodeModifier::ResourceType::STRING};
const Opt_Union_String_Resource OPT_UNION_RESOURCE_RESOURCE = CreateResourceUnion<Opt_Union_String_Resource>(RES_NAME);
const std::string CHECK_RESOURCE_STR(RES_CONTENT_STR);

typedef std::pair<Opt_Union_String_Resource, std::string> UnionStringResourceTestStep;
const std::vector<UnionStringResourceTestStep> UNION_RESOURCE_STRING_PLAN = {
    { Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(RES_CONTENT), CHECK_RESOURCE_STR },
    { OPT_UNION_RESOURCE_RESOURCE, CHECK_RESOURCE_STR }
};

typedef std::pair<Opt_Length, std::string> OptLengthTestStep;
const std::vector<OptLengthTestStep> FONT_SIZE_TEST_PLAN = {
    { Converter::ArkValue<Opt_Length>(AINT32_POS), CHECK_AINT32_POS },
    { Converter::ArkValue<Opt_Length>(AINT32_NEG), ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Length>(AFLT32_NEG), ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Length>(AFLT32_POS), CHECK_AFLT32_POS }
};

typedef std::pair<Opt_FontStyle, std::string> ArkFontStyleTestStep;
const std::vector<ArkFontStyleTestStep> FONT_STYLE_TEST_PLAN = {
    { { .tag = ARK_TAG_OBJECT, .value = ARK_FONT_STYLE_NORMAL }, "FontStyle.Normal" },
    { { .tag = ARK_TAG_OBJECT, .value = ARK_FONT_STYLE_ITALIC }, "FontStyle.Italic" },
    { { .tag = ARK_TAG_OBJECT, .value = static_cast<Ark_FontStyle>(2) }, "FontStyle.Normal" },
};

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
        "FontWeight.Bolder" }
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

typedef std::tuple<Ark_ResourceColor, std::string> ColorTestStep;
const std::vector<ColorTestStep> COLOR_TEST_PLAN = {
    { Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("incorrect_color"), COLOR_BLACK },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""), COLOR_BLACK }
};

const std::vector<PickerTime> CHANGE_EVENT_TEST_PLAN = {
    PickerTime(0, 1, 2),
    PickerTime(10, 20, 30),
    PickerTime(15, 59, 0),
    PickerTime(23, 0, 15)
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

        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
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

    modifier_->setUseMilitaryTime(node_, true);
    auto checkVal2 = GetAttrValue<std::string>(node_, PROP_NAME_USE_MILITARY_TIME);
    EXPECT_EQ(checkVal2, EXPECTED_TRUE);

    modifier_->setUseMilitaryTime(node_, false);
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

    modifier_->setLoop(node_, true);
    auto checkVal2 = GetAttrValue<std::string>(node_, PROP_NAME_LOOP);
    EXPECT_EQ(checkVal2, EXPECTED_TRUE);

    modifier_->setLoop(node_, false);
    auto checkVal3 = GetAttrValue<std::string>(node_, PROP_NAME_LOOP);
    EXPECT_EQ(checkVal3, EXPECTED_FALSE);
}

/**
 * @tc.name: setDisappearTextStyle
 * @tc.desc: Check the functionality of TimePickerModifierTest.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerModifierTest, setDisappearTextStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    Ark_Font font = {
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
        modifier_->setDisappearTextStyle(node_, &pickerStyle);
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
HWTEST_F(TimePickerModifierTest, setDisappearTextWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    Ark_Font font = {
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
        modifier_->setDisappearTextStyle(node_, &pickerStyle);
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
        modifier_->setDisappearTextStyle(node_, &pickerStyle);
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
    Ark_Font font = {
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
        modifier_->setDisappearTextStyle(node_, &pickerStyle);
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
HWTEST_F(TimePickerModifierTest, setDisappearTextSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    Ark_Font font = {
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
        modifier_->setDisappearTextStyle(node_, &pickerStyle);
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
HWTEST_F(TimePickerModifierTest, setDisappearTextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DISAPPEAR_TEXT_STYLE);
    auto checkVal = GetAttrValue<std::string>(styleObject, PROP_NAME_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        pickerStyle.color = { .value = value };
        modifier_->setDisappearTextStyle(node_, &pickerStyle);
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
HWTEST_F(TimePickerModifierTest, setTextStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    Ark_Font font = {
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
        modifier_->setTextStyle(node_, &pickerStyle);
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
HWTEST_F(TimePickerModifierTest, setTextWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    Ark_Font font = {
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
        modifier_->setTextStyle(node_, &pickerStyle);
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
        modifier_->setTextStyle(node_, &pickerStyle);
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
    Ark_Font font = {
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
        modifier_->setTextStyle(node_, &pickerStyle);
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
HWTEST_F(TimePickerModifierTest, setTextSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    Ark_Font font = {
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
        modifier_->setTextStyle(node_, &pickerStyle);
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
HWTEST_F(TimePickerModifierTest, setTextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_TEXT_STYLE);
    auto checkVal = GetAttrValue<std::string>(styleObject, PROP_NAME_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        pickerStyle.color = { .value = value };
        modifier_->setTextStyle(node_, &pickerStyle);
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
HWTEST_F(TimePickerModifierTest, setSelectedTextStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    Ark_Font font = {
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
        modifier_->setSelectedTextStyle(node_, &pickerStyle);
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
HWTEST_F(TimePickerModifierTest, setSelectedTextWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    Ark_Font font = {
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
        modifier_->setSelectedTextStyle(node_, &pickerStyle);
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
        modifier_->setSelectedTextStyle(node_, &pickerStyle);
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
    Ark_Font font = {
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
        modifier_->setSelectedTextStyle(node_, &pickerStyle);
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
HWTEST_F(TimePickerModifierTest, setSelectedTextSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    Ark_Font font = {
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
        modifier_->setSelectedTextStyle(node_, &pickerStyle);
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
HWTEST_F(TimePickerModifierTest, setSelectedTextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_TEXT_STYLE);
    auto checkVal = GetAttrValue<std::string>(styleObject, PROP_NAME_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        pickerStyle.color = { .value = value };
        modifier_->setSelectedTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_TEXT_STYLE);
        checkVal = GetAttrValue<std::string>(styleObject, PROP_NAME_COLOR);
        EXPECT_EQ(checkVal, expectVal);
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
    Callback_TimePickerResult_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TimePickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static PickerTime selectedTime;
    EventsTracker::timePickerEventReceiver.onChange = [](Ark_Int32 nodeId, Ark_TimePickerResult arkResult) {
        selectedTime.SetHour(Converter::Convert<int32_t>(arkResult.hour));
        selectedTime.SetMinute(Converter::Convert<int32_t>(arkResult.minute));
        selectedTime.SetSecond(Converter::Convert<int32_t>(arkResult.second));
    };
    modifier_->setOnChange(node_, &func);

    for (const auto time : CHANGE_EVENT_TEST_PLAN) {
        DatePickerChangeEvent event(time.ToString(true, true));
        eventHub->FireChangeEvent(&event);
        EXPECT_EQ(selectedTime.GetHour(), time.GetHour());
        EXPECT_EQ(selectedTime.GetMinute(), time.GetMinute());
        EXPECT_EQ(selectedTime.GetSecond(), time.GetSecond());

        DatePickerChangeEvent eventWithoutSeconds(time.ToString(true, false));
        eventHub->FireChangeEvent(&eventWithoutSeconds);
        EXPECT_EQ(selectedTime.GetHour(), time.GetHour());
        EXPECT_EQ(selectedTime.GetMinute(), time.GetMinute());
        EXPECT_EQ(selectedTime.GetSecond(), 0);
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

    modifier_->setEnableHapticFeedback(node_, false);
    checkVal = static_cast<bool>(TimePickerModelNG::getEnableHapticFeedback(frameNode));
    EXPECT_EQ(checkVal, false);

    modifier_->setEnableHapticFeedback(node_, true);
    checkVal = static_cast<bool>(TimePickerModelNG::getEnableHapticFeedback(frameNode));
    EXPECT_EQ(checkVal, true);
}
} // namespace OHOS::Ace::NG
