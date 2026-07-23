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

#include "grid_test_ng.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/scrollable/scrollable_test_utils.h"

#include "base/geometry/shape.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_with_options_layout_algorithm.h"

#define private public
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#undef private

namespace OHOS::Ace::NG {
namespace {
constexpr float ITEM_HEIGHT = 100.0f;
constexpr int32_t ITEM_COUNT = 40;
constexpr float GRID_ITEM_WIDTH = 180.0f;

PaddingProperty CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

RefPtr<ShapeRect> CreateCustomClipShape(float offsetY, float height)
{
    auto shape = AceType::MakeRefPtr<ShapeRect>();
    shape->SetWidth(Dimension(1.0f, DimensionUnit::PERCENT));
    shape->SetHeight(Dimension(height));
    shape->SetOffset(DimensionOffset(Dimension(0.0f), Dimension(offsetY)));
    return shape;
}

// The four scrollable layout algorithms. The clip-extension wiring lives in the shared
// GridLayoutBaseAlgorithm + each algorithm's Measure, so each kind must be exercised.
enum class LayoutKind { SCROLL, SCROLL_WITH_OPTIONS, IRREGULAR, CUSTOM };
} // namespace

// Dedicated fixture mirroring WaterFlowContentClipTest : public WaterFlowTestNg.
class GridContentClipTest : public GridTestNg {
protected:
    int32_t cbStart_ = -1;
    int32_t cbEnd_ = -1;

    void ConfigureLayout(GridModelNG& model, LayoutKind kind)
    {
        if (kind == LayoutKind::SCROLL) {
            return;
        }
        GridLayoutOptions opt;
        if (kind == LayoutKind::IRREGULAR) {
            opt.regularSize = GridItemSize { 1, 1 };
            opt.irregularIndexes = { 1, 3 };
            // GridItemSize is {rows, columns}. For a vertical grid, items must have rows > 1
            // to trigger SetIrregular(true) -> GridIrregularLayoutAlgorithm.
            opt.getSizeByIndex = [](int32_t) { return GridItemSize { 2, 1 }; };
        } else if (kind == LayoutKind::CUSTOM) {
            ConfigureCustomOptions(opt);
        }
        model.SetLayoutOptions(opt);
    }

    void ConfigureCustomOptions(GridLayoutOptions& opt)
    {
        constexpr int32_t crossCount = 2;
        opt.getStartIndexByOffset = [crossCount](float offset) -> GridStartLineInfo {
            if (offset < 0.0f) {
                return {
                    .startIndex = 0,
                    .startLine = 0,
                    .startOffset = 0 - offset,
                    .totalOffset = offset
                };
            }
            int32_t line = static_cast<int32_t>(offset / ITEM_HEIGHT);
            float startOffset = std::fmod(offset, ITEM_HEIGHT);
            return {
                .startIndex = line * crossCount,
                .startLine = line,
                .startOffset = 0 - startOffset,
                .totalOffset = offset
            };
        };
        opt.getStartIndexByIndex = [crossCount](int32_t idx) -> GridStartLineInfo {
            int32_t line = idx / crossCount;
            return {
                .startIndex = line * crossCount,
                .startLine = line,
                .startOffset = 0.0f,
                .totalOffset = line * ITEM_HEIGHT
            };
        };
    }

    void BuildClipGrid(LayoutKind kind, ContentClipMode mode, float bottomPadding, const RefPtr<ShapeRect>& shape)
    {
        cbStart_ = -1;
        cbEnd_ = -1;
        GridModelNG model = CreateGrid();
        model.SetColumnsTemplate("1fr 1fr");
        model.SetRowsGap(Dimension(0));
        model.SetColumnsGap(Dimension(0));
        model.SetOnScrollIndex([this](int32_t s, int32_t e) {
            cbStart_ = s;
            cbEnd_ = e;
        });
        ConfigureLayout(model, kind);
        if (bottomPadding > 0.0f) {
            layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, bottomPadding));
        }
        ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), mode, shape);
        CreateGridItems(ITEM_COUNT, GRID_ITEM_WIDTH, ITEM_HEIGHT);
        CreateDone();
    }

    // Content-only: report == active, fix offsets == 0.
    void VerifyContentOnly()
    {
        const auto& info = pattern_->GetGridLayoutInfo();
        EXPECT_EQ(cbStart_, info.reportStartIndex_);
        EXPECT_EQ(cbEnd_, info.reportEndIndex_);
        EXPECT_EQ(info.startFixOffset_, 0);
        EXPECT_EQ(info.endFixOffset_, 0);
        EXPECT_EQ(info.reportStartIndex_, info.startIndex_);
        EXPECT_EQ(info.reportEndIndex_, info.endIndex_);
    }

    // Extension: onScrollIndex reports content range; endIndex/reportEndIndex match expected.
    void VerifyClip(int32_t expectedEndIndex, int32_t expectedReportEnd)
    {
        const auto& info = pattern_->GetGridLayoutInfo();
        EXPECT_EQ(cbStart_, info.reportStartIndex_);
        EXPECT_EQ(cbEnd_, info.reportEndIndex_);
        EXPECT_EQ(info.endIndex_, expectedEndIndex);
        EXPECT_EQ(info.reportEndIndex_, expectedReportEnd);
        if (expectedEndIndex > expectedReportEnd) {
            ASSERT_TRUE(GetItem(info.endIndex_, false));
            EXPECT_TRUE(GetItem(info.endIndex_, false)->IsActive());
        }
    }
};

