/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#include "test/mock/adapter/mock_uisession_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/page_transition_effect.h"
#include "core/components_ng/pattern/stage/page_transition_model_ng.h"
#include "core/components_ng/pattern/stage/stage_layout_algorithm.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/pipeline/base/element_register.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string CHECK_STRING = "check";
const std::string TEST_GROUP_NAME = "testGroup";
const std::string ERROR_GROUP_NAME = "errorGroup";
const std::string FRAME_NODE_TAG = "testFrameNode";
const std::string TEST_ANIMATOR_ID = "testAnimatorId";
constexpr int32_t RADIO_ID_FIRST = 1;
constexpr int32_t RADIO_ID_SECOND = 2;
constexpr int32_t RADIO_ID_THIRD = 3;
constexpr int32_t CHECK_BOX_ID_FIRST = 4;
constexpr int32_t CHECK_BOX_ID_THIRD = 6;
constexpr int32_t CHECK_BOX_ID_FOURTH = 6;
constexpr int32_t TEST_CONTAINER_ID = 100;
constexpr int32_t AT_LEAST_TIME = 1;
const float NOPADDING = 0.0f;
const float RK356_WIDTH = 720.0f;
constexpr float RK356_HEIGHT = 1136.0f;
const float ROW_HEIGHT = 120.0f;
const SizeF CONTAINER_SIZE { RK356_WIDTH, RK356_HEIGHT };
int32_t flag = 0;
std::function<void()> FLAG_FUNC = []() { flag++; };
} // namespace

RefPtr<LayoutWrapperNode> CreatChildlayoutWrapper()
{
    auto firstFrameNode = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<StagePattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    return firstLayoutWrapper;
}

class StageTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        auto pipeline = AceType::DynamicCast<NG::MockPipelineContext>(PipelineBase::GetCurrentContext());
        auto stageNode = FrameNode::CreateFrameNode(
            V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
        pipeline->sharedTransitionManager_ = AceType::MakeRefPtr<SharedOverlayManager>(stageNode);
        MockContainer::SetUp();
        EXPECT_CALL(*MockContainer::Current(), WindowIsShow())
            .Times(testing::AtLeast(AT_LEAST_TIME))
            .WillRepeatedly(Return(true));
        ContainerScope::UpdateCurrent(TEST_CONTAINER_ID);
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
    void SetUp()
    {
        flag = 0;
    }
    void TearDown() {}
};

/**
 * @tc.name: PageEventHubTest001
 * @tc.desc: Testing Radio Correlation Functions of PageEventHub work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PageEventHubTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a PageEventHub.
     */
    PageEventHub pageEventHub;
    auto groupManager = pageEventHub.GetGroupManager();
    ASSERT_NE(groupManager, nullptr);
    groupManager->UpdateRadioGroupValue(TEST_GROUP_NAME, RADIO_ID_FIRST);

    /**
     * @tc.steps: step2. Add radio to group.
     * @tc.expected: The HasRadioId function of PageEventHub meets expectations .
     */
    groupManager->AddRadioToGroup(TEST_GROUP_NAME, RADIO_ID_FIRST);
    EXPECT_TRUE(groupManager->HasRadioId(TEST_GROUP_NAME, RADIO_ID_FIRST));
    EXPECT_FALSE(groupManager->HasRadioId(ERROR_GROUP_NAME, RADIO_ID_FIRST));

    /**
     * @tc.steps: step3. Add another two radio to group.
     * @tc.expected: The HasRadioId function of PageEventHub meets expectations .
     */
    groupManager->AddRadioToGroup(TEST_GROUP_NAME, RADIO_ID_SECOND);
    groupManager->AddRadioToGroup(TEST_GROUP_NAME, RADIO_ID_THIRD);

    /**
     * @tc.steps: step4. Create real node and fake node to ElementRegister.
     */
    auto radioPattern = AceType::MakeRefPtr<RadioPattern>();
    auto radioNode = FrameNode::CreateFrameNode(FRAME_NODE_TAG, RADIO_ID_FIRST, radioPattern);
    ElementRegister::GetInstance()->AddReferenced(RADIO_ID_FIRST, radioNode);
    auto checkBoxGroup = AceType::MakeRefPtr<CheckBoxGroupPattern>();
    auto checkBoxGroupNode = FrameNode::CreateFrameNode(FRAME_NODE_TAG, RADIO_ID_SECOND, checkBoxGroup);
    ElementRegister::GetInstance()->AddReferenced(RADIO_ID_SECOND, checkBoxGroupNode);

    /**
     * @tc.steps: step5. UpdateRadioGroupValue.
     */
    groupManager->UpdateRadioGroupValue(TEST_GROUP_NAME, RADIO_ID_FIRST);
    groupManager->UpdateRadioGroupValue(TEST_GROUP_NAME, RADIO_ID_SECOND);

    /**
     * @tc.steps: step6. RemoveRadioFromGroup.
     * @tc.expected: The radio remove successful .
     */
    groupManager->RemoveRadioFromGroup(TEST_GROUP_NAME, RADIO_ID_FIRST);
    EXPECT_FALSE(groupManager->HasRadioId(TEST_GROUP_NAME, RADIO_ID_FIRST));
}

/**
 * @tc.name: PageEventHubTest002
 * @tc.desc: Testing CheckBox Correlation Functions of PageEventHub work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PageEventHubTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a PageEventHub.
     * @tc.expected: The CheckBoxGroupMap size meets expectations .
     */
    PageEventHub pageEventHub;
    auto groupManager = pageEventHub.GetGroupManager();
    EXPECT_EQ(groupManager->GetCheckboxList(TEST_GROUP_NAME).size(), 0);

    /**
     * @tc.steps: step2. build error pattern and add to the group.
     * @tc.expected: The CheckBoxGroupMap[TEST_GROUP_NAME] has the error pattern.
     */
    auto errorPattern = AceType::MakeRefPtr<RadioPattern>();
    auto errorNode = FrameNode::CreateFrameNode(V2::CHECKBOXGROUP_ETS_TAG, CHECK_BOX_ID_FIRST, errorPattern);
    ElementRegister::GetInstance()->AddReferenced(CHECK_BOX_ID_FIRST, errorNode);
    groupManager->RemoveCheckBoxGroup(TEST_GROUP_NAME, CHECK_BOX_ID_FIRST);
    groupManager->AddCheckBoxGroup(TEST_GROUP_NAME, errorNode);
    EXPECT_EQ(groupManager->GetCheckboxGroup(TEST_GROUP_NAME), nullptr);

    /**
     * @tc.steps: step3. remove error pattern.
     * @tc.expected: The CheckBoxGroupMap[TEST_GROUP_NAME] has the error pattern.
     */
    ElementRegister::GetInstance()->RemoveItem(CHECK_BOX_ID_FIRST);
    groupManager->RemoveCheckBoxGroup(TEST_GROUP_NAME, CHECK_BOX_ID_FIRST);
    EXPECT_EQ(groupManager->GetCheckboxGroup(TEST_GROUP_NAME), nullptr);

    /**
     * @tc.steps: step4. add real checkBoxGroup and add to the group.
     * @tc.expected: add success.
     */
    auto checkBoxGroup = AceType::MakeRefPtr<CheckBoxGroupPattern>();
    auto checkBoxGroupNode = FrameNode::CreateFrameNode(V2::CHECKBOXGROUP_ETS_TAG, CHECK_BOX_ID_THIRD, checkBoxGroup);
    ElementRegister::GetInstance()->AddReferenced(CHECK_BOX_ID_THIRD, checkBoxGroupNode);
    groupManager->AddCheckBoxGroup(TEST_GROUP_NAME, checkBoxGroupNode);
    EXPECT_NE(groupManager->GetCheckboxGroup(TEST_GROUP_NAME), nullptr);

    /**
     * @tc.steps: step5. add checkBox to group
     * @tc.expected: add success.
     */
    groupManager->AddCheckBoxGroup(TEST_GROUP_NAME, nullptr);
    EXPECT_NE(groupManager->GetCheckboxGroup(TEST_GROUP_NAME), nullptr);

    /**
     * @tc.steps: step6. remove the checkBoxGroup from group.
     * @tc.expected: remove success.
     */
    ElementRegister::GetInstance()->RemoveItem(CHECK_BOX_ID_THIRD);
    groupManager->RemoveCheckBoxGroup(TEST_GROUP_NAME, CHECK_BOX_ID_THIRD);
    EXPECT_EQ(groupManager->GetCheckboxGroup(TEST_GROUP_NAME), nullptr);

    /**
     * @tc.steps: step7. add checkBoxGroup to group again.
     * @tc.expected: add success.
     */
    ElementRegister::GetInstance()->AddReferenced(CHECK_BOX_ID_THIRD, checkBoxGroupNode);
    groupManager->AddCheckBoxGroup(TEST_GROUP_NAME, nullptr);
    EXPECT_EQ(groupManager->GetCheckboxGroup(TEST_GROUP_NAME), nullptr);

    /**
     * @tc.steps: step8. build second checkBoxGroup to group.
     * @tc.expected: add fail.
     */
    auto checkBoxGroup2 = AceType::MakeRefPtr<CheckBoxGroupPattern>();
    auto checkBoxGroupNode2 =
        FrameNode::CreateFrameNode(V2::CHECKBOXGROUP_ETS_TAG, CHECK_BOX_ID_FOURTH, checkBoxGroup2);
    ElementRegister::GetInstance()->AddReferenced(CHECK_BOX_ID_FOURTH, checkBoxGroupNode2);
    groupManager->RemoveCheckBoxFromGroup(TEST_GROUP_NAME, CHECK_BOX_ID_FOURTH);
    EXPECT_EQ(groupManager->GetCheckboxGroup(TEST_GROUP_NAME), nullptr);
}

