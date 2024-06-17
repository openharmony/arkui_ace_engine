/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#define private public
#define protected public
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
namespace {
constexpr float MAX = 100.0f;
constexpr float MIN = 0.0f;
constexpr bool ENABLED_TRUE = true;
constexpr bool ENABLED_FALSE = false;
float g_testValue = 0.0f;
float g_testMax = 0.0f;
float g_testMin = 0.0f;
} // namespace

class GaugePatternTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void Create(float values, float min, float max, const std::function<void(GaugeModelNG)>& callback = nullptr);

    RefPtr<FrameNode> frameNode_;
    RefPtr<GaugePattern> pattern_;
    RefPtr<GaugeLayoutProperty> layoutProperty_;
    RefPtr<GaugePaintProperty> paintProperty_;
    RefPtr<GaugeAccessibilityProperty> accessibilityProperty_;
};

void GaugePatternTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_PROGRESS);
    auto progressTheme = ProgressTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
}

void GaugePatternTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void GaugePatternTestNg::SetUp() {}

void GaugePatternTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void GaugePatternTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<GaugePattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<GaugeLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<GaugePaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<GaugeAccessibilityProperty>();
}

void GaugePatternTestNg::Create(float values, float min, float max, const std::function<void(GaugeModelNG)>& callback)
{
    GaugeModelNG model;
    model.Create(values, min, max);
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: GaugePatternTest050
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = -1.0f;
    g_testMin = 0.0f;
    g_testMax = 100.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_TRUE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_TRUE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest051
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = -101.0f;
    g_testMin = -100.0f;
    g_testMax = 0.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_TRUE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_TRUE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest052
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest052, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 1.0f;
    g_testMin = -100.0f;
    g_testMax = 0.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_TRUE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_TRUE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest053
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest053, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = -1.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_TRUE);
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_TRUE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest054
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest054, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 101.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_TRUE);
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_TRUE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest055
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest055, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 0.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_TRUE);
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(MIN, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_TRUE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest056
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest056, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 0.1f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_TRUE);
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_TRUE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest057
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest057, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = -0.1f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_TRUE);
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_TRUE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest058
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest058, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 100.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_TRUE);
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_TRUE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest059
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest059, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 100.1f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_TRUE);
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_TRUE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest060
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest060, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 0.0f;
    g_testMax = 100.0f;
    g_testMin = 0.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest061
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest061, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 100.0f;
    g_testMax = 100.0f;
    g_testMin = 0.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest062
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest062, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 0.1f;
    g_testMax = 100.0f;
    g_testMin = 0.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest063
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest063, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 99.9f;
    g_testMax = 100.0f;
    g_testMin = 0.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest064
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest064, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 0.0f;
    g_testMax = 0.0f;
    g_testMin = 0.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest065
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest065, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = -0.1f;
    g_testMax = 0.0f;
    g_testMin = -10.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest066
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest066, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = -9.9f;
    g_testMax = 0.0f;
    g_testMin = -10.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest067
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest067, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = -1.0f;
    g_testMax = -1.0f;
    g_testMin = -10.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest068
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest068, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = -10.0f;
    g_testMax = -1.0f;
    g_testMin = -10.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest069
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest069, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = -50.0f;
    g_testMax = 0.0f;
    g_testMin = -100.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest070
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest070, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = -50.0f;
    g_testMax = -50.0f;
    g_testMin = -50.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest071
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest071, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 100.0f;
    g_testMax = 100.0f;
    g_testMin = 100.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest072
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest072, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 10.0f;
    g_testMin = 0.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest073
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest073, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 10.0f;
    g_testMax = 100.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest074
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest074, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 10.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest075
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest075, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 10.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest076
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest076, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = -10.0f;
    g_testMin = 0.0f;
    g_testMax = 100.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest077
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest077, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 1.0f;
    g_testMin = 10.0f;
    g_testMax = 100.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest078
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest078, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 101.0f;
    g_testMin = 0.0f;
    g_testMax = 100.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}
/**
 * @tc.name: GaugePatternTest079
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest079, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = -1.0f;
    g_testMin = 0.0f;
    g_testMax = 100.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest080
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest080, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = -101.0f;
    g_testMin = -100.0f;
    g_testMax = 0.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest081
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest081, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 1.0f;
    g_testMin = -100.0f;
    g_testMax = 0.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest082
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest082, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = -1.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest083
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest083, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 101.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest084
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest084, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 0.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(MIN, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest085
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest085, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 0.1f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest086
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest086, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = -0.1f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest087
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest087, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 100.0f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest088
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugePatternTestNg, GaugePatternTest088, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    g_testValue = 100.1f;
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_FALSE);
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(ENABLED_FALSE, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}
} // namespace OHOS::Ace::NG