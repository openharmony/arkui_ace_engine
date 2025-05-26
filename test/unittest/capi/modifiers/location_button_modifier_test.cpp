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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/components_ng/pattern/security_component/location_button/location_button_common.h"
#include "core/components_ng/pattern/security_component/location_button/location_button_model_ng.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace GeneratedModifier {
    const GENERATED_ArkUIClickEventAccessor* GetClickEventAccessor();
}

namespace  {
    const auto ATTRIBUTE_ICON_NAME = "icon";
    const auto ATTRIBUTE_ICON_DEFAULT_VALUE = LocationButtonIconStyle::ICON_NULL;
    const auto ATTRIBUTE_TEXT_NAME = "text";
    const auto ATTRIBUTE_TEXT_DEFAULT_VALUE = LocationButtonLocationDescription::TEXT_NULL;
    const auto ATTRIBUTE_BUTTON_TYPE_NAME = "buttonType";
    const auto ATTRIBUTE_BUTTON_TYPE_DEFAULT_VALUE = ButtonType::CAPSULE;

    const auto DEFAULT_JSON_INT = -1;
    constexpr double OFFSET_X = 60.4;
    constexpr double OFFSET_Y = 85.5;

    static std::shared_ptr<JsonValue> CreateJson(SecurityComponentHandleResult value)
    {
        int32_t res = static_cast<int32_t>(value);
        auto jsonNode = JsonUtil::Create(true);
        jsonNode->Put("handleRes", res);
        std::shared_ptr<JsonValue> jsonShrd(jsonNode.release());
        return jsonShrd;
    };
} // namespace

class LocationButtonModifierTest : public ModifierTestBase<GENERATED_ArkUILocationButtonModifier,
    &GENERATED_ArkUINodeModifiers::getLocationButtonModifier, GENERATED_ARKUI_LOCATION_BUTTON> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<SecurityComponentTheme>();
    }
};

