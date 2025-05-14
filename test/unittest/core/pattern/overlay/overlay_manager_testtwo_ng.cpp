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

#include "test/mock/base/mock_subwindow.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_rosen_render_context.h"
#include "test/unittest/core/event/frame_node_on_tree.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/common/frontend.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const NG::BorderColorProperty BORDER_COLOR_TEST = { Color::BLUE, Color::BLUE, Color::BLUE, Color::BLUE };
const NG::BorderColorProperty NEW_BORDER_COLOR_TEST = { Color::RED, Color::GREEN, Color::GRAY, Color::BLACK };
const std::string TEXT_TAG = "text";
const OffsetF MENU_OFFSET(10.0, 10.0);
const std::string MESSAGE = "hello world";
const std::string BOTTOMSTRING = "test";
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
} // namespace

class OverlayManagerTwoTestNg : public TestNG {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    std::function<RefPtr<UINode>()> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;

protected:
    static RefPtr<FrameNode> CreateBubbleNode(const TestProperty& testProperty);
    static RefPtr<FrameNode> CreateTargetNode();
    static void CreateSheetStyle(SheetStyle& sheetStyle);
    void CreateSheetBuilder();
    int32_t minPlatformVersion_ = 0;
};

void OverlayManagerTwoTestNg::SetUp()
{
    minPlatformVersion_ = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
}

void OverlayManagerTwoTestNg::TearDown()
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion_);
}

void OverlayManagerTwoTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockPipelineContext::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_ELEVEN);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == DragBarTheme::TypeId()) {
            return AceType::MakeRefPtr<DragBarTheme>();
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else if (type == PickerTheme::TypeId()) {
            return AceType::MakeRefPtr<PickerTheme>();
        } else if (type == SelectTheme::TypeId()) {
            return AceType::MakeRefPtr<SelectTheme>();
        } else if (type == MenuTheme::TypeId()) {
            return AceType::MakeRefPtr<MenuTheme>();
        } else if (type == ToastTheme::TypeId()) {
            return AceType::MakeRefPtr<ToastTheme>();
        } else if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}
void OverlayManagerTwoTestNg::TearDownTestSuite()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> OverlayManagerTwoTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

void OverlayManagerTwoTestNg::CreateSheetStyle(SheetStyle& sheetStyle)
{
    if (!sheetStyle.sheetHeight.sheetMode.has_value()) {
        sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    }
    if (!sheetStyle.showDragBar.has_value()) {
        sheetStyle.showDragBar = true;
    }
}

void OverlayManagerTwoTestNg::CreateSheetBuilder()
{
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    builderFunc_ = builderFunc;
    titleBuilderFunc_ = buildTitleNodeFunc;
}

