/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"

#include "core/components/common/properties/placement.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/property/geometry_property.h"
#include "test/mock/frameworks/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TARGET_ID = 3;
constexpr MenuType TYPE = MenuType::MENU;
const std::string EMPTY_TEXT = "";

} // namespace

class MenuPatternGetAdjustedPosTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> CreateMenuFrameNode();
    RefPtr<MenuPattern> menuPattern_;
    RefPtr<FrameNode> menuFrameNode_;
};

void MenuPatternGetAdjustedPosTestNg::SetUpTestCase() {}

void MenuPatternGetAdjustedPosTestNg::TearDownTestCase() {}

void MenuPatternGetAdjustedPosTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockContainer::SetUp();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuPatternGetAdjustedPosTestNg::TearDown()
{
    MockPipelineContext::TearDown();
    menuPattern_ = nullptr;
    menuFrameNode_ = nullptr;
    MockContainer::TearDown();
}

RefPtr<FrameNode> MenuPatternGetAdjustedPosTestNg::CreateMenuFrameNode()
{
    auto node = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, EMPTY_TEXT, TYPE); });
    CHECK_NULL_RETURN(node, nullptr);
    auto geometryNode = node->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, nullptr);
    return node;
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition001
 * @tc.desc: Test when host is nullptr, return menuPosition directly
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, EMPTY_TEXT, TYPE);
    ASSERT_NE(pattern, nullptr);
    OffsetF menuPosition(50.0f, 100.0f);
    auto result = pattern->GetAdjustedExtensionMenuPosition(menuPosition);
    EXPECT_EQ(result.GetX(), menuPosition.GetX());
    EXPECT_EQ(result.GetY(), menuPosition.GetY());
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition002
 * @tc.desc: Test when host exists but geometryNode is nullptr, return menuPosition
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition002, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto originalGeometryNode = menuFrameNode_->GetGeometryNode();
    menuFrameNode_->SetGeometryNode(nullptr);
    OffsetF menuPosition(50.0f, 100.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    EXPECT_EQ(result.GetX(), menuPosition.GetX());
    EXPECT_EQ(result.GetY(), menuPosition.GetY());
    menuFrameNode_->SetGeometryNode(originalGeometryNode);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition003
 * @tc.desc: Test Placement::BOTTOM branch - extensionTop >= selectTop
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition003, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(200.0f, 50.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 100.0f, 300.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 120.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), selectMenuPaintRect.Top(), 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition004
 * @tc.desc: Test Placement::TOP branch - extensionTop < selectTop && extensionBottom <= selectBottom
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition004, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(200.0f, 50.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 100.0f, 300.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 80.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    float expectedY = selectMenuPaintRect.Bottom() - extensionMenuSize.Height();
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), expectedY, 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition005
 * @tc.desc: Test Placement::NONE branch - extensionTop < selectTop && extensionBottom > selectBottom
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition005, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(200.0f, 300.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 100.0f, 300.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 80.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), menuPosition.GetY(), 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition006
 * @tc.desc: Test Placement::TOP with extensionTop exactly at selectTop (boundary - should be BOTTOM)
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition006, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(200.0f, 50.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 100.0f, 300.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 100.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), selectMenuPaintRect.Top(), 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition007
 * @tc.desc: Test with extensionMenuSize wider than selectMenu - X adjustment goes negative
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition007, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(400.0f, 50.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 100.0f, 200.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 120.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), selectMenuPaintRect.Top(), 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition008
 * @tc.desc: Test Placement::TOP when extensionTop slightly below selectTop and extensionBottom within selectBottom
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition008, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(200.0f, 50.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 99.9f, 300.0f, 200.1f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 90.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    float expectedY = selectMenuPaintRect.Bottom() - extensionMenuSize.Height();
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), expectedY, 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition009
 * @tc.desc: Test Placement::BOTTOM with extensionTop slightly above selectTop, extensionBottom above selectBottom
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition009, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(200.0f, 50.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 101.0f, 300.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 100.5f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), selectMenuPaintRect.Top(), 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition010
 * @tc.desc: Test Placement::NONE - extensionMenu straddles selectMenu (top above, bottom below)
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition010, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(200.0f, 250.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 100.0f, 300.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 90.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), menuPosition.GetY(), 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition011
 * @tc.desc: Test Placement::TOP - extension exactly fits within selectMenu vertically
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition011, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(200.0f, 200.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 100.0f, 300.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 0.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    float expectedY = selectMenuPaintRect.Bottom() - extensionMenuSize.Height();
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), expectedY, 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition012
 * @tc.desc: Test with zero-sized extensionMenu
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition012, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(0.0f, 0.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 100.0f, 300.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 120.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), selectMenuPaintRect.Top(), 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition013
 * @tc.desc: Test with zero-sized selectMenuPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition013, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(200.0f, 50.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 0.0f, 0.0f, 0.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 0.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    EXPECT_NEAR(result.GetX(), 0.0f - (0.0f - 200.0f) / 2.0f, 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition014
 * @tc.desc: Test Placement::BOTTOM - extension entirely below selectMenu
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition014, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(200.0f, 50.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 100.0f, 300.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 200.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), selectMenuPaintRect.Top(), 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition015
 * @tc.desc: Test Placement::TOP - extension entirely above selectMenu
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition015, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(200.0f, 50.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 100.0f, 300.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 10.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    float expectedY = selectMenuPaintRect.Bottom() - extensionMenuSize.Height();
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), expectedY, 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition016
 * @tc.desc: Test with same width for extension and select - X should align left
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition016, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(300.0f, 50.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 100.0f, 300.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 120.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), selectMenuPaintRect.Top(), 0.01f);
}

/**
 * @tc.name: GetSelectMenuPaintRect001
 * @tc.desc: Test GetSelectMenuPaintRect returns set value
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetSelectMenuPaintRect001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, EMPTY_TEXT, TYPE);
    ASSERT_NE(pattern, nullptr);
    RectF rect(10.0f, 20.0f, 100.0f, 200.0f);
    pattern->SetSelectMenuPaintRect(rect);
    auto result = pattern->GetSelectMenuPaintRect();
    EXPECT_EQ(result.Left(), rect.Left());
    EXPECT_EQ(result.Top(), rect.Top());
    EXPECT_EQ(result.Width(), rect.Width());
    EXPECT_EQ(result.Height(), rect.Height());
}

/**
 * @tc.name: GetSelectMenuPaintRect002
 * @tc.desc: Test GetSelectMenuPaintRect default value
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetSelectMenuPaintRect002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, EMPTY_TEXT, TYPE);
    ASSERT_NE(pattern, nullptr);
    auto result = pattern->GetSelectMenuPaintRect();
    EXPECT_EQ(result.Left(), 0.0f);
    EXPECT_EQ(result.Top(), 0.0f);
    EXPECT_EQ(result.Width(), 0.0f);
    EXPECT_EQ(result.Height(), 0.0f);
}

/**
 * @tc.name: SetSelectMenuPaintRect001
 * @tc.desc: Test SetSelectMenuPaintRect sets value correctly
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, SetSelectMenuPaintRect001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, EMPTY_TEXT, TYPE);
    ASSERT_NE(pattern, nullptr);
    RectF rect1(10.0f, 20.0f, 100.0f, 200.0f);
    pattern->SetSelectMenuPaintRect(rect1);
    auto result1 = pattern->GetSelectMenuPaintRect();
    EXPECT_EQ(result1.Left(), 10.0f);
    RectF rect2(30.0f, 40.0f, 200.0f, 300.0f);
    pattern->SetSelectMenuPaintRect(rect2);
    auto result2 = pattern->GetSelectMenuPaintRect();
    EXPECT_EQ(result2.Left(), 30.0f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition017
 * @tc.desc: Test with non-zero selectMenuPaintRect.Left() - X should offset from non-zero left
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition017, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(200.0f, 50.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(50.0f, 100.0f, 300.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 120.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), selectMenuPaintRect.Top(), 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition018
 * @tc.desc: Test Placement::TOP boundary - extensionBottom exactly equals selectBottom
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition018, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(200.0f, 100.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 100.0f, 300.0f, 100.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 0.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    float expectedY = selectMenuPaintRect.Bottom() - extensionMenuSize.Height();
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), expectedY, 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition019
 * @tc.desc: Test Placement::NONE - extensionTop < selectTop but extensionBottom slightly above selectBottom
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition019, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(200.0f, 201.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 100.0f, 300.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 99.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), menuPosition.GetY(), 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition020
 * @tc.desc: Test with negative selectMenuPaintRect position
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition020, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(200.0f, 50.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(-50.0f, -100.0f, 300.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, -80.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition021
 * @tc.desc: Test Placement::BOTTOM with same width - X equals selectMenuPaintRect.Left()
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition021, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(300.0f, 200.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 100.0f, 300.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 100.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), selectMenuPaintRect.Top(), 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition022
 * @tc.desc: Test Placement::TOP with non-zero Left - verify X offset and Y calculation
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition022, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(100.0f, 50.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(20.0f, 50.0f, 300.0f, 100.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(20.0f, 40.0f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = 20.0f + (300.0f - 100.0f) / 2.0f;
    float expectedY = 150.0f - 50.0f;
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
    EXPECT_NEAR(result.GetY(), expectedY, 0.01f);
}

/**
 * @tc.name: GetAdjustedExtensionMenuPosition023
 * @tc.desc: Test Placement::NONE with extensionTop slightly below selectTop (within epsilon)
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternGetAdjustedPosTestNg, GetAdjustedExtensionMenuPosition023, TestSize.Level1)
{
    menuFrameNode_ = CreateMenuFrameNode();
    ASSERT_NE(menuFrameNode_, nullptr);
    menuPattern_ = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern_, nullptr);
    auto geometryNode = menuFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF extensionMenuSize(200.0f, 300.0f);
    geometryNode->SetFrameSize(extensionMenuSize);
    RectF selectMenuPaintRect(0.0f, 100.0f, 300.0f, 200.0f);
    menuPattern_->SetSelectMenuPaintRect(selectMenuPaintRect);
    OffsetF menuPosition(50.0f, 99.999f);
    auto result = menuPattern_->GetAdjustedExtensionMenuPosition(menuPosition);
    float expectedX = selectMenuPaintRect.Left() +
        (selectMenuPaintRect.Width() - extensionMenuSize.Width()) / 2.0f;
    EXPECT_NEAR(result.GetX(), expectedX, 0.01f);
}
} // namespace OHOS::Ace::NG