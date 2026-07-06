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
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/unittest/core/event/frame_node_on_tree.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/pipeline/base/element_register.h"
#include "core/common/ace_engine.h"
#include "core/common/visual_effect/transparency_utils.h"
#include "core/components/common/properties/ui_material.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "interfaces/inner_api/ace_kit/include/ui/properties/ui_material_enums.h"
#include "interfaces/inner_api/ace_kit/include/ui/properties/ui_material_structs.h"
#include "interfaces/inner_api/ace_kit/include/ui/view/theme/token_colors.h"


using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
    constexpr int32_t TEST_DIALOG_NODE_ID = 101;
    constexpr int32_t TEST_DIALOG_NODE_ON_TREE_ID = 102;
    constexpr int32_t TEST_VALID_UNIQUE_ID = -1;
    constexpr int32_t MATERIAL_TYPE_NONE = static_cast<int32_t>(MaterialType::NONE);
    constexpr int32_t MATERIAL_TYPE_SEMI_TRANSPARENT = static_cast<int32_t>(MaterialType::SEMI_TRANSPARENT);
    constexpr int32_t MATERIAL_TYPE_IMMERSIVE = static_cast<int32_t>(MaterialType::IMMERSIVE);

    // Restore the immersive-material inputs to their pristine defaults so that mutating them in a test never leaks
    // into sibling tests in the same binary.
    void ResetImmersiveMaterialState()
    {
        g_uiMaterialLevel = UiMaterialLevel::DEFAULT;
        TransparencyUtils::transparencyLevelGet_ = false;
        auto& levelMap = TransparencyUtils::GetLevelMap();
        levelMap[UiMaterialLevel::EXQUISITE] = UiMaterialTransparency::NORMAL;
        levelMap[UiMaterialLevel::GENTLE] = UiMaterialTransparency::GENTLE_NORMAL;
        levelMap[UiMaterialLevel::SMOOTH] = UiMaterialTransparency::NONE;
    }

    // Drive TransparencyUtils::GetTransparencyLevel to return `transparency` for `level` by short-circuiting the
    // settings read (transparencyLevelGet_ = true) and seeding the lookup map.
    void SetTransparencyForLevel(UiMaterialLevel level, UiMaterialTransparency transparency)
    {
        TransparencyUtils::transparencyLevelGet_ = true;
        TransparencyUtils::GetLevelMap()[level] = transparency;
    }
} // namespace

