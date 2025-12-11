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
#include "core/components_ng/pattern/security_component/paste_button/paste_button_common.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_model_ng.h"
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
    const auto ATTRIBUTE_ICON_DEFAULT_VALUE = PasteButtonIconStyle::ICON_NULL;
    const auto ATTRIBUTE_TEXT_NAME = "text";
    const auto ATTRIBUTE_TEXT_DEFAULT_VALUE = PasteButtonPasteDescription::TEXT_NULL;
    const auto ATTRIBUTE_BUTTON_TYPE_NAME = "buttonType";
    const auto ATTRIBUTE_BUTTON_TYPE_DEFAULT_VALUE = ButtonType::CAPSULE;

    const auto DEFAULT_JSON_INT = -1;
    constexpr double OFFSET_X = 60.4;
    constexpr double OFFSET_Y = 85.5;
} // namespace

class PasteButtonModifierTest : public ModifierTestBase<GENERATED_ArkUIPasteButtonModifier,
    &GENERATED_ArkUINodeModifiers::getPasteButtonModifier, GENERATED_ARKUI_PASTE_BUTTON> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<SecurityComponentTheme>();
    }
};

/*
 * @tc.name: setPasteButtonOptions0
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PasteButtonModifierTest, setPasteButtonOptions0, TestSize.Level1)
{
    auto node = CreateNode();
    modifier_->setPasteButtonOptions0(node);
    auto jsonValue = GetJsonValue(node);
    DisposeNode(node);
    int32_t resultText = jsonValue->GetInt(ATTRIBUTE_TEXT_NAME, DEFAULT_JSON_INT);
    int32_t resultIcon = jsonValue->GetInt(ATTRIBUTE_ICON_NAME, DEFAULT_JSON_INT);
    int32_t resultButtonType = jsonValue->GetInt(ATTRIBUTE_BUTTON_TYPE_NAME, DEFAULT_JSON_INT);
    EXPECT_EQ(resultText, static_cast<int32_t>(PasteButtonStyle::DEFAULT_TEXT));
    EXPECT_EQ(resultIcon, static_cast<int32_t>(PasteButtonStyle::DEFAULT_ICON));
    EXPECT_EQ(resultButtonType, static_cast<int32_t>(PasteButtonStyle::DEFAULT_BACKGROUND_TYPE));
}

// Valid values for attribute 'icon' of method 'setPasteButtonOptions'
using IconValidValuesStep = std::tuple<std::string, Opt_PasteIconStyle, PasteButtonIconStyle>;
static std::vector<IconValidValuesStep> setPasteButtonOptionsIconValidValues = {
    {
        "ARK_PASTE_ICON_STYLE_LINES",
        Converter::ArkValue<Opt_PasteIconStyle>(ARK_PASTE_ICON_STYLE_LINES),
        PasteButtonIconStyle::ICON_LINE
    },
};

// Valid values for attribute 'text' of method 'setPasteButtonOptions'
using TextValidValuesStep = std::tuple<std::string, Opt_PasteDescription, PasteButtonPasteDescription>;
static std::vector<TextValidValuesStep> setPasteButtonOptionsTextValidValues = {
    {
        "ARK_PASTE_DESCRIPTION_PASTE",
        Converter::ArkValue<Opt_PasteDescription>(ARK_PASTE_DESCRIPTION_PASTE),
        PasteButtonPasteDescription::PASTE
    },
};

// Valid values for attribute 'buttonType' of method 'setPasteButtonOptions'
static std::vector<std::tuple<std::string, Opt_ButtonType, ButtonType>> setPasteButtonOptionsButtonTypeValidValues = {
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
 * @tc.name: setPasteButtonOptions1TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PasteButtonModifierTest, setPasteButtonOptions1TestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    int32_t result;
    int32_t expected;
    Ark_PasteButtonOptions inputValueOptions;
    Ark_PasteButtonOptions initValueOptions;

    // Initial setup
    initValueOptions.icon = std::get<1>(setPasteButtonOptionsIconValidValues[0]);
    initValueOptions.text = std::get<1>(setPasteButtonOptionsTextValidValues[0]);
    initValueOptions.buttonType = std::get<1>(setPasteButtonOptionsButtonTypeValidValues[0]);

    // Verifying attribute's 'icon'  values
    inputValueOptions = initValueOptions;
    for (auto&& value: setPasteButtonOptionsIconValidValues) {
        inputValueOptions.icon = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setPasteButtonOptions1(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        DisposeNode(node);
        result = jsonValue->GetInt(ATTRIBUTE_ICON_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(std::get<2>(value));
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'text'  values
    inputValueOptions = initValueOptions;
    for (auto&& value: setPasteButtonOptionsTextValidValues) {
        inputValueOptions.text = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setPasteButtonOptions1(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        DisposeNode(node);
        result = jsonValue->GetInt(ATTRIBUTE_TEXT_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(std::get<2>(value));
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'buttonType'  values
    inputValueOptions = initValueOptions;
    for (auto&& value: setPasteButtonOptionsButtonTypeValidValues) {
        inputValueOptions.buttonType = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setPasteButtonOptions1(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        DisposeNode(node);
        result = jsonValue->GetInt(ATTRIBUTE_BUTTON_TYPE_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(std::get<2>(value));
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'icon' of method 'setPasteButtonOptions'
static std::vector<std::tuple<std::string, Opt_PasteIconStyle>> setPasteButtonOptionsIconInvalidValues = {
    {
        "Ark_Empty()",
        Converter::ArkValue<Opt_PasteIconStyle>(Ark_Empty())
    },
    {
        "static_cast<Ark_PasteIconStyle>(-1)",
        Converter::ArkValue<Opt_PasteIconStyle>(static_cast<Ark_PasteIconStyle>(-1))
    },
};

// Invalid values for attribute 'text' of method 'setPasteButtonOptions'
static std::vector<std::tuple<std::string, Opt_PasteDescription>> setPasteButtonOptionsTextInvalidValues = {
    {
        "Ark_Empty()",
        Converter::ArkValue<Opt_PasteDescription>(Ark_Empty())
    },
    {
        "static_cast<Ark_PasteDescription>(-1)",
        Converter::ArkValue<Opt_PasteDescription>(static_cast<Ark_PasteDescription>(-1))
    },
};

// Invalid values for attribute 'buttonType' of method 'setPasteButtonOptions'
static std::vector<std::tuple<std::string, Opt_ButtonType>> setPasteButtonOptionsButtonTypeInvalidValues = {
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
 * @tc.name: setPasteButtonOptions1TestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PasteButtonModifierTest, setPasteButtonOptions1TestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    int32_t result;
    int32_t expected;
    Ark_PasteButtonOptions inputValueOptions;
    Ark_PasteButtonOptions initValueOptions;

    // Initial setup
    initValueOptions.icon = std::get<1>(setPasteButtonOptionsIconValidValues[0]);
    initValueOptions.text = std::get<1>(setPasteButtonOptionsTextValidValues[0]);
    initValueOptions.buttonType = std::get<1>(setPasteButtonOptionsButtonTypeValidValues[0]);

    // Verifying attribute's 'icon'  values
    for (auto&& value: setPasteButtonOptionsIconInvalidValues) {
        inputValueOptions = initValueOptions;
        inputValueOptions.icon = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setPasteButtonOptions1(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        DisposeNode(node);
        result = jsonValue->GetInt(ATTRIBUTE_ICON_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(ATTRIBUTE_ICON_DEFAULT_VALUE);
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'text'  values
    for (auto&& value: setPasteButtonOptionsTextInvalidValues) {
        inputValueOptions = initValueOptions;
        inputValueOptions.text = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setPasteButtonOptions1(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        DisposeNode(node);
        result = jsonValue->GetInt(ATTRIBUTE_TEXT_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(ATTRIBUTE_TEXT_DEFAULT_VALUE);
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'buttonType'  values
    for (auto&& value: setPasteButtonOptionsButtonTypeInvalidValues) {
        inputValueOptions = initValueOptions;
        inputValueOptions.buttonType = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setPasteButtonOptions1(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        DisposeNode(node);
        result = jsonValue->GetInt(ATTRIBUTE_BUTTON_TYPE_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(ATTRIBUTE_BUTTON_TYPE_DEFAULT_VALUE);
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setPasteButtonOptions1TestTextAndIconEmpty
 * @tc.desc: Verify that all attributes are set to default values in case neither text nor icon is set.
 * @tc.type: FUNC
 */
