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
#include "gtest/gtest.h"

#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"
#include "core/components_v2/inspector/inspector_constants.h"

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
    FlushUITasks(frameNode_);
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
    FlushUITasks(frameNode_);
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
    FlushUITasks(frameNode_);
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
    EXPECT_TRUE(NearEqual(algorithm.GetNearScale(141.0), 0.832255));
    EXPECT_TRUE(NearEqual(algorithm.GetNearScale(-132.0), 0.856995));
    EXPECT_TRUE(NearEqual(algorithm.GetNearScale(120.0), 0.889020));
    EXPECT_TRUE(NearEqual(algorithm.GetNearScale(95.0), 0.950898));
    EXPECT_TRUE(NearEqual(algorithm.GetNearScale(10.0), 1.077197));
    EXPECT_TRUE(NearEqual(algorithm.GetNearScale(-10.0), 1.077197));
}

/**
 * @tc.name: GetNearScale002
 * @tc.desc: Test GetNearScale when the height of the item is large
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, GetNearScale002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list with a large height of one of the items in the list.
     */
    ListModelNG model = CreateList();
    CreateListItems(1);
    CreateListItemsWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(1000.f)));
    CreateListItems(1);
    CreateDone();
    auto maxScale = 1.08f;
    auto minScale = 0.406643271f;

    /**
     * @tc.steps: step2. Flush ui task.
     * @tc.expected: The distance between the item and the middle point of the list does not reach the threshold.
     * Therefore, the scale is minimum.
     */
    FlushUITasks(frameNode_);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 250.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, 1250.0f);
    EXPECT_TRUE(NearEqual(pattern_->itemPosition_[1].scale, minScale));

    /**
     * @tc.steps: step3. Scroll to 50.
     * @tc.expected: The distance does not reach the threshold. Therefore, the scale remains unchanged.
     */
    ScrollTo(50);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 50.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, 1050.0f);
    EXPECT_TRUE(NearEqual(pattern_->itemPosition_[1].scale, minScale));

    /**
     * @tc.steps: step4. Scroll to 100.
     * @tc.expected: The distance reach the threshold. Therefore, the scale changed.
     */
    ScrollTo(100);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, 1000.0f);
    EXPECT_TRUE(GreatNotEqual(pattern_->itemPosition_[1].scale, minScale));
    EXPECT_TRUE(LessNotEqual(pattern_->itemPosition_[1].scale, maxScale));

    /**
     * @tc.steps: step5. Scroll to 400.
     * @tc.expected: The distance is 0. Therefore, the scale reaches the maximum value.
     */
    ScrollTo(400);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -300.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, 700.0f);
    EXPECT_TRUE(NearEqual(pattern_->itemPosition_[1].scale, maxScale));

    /**
     * @tc.steps: step6. Scroll to 700.
     * @tc.expected: The distance reach the threshold. Therefore, the scale changed.
     */
    ScrollTo(700);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -600.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, 400.0f);
    EXPECT_TRUE(GreatNotEqual(pattern_->itemPosition_[1].scale, minScale));
    EXPECT_TRUE(LessNotEqual(pattern_->itemPosition_[1].scale, maxScale));

    /**
     * @tc.steps: step7. Scroll to 750.
     * @tc.expected: The distance does not reach the threshold. Therefore, the scale reaches the minimum value.
     */
    ScrollTo(750);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -650.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, 350.0f);
    EXPECT_TRUE(NearEqual(pattern_->itemPosition_[1].scale, minScale));

    /**
     * @tc.steps: step8. Scroll to 800.
     * @tc.expected: The distance does not reach the threshold. Therefore, the scale remains unchanged.
     */
    ScrollTo(800);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -700.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, 300.0f);
    EXPECT_TRUE(NearEqual(pattern_->itemPosition_[1].scale, minScale));
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
    posMap->UpdatePosMap(Referenced::RawPtr(frameNode_), 2, spaceWidth, childrenSize_);

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
    listLayoutAlgorithm->MeasureList(Referenced::RawPtr(frameNode_));

    EXPECT_TRUE(NearEqual(listLayoutAlgorithm->GetTargetIndex().value_or(-99), -99));
}

/**
 * @tc.name: FixPredictSnapPos001
 * @tc.desc: Test ArcListLayoutAlgorithm::FixPredictSnapPos
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, FixPredictSnapPos001, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    // For check FixPredictSnapOffset switch cover, in this case predictSnapEndPos_ is not set.
    pattern_->SetPredictSnapOffset(100.0);
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(listLayoutAlgorithm, nullptr);
    listLayoutAlgorithm->FixPredictSnapPos();
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->predictSnapOffset_, 100.0);
}

/**
 * @tc.name: FixPredictSnapPos002
 * @tc.desc: Test ArcListLayoutAlgorithm::FixPredictSnapPos
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, FixPredictSnapPos002, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    pattern_->SetPredictSnapOffset(100.0);
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(listLayoutAlgorithm, nullptr);
    // For check MeasureList switch cover, in this case targetIndexStaged_ is not set.
    listLayoutAlgorithm->SetPredictSnapOffset(100.0);
    listLayoutAlgorithm->SetPredictSnapEndPosition(200.0);
    listLayoutAlgorithm->FixPredictSnapPos();
    listLayoutAlgorithm->headerIndex_ = 0;
    listLayoutAlgorithm->SetTargetIndex(1);
    listLayoutAlgorithm->MeasureList(Referenced::RawPtr(frameNode_));
    EXPECT_TRUE(NearEqual(listLayoutAlgorithm->GetTargetIndex().value_or(-99), -99));
}

/**
 * @tc.name: FixPredictSnapOffsetAlignCenter001
 * @tc.desc: Test ArcListLayoutAlgorithm::FixPredictSnapOffsetAlignCenter
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, FixPredictSnapOffsetAlignCenter001, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    pattern_->SetPredictSnapOffset(100.0);
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(listLayoutAlgorithm, nullptr);
    listLayoutAlgorithm->SetItemInfo(0, { 0, 1.0, 2.0, true });
    listLayoutAlgorithm->FixPredictSnapOffsetAlignCenter();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0.0f);
}

/**
 * @tc.name: FixPredictSnapOffsetAlignCenter002
 * @tc.desc: Test ArcListLayoutAlgorithm::FixPredictSnapOffsetAlignCenter
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, FixPredictSnapOffsetAlignCenter002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List with ScrollSnapAlign::END
     * @tc.expected: not contentStartOffset
     */
    ListModelNG model = CreateList();
    // Make ListHeight not an integer multiple of ListItems
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT - DEVIATION_HEIGHT));
    model.SetScrollSnapAlign(ScrollSnapAlign::END);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0.0f);
}

/**
 * @tc.name: FixPredictSnapOffsetAlignCenter003
 * @tc.desc: Test ArcListLayoutAlgorithm::FixPredictSnapOffsetAlignCenter
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, FixPredictSnapOffsetAlignCenter003, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    pattern_->SetPredictSnapOffset(100.0);
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(listLayoutAlgorithm, nullptr);
    listLayoutAlgorithm->SetItemInfo(0, { 0, 1.0, 200.0, true });
    listLayoutAlgorithm->totalOffset_ = 1000.0;
    listLayoutAlgorithm->FixPredictSnapOffsetAlignCenter();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0.0f);
}

/**
 * @tc.name: FixPredictSnapOffsetAlignCenter004
 * @tc.desc: Test ArcListLayoutAlgorithm::FixPredictSnapOffsetAlignCenter
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, FixPredictSnapOffsetAlignCenter004, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    pattern_->SetPredictSnapOffset(100.0);
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(listLayoutAlgorithm, nullptr);
    listLayoutAlgorithm->SetItemInfo(0, { 0, 1.f, 2.f, true });
    listLayoutAlgorithm->isSpringEffect_ = false;
    listLayoutAlgorithm->FixPredictSnapOffsetAlignCenter();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0.f);
}

/**
 * @tc.name: FixPredictSnapOffsetAlignCenter005
 * @tc.desc: Test ArcListLayoutAlgorithm::FixPredictSnapOffsetAlignCenter
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, FixPredictSnapOffsetAlignCenter005, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    pattern_->SetPredictSnapOffset(100.0);
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(listLayoutAlgorithm, nullptr);
    listLayoutAlgorithm->SetItemInfo(0, { 0, 1.0, 200.0, true });
    listLayoutAlgorithm->totalOffset_ = 1000.0;
    listLayoutAlgorithm->isSpringEffect_ = false;
    listLayoutAlgorithm->FixPredictSnapOffsetAlignCenter();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0.0f);
}

/**
 * @tc.name: FixPredictSnapOffsetAlignCenter006
 * @tc.desc: Test ArcListLayoutAlgorithm::FixPredictSnapOffsetAlignCenter
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, FixPredictSnapOffsetAlignCenter006, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    pattern_->SetPredictSnapOffset(100.0);
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(listLayoutAlgorithm, nullptr);
    listLayoutAlgorithm->SetItemInfo(0, { 0, 1.0, 200.0, true });
    listLayoutAlgorithm->totalOffset_ = 200.0;
    listLayoutAlgorithm->totalItemCount_ = 3;
    listLayoutAlgorithm->FixPredictSnapOffsetAlignCenter();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0.0f);
}

/**
 * @tc.name: FixPredictSnapOffsetAlignCenter007
 * @tc.desc: Test ArcListLayoutAlgorithm::FixPredictSnapOffsetAlignCenter
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, FixPredictSnapOffsetAlignCenter007, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    pattern_->SetPredictSnapOffset(100.0);
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(listLayoutAlgorithm, nullptr);
    listLayoutAlgorithm->SetItemInfo(0, { 0, 10.0, 240.0, true });
    listLayoutAlgorithm->spaceWidth_ = 50;
    listLayoutAlgorithm->totalOffset_ = 200.0;
    listLayoutAlgorithm->predictSnapOffset_ = 100.0;
    listLayoutAlgorithm->contentMainSize_ = 20;
    listLayoutAlgorithm->totalItemCount_ = 1;
    listLayoutAlgorithm->FixPredictSnapOffsetAlignCenter();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0.0f);
}

/**
 * @tc.name: MeasureHeader001
 * @tc.desc: Test ArcListLayoutAlgorithm::MeasureHeader
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, MeasureHeader001, TestSize.Level1)
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
    listLayoutAlgorithm->headerIndex_ = 0;
    listLayoutAlgorithm->MeasureList(Referenced::RawPtr(frameNode_));

    EXPECT_TRUE(NearEqual(listLayoutAlgorithm->GetTargetIndex().value_or(-99), -99));
}

#ifdef SUPPORT_DIGITAL_CROWN
/**
 * @tc.name: OnMidIndexChanged001
 * @tc.desc: Test ArcListPattern::OnMidIndexChanged
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestNg, OnMidIndexChanged001, TestSize.Level1)
{
    CreateList();
    CreateListItems(ARC_ITEM_COUNT);
    CreateDone();
    auto scrollable = pattern_->CreateScrollable();
    ASSERT_NE(scrollable, nullptr);
    scrollable->SetCrownEventDragging(true);
    pattern_->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    pattern_->scrollableEvent_->SetScrollable(scrollable);
    pattern_->OnMidIndexChanged();
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_TRUE(NearEqual(listLayoutAlgorithm->GetPredictSnapEndPosition().value_or(-0.001), -0.001));
}
#endif
} // namespace OHOS::Ace::NG
