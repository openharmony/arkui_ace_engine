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
// Scroll offsets in item-line units so the step sequences stay
// self-documenting (one line equals ITEM_HEIGHT, per the G.CNS.02
// magic-number rule).
constexpr float SCROLL_TWO_LINES = ITEM_HEIGHT * 2;
constexpr float SCROLL_THREE_LINES = ITEM_HEIGHT * 3;
// Gap-boundary scenario geometry: uniform rows with a nonzero rowsGap so the
// (height, height + gap] report-start boundary window is exercisable.
constexpr float BOUNDARY_ROW_HEIGHT = 50.0f;
constexpr float BOUNDARY_ROW_GAP = 10.0f;
// Steps through the window: exact bottom edge (one row height), then two
// half-gap increments landing mid-window and on the pitch boundary.
constexpr int32_t BOUNDARY_STEP_COUNT = 3;
constexpr float BOUNDARY_HALF_GAP_STEP = BOUNDARY_ROW_GAP / 2.0f;

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

enum class LayoutKind { SCROLL, SCROLL_WITH_OPTIONS, IRREGULAR };
} // namespace

// Extension scenario library: verifies the contentClip extension layout
// behavior itself (AC-1.1~1.5, AC-2.2, AC-3.1~3.3, AC-4.3). Unlike the parity
// suite, this file asserts the extension internals (layout fields / fix
// offsets / report ranges), while the parity suite only asserts
// developer-visible interface consistency.
class GridContentClipTest : public GridTestNg {
protected:
    int32_t cbStart_ = -1;
    int32_t cbEnd_ = -1;
    int32_t reachStartCount_ = 0;
    int32_t reachEndCount_ = 0;

    void ConfigureLayout(GridModelNG& model, LayoutKind kind)
    {
        if (kind == LayoutKind::SCROLL) {
            return;
        }
        GridLayoutOptions opt;
        if (kind == LayoutKind::IRREGULAR) {
            opt.regularSize = GridItemSize { 1, 1 };
            opt.irregularIndexes = { 1, 3 };
            opt.getSizeByIndex = [](int32_t) { return GridItemSize { 1, 2 }; };
        }
        model.SetLayoutOptions(opt);
    }

