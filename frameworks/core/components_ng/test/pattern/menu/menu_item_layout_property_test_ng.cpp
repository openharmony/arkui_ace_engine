/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components/select/select_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_view.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class MenuItemLayoutPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void MenuItemLayoutPropertyTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void MenuItemLayoutPropertyTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void MenuItemLayoutPropertyTestNg::SetUp() {}
void MenuItemLayoutPropertyTestNg::TearDown() {}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg001
 * @tc.desc: Verify GetStartIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg001, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetStartIcon().has_value());
    property.UpdateStartIcon("test.png");
    ASSERT_TRUE(property.GetStartIcon().has_value());
    EXPECT_EQ(property.GetStartIcon().value(), "test.png");
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg002
 * @tc.desc: Verify GetContent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg002, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetContent().has_value());
    property.UpdateContent("content");
    ASSERT_TRUE(property.GetContent().has_value());
    EXPECT_EQ(property.GetContent().value(), "content");
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg003
 * @tc.desc: Verify GetEndIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg003, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetEndIcon().has_value());
    property.UpdateEndIcon("test.png");
    ASSERT_TRUE(property.GetEndIcon().has_value());
    EXPECT_EQ(property.GetEndIcon().value(), "test.png");
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg004
 * @tc.desc: Verify GetLabel.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg004, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetLabel().has_value());
    property.UpdateLabel("label");
    ASSERT_TRUE(property.GetLabel().has_value());
    EXPECT_EQ(property.GetLabel().value(), "label");
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg005
 * @tc.desc: Verify GetSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg005, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetSelectIcon().has_value());
    property.UpdateSelectIcon(true);
    ASSERT_TRUE(property.GetSelectIcon().has_value());
    EXPECT_TRUE(property.GetSelectIcon().value());
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg006
 * @tc.desc: Verify GetSelectIconSrc.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg006, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetSelectIconSrc().has_value());
    property.UpdateSelectIconSrc("test.png");
    ASSERT_TRUE(property.GetSelectIconSrc().has_value());
    EXPECT_EQ(property.GetSelectIconSrc().value(), "test.png");
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg007
 * @tc.desc: Verify GetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg007, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetFontSize().has_value());
    property.UpdateFontSize(Dimension(25.0f));
    ASSERT_TRUE(property.GetFontSize().has_value());
    EXPECT_EQ(property.GetFontSize().value(), Dimension(25.0f));
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg008
 * @tc.desc: Verify GetFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg008, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetFontColor().has_value());
    property.UpdateFontColor(Color::RED);
    ASSERT_TRUE(property.GetFontColor().has_value());
    EXPECT_EQ(property.GetFontColor().value(), Color::RED);
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg009
 * @tc.desc: Verify GetFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg009, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetFontWeight().has_value());
    property.UpdateFontWeight(FontWeight::BOLD);
    ASSERT_TRUE(property.GetFontWeight().has_value());
    EXPECT_EQ(property.GetFontWeight().value(), FontWeight::BOLD);
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg0010
 * @tc.desc: Verify GetLabelFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg0010, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetLabelFontSize().has_value());
    property.UpdateLabelFontSize(Dimension(25.0f));
    ASSERT_TRUE(property.GetLabelFontSize().has_value());
    EXPECT_EQ(property.GetLabelFontSize().value(), Dimension(25.0f));
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg011
 * @tc.desc: Verify GetLabelFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg011, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetLabelFontColor().has_value());
    property.UpdateLabelFontColor(Color::RED);
    ASSERT_TRUE(property.GetLabelFontColor().has_value());
    EXPECT_EQ(property.GetLabelFontColor().value(), Color::RED);
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg012
 * @tc.desc: Verify GetLabelFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg012, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetLabelFontWeight().has_value());
    property.UpdateLabelFontWeight(FontWeight::BOLD);
    ASSERT_TRUE(property.GetLabelFontWeight().has_value());
    EXPECT_EQ(property.GetLabelFontWeight().value(), FontWeight::BOLD);
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg013
 * @tc.desc: Verify Reset.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg013, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    property.UpdateStartIcon("test.png");
    property.UpdateContent("content");
    property.UpdateEndIcon("test.png");
    property.UpdateLabel("label");
    property.UpdateSelectIcon(true);
    property.UpdateSelectIconSrc("test.png");
    property.UpdateFontSize(Dimension(25.0f));
    property.UpdateFontColor(Color::RED);
    property.UpdateFontWeight(FontWeight::BOLD);
    property.UpdateLabelFontSize(Dimension(25.0f));
    property.UpdateLabelFontColor(Color::RED);
    property.UpdateLabelFontWeight(FontWeight::BOLD);
    EXPECT_TRUE(property.GetStartIcon().has_value());
    EXPECT_TRUE(property.GetContent().has_value());
    EXPECT_TRUE(property.GetLabel().has_value());
    EXPECT_TRUE(property.GetEndIcon().has_value());
    EXPECT_TRUE(property.GetSelectIcon().has_value());
    EXPECT_TRUE(property.GetSelectIconSrc().has_value());
    EXPECT_TRUE(property.GetFontSize().has_value());
    EXPECT_TRUE(property.GetFontColor().has_value());
    EXPECT_TRUE(property.GetFontWeight().has_value());
    EXPECT_TRUE(property.GetLabelFontSize().has_value());
    EXPECT_TRUE(property.GetLabelFontColor().has_value());
    EXPECT_TRUE(property.GetLabelFontWeight().has_value());
    property.Reset();
    EXPECT_FALSE(property.GetStartIcon().has_value());
    EXPECT_FALSE(property.GetContent().has_value());
    EXPECT_FALSE(property.GetLabel().has_value());
    EXPECT_FALSE(property.GetEndIcon().has_value());
    EXPECT_FALSE(property.GetSelectIcon().has_value());
    EXPECT_FALSE(property.GetSelectIconSrc().has_value());
    EXPECT_FALSE(property.GetFontSize().has_value());
    EXPECT_FALSE(property.GetFontColor().has_value());
    EXPECT_FALSE(property.GetFontWeight().has_value());
    EXPECT_FALSE(property.GetLabelFontSize().has_value());
    EXPECT_FALSE(property.GetLabelFontColor().has_value());
    EXPECT_FALSE(property.GetLabelFontWeight().has_value());
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg014
 * @tc.desc: Verify Clone.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg014, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    property.UpdateStartIcon("start.png");
    property.UpdateContent("content");
    property.UpdateEndIcon("end.png");
    property.UpdateLabel("label");
    property.UpdateSelectIcon(true);
    property.UpdateSelectIconSrc("select.png");
    property.UpdateFontSize(Dimension(25.0f));
    property.UpdateFontColor(Color::RED);
    property.UpdateFontWeight(FontWeight::BOLD);
    property.UpdateLabelFontSize(Dimension(35.0f));
    property.UpdateLabelFontColor(Color::BLUE);
    property.UpdateLabelFontWeight(FontWeight::LIGHTER);

    auto cloneProperty = AceType::DynamicCast<MenuItemLayoutProperty>(property.Clone());
    ASSERT_NE(cloneProperty, nullptr);
    EXPECT_EQ(property.GetStartIcon().value(), cloneProperty->GetStartIcon().value());
    EXPECT_EQ(property.GetContent().value(), cloneProperty->GetContent().value());
    EXPECT_EQ(property.GetEndIcon().value(), cloneProperty->GetEndIcon().value());
    EXPECT_EQ(property.GetLabel().value(), cloneProperty->GetLabel().value());
    EXPECT_EQ(property.GetSelectIcon().value(), cloneProperty->GetSelectIcon().value());
    EXPECT_EQ(property.GetSelectIconSrc().value(), cloneProperty->GetSelectIconSrc().value());
    EXPECT_EQ(property.GetFontSize().value(), cloneProperty->GetFontSize().value());
    EXPECT_EQ(property.GetFontColor().value(), cloneProperty->GetFontColor().value());
    EXPECT_EQ(property.GetFontWeight().value(), cloneProperty->GetFontWeight().value());
    EXPECT_EQ(property.GetLabelFontSize().value(), cloneProperty->GetLabelFontSize().value());
    EXPECT_EQ(property.GetLabelFontColor().value(), cloneProperty->GetLabelFontColor().value());
    EXPECT_EQ(property.GetLabelFontWeight().value(), cloneProperty->GetLabelFontWeight().value());
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg015
 * @tc.desc: Verify ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg015, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    property.UpdateStartIcon("start.png");
    property.UpdateContent("content");
    property.UpdateEndIcon("end.png");
    property.UpdateLabel("label");
    property.UpdateSelectIcon(true);
    property.UpdateSelectIconSrc("select.png");
    property.UpdateFontSize(Dimension(25.0f));
    property.UpdateFontColor(Color::RED);
    property.UpdateFontWeight(FontWeight::BOLD);
    property.UpdateLabelFontSize(Dimension(35.0f));
    property.UpdateLabelFontColor(Color::BLUE);
    property.UpdateLabelFontWeight(FontWeight::LIGHTER);

    auto json = JsonUtil::Create(true);
    property.ToJsonValue(json);
    EXPECT_EQ(json->GetString("startIcon"), "start.png");
    EXPECT_EQ(json->GetString("content"), "content");
    EXPECT_EQ(json->GetString("endIcon"), "end.png");
    EXPECT_EQ(json->GetString("labelInfo"), "label");
    EXPECT_EQ(json->GetString("selectIcon"), "select.png");
    EXPECT_EQ(json->GetString("fontSize"), Dimension(25.0f).ToString());
    EXPECT_EQ(json->GetString("fontColor"), Color::RED.ColorToString());
    EXPECT_EQ(json->GetString("fontWeight"), V2::ConvertWrapFontWeightToStirng(FontWeight::BOLD));
    EXPECT_EQ(json->GetString("labelFontSize"), Dimension(35.0f).ToString());
    EXPECT_EQ(json->GetString("labelFontColor"), Color::BLUE.ColorToString());
    EXPECT_EQ(json->GetString("labelFontWeight"), V2::ConvertWrapFontWeightToStirng(FontWeight::LIGHTER));
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg016
 * @tc.desc: Verify ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg016, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    property.UpdateSelectIcon(false);
    property.UpdateSelectIconSrc("select.png");

    auto json = JsonUtil::Create(true);
    property.ToJsonValue(json);
    EXPECT_EQ(json->GetString("selectIcon"), "false");
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg017
 * @tc.desc: Verify ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg017, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    property.UpdateSelectIcon(true);

    auto json = JsonUtil::Create(true);
    property.ToJsonValue(json);
    EXPECT_EQ(json->GetString("selectIcon"), "true");
}

/**
 * @tc.name: MenuItemLayoutPropertyTestNg018
 * @tc.desc: Verify ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, MenuItemLayoutPropertyTestNg018, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MenuItemView::Create(itemOption);
    MenuItemView::SetSelectIcon(true);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    auto json = JsonUtil::Create(true);
    itemProperty->ToJsonValue(json);
    EXPECT_EQ(json->GetString("selectIcon"), "true");
}
} // namespace
} // namespace OHOS::Ace::NG
