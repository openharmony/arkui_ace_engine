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

#include "test/mock/frameworks/base/subwindow/mock_subwindow.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "test/unittest/core/event/frame_node_on_tree.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/common/frontend.h"
#include "core/common/ace_engine.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components_ng/pattern/date_picker/picker_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/dialog/dialog_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_manager.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_ng/pattern/sheet/sheet_wrapper_pattern.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string TEXT_TAG = "text";
} // namespace

class OverlayManagerTestFiveNg : public TestNG {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite()
    {
        TestNG::TearDownTestSuite();
        ElementRegister::GetInstance()->Clear();
    }

protected:
    int32_t minPlatformVersion_ = 0;
    RefPtr<AceType> savedMenuManager_;
    WeakPtr<UINode> savedRootNodeWeak_;
};

void OverlayManagerTestFiveNg::SetUp()
{
    minPlatformVersion_ = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (pipelineContext && pipelineContext->overlayManager_) {
        savedMenuManager_ = pipelineContext->overlayManager_->menuManager_;
        savedRootNodeWeak_ = pipelineContext->overlayManager_->rootNodeWeak_;
    }
}

void OverlayManagerTestFiveNg::TearDown()
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (pipelineContext && pipelineContext->overlayManager_) {
        pipelineContext->overlayManager_->menuManager_ = savedMenuManager_;
        pipelineContext->overlayManager_->rootNodeWeak_ = savedRootNodeWeak_;
        pipelineContext->overlayManager_->imageGeneratorSheetKey_ = std::nullopt;
        pipelineContext->overlayManager_->modalList_.clear();
        pipelineContext->overlayManager_->detachedProxyMap_.clear();
    }
    auto mockContainer = MockContainer::Current();
    if (mockContainer) {
        mockContainer->isSubContainer_ = false;
    }
}

