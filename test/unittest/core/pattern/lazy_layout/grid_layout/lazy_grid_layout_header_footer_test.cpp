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

#include "lazy_grid_layout_test.h"

#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/lazy_layout/lazy_edge_test_helper.h"

#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_model.h"
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_property.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"

namespace OHOS::Ace::NG {

namespace {

class LazyGridLayoutHeaderFooterTest : public LazyGridLayoutTest {
public:
    // Lazy grid with header / content / footer inside the already-created scrollable container.
    void CreateGridWithEdges(float headerHeight, int32_t itemCount, float footerHeight,
        StickyStyle sticky = StickyStyle::NONE)
    {
        CreateLazyWithEdges<LazyGridLayoutModel>(
            *this, [this]() { CreateLazyGridLayout(); }, headerHeight, itemCount, footerHeight, sticky);
    }
};

} // namespace

/**
 * @tc.name: LazyGridInListHeaderFooterContentOffsetBackScroll001
 * @tc.desc: A header/footer LazyVGrid under List.contentOffset must be able to scroll back from the bottom.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutHeaderFooterTest, LazyGridInListHeaderFooterContentOffsetBackScroll001, TestSize.Level1)
{
    CreateList();
    ListModelNG::SetContentStartOffset(AceType::RawPtr(scrollableFrameNode_), 30.0f);
    ListModelNG::SetContentEndOffset(AceType::RawPtr(scrollableFrameNode_), 30.0f);
    CreateGridWithEdges(60.0f, 100, 60.0f);
    ASSERT_NE(scrollablePattern_, nullptr);

    scrollablePattern_->UpdateCurrentOffset(-6000.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    const int32_t startAtBottom = pattern_->layoutInfo_->startIndex_;
    EXPECT_GT(startAtBottom, 0);

    scrollablePattern_->UpdateCurrentOffset(700.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_LT(pattern_->layoutInfo_->startIndex_, startAtBottom);
}

/**
 * @tc.name: StickyEdgesIdleAndToggleStability001
 * @tc.desc: Sticky edges must survive non-scroll relayout paths: predictive (idle) frames keep the section total
 *           and the edges' active state intact, and toggling sticky BOTH -> NONE -> BOTH keeps the header sized
 *           with item 0 anchored at body 0 (regression for the header collapsing onto item 0 when a property-only
 *           relayout addressed a stale edge reference).
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutHeaderFooterTest, StickyEdgesIdleAndToggleStability001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateGridWithEdges(60.0f, 30, 40.0f, StickyStyle::BOTH);
    RunIdleStabilityChecks(*this);
    RunStickyToggleKeepsHeaderScenario<LazyGridLayoutModel>(*this, 60.0f);
}

/**
 * @tc.name: HeaderResizeBodyLocalAndIdleTotal001
 * @tc.desc: Header resizes leave the body-local posMap_ coords untouched (regular relayout), and a resize driven
 *           only through the predictive PROPERTY_UPDATE_MEASURE_SELF pass still grows the section total by exactly
 *           headerDelta with adjustOffset_ kept neutral (the pass must reuse prevBodyMainSize_, not derive the body
 *           from the stale section total minus the CURRENT edges).
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutHeaderFooterTest, HeaderResizeBodyLocalAndIdleTotal001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateGridWithEdges(40.0f, 20, 30.0f);
    RunBodyLocalPosMapInvariantOnHeaderResize(*this, 120.0f);
    RunHeaderResizeOnIdleScenario(*this, 120.0f, 200.0f);
}

/**
 * @tc.name: EmptyDataWithHeaderFooterTotal001
 * @tc.desc: Body-local contract: with zero data items the section total is exactly headerMainSize_ + footerMainSize_,
 *           and the edges still lay out (header at top, footer right below it).
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutHeaderFooterTest, EmptyDataWithHeaderFooterTotal001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateGridWithEdges(60.0f, 0, 40.0f);
    RunEmptyDataEdgesOnlyChecks(*this, 60.0f, 40.0f);
}

/**
 * @tc.name: StickyHeaderPinnedUnderScroll001
 * @tc.desc: Body-local contract (parity with LazyColumn): a sticky header stays pinned at the section top while the
 *           body scrolls, and stays active and sized. Sticky math uses section coords, independent of body-local
 *           item coords.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutHeaderFooterTest, StickyHeaderPinnedUnderScroll001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateGridWithEdges(40.0f, 40, 30.0f, StickyStyle::BOTH);
    RunStickyPinnedUnderScrollChecks(*this, 40.0f, -250.0f);
}

/**
 * @tc.name: FooterOnlyViewportKeepsBodyWindowEmpty001
 * @tc.desc: Body-local contract: with the viewport scrolled fully into the footer zone (past the body end), the lazy
 *           window must report "past the last item" (startIndex_ == totalItemCount). Clamping against the stale
 *           SECTION total instead of the body extent keeps the last row in the window by header+footer too long.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutHeaderFooterTest, FooterOnlyViewportKeepsBodyWindowEmpty001, TestSize.Level1)
{
    CreateScroll();
    // Footer (600) taller than the viewport so a footer-only viewport exists; 4 items = 2 rows in 2 lanes.
    CreateGridWithEdges(40.0f, 4, 600.0f);
    RunFooterOnlyViewportChecks(*this, 4, SCROLL_HEIGHT);
}

/**
 * @tc.name: EmptyBodyWithEdgesThenAddItems001
 * @tc.desc: With a previous frame holding only header+footer (body empty, section total > 0), adding the first data
 *           items while the viewport sits past the (unknown) body start must measure from item 0, not clamp to
 *           past-the-end. Guards the "body known" predicate against counting header/footer as measured body.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutHeaderFooterTest, EmptyBodyWithEdgesThenAddItems001, TestSize.Level1)
{
    CreateList();
    // 4 items in 2 lanes -> 2 rows; scroll and the data change land in the same flush.
    RunEmptyBodyThenAddItemsScenario<LazyGridLayoutModel>(*this, [this]() { CreateLazyGridLayout(); }, 40.0f, 30.0f,
        10, -50.0f, false, 4, ITEM_HEIGHT, 2 * ITEM_HEIGHT, true);
}

/**
 * @tc.name: EmptyBodyWithEdgesThenAddItemsOffscreen001
 * @tc.desc: SLIDING_WINDOW WaterFlow measures far-offscreen children, so here the viewport genuinely sits past the
 *           empty child's (unknown) body when its first data items arrive. The child must measure them from item 0
 *           and report the real section total, not clamp to past-the-end because last frame's header+footer made the
 *           section total positive.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutHeaderFooterTest, EmptyBodyWithEdgesThenAddItemsOffscreen001, TestSize.Level1)
{
    CreateWaterFlow(WaterFlowLayoutMode::SLIDING_WINDOW);
    // Gap 60 > header 40 keeps the child partially visible with the viewport top past its header.
    RunEmptyBodyThenAddItemsScenario<LazyGridLayoutModel>(*this, [this]() { CreateLazyGridLayout(); }, 40.0f, 30.0f,
        40, -60.0f, true, 4, ITEM_HEIGHT, 2 * ITEM_HEIGHT, false);
}

/**
 * @tc.name: CacheRecycleSentinelIsBodyLocal001
 * @tc.desc: CheckCacheRecycle's "everything scrolled past cacheStart" sentinel feeds body-local predict cursors, so
 *           it must use the body extent, not the stale section total.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutHeaderFooterTest, CacheRecycleSentinelIsBodyLocal001, TestSize.Level1)
{
    auto info = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    info->totalItemCount_ = 2;
    info->posMap_[0] = { 0, 0.0f, 100.0f };
    info->posMap_[1] = { 0, 100.0f, 200.0f };
    info->cachedStartIndex_ = 0;
    info->cacheStartPos_ = 325.0f; // body coords: both items fully before the cache window

    LazyGridLayoutAlgorithm algorithm(info);
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
HWTEST_F(LazyGridLayoutHeaderFooterTest, AdjustOffsetNeutralAndStaleClear001, TestSize.Level1)
{
    CreateScroll();
    CreateGridWithEdges(40.0f, 20, 30.0f);
    RunAdjustNeutralOnEdgeResizes(*this, 120.0f, 100.0f);
    RunEmptyDataClearsAdjustScenario(*this, 20);
}

/**
 * @tc.name: AdjustOffsetExcludesEdgesAcrossHeaderResize001
 * @tc.desc: UpdatePosMap with stable body coords must report {0,0}: both with unchanged edges and on a header-resize
 *           frame (headerMainSize_ already new while totalMainSize_ still holds the previous SECTION total).
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutHeaderFooterTest, AdjustOffsetExcludesEdgesAcrossHeaderResize001, TestSize.Level1)
{
    LazyGridLayoutInfo layoutInfo;
    layoutInfo.SetLanes(2);
    layoutInfo.SetSpace(10.0f);
    layoutInfo.SetTotalItemCount(6);
    layoutInfo.headerMainSize_ = 60.0f;
    layoutInfo.footerMainSize_ = 40.0f;
    layoutInfo.totalMainSize_ = 420.0f; // SECTION total: header 60 + body 320 + footer 40
    auto seedPosMap = [&layoutInfo]() {
        layoutInfo.SetPosMap(0, { 0, 0.0f, 100.0f });
        layoutInfo.SetPosMap(1, { 1, 0.0f, 100.0f });
        layoutInfo.SetPosMap(2, { 0, 110.0f, 210.0f });
        layoutInfo.SetPosMap(3, { 1, 110.0f, 210.0f });
        layoutInfo.SetPosMap(4, { 0, 220.0f, 320.0f });
        layoutInfo.SetPosMap(5, { 1, 220.0f, 320.0f });
    };
    seedPosMap();
    layoutInfo.UpdatePosMap(320.0f); // prev body = 420 - 60 - 40
    EXPECT_FLOAT_EQ(layoutInfo.totalMainSize_, 320.0f);
    EXPECT_FLOAT_EQ(layoutInfo.adjustOffset_.start, 0.0f);
    EXPECT_FLOAT_EQ(layoutInfo.adjustOffset_.end, 0.0f);

    // Header-resize frame: header already holds the new value, totalMainSize_ the stale previous section.
    layoutInfo.headerMainSize_ = 120.0f;
    layoutInfo.totalMainSize_ = 420.0f;
    seedPosMap();
    layoutInfo.UpdatePosMap(320.0f); // prev body, unaffected by the resize
    EXPECT_FLOAT_EQ(layoutInfo.totalMainSize_, 320.0f);
    EXPECT_FLOAT_EQ(layoutInfo.adjustOffset_.start, 0.0f);
    EXPECT_FLOAT_EQ(layoutInfo.adjustOffset_.end, 0.0f);
}
} // namespace OHOS::Ace::NG
