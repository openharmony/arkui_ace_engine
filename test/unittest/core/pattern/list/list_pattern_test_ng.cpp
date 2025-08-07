/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
} // namespace OHOS::Ace::NG