// ===================== Scroll layout =====================
HWTEST_F(GridContentClipTest, GridClipScrollContentOnly001, TestSize.Level1)
{
    BuildClipGrid(LayoutKind::SCROLL, ContentClipMode::CONTENT_ONLY, 0.0f, nullptr);
    VerifyContentOnly();
}

HWTEST_F(GridContentClipTest, GridClipScrollBoundary001, TestSize.Level1)
{
    BuildClipGrid(LayoutKind::SCROLL, ContentClipMode::BOUNDARY, 300.0f, nullptr);
    VerifyClip(7, 1);
}

HWTEST_F(GridContentClipTest, GridClipScrollCustom001, TestSize.Level1)
{
    auto shape = CreateCustomClipShape(0.0f, 900.0f);
    BuildClipGrid(LayoutKind::SCROLL, ContentClipMode::CUSTOM, 0.0f, shape);
    VerifyClip(17, 7);
}

// ===================== ScrollWithOptions layout =====================
HWTEST_F(GridContentClipTest, GridClipScrollWithOptionsContentOnly001, TestSize.Level1)
{
    BuildClipGrid(LayoutKind::SCROLL_WITH_OPTIONS, ContentClipMode::CONTENT_ONLY, 0.0f, nullptr);
    VerifyContentOnly();
}

HWTEST_F(GridContentClipTest, GridClipScrollWithOptionsBoundary001, TestSize.Level1)
{
    BuildClipGrid(LayoutKind::SCROLL_WITH_OPTIONS, ContentClipMode::BOUNDARY, 300.0f, nullptr);
    VerifyClip(7, 1);
}

HWTEST_F(GridContentClipTest, GridClipScrollWithOptionsCustom001, TestSize.Level1)
{
    auto shape = CreateCustomClipShape(0.0f, 900.0f);
    BuildClipGrid(LayoutKind::SCROLL_WITH_OPTIONS, ContentClipMode::CUSTOM, 0.0f, shape);
    VerifyClip(17, 7);
}

// ===================== Irregular layout =====================
HWTEST_F(GridContentClipTest, GridClipIrregularContentOnly001, TestSize.Level1)
{
    BuildClipGrid(LayoutKind::IRREGULAR, ContentClipMode::CONTENT_ONLY, 0.0f, nullptr);
    VerifyContentOnly();
}

HWTEST_F(GridContentClipTest, GridClipIrregularBoundary001, TestSize.Level1)
{
    BuildClipGrid(LayoutKind::IRREGULAR, ContentClipMode::BOUNDARY, 300.0f, nullptr);
    VerifyClip(5, 1);
}

HWTEST_F(GridContentClipTest, GridClipIrregularCustom001, TestSize.Level1)
{
    auto shape = CreateCustomClipShape(0.0f, 900.0f);
    BuildClipGrid(LayoutKind::IRREGULAR, ContentClipMode::CUSTOM, 0.0f, shape);
    VerifyClip(15, 5);
}

// ===================== Custom layout =====================
HWTEST_F(GridContentClipTest, GridClipCustomContentOnly001, TestSize.Level1)
{
    BuildClipGrid(LayoutKind::CUSTOM, ContentClipMode::CONTENT_ONLY, 0.0f, nullptr);
    VerifyContentOnly();
}

HWTEST_F(GridContentClipTest, GridClipCustomBoundary001, TestSize.Level1)
{
    BuildClipGrid(LayoutKind::CUSTOM, ContentClipMode::BOUNDARY, 300.0f, nullptr);
    VerifyClip(7, 1);
}

HWTEST_F(GridContentClipTest, GridClipCustomLayoutCustomClip001, TestSize.Level1)
{
    auto shape = CreateCustomClipShape(0.0f, 900.0f);
    BuildClipGrid(LayoutKind::CUSTOM, ContentClipMode::CUSTOM, 0.0f, shape);
    VerifyClip(17, 7);
}

