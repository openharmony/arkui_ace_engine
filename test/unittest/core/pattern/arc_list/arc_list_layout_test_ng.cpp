/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "arc_list_test_ng.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class ArcListLayoutTestNg : public ArcListTestNg {
public:
    void UpdateContentModifier();
    RefPtr<ListPaintMethod> UpdateOverlayModifier();
    AssertionResult VerifySticky(int32_t groupIndex, bool isHeader, float expectOffsetY);
    void UpdateDividerMap();
};

void ArcListLayoutTestNg::UpdateContentModifier()
{
    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    listPaint->UpdateContentModifier(AceType::RawPtr(paintWrapper));
}

RefPtr<ListPaintMethod> ArcListLayoutTestNg::UpdateOverlayModifier()
{
    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    listPaint->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    return listPaint;
}

AssertionResult ArcListLayoutTestNg::VerifySticky(int32_t groupIndex, bool isHeader, float expectOffsetY)
{
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, groupIndex);
    float offsetY = isHeader ? GetChildRect(groupNode, 0).GetY() : GetChildRect(groupNode, 1).GetY();
    // because has header height, the footer under header
    if (!isHeader && expectOffsetY < GROUP_HEADER_LEN) {
        expectOffsetY = GROUP_HEADER_LEN;
    }
    return IsEqual(offsetY, expectOffsetY);
}

void ArcListLayoutTestNg::UpdateDividerMap()
{
    int cur = 0;
    for (auto& child : pattern_->itemPosition_) {
        child.second.id += cur;
        cur++;
    }
    UpdateContentModifier();
}

/**
 * @tc.name: PaintMethod003
 * @tc.desc: Test Arc_list paint method about UpdateOverlayModifier
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, PaintMethod003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DisplayMode ON
     * @tc.expected: The displayMode is ON, has scrollbar and on the right
     */
    ListModelNG model = CreateList();
    model.SetScrollBar(DisplayMode::ON);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    RefPtr<ListPaintMethod> paint = UpdateOverlayModifier();
    auto scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    auto scrollBar = paint->scrollBar_.Upgrade();
    ASSERT_NE(scrollBar, nullptr);
    EXPECT_EQ(scrollBar->displayMode_, DisplayMode::ON);
    EXPECT_FALSE(scrollBar->NeedPaint());

    /**
     * @tc.steps: step2. Update axis
     * @tc.expected: The scrollbar and on the bottom
     */
    layoutProperty_->UpdateListDirection(Axis::HORIZONTAL);
    pattern_->OnModifyDone();
    FlushLayoutTask(frameNode_);
    paint = UpdateOverlayModifier();
    scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    scrollBar = paint->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);
    EXPECT_TRUE(scrollBar->NeedPaint());

    /**
     * @tc.steps: step3. Set DisplayMode::OFF
     * @tc.expected: Has no scrollbar
     */
    model = CreateList();
    model.SetScrollBar(DisplayMode::OFF);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    paint = UpdateOverlayModifier();
    scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    scrollBar = paint->scrollBar_.Upgrade();
    EXPECT_EQ(scrollBar, nullptr);

    /**
     * @tc.steps: step4. Set DisplayMode::ON
     * @tc.expected: Has scrollbar and on the right
     */
    ClearOldNodes();
    model = CreateList();
    model.SetScrollBar(DisplayMode::ON);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    paint = UpdateOverlayModifier();
    scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    scrollBar = paint->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);
    EXPECT_FALSE(scrollBar->NeedPaint());

    /**
     * @tc.steps: step5. Has no item
     * @tc.expected: UnScrollable, has no scrollbar
     */
    ClearOldNodes();
    model = CreateList();
    model.SetScrollBar(DisplayMode::ON);
    CreateDone();
    paint = UpdateOverlayModifier();
    scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    scrollBar = paint->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);
    EXPECT_FALSE(scrollBar->NeedPaint());
}

/**
 * @tc.name: Pattern007
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, Pattern007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When has ListItem, position not at any ListItem
     * @tc.expected: Would return the last itemIndex
     */
    CreateList();
    CreateListItems(VIEW_ITEM_NUMBER);
    CreateDone();
    const Point point = Point(0, 1000.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, 0);
}

/**
 * @tc.name: Pattern008
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, Pattern008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When has no ListItem, call GetItemIndexByPosition
     * @tc.expected: Would return 0
     */
    CreateList();
    CreateDone();
    const Point point = Point(0, 1000.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, 0);
}

/**
 * @tc.name: Pattern010
 * @tc.desc: Test layout
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, Pattern010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. do not set selfIdealSize, 0 listItem
     */
    CreateList();
    ViewAbstract::SetWidth(CalcLength(LIST_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    CreateDone();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 0);

    /**
     * @tc.steps: step1. do not set selfIdealSize, TOTAL_ITEM_NUMBER listItem
     */
    CreateList();
    ViewAbstract::SetWidth(CalcLength(LIST_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 0);

    /**
     * @tc.steps: step1. set width Infinity
     */
    CreateList();
    ViewAbstract::SetWidth(CalcLength(Infinity<float>()));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 0);

    /**
     * @tc.steps: step1. set width Infinity, but no item
     */
    ClearOldNodes();
    CreateList();
    ViewAbstract::SetWidth(CalcLength(Infinity<float>()));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    CreateDone();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 0);
}

/**
 * @tc.name: ListItemCreateForCardModeTest001
 * @tc.desc: Test the initialization of listItem in card mode.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, ListItemCreateForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create ArcListItem in card mode.
     * @tc.expected: step2. create a card style ArcListItem success.
     */
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<ArcListItemPattern>();
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(pattern->GetListItemStyle(), V2::ListItemStyle::CARD);

    /**
     * @tc.steps: step3. compare the obtained value with the set value.
     * @tc.expected: step3. the obtained value is equal to the set value.
     */
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::WHITE);
}

/**
 * @tc.name: ListItemHoverEventForCardModeTest001
 * @tc.desc: Test the hover event when the hover status of card mode listItem is true.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, ListItemHoverEventForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create ArcListItem in card mode.
     * @tc.expected: step2. create a card style ArcListItem success.
     */
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. call function HandleHoverEvent and Set hover status to true.
     * @tc.expected: step3. the hover status is true.
     */
    pattern->HandleHoverEvent(true, frameNode);
    EXPECT_TRUE(pattern->isHover_);

    /**
     * @tc.steps: step3. call function HandleHoverEvent and Set hover status to false.
     * @tc.expected: step3. the hover status is false.
     */
    pattern->HandleHoverEvent(false, frameNode);
    EXPECT_FALSE(pattern->isHover_);
}

/**
 * @tc.name: ListItemPressEventForCardModeTest001
 * @tc.desc: Test the press event when the TouchType is DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, ListItemPressEventForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create ArcListItem in card mode.
     * @tc.expected: step2. create a card style ArcListItem success.
     */
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<ArcListItemPattern>();

    /**
     * @tc.steps: step3. call function HandlePressEvent, set TouchType to DOWN and set hover status is true.
     * @tc.expected: step3. the color is different from the initial color when the listItem is pressed with the mouse.
     */
    pattern->isHover_ = true;
    pattern->HandlePressEvent(true, frameNode);
    EXPECT_TRUE(pattern->isPressed_);

    /**
     * @tc.steps: step4. call function HandlePressEvent, set TouchType to DOWN and set hover status is false.
     * @tc.expected: step4. the color is different from the initial color when the listItem is pressed with gesture.
     */
    pattern->isHover_ = false;
    pattern->HandlePressEvent(true, frameNode);
    EXPECT_TRUE(pattern->isPressed_);

    /**
     * @tc.steps: step5. call function HandlePressEvent, set TouchType to UP and set hover status is true.
     * @tc.expected: step5. the color differs from the initial color when mouse hovers over listItem after pressing.
     */
    pattern->isHover_ = true;
    pattern->HandlePressEvent(false, frameNode);
    EXPECT_FALSE(pattern->isPressed_);

    /**
     * @tc.steps: step6. call function HandlePressEvent, set TouchType to UP and set hover status is false.
     * @tc.expected: step6. the color returns to its original color after pressing on listItem through gestures.
     */
    pattern->isHover_ = false;
    pattern->HandlePressEvent(false, frameNode);
    EXPECT_FALSE(pattern->isPressed_);
}

/**
 * @tc.name: ListLayout_SafeArea001
 * @tc.desc: Test arc_list layout with expandSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, ListLayout_SafeArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List.
     */
    ListModelNG model = CreateList();
    model.SetInitialIndex(1);
    CreateListItems(TOTAL_ITEM_NUMBER * 2);
    CreateDone();
    layoutProperty_->UpdateSafeAreaExpandOpts({ .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_ALL });
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->contentEndOffset_, 0);
    EXPECT_TRUE(IsEqual(frameNode_->geometryNode_->GetFrameSize(), SizeF(LIST_WIDTH, LIST_HEIGHT)));
}

/**
 * @tc.name: ListLayout_SafeArea002
 * @tc.desc: Test arc_list layout with expandSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, ListLayout_SafeArea002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List.
     */
    ListModelNG model = CreateList();
    model.SetInitialIndex(1);
    CreateListItems(TOTAL_ITEM_NUMBER * 2);
    CreateDone();
    layoutProperty_->UpdateSafeAreaExpandOpts({ .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_TOP });
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->contentEndOffset_, 0);
    EXPECT_TRUE(IsEqual(frameNode_->geometryNode_->GetFrameSize(), SizeF(LIST_WIDTH, LIST_HEIGHT)));
}

/**
 * @tc.name: ChildrenMainSize005
 * @tc.desc: Test childrenMainSize layout
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, ChildrenMainSize005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list
     */
    ListModelNG model = CreateList();
    auto childrenSize = model.GetOrCreateListChildrenMainSize();
    childrenSize->UpdateDefaultSize(0);
    childrenSize->ChangeData(0, 2, { 100.f, 100.f });
    childrenSize->ChangeData(4, 1, { 200.f });
    childrenSize->ChangeData(5, 8, { 100.f, 100.f, 100.f, 100.f, 100.f, 100.f, 100.f, 100.f });
    CreateListItems(2);
    CreateItemWithSize(2, SizeT<Dimension>(FILL_LENGTH, Dimension(0.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.f)));
    CreateListItems(8);
    CreateDone();
    EXPECT_FALSE(ScrollToIndex(1, false, ScrollAlign::CENTER, -50.f));
    EXPECT_TRUE(ScrollToIndex(2, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(3, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(4, false, ScrollAlign::CENTER, 100.f));
}

/**
 * @tc.name: ChildrenMainSize006
 * @tc.desc: Test childrenMainSize layout
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, ChildrenMainSize006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list
     */
    ListModelNG model = CreateList();
    auto childrenSize = model.GetOrCreateListChildrenMainSize();
    childrenSize->UpdateDefaultSize(ITEM_HEIGHT);
    childrenSize->ChangeData(2, 2, { -100.f, 200.f });
    CreateListItems(2);
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(-100.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.f)));
    CreateListItems(8);
    CreateDone();
    EXPECT_FALSE(ScrollToIndex(3, false, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(4, false, ScrollAlign::CENTER, 150.f));

    /**
     * @tc.steps: step2. insert data
     */
    ClearOldNodes();
    model = CreateList();
    childrenSize = model.GetOrCreateListChildrenMainSize();
    childrenSize->UpdateDefaultSize(ITEM_HEIGHT);
    childrenSize->ChangeData(8, 0, { 50.f, 200.f });
    CreateListItems(8);
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(50.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.f)));
    CreateDone();
    EXPECT_EQ(pattern_->childrenSize_->childrenSize_.size(), 10);
    EXPECT_FALSE(ScrollToIndex(8, false, ScrollAlign::END, 225.f));
    EXPECT_FALSE(ScrollToIndex(9, false, ScrollAlign::END, 250.f));
}

/**
 * @tc.name: GetNearScale001
 * @tc.desc: Test GetNearScale layout algorithm
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, GetNearScale001, TestSize.Level1)
{
    ArcListLayoutAlgorithm algorithm(200, 100);
    EXPECT_FALSE(NearEqual(algorithm.GetNearScale(150.0), 0.780000));
    EXPECT_FALSE(NearEqual(algorithm.GetNearScale(-135.0), 0.820000));
    EXPECT_TRUE(NearEqual(algorithm.GetNearScale(141.0), 0.780000));
    EXPECT_TRUE(NearEqual(algorithm.GetNearScale(-132.0), 0.820000));
    EXPECT_TRUE(NearEqual(algorithm.GetNearScale(120.0), 0.871304));
    EXPECT_TRUE(NearEqual(algorithm.GetNearScale(95.0), 0.966250));
    EXPECT_TRUE(NearEqual(algorithm.GetNearScale(10.0), 1.077872));
    EXPECT_TRUE(NearEqual(algorithm.GetNearScale(-10.0), 1.077826));
}

/**
 * @tc.name: UpdatePosMap001
 * @tc.desc: Test class ArcListPositionMap interface UpdatePosMap
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, UpdatePosMap001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    RefPtr<ListPositionMap> posMap = AceType::MakeRefPtr<ArcListPositionMap>(0);

    ListChangeFlag flag = LIST_UPDATE_HEADER_FOOTER;
    posMap->MarkDirty(flag);

    float spaceWidth = 10.f;
    std::vector<float> mainSize = {10, 20, 30};
    float defaultSize;
    RefPtr<ListChildrenMainSize> childrenSize_ = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, defaultSize);
    posMap->UpdatePosMap(frameNode_.GetRawPtr(), 2, spaceWidth, childrenSize_);

    EXPECT_EQ(posMap->GetTotalHeight(), 70.f);
}

/**
 * @tc.name: FixPredictSnapOffset001
 * @tc.desc: Test ArcListLayoutAlgorithm::SetPredictSnapOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, FixPredictSnapOffset001, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    // For check FixPredictSnapOffset switch cover, in this case predictSnapEndPos_ is not set.
    pattern_->SetPredictSnapOffset(100.0);
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_TRUE(NearEqual(listLayoutAlgorithm->GetPredictSnapEndPosition().value_or(-0.001), -0.001));
}

/**
 * @tc.name: FixPredictSnapOffset002
 * @tc.desc: Test ArcListLayoutAlgorithm::SetPredictSnapOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, FixPredictSnapOffset002, TestSize.Level1)
{
    // Set item different hight.
    std::vector<SizeT<Dimension>> itemSizes;
    itemSizes.emplace_back(SizeT<Dimension>(FILL_LENGTH, Dimension(30.f)));
    itemSizes.emplace_back(SizeT<Dimension>(FILL_LENGTH, Dimension(40.f)));
    itemSizes.emplace_back(SizeT<Dimension>(FILL_LENGTH, Dimension(50.f)));

    ListModelNG model = CreateList();
    CreateListItemsWithSize(itemSizes);
    CreateDone();

    pattern_->SetPredictSnapOffset(100.0);
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    // Before scroll, call SetPredictSnapOffset to set value.
    listLayoutAlgorithm->SetPredictSnapOffset(100.0);
    ScrollTo(200);
    EXPECT_EQ(pattern_->GetTotalOffset(), -105);
}

/**
 * @tc.name: OnItemPositionAddOrUpdate001
 * @tc.desc: Test ArcListLayoutAlgorithm::OnItemPositionAddOrUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, OnItemPositionAddOrUpdate001, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    pattern_->SetPredictSnapOffset(100.0);
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());

    // Before scroll, call SetPredictSnapOffset to set value.
    listLayoutAlgorithm->SetPredictSnapOffset(100.0);
    uint32_t index = 0;
    // For check OnItemPositionAddOrUpdate switch cover, in this case predictSnapEndPos_ is not set.
    listLayoutAlgorithm->OnItemPositionAddOrUpdate(frameNode_.GetRawPtr(), index);
    EXPECT_TRUE(NearEqual(listLayoutAlgorithm->GetPredictSnapEndPosition().value_or(-0.001), -0.001));
}

/**
 * @tc.name: OnItemPositionAddOrUpdate002
 * @tc.desc: Test ArcListLayoutAlgorithm::OnItemPositionAddOrUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, OnItemPositionAddOrUpdate002, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    pattern_->SetPredictSnapOffset(100.0);
    // Call SetPredictSnapOffset twice to cover more switch(the init value check switch).
    pattern_->SetPredictSnapOffset(100.0);

    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());

    // Before scroll, call SetPredictSnapOffset to set value.
    listLayoutAlgorithm->SetPredictSnapOffset(100.0);
    listLayoutAlgorithm->SetPredictSnapEndPosition(200.0);

    for (uint32_t index = 0; index < count; ++index) {
        // For check OnItemPositionAddOrUpdate switch cover, in this case predictSnapEndPos_ is set.
        listLayoutAlgorithm->OnItemPositionAddOrUpdate(frameNode_.GetRawPtr(), index);
        EXPECT_FALSE(NearEqual(listLayoutAlgorithm->GetPredictSnapEndPosition().value_or(-0.001), -0.001));
    }
}

/**
 * @tc.name: MeasureList001
 * @tc.desc: Test ArcListLayoutAlgorithm::MeasureList
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, MeasureList001, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    pattern_->SetPredictSnapOffset(100.0);
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());

    // For check MeasureList switch cover, in this case targetIndexStaged_ is not set.
    listLayoutAlgorithm->SetPredictSnapOffset(100.0);
    listLayoutAlgorithm->SetPredictSnapEndPosition(200.0);

    listLayoutAlgorithm->SetTargetIndex(1);
    listLayoutAlgorithm->MeasureList(frameNode_.GetRawPtr());

    EXPECT_TRUE(NearEqual(listLayoutAlgorithm->GetTargetIndex().value_or(-99), -99));
}
} // namespace OHOS::Ace::NG
