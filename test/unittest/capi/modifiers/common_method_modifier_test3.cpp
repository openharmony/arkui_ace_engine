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

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "generated/test_fixtures.h"
#include "generated/type_helpers.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/progress_mask_peer.h"
#include "common_method_modifier_test.h"
#include "test/mock/core/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {

namespace {
    // GENERATED_ArkUICommonMethodModifier
    constexpr auto ATTRIBUTE_BRIGHTNESS_NAME = "brightness";
    constexpr auto ATTRIBUTE_BRIGHTNESS_DEFAULT_VALUE = "1";
    constexpr auto ATTRIBUTE_BRIGHTNESS_NEGATIVE_DEFAULT_VALUE = "0";
    constexpr auto ATTRIBUTE_CONTRAST_NAME = "contrast";
    constexpr auto ATTRIBUTE_CONTRAST_DEFAULT_VALUE = "1";
    constexpr auto ATTRIBUTE_CONTRAST_NEGATIVE_DEFAULT_VALUE = "0";
    constexpr auto ATTRIBUTE_GRAYSCALE_NAME = "grayscale";
    constexpr auto ATTRIBUTE_GRAYSCALE_DEFAULT_VALUE = "0";
    constexpr auto ATTRIBUTE_SATURATE_NAME = "saturate";
    constexpr auto ATTRIBUTE_SATURATE_DEFAULT_VALUE = "1";
    constexpr auto ATTRIBUTE_SATURATE_NEGATIVE_DEFAULT_VALUE = "0";
    constexpr auto ATTRIBUTE_SEPIA_NAME = "sepia";
    constexpr auto ATTRIBUTE_SEPIA_DEFAULT_VALUE = "0";
    constexpr auto ATTRIBUTE_USE_SHADOW_BATCHING_NAME = "useShadowBatching";
    constexpr auto ATTRIBUTE_USE_SHADOW_BATCHING_DEFAULT_VALUE = "false";
    constexpr auto ATTRIBUTE_PROGRESS_MASK_VALUE_NAME = "updateProgress";
    constexpr auto ATTRIBUTE_PROGRESS_MASK_TOTAL_NAME = "total";
    constexpr auto ATTRIBUTE_PROGRESS_MASK_COLOR_NAME = "updateColor";
    constexpr auto ATTRIBUTE_PROGRESS_MASK_ENABLE_BREATHE_NAME = "enableBreathe";
}

class CommonMethodModifierTest3 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
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
 * @tc.name: setBrightnessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, setBrightnessTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_BRIGHTNESS_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_BRIGHTNESS_DEFAULT_VALUE);
}

