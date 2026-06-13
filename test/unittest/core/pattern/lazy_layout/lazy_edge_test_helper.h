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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_EDGE_TEST_HELPER_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_EDGE_TEST_HELPER_H

#include <map>
#include <utility>

#include "gtest/gtest.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"

namespace OHOS::Ace::NG {

// Shared helpers for the lazy grid/column header-footer suites. Both components run the same scenarios
// against their own Model / Pattern types, so the scenario bodies are parameterized on the test fixture
// (public members: frameNode_, pattern_, layoutProperty_, scrollablePattern_, scrollableFrameNode_) and,
// where properties are set, on the Model type.

inline void CreateLazyTestEdge(float height)
{
    StackModelNG stackModel;
    stackModel.Create();
    ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
    ViewAbstract::SetHeight(CalcLength(height));
    ViewStackProcessor::GetInstance()->Pop();
}

inline void AddLazyTestItemsAt(const RefPtr<FrameNode>& host, int32_t count, float height)
{
    for (int32_t i = 0; i < count; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(1, DimensionUnit::PERCENT));
        ViewAbstract::SetHeight(CalcLength(height));
        auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        host->AddChild(itemNode, 1 + i);
    }
}

// Build a lazy layout (createLazy provides the component) with header / content / footer inside an
// already-created scrollable container, then finish the view stack.
template<typename ModelT, typename TestT, typename CreateLazyF>
void CreateLazyWithEdges(TestT& t, CreateLazyF&& createLazy, float headerHeight, int32_t itemCount,
    float footerHeight, StickyStyle sticky = StickyStyle::NONE)
{
    createLazy();
    if (sticky != StickyStyle::NONE) {
        ModelT::SetSticky(sticky);
    }
    ModelT::SetHeader([headerHeight]() { CreateLazyTestEdge(headerHeight); });
    t.CreateContent(itemCount);
    ModelT::SetFooter([footerHeight]() { CreateLazyTestEdge(footerHeight); });
    t.CreateDone();
    ASSERT_NE(t.pattern_, nullptr);
}

// Resize one edge node and run a full relayout.
template<typename TestT>
void ResizeLazyEdge(TestT& t, const RefPtr<FrameNode>& edgeNode, float newHeight)
{
    edgeNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0f, DimensionUnit::PERCENT), CalcLength(newHeight)));
    edgeNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    t.frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    t.FlushUITasks();
}

// Toggling sticky at runtime must not drop the header: it stays sized/active and item 0 stays anchored at
// body 0 across BOTH -> NONE -> BOTH without a scroll.
template<typename ModelT, typename TestT>
void RunStickyToggleKeepsHeaderScenario(TestT& t, float headerHeight)
{
    ASSERT_NE(t.layoutProperty_, nullptr);
    auto headerNode = t.pattern_->GetHeaderNode();
    ASSERT_NE(headerNode, nullptr);
    EXPECT_TRUE(headerNode->IsActive());
    EXPECT_EQ(t.pattern_->GetHeaderMainSize(), headerHeight);
    EXPECT_EQ(t.pattern_->layoutInfo_->posMap_[0].startPos, 0.0f);

    for (auto sticky : { StickyStyle::NONE, StickyStyle::BOTH }) {
        t.layoutProperty_->CleanDirty();
        ModelT::SetSticky(AceType::RawPtr(t.frameNode_), sticky);
        t.frameNode_->MarkDirtyNode(t.layoutProperty_->GetPropertyChangeFlag());
        t.FlushUITasks();
        EXPECT_EQ(t.pattern_->GetStickyStyle(), sticky);
        headerNode = t.pattern_->GetHeaderNode();
        ASSERT_NE(headerNode, nullptr);
        EXPECT_TRUE(headerNode->IsActive());
        EXPECT_EQ(t.pattern_->GetHeaderMainSize(), headerHeight);
        EXPECT_EQ(t.pattern_->layoutInfo_->posMap_[0].startPos, 0.0f);
    }
}

// posMap_ stores body coords: a header resize must not move any item's stored startPos/endPos; only the
// layout-time +headerMainSize_ screen offset changes.
template<typename TestT>
void RunBodyLocalPosMapInvariantOnHeaderResize(TestT& t, float grownHeader)
{
    auto headerNode = t.pattern_->GetHeaderNode();
    ASSERT_NE(headerNode, nullptr);
    std::map<int32_t, std::pair<float, float>> beforeCoords;
    for (const auto& [idx, pos] : t.pattern_->layoutInfo_->posMap_) {
        beforeCoords[idx] = { pos.startPos, pos.endPos };
    }
    ASSERT_FALSE(beforeCoords.empty());

    ResizeLazyEdge(t, headerNode, grownHeader);

    ASSERT_EQ(t.pattern_->GetHeaderMainSize(), grownHeader);
    for (const auto& [idx, coords] : beforeCoords) {
        ASSERT_TRUE(t.pattern_->layoutInfo_->posMap_.count(idx)) << "item " << idx << " dropped from posMap";
        const auto& now = t.pattern_->layoutInfo_->posMap_.at(idx);
        EXPECT_FLOAT_EQ(now.startPos, coords.first) << "item " << idx << " startPos must be body-local invariant";
        EXPECT_FLOAT_EQ(now.endPos, coords.second) << "item " << idx << " endPos must be body-local invariant";
    }
}