// Custom layout: scrollToIndex must preserve the end extension. The custom layout
// always calls MeasureOnOffset after jump (line 478), and JumpToTargetOffset uses
// GetViewEndBound — so the extension should remain filled.
HWTEST_F(GridContentClipTest, GridClipCustomScrollToIndexEndExtension001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    ConfigureLayout(model, LayoutKind::CUSTOM);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    const auto& info0 = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info0.endFixOffset_, 300.0f);
    EXPECT_GT(info0.endIndex_, info0.reportEndIndex_);

    pattern_->ScrollToIndex(0, false, ScrollAlign::START);
    FlushUITasks();
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_GT(info.endIndex_, info.reportEndIndex_);
    ASSERT_TRUE(GetItem(info.endIndex_, false));
    EXPECT_TRUE(GetItem(info.endIndex_, false)->IsActive());
}

// Custom layout: top extension must keep items laid out after scrolling.
// FillBackward uses SkipLinesAboveView (which accounts for startFixOffset_) and
// FindStartingRow (fixed) — so items in the top extension should remain active.
HWTEST_F(GridContentClipTest, GridClipCustomTopPaddingScrollExtension001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    ConfigureLayout(model, LayoutKind::CUSTOM);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 200.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    const auto& info0 = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info0.startFixOffset_, 200.0f);
    EXPECT_EQ(info0.endFixOffset_, 300.0f);
    EXPECT_EQ(info0.startIndex_, 0);
    ASSERT_TRUE(GetItem(0, false));
    EXPECT_TRUE(GetItem(0, false)->IsActive());

    // Scroll down then jump back to top: both extensions must remain functional.
    UpdateCurrentOffset(ITEM_HEIGHT * 4);
    pattern_->ScrollToIndex(0, false, ScrollAlign::START);
    FlushUITasks();
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_GT(info.endIndex_, info.reportEndIndex_);
    ASSERT_TRUE(GetItem(0, false));
    EXPECT_TRUE(GetItem(0, false)->IsActive());
    ASSERT_TRUE(GetItem(info.endIndex_, false));
    EXPECT_TRUE(GetItem(info.endIndex_, false)->IsActive());
}

// ===================== cachedCount (requirement 3) =====================
HWTEST_F(GridContentClipTest, GridClipScrollCachedCount001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    model.SetCachedCount(1);
    ConfigureLayout(model, LayoutKind::SCROLL);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.endIndex_, 7);
    EXPECT_EQ(info.reportEndIndex_, 1);
    ASSERT_TRUE(GetItem(info.endIndex_, false));
    EXPECT_TRUE(GetItem(info.endIndex_, false)->IsActive());
}

HWTEST_F(GridContentClipTest, GridClipIrregularCachedCount001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    model.SetCachedCount(1);
    ConfigureLayout(model, LayoutKind::IRREGULAR);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.endIndex_, 5);
    EXPECT_EQ(info.reportEndIndex_, 1);
}

HWTEST_F(GridContentClipTest, GridClipCustomCachedCount001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    model.SetCachedCount(1);
    ConfigureLayout(model, LayoutKind::CUSTOM);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.endIndex_, 7);
    EXPECT_EQ(info.reportEndIndex_, 1);
    ASSERT_TRUE(GetItem(info.endIndex_, false));
    EXPECT_TRUE(GetItem(info.endIndex_, false)->IsActive());
}

// ===================== SAFE_AREA smoke =====================
HWTEST_F(GridContentClipTest, GridClipScrollSafeArea001, TestSize.Level1)
{
    BuildClipGrid(LayoutKind::SCROLL, ContentClipMode::SAFE_AREA, 0.0f, nullptr);
    FlushUITasks();
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(cbStart_, info.reportStartIndex_);
    EXPECT_EQ(cbEnd_, info.reportEndIndex_);
    EXPECT_EQ(info.reportEndIndex_, info.endIndex_);
}

// ===================== onScrollIndex stability on scroll (requirement 2) =====================
HWTEST_F(GridContentClipTest, GridClipScrollIndexStableOnScroll001, TestSize.Level1)
{
    BuildClipGrid(LayoutKind::SCROLL, ContentClipMode::BOUNDARY, 300.0f, nullptr);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().endIndex_, 7);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().reportEndIndex_, 1);

    UpdateCurrentOffset(ITEM_HEIGHT * 2);
    const auto& info = pattern_->GetGridLayoutInfo();
    // After scrolling, the end extension remains filled (UseCurrentLines measures
    // up to viewEndBound), but onScrollIndex still reports the content-area range.
    EXPECT_GT(info.endIndex_, info.reportEndIndex_);
    EXPECT_EQ(info.reportEndIndex_, 1);
    EXPECT_EQ(cbStart_, info.reportStartIndex_);
    EXPECT_EQ(cbEnd_, info.reportEndIndex_);
}

