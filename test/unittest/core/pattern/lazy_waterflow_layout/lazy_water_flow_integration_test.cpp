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

#include "lazy_water_flow_layout_test.h"

#include <algorithm>
#include <functional>
#include <utility>

#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"

// LazyWaterFlowLayoutTestBase forward-declares LayoutInfo / LayoutProperty in its
// header; these full-type includes are needed for RefPtr destruction and
// member access in this translation unit.
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_info.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_model.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_property.h"
#include "core/components_ng/pattern/list/list_item_group_model_ng.h"
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"

namespace OHOS::Ace::NG {
namespace {

// Item count chosen so the initial top-down measure leaves an unmaterialised
// tail. With LAZY_WATER_FLOW_SCROLL_HEIGHT=450 and 100 px items, a single-lane
// child holds ~4.5 items in view; 30 items × 100 px = 3000 px of content keeps
// a substantial unmaterialised tail across all four cases.
constexpr int32_t INTEGRATION_ITEM_COUNT = 30;

class LazyVWaterFlowParentIntegrationTest : public LazyWaterFlowLayoutTestBase {};

// Local mock builder mirroring lazy_water_flow_layout_test.cpp's
// LazyWaterFlowMockLazy (helpers there live in an anonymous namespace and are
// not externally visible). Kept minimal — only the operations these tests need:
// Supports front insert and erase cases covered below.
class IntegrationMockLazy : public Framework::MockLazyForEachBuilder {
public:
    explicit IntegrationMockLazy(int32_t count)
    {
        for (int32_t i = 0; i < count; ++i) {
            items_.push_back({ nextId_++, LAZY_WATER_FLOW_ITEM_HEIGHT });
        }
    }

    void Insert(int32_t index, float height)
    {
        index = std::clamp(index, 0, static_cast<int32_t>(items_.size()));
        items_.insert(items_.begin() + index, { nextId_++, height });
    }

    void Erase(int32_t index)
    {
        if (index < 0 || index >= static_cast<int32_t>(items_.size())) {
            return;
        }
        items_.erase(items_.begin() + index);
    }

    int32_t Count() const
    {
        return static_cast<int32_t>(items_.size());
    }

protected:
    int32_t OnGetTotalCount() override
    {
        return static_cast<int32_t>(items_.size());
    }

    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, NG::LazyForEachCacheChild>& expiringItems) override
    {
        ScopedViewStackProcessor scope;
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
        const float height = (index >= 0 && index < static_cast<int32_t>(items_.size()))
                                 ? items_[index].height
                                 : LAZY_WATER_FLOW_ITEM_HEIGHT;
        ViewAbstract::SetHeight(CalcLength(height));
        auto node = ViewStackProcessor::GetInstance()->Finish();
        const std::string key = (index >= 0 && index < static_cast<int32_t>(items_.size()))
                                    ? std::to_string(items_[index].id)
                                    : std::to_string(index);
        return { key, node };
    }

private:
    struct Item {
        int32_t id = 0;
        float height = 0.0f;
    };

    int32_t nextId_ = 0;
    std::vector<Item> items_;
};

void CreateFixedStack(float height)
{
    StackModelNG stackModel;
    stackModel.Create();
    ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
    ViewAbstract::SetHeight(CalcLength(height));
    ViewStackProcessor::GetInstance()->Pop();
}

void CreateLazyForEach(const RefPtr<IntegrationMockLazy>& builder, int32_t elmtId)
{
    RefPtr<LazyForEachActuator> actuator = builder;
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(elmtId);
    LazyForEachModelNG lazyForEachModel;
    lazyForEachModel.Create(actuator);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
}

RefPtr<LazyForEachNode> GetLazyForEachChild(const RefPtr<FrameNode>& host, int32_t childIdx)
{
    CHECK_NULL_RETURN(host, nullptr);
    return AceType::DynamicCast<LazyForEachNode>(host->GetChildAtIndex(childIdx));
}

void CreateFixedListItemGroup(float height)
{
    V2::ListItemGroupOptions groupOptions;
    ListItemGroupModelNG groupModel;
    groupModel.Create(groupOptions);
    ListItemModelNG itemModel;
    itemModel.Create();
    ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
    ViewAbstract::SetHeight(CalcLength(height));
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->Pop();
}

void CreateFixedListItemGroupWithFooter(float itemHeight, float footerHeight)
{
    V2::ListItemGroupOptions groupOptions;
    ListItemGroupModelNG groupModel;
    groupModel.Create(groupOptions);
    std::function<void()> footer = [footerHeight]() { CreateFixedStack(footerHeight); };
    groupModel.SetFooter(std::move(footer));
    ListItemModelNG itemModel;
    itemModel.Create();
    ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
    ViewAbstract::SetHeight(CalcLength(itemHeight));
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->Pop();
}

} // namespace

