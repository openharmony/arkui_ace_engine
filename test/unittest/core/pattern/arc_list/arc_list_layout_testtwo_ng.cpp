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

#include "arc_list_test_ng.h"
#include "gtest/gtest.h"

#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class ArcListLayoutTestTwoNg : public ArcListTestNg {
public:
    void UpdateContentModifier();
    RefPtr<ListPaintMethod> UpdateOverlayModifier();
    AssertionResult VerifySticky(int32_t groupIndex, bool isHeader, float expectOffsetY);
    void UpdateDividerMap();
};

void ArcListLayoutTestTwoNg::UpdateContentModifier()
{
    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    listPaint->UpdateContentModifier(AceType::RawPtr(paintWrapper));
}

RefPtr<ListPaintMethod> ArcListLayoutTestTwoNg::UpdateOverlayModifier()
{
    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    listPaint->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    return listPaint;
}

AssertionResult ArcListLayoutTestTwoNg::VerifySticky(int32_t groupIndex, bool isHeader, float expectOffsetY)
{
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, groupIndex);
    float offsetY = isHeader ? GetChildRect(groupNode, 0).GetY() : GetChildRect(groupNode, 1).GetY();
    // because has header height, the footer under header
    if (!isHeader && expectOffsetY < GROUP_HEADER_LEN) {
        expectOffsetY = GROUP_HEADER_LEN;
    }
    return IsEqual(offsetY, expectOffsetY);
}

void ArcListLayoutTestTwoNg::UpdateDividerMap()
{
    int cur = 0;
    for (auto& child : pattern_->itemPosition_) {
        child.second.id += cur;
        cur++;
    }
    UpdateContentModifier();
}

/**
 * @tc.name: LayoutHeader001
 * @tc.desc: Test ArcListLayoutAlgorithm::LayoutHeader
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, LayoutHeader001, TestSize.Level1)
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
    ArcListLayoutAlgorithm listLayoutAlgorithm(200, 100);
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
    EXPECT_EQ(150, crossOffset);
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
    EXPECT_EQ(layoutDirection, TextDirection::RTL);
}

/**
 * @tc.name: LayoutHeader002
 * @tc.desc: Test ArcListLayoutAlgorithm::LayoutHeader
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, LayoutHeader002, TestSize.Level1)
{
    // create menu item group
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    menuItemGroup->MountToParent(wrapperNode);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->OnModifyDone();
    auto algorithm = AceType::MakeRefPtr<ArcListLayoutAlgorithm>(200, 100);
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto* layoutWrapper = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    auto props = layoutWrapper->GetLayoutProperty();
    props->UpdateLayoutConstraint(parentLayoutConstraint);
    props->UpdateContentConstraint();
    // create menu item
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
        layoutWrapper->AppendChild(childWrapper);
    }
    // set selectTheme to themeManager before using themeManager to get selectTheme
    // test measure
    algorithm->Measure(layoutWrapper);
    // @tc.expected: menu content width = item width, height = sum(item height)
    auto expectedSize = SizeF(0, 0);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), expectedSize);

    // test layout
    algorithm->Layout(layoutWrapper);
    parentLayoutConstraint.selfIdealSize.SetWidth(10);
    props->UpdateLayoutConstraint(parentLayoutConstraint);
    props->UpdateContentConstraint();
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    algorithm->paddingOffset_ = padding.Offset();
    algorithm->headerIndex_ = 0;
    algorithm->Measure(layoutWrapper);
    algorithm->Layout(layoutWrapper);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().Height(), 0);
    algorithm->LayoutHeader(layoutWrapper, algorithm->paddingOffset_, 5.0);
    algorithm->MeasureHeader(layoutWrapper);
    EXPECT_EQ(algorithm->headerIndex_, 0);
    delete (layoutWrapper);
}

/**
 * @tc.name: LayoutHeader003
 * @tc.desc: Test ArcListLayoutAlgorithm::LayoutHeader
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, LayoutHeader003, TestSize.Level1)
{
    // create menu item group
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    menuItemGroup->MountToParent(wrapperNode);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->OnModifyDone();
    auto algorithm = AceType::MakeRefPtr<ArcListLayoutAlgorithm>(200, 100);
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto* layoutWrapper = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    auto props = layoutWrapper->GetLayoutProperty();
    props->UpdateLayoutConstraint(parentLayoutConstraint);
    props->UpdateContentConstraint();
    // create menu item
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
        layoutWrapper->AppendChild(childWrapper);
    }
    // set selectTheme to themeManager before using themeManager to get selectTheme
    // test measure
    algorithm->Measure(layoutWrapper);
    // @tc.expected: menu content width = item width, height = sum(item height)
    auto expectedSize = SizeF(0, 0);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), expectedSize);

    // test layout
    algorithm->Layout(layoutWrapper);
    parentLayoutConstraint.selfIdealSize.SetWidth(10);
    props->UpdateLayoutConstraint(parentLayoutConstraint);
    props->UpdateContentConstraint();
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    algorithm->paddingOffset_ = padding.Offset();
    algorithm->headerIndex_ = 0;
    algorithm->SetItemInfo(0, { 0, 1.0, 200.0, true });
    algorithm->startHeaderPos_ = 1000.0;
    algorithm->headerMainSize_ = -200.0;
    algorithm->headerOffset_ = -50.0;
    algorithm->expandSafeArea_ = true;
    algorithm->LayoutHeader(layoutWrapper, algorithm->paddingOffset_, 5.0);
    EXPECT_EQ(algorithm->headerIndex_, 0);
}

/**
 * @tc.name: LayoutHeader004
 * @tc.desc: Test ArcListLayoutAlgorithm::LayoutHeader when the height of first item changed
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, LayoutHeader004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list with header.
     */
    ListModelNG model = CreateList();
    auto headerSize = 50.0f;
    auto column = CreateColumn([headerSize](ColumnModelNG model) {
        ViewAbstract::SetWidth(CalcLength(headerSize));
        ViewAbstract::SetHeight(CalcLength(headerSize));
    });
    model.SetHeader(column);
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();

    /**
     * @tc.steps: step2. Flush ui task.
     * @tc.expected: 1. The start position of the header is 40.0f. 2. The distance between the header and the first item
     * is greater than 0, that is, the value of headerOffset_ is greater than 0.
     */
    FlushUITasks(frameNode_);
    auto headerDist = 40.0f;
    auto headerOffset = (LIST_HEIGHT - ITEM_HEIGHT * 1.08f) / 2.0f - headerDist - headerSize;
    EXPECT_EQ(pattern_->startHeaderPos_, headerDist);
    EXPECT_EQ(pattern_->headerOffset_, headerOffset);
    EXPECT_EQ(pattern_->oldFirstItemSize_, ITEM_HEIGHT);
    EXPECT_EQ(pattern_->oldHeaderSize_, headerSize);

    /**
     * @tc.steps: step3. Scroll list.
     * @tc.expected: The value of headerOffset_ unchanged.
     */
    ScrollTo(100);
    EXPECT_EQ(pattern_->headerOffset_, headerOffset);

    /**
     * @tc.steps: step4. Decrease the height of the first item.
     * @tc.expected: The value of headerOffset_ becomes larger.
     */
    auto firstItem = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(1));
    ViewAbstract::SetHeight(AceType::RawPtr(firstItem), CalcLength(ITEM_HEIGHT / 2.0f));
    FlushUITasks(frameNode_);
    EXPECT_GT(pattern_->headerOffset_, headerOffset);
    EXPECT_EQ(pattern_->oldFirstItemSize_, ITEM_HEIGHT / 2.0f);

    /**
     * @tc.steps: step5. Scroll list.
     * @tc.expected: 1. The start position of the header is 40.0f. 2. The value of headerOffset_ unchanged.
     */
    ScrollTo(-200);
    EXPECT_EQ(pattern_->startHeaderPos_, headerDist);
    EXPECT_GT(pattern_->headerOffset_, headerOffset);
}

/**
 * @tc.name: CreateLayoutAlgorithm001
 * @tc.desc: Test ArcListPattern::CreateLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, CreateLayoutAlgorithm001, TestSize.Level1)
{
    ListModelNG model = CreateListWithHeader();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();

    ListItemGroupLayoutInfo info;
    info.atStart = true;
    struct ListItemInfo itemInfo;
    itemInfo.id = 0;
    itemInfo.isGroup = true;
    itemInfo.groupInfo = info;
    pattern_->itemPosition_[DEFAULT_LANES] = itemInfo;

    pattern_->startMainPos_ = START_MAIN_POS;
    pattern_->startIndex_ = 0;
    pattern_->scrollSource_ = SCROLL_FROM_BAR;
    pattern_->predictSnapEndPos_ = PREDICT_SNAPEND_POS;
    pattern_->SetPredictSnapOffset(END_NODE_LEN);
    pattern_->CreateLayoutAlgorithm();
    EXPECT_EQ(pattern_->scrollSource_, SCROLL_FROM_BAR);
}

/**
 * @tc.name: GetSnapCenterOverScrollPos001
 * @tc.desc: Test ArcListPattern::GetSnapCenterOverScrollPos
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, GetSnapCenterOverScrollPos001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(END_NODE_LEN);

    float startPos = 30.0;
    float prevScroll = 20.0;
    pattern_->startIndex_ = 0;
    pattern_->GetSnapCenterOverScrollPos(startPos, prevScroll);
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_TRUE(NearEqual(listLayoutAlgorithm->GetPredictSnapEndPosition().value_or(-0.001), -0.001));
}

/**
 * @tc.name: GetSnapCenterOverScrollPos002
 * @tc.desc: Test ArcListPattern::GetSnapCenterOverScrollPos
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, GetSnapCenterOverScrollPos002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    pattern_->startIndex_ = 1;
    pattern_->endIndex_ = 3;
    pattern_->maxListItemIndex_ = 3;
    float startPos = 30.0;
    float prevScroll = 20.0;
    pattern_->endMainPos_ = 40.0;
    pattern_->currentDelta_ = 3.0;
    pattern_->contentMainSize_ = 100;
    pattern_->GetSnapCenterOverScrollPos(startPos, prevScroll);
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_TRUE(NearEqual(listLayoutAlgorithm->GetPredictSnapEndPosition().value_or(-0.001), -0.001));
}

/**
 * @tc.name: HandleScrollBarOutBoundary001
 * @tc.desc: Test ArcListPattern::HandleScrollBarOutBoundary
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, HandleScrollBarOutBoundary001, TestSize.Level1)
{
    ListModelNG model = CreateListWithHeader();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();

    ListItemGroupLayoutInfo info;
    info.atStart = true;
    struct ListItemInfo itemInfo;
    itemInfo.id = 0;
    itemInfo.isGroup = true;
    itemInfo.groupInfo = info;
    pattern_->itemPosition_[1] = itemInfo;
    pattern_->isScrollable_ = true;

    pattern_->startMainPos_ = 200.0;
    pattern_->startIndex_ = 0;
    pattern_->predictSnapEndPos_ = 34.5;
    pattern_->HandleScrollBarOutBoundary();
    pattern_->SetPredictSnapOffset(100.0);
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(listLayoutAlgorithm, nullptr);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_TRUE(NearEqual(listLayoutAlgorithm->GetPredictSnapEndPosition().value_or(-0.001), -0.001));
}

/**
 * @tc.name: HandleScrollBarOutBoundary002
 * @tc.desc: Test ArcListPattern::HandleScrollBarOutBoundary
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, HandleScrollBarOutBoundary002, TestSize.Level1)
{
    ListModelNG model = CreateListWithHeader();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();

    ListItemGroupLayoutInfo info;
    info.atStart = true;
    struct ListItemInfo itemInfo;
    itemInfo.id = 0;
    itemInfo.isGroup = true;
    itemInfo.groupInfo = info;
    pattern_->itemPosition_[1] = itemInfo;
    pattern_->startIndex_ = 0;
    pattern_->contentEndOffset_ = 0;
    pattern_->contentStartOffset_ = 0;
    pattern_->isScrollable_ = true;

    pattern_->startMainPos_ = 200.0;
    pattern_->endIndex_ = 3;
    pattern_->maxListItemIndex_ = 3;
    pattern_->endMainPos_ = 4;
    pattern_->contentMainSize_ = 400.0;
    pattern_->predictSnapEndPos_ = 34.5;
    pattern_->HandleScrollBarOutBoundary();
    pattern_->SetPredictSnapOffset(100.0);
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(listLayoutAlgorithm, nullptr);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_TRUE(NearEqual(listLayoutAlgorithm->GetPredictSnapEndPosition().value_or(-0.001), -0.001));
}

/**
 * @tc.name: HandleScrollBarOutBoundary003
 * @tc.desc: Test ArcListPattern::HandleScrollBarOutBoundary
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, HandleScrollBarOutBoundary003, TestSize.Level1)
{
    ListModelNG model = CreateListWithHeader();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->HandleScrollBarOutBoundary();
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_TRUE(NearEqual(listLayoutAlgorithm->GetPredictSnapEndPosition().value_or(-0.001), -0.001));
}

/**
 * @tc.name: HandleScrollBarOutBoundary004
 * @tc.desc: Test ArcListPattern::HandleScrollBarOutBoundary
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, HandleScrollBarOutBoundary004, TestSize.Level1)
{
    ListModelNG model = CreateListWithHeader();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    ListItemGroupLayoutInfo info;
    info.atStart = true;
    struct ListItemInfo itemInfo;
    itemInfo.id = 0;
    itemInfo.isGroup = true;
    itemInfo.groupInfo = info;
    pattern_->itemPosition_[1] = itemInfo;

    pattern_->SetScrollBar(nullptr);
    pattern_->SetScrollBarProxy(nullptr);
    pattern_->HandleScrollBarOutBoundary();
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_TRUE(NearEqual(listLayoutAlgorithm->GetPredictSnapEndPosition().value_or(-0.001), -0.001));
}

/**
 * @tc.name: GetItemDisplayInfo001
 * @tc.desc: Test ArcListPattern::GetItemDisplayInfo
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, GetItemDisplayInfo001, TestSize.Level1)
{
    ListModelNG model = CreateListWithHeader();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->GetHost()->GetOrCreateChildByIndex(0, false) = nullptr;
    pattern_->GetItemDisplayInfo(0);

    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm =
        AceType::DynamicCast<ArcListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_TRUE(NearEqual(listLayoutAlgorithm->GetPredictSnapEndPosition().value_or(-0.001), -0.001));
}

/**
 * @tc.name: CheckNeedUpdateHeaderOffset001
 * @tc.desc: Test ArcListLayoutAlgorithm CheckNeedUpdateHeaderOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, CheckNeedUpdateHeaderOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ArcListPattern> arcListPattern = AceType::MakeRefPtr<ArcListPattern>();
    arcListPattern->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    arcListPattern->scrollableEvent_->scrollable_ =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    auto wrapperNode = FrameNode::CreateFrameNode(V2::ARC_LIST_ETS_TAG, 1, arcListPattern);
    auto layoutWrapper = wrapperNode->CreateLayoutWrapper(true, true);
    RefPtr<ArcListLayoutAlgorithm> arcAlgorithm = AceType::MakeRefPtr<ArcListLayoutAlgorithm>(500, 200);

    /**
     * @tc.steps: step2. Set the IsScrollableStopped function to true
     */
    arcListPattern->scrollableEvent_->scrollable_->state_ = Scrollable::AnimationState::SPRING;

    /**
     * @tc.steps: step3. Call the CheckNeedUpdateHeaderOffset
     * @tc.expected: The result of function return false
     */
    auto result = arcAlgorithm->CheckNeedUpdateHeaderOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckNeedUpdateHeaderOffset002
 * @tc.desc: Test ArcListLayoutAlgorithm CheckNeedUpdateHeaderOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, CheckNeedUpdateHeaderOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ArcListPattern> arcListPattern = AceType::MakeRefPtr<ArcListPattern>();
    arcListPattern->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    arcListPattern->scrollableEvent_->scrollable_ =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    auto wrapperNode = FrameNode::CreateFrameNode(V2::ARC_LIST_ETS_TAG, 1, arcListPattern);
    auto layoutWrapper = wrapperNode->CreateLayoutWrapper(true, true);
    RefPtr<ArcListLayoutAlgorithm> arcAlgorithm = AceType::MakeRefPtr<ArcListLayoutAlgorithm>(500, 200);

    /**
     * @tc.steps: step2. Set the IsScrollableStopped function to return false
     * set IsOutOfBoundary function to return true
     */
    arcListPattern->scrollableEvent_->scrollable_->state_ = Scrollable::AnimationState::IDLE;
    ListItemGroupLayoutInfo itemGroupInfo = { true, true };
    ListItemInfo info = { 2, 2.0f, 4.0f, true, false, 1.0f, 2.0f, itemGroupInfo };
    std::map<int32_t, ListItemInfo> itemPosition = { { 0, info } };
    arcListPattern->itemPosition_ = itemPosition;
    arcListPattern->scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    arcListPattern->startIndex_ = 0;
    arcListPattern->endIndex_ = 6;
    arcListPattern->startMainPos_ = 20.0f;
    arcListPattern->endMainPos_ = 30.0f;
    arcListPattern->contentMainSize_ = 8.0f;
    arcListPattern->contentEndOffset_ = 4.0f;
    arcListPattern->contentStartOffset_ = 2.0f;
    arcListPattern->isStackFromEnd_ = false;
    arcListPattern->isScrollable_ = false;
    arcListPattern->scrollBarOutBoundaryExtent_ = 2.0f;
    arcListPattern->currentDelta_ = 0.0f;

    /**
     * @tc.steps: step3. Call the CheckNeedUpdateHeaderOffset
     * @tc.expected: The result of function return false
     */
    auto result = arcAlgorithm->CheckNeedUpdateHeaderOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckNeedUpdateHeaderOffset003
 * @tc.desc: Test ArcListLayoutAlgorithm CheckNeedUpdateHeaderOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, CheckNeedUpdateHeaderOffset003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ArcListPattern> arcListPattern = AceType::MakeRefPtr<ArcListPattern>();
    auto wrapperNode = FrameNode::CreateFrameNode(V2::ARC_LIST_ETS_TAG, 1, arcListPattern);
    auto layoutWrapper = wrapperNode->CreateLayoutWrapper(true, true);
    RefPtr<ArcListLayoutAlgorithm> arcAlgorithm = AceType::MakeRefPtr<ArcListLayoutAlgorithm>(500, 200);

    /**
     * @tc.steps: step2. Set the headerStayNear_ of ArcListLayoutAlgorithm to true
     */
    arcAlgorithm->headerStayNear_ = true;

    /**
     * @tc.steps: step3. Call the CheckNeedUpdateHeaderOffset
     * @tc.expected: The result of function return false
     */
    auto result = arcAlgorithm->CheckNeedUpdateHeaderOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckNeedUpdateHeaderOffset004
 * @tc.desc: Test ArcListLayoutAlgorithm CheckNeedUpdateHeaderOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, CheckNeedUpdateHeaderOffset004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ArcListPattern> arcListPattern = AceType::MakeRefPtr<ArcListPattern>();
    auto wrapperNode = FrameNode::CreateFrameNode(V2::ARC_LIST_ETS_TAG, 1, arcListPattern);
    auto layoutWrapper = wrapperNode->CreateLayoutWrapper(true, true);
    RefPtr<ArcListLayoutAlgorithm> arcAlgorithm = AceType::MakeRefPtr<ArcListLayoutAlgorithm>(500, 200);

    /**
     * @tc.steps: step2. Set the headerStayNear_ of ArcListLayoutAlgorithm to false
     * set the headerOffset_ of ArcListLayoutAlgorithm less than 0
     * set itemPosition_.count(0) equal to 0
     */
    ListItemGroupLayoutInfo itemGroupInfo = { true, true };
    ListItemInfo info = { 2, 2.0f, 4.0f, true, false, 1.0f, 2.0f, itemGroupInfo };
    std::map<int32_t, ListItemInfo> itemPosition = { { 1, info } };
    arcAlgorithm->itemPosition_ = itemPosition;
    arcListPattern->startIndex_ = 1;
    arcListPattern->endIndex_ = 2;
    arcAlgorithm->headerStayNear_ = false;
    arcAlgorithm->headerOffset_ = -2.0f;

    /**
     * @tc.steps: step3. Call the CheckNeedUpdateHeaderOffset
     * @tc.expected: The result of function return true and headerStayNear_ to be true
     */
    auto result = arcAlgorithm->CheckNeedUpdateHeaderOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(arcAlgorithm->headerStayNear_);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckNeedUpdateHeaderOffset005
 * @tc.desc: Test ArcListLayoutAlgorithm CheckNeedUpdateHeaderOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, CheckNeedUpdateHeaderOffset005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ArcListPattern> arcListPattern = AceType::MakeRefPtr<ArcListPattern>();
    auto wrapperNode = FrameNode::CreateFrameNode(V2::ARC_LIST_ETS_TAG, 1, arcListPattern);
    auto layoutWrapper = wrapperNode->CreateLayoutWrapper(true, true);
    RefPtr<ArcListLayoutAlgorithm> arcAlgorithm = AceType::MakeRefPtr<ArcListLayoutAlgorithm>(500, 200);

    /**
     * @tc.steps: step2. Set the headerStayNear_ of ArcListLayoutAlgorithm to false
     * set the headerOffset_ of ArcListLayoutAlgorithm greater than 0
     * set itemPosition_.count(0) equal to 0
     */
    ListItemGroupLayoutInfo itemGroupInfo = { true, true };
    ListItemInfo info = { 2, 2.0f, 4.0f, true, false, 1.0f, 2.0f, itemGroupInfo };
    std::map<int32_t, ListItemInfo> itemPosition = { { 1, info } };
    arcAlgorithm->itemPosition_ = itemPosition;
    arcListPattern->startIndex_ = 1;
    arcListPattern->endIndex_ = 2;
    arcAlgorithm->headerStayNear_ = false;
    arcAlgorithm->headerOffset_ = 2.0f;

    /**
     * @tc.steps: step3. Call the CheckNeedUpdateHeaderOffset
     * @tc.expected: The result of function return false
     */
    auto result = arcAlgorithm->CheckNeedUpdateHeaderOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckNeedUpdateHeaderOffset006
 * @tc.desc: Test ArcListLayoutAlgorithm CheckNeedUpdateHeaderOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, CheckNeedUpdateHeaderOffset006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ArcListPattern> arcListPattern = AceType::MakeRefPtr<ArcListPattern>();
    auto wrapperNode = FrameNode::CreateFrameNode(V2::ARC_LIST_ETS_TAG, 1, arcListPattern);
    auto layoutWrapper = wrapperNode->CreateLayoutWrapper(true, true);
    RefPtr<ArcListLayoutAlgorithm> arcAlgorithm = AceType::MakeRefPtr<ArcListLayoutAlgorithm>(500, 200);

    /**
     * @tc.steps: step2. Set the headerStayNear_ of ArcListLayoutAlgorithm to false
     * set the headerOffset_ of ArcListLayoutAlgorithm less than 0
     * set itemPosition_.count(0) not equal to 0
     */
    ListItemGroupLayoutInfo itemGroupInfo = { true, true };
    arcAlgorithm->itemPosition_.clear();
    arcAlgorithm->itemPosition_[0] = { 2, 2.0f, 4.0f, true, false, 1.0f, 2.0f, itemGroupInfo };
    arcListPattern->startIndex_ = 1;
    arcListPattern->endIndex_ = 2;
    arcAlgorithm->headerStayNear_ = false;
    arcAlgorithm->headerOffset_ = -2.0f;
    arcAlgorithm->oldFirstItemSize_ = 1.0f;
    arcAlgorithm->headerMainSize_ = 5.0f;
    arcAlgorithm->oldHeaderSize_ = 3.0f;

    /**
     * @tc.steps: step3. Call the CheckNeedUpdateHeaderOffset
     * @tc.expected: The oldFirstItemSize_ to be the difference between endPos and startPos
     * the oldHeaderSize_ to be headerMainSize_
     * the result of function return true
     */
    auto value = arcAlgorithm->itemPosition_[0].endPos - arcAlgorithm->itemPosition_[0].startPos;
    auto result = arcAlgorithm->CheckNeedUpdateHeaderOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(arcAlgorithm->oldFirstItemSize_, value);
    EXPECT_EQ(arcAlgorithm->oldHeaderSize_, arcAlgorithm->headerMainSize_);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckNeedUpdateHeaderOffset007
 * @tc.desc: Test ArcListLayoutAlgorithm CheckNeedUpdateHeaderOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, CheckNeedUpdateHeaderOffset007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ArcListPattern> arcListPattern = AceType::MakeRefPtr<ArcListPattern>();
    auto wrapperNode = FrameNode::CreateFrameNode(V2::ARC_LIST_ETS_TAG, 1, arcListPattern);
    auto layoutWrapper = wrapperNode->CreateLayoutWrapper(true, true);
    RefPtr<ArcListLayoutAlgorithm> arcAlgorithm = AceType::MakeRefPtr<ArcListLayoutAlgorithm>(500, 200);

    /**
     * @tc.steps: step2. Set the headerStayNear_ of ArcListLayoutAlgorithm to false
     * set the headerOffset_ of ArcListLayoutAlgorithm greater than 0
     * set itemPosition_.count(0) not equal to 0
     * the oldFirstItemSize_ not equal to  the difference between endPos and startPos
     */
    ListItemGroupLayoutInfo itemGroupInfo = { true, true };
    arcAlgorithm->itemPosition_.clear();
    arcAlgorithm->itemPosition_[0] = { 2, 2.0f, 4.0f, true, false, 1.0f, 2.0f, itemGroupInfo };
    arcListPattern->startIndex_ = 1;
    arcListPattern->endIndex_ = 2;
    arcAlgorithm->headerStayNear_ = false;
    arcAlgorithm->headerOffset_ = 2.0f;
    arcAlgorithm->oldFirstItemSize_ = 1.0f;
    arcAlgorithm->headerMainSize_ = 5.0f;
    arcAlgorithm->oldHeaderSize_ = 3.0f;

    /**
     * @tc.steps: step3. Call the CheckNeedUpdateHeaderOffset
     * @tc.expected: The oldFirstItemSize_ to be the difference between endPos and startPos
     * the oldHeaderSize_ to be headerMainSize_
     * the result of function return true
     */
    auto value = arcAlgorithm->itemPosition_[0].endPos - arcAlgorithm->itemPosition_[0].startPos;
    auto result = arcAlgorithm->CheckNeedUpdateHeaderOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(arcAlgorithm->oldFirstItemSize_, value);
    EXPECT_EQ(arcAlgorithm->oldHeaderSize_, arcAlgorithm->headerMainSize_);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckNeedUpdateHeaderOffset008
 * @tc.desc: Test ArcListLayoutAlgorithm CheckNeedUpdateHeaderOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, CheckNeedUpdateHeaderOffset008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ArcListPattern> arcListPattern = AceType::MakeRefPtr<ArcListPattern>();
    auto wrapperNode = FrameNode::CreateFrameNode(V2::ARC_LIST_ETS_TAG, 1, arcListPattern);
    auto layoutWrapper = wrapperNode->CreateLayoutWrapper(true, true);
    RefPtr<ArcListLayoutAlgorithm> arcAlgorithm = AceType::MakeRefPtr<ArcListLayoutAlgorithm>(500, 200);

    /**
     * @tc.steps: step2. Set the headerStayNear_ of ArcListLayoutAlgorithm to false
     * set the headerOffset_ of ArcListLayoutAlgorithm greater than 0
     * set itemPosition_.count(0) not equal to 0
     * the oldFirstItemSize_ equal to  the difference between endPos and startPos
     */
    ListItemGroupLayoutInfo itemGroupInfo = { true, true };
    arcAlgorithm->itemPosition_.clear();
    arcAlgorithm->itemPosition_[0] = { 2, 2.0f, 4.0f, true, false, 1.0f, 2.0f, itemGroupInfo };
    arcListPattern->startIndex_ = 1;
    arcListPattern->endIndex_ = 2;
    arcAlgorithm->headerStayNear_ = false;
    arcAlgorithm->headerOffset_ = 3.0f;
    arcAlgorithm->oldFirstItemSize_ = 2.0f;
    arcAlgorithm->headerMainSize_ = 5.0f;
    arcAlgorithm->oldHeaderSize_ = 3.0f;

    /**
     * @tc.steps: step3. Call the CheckNeedUpdateHeaderOffset
     * @tc.expected: The oldFirstItemSize_ to be the difference between endPos and startPos
     * the oldHeaderSize_ to be headerMainSize_
     * the result of function return true
     */
    auto value = arcAlgorithm->itemPosition_[0].endPos - arcAlgorithm->itemPosition_[0].startPos;
    auto result = arcAlgorithm->CheckNeedUpdateHeaderOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(arcAlgorithm->oldFirstItemSize_, value);
    EXPECT_EQ(arcAlgorithm->oldHeaderSize_, arcAlgorithm->headerMainSize_);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckNeedUpdateHeaderOffset009
 * @tc.desc: Test ArcListLayoutAlgorithm CheckNeedUpdateHeaderOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcListLayoutTestTwoNg, CheckNeedUpdateHeaderOffset009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ArcListPattern> arcListPattern = AceType::MakeRefPtr<ArcListPattern>();
    auto wrapperNode = FrameNode::CreateFrameNode(V2::ARC_LIST_ETS_TAG, 1, arcListPattern);
    auto layoutWrapper = wrapperNode->CreateLayoutWrapper(true, true);
    RefPtr<ArcListLayoutAlgorithm> arcAlgorithm = AceType::MakeRefPtr<ArcListLayoutAlgorithm>(500, 200);

    /**
     * @tc.steps: step2. Set the headerStayNear_ of ArcListLayoutAlgorithm to false
     * set the headerOffset_ of ArcListLayoutAlgorithm greater than 0
     * set itemPosition_.count(0) not equal to 0 and  the oldHeaderSize_ not equal to headerMainSize_
     * the oldFirstItemSize_ equal to  the difference between endPos and startPos
     */
    ListItemGroupLayoutInfo itemGroupInfo = { true, true };
    arcAlgorithm->itemPosition_.clear();
    arcAlgorithm->itemPosition_[0] = { 2, 2.0f, 4.0f, true, false, 1.0f, 2.0f, itemGroupInfo };
    arcListPattern->startIndex_ = 1;
    arcListPattern->endIndex_ = 2;
    arcAlgorithm->headerStayNear_ = false;
    arcAlgorithm->headerOffset_ = 3.0f;
    arcAlgorithm->oldFirstItemSize_ = 2.0f;
    arcAlgorithm->headerMainSize_ = 5.0f;
    arcAlgorithm->oldHeaderSize_ = 5.0f;

    /**
     * @tc.steps: step3. Call the CheckNeedUpdateHeaderOffset
     * @tc.expected: The result of function return false
     */
    auto result = arcAlgorithm->CheckNeedUpdateHeaderOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(result);
}
} // namespace OHOS::Ace::NG