/*
 * @tc.name: setLocationButtonOptions0
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LocationButtonModifierTest, setLocationButtonOptions0, TestSize.Level1)
{
    auto node = CreateNode();
    modifier_->setLocationButtonOptions0(node);
    auto jsonValue = GetJsonValue(node);
    DisposeNode(node);
    int32_t resultText = jsonValue->GetInt(ATTRIBUTE_TEXT_NAME, DEFAULT_JSON_INT);
    int32_t resultIcon = jsonValue->GetInt(ATTRIBUTE_ICON_NAME, DEFAULT_JSON_INT);
    int32_t resultButtonType = jsonValue->GetInt(ATTRIBUTE_BUTTON_TYPE_NAME, DEFAULT_JSON_INT);
    EXPECT_EQ(resultText, static_cast<int32_t>(LocationButtonStyle::DEFAULT_TEXT));
    EXPECT_EQ(resultIcon, static_cast<int32_t>(LocationButtonStyle::DEFAULT_ICON));
    EXPECT_EQ(resultButtonType, static_cast<int32_t>(LocationButtonStyle::DEFAULT_BACKGROUND_TYPE));
}

// Valid values for attribute 'icon' of method 'setLocationButtonOptions'
using IconValidValuesStep = std::tuple<std::string, Opt_LocationIconStyle, LocationButtonIconStyle>;
static std::vector<IconValidValuesStep> setLocationButtonOptionsIconValidValues = {
    {
        "ARK_LOCATION_ICON_STYLE_FULL_FILLED",
        Converter::ArkValue<Opt_LocationIconStyle>(ARK_LOCATION_ICON_STYLE_FULL_FILLED),
        LocationButtonIconStyle::ICON_FULL_FILLED
    },
    {
        "ARK_LOCATION_ICON_STYLE_LINES",
        Converter::ArkValue<Opt_LocationIconStyle>(ARK_LOCATION_ICON_STYLE_LINES),
        LocationButtonIconStyle::ICON_LINE
    },
};

// Valid values for attribute 'text' of method 'setLocationButtonOptions'
using TextValidValuesStep = std::tuple<std::string, Opt_LocationDescription, LocationButtonLocationDescription>;
static std::vector<TextValidValuesStep> setLocationButtonOptionsTextValidValues = {
    {
        "ARK_LOCATION_DESCRIPTION_CURRENT_LOCATION",
        Converter::ArkValue<Opt_LocationDescription>(ARK_LOCATION_DESCRIPTION_CURRENT_LOCATION),
        LocationButtonLocationDescription::CURRENT_LOCATION
    },
    {
        "ARK_LOCATION_DESCRIPTION_ADD_LOCATION",
        Converter::ArkValue<Opt_LocationDescription>(ARK_LOCATION_DESCRIPTION_ADD_LOCATION),
        LocationButtonLocationDescription::ADD_LOCATION
    },
    {
        "ARK_LOCATION_DESCRIPTION_SELECT_LOCATION",
        Converter::ArkValue<Opt_LocationDescription>(ARK_LOCATION_DESCRIPTION_SELECT_LOCATION),
        LocationButtonLocationDescription::SELECT_LOCATION
    },
    {
        "ARK_LOCATION_DESCRIPTION_SHARE_LOCATION",
        Converter::ArkValue<Opt_LocationDescription>(ARK_LOCATION_DESCRIPTION_SHARE_LOCATION),
        LocationButtonLocationDescription::SHARE_LOCATION
    },
    {
        "ARK_LOCATION_DESCRIPTION_SEND_LOCATION",
        Converter::ArkValue<Opt_LocationDescription>(ARK_LOCATION_DESCRIPTION_SEND_LOCATION),
        LocationButtonLocationDescription::SEND_LOCATION
    },
    {
        "ARK_LOCATION_DESCRIPTION_LOCATING",
        Converter::ArkValue<Opt_LocationDescription>(ARK_LOCATION_DESCRIPTION_LOCATING),
        LocationButtonLocationDescription::LOCATING
    },
    {
        "ARK_LOCATION_DESCRIPTION_LOCATION",
        Converter::ArkValue<Opt_LocationDescription>(ARK_LOCATION_DESCRIPTION_LOCATION),
        LocationButtonLocationDescription::LOCATION
    },
    {
        "ARK_LOCATION_DESCRIPTION_SEND_CURRENT_LOCATION",
        Converter::ArkValue<Opt_LocationDescription>(ARK_LOCATION_DESCRIPTION_SEND_CURRENT_LOCATION),
        LocationButtonLocationDescription::SEND_CURRENT_LOCATION
    },
    {
        "ARK_LOCATION_DESCRIPTION_RELOCATION",
        Converter::ArkValue<Opt_LocationDescription>(ARK_LOCATION_DESCRIPTION_RELOCATION),
        LocationButtonLocationDescription::RELOCATION
    },
    {
        "ARK_LOCATION_DESCRIPTION_PUNCH_IN",
        Converter::ArkValue<Opt_LocationDescription>(ARK_LOCATION_DESCRIPTION_PUNCH_IN),
        LocationButtonLocationDescription::PUNCHIN
    },
    {
        "ARK_LOCATION_DESCRIPTION_CURRENT_POSITION",
        Converter::ArkValue<Opt_LocationDescription>(ARK_LOCATION_DESCRIPTION_CURRENT_POSITION),
        LocationButtonLocationDescription::CURRENT_POSITION
    },
};

// Valid values for attribute 'buttonType' of method 'setLocationButtonOptions'
using ButtonTypeValidValuesStep = std::tuple<std::string, Opt_ButtonType, ButtonType>;
static std::vector<ButtonTypeValidValuesStep> setLocationButtonOptionsButtonTypeValidValues = {
    {
        "ARK_BUTTON_TYPE_CAPSULE",
        Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE),
        ButtonType::CAPSULE
    },
    {
        "ARK_BUTTON_TYPE_CIRCLE",
        Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CIRCLE),
        ButtonType::CIRCLE
    },
    {
        "ARK_BUTTON_TYPE_NORMAL",
        Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_NORMAL),
        ButtonType::NORMAL
    },
    {
        "ARK_BUTTON_TYPE_ROUNDED_RECTANGLE",
        Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_ROUNDED_RECTANGLE),
        ButtonType::ROUNDED_RECTANGLE
    },
};

/*
 * @tc.name: setLocationButtonOptions1TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LocationButtonModifierTest, setLocationButtonOptions1TestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    int32_t result;
    int32_t expected;
    Ark_LocationButtonOptions inputValueOptions;
    Ark_LocationButtonOptions initValueOptions;

    // Initial setup
    initValueOptions.icon = std::get<1>(setLocationButtonOptionsIconValidValues[0]);
    initValueOptions.text = std::get<1>(setLocationButtonOptionsTextValidValues[0]);
    initValueOptions.buttonType = std::get<1>(setLocationButtonOptionsButtonTypeValidValues[0]);

    // Verifying attribute's 'icon'  values
    inputValueOptions = initValueOptions;
    for (auto&& value: setLocationButtonOptionsIconValidValues) {
        inputValueOptions.icon = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setLocationButtonOptions1(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        DisposeNode(node);
        result = jsonValue->GetInt(ATTRIBUTE_ICON_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(std::get<2>(value));
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'text'  values
    inputValueOptions = initValueOptions;
    for (auto&& value: setLocationButtonOptionsTextValidValues) {
        inputValueOptions.text = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setLocationButtonOptions1(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        DisposeNode(node);
        result = jsonValue->GetInt(ATTRIBUTE_TEXT_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(std::get<2>(value));
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'buttonType'  values
    inputValueOptions = initValueOptions;
    for (auto&& value: setLocationButtonOptionsButtonTypeValidValues) {
        inputValueOptions.buttonType = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setLocationButtonOptions1(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        DisposeNode(node);
        result = jsonValue->GetInt(ATTRIBUTE_BUTTON_TYPE_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(std::get<2>(value));
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'icon' of method 'setLocationButtonOptions'
static std::vector<std::tuple<std::string, Opt_LocationIconStyle>> setLocationButtonOptionsIconInvalidValues = {
    {
        "Ark_Empty()",
        Converter::ArkValue<Opt_LocationIconStyle>(Ark_Empty())
    },
    {
        "static_cast<Ark_LocationIconStyle>(-1)",
        Converter::ArkValue<Opt_LocationIconStyle>(static_cast<Ark_LocationIconStyle>(-1))
    },
};

// Invalid values for attribute 'text' of method 'setLocationButtonOptions'
static std::vector<std::tuple<std::string, Opt_LocationDescription>> setLocationButtonOptionsTextInvalidValues = {
    {
        "Ark_Empty()",
        Converter::ArkValue<Opt_LocationDescription>(Ark_Empty())
    },
    {
        "static_cast<Ark_LocationDescription>(-1)",
        Converter::ArkValue<Opt_LocationDescription>(static_cast<Ark_LocationDescription>(-1))
    },
};

// Invalid values for attribute 'buttonType' of method 'setLocationButtonOptions'
static std::vector<std::tuple<std::string, Opt_ButtonType>> setLocationButtonOptionsButtonTypeInvalidValues = {
    {
        "Ark_Empty()",
        Converter::ArkValue<Opt_ButtonType>(Ark_Empty())
    },
    {
        "static_cast<Ark_ButtonType>(-1)",
        Converter::ArkValue<Opt_ButtonType>(static_cast<Ark_ButtonType>(-1))
    },
};

/*
 * @tc.name: setLocationButtonOptions1TestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LocationButtonModifierTest, setLocationButtonOptions1TestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    int32_t result;
    int32_t expected;
    Ark_LocationButtonOptions inputValueOptions;
    Ark_LocationButtonOptions initValueOptions;

    // Initial setup
    initValueOptions.icon = std::get<1>(setLocationButtonOptionsIconValidValues[0]);
    initValueOptions.text = std::get<1>(setLocationButtonOptionsTextValidValues[0]);
    initValueOptions.buttonType = std::get<1>(setLocationButtonOptionsButtonTypeValidValues[0]);

    // Verifying attribute's 'icon'  values
    for (auto&& value: setLocationButtonOptionsIconInvalidValues) {
        inputValueOptions = initValueOptions;
        inputValueOptions.icon = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setLocationButtonOptions1(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        DisposeNode(node);
        result = jsonValue->GetInt(ATTRIBUTE_ICON_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(ATTRIBUTE_ICON_DEFAULT_VALUE);
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'text'  values
    for (auto&& value: setLocationButtonOptionsTextInvalidValues) {
        inputValueOptions = initValueOptions;
        inputValueOptions.text = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setLocationButtonOptions1(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        DisposeNode(node);
        result = jsonValue->GetInt(ATTRIBUTE_TEXT_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(ATTRIBUTE_TEXT_DEFAULT_VALUE);
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'buttonType'  values
    for (auto&& value: setLocationButtonOptionsButtonTypeInvalidValues) {
        inputValueOptions = initValueOptions;
        inputValueOptions.buttonType = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setLocationButtonOptions1(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        DisposeNode(node);
        result = jsonValue->GetInt(ATTRIBUTE_BUTTON_TYPE_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(ATTRIBUTE_BUTTON_TYPE_DEFAULT_VALUE);
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setLocationButtonOptions1TestTextAndIconEmpty
 * @tc.desc: Verify that all attributes are set to default values in case neither text nor icon is set.
 * @tc.type: FUNC
 */