/**
 * @tc.name: ListParentBottomFillSettles_001
 * @tc.desc: Scrolling the parent List to the bottom must let the lazy child's
 *           tail materialise and then settle without leaking adjustOffset
 *           back into the parent's scroll math. Concretely:
 *             - ScrollToEdge(SCROLL_BOTTOM) makes endIndex_ reach the data
 *               tail and produces a non-zero parent offset;
 *             - re-issuing the same SCROLL_BOTTOM in steady state keeps the
 *               parent put and reports adjustOffset_.{start,end} == 0.
 *           No claim about which referenceEdge branch ran — the white-box
 *           proof of the END/START anchor algorithm lives in the single-test
 *           layer (EndAnchorAdjustOffset_*).
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowParentIntegrationTest, ListParentBottomFillSettles_001, TestSize.Level1)
{
    CreateList();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    auto builder = AceType::MakeRefPtr<IntegrationMockLazy>(INTEGRATION_ITEM_COUNT);
    CreateLazyForEach(builder, GetElmtId());
    CreateDone();
    ASSERT_NE(scrollablePattern_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(pattern_->layoutInfo_, nullptr);
    // Sanity: the initial top-down measure leaves an unmaterialised tail.
    ASSERT_LT(pattern_->layoutInfo_->endIndex_, INTEGRATION_ITEM_COUNT - 1);

    /**
     * @tc.steps: step1. ScrollToEdge(SCROLL_BOTTOM, false) on the parent List.
     * @tc.expected: Lazy child's visible window reaches the data tail; parent
     *           commits a non-zero offset.
     */
    scrollablePattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();

    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, INTEGRATION_ITEM_COUNT - 1);
    EXPECT_GT(scrollablePattern_->GetTotalOffset(), 0.0);
    const float bottomOffset = static_cast<float>(scrollablePattern_->GetTotalOffset());

    /**
     * @tc.steps: step2. Re-issue the same SCROLL_BOTTOM request in steady
     *           state (no data change, no resize).
     * @tc.expected: Parent offset is identical to step1's bottomOffset, and
     *           adjustOffset_.{start,end} == 0 — no spurious feedback. A
     *           future regression that mishandles the steady-state diff would
     *           visibly drift the parent here.
     */
    scrollablePattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();

    EXPECT_FLOAT_EQ(static_cast<float>(scrollablePattern_->GetTotalOffset()), bottomOffset);
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->adjustOffset_.start, 0.0f);
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->adjustOffset_.end, 0.0f);
}