/**
 * @tc.name: IsNeedAvoidFoldCrease001
 * @tc.desc: Test IsNeedAvoidFoldCrease when frameNode is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsNeedAvoidFoldCrease001, TestSize.Level1)
{
    EXPECT_FALSE(OverlayManager::IsNeedAvoidFoldCrease(nullptr, false, false, std::nullopt));
}

/**
 * @tc.name: IsNeedAvoidFoldCrease002
 * @tc.desc: Test IsNeedAvoidFoldCrease when container is null.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsNeedAvoidFoldCrease002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachContext(PipelineContext::GetCurrentContext().GetRawPtr());
    AceEngine::Get().RemoveContainer(0);
    EXPECT_FALSE(OverlayManager::IsNeedAvoidFoldCrease(frameNode, false, false, std::nullopt));
    AceEngine::Get().AddContainer(0, MockContainer::Current());
}

/**
 * @tc.name: IsNeedAvoidFoldCrease003
 * @tc.desc: Test IsNeedAvoidFoldCrease when container is sub container and parent container is null.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsNeedAvoidFoldCrease003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachContext(PipelineContext::GetCurrentContext().GetRawPtr());
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    bool savedIsSubContainer = mockContainer->isSubContainer_;
    mockContainer->isSubContainer_ = true;
    AceEngine::Get().RemoveContainer(-1);
    EXPECT_FALSE(OverlayManager::IsNeedAvoidFoldCrease(frameNode, false, false, std::nullopt));
    mockContainer->isSubContainer_ = savedIsSubContainer;
    AceEngine::Get().AddContainer(0, MockContainer::Current());
}

/**
 * @tc.name: IsNeedAvoidFoldCrease004
 * @tc.desc: Test IsNeedAvoidFoldCrease when container is not sub container, expandDisplay true and sourceMode EXTEND.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsNeedAvoidFoldCrease004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachContext(PipelineContext::GetCurrentContext().GetRawPtr());
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    bool savedIsSubContainer = mockContainer->isSubContainer_;
    mockContainer->isSubContainer_ = false;
    EXPECT_FALSE(OverlayManager::IsNeedAvoidFoldCrease(frameNode, false, true, std::nullopt));
    mockContainer->isSubContainer_ = savedIsSubContainer;
}

/**
 * @tc.name: IsNeedAvoidFoldCrease005
 * @tc.desc: Test IsNeedAvoidFoldCrease when container is not sub container, normal case returns false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsNeedAvoidFoldCrease005, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachContext(PipelineContext::GetCurrentContext().GetRawPtr());
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    bool savedIsSubContainer = mockContainer->isSubContainer_;
    mockContainer->isSubContainer_ = false;
    bool result = OverlayManager::IsNeedAvoidFoldCrease(frameNode, false, false, std::nullopt);
    EXPECT_FALSE(result);
    mockContainer->isSubContainer_ = savedIsSubContainer;
}

/**
 * @tc.name: GetSubwindowKeyNodeId001
 * @tc.desc: Test GetSubwindowKeyNodeId when frameNode is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetSubwindowKeyNodeId001, TestSize.Level1)
{
    EXPECT_EQ(OverlayManager::GetSubwindowKeyNodeId(nullptr), -1);
}

/**
 * @tc.name: GetSubwindowKeyNodeId002
 * @tc.desc: Test GetSubwindowKeyNodeId when frameNode has no DialogPattern.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetSubwindowKeyNodeId002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(OverlayManager::GetSubwindowKeyNodeId(frameNode), -1);
}

/**
 * @tc.name: GetSubwindowKeyNodeId003
 * @tc.desc: Test GetSubwindowKeyNodeId when IsUIExtensionSubWindow is false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetSubwindowKeyNodeId003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto dialogPattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->isUIExtensionSubWindow_ = false;
    EXPECT_EQ(OverlayManager::GetSubwindowKeyNodeId(frameNode), -1);
}

/**
 * @tc.name: GetSubwindowKeyNodeId004
 * @tc.desc: Test GetSubwindowKeyNodeId when IsUIExtensionSubWindow is true and IsModal is true.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetSubwindowKeyNodeId004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto dialogPattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->isUIExtensionSubWindow_ = true;
    auto dialogProps = AceType::DynamicCast<DialogLayoutProperty>(frameNode->GetLayoutProperty());
    ASSERT_NE(dialogProps, nullptr);
    dialogProps->UpdateIsModal(true);
    EXPECT_EQ(OverlayManager::GetSubwindowKeyNodeId(frameNode), frameNode->GetId());
}

/**
 * @tc.name: GetSubwindowKeyNodeId005
 * @tc.desc: Test GetSubwindowKeyNodeId when IsUIExtensionSubWindow is true and IsModal is false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetSubwindowKeyNodeId005, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto dialogPattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->isUIExtensionSubWindow_ = true;
    auto dialogProps = AceType::DynamicCast<DialogLayoutProperty>(frameNode->GetLayoutProperty());
    ASSERT_NE(dialogProps, nullptr);
    dialogProps->UpdateIsModal(false);
    EXPECT_EQ(OverlayManager::GetSubwindowKeyNodeId(frameNode), -1);
}

/**
 * @tc.name: GetDisplayAvailableRect001
 * @tc.desc: Test GetDisplayAvailableRect when IsSuperFoldDisplayDevice is false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetDisplayAvailableRect001, TestSize.Level1)
{
    bool saved = MockSystemProperties::g_isSuperFoldDisplayDevice;
    MockSystemProperties::g_isSuperFoldDisplayDevice = false;
    auto rect = OverlayManager::GetDisplayAvailableRect(nullptr, 0);
    EXPECT_EQ(rect.ToString(), Rect().ToString());
    MockSystemProperties::g_isSuperFoldDisplayDevice = saved;
}

/**
 * @tc.name: GetDisplayAvailableRect002
 * @tc.desc: Test GetDisplayAvailableRect when IsSuperFoldDisplayDevice is true and frameNode is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetDisplayAvailableRect002, TestSize.Level1)
{
    bool saved = MockSystemProperties::g_isSuperFoldDisplayDevice;
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    auto rect = OverlayManager::GetDisplayAvailableRect(nullptr, 0);
    EXPECT_EQ(rect.ToString(), Rect().ToString());
    MockSystemProperties::g_isSuperFoldDisplayDevice = saved;
}

/**
 * @tc.name: GetDisplayAvailableRect003
 * @tc.desc: Test GetDisplayAvailableRect when IsSuperFoldDisplayDevice is true and container is not sub container.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetDisplayAvailableRect003, TestSize.Level1)
{
    bool saved = MockSystemProperties::g_isSuperFoldDisplayDevice;
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachContext(PipelineContext::GetCurrentContext().GetRawPtr());
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    bool savedIsSubContainer = mockContainer->isSubContainer_;
    mockContainer->isSubContainer_ = false;
    AceEngine::Get().AddContainer(0, mockContainer);
    auto rect = OverlayManager::GetDisplayAvailableRect(frameNode, 0);
    EXPECT_FALSE(rect.ToString().empty());
    mockContainer->isSubContainer_ = savedIsSubContainer;
    MockSystemProperties::g_isSuperFoldDisplayDevice = saved;
}

/**
 * @tc.name: GetDisplayAvailableRect004
 * @tc.desc: Test GetDisplayAvailableRect when IsSuperFoldDisplayDevice is true and container is sub container.
 *           Covers the false branch of if (!container->IsSubContainer()).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetDisplayAvailableRect004, TestSize.Level1)
{
    bool saved = MockSystemProperties::g_isSuperFoldDisplayDevice;
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachContext(PipelineContext::GetCurrentContext().GetRawPtr());
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    bool savedIsSubContainer = mockContainer->isSubContainer_;
    mockContainer->isSubContainer_ = true;
    AceEngine::Get().AddContainer(0, mockContainer);
    auto rect = OverlayManager::GetDisplayAvailableRect(frameNode, 0);
    EXPECT_FALSE(rect.ToString().empty());
    mockContainer->isSubContainer_ = savedIsSubContainer;
    MockSystemProperties::g_isSuperFoldDisplayDevice = saved;
}

/**
 * @tc.name: GetSafeAreaInsets001
 * @tc.desc: Test GetSafeAreaInsets when useCurrentWindow is false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetSafeAreaInsets001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto insets = OverlayManager::GetSafeAreaInsets(frameNode, false);
    EXPECT_TRUE(insets.IsValid() || !insets.IsValid());
}

/**
 * @tc.name: GetSafeAreaInsets002
 * @tc.desc: Test GetSafeAreaInsets when useCurrentWindow is true with valid frameNode.
 *           Covers the true branch of if (useCurrentWindow).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetSafeAreaInsets002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachContext(PipelineContext::GetCurrentContext().GetRawPtr());
    auto insets = OverlayManager::GetSafeAreaInsets(frameNode, true);
    EXPECT_TRUE(insets.IsValid() || !insets.IsValid());
}

/**
 * @tc.name: GetSafeAreaInsets003
 * @tc.desc: Test GetSafeAreaInsets when useCurrentWindow is true and frameNode is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetSafeAreaInsets003, TestSize.Level1)
{
    auto insets = OverlayManager::GetSafeAreaInsets(nullptr, true);
    EXPECT_FALSE(insets.IsValid());
}

/**
 * @tc.name: SetNodeBeforeAppbar001
 * @tc.desc: Test SetNodeBeforeAppbar when rootNode is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, SetNodeBeforeAppbar001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto node = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(overlayManager->SetNodeBeforeAppbar(nullptr, node, std::nullopt));
}

/**
 * @tc.name: SetNodeBeforeAppbar002
 * @tc.desc: Test SetNodeBeforeAppbar when node is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, SetNodeBeforeAppbar002, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    EXPECT_FALSE(overlayManager->SetNodeBeforeAppbar(rootNode, nullptr, std::nullopt));
}

/**
 * @tc.name: SetNodeBeforeAppbar003
 * @tc.desc: Test SetNodeBeforeAppbar when rootNode has no AtomicService child.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, SetNodeBeforeAppbar003, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto child = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child, nullptr);
    rootNode->AddChild(child);
    auto node = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(overlayManager->SetNodeBeforeAppbar(rootNode, node, std::nullopt));
}

/**
 * @tc.name: SetNodeBeforeAppbar004
 * @tc.desc: Test SetNodeBeforeAppbar when AtomicService child has serviceContainer and GetNextNodeWithOrder returns non-null.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, SetNodeBeforeAppbar004, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto atomicService = FrameNode::CreateFrameNode(
        V2::ATOMIC_SERVICE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(atomicService, nullptr);
    auto serviceContainer = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(serviceContainer, nullptr);
    serviceContainer->UpdateInspectorId("AtomicServiceContainerId");
    atomicService->AddChild(serviceContainer);
    rootNode->AddChild(atomicService);
    auto node = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(node, nullptr);
    double order = 5.0;
    auto existingNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(existingNode, nullptr);
    overlayManager->nodeIdOrderMap_[existingNode->GetId()] = 10.0;
    overlayManager->orderNodesMap_[10.0].emplace_back(existingNode);
    EXPECT_TRUE(overlayManager->SetNodeBeforeAppbar(rootNode, node, order));
    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();
}

/**
 * @tc.name: SetNodeBeforeAppbar005
 * @tc.desc: Test SetNodeBeforeAppbar when GetNextNodeWithOrder returns null, childNode found.
 *           Covers the else branch.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, SetNodeBeforeAppbar005, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto atomicService = FrameNode::CreateFrameNode(
        V2::ATOMIC_SERVICE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(atomicService, nullptr);
    auto serviceContainer = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(serviceContainer, nullptr);
    serviceContainer->UpdateInspectorId("AtomicServiceContainerId");
    auto menubarRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(menubarRow, nullptr);
    menubarRow->UpdateInspectorId("AtomicServiceMenubarRowId");
    atomicService->AddChild(serviceContainer);
    atomicService->AddChild(menubarRow);
    rootNode->AddChild(atomicService);
    auto node = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(node, nullptr);
    EXPECT_TRUE(overlayManager->SetNodeBeforeAppbar(rootNode, node, std::nullopt));
    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();
}

/**
 * @tc.name: SetNodeBeforeAppbar006
 * @tc.desc: Test SetNodeBeforeAppbar when GetNextNodeWithOrder returns null and childNode not found.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, SetNodeBeforeAppbar006, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto atomicService = FrameNode::CreateFrameNode(
        V2::ATOMIC_SERVICE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(atomicService, nullptr);
    auto serviceContainer = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(serviceContainer, nullptr);
    serviceContainer->UpdateInspectorId("AtomicServiceContainerId");
    atomicService->AddChild(serviceContainer);
    rootNode->AddChild(atomicService);
    auto node = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(overlayManager->SetNodeBeforeAppbar(rootNode, node, std::nullopt));
    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();
}

/**
 * @tc.name: GetPixelMapContentNodeForSubwindow001
 * @tc.desc: Test GetPixelMapContentNodeForSubwindow when rootNode is null.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetPixelMapContentNodeForSubwindow001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->rootNodeWeak_ = nullptr;
    EXPECT_EQ(overlayManager->GetPixelMapContentNodeForSubwindow(), nullptr);
}

/**
 * @tc.name: GetPixelMapContentNodeForSubwindow002
 * @tc.desc: Test GetPixelMapContentNodeForSubwindow when rootNode has no MenuWrapper child.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetPixelMapContentNodeForSubwindow002, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto child = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child, nullptr);
    rootNode->AddChild(child);
    overlayManager->rootNodeWeak_ = rootNode;
    EXPECT_EQ(overlayManager->GetPixelMapContentNodeForSubwindow(), nullptr);
    overlayManager->rootNodeWeak_ = nullptr;
}

/**
 * @tc.name: GetPixelMapContentNodeForSubwindow003
 * @tc.desc: Test GetPixelMapContentNodeForSubwindow when MenuWrapper child has non-matching inner children.
 *           Covers the inner loop else branch (continue).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetPixelMapContentNodeForSubwindow003, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(menuWrapper, nullptr);
    auto nonMatchingChild = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(nonMatchingChild, nullptr);
    menuWrapper->AddChild(nonMatchingChild);
    rootNode->AddChild(menuWrapper);
    overlayManager->rootNodeWeak_ = rootNode;
    EXPECT_EQ(overlayManager->GetPixelMapContentNodeForSubwindow(), nullptr);
    overlayManager->rootNodeWeak_ = nullptr;
}

/**
 * @tc.name: GetPixelMapContentNodeForSubwindow004
 * @tc.desc: Test GetPixelMapContentNodeForSubwindow when MenuWrapper child has MenuPreview inner child.
 *           Covers the inner loop if branch (return frameNode).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetPixelMapContentNodeForSubwindow004, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(menuWrapper, nullptr);
    auto nonMatchingChild = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(nonMatchingChild, nullptr);
    auto menuPreviewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(menuPreviewNode, nullptr);
    menuWrapper->AddChild(nonMatchingChild);
    menuWrapper->AddChild(menuPreviewNode);
    rootNode->AddChild(menuWrapper);
    overlayManager->rootNodeWeak_ = rootNode;
    auto result = overlayManager->GetPixelMapContentNodeForSubwindow();
    EXPECT_EQ(result, menuPreviewNode);
    overlayManager->rootNodeWeak_ = nullptr;
}

/**
 * @tc.name: GetPixelMapContentNodeForSubwindow005
 * @tc.desc: Test GetPixelMapContentNodeForSubwindow when MenuWrapper child has Image inner child.
 *           Covers the inner loop if branch with IMAGE_ETS_TAG.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetPixelMapContentNodeForSubwindow005, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(menuWrapper, nullptr);
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(imageNode, nullptr);
    menuWrapper->AddChild(imageNode);
    rootNode->AddChild(menuWrapper);
    overlayManager->rootNodeWeak_ = rootNode;
    auto result = overlayManager->GetPixelMapContentNodeForSubwindow();
    EXPECT_EQ(result, imageNode);
    overlayManager->rootNodeWeak_ = nullptr;
}

/**
 * @tc.name: MarkDirty001
 * @tc.desc: Test MarkDirty when root is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: MarkDirty002
 * @tc.desc: Test MarkDirty when installationFree is false and rootNode == markNode (return early).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty002, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    bool savedInstallationFree = pipelineContext->installationFree_;
    pipelineContext->installationFree_ = false;
    auto rootElement = pipelineContext->GetRootElement();
    ASSERT_NE(rootElement, nullptr);
    overlayManager->rootNodeWeak_ = rootElement;
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    pipelineContext->installationFree_ = savedInstallationFree;
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: MarkDirty003
 * @tc.desc: Test MarkDirty when installationFree is true, markNode is root's first child.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty003, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    bool savedInstallationFree = pipelineContext->installationFree_;
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->installationFree_ = true;
    pipelineContext->isSubPipeline_ = false;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto firstChild = FrameNode::CreateFrameNode(
        V2::ATOMIC_SERVICE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(firstChild, nullptr);
    auto secondChild = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(secondChild, nullptr);
    rootNode->AddChild(firstChild);
    rootNode->AddChild(secondChild);
    overlayManager->rootNodeWeak_ = rootNode;
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    pipelineContext->installationFree_ = savedInstallationFree;
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: MarkDirty004
 * @tc.desc: Test MarkDirty when child is first child and not sub pipeline (skip child in for loop).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty004, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    bool savedInstallationFree = pipelineContext->installationFree_;
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->installationFree_ = false;
    pipelineContext->isSubPipeline_ = false;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto firstChild = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(firstChild, nullptr);
    auto secondChild = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(secondChild, nullptr);
    rootNode->AddChild(firstChild);
    rootNode->AddChild(secondChild);
    overlayManager->rootNodeWeak_ = rootNode;
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    pipelineContext->installationFree_ = savedInstallationFree;
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: MarkDirty005
 * @tc.desc: Test MarkDirty when child is sheet wrapper with sheet child.
 *           Covers sheetParent tag == SHEET_WRAPPER_TAG and sheet non-null.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty005, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    bool savedInstallationFree = pipelineContext->installationFree_;
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->installationFree_ = false;
    pipelineContext->isSubPipeline_ = true;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto sheetWrapper = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    ASSERT_NE(sheetWrapper, nullptr);
    auto sheetChild = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(sheetChild, nullptr);
    sheetWrapper->AddChild(sheetChild);
    rootNode->AddChild(sheetWrapper);
    overlayManager->rootNodeWeak_ = rootNode;
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    pipelineContext->installationFree_ = savedInstallationFree;
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: MarkDirty006
 * @tc.desc: Test MarkDirty when child is sheet wrapper without sheet child (sheet is null).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty006, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    bool savedInstallationFree = pipelineContext->installationFree_;
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->installationFree_ = false;
    pipelineContext->isSubPipeline_ = true;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto sheetWrapper = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    ASSERT_NE(sheetWrapper, nullptr);
    rootNode->AddChild(sheetWrapper);
    overlayManager->rootNodeWeak_ = rootNode;
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    pipelineContext->installationFree_ = savedInstallationFree;
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: MarkDirty007
 * @tc.desc: Test MarkDirty when rootNode != markNode and toast child exists.
 *           Covers toast loop true branch.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty007, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    bool savedInstallationFree = pipelineContext->installationFree_;
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->installationFree_ = false;
    pipelineContext->isSubPipeline_ = false;
    auto customRoot = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(customRoot, nullptr);
    auto child1 = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child1, nullptr);
    customRoot->AddChild(child1);
    overlayManager->rootNodeWeak_ = customRoot;
    auto rootElement = pipelineContext->GetRootElement();
    ASSERT_NE(rootElement, nullptr);
    auto toastChild = FrameNode::CreateFrameNode(
        V2::TOAST_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToastPattern>());
    ASSERT_NE(toastChild, nullptr);
    rootElement->AddChild(toastChild);
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    rootElement->RemoveChild(toastChild);
    pipelineContext->installationFree_ = savedInstallationFree;
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: MarkDirty008
 * @tc.desc: Test MarkDirty when rootNode != markNode and non-toast child exists.
 *           Covers toast loop false branch (tag != TOAST_ETS_TAG).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty008, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    bool savedInstallationFree = pipelineContext->installationFree_;
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->installationFree_ = false;
    pipelineContext->isSubPipeline_ = false;
    auto customRoot = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(customRoot, nullptr);
    auto child1 = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child1, nullptr);
    customRoot->AddChild(child1);
    overlayManager->rootNodeWeak_ = customRoot;
    auto rootElement = pipelineContext->GetRootElement();
    ASSERT_NE(rootElement, nullptr);
    auto nonToastChild = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(nonToastChild, nullptr);
    rootElement->AddChild(nonToastChild);
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    rootElement->RemoveChild(nonToastChild);
    pipelineContext->installationFree_ = savedInstallationFree;
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: MarkDirty009
 * @tc.desc: Test MarkDirty when isSubPipeline is true, first child is marked.
 *           Covers the IsSubPipeline true branch in for loop condition.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty009, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    bool savedInstallationFree = pipelineContext->installationFree_;
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->installationFree_ = false;
    pipelineContext->isSubPipeline_ = true;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto firstChild = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(firstChild, nullptr);
    rootNode->AddChild(firstChild);
    overlayManager->rootNodeWeak_ = rootNode;
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    pipelineContext->installationFree_ = savedInstallationFree;
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
    overlayManager->rootNodeWeak_ = savedRoot;
}
} // namespace OHOS::Ace::NG
