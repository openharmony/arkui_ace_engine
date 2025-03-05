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

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"

#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/menu/menu_divider/menu_divider_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string ITEM_CONTENT = "item";

RefPtr<FrameNode> CreateMenuItem(std::string content)
{
    MenuItemModelNG instance;
    MenuItemProperties itemOption;
    itemOption.content = content;
    instance.Create(itemOption);
    return AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
}

RefPtr<FrameNode> CreateMenuItemGroup()
{
    auto menuItemGroup = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ITEM_GROUP_ETS_TAG, 0, []() { return AceType::MakeRefPtr<MenuItemGroupPattern>(); });
    return menuItemGroup;
}
} // namespace

class MenuDividerTestNG : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void MenuDividerTestNG::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SelectTheme::TypeId()) {
            return AceType::MakeRefPtr<SelectTheme>();
        } else {
            return AceType::MakeRefPtr<MenuTheme>();
        }
    });
}

void MenuDividerTestNG::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: MenuDividerTest001
 * @tc.desc: Verify BottomDivider Create
 * @tc.type: FUNC
 */
HWTEST_F(MenuDividerTestNG, MenuDividerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menu item
     * @tc.expected: menu item assert not null
     */
    auto menuItem = CreateMenuItem(ITEM_CONTENT);
    auto menuItemPattern = menuItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    /**
     * @tc.steps: step2. get the bottom divider of menu item
     * @tc.expected: menu item assert not null
     */
    auto bottomDivider = menuItemPattern->GetBottomDivider();
    EXPECT_NE(bottomDivider, nullptr);
}

/**
 * @tc.name: MenuDividerTest002
 * @tc.desc: Verify UpdateMenuItemDivider with some abnormal value
 * @tc.type: FUNC
 */
HWTEST_F(MenuDividerTestNG, MenuDividerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Menu and some menu item
     */
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 0, AceType::MakeRefPtr<MenuPattern>(1, "targetTag", MenuType::MENU));
    auto firstItem = CreateMenuItem(ITEM_CONTENT);
    auto secondItem = CreateMenuItem(ITEM_CONTENT);
    firstItem->MountToParent(menuNode);
    secondItem->MountToParent(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    auto firstPattern = firstItem->GetPattern<MenuItemPattern>();
    /**
     * @tc.steps: step2. get the bottom divider of menu item
     * @tc.expected: bottom divider not null
     */
    auto bottomDivider = firstPattern->GetBottomDivider();
    ASSERT_NE(bottomDivider, nullptr);
    /**
     * @tc.steps: step3. call UpdateMenuItemDivider
     * @tc.expected: the bottom divider not have parent
     */
    menuPattern->UpdateMenuItemDivider();
    EXPECT_EQ(bottomDivider->GetParent(), nullptr);
    /**
     * @tc.steps: step3. make is select, call UpdateMenuItemDivider
     * @tc.expected: the bottom divider not have parent
     */
    menuPattern->isSelectMenu_ = true;
    menuPattern->UpdateMenuItemDivider();
    EXPECT_EQ(bottomDivider->GetParent(), nullptr);
    /**
     * @tc.steps: step3. push option into menu, call UpdateMenuItemDivider
     * @tc.expected: the bottom divider not have parent
     */
    menuPattern->options_.push_back(firstItem);
    menuPattern->options_.push_back(secondItem);
    menuPattern->UpdateMenuItemDivider();
    EXPECT_EQ(bottomDivider->GetParent(), nullptr);
}

/**
 * @tc.name: MenuDividerTest003
 * @tc.desc: Verify select EMBEDDED_IN_MENU mode UpdateMenuItemDivider
 * @tc.type: FUNC
 */
