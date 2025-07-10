/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "list_test_ng.h"

#include "core/components_ng/pattern/list/list_item_layout_algorithm.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t HEADER_INDEX = 0;
} // namespace

class ListGroupAlgTestNg : public ListTestNg {
public:
    void CreateGroupWithHeader(
        int32_t groupNumber, V2::ListItemGroupStyle listItemGroupStyle, int32_t itemNumber = GROUP_ITEM_NUMBER);
    void CreateGroupWithFooter(
        int32_t groupNumber, V2::ListItemGroupStyle listItemGroupStyle, int32_t itemNumber = GROUP_ITEM_NUMBER);
    void CreateGroupOnlySmallItem(
        int32_t groupNumber, V2::ListItemGroupStyle listItemGroupStyle, int32_t itemNumber = GROUP_ITEM_NUMBER);
    void CreateGroupOnlyBigItem(
        int32_t groupNumber, V2::ListItemGroupStyle listItemGroupStyle, int32_t itemNumber = GROUP_ITEM_NUMBER);
};

void ListGroupAlgTestNg::CreateGroupWithHeader(
    int32_t groupNumber, V2::ListItemGroupStyle listItemGroupStyle, int32_t itemNumber)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        auto header = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
        ListItemGroupModelNG groupModel = CreateListItemGroup(listItemGroupStyle);
        groupModel.SetSpace(Dimension(SPACE));
        groupModel.SetDivider(ITEM_DIVIDER);
        groupModel.SetHeader(std::move(header));
        CreateListItems(itemNumber, static_cast<V2::ListItemStyle>(listItemGroupStyle));
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void ListGroupAlgTestNg::CreateGroupWithFooter(
    int32_t groupNumber, V2::ListItemGroupStyle listItemGroupStyle, int32_t itemNumber)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        auto footer = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
        ListItemGroupModelNG groupModel = CreateListItemGroup(listItemGroupStyle);
        groupModel.SetSpace(Dimension(SPACE));
        groupModel.SetDivider(ITEM_DIVIDER);
        groupModel.SetFooter(std::move(footer));
        CreateListItems(itemNumber, static_cast<V2::ListItemStyle>(listItemGroupStyle));
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void ListGroupAlgTestNg::CreateGroupOnlySmallItem(
    int32_t groupNumber, V2::ListItemGroupStyle listItemGroupStyle, int32_t itemNumber)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        ListItemGroupModelNG groupModel = CreateListItemGroup(listItemGroupStyle);
        groupModel.SetSpace(Dimension(SPACE));
        CreateListItems(itemNumber, static_cast<V2::ListItemStyle>(listItemGroupStyle));
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void ListGroupAlgTestNg::CreateGroupOnlyBigItem(
    int32_t groupNumber, V2::ListItemGroupStyle listItemGroupStyle, int32_t itemNumber)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        ListItemGroupModelNG groupModel = CreateListItemGroup(listItemGroupStyle);
        // 5: Increase the average height of elements by enlarging the space.
        groupModel.SetSpace(Dimension(SPACE * 5));
        CreateListItems(itemNumber, static_cast<V2::ListItemStyle>(listItemGroupStyle));
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

/**
 * @tc.name: CheckReMeasureTest001
 * @tc.desc: check recycledItemPosition while re-measure
 * @tc.type: FUNC
 */

HWTEST_F(ListGroupAlgTestNg, CheckReMeasureTest001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create ListItemGroup and get layoutAlgorithm
    * @tc.expected: layoutAlgorithm not null
    */
    auto model = CreateList();
    CreateGroupWithHeader(1, V2::ListItemGroupStyle::NONE, 10);
    CreateDone();
    auto listProps = AceType::DynamicCast<ListLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_TRUE(listProps);
    auto groupNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    ASSERT_TRUE(groupNode);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(groupNode->GetLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithmWrapper);
    auto layoutAlgorithm =
        AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);

    /**
    * @tc.steps: step2. set itemPosition
    * @tc.expected: after first measure, itemPosition_.size() == 10, recycledItem.size() == 0
    */
    layoutAlgorithm->listLayoutProperty_ = listProps;
    layoutAlgorithm->childLayoutConstraint_ = listProps->CreateChildConstraint();
    layoutAlgorithm->Measure(AceType::RawPtr(groupNode));
    layoutAlgorithm->itemPosition_.clear();
    for (int32_t i = 0; i < 10; i++) {
        layoutAlgorithm->itemPosition_.emplace(std::make_pair(i, ListItemGroupInfo()));
    }
    ASSERT_EQ(static_cast<int32_t>(layoutAlgorithm->recycledItemPosition_.size()), 0);

    /**
    * @tc.steps: step3. re measure listitemgroup
    * @tc.expected: recycledItem.size() != 0
    */
    layoutAlgorithm->Measure(AceType::RawPtr(groupNode));
    ASSERT_NE(static_cast<int32_t>(layoutAlgorithm->recycledItemPosition_.size()), 0);
}

/**
 * @tc.name: BigJumpAccuracyTest001
 * @tc.desc: jump with big offset and check position
 * @tc.type: FUNC
 */

HWTEST_F(ListGroupAlgTestNg, BigJumpAccuracyTest001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Create ListItemGroup with big/small average height
    * @tc.expected: big/small ListItemGroup height is 760/700
    */
    auto model = CreateList();
    model.SetInitialIndex(0);
    CreateGroupOnlySmallItem(10, V2::ListItemGroupStyle::NONE, 7);
    CreateGroupOnlyBigItem(10, V2::ListItemGroupStyle::NONE, 5);
    CreateDone();
    EXPECT_EQ(pattern_->currentOffset_, 0.f);

    /**
    * @tc.steps: step2. Slide to bottom
    * @tc.expected: pos is 760 * 10 + 700 * 10 - 400 = 14200
    */
    UpdateCurrentOffset(-14200.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->currentOffset_, 14200.f);

    /**
    * @tc.steps: step3. Simulate LazyForEach. reset ListItemGroup layoutInfo.
    */
    for (auto i = 0; i < 10; i++) {
        auto groupNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(i));
        auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
        groupPattern->ResetLayoutedInfo();
        groupPattern->cachedItemPosition_.clear();
        groupPattern->mainSize_ = 0.f;
        groupNode->GetGeometryNode()->Reset();
    }

    /**
    * @tc.steps: step4. backToTop. Simulate big offset callback.
    * @tc.expected: after scroll, pos is 14200 - 10000 = 4200
    */
    UpdateCurrentOffset(10000.f, SCROLL_FROM_STATUSBAR);
    EXPECT_EQ(pattern_->currentOffset_, 4200.f);
}

/**
 * @tc.name: ListItemGroupLayoutAlgorithm001
 * @tc.desc: ListItemGroup  Measure
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListItemGroupLayoutAlgorithm_NeedMeasureItem001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItemGroup with header
     * @tc.expected: currentOffset is 260
     */
    auto model = CreateList();
    model.SetInitialIndex(1);
    CreateGroupWithFooter(4, V2::ListItemGroupStyle::NONE);
    CreateDone();
    EXPECT_EQ(pattern_->currentOffset_, 260);

    /**
     * @tc.steps: step2. Scroll -25px, first group footer at top edge
     * @tc.expected: Group1 Offset is 25
     */
    pattern_->UpdateCurrentOffset(25, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 1), OffsetF(0, 25)));
    EXPECT_EQ(pattern_->currentOffset_, 235);

    /**
     * @tc.steps: step3. Scroll 0px, first group footer at top edge
     * @tc.expected: Group1 Offset is 25
     */
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 1), OffsetF(0, 25)));
    EXPECT_EQ(pattern_->currentOffset_, 235);
}

/**
 * @tc.name: ListItemGroupLayoutAlgorithm002
 * @tc.desc: ListItemGroup  Measure
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListItemGroupLayoutAlgorithm_NeedMeasureItem002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItemGroup with header, second group header is at bottom edge.
     */
    auto model = CreateList();
    CreateGroupWithHeader(3, V2::ListItemGroupStyle::NONE, 3);
    CreateDone();

    /**
     * @tc.steps: step2. Scroll 450px, second group header is at top edge.
     * @tc.expected: Group2 Offset is 290
     */
    pattern_->UpdateCurrentOffset(-450, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 2), OffsetF(0, 290)));
    EXPECT_EQ(pattern_->currentOffset_, 450);
}

/**
 * @tc.name: ListItemGroupLayoutAlgorithm_Layout
 * @tc.desc: set layoutWrapper Property null
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListItemGroupLayoutAlgorithm_Layout, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. create List/ListItemGroup and Set Space
     */
    int32_t groupNumber = 2;
    int32_t itemNumber = 3;
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE));
    // head + ListItem + SPACE + ListItem + SPACE + ListItem + Foot
    // FrameNode = 2 * 3
    CreateGroupWithSetting(groupNumber, V2::ListItemGroupStyle::NONE, itemNumber);
    CreateDone();

    /* *
     * @tc.steps: step2. get child frame node from index
     */
    auto groupFrameNode = GetChildFrameNode(frameNode_, 0);

    /* *
     * @tc.steps: step3. build a object about layoutWraper
     */
    RefPtr<LayoutWrapper> layoutWrapper = groupFrameNode->CreateLayoutWrapper(true, true);
    RefPtr<LayoutWrapperNode> layoutWrapper_ = AceType::DynamicCast<LayoutWrapperNode>(layoutWrapper);
    // Set LayoutProperty null , CHECK_NULL_VOID eq null
    layoutWrapper_->layoutProperty_ = nullptr;
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    EXPECT_EQ(layoutProperty, nullptr);

    /* *
     * @tc.steps: step4. build a object about ListItemGroupLayoutAlgorithm
     */
    auto groupPattern = groupFrameNode->GetPattern<ListItemGroupPattern>();
    RefPtr<LayoutAlgorithm> layoutAl = groupPattern->CreateLayoutAlgorithm();
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupAl = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAl);
    listItemGroupAl->headerIndex_ = -1;
    listItemGroupAl->Layout(AceType::RawPtr<LayoutWrapper>(layoutWrapper));
}

/**
 * @tc.name: ListLayoutAlgorithmTest001
 * @tc.desc: Test the list layout from right to left
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ListGroupAlgTestNg, ListLayoutAlgorithmTest001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(listPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, -1, listPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    /**
     * @tc.steps: step2. call Layout function.
     */
    // set reverse true
    auto listLayoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
    listLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, listLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    ListLayoutAlgorithm listLayoutAlgorithm;
    LayoutConstraintF layoutConstraint;
    layoutWrapper->layoutProperty_->layoutConstraint_ = layoutConstraint;
    layoutWrapper->layoutProperty_->contentConstraint_ = layoutConstraint;
    struct ListItemInfo listItemInfo1;
    listItemInfo1.startPos = 0.0f;
    listItemInfo1.endPos = 180.0f;
    listLayoutAlgorithm.contentMainSize_ = 720.0f;
    listLayoutAlgorithm.itemPosition_.emplace(std::make_pair(0, listItemInfo1));
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(listLayoutAlgorithm.itemPosition_.begin()->first);
    auto size = layoutWrapper->GetGeometryNode()->GetMarginFrameSize();
    float crossSize = 300.0f;
    int32_t startIndex = 0;
    listLayoutAlgorithm.LayoutItem(
        wrapper, 0, listLayoutAlgorithm.itemPosition_.begin()->second, startIndex, crossSize);
    float crossOffset = listLayoutAlgorithm.CalculateLaneCrossOffset(crossSize, size.Width(), false);
    auto offset = OffsetF(crossSize - crossOffset - size.Width(), listItemInfo1.startPos);
    EXPECT_EQ(0, crossOffset);
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
    EXPECT_EQ(layoutDirection, TextDirection::RTL);
}

/**
 * @tc.name: ListItemLayoutAlgorithmTest001
 * @tc.desc: Test the listitem layout from right to left
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ListGroupAlgTestNg, ListItemLayoutAlgorithmTest001, TestSize.Level1)
{
    RefPtr<ListItemPattern> listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE);
    ASSERT_NE(listItemPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, -1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    /**
     * @tc.steps: step2. call Layout function.
     */
    // set reverse true
    auto listItemLayoutProperty = frameNode->GetLayoutProperty<ListItemLayoutProperty>();
    listItemLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, listItemLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    ListItemLayoutAlgorithm listItemLayoutAlgorithm(0, 0, 0);
    LayoutConstraintF layoutConstraint;
    layoutWrapper->layoutProperty_->layoutConstraint_ = layoutConstraint;
    layoutWrapper->layoutProperty_->contentConstraint_ = layoutConstraint;
    listItemLayoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
    listItemLayoutAlgorithm.Layout(AceType::RawPtr(layoutWrapper));
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
    EXPECT_EQ(layoutDirection, TextDirection::RTL);
}

/**
 * @tc.name: ListItemLayoutAlgorithmTest002
 * @tc.desc: Test the listitem layout from right to left
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ListGroupAlgTestNg, ListItemLayoutAlgorithmTest002, TestSize.Level1)
{
    RefPtr<ListItemPattern> listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE);
    ASSERT_NE(listItemPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, -1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    /**
     * @tc.steps: step2. call Layout function.
     */
    // set reverse true
    auto listItemLayoutProperty = frameNode->GetLayoutProperty<ListItemLayoutProperty>();
    listItemLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, listItemLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    ListItemLayoutAlgorithm listItemLayoutAlgorithm(0, 0, 0);
    LayoutConstraintF layoutConstraint;
    layoutWrapper->layoutProperty_->layoutConstraint_ = layoutConstraint;
    layoutWrapper->layoutProperty_->contentConstraint_ = layoutConstraint;
    listItemLayoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
    bool value = listItemLayoutAlgorithm.IsRTLAndVertical(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(value, true);
}

/**
 * @tc.name: ListItemGroupLayout001
 * @tc.desc: Test ListItemGroup rect and itemPosition with V2::ListItemGroupStyle::NONE
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListItemGroupLayout001, TestSize.Level1)
{
    CreateList();
    CreateGroupWithSetting(1, V2::ListItemGroupStyle::NONE);
    CreateDone();
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, 0);
    float groupHeight = GROUP_ITEM_NUMBER * (ITEM_MAIN_SIZE + SPACE) - SPACE + GROUP_HEADER_LEN * 2;
    RectF groupRect = GetChildRect(frameNode_, 0);
    RectF headRect = GetChildRect(groupNode, HEADER_INDEX);
    RectF firstItemRect = GetChildRect(groupNode, HEADER_INDEX + 1);
    RectF secondItemRect = GetChildRect(groupNode, HEADER_INDEX + 2);
    RectF footRect = GetChildRect(groupNode, 3);
     EXPECT_TRUE(IsEqual(groupRect, RectF(0, 0, WIDTH, groupHeight)));
    EXPECT_TRUE(IsEqual(headRect, RectF(0, 0, WIDTH, GROUP_HEADER_LEN)));
    EXPECT_TRUE(IsEqual(firstItemRect, RectF(0, GROUP_HEADER_LEN, WIDTH, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(secondItemRect, RectF(0, GROUP_HEADER_LEN + SPACE + ITEM_MAIN_SIZE, WIDTH, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(footRect, RectF(0, groupHeight - GROUP_HEADER_LEN, WIDTH, GROUP_HEADER_LEN)));
}

/**
 * @tc.name: ListItemGroupLayout002
 * @tc.desc: Test ListItemGroup rect and itemPosition with V2::ListItemGroupStyle::CARD
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListItemGroupLayout002, TestSize.Level1)
{
    CreateList();
    CreateGroupWithSetting(1, V2::ListItemGroupStyle::CARD);
    CreateDone();
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, 0);
    float groupHeight = GROUP_ITEM_NUMBER * (ITEM_MAIN_SIZE + SPACE) - SPACE + GROUP_HEADER_LEN * 2;
    RectF groupRect = GetChildRect(frameNode_, 0);
    RectF headRect = GetChildRect(groupNode, 0);
    RectF firstItemRect = GetChildRect(groupNode, HEADER_INDEX + 1);
    RectF secondItemRect = GetChildRect(groupNode, HEADER_INDEX + 2);
    RectF footRect = GetChildRect(groupNode, 3);
    float expectWidth = 216.f;
    EXPECT_TRUE(IsEqual(groupRect, RectF(12.f, 0, expectWidth, groupHeight)));
    EXPECT_TRUE(IsEqual(headRect, RectF(0, 0, expectWidth, GROUP_HEADER_LEN)));
    EXPECT_TRUE(IsEqual(footRect, RectF(0, groupHeight - GROUP_HEADER_LEN, expectWidth, GROUP_HEADER_LEN)));
    EXPECT_TRUE(IsEqual(firstItemRect, RectF(0, GROUP_HEADER_LEN, expectWidth, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(
        IsEqual(secondItemRect, RectF(0, GROUP_HEADER_LEN + SPACE + ITEM_MAIN_SIZE, expectWidth, ITEM_MAIN_SIZE)));
}

/**
 * @tc.name: ListItemGroupLayout003
 * @tc.desc: Test CARD not support HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListItemGroupLayout003, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    CreateGroupWithSetting(2, V2::ListItemGroupStyle::CARD);
    CreateDone();
    EXPECT_EQ(layoutProperty_->GetListDirection(), Axis::VERTICAL);
    EXPECT_LT(GetChildX(frameNode_, 0), GetChildX(frameNode_, 1));
}

/**
 * @tc.name: ListItemGroupLayout004
 * @tc.desc: Test model SetStyle
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListItemGroupLayout004, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    ListItemGroupModelNG groupModel = CreateListItemGroup(V2::ListItemGroupStyle::NONE);
    CreateListItem();
    CreateDone();

    /**
     * @tc.steps: step1. Change NONE to CARD
     * @tc.expected: Change to CARD
     */
    auto groupNode = GetChildFrameNode(frameNode_, 0);
    auto groupPattern = GetChildPattern<ListItemGroupPattern>(frameNode_, 0);
    auto groupRenderContext = groupNode->GetRenderContext();
    groupModel.SetStyle(AceType::RawPtr(groupNode), V2::ListItemGroupStyle::CARD);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(groupPattern->listItemGroupStyle_, V2::ListItemGroupStyle::CARD);
    EXPECT_EQ(groupRenderContext->GetBackgroundColor(), ITEM_DEFAULT_COLOR);

    /**
     * @tc.steps: step2. Change CARD to NONE
     * @tc.expected: Still is CARD
     */
    groupPattern->SetListItemGroupStyle(V2::ListItemGroupStyle::NONE);
    EXPECT_EQ(groupPattern->listItemGroupStyle_, V2::ListItemGroupStyle::CARD);
}

/**
 * @tc.name: ListItemGroupLayout005
 * @tc.desc: Test model SetStyle
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListItemGroupLayout005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. No Item in group
     * @tc.expected: The group height depend on header+footer
     */
    ListModelNG model = CreateList();
    CreateGroupWithSetting(1, V2::ListItemGroupStyle::NONE, 0);
    CreateGroupWithHeader(1, V2::ListItemGroupStyle::NONE, 0);
    CreateGroupWithFooter(1, V2::ListItemGroupStyle::NONE, 0);
    CreateDone();
    EXPECT_EQ(GetChildHeight(frameNode_, 0), GROUP_HEADER_LEN * 2);
    EXPECT_EQ(GetChildHeight(frameNode_, 1), GROUP_HEADER_LEN);
    EXPECT_EQ(GetChildHeight(frameNode_, 2), GROUP_HEADER_LEN);
}

/**
 * @tc.name: Sticky001
 * @tc.desc: List set sticky header and footer
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, Sticky001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::StickyStyle::HEADER
     * @tc.expected: head is Sticky
     */
    ListModelNG model = CreateList();
    model.SetSticky(V2::StickyStyle::HEADER);
    CreateGroupWithSetting(GROUP_NUMBER, V2::ListItemGroupStyle::NONE);
    CreateDone();
    RefPtr<FrameNode> firstGroupNode = GetChildFrameNode(frameNode_, 0);
    RefPtr<FrameNode> secondGroupNode = GetChildFrameNode(frameNode_, 1);
    EXPECT_EQ(GetChildY(firstGroupNode, HEADER_INDEX), 0);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(GetChildY(firstGroupNode, HEADER_INDEX), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step2. V2::StickyStyle::FOOTER
     * @tc.expected: foot is Sticky
     */
    ScrollTo(0); // reset position
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::FOOTER);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    float expectOffset = HEIGHT - GetChildHeight(frameNode_, 0) - GROUP_HEADER_LEN;
    auto footerIndex  = 1/*HeaderCount*/ + GROUP_ITEM_NUMBER;
    EXPECT_EQ(GetChildY(secondGroupNode, footerIndex), GROUP_HEADER_LEN);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(GetChildY(secondGroupNode, footerIndex), expectOffset + ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step3. V2::StickyStyle::BOTH
     * @tc.expected: head/foot is Sticky
     */
    ScrollTo(0); // reset position
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::BOTH);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(GetChildY(firstGroupNode, HEADER_INDEX), 0);
    EXPECT_EQ(GetChildY(secondGroupNode, footerIndex), GROUP_HEADER_LEN);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(GetChildY(firstGroupNode, HEADER_INDEX), ITEM_MAIN_SIZE);
    EXPECT_EQ(GetChildY(secondGroupNode, footerIndex), expectOffset + ITEM_MAIN_SIZE);
}

/**
 * @tc.name: Sticky002
 * @tc.desc: List set sticky header in RTL Layout, but RTL has no effect
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, Sticky002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::StickyStyle::HEADER
     * @tc.expected: head is Sticky
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true; // no effect because vertical layout
    ListModelNG model = CreateList();
    model.SetSticky(V2::StickyStyle::HEADER);
    CreateGroupWithHeader(GROUP_NUMBER, V2::ListItemGroupStyle::NONE);
    CreateDone();
    RefPtr<FrameNode> firstGroupNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_EQ(GetChildY(firstGroupNode, HEADER_INDEX), 0);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(GetChildY(firstGroupNode, HEADER_INDEX), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step2. V2::StickyStyle::BOTH
     * @tc.expected: head is Sticky
     */
    ScrollTo(0); // reset position
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::BOTH);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(GetChildY(firstGroupNode, HEADER_INDEX), 0);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(GetChildY(firstGroupNode, HEADER_INDEX), ITEM_MAIN_SIZE);
}

/**
 * @tc.name: Sticky003
 * @tc.desc: List set sticky footer
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, Sticky003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::StickyStyle::FOOTER
     * @tc.expected: foot is Sticky
     */
 
    ListModelNG model = CreateList();
    model.SetSticky(V2::StickyStyle::FOOTER);
    CreateGroupWithFooter(GROUP_NUMBER, V2::ListItemGroupStyle::NONE);
    CreateDone();
    const int32_t footerIndex = GROUP_ITEM_NUMBER;
    RefPtr<FrameNode> secondGroupNode = GetChildFrameNode(frameNode_, 1);
    float expectOffset = HEIGHT - GetChildHeight(frameNode_, 0) - GROUP_HEADER_LEN;
    EXPECT_EQ(GetChildY(secondGroupNode, footerIndex), expectOffset);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(GetChildY(secondGroupNode, footerIndex), expectOffset + ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step3. V2::StickyStyle::BOTH
     * @tc.expected: head/foot is Sticky
     */
    ScrollTo(0); // reset position
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::BOTH);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(GetChildY(secondGroupNode, footerIndex), expectOffset);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(GetChildY(secondGroupNode, footerIndex), expectOffset + ITEM_MAIN_SIZE);
}

/**
 * @tc.name: Sticky004
 * @tc.desc: List set sticky header and footer in HORIZONTAL and RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, Sticky004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::StickyStyle::HEADER
     * @tc.expected: head is Sticky
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    ListModelNG model = CreateList();
    ViewAbstract::SetWidth(CalcLength(400));
    model.SetListDirection(Axis::HORIZONTAL);
    model.SetSticky(V2::StickyStyle::HEADER);
    CreateGroupWithSetting(GROUP_NUMBER, V2::ListItemGroupStyle::NONE);
    CreateDone();
    RefPtr<FrameNode> firstGroupNode = GetChildFrameNode(frameNode_, 0);
    RefPtr<FrameNode> secondGroupNode = GetChildFrameNode(frameNode_, 1);
    EXPECT_EQ(GetChildX(firstGroupNode, HEADER_INDEX), 260.f);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(GetChildX(firstGroupNode, HEADER_INDEX), 160.f);

    /**
     * @tc.steps: step2. V2::StickyStyle::FOOTER
     * @tc.expected: foot is Sticky
     */
    ScrollTo(0); // reset position
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::FOOTER);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    auto footerIndex = 1/*HeaderCount*/ + GROUP_ITEM_NUMBER;
    EXPECT_EQ(GetChildX(secondGroupNode, footerIndex), 210.f);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(GetChildX(secondGroupNode, footerIndex), 120.f);

    /**
     * @tc.steps: step3. V2::StickyStyle::BOTH
     * @tc.expected: head/foot is Sticky
     */
    ScrollTo(0); // reset position
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::BOTH);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(GetChildY(firstGroupNode, HEADER_INDEX), 0);
    EXPECT_EQ(GetChildY(secondGroupNode, footerIndex), 0);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(GetChildY(firstGroupNode, HEADER_INDEX), 0);
    EXPECT_EQ(GetChildY(secondGroupNode, footerIndex), 0);
}

