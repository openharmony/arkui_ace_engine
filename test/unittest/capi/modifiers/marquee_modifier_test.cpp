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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/marquee/marquee_event_hub.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_ALLOW_SCALE_NAME = "allowScale";
    const auto ATTRIBUTE_ALLOW_SCALE_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_FONT_COLOR_NAME = "fontColor";
    const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = "#FF000000";
    const auto ATTRIBUTE_FONT_COLOR_INVALID_VALUE = "#00000000";
    const auto ATTRIBUTE_FONT_FAMILY_NAME("fontFamily");
    const auto ATTRIBUTE_FONT_SIZE_NAME("fontSize");
    const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE("10.00vp");
    const auto ATTRIBUTE_FONT_WEIGHT_NAME("fontWeight");
    const auto ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE("FontWeight.Normal");
    const auto ATTRIBUTE_UPDATE_STRATEGY_NAME("marqueeUpdateStrategy");
    const auto ATTRIBUTE_UPDATE_STRATEGY_DEFAULT_VALUE("MarqueeUpdateStrategy.DEFAULT");
    const auto ATTRIBUTE_UPDATE_STRATEGY_TEST_VALUE("MarqueeUpdateStrategy.PRESERVE_POSITION");
    const auto ATTRIBUTE_STEP_NAME("step");
    const auto ATTRIBUTE_STEP_DEFAULT_VALUE("6.000000");
    const auto ATTRIBUTE_LOOP_NAME("loop");
    const auto ATTRIBUTE_LOOP_DEFAULT_VALUE("-1");
    const auto ATTRIBUTE_SRC_NAME("src");
    const auto ATTRIBUTE_SRC_DEFAULT_VALUE("");
    const auto ATTRIBUTE_PLAYER_STATUS_NAME("start");
    const auto ATTRIBUTE_PLAYER_STATUS_DEFAULT_VALUE("true");
    const auto ATTRIBUTE_DIRECTION_NAME("fromStart");
    const auto ATTRIBUTE_DIRECTION_DEFAULT_VALUE("false");

} // namespace

class MarqueeModifierTest : public ModifierTestBase<GENERATED_ArkUIMarqueeModifier,
    &GENERATED_ArkUINodeModifiers::getMarqueeModifier, GENERATED_ARKUI_MARQUEE> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
    }
};