/**
 * @tc.name: ScrollParentBottomFillSettles_001
 * @tc.desc: Scroll parent counterpart to the List bottom-fill case. A no-data
 *           bottom jump may materialise the lazy child's tail, but the child
 *           must not export that internal re-anchor back to Scroll as a
 *           parent-consumed adjustOffset.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowParentIntegrationTest, ScrollParentBottomFillSettles_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    auto builder = AceType::MakeRefPtr<IntegrationMockLazy>(INTEGRATION_ITEM_COUNT);
    CreateLazyForEach(builder, GetElmtId());
    CreateDone();
    ASSERT_NE(scrollablePattern_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(pattern_->layoutInfo_, nullptr);
    ASSERT_LT(pattern_->layoutInfo_->endIndex_, INTEGRATION_ITEM_COUNT - 1);

    scrollablePattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();

    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, INTEGRATION_ITEM_COUNT - 1);
    EXPECT_GT(scrollablePattern_->GetTotalOffset(), 0.0);
    const float bottomOffset = static_cast<float>(scrollablePattern_->GetTotalOffset());

    scrollablePattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();

    EXPECT_FLOAT_EQ(static_cast<float>(scrollablePattern_->GetTotalOffset()), bottomOffset);
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->adjustOffset_.start, 0.0f);
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->adjustOffset_.end, 0.0f);
}

/**
 * @tc.name: ListParentFrontDeleteKeepsLazyChildAtGroupBoundary_001
 * @tc.desc: In List { ListItemGroup; LazyVWaterFlowLayout { LazyForEach } }, deleting the lazy child's first
 *           visible item must not move the LazyVWaterFlow host down. The remaining items are already relaid
 *           out at y=0 in the child's local coordinates; a negative adjustOffset.start would make List apply
 *           an opposite host shift and leave a one-item gap below the group.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowParentIntegrationTest, ListParentFrontDeleteKeepsLazyChildAtGroupBoundary_001, TestSize.Level1)
{
    CreateList();
    CreateFixedListItemGroup(LAZY_WATER_FLOW_ITEM_HEIGHT);
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    auto builder = AceType::MakeRefPtr<IntegrationMockLazy>(INTEGRATION_ITEM_COUNT);
    CreateLazyForEach(builder, GetElmtId());
    CreateDone();

    ASSERT_NE(scrollablePattern_, nullptr);
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(pattern_->layoutInfo_, nullptr);
    ASSERT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    auto firstPosBefore = pattern_->layoutInfo_->GetPos(0);
    ASSERT_NE(firstPosBefore, nullptr);
    EXPECT_NEAR(firstPosBefore->startPos, 0.0f, 0.01f);
    const float hostYBefore = frameNode_->GetGeometryNode()->GetFrameOffset().GetY();
    EXPECT_NEAR(hostYBefore, LAZY_WATER_FLOW_ITEM_HEIGHT, 0.01f);

    auto lazyForEachNode = GetLazyForEachChild(frameNode_, 0);
    ASSERT_NE(lazyForEachNode, nullptr);
    builder->Erase(0);
    lazyForEachNode->OnDataDeleted(0);
    FlushUITasks();

    const float hostYAfter = frameNode_->GetGeometryNode()->GetFrameOffset().GetY();
    EXPECT_NEAR(hostYAfter, hostYBefore, 0.01f);
    ASSERT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    auto firstPosAfter = pattern_->layoutInfo_->GetPos(0);
    ASSERT_NE(firstPosAfter, nullptr);
    EXPECT_NEAR(firstPosAfter->startPos, 0.0f, 0.01f);
}

/**
 * @tc.name: ListParentFrontInsertKeepsLazyChildAfterGroupFooter_001
 * @tc.desc: In List { ListItemGroup(footer); LazyVWaterFlowLayout { LazyForEach } }, inserting one item before
 *           the lazy child's body start keeps the lazy host below the previous ListItemGroup footer and places the
 *           new item at the lazy body origin.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowParentIntegrationTest, ListParentFrontInsertKeepsLazyChildAfterGroupFooter_001,
    TestSize.Level1)
{
    CreateList();
    ListModelNG::SetSticky(AceType::RawPtr(scrollableFrameNode_), static_cast<int32_t>(V2::StickyStyle::BOTH));
    CreateFixedListItemGroupWithFooter(LAZY_WATER_FLOW_ITEM_HEIGHT, LAZY_WATER_FLOW_ITEM_HEIGHT / 2.0f);
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    auto builder = AceType::MakeRefPtr<IntegrationMockLazy>(INTEGRATION_ITEM_COUNT);
    CreateLazyForEach(builder, GetElmtId());
    CreateDone();

    ASSERT_NE(scrollablePattern_, nullptr);
    ASSERT_NE(scrollableFrameNode_, nullptr);
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(pattern_->layoutInfo_, nullptr);
    auto groupNode = AceType::DynamicCast<FrameNode>(scrollableFrameNode_->GetChildAtIndex(0));
    ASSERT_NE(groupNode, nullptr);
    ASSERT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    auto firstPosBefore = pattern_->layoutInfo_->GetPos(0);
    ASSERT_NE(firstPosBefore, nullptr);
    const auto groupFrameBefore = groupNode->GetGeometryNode();
    const auto lazyFrameBefore = frameNode_->GetGeometryNode();
    ASSERT_NE(groupFrameBefore, nullptr);
    ASSERT_NE(lazyFrameBefore, nullptr);
    const float groupBottomBefore =
        groupFrameBefore->GetFrameOffset().GetY() + groupFrameBefore->GetFrameSize().Height();
    const float lazyYBefore = lazyFrameBefore->GetFrameOffset().GetY();
    EXPECT_NEAR(lazyYBefore, groupBottomBefore, 0.01f);
    EXPECT_NEAR(lazyYBefore + firstPosBefore->startPos, groupBottomBefore, 0.01f);

    auto lazyForEachNode = GetLazyForEachChild(frameNode_, 0);
    ASSERT_NE(lazyForEachNode, nullptr);
    builder->Insert(0, LAZY_WATER_FLOW_ITEM_HEIGHT);
    lazyForEachNode->OnDataAdded(0);
    FlushUITasks();

    const auto groupFrameAfter = groupNode->GetGeometryNode();
    const auto lazyFrameAfter = frameNode_->GetGeometryNode();
    ASSERT_NE(groupFrameAfter, nullptr);
    ASSERT_NE(lazyFrameAfter, nullptr);
    const float groupBottomAfter =
        groupFrameAfter->GetFrameOffset().GetY() + groupFrameAfter->GetFrameSize().Height();
    const float lazyYAfter = lazyFrameAfter->GetFrameOffset().GetY();
    EXPECT_NEAR(lazyYAfter, groupBottomAfter, 0.01f);

    auto insertedPos = pattern_->layoutInfo_->GetPos(0);
    auto shiftedOldFirstPos = pattern_->layoutInfo_->GetPos(1);
    ASSERT_NE(insertedPos, nullptr);
    ASSERT_NE(shiftedOldFirstPos, nullptr);
    EXPECT_NEAR(lazyYAfter + insertedPos->startPos, groupBottomAfter, 0.01f);
    EXPECT_NEAR(shiftedOldFirstPos->startPos, insertedPos->endPos, 0.01f);
}

/**
 * @tc.name: ListParentTailDeleteShrinksBottom_001
 * @tc.desc: When the lazy child's tail item is deleted while parked at the
 *           bottom, the lazy child must:
 *             1. Track the new tail (endIndex_ = N-2);
 *             2. Shrink its reported totalMainSize_ by exactly one item's
 *                main size — this is the value the parent consumes for its
 *                scroll math, and was historically frozen by a stale
 *                maxHeight_ in CheckReset's past-window branch.
 *           Single-lane lazy child (1fr) makes the body shrink observable;
 *           a 2-lane uniform-height layout would have the OTHER lane still
 *           pinning total height after the delete, hiding the signal.
 *
 *           Note on parent observation: ArkUI's List does NOT auto-clamp its
 *           current offset when content shrinks underneath it (the parent
 *           keeps its absolute offset and silently enters over-scroll). So
 *           the parent's offset assertion is intentionally weak — only
 *           bounded — while the lazy child's totalMainSize_ shrink is the
 *           strong cross-component contract.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowParentIntegrationTest, ListParentTailDeleteShrinksBottom_001, TestSize.Level1)
{
    CreateList();
    CreateLazyWaterFlowLayout();
    // Single lane keeps the bookkeeping simple — the deleted item is the sole
    // tail in its lane. With 2 lanes uniform heights the OTHER lane still
    // pins bodyHeight, hiding the totalMainSize_ shrink signal entirely.
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    auto builder = AceType::MakeRefPtr<IntegrationMockLazy>(INTEGRATION_ITEM_COUNT);
    CreateLazyForEach(builder, GetElmtId());
    CreateDone();

    ASSERT_NE(scrollablePattern_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(pattern_->layoutInfo_, nullptr);

    scrollablePattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();
    ASSERT_EQ(pattern_->layoutInfo_->endIndex_, INTEGRATION_ITEM_COUNT - 1);
    const float lazyTotalBefore = pattern_->layoutInfo_->totalMainSize_,
        parentOffsetBefore = static_cast<float>(scrollablePattern_->GetTotalOffset());
    ASSERT_GT(lazyTotalBefore, 0.0f);
    auto lazyForEachNode = GetLazyForEachChild(frameNode_, 0);
    ASSERT_NE(lazyForEachNode, nullptr);
    const int32_t deletedIdx = builder->Count() - 1;
    builder->Erase(deletedIdx);
    lazyForEachNode->OnDataDeleted(deletedIdx);
    FlushUITasks();

    /**
     * @tc.expected: Three contract checks, ordered by signal strength:
     *   1. Lazy child's totalMainSize_ shrank by exactly one itemHeight —
     *      the strong contract this test guards. Failing this means a stale
     *      maxHeight_ regressed somewhere upstream.
     *   2. Visible window tracks the new tail (endIndex_ = N-2).
     *   3. Parent offset stays in a sane bounded range — no spurious jump
     *      from the lazy child. "Stay put" is acceptable (List does not
     *      auto-clamp on shrink).
     */
    const float lazyTotalAfter = pattern_->layoutInfo_->totalMainSize_,
        parentOffsetAfter = static_cast<float>(scrollablePattern_->GetTotalOffset());
    constexpr float kSubPixelSlack = 1.0f;

    EXPECT_NEAR(lazyTotalBefore - lazyTotalAfter, LAZY_WATER_FLOW_ITEM_HEIGHT, kSubPixelSlack);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, INTEGRATION_ITEM_COUNT - 2);

    const float parentDelta = parentOffsetBefore - parentOffsetAfter;
    EXPECT_GE(parentDelta, -kSubPixelSlack);
    EXPECT_LE(parentDelta, LAZY_WATER_FLOW_ITEM_HEIGHT + kSubPixelSlack);
}

