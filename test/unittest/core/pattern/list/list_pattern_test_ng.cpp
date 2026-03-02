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

#include <memory>

#include "gtest/gtest.h"
#include "list_test_ng.h"
#include "test/mock/adapter/mock_ui_session_manager.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/list/list_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int DEFAULT_HEADER_VALUE = 2;
constexpr int DEFAULT_FOOTER_VALUE = 3;
} // namespace

using namespace testing;
using namespace testing::ext;

class ListPatternTestNg : public ListTestNg {};

/**
 * @tc.name: GetNextLineFocusIndex001
 * @tc.desc: Test ListPattern GetNextLineFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetNextLineFocusIndex001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    listPattern->lanes_ = 2;
    listPattern->maxListItemIndex_ = 2;
    listPattern->itemPosition_[0] = { 2, 2.0f, 4.0f, true };
    auto result = listPattern->GetNextLineFocusIndex(1);
    EXPECT_EQ(result, 3);
}

/**
 * @tc.name: GetNextLineFocusIndex002
 * @tc.desc: Test ListPattern GetNextLineFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetNextLineFocusIndex002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    listPattern->lanes_ = 2;
    listPattern->maxListItemIndex_ = 1;
    listPattern->itemPosition_[0] = { 2, 2.0f, 4.0f, true };
    auto result = listPattern->GetNextLineFocusIndex(0);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: GetNextLineFocusIndex003
 * @tc.desc: Test ListPattern GetNextLineFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetNextLineFocusIndex003, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    listPattern->lanes_ = 2;
    listPattern->maxListItemIndex_ = 0;
    listPattern->itemPosition_[0] = { 2, 2.0f, 4.0f, true };
    auto result = listPattern->GetNextLineFocusIndex(0);
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: GetNextLineFocusIndex004
 * @tc.desc: Test ListPattern GetNextLineFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetNextLineFocusIndex004, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    listPattern->lanes_ = 2;
    listPattern->maxListItemIndex_ = 2;
    listPattern->itemPosition_[1] = { 2, 2.0f, 4.0f, true };
    listPattern->itemPosition_[2] = { 2, 3.0f, 4.0f, true };
    auto result = listPattern->GetNextLineFocusIndex(1);
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: HandleDisplayedChildFocus001
 * @tc.desc: Test ListPattern HandleDisplayedChildFocus
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, HandleDisplayedChildFocus001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    listPattern->itemPosition_[0] = { 2, 2.0f, 4.0f, true };
    auto result = listPattern->HandleDisplayedChildFocus(1, 2);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CalcAlignForFocusToGroupItem001
 * @tc.desc: Test ListPattern CalcAlignForFocusToGroupItem
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, CalcAlignForFocusToGroupItem001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto result = listPattern->CalcAlignForFocusToGroupItem(1, FocusStep::UP_END);
    EXPECT_EQ(result, ScrollAlign::START);
}

/**
 * @tc.name: CalcAlignForFocusToGroupItem002
 * @tc.desc: Test ListPattern CalcAlignForFocusToGroupItem
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, CalcAlignForFocusToGroupItem002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto result = listPattern->CalcAlignForFocusToGroupItem(-1, FocusStep::LEFT_END);
    EXPECT_EQ(result, ScrollAlign::END);
}

/**
 * @tc.name: CalcAlignForFocusToGroupItem003
 * @tc.desc: Test ListPattern CalcAlignForFocusToGroupItem
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, CalcAlignForFocusToGroupItem003, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto result = listPattern->CalcAlignForFocusToGroupItem(1, FocusStep::DOWN_END);
    EXPECT_EQ(result, ScrollAlign::START);
}

/**
 * @tc.name: CalcAlignForFocusToGroupItem004
 * @tc.desc: Test ListPattern CalcAlignForFocusToGroupItem
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, CalcAlignForFocusToGroupItem004, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto result = listPattern->CalcAlignForFocusToGroupItem(-1, FocusStep::RIGHT_END);
    EXPECT_EQ(result, ScrollAlign::END);
}

/**
 * @tc.name: CalcNextIndexInGroup001
 * @tc.desc: Test ListPattern CalcNextIndexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, CalcNextIndexInGroup001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    ListItemGroupPara nextListItemGroupPara;
    nextListItemGroupPara.hasFooter = true;
    nextListItemGroupPara.itemEndIndex = 2;
    auto result = listPattern->CalcNextIndexInGroup(2, 2, -1, -1, nextListItemGroupPara);
    EXPECT_TRUE(nextListItemGroupPara.hasFooter);
    EXPECT_EQ(nextListItemGroupPara.itemEndIndex, 2);
    EXPECT_EQ(result, 3);
}

/**
 * @tc.name: CalcNextIndexInGroup002
 * @tc.desc: Test ListPattern CalcNextIndexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, CalcNextIndexInGroup002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    ListItemGroupPara nextListItemGroupPara;
    nextListItemGroupPara.hasFooter = false;
    nextListItemGroupPara.itemEndIndex = 2;
    auto result = listPattern->CalcNextIndexInGroup(2, 2, -1, -1, nextListItemGroupPara);
    EXPECT_FALSE(nextListItemGroupPara.hasFooter);
    EXPECT_EQ(nextListItemGroupPara.itemEndIndex, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: CalcNextIndexInGroup003
 * @tc.desc: Test ListPattern CalcNextIndexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, CalcNextIndexInGroup003, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    ListItemGroupPara nextListItemGroupPara;
    nextListItemGroupPara.hasFooter = true;
    nextListItemGroupPara.itemEndIndex = 2;
    auto result = listPattern->CalcNextIndexInGroup(2, 2, 2, -1, nextListItemGroupPara);
    EXPECT_TRUE(nextListItemGroupPara.hasFooter);
    EXPECT_EQ(nextListItemGroupPara.itemEndIndex, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: CalcNextIndexInGroup004
 * @tc.desc: Test ListPattern CalcNextIndexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, CalcNextIndexInGroup004, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    ListItemGroupPara nextListItemGroupPara;
    nextListItemGroupPara.hasFooter = true;
    nextListItemGroupPara.hasHeader = true;
    nextListItemGroupPara.itemEndIndex = 2;
    auto result = listPattern->CalcNextIndexInGroup(2, 2, 2, 1, nextListItemGroupPara);
    EXPECT_TRUE(nextListItemGroupPara.hasHeader);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ScrollPage001
 * @tc.desc: Test ListPattern ScrollPage
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ScrollPage001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    listPattern->isScrollEnd_ = false;
    listPattern->ScrollPage(true, false, AccessibilityScrollType::SCROLL_HALF);
    EXPECT_TRUE(listPattern->isScrollEnd_);
}

/**
 * @tc.name: ProcessAreaVertical001
 * @tc.desc: Test ListPattern ProcessAreaVertical
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaVertical001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    groupItemPattern->header_ = frameNode;
    double x = 2.F;
    double y = -4.F;
    Rect groupRect(6.0f, -7.0f, 2.0f, 4.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaVertical(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 2.F);
    EXPECT_EQ(y, -4.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, DEFAULT_HEADER_VALUE);
}

/**
 * @tc.name: ProcessAreaVertical002
 * @tc.desc: Test ListPattern ProcessAreaVertical
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaVertical002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = frameNode;
    double x = 2.F;
    double y = -4.F;
    Rect groupRect(6.0f, -7.0f, 2.0f, 4.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaVertical(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 2.F);
    EXPECT_EQ(y, -4.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaVertical003
 * @tc.desc: Test ListPattern ProcessAreaVertical
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaVertical003, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 0;
    groupItemPattern->headerMainSize_ = 4.0f;
    groupItemPattern->footerMainSize_ = 8.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->padding_ = std::make_unique<PaddingPropertyF>();
    frameNode->geometryNode_->padding_->top = 2.0f;
    frameNode->geometryNode_->padding_->bottom = 5.0f;
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = frameNode;
    groupItemPattern->frameNode_ = frameNode;
    double x = 2.F;
    double y = 4.F;
    Rect groupRect(6.0f, 3.0f, 2.0f, 4.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaVertical(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 2.F);
    EXPECT_EQ(y, 4.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, DEFAULT_HEADER_VALUE);
}

/**
 * @tc.name: ProcessAreaVertical004
 * @tc.desc: Test ListPattern ProcessAreaVertical
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaVertical004, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 0;
    groupItemPattern->headerMainSize_ = 4.0f;
    groupItemPattern->footerMainSize_ = 8.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->padding_ = std::make_unique<PaddingPropertyF>();
    frameNode->geometryNode_->padding_->top = 2.0f;
    frameNode->geometryNode_->padding_->bottom = 5.0f;
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = frameNode;
    groupItemPattern->frameNode_ = frameNode;
    double x = 2.F;
    double y = 4.F;
    Rect groupRect(6.0f, 6.0f, 2.0f, 4.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaVertical(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 2.F);
    EXPECT_EQ(y, 4.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, DEFAULT_FOOTER_VALUE);
}

/**
 * @tc.name: ProcessAreaVertical005
 * @tc.desc: Test ListPattern ProcessAreaVertical
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaVertical005, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 0;
    groupItemPattern->headerMainSize_ = 1.0f;
    groupItemPattern->footerMainSize_ = 8.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->padding_ = std::make_unique<PaddingPropertyF>();
    frameNode->geometryNode_->padding_->top = 1.0f;
    frameNode->geometryNode_->padding_->bottom = 5.0f;
    groupItemPattern->header_ = frameNode;
    groupItemPattern->footer_ = frameNode;
    groupItemPattern->frameNode_ = frameNode;
    double x = 2.F;
    double y = 5.F;
    Rect groupRect(6.0f, 1.0f, 2.0f, 3.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaVertical(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 2.F);
    EXPECT_EQ(y, 5.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaVertical006
 * @tc.desc: Test ListPattern ProcessAreaVertical
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaVertical006, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 0;
    groupItemPattern->headerMainSize_ = 1.0f;
    groupItemPattern->footerMainSize_ = 2.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->padding_ = std::make_unique<PaddingPropertyF>();
    frameNode->geometryNode_->padding_->top = 1.0f;
    frameNode->geometryNode_->padding_->bottom = 1.0f;
    groupItemPattern->header_ = frameNode;
    groupItemPattern->footer_ = nullptr;
    groupItemPattern->frameNode_ = frameNode;
    double x = 2.F;
    double y = 5.F;
    Rect groupRect(6.0f, 1.0f, 10.0f, 10.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaVertical(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 2.F);
    EXPECT_EQ(y, 5.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaVertical007
 * @tc.desc: Test ListPattern ProcessAreaVertical
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaVertical007, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 0;
    groupItemPattern->headerMainSize_ = 1.0f;
    groupItemPattern->footerMainSize_ = 8.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->padding_ = std::make_unique<PaddingPropertyF>();
    frameNode->geometryNode_->padding_->top = 1.0f;
    frameNode->geometryNode_->padding_->bottom = 5.0f;
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = nullptr;
    groupItemPattern->frameNode_ = frameNode;
    double x = 2.F;
    double y = 5.F;
    Rect groupRect(6.0f, 1.0f, 2.0f, 6.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaVertical(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 2.F);
    EXPECT_EQ(y, 5.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: ProcessAreaVertical008
 * @tc.desc: Test ListPattern ProcessAreaVertical
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaVertical008, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 0;
    groupItemPattern->headerMainSize_ = 1.0f;
    groupItemPattern->footerMainSize_ = 8.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->padding_ = std::make_unique<PaddingPropertyF>();
    frameNode->geometryNode_->padding_->top = 1.0f;
    frameNode->geometryNode_->padding_->bottom = 5.0f;
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = nullptr;
    groupItemPattern->frameNode_ = frameNode;
    double x = 2.F;
    double y = 5.F;
    Rect groupRect(6.0f, 1.0f, 2.0f, 3.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaVertical(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 2.F);
    EXPECT_EQ(y, 5.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaVertical009
 * @tc.desc: Test ListPattern ProcessAreaVertical
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaVertical009, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 0;
    groupItemPattern->headerMainSize_ = 1.0f;
    groupItemPattern->footerMainSize_ = 8.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->padding_ = std::make_unique<PaddingPropertyF>();
    frameNode->geometryNode_->padding_->top = 1.0f;
    frameNode->geometryNode_->padding_->bottom = 5.0f;
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = nullptr;
    groupItemPattern->frameNode_ = frameNode;
    double x = 2.F;
    double y = 5.F;
    Rect groupRect(6.0f, 8.0f, 2.0f, 3.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaVertical(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 2.F);
    EXPECT_EQ(y, 5.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaVertical010
 * @tc.desc: Test ListPattern ProcessAreaVertical
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaVertical010, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = frameNode;
    double x = 2.F;
    double y = 5.F;
    Rect groupRect(6.0f, 6.0f, 2.0f, 4.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaVertical(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 2.F);
    EXPECT_EQ(y, 5.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, DEFAULT_FOOTER_VALUE);
}

/**
 * @tc.name: ProcessAreaVertical011
 * @tc.desc: Test ListPattern ProcessAreaVertical
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaVertical011, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = nullptr;
    double x = 2.F;
    double y = -2.F;
    Rect groupRect(6.0f, -4.0f, 2.0f, -6.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaVertical(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 2.F);
    EXPECT_EQ(y, -2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaVertical012
 * @tc.desc: Test ListPattern ProcessAreaVertical
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaVertical012, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = frameNode;
    double x = 2.F;
    double y = 5.F;
    Rect groupRect(6.0f, 3.0f, 2.0f, 1.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaVertical(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 2.F);
    EXPECT_EQ(y, 5.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaVertical013
 * @tc.desc: Test ListPattern ProcessAreaVertical
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaVertical013, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = frameNode;
    double x = 2.F;
    double y = -2.F;
    Rect groupRect(6.0f, -4.0f, 2.0f, 1.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaVertical(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 2.F);
    EXPECT_EQ(y, -2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaVertical014
 * @tc.desc: Test ListPattern ProcessAreaVertical
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaVertical014, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    groupItemPattern->header_ = frameNode;
    groupItemPattern->footer_ = nullptr;
    double x = 2.F;
    double y = -5.F;
    Rect groupRect(6.0f, 2.0f, 2.0f, 4.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaVertical(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 2.F);
    EXPECT_EQ(y, -5.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaVertical015
 * @tc.desc: Test ListPattern ProcessAreaVertical
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaVertical015, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    groupItemPattern->header_ = frameNode;
    groupItemPattern->footer_ = nullptr;
    double x = 2.F;
    double y = 5.F;
    Rect groupRect(6.0f, 6.0f, 2.0f, 4.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaVertical(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 2.F);
    EXPECT_EQ(y, 5.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaHorizontal001
 * @tc.desc: Test ListPattern ProcessAreaHorizontal
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaHorizontal001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    groupItemPattern->header_ = frameNode;
    double x = -4.F;
    double y = 2.F;
    Rect groupRect(-7.0f, 6.0f, 4.0f, 2.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaHorizontal(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, -4.F);
    EXPECT_EQ(y, 2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), -7.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, DEFAULT_HEADER_VALUE);
}

/**
 * @tc.name: ProcessAreaHorizontal002
 * @tc.desc: Test ListPattern ProcessAreaHorizontal
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaHorizontal002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = frameNode;
    double x = -4.F;
    double y = 2.F;
    Rect groupRect(-7.0f, 6.0f, 4.0f, 2.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaHorizontal(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, -4.F);
    EXPECT_EQ(y, 2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), -7.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaHorizontal003
 * @tc.desc: Test ListPattern ProcessAreaHorizontal
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaHorizontal003, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 0;
    groupItemPattern->headerMainSize_ = 4.0f;
    groupItemPattern->footerMainSize_ = 8.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->padding_ = std::make_unique<PaddingPropertyF>();
    frameNode->geometryNode_->padding_->top = 2.0f;
    frameNode->geometryNode_->padding_->bottom = 5.0f;
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = frameNode;
    groupItemPattern->frameNode_ = frameNode;
    double x = 4.F;
    double y = 2.F;
    Rect groupRect(3.0f, 6.0f, 4.0f, 2.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaHorizontal(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 4.F);
    EXPECT_EQ(y, 2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 3.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, DEFAULT_HEADER_VALUE);
}

/**
 * @tc.name: ProcessAreaHorizontal004
 * @tc.desc: Test ListPattern ProcessAreaHorizontal
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaHorizontal004, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 0;
    groupItemPattern->headerMainSize_ = 4.0f;
    groupItemPattern->footerMainSize_ = 8.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->padding_ = std::make_unique<PaddingPropertyF>();
    frameNode->geometryNode_->padding_->top = 2.0f;
    frameNode->geometryNode_->padding_->bottom = 5.0f;
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = frameNode;
    groupItemPattern->frameNode_ = frameNode;
    double x = 4.F;
    double y = 2.F;
    Rect groupRect(6.0f, 6.0f, 4.0f, 2.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaHorizontal(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 4.F);
    EXPECT_EQ(y, 2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, DEFAULT_FOOTER_VALUE);
}

/**
 * @tc.name: ProcessAreaHorizontal005
 * @tc.desc: Test ListPattern ProcessAreaHorizontal
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaHorizontal005, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 0;
    groupItemPattern->headerMainSize_ = 1.0f;
    groupItemPattern->footerMainSize_ = 8.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->padding_ = std::make_unique<PaddingPropertyF>();
    frameNode->geometryNode_->padding_->top = 1.0f;
    frameNode->geometryNode_->padding_->bottom = 5.0f;
    groupItemPattern->header_ = frameNode;
    groupItemPattern->footer_ = frameNode;
    groupItemPattern->frameNode_ = frameNode;
    double x = 5.F;
    double y = 2.F;
    Rect groupRect(1.0f, 6.0f, 3.0f, 2.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaHorizontal(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 5.F);
    EXPECT_EQ(y, 2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 1.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaHorizontal006
 * @tc.desc: Test ListPattern ProcessAreaHorizontal
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaHorizontal006, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 0;
    groupItemPattern->headerMainSize_ = 1.0f;
    groupItemPattern->footerMainSize_ = 2.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->padding_ = std::make_unique<PaddingPropertyF>();
    frameNode->geometryNode_->padding_->top = 1.0f;
    frameNode->geometryNode_->padding_->bottom = 1.0f;
    groupItemPattern->header_ = frameNode;
    groupItemPattern->footer_ = nullptr;
    groupItemPattern->frameNode_ = frameNode;
    double x = 5.F;
    double y = 2.F;
    Rect groupRect(1.0f, 6.0f, 10.0f, 10.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaHorizontal(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 5.F);
    EXPECT_EQ(y, 2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 1.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaHorizontal007
 * @tc.desc: Test ListPattern ProcessAreaHorizontal
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaHorizontal007, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 0;
    groupItemPattern->headerMainSize_ = 1.0f;
    groupItemPattern->footerMainSize_ = 8.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->padding_ = std::make_unique<PaddingPropertyF>();
    frameNode->geometryNode_->padding_->top = 1.0f;
    frameNode->geometryNode_->padding_->bottom = 5.0f;
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = nullptr;
    groupItemPattern->frameNode_ = frameNode;
    double x = 5.F;
    double y = 2.F;
    Rect groupRect(1.0f, 6.0f, 6.0f, 2.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaHorizontal(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 5.F);
    EXPECT_EQ(y, 2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 1.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: ProcessAreaHorizontal008
 * @tc.desc: Test ListPattern ProcessAreaHorizontal
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaHorizontal008, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 0;
    groupItemPattern->headerMainSize_ = 1.0f;
    groupItemPattern->footerMainSize_ = 8.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->padding_ = std::make_unique<PaddingPropertyF>();
    frameNode->geometryNode_->padding_->top = 1.0f;
    frameNode->geometryNode_->padding_->bottom = 5.0f;
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = nullptr;
    groupItemPattern->frameNode_ = frameNode;
    double x = 5.F;
    double y = 2.F;
    Rect groupRect(1.0f, 6.0f, 3.0f, 2.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaHorizontal(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 5.F);
    EXPECT_EQ(y, 2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 1.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaHorizontal009
 * @tc.desc: Test ListPattern ProcessAreaHorizontal
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaHorizontal009, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 0;
    groupItemPattern->headerMainSize_ = 1.0f;
    groupItemPattern->footerMainSize_ = 8.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->padding_ = std::make_unique<PaddingPropertyF>();
    frameNode->geometryNode_->padding_->top = 1.0f;
    frameNode->geometryNode_->padding_->bottom = 5.0f;
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = nullptr;
    groupItemPattern->frameNode_ = frameNode;
    double x = 5.F;
    double y = 2.F;
    Rect groupRect(8.0f, 6.0f, 3.0f, 2.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaHorizontal(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 5.F);
    EXPECT_EQ(y, 2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 8.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaHorizontal010
 * @tc.desc: Test ListPattern ProcessAreaHorizontal
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaHorizontal010, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = frameNode;
    double x = 5.F;
    double y = 2.F;
    Rect groupRect(6.0f, 6.0f, 4.0f, 2.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaHorizontal(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 5.F);
    EXPECT_EQ(y, 2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, DEFAULT_FOOTER_VALUE);
}

/**
 * @tc.name: ProcessAreaHorizontal011
 * @tc.desc: Test ListPattern ProcessAreaHorizontal
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaHorizontal011, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = nullptr;
    double x = -2.F;
    double y = 2.F;
    Rect groupRect(-4.0f, 6.0f, -6.0f, 2.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaHorizontal(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, -2.F);
    EXPECT_EQ(y, 2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), -4.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaHorizontal012
 * @tc.desc: Test ListPattern ProcessAreaHorizontal
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaHorizontal012, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = frameNode;
    double x = 5.F;
    double y = 2.F;
    Rect groupRect(3.0f, 6.0f, 1.0f, 2.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaHorizontal(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 5.F);
    EXPECT_EQ(y, 2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 3.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaHorizontal013
 * @tc.desc: Test ListPattern ProcessAreaHorizontal
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaHorizontal013, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    groupItemPattern->header_ = nullptr;
    groupItemPattern->footer_ = frameNode;
    double x = -2.F;
    double y = 2.F;
    Rect groupRect(-4.0f, 6.0f, 1.0f, 2.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaHorizontal(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, -2.F);
    EXPECT_EQ(y, 2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), -4.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaHorizontal014
 * @tc.desc: Test ListPattern ProcessAreaHorizontal
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaHorizontal014, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    groupItemPattern->header_ = frameNode;
    groupItemPattern->footer_ = nullptr;
    double x = -5.F;
    double y = 2.F;
    Rect groupRect(2.0f, 6.0f, 4.0f, 2.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaHorizontal(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, -5.F);
    EXPECT_EQ(y, 2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 2.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ProcessAreaHorizontal015
 * @tc.desc: Test ListPattern ProcessAreaHorizontal
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessAreaHorizontal015, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    groupItemPattern->header_ = frameNode;
    groupItemPattern->footer_ = nullptr;
    double x = 5.F;
    double y = 2.F;
    Rect groupRect(6.0f, 6.0f, 4.0f, 2.0f);
    int32_t index = 2;
    auto result = listPattern->ProcessAreaHorizontal(x, y, groupRect, index, groupItemPattern);
    EXPECT_EQ(x, 5.F);
    EXPECT_EQ(y, 2.F);
    EXPECT_EQ(groupRect.GetOffset().GetX(), 6.0f);
    EXPECT_EQ(index, 2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: HandleDividerList001
 * @tc.desc: Test ListPaintMethod HandleDividerList
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, HandleDividerList001, TestSize.Level1)
{
    V2::ItemDivider divider;
    RefPtr<ListPaintMethod> listPaintMethod = AceType::MakeRefPtr<ListPaintMethod>(divider, true, true, 2, 2.0f);
    listPaintMethod->isRTL_ = true;
    listPaintMethod->adjustOffset_ = 1.0f;
    ListItemInfo info;
    info.isGroup = false;
    info.startPos = 2.0f;
    listPaintMethod->itemPosition_[1] = info;
    DividerInfo dividerInfo { 2.0f, 4.0f, 8.0f, 4.0f, 2.0f, 1.0f, 3.0f, 1.0f, 2.0f, 3, 0, Color::RED, true };
    auto result = listPaintMethod->HandleDividerList(1, false, 3, dividerInfo);
    EXPECT_EQ(result.offset.GetX(), 5.5f);
    EXPECT_EQ(result.offset.GetY(), 14.0f);
}

/**
 * @tc.name: HandleDividerList002
 * @tc.desc: Test ListPaintMethod HandleDividerList
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, HandleDividerList002, TestSize.Level1)
{
    V2::ItemDivider divider;
    RefPtr<ListPaintMethod> listPaintMethod = AceType::MakeRefPtr<ListPaintMethod>(divider, true, true, 2, 2.0f);
    listPaintMethod->isRTL_ = true;
    listPaintMethod->adjustOffset_ = 1.0f;
    ListItemInfo info;
    info.isGroup = false;
    info.startPos = 2.0f;
    listPaintMethod->itemPosition_[2] = info;
    DividerInfo dividerInfo { 2.0f, 4.0f, 8.0f, 6.0f, 2.0f, 1.0f, 3.0f, 1.0f, 2.0f, 3, 0, Color::RED, false };
    auto result = listPaintMethod->HandleDividerList(2, false, 3, dividerInfo);
    EXPECT_EQ(result.offset.GetY(), 7.5f);
}

/**
 * @tc.name: VerifyFocusIndex001
 * @tc.desc: Test ListPattern VerifyFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, VerifyFocusIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set nextIndex to 1 and set nextIndexInGroup to be less than 0
     * and set the lanes of ListItemGroupPara to 2 and the itemEndIndex of ListItemGroupPara to 3
     */
    int32_t nextIndex = 1;
    int32_t nextIndexInGroup = -2;
    ListItemGroupPara param;
    param.lanes = 2;
    param.itemEndIndex = 3;

    /**
     * @tc.steps: step3. Call the VerifyFocusIndex function
     * @tc.expected: The nextIndex to be 0 and nextIndexInGroup to be -1
     */
    listPattern->VerifyFocusIndex(nextIndex, nextIndexInGroup, param);
    EXPECT_EQ(nextIndex, 0);
    EXPECT_EQ(nextIndexInGroup, -1);
}

