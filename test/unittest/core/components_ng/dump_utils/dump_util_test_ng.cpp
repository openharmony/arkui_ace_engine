/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "base/memory/ace_type.h"

#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#undef private
#undef protected

#include "core/components_ng/dump_utils/dump_util.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t ROOT_NODE_ID = 3000;
constexpr int32_t PAGE_NODE_ID = 3001;
constexpr int32_t DIALOG_NODE_ID = 3002;
constexpr int32_t TOAST_NODE_ID = 3003;
constexpr int32_t NON_OVERLAY_NODE_ID = 3004;
constexpr int32_t CONTAINER_MODAL_NODE_ID = 3005;
constexpr int32_t COLUMN_NODE_ID = 3006;
constexpr int32_t TITLE_NODE_ID = 3007;
constexpr int32_t STACK_NODE_ID = 3008;
constexpr int32_t ROOT_TOAST_NODE_ID = 3009;
constexpr int32_t ATOMIC_NODE_ID = 3010;
constexpr int32_t ATOMIC_ROOT_NODE_ID = 3011;
constexpr int32_t ATOMIC_DIALOG_NODE_ID = 3012;

RefPtr<FrameNode> CreateNode(const std::string& tag, int32_t nodeId)
{
    auto node = FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
    return node;
}

RefPtr<FrameNode> CreatePageNode()
{
    return CreateNode(V2::PAGE_ETS_TAG, PAGE_NODE_ID);
}
} // namespace

class DumpUtilTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void DumpUtilTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void DumpUtilTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: DumpUtil_IsTagInOverlay001
 * @tc.desc: Test IsTagInOverlay returns true for all known overlay tags and false otherwise.
 * @tc.type: FUNC
 */
HWTEST_F(DumpUtilTestNg, DumpUtil_IsTagInOverlay001, TestSize.Level1)
{
    EXPECT_TRUE(DumpUtil::IsTagInOverlay(V2::TOAST_ETS_TAG));
    EXPECT_TRUE(DumpUtil::IsTagInOverlay(V2::POPUP_ETS_TAG));
    EXPECT_TRUE(DumpUtil::IsTagInOverlay(V2::DIALOG_ETS_TAG));
    EXPECT_TRUE(DumpUtil::IsTagInOverlay(V2::ACTION_SHEET_DIALOG_ETS_TAG));
    EXPECT_TRUE(DumpUtil::IsTagInOverlay(V2::ALERT_DIALOG_ETS_TAG));
    EXPECT_TRUE(DumpUtil::IsTagInOverlay(V2::MENU_ETS_TAG));
    EXPECT_TRUE(DumpUtil::IsTagInOverlay(V2::MENU_WRAPPER_ETS_TAG));
    EXPECT_TRUE(DumpUtil::IsTagInOverlay(V2::SHEET_PAGE_TAG));
    EXPECT_TRUE(DumpUtil::IsTagInOverlay(V2::MODAL_PAGE_TAG));
    EXPECT_TRUE(DumpUtil::IsTagInOverlay(V2::SHEET_WRAPPER_TAG));
    EXPECT_TRUE(DumpUtil::IsTagInOverlay(V2::OVERLAY_ETS_TAG));
    EXPECT_TRUE(DumpUtil::IsTagInOverlay(V2::ORDER_OVERLAY_ETS_TAG));
    EXPECT_FALSE(DumpUtil::IsTagInOverlay(V2::PAGE_ETS_TAG));
    EXPECT_FALSE(DumpUtil::IsTagInOverlay(V2::ROOT_ETS_TAG));
    EXPECT_FALSE(DumpUtil::IsTagInOverlay(V2::STAGE_ETS_TAG));
    EXPECT_FALSE(DumpUtil::IsTagInOverlay(""));
}

/**
 * @tc.name: DumpUtil_CollectStartNodes001
 * @tc.desc: Test CollectInspectorStartNodes with null inputs returns an empty set.
 * @tc.type: FUNC
 */
HWTEST_F(DumpUtilTestNg, DumpUtil_CollectStartNodes001, TestSize.Level1)
{
    auto set = DumpUtil::CollectInspectorStartNodes(nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(set.dumpBeginNode, nullptr);
    EXPECT_EQ(set.containerModalTitleRow, nullptr);
    EXPECT_EQ(set.atomicServiceRoot, nullptr);
    EXPECT_EQ(set.atomicServiceMenuBar, nullptr);
    EXPECT_TRUE(set.pageStartNodes.empty());
    EXPECT_TRUE(set.overlayNodes.empty());
}

/**
 * @tc.name: DumpUtil_CollectStartNodes002
 * @tc.desc: Test dumpBeginNode falls back to rootNode when no container modal.
 * @tc.type: FUNC
 */
HWTEST_F(DumpUtilTestNg, DumpUtil_CollectStartNodes002, TestSize.Level1)
{
    auto rootNode = CreateNode(V2::ROOT_ETS_TAG, ROOT_NODE_ID);
    auto set = DumpUtil::CollectInspectorStartNodes(rootNode, nullptr, nullptr, nullptr);
    ASSERT_TRUE(set.dumpBeginNode);
    EXPECT_EQ(set.dumpBeginNode->GetId(), ROOT_NODE_ID);
    EXPECT_EQ(set.containerModalTitleRow, nullptr);
    EXPECT_EQ(set.atomicServiceRoot, nullptr);
}

/**
 * @tc.name: DumpUtil_CollectStartNodes003
 * @tc.desc: Test overlayNodes collects only root direct children whose tag is in overlay set.
 * @tc.type: FUNC
 */
HWTEST_F(DumpUtilTestNg, DumpUtil_CollectStartNodes003, TestSize.Level1)
{
    auto rootNode = CreateNode(V2::ROOT_ETS_TAG, ROOT_NODE_ID);
    auto dialogChild = CreateNode(V2::DIALOG_ETS_TAG, DIALOG_NODE_ID);
    auto toastChild = CreateNode(V2::TOAST_ETS_TAG, TOAST_NODE_ID);
    auto nonOverlayChild = CreateNode(V2::PAGE_ETS_TAG, NON_OVERLAY_NODE_ID);
    dialogChild->MountToParent(rootNode);
    toastChild->MountToParent(rootNode);
    nonOverlayChild->MountToParent(rootNode);

    auto set = DumpUtil::CollectInspectorStartNodes(rootNode, nullptr, nullptr, nullptr);
    EXPECT_EQ(set.overlayNodes.size(), 2u);
    bool hasDialog = false;
    bool hasToast = false;
    for (const auto& node : set.overlayNodes) {
        if (node->GetId() == DIALOG_NODE_ID) {
            hasDialog = true;
        }
        if (node->GetId() == TOAST_NODE_ID) {
            hasToast = true;
        }
    }
    EXPECT_TRUE(hasDialog);
    EXPECT_TRUE(hasToast);
}

/**
 * @tc.name: DumpUtil_CollectStartNodes004
 * @tc.desc: Test pageStartNodes falls back to lastPageNode when no nav destination is found.
 * @tc.type: FUNC
 */
HWTEST_F(DumpUtilTestNg, DumpUtil_CollectStartNodes004, TestSize.Level1)
{
    auto rootNode = CreateNode(V2::ROOT_ETS_TAG, ROOT_NODE_ID);
    auto lastPage = CreatePageNode();
    auto set = DumpUtil::CollectInspectorStartNodes(rootNode, nullptr, lastPage, nullptr);
    ASSERT_EQ(set.pageStartNodes.size(), 1u);
    EXPECT_EQ(set.pageStartNodes.front()->GetId(), PAGE_NODE_ID);
}

/**
 * @tc.name: DumpUtil_CollectStartNodes005
 * @tc.desc: Test atomic service branch stays null when overlayManager is null.
 * @tc.type: FUNC
 */
HWTEST_F(DumpUtilTestNg, DumpUtil_CollectStartNodes005, TestSize.Level1)
{
    auto rootNode = CreateNode(V2::ROOT_ETS_TAG, ROOT_NODE_ID);
    // Add an AtomicService child under root; util should not dereference a null overlayManager.
    auto atomicChild = CreateNode(V2::ATOMIC_SERVICE_ETS_TAG, 3099);
    atomicChild->MountToParent(rootNode);

    auto set = DumpUtil::CollectInspectorStartNodes(rootNode, nullptr, nullptr, nullptr);
    EXPECT_EQ(set.atomicServiceRoot, nullptr);
    EXPECT_EQ(set.atomicServiceMenuBar, nullptr);
}

/**
 * @tc.name: DumpUtil_CollectStartNodes006
 * @tc.desc: Test CollectInspectorStartNodes with a real OverlayManager resolves atomic service via key.
 * @tc.type: FUNC
 */
HWTEST_F(DumpUtilTestNg, DumpUtil_CollectStartNodes006, TestSize.Level1)
{
    auto rootNode = CreateNode(V2::ROOT_ETS_TAG, ROOT_NODE_ID);
    auto atomicChild = CreateNode(V2::ATOMIC_SERVICE_ETS_TAG, 3099);
    atomicChild->MountToParent(rootNode);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    auto set = DumpUtil::CollectInspectorStartNodes(rootNode, nullptr, nullptr, overlayManager);
    // The test OverlayManager does not register children by key, so atomic
    // service root stays null; this verifies the lookup path is exercised
    // without crashing.
    EXPECT_EQ(set.atomicServiceRoot, nullptr);
}

/**
 * @tc.name: DumpUtil_CollectStartNodes007
 * @tc.desc: Test ContainerModal overlays are collected from both the inner stack and pipeline root.
 * @tc.type: FUNC
 */
HWTEST_F(DumpUtilTestNg, DumpUtil_CollectStartNodes007, TestSize.Level1)
{
    auto rootNode = CreateNode(V2::ROOT_ETS_TAG, ROOT_NODE_ID);
    auto containerModalNode = FrameNode::CreateFrameNode(
        "ContainerModal", CONTAINER_MODAL_NODE_ID, AceType::MakeRefPtr<ContainerModalPattern>());
    auto columnNode = CreateNode(V2::COLUMN_ETS_TAG, COLUMN_NODE_ID);
    auto titleNode = CreateNode(V2::ROW_ETS_TAG, TITLE_NODE_ID);
    auto stackNode = CreateNode(V2::STACK_ETS_TAG, STACK_NODE_ID);
    auto stackDialogNode = CreateNode(V2::DIALOG_ETS_TAG, DIALOG_NODE_ID);
    auto rootToastNode = CreateNode(V2::TOAST_ETS_TAG, ROOT_TOAST_NODE_ID);
    containerModalNode->MountToParent(rootNode);
    columnNode->MountToParent(containerModalNode);
    titleNode->MountToParent(columnNode);
    stackNode->MountToParent(columnNode);
    stackDialogNode->MountToParent(stackNode);
    rootToastNode->MountToParent(rootNode);

    auto set = DumpUtil::CollectInspectorStartNodes(rootNode, containerModalNode, nullptr, nullptr);

    ASSERT_EQ(set.dumpBeginNode, stackNode);
    ASSERT_EQ(set.overlayNodes.size(), 2u);
    EXPECT_EQ(set.overlayNodes[0], stackDialogNode);
    EXPECT_EQ(set.overlayNodes[1], rootToastNode);
}

/**
 * @tc.name: DumpUtil_CollectStartNodes008
 * @tc.desc: Test AtomicService contributes only its direct overlay children as PageScene roots.
 * @tc.type: FUNC
 */
HWTEST_F(DumpUtilTestNg, DumpUtil_CollectStartNodes008, TestSize.Level1)
{
    auto rootNode = CreateNode(V2::ROOT_ETS_TAG, ROOT_NODE_ID);
    auto atomicNode = CreateNode(V2::ATOMIC_SERVICE_ETS_TAG, ATOMIC_NODE_ID);
    auto atomicRootNode = CreateNode(V2::COLUMN_ETS_TAG, ATOMIC_ROOT_NODE_ID);
    auto atomicDialogNode = CreateNode(V2::DIALOG_ETS_TAG, ATOMIC_DIALOG_NODE_ID);
    atomicRootNode->UpdateInspectorId("AtomicServiceContainerId");
    atomicNode->MountToParent(rootNode);
    atomicRootNode->MountToParent(atomicNode);
    atomicDialogNode->MountToParent(atomicRootNode);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    auto set = DumpUtil::CollectInspectorStartNodes(rootNode, nullptr, nullptr, overlayManager);

    ASSERT_EQ(set.atomicServiceRoot, atomicRootNode);
    ASSERT_EQ(set.overlayNodes.size(), 1u);
    EXPECT_EQ(set.overlayNodes.front(), atomicDialogNode);
}
} // namespace OHOS::Ace::NG
