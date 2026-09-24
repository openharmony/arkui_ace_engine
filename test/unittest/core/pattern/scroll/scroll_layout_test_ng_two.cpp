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

#include "scroll_test_ng.h"

#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_model.h"
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float LAZY_GRID_ITEM_HEIGHT = 50.0f;
constexpr float LAZY_GRID_GAP = 5.0f;
constexpr int32_t LAZY_GRID_SMALL_ITEM_COUNT = 4;
constexpr float ADJUST_OFFSET_START_POSITIVE = 20.0f;
constexpr float ADJUST_OFFSET_START_NEGATIVE = -20.0f;
constexpr float ADJUST_OFFSET_END = 15.0f;

void CreateLazyVGridInScroll(float itemHeight, int32_t itemCount)
{
    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");
    gridModel.SetRowGap(Dimension(LAZY_GRID_GAP));
    gridModel.SetColumnGap(Dimension(LAZY_GRID_GAP));
    for (int32_t index = 0; index < itemCount; index++) {
        TextModelNG textModel;
        textModel.Create(u"text");
        ViewAbstract::SetHeight(CalcLength(itemHeight));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();
}
} // namespace

class ScrollLayoutTestNg : public ScrollTestNg {
public:
};

/**
 * @tc.name: ContentOffset001
 * @tc.desc: Test Scroll ContentStartOffset and ContentEndOffset.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffset001, TestSize.Level1)
{
    CreateScroll();
    float contentOffset = 20.f;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(layoutProperty_->GetContentStartOffset(), contentOffset);
    EXPECT_EQ(layoutProperty_->GetContentEndOffset(), contentOffset);
}

/**
 * @tc.name: ContentOffset002
 * @tc.desc: Test Scroll scrollableDistance with ContentStartOffset and ContentEndOffset.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffset002, TestSize.Level1)
{
    CreateScroll();
    float contentOffset = 20.f;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(layoutProperty_->GetContentStartOffset(), contentOffset);
    EXPECT_EQ(layoutProperty_->GetContentEndOffset(), contentOffset);
    EXPECT_EQ(pattern_->scrollableDistance_, CONTENT_MAIN_SIZE - HEIGHT + contentOffset * 2);
}

/**
 * @tc.name: ContentOffset003
 * @tc.desc: Test Scroll ContentStartOffset and ContentEndOffset with illegle value
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffset003, TestSize.Level1)
{
    CreateScroll();
    ScrollableModelNG::SetContentStartOffset(HEIGHT / 2);
    ScrollableModelNG::SetContentEndOffset(HEIGHT / 2);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(pattern_->contentEndOffset_, 0);
    EXPECT_EQ(pattern_->contentStartOffset_, 0);
    EXPECT_EQ(pattern_->scrollableDistance_, CONTENT_MAIN_SIZE - HEIGHT);
}

/**
 * @tc.name: ContentOffset004
 * @tc.desc: Test Scroll ContentStartOffset and ContentEndOffset with ReachStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffset004, TestSize.Level1)
{
    CreateScroll();
    float contentOffset = 20;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(pattern_->currentOffset_, 0.0);
    EXPECT_EQ(pattern_->GetTotalOffset(), -contentOffset);
    EXPECT_TRUE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());

    pattern_->ScrollBy(0, -640, false);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, -640.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 620.f);
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_TRUE(pattern_->IsAtBottom());
}

/**
 * @tc.name: ContentOffset005
 * @tc.desc: Test Scroll ContentStartOffset and ContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffset005, TestSize.Level1)
{
    int32_t isToEdge = 0;
    int32_t isReachStart = 0;
    int32_t isReachEnd = 0;
    NG::ScrollEdgeEvent scrollEdgeEvent = [&isToEdge](ScrollEdge) { isToEdge++; };
    auto reachStartEvent = [&isReachStart]() { isReachStart++; };
    auto reachEndEvent = [&isReachEnd]() { isReachEnd++; };
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::VERTICAL);
    model.SetOnScrollEdge(std::move(scrollEdgeEvent));
    model.SetOnReachStart(std::move(reachStartEvent));
    model.SetOnReachEnd(std::move(reachEndEvent));
    float contentOffset = 20;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset * 1.5);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Trigger reachStartEvent init
     */
    EXPECT_EQ(isReachStart, 1);
    EXPECT_EQ(isReachEnd, 0);
    EXPECT_EQ(isToEdge, 0);
    EXPECT_EQ(pattern_->GetTotalOffset(), -contentOffset);
    EXPECT_EQ(pattern_->currentOffset_, 0.0);
    EXPECT_EQ(isReachStart, 1);

    /**
     * @tc.steps: step2. ScrollTo 0
     * @tc.expected: totalOffset and currentOffset is correct
     */
    ScrollTo(0);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0.0f);
    EXPECT_EQ(pattern_->currentOffset_, -contentOffset);

    /**
     * @tc.steps: step3. ScrollTo bottom
     * @tc.expected: Trigger scrollEdgeEvent/reachEndEvent
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630.0f);
    EXPECT_EQ(isReachEnd, 1);
    EXPECT_EQ(isToEdge, 1);

    ScrollBy(0, 10);
    EXPECT_EQ(pattern_->GetTotalOffset(), 620.0f);

    ScrollBy(0, -10);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630.0f);
    EXPECT_EQ(isReachEnd, 2);
    EXPECT_EQ(isToEdge, 2);

    /**
     * @tc.steps: step3. ScrollTo top
     * @tc.expected: Trigger onScrollEvent/scrollEdgeEvent/reachStartEvent
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_EQ(isReachStart, 2);
    EXPECT_EQ(isReachEnd, 2);
    EXPECT_EQ(isToEdge, 3);
}

/**
 * @tc.name: ContentOffsetWithInitialOffset
 * @tc.desc: Test Scroll ContentStartOffset and ContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffsetWithInitialOffset, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    model.SetInitialOffset(OffsetT(CalcDimension(0.f), CalcDimension(5.f)));
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(pattern_->GetInitialOffset().GetX().ToString(), "0.00px");
    EXPECT_EQ(pattern_->GetInitialOffset().GetY().ToString(), "5.00px");

    EXPECT_EQ(pattern_->currentOffset_, -CONTENT_START_OFFSET - 5.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 5.f);
}

/**
 * @tc.name: ContentOffsetWithSmallChildSize
 * @tc.desc: Test Scroll with small child and ContentStartOffset and ContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffsetWithSmallChildSize, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateContent(100.f);
    CreateScrollDone();

    EXPECT_EQ(pattern_->currentOffset_, 0.0f);
    EXPECT_EQ(pattern_->GetChildrenExpandedSize().height_, 100.f);
}

/**
 * @tc.name: ContentOffsetWithAlignTopCenter
 * @tc.desc: Test Scroll with align top center and ContentStartOffset and ContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffsetWithAlignTopCenter, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    ViewAbstract::SetAlign(Alignment::TOP_CENTER);
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateContent(100.f);
    CreateScrollDone();

    RectF childRect = GetChildRect(frameNode_, 0);
    EXPECT_EQ(childRect.y_, CONTENT_START_OFFSET);
}

/**
 * @tc.name: ContentOffsetWithAlignCenter
 * @tc.desc: Test Scroll with align center and ContentStartOffset and ContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffsetWithAlignCenter, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    ViewAbstract::SetAlign(Alignment::CENTER);
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateContent(100.f);
    CreateScrollDone();

    RectF childRect = GetChildRect(frameNode_, 0);
    EXPECT_EQ(childRect.y_, (HEIGHT - CONTENT_START_OFFSET - CONTENT_END_OFFSET - 100) / 2 + CONTENT_START_OFFSET);
}

/**
 * @tc.name: ContentOffsetWithAlignBottomCenter
 * @tc.desc: Test Scroll with align center and ContentStartOffset and ContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffsetWithAlignBottomCenter, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    ViewAbstract::SetAlign(Alignment::BOTTOM_CENTER);
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateContent(100.f);
    CreateScrollDone();

    RectF childRect = GetChildRect(frameNode_, 0);
    EXPECT_EQ(childRect.y_, HEIGHT - 100 - CONTENT_END_OFFSET);
}

/**
 * @tc.name: ContentOffsetWithItemAlignStart
 * @tc.desc: Test Scroll with align Start and ContentStartOffset and ContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffsetWithItemAlignStart, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    ViewAbstract::SetAlign(Alignment::TOP_CENTER);
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateContent(HEIGHT - 10);
    CreateScrollDone();

    RectF childRect = GetChildRect(frameNode_, 0);
    EXPECT_EQ(childRect.y_, CONTENT_START_OFFSET);
}

/**
 * @tc.name: ContentOffsetWithItemAlignCenter
 * @tc.desc: Test Scroll with align Center and ContentStartOffset and ContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffsetWithItemAlignCenter, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    ViewAbstract::SetAlign(Alignment::CENTER);
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateContent(HEIGHT - 10);
    CreateScrollDone();

    RectF childRect = GetChildRect(frameNode_, 0);
    EXPECT_EQ(childRect.y_, CONTENT_START_OFFSET);
}

/**
 * @tc.name: ContentOffsetWithItemAlignBottom
 * @tc.desc: Test Scroll with align Center and ContentStartOffset and ContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffsetWithItemAlignBottom, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    ViewAbstract::SetAlign(Alignment::BOTTOM_CENTER);
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateContent(HEIGHT - 10);
    CreateScrollDone();

    RectF childRect = GetChildRect(frameNode_, 0);
    EXPECT_EQ(childRect.y_, CONTENT_START_OFFSET);
}

/**
 * @tc.name: ContentOffsetWithItemAlignStart
 * @tc.desc: Test Scroll with align Start and ContentStartOffset and ContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffsetWithItemHeightAlignStart, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    ViewAbstract::SetAlign(Alignment::TOP_CENTER);
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateContent(HEIGHT - CONTENT_START_OFFSET - CONTENT_END_OFFSET);
    CreateScrollDone();

    RectF childRect = GetChildRect(frameNode_, 0);
    EXPECT_EQ(childRect.y_, CONTENT_START_OFFSET);
}

/**
 * @tc.name: ContentOffsetWithItemAlignCenter
 * @tc.desc: Test Scroll with align Center and ContentStartOffset and ContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffsetWithItemHeightAlignCenter, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    ViewAbstract::SetAlign(Alignment::CENTER);
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateContent(HEIGHT - CONTENT_START_OFFSET - CONTENT_END_OFFSET);
    CreateScrollDone();

    RectF childRect = GetChildRect(frameNode_, 0);
    EXPECT_EQ(childRect.y_, CONTENT_START_OFFSET);
}

/**
 * @tc.name: ContentOffsetWithItemAlignBottom
 * @tc.desc: Test Scroll with align Center and ContentStartOffset and ContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffsetWithItemHeightAlignBottom, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    ViewAbstract::SetAlign(Alignment::BOTTOM_CENTER);
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateContent(HEIGHT - CONTENT_START_OFFSET - CONTENT_END_OFFSET);
    CreateScrollDone();

    RectF childRect = GetChildRect(frameNode_, 0);
    EXPECT_EQ(childRect.y_, CONTENT_START_OFFSET);
}

/**
 * @tc.name: LargeScrollOffsetAccuracy
 * @tc.desc: Test large scroll offset accuracy
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, LargeScrollOffsetAccuracy, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    CreateContent(16777216);
    CreateScrollDone();

    /**
     * @tc.steps: step2. Scroll to a large offset.
     * @tc.expected: the current offset is 16770000
     */
    ScrollBy(0, -16770000.0);
    EXPECT_DOUBLE_EQ(pattern_->currentOffset_, -16770000.0);

    /**
     * @tc.steps: step3. Scroll to a small offset.
     * @tc.expected: the current offset is 16770000.0625
     */
    pattern_->UpdateCurrentOffset(-0.0625, SCROLL_FROM_JUMP);
    FlushUITasks();
    EXPECT_DOUBLE_EQ(pattern_->currentOffset_, -16770000.0625);
}