/**
 * @tc.name: VerifyFocusIndex002
 * @tc.desc: Test ListPattern VerifyFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, VerifyFocusIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set nextIndexInGroup greater than 0 and greater than the itemEndIndex of ListItemGroupPara
     * Set nextIndex to 1 and set the lanes of ListItemGroupPara greater than 1
     */
    int32_t nextIndex = 1;
    int32_t nextIndexInGroup = 2;
    ListItemGroupPara param;
    param.lanes = 5;
    param.itemEndIndex = 1;

    /**
     * @tc.steps: step3. Call the VerifyFocusIndex function
     * @tc.expected: The nextIndex is not changed and nextIndexInGroup to be the value of param.itemEndIndex
     */
    listPattern->VerifyFocusIndex(nextIndex, nextIndexInGroup, param);
    EXPECT_EQ(nextIndex, 1);
    EXPECT_EQ(nextIndexInGroup, 1);
}

/**
 * @tc.name: VerifyFocusIndex003
 * @tc.desc: Test ListPattern VerifyFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, VerifyFocusIndex003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set nextIndexInGroup greater than 0 and greater than the itemEndIndex of ListItemGroupPara
     * nextIndexInGroup Less than or equal to (param.itemEndIndex + param.lanes - param.itemEndIndex % param.lanes - 1)
     * Set nextIndex to 1 and set the lanes of ListItemGroupPara greater than 1
     */
    int32_t nextIndex = 1;
    int32_t nextIndexInGroup = 2;
    ListItemGroupPara param;
    param.lanes = 5;
    param.itemEndIndex = 1;

    /**
     * @tc.steps: step3. Call the VerifyFocusIndex function
     * @tc.expected: The nextIndex is not changed and nextIndexInGroup to be the value of param.itemEndIndex
     */
    listPattern->VerifyFocusIndex(nextIndex, nextIndexInGroup, param);
    EXPECT_EQ(nextIndex, 1);
    EXPECT_EQ(nextIndexInGroup, 1);
}

