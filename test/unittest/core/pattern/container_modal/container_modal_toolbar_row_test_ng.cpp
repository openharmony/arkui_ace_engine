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
 * @file container_modal_toolbar_row_test_ng.cpp
 * @brief 工具栏行添加和移除测试用例
 *
 * 本文件包含 AddNavBarRow、AddNavDestBarRow、RemoveToolbarRowContainers、
 * OnToolBarLayoutChange 等工具栏行管理相关测试用例。
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
 * @tc.name: AddNavBarRow_001
 * @tc.desc: 测试 AddNavBarRow 方法 - 基本场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, AddNavBarRow_001, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 设置有导航栏
    titleMgr_->toolbarManager_->SetHasNavBar(true);

    // 添加导航栏行并验证
    ToolbarInfo navBarInfo_ = { false, 500.0f };
    titleMgr_->toolbarManager_->SetNavBarInfo(navBarInfo_);
    EXPECT_EQ(navBarInfo_.isShow, false);
    titleMgr_->AddNavBarRow();
    EXPECT_EQ(titleMgr_->navbarRow_, nullptr);

    // 设置导航栏显示状态为true
    navBarInfo_ = { true, 500.0f };
    titleMgr_->toolbarManager_->SetNavBarInfo(navBarInfo_);
    EXPECT_EQ(navBarInfo_.isShow, true);
    titleMgr_->AddNavBarRow();
    ASSERT_NE(titleMgr_->navbarRow_, nullptr);
    EXPECT_EQ(titleMgr_->navbarRow_->GetChildren().size(), 0);

    // 添加左侧导航栏行
    EXPECT_EQ(titleMgr_->leftNavRow_, nullptr);
    titleMgr_->AddLeftNavRow();
    ASSERT_NE(titleMgr_->leftNavRow_, nullptr);
    EXPECT_EQ(titleMgr_->navbarRow_->GetChildren().size(), 1);
    titleMgr_->AddLeftNavRow();
    ASSERT_NE(titleMgr_->leftNavRow_, nullptr);
    EXPECT_EQ(titleMgr_->navbarRow_->GetChildren().size(), 1);

    // 添加右侧导航栏行
    EXPECT_EQ(titleMgr_->rightNavRow_, nullptr);
    titleMgr_->AddRightNavRow();
    ASSERT_NE(titleMgr_->rightNavRow_, nullptr);
    EXPECT_EQ(titleMgr_->navbarRow_->GetChildren().size(), 2);
    titleMgr_->AddRightNavRow();
    ASSERT_NE(titleMgr_->rightNavRow_, nullptr);
    EXPECT_EQ(titleMgr_->navbarRow_->GetChildren().size(), 2);
}