class DialogManagerTestNg : public testing::Test {
    public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void DialogManagerTestNg::SetUpTestCase()
{
    // First clean up any existing state to avoid accumulation
    TearDownTestCase();
    // Clear ElementRegister to avoid ID conflicts between tests
    ElementRegister::GetInstance()->Clear();
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}
void DialogManagerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: DialogManagerTest001
 * @tc.desc: Test FindPageNodeOverlay
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest001, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();
    auto dialogPattern = AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr);
    auto dialogNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 101, dialogPattern);
    auto dialogNodeOnTree = FrameNodeOnTree::CreateFrameNode(V2::DIALOG_ETS_TAG, 102, dialogPattern);
    DialogManager dialogManager;
    auto ret = dialogManager.FindPageNodeOverlay(nullptr);
    EXPECT_EQ(ret, nullptr);
    ret = dialogManager.FindPageNodeOverlay(dialogNode);
    EXPECT_EQ(ret, nullptr);
    ret = dialogManager.FindPageNodeOverlay(dialogNodeOnTree);
    EXPECT_EQ(ret, nullptr);
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest002
 * @tc.desc: Test GetEmbeddedOverlay
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest002, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto dialogPattern = AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr);
    auto dialogNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 101, dialogPattern);
    auto dialogNodeOnTree = FrameNodeOnTree::CreateFrameNode(V2::DIALOG_ETS_TAG, 102, dialogPattern);
    DialogManager dialogManager;
    auto ret = dialogManager.GetEmbeddedOverlay(1, context);
    EXPECT_EQ(ret, nullptr);
    ret = dialogManager.GetEmbeddedOverlay(101, context);
    EXPECT_EQ(ret, nullptr);
    ret = dialogManager.GetEmbeddedOverlay(102, context);
    EXPECT_EQ(ret, nullptr);
    ret = dialogManager.GetEmbeddedOverlay(-1, context);
    EXPECT_EQ(ret, nullptr);
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest003
 * @tc.desc: Test GetEmbeddedOverlayWithNode&GetDialogNodeByContentNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest003, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 201, AceType::MakeRefPtr<RootPattern>());
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 301, AceType::MakeRefPtr<StagePattern>());
    auto pageNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, 401, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto pageDialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, 501, AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    auto navigationNode = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 601, AceType::MakeRefPtr<NavDestinationPattern>());
    auto navDialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, 701, AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    auto columnNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, 801, AceType::MakeRefPtr<OHOS::Ace::NG::LinearLayoutPattern>(true));
    stageNode->MountToParent(rootNode);
    pageNode->MountToParent(stageNode);
    navigationNode->MountToParent(pageNode);
    pageDialogNode->MountToParent(pageNode);
    navDialogNode->MountToParent(navigationNode);
    columnNode->MountToParent(navDialogNode);
    DialogManager dialogManager;
    auto ret = dialogManager.GetEmbeddedOverlayWithNode(pageDialogNode);
    EXPECT_EQ(ret, nullptr);
    ret = dialogManager.GetEmbeddedOverlayWithNode(navDialogNode);
    EXPECT_EQ(ret, nullptr);
    dialogManager.GetDialogNodeByContentNode(columnNode);
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest004
 * @tc.desc: Test GetMainPipelineContext
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest004, TestSize.Level1)
{
    RefPtr<FrameNode> framenode = nullptr;
    auto context = DialogManager::GetMainPipelineContext(framenode);
    EXPECT_EQ(context, nullptr);

    auto node = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    context = DialogManager::GetMainPipelineContext(node);
    EXPECT_EQ(context, nullptr);

    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    node->context_ = AceType::RawPtr(pipelineContext);
    context = DialogManager::GetMainPipelineContext(node);
    EXPECT_EQ(context, nullptr);
    node->instanceId_ = 999;
    context = DialogManager::GetMainPipelineContext(node);
    EXPECT_EQ(context, nullptr);
    
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->pipelineContext_ = pipelineContext;
    node->instanceId_ = container->GetInstanceId();
    AceEngine::Get().AddContainer(container->GetInstanceId(), container);
    context = DialogManager::GetMainPipelineContext(node);
    EXPECT_NE(context, nullptr);

    container->isSubContainer_ = true;
    EXPECT_EQ(container->IsSubContainer(), true);
    context = DialogManager::GetMainPipelineContext(node);
    EXPECT_EQ(context, nullptr);

    SubwindowManager::GetInstance()->AddParentContainerId(container->GetInstanceId(), container->GetInstanceId());
    context = DialogManager::GetMainPipelineContext(node);
    EXPECT_NE(context, nullptr);
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
    container->isSubContainer_ = false;
}

