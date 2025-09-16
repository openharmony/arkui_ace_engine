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
 * @tc.name: setEnableHapticFeedbackTestEnableHapticFeedbackInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setEnableHapticFeedbackTestEnableHapticFeedbackInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableHapticFeedback;

    // Initial setup
    initValueEnableHapticFeedback = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableHapticFeedback](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableHapticFeedback = initValueEnableHapticFeedback;

        modifier_->setEnableHapticFeedback(node_, &inputValueEnableHapticFeedback);
        inputValueEnableHapticFeedback = value;
        modifier_->setEnableHapticFeedback(node_, &inputValueEnableHapticFeedback);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEnableHapticFeedback, attribute: enableHapticFeedback";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setShowTipsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setShowTipsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_TIPS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_TIPS_DEFAULT_VALUE) << "Default value for attribute 'showTips'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_DEFAULT_VALUE) << "Default value for attribute 'content'";
}

/*
 * @tc.name: setShowTipsTestShowTipsValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setShowTipsTestShowTipsValidValues, TestSize.Level1)
{
    Opt_Boolean initValueShowTips;
    Opt_ResourceStr initValueContent;

    // Initial setup
    initValueShowTips = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueContent = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueShowTips, &initValueContent](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueShowTips = initValueShowTips;
        Opt_ResourceStr inputValueContent = initValueContent;

        inputValueShowTips = value;
        modifier_->setShowTips(node_, &inputValueShowTips, &inputValueContent);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_TIPS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setShowTips, attribute: showTips";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setShowTipsTestShowTipsInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setShowTipsTestShowTipsInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueShowTips;
    Opt_ResourceStr initValueContent;

    // Initial setup
    initValueShowTips = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueContent = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueShowTips, &initValueContent](
                          const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueShowTips = initValueShowTips;
        Opt_ResourceStr inputValueContent = initValueContent;

        modifier_->setShowTips(node_, &inputValueShowTips, &inputValueContent);
        inputValueShowTips = value;
        modifier_->setShowTips(node_, &inputValueShowTips, &inputValueContent);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_TIPS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_TIPS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setShowTips, attribute: showTips";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setShowTipsTestContentValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setShowTipsTestContentValidValues, TestSize.Level1)
{
    Opt_Boolean initValueShowTips;
    Opt_ResourceStr initValueContent;

    // Initial setup
    initValueShowTips = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueContent = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueShowTips, &initValueContent](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceStr& value) {
        Opt_Boolean inputValueShowTips = initValueShowTips;
        Opt_ResourceStr inputValueContent = initValueContent;

        inputValueContent = value;
        modifier_->setShowTips(node_, &inputValueShowTips, &inputValueContent);
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
    Opt_Boolean initValueShowTips;
    Opt_ResourceStr initValueContent;

    // Initial setup
    initValueShowTips = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueContent = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueShowTips, &initValueContent](
                          const std::string& input, const Opt_ResourceStr& value) {
        Opt_Boolean inputValueShowTips = initValueShowTips;
        Opt_ResourceStr inputValueContent = initValueContent;

        modifier_->setShowTips(node_, &inputValueShowTips, &inputValueContent);
        inputValueContent = value;
        modifier_->setShowTips(node_, &inputValueShowTips, &inputValueContent);
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