/**
 * @tc.name: Sticky005
 * @tc.desc: List set sticky header in HORIZONTAL and RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, Sticky005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::StickyStyle::HEADER
     * @tc.expected: head is Sticky
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    ListModelNG model = CreateList();
    ViewAbstract::SetWidth(CalcLength(400));
    model.SetListDirection(Axis::HORIZONTAL);
    model.SetSticky(V2::StickyStyle::HEADER);
    CreateGroupWithHeader(GROUP_NUMBER, V2::ListItemGroupStyle::NONE);
    CreateDone();
    RefPtr<FrameNode> firstGroupNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_EQ(GetChildX(firstGroupNode, HEADER_INDEX), 210.f);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(GetChildX(firstGroupNode, HEADER_INDEX), 110.f);

    /**
     * @tc.steps: step2. V2::StickyStyle::BOTH
     * @tc.expected: head is Sticky
     */
    ScrollTo(0); // reset position
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::BOTH);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(GetChildY(firstGroupNode, HEADER_INDEX), 0);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(GetChildY(firstGroupNode, HEADER_INDEX), 0);
}

/**
 * @tc.name: Sticky006
 * @tc.desc: List set sticky footer in HORIZONTAL and RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, Sticky006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::StickyStyle::FOOTER
     * @tc.expected: foot is Sticky
     */
    const int32_t footerIndex = GROUP_ITEM_NUMBER;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    ListModelNG model = CreateList();
    ViewAbstract::SetWidth(CalcLength(400));
    model.SetListDirection(Axis::HORIZONTAL);
    model.SetSticky(V2::StickyStyle::FOOTER);
    CreateGroupWithFooter(GROUP_NUMBER, V2::ListItemGroupStyle::NONE);
    CreateDone();
    RefPtr<FrameNode> secondGroupNode = GetChildFrameNode(frameNode_, 1);
    EXPECT_EQ(GetChildX(secondGroupNode, footerIndex), 120.f);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(GetChildX(secondGroupNode, footerIndex), 20.f);

    /**
     * @tc.steps: step2. V2::StickyStyle::BOTH
     * @tc.expected: head/foot is Sticky
     */
    ScrollTo(0); // reset position
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::BOTH);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(GetChildY(secondGroupNode, footerIndex), 0);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(GetChildY(secondGroupNode, footerIndex), 0);
}

/**
 * @tc.name: Sticky007
 * @tc.desc: List set sticky footer when top out of boundary
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, Sticky007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::StickyStyle::FOOTER
     * @tc.expected: footer is Sticky
     */
    ListModelNG model = CreateList();
    model.SetSticky(V2::StickyStyle::FOOTER);
    CreateGroupWithFooter(1, V2::ListItemGroupStyle::NONE, 4);
    CreateDone();
    RefPtr<FrameNode> firstGroupNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_EQ(GetChildY(firstGroupNode, 4), 350.f);

    /**
     * @tc.steps: step2. List scroll out of Top
     * @tc.expected: footer is Sticky
     */
    auto scrollable = pattern_->scrollableEvent_->GetScrollable();
    EXPECT_NE(scrollable, nullptr);
    scrollable->isTouching_ = true;
    UpdateCurrentOffset(100, SCROLL_FROM_UPDATE);
    float footerPos = GetChildY(frameNode_, 0) + GetChildY(firstGroupNode, 4);
    EXPECT_EQ(footerPos, 350.f);

    UpdateCurrentOffset(100, SCROLL_FROM_UPDATE);
    footerPos = GetChildY(frameNode_, 0) + GetChildY(firstGroupNode, 4);
    EXPECT_EQ(footerPos, 350.f);
}

/**
 * @tc.name: LanesLayout001
 * @tc.desc: test lanes
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, LanesLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetLanes 2
     * @tc.expected: has 2 lanes items
     */
    int32_t lanes = 2;
    ListModelNG model = CreateList();
    model.SetLanes(lanes);
    CreateListItemGroups(1);
    CreateDone();
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_EQ(GetChildHeight(frameNode_, 0), std::ceil(GROUP_ITEM_NUMBER / lanes) * ITEM_MAIN_SIZE);
    EXPECT_LT(GetChildX(groupNode, 0), GetChildX(groupNode, 1));

    /**
     * @tc.steps: step2. maxLaneLength > WIDTH
     * @tc.expected: has 1 lanes items
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLaneMinLength(Dimension(300.f));
    model.SetLaneMaxLength(Dimension(WIDTH + 100.f));
    CreateListItemGroups(1);
    CreateDone();
    groupNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), WIDTH);
    EXPECT_LT(GetChildY(groupNode, 0), GetChildY(groupNode, 1));

    /**
     * @tc.steps: step3. maxLaneLength < WIDTH
     * @tc.expected: has 1 lanes items
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLaneMinLength(Dimension(300.f));
    model.SetLaneMaxLength(Dimension(350.f));
    CreateListItemGroups(1);
    CreateDone();
    groupNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), WIDTH);
    EXPECT_LT(GetChildY(groupNode, 0), GetChildY(groupNode, 1));

    /**
     * @tc.steps: step4. SetLanes 2 with header/footer/space ...
     * @tc.expected: has 2 lanes items
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(lanes);
    CreateGroupWithSetting(1, V2::ListItemGroupStyle::NONE);
    CreateDone();
    groupNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_LT(GetChildX(groupNode, 1), GetChildX(groupNode, 2));

    /**
     * @tc.steps: step5. set minLaneLength/maxLaneLength with header/footer/space ...
     * @tc.expected: headWidth would be maxLaneLength
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLaneMinLength(Dimension(300.f));
    model.SetLaneMaxLength(Dimension(400.f));
    CreateGroupWithSetting(1, V2::ListItemGroupStyle::NONE);
    CreateDone();
    groupNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_EQ(GetChildWidth(groupNode, HEADER_INDEX), WIDTH);
    EXPECT_LT(GetChildY(groupNode, 1), GetChildY(groupNode, 2));
}

/**
 * @tc.name: ListItemAlign001
 * @tc.desc: test SetListItemAlign
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListItemAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. V2::ListItemAlign::START
     */
    const float itemWidth = WIDTH - 100.f;
    ListModelNG model = CreateList();
    model.SetListItemAlign(V2::ListItemAlign::START);
    CreateListItemGroup(V2::ListItemGroupStyle::NONE);
    CreateListItem();
    ViewAbstract::SetWidth(CalcLength(itemWidth));
    CreateDone();
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_EQ(GetChildX(groupNode, 0), 0);

    /**
     * @tc.steps: step2. V2::ListItemAlign::CENTER
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::CENTER);
    FlushUITasks();
    EXPECT_EQ(GetChildX(groupNode, 0), (WIDTH - itemWidth) / 2);

    /**
     * @tc.steps: step3. V2::ListItemAlign::END
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::END);
    FlushUITasks();
    EXPECT_EQ(GetChildX(groupNode, 0), WIDTH - itemWidth);
}

/**
 * @tc.name: ListItemAlign002
 * @tc.desc: test SetListItemAlign in RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListItemAlign002, TestSize.Level1)
{
    /**
     * @tc.steps: step2. V2::ListItemAlign::START
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    const float itemWidth = WIDTH - 100.f;
    ListModelNG model = CreateList();
    model.SetListItemAlign(V2::ListItemAlign::START);
    CreateListItemGroup(V2::ListItemGroupStyle::NONE);
    CreateListItem();
    ViewAbstract::SetWidth(CalcLength(itemWidth));
    CreateDone();
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_EQ(GetChildX(groupNode, 0), WIDTH - itemWidth);

    /**
     * @tc.steps: step2. V2::ListItemAlign::CENTER
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::CENTER);
    FlushUITasks();
    EXPECT_EQ(GetChildX(groupNode, 0), (WIDTH - itemWidth) / 2);

    /**
     * @tc.steps: step3. V2::ListItemAlign::END
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::END);
    FlushUITasks();
    EXPECT_EQ(GetChildX(groupNode, 0), 0);
}

/**
 * @tc.name: ListGroupRepeatCacheCount001
 * @tc.desc: ListItemGroup cacheCount
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListGroupRepeatCacheCount001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    ListItemGroupModelNG groupModel = CreateListItemGroup();
    auto header = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
    groupModel.SetHeader(std::move(header));
    CreateRepeatVirtualScrollNode(10, [this](int32_t idx) {
        CreateListItem();
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    });
    CreateDone();

    /**
     * @tc.steps: step1. Check Repeat frameCount
     */
    auto groupNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto repeat = AceType::DynamicCast<RepeatVirtualScrollNode>(groupNode->GetChildAtIndex(1));
    EXPECT_NE(repeat, nullptr);
    int32_t frameCount = repeat->FrameCount();
    EXPECT_EQ(frameCount, 10);

    /**
     * @tc.steps: step2. Flush Idle Task
     * @tc.expected: ListItem 4 is cached
     */
    auto listPattern = frameNode_->GetPattern<ListPattern>();
    FlushIdleTask(listPattern);
    int32_t childrenCount = repeat->GetChildren().size();
    EXPECT_EQ(childrenCount, 5);
    auto cachedItem = groupNode->GetChildByIndex(4 + 1)->GetHostNode();
    EXPECT_EQ(cachedItem->IsActive(), false);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildY(groupNode, 4 + 1), ITEM_MAIN_SIZE * 4 + GROUP_HEADER_LEN);

    /**
     * @tc.steps: step3. Flush Idle Task
     * @tc.expected: ListItem 1 and 7 is cached, ListItem 2,3,4,5,6 is active.
     */
    UpdateCurrentOffset(-300, SCROLL_FROM_JUMP);
    FlushIdleTask(listPattern);
    childrenCount = repeat->GetChildren().size();
    EXPECT_EQ(childrenCount, 7);
    cachedItem = groupNode->GetChildByIndex(1 + 1)->GetHostNode();
    EXPECT_EQ(cachedItem->IsActive(), false);
    EXPECT_EQ(GetChildY(frameNode_, 0), -300.0f);
    EXPECT_EQ(GetChildY(groupNode, 1 + 1), ITEM_MAIN_SIZE * 1 + GROUP_HEADER_LEN);
    cachedItem = groupNode->GetChildByIndex(7 + 1)->GetHostNode();
    EXPECT_EQ(cachedItem->IsActive(), false);
    EXPECT_EQ(GetChildY(frameNode_, 0), -300.0f);
    EXPECT_EQ(GetChildY(groupNode, 7 + 1), ITEM_MAIN_SIZE * 7 + GROUP_HEADER_LEN);
}

