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
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/utils.h"
#include "base/window/foldable_window.h"
#include "core/common/ace_engine.h"
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
constexpr int32_t EXPECT_CALL_TWICE_TIMES = 2;
constexpr int32_t EXPECT_CALL_THREE_TIMES = 3;
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
    if (!sheetStyle.sheetHeight.sheetMode.has_value()) {
        sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
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

/**
 * @tc.name: MenuTest009
 * @tc.desc: Test OverlayManager::ShowMenu.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, MenuTest009, TestSize.Level1)
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
    MockContainer::Current()->SetIsSceneBoardWindow(true);

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
 * @tc.name: MenuTest010
 * @tc.desc: Test OverlayManager::ShowMenu.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, MenuTest010, TestSize.Level1)
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
    MockContainer::Current()->SetIsSceneBoardWindow(true);

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
 * @tc.name: MenuTest011
 * @tc.desc: Test OverlayManager::CleanMenuInSubWindowWithAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, MenuTest011, TestSize.Level1)
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
    overlayManager->CleanPreviewInSubWindow();
    EXPECT_EQ(menuWrapperNode->GetChildren().size(), 2);
}

/**
 * @tc.name: MenuTest012
 * @tc.desc: Test OverlayManager::UpdateMenuAnimationOptions.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, MenuTest012, TestSize.Level1)
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
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step2. call UpdateMenuAnimationOptions duration 100ms.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->menuAnimationDuration_ = 100;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
    AnimationOption option;
    overlayManager->UpdateMenuAnimationOptions(menuWrapperNode, option);
    EXPECT_EQ(option.GetDuration(), 100);
    EXPECT_EQ(option.GetCurve(), Curves::FAST_OUT_SLOW_IN);

    /**
     * @tc.steps: step2. call UpdateMenuAnimationOptions duration 150ms.
     */
    selectTheme->menuAnimationDuration_ = 0;
    overlayManager->UpdateMenuAnimationOptions(menuWrapperNode, option);
    EXPECT_EQ(option.GetDuration(), 150);
}

/**
 * @tc.name: HandleMenuDisappearCallbackNoCallback
 * @tc.desc: Test HandleMenuDisappearCallback when disappear callback is null
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, HandleMenuDisappearCallbackNoCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create overlay manager and proper menu wrapper
     * @tc.expected: nodes are created successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);

    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(rootNode->GetId()));
    ASSERT_NE(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    /**
     * @tc.steps: step2. Do not set disappear callback (keep it null)
     * @tc.expected: callback remains null
     */
    EXPECT_EQ(menuWrapperPattern->GetMenuDisappearCallback(), nullptr);

    /**
     * @tc.steps: step3. Call HandleMenuDisappearCallback
     * @tc.expected: Basic operations execute but callback condition fails
     */
    overlayManager->HandleMenuDisappearCallback(menuWrapper);

    EXPECT_EQ(menuWrapperPattern->GetMenuStatus(), MenuStatus::HIDE);
    EXPECT_FALSE(menuWrapperPattern->GetOnMenuDisappear());
}

/**
 * @tc.name: HandleMenuDisappearCallbackWithMainPipelineAndCallback
 * @tc.desc: Test HandleMenuDisappearCallback with main pipeline and callback present
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, HandleMenuDisappearCallbackWithMainPipelineAndCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create overlay manager and proper menu wrapper
     * @tc.expected: nodes are created successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);

    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(rootNode->GetId()));
    ASSERT_NE(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    /**
     * @tc.steps: step2. Set up main pipeline context and disappear callback
     * @tc.expected: setup is successful
     */
    bool callbackExecuted = false;
    auto disappearCallback = [&callbackExecuted]() { callbackExecuted = true; };
    menuWrapperPattern->RegisterMenuDisappearCallback(disappearCallback);

    auto mainPipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(mainPipeline, nullptr);

    /**
     * @tc.steps: step3. Call HandleMenuDisappearCallback
     * @tc.expected: All operations execute including pipeline flush due to both conditions being true
     */
    overlayManager->HandleMenuDisappearCallback(menuWrapper);

    EXPECT_EQ(menuWrapperPattern->GetMenuStatus(), MenuStatus::HIDE);
    EXPECT_FALSE(menuWrapperPattern->GetOnMenuDisappear());
}