/*
 * @tc.name: setBrightnessTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, DISABLED_setBrightnessTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBrightness, nullptr);
    using OneTestStep = std::tuple<Opt_Float64, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Float64>(0.0), "0"},
        {Converter::ArkValue<Opt_Float64>(0.5), "0.5"},
        {Converter::ArkValue<Opt_Float64>(5.0), "5"},
        {Converter::ArkValue<Opt_Float64>(5.5), "5.5"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setBrightness(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_BRIGHTNESS_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setBrightnessTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, setBrightnessTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBrightness, nullptr);
    using OneTestStep = std::tuple<Opt_Float64, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Float64>(-0.5), ATTRIBUTE_BRIGHTNESS_NEGATIVE_DEFAULT_VALUE},
        {Converter::ArkValue<Opt_Float64>(-5.0), ATTRIBUTE_BRIGHTNESS_NEGATIVE_DEFAULT_VALUE},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setBrightness(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_BRIGHTNESS_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setContrastTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, setContrastTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_CONTRAST_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_CONTRAST_DEFAULT_VALUE);
}

/*
 * @tc.name: setContrastTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, DISABLED_setContrastTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setContrast, nullptr);
    using OneTestStep = std::tuple<Opt_Float64, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Float64>(0.0), "0"},
        {Converter::ArkValue<Opt_Float64>(0.5), "0.5"},
        {Converter::ArkValue<Opt_Float64>(5.0), "5"},
        {Converter::ArkValue<Opt_Float64>(5.5), "5.5"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setContrast(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_CONTRAST_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setContrastTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, setContrastTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setContrast, nullptr);
    using OneTestStep = std::tuple<Opt_Float64, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Float64>(-0.5), ATTRIBUTE_CONTRAST_NEGATIVE_DEFAULT_VALUE},
        {Converter::ArkValue<Opt_Float64>(-5.0), ATTRIBUTE_CONTRAST_NEGATIVE_DEFAULT_VALUE},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setContrast(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_CONTRAST_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setGrayScaleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, setGrayScaleTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_GRAYSCALE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_GRAYSCALE_DEFAULT_VALUE);
}

/*
 * @tc.name: setGrayScaleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, DISABLED_setGrayScaleTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setGrayscale, nullptr);
    using OneTestStep = std::tuple<Opt_Float64, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Float64>(0.0), "0"},
        {Converter::ArkValue<Opt_Float64>(0.5), "0.5"},
        {Converter::ArkValue<Opt_Float64>(5.0), "5"},
        {Converter::ArkValue<Opt_Float64>(5.5), "5.5"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setGrayscale(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_GRAYSCALE_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setGrayScaleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, setGrayScaleTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setGrayscale, nullptr);
    using OneTestStep = std::tuple<Opt_Float64, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Float64>(-0.5), ATTRIBUTE_GRAYSCALE_DEFAULT_VALUE},
        {Converter::ArkValue<Opt_Float64>(-5.0), ATTRIBUTE_GRAYSCALE_DEFAULT_VALUE},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setGrayscale(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_GRAYSCALE_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setSaturateTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, setSaturateTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_SATURATE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SATURATE_DEFAULT_VALUE);
}

/*
 * @tc.name: setSaturateTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, DISABLED_setSaturateTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSaturate, nullptr);
    using OneTestStep = std::tuple<Opt_Float64, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Float64>(0.0), "0"},
        {Converter::ArkValue<Opt_Float64>(0.5), "0.5"},
        {Converter::ArkValue<Opt_Float64>(5.0), "5"},
        {Converter::ArkValue<Opt_Float64>(5.5), "5.5"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setSaturate(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_SATURATE_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setSaturateTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, setSaturateTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSaturate, nullptr);
    using OneTestStep = std::tuple<Opt_Float64, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Float64>(-0.5), ATTRIBUTE_SATURATE_NEGATIVE_DEFAULT_VALUE},
        {Converter::ArkValue<Opt_Float64>(-5.0), ATTRIBUTE_SATURATE_NEGATIVE_DEFAULT_VALUE},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setSaturate(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_SATURATE_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setSepiaTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, setSepiaTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_SEPIA_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SEPIA_DEFAULT_VALUE);
}

/*
 * @tc.name: setSepiaTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, DISABLED_setSepiaTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSepia, nullptr);
    using OneTestStep = std::tuple<Opt_Float64, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Float64>(0.0), "0"},
        {Converter::ArkValue<Opt_Float64>(0.5), "0.5"},
        {Converter::ArkValue<Opt_Float64>(5.0), "5"},
        {Converter::ArkValue<Opt_Float64>(5.5), "5.5"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setSepia(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_SEPIA_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setSepiaTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, setSepiaTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSepia, nullptr);
    using OneTestStep = std::tuple<Opt_Float64, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Float64>(-0.5), ATTRIBUTE_SEPIA_DEFAULT_VALUE},
        {Converter::ArkValue<Opt_Float64>(-5.0), ATTRIBUTE_SEPIA_DEFAULT_VALUE},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setSepia(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_SEPIA_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setUseShadowBatchingTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, setUseShadowBatchingTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_USE_SHADOW_BATCHING_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_USE_SHADOW_BATCHING_DEFAULT_VALUE);
}

/*
 * @tc.name: setUseShadowBatchingTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, DISABLED_setUseShadowBatchingTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setUseShadowBatching, nullptr);
    using OneTestStep = std::tuple<Opt_Boolean, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Boolean>(false), "false"},
        {Converter::ArkValue<Opt_Boolean>(true), "true"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setUseShadowBatching(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_USE_SHADOW_BATCHING_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

struct ProgressMaskTestPlan {
    Ark_Number inputValue;
    std::string expectedValue;
    Ark_Number inputTotal;
    std::string expectedTotal;
    Ark_ResourceColor inputColor;
    std::string expectedColor;
    Ark_Boolean inputEnableBreathe;
    std::string expectedEnableBreathe;
};

struct AutoProgressMaskPeer {
    const GENERATED_ArkUIProgressMaskAccessor* const accessor;
    ProgressMaskPeer* const ptr;

    AutoProgressMaskPeer(
        const GENERATED_ArkUIFullNodeAPI* fullAPI,
        const Ark_Number* value, const Ark_Number* total, const Ark_ResourceColor* color
    ) : accessor(fullAPI->getAccessors()->getProgressMaskAccessor()),
        ptr(accessor->construct(value, total, color))
    {}

    ~AutoProgressMaskPeer() { accessor->destroyPeer(ptr); }

    Ark_ProgressMask GetArkValue() const
    {
        return ptr;
    }
    ACE_DISALLOW_COPY_AND_MOVE(AutoProgressMaskPeer);
};

/*
 * @tc.name: setMaskValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, DISABLED_setMaskValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMask, nullptr);
    const std::vector<ProgressMaskTestPlan> validValues {
        {
            Converter::ArkValue<Ark_Number>(0), "0",
            Converter::ArkValue<Ark_Number>(100), "100",
            Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_RED), Color::RED.ToString(),
            Converter::ArkValue<Ark_Boolean>(false), "false"
        },
        {
            Converter::ArkValue<Ark_Number>(20.5f), "20.5",
            Converter::ArkValue<Ark_Number>(200.25f), "200.25",
            Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xff0000ff), Color(0xff0000ff).ToString(),
            Converter::ArkValue<Ark_Boolean>(true), "true"
        },
        {
            Converter::ArkValue<Ark_Number>(65535), "65535",
            Converter::ArkValue<Ark_Number>(32267), "32267",
            Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#123456"), Color::FromString("#123456").ToString(),
            Converter::ArkValue<Ark_Boolean>(false), "false"
        },
    };
    for (const auto& plan : validValues) {
        AutoProgressMaskPeer peer(fullAPI_, &plan.inputValue, &plan.inputTotal, &plan.inputColor);
        ASSERT_NE(peer.ptr, nullptr);
        peer.accessor->enableBreathingAnimation(peer.ptr, plan.inputEnableBreathe);
        const auto materialized = Converter::ArkValue<Opt_ProgressMask>(peer.GetArkValue());
        modifier_->setMask(node_, &materialized);
        const auto json = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(json, ATTRIBUTE_PROGRESS_MASK_VALUE_NAME);
        EXPECT_EQ(resultValue, plan.expectedValue);
        resultValue = GetAttrValue<std::string>(json, ATTRIBUTE_PROGRESS_MASK_TOTAL_NAME);
        EXPECT_EQ(resultValue, plan.expectedTotal);
        resultValue = GetAttrValue<std::string>(json, ATTRIBUTE_PROGRESS_MASK_COLOR_NAME);
        EXPECT_EQ(resultValue, plan.expectedColor);
        resultValue = GetAttrValue<std::string>(json, ATTRIBUTE_PROGRESS_MASK_ENABLE_BREATHE_NAME);
        EXPECT_EQ(resultValue, plan.expectedEnableBreathe);
    }
}

/*
 * @tc.name: setMask1PartForProgressMaskValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
#ifdef WRONG_OVERRIDE
HWTEST_F(CommonMethodModifierTest3, setMask1PartForProgressMaskValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMask1, nullptr);
    const std::vector<ProgressMaskTestPlan> validValues {
        {
            Converter::ArkValue<Ark_Number>(255), "255",
            Converter::ArkValue<Ark_Number>(99.5f), "99.5",
            Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_TRANSPARENT), Color::TRANSPARENT.ToString(),
            Converter::ArkValue<Ark_Boolean>(true), "true"
        },
        {
            Converter::ArkValue<Ark_Number>(20.5f), "20.5",
            Converter::ArkValue<Ark_Number>(20.5f), "20.5",
            Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xff123456), Color(0xff123456).ToString(),
            Converter::ArkValue<Ark_Boolean>(false), "false"
        },
    };
    for (const auto& plan : validValues) {
        AutoProgressMaskPeer peer(fullAPI_, &plan.inputValue, &plan.inputTotal, &plan.inputColor);
        ASSERT_NE(peer.ptr, nullptr);
        peer.accessor->enableBreathingAnimation(peer.ptr, plan.inputEnableBreathe);
        const auto materialized = peer.GetArkValue();
        const auto maskValue = Converter::ArkUnion<Ark_Type_CommonMethod_mask_value, Ark_ProgressMask>(materialized);
        modifier_->setMask2(node_, &maskValue);
        const auto json = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(json, ATTRIBUTE_PROGRESS_MASK_VALUE_NAME);
        EXPECT_EQ(resultValue, plan.expectedValue);
        resultValue = GetAttrValue<std::string>(json, ATTRIBUTE_PROGRESS_MASK_TOTAL_NAME);
        EXPECT_EQ(resultValue, plan.expectedTotal);
        resultValue = GetAttrValue<std::string>(json, ATTRIBUTE_PROGRESS_MASK_COLOR_NAME);
        EXPECT_EQ(resultValue, plan.expectedColor);
        resultValue = GetAttrValue<std::string>(json, ATTRIBUTE_PROGRESS_MASK_ENABLE_BREATHE_NAME);
        EXPECT_EQ(resultValue, plan.expectedEnableBreathe);
    }
}
#endif

/*
 * @tc.name: setFocusBoxTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest3, setFocusBoxTest, TestSize.Level1)
{
    auto style = Converter::ArkValue<Opt_FocusBoxStyle>(Ark_FocusBoxStyle {
        .margin = Converter::ArkCreate<Opt_LengthMetrics>(ARK_LENGTH_UNIT_PX, 10.f),
        .strokeWidth = Converter::ArkCreate<Opt_LengthMetrics>(ARK_LENGTH_UNIT_PX, 5.f),
    });
    modifier_->setFocusBox(node_, &style);
    const auto json = GetJsonValue(node_);
    auto focusbox = json->GetValue("focusBox");
    auto resultValue = GetAttrValue<std::string>(focusbox, "strokeWidth");
    EXPECT_EQ(resultValue, "5.00px");
    resultValue = GetAttrValue<std::string>(focusbox, "margin");
    EXPECT_EQ(resultValue, "10.00px");
}

} // namespace OHOS::Ace::NG