    void SetClip(ContentClipMode mode, const RefPtr<ShapeRect>& shape = nullptr)
    {
        ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), mode, shape);
    }

    // BuildGrid scenario knobs, bundled to keep the parameter list small
    // (G.FUN.01): the paddings activate the corresponding extension band,
    // cachedCount adds cache rows, withCallbacks installs the scroll
    // observers.
    struct BuildOptions {
        float bottomPadding = 0.0f;
        float topPadding = 0.0f;
        bool cachedCount = false;
        bool withCallbacks = true;
    };

    // Applies the BuildOptions knobs that need the model/property context:
    // scroll observers, extension-band paddings, cached count.
    void ApplyBuildOptions(GridModelNG& model, const BuildOptions& options)
    {
        if (options.withCallbacks) {
            model.SetOnScrollIndex([this](int32_t s, int32_t e) {
                cbStart_ = s;
                cbEnd_ = e;
            });
            model.SetOnReachStart([this]() { ++reachStartCount_; });
            model.SetOnReachEnd([this]() { ++reachEndCount_; });
        }
        if (options.bottomPadding > 0.0f) {
            layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, options.bottomPadding));
        }
        if (options.topPadding > 0.0f) {
            layoutProperty_->UpdatePadding(CreatePadding(0.0f, options.topPadding, 0.0f, 0.0f));
        }
        if (options.cachedCount) {
            model.SetCachedCount(1);
        }
    }

    void BuildGrid(LayoutKind kind, ContentClipMode mode, BuildOptions options)
    {
        cbStart_ = -1;
        cbEnd_ = -1;
        reachStartCount_ = 0;
        reachEndCount_ = 0;
        GridModelNG model = CreateGrid();
        model.SetColumnsTemplate("1fr 1fr");
        model.SetRowsGap(Dimension(0));
        model.SetColumnsGap(Dimension(0));
        ConfigureLayout(model, kind);
        ApplyBuildOptions(model, options);
        SetClip(mode);
        CreateGridItems(ITEM_COUNT, GRID_ITEM_WIDTH, ITEM_HEIGHT);
        CreateDone();
    }

    // Builds the gap-boundary scenario grid for the given kind: uniform
    // BOUNDARY_ROW_HEIGHT rows, BOUNDARY_ROW_GAP rowsGap, top padding 100, and
    // the kind's layout options (irregular gets a spanned item far below the
    // top so the boundary region stays uniform). withClip toggles BOUNDARY
    // contentClip (the set instance); the padding stays on the unset twin so
    // both instances share the same content geometry.
    void BuildGapBoundaryGrid(LayoutKind kind, bool withClip)
    {
        ClearOldNodes();
        GridModelNG model = CreateGrid();
        model.SetColumnsTemplate("1fr 1fr");
        model.SetRowsGap(Dimension(BOUNDARY_ROW_GAP));
        GridLayoutOptions opt;
        if (kind == LayoutKind::IRREGULAR) {
            opt.regularSize = GridItemSize { 1, 1 };
            opt.irregularIndexes = { 20 };
            opt.getSizeByIndex = [](int32_t) { return GridItemSize { 2, 1 }; };
            model.SetLayoutOptions(opt);
        } else if (kind == LayoutKind::SCROLL_WITH_OPTIONS) {
            opt.regularSize = GridItemSize { 1, 1 };
            model.SetLayoutOptions(opt);
        }
        layoutProperty_->UpdatePadding(CreatePadding(0.0f, 100.0f, 0.0f, 0.0f));
        if (withClip) {
            SetClip(ContentClipMode::BOUNDARY);
        }
        CreateGridItems(ITEM_COUNT, GRID_ITEM_WIDTH, BOUNDARY_ROW_HEIGHT);
        CreateDone();
    }

    // Scrolls through the boundary window (cumulative offsets 50 / 55 / 60 =
    // exact bottom edge, inside-window, pitch boundary) recording the reported
    // start index after each step.
    void RunGapBoundarySteps(int32_t reports[BOUNDARY_STEP_COUNT])
    {
        const float steps[BOUNDARY_STEP_COUNT] = { -BOUNDARY_ROW_HEIGHT,
            -BOUNDARY_HALF_GAP_STEP, -BOUNDARY_HALF_GAP_STEP };
        for (int32_t s = 0; s < BOUNDARY_STEP_COUNT; ++s) {
            UpdateCurrentOffset(steps[s]);
            reports[s] = pattern_->GetGridLayoutInfo().ReportStartIndex();
        }
    }

    // Inactive (unset/reset/DEFAULT/CONTENT_ONLY): fix offsets 0, report == active.
    void VerifyNoExtension()
    {
        const auto& info = pattern_->GetGridLayoutInfo();
        EXPECT_EQ(info.startFixOffset_, 0.0f);
        EXPECT_EQ(info.endFixOffset_, 0.0f);
        EXPECT_EQ(info.ReportStartIndex(), info.startIndex_);
        EXPECT_EQ(info.ReportEndIndex(), info.endIndex_);
    }

    // Extension active: extension items participate in layout (endIndex_
    // includes the extension area), report is the content-area range.
    void VerifyExtension(int32_t expectedEndIndex, int32_t expectedReportEnd)
    {
        const auto& info = pattern_->GetGridLayoutInfo();
        EXPECT_EQ(info.endIndex_, expectedEndIndex) << "active end index";
        EXPECT_EQ(info.ReportEndIndex(), expectedReportEnd) << "report end index";
        if (expectedEndIndex > expectedReportEnd) {
            auto item = GetItem(expectedEndIndex, false);
            ASSERT_TRUE(item);
            EXPECT_TRUE(item->IsActive()) << "extension item active";
        }
    }
};

// ===================== AC-1.1: BOUNDARY extension item layout =====================

HWTEST_F(GridContentClipTest, GridClipScrollBoundaryBottomExtension001, TestSize.Level1)
{
    BuildGrid(LayoutKind::SCROLL, ContentClipMode::BOUNDARY, { .bottomPadding = 300.0f });
    // Frame 400, bottom padding 300: the content area [0,100) holds only one
    // row (item0-1). The extension area [100,400) fills 3 more rows
    // (item2-7), so endIndex_ is 7 while the reported end stays at item1.
    VerifyExtension(7, 1);
    EXPECT_EQ(cbStart_, pattern_->GetGridLayoutInfo().ReportStartIndex());
    EXPECT_EQ(cbEnd_, pattern_->GetGridLayoutInfo().ReportEndIndex());
}

HWTEST_F(GridContentClipTest, GridClipIrregularBoundaryBottomExtension001, TestSize.Level1)
{
    BuildGrid(LayoutKind::IRREGULAR, ContentClipMode::BOUNDARY, { .bottomPadding = 300.0f });
    VerifyExtension(3, 0);
}

HWTEST_F(GridContentClipTest, GridClipScrollWithOptionsBoundaryBottomExtension001, TestSize.Level1)
{
    BuildGrid(LayoutKind::SCROLL_WITH_OPTIONS, ContentClipMode::BOUNDARY, { .bottomPadding = 300.0f });
    VerifyExtension(7, 1);
}

// ===================== AC-1.2: SAFE_AREA + safeAreaPadding extension =====================
// In SAFE_AREA mode the extension area is the SafeAreaPadding (the
// safeAreaPadding property expands the safe-area display region). The test
// environment has no system safe area (safeAreaPad=0), so the extension is
// activated through an explicit safeAreaPadding.

HWTEST_F(GridContentClipTest, GridClipScrollSafeAreaPaddingExtension001, TestSize.Level1)
{
    BuildGrid(LayoutKind::SCROLL, ContentClipMode::SAFE_AREA, {});
    // Explicit safeAreaPadding expands the safe-area display region (100 top/bottom)
    layoutProperty_->UpdateSafeAreaPadding(CreatePadding(0.0f, 100.0f, 0.0f, 100.0f));
    FlushUITasks();
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.startFixOffset_, 100.0f) << "SAFE_AREA start extension from safeAreaPadding";
    EXPECT_EQ(info.endFixOffset_, 100.0f) << "SAFE_AREA end extension from safeAreaPadding";
    EXPECT_GT(info.endIndex_, info.ReportEndIndex()) << "extension items laid out beyond content area";
}

HWTEST_F(GridContentClipTest, GridClipIrregularSafeAreaPaddingExtension001, TestSize.Level1)
{
    BuildGrid(LayoutKind::IRREGULAR, ContentClipMode::SAFE_AREA, {});
    layoutProperty_->UpdateSafeAreaPadding(CreatePadding(0.0f, 100.0f, 0.0f, 100.0f));
    FlushUITasks();
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.startFixOffset_, 100.0f);
    EXPECT_EQ(info.endFixOffset_, 100.0f);
    EXPECT_GT(info.endIndex_, info.ReportEndIndex());
}

// ===================== BOUNDARY + padding + safeAreaPadding combo =====================
// Layout behavior of BOUNDARY mode with both padding and safeAreaPadding:
// content area equals frame minus padding minus safeAreaPadding (safe-area
// layout counts into content size). The BOUNDARY extension spans from
// clip(frame) to the content area, covering the padding plus safeAreaPadding
// region.

HWTEST_F(GridContentClipTest, GridClipScrollBoundaryPaddingAndSafeAreaPadding001, TestSize.Level1)
{
    // padding 50/50 + safeAreaPadding 50/50: content area = 400-100-100 = 200
    BuildGrid(LayoutKind::SCROLL, ContentClipMode::BOUNDARY, { .bottomPadding = 50.0f, .topPadding = 50.0f });
    layoutProperty_->UpdateSafeAreaPadding(CreatePadding(0.0f, 50.0f, 0.0f, 50.0f));
    FlushUITasks();
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_GT(info.startFixOffset_, 0.0f) << "BOUNDARY start extension from padding+safeAreaPadding";
    EXPECT_GT(info.endFixOffset_, 0.0f) << "BOUNDARY end extension from padding+safeAreaPadding";
    // Extension items participate in layout (lineHeightMap_ contains extension rows)
    auto extItem = GetItem(info.endIndex_, false);
    ASSERT_TRUE(extItem);
    EXPECT_TRUE(extItem->IsActive()) << "extension item active";
}

// Without safeAreaPadding the SAFE_AREA extension stays inactive (the test
// environment has no system safe area)
HWTEST_F(GridContentClipTest, GridClipScrollSafeAreaNoPadNoExtension001, TestSize.Level1)
{
    BuildGrid(LayoutKind::SCROLL, ContentClipMode::SAFE_AREA, {});
    FlushUITasks();
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.startFixOffset_, 0.0f);
    EXPECT_EQ(info.endFixOffset_, 0.0f);
    EXPECT_EQ(info.endIndex_, info.ReportEndIndex());
}

// ===================== AC-1.3: CUSTOM shape extension =====================

HWTEST_F(GridContentClipTest, GridClipScrollCustomShapeExtension001, TestSize.Level1)
{
    auto shape = CreateCustomClipShape(0.0f, 900.0f);
    BuildGrid(LayoutKind::SCROLL, ContentClipMode::CUSTOM, {});
    // Re-set CUSTOM with a shape (BuildGrid passes a nullptr shape, which
    // gives CUSTOM no extension)
    SetClip(ContentClipMode::CUSTOM, shape);
    FlushUITasks();
    VerifyExtension(17, 7);
}

