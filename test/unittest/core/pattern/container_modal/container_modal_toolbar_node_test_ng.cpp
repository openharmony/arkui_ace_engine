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
 * @file container_modal_toolbar_node_test_ng.cpp
 * @brief 工具栏节点相关测试用例
 *
 * 本文件包含 GetNavOrSideBarNodes、GetNavOrSideBarNodesParseChildren、
 * IsTragetSideBarNodeParse、IsTragetNavigationNodeParse、ToInitNavOrSideBarNode、
 * GetCurrentPageNode 等节点相关测试用例。
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
 * @tc.name: GetNavOrSideBarNodes
 * @tc.desc: 测试 GetNavOrSideBarNodes 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodes, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    CreatePageWithAllNodes();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);

    // 测试获取导航或侧边栏节点
    bool ret = titleMgr_->GetNavOrSideBarNodes(AceType::DynamicCast<FrameNode>(pageInfo.node));
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: GetNavOrSideBarNodesParseChildren_EmptyPage
 * @tc.desc: 测试 GetNavOrSideBarNodesParseChildren 方法 - 空页面场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodesParseChildren_EmptyPage, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    CreateEmptyPage();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);

    // 测试解析空页面的子节点
    ASSERT_FALSE(titleMgr_->GetNavOrSideBarNodesParseChildren(pageInfo.node, pageInfo.width));
}

