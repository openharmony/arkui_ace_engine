/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#define protected public
#define private public

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/manager/shared_overlay/shared_overlay_manager.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string ROOT_TAG = "root";
const std::string NODE_TAG = "node";
const std::string SHARE_ID1("id1");
const std::string SHARE_ID2("id2");
const SizeF SRC_SIZE(100.0f, 100.0f);
const SizeF DEST_SIZE(200.0f, 200.0f);
const int32_t SRC_DURATION = 500;
const int32_t DEST_DURATION = 1000;

RefPtr<FrameNode> CreateSharedNode(const std::string& shareId, const int32_t& duration, const SizeF& frameSize)
{
    auto node = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>(), false);
    node->GetRenderContext()->SetShareId(shareId);
    auto option = std::make_shared<SharedTransitionOption>();
    option->curve = Curves::LINEAR;
    option->duration = duration;
    option->type = SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE;
    node->GetRenderContext()->SetSharedTransitionOptions(option);
    node->GetGeometryNode()->SetFrameSize(frameSize);
    return node;
}
} // namespace

class SharedOverlayManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override;
    void TearDown() override;

private:
    RefPtr<SharedOverlayManager> manager_;
    RefPtr<FrameNode> srcPage_;
    RefPtr<FrameNode> destPage_;
};

void SharedOverlayManagerTestNg::SetUp()
{
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    manager_ = AceType::MakeRefPtr<SharedOverlayManager>(root);
    srcPage_ = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<PagePattern>(nullptr), false);
    destPage_ = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<PagePattern>(nullptr), false);
}

void SharedOverlayManagerTestNg::TearDown()
{
    manager_.Reset();
    srcPage_.Reset();
    destPage_.Reset();
}

/**
 * @tc.name: SharedOverlayManagerTest001
 * @tc.desc: There is no matching shareId, so it cannot perform sharedTransition.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SharedOverlayManagerTestNg, SharedOverlayManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a SharedOverlayManager
     */
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto sharedOverlayManager = AceType::MakeRefPtr<SharedOverlayManager>(root);

    /**
     * @tc.steps: step2. construct two frameNodes which type is Page and pageInfo is default config
     */
    auto srcPageInfo = AceType::MakeRefPtr<PageInfo>();
    auto destPageInfo = AceType::MakeRefPtr<PageInfo>();
    auto pageSrc = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<PagePattern>(srcPageInfo));
    auto pageDest = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<PagePattern>(destPageInfo));

    /**
     * @tc.steps: step3. call StartSharedTransition
     * @tc.expected: step3. effects_ is empty for page has no sharedTransitionEffect
     */
    sharedOverlayManager->StartSharedTransition(pageSrc, pageDest);
    EXPECT_EQ(sharedOverlayManager->effects_.size(), 0);

    /**
     * @tc.steps: step4. Add a node configured with exchange sharedTransition to source page,
     *            and add a node with no sharedTransition to destination page
     */
    sharedOverlayManager->effects_.clear();
    auto shareNodeSrc = CreateSharedNode(SHARE_ID1, SRC_DURATION, SRC_SIZE);
    pageSrc->AddChild(shareNodeSrc);
    pageSrc->GetPattern<PagePattern>()->sharedTransitionMap_.emplace(SHARE_ID1, shareNodeSrc);
    auto nodeDest = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>(), false);
    pageDest->AddChild(nodeDest);

    /**
     * @tc.steps: step5. call StartSharedTransition
     * @tc.expected: effects_ is empty because there is no node configured with exchange sharedTransition
     *               in destination page
     */
    sharedOverlayManager->StartSharedTransition(pageSrc, pageDest);
    EXPECT_EQ(sharedOverlayManager->effects_.size(), 0);

    /**
     * @tc.steps: step6. Clear the nodes of dest page, and add a node configured with exchange sharedTransition
     *            to destination page, but the shareId is different from that of the node in source page
     */
    sharedOverlayManager->effects_.clear();
    pageDest->RemoveChild(nodeDest);
    auto shareNodeDest = CreateSharedNode(SHARE_ID2, DEST_DURATION, DEST_SIZE);
    pageDest->AddChild(shareNodeDest);
    pageDest->GetPattern<PagePattern>()->sharedTransitionMap_.emplace(SHARE_ID2, shareNodeDest);

    /**
     * @tc.steps: step7. call StartSharedTransition
     * @tc.expected: effects_ is empty because the node in source page and the node in destination page have
     *               different shareId
     */
    sharedOverlayManager->PrepareSharedTransition(pageSrc, pageDest);
    EXPECT_EQ(sharedOverlayManager->effects_.size(), 0);
}

