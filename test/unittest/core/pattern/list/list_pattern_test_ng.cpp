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
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/list/list_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int DEFAULT_HEADER_VALUE = 2;
constexpr int DEFAULT_FOOTER_VALUE = 3;
} // namespace

using namespace testing;
using namespace testing::ext;

class ListPatternTestNg : public TestNG {
public:
};

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
} // namespace OHOS::Ace::NG