HWTEST_F(PasteButtonModifierTest, setPasteButtonOptions1TestTextAndIconEmpty, TestSize.Level1)
{
    Ark_PasteButtonOptions inputValueOptions = {
        .text = Converter::ArkValue<Opt_PasteDescription>(Ark_Empty()),
        .icon = Converter::ArkValue<Opt_PasteIconStyle>(Ark_Empty()),
        .buttonType = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_NORMAL)
    };
    auto node = CreateNode();
    modifier_->setPasteButtonOptions1(node, &inputValueOptions);
    auto jsonValue = GetJsonValue(node);
    DisposeNode(node);
    int32_t resultText = jsonValue->GetInt(ATTRIBUTE_TEXT_NAME, DEFAULT_JSON_INT);
    int32_t resultIcon = jsonValue->GetInt(ATTRIBUTE_ICON_NAME, DEFAULT_JSON_INT);
    int32_t resultButtonType = jsonValue->GetInt(ATTRIBUTE_BUTTON_TYPE_NAME, DEFAULT_JSON_INT);
    EXPECT_EQ(resultText, static_cast<int32_t>(PasteButtonStyle::DEFAULT_TEXT));
    EXPECT_EQ(resultIcon, static_cast<int32_t>(PasteButtonStyle::DEFAULT_ICON));
    EXPECT_EQ(resultButtonType, static_cast<int32_t>(PasteButtonStyle::DEFAULT_BACKGROUND_TYPE));
}

struct CheckEvent {
    int32_t nodeId;
    Ark_Number offsetX = Converter::ArkValue<Ark_Number>(-1.0f);
    Ark_Number offsetY = Converter::ArkValue<Ark_Number>(-1.0f);
    std::optional<Ark_PasteButtonOnClickResult> result = std::nullopt;
};

