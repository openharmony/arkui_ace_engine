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
} // namespace OHOS::Ace::NG