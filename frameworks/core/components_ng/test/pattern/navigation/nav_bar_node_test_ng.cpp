/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#define protected public
#define private public

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_view.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string BAR_ITEM_ETS_TAG = "BarItem";
const std::string FRAME_ITEM_ETS_TAG = "FrameItem";
const char NAVBAR_CONTENT_ETS_TAG[] = "NavBarContent";
const char TEXT_ETS_TAG[] = "Text";
const std::string EMPTY_STRING = "";
const int32_t RET_OK = 0;
} // namespace

class NavBarNodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override;
    void TearDown() override;
};

void NavBarNodeTestNg::SetUp() {}
void NavBarNodeTestNg::TearDown() {}

/**
 * @tc.name: GetOrCreateNavBarNode001
 * @tc.desc: Test create nav bar node.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, GetOrCreateNavBarNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto frameNode = FrameNode::GetFrameNode(barTag, nodeId);
    EXPECT_EQ(frameNode, nullptr);
    RefPtr<NavBarNode> navBarNode = barNode->GetOrCreateNavBarNode(barTag, nodeId, nullptr);
    EXPECT_NE(navBarNode, nullptr);
}

/**
 * @tc.name: GetOrCreateNavBarNode002
 * @tc.desc: Test get nav bar node.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, GetOrCreateNavBarNode002, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto node = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    node->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(node);
    auto frameNode = FrameNode::GetFrameNode(barTag, nodeId);
    RefPtr<NavBarNode> navBarNode = barNode->GetOrCreateNavBarNode(barTag, nodeId, nullptr);
    EXPECT_NE(navBarNode, nullptr);
}

/**
 * @tc.name: AddChildToGroup001
 * @tc.desc: Test add nav bar content node child to group.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, AddChildToGroup001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    std::string frameTag = FRAME_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(frameTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto navBarNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode(
            NAVBAR_CONTENT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navBarNode->SetNavBarContentNode(contentNode);
    navBarNode->AddChildToGroup(frameNode);
    auto group = navBarNode->GetNavBarContentNode();
    EXPECT_NE(group, nullptr);
}

/**
 * @tc.name: AddChildToGroup002
 * @tc.desc: Test add new content node child to group.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, AddChildToGroup002, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    std::string frameTag = FRAME_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(frameTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto navBarNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<NavBarPattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode(
            NAVBAR_CONTENT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navBarNode->AddChildToGroup(frameNode);
    auto group = navBarNode->GetNavBarContentNode();
    EXPECT_EQ(group, nullptr);
}

/**
 * @tc.name: GetTitleString001
 * @tc.desc: Test get title string with error tag.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, GetTitleString001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    std::string frameTag = FRAME_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(BAR_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    auto frameNode = AceType::MakeRefPtr<FrameNode>(frameTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetTitle(frameNode);
    auto ret = barNode->GetTitleString();
    EXPECT_EQ(ret, EMPTY_STRING);
}

/**
 * @tc.name: GetTitleString002
 * @tc.desc: Test get title string with right tag.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, GetTitleString002, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    std::string textTag = TEXT_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto frameNode = AceType::MakeRefPtr<FrameNode>(textTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetTitle(frameNode);
    auto ret = barNode->GetTitleString();
    EXPECT_EQ(ret, EMPTY_STRING);
}

/**
 * @tc.name: GetSubtitleString001
 * @tc.desc: Test get sub title string with error tag.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, GetSubtitleString001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    std::string frameTag = FRAME_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(BAR_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    auto frameNode = AceType::MakeRefPtr<FrameNode>(frameTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetSubtitle(frameNode);
    auto ret = barNode->GetSubtitleString();
    EXPECT_EQ(ret, EMPTY_STRING);
}

/**
 * @tc.name: GetSubtitleString002
 * @tc.desc: Test get sub title string with right tag.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, GetSubtitleString002, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    std::string textTag = TEXT_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto frameNode = AceType::MakeRefPtr<FrameNode>(textTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetSubtitle(frameNode);
    auto ret = barNode->GetSubtitleString();
    EXPECT_EQ(ret, EMPTY_STRING);
}

/**
 * @tc.name: GetBarItemsString001
 * @tc.desc: Test get bar items string without menu.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, GetBarItemsString001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetBarItemsString(false);
    EXPECT_EQ(ret, EMPTY_STRING);
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test to json value.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, ToJsonValue001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto json = JsonUtil::Create(true);
    barNode->ToJsonValue(json);
    EXPECT_EQ(json->GetValue("title")->GetString(), EMPTY_STRING);
    EXPECT_EQ(json->GetValue("subtitle")->GetString(), EMPTY_STRING);
    EXPECT_EQ(json->GetValue("menus")->GetString(), EMPTY_STRING);
    EXPECT_EQ(json->GetValue("toolBar")->GetString(), EMPTY_STRING);
}

/**
 * @tc.name: IsAtomicNode001
 * @tc.desc: Test IsAtomicNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, IsAtomicNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->IsAtomicNode();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetBackButton001
 * @tc.desc: Test SetBackButton interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, SetBackButton001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetBackButton(nullptr);
    EXPECT_EQ(barNode->backButton_, nullptr);
}

/**
 * @tc.name: GetBackButton001
 * @tc.desc: Test GetBackButton interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, GetBackButton001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetBackButton();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetTitle001
 * @tc.desc: Test SetTitle interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, SetTitle001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetTitle(nullptr);
    EXPECT_EQ(barNode->title_, nullptr);
}

/**
 * @tc.name: GetTitle001
 * @tc.desc: Test GetTitle interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, GetTitle001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetTitle();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetSubtitle001
 * @tc.desc: Test SetSubtitle interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, SetSubtitle001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetSubtitle(nullptr);
    EXPECT_EQ(barNode->subtitle_, nullptr);
}

/**
 * @tc.name: GetSubtitle001
 * @tc.desc: Test GetSubtitle interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, GetSubtitle001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetSubtitle();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetMenu001
 * @tc.desc: Test SetMenu interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, SetMenu001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetMenu(nullptr);
    EXPECT_EQ(barNode->menu_, nullptr);
}

/**
 * @tc.name: GetMenu001
 * @tc.desc: Test GetMenu interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, GetMenu001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetMenu();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetTitleBarNode001
 * @tc.desc: Test SetTitleBarNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, SetTitleBarNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetTitleBarNode(nullptr);
    EXPECT_EQ(barNode->titleBarNode_, nullptr);
}

/**
 * @tc.name: GetTitleBarNode001
 * @tc.desc: Test GetTitleBarNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, GetTitleBarNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetTitleBarNode();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetNavBarContentNode001
 * @tc.desc: Test SetNavBarContentNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, SetNavBarContentNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetNavBarContentNode(nullptr);
    EXPECT_EQ(barNode->navBarContentNode_, nullptr);
}

/**
 * @tc.name: GetNavBarContentNode001
 * @tc.desc: Test GetNavBarContentNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, GetNavBarContentNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetNavBarContentNode();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetToolBarNode001
 * @tc.desc: Test SetToolBarNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, SetToolBarNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetToolBarNode(nullptr);
    EXPECT_EQ(barNode->toolBarNode_, nullptr);
}

/**
 * @tc.name: GetToolBarNode001
 * @tc.desc: Test GetToolBarNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, GetToolBarNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetToolBarNode();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetPreToolBarNode001
 * @tc.desc: Test SetPreToolBarNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, SetPreToolBarNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetPreToolBarNode(nullptr);
    EXPECT_EQ(barNode->preToolBarNode_, nullptr);
}

/**
 * @tc.name: GetPreToolBarNode001
 * @tc.desc: Test GetPreToolBarNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, GetPreToolBarNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetPreToolBarNode();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: OnPrevTitleIsCustomUpdate001
 * @tc.desc: Test OnPrevTitleIsCustomUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, OnPrevTitleIsCustomUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t ret = RET_OK;
    barNode->OnPrevTitleIsCustomUpdate(true);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: OnPrevMenuIsCustomUpdate001
 * @tc.desc: Test OnPrevMenuIsCustomUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, OnPrevMenuIsCustomUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t ret = RET_OK;
    barNode->OnPrevMenuIsCustomUpdate(true);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: OnPrevToolBarIsCustomUpdate001
 * @tc.desc: Test OnPrevToolBarIsCustomUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, OnPrevToolBarIsCustomUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t ret = RET_OK;
    barNode->OnPrevToolBarIsCustomUpdate(true);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: OnBackButtonNodeOperationUpdate001
 * @tc.desc: Test OnBackButtonNodeOperationUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, OnBackButtonNodeOperationUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t ret = RET_OK;
    ChildNodeOperation value = ChildNodeOperation::ADD;
    barNode->OnBackButtonNodeOperationUpdate(value);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: OnTitleNodeOperationUpdate001
 * @tc.desc: Test OnTitleNodeOperationUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, OnTitleNodeOperationUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t ret = RET_OK;
    ChildNodeOperation value = ChildNodeOperation::ADD;
    barNode->OnTitleNodeOperationUpdate(value);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: OnSubtitleNodeOperationUpdate001
 * @tc.desc: Test OnSubtitleNodeOperationUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, OnSubtitleNodeOperationUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t ret = RET_OK;
    ChildNodeOperation value = ChildNodeOperation::ADD;
    barNode->OnSubtitleNodeOperationUpdate(value);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: OnMenuNodeOperationUpdate001
 * @tc.desc: Test OnMenuNodeOperationUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, OnMenuNodeOperationUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t ret = RET_OK;
    ChildNodeOperation value = ChildNodeOperation::ADD;
    barNode->OnMenuNodeOperationUpdate(value);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: OnToolBarNodeOperationUpdate001
 * @tc.desc: Test OnToolBarNodeOperationUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarNodeTestNg, OnToolBarNodeOperationUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t ret = RET_OK;
    ChildNodeOperation value = ChildNodeOperation::ADD;
    barNode->OnToolBarNodeOperationUpdate(value);
    EXPECT_EQ(ret, RET_OK);
}
} // namespace OHOS::Ace::NG
