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

#include "gtest/gtest.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
using CheckboxBuilderFunc = std::optional<std::function<void()>>;

namespace OHOS::Ace::NG {
namespace {
const std::string NAME = "checkbox";
const std::string GROUP_NAME = "checkboxGroup";
const std::string TAG = "CHECKBOX_TAG";
} // namespace

class CheckBoxPatternTestNG : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    CheckboxBuilderFunc CheckboxBuilder();
};

void CheckBoxPatternTestNG::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));

    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
}

void CheckBoxPatternTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

CheckboxBuilderFunc CheckBoxPatternTestNG::CheckboxBuilder()
{
    return []() {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(10.f));
        ViewAbstract::SetHeight(CalcLength(10.f));
    };
}

/**
 * @tc.name: CheckBoxPatternTest001
 * @tc.desc: Test UpdateIndicator when builder has value.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->builder_ = checkBoxFunc;
    pattern->UpdateIndicator();
    EXPECT_TRUE(pattern->builder_.has_value());
}

/**
 * @tc.name: CheckBoxPatternTest002
 * @tc.desc: Test UpdateIndicator when builder has not value.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->builder_ = std::nullopt;
    pattern->UpdateIndicator();
    EXPECT_FALSE(pattern->builder_.has_value());
}

/**
 * @tc.name: CheckBoxPatternTest003
 * @tc.desc: Test UpdateIndicator when UseContentModifier is true.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->contentModifierNode_ = frameNode;
    pattern->UpdateIndicator();
    EXPECT_EQ(pattern->builderNode_, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest004
 * @tc.desc: Test UpdateIndicator when UseContentModifier is true.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->contentModifierNode_ = frameNode;
    pattern->UpdateIndicator();
    EXPECT_EQ(pattern->builderNode_, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest005
 * @tc.desc: Test UpdateIndicator when UseContentModifier is false.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(pattern, nullptr);
    paintProperty->UpdateCheckBoxSelect(true);
    pattern->builder_ = checkBoxFunc;
    pattern->UpdateIndicator();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(pattern->builderNode_, nullptr);
    EXPECT_NE(layoutProperty->GetVisibility(), VisibleType::GONE);
}

/**
 * @tc.name: CheckBoxPatternTest006
 * @tc.desc: Test UpdateIndicator when CheckBoxSelect is false.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(pattern, nullptr);
    paintProperty->UpdateCheckBoxSelect(false);
    pattern->builder_ = checkBoxFunc;
    pattern->UpdateIndicator();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(pattern->builderNode_, nullptr);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::GONE);
}

/**
 * @tc.name: CheckBoxPatternTest007
 * @tc.desc: Test UpdateIndicator when CheckBoxSelect is null.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(pattern, nullptr);
    pattern->builder_ = checkBoxFunc;
    pattern->UpdateIndicator();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(pattern->builderNode_, nullptr);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::GONE);
}

/**
 * @tc.name: CheckBoxPatternTest008
 * @tc.desc: Test UpdateIndicator when UseContentModifier is false.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(pattern, nullptr);
    paintProperty->UpdateCheckBoxSelect(true);
    pattern->builder_ = checkBoxFunc;
    pattern->UpdateIndicator();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    auto visibility = layoutProperty->GetVisibility();
    auto child = frameNode->GetFirstChild();
    EXPECT_NE(pattern->builderNode_, nullptr);
    EXPECT_NE(visibility, VisibleType::GONE);
    EXPECT_NE(child, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest009
 * @tc.desc: Test UpdateIndicator when UseContentModifier is false.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(pattern, nullptr);
    paintProperty->UpdateCheckBoxSelect(true);
    pattern->UpdateIndicator();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    auto visibility = layoutProperty->GetVisibility();
    auto child = frameNode->GetFirstChild();
    EXPECT_NE(pattern->builderNode_, nullptr);
    EXPECT_NE(visibility, VisibleType::GONE);
    EXPECT_NE(child, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest010
 * @tc.desc: Test UpdateIndicator when CheckBoxSelect is false.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(pattern, nullptr);
    paintProperty->UpdateCheckBoxSelect(false);
    pattern->builder_ = checkBoxFunc;
    pattern->UpdateIndicator();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(pattern->builderNode_, nullptr);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::GONE);
}

/**
 * @tc.name: CheckBoxPatternTest011
 * @tc.desc: Test UpdateIndicator when CheckBoxSelect is null.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(pattern, nullptr);
    pattern->builder_ = checkBoxFunc;
    pattern->UpdateIndicator();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(pattern->builderNode_, nullptr);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::GONE);
}

/**
 * @tc.name: CheckBoxPatternTest012
 * @tc.desc: Test LoadBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->builder_ = checkBoxFunc;
    pattern->LoadBuilder();
    EXPECT_NE(pattern->builderNode_, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest013
 * @tc.desc: Test LoadBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->builder_ = checkBoxFunc;
    pattern->LoadBuilder();
    auto child = frameNode->GetFirstChild();
    EXPECT_NE(pattern->builderNode_, nullptr);
    EXPECT_NE(child, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest014
 * @tc.desc: Test LoadBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->LoadBuilder();
    auto child = frameNode->GetFirstChild();
    EXPECT_EQ(pattern->builderNode_, nullptr);
    EXPECT_EQ(child, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest015
 * @tc.desc: Test LoadBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->LoadBuilder();
    auto child = frameNode->GetFirstChild();
    EXPECT_NE(pattern->builderNode_, nullptr);
    EXPECT_NE(child, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest016
 * @tc.desc: Test SetBuilderNodeHidden.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    pattern->SetBuilderNodeHidden();
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::GONE);
}

/**
 * @tc.name: CheckBoxPatternTest017
 * @tc.desc: Test SetBuilderNodeHidden.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetBuilderNodeHidden();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest018
 * @tc.desc: Test StartCustomNodeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->StartCustomNodeAnimation(true);
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::GONE);
}

/**
 * @tc.name: CheckBoxPatternTest019
 * @tc.desc: Test StartCustomNodeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = false;
    pattern->StartCustomNodeAnimation(true);
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: CheckBoxPatternTest020
 * @tc.desc: Test StartCustomNodeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = true;
    pattern->StartCustomNodeAnimation(true);
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: CheckBoxPatternTest021
 * @tc.desc: Test StartCustomNodeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->StartCustomNodeAnimation(true);
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto eventHub = pattern->builderNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->IsEnabled(), true);
}

/**
 * @tc.name: CheckBoxPatternTest022
 * @tc.desc: Test StartCustomNodeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = false;
    pattern->StartCustomNodeAnimation(true);
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
    auto eventHub = pattern->builderNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->IsEnabled(), true);
}

/**
 * @tc.name: CheckBoxPatternTest023
 * @tc.desc: Test StartCustomNodeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = true;
    pattern->StartCustomNodeAnimation(true);
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
    auto eventHub = pattern->builderNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->IsEnabled(), true);
}

/**
 * @tc.name: CheckBoxPatternTest024
 * @tc.desc: Test StartCustomNodeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = true;
    pattern->StartCustomNodeAnimation(false);
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: CheckBoxPatternTest025
 * @tc.desc: Test StartCustomNodeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->StartCustomNodeAnimation(false);
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto eventHub = pattern->builderNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->IsEnabled(), true);
}
/**
 * @tc.name: CheckBoxPatternTest026
 * @tc.desc: Test StartCustomNodeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = false;
    pattern->StartCustomNodeAnimation(false);
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
    auto eventHub = pattern->builderNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(eventHub->IsEnabled(), true);
}

/**
 * @tc.name: CheckBoxPatternTest027
 * @tc.desc: Test StartCustomNodeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = true;
    pattern->StartCustomNodeAnimation(false);
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
    auto eventHub = pattern->builderNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->IsEnabled(), true);
}

/**
 * @tc.name: CheckBoxPatternTest028
 * @tc.desc: Test StartEnterAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = true;
    pattern->StartEnterAnimation();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: CheckBoxPatternTest029
 * @tc.desc: Test StartCustomNodeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->StartEnterAnimation();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto eventHub = pattern->builderNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->IsEnabled(), true);
}

/**
 * @tc.name: CheckBoxPatternTest030
 * @tc.desc: Test StartEnterAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = false;
    pattern->StartEnterAnimation();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
    auto eventHub = pattern->builderNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->IsEnabled(), true);
}

/**
 * @tc.name: CheckBoxPatternTest031
 * @tc.desc: Test StartEnterAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = true;
    pattern->StartEnterAnimation();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
    auto eventHub = pattern->builderNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->IsEnabled(), true);
}

/**
 * @tc.name: CheckBoxPatternTest032
 * @tc.desc: Test StartExitAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = true;
    pattern->StartExitAnimation();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: CheckBoxPatternTest033
 * @tc.desc: Test StartExitAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->StartExitAnimation();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto eventHub = pattern->builderNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->IsEnabled(), true);
}
/**
 * @tc.name: CheckBoxPatternTest034
 * @tc.desc: Test StartExitAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = false;
    pattern->StartExitAnimation();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
    auto eventHub = pattern->builderNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->IsEnabled(), true);
}

/**
 * @tc.name: CheckBoxPatternTest035
 * @tc.desc: Test StartExitAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = true;
    pattern->StartExitAnimation();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
    auto eventHub = pattern->builderNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->IsEnabled(), true);
}

/**
 * @tc.name: CheckBoxPatternTest036
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = true;
    pattern->StartExitAnimation();
    pattern->paintMethod_ = AceType::MakeRefPtr<CheckBoxPaintMethod>();

    /**
     * @tc.steps: step3. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkBoxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_NE(pattern->paintMethod_->GetContentModifier(paintWrapper), nullptr);
    pattern->size_ = SizeF(200, 200); //200 is width of checkbox, 200 is height of checkbox
    pattern->paintMethod_->UpdateContentModifier(paintWrapper);
    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (0.00, 0.00) - [200.00 x 200.00]");
}

/**
 * @tc.name: CheckBoxPatternTest037
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = true;
    pattern->StartExitAnimation();
    pattern->paintMethod_ = AceType::MakeRefPtr<CheckBoxPaintMethod>();

    /**
     * @tc.steps: step3. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkBoxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_NE(pattern->paintMethod_->GetContentModifier(paintWrapper), nullptr);
    pattern->offset_ = OffsetF(1, 1);
    pattern->size_ = SizeF(200, 200); //200 is width of checkbox, 200 is height of checkbox
    pattern->paintMethod_->UpdateContentModifier(paintWrapper);
    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (1.00, 1.00) - [200.00 x 200.00]");
}

/**
 * @tc.name: CheckBoxPatternTest038
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = true;
    pattern->StartExitAnimation();
    pattern->paintMethod_ = AceType::MakeRefPtr<CheckBoxPaintMethod>();

    /**
     * @tc.steps: step3. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkBoxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_NE(pattern->paintMethod_->GetContentModifier(paintWrapper), nullptr);
    checkBoxTheme->focusPaintPadding_ = 10.0_px; //10.0_px is value of focusPaintPadding_
    pattern->offset_ = OffsetF(1, 1);
    pattern->size_ = SizeF(200, 200); //200 is width of checkbox, 200 is height of checkbox
    pattern->paintMethod_->UpdateContentModifier(paintWrapper);
    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (-9.00, -9.00) - [220.00 x 220.00]");
}

/**
 * @tc.name: CheckBoxPatternTest039
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = true;
    pattern->StartExitAnimation();
    pattern->paintMethod_ = AceType::MakeRefPtr<CheckBoxPaintMethod>();

    /**
     * @tc.steps: step3. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkBoxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_NE(pattern->paintMethod_->GetContentModifier(paintWrapper), nullptr);
    checkBoxTheme->focusPaintPadding_ = 10.0_px; //10.0_px is value of focusPaintPadding_
    pattern->offset_ = OffsetF(1, 1);
    pattern->size_ = SizeF(100, 150); //100 is width of checkbox, 150 is height of checkbox
    pattern->paintMethod_->UpdateContentModifier(paintWrapper);
    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (-9.00, -9.00) - [120.00 x 170.00]");
}

/**
 * @tc.name: CheckBoxPatternTest040
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = true;
    pattern->StartExitAnimation();
    pattern->paintMethod_ = AceType::MakeRefPtr<CheckBoxPaintMethod>();

    /**
     * @tc.steps: step3. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkBoxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_NE(pattern->paintMethod_->GetContentModifier(paintWrapper), nullptr);
    checkBoxTheme->focusPaintPadding_ = 10.0_px; //10.0_px is value of focusPaintPadding_
    pattern->offset_ = OffsetF(20, 30); //20 is x offset of checkbox, 30 is y offset of checkbox
    pattern->size_ = SizeF(100, 150); //100 is width of checkbox, 150 is height of checkbox
    pattern->paintMethod_->UpdateContentModifier(paintWrapper);
    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (10.00, 20.00) - [120.00 x 170.00]");
}

/**
 * @tc.name: CheckBoxPatternTest041
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = false;
    pattern->StartExitAnimation();
    pattern->paintMethod_ = AceType::MakeRefPtr<CheckBoxPaintMethod>();

    /**
     * @tc.steps: step3. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkBoxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_NE(pattern->paintMethod_->GetContentModifier(paintWrapper), nullptr);
    checkBoxTheme->focusPaintPadding_ = 10.0_px; //10.0_px is value of focusPaintPadding_
    pattern->offset_ = OffsetF(20, 30); //20 is x offset of checkbox, 30 is y offset of checkbox
    pattern->size_ = SizeF(100, 150); //100 is width of checkbox, 150 is height of checkbox
    pattern->paintMethod_->UpdateContentModifier(paintWrapper);
    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (10.00, 20.00) - [120.00 x 170.00]");
}

/**
 * @tc.name: CheckBoxPatternTest042
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = false;
    pattern->StartExitAnimation();
    pattern->paintMethod_ = AceType::MakeRefPtr<CheckBoxPaintMethod>();

    /**
     * @tc.steps: step3. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkBoxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_NE(pattern->paintMethod_->GetContentModifier(paintWrapper), nullptr);
    checkBoxTheme->focusPaintPadding_ = 10.0_px; //10.0_px is value of focusPaintPadding_
    pattern->offset_ = OffsetF(20, 30); //20 is x offset of checkbox, 30 is y offset of checkbox
    pattern->size_ = SizeF(100, 150); //100 is width of checkbox, 150 is height of checkbox
    pattern->paintMethod_->UpdateContentModifier(paintWrapper);
    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (10.00, 20.00) - [120.00 x 170.00]");
}

/**
 * @tc.name: CheckBoxPatternTest043
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = false;
    pattern->StartExitAnimation();
    pattern->paintMethod_ = AceType::MakeRefPtr<CheckBoxPaintMethod>();

    /**
     * @tc.steps: step3. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkBoxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_NE(pattern->paintMethod_->GetContentModifier(paintWrapper), nullptr);
    checkBoxTheme->focusPaintPadding_ = 10.0_px; //10.0_px is value of focusPaintPadding_
    pattern->offset_ = OffsetF(1, 1);
    pattern->size_ = SizeF(200, 200); //200 is width of checkbox, 200 is height of checkbox
    pattern->paintMethod_->UpdateContentModifier(paintWrapper);
    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (-9.00, -9.00) - [220.00 x 220.00]");
}

/**
 * @tc.name: CheckBoxPatternTest044
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = false;
    pattern->StartExitAnimation();
    pattern->paintMethod_ = AceType::MakeRefPtr<CheckBoxPaintMethod>();

    /**
     * @tc.steps: step3. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkBoxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_NE(pattern->paintMethod_->GetContentModifier(paintWrapper), nullptr);
    pattern->size_ = SizeF(200, 200); //200 is width of checkbox, 200 is height of checkbox
    pattern->paintMethod_->UpdateContentModifier(paintWrapper);
    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (0.00, 0.00) - [200.00 x 200.00]");
}

/**
 * @tc.name: CheckBoxPatternTest045
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTestNG, CheckBoxPatternTest045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFirstCreated_ = true;
    pattern->StartExitAnimation();
    pattern->paintMethod_ = AceType::MakeRefPtr<CheckBoxPaintMethod>();

    /**
     * @tc.steps: step3. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkBoxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_NE(pattern->paintMethod_->GetContentModifier(paintWrapper), nullptr);
    checkBoxTheme->focusPaintPadding_ = 100.0_px; //10.0_px is value of focusPaintPadding_
    pattern->offset_ = OffsetF(-5, -5); //-5 is value of offset_
    pattern->size_ = SizeF(200, 200); //200 is width of checkbox, 200 is height of checkbox
    pattern->paintMethod_->UpdateContentModifier(paintWrapper);
    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (-105.00, -105.00) - [400.00 x 400.00]");
}
} // namespace OHOS::Ace::NG
