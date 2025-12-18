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

#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
// resource names and id
const auto RES_NAME = NamedResourceId{"aa.bb.cc", ResourceType::COLOR};
const auto RES_ID = IntResourceId{11111, ResourceType::COLOR};
const auto INVALID_ID = IntResourceId{-1, ResourceType::COLOR};

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
static constexpr int TEST_RESOURCE_ID = 1000;
static constexpr int32_t NODE_ID = 555;
struct CheckEvent {
    int32_t resourceId;
    Ark_NativePointer parentNode;
};
static std::optional<CheckEvent> checkEvent = std::nullopt;
static std::optional<RefPtr<UINode>> uiNode = std::nullopt;
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
    }

    CustomNodeBuilder getBuilderCb()
    {
        auto checkCallback = [](
            const Ark_Int32 resourceId,
            const Ark_NativePointer parentNode,
            const Callback_Pointer_Void continuation) {
            checkEvent = {
                .resourceId = resourceId,
                .parentNode = parentNode
            };
            if (uiNode) {
                CallbackHelper(continuation).InvokeSync(AceType::RawPtr(uiNode.value()));
            }
        };
        CustomNodeBuilder customBuilder =
            Converter::ArkValue<CustomNodeBuilder>(checkCallback, TEST_RESOURCE_ID);
        return customBuilder;
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

/*
 * @tc.name: RadioOptionsCustomBuilderTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, RadioOptionsCustomBuilderTest, TestSize.Level1)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        Ark_RadioOptions radioOptions = {
            .group = Converter::ArkValue<Ark_String>(RADIO_GROUP_VALUE),
            .value = Converter::ArkValue<Ark_String>(RADIO_VALUE_VALUE),
            .indicatorType = Converter::ArkValue<Opt_RadioIndicatorType>(ARK_RADIO_INDICATOR_TYPE_CUSTOM),
        };
        uiNode = BlankModelNG::CreateFrameNode(NODE_ID);
        auto builder = getBuilderCb();
        radioOptions.indicatorBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
        checkEvent = std::nullopt;
        modifier_->setRadioOptions(node_, &radioOptions);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        auto pattern = frameNode->GetPattern<RadioPattern>();
        ASSERT_NE(pattern, nullptr);
        pattern->SetRadioChecked(true);
        ASSERT_EQ(checkEvent.has_value(), true);
        EXPECT_EQ(checkEvent->resourceId, TEST_RESOURCE_ID);
        uiNode = std::nullopt;
        checkEvent = std::nullopt;
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
    auto optValue = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(true);
    modifier_->setChecked(node_, &optValue);
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
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            ARK_ARKUI_COMPONENT_ENUMS_COLOR_WHITE), "#FFFFFFFF" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLACK), "#FF000000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE), "#FF0000FF" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            ARK_ARKUI_COMPONENT_ENUMS_COLOR_BROWN), "#FFA52A2A" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            ARK_ARKUI_COMPONENT_ENUMS_COLOR_GRAY), "#FF808080" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            ARK_ARKUI_COMPONENT_ENUMS_COLOR_GREEN), "#FF008000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            ARK_ARKUI_COMPONENT_ENUMS_COLOR_GREY), "#FF808080" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            ARK_ARKUI_COMPONENT_ENUMS_COLOR_ORANGE), "#FFFFA500" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            ARK_ARKUI_COMPONENT_ENUMS_COLOR_PINK), "#FFFFC0CB" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            ARK_ARKUI_COMPONENT_ENUMS_COLOR_RED), "#FFFF0000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            ARK_ARKUI_COMPONENT_ENUMS_COLOR_YELLOW), "#FFFFFF00" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            ARK_ARKUI_COMPONENT_ENUMS_COLOR_TRANSPARENT), "#00000000" },
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
HWTEST_F(RadioModifierTest, DISABLED_setRadioStyleTestValidNumberValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::unique_ptr<JsonValue> radioStyle;

    using OneTestStep = std::pair<Opt_ResourceColor, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0xffffffff), "#FFFFFFFF" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0xff000000), "#FF000000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0xff0000ff), "#FF0000FF" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0xffa52a2a), "#FFA52A2A" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0xff808080), "#FF808080" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0xff008000), "#FF008000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0xffffa500), "#FFFFA500" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0xffffc0cb), "#FFFFC0CB" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0xffff0000), "#FFFF0000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0xffffff00), "#FFFFFF00" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0x00000000), "#00000000" },
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
HWTEST_F(RadioModifierTest, DISABLED_setRadioStyleTestInvalidNumberValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::unique_ptr<JsonValue> radioStyle;

    using OneTestStep = std::pair<Opt_ResourceColor, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0xffffffff + 1), "#00000000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0x00000000 - 1), "#FFFFFFFF" },
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
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    struct CheckEvent {
        int32_t nodeId;
        bool value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    OnRadioChangeCallback arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_Boolean value) {
            checkEvent = {
                .nodeId = nodeId,
                .value = Converter::Convert<bool>(value)
            };
        }
    };
    auto optCallback = Converter::ArkValue<Opt_OnRadioChangeCallback>(arkCallback);
    modifier_->setOnChange(node_, &optCallback);
    eventHub->UpdateChangeEvent(true);
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_TRUE(checkEvent->value);
}

#ifdef WRONG_OLD_GEN
/*
 * @tc.name: setOnChangeEventCheckedImpl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setOnChangeEventCheckedImpl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        std::optional<bool> value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Opt_Boolean parameter) {
        checkEvent = {
            .nodeId = resourceId,
            .value = Converter::OptConvert<bool>(parameter)
        };
    };

    auto arkCallback = Converter::ArkValue<Callback_Opt_Boolean_Void>(checkCallback, contextId);

    modifier_->set_onChangeEvent_checked(node_, &arkCallback);

    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->UpdateChangeEvent(true);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, true);
    eventHub->UpdateChangeEvent(false);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, false);
}
#endif
} // namespace OHOS::Ace::NG