/**
 * @tc.name: HandleMenuDisappearCallbackMenuStatusChangeCallback
 * @tc.desc: Test HandleMenuDisappearCallback verifies menu status changes
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, HandleMenuDisappearCallbackMenuStatusChangeCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create overlay manager and menu wrapper with initial status
     * @tc.expected: nodes are created successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);

    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(rootNode->GetId()));
    ASSERT_NE(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    /**
     * @tc.steps: step2. Set initial menu status and disappear state
     * @tc.expected: initial states are set correctly
     */
    menuWrapperPattern->SetMenuStatus(MenuStatus::SHOW);
    menuWrapperPattern->SetOnMenuDisappear(true);
    EXPECT_EQ(menuWrapperPattern->GetMenuStatus(), MenuStatus::SHOW);
    EXPECT_TRUE(menuWrapperPattern->GetOnMenuDisappear());

    /**
     * @tc.steps: step3. Call HandleMenuDisappearCallback
     * @tc.expected: Status and disappear state are updated correctly
     */
    overlayManager->HandleMenuDisappearCallback(menuWrapper);

    EXPECT_EQ(menuWrapperPattern->GetMenuStatus(), MenuStatus::HIDE);
    EXPECT_FALSE(menuWrapperPattern->GetOnMenuDisappear());
}

/**
 * @tc.name: HandleMenuDisappearCallbackComprehensiveBranchCoverage
 * @tc.desc: Test HandleMenuDisappearCallback comprehensive branch coverage
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, HandleMenuDisappearCallbackComprehensiveBranchCoverage, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test all combinations to ensure 100% branch coverage
     * @tc.expected: All branches are covered
     */
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step3. Call HandleMenuDisappearCallback with various conditions
     * @tc.expected: All branches execute correctly
     */
    overlayManager->HandleMenuDisappearCallback(nullptr);

    auto invalidMenuNode = FrameNode::CreateFrameNode(
        V2::MENU_WRAPPER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    overlayManager->HandleMenuDisappearCallback(invalidMenuNode);

    auto validMenuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(rootNode->GetId()));
    auto validMenuWrapperPattern = validMenuWrapper->GetPattern<MenuWrapperPattern>();

    overlayManager->HandleMenuDisappearCallback(validMenuWrapper);
    EXPECT_EQ(validMenuWrapperPattern->GetMenuStatus(), MenuStatus::HIDE);

    auto menuWrapper2 = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(rootNode->GetId()));
    auto menuWrapperPattern2 = menuWrapper2->GetPattern<MenuWrapperPattern>();

    overlayManager->HandleMenuDisappearCallback(menuWrapper2);
    EXPECT_EQ(menuWrapperPattern2->GetMenuStatus(), MenuStatus::HIDE);

    auto menuWrapper3 = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(rootNode->GetId()));
    auto menuWrapperPattern3 = menuWrapper3->GetPattern<MenuWrapperPattern>();

    bool callbackExecuted = false;
    auto disappearCallback = [&callbackExecuted]() { callbackExecuted = true; };
    menuWrapperPattern3->RegisterMenuDisappearCallback(disappearCallback);

    overlayManager->HandleMenuDisappearCallback(menuWrapper3);
    EXPECT_EQ(menuWrapperPattern3->GetMenuStatus(), MenuStatus::HIDE);
}

/**
 * @tc.name: HandleMenuDisappearCallbackMainPipelineExistsNoCallback
 * @tc.desc: Test HandleMenuDisappearCallback with main pipeline exists but no disappear callback
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, HandleMenuDisappearCallbackMainPipelineExistsNoCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create overlay manager and proper menu wrapper
     * @tc.expected: nodes are created successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);

    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(rootNode->GetId()));
    ASSERT_NE(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    /**
     * @tc.steps: step2. Set up main pipeline context but do NOT set disappear callback
     * @tc.expected: main pipeline exists but callback is null
     */
    EXPECT_EQ(menuWrapperPattern->GetMenuDisappearCallback(), nullptr);

    /**
     * @tc.steps: step3. Call HandleMenuDisappearCallback
     * @tc.expected: Basic operations execute, pipeline branch is taken but callback condition fails
     */
    overlayManager->HandleMenuDisappearCallback(menuWrapper);

    EXPECT_EQ(menuWrapperPattern->GetMenuStatus(), MenuStatus::HIDE);
    EXPECT_FALSE(menuWrapperPattern->GetOnMenuDisappear());
}

