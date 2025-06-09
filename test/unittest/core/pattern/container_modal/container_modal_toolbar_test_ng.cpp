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
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
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

    RefPtr<FrameNode> frameNode_;
    RefPtr<ContainerModalPattern> pattern_;
    RefPtr<LayoutProperty> layoutProperty_;
    RefPtr<ContainerModalAccessibilityProperty> accessibilityProperty_;
    RefPtr<ContainerModalToolBar> titleMgr_;
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
}

void ContainerModelToolBarTestNg::CreateTitleMgr()
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("frameNode", 0, AceType::MakeRefPtr<Pattern>());
    pattern_->SetToolbarBuilder(frameNode, nullptr);
    titleMgr_ = pattern_->titleMgr_;
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
    return AceType::MakeRefPtr<FrameNode>("content", 0, AceType::MakeRefPtr<Pattern>());
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
 * @tc.name: SetToolbarBuilder
 * @tc.desc: Test SetToolbarBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, SetToolbarBuilder, TestSize.Level1)
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
    titleMgr_->ParsePlacementType();
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

    // create navigation and navbar
    auto navigationNode = FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 3, AceType::MakeRefPtr<Pattern>());
    auto navbarNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG, 4, AceType::MakeRefPtr<Pattern>());
    navigationNode->AddChild(navbarNode);
    titleMgr_->navigationNode_ = AceType::WeakClaim(AceType::RawPtr(navigationNode));

    // create toolbarItem and mountToParent
    auto toolbarItem2 =
        FrameNode::CreateFrameNode(V2::TOOLBARITEM_ETS_TAG, 5, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->itemsWillOnTree_[navbarNode].push_back(toolbarItem);
    titleMgr_->ParsePlacementType();
    size = titleMgr_->itemsWillOnTree_[navbarNode].size();
    EXPECT_EQ(size, 1);
    size = titleMgr_->itemWillAdd_[ItemPlacementType::NAV_BAR_START].size();
    EXPECT_EQ(size, 0);
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
    items.push_back(toolbarNode);
    bool result = titleMgr_->HandleToolbarItemList(navbarNode, items);
    EXPECT_TRUE(result);
    auto invalidParent = FrameNode::CreateFrameNode("Invalid", 4, AceType::MakeRefPtr<Pattern>());
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
    titleMgr_->itemsOnTree_[parentNode].push_back(toolbarItem);
    titleMgr_->RemoveToolbarItem(parentNode);
    EXPECT_TRUE(titleMgr_->itemsOnTree_.empty());
}

/**
 * @tc.name: GetTagFromNode
 * @tc.desc: Test GetTagFromNode.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, GetTagFromNode, TestSize.Level1)
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
    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavBarStart(toolbarItem);
    EXPECT_EQ(titleMgr_->leftNavRow_->GetChildren().size(), 1);
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
    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavBarEnd(toolbarItem);
    EXPECT_EQ(titleMgr_->rightNavRow_->GetChildren().size(), 1);
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
    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavDestStart(toolbarItem);
    EXPECT_EQ(titleMgr_->leftNavDestRow_->GetChildren().size(), 1);
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
    auto toolbarItem = FrameNode::CreateFrameNode("toolbarItem", 1, AceType::MakeRefPtr<ToolBarItemPattern>());
    titleMgr_->AddToolbarItemToNavDestEnd(toolbarItem);
    EXPECT_EQ(titleMgr_->rightNavDestRow_->GetChildren().size(), 1);
}

/**
 * @tc.name: AddNavBarRow
 * @tc.desc: Test AddNavBarRow.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AddNavBarRow, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    titleMgr_->toolbarManager_->SetHasNavBar(true);

    // adding a navigation bar row
    titleMgr_->AddNavBarRow();
    ASSERT_NE(titleMgr_->navbarRow_, nullptr);
    EXPECT_EQ(titleMgr_->navbarRow_->GetChildren().size(), 0);

    // adding left navigation bar row
    titleMgr_->AddLeftNavRow();
    ASSERT_NE(titleMgr_->leftNavRow_, nullptr);

    // adding right navigation bar row
    titleMgr_->AddRightNavRow();
    ASSERT_NE(titleMgr_->rightNavRow_, nullptr);
}

/**
 * @tc.name: AddNavDestBarRow
 * @tc.desc: Test AddNavDestBarRow.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AddNavDestBarRow, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(titleMgr_, nullptr);

    titleMgr_->InitToolBarManager();
    ASSERT_NE(titleMgr_->toolbarManager_, nullptr);

    titleMgr_->toolbarManager_->SetHasNavDest(true);

    // adding navigation destination bar row
    titleMgr_->AddNavDestBarRow();
    ASSERT_NE(titleMgr_->navDestbarRow_, nullptr);
    EXPECT_EQ(titleMgr_->navDestbarRow_->GetChildren().size(), 0);

    // adding left navigation destination row
    titleMgr_->AddLeftNavDestRow();
    ASSERT_NE(titleMgr_->leftNavDestRow_, nullptr);

    // adding right navigation destination row
    titleMgr_->AddRightNavDestRow();
    ASSERT_NE(titleMgr_->rightNavDestRow_, nullptr);
}

/**
 * @tc.name: RemoveToolbarRowContainers
 * @tc.desc: Test RemoveToolbarRowContainers.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, RemoveToolbarRowContainers, TestSize.Level1)
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
}

/**
 * @tc.name: AdjustTitleNodeWidth
 * @tc.desc: Test AdjustTitleNodeWidth.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, AdjustTitleNodeWidth, TestSize.Level1)
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
    titleMgr_->InitToolBarManager();
    titleMgr_->isUpdateTargetNode_ = true;
    titleMgr_->ResetExpandStackNode();
    EXPECT_FALSE(titleMgr_->isUpdateTargetNode_);
    auto isMoveUp = titleMgr_->toolbarManager_->GetIsMoveUp();
    EXPECT_FALSE(isMoveUp);
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
} // namespace OHOS::Ace::NG