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
#define private public
#define protected public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ref_counter.h"
#include "base/memory/referenced.h"
#include "core/animation/animator.h"
#include "core/animation/curve_animation.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_property.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model_ng.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_paint_method.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"
#include "core/components_ng/pattern/side_bar/side_bar_theme.h"
#include "core/components_v2/extensions/extension.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/base/mock_system_properties.h"
#include "core/components_ng/pattern/navigation/custom_safe_area_expander.h"
#include "core/common/page_viewport_config.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_event_hub.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/pattern/navigation/inner_navigation_controller.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float UPDATE_SIDE_BAR_WIDTH = 240.0f;
} // namespace

class SideBarPatternTestTwoNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SideBarPatternTestTwoNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void SideBarPatternTestTwoNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test SideBar OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestTwoNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);
    auto sideBarLayoutProperty = sideBarFrameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(sideBarLayoutProperty, nullptr);

    sideBarPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(sideBarPattern->dragEvent_, nullptr);
    g_isConfigChangePerform = true;
    sideBarPattern->OnColorConfigurationUpdate();
    EXPECT_NE(sideBarPattern->dragEvent_, nullptr);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SideBarToolBarManager_001
 * @tc.desc: Test ToolbarManager SetToolBarChangeCallback and SetModifyDoneCallback.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestTwoNg, SideBarToolBarManager_001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    SideBarContainerModelNG SideBarContainerModelInstance;
    SideBarContainerModelInstance.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    pattern->frameNode_ = frameNode;
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<SideBarContainerPattern>());
    frameNode->children_.push_back(backButton);

    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SideBarTheme>()));
    EXPECT_CALL(*themeManagerOne, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SideBarTheme>()));

    auto pipelineContext = frameNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto toolBarManager = pipelineContext->GetToolbarManager();
    ASSERT_NE(toolBarManager, nullptr);

    int32_t modifyDoneCallbackCount = 0;
    int32_t toolBarChangeCallback = 0;
    pattern->realDividerWidth_ = 10;
    pattern->realSideBarWidth_ = Dimension(120);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto geometryNode = host->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(200, 200));

    toolBarManager->SetModifyDoneCallback([&modifyDoneCallbackCount]() { modifyDoneCallbackCount++; });
    toolBarManager->SetToolBarChangeCallback([&toolBarChangeCallback]() { toolBarChangeCallback++; });
    pattern->InitToolBarManager();

    auto layoutProperty = pattern->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    pattern->HandleDragUpdate(UPDATE_SIDE_BAR_WIDTH);
    pattern->realSideBarWidth_ = Dimension(120);
    pattern->OnModifyDone();
    pattern->FireSideBarWidthChangeEvent();
    ASSERT_EQ(modifyDoneCallbackCount, 1);
    ASSERT_EQ(toolBarChangeCallback, 4);
    auto sideBarInfo = toolBarManager->GetSideBarInfo();
    ASSERT_TRUE(sideBarInfo.isShow);
    ASSERT_EQ(sideBarInfo.width, 120);
    ASSERT_TRUE(toolBarManager->HasSideBar());
}