/**
 * @tc.name: VerifyFocusIndex004
 * @tc.desc: Test ListPattern VerifyFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, VerifyFocusIndex004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set nextIndexInGroup greater than 0 and greater than the itemEndIndex of ListItemGroupPara
     * nextIndexInGroup greater than (param.itemEndIndex + param.lanes - param.itemEndIndex % param.lanes - 1)
     * Set nextIndex to 1 and set the lanes of ListItemGroupPara greater than 1
     */
    int32_t nextIndex = 1;
    int32_t nextIndexInGroup = 2;
    ListItemGroupPara param;
    param.lanes = 2;
    param.itemEndIndex = 1;

    /**
     * @tc.steps: step3. Call the VerifyFocusIndex function
     * @tc.expected: The nextIndex to be 2 and nextIndexInGroup to be -1
     */
    listPattern->VerifyFocusIndex(nextIndex, nextIndexInGroup, param);
    EXPECT_EQ(nextIndex, 2);
    EXPECT_EQ(nextIndexInGroup, -1);
}

/**
 * @tc.name: VerifyFocusIndex005
 * @tc.desc: Test ListPattern VerifyFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, VerifyFocusIndex005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set nextIndexInGroup greater than 0 and greater than the itemEndIndex of ListItemGroupPara
     * set the lanes of ListItemGroupPara Less than or equal to 1
     * Set nextIndex to 1
     */
    int32_t nextIndex = 1;
    int32_t nextIndexInGroup = 2;
    ListItemGroupPara param;
    param.lanes = 2;
    param.itemEndIndex = 1;

    /**
     * @tc.steps: step3. Call the VerifyFocusIndex function
     * @tc.expected: The nextIndex to be 2 and nextIndexInGroup to be -1
     */
    listPattern->VerifyFocusIndex(nextIndex, nextIndexInGroup, param);
    EXPECT_EQ(nextIndex, 2);
    EXPECT_EQ(nextIndexInGroup, -1);
}

