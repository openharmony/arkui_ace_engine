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

#include <cmath>
#include <cstddef>
#include <memory>
#include <optional>
#include <vector>

#include "gtest/gtest.h"

#include "base/memory/referenced.h"
#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"

#include "base/memory/ace_type.h"
#include "core/components/progress/progress_theme.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/progress/progress_layout_algorithm.h"
#include "core/components_ng/pattern/progress/progress_layout_property.h"
#include "core/components_ng/pattern/progress/progress_model_ng.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/progress_mask_property.h"
#include "core/components_ng/render/render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

namespace OHOS::Ace::NG {
namespace {
using namespace testing;
using namespace testing::ext;
const InspectorFilter filter;
constexpr double MAX_VALUE = 1.0;
constexpr double MIN_VALUE = 0.0;
constexpr double NEG_VALUE = -1.0;
constexpr double VALUE_OF_PROGRESS = 100.0;
constexpr double NEG_VALUE_OF_PROGRESS = -100.0;
constexpr double MAX_VALUE_OF_PROGRESS = 100000.0;
constexpr double MAX_NEG_VALUE_OF_PROGRESS = -100000.0;
constexpr ProgressType PROGRESS_TYPE_LINEAR = ProgressType::LINEAR;
constexpr ProgressType PROGRESS_TYPE_RING = ProgressType::RING;
constexpr ProgressType PROGRESS_TYPE_SCALE = ProgressType::SCALE;
constexpr ProgressType PROGRESS_TYPE_MOON = ProgressType::MOON;
constexpr int32_t SCALE_COUNT = 120;
constexpr Color FRONT_COLOR = Color(0xff0000ff);
constexpr Color BG_COLOR = Color(0xffc0c0c0);
constexpr float PROGRESS_COMPONENT_WIDTH = 200.0f;
constexpr float PROGRESS_COMPONENT_HEIGHT = 200.0f;
constexpr Dimension TEST_PROGRESS_THICKNESS = 4.0_vp;
constexpr Dimension TEST_PROGRESS_STROKE_WIDTH = 10.0_vp;
constexpr Dimension TEST_PROGRESS_DEFAULT_DIAMETER = 72.0_vp;
constexpr Dimension TEST_PROGRESS_SCALE_WIDTH = 2.0_vp;
const Color TEST_COLOR = Color::BLUE;
const LinearColor TEST_LINEARCOLOR = LinearColor(TEST_COLOR);
const std::vector<std::string> FONT_FAMILY = { "serif" };

ProgressModelNG progressModel;
RefPtr<ProgressTheme> progressTheme;
RefPtr<MockThemeManager> themeManager;
} // namespace

class ProgressConModTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetProgress();
    ProgressModelNG CreateProgress(double value, double max, NG::ProgressType type);

    RefPtr<FrameNode> frameNode_;
    RefPtr<ProgressPattern> pattern_;
    RefPtr<EventHub> eventHub_;
    RefPtr<ProgressLayoutProperty> layoutProperty_;
    RefPtr<ProgressPaintProperty> paintProperty_;
    RefPtr<ProgressAccessibilityProperty> accessibilityProperty_;
};

void ProgressConModTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    progressTheme = AceType::MakeRefPtr<ProgressTheme>();
    progressTheme->trackThickness_ = TEST_PROGRESS_THICKNESS;
    progressTheme->scaleLength_ = TEST_PROGRESS_STROKE_WIDTH;
    progressTheme->ringDiameter_ = TEST_PROGRESS_DEFAULT_DIAMETER;
    progressTheme->trackBgColor_ = BG_COLOR;
    progressTheme->trackSelectedColor_ = FRONT_COLOR;
    progressTheme->scaleNumber_ = SCALE_COUNT;
    progressTheme->scaleWidth_ = TEST_PROGRESS_SCALE_WIDTH;
}

void ProgressConModTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    progressTheme = nullptr;
    themeManager = nullptr;
}