HWTEST_F(LocationButtonModifierTest, setLocationButtonOptions1TestTextAndIconEmpty, TestSize.Level1)
{
    Ark_LocationButtonOptions inputValueOptions = {
        .text = Converter::ArkValue<Opt_LocationDescription>(Ark_Empty()),
        .icon = Converter::ArkValue<Opt_LocationIconStyle>(Ark_Empty()),
        .buttonType = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_NORMAL)
    };
    auto node = CreateNode();
    modifier_->setLocationButtonOptions1(node, &inputValueOptions);
    auto jsonValue = GetJsonValue(node);
    DisposeNode(node);
    int32_t resultText = jsonValue->GetInt(ATTRIBUTE_TEXT_NAME, DEFAULT_JSON_INT);
    int32_t resultIcon = jsonValue->GetInt(ATTRIBUTE_ICON_NAME, DEFAULT_JSON_INT);
    int32_t resultButtonType = jsonValue->GetInt(ATTRIBUTE_BUTTON_TYPE_NAME, DEFAULT_JSON_INT);
    EXPECT_EQ(resultText, static_cast<int32_t>(LocationButtonStyle::DEFAULT_TEXT));
    EXPECT_EQ(resultIcon, static_cast<int32_t>(LocationButtonStyle::DEFAULT_ICON));
    EXPECT_EQ(resultButtonType, static_cast<int32_t>(LocationButtonStyle::DEFAULT_BACKGROUND_TYPE));
}