// ===================== Scope: user-defined (custom) layout excluded from the extension =====================
// GridCustomLayoutAlgorithm is out of the contentClip-extension scope: the mode
// is never injected by GridPattern, so an explicit clip value must leave the
// custom layout identical with the unset baseline (fix offsets 0, report range
// == active range, baseline fill).

HWTEST_F(GridContentClipTest, GridClipUserDefinedExcludedNoExtension001, TestSize.Level1)
{
    constexpr int32_t crossCount = 2;
    GridLayoutOptions opt;
    // Uniform 2-column grid callbacks emulating the scroll baseline by line pitch
    opt.getStartIndexByOffset = [crossCount](float offset) -> GridStartLineInfo {
        if (offset < 0.0f) {
            return { .startIndex = 0, .startLine = 0, .startOffset = 0 - offset, .totalOffset = offset };
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(opt);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 200.0f, 0.0f, 0.0f));
    SetClip(ContentClipMode::BOUNDARY);
    CreateGridItems(ITEM_COUNT, GRID_ITEM_WIDTH, ITEM_HEIGHT);
    CreateDone();
    VerifyNoExtension();
    // Baseline fill: the 200px content area (frame 400 minus top padding 200)
    // holds 2 rows of the 2-column grid
    EXPECT_EQ(pattern_->GetGridLayoutInfo().endIndex_, 3) << "baseline fill, no extension rows";
}

// ===================== AC-2.2: CONTENT_ONLY / unset has no extension =====================

HWTEST_F(GridContentClipTest, GridClipScrollContentOnlyNoExtension001, TestSize.Level1)
{
    BuildGrid(LayoutKind::SCROLL, ContentClipMode::CONTENT_ONLY, { .bottomPadding = 300.0f });
    VerifyNoExtension();
    EXPECT_EQ(pattern_->GetGridLayoutInfo().endIndex_, 1);
}

HWTEST_F(GridContentClipTest, GridClipDefaultNoExtension001, TestSize.Level1)
{
    BuildGrid(LayoutKind::SCROLL, ContentClipMode::DEFAULT, { .bottomPadding = 300.0f });
    VerifyNoExtension();
}

// ===================== AC-1.4: start extension stays laid out while scrolling up =====================

HWTEST_F(GridContentClipTest, GridClipScrollUpKeepsStartExtensionActive001, TestSize.Level1)
{
    BuildGrid(LayoutKind::IRREGULAR, ContentClipMode::BOUNDARY, { .topPadding = 200.0f });
    const auto& info0 = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info0.startFixOffset_, 200.0f);

    UpdateCurrentOffset(SCROLL_TWO_LINES);
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.ReportStartIndex(), 0);
    auto item0 = GetItem(0, false);
    ASSERT_TRUE(item0);
    EXPECT_TRUE(item0->IsActive()) << "start extension item stays active after scroll up";
}

// Scenario: Irregular first jumps into a never-measured middle area (index 30).
HWTEST_F(GridContentClipTest, GridClipIrregularFirstJumpTopExtensionBackfill001, TestSize.Level1)
{
    BuildGrid(LayoutKind::IRREGULAR, ContentClipMode::BOUNDARY, { .topPadding = 200.0f });
    ASSERT_GT(pattern_->GetGridLayoutInfo().startFixOffset_, 0.0f);

    ScrollToIndex(30, false, ScrollAlign::START);
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_LT(info.startIndex_, info.ReportStartIndex())
        << "first jump into uncached area must backfill top extension items";
    auto contentPos = info.GetItemPos(info.ReportStartIndex());
    ASSERT_NE(contentPos.second, -1);
    EXPECT_NE(info.lineHeightMap_.find(contentPos.second - 1), info.lineHeightMap_.end())
        << "line above content start must be measured after first jump";
    auto item = GetItem(info.startIndex_, false);
    ASSERT_TRUE(item);
    EXPECT_TRUE(item->IsActive());
    auto extRect = pattern_->GetItemRect(info.startIndex_);
    EXPECT_LT(extRect.Top(), 200.0f) << "extension item rect must intersect top extension area";
}

// ===================== AC-1.5: last item extension-only must not fire onReachEnd =====================