HWTEST_F(MenuDividerTestNG, MenuDividerTest003, TestSize.Level1)
{
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 0, AceType::MakeRefPtr<MenuPattern>(1, "targetTag", MenuType::MENU));
    /**
     * @tc.steps: step1. Building a reasonable structure
     */
    auto firstItem = CreateMenuItem(ITEM_CONTENT);
    auto secondItem = CreateMenuItem(ITEM_CONTENT);
    firstItem->MountToParent(menuNode);
    secondItem->MountToParent(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();

    auto firstPattern = firstItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(firstPattern, nullptr);
    /**
     * @tc.steps: step2. get the bottom divider of menu item
     * @tc.expected: menu item assert not null
     */
    auto bottomDivider = firstPattern->GetBottomDivider();
    ASSERT_NE(bottomDivider, nullptr);
    /**
     * @tc.steps: step3. push the option, set EMBEDDED_IN_MENU mode
     * @tc.expected: bottom divider mount to parent
     */
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    property->UpdateItemDividerMode(DividerMode::EMBEDDED_IN_MENU);
    menuPattern->isSelectMenu_ = true;
    menuPattern->options_.push_back(firstItem);
    menuPattern->options_.push_back(secondItem);
    menuPattern->UpdateMenuItemDivider();
    EXPECT_NE(bottomDivider->GetParent(), nullptr);
    /**
     * @tc.steps: step4. change divider mode
     * @tc.expected: bottom divider remove from parent
     */
    property->UpdateItemDividerMode(DividerMode::FLOATING_ABOVE_MENU);
    menuPattern->UpdateMenuItemDivider();
    EXPECT_EQ(bottomDivider->GetParent(), nullptr);
}

/**
 * @tc.name: MenuDividerTest004
 * @tc.desc: Verify the select hover status.
 * @tc.type: FUNC
 */
HWTEST_F(MenuDividerTestNG, MenuDividerTest004, TestSize.Level1)
{
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 0, AceType::MakeRefPtr<MenuPattern>(1, "targetTag", MenuType::MENU));
    /**
     * @tc.steps: step1. Building a reasonable structure
     */
    auto firstItem = CreateMenuItem(ITEM_CONTENT);
    auto secondItem = CreateMenuItem(ITEM_CONTENT);
    firstItem->MountToParent(menuNode);
    secondItem->MountToParent(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();

    auto firstPattern = firstItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(firstPattern, nullptr);
    auto secondPattern = secondItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(secondPattern, nullptr);
    /**
     * @tc.steps: step2. get the bottom divider of menu item
     * @tc.expected: menu item assert not null
     */
    auto bottomDivider = firstPattern->GetBottomDivider();
    ASSERT_NE(bottomDivider, nullptr);
    /**
     * @tc.steps: step3. push the option, set EMBEDDED_IN_MENU mode
     */
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    property->UpdateItemDividerMode(DividerMode::EMBEDDED_IN_MENU);
    menuPattern->isSelectMenu_ = true;
    menuPattern->options_.push_back(firstItem);
    menuPattern->options_.push_back(secondItem);
    menuPattern->UpdateMenuItemDivider();
    /**
     * @tc.steps: second menu item hover
     * @tc.expected: bottom divider as top divider, the hover status is true
     */
    secondPattern->UpdateDividerHoverStatus(true);
    auto topDivider = secondPattern->GetTopDivider();
    EXPECT_EQ(topDivider, bottomDivider);
    auto paintProperty = topDivider->GetPaintProperty<MenuDividerPaintProperty>();
    EXPECT_TRUE(paintProperty->GetTopHoverValue(false));
    secondPattern->UpdateDividerHoverStatus(false);
    firstPattern->UpdateDividerHoverStatus(true);
    paintProperty = bottomDivider->GetPaintProperty<MenuDividerPaintProperty>();
    EXPECT_TRUE(paintProperty->GetBottomHoverValue(false));
}

/**
 * @tc.name: MenuDividerTest005
 * @tc.desc: Verify the select selected status.
 * @tc.type: FUNC
 */