// Zero data items: section total == header + footer and the edges lay out in order (header, then footer).
template<typename TestT>
void RunEmptyDataEdgesOnlyChecks(TestT& t, float headerHeight, float footerHeight)
{
    EXPECT_FLOAT_EQ(t.pattern_->layoutInfo_->totalMainSize_, headerHeight + footerHeight);
    EXPECT_EQ(t.pattern_->GetHeaderMainSize(), headerHeight);
    EXPECT_EQ(t.pattern_->GetFooterMainSize(), footerHeight);
    EXPECT_FLOAT_EQ(t.GetChildY(t.frameNode_, 0), 0.0f);
    EXPECT_FLOAT_EQ(t.GetChildY(t.frameNode_, 1), headerHeight);
}

// A sticky header stays pinned (same screen position), active and sized while the body scrolls.
template<typename TestT>
void RunStickyPinnedUnderScrollChecks(TestT& t, float headerHeight, float scrollDelta)
{
    ASSERT_NE(t.scrollablePattern_, nullptr);
    auto headerNode = t.pattern_->GetHeaderNode();
    ASSERT_NE(headerNode, nullptr);
    const float pinnedScreenY = t.GetChildY(t.scrollableFrameNode_, 0) + t.GetChildY(t.frameNode_, 0);

    t.scrollablePattern_->UpdateCurrentOffset(scrollDelta, SCROLL_FROM_UPDATE);
    t.FlushUITasks();

    EXPECT_TRUE(headerNode->IsActive());
    EXPECT_EQ(t.pattern_->GetHeaderMainSize(), headerHeight);
    EXPECT_TRUE(NearEqual(t.GetChildY(t.scrollableFrameNode_, 0) + t.GetChildY(t.frameNode_, 0), pinnedScreenY));
}

// Viewport fully inside the footer zone (past the body end): the lazy window must report past-the-last-item.
template<typename TestT>
void RunFooterOnlyViewportChecks(TestT& t, int32_t totalItemCount, float viewportHeight)
{
    ASSERT_NE(t.scrollablePattern_, nullptr);
    const float total = t.pattern_->layoutInfo_->totalMainSize_;
    t.scrollablePattern_->UpdateCurrentOffset(-(total - viewportHeight), SCROLL_FROM_UPDATE);
    t.FlushUITasks();
    EXPECT_EQ(t.pattern_->layoutInfo_->startIndex_, totalItemCount);
}

// Empty child (header+footer only) receives its first data items while the viewport sits past its (unknown)
// body start: it must measure from item 0 and report the real section total, not clamp to past-the-end.
// flushBeforeAdd distinguishes the same-flush (List) and separate-flush (SLIDING_WINDOW offscreen) variants;
// checkWindowStart is skipped for the offscreen variant where the child stays out of the visible window.
template<typename ModelT, typename TestT, typename CreateLazyF>
void RunEmptyBodyThenAddItemsScenario(TestT& t, CreateLazyF&& createLazy, float headerHeight, float footerHeight,
    int32_t fillerCount, float scrollDelta, bool flushBeforeAdd, int32_t addCount, float itemHeight,
    float expectedBodyHeight, bool checkWindowStart)
{
    createLazy();
    ModelT::SetHeader([headerHeight]() { CreateLazyTestEdge(headerHeight); });
    ModelT::SetFooter([footerHeight]() { CreateLazyTestEdge(footerHeight); });
    ViewStackProcessor::GetInstance()->Pop();
    auto emptyLazyNode = t.frameNode_;
    auto emptyLazyPattern = t.pattern_;
    createLazy(); // scrollable filler below
    t.CreateContent(fillerCount);
    t.CreateDone();

    ASSERT_NE(emptyLazyPattern, nullptr);
    EXPECT_FLOAT_EQ(emptyLazyPattern->layoutInfo_->totalMainSize_, headerHeight + footerHeight);

    t.scrollablePattern_->UpdateCurrentOffset(scrollDelta, SCROLL_FROM_UPDATE);
    if (flushBeforeAdd) {
        t.FlushUITasks();
    }
    AddLazyTestItemsAt(emptyLazyNode, addCount, itemHeight);
    emptyLazyNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    t.FlushUITasks();

    EXPECT_FLOAT_EQ(
        emptyLazyPattern->layoutInfo_->totalMainSize_, headerHeight + expectedBodyHeight + footerHeight);
    if (checkWindowStart) {
        EXPECT_EQ(emptyLazyPattern->layoutInfo_->startIndex_, 0);
        ASSERT_TRUE(emptyLazyPattern->layoutInfo_->posMap_.count(0));
        EXPECT_FLOAT_EQ(emptyLazyPattern->layoutInfo_->posMap_[0].startPos, 0.0f);
    }
}

