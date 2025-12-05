/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/pattern/scrollable/scrollable_theme.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_NESTED_SCROLL_NAME = "nestedScroll";
const auto ATTRIBUTE_EDGE_EFFECT_NAME = "edgeEffect";
const auto ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_NAME = "options";
const auto ATTRIBUTE_FADING_EDGE_OPTION_NAME = "fadingEdgeOption";
const auto ATTRIBUTE_SCROLL_BAR_NAME = "scrollBar";
const auto ATTRIBUTE_SCROLL_BAR_DEFAULT_VALUE = "BarState.Off";
const auto ATTRIBUTE_SCROLL_BAR_COLOR_NAME = "scrollBarColor";
const auto ATTRIBUTE_SCROLL_BAR_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_SCROLL_BAR_WIDTH_NAME = "scrollBarWidth";
const auto ATTRIBUTE_SCROLL_BAR_WIDTH_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME = "scrollForward";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_DEFAULT_VALUE = "NestedScrollMode.SELF_ONLY";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME = "scrollBackward";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_DEFAULT_VALUE = "NestedScrollMode.SELF_ONLY";
const auto ATTRIBUTE_ENABLE_SCROLL_INTERACTION_NAME = "enableScrollInteraction";
const auto ATTRIBUTE_ENABLE_SCROLL_INTERACTION_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_FRICTION_NAME = "friction";
const auto ATTRIBUTE_FRICTION_DEFAULT_VALUE = "0.75";
const auto ATTRIBUTE_FLING_SPEED_LIMIT_NAME = "flingSpeedLimit";
const auto ATTRIBUTE_FLING_SPEED_LIMIT_DEFAULT_VALUE = "9000.00vp";
const auto ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_NAME = "digitalCrownSensitivity";
const auto ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_BACK_TO_TOP_NAME = "backToTop";
const auto ATTRIBUTE_BACK_TO_TOP_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_EDGE_EFFECT_I_EDGE_EFFECT_NAME = "edgeEffect";
const auto ATTRIBUTE_EDGE_EFFECT_I_EDGE_EFFECT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_I_ALWAYS_ENABLED_NAME = "alwaysEnabled";
const auto ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_I_ALWAYS_ENABLED_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_I_EFFECT_EDGE_NAME = "effectEdge";
const auto ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_I_EFFECT_EDGE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FADING_EDGE_NAME = "fadingEdge";
const auto ATTRIBUTE_FADING_EDGE_DEFAULT_VALUE = "false";
} // namespace