/**
 * @tc.name: OverlayManagerTwoTestNg_UpdateContextMenuDisappearPosition
 * @tc.desc: Test SheetView::CreateTitleColumn.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, UpdateContextMenuDisappearPosition, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    const OffsetF menu_zero_offset(0.0, 0.0);
    const OffsetF deformMenuOffset(5.0, 5.0);
    const OffsetF deformOneMenuOffset(10.0, 10.0);
    const OffsetF deformSecondMenuOffset(20.0, 20.0);
    const OffsetF deformThreeMenuOffset(30.0, 30.0);
    float menuScale = 0.0f;
    bool isRedragStart = true;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode_, nullptr);
    EXPECT_NE(overlayManager, nullptr);
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNodeFst =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    overlayManager->menuMap_.emplace(1, AceType::RawPtr(menuNodeFst));
    overlayManager->UpdateContextMenuDisappearPosition(menu_zero_offset, menuScale, isRedragStart);
    isRedragStart = false;
    overlayManager->UpdateContextMenuDisappearPosition(deformMenuOffset, menuScale, isRedragStart);
    overlayManager->UpdateContextMenuDisappearPosition(deformOneMenuOffset, menuScale, isRedragStart);
    overlayManager->UpdateContextMenuDisappearPosition(deformSecondMenuOffset, menuScale, isRedragStart);
    menuNodeFst->MountToParent(menuNode);
    menuNode->MountToParent(rootNode_);
    rootNode_->MarkDirtyNode();
    overlayManager->UpdateContextMenuDisappearPosition(deformThreeMenuOffset, menuScale, isRedragStart);
    rootNode_->children_.pop_back();
    EXPECT_EQ(overlayManager->dragMoveVector_.GetX(), .0f);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_GetMenuPreviewCenter
 * @tc.desc: Test SheetView::CreateTitleColumn.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, GetMenuPreviewCenter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode_, nullptr);
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
    OffsetF menu_zero_offset(0.0, 0.0);
    OffsetF deformMenuOffset(5.0, 5.0);
    overlayManager->GetMenuPreviewCenter(menu_zero_offset);
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    menuNode->MountToParent(rootNode_);
    rootNode_->MarkDirtyNode();
    EXPECT_EQ(rootNode_->GetChildren().size(), 2);
    overlayManager->GetMenuPreviewCenter(deformMenuOffset);
    rootNode_->children_.back() = nullptr;
    overlayManager->GetMenuPreviewCenter(deformMenuOffset);
    rootNode_->children_.pop_back();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_ContextMenuSwitchDragPreviewAnimation
 * @tc.desc: Test SheetView::CreateTitleColumn.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, ContextMenuSwitchDragPreviewAnimation, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    EXPECT_EQ(MockPipelineContext::pipeline_, pipelineContext);
    auto overlayManager = pipelineContext->overlayManager_;
    EXPECT_NE(overlayManager, nullptr);
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode_, nullptr);
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
    const OffsetF deformMenuOffset(5.0, 5.0);
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuPreNode =
        FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG, 3, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    menuNode->MountToParent(rootNode_);
    rootNode_->MarkDirtyNode();
    EXPECT_EQ(rootNode_->GetChildren().size(), 2);
    rootNode_->children_.back() = nullptr;
    overlayManager->ContextMenuSwitchDragPreviewAnimation(menuPreNode, deformMenuOffset);
    rootNode_->children_.pop_back();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
}

/**
 * @tc.name: RemoveFilter001
 * @tc.desc: Test RemoveFilter
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, RemoveFilter001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    EXPECT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    EXPECT_NE(overlayManager, nullptr);
    overlayManager->SetHasFilter(true);
    overlayManager->RemoveFilter();

    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_NE(columnNode, nullptr);
    columnNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();

    overlayManager->SetHasFilter(true);
    overlayManager->SetFilterColumnNode(columnNode);
    overlayManager->RemoveFilter();

    EXPECT_FALSE(overlayManager->GetHasFilter());
}

/**
 * @tc.name: RemoveEventColumn001
 * @tc.desc: Test RemoveEventColumn
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, RemoveEventColumn001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->SetHasEvent(true);
    overlayManager->RemoveEventColumn();

    overlayManager->eventColumnNodeWeak_ = rootNode;
    overlayManager->RemoveEventColumn();

    overlayManager->eventColumnNodeWeak_ = targetNode;
    overlayManager->RemoveEventColumn();

    EXPECT_FALSE(overlayManager->hasEvent_);
}

/**
 * @tc.name: ResetRootNode001
 * @tc.desc: Test ResetRootNode
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, ResetRootNode001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ResetRootNode(2);
    overlayManager->curSessionIds_.insert(2);
    overlayManager->ResetRootNode(2);

    int32_t modalUiextensionCount = rootNode->modalUiextensionCount_;
    auto pipeline = rootNode->GetContextRefPtr();
    pipeline->SetInstallationFree(true);
    overlayManager->curSessionIds_.insert(2);
    overlayManager->ResetRootNode(2);
    EXPECT_NE(modalUiextensionCount, rootNode->modalUiextensionCount_);
}

/**
 * @tc.name: AddCurSessionId001
 * @tc.desc: Test AddCurSessionId
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, AddCurSessionId001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    EXPECT_TRUE(overlayManager->AddCurSessionId(2));
    EXPECT_FALSE(overlayManager->AddCurSessionId(2));
}

/**
 * @tc.name: HandleUIExtNodeAngle001
 * @tc.desc: Test HandleUIExtNodeAngle
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, HandleUIExtNodeAngle001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    EXPECT_TRUE(overlayManager->HandleUIExtNodeAngle(90, targetNode));
    EXPECT_TRUE(overlayManager->HandleUIExtNodeAngle(180, targetNode));
    EXPECT_TRUE(overlayManager->HandleUIExtNodeAngle(270, targetNode));

    EXPECT_TRUE(overlayManager->HandleUIExtNodeAngle(0, targetNode));
}

/**
 * @tc.name: UIExtNodeAngleValid001
 * @tc.desc: Test UIExtNodeAngleValid
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, UIExtNodeAngleValid001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    EXPECT_FALSE(overlayManager->UIExtNodeAngleValid(0));
    EXPECT_TRUE(overlayManager->UIExtNodeAngleValid(90));
    EXPECT_TRUE(overlayManager->UIExtNodeAngleValid(180));
    EXPECT_TRUE(overlayManager->UIExtNodeAngleValid(270));
}

/**
 * @tc.name: ClearUIExtensionNode001
 * @tc.desc: Test ClearUIExtensionNode
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, ClearUIExtensionNode001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    overlayManager->ClearUIExtensionNode();

    overlayManager->uiExtNodes_.insert({ 2, nullptr });
    overlayManager->ClearUIExtensionNode();

    overlayManager->uiExtNodes_.insert({ 2, rootNode });
    overlayManager->ClearUIExtensionNode();
    EXPECT_TRUE(overlayManager->uiExtNodes_.empty());
}

/**
 * @tc.name: DeleteUIExtensionNode001
 * @tc.desc: Test DeleteUIExtensionNode
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, DeleteUIExtensionNode001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->DeleteUIExtensionNode(2);
    overlayManager->uiExtNodes_.insert({ 2, nullptr });
    overlayManager->DeleteUIExtensionNode(2);
    overlayManager->uiExtNodes_.insert({ 2, rootNode });
    overlayManager->DeleteUIExtensionNode(2);
    EXPECT_TRUE(overlayManager->uiExtNodes_.empty());
}

/**
 * @tc.name: CloseAIEntityMenu001
 * @tc.desc: Test CloseAIEntityMenu
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, CloseAIEntityMenu001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->CloseAIEntityMenu(2);
    EXPECT_FALSE(overlayManager->GetMenuNode(2));
}

/**
 * @tc.name: CheckPageNeedAvoidKeyboard001
 * @tc.desc: Test CheckPageNeedAvoidKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, CheckPageNeedAvoidKeyboard001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    EXPECT_TRUE(overlayManager->CheckPageNeedAvoidKeyboard());
}

/**
 * @tc.name: isMaskNode001
 * @tc.desc: Test isMaskNode
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, isMaskNode001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    EXPECT_FALSE(overlayManager->isMaskNode(2));

    overlayManager->SetMaskNodeId(1, 1);
    overlayManager->SetMaskNodeId(2, 2);
    EXPECT_TRUE(overlayManager->isMaskNode(1));
}

/**
 * @tc.name: GetMaskNodeIdWithDialogId001
 * @tc.desc: Test GetMaskNodeIdWithDialogId
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, GetMaskNodeIdWithDialogId001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    EXPECT_EQ(overlayManager->GetMaskNodeIdWithDialogId(2), -1);

    overlayManager->SetMaskNodeId(1, 1);
    overlayManager->SetMaskNodeId(2, 2);
    EXPECT_EQ(overlayManager->GetMaskNodeIdWithDialogId(2), 2);
}

/**
 * @tc.name: RemoveGatherNodeWithAnimation001
 * @tc.desc: Test RemoveGatherNodeWithAnimation
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, RemoveGatherNodeWithAnimation001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->RemoveGatherNodeWithAnimation();

    overlayManager->hasGatherNode_ = true;
    overlayManager->RemoveGatherNodeWithAnimation();

    overlayManager->hasGatherNode_ = true;
    overlayManager->gatherNodeChildrenInfo_.push_back(GatherNodeChildInfo());
    overlayManager->RemoveGatherNodeWithAnimation();

    EXPECT_FALSE(overlayManager->hasGatherNode_);
}

/**
 * @tc.name: GetPixelMapContentNode001
 * @tc.desc: Test GetPixelMapContentNode
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, GetPixelMapContentNode001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    EXPECT_EQ(overlayManager->GetPixelMapContentNode(true), nullptr);
    EXPECT_EQ(overlayManager->GetPixelMapContentNode(false), nullptr);
}

/**
 * @tc.name: GetPixelMapContentNodeForSubwindow001
 * @tc.desc: Test GetPixelMapContentNodeForSubwindow
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, GetPixelMapContentNodeForSubwindow001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    EXPECT_EQ(overlayManager->GetPixelMapContentNodeForSubwindow(), nullptr);
}

/**
 * @tc.name: GetPixelMapContentNodeForSubwindow002
 * @tc.desc: Test GetPixelMapContentNodeForSubwindow
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, GetPixelMapContentNodeForSubwindow002, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    EXPECT_EQ(overlayManager->GetPixelMapContentNodeForSubwindow(), nullptr);
}

/**
 * @tc.name: OnUIExtensionWindowSizeChange001
 * @tc.desc: Test OnUIExtensionWindowSizeChange
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, OnUIExtensionWindowSizeChange001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto dialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, 2, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    ASSERT_NE(dialogNode, nullptr);
    dialogNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    overlayManager->OnUIExtensionWindowSizeChange();

    overlayManager->dialogMap_.insert({ 1, rootNode });
    overlayManager->dialogMap_.insert({ 2, dialogNode });

    overlayManager->OnUIExtensionWindowSizeChange();
    EXPECT_FALSE(dialogNode->GetPattern<DialogPattern>()->isUIExtensionSubWindow_);
}

/**
 * @tc.name: UpdateCustomDialog001
 * @tc.desc: Test UpdateCustomDialog
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, UpdateCustomDialog001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    WeakPtr<NG::UINode> node = nullptr;
    DialogProperties dialogProps;
    std::function<void(int32_t)> callback = nullptr;
    overlayManager->UpdateCustomDialog(node, dialogProps, std::move(callback));

    callback = [](int32_t err) {};
    overlayManager->UpdateCustomDialog(node, dialogProps, std::move(callback));

    node = rootNode;
    int32_t code;
    callback = [&code](int32_t err) { code = err; };
    overlayManager->UpdateCustomDialog(node, dialogProps, std::move(callback));
    EXPECT_EQ(code, 103303);
}

/**
 * @tc.name: PopModalDialog001
 * @tc.desc: Test PopModalDialog
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, ShowCalendarDialog001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    overlayManager->PopModalDialog(2);

    overlayManager->maskNodeIdMap_.insert({ 1, 1 });
    overlayManager->PopModalDialog(2);

    overlayManager->maskNodeIdMap_.insert({ 2, 2 });
    overlayManager->PopModalDialog(2);

    auto subwindow = AceType::MakeRefPtr<MockSubwindow>();
    SubwindowManager::GetInstance()->AddSubwindow(2, subwindow);
    overlayManager->subWindowId_ = 2;
    overlayManager->PopModalDialog(2);

    EXPECT_TRUE(SubwindowManager::GetInstance()->GetSubwindow(2));
}

/**
 * @tc.name: HasModalPage001
 * @tc.desc: Test HasModalPage
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, HasModalPage001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    EXPECT_FALSE(overlayManager->HasModalPage());

    overlayManager->modalList_.push_back(nullptr);
    overlayManager->modalList_.push_back(rootNode);
    EXPECT_FALSE(overlayManager->HasModalPage());

    auto modalPattern = AceType::MakeRefPtr<ModalPresentationPattern>(-1, ModalTransition::DEFAULT, nullptr);
    auto modalNode = FrameNodeOnTree::CreateFrameNode(V2::MODAL_PAGE_TAG, -1, modalPattern);
    overlayManager->modalList_.push_back(modalNode);

    EXPECT_TRUE(overlayManager->HasModalPage());
}

/**
 * @tc.name: GetPopupIdByNode001
 * @tc.desc: Test GetPopupIdByNode
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, GetPopupIdByNode001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    EXPECT_EQ(overlayManager->GetPopupIdByNode(nullptr), -1);

    overlayManager->popupMap_.insert({ 0, NG::PopupInfo() });
    overlayManager->GetPopupIdByNode(rootNode);

    NG::PopupInfo info;
    info.popupNode = rootNode;
    overlayManager->popupMap_.insert({ 1, info });
    EXPECT_EQ(overlayManager->GetPopupIdByNode(rootNode), 1);
}

/**
 * @tc.name: RemoveOverlayCommon001
 * @tc.desc: Test RemoveOverlayCommon
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, RemoveOverlayCommon001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    RefPtr<NG::FrameNode> overlay;
    RefPtr<Pattern> pattern;
    EXPECT_EQ(overlayManager->RemoveOverlayCommon(rootNode, overlay, pattern, false, false), 0);

    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    EXPECT_TRUE(toastProperty->HasToastAlignment());
    EXPECT_EQ(toastProperty->GetToastAlignmentValue(), Alignment::TOP_LEFT);
    pattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_EQ(overlayManager->RemoveOverlayCommon(rootNode, overlay, pattern, false, false), 0);
}

/**
 * @tc.name: RemoveOverlayCommon002
 * @tc.desc: Test RemoveOverlayCommon
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, RemoveOverlayCommon002, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto dialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, 2, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    ASSERT_NE(dialogNode, nullptr);
    dialogNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    RefPtr<NG::FrameNode> overlay;
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    EXPECT_TRUE(toastProperty->HasToastAlignment());
    EXPECT_EQ(toastProperty->GetToastAlignmentValue(), Alignment::TOP_LEFT);
    RefPtr<Pattern> pattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_EQ(overlayManager->RemoveOverlayCommon(rootNode, overlay, pattern, false, false), 0);
}

/**
 * @tc.name: RemoveOverlayCommon003
 * @tc.desc: Test RemoveOverlayCommon
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, RemoveOverlayCommon003, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());

    for (int i = 0; i < 3; ++i) {
        auto dialogNode = FrameNode::CreateFrameNode(
            V2::DIALOG_ETS_TAG, 2, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
        ASSERT_NE(dialogNode, nullptr);
        dialogNode->MountToParent(rootNode);
    }

    auto dialogNode1 = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, 2, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    ASSERT_NE(dialogNode1, nullptr);
    auto dialogPattern1 = dialogNode1->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern1, nullptr);
    dialogPattern1->onWillDismiss_ = nullptr;
    dialogNode1->MountToParent(rootNode);

    auto dialogNode2 = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, 2, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    ASSERT_NE(dialogNode2, nullptr);
    auto dialogPattern2 = dialogNode2->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern2, nullptr);
    dialogPattern2->SetOnWillDismissByNDK([](const int32_t& info) -> bool { return true; });
    dialogNode2->MountToParent(rootNode);

    rootNode->MarkDirtyNode();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    RefPtr<NG::FrameNode> overlay;
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    EXPECT_TRUE(toastProperty->HasToastAlignment());
    EXPECT_EQ(toastProperty->GetToastAlignmentValue(), Alignment::TOP_LEFT);
    RefPtr<Pattern> pattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_EQ(overlayManager->RemoveOverlayCommon(rootNode, overlay, pattern, false, true), 1);
    EXPECT_EQ(overlayManager->RemoveOverlayCommon(rootNode, overlay, pattern, false, false), 0);
}

/**
 * @tc.name: RemoveOverlayCommon004
 * @tc.desc: Test RemoveOverlayCommon
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, RemoveOverlayCommon004, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());

    for (int i = 0; i < 3; ++i) {
        auto dialogNode = FrameNode::CreateFrameNode(
            V2::DIALOG_ETS_TAG, 2, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
        ASSERT_NE(dialogNode, nullptr);
        auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
        dialogPattern->onWillDismissByNDK_ = [](const int32_t& info) -> bool { return true; };
        dialogNode->MountToParent(rootNode);
    }

    rootNode->MarkDirtyNode();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    RefPtr<NG::FrameNode> overlay;
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    EXPECT_TRUE(toastProperty->HasToastAlignment());
    EXPECT_EQ(toastProperty->GetToastAlignmentValue(), Alignment::TOP_LEFT);
    RefPtr<Pattern> pattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_EQ(overlayManager->RemoveOverlayCommon(rootNode, overlay, pattern, false, false), 1);
}

/**
 * @tc.name: RemoveOverlayCommon005
 * @tc.desc: Test RemoveOverlayCommon
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, RemoveOverlayCommon005, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());

    for (int i = 0; i < 3; ++i) {
        auto dialogNode = FrameNode::CreateFrameNode(
            V2::DIALOG_ETS_TAG, 2, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
        ASSERT_NE(dialogNode, nullptr);
        auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
        dialogPattern->SetOnWillDismiss([](const int32_t& info, const int32_t& instanceId) {});
        dialogNode->MountToParent(rootNode);
    }

    rootNode->MarkDirtyNode();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    RefPtr<NG::FrameNode> overlay;
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    EXPECT_TRUE(toastProperty->HasToastAlignment());
    EXPECT_EQ(toastProperty->GetToastAlignmentValue(), Alignment::TOP_LEFT);
    RefPtr<Pattern> pattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_EQ(overlayManager->RemoveOverlayCommon(rootNode, overlay, pattern, false, false), 1);
}

/**
 * @tc.name: FindWebNode001
 * @tc.desc: Test FindWebNode
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, FindWebNode001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    RefPtr<NG::FrameNode> webNode;
    bool isNavDestination = false;
    overlayManager->FindWebNode(nullptr, webNode, isNavDestination);
    overlayManager->FindWebNode(rootNode, rootNode, isNavDestination);
    overlayManager->FindWebNode(rootNode, webNode, isNavDestination);

    rootNode->isInternal_ = true;
    overlayManager->FindWebNode(rootNode, webNode, isNavDestination);

    rootNode->isInternal_ = false;
    overlayManager->FindWebNode(rootNode, webNode, isNavDestination);
    EXPECT_FALSE(webNode);
}

/**
 * @tc.name: RemoveOverlayCommon006
 * @tc.desc: Test RemoveOverlayCommon
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, RemoveOverlayCommon006, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());

    for (int i = 0; i < 3; ++i) {
        auto bubblePattern = AceType::MakeRefPtr<BubblePattern>();
        auto bubbleNode = FrameNodeOnTree::CreateFrameNode(V2::POPUP_ETS_TAG, 2, bubblePattern);
        rootNode->AddChild(bubbleNode);
    }

    rootNode->MarkDirtyNode();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    RefPtr<NG::FrameNode> overlay;
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    EXPECT_TRUE(toastProperty->HasToastAlignment());
    EXPECT_EQ(toastProperty->GetToastAlignmentValue(), Alignment::TOP_LEFT);
    RefPtr<Pattern> pattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_EQ(overlayManager->RemoveOverlayCommon(rootNode, overlay, pattern, false, false), 0);
}

/**
 * @tc.name: RemoveOverlayCommon007
 * @tc.desc: Test RemoveOverlayCommon
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, RemoveOverlayCommon007, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());

    for (int i = 0; i < 3; ++i) {
        auto menu = FrameNode::CreateFrameNode("targetNode", 2, AceType::MakeRefPtr<MenuWrapperPattern>(2), false);
        rootNode->AddChild(menu);
    }

    rootNode->MarkDirtyNode();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    RefPtr<NG::FrameNode> overlay;
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    EXPECT_TRUE(toastProperty->HasToastAlignment());
    EXPECT_EQ(toastProperty->GetToastAlignmentValue(), Alignment::TOP_LEFT);
    RefPtr<Pattern> pattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_EQ(overlayManager->RemoveOverlayCommon(rootNode, overlay, pattern, false, false), 1);
}

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        return MakeRefPtr<TestNode>(nodeId);
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};

/**
 * @tc.name: FindWebNode002
 * @tc.desc: Test FindWebNode
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, FindWebNode002, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    auto framenode = FrameNode::CreateFrameNode(V2::WEB_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>(), false);

    RefPtr<NG::FrameNode> webNode;
    bool isNavDestination = false;
    overlayManager->FindWebNode(TestNode::CreateTestNode(3), webNode, isNavDestination);
    framenode->isInternal_ = false;
    overlayManager->FindWebNode(framenode, webNode, isNavDestination);

    webNode = nullptr;
    rootNode->AddChild(framenode);
    framenode->isInternal_ = false;
    overlayManager->FindWebNode(rootNode, webNode, isNavDestination);

    EXPECT_EQ(webNode, framenode);
}

/**
 * @tc.name: RemoveAllModalInOverlayByList001
 * @tc.desc: Test RemoveAllModalInOverlayByList
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, RemoveAllModalInOverlayByList001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    EXPECT_TRUE(overlayManager->RemoveAllModalInOverlayByList());

    overlayManager->modalStack_.push(rootNode);
    EXPECT_TRUE(overlayManager->RemoveAllModalInOverlayByList());
}

/**
 * @tc.name: AfterRemoveAllModalInOverlayByList001
 * @tc.desc: Test AfterRemoveAllModalInOverlayByList
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, AfterRemoveAllModalInOverlayByList001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->modalList_.push_back(rootNode);
    overlayManager->AfterRemoveAllModalInOverlayByList();
    EXPECT_EQ(overlayManager->modalList_.size(), overlayManager->modalStack_.size());
}

/**
 * @tc.name: OnRemoveAllModalInOverlayByList001
 * @tc.desc: Test OnRemoveAllModalInOverlayByList
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, OnRemoveAllModalInOverlayByList001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->modalList_.push_back(rootNode);
    EXPECT_FALSE(overlayManager->OnRemoveAllModalInOverlayByList());
}

/**
 * @tc.name: OverlayManagerTwoTestNg_OpenDialogAnimation
 * @tc.desc: Test SheetView::CreateTitleColumn.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, OpenDialogAnimation, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);
    MockContainer::Current()->SetIsSceneBoardWindow(true);
    overlayManager->OpenDialogAnimation(dialogNode_, props);
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step3. create dialog mask node
     */
    DialogProperties maskProps {
        .isMask = true,
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto maskNode_ = DialogView::CreateDialogNode(props, nullptr);
    EXPECT_NE(maskNode_, nullptr);
    overlayManager->OpenDialogAnimation(maskNode_, maskProps);
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_OpenDialogAnimation002
 * @tc.desc: Test OverlayManager::OpenDialogAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, OpenDialogAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);
    MockContainer::Current()->SetIsSceneBoardWindow(true);
    overlayManager->OpenDialogAnimation(dialogNode_, props);
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    auto contentNode1_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode1_, nullptr);
    auto dialogNode1_ = DialogView::CreateDialogNode(props, contentNode1_);
    EXPECT_NE(dialogNode1_, nullptr);
    MockContainer::Current()->SetIsSceneBoardWindow(true);
    props.levelOrder = std::make_optional(1.0);
    overlayManager->OpenDialogAnimation(dialogNode1_, props);
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_OpenDialogAnimation003
 * @tc.desc: Test OverlayManager::OpenDialogAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, OpenDialogAnimation003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);
    MockContainer::Current()->SetIsSceneBoardWindow(true);
    overlayManager->OpenDialogAnimation(dialogNode_, props);
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    auto contentNode1_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode1_, nullptr);
    auto dialogNode1_ = DialogView::CreateDialogNode(props, contentNode1_);
    EXPECT_NE(dialogNode1_, nullptr);
    MockContainer::Current()->SetIsSceneBoardWindow(true);
    props.levelOrder = std::make_optional(1.0);
    overlayManager->OpenDialogAnimation(dialogNode1_, props);
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    auto contentNode2_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode2_, nullptr);
    auto dialogNode2_ = DialogView::CreateDialogNode(props, contentNode2_);
    EXPECT_NE(dialogNode2_, nullptr);
    props.levelOrder = std::make_optional(0.0);
    overlayManager->OpenDialogAnimation(dialogNode2_, props);
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_SetDialogTransitionEffect
 * @tc.desc: Test SheetView::CreateTitleColumn.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, SetDialogTransitionEffect, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);
    MockContainer::Current()->SetIsSceneBoardWindow(true);
    overlayManager->SetDialogTransitionEffect(dialogNode_, props);
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_SetDialogTransitionEffect002
 * @tc.desc: Test OverlayManager::SetDialogTransitionEffect.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, SetDialogTransitionEffect002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);
    MockContainer::Current()->SetIsSceneBoardWindow(true);
    overlayManager->SetDialogTransitionEffect(dialogNode_, props);
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    auto contentNode1_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode1_, nullptr);
    auto dialogNode1_ = DialogView::CreateDialogNode(props, contentNode1_);
    EXPECT_NE(dialogNode1_, nullptr);
    props.levelOrder = std::make_optional(1.0);
    overlayManager->SetDialogTransitionEffect(dialogNode1_, props);
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_SetDialogTransitionEffect003
 * @tc.desc: Test OverlayManager::SetDialogTransitionEffect.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, SetDialogTransitionEffect003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);
    MockContainer::Current()->SetIsSceneBoardWindow(true);
    overlayManager->SetDialogTransitionEffect(dialogNode_, props);
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    auto contentNode1_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode1_, nullptr);
    auto dialogNode1_ = DialogView::CreateDialogNode(props, contentNode1_);
    EXPECT_NE(dialogNode1_, nullptr);
    props.levelOrder = std::make_optional(1.0);
    overlayManager->SetDialogTransitionEffect(dialogNode1_, props);
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
    overlayManager->PutLevelOrder(dialogNode1_, props.levelOrder);

    auto contentNode2_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode2_, nullptr);
    auto dialogNode2_ = DialogView::CreateDialogNode(props, contentNode2_);
    EXPECT_NE(dialogNode2_, nullptr);
    props.levelOrder = std::make_optional(0.0);
    overlayManager->SetDialogTransitionEffect(dialogNode2_, props);
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_PutLevelOrder001
 * @tc.desc: Test OverlayManager::PutLevelOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, PutLevelOrder001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    overlayManager->PutLevelOrder(dialogNode_, std::nullopt);
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 0);
    EXPECT_EQ(overlayManager->orderNodesMap_.size(), 0);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_PutLevelOrder002
 * @tc.desc: Test OverlayManager::PutLevelOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, PutLevelOrder002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    overlayManager->PutLevelOrder(dialogNode_, std::make_optional(0.0));
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 1);
    EXPECT_EQ(overlayManager->orderNodesMap_.size(), 1);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_PopLevelOrder001
 * @tc.desc: Test OverlayManager::PopLevelOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, PopLevelOrder001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    overlayManager->PopLevelOrder(dialogNode_->GetId());
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 0);
    EXPECT_EQ(overlayManager->orderNodesMap_.size(), 0);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_PopLevelOrder002
 * @tc.desc: Test OverlayManager::PopLevelOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, PopLevelOrder002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    overlayManager->nodeIdOrderMap_[dialogNode_->GetId()] = 0.0;
    overlayManager->PopLevelOrder(dialogNode_->GetId());
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 0);

    overlayManager->nodeIdOrderMap_[dialogNode_->GetId()] = 0.0;
    overlayManager->PopLevelOrder(dialogNode_->GetId());
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 0);
    overlayManager->nodeIdOrderMap_.erase(dialogNode_->GetId());
}