// ===================== Top (start) extension (requirement 1) =====================
HWTEST_F(GridContentClipTest, GridClipScrollTopPaddingExtension001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 200.0f, 0.0f, 0.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    const auto& info0 = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info0.startFixOffset_, 200.0f);

    UpdateCurrentOffset(ITEM_HEIGHT * 2);
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.reportStartIndex_, 0);
}

HWTEST_F(GridContentClipTest, GridClipCustomTopPaddingExtension001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    ConfigureLayout(model, LayoutKind::CUSTOM);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 200.0f, 0.0f, 0.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    EXPECT_EQ(pattern_->GetGridLayoutInfo().startFixOffset_, 200.0f);
    UpdateCurrentOffset(ITEM_HEIGHT * 2);
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.reportStartIndex_, 0);
}

// Irregular layout: top extension must keep items in the safeAreaPadding region laid out
// after scrolling. Without the FindStartingRow fix, SolveForward/SolveBackward ignore
// startFixOffset_ and incorrectly skip lines still inside the clip extension area.
HWTEST_F(GridContentClipTest, GridClipIrregularTopPaddingExtension001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    ConfigureLayout(model, LayoutKind::IRREGULAR);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 200.0f, 0.0f, 0.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    const auto& info0 = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info0.startFixOffset_, 200.0f);
    EXPECT_EQ(info0.startIndex_, 0);
    ASSERT_TRUE(GetItem(0, false));
    EXPECT_TRUE(GetItem(0, false)->IsActive());

    // Scroll down past item 0, then back up: items in the top extension area must remain
    // laid out (active). Without the fix, FindStartingRow -> SolveBackward uses targetLen =
    // currentOffset_ (without startFixOffset_), so the start line doesn't reach back into
    // the extension area and item 0 is dropped.
    UpdateCurrentOffset(ITEM_HEIGHT * 4);
    UpdateCurrentOffset(-ITEM_HEIGHT * 2);
    const auto& info = pattern_->GetGridLayoutInfo();
    // With the fix, FindStartingRow uses SkipLinesAboveView (which accounts for startFixOffset_)
    // so the start line stays at row 0 with a negative offset — items in the top extension area
    // remain laid out. Without the fix, SolveForward uses targetLen = -currentOffset_ (without
    // startFixOffset_), advancing the start line past row 0 and dropping item 0.
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    ASSERT_TRUE(GetItem(0, false));
    EXPECT_TRUE(GetItem(0, false)->IsActive());
}

// Irregular layout: scrollToIndex triggers MeasureOnJump -> FindRangeOnJump, which must
// fill the end extension. Without the fix, FindRangeOnJump uses mainSize (not
// GetViewEndBound) and MeasureOnJump doesn't call MeasureOnOffset when extensions are
// active, so the end extension is lost after jump.
HWTEST_F(GridContentClipTest, GridClipIrregularScrollToIndexEndExtension001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    ConfigureLayout(model, LayoutKind::IRREGULAR);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    const auto& info0 = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info0.endFixOffset_, 300.0f);
    EXPECT_GT(info0.endIndex_, info0.reportEndIndex_);

    // scrollToIndex triggers MeasureOnJump. The end extension must remain filled.
    pattern_->ScrollToIndex(0, false, ScrollAlign::START);
    FlushUITasks();
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_GT(info.endIndex_, info.reportEndIndex_);
    ASSERT_TRUE(GetItem(info.endIndex_, false));
    EXPECT_TRUE(GetItem(info.endIndex_, false)->IsActive());
}

// Irregular layout: scrollToIndex with START align must fill the start extension area.
// Items above the jump target that fit in startFixOffset_ must remain laid out (active).
// Without the fix, FindStartingRow NearZero case returns the current start without extending
// upward, and PrepareLineHeight for START only fills forward, so items in the top padding
// region are neither measured nor included in the visible range.
HWTEST_F(GridContentClipTest, GridClipIrregularScrollToIndexStartExtension001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    ConfigureLayout(model, LayoutKind::IRREGULAR);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 200.0f, 0.0f, 0.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    const auto& info0 = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info0.startFixOffset_, 200.0f);

    // scrollToIndex to a middle item with START align: the jump target lands at the content
    // top (currentOffset_ == 0). Items above that fit in startFixOffset_ (200px = 2 rows of
    // 100px) must be measured and included in the visible range.
    pattern_->ScrollToIndex(6, false, ScrollAlign::START);
    FlushUITasks();
    const auto& info = pattern_->GetGridLayoutInfo();
    // The start must extend above the jump target into the padding extension area,
    // producing a negative currentOffset_ and a startMainLineIndex_ below the jump line.
    EXPECT_LT(info.currentOffset_, 0.0f);
    // Items in the start extension area must be active.
    ASSERT_TRUE(GetItem(info.startIndex_, false));
    EXPECT_TRUE(GetItem(info.startIndex_, false)->IsActive());
}

