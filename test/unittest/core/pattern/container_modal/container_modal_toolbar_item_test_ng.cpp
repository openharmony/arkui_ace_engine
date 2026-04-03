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
 * @file container_modal_toolbar_item_test_ng.cpp
 * @brief 工具栏项相关测试用例
 *
 * 本文件包含 GetItemTypeFromTag、RemoveToolbarItem、GetTagFromNode、AddToolbarItemToContainer
 * 等工具栏项相关操作的测试用例。
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
 * @tc.name: GetItemTypeFromTag
 * @tc.desc: 测试 GetItemTypeFromTag 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, GetItemTypeFromTag, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 测试导航栏标签
    auto type = titleMgr_->GetItemTypeFromTag(V2::NAVBAR_ETS_TAG, 0);
    EXPECT_EQ(type, ItemPlacementType::NAV_BAR_START);
    type = titleMgr_->GetItemTypeFromTag(V2::NAVBAR_ETS_TAG, 1);
    EXPECT_EQ(type, ItemPlacementType::NAV_BAR_END);

    // 测试侧边栏标签
    type = titleMgr_->GetItemTypeFromTag(V2::SIDE_BAR_ETS_TAG, 0);
    EXPECT_EQ(type, ItemPlacementType::SIDE_BAR_START);
    type = titleMgr_->GetItemTypeFromTag(V2::SIDE_BAR_ETS_TAG, 1);
    EXPECT_EQ(type, ItemPlacementType::SIDE_BAR_END);

    // 测试导航目的地视图标签
    type = titleMgr_->GetItemTypeFromTag(V2::NAVDESTINATION_VIEW_ETS_TAG, 0);
    EXPECT_EQ(type, ItemPlacementType::NAVDEST_START);
    type = titleMgr_->GetItemTypeFromTag(V2::NAVDESTINATION_VIEW_ETS_TAG, 1);
    EXPECT_EQ(type, ItemPlacementType::NAVDEST_END);

    // 测试无效标签
    type = titleMgr_->GetItemTypeFromTag("InvalidTag", 0);
    EXPECT_EQ(type, ItemPlacementType::NONE);
    type = titleMgr_->GetItemTypeFromTag("InvalidTag", 1);
    EXPECT_EQ(type, ItemPlacementType::NONE);
}