#ifdef SECURITY_COMPONENT_ENABLE
/*
 * @tc.name: setOnClickTestSecurity
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PasteButtonModifierTest, setOnClickTestSecurity, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onClick = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_ClickEvent event,
        Ark_PasteButtonOnClickResult result, Opt_BusinessError error) {
        auto peer = event;
        ASSERT_NE(peer, nullptr);
        auto accessor = GeneratedModifier::GetClickEventAccessor();
        checkEvent = {
            .nodeId = resourceId,
            .offsetX = accessor->getWindowX(peer),
            .offsetY = accessor->getWindowY(peer),
            .result = result
        };
        accessor->destroyPeer(peer);
    };

    auto func = Converter::ArkValue<PasteButtonCallback>(onClick, frameNode->GetId());
    auto arkCallback = Converter::ArkValue<Opt_PasteButtonCallback>(func);
    modifier_->setOnClick(node_, &arkCallback);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameOffset({OFFSET_X, OFFSET_Y});

    auto createJson = [](SecurityComponentHandleResult value) {
        int32_t res = static_cast<int32_t>(value);
        auto jsonNode = JsonUtil::Create(true);
        jsonNode->Put("handleRes", res);
        std::shared_ptr<JsonValue> jsonShrd(jsonNode.release());
        return jsonShrd;
    };

    auto testFunction = [gestureEventHub, createJson](SecurityComponentHandleResult input,
        Ark_PasteButtonOnClickResult expected) {
        checkEvent.reset();
        gestureEventHub->ActClick(createJson(input));
        ASSERT_TRUE(checkEvent);
        ASSERT_TRUE(checkEvent->result);
        EXPECT_EQ(checkEvent->result.value(), expected);
        EXPECT_FLOAT_EQ(Converter::Convert<double>(checkEvent->offsetX), OFFSET_X);
        EXPECT_FLOAT_EQ(Converter::Convert<double>(checkEvent->offsetY), OFFSET_Y);
    };

    testFunction(SecurityComponentHandleResult::CLICK_SUCCESS,
        ARK_PASTE_BUTTON_ON_CLICK_RESULT_SUCCESS);
    testFunction(SecurityComponentHandleResult::CLICK_GRANT_FAILED,
        ARK_PASTE_BUTTON_ON_CLICK_RESULT_TEMPORARY_AUTHORIZATION_FAILED);

    checkEvent.reset();
    gestureEventHub->ActClick(createJson(SecurityComponentHandleResult::DROP_CLICK));
    ASSERT_FALSE(checkEvent); // callback is not called in modifier in DROP_CLICK case
}
#else
/*
 * @tc.name: setOnClickTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PasteButtonModifierTest, setOnClickTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onClick = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_ClickEvent event,
        Ark_PasteButtonOnClickResult result, Opt_BusinessError error) {
        auto peer = event;
        ASSERT_NE(peer, nullptr);
        auto accessor = GeneratedModifier::GetClickEventAccessor();
        checkEvent = {
            .nodeId = resourceId,
            .offsetX = accessor->getWindowX(peer),
            .offsetY = accessor->getWindowY(peer),
            .result = result
        };
        accessor->destroyPeer(peer);
    };

    auto func = Converter::ArkValue<PasteButtonCallback>(onClick, frameNode->GetId());
    auto arkCallback = Converter::ArkValue<Opt_PasteButtonCallback>(func);
    modifier_->setOnClick(node_, &arkCallback);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameOffset({OFFSET_X, OFFSET_Y});

    auto createJson = [](SecurityComponentHandleResult value)
    {
        int32_t res = static_cast<int32_t>(value);
        auto jsonNode = JsonUtil::Create(true);
        jsonNode->Put("handleRes", res);
        std::shared_ptr<JsonValue> jsonShrd(jsonNode.release());
        return jsonShrd;
    };

    auto testFunction = [gestureEventHub, createJson](SecurityComponentHandleResult input,
        Ark_PasteButtonOnClickResult expected) {
        checkEvent.reset();
        gestureEventHub->ActClick(createJson(input));
        ASSERT_TRUE(checkEvent);
        EXPECT_EQ(checkEvent->result, expected);
        EXPECT_FLOAT_EQ(Converter::Convert<double>(checkEvent->offsetX), OFFSET_X);
        EXPECT_FLOAT_EQ(Converter::Convert<double>(checkEvent->offsetY), OFFSET_Y);
    };

    testFunction(SecurityComponentHandleResult::CLICK_SUCCESS,
        ARK_PASTE_BUTTON_ON_CLICK_RESULT_TEMPORARY_AUTHORIZATION_FAILED);
    testFunction(SecurityComponentHandleResult::CLICK_GRANT_FAILED,
        ARK_PASTE_BUTTON_ON_CLICK_RESULT_TEMPORARY_AUTHORIZATION_FAILED);
    testFunction(SecurityComponentHandleResult::DROP_CLICK,
        ARK_PASTE_BUTTON_ON_CLICK_RESULT_TEMPORARY_AUTHORIZATION_FAILED);
}
#endif
} // namespace OHOS::Ace::NG
