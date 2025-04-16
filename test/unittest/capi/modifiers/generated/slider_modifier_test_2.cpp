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

#include "slider_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::Slider;
/*
 * @tc.name: setShowTipsTestContentValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setShowTipsTestContentValidValues, TestSize.Level1)
{
    Ark_Boolean initValueShowTips;
    Opt_ResourceStr initValueContent;

    // Initial setup
    initValueShowTips = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    initValueContent = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueShowTips, &initValueContent](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceStr& value) {
        Ark_Boolean inputValueShowTips = initValueShowTips;
        Opt_ResourceStr inputValueContent = initValueContent;

        inputValueContent = value;
        modifier_->setShowTips(node_, inputValueShowTips, &inputValueContent);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setShowTips, attribute: content";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setShowTipsTestContentInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setShowTipsTestContentInvalidValues, TestSize.Level1)
{
    Ark_Boolean initValueShowTips;
    Opt_ResourceStr initValueContent;

    // Initial setup
    initValueShowTips = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    initValueContent = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueShowTips, &initValueContent](
                          const std::string& input, const Opt_ResourceStr& value) {
        Ark_Boolean inputValueShowTips = initValueShowTips;
        Opt_ResourceStr inputValueContent = initValueContent;

        modifier_->setShowTips(node_, inputValueShowTips, &inputValueContent);
        inputValueContent = value;
        modifier_->setShowTips(node_, inputValueShowTips, &inputValueContent);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setShowTips, attribute: content";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceStr, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceStr>());
}
} // namespace OHOS::Ace::NG
