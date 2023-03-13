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
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TARGET_ID = 3;
constexpr MenuType TYPE = MenuType::MENU;
class MenuLayoutPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void MenuLayoutPropertyTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void MenuLayoutPropertyTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void MenuLayoutPropertyTestNg::SetUp() {}
void MenuLayoutPropertyTestNg::TearDown() {}

/**
 * @tc.name: MenuLayoutPropertyTestNg001
 * @tc.desc: Verify GetPositionOffset.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutPropertyTestNg, MenuLayoutPropertyTestNg001, TestSize.Level1)
{
    MenuLayoutProperty property;
    EXPECT_FALSE(property.GetPositionOffset().has_value());
    property.UpdatePositionOffset(OffsetF(25.0f, 30.0f));
    ASSERT_TRUE(property.GetPositionOffset().has_value());
    EXPECT_EQ(property.GetPositionOffset().value(), OffsetF(25.0f, 30.0f));
}

/**
 * @tc.name: MenuLayoutPropertyTestNg002
 * @tc.desc: Verify GetTitle.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutPropertyTestNg, MenuLayoutPropertyTestNg002, TestSize.Level1)
{
    MenuLayoutProperty property;
    EXPECT_FALSE(property.GetTitle().has_value());
    property.UpdateTitle("title");
    ASSERT_TRUE(property.GetTitle().has_value());
    EXPECT_EQ(property.GetTitle().value(), "title");
}

/**
 * @tc.name: MenuLayoutPropertyTestNg003
 * @tc.desc: Verify GetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutPropertyTestNg, MenuLayoutPropertyTestNg003, TestSize.Level1)
{
    MenuLayoutProperty property;
    EXPECT_FALSE(property.GetFontSize().has_value());
    property.UpdateFontSize(Dimension(25.0f));
    ASSERT_TRUE(property.GetFontSize().has_value());
    EXPECT_EQ(property.GetFontSize().value(), Dimension(25.0f));
}

/**
 * @tc.name: MenuLayoutPropertyTestNg004
 * @tc.desc: Verify GetFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutPropertyTestNg, MenuLayoutPropertyTestNg004, TestSize.Level1)
{
    MenuLayoutProperty property;
    EXPECT_FALSE(property.GetFontColor().has_value());
    property.UpdateFontColor(Color::RED);
    ASSERT_TRUE(property.GetFontColor().has_value());
    EXPECT_EQ(property.GetFontColor().value(), Color::RED);
}

/**
 * @tc.name: MenuLayoutPropertyTestNg005
 * @tc.desc: Verify GetFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutPropertyTestNg, MenuLayoutPropertyTestNg005, TestSize.Level1)
{
    MenuLayoutProperty property;
    EXPECT_FALSE(property.GetFontWeight().has_value());
    property.UpdateFontWeight(FontWeight::BOLD);
    ASSERT_TRUE(property.GetFontWeight().has_value());
    EXPECT_EQ(property.GetFontWeight().value(), FontWeight::BOLD);
}

/**
 * @tc.name: MenuLayoutPropertyTestNg006
 * @tc.desc: Verify GetMenuOffset.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutPropertyTestNg, MenuLayoutPropertyTestNg006, TestSize.Level1)
{
    MenuLayoutProperty property;
    EXPECT_FALSE(property.GetMenuOffset().has_value());
    property.UpdateMenuOffset(OffsetF(25.0f, 30.0f));
    ASSERT_TRUE(property.GetMenuOffset().has_value());
    EXPECT_EQ(property.GetMenuOffset().value(), OffsetF(25.0f, 30.0f));
}

/**
 * @tc.name: MenuLayoutPropertyTestNg007
 * @tc.desc: Verify Reset.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutPropertyTestNg, MenuLayoutPropertyTestNg007, TestSize.Level1)
{
    MenuLayoutProperty property;
    property.UpdateMenuOffset(OffsetF(25.0f, 30.0f));
    property.UpdatePositionOffset(OffsetF(25.0f, 30.0f));
    property.UpdateTitle("title");
    property.UpdateFontSize(Dimension(25.0f));
    property.UpdateFontColor(Color::RED);
    property.UpdateFontWeight(FontWeight::BOLD);
    EXPECT_TRUE(property.GetMenuOffset().has_value());
    EXPECT_TRUE(property.GetPositionOffset().has_value());
    EXPECT_TRUE(property.GetTitle().has_value());
    EXPECT_TRUE(property.GetFontSize().has_value());
    EXPECT_TRUE(property.GetFontColor().has_value());
    EXPECT_TRUE(property.GetFontWeight().has_value());
    property.Reset();
    EXPECT_FALSE(property.GetMenuOffset().has_value());
    EXPECT_FALSE(property.GetPositionOffset().has_value());
    EXPECT_FALSE(property.GetTitle().has_value());
    EXPECT_FALSE(property.GetFontSize().has_value());
    EXPECT_FALSE(property.GetFontColor().has_value());
    EXPECT_FALSE(property.GetFontWeight().has_value());
}

/**
 * @tc.name: MenuLayoutPropertyTestNg008
 * @tc.desc: Verify Clone.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutPropertyTestNg, MenuLayoutPropertyTestNg008, TestSize.Level1)
{
    MenuLayoutProperty property;
    property.UpdateMenuOffset(OffsetF(25.0f, 30.0f));
    property.UpdatePositionOffset(OffsetF(25.0f, 30.0f));
    property.UpdateTitle("title");
    property.UpdateFontSize(Dimension(25.0f));
    property.UpdateFontColor(Color::RED);
    property.UpdateFontWeight(FontWeight::BOLD);

    auto cloneProperty = AceType::DynamicCast<MenuLayoutProperty>(property.Clone());
    ASSERT_NE(cloneProperty, nullptr);
    EXPECT_EQ(property.GetMenuOffset().value(), cloneProperty->GetMenuOffset().value());
    EXPECT_EQ(property.GetPositionOffset().value(), cloneProperty->GetPositionOffset().value());
    EXPECT_EQ(property.GetTitle().value(), cloneProperty->GetTitle().value());
    EXPECT_EQ(property.GetFontSize().value(), cloneProperty->GetFontSize().value());
    EXPECT_EQ(property.GetFontColor().value(), cloneProperty->GetFontColor().value());
    EXPECT_EQ(property.GetFontWeight().value(), cloneProperty->GetFontWeight().value());
}

/**
 * @tc.name: MenuLayoutPropertyTestNg009
 * @tc.desc: Verify ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutPropertyTestNg, MenuLayoutPropertyTestNg009, TestSize.Level1)
{
    MenuLayoutProperty property;
    property.UpdateMenuOffset(OffsetF(25.0f, 30.0f));
    property.UpdatePositionOffset(OffsetF(25.0f, 30.0f));
    property.UpdateTitle("title");
    property.UpdateFontSize(Dimension(25.0f));
    property.UpdateFontColor(Color::RED);
    property.UpdateFontWeight(FontWeight::BOLD);

    auto json = JsonUtil::Create(true);
    property.ToJsonValue(json);
    EXPECT_EQ(json->GetString("title"), "title");
    EXPECT_EQ(json->GetString("offset"), OffsetF(25.0f, 30.0f).ToString());
    EXPECT_EQ(json->GetString("fontSize"), Dimension(25.0f).ToString());
    EXPECT_EQ(json->GetString("fontColor"), Color::RED.ColorToString());
    EXPECT_EQ(json->GetString("fontWeight"), V2::ConvertWrapFontWeightToStirng(FontWeight::BOLD));
}

/**
 * @tc.name: MenuLayoutPropertyTestNg010
 * @tc.desc: Verify ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutPropertyTestNg, MenuLayoutPropertyTestNg010, TestSize.Level1)
{
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "fakeIcon", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), TARGET_ID, TYPE, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);

    auto json = JsonUtil::Create(true);
    property->ToJsonValue(json);
    auto itemArray = json->GetValue("bindMenu");
    ASSERT_EQ(itemArray->GetArraySize(), 2u);
    auto item1 = itemArray->GetArrayItem(0);
    EXPECT_EQ(item1->GetString("value"), "MenuItem1");
    EXPECT_EQ(item1->GetString("icon"), "fakeIcon");
    auto item2 = itemArray->GetArrayItem(1);
    EXPECT_EQ(item2->GetString("value"), "MenuItem2");
    EXPECT_EQ(item2->GetString("icon"), "");
}
} // namespace
} // namespace OHOS::Ace::NG
