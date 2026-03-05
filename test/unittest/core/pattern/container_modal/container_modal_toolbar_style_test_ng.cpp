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
 * @file container_modal_toolbar_style_test_ng.cpp
 * @brief 工具栏样式更新测试用例
 *
 * 本文件包含 UpdateSideTitleBgColor、UpdateTargetNodesBarMargin、UpdateNavbarTitlebarMargin、
 * UpdateNavDestinationTitlebarMargin、OnChangeSideBarColor、ExpandStackNodeLayout 等样式更新相关测试用例。
 */

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_resource_adapter.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
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
 * @tc.name: UpdateSideTitleBgColor
 * @tc.desc: 测试 ContainerModalToolBar UpdateSideTitleBgColor 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateSideTitleBgColor, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);

    // 设置颜色和模糊样式
    Color otherColor = Color::RED;
    Color baseColor = Color::GREEN;
    BlurStyle blurStyle = BlurStyle::THIN;
    Color blendColor = baseColor.BlendColorWithAlpha(otherColor);

    // 更新侧边栏标题背景颜色
    titleMgr_->UpdateSideTitleBgColor(otherColor, baseColor, blurStyle);

    // 验证标题背景颜色
    auto title = titleMgr_->title_;
    ASSERT_NE(title, nullptr);
    auto titleNode = AceType::DynamicCast<FrameNode>(title->GetChildren().front());
    ASSERT_NE(titleNode, nullptr);
    auto ctx = titleNode->GetRenderContext();
    ASSERT_NE(ctx, nullptr);
    auto titleColor = ctx->GetBackgroundColor().value_or(Color::TRANSPARENT);
    EXPECT_EQ(titleColor, blendColor);
}