/**
 * @tc.name: OverlayManagerTwoTestNg_PopLevelOrder003
 * @tc.desc: Test OverlayManager::PopLevelOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, PopLevelOrder003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    overlayManager->PopLevelOrder(dialogNode_->GetId());
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 0);
    EXPECT_EQ(overlayManager->orderNodesMap_.size(), 0);

    overlayManager->nodeIdOrderMap_[dialogNode_->GetId()] = 0.0;
    overlayManager->PopLevelOrder(dialogNode_->GetId());
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 0);
    overlayManager->nodeIdOrderMap_.erase(dialogNode_->GetId());

    overlayManager->PutLevelOrder(dialogNode_, std::make_optional(0.0));
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 1);
    EXPECT_EQ(overlayManager->orderNodesMap_.size(), 1);
    overlayManager->PopLevelOrder(dialogNode_->GetId());
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 0);
    EXPECT_EQ(overlayManager->orderNodesMap_.size(), 0);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_GetPrevNodeWithOrder001
 * @tc.desc: Test OverlayManager::GetPrevNodeWithOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, GetPrevNodeWithOrder001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    overlayManager->orderNodesMap_[0.0] = {};
    auto prevNode = overlayManager->GetPrevNodeWithOrder(std::nullopt);
    EXPECT_EQ(prevNode, nullptr);
    overlayManager->orderNodesMap_.erase(0.0);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_GetPrevNodeWithOrder002
 * @tc.desc: Test OverlayManager::GetPrevNodeWithOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, GetPrevNodeWithOrder002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    auto levelOrder1 = std::make_optional(1.0);
    overlayManager->PutLevelOrder(dialogNode_, levelOrder1);
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 1);
    EXPECT_EQ(overlayManager->orderNodesMap_.size(), 1);
    auto prevNode1 = overlayManager->GetPrevNodeWithOrder(levelOrder1);
    EXPECT_EQ(prevNode1->GetId(), dialogNode_->GetId());
}

/**
 * @tc.name: OverlayManagerTwoTestNg_GetPrevNodeWithOrder003
 * @tc.desc: Test OverlayManager::GetPrevNodeWithOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, GetPrevNodeWithOrder003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    auto levelOrder1 = std::make_optional(1.0);
    overlayManager->PutLevelOrder(dialogNode_, levelOrder1);
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 1);
    EXPECT_EQ(overlayManager->orderNodesMap_.size(), 1);
    auto prevNode1 = overlayManager->GetPrevNodeWithOrder(levelOrder1);
    EXPECT_EQ(prevNode1->GetId(), dialogNode_->GetId());

    auto contentNode2_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode2_, nullptr);
    auto dialogNode2_ = DialogView::CreateDialogNode(props, contentNode2_);
    EXPECT_NE(dialogNode2_, nullptr);

    auto levelOrder2 = std::make_optional(2.0);
    overlayManager->PutLevelOrder(dialogNode2_, levelOrder2);
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 2);
    EXPECT_EQ(overlayManager->orderNodesMap_.size(), 2);
    auto prevNode2 = overlayManager->GetPrevNodeWithOrder(levelOrder1);
    EXPECT_EQ(prevNode2->GetId(), dialogNode_->GetId());
}

/**
 * @tc.name: OverlayManagerTwoTestNg_GetPrevNodeWithOrder004
 * @tc.desc: Test OverlayManager::GetPrevNodeWithOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, GetPrevNodeWithOrder004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    overlayManager->orderNodesMap_[0.0] = {};
    auto prevNode = overlayManager->GetPrevNodeWithOrder(std::nullopt);
    EXPECT_EQ(prevNode, nullptr);
    overlayManager->orderNodesMap_.erase(0.0);

    auto levelOrder1 = std::make_optional(1.0);
    overlayManager->PutLevelOrder(dialogNode_, levelOrder1);
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 1);
    EXPECT_EQ(overlayManager->orderNodesMap_.size(), 1);
    auto prevNode1 = overlayManager->GetPrevNodeWithOrder(levelOrder1);
    EXPECT_EQ(prevNode1->GetId(), dialogNode_->GetId());

    auto contentNode2_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode2_, nullptr);
    auto dialogNode2_ = DialogView::CreateDialogNode(props, contentNode2_);
    EXPECT_NE(dialogNode2_, nullptr);

    auto levelOrder2 = std::make_optional(2.0);
    overlayManager->PutLevelOrder(dialogNode2_, levelOrder2);
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 2);
    EXPECT_EQ(overlayManager->orderNodesMap_.size(), 2);
    auto prevNode2 = overlayManager->GetPrevNodeWithOrder(levelOrder1);
    EXPECT_EQ(prevNode2->GetId(), dialogNode_->GetId());
}

/**
 * @tc.name: OverlayManagerTwoTestNg_IsTopOrder001
 * @tc.desc: Test OverlayManager::IsTopOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, IsTopOrder001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    bool needFocus = overlayManager->IsTopOrder(std::nullopt);
    EXPECT_TRUE(needFocus);
    needFocus = overlayManager->IsTopOrder(std::make_optional(1.0));
    EXPECT_TRUE(needFocus);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_IsTopOrder002
 * @tc.desc: Test OverlayManager::IsTopOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, IsTopOrder002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    auto needFocus = overlayManager->IsTopOrder(std::make_optional(1.0));
    EXPECT_TRUE(needFocus);

    overlayManager->PutLevelOrder(dialogNode_, std::make_optional(0.0));
    needFocus = overlayManager->IsTopOrder(std::make_optional(1.0));
    EXPECT_TRUE(needFocus);

    needFocus = overlayManager->IsTopOrder(std::make_optional(-1.0));
    EXPECT_FALSE(needFocus);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_GetTopOrder001
 * @tc.desc: Test OverlayManager::GetTopOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, GetTopOrder001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    auto topOrder = overlayManager->GetTopOrder();
    EXPECT_EQ(topOrder, std::nullopt);

    overlayManager->orderNodesMap_[0.0] = {};
    topOrder = overlayManager->GetTopOrder();
    EXPECT_EQ(topOrder, std::nullopt);
    overlayManager->orderNodesMap_.erase(0.0);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_GetTopOrder002
 * @tc.desc: Test OverlayManager::GetTopOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, GetTopOrder002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    overlayManager->PutLevelOrder(dialogNode_, std::make_optional(0.0));
    auto topOrder = overlayManager->GetTopOrder();
    EXPECT_EQ(topOrder, std::make_optional(0.0));
}

/**
 * @tc.name: OverlayManagerTwoTestNg_GetTopOrder003
 * @tc.desc: Test OverlayManager::GetTopOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, GetTopOrder003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    overlayManager->PutLevelOrder(dialogNode_, std::make_optional(0.0));
    auto topOrder = overlayManager->GetTopOrder();
    EXPECT_EQ(topOrder, std::make_optional(0.0));

    auto contentNode2_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode2_, nullptr);
    auto dialogNode2_ = DialogView::CreateDialogNode(props, contentNode2_);
    EXPECT_NE(dialogNode2_, nullptr);

    overlayManager->PutLevelOrder(dialogNode2_, std::make_optional(1.0));
    topOrder = overlayManager->GetTopOrder();
    EXPECT_EQ(topOrder, std::make_optional(1.0));
}

/**
 * @tc.name: OverlayManagerTwoTestNg_GetBottomOrder001
 * @tc.desc: Test OverlayManager::GetBottomOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, GetBottomOrder001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    auto bottomOrder = overlayManager->GetBottomOrder();
    EXPECT_EQ(bottomOrder, std::nullopt);

    overlayManager->orderNodesMap_[0.0] = {};
    bottomOrder = overlayManager->GetBottomOrder();
    EXPECT_EQ(bottomOrder, std::nullopt);
    overlayManager->orderNodesMap_.erase(0.0);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_GetBottomOrder002
 * @tc.desc: Test OverlayManager::GetBottomOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, GetBottomOrder002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    overlayManager->PutLevelOrder(dialogNode_, std::make_optional(0.0));
    auto bottomOrder = overlayManager->GetBottomOrder();
    EXPECT_EQ(bottomOrder, std::make_optional(0.0));
}

/**
 * @tc.name: OverlayManagerTwoTestNg_GetBottomOrder003
 * @tc.desc: Test OverlayManager::GetBottomOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, GetBottomOrder003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. create dialog node
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    auto contentNode_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode_, nullptr);
    auto dialogNode_ = DialogView::CreateDialogNode(props, contentNode_);
    EXPECT_NE(dialogNode_, nullptr);

    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();

    overlayManager->PutLevelOrder(dialogNode_, std::make_optional(0.0));
    auto bottomOrder = overlayManager->GetBottomOrder();
    EXPECT_EQ(bottomOrder, std::make_optional(0.0));

    auto contentNode2_ = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(contentNode2_, nullptr);
    auto dialogNode2_ = DialogView::CreateDialogNode(props, contentNode2_);
    EXPECT_NE(dialogNode2_, nullptr);

    overlayManager->PutLevelOrder(dialogNode2_, std::make_optional(-1.0));
    bottomOrder = overlayManager->GetBottomOrder();
    EXPECT_EQ(bottomOrder, std::make_optional(-1.0));
}

/**
 * @tc.name: ShowMenuAnimation
 * @tc.desc: Test SheetView::CreateTitleColumn.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, ShowMenuAnimation, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuPattern = mainMenu->GetPattern<MenuPattern>();
    EXPECT_NE(menuPattern, nullptr);
    menuPattern->SetPreviewMode(MenuPreviewMode::CUSTOM);
    EXPECT_EQ(menuPattern->GetPreviewMode(), MenuPreviewMode::CUSTOM);
    mainMenu->MountToParent(menuNode);
    menuNode->MountToParent(rootNode_);
    rootNode_->MarkDirtyNode();
    auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    EXPECT_NE(wrapperPattern, nullptr);
    EXPECT_NE(wrapperPattern->HasTransitionEffect(), true);
    auto renderContext = menuNode->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    EXPECT_EQ(wrapperPattern->GetPreviewMode(), MenuPreviewMode::CUSTOM);
    auto previewChild = wrapperPattern->GetPreview();
    EXPECT_EQ(previewChild, nullptr);
    overlayManager->ShowMenuAnimation(menuNode);
    auto firstMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 4, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    firstMenu->MountToParent(menuNode);
    menuNode->MarkDirtyNode();
    rootNode_->MarkDirtyNode();
    previewChild = wrapperPattern->GetPreview();
    EXPECT_NE(previewChild, nullptr);
    auto previewPattern = AceType::DynamicCast<MenuPreviewPattern>(previewChild->GetPattern());
    EXPECT_EQ(previewPattern, nullptr);
    overlayManager->ShowMenuAnimation(menuNode);
    rootNode_->children_.pop_back();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_OnPopMenuAnimationFinished
 * @tc.desc: Test SheetView::CreateTitleColumn.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, OnPopMenuAnimationFinished, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    mainMenu->MountToParent(menuNode);
    menuNode->MountToParent(rootNode_);
    rootNode_->MarkDirtyNode();
    const WeakPtr<FrameNode> menuWK(menuNode);
    EXPECT_NE(menuWK.Upgrade(), nullptr);
    const WeakPtr<UINode> rootWeak = overlayManager->GetRootNode();
    EXPECT_NE(rootWeak.Upgrade(), nullptr);
    const WeakPtr<OverlayManager> weakManager_(overlayManager);
    EXPECT_NE(weakManager_.Upgrade(), nullptr);
    auto menuWrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    overlayManager->OnPopMenuAnimationFinished(menuWK, rootWeak, weakManager_, MIN_SUBCONTAINER_ID);
    std::function<void()> onDisappear = []() {};
    menuWrapperPattern->RegisterMenuDisappearCallback(onDisappear);
    auto pipelineMenuContext = menuNode->GetContext();
    pipelineMenuContext->instanceId_ = MIN_SUBCONTAINER_ID;
    auto containerId = pipelineMenuContext->GetInstanceId();
    EXPECT_EQ(containerId, MIN_SUBCONTAINER_ID);
    overlayManager->OnPopMenuAnimationFinished(menuWK, rootWeak, weakManager_, MIN_SUBCONTAINER_ID);
    rootNode_->children_.pop_back();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_PopMenuAnimation
 * @tc.desc: Test SheetView::CreateTitleColumn.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, PopMenuAnimation, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    mainMenu->MountToParent(menuNode);
    menuNode->MountToParent(rootNode_);
    rootNode_->MarkDirtyNode();
    overlayManager->PopMenuAnimation(menuNode, true, true);
    auto menuWrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    menuWrapperPattern->SetHasTransitionEffect(true);
    EXPECT_EQ(menuWrapperPattern->HasTransitionEffect(), true);
    auto menuPattern = mainMenu->GetPattern<MenuPattern>();
    menuPattern->SetPreviewMode(MenuPreviewMode::CUSTOM);
    EXPECT_EQ(menuPattern->GetPreviewMode(), MenuPreviewMode::CUSTOM);
    EXPECT_EQ(menuWrapperPattern->GetPreviewMode(), MenuPreviewMode::CUSTOM);
    menuNode->renderContext_ = AceType::MakeRefPtr<RosenRenderContext>();
    auto deformRenderContext = menuNode->GetRenderContext();
    EXPECT_NE(deformRenderContext, nullptr);
    auto renderContext = AceType::DynamicCast<RosenRenderContext>(deformRenderContext);
    EXPECT_NE(renderContext, nullptr);
    EXPECT_FALSE(renderContext->HasDisappearTransition());
    overlayManager->PopMenuAnimation(menuNode, true, true);
    rootNode_->children_.pop_back();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
}

/**
 * @tc.name: OverlayManagerTwoTestNg_ShowMenuClearAnimation
 * @tc.desc: Test SheetView::CreateTitleColumn.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, ShowMenuClearAnimation, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    mainMenu->MountToParent(menuNode);
    menuNode->MountToParent(rootNode_);
    rootNode_->MarkDirtyNode();
    auto dragEventHub = AceType::MakeRefPtr<EventHub>();
    auto dragFrameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    dragEventHub->host_ = AceType::WeakClaim(AceType::RawPtr(dragFrameNode));
    dragFrameNode->eventHub_ = dragEventHub;
    dragFrameNode->SetDraggable(true);
    dragFrameNode->GetOrCreateFocusHub();
    AnimationOption option;
    overlayManager->ShowMenuClearAnimation(menuNode, option, false, true);
    auto overlayContainer = Container::Current();
    overlayContainer->SetApiTargetVersion(12);
    EXPECT_EQ(overlayContainer->GetApiTargetVersion(), 12);
    EXPECT_EQ(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE), true);
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    EXPECT_NE(mainPipeline, false);
    auto dragDropManager = mainPipeline->GetDragDropManager();
    EXPECT_NE(dragDropManager, false);
    DragDropGlobalController::GetInstance().SetPrepareDragFrameNode(dragFrameNode);
    auto draggingNode = DragDropGlobalController::GetInstance().GetPrepareDragFrameNode().Upgrade();
    EXPECT_NE(draggingNode, false);
    auto eventHub = draggingNode->GetOrCreateEventHub<EventHub>();
    EXPECT_NE(eventHub, false);
    auto frameNode = eventHub->GetFrameNode();
    EXPECT_NE(frameNode, false);
    auto focusHub = frameNode->GetFocusHub();
    EXPECT_NE(focusHub, false);
    std::function<bool(const KeyEvent&)> onKeyEvenCallback = [](const KeyEvent& event) -> bool { return true; };
    focusHub->onKeyEventsInternal_.emplace(OnKeyEventType::CONTEXT_MENU, onKeyEvenCallback);
    auto isBindOrigNode = overlayManager->IsContextMenuBindedOnOrigNode();
    EXPECT_EQ(isBindOrigNode, true);
    overlayManager->ShowMenuClearAnimation(menuNode, option, true, true);
    auto menuPattern = mainMenu->GetPattern<MenuPattern>();
    menuPattern->SetPreviewMode(MenuPreviewMode::CUSTOM);
    overlayManager->ShowMenuClearAnimation(menuNode, option, true, true);
    rootNode_->children_.pop_back();
    EXPECT_EQ(rootNode_->GetChildren().size(), 1);
}

/**
 * @tc.name: ResetDragMoveVector
 * @tc.desc: Test reset drag move vector.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTwoTestNg, ResetDragMoveVector, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode_ = overlayManager->GetRootNode().Upgrade();
    ASSERT_EQ(rootNode_->GetChildren().size(), 1);
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->SetPreviewMode(MenuPreviewMode::CUSTOM);
    ASSERT_EQ(menuPattern->GetPreviewMode(), MenuPreviewMode::CUSTOM);
    ASSERT_NE(mainMenu, nullptr);
    ASSERT_NE(menuNode, nullptr);
    mainMenu->MountToParent(menuNode);
    menuNode->MountToParent(rootNode_);

    /**
     * @tc.steps: step2. set drag move vector
     */
    overlayManager->dragMoveVector_ = OffsetF(1.0f, 1.0f);
    overlayManager->lastDragMoveVector_ = OffsetF(1.0f, 1.0f);

    /**
     * @tc.steps: step3. ShowMenuAnimation
     */
    overlayManager->ShowMenuAnimation(menuNode);
    
    EXPECT_EQ(overlayManager->dragMoveVector_, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(overlayManager->lastDragMoveVector_, OffsetF(0.0f, 0.0f));
}

} // namespace OHOS::Ace::NG