/**
 * @tc.name: ScrollExpandSafeArea
 * @tc.desc: Test Scroll Set ExpandSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ScrollExpandSafeArea, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();

    auto geometryNode = frameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetSelfAdjust(RectF(-10.0f, -10.0f, 1.0f, 1.0f));
    DirtySwapConfig config;
    pattern_->BeforeSyncGeometryProperties(config);
    auto scrollBarOverlayModifier = pattern_->GetScrollBarOverlayModifier();
    ASSERT_NE(scrollBarOverlayModifier, nullptr);
    EXPECT_EQ(scrollBarOverlayModifier->GetAdjustOffset(), Offset(10.0f, 10.0f));
}

/**
 * @tc.name: RTLwithContentOffset001
 * @tc.desc: Test horizontal scroll in RTL Layout with contentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, RTLwithContentOffset001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateContent(WIDTH);
    CreateScrollDone(frameNode_);

    RectF childRect = GetChildRect(frameNode_, 0);
    EXPECT_EQ(childRect.x_, -CONTENT_START_OFFSET);
}

/**
 * @tc.name: MeasureLazyChild001
 * @tc.desc: Test MeasureLazyChild with valid contentSize and isMainFix=false
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, MeasureLazyChild001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll with LazyLayout child
     */
    CreateScroll();
    CreateLazyVGridInScroll(LAZY_GRID_ITEM_HEIGHT, LAZY_GRID_SMALL_ITEM_COUNT);
    CreateScrollDone();

    auto gridNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridNode, nullptr);

    /**
     * @tc.steps: step2. Create layout wrapper and algorithm
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);
    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. Set layout constraint
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    /**
     * @tc.steps: step4. Measure lazy child with valid contentSize
     * @tc.expected: estimatedIdealSize remains empty, viewPosEnd = LayoutInfinity
     */
    auto contentSize = SizeF(WIDTH, HEIGHT);
    bool isMainFix = false;
    auto childSize = layoutAlgorithm->MeasureLazyChild(
        AceType::RawPtr(layoutWrapper), childWrapper, childLayoutConstraint, axis, contentSize, isMainFix);

    const float expectedHeight = LAZY_GRID_ITEM_HEIGHT * 2 + LAZY_GRID_GAP;
    EXPECT_EQ(childSize.Width(), WIDTH);
    EXPECT_EQ(childSize.Height(), expectedHeight);

    ASSERT_TRUE(childLayoutConstraint.viewPosRef.has_value());
    auto& viewPosRef = childLayoutConstraint.viewPosRef.value();
    EXPECT_EQ(viewPosRef.viewPosStart, 0.0f);
    EXPECT_EQ(viewPosRef.viewPosEnd, HEIGHT);
    EXPECT_EQ(viewPosRef.referenceEdge, ReferenceEdge::START);
    EXPECT_EQ(viewPosRef.axis, axis);
}

/**
 * @tc.name: MeasureLazyChild002
 * @tc.desc: Test MeasureLazyChild when viewPortLength <= 0 triggers MATCH_PARENT calculation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, MeasureLazyChild002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll with LazyLayout child
     */
    CreateScroll();
    CreateLazyVGridInScroll(LAZY_GRID_ITEM_HEIGHT, LAZY_GRID_SMALL_ITEM_COUNT);
    CreateScrollDone();

    auto gridNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridNode, nullptr);

    /**
     * @tc.steps: step2. Create layout wrapper and algorithm
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);
    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. Set layout constraint
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    /**
     * @tc.steps: step4. Measure lazy child with contentSize.Height=0
     * @tc.expected: MATCH_PARENT triggered, estimatedIdealSize.Height = constraint.maxSize.Height
     */
    auto contentSize = SizeF(WIDTH, 0.0f);
    bool isMainFix = false;
    auto childSize = layoutAlgorithm->MeasureLazyChild(
        AceType::RawPtr(layoutWrapper), childWrapper, childLayoutConstraint, axis, contentSize, isMainFix);

    EXPECT_GT(childSize.Width(), 0.0f);
    EXPECT_GT(childSize.Height(), 0.0f);

    ASSERT_TRUE(childLayoutConstraint.viewPosRef.has_value());
    auto& viewPosRef = childLayoutConstraint.viewPosRef.value();
    EXPECT_EQ(viewPosRef.viewPosStart, 0.0f);
    EXPECT_EQ(viewPosRef.viewPosEnd, HEIGHT);
}

/**
 * @tc.name: MeasureLazyChild003
 * @tc.desc: Test MeasureLazyChild with isMainFix=true applies calcLayoutConstraint
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, MeasureLazyChild003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll with LazyLayout child
     */
    CreateScroll();
    CreateLazyVGridInScroll(LAZY_GRID_ITEM_HEIGHT, LAZY_GRID_SMALL_ITEM_COUNT);
    CreateScrollDone();

    auto gridNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridNode, nullptr);

    /**
     * @tc.steps: step2. Create layout wrapper and algorithm
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);
    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. Set layout constraint and calcLayoutConstraint
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, HEIGHT);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);

    auto calcLayoutConstraint = std::make_unique<MeasureProperty>();
    calcLayoutConstraint->maxSize = CalcSize(CalcLength(WIDTH), CalcLength(500.0f));
    scrollLayoutProperty->calcLayoutConstraint_ = std::move(calcLayoutConstraint);

    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    /**
     * @tc.steps: step4. Measure lazy child with isMainFix=true
     * @tc.expected: calcLayoutConstraint applied to estimatedIdealSize
     */
    auto contentSize = SizeF(WIDTH, HEIGHT);
    bool isMainFix = true;
    auto childSize = layoutAlgorithm->MeasureLazyChild(
        AceType::RawPtr(layoutWrapper), childWrapper, childLayoutConstraint, axis, contentSize, isMainFix);

    EXPECT_GT(childSize.Width(), 0.0f);
    EXPECT_GT(childSize.Height(), 0.0f);
}

/**
 * @tc.name: MeasureLazyChild004
 * @tc.desc: Test MeasureLazyChild with contentStartOffset reset logic
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, MeasureLazyChild004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll with LazyLayout child and contentOffset
     */
    ScrollModelNG model = CreateScroll();
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateLazyVGridInScroll(LAZY_GRID_ITEM_HEIGHT, LAZY_GRID_SMALL_ITEM_COUNT);
    CreateScrollDone();

    auto gridNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridNode, nullptr);

    /**
     * @tc.steps: step2. Create layout wrapper and algorithm with large offset
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);
    layoutAlgorithm->contentStartOffset_ = CONTENT_START_OFFSET;
    layoutAlgorithm->contentEndOffset_ = CONTENT_END_OFFSET;

    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. Set layout constraint with small maxSize to trigger reset
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, 50.0f);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, 50.0f);
    parentLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    /**
     * @tc.steps: step4. Measure lazy child
     * @tc.expected: estimatedContentStartOffset reset when offset >= estimatedIdealSize
     */
    auto contentSize = SizeF(WIDTH, 0.0f);
    bool isMainFix = false;
    auto childSize = layoutAlgorithm->MeasureLazyChild(
        AceType::RawPtr(layoutWrapper), childWrapper, childLayoutConstraint, axis, contentSize, isMainFix);

    EXPECT_GT(childSize.Width(), 0.0f);
    EXPECT_GT(childSize.Height(), 0.0f);
}

/**
 * @tc.name: MeasureLazyChild005
 * @tc.desc: Test MeasureLazyChild with maxSize.Height=0 and contentSize.Height=0
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, MeasureLazyChild005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll with LazyLayout child
     */
    CreateScroll();
    CreateLazyVGridInScroll(LAZY_GRID_ITEM_HEIGHT, LAZY_GRID_SMALL_ITEM_COUNT);
    CreateScrollDone();

    auto gridNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridNode, nullptr);

    /**
     * @tc.steps: step2. Create layout wrapper and algorithm
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);

    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. Set layout constraint with maxSize.Height=0
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, 0.0f);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    /**
     * @tc.steps: step4. Measure lazy child with maxSize.Height=0 and contentSize.Height=0
     * @tc.expected: CreateIdealSize uses parentIdealSize or percentReference.Height=HEIGHT
     *                estimatedIdealSize.Height = HEIGHT, viewPosEnd = HEIGHT
     */
    auto contentSize = SizeF(WIDTH, 0.0f);
    bool isMainFix = false;
    layoutAlgorithm->MeasureLazyChild(
        AceType::RawPtr(layoutWrapper), childWrapper, childLayoutConstraint, axis, contentSize, isMainFix);

    ASSERT_TRUE(childLayoutConstraint.viewPosRef.has_value());
    auto& viewPosRef = childLayoutConstraint.viewPosRef.value();
    EXPECT_EQ(viewPosRef.viewPosStart, 0.0f);
    EXPECT_EQ(viewPosRef.viewPosEnd, HEIGHT);
    EXPECT_EQ(viewPosRef.referenceEdge, ReferenceEdge::START);
    EXPECT_EQ(viewPosRef.axis, axis);
}

/**
 * @tc.name: GetLazyChildAdjustOffsetTest001
 * @tc.desc: Test GetLazyChildAdjustOffset with positive start adjustOffset applied during MeasureLazyChildAgain
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, GetLazyChildAdjustOffsetTest001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyVGridInScroll(LAZY_GRID_ITEM_HEIGHT, LAZY_GRID_SMALL_ITEM_COUNT);
    CreateScrollDone();

    auto gridNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridNode, nullptr);
    auto gridPattern = gridNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(gridPattern, nullptr);

    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);
    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    auto contentSize = SizeF(WIDTH, HEIGHT);
    bool isMainFix = false;
    layoutAlgorithm->MeasureLazyChild(
        AceType::RawPtr(layoutWrapper), childWrapper, childLayoutConstraint, axis, contentSize, isMainFix);

    gridPattern->layoutInfo_->adjustOffset_ = { ADJUST_OFFSET_START_POSITIVE, 0.0f };

    auto initialOffset = layoutAlgorithm->currentOffset_;
    auto padding = scrollLayoutProperty->CreatePaddingAndBorder();
    layoutAlgorithm->MeasureLazyChildAgain(
        childWrapper, childLayoutConstraint, axis, contentSize, padding, true);

    EXPECT_EQ(layoutAlgorithm->currentOffset_, initialOffset - ADJUST_OFFSET_START_POSITIVE);
}

/**
 * @tc.name: GetLazyChildAdjustOffsetTest002
 * @tc.desc: Test GetLazyChildAdjustOffset with negative start adjustOffset (currentOffset increases)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, GetLazyChildAdjustOffsetTest002, TestSize.Level1)
{
    CreateScroll();
    CreateLazyVGridInScroll(LAZY_GRID_ITEM_HEIGHT, LAZY_GRID_SMALL_ITEM_COUNT);
    CreateScrollDone();

    auto gridNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridNode, nullptr);
    auto gridPattern = gridNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(gridPattern, nullptr);

    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);
    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    auto contentSize = SizeF(WIDTH, HEIGHT);
    bool isMainFix = false;
    layoutAlgorithm->MeasureLazyChild(
        AceType::RawPtr(layoutWrapper), childWrapper, childLayoutConstraint, axis, contentSize, isMainFix);

    gridPattern->layoutInfo_->adjustOffset_ = { ADJUST_OFFSET_START_NEGATIVE, 0.0f };

    auto initialOffset = layoutAlgorithm->currentOffset_;
    auto padding = scrollLayoutProperty->CreatePaddingAndBorder();
    layoutAlgorithm->MeasureLazyChildAgain(
        childWrapper, childLayoutConstraint, axis, contentSize, padding, true);

    EXPECT_EQ(layoutAlgorithm->currentOffset_, initialOffset - ADJUST_OFFSET_START_NEGATIVE);
}

/**
 * @tc.name: GetLazyChildAdjustOffsetTest003
 * @tc.desc: Test that non-lazy child does not trigger GetLazyChildAdjustOffset (hasLazyLayoutChild_ is false)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, GetLazyChildAdjustOffsetTest003, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();

    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);
    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    auto contentSize = SizeF(WIDTH, HEIGHT);
    auto initialOffset = layoutAlgorithm->currentOffset_;
    auto padding = scrollLayoutProperty->CreatePaddingAndBorder();
    layoutAlgorithm->MeasureLazyChildAgain(
        childWrapper, childLayoutConstraint, axis, contentSize, padding, false);

    EXPECT_EQ(layoutAlgorithm->currentOffset_, initialOffset);
}

/**
 * @tc.name: GetLazyChildAdjustOffsetTest004
 * @tc.desc: Test GetLazyChildAdjustOffset with zero adjustOffset (no effect on currentOffset_)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, GetLazyChildAdjustOffsetTest004, TestSize.Level1)
{
    CreateScroll();
    CreateLazyVGridInScroll(LAZY_GRID_ITEM_HEIGHT, LAZY_GRID_SMALL_ITEM_COUNT);
    CreateScrollDone();

    auto gridNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridNode, nullptr);
    auto gridPattern = gridNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(gridPattern, nullptr);

    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);
    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    auto contentSize = SizeF(WIDTH, HEIGHT);
    bool isMainFix = false;
    layoutAlgorithm->MeasureLazyChild(
        AceType::RawPtr(layoutWrapper), childWrapper, childLayoutConstraint, axis, contentSize, isMainFix);

    gridPattern->layoutInfo_->adjustOffset_ = { 0.0f, 0.0f };

    auto initialOffset = layoutAlgorithm->currentOffset_;
    auto padding = scrollLayoutProperty->CreatePaddingAndBorder();
    layoutAlgorithm->MeasureLazyChildAgain(
        childWrapper, childLayoutConstraint, axis, contentSize, padding, true);

    EXPECT_EQ(layoutAlgorithm->currentOffset_, initialOffset);
}

/**
 * @tc.name: GetLazyChildAdjustOffsetTest005
 * @tc.desc: Test that only end adjustOffset (start=0) has no effect on currentOffset_
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, GetLazyChildAdjustOffsetTest005, TestSize.Level1)
{
    CreateScroll();
    CreateLazyVGridInScroll(LAZY_GRID_ITEM_HEIGHT, LAZY_GRID_SMALL_ITEM_COUNT);
    CreateScrollDone();

    auto gridNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridNode, nullptr);
    auto gridPattern = gridNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(gridPattern, nullptr);

    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);
    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    auto contentSize = SizeF(WIDTH, HEIGHT);
    bool isMainFix = false;
    layoutAlgorithm->MeasureLazyChild(
        AceType::RawPtr(layoutWrapper), childWrapper, childLayoutConstraint, axis, contentSize, isMainFix);

    gridPattern->layoutInfo_->adjustOffset_ = { 0.0f, ADJUST_OFFSET_END };

    auto initialOffset = layoutAlgorithm->currentOffset_;
    auto padding = scrollLayoutProperty->CreatePaddingAndBorder();
    layoutAlgorithm->MeasureLazyChildAgain(
        childWrapper, childLayoutConstraint, axis, contentSize, padding, true);

    EXPECT_EQ(layoutAlgorithm->currentOffset_, initialOffset);
}

/**
 * @tc.name: GetLazyChildAdjustOffsetTest006
 * @tc.desc: Test GetAndResetAdjustOffset resets adjustOffset after being consumed during MeasureLazyChildAgain
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, GetLazyChildAdjustOffsetTest006, TestSize.Level1)
{
    CreateScroll();
    CreateLazyVGridInScroll(LAZY_GRID_ITEM_HEIGHT, LAZY_GRID_SMALL_ITEM_COUNT);
    CreateScrollDone();

    auto gridNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridNode, nullptr);
    auto gridPattern = gridNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(gridPattern, nullptr);

    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);
    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    auto contentSize = SizeF(WIDTH, HEIGHT);
    bool isMainFix = false;
    layoutAlgorithm->MeasureLazyChild(
        AceType::RawPtr(layoutWrapper), childWrapper, childLayoutConstraint, axis, contentSize, isMainFix);

    gridPattern->layoutInfo_->adjustOffset_ = { ADJUST_OFFSET_START_POSITIVE, ADJUST_OFFSET_END };

    auto padding = scrollLayoutProperty->CreatePaddingAndBorder();
    layoutAlgorithm->MeasureLazyChildAgain(
        childWrapper, childLayoutConstraint, axis, contentSize, padding, true);

    EXPECT_EQ(gridPattern->layoutInfo_->adjustOffset_.start, 0.0f);
    EXPECT_EQ(gridPattern->layoutInfo_->adjustOffset_.end, 0.0f);
}

/**
 * @tc.name: GetLazyChildAdjustOffsetTest007
 * @tc.desc: Test that second MeasureLazyChildAgain gets default AdjustOffset after first call consumed it
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, GetLazyChildAdjustOffsetTest007, TestSize.Level1)
{
    CreateScroll();
    CreateLazyVGridInScroll(LAZY_GRID_ITEM_HEIGHT, LAZY_GRID_SMALL_ITEM_COUNT);
    CreateScrollDone();

    auto gridNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridNode, nullptr);
    auto gridPattern = gridNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(gridPattern, nullptr);

    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);
    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    auto contentSize = SizeF(WIDTH, HEIGHT);
    bool isMainFix = false;
    layoutAlgorithm->MeasureLazyChild(
        AceType::RawPtr(layoutWrapper), childWrapper, childLayoutConstraint, axis, contentSize, isMainFix);

    gridPattern->layoutInfo_->adjustOffset_ = { ADJUST_OFFSET_START_POSITIVE, ADJUST_OFFSET_END };

    auto padding = scrollLayoutProperty->CreatePaddingAndBorder();
    layoutAlgorithm->MeasureLazyChildAgain(
        childWrapper, childLayoutConstraint, axis, contentSize, padding, true);

    auto offsetAfterFirstCall = layoutAlgorithm->currentOffset_;
    layoutAlgorithm->MeasureLazyChildAgain(
        childWrapper, childLayoutConstraint, axis, contentSize, padding, true);

    EXPECT_EQ(layoutAlgorithm->currentOffset_, offsetAfterFirstCall);
}

/**
 * @tc.name: GetLazyChildAdjustOffsetTest008
 * @tc.desc: Test GetLazyChildAdjustOffset returns default when child has no LazyLayoutPattern
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, GetLazyChildAdjustOffsetTest008, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateContentChild(10);
    CreateScrollDone();

    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);
    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    auto contentSize = SizeF(WIDTH, HEIGHT);
    auto initialOffset = layoutAlgorithm->currentOffset_;
    auto padding = scrollLayoutProperty->CreatePaddingAndBorder();
    layoutAlgorithm->MeasureLazyChildAgain(
        childWrapper, childLayoutConstraint, axis, contentSize, padding, true);

    EXPECT_EQ(layoutAlgorithm->currentOffset_, initialOffset);
}

/**
 * @tc.name: GetLazyChildAdjustOffsetTest009
 * @tc.desc: Test positive start adjustOffset with both start and end values set
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, GetLazyChildAdjustOffsetTest009, TestSize.Level1)
{
    CreateScroll();
    CreateLazyVGridInScroll(LAZY_GRID_ITEM_HEIGHT, LAZY_GRID_SMALL_ITEM_COUNT);
    CreateScrollDone();

    auto gridNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridNode, nullptr);
    auto gridPattern = gridNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(gridPattern, nullptr);

    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);
    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    auto contentSize = SizeF(WIDTH, HEIGHT);
    bool isMainFix = false;
    layoutAlgorithm->MeasureLazyChild(
        AceType::RawPtr(layoutWrapper), childWrapper, childLayoutConstraint, axis, contentSize, isMainFix);

    gridPattern->layoutInfo_->adjustOffset_ = { ADJUST_OFFSET_START_POSITIVE, ADJUST_OFFSET_END };

    auto initialOffset = layoutAlgorithm->currentOffset_;
    auto padding = scrollLayoutProperty->CreatePaddingAndBorder();
    layoutAlgorithm->MeasureLazyChildAgain(
        childWrapper, childLayoutConstraint, axis, contentSize, padding, true);

    EXPECT_EQ(layoutAlgorithm->currentOffset_, initialOffset - ADJUST_OFFSET_START_POSITIVE);
}

/**
 * @tc.name: GetLazyChildAdjustOffsetTest010
 * @tc.desc: Test that adjustOffset is fully reset (both start and end) after consumption
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, GetLazyChildAdjustOffsetTest010, TestSize.Level1)
{
    CreateScroll();
    CreateLazyVGridInScroll(LAZY_GRID_ITEM_HEIGHT, LAZY_GRID_SMALL_ITEM_COUNT);
    CreateScrollDone();

    auto gridNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridNode, nullptr);
    auto gridPattern = gridNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(gridPattern, nullptr);

    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);
    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    auto contentSize = SizeF(WIDTH, HEIGHT);
    bool isMainFix = false;
    layoutAlgorithm->MeasureLazyChild(
        AceType::RawPtr(layoutWrapper), childWrapper, childLayoutConstraint, axis, contentSize, isMainFix);

    gridPattern->layoutInfo_->adjustOffset_ = { ADJUST_OFFSET_START_POSITIVE, ADJUST_OFFSET_END };

    auto padding = scrollLayoutProperty->CreatePaddingAndBorder();
    layoutAlgorithm->MeasureLazyChildAgain(
        childWrapper, childLayoutConstraint, axis, contentSize, padding, true);

    EXPECT_EQ(gridPattern->layoutInfo_->adjustOffset_.start, 0.0f);
    EXPECT_EQ(gridPattern->layoutInfo_->adjustOffset_.end, 0.0f);
}

/**
 * @tc.name: GetLazyChildAdjustOffsetTest011
 * @tc.desc: Test that second MeasureLazyChildAgain with a new algorithm gets zero adjustOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, GetLazyChildAdjustOffsetTest011, TestSize.Level1)
{
    CreateScroll();
    CreateLazyVGridInScroll(LAZY_GRID_ITEM_HEIGHT, LAZY_GRID_SMALL_ITEM_COUNT);
    CreateScrollDone();

    auto gridNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridNode, nullptr);
    auto gridPattern = gridNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(gridPattern, nullptr);

    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);
    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    auto contentSize = SizeF(WIDTH, HEIGHT);
    bool isMainFix = false;
    layoutAlgorithm->MeasureLazyChild(
        AceType::RawPtr(layoutWrapper), childWrapper, childLayoutConstraint, axis, contentSize, isMainFix);

    gridPattern->layoutInfo_->adjustOffset_ = { ADJUST_OFFSET_START_POSITIVE, 0.0f };

    auto padding = scrollLayoutProperty->CreatePaddingAndBorder();
    layoutAlgorithm->MeasureLazyChildAgain(
        childWrapper, childLayoutConstraint, axis, contentSize, padding, true);

    auto offsetAfterFirstCall = layoutAlgorithm->currentOffset_;

    auto layoutAlgorithm2 = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(offsetAfterFirstCall);
    layoutAlgorithm2->MeasureLazyChildAgain(
        childWrapper, childLayoutConstraint, axis, contentSize, padding, true);

    EXPECT_EQ(layoutAlgorithm2->currentOffset_, offsetAfterFirstCall);
}

/**
 * @tc.name: GetLazyChildAdjustOffsetTest012
 * @tc.desc: Test GetLazyChildAdjustOffset with non-zero initial scroll offset and positive adjustOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, GetLazyChildAdjustOffsetTest012, TestSize.Level1)
{
    CreateScroll();
    CreateLazyVGridInScroll(LAZY_GRID_ITEM_HEIGHT, LAZY_GRID_SMALL_ITEM_COUNT);
    CreateScrollDone();

    auto gridNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridNode, nullptr);
    auto gridPattern = gridNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(gridPattern, nullptr);

    double initialScrollOffset = -100.0;
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(initialScrollOffset);

    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto scrollLayoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(frameNode_->GetLayoutProperty());
    ASSERT_NE(scrollLayoutProperty, nullptr);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(WIDTH, HEIGHT);
    parentLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    scrollLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    auto axis = scrollLayoutProperty->GetAxis().value_or(Axis::VERTICAL);

    auto childLayoutConstraint = scrollLayoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);

    auto contentSize = SizeF(WIDTH, HEIGHT);
    bool isMainFix = false;
    layoutAlgorithm->MeasureLazyChild(
        AceType::RawPtr(layoutWrapper), childWrapper, childLayoutConstraint, axis, contentSize, isMainFix);

    gridPattern->layoutInfo_->adjustOffset_ = { ADJUST_OFFSET_START_POSITIVE, 0.0f };

    auto padding = scrollLayoutProperty->CreatePaddingAndBorder();
    layoutAlgorithm->MeasureLazyChildAgain(
        childWrapper, childLayoutConstraint, axis, contentSize, padding, true);

    EXPECT_EQ(layoutAlgorithm->currentOffset_, initialScrollOffset - ADJUST_OFFSET_START_POSITIVE);
}

class ScrollLayoutAlgorithmAlignmentTest : public testing::Test {
public:
    void SetUp() override
    {
        layoutProperty_ = AceType::MakeRefPtr<ScrollLayoutProperty>();
        algorithm_ = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(0.0);
    }
    void TearDown() override {}

    RefPtr<ScrollLayoutProperty> layoutProperty_;
    RefPtr<ScrollLayoutAlgorithm> algorithm_;
};

/**
 * @tc.name: GetAlignmentPosition001
 * @tc.desc: Test GetAlignmentPosition with default CENTER alignment, LTR, VERTICAL, content smaller than viewport
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition001, TestSize.Level1)
{
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::LTR, SizeF(400.0f, 600.0f), SizeF(400.0f, 300.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 150.0f);
}

/**
 * @tc.name: GetAlignmentPosition002
 * @tc.desc: Test GetAlignmentPosition with default CENTER alignment, LTR, VERTICAL, content larger than viewport
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition002, TestSize.Level1)
{
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::LTR, SizeF(400.0f, 600.0f), SizeF(400.0f, 1000.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
}

/**
 * @tc.name: GetAlignmentPosition003
 * @tc.desc: Test GetAlignmentPosition with TOP_LEFT alignment, LTR, VERTICAL, content smaller than viewport
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition003, TestSize.Level1)
{
    layoutProperty_->UpdateAlignment(Alignment::TOP_LEFT);
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::LTR, SizeF(400.0f, 600.0f), SizeF(300.0f, 200.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
}

/**
 * @tc.name: GetAlignmentPosition004
 * @tc.desc: Test GetAlignmentPosition with TOP_RIGHT alignment, LTR, VERTICAL, content smaller than viewport
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition004, TestSize.Level1)
{
    layoutProperty_->UpdateAlignment(Alignment::TOP_RIGHT);
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::LTR, SizeF(400.0f, 600.0f), SizeF(300.0f, 200.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 100.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
}

/**
 * @tc.name: GetAlignmentPosition005
 * @tc.desc: Test GetAlignmentPosition with BOTTOM_LEFT alignment, LTR, VERTICAL, content smaller than viewport
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition005, TestSize.Level1)
{
    layoutProperty_->UpdateAlignment(Alignment::BOTTOM_LEFT);
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::LTR, SizeF(400.0f, 600.0f), SizeF(300.0f, 200.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 400.0f);
}

/**
 * @tc.name: GetAlignmentPosition006
 * @tc.desc: Test GetAlignmentPosition with BOTTOM_RIGHT alignment, LTR, VERTICAL, content smaller than viewport
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition006, TestSize.Level1)
{
    layoutProperty_->UpdateAlignment(Alignment::BOTTOM_RIGHT);
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::LTR, SizeF(400.0f, 600.0f), SizeF(300.0f, 200.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 100.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 400.0f);
}

/**
 * @tc.name: GetAlignmentPosition007
 * @tc.desc: Test GetAlignmentPosition with CENTER alignment, HORIZONTAL axis, content smaller than viewport
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition007, TestSize.Level1)
{
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::HORIZONTAL, TextDirection::LTR, SizeF(600.0f, 400.0f), SizeF(200.0f, 400.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 200.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
}

/**
 * @tc.name: GetAlignmentPosition008
 * @tc.desc: Test GetAlignmentPosition with CENTER alignment, HORIZONTAL axis, content larger than viewport
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition008, TestSize.Level1)
{
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::HORIZONTAL, TextDirection::LTR, SizeF(600.0f, 400.0f), SizeF(1000.0f, 400.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
}

/**
 * @tc.name: GetAlignmentPosition009
 * @tc.desc: Test GetAlignmentPosition with CENTER alignment, FREE axis (always uses else branch)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition009, TestSize.Level1)
{
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::FREE, TextDirection::LTR, SizeF(400.0f, 600.0f), SizeF(300.0f, 200.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 50.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 200.0f);
}

/**
 * @tc.name: GetAlignmentPosition010
 * @tc.desc: Test GetAlignmentPosition with TOP_LEFT alignment in RTL direction (should swap to TOP_RIGHT)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition010, TestSize.Level1)
{
    layoutProperty_->UpdateAlignment(Alignment::TOP_LEFT);
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::RTL, SizeF(400.0f, 600.0f), SizeF(300.0f, 200.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 100.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
}

/**
 * @tc.name: GetAlignmentPosition011
 * @tc.desc: Test GetAlignmentPosition with CENTER_LEFT alignment in RTL direction (should swap to CENTER_RIGHT)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition011, TestSize.Level1)
{
    layoutProperty_->UpdateAlignment(Alignment::CENTER_LEFT);
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::RTL, SizeF(400.0f, 600.0f), SizeF(300.0f, 200.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 100.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 200.0f);
}

/**
 * @tc.name: GetAlignmentPosition012
 * @tc.desc: Test GetAlignmentPosition with CENTER alignment in RTL direction (should remain CENTER)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition012, TestSize.Level1)
{
    layoutProperty_->UpdateAlignment(Alignment::CENTER);
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::RTL, SizeF(400.0f, 600.0f), SizeF(300.0f, 200.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 50.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 200.0f);
}

/**
 * @tc.name: GetAlignmentPosition013
 * @tc.desc: Test GetAlignmentPosition RTL + VERTICAL + wider content (X adjustment applied)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition013, TestSize.Level1)
{
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::RTL, SizeF(400.0f, 600.0f), SizeF(500.0f, 1000.0f));
    EXPECT_FLOAT_EQ(result.GetX(), -100.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
}

/**
 * @tc.name: GetAlignmentPosition014
 * @tc.desc: Test GetAlignmentPosition LTR + VERTICAL + wider content (no X adjustment)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition014, TestSize.Level1)
{
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::LTR, SizeF(400.0f, 600.0f), SizeF(500.0f, 1000.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
}

/**
 * @tc.name: GetAlignmentPosition015
 * @tc.desc: Test GetAlignmentPosition RTL + HORIZONTAL + wider content (no X adjustment, only for VERTICAL)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition015, TestSize.Level1)
{
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::HORIZONTAL, TextDirection::RTL, SizeF(400.0f, 600.0f), SizeF(500.0f, 1000.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
}

/**
 * @tc.name: GetAlignmentPosition016
 * @tc.desc: Test GetAlignmentPosition with contentStartOffset and contentEndOffset, VERTICAL, content smaller
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition016, TestSize.Level1)
{
    algorithm_->contentStartOffset_ = 20.0f;
    algorithm_->contentEndOffset_ = 30.0f;
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::LTR, SizeF(400.0f, 600.0f), SizeF(400.0f, 300.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 125.0f);
}

/**
 * @tc.name: GetAlignmentPosition017
 * @tc.desc: Test GetAlignmentPosition with only contentStartOffset, VERTICAL, content smaller
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition017, TestSize.Level1)
{
    algorithm_->contentStartOffset_ = 20.0f;
    algorithm_->contentEndOffset_ = 0.0f;
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::LTR, SizeF(400.0f, 600.0f), SizeF(400.0f, 300.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 140.0f);
}

/**
 * @tc.name: GetAlignmentPosition018
 * @tc.desc: Test GetAlignmentPosition with only contentEndOffset, VERTICAL, content smaller
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition018, TestSize.Level1)
{
    algorithm_->contentStartOffset_ = 0.0f;
    algorithm_->contentEndOffset_ = 30.0f;
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::LTR, SizeF(400.0f, 600.0f), SizeF(400.0f, 300.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 135.0f);
}

/**
 * @tc.name: GetAlignmentPosition019
 * @tc.desc: Test GetAlignmentPosition with contentStartOffset and contentEndOffset, HORIZONTAL, content smaller
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition019, TestSize.Level1)
{
    algorithm_->contentStartOffset_ = 20.0f;
    algorithm_->contentEndOffset_ = 30.0f;
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::HORIZONTAL, TextDirection::LTR, SizeF(600.0f, 400.0f), SizeF(200.0f, 400.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 175.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
}

/**
 * @tc.name: GetAlignmentPosition020
 * @tc.desc: Test GetAlignmentPosition RTL + VERTICAL + wider content with TOP_LEFT alignment
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition020, TestSize.Level1)
{
    layoutProperty_->UpdateAlignment(Alignment::TOP_LEFT);
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::RTL, SizeF(400.0f, 600.0f), SizeF(500.0f, 200.0f));
    EXPECT_FLOAT_EQ(result.GetX(), -100.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
}

/**
 * @tc.name: GetAlignmentPosition021
 * @tc.desc: Test GetAlignmentPosition RTL + VERTICAL + wider content with BOTTOM_RIGHT alignment
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition021, TestSize.Level1)
{
    layoutProperty_->UpdateAlignment(Alignment::BOTTOM_RIGHT);
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::RTL, SizeF(400.0f, 600.0f), SizeF(500.0f, 200.0f));
    EXPECT_FLOAT_EQ(result.GetX(), -100.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 400.0f);
}

/**
 * @tc.name: GetAlignmentPosition022
 * @tc.desc: Test GetAlignmentPosition with content larger than viewport, contentStartOffset/endOffset not used
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition022, TestSize.Level1)
{
    algorithm_->contentStartOffset_ = 20.0f;
    algorithm_->contentEndOffset_ = 30.0f;
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::LTR, SizeF(400.0f, 600.0f), SizeF(400.0f, 1000.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
}

/**
 * @tc.name: GetAlignmentPosition023
 * @tc.desc: Test GetAlignmentPosition with FREE axis, content offsets not applied (else branch always)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition023, TestSize.Level1)
{
    algorithm_->contentStartOffset_ = 20.0f;
    algorithm_->contentEndOffset_ = 30.0f;
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::FREE, TextDirection::LTR, SizeF(400.0f, 600.0f), SizeF(300.0f, 200.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 50.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 200.0f);
}

/**
 * @tc.name: GetAlignmentPosition024
 * @tc.desc: Test GetAlignmentPosition with RTL + TOP_RIGHT alignment (should swap to TOP_LEFT)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition024, TestSize.Level1)
{
    layoutProperty_->UpdateAlignment(Alignment::TOP_RIGHT);
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::RTL, SizeF(400.0f, 600.0f), SizeF(300.0f, 200.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
}

/**
 * @tc.name: GetAlignmentPosition025
 * @tc.desc: Test GetAlignmentPosition with RTL + BOTTOM_LEFT alignment (should swap to BOTTOM_RIGHT)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition025, TestSize.Level1)
{
    layoutProperty_->UpdateAlignment(Alignment::BOTTOM_LEFT);
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::RTL, SizeF(400.0f, 600.0f), SizeF(300.0f, 200.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 100.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 400.0f);
}

/**
 * @tc.name: GetAlignmentPosition026
 * @tc.desc: Test GetAlignmentPosition with RTL + BOTTOM_RIGHT alignment (should swap to BOTTOM_LEFT)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition026, TestSize.Level1)
{
    layoutProperty_->UpdateAlignment(Alignment::BOTTOM_RIGHT);
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::RTL, SizeF(400.0f, 600.0f), SizeF(300.0f, 200.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 400.0f);
}

/**
 * @tc.name: GetAlignmentPosition027
 * @tc.desc: Test GetAlignmentPosition with RTL + CENTER_RIGHT alignment (should swap to CENTER_LEFT)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition027, TestSize.Level1)
{
    layoutProperty_->UpdateAlignment(Alignment::CENTER_RIGHT);
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::RTL, SizeF(400.0f, 600.0f), SizeF(300.0f, 200.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 200.0f);
}

/**
 * @tc.name: GetAlignmentPosition028
 * @tc.desc: Test GetAlignmentPosition with zero-sized viewport and content
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition028, TestSize.Level1)
{
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::LTR, SizeF(0.0f, 0.0f), SizeF(0.0f, 0.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
}

/**
 * @tc.name: GetAlignmentPosition029
 * @tc.desc: Test GetAlignmentPosition with equal content and viewport size (boundary: not smaller)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition029, TestSize.Level1)
{
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::VERTICAL, TextDirection::LTR, SizeF(400.0f, 600.0f), SizeF(400.0f, 600.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
}

/**
 * @tc.name: GetAlignmentPosition030
 * @tc.desc: Test GetAlignmentPosition with contentStartOffset/endOffset and HORIZONTAL TOP_RIGHT alignment
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutAlgorithmAlignmentTest, GetAlignmentPosition030, TestSize.Level1)
{
    layoutProperty_->UpdateAlignment(Alignment::TOP_RIGHT);
    algorithm_->contentStartOffset_ = 10.0f;
    algorithm_->contentEndOffset_ = 10.0f;
    auto result = algorithm_->GetAlignmentPosition(
        layoutProperty_, Axis::HORIZONTAL, TextDirection::LTR, SizeF(600.0f, 400.0f), SizeF(200.0f, 300.0f));
    EXPECT_FLOAT_EQ(result.GetX(), 380.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
}

} // namespace OHOS::Ace::NG