// The empty-data measure path must clear a stale (unconsumed) adjustOffset_ instead of leaking it upward.
template<typename TestT>
void RunEmptyDataClearsAdjustScenario(TestT& t, int32_t itemCount)
{
    t.pattern_->layoutInfo_->adjustOffset_ = { 123.0f, 456.0f }; // simulate a stale unconsumed adjust
    for (int32_t i = 0; i < itemCount; i++) {
        t.frameNode_->RemoveChildAtIndex(1); // raw 1 = first data item
    }
    t.frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    t.FlushUITasks(t.frameNode_);

    EXPECT_EQ(t.pattern_->layoutInfo_->totalItemCount_, 0);
    EXPECT_FLOAT_EQ(t.pattern_->layoutInfo_->adjustOffset_.start, 0.0f);
    EXPECT_FLOAT_EQ(t.pattern_->layoutInfo_->adjustOffset_.end, 0.0f);
    // Scroll consumes adjustOffset on every measure: the stale value must not shift the scroll position.
    EXPECT_FLOAT_EQ(static_cast<float>(t.scrollablePattern_->GetTotalOffset()), 0.0f);
}

// Header resize driven only through the predictive self-measure pass: the section total must grow by exactly
// headerDelta with adjustOffset_ kept neutral.
template<typename TestT>
void RunHeaderResizeOnIdleScenario(TestT& t, float initialHeader, float grownHeader)
{
    const float totalBefore = t.pattern_->layoutInfo_->totalMainSize_;
    auto headerNode = t.pattern_->GetHeaderNode();
    ASSERT_NE(headerNode, nullptr);
    headerNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0f, DimensionUnit::PERCENT), CalcLength(grownHeader)));
    t.layoutProperty_->CleanDirty();
    t.frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    t.FlushIdleTask(t.pattern_);

    ASSERT_EQ(t.pattern_->GetHeaderMainSize(), grownHeader);
    EXPECT_FLOAT_EQ(t.pattern_->layoutInfo_->totalMainSize_, totalBefore + (grownHeader - initialHeader));
    EXPECT_FLOAT_EQ(t.pattern_->layoutInfo_->adjustOffset_.start, 0.0f);
    EXPECT_FLOAT_EQ(t.pattern_->layoutInfo_->adjustOffset_.end, 0.0f);
}

// Predictive (idle) frames must neither inflate the section total nor deactivate or move the sticky edges.
template<typename TestT>
void RunIdleStabilityChecks(TestT& t)
{
    auto headerNode = t.pattern_->GetHeaderNode();
    auto footerNode = t.pattern_->GetFooterNode();
    ASSERT_NE(headerNode, nullptr);
    ASSERT_NE(footerNode, nullptr);
    const float totalAfterLayout = t.pattern_->layoutInfo_->totalMainSize_;
    const float headerYBefore = t.GetChildY(t.frameNode_, 0);
    EXPECT_GT(totalAfterLayout, t.pattern_->GetHeaderMainSize() + t.pattern_->GetFooterMainSize());

    t.FlushIdleTask(t.pattern_);
    EXPECT_FLOAT_EQ(t.pattern_->layoutInfo_->totalMainSize_, totalAfterLayout);
    EXPECT_TRUE(headerNode->IsActive());
    EXPECT_TRUE(footerNode->IsActive());
    EXPECT_FLOAT_EQ(t.GetChildY(t.frameNode_, 0), headerYBefore);

    t.FlushIdleTask(t.pattern_);
    EXPECT_FLOAT_EQ(t.pattern_->layoutInfo_->totalMainSize_, totalAfterLayout);
}

// adjustOffset_ must stay {0,0} on the first layout (no parent anchor) and across pure header and footer
// resizes (edge slots are not body deltas).
template<typename TestT>
void RunAdjustNeutralOnEdgeResizes(TestT& t, float grownHeader, float grownFooter)
{
    EXPECT_FLOAT_EQ(t.pattern_->layoutInfo_->adjustOffset_.start, 0.0f);
    EXPECT_FLOAT_EQ(t.pattern_->layoutInfo_->adjustOffset_.end, 0.0f);

    auto headerNode = t.pattern_->GetHeaderNode();
    ASSERT_NE(headerNode, nullptr);
    ResizeLazyEdge(t, headerNode, grownHeader);
    ASSERT_EQ(t.pattern_->GetHeaderMainSize(), grownHeader);
    EXPECT_FLOAT_EQ(t.pattern_->layoutInfo_->adjustOffset_.start, 0.0f);
    EXPECT_FLOAT_EQ(t.pattern_->layoutInfo_->adjustOffset_.end, 0.0f);

    auto footerNode = t.pattern_->GetFooterNode();
    ASSERT_NE(footerNode, nullptr);
    ResizeLazyEdge(t, footerNode, grownFooter);
    ASSERT_EQ(t.pattern_->GetFooterMainSize(), grownFooter);
    EXPECT_FLOAT_EQ(t.pattern_->layoutInfo_->adjustOffset_.start, 0.0f);
    EXPECT_FLOAT_EQ(t.pattern_->layoutInfo_->adjustOffset_.end, 0.0f);
}

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_EDGE_TEST_HELPER_H
