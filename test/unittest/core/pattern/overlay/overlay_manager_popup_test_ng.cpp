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

#define private public
#define protected public
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t POPUP_NODE_2 = 2;
const std::string MESSAGE = "hello world";
const std::string BOTTOMSTRING = "test";
constexpr int32_t DURATION = 2;

// Constants for MountPopup duplicate prevention tests
constexpr int32_t EXPECTED_POPUP_COUNT_ONE = 1;
constexpr int32_t EXPECTED_POPUP_COUNT_TWO = 2;
constexpr int32_t POPUP_NODE_ID_1 = 1;
constexpr int32_t POPUP_NODE_ID_ZERO = 0;
} // namespace

class OverlayManagerPopupTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static RefPtr<FrameNode> CreateTargetNode();
    static void CreatePopupNodes(std::vector<RefPtr<FrameNode>> &targetNodes, std::vector<PopupInfo> &popups,
        int32_t nodeNum);
};

void OverlayManagerPopupTestNg::SetUpTestCase()
{
}

void OverlayManagerPopupTestNg::TearDownTestCase()
{
}


RefPtr<FrameNode> OverlayManagerPopupTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

void OverlayManagerPopupTestNg::CreatePopupNodes(std::vector<RefPtr<FrameNode>> &targetNodes,
    std::vector<PopupInfo> &popups, int32_t nodeNum)
{
    for (int i = 0; i < nodeNum; i++) {
        auto targetNode = CreateTargetNode();
        ASSERT_NE(targetNode, nullptr);
        targetNodes.emplace_back(targetNode);
        auto targetId = targetNodes[i]->GetId();
        auto targetTag = targetNodes[i]->GetTag();

        auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
        auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                                                    AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
        PopupInfo popupInfo;
        popupInfo.popupId = popupId;
        popupInfo.popupNode = popupNode;
        popupInfo.target = targetNode;
        popupInfo.markNeedUpdate = true;
        popupInfo.isBlockEvent = false;
        popups.emplace_back(popupInfo);
    }
}

/**
 * @tc.name: PopupTest001
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    std::function<void(int32_t)> onWillDismiss1 = [](int32_t reason) {};
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], move(onWillDismiss1));
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_TRUE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->SetDismissPopupId(targetId1);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    overlayManager->ShowPopup(targetId2, popups[1], nullptr);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_FALSE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->SetDismissPopupId(targetId2);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest002
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], nullptr, true);
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_FALSE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    overlayManager->ShowPopup(targetId2, popups[1], nullptr, false);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_TRUE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest003
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    std::function<void(int32_t)> onWillDismiss1 = [](int32_t reason) {};
    popups[0].markNeedUpdate = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], move(onWillDismiss1));
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_TRUE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->SetDismissPopupId(targetId1);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].markNeedUpdate = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_FALSE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->SetDismissPopupId(targetId2);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest004
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    std::function<void(int32_t)> onWillDismiss1 = [](int32_t reason) {};
    popups[0].isCurrentOnShow = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], move(onWillDismiss1));
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_TRUE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->SetDismissPopupId(targetId1);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].isCurrentOnShow = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_FALSE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->SetDismissPopupId(targetId2);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest005
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    std::function<void(int32_t)> onWillDismiss1 = [](int32_t reason) {};
    popups[0].isBlockEvent = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], move(onWillDismiss1));
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_TRUE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->SetDismissPopupId(targetId1);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].isBlockEvent = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_FALSE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->SetDismissPopupId(targetId2);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest006
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    std::function<void(int32_t)> onWillDismiss1 = [](int32_t reason) {};
    popups[0].focusable = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], move(onWillDismiss1));
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_TRUE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->SetDismissPopupId(targetId1);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].focusable = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_FALSE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->SetDismissPopupId(targetId2);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest007
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    std::function<void(int32_t)> onWillDismiss1 = [](int32_t reason) {};
    popups[0].markNeedUpdate = true;
    popups[0].isCurrentOnShow = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], move(onWillDismiss1));
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_TRUE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->SetDismissPopupId(targetId1);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].markNeedUpdate = true;
    popups[1].isCurrentOnShow = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_FALSE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->SetDismissPopupId(targetId2);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest008
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    std::function<void(int32_t)> onWillDismiss1 = [](int32_t reason) {};
    popups[0].markNeedUpdate = true;
    popups[0].isBlockEvent = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], move(onWillDismiss1));
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_TRUE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->SetDismissPopupId(targetId1);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].markNeedUpdate = true;
    popups[1].isBlockEvent = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_FALSE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->SetDismissPopupId(targetId2);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest009
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    std::function<void(int32_t)> onWillDismiss1 = [](int32_t reason) {};
    popups[0].markNeedUpdate = true;
    popups[0].focusable = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], move(onWillDismiss1));
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_TRUE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->SetDismissPopupId(targetId1);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].markNeedUpdate = true;
    popups[1].focusable = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_FALSE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->SetDismissPopupId(targetId2);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest010
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    std::function<void(int32_t)> onWillDismiss1 = [](int32_t reason) {};
    popups[0].isCurrentOnShow = true;
    popups[0].isBlockEvent = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], move(onWillDismiss1));
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_TRUE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->SetDismissPopupId(targetId1);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].isCurrentOnShow = true;
    popups[1].isBlockEvent = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_FALSE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->SetDismissPopupId(targetId2);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest011
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    std::function<void(int32_t)> onWillDismiss1 = [](int32_t reason) {};
    popups[0].isCurrentOnShow = true;
    popups[0].focusable = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], move(onWillDismiss1));
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_TRUE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->SetDismissPopupId(targetId1);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].isCurrentOnShow = true;
    popups[1].focusable = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->HasOnWillDismiss());
    EXPECT_FALSE(overlayManager->PopupCallBackOnWillDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->SetDismissPopupId(targetId2);
    overlayManager->DismissPopup();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest012
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    popups[0].markNeedUpdate = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], nullptr, true);
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_FALSE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].markNeedUpdate = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr, false);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_TRUE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest013
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    popups[0].isCurrentOnShow = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], nullptr, true);
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_FALSE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].isCurrentOnShow = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr, false);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_TRUE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest014
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    popups[0].isBlockEvent = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], nullptr, true);
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_FALSE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].isBlockEvent = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr, false);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_TRUE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest015
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    popups[0].focusable = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], nullptr, true);
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_FALSE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].focusable = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr, false);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_TRUE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest016
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    popups[0].markNeedUpdate = true;
    popups[0].isCurrentOnShow = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], nullptr, true);
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_FALSE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].markNeedUpdate = true;
    popups[1].isCurrentOnShow = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr, false);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_TRUE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest017
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    popups[0].markNeedUpdate = true;
    popups[0].isBlockEvent = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], nullptr, true);
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_FALSE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].markNeedUpdate = true;
    popups[1].isBlockEvent = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr, false);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_TRUE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest018
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    popups[0].markNeedUpdate = true;
    popups[0].focusable = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], nullptr, true);
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_FALSE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].markNeedUpdate = true;
    popups[1].focusable = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr, false);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_TRUE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest019
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    popups[0].isCurrentOnShow = true;
    popups[0].isBlockEvent = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], nullptr, true);
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_FALSE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].isCurrentOnShow = true;
    popups[1].isBlockEvent = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr, false);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_TRUE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest020
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    popups[0].isCurrentOnShow = true;
    popups[0].focusable = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], nullptr, true);
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_FALSE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].isCurrentOnShow = true;
    popups[1].focusable = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr, false);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_TRUE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest021
 * @tc.desc: Test Test OverlayManager hasOnWillDismiss
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    popups[0].markNeedUpdate = true;
    popups[0].isCurrentOnShow = true;
    popups[0].focusable = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], nullptr, true);
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_FALSE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    popups[1].markNeedUpdate = true;
    popups[1].isCurrentOnShow = true;
    popups[1].focusable = true;
    overlayManager->ShowPopup(targetId2, popups[1], nullptr, false);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_FALSE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_TRUE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId2);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: PopupTest022
 * @tc.desc: Test ShowPopupAnimation when hastransition is true.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isBlockEvent = false;

    /**
     * @tc.steps: step2. create overlayManager and call ShowPopupAnimation.
     * @tc.expected: transitionStatus_ and visibility of layoutProperty is updated successfully
     */
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(true);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    rootNode->isLayoutComplete_ = true;
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    popupPattern->SetHasTransition(true);
    EXPECT_TRUE(popupPattern->GetHasTransition());
    overlayManager->ShowPopupAnimation(popupNode);
    EXPECT_EQ(popupPattern->transitionStatus_, TransitionStatus::ENTERING);
    EXPECT_EQ(layoutProp->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: PopupTest023
 * @tc.desc: Test ShowPopupAnimationNG when hastransition is true.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isBlockEvent = false;

    /**
     * @tc.steps: step2. create overlayManager and call ShowPopupAnimationNG.
     * @tc.expected: transitionStatus_ and visibility of layoutProperty is updated successfully
     */
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(true);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    rootNode->isLayoutComplete_ = true;
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    popupPattern->SetHasTransition(true);
    EXPECT_TRUE(popupPattern->GetHasTransition());
    overlayManager->ShowPopupAnimationNG(popupNode);
    EXPECT_EQ(popupPattern->transitionStatus_, TransitionStatus::ENTERING);
    EXPECT_EQ(layoutProp->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: PopupTest024
 * @tc.desc: Test ShowPopupAnimation when hastransition is false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isBlockEvent = false;

    /**
     * @tc.steps: step2. create overlayManager and call ShowPopupAnimation.
     * @tc.expected: transitionStatus_ and visibility of layoutProperty is updated successfully
     */
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(true);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    rootNode->isLayoutComplete_ = true;
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    popupPattern->SetHasTransition(false);
    EXPECT_FALSE(popupPattern->GetHasTransition());
    overlayManager->ShowPopupAnimation(popupNode);
    EXPECT_EQ(popupPattern->transitionStatus_, TransitionStatus::INVISIABLE);
}

/**
 * @tc.name: PopupTest025
 * @tc.desc: Test ShowPopupAnimationNG when hastransition is false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isBlockEvent = false;

    /**
     * @tc.steps: step2. create overlayManager and call ShowPopupAnimationNG.
     * @tc.expected: transitionStatus_ and visibility of layoutProperty is updated successfully
     */
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(true);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    rootNode->isLayoutComplete_ = true;
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    popupPattern->SetHasTransition(false);
    EXPECT_FALSE(popupPattern->GetHasTransition());
    overlayManager->ShowPopupAnimationNG(popupNode);
    EXPECT_EQ(popupPattern->transitionStatus_, TransitionStatus::INVISIABLE);
}

/**
 * @tc.name: PopupTest026
 * @tc.desc: Test HidePopupAnimation when hastransition is true.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isBlockEvent = false;

    /**
     * @tc.steps: step2. create overlayManager and call HidePopupAnimation.
     * @tc.expected: transitionStatus_ and visibility of layoutProperty is updated successfully
     */
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(true);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    rootNode->isLayoutComplete_ = true;
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    popupPattern->SetHasTransition(true);
    EXPECT_TRUE(popupPattern->GetHasTransition());
    overlayManager->HidePopupAnimation(popupNode, nullptr);
    EXPECT_EQ(popupPattern->transitionStatus_, TransitionStatus::INVISIABLE);
}

/**
 * @tc.name: PopupTest027
 * @tc.desc: Test HidePopupAnimation when hastransition is false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isBlockEvent = false;

    /**
     * @tc.steps: step2. create overlayManager and call HidePopupAnimation.
     * @tc.expected: transitionStatus_ and visibility of layoutProperty is updated successfully
     */
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(true);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    rootNode->isLayoutComplete_ = true;
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    popupPattern->SetHasTransition(false);
    EXPECT_FALSE(popupPattern->GetHasTransition());
    overlayManager->HidePopupAnimation(popupNode, nullptr);
    EXPECT_FALSE(popupNode->GetRenderContext()->HasDisappearTransition());
    EXPECT_EQ(popupPattern->transitionStatus_, TransitionStatus::INVISIABLE);
}

/**
 * @tc.name: PopupTest028
 * @tc.desc: Test ShowPopupAnimation when hastransition is true.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isBlockEvent = false;

    /**
     * @tc.steps: step2. create overlayManager and call ShowPopupAnimation.
     * @tc.expected: transitionStatus_ and visibility of layoutProperty is updated successfully
     */
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(false);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    rootNode->isLayoutComplete_ = true;
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    popupPattern->SetHasTransition(true);
    EXPECT_TRUE(popupPattern->GetHasTransition());
    overlayManager->ShowPopupAnimation(popupNode);
    EXPECT_EQ(popupPattern->transitionStatus_, TransitionStatus::ENTERING);
    EXPECT_EQ(layoutProp->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: PopupTest029
 * @tc.desc: Test ShowPopupAnimationNG when hastransition is true.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isBlockEvent = false;

    /**
     * @tc.steps: step2. create overlayManager and call ShowPopupAnimationNG.
     * @tc.expected: transitionStatus_ and visibility of layoutProperty is updated successfully
     */
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(false);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    rootNode->isLayoutComplete_ = true;
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    popupPattern->SetHasTransition(true);
    EXPECT_TRUE(popupPattern->GetHasTransition());
    overlayManager->ShowPopupAnimationNG(popupNode);
    EXPECT_EQ(popupPattern->transitionStatus_, TransitionStatus::ENTERING);
    EXPECT_EQ(layoutProp->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: PopupTest030
 * @tc.desc: Test ShowPopupAnimation when hastransition is false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isBlockEvent = false;

    /**
     * @tc.steps: step2. create overlayManager and call ShowPopupAnimation.
     * @tc.expected: transitionStatus_ and visibility of layoutProperty is updated successfully
     */
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(false);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    rootNode->isLayoutComplete_ = true;
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    popupPattern->SetHasTransition(false);
    EXPECT_FALSE(popupPattern->GetHasTransition());
    overlayManager->ShowPopupAnimation(popupNode);
    EXPECT_EQ(popupPattern->transitionStatus_, TransitionStatus::INVISIABLE);
}

/**
 * @tc.name: PopupTest031
 * @tc.desc: Test ShowPopupAnimationNG when hastransition is false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isBlockEvent = false;

    /**
     * @tc.steps: step2. create overlayManager and call ShowPopupAnimationNG.
     * @tc.expected: transitionStatus_ and visibility of layoutProperty is updated successfully
     */
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(false);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    rootNode->isLayoutComplete_ = true;
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    popupPattern->SetHasTransition(false);
    EXPECT_FALSE(popupPattern->GetHasTransition());
    overlayManager->ShowPopupAnimationNG(popupNode);
    EXPECT_EQ(popupPattern->transitionStatus_, TransitionStatus::INVISIABLE);
}

/**
 * @tc.name: PopupTest033
 * @tc.desc: Test HidePopupAnimation when hastransition is true.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isBlockEvent = false;

    /**
     * @tc.steps: step2. create overlayManager and call HidePopupAnimation.
     * @tc.expected: transitionStatus_ and visibility of layoutProperty is updated successfully
     */
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(false);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    rootNode->isLayoutComplete_ = true;
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    popupPattern->SetHasTransition(true);
    EXPECT_TRUE(popupPattern->GetHasTransition());
    overlayManager->HidePopupAnimation(popupNode, nullptr);
    EXPECT_EQ(popupPattern->transitionStatus_, TransitionStatus::INVISIABLE);
}

/**
 * @tc.name: PopupTest034
 * @tc.desc: Test HidePopupAnimation when hastransition is false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isBlockEvent = false;

    /**
     * @tc.steps: step2. create overlayManager and call HidePopupAnimation.
     * @tc.expected: transitionStatus_ and visibility of layoutProperty is updated successfully
     */
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(false);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    rootNode->isLayoutComplete_ = true;
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    popupPattern->SetHasTransition(false);
    EXPECT_FALSE(popupPattern->GetHasTransition());
    overlayManager->HidePopupAnimation(popupNode, nullptr);
    EXPECT_FALSE(popupNode->GetRenderContext()->HasDisappearTransition());
    EXPECT_EQ(popupPattern->transitionStatus_, TransitionStatus::INVISIABLE);
}
/**
 * @tc.name: PopupTest035
 * @tc.desc: Test OverlayManager::PopupEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    for (int i = 0; i < POPUP_NODE_2; i++) {
        auto targetNode = CreateTargetNode();
        ASSERT_NE(targetNode, nullptr);
        targetNodes.emplace_back(targetNode);
        auto targetId = targetNodes[i]->GetId();
        auto targetTag = targetNodes[i]->GetTag();

        auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
        auto popupNode = FrameNode::CreateFrameNode(
            V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
        PopupInfo popupInfo;
        popupInfo.popupId = popupId;
        popupInfo.popupNode = popupNode;
        popupInfo.target = targetNode;
        popupInfo.markNeedUpdate = true;
        popupInfo.isBlockEvent = false;
        popups.emplace_back(popupInfo);
    }
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0]);
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    overlayManager->ShowPopup(targetId2, popups[1]);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    /**
     * @tc.steps: step3. call HideCustomPopups when childCount is 2
     * @tc.expected: popupMap's data is updated successfully
     */
    overlayManager->HideCustomPopups();
    EXPECT_FALSE(overlayManager->popupMap_.empty());
    EXPECT_FALSE(rootNode->GetChildren().empty());
    /**
     * @tc.steps: step4. call RemoveOverlay when childCount is 2
     * @tc.expected: remove one popupNode at a time
     */
    overlayManager->HidePopup(targetId1, popups[0]);
    overlayManager->HidePopup(targetId2, popups[1]);
    EXPECT_FALSE(overlayManager->RemoveOverlay(false));
    EXPECT_FALSE(overlayManager->popupMap_.empty());
    overlayManager->ErasePopup(targetId1);
    overlayManager->ErasePopup(targetId2);
    EXPECT_TRUE(overlayManager->popupMap_.empty());
    /**
     * @tc.steps: step5. call HideCustomPopups when popupMap_ is empty
     * @tc.expected: function exits normally
     */
    overlayManager->HideCustomPopups();
    EXPECT_TRUE(overlayManager->popupMap_.empty());
}
/**
 * @tc.name: PopupTest036
 * @tc.desc: Test IsAccessibilityModal function of BubbleAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    ASSERT_NE(popupNode, nullptr);
    auto accessibilityProperty = popupNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step2. get modal attribute from accessibilityProperty.
     * @tc.expected: modal is true.
     */
    auto isModal = accessibilityProperty->IsAccessibilityModal();
    EXPECT_TRUE(isModal);

    /**
     * @tc.steps: step3. set IsModal false to BubbleLayoutProperty, then get modal attribute from accessibilityProperty.
     * @tc.expected: modal is false.
     */
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateIsModal(false);
    isModal = accessibilityProperty->IsAccessibilityModal();
    EXPECT_FALSE(isModal);
}

/**
 * @tc.name: ToastTest001
 * @tc.desc: Test OverlayManager::ShowToast.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, ToastTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get overlay manager instance.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call ShowToast.
     * @tc.expected: toastMap_ is not empty
     */
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    overlayManager->ShowToast(toastInfo, nullptr);
    EXPECT_FALSE(overlayManager->toastMap_.empty());
}

/**
 * @tc.name: HideAllPopupsWithoutAnimation001
 * @tc.desc: Test OverlayManager::HideAllPopupsWithoutAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, HideAllPopupsWithoutAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    popups[0].markNeedUpdate = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);
    overlayManager->ShowPopup(targetId1, popups[0], nullptr, true);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    EXPECT_TRUE(overlay->GetPattern<BubblePattern>()->GetInteractiveDismiss());
    EXPECT_FALSE(overlayManager->PopupInteractiveDismiss(overlay));
    EXPECT_EQ(overlayManager->GetPopupIdByNode(overlay), targetId1);
    overlayManager->HideAllPopupsWithoutAnimation();
    EXPECT_FALSE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    EXPECT_FALSE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
}

/**
 * @tc.name: ShowTipsInSubwindow001
 * @tc.desc: Test ShowTipsInSubwindow function.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, ShowTipsInSubwindow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    PopupInfo popupInfo;
    popupInfo.target = AceType::WeakClaim(AceType::RawPtr(targetNode));
    MockPipelineContext::SetUp();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    MockPipelineContext::GetCurrent()->overlayManager_ = overlayManager;
    overlayManager->tipsEnterAndLeaveInfoMap_[targetNode->GetId()] = { { 0, true } };
    overlayManager->ShowTipsInSubwindow(targetNode->GetId(), popupInfo, 0);
    EXPECT_FALSE(overlayManager->tipsInfoList_.empty());

    overlayManager->tipsEnterAndLeaveInfoMap_[targetNode->GetId()] = { { 0, true } };
    popupInfo.isTips = false;
    popupInfo.popupNode = stageNode;
    overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    overlayManager->ShowTipsInSubwindow(targetNode->GetId(), popupInfo, 0);
    EXPECT_FALSE(overlayManager->tipsInfoList_.empty());
    
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ErasePopupTest001
 * @tc.desc: Test OverlayManager::ErasePopup.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, ErasePopupTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isBlockEvent = false;

    /**
     * @tc.steps: step2. create overlayManager and call ShowPopupAnimation.
     * @tc.expected: transitionStatus_ and visibility of layoutProperty is updated successfully
     */
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(false);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    rootNode->isLayoutComplete_ = true;
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    int32_t number = 0;
    std::function<void(int32_t)> onWillDismiss1 = [&number](int32_t reason) { number = number + 1; };
    overlayManager->ShowPopup(targetId, popupInfo, move(onWillDismiss1), true);
    overlayManager->ErasePopup(targetId);
    EXPECT_EQ(number, 0);
    EXPECT_TRUE(overlayManager->popupMap_.empty());
}

/**
 * @tc.name: PopupLifecycleCallbackTest001
 * @tc.desc: Test Popup lifecycle callbacks (onWillAppear, onDidAppear)
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupLifecycleCallbackTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isBlockEvent = false;

    /**
     * @tc.steps: step2. set lifecycle callbacks on popupParam.
     */
    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    ASSERT_NE(popupParam, nullptr);

    bool onWillAppearCalled = false;
    bool onDidAppearCalled = false;
    bool onWillDisappearCalled = false;
    bool onDidDisappearCalled = false;

    popupParam->SetOnWillAppear([&onWillAppearCalled]() {
        onWillAppearCalled = true;
    });
    popupParam->SetOnDidAppear([&onDidAppearCalled]() {
        onDidAppearCalled = true;
    });
    popupParam->SetOnWillDisappear([&onWillDisappearCalled]() {
        onWillDisappearCalled = false;
    });
    popupParam->SetOnDidDisappear([&onDidDisappearCalled]() {
        onDidDisappearCalled = true;
    });
    popupPattern->SetPopupParam(popupParam);

    /**
     * @tc.steps: step3. create overlayManager and call ShowPopup.
     * @tc.expected: onWillAppear callback should be set
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    rootNode->isLayoutComplete_ = true;
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(0);

    overlayManager->ShowPopup(targetId, popupInfo, nullptr);
    EXPECT_TRUE(overlayManager->popupMap_[targetId].isCurrentOnShow);

    /**
     * @tc.steps: step4. verify popupParam has lifecycle callbacks.
     * @tc.expected: callbacks are correctly set
     */
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);
    auto overlay = AceType::DynamicCast<NG::FrameNode>(rootUINode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    auto pattern = overlay->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    auto param = pattern->GetPopupParam();
    ASSERT_NE(param, nullptr);
    EXPECT_TRUE(param->GetOnWillAppear());
    EXPECT_TRUE(param->GetOnDidAppear());
    EXPECT_TRUE(param->GetOnWillDisappear());
    EXPECT_TRUE(param->GetOnDidDisappear());
}

/**
 * @tc.name: PopupLifecycleCallbackTest002
 * @tc.desc: Test PopupParam FireOnWillAppear and FireOnDidAppear
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupLifecycleCallbackTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create popupParam and set callbacks.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    ASSERT_NE(popupParam, nullptr);

    bool onWillAppearCalled = false;
    bool onDidAppearCalled = false;

    popupParam->SetOnWillAppear([&onWillAppearCalled]() {
        onWillAppearCalled = true;
    });
    popupParam->SetOnDidAppear([&onDidAppearCalled]() {
        onDidAppearCalled = true;
    });

    /**
     * @tc.steps: step2. call FireOnWillAppear and FireOnDidAppear.
     * @tc.expected: callbacks are invoked
     */
    EXPECT_FALSE(onWillAppearCalled);
    popupParam->FireOnWillAppear();
    EXPECT_TRUE(onWillAppearCalled);

    EXPECT_FALSE(onDidAppearCalled);
    popupParam->FireOnDidAppear();
    EXPECT_TRUE(onDidAppearCalled);
}

/**
 * @tc.name: PopupLifecycleCallbackTest003
 * @tc.desc: Test PopupParam FireOnWillDisappear and FireOnDidDisappear
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupLifecycleCallbackTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create popupParam and set callbacks.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    ASSERT_NE(popupParam, nullptr);

    bool onWillDisappearCalled = false;
    bool onDidDisappearCalled = false;

    popupParam->SetOnWillDisappear([&onWillDisappearCalled]() {
        onWillDisappearCalled = true;
    });
    popupParam->SetOnDidDisappear([&onDidDisappearCalled]() {
        onDidDisappearCalled = true;
    });

    /**
     * @tc.steps: step2. call FireOnWillDisappear and FireOnDidDisappear.
     * @tc.expected: callbacks are invoked
     */
    EXPECT_FALSE(onWillDisappearCalled);
    popupParam->FireOnWillDisappear();
    EXPECT_TRUE(onWillDisappearCalled);

    EXPECT_FALSE(onDidDisappearCalled);
    popupParam->FireOnDidDisappear();
    EXPECT_TRUE(onDidDisappearCalled);
}

/**
 * @tc.name: PopupLifecycleCallbackTest004
 * @tc.desc: Test PopupParam lifecycle callbacks with null callbacks
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, PopupLifecycleCallbackTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create popupParam without setting callbacks.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    ASSERT_NE(popupParam, nullptr);

    /**
     * @tc.steps: step2. call Fire methods without callbacks set.
     * @tc.expected: no crash occurs
     */
    popupParam->FireOnWillAppear();
    popupParam->FireOnDidAppear();
    popupParam->FireOnWillDisappear();
    popupParam->FireOnDidDisappear();
    // If we reach here, the test passes (no crash)
    EXPECT_TRUE(true);
}

/**
 * @tc.name: GetEmbeddedNodeTest001
 * @tc.desc: Test OverlayManager::GetEmbeddedNode when embeddedOverlay is set.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, GetEmbeddedNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create root node and embedded overlay.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);

    auto embeddedRootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 2, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(embeddedRootNode, nullptr);
    auto embeddedOverlayManager = AceType::MakeRefPtr<OverlayManager>(embeddedRootNode);
    ASSERT_NE(embeddedOverlayManager, nullptr);

    /**
     * @tc.steps: step2. Create popupInfo with embeddedOverlay set.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.embeddedOveraly = embeddedOverlayManager;

    /**
     * @tc.steps: step3. Call GetEmbeddedNode and verify it returns embedded root node.
     * @tc.expected: GetEmbeddedNode returns the embedded root node when embeddedOverlay is set.
     */
    auto embeddedNode = overlayManager->GetEmbeddedNode(popupInfo);
    EXPECT_EQ(embeddedNode.Upgrade(), embeddedRootNode);
}

/**
 * @tc.name: GetEmbeddedNodeTest002
 * @tc.desc: Test OverlayManager::GetEmbeddedNode when embeddedOverlay is not set.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, GetEmbeddedNodeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create root node and overlayManager.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step2. Create popupInfo without embeddedOverlay set.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
                        AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;

    /**
     * @tc.steps: step3. Call GetEmbeddedNode and verify it returns root node.
     * @tc.expected: GetEmbeddedNode returns the default root node when embeddedOverlay is not set.
     */
    auto embeddedNode = overlayManager->GetEmbeddedNode(popupInfo);
    EXPECT_EQ(embeddedNode.Upgrade(), rootNode);
}

/**
 * @tc.name: MountPopupPreventDuplicate001
 * @tc.desc: Test MountPopup prevents duplicate popup mounting for same targetId
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, MountPopupPreventDuplicate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create target node and popup nodes.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_ID_1);

    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, POPUP_NODE_ID_1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId = targetNodes[0]->GetId();
    rootNode->isLayoutComplete_ = true;

    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(POPUP_NODE_ID_ZERO);

    /**
     * @tc.steps: step2. Mount first popup successfully.
     * @tc.expected: First popup is mounted and isCurrentOnShow is true.
     */
    overlayManager->ShowPopup(targetId, popups[0], nullptr);
    EXPECT_TRUE(overlayManager->popupMap_[targetId].isCurrentOnShow);

    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);

    const auto& rootChildren = rootUINode->GetChildren();
    int32_t popupCountBefore = 0;
    for (const auto& child : rootChildren) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (childFrameNode && childFrameNode->GetPattern<BubblePattern>()) {
            popupCountBefore++;
        }
    }
    EXPECT_EQ(popupCountBefore, EXPECTED_POPUP_COUNT_ONE);

    /**
     * @tc.steps: step3. Create second popup with same targetId and try to mount.
     * @tc.expected: Second popup mounting should be prevented.
     */
    auto popupId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode2 = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId2,
        AceType::MakeRefPtr<BubblePattern>(targetId, targetNodes[0]->GetTag()));

    PopupInfo popupInfo2;
    popupInfo2.popupId = popupId2;
    popupInfo2.popupNode = popupNode2;
    popupInfo2.target = targetNodes[0];
    popupInfo2.markNeedUpdate = true;
    popupInfo2.isBlockEvent = false;

    overlayManager->MountPopup(targetId, popupInfo2, nullptr);

    /**
     * @tc.steps: step4. Verify only one popup exists on tree.
     * @tc.expected: No duplicate popup should be mounted.
     */
    int32_t popupCountAfter = 0;
    for (const auto& child : rootChildren) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (childFrameNode && childFrameNode->GetPattern<BubblePattern>()) {
            popupCountAfter++;
        }
    }
    EXPECT_EQ(popupCountAfter, popupCountBefore);
    EXPECT_EQ(popupCountAfter, EXPECTED_POPUP_COUNT_ONE);
}

/**
 * @tc.name: MountPopupPreventDuplicate002
 * @tc.desc: Test MountPopup allows mounting for different targetIds
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, MountPopupPreventDuplicate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create two different target nodes and popup nodes.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_2);

    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, POPUP_NODE_ID_1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;

    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(POPUP_NODE_ID_ZERO);

    /**
     * @tc.steps: step2. Mount first popup for targetId1.
     * @tc.expected: First popup is mounted successfully.
     */
    overlayManager->MountPopup(targetId1, popups[0], nullptr);
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);

    /**
     * @tc.steps: step3. Mount second popup for different targetId2.
     * @tc.expected: Second popup should also be mounted successfully.
     */
    overlayManager->MountPopup(targetId2, popups[1], nullptr);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);

    /**
     * @tc.steps: step4. Verify both popups exist on tree.
     * @tc.expected: Two popups should be mounted for different targetIds.
     */
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);

    const auto& rootChildren = rootUINode->GetChildren();
    int32_t popupCount = 0;
    for (const auto& child : rootChildren) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (childFrameNode && childFrameNode->GetPattern<BubblePattern>()) {
            popupCount++;
        }
    }
    EXPECT_EQ(popupCount, EXPECTED_POPUP_COUNT_TWO);
}

/**
 * @tc.name: MountPopupPreventDuplicate003
 * @tc.desc: Test MountPopup prevents duplicate when ShowPopup called twice quickly
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, MountPopupPreventDuplicate003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create target node and two popup nodes with same targetId.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_ID_1);

    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, POPUP_NODE_ID_1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId = targetNodes[0]->GetId();
    rootNode->isLayoutComplete_ = true;

    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(POPUP_NODE_ID_ZERO);

    /**
     * @tc.steps: step2. Create second popup info with same targetId.
     */
    auto popupId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode2 = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId2,
        AceType::MakeRefPtr<BubblePattern>(targetId, targetNodes[0]->GetTag()));

    PopupInfo popupInfo2;
    popupInfo2.popupId = popupId2;
    popupInfo2.popupNode = popupNode2;
    popupInfo2.target = targetNodes[0];
    popupInfo2.markNeedUpdate = true;
    popupInfo2.isBlockEvent = false;

    /**
     * @tc.steps: step3. Call ShowPopup twice quickly with same targetId.
     * @tc.expected: Second popup should be prevented from mounting.
     */
    overlayManager->ShowPopup(targetId, popups[0], nullptr);
    overlayManager->ShowPopup(targetId, popupInfo2, nullptr);

    /**
     * @tc.steps: step4. Verify only one popup exists on tree after both calls.
     * @tc.expected: Duplicate mounting prevented, only one popup on tree.
     */
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);

    const auto& rootChildren = rootUINode->GetChildren();
    int32_t popupCount = 0;
    for (const auto& child : rootChildren) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (childFrameNode && childFrameNode->GetPattern<BubblePattern>()) {
            popupCount++;
        }
    }
    EXPECT_LE(popupCount, EXPECTED_POPUP_COUNT_ONE);
}

/**
 * @tc.name: MountPopupPreventDuplicate004
 * @tc.desc: Test MountPopup check logic with null rootNode
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, MountPopupPreventDuplicate004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create overlayManager with null rootNode scenario.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, POPUP_NODE_ID_1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_ID_1);
    auto targetId = targetNodes[0]->GetId();

    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(POPUP_NODE_ID_ZERO);

    /**
     * @tc.steps: step2. Call MountPopup after rootNode is destroyed.
     * @tc.expected: MountPopup should handle null rootNode gracefully.
     */
    overlayManager->rootNodeWeak_ = WeakPtr<FrameNode>();  // Set to null
    overlayManager->MountPopup(targetId, popups[0], nullptr);

    // Test passes if no crash occurs
    EXPECT_TRUE(true);
}

/**
 * @tc.name: MountPopupPreventDuplicate005
 * @tc.desc: Test MountPopup check logic when popupNode is already mounted
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, MountPopupPreventDuplicate005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and mount first popup.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_ID_1);

    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, POPUP_NODE_ID_1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId = targetNodes[0]->GetId();
    rootNode->isLayoutComplete_ = true;

    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(POPUP_NODE_ID_ZERO);

    overlayManager->MountPopup(targetId, popups[0], nullptr);

    /**
     * @tc.steps: step2. Try to mount the same popupNode again.
     * @tc.expected: Mounting the same popupNode should not create duplicate.
     */
    overlayManager->MountPopup(targetId, popups[0], nullptr);

    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);

    const auto& rootChildren = rootUINode->GetChildren();
    int32_t popupCount = 0;
    for (const auto& child : rootChildren) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (childFrameNode && childFrameNode->GetPattern<BubblePattern>()) {
            popupCount++;
        }
    }
    EXPECT_EQ(popupCount, EXPECTED_POPUP_COUNT_ONE);
}

/**
 * @tc.name: MountPopupPreventDuplicate006
 * @tc.desc: Test MountPopup when popupMap_ has no record for targetId
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerPopupTestNg, MountPopupPreventDuplicate006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create targetNode and popupInfo without adding to popupMap_.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    CreatePopupNodes(targetNodes, popups, POPUP_NODE_ID_1);

    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, POPUP_NODE_ID_1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId = targetNodes[0]->GetId();
    rootNode->isLayoutComplete_ = true;

    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetInstallationFree(POPUP_NODE_ID_ZERO);

    /**
     * @tc.steps: step2. Ensure popupMap_ has no record for this targetId.
     * @tc.expected: popupMap_ should not contain targetId.
     */
    EXPECT_FALSE(overlayManager->HasPopupInfo(targetId));

    /**
     * @tc.steps: step3. Call MountPopup directly without ShowPopup (popupMap_ empty).
     * @tc.expected: MountPopup should proceed when popupMap_ has no record.
     */
    overlayManager->MountPopup(targetId, popups[0], nullptr);

    /**
     * @tc.steps: step4. Verify popup is mounted successfully.
     * @tc.expected: Popup should be mounted even though popupMap_ initially had no record.
     */
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootUINode, nullptr);

    const auto& rootChildren = rootUINode->GetChildren();
    int32_t popupCount = 0;
    for (const auto& child : rootChildren) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (childFrameNode && childFrameNode->GetPattern<BubblePattern>()) {
            popupCount++;
        }
    }
    EXPECT_EQ(popupCount, EXPECTED_POPUP_COUNT_ONE);
}
} // namespace OHOS::Ace::NG