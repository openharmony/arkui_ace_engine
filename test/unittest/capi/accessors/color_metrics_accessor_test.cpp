/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "accessor_test_base.h"
#include "accessor_test_utils.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"
#include "core/interfaces/native/implementation/color_metrics_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

class ColorMetricsAccessorTest : public AccessorTestBase<GENERATED_ArkUIColorMetricsAccessor,
                                    &GENERATED_ArkUIAccessors::getColorMetricsAccessor, ColorMetricsPeer> {};

/**
 * @tc.name: NumericTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorMetricsAccessorTest, NumericTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->numeric, nullptr);
    using OneTestStep = std::tuple<Ark_Number, uint32_t>;
    const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Number>(0xff000011), 0xff000011 },
        { Converter::ArkValue<Ark_Number>(0xff001100), 0xff001100 },
        { Converter::ArkValue<Ark_Number>(0xff110000), 0xff110000 },
        { Converter::ArkValue<Ark_Number>(0xaa112233), 0xaa112233 },
        { Converter::ArkValue<Ark_Number>(0xffffffff), 0xffffffff }, // Test max value
        { Converter::ArkValue<Ark_Number>(0x00000000), 0xff000000 }  // Test min value
    };
    Ark_ColorMetrics resultPeer;
    for (auto [inputValue, expectedValue]: testPlan) {
        resultPeer = accessor_->numeric(&inputValue);
        EXPECT_EQ(resultPeer->colorValue.value, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: RgbaTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorMetricsAccessorTest, RgbaTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->rgba, nullptr);
    using OneTestStep = std::tuple<Ark_Number, Ark_Number, Ark_Number, Ark_Number, uint32_t>;
    const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Number>(0.67f), Converter::ArkValue<Ark_Number>(0x00),
            Converter::ArkValue<Ark_Number>(0x00), Converter::ArkValue<Ark_Number>(0x11), 0xaa000011 },
        { Converter::ArkValue<Ark_Number>(0.5f), Converter::ArkValue<Ark_Number>(0x00),
            Converter::ArkValue<Ark_Number>(0x11), Converter::ArkValue<Ark_Number>(0x00), 0x7f001100 },
        { Converter::ArkValue<Ark_Number>(0.75f), Converter::ArkValue<Ark_Number>(0x11),
            Converter::ArkValue<Ark_Number>(0x00), Converter::ArkValue<Ark_Number>(0x00), 0xbf110000 },
        { Converter::ArkValue<Ark_Number>(0.25f), Converter::ArkValue<Ark_Number>(0x11),
            Converter::ArkValue<Ark_Number>(0x22), Converter::ArkValue<Ark_Number>(0x33), 0x3f112233 },
        { Converter::ArkValue<Ark_Number>(1.f), Converter::ArkValue<Ark_Number>(0xff),
            Converter::ArkValue<Ark_Number>(0xff), Converter::ArkValue<Ark_Number>(0xff), 0xffffffff },
        { Converter::ArkValue<Ark_Number>(0.f), Converter::ArkValue<Ark_Number>(0x00),
            Converter::ArkValue<Ark_Number>(0x00), Converter::ArkValue<Ark_Number>(0x00), 0x00000000 },
    };
    Ark_ColorMetrics resultPeer;
    for (auto [inputAlpha, inputRed, inputGreen, inputBlue, expectedValue]: testPlan) {
        resultPeer = accessor_->rgba(&inputRed, &inputGreen, &inputBlue, &inputAlpha);
        EXPECT_EQ(resultPeer->colorValue.value, expectedValue) <<
            std::hex << "Result: " << resultPeer->colorValue.value << ", Expected: " << expectedValue;
    }
}

/**
 * @tc.name: ResourceColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorMetricsAccessorTest, ResourceColorTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->resourceColor, nullptr);
    const auto RES_NAME_ID = NamedResourceId { "color_resource_name", ResourceType::COLOR };
    const auto EXPECTED_COLOR = Color(0xaabbccdd);

    auto arkResource = CreateResource(RES_NAME_ID);
    auto arkResourceColor = Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(arkResource);
    AddResource(RES_NAME_ID, EXPECTED_COLOR);

    auto resultPeer = accessor_->resourceColor(&arkResourceColor);
    auto peerColor = resultPeer->colorValue.value;

    EXPECT_EQ(peerColor, EXPECTED_COLOR.GetValue());
}

/**
 * @tc.name: BlendColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorMetricsAccessorTest, BlendColorTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->blendColor, nullptr);
    using OneTestStep = std::tuple<uint32_t, uint32_t>;
    const std::vector<OneTestStep> testPlan = {
        { 0x22000011, 0x22000011 },
        { 0x33001100, 0x4e000b05 },
        { 0x44110000, 0x7d090502 },
        { 0xaa112233, 0xd30f1c29 },
        { 0xff000000, 0xff000000 },
        { 0xffffffff, 0xffffffff },
        { 0x00000000, 0xffffffff }
    };
    peer_->colorValue.value = 0x00000000; // Test blend with a full transparent color
    Ark_ColorMetrics overlayPeer = new ColorMetricsPeer();
    Ark_ColorMetrics resultPeer;
    for (auto [inputValue, expectedValue]: testPlan) {
        overlayPeer->colorValue.value = inputValue;
        resultPeer = accessor_->blendColor(peer_, overlayPeer);
        EXPECT_EQ(resultPeer->colorValue.value, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: GetColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorMetricsAccessorTest, GetColorTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->color, nullptr);
    using OneTestStep = std::tuple<uint32_t, std::string>;
    const std::vector<OneTestStep> testPlan = {
        { 0xff000011, "#FF000011" },
        { 0xff001100, "#FF001100" },
        { 0xff110000, "#FF110000" },
        { 0xaa112233, "#AA112233" },
        { 0xffffffff, "#FFFFFFFF" }, // Test max value
        { 0x00000000, "#00000000" }  // Test min value
    };
    Ark_String arkResultValue;
    std::string resultValue;
    for (auto [inputValue, expectedValue]: testPlan) {
        peer_->colorValue.value = inputValue;
        arkResultValue = accessor_->color(peer_);
        resultValue = Converter::Convert<std::string>(arkResultValue);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: GetRedTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorMetricsAccessorTest, GetRedTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->red, nullptr);
    using OneTestStep = std::tuple<uint32_t, int32_t>;
    const std::vector<OneTestStep> testPlan = {
        { 0xff110011, 0x11 },
        { 0xff2211aa, 0x22 },
        { 0xaabb22cc, 0xbb },
        { 0xffffffff, 0xff }, // Test max value
        { 0x00000000, 0x00 }  // Test min value
    };
    Ark_Number arkResultValue;
    int32_t resultValue;
    for (auto [inputValue, expectedValue]: testPlan) {
        peer_->colorValue.value = inputValue;
        arkResultValue = accessor_->red(peer_);
        resultValue = Converter::Convert<int32_t>(arkResultValue);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: GetGreenTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorMetricsAccessorTest, GetGreenTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->green, nullptr);
    using OneTestStep = std::tuple<uint32_t, int32_t>;
    const std::vector<OneTestStep> testPlan = {
        { 0xff001111, 0x11 },
        { 0xff1122aa, 0x22 },
        { 0xaa22bbcc, 0xbb },
        { 0xffffffff, 0xff }, // Test max value
        { 0x00000000, 0x00 }  // Test min value
    };
    Ark_Number arkResultValue;
    int32_t resultValue;
    for (auto [inputValue, expectedValue]: testPlan) {
        peer_->colorValue.value = inputValue;
        arkResultValue = accessor_->green(peer_);
        resultValue = Converter::Convert<int32_t>(arkResultValue);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: GetBlueTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorMetricsAccessorTest, GetBlueTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->blue, nullptr);
    using OneTestStep = std::tuple<uint32_t, int32_t>;
    const std::vector<OneTestStep> testPlan = {
        { 0xff001111, 0x11 },
        { 0xff11aa22, 0x22 },
        { 0xaa22ccbb, 0xbb },
        { 0xffffffff, 0xff }, // Test max value
        { 0x00000000, 0x00 }  // Test min value
    };
    Ark_Number arkResultValue;
    int32_t resultValue;
    for (auto [inputValue, expectedValue]: testPlan) {
        peer_->colorValue.value = inputValue;
        arkResultValue = accessor_->blue(peer_);
        resultValue = Converter::Convert<int32_t>(arkResultValue);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: GetAlphaTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorMetricsAccessorTest, GetAlphaTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->alpha, nullptr);
    using OneTestStep = std::tuple<uint32_t, int32_t>;
    const std::vector<OneTestStep> testPlan = {
        { 0x11ff0011, 0x11 },
        { 0x2211aaff, 0x22 },
        { 0xbb22ccaa, 0xbb },
        { 0xffffffff, 0xff }, // Test max value
        { 0x00000000, 0x00 }  // Test min value
    };
    Ark_Number arkResultValue;
    int32_t resultValue;
    for (auto [inputValue, expectedValue]: testPlan) {
        peer_->colorValue.value = inputValue;
        arkResultValue = accessor_->alpha(peer_);
        resultValue = Converter::Convert<int32_t>(arkResultValue);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}
} // namespace OHOS::Ace::NG
