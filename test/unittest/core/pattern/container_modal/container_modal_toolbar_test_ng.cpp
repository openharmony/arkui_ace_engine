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
constexpr float TITLE_ITEM_HEIGT_S = 56.0; // 56vp height of title
constexpr float TITLE_ITEM_HEIGT_M = 64.0; // 64vp height of title
constexpr float TITLE_ITEM_HEIGT_L = 72.0; // 72vp height of title
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
 * @tc.name: ToolbarManager
 * @tc.desc: Test InitToolBarManager.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolbarManagerTest, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
}

/**
 * @tc.name: SetOnChangeCallback
 * @tc.desc: Test SetOnChangeCallback.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, SetOnChangeCallback, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    CreatePageWithAllNodes();
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);
    auto parentNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto toolbarItem =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 2, AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem);

    // test Valid Inputs
    titleMgr_->toolbarManager_->SetNavigationMode(NavigationMode::SPLIT);
    titleMgr_->SetOnChangeCallback();

    // test Invalid Inputs
    titleMgr_->toolbarManager_->SetNavigationMode(NavigationMode::STACK);
    titleMgr_->SetOnChangeCallback();
    EXPECT_TRUE(titleMgr_->itemsOnTree_.empty());
}

/**
 * @tc.name: SetToolbarBuilder
 * @tc.desc: Test SetToolbarBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, SetToolbarBuilder001, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    auto parentNode = FrameNode::CreateFrameNode("parentNode", 1, AceType::MakeRefPtr<Pattern>());
    std::function<RefPtr<UINode>()> builder = []() -> RefPtr<UINode> {
        auto ToolbarNode =
            FrameNode::GetOrCreateFrameNode(V2::TOOLBAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
        CHECK_NULL_RETURN(ToolbarNode, nullptr);
        auto ToolbarItemNode = FrameNode::GetOrCreateFrameNode(V2::TOOLBARITEM_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ToolBarItemPattern>(); });
        CHECK_NULL_RETURN(ToolbarItemNode, nullptr);
        ToolbarNode->AddChild(ToolbarItemNode);
        return ToolbarNode;
    };
    titleMgr_->SetToolbarBuilder(parentNode, builder);
    auto& items = titleMgr_->itemsWillOnTree_[parentNode];
    EXPECT_EQ(items.size(), 1);
    EXPECT_EQ(parentNode->removeToolbarItemCallbacks_.size(), 1);
    auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
    ASSERT_NE(pipeline, nullptr);
    pipeline->taskScheduler_->FlushAfterRenderTask();
}

/**
 * @tc.name: SetToolbarBuilder
 * @tc.desc: Test SetToolbarBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, SetToolbarBuilder002, TestSize.Level1)
{
    CreateContainerModal();
    CreatePageWithAllNodes();
    ASSERT_NE(titleMgr_, nullptr);
    std::function<RefPtr<UINode>()> builder = []() -> RefPtr<UINode> {
        auto ToolbarNode =
            FrameNode::GetOrCreateFrameNode(V2::TOOLBAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
        CHECK_NULL_RETURN(ToolbarNode, nullptr);
        auto ToolbarItemNode = FrameNode::GetOrCreateFrameNode(V2::TOOLBARITEM_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ToolBarItemPattern>(); });
        CHECK_NULL_RETURN(ToolbarItemNode, nullptr);
        ToolbarNode->AddChild(ToolbarItemNode);
        return ToolbarNode;
    };
    auto parentNode = FrameNode::CreateFrameNode("parentNode", 1, AceType::MakeRefPtr<Pattern>());
    auto tmpNode = FrameNode::GetOrCreateFrameNode(V2::TOOLBARITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ToolBarItemPattern>(); });
    titleMgr_->itemsWillOnTree_[parentNode].push_back(tmpNode);
    titleMgr_->SetToolbarBuilder(parentNode, builder);
    int ret = titleMgr_->itemsWillOnTree_[parentNode].size();
    EXPECT_EQ(parentNode->removeToolbarItemCallbacks_.size(), 1);
    titleMgr_->itemsWillOnTree_.clear();

    EXPECT_EQ(ret, 1);
    auto& removeToolbarItemCallbacks = parentNode->removeToolbarItemCallbacks_;
    for (auto [_, callback] : removeToolbarItemCallbacks) {
        if (callback) {
            callback();
        }
    }
    ret = titleMgr_->itemsWillOnTree_[parentNode].size();
    EXPECT_EQ(ret, 0);

    auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
    ASSERT_NE(pipeline, nullptr);
    pipeline->taskScheduler_->FlushAfterRenderTask();
}

/**
 * @tc.name: ParsePlacementType
 * @tc.desc: Test ParsePlacementType.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, ParsePlacementType, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    // clear itemsWillOnTree_ and itemWillAdd_
    titleMgr_->itemsWillOnTree_.clear();
    titleMgr_->itemWillAdd_.clear();

    // create toolbarItem and mountToParent
    auto noneNode = FrameNode::CreateFrameNode("NONE", 1, AceType::MakeRefPtr<Pattern>());
    auto toolbarItem =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 2, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->itemsWillOnTree_[noneNode].push_back(toolbarItem);
    titleMgr_->ParsePlacementType(noneNode);
    auto size = titleMgr_->itemsWillOnTree_[noneNode].size();
    EXPECT_EQ(size, 1);
    size = titleMgr_->itemWillAdd_[ItemPlacementType::NONE].size();
    EXPECT_EQ(size, 0);

    // init toolbarManager_ and set HasNavBar is false
    titleMgr_->InitToolBarManager();
    EXPECT_TRUE(titleMgr_->toolbarManager_);
    titleMgr_->toolbarManager_->SetHasNavBar(false);

    // clear itemsWillOnTree_ and itemWillAdd_
    titleMgr_->itemsWillOnTree_.clear();
    titleMgr_->itemWillAdd_.clear();

    auto navbarNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 4, AceType::MakeRefPtr<Pattern>());
    // create toolbarItem and mountToParent
    auto toolbarItem2 =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 5, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->itemsWillOnTree_[navbarNode].push_back(toolbarItem);
    CreatePageWithAllNodes();
    titleMgr_->SetHasNavOrSideBarNodes(true);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);
    titleMgr_->GetNavOrSideBarNodes(AceType::DynamicCast<FrameNode>(pageInfo.node));
    auto navigationNode = titleMgr_->navigationNode_.Upgrade();
    ASSERT_NE(navigationNode, nullptr);
    navigationNode->AddChild(navbarNode);
    titleMgr_->ParsePlacementType(navigationNode);
    size = titleMgr_->itemsWillOnTree_[navbarNode].size();
    EXPECT_EQ(size, 0);
    size = titleMgr_->itemWillAdd_[ItemPlacementType::NAV_BAR_START].size();
    EXPECT_EQ(size, 1);
}

/**
 * @tc.name: HandleToolbarItemList
 * @tc.desc: Test HandleToolbarItemList.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, HandleToolbarItemList, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    auto navigationNode = FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto navbarNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    navigationNode->AddChild(navbarNode);
    titleMgr_->navigationNode_ = AceType::WeakClaim(AceType::RawPtr(navigationNode));
    std::list<RefPtr<UINode>> items;
    auto toolbarNode =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 3, AceType::MakeRefPtr<ToolBarItemPattern>());
    auto invalidToolbarNode =
        FrameNode::CreateFrameNode("InvalidToolbarItem", 4, AceType::MakeRefPtr<Pattern>());
    items.push_back(toolbarNode);
    items.push_back(invalidToolbarNode);
    bool result = titleMgr_->HandleToolbarItemList(navbarNode, items);
    EXPECT_TRUE(result);
    auto invalidParent = FrameNode::CreateFrameNode("Invalid", 5, AceType::MakeRefPtr<Pattern>());
    result = titleMgr_->HandleToolbarItemList(invalidParent, items);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetItemTypeFromTag
 * @tc.desc: Test GetItemTypeFromTag.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, GetItemTypeFromTag, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // Test the navbar tag
    auto type = titleMgr_->GetItemTypeFromTag(V2::NAVBAR_ETS_TAG, 0);
    EXPECT_EQ(type, ItemPlacementType::NAV_BAR_START);
    type = titleMgr_->GetItemTypeFromTag(V2::NAVBAR_ETS_TAG, 1);
    EXPECT_EQ(type, ItemPlacementType::NAV_BAR_END);

    // Test the sidebar tag
    type = titleMgr_->GetItemTypeFromTag(V2::SIDE_BAR_ETS_TAG, 0);
    EXPECT_EQ(type, ItemPlacementType::SIDE_BAR_START);
    type = titleMgr_->GetItemTypeFromTag(V2::SIDE_BAR_ETS_TAG, 1);
    EXPECT_EQ(type, ItemPlacementType::SIDE_BAR_END);

    // Test the navdestination view tag
    type = titleMgr_->GetItemTypeFromTag(V2::NAVDESTINATION_VIEW_ETS_TAG, 0);
    EXPECT_EQ(type, ItemPlacementType::NAVDEST_START);
    type = titleMgr_->GetItemTypeFromTag(V2::NAVDESTINATION_VIEW_ETS_TAG, 1);
    EXPECT_EQ(type, ItemPlacementType::NAVDEST_END);

    // Test invalid tag
    type = titleMgr_->GetItemTypeFromTag("InvalidTag", 0);
    EXPECT_EQ(type, ItemPlacementType::NONE);
    type = titleMgr_->GetItemTypeFromTag("InvalidTag", 1);
    EXPECT_EQ(type, ItemPlacementType::NONE);
}

/**
 * @tc.name: RemoveAllToolbarItem
 * @tc.desc: Test RemoveAllToolbarItem.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, RemoveAllToolbarItem, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // test Valid Inputs
    auto parentNode = FrameNode::CreateFrameNode(
        V2::NAVBAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto toolbarItem = FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem);
    auto noParentToolbarItem = FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem);
    titleMgr_->itemsOnTree_[parentNode].push_back(noParentToolbarItem);
    titleMgr_->RemoveAllToolbarItem();
    EXPECT_TRUE(titleMgr_->itemsOnTree_.empty());
}

/**
 * @tc.name: RemoveToolbarItem
 * @tc.desc: Test RemoveToolbarItem.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, RemoveToolbarItem, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    auto parentNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto toolbarItem =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 2, AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem);
    auto noParentToolbarItem =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 3, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem);
    titleMgr_->itemsOnTree_[parentNode].push_back(noParentToolbarItem);
    titleMgr_->RemoveToolbarItem(parentNode);
    EXPECT_TRUE(titleMgr_->itemsOnTree_.empty());
}

/**
 * @tc.name: GetTagFromNode
 * @tc.desc: Test GetTagFromNode.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, GetTagFromNode001, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    auto navigationNode = FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto navbarNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    navigationNode->AddChild(navbarNode);
    titleMgr_->navigationNode_ = AceType::WeakClaim(AceType::RawPtr(navigationNode));
    std::string ret = titleMgr_->GetTagFromNode(navbarNode);
    EXPECT_EQ(ret, navbarNode->GetTag());

    auto navDestContentNode = FrameNode::CreateFrameNode("navDestContentNode", 3, AceType::MakeRefPtr<Pattern>());
    auto navDestNode = FrameNode::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG, 4, AceType::MakeRefPtr<Pattern>());
    navDestContentNode->AddChild(navDestNode);
    navigationNode->AddChild(navDestContentNode);
    ret = titleMgr_->GetTagFromNode(navDestNode);
    EXPECT_EQ(ret, navDestNode->GetTag());
}

/**
 * @tc.name: GetTagFromNode
 * @tc.desc: Test GetTagFromNode.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, GetTagFromNode002, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    auto navigationNode = FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto navbarNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    std::string ret = titleMgr_->GetTagFromNode(navbarNode);
    EXPECT_EQ(ret, "");

    auto navDestNode = FrameNode::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG, 4, AceType::MakeRefPtr<Pattern>());
    ret = titleMgr_->GetTagFromNode(navDestNode);
    EXPECT_EQ(ret, "");

    titleMgr_->navigationNode_ = AceType::WeakClaim(AceType::RawPtr(navigationNode));
    ret = titleMgr_->GetTagFromNode(navDestNode);
    EXPECT_EQ(ret, "");

    auto navDestContentNode = FrameNode::CreateFrameNode("navDestContentNode", 3, AceType::MakeRefPtr<Pattern>());
    navDestContentNode->AddChild(navDestNode);
    navigationNode->AddChild(navDestContentNode);
    ret = titleMgr_->GetTagFromNode(navDestNode);
    EXPECT_EQ(ret, navDestNode->GetTag());

    titleMgr_->navDestNode_ = AceType::WeakClaim(AceType::RawPtr(navDestNode));
    ret = titleMgr_->GetTagFromNode(navDestNode);
    EXPECT_EQ(ret, navDestNode->GetTag());
}

/**
 * @tc.name: AddToolbarItemToContainer
 * @tc.desc: Test AddToolbarItemToContainer.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AddToolbarItemToContainer, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    titleMgr_->toolbarManager_->SetHasNavBar(true);

    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->itemWillAdd_[ItemPlacementType::NAV_BAR_START].emplace_back(toolbarItem);
    titleMgr_->AddToolbarItemToContainer();
    EXPECT_EQ(titleMgr_->itemWillAdd_.size(), 1);
    EXPECT_EQ(titleMgr_->itemsWillOnTree_.size(), 0);

    titleMgr_->itemWillAdd_.clear();
    titleMgr_->itemsWillOnTree_.clear();

    titleMgr_->toolbarManager_->SetHasNavBar(false);
    auto toolbarItem1 = FrameNode::CreateFrameNode("toolbarItem", 2, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->itemWillAdd_[ItemPlacementType::NONE].emplace_back(toolbarItem1);
    titleMgr_->itemWillAdd_[ItemPlacementType::NAV_BAR_START].emplace_back(toolbarItem);
    titleMgr_->AddToolbarItemToContainer();
    EXPECT_EQ(titleMgr_->itemWillAdd_.size(), 2);
    EXPECT_EQ(titleMgr_->itemsWillOnTree_.size(), 0);
}

/**
 * @tc.name: UpdateTitleLayout_001
 * @tc.desc: Test UpdateTitleLayout.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateTitleLayout_001, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

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

    // test Valid Inputs
    auto parentNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto toolbarItem =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 2, AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem);

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
 * @tc.desc: Test UpdateTitleLayout.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateTitleLayout_002, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

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

    // test Valid Inputs
    auto parentNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto toolbarItem =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 2, AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem);

    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_START, toolbarItem);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem);

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
 * @tc.name: AddToolbarItemToRow_001
 * @tc.desc: Test AddToolbarItemToRow.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AddToolbarItemToRow_001, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

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

    // test Invalid Input
    bool result1 = titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_START, nullptr);
    EXPECT_FALSE(result1);

    bool result2 = titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAVDEST_START, nullptr);
    EXPECT_FALSE(result2);

    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    bool result3 = titleMgr_->AddToolbarItemToRow(ItemPlacementType::NONE, toolbarItem);
    EXPECT_FALSE(result3);

    titleMgr_->toolbarManager_->SetHasNavBar(false);
    bool result4 = titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_START, toolbarItem);
    EXPECT_FALSE(result4);

    bool result5 = titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_END, toolbarItem);
    EXPECT_FALSE(result5);

    titleMgr_->toolbarManager_->SetHasNavDest(false);
    bool result6 = titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAVDEST_START, toolbarItem);
    EXPECT_FALSE(result6);

    bool result7 = titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAVDEST_END, toolbarItem);
    EXPECT_FALSE(result7);
}

/**
 * @tc.name: AddToolbarItemToRow_002
 * @tc.desc: Test AddToolbarItemToRow.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AddToolbarItemToRow_002, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    auto customTitleRow = pattern_->GetCustomTitleRow();
    ASSERT_NE(customTitleRow, nullptr);

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

    // test Valid Inputs
    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_START, toolbarItem);
    EXPECT_EQ(titleMgr_->leftNavRow_->GetChildren().size(), 1);

    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_END, toolbarItem);
    EXPECT_EQ(titleMgr_->rightNavRow_->GetChildren().size(), 1);

    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAVDEST_START, toolbarItem);
    EXPECT_EQ(titleMgr_->leftNavDestRow_->GetChildren().size(), 1);

    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAVDEST_END, toolbarItem);
    EXPECT_EQ(titleMgr_->rightNavDestRow_->GetChildren().size(), 1);
}

/**
 * @tc.name: AddToolbarItemToSpecificRow
 * @tc.desc: Test AddToolbarItemToSpecificRow.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AddToolbarItemToSpecificRow, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // setting the Split Controller Information
    ToolbarInfo navDestInfo_ = { true, 1200.0f };
    titleMgr_->toolbarManager_->SetNavDestInfo(navDestInfo_);

    // valid Inputs
    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToSpecificRow(ItemPlacementType::NAVDEST_START, toolbarItem);
    EXPECT_EQ(titleMgr_->leftNavDestRow_->GetChildren().size(), 1);

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
 * @tc.desc: Test AddToolbarItemToNavBarStart.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AddToolbarItemToNavBarStart, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // setting the Split Controller Information
    titleMgr_->toolbarManager_->SetHasNavBar(true);

    // valid Inputs
    auto toolbarItem1 = FrameNode::CreateFrameNode(
        "toolbarItem1", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavBarStart(toolbarItem1);
    EXPECT_EQ(titleMgr_->leftNavRow_->GetChildren().size(), 1);

    auto toolbarItem2 = FrameNode::CreateFrameNode(
        "toolbarItem2", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavBarStart(toolbarItem2);
    EXPECT_EQ(titleMgr_->leftNavRow_->GetChildren().size(), 2);
}

/**
 * @tc.name: AddToolbarItemToNavBarEnd
 * @tc.desc: Test AddToolbarItemToNavBarEnd.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AddToolbarItemToNavBarEnd, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // setting the Split Controller Information
    titleMgr_->toolbarManager_->SetHasNavBar(true);

    // valid Inputs
    auto toolbarItem1 = FrameNode::CreateFrameNode(
        "toolbarItem", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavBarEnd(toolbarItem1);
    EXPECT_EQ(titleMgr_->rightNavRow_->GetChildren().size(), 1);

    auto toolbarItem2 = FrameNode::CreateFrameNode(
        "toolbarItem2", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavBarEnd(toolbarItem2);
    EXPECT_EQ(titleMgr_->rightNavRow_->GetChildren().size(), 2);
}

/**
 * @tc.name: AddToolbarItemToNavDestStart
 * @tc.desc: Test AddToolbarItemToNavDestStart.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AddToolbarItemToNavDestStart, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // setting the Split Controller Information
    titleMgr_->toolbarManager_->SetHasNavDest(true);

    // valid Inputs
    auto toolbarItem1 = FrameNode::CreateFrameNode(
        "toolbarItem1", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavDestStart(toolbarItem1);
    EXPECT_EQ(titleMgr_->leftNavDestRow_->GetChildren().size(), 1);

    auto toolbarItem2 = FrameNode::CreateFrameNode(
        "toolbarItem2", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavDestStart(toolbarItem2);
    EXPECT_EQ(titleMgr_->leftNavDestRow_->GetChildren().size(), 2);
}

/**
 * @tc.name: AddToolbarItemToNavDestEnd
 * @tc.desc: Test AddToolbarItemToNavDestEnd.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AddToolbarItemToNavDestEnd, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    // setting the Split Controller Information
    titleMgr_->toolbarManager_->SetHasNavDest(true);

    // valid Inputs
    auto toolbarItem1 = FrameNode::CreateFrameNode(
        "toolbarItem1", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavDestEnd(toolbarItem1);
    EXPECT_EQ(titleMgr_->rightNavDestRow_->GetChildren().size(), 1);

    auto toolbarItem2 = FrameNode::CreateFrameNode(
        "toolbarItem2", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavDestEnd(toolbarItem2);
    EXPECT_EQ(titleMgr_->rightNavDestRow_->GetChildren().size(), 2);
}

/**
 * @tc.name: AddNavBarRow_001
 * @tc.desc: Test AddNavBarRow.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AddNavBarRow_001, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    titleMgr_->toolbarManager_->SetHasNavBar(true);

    // adding a navigation bar row
    ToolbarInfo navBarInfo_ = { false, 500.0f };
    titleMgr_->toolbarManager_->SetNavBarInfo(navBarInfo_);
    EXPECT_EQ(navBarInfo_.isShow, false);
    titleMgr_->AddNavBarRow();
    EXPECT_EQ(titleMgr_->navbarRow_, nullptr);

    navBarInfo_ = { true, 500.0f };
    titleMgr_->toolbarManager_->SetNavBarInfo(navBarInfo_);
    EXPECT_EQ(navBarInfo_.isShow, true);
    titleMgr_->AddNavBarRow();
    ASSERT_NE(titleMgr_->navbarRow_, nullptr);
    EXPECT_EQ(titleMgr_->navbarRow_->GetChildren().size(), 0);

    // adding left navigation bar row
    EXPECT_EQ(titleMgr_->leftNavRow_, nullptr);
    titleMgr_->AddLeftNavRow();
    ASSERT_NE(titleMgr_->leftNavRow_, nullptr);
    EXPECT_EQ(titleMgr_->navbarRow_->GetChildren().size(), 1);
    titleMgr_->AddLeftNavRow();
    ASSERT_NE(titleMgr_->leftNavRow_, nullptr);
    EXPECT_EQ(titleMgr_->navbarRow_->GetChildren().size(), 1);

    // adding right navigation bar row
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
 * @tc.desc: Test AddNavBarRow.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AddNavBarRow_002, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    EXPECT_EQ(titleMgr_->title_->GetChildren().size(), 1);
    EXPECT_EQ(titleMgr_->navbarRow_, nullptr);

    titleMgr_->toolbarManager_->SetHasNavBar(true);
    titleMgr_->navbarRow_ =
        AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(false));

    // adding a navigation bar row
    titleMgr_->AddNavBarRow();
    ASSERT_NE(titleMgr_->navbarRow_, nullptr);
    EXPECT_EQ(titleMgr_->title_->GetChildren().size(), 1);
    EXPECT_EQ(titleMgr_->navbarRow_->GetChildren().size(), 0);

    // adding left navigation bar row
    titleMgr_->navbarRow_ = nullptr;
    titleMgr_->AddLeftNavRow();
    EXPECT_EQ(titleMgr_->leftNavRow_, nullptr);

    // adding right navigation bar row
    titleMgr_->AddRightNavRow();
    EXPECT_EQ(titleMgr_->rightNavRow_, nullptr);
}

/**
 * @tc.name: AddNavDestBarRow_001
 * @tc.desc: Test AddNavDestBarRow001.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AddNavDestBarRow_001, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    titleMgr_->toolbarManager_->SetHasNavDest(true);

    // adding navigation destination bar row
    ToolbarInfo navDestInfo_ = { false, 500.0f };
    titleMgr_->toolbarManager_->SetNavDestInfo(navDestInfo_);
    EXPECT_EQ(navDestInfo_.isShow, false);
    titleMgr_->AddNavDestBarRow();
    EXPECT_EQ(titleMgr_->navDestbarRow_, nullptr);

    navDestInfo_ = { true, 500.0f };
    titleMgr_->toolbarManager_->SetNavDestInfo(navDestInfo_);
    EXPECT_EQ(navDestInfo_.isShow, true);
    titleMgr_->AddNavDestBarRow();
    ASSERT_NE(titleMgr_->navDestbarRow_, nullptr);
    EXPECT_EQ(titleMgr_->navDestbarRow_->GetChildren().size(), 0);

    // adding left navigation destination row
    EXPECT_EQ(titleMgr_->leftNavDestRow_, nullptr);
    titleMgr_->AddLeftNavDestRow();
    ASSERT_NE(titleMgr_->leftNavDestRow_, nullptr);
    EXPECT_EQ(titleMgr_->navDestbarRow_->GetChildren().size(), 1);
    titleMgr_->AddLeftNavDestRow();
    ASSERT_NE(titleMgr_->leftNavDestRow_, nullptr);
    EXPECT_EQ(titleMgr_->navDestbarRow_->GetChildren().size(), 1);

    // adding right navigation destination row
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
 * @tc.desc: Test AddNavDestBarRow002.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AddNavDestBarRow_002, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    EXPECT_EQ(titleMgr_->title_->GetChildren().size(), 1);
    EXPECT_EQ(titleMgr_->navDestbarRow_, nullptr);

    titleMgr_->toolbarManager_->SetHasNavDest(true);
    titleMgr_->navDestbarRow_ =
        AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(false));

    // adding a navigation bar row
    titleMgr_->AddNavDestBarRow();
    ASSERT_NE(titleMgr_->navDestbarRow_, nullptr);
    EXPECT_EQ(titleMgr_->title_->GetChildren().size(), 1);
    EXPECT_EQ(titleMgr_->navDestbarRow_->GetChildren().size(), 0);

    // adding left navigation bar row
    titleMgr_->navDestbarRow_ = nullptr;
    titleMgr_->AddLeftNavDestRow();
    EXPECT_EQ(titleMgr_->leftNavDestRow_, nullptr);

    // adding right navigation bar row
    titleMgr_->AddRightNavDestRow();
    EXPECT_EQ(titleMgr_->rightNavDestRow_, nullptr);
}

/**
 * @tc.name: RemoveToolbarRowContainers_001
 * @tc.desc: Test RemoveToolbarRowContainers.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, RemoveToolbarRowContainers_001, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    titleMgr_->toolbarManager_->SetHasNavBar(true);
    titleMgr_->toolbarManager_->SetHasNavDest(true);

    // add toolbar row and remove
    titleMgr_->AddNavBarRow();
    ASSERT_NE(titleMgr_->navbarRow_, nullptr);
    titleMgr_->AddNavDestBarRow();
    ASSERT_NE(titleMgr_->navDestbarRow_, nullptr);
    titleMgr_->RemoveToolbarRowContainers();
    ASSERT_EQ(titleMgr_->navbarRow_, nullptr);
    ASSERT_EQ(titleMgr_->navDestbarRow_, nullptr);

    auto parentNode = FrameNode::CreateFrameNode(
        V2::NAVBAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto toolbarItem2 = FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    auto toolbarItem3 = FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem2);
    parentNode->AddChild(toolbarItem3);
    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_END, toolbarItem2);
    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAVDEST_END, toolbarItem3);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem2);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem3);
    titleMgr_->RemoveToolbarRowContainers();
    EXPECT_EQ(titleMgr_->title_->GetChildren().size(), 3);
    EXPECT_EQ(titleMgr_->navbarRow_->GetChildren().size(), 2);
    EXPECT_EQ(titleMgr_->navDestbarRow_->GetChildren().size(), 2);
}

/**
 * @tc.name: RemoveToolbarRowContainers_002
 * @tc.desc: Test RemoveToolbarRowContainers.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, RemoveToolbarRowContainers_002, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    titleMgr_->toolbarManager_->SetHasNavBar(true);
    titleMgr_->toolbarManager_->SetHasNavDest(true);

    // add toolbar row and remove
    auto parentNode = FrameNode::CreateFrameNode(
        V2::NAVBAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto toolbarItem2 = FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem2);
    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAV_BAR_END, toolbarItem2);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem2);
    titleMgr_->RemoveToolbarRowContainers();

    EXPECT_EQ(titleMgr_->title_->GetChildren().size(), 2);
    EXPECT_EQ(titleMgr_->navbarRow_->GetChildren().size(), 2);

    auto toolbarItem3 = FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem3);
    titleMgr_->AddToolbarItemToRow(ItemPlacementType::NAVDEST_END, toolbarItem3);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem3);
    titleMgr_->RemoveToolbarRowContainers();
    EXPECT_EQ(titleMgr_->title_->GetChildren().size(), 3);
    EXPECT_EQ(titleMgr_->navDestbarRow_->GetChildren().size(), 2);
}

/**
 * @tc.name: OnToolBarLayoutChange
 * @tc.desc: Test OnToolBarLayoutChange.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, OnToolBarLayoutChange, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    titleMgr_->hasNavOrSideBarNodes_ = true;

    // checking the layout change of toolbar
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

        titleMgr_->OnToolBarLayoutChange();
        auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
        ASSERT_NE(pipeline, nullptr);
        pipeline->taskScheduler_->FlushAfterRenderTask();
    }
    EXPECT_EQ(titleMgr_->navbarRow_, nullptr);
}

/**
 * @tc.name: AdjustTitleNodeWidth001
 * @tc.desc: Test AdjustTitleNodeWidth.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustTitleNodeWidth001, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    ToolbarInfo sideBarInfo_ = { true, 200.0f };
    ToolbarInfo sideBarDividerInfo_ = { true, 20.0f };

    titleMgr_->toolbarManager_->SetSideBarDividerInfo(sideBarDividerInfo_);
    titleMgr_->toolbarManager_->SetSideBarInfo(sideBarInfo_);

    auto customTitleRow = pattern_->GetCustomTitleRow();
    ASSERT_NE(customTitleRow, nullptr);

    auto parentNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto toolbarItem =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 2, AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem);
    titleMgr_->AdjustTitleNodeWidth();

    // Checking the width of the titleNode
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
 * @tc.name: AdjustTitleNodeWidth002
 * @tc.desc: Test AdjustTitleNodeWidth.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustTitleNodeWidth002, TestSize.Level1)
{
        CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    ToolbarInfo sideBarInfo_ = { true, 200.0f };
    ToolbarInfo sideBarDividerInfo_ = { true, 20.0f };

    titleMgr_->toolbarManager_->SetSideBarDividerInfo(sideBarDividerInfo_);
    titleMgr_->toolbarManager_->SetSideBarInfo(sideBarInfo_);

    auto customTitleRow = pattern_->GetCustomTitleRow();
    ASSERT_NE(customTitleRow, nullptr);

    titleMgr_->AdjustTitleNodeWidth();

    // Checking the width of the titleNode
    auto titleNode = AceType::DynamicCast<FrameNode>(customTitleRow->GetChildren().front());
    ASSERT_NE(titleNode, nullptr);
    LayoutConstraintF titleNodeconstraint;
    titleNode->Measure(titleNodeconstraint);
    auto titleNode2 = titleNode->GetGeometryNode();
    ASSERT_NE(titleNode2, nullptr);
    EXPECT_EQ(titleNode2->GetFrameSize().Width(), 0.0f);
}

/**
 * @tc.name: AdjustNavbarRowWidth_001
 * @tc.desc: Test AdjustNavbarRowWidth.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustNavbarRowWidth_001, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

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

    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavBarStart(toolbarItem);
    titleMgr_->AdjustNavbarRowWidth();

    // Checking the width of the navbarRow
    LayoutConstraintF constraint;
    titleMgr_->navbarRow_->Measure(constraint);
    auto navbarRowNode = titleMgr_->navbarRow_->GetGeometryNode();
    ASSERT_NE(navbarRowNode, nullptr);
    float navbarRowWidth = navbarRowNode->GetFrameSize().Width();
    EXPECT_EQ(navbarRowWidth, navBarInfo_.width);
}

/**
 * @tc.name: AdjustNavbarRowWidth_002
 * @tc.desc: Test AdjustNavbarRowWidth.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustNavbarRowWidth_002, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    ToolbarInfo sideBarInfo_ = { true, 200.0f };
    ToolbarInfo sideBarDividerInfo_ = { true, 20.0f };
    ToolbarInfo navBarInfo_ = { true, 500.0f };
    ToolbarInfo navBarDividerInfo_ = { true, 10.0f };
    ToolbarInfo navDestInfo_ = { true, 100.0f };

    titleMgr_->toolbarManager_->SetSideBarDividerInfo(sideBarDividerInfo_);
    titleMgr_->toolbarManager_->SetSideBarInfo(sideBarInfo_);
    titleMgr_->toolbarManager_->SetHasNavBar(true);
    titleMgr_->toolbarManager_->SetNavBarInfo(navBarInfo_);
    titleMgr_->toolbarManager_->SetNavBarDividerInfo(navBarDividerInfo_);
    titleMgr_->toolbarManager_->SetHasNavDest(true);
    titleMgr_->toolbarManager_->SetNavDestInfo(navDestInfo_);

    auto controlButtonsRow = pattern_->GetControlButtonRow();
    ASSERT_NE(controlButtonsRow, nullptr);
    auto controlButtonsWidth = pattern_->GetControlButtonRowWidth();

    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavBarStart(toolbarItem);
    titleMgr_->AdjustNavbarRowWidth();
    float navbarRowWidth = navDestInfo_.width + navBarInfo_.width - controlButtonsWidth.GetDimension().ConvertToPx();

    // Checking the width of the navbarRow
    LayoutConstraintF constraint;
    titleMgr_->navbarRow_->Measure(constraint);
    auto navbarRowNode = titleMgr_->navbarRow_->GetGeometryNode();
    ASSERT_NE(navbarRowNode, nullptr);
    float navbarRowRealWidth = navbarRowNode->GetFrameSize().Width();
    EXPECT_EQ(navbarRowRealWidth, navbarRowWidth);
}

/**
 * @tc.name: AdjustNavbarRowWidth_003
 * @tc.desc: Test AdjustNavbarRowWidth.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustNavbarRowWidth_003, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    ToolbarInfo sideBarInfo_ = { true, 200.0f };
    ToolbarInfo sideBarDividerInfo_ = { true, 20.0f };
    ToolbarInfo navBarInfo_ = { true, 500.0f };
    ToolbarInfo navBarDividerInfo_ = { true, 10.0f };
    ToolbarInfo navDestInfo_ = { true, 100.0f };

    titleMgr_->toolbarManager_->SetSideBarDividerInfo(sideBarDividerInfo_);
    titleMgr_->toolbarManager_->SetSideBarInfo(sideBarInfo_);
    titleMgr_->toolbarManager_->SetHasNavBar(true);
    titleMgr_->toolbarManager_->SetNavBarInfo(navBarInfo_);
    titleMgr_->toolbarManager_->SetNavBarDividerInfo(navBarDividerInfo_);
    titleMgr_->toolbarManager_->SetHasNavDest(true);
    titleMgr_->toolbarManager_->SetNavDestInfo(navDestInfo_);

    auto controlButtonsRow = pattern_->GetControlButtonRow();
    ASSERT_NE(controlButtonsRow, nullptr);
    auto controlButtonsWidth = pattern_->GetControlButtonRowWidth();
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavBarStart(toolbarItem);
    titleMgr_->AdjustNavbarRowWidth();

    // Checking the margin of the navbarRow
    auto navbarRowProperty = titleMgr_->navbarRow_->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(navbarRowProperty);
    MarginProperty navbarRowMargin;
    navbarRowMargin.left = CalcLength(controlButtonsWidth.GetDimension().ConvertToPx());
    navbarRowMargin.right = sideBarInfo_.isShow ? CalcLength(sideBarDividerInfo_.width) : CalcLength(0);
    navbarRowProperty->UpdateMargin(navbarRowMargin);
    titleMgr_->navbarRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    EXPECT_EQ(navbarRowMargin.left.value(), CalcLength(controlButtonsWidth.GetDimension().ConvertToPx()));
    EXPECT_EQ(navbarRowMargin.right.value(), CalcLength(sideBarDividerInfo_.width));
}

/**
 * @tc.name: AdjustNavbarRowWidth_004
 * @tc.desc: Test AdjustNavbarRowWidth.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustNavbarRowWidth_004, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

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

    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavBarStart(toolbarItem);
    titleMgr_->AdjustNavbarRowWidth();

    // Checking the margin of the navbarRow
    auto navbarRowProperty = titleMgr_->navbarRow_->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(navbarRowProperty);
    MarginProperty navbarRowMargin;
    navbarRowMargin.left = CalcLength(navBarDividerInfo_.width);
    navbarRowMargin.right = sideBarInfo_.isShow ? CalcLength(sideBarDividerInfo_.width) : CalcLength(0);
    navbarRowProperty->UpdateMargin(navbarRowMargin);
    titleMgr_->navbarRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    EXPECT_EQ(navbarRowMargin.left.value(), CalcLength(navBarDividerInfo_.width));
    EXPECT_EQ(navbarRowMargin.right.value(), CalcLength(sideBarDividerInfo_.width));
}

/**
 * @tc.name: AdjustNavbarRowWidth_005
 * @tc.desc: Test AdjustNavbarRowWidth.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustNavbarRowWidth_005, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    ToolbarInfo sideBarInfo_ = { true, 200.0f };
    ToolbarInfo sideBarDividerInfo_ = { true, 20.0f };
    ToolbarInfo navBarInfo_ = { true, 500.0f };
    ToolbarInfo navBarDividerInfo_ = { true, 10.0f };
    ToolbarInfo navDestInfo_ = { true, 100.0f };

    titleMgr_->toolbarManager_->SetSideBarDividerInfo(sideBarDividerInfo_);
    titleMgr_->toolbarManager_->SetSideBarInfo(sideBarInfo_);
    titleMgr_->toolbarManager_->SetHasNavBar(true);
    titleMgr_->toolbarManager_->SetNavBarInfo(navBarInfo_);
    titleMgr_->toolbarManager_->SetNavBarDividerInfo(navBarDividerInfo_);
    titleMgr_->toolbarManager_->SetHasNavDest(true);
    titleMgr_->toolbarManager_->SetNavDestInfo(navDestInfo_);

    auto controlButtonsRow = pattern_->GetControlButtonRow();
    ASSERT_NE(controlButtonsRow, nullptr);
    auto controlButtonsWidth = pattern_->GetControlButtonRowWidth();
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavBarStart(toolbarItem);
    titleMgr_->AdjustNavbarRowWidth();

    // Checking the margin of the navbarRow
    auto navbarRowProperty = titleMgr_->navbarRow_->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(navbarRowProperty);
    MarginProperty navbarRowMargin;
    navbarRowMargin.left = sideBarInfo_.isShow ? CalcLength(sideBarDividerInfo_.width) : CalcLength(0);
    navbarRowMargin.right = CalcLength(controlButtonsWidth.GetDimension().ConvertToPx());
    navbarRowProperty->UpdateMargin(navbarRowMargin);
    titleMgr_->navbarRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    EXPECT_EQ(navbarRowMargin.left.value(), CalcLength(sideBarDividerInfo_.width));
    EXPECT_EQ(navbarRowMargin.right.value(), CalcLength(controlButtonsWidth.GetDimension().ConvertToPx()));
}

/**
 * @tc.name: AdjustNavbarRowWidth_006
 * @tc.desc: Test AdjustNavbarRowWidth.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustNavbarRowWidth_006, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

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

    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavBarStart(toolbarItem);
    titleMgr_->AdjustNavbarRowWidth();

    // Checking the margin of the navbarRow
    auto navbarRowProperty = titleMgr_->navbarRow_->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(navbarRowProperty);
    MarginProperty navbarRowMargin;
    navbarRowMargin.left = sideBarInfo_.isShow ? CalcLength(sideBarDividerInfo_.width) : CalcLength(0);
    navbarRowMargin.right = CalcLength(navBarDividerInfo_.width);
    navbarRowProperty->UpdateMargin(navbarRowMargin);
    titleMgr_->navbarRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    EXPECT_EQ(navbarRowMargin.left.value(), CalcLength(sideBarDividerInfo_.width));
    EXPECT_EQ(navbarRowMargin.right.value(), CalcLength(navBarDividerInfo_.width));
}

/**
 * @tc.name: AdjustNavbarRowWidth_007
 * @tc.desc: Test AdjustNavbarRowWidth.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustNavbarRowWidth_007, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    std::vector<std::pair<bool, bool>> vec { { false, false }, { false, true }, { true, false }, { true, true } };
    ToolbarInfo sideBarInfo_ = { true, 200.0f };
    ToolbarInfo sideBarDividerInfo_ = { true, 20.0f };
    ToolbarInfo navBarInfo_ = { true, 500.0f };
    ToolbarInfo navBarDividerInfo_ = { true, 10.0f };
    ToolbarInfo navDestInfo_ = { true, 100.0f };

    for (auto pair : vec) {
        sideBarInfo_.isShow = pair.first;
        navDestInfo_.isShow = pair.second;
        titleMgr_->toolbarManager_->SetSideBarDividerInfo(sideBarDividerInfo_);
        titleMgr_->toolbarManager_->SetSideBarInfo(sideBarInfo_);
        titleMgr_->toolbarManager_->SetHasNavBar(true);
        titleMgr_->toolbarManager_->SetNavBarInfo(navBarInfo_);
        titleMgr_->toolbarManager_->SetNavBarDividerInfo(navBarDividerInfo_);
        titleMgr_->toolbarManager_->SetHasNavDest(true);
        titleMgr_->toolbarManager_->SetNavDestInfo(navDestInfo_);

        auto controlButtonsRow = pattern_->GetControlButtonRow();
        ASSERT_NE(controlButtonsRow, nullptr);
        auto controlButtonsWidth = pattern_->GetControlButtonRowWidth();
        AceApplicationInfo::GetInstance().isRightToLeft_ = true;

        auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
        titleMgr_->AddToolbarItemToNavBarStart(toolbarItem);
        titleMgr_->AdjustNavbarRowWidth();

        // Checking the margin of the navbarRow
        auto navbarRowProperty = titleMgr_->navbarRow_->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_VOID(navbarRowProperty);
        MarginProperty navbarRowMargin;
        navbarRowMargin.left = CalcLength(controlButtonsWidth.GetDimension().ConvertToPx());
        navbarRowMargin.right = sideBarInfo_.isShow ? CalcLength(sideBarDividerInfo_.width) : CalcLength(0);
        navbarRowProperty->UpdateMargin(navbarRowMargin);
        titleMgr_->navbarRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        EXPECT_EQ(navbarRowMargin.left.value(), CalcLength(controlButtonsWidth.GetDimension().ConvertToPx()));
        EXPECT_EQ(navbarRowMargin.right.value(), CalcLength(sideBarInfo_.isShow ? sideBarDividerInfo_.width : 0.0f));
    }
}

/**
 * @tc.name: AdjustNavDestRowWidth_001
 * @tc.desc: Test AdjustNavDestRowWidth.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustNavDestRowWidth_001, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

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

    auto controlButtonsRow = pattern_->GetControlButtonRow();
    ASSERT_NE(controlButtonsRow, nullptr);
    auto controlButtonsWidth = pattern_->GetControlButtonRowWidth();

    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavDestStart(toolbarItem);
    titleMgr_->AdjustNavDestRowWidth();

    // Checking the width of the navDestRow
    LayoutConstraintF constraint;
    titleMgr_->navDestbarRow_->Measure(constraint);
    auto navDestRowNode = titleMgr_->navDestbarRow_->GetGeometryNode();
    ASSERT_NE(navDestRowNode, nullptr);
    float navDestRowWidth = navDestRowNode->GetFrameSize().Width();
    EXPECT_EQ(navDestRowWidth, navDestInfo_.width - controlButtonsWidth.GetDimension().ConvertToPx());
}

/**
 * @tc.name: AdjustNavDestRowWidth_002
 * @tc.desc: Test AdjustNavDestRowWidth.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustNavDestRowWidth_002, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

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

    auto controlButtonsRow = pattern_->GetControlButtonRow();
    ASSERT_NE(controlButtonsRow, nullptr);
    auto controlButtonsWidth = pattern_->GetControlButtonRowWidth();

    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavDestStart(toolbarItem);
    titleMgr_->AdjustNavDestRowWidth();

    // Checking the margin of the navDestRow
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    float navDestbarRowLeftMargin = 0.0f;

    if (titleMgr_->navbarRow_) {
        navDestbarRowLeftMargin = navBarDividerInfo_.width;
    } else if (!sideBarInfo_.isShow && !navBarInfo_.isShow) {
        navDestbarRowLeftMargin = 0.0f;
    } else if (!sideBarInfo_.isShow) {
        navDestbarRowLeftMargin = navBarInfo_.width + navBarDividerInfo_.width;
    } else if (!navBarInfo_.isShow) {
        navDestbarRowLeftMargin = sideBarDividerInfo_.width;
    } else {
        navDestbarRowLeftMargin = sideBarDividerInfo_.width + navBarInfo_.width + navBarDividerInfo_.width;
    }
    auto navDestbarRowProperty = titleMgr_->navDestbarRow_->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(navDestbarRowProperty);
    MarginProperty navDestbarRowMargin;
    navDestbarRowMargin.left = CalcLength(controlButtonsWidth.GetDimension().ConvertToPx());
    navDestbarRowMargin.right = CalcLength(navDestbarRowLeftMargin);
    navDestbarRowProperty->UpdateMargin(navDestbarRowMargin);
    EXPECT_EQ(navDestbarRowMargin.left.value(), CalcLength(controlButtonsWidth.GetDimension().ConvertToPx()));
    EXPECT_EQ(navDestbarRowMargin.right.value(), CalcLength(navDestbarRowLeftMargin));
}

/**
 * @tc.name: AdjustNavDestRowWidth_003
 * @tc.desc: Test AdjustNavDestRowWidth.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustNavDestRowWidth_003, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

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

    auto controlButtonsRow = pattern_->GetControlButtonRow();
    ASSERT_NE(controlButtonsRow, nullptr);
    auto controlButtonsWidth = pattern_->GetControlButtonRowWidth();

    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavDestStart(toolbarItem);
    titleMgr_->AdjustNavDestRowWidth();

    // Checking the margin of the navDestRow
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    float navDestbarRowLeftMargin = 0.0f;

    if (titleMgr_->navbarRow_) {
        navDestbarRowLeftMargin = navBarDividerInfo_.width;
    } else if (!sideBarInfo_.isShow && !navBarInfo_.isShow) {
        navDestbarRowLeftMargin = 0.0f;
    } else if (!sideBarInfo_.isShow) {
        navDestbarRowLeftMargin = navBarInfo_.width + navBarDividerInfo_.width;
    } else if (!navBarInfo_.isShow) {
        navDestbarRowLeftMargin = sideBarDividerInfo_.width;
    } else {
        navDestbarRowLeftMargin = sideBarDividerInfo_.width + navBarInfo_.width + navBarDividerInfo_.width;
    }
    auto navDestbarRowProperty = titleMgr_->navDestbarRow_->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(navDestbarRowProperty);
    MarginProperty navDestbarRowMargin;
    navDestbarRowMargin.left = CalcLength(navDestbarRowLeftMargin);
    navDestbarRowMargin.right = CalcLength(controlButtonsWidth.GetDimension().ConvertToPx());
    navDestbarRowProperty->UpdateMargin(navDestbarRowMargin);
    EXPECT_EQ(navDestbarRowMargin.left.value(), CalcLength(navDestbarRowLeftMargin));
    EXPECT_EQ(navDestbarRowMargin.right.value(), CalcLength(controlButtonsWidth.GetDimension().ConvertToPx()));
}

/**
 * @tc.name: AdjustNavDestRowWidth_004
 * @tc.desc: Test AdjustNavDestRowWidth.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustNavDestRowWidth_004, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    std::vector<std::pair<bool, bool>> vec { { false, false }, { false, true }, { true, false }, { true, true } };
    ToolbarInfo sideBarInfo_ = { false, 200.0f };
    ToolbarInfo sideBarDividerInfo_ = { true, 20.0f };
    ToolbarInfo navBarInfo_ = { false, 500.0f };
    ToolbarInfo navBarDividerInfo_ = { true, 10.0f };
    ToolbarInfo navDestInfo_ = { true, 1200.0f };
    for (auto& pair : vec) {
        sideBarInfo_.isShow = pair.first;
        navBarInfo_.isShow = pair.second;
        titleMgr_->toolbarManager_->SetSideBarDividerInfo(sideBarDividerInfo_);
        titleMgr_->toolbarManager_->SetSideBarInfo(sideBarInfo_);
        titleMgr_->toolbarManager_->SetHasNavBar(true);
        titleMgr_->toolbarManager_->SetNavBarInfo(navBarInfo_);
        titleMgr_->toolbarManager_->SetNavBarDividerInfo(navBarDividerInfo_);
        titleMgr_->toolbarManager_->SetHasNavDest(true);
        titleMgr_->toolbarManager_->SetNavDestInfo(navDestInfo_);

        auto controlButtonsRow = pattern_->GetControlButtonRow();
        ASSERT_NE(controlButtonsRow, nullptr);
        auto controlButtonsWidth = pattern_->GetControlButtonRowWidth();

        auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
        titleMgr_->AddToolbarItemToNavDestStart(toolbarItem);
        titleMgr_->AdjustNavDestRowWidth();

        // Checking the margin of the navDestRow
        AceApplicationInfo::GetInstance().isRightToLeft_ = false;
        float navDestbarRowLeftMargin = 0.0f;

        if (titleMgr_->navbarRow_) {
            navDestbarRowLeftMargin = navBarDividerInfo_.width;
        } else if (!sideBarInfo_.isShow && !navBarInfo_.isShow) {
            navDestbarRowLeftMargin = 0.0f;
        } else if (!sideBarInfo_.isShow) {
            navDestbarRowLeftMargin = navBarInfo_.width + navBarDividerInfo_.width;
        } else if (!navBarInfo_.isShow) {
            navDestbarRowLeftMargin = sideBarDividerInfo_.width;
        } else {
            navDestbarRowLeftMargin = sideBarDividerInfo_.width + navBarInfo_.width + navBarDividerInfo_.width;
        }
        auto navDestbarRowProperty = titleMgr_->navDestbarRow_->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_VOID(navDestbarRowProperty);
        MarginProperty navDestbarRowMargin;
        navDestbarRowMargin.left = CalcLength(navDestbarRowLeftMargin);
        navDestbarRowMargin.right = CalcLength(controlButtonsWidth.GetDimension().ConvertToPx());
        navDestbarRowProperty->UpdateMargin(navDestbarRowMargin);
        EXPECT_EQ(navDestbarRowMargin.left.value(), CalcLength(navDestbarRowLeftMargin));
        EXPECT_EQ(navDestbarRowMargin.right.value(), CalcLength(controlButtonsWidth.GetDimension().ConvertToPx()));
    }
}

/**
 * @tc.name: UpdateToolbarShow
 * @tc.desc: Test UpdateToolbarShow
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateToolbarShow, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

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
 * @tc.name: AdjustContainerModalTitleHeight
 * @tc.desc: Test AdjustContainerModalTitleHeight.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustContainerModalTitleHeight, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    titleMgr_->toolbarManager_->SetHasNavBar(true);

    auto parentNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto toolbarItem =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 2, AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem);
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem);

    // test the title height of different toolbar items
    titleMgr_->toolbarItemMaxHeight_ = 40.0f;
    titleMgr_->AdjustContainerModalTitleHeight();
    EXPECT_EQ(pattern_->titleHeight_, Dimension(TITLE_ITEM_HEIGT_S, DimensionUnit::VP));

    titleMgr_->toolbarItemMaxHeight_ = 50.0f;
    titleMgr_->AdjustContainerModalTitleHeight();
    EXPECT_EQ(pattern_->titleHeight_, Dimension(TITLE_ITEM_HEIGT_M, DimensionUnit::VP));

    titleMgr_->toolbarItemMaxHeight_ = 60.0f;
    titleMgr_->AdjustContainerModalTitleHeight();
    EXPECT_EQ(pattern_->titleHeight_, Dimension(TITLE_ITEM_HEIGT_L, DimensionUnit::VP));
    // set the maximum height of toolbar items to 0
    titleMgr_->toolbarItemMaxHeight_ = 0;
    titleMgr_->AdjustContainerModalTitleHeight();
    EXPECT_EQ(pattern_->titleHeight_, CONTAINER_TITLE_HEIGHT);

    // set to default height if there are no toolbar items
    titleMgr_->itemsOnTree_.clear();
    titleMgr_->AdjustContainerModalTitleHeight();
    EXPECT_EQ(pattern_->titleHeight_, CONTAINER_TITLE_HEIGHT);
}

/**
 * @tc.name: AdjustContainerModalTitleHeight_002
 * @tc.desc: Test AdjustContainerModalTitleHeight.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustContainerModalTitleHeight_002, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(floatTitleMgr_, nullptr);

    floatTitleMgr_->InitToolBarManager();
    ASSERT_NE(floatTitleMgr_->toolbarManager_, nullptr);

    floatTitleMgr_->toolbarManager_->SetHasNavBar(true);

    auto parentNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto toolbarItem =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 2, AceType::MakeRefPtr<ToolBarItemPattern>());
    parentNode->AddChild(toolbarItem);
    floatTitleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem);

    // test the title height of different toolbar items
    floatTitleMgr_->toolbarItemMaxHeight_ = 40.0f;
    floatTitleMgr_->AdjustContainerModalTitleHeight();
    pattern_->InitTitleRowLayoutProperty(pattern_->GetFloatingTitleRow(), true);
    EXPECT_EQ(pattern_->titleHeight_, Dimension(TITLE_ITEM_HEIGT_S, DimensionUnit::VP));

    floatTitleMgr_->toolbarItemMaxHeight_ = 50.0f;
    floatTitleMgr_->AdjustContainerModalTitleHeight();
    EXPECT_EQ(pattern_->titleHeight_, Dimension(TITLE_ITEM_HEIGT_M, DimensionUnit::VP));

    floatTitleMgr_->toolbarItemMaxHeight_ = 60.0f;
    floatTitleMgr_->AdjustContainerModalTitleHeight();
    EXPECT_EQ(pattern_->titleHeight_, Dimension(TITLE_ITEM_HEIGT_L, DimensionUnit::VP));

    // set the maximum height of toolbar items to 0
    floatTitleMgr_->toolbarItemMaxHeight_ = 0;
    floatTitleMgr_->AdjustContainerModalTitleHeight();
    EXPECT_EQ(pattern_->titleHeight_, CONTAINER_TITLE_HEIGHT);

    // set to default height if there are no toolbar items
    floatTitleMgr_->itemsOnTree_.clear();
    floatTitleMgr_->AdjustContainerModalTitleHeight();
    EXPECT_EQ(pattern_->titleHeight_, CONTAINER_TITLE_HEIGHT);
}

/**
 * @tc.name: FocusEventTest_001
 * @tc.desc: Test PagePattern GetScopeFocusAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, FocusEventTest_001, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    auto pageNode = pattern_->GetPageNode();
    ASSERT_NE(pageNode, nullptr);
    EXPECT_EQ(pageNode->GetTag(), V2::PAGE_ETS_TAG);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    ASSERT_NE(pagePattern, nullptr);

    pattern_->SetIsHaveToolBar(false);
    EXPECT_EQ(pattern_->GetIsHaveToolBar(), false);
    auto focusAlgorithmFalse = pagePattern->GetScopeFocusAlgorithm();
    EXPECT_EQ(focusAlgorithmFalse.getNextFocusNode, nullptr);
}

/**
 * @tc.name: FocusEventTest_002
 * @tc.desc: Test ToolBarRowPattern GetScopeFocusAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, FocusEventTest_002, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    auto toolBarRow = pattern_->GetCustomTitleRow();
    ASSERT_NE(toolBarRow, nullptr);
    EXPECT_EQ(toolBarRow->GetTag(), V2::ROW_ETS_TAG);
    auto toolBarRowPattern = toolBarRow->GetPattern<ToolBarRowPattern>();
    ASSERT_NE(toolBarRowPattern, nullptr);

    auto focusAlgorithm = toolBarRowPattern->GetScopeFocusAlgorithm();
    ASSERT_NE(focusAlgorithm.getNextFocusNode, nullptr);
}

/**
 * @tc.name: UpdateSideTitleBgColor
 * @tc.desc: Test ContainerModalToolBar UpdateSideTitleBgColor.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateSideTitleBgColor, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    Color otherColor = Color::RED;
    Color baseColor = Color::GREEN;
    BlurStyle blurStyle = BlurStyle::THIN;
    Color blendColor = baseColor.BlendColorWithAlpha(otherColor);
    titleMgr_->UpdateSideTitleBgColor(otherColor, baseColor, blurStyle);
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
 * @tc.desc: Test ContainerModalToolBar UpdateTargetNodesBarMargin.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateTargetNodesBarMargin_001, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto toolbarMgr = titleMgr_->toolbarManager_;
    toolbarMgr->SetTitleHeight(Dimension(60.0f));
    titleMgr_->isUpdateTargetNode_ = false;
    titleMgr_->UpdateTargetNodesBarMargin(true);
    auto titleHeight = toolbarMgr->GetTitleHeight().ConvertToPx();
    EXPECT_TRUE(NearEqual(titleHeight, 60.0f));
    titleMgr_->isUpdateTargetNode_ = true;
    titleMgr_->UpdateTargetNodesBarMargin(true);
    titleHeight = toolbarMgr->GetTitleHeight().ConvertToPx();
    EXPECT_TRUE(NearEqual(titleHeight, 0.0f));
}

/**
 * @tc.name: UpdateTargetNodesBarMargin_002
 * @tc.desc: Test ContainerModalToolBar UpdateTargetNodesBarMargin.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateTargetNodesBarMargin_002, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    pattern_->activeColor_ = Color::TRANSPARENT;
    pattern_->inactiveColor_ = Color::TRANSPARENT;
    pattern_->isHaveToolBar_ = true;
    pattern_->isTitleShow_ = true;
    pattern_->isCustomColor_ = true;
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->isUpdateTargetNode_ = false;
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto toolbarMgr = titleMgr_->toolbarManager_;
    titleMgr_->UpdateTargetNodesBarMargin();
    auto isMoveUp = toolbarMgr->GetIsMoveUp();
    EXPECT_TRUE(isMoveUp);
    auto titleHeight = toolbarMgr->GetTitleHeight().ConvertToPx();
    EXPECT_TRUE(NearEqual(titleHeight, pattern_->titleHeight_.ConvertToPx()));
}

/**
 * @tc.name: ExpandStackNodeLayout
 * @tc.desc: Test ContainerModalToolBar ExpandStackNodeLayout.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, ExpandStackNodeLayout, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->ExpandStackNodeLayout();
    auto stackNode = pattern_->GetStackNode();
    ASSERT_NE(stackNode, nullptr);
    auto ctx = stackNode->GetRenderContext();
    ASSERT_NE(ctx, nullptr);
    auto zIndex = ctx->GetZIndexValue(ZINDEX_DEFAULT_VALUE);
    ASSERT_EQ(zIndex, -1);
    titleMgr_->ExpandStackNodeLayout(true);
    zIndex = ctx->GetZIndexValue(ZINDEX_DEFAULT_VALUE);
    ASSERT_EQ(zIndex, ZINDEX_DEFAULT_VALUE);
}

/**
 * @tc.name: ResetExpandStackNode
 * @tc.desc: Test ContainerModalToolBar ResetExpandStackNode.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, ResetExpandStackNode, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(titleMgr_, nullptr);
    std::vector<std::pair<bool, bool>> vec { { true, false }, { true, true }, { false, true }, { false, false } };
    for (auto pair : vec) {
        titleMgr_->isUpdateTargetNode_ = pair.first;
        titleMgr_->isFloating_ = pair.second;
        titleMgr_->ResetExpandStackNode();
    }
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
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
 * @tc.desc: Test ContainerModalToolBar SetCustomTitleRowBlurStyle.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, SetCustomTitleRowBlurStyle, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(titleMgr_, nullptr);
    auto title = titleMgr_->title_;
    ASSERT_NE(title, nullptr);
    auto ctx = title->GetRenderContext();
    ASSERT_NE(ctx, nullptr);
    auto ret = ctx->GetBackBlurStyle().has_value();
    EXPECT_FALSE(ret);
    BlurStyle blurStyle = BlurStyle::THIN;
    titleMgr_->SetCustomTitleRowBlurStyle(blurStyle);
    ret = ctx->GetBackBlurStyle().has_value();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: UpdateSidebarMargin
 * @tc.desc: Test ContainerModalToolBar UpdateSidebarMargin.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateSidebarMargin, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    auto toolbarMgr = titleMgr_->toolbarManager_;
    ASSERT_NE(toolbarMgr, nullptr);
    toolbarMgr->SetIsMoveUp(true);
    auto sideBarContainerNode = FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    toolbarMgr->SetSideBarContainerModel(sideBarContainerNode);
    titleMgr_->UpdateSidebarMargin();
    EXPECT_TRUE(titleMgr_->isUpdateTargetNode_);
}

/**
 * @tc.name: UpdateNavbarTitlebarMargin
 * @tc.desc: Test ContainerModalToolBar UpdateNavbarTitlebarMargin.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateNavbarTitlebarMargin, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    auto toolbarMgr = titleMgr_->toolbarManager_;
    ASSERT_NE(toolbarMgr, nullptr);
    toolbarMgr->SetIsMoveUp(true);
    auto navigation = FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto navBar = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    navigation->AddChild(navBar);
    toolbarMgr->SetNavBarNode(navBar);
    titleMgr_->UpdateNavbarTitlebarMargin();
    EXPECT_TRUE(titleMgr_->isUpdateTargetNode_);
}

/**
 * @tc.name: UpdateNavDestinationTitlebarMargin
 * @tc.desc: Test ContainerModalToolBar UpdateNavDestinationTitlebarMargin.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, UpdateNavDestinationTitlebarMargin, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    auto toolbarMgr = titleMgr_->toolbarManager_;
    ASSERT_NE(toolbarMgr, nullptr);
    toolbarMgr->SetIsMoveUp(true);

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

    toolbarMgr->SetNavDestNode(contentNode);
    titleMgr_->UpdateNavDestinationTitlebarMargin();
    EXPECT_TRUE(titleMgr_->isUpdateTargetNode_);
}

/**
 * @tc.name: OnChangeSideBarColor
 * @tc.desc: Test ToolbarManager OnChangeSideBarColor.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, OnChangeSideBarColor, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    Color otherColor = Color::RED;
    Color baseColor = Color::GREEN;
    BlurStyle blurStyle = BlurStyle::THIN;
    Color blendColor = baseColor.BlendColorWithAlpha(otherColor);
    titleMgr_->SetOnChangeCallback();
    auto toolbarMgr =  titleMgr_->toolbarManager_;
    toolbarMgr->SetSideBarColor(otherColor);
    toolbarMgr->SetSideBarContainerColor(baseColor);
    toolbarMgr->SetSideBarBlurStyle(blurStyle);
    titleMgr_->toolbarManager_->OnChangeSideBarColor();
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
 * @tc.name: GetNavOrSideBarNodes
 * @tc.desc: Test GetNavOrSideBarNodes.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodes, TestSize.Level1)
{
    CreateContainerModal();
    CreatePageWithAllNodes();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);
    bool ret = titleMgr_->GetNavOrSideBarNodes(AceType::DynamicCast<FrameNode>(pageInfo.node));
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: GetNavOrSideBarNodesParseChildren
 * @tc.desc: Test GetNavOrSideBarNodesParseChildren_EmptyPage.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodesParseChildren_EmptyPage, TestSize.Level1)
{
    CreateContainerModal();
    CreateEmptyPage();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);
    ASSERT_FALSE(titleMgr_->GetNavOrSideBarNodesParseChildren(pageInfo.node, pageInfo.width));
}

/**
 * @tc.name: GetNavOrSideBarNodesParseChildren
 * @tc.desc: Test GetNavOrSideBarNodesParseChildren_OnlySideBar.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodesParseChildren_OnlySideBar, TestSize.Level1)
{
    CreateContainerModal();
    CreatePageWithSideBarOnly();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);
    ASSERT_FALSE(titleMgr_->GetNavOrSideBarNodesParseChildren(pageInfo.node, pageInfo.width));
}

/**
 * @tc.name: GetNavOrSideBarNodesParseChildren
 * @tc.desc: Test GetNavOrSideBarNodesParseChildren_OnlyNavigation.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodesParseChildren_OnlyNavigation, TestSize.Level1)
{
    CreateContainerModal();
    CreatePageWithNavigationOnly();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);
    ASSERT_TRUE(titleMgr_->GetNavOrSideBarNodesParseChildren(pageInfo.node, pageInfo.width));
}

/**
 * @tc.name: GetNavOrSideBarNodesParseChildren
 * @tc.desc: Test GetNavOrSideBarNodesParseChildren_OnlyNavDest.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodesParseChildren_OnlyNavDest, TestSize.Level1)
{
    CreateContainerModal();
    CreatePageWithNavDestOnly();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);
    ASSERT_TRUE(titleMgr_->GetNavOrSideBarNodesParseChildren(pageInfo.node, pageInfo.width));
}

/**
 * @tc.name: GetNavOrSideBarNodesParseChildren
 * @tc.desc: Test GetNavOrSideBarNodesParseChildren_SideBarAndNavigation.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodesParseChildren_SideBarAndNavigation, TestSize.Level1)
{
    CreateContainerModal();
    CreatePageWithSideBarOnly();
    CreatePageWithNavigationOnly();
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);
    ASSERT_TRUE(titleMgr_->GetNavOrSideBarNodesParseChildren(pageInfo.node, pageInfo.width));
}

/**
 * @tc.name: GetNavOrSideBarNodesParseChildren
 * @tc.desc: Test GetNavOrSideBarNodesParseChildren_SideBarAndNavDest.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodesParseChildren_SideBarAndNavDest, TestSize.Level1)
{
    CreateContainerModal();
    CreatePageWithSideBarOnly();
    CreatePageWithNavDestOnly();
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);
    ASSERT_TRUE(titleMgr_->GetNavOrSideBarNodesParseChildren(pageInfo.node, pageInfo.width));
}

/**
 * @tc.name: GetNavOrSideBarNodesParseChildren
 * @tc.desc: Test GetNavOrSideBarNodesParseChildren_NavigationAndNavDest.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodesParseChildren_NavigationAndNavDest, TestSize.Level1)
{
    CreateContainerModal();
    CreatePageWithSideBarOnly();
    CreatePageWithNavDestOnly();
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);
    ASSERT_TRUE(titleMgr_->GetNavOrSideBarNodesParseChildren(pageInfo.node, pageInfo.width));
}

/**
 * @tc.name: GetNavOrSideBarNodesParseChildren
 * @tc.desc: Test GetNavOrSideBarNodesParseChildren_AllNodes.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, GetNavOrSideBarNodesParseChildren_AllNodes, TestSize.Level1)
{
    CreateContainerModal();
    CreatePageWithAllNodes();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    auto pageInfo = GetPageNodeAndWidth();
    ASSERT_NE(pageInfo.node, nullptr);
    ASSERT_TRUE(titleMgr_->GetNavOrSideBarNodesParseChildren(pageInfo.node, pageInfo.width));
}

/**
 * @tc.name: ToolBarItemCreate
 * @tc.desc: Test ToolBarItemCreate.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolBarItemCreate, TestSize.Level1)
{
    ToolBarItemModelNG model;
    model.SetIsFirstCreate(true);
    model.Create(VALUE);
    auto toolbaritemNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(toolbaritemNode, nullptr);
    EXPECT_EQ(toolbaritemNode->GetTag(), V2::TOOLBARITEM_ETS_TAG);
    auto toolbarNode = toolbaritemNode->GetParent();
    ASSERT_NE(toolbarNode, nullptr);
    EXPECT_EQ(toolbarNode->GetTag(), V2::TOOLBAR_ETS_TAG);
    EXPECT_EQ(toolbarNode->GetChildren().size(), 1);

    model.SetIsFirstCreate(false);
    model.Create(VALUE);
    EXPECT_EQ(toolbarNode->GetChildren().size(), 2);
}

/**
 * @tc.name: IsTragetSideBarNodeParseTest
 * @tc.desc: Test IsTragetSideBarNodeParse function with different scenarios.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, IsTragetSideBarNodeParseTest, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    RefPtr<FrameNode> nullFrameNode = nullptr;
    float pageWidth = 100.0f;
    float sideBarHeight = 0.0f;
    bool isSideBarFound = false;
    bool result = titleMgr_->IsTragetSideBarNodeParse(nullFrameNode, pageWidth, sideBarHeight, isSideBarFound);
    EXPECT_FALSE(result);

    auto nonSideBarNode = FrameNode::CreateFrameNode("NonSideBar", 1, AceType::MakeRefPtr<Pattern>());
    result = titleMgr_->IsTragetSideBarNodeParse(nonSideBarNode, pageWidth, sideBarHeight, isSideBarFound);
    EXPECT_FALSE(result);

    auto sideBarNode = FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(50.0f, 200.0f));
    sideBarNode->SetGeometryNode(geometryNode);
    result = titleMgr_->IsTragetSideBarNodeParse(sideBarNode, pageWidth, sideBarHeight, isSideBarFound);
    EXPECT_FALSE(result);

    geometryNode->SetFrameSize(SizeF(pageWidth, 300.0f));
    sideBarNode->SetGeometryNode(geometryNode);
    result = titleMgr_->IsTragetSideBarNodeParse(sideBarNode, pageWidth, sideBarHeight, isSideBarFound);
    EXPECT_TRUE(result);
    EXPECT_EQ(sideBarHeight, 300.0f);
    EXPECT_EQ(titleMgr_->sideBarNode_, sideBarNode);

    isSideBarFound = true;
    result = titleMgr_->IsTragetSideBarNodeParse(sideBarNode, pageWidth, sideBarHeight, isSideBarFound);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsTragetNavigationNodeParse_001
 * @tc.desc: Test IsTragetNavigationNodeParse.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, IsTragetNavigationNodeParse_001, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>());
    bool result = titleMgr_->IsTragetNavigationNodeParse(frameNode, 500.0f, 300.0f, true, false);
    EXPECT_FALSE(result);

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
 * @tc.desc: Test IsTragetNavigationNodeParse.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, IsTragetNavigationNodeParse_002, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    auto navigationNode =
        FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 2, AceType::MakeRefPtr<NavigationPattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(500.0f, 300.0f));
    navigationNode->SetGeometryNode(geometryNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationMode(NavigationMode::STACK);

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
 * @tc.desc: Test ToInitNavOrSideBarNode function with different scenarios.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, ToInitNavOrSideBarNodeTest, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    titleMgr_->sideBarNode_.Reset();
    titleMgr_->navigationNode_.Reset();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    titleMgr_->toolbarManager_->modifyDoneCallbackFuncs_.clear();
    titleMgr_->ToInitNavOrSideBarNode();
    EXPECT_EQ(titleMgr_->toolbarManager_->modifyDoneCallbackFuncs_.size(), 1);

    auto sideBarNode = FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    titleMgr_->sideBarNode_ = AceType::WeakClaim(AceType::RawPtr(sideBarNode));
    titleMgr_->navigationNode_.Reset();
    titleMgr_->ToInitNavOrSideBarNode();
    EXPECT_EQ(titleMgr_->toolbarManager_->modifyDoneCallbackFuncs_.size(), 2);

    sideBarNode = FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 2, AceType::MakeRefPtr<SideBarContainerPattern>());
    titleMgr_->sideBarNode_ = AceType::WeakClaim(AceType::RawPtr(sideBarNode));
    titleMgr_->navigationNode_.Reset();
    titleMgr_->ToInitNavOrSideBarNode();
    EXPECT_EQ(titleMgr_->toolbarManager_->modifyDoneCallbackFuncs_.size(), 3);

    titleMgr_->sideBarNode_.Reset();
    titleMgr_->navigationNode_.Reset();
    titleMgr_->ToInitNavOrSideBarNode();
    EXPECT_EQ(titleMgr_->toolbarManager_->modifyDoneCallbackFuncs_.size(), 4);

    auto navigationNode = FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 3, AceType::MakeRefPtr<Pattern>());
    titleMgr_->sideBarNode_.Reset();
    titleMgr_->navigationNode_ = AceType::WeakClaim(AceType::RawPtr(navigationNode));
    titleMgr_->ToInitNavOrSideBarNode();
    EXPECT_EQ(titleMgr_->toolbarManager_->modifyDoneCallbackFuncs_.size(), 5);

    titleMgr_->sideBarNode_.Reset();
    navigationNode =
        FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 4, AceType::MakeRefPtr<NavigationPattern>());
    titleMgr_->navigationNode_ = AceType::WeakClaim(AceType::RawPtr(navigationNode));
    titleMgr_->ToInitNavOrSideBarNode();
    EXPECT_EQ(titleMgr_->toolbarManager_->modifyDoneCallbackFuncs_.size(), 6);

    sideBarNode = FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 5, AceType::MakeRefPtr<SideBarContainerPattern>());
    titleMgr_->sideBarNode_ = AceType::WeakClaim(AceType::RawPtr(sideBarNode));
    navigationNode =
        FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 6, AceType::MakeRefPtr<NavigationPattern>());
    titleMgr_->navigationNode_ = AceType::WeakClaim(AceType::RawPtr(navigationNode));
    titleMgr_->ToInitNavOrSideBarNode();
    EXPECT_EQ(titleMgr_->toolbarManager_->modifyDoneCallbackFuncs_.size(), 7);
}

/**
 * @tc.name: ToolbarManager_OnChange
 * @tc.desc: Test ToolbarManager OnChange function.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolbarManager_OnChange, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    int32_t count = 0;
    titleMgr_->toolbarManager_->SetToolBarChangeCallback([&count]() { count++; });
    titleMgr_->toolbarManager_->SetToolBarChangeCallback(nullptr);
    titleMgr_->toolbarManager_->OnChange();
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: ToolbarManager_OnToolBarManagerModifyDone
 * @tc.desc: Test ToolbarManager OnToolBarManagerModifyDone function.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolbarManager_OnToolBarManagerModifyDone, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    int32_t count = 0;
    titleMgr_->toolbarManager_->SetModifyDoneCallback([&count]() { count++; });
    titleMgr_->toolbarManager_->SetModifyDoneCallback(nullptr);
    titleMgr_->toolbarManager_->OnToolBarManagerModifyDone();
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: ToolbarManager_OnChangeSideBarColor
 * @tc.desc: Test ToolbarManager OnChangeSideBarColor function.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolbarManager_OnChangeSideBarColor, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    int32_t count = 0;
    titleMgr_->toolbarManager_->SetSideBarColorChangeCallback(
        [&count](const Color&, const Color&, const BlurStyle&) { count++; });
    titleMgr_->toolbarManager_->OnChangeSideBarColor();
    EXPECT_EQ(count, 1);
    titleMgr_->toolbarManager_->SetSideBarColorChangeCallback(nullptr);
    titleMgr_->toolbarManager_->OnChangeSideBarColor();
}

/**
 * @tc.name: ToolbarManager_SetNavigationModeChangeCallback
 * @tc.desc: Test ToolbarManager SetNavigationModeChangeCallback function.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolbarManager_SetNavigationModeChangeCallback, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);
    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);
    int32_t count = 0;
    titleMgr_->toolbarManager_->SetNavigationModeChangeCallback([&count]() { count++; });
    titleMgr_->toolbarManager_->SetNavigationModeChangeCallback(nullptr);
    titleMgr_->toolbarManager_->OnNavigationModeChange();
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: FocusEventTest_003
 * @tc.desc: Test PagePattern GetNextFocusNode.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, FocusEventTest_003, TestSize.Level1)
{
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
    pageNode->AddChild(buttonNode1);
    toolBarRow->AddChild(buttonNode2, 0);
    toolBarRow->AddChild(buttonNode3, 1);
    ASSERT_NE(toolBarRowFocusHub->GetHeadOrTailChild(true), nullptr);
    EXPECT_EQ(pagePattern->GetNextFocusNode(FocusStep::UP, buttonFocusHub1).Upgrade(), buttonFocusHub2);
    EXPECT_EQ(pagePattern->GetNextFocusNode(FocusStep::TAB, buttonFocusHub1).Upgrade(), toolBarRowFocusHub);
    EXPECT_EQ(pagePattern->GetNextFocusNode(FocusStep::SHIFT_TAB, buttonFocusHub1).Upgrade(), toolBarRowFocusHub);
    EXPECT_EQ(pagePattern->GetNextFocusNode(FocusStep::LEFT, buttonFocusHub1).Upgrade(), nullptr);
    EXPECT_EQ(pagePattern->GetNextFocusNode(FocusStep::RIGHT, buttonFocusHub1).Upgrade(), nullptr);
    rootNode->RemoveChild(frameNode_);
}

/**
 * @tc.name: ToolBarRowPatternGetNextFocusNodeTest_001
 * @tc.desc: Test ToolBarRowPattern::GetNextFocusNode FocusStep::DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolBarRowPatternGetNextFocusNodeTest_001, TestSize.Level1)
{
    CreateContainerModal();
    auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
    ASSERT_NE(pipeline, nullptr);
    auto rootNode = pipeline->rootNode_;
    ASSERT_NE(rootNode, nullptr);
    rootNode->AddChild(frameNode_, 0);

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

    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::DOWN, toolBarRowFocusHub).Upgrade(), buttonFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::UP, toolBarRowFocusHub).Upgrade(), nullptr);
    rootNode->RemoveChild(frameNode_);
}

/**
 * @tc.name: ToolBarRowPatternGetNextFocusNodeTest_002
 * @tc.desc: Test ToolBarRowPattern::GetNextFocusNode leftRow.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolBarRowPatternGetNextFocusNodeTest_002, TestSize.Level1)
{
    CreateContainerModal();
    auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
    ASSERT_NE(pipeline, nullptr);
    auto rootNode = pipeline->rootNode_;
    ASSERT_NE(rootNode, nullptr);
    rootNode->AddChild(frameNode_, 0);

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

    auto leftRow = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto leftRowFocusHub = leftRow->GetFocusHub();
    toolBarRow->AddChild(leftRow, 1);

    auto buttonNode1 = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonFocusHub1 = buttonNode1->GetFocusHub();
    leftRow->AddChild(buttonNode1);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::TAB, buttonFocusHub1).Upgrade(), pageFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::RIGHT, buttonFocusHub1).Upgrade(), nullptr);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::SHIFT_TAB, buttonFocusHub1).Upgrade(), leftRowFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::LEFT, buttonFocusHub1).Upgrade(), leftRowFocusHub);

    rootNode->RemoveChild(frameNode_);
}

/**
 * @tc.name: ToolBarRowPatternGetNextFocusNodeTest_003
 * @tc.desc: Test ToolBarRowPattern::GetNextFocusNode rightRow.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolBarRowPatternGetNextFocusNodeTest_003, TestSize.Level1)
{
    CreateContainerModal();
    auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
    ASSERT_NE(pipeline, nullptr);
    auto rootNode = pipeline->rootNode_;
    ASSERT_NE(rootNode, nullptr);
    rootNode->AddChild(frameNode_, 0);

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

    auto rightRow = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto rightRowFocusHub = rightRow->GetFocusHub();
    toolBarRow->AddChild(rightRow, 2);

    auto buttonNode1 = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonFocusHub1 = buttonNode1->GetFocusHub();

    rightRow->AddChild(buttonNode1);

    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::TAB, buttonFocusHub1).Upgrade(), pageFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::RIGHT, buttonFocusHub1).Upgrade(), nullptr);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::SHIFT_TAB, buttonFocusHub1).Upgrade(), pageFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::LEFT, buttonFocusHub1).Upgrade(), nullptr);

    rootNode->RemoveChild(frameNode_);
}
/**
 * @tc.name: ToolBarRowPatternGetNextFocusNodeTest_004
 * @tc.desc: Test ToolBarRowPattern::GetNextFocusNode leftRow and rightRow.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolBarRowPatternGetNextFocusNodeTest_004, TestSize.Level1)
{
    CreateContainerModal();
    auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
    ASSERT_NE(pipeline, nullptr);
    auto rootNode = pipeline->rootNode_;
    ASSERT_NE(rootNode, nullptr);
    rootNode->AddChild(frameNode_, 0);

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

    auto leftRow = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto leftRowFocusHub = leftRow->GetFocusHub();
    auto rightRow = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto rightRowFocusHub = rightRow->GetFocusHub();
    toolBarRow->AddChild(leftRow, 1);
    toolBarRow->AddChild(rightRow, 2);

    auto buttonNode1 = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonFocusHub1 = buttonNode1->GetFocusHub();
    auto buttonNode2 = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonFocusHub2 = buttonNode2->GetFocusHub();
    leftRow->AddChild(buttonNode1);

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
 * @tc.desc: Test ToolBarRowPattern::GetNextFocusNode leftRow and rightRow.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, ToolBarRowPatternGetNextFocusNodeTest_005, TestSize.Level1)
{
    CreateContainerModal();
    auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
    ASSERT_NE(pipeline, nullptr);
    auto rootNode = pipeline->rootNode_;
    ASSERT_NE(rootNode, nullptr);
    rootNode->AddChild(frameNode_, 0);

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

    auto leftRow = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto leftRowFocusHub = leftRow->GetFocusHub();
    auto rightRow = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto rightRowFocusHub = rightRow->GetFocusHub();
    toolBarRow->AddChild(leftRow, 1);
    toolBarRow->AddChild(rightRow, 2);

    auto buttonNode1 = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonFocusHub1 = buttonNode1->GetFocusHub();
    auto buttonNode2 = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonFocusHub2 = buttonNode2->GetFocusHub();

    rightRow->AddChild(buttonNode2);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::TAB, buttonFocusHub1).Upgrade(), rightRowFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::RIGHT, buttonFocusHub1).Upgrade(), rightRowFocusHub);
    rightRowFocusHub->SetCurrentFocus(true);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::TAB, rightRowFocusHub).Upgrade(), pageFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::RIGHT, rightRowFocusHub).Upgrade(), nullptr);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::SHIFT_TAB, rightRowFocusHub).Upgrade(), pageFocusHub);
    EXPECT_EQ(toolBarRowPattern->GetNextFocusNode(FocusStep::LEFT, rightRowFocusHub).Upgrade(), nullptr);
    rootNode->RemoveChild(frameNode_);
}

/**
 * @tc.name: GetCurrentPageNode
 * @tc.desc: Test ContainerModelToolBar::GetCurrentPageNode
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, GetCurrentPageNode, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    // Test with nullptr node, expect nullptr return.
    auto ret = titleMgr_->GetCurrentPageNode(nullptr);
    EXPECT_EQ(ret, nullptr);

    // Test with non-page node, expect nullptr return.
    auto node = FrameNode::CreateFrameNode(
        "node", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ret = titleMgr_->GetCurrentPageNode(node);
    EXPECT_EQ(ret, nullptr);

    // Test with page node but no parent, expect nullptr return.
    auto page = FrameNode::CreateFrameNode(
        "page", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ret = titleMgr_->GetCurrentPageNode(page);
    EXPECT_EQ(ret, nullptr);

    // Test with page node and non-stage parent, expect nullptr return.
    auto parent = FrameNode::CreateFrameNode(
        "parent", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    parent->AddChild(page);
    ret = titleMgr_->GetCurrentPageNode(page);
    EXPECT_EQ(ret, nullptr);

    // Test with page node and stage parent, expect non-null return.
    auto stage = FrameNode::CreateFrameNode(
        "stage", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    parent->RemoveChild(page);
    stage->AddChild(page);
    ret = titleMgr_->GetCurrentPageNode(page);
    EXPECT_NE(ret, nullptr);
}
} // namespace OHOS::Ace::NG