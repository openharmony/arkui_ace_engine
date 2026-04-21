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
 * @file container_modal_toolbar_focus_test_ng.cpp
 * @brief 工具栏焦点事件测试用例
 *
 * 本文件包含 FocusEventTest、ToolBarRowPatternGetNextFocusNodeTest 等焦点事件
 * 相关测试用例。测试页面模式和工具栏行模式的焦点导航算法。
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
 * @tc.name: FocusEventTest_001
 * @tc.desc: 测试 PagePattern GetScopeFocusAlgorithm 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, FocusEventTest_001, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    auto pageNode = pattern_->GetPageNode();
    ASSERT_NE(pageNode, nullptr);
    EXPECT_EQ(pageNode->GetTag(), V2::PAGE_ETS_TAG);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    ASSERT_NE(pagePattern, nullptr);

    // 设置无工具栏并验证焦点算法
    pattern_->SetIsHaveToolBar(false);
    EXPECT_EQ(pattern_->GetIsHaveToolBar(), false);
    auto focusAlgorithmFalse = pagePattern->GetScopeFocusAlgorithm();
    EXPECT_EQ(focusAlgorithmFalse.getNextFocusNode, nullptr);
}

/**
 * @tc.name: FocusEventTest_002
 * @tc.desc: 测试 ToolBarRowPattern GetScopeFocusAlgorithm 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, FocusEventTest_002, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    auto toolBarRow = pattern_->GetCustomTitleRow();
    ASSERT_NE(toolBarRow, nullptr);
    EXPECT_EQ(toolBarRow->GetTag(), V2::ROW_ETS_TAG);
    auto toolBarRowPattern = toolBarRow->GetPattern<ToolBarRowPattern>();
    ASSERT_NE(toolBarRowPattern, nullptr);

    // 获取焦点算法并验证
    auto focusAlgorithm = toolBarRowPattern->GetScopeFocusAlgorithm();
    ASSERT_NE(focusAlgorithm.getNextFocusNode, nullptr);
}

/**
 * @tc.name: FocusEventTest_003
 * @tc.desc: 测试 PagePattern GetNextFocusNode 方法
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, FocusEventTest_003, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
    ASSERT_NE(pipeline, nullptr);
    auto rootNode = pipeline->rootNode_;
    ASSERT_NE(rootNode, nullptr);
    rootNode->AddChild(frameNode_, 0);
    ASSERT_NE(pattern_, nullptr);
    auto pageNode = pattern_->GetPageNode();
    ASSERT_NE(pageNode, nullptr);
    EXPECT_EQ(pageNode->GetTag(), V2::PAGE_ETS_TAG);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    ASSERT_NE(pagePattern, nullptr);
    auto toolBarRow = pattern_->GetCustomTitleRow();
    ASSERT_NE(toolBarRow, nullptr);
    EXPECT_EQ(toolBarRow->GetTag(), V2::ROW_ETS_TAG);
    auto toolBarRowFocusHub = toolBarRow->GetFocusHub();
    ASSERT_NE(toolBarRowFocusHub, nullptr);

    // 创建按钮节点和焦点 Hub
    auto buttonNode1 = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonFocusHub1 = buttonNode1->GetFocusHub();
    ASSERT_NE(buttonFocusHub1, nullptr);

    auto buttonNode2 = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonFocusHub2 = buttonNode2->GetFocusHub();
    ASSERT_NE(buttonFocusHub2, nullptr);

    auto buttonNode3 = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonFocusHub3 = buttonNode3->GetFocusHub();
    ASSERT_NE(buttonFocusHub3, nullptr);

    // 构建节点树
    pageNode->AddChild(buttonNode1);
    toolBarRow->AddChild(buttonNode2, 0);
    toolBarRow->AddChild(buttonNode3, 1);

    ASSERT_NE(toolBarRowFocusHub->GetHeadOrTailChild(true), nullptr);

    // 测试不同焦点步进下的焦点导航
    EXPECT_EQ(pagePattern->GetNextFocusNode(FocusStep::UP, buttonFocusHub1).Upgrade(), buttonFocusHub2);
    EXPECT_EQ(pagePattern->GetNextFocusNode(FocusStep::TAB, buttonFocusHub1).Upgrade(), toolBarRowFocusHub);
    EXPECT_EQ(pagePattern->GetNextFocusNode(FocusStep::SHIFT_TAB, buttonFocusHub1).Upgrade(), toolBarRowFocusHub);
    EXPECT_EQ(pagePattern->GetNextFocusNode(FocusStep::LEFT, buttonFocusHub1).Upgrade(), nullptr);
    EXPECT_EQ(pagePattern->GetNextFocusNode(FocusStep::RIGHT, buttonFocusHub1).Upgrade(), nullptr);
    rootNode->RemoveChild(frameNode_);
}

/**
 * @tc.name: ToolBarRowPatternGetNextFocusNodeTest_001
 * @tc.desc: 测试 ToolBarRowPattern::GetNextFocusNode FocusStep::DOWN
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolBarRowPatternGetNextFocusNodeTest_001, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
    ASSERT_NE(pipeline, nullptr);
    auto rootNode = pipeline->rootNode_;
    ASSERT_NE(rootNode, nullptr);
    rootNode->AddChild(frameNode_, 0);

    // 获取组件和焦点 Hub
    auto pattern = frameNode_->GetPattern<ContainerModalPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pageNode = pattern->GetPageNode();
    ASSERT_NE(pageNode, nullptr);
    auto pageFocusHub = pageNode->GetFocusHub();
    ASSERT_NE(pageFocusHub, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    pageNode->AddChild(buttonNode);
    auto buttonFocusHub = buttonNode->GetFocusHub();
    ASSERT_NE(buttonFocusHub, nullptr);

    auto toolBarRow = pattern->GetCustomTitleRow();
    ASSERT_NE(toolBarRow, nullptr);
    auto toolBarRowPattern = toolBarRow->GetPattern<ToolBarRowPattern>();
    ASSERT_NE(toolBarRowPattern, nullptr);
    auto toolBarRowFocusHub = toolBarRow->GetFocusHub();
    ASSERT_NE(toolBarRowFocusHub, nullptr);

    // 测试 DOWN 和 UP 焦点步进
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::DOWN, toolBarRowFocusHub).Upgrade(), buttonFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::UP, toolBarRowFocusHub).Upgrade(), nullptr);
    rootNode->RemoveChild(frameNode_);
}

/**
 * @tc.name: ToolBarRowPatternGetNextFocusNodeTest_002
 * @tc.desc: 测试 ToolBarRowPattern::GetNextFocusNode leftRow
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolBarRowPatternGetNextFocusNodeTest_002, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
    ASSERT_NE(pipeline, nullptr);
    auto rootNode = pipeline->rootNode_;
    ASSERT_NE(rootNode, nullptr);
    rootNode->AddChild(frameNode_, 0);

    // 获取组件和焦点 Hub
    auto pattern = frameNode_->GetPattern<ContainerModalPattern>();
    ASSERT_NE(pattern, nullptr);
    auto toolBarRow = pattern->GetCustomTitleRow();
    ASSERT_NE(toolBarRow, nullptr);
    auto toolBarRowPattern = toolBarRow->GetPattern<ToolBarRowPattern>();
    ASSERT_NE(toolBarRowPattern, nullptr);
    auto pageNode = pattern->GetPageNode();
    ASSERT_NE(pageNode, nullptr);
    auto pageFocusHub = pageNode->GetFocusHub();
    ASSERT_NE(pageFocusHub, nullptr);

    // 创建左侧行和按钮节点
    auto leftRow = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto leftRowFocusHub = leftRow->GetFocusHub();
    toolBarRow->AddChild(leftRow, 1);

    auto buttonNode1 = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonFocusHub1 = buttonNode1->GetFocusHub();
    leftRow->AddChild(buttonNode1);

    // 测试左侧行中的焦点导航
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::TAB, buttonFocusHub1).Upgrade(), pageFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::RIGHT, buttonFocusHub1).Upgrade(), nullptr);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::SHIFT_TAB, buttonFocusHub1).Upgrade(), leftRowFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::LEFT, buttonFocusHub1).Upgrade(), leftRowFocusHub);

    rootNode->RemoveChild(frameNode_);
}

/**
 * @tc.name: ToolBarRowPatternGetNextFocusNodeTest_003
 * @tc.desc: 测试 ToolBarRowPattern::GetNextFocusNode rightRow
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolBarRowPatternGetNextFocusNodeTest_003, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
    ASSERT_NE(pipeline, nullptr);
    auto rootNode = pipeline->rootNode_;
    ASSERT_NE(rootNode, nullptr);
    rootNode->AddChild(frameNode_, 0);

    // 获取组件和焦点 Hub
    auto pattern = frameNode_->GetPattern<ContainerModalPattern>();
    ASSERT_NE(pattern, nullptr);
    auto toolBarRow = pattern->GetCustomTitleRow();
    ASSERT_NE(toolBarRow, nullptr);
    auto toolBarRowPattern = toolBarRow->GetPattern<ToolBarRowPattern>();
    ASSERT_NE(toolBarRowPattern, nullptr);
    auto pageNode = pattern->GetPageNode();
    ASSERT_NE(pageNode, nullptr);
    auto pageFocusHub = pageNode->GetFocusHub();
    ASSERT_NE(pageFocusHub, nullptr);

    // 创建右侧行和按钮节点
    auto rightRow = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto rightRowFocusHub = rightRow->GetFocusHub();
    toolBarRow->AddChild(rightRow, 2);

    auto buttonNode1 = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonFocusHub1 = buttonNode1->GetFocusHub();
    rightRow->AddChild(buttonNode1);

    // 测试右侧行中的焦点导航
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::TAB, buttonFocusHub1).Upgrade(), pageFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::RIGHT, buttonFocusHub1).Upgrade(), nullptr);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::SHIFT_TAB, buttonFocusHub1).Upgrade(), pageFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::LEFT, buttonFocusHub1).Upgrade(), nullptr);

    rootNode->RemoveChild(frameNode_);
}

/**
 * @tc.name: ToolBarRowPatternGetNextFocusNodeTest_004
 * @tc.desc: 测试 ToolBarRowPattern::GetNextFocusNode leftRow and rightRow
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolBarRowPatternGetNextFocusNodeTest_004, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
    ASSERT_NE(pipeline, nullptr);
    auto rootNode = pipeline->rootNode_;
    ASSERT_NE(rootNode, nullptr);
    rootNode->AddChild(frameNode_, 0);

    // 获取组件和焦点 Hub
    auto pattern = frameNode_->GetPattern<ContainerModalPattern>();
    ASSERT_NE(pattern, nullptr);
    auto toolBarRow = pattern->GetCustomTitleRow();
    ASSERT_NE(toolBarRow, nullptr);
    auto toolBarRowPattern = toolBarRow->GetPattern<ToolBarRowPattern>();
    ASSERT_NE(toolBarRowPattern, nullptr);
    auto pageNode = pattern->GetPageNode();
    ASSERT_NE(pageNode, nullptr);
    auto pageFocusHub = pageNode->GetFocusHub();
    ASSERT_NE(pageFocusHub, nullptr);

    // 创建左侧行和右侧行
    auto leftRow = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto leftRowFocusHub = leftRow->GetFocusHub();
    auto rightRow = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto rightRowFocusHub = rightRow->GetFocusHub();
    toolBarRow->AddChild(leftRow, 1);
    toolBarRow->AddChild(rightRow, 2);

    // 创建按钮节点
    auto buttonNode1 = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonFocusHub1 = buttonNode1->GetFocusHub();
    auto buttonNode2 = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonFocusHub2 = buttonNode2->GetFocusHub();

    leftRow->AddChild(buttonNode1);

    // 测试左侧行和右侧行之间的焦点导航
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::TAB, buttonFocusHub1).Upgrade(), pageFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::RIGHT, buttonFocusHub1).Upgrade(), nullptr);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::SHIFT_TAB, rightRowFocusHub).Upgrade(), leftRowFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::LEFT, rightRowFocusHub).Upgrade(), leftRowFocusHub);

    leftRowFocusHub->SetCurrentFocus(true);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::SHIFT_TAB, leftRowFocusHub).Upgrade(), pageFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::LEFT, leftRowFocusHub).Upgrade(), nullptr);

    rootNode->RemoveChild(frameNode_);
}

/**
 * @tc.name: ToolBarRowPatternGetNextFocusNodeTest_005
 * @tc.desc: 测试 ToolBarRowPattern::GetNextFocusNode leftRow and rightRow - 反向场景
 * @tc.type: FUNC
 * @tc.require: AR000H0JIC AR000H0JIE
 * @tc.author:
 * @tc.level: Level1
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolBarRowPatternGetNextFocusNodeTest_005, TestSize.Level1)
{
    // 创建容器模态框
    CreateContainerModal();
    auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
    ASSERT_NE(pipeline, nullptr);
    auto rootNode = pipeline->rootNode_;
    ASSERT_NE(rootNode, nullptr);
    rootNode->AddChild(frameNode_, 0);

    // 获取组件和焦点 Hub
    auto pattern = frameNode_->GetPattern<ContainerModalPattern>();
    ASSERT_NE(pattern, nullptr);
    auto toolBarRow = pattern->GetCustomTitleRow();
    ASSERT_NE(toolBarRow, nullptr);
    auto toolBarRowPattern = toolBarRow->GetPattern<ToolBarRowPattern>();
    ASSERT_NE(toolBarRowPattern, nullptr);
    auto pageNode = pattern->GetPageNode();
    ASSERT_NE(pageNode, nullptr);
    auto pageFocusHub = pageNode->GetFocusHub();
    ASSERT_NE(pageFocusHub, nullptr);

    // 创建左侧行和右侧行
    auto leftRow = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto leftRowFocusHub = leftRow->GetFocusHub();
    auto rightRow = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto rightRowFocusHub = rightRow->GetFocusHub();
    toolBarRow->AddChild(leftRow, 1);
    toolBarRow->AddChild(rightRow, 2);

    // 创建按钮节点
    auto buttonNode1 = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonFocusHub1 = buttonNode1->GetFocusHub();
    auto buttonNode2 = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonFocusHub2 = buttonNode2->GetFocusHub();

    rightRow->AddChild(buttonNode2);

    // 测试右侧行中的焦点导航
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::TAB, buttonFocusHub1).Upgrade(), rightRowFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::RIGHT, buttonFocusHub1).Upgrade(), rightRowFocusHub);
    rightRowFocusHub->SetCurrentFocus(true);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::TAB, rightRowFocusHub).Upgrade(), pageFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::RIGHT, rightRowFocusHub).Upgrade(), nullptr);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::SHIFT_TAB, rightRowFocusHub).Upgrade(), pageFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::LEFT, rightRowFocusHub).Upgrade(), nullptr);

    rootNode->RemoveChild(frameNode_);
}

} // namespace OHOS::Ace::NG
