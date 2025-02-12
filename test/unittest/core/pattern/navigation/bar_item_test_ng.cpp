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

#define protected public
#define private public

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TOAST_ETS_TAG = "Toast";
const std::string BAR_ITEM_ETS_TAG = "BarItem";
const std::string EMPTY_STRING = "";
const std::string BAR_ITEM_TEXT = "text";
const std::string EMPTY_TEXT;
} // namespace

class BarItemTestNg : public testing::Test {
public:
    void InitBarItemTestNg();
    void DestroyBarItemObject();

    RefPtr<BarItemNode> frameNode_;
    RefPtr<BarItemPattern> barItemPattern_;
};

void BarItemTestNg::DestroyBarItemObject()
{
    frameNode_ = nullptr;
    barItemPattern_ = nullptr;
}

void BarItemTestNg::InitBarItemTestNg()
{
    auto barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    frameNode_ = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, barItemNodeId, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    frameNode_->InitializePatternAndContext();
    barItemPattern_ = frameNode_->GetPattern<BarItemPattern>();
    ASSERT_NE(barItemPattern_, nullptr);
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->SetTextNode(textNode);
}

/**
 * @tc.name: CreateLayoutProperty001
 * @tc.desc: Test CreateLayoutProperty interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemTestNg, CreateLayoutProperty001, TestSize.Level1)
{
    auto barItemPattern = AceType::MakeRefPtr<BarItemPattern>();
    auto ret = barItemPattern->CreateLayoutProperty();
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: CreateLayoutAlgorithm001
 * @tc.desc: Test CreateLayoutAlgorithm interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemTestNg, CreateLayoutAlgorithm001, TestSize.Level1)
{
    auto barItemPattern = AceType::MakeRefPtr<BarItemPattern>();
    auto ret = barItemPattern->CreateLayoutAlgorithm();
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: CreateEventHub001
 * @tc.desc: Test CreateEventHub interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemTestNg, CreateEventHub001, TestSize.Level1)
{
    auto barItemPattern = AceType::MakeRefPtr<BarItemPattern>();
    auto ret = barItemPattern->CreateEventHub();
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: IsAtomicNode002
 * @tc.desc: Test IsAtomicNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemTestNg, IsAtomicNode002, TestSize.Level1)
{
    auto barItemPattern = AceType::MakeRefPtr<BarItemPattern>();
    auto ret = barItemPattern->IsAtomicNode();
    EXPECT_NE(ret, true);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test OnModifyDone interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemTestNg, OnModifyDone001, TestSize.Level1)
{
    auto itemNode = FrameNode::CreateFrameNode(TOAST_ETS_TAG, 0, AceType::MakeRefPtr<BarItemPattern>());
    EXPECT_TRUE(itemNode != nullptr);
    auto barItemPattern = AceType::MakeRefPtr<BarItemPattern>();
    barItemPattern->clickListener_ = nullptr;
    barItemPattern->AttachToFrameNode(itemNode);
    barItemPattern->OnModifyDone();
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Test OnModifyDone interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemTestNg, OnModifyDone002, TestSize.Level1)
{
    auto itemNode = FrameNode::CreateFrameNode(TOAST_ETS_TAG, 0, AceType::MakeRefPtr<BarItemPattern>());
    EXPECT_TRUE(itemNode != nullptr);
    auto barItemPattern = AceType::MakeRefPtr<BarItemPattern>();
    barItemPattern->clickListener_ = AceType::MakeRefPtr<ClickEvent>(nullptr);
    barItemPattern->AttachToFrameNode(itemNode);
    barItemPattern->OnModifyDone();
}

/**
 * @tc.name: IsAtomicNode001
 * @tc.desc: Test IsAtomicNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemTestNg, IsAtomicNode001, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto ret = barItemNode->IsAtomicNode();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetTextNode001
 * @tc.desc: Test SetTextNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemTestNg, SetTextNode001, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    barItemNode->SetTextNode(nullptr);
    EXPECT_EQ(barItemNode->text_, nullptr);
}

/**
 * @tc.name: GetTextNode001
 * @tc.desc: Test GetTextNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemTestNg, GetTextNode001, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto ret = barItemNode->GetTextNode();
    EXPECT_EQ(ret, nullptr);
}

/**
 * @tc.name: SetIconNode001
 * @tc.desc: Test SetIconNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemTestNg, SetIconNode001, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    barItemNode->SetIconNode(nullptr);
    EXPECT_EQ(barItemNode->icon_, nullptr);
}

/**
 * @tc.name: GetIconNode001
 * @tc.desc: Test GetIconNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemTestNg, GetIconNode001, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto ret = barItemNode->GetIconNode();
    EXPECT_EQ(ret, nullptr);
}

/**
 * @tc.name: BarItemPattern001
 * @tc.desc: Test barItem pattern.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemTestNg, BarItemPattern001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialization.
     */
    InitBarItemTestNg();
    auto iconNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(iconNode, nullptr);
    frameNode_->SetIconNode(iconNode);

    /**
     * @tc.steps: step2. test whether active icon can be set successful.
     * @tc.expected: active icon getting from Get function is equal to icon by setting function.
     */
    ImageSourceInfo activeIconInfo("");
    barItemPattern_->SetActiveIconImageSourceInfo(activeIconInfo);
    EXPECT_EQ(barItemPattern_->GetActiveIconImageSourceInfo(), activeIconInfo);

    /**
     * @tc.steps: step3. test whether initial icon can be set successful.
     * @tc.expected: initial icon getting from Get function is equal to icon by Set function.
     */
    ImageSourceInfo initialIconInfo("");
    barItemPattern_->SetInitialIconImageSourceInfo(initialIconInfo);
    EXPECT_EQ(barItemPattern_->GetInitialIconImageSourceInfo(), initialIconInfo);

    /**
     * @tc.steps: step4. test whether toolbar item status is active.
     * @tc.expected: toolbar item status is active.
     */
    barItemPattern_->SetToolbarItemStatus(NavToolbarItemStatus::ACTIVE);
    EXPECT_EQ(barItemPattern_->GetToolbarItemStatus(), NavToolbarItemStatus::ACTIVE);

    /**
     * @tc.steps: step5. test whether toolbar icon status is initial.
     * @tc.expected: toolbar icon status is initial.
     */
    barItemPattern_->SetCurrentIconStatus(ToolbarIconStatus::INITIAL);
    EXPECT_EQ(barItemPattern_->GetCurrentIconStatus(), ToolbarIconStatus::INITIAL);
    DestroyBarItemObject();
}

