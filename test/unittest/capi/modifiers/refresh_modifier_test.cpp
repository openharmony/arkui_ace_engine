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
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_REFRESH_OFFSET_NAME = "refreshOffset";
    const auto ATTRIBUTE_REFRESH_OFFSET_DEFAULT_VALUE = "0.00vp";
    const auto ATTRIBUTE_PULL_TO_REFRESH_NAME = "pullToRefresh";
    const auto ATTRIBUTE_PULL_TO_REFRESH_DEFAULT_VALUE = "true";
    const auto ATTRIBUTE_PULL_DOWN_RATIO_RATIO_NAME = "pullDownRatio";
    const auto ATTRIBUTE_PULL_DOWN_RATIO_RATIO_DEFAULT_VALUE = "";
} // namespace

class RefreshModifierTest : public ModifierTestBase<
    GENERATED_ArkUIRefreshModifier,
    &GENERATED_ArkUINodeModifiers::getRefreshModifier,
    GENERATED_ARKUI_REFRESH
> {
};

/*
 * @tc.name: DISABLED_setOnStateChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, DISABLED_setOnStateChangeTest, TestSize.Level1)
{
}

/*
 * @tc.name: DISABLED_setOnRefreshingTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, DISABLED_setOnRefreshingTest, TestSize.Level1)
{
}

/*
 * @tc.name: setRefreshOffsetTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, setRefreshOffsetTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_REFRESH_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_REFRESH_OFFSET_DEFAULT_VALUE);
}

// Valid values for attribute 'refreshOffset' of method 'refreshOffset'
static std::vector<std::tuple<std::string, Ark_Number, std::string>> refreshOffsetRefreshOffsetValidValues = {
    { "-1", Converter::ArkValue<Ark_Number>(-1), "-1.00vp" },
    { "0", Converter::ArkValue<Ark_Number>(0), "0.00vp" },
    { "1", Converter::ArkValue<Ark_Number>(1), "1.00vp" },
    { "10", Converter::ArkValue<Ark_Number>(10), "10.00vp" },
    { "50", Converter::ArkValue<Ark_Number>(50), "50.00vp" },
};

/*
 * @tc.name: setRefreshOffsetTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, setRefreshOffsetTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Number inputValueRefreshOffset;
    Ark_Number initValueRefreshOffset;

    // Initial setup
    initValueRefreshOffset = std::get<1>(refreshOffsetRefreshOffsetValidValues[0]);

    // Verifying attribute's  values
    inputValueRefreshOffset = initValueRefreshOffset;
    for (auto&& value: refreshOffsetRefreshOffsetValidValues) {
        inputValueRefreshOffset = std::get<1>(value);
        modifier_->setRefreshOffset(node_, &inputValueRefreshOffset);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_REFRESH_OFFSET_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setPullToRefreshTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, setPullToRefreshTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PULL_TO_REFRESH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PULL_TO_REFRESH_DEFAULT_VALUE);
}

// Valid values for attribute 'pullToRefresh' of method 'pullToRefresh'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> pullToRefreshPullToRefreshValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setPullToRefreshTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, setPullToRefreshTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValuePullToRefresh;
    Ark_Boolean initValuePullToRefresh;

    // Initial setup
    initValuePullToRefresh = std::get<1>(pullToRefreshPullToRefreshValidValues[0]);

    // Verifying attribute's  values
    inputValuePullToRefresh = initValuePullToRefresh;
    for (auto&& value: pullToRefreshPullToRefreshValidValues) {
        inputValuePullToRefresh = std::get<1>(value);
        modifier_->setPullToRefresh(node_, inputValuePullToRefresh);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PULL_TO_REFRESH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: DISABLED_setOnOffsetChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, DISABLED_setOnOffsetChangeTest, TestSize.Level1)
{
}

/*
 * @tc.name: setPullDownRatioTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, setPullDownRatioTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PULL_DOWN_RATIO_RATIO_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PULL_DOWN_RATIO_RATIO_DEFAULT_VALUE);
}

// Valid values for attribute 'pullDownRatioRatio' of method 'pullDownRatio'
static std::vector<std::tuple<std::string, Opt_Number, double>> pullDownRatioPullDownRatioRatioValidValues = {
    { "0", Converter::ArkValue<Opt_Number>(0), 0 },
    { "0.5", Converter::ArkValue<Opt_Number>(0.5f), 0.5 },
    { "1", Converter::ArkValue<Opt_Number>(1), 1 },
    { "-20", Converter::ArkValue<Opt_Number>(-20), -20 },
    { "12.4", Converter::ArkValue<Opt_Number>(12.4f), 12.4 },
    { "22.5", Converter::ArkValue<Opt_Number>(22.5f), 22.5 },
};

/*
 * @tc.name: setPullDownRatioTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
#ifdef WRONG_OPT
HWTEST_F(RefreshModifierTest, setPullDownRatioTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    double result;
    double expected;
    Opt_Number initValuePullDownRatioRatio;
    Opt_Number inputValuePullDownRatioRatio;

    // Initial setup
    initValuePullDownRatioRatio = std::get<1>(pullDownRatioPullDownRatioRatioValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: pullDownRatioPullDownRatioRatioValidValues) {
        inputValuePullDownRatioRatio = std::get<1>(value);
        modifier_->setPullDownRatio(node_, &inputValuePullDownRatioRatio);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<double>(jsonValue, ATTRIBUTE_PULL_DOWN_RATIO_RATIO_NAME);
        expected = std::get<2>(value);
        EXPECT_FLOAT_EQ(result, expected);
    }

    // Verifying Ark_Empty value
    inputValuePullDownRatioRatio = Converter::ArkValue<Opt_Number>(Ark_Empty());
    modifier_->setPullDownRatio(node_, &inputValuePullDownRatioRatio);
    jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PULL_DOWN_RATIO_RATIO_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PULL_DOWN_RATIO_RATIO_DEFAULT_VALUE);
}
#endif
} // namespace OHOS::Ace::NG