/**
 * @tc.name: ShowDialogWithNode001
 * @tc.desc: Test ShowDialogWithNode when dialog is already shown
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestTwoNg, ShowDialogWithNode001, TestSize.Level1)
{
    SideBarPatternTestTwoNg::SetUpTestCase();

    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);

    // Set dialog as already shown
    sideBarPattern->isDialogShow_ = true;

    // Call ShowDialogWithNode - should return early
    sideBarPattern->ShowDialogWithNode();

    // Verify dialog is still shown
    EXPECT_TRUE(sideBarPattern->isDialogShow_);

    SideBarPatternTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: ShowDialogWithNode002
 * @tc.desc: Test ShowDialogWithNode with valid host and button node
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestTwoNg, ShowDialogWithNode002, TestSize.Level1)
{
    SideBarPatternTestTwoNg::SetUpTestCase();

    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);

    // Create button node as last child
    auto buttonNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(buttonNode, nullptr);
    sideBarFrameNode->children_.push_back(buttonNode);

    // Set dialog as not shown
    sideBarPattern->isDialogShow_ = false;

    // Call ShowDialogWithNode
    sideBarPattern->ShowDialogWithNode();

    // Verify dialog is now shown
    EXPECT_TRUE(sideBarPattern->isDialogShow_);

    SideBarPatternTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: ShowDialogWithNode003
 * @tc.desc: Test ShowDialogWithNode with ArkuiAccessibility Text
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestTwoNg, ShowDialogWithNode003, TestSize.Level1)
{
    SideBarPatternTestTwoNg::SetUpTestCase();

    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);

    // Create button node with ArkuiAccessibility property
    auto buttonNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(buttonNode, nullptr);

    // Set ArkuiAccessibility Text
    auto accessibilityProperty = buttonNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetAccessibilityText("Test ArkuiAccessibility Text");

    sideBarFrameNode->children_.push_back(buttonNode);

    // Set dialog as not shown
    sideBarPattern->isDialogShow_ = false;

    // Call ShowDialogWithNode
    sideBarPattern->ShowDialogWithNode();

    // Verify dialog is now shown
    EXPECT_TRUE(sideBarPattern->isDialogShow_);

    SideBarPatternTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: ShowDialogWithNode004
 * @tc.desc: Test ShowDialogWithNode with image info
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestTwoNg, ShowDialogWithNode004, TestSize.Level1)
{
    SideBarPatternTestTwoNg::SetUpTestCase();

    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);

    // Create button node
    auto buttonNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(buttonNode, nullptr);
    sideBarFrameNode->children_.push_back(buttonNode);

    // Set image info
    ImageSourceInfo imageInfo("test_image.png");
    sideBarPattern->imageInfo_ = imageInfo;

    // Set dialog as not shown
    sideBarPattern->isDialogShow_ = false;

    // Call ShowDialogWithNode
    sideBarPattern->ShowDialogWithNode();

    // Verify dialog is now shown
    EXPECT_TRUE(sideBarPattern->isDialogShow_);

    SideBarPatternTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: SideBarContainerPattern_OnColorConfigurationUpdate001
 * @tc.desc: Test OnColorConfigurationUpdate calls UpdateBackgroundStyle
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestTwoNg, SideBarContainerPattern_OnColorConfigurationUpdate001, TestSize.Level1)
{
    SideBarPatternTestTwoNg::SetUpTestCase();

    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);

    // Call OnColorConfigurationUpdate (should not crash)
    sideBarPattern->OnColorConfigurationUpdate();
    SUCCEED();

    SideBarPatternTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: SideBarContainerPattern_OnThemeScopeUpdate001
 * @tc.desc: Test OnThemeScopeUpdate calls UpdateBackgroundStyle and returns false
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestTwoNg, SideBarContainerPattern_OnThemeScopeUpdate001, TestSize.Level1)
{
    SideBarPatternTestTwoNg::SetUpTestCase();

    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);

    bool result = sideBarPattern->OnThemeScopeUpdate(123);
    EXPECT_FALSE(result);

    SideBarPatternTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: SideBarContainerPattern_CustomizeExpandSafeArea001
 * @tc.desc: Test CustomizeExpandSafeArea returns false if host is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestTwoNg, SideBarContainerPattern_CustomizeExpandSafeArea001, TestSize.Level1)
{
    SideBarPatternTestTwoNg::SetUpTestCase();

    auto sideBarPattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);

    // Do not attach to FrameNode, so GetHost() returns nullptr
    bool result = sideBarPattern->CustomizeExpandSafeArea();
    EXPECT_FALSE(result);

    SideBarPatternTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: CustomSafeAreaExpander_RunCustomizeExpandIfNeeded001
 * @tc.desc: RunCustomizeExpandIfNeeded returns false when isCustomExpandRunning_ is true.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestTwoNg, CustomSafeAreaExpander_RunCustomizeExpandIfNeeded001, TestSize.Level1)
{
    SideBarPatternTestTwoNg::SetUpTestCase();
    OHOS::Ace::NG::CustomSafeAreaExpander expander;
    expander.isCustomExpandRunning_ = true;
    auto frameNode = AceType::MakeRefPtr<FrameNode>("TestNode", 1, AceType::MakeRefPtr<Pattern>());
    bool result = expander.RunCustomizeExpandIfNeeded(frameNode);
    EXPECT_FALSE(result);
    SideBarPatternTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: CustomSafeAreaExpander_RunCustomizeExpandIfNeeded002
 * @tc.desc: RunCustomizeExpandIfNeeded returns false when viewportConfig_ is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestTwoNg, CustomSafeAreaExpander_RunCustomizeExpandIfNeeded002, TestSize.Level1)
{
    SideBarPatternTestTwoNg::SetUpTestCase();
    OHOS::Ace::NG::CustomSafeAreaExpander expander;
    expander.isCustomExpandRunning_ = false;
    expander.viewportConfig_ = nullptr;
    auto frameNode = AceType::MakeRefPtr<FrameNode>("TestNode", 2, AceType::MakeRefPtr<Pattern>());
    bool result = expander.RunCustomizeExpandIfNeeded(frameNode);
    EXPECT_FALSE(result);
    SideBarPatternTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: CustomSafeAreaExpander_RunCustomizeExpandIfNeeded003
 * @tc.desc: RunCustomizeExpandIfNeeded returns true when all conditions are met.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestTwoNg, CustomSafeAreaExpander_RunCustomizeExpandIfNeeded003, TestSize.Level1)
{
    SideBarPatternTestTwoNg::SetUpTestCase();
    OHOS::Ace::NG::CustomSafeAreaExpander expander;
    expander.isCustomExpandRunning_ = false;
    // Use default PageViewportConfig from the project, no need to mock
    expander.viewportConfig_ = AceType::MakeRefPtr<OHOS::Ace::PageViewportConfig>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>("TestNode", 3, AceType::MakeRefPtr<Pattern>());
    bool result = expander.RunCustomizeExpandIfNeeded(frameNode);
    EXPECT_TRUE(result);
    EXPECT_FALSE(expander.isCustomExpandRunning_);
    SideBarPatternTestTwoNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG