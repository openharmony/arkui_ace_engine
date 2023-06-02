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

#include "core/components/common/properties/shadow_config.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_pattern.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"
#include "core/components_ng/pattern/menu/menu_model_ng.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/multi_menu_layout_algorithm.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TARGET_ID = 3;
constexpr MenuType TYPE = MenuType::MENU;
constexpr int32_t SELECTED_INDEX = 10;
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
 * @tc.desc: Verify RegisterOnTouch.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg001, TestSize.Level1)
{
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE);
    std::string type = "1";
    TouchEventInfo info(type);
    menuPattern->RegisterOnTouch();
    EXPECT_TRUE(info.GetTouches().empty());
}

/**
 * @tc.name: MenuPatternTestNg002
 * @tc.desc: Verify RegisterOnTouch.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg002, TestSize.Level1)
{
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE);
    std::string type = "1";
    TouchType touchType = TouchType::UP;
    TouchEventInfo info(type);
    TouchLocationInfo locationInfo(TARGET_ID);
    Offset globalLocation(1, 1);
    locationInfo.SetTouchType(touchType);
    auto touchLocationInfo = locationInfo.SetGlobalLocation(globalLocation);
    info.touches_.emplace_back(touchLocationInfo);
    menuPattern->RegisterOnTouch();
    EXPECT_FALSE(info.GetTouches().empty());
    EXPECT_TRUE(info.GetTouches().front().GetTouchType() == TouchType::UP);
}

/**
 * @tc.name: MenuPatternTestNg003
 * @tc.desc: Verify RegisterOnTouch.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg003, TestSize.Level1)
{
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE);
    std::string type = "1";
    TouchType touchType = TouchType::UP;
    TouchEventInfo info(type);
    TouchLocationInfo locationInfo(TARGET_ID);
    Offset globalLocation(1, 1);
    locationInfo.SetTouchType(touchType);
    auto touchLocationInfo = locationInfo.SetGlobalLocation(globalLocation);
    info.touches_.emplace_back(touchLocationInfo);
    menuPattern->type_ = MenuType::CONTEXT_MENU;
    menuPattern->RegisterOnTouch();
    EXPECT_FALSE(info.GetTouches().empty());
    EXPECT_TRUE(info.GetTouches().front().GetTouchType() == TouchType::UP);
}

/**
 * @tc.name: MenuPatternTestNg004
 * @tc.desc: Verify RegisterOnTouch.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg004, TestSize.Level1)
{
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE);
    std::string type = "1";
    TouchEventInfo info(type);
    TouchLocationInfo locationInfo(TARGET_ID);
    Offset globalLocation(1, 1);
    auto touchLocationInfo = locationInfo.SetGlobalLocation(globalLocation);
    info.touches_.emplace_back(touchLocationInfo);
    menuPattern->RegisterOnTouch();
    EXPECT_FALSE(info.GetTouches().empty());
    EXPECT_TRUE(info.GetTouches().front().GetTouchType() == TouchType::UNKNOWN);
}

/**
 * @tc.name: MenuPatternTestNg005
 * @tc.desc: Verify RegisterOnTouch.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg005, TestSize.Level1)
{
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE);
    std::string type = "1";
    TouchEventInfo info(type);
    TouchType touchType = TouchType::UP;
    TouchLocationInfo locationInfo(TARGET_ID);
    locationInfo.SetTouchType(touchType);
    menuPattern->RegisterOnTouch();
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
    MenuModelNG MneuModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    MneuModelInstance.Create();
    MneuModelInstance.SetFontSize(Dimension(25.0));
    MneuModelInstance.SetFontColor(Color::RED);
    MneuModelInstance.SetFontWeight(FontWeight::BOLD);
    MneuModelInstance.SetFontStyle(Ace::FontStyle::ITALIC);

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
    ASSERT_TRUE(layoutProperty->GetItalicFontStyle().has_value());
    EXPECT_EQ(layoutProperty->GetItalicFontStyle().value(), Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: MenuPatternTestNg007
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg007, TestSize.Level1)
{
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    MneuModelInstance.Create();
    MneuModelInstance.SetFontSize(Dimension(25.0));
    MneuModelInstance.SetFontColor(Color::RED);
    MneuModelInstance.SetFontWeight(FontWeight::BOLD);

    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    MneuItemModelInstance.Create(itemOption);
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
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    MneuModelInstance.Create();
    MneuModelInstance.SetFontSize(Dimension(25.0));
    MneuModelInstance.SetFontColor(Color::RED);
    MneuModelInstance.SetFontWeight(FontWeight::BOLD);

    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontSize(Dimension(35.0));
    MneuItemModelInstance.SetFontColor(Color::BLUE);
    MneuItemModelInstance.SetFontWeight(FontWeight::LIGHTER);
    MneuItemModelInstance.SetLabelFontSize(Dimension(40.0));
    MneuItemModelInstance.SetLabelFontColor(Color::GRAY);
    MneuItemModelInstance.SetLabelFontWeight(FontWeight::LIGHTER);
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
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    MneuModelInstance.Create();
    MneuModelInstance.SetFontSize(Dimension(25.0));
    MneuModelInstance.SetFontColor(Color::RED);
    MneuModelInstance.SetFontWeight(FontWeight::BOLD);

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
    MneuItemModelInstance.Create(itemOption);
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
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    MneuModelInstance.Create();
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
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    itemPattern->OnModifyDone();
    itemNode->MountToParent(groupNode);
    itemNode->OnMountToParentDone();
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
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
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    MneuModelInstance.Create();
    MneuModelInstance.SetFontSize(Dimension(25.0));
    MneuModelInstance.SetFontColor(Color::RED);
    MneuModelInstance.SetFontWeight(FontWeight::BOLD);
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    MenuItemProperties itemOption;
    itemOption.content = "content";
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontStyle(Ace::FontStyle::ITALIC);
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

/**
 * @tc.name: MenuPatternTestNg012
 * @tc.desc: Verify UpdateSelectParam.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg012, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    std::vector<SelectParam> params;
    params.emplace_back("content1", "icon1");
    params.emplace_back("content2", "");
    params.emplace_back("", "icon3");
    params.emplace_back("", "");
    auto wrapperNode = MenuView::Create(params, TARGET_ID);
    ASSERT_NE(wrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    ASSERT_EQ(menuPattern->GetOptions().size(), 4);
    const auto& children = menuPattern->GetOptions();
    auto childIt = children.begin();
    for (size_t i = 0; i < children.size(); i++, childIt++) {
        const auto& childNode = AceType::DynamicCast<FrameNode>(*childIt);
        ASSERT_NE(childNode, nullptr);
        auto optionPattern = childNode->GetPattern<OptionPattern>();
        ASSERT_NE(optionPattern, nullptr);
        ASSERT_NE(optionPattern->text_, nullptr);
        auto textProps = optionPattern->text_->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(textProps, nullptr);
        auto param = params.at(i);
        EXPECT_EQ(textProps->GetContent().value_or(""), param.first);
        if (param.second.empty()) {
            ASSERT_EQ(optionPattern->icon_, nullptr);
        } else {
            ASSERT_NE(optionPattern->icon_, nullptr);
            auto imageProps = optionPattern->icon_->GetLayoutProperty<ImageLayoutProperty>();
            ASSERT_NE(imageProps, nullptr);
            auto imageSrcInfo = imageProps->GetImageSourceInfo();
            ASSERT_TRUE(imageSrcInfo.has_value());
            ASSERT_EQ(imageSrcInfo->GetSrc(), param.second);
        }
    }

    params.clear();
    menuPattern->UpdateSelectParam(params);
    ASSERT_EQ(menuPattern->GetOptions().size(), 0);
}

/**
 * @tc.name: MenuPatternTestNg013
 * @tc.desc: Verify UpdateSelectParam.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg013, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    std::vector<SelectParam> params;
    auto wrapperNode = MenuView::Create(params, TARGET_ID);
    ASSERT_NE(wrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    ASSERT_EQ(menuNode->GetChildren().size(), 1);

    params.emplace_back("content1", "icon1");
    params.emplace_back("content2", "");
    params.emplace_back("", "icon3");
    params.emplace_back("", "");
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->UpdateSelectParam(params);

    ASSERT_EQ(menuPattern->GetOptions().size(), 4);
    const auto& children = menuPattern->GetOptions();
    auto childIt = children.begin();
    for (size_t i = 0; i < children.size(); i++, childIt++) {
        const auto& childNode = AceType::DynamicCast<FrameNode>(*childIt);
        ASSERT_NE(childNode, nullptr);
        auto optionPattern = childNode->GetPattern<OptionPattern>();
        ASSERT_NE(optionPattern, nullptr);
        ASSERT_NE(optionPattern->text_, nullptr);
        auto textProps = optionPattern->text_->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(textProps, nullptr);
        auto param = params.at(i);
        EXPECT_EQ(textProps->GetContent().value_or(""), param.first);
        if (param.second.empty()) {
            ASSERT_EQ(optionPattern->icon_, nullptr);
        } else {
            ASSERT_NE(optionPattern->icon_, nullptr);
            auto imageProps = optionPattern->icon_->GetLayoutProperty<ImageLayoutProperty>();
            ASSERT_NE(imageProps, nullptr);
            auto imageSrcInfo = imageProps->GetImageSourceInfo();
            ASSERT_TRUE(imageSrcInfo.has_value());
            ASSERT_EQ(imageSrcInfo->GetSrc(), param.second);
        }
    }
}

/**
 * @tc.name: MenuPatternTestNg014
 * @tc.desc: Verify UpdateSelectParam.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg014, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    std::vector<SelectParam> params;
    auto wrapperNode = MenuView::Create(params, TARGET_ID);
    ASSERT_NE(wrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    ASSERT_EQ(menuPattern->GetOptions().size(), 0);

    menuPattern->UpdateSelectParam(params);
    ASSERT_EQ(menuPattern->GetOptions().size(), 0);
}

/**
 * @tc.name: MenuPatternTestNg015
 * @tc.desc: Verify UpdateSelectParam.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg015, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    std::vector<SelectParam> params;
    params.emplace_back("content1", "icon1");
    params.emplace_back("content2", "");
    params.emplace_back("", "icon3");
    params.emplace_back("", "");
    auto wrapperNode = MenuView::Create(params, TARGET_ID);
    ASSERT_NE(wrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    ASSERT_EQ(menuPattern->GetOptions().size(), 4);

    params.clear();
    params.emplace_back("content1_new", "");
    params.emplace_back("content2_new", "icon2_new");
    params.emplace_back("", "");
    params.emplace_back("", "icon4_new");
    menuPattern->UpdateSelectParam(params);
    ASSERT_EQ(menuPattern->GetOptions().size(), 4);

    const auto& children = menuPattern->GetOptions();
    auto childIt = children.begin();
    for (size_t i = 0; i < children.size(); i++, childIt++) {
        const auto& childNode = AceType::DynamicCast<FrameNode>(*childIt);
        ASSERT_NE(childNode, nullptr);
        auto optionPattern = childNode->GetPattern<OptionPattern>();
        ASSERT_NE(optionPattern, nullptr);
        ASSERT_NE(optionPattern->text_, nullptr);
        auto textProps = optionPattern->text_->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(textProps, nullptr);
        auto param = params.at(i);
        EXPECT_EQ(textProps->GetContent().value_or(""), param.first);
        if (param.second.empty()) {
            ASSERT_EQ(optionPattern->icon_, nullptr);
        } else {
            ASSERT_NE(optionPattern->icon_, nullptr);
            auto imageProps = optionPattern->icon_->GetLayoutProperty<ImageLayoutProperty>();
            ASSERT_NE(imageProps, nullptr);
            auto imageSrcInfo = imageProps->GetImageSourceInfo();
            ASSERT_TRUE(imageSrcInfo.has_value());
            ASSERT_EQ(imageSrcInfo->GetSrc(), param.second);
        }
    }
}

/**
 * @tc.name: MenuPatternTestNg016
 * @tc.desc: Verify UpdateSelectParam.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg016, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    std::vector<SelectParam> params;
    params.emplace_back("content1", "icon1");
    params.emplace_back("content2", "");
    params.emplace_back("", "icon3");
    params.emplace_back("", "");
    auto wrapperNode = MenuView::Create(params, TARGET_ID);
    ASSERT_NE(wrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    ASSERT_EQ(menuPattern->GetOptions().size(), 4);

    params.clear();
    params.emplace_back("content1_new", "");
    params.emplace_back("content2_new", "icon2_new");
    params.emplace_back("", "");
    menuPattern->UpdateSelectParam(params);
    ASSERT_EQ(menuPattern->GetOptions().size(), 3);

    const auto& children = menuPattern->GetOptions();
    auto childIt = children.begin();
    for (size_t i = 0; i < children.size(); i++, childIt++) {
        const auto& childNode = AceType::DynamicCast<FrameNode>(*childIt);
        ASSERT_NE(childNode, nullptr);
        auto optionPattern = childNode->GetPattern<OptionPattern>();
        ASSERT_NE(optionPattern, nullptr);
        ASSERT_NE(optionPattern->text_, nullptr);
        auto textProps = optionPattern->text_->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(textProps, nullptr);
        auto param = params.at(i);
        EXPECT_EQ(textProps->GetContent().value_or(""), param.first);
        if (param.second.empty()) {
            ASSERT_EQ(optionPattern->icon_, nullptr);
        } else {
            ASSERT_NE(optionPattern->icon_, nullptr);
            auto imageProps = optionPattern->icon_->GetLayoutProperty<ImageLayoutProperty>();
            ASSERT_NE(imageProps, nullptr);
            auto imageSrcInfo = imageProps->GetImageSourceInfo();
            ASSERT_TRUE(imageSrcInfo.has_value());
            ASSERT_EQ(imageSrcInfo->GetSrc(), param.second);
        }
    }
}

/**
 * @tc.name: MenuPatternTestNg017
 * @tc.desc: Verify UpdateSelectParam.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg017, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    std::vector<SelectParam> params;
    params.emplace_back("content1", "icon1");
    params.emplace_back("content2", "");
    params.emplace_back("", "icon3");
    auto wrapperNode = MenuView::Create(params, TARGET_ID);
    ASSERT_NE(wrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    ASSERT_EQ(menuPattern->GetOptions().size(), 3);

    params.clear();
    params.emplace_back("content1_new", "");
    params.emplace_back("content2_new", "icon2_new");
    params.emplace_back("", "");
    params.emplace_back("", "icon4_new");
    menuPattern->UpdateSelectParam(params);
    ASSERT_EQ(menuPattern->GetOptions().size(), 4);

    const auto& children = menuPattern->GetOptions();
    auto childIt = children.begin();
    for (size_t i = 0; i < children.size(); i++, childIt++) {
        const auto& childNode = AceType::DynamicCast<FrameNode>(*childIt);
        ASSERT_NE(childNode, nullptr);
        auto optionPattern = childNode->GetPattern<OptionPattern>();
        ASSERT_NE(optionPattern, nullptr);
        ASSERT_NE(optionPattern->text_, nullptr);
        auto textProps = optionPattern->text_->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(textProps, nullptr);
        auto param = params.at(i);
        EXPECT_EQ(textProps->GetContent().value_or(""), param.first);
        if (param.second.empty()) {
            ASSERT_EQ(optionPattern->icon_, nullptr);
        } else {
            ASSERT_NE(optionPattern->icon_, nullptr);
            auto imageProps = optionPattern->icon_->GetLayoutProperty<ImageLayoutProperty>();
            ASSERT_NE(imageProps, nullptr);
            auto imageSrcInfo = imageProps->GetImageSourceInfo();
            ASSERT_TRUE(imageSrcInfo.has_value());
            ASSERT_EQ(imageSrcInfo->GetSrc(), param.second);
        }
    }
}

/**
 * @tc.name: MenuPatternTestNg018
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg018, TestSize.Level1)
{
    MenuModelNG MneuModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    MneuModelInstance.Create();
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    ASSERT_EQ(menuPattern->GetOptions().size(), 0);
    std::vector<SelectParam> params;
    params.emplace_back("content1", "icon1");
    menuPattern->UpdateSelectParam(params);
    ASSERT_EQ(menuPattern->GetOptions().size(), 0);
}

/**
 * @tc.ame: MenuPatternTestNg019
 * @tc.desc: Test MultiMenu and outer Menu container.
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg019, TestSize.Level1)
{
    MenuModelNG model;
    model.Create();
    auto multiMenu = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto menuWrapper = MenuView::Create(multiMenu, -1);
    ASSERT_NE(menuWrapper, nullptr);
    auto outerMenu = AceType::DynamicCast<FrameNode>(menuWrapper->GetFirstChild());
    ASSERT_NE(outerMenu, nullptr);

    // backgroundColor should be reset
    ASSERT_EQ(outerMenu->GetRenderContext()->GetBackgroundColorValue(), Color::TRANSPARENT);

    // padding should be moved to inner multi menu
    auto scroll = AceType::DynamicCast<FrameNode>(outerMenu->GetFirstChild());
    ASSERT_NE(scroll, nullptr);
    auto&& padding = scroll->GetLayoutProperty()->GetPaddingProperty();
    // should have empty padding
    ASSERT_EQ(padding->ToString(), PaddingProperty().ToString());

    // inner multi menu should have backgroundColor and padding set up
    ASSERT_NE(multiMenu->GetLayoutProperty()->GetPaddingProperty()->ToString(), PaddingProperty().ToString());
    ASSERT_NE(multiMenu->GetRenderContext()->GetBackgroundColor(), std::nullopt);
    // inner menu should have no shadow
    ASSERT_EQ(multiMenu->GetRenderContext()->GetBackShadow(), ShadowConfig::NoneShadow);

    // MultiMenu should have its own layout algorithm
    auto layoutAlgorithm = multiMenu->GetPattern<MenuPattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(AceType::DynamicCast<MultiMenuLayoutAlgorithm>(layoutAlgorithm), nullptr);
}

/**
 * @tc.name: MenuPatternTestNg020
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MenuModelNG and MenuItemModelNG object and set FontStyle properties of MenuModelNG.
     */
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    MneuModelInstance.Create();
    MneuModelInstance.SetFontStyle(Ace::FontStyle::ITALIC);

    /**
     * @tc.steps: step2. get the frameNode, MenuPattern and MenuLayoutProperty.
     * @tc.expected: step2. check whether the objects is available.
     */
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. not set FontStyle properties of MenuModelNG.
     */
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    itemPattern->OnModifyDone();
    itemNode->MountToParent(menuNode);
    itemNode->OnMountToParentDone();

    /**
     * @tc.steps: step4. call OnModifyDone of MenuPattern to call UpdateMenuItemChildren
     */
    menuPattern->OnModifyDone();

    /**
     * @tc.steps: step5. get the FontStyle properties of menuItemLayoutProperty.
     * @tc.expected: step5. check whether the FontStyle properties is is correct.
     */
    auto contentNode = itemPattern->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto textProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);
    ASSERT_TRUE(textProperty->GetItalicFontStyle().has_value());
    EXPECT_EQ(textProperty->GetItalicFontStyle().value(), Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: MenuItem Accessibility PerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menu, get menu frameNode and pattern, set callback function.
     * @tc.expected: FrameNode and pattern is not null, related function is called.
     */
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto menuItemEventHub = frameNode->GetEventHub<MenuItemEventHub>();
    ASSERT_NE(menuItemEventHub, nullptr);
    auto menuItemAccessibilityProperty = frameNode->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty, nullptr);
    menuItemPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step2. When selectedChangeEvent onChange and subBuilder is null, call the callback function in
     *                   menuItemAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(menuItemAccessibilityProperty->ActActionSelect());

    /**
     * @tc.steps: step3. When selectedChangeEvent onChange and subBuilder is not null, call the callback function in
     *                   menuItemAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    bool isSelected = false;
    auto changeEvent = [&isSelected](bool select) { isSelected = select; };
    menuItemEventHub->SetSelectedChangeEvent(changeEvent);
    menuItemEventHub->SetOnChange(changeEvent);
    auto subBuilder = []() {};
    menuItemPattern->SetSubBuilder(subBuilder);
    EXPECT_TRUE(menuItemAccessibilityProperty->ActActionSelect());
}

/**
 * @tc.name: PerformActionTest002
 * @tc.desc: Menu Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, PerformActionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menu, get menu frameNode and pattern, set callback function.
     * @tc.expected: FrameNode and pattern is not null, related function is called.
     */
    MenuModelNG model;
    model.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuPattern = frameNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto menuAccessibilityProperty = frameNode->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty, nullptr);
    menuPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step2. When firstChild is null, call the callback function in menuAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(menuAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(menuAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step3. When firstChild is not null and firstChild tag is SCROLL_ETS_TAG, call the callback function in
     *                   menuAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->SetAxis(Axis::VERTICAL);
    scrollPattern->scrollableDistance_ = 1.0f;
    auto scroll =
        FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), scrollPattern);
    ASSERT_NE(scroll, nullptr);
    scroll->MountToParent(frameNode, 0);
    scroll->MarkModifyDone();
    EXPECT_TRUE(menuAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(menuAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step4. When firstChild is not null and firstChild tag is not SCROLL_ETS_TAG, call the callback
     *                   function in menuAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    textNode->MountToParent(frameNode, 0);
    textNode->MarkModifyDone();
    EXPECT_TRUE(menuAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(menuAccessibilityProperty->ActActionScrollBackward());
}

/**
 * @tc.name: MenuAccessibilityEventTestNg001
 * @tc.desc: Test Click Event for Option of Menu.
 */
HWTEST_F(MenuPatternTestNg, MenuAccessibilityEventTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Option for Menu.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<OptionPattern>(0); });
    ASSERT_NE(frameNode, nullptr);
    auto optionPattern = frameNode->GetPattern<OptionPattern>();
    ASSERT_NE(optionPattern, nullptr);

    /**
     * @tc.steps: step2. set callback function.
     */
    int testIndex = SELECTED_INDEX;
    auto selectFunc = [optionPattern, testIndex](int index) { optionPattern->index_ = testIndex; };
    auto optionEventHub = frameNode->GetEventHub<OptionEventHub>();
    optionEventHub->SetOnSelect(selectFunc);
    optionPattern->RegisterOnClick();

    /**
     * @tc.steps: step3. call callback function.
     * @tc.expected: index_ is SELECTED_INDEX.
     */
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    auto clickEventActuator = gestureHub->clickEventActuator_;
    ASSERT_NE(clickEventActuator, nullptr);
    auto event = clickEventActuator->GetClickEvent();
    ASSERT_NE(event, nullptr);
    GestureEvent gestureEvent;
    event(gestureEvent);
    EXPECT_EQ(optionPattern->index_, SELECTED_INDEX);
}