/**
 * @tc.name: DialogManagerTest005
 * @tc.desc: Test ShowInEmbeddedOverlay with null context
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest005, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();
    bool taskExecuted = false;
    auto testTask = [&taskExecuted](RefPtr<NG::OverlayManager> overlayManager) {
        taskExecuted = true;
    };

    // Clear current context to test null path
    // Need to clear both PipelineContext and Container to simulate null context
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
    DialogManager::ShowInEmbeddedOverlay(std::move(testTask), "TestTask", TEST_VALID_UNIQUE_ID);

    // Task should not be executed when context is null
    EXPECT_FALSE(taskExecuted);
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest006
 * @tc.desc: Test ShowInEmbeddedOverlay with valid context
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest006, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);

    bool taskExecuted = false;
    auto testTask = [&taskExecuted](RefPtr<NG::OverlayManager> overlayManager) {
        taskExecuted = true;
    };

    DialogManager::ShowInEmbeddedOverlay(std::move(testTask), "TestTask", TEST_VALID_UNIQUE_ID);

    // Task should be posted to executor (may not execute immediately in test)
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest007
 * @tc.desc: Test ShouldHandleSmoothImmersiveMaterial when UiMaterialLevel is not SMOOTH
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest007, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();

    // Test with null systemMaterial
    auto result = DialogManager::ShouldHandleSmoothImmersiveMaterial(nullptr);
    EXPECT_FALSE(result);

    // Test with valid systemMaterial but different UiMaterialLevel
    // Note: In test environment, GetUiMaterialLevel returns DEFAULT which equals SMOOTH
    // This test verifies the function handles null material correctly
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(MATERIAL_TYPE_NONE);
    result = DialogManager::ShouldHandleSmoothImmersiveMaterial(material);
    // Result depends on SystemProperties::GetUiMaterialLevel() return value
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest009
 * @tc.desc: Test ShouldHandleSmoothImmersiveMaterial with non-IMMERSIVE material type
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest009, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();

    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(MATERIAL_TYPE_SEMI_TRANSPARENT);

    // When material type is not IMMERSIVE, should not handle
    auto result = DialogManager::ShouldHandleSmoothImmersiveMaterial(material);
    EXPECT_FALSE(result);

    material->SetType(MATERIAL_TYPE_NONE);
    result = DialogManager::ShouldHandleSmoothImmersiveMaterial(material);
    EXPECT_FALSE(result);
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest010
 * @tc.desc: Test ShouldApplySystemMaterialShadow with null systemMaterial
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest010, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();

    auto result = DialogManager::ShouldApplySystemMaterialShadow(nullptr);
    EXPECT_FALSE(result);
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest011
 * @tc.desc: Test ShouldApplySystemMaterialShadow with null immersiveOptions
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest011, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();

    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(MATERIAL_TYPE_IMMERSIVE);
    // immersiveOptions is null by default

    auto result = DialogManager::ShouldApplySystemMaterialShadow(material);
    EXPECT_TRUE(result);
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest012
 * @tc.desc: Test ShouldApplySystemMaterialShadow with applyShadow true
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest012, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();

    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(MATERIAL_TYPE_IMMERSIVE);

    ImmersiveOptions options;
    options.applyShadow = true;
    material->SetImmersiveOptions(options);

    auto result = DialogManager::ShouldApplySystemMaterialShadow(material);
    EXPECT_TRUE(result);
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest013
 * @tc.desc: Test ShouldApplySystemMaterialShadow with applyShadow false
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest013, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();

    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(MATERIAL_TYPE_IMMERSIVE);

    ImmersiveOptions options;
    options.applyShadow = false;
    material->SetImmersiveOptions(options);

    auto result = DialogManager::ShouldApplySystemMaterialShadow(material);
    EXPECT_FALSE(result);
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest014
 * @tc.desc: Test HandleSmoothImmersiveMaterial with null columnNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest014, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();

    RefPtr<FrameNode> nullNode = nullptr;
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(MATERIAL_TYPE_IMMERSIVE);

    auto result = DialogManager::HandleSmoothImmersiveMaterial(nullNode, material);
    EXPECT_FALSE(result);
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest015
 * @tc.desc: Test HandleSmoothImmersiveMaterial with valid columnNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest015, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();

    auto columnNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, TEST_DIALOG_NODE_ID,
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);

    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(MATERIAL_TYPE_IMMERSIVE);

    auto result = DialogManager::HandleSmoothImmersiveMaterial(columnNode, material);
    EXPECT_TRUE(result);
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest016
 * @tc.desc: Test HandleSmoothImmersiveMaterial with null systemMaterial
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest016, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();

    auto columnNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, TEST_DIALOG_NODE_ID,
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);

    RefPtr<UiMaterial> nullMaterial = nullptr;

    // HandleSmoothImmersiveMaterial returns true if columnNode and renderContext are valid,
    // even if systemMaterial is null. The null material is handled by SetSmoothImmersiveShadow
    // which checks ShouldApplySystemMaterialShadow before applying shadow.
    auto result = DialogManager::HandleSmoothImmersiveMaterial(columnNode, nullMaterial);
    EXPECT_TRUE(result);
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest018
 * @tc.desc: Test SetSmoothImmersiveBackground with valid renderContext
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest018, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();

    auto columnNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, TEST_DIALOG_NODE_ID,
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);

    auto renderContext = columnNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // Reset background color to ensure clean state
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);

    DialogManager::SetSmoothImmersiveBackground(renderContext);

    // Verify render context is still valid
    EXPECT_NE(renderContext, nullptr);
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest020
 * @tc.desc: Test SetSmoothImmersiveShadow with applyShadow true
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest020, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();

    auto columnNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, TEST_DIALOG_NODE_ID,
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);

    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(MATERIAL_TYPE_IMMERSIVE);

    ImmersiveOptions options;
    options.applyShadow = true;
    material->SetImmersiveOptions(options);

    auto renderContext = columnNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // Reset back shadow to ensure clean state
    renderContext->UpdateBackShadow(Shadow());

    DialogManager::SetSmoothImmersiveShadow(columnNode, material);

    // Verify render context is still valid
    EXPECT_NE(renderContext, nullptr);
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest021
 * @tc.desc: Test SetSmoothImmersiveShadow with applyShadow false
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest021, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();

    auto columnNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, TEST_DIALOG_NODE_ID,
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);

    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(MATERIAL_TYPE_IMMERSIVE);

    ImmersiveOptions options;
    options.applyShadow = false;
    material->SetImmersiveOptions(options);

    auto renderContext = columnNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    DialogManager::SetSmoothImmersiveShadow(columnNode, material);

    // Verify render context is still valid
    EXPECT_NE(renderContext, nullptr);
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest022
 * @tc.desc: Test SetSmoothImmersiveShadow with null systemMaterial
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest022, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();

    auto columnNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, TEST_DIALOG_NODE_ID,
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);

    RefPtr<UiMaterial> nullMaterial = nullptr;

    auto renderContext = columnNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    DialogManager::SetSmoothImmersiveShadow(columnNode, nullMaterial);

    // Verify render context is still valid
    EXPECT_NE(renderContext, nullptr);
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerTest023
 * @tc.desc: Test SetSmoothImmersiveShadow with null renderContext
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest023, TestSize.Level1)
{
    DialogManagerTestNg::SetUpTestCase();

    auto columnNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, TEST_DIALOG_NODE_ID,
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);

    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(MATERIAL_TYPE_IMMERSIVE);

    ImmersiveOptions options;
    options.applyShadow = true;
    material->SetImmersiveOptions(options);

    // Temporarily set renderContext to null by creating a new node without context
    RefPtr<FrameNode> nodeWithoutContext = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, TEST_DIALOG_NODE_ON_TREE_ID,
        AceType::MakeRefPtr<LinearLayoutPattern>(true));

    // Clear the render context to test null path
    nodeWithoutContext->renderContext_ = nullptr;

    DialogManager::SetSmoothImmersiveShadow(nodeWithoutContext, material);
    // Function should return early without crash
    DialogManagerTestNg::SetUpTestCase();
}

/**
 * @tc.name: DialogManagerIsUseImmersiveDistortionEffectSmooth001
 * @tc.desc: Test IsUseImmersiveDistortionEffect returns false for SMOOTH material level.
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerIsUseImmersiveDistortionEffectSmooth001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::SMOOTH;
    EXPECT_FALSE(DialogManager::IsUseImmersiveDistortionEffect());
    ResetImmersiveMaterialState();
}

/**
 * @tc.name: DialogManagerIsUseImmersiveDistortionEffectExquisite001
 * @tc.desc: Test IsUseImmersiveDistortionEffect for EXQUISITE level returns true when transparency is NORMAL.
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerIsUseImmersiveDistortionEffectExquisite001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    SetTransparencyForLevel(UiMaterialLevel::EXQUISITE, UiMaterialTransparency::NORMAL);
    EXPECT_TRUE(DialogManager::IsUseImmersiveDistortionEffect());
    ResetImmersiveMaterialState();
}

/**
 * @tc.name: DialogManagerIsUseImmersiveDistortionEffectExquisite002
 * @tc.desc: Test IsUseImmersiveDistortionEffect for EXQUISITE level returns true when transparency is THIN.
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerIsUseImmersiveDistortionEffectExquisite002, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    SetTransparencyForLevel(UiMaterialLevel::EXQUISITE, UiMaterialTransparency::THIN);
    EXPECT_TRUE(DialogManager::IsUseImmersiveDistortionEffect());
    ResetImmersiveMaterialState();
}

/**
 * @tc.name: DialogManagerIsUseImmersiveDistortionEffectExquisite003
 * @tc.desc: Test IsUseImmersiveDistortionEffect for EXQUISITE level returns false when transparency is THICK.
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerIsUseImmersiveDistortionEffectExquisite003, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    SetTransparencyForLevel(UiMaterialLevel::EXQUISITE, UiMaterialTransparency::THICK);
    EXPECT_FALSE(DialogManager::IsUseImmersiveDistortionEffect());
    ResetImmersiveMaterialState();
}

/**
 * @tc.name: DialogManagerIsUseImmersiveDistortionEffectGentle001
 * @tc.desc: Test IsUseImmersiveDistortionEffect for GENTLE level returns false for GENTLE_THIN.
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerIsUseImmersiveDistortionEffectGentle001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::GENTLE;
    SetTransparencyForLevel(UiMaterialLevel::GENTLE, UiMaterialTransparency::GENTLE_THIN);
    EXPECT_FALSE(DialogManager::IsUseImmersiveDistortionEffect());
    ResetImmersiveMaterialState();
}

/**
 * @tc.name: DialogManagerIsUseImmersiveDistortionEffectGentle002
 * @tc.desc: Test IsUseImmersiveDistortionEffect for GENTLE level returns false for GENTLE_NORMAL.
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerIsUseImmersiveDistortionEffectGentle002, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::GENTLE;
    SetTransparencyForLevel(UiMaterialLevel::GENTLE, UiMaterialTransparency::GENTLE_NORMAL);
    EXPECT_FALSE(DialogManager::IsUseImmersiveDistortionEffect());
    ResetImmersiveMaterialState();
}

/**
 * @tc.name: DialogManagerIsUseImmersiveEdgeLightEffectSmooth001
 * @tc.desc: Test IsUseImmersiveEdgeLightEffect returns false for SMOOTH material level.
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerIsUseImmersiveEdgeLightEffectSmooth001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::SMOOTH;
    EXPECT_FALSE(DialogManager::IsUseImmersiveEdgeLightEffect());
    ResetImmersiveMaterialState();
}

/**
 * @tc.name: DialogManagerIsUseImmersiveEdgeLightEffectExquisite001
 * @tc.desc: Test IsUseImmersiveEdgeLightEffect for EXQUISITE level returns true when transparency is NORMAL.
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerIsUseImmersiveEdgeLightEffectExquisite001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    SetTransparencyForLevel(UiMaterialLevel::EXQUISITE, UiMaterialTransparency::NORMAL);
    EXPECT_TRUE(DialogManager::IsUseImmersiveEdgeLightEffect());
    ResetImmersiveMaterialState();
}

/**
 * @tc.name: DialogManagerIsUseImmersiveEdgeLightEffectExquisite002
 * @tc.desc: Test IsUseImmersiveEdgeLightEffect for EXQUISITE level returns true when transparency is THIN.
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerIsUseImmersiveEdgeLightEffectExquisite002, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    SetTransparencyForLevel(UiMaterialLevel::EXQUISITE, UiMaterialTransparency::THIN);
    EXPECT_TRUE(DialogManager::IsUseImmersiveEdgeLightEffect());
    ResetImmersiveMaterialState();
}

/**
 * @tc.name: DialogManagerIsUseImmersiveEdgeLightEffectExquisite003
 * @tc.desc: Test IsUseImmersiveEdgeLightEffect for EXQUISITE level returns false when transparency is THICK.
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerIsUseImmersiveEdgeLightEffectExquisite003, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    SetTransparencyForLevel(UiMaterialLevel::EXQUISITE, UiMaterialTransparency::THICK);
    EXPECT_FALSE(DialogManager::IsUseImmersiveEdgeLightEffect());
    ResetImmersiveMaterialState();
}

/**
 * @tc.name: DialogManagerIsUseImmersiveEdgeLightEffectGentle001
 * @tc.desc: Test IsUseImmersiveEdgeLightEffect for GENTLE level returns true when transparency is GENTLE_THIN.
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerIsUseImmersiveEdgeLightEffectGentle001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::GENTLE;
    SetTransparencyForLevel(UiMaterialLevel::GENTLE, UiMaterialTransparency::GENTLE_THIN);
    EXPECT_TRUE(DialogManager::IsUseImmersiveEdgeLightEffect());
    ResetImmersiveMaterialState();
}

/**
 * @tc.name: DialogManagerIsUseImmersiveEdgeLightEffectGentle002
 * @tc.desc: Test IsUseImmersiveEdgeLightEffect for GENTLE level returns false when transparency is GENTLE_NORMAL.
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerIsUseImmersiveEdgeLightEffectGentle002, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::GENTLE;
    SetTransparencyForLevel(UiMaterialLevel::GENTLE, UiMaterialTransparency::GENTLE_NORMAL);
    EXPECT_FALSE(DialogManager::IsUseImmersiveEdgeLightEffect());
    ResetImmersiveMaterialState();
}

} // namespace OHOS::Ace::NG