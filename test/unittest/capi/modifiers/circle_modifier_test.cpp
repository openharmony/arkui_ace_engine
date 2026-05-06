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

#include "core/interfaces/native/implementation/color_metrics_peer.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_WIDTH_NAME = "width";
    const auto ATTRIBUTE_WIDTH_DEFAULT_VALUE = "0.00vp";

    const auto ATTRIBUTE_HEIGHT_NAME = "height";
    const auto ATTRIBUTE_HEIGHT_DEFAULT_VALUE = "0.00vp";
    const auto ATTRIBUTE_STROKE_NAME = "stroke";
    const auto ATTRIBUTE_FILL_NAME = "fill";
    const auto ATTRIBUTE_FOREGROUND_COLOR_NAME = "foregroundColor";
    const auto ATTRIBUTE_COLOR_DEFAULT_VALUE = "#FF000000";
} // namespace

class CircleModifierTest : public ModifierTestBase<GENERATED_ArkUICircleModifier,
    &GENERATED_ArkUINodeModifiers::getCircleModifier, GENERATED_ARKUI_CIRCLE> {
};


/*
 * @tc.name: setCircleOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CircleModifierTest, setCircleOptionsTestDefaultValues, TestSize.Level1)
{
    auto strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_WIDTH_NAME);
    EXPECT_THAT(strResult, Eq(ATTRIBUTE_WIDTH_DEFAULT_VALUE));

    strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_HEIGHT_NAME);
    EXPECT_THAT(strResult, Eq(ATTRIBUTE_HEIGHT_DEFAULT_VALUE));
}

/*
 * @tc.name: setStrokeTestResourceColorAndColorMetrics
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CircleModifierTest, setStrokeTestResourceColorAndColorMetrics, TestSize.Level1)
{
    ASSERT_NE(modifier_->setStroke, nullptr);
    const auto RES_NAME = NamedResourceId { "circle.stroke.test", ResourceType::COLOR };
    AddResource(RES_NAME, Color::RED);

    const auto initialValue = GetAttrValue<std::string>(node_, ATTRIBUTE_STROKE_NAME);
    EXPECT_THAT(initialValue, Eq(ATTRIBUTE_COLOR_DEFAULT_VALUE));

    const std::vector<std::pair<Ark_ResourceColor, std::string>> resourcePlan = {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
        { CreateResourceUnion<Ark_ResourceColor>(RES_NAME), Color::RED.ToString() },
    };

    for (const auto& [resourceColor, expected] : resourcePlan) {
        auto inputValue =
            Converter::ArkUnion<Opt_Union_ResourceColor_ColorMetricsExt, Ark_ResourceColor>(resourceColor);
        modifier_->setStroke(node_, &inputValue);
        const auto actualValue = GetAttrValue<std::string>(node_, ATTRIBUTE_STROKE_NAME);
        EXPECT_THAT(actualValue, Eq(expected));
    }

    Ark_ColorMetricsExt colorMetrics = {
        .red = 0x11,
        .green = 0x22,
        .blue = 0x33,
        .alpha = 0xAA,
        .colorSpace = ARK_COLOR_SPACE_SRGB,
        .resourceId = 0,
        .redValue = 0.0,
        .greenValue = 0.0,
        .blueValue = 0.0,
        .headRoom = 1.0,
        .isHDR = false,
    };
    auto metricsValue = Converter::ArkUnion<Opt_Union_ResourceColor_ColorMetricsExt, Ark_ColorMetricsExt>(colorMetrics);
    modifier_->setStroke(node_, &metricsValue);
    const auto metricsResult = GetAttrValue<std::string>(node_, ATTRIBUTE_STROKE_NAME);
    EXPECT_THAT(metricsResult, Eq("#AA112233"));

    auto resetValue = Converter::ArkValue<Opt_Union_ResourceColor_ColorMetricsExt>(Ark_Empty());
    modifier_->setStroke(node_, &resetValue);
    const auto resetResult = GetAttrValue<std::string>(node_, ATTRIBUTE_STROKE_NAME);
    EXPECT_THAT(resetResult, Eq(ATTRIBUTE_COLOR_DEFAULT_VALUE));
}

/*
 * @tc.name: setFillTestColorMetricsAndResetSemantics
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CircleModifierTest, setFillTestColorMetricsAndResetSemantics, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFill, nullptr);
    ASSERT_NE(commonModifier_->setForegroundColor, nullptr);

    auto foregroundValue = Converter::ArkUnion<Opt_Union_ResourceColor_ColoringStrategy, Ark_ResourceColor>(
        Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0x445566));
    commonModifier_->setForegroundColor(node_, &foregroundValue);
    auto foregroundResult = GetAttrValue<std::string>(node_, ATTRIBUTE_FOREGROUND_COLOR_NAME);
    EXPECT_THAT(foregroundResult, Eq("#FF445566"));

    Ark_ColorMetricsExt colorMetrics = {
        .red = 0x66,
        .green = 0x77,
        .blue = 0x88,
        .alpha = 0xCC,
        .colorSpace = ARK_COLOR_SPACE_SRGB,
        .resourceId = 0,
        .redValue = 0.0,
        .greenValue = 0.0,
        .blueValue = 0.0,
        .headRoom = 1.0,
        .isHDR = false,
    };
    auto fillValue = Converter::ArkUnion<Opt_Union_ResourceColor_ColorMetricsExt, Ark_ColorMetricsExt>(colorMetrics);
    modifier_->setFill(node_, &fillValue);

    auto fillResult = GetAttrValue<std::string>(node_, ATTRIBUTE_FILL_NAME);
    EXPECT_THAT(fillResult, Eq("#CC667788"));
    foregroundResult = GetAttrValue<std::string>(node_, ATTRIBUTE_FOREGROUND_COLOR_NAME);
    EXPECT_THAT(foregroundResult, Eq("#CC667788"));

    auto resetValue = Converter::ArkValue<Opt_Union_ResourceColor_ColorMetricsExt>(Ark_Empty());
    modifier_->setFill(node_, &resetValue);

    fillResult = GetAttrValue<std::string>(node_, ATTRIBUTE_FILL_NAME);
    EXPECT_THAT(fillResult, Eq(ATTRIBUTE_COLOR_DEFAULT_VALUE));
    foregroundResult = GetAttrValue<std::string>(node_, ATTRIBUTE_FOREGROUND_COLOR_NAME);
    EXPECT_FALSE(foregroundResult.has_value());
}

/*
 * @tc.name: setCircleOptionsTestValidWidthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CircleModifierTest, setCircleOptionsTestValidWidthValues, TestSize.Level1)
{
    Ark_CircleOptions circleOptions;
    Opt_CircleOptions circleOptionsOpt;

    typedef std::pair<Opt_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Opt_Length>(1.0), "1.00vp" },
        { Converter::ArkValue<Opt_Length>(0.0), "0.00vp" },
        { Converter::ArkValue<Opt_Length>(2.45f), "2.45vp" },
        { Converter::ArkValue<Opt_Length>("5px"), "5.00px" },
        { Converter::ArkValue<Opt_Length>("22.35px"), "22.35px" },
        { Converter::ArkValue<Opt_Length>("7vp"), "7.00vp" },
        { Converter::ArkValue<Opt_Length>("1.65vp"), "1.65vp" },
        { Converter::ArkValue<Opt_Length>("65fp"), "65.00fp" },
        { Converter::ArkValue<Opt_Length>("4.3fp"), "4.30fp" },
        { Converter::ArkValue<Opt_Length>("11lpx"), "11.00lpx" },
        { Converter::ArkValue<Opt_Length>("0.5lpx"), "0.50lpx" },
        { Converter::ArkValue<Opt_Length>("3"), "3.00vp" },
        { Converter::ArkValue<Opt_Length>("10.65"), "10.65vp" },
        { Converter::ArkValue<Opt_Length>("23%"), "23.00%" },
    };

    for (const auto &[arkResWidth, expected]: testPlan) {
        circleOptions.width = arkResWidth;
        circleOptions.height = Converter::ArkValue<Opt_Length>(Ark_Empty());
        circleOptionsOpt = Converter::ArkValue<Opt_CircleOptions>(circleOptions);
        modifier_->setCircleOptions(node_, &circleOptionsOpt);

        auto strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_THAT(strResult, Eq(expected));
        strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_THAT(strResult, Eq(ATTRIBUTE_HEIGHT_DEFAULT_VALUE));
    }
}

/*
 * @tc.name: setCircleOptionsTestValidHeightValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CircleModifierTest, setCircleOptionsTestValidHeightValues, TestSize.Level1)
{
    Ark_CircleOptions circleOptions;
    Opt_CircleOptions circleOptionsOpt;

    typedef std::pair<Opt_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Opt_Length>(1.0), "1.00vp" },
        { Converter::ArkValue<Opt_Length>(0.0), "0.00vp" },
        { Converter::ArkValue<Opt_Length>(2.45f), "2.45vp" },
        { Converter::ArkValue<Opt_Length>("5px"), "5.00px" },
        { Converter::ArkValue<Opt_Length>("22.35px"), "22.35px" },
        { Converter::ArkValue<Opt_Length>("7vp"), "7.00vp" },
        { Converter::ArkValue<Opt_Length>("1.65vp"), "1.65vp" },
        { Converter::ArkValue<Opt_Length>("65fp"), "65.00fp" },
        { Converter::ArkValue<Opt_Length>("4.3fp"), "4.30fp" },
        { Converter::ArkValue<Opt_Length>("11lpx"), "11.00lpx" },
        { Converter::ArkValue<Opt_Length>("0.5lpx"), "0.50lpx" },
        { Converter::ArkValue<Opt_Length>("3"), "3.00vp" },
        { Converter::ArkValue<Opt_Length>("10.65"), "10.65vp" },
        { Converter::ArkValue<Opt_Length>("23%"), "23.00%" },
    };

    for (const auto &[arkResHeight, expected]: testPlan) {
        circleOptions.width = Converter::ArkValue<Opt_Length>(Ark_Empty());
        circleOptions.height = arkResHeight;
        circleOptionsOpt = Converter::ArkValue<Opt_CircleOptions>(circleOptions);
        modifier_->setCircleOptions(node_, &circleOptionsOpt);

        auto strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_THAT(strResult, Eq(ATTRIBUTE_WIDTH_DEFAULT_VALUE));
        strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_THAT(strResult, Eq(expected));
    }
}

/*
 * @tc.name: setCircleOptionsTestInvalidWidthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CircleModifierTest, setCircleOptionsTestInvalidWidthValues, TestSize.Level1)
{
    Ark_CircleOptions circleOptions;
    Opt_CircleOptions circleOptionsOpt;

    typedef std::pair<Opt_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Opt_Length>(-1.0), "0.00vp" },
        { Converter::ArkValue<Opt_Length>(-3.56f), "0.00vp" },
        { Converter::ArkValue<Opt_Length>("invalid value"), "0.00vp" },
        { Converter::ArkValue<Opt_Length>("-8px"), "0.00px" },
        { Converter::ArkValue<Opt_Length>("-15.6px"), "0.00px" },
        { Converter::ArkValue<Opt_Length>("-21vp"), "0.00vp" },
        { Converter::ArkValue<Opt_Length>("-8.6vp"), "0.00vp" },
        { Converter::ArkValue<Opt_Length>("-32fp"), "0.00fp" },
        { Converter::ArkValue<Opt_Length>("-9.99fp"), "0.00fp" },
        { Converter::ArkValue<Opt_Length>("-22lpx"), "0.00lpx" },
        { Converter::ArkValue<Opt_Length>("-1.23lpx"), "0.00lpx" },
        { Converter::ArkValue<Opt_Length>("-6"), "0.00vp" },
        { Converter::ArkValue<Opt_Length>("-16.2"), "0.00vp" },
    };

    for (const auto &[arkResWidth, expected]: testPlan) {
        circleOptions.width = arkResWidth;
        circleOptions.height = Converter::ArkValue<Opt_Length>(Ark_Empty());
        circleOptionsOpt = Converter::ArkValue<Opt_CircleOptions>(circleOptions);
        modifier_->setCircleOptions(node_, &circleOptionsOpt);

        auto strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_THAT(strResult, Eq(expected));
        strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_THAT(strResult, Eq(ATTRIBUTE_HEIGHT_DEFAULT_VALUE));
    }
}

/*
 * @tc.name: setCircleOptionsTestInvalidHeightValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CircleModifierTest, setCircleOptionsTestInvalidHeightValues, TestSize.Level1)
{
    Ark_CircleOptions circleOptions;
    Opt_CircleOptions circleOptionsOpt;

    typedef std::pair<Opt_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Opt_Length>(-1.0), "0.00vp" },
        { Converter::ArkValue<Opt_Length>(-3.56f), "0.00vp" },
        { Converter::ArkValue<Opt_Length>("invalid value"), "0.00vp" },
        { Converter::ArkValue<Opt_Length>("-8px"), "0.00px" },
        { Converter::ArkValue<Opt_Length>("-15.6px"), "0.00px" },
        { Converter::ArkValue<Opt_Length>("-21vp"), "0.00vp" },
        { Converter::ArkValue<Opt_Length>("-8.6vp"), "0.00vp" },
        { Converter::ArkValue<Opt_Length>("-32fp"), "0.00fp" },
        { Converter::ArkValue<Opt_Length>("-9.99fp"), "0.00fp" },
        { Converter::ArkValue<Opt_Length>("-22lpx"), "0.00lpx" },
        { Converter::ArkValue<Opt_Length>("-1.23lpx"), "0.00lpx" },
        { Converter::ArkValue<Opt_Length>("-6"), "0.00vp" },
        { Converter::ArkValue<Opt_Length>("-16.2"), "0.00vp" },
    };

    for (const auto &[arkResHeight, expected]: testPlan) {
        circleOptions.width = Converter::ArkValue<Opt_Length>(Ark_Empty());
        circleOptions.height = arkResHeight;
        circleOptionsOpt = Converter::ArkValue<Opt_CircleOptions>(circleOptions);
        modifier_->setCircleOptions(node_, &circleOptionsOpt);

        auto strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_THAT(strResult, Eq(ATTRIBUTE_WIDTH_DEFAULT_VALUE));
        strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_THAT(strResult, Eq(expected));
    }
}
} // namespace OHOS::Ace::NG