// Irregular layout: scrollToIndex with START align after scrolling down must also fill
// the start extension area. This verifies the fix works when the jump originates from a
// scrolled state (matrix is pre-filled, then a jump resets the range).
HWTEST_F(GridContentClipTest, GridClipIrregularScrollToIndexStartExtensionAfterScroll001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    ConfigureLayout(model, LayoutKind::IRREGULAR);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 200.0f, 0.0f, 0.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    EXPECT_EQ(pattern_->GetGridLayoutInfo().startFixOffset_, 200.0f);

    // Scroll down first, then jump to a middle item. The start extension must still be filled.
    UpdateCurrentOffset(ITEM_HEIGHT * 6);
    pattern_->ScrollToIndex(8, false, ScrollAlign::START);
    FlushUITasks();
    const auto& info = pattern_->GetGridLayoutInfo();
    // The start must extend above the jump target, producing a negative offset.
    // The offset can exceed -startFixOffset_ when a multi-row irregular item forces
    // the start line further up to include the full item.
    EXPECT_LT(info.currentOffset_, 0.0f);
    EXPECT_LT(info.startMainLineIndex_, info.endMainLineIndex_);
    ASSERT_TRUE(GetItem(info.startIndex_, false));
    EXPECT_TRUE(GetItem(info.startIndex_, false)->IsActive());
}

// ===================== onScrollIndex non-negative (irregular items) =====================
// Multi-row irregular items store -itemIdx in continuation rows of gridMatrix_. Without
// abs(), SyncReportRange would report negative indices via onScrollIndex when a continuation
// row is the first or last visible row in the content area.

// Irregular layout: reportStartIndex_ must be non-negative when a continuation row is at
// the content start. Item 3 (2x1) starts at row 2; row 3 is its continuation (matrix value
// -3). Scrolling 3 rows puts row 3 at content start. Without abs(), reportStartIndex_ = -3.
HWTEST_F(GridContentClipTest, GridClipIrregularReportStartNonNegative001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    model.SetOnScrollIndex([this](int32_t s, int32_t e) {
        cbStart_ = s;
        cbEnd_ = e;
    });
    ConfigureLayout(model, LayoutKind::IRREGULAR);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    // Scroll 3 rows: row 3 (continuation of item 3) lands at content start.
    UpdateCurrentOffset(ITEM_HEIGHT * 3);
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_GE(info.reportStartIndex_, 0);
    EXPECT_GE(info.reportEndIndex_, 0);
    EXPECT_GE(cbStart_, 0);
    EXPECT_GE(cbEnd_, 0);
}

// Irregular layout: reportEndIndex_ must be non-negative when a continuation row is the
// last visible row in the content area. Item 1 (2x1) starts at row 0; row 1 is its
// continuation (matrix value -1 at col 1). With bottom padding 300 (content height = 100),
// scrolling 1 row makes row 1 the only visible row. Without abs(), reportEndIndex_ = -1.
HWTEST_F(GridContentClipTest, GridClipIrregularReportEndNonNegative001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    model.SetOnScrollIndex([this](int32_t s, int32_t e) {
        cbStart_ = s;
        cbEnd_ = e;
    });
    ConfigureLayout(model, LayoutKind::IRREGULAR);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    // Scroll 1 row: row 1 (continuation of item 1 at col 1) is the only visible row.
    UpdateCurrentOffset(ITEM_HEIGHT);
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_GE(info.reportStartIndex_, 0);
    EXPECT_GE(info.reportEndIndex_, 0);
    EXPECT_GE(cbStart_, 0);
    EXPECT_GE(cbEnd_, 0);
}

// Scroll layout: reachStart_ clamp must allow items in the clip extension area to remain
// active after scrolling. The clamp only triggers when currentOffset_ exceeds the clip start
// bound (contentStartOffset_ - startFixOffset_), not for any negative offset.
HWTEST_F(GridContentClipTest, GridClipScrollReachStartClampExtension001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 200.0f, 0.0f, 0.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    EXPECT_EQ(pattern_->GetGridLayoutInfo().startFixOffset_, 200.0f);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0.0f);
    ASSERT_TRUE(GetItem(0, false));
    EXPECT_TRUE(GetItem(0, false)->IsActive());

    // Scroll down then jump back to top: verifies the reachStart_ clamp doesn't break
    // the extension layout. After returning to rest, item 0 must remain active.
    UpdateCurrentOffset(ITEM_HEIGHT * 4);
    pattern_->ScrollToIndex(0, false, ScrollAlign::START);
    FlushUITasks();
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.startFixOffset_, 200.0f);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.currentOffset_, 0.0f);
    ASSERT_TRUE(GetItem(0, false));
    EXPECT_TRUE(GetItem(0, false)->IsActive());
}