HWTEST_F(GridContentClipTest, GridClipReachEndBoundarySemantics001, TestSize.Level1)
{
    BuildGrid(LayoutKind::SCROLL, ContentClipMode::BOUNDARY, { .bottomPadding = 300.0f });
    EXPECT_EQ(reachEndCount_, 0) << "extension-only items must not fire onReachEnd";

    // After scrolling to the bottom (last item visible in the content area),
    // onReachEnd fires
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_GE(reachEndCount_, 1) << "onReachEnd fires when last item enters content area";
}

// ===================== AC-3.1: dynamic switch invariants =====================

HWTEST_F(GridContentClipTest, GridClipDynamicSwitchNoCallback001, TestSize.Level1)
{
    BuildGrid(LayoutKind::SCROLL, ContentClipMode::BOUNDARY, { .withCallbacks = false });
    cbStart_ = -1;
    cbEnd_ = -1;
    // Switch BOUNDARY -> CONTENT_ONLY at rest: no onScrollIndex fired
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CONTENT_ONLY, nullptr);
    FlushUITasks();
    EXPECT_EQ(cbStart_, -1) << "switch must not fire onScrollIndex";
    EXPECT_EQ(cbEnd_, -1);
}

HWTEST_F(GridContentClipTest, GridClipDynamicSwitchReportStable001, TestSize.Level1)
{
    BuildGrid(LayoutKind::SCROLL, ContentClipMode::BOUNDARY,
        { .bottomPadding = 300.0f, .withCallbacks = false });
    const auto& info0 = pattern_->GetGridLayoutInfo();
    int32_t reportStart0 = info0.ReportStartIndex();
    int32_t reportEnd0 = info0.ReportEndIndex();
    double to0 = pattern_->GetTotalOffset();

    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CONTENT_ONLY, nullptr);
    FlushUITasks();
    const auto& info1 = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info1.ReportStartIndex(), reportStart0) << "report start unchanged on switch";
    EXPECT_EQ(info1.ReportEndIndex(), reportEnd0) << "report end unchanged on switch";
    EXPECT_EQ(pattern_->GetTotalOffset(), to0) << "GetTotalOffset unchanged on switch";
}

// ===================== AC-4.3: repeat reporting never negative =====================

HWTEST_F(GridContentClipTest, GridClipRepeatReportNonNegative001, TestSize.Level1)
{
    GridModelNG model = CreateRepeatGrid(ITEM_COUNT, [](uint32_t) { return ITEM_HEIGHT; });
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(0));
    model.SetColumnsGap(Dimension(0));
    SetClip(ContentClipMode::BOUNDARY);
    CreateDone();
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_GE(info.ReportStartIndex(), 0) << "report start never negative";
    EXPECT_GE(info.ReportEndIndex(), -1) << "report end never below -1";
}

// ===================== F-8: report range must stay inside the content area =====================
// SyncReportRange's report ends (start/end) are bounded by the content area:
// with the end extension active, report end never falls onto items outside
// the content area; after scrolling down until the first row fully leaves
// the content area, report start excludes items above the content area.

// End extension active: item bottoms inside the report range must not
// exceed the content-area bottom; extension items stay active but never
// enter the report range. Note: use the initial layout state (plenty of
// items) — after scrolling to the absolute bottom the items are exhausted
// and the extension no longer holds items outside the content area.
HWTEST_F(GridContentClipTest, GridClipBottomExtensionReportEndWithinContent001, TestSize.Level1)
{
    // Bottom padding 300: content area = frame[0,100], extension = [100,400]
    BuildGrid(LayoutKind::SCROLL, ContentClipMode::BOUNDARY, { .bottomPadding = 300.0f });
    const auto& info = pattern_->GetGridLayoutInfo();
    ASSERT_GT(info.endIndex_, info.ReportEndIndex()) << "extension items must be active beyond content area";
    // Content-area bottom = frame 400 - bottom padding 300 = 100
    for (int32_t idx = info.ReportStartIndex(); idx <= info.ReportEndIndex(); ++idx) {
        auto rect = pattern_->GetItemRect(idx);
        EXPECT_LE(rect.Bottom(), 100.0f + 1.0f) << "reported item " << idx << " must stay within content area";
    }
    // First extension item beyond the reported end: active but its bottom is
    // outside the content area
    auto extRect = pattern_->GetItemRect(info.endIndex_);
    EXPECT_GE(extRect.Bottom(), 100.0f) << "extension-only item must lie beyond content area";
}

