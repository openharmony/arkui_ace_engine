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
#include <mutex>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "base/window/foldable_window.h"
#include "core/components/common/properties/color.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components/picker/picker_data.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/overlay/modal_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/sheet_theme.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const NG::BorderColorProperty BORDER_COLOR_TEST = { Color::BLUE,
    Color::BLUE, Color::BLUE, Color::BLUE };
const NG::BorderColorProperty NEW_BORDER_COLOR_TEST = { Color::RED,
    Color::GREEN, Color::GRAY, Color::BLACK };
const std::string TEXT_TAG = "text";
const OffsetF MENU_OFFSET(10.0, 10.0);
const std::string MESSAGE = "hello world";
const std::string BOTTOMSTRING = "test";
const std::string LONGEST_CONTENT = "新建文件夹";
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
} // namespace

class OverlayManagerMenuTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestCase();
    static void TearDownTestCase();
    std::function<RefPtr<UINode>()> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;

protected:
    static RefPtr<FrameNode> CreateBubbleNode(const TestProperty& testProperty);
    static RefPtr<FrameNode> CreateTargetNode();
    static void CreateSheetStyle(SheetStyle& sheetStyle);
    void CreateSheetBuilder();
    int32_t minPlatformVersion_ = 0;
};

void OverlayManagerMenuTestNg::SetUp()
{
    minPlatformVersion_ = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
}

void OverlayManagerMenuTestNg::TearDown()
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion_);
}

void OverlayManagerMenuTestNg::SetUpTestCase()
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
void OverlayManagerMenuTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> OverlayManagerMenuTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

void OverlayManagerMenuTestNg::CreateSheetStyle(SheetStyle& sheetStyle)
{
    if (!sheetStyle.sheetMode.has_value()) {
        sheetStyle.sheetMode = SheetMode::MEDIUM;
    }
    if (!sheetStyle.showDragBar.has_value()) {
        sheetStyle.showDragBar = true;
    }
}

void OverlayManagerMenuTestNg::CreateSheetBuilder()
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
 * @tc.name: MenuTest001
 * @tc.desc: Test OverlayManager::SendToAccessibility.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, MenuTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node , preview node and root node.
     */
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto menuWrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    menuNode->MountToParent(menuWrapperNode);
    previewNode->MountToParent(menuWrapperNode);
    menuWrapperNode->MountToParent(rootNode);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step2. call SendToAccessibility
     * @tc.expected: menuWrapperNode is not null
     */
    overlayManager->SendToAccessibility(menuWrapperNode, true);
    ASSERT_NE(menuWrapperNode, nullptr);
}

/**
 * @tc.name: MenuTest002
 * @tc.desc: Test OverlayManager::SendToAccessibility.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, MenuTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node , preview node and root node.
     */
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto menuWrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    menuNode->MountToParent(menuWrapperNode);
    previewNode->MountToParent(menuWrapperNode);
    menuWrapperNode->MountToParent(rootNode);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step2. call SendToAccessibility
     * @tc.expected: menuWrapperNode is not null
     */
    overlayManager->SendToAccessibility(menuWrapperNode, false);
    ASSERT_NE(menuWrapperNode, nullptr);
}

/**
 * @tc.name: MenuTest003
 * @tc.desc: Test OverlayManager::ShowMenu.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, MenuTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node and root node.
     */
    auto menuId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, menuId, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenuFirst = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto subMenuSecond = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 4, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    mainMenu->MountToParent(menuNode);
    subMenuFirst->MountToParent(menuNode);
    subMenuSecond->MountToParent(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuWrapperPattern>();
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    menuNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. call showMenu when menuNode already appended.
     * @tc.expected: function exits rightly
     */
    auto targetId = rootNode->GetId();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowMenu(targetId, MENU_OFFSET, menuNode);
    overlayManager->HideMenu(menuNode, targetId);
    EXPECT_TRUE(overlayManager->menuMap_.empty());
    overlayManager->ShowMenuInSubWindow(rootNode->GetId(), MENU_OFFSET, menuNode);
    overlayManager->HideMenuInSubWindow(menuNode, rootNode->GetId());
    overlayManager->HideMenuInSubWindow();
    EXPECT_TRUE(overlayManager->menuMap_.empty());
    overlayManager->ShowMenuAnimation(menuNode);
    EXPECT_FALSE(menuPattern == nullptr);
    EXPECT_FALSE(menuPattern->animationOption_.GetOnFinishEvent() == nullptr);
    menuPattern->StartShowAnimation();
    auto menuHelper = overlayManager->ShowMenuHelper(menuNode, rootNode->GetId(), MENU_OFFSET);
    EXPECT_TRUE(menuHelper);

    /**
     * @tc.steps: step3. call HideMenu related functions after menuNode already erased.
     * @tc.expected: return normally
     */
    overlayManager->HideAllMenus();
    overlayManager->DeleteMenu(targetId);
    overlayManager->HideMenu(menuNode, targetId);
    overlayManager->HideMenuInSubWindow(menuNode, targetId);
    overlayManager->HideMenuInSubWindow();
    EXPECT_TRUE(overlayManager->menuMap_.empty());

    /**
     * @tc.steps: step4. call DeleteMenu again after menuNode already erased.
     * @tc.expected: return normally
     */
    overlayManager->RemoveMenu(menuNode);
    overlayManager->RemoveOverlayInSubwindow();
    overlayManager->DeleteMenu(targetId);
    EXPECT_TRUE(overlayManager->menuMap_.empty());
}