/**
 * @tc.name: SetIsHideItemText001
 * @tc.desc: Test SetIsHideItemText interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemTestNg, SetToolBarItemHideText001, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    bool hideText = true;
    barItemNode->SetIsHideItemText(hideText);
    bool result = barItemNode->isHideText_;
    EXPECT_EQ(result, hideText);
}

/**
 * @tc.name: SetIsHideItemText002
 * @tc.desc: Test SetIsHideItemText interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemTestNg, SetToolBarItemHideText002, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    bool showText = false;
    barItemNode->SetIsHideItemText(showText);
    bool result = barItemNode->isHideText_;
    EXPECT_EQ(result, showText);
}

/**
 * @tc.name: IsHideItemText001
 * @tc.desc: Test IsHideItemText interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemTestNg, IsToolBarItemHideText001, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    bool hideText = true;
    barItemNode->SetIsHideItemText(hideText);
    bool result = barItemNode->IsHideText();
    EXPECT_EQ(result, hideText);
}

/**
 * @tc.name: IsHideItemText002
 * @tc.desc: Test IsHideItemText interface.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemTestNg, IsToolBarItemHideText002, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    bool showText = false;
    barItemNode->SetIsHideItemText(showText);
    bool result = barItemNode->IsHideText();
    EXPECT_EQ(result, showText);
}
} // namespace OHOS::Ace::NG