/**
 * @tc.name: DesktopMenuPattern001
 * @tc.desc: Test MenuPattern onModifyDone, switch between DesktopMenu and regular menu.
 */
HWTEST_F(MenuPatternTestNg, DesktopMenuPattern001, TestSize.Level1)
{
    MenuModelNG model;
    model.Create();
    auto menu1 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu1, nullptr);
    model.Create();
    auto menu2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto container = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MENU));
    auto mockScroll = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<Pattern>());
    mockScroll->MountToParent(container);
    menu1->MountToParent(mockScroll);
    menu2->MountToParent(mockScroll);

    auto pattern1 = menu1->GetPattern<InnerMenuPattern>();
    auto pattern2 = menu2->GetPattern<InnerMenuPattern>();
    auto containerPattern = container->GetPattern<MenuPattern>();
    containerPattern->OnModifyDone();
    pattern1->OnModifyDone();
    pattern2->OnModifyDone();
    EXPECT_EQ(pattern1->type_, MenuType::DESKTOP_MENU);
    EXPECT_EQ(pattern2->type_, MenuType::DESKTOP_MENU);
    EXPECT_EQ(container->GetRenderContext()->GetBackShadow(), ShadowConfig::NoneShadow);

    mockScroll->RemoveChildAtIndex(1);
    pattern1->OnModifyDone();
    containerPattern->OnModifyDone();
    EXPECT_EQ(pattern1->type_, MenuType::MULTI_MENU);
    EXPECT_EQ(container->GetRenderContext()->GetBackShadow(), ShadowConfig::DefaultShadowM);
}
} // namespace
} // namespace OHOS::Ace::NG