/**
 * @tc.name: MenuTest004
 * @tc.desc: Test OverlayManager::ShowMenu.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, MenuTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node and root node.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto targetId = rootNode->GetId();
    auto menuId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, menuId, AceType::MakeRefPtr<MenuWrapperPattern>(targetId));
    auto subMenuId = ElementRegister::GetInstance()->MakeUniqueId();
    auto subMenuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, subMenuId, AceType::MakeRefPtr<MenuPattern>(1, "Test", MenuType::MENU));
    subMenuNode->MountToParent(menuNode);
    /**
     * @tc.steps: step2. call showMenu when menuNode is nullptr and menuMap is empty.
     * @tc.expected: function exits normally
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowMenu(targetId, MENU_OFFSET, nullptr);
    overlayManager->ShowMenuInSubWindow(targetId, MENU_OFFSET, nullptr);
    EXPECT_TRUE(overlayManager->menuMap_.empty());
    /**
     * @tc.steps: step3. call showMenu when menuNode is not appended.
     * @tc.expected: menuNode mounted successfully
     */
    overlayManager->ShowMenu(targetId, MENU_OFFSET, menuNode);
    EXPECT_FALSE(overlayManager->menuMap_.empty());
    /**
     * @tc.steps: step4. call showMenu when menuNode is nullptr and menuMap is not empty.
     * @tc.expected: function exits normally
     */
    overlayManager->ShowMenu(targetId, MENU_OFFSET, nullptr);
    EXPECT_FALSE(overlayManager->menuMap_.empty());
    /**
     * @tc.steps: step5. call HideAllMenus.
     * @tc.expected: function exits normally
     */
    overlayManager->CleanMenuInSubWindow(targetId);
    overlayManager->FocusOverlayNode(menuNode, false);
    EXPECT_FALSE(overlayManager->menuMap_.empty());
    EXPECT_FALSE(overlayManager->RemoveOverlayInSubwindow());
    EXPECT_TRUE(overlayManager->RemoveAllModalInOverlay());
    EXPECT_FALSE(overlayManager->RemoveOverlay(false));
    overlayManager->RemoveMenu(rootNode);
}

/**
 * @tc.name: MenuTest005
 * @tc.desc: Test OverlayManager::PopMenuAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, MenuTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node , preview node and root node.
     */
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto menuWrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    menuNode->MountToParent(menuWrapperNode);
    previewNode->MountToParent(menuWrapperNode);
    menuWrapperNode->MountToParent(rootNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->SetPreviewMode(MenuPreviewMode::CUSTOM);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto previewContext = previewNode->GetRenderContext();
    ASSERT_NE(previewContext, nullptr);
    auto menuContext = previewNode->GetRenderContext();
    ASSERT_NE(menuContext, nullptr);
    previewContext->UpdateTransformScale(VectorF(1.0f, 1.0f));
    menuContext->UpdateTransformScale(VectorF(1.0f, 1.0f));

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();

    /**
     * @tc.steps: step2. call PopMenuAnimation when showPreviewAnimation is true
     * @tc.expected: the render context of menu and preview will update, and menu wrapper node will remove
     */
    EXPECT_EQ(rootNode->GetChildren().size(), 1);
    EXPECT_EQ(menuWrapperNode->GetChildren().size(), 2);
    overlayManager->PopMenuAnimation(menuWrapperNode, true);
    pipeline->taskExecutor_ = nullptr;
    EXPECT_EQ(menuContext->GetTransformScale(), VectorF(1.0f, 1.0f));
    EXPECT_EQ(previewContext->GetTransformScale(), VectorF(1.0f, 1.0f));
    EXPECT_EQ(rootNode->GetChildren().size(), 0);

    menuNode->MountToParent(menuWrapperNode);
    previewNode->MountToParent(menuWrapperNode);
    menuWrapperNode->MountToParent(rootNode);
    /**
     * @tc.steps: step2. call PopMenuAnimation when showPreviewAnimation is false
     * @tc.expected: the none of node will remove.
     */
    EXPECT_EQ(menuWrapperNode->GetChildren().size(), 2);
    overlayManager->PopMenuAnimation(menuWrapperNode, false);
    EXPECT_EQ(menuWrapperNode->GetChildren().size(), 2);
}

