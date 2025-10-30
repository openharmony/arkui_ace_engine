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

class CheckBoxPatternTwoTestNG : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    CheckboxBuilderFunc CheckboxBuilder();
};

void CheckBoxPatternTwoTestNG::SetUpTestSuite()
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

void CheckBoxPatternTwoTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

CheckboxBuilderFunc CheckBoxPatternTwoTestNG::CheckboxBuilder()
{
    return []() {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(10.f));
        ViewAbstract::SetHeight(CalcLength(10.f));
    };
}


/**
 * @tc.name: CheckBoxPatternTest042
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTwoTestNG, CheckBoxPatternTest042, TestSize.Level1)
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
HWTEST_F(CheckBoxPatternTwoTestNG, CheckBoxPatternTest043, TestSize.Level1)
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
HWTEST_F(CheckBoxPatternTwoTestNG, CheckBoxPatternTest044, TestSize.Level1)
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
HWTEST_F(CheckBoxPatternTwoTestNG, CheckBoxPatternTest045, TestSize.Level1)
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

/**
 * @tc.name: CheckBoxPatternTest046
 * @tc.desc: Test CheckBox OnDetachFromFrameNodeMultiThread.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTwoTestNG, CheckBoxPatternTest046, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnDetachFromFrameNodeMultiThread();
}

/**
 * @tc.name: CheckBoxPatternTest047
 * @tc.desc: Test CheckBox OnDetachFromMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTwoTestNG, CheckBoxPatternTest047, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnDetachFromMainTree();
}

/**
 * @tc.name: CheckBoxPatternTest048
 * @tc.desc: Test CheckBox OnDetachFromMainTreeMultiThread.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTwoTestNG, CheckBoxPatternTest048, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnDetachFromMainTreeMultiThread(frameNode);
}

/**
 * @tc.name: InitDefaultMarginTest001
 * @tc.desc: Test Checkbox InitDefaultMargin.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTwoTestNG, InitDefaultMarginTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. make builderFunc
     */
    auto buildFunc = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> { return nullptr; };
    /**
     * @tc.steps: step3. set builder func and call InitDefaultMargin.
     * @tc.expected: step3. margin property is null.
     */
    checkBoxModelNG.SetIsUserSetMargin(true);
    pattern->SetBuilderFunc(buildFunc);
    pattern->InitDefaultMargin();
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty->GetMarginProperty(), nullptr);
    /**
     * @tc.steps: step4. clear builderFunc and call InitDefaultMargin.
     * @tc.expected: step4. margin property is not null.
     */
    checkBoxModelNG.SetIsUserSetMargin(false);
    pattern->InitDefaultMargin();
    EXPECT_NE(layoutProperty->GetMarginProperty(), nullptr);
    pattern->SetBuilderFunc(nullptr);
    pattern->InitDefaultMargin();
    EXPECT_NE(layoutProperty->GetMarginProperty(), nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest049
 * @tc.desc: Test CheckBox OnAttachToFrameNodeMultiThread.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTwoTestNG, CheckBoxPatternTest049, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNodeMultiThread(frameNode);
}

/**
 * @tc.name: CheckBoxPatternTest050
 * @tc.desc: Test CheckBox OnAttachToMainTreeMultiThread.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxPatternTwoTestNG, CheckBoxPatternTest050, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnAttachToMainTreeMultiThread(frameNode);
}
} // namespace OHOS::Ace::NG