/**
 * @tc.name: AddNavBarRow_002
 * @tc.desc: 测试 AddNavBarRow 方法 - 边界场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, AddNavBarRow_002, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    EXPECT_EQ(titleMgr_->title_->GetChildren().size(), 1);
    EXPECT_EQ(titleMgr_->navbarRow_, nullptr);

    // 设置有导航栏和预创建的导航栏行
    titleMgr_->toolbarManager_->SetHasNavBar(true);
    titleMgr_->navbarRow_ =
        AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(false));

    // 测试添加导航栏行
    titleMgr_->AddNavBarRow();
    ASSERT_NE(titleMgr_->navbarRow_, nullptr);
    EXPECT_EQ(titleMgr_->title_->GetChildren().size(), 1);
    EXPECT_EQ(titleMgr_->navbarRow_->GetChildren().size(), 0);

    // 测试添加左侧导航栏行
    titleMgr_->navbarRow_ = nullptr;
    titleMgr_->AddLeftNavRow();
    EXPECT_EQ(titleMgr_->leftNavRow_, nullptr);

    // 测试添加右侧导航栏行
    titleMgr_->AddRightNavRow();
    EXPECT_EQ(titleMgr_->rightNavRow_, nullptr);
}

/**
 * @tc.name: AddNavDestBarRow_001
 * @tc.desc: 测试 AddNavDestBarRow 方法 - 基本场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, AddNavDestBarRow_001, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 设置有导航目的地
    titleMgr_->toolbarManager_->SetHasNavDest(true);

    // 添加导航目的地行并验证
    ToolbarInfo navDestInfo_ = { false, 500.0f };
    titleMgr_->toolbarManager_->SetNavDestInfo(navDestInfo_);
    EXPECT_EQ(navDestInfo_.isShow, false);
    titleMgr_->AddNavDestBarRow();
    EXPECT_EQ(titleMgr_->navDestbarRow_, nullptr);

    // 设置导航目的地显示状态为true
    navDestInfo_ = { true, 500.0f };
    titleMgr_->toolbarManager_->SetNavDestInfo(navDestInfo_);
    EXPECT_EQ(navDestInfo_.isShow, true);
    titleMgr_->AddNavDestBarRow();
    ASSERT_NE(titleMgr_->navDestbarRow_, nullptr);
    EXPECT_EQ(titleMgr_->navDestbarRow_->GetChildren().size(), 0);

    // 添加左侧导航目的地行
    EXPECT_EQ(titleMgr_->leftNavDestRow_, nullptr);
    titleMgr_->AddLeftNavDestRow();
    ASSERT_NE(titleMgr_->leftNavDestRow_, nullptr);
    EXPECT_EQ(titleMgr_->navDestbarRow_->GetChildren().size(), 1);
    titleMgr_->AddLeftNavDestRow();
    ASSERT_NE(titleMgr_->leftNavDestRow_, nullptr);
    EXPECT_EQ(titleMgr_->navDestbarRow_->GetChildren().size(), 1);

    // 添加右侧导航目的地行
    EXPECT_EQ(titleMgr_->rightNavDestRow_, nullptr);
    titleMgr_->AddRightNavDestRow();
    ASSERT_NE(titleMgr_->rightNavDestRow_, nullptr);
    EXPECT_EQ(titleMgr_->navDestbarRow_->GetChildren().size(), 2);
    titleMgr_->AddRightNavDestRow();
    ASSERT_NE(titleMgr_->rightNavDestRow_, nullptr);
    EXPECT_EQ(titleMgr_->navDestbarRow_->GetChildren().size(), 2);
}

/**
 * @tc.name: AddNavDestBarRow_002
 * @tc.desc: 测试 AddNavDestBarRow 方法 - 边界场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, AddNavDestBarRow_002, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    EXPECT_EQ(titleMgr_->title_->GetChildren().size(), 1);
    EXPECT_EQ(titleMgr_->navDestbarRow_, nullptr);

    // 设置有导航目的地和预创建的导航目的地行
    titleMgr_->toolbarManager_->SetHasNavDest(true);
    titleMgr_->navDestbarRow_ =
        AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(false));

    // 测试添加导航目的地行
    titleMgr_->AddNavDestBarRow();
    ASSERT_NE(titleMgr_->navDestbarRow_, nullptr);
    EXPECT_EQ(titleMgr_->title_->GetChildren().size(), 1);
    EXPECT_EQ(titleMgr_->navDestbarRow_->GetChildren().size(), 0);

    // 测试添加左侧导航目的地行
    titleMgr_->navDestbarRow_ = nullptr;
    titleMgr_->AddLeftNavDestRow();
    EXPECT_EQ(titleMgr_->leftNavDestRow_, nullptr);

    // 测试添加右侧导航目的地行
    titleMgr_->AddRightNavDestRow();
    EXPECT_EQ(titleMgr_->rightNavDestRow_, nullptr);
}

/**
 * @tc.name: RemoveToolbarRowContainers_001
 * @tc.desc: 测试 RemoveToolbarRowContainers 方法 - 基本场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, RemoveToolbarRowContainers_001, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 设置有导航栏和导航目的地
    titleMgr_->toolbarManager_->SetHasNavBar(true);
    titleMgr_->toolbarManager_->SetHasNavDest(true);

    // 添加工具栏行并移除
    titleMgr_->AddNavBarRow();
    ASSERT_NE(titleMgr_->navbarRow_, nullptr);
    titleMgr_->AddNavDestBarRow();
    ASSERT_NE(titleMgr_->navDestbarRow_, nullptr);
    titleMgr_->RemoveToolbarRowContainers();
    ASSERT_EQ(titleMgr_->navbarRow_, nullptr);
    ASSERT_EQ(titleMgr_->navDestbarRow_, nullptr);

    // 创建父节点和工具栏项
    auto parentNode = FrameNode::CreateFrameNode(
        V2::NAVBAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto toolbarItem2 = FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    auto toolbarItem3 = FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem2);
    parentNode->AddChild(toolbarItem3);

    // 添加工具栏项到行
    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_END, toolbarItem2);
    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAVDEST_END, toolbarItem3);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem2);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem3);

    // 移除工具栏行容器
    titleMgr_->RemoveToolbarRowContainers();
    EXPECT_EQ(titleMgr_->title_->GetChildren().size(), 3);
    EXPECT_EQ(titleMgr_->navbarRow_->GetChildren().size(), 2);
    EXPECT_EQ(titleMgr_->navDestbarRow_->GetChildren().size(), 2);
}

/**
 * @tc.name: RemoveToolbarRowContainers_002
 * @tc.desc: 测试 RemoveToolbarRowContainers 方法 - 分步场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, RemoveToolbarRowContainers_002, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 设置有导航栏和导航目的地
    titleMgr_->toolbarManager_->SetHasNavBar(true);
    titleMgr_->toolbarManager_->SetHasNavDest(true);

    // 创建父节点和工具栏项
    auto parentNode = FrameNode::CreateFrameNode(
        V2::NAVBAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto toolbarItem2 = FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem2);
    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_END, toolbarItem2);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem2);
    titleMgr_->RemoveToolbarRowContainers();

    // 验证导航栏行容器
    EXPECT_EQ(titleMgr_->title_->GetChildren().size(), 2);
    EXPECT_EQ(titleMgr_->navbarRow_->GetChildren().size(), 2);

    // 创建第二个工具栏项
    auto toolbarItem3 = FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem3);
    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAVDEST_END, toolbarItem3);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem3);
    titleMgr_->RemoveToolbarRowContainers();

    // 验证导航目的地行容器
    EXPECT_EQ(titleMgr_->title_->GetChildren().size(), 3);
    EXPECT_EQ(titleMgr_->navDestbarRow_->GetChildren().size(), 2);
}

/**
 * @tc.name: OnToolBarLayoutChange
 * @tc.desc: 测试 OnToolBarLayoutChange 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, OnToolBarLayoutChange, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    titleMgr_->hasNavOrSideBarNodes_ = true;

    // 测试工具栏布局变化
    std::vector<std::pair<bool, bool>> vec { { false, false }, { false, true }, { true, false }, { true, true } };
    ToolbarInfo sideBarInfo_ = { false, 200.0f };
    ToolbarInfo sideBarDividerInfo_ = { true, 20.0f };
    ToolbarInfo navBarInfo_ = { false, 500.0f };
    ToolbarInfo navBarDividerInfo_ = { true, 10.0f };
    ToolbarInfo navDestInfo_ = { true, 1200.0f };

    for (auto& pair : vec) {
        navBarInfo_.isShow = pair.first;
        navDestInfo_.isShow = pair.second;
        titleMgr_->toolbarManager_->SetSideBarDividerInfo(sideBarDividerInfo_);
        titleMgr_->toolbarManager_->SetSideBarInfo(sideBarInfo_);
        titleMgr_->toolbarManager_->SetHasNavBar(true);
        titleMgr_->toolbarManager_->SetNavBarInfo(navBarInfo_);
        titleMgr_->toolbarManager_->SetNavBarDividerInfo(navBarDividerInfo_);
        titleMgr_->toolbarManager_->SetHasNavDest(true);
        titleMgr_->toolbarManager_->SetNavDestInfo(navDestInfo_);

        // 触发工具栏布局变更
        titleMgr_->OnToolBarLayoutChange();
        auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
        ASSERT_NE(pipeline, nullptr);
        pipeline->taskScheduler_->FlushAfterRenderTask();
    }
    EXPECT_EQ(titleMgr_->navbarRow_, nullptr);
}

} // namespace OHOS::Ace::NG
