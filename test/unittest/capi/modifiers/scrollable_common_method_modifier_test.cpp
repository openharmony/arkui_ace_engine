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
#include "test/unittest/capi/modifiers/generated/test_fixtures.h"
#include "test/unittest/capi/modifiers/generated/type_helpers.h"

#include "core/components/scroll/scroll_bar_theme.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_EDGE_EFFECT_NAME = "edgeEffect";
const auto ATTRIBUTE_EDGE_EFFECT_DEFAULT_VALUE = "EdgeEffect.None";
const auto ATTRIBUTE_EDGE_EFFECT_OPTIONS_NAME = "edgeEffectOptions";
const auto ATTRIBUTE_EDGE_EFFECT_OPTIONS_ALWAYS_ENABLED_NAME = "alwaysEnabled";
const auto ATTRIBUTE_EDGE_EFFECT_OPTIONS_ALWAYS_ENABLED_DEFAULT_VALUE = "false";
} // namespace

class ScrollableCommonMethodModifierTest
    : public ModifierTestBase<GENERATED_ArkUIScrollableCommonMethodModifier,
          &GENERATED_ArkUINodeModifiers::getScrollableCommonMethodModifier, GENERATED_ARKUI_WATER_FLOW> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<ScrollBarTheme>();
    }
};

/*
 * @tc.name: setEdgeEffectTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCommonMethodModifierTest, setEdgeEffectTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultOptions =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_EDGE_EFFECT_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_EDGE_EFFECT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_EDGE_EFFECT_DEFAULT_VALUE)
        << "Default value for attribute 'edgeEffect.edgeEffect'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_EDGE_EFFECT_OPTIONS_ALWAYS_ENABLED_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_EDGE_EFFECT_OPTIONS_ALWAYS_ENABLED_DEFAULT_VALUE)
        << "Default value for attribute 'edgeEffect.edgeEffectOptions.alwaysEnabled'";
}

/*
 * @tc.name: setEdgeEffectTestEdgeEffectEdgeEffectValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCommonMethodModifierTest, setEdgeEffectTestEdgeEffectEdgeEffectValidValues, TestSize.Level1)
{
    Ark_EdgeEffect initValueEdgeEffect;
    Opt_EdgeEffectOptions initValueOptions;

    // Initial setup
    initValueEdgeEffect = std::get<1>(Fixtures::testFixtureEnumEdgeEffectValidValues[0]);
    WriteTo(initValueOptions).alwaysEnabled = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEdgeEffect, &initValueOptions](
                          const std::string& input, const Ark_EdgeEffect& value, const std::string& expectedStr) {
        Ark_EdgeEffect inputValueEdgeEffect = initValueEdgeEffect;
        Opt_EdgeEffectOptions inputValueOptions = initValueOptions;

        inputValueEdgeEffect = value;
        modifier_->setEdgeEffect(node_, inputValueEdgeEffect, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_EDGE_EFFECT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setEdgeEffect, attribute: edgeEffect.edgeEffect";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumEdgeEffectValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setEdgeEffectTestEdgeEffectEdgeEffectInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    ScrollableCommonMethodModifierTest, setEdgeEffectTestEdgeEffectEdgeEffectInvalidValues, TestSize.Level1)
{
    Ark_EdgeEffect initValueEdgeEffect;
    Opt_EdgeEffectOptions initValueOptions;

    // Initial setup
    initValueEdgeEffect = std::get<1>(Fixtures::testFixtureEnumEdgeEffectValidValues[0]);
    WriteTo(initValueOptions).alwaysEnabled = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEdgeEffect, &initValueOptions](
                          const std::string& input, const Ark_EdgeEffect& value) {
        Ark_EdgeEffect inputValueEdgeEffect = initValueEdgeEffect;
        Opt_EdgeEffectOptions inputValueOptions = initValueOptions;

        modifier_->setEdgeEffect(node_, inputValueEdgeEffect, &inputValueOptions);
        inputValueEdgeEffect = value;
        modifier_->setEdgeEffect(node_, inputValueEdgeEffect, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_EDGE_EFFECT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_EDGE_EFFECT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setEdgeEffect, attribute: edgeEffect.edgeEffect";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumEdgeEffectInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setEdgeEffectTestEdgeEffectOptionsAlwaysEnabledValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCommonMethodModifierTest, setEdgeEffectTestEdgeEffectOptionsAlwaysEnabledValidValues,
    TestSize.Level1)
{
    Ark_EdgeEffect initValueEdgeEffect;
    Opt_EdgeEffectOptions initValueOptions;

    // Initial setup
    initValueEdgeEffect = std::get<1>(Fixtures::testFixtureEnumEdgeEffectValidValues[0]);
    WriteTo(initValueOptions).alwaysEnabled = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEdgeEffect, &initValueOptions](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_EdgeEffect inputValueEdgeEffect = initValueEdgeEffect;
        Opt_EdgeEffectOptions inputValueOptions = initValueOptions;

        WriteTo(inputValueOptions).alwaysEnabled = value;
        modifier_->setEdgeEffect(node_, inputValueEdgeEffect, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_EDGE_EFFECT_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultOptions, ATTRIBUTE_EDGE_EFFECT_OPTIONS_ALWAYS_ENABLED_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setEdgeEffect, attribute: edgeEffect.options.alwaysEnabled";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}
} // namespace OHOS::Ace::NG