HWTEST_F(MenuDividerTestNG, MenuDividerTest005, TestSize.Level1)
{
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 0, AceType::MakeRefPtr<MenuPattern>(1, "targetTag", MenuType::MENU));
    /**
     * @tc.steps: step1. Building a reasonable structure
     */
    auto firstItem = CreateMenuItem(ITEM_CONTENT);
    auto secondItem = CreateMenuItem(ITEM_CONTENT);
    firstItem->MountToParent(menuNode);
    secondItem->MountToParent(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();

    auto firstPattern = firstItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(firstPattern, nullptr);
    auto secondPattern = secondItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(secondPattern, nullptr);
    /**
     * @tc.steps: step2. get the bottom divider of menu item
     * @tc.expected: menu item assert not null
     */
    auto bottomDivider = firstPattern->GetBottomDivider();
    ASSERT_NE(bottomDivider, nullptr);
    /**
     * @tc.steps: step3. push the option, set EMBEDDED_IN_MENU mode
     */
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    property->UpdateItemDividerMode(DividerMode::EMBEDDED_IN_MENU);
    menuPattern->isSelectMenu_ = true;
    menuPattern->options_.push_back(firstItem);
    menuPattern->options_.push_back(secondItem);
    menuPattern->UpdateMenuItemDivider();
    /**
     * @tc.steps: second menu item hover
     * @tc.expected: bottom divider as top divider, the hover status is true
     */
    secondPattern->UpdateDividerSelectedStatus(true);
    auto topDivider = secondPattern->GetTopDivider();
    EXPECT_EQ(topDivider, bottomDivider);
    auto paintProperty = topDivider->GetPaintProperty<MenuDividerPaintProperty>();
    EXPECT_TRUE(paintProperty->GetTopSelectedValue(false));
    secondPattern->UpdateDividerSelectedStatus(false);
    firstPattern->UpdateDividerSelectedStatus(true);
    paintProperty = bottomDivider->GetPaintProperty<MenuDividerPaintProperty>();
    EXPECT_TRUE(paintProperty->GetBottomSelectedValue(false));
}

/**
 * @tc.name: MenuDividerTest006
 * @tc.desc: Verify the select press status.
 * @tc.type: FUNC
 */
HWTEST_F(MenuDividerTestNG, MenuDividerTest006, TestSize.Level1)
{
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 0, AceType::MakeRefPtr<MenuPattern>(1, "targetTag", MenuType::MENU));
    /**
     * @tc.steps: step1. Building a reasonable structure
     */
    auto firstItem = CreateMenuItem(ITEM_CONTENT);
    auto secondItem = CreateMenuItem(ITEM_CONTENT);
    firstItem->MountToParent(menuNode);
    secondItem->MountToParent(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();

    auto firstPattern = firstItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(firstPattern, nullptr);
    auto secondPattern = secondItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(secondPattern, nullptr);
    /**
     * @tc.steps: step2. get the bottom divider of menu item
     * @tc.expected: menu item assert not null
     */
    auto bottomDivider = firstPattern->GetBottomDivider();
    ASSERT_NE(bottomDivider, nullptr);
    /**
     * @tc.steps: step3. push the option, set EMBEDDED_IN_MENU mode
     */
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    property->UpdateItemDividerMode(DividerMode::EMBEDDED_IN_MENU);
    menuPattern->isSelectMenu_ = true;
    menuPattern->options_.push_back(firstItem);
    menuPattern->options_.push_back(secondItem);
    menuPattern->UpdateMenuItemDivider();
    /**
     * @tc.steps: second menu item hover
     * @tc.expected: bottom divider as top divider, the hover status is true
     */
    secondPattern->UpdateDividerPressStatus(true);
    auto topDivider = secondPattern->GetTopDivider();
    EXPECT_EQ(topDivider, bottomDivider);
    auto paintProperty = topDivider->GetPaintProperty<MenuDividerPaintProperty>();
    EXPECT_TRUE(paintProperty->GetTopPressValue(false));
    secondPattern->UpdateDividerPressStatus(false);
    firstPattern->UpdateDividerPressStatus(true);
    paintProperty = bottomDivider->GetPaintProperty<MenuDividerPaintProperty>();
    EXPECT_TRUE(paintProperty->GetBottomPressValue(false));
}

