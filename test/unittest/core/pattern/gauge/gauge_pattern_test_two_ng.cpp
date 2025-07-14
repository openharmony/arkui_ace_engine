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

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "gtest/internal/gtest-port.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/offset.h"
#include "base/log/log_wrapper.h"
#include "core/components/progress/progress_theme.h"
#include "core/components/theme/theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/gauge/gauge_layout_algorithm.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/components_ng/pattern/gauge/gauge_modifier.h"
#include "core/components_ng/pattern/gauge/gauge_paint_method.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/pattern/gauge/gauge_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class GaugePatternTestTwoNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    RefPtr<FrameNode> frameNode_;
    RefPtr<GaugePattern> pattern_;
    RefPtr<GaugeLayoutProperty> layoutProperty_;
    RefPtr<GaugePaintProperty> paintProperty_;
    RefPtr<GaugeAccessibilityProperty> accessibilityProperty_;
};

void GaugePatternTestTwoNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_PROGRESS);
    auto progressTheme = ProgressTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
}

void GaugePatternTestTwoNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void GaugePatternTestTwoNg::SetUp() {}

void GaugePatternTestTwoNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void GaugePatternTestTwoNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<GaugePattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<GaugeLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<GaugePaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<GaugeAccessibilityProperty>();
}

/**
 * @tc.name: GaugeTestSetGradientColorModeInit001
 * @tc.desc: Test SetGradientColorModeInit
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestTwoNg, GaugeTestSetGradientColorModeInit001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GaugeModelNG.
     */
    GaugeModelNG gauge;
    gauge.Create(50.0f, 100.0f, 0.0f);
    /**
     * @tc.steps: step2. Test with SystemProperties::ConfigChangePerform() = false
     */
    g_isConfigChangePerform = false;
    gauge.SetGradientColorModeInit();
    std::vector<Color> colorVector = { Color::BLUE, Color::RED, Color::GREEN };
    std::vector<ColorStopArray> colors;
    ColorStopArray colorStopArray;
    for (const auto& color : colorVector) {
        colorStopArray.emplace_back(std::make_pair(color, Dimension(0.0)));
    }
    colors.emplace_back(colorStopArray);
    gauge.SetGradientInit(colors);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    gauge.SetGradientColorModeInit(frameNode);
    gauge.SetGradientInit(frameNode, colors);
    /**
     * @tc.steps: step2. Test with SystemProperties::ConfigChangePerform() = true
     */
    g_isConfigChangePerform = true;
    gauge.SetGradientInit(frameNode, colors);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    EXPECT_TRUE(gaugePaintProperty->GetGradientColorsInit().has_value());
    EXPECT_EQ(gaugePaintProperty->GetGradientColorsInitValue(), colors);
}

