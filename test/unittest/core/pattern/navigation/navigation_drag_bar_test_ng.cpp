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

#include "gtest/gtest.h"
#include "mock_navigation_route.h"
#include "mock_navigation_stack.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
constexpr float DEFAULT_ROOT_HEIGHT = 800.f;
constexpr float DEFAULT_ROOT_WIDTH = 480.f;
class NavigationDragBarTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
    static void RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width = DEFAULT_ROOT_WIDTH);
    void CreateNavigationModel();
};

void NavigationDragBarTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void NavigationDragBarTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationDragBarTestNg::RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width)
{
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { width, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { width, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { width, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { width, DEFAULT_ROOT_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
}

void NavigationDragBarTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

void NavigationDragBarTestNg::CreateNavigationModel()
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

/**
 * @tc.name: NavigationDragBarTest001
 * @tc.desc: Test create drag bar node task
 * @tc.type: FUNC
 */
HWTEST_F(NavigationDragBarTestNg, NavigationDragBarTest001, TestSize.Level1)
{
    /**
     * @tc.steps: create NavigationGroupNode and dragBar Node.
     * @tc.expected: dragBar and dragBarItem node are not nullptr.
     */
    CreateNavigationModel();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigation, nullptr);
    RefPtr<NavigationPattern> pattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateDragBarNode(navigation);
    auto dragBarNode = AceType::DynamicCast<FrameNode>(navigation->GetDragBarNode());
    EXPECT_NE(dragBarNode, nullptr);
    auto dragBarItemNode = dragBarNode->GetChildAtIndex(0);
    EXPECT_NE(dragBarItemNode, nullptr);
}

/**
 * @tc.name: NavigationDragBarTest002
 * @tc.desc: Test create drag bar task
 * @tc.type: FUNC
 */
HWTEST_F(NavigationDragBarTestNg, NavigationDragBarTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create NavigationGroupNode.
     */
    CreateNavigationModel();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigation, nullptr);
    auto layoutWrapper = navigation->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RefPtr<NavigationPattern> pattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. enableDragBar is true.
     * @tc.expected: dragBar is not nullptr and divider event has been cleared.
     */
    pattern->enableDragBar_ = true;
    pattern->OnModifyDone();
    auto dragBarNode = AceType::DynamicCast<FrameNode>(navigation->GetDragBarNode());
    EXPECT_NE(dragBarNode, nullptr);
    auto panEvent_ = pattern->panEvent_;
    EXPECT_EQ(panEvent_, nullptr);
    auto hoverEvent = pattern->hoverEvent_;
    EXPECT_EQ(hoverEvent, nullptr);

    /**
     * @tc.steps: step3. enableDragBar is false.
     * @tc.expected: dragBar is nullptr and divider event has been reseted.
     */
    pattern->enableDragBar_ = false;
    pattern->OnModifyDone();
    auto dragBarNode1 = AceType::DynamicCast<FrameNode>(navigation->GetDragBarNode());
    EXPECT_EQ(dragBarNode1, nullptr);
    auto panEvent1 = pattern->panEvent_;
    EXPECT_NE(panEvent1, nullptr);
    auto hoverEvent1 = pattern->hoverEvent_;
    EXPECT_NE(hoverEvent1, nullptr);
}

/**
 * @tc.name: NavigationDragBarTest003
 * @tc.desc: Test dragBar measure and layout task
 * @tc.type: FUNC
 */
HWTEST_F(NavigationDragBarTestNg, NavigationDragBarTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create NavigationGroupNode.
     */
    CreateNavigationModel();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigation, nullptr);
    RefPtr<NavigationPattern> pattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step2. enableDragBar is false.
     * @tc.expected: The height and width of drag bar are zero after measured.
     */
    pattern->enableDragBar_ = true;
    pattern->OnModifyDone();
    auto dragBarNode = AceType::DynamicCast<FrameNode>(navigation->GetDragBarNode());
    ASSERT_NE(dragBarNode, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    NavigationDragBarTestNg::RunMeasureAndLayout(layoutWrapper);
    EXPECT_EQ(dragBarNode->GetGeometryNode()->GetFrameSize().Width(), 0.0f);
    EXPECT_EQ(dragBarNode->GetGeometryNode()->GetFrameSize().Height(), 0.0f);
}

/**
 * @tc.name: NavigationDragBarTest004
 * @tc.desc: Test dragBar pan and touch event
 * @tc.type: FUNC
 */
HWTEST_F(NavigationDragBarTestNg, NavigationDragBarTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create NavigationGroupNode and dragBar.
     */
    CreateNavigationModel();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->enableDragBar_ = true;
    navigationPattern->OnModifyDone();
    auto dragBarNode = AceType::DynamicCast<FrameNode>(navigation->GetDragBarNode());
    ASSERT_NE(dragBarNode, nullptr);

    /**
     * @tc.steps: step2. Initialize dragBar pan and touch event.
     * @tc.expected: The gesture events of dragBar are not empty .
     */
    auto eventHub = dragBarNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    navigationPattern->InitDragBarPanEvent(gestureHub);
    auto panEvent = navigationPattern->dragBarPanEvent_;
    EXPECT_NE(panEvent, nullptr);
    navigationPattern->InitTouchEvent(gestureHub);
    auto touchEvent = navigationPattern->touchEvent_;
    EXPECT_NE(touchEvent, nullptr);
}
} // namespace OHOS::Ace::NG