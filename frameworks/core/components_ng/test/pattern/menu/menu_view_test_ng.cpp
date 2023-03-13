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
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TARGET_ID = 3;
constexpr MenuType TYPE = MenuType::MENU;
class MenuViewTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void MenuViewTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void MenuViewTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void MenuViewTestNg::SetUp() {}
void MenuViewTestNg::TearDown() {}

/**
 * @tc.name: MenuViewTestNgCreate001
 * @tc.desc: Verify Create.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, MenuViewTestNgCreate001, TestSize.Level1)
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
    auto children = menuNode->GetChildren();
    ASSERT_EQ(children.size(), 2);
    auto firstChild = AceType::DynamicCast<FrameNode>(menuNode->GetChildAtIndex(0));
    ASSERT_NE(firstChild, nullptr);
    EXPECT_EQ(firstChild->GetTag(), V2::OPTION_ETS_TAG);
    auto firstPattern = firstChild->GetPattern<OptionPattern>();
    ASSERT_NE(firstPattern, nullptr);
    EXPECT_EQ(firstPattern->GetText(), "MenuItem1");
    EXPECT_EQ(firstPattern->GetIcon(), "fakeIcon");
    auto secondChild = AceType::DynamicCast<FrameNode>(menuNode->GetChildAtIndex(1));
    ASSERT_NE(secondChild, nullptr);
    EXPECT_EQ(secondChild->GetTag(), V2::OPTION_ETS_TAG);
    auto secondPattern = secondChild->GetPattern<OptionPattern>();
    ASSERT_NE(secondPattern, nullptr);
    EXPECT_EQ(secondPattern->GetText(), "MenuItem2");
    EXPECT_EQ(secondPattern->GetIcon(), "");
}

/**
 * @tc.name: MenuViewTestNgCreate002
 * @tc.desc: Verify Create.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, MenuViewTestNgCreate002, TestSize.Level1)
{
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "fakeIcon", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam;
    menuParam.title = "Title";
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), TARGET_ID, TYPE, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->OnModifyDone();
    auto children = menuNode->GetChildren();
    ASSERT_EQ(children.size(), 3);
    auto titleChild = AceType::DynamicCast<FrameNode>(menuNode->GetChildAtIndex(0));
    ASSERT_NE(titleChild, nullptr);
    EXPECT_EQ(titleChild->GetTag(), V2::TEXT_ETS_TAG);
    auto textProperty = titleChild->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);
    EXPECT_TRUE(textProperty->GetContent().has_value());
    EXPECT_EQ(textProperty->GetContent().value(), "Title");
}

/**
 * @tc.name: MenuViewTestNgCreate003
 * @tc.desc: Verify Create.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, MenuViewTestNgCreate003, TestSize.Level1)
{
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    MenuParam menuParam;
    menuParam.positionOffset = {10.0f, 10.0f};
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto menuWrapperNode = MenuView::Create(textNode, TARGET_ID, TYPE, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF(10.0f, 10.0f));
}

/**
 * @tc.name: MenuViewTestNgSetFontSize001
 * @tc.desc: Verify SetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, MenuViewTestNgSetFontSize001, TestSize.Level1)
{
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem", "", nullptr);
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
    ViewStackProcessor::GetInstance()->Push(menuNode);
    MenuView::SetFontSize(Dimension(50.0));
    ASSERT_TRUE(property->GetFontSize().has_value());
    EXPECT_EQ(property->GetFontSize().value(), Dimension(50.0));
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: MenuViewTestNgSetFontSize002
 * @tc.desc: Verify SetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, MenuViewTestNgSetFontSize002, TestSize.Level1)
{
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem", "", nullptr);
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
    ViewStackProcessor::GetInstance()->Push(menuNode);
    MenuView::SetFontSize(Dimension());
    EXPECT_FALSE(property->GetFontSize().has_value());
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: MenuViewTestNgSetFontSize003
 * @tc.desc: Verify SetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, MenuViewTestNgSetFontSize003, TestSize.Level1)
{
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem", "", nullptr);
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
    MenuView::SetFontSize(Dimension(50.0));
    ASSERT_FALSE(property->GetFontSize().has_value());
}

/**
 * @tc.name: MenuViewTestNgSetFontColor001
 * @tc.desc: Verify SetFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, MenuViewTestNgSetFontColor001, TestSize.Level1)
{
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem", "", nullptr);
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
    ViewStackProcessor::GetInstance()->Push(menuNode);
    MenuView::SetFontColor(Color::RED);
    ASSERT_TRUE(property->GetFontColor().has_value());
    EXPECT_EQ(property->GetFontColor().value(), Color::RED);
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: MenuViewTestNgSetFontColor002
 * @tc.desc: Verify SetFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, MenuViewTestNgSetFontColor002, TestSize.Level1)
{
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem", "", nullptr);
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
    MenuView::SetFontColor(Color::RED);
    ASSERT_FALSE(property->GetFontColor().has_value());
}

/**
 * @tc.name: MenuViewTestNgSetFontColor003
 * @tc.desc: Verify SetFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, MenuViewTestNgSetFontColor003, TestSize.Level1)
{
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem", "", nullptr);
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
    ViewStackProcessor::GetInstance()->Push(menuNode);
    MenuView::SetFontColor(Color::RED);
    ASSERT_TRUE(property->GetFontColor().has_value());
    EXPECT_EQ(property->GetFontColor().value(), Color::RED);
    MenuView::SetFontColor(std::nullopt);
    ASSERT_FALSE(property->GetFontColor().has_value());
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: MenuViewTestNgSetFontWeight001
 * @tc.desc: Verify SetFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, MenuViewTestNgSetFontWeight001, TestSize.Level1)
{
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem", "", nullptr);
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
    ViewStackProcessor::GetInstance()->Push(menuNode);
    MenuView::SetFontWeight(FontWeight::BOLDER);
    ASSERT_TRUE(property->GetFontWeight().has_value());
    EXPECT_EQ(property->GetFontWeight().value(), FontWeight::BOLDER);
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: MenuViewTestNgSetFontWeight002
 * @tc.desc: Verify SetFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, MenuViewTestNgSetFontWeight002, TestSize.Level1)
{
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem", "", nullptr);
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
    MenuView::SetFontWeight(FontWeight::BOLDER);
    ASSERT_FALSE(property->GetFontWeight().has_value());
}
} // namespace
} // namespace OHOS::Ace::NG
