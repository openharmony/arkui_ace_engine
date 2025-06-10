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
using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t POPUP_NODE_2 = 2;
const std::string MESSAGE = "hello world";
const std::string BOTTOMSTRING = "test";
constexpr int32_t DURATION = 2;
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
 * @tc.name: ToastTest001
 * @tc.desc: Test OverlayManager::ClearToast.
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
     * @tc.expected: toastMap_ is empty
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
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    rootNode->isLayoutComplete_ = true;
    
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
} // namespace OHOS::Ace::NG