/**
 * @tc.name: PageEventHubTest003
 * @tc.desc: Testing CheckBox Correlation Functions of PageEventHub work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PageEventHubTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a PageEventHub.
     * @tc.expected: The CheckBoxGroupMap size meets expectations .
     */
    PageEventHub pageEventHub;
    auto groupManager = pageEventHub.GetGroupManager();
    EXPECT_EQ(groupManager->GetCheckboxList(TEST_GROUP_NAME).size(), 0);

    /**
     * @tc.steps: step2. add real checkBoxGroup and add to the group.
     * @tc.expected: add success.
     */
    auto checkBoxGroup = AceType::MakeRefPtr<CheckBoxGroupPattern>();
    auto checkBoxGroupNode = FrameNode::CreateFrameNode("CheckboxGroup2", CHECK_BOX_ID_FIRST, checkBoxGroup);
    ElementRegister::GetInstance()->AddReferenced(CHECK_BOX_ID_FIRST, checkBoxGroupNode);
    groupManager->AddCheckBoxGroup(TEST_GROUP_NAME, checkBoxGroupNode);
    EXPECT_NE(groupManager->GetCheckboxGroup(TEST_GROUP_NAME), nullptr);

    /**
     * @tc.steps: step3. add checkBoxGroup to group
     * @tc.expected: add success.
     */
    auto checkBoxGroupNode2 = FrameNode::CreateFrameNode(V2::CHECKBOXGROUP_ETS_TAG, CHECK_BOX_ID_FIRST, checkBoxGroup);
    ElementRegister::GetInstance()->AddReferenced(12, checkBoxGroupNode2);
    groupManager->AddCheckBoxGroup(TEST_GROUP_NAME, checkBoxGroupNode2);
    ASSERT_NE(groupManager->GetCheckboxGroup(TEST_GROUP_NAME), nullptr);
    EXPECT_NE(groupManager->GetCheckboxGroup(TEST_GROUP_NAME)->GetTag(), V2::CHECKBOXGROUP_ETS_TAG);
}

/**
 * @tc.name: StageManagerTest001
 * @tc.desc: Testing PushPage and PopPage Function of StageManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, StageManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StagePattern and some PagePattern.
     */
    auto stageNode = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto firstNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto secondNode =
        FrameNode::CreateFrameNode("2", 2, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto thirdNode =
        FrameNode::CreateFrameNode("3", 3, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto fourthNode =
        FrameNode::CreateFrameNode("4", 4, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));

    /**
     * @tc.steps: step2. Create a StageManager based on stageNode.
     */
    StageManager stageManager(stageNode);

    /**
     * @tc.steps: step3. PopPage.
     * @tc.expected: Expected no child failed.
     */
    EXPECT_FALSE(stageManager.PopPage(nullptr));

    /**
     * @tc.steps: step4. Push a Page into StageManager.
     * @tc.expected: Push successfully.
     */
    EXPECT_TRUE(stageManager.PushPage(firstNode));

    /**
     * @tc.steps: step5. Push another three Page with different parameters into StageManager.
     * @tc.expected: Push successfully.
     */
    stageManager.PushPage(secondNode, false, false);
    stageManager.PushPage(thirdNode, true, false);
    stageManager.stageNode_->GetGeometryNode()->SetFrameSize(SizeF(1.0f, 1.0f));
    stageManager.PushPage(fourthNode, false, true);
    EXPECT_EQ(stageNode->GetChildren().size(), 4);

    /**
     * @tc.steps: step6. Push an exist page.
     * @tc.expected: StageNode size not changed.
     */
    stageManager.PushPage(secondNode);
    EXPECT_EQ(stageNode->GetChildren().size(), 4);

    /**
     * @tc.steps: step7. PopPage with different parameters.
     * @tc.expected: removeChild meets expectations .
     */
    stageManager.SetSrcPage(fourthNode);
    stageManager.PopPage(thirdNode, false, false);
    EXPECT_EQ(stageNode->GetChildren().size(), 3);
    stageManager.SetSrcPage(thirdNode);
    stageManager.PopPage(secondNode, false, false);
    EXPECT_EQ(stageNode->GetChildren().size(), 2);

    // children.size() < 2
    stageManager.SetSrcPage(secondNode);
    stageManager.PopPage(firstNode, false, false);
    EXPECT_EQ(stageNode->GetChildren().size(), 1);
}

/**
 * @tc.name: StageManagerTest002
 * @tc.desc: Testing PopPageToIndex function of StageManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, StageManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StagePattern and some PagePattern.
     */
    auto stageNode = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto firstNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto secondNode =
        FrameNode::CreateFrameNode("2", 2, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto thirdNode =
        FrameNode::CreateFrameNode("3", 3, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto fourthNode =
        FrameNode::CreateFrameNode("4", 4, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    StageManager stageManager(stageNode);

    /**
     * @tc.steps: step2. Calling PopPageToIndex function.
     * @tc.expected: Children are empty and return false
     */
    EXPECT_FALSE(stageManager.PopPageToIndex(1));

    /**
     * @tc.steps: step3. Add first child node and recall PopPageToIndex.
     * @tc.expected: Children length is less than the current index and return false
     */
    stageManager.PushPage(firstNode);
    stageManager.SetSrcPage(firstNode);
    EXPECT_FALSE(stageManager.PopPageToIndex(1));

    /**
     * @tc.steps: step4. Add second child node and recall PopPageToIndex.
     * @tc.expected: Children length is equal to the current index and return true
     */
    stageManager.PushPage(secondNode);
    stageManager.SetSrcPage(secondNode);
    EXPECT_TRUE(stageManager.PopPageToIndex(1));

    /**
     * @tc.steps: step5. Add third child node and recall PopPageToIndex.
     * @tc.expected: stageManager child size meets expectations.
     */
    stageManager.PushPage(thirdNode);
    stageManager.PushPage(fourthNode);
    stageManager.SetSrcPage(fourthNode);
    stageManager.PopPageToIndex(1);
    EXPECT_EQ(stageNode->GetChildren().size(), 2);
    stageManager.SetSrcPage(secondNode);
    stageManager.PopPageToIndex(0);
    EXPECT_EQ(stageNode->GetChildren().size(), 1);

    /**
     * @tc.steps: step6. Add third child node and recall PopPageToIndex.
     * @tc.expected: return true
     */
    stageManager.PushPage(thirdNode);
    stageManager.PushPage(fourthNode);
    stageManager.SetSrcPage(fourthNode);
    EXPECT_TRUE(stageManager.PopPageToIndex(1, false, false));
}

/**
 * @tc.name: StageManagerTest003
 * @tc.desc: Testing CleanPageStack Function of StageManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, StageManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StagePattern and PagePattern.
     */
    auto stageNode = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto firstNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto secondNode =
        FrameNode::CreateFrameNode("2", 2, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    StageManager stageManager(stageNode);

    /**
     * @tc.steps: step2. Call CleanPageStack function.
     * @tc.expected:Children just one and return false
     */
    stageManager.PushPage(firstNode);
    EXPECT_FALSE(stageManager.CleanPageStack());

    /**
     * @tc.steps: step3. Add second child node and recall CleanPageStack.
     * @tc.expected: return true
     */
    stageManager.PushPage(secondNode);
    EXPECT_TRUE(stageManager.CleanPageStack());
}

/**
 * @tc.name: StageManagerTest004
 * @tc.desc: Testing GetLastPage and MovePageToFront Function of StageManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, StageManagerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StagePattern and some PagePattern.
     */
    auto stageNode = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto firstNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto secondNode =
        FrameNode::CreateFrameNode("2", 2, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));

    /**
     * @tc.steps: step2. Create a StageManager based on stageNode.
     */
    StageManager stageManager(stageNode);

    /**
     * @tc.steps: step3. Calling the GetLastPage function.
     * @tc.expected: The manager GetLastPage return null.
     */
    EXPECT_EQ(stageManager.GetLastPage(), nullptr);

    /**
     * @tc.steps: step4. Calling the MovePageToFront function.
     * @tc.expected: return false.
     */
    EXPECT_FALSE(stageManager.MovePageToFront(firstNode));

    /**
     * @tc.steps: step5. StateManager put a page and recall MovePageToFront.
     * @tc.expected: return true.
     */
    stageManager.PushPage(firstNode);
    EXPECT_TRUE(stageManager.MovePageToFront(firstNode));

    /**
     * @tc.steps: step6. StateManager another page and recall MovePageToFront with different params.
     * @tc.expected: always return true.
     */
    stageManager.PushPage(secondNode);
    EXPECT_TRUE(stageManager.MovePageToFront(firstNode, false, true));
    EXPECT_TRUE(stageManager.MovePageToFront(secondNode, true, false));

    /**
     * @tc.steps: step7. Calling the GetLastPage function.
     * @tc.expected: The secondNode is last page.
     */
    EXPECT_EQ(stageManager.GetLastPage(), secondNode);
}
/**
 * @tc.name: StageManagerTest005
 * @tc.desc: Testing ReloadStage Function of StageManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, StageManagerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a StageManager.
     */
    auto stageNode = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    StageManager stageManager(stageNode);

    /**
     * @tc.steps: step2. call ReloadStage.
     */
    stageManager.ReloadStage();

    /**
     * @tc.steps: step3. Create FrameNode and fake CustomNode.
     */
    auto firstNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    stageManager.PushPage(firstNode);
    auto secondNode = AceType::MakeRefPtr<CustomNode>(2, "2");
    secondNode->MountToParent(stageNode);

    /**
     * @tc.steps: step4. call ReloadStage.
     * @tc.expected: stageNode children size not changed
     */
    stageManager.ReloadStage();
    EXPECT_EQ(stageNode->GetChildren().size(), 2);
}

/**
 * @tc.name: StageManagerTest006
 * @tc.desc: Testing PushPage and PopPage Function of StageManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, StageManagerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StagePattern and some PagePattern.
     */
    auto stageNode = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto firstNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto secondNode =
        FrameNode::CreateFrameNode("2", 2, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto thirdNode =
        FrameNode::CreateFrameNode("3", 3, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto fourthNode =
        FrameNode::CreateFrameNode("4", 4, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));

    /**
     * @tc.steps: step2. Create a StageManager based on stageNode.
     */
    StageManager stageManager(stageNode);
    stageManager.PushPage(firstNode);
    stageManager.PushPage(secondNode);
    stageManager.PushPage(thirdNode);
    stageManager.PushPage(fourthNode);
    EXPECT_EQ(stageNode->GetChildren().size(), 4);

    /**
     * @tc.steps: step3. Create outPageNode and inPageNode.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    const auto& children = stageManager.stageNode_->GetChildren();
    bool needTransition = true;
    auto pageNode = children.back();
    const size_t transitionPageSize = 2;
    needTransition &= (children.size() >= transitionPageSize);
    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }
    stageManager.FirePageHide(pageNode, needTransition ? PageTransitionType::EXIT_POP : PageTransitionType::NONE);
    RefPtr<FrameNode> inPageNode;
    if (children.size() >= transitionPageSize) {
        auto newPageNode = *(++children.rbegin());
        stageManager.FirePageShow(
            newPageNode, needTransition ? PageTransitionType::ENTER_POP : PageTransitionType::NONE);
        inPageNode = AceType::DynamicCast<FrameNode>(newPageNode);
    }
    auto outPageNode = AceType::DynamicCast<FrameNode>(pageNode);

    /**
     * @tc.steps: step4. Call StartTransition,with route type NONE..
     * @tc.expected: Start Successful.
     */
    stageManager.SetSrcPage(outPageNode);
    stageManager.StartTransition(outPageNode, inPageNode, RouteType::NONE);
    inPageNode->OnAccessibilityEvent(AccessibilityEventType::CHANGE);
    EXPECT_EQ(stageManager.srcPageNode_, outPageNode);
    EXPECT_EQ(stageManager.destPageNode_, inPageNode);

    /**
     * @tc.steps: step5. Call StartTransition with route type POP.
     * @tc.expected: Start Successful. and call ui session on OnRouterChange with "routerPopPage".
     */
    MockUiSessionManager* mockUiSessionManager =
        reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());
    EXPECT_CALL(*mockUiSessionManager, OnRouterChange(_, "routerPopPage")).Times(testing::AtLeast(AT_LEAST_TIME));
    stageManager.StartTransition(outPageNode, inPageNode, RouteType::POP);

    /**
     * @tc.steps: step6. Call StartTransition with route type PUSH.
     * @tc.expected: Start Successful. and call ui session on OnRouterChange with "routerPushPage".
     */
    EXPECT_CALL(*mockUiSessionManager, OnRouterChange(_, "routerPushPage")).Times(testing::AtLeast(AT_LEAST_TIME));
    stageManager.StartTransition(outPageNode, inPageNode, RouteType::PUSH);
}

/**
 * @tc.name: StageManagerTest007
 * @tc.desc: Testing PushPage and PopPage Function of StageManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, StageManagerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StagePattern and some PagePattern.
     */
    auto stageNode = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto firstNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto secondNode =
        FrameNode::CreateFrameNode("2", 2, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto thirdNode =
        FrameNode::CreateFrameNode("3", 3, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto fourthNode =
        FrameNode::CreateFrameNode("4", 4, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));

    /**
     * @tc.steps: step2. Create a StageManager based on stageNode.
     */
    StageManager stageManager(stageNode);

    /**
     * @tc.steps: step3. PopPage.
     * @tc.expected: Expected no child failed.
     */
    EXPECT_FALSE(stageManager.PopPage(nullptr));

    /**
     * @tc.steps: step4. Push a Page into StageManager.
     * @tc.expected: Push successfully.
     */
    EXPECT_TRUE(stageManager.PushPage(firstNode));

    /**
     * @tc.steps: step5. Push another three Page with different parameters into StageManager.
     * @tc.expected: Push successfully.
     */
    stageManager.PushPage(secondNode, false, false);
    stageManager.PushPage(thirdNode, true, false);
    stageManager.stageNode_->GetGeometryNode()->SetFrameSize(SizeF(1.0f, 1.0f));
    stageManager.PushPage(fourthNode, false, true);
    EXPECT_EQ(stageNode->GetChildren().size(), 4);

    /**
     * @tc.steps: step6. Push an exist page.
     * @tc.expected: StageNode size not changed.
     */
    stageManager.PushPage(secondNode);
    EXPECT_EQ(stageNode->GetChildren().size(), 4);

    /**
     * @tc.steps: step7. PopPage with different parameters.
     * @tc.expected: removeChild meets expectations .
     */
    stageManager.SetSrcPage(fourthNode);
    bool bResult = stageManager.PopPage(thirdNode, true, true);
    EXPECT_EQ(stageNode->GetChildren().size(), 3);
    EXPECT_TRUE(bResult);
}

/**
 * @tc.name: StageManagerTest008
 * @tc.desc: Testing PushPage and PopPage Function of StageManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, StageManagerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StagePattern and some PagePattern.
     */
    auto stageNode = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto firstNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto secondNode =
        FrameNode::CreateFrameNode("2", 2, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto thirdNode =
        FrameNode::CreateFrameNode("3", 3, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto fourthNode =
        FrameNode::CreateFrameNode("4", 4, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));

    /**
     * @tc.steps: step2. Create a StageManager based on stageNode.
     */
    StageManager stageManager(stageNode);

    /**
     * @tc.steps: step3. PopPage.
     * @tc.expected: Expected no child failed.
     */
    EXPECT_FALSE(stageManager.PopPage(nullptr));

    /**
     * @tc.steps: step4. Push a Page into StageManager.
     * @tc.expected: Push successfully.
     */
    EXPECT_TRUE(stageManager.PushPage(firstNode));

    /**
     * @tc.steps: step5. Push another three Page with different parameters into StageManager.
     * @tc.expected: Push successfully.
     */
    stageManager.PushPage(secondNode, false, false);
    stageManager.PushPage(thirdNode, true, false);
    stageManager.stageNode_->GetGeometryNode()->SetFrameSize(SizeF(10.0f, 10.0f));
    stageManager.PushPage(fourthNode, false, true);
    EXPECT_EQ(stageNode->GetChildren().size(), 4);

    /**
     * @tc.steps: step6. Push an exist page.
     * @tc.expected: StageNode size not changed.
     */
    stageManager.PushPage(secondNode);
    EXPECT_EQ(stageNode->GetChildren().size(), 4);

    /**
     * @tc.steps: step7. PopPage with different parameters.
     * @tc.expected: removeChild meets expectations .
     */
    stageManager.SetSrcPage(fourthNode);
    bool bResult = stageManager.PopPage(thirdNode, true, true);
    EXPECT_EQ(stageNode->GetChildren().size(), 3);
    EXPECT_TRUE(bResult);
    stageManager.SetSrcPage(thirdNode);
    stageManager.PopPage(secondNode, true, false);
    EXPECT_EQ(stageNode->GetChildren().size(), 2);
}

/**
 * @tc.name: StageManagerTest009
 * @tc.desc: Testing PushPage and PopPage Function of StageManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, StageManagerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StagePattern and some PagePattern.
     */
    auto stageNode = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto firstNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto secondNode =
        FrameNode::CreateFrameNode("2", 2, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto thirdNode =
        FrameNode::CreateFrameNode("3", 3, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto fourthNode =
        FrameNode::CreateFrameNode("4", 4, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));

    /**
     * @tc.steps: step2. Create a StageManager based on stageNode.
     */
    StageManager stageManager(stageNode);

    /**
     * @tc.steps: step3. PopPage.
     * @tc.expected: Expected no child failed.
     */
    EXPECT_FALSE(stageManager.PopPage(nullptr));

    /**
     * @tc.steps: step4. Push a Page into StageManager.
     * @tc.expected: Push successfully.
     */
    EXPECT_TRUE(stageManager.PushPage(firstNode));

    /**
     * @tc.steps: step5. Push another three Page with different parameters into StageManager.
     * @tc.expected: Push successfully.
     */
    stageManager.PushPage(secondNode, false, false);
    stageManager.PushPage(thirdNode, true, false);
    stageManager.stageNode_->GetGeometryNode()->SetFrameSize(SizeF(1.0f, 1.0f));
    stageManager.PushPage(fourthNode, false, true);
    EXPECT_EQ(stageNode->GetChildren().size(), 4);

    /**
     * @tc.steps: step6. Push an exist page.
     * @tc.expected: StageNode size not changed.
     */
    stageManager.PushPage(secondNode);
    EXPECT_EQ(stageNode->GetChildren().size(), 4);

    /**
     * @tc.steps: step7. PopPage with different parameters.
     * @tc.expected: removeChild meets expectations .
     */
    stageManager.SetSrcPage(fourthNode);
    bool bResult = stageManager.PopPage(thirdNode, true, false);
    EXPECT_EQ(stageNode->GetChildren().size(), 3);
    EXPECT_TRUE(bResult);
}

/**
 * @tc.name: StageManagerTest010
 * @tc.desc: Testing GetPageById Function of StageManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, StageManagerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StagePattern and some PagePattern.
     */
    auto stageNode = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto firstNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto secondNode =
        FrameNode::CreateFrameNode("2", 2, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto thirdNode =
        FrameNode::CreateFrameNode("3", 3, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto fourthNode =
        FrameNode::CreateFrameNode("4", 4, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));

    /**
     * @tc.steps: step2. Create a StageManager based on stageNode.
     */
    StageManager stageManager(stageNode);

    /**
     * @tc.steps: step3. PopPage.
     * @tc.expected: Expected no child failed.
     */
    EXPECT_FALSE(stageManager.PopPage(nullptr));

    /**
     * @tc.steps: step4. Push a Page into StageManager.
     * @tc.expected: Push successfully.
     */
    EXPECT_TRUE(stageManager.PushPage(firstNode));

    /**
     * @tc.steps: step5. Push another three Page with different parameters into StageManager.
     * @tc.expected: Push successfully.
     */
    stageManager.PushPage(secondNode, false, false);
    stageManager.PushPage(thirdNode, true, false);
    stageManager.stageNode_->GetGeometryNode()->SetFrameSize(SizeF(1.0f, 1.0f));
    stageManager.PushPage(fourthNode, false, true);
    EXPECT_EQ(stageNode->GetChildren().size(), 4);

    /**
     * @tc.steps: step6. GetPageById(0).
     * @tc.expected: Get successfully.
     */
    auto pageNode = stageManager.GetPageById(0);

    EXPECT_EQ(pageNode->tag_, firstNode->tag_);

    /**
     * @tc.steps: step6. GetPageById(other).
     * @tc.expected: Get nullptr.
     */
    pageNode = stageManager.GetPageById(5);
    EXPECT_FALSE(pageNode);
}

/**
 * @tc.name: StageManagerTest011
 * @tc.desc: Testing InsertPage Function of StageManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, StageManagerTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StagePattern and some PagePattern.
     */
    auto stageNode = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto firstNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto secondNode =
        FrameNode::CreateFrameNode("2", 2, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto thirdNode =
        FrameNode::CreateFrameNode("3", 3, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));

    /**
     * @tc.steps: step2. Create a StageManager based on stageNode.
     */
    StageManager stageManager(stageNode);

    /**
     * @tc.steps: step3. Insert page bellow Top when stageNode has no child.
     * @tc.expected: Expected insert failed.
     */
    EXPECT_FALSE(stageManager.InsertPage(firstNode, true));
    EXPECT_EQ(stageNode->GetChildren().size(), 0);

    /**
     * @tc.steps: step4. Insert page to bottom when stageNode has no child.
     * @tc.expected: Expected insert failed.
     */
    EXPECT_FALSE(stageManager.InsertPage(firstNode, false));
    EXPECT_EQ(stageNode->GetChildren().size(), 0);

    /**
     * @tc.steps: step5. Push a Page into StageManager.
     * @tc.expected: Push successfully.
     */
    EXPECT_TRUE(stageManager.PushPage(firstNode));
    EXPECT_EQ(stageNode->GetChildren().size(), 1);
    EXPECT_EQ(stageNode->GetFirstChild(), firstNode);

    /**
     * @tc.steps: step6. Insert page bellow Top when stageNode has child.
     * @tc.expected: Expected insert success.
     */
    EXPECT_TRUE(stageManager.InsertPage(secondNode, true));
    EXPECT_EQ(stageNode->GetChildren().size(), 2);
    EXPECT_EQ(stageNode->GetFirstChild(), secondNode);

    /**
     * @tc.steps: step7. Insert page to bottom when stageNode has child.
     * @tc.expected: Expected insert success.
     */
    EXPECT_TRUE(stageManager.InsertPage(thirdNode, false));
    EXPECT_EQ(stageNode->GetChildren().size(), 3);
    EXPECT_EQ(stageNode->GetFirstChild(), thirdNode);
}

/**
 * @tc.name: PagePattern FirePageTransitionStart001
 * @tc.desc: Test the PagePattern Fire Page Transition Start
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePattern_FirePageTransitionStart001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some node and PagePattern.
     */
    auto parent = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto node = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 1, AceType::MakeRefPtr<StagePattern>());
    auto child = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(2, "child");
    parent->AddChild(node);
    node->AddChild(child);
    auto pattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    pattern->AttachToFrameNode(node);
    pattern->ReloadPage();

    /**
     * @tc.steps: step2. add Element to nodeAnimatablePropertyMap_.
     * @tc.expected: GetAnimatablePropertyFloat seccuess.
     */
    auto FRAME_NODE = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<Pattern>());
    FRAME_NODE->nodeAnimatablePropertyMap_.emplace(
        "pageTransitionProperty", AceType::MakeRefPtr<NodeAnimatablePropertyBase>());
    pattern->frameNode_ = FRAME_NODE;
    EXPECT_TRUE(FRAME_NODE->GetAnimatablePropertyFloat("pageTransitionProperty"));
    pattern->FirePageTransitionStart();

    /**
     * @tc.steps: step3. create safeAreaInsets_ .
     * @tc.expected: create seccuessful.
     */
    auto pipeline = MockPipelineContext::GetCurrentContext();
    pipeline->SetInstallationFree(0);
    SafeAreaInsets::Inset insetleft;
    insetleft.end = 5;
    SafeAreaInsets::Inset insetTop;
    insetTop.end = 1;
    SafeAreaInsets::Inset insetRight;
    SafeAreaInsets::Inset insetBottom;
    insetBottom.start = RK356_HEIGHT - 1;
    insetBottom.end = RK356_HEIGHT;
    pipeline->safeAreaManager_->cutoutSafeArea_ = SafeAreaInsets(insetleft, insetTop, insetRight, insetBottom);

    /**
     * @tc.steps: step4. test BeforeCreateLayoutWrapper .
     * @tc.expected: GetInstallationFree is true.
     */
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_FALSE(pipeline->GetInstallationFree());
}

/**
 * @tc.name: PagePattern FirePageTransitionFinish001
 * @tc.desc: Test the PagePattern Fire Page Transition Finish
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePattern_FirePageTransitionFinish001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some node and PagePattern.
     */
    auto parent = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto node = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 1, AceType::MakeRefPtr<StagePattern>());
    auto child = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(2, "child");
    parent->AddChild(node);
    node->AddChild(child);
    auto pattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    pattern->AttachToFrameNode(node);
    pattern->ReloadPage();

    /**
     * @tc.steps: step2. add Element to nodeAnimatablePropertyMap_.
     * @tc.expected: GetAnimatablePropertyFloat seccuess.
     */
    auto FRAME_NODE = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<Pattern>());
    FRAME_NODE->nodeAnimatablePropertyMap_.emplace(
        "pageTransitionProperty", AceType::MakeRefPtr<NodeAnimatablePropertyBase>());
    pattern->frameNode_ = FRAME_NODE;
    EXPECT_TRUE(FRAME_NODE->GetAnimatablePropertyFloat("pageTransitionProperty"));
    pattern->FirePageTransitionFinish();

    /**
     * @tc.steps: step3. create safeAreaInsets_ .
     * @tc.expected: create seccuessful.
     */
    auto pipeline = MockPipelineContext::GetCurrentContext();
    pipeline->SetInstallationFree(0);
    SafeAreaInsets::Inset insetleft;
    insetleft.end = 5;
    SafeAreaInsets::Inset insetTop;
    insetTop.end = 1;
    SafeAreaInsets::Inset insetRight;
    SafeAreaInsets::Inset insetBottom;
    insetBottom.start = RK356_HEIGHT - 1;
    insetBottom.end = RK356_HEIGHT;
    pipeline->safeAreaManager_->cutoutSafeArea_ = SafeAreaInsets(insetleft, insetTop, insetRight, insetBottom);

    /**
     * @tc.steps: step4. test BeforeCreateLayoutWrapper .
     * @tc.expected: GetInstallationFree is true.
     */
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_FALSE(pipeline->GetInstallationFree());
}

/**
 * @tc.name: PagePatternTest001
 * @tc.desc: Testing OnDirtyLayoutWrapperSwap of PagePattern work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a PagePattern.
     */
    PagePattern pattern(AceType::MakeRefPtr<PageInfo>());
    /**
     * @tc.steps: step2. Calling the SetFirstBuildCallback function.
     * @tc.expected: The callback firstBuildCallback_ in the pagePattern not nullptr.
     */
    pattern.SetFirstBuildCallback(std::move(FLAG_FUNC));
    EXPECT_NE(pattern.firstBuildCallback_, nullptr);
    /**
     * @tc.steps: step3. try call OnDirtyLayoutWrapperSwap with different condition.
     * @tc.expected: the callback firstBuildCallback_ in the pagePattern cleared.
     */
    DirtySwapConfig config;
    pattern.OnDirtyLayoutWrapperSwap(nullptr, config);
    pattern.isFirstLoad_ = true;
    pattern.OnDirtyLayoutWrapperSwap(nullptr, config);
    pattern.OnDirtyLayoutWrapperSwap(nullptr, config);
    EXPECT_EQ(flag, 1);
    /**
     * @tc.steps: step4. Call SetFirstBuildCallback again.
     * @tc.expected: The callback will be executed immediately.
     */
    pattern.SetFirstBuildCallback(std::move(FLAG_FUNC));
    EXPECT_EQ(flag, 2);
    /**
     * @tc.steps: step4. Call SetFirstBuildCallback again and don's set func.
     * @tc.expected: The callback won't be executed.
     */
    pattern.SetFirstBuildCallback(nullptr);
    EXPECT_EQ(flag, 2);
}

/**
 * @tc.name: PagePatternTest002
 * @tc.desc: Testing BuildSharedTransitionMap of PagePattern work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a parent and some child node ,config the page.
     */
    auto node = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto child = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 1, AceType::MakeRefPtr<StagePattern>());
    child->GetRenderContext()->SetShareId("shareId");
    auto child2 = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 2, AceType::MakeRefPtr<StagePattern>());
    auto child3 = CustomNode::CreateCustomNode(3, "child");
    node->AddChild(child);
    node->AddChild(child2);
    node->AddChild(child3);
    PagePattern pattern(AceType::MakeRefPtr<PageInfo>());
    pattern.AttachToFrameNode(node);
    /**
     * @tc.steps: step2. Calling the BuildSharedTransitionMap function.
     * @tc.expected: The property sharedTransitionMap_ in the pagePattern size meets expectations.
     */
    pattern.BuildSharedTransitionMap();
    EXPECT_EQ(pattern.sharedTransitionMap_.size(), 1);
}

/**
 * @tc.name: PagePatternTest003
 * @tc.desc: Testing ProcessHideState And ProcessShowState of PagePattern work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some node and PagePattern.
     */
    auto parent = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto node = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 1, AceType::MakeRefPtr<StagePattern>());
    auto child = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 2, AceType::MakeRefPtr<StagePattern>());
    parent->AddChild(node);
    node->AddChild(child);
    child->GetRenderContext()->SetShareId("shareId");
    PagePattern pattern(AceType::MakeRefPtr<PageInfo>());
    pattern.AttachToFrameNode(node);

    /**
     * @tc.steps: step2. Calling the ProcessShowState function.
     * @tc.expected: Call node isActive function return true.
     */
    pattern.ProcessShowState();
    EXPECT_TRUE(node->IsActive());

    /**
     * @tc.steps: step3. Calling the ProcessHideState function.
     * @tc.expected: Call node isActive function return false.
     */
    pattern.ProcessHideState();
    EXPECT_FALSE(node->IsActive());
}

/**
 * @tc.name: PagePatternTest004
 * @tc.desc: Testing the Show and Hide Related Methods of PagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePatternTest004, TestSize.Level1)
{
    Container::Current()->state_ = Frontend::State::ON_SHOW;
    /**
     * @tc.steps: step1. Create some node and PagePattern.
     */
    auto parent = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto node = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 1, AceType::MakeRefPtr<StagePattern>());
    auto child = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 2, AceType::MakeRefPtr<StagePattern>());
    parent->AddChild(node);
    node->AddChild(child);
    PagePattern pattern(AceType::MakeRefPtr<PageInfo>());
    pattern.AttachToFrameNode(node);
    /**
     * @tc.steps: step2. Calling the MarkRenderDone function.
     * @tc.expected: The property isRenderDone_ in the pagePattern is true
     */
    pattern.MarkRenderDone();
    EXPECT_TRUE(pattern.isRenderDone_);
    /**
     * @tc.steps: step3. Calling the OnShow and OnHide.
     * @tc.expected: The property isOnShow_ meets expectations.
     */
    pattern.OnShow();
    EXPECT_TRUE(pattern.isOnShow_);
    pattern.OnHide();
    EXPECT_FALSE(pattern.isOnShow_);
    /**
     * @tc.steps: step4. set show hide callback and call show hide again.
     * @tc.expected: The callback call times meets expectation.
     */
    pattern.SetOnPageShow(std::move(FLAG_FUNC));
    pattern.SetOnPageHide(std::move(FLAG_FUNC));
    pattern.OnShow();
    pattern.OnHide();
    EXPECT_EQ(flag, 2);
}

/**
 * @tc.name: PagePatternTest005
 * @tc.desc: Test the PageTransition related functions in the PagePattern work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some node and PagePattern.
     */
    auto parent = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto node = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 1, AceType::MakeRefPtr<StagePattern>());
    auto child = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(2, "child");
    parent->AddChild(node);
    node->AddChild(child);
    auto pattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    pattern->AttachToFrameNode(node);
    pattern->ReloadPage();

    /**
     * @tc.steps: step2. Create PageTransitionEffect with option.
     */
    PageTransitionOption option;
    option.routeType = RouteType::POP;
    auto effect = AceType::MakeRefPtr<PageTransitionEffect>(PageTransitionType::ENTER, option);

    /**
     * @tc.steps: step3. Calling the AddPageTransition function.
     * @tc.expected: Calling the GetTopTransition function returned not nullptr.
     */
    pattern->AddPageTransition(effect);
    EXPECT_NE(pattern->GetTopTransition(), nullptr);

    /**
     * @tc.steps: step5. SetUserCallback and recall TriggerPageTransition and StopPageTransition.
     */
    effect->SetUserCallback([](RouteType routeType, const float& value) {});
    pattern->SetPageTransitionFunc(std::move(FLAG_FUNC));
    /**
     * @tc.steps: step6.change some params ,recall TriggerPageTransition and StopPageTransition.
     * @tc.expected: The FLAG_FUNC call times meets expectation.
     */
    auto innerEffect = pattern->FindPageTransitionEffect(PageTransitionType::ENTER_POP);
    ASSERT_NE(effect, nullptr);
    innerEffect->animationOption_.delay = -1;
    /**
     * @tc.steps: step7.Calling the ClearPageTransitionEffect function.
     * @tc.expected: The GetTopTransition function returns a nullptr.
     */
    pattern->ClearPageTransitionEffect();
    EXPECT_EQ(pattern->GetTopTransition(), nullptr);
}

/**
 * @tc.name: PagePatternTest006
 * @tc.desc: Testing AddJsAnimator And GetJsAnimator of PagePattern work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PagePattern.
     */
    PagePattern pattern(AceType::MakeRefPtr<PageInfo>());

    /**
     * @tc.steps: step2. Create AnimatorInfo.
     */
    auto animatorInfo = AceType::MakeRefPtr<Framework::AnimatorInfo>();

    /**
     * @tc.steps: step3. Calling the GetJsAnimator function in the PagePattern.
     * @tc.expected: The GetJsAnimator function returned nullptr;
     */
    EXPECT_EQ(pattern.GetJsAnimator(TEST_ANIMATOR_ID), nullptr);

    /**
     * @tc.steps: step4. Calling the SetAnimator function in the PagePattern.
     * @tc.expected: The GetJsAnimator function returned not nullptr;
     */
    animatorInfo->SetAnimator(AceType::MakeRefPtr<Animator>(TEST_ANIMATOR_ID.c_str()));
    pattern.AddJsAnimator(TEST_ANIMATOR_ID, animatorInfo);
    EXPECT_NE(pattern.GetJsAnimator(TEST_ANIMATOR_ID), nullptr);
}
/**
 * @tc.name: PagePatternTest007
 * @tc.desc: Test the PagePattern related functions in the PagePattern work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some node and PagePattern.
     */
    auto parent = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto node = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 1, AceType::MakeRefPtr<StagePattern>());
    auto child = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(2, "child");
    parent->AddChild(node);
    node->AddChild(child);
    auto pattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    pattern->AttachToFrameNode(node);
    pattern->ReloadPage();

    /**
     * @tc.steps: step2. add Element to nodeAnimatablePropertyMap_.
     * @tc.expected: GetAnimatablePropertyFloat seccuess.
     */
    auto FRAME_NODE = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<Pattern>());
    FRAME_NODE->nodeAnimatablePropertyMap_.emplace(
        "pageTransitionProperty", AceType::MakeRefPtr<NodeAnimatablePropertyBase>());
    pattern->frameNode_ = FRAME_NODE;
    EXPECT_TRUE(FRAME_NODE->GetAnimatablePropertyFloat("pageTransitionProperty"));

    /**
     * @tc.steps: step3. test BeforeCreateLayoutWrapper.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_FALSE(pipeline->GetInstallationFree());

    pipeline->windowManager_ = AceType::MakeRefPtr<WindowManager>();
    pipeline->safeAreaManager_->keyboardSafeAreaEnabled_ = true;
    pipeline->windowManager_->windowGetModeCallback_ = []() -> WindowMode { return WindowMode::WINDOW_MODE_FLOATING; };
    pipeline->SetWindowModal(WindowModal::CONTAINER_MODAL);
    auto inset = pipeline->GetSafeArea();
    inset.bottom_.start = 0;
    inset.bottom_.end = 1;
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_FALSE(pipeline->GetInstallationFree());

    pipeline->SetInstallationFree(1);
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_TRUE(pipeline->GetInstallationFree());

    /**
     * @tc.steps: step4. coverage AvoidKeyboard.
     * @tc.expected: true.
     */
    pipeline->safeAreaManager_->keyboardSafeAreaEnabled_ = true;
    bool bResult = pattern->AvoidKeyboard();
    EXPECT_TRUE(bResult);
}

/**
 * @tc.name: PagePatternTest008
 * @tc.desc: Test the PagePattern related functions in the PagePattern work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some node and PagePattern.
     */
    auto parent = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto node = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 1, AceType::MakeRefPtr<StagePattern>());
    auto child = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(2, "child");
    parent->AddChild(node);
    node->AddChild(child);
    auto pattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    pattern->AttachToFrameNode(node);
    pattern->ReloadPage();

    /**
     * @tc.steps: step2. add Element to nodeAnimatablePropertyMap_.
     * @tc.expected: GetAnimatablePropertyFloat seccuess.
     */
    auto FRAME_NODE = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<Pattern>());
    FRAME_NODE->nodeAnimatablePropertyMap_.emplace(
        "pageTransitionProperty", AceType::MakeRefPtr<NodeAnimatablePropertyBase>());
    pattern->frameNode_ = FRAME_NODE;
    EXPECT_TRUE(FRAME_NODE->GetAnimatablePropertyFloat("pageTransitionProperty"));

    /**
     * @tc.steps: step3. create safeAreaInsets_ .
     * @tc.expected: create seccuessful.
     */
    auto pipeline = MockPipelineContext::GetCurrentContext();
    pipeline->SetInstallationFree(0);
    SafeAreaInsets::Inset insetleft;
    insetleft.end = 5;
    SafeAreaInsets::Inset insetTop;
    insetTop.end = 1;
    SafeAreaInsets::Inset insetRight;
    SafeAreaInsets::Inset insetBottom;
    insetBottom.start = RK356_HEIGHT - 1;
    insetBottom.end = RK356_HEIGHT;
    pipeline->safeAreaManager_->cutoutSafeArea_ = SafeAreaInsets(insetleft, insetTop, insetRight, insetBottom);
    auto host = pattern->GetHost();
    auto props = host->GetLayoutProperty();
    props->UpdateSafeAreaInsets(pipeline->safeAreaManager_->cutoutSafeArea_);
    EXPECT_TRUE(props->GetSafeAreaInsets());

    /**
     * @tc.steps: step4. test BeforeCreateLayoutWrapper .
     * @tc.expected: GetInstallationFree is true.
     */
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_FALSE(pipeline->GetInstallationFree());

    /**
     * @tc.steps: step5. coverage AvoidKeyboard.
     * @tc.expected: true.
     */
    pipeline->safeAreaManager_->keyboardSafeAreaEnabled_ = true;
    bool bResult = pattern->AvoidKeyboard();
    EXPECT_TRUE(bResult);

    /**
     * @tc.steps: step5. set keyboardInset_ to button.
     * @tc.expected: set success and Valid().
     */
    pipeline->GetSafeAreaManager()->keyboardInset_ = SafeAreaInsets::Inset(insetBottom);
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_TRUE(pipeline->GetSafeAreaManager()->GetKeyboardInset().IsValid());
}

/**
 * @tc.name: PageTransitionModelTest001
 * @tc.desc: Testing .
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PageTransitionModelTest001, TestSize.Level1)
{
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    stageNode->pattern_ = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    ViewStackProcessor::GetInstance()->SetPageNode(stageNode);

    /**
     * @tc.steps: step1. Create.
     * @tc.expected: pageTransitionEffects_ clear;
     */
    PageTransitionModelNG pageTransitionModel;
    pageTransitionModel.Create();
    EXPECT_EQ(stageNode->GetPattern<PagePattern>()->pageTransitionEffects_.size(), 0);

    pageTransitionModel.Pop();

    /**
     * @tc.steps: step2. CreateTransition.
     * @tc.expected: pageTransitionEffects_ add;
     */
    PageTransitionOption option;
    pageTransitionModel.CreateTransition(PageTransitionType::ENTER, option);
    EXPECT_EQ(stageNode->GetPattern<PagePattern>()->pageTransitionEffects_.size(), 1);

    /**
     * @tc.steps: step3. SetOpacityEffect.
     * @tc.expected: set Success;
     */
    pageTransitionModel.SetOpacityEffect(0.0);
    EXPECT_EQ(stageNode->GetPattern<PagePattern>()->GetTopTransition()->opacity_, 0.0);

    pageTransitionModel.SetOpacityEffect(10);
    EXPECT_EQ(stageNode->GetPattern<PagePattern>()->GetTopTransition()->opacity_, 10);

    /**
     * @tc.steps: step4. SetScaleEffect.
     * @tc.expected: set Success;
     */
    ScaleOptions scale(5.0, 6, 7, CalcDimension(), CalcDimension());
    pageTransitionModel.SetScaleEffect(scale);
    EXPECT_TRUE(stageNode->GetPattern<PagePattern>()->GetTopTransition()->scale_ == scale);

    /**
     * @tc.steps: step5. SetTranslateEffect.
     * @tc.expected: set Success;
     */
    TranslateOptions transop(5.0, 6, 7);
    pageTransitionModel.SetTranslateEffect(transop);
    EXPECT_TRUE(stageNode->GetPattern<PagePattern>()->GetTopTransition()->translate_ == transop);

    /**
     * @tc.steps: step6. SetSlideEffect.
     * @tc.expected: set Success;
     */
    pageTransitionModel.SetSlideEffect(SlideEffect::NONE);
    EXPECT_EQ(stageNode->GetPattern<PagePattern>()->GetTopTransition()->slide_, SlideEffect::NONE);

    /**
     * @tc.steps: step7. SetOnEnter.
     * @tc.expected: set Success;
     */
    int iTemp = 0;
    auto myLambda = [&iTemp](RouteType type, const float& y) { iTemp++; };
    pageTransitionModel.SetOnEnter(myLambda);
    stageNode->GetPattern<PagePattern>()->GetTopTransition()->userCallback_(RouteType::PUSH, 2);
    EXPECT_EQ(iTemp, 1);

    /**
     * @tc.steps: step8. SetOnExit.
     * @tc.expected: set Success;
     */
    auto myLambda2 = [&iTemp](RouteType type, const float& y) { iTemp--; };
    pageTransitionModel.SetOnExit(myLambda2);
    stageNode->GetPattern<PagePattern>()->GetTopTransition()->userCallback_(RouteType::PUSH, 2);
    EXPECT_EQ(iTemp, 0);
}

/**
 * @tc.name: PageTransitionModelTest002
 * @tc.desc: Testing .
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PageTransitionModelTest002, TestSize.Level1)
{
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    stageNode->pattern_ = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    ViewStackProcessor::GetInstance()->SetPageNode(stageNode);
    PageTransitionModelNG pageTransitionModel;
    PageTransitionOption option;
    pageTransitionModel.CreateTransition(PageTransitionType::ENTER, option);
    /**
     * @tc.steps: step1. SetSlideEffect is START.
     * @tc.expected: set Success;
     */
    pageTransitionModel.SetSlideEffect(SlideEffect::START);
    EXPECT_EQ(stageNode->GetPattern<PagePattern>()->GetTopTransition()->slide_, SlideEffect::START);

    /**
     * @tc.steps: step2. SetSlideEffect is END.
     * @tc.expected: set Success;
     */
    pageTransitionModel.SetSlideEffect(SlideEffect::END);
    EXPECT_EQ(stageNode->GetPattern<PagePattern>()->GetTopTransition()->slide_, SlideEffect::END);
}

/**
 * @tc.name: StageLayoutAlgorithmTest001
 * @tc.desc: Testing .
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, StageLayoutAlgorithmTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat a layoutwrapper and SetLayoutAlgorithm for it.
     */
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<StagePattern>());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<StagePattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step2. layout parameter initialization.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));
    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    /**
     * @tc.steps: step3. Perform element updates.
     */
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step4. creat a childLayoutWrapper and add to layoutWrapper.
     */
    auto childLayoutWrapper = CreatChildlayoutWrapper();
    layoutWrapper->AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step5. call Measure and Layout.
     * @tc.expected: Set FrameOffset Success.
     */
    StageLayoutAlgorithm stageLayoutAlgorithm;
    stageLayoutAlgorithm.Measure(AccessibilityManager::RawPtr(layoutWrapper));
    stageLayoutAlgorithm.Layout(AccessibilityManager::RawPtr(layoutWrapper));
    bool bEqual =
        childLayoutWrapper->GetGeometryNode()->GetFrameOffset() ==
        OffsetF(stageLayoutAlgorithm.childInsets_.left_.Length(), stageLayoutAlgorithm.childInsets_.top_.Length());
    EXPECT_TRUE(bEqual);
}