// Scroll layout: UseCurrentLines must measure items in the end extension area.
// After scrolling down and back up (which triggers UseCurrentLines via FillBlankAtStart),
// items in the end extension must remain active.
HWTEST_F(GridContentClipTest, GridClipScrollUseCurrentLinesEndExtension001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 200.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    const auto& info0 = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info0.startFixOffset_, 200.0f);
    EXPECT_EQ(info0.endFixOffset_, 300.0f);
    EXPECT_GT(info0.endIndex_, info0.reportEndIndex_);

    // Scroll down then back up: FillBlankAtStart adds lines at the top, triggering
    // UseCurrentLines to re-measure. The end extension must remain filled.
    UpdateCurrentOffset(ITEM_HEIGHT * 2);
    UpdateCurrentOffset(-ITEM_HEIGHT * 2);
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_GT(info.endIndex_, info.reportEndIndex_);
    ASSERT_TRUE(GetItem(info.endIndex_, false));
    EXPECT_TRUE(GetItem(info.endIndex_, false)->IsActive());
}

// ===================== Top rest position =====================
HWTEST_F(GridContentClipTest, GridClipScrollTopRestAtContentTop001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 200.0f, 0.0f, 0.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.startFixOffset_, 200.0f);
    EXPECT_EQ(info.currentOffset_, 0.0f);
    EXPECT_EQ(info.startIndex_, 0);
    ASSERT_TRUE(GetItem(0, false));
    EXPECT_TRUE(GetItem(0, false)->IsActive());
}

HWTEST_F(GridContentClipTest, GridClipScrollBackToFrontTopRest001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 200.0f, 0.0f, 0.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    UpdateCurrentOffset(ITEM_HEIGHT * 10);
    UpdateCurrentOffset(-ITEM_HEIGHT * 10);

    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.startFixOffset_, 200.0f);
}

// ===================== Report range consistency: both paddings =====================
HWTEST_F(GridContentClipTest, GridClipBothPaddingReportConsistent001, TestSize.Level1)
{
    constexpr float pad = 100.0f;
    // Phase 1: CONTENT_ONLY baseline.
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    model.SetOnScrollIndex([this](int32_t s, int32_t e) { cbStart_ = s; cbEnd_ = e; });
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, pad, 0.0f, pad));
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();
    UpdateCurrentOffset(ITEM_HEIGHT * 3);
    int32_t baseStart = pattern_->GetGridLayoutInfo().reportStartIndex_;
    int32_t baseEnd = pattern_->GetGridLayoutInfo().reportEndIndex_;

    // Phase 2: BOUNDARY with the same paddings and scroll delta.
    GridModelNG model2 = CreateGrid();
    model2.SetColumnsTemplate("1fr 1fr");
    model2.SetRowsGap(Dimension(0));
    model2.SetColumnsGap(Dimension(0));
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, pad, 0.0f, pad));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();
    UpdateCurrentOffset(ITEM_HEIGHT * 3);

    const auto& clipInfo = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(clipInfo.reportStartIndex_, baseStart);
    EXPECT_EQ(clipInfo.reportEndIndex_, baseEnd);
    EXPECT_GT(clipInfo.endIndex_, clipInfo.reportEndIndex_);
}

// ===================== Horizontal grid (rowsTemplate) =====================
HWTEST_F(GridContentClipTest, GridClipScrollHorizontalBoundary001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 300.0f, 0.0f)); // right padding -> end extension
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, ITEM_HEIGHT, GRID_ITEM_WIDTH); // width=100 (main), height=180 (cross)
    CreateDone();

    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.endIndex_, 5);
    EXPECT_EQ(info.reportEndIndex_, 1);
    ASSERT_TRUE(GetItem(info.endIndex_, false));
    EXPECT_TRUE(GetItem(info.endIndex_, false)->IsActive());
}

// ===================== CONTENT_ONLY with padding: no extension =====================
HWTEST_F(GridContentClipTest, GridClipScrollContentOnlyWithPadding001, TestSize.Level1)
{
    BuildClipGrid(LayoutKind::SCROLL, ContentClipMode::CONTENT_ONLY, 300.0f, nullptr);
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.startFixOffset_, 0);
    EXPECT_EQ(info.endFixOffset_, 0);
    EXPECT_EQ(info.endIndex_, 1);
    EXPECT_EQ(info.reportEndIndex_, 1);
}