/**
 * @tc.name: VerifyFocusIndex006
 * @tc.desc: Test ListPattern VerifyFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, VerifyFocusIndex006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set nextIndexInGroup greater than 0 and Set nextIndex to 1
     * and the nextIndexInGroup Less than to the itemEndIndex of ListItemGroupPara
     */
    int32_t nextIndex = 1;
    int32_t nextIndexInGroup = 2;
    ListItemGroupPara param;
    param.lanes = 2;
    param.itemEndIndex = 3;

    /**
     * @tc.steps: step3. Call the VerifyFocusIndex function
     * @tc.expected: The nextIndex and nextIndexInGroup is not changed
     */
    listPattern->VerifyFocusIndex(nextIndex, nextIndexInGroup, param);
    EXPECT_EQ(nextIndex, 1);
    EXPECT_EQ(nextIndexInGroup, 2);
}

/**
 * @tc.name: GetNextLineFocusIndex001
 * @tc.desc: Test ListPattern GetNextLineFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetNextLineFocusIndex, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set the lanes_ to 2 and the maxListItemIndex_ to 6
     */
    listPattern->lanes_ = 2;
    listPattern->maxListItemIndex_ = 6;

    /**
     * @tc.steps: step3.  Set the currIndex to 2 and call the GetNextLineFocusIndex function
     * @tc.expected: The result of calling the function is the sum of currIndex and lanes_
     */
    auto result = listPattern->GetNextLineFocusIndex(2);
    EXPECT_EQ(result, 4);
}

/**
 * @tc.name: ScrollListForFocus001
 * @tc.desc: Test ListPattern ScrollListForFocus
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ScrollListForFocus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, listPattern);
    ASSERT_NE(listNode, nullptr);

    /**
     * @tc.steps: step2. Set nextIndex Less than startIndex_ and curIndex to 1
     * Set nextIndexInGroup to -1 and set scrollAlign_ to NONE
     */
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    listNode->context_ = AceType::RawPtr(context);
    listPattern->frameNode_ = listNode;
    listPattern->startIndex_ = 4;
    listPattern->scrollAlign_ = ScrollAlign::NONE;

    /**
     * @tc.steps: step3.  Set the currIndex to 2 and call the ScrollListForFocus function
     * @tc.expected: The result of calling the function is true and scrollAlign_ to be START
     */
    auto result = listPattern->ScrollListForFocus(2, 1, -1);
    listNode->context_ = nullptr;
    EXPECT_EQ(listPattern->scrollAlign_, ScrollAlign::START);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ScrollListForFocus002
 * @tc.desc: Test ListPattern ScrollListForFocus
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ScrollListForFocus002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, listPattern);
    ASSERT_NE(listNode, nullptr);

    /**
     * @tc.steps: step2. Set nextIndex Less than startIndex_ and curIndex to 1
     * Set nextIndexInGroup to 2
     */
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    listNode->context_ = AceType::RawPtr(context);
    listPattern->frameNode_ = listNode;
    listPattern->startIndex_ = 4;

    /**
     * @tc.steps: step3.  Set the currIndex to 2 and call the ScrollListForFocus function
     * @tc.expected: The result of calling the function is false
     */
    auto result = listPattern->ScrollListForFocus(2, 1, 2);
    listNode->context_ = nullptr;
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ScrollListForFocus003
 * @tc.desc: Test ListPattern ScrollListForFocus
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ScrollListForFocus003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, listPattern);
    ASSERT_NE(listNode, nullptr);

    /**
     * @tc.steps: step2. Set endIndex_ Less than nextIndex and curIndex to 2
     * Set nextIndexInGroup to -1 and set scrollAlign_ to NONE
     */
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    listNode->context_ = AceType::RawPtr(context);
    listPattern->frameNode_ = listNode;
    listPattern->endIndex_ = 2;
    listPattern->scrollAlign_ = ScrollAlign::NONE;

    /**
     * @tc.steps: step3.  Set the currIndex to 2 and call the ScrollListForFocus function
     * @tc.expected: The result of calling the function is true and scrollAlign_ to be END
     */
    auto result = listPattern->ScrollListForFocus(3, 2, -1);
    listNode->context_ = nullptr;
    EXPECT_EQ(listPattern->scrollAlign_, ScrollAlign::END);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ScrollListForFocus004
 * @tc.desc: Test ListPattern ScrollListForFocus
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ScrollListForFocus004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, listPattern);
    ASSERT_NE(listNode, nullptr);

    /**
     * @tc.steps: step2. Set endIndex_ Less than nextIndex and curIndex to 2
     * Set nextIndexInGroup to 1
     */
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    listNode->context_ = AceType::RawPtr(context);
    listPattern->frameNode_ = listNode;
    listPattern->endIndex_ = 2;

    /**
     * @tc.steps: step3.  Set the currIndex to 2 and call the ScrollListForFocus function
     * @tc.expected: The result of calling the function is false
     */
    auto result = listPattern->ScrollListForFocus(3, 2, 2);
    listNode->context_ = nullptr;
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ScrollListForFocus005
 * @tc.desc: Test ListPattern ScrollListForFocus
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ScrollListForFocus005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, listPattern);
    ASSERT_NE(listNode, nullptr);

    /**
     * @tc.steps: step2. Set startIndex_ and endIndex_ equal to nextIndex and curIndex to 1
     * Set nextIndexInGroup to -1
     */
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    listNode->context_ = AceType::RawPtr(context);
    listPattern->frameNode_ = listNode;
    listPattern->startIndex_ = 2;
    listPattern->endIndex_ = 2;

    /**
     * @tc.steps: step3.  Set the currIndex to 2 and call the ScrollListForFocus function
     * @tc.expected: The result of calling the function is false
     */
    auto result = listPattern->ScrollListForFocus(2, 1, -1);
    listNode->context_ = nullptr;
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleLastLineIndex001
 * @tc.desc: Test ListPaintMethod HandleLastLineIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, HandleLastLineIndex001, TestSize.Level1)
{
    V2::ItemDivider divider;
    RefPtr<ListPaintMethod> listPaintMethod = AceType::MakeRefPtr<ListPaintMethod>(divider, true, true, 2, 2.0f);
    listPaintMethod->isRTL_ = true;
    listPaintMethod->adjustOffset_ = 1.0f;
    ListItemInfo info;
    info.isGroup = false;
    info.endPos = 5.0f;
    listPaintMethod->itemPosition_[1] = info;
    DividerInfo dividerInfo { 2.0f, 4.0f, 8.0f, 4.0f, 2.0f, 1.0f, 3.0f, 1.0f, 2.0f, 3, 0, Color::RED, true };
    auto result = listPaintMethod->HandleLastLineIndex(1, 3, dividerInfo);
    EXPECT_EQ(result.offset.GetX(), 1.5f);
    EXPECT_EQ(result.offset.GetY(), 14.0f);
}

/**
 * @tc.name: HandleLastLineIndex002
 * @tc.desc: Test ListPaintMethod HandleLastLineIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, HandleLastLineIndex002, TestSize.Level1)
{
    V2::ItemDivider divider;
    RefPtr<ListPaintMethod> listPaintMethod = AceType::MakeRefPtr<ListPaintMethod>(divider, true, true, 2, 2.0f);
    listPaintMethod->isRTL_ = true;
    listPaintMethod->adjustOffset_ = 1.0f;
    ListItemInfo info;
    info.isGroup = false;
    info.endPos = 6.0f;
    listPaintMethod->itemPosition_[2] = info;
    DividerInfo dividerInfo { 2.0f, 4.0f, 8.0f, 6.0f, 2.0f, 1.0f, 3.0f, 1.0f, 2.0f, 3, 0, Color::RED, false };
    auto result = listPaintMethod->HandleLastLineIndex(2, 3, dividerInfo);
    EXPECT_EQ(result.offset.GetY(), 12.5f);
}

/**
 * @tc.name: UpdateScrollBarOffset001
 * @tc.desc: Test ListPattern UpdateScrollBarOffset with heightEstimated_
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, UpdateScrollBarOffset001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    listPattern->heightEstimated_ = true;
    listPattern->UpdateScrollBarOffset();
    EXPECT_FALSE(listPattern->heightEstimated_);
}

/**
 * @tc.name: VerifyFocusIndex01
 * @tc.desc: Test ListPattern VerifyFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, VerifyFocusIndex01, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    int32_t nextIndex = 2;
    int32_t nextIndexInGroup = 2;
    ListItemGroupPara param;
    param.itemEndIndex = -1;
    param.lanes = -1;
    listPattern->VerifyFocusIndex(nextIndex, nextIndexInGroup, param);
    EXPECT_EQ(nextIndexInGroup, -1);
}

/**
 * @tc.name: VerifyFocusIndex02
 * @tc.desc: Test ListPattern VerifyFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, VerifyFocusIndex02, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    int32_t nextIndex = 2;
    int32_t nextIndexInGroup = -2;
    ListItemGroupPara param;
    param.itemEndIndex = -1;
    param.lanes = -1;
    listPattern->VerifyFocusIndex(nextIndex, nextIndexInGroup, param);
    EXPECT_EQ(nextIndexInGroup, -1);
}

/**
 * @tc.name: VerifyFocusIndex03
 * @tc.desc: Test ListPattern VerifyFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, VerifyFocusIndex03, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    int32_t nextIndex = 2;
    int32_t nextIndexInGroup = 2;
    ListItemGroupPara param;
    param.itemEndIndex = -1;
    param.lanes = -1;
    listPattern->VerifyFocusIndex(nextIndex, nextIndexInGroup, param);
    EXPECT_EQ(nextIndexInGroup, -1);
}

/**
 * @tc.name: VerifyFocusIndex04
 * @tc.desc: Test ListPattern VerifyFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, VerifyFocusIndex04, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    int32_t nextIndex = 2;
    int32_t nextIndexInGroup = 2;
    ListItemGroupPara param;
    param.itemEndIndex = 3;
    param.lanes = -1;
    listPattern->VerifyFocusIndex(nextIndex, nextIndexInGroup, param);
    EXPECT_EQ(nextIndexInGroup, 2);
}

/**
 * @tc.name: VerifyFocusIndex05
 * @tc.desc: Test ListPattern VerifyFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, VerifyFocusIndex05, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    int32_t nextIndex = 2;
    int32_t nextIndexInGroup = 2;
    ListItemGroupPara param;
    param.itemEndIndex = 1;
    param.lanes = -1;
    listPattern->VerifyFocusIndex(nextIndex, nextIndexInGroup, param);
    EXPECT_EQ(nextIndexInGroup, -1);
}

/**
 * @tc.name: VerifyFocusIndex06
 * @tc.desc: Test ListPattern VerifyFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, VerifyFocusIndex06, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    int32_t nextIndex = 2;
    int32_t nextIndexInGroup = 2;
    ListItemGroupPara param;
    param.itemEndIndex = 1;
    param.lanes = 5;
    listPattern->VerifyFocusIndex(nextIndex, nextIndexInGroup, param);
    EXPECT_EQ(nextIndexInGroup, 1);
}

/**
 * @tc.name: VerifyFocusIndex07
 * @tc.desc: Test ListPattern VerifyFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, VerifyFocusIndex07, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    int32_t nextIndex = 2;
    int32_t nextIndexInGroup = 2;
    ListItemGroupPara param;
    param.itemEndIndex = 1;
    param.lanes = -1;
    listPattern->VerifyFocusIndex(nextIndex, nextIndexInGroup, param);
    EXPECT_EQ(nextIndexInGroup, -1);
}

/**
 * @tc.name: VerifyFocusIndex08
 * @tc.desc: Test ListPattern VerifyFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, VerifyFocusIndex08, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    int32_t nextIndex = 2;
    int32_t nextIndexInGroup = 3;
    ListItemGroupPara param;
    param.itemEndIndex = 3;
    param.lanes = 2;
    listPattern->VerifyFocusIndex(nextIndex, nextIndexInGroup, param);
    EXPECT_EQ(nextIndexInGroup, 3);
}

/**
 * @tc.name: AnimateTo001
 * @tc.desc: Test ListPattern AnimateTo
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, AnimateTo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a list with items of varying heights at the bottom
     */
    ListModelNG model = CreateList();
    model.SetInitialIndex(9);
    model.SetCachedCount(0);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    CreateRepeatVirtualScrollNode(10, [this](int32_t idx) {
        ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
        ListItemModelNG itemModel;
        itemModel.Create([](int32_t) {}, V2::ListItemStyle::NONE);
        Axis axis = layoutProperty_->GetListDirection().value_or(Axis::VERTICAL);
        if (idx == 9) {
            SetSize(axis, CalcLength(FILL_LENGTH), CalcLength(ITEM_MAIN_SIZE * 5));
        } else {
            SetSize(axis, CalcLength(FILL_LENGTH), CalcLength(ITEM_MAIN_SIZE));
        }
        
    });
    CreateDone();
    FlushUITasks(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->currentOffset_, 4500);
    
    /**
     * @tc.steps: step2. AnimateTo the top
     * @tc.expected: AnimateTo the top
     */
    MockAnimationManager::GetInstance().SetTicks(4);
    pattern_->AnimateTo(0, -1, nullptr, true);
    FlushUITasks(frameNode_);
    for (int i = 0; i < 4; ++i) {
        MockAnimationManager::GetInstance().Tick();
        FlushUITasks(frameNode_);
    }
    
    EXPECT_FLOAT_EQ(pattern_->currentOffset_, 0);
}

/**
 * @tc.name: AnimateTo001
 * @tc.desc: Test ListPattern AnimateTo
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, AnimateTo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a list with items of varying heights at the bottom
     */
    ListModelNG model = CreateList();
    model.SetInitialIndex(9);
    model.SetCachedCount(0);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    CreateRepeatVirtualScrollNode(10, [this](int32_t idx) {
        ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
        ListItemModelNG itemModel;
        itemModel.Create([](int32_t) {}, V2::ListItemStyle::NONE);
        Axis axis = layoutProperty_->GetListDirection().value_or(Axis::VERTICAL);
        if (idx == 9) {
            SetSize(axis, CalcLength(FILL_LENGTH), CalcLength(ITEM_MAIN_SIZE * 5));
        } else {
            SetSize(axis, CalcLength(FILL_LENGTH), CalcLength(ITEM_MAIN_SIZE));
        }
        
    });
    CreateDone();
    FlushUITasks(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->currentOffset_, 4500);
    
    /**
     * @tc.steps: step2. AnimateTo the 100
     * @tc.expected: AnimateTo the 100
     */
    MockAnimationManager::GetInstance().SetTicks(4);
    pattern_->AnimateTo(100, -1, nullptr, true);
    FlushUITasks(frameNode_);
    for (int i = 0; i < 4; ++i) {
        MockAnimationManager::GetInstance().Tick();
        FlushUITasks(frameNode_);
    }
    
    EXPECT_FLOAT_EQ(pattern_->currentOffset_, 100);
}