// Scroll down until the first row fully leaves the content area (top
// extension active): the reported start item's top must not be above the
// content-area top.
HWTEST_F(GridContentClipTest, GridClipScrollDownReportStartWithinContent001, TestSize.Level1)
{
    // Top padding 200: content area = frame[200,400], extension = [0,200)
    BuildGrid(LayoutKind::SCROLL, ContentClipMode::BOUNDARY, { .topPadding = 200.0f });
    UpdateCurrentOffset(SCROLL_THREE_LINES);
    const auto& info = pattern_->GetGridLayoutInfo();
    auto startRect = pattern_->GetItemRect(info.ReportStartIndex());
    EXPECT_GE(startRect.Top(), 200.0f - 1.0f)
        << "reported start item must not lie above content area (frame y=200)";
    for (int32_t idx = info.ReportStartIndex(); idx <= info.ReportEndIndex(); ++idx) {
        auto rect = pattern_->GetItemRect(idx);
        EXPECT_LE(rect.Bottom(), 400.0f + 1.0f) << "reported item " << idx << " must stay within content area";
    }
}

// ===================== Report-start boundary window with row gap =====================
// The report-start walk must mirror the unset-baseline anchor advance: a line
// is skipped only when the NEXT line's top passed the content-area top
// (bottom + mainGap <= 0), not when its own bottom edge passes it. With a row
// gap, a fully scrolled-out line whose gap still overlaps the content top
// stays reported until the anchor would advance past it — otherwise the
// extension instance would report the next line one frame earlier than the
// unset baseline inside the (height, height + gap] boundary window.

// Row height 50, rowsGap 10 (pitch 60): the boundary window is offsets
// (50, 60]. The walk must mirror EACH algorithm's own unset-anchor advance:
// - scroll / with-options (UpdateStartIndexForExtralOffset): the anchor keeps
//   a line until the NEXT line's top passes the content top, so the reported
//   start stays 0 through the window and advances at the pitch boundary (60);
// - irregular (solver SolveForward): the anchor advances once a line's bottom
//   passes the content top, so the reported start is already line 1 at 50.
// The per-algorithm set-vs-unset parity is the hard requirement; the concrete
// values differ between algorithm families by their pre-existing baseline
// semantics and must not be unified by the extension.
HWTEST_F(GridContentClipTest, GridClipReportStartGapBoundary001, TestSize.Level1)
{
    const LayoutKind kinds[] = { LayoutKind::SCROLL, LayoutKind::SCROLL_WITH_OPTIONS, LayoutKind::IRREGULAR };
    for (auto kind : kinds) {
        // Extension instance (BOUNDARY + top padding): report via the walk
        BuildGapBoundaryGrid(kind, true);
        ASSERT_GT(pattern_->GetGridLayoutInfo().startFixOffset_, 0.0f) << "extension must be active";
        int32_t setReports[BOUNDARY_STEP_COUNT] = { -1, -1, -1 };
        RunGapBoundarySteps(setReports);

        // Unset twin: same geometry and steps, report via the anchor fast path
        BuildGapBoundaryGrid(kind, false);
        int32_t unsetReports[BOUNDARY_STEP_COUNT] = { -1, -1, -1 };
        RunGapBoundarySteps(unsetReports);

        for (int32_t s = 0; s < BOUNDARY_STEP_COUNT; ++s) {
            EXPECT_EQ(setReports[s], unsetReports[s])
                << "kind " << static_cast<int>(kind) << " step " << s << ": set vs unset report mismatch";
        }
        if (kind == LayoutKind::IRREGULAR) {
            // Irregular anchor advances once the bottom passes the content top
            EXPECT_EQ(setReports[0], 2);
            EXPECT_EQ(setReports[1], 2);
            EXPECT_EQ(setReports[2], 2);
        } else if (kind == LayoutKind::SCROLL) {
            // Scroll anchor keeps the gap-straddling line until the pitch
            // boundary. SCROLL_WITH_OPTIONS gets only the parity assertions
            // above: with the GridIrregularLayoutEnabled flag on it routes to
            // the irregular algorithm and legitimately takes its strict rule.
            EXPECT_EQ(setReports[0], 0);
            EXPECT_EQ(setReports[1], 0);
            EXPECT_EQ(setReports[2], 2);
        }
    }
}