/*
 * @tc.name: setAllowScaleTestDefaultValues
 * @tc.desc: Check the functionality of MarqueeModifier.setAllowScale
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, setAllowScaleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALLOW_SCALE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALLOW_SCALE_DEFAULT_VALUE);
}

// Valid values for attribute 'select' of method 'select'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> allowScaleValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setAllowScaleTestValidValues
 * @tc.desc: Check the functionality of MarqueeModifier.setAllowScale
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, setAllowScaleTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueAllowScale;
    Ark_Boolean initValueAllowScale;

    // Initial setup
    initValueAllowScale = std::get<1>(allowScaleValidValues[0]);

    // Verifying attribute's  values
    inputValueAllowScale = initValueAllowScale;
    for (auto&& value: allowScaleValidValues) {
        inputValueAllowScale = std::get<1>(value);
        auto optInputValueAllowScale = Converter::ArkValue<Opt_Boolean>(inputValueAllowScale);
        modifier_->setAllowScale(node_, &optInputValueAllowScale);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALLOW_SCALE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setFontColorTestDefaultValues
 * @tc.desc: Check the functionality of MarqueeModifier.setFontColor
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, setFontColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
}

// Valid values for attribute 'fontColor' of method 'fontColor'
static std::vector<std::tuple<std::string, Ark_ResourceColor, std::string>> fontColorFontColorValidValues = {
    { "ARK_COLOR_BLUE", Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { "ARK_COLOR_RED", Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_RED), "#FFFF0000" },
};

/*
 * @tc.name: setFontColorTestValidValues
 * @tc.desc: Check the functionality of MarqueeModifier.setFontColor
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, setFontColorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_ResourceColor inputValueFontColor;
    Ark_ResourceColor initValueFontColor;

    // Initial setup
    initValueFontColor = std::get<1>(fontColorFontColorValidValues[0]);

    // Verifying attribute's  values
    inputValueFontColor = initValueFontColor;
    for (auto&& value: fontColorFontColorValidValues) {
        inputValueFontColor = std::get<1>(value);
        auto optInputValueFontColor = Converter::ArkValue<Opt_ResourceColor>(inputValueFontColor);
        modifier_->setFontColor(node_, &optInputValueFontColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setFontColorTestInvalidValues
 * @tc.desc: Check the functionality of MarqueeModifier.setFontColor
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, DISABLED_setFontColorTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_ResourceColor inputValueFontColor;

    // Verifying attribute's  values
    inputValueFontColor = Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0xffffffff + 1);
    auto optInputValueFontColor = Converter::ArkValue<Opt_ResourceColor>(inputValueFontColor);
    modifier_->setFontColor(node_, &optInputValueFontColor);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
    expectedStr = ATTRIBUTE_FONT_COLOR_INVALID_VALUE;
    EXPECT_EQ(resultStr, expectedStr);
}

/*
 * @tc.name: setFontFamilyTestValidValueson
 * @tc.desc: Check the functionality of MarqueeModifier.setFontFamily
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, setFontFamilyTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    auto inputStringValue = "testFamily";
    auto inputArkStringValue = Converter::ArkValue<Ark_String>(inputStringValue);
    auto inputValue = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(inputArkStringValue);

    auto optInputValue = Converter::ArkValue<Opt_Union_String_Resource>(inputValue);
    modifier_->setFontFamily(node_, &optInputValue);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
    EXPECT_EQ(resultStr, inputStringValue);

    inputStringValue = "testFamily1, testFamily2";
    inputArkStringValue = Converter::ArkValue<Ark_String>(inputStringValue);
    inputValue = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(inputArkStringValue);

    optInputValue = Converter::ArkValue<Opt_Union_String_Resource>(inputValue);
    modifier_->setFontFamily(node_, &optInputValue);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
    EXPECT_EQ(resultStr, inputStringValue);

    inputStringValue = "testFamily1, testFamily2";
    inputArkStringValue = Converter::ArkValue<Ark_String>(inputStringValue);
    inputValue = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(inputArkStringValue);

    optInputValue = Converter::ArkValue<Opt_Union_String_Resource>(inputValue);
    modifier_->setFontFamily(node_, &optInputValue);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
    EXPECT_EQ(resultStr, inputStringValue);
}

/*
 * @tc.name: setFontSizeDefaultValues
 * @tc.desc: Check the functionality of MarqueeModifier.setFontSize
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, setFontSizeDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto size = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
    EXPECT_EQ(size, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
}

/*
 * @tc.name: setFontSizeTestValidValues
 * @tc.desc: Check the functionality of MarqueeModifier.setFontSize
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, DISABLED_setFontSizeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    typedef std::pair<Opt_Length, std::string> OneTestStep;
    const std::vector<OneTestStep> testFontSizeValid = {
        { Converter::ArkValue<Opt_Length>(1.0f),  "1.00vp" },
        { Converter::ArkValue<Opt_Length>(2.45f), "2.45vp" },
        { Converter::ArkValue<Opt_Length>("5.0px"), "5.00px" },
        { Converter::ArkValue<Opt_Length>("22.35px"), "22.35px" },
        { Converter::ArkValue<Opt_Length>("7.0vp"), "7.00vp" },
        { Converter::ArkValue<Opt_Length>("1.65vp"), "1.65vp" },
        { Converter::ArkValue<Opt_Length>("65.0fp"), "65.00fp" },
        { Converter::ArkValue<Opt_Length>("4.3fp"), "4.30fp" },
    };
    for (const auto &[value, expectValue]: testFontSizeValid) {
        modifier_->setFontSize(node_, &value);
        jsonValue = GetJsonValue(node_);
        auto size = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(size, expectValue);
    }
}
/*
 * @tc.name: setFontSizeInvalidValues
 * @tc.desc: Check the functionality of MarqueeModifier.setFontSize
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, DISABLED_setFontSizeInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    typedef std::pair<Opt_Length, std::string> OneTestStep;
    const std::vector<OneTestStep> testFontSizeInvalid = {
        { Converter::ArkValue<Opt_Length>(-0.1f), "10.00p"},
        { Converter::ArkValue<Opt_Length>("-5.0px"), "10.00vp" },
    };
    for (const auto &[value, expectValue]: testFontSizeInvalid) {
        modifier_->setFontSize(node_, &value);
        jsonValue = GetJsonValue(node_);
        auto size = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(size, expectValue);
    }
}

using  ArkFontWeightTest = std::pair<Ark_Union_I32_FontWeight_String, std::string>;
namespace Converter {
const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN = {
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_FontWeight>(ARK_FONT_WEIGHT_LIGHTER), "FontWeight.Lighter" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_FontWeight>(ARK_FONT_WEIGHT_NORMAL), "FontWeight.Normal" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_FontWeight>(ARK_FONT_WEIGHT_REGULAR), "FontWeight.Regular" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_FontWeight>(ARK_FONT_WEIGHT_MEDIUM), "FontWeight.Medium" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLD), "FontWeight.Bold" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLDER), "FontWeight.Bolder" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_Int32>(100), "100" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_Int32>(200), "200" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_Int32>(300), "300" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_Int32>(400), "400" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_Int32>(500), "500" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_Int32>(600), "600" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_Int32>(700), "700" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_Int32>(800), "800" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_Int32>(900), "900" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_String>("lighter"), "FontWeight.Lighter" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_String>("normal"), "FontWeight.Normal" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_String>("regular"), "FontWeight.Regular" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_String>("medium"), "FontWeight.Medium" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_String>("bold"), "FontWeight.Bold" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_String>("bolder"), "FontWeight.Bolder" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_String>("100"), "100" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_String>("200"), "200" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_String>("300"), "300" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_String>("400"), "400" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_String>("500"), "500" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_String>("600"), "600" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_String>("700"), "700" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_String>("800"), "800" },
    { ArkUnion<Ark_Union_I32_FontWeight_String, Ark_String>("900"), "900" },
};
}

/**
 * @tc.name: setFontWeightTestDefaultValue
 * @tc.desc: Check the functionality of setFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, setFontWeightTestDefaultValue, TestSize.Level1)
{
    auto jsonValue = GetJsonValue(node_);
    auto result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
    EXPECT_EQ(result, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE);
}

/**
 * @tc.name: setFontWeightTestValidValues
 * @tc.desc: Check the functionality of setFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, setFontWeightTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontWeight, nullptr);
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;
    for (const auto &[weight, expectValue] : Converter::FONT_WEIGHT_TEST_PLAN) {
        auto optWeight = Converter::ArkValue<Opt_Union_I32_FontWeight_String>(weight);
        modifier_->setFontWeight(node_, &optWeight);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(result, expectValue);
    }
}

/**
 * @tc.name: setFontWeightTestInvalidValues
 * @tc.desc: Check the functionality of setFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, setFontWeightTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontWeight, nullptr);
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;

    const std::vector<ArkFontWeightTest> testPlan = {
        { Converter::ArkUnion<Ark_Union_I32_FontWeight_String, Ark_Int32>(1000), "FontWeight.Normal" },
        { Converter::ArkUnion<Ark_Union_I32_FontWeight_String, Ark_String>("1000"), "FontWeight.Normal" },
    };
    for (const auto &[weight, expectValue] : testPlan) {
        auto optWeight = Converter::ArkValue<Opt_Union_I32_FontWeight_String>(weight);
        modifier_->setFontWeight(node_, &optWeight);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(result, expectValue);
    }
}

/*
 * @tc.name: setUpdateStrategyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, setUpdateStrategyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_UPDATE_STRATEGY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_UPDATE_STRATEGY_DEFAULT_VALUE);
}

/*
 * @tc.name: setUpdateStrategyTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, setUpdateStrategyTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_MarqueeUpdateStrategy inputUpdateStrategyItems;

    // Verifying attribute's  values
    inputUpdateStrategyItems = Converter::ArkValue<Ark_MarqueeUpdateStrategy>
        (ARK_MARQUEE_UPDATE_STRATEGY_PRESERVE_POSITION);
    auto optInputUpdateStrategyItems = Converter::ArkValue<Opt_MarqueeUpdateStrategy>(inputUpdateStrategyItems);
    modifier_->setMarqueeUpdateStrategy(node_, &optInputUpdateStrategyItems);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_UPDATE_STRATEGY_NAME);
    expectedStr = ATTRIBUTE_UPDATE_STRATEGY_TEST_VALUE;
    EXPECT_EQ(resultStr, expectedStr);
}

/*
 * @tc.name: setMarqueeOptionsTestDefaultValues
 * @tc.desc: Check default options values
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, setMarqueeOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STEP_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LOOP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LOOP_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SRC_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SRC_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PLAYER_STATUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLAYER_STATUS_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIRECTION_DEFAULT_VALUE);
}

/**
 * @tc.name: SetMarqueeOptionsValidTest
 * @tc.desc: Check the functionality of MarqueeModifier.SetScrollAmount
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, DISABLED_SetMarqueeOptionsValidTest, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    Ark_MarqueeOptions inputValueOptions;

    inputValueOptions.step = Converter::ArkValue<Opt_Float64>(8);
    inputValueOptions.loop = Converter::ArkValue<Opt_Int32>(3);
    inputValueOptions.src = Converter::ArkValue<Ark_String>("teststring");
    inputValueOptions.start = Converter::ArkValue<Ark_Boolean>(false);
    inputValueOptions.fromStart = Converter::ArkValue<Opt_Boolean>(true);
    // Test
    modifier_->setMarqueeOptions(node_, &inputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkStep = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_NAME);
    auto checkLoop = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LOOP_NAME);
    auto checkSrc = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SRC_NAME);
    auto checkPlayerStatus = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PLAYER_STATUS_NAME);
    auto checkDirection = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
    EXPECT_EQ(checkStep, "8.000000");
    EXPECT_EQ(checkLoop, "3");
    EXPECT_EQ(checkSrc, "teststring");
    EXPECT_EQ(checkPlayerStatus, "false");
    EXPECT_EQ(checkDirection, "true");
}
/*
 * @tc.name: setOnStartTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, DISABLED_setOnStartTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnStart, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<MarqueeEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static constexpr int32_t contextId = 123;
    static bool isCalled = false;
    auto checkCallback = [](const Ark_Int32 resourceId) {
        isCalled = true;
        EXPECT_EQ(resourceId, contextId);
    };
    // setup the callback object via C-API
    Callback_Void arkCallback = Converter::ArkValue<Callback_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    modifier_->setOnStart(node_, &optCallback);

    isCalled = false;
    eventHub->FireStartEvent();
    ASSERT_TRUE(isCalled);
}
/*
 * @tc.name: setOnBounceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, DISABLED_setOnBounceTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnBounce, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<MarqueeEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static constexpr int32_t contextId = 123;
    static bool isCalled = false;
    auto checkCallback = [](const Ark_Int32 resourceId) {
        isCalled = true;
        EXPECT_EQ(resourceId, contextId);
    };
    // setup the callback object via C-API
    Callback_Void arkCallback = Converter::ArkValue<Callback_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    modifier_->setOnBounce(node_, &optCallback);

    isCalled = false;
    eventHub->FireBounceEvent();
    ASSERT_TRUE(isCalled);
}
/*
 * @tc.name: setOnFinishTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeModifierTest, DISABLED_setOnFinishTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnFinish, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<MarqueeEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static constexpr int32_t contextId = 123;
    static bool isCalled = false;
    auto checkCallback = [](const Ark_Int32 resourceId) {
        isCalled = true;
        EXPECT_EQ(resourceId, contextId);
    };
    // setup the callback object via C-API
    Callback_Void arkCallback = Converter::ArkValue<Callback_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    modifier_->setOnFinish(node_, &optCallback);

    isCalled = false;
    eventHub->FireFinishEvent();
    ASSERT_TRUE(isCalled);
}
} // namespace OHOS::Ace::NG