/**
 * @tc.name: WaterFlowParentBottomFillSettles_001
 * @tc.desc: WaterFlow (sliding-window mode, single column) parent counterpart
 *           to the List bottom-fill case. Externally observable contract:
 *           tail reaches, parent stable on repeat SCROLL_BOTTOM, steady-state
 *           adjustOffset == 0.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowParentIntegrationTest, WaterFlowParentBottomFillSettles_001, TestSize.Level1)
{
    CreateWaterFlow(WaterFlowLayoutMode::SLIDING_WINDOW);
    WaterFlowModelNG::SetColumnsTemplate(AceType::RawPtr(scrollableFrameNode_), "1fr");
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    auto builder = AceType::MakeRefPtr<IntegrationMockLazy>(INTEGRATION_ITEM_COUNT);
    CreateLazyForEach(builder, GetElmtId());
    CreateDone();

    ASSERT_NE(scrollablePattern_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(pattern_->layoutInfo_, nullptr);
    ASSERT_LT(pattern_->layoutInfo_->endIndex_, INTEGRATION_ITEM_COUNT - 1);

    scrollablePattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();

    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, INTEGRATION_ITEM_COUNT - 1);
    EXPECT_GT(scrollablePattern_->GetTotalOffset(), 0.0);
    const float bottomOffset = static_cast<float>(scrollablePattern_->GetTotalOffset());

    scrollablePattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();

    EXPECT_FLOAT_EQ(static_cast<float>(scrollablePattern_->GetTotalOffset()), bottomOffset);
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->adjustOffset_.start, 0.0f);
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->adjustOffset_.end, 0.0f);
}

/**
 * @tc.name: WaterFlowParentFrontInsertKeepsVisiblePosition_001
 * @tc.desc: WaterFlow parent consumes LazyVWaterFlowLayout's data-change
 *           START adjust. Inserting at the lazy child's head should keep the
 *           old first item at the same viewport position instead of exposing
 *           a gap or double-consuming the offset.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowParentIntegrationTest, WaterFlowParentFrontInsertKeepsVisiblePosition_001, TestSize.Level1)
{
    CreateWaterFlow();
    WaterFlowModelNG::SetColumnsTemplate(AceType::RawPtr(scrollableFrameNode_), "1fr");
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    auto builder = AceType::MakeRefPtr<IntegrationMockLazy>(INTEGRATION_ITEM_COUNT);
    CreateLazyForEach(builder, GetElmtId());
    CreateDone();

    ASSERT_NE(scrollablePattern_, nullptr);
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(pattern_->layoutInfo_, nullptr);
    ASSERT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    auto firstPosBefore = pattern_->layoutInfo_->GetPos(0);
    ASSERT_NE(firstPosBefore, nullptr);
    const auto offsetBefore = static_cast<float>(scrollablePattern_->GetTotalOffset());
    EXPECT_FLOAT_EQ(offsetBefore, 0.0f);
    const auto firstViewportY = firstPosBefore->startPos - offsetBefore;

    auto lazyForEachNode = GetLazyForEachChild(frameNode_, 0);
    ASSERT_NE(lazyForEachNode, nullptr);
    builder->Insert(0, LAZY_WATER_FLOW_ITEM_HEIGHT);
    lazyForEachNode->OnDataAdded(0);
    FlushUITasks();

    const auto offsetAfter = static_cast<float>(scrollablePattern_->GetTotalOffset());
    auto insertedPos = pattern_->layoutInfo_->GetPos(0);
    auto shiftedFirstPos = pattern_->layoutInfo_->GetPos(1);
    ASSERT_NE(insertedPos, nullptr);
    ASSERT_NE(shiftedFirstPos, nullptr);
    EXPECT_FLOAT_EQ(offsetAfter, offsetBefore + LAZY_WATER_FLOW_ITEM_HEIGHT);
    EXPECT_FLOAT_EQ(insertedPos->startPos, 0.0f);
    EXPECT_FLOAT_EQ(insertedPos->endPos, LAZY_WATER_FLOW_ITEM_HEIGHT);
    EXPECT_FLOAT_EQ(shiftedFirstPos->startPos - offsetAfter, firstViewportY);
}

/**
 * @tc.name: WaterFlowParentTailDeleteShrinksBottom_001
 * @tc.desc: WaterFlow (sliding-window, single column) parent counterpart to
 *           the List tail-delete case. Same three contract checks: lazy
 *           child's totalMainSize_ shrank by itemHeight, visible window
 *           tracks new tail, parent offset stayed sane.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowParentIntegrationTest, WaterFlowParentTailDeleteShrinksBottom_001, TestSize.Level1)
{
    CreateWaterFlow(WaterFlowLayoutMode::SLIDING_WINDOW);
    WaterFlowModelNG::SetColumnsTemplate(AceType::RawPtr(scrollableFrameNode_), "1fr");
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    auto builder = AceType::MakeRefPtr<IntegrationMockLazy>(INTEGRATION_ITEM_COUNT);
    CreateLazyForEach(builder, GetElmtId());
    CreateDone();

    ASSERT_NE(scrollablePattern_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(pattern_->layoutInfo_, nullptr);

    scrollablePattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();
    ASSERT_EQ(pattern_->layoutInfo_->endIndex_, INTEGRATION_ITEM_COUNT - 1);
    const float lazyTotalBefore = pattern_->layoutInfo_->totalMainSize_;
    const float parentOffsetBefore = static_cast<float>(scrollablePattern_->GetTotalOffset());
    ASSERT_GT(lazyTotalBefore, 0.0f);

    auto lazyForEachNode = GetLazyForEachChild(frameNode_, 0);
    ASSERT_NE(lazyForEachNode, nullptr);
    const int32_t deletedIdx = builder->Count() - 1;
    builder->Erase(deletedIdx);
    lazyForEachNode->OnDataDeleted(deletedIdx);
    FlushUITasks();

    const float lazyTotalAfter = pattern_->layoutInfo_->totalMainSize_;
    const float parentOffsetAfter = static_cast<float>(scrollablePattern_->GetTotalOffset());
    constexpr float kSubPixelSlack = 1.0f;

    EXPECT_NEAR(lazyTotalBefore - lazyTotalAfter, LAZY_WATER_FLOW_ITEM_HEIGHT, kSubPixelSlack);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, INTEGRATION_ITEM_COUNT - 2);

    const float parentDelta = parentOffsetBefore - parentOffsetAfter;
    EXPECT_GE(parentDelta, -kSubPixelSlack);
    EXPECT_LE(parentDelta, LAZY_WATER_FLOW_ITEM_HEIGHT + kSubPixelSlack);
}

} // namespace OHOS::Ace::NG
