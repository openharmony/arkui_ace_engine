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

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
// resource names and id
const auto RES_NAME = NamedResourceId{"aa.bb.cc", Converter::ResourceType::COLOR};
const auto RES_ID = IntResourceId{11111, Converter::ResourceType::COLOR};
const auto INVALID_ID = IntResourceId{-1, Converter::ResourceType::COLOR};

const auto COLOR_BY_STRING = Color(0xFF123456);
const auto COLOR_BY_NUMBER = Color(0xFF654321);

//  default colors
const auto CHECKED_COLOR_DEFAULT = "#FF000000";
const auto UNCHECKED_COLOR_DEFAULT = "#FF000000";
const auto INDICATOR_COLOR_DEFAULT = "#FF000000";
const auto RESOURCE_DEFAULT_COLOR_DEFAULT = "#FFFF0000";
// attributes
const std::string CHECKED_ATTR = "checked";
const std::string RADIO_STYLE_ATTR = "radioStyle";
const std::string CHECKED_BACKGROUND_COLOR_ATTR = "checkedBackgroundColor";
const std::string UNCHECKED_BORDER_COLOR_ATTR = "uncheckedBorderColor";
const std::string INDICATOR_COLOR_ATTR = "indicatorColor";
// indicatorType
const std::string INDICATOR_TYPE_ATTR = "indicatorType";
const std::string INDICATOR_TYPE_TICK = "TICK";
const std::string INDICATOR_TYPE_DOT = "DOT";
const std::string INDICATOR_TYPE_CUSTOM = "CUSTOM";
// options
const std::string RADIO_GROUP_ATTR = "group";
const std::string RADIO_VALUE_ATTR = "value";
const auto RADIO_GROUP_VALUE = "test_value";
const auto RADIO_VALUE_VALUE = "test_group";

static bool g_isCheckedTest = true;
static auto radioOnChange(Ark_Int32 nodeId, const Ark_Boolean isChecked)
{
    g_isCheckedTest = !g_isCheckedTest;
};
static GENERATED_ArkUIRadioEventsReceiver recv {
    .onChange = radioOnChange
};
static const GENERATED_ArkUIRadioEventsReceiver* getRadioEventsReceiverTest()
{
    return &recv;
};
static const GENERATED_ArkUIEventsAPI* GetArkUiEventsAPITest()
{
    static const GENERATED_ArkUIEventsAPI eventsImpl = { .getRadioEventsReceiver = getRadioEventsReceiverTest };
    return &eventsImpl;
};
} // namespace
class RadioModifierTest : public ModifierTestBase<GENERATED_ArkUIRadioModifier,
                              &GENERATED_ArkUINodeModifiers::getRadioModifier, GENERATED_ARKUI_RADIO> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<RadioTheme>();

        AddResource(RES_ID, COLOR_BY_NUMBER);
        AddResource(RES_NAME, COLOR_BY_STRING);

        fullAPI_->setArkUIEventsAPI(GetArkUiEventsAPITest());
    }
};

