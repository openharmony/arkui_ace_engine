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

class CheckBoxPatternSubTestNG : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    CheckboxBuilderFunc CheckboxBuilder();
};

void CheckBoxPatternSubTestNG::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));

    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
}

void CheckBoxPatternSubTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

CheckboxBuilderFunc CheckBoxPatternSubTestNG::CheckboxBuilder()
{
    return []() {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(10.f));
        ViewAbstract::SetHeight(CalcLength(10.f));
    };
}

/**
 * @tc.name: CheckBoxPatternTest046
 * @tc.desc: Test UpdateIndicator when builder has value and UseContentModifier is true.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest046, TestSize.Level1)
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
    pattern->contentModifierNode_ = frameNode;
    pattern->UpdateIndicator();
    EXPECT_EQ(pattern->builderNode_, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest047
 * @tc.desc: Test UpdateIndicator when UseContentModifier is false.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest047, TestSize.Level1)
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
    pattern->contentModifierNode_ = nullptr;
    pattern->UpdateIndicator();
    EXPECT_EQ(pattern->builderNode_, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest048
 * @tc.desc: Test UpdateIndicator when builder has not value after builder has value.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest048, TestSize.Level1)
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
    pattern->contentModifierNode_ = nullptr;
    pattern->UpdateIndicator();
    EXPECT_NE(pattern->builderNode_, nullptr);
    pattern->builder_ = std::nullopt;
    pattern->UpdateIndicator();
    EXPECT_EQ(pattern->builderNode_, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest049
 * @tc.desc: Test UpdateIndicator when UseContentModifier is true.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest049, TestSize.Level1)
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
    pattern->contentModifierNode_ = nullptr;
    pattern->UpdateIndicator();
    EXPECT_NE(pattern->builderNode_, nullptr);
    pattern->contentModifierNode_ = frameNode;
    pattern->UpdateIndicator();
    EXPECT_EQ(pattern->builderNode_, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest050
 * @tc.desc: Test UpdateIndicator when CheckBoxSelect is false.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest050, TestSize.Level1)
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
    pattern->contentModifierNode_ = frameNode;
    pattern->UpdateIndicator();
    EXPECT_EQ(pattern->builderNode_, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest051
 * @tc.desc: Test LoadBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest051, TestSize.Level1)
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
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto countBefore = host->TotalChildCount();
    pattern->LoadBuilder();
    auto child = frameNode->GetFirstChild();
    auto countAfter = host->TotalChildCount();
    EXPECT_NE(child, nullptr);
    EXPECT_EQ(countBefore, (countAfter-1));
}

/**
 * @tc.name: CheckBoxPatternTest052
 * @tc.desc: Test SetBuilderNodeHidden.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest052, TestSize.Level1)
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
    pattern->LoadBuilder();
    pattern->SetBuilderNodeHidden();
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::GONE);
}

/**
 * @tc.name: CheckBoxPatternTest053
 * @tc.desc: Test SetBuilderNodeHidden.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest053, TestSize.Level1)
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
    pattern->SetBuilderNodeHidden();
    auto layoutProperty = pattern->builderNode_->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest054
 * @tc.desc: Test StartCustomNodeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest054, TestSize.Level1)
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
    const auto& renderContext = pattern->builderNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto opacity = renderContext->GetOpacityValue();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
    EXPECT_NEAR(opacity, 1.0f, DBL_EPSILON);
}

/**
 * @tc.name: CheckBoxPatternTest055
 * @tc.desc: Test StartEnterAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest055, TestSize.Level1)
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
    const auto& renderContext = pattern->builderNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto opacity = renderContext->GetOpacityValue();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
    EXPECT_NEAR(opacity, 1.0f, DBL_EPSILON);
}

/**
 * @tc.name: CheckBoxPatternTest056
 * @tc.desc: Test StartEnterAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest056, TestSize.Level1)
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
    const auto& renderContext = pattern->builderNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto opacity = renderContext->GetOpacityValue();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
    EXPECT_NEAR(opacity, 1.0f, DBL_EPSILON);
    auto eventHub = pattern->builderNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->IsEnabled(), true);
}

/**
 * @tc.name: CheckBoxPatternTest057
 * @tc.desc: Test StartExitAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest057, TestSize.Level1)
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
    const auto& renderContext = pattern->builderNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto opacity = renderContext->GetOpacityValue();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
    EXPECT_NEAR(opacity, 0.0f, DBL_EPSILON);
}

/**
 * @tc.name: CheckBoxPatternTest058
 * @tc.desc: Test StartExitAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest058, TestSize.Level1)
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
    const auto& renderContext = pattern->builderNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto opacity = renderContext->GetOpacityValue();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_NEAR(opacity, 0.0f, DBL_EPSILON);
    auto eventHub = pattern->builderNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->IsEnabled(), true);
}

/**
 * @tc.name: CheckBoxPatternTest059
 * @tc.desc: Test StartExitAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest059, TestSize.Level1)
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
    const auto& renderContext = pattern->builderNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto opacity = renderContext->GetOpacityValue();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
    EXPECT_NEAR(opacity, 0.0f, DBL_EPSILON);
    auto eventHub = pattern->builderNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->IsEnabled(), true);
}

/**
 * @tc.name: CheckBoxPatternTest060
 * @tc.desc: Test StartExitAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest060, TestSize.Level1)
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
    const auto& renderContext = pattern->builderNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto opacity = renderContext->GetOpacityValue();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
    EXPECT_NEAR(opacity, 0.0f, DBL_EPSILON);
    auto eventHub = pattern->builderNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->IsEnabled(), true);
}

/**
 * @tc.name: CheckBoxPatternTest061
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest061, TestSize.Level1)
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
    EXPECT_NE(pattern->paintMethod_->GetContentModifier(paintWrapper), nullptr);
    checkBoxTheme->focusPaintPadding_ = 10.0_px; //10.0_px is value of focusPaintPadding_
    pattern->size_ = SizeF(200, 200); //200 is width of checkbox, 200 is height of checkbox
    pattern->paintMethod_->UpdateContentModifier(paintWrapper);
    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (-10.00, -10.00) - [220.00 x 220.00]");
}

/**
 * @tc.name: CheckBoxPatternTest062
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest062, TestSize.Level1)
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
    EXPECT_NE(pattern->paintMethod_->GetContentModifier(paintWrapper), nullptr);
    checkBoxTheme->focusPaintPadding_ = 10.0_px; //10.0_px is value of focusPaintPadding_
    pattern->size_ = SizeF(200, 200); //200 is width of checkbox, 200 is height of checkbox
    pattern->paintMethod_->UpdateContentModifier(paintWrapper);
    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (-10.00, -10.00) - [220.00 x 220.00]");
}

/**
 * @tc.name: CheckBoxPatternTest063
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternSubTestNG, CheckBoxPatternTest063, TestSize.Level1)
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
    EXPECT_NE(pattern->paintMethod_->GetContentModifier(paintWrapper), nullptr);
    checkBoxTheme->focusPaintPadding_ = 100.0_px; //10.0_px is value of focusPaintPadding_
    pattern->size_ = SizeF(200, 200); //200 is width of checkbox, 200 is height of checkbox
    pattern->paintMethod_->UpdateContentModifier(paintWrapper);
    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (-100.00, -100.00) - [400.00 x 400.00]");
}
} // namespace OHOS::Ace::NG
