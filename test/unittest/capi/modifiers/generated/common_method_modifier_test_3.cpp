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

#include "common_method_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::CommonMethod;
/*
 * @tc.name: setRenderFit0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRenderFit0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_FIT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RENDER_FIT_DEFAULT_VALUE) << "Default value for attribute 'renderFit'";
}

/*
 * @tc.name: setRenderFit0TestRenderFitValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRenderFit0TestRenderFitValidValues, TestSize.Level1)
{
    Ark_RenderFit initValueRenderFit;

    // Initial setup
    initValueRenderFit = std::get<1>(Fixtures::testFixtureEnumRenderFitValidValues[0]);

    auto checkValue = [this, &initValueRenderFit](
                          const std::string& input, const std::string& expectedStr, const Ark_RenderFit& value) {
        Ark_RenderFit inputValueRenderFit = initValueRenderFit;

        inputValueRenderFit = value;
        modifier_->setRenderFit0(node_, inputValueRenderFit);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_FIT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRenderFit0, attribute: renderFit";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumRenderFitValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setRenderFit0TestRenderFitInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRenderFit0TestRenderFitInvalidValues, TestSize.Level1)
{
    Ark_RenderFit initValueRenderFit;

    // Initial setup
    initValueRenderFit = std::get<1>(Fixtures::testFixtureEnumRenderFitValidValues[0]);

    auto checkValue = [this, &initValueRenderFit](const std::string& input, const Ark_RenderFit& value) {
        Ark_RenderFit inputValueRenderFit = initValueRenderFit;

        modifier_->setRenderFit0(node_, inputValueRenderFit);
        inputValueRenderFit = value;
        modifier_->setRenderFit0(node_, inputValueRenderFit);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_FIT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RENDER_FIT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRenderFit0, attribute: renderFit";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumRenderFitInvalidValues) {
        checkValue(input, value);
    }
}
} // namespace OHOS::Ace::NG