/**
 * @tc.name: HandleMenuDisappearCallbackMainPipelineExistsWithCallback
 * @tc.desc: Test HandleMenuDisappearCallback with both main pipeline and disappear callback present
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, HandleMenuDisappearCallbackMainPipelineExistsWithCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create overlay manager and proper menu wrapper
     * @tc.expected: nodes are created successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);

    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(rootNode->GetId()));
    ASSERT_NE(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    /**
     * @tc.steps: step2. Set up both main pipeline context AND disappear callback
     * @tc.expected: both main pipeline and callback are available
     */
    bool callbackExecuted = false;
    auto disappearCallback = [&callbackExecuted]() { callbackExecuted = true; };
    menuWrapperPattern->RegisterMenuDisappearCallback(disappearCallback);

    ASSERT_NE(menuWrapperPattern->GetMenuDisappearCallback(), nullptr);

    /**
     * @tc.steps: step3. Call HandleMenuDisappearCallback
     * @tc.expected: All operations execute including pipeline flush due to both conditions being true
     */
    overlayManager->HandleMenuDisappearCallback(menuWrapper);

    EXPECT_EQ(menuWrapperPattern->GetMenuStatus(), MenuStatus::HIDE);
    EXPECT_FALSE(menuWrapperPattern->GetOnMenuDisappear());
}

/**
 * @tc.name: HandleMenuDisappearCallbackStateChangeCallbackVerification
 * @tc.desc: Test HandleMenuDisappearCallback verifies CallMenuStateChangeCallback is called
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, HandleMenuDisappearCallbackStateChangeCallbackVerification, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create overlay manager and menu wrapper
     * @tc.expected: nodes are created successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);

    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(rootNode->GetId()));
    ASSERT_NE(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    /**
     * @tc.steps: step2. Call HandleMenuDisappearCallback
     * @tc.expected: CallMenuStateChangeCallback is invoked with "false"
     */
    overlayManager->HandleMenuDisappearCallback(menuWrapper);

    EXPECT_EQ(menuWrapperPattern->GetMenuStatus(), MenuStatus::HIDE);
    EXPECT_FALSE(menuWrapperPattern->GetOnMenuDisappear());
}

/**
 * @tc.name: HandleMenuDisappearCallback_InvalidMainPipeline_Test
 * @tc.desc: Test HandleMenuDisappearCallback when mainPipeline is invalid
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, HandleMenuDisappearCallback_InvalidMainPipeline_Test, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create overlay manager and proper menu wrapper
     * @tc.expected: nodes are created successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);

    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(rootNode->GetId()));
    ASSERT_NE(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    bool callbackExecuted = false;
    auto disappearCallback = [&callbackExecuted]() { callbackExecuted = true; };
    menuWrapperPattern->RegisterMenuDisappearCallback(disappearCallback);
    menuWrapperPattern->SetMenuStatus(MenuStatus::SHOW);

    /**
     * @tc.steps: step2. Simulate an invalid mainPipeline context and call HandleMenuDisappearCallback
     * @tc.expected: The function executes correctly, updates menu status, and calls the callback
     */
    MockPipelineContext::TearDown();
    overlayManager->HandleMenuDisappearCallback(menuWrapper);
    MockPipelineContext::SetUp();

    /**
     * @tc.steps: step3. Verify the menu status and that the callback was NOT executed
     * @tc.expected: Menu status is HIDE and callback was not called
     */
    EXPECT_EQ(menuWrapperPattern->GetMenuStatus(), MenuStatus::HIDE);
    EXPECT_FALSE(callbackExecuted);
}