struct CheckEvent {
    int32_t nodeId;
    Ark_Int32 offsetX = -1;
    Ark_Int32 offsetY = -1;
    std::optional<Ark_LocationButtonOnClickResult> result = std::nullopt;
};

/*
 * @tc.name: setOnClickTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LocationButtonModifierTest, setOnClickTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_ClickEvent peer,
            const Ark_LocationButtonOnClickResult result, Opt_BusinessError error) {
        ASSERT_NE(peer, nullptr);
        auto accessor = GeneratedModifier::GetClickEventAccessor();
        checkEvent = {
            .nodeId = resourceId,
            .offsetX = Converter::Convert<int32_t>(accessor->getWindowX(peer)),
            .offsetY = Converter::Convert<int32_t>(accessor->getWindowY(peer)),
            .result = result
        };
        accessor->destroyPeer(peer);
    };
    const int32_t contextId = 123;
    auto func = Converter::ArkValue<LocationButtonCallback>(checkCallback, contextId);
    auto optFunc = Converter::ArkValue<Opt_LocationButtonCallback>(func);
    modifier_->setOnClick(node_, &optFunc);

    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameOffset({OFFSET_X, OFFSET_Y});

    auto testFunc = [gestureEventHub](SecurityComponentHandleResult input, Ark_LocationButtonOnClickResult expected) {
        checkEvent.reset();
        gestureEventHub->ActClick(CreateJson(input));
        ASSERT_TRUE(checkEvent.has_value() && checkEvent->result.has_value());
        EXPECT_EQ(checkEvent->result.value(), expected);
        EXPECT_EQ(checkEvent->offsetX, static_cast<int32_t>(OFFSET_X));
        EXPECT_EQ(checkEvent->offsetY, static_cast<int32_t>(OFFSET_Y));
    };

#ifdef SECURITY_COMPONENT_ENABLE
    testFunc(SecurityComponentHandleResult::CLICK_SUCCESS, ARK_LOCATION_BUTTON_ON_CLICK_RESULT_SUCCESS);
    testFunc(SecurityComponentHandleResult::CLICK_GRANT_FAILED,
        ARK_LOCATION_BUTTON_ON_CLICK_RESULT_TEMPORARY_AUTHORIZATION_FAILED);

    checkEvent.reset();
    gestureEventHub->ActClick(CreateJson(SecurityComponentHandleResult::DROP_CLICK));
    ASSERT_FALSE(checkEvent.has_value());
#else
    testFunc(SecurityComponentHandleResult::CLICK_SUCCESS,
        ARK_LOCATION_BUTTON_ON_CLICK_RESULT_TEMPORARY_AUTHORIZATION_FAILED);
    testFunc(SecurityComponentHandleResult::CLICK_GRANT_FAILED,
        ARK_LOCATION_BUTTON_ON_CLICK_RESULT_TEMPORARY_AUTHORIZATION_FAILED);
    testFunc(SecurityComponentHandleResult::DROP_CLICK,
        ARK_LOCATION_BUTTON_ON_CLICK_RESULT_TEMPORARY_AUTHORIZATION_FAILED);
#endif
}

} // namespace OHOS::Ace::NG
