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
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class MenuItemViewTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void MenuItemViewTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void MenuItemViewTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void MenuItemViewTestNg::SetUp() {}
void MenuItemViewTestNg::TearDown() {}

/**
 * @tc.name: MenuItemViewTestNgCreate001
 * @tc.desc: Verify Create.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgCreate001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    EXPECT_EQ(leftRow->GetChildren().size(), 0);
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));
    EXPECT_EQ(rightRow->GetChildren().size(), 0);

    ASSERT_TRUE(itemProperty->GetStartIcon().has_value());
    EXPECT_EQ(itemProperty->GetStartIcon().value(), "");
    ASSERT_TRUE(itemProperty->GetEndIcon().has_value());
    EXPECT_EQ(itemProperty->GetEndIcon().value(), "");
    ASSERT_TRUE(itemProperty->GetContent().has_value());
    EXPECT_EQ(itemProperty->GetContent().value(), "");
    ASSERT_TRUE(itemProperty->GetLabel().has_value());
    EXPECT_EQ(itemProperty->GetLabel().value(), "");
}

/**
 * @tc.name: MenuItemViewTestNgCreate002
 * @tc.desc: Verify Create.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgCreate002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.startIcon = "startIcon";
    itemOption.endIcon = "endIcon";
    itemOption.labelInfo = "label";
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetStartIcon().has_value());
    EXPECT_EQ(itemProperty->GetStartIcon().value(), "startIcon");
    ASSERT_TRUE(itemProperty->GetEndIcon().has_value());
    EXPECT_EQ(itemProperty->GetEndIcon().value(), "endIcon");
    ASSERT_TRUE(itemProperty->GetContent().has_value());
    EXPECT_EQ(itemProperty->GetContent().value(), "content");
    ASSERT_TRUE(itemProperty->GetLabel().has_value());
    EXPECT_EQ(itemProperty->GetLabel().value(), "label");
}

/**
 * @tc.name: MenuItemViewTestNgSetSelectIcon001
 * @tc.desc: Verify SetSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetSelectIcon001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetSelectIcon(true);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    EXPECT_EQ(itemProperty->GetSelectIcon().value_or(false), true);
}

/**
 * @tc.name: MenuItemViewTestNgSetSelectIcon002
 * @tc.desc: Verify SetSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetSelectIcon002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.SetSelectIcon(true);
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    EXPECT_FALSE(itemProperty->GetSelectIcon().has_value());
}

/**
 * @tc.name: MenuItemViewTestNgSetSelectIconSrc001
 * @tc.desc: Verify SetSelectIconSrc.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetSelectIconSrc001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetSelectIconSrc("selectIcon.png");
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    EXPECT_EQ(itemProperty->GetSelectIconSrc().value_or(""), "selectIcon.png");
}

/**
 * @tc.name: MenuItemViewTestNgSetSelectIconSrc002
 * @tc.desc: Verify SetSelectIconSrc.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetSelectIconSrc002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.SetSelectIconSrc("selectIcon.png");
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    EXPECT_FALSE(itemProperty->GetSelectIconSrc().has_value());
}

/**
 * @tc.name: MenuItemViewTestNgSetFontSize001
 * @tc.desc: Verify SetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetFontSize001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontSize(Dimension());
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    EXPECT_FALSE(itemProperty->GetFontSize().has_value());
}

/**
 * @tc.name: MenuItemViewTestNgSetFontSize002
 * @tc.desc: Verify SetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetFontSize002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontSize(Dimension(40.0));
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetFontSize().has_value());
    EXPECT_EQ(itemProperty->GetFontSize().value(), Dimension(40.0));
}

/**
 * @tc.name: MenuItemViewTestNgSetFontSize003
 * @tc.desc: Verify SetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetFontSize003, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.SetFontSize(Dimension(40.0));
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    ASSERT_FALSE(itemProperty->GetFontSize().has_value());
}

/**
 * @tc.name: MenuItemViewTestNgSetFontWeight001
 * @tc.desc: Verify SetFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetFontWeight001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontWeight(FontWeight::BOLD);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetFontWeight().has_value());
    EXPECT_EQ(itemProperty->GetFontWeight().value(), FontWeight::BOLD);
}

/**
 * @tc.name: MenuItemViewTestNgSetFontWeight002
 * @tc.desc: Verify SetFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetFontWeight002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.SetFontWeight(FontWeight::BOLD);
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    ASSERT_FALSE(itemProperty->GetFontWeight().has_value());
}

/**
 * @tc.name: MenuItemViewTestNgSetFontColor001
 * @tc.desc: Verify SetFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetFontColor001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontColor(Color::RED);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetFontColor().has_value());
    EXPECT_EQ(itemProperty->GetFontColor().value(), Color::RED);
}

/**
 * @tc.name: MenuItemViewTestNgSetFontColor002
 * @tc.desc: Verify SetFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetFontColor002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.SetFontColor(Color::RED);
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    ASSERT_FALSE(itemProperty->GetFontColor().has_value());
}

/**
 * @tc.name: MenuItemViewTestNgSetFontColor003
 * @tc.desc: Verify SetFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetFontColor003, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontColor(Color::RED);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetFontColor().has_value());
    EXPECT_EQ(itemProperty->GetFontColor().value(), Color::RED);

    ViewStackProcessor::GetInstance()->Push(itemNode);
    MneuItemModelInstance.SetFontColor(std::nullopt);
    ASSERT_FALSE(itemProperty->GetFontColor().has_value());
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: MenuItemViewTestNgSetLabelFontSize001
 * @tc.desc: Verify SetLabelFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetLabelFontSize001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetLabelFontSize(Dimension());
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    EXPECT_FALSE(itemProperty->GetLabelFontSize().has_value());
}

/**
 * @tc.name: MenuItemViewTestNgSetLabelFontSize002
 * @tc.desc: Verify SetLabelFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetLabelFontSize002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetLabelFontSize(Dimension(40.0));
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetLabelFontSize().has_value());
    EXPECT_EQ(itemProperty->GetLabelFontSize().value(), Dimension(40.0));
}

/**
 * @tc.name: MenuItemViewTestNgSetLabelFontSize003
 * @tc.desc: Verify SetLabelFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetLabelFontSize003, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.SetLabelFontSize(Dimension(40.0));
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    ASSERT_FALSE(itemProperty->GetLabelFontSize().has_value());
}

/**
 * @tc.name: MenuItemViewTestNgSetLabelFontWeight001
 * @tc.desc: Verify SetLabelFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetLabelFontWeight001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetLabelFontWeight(FontWeight::BOLD);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetLabelFontWeight().has_value());
    EXPECT_EQ(itemProperty->GetLabelFontWeight().value(), FontWeight::BOLD);
}

/**
 * @tc.name: MenuItemViewTestNgSetLabelFontWeight002
 * @tc.desc: Verify SetLabelFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetLabelFontWeight002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.SetLabelFontWeight(FontWeight::BOLD);
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    ASSERT_FALSE(itemProperty->GetLabelFontWeight().has_value());
}

/**
 * @tc.name: MenuItemViewTestNgSetLabelFontColor001
 * @tc.desc: Verify SetLabelFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetLabelFontColor001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetLabelFontColor(Color::RED);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetLabelFontColor().has_value());
    EXPECT_EQ(itemProperty->GetLabelFontColor().value(), Color::RED);
}

/**
 * @tc.name: MenuItemViewTestNgSetLabelFontColor002
 * @tc.desc: Verify SetLabelFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetLabelFontColor002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.SetLabelFontColor(Color::RED);
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    ASSERT_FALSE(itemProperty->GetLabelFontColor().has_value());
}

/**
 * @tc.name: MenuItemViewTestNgSetLabelFontColor003
 * @tc.desc: Verify SetLabelFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetLabelFontColor003, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetLabelFontColor(Color::RED);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetLabelFontColor().has_value());
    EXPECT_EQ(itemProperty->GetLabelFontColor().value(), Color::RED);

    ViewStackProcessor::GetInstance()->Push(itemNode);
    MneuItemModelInstance.SetLabelFontColor(std::nullopt);
    ASSERT_FALSE(itemProperty->GetLabelFontColor().has_value());
    ViewStackProcessor::GetInstance()->Finish();
}
/**
 * @tc.name: MenuItemSetSelectedChangeEvent001
 * @tc.desc: Verify SetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemSetSelectedChangeEvent001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    bool isSelected = false;
    auto changeEvent = [&isSelected](bool select) { isSelected = select; };
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetSelectedChangeEvent(changeEvent);
    
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);

    auto itemProperty = itemNode->GetEventHub<NG::MenuItemEventHub>();
    ASSERT_NE(itemProperty, nullptr);
    EXPECT_TRUE(itemProperty->GetSelectedChangeEvent());
}

/**
 * @tc.name: MenuItemViewTestNgSetLabelFontStyle001
 * @tc.desc: Verify SetLabelFontStyle.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetLabelFontStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MenuItemModelNG object and set LabelFontStyle properties.
     */
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetLabelFontStyle(Ace::FontStyle::ITALIC);

    /**
     * @tc.steps: step2. get the frameNode, menuItemPattern and menuItemLayoutProperty.
     * @tc.expected: step2. check whether the objects is available.
     */
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    /**
     * @tc.steps: step3. get the labelFontStyle properties of menuItemLayoutProperty.
     * @tc.expected: step3. check whether the labelFontStyle properties is is correct.
     */
    ASSERT_TRUE(itemProperty->GetLabelItalicFontStyle().has_value());
    EXPECT_EQ(itemProperty->GetLabelItalicFontStyle().value(), Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: MenuItemViewTestNgSetFontStyle001
 * @tc.desc: Verify SetFontStyle.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemViewTestNg, MenuItemViewTestNgSetFontStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MenuItemModelNG object and set FontStyle properties.
     */
    MenuItemModelNG MneuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontStyle(Ace::FontStyle::ITALIC);

    /**
     * @tc.steps: step2. get the frameNode, menuItemPattern and menuItemLayoutProperty.
     * @tc.expected: step2. check whether the objects is available.
     */
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    /**
     * @tc.steps: step3. get the FontStyle properties of menuItemLayoutProperty.
     * @tc.expected: step3. check whether the FontStyle properties is is correct.
     */
    ASSERT_TRUE(itemProperty->GetItalicFontStyle().has_value());
    EXPECT_EQ(itemProperty->GetItalicFontStyle().value(), Ace::FontStyle::ITALIC);
}
}
} // namespace OHOS::Ace::NG
