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
 * @file container_modal_toolbar_basic_test_ng.cpp
 * @brief 基础测试用例，包含测试类的初始化、设置和辅助方法
 *
 * 本文件包含 ContainerModelToolBarTestNg 测试类的基础设置、 TearDown 以及各种
 * 辅助方法，用于创建测试环境、生成测试节点和辅助测试执行。
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
// 常量定义：标题项的不同高度规格
constexpr float TITLE_ITEM_HEIGT_S = 56.0;  // 小号标题高度 56vp
constexpr float TITLE_ITEM_HEIGT_M = 64.0;  // 中号标题高度 64vp
constexpr float TITLE_ITEM_HEIGT_L = 72.0;  // 大号标题高度 72vp
const uint32_t VALUE = 0;

// 页面节点和宽度的结构体
struct PageNodeAndWidth {
    RefPtr<UINode> node;  // 页面节点指针
    float width;           // 页面宽度
};
} // namespace

/**
 * @class ContainerModelToolBarTestNg
 * @brief ContainerModal 工具栏测试基类
 *
 * 该类提供用于测试 ContainerModal 工具栏功能的基础设施，
 * 包括测试环境设置、节点创建和辅助方法。
 */
class ContainerModelToolBarTestNg : public TestNG {
protected:
    /**
     * @brief 设置测试套件，初始化全局测试环境
     */
    static void SetUpTestSuite();

    /**
     * @brief 清理测试套件
     */
    static void TearDownTestSuite();

    /**
     * @brief 每个测试用例前的初始化
     */
    void SetUp() override;

    /**
     * @brief 每个测试用例后的清理
     */
    void TearDown() override;

    /**
     * @brief 创建标题管理器
     */
    void CreateTitleMgr();

    /**
     * @brief 获取实例
     */
    void GetInstance();

    /**
     * @brief 创建内容节点
     * @return RefPtr<FrameNode> 内容帧节点
     */
    RefPtr<FrameNode> CreateContent();

    /**
     * @brief 设置模拟窗口
     * @param windowMode 窗口模式
     */
    void SetMockWindow(WindowMode windowMode);

    /**
     * @brief 创建容器模态框
     */
    void CreateContainerModal();

    /**
     * @brief 创建空页面
     */
    void CreateEmptyPage();

    /**
     * @brief 创建仅包含侧边栏的页面
     */
    void CreatePageWithSideBarOnly();

    /**
     * @brief 创建仅包含导航栏的页面
     */
    void CreatePageWithNavigationOnly();

    /**
     * @brief 创建仅包含导航目的地的页面
     */
    void CreatePageWithNavDestOnly();

    /**
     * @brief 创建包含所有节点的页面
     */
    void CreatePageWithAllNodes();

    /**
     * @brief 获取页面节点和宽度
     * @return PageNodeAndWidth 页面节点和宽度信息
     */
    PageNodeAndWidth GetPageNodeAndWidth();

    // 成员变量
    RefPtr<FrameNode> frameNode_;                              // 帧节点
    RefPtr<ContainerModalPattern> pattern_;                      // 容器模态框模式
    RefPtr<LayoutProperty> layoutProperty_;                      // 布局属性
    RefPtr<ContainerModalAccessibilityProperty> accessibilityProperty_;  // 可访问性属性
    RefPtr<ContainerModalToolBar> titleMgr_;                     // 标题管理器
    RefPtr<ContainerModalToolBar> floatTitleMgr_;               // 浮动标题管理器
};

void ContainerModelToolBarTestNg::SetUpTestSuite()
{
    // 设置模拟管道上下文
    MockPipelineContext::SetUp();
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);

    // 创建并设置主题管理器
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    // 创建容器模态框主题常量和主题
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_CONTAINER_MODAL);
    auto containerModalTheme = ContainerModalTheme::Builder().Build(themeConstants);

    // 配置主题管理器的期望
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(containerModalTheme));
    EXPECT_CALL(*themeManager, GetThemeConstants()).WillRepeatedly(Return(themeConstants));
}

void ContainerModelToolBarTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ContainerModelToolBarTestNg::SetUp()
{
    // 设置为全屏窗口模式
    SetMockWindow(WindowMode::WINDOW_MODE_FULLSCREEN);
}

void ContainerModelToolBarTestNg::TearDown()
{
    // 清理所有成员变量
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    titleMgr_ = nullptr;
    floatTitleMgr_ = nullptr;
}

void ContainerModelToolBarTestNg::CreateTitleMgr()
{
    // 创建帧节点并设置工具栏构建器
    auto frameNode = AceType::MakeRefPtr<FrameNode>("frameNode", 0, AceType::MakeRefPtr<Pattern>());
    pattern_->SetToolbarBuilder(frameNode, nullptr);

    // 获取标题管理器和浮动标题管理器
    titleMgr_ = pattern_->titleMgr_;
    floatTitleMgr_ = pattern_->floatTitleMgr_;
}

void ContainerModelToolBarTestNg::GetInstance()
{
    // 获取元素并转换为帧节点
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);

    // 获取相关的模式和属性
    pattern_ = frameNode_->GetPattern<ContainerModalPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ContainerModalAccessibilityProperty>();
}

RefPtr<FrameNode> ContainerModelToolBarTestNg::CreateContent()
{
    // 创建并返回内容帧节点
    return AceType::MakeRefPtr<FrameNode>("stage", 0, AceType::MakeRefPtr<Pattern>());
}

void ContainerModelToolBarTestNg::SetMockWindow(WindowMode windowMode)
{
    // 创建窗口管理器并设置窗口模式回调
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowModeCallback = [windowMode]() { return windowMode; };
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));

    // 设置管道上下文的窗口管理器
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
}

void ContainerModelToolBarTestNg::CreateContainerModal()
{
    // 创建容器模态框视图
    ContainerModalView view;
    RefPtr<FrameNode> content = CreateContent();

    // 创建页面节点
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    content->AddChild(pageNode);

    // 创建帧节点并初始化
    auto frameNode = view.Create(content);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    GetInstance();

    // 创建标题管理器并刷新UI任务
    CreateTitleMgr();
    FlushUITasks(frameNode_);
}

void ContainerModelToolBarTestNg::CreateEmptyPage()
{
    // 验证模式存在
    ASSERT_NE(pattern_, nullptr);
    auto stackNode = pattern_->GetStackNode();
    ASSERT_NE(stackNode, nullptr);

    // 创建舞台和页面节点
    auto stage = FrameNode::CreateFrameNode(
        "stage", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto page = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));

    // 构建节点树：stackNode -> stage -> page
    stage->AddChild(page, 0);
    stackNode->AddChild(stage, 0);
}

void ContainerModelToolBarTestNg::CreatePageWithSideBarOnly()
{
    // 验证模式存在
    ASSERT_NE(pattern_, nullptr);
    auto stackNode = pattern_->GetStackNode();
    ASSERT_NE(stackNode, nullptr);

    // 创建舞台节点
    auto stage = FrameNode::CreateFrameNode(
        "stack", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    // 创建页面节点
    auto page = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));

    // 创建侧边栏节点
    auto sideBarNode = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    // 构建节点树：stackNode -> stage -> page -> sideBarNode
    page->AddChild(sideBarNode);
    stage->AddChild(page, 0);
    stackNode->AddChild(stage, 0);
}

