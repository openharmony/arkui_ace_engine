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

#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_view.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_pattern.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class MenuItemPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void MenuItemPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void MenuItemPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void MenuItemPatternTestNg::SetUp() {}
void MenuItemPatternTestNg::TearDown() {}

/**
 * @tc.name: MenuItemPatternTestNgAddSelectIcon001
 * @tc.desc: Verify AddSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgAddSelectIcon001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MenuItemView::Create(itemOption);
    MenuItemView::SetSelectIcon(false);
    MenuItemView::SetSelectIconSrc("selectIcon.png");
    MenuItemView::SetSelected(true);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));
    EXPECT_EQ(rightRow->GetChildren().size(), 0u);

    // call AddSelectIcon
    itemPattern->OnModifyDone();

    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    EXPECT_EQ(rightRow->GetChildren().size(), 0u);
}

/**
 * @tc.name: MenuItemPatternTestNgAddSelectIcon002
 * @tc.desc: Verify AddSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgAddSelectIcon002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MenuItemView::Create(itemOption);
    MenuItemView::SetSelectIcon(true);
    MenuItemView::SetSelectIconSrc("");
    MenuItemView::SetSelected(true);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));
    EXPECT_EQ(rightRow->GetChildren().size(), 0u);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<IconTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<SelectTheme>()));
    // call AddSelectIcon
    itemPattern->OnModifyDone();

    EXPECT_EQ(rightRow->GetChildren().size(), 0u);
    ASSERT_EQ(leftRow->GetChildren().size(), 1u);
    auto selectIconNode = AceType::DynamicCast<FrameNode>(leftRow->GetChildAtIndex(0));
    ASSERT_NE(selectIconNode, nullptr);
    EXPECT_EQ(selectIconNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = selectIconNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = selectIconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto sourceInfo = imageLayoutProperty->GetImageSourceInfo();
    EXPECT_TRUE(sourceInfo.has_value());
}

/**
 * @tc.name: MenuItemPatternTestNgAddSelectIcon003
 * @tc.desc: Verify AddSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgAddSelectIcon003, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MenuItemView::Create(itemOption);
    MenuItemView::SetSelectIcon(true);
    MenuItemView::SetSelectIconSrc("selectIcon.png");
    MenuItemView::SetSelected(false);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));
    EXPECT_EQ(rightRow->GetChildren().size(), 0u);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<IconTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<SelectTheme>()));
    // call AddSelectIcon
    itemPattern->OnModifyDone();

    EXPECT_EQ(rightRow->GetChildren().size(), 0u);
    ASSERT_EQ(leftRow->GetChildren().size(), 1u);
    auto selectIconNode = AceType::DynamicCast<FrameNode>(leftRow->GetChildAtIndex(0));
    ASSERT_NE(selectIconNode, nullptr);
    EXPECT_EQ(selectIconNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = selectIconNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = selectIconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto sourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_TRUE(sourceInfo.has_value());
    EXPECT_EQ(sourceInfo.value().GetSrc(), "selectIcon.png");
}

/**
 * @tc.name: MenuItemPatternTestNgAddSelectIcon004
 * @tc.desc: Verify AddSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgAddSelectIcon004, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MenuItemView::Create(itemOption);
    MenuItemView::SetSelectIcon(true);
    MenuItemView::SetSelectIconSrc("selectIcon.png");
    MenuItemView::SetSelected(false);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));
    EXPECT_EQ(rightRow->GetChildren().size(), 0u);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<IconTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<SelectTheme>()));
    // call AddSelectIcon
    itemPattern->OnModifyDone();

    EXPECT_EQ(rightRow->GetChildren().size(), 0u);
    ASSERT_EQ(leftRow->GetChildren().size(), 1u);
    auto selectIconNode = AceType::DynamicCast<FrameNode>(leftRow->GetChildAtIndex(0));
    ASSERT_NE(selectIconNode, nullptr);
    EXPECT_EQ(selectIconNode->GetTag(), V2::IMAGE_ETS_TAG);

    itemProperty->UpdateSelectIcon(false);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    // call AddSelectIcon
    itemPattern->OnModifyDone();
    ASSERT_EQ(leftRow->GetChildren().size(), 0u);
}

/**
 * @tc.name: MenuItemPatternTestNgUpdateIcon001
 * @tc.desc: Verify UpdateIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgUpdateIcon001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    itemOption.startIcon = "startIcon.png";
    MenuItemView::Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));

    // call UpdateIcon
    itemPattern->OnModifyDone();

    EXPECT_EQ(rightRow->GetChildren().size(), 0u);
    ASSERT_EQ(leftRow->GetChildren().size(), 1u);
    auto startIconNode = AceType::DynamicCast<FrameNode>(leftRow->GetChildAtIndex(0));
    ASSERT_NE(startIconNode, nullptr);
    EXPECT_EQ(startIconNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = startIconNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = startIconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto sourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_TRUE(sourceInfo.has_value());
    EXPECT_EQ(sourceInfo.value().GetSrc(), "startIcon.png");
}

/**
 * @tc.name: MenuItemPatternTestNgUpdateIcon002
 * @tc.desc: Verify UpdateIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgUpdateIcon002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    itemOption.endIcon = "endIcon.png";
    MenuItemView::Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));

    // call UpdateIcon
    itemPattern->OnModifyDone();

    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    ASSERT_EQ(rightRow->GetChildren().size(), 1u);
    auto endIconNode = AceType::DynamicCast<FrameNode>(rightRow->GetChildAtIndex(0));
    ASSERT_NE(endIconNode, nullptr);
    EXPECT_EQ(endIconNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = endIconNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = endIconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto sourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_TRUE(sourceInfo.has_value());
    EXPECT_EQ(sourceInfo.value().GetSrc(), "endIcon.png");

    itemProperty->UpdateEndIcon("endIcon2.png");
    // call UpdateIcon
    itemPattern->OnModifyDone();
    imagePattern = endIconNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imageLayoutProperty = endIconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    sourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_TRUE(sourceInfo.has_value());
    EXPECT_EQ(sourceInfo.value().GetSrc(), "endIcon2.png");
}

/**
 * @tc.name: MenuItemPatternTestNgUpdateText001
 * @tc.desc: Verify UpdateText.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgUpdateText001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemView::Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));

    // call UpdateText
    itemPattern->OnModifyDone();

    EXPECT_EQ(rightRow->GetChildren().size(), 0u);
    ASSERT_EQ(leftRow->GetChildren().size(), 1u);
    auto contentNode = AceType::DynamicCast<FrameNode>(leftRow->GetChildAtIndex(0));
    ASSERT_NE(contentNode, nullptr);
    EXPECT_EQ(contentNode->GetTag(), V2::TEXT_ETS_TAG);
    auto textLayoutProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto content = textLayoutProperty->GetContent();
    ASSERT_TRUE(content.has_value());
    EXPECT_EQ(content.value(), "content");
}

/**
 * @tc.name: MenuItemPatternTestNgUpdateText002
 * @tc.desc: Verify UpdateText.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgUpdateText002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    itemOption.labelInfo = "label";
    MenuItemView::Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));

    // call UpdateText
    itemPattern->OnModifyDone();

    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    ASSERT_EQ(rightRow->GetChildren().size(), 1u);
    auto labelNode = AceType::DynamicCast<FrameNode>(rightRow->GetChildAtIndex(0));
    ASSERT_NE(labelNode, nullptr);
    EXPECT_EQ(labelNode->GetTag(), V2::TEXT_ETS_TAG);
    auto textLayoutProperty = labelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto content = textLayoutProperty->GetContent();
    ASSERT_TRUE(content.has_value());
    EXPECT_EQ(content.value(), "label");
}
} // namespace
} // namespace OHOS::Ace::NG