/**
 * @tc.name: MenuDividerTest007
 * @tc.desc: Verify the UpdateMenuItemChildren
 * @tc.type: FUNC
 */
HWTEST_F(MenuDividerTestNG, MenuDividerTest007, TestSize.Level1)
{
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 0, AceType::MakeRefPtr<MenuPattern>(1, "targetTag", MenuType::MENU));
    /**
     * @tc.steps: step1. Building a reasonable structure
     */
    auto firstItem = CreateMenuItem(ITEM_CONTENT);
    auto secondItem = CreateMenuItem(ITEM_CONTENT);
    firstItem->MountToParent(menuNode);
    secondItem->MountToParent(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();

    auto firstPattern = firstItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(firstPattern, nullptr);
    auto secondPattern = secondItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(secondPattern, nullptr);
    /**
     * @tc.steps: step2. get the bottom divider of menu item
     * @tc.expected: menu item assert not null
     */
    auto bottomDivider = firstPattern->GetBottomDivider();
    ASSERT_NE(bottomDivider, nullptr);
    /**
     * @tc.steps: step3. push the option, set EMBEDDED_IN_MENU mode
     * @tc.expected: the divider will remove or add when mode change
     */
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    property->UpdateItemDividerMode(DividerMode::EMBEDDED_IN_MENU);
    auto uiNode = AceType::DynamicCast<UINode>(menuNode);
    RefPtr<UINode> previousNode = nullptr;
    menuPattern->UpdateMenuItemChildren(uiNode, previousNode);
    EXPECT_NE(bottomDivider->GetParent(), nullptr);
    property->UpdateItemDividerMode(DividerMode::FLOATING_ABOVE_MENU);
    menuPattern->UpdateMenuItemChildren(uiNode, previousNode);
    EXPECT_EQ(bottomDivider->GetParent(), nullptr);
}

/**
 * @tc.name: MenuDividerTest008
 * @tc.desc: Verify the UpdateMenuItemChildren with group
 * @tc.type: FUNC
 */
HWTEST_F(MenuDividerTestNG, MenuDividerTest008, TestSize.Level1)
{
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 0, AceType::MakeRefPtr<MenuPattern>(1, "targetTag", MenuType::MENU));
    /**
     * @tc.steps: step1. Building a reasonable structure
     */
    auto firstItem = CreateMenuItem(ITEM_CONTENT);
    auto secondItem = CreateMenuItem(ITEM_CONTENT);
    firstItem->MountToParent(menuNode);
    secondItem->MountToParent(menuNode);
    auto group = CreateMenuItemGroup();
    auto thirdItem = CreateMenuItem(ITEM_CONTENT);
    auto fourthItem = CreateMenuItem(ITEM_CONTENT);
    group->MountToParent(menuNode);
    thirdItem->MountToParent(group);
    fourthItem->MountToParent(fourthItem);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    auto firstPattern = firstItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(firstPattern, nullptr);
    auto secondPattern = secondItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(secondPattern, nullptr);
    /**
     * @tc.steps: step2. get the bottom divider of menu item
     * @tc.expected: menu item assert not null
     */
    auto bottomDivider = firstPattern->GetBottomDivider();
    ASSERT_NE(bottomDivider, nullptr);
    /**
     * @tc.steps: step3. set the group mode EMBEDDED_IN_MENU
     * @tc.expected: bottom divider will add when near group
     */
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    property->UpdateItemGroupDividerMode(DividerMode::EMBEDDED_IN_MENU);
    auto uiNode = AceType::DynamicCast<UINode>(menuNode);
    RefPtr<UINode> previousNode = nullptr;
    menuPattern->UpdateMenuItemChildren(uiNode, previousNode);
    EXPECT_EQ(bottomDivider->GetParent(), nullptr);
    bottomDivider = secondPattern->GetBottomDivider();
    EXPECT_NE(bottomDivider->GetParent(), nullptr);
}
} // namespace OHOS::Ace::NG