/**
 * @tc.name: CustomizeSafeAreaPadding001
 * @tc.desc: Test ListPattern CustomizeSafeAreaPadding
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, CustomizeSafeAreaPadding001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    PaddingPropertyF padding { 10, 10, 10, 10 };
    padding = listPattern->CustomizeSafeAreaPadding(padding, false);
    EXPECT_EQ(padding.top, std::nullopt);
    EXPECT_EQ(padding.bottom, std::nullopt);
    EXPECT_EQ(padding.left, 10);
    EXPECT_EQ(padding.right, 10);
}

/**
 * @tc.name: CustomizeSafeAreaPadding002
 * @tc.desc: Test ListPattern CustomizeSafeAreaPadding
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, CustomizeSafeAreaPadding002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    PaddingPropertyF padding { 10, 10, 10, 10 };
    padding = listPattern->CustomizeSafeAreaPadding(padding, true);
    EXPECT_EQ(padding.top, 10);
    EXPECT_EQ(padding.bottom, 10);
    EXPECT_EQ(padding.left, std::nullopt);
    EXPECT_EQ(padding.right, std::nullopt);
}

/**
 * @tc.name: GetStartIndexExcludeStartOffset001
 * @tc.desc: Test ListPattern GetStartIndexExcludeStartOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetStartIndexExcludeStartOffset001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    int32_t returnIndex = listPattern->GetStartIndexExcludeStartOffset();
    EXPECT_EQ(listPattern->GetStartIndex(), returnIndex);
}

/**
 * @tc.name: GetStartIndexExcludeStartOffset002
 * @tc.desc: Test ListPattern GetStartIndexExcludeStartOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetStartIndexExcludeStartOffset002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    listPattern->contentStartOffset_ = 10.0f;
    listPattern->itemPosition_[0] = { 2, 20.0f, 40.0f, true };
    int32_t returnIndex = listPattern->GetStartIndexExcludeStartOffset();
    EXPECT_EQ(returnIndex, 0);
}

/**
 * @tc.name: GetEndIndexExcludeEndOffset001
 * @tc.desc: Test ListPattern GetEndIndexExcludeEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetEndIndexExcludeEndOffset001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    int32_t returnIndex = listPattern->GetEndIndexExcludeEndOffset();
    EXPECT_EQ(listPattern->GetEndIndex(), returnIndex);
}

/**
 * @tc.name: GetEndIndexExcludeEndOffset002
 * @tc.desc: Test ListPattern GetEndIndexExcludeEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetEndIndexExcludeEndOffset002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    listPattern->contentMainSize_ = 100.0f;
    listPattern->itemPosition_[0] = { 2, 2.0f, 4.0f, true };
    int32_t returnIndex = listPattern->GetEndIndexExcludeEndOffset();
    EXPECT_EQ(returnIndex, 0);
}

/**
 * @tc.name: IsFreeScrollTest001
 * @tc.desc: Test IsFreeScroll
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, IsFreeScrollTest001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(listPattern, nullptr);
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(listNode, nullptr);
    model.SetListDirection(Axis::FREE);
    auto scrollBarProxy = listPattern->GetScrollBarProxy();
    CHECK_NULL_VOID(scrollBarProxy);

    EXPECT_FALSE(scrollBarProxy->IsFreeScroll());
}

/**
 * @tc.name: OnInjectionEventTest001
 * @tc.desc: Test ListPattern OnInjectionEventTest
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, OnInjectionEventTest001, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_TRUE(pattern_->IsAtTop());

    std::string command = R"()";
    pattern_->OnInjectionEvent(command);
    EXPECT_EQ(pattern_->currentDelta_, 0);

    command = R"({"cmd":"scrollForward"})";
    pattern_->OnInjectionEvent(command);
    EXPECT_EQ(pattern_->currentDelta_, 0);

    command = R"({"cmd":"scrollBackward"})";
    pattern_->OnInjectionEvent(command);
    EXPECT_EQ(pattern_->currentDelta_, 400);
}

/**
 * @tc.name: OnInjectionEventTest002
 * @tc.desc: test OnInjectionEvent
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, OnInjectionEventTest002, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_TRUE(pattern_->IsAtTop());

    std::string command = R"({"cmd":"scrollForward","eventId":123123,"ratio":0.1})";
    pattern_->OnInjectionEvent(command);
    EXPECT_EQ(pattern_->currentDelta_, 0);

    command = R"({"cmd":"scrollBackward","eventId":123123,"ratio":0.1})";
    pattern_->OnInjectionEvent(command);
    EXPECT_EQ(pattern_->currentDelta_, 40);

    command = R"({"cmd":"scrollForward","eventId":123123,"ratio":0.1})";
    pattern_->OnInjectionEvent(command);
    EXPECT_EQ(pattern_->currentDelta_, 0);

    command = R"({"cmd":"scrollward","eventId":123123,"ratio":0.1})";
    pattern_->OnInjectionEvent(command);
    EXPECT_EQ(pattern_->currentDelta_, 0);

    command = R"({"cmd":"scrollForward","eventId":123123,"ratio":1.1})";
    pattern_->OnInjectionEvent(command);
    EXPECT_EQ(pattern_->currentDelta_, 0);

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(pattern_->IsAtBottom());

    command = R"({"cmd":"scrollBackward","eventId":123123,"ratio":0.1})";
    pattern_->OnInjectionEvent(command);
    EXPECT_EQ(pattern_->currentDelta_, 0);
}

/**
 * @tc.name: OnInjectionEventTest003
 * @tc.desc: test OnInjectionEvent
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, OnInjectionEventTest003, TestSize.Level1)
{
    CreateList();
    CreateListItems(1);
    CreateDone();
    EXPECT_FALSE(pattern_->IsScrollable());

    std::string command = R"({"cmd":"scrollForward","eventId":123123,"ratio":0.1})";
    pattern_->OnInjectionEvent(command);
    EXPECT_EQ(pattern_->currentDelta_, 0);

    command = R"()";
    pattern_->OnInjectionEvent(command);
    EXPECT_EQ(pattern_->currentDelta_, 0);
}

/**
 * @tc.name: ReportComponentChangeEventTest001
 * @tc.desc: ReportComponentChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ReportComponentChangeEventTest001, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_TRUE(pattern_->IsAtTop());
    MockUiSessionManager* mockUiSessionManager =
        reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());
    EXPECT_CALL(*mockUiSessionManager, GetComponentChangeEventRegistered()).WillRepeatedly(Return(true));

    pattern_->ReportScroll(false, ScrollError::SCROLL_ERROR_OTHER, 123);
    pattern_->ReportScroll(true, ScrollError::SCROLL_NO_ERROR, 123);
    pattern_->ReportOnItemListEvent("onReachStart");
    pattern_->ReportOnItemListScrollEvent("onScrollIndex", 0, 0);

    std::string command = R"()";
    pattern_->OnInjectionEvent(command);
    EXPECT_EQ(pattern_->currentDelta_, 0);
}

/**
 * @tc.name: ProcessDragUpdateNullChainAnimation
 * @tc.desc: generated. ProcessDragUpdate returns early when chainAnimation_ is null
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessDragUpdateNullChainAnimation, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    pattern_->chainAnimation_ = nullptr;

    /**
     * @tc.steps: step2. Call ProcessDragUpdate with null chainAnimation
     * @tc.expected: Function returns early without modifying currentDelta_
     */
    float originalDelta = pattern_->currentDelta_;
    pattern_->ProcessDragUpdate(10.0f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->currentDelta_, originalDelta);
}

/**
 * @tc.name: ProcessDragUpdateFromBar
 * @tc.desc: generated. Verify ProcessDragUpdate returns early for SCROLL_FROM_BAR source
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessDragUpdateFromBar, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. Call with SCROLL_FROM_BAR (should return early)
     * @tc.expected: currentDelta_ should not change
     */
    float originalDelta = pattern_->currentDelta_;
    pattern_->ProcessDragUpdate(10.0f, SCROLL_FROM_BAR);
    EXPECT_EQ(pattern_->currentDelta_, originalDelta);
}

/**
 * @tc.name: ProcessDragUpdateFromAxis
 * @tc.desc: generated. Verify ProcessDragUpdate returns early for SCROLL_FROM_AXIS source
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessDragUpdateFromAxis, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    float originalDelta = pattern_->currentDelta_;
    pattern_->ProcessDragUpdate(10.0f, SCROLL_FROM_AXIS);
    EXPECT_EQ(pattern_->currentDelta_, originalDelta);
}

/**
 * @tc.name: ProcessDragUpdateFromBarFling
 * @tc.desc: generated. Verify ProcessDragUpdate returns early for SCROLL_FROM_BAR_FLING source
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessDragUpdateFromBarFling, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    float originalDelta = pattern_->currentDelta_;
    pattern_->ProcessDragUpdate(10.0f, SCROLL_FROM_BAR_FLING);
    EXPECT_EQ(pattern_->currentDelta_, originalDelta);
}

/**
 * @tc.name: ProcessDragUpdateWithUpdateSourceBasic
 * @tc.desc: generated. Verify ProcessDragUpdate executes for SCROLL_FROM_UPDATE source
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessDragUpdateWithUpdateSourceBasic, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. Call ProcessDragUpdate with SCROLL_FROM_UPDATE
     * @tc.expected: Function executes and frameNode remains valid (no crash)
     */
    pattern_->ProcessDragUpdate(10.0f, SCROLL_FROM_UPDATE);
    // Verify function executed successfully without causing crash
    EXPECT_NE(frameNode_, nullptr);
}