/**
 * @tc.name: RemoveAllToolbarItem
 * @tc.desc: 测试 RemoveAllToolbarItem 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, RemoveAllToolbarItem, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 创建父节点和工具栏项
    auto parentNode = FrameNode::CreateFrameNode(
        V2::NAVBAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto toolbarItem = FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem);

    // 创建无父节点的工具栏项
    auto noParentToolbarItem = FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());

    // 添加到 itemsOnTree_
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem);
    titleMgr_->itemsOnTree_[parentNode].push_back(noParentToolbarItem);

    // 移除所有工具栏项
    titleMgr_->RemoveAllToolbarItem();

    // 验证 itemsOnTree_ 已清空
    EXPECT_TRUE(titleMgr_->itemsOnTree_.empty());
}

/**
 * @tc.name: RemoveToolbarItem
 * @tc.desc: 测试 RemoveToolbarItem 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, RemoveToolbarItem, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 创建父节点和工具栏项
    auto parentNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto toolbarItem =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 2, AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem);

    // 创建无父节点的工具栏项
    auto noParentToolbarItem =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 3, AceType::MakeRefPtr<ToolBarItemPattern>());

    // 添加到 itemsOnTree_
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem);
    titleMgr_->itemsOnTree_[parentNode].push_back(noParentToolbarItem);

    // 移除工具栏项
    titleMgr_->RemoveToolbarItem(parentNode);

    // 验证 itemsOnTree_ 已清空
    EXPECT_TRUE(titleMgr_->itemsOnTree_.empty());
}

/**
 * @tc.name: GetTagFromNode_001
 * @tc.desc: 测试 GetTagFromNode 方法 - 基本场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, GetTagFromNode_001, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 创建导航节点和导航栏节点
    auto navigationNode = FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto navbarNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    navigationNode->AddChild(navbarNode);
    titleMgr_->navigationNode_ = AceType::WeakClaim(AceType::RawPtr(navigationNode));

    // 测试获取导航栏标签
    std::string ret = titleMgr_->GetTagFromNode(navbarNode);
    EXPECT_EQ(ret, navbarNode->GetTag());

    // 创建导航目的地内容节点和导航目的地节点
    auto navDestContentNode = FrameNode::CreateFrameNode("navDestContentNode", 3, AceType::MakeRefPtr<Pattern>());
    auto navDestNode = FrameNode::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG, 4, AceType::MakeRefPtr<Pattern>());
    navDestContentNode->AddChild(navDestNode);
    navigationNode->AddChild(navDestContentNode);

    // 测试获取导航目的地标签
    ret = titleMgr_->GetTagFromNode(navDestNode);
    EXPECT_EQ(ret, navDestNode->GetTag());
}

/**
 * @tc.name: GetTagFromNode_002
 * @tc.desc: 测试 GetTagFromNode 方法 - 边界场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, GetTagFromNode_002, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 创建导航节点和导航栏节点（无导航节点关联）
    auto navigationNode = FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto navbarNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());

    // 测试获取导航栏标签（无关联节点）
    std::string ret = titleMgr_->GetTagFromNode(navbarNode);
    EXPECT_EQ(ret, "");

    // 创建导航目的地节点（无关联节点）
    auto navDestNode = FrameNode::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG, 4, AceType::MakeRefPtr<Pattern>());
    ret = titleMgr_->GetTagFromNode(navDestNode);
    EXPECT_EQ(ret, "");

    // 设置导航节点关联
    titleMgr_->navigationNode_ = AceType::WeakClaim(AceType::RawPtr(navigationNode));
    ret = titleMgr_->GetTagFromNode(navDestNode);
    EXPECT_EQ(ret, "");

    // 创建导航目的地内容节点并建立关联
    auto navDestContentNode = FrameNode::CreateFrameNode("navDestContentNode", 3, AceType::MakeRefPtr<Pattern>());
    navDestContentNode->AddChild(navDestNode);
    navigationNode->AddChild(navDestContentNode);

    // 测试获取导航目的地标签（有完整关联）
    ret = titleMgr_->GetTagFromNode(navDestNode);
    EXPECT_EQ(ret, navDestNode->GetTag());

    // 设置导航目的地节点关联
    titleMgr_->navDestNode_ = AceType::WeakClaim(AceType::RawPtr(navDestNode));
    ret = titleMgr_->GetTagFromNode(navDestNode);
    EXPECT_EQ(ret, navDestNode->GetTag());
}

/**
 * @tc.name: AddToolbarItemToContainer
 * @tc.desc: 测试 AddToolbarItemToContainer 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, AddToolbarItemToContainer, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    titleMgr_->toolbarManager_->SetHasNavBar(true);

    // 创建导航栏起始位置的工具栏项
    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->itemWillAdd_[ItemPlacementType::NAV_BAR_START].emplace_back(toolbarItem);
    titleMgr_->AddToolbarItemToContainer();

    // 验证有导航栏时工具栏项未被移除
    EXPECT_EQ(titleMgr_->itemWillAdd_.size(), 1);
    EXPECT_EQ(titleMgr_->itemsWillOnTree_.size(), 0);

    // 清空并设置无导航栏场景
    titleMgr_->itemWillAdd_.clear();
    titleMgr_->itemsWillOnTree_.clear();
    titleMgr_->toolbarManager_->SetHasNavBar(false);

    // 创建工具栏项到不同位置
    auto toolbarItem1 = FrameNode::CreateFrameNode("toolbarItem", 2, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->itemWillAdd_[ItemPlacementType::NONE].emplace_back(toolbarItem1);
    titleMgr_->itemWillAdd_[ItemPlacementType::NAV_BAR_START].emplace_back(toolbarItem);
    titleMgr_->AddToolbarItemToContainer();

    // 验证无导航栏时工具栏项保留
    EXPECT_EQ(titleMgr_->itemWillAdd_.size(), 2);
    EXPECT_EQ(titleMgr_->itemsWillOnTree_.size(), 0);
}

/**
 * @tc.name: ToolBarItemCreate
 * @tc.desc: 测试 ToolBarItemCreate 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolBarItemCreate, TestSize.Level1)
{
    // 创建工具栏项模型
    ToolBarItemModelNG model;
    model.SetIsFirstCreate(true);
    model.Create(VALUE);
    auto toolbaritemNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(toolbaritemNode, nullptr);
    EXPECT_EQ(toolbaritemNode->GetTag(), V2::TOOLBARITEM_ETS_TAG);

    // 获取父节点验证
    auto toolbarNode = toolbaritemNode->GetParent();
    ASSERT_NE(toolbarNode, nullptr);
    EXPECT_EQ(toolbarNode->GetTag(), V2::TOOLBAR_ETS_TAG);
    EXPECT_EQ(toolbarNode->GetChildren().size(), 1);

    // 测试第二次创建
    model.SetIsFirstCreate(false);
    model.Create(VALUE);
    EXPECT_EQ(toolbarNode->GetChildren().size(), 2);
}

} // namespace OHOS::Ace::NG