void ProgressConModTestNg::SetUp()
{
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
}

void ProgressConModTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    ClearOldNodes();  // Each testcase will create new node at begin
}

void ProgressConModTestNg::GetProgress()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ProgressPattern>();
    eventHub_ = frameNode_->GetEventHub<EventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<ProgressLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ProgressAccessibilityProperty>();
}

ProgressModelNG ProgressConModTestNg::CreateProgress(double value, double max, NG::ProgressType type)
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ProgressModelNG model;
    model.Create(MIN_VALUE, value, MIN_VALUE, max, type);
    ViewAbstract::SetWidth(CalcLength(PROGRESS_COMPONENT_WIDTH));
    ViewAbstract::SetHeight(CalcLength(PROGRESS_COMPONENT_HEIGHT));
    GetProgress();
    return model;
}

/**
 * @tc.name: ProgressConPatternTest001
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step3. Get ProgressPattern .
     * @tc.expected: step3. Check the pattern not nullptr.
     */
    CreateProgress(MAX_VALUE, MAX_VALUE, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);

    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_VALUE);
        return nullptr;
    };

    /**
     * @tc.steps: step5. Set parameters to pattern builderFunc.
     */
    pattern_->SetBuilderFunc(node);

    /**
     * @tc.steps: step6. call the FireBuilder.
     * @tc.expected: step6. Check the UseContentModifier equal to false.
     */
    pattern_->FireBuilder();
    ASSERT_EQ(pattern_->UseContentModifier(), false);
}