/**
 * @tc.name: GetNavOrSideBarNodesParseChildren_OnlySideBar
 * @tc.desc: 测试 GetNavOrSideBarNodesParseChildren 方法 - 仅侧边栏场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodesParseChildren_OnlySideBar, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    CreatePageWithSideBarOnly();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);

    // 测试解析仅包含侧边栏的子节点
    ASSERT_FALSE(titleMgr_->GetNavOrSideBarNodesParseChildren(pageInfo.node, pageInfo.width));
}

/**
 * @tc.name: GetNavOrSideBarNodesParseChildren_OnlyNavigation
 * @tc.desc: 测试 GetNavOrSideBarNodesParseChildren 方法 - 仅导航栏场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodesParseChildren_OnlyNavigation, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    CreatePageWithNavigationOnly();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);

    // 测试解析仅包含导航栏的子节点
    ASSERT_TRUE(titleMgr_->GetNavOrSideBarNodesParseChildren(pageInfo.node, pageInfo.width));
}

/**
 * @tc.name: GetNavOrSideBarNodesParseChildren_OnlyNavDest
 * @tc.desc: 测试 GetNavOrSideBarNodesParseChildren 方法 - 仅导航目的地场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodesParseChildren_OnlyNavDest, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    CreatePageWithNavDestOnly();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);

    // 测试解析仅包含导航目的地的子节点
    ASSERT_TRUE(titleMgr_->GetNavOrSideBarNodesParseChildren(pageInfo.node, pageInfo.width));
}

/**
 * @tc.name: GetNavOrSideBarNodesParseChildren_SideBarAndNavigation
 * @tc.desc: 测试 GetNavOrSideBarNodesParseChildren 方法 - 侧边栏和导航栏场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodesParseChildren_SideBarAndNavigation, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    CreatePageWithSideBarOnly();
    CreatePageWithNavigationOnly();
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);

    // 测试解析侧边栏和导航栏的子节点
    ASSERT_TRUE(titleMgr_->GetNavOrSideBarNodesParseChildren(pageInfo.node, pageInfo.width));
}

/**
 * @tc.name: GetNavOrSideBarNodesParseChildren_SideBarAndNavDest
 * @tc.desc: 测试 GetNavOrSideBarNodesParseChildren 方法 - 侧边栏和导航目的地场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodesParseChildren_SideBarAndNavDest, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    CreatePageWithSideBarOnly();
    CreatePageWithNavDestOnly();
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);

    // 测试解析侧边栏和导航目的地的子节点
    ASSERT_TRUE(titleMgr_->GetNavOrSideBarNodesParseChildren(pageInfo.node, pageInfo.width));
}

/**
 * @tc.name: GetNavOrSideBarNodesParseChildren_NavigationAndNavDest
 * @tc.desc: 测试 GetNavOrSideBarNodesParseChildren 方法 - 导航栏和导航目的地场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodesParseChildren_NavigationAndNavDest, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    CreatePageWithSideBarOnly();
    CreatePageWithNavDestOnly();
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);

    // 测试解析导航栏和导航目的地的子节点
    ASSERT_TRUE(titleMgr_->GetNavOrSideBarNodesParseChildren(pageInfo.node, pageInfo.width));
}

/**
 * @tc.name: GetNavOrSideBarNodesParseChildren_AllNodes
 * @tc.desc: 测试 GetNavOrSideBarNodesParseChildren 方法 - 所有节点场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodesParseChildren_AllNodes, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    CreatePageWithAllNodes();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);

    // 测试解析所有节点的子节点
    ASSERT_TRUE(titleMgr_->GetNavOrSideBarNodesParseChildren(pageInfo.node, pageInfo.width));
}

/**
 * @tc.name: IsTragetSideBarNodeParseTest
 * @tc.desc: 测试 IsTragetSideBarNodeParse 方法 - 不同场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, IsTragetSideBarNodeParseTest, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    RefPtr<FrameNode> nullFrameNode = nullptr;
    float pageWidth = 100.0f;
    float sideBarHeight = 0.0f;
    bool isSideBarFound = false;

    // 测试 null 节点
    bool result = titleMgr_->IsTragetSideBarNodeParse(nullFrameNode, pageWidth, sideBarHeight, isSideBarFound);
    EXPECT_FALSE(result);

    // 测试非侧边栏节点
    auto nonSideBarNode = FrameNode::CreateFrameNode("NonSideBar", 1, AceType::MakeRefPtr<Pattern>());
    result = titleMgr_->IsTragetSideBarNodeParse(nonSideBarNode, pageWidth, sideBarHeight, isSideBarFound);
    EXPECT_FALSE(result);

    // 测试侧边栏节点（高度小于页面宽度）
    auto sideBarNode = FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(50.0f, 200.0f));
    sideBarNode->SetGeometryNode(geometryNode);
    result = titleMgr_->IsTragetSideBarNodeParse(sideBarNode, pageWidth, sideBarHeight, isSideBarFound);
    EXPECT_FALSE(result);

    // 测试侧边栏节点（高度等于页面宽度）
    geometryNode->SetFrameSize(SizeF(pageWidth, 300.0f));
    sideBarNode->SetGeometryNode(geometryNode);
    result = titleMgr_->IsTragetSideBarNodeParse(sideBarNode, pageWidth, sideBarHeight, isSideBarFound);
    EXPECT_TRUE(result);
    EXPECT_EQ(sideBarHeight, 300.0f);
    EXPECT_EQ(titleMgr_->sideBarNode_, sideBarNode);

    // 测试侧边栏节点（已找到）
    isSideBarFound = true;
    result = titleMgr_->IsTragetSideBarNodeParse(sideBarNode, pageWidth, sideBarHeight, isSideBarFound);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsTragetNavigationNodeParse_001
 * @tc.desc: 测试 IsTragetNavigationNodeParse 方法 - SPLIT 模式
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, IsTragetNavigationNodeParse_001, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 测试非导航节点
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>());
    bool result = titleMgr_->IsTragetNavigationNodeParse(frameNode, 500.0f, 300.0f, true, false);
    EXPECT_FALSE(result);

    // 创建导航节点并设置 SPLIT 模式
    auto navigationNode =
        FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 2, AceType::MakeRefPtr<NavigationPattern>());
    result = titleMgr_->IsTragetNavigationNodeParse(navigationNode, 500.0f, 300.0f, true, false);
    EXPECT_FALSE(result);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(500.0f, 300.0f));
    navigationNode->SetGeometryNode(geometryNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationMode(NavigationMode::SPLIT);

    // 测试不同宽度和模式组合
    result = titleMgr_->IsTragetNavigationNodeParse(navigationNode, 500.0f, 300.0f, false, false);
    EXPECT_TRUE(result);
    EXPECT_EQ(titleMgr_->navigationNode_, navigationNode);

    result = titleMgr_->IsTragetNavigationNodeParse(navigationNode, 600.0f, 300.0f, false, false);
    EXPECT_FALSE(result);

    result = titleMgr_->IsTragetNavigationNodeParse(navigationNode, 500.0f, 300.0f, false, true);
    EXPECT_TRUE(result);
    EXPECT_EQ(titleMgr_->navigationNode_, navigationNode);

    result = titleMgr_->IsTragetNavigationNodeParse(navigationNode, 500.0f, 400.0f, false, true);
    EXPECT_FALSE(result);

    result = titleMgr_->IsTragetNavigationNodeParse(navigationNode, 500.0f, 0.0f, false, true);
    EXPECT_TRUE(result);
    EXPECT_EQ(titleMgr_->navigationNode_, navigationNode);
}

/**
 * @tc.name: IsTragetNavigationNodeParse_002
 * @tc.desc: 测试 IsTragetNavigationNodeParse 方法 - STACK 模式
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, IsTragetNavigationNodeParse_002, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 创建导航节点并设置 STACK 模式
    auto navigationNode =
        FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 2, AceType::MakeRefPtr<NavigationPattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(500.0f, 300.0f));
    navigationNode->SetGeometryNode(geometryNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationMode(NavigationMode::STACK);

    // 测试 STACK 模式下所有场景都应返回 false
    bool result = titleMgr_->IsTragetNavigationNodeParse(navigationNode, 500.0f, 300.0f, false, false);
    EXPECT_FALSE(result);

    result = titleMgr_->IsTragetNavigationNodeParse(navigationNode, 600.0f, 300.0f, false, false);
    EXPECT_FALSE(result);

    result = titleMgr_->IsTragetNavigationNodeParse(navigationNode, 500.0f, 300.0f, false, true);
    EXPECT_FALSE(result);

    result = titleMgr_->IsTragetNavigationNodeParse(navigationNode, 500.0f, 400.0f, false, true);
    EXPECT_FALSE(result);

    result = titleMgr_->IsTragetNavigationNodeParse(navigationNode, 500.0f, 0.0f, false, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ToInitNavOrSideBarNodeTest
 * @tc.desc: 测试 ToInitNavOrSideBarNode 方法 - 不同节点组合
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, ToInitNavOrSideBarNodeTest, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 测试初始无节点状态
    titleMgr_->sideBarNode_.Reset();
    titleMgr_->navigationNode_.Reset();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    titleMgr_->toolbarManager_->modifyDoneCallbackFuncs_.clear();
    titleMgr_->ToInitNavOrSideBarNode();
    EXPECT_EQ(titleMgr_->toolbarManager_->modifyDoneCallbackFuncs_.size(), 1);

    // 测试仅侧边栏节点
    auto sideBarNode = FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    titleMgr_->sideBarNode_ = AceType::WeakClaim(AceType::RawPtr(sideBarNode));
    titleMgr_->navigationNode_.Reset();
    titleMgr_->ToInitNavOrSideBarNode();
    EXPECT_EQ(titleMgr_->toolbarManager_->modifyDoneCallbackFuncs_.size(), 2);

    // 测试带侧边栏模式的侧边栏节点
    sideBarNode = FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 2, AceType::MakeRefPtr<SideBarContainerPattern>());
    titleMgr_->sideBarNode_ = AceType::WeakClaim(AceType::RawPtr(sideBarNode));
    titleMgr_->navigationNode_.Reset();
    titleMgr_->ToInitNavOrSideBarNode();
    EXPECT_EQ(titleMgr_->toolbarManager_->modifyDoneCallbackFuncs_.size(), 3);

    // 测试重置状态
    titleMgr_->sideBarNode_.Reset();
    titleMgr_->navigationNode_.Reset();
    titleMgr_->ToInitNavOrSideBarNode();
    EXPECT_EQ(titleMgr_->toolbarManager_->modifyDoneCallbackFuncs_.size(), 4);

    // 测试仅导航节点
    auto navigationNode = FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 3, AceType::MakeRefPtr<Pattern>());
    titleMgr_->sideBarNode_.Reset();
    titleMgr_->navigationNode_ = AceType::WeakClaim(AceType::RawPtr(navigationNode));
    titleMgr_->ToInitNavOrSideBarNode();
    EXPECT_EQ(titleMgr_->toolbarManager_->modifyDoneCallbackFuncs_.size(), 5);

    // 测试带导航模式的导航节点
    navigationNode =
        FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 4, AceType::MakeRefPtr<NavigationPattern>());
    titleMgr_->sideBarNode_.Reset();
    titleMgr_->navigationNode_ = AceType::WeakClaim(AceType::RawPtr(navigationNode));
    titleMgr_->ToInitNavOrSideBarNode();
    EXPECT_EQ(titleMgr_->toolbarManager_->modifyDoneCallbackFuncs_.size(), 6);

    // 测试侧边栏和导航节点组合
    sideBarNode = FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 5, AceType::MakeRefPtr<SideBarContainerPattern>());
    titleMgr_->sideBarNode_ = AceType::WeakClaim(AceType::RawPtr(sideBarNode));
    navigationNode =
        FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 6, AceType::MakeRefPtr<NavigationPattern>());
    titleMgr_->navigationNode_ = AceType::WeakClaim(AceType::RawPtr(navigationNode));
    titleMgr_->ToInitNavOrSideBarNode();
    EXPECT_EQ(titleMgr_->toolbarManager_->modifyDoneCallbackFuncs_.size(), 7);
}

/**
 * @tc.name: GetCurrentPageNode
 * @tc.desc: 测试 ContainerModelToolBar::GetCurrentPageNode 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, GetCurrentPageNode, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 测试 null 节点
    auto ret = titleMgr_->GetCurrentPageNode(nullptr);
    EXPECT_EQ(ret, nullptr);

    // 测试非页面节点
    auto node = FrameNode::CreateFrameNode(
        "node", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ret = titleMgr_->GetCurrentPageNode(node);
    EXPECT_EQ(ret, nullptr);

    // 测试页面节点但无父节点
    auto page = FrameNode::CreateFrameNode(
        "page", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ret = titleMgr_->GetCurrentPageNode(page);
    EXPECT_EQ(ret, nullptr);

    // 测试页面节点和非舞台父节点
    auto parent = FrameNode::CreateFrameNode(
        "parent", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    parent->AddChild(page);
    ret = titleMgr_->GetCurrentPageNode(page);
    EXPECT_EQ(ret, nullptr);

    // 测试页面节点和舞台父节点
    auto stage = FrameNode::CreateFrameNode(
        "stage", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    parent->RemoveChild(page);
    stage->AddChild(page);
    ret = titleMgr_->GetCurrentPageNode(page);
    EXPECT_NE(ret, nullptr);
}

} // namespace OHOS::Ace::NG