/**
 * @tc.name: MenuTest006
 * @tc.desc: Test OverlayManager::CleanMenuInSubWindowWithAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, MenuTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, preview node and root node.
     */
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto menuWrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    menuNode->MountToParent(menuWrapperNode);
    previewNode->MountToParent(menuWrapperNode);
    menuWrapperNode->MountToParent(rootNode);
    auto menuWrapperContext = menuWrapperNode->GetRenderContext();
    ASSERT_NE(menuWrapperContext, nullptr);
    menuWrapperContext->UpdateOpacity(1.0);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto previewContext = previewNode->GetRenderContext();
    ASSERT_NE(previewContext, nullptr);
    auto menuContext = previewNode->GetRenderContext();
    ASSERT_NE(menuContext, nullptr);
    previewContext->UpdateTransformScale(VectorF(0.0f, 0.0f));
    menuContext->UpdateTransformScale(VectorF(0.0f, 0.0f));
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->SetPreviewMode(MenuPreviewMode::CUSTOM);
    /**
     * @tc.steps: step2. call PopMenuAnimation when showPreviewAnimation is false
     * @tc.expected: the render context of menu and preview will update
     */
    overlayManager->CleanMenuInSubWindowWithAnimation();
    pipeline->taskExecutor_ = nullptr;
    EXPECT_EQ(menuContext->GetTransformScale(), VectorF(1.0f, 1.0f));
    EXPECT_EQ(previewContext->GetTransformScale(), VectorF(1.0f, 1.0f));
}

/**
 * @tc.name: MenuTest007
 * @tc.desc: Test OverlayManager::ShowMenuAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, MenuTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node , preview node and root node.
     */
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto menuWrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    menuNode->MountToParent(menuWrapperNode);
    previewNode->MountToParent(menuWrapperNode);
    menuWrapperNode->MountToParent(rootNode);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto focusHub = menuWrapperNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    menuPattern->SetPreviewMode(MenuPreviewMode::CUSTOM);
    /**
     * @tc.steps: step2. call ShowMenuAnimation and call StartShowAnimation of menu pattern
     * @tc.expected: the isFirstShow_ of preview pattern true and parentFocusable_ of menuWrapper's focus hub is true
     */
    overlayManager->ShowMenuAnimation(menuWrapperNode);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    menuWrapperPattern->StartShowAnimation();
    pipeline->taskExecutor_ = nullptr;

    auto previewPattern = previewNode->GetPattern<MenuPreviewPattern>();
    ASSERT_NE(previewPattern, nullptr);
    EXPECT_TRUE(previewPattern->isFirstShow_);
}

/**
 * @tc.name: MenuTest008
 * @tc.desc: Test OverlayManager::UpdateContextMenuDisappearPosition.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, MenuTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get overlay manager instance , set two different menu_offset.
     */
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlay = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlay, nullptr);
    overlay->ResetContextMenuDragHideFinished();
    const OffsetF menu_zero_offset(0.0, 0.0);
    const OffsetF menu_five_offset(5.0, 0.0);
    overlay->UpdateContextMenuDisappearPosition(menu_zero_offset);
    overlay->UpdateDragMoveVector(menu_five_offset);
    overlay->UpdateContextMenuDisappearPosition(MENU_OFFSET);
    /**
     * @tc.steps: step2. create menu and call UpdateContextMenuDisappearPosition.
     * @tc.expected: submenu is called
     */
    auto menuId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, menuId, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenuFirst = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto subMenuSecond = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 4, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    mainMenu->MountToParent(menuNode);
    subMenuFirst->MountToParent(menuNode);
    subMenuSecond->MountToParent(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuWrapperPattern>();
    auto rootNode = overlay->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    menuNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    auto targetId = rootNode->GetId();
    overlay->ShowMenu(targetId, MENU_OFFSET, menuNode);
    overlay->UpdateContextMenuDisappearPosition(menu_five_offset);
    EXPECT_EQ(rootNode->GetChildren().size(), 2);
    auto node = AceType::DynamicCast<FrameNode>(rootNode->GetChildren().back());
    EXPECT_EQ(node->GetTag(), V2::MENU_WRAPPER_ETS_TAG);
    overlay->HideMenu(menuNode, targetId);
}
} // namespace OHOS::Ace::NG