/**
 * @tc.name: GaugeTestCheckDarkResource001
 * @tc.desc: Test CheckDarkResource
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestTwoNg, GaugeTestCheckDarkResource001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GaugeModelNG.
     */
    GaugeModelNG gauge;
    gauge.Create(50.0f, 100.0f, 0.0f);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Test with ColorMode::DARK
     */
    MockContainer::SetMockColorMode(ColorMode::DARK);
    auto result = pattern->CheckDarkResource(1);
    EXPECT_FALSE(result);
    /**
     * @tc.steps: step2. Test with ColorMode::LIGHT
     */
    MockContainer::SetMockColorMode(ColorMode::LIGHT);
    result = pattern->CheckDarkResource(1);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GaugeTestProcessSingleColorStop001
 * @tc.desc: Test ProcessSingleColorStop
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestTwoNg, GaugeTestProcessSingleColorStop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GaugeModelNG.
     */
    GaugeModelNG gauge;
    gauge.Create(50.0f, 100.0f, 0.0f);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(pattern, nullptr);

    Color color(0xFFFFFFFF);
    color.SetResourceId(0);
    std::function<uint32_t(uint32_t)> invertFunc = [](uint32_t val) -> uint32_t { return val ^ 0xFFFFFFFF; };
    auto result = pattern->ProcessSingleColorStop(color, invertFunc);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GaugeTestProcessSingleColorStop002
 * @tc.desc: Test ProcessSingleColorStop
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestTwoNg, GaugeTestProcessSingleColorStop002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GaugeModelNG.
     */
    GaugeModelNG gauge;
    gauge.Create(50.0f, 100.0f, 0.0f);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(pattern, nullptr);

    Color color(0xFFFFFFFF);
    color.SetResourceId(0);
    std::function<uint32_t(uint32_t)> invertFunc = nullptr;
    auto result = pattern->ProcessSingleColorStop(color, invertFunc);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GaugeTestProcessSingleColorStop003
 * @tc.desc: Test ProcessSingleColorStop
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestTwoNg, GaugeTestProcessSingleColorStop003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GaugeModelNG.
     */
    GaugeModelNG gauge;
    gauge.Create(50.0f, 100.0f, 0.0f);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(pattern, nullptr);

    Color color(0xFFFFFFFF);
    color.SetResourceId(123);
    std::function<uint32_t(uint32_t)> invertFunc = [](uint32_t val) -> uint32_t { return val ^ 0xFFFFFFFF; };
    MockContainer::SetMockColorMode(ColorMode::LIGHT);
    auto result = pattern->ProcessSingleColorStop(color, invertFunc);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GaugeTestProcessSingleColorStop004
 * @tc.desc: Test ProcessSingleColorStop
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestTwoNg, GaugeTestProcessSingleColorStop004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GaugeModelNG.
     */
    GaugeModelNG gauge;
    gauge.Create(50.0f, 100.0f, 0.0f);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(pattern, nullptr);

    Color color(0xFFFFFFFF);
    color.SetResourceId(123);
    std::function<uint32_t(uint32_t)> invertFunc = [](uint32_t val) -> uint32_t { return val ^ 0xFFFFFFFF; };
    MockContainer::SetMockColorMode(ColorMode::DARK);
    auto result = pattern->ProcessSingleColorStop(color, invertFunc);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GaugeTestProcessSingleColorStop005
 * @tc.desc: Test ProcessSingleColorStop
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestTwoNg, GaugeTestProcessSingleColorStop005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GaugeModelNG.
     */
    GaugeModelNG gauge;
    gauge.Create(50.0f, 100.0f, 0.0f);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(pattern, nullptr);

    Color color(0xFFFFFFFF);
    color.SetResourceId(123);
    std::function<uint32_t(uint32_t)> invertFunc = nullptr;

    MockContainer::SetMockColorMode(ColorMode::DARK);
    auto result = pattern->ProcessSingleColorStop(color, invertFunc);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GaugeTestProcessGradientColors001
 * @tc.desc: Test ProcessGradientColors
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestTwoNg, GaugeTestProcessGradientColors001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GaugeModelNG.
     */
    GaugeModelNG gauge;
    gauge.Create(50.0f, 100.0f, 0.0f);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(pattern, nullptr);

    Color color(0xFFFFFFFF);
    color.SetResourceId(123);
    std::function<uint32_t(uint32_t)> invertFunc = nullptr;
    std::vector<std::vector<std::pair<Color, Dimension>>> gradientColors = { { { color, Dimension(0.0f) },
        { Color(0xFF0000FF, 321), Dimension(1.0f) } } };
    auto result = pattern->ProcessGradientColors(gradientColors, invertFunc);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GaugeTestProcessGradientColors002
 * @tc.desc: Test ProcessGradientColors
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestTwoNg, GaugeTestProcessGradientColors002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GaugeModelNG.
     */
    GaugeModelNG gauge;
    gauge.Create(50.0f, 100.0f, 0.0f);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(pattern, nullptr);

    Color color(0xFFFFFFFF);
    color.SetResourceId(123);
    std::function<uint32_t(uint32_t)> invertFunc = [](uint32_t val) -> uint32_t { return val ^ 0xFFFFFFFF; };

    std::vector<std::vector<std::pair<Color, Dimension>>> gradientColors = { { { color, Dimension(0.0f) },
        { Color(0xFF0000FF, 321), Dimension(1.0f) } } };
    auto result = pattern->ProcessGradientColors(gradientColors, invertFunc);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GaugeTestOnColorConfigurationUpdate001
 * @tc.desc: Test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestTwoNg, GaugeTestOnColorConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GaugeModelNG.
     */
    GaugeModelNG gauge;
    gauge.Create(50.0f, 100.0f, 0.0f);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    gaugePaintProperty->UpdateUseJsLinearGradient(false);
    std::vector<Color> colorVector = { Color::BLUE, Color::RED, Color::GREEN };
    std::vector<ColorStopArray> colors;
    ColorStopArray colorStopArray;
    for (const auto& color : colorVector) {
        colorStopArray.emplace_back(std::make_pair(color, Dimension(0.0)));
    }
    colors.emplace_back(colorStopArray);
    gaugePaintProperty->UpdateGradientColors(colors);
    gauge.SetGradientInit(frameNode, colors);
    gaugePaintProperty->UpdateColorModeInit(static_cast<int>(ColorMode::DARK));
    MockContainer::SetMockColorMode(ColorMode::LIGHT);
    pattern->OnColorConfigurationUpdate();

    MockContainer::SetMockColorMode(ColorMode::DARK);
    pattern->OnColorConfigurationUpdate();
    EXPECT_EQ(gaugePaintProperty->GetGradientColorsValue(), gaugePaintProperty->GetGradientColorsInitValue());

    MockContainer::SetMockColorMode(ColorMode::LIGHT);
    std::vector<ColorStopArray> colors2;
    ColorStopArray colorStopArray2;
    Color color1(0xFFFFFFFF);
    color1.SetResourceId(123);
    colorStopArray2.emplace_back(std::make_pair(color1, Dimension(0.0)));
    colorStopArray2.emplace_back(std::make_pair(color1, Dimension(1.0)));
    colors2.emplace_back(colorStopArray2);
    gaugePaintProperty->UpdateGradientColors(colors2);
    pattern->OnColorConfigurationUpdate();
    EXPECT_NE(gaugePaintProperty->GetGradientColorsValue(), gaugePaintProperty->GetGradientColorsInitValue());
}
} // namespace OHOS::Ace::NG