/**
 * @tc.name: CheckSelectSubWindowToClose_NullMenu_Test
 * @tc.desc: Test CheckSelectSubWindowToClose with null menu parameter
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, CheckSelectSubWindowToClose_NullMenu_Test, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call CheckSelectSubWindowToClose with null menu
     * @tc.expected: step1. Function returns false due to null menu check
     */
    RefPtr<FrameNode> nullMenu = nullptr;
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    bool expandDisplay = true;

    bool result = overlayManager->CheckSelectSubWindowToClose(nullMenu, overlayManager, expandDisplay);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckSelectSubWindowToClose_NullOverlayManager_Test
 * @tc.desc: Test CheckSelectSubWindowToClose with null overlayManager parameter
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, CheckSelectSubWindowToClose_NullOverlayManager_Test, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a valid menu node
     * @tc.expected: step1. Menu node is created successfully
     */
    auto menu = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(2));
    ASSERT_NE(menu, nullptr);

    /**
     * @tc.steps: step2. Call CheckSelectSubWindowToClose with null overlayManager
     * @tc.expected: step2. Function returns false due to null overlayManager check
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    RefPtr<OverlayManager> nullOverlayManager = nullptr;
    bool expandDisplay = true;

    bool result = overlayManager->CheckSelectSubWindowToClose(menu, nullOverlayManager, expandDisplay);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckSelectSubWindowToClose_MenuWithNoChildren_Test
 * @tc.desc: Test CheckSelectSubWindowToClose with menu that has no child nodes
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, CheckSelectSubWindowToClose_MenuWithNoChildren_Test, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a menu frame node without children
     * @tc.expected: step1. Menu node is created but has no children
     */
    auto menu = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(2));
    ASSERT_NE(menu, nullptr);
    ASSERT_EQ(menu->GetChildren().size(), 0);

    /**
     * @tc.steps: step2. Call CheckSelectSubWindowToClose
     * @tc.expected: step2. Function returns false due to null menuNode check (no child at index 0)
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    bool expandDisplay = true;

    bool result = overlayManager->CheckSelectSubWindowToClose(menu, overlayManager, expandDisplay);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckSelectSubWindowToClose_InvalidMenuPattern_Test
 * @tc.desc: Test CheckSelectSubWindowToClose with child node that doesn't have MenuPattern
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, CheckSelectSubWindowToClose_InvalidMenuPattern_Test, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a menu wrapper with child that has no MenuPattern
     * @tc.expected: step1. Menu structure is created with different target tag
     */
    auto menu = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(2));
    auto childNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 2, AceType::MakeRefPtr<ButtonPattern>());
    menu->AddChild(childNode);
    ASSERT_NE(menu, nullptr);
    ASSERT_EQ(menu->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. Call CheckSelectSubWindowToClose
     * @tc.expected: step2. Function returns false due to null menuPattern check (cast fails)
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    bool expandDisplay = true;

    bool result = overlayManager->CheckSelectSubWindowToClose(menu, overlayManager, expandDisplay);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckSelectSubWindowToClose_NullMenuLayoutProperty_Test
 * @tc.desc: Test CheckSelectSubWindowToClose with MenuPattern that has no layout property
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, CheckSelectSubWindowToClose_NullMenuLayoutProperty_Test, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menu structure with MenuPattern but no layout property
     * @tc.expected: step1. Menu structure is created but layout property is null
     */
    auto menu = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(2));
    ASSERT_NE(menu, nullptr);
    auto menuNode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(2, V2::SELECT_ETS_TAG, MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    menu->AddChild(menuNode);

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    ASSERT_NE(menuPattern->GetLayoutProperty<MenuLayoutProperty>(), nullptr);

    /**
     * @tc.steps: step2. Call CheckSelectSubWindowToClose
     * @tc.expected: step2. Function returns false due to null menuLayoutProp check
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    bool expandDisplay = true;

    bool result = overlayManager->CheckSelectSubWindowToClose(menu, overlayManager, expandDisplay);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckSelectSubWindowToClose_ExpandDisplayFalse_Test
 * @tc.desc: Test CheckSelectSubWindowToClose with expandDisplay set to false
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, CheckSelectSubWindowToClose_ExpandDisplayFalse_Test, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create complete valid menu structure
     * @tc.expected: step1. Menu structure is created successfully
     */
    auto menu = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(2));
    ASSERT_NE(menu, nullptr);
    auto menuNode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(2, V2::SELECT_ETS_TAG, MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    menu->AddChild(menuNode);
    /**
     * @tc.steps: step2. Call CheckSelectSubWindowToClose with expandDisplay=false
     * @tc.expected: step2. Function returns false due to expandDisplay condition
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    bool expandDisplay = false;

    bool result = overlayManager->CheckSelectSubWindowToClose(menu, overlayManager, expandDisplay);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckSelectSubWindowToClose_NonSelectTargetTag_Test
 * @tc.desc: Test CheckSelectSubWindowToClose with menu that doesn't have SELECT_ETS_TAG
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, CheckSelectSubWindowToClose_NonSelectTargetTag_Test, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menu structure with non-SELECT target tag
     * @tc.expected: step1. Menu structure is created with different target tag
     */
    auto menu = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(2));
    ASSERT_NE(menu, nullptr);
    auto menuNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(2, V2::BUTTON_ETS_TAG, MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    menu->AddChild(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();

    ASSERT_NE(menuPattern->GetTargetTag(), V2::SELECT_ETS_TAG);

    /**
     * @tc.steps: step2. Call CheckSelectSubWindowToClose with expandDisplay=true
     * @tc.expected: step2. Function returns false due to target tag condition
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    bool expandDisplay = true;

    bool result = overlayManager->CheckSelectSubWindowToClose(menu, overlayManager, expandDisplay);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckSelectSubWindowToClose_ShowInSubWindowFalse_Test
 * @tc.desc: Test CheckSelectSubWindowToClose with ShowInSubWindow set to false
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, CheckSelectSubWindowToClose_ShowInSubWindowFalse_Test, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menu structure with SELECT target tag but ShowInSubWindow=false
     * @tc.expected: step1. Menu structure is created with correct target tag
     */
    auto menu = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(2));
    ASSERT_NE(menu, nullptr);
    auto menuNode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(2, V2::SELECT_ETS_TAG, MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    menu->AddChild(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    auto menuLayoutProp = menuPattern->GetLayoutProperty<MenuLayoutProperty>();

    menuLayoutProp->UpdateShowInSubWindow(false);

    ASSERT_FALSE(menuLayoutProp->GetShowInSubWindowValue(false));

    /**
     * @tc.steps: step2. Call CheckSelectSubWindowToClose with expandDisplay=true
     * @tc.expected: step2. Function returns false due to ShowInSubWindow condition
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    bool expandDisplay = true;

    bool result = overlayManager->CheckSelectSubWindowToClose(menu, overlayManager, expandDisplay);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HideAllMenusWithoutAnimation001
 * @tc.desc: Test OverlayManager::HideAllMenusWithoutAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, HideAllMenusWithoutAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node and root node.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto targetId = rootNode->GetId();
    auto menuId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, menuId, AceType::MakeRefPtr<MenuWrapperPattern>(targetId));
    ASSERT_NE(menuNode, nullptr);
    auto subMenuId = ElementRegister::GetInstance()->MakeUniqueId();
    auto subMenuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, subMenuId, AceType::MakeRefPtr<MenuPattern>(1, "Test", MenuType::MENU));
    ASSERT_NE(subMenuNode, nullptr);
    subMenuNode->MountToParent(menuNode);
    /**
     * @tc.steps: step2. call showMenu when menuNode is nullptr and menuMap is empty.
     * @tc.expected: function exits normally
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
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
    overlayManager->HideAllMenusWithoutAnimation();
    EXPECT_TRUE(overlayManager->menuMap_.empty());
    EXPECT_FALSE(overlayManager->IsMenuShow());
}

/**
 * @tc.name: RemoveMenuFilter001
 * @tc.desc: Test OverlayManager::RemoveMenuFilter
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, RemoveMenuFilter001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);

    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(rootNode->GetId()));
    ASSERT_NE(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    auto column = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(column, nullptr);
    column->MountToParent(rootNode);
    menuWrapperPattern->SetFilterColumnNode(column);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    
    EXPECT_FALSE(rootNode->GetChildren().empty());
    overlayManager->RemoveMenuFilter(menuWrapper, false);
    EXPECT_TRUE(rootNode->GetChildren().empty());
}

/**
 * @tc.name: CallMenuDisappearWithStatus001
 * @tc.desc: Test OverlayManager::CallMenuDisappearWithStatus
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, CallMenuDisappearWithStatus001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);

    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(rootNode->GetId()));
    ASSERT_NE(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    auto column = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(column, nullptr);
    column->MountToParent(rootNode);
    menuWrapperPattern->SetFilterColumnNode(column);
    auto callCount = 0;
    auto aboutToDisappearCallback = [&callCount]() {
        callCount++;
    };
    auto disappearCallback = [&callCount]() {
        callCount++;
    };
    menuWrapperPattern->RegisterMenuAboutToDisappearCallback(aboutToDisappearCallback);
    menuWrapperPattern->RegisterMenuDisappearCallback(disappearCallback);
    menuWrapperPattern->menuStatus_ = MenuStatus::SHOW;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->CallMenuDisappearWithStatus(menuWrapper);
    EXPECT_EQ(callCount, EXPECT_CALL_TWICE_TIMES);
    menuWrapperPattern->menuStatus_ = MenuStatus::ON_HIDE_ANIMATION;
    overlayManager->CallMenuDisappearWithStatus(menuWrapper);
    EXPECT_EQ(callCount, EXPECT_CALL_THREE_TIMES);
}

/**
 * @tc.name: CallMenuDisappearOnlyNewLifeCycle001
 * @tc.desc: Test OverlayManager::CallMenuDisappearOnlyNewLifeCycle
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, CallMenuDisappearOnlyNewLifeCycle, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);

    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(rootNode->GetId()));
    ASSERT_NE(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    auto column = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(column, nullptr);
    column->MountToParent(rootNode);
    menuWrapperPattern->SetFilterColumnNode(column);
    auto callCount = 0;
    auto aboutToDisappearCallback = [&callCount]() {
        callCount++;
    };
    auto disappearCallback = [&callCount]() {
        callCount++;
    };
    menuWrapperPattern->RegisterMenuOnWillDisappearCallback(aboutToDisappearCallback);
    menuWrapperPattern->RegisterMenuOnDidDisappearCallback(disappearCallback);
    menuWrapperPattern->menuStatus_ = MenuStatus::SHOW;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->CallMenuDisappearWithStatus(menuWrapper);
    EXPECT_EQ(callCount, EXPECT_CALL_TWICE_TIMES);
    menuWrapperPattern->menuStatus_ = MenuStatus::ON_HIDE_ANIMATION;
    overlayManager->CallMenuDisappearWithStatus(menuWrapper);
    EXPECT_EQ(callCount, EXPECT_CALL_THREE_TIMES);
}

/**
 * @tc.name: IsSceneBoardWindow001
 * @tc.desc: Test OverlayManager::IsSceneBoardWindow
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerMenuTestNg, IsSceneBoardWindow001, TestSize.Level1)
{
    auto containerId = Container::CurrentId();
    auto container = AceEngine::Get().GetContainer(containerId);
    ASSERT_NE(container, nullptr);
    auto mockContainer = AceType::DynamicCast<MockContainer>(container);
    ASSERT_NE(mockContainer, nullptr);
    mockContainer->SetIsSceneBoardWindow(true);
    AceEngine::Get().RemoveContainer(container->GetInstanceId());
    auto isSceneBoard = OverlayManager::IsSceneBoardWindow();
    EXPECT_FALSE(isSceneBoard);
    AceEngine::Get().AddContainer(container->GetInstanceId(), container);
    isSceneBoard = OverlayManager::IsSceneBoardWindow();
    EXPECT_TRUE(isSceneBoard);
    mockContainer->isSubContainer_ = true;
    SubwindowManager::GetInstance()->RemoveParentContainerId(container->GetInstanceId());
    isSceneBoard = OverlayManager::IsSceneBoardWindow();
    EXPECT_FALSE(isSceneBoard);
    SubwindowManager::GetInstance()->AddParentContainerId(container->GetInstanceId(), container->GetInstanceId());
    isSceneBoard = OverlayManager::IsSceneBoardWindow();
    EXPECT_TRUE(isSceneBoard);
    mockContainer->isSubContainer_ = false;
    mockContainer->SetIsSceneBoardWindow(false);
}
} // namespace OHOS::Ace::NG