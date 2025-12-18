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
#include "core/interfaces/native/implementation/draw_modifier_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const auto ATTRIBUTE_LINEAR_GRADIENT_BLUR_NAME = "linearGradientBlur";
    const auto ATTRIBUTE_LINEAR_GRADIENT_BLUR_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_SYSTEM_BAR_EFFECT_NAME = "systemBarEffect";
    const auto ATTRIBUTE_SYSTEM_BAR_EFFECT_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_SYSTEM_BAR_EFFECT_TRUE_VALUE = "true";
    const auto ATTRIBUTE_BLEND_MODE_NAME = "blendMode";
    const auto ATTRIBUTE_BLEND_MODE_DEFAULT_VALUE = "0";

    struct FractionStop {
        float first;
        float second;
    };
    void AssignArkValue(Ark_FractionStop& dst, const FractionStop& fractionStopValue)
    {
        dst.value0 = Converter::ArkValue<Ark_Float64>(fractionStopValue.first);
        dst.value1 = Converter::ArkValue<Ark_Float64>(fractionStopValue.second);
    }
}

class CommonMethodModifierTest5 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    RefPtr<RenderContext> render_;

    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }
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
    using OneTestStep = std::tuple<Opt_Float64, Opt_LinearGradientBlurOptions, std::string>;
    std::vector<FractionStop> val1 = {{1.1f, 2.2f}, {3.3f, 4.4f}, {5.5f, 6.6f}};
    Converter::ArkArrayHolder<Array_FractionStop> frac(val1);
    Array_FractionStop fractions = frac.ArkValue();
    static const std::vector<OneTestStep> testPlan = {
        {
            Converter::ArkValue<Opt_Float64>(12),
            Converter::ArkValue<Opt_LinearGradientBlurOptions>(Ark_LinearGradientBlurOptions {
                .direction = Converter::ArkValue<Opt_GradientDirection>(ARK_GRADIENT_DIRECTION_BOTTOM),
                .fractionStops = Converter::ArkValue<Opt_Array_FractionStop>(fractions)
            }),
            "{\"value\":\"12.00vp\",\"options\":{\"direction\":\"BOTTOM\","
            "\"fractionStops\":[\"1.100000,2.200000\",\"3.300000,4.400000\",\"5.500000,6.600000\"]}}"
        },
    };
    for (auto [inputValueNum, inputValueGradient, expectedValue]: testPlan) {
        modifier_->setLinearGradientBlur(node_, &inputValueNum, &inputValueGradient);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_LINEAR_GRADIENT_BLUR_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setLinearGradientBlurTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest5, DISABLED_setLinearGradientBlurTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLinearGradientBlur, nullptr);
    modifier_->setLinearGradientBlur(node_, nullptr, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_LINEAR_GRADIENT_BLUR_NAME);
    EXPECT_EQ(resultValue, ATTRIBUTE_LINEAR_GRADIENT_BLUR_DEFAULT_VALUE)
        << "Passed value is: nullptr";
}