/**
 * @tc.name: UpdateTargetNodesBarMargin_001
 * @tc.desc: 测试 ContainerModalToolBar UpdateTargetNodesBarMargin 方法 - 基本场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateTargetNodesBarMargin_001, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto toolbarMgr = titleMgr_->toolbarManager_;
    toolbarMgr->SetTitleHeight(Dimension(60.0f));

    // 测试未更新目标节点时的边距
    titleMgr_->isUpdateTargetNode_ = false;
    titleMgr_->UpdateTargetNodesBarMargin(true);
    auto titleHeight = toolbarMgr->GetTitleHeight().ConvertToPx();
    EXPECT_TRUE(NearEqual(titleHeight, 60.0f));

    // 测试已更新目标节点时的边距
    titleMgr_->isUpdateTargetNode_ = true;
    titleMgr_->UpdateTargetNodesBarMargin(true);
    titleHeight = toolbarMgr->GetTitleHeight().ConvertToPx();
    EXPECT_TRUE(NearEqual(titleHeight, 0.0f));
}

/**
 * @tc.name: UpdateTargetNodesBarMargin_002
 * @tc.desc: 测试 ContainerModalToolBar UpdateTargetNodesBarMargin 方法 - 完整场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateTargetNodesBarMargin_002, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);

    // 设置模式属性
    pattern_->activeColor_ = Color::TRANSPARENT;
    pattern_->inactiveColor_ = Color::TRANSPARENT;
    pattern_->isHaveToolBar_ = true;
    pattern_->isTitleShow_ = true;
    pattern_->isCustomColor_ = true;
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->isUpdateTargetNode_ = false;

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto toolbarMgr = titleMgr_->toolbarManager_;
    titleMgr_->UpdateTargetNodesBarMargin();

    // 验证边距更新结果
    auto isMoveUp = toolbarMgr->GetIsMoveUp();
    EXPECT_TRUE(isMoveUp);
    auto titleHeight = toolbarMgr->GetTitleHeight().ConvertToPx();
    EXPECT_TRUE(NearEqual(titleHeight, pattern_->titleHeight_.ConvertToPx()));
}

/**
 * @tc.name: ExpandStackNodeLayout
 * @tc.desc: 测试 ContainerModalToolBar ExpandStackNodeLayout 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, ExpandStackNodeLayout, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(titleMgr_, nullptr);

    // 扩展堆栈节点布局
    titleMgr_->ExpandStackNodeLayout();
    auto stackNode = pattern_->GetStackNode();
    ASSERT_NE(stackNode, nullptr);
    auto ctx = stackNode->GetRenderContext();
    ASSERT_NE(ctx, nullptr);
    auto zIndex = ctx->GetZIndexValue(ZINDEX_DEFAULT_VALUE);
    ASSERT_EQ(zIndex, -1);

    // 扩展堆栈节点布局（带参数）
    titleMgr_->ExpandStackNodeLayout(true);
    zIndex = ctx->GetZIndexValue(ZINDEX_DEFAULT_VALUE);
    ASSERT_EQ(zIndex, ZINDEX_DEFAULT_VALUE);
}

/**
 * @tc.name: ResetExpandStackNode
 * @tc.desc: 测试 ContainerModalToolBar ResetExpandStackNode 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, ResetExpandStackNode, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(titleMgr_, nullptr);

    // 测试不同的目标节点更新状态和浮动状态组合
    std::vector<std::pair<bool, bool>> vec { { true, false }, { true, true }, { false, true }, { false, false } };
    for (auto pair : vec) {
        titleMgr_->isUpdateTargetNode_ = pair.first;
        titleMgr_->isFloating_ = pair.second;
        titleMgr_->ResetExpandStackNode();
    }

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 测试带工具栏管理器的重置操作
    for (const auto& pair : vec) {
        titleMgr_->toolbarManager_->SetIsMoveUp(true);
        titleMgr_->isUpdateTargetNode_ = pair.first;
        titleMgr_->isFloating_ = pair.second;
        titleMgr_->ResetExpandStackNode();
        auto isMoveUp = titleMgr_->toolbarManager_->GetIsMoveUp();
        if (pair.first && !pair.second) {
            EXPECT_FALSE(isMoveUp);
        } else {
            EXPECT_TRUE(isMoveUp);
        }
    }
}

/**
 * @tc.name: SetCustomTitleRowBlurStyle
 * @tc.desc: 测试 ContainerModalToolBar SetCustomTitleRowBlurStyle 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, SetCustomTitleRowBlurStyle, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(titleMgr_, nullptr);

    // 获取标题节点并验证初始模糊样式
    auto title = titleMgr_->title_;
    ASSERT_NE(title, nullptr);
    auto ctx = title->GetRenderContext();
    ASSERT_NE(ctx, nullptr);
    auto ret = ctx->GetBackBlurStyle().has_value();
    EXPECT_FALSE(ret);

    // 设置自定义标题行模糊样式
    BlurStyle blurStyle = BlurStyle::THIN;
    titleMgr_->SetCustomTitleRowBlurStyle(blurStyle);
    ret = ctx->GetBackBlurStyle().has_value();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: UpdateSidebarMargin
 * @tc.desc: 测试 ContainerModalToolBar UpdateSidebarMargin 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateSidebarMargin, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    auto toolbarMgr = titleMgr_->toolbarManager_;
    ASSERT_NE(toolbarMgr, nullptr);

    // 设置移动上移状态并创建侧边栏容器节点
    toolbarMgr->SetIsMoveUp(true);
    auto sideBarContainerNode = FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    toolbarMgr->SetSideBarContainerModel(sideBarContainerNode);

    // 更新侧边栏边距
    titleMgr_->UpdateSidebarMargin();
    EXPECT_TRUE(titleMgr_->isUpdateTargetNode_);
}

/**
 * @tc.name: UpdateNavbarTitlebarMargin
 * @tc.desc: 测试 ContainerModalToolBar UpdateNavbarTitlebarMargin 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateNavbarTitlebarMargin, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    auto toolbarMgr = titleMgr_->toolbarManager_;
    ASSERT_NE(toolbarMgr, nullptr);

    // 设置移动上移状态并创建导航节点
    toolbarMgr->SetIsMoveUp(true);
    auto navigation = FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto navBar = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    navigation->AddChild(navBar);
    toolbarMgr->SetNavBarNode(navBar);

    // 更新导航栏标题边距
    titleMgr_->UpdateNavbarTitlebarMargin();
    EXPECT_TRUE(titleMgr_->isUpdateTargetNode_);
}

/**
 * @tc.name: UpdateNavDestinationTitlebarMargin
 * @tc.desc: 测试 ContainerModalToolBar UpdateNavDestinationTitlebarMargin 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateNavDestinationTitlebarMargin, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(titleMgr_, nullptr);

    // 初始化工具栏管理器
    titleMgr_->InitToolBarManager();
    auto toolbarMgr = titleMgr_->toolbarManager_;
    ASSERT_NE(toolbarMgr, nullptr);

    // 设置移动上移状态
    toolbarMgr->SetIsMoveUp(true);

    // 创建导航组和导航目的地节点
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        "navigation", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navBarNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto pattern = navigation->GetPattern<NavigationPattern>();
    auto layoutProperty = pattern->GetLayoutProperty<NavigationLayoutProperty>();
    navigation->contentNode_ = contentNode;
    navigation->navBarNode_ = navBarNode;
    navigation->AddChild(contentNode);
    navigation->AddChild(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(AceType::MakeRefPtr<NavigationStack>());
    navigationPattern->navigationStack_->Add("contentNode", contentNode);

    // 设置导航目的地节点
    toolbarMgr->SetNavDestNode(contentNode);

    // 更新导航目的地标题边距
    titleMgr_->UpdateNavDestinationTitlebarMargin();
    EXPECT_TRUE(titleMgr_->isUpdateTargetNode_);
}

/**
 * @tc.name: OnChangeSideBarColor
 * @tc.desc: 测试 ToolbarManager OnChangeSideBarColor 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, OnChangeSideBarColor, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // 设置侧边栏颜色和模糊样式
    Color otherColor = Color::RED;
    Color baseColor = Color::GREEN;
    BlurStyle blurStyle = BlurStyle::THIN;
    Color blendColor = baseColor.BlendColorWithAlpha(otherColor);

    // 设置变更回调
    titleMgr_->SetOnChangeCallback();
    auto toolbarMgr = titleMgr_->toolbarManager_;
    toolbarMgr->SetSideBarColor(otherColor);
    toolbarMgr->SetSideBarContainerColor(baseColor);
    toolbarMgr->SetSideBarBlurStyle(blurStyle);

    // 触发侧边栏颜色变更
    titleMgr_->toolbarManager_->OnChangeSideBarColor();

    // 验证标题背景颜色
    auto title = titleMgr_->title_;
    ASSERT_NE(title, nullptr);
    auto titleNode = AceType::DynamicCast<FrameNode>(title->GetChildren().front());
    ASSERT_NE(titleNode, nullptr);
    auto ctx = titleNode->GetRenderContext();
    ASSERT_NE(ctx, nullptr);
    auto titleColor = ctx->GetBackgroundColor().value_or(Color::TRANSPARENT);
    EXPECT_EQ(titleColor, blendColor);
}

} // namespace OHOS::Ace::NG
