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
float g_testValue = 0.0f;
float g_testMax = 0.0f;
float g_testMin = 0.0f;
} // namespace

class GaugeBuilderTestNg : public TestNG {
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

void GaugeBuilderTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_PROGRESS);
    auto progressTheme = ProgressTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
}

void GaugeBuilderTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void GaugeBuilderTestNg::SetUp() {}

void GaugeBuilderTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void GaugeBuilderTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<GaugePattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<GaugeLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<GaugePaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<GaugeAccessibilityProperty>();
}

void GaugeBuilderTestNg::Create(float values, float min, float max, const std::function<void(GaugeModelNG)>& callback)
{
    GaugeModelNG model;
    model.Create(values, min, max);
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushUITasks(frameNode_);
}

/**
 * @tc.name: GaugePatternTest002
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest002, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest003
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest003, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest004
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest004, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest005
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest005, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest006
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest006, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest007
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest007, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest008
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest008, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest009
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest009, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest010
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest010, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest011
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest011, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest012
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest012, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest013
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest013, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest014
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest014, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(MAX, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest015
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest015, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest016
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest016, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest017
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest017, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest018
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest018, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest019
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest019, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest020
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest020, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest021
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest021, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest022
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest022, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest023
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest023, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
        EXPECT_EQ(g_testMax, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest024
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest024, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest025
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest025, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest026
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest026, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(MIN, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest027
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest027, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest028
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest028, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest029
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest029, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePatternTest030
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest030, TestSize.Level1)
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
    gaugePaintProperty->UpdateValue(g_testValue);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}
/**
 * @tc.name: GaugePatternTest031
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest031, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
 * @tc.name: GaugePatternTest032
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest032, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
 * @tc.name: GaugePatternTest033
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest033, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
 * @tc.name: GaugePatternTest034
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest034, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
 * @tc.name: GaugePatternTest035
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest035, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
 * @tc.name: GaugePatternTest036
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest036, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
 * @tc.name: GaugePatternTest037
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest037, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
 * @tc.name: GaugePatternTest038
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest038, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
 * @tc.name: GaugePatternTest039
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest039, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
 * @tc.name: GaugePatternTest040
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest040, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
 * @tc.name: GaugePatternTest041
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest041, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
 * @tc.name: GaugePatternTest042
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest042, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
 * @tc.name: GaugePatternTest043
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest043, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_TRUE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMin(g_testMin);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(g_testMin, config.min_);
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
 * @tc.name: GaugePatternTest044
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest044, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(ENABLED_TRUE);
    gaugePaintProperty->UpdateValue(g_testValue);
    gaugePaintProperty->UpdateMax(g_testMax);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(g_testValue, config.value_);
        EXPECT_EQ(MIN, config.min_);
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
 * @tc.name: GaugePatternTest045
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest045, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
 * @tc.name: GaugePatternTest046
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest046, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
 * @tc.name: GaugePatternTest047
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest047, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
 * @tc.name: GaugePatternTest048
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest048, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
 * @tc.name: GaugePatternTest049
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeBuilderTestNg, GaugePatternTest049, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::EventHub>();
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
} // namespace OHOS::Ace::NG