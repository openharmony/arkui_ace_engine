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

/**
 * @file container_modal_toolbar_layout_test_ng.cpp
 * @brief 工具栏布局调整测试用例
 *
 * 本文件包含 UpdateTitleLayout、AdjustTitleNodeWidth、AdjustNavbarRowWidth、
 * AdjustNavDestRowWidth 等布局调整相关测试用例。
 */

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/frameworks/core/common/mock_resource_adapter.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/log/log_wrapper.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/container_modal/container_modal_toolbar.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/toolbaritem/toolbaritem_model_ng.h"
#include "core/components_ng/pattern/toolbaritem/toolbar_row_pattern.h"
#include "core/components_ng/pattern/toolbaritem/toolbaritem_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float TITLE_ITEM_HEIGT_S = 56.0;
constexpr float TITLE_ITEM_HEIGT_M = 64.0;
constexpr float TITLE_ITEM_HEIGT_L = 72.0;
const uint32_t VALUE = 0;

struct PageNodeAndWidth {
    RefPtr<UINode> node;
    float width;
};
} // namespace

class ContainerModelToolBarTestNg : public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateTitleMgr();
    void GetInstance();
    RefPtr<FrameNode> CreateContent();
    void SetMockWindow(WindowMode windowMode);
    void CreateContainerModal();
    void CreateEmptyPage();
    void CreatePageWithSideBarOnly();
    void CreatePageWithNavigationOnly();
    void CreatePageWithNavDestOnly();
    void CreatePageWithAllNodes();
    PageNodeAndWidth GetPageNodeAndWidth();
    RefPtr<FrameNode> frameNode_;
    RefPtr<ContainerModalPattern> pattern_;
    RefPtr<LayoutProperty> layoutProperty_;
    RefPtr<ContainerModalAccessibilityProperty> accessibilityProperty_;
    RefPtr<ContainerModalToolBar> titleMgr_;
    RefPtr<ContainerModalToolBar> floatTitleMgr_;
};

void ContainerModelToolBarTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_CONTAINER_MODAL);
    auto containerModalTheme = ContainerModalTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(containerModalTheme));
    EXPECT_CALL(*themeManager, GetThemeConstants()).WillRepeatedly(Return(themeConstants));
}

void ContainerModelToolBarTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ContainerModelToolBarTestNg::SetUp()
{
    SetMockWindow(WindowMode::WINDOW_MODE_FULLSCREEN);
}

void ContainerModelToolBarTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    titleMgr_ = nullptr;
    floatTitleMgr_ = nullptr;
}

void ContainerModelToolBarTestNg::CreateTitleMgr()
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("frameNode", 0, AceType::MakeRefPtr<Pattern>());
    pattern_->SetToolbarBuilder(frameNode, nullptr);
    titleMgr_ = pattern_->titleMgr_;
    floatTitleMgr_ = pattern_->floatTitleMgr_;
}

void ContainerModelToolBarTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ContainerModalPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ContainerModalAccessibilityProperty>();
}

RefPtr<FrameNode> ContainerModelToolBarTestNg::CreateContent()
{
    return AceType::MakeRefPtr<FrameNode>("stage", 0, AceType::MakeRefPtr<Pattern>());
}

void ContainerModelToolBarTestNg::SetMockWindow(WindowMode windowMode)
{
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowModeCallback = [windowMode]() { return windowMode; };
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
}

void ContainerModelToolBarTestNg::CreateContainerModal()
{
    ContainerModalView view;
    RefPtr<FrameNode> content = CreateContent();
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    content->AddChild(pageNode);
    auto frameNode = view.Create(content);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    GetInstance();
    CreateTitleMgr();
    FlushUITasks(frameNode_);
}

void ContainerModelToolBarTestNg::CreateEmptyPage()
{
    ASSERT_NE(pattern_, nullptr);
    auto stackNode = pattern_->GetStackNode();
    ASSERT_NE(stackNode, nullptr);
    auto stage = FrameNode::CreateFrameNode(
        "stage", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto page = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    stage->AddChild(page, 0);
    stackNode->AddChild(stage, 0);
}

void ContainerModelToolBarTestNg::CreatePageWithSideBarOnly()
{
    ASSERT_NE(pattern_, nullptr);
    auto stackNode = pattern_->GetStackNode();
    ASSERT_NE(stackNode, nullptr);
    auto stage = FrameNode::CreateFrameNode(
        "stack", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto page = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto sideBarNode = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    page->AddChild(sideBarNode);
    stage->AddChild(page, 0);
    stackNode->AddChild(stage, 0);
}

void ContainerModelToolBarTestNg::CreatePageWithNavigationOnly()
{
    ASSERT_NE(pattern_, nullptr);
    auto stackNode = pattern_->GetStackNode();
    ASSERT_NE(stackNode, nullptr);
    auto stage = FrameNode::CreateFrameNode(
        "stack", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto page = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto navigationNode = FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavigationPattern>());
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationMode(NavigationMode::SPLIT);
    auto navbarNode = FrameNode::CreateFrameNode(
        V2::NAVBAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->AddChild(navbarNode);
    auto navDestContentNode = FrameNode::CreateFrameNode(
        "navDestContentNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto navDestNode = FrameNode::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navDestContentNode->AddChild(navDestNode);
    navigationNode->AddChild(navDestContentNode);
    page->AddChild(navigationNode);
    stage->AddChild(page, 0);
    stackNode->AddChild(stage, 0);
}

void ContainerModelToolBarTestNg::CreatePageWithNavDestOnly()
{
    ASSERT_NE(pattern_, nullptr);
    auto stackNode = pattern_->GetStackNode();
    ASSERT_NE(stackNode, nullptr);
    auto stage = FrameNode::CreateFrameNode(
        "stack", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto page = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto navigationNode = FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavigationPattern>());
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationMode(NavigationMode::SPLIT);
    auto navDestContentNode = FrameNode::CreateFrameNode(
        "navDestContentNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto navDestNode = FrameNode::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navDestContentNode->AddChild(navDestNode);
    navigationNode->AddChild(navDestContentNode);
    page->AddChild(navigationNode);
    stage->AddChild(page, 0);
    stackNode->AddChild(stage, 0);
}

void ContainerModelToolBarTestNg::CreatePageWithAllNodes()
{
    ASSERT_NE(pattern_, nullptr);
    auto stackNode = pattern_->GetStackNode();
    ASSERT_NE(stackNode, nullptr);
    auto stage = FrameNode::CreateFrameNode(
        "stage", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto page = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto navigationNode = FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavigationPattern>());
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationMode(NavigationMode::SPLIT);
    auto navbarNode = FrameNode::CreateFrameNode(
        V2::NAVBAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->AddChild(navbarNode);
    auto navDestContentNode = FrameNode::CreateFrameNode(
        "navDestContentNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto navDestNode = FrameNode::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navDestContentNode->AddChild(navDestNode);
    navigationNode->AddChild(navDestContentNode);
    auto sideBarNode = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    sideBarNode->AddChild(navigationNode);
    page->AddChild(sideBarNode);
    stage->AddChild(page, 0);
    stackNode->AddChild(stage, 0);
}

PageNodeAndWidth ContainerModelToolBarTestNg::GetPageNodeAndWidth()
{
    PageNodeAndWidth ret { nullptr, 0 };
    CHECK_NULL_RETURN(pattern_, ret);
    auto stackNode = pattern_->GetStackNode();
    CHECK_NULL_RETURN(stackNode, ret);
    auto stage = stackNode->GetFirstChild();
    CHECK_NULL_RETURN(stage, ret);
    auto page = stage->GetFirstChild();
    CHECK_NULL_RETURN(page, ret);
    auto pageNode = AceType::DynamicCast<FrameNode>(page);
    CHECK_NULL_RETURN(pageNode, ret);
    auto pageGeometryNode = pageNode->GetGeometryNode();
    CHECK_NULL_RETURN(pageGeometryNode, ret);
    auto pageWidth = pageGeometryNode->GetFrameSize().Width();
    ret.node = page;
    ret.width = pageWidth;
    return ret;
}

/**
 * @tc.name: UpdateTitleLayout_001
 * @tc.desc: 测试 UpdateTitleLayout 方法 - 基本场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateTitleLayout_001, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 设置工具栏信息
    ToolbarInfo sideBarInfo_ = { true, 200.0f };
    ToolbarInfo sideBarDividerInfo_ = { true, 20.0f };
    ToolbarInfo navBarInfo_ = { true, 500.0f };
    ToolbarInfo navBarDividerInfo_ = { true, 10.0f };
    ToolbarInfo navDestInfo_ = { true, 1200.0f };

    titleMgr_->toolbarManager_->SetSideBarDividerInfo(sideBarDividerInfo_);
    titleMgr_->toolbarManager_->SetSideBarInfo(sideBarInfo_);
    titleMgr_->toolbarManager_->SetHasNavBar(true);
    titleMgr_->toolbarManager_->SetNavBarInfo(navBarInfo_);
    titleMgr_->toolbarManager_->SetNavBarDividerInfo(navBarDividerInfo_);
    titleMgr_->toolbarManager_->SetHasNavDest(true);
    titleMgr_->toolbarManager_->SetNavDestInfo(navDestInfo_);
    titleMgr_->hasNavOrSideBarNodes_ = true;

    // 测试有效输入：创建父节点和工具栏项
    auto parentNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto toolbarItem =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 2, AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem);

    // 测试添加和移除工具栏项到不同位置
    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_START, toolbarItem);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem);
    titleMgr_->RemoveToolbarItem(parentNode);
    titleMgr_->UpdateTitleLayout();

    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_END, toolbarItem);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem);
    titleMgr_->RemoveToolbarItem(parentNode);
    titleMgr_->UpdateTitleLayout();

    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAVDEST_START, toolbarItem);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem);
    titleMgr_->RemoveToolbarItem(parentNode);
    titleMgr_->UpdateTitleLayout();

    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAVDEST_END, toolbarItem);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem);
    titleMgr_->RemoveToolbarItem(parentNode);
    titleMgr_->UpdateTitleLayout();

    titleMgr_->isTitleShow_ = true;
    titleMgr_->customTitleShow_ = false;
    titleMgr_->UpdateTitleLayout();
    EXPECT_DOUBLE_EQ(titleMgr_->toolbarItemMaxHeight_, 0.0f);
}

/**
 * @tc.name: UpdateTitleLayout_002
 * @tc.desc: 测试 UpdateTitleLayout 方法 - 显示状态组合场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateTitleLayout_002, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 设置工具栏信息
    ToolbarInfo sideBarInfo_ = { true, 200.0f };
    ToolbarInfo sideBarDividerInfo_ = { true, 20.0f };
    ToolbarInfo navBarInfo_ = { true, 500.0f };
    ToolbarInfo navBarDividerInfo_ = { true, 10.0f };
    ToolbarInfo navDestInfo_ = { true, 1200.0f };

    titleMgr_->toolbarManager_->SetSideBarDividerInfo(sideBarDividerInfo_);
    titleMgr_->toolbarManager_->SetSideBarInfo(sideBarInfo_);
    titleMgr_->toolbarManager_->SetHasNavBar(true);
    titleMgr_->toolbarManager_->SetNavBarInfo(navBarInfo_);
    titleMgr_->toolbarManager_->SetNavBarDividerInfo(navBarDividerInfo_);
    titleMgr_->toolbarManager_->SetHasNavDest(true);
    titleMgr_->toolbarManager_->SetNavDestInfo(navDestInfo_);

    // 创建父节点和工具栏项
    auto parentNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto toolbarItem =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 2, AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem);

    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_START, toolbarItem);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem);

    // 测试不同的显示状态组合
    titleMgr_->hasNavOrSideBarNodes_ = true;
    titleMgr_->isTitleShow_ = true;
    titleMgr_->customTitleShow_ = true;
    titleMgr_->UpdateTitleLayout();

    titleMgr_->hasNavOrSideBarNodes_ = false;
    titleMgr_->isTitleShow_ = true;
    titleMgr_->customTitleShow_ = false;
    titleMgr_->UpdateTitleLayout();

    titleMgr_->hasNavOrSideBarNodes_ = true;
    titleMgr_->isTitleShow_ = false;
    titleMgr_->customTitleShow_ = true;
    titleMgr_->UpdateTitleLayout();

    titleMgr_->hasNavOrSideBarNodes_ = true;
    titleMgr_->isTitleShow_ = false;
    titleMgr_->customTitleShow_ = false;
    titleMgr_->UpdateTitleLayout();
    EXPECT_DOUBLE_EQ(titleMgr_->toolbarItemMaxHeight_, 0.0f);
}

/**
 * @tc.name: UpdateToolbarShow
 * @tc.desc: 测试 UpdateToolbarShow 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateToolbarShow, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 测试不同的工具栏显示状态
    titleMgr_->UpdateToolbarShow(true, true);
    EXPECT_TRUE(titleMgr_->isTitleShow_);

    titleMgr_->UpdateToolbarShow(true, false);
    EXPECT_FALSE(titleMgr_->customTitleShow_);

    titleMgr_->UpdateToolbarShow(false, true);
    EXPECT_TRUE(titleMgr_->customTitleShow_);

    titleMgr_->UpdateToolbarShow(false, false);
    EXPECT_FALSE(titleMgr_->isTitleShow_);
}

/**
 * @tc.name: AdjustTitleNodeWidth_001
 * @tc.desc: 测试 AdjustTitleNodeWidth 方法 - 有工具栏项场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustTitleNodeWidth_001, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 设置侧边栏信息
    ToolbarInfo sideBarInfo_ = { true, 200.0f };
    ToolbarInfo sideBarDividerInfo_ = { true, 20.0f };

    titleMgr_->toolbarManager_->SetSideBarDividerInfo(sideBarDividerInfo_);
    titleMgr_->toolbarManager_->SetSideBarInfo(sideBarInfo_);

    auto customTitleRow = pattern_->GetCustomTitleRow();
    ASSERT_NE(customTitleRow, nullptr);

    // 创建父节点和工具栏项
    auto parentNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto toolbarItem =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 2, AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem);
    titleMgr_->AdjustTitleNodeWidth();

    // 检查标题节点宽度
    auto titleNode = AceType::DynamicCast<FrameNode>(customTitleRow->GetChildren().front());
    ASSERT_NE(titleNode, nullptr);
    LayoutConstraintF titleNodeconstraint;
    titleNode->Measure(titleNodeconstraint);
    float titleNodeWidth = sideBarInfo_.isShow ? sideBarInfo_.width : 0;
    auto titleNode2 = titleNode->GetGeometryNode();
    ASSERT_NE(titleNode2, nullptr);
    EXPECT_EQ(titleNode2->GetFrameSize().Width(), titleNodeWidth);
}

/**
 * @tc.name: AdjustTitleNodeWidth_002
 * @tc.desc: 测试 AdjustTitleNodeWidth 方法 - 无工具栏项场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustTitleNodeWidth_002, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 设置侧边栏信息
    ToolbarInfo sideBarInfo_ = { true, 200.0f };
    ToolbarInfo sideBarDividerInfo_ = { true, 20.0f };

    titleMgr_->toolbarManager_->SetSideBarDividerInfo(sideBarDividerInfo_);
    titleMgr_->toolbarManager_->SetSideBarInfo(sideBarInfo_);

    auto customTitleRow = pattern_->GetCustomTitleRow();
    ASSERT_NE(customTitleRow, nullptr);

    // 调整标题节点宽度（无工具栏项）
    titleMgr_->AdjustTitleNodeWidth();

    // 检查标题节点宽度
    auto titleNode = AceType::DynamicCast<FrameNode>(customTitleRow->GetChildren().front());
    ASSERT_NE(titleNode, nullptr);
    LayoutConstraintF titleNodeconstraint;
    titleNode->Measure(titleNodeconstraint);
    auto titleNode2 = titleNode->GetGeometryNode();
    ASSERT_NE(titleNode2, nullptr);
    EXPECT_EQ(titleNode2->GetFrameSize().Width(), 0.0f);
}

} // namespace OHOS::Ace::NG