void ContainerModelToolBarTestNg::CreatePageWithNavigationOnly()
{
    // 验证模式存在
    ASSERT_NE(pattern_, nullptr);
    auto stackNode = pattern_->GetStackNode();
    ASSERT_NE(stackNode, nullptr);

    // 创建舞台节点
    auto stage = FrameNode::CreateFrameNode(
        "stack", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    // 创建页面节点
    auto page = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));

    // 创建导航节点
    auto navigationNode = FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavigationPattern>());
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationMode(NavigationMode::SPLIT);

    // 创建导航栏节点
    auto navbarNode = FrameNode::CreateFrameNode(
        V2::NAVBAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->AddChild(navbarNode);

    // 创建导航目的地内容节点
    auto navDestContentNode = FrameNode::CreateFrameNode(
        "navDestContentNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    // 创建导航目的地节点
    auto navDestNode = FrameNode::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    // 构建节点树：stackNode -> stage -> page -> navigationNode -> [navbarNode, navDestContentNode -> navDestNode]
    navDestContentNode->AddChild(navDestNode);
    navigationNode->AddChild(navDestContentNode);
    page->AddChild(navigationNode);
    stage->AddChild(page, 0);
    stackNode->AddChild(stage, 0);
}

void ContainerModelToolBarTestNg::CreatePageWithNavDestOnly()
{
    // 验证模式存在
    ASSERT_NE(pattern_, nullptr);
    auto stackNode = pattern_->GetStackNode();
    ASSERT_NE(stackNode, nullptr);

    // 创建舞台节点
    auto stage = FrameNode::CreateFrameNode(
        "stack", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    // 创建页面节点
    auto page = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));

    // 创建导航节点
    auto navigationNode = FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavigationPattern>());
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationMode(NavigationMode::SPLIT);

    // 创建导航目的地内容节点
    auto navDestContentNode = FrameNode::CreateFrameNode(
        "navDestContentNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    // 创建导航目的地节点（无导航栏）
    auto navDestNode = FrameNode::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    // 构建节点树：stackNode -> stage -> page -> navigationNode -> navDestContentNode -> navDestNode
    navDestContentNode->AddChild(navDestNode);
    navigationNode->AddChild(navDestContentNode);
    page->AddChild(navigationNode);
    stage->AddChild(page, 0);
    stackNode->AddChild(stage, 0);
}

void ContainerModelToolBarTestNg::CreatePageWithAllNodes()
{
    // 验证模式存在
    ASSERT_NE(pattern_, nullptr);
    auto stackNode = pattern_->GetStackNode();
    ASSERT_NE(stackNode, nullptr);

    // 创建舞台节点
    auto stage = FrameNode::CreateFrameNode(
        "stage", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    // 创建页面节点
    auto page = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));

    // 创建导航节点
    auto navigationNode = FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavigationPattern>());
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationMode(NavigationMode::SPLIT);

    // 创建导航栏节点
    auto navbarNode = FrameNode::CreateFrameNode(
        V2::NAVBAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->AddChild(navbarNode);

    // 创建导航目的地内容节点
    auto navDestContentNode = FrameNode::CreateFrameNode(
        "navDestContentNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    // 创建导航目的地节点
    auto navDestNode = FrameNode::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navDestContentNode->AddChild(navDestNode);
    navigationNode->AddChild(navDestContentNode);

    // 创建侧边栏节点
    auto sideBarNode = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    // 构建完整节点树：stackNode -> stage -> page -> sideBarNode -> navigationNode
    sideBarNode->AddChild(navigationNode);
    page->AddChild(sideBarNode);
    stage->AddChild(page, 0);
    stackNode->AddChild(stage, 0);
}

PageNodeAndWidth ContainerModelToolBarTestNg::GetPageNodeAndWidth()
{
    // 初始化返回结构体
    PageNodeAndWidth ret { nullptr, 0 };

    // 验证模式
    CHECK_NULL_RETURN(pattern_, ret);
    auto stackNode = pattern_->GetStackNode();
    CHECK_NULL_RETURN(stackNode, ret);

    // 获取舞台节点
    auto stage = stackNode->GetFirstChild();
    CHECK_NULL_RETURN(stage, ret);

    // 获取页面节点
    auto page = stage->GetFirstChild();
    CHECK_NULL_RETURN(page, ret);

    // 转换为帧节点
    auto pageNode = AceType::DynamicCast<FrameNode>(page);
    CHECK_NULL_RETURN(pageNode, ret);

    // 获取页面几何节点和宽度
    auto pageGeometryNode = pageNode->GetGeometryNode();
    CHECK_NULL_RETURN(pageGeometryNode, ret);
    auto pageWidth = pageGeometryNode->GetFrameSize().Width();

    // 填充返回值
    ret.node = page;
    ret.width = pageWidth;
    return ret;
}

} // namespace OHOS::Ace::NG