/**
 * @tc.name: PagePatternTest009
 * @tc.desc: test OnBackPressed
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePatternTest009, TestSize.Level1)
{
    const auto& pageNode = ViewStackProcessor::GetInstance()->GetPageNode();
    auto pattern = pageNode->GetPattern<PagePattern>();
    auto result = pattern->OnBackPressed();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PagePatternTest010
 * @tc.desc: test OnBackPressed
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePatternTest010, TestSize.Level1)
{
    const auto& pageNode = ViewStackProcessor::GetInstance()->GetPageNode();
    auto pattern = pageNode->GetPattern<PagePattern>();
    auto result = pattern->OnBackPressed();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PagePatternTest011
 * @tc.desc: test OnBackPressed
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePatternTest011, TestSize.Level1)
{
    const auto& pageNode = ViewStackProcessor::GetInstance()->GetPageNode();
    auto pattern = pageNode->GetPattern<PagePattern>();
    auto backPressedFunc = []() -> bool { return false; };
    pattern->isPageInTransition_ = false;
    pattern->SetOnBackPressed(backPressedFunc);
    auto result = pattern->OnBackPressed();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PagePatternTest012
 * @tc.desc: test OnBackPressed
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePatternTest012, TestSize.Level1)
{
    const auto& pageNode = ViewStackProcessor::GetInstance()->GetPageNode();
    auto pattern = pageNode->GetPattern<PagePattern>();
    auto backPressedFunc = []() -> bool { return false; };
    pattern->isPageInTransition_ = false;
    pattern->SetOnBackPressed(backPressedFunc);
    auto overlayManagernode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto overlayManger = AceType::MakeRefPtr<OverlayManager>(overlayManagernode);
    pattern->overlayManager_ = overlayManger;
    auto result = pattern->OnBackPressed();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PagePatternTest015
 * @tc.desc: test OnBackPressed
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePatternTest015, TestSize.Level1)
{
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto testStageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    auto UInode = AceType::DynamicCast<NG::UINode>(testStageManager);
    testStageManager->stageNode_->children_.push_back(UInode);
    testStageManager->stageInTrasition_ = true;
    auto nodeTest = testStageManager->GetPrevPageWithTransition();
    EXPECT_EQ(testStageManager->stageInTrasition_, true);
}

/**
 * @tc.name: PagePatternTest016
 * @tc.desc: test OnBackPressed
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePatternTest016, TestSize.Level1)
{
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto testStageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    auto UInode = AceType::DynamicCast<NG::UINode>(testStageManager);
    testStageManager->stageNode_->children_.push_back(UInode);
    testStageManager->stageInTrasition_ = false;
    auto nodeTest = testStageManager->GetPrevPageWithTransition();
    EXPECT_EQ(testStageManager->stageInTrasition_, false);
}

/**
 * @tc.name: PagePatternTest017
 * @tc.desc: test GetLastPageWithTransition
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePatternTest017, TestSize.Level1)
{
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto testStageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    auto UInode = AceType::DynamicCast<NG::UINode>(testStageManager);
    testStageManager->stageNode_->children_.push_back(UInode);
    testStageManager->stageInTrasition_ = false;
    testStageManager->stageNode_->children_.clear();
    auto nodeTest = testStageManager->GetLastPageWithTransition();
    EXPECT_EQ(testStageManager->stageInTrasition_, false);
}

/**
 * @tc.name: PagePatternTest018
 * @tc.desc: test OnBackPressed
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, PagePatternTest018, TestSize.Level1)
{
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto testStageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    auto UInode = AceType::DynamicCast<NG::UINode>(testStageManager);
    testStageManager->stageNode_->children_.push_back(UInode);
    testStageManager->stageInTrasition_ = false;
    testStageManager->stageNode_->children_.clear();
    auto nodeTest = testStageManager->GetPrevPageWithTransition();
    EXPECT_EQ(testStageManager->stageInTrasition_, false);
}

/**
 * @tc.name: GetTopPagesWithTransition001
 * @tc.desc: test branch: if (page)
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, GetTopPagesWithTransition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StageManager.
     */
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    ASSERT_NE(stageManager, nullptr);

    /**
     * @tc.steps: step2. Call function GetTopPagesWithTransition.
     *                   Branch: if (page) {
     *                   Condition: page => nullptr
     * @tc.expected: No pageNode will return.
     */
    auto topPages = stageManager->GetTopPagesWithTransition();
    ASSERT_TRUE(topPages.empty());

    /**
     * @tc.steps: step3. Add one pageNode to StageNode, and call function GetTopPagesWithTransition again.
     *                   Branch: if (page) {
     *                   Condition: page != nullptr.
     * @tc.expected: Only one pageNode will return.
     */
    auto pageInfo = AceType::MakeRefPtr<PageInfo>(1, "testUrl", "testPath");
    ASSERT_NE(pageInfo, nullptr);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(pageInfo);
    ASSERT_NE(pagePattern, nullptr);
    auto pageNode =
        FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pagePattern);
    ASSERT_NE(pageNode, nullptr);
    stageNode->AddChild(pageNode);
    topPages = stageManager->GetTopPagesWithTransition();
    ASSERT_EQ(topPages.size(), 1);
    ASSERT_EQ(topPages[0], pageNode);
}

/**
 * @tc.name: GetTopPagePaths001
 * @tc.desc: test branch: for (auto& page : pages)
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, GetTopPagePaths001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StageNode and StageManager.
     */
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    ASSERT_NE(stageManager, nullptr);
    std::string pageUrl = "";
    const std::string TEST_PATH = "TestPath/TestName";
    auto testGetPagePathCallback = [&pageUrl, &TEST_PATH](const std::string& url) -> std::string {
        pageUrl = url;
        return TEST_PATH;
    };
    stageManager->SetGetPagePathCallback(std::move(testGetPagePathCallback));

    /**
     * @tc.steps: step2. Call function GetTopPagePaths.
     *                   Branch: for (auto& page : pages)
     *                   Condition: pages is empty
     * @tc.expected: No pagePath will return.
     */
    auto topPagePaths = stageManager->GetTopPagePaths();
    ASSERT_TRUE(topPagePaths.empty());

    /**
     * @tc.steps: step3. Add one page to StageNode, then call function GetTopPagePaths again.
     *                   Branch: for (auto& page : pages)
     *                   Condition: pages contains one page
     * @tc.expected: One pagePath will return.
     */
    auto pageInfo = AceType::MakeRefPtr<PageInfo>(1, "myUrl", "myPath");
    ASSERT_NE(pageInfo, nullptr);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(pageInfo);
    ASSERT_NE(pagePattern, nullptr);
    auto pageNode =
        FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pagePattern);
    ASSERT_NE(pageNode, nullptr);
    stageNode->AddChild(pageNode);
    topPagePaths = stageManager->GetTopPagePaths();
    ASSERT_EQ(topPagePaths.size(), 1);
    ASSERT_EQ(topPagePaths[0], TEST_PATH);
    ASSERT_EQ(pageUrl, "myUrl");
}

/**
 * @tc.name: MovePageToFront
 * @tc.desc: test animationPage equal srcPage
 * @tc.type: FUNC
 */
HWTEST_F(StageTestNg, MovePageToFront, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StagePattern and some PagePattern.
     */
    auto stageNode = FrameNode::CreateFrameNode(FRAME_NODE_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    auto firstNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto secondNode =
        FrameNode::CreateFrameNode("2", 2, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto thirdNode =
        FrameNode::CreateFrameNode("3", 3, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto fourthNode =
        FrameNode::CreateFrameNode("4", 4, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));

    /**
     * @tc.steps: step2. Create a StageManager based on stageNode.
     */
    StageManager stageManager(stageNode);
    stageManager.PushPage(firstNode);
    stageManager.PushPage(secondNode, false, false);
    stageManager.PushPage(thirdNode, true, false);
    stageManager.PushPage(fourthNode, false, true);
    EXPECT_EQ(stageNode->GetChildren().size(), 4);

    stageManager.srcPageNode_ = thirdNode;

    stageManager.MovePageToFront(firstNode);
    EXPECT_EQ(stageManager.animationSrcPage_, stageManager.srcPageNode_);
}
} // namespace OHOS::Ace::NG