// ===================== C-4: stale extension state cleared after algorithm-family switch =====================
// The fix-offset reset relied on CalculateContentClipFixOffset (called inside
// Measure), but static/adaptive algorithms and Measure early-return paths
// (empty grid / zero main axis) bypass it — after switching from an
// extension-active scroll algorithm (fix>0) to dual templates (static
// algorithm), info_ must not keep stale fix offsets / report ranges.
// Implementation: ClearContentClipExtension at the matching
// GridPattern::CreateLayoutAlgorithm branches (algorithm objects are rebuilt
// every frame; an extension-active Measure recomputes right after).
HWTEST_F(GridContentClipTest, GridClipStaleExtensionClearedOnStaticSwitch001, TestSize.Level1)
{
    BuildGrid(LayoutKind::SCROLL, ContentClipMode::BOUNDARY, { .topPadding = 200.0f });
    const auto& info0 = pattern_->GetGridLayoutInfo();
    ASSERT_GT(info0.startFixOffset_, 0.0f) << "extension must be active before switch";

    // Also set rowsTemplate -> dual templates (columnsTemplate already set)
    // -> static algorithm (extension-unaware)
    layoutProperty_->UpdateRowsTemplate("1fr 1fr");
    FlushUITasks();
    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.startFixOffset_, 0.0f) << "stale fix offset must be cleared on algorithm switch";
    EXPECT_EQ(info.endFixOffset_, 0.0f) << "stale fix offset must be cleared on algorithm switch";
    EXPECT_EQ(info.ReportStartIndex(), info.startIndex_) << "report range must track layout range";
    EXPECT_EQ(info.ReportEndIndex(), info.endIndex_) << "report range must track layout range";
}

// The same choke point also covers the switch to an EMPTY user-defined grid:
// with the scroll algorithm's extension active (fix offsets > 0), emptying the
// grid and installing the custom callbacks at runtime switches the algorithm to
// the out-of-scope custom one, whose Measure early-returns on childrenCount<=0
// before CalculateContentClipFixOffset's reset — the extension state must be
// cleared at algorithm creation (C-4), not left stale in info_.
HWTEST_F(GridContentClipTest, GridClipEmptyGridNoStaleExtension001, TestSize.Level1)
{
    // 1. Establish the extension state on the scroll algorithm
    BuildGrid(LayoutKind::SCROLL, ContentClipMode::BOUNDARY, { .topPadding = 200.0f });
    const auto& info0 = pattern_->GetGridLayoutInfo();
    ASSERT_GT(info0.startFixOffset_, 0.0f) << "extension must be active before switch";

    // 2. Empty the grid at runtime; an empty custom grid never reaches
    // CalculateContentClipFixOffset (Measure early-returns)
    while (!frameNode_->GetChildren().empty()) {
        frameNode_->RemoveChildAtIndex(static_cast<int32_t>(frameNode_->GetChildren().size()) - 1);
    }
    // 3. Switch to user-defined (both start-index callbacks present) at runtime
    GridLayoutOptions opt;
    opt.getStartIndexByIndex = [](int32_t) -> GridStartLineInfo { return {}; };
    opt.getStartIndexByOffset = [](float) -> GridStartLineInfo { return {}; };
    layoutProperty_->UpdateLayoutOptions(opt);
    FlushUITasks();

    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.startFixOffset_, 0.0f) << "stale fix offset must be cleared on switch to empty user-defined grid";
    EXPECT_EQ(info.endFixOffset_, 0.0f) << "stale fix offset must be cleared on switch to empty user-defined grid";
    EXPECT_EQ(info.ReportStartIndex(), info.startIndex_) << "report range must track layout range";
    EXPECT_EQ(info.ReportEndIndex(), info.endIndex_) << "report range must track layout range";
}

// ===================== M-3: SyncReportRange must not invert under extreme geometry =====================
// With all content above the content area (currentOffset_ far greater than
// mainSize) and the start extension active: report start resolves through
// continuation markers to the multi-row item's start (a head on an earlier
// row), while report end's geometric walk exhausts immediately and takes
// FindEndIdx of the current row (which skips continuation markers) — before
// the fix this produced an inverted range reportStart > reportEnd, so a
// defensive clamp is required.
HWTEST_F(GridContentClipTest, GridClipSyncReportRangeNoInversion001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.gridMatrix_ = {
        { 2, { { 1, 8 } } },                    // item 8 starts at row2
        { 3, { { 0, 5 }, { 1, -8 } } },          // row3: item5 and item8's continuation
    };
    info.lineHeightMap_ = { { 2, 50.0f }, { 3, 40.0f } };
    info.startMainLineIndex_ = 3;
    info.endMainLineIndex_ = 3;
    info.startIndex_ = 5;
    info.endIndex_ = 5;
    info.currentOffset_ = 500.0;   // no visible row in the content area (all above)
    info.startFixOffset_ = 100.0f; // extension active, slow path
    info.SyncReportRange(400.0f, 1.0f);
    EXPECT_EQ(info.ReportStartIndex(), 8) << "continuation resolution picks item 8 (starts row2)";
    EXPECT_GE(info.ReportEndIndex(), info.ReportStartIndex()) << "report range must not invert";
    EXPECT_EQ(info.ReportEndIndex(), 8) << "inverted end must clamp to start";
}