// ===================== ScrollWithOptions cachedCount =====================
HWTEST_F(GridContentClipTest, GridClipScrollWithOptionsCachedCount001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    model.SetCachedCount(1);
    ConfigureLayout(model, LayoutKind::SCROLL_WITH_OPTIONS);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.endIndex_, 7);
    EXPECT_EQ(info.reportEndIndex_, 1);
    ASSERT_TRUE(GetItem(info.endIndex_, false));
    EXPECT_TRUE(GetItem(info.endIndex_, false)->IsActive());
}

// ===================== Irregular SAFE_AREA smoke =====================
HWTEST_F(GridContentClipTest, GridClipIrregularSafeArea001, TestSize.Level1)
{
    BuildClipGrid(LayoutKind::IRREGULAR, ContentClipMode::SAFE_AREA, 0.0f, nullptr);
    FlushUITasks();
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(cbStart_, info.reportStartIndex_);
    EXPECT_EQ(cbEnd_, info.reportEndIndex_);
    EXPECT_EQ(info.reportEndIndex_, info.endIndex_);
}

// ===================== Irregular onScrollIndex stability on scroll =====================
HWTEST_F(GridContentClipTest, GridClipIrregularIndexStableOnScroll001, TestSize.Level1)
{
    BuildClipGrid(LayoutKind::IRREGULAR, ContentClipMode::BOUNDARY, 300.0f, nullptr);
    UpdateCurrentOffset(ITEM_HEIGHT * 2);
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(cbStart_, info.reportStartIndex_);
    EXPECT_EQ(cbEnd_, info.reportEndIndex_);
}

// ===================== Custom onScrollIndex stability on scroll =====================
HWTEST_F(GridContentClipTest, GridClipCustomIndexStableOnScroll001, TestSize.Level1)
{
    BuildClipGrid(LayoutKind::CUSTOM, ContentClipMode::BOUNDARY, 300.0f, nullptr);
    UpdateCurrentOffset(ITEM_HEIGHT * 2);
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(cbStart_, info.reportStartIndex_);
    EXPECT_EQ(cbEnd_, info.reportEndIndex_);
}

// ===================== ReachEnd with extension =====================
HWTEST_F(GridContentClipTest, GridClipScrollReachEnd001, TestSize.Level1)
{
    auto shape = CreateCustomClipShape(0.0f, 500.0f); // clip extends beyond content
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CUSTOM, shape);
    CreateGridItems(4, 180, ITEM_HEIGHT); // 4 items, 2 rows, fits in viewport -> reachEnd at init
    CreateDone();

    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.reachEnd_, true);
    EXPECT_EQ(info.endIndex_, 3);
    EXPECT_EQ(info.reportEndIndex_, 3);
}

// ===================== Multi scroll cycle: no crash, report range correct =====================
HWTEST_F(GridContentClipTest, GridClipScrollMultiScrollCycle001, TestSize.Level1)
{
    BuildClipGrid(LayoutKind::SCROLL, ContentClipMode::BOUNDARY, 300.0f, nullptr);
    UpdateCurrentOffset(ITEM_HEIGHT * 5);
    UpdateCurrentOffset(-ITEM_HEIGHT * 3);
    UpdateCurrentOffset(ITEM_HEIGHT * 8);
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(cbStart_, info.reportStartIndex_);
    EXPECT_EQ(cbEnd_, info.reportEndIndex_);
}

// ===================== Direct unit tests for new methods =====================

// --- SyncReportRange: content area [0, 400], 4 rows, items 0-7 ---
HWTEST_F(GridContentClipTest, GridClipSyncReportRangeAtTop001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.axis_ = Axis::VERTICAL;
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 3;
    info.currentOffset_ = 0.0;
    info.startFixOffset_ = 0.0f;
    info.endFixOffset_ = 0.0f;
    for (int32_t i = 0; i < 4; ++i) {
        info.lineHeightMap_[i] = ITEM_HEIGHT;
        info.gridMatrix_[i] = { { 0, i * 2 }, { 1, i * 2 + 1 } };
    }
    info.SyncReportRange(400.0f, 0.0f);
    EXPECT_EQ(info.reportStartIndex_, 0);
    EXPECT_EQ(info.reportEndIndex_, 7);
}

