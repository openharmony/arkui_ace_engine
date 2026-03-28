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
 * @file container_modal_toolbar_add_test_ng.cpp
 * @brief 工具栏项添加到行测试用例
 *
 * 本文件包含 AddToolbarItemToRow、AddToolbarItemToNavBarStart、AddToolbarItemToNavBarEnd、
 * AddToolbarItemToNavDestStart、AddToolbarItemToNavDestEnd 等相关测试用例。
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
 * @tc.name: AddToolbarItemToRow_001
 * @tc.desc: 测试 AddToolbarItemToRow 方法 - 无效输入场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, AddToolbarItemToRow_001, TestSize.Level1)
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
    titleMgr_->toolbarManager_->SetNavBarInfo(navBarInfo_);
    titleMgr_->toolbarManager_->SetNavBarDividerInfo(navBarDividerInfo_);
    titleMgr_->toolbarManager_->SetNavDestInfo(navDestInfo_);

    // 测试无效输入：null 指针
    bool result1 = titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_START, nullptr);
    EXPECT_FALSE(result1);
    bool result2 = titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAVDEST_START, nullptr);
    EXPECT_FALSE(result2);

    // 创建工具栏项
    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());

    // 测试无效输入：NONE 类型
    bool result3 = titleMgr_->AddToolbarItemToRow(ItemPlacementType::NONE, toolbarItem);
    EXPECT_FALSE(result3);

    // 测试无效输入：无导航栏时添加到导航栏
    titleMgr_->toolbarManager_->SetHasNavBar(false);
    bool result4 = titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_START, toolbarItem);
    EXPECT_FALSE(result4);
    bool result5 = titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_END, toolbarItem);
    EXPECT_FALSE(result5);

    // 测试无效输入：无导航目的地时添加到导航目的地
    titleMgr_->toolbarManager_->SetHasNavDest(false);
    bool result6 = titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAVDEST_START, toolbarItem);
    EXPECT_FALSE(result6);
    bool result7 = titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAVDEST_END, toolbarItem);
    EXPECT_FALSE(result7);
}

