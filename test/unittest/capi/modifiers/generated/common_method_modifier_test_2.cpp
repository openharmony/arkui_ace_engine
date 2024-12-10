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

#include "common_method_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::CommonMethod;
/*
 * @tc.name: setAlignRules1TestAlignRulesBiasHorizontalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesBiasHorizontalValidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.bias).horizontal = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBias = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BIAS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.bias.horizontal";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesBiasHorizontalInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesBiasHorizontalInvalidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Opt_Number& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        WriteTo(inputValueAlignRules.bias).horizontal = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBias = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BIAS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.bias.horizontal";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setAlignRules1TestAlignRulesBiasVerticalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesBiasVerticalValidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.bias).vertical = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBias = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BIAS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.bias.vertical";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesBiasVerticalInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesBiasVerticalInvalidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Opt_Number& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        WriteTo(inputValueAlignRules.bias).vertical = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBias = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BIAS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.bias.vertical";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setDragPreviewTestDragPreviewDragItemInfoExtraInfoValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(
    CommonMethodModifierTest, DISABLED_setDragPreviewTestDragPreviewDragItemInfoExtraInfoValidValues, TestSize.Level1)
{
    Ark_Union_CustomBuilder_DragItemInfo_String initValueDragPreview;

    // Initial setup
    WriteToUnion<Ark_DragItemInfo>(initValueDragPreview).extraInfo =
        ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueDragPreview](
                          const std::string& input, const std::string& expectedStr, const Opt_String& value) {
        Ark_Union_CustomBuilder_DragItemInfo_String inputValueDragPreview = initValueDragPreview;

        WriteToUnion<Ark_DragItemInfo>(inputValueDragPreview).extraInfo = value;
        modifier_->setDragPreview(node_, &inputValueDragPreview);
        auto jsonValue = GetJsonValue(node_);
        auto resultDragPreview = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DRAG_PREVIEW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDragPreview, ATTRIBUTE_DRAG_PREVIEW_I_EXTRA_INFO_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDragPreview, attribute: dragPreview.DragItemInfo.extraInfo";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkValue<Opt_String>(value));
    }
}

/*
 * @tc.name: setDragPreviewTestDragPreviewDragItemInfoExtraInfoInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(
    CommonMethodModifierTest, DISABLED_setDragPreviewTestDragPreviewDragItemInfoExtraInfoInvalidValues, TestSize.Level1)
{
    Ark_Union_CustomBuilder_DragItemInfo_String initValueDragPreview;

    // Initial setup
    WriteToUnion<Ark_DragItemInfo>(initValueDragPreview).extraInfo =
        ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueDragPreview](const std::string& input, const Opt_String& value) {
        Ark_Union_CustomBuilder_DragItemInfo_String inputValueDragPreview = initValueDragPreview;

        modifier_->setDragPreview(node_, &inputValueDragPreview);
        WriteToUnion<Ark_DragItemInfo>(inputValueDragPreview).extraInfo = value;
        modifier_->setDragPreview(node_, &inputValueDragPreview);
        auto jsonValue = GetJsonValue(node_);
        auto resultDragPreview = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DRAG_PREVIEW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDragPreview, ATTRIBUTE_DRAG_PREVIEW_I_EXTRA_INFO_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DRAG_PREVIEW_I_EXTRA_INFO_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setDragPreview, attribute: dragPreview.DragItemInfo.extraInfo";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_String>());
}
} // namespace OHOS::Ace::NG