/*
 * @tc.name: setSystemBarEffectTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest5, setSystemBarEffectTestDefaultValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSystemBarEffect, nullptr);
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_SYSTEM_BAR_EFFECT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SYSTEM_BAR_EFFECT_DEFAULT_VALUE);
}

/*
 * @tc.name: setSystemBarEffectTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest5, setSystemBarEffectTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSystemBarEffect, nullptr);
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_SYSTEM_BAR_EFFECT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SYSTEM_BAR_EFFECT_DEFAULT_VALUE);

    modifier_->setSystemBarEffect(node_);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SYSTEM_BAR_EFFECT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SYSTEM_BAR_EFFECT_TRUE_VALUE);
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
    using OneTestStep = std::tuple<Opt_BlendMode, Opt_BlendApplyType, std::string>;
    auto blendType = Converter::ArkValue<Opt_BlendApplyType>(ARK_BLEND_APPLY_TYPE_FAST);
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_CLEAR), blendType, "1"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_SRC), blendType, "2"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_DST), blendType, "3"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_SRC_OVER), blendType, "4"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_DST_OVER), blendType, "5"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_SRC_IN), blendType, "6"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_DST_IN), blendType, "7"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_SRC_OUT), blendType, "8"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_DST_OUT), blendType, "9"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_SRC_ATOP), blendType, "10"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_DST_ATOP), blendType, "11"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_XOR), blendType, "12"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_PLUS), blendType, "13"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_MODULATE), blendType, "14"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_SCREEN), blendType, "15"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_OVERLAY), blendType, "16"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_DARKEN), blendType, "17"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_LIGHTEN), blendType, "18"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_COLOR_DODGE), blendType, "19"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_COLOR_BURN), blendType, "20"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_HARD_LIGHT), blendType, "21"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_SOFT_LIGHT), blendType, "22"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_DIFFERENCE), blendType, "23"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_EXCLUSION), blendType, "24"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_MULTIPLY), blendType, "25"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_SCREEN), blendType, "15"},
    };
    for (auto [inputValueMode, inputValueType, expectedValue]: testPlan) {
        modifier_->setBlendMode(node_, &inputValueMode, &inputValueType);
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
    using OneTestStep = std::tuple<Opt_BlendMode, Opt_BlendApplyType, std::string>;
    auto blendType = Converter::ArkValue<Opt_BlendApplyType>(ARK_BLEND_APPLY_TYPE_OFFSCREEN);
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_CLEAR), blendType, "1"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_SRC), blendType, "2"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_DST), blendType, "3"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_SRC_OVER), blendType, "4"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_DST_OVER), blendType, "5"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_SRC_IN), blendType, "6"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_DST_IN), blendType, "7"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_SRC_OUT), blendType, "8"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_DST_OUT), blendType, "9"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_SRC_ATOP), blendType, "10"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_DST_ATOP), blendType, "11"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_XOR), blendType, "12"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_PLUS), blendType, "13"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_MODULATE), blendType, "14"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_SCREEN), blendType, "15"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_OVERLAY), blendType, "16"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_DARKEN), blendType, "17"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_LIGHTEN), blendType, "18"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_COLOR_DODGE), blendType, "19"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_COLOR_BURN), blendType, "20"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_HARD_LIGHT), blendType, "21"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_SOFT_LIGHT), blendType, "22"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_DIFFERENCE), blendType, "23"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_EXCLUSION), blendType, "24"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_MULTIPLY), blendType, "25"},
        {Converter::ArkValue<Opt_BlendMode>(ARK_BLEND_MODE_SCREEN), blendType, "15"},
    };
    for (auto [inputValueMode, inputValueType, expectedValue]: testPlan) {
        modifier_->setBlendMode(node_, &inputValueMode, &inputValueType);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_BLEND_MODE_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

HWTEST_F(CommonMethodModifierTest5, setBlendModeTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBlendMode, nullptr);
    using OneTestStep = std::tuple<Opt_BlendMode, Opt_BlendApplyType, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_BlendMode>(static_cast<Ark_BlendMode>(-1)),
            Converter::ArkValue<Opt_BlendApplyType>(ARK_BLEND_APPLY_TYPE_FAST), "0"},
        {Converter::ArkValue<Opt_BlendMode>(static_cast<Ark_BlendMode>(999)),
            Converter::ArkValue<Opt_BlendApplyType>(ARK_BLEND_APPLY_TYPE_FAST), "0"},
    };
    for (const auto& [blendMode, applyType, expectedValue] : testPlan) {
        modifier_->setBlendMode(node_, &blendMode, &applyType);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_BLEND_MODE_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Invalid value should not change the blend mode";
    }
}

HWTEST_F(CommonMethodModifierTest5, DISABLED_setDrawModifierTest, TestSize.Level1)
{
#ifdef WRONG_GEN
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(modifier_->setDrawModifier, nullptr);
    DrawModifierPeer peer{};
    Opt_DrawModifier drawModifierOpt = Converter::ArkValue<Opt_DrawModifier>(&peer);
    EXPECT_EQ(peer.drawModifier, nullptr);
    EXPECT_EQ(peer.frameNode.Upgrade(), nullptr);
    modifier_->setDrawModifier(node_, &drawModifierOpt);
    EXPECT_NE(peer.drawModifier, nullptr);
    EXPECT_EQ(peer.frameNode.Upgrade(), frameNode);
#endif
}
}