/**
 * @tc.name: AddToolbarItemToRow_002
 * @tc.desc: 测试 AddToolbarItemToRow 方法 - 有效输入场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, AddToolbarItemToRow_002, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    auto customTitleRow = pattern_->GetCustomTitleRow();
    ASSERT_NE(customTitleRow, nullptr);

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

    // 创建工具栏项并添加到各个位置
    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());

    // 测试添加到导航栏起始位置
    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_START, toolbarItem);
    EXPECT_EQ(titleMgr_->leftNavRow_->GetChildren().size(), 1);

    // 测试添加到导航栏结束位置
    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_END, toolbarItem);
    EXPECT_EQ(titleMgr_->rightNavRow_->GetChildren().size(), 1);

    // 测试添加到导航目的地起始位置
    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAVDEST_START, toolbarItem);
    EXPECT_EQ(titleMgr_->leftNavDestRow_->GetChildren().size(), 1);

    // 测试添加到导航目的地结束位置
    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAVDEST_END, toolbarItem);
    EXPECT_EQ(titleMgr_->rightNavDestRow_->GetChildren().size(), 1);
}

/**
 * @tc.name: AddToolbarItemToSpecificRow
 * @tc.desc: 测试 AddToolbarItemToSpecificRow 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, AddToolbarItemToSpecificRow, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 设置导航目的地信息
    ToolbarInfo navDestInfo_ = { true, 1200.0f };
    titleMgr_->toolbarManager_->SetNavDestInfo(navDestInfo_);

    // 创建工具栏项
    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());

    // 测试基本添加
    titleMgr_->AddToolbarItemToSpecificRow(ItemPlacementType::NAVDEST_START, toolbarItem);
    EXPECT_EQ(titleMgr_->leftNavDestRow_->GetChildren().size(), 1);

    // 测试标题显示状态变化时的添加
    titleMgr_->isTitleShow_ = true;
    titleMgr_->customTitleShow_ = false;
    titleMgr_->AddToolbarItemToSpecificRow(ItemPlacementType::NAVDEST_START, toolbarItem);
    EXPECT_EQ(titleMgr_->leftNavDestRow_->GetChildren().size(), 1);

    titleMgr_->isTitleShow_ = true;
    titleMgr_->customTitleShow_ = true;
    titleMgr_->AddToolbarItemToSpecificRow(ItemPlacementType::NAVDEST_START, toolbarItem);
    EXPECT_EQ(titleMgr_->leftNavDestRow_->GetChildren().size(), 1);

    titleMgr_->isTitleShow_ = false;
    titleMgr_->customTitleShow_ = false;
    titleMgr_->AddToolbarItemToSpecificRow(ItemPlacementType::NAVDEST_START, toolbarItem);
    EXPECT_EQ(titleMgr_->leftNavDestRow_->GetChildren().size(), 1);

    titleMgr_->isTitleShow_ = false;
    titleMgr_->customTitleShow_ = true;
    titleMgr_->AddToolbarItemToSpecificRow(ItemPlacementType::NAVDEST_START, toolbarItem);
    EXPECT_EQ(titleMgr_->leftNavDestRow_->GetChildren().size(), 1);
}

/**
 * @tc.name: AddToolbarItemToNavBarStart
 * @tc.desc: 测试 AddToolbarItemToNavBarStart 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, AddToolbarItemToNavBarStart, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 设置有导航栏
    titleMgr_->toolbarManager_->SetHasNavBar(true);

    // 创建第一个工具栏项并添加到导航栏起始位置
    auto toolbarItem1 = FrameNode::CreateFrameNode(
        "toolbarItem1", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavBarStart(toolbarItem1);
    EXPECT_EQ(titleMgr_->leftNavRow_->GetChildren().size(), 1);

    // 创建第二个工具栏项并添加到导航栏起始位置
    auto toolbarItem2 = FrameNode::CreateFrameNode(
        "toolbarItem2", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavBarStart(toolbarItem2);
    EXPECT_EQ(titleMgr_->leftNavRow_->GetChildren().size(), 2);
}

/**
 * @tc.name: AddToolbarItemToNavBarEnd
 * @tc.desc: 测试 AddToolbarItemToNavBarEnd 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, AddToolbarItemToNavBarEnd, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 设置有导航栏
    titleMgr_->toolbarManager_->SetHasNavBar(true);

    // 创建第一个工具栏项并添加到导航栏结束位置
    auto toolbarItem1 = FrameNode::CreateFrameNode(
        "toolbarItem", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavBarEnd(toolbarItem1);
    EXPECT_EQ(titleMgr_->rightNavRow_->GetChildren().size(), 1);

    // 创建第二个工具栏项并添加到导航栏结束位置
    auto toolbarItem2 = FrameNode::CreateFrameNode(
        "toolbarItem2", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavBarEnd(toolbarItem2);
    EXPECT_EQ(titleMgr_->rightNavRow_->GetChildren().size(), 2);
}

/**
 * @tc.name: AddToolbarItemToNavDestStart
 * @tc.desc: 测试 AddToolbarItemToNavDestStart 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, AddToolbarItemToNavDestStart, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 设置有导航目的地
    titleMgr_->toolbarManager_->SetHasNavDest(true);

    // 创建第一个工具栏项并添加到导航目的地起始位置
    auto toolbarItem1 = FrameNode::CreateFrameNode(
        "toolbarItem1", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavDestStart(toolbarItem1);
    EXPECT_EQ(titleMgr_->leftNavDestRow_->GetChildren().size(), 1);

    // 创建第二个工具栏项并添加到导航目的地起始位置
    auto toolbarItem2 = FrameNode::CreateFrameNode(
        "toolbarItem2", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavDestStart(toolbarItem2);
    EXPECT_EQ(titleMgr_->leftNavDestRow_->GetChildren().size(), 2);
}

/**
 * @tc.name: AddToolbarItemToNavDestEnd
 * @tc.desc: 测试 AddToolbarItemToNavDestEnd 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, AddToolbarItemToNavDestEnd, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 设置有导航目的地
    titleMgr_->toolbarManager_->SetHasNavDest(true);

    // 创建第一个工具栏项并添加到导航目的地结束位置
    auto toolbarItem1 = FrameNode::CreateFrameNode(
        "toolbarItem1", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavDestEnd(toolbarItem1);
    EXPECT_EQ(titleMgr_->rightNavDestRow_->GetChildren().size(), 1);

    // 创建第二个工具栏项并添加到导航目的地结束位置
    auto toolbarItem2 = FrameNode::CreateFrameNode(
        "toolbarItem2", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavDestEnd(toolbarItem2);
    EXPECT_EQ(titleMgr_->rightNavDestRow_->GetChildren().size(), 2);
}

} // namespace OHOS::Ace::NG
