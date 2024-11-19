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
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "common_method_modifier_test.h"
#include "test/mock/core/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {

namespace {
    // GENERATED_ArkUICommonMethodModifier
    const auto ATTRIBUTE_BRIGHTNESS_NAME = "brightness";
    const auto ATTRIBUTE_BRIGHTNESS_DEFAULT_VALUE = "1";
    const auto ATTRIBUTE_CONTRAST_NAME = "contrast";
    const auto ATTRIBUTE_CONTRAST_DEFAULT_VALUE = "1";
    const auto ATTRIBUTE_GRAYSCALE_NAME = "grayscale";
    const auto ATTRIBUTE_GRAYSCALE_DEFAULT_VALUE = "0";
    const auto ATTRIBUTE_SATURATE_NAME = "saturate";
    const auto ATTRIBUTE_SATURATE_DEFAULT_VALUE = "1";
    const auto ATTRIBUTE_SEPIA_NAME = "sepia";
    const auto ATTRIBUTE_SEPIA_DEFAULT_VALUE = "0";
    const auto ATTRIBUTE_USE_SHADOW_BATCHING_NAME = "useShadowBatching";
    const auto ATTRIBUTE_USE_SHADOW_BATCHING_DEFAULT_VALUE = "false";
}

class CommonMethodModifierTest3 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    RefPtr<RenderContext> render_;

    RefPtr<GestureEventHub> GetGestureEventHub()
    {
        if (auto fnode = reinterpret_cast<FrameNode *>(node_); fnode) {
            if (auto eventHub = fnode->GetEventHub<NG::EventHub>(); eventHub) {
                return eventHub->GetOrCreateGestureEventHub();
            }
        }
        return nullptr;
    }

    RefPtr<MockRenderContext> GetMockRenderContext()
    {
        if (auto fnode = reinterpret_cast<FrameNode *>(node_); fnode) {
            return AceType::DynamicCast<MockRenderContext>(fnode->GetRenderContext());
        }
        return nullptr;
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
HWTEST_F(CommonMethodModifierTest3, setBrightnessTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBrightness, nullptr);
    using OneTestStep = std::tuple<Ark_Number, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Number>(0.0), "0"},
        {Converter::ArkValue<Ark_Number>(0.5), "0.5"},
        {Converter::ArkValue<Ark_Number>(5.0), "5"},
        {Converter::ArkValue<Ark_Number>(5.5), "5.5"},
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
    using OneTestStep = std::tuple<Ark_Number, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Number>(-0.5), ATTRIBUTE_BRIGHTNESS_DEFAULT_VALUE},
        {Converter::ArkValue<Ark_Number>(-5.0), ATTRIBUTE_BRIGHTNESS_DEFAULT_VALUE},
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
HWTEST_F(CommonMethodModifierTest3, setContrastTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setContrast, nullptr);
    using OneTestStep = std::tuple<Ark_Number, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Number>(0.0), "0"},
        {Converter::ArkValue<Ark_Number>(0.5), "0.5"},
        {Converter::ArkValue<Ark_Number>(5.0), "5"},
        {Converter::ArkValue<Ark_Number>(5.5), "5.5"},
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
    using OneTestStep = std::tuple<Ark_Number, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Number>(-0.5), ATTRIBUTE_CONTRAST_DEFAULT_VALUE},
        {Converter::ArkValue<Ark_Number>(-5.0), ATTRIBUTE_CONTRAST_DEFAULT_VALUE},
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
HWTEST_F(CommonMethodModifierTest3, setGrayScaleTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setGrayscale, nullptr);
    using OneTestStep = std::tuple<Ark_Number, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Number>(0.0), "0"},
        {Converter::ArkValue<Ark_Number>(0.5), "0.5"},
        {Converter::ArkValue<Ark_Number>(5.0), "5"},
        {Converter::ArkValue<Ark_Number>(5.5), "5.5"},
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
    using OneTestStep = std::tuple<Ark_Number, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Number>(-0.5), ATTRIBUTE_GRAYSCALE_DEFAULT_VALUE},
        {Converter::ArkValue<Ark_Number>(-5.0), ATTRIBUTE_GRAYSCALE_DEFAULT_VALUE},
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
HWTEST_F(CommonMethodModifierTest3, setSaturateTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSaturate, nullptr);
    using OneTestStep = std::tuple<Ark_Number, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Number>(0.0), "0"},
        {Converter::ArkValue<Ark_Number>(0.5), "0.5"},
        {Converter::ArkValue<Ark_Number>(5.0), "5"},
        {Converter::ArkValue<Ark_Number>(5.5), "5.5"},
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
    using OneTestStep = std::tuple<Ark_Number, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Number>(-0.5), ATTRIBUTE_SATURATE_DEFAULT_VALUE},
        {Converter::ArkValue<Ark_Number>(-5.0), ATTRIBUTE_SATURATE_DEFAULT_VALUE},
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
HWTEST_F(CommonMethodModifierTest3, setSepiaTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSepia, nullptr);
    using OneTestStep = std::tuple<Ark_Number, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Number>(0.0), "0"},
        {Converter::ArkValue<Ark_Number>(0.5), "0.5"},
        {Converter::ArkValue<Ark_Number>(5.0), "5"},
        {Converter::ArkValue<Ark_Number>(5.5), "5.5"},
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
    using OneTestStep = std::tuple<Ark_Number, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Number>(-0.5), ATTRIBUTE_SEPIA_DEFAULT_VALUE},
        {Converter::ArkValue<Ark_Number>(-5.0), ATTRIBUTE_SEPIA_DEFAULT_VALUE},
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
HWTEST_F(CommonMethodModifierTest3, setUseShadowBatchingTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setUseShadowBatching, nullptr);
    using OneTestStep = std::tuple<Ark_Boolean, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Boolean>(false), "false"},
        {Converter::ArkValue<Ark_Boolean>(true), "true"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setUseShadowBatching(node_, inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_USE_SHADOW_BATCHING_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}
}