// --- SyncReportRange: scrolled (currentOffset_ < 0), report end accounts for offset ---
HWTEST_F(GridContentClipTest, GridClipSyncReportRangeScrolled001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.axis_ = Axis::VERTICAL;
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 5;
    info.currentOffset_ = -150.0; // 1.5 rows scrolled
    info.startFixOffset_ = 200.0f;
    info.endFixOffset_ = 0.0f;
    for (int32_t i = 0; i < 6; ++i) {
        info.lineHeightMap_[i] = ITEM_HEIGHT;
        info.gridMatrix_[i] = { { 0, i * 2 }, { 1, i * 2 + 1 } };
    }
    info.SyncReportRange(400.0f, 0.0f);
    // currentOffset_=-150: line 0 bottom=-50 (<0, skipped), line 1 bottom=50 (>0, report start=2).
    // remain=550: walk 6 lines(600), last with top<400 is line 5 (top=350). report end=11.
    EXPECT_EQ(info.reportStartIndex_, 2);
    EXPECT_EQ(info.reportEndIndex_, 11);
}

// --- CreateScrollLayoutAlgorithm: returns GridScrollLayoutAlgorithm when no options ---
HWTEST_F(GridContentClipTest, GridClipCreateScrollLayoutAlgorithm001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    auto algo = pattern_->CreateScrollLayoutAlgorithm(false, false, false, false);
    auto scroll = AceType::DynamicCast<GridScrollLayoutAlgorithm>(algo);
    EXPECT_TRUE(scroll != nullptr);
}

// --- CreateScrollLayoutAlgorithm: returns GridScrollWithOptionsLayoutAlgorithm when has options ---
HWTEST_F(GridContentClipTest, GridClipCreateScrollLayoutAlgorithmWithOptions001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GridLayoutOptions {});
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    auto algo = pattern_->CreateScrollLayoutAlgorithm(true, false, false, false);
    auto withOptions = AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(algo);
    EXPECT_TRUE(withOptions != nullptr);
}

// --- SetLayoutAlgorithmContentClip: sets BOUNDARY mode on algorithm ---
HWTEST_F(GridContentClipTest, GridClipSetLayoutAlgorithmContentClipBoundary001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    auto algo = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(pattern_->info_);
    pattern_->SetLayoutAlgorithmContentClip(algo);
    EXPECT_EQ(algo->contentClipMode_, ContentClipMode::BOUNDARY);
}

// --- SetLayoutAlgorithmContentClip: sets CUSTOM mode + shape on algorithm ---
HWTEST_F(GridContentClipTest, GridClipSetLayoutAlgorithmContentClipCustom001, TestSize.Level1)
{
    auto shape = CreateCustomClipShape(0.0f, 900.0f);
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CUSTOM, shape);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    auto algo = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(pattern_->info_);
    pattern_->SetLayoutAlgorithmContentClip(algo);
    EXPECT_EQ(algo->contentClipMode_, ContentClipMode::CUSTOM);
    EXPECT_TRUE(algo->clipShapeRect_ != nullptr);
}

// --- SetLayoutAlgorithmContentClip: no ContentClip -> resets safeAreaPad_ ---
HWTEST_F(GridContentClipTest, GridClipSetLayoutAlgorithmContentClipNone001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    pattern_->safeAreaPad_ = ExpandEdges { 10.0f, 10.0f, 10.0f, 10.0f };
    auto algo = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(pattern_->info_);
    pattern_->SetLayoutAlgorithmContentClip(algo);
    EXPECT_EQ(algo->contentClipMode_, ContentClipMode::CONTENT_ONLY);
    EXPECT_EQ(pattern_->safeAreaPad_.has_value(), false);
}

// --- PostponedTaskForIgnoreCustomized: returns true ---
HWTEST_F(GridContentClipTest, GridClipPostponedTaskForIgnoreCustomized001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::SAFE_AREA, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    EXPECT_EQ(pattern_->PostponedTaskForIgnoreCustomized(), true);
}

// --- PostponedTaskForIgnore: non-CONTENT_CLIP_SAFE_AREA -> default path, no crash ---
HWTEST_F(GridContentClipTest, GridClipPostponedTaskForIgnoreDefault001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::SAFE_AREA, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    pattern_->PostponedTaskForIgnore(LayoutSafeAreaBundleType::IGNORE_LAYOUT_SAFE_AREA);
    SUCCEED();
}

// --- PostponedTaskForIgnore: CONTENT_CLIP_SAFE_AREA -> sets safeAreaPad_ ---
HWTEST_F(GridContentClipTest, GridClipPostponedTaskForIgnoreSafeArea001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::SAFE_AREA, nullptr);
    CreateGridItems(ITEM_COUNT, 180, ITEM_HEIGHT);
    CreateDone();

    pattern_->safeAreaPad_.reset();
    pattern_->PostponedTaskForIgnore(LayoutSafeAreaBundleType::CONTENT_CLIP_SAFE_AREA);
    EXPECT_EQ(pattern_->safeAreaPad_.has_value(), true);
}
} // namespace OHOS::Ace::NG