/**
 * @tc.name: SharedOverlayManagerTest002
 * @tc.desc: Build a sharedTransition node with the same share id on the source page and the destination page
 *           and perform sharedTransition successfully
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SharedOverlayManagerTestNg, SharedOverlayManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add node configured with same shareId to source page and destination page respectively
     */
    auto srcNodeShareId1 = CreateSharedNode(SHARE_ID1, SRC_DURATION, SRC_SIZE);
    srcPage_->AddChild(srcNodeShareId1);
    srcPage_->GetPattern<PagePattern>()->sharedTransitionMap_.emplace(SHARE_ID1, srcNodeShareId1);
    auto destNodeShareId1 = CreateSharedNode(SHARE_ID1, DEST_DURATION, DEST_SIZE);
    destPage_->AddChild(destNodeShareId1);
    destPage_->GetPattern<PagePattern>()->sharedTransitionMap_.emplace(SHARE_ID1, destNodeShareId1);

    /**
     * @tc.steps: step2. call StartSharedTransition
     * @tc.expected: effects_ has one expected effect. The node in source page has been removed and is mounted to
     *               sharedManager
     */
    manager_->StartSharedTransition(srcPage_, destPage_);
    ASSERT_EQ(manager_->effects_.size(), 1);
    auto effect = *manager_->effects_.begin();
    EXPECT_EQ(effect->GetType(), SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE);
    EXPECT_EQ(effect->GetSrcSharedNode().Upgrade(), srcNodeShareId1);
    EXPECT_EQ(effect->GetDestSharedNode().Upgrade(), destNodeShareId1);
    EXPECT_EQ(effect->GetShareId(), SHARE_ID1);
    ASSERT_TRUE(effect->GetOption() != nullptr);
    EXPECT_EQ(effect->GetOption()->duration, DEST_DURATION);
    ASSERT_EQ(manager_->sharedManager_->GetChildren().size(), 1);
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(manager_->sharedManager_->GetFirstChild()), srcNodeShareId1);
    ASSERT_EQ(srcPage_->GetChildren().size(), 1);
    EXPECT_NE(AceType::DynamicCast<FrameNode>(srcPage_->GetFirstChild()), srcNodeShareId1);

    /**
     * @tc.steps: step3. Notify the controller of effect to stop so the sharedTransition can finish
     * @tc.expected: The node mounted to sharedManager has been removed and is mounted to the original parent
     */
    auto controller = effect->GetController();
    ASSERT_TRUE(controller != nullptr);
    controller->Stop();
    EXPECT_EQ(manager_->sharedManager_->GetChildren().size(), 0);
    ASSERT_EQ(srcPage_->GetChildren().size(), 1);
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(srcPage_->GetFirstChild()), srcNodeShareId1);
}

/**
 * @tc.name: SharedOverlayManagerTest003
 * @tc.desc: Build a node configured with static sharedTransition in source page and perform sharedTransition
 *           successfully
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SharedOverlayManagerTestNg, SharedOverlayManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add a node configured with static sharedTransition to source page
     */
    auto srcNodeShareId1 = CreateSharedNode(SHARE_ID1, SRC_DURATION, SRC_SIZE);
    srcNodeShareId1->GetRenderContext()->GetSharedTransitionOption()->type =
        SharedTransitionEffectType::SHARED_EFFECT_STATIC;
    srcPage_->AddChild(srcNodeShareId1);
    srcPage_->GetPattern<PagePattern>()->sharedTransitionMap_.emplace(SHARE_ID1, srcNodeShareId1);

    /**
     * @tc.steps: step2. call StartSharedTransition
     * @tc.expected: effects_ has one expected effect. The node in source page has been removed and is mounted to
     *               sharedManager
     */
    manager_->StartSharedTransition(srcPage_, destPage_);
    ASSERT_EQ(manager_->effects_.size(), 1);
    auto effect = *manager_->effects_.begin();
    ASSERT_EQ(effect->GetType(), SharedTransitionEffectType::SHARED_EFFECT_STATIC);
    EXPECT_EQ(effect->GetSrcSharedNode().Upgrade(), srcNodeShareId1);
    EXPECT_EQ(effect->GetDestSharedNode().Upgrade(), nullptr);
    EXPECT_EQ(effect->GetShareId(), SHARE_ID1);
    ASSERT_TRUE(effect->GetOption() != nullptr);
    EXPECT_EQ(effect->GetOption()->duration, SRC_DURATION);
    auto staticEffect = AceType::DynamicCast<SharedTransitionStatic>(effect);
    EXPECT_EQ(staticEffect->GetPassengerNode().Upgrade(), srcNodeShareId1);
    ASSERT_EQ(manager_->sharedManager_->GetChildren().size(), 1);
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(manager_->sharedManager_->GetFirstChild()), srcNodeShareId1);
    ASSERT_EQ(srcPage_->GetChildren().size(), 1);
    EXPECT_NE(AceType::DynamicCast<FrameNode>(srcPage_->GetFirstChild()), srcNodeShareId1);

    /**
     * @tc.steps: step3. Notify the controller of effect to stop so the sharedTransition can finish
     * @tc.expected: The node mounted to sharedManager has been removed and is mounted to the original parent
     */
    auto controller = effect->GetController();
    ASSERT_TRUE(controller != nullptr);
    controller->Stop();
    EXPECT_EQ(manager_->sharedManager_->GetChildren().size(), 0);
    ASSERT_EQ(srcPage_->GetChildren().size(), 1);
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(srcPage_->GetFirstChild()), srcNodeShareId1);
}

/**
 * @tc.name: SharedOverlayManagerTest004
 * @tc.desc: Build a node configured with static sharedTransition in destination page and perform sharedTransition
 *           successfully
 * @tc.type: FUNC
 */
HWTEST_F(SharedOverlayManagerTestNg, SharedOverlayManagerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add a node configured with static sharedTransition to destination page
     */
    auto destNodeShareId1 = CreateSharedNode(SHARE_ID1, DEST_DURATION, DEST_SIZE);
    destNodeShareId1->GetRenderContext()->GetSharedTransitionOption()->type =
        SharedTransitionEffectType::SHARED_EFFECT_STATIC;
    destPage_->AddChild(destNodeShareId1);
    destPage_->GetPattern<PagePattern>()->sharedTransitionMap_.emplace(SHARE_ID1, destNodeShareId1);

    /**
     * @tc.steps: step2. call StartSharedTransition
     * @tc.expected: effects_ has one expected effect. The node in destination page has been removed and is mounted to
     *               sharedManager
     */
    manager_->StartSharedTransition(srcPage_, destPage_);
    ASSERT_EQ(manager_->effects_.size(), 1);
    auto effect = *manager_->effects_.begin();
    ASSERT_EQ(effect->GetType(), SharedTransitionEffectType::SHARED_EFFECT_STATIC);
    EXPECT_EQ(effect->GetSrcSharedNode().Upgrade(), nullptr);
    EXPECT_EQ(effect->GetDestSharedNode().Upgrade(), destNodeShareId1);
    EXPECT_EQ(effect->GetShareId(), SHARE_ID1);
    ASSERT_TRUE(effect->GetOption() != nullptr);
    EXPECT_EQ(effect->GetOption()->duration, DEST_DURATION);
    auto staticEffect = AceType::DynamicCast<SharedTransitionStatic>(effect);
    EXPECT_EQ(staticEffect->GetPassengerNode().Upgrade(), destNodeShareId1);
    ASSERT_EQ(manager_->sharedManager_->GetChildren().size(), 1);
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(manager_->sharedManager_->GetFirstChild()), destNodeShareId1);
    ASSERT_EQ(destPage_->GetChildren().size(), 1);
    EXPECT_NE(destPage_->GetFirstChild(), destNodeShareId1);

    /**
     * @tc.steps: step3. Call StopSharedTransition to test it
     * @tc.expected: The node mounted to sharedManager has been removed and is mounted to the original parent
     */
    manager_->StopSharedTransition();
    EXPECT_EQ(manager_->sharedManager_->GetChildren().size(), 0);
    ASSERT_EQ(destPage_->GetChildren().size(), 1);
    EXPECT_EQ(destPage_->GetFirstChild(), destNodeShareId1);
}
} // namespace OHOS::Ace::NG