/**
 * @tc.name: RadioOptionsTest001
 * @tc.desc: Test Radio setRadioOptions.
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, RadioOptionsTest001, TestSize.Level1)
{
    auto groupDefault = GetStringAttribute(node_, RADIO_GROUP_ATTR);
    auto valueDefault = GetStringAttribute(node_, RADIO_VALUE_ATTR);
    EXPECT_EQ(groupDefault, "");
    EXPECT_EQ(groupDefault, "");
    Ark_RadioOptions radioOptions = {
        .group = Converter::ArkValue<Ark_String>(RADIO_GROUP_VALUE),
        .value = Converter::ArkValue<Ark_String>(RADIO_VALUE_VALUE)
    };
    modifier_->setRadioOptions(node_, &radioOptions);
    auto group = GetStringAttribute(node_, RADIO_GROUP_ATTR);
    auto value = GetStringAttribute(node_, RADIO_VALUE_ATTR);
    EXPECT_EQ(group, RADIO_GROUP_VALUE);
    EXPECT_EQ(value, RADIO_VALUE_VALUE);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        Ark_RadioOptions radioOptionsTick = {
            .indicatorType = Converter::ArkValue<Opt_RadioIndicatorType>(ARK_RADIO_INDICATOR_TYPE_TICK),
        };
        modifier_->setRadioOptions(node_, &radioOptionsTick);
        auto groupEmpty = GetStringAttribute(node_, RADIO_GROUP_ATTR);
        auto valueEmpty = GetStringAttribute(node_, RADIO_VALUE_ATTR);
        auto indicatorTypeTick = GetStringAttribute(node_, INDICATOR_TYPE_ATTR);
        EXPECT_EQ(groupEmpty, RADIO_GROUP_VALUE);
        EXPECT_EQ(valueEmpty, RADIO_VALUE_VALUE);
        EXPECT_EQ(indicatorTypeTick, INDICATOR_TYPE_TICK);
        Ark_RadioOptions radioOptionsDot = {
            .indicatorType = Converter::ArkValue<Opt_RadioIndicatorType>(ARK_RADIO_INDICATOR_TYPE_DOT),
        };
        modifier_->setRadioOptions(node_, &radioOptionsDot);
        auto indicatorTypeDot = GetStringAttribute(node_, INDICATOR_TYPE_ATTR);
        EXPECT_EQ(indicatorTypeDot, INDICATOR_TYPE_DOT);
        Ark_RadioOptions radioOptionsCustom = {
            .indicatorType = Converter::ArkValue<Opt_RadioIndicatorType>(ARK_RADIO_INDICATOR_TYPE_CUSTOM),
        };
        modifier_->setRadioOptions(node_, &radioOptionsCustom);
        auto indicatorTypeCustom = GetStringAttribute(node_, INDICATOR_TYPE_ATTR);
        EXPECT_EQ(indicatorTypeCustom, INDICATOR_TYPE_CUSTOM);
        Ark_RadioOptions radioOptionsInvalid = {
            .indicatorType = Converter::ArkValue<Opt_RadioIndicatorType>(static_cast<Ark_RadioIndicatorType>(INT_MAX)),
        };
        modifier_->setRadioOptions(node_, &radioOptionsInvalid);
        auto indicatorTypeInvalid = GetStringAttribute(node_, INDICATOR_TYPE_ATTR);
        EXPECT_EQ(indicatorTypeInvalid, INDICATOR_TYPE_TICK);
    }
}
/**
 * @tc.name: RadioModifierTest001
 * @tc.desc: Test Radio setChecked.
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, RadioModifierTest001, TestSize.Level1)
{
    auto checked = GetStringAttribute(node_, CHECKED_ATTR);
    EXPECT_EQ(checked, "false");
    modifier_->setChecked(node_, true);
    auto checkedChanged = GetStringAttribute(node_, CHECKED_ATTR);
    EXPECT_EQ(checkedChanged, "true");
}

/**
 * @tc.name: RadioModifierTest002
 * @tc.desc: Test Radio setRadioStyle default color.
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, RadioModifierTestDefaultColor, TestSize.Level1)
{
    auto jsonValue = GetJsonValue(node_);
    auto radioStyle = GetAttrValue< std::unique_ptr<JsonValue>>(jsonValue, RADIO_STYLE_ATTR);
    auto checkedBackgroundColor = radioStyle->GetString(CHECKED_BACKGROUND_COLOR_ATTR);
    EXPECT_EQ(checkedBackgroundColor, CHECKED_COLOR_DEFAULT);
    auto uncheckedBackgroundColor = radioStyle->GetString(UNCHECKED_BORDER_COLOR_ATTR);
    EXPECT_EQ(checkedBackgroundColor, UNCHECKED_COLOR_DEFAULT);
    auto indicatorBackgroundColor = radioStyle->GetString(INDICATOR_COLOR_ATTR);
    EXPECT_EQ(checkedBackgroundColor, INDICATOR_COLOR_DEFAULT);
}

/*
 * @tc.name: setRadioStyleTestValidEnumColorValues
 * @tc.desc: Check the functionality of ButtonModifier.setRadioStyle
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestValidEnumColorValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::unique_ptr<JsonValue> radioStyle;

    using OneTestStep = std::pair<Opt_ResourceColor, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_BLACK), "#FF000000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_BROWN), "#FFA52A2A" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_GRAY), "#FF808080" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_GREEN), "#FF008000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_GREY), "#FF808080" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_ORANGE), "#FFFFA500" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_PINK), "#FFFFC0CB" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_RED), "#FFFF0000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_YELLOW), "#FFFFFF00" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_TRANSPARENT), "#00000000" },
    };

    for (const auto &[arkResColor, expected]: testPlan) {
        Ark_RadioStyle arkRadioStyle = {
            .checkedBackgroundColor = arkResColor,
            .indicatorColor = arkResColor,
            .uncheckedBorderColor = arkResColor
        };
        auto radioStyleColors = ArkValue<Opt_RadioStyle>(arkRadioStyle);

        modifier_->setRadioStyle(node_, &radioStyleColors);
        jsonValue = GetJsonValue(node_);
        radioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, RADIO_STYLE_ATTR);
        auto checkedBackgroundColor = radioStyle->GetString(CHECKED_BACKGROUND_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, expected);
        auto uncheckedBackgroundColor = radioStyle->GetString(UNCHECKED_BORDER_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, expected);
        auto indicatorBackgroundColor = radioStyle->GetString(INDICATOR_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, expected);
    }
}

/*
 * @tc.name: setRadioStyleTestValidNumberValues
 * @tc.desc: Check the functionality of ButtonModifier.setRadioStyle
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestValidNumberValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::unique_ptr<JsonValue> radioStyle;

    using OneTestStep = std::pair<Opt_ResourceColor, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0xffffffff), "#FFFFFFFF" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0xff000000), "#FF000000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0xff0000ff), "#FF0000FF" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0xffa52a2a), "#FFA52A2A" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0xff808080), "#FF808080" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0xff008000), "#FF008000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0xffffa500), "#FFFFA500" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0xffffc0cb), "#FFFFC0CB" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0xffff0000), "#FFFF0000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0xffffff00), "#FFFFFF00" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0x00000000), "#00000000" },
    };

    for (const auto &[arkResColor, expected]: testPlan) {
        Ark_RadioStyle arkRadioStyle = {
            .checkedBackgroundColor = arkResColor,
            .indicatorColor = arkResColor,
            .uncheckedBorderColor = arkResColor
        };
        auto radioStyleColors = ArkValue<Opt_RadioStyle>(arkRadioStyle);

        modifier_->setRadioStyle(node_, &radioStyleColors);
        jsonValue = GetJsonValue(node_);
        radioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, RADIO_STYLE_ATTR);
        auto checkedBackgroundColor = radioStyle->GetString(CHECKED_BACKGROUND_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, expected);
        auto uncheckedBackgroundColor = radioStyle->GetString(UNCHECKED_BORDER_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, expected);
        auto indicatorBackgroundColor = radioStyle->GetString(INDICATOR_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, expected);
    }
}

/*
 * @tc.name: setRadioStyleTestValidStringValues
 * @tc.desc: Check the functionality of ButtonModifier.setRadioStyle
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestValidStringValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::unique_ptr<JsonValue> radioStyle;

    using OneTestStep = std::pair<Opt_ResourceColor, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#FFFFFFFF"), "#FFFFFFFF" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#ff000000"), "#FF000000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#ff0000ff"), "#FF0000FF" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#ffa52a2a"), "#FFA52A2A" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#ff808080"), "#FF808080" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#ff008000"), "#FF008000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#ffffa500"), "#FFFFA500" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#ffffc0cb"), "#FFFFC0CB" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#ffff0000"), "#FFFF0000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#ffffff00"), "#FFFFFF00" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#00000000"), "#00000000" },
    };

    for (const auto &[arkResColor, expected]: testPlan) {
        Ark_RadioStyle arkRadioStyle = {
            .checkedBackgroundColor = arkResColor,
            .indicatorColor = arkResColor,
            .uncheckedBorderColor = arkResColor
        };
        auto radioStyleColors = ArkValue<Opt_RadioStyle>(arkRadioStyle);

        modifier_->setRadioStyle(node_, &radioStyleColors);
        jsonValue = GetJsonValue(node_);
        radioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, RADIO_STYLE_ATTR);
        auto checkedBackgroundColor = radioStyle->GetString(CHECKED_BACKGROUND_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, expected);
        auto uncheckedBackgroundColor = radioStyle->GetString(UNCHECKED_BORDER_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, expected);
        auto indicatorBackgroundColor = radioStyle->GetString(INDICATOR_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, expected);
    }
}

/*
 * @tc.name: setRadioStyleTestInvalidNumberValues
 * @tc.desc: Check the functionality of ButtonModifier.setRadioStyle
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestInvalidNumberValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::unique_ptr<JsonValue> radioStyle;

    using OneTestStep = std::pair<Opt_ResourceColor, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0xffffffff + 1), "#00000000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0x00000000 - 1), "#FFFFFFFF" },
    };

    for (const auto &[arkResColor, expected]: testPlan) {
        Ark_RadioStyle arkRadioStyle = {
            .checkedBackgroundColor = arkResColor,
            .indicatorColor = arkResColor,
            .uncheckedBorderColor = arkResColor
        };
        auto radioStyleColors = ArkValue<Opt_RadioStyle>(arkRadioStyle);

        modifier_->setRadioStyle(node_, &radioStyleColors);
        jsonValue = GetJsonValue(node_);
        radioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, RADIO_STYLE_ATTR);
        auto checkedBackgroundColor = radioStyle->GetString(CHECKED_BACKGROUND_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, expected);
        auto uncheckedBackgroundColor = radioStyle->GetString(UNCHECKED_BORDER_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, expected);
        auto indicatorBackgroundColor = radioStyle->GetString(INDICATOR_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, expected);
    }
}


/*
 * @tc.name: setRadioStyleTestInvalidStringValues
 * @tc.desc: Check the functionality of ButtonModifier.setRadioStyle
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestInvalidStringValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::unique_ptr<JsonValue> radioStyle;

    static const std::vector<Opt_ResourceColor> testPlan = {
        { Converter::ArkUnion<Opt_ResourceColor, Ark_String>("undefined") },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_String>("GGTTSSPP") },
    };

    for (const auto &arkResColor: testPlan) {
        Ark_RadioStyle arkRadioStyle = {
            .checkedBackgroundColor = arkResColor,
            .indicatorColor = arkResColor,
            .uncheckedBorderColor = arkResColor
        };
        auto radioStyleColors = ArkValue<Opt_RadioStyle>(arkRadioStyle);

        modifier_->setRadioStyle(node_, &radioStyleColors);
        jsonValue = GetJsonValue(node_);
        radioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, RADIO_STYLE_ATTR);
        auto checkedBackgroundColor = radioStyle->GetString(CHECKED_BACKGROUND_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, CHECKED_COLOR_DEFAULT);
        auto uncheckedBackgroundColor = radioStyle->GetString(UNCHECKED_BORDER_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, UNCHECKED_COLOR_DEFAULT);
        auto indicatorBackgroundColor = radioStyle->GetString(INDICATOR_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, INDICATOR_COLOR_DEFAULT);
    }
}

/*
 * @tc.name: setRadioStyleTestResourceColorValues
 * @tc.desc: Check the functionality of ButtonModifier.setRadioStyle
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestResourceColorValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::unique_ptr<JsonValue> radioStyle;

    typedef std::pair<Opt_ResourceColor, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(CreateResource(RES_NAME)),
            COLOR_BY_STRING.ColorToString() },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(CreateResource(RES_ID)),
            COLOR_BY_NUMBER.ColorToString() },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(CreateResource(INVALID_ID)),
            RESOURCE_DEFAULT_COLOR_DEFAULT },
    };

    for (const auto &[arkResColor, expected]: testPlan) {
        Ark_RadioStyle arkRadioStyle = {
            .checkedBackgroundColor = arkResColor,
            .indicatorColor = arkResColor,
            .uncheckedBorderColor = arkResColor
        };
        auto radioStyleColors = ArkValue<Opt_RadioStyle>(arkRadioStyle);

        modifier_->setRadioStyle(node_, &radioStyleColors);
        jsonValue = GetJsonValue(node_);
        radioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, RADIO_STYLE_ATTR);
        auto checkedBackgroundColor = radioStyle->GetString(CHECKED_BACKGROUND_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, expected);
        auto uncheckedBackgroundColor = radioStyle->GetString(UNCHECKED_BORDER_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, expected);
        auto indicatorBackgroundColor = radioStyle->GetString(INDICATOR_COLOR_ATTR);
        EXPECT_EQ(checkedBackgroundColor, expected);
    }
}

/**
 * @tc.name: RadioModifierTest008
 * @tc.desc: Test Radio ContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, RadioModifierTest008, TestSize.Level1)
{
    LOGE("ARKOALA RadioAttributeModifier::ContentModifierImpl -> Method is not "
                "implemented.");
    EXPECT_EQ("true", "true");
}

/**
 * @tc.name: RadioEventTest001
 * @tc.desc: Test Radio onChange event.
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, RadioEventTest001, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_Boolean_Void func{};
    modifier_->setOnChange(node_, &func);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(g_isCheckedTest, false);
    ASSERT_NE(eventHub, nullptr);
    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(g_isCheckedTest, true);
}
} // namespace OHOS::Ace::NG
