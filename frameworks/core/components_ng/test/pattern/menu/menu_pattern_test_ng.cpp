/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_view.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_pattern.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TARGET_ID = 3;
constexpr MenuType TYPE = MenuType::MENU;
class MenuPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void MenuPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void MenuPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void MenuPatternTestNg::SetUp() {}
void MenuPatternTestNg::TearDown() {}

/**
 * @tc.name: MenuPatternTestNg001
 * @tc.desc: Verify RegisterOnClick.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg001, TestSize.Level1)
{
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, TYPE);
    std::string type = "1";
    TouchEventInfo info(type);
    menuPattern->RegisterOnClick();
    EXPECT_TRUE(info.GetTouches().empty());
}

/**
 * @tc.name: MenuPatternTestNg002
 * @tc.desc: Verify RegisterOnClick.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg002, TestSize.Level1)
{
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, TYPE);
    std::string type = "1";
    TouchType touchType = TouchType::UP;
    TouchEventInfo info(type);
    TouchLocationInfo locationInfo(TARGET_ID);
    Offset globalLocation(1, 1);
    locationInfo.SetTouchType(touchType);
    auto touchLocationInfo = locationInfo.SetGlobalLocation(globalLocation);
    info.touches_.emplace_back(touchLocationInfo);
    menuPattern->RegisterOnClick();
    EXPECT_FALSE(info.GetTouches().empty());
    EXPECT_TRUE(info.GetTouches().front().GetTouchType() == TouchType::UP);
}

/**
 * @tc.name: MenuPatternTestNg003
 * @tc.desc: Verify RegisterOnClick.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg003, TestSize.Level1)
{
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, TYPE);
    std::string type = "1";
    TouchType touchType = TouchType::UP;
    TouchEventInfo info(type);
    TouchLocationInfo locationInfo(TARGET_ID);
    Offset globalLocation(1, 1);
    locationInfo.SetTouchType(touchType);
    auto touchLocationInfo = locationInfo.SetGlobalLocation(globalLocation);
    info.touches_.emplace_back(touchLocationInfo);
    menuPattern->type_ = MenuType::CONTEXT_MENU;
    menuPattern->RegisterOnClick();
    EXPECT_FALSE(info.GetTouches().empty());
    EXPECT_TRUE(info.GetTouches().front().GetTouchType() == TouchType::UP);
}

/**
 * @tc.name: MenuPatternTestNg004
 * @tc.desc: Verify RegisterOnClick.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg004, TestSize.Level1)
{
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, TYPE);
    std::string type = "1";
    TouchEventInfo info(type);
    TouchLocationInfo locationInfo(TARGET_ID);
    Offset globalLocation(1, 1);
    auto touchLocationInfo = locationInfo.SetGlobalLocation(globalLocation);
    info.touches_.emplace_back(touchLocationInfo);
    menuPattern->RegisterOnClick();
    EXPECT_FALSE(info.GetTouches().empty());
    EXPECT_TRUE(info.GetTouches().front().GetTouchType() == TouchType::UNKNOWN);
}

/**
 * @tc.name: MenuPatternTestNg005
 * @tc.desc: Verify RegisterOnClick.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg005, TestSize.Level1)
{
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, TYPE);
    std::string type = "1";
    TouchEventInfo info(type);
    TouchType touchType = TouchType::UP;
    TouchLocationInfo locationInfo(TARGET_ID);
    locationInfo.SetTouchType(touchType);
    menuPattern->RegisterOnClick();
    EXPECT_TRUE(info.GetTouches().empty());
    EXPECT_FALSE(info.GetTouches().front().GetTouchType() == TouchType::UP);
}

/**
 * @tc.name: MenuPatternTestNg006
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg006, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    MenuView::Create();
    MenuView::SetFontSize(Dimension(25.0));
    MenuView::SetFontColor(Color::RED);
    MenuView::SetFontWeight(FontWeight::BOLD);

    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    // call UpdateMenuItemChildren
    menuPattern->OnModifyDone();

    ASSERT_TRUE(layoutProperty->GetFontSize().has_value());
    EXPECT_EQ(layoutProperty->GetFontSize().value(), Dimension(25.0));
    ASSERT_TRUE(layoutProperty->GetFontWeight().has_value());
    EXPECT_EQ(layoutProperty->GetFontWeight().value(), FontWeight::BOLD);
    ASSERT_TRUE(layoutProperty->GetFontColor().has_value());
    EXPECT_EQ(layoutProperty->GetFontColor().value(), Color::RED);
}

/**
 * @tc.name: MenuPatternTestNg007
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg007, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    MenuView::Create();
    MenuView::SetFontSize(Dimension(25.0));
    MenuView::SetFontColor(Color::RED);
    MenuView::SetFontWeight(FontWeight::BOLD);

    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    MenuItemView::Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    itemPattern->OnModifyDone();
    itemNode->MountToParent(menuNode);
    itemNode->OnMountToParentDone();

    // call UpdateMenuItemChildren
    menuPattern->OnModifyDone();

    auto contentNode = itemPattern->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto textProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);
    ASSERT_TRUE(textProperty->GetContent().has_value());
    EXPECT_EQ(textProperty->GetContent().value(), "content");
    ASSERT_TRUE(textProperty->GetFontSize().has_value());
    EXPECT_EQ(textProperty->GetFontSize().value(), Dimension(25.0));
    ASSERT_TRUE(textProperty->GetFontWeight().has_value());
    EXPECT_EQ(textProperty->GetFontWeight().value(), FontWeight::BOLD);
    ASSERT_TRUE(textProperty->GetTextColor().has_value());
    EXPECT_EQ(textProperty->GetTextColor().value(), Color::RED);

    auto labelNode = itemPattern->GetLabelNode();
    ASSERT_NE(labelNode, nullptr);
    auto labelProperty = labelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(labelProperty, nullptr);
    ASSERT_TRUE(labelProperty->GetContent().has_value());
    EXPECT_EQ(labelProperty->GetContent().value(), "label");
    ASSERT_TRUE(labelProperty->GetFontSize().has_value());
    EXPECT_EQ(labelProperty->GetFontSize().value(), Dimension(25.0));
    ASSERT_TRUE(labelProperty->GetFontWeight().has_value());
    EXPECT_EQ(labelProperty->GetFontWeight().value(), FontWeight::BOLD);
    ASSERT_TRUE(labelProperty->GetTextColor().has_value());
    EXPECT_EQ(labelProperty->GetTextColor().value(), Color::RED);
}

/**
 * @tc.name: MenuPatternTestNg008
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg008, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    MenuView::Create();
    MenuView::SetFontSize(Dimension(25.0));
    MenuView::SetFontColor(Color::RED);
    MenuView::SetFontWeight(FontWeight::BOLD);

    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    MenuItemView::Create(itemOption);
    MenuItemView::SetFontSize(Dimension(35.0));
    MenuItemView::SetFontColor(Color::BLUE);
    MenuItemView::SetFontWeight(FontWeight::LIGHTER);
    MenuItemView::SetLabelFontSize(Dimension(40.0));
    MenuItemView::SetLabelFontColor(Color::GRAY);
    MenuItemView::SetLabelFontWeight(FontWeight::LIGHTER);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    itemPattern->OnModifyDone();
    itemNode->MountToParent(menuNode);
    itemNode->OnMountToParentDone();

    // call UpdateMenuItemChildren
    menuPattern->OnModifyDone();

    auto contentNode = itemPattern->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto textProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);
    ASSERT_TRUE(textProperty->GetContent().has_value());
    EXPECT_EQ(textProperty->GetContent().value(), "content");
    ASSERT_TRUE(textProperty->GetFontSize().has_value());
    EXPECT_EQ(textProperty->GetFontSize().value(), Dimension(35.0));
    ASSERT_TRUE(textProperty->GetFontWeight().has_value());
    EXPECT_EQ(textProperty->GetFontWeight().value(), FontWeight::LIGHTER);
    ASSERT_TRUE(textProperty->GetTextColor().has_value());
    EXPECT_EQ(textProperty->GetTextColor().value(), Color::BLUE);

    auto labelNode = itemPattern->GetLabelNode();
    ASSERT_NE(labelNode, nullptr);
    auto labelProperty = labelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(labelProperty, nullptr);
    ASSERT_TRUE(labelProperty->GetContent().has_value());
    EXPECT_EQ(labelProperty->GetContent().value(), "label");
    ASSERT_TRUE(labelProperty->GetFontSize().has_value());
    EXPECT_EQ(labelProperty->GetFontSize().value(), Dimension(40.0));
    ASSERT_TRUE(labelProperty->GetFontWeight().has_value());
    EXPECT_EQ(labelProperty->GetFontWeight().value(), FontWeight::LIGHTER);
    ASSERT_TRUE(labelProperty->GetTextColor().has_value());
    EXPECT_EQ(labelProperty->GetTextColor().value(), Color::GRAY);
}

/**
 * @tc.name: MenuPatternTestNg009
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg009, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    MenuView::Create();
    MenuView::SetFontSize(Dimension(25.0));
    MenuView::SetFontColor(Color::RED);
    MenuView::SetFontWeight(FontWeight::BOLD);

    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    MenuItemGroupView::Create();
    auto groupNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    MenuItemGroupView::Create();
    auto groupNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(groupNode, nullptr);
    auto groupPattern = groupNode->GetPattern<MenuItemGroupPattern>();

    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    MenuItemView::Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    itemPattern->OnModifyDone();
    itemNode->MountToParent(groupNode);
    itemNode->OnMountToParentDone();
    groupPattern->OnModifyDone();
    groupNode->MountToParent(menuNode);
    groupNode->OnMountToParentDone();
    groupNode2->MountToParent(menuNode);
    groupNode2->OnMountToParentDone();

    // call UpdateMenuItemChildren
    menuPattern->OnModifyDone();

    auto contentNode = itemPattern->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto textProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);
    ASSERT_TRUE(textProperty->GetContent().has_value());
    EXPECT_EQ(textProperty->GetContent().value(), "content");
    ASSERT_TRUE(textProperty->GetFontSize().has_value());
    EXPECT_EQ(textProperty->GetFontSize().value(), Dimension(25.0));
    ASSERT_TRUE(textProperty->GetFontWeight().has_value());
    EXPECT_EQ(textProperty->GetFontWeight().value(), FontWeight::BOLD);
    ASSERT_TRUE(textProperty->GetTextColor().has_value());
    EXPECT_EQ(textProperty->GetTextColor().value(), Color::RED);

    auto labelNode = itemPattern->GetLabelNode();
    ASSERT_NE(labelNode, nullptr);
    auto labelProperty = labelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(labelProperty, nullptr);
    ASSERT_TRUE(labelProperty->GetContent().has_value());
    EXPECT_EQ(labelProperty->GetContent().value(), "label");
    ASSERT_TRUE(labelProperty->GetFontSize().has_value());
    EXPECT_EQ(labelProperty->GetFontSize().value(), Dimension(25.0));
    ASSERT_TRUE(labelProperty->GetFontWeight().has_value());
    EXPECT_EQ(labelProperty->GetFontWeight().value(), FontWeight::BOLD);
    ASSERT_TRUE(labelProperty->GetTextColor().has_value());
    EXPECT_EQ(labelProperty->GetTextColor().value(), Color::RED);
}

/**
 * @tc.name: MenuPatternTestNg010
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg010, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    MenuView::Create();
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    MenuItemGroupView::Create();
    auto groupNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(groupNode, nullptr);
    auto groupPattern = groupNode->GetPattern<MenuItemGroupPattern>();

    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemView::Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    itemPattern->OnModifyDone();
    itemNode->MountToParent(groupNode);
    itemNode->OnMountToParentDone();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textPattern = textNode->GetPattern<TextPattern>();
    textPattern->OnModifyDone();
    textNode->MountToParent(groupNode);
    textNode->OnMountToParentDone();
    groupPattern->OnModifyDone();
    groupNode->MountToParent(menuNode);
    groupNode->OnMountToParentDone();

    // call UpdateMenuItemChildren
    menuPattern->OnModifyDone();

    auto contentNode = itemPattern->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto textProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);
    ASSERT_TRUE(textProperty->GetContent().has_value());
    EXPECT_EQ(textProperty->GetContent().value(), "content");
    ASSERT_TRUE(textProperty->GetFontSize().has_value());
    ASSERT_TRUE(textProperty->GetFontWeight().has_value());
    EXPECT_EQ(textProperty->GetFontWeight().value(), FontWeight::REGULAR);
    ASSERT_TRUE(textProperty->GetTextColor().has_value());

    auto labelNode = itemPattern->GetLabelNode();
    ASSERT_EQ(labelNode, nullptr);
}

/**
 * @tc.name: MenuPatternTestNg011
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg011, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    MenuView::Create();
    MenuView::SetFontSize(Dimension(25.0));
    MenuView::SetFontColor(Color::RED);
    MenuView::SetFontWeight(FontWeight::BOLD);
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemView::Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    itemPattern->OnModifyDone();
    itemNode->MountToParent(menuNode);
    itemNode->OnMountToParentDone();

    // call UpdateMenuItemChildren
    menuPattern->OnModifyDone();
    itemPattern->OnModifyDone();
    auto labelNode = itemPattern->GetLabelNode();
    ASSERT_EQ(labelNode, nullptr);
}
} // namespace
} // namespace OHOS::Ace::NG