/**
 * @tc.name: ListGroupRepeatCacheCount002
 * @tc.desc: ListItemGroup lanes cacheCount
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListGroupRepeatCacheCount002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetLanes(2);
    ListItemGroupModelNG groupModel = CreateListItemGroup();
    auto header = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
    groupModel.SetHeader(std::move(header));
    CreateRepeatVirtualScrollNode(20, [this](int32_t idx) {
        CreateListItem();
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    });
    CreateDone();

    /**
     * @tc.steps: step1. Check Repeat frameCount
     */
    auto groupNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto repeat = AceType::DynamicCast<RepeatVirtualScrollNode>(groupNode->GetChildAtIndex(1));
    EXPECT_NE(repeat, nullptr);
    int32_t frameCount = repeat->FrameCount();
    EXPECT_EQ(frameCount, 20);

    /**
     * @tc.steps: step2. Flush Idle Task
     * @tc.expected: ListItem 8, 9 is cached
     */
    auto listPattern = frameNode_->GetPattern<ListPattern>();
    FlushIdleTask(listPattern);
    int32_t childrenCount = repeat->GetChildren().size();
    EXPECT_EQ(childrenCount, 10);
    auto item8 = groupNode->GetChildByIndex(8 + 1)->GetHostNode();
    EXPECT_EQ(item8->IsActive(), false);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildY(groupNode, 8 + 1), ITEM_MAIN_SIZE * (8 / 2) + GROUP_HEADER_LEN);
    auto item9 = groupNode->GetChildByIndex(9 + 1)->GetHostNode();
    EXPECT_EQ(item9->IsActive(), false);
    EXPECT_EQ(GetChildX(groupNode, 9 + 1), WIDTH / 2);
    EXPECT_EQ(GetChildY(groupNode, 9 + 1), ITEM_MAIN_SIZE * (9 / 2) + GROUP_HEADER_LEN);

    /**
     * @tc.steps: step3. Flush Idle Task
     * @tc.expected: ListItem 2,3,14,15 is cached, ListItem 4-13 active.
     */
    UpdateCurrentOffset(-300, SCROLL_FROM_JUMP);
    FlushIdleTask(listPattern);
    childrenCount = repeat->GetChildren().size();
    EXPECT_EQ(childrenCount, 14);
    EXPECT_EQ(GetChildY(frameNode_, 0), -300.0f);
    auto item2 = groupNode->GetChildByIndex(2 + 1)->GetHostNode();
    EXPECT_EQ(item2->IsActive(), false);
    EXPECT_EQ(GetChildY(groupNode, 2 + 1), ITEM_MAIN_SIZE * (2 / 2) + GROUP_HEADER_LEN);
    auto item3 = groupNode->GetChildByIndex(3 + 1)->GetHostNode();
    EXPECT_EQ(item3->IsActive(), false);
    EXPECT_EQ(GetChildX(groupNode, 3 + 1), WIDTH / 2);
    EXPECT_EQ(GetChildY(groupNode, 3 + 1), ITEM_MAIN_SIZE * (3 / 2) + GROUP_HEADER_LEN);
    auto item14 = groupNode->GetChildByIndex(14 + 1)->GetHostNode();
    EXPECT_EQ(item14->IsActive(), false);
    EXPECT_EQ(GetChildY(groupNode, 14 + 1), ITEM_MAIN_SIZE * (14 / 2) + GROUP_HEADER_LEN);
    auto item15 = groupNode->GetChildByIndex(15 + 1)->GetHostNode();
    EXPECT_EQ(item15->IsActive(), false);
    EXPECT_EQ(GetChildX(groupNode, 15 + 1), WIDTH / 2);
    EXPECT_EQ(GetChildY(groupNode, 15 + 1), ITEM_MAIN_SIZE * (15 / 2) + GROUP_HEADER_LEN);
}

/**
 * @tc.name: ListGroupRepeatCacheCount003
 * @tc.desc: ListItemGroup lanes cacheCount
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListGroupRepeatCacheCount003, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetCachedCount(2);
    model.SetSticky(V2::StickyStyle::BOTH);
    CreateRepeatVirtualScrollNode(3, [this](int32_t idx) {
        ListItemGroupModelNG groupModel = CreateListItemGroup();
        auto header = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
        groupModel.SetHeader(std::move(header));
        CreateRepeatVirtualScrollNode(5, [this](int32_t idx) {
            CreateListItem();
            ViewStackProcessor::GetInstance()->Pop();
            ViewStackProcessor::GetInstance()->StopGetAccessRecording();
        });
    });
    CreateDone();

    /**
     * @tc.steps: step1. Check Repeat frameCount
     */
    auto repeat = AceType::DynamicCast<RepeatVirtualScrollNode>(frameNode_->GetChildAtIndex(0));
    EXPECT_EQ(repeat->FrameCount(), 3);

    /**
     * @tc.steps: step2. Flush Idle Task
     * @tc.expected: Group0 ListItem 4 is cached, Group1 ListItem1 is cached
     */
    auto listPattern = frameNode_->GetPattern<ListPattern>();
    FlushIdleTask(listPattern);
    // check group0
    auto groupNode0 = AceType::DynamicCast<FrameNode>(frameNode_->GetChildByIndex(0));
    auto repeat0 = AceType::DynamicCast<RepeatVirtualScrollNode>(groupNode0->GetChildAtIndex(1));
    int32_t childrenCount = repeat0->GetChildren().size();
    EXPECT_EQ(childrenCount, 5);
    auto g0Item4 = groupNode0->GetChildByIndex(4 + 1)->GetHostNode();
    EXPECT_EQ(g0Item4->IsActive(), false);
    // check group1
    auto groupNode1 = AceType::DynamicCast<FrameNode>(frameNode_->GetChildByIndex(1));
    auto repeat1 = AceType::DynamicCast<RepeatVirtualScrollNode>(groupNode1->GetChildAtIndex(1));
    childrenCount = repeat1->GetChildren().size();
    EXPECT_EQ(childrenCount, 1);
    auto g1Item0 = groupNode1->GetChildByIndex(0 + 1)->GetHostNode();
    EXPECT_EQ(g1Item0->IsActive(), false);

    /**
     * @tc.steps: step3. Flush Idle Task
     * @tc.expected: group0 item4 cached, group1 item0 cached, group2 item0-1 cached
     */
    UpdateCurrentOffset(-725);
    FlushIdleTask(listPattern);
    // check group 0
    childrenCount = repeat0->GetChildren().size();
    EXPECT_EQ(childrenCount, 1);
    g0Item4 = groupNode0->GetChildByIndex(4 + 1)->GetHostNode();
    EXPECT_EQ(g0Item4->IsActive(), false);
    // check group 0
    childrenCount = repeat1->GetChildren().size();
    EXPECT_EQ(childrenCount, 5);
    g1Item0 = groupNode1->GetChildByIndex(0 + 1)->GetHostNode();
    EXPECT_EQ(g1Item0->IsActive(), false);
    // check group 2
    auto groupNode2 = AceType::DynamicCast<FrameNode>(frameNode_->GetChildByIndex(2));
    auto repeat2 = AceType::DynamicCast<RepeatVirtualScrollNode>(groupNode2->GetChildAtIndex(1));
    childrenCount = repeat2->GetChildren().size();
    EXPECT_EQ(childrenCount, 2);
    auto g2item0 = groupNode2->GetChildByIndex(0 + 1)->GetHostNode();
    EXPECT_EQ(g2item0->IsActive(), false);
    auto g2item1 = groupNode2->GetChildByIndex(1 + 1)->GetHostNode();
    EXPECT_EQ(g2item1->IsActive(), false);
}

/**
 * @tc.name: ListGroupRepeatCacheCount004
 * @tc.desc: ListItemGroup lanes cacheCount
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListGroupRepeatCacheCount004, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetCachedCount(2);
    model.SetLaneMinLength(Dimension(100));
    model.SetLaneMaxLength(Dimension(240));
    CreateRepeatVirtualScrollNode(3, [this](int32_t idx) {
        ListItemGroupModelNG groupModel = CreateListItemGroup();
        auto header = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
        groupModel.SetHeader(std::move(header));
        ViewAbstract::SetWidth(CalcLength(180));
        CreateRepeatVirtualScrollNode(5, [this](int32_t idx) {
            CreateListItem();
            ViewStackProcessor::GetInstance()->Pop();
            ViewStackProcessor::GetInstance()->StopGetAccessRecording();
        });
    });
    CreateDone();

    /**
     * @tc.steps: step1. Check Repeat frameCount
     */
    auto repeat = AceType::DynamicCast<RepeatVirtualScrollNode>(frameNode_->GetChildAtIndex(0));
    EXPECT_EQ(repeat->FrameCount(), 3);

    /**
     * @tc.steps: step2. Flush Idle Task
     * @tc.expected: Group0 ListItem 4 is cached, Group1 ListItem1 is cached
     */
    auto listPattern = frameNode_->GetPattern<ListPattern>();
    FlushIdleTask(listPattern);
    // check group0
    auto groupNode0 = AceType::DynamicCast<FrameNode>(frameNode_->GetChildByIndex(0));
    auto repeat0 = AceType::DynamicCast<RepeatVirtualScrollNode>(groupNode0->GetChildAtIndex(1));
    int32_t childrenCount = repeat0->GetChildren().size();
    EXPECT_EQ(childrenCount, 5);
    auto g0Item4 = groupNode0->GetChildByIndex(4 + 1)->GetHostNode();
    EXPECT_EQ(g0Item4->IsActive(), false);
    // check group1
    auto groupNode1 = AceType::DynamicCast<FrameNode>(frameNode_->GetChildByIndex(1));
    auto repeat1 = AceType::DynamicCast<RepeatVirtualScrollNode>(groupNode1->GetChildAtIndex(1));
    childrenCount = repeat1->GetChildren().size();
    EXPECT_EQ(childrenCount, 1);
    auto g1Item0 = groupNode1->GetChildByIndex(0 + 1)->GetHostNode();
    EXPECT_EQ(g1Item0->IsActive(), false);

    /**
     * @tc.steps: step3. Flush Idle Task
     * @tc.expected: group0 item4 cached, group1 item0 cached, group2 item0-1 cached
     */
    UpdateCurrentOffset(-725);
    FlushIdleTask(listPattern);
    // check group 0
    childrenCount = repeat0->GetChildren().size();
    EXPECT_EQ(childrenCount, 1);
    g0Item4 = groupNode0->GetChildByIndex(4 + 1)->GetHostNode();
    EXPECT_EQ(g0Item4->IsActive(), false);
    // check group 0
    childrenCount = repeat1->GetChildren().size();
    EXPECT_EQ(childrenCount, 5);
    g1Item0 = groupNode1->GetChildByIndex(0 + 1)->GetHostNode();
    EXPECT_EQ(g1Item0->IsActive(), false);
    // check group 2
    auto groupNode2 = AceType::DynamicCast<FrameNode>(frameNode_->GetChildByIndex(2));
    auto repeat2 = AceType::DynamicCast<RepeatVirtualScrollNode>(groupNode2->GetChildAtIndex(1));
    childrenCount = repeat2->GetChildren().size();
    EXPECT_EQ(childrenCount, 2);
    auto g2item0 = groupNode2->GetChildByIndex(0 + 1)->GetHostNode();
    EXPECT_EQ(g2item0->IsActive(), false);
    auto g2item1 = groupNode2->GetChildByIndex(1 + 1)->GetHostNode();
    EXPECT_EQ(g2item1->IsActive(), false);
}

/**
 * @tc.name: Space001
 * @tc.desc: test space
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, Space001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set Normal space
     * @tc.expected: There is space between listItems
     */
    CreateList();
    ListItemGroupModelNG groupModel = CreateListItemGroup();
    groupModel.SetSpace(Dimension(SPACE));
    CreateListItems(GROUP_ITEM_NUMBER);
    CreateDone();
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_EQ(GetChildY(groupNode, 1), ITEM_MAIN_SIZE + SPACE);

    /**
     * @tc.steps: step2. Set invalid space
     * @tc.expected: Space reset to 0
     */
    auto groupProperty = groupNode->GetLayoutProperty<ListItemGroupLayoutProperty>();
    groupProperty->UpdateSpace(Dimension(-1.f));
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(GetChildY(groupNode, 1), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step3. Set space > groupHeight
     * @tc.expected: Space reset to 0
     */
    groupProperty->UpdateSpace(Dimension(HEIGHT));
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(GetChildY(groupNode, 1), ITEM_MAIN_SIZE);
}

/**
 * @tc.name: Divider001
 * @tc.desc: test divider
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, Divider001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set Normal divider
     * @tc.expected: There is divider between listItems
     */
    CreateList();
    ListItemGroupModelNG groupModel = CreateListItemGroup();
    groupModel.SetDivider(ITEM_DIVIDER);
    CreateListItems(GROUP_ITEM_NUMBER);
    CreateDone();
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_EQ(GetChildY(groupNode, 1), ITEM_MAIN_SIZE + STROKE_WIDTH);

    /**
     * @tc.steps: step2. Set invalid strokeWidth
     * @tc.expected: StrokeWidth reset to 0
     */
    auto divider = ITEM_DIVIDER;
    divider.strokeWidth = Dimension(-1.f);
    auto groupProperty = groupNode->GetLayoutProperty<ListItemGroupLayoutProperty>();
    groupProperty->UpdateDivider(divider);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(GetChildY(groupNode, 1), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step3. Set strokeWidth > groupHeight
     * @tc.expected: StrokeWidth reset to 0
     */
    divider.strokeWidth = Dimension(HEIGHT);
    groupProperty->UpdateDivider(divider);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(GetChildY(groupNode, 1), ITEM_MAIN_SIZE);
}

/**
 * @tc.name: SpaceDivider001
 * @tc.desc: test space and divider
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, SpaceDivider001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set Normal space and divider, SPACE > strokeWidth
     * @tc.expected: There is interval between listItems and equal to SPACE
     */
    CreateList();
    ListItemGroupModelNG groupModel = CreateListItemGroup();
    groupModel.SetSpace(Dimension(SPACE));
    groupModel.SetDivider(ITEM_DIVIDER);
    CreateListItems(GROUP_ITEM_NUMBER);
    CreateDone();
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_EQ(GetChildY(groupNode, 1), ITEM_MAIN_SIZE + SPACE);

    /**
     * @tc.steps: step2. Set SPACE < strokeWidth
     * @tc.expected: The interval is strokeWidth
     */
    auto groupProperty = groupNode->GetLayoutProperty<ListItemGroupLayoutProperty>();
    groupProperty->UpdateSpace(Dimension(1.f));
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(GetChildY(groupNode, 1), ITEM_MAIN_SIZE + STROKE_WIDTH);
}

/**
 * @tc.name: InfinityCrossSize001
 * @tc.desc: test Infinity crossSize
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, InfinityCrossSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set Group Infinity crossSize
     * @tc.expected: crossSize equal to child size
     */
    CreateList();
    CreateListItemGroup();
    ViewAbstract::SetWidth(CalcLength(Infinity<float>()));
    CreateListItem();
    ViewAbstract::SetWidth(CalcLength(150.f));
    CreateDone();
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 150.f);
}

/**
 * @tc.name: SetHeaderFooter001
 * @tc.desc: test SetHeader/SetFooter to null, will not has header/footer
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, SetHeaderFooter001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set header footer to null
     * @tc.expected: Will not has header/footer node
     */
    CreateList();
    ListItemGroupModelNG groupModel = CreateListItemGroup();
    groupModel.SetHeader(nullptr);
    groupModel.SetFooter(nullptr);
    auto groupNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_EQ(groupNode->GetTotalChildCount(), 0);

    /**
     * @tc.steps: step2. Set header
     * @tc.expected: Has header node
     */
    auto header = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
    groupModel.SetHeader(std::move(header));
    EXPECT_EQ(groupNode->GetTotalChildCount(), 1);

    /**
     * @tc.steps: step3. Set footer
     * @tc.expected: Has header and footer nodes
     */
    auto footer = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
    groupModel.SetFooter(std::move(footer));
    EXPECT_EQ(groupNode->GetTotalChildCount(), 2);
    // pop frameNode
    CreateDone();
}

/*
 * @tc.name: ListItemGroupOffsetTest001
 * @tc.desc: Test the scroll offset for ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListItemGroupOffsetTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItemGroup with header, second group header is at bottom edge.
     * @tc.expected: current offset is 370
     */
    auto model = CreateList();
    model.SetInitialIndex(1);
    CreateGroupWithHeader(4, V2::ListItemGroupStyle::NONE, 3);
    CreateDone();
    EXPECT_EQ(pattern_->currentOffset_, 370);

    /**
     * @tc.steps: step2. Scroll -50px, first group load 1 item.
     * @tc.expected: current offset is 320
     */
    pattern_->UpdateCurrentOffset(50, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, 320);

    /**
     * @tc.steps: step3. Scroll 445px, 3th group head at top edge.
     * @tc.expected: current offset is 765, group0 and group1 layoutAlgorithm_ is nullptr.
     */
    pattern_->UpdateCurrentOffset(-445, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, 765);
    auto group0 = GetChildFrameNode(frameNode_, 0);
    EXPECT_EQ(group0->layoutAlgorithm_, nullptr);
    auto group1 = GetChildFrameNode(frameNode_, 1);
    EXPECT_EQ(group1->layoutAlgorithm_, nullptr);
}

/**
 * @tc.name: ParseResObjDividerStrokeWidth001
 * @tc.desc: Test ParseResObjDividerStrokeWidth in ListItemGroupModelNG
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ParseResObjDividerStrokeWidth001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    ListItemGroupModelNG groupModel = CreateListItemGroup();
    RefPtr<UINode> listItemGroupNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto listItemGroup = AceType::DynamicCast<FrameNode>(listItemGroupNode);
    ASSERT_NE(listItemGroup, nullptr);
    auto listItemGroupPattern = listItemGroup->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(listItemGroupPattern, nullptr);
    ASSERT_EQ(listItemGroupPattern->resourceMgr_, nullptr);

    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    groupModel.ParseResObjDividerStrokeWidth(invalidResObj);
    ASSERT_NE(listItemGroupPattern->resourceMgr_, nullptr);
    EXPECT_NE(listItemGroupPattern->resourceMgr_->resMap_.size(), 0);

    V2::ItemDivider divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    divider.strokeWidth = 1000.0_vp;
    listItemGroupPattern->resourceMgr_->ReloadResources();
    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    EXPECT_NE(divider.strokeWidth, 1000.0_vp);

    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(0, static_cast<int32_t>(ResourceType::INTEGER), params, "", "", 0);
    groupModel.ParseResObjDividerStrokeWidth(resObj);
    ASSERT_NE(listItemGroupPattern->resourceMgr_, nullptr);
    EXPECT_NE(listItemGroupPattern->resourceMgr_->resMap_.size(), 0);

    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    divider.strokeWidth = 1000.0_vp;
    listItemGroupPattern->resourceMgr_->ReloadResources();
    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    EXPECT_NE(divider.strokeWidth, 1000.0_vp);
}

/**
 * @tc.name: ParseResObjDividerStrokeWidth002
 * @tc.desc: Test ParseResObjDividerStrokeWidth in ListItemGroupModelNG
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ParseResObjDividerStrokeWidth002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    ListItemGroupModelNG groupModel = CreateListItemGroup();
    RefPtr<UINode> listItemGroupNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto listItemGroup = AceType::DynamicCast<FrameNode>(listItemGroupNode);
    ASSERT_NE(listItemGroup, nullptr);
    auto listItemGroupPattern = listItemGroup->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(listItemGroupPattern, nullptr);
    ASSERT_EQ(listItemGroupPattern->resourceMgr_, nullptr);

    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    ListItemGroupModelNG::ParseResObjDividerStrokeWidth(AceType::RawPtr(listItemGroup), invalidResObj);
    ASSERT_NE(listItemGroupPattern->resourceMgr_, nullptr);
    EXPECT_NE(listItemGroupPattern->resourceMgr_->resMap_.size(), 0);

    V2::ItemDivider divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    divider.strokeWidth = 1000.0_vp;
    listItemGroupPattern->resourceMgr_->ReloadResources();
    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    EXPECT_NE(divider.strokeWidth, 1000.0_vp);

    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(0, static_cast<int32_t>(ResourceType::INTEGER), params, "", "", 0);
    ListItemGroupModelNG::ParseResObjDividerStrokeWidth(AceType::RawPtr(listItemGroup), resObj);
    ASSERT_NE(listItemGroupPattern->resourceMgr_, nullptr);
    EXPECT_NE(listItemGroupPattern->resourceMgr_->resMap_.size(), 0);

    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    divider.strokeWidth = 1000.0_vp;
    listItemGroupPattern->resourceMgr_->ReloadResources();
    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    EXPECT_NE(divider.strokeWidth, 1000.0_vp);
}

/**
 * @tc.name: ParseResObjDividerColor001
 * @tc.desc: Test ParseResObjDividerColor in ListItemGroupModelNG
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ParseResObjDividerColor001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    ListItemGroupModelNG groupModel = CreateListItemGroup();
    RefPtr<UINode> listItemGroupNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto listItemGroup = AceType::DynamicCast<FrameNode>(listItemGroupNode);
    ASSERT_NE(listItemGroup, nullptr);
    auto listItemGroupPattern = listItemGroup->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(listItemGroupPattern, nullptr);
    ASSERT_EQ(listItemGroupPattern->resourceMgr_, nullptr);

    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    groupModel.ParseResObjDividerColor(invalidResObj);
    ASSERT_NE(listItemGroupPattern->resourceMgr_, nullptr);
    EXPECT_NE(listItemGroupPattern->resourceMgr_->resMap_.size(), 0);

    V2::ItemDivider divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    divider.color = Color::BLUE;
    listItemGroupPattern->resourceMgr_->ReloadResources();
    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    EXPECT_NE(divider.color, Color::BLUE);

    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(0, static_cast<int32_t>(ResourceType::INTEGER), params, "", "", 0);
    groupModel.ParseResObjDividerColor(resObj);
    ASSERT_NE(listItemGroupPattern->resourceMgr_, nullptr);
    EXPECT_NE(listItemGroupPattern->resourceMgr_->resMap_.size(), 0);

    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    divider.color = Color::BLUE;
    listItemGroupPattern->resourceMgr_->ReloadResources();
    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    EXPECT_NE(divider.color, Color::BLUE);
}

/**
 * @tc.name: ParseResObjDividerColor002
 * @tc.desc: Test ParseResObjDividerColor in ListItemGroupModelNG
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ParseResObjDividerColor002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    ListItemGroupModelNG groupModel = CreateListItemGroup();
    RefPtr<UINode> listItemGroupNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto listItemGroup = AceType::DynamicCast<FrameNode>(listItemGroupNode);
    ASSERT_NE(listItemGroup, nullptr);
    auto listItemGroupPattern = listItemGroup->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(listItemGroupPattern, nullptr);
    ASSERT_EQ(listItemGroupPattern->resourceMgr_, nullptr);

    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    ListItemGroupModelNG::ParseResObjDividerColor(AceType::RawPtr(listItemGroup), invalidResObj);
    ASSERT_NE(listItemGroupPattern->resourceMgr_, nullptr);
    EXPECT_NE(listItemGroupPattern->resourceMgr_->resMap_.size(), 0);

    V2::ItemDivider divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    divider.color = Color::BLUE;
    listItemGroupPattern->resourceMgr_->ReloadResources();
    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    EXPECT_NE(divider.color, Color::BLUE);

    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(0, static_cast<int32_t>(ResourceType::INTEGER), params, "", "", 0);
    ListItemGroupModelNG::ParseResObjDividerColor(AceType::RawPtr(listItemGroup), resObj);
    ASSERT_NE(listItemGroupPattern->resourceMgr_, nullptr);
    EXPECT_NE(listItemGroupPattern->resourceMgr_->resMap_.size(), 0);

    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    divider.color = Color::BLUE;
    listItemGroupPattern->resourceMgr_->ReloadResources();
    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    EXPECT_NE(divider.color, Color::BLUE);
}

/**
 * @tc.name: ParseResObjDividerStartMargin001
 * @tc.desc: Test ParseResObjDividerStartMargin in ListItemGroupModelNG
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ParseResObjDividerStartMargin001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    ListItemGroupModelNG groupModel = CreateListItemGroup();
    RefPtr<UINode> listItemGroupNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto listItemGroup = AceType::DynamicCast<FrameNode>(listItemGroupNode);
    ASSERT_NE(listItemGroup, nullptr);
    auto listItemGroupPattern = listItemGroup->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(listItemGroupPattern, nullptr);
    ASSERT_EQ(listItemGroupPattern->resourceMgr_, nullptr);

    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    groupModel.ParseResObjDividerStartMargin(invalidResObj);
    ASSERT_NE(listItemGroupPattern->resourceMgr_, nullptr);
    EXPECT_NE(listItemGroupPattern->resourceMgr_->resMap_.size(), 0);

    V2::ItemDivider divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    divider.startMargin = 1000.0_vp;
    listItemGroupPattern->resourceMgr_->ReloadResources();
    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    EXPECT_NE(divider.startMargin, 1000.0_vp);

    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(0, static_cast<int32_t>(ResourceType::INTEGER), params, "", "", 0);
    groupModel.ParseResObjDividerStartMargin(resObj);
    ASSERT_NE(listItemGroupPattern->resourceMgr_, nullptr);
    EXPECT_NE(listItemGroupPattern->resourceMgr_->resMap_.size(), 0);

    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    divider.startMargin = 1000.0_vp;
    listItemGroupPattern->resourceMgr_->ReloadResources();
    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    EXPECT_NE(divider.startMargin, 1000.0_vp);
}

/**
 * @tc.name: ParseResObjDividerStartMargin002
 * @tc.desc: Test ParseResObjDividerStartMargin in ListItemGroupModelNG
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ParseResObjDividerStartMargin002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    ListItemGroupModelNG groupModel = CreateListItemGroup();
    RefPtr<UINode> listItemGroupNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto listItemGroup = AceType::DynamicCast<FrameNode>(listItemGroupNode);
    ASSERT_NE(listItemGroup, nullptr);
    auto listItemGroupPattern = listItemGroup->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(listItemGroupPattern, nullptr);
    ASSERT_EQ(listItemGroupPattern->resourceMgr_, nullptr);

    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    ListItemGroupModelNG::ParseResObjDividerStartMargin(AceType::RawPtr(listItemGroup), invalidResObj);
    ASSERT_NE(listItemGroupPattern->resourceMgr_, nullptr);
    EXPECT_NE(listItemGroupPattern->resourceMgr_->resMap_.size(), 0);

    V2::ItemDivider divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    divider.startMargin = 1000.0_vp;
    listItemGroupPattern->resourceMgr_->ReloadResources();
    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    EXPECT_NE(divider.startMargin, 1000.0_vp);

    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(0, static_cast<int32_t>(ResourceType::INTEGER), params, "", "", 0);
    ListItemGroupModelNG::ParseResObjDividerStartMargin(AceType::RawPtr(listItemGroup), resObj);
    ASSERT_NE(listItemGroupPattern->resourceMgr_, nullptr);
    EXPECT_NE(listItemGroupPattern->resourceMgr_->resMap_.size(), 0);

    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    divider.startMargin = 1000.0_vp;
    listItemGroupPattern->resourceMgr_->ReloadResources();
    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    EXPECT_NE(divider.startMargin, 1000.0_vp);
}

/**
 * @tc.name: ParseResObjDividerEndMargin001
 * @tc.desc: Test ParseResObjDividerEndMargin in ListItemGroupModelNG
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ParseResObjDividerEndMargin001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    ListItemGroupModelNG groupModel = CreateListItemGroup();
    RefPtr<UINode> listItemGroupNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto listItemGroup = AceType::DynamicCast<FrameNode>(listItemGroupNode);
    ASSERT_NE(listItemGroup, nullptr);
    auto listItemGroupPattern = listItemGroup->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(listItemGroupPattern, nullptr);
    ASSERT_EQ(listItemGroupPattern->resourceMgr_, nullptr);

    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    groupModel.ParseResObjDividerEndMargin(invalidResObj);
    ASSERT_NE(listItemGroupPattern->resourceMgr_, nullptr);
    EXPECT_NE(listItemGroupPattern->resourceMgr_->resMap_.size(), 0);

    V2::ItemDivider divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    divider.endMargin = 1000.0_vp;
    listItemGroupPattern->resourceMgr_->ReloadResources();
    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    EXPECT_NE(divider.endMargin, 1000.0_vp);

    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(0, static_cast<int32_t>(ResourceType::INTEGER), params, "", "", 0);
    groupModel.ParseResObjDividerEndMargin(resObj);
    ASSERT_NE(listItemGroupPattern->resourceMgr_, nullptr);
    EXPECT_NE(listItemGroupPattern->resourceMgr_->resMap_.size(), 0);

    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    divider.endMargin = 1000.0_vp;
    listItemGroupPattern->resourceMgr_->ReloadResources();
    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    EXPECT_NE(divider.endMargin, 1000.0_vp);
}

/**
 * @tc.name: ParseResObjDividerEndMargin002
 * @tc.desc: Test ParseResObjDividerEndMargin in ListItemGroupModelNG
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ParseResObjDividerEndMargin002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    ListItemGroupModelNG groupModel = CreateListItemGroup();
    RefPtr<UINode> listItemGroupNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto listItemGroup = AceType::DynamicCast<FrameNode>(listItemGroupNode);
    ASSERT_NE(listItemGroup, nullptr);
    auto listItemGroupPattern = listItemGroup->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(listItemGroupPattern, nullptr);
    ASSERT_EQ(listItemGroupPattern->resourceMgr_, nullptr);

    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    ListItemGroupModelNG::ParseResObjDividerEndMargin(AceType::RawPtr(listItemGroup), invalidResObj);
    ASSERT_NE(listItemGroupPattern->resourceMgr_, nullptr);
    EXPECT_NE(listItemGroupPattern->resourceMgr_->resMap_.size(), 0);

    V2::ItemDivider divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    divider.endMargin = 1000.0_vp;
    listItemGroupPattern->resourceMgr_->ReloadResources();
    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    EXPECT_NE(divider.endMargin, 1000.0_vp);

    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(0, static_cast<int32_t>(ResourceType::INTEGER), params, "", "", 0);
    ListItemGroupModelNG::ParseResObjDividerEndMargin(AceType::RawPtr(listItemGroup), resObj);
    ASSERT_NE(listItemGroupPattern->resourceMgr_, nullptr);
    EXPECT_NE(listItemGroupPattern->resourceMgr_->resMap_.size(), 0);

    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    divider.endMargin = 1000.0_vp;
    listItemGroupPattern->resourceMgr_->ReloadResources();
    divider = ListItemGroupModelNG::GetDivider(AceType::RawPtr(listItemGroup));
    EXPECT_NE(divider.endMargin, 1000.0_vp);
}
} // namespace OHOS::Ace::NG
