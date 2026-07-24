/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "lazy_column_layout_test.h"

#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/lazy_layout/lazy_edge_test_helper.h"

#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_model.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_model.h"
#include "core/components_ng/pattern/list/list_model_ng.h"

namespace OHOS::Ace::NG {

namespace {

class LazyColumnLayoutHeaderFooterTest : public LazyColumnLayoutTest {
public:
    // Lazy column with header / content / footer inside the already-created scrollable container.
    void CreateColumnWithEdges(float headerHeight, int32_t itemCount, float footerHeight,
        StickyStyle sticky = StickyStyle::NONE)
    {
        CreateLazyWithEdges<LazyColumnLayoutModel>(
            *this, [this]() { CreateLazyColumnLayout(); }, headerHeight, itemCount, footerHeight, sticky);
    }
};

} // namespace

/**
 * @tc.name: NestedGridItemsRenderWithHeaderFooter001
 * @tc.desc: A header/footer LazyVGridLayout nested under LazyColumnLayout must activate its content items.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutHeaderFooterTest, NestedGridItemsRenderWithHeaderFooter001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyColumnLayout();
    CreateLazyWithEdges<LazyGridLayoutModel>(
        *this, [this]() { CreateLazyVGridLayout(); }, 60.0f, 30, 40.0f, StickyStyle::BOTH);
    ASSERT_NE(lazyGridPattern_, nullptr);
    EXPECT_EQ(lazyGridPattern_->layoutInfo_->startIndex_, 0);
    EXPECT_GT(lazyGridPattern_->layoutInfo_->endIndex_, 0);

    auto headerNode = lazyGridPattern_->GetHeaderNode();
    auto footerNode = lazyGridPattern_->GetFooterNode();
    ASSERT_NE(headerNode, nullptr);
    ASSERT_NE(footerNode, nullptr);
    EXPECT_TRUE(headerNode->IsActive());
    EXPECT_TRUE(footerNode->IsActive());

    auto firstItemWrapper = lazyGridFrameNode_->GetChildByIndex(1);
    ASSERT_NE(firstItemWrapper, nullptr);
    auto firstItemNode = firstItemWrapper->GetHostNode();
    ASSERT_NE(firstItemNode, nullptr);
    EXPECT_TRUE(firstItemNode->IsActive());
}

/**
 * @tc.name: StickyEdgesIdleAndToggleStability001
 * @tc.desc: Sticky edges must survive non-scroll relayout paths: predictive (idle) frames keep the section total
 *           (regression: footer double-counted on the PROPERTY_UPDATE_MEASURE_SELF predict path) and the edges'
 *           active state intact, and toggling sticky BOTH -> NONE -> BOTH keeps the header sized with item 0
 *           anchored at body 0.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutHeaderFooterTest, StickyEdgesIdleAndToggleStability001, TestSize.Level1)
{
    CreateScroll();
    CreateColumnWithEdges(60.0f, 30, 40.0f, StickyStyle::BOTH);
    RunIdleStabilityChecks(*this);
    RunStickyToggleKeepsHeaderScenario<LazyColumnLayoutModel>(*this, 60.0f);
}

/**
 * @tc.name: ListContentOffsetInsetAndHeaderResizeLocal001
 * @tc.desc: A List's contentStartOffset/contentEndOffset must be forwarded through the nested LazyColumnLayout's
 *           layout constraint so sticky edges reserve that space, and growing the header must reflow item 0 below
 *           the new header without moving the LazyColumnLayout wrapper to the List top.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutHeaderFooterTest, ListContentOffsetInsetAndHeaderResizeLocal001, TestSize.Level1)
{
    constexpr float startOffset = 30.0f;
    constexpr float endOffset = 20.0f;
    constexpr float initialHeader = 40.0f;
    constexpr float grownHeader = 120.0f;
    constexpr float footerHeight = 30.0f;

    CreateList();
    ListModelNG::SetContentStartOffset(AceType::RawPtr(scrollableFrameNode_), startOffset);
    ListModelNG::SetContentEndOffset(AceType::RawPtr(scrollableFrameNode_), endOffset);
    CreateColumnWithEdges(initialHeader, 12, footerHeight, StickyStyle::BOTH);
    auto headerNode = pattern_->GetHeaderNode();
    ASSERT_NE(headerNode, nullptr);
    EXPECT_FLOAT_EQ(GetChildY(scrollableFrameNode_, 0), startOffset);
    EXPECT_FLOAT_EQ(GetChildY(scrollableFrameNode_, 0) + GetChildY(frameNode_, 1), startOffset + initialHeader);

    // Header resize stays local: the wrapper keeps its position, item 0 reflows below the new header.
    ResizeLazyEdge(*this, headerNode, grownHeader);
    EXPECT_EQ(pattern_->GetHeaderMainSize(), grownHeader);
    EXPECT_FLOAT_EQ(GetChildY(scrollableFrameNode_, 0), startOffset);
    EXPECT_FLOAT_EQ(GetChildY(scrollableFrameNode_, 0) + GetChildY(frameNode_, 0), startOffset);
    EXPECT_FLOAT_EQ(GetChildY(scrollableFrameNode_, 0) + GetChildY(frameNode_, 1), startOffset + grownHeader);

    // Scrolled: both sticky edges keep reserving the forwarded insets.
    scrollablePattern_->UpdateCurrentOffset(-120.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    const auto lazyColumnY = GetChildY(scrollableFrameNode_, 0);
    EXPECT_FLOAT_EQ(lazyColumnY + GetChildY(frameNode_, 0), startOffset);
    EXPECT_FLOAT_EQ(lazyColumnY + GetChildY(frameNode_, 13), SCROLL_HEIGHT - endOffset - footerHeight);
}

/**
 * @tc.name: ListBackScrollWithFooter001
 * @tc.desc: A footer-backed LazyColumnLayout under a List must be able to scroll back from the bottom.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutHeaderFooterTest, ListBackScrollWithFooter001, TestSize.Level1)
{
    CreateList();
    CreateLazyColumnLayout();
    CreateContent(20);
    LazyColumnLayoutModel::SetFooter([]() { CreateLazyTestEdge(60.0f); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);

    scrollablePattern_->UpdateCurrentOffset(-1500.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    const int32_t startAtBottom = pattern_->layoutInfo_->startIndex_;
    EXPECT_GT(startAtBottom, 0);

    // Back-scroll: the content must move back (start index decreases); the footer-leak bug pinned it at the bottom.
    scrollablePattern_->UpdateCurrentOffset(700.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_LT(pattern_->layoutInfo_->startIndex_, startAtBottom);
}

/**
 * @tc.name: HeaderResizeBodyLocalAndIdleTotal001
 * @tc.desc: Header resizes leave the body-local posMap_ coords untouched (the reflow shows up only as the
 *           layout-time +headerMainSize_ screen offset of the items), and a resize driven only through the
 *           predictive PROPERTY_UPDATE_MEASURE_SELF pass still grows the section total by exactly headerDelta
 *           with adjustOffset_ kept neutral (the pass must reuse prevBodyMainSize_).
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutHeaderFooterTest, HeaderResizeBodyLocalAndIdleTotal001, TestSize.Level1)
{
    constexpr float initialHeader = 40.0f;
    constexpr float grownHeader = 120.0f;

    CreateScroll();
    CreateColumnWithEdges(initialHeader, 20, 30.0f);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 1), initialHeader);

    RunBodyLocalPosMapInvariantOnHeaderResize(*this, grownHeader);

    // The reflow shows up only as a screen offset: item 0 sits below the grown header.
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 1), grownHeader);

    RunHeaderResizeOnIdleScenario(*this, grownHeader, 200.0f);
}

/**
 * @tc.name: EmptyDataWithHeaderFooterTotal001
 * @tc.desc: Body-local contract: with zero data items the section total is exactly headerMainSize_ + footerMainSize_,
 *           and the edges still lay out (header at top, footer right below it).
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutHeaderFooterTest, EmptyDataWithHeaderFooterTotal001, TestSize.Level1)
{
    CreateScroll();
    CreateColumnWithEdges(60.0f, 0, 40.0f);
    RunEmptyDataEdgesOnlyChecks(*this, 60.0f, 40.0f);
}

/**
 * @tc.name: DataRemoveAddKeepsHeaderFooterAsEdges001
 * @tc.desc: Body-local contract: removing/adding a DATA item keeps header/footer as edge slots (header at section
 *           top, section total = header + body + footer) and only the body extent changes. Header is raw child 0
 *           and footer is the last raw child, so data items are mutated at raw index >= 1.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutHeaderFooterTest, DataRemoveAddKeepsHeaderFooterAsEdges001, TestSize.Level1)
{
    constexpr float headerHeight = 40.0f;
    constexpr float footerHeight = 30.0f;

    CreateScroll();
    CreateColumnWithEdges(headerHeight, 8, footerHeight);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 8);
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->totalMainSize_, headerHeight + 8 * ITEM_HEIGHT + footerHeight);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0.0f); // header at section top

    // Remove one DATA item (raw index 1; raw 0 is the header).
    frameNode_->RemoveChildAtIndex(1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode_);

    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 7);
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->totalMainSize_, headerHeight + 7 * ITEM_HEIGHT + footerHeight);
    EXPECT_EQ(pattern_->GetHeaderMainSize(), headerHeight);
    EXPECT_EQ(pattern_->GetFooterMainSize(), footerHeight);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0.0f);

    // Add one DATA item back after the header.
    AddChildAtIndex(1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode_);

    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 8);
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->totalMainSize_, headerHeight + 8 * ITEM_HEIGHT + footerHeight);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0.0f);
}

/**
 * @tc.name: StickyHeaderPinnedUnderScroll001
 * @tc.desc: Body-local contract: a sticky header stays pinned to the section top while the body scrolls, and stays
 *           active and sized. Sticky math uses section coords and is independent of the body-local item coords.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutHeaderFooterTest, StickyHeaderPinnedUnderScroll001, TestSize.Level1)
{
    CreateScroll();
    CreateColumnWithEdges(40.0f, 20, 30.0f, StickyStyle::BOTH);
    // At rest the header sits at the section/viewport top.
    EXPECT_FLOAT_EQ(GetChildY(scrollableFrameNode_, 0) + GetChildY(frameNode_, 0), 0.0f);
    RunStickyPinnedUnderScrollChecks(*this, 40.0f, -250.0f);
}

/**
 * @tc.name: HeaderResizeFrameAdjustOffsetNeutral001
 * @tc.desc: On the frame where the header resized (totalMainSize_ still holds the previous SECTION total while
 *           headerMainSize_ already holds the new value), UpdatePosMap must use the caller-supplied prev body and
 *           keep adjustOffset_ at {0,0} for stable body positions.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutHeaderFooterTest, HeaderResizeFrameAdjustOffsetNeutral001, TestSize.Level1)
{
    LazyColumnLayoutInfo layoutInfo;
    layoutInfo.SetSpace(10.0f);
    layoutInfo.SetTotalItemCount(3);
    layoutInfo.headerMainSize_ = 120.0f; // current (grown from 60)
    layoutInfo.footerMainSize_ = 40.0f;
    layoutInfo.totalMainSize_ = 420.0f; // previous SECTION total: prev header 60 + body 320 + footer 40

    layoutInfo.SetPosMap(0, { 0.0f, 100.0f });
    layoutInfo.SetPosMap(1, { 110.0f, 210.0f });
    layoutInfo.SetPosMap(2, { 220.0f, 320.0f });

    layoutInfo.UpdatePosMap(320.0f); // prev body, unaffected by the resize

    EXPECT_FLOAT_EQ(layoutInfo.totalMainSize_, 320.0f);
    EXPECT_FLOAT_EQ(layoutInfo.adjustOffset_.start, 0.0f);
    EXPECT_FLOAT_EQ(layoutInfo.adjustOffset_.end, 0.0f);
}

/**
 * @tc.name: FooterOnlyViewportKeepsBodyWindowEmpty001
 * @tc.desc: Body-local contract: with the viewport scrolled fully into the footer zone (past the body end), the lazy
 *           window must report "past the last item" (startIndex_ == totalItemCount). Clamping against the stale
 *           SECTION total instead of the body extent keeps the last item in the window by header+footer too long.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutHeaderFooterTest, FooterOnlyViewportKeepsBodyWindowEmpty001, TestSize.Level1)
{
    CreateScroll();
    // Footer (600) taller than the viewport so a footer-only viewport exists; section = 40 + 300 + 600.
    CreateColumnWithEdges(40.0f, 3, 600.0f);
    RunFooterOnlyViewportChecks(*this, 3, SCROLL_HEIGHT);
}

/**
 * @tc.name: EmptyBodyWithEdgesThenAddItems001
 * @tc.desc: With a previous frame holding only header+footer (body empty, section total > 0), adding the first data
 *           items while the viewport sits past the (unknown) body start must measure from item 0, not clamp to
 *           past-the-end. Guards the "body known" predicate against counting header/footer as measured body.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutHeaderFooterTest, EmptyBodyWithEdgesThenAddItems001, TestSize.Level1)
{
    CreateList();
    // Scroll past the empty child's header and add the first data items in the same flush.
    RunEmptyBodyThenAddItemsScenario<LazyColumnLayoutModel>(*this, [this]() { CreateLazyColumnLayout(); }, 40.0f,
        30.0f, 5, -50.0f, false, 5, ITEM_HEIGHT, 5 * ITEM_HEIGHT, true);
}

/**
 * @tc.name: EmptyBodyWithEdgesThenAddItemsOffscreen001
 * @tc.desc: SLIDING_WINDOW WaterFlow measures far-offscreen children, so here the viewport genuinely sits past the
 *           empty child's (unknown) body when its first data items arrive. The child must measure them from item 0
 *           and report the real section total, not clamp to past-the-end because last frame's header+footer made the
 *           section total positive.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutHeaderFooterTest, EmptyBodyWithEdgesThenAddItemsOffscreen001, TestSize.Level1)
{
    CreateWaterFlow(WaterFlowLayoutMode::SLIDING_WINDOW);
    // Gap 60 > header 40 keeps the child partially visible with the viewport top past its header.
    RunEmptyBodyThenAddItemsScenario<LazyColumnLayoutModel>(*this, [this]() { CreateLazyColumnLayout(); }, 40.0f,
        30.0f, 20, -60.0f, true, 5, ITEM_HEIGHT, 5 * ITEM_HEIGHT, false);
}

/**
 * @tc.name: CacheRecycleSentinelIsBodyLocal001
 * @tc.desc: CheckCacheRecycle's "everything scrolled past cacheStart" sentinel feeds body-local predict cursors, so
 *           it must use the body extent, not the stale section total.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutHeaderFooterTest, CacheRecycleSentinelIsBodyLocal001, TestSize.Level1)
{
    auto info = AceType::MakeRefPtr<LazyColumnLayoutInfo>();
    info->totalItemCount_ = 2;
    info->posMap_[0] = { 0.0f, 100.0f };
    info->posMap_[1] = { 100.0f, 200.0f };
    info->cachedStartIndex_ = 0;
    info->cacheStartPos_ = 325.0f; // body coords: both items fully before the cache window

    LazyColumnLayoutAlgorithm algorithm(info);
    algorithm.totalItemCount_ = 2;
    algorithm.totalMainSize_ = 1040.0f; // stale SECTION total (header 40 + body 200 + footer 800)
    algorithm.prevBodyMainSize_ = 200.0f;

    algorithm.CheckCacheRecycle();

    EXPECT_EQ(algorithm.layoutedEndIndex_, 2);
    EXPECT_FLOAT_EQ(algorithm.layoutedEnd_, 200.0f); // body end, not the stale section total
}

/**
 * @tc.name: AdjustOffsetNeutralAndStaleClear001
 * @tc.desc: adjustOffset_ must stay {0,0} on the first layout (no parent anchor) and across pure header and footer
 *           resizes (edge slots are not body deltas), and the empty-data measure path must clear a stale
 *           (unconsumed) adjustOffset_ instead of leaking it to the parent.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutHeaderFooterTest, AdjustOffsetNeutralAndStaleClear001, TestSize.Level1)
{
    CreateScroll();
    CreateColumnWithEdges(40.0f, 12, 30.0f);
    RunAdjustNeutralOnEdgeResizes(*this, 120.0f, 100.0f);
    RunEmptyDataClearsAdjustScenario(*this, 12);
}

/**
 * @tc.name: EndAnchoredPureEdgeResizeKeepsAdjacency001
 * @tc.desc: With the List anchored at the item BELOW the LazyColumnLayout (backward fill, parent consumes .end),
 *           pure header and footer resizes must keep the LazyColumnLayout's bottom glued to the next item.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutHeaderFooterTest, EndAnchoredPureEdgeResizeKeepsAdjacency001, TestSize.Level1)
{
    CreateList();
    ListModelNG::SetInitialIndex(AceType::RawPtr(scrollableFrameNode_), 1);
    CreateLazyColumnLayout();
    LazyColumnLayoutModel::SetHeader([]() { CreateLazyTestEdge(40.0f); });
    CreateContent(12);
    LazyColumnLayoutModel::SetFooter([]() { CreateLazyTestEdge(30.0f); });
    ViewStackProcessor::GetInstance()->Pop();
    CreateListItems();
    CreateDone();
    ASSERT_NE(pattern_, nullptr);
    auto adjacencyGap = [this]() {
        return GetChildY(scrollableFrameNode_, 0) + GetChildHeight(scrollableFrameNode_, 0) -
               GetChildY(scrollableFrameNode_, 1);
    };
    EXPECT_FLOAT_EQ(adjacencyGap(), 0.0f);

    auto headerNode = pattern_->GetHeaderNode();
    ASSERT_NE(headerNode, nullptr);
    ResizeLazyEdge(*this, headerNode, 120.0f);
    ASSERT_EQ(pattern_->GetHeaderMainSize(), 120.0f);
    EXPECT_FLOAT_EQ(adjacencyGap(), 0.0f);

    auto footerNode = pattern_->GetFooterNode();
    ASSERT_NE(footerNode, nullptr);
    ResizeLazyEdge(*this, footerNode, 100.0f);
    ASSERT_EQ(pattern_->GetFooterMainSize(), 100.0f);
    EXPECT_FLOAT_EQ(adjacencyGap(), 0.0f);
}
} // namespace OHOS::Ace::NG
