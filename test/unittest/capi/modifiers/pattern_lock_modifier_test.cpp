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
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/patternlock/patternlock_event_hub.h"
#include "core/components_v2/pattern_lock/pattern_lock_component.h"
#include "core/components_v2/pattern_lock/pattern_lock_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
const auto ATTRIBUTE_SIDE_LENGTH_NAME = "sideLength";
const auto ATTRIBUTE_SIDE_LENGTH_DEFAULT_VALUE = "288.00vp";
const auto ATTRIBUTE_CIRCLE_RADIUS_NAME = "circleRadius";
const auto ATTRIBUTE_CIRCLE_RADIUS_DEFAULT_VALUE = "6.00vp";
const auto ATTRIBUTE_BACKGROUND_COLOR_NAME = "backgroundColor";
const auto ATTRIBUTE_BACKGROUND_COLOR_DEFAULT_VALUE = "#00000000";
const auto ATTRIBUTE_REGULAR_COLOR_NAME = "regularColor";
const auto ATTRIBUTE_REGULAR_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_SELECTED_COLOR_NAME = "selectedColor";
const auto ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_ACTIVE_COLOR_NAME = "activeColor";
const auto ATTRIBUTE_ACTIVE_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_PATH_COLOR_NAME = "pathColor";
const auto ATTRIBUTE_PATH_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_AUTO_RESET_NAME = "autoReset";
const auto ATTRIBUTE_AUTO_RESET_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_SKIP_UNSELECTED_POINT = "skipUnselectedPoint";
const auto ATTRIBUTE_SKIP_UNSELECTED_POINT_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_COLOR_NAME = "activeCircleColor";
const auto ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_RADIUS_NAME = "activeCircleRadius";
const auto ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_RADIUS_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_ENABLE_WAVE_EFFECT_NAME = "enableWaveEffect";
const auto ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_ENABLE_WAVE_EFFECT_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_ENABLE_FOREGROUND_NAME = "enableForeground";
const auto ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_ENABLE_FOREGROUND_DEFAULT_VALUE = "false";

const int32_t INT_NEG = -1234;
const int32_t INT_ZERO = 0;
const int32_t INT_POS = 1234;

const auto LEN_NUM_NEG = Converter::ArkValue<Ark_Length>("-1234.00px");
const auto LEN_NUM_ZERO = Converter::ArkValue<Ark_Length>("0.00px");
const auto LEN_NUM_VALID = Converter::ArkValue<Ark_Length>("1234.00px");
const auto LEN_NUM_MAX = Converter::ArkValue<Ark_Length>("2147483648.00px");

const std::string EXPECTED_NUM_NEG_PX("-1234.00px");
const std::string EXPECTED_NUM_VILID_PX("1234.00px");
const std::string EXPECTED_NUM_MAX_PX("2147483648.00px");
const std::string EXPECTED_NUM_ZERO_PX("0.00px");

const auto RES_COLOR_NAME = NamedResourceId{"color_name", ResourceType::COLOR};
const auto RES_COLOR_ID = IntResourceId{123456, ResourceType::COLOR};

const auto COLOR_BY_STRING1 = Color(0xFF123456);
const auto COLOR_BY_NUMBER = Color(0xFF654321);
} // namespace

class PatternLockModifierTest : public ModifierTestBase<GENERATED_ArkUIPatternLockModifier,
    &GENERATED_ArkUINodeModifiers::getPatternLockModifier, GENERATED_ARKUI_PATTERN_LOCK> {
    public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        auto themeStyle = SetupThemeStyle("pattern_lock_pattern");
        themeStyle->SetAttr("side_length", { .value = V2::DEFAULT_SIDE_LENGTH });
        SetupTheme<V2::PatternLockTheme>();
        AddResource(RES_COLOR_ID, COLOR_BY_NUMBER);
        AddResource(RES_COLOR_NAME, COLOR_BY_STRING1);
    }
};

/*
 * @tc.name: setSideLengthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setSideLengthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SIDE_LENGTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SIDE_LENGTH_DEFAULT_VALUE);
}

// Valid values for attribute 'sideLength' of method 'sideLength'
static std::vector<std::tuple<std::string, Ark_Length, std::string>> sideLengthValidValues = {
    {EXPECTED_NUM_NEG_PX, LEN_NUM_NEG, EXPECTED_NUM_NEG_PX},
    {EXPECTED_NUM_ZERO_PX, LEN_NUM_ZERO, EXPECTED_NUM_ZERO_PX},
    {EXPECTED_NUM_VILID_PX, LEN_NUM_VALID, EXPECTED_NUM_VILID_PX},
    {EXPECTED_NUM_MAX_PX, LEN_NUM_MAX, EXPECTED_NUM_MAX_PX},
};

/*
 * @tc.name: setSideLengthTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, DISABLED_setSideLengthTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    for (auto [passed, checkVal, expected]: sideLengthValidValues) {
        auto optVal = Converter::ArkValue<Opt_Length>(checkVal);
        modifier_->setSideLength(node_, &optVal);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SIDE_LENGTH_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setCircleRadiusTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setCircleRadiusTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CIRCLE_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CIRCLE_RADIUS_DEFAULT_VALUE);
}

// Valid values for attribute 'circleRadius' of method 'circleRadius'
static std::vector<std::tuple<std::string, Ark_Length, std::string>> circleRadiusValidValues = {
    {EXPECTED_NUM_NEG_PX, LEN_NUM_NEG, ATTRIBUTE_CIRCLE_RADIUS_DEFAULT_VALUE},
    {"0.00px", Converter::ArkValue<Ark_Length>("0.00px"), ATTRIBUTE_CIRCLE_RADIUS_DEFAULT_VALUE},
    {EXPECTED_NUM_VILID_PX, LEN_NUM_VALID, EXPECTED_NUM_VILID_PX},
    {EXPECTED_NUM_MAX_PX, LEN_NUM_MAX, EXPECTED_NUM_MAX_PX},
};

/*
 * @tc.name: setCircleRadiusTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setCircleRadiusTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    for (auto [passed, checkVal, expected]: circleRadiusValidValues) {
        auto optVal = Converter::ArkValue<Opt_Length>(checkVal);
        modifier_->setCircleRadius(node_, &optVal);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CIRCLE_RADIUS_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setBackgroundColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setBackgroundColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BACKGROUND_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BACKGROUND_COLOR_DEFAULT_VALUE);
}

static std::vector<std::tuple<std::string, Ark_ResourceColor, std::string>> backgroundColorValidValues = {
    {COLOR_BY_STRING1.ColorToString(),
        Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_NAME)),
        COLOR_BY_STRING1.ColorToString() },
    {COLOR_BY_NUMBER.ColorToString(),
        Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_ID)),
        COLOR_BY_NUMBER.ColorToString() },
};

/*
 * @tc.name: setBackgroundColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setBackgroundColorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    for (auto [passed, checkVal, expected]: backgroundColorValidValues) {
        auto optVal = Converter::ArkValue<Opt_ResourceColor>(checkVal);
        modifier_->setBackgroundColor(node_, &optVal);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setRegularColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setRegularColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_REGULAR_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_REGULAR_COLOR_DEFAULT_VALUE);
}

// Valid values for attribute 'regularColor' of method 'regularColor'
static std::vector<std::tuple<std::string, Ark_ResourceColor, std::string>> regularColorValidValues = {
    {COLOR_BY_STRING1.ColorToString(),
        Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_NAME)),
        COLOR_BY_STRING1.ColorToString() },
    {COLOR_BY_NUMBER.ColorToString(),
        Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_ID)),
        COLOR_BY_NUMBER.ColorToString() },
};
/*
 * @tc.name: setRegularColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setRegularColorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    for (auto [passed, checkVal, expected]: regularColorValidValues) {
        auto optVal = Converter::ArkValue<Opt_ResourceColor>(checkVal);
        modifier_->setRegularColor(node_, &optVal);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_REGULAR_COLOR_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setSelectedColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setSelectedColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE);
}

// Valid values for attribute 'selectedColor' of method 'selectedColor'
static std::vector<std::tuple<std::string, Ark_ResourceColor, std::string>> selectedColorValidValues = {
    {COLOR_BY_STRING1.ColorToString(),
        Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_NAME)),
        COLOR_BY_STRING1.ColorToString() },
    {COLOR_BY_NUMBER.ColorToString(),
        Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_ID)),
        COLOR_BY_NUMBER.ColorToString() },
};

/*
 * @tc.name: setSelectedColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setSelectedColorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    for (auto [passed, checkVal, expected]: selectedColorValidValues) {
        auto optVal = Converter::ArkValue<Opt_ResourceColor>(checkVal);
        modifier_->setSelectedColor(node_, &optVal);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setActiveColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setActiveColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ACTIVE_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ACTIVE_COLOR_DEFAULT_VALUE);
}

// Valid values for attribute 'activeColor' of method 'activeColor'
static std::vector<std::tuple<std::string, Ark_ResourceColor, std::string>> activeColorValidValues = {
    {COLOR_BY_STRING1.ColorToString(),
        Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_NAME)),
        COLOR_BY_STRING1.ColorToString() },
    {COLOR_BY_NUMBER.ColorToString(),
        Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_ID)),
        COLOR_BY_NUMBER.ColorToString() },
};
/*
 * @tc.name: setActiveColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setActiveColorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    for (auto [passed, checkVal, expected]: activeColorValidValues) {
        auto optVal = Converter::ArkValue<Opt_ResourceColor>(checkVal);
        modifier_->setActiveColor(node_, &optVal);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ACTIVE_COLOR_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setPathColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setPathColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PATH_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PATH_COLOR_DEFAULT_VALUE);
}

// Valid values for attribute 'pathColor' of method 'pathColor'
static std::vector<std::tuple<std::string, Ark_ResourceColor, std::string>> pathColorValidValues = {
    {COLOR_BY_STRING1.ColorToString(),
        Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_NAME)),
        COLOR_BY_STRING1.ColorToString() },
    {COLOR_BY_NUMBER.ColorToString(),
        Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_ID)),
        COLOR_BY_NUMBER.ColorToString() },
};
/*
 * @tc.name: setPathColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setPathColorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    for (auto [passed, checkVal, expected]: pathColorValidValues) {
        auto optVal = Converter::ArkValue<Opt_ResourceColor>(checkVal);
        modifier_->setPathColor(node_, &optVal);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PATH_COLOR_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setAutoResetTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setAutoResetTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_RESET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_AUTO_RESET_DEFAULT_VALUE);
}

// Valid values for attribute 'autoReset' of method 'autoReset'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> autoResetValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setAutoResetTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setAutoResetTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    for (auto [passed, checkVal, expected]: autoResetValidValues) {
        auto optVal = Converter::ArkValue<Opt_Boolean>(checkVal);
        modifier_->setAutoReset(node_, &optVal);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_RESET_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setSkipUnselectedPointTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setSkipUnselectedPointTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SKIP_UNSELECTED_POINT);
    EXPECT_EQ(resultStr, ATTRIBUTE_SKIP_UNSELECTED_POINT_DEFAULT_VALUE);
}

/*
 * @tc.name: setSkipUnselectedPointTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setSkipUnselectedPointTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    for (auto [passed, checkVal, expected]: autoResetValidValues) {
        auto optVal = Converter::ArkValue<Opt_Boolean>(checkVal);
        modifier_->setSkipUnselectedPoint(node_, &optVal);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SKIP_UNSELECTED_POINT);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setOnPatternCompleteTest
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, SetOnPatternCompleteTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<PatternLockEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        std::vector<int32_t> input;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onPatternComplete = [](Ark_Int32 nodeId, const Array_Int32 input) {
        checkEvent = {
            .nodeId = nodeId,
            .input = Converter::Convert<std::vector<int32_t>>(input),
        };
    };

    Callback_Array_I32_Void callBackValue = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onPatternComplete
    };

    auto test = [this, &callBackValue, eventHub, frameNode](const std::vector<int> testVec) {
        checkEvent = std::nullopt;
        auto event = V2::PatternCompleteEvent(testVec);
        auto optVal = Converter::ArkValue<Opt_Callback_Array_I32_Void>(callBackValue);
        modifier_->setOnPatternComplete(node_, &optVal);
        EXPECT_FALSE(checkEvent.has_value());
        eventHub->UpdateCompleteEvent(&event);
        ASSERT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
        EXPECT_EQ(checkEvent->input.size(), testVec.size());
        for (int i = 0; i < testVec.size(); i++) {
            EXPECT_EQ(checkEvent->input[i], testVec[i]);
        }
    };
    std::vector<int32_t> vec = {INT_NEG, INT_ZERO, INT_POS};
    test(vec);
}

/*
 * @tc.name: setOnDotConnectTest
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, SetOnDotConnectTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<PatternLockEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        int32_t code;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onDotConnect = [](Ark_Int32 nodeId, const Ark_Int32 code) {
        checkEvent = {
            .nodeId = nodeId,
            .code = Converter::Convert<int32_t>(code),
        };
    };

    Callback_I32_Void callBackValue = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onDotConnect
    };

    auto test = [this, &callBackValue, eventHub, frameNode](const int32_t testValue) {
        checkEvent = std::nullopt;
        auto optVal = Converter::ArkValue<Opt_Callback_I32_Void>(callBackValue);
        modifier_->setOnDotConnect(node_, &optVal);
        EXPECT_FALSE(checkEvent.has_value());
        eventHub->UpdateDotConnectEvent(testValue);
        ASSERT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
        EXPECT_EQ(checkEvent->code, testValue);
    };
    test(INT_NEG);
    test(INT_ZERO);
    test(INT_POS);
}

/*
 * @tc.name: setActivateCircleStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setActivateCircleStyleTestDefaultValues, TestSize.Level1)
{
    std::string resultStr;
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_COLOR_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_RADIUS_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue,
        ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_ENABLE_WAVE_EFFECT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_ENABLE_WAVE_EFFECT_DEFAULT_VALUE);
    resultStr = GetAttrValue<std::string>(jsonValue,
        ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_ENABLE_FOREGROUND_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_ENABLE_FOREGROUND_DEFAULT_VALUE);
}

// Valid values for attribute 'color' of method 'activateCircleStyle'
static std::vector<std::tuple<std::string, Opt_ResourceColor, std::string>> styleColorValidValues = {
    {"\"#123456\"", Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#123456"), "#FF123456"},
    {"0x11223344", Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0x11223344), "#11223344"},
    {"-1", Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(-1), "#FFFFFFFF"},
};

// Valid values for attribute 'radius' of method 'activateCircleStyle'
using LengthMetrictsTestStep = std::pair<Ark_LengthMetrics, std::string>;
static const std::vector<LengthMetrictsTestStep> LENGTH_METRICS_ANY_TEST_PLAN = {
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_PX, 1.f), "1.00px" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_PX, 0.f), "0.00px" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_VP, 2.45f), "2.45vp" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_VP, -7.f), "-7.00vp" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_FP, -65.5f), "-65.50fp" },
};

// Valid values for attribute 'enableWaveEffect' of method 'activateCircleStyle'
static std::vector<std::tuple<std::string, Opt_Boolean, std::string>> styleEnableWaveEffectValidValues = {
    {"true", Converter::ArkValue<Opt_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Opt_Boolean>(false), "false"},
};

/*
 * @tc.name: setActivateCircleStyleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest, setActivateCircleStyleTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultJsonOptions;
    std::string resultStr;
    Opt_CircleStyleOptions realInputValue = Converter::ArkValue<Opt_CircleStyleOptions>(Ark_CircleStyleOptions{});

    for (auto [passed, checkVal, expected]: styleColorValidValues) {
        realInputValue.value.color = checkVal;
        modifier_->setActivateCircleStyle(node_, &realInputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_COLOR_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }

    for (auto [passed, checkVal, expected]: styleEnableWaveEffectValidValues) {
        realInputValue.value.enableWaveEffect = checkVal;
        realInputValue.value.enableForeground = checkVal;
        modifier_->setActivateCircleStyle(node_, &realInputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue,
            ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_ENABLE_WAVE_EFFECT_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
        resultStr = GetAttrValue<std::string>(jsonValue,
            ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_ENABLE_FOREGROUND_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }

    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        realInputValue.value.radius = Converter::ArkValue<Opt_LengthMetrics>(lenMetrics);
        modifier_->setActivateCircleStyle(node_, &realInputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue,
            ATTRIBUTE_ACTIVATE_CIRCLE_STYLE_OPTIONS_RADIUS_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << expected;
    }
}
} // namespace OHOS::Ace::NG