/**
 * @tc.name: ProgressConPatternTest002
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_VALUE, MAX_VALUE, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MAX_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_VALUE);
        EXPECT_EQ(config.total_, MAX_VALUE);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest003
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MIN_VALUE, MAX_VALUE, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MAX_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MIN_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MIN_VALUE);
        EXPECT_EQ(config.total_, MAX_VALUE);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest004
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(NEG_VALUE, MAX_VALUE, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MAX_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to NEG_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, NEG_VALUE);
        EXPECT_EQ(config.total_, MAX_VALUE);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest005
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE, PROGRESS_TYPE_MOON);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MAX_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, MAX_VALUE);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest006
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(NEG_VALUE_OF_PROGRESS, MAX_VALUE, PROGRESS_TYPE_RING);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MAX_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to NEG_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, MAX_VALUE);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest007
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_VALUE_OF_PROGRESS, MAX_VALUE, PROGRESS_TYPE_SCALE);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MAX_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, MAX_VALUE);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest008
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_NEG_VALUE_OF_PROGRESS, MAX_VALUE, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MAX_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_NEG_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, MAX_VALUE);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest009
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_VALUE, MIN_VALUE, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MIN_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_VALUE);
        EXPECT_EQ(config.total_, MIN_VALUE);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest010
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MIN_VALUE, MIN_VALUE, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MIN_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MIN_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MIN_VALUE);
        EXPECT_EQ(config.total_, MIN_VALUE);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest011
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(NEG_VALUE, MIN_VALUE, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MIN_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to NEG_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, NEG_VALUE);
        EXPECT_EQ(config.total_, MIN_VALUE);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest012
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(VALUE_OF_PROGRESS, MIN_VALUE, PROGRESS_TYPE_RING);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MIN_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, MIN_VALUE);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest013
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(NEG_VALUE_OF_PROGRESS, MIN_VALUE, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MIN_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to NEG_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, MIN_VALUE);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest014
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_VALUE_OF_PROGRESS, MIN_VALUE, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MIN_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, MIN_VALUE);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest015
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_NEG_VALUE_OF_PROGRESS, MIN_VALUE, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MIN_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_NEG_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, MIN_VALUE);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest016
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_VALUE, NEG_VALUE, PROGRESS_TYPE_MOON);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(NEG_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_VALUE);
        EXPECT_EQ(config.total_, NEG_VALUE);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest017
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MIN_VALUE, NEG_VALUE, PROGRESS_TYPE_SCALE);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(NEG_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MIN_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MIN_VALUE);
        EXPECT_EQ(config.total_, NEG_VALUE);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest018
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(NEG_VALUE, NEG_VALUE, PROGRESS_TYPE_SCALE);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(NEG_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to NEG_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, NEG_VALUE);
        EXPECT_EQ(config.total_, NEG_VALUE);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest019
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(VALUE_OF_PROGRESS, NEG_VALUE, PROGRESS_TYPE_SCALE);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(NEG_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, NEG_VALUE);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest020
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(NEG_VALUE_OF_PROGRESS, NEG_VALUE, PROGRESS_TYPE_SCALE);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(NEG_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to NEG_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, NEG_VALUE);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest021
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_VALUE_OF_PROGRESS, NEG_VALUE, PROGRESS_TYPE_SCALE);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(NEG_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, NEG_VALUE);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest022
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_NEG_VALUE_OF_PROGRESS, NEG_VALUE, PROGRESS_TYPE_SCALE);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(NEG_VALUE);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_NEG_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, NEG_VALUE);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest023
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_VALUE, VALUE_OF_PROGRESS, PROGRESS_TYPE_SCALE);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_VALUE);
        EXPECT_EQ(config.total_, VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest024
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MIN_VALUE, VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MIN_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MIN_VALUE);
        EXPECT_EQ(config.total_, VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest025
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(NEG_VALUE, VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to NEG_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, NEG_VALUE);
        EXPECT_EQ(config.total_, VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest026
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(VALUE_OF_PROGRESS, VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest027
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(NEG_VALUE_OF_PROGRESS, VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to NEG_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest028
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_VALUE_OF_PROGRESS, VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest029
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_NEG_VALUE_OF_PROGRESS, VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_NEG_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest030
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_VALUE, NEG_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(NEG_VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_VALUE);
        EXPECT_EQ(config.total_, NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest031
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MIN_VALUE, NEG_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(NEG_VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MIN_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MIN_VALUE);
        EXPECT_EQ(config.total_, NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest032
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(NEG_VALUE, NEG_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(NEG_VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to NEG_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, NEG_VALUE);
        EXPECT_EQ(config.total_, NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest033
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(VALUE_OF_PROGRESS, NEG_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(NEG_VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest034
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(NEG_VALUE_OF_PROGRESS, NEG_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(NEG_VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to NEG_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest035
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_VALUE_OF_PROGRESS, NEG_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(NEG_VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest036
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_NEG_VALUE_OF_PROGRESS, NEG_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(NEG_VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_NEG_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest037
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_VALUE, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MAX_VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_VALUE);
        EXPECT_EQ(config.total_, MAX_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest038
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MIN_VALUE, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MAX_VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MIN_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MIN_VALUE);
        EXPECT_EQ(config.total_, MAX_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest039
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(NEG_VALUE, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MAX_VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to NEG_VALUE.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, NEG_VALUE);
        EXPECT_EQ(config.total_, MAX_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest040
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MAX_VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, MAX_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest041
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(NEG_VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MAX_VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to NEG_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, NEG_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, MAX_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, false);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest042
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest042, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
   
    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MAX_VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, MAX_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressConPatternTest043
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressConModTestNg, ProgressConPatternTest043, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    CreateProgress(MAX_VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_SCALE);
    CreateDone(frameNode_);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);

    auto progressPaintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MAX_VALUE_OF_PROGRESS);
    auto pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Init Progress node.
     * @tc.expected: step4. Check the value_ of config is equal to MAX_VALUE_OF_PROGRESS.
     */
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, MAX_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.total_, MAX_VALUE_OF_PROGRESS);
        EXPECT_EQ(config.enabled_, true);
        return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}
} // namespace OHOS::Ace::NG