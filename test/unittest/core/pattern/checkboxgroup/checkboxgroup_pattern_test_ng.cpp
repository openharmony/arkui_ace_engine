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
#include <optional>
#include <string>
#include <utility>

#include "gtest/gtest.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components/checkable/checkable_component.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkbox/checkbox_model.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_method.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"

#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/pipeline/base/render_node.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string CHECKBOXGROUP_NAME = "checkboxGroup";
const Color DEFAULT_COLOR = Color::BLACK;
} // namespace

class CheckBoxGroupPatternTestNG : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CheckBoxGroupPatternTestNG::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
}

void CheckBoxGroupPatternTestNG::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void CheckBoxGroupPatternTestNG::SetUp() {}

void CheckBoxGroupPatternTestNG::TearDown() {}

/**
 * @tc.name: CheckBoxGroupPatternTest001
 * @tc.desc: Test CheckBoxGroup.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPatternTestNG, CheckBoxGroupPatternTest001, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Init CheckBoxGroup model
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(CHECKBOXGROUP_NAME);

    /**
     * @tc.steps: step2. Set parameters to CheckBoxGroup property
     */
    checkBoxGroupModelNG.SetCheckboxGroupStyle(CheckBoxStyle::SQUARE_STYLE);

    /**
     * @tc.steps: step3. Get paint property and get CheckBox property
     * @tc.expected: Check the CheckBox property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto parintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(parintProperty, nullptr);
    EXPECT_EQ(parintProperty->GetCheckBoxGroupSelectedStyle(), CheckBoxStyle::SQUARE_STYLE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupPatternTest002
 * @tc.desc: Test OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPatternTestNG, CheckBoxGroupPatternTest002, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Init CheckBoxGroup model
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(CHECKBOXGROUP_NAME);

    /**
     * @tc.steps: step2 Create frameNode
     * @tc.expected: Create successfully.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());

    /**
     * @tc.steps: step3. Call OnDirtyLayoutWrapperSwap
     */
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    EXPECT_NE(pattern, nullptr);
    DirtySwapConfig config;
    config.skipLayout = false;
    config.skipMeasure = false;
    EXPECT_TRUE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config.skipLayout, config.skipMeasure));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupPatternTest003
 * @tc.desc: Test CheckBoxGroupIsTrue.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPatternTestNG, CheckBoxGroupPatternTest003, TestSize.Level1)
{
    /*
     * @tc.steps: step1. create checkBoxFrameNode and some parameters.
     */
    auto child1 = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<CheckBoxPattern>());
    auto checkboxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    checkboxPaintProperty->UpdateCheckBoxSelect(true);
    child1->paintProperty_ = checkboxPaintProperty;
    auto checkBoxeventHub = AceType::MakeRefPtr<CheckBoxEventHub>();
    checkBoxeventHub->SetGroupName(CHECKBOXGROUP_NAME);
    child1->eventHub_ = checkBoxeventHub;

    /**
     * @tc.steps: step2 Create checkBoxPattern
     * @tc.expected: Create successfully.
     */
    auto checkBoxPattern = AceType::MakeRefPtr<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    checkBoxPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(child1));
    EXPECT_NE(checkBoxPattern->GetHost(), nullptr);

    /*
     * @tc.steps: step3. create stageManager.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<CheckBoxPattern>());
    auto pageNode = AceType::MakeRefPtr<FrameNode>("STAGE", 0, AceType::MakeRefPtr<CheckBoxPattern>());
    auto pageEventHub = AceType::MakeRefPtr<NG::PageEventHub>();
    auto groupManager = pageEventHub->GetGroupManager();
    pageNode->eventHub_ = pageEventHub;

    stageNode->AddChild(pageNode);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    pipelineContext->stageManager_ = stageManager;

    /*
     * @tc.steps: step4. create list with Children
     */
    auto checkBoxGroupPattern = AceType::MakeRefPtr<CheckBoxGroupPattern>();
    checkBoxPattern->groupManager_ = GroupManager::GetGroupManager();
    checkBoxGroupPattern->groupManager_ = GroupManager::GetGroupManager();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::CHECKBOXGROUP_ETS_TAG, 2, checkBoxGroupPattern);

    auto groupPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    groupPaintProperty->isCheckBoxCallbackDealed_ = true;
    frameNode->paintProperty_ = groupPaintProperty;
    groupManager->AddCheckBoxGroup(CHECKBOXGROUP_NAME, frameNode);
    auto child2 = AceType::MakeRefPtr<FrameNode>("test3", 3, AceType::MakeRefPtr<Pattern>());
    auto paintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    paintProperty->UpdateCheckBoxSelect(true);
    child2->paintProperty_ = paintProperty;
    groupManager->AddCheckBoxToGroup(CHECKBOXGROUP_NAME, child2);
    ElementRegister::GetInstance()->itemMap_[2] = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ElementRegister::GetInstance()->itemMap_[3] = AceType::WeakClaim(AceType::RawPtr(child1));
    ElementRegister::GetInstance()->itemMap_[4] = AceType::WeakClaim(AceType::RawPtr(child2));

    /*
     * @tc.steps: step5. call CheckBoxGroupIsTrue,
     * @tc.expected: groupPaintProperty.GetIsCheckBoxCallbackDealed() is true and exit error
     */
    checkBoxPattern->CheckBoxGroupIsTrue();
    EXPECT_TRUE(groupPaintProperty->GetIsCheckBoxCallbackDealed());
    CheckBoxStyle style;
    checkBoxGroupPattern->GetCheckBoxGroupStyle(child2, style);
    EXPECT_EQ(style, CheckBoxStyle::CIRCULAR_STYLE);
    /*
     * @tc.steps: step6. set CheckBoxSelect is false and call CheckBoxGroupIsTrue
     * @tc.expected: GetSelectStatus is NONE
     */
    groupPaintProperty->isCheckBoxCallbackDealed_ = false;
    checkboxPaintProperty->UpdateCheckBoxSelect(false);

    checkBoxPattern->CheckBoxGroupIsTrue();
    EXPECT_EQ(groupPaintProperty->GetSelectStatus(), CheckBoxGroupPaintProperty::SelectStatus::NONE);
}

/**
 * @tc.name: CheckBoxGroupPatternTest004
 * @tc.desc: Test OnColorConfigurationUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPatternTestNG, CheckBoxGroupPatternTest004, TestSize.Level1)
{
    /*
     * @tc.steps: step1. create CheckBoxGroup model.
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(CHECKBOXGROUP_NAME);

    /**
     * @tc.steps: step2 Create frameNode and pattern
     * @tc.expected: Create successfully.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Create mock theme manager
     * @tc.expected: create successfully.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<CheckboxTheme>();
    ASSERT_NE(theme, nullptr);
    theme->inactiveColor_ = DEFAULT_COLOR;
    theme->pointColor_ = DEFAULT_COLOR;
    theme->activeColor_ = DEFAULT_COLOR;

    /*
     * @tc.steps: step3. call OnColorConfigurationUpdate
     * @tc.expected: SelectedColor, UnSelectedColor and MarkColor are Color::BLACK.
     */
    pattern->OnColorConfigurationUpdate();
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupSelectedColor(), DEFAULT_COLOR);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupCheckMarkColor(), DEFAULT_COLOR);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupUnSelectedColor(), DEFAULT_COLOR);
}

/**
 * @tc.name: CheckBoxGroupPatternTest005
 * @tc.desc: Test OnClick
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPatternTestNG, CheckBoxGroupPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup model
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(CHECKBOXGROUP_NAME);

    /**
     * @tc.steps: step2 Create frameNode and pattern
     * @tc.expected: Create successfully.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto host = pattern->GetHost();
    /**
     * @tc.steps: step3. Call OnClick
     * @tc.expected: updateFlag_ is false
     */
    pattern->OnClick();
    EXPECT_FALSE(pattern->updateFlag_);
}

/**
 * @tc.name: CheckBoxGroupPatternTest006
 * @tc.desc: Test UpdateCheckBoxStyle.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPatternTestNG, CheckBoxGroupPatternTest006, TestSize.Level1)
{
    /*
     * @tc.steps: step1. create checkBoxFrameNode and some parameters.
     */
    auto child = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<CheckBoxPattern>());
    auto checkboxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    child->paintProperty_ = checkboxPaintProperty;
    auto checkBoxEventHub = AceType::MakeRefPtr<CheckBoxEventHub>();
    checkBoxEventHub->SetEnabled(false);
    checkBoxEventHub->SetGroupName(CHECKBOXGROUP_NAME);
    checkBoxEventHub->SetEnabled(true);

    /**
     * @tc.steps: step2 Create pattern
     * @tc.expected: Create successfully.
     */
    auto checkBoxPattern = AceType::MakeRefPtr<CheckBoxPattern>();
    checkBoxPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(child));
    EXPECT_NE(checkBoxPattern->GetHost(), nullptr);

    /*
     * @tc.steps: step3. create stageManager.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<CheckBoxPattern>());
    auto pageNode = AceType::MakeRefPtr<FrameNode>("STAGE", 0, AceType::MakeRefPtr<CheckBoxPattern>());
    auto pageEventHub = AceType::MakeRefPtr<NG::PageEventHub>();
    auto groupManager = pageEventHub->GetGroupManager();
    pageNode->eventHub_ = pageEventHub;

    stageNode->AddChild(pageNode);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    pipelineContext->stageManager_ = stageManager;

    /*
     * @tc.steps: step4. create list with Children
     */
    auto checkBoxGroupPattern = AceType::MakeRefPtr<CheckBoxGroupPattern>();
    checkBoxPattern->groupManager_ = GroupManager::GetGroupManager();
    checkBoxGroupPattern->groupManager_ = GroupManager::GetGroupManager();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::CHECKBOXGROUP_ETS_TAG, 2, checkBoxGroupPattern);
    auto checkBoxGroupEventHub = AceType::MakeRefPtr<CheckBoxGroupEventHub>();
    checkBoxGroupEventHub->SetGroupName(CHECKBOXGROUP_NAME);
    checkBoxGroupEventHub->SetEnabled(false);
    frameNode->eventHub_ = checkBoxGroupEventHub;

    auto groupPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    groupPaintProperty->isCheckBoxCallbackDealed_ = true;
    frameNode->paintProperty_ = groupPaintProperty;
    groupManager->AddCheckBoxGroup(CHECKBOXGROUP_NAME, frameNode);

    ElementRegister::GetInstance()->itemMap_[2] = AceType::WeakClaim(AceType::RawPtr(child));
    ElementRegister::GetInstance()->itemMap_[3] = nullptr;

    /*
     * @tc.steps: step5. call UpdateCheckBoxStyle
     * @tc.expected: IsEnabled is true
     */
    checkBoxGroupPattern->UpdateCheckBoxStyle();
    EXPECT_TRUE(checkBoxEventHub->IsEnabled());
}

/**
 * @tc.name: CheckBoxGroupPatternTest007
 * @tc.desc: Test OnDetachFromFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPatternTestNG, CheckBoxGroupPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup model
     */
    CheckBoxGroupModelNG checkBoxModelNG;
    checkBoxModelNG.Create(CHECKBOXGROUP_NAME);

    /**
     * @tc.steps: step2 Create frameNode and pattern
     * @tc.expected: Create successfully.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    EXPECT_NE(pattern, nullptr);

    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    FrameNode& ref = *stageNode;
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext->stageManager_, nullptr);
    auto child = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    pipelineContext->stageManager_->stageNode_ = frameNode;
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<PageEventHub>();
    EXPECT_NE(eventHub, nullptr);
    child->eventHub_ = eventHub;
    frameNode->AddChild(child);

    /**
     * @tc.steps: step3 Call OnDetachFromFrameNode
     * @tc.expected: stageNode_ isn't null.
     */
    pattern->OnDetachFromFrameNode(&ref);
    EXPECT_NE(stageManager->stageNode_, nullptr);
}

/**
 * @tc.name: CheckBoxGroupPatternTest008
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPatternTestNG, CheckBoxGroupPatternTest008, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /*
     * @tc.steps: step1. Create CheckBoxGroup model.
     */
    CheckBoxGroupModelNG checkBoxModelNG;
    checkBoxModelNG.Create(CHECKBOXGROUP_NAME);

    /**
     * @tc.steps: step2 Create frameNode
     * @tc.expected: Create successfully.
     */

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. Set parameters to CheckBoxGroup property
     */
    auto groupPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    groupPaintProperty->UpdateCheckBoxGroupSelectedStyle(CheckBoxStyle::CIRCULAR_STYLE);
    frameNode->paintProperty_ = groupPaintProperty;
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    EXPECT_NE(pattern, nullptr);
    RefPtr<EventHub> eventHub = AccessibilityManager::MakeRefPtr<EventHub>();
    RefPtr<FocusHub> focusHub = AccessibilityManager::MakeRefPtr<FocusHub>(eventHub, FocusType::DISABLE, false);
    pattern->InitOnKeyEvent(focusHub);

    /*
     * @tc.steps: step4. Call GetInnerFocusPaintRect.
     */
    RoundRect paintRect;
    pattern->GetInnerFocusPaintRect(paintRect);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: PreventDefault001
 * @tc.desc: test InitTouchEvent and InitClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPatternTestNG, PreventDefault001, TestSize.Level1)
{
    /*
     * @tc.steps: step1. Create CheckBoxGroup model.
     */
    CheckBoxGroupModelNG checkBoxModelNG;
    checkBoxModelNG.Create(CHECKBOXGROUP_NAME);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Mock TouchEventInfo info and set preventDefault to true
     * @tc.expected: Check the param value
     */
    pattern->InitTouchEvent();
    TouchEventInfo touchInfo("onTouch");
    TouchLocationInfo touchDownInfo(1);
    touchDownInfo.SetTouchType(TouchType::DOWN);
    touchInfo.SetPreventDefault(true);
    touchInfo.SetSourceDevice(SourceType::TOUCH);
    touchInfo.AddTouchLocationInfo(std::move(touchDownInfo));
    ASSERT_NE(pattern->touchListener_, nullptr);
    pattern->touchListener_->callback_(touchInfo);
    EXPECT_TRUE(pattern->isTouchPreventDefault_);
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::PRESS);
    /**
     * @tc.steps: step3.Mock GestureEvent info and set preventDefault to true
     * @tc.expected: Check the param value
     */
    pattern->InitClickEvent();
    GestureEvent clickInfo;
    clickInfo.SetSourceDevice(SourceType::TOUCH);
    clickInfo.SetPreventDefault(true);
    ASSERT_NE(pattern->clickListener_, nullptr);
    pattern->clickListener_->operator()(clickInfo);
    EXPECT_FALSE(pattern->isTouchPreventDefault_);
}

/**
 * @tc.name: PreventDefault002
 * @tc.desc: test InitTouchEvent and InitClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPatternTestNG, PreventDefault002, TestSize.Level1)
{
    /*
     * @tc.steps: step1. Create CheckBoxGroup model.
     */
    CheckBoxGroupModelNG checkBoxModelNG;
    checkBoxModelNG.Create(CHECKBOXGROUP_NAME);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Mock TouchEvent info and set preventDefault to false
     * @tc.expected: Check the param value
     */
    pattern->InitTouchEvent();
    TouchEventInfo touchInfo("onTouch");
    TouchLocationInfo touchDownInfo(1);
    touchDownInfo.SetTouchType(TouchType::DOWN);
    touchInfo.SetPreventDefault(false);
    touchInfo.SetSourceDevice(SourceType::TOUCH);
    touchInfo.AddTouchLocationInfo(std::move(touchDownInfo));
    ASSERT_NE(pattern->touchListener_, nullptr);
    pattern->touchListener_->callback_(touchInfo);
    EXPECT_EQ(touchInfo.IsPreventDefault(), pattern->isTouchPreventDefault_);
    /**
     * @tc.steps: step3. Mock GestureEvent info and set preventDefault to false
     * @tc.expected: Check the param value
     */
    pattern->InitClickEvent();
    GestureEvent clickInfo;
    clickInfo.SetSourceDevice(SourceType::TOUCH);
    clickInfo.SetPreventDefault(false);
    ASSERT_NE(pattern->clickListener_, nullptr);
    pattern->clickListener_->operator()(clickInfo);
    EXPECT_FALSE(pattern->isTouchPreventDefault_);
}
} // namespace OHOS::Ace::NG
