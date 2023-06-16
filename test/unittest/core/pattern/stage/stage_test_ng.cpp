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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "core/common/container.h"
#include "core/common/ace_engine.h"
#include "core/common/container_scope.h"
#include "test/mock/core/common/mock_container.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
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
constexpr int32_t CHECK_BOX_ID_SECOND = 5;
constexpr int32_t CHECK_BOX_ID_THIRD = 6;
constexpr int32_t CHECK_BOX_ID_FOURTH = 6;
constexpr int32_t TEST_CONTAINER_ID = 100;
constexpr int32_t AT_LEAST_TIME = 3;
int32_t flag = 0;
std::function<void()> FLAG_FUNC = []() { flag++; };
} // namespace

class StageTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineBase::SetUp();
        auto pipeline = AceType::DynamicCast<NG::MockPipelineBase>(PipelineBase::GetCurrentContext());
        auto stageNode = FrameNode::CreateFrameNode(
            V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
        pipeline->sharedTransitionManager_ = AceType::MakeRefPtr<SharedOverlayManager>(stageNode);
        EXPECT_CALL(*pipeline, FlushPipelineImmediately()).Times(testing::AtLeast(AT_LEAST_TIME));
        MockContainer::SetUp();
        ContainerScope::UpdateCurrent(TEST_CONTAINER_ID);
    }
    static void TearDownTestSuite()
    {
        MockPipelineBase::TearDown();
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
    pageEventHub.UpdateRadioGroupValue(TEST_GROUP_NAME, RADIO_ID_FIRST);

    /**
     * @tc.steps: step2. Add radio to group.
     * @tc.expected: The HasRadioId function of PageEventHub meets expectations .
     */
    pageEventHub.AddRadioToGroup(TEST_GROUP_NAME, RADIO_ID_FIRST);
    EXPECT_TRUE(pageEventHub.HasRadioId(TEST_GROUP_NAME, RADIO_ID_FIRST));
    EXPECT_FALSE(pageEventHub.HasRadioId(ERROR_GROUP_NAME, RADIO_ID_FIRST));

    /**
     * @tc.steps: step3. Add another two radio to group.
     * @tc.expected: The HasRadioId function of PageEventHub meets expectations .
     */
    pageEventHub.AddRadioToGroup(TEST_GROUP_NAME, RADIO_ID_SECOND);
    pageEventHub.AddRadioToGroup(TEST_GROUP_NAME, RADIO_ID_THIRD);

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
    pageEventHub.UpdateRadioGroupValue(TEST_GROUP_NAME, RADIO_ID_FIRST);
    pageEventHub.UpdateRadioGroupValue(TEST_GROUP_NAME, RADIO_ID_SECOND);

    /**
     * @tc.steps: step6. RemoveRadioFromGroup.
     * @tc.expected: The radio remove successful .
     */
    pageEventHub.RemoveRadioFromGroup(TEST_GROUP_NAME, RADIO_ID_FIRST);
    EXPECT_FALSE(pageEventHub.HasRadioId(TEST_GROUP_NAME, RADIO_ID_FIRST));
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
    EXPECT_EQ(pageEventHub.GetCheckBoxGroupMap().size(), 0);

    /**
     * @tc.steps: step2. build error pattern and add to the group.
     * @tc.expected: The CheckBoxGroupMap[TEST_GROUP_NAME] has the error pattern.
     */
    auto errorPattern = AceType::MakeRefPtr<RadioPattern>();
    auto errorNode = FrameNode::CreateFrameNode(V2::CHECKBOXGROUP_ETS_TAG, CHECK_BOX_ID_FIRST, errorPattern);
    ElementRegister::GetInstance()->AddReferenced(CHECK_BOX_ID_FIRST, errorNode);
    pageEventHub.RemoveCheckBoxFromGroup(TEST_GROUP_NAME, CHECK_BOX_ID_FIRST);
    pageEventHub.AddCheckBoxGroupToGroup(TEST_GROUP_NAME, CHECK_BOX_ID_FIRST);
    EXPECT_EQ(pageEventHub.GetCheckBoxGroupMap()[TEST_GROUP_NAME].size(), 1);

    /**
     * @tc.steps: step3. remove error pattern.
     * @tc.expected: The CheckBoxGroupMap[TEST_GROUP_NAME] has the error pattern.
     */
    ElementRegister::GetInstance()->RemoveItem(CHECK_BOX_ID_FIRST);
    pageEventHub.RemoveCheckBoxFromGroup(TEST_GROUP_NAME, CHECK_BOX_ID_FIRST);
    EXPECT_EQ(pageEventHub.GetCheckBoxGroupMap()[TEST_GROUP_NAME].size(), 0);

    /**
     * @tc.steps: step4. add real checkBoxGroup and add to the group.
     * @tc.expected: add success.
     */
    auto checkBoxGroup = AceType::MakeRefPtr<CheckBoxGroupPattern>();
    auto checkBoxGroupNode = FrameNode::CreateFrameNode(V2::CHECKBOXGROUP_ETS_TAG, CHECK_BOX_ID_THIRD, checkBoxGroup);
    ElementRegister::GetInstance()->AddReferenced(CHECK_BOX_ID_THIRD, checkBoxGroupNode);
    pageEventHub.AddCheckBoxGroupToGroup(TEST_GROUP_NAME, CHECK_BOX_ID_THIRD);
    EXPECT_EQ(pageEventHub.GetCheckBoxGroupMap()[TEST_GROUP_NAME].size(), 1);

    /**
     * @tc.steps: step5. add checkBox to group
     * @tc.expected: add success.
     */
    pageEventHub.AddCheckBoxToGroup(TEST_GROUP_NAME, CHECK_BOX_ID_SECOND);
    EXPECT_EQ(pageEventHub.GetCheckBoxGroupMap()[TEST_GROUP_NAME].size(), 2);

    /**
     * @tc.steps: step6. remove the checkBoxGroup from group.
     * @tc.expected: remove success.
     */
    ElementRegister::GetInstance()->RemoveItem(CHECK_BOX_ID_THIRD);
    pageEventHub.RemoveCheckBoxFromGroup(TEST_GROUP_NAME, CHECK_BOX_ID_THIRD);
    EXPECT_EQ(pageEventHub.GetCheckBoxGroupMap()[TEST_GROUP_NAME].size(), 1);

    /**
     * @tc.steps: step7. add checkBoxGroup to group again.
     * @tc.expected: add success.
     */
    ElementRegister::GetInstance()->AddReferenced(CHECK_BOX_ID_THIRD, checkBoxGroupNode);
    pageEventHub.AddCheckBoxGroupToGroup(TEST_GROUP_NAME, CHECK_BOX_ID_THIRD);
    EXPECT_EQ(pageEventHub.GetCheckBoxGroupMap()[TEST_GROUP_NAME].size(), 2);

    /**
     * @tc.steps: step8. build second checkBoxGroup to group.
     * @tc.expected: add fail.
     */
    auto checkBoxGroup2 = AceType::MakeRefPtr<CheckBoxGroupPattern>();
    auto checkBoxGroupNode2 =
        FrameNode::CreateFrameNode(V2::CHECKBOXGROUP_ETS_TAG, CHECK_BOX_ID_FOURTH, checkBoxGroup2);
    ElementRegister::GetInstance()->AddReferenced(CHECK_BOX_ID_FOURTH, checkBoxGroupNode2);
    pageEventHub.RemoveCheckBoxFromGroup(TEST_GROUP_NAME, CHECK_BOX_ID_FIRST);
    EXPECT_EQ(pageEventHub.GetCheckBoxGroupMap()[TEST_GROUP_NAME].size(), 2);
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
    EXPECT_FALSE(stageManager.PopPage());

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
    stageManager.PopPage(true, false);
    stageManager.PopPage(false, true);
    EXPECT_EQ(stageNode->GetChildren().size(), 3);

    /**
     * @tc.steps: step8. Call StopPageTransition.
     * @tc.expected: stop transition and remove in transition page,size meets expectations.
     */
    stageManager.StopPageTransition();
    EXPECT_EQ(stageNode->GetChildren().size(), 2);
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
    EXPECT_FALSE(stageManager.PopPageToIndex(1));

    /**
     * @tc.steps: step4. Add second child node and recall PopPageToIndex.
     * @tc.expected: Children length is equal to the current index and return true
     */
    stageManager.PushPage(secondNode);
    EXPECT_TRUE(stageManager.PopPageToIndex(1));

    /**
     * @tc.steps: step5. Add third child node and recall PopPageToIndex.
     * @tc.expected: stageManager child size meets expectations.
     */
    stageManager.PushPage(thirdNode);
    stageManager.PushPage(fourthNode);
    stageManager.PopPageToIndex(1);
    EXPECT_EQ(stageNode->GetChildren().size(), 3);
    stageManager.PopPageToIndex(0);
    EXPECT_EQ(stageNode->GetChildren().size(), 2);

    /**
     * @tc.steps: step6. Add third child node and recall PopPageToIndex.
     * @tc.expected: return true
     */
    stageManager.PushPage(thirdNode);
    stageManager.PushPage(fourthNode);
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
    PagePattern pattern(AceType::MakeRefPtr<PageInfo>());
    pattern.AttachToFrameNode(node);
    pattern.ReloadPage();

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
    pattern.AddPageTransition(effect);
    EXPECT_NE(pattern.GetTopTransition(), nullptr);

    /**
     * @tc.steps: step4. Calling the TriggerPageTransition function.
     * @tc.expected: Attribute pageTransitionFinish_ not nullptr.
     */
    pattern.TriggerPageTransition(PageTransitionType::NONE, FLAG_FUNC);
    EXPECT_NE(pattern.pageTransitionFinish_, nullptr);

    /**
     * @tc.steps: step5. SetUserCallback and recall TriggerPageTransition and StopPageTransition.
     */
    effect->SetUserCallback([](RouteType routeType, const float& value) {});
    pattern.SetPageTransitionFunc(std::move(FLAG_FUNC));
    pattern.TriggerPageTransition(PageTransitionType::ENTER_POP, FLAG_FUNC);
    pattern.StopPageTransition();
    /**
     * @tc.steps: step6.change some params ,recall TriggerPageTransition and StopPageTransition.
     * @tc.expected: The FLAG_FUNC call times meets expectation.
     */
    ASSERT_NE(pattern.controller_, nullptr);
    pattern.controller_->Stop();
    auto innerEffect = pattern.FindPageTransitionEffect(PageTransitionType::ENTER_POP);
    ASSERT_NE(effect, nullptr);
    innerEffect->animationOption_.delay = -1;
    pattern.TriggerPageTransition(PageTransitionType::ENTER_POP, FLAG_FUNC);
    pattern.StopPageTransition();
    EXPECT_EQ(flag, 3);
    /**
     * @tc.steps: step7.Calling the ClearPageTransitionEffect function.
     * @tc.expected: The GetTopTransition function returns a nullptr.
     */
    pattern.ClearPageTransitionEffect();
    EXPECT_EQ(pattern.GetTopTransition(), nullptr);
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
} // namespace OHOS::Ace::NG