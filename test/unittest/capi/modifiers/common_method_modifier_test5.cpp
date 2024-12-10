/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "common_method_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const auto ATTRIBUTE_LINEAR_GRADIENT_BLUR_NAME = "linearGradientBlur";
    const auto ATTRIBUTE_LINEAR_GRADIENT_BLUR_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_SYSTEM_BAR_EFFECT_NAME = "systemBarEffect";
    const auto ATTRIBUTE_SYSTEM_BAR_EFFECT_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_BLEND_MODE_NAME = "blendMode";
    const auto ATTRIBUTE_BLEND_MODE_DEFAULT_VALUE = "0";
}
namespace Converter {
    template<>
    Array_FractionStop ArkValue(const std::vector<std::pair<float, float>>& fractionStopValue)
    {
        Array_FractionStop arr;
        arr.length = fractionStopValue.size();
        arr.array = new Ark_FractionStop[arr.length];
        for (auto i = 0; i < fractionStopValue.size(); ++i) {
            arr.array[i].value0 = ArkValue<Ark_Number>(fractionStopValue[i].first);
            arr.array[i].value1 = ArkValue<Ark_Number>(fractionStopValue[i].second);
        }
        return arr;
    }
    template<>
    void AssignArkValue(Opt_BlendApplyType& dst, const BlendApplyType& src)
    {
        Ark_BlendApplyType arkDst;
        switch (src) {
            case BlendApplyType::FAST: arkDst = ARK_BLEND_APPLY_TYPE_FAST; break;
            case BlendApplyType::OFFSCREEN: arkDst = ARK_BLEND_APPLY_TYPE_OFFSCREEN; break;
            default:
                arkDst = ARK_BLEND_APPLY_TYPE_FAST;
        }
        dst = ArkValue<Opt_BlendApplyType>(arkDst);
    }
}

class CommonMethodModifierTest5 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    RefPtr<RenderContext> render_;
};

/*
 * @tc.name: setLinearGradientBlurTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest5, setLinearGradientBlurTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_LINEAR_GRADIENT_BLUR_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_LINEAR_GRADIENT_BLUR_DEFAULT_VALUE);
}

/*
 * @tc.name: setLinearGradientBlurTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest5, setLinearGradientBlurTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLinearGradientBlur, nullptr);
    using OneTestStep = std::tuple<Ark_Number, Ark_LinearGradientBlurOptions, std::string>;
    std::vector<std::pair<float, float>> val1 = {{1.1f, 2.2f}, {3.3f, 4.4f}, {5.5f, 6.6f}};
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Number>(12), {
            .direction = Ark_GradientDirection::ARK_GRADIENT_DIRECTION_BOTTOM,
            .fractionStops = Converter::ArkValue<Array_FractionStop>(val1)},
            "{\"value\":\"12.00vp\",\"options\":{\"direction\":\"BOTTOM\","
            "\"fractionStops\":[\"1.100000,2.200000\",\"3.300000,4.400000\",\"5.500000,6.600000\"]}}"},
    };
    auto freeArray = [](Array_FractionStop& arr) {
        delete[] arr.array;
        arr.array = nullptr;
        arr.length = 0;
    };
    for (auto [inputValueNum, inputValueGradient, expectedValue]: testPlan) {
        modifier_->setLinearGradientBlur(node_, &inputValueNum, &inputValueGradient);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_LINEAR_GRADIENT_BLUR_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
        freeArray(inputValueGradient.fractionStops);
    }
}

/*
 * @tc.name: setLinearGradientBlurTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest5, setLinearGradientBlurTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLinearGradientBlur, nullptr);
    modifier_->setLinearGradientBlur(node_, nullptr, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_LINEAR_GRADIENT_BLUR_NAME);
    EXPECT_EQ(resultValue, ATTRIBUTE_LINEAR_GRADIENT_BLUR_DEFAULT_VALUE)
        << "Passed value is: " << ATTRIBUTE_LINEAR_GRADIENT_BLUR_DEFAULT_VALUE;
}

/*
 * @tc.name: setSystemBarEffectTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest5, setSystemBarEffectTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_SYSTEM_BAR_EFFECT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SYSTEM_BAR_EFFECT_DEFAULT_VALUE);
}

/*
 * @tc.name: setSystemBarEffectTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest5, DISABLED_setSystemBarEffectTestValidValues, TestSize.Level1)
{
    LOGE("The `SetSystemBarEffect` modifier not implemented.");
}

/*
 * @tc.name: setSystemBarEffectTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest5, DISABLED_setSystemBarEffectTestInvalidValues, TestSize.Level1)
{
    LOGE("The `SetSystemBarEffect` modifier not implemented.");
}

/*
 * @tc.name: setBlendModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest5, setBlendModeTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_BLEND_MODE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_BLEND_MODE_DEFAULT_VALUE);
}

/*
 * @tc.name: setBlendModeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest5, setBlendModeTestValidValues1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBlendMode, nullptr);
    using OneTestStep = std::tuple<Ark_BlendMode, Opt_BlendApplyType, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Ark_BlendMode::ARK_BLEND_MODE_NONE, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST),
            ATTRIBUTE_BLEND_MODE_DEFAULT_VALUE},
        {Ark_BlendMode::ARK_BLEND_MODE_CLEAR, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "1"},
        {Ark_BlendMode::ARK_BLEND_MODE_SRC, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "2"},
        {Ark_BlendMode::ARK_BLEND_MODE_DST, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "3"},
        {Ark_BlendMode::ARK_BLEND_MODE_SRC_OVER, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "4"},
        {Ark_BlendMode::ARK_BLEND_MODE_DST_OVER, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "5"},
        {Ark_BlendMode::ARK_BLEND_MODE_SRC_IN, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "6"},
        {Ark_BlendMode::ARK_BLEND_MODE_DST_IN, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "7"},
        {Ark_BlendMode::ARK_BLEND_MODE_SRC_OUT, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "8"},
        {Ark_BlendMode::ARK_BLEND_MODE_DST_OUT, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "9"},
        {Ark_BlendMode::ARK_BLEND_MODE_SRC_ATOP, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "10"},
        {Ark_BlendMode::ARK_BLEND_MODE_DST_ATOP, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "11"},
        {Ark_BlendMode::ARK_BLEND_MODE_XOR, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "12"},
        {Ark_BlendMode::ARK_BLEND_MODE_PLUS, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "13"},
        {Ark_BlendMode::ARK_BLEND_MODE_MODULATE, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "14"},
        {Ark_BlendMode::ARK_BLEND_MODE_SCREEN, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "15"},
        {Ark_BlendMode::ARK_BLEND_MODE_OVERLAY, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "16"},
        {Ark_BlendMode::ARK_BLEND_MODE_DARKEN, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "17"},
        {Ark_BlendMode::ARK_BLEND_MODE_LIGHTEN, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "18"},
        {Ark_BlendMode::ARK_BLEND_MODE_COLOR_DODGE, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST),
            "19"},
        {Ark_BlendMode::ARK_BLEND_MODE_COLOR_BURN, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "20"},
        {Ark_BlendMode::ARK_BLEND_MODE_HARD_LIGHT, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "21"},
        {Ark_BlendMode::ARK_BLEND_MODE_SOFT_LIGHT, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "22"},
        {Ark_BlendMode::ARK_BLEND_MODE_DIFFERENCE, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "23"},
        {Ark_BlendMode::ARK_BLEND_MODE_EXCLUSION, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "24"},
        {Ark_BlendMode::ARK_BLEND_MODE_MULTIPLY, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "25"},
        {Ark_BlendMode::ARK_BLEND_MODE_SCREEN, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "15"},
    };
    for (auto [inputValueMode, inputValueType, expectedValue]: testPlan) {
        modifier_->setBlendMode(node_, inputValueMode, &inputValueType);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_BLEND_MODE_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setBlendModeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest5, setBlendModeTestValidValues2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBlendMode, nullptr);
    using OneTestStep = std::tuple<Ark_BlendMode, Opt_BlendApplyType, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Ark_BlendMode::ARK_BLEND_MODE_NONE, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX),
            ATTRIBUTE_BLEND_MODE_DEFAULT_VALUE},
        {Ark_BlendMode::ARK_BLEND_MODE_CLEAR, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "1"},
        {Ark_BlendMode::ARK_BLEND_MODE_SRC, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "2"},
        {Ark_BlendMode::ARK_BLEND_MODE_DST, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "3"},
        {Ark_BlendMode::ARK_BLEND_MODE_SRC_OVER, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "4"},
        {Ark_BlendMode::ARK_BLEND_MODE_DST_OVER, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "5"},
        {Ark_BlendMode::ARK_BLEND_MODE_SRC_IN, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "6"},
        {Ark_BlendMode::ARK_BLEND_MODE_DST_IN, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "7"},
        {Ark_BlendMode::ARK_BLEND_MODE_SRC_OUT, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "8"},
        {Ark_BlendMode::ARK_BLEND_MODE_DST_OUT, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "9"},
        {Ark_BlendMode::ARK_BLEND_MODE_SRC_ATOP, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "10"},
        {Ark_BlendMode::ARK_BLEND_MODE_DST_ATOP, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "11"},
        {Ark_BlendMode::ARK_BLEND_MODE_XOR, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "12"},
        {Ark_BlendMode::ARK_BLEND_MODE_PLUS, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "13"},
        {Ark_BlendMode::ARK_BLEND_MODE_MODULATE, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "14"},
        {Ark_BlendMode::ARK_BLEND_MODE_SCREEN, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "15"},
        {Ark_BlendMode::ARK_BLEND_MODE_OVERLAY, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "16"},
        {Ark_BlendMode::ARK_BLEND_MODE_DARKEN, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "17"},
        {Ark_BlendMode::ARK_BLEND_MODE_LIGHTEN, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "18"},
        {Ark_BlendMode::ARK_BLEND_MODE_COLOR_DODGE, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX),
            "19"},
        {Ark_BlendMode::ARK_BLEND_MODE_COLOR_BURN, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "20"},
        {Ark_BlendMode::ARK_BLEND_MODE_HARD_LIGHT, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "21"},
        {Ark_BlendMode::ARK_BLEND_MODE_SOFT_LIGHT, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "22"},
        {Ark_BlendMode::ARK_BLEND_MODE_DIFFERENCE, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "23"},
        {Ark_BlendMode::ARK_BLEND_MODE_EXCLUSION, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "24"},
        {Ark_BlendMode::ARK_BLEND_MODE_MULTIPLY, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "25"},
        {Ark_BlendMode::ARK_BLEND_MODE_SCREEN, Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::MAX), "15"},
    };
    for (auto [inputValueMode, inputValueType, expectedValue]: testPlan) {
        modifier_->setBlendMode(node_, inputValueMode, &inputValueType);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_BLEND_MODE_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

HWTEST_F(CommonMethodModifierTest5, setBlendModeTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBlendMode, nullptr);
    using OneTestStep = std::tuple<Ark_BlendMode, Opt_BlendApplyType, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {static_cast<Ark_BlendMode>(-1), Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "0"},
        {static_cast<Ark_BlendMode>(999), Converter::ArkValue<Opt_BlendApplyType>(BlendApplyType::FAST), "0"},
    };
    for (const auto& [blendMode, applyType, expectedValue] : testPlan) {
        modifier_->setBlendMode(node_, blendMode, &applyType);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_BLEND_MODE_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Invalid value should not change the blend mode";
    }
}
}