class ScrollableCommonMethodModifierTest
    : public ModifierTestBase<GENERATED_ArkUIScrollableCommonMethodModifier,
          &GENERATED_ArkUINodeModifiers::getScrollableCommonMethodModifier, GENERATED_ARKUI_SCROLLABLE_COMMON_METHOD>,
      public testing::WithParamInterface<int> {
public:
    void* CreateNodeImpl() override
    {
        typedef void* (*ConstructFunc)(Ark_Int32, Ark_Int32);
        const ConstructFunc constructors[] = {
            nodeModifiers_->getGridModifier()->construct,
            nodeModifiers_->getListModifier()->construct,
            nodeModifiers_->getScrollModifier()->construct,
            nodeModifiers_->getWaterFlowModifier()->construct,
        };
        if (GetParam() < std::size(constructors)) {
            return constructors[GetParam()](GetId(), 0);
        }
        return nullptr;
    }

    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<ScrollBarTheme>();
        SetupTheme<ScrollableTheme>();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

INSTANTIATE_TEST_SUITE_P(Tests, ScrollableCommonMethodModifierTest, testing::Range(0, 4));

/*
 * @tc.name: setScrollBarTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, DISABLED_setScrollBarTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SCROLL_BAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SCROLL_BAR_DEFAULT_VALUE) << "Default value for attribute 'scrollBar'";
}

/*
 * @tc.name: setScrollBarTestScrollBarValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setScrollBarTestScrollBarValidValues, TestSize.Level1)
{
    Opt_BarState initValueScrollBar;

    // Initial setup
    initValueScrollBar = ArkValue<Opt_BarState>(std::get<1>(Fixtures::testFixtureEnumBarStateValidValues[0]));

    auto checkValue = [this, &initValueScrollBar](
                          const std::string& input, const std::string& expectedStr, const Opt_BarState& value) {
        Opt_BarState inputValueScrollBar = initValueScrollBar;

        inputValueScrollBar = value;
        modifier_->setScrollBar(node_, &inputValueScrollBar);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SCROLL_BAR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setScrollBar, attribute: scrollBar";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumBarStateValidValues) {
        checkValue(input, expected, ArkValue<Opt_BarState>(value));
    }
}

/*
 * @tc.name: setScrollBarTestScrollBarInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, DISABLED_setScrollBarTestScrollBarInvalidValues, TestSize.Level1)
{
    Opt_BarState initValueScrollBar;

    // Initial setup
    initValueScrollBar = ArkValue<Opt_BarState>(std::get<1>(Fixtures::testFixtureEnumBarStateValidValues[0]));

    auto checkValue = [this, &initValueScrollBar](const std::string& input, const Opt_BarState& value) {
        Opt_BarState inputValueScrollBar = initValueScrollBar;

        modifier_->setScrollBar(node_, &inputValueScrollBar);
        inputValueScrollBar = value;
        modifier_->setScrollBar(node_, &inputValueScrollBar);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SCROLL_BAR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SCROLL_BAR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setScrollBar, attribute: scrollBar";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumBarStateInvalidValues) {
        checkValue(input, ArkValue<Opt_BarState>(value));
    }
}

/*
 * @tc.name: setScrollBarColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setScrollBarColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SCROLL_BAR_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SCROLL_BAR_COLOR_DEFAULT_VALUE) << "Default value for attribute 'scrollBarColor'";
}

/*
 * @tc.name: setScrollBarColorTestScrollBarColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, DISABLED_setScrollBarColorTestScrollBarColorValidValues, TestSize.Level1)
{
    Opt_Union_Color_Number_String initValueScrollBarColor;

    // Initial setup
    initValueScrollBarColor =
        ArkUnion<Opt_Union_Color_Number_String, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueScrollBarColor](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Color_Number_String& value) {
        Opt_Union_Color_Number_String inputValueScrollBarColor = initValueScrollBarColor;

        inputValueScrollBarColor = value;
        modifier_->setScrollBarColor(node_, &inputValueScrollBarColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SCROLL_BAR_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setScrollBarColor, attribute: scrollBarColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Color_Number_String, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Color_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Color_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setScrollBarColorTestScrollBarColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setScrollBarColorTestScrollBarColorInvalidValues, TestSize.Level1)
{
    Opt_Union_Color_Number_String initValueScrollBarColor;

    // Initial setup
    initValueScrollBarColor =
        ArkUnion<Opt_Union_Color_Number_String, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueScrollBarColor](
                          const std::string& input, const Opt_Union_Color_Number_String& value) {
        Opt_Union_Color_Number_String inputValueScrollBarColor = initValueScrollBarColor;

        modifier_->setScrollBarColor(node_, &inputValueScrollBarColor);
        inputValueScrollBarColor = value;
        modifier_->setScrollBarColor(node_, &inputValueScrollBarColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SCROLL_BAR_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SCROLL_BAR_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setScrollBarColor, attribute: scrollBarColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_Number_String, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_Number_String, Ark_arkui_component_enums_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Color_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Color_Number_String>());
}

/*
 * @tc.name: setScrollBarWidthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setScrollBarWidthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SCROLL_BAR_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SCROLL_BAR_WIDTH_DEFAULT_VALUE) << "Default value for attribute 'scrollBarWidth'";
}

/*
 * @tc.name: setScrollBarWidthTestScrollBarWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setScrollBarWidthTestScrollBarWidthValidValues, TestSize.Level1)
{
    Opt_Union_Number_String initValueScrollBarWidth;

    // Initial setup
    initValueScrollBarWidth = ArkUnion<Opt_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueScrollBarWidth](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_String& value) {
        Opt_Union_Number_String inputValueScrollBarWidth = initValueScrollBarWidth;

        inputValueScrollBarWidth = value;
        modifier_->setScrollBarWidth(node_, &inputValueScrollBarWidth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SCROLL_BAR_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setScrollBarWidth, attribute: scrollBarWidth";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setScrollBarWidthTestScrollBarWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setScrollBarWidthTestScrollBarWidthInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_String initValueScrollBarWidth;

    // Initial setup
    initValueScrollBarWidth = ArkUnion<Opt_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueScrollBarWidth](const std::string& input, const Opt_Union_Number_String& value) {
        Opt_Union_Number_String inputValueScrollBarWidth = initValueScrollBarWidth;

        modifier_->setScrollBarWidth(node_, &inputValueScrollBarWidth);
        inputValueScrollBarWidth = value;
        modifier_->setScrollBarWidth(node_, &inputValueScrollBarWidth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SCROLL_BAR_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SCROLL_BAR_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setScrollBarWidth, attribute: scrollBarWidth";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_String>());
}

/*
 * @tc.name: setNestedScrollTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setNestedScrollTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultNestedScroll =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_DEFAULT_VALUE) <<
        "Default value for attribute 'nestedScroll.scrollForward'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_DEFAULT_VALUE) <<
        "Default value for attribute 'nestedScroll.scrollBackward'";
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollForwardValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setNestedScrollTestNestedScrollScrollForwardValidValues, TestSize.Level1)
{
    Opt_NestedScrollOptions initValueNestedScroll;

    // Initial setup
    WriteTo(initValueNestedScroll).scrollForward = std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteTo(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const std::string& expectedStr, const Ark_NestedScrollMode& value) {
        Opt_NestedScrollOptions inputValueNestedScroll = initValueNestedScroll;

        WriteTo(inputValueNestedScroll).scrollForward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll.scrollForward";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollForwardInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setNestedScrollTestNestedScrollScrollForwardInvalidValues, TestSize.Level1)
{
    Opt_NestedScrollOptions initValueNestedScroll;

    // Initial setup
    WriteTo(initValueNestedScroll).scrollForward = std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteTo(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Ark_NestedScrollMode& value) {
        Opt_NestedScrollOptions inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        WriteTo(inputValueNestedScroll).scrollForward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll.scrollForward";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollBackwardValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setNestedScrollTestNestedScrollScrollBackwardValidValues, TestSize.Level1)
{
    Opt_NestedScrollOptions initValueNestedScroll;

    // Initial setup
    WriteTo(initValueNestedScroll).scrollForward = std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteTo(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const std::string& expectedStr, const Ark_NestedScrollMode& value) {
        Opt_NestedScrollOptions inputValueNestedScroll = initValueNestedScroll;

        WriteTo(inputValueNestedScroll).scrollBackward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll.scrollBackward";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollBackwardInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(
    ScrollableCommonMethodModifierTest, setNestedScrollTestNestedScrollScrollBackwardInvalidValues, TestSize.Level1)
{
    Opt_NestedScrollOptions initValueNestedScroll;

    // Initial setup
    WriteTo(initValueNestedScroll).scrollForward = std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteTo(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Ark_NestedScrollMode& value) {
        Opt_NestedScrollOptions inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        WriteTo(inputValueNestedScroll).scrollBackward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll.scrollBackward";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setEnableScrollInteractionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setEnableScrollInteractionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_SCROLL_INTERACTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_SCROLL_INTERACTION_DEFAULT_VALUE) <<
        "Default value for attribute 'enableScrollInteraction'";
}

/*
 * @tc.name: setEnableScrollInteractionTestEnableScrollInteractionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setEnableScrollInteractionTestEnableScrollInteractionValidValues,
    TestSize.Level1)
{
    Opt_Boolean initValueEnableScrollInteraction;

    // Initial setup
    initValueEnableScrollInteraction = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableScrollInteraction](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableScrollInteraction = initValueEnableScrollInteraction;

        inputValueEnableScrollInteraction = value;
        modifier_->setEnableScrollInteraction(node_, &inputValueEnableScrollInteraction);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_SCROLL_INTERACTION_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input <<
                                          ", method: setEnableScrollInteraction, attribute: enableScrollInteraction";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setEnableScrollInteractionTestEnableScrollInteractionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setEnableScrollInteractionTestEnableScrollInteractionInvalidValues,
    TestSize.Level1)
{
    Opt_Boolean initValueEnableScrollInteraction;

    // Initial setup
    initValueEnableScrollInteraction = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableScrollInteraction](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableScrollInteraction = initValueEnableScrollInteraction;

        modifier_->setEnableScrollInteraction(node_, &inputValueEnableScrollInteraction);
        inputValueEnableScrollInteraction = value;
        modifier_->setEnableScrollInteraction(node_, &inputValueEnableScrollInteraction);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_SCROLL_INTERACTION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_SCROLL_INTERACTION_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setEnableScrollInteraction, attribute: enableScrollInteraction";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setFrictionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, DISABLED_setFrictionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FRICTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FRICTION_DEFAULT_VALUE) << "Default value for attribute 'friction'";
}

/*
 * @tc.name: setFrictionTestFrictionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setFrictionTestFrictionValidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueFriction;

    // Initial setup
    initValueFriction = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureScrollableFrictionNumValidValues[0]));

    auto checkValue = [this, &initValueFriction](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_Resource& value) {
        Opt_Union_Number_Resource inputValueFriction = initValueFriction;

        inputValueFriction = value;
        modifier_->setFriction(node_, &inputValueFriction);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FRICTION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFriction, attribute: friction";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureScrollableFrictionNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureScrollableFrictionResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setFrictionTestFrictionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setFrictionTestFrictionInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueFriction;

    // Initial setup
    initValueFriction = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureScrollableFrictionNumValidValues[0]));

    auto checkValue = [this, &initValueFriction](const std::string& input, const Opt_Union_Number_Resource& value) {
        Opt_Union_Number_Resource inputValueFriction = initValueFriction;

        modifier_->setFriction(node_, &inputValueFriction);
        inputValueFriction = value;
        modifier_->setFriction(node_, &inputValueFriction);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FRICTION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FRICTION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFriction, attribute: friction";
    };

    for (auto& [input, value] : Fixtures::testFixtureScrollableFrictionNumInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureScrollableFrictionResInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource>());
}

/*
 * @tc.name: setFlingSpeedLimitTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setFlingSpeedLimitTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FLING_SPEED_LIMIT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FLING_SPEED_LIMIT_DEFAULT_VALUE) << "Default value for attribute 'flingSpeedLimit'";
}

/*
 * @tc.name: setFlingSpeedLimitTestFlingSpeedLimitValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setFlingSpeedLimitTestFlingSpeedLimitValidValues, TestSize.Level1)
{
    Opt_Number initValueFlingSpeedLimit;

    // Initial setup
    initValueFlingSpeedLimit = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureFlingSpeedLimitValidValues[0]));

    auto checkValue = [this, &initValueFlingSpeedLimit](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Number inputValueFlingSpeedLimit = initValueFlingSpeedLimit;

        inputValueFlingSpeedLimit = value;
        modifier_->setFlingSpeedLimit(node_, &inputValueFlingSpeedLimit);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FLING_SPEED_LIMIT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFlingSpeedLimit, attribute: flingSpeedLimit";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFlingSpeedLimitValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setFlingSpeedLimitTestFlingSpeedLimitInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(
    ScrollableCommonMethodModifierTest, DISABLED_setFlingSpeedLimitTestFlingSpeedLimitInvalidValues, TestSize.Level1)
{
    Opt_Number initValueFlingSpeedLimit;

    // Initial setup
    initValueFlingSpeedLimit = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureFlingSpeedLimitValidValues[0]));

    auto checkValue = [this, &initValueFlingSpeedLimit](const std::string& input, const Opt_Number& value) {
        Opt_Number inputValueFlingSpeedLimit = initValueFlingSpeedLimit;

        modifier_->setFlingSpeedLimit(node_, &inputValueFlingSpeedLimit);
        inputValueFlingSpeedLimit = value;
        modifier_->setFlingSpeedLimit(node_, &inputValueFlingSpeedLimit);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FLING_SPEED_LIMIT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FLING_SPEED_LIMIT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFlingSpeedLimit, attribute: flingSpeedLimit";
    };

    for (auto& [input, value] : Fixtures::testFixtureFlingSpeedLimitInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setDigitalCrownSensitivityTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, DISABLED_setDigitalCrownSensitivityTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE) <<
        "Default value for attribute 'digitalCrownSensitivity'";
}

/*
 * @tc.name: setDigitalCrownSensitivityTestDigitalCrownSensitivityValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, DISABLED_setDigitalCrownSensitivityTestDigitalCrownSensitivityValidValues,
    TestSize.Level1)
{
    Opt_CrownSensitivity initValueDigitalCrownSensitivity;

    // Initial setup
    initValueDigitalCrownSensitivity =
        ArkValue<Opt_CrownSensitivity>(std::get<1>(Fixtures::testFixtureEnumCrownSensitivityValidValues[0]));

    auto checkValue = [this, &initValueDigitalCrownSensitivity](
                          const std::string& input, const std::string& expectedStr, const Opt_CrownSensitivity& value) {
        Opt_CrownSensitivity inputValueDigitalCrownSensitivity = initValueDigitalCrownSensitivity;

        inputValueDigitalCrownSensitivity = value;
        modifier_->setDigitalCrownSensitivity(node_, &inputValueDigitalCrownSensitivity);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input <<
                                          ", method: setDigitalCrownSensitivity, attribute: digitalCrownSensitivity";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumCrownSensitivityValidValues) {
        checkValue(input, expected, ArkValue<Opt_CrownSensitivity>(value));
    }
}

/*
 * @tc.name: setDigitalCrownSensitivityTestDigitalCrownSensitivityInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest,
    DISABLED_setDigitalCrownSensitivityTestDigitalCrownSensitivityInvalidValues, TestSize.Level1)
{
    Opt_CrownSensitivity initValueDigitalCrownSensitivity;

    // Initial setup
    initValueDigitalCrownSensitivity =
        ArkValue<Opt_CrownSensitivity>(std::get<1>(Fixtures::testFixtureEnumCrownSensitivityValidValues[0]));

    auto checkValue = [this, &initValueDigitalCrownSensitivity](
                          const std::string& input, const Opt_CrownSensitivity& value) {
        Opt_CrownSensitivity inputValueDigitalCrownSensitivity = initValueDigitalCrownSensitivity;

        modifier_->setDigitalCrownSensitivity(node_, &inputValueDigitalCrownSensitivity);
        inputValueDigitalCrownSensitivity = value;
        modifier_->setDigitalCrownSensitivity(node_, &inputValueDigitalCrownSensitivity);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setDigitalCrownSensitivity, attribute: digitalCrownSensitivity";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumCrownSensitivityInvalidValues) {
        checkValue(input, ArkValue<Opt_CrownSensitivity>(value));
    }
}

/*
 * @tc.name: setBackToTopTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, DISABLED_setBackToTopTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BACK_TO_TOP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BACK_TO_TOP_DEFAULT_VALUE) << "Default value for attribute 'backToTop'";
}

/*
 * @tc.name: setBackToTopTestBackToTopValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, DISABLED_setBackToTopTestBackToTopValidValues, TestSize.Level1)
{
    Opt_Boolean initValueBackToTop;

    // Initial setup
    initValueBackToTop = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueBackToTop](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueBackToTop = initValueBackToTop;

        inputValueBackToTop = value;
        modifier_->setBackToTop(node_, &inputValueBackToTop);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BACK_TO_TOP_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBackToTop, attribute: backToTop";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setBackToTopTestBackToTopInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, DISABLED_setBackToTopTestBackToTopInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueBackToTop;

    // Initial setup
    initValueBackToTop = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueBackToTop](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueBackToTop = initValueBackToTop;

        modifier_->setBackToTop(node_, &inputValueBackToTop);
        inputValueBackToTop = value;
        modifier_->setBackToTop(node_, &inputValueBackToTop);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BACK_TO_TOP_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BACK_TO_TOP_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBackToTop, attribute: backToTop";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setEdgeEffectTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, DISABLED_setEdgeEffectTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultEdgeEffect =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_EDGE_EFFECT_NAME);
    std::unique_ptr<JsonValue> resultOptions =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultEdgeEffect, ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultEdgeEffect, ATTRIBUTE_EDGE_EFFECT_I_EDGE_EFFECT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_EDGE_EFFECT_I_EDGE_EFFECT_DEFAULT_VALUE) <<
        "Default value for attribute 'edgeEffect.edgeEffect'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_I_ALWAYS_ENABLED_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_I_ALWAYS_ENABLED_DEFAULT_VALUE) <<
        "Default value for attribute 'edgeEffect.options.alwaysEnabled'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_I_EFFECT_EDGE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_I_EFFECT_EDGE_DEFAULT_VALUE) <<
        "Default value for attribute 'edgeEffect.options.effectEdge'";
}

/*
 * @tc.name: setEdgeEffectTestEdgeEffectEdgeEffectValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, DISABLED_setEdgeEffectTestEdgeEffectEdgeEffectValidValues, TestSize.Level1)
{
    Opt_EdgeEffect initValueEdgeEffect;
    Opt_EdgeEffectOptions initValueOptions;

    // Initial setup
    initValueEdgeEffect = ArkValue<Opt_EdgeEffect>(std::get<1>(Fixtures::testFixtureEnumEdgeEffectValidValues[0]));
    WriteTo(initValueOptions).alwaysEnabled = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueOptions).effectEdge =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueEdgeEffect, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_EdgeEffect& value) {
        Opt_EdgeEffect inputValueEdgeEffect = initValueEdgeEffect;
        Opt_EdgeEffectOptions inputValueOptions = initValueOptions;

        inputValueEdgeEffect = value;
        modifier_->setEdgeEffect(node_, &inputValueEdgeEffect, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultEdgeEffect = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_EDGE_EFFECT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultEdgeEffect, ATTRIBUTE_EDGE_EFFECT_I_EDGE_EFFECT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEdgeEffect, attribute: edgeEffect.edgeEffect";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumEdgeEffectValidValues) {
        checkValue(input, expected, ArkValue<Opt_EdgeEffect>(value));
    }
}

/*
 * @tc.name: setEdgeEffectTestEdgeEffectEdgeEffectInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(
    ScrollableCommonMethodModifierTest, DISABLED_setEdgeEffectTestEdgeEffectEdgeEffectInvalidValues, TestSize.Level1)
{
    Opt_EdgeEffect initValueEdgeEffect;
    Opt_EdgeEffectOptions initValueOptions;

    // Initial setup
    initValueEdgeEffect = ArkValue<Opt_EdgeEffect>(std::get<1>(Fixtures::testFixtureEnumEdgeEffectValidValues[0]));
    WriteTo(initValueOptions).alwaysEnabled = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueOptions).effectEdge =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueEdgeEffect, &initValueOptions](
                          const std::string& input, const Opt_EdgeEffect& value) {
        Opt_EdgeEffect inputValueEdgeEffect = initValueEdgeEffect;
        Opt_EdgeEffectOptions inputValueOptions = initValueOptions;

        modifier_->setEdgeEffect(node_, &inputValueEdgeEffect, &inputValueOptions);
        inputValueEdgeEffect = value;
        modifier_->setEdgeEffect(node_, &inputValueEdgeEffect, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultEdgeEffect = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_EDGE_EFFECT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultEdgeEffect, ATTRIBUTE_EDGE_EFFECT_I_EDGE_EFFECT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_EDGE_EFFECT_I_EDGE_EFFECT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEdgeEffect, attribute: edgeEffect.edgeEffect";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumEdgeEffectInvalidValues) {
        checkValue(input, ArkValue<Opt_EdgeEffect>(value));
    }
}

/*
 * @tc.name: setEdgeEffectTestEdgeEffectOptionsAlwaysEnabledValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, DISABLED_setEdgeEffectTestEdgeEffectOptionsAlwaysEnabledValidValues,
    TestSize.Level1)
{
    Opt_EdgeEffect initValueEdgeEffect;
    Opt_EdgeEffectOptions initValueOptions;

    // Initial setup
    initValueEdgeEffect = ArkValue<Opt_EdgeEffect>(std::get<1>(Fixtures::testFixtureEnumEdgeEffectValidValues[0]));
    WriteTo(initValueOptions).alwaysEnabled = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueOptions).effectEdge =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueEdgeEffect, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Opt_EdgeEffect inputValueEdgeEffect = initValueEdgeEffect;
        Opt_EdgeEffectOptions inputValueOptions = initValueOptions;

        WriteTo(inputValueOptions).alwaysEnabled = value;
        modifier_->setEdgeEffect(node_, &inputValueEdgeEffect, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultEdgeEffect = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_EDGE_EFFECT_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultEdgeEffect, ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultOptions, ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_I_ALWAYS_ENABLED_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEdgeEffect, attribute: edgeEffect.options.alwaysEnabled";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setEdgeEffectTestEdgeEffectOptionsEffectEdgeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, DISABLED_setEdgeEffectTestEdgeEffectOptionsEffectEdgeValidValues,
    TestSize.Level1)
{
    Opt_EdgeEffect initValueEdgeEffect;
    Opt_EdgeEffectOptions initValueOptions;

    // Initial setup
    initValueEdgeEffect = ArkValue<Opt_EdgeEffect>(std::get<1>(Fixtures::testFixtureEnumEdgeEffectValidValues[0]));
    WriteTo(initValueOptions).alwaysEnabled = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueOptions).effectEdge =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueEdgeEffect, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_EdgeEffect inputValueEdgeEffect = initValueEdgeEffect;
        Opt_EdgeEffectOptions inputValueOptions = initValueOptions;

        WriteTo(inputValueOptions).effectEdge = value;
        modifier_->setEdgeEffect(node_, &inputValueEdgeEffect, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultEdgeEffect = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_EDGE_EFFECT_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultEdgeEffect, ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_I_EFFECT_EDGE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEdgeEffect, attribute: edgeEffect.options.effectEdge";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setEdgeEffectTestEdgeEffectOptionsEffectEdgeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, DISABLED_setEdgeEffectTestEdgeEffectOptionsEffectEdgeInvalidValues,
    TestSize.Level1)
{
    Opt_EdgeEffect initValueEdgeEffect;
    Opt_EdgeEffectOptions initValueOptions;

    // Initial setup
    initValueEdgeEffect = ArkValue<Opt_EdgeEffect>(std::get<1>(Fixtures::testFixtureEnumEdgeEffectValidValues[0]));
    WriteTo(initValueOptions).alwaysEnabled = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueOptions).effectEdge =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueEdgeEffect, &initValueOptions](
                          const std::string& input, const Opt_Number& value) {
        Opt_EdgeEffect inputValueEdgeEffect = initValueEdgeEffect;
        Opt_EdgeEffectOptions inputValueOptions = initValueOptions;

        modifier_->setEdgeEffect(node_, &inputValueEdgeEffect, &inputValueOptions);
        WriteTo(inputValueOptions).effectEdge = value;
        modifier_->setEdgeEffect(node_, &inputValueEdgeEffect, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultEdgeEffect = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_EDGE_EFFECT_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultEdgeEffect, ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_I_EFFECT_EDGE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_EDGE_EFFECT_I_OPTIONS_I_EFFECT_EDGE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEdgeEffect, attribute: edgeEffect.options.effectEdge";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setFadingEdgeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setFadingEdgeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultFadingEdgeOption =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FADING_EDGE_OPTION_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FADING_EDGE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FADING_EDGE_DEFAULT_VALUE) << "Default value for attribute 'fadingEdge'";
}

/*
 * @tc.name: setFadingEdgeTestFadingEdgeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setFadingEdgeTestFadingEdgeValidValues, TestSize.Level1)
{
    Opt_Boolean initValueFadingEdge;
    Opt_FadingEdgeOptions initValueFadingEdgeOption;

    // Initial setup
    initValueFadingEdge = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFadingEdge, &initValueFadingEdgeOption](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueFadingEdge = initValueFadingEdge;
        Opt_FadingEdgeOptions inputValueFadingEdgeOption = initValueFadingEdgeOption;

        inputValueFadingEdge = value;
        modifier_->setFadingEdge(node_, &inputValueFadingEdge, &inputValueFadingEdgeOption);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FADING_EDGE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFadingEdge, attribute: fadingEdge";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setFadingEdgeTestFadingEdgeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest, setFadingEdgeTestFadingEdgeInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueFadingEdge;
    Opt_FadingEdgeOptions initValueFadingEdgeOption;

    // Initial setup
    initValueFadingEdge = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFadingEdge, &initValueFadingEdgeOption](
                          const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueFadingEdge = initValueFadingEdge;
        Opt_FadingEdgeOptions inputValueFadingEdgeOption = initValueFadingEdgeOption;

        modifier_->setFadingEdge(node_, &inputValueFadingEdge, &inputValueFadingEdgeOption);
        inputValueFadingEdge = value;
        modifier_->setFadingEdge(node_, &inputValueFadingEdge, &inputValueFadingEdgeOption);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FADING_EDGE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FADING_EDGE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFadingEdge, attribute: fadingEdge";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}
} // namespace OHOS::Ace::NG