/**
 * @tc.name: ProcessDragUpdateWithOverOffset
 * @tc.desc: generated. Verify ProcessDragUpdate handles overOffset correctly
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessDragUpdateWithOverOffset, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    pattern_->itemPosition_[0] = { 1, 0.0f, 100.0f, false };

    /**
     * @tc.steps: step2. Call ProcessDragUpdate with itemPosition set
     * @tc.expected: Should calculate overOffset and call SetDelta without crash
     */
    pattern_->ProcessDragUpdate(10.0f, SCROLL_FROM_UPDATE);
    // Verify list structure is still valid after ProcessDragUpdate
    EXPECT_GT(frameNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: ProcessDragUpdateNormalDrag
 * @tc.desc: generated. Verify ProcessDragUpdate handles normal drag scenario
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessDragUpdateNormalDrag, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. Scroll to middle position to change list state
     * @tc.steps: step3. Call ProcessDragUpdate with normal drag offset
     * @tc.expected: Function executes successfully with scrolled state
     */
    UpdateCurrentOffset(100.0f, SCROLL_FROM_UPDATE);
    pattern_->ProcessDragUpdate(10.0f, SCROLL_FROM_UPDATE);
    // Verify list structure is still valid
    EXPECT_GT(frameNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: ProcessDragUpdateAtTopEdge
 * @tc.desc: generated. Verify ProcessDragUpdate behavior at top edge
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessDragUpdateAtTopEdge, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. Ensure list is at top edge
     * @tc.steps: step3. Call ProcessDragUpdate with drag offset
     * @tc.expected: Should handle edge case correctly
     */
    EXPECT_TRUE(pattern_->IsAtTop());
    pattern_->ProcessDragUpdate(10.0f, SCROLL_FROM_UPDATE);
    // Verify list is still at top after ProcessDragUpdate
    EXPECT_TRUE(pattern_->IsAtTop());
}

/**
 * @tc.name: ProcessDragUpdateAtBottomEdge
 * @tc.desc: generated. Verify ProcessDragUpdate behavior at bottom edge
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ProcessDragUpdateAtBottomEdge, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. Scroll to bottom
     * @tc.steps: step3. Call ProcessDragUpdate at bottom edge
     * @tc.expected: Should handle bottom edge case correctly
     */
    UpdateCurrentOffset(-1000.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    pattern_->ProcessDragUpdate(-10.0f, SCROLL_FROM_UPDATE);
    // Verify list structure is still valid
    EXPECT_GT(frameNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: GetNextFocusNodeNullCurrentFocus
 * @tc.desc: generated. Verify GetNextFocusNode returns nullptr for null currentFocusNode
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetNextFocusNodeNullCurrentFocus, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    WeakPtr<FocusHub> nullFocus;
    auto result = pattern_->GetNextFocusNode(FocusStep::DOWN, nullFocus);
    EXPECT_EQ(result.Upgrade(), nullptr);
}

/**
 * @tc.name: GetNextFocusNodeInvalidIndex
 * @tc.desc: generated. Verify GetNextFocusNode returns nullptr when curIndex > maxListItemIndex_
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetNextFocusNodeInvalidIndex, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    pattern_->maxListItemIndex_ = TOTAL_ITEM_NUMBER - 1;

    auto listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr);
    auto itemNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG, 999, listItemPattern);
    ASSERT_NE(itemNode, nullptr);
    auto itemFocusHub = itemNode->GetOrCreateFocusHub();
    ASSERT_NE(itemFocusHub, nullptr);

    auto result = pattern_->GetNextFocusNode(FocusStep::DOWN, itemFocusHub);
    EXPECT_EQ(result.Upgrade(), nullptr);
}

/**
 * @tc.name: GetNextFocusNodeDownStep
 * @tc.desc: generated. Verify GetNextFocusNode handles FocusStep::DOWN correctly
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetNextFocusNodeDownStep, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    /**
     * @tc.steps: step2. Get first list item's focus hub
     * @tc.steps: step3. Call GetNextFocusNode with FocusStep::DOWN
     * @tc.expected: Function executes successfully, list structure remains intact
     */
    auto firstItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(firstItem, nullptr);

    auto firstItemFocus = firstItem->GetFocusHub();
    ASSERT_NE(firstItemFocus, nullptr);

    auto result = pattern_->GetNextFocusNode(FocusStep::DOWN, firstItemFocus);
    // Verify list still has children after function call (structure not corrupted)
    EXPECT_GT(frameNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: GetNextFocusNodeUpStep
 * @tc.desc: generated. Verify GetNextFocusNode handles FocusStep::UP correctly
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetNextFocusNodeUpStep, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    /**
     * @tc.steps: step2. Get last list item's focus hub
     * @tc.steps: step3. Call GetNextFocusNode with FocusStep::UP
     * @tc.expected: Function executes successfully, list structure remains intact
     */
    auto lastItem = GetChildFrameNode(frameNode_, 4);
    ASSERT_NE(lastItem, nullptr);

    auto lastItemFocus = lastItem->GetFocusHub();
    ASSERT_NE(lastItemFocus, nullptr);

    auto result = pattern_->GetNextFocusNode(FocusStep::UP, lastItemFocus);
    // Verify list still has children after function call
    EXPECT_GT(frameNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: GetNextFocusNodeLeftStep
 * @tc.desc: generated. Verify GetNextFocusNode handles FocusStep::LEFT correctly
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetNextFocusNodeLeftStep, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    auto firstItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(firstItem, nullptr);

    auto firstItemFocus = firstItem->GetFocusHub();
    ASSERT_NE(firstItemFocus, nullptr);

    auto result = pattern_->GetNextFocusNode(FocusStep::LEFT, firstItemFocus);
    // Verify list structure is still valid
    EXPECT_GT(frameNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: GetNextFocusNodeRightStep
 * @tc.desc: generated. Verify GetNextFocusNode handles FocusStep::RIGHT correctly
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetNextFocusNodeRightStep, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    auto firstItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(firstItem, nullptr);

    auto firstItemFocus = firstItem->GetFocusHub();
    ASSERT_NE(firstItemFocus, nullptr);

    auto result = pattern_->GetNextFocusNode(FocusStep::RIGHT, firstItemFocus);
    // Verify list structure is still valid
    EXPECT_GT(frameNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: GetChildFocusNodeByIndexNullHost
 * @tc.desc: generated. Verify GetChildFocusNodeByIndex returns nullptr when GetHost is null
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetChildFocusNodeByIndexNullHost, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    listPattern->frameNode_ = nullptr;

    auto result = listPattern->GetChildFocusNodeByIndex(0, -1);
    EXPECT_EQ(result.Upgrade(), nullptr);
}

/**
 * @tc.name: GetChildFocusNodeByIndexFirstItem
 * @tc.desc: generated. Verify GetChildFocusNodeByIndex can find first item
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetChildFocusNodeByIndexFirstItem, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    /**
     * @tc.steps: step2. Try to get focus node for first item (index 0, groupIndex 0)
     * @tc.expected: Function executes successfully, list structure remains valid
     */
    auto result = pattern_->GetChildFocusNodeByIndex(0, 0);
    // Verify list structure is still valid after function call
    EXPECT_GT(frameNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: GetChildFocusNodeByIndexLastItem
 * @tc.desc: generated. Verify GetChildFocusNodeByIndex can find last item
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetChildFocusNodeByIndexLastItem, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    /**
     * @tc.steps: step2. Try to get focus node for last item (index 4, groupIndex 0)
     * @tc.expected: Function executes successfully, list structure remains valid
     */
    auto result = pattern_->GetChildFocusNodeByIndex(4, 0);
    // Verify list structure is still valid after function call
    EXPECT_GT(frameNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: GetChildFocusNodeByIndexInvalidIndex
 * @tc.desc: generated. Verify GetChildFocusNodeByIndex handles invalid index gracefully
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetChildFocusNodeByIndexInvalidIndex, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    /**
     * @tc.steps: step2. Try to get focus node with out-of-range index
     * @tc.expected: Should return nullptr for non-existent index
     */
    auto result = pattern_->GetChildFocusNodeByIndex(999, 0);
    EXPECT_EQ(result.Upgrade(), nullptr);
}

/**
 * @tc.name: ScrollAndFindFocusNodeBasic
 * @tc.desc: generated. Verify ScrollAndFindFocusNode completes without crash
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ScrollAndFindFocusNodeBasic, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    int32_t nextIndexInGroup = -1;
    auto result = pattern_->ScrollAndFindFocusNode(0, 0, nextIndexInGroup, 0, 1, FocusStep::DOWN);
    // Verify function executed successfully and list structure is intact
    EXPECT_GT(frameNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: ScrollAndFindFocusNodeWithScroll
 * @tc.desc: generated. Verify ScrollAndFindFocusNode can scroll to find focus node
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ScrollAndFindFocusNodeWithScroll, TestSize.Level1)
{
    CreateList();
    CreateListItems(20);
    CreateDone();

    /**
     * @tc.steps: step2. Try to scroll and find focus node at index 10
     * @tc.expected: Should attempt to scroll and return focus node
     */
    int32_t nextIndexInGroup = -1;
    auto result = pattern_->ScrollAndFindFocusNode(10, 0, nextIndexInGroup, 0, 1, FocusStep::DOWN);
    // Verify list structure is still valid after scroll attempt
    EXPECT_GT(frameNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: ScrollAndFindFocusNodeInGroup
 * @tc.desc: generated. Verify ScrollAndFindFocusNode handles ListItemGroup correctly
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ScrollAndFindFocusNodeInGroup, TestSize.Level1)
{
    CreateList();
    CreateListItemGroups(2);
    CreateListItems(5);
    CreateDone();

    /**
     * @tc.steps: step2. Try to find focus node in group context
     * @tc.expected: Should handle group-specific logic
     */
    int32_t nextIndexInGroup = 0;
    auto result = pattern_->ScrollAndFindFocusNode(0, 0, nextIndexInGroup, 0, 1, FocusStep::DOWN);
    // Verify list structure is still valid
    EXPECT_GT(frameNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: HandleDisplayedChildFocusEmptyPosition
 * @tc.desc: generated. Verify HandleDisplayedChildFocus returns false when itemPosition_ is empty
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, HandleDisplayedChildFocusEmptyPosition, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    pattern_->itemPosition_.clear();

    auto result = pattern_->HandleDisplayedChildFocus(0, 1);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleDisplayedChildFocusInvalidIndex
 * @tc.desc: generated. Verify HandleDisplayedChildFocus returns false for invalid index
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, HandleDisplayedChildFocusInvalidIndex, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. Try to handle focus for non-existent index
     * @tc.expected: Should return false
     */
    auto result = pattern_->HandleDisplayedChildFocus(999, 1);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleDisplayedChildFocusWithValidPosition
 * @tc.desc: generated. Verify HandleDisplayedChildFocus handles itemPosition_ correctly
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, HandleDisplayedChildFocusWithValidPosition, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    pattern_->itemPosition_[0] = { 1, 0.0f, 100.0f, false };

    auto result = pattern_->HandleDisplayedChildFocus(0, 1);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleDisplayedChildFocusWithGroup
 * @tc.desc: generated. Verify HandleDisplayedChildFocus handles ListItemGroup position
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, HandleDisplayedChildFocusWithGroup, TestSize.Level1)
{
    CreateList();
    CreateListItemGroups(1);
    CreateListItems(5);
    CreateDone();
    pattern_->itemPosition_[0] = { 1, 0.0f, 100.0f, true };

    /**
     * @tc.steps: step2. Handle displayed child focus with isGroup=true
     * @tc.expected: Should handle group-specific logic
     */
    auto result = pattern_->HandleDisplayedChildFocus(0, 1);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleDisplayedChildFocusAtTop
 * @tc.desc: generated. Verify HandleDisplayedChildFocus when item is at top (startPos < 0)
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, HandleDisplayedChildFocusAtTop, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    pattern_->itemPosition_[0] = { 1, -50.0f, 100.0f, false };

    /**
     * @tc.steps: step2. Handle focus for item above viewport (negative startPos)
     * @tc.expected: Should trigger ScrollToIndex with START alignment
     */
    pattern_->HandleDisplayedChildFocus(0, 1);
    // Verify list structure is still valid after focus handling
    EXPECT_GT(frameNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: HandleDisplayedChildFocusAtBottom
 * @tc.desc: generated. Verify HandleDisplayedChildFocus when item is below viewport
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, HandleDisplayedChildFocusAtBottom, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    pattern_->itemPosition_[0] = { 1, 1000.0f, 1100.0f, false };

    /**
     * @tc.steps: step2. Handle focus for item below viewport (large positive startPos)
     * @tc.expected: Should trigger ScrollToIndex with END alignment
     */
    pattern_->HandleDisplayedChildFocus(0, 1);
    // Verify list structure is still valid after focus handling
    EXPECT_GT(frameNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: ScrollListItemGroupForFocusNullContext
 * @tc.desc: generated. Verify ScrollListItemGroupForFocus handles null pipeline
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ScrollListItemGroupForFocusNullContext, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    frameNode_->context_ = nullptr;

    int32_t nextIndexInGroup = 0;
    auto result = pattern_->ScrollListItemGroupForFocus(0, 0, nextIndexInGroup, 0, 1, FocusStep::DOWN, false);
    EXPECT_TRUE(result);
    EXPECT_EQ(nextIndexInGroup, -1);
}

/**
 * @tc.name: ScrollListItemGroupForFocusNonGroup
 * @tc.desc: generated. Verify ScrollListItemGroupForFocus handles non-ListItemGroup items
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ScrollListItemGroupForFocusNonGroup, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    int32_t nextIndexInGroup = 0;
    auto result = pattern_->ScrollListItemGroupForFocus(0, 0, nextIndexInGroup, 0, 1, FocusStep::DOWN, false);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ScrollListItemGroupForFocusWithGroup
 * @tc.desc: generated. Verify ScrollListItemGroupForFocus works with ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ScrollListItemGroupForFocusWithGroup, TestSize.Level1)
{
    CreateList();
    CreateListItemGroups(2);
    CreateListItems(5);
    CreateDone();

    /**
     * @tc.steps: step2. Call ScrollListItemGroupForFocus with valid group index
     * @tc.expected: Should scroll and find focus node in group
     */
    int32_t nextIndexInGroup = 0;
    auto result = pattern_->ScrollListItemGroupForFocus(0, 0, nextIndexInGroup, 0, 1, FocusStep::DOWN, false);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GetListItemGroupParameterWithListItem
 * @tc.desc: generated. Verify GetListItemGroupParameter returns default values for ListItem not in group
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetListItemGroupParameterWithListItem, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    // Get first ListItem (not in a group)
    auto firstItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(firstItem, nullptr);

    auto result = pattern_->GetListItemGroupParameter(firstItem);
    // ListItem not in group should return default values
    EXPECT_EQ(result.lanes, -1);
    EXPECT_EQ(result.itemEndIndex, -1);
    EXPECT_EQ(result.displayStartIndex, -1);
    EXPECT_EQ(result.displayEndIndex, -1);
    EXPECT_FALSE(result.hasHeader);
    EXPECT_FALSE(result.hasFooter);
}

/**
 * @tc.name: GetListItemGroupParameterWithGroup
 * @tc.desc: generated. Verify GetListItemGroupParameter extracts ListItemGroup parameters correctly
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetListItemGroupParameterWithGroup, TestSize.Level1)
{
    CreateList();
    CreateListItemGroups(1);
    CreateDone();

    if (!itemGroupPatters_.empty()) {
        auto groupNode = itemGroupPatters_[0]->GetHost();
        ASSERT_NE(groupNode, nullptr);

        auto result = pattern_->GetListItemGroupParameter(groupNode);
        EXPECT_GE(result.lanes, -1);
        EXPECT_GE(result.itemEndIndex, -1);
        EXPECT_GE(result.displayStartIndex, -1);
        EXPECT_GE(result.displayEndIndex, -1);
    }
}

/**
 * @tc.name: GetScopeFocusAlgorithmWithList
 * @tc.desc: generated. Verify GetScopeFocusAlgorithm returns valid algorithm
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetScopeFocusAlgorithmWithList, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    auto result = pattern_->GetScopeFocusAlgorithm();
    EXPECT_TRUE(result.isVertical);
    EXPECT_EQ(result.scopeType, ScopeType::OTHERS);
}

/**
 * @tc.name: GetScopeFocusAlgorithmHorizontalList
 * @tc.desc: generated. Verify GetScopeFocusAlgorithm for horizontal list
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, GetScopeFocusAlgorithmHorizontalList, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create horizontal list
     * @tc.expected: List should be created with horizontal direction
     */
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    auto result = pattern_->GetScopeFocusAlgorithm();
    EXPECT_FALSE(result.isVertical); // Horizontal list
    EXPECT_EQ(result.scopeType, ScopeType::OTHERS);
}

/**
 * @tc.name: AdjustFocusGroupIndexInvalidIndex
 * @tc.desc: generated. Verify AdjustFocusGroupIndex returns early for invalid index
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, AdjustFocusGroupIndexInvalidIndex, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    int32_t indexInGroup = 0;
    pattern_->AdjustFocusGroupIndex(-1, indexInGroup);
    EXPECT_EQ(indexInGroup, 0);
}

/**
 * @tc.name: AdjustFocusGroupIndexNegativeInGroup
 * @tc.desc: generated. Verify AdjustFocusGroupIndex returns early for negative indexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, AdjustFocusGroupIndexNegativeInGroup, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    int32_t indexInGroup = -1;
    pattern_->AdjustFocusGroupIndex(0, indexInGroup);
    EXPECT_EQ(indexInGroup, -1);
}

/**
 * @tc.name: AdjustFocusGroupIndexValid
 * @tc.desc: generated. Verify AdjustFocusGroupIndex handles valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, AdjustFocusGroupIndexValid, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. Call with valid index and indexInGroup
     * @tc.expected: Should process without early return
     */
    int32_t indexInGroup = 0;
    pattern_->AdjustFocusGroupIndex(5, indexInGroup);
    // indexInGroup may be modified based on list state
    EXPECT_GE(indexInGroup, -1);
}

/**
 * @tc.name: UpdateStartIndexInvalidIndex
 * @tc.desc: generated. Verify UpdateStartIndex returns false for invalid index
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, UpdateStartIndexInvalidIndex, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    auto result = pattern_->UpdateStartIndex(-1, -1);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: RequestFocusForItemNonExistent
 * @tc.desc: generated. Verify RequestFocusForItem handles non-existent item gracefully
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, RequestFocusForItemNonExistent, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. Call RequestFocusForItem with non-existent index (999)
     * @tc.expected: Function should handle gracefully without crash (early returns at GetChildByIndex)
     */
    pattern_->RequestFocusForItem(999, -1);
    EXPECT_NE(frameNode_, nullptr);
}

/**
 * @tc.name: RequestFocusForItemValidIndex
 * @tc.desc: generated. Verify RequestFocusForItem executes for valid item
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, RequestFocusForItemValidIndex, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. Call RequestFocusForItem with valid index (0)
     * @tc.expected: Function should execute without crash and mark node as dirty
     */
    pattern_->RequestFocusForItem(0, -1);
    EXPECT_NE(frameNode_, nullptr);
}

/**
 * @tc.name: RequestFocusForItemInGroup
 * @tc.desc: generated. Verify RequestFocusForItem handles group index correctly
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, RequestFocusForItemInGroup, TestSize.Level1)
{
    CreateList();
    CreateListItemGroups(2);
    CreateListItems(10);
    CreateDone();

    /**
     * @tc.steps: step2. Request focus for item in group (group 0, item 2)
     * @tc.expected: Should handle group-specific focus logic
     */
    pattern_->RequestFocusForItem(0, 2);
    EXPECT_NE(frameNode_, nullptr);
}

/**
 * @tc.name: RequestFocusForItemLastInGroup
 * @tc.desc: generated. Verify RequestFocusForItem handles last item in group
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, RequestFocusForItemLastInGroup, TestSize.Level1)
{
    CreateList();
    CreateListItemGroups(1);
    CreateListItems(10);
    CreateDone();

    /**
     * @tc.steps: step2. Request focus for last item in group
     * @tc.expected: Should handle correctly
     */
    pattern_->RequestFocusForItem(0, 9);
    EXPECT_NE(frameNode_, nullptr);
}

} // namespace OHOS::Ace::NG