// ===================== ADR-2: fast path equals the geometric walk at fix 0 =====================
// With fix offsets of 0, SyncReportRange takes the fast path (report equals
// the active range). The geometric-walk branch would land on the same range
// in the negative-offset state where the start row sits partially above the
// content-area top: Measure advances startMainLineIndex_ once a line fully
// leaves the content area, so at fix 0 the start line is always at least
// partially visible and the start walk stops on it. Hand-derived walk for
// this fixture (line height 100, gap 20, mainSize 150, currentOffset -50):
// the start walk keeps row1 (its bottom reaches 50 below the content top),
// the end walk consumes row1 and row2 and stops there (report end item 5),
// and the no-end-extension trailing rule then extends the reported end
// through endIndex_ (item 7) — identical to the fast-path output.
HWTEST_F(GridContentClipTest, GridClipSyncReportRangeFastPathNegativeOffset001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
        { 2, { { 0, 4 }, { 1, 5 } } },
        { 3, { { 0, 6 }, { 1, 7 } } },
    };
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f }, { 3, 100.0f } };
    info.startMainLineIndex_ = 1;
    info.endMainLineIndex_ = 3;
    info.startIndex_ = 2;
    info.endIndex_ = 7;
    info.currentOffset_ = -50.0f; // start row partially above the content-area top

    info.SyncReportRange(150.0f, 20.0f);
    EXPECT_EQ(info.ReportStartIndex(), 2) << "fast path matches the start walk landing on row1";
    EXPECT_EQ(info.ReportEndIndex(), 7) << "fast path matches the end walk plus the trailing rule";
}

// ===================== R-10 contract: onScrollBarUpdate offset argument =====================
// The offset argument must be a VP-unit Dimension carrying the px->vp
// conversion of the content anchor (GetContentAnchorOffset == currentOffset_
// when no extension is active). A PX-unit dimension makes the ArkTS bridges
// (arkts_native_grid_bridge / grid_static_modifier) run ConvertToVp() again
// on a value already in vp, dividing it by dipScale a second time and
// shrinking the frontend-visible offset. Host dipScale is 1.0, so the value
// assertions pin the anchor semantics while the unit assertions are the
// regression guard.
HWTEST_F(GridContentClipTest, GridClipScrollBarUpdateOffsetUnitVp001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    int32_t fireCount = 0;
    Dimension captured(0.0f, DimensionUnit::AUTO);
    model.SetOnScrollBarUpdate([&fireCount, &captured](int32_t index, const Dimension& offset) {
        ++fireCount;
        captured = offset;
        return std::pair<std::optional<float>, std::optional<float>>();
    });
    CreateGridItems(ITEM_COUNT, GRID_ITEM_WIDTH, ITEM_HEIGHT);
    CreateDone();

    ASSERT_GT(fireCount, 0) << "onScrollBarUpdate must fire on initial layout";
    EXPECT_EQ(captured.Unit(), DimensionUnit::VP) << "offset argument must be a VP-unit dimension";
    EXPECT_FLOAT_EQ(captured.Value(), 0.0f) << "initial anchor is 0";

    // Half-line scroll keeps the offset mid-line: a full-line delta advances
    // startIndex_ and the layout normalizes currentOffset_ back to 0 before
    // the event dispatch, so the anchor would be 0 by design.
    constexpr float halfLine = ITEM_HEIGHT / 2;
    UpdateCurrentOffset(-halfLine);
    EXPECT_FLOAT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -halfLine) << "scroll delta applied";
    // Bounded convergence flush: a measure-break round defers event dispatch to
    // the next layout pass (same driver as the parity suite).
    for (int32_t round = 0; round < 3; ++round) {
        if (MockPipelineContext::GetCurrent()->IsDirtyLayoutNodesEmpty() && !pattern_->prevMeasureBreak_) {
            break;
        }
        MockPipelineContext::GetCurrent()->FlushUITasks();
    }
    EXPECT_GT(fireCount, 1) << "onScrollBarUpdate must fire again after scroll";
    EXPECT_EQ(captured.Unit(), DimensionUnit::VP) << "offset argument must stay VP-unit after scroll";
    EXPECT_FLOAT_EQ(captured.Value(), -halfLine) << "vp value equals the px anchor at dipScale 1";
}
} // namespace OHOS::Ace::NG
