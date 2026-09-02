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
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float ITEM_HEIGHT = 100.0f;
constexpr int32_t ITEM_COUNT = 40;
constexpr float GRID_ITEM_WIDTH = 180.0f;
// Gap scenarios (section 12): rowsGap and columnsGap set together; the
// main-axis line pitch becomes ITEM_HEIGHT + GRID_GAP. GRID_GAP does not
// divide ITEM_HEIGHT, so fractional scroll offsets land mid-item or inside
// a gap instead of on line boundaries — exercising the gap-aware paths of
// the fillers, the report-range walk and the extension bounds.
constexpr float GRID_GAP = 20.0f;
// Scenario scroll distances, named in item-line units so the step sequences
// stay self-documenting (one line equals ITEM_HEIGHT, per the G.CNS.02
// magic-number rule).
constexpr float SCROLL_HALF_LINE = ITEM_HEIGHT / 2;
constexpr float SCROLL_TWO_LINES = ITEM_HEIGHT * 2;
constexpr float SCROLL_THREE_LINES = ITEM_HEIGHT * 3;
constexpr float SCROLL_FOUR_LINES = ITEM_HEIGHT * 4;
constexpr float SCROLL_FIVE_LINES = ITEM_HEIGHT * 5;
constexpr float SCROLL_TEN_LINES = ITEM_HEIGHT * 10;
// scrollToIndex targets: mid-grid for the alignment scenarios, near the end
// for the large-jump (TrySkipping) scenario.
constexpr int32_t JUMP_TARGET_INDEX = 10;
constexpr int32_t LARGE_JUMP_TARGET_INDEX = 30;
// Combined padding (top+bottom set together) must keep the content area
// non-empty: 100+100 < HEIGHT(400). Single-sided padding scenarios
// (PaddingParitySteps) reuse this value; a 100px extension is enough to
// activate the extension.
constexpr float PAD_TOP = 100.0f;
constexpr float PAD_BOTTOM = 100.0f;
// Combo scenario (padding and safeAreaPadding set together, BoundaryComboParitySteps)
constexpr float COMBO_PAD = 50.0f;
// FlushToStableLayout convergence round cap (exceeding it fails the test,
// preventing the test from masking endless re-measuring)
constexpr int32_t MAX_STABLE_ROUNDS = 3;

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

// The scrollable layout algorithms. The clip-extension wiring lives in the shared
// GridLayoutBaseAlgorithm + each algorithm's Measure, so each kind must be exercised.
enum class LayoutKind { SCROLL, SCROLL_WITH_OPTIONS, IRREGULAR };

// Parity mode under test. UNSET is the baseline instance that every other mode is
// compared against. All modes are asserted with the SAME full-field expectations
// (WP-4/F-3: no assertion exemption for extension modes).
enum class ParityMode { UNSET, DEFAULT, CONTENT_ONLY, BOUNDARY, SAFE_AREA, CUSTOM, RESET };

const ParityMode ALL_MODES[] = { ParityMode::DEFAULT, ParityMode::CONTENT_ONLY, ParityMode::BOUNDARY,
    ParityMode::SAFE_AREA, ParityMode::CUSTOM, ParityMode::RESET };

std::string ParityModeName(ParityMode mode)
{
    switch (mode) {
        case ParityMode::UNSET: return "UNSET";
        case ParityMode::DEFAULT: return "DEFAULT";
        case ParityMode::CONTENT_ONLY: return "CONTENT_ONLY";
        case ParityMode::BOUNDARY: return "BOUNDARY";
        case ParityMode::SAFE_AREA: return "SAFE_AREA";
        case ParityMode::CUSTOM: return "CUSTOM";
        case ParityMode::RESET: return "RESET";
        default: return "?";
    }
}
} // namespace

// Parity suite: two instances (contentClip set vs unset) driven through the
// same step sequence must match field-by-field on the developer-visible
// surface at every step (AC-4.1/R-10). WP-4 (F-3) rework notes:
//   1. every mode (including BOUNDARY/SAFE_AREA/CUSTOM) runs the same
//      full-field assertions, with no exemption branches;
//   2. FlushToStableLayout() gives base and mode the exact same bounded
//      layout-refresh strategy;
//   3. Surface captures the content-area report range
//      (ReportStartIndex/ReportEndIndex) plus per-item GetItemRect inside it,
//      instead of hard-comparing item0/item1 (they may be off-screen after
//      scrolling, which is not part of the content-area observable surface).
//   4. offset assertions only relax under the AC-3.3 extension
//      negative-offset rule (same source as onScrollBarUpdate). Everywhere
//      else they must be bit-identical.
class GridContentClipParityTest : public GridTestNg {
protected:
    int32_t cbStart_ = -1;
    int32_t cbEnd_ = -1;
    int32_t reachStartCount_ = 0;
    int32_t reachEndCount_ = 0;
    int32_t scrollStartCount_ = 0;
    int32_t scrollStopCount_ = 0;
    std::vector<float> frameBeginOffsets_;
    std::vector<std::pair<int32_t, float>> scrollBarUpdates_;
    // Diagnostic context (for SCOPED_TRACE): current parity mode and step index
    ParityMode activeMode_ = ParityMode::UNSET;
    int32_t activeStep_ = 0;
    // Estimation granularity allowance for the offset surfaces (see
    // ExpectOffsetValue): only the IRREGULAR kind reports GetTotalOffset /
    // GetCurrentOffset through GridLayoutInfo::GetIrregularOffset, an
    // average-line-height extrapolation over unmeasured lines. The extension
    // side legitimately measures one more line at the edges, and with gap the
    // extrapolation inputs (start line, known-line count, current offset)
    // drift by more than the pure extension bound. This is a calibration of
    // the tolerance for a heuristic surface — the real landing offset
    // (currentOffset_) stays within the extension bound — not an assertion
    // exemption: report ranges, item rects and scroll states remain compared
    // strictly everywhere.
    float offsetEstimateSlack_ = 0.0f;

    void ConfigureLayout(GridModelNG& model, LayoutKind kind, float mainGap = 0.0f)
    {
        if (kind == LayoutKind::SCROLL) {
            return;
        }
        GridLayoutOptions opt;
        if (kind == LayoutKind::IRREGULAR) {
            // rows=2 triggers irregular_ (vertical mode: only rowSpan>1
            // applies), so algorithm selection does not depend on the global
            // GridIrregularLayoutEnabled system property (other cases rewrite
            // it, causing algorithm drift and order dependence). Mistakenly
            // using columns>1 (no irregular_ in vertical mode) would silently
            // degrade this kind to SCROLL_WITH_OPTIONS and leave a coverage
            // hole in the four-algorithm matrix.
            opt.regularSize = GridItemSize { 1, 1 };
            opt.irregularIndexes = { 1, 3 };
            opt.getSizeByIndex = [](int32_t) { return GridItemSize { 2, 1 }; };
        }
        model.SetLayoutOptions(opt);
    }

    // Building several Grids in one case makes CreateGrid() claim the same
    // nodeId (=10000) and reuse the ElementRegister-cached FrameNode/pattern
    // (distorting the indexChanged detection in callbacks). Clear the
    // ElementRegister before each build so every instance gets its own
    // FrameNode/pattern.
    GridModelNG CreateParityGrid()
    {
        ClearOldNodes();
        return CreateGrid();
    }

    void SetMode(ParityMode mode)
    {
        if (mode == ParityMode::UNSET) {
            return;
        }
        auto* raw = AceType::RawPtr(frameNode_);
        switch (mode) {
            case ParityMode::DEFAULT:
                ScrollableModelNG::SetContentClip(raw, ContentClipMode::DEFAULT, nullptr);
                break;
            case ParityMode::CONTENT_ONLY:
                ScrollableModelNG::SetContentClip(raw, ContentClipMode::CONTENT_ONLY, nullptr);
                break;
            case ParityMode::BOUNDARY:
                ScrollableModelNG::SetContentClip(raw, ContentClipMode::BOUNDARY, nullptr);
                break;
            case ParityMode::SAFE_AREA:
                ScrollableModelNG::SetContentClip(raw, ContentClipMode::SAFE_AREA, nullptr);
                break;
            case ParityMode::CUSTOM:
                ScrollableModelNG::SetContentClip(raw, ContentClipMode::CUSTOM, CreateCustomClipShape(0.0f, 900.0f));
                break;
            case ParityMode::RESET:
                ScrollableModelNG::SetContentClip(raw, ContentClipMode::BOUNDARY, nullptr);
                ScrollableModelNG::ResetContentClip(raw);
                break;
            default:
                break;
        }
    }

    void ResetObservation()
    {
        cbStart_ = -1;
        cbEnd_ = -1;
        reachStartCount_ = 0;
        reachEndCount_ = 0;
        scrollStartCount_ = 0;
        scrollStopCount_ = 0;
        frameBeginOffsets_.clear();
        scrollBarUpdates_.clear();
    }

    void BuildGrid(GridModelNG& model, LayoutKind kind, ParityMode mode, bool topPad = false, bool bottomPad = false,
        bool cachedCount = false, bool skipItems = false, bool comboPads = false, float rowsGap = 0.0f,
        float colsGap = 0.0f)
    {
        ResetObservation();
        activeMode_ = mode;
        activeStep_ = 0;
        // Only the IRREGULAR kind reports offsets through the avg-height
        // extrapolation (GetIrregularOffset). The exact-offset kinds keep a
        // zero slack so their parity stays as strict as before.
        offsetEstimateSlack_ = (kind == LayoutKind::IRREGULAR) ? ITEM_HEIGHT + rowsGap : 0.0f;
        model.SetColumnsTemplate("1fr 1fr");
        model.SetRowsGap(Dimension(rowsGap));
        model.SetColumnsGap(Dimension(colsGap));
        model.SetOnScrollIndex([this](int32_t s, int32_t e) {
            cbStart_ = s;
            cbEnd_ = e;
        });
        model.SetOnReachStart([this]() { ++reachStartCount_; });
        model.SetOnReachEnd([this]() { ++reachEndCount_; });
        model.SetOnScrollStart([this]() { ++scrollStartCount_; });
        model.SetOnScrollStop([this]() { ++scrollStopCount_; });
        model.SetOnScrollFrameBegin([this](const Dimension&, ScrollState) {
            frameBeginOffsets_.emplace_back(0.0f);
            return ScrollFrameResult();
        });
        model.SetOnScrollBarUpdate([this](int32_t index, const Dimension& offset) {
            scrollBarUpdates_.emplace_back(index, static_cast<float>(offset.Value()));
            return std::pair<std::optional<float>, std::optional<float>>();
        });
        ConfigureLayout(model, kind, rowsGap);
        if (comboPads) {
            // padding and safeAreaPadding set together (combo scenario):
            // content area = frame - padding - safeAreaPadding
            // = 400 - 100 - 100 = 200 (non-empty).
            layoutProperty_->UpdatePadding(CreatePadding(0.0f, COMBO_PAD, 0.0f, COMBO_PAD));
            layoutProperty_->UpdateSafeAreaPadding(CreatePadding(0.0f, COMBO_PAD, 0.0f, COMBO_PAD));
        } else if (mode == ParityMode::SAFE_AREA) {
            // SAFE_AREA scenarios activate the extension via safeAreaPadding
            // (no padding — safe-area layout counts safeAreaPadding into the
            // content size, and stacking padding on top would empty the content
            // area). safeAreaPadding 100/100 makes the content area
            // equals frame minus 200, i.e. 200, matching the base (padding
            // 100/100). The extension area is the safeAreaPadding region,
            // with fix offsets of 100 on both sides.
            layoutProperty_->UpdateSafeAreaPadding(CreatePadding(0.0f, PAD_TOP, 0.0f, PAD_BOTTOM));
        } else if (topPad || bottomPad) {
            // top/bottom padding must be set in one call (two UpdatePadding
            // calls overwrite each other)
            layoutProperty_->UpdatePadding(
                CreatePadding(0.0f, topPad ? PAD_TOP : 0.0f, 0.0f, bottomPad ? PAD_BOTTOM : 0.0f));
        }
        if (cachedCount) {
            model.SetCachedCount(1);
        }
        SetMode(mode);
        if (!skipItems) {
            CreateGridItems(ITEM_COUNT, GRID_ITEM_WIDTH, ITEM_HEIGHT);
        }
        CreateDone();
        FlushToStableLayout();
    }

    // ===================== Stable-layout driver (WP-4 §10.2) =====================
    // base and mode run the exact same layout-refresh strategy: a bounded
    // convergence flush after each operation. Each round = one pipeline flush
    // without forced dirty (only advancing genuinely pending layout work:
    // async loading, the SAFE_AREA second pass, post-measure-break rounds).
    // The exit condition is no pending layout task and no measure break.
    // Extra flushes after convergence are no-ops for observable events (no
    // dirty nodes means no measure and no dispatch), so differing convergence
    // round counts on the two sides introduce no count differences.
    // Not converging within MAX_STABLE_ROUNDS fails directly, preventing the
    // test from masking endless re-measuring.

    bool HasPendingStableWork() const
    {
        auto pipeline = MockPipelineContext::GetCurrent();
        return !pipeline->IsDirtyLayoutNodesEmpty() || pattern_->prevMeasureBreak_;
    }

    void FlushToStableLayout()
    {
        ASSERT_TRUE(pattern_) << "FlushToStableLayout requires a live pattern";
        for (int32_t round = 0; round < MAX_STABLE_ROUNDS; ++round) {
            if (!HasPendingStableWork()) {
                return;
            }
            MockPipelineContext::GetCurrent()->FlushUITasks();
        }
        EXPECT_FALSE(HasPendingStableWork())
            << "layout did not converge within " << MAX_STABLE_ROUNDS << " rounds";
    }

    // Scenario step helper: operation + stable flush (base and mode replay
    // the exact same path in the two-phase driving).
    void ScrollByStep(float offset)
    {
        ++activeStep_;
        UpdateCurrentOffset(offset);
        FlushToStableLayout();
    }

    void ScrollToIndexStep(int32_t index, ScrollAlign align)
    {
        ++activeStep_;
        ScrollToIndex(index, false, align);
        FlushToStableLayout();
    }

    void ScrollToEdgeStep(ScrollEdgeType edge)
    {
        ++activeStep_;
        ScrollToEdge(edge, false);
        FlushToStableLayout();
    }

    void ScrollToStep(float position)
    {
        ++activeStep_;
        ScrollTo(position);
        FlushToStableLayout();
    }

    void ScrollPageStep(bool reverse)
    {
        ++activeStep_;
        ScrollPage(reverse, false);
        FlushToStableLayout();
    }

    // Snapshot of the developer-visible surface after a scenario step.
    struct Surface {
        int32_t cbStart = -1;
        int32_t cbEnd = -1;
        int32_t reachStartCount = 0;
        int32_t reachEndCount = 0;
        int32_t scrollStartCount = 0;
        int32_t scrollStopCount = 0;
        size_t frameBeginCount = 0;
        std::vector<std::pair<int32_t, float>> scrollBarUpdates;
        double totalOffset = 0.0;
        Offset currentOffset;
        bool isAtTop = false;
        bool isAtBottom = false;
        bool isAtTopWithDelta = false;
        bool isAtBottomWithDelta = false;
        int32_t accBegin = -1;
        int32_t accEnd = -1;
        // Content-area report range (ReportStartIndex/ReportEndIndex) plus
        // per-item geometry inside it (AC-4.1 "content-area item GetItemRect").
        // Hard-comparing item0/item1 is the wrong capture: after scrolling they
        // may be off-screen or exist only in the extension area, which is not
        // part of the content-area observable surface.
        int32_t reportStart = -1;
        int32_t reportEnd = -1;
        std::vector<std::pair<int32_t, Rect>> reportedItemRects;
        // Extension geometry (internal fields for the AC-3.3 bounded offset
        // rule in the extension negative-offset state; not developer-visible)
        float startFixOffset = 0.0f;
        float endFixOffset = 0.0f;
    };

    Surface CaptureSurface() const
    {
        Surface s;
        s.cbStart = cbStart_;
        s.cbEnd = cbEnd_;
        s.reachStartCount = reachStartCount_;
        s.reachEndCount = reachEndCount_;
        s.scrollStartCount = scrollStartCount_;
        s.scrollStopCount = scrollStopCount_;
        s.frameBeginCount = frameBeginOffsets_.size();
        s.scrollBarUpdates = scrollBarUpdates_;
        s.totalOffset = pattern_->GetTotalOffset();
        s.currentOffset = positionController_->GetCurrentOffset();
        s.isAtTop = pattern_->IsAtTop();
        s.isAtBottom = pattern_->IsAtBottom();
        s.isAtTopWithDelta = pattern_->IsAtTopWithDelta();
        s.isAtBottomWithDelta = pattern_->IsAtBottomWithDelta();
        s.accBegin = accessibilityProperty_->GetBeginIndex();
        s.accEnd = accessibilityProperty_->GetEndIndex();
        const auto& ginfo = pattern_->GetGridLayoutInfo();
        s.reportStart = ginfo.ReportStartIndex();
        s.reportEnd = ginfo.ReportEndIndex();
        for (int32_t idx = s.reportStart; idx >= 0 && idx <= s.reportEnd; ++idx) {
            s.reportedItemRects.emplace_back(idx, pattern_->GetItemRect(idx));
        }
        s.startFixOffset = ginfo.startFixOffset_;
        s.endFixOffset = ginfo.endFixOffset_;
        return s;
    }

    // onScrollBarUpdate assertion helper: equal counts + item-wise equal
    // indices (content-area semantics). Offset argument rule (spec AC-3.3
    // "top/bottom extension negative-offset state"): when the base is clamped
    // at the content-area boundary (top 0 / bottom max offset) while the mode
    // enters the extension area, the offset argument drifts accordingly — the
    // extension is part of the content display region and can be scrolled
    // into view (matching List/WaterFlow contentClip behavior). Rule: the
    // mode-vs-base offset difference must be <= the total extension size
    // (startFix plus endFix). Drift beyond the extension is a real defect
    // and fails. Indices are always compared strictly, item by item.
    void ExpectScrollBarUpdates(const Surface& base, const Surface& mode)
    {
        EXPECT_EQ(base.scrollBarUpdates.size(), mode.scrollBarUpdates.size()) << "onScrollBarUpdate count";
        for (size_t i = 0; i < base.scrollBarUpdates.size(); ++i) {
            EXPECT_EQ(base.scrollBarUpdates[i].first, mode.scrollBarUpdates[i].first)
                << "scrollBarUpdate index @" << i;
            const float baseOff = base.scrollBarUpdates[i].second;
            const float modeOff = mode.scrollBarUpdates[i].second;
            const float fixTotal = mode.startFixOffset + mode.endFixOffset;
            if (GreatNotEqual(fixTotal, 0.0f) && std::abs(modeOff - baseOff) <= fixTotal + 1.0f) {
                // Offset inside the extension (AC-3.3 negative-offset state): allowed, but the difference is bounded
                continue;
            }
            EXPECT_EQ(baseOff, modeOff) << "scrollBarUpdate offset @" << i;
        }
    }

    // AC-3.3 bounded rule for GetTotalOffset/GetCurrentOffset, same source as
    // the onScrollBarUpdate offset argument: bit-identical; in the extension
    // negative-offset state the difference is <= total extension size + 1px
    // (plus offsetEstimateSlack_ for the estimate-based IRREGULAR surface —
    // one line pitch, see the member comment for the calibration rationale).
    void ExpectOffsetValue(double baseVal, double modeVal, const Surface& mode, const char* what) const
    {
        const double diff = std::abs(modeVal - baseVal);
        const double fixTotal = mode.startFixOffset + mode.endFixOffset;
        if (GreatNotEqual(fixTotal, 0.0f) && diff <= fixTotal + 1.0 + offsetEstimateSlack_) {
            return; // extension negative-offset state (AC-3.3): bounded exception
        }
        EXPECT_EQ(baseVal, modeVal) << what;
    }

    void ExpectCurrentOffset(const Surface& base, const Surface& mode)
    {
        ExpectOffsetValue(base.currentOffset.GetX(), mode.currentOffset.GetX(), mode, "GetCurrentOffset x");
        ExpectOffsetValue(base.currentOffset.GetY(), mode.currentOffset.GetY(), mode, "GetCurrentOffset y");
    }

    // Full-field step-wise assertions (AC-4.1/R-10): every mode (including
    // BOUNDARY/SAFE_AREA/CUSTOM) runs the same assertion set with no exemption
    // branches (WP-4/F-3). Any difference exposed after removing the
    // exemptions is investigated as an implementation defect; it must not be
    // skipped again with a new conditional branch.
    void ExpectSurfaceEqual(const Surface& base, const Surface& mode)
    {
        SCOPED_TRACE("mode=" + ParityModeName(activeMode_) + " step=" + std::to_string(activeStep_));
        SCOPED_TRACE("base report=[" + std::to_string(base.reportStart) + "," + std::to_string(base.reportEnd) +
            "] fix=" + std::to_string(base.startFixOffset) + "/" + std::to_string(base.endFixOffset) +
            " | mode report=[" + std::to_string(mode.reportStart) + "," + std::to_string(mode.reportEnd) +
            "] fix=" + std::to_string(mode.startFixOffset) + "/" + std::to_string(mode.endFixOffset) +
            " totalOffset base=" + std::to_string(base.totalOffset) + " mode=" + std::to_string(mode.totalOffset));
        EXPECT_EQ(base.cbStart, mode.cbStart) << "onScrollIndex start";
        EXPECT_EQ(base.cbEnd, mode.cbEnd) << "onScrollIndex end";
        EXPECT_EQ(base.accBegin, mode.accBegin) << "GetBeginIndex";
        EXPECT_EQ(base.accEnd, mode.accEnd) << "GetEndIndex";
        EXPECT_EQ(base.reachStartCount, mode.reachStartCount) << "onReachStart count";
        EXPECT_EQ(base.reachEndCount, mode.reachEndCount) << "onReachEnd count";
        EXPECT_EQ(base.scrollStartCount, mode.scrollStartCount) << "onScrollStart count";
        EXPECT_EQ(base.scrollStopCount, mode.scrollStopCount) << "onScrollStop count";
        EXPECT_EQ(base.frameBeginCount, mode.frameBeginCount) << "onScrollFrameBegin count";
        ExpectScrollBarUpdates(base, mode);
        ExpectOffsetValue(base.totalOffset, mode.totalOffset, mode, "GetTotalOffset");
        ExpectCurrentOffset(base, mode);
        EXPECT_EQ(base.isAtTop, mode.isAtTop) << "IsAtTop";
        EXPECT_EQ(base.isAtBottom, mode.isAtBottom) << "IsAtBottom";
        EXPECT_EQ(base.isAtTopWithDelta, mode.isAtTopWithDelta) << "IsAtTopWithDelta";
        EXPECT_EQ(base.isAtBottomWithDelta, mode.isAtBottomWithDelta) << "IsAtBottomWithDelta";
        // Content-area report range: the extension side may activate extra
        // extension nodes, but extension items must not enter the report range.
        EXPECT_EQ(base.reportStart, mode.reportStart) << "report start (content area)";
        EXPECT_EQ(base.reportEnd, mode.reportEnd) << "report end (content area)";
        ASSERT_EQ(base.reportedItemRects.size(), mode.reportedItemRects.size()) << "reported rects size";
        for (size_t i = 0; i < base.reportedItemRects.size(); ++i) {
            EXPECT_EQ(base.reportedItemRects[i].first, mode.reportedItemRects[i].first)
                << "reported item index @" << i;
            EXPECT_TRUE(IsEqual(base.reportedItemRects[i].second, mode.reportedItemRects[i].second))
                << "reported item rect @ index " << base.reportedItemRects[i].first;
        }
    }
};

// ===================== 1. Initial layout parity (all modes x all algorithms) =====================

void InitialParitySteps(GridContentClipParityTest* fixture, ParityMode mode, LayoutKind kind)
{
    GridModelNG baseModel = fixture->CreateParityGrid();
    fixture->BuildGrid(baseModel, kind, ParityMode::UNSET, true, true);
    auto base = fixture->CaptureSurface();

    GridModelNG modeModel = fixture->CreateParityGrid();
    fixture->BuildGrid(modeModel, kind, mode, true, true);
    fixture->ExpectSurfaceEqual(base, fixture->CaptureSurface());
}

HWTEST_F(GridContentClipParityTest, GridParityScrollInitialAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        InitialParitySteps(this, mode, LayoutKind::SCROLL);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollWithOptionsInitialAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        InitialParitySteps(this, mode, LayoutKind::SCROLL_WITH_OPTIONS);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityIrregularInitialAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        InitialParitySteps(this, mode, LayoutKind::IRREGULAR);
    }
}

// ===================== 2. Scroll parity (small steps) =====================
// Two-phase driving: the base (UNSET) instance's full sequence must be
// captured before the mode instance is built; otherwise pattern_ already
// points at the mode instance and the base sequence would act on it
// (test-structure bug).

void ScrollParitySteps(GridContentClipParityTest* fixture, ParityMode mode, LayoutKind kind)
{
    // Scroll offsets in item-line units: forward two, back one, forward ten
    // (crosses the jump threshold), back three.
    const float steps[] = { SCROLL_TWO_LINES, -ITEM_HEIGHT, SCROLL_TEN_LINES, -SCROLL_THREE_LINES };
    std::vector<GridContentClipParityTest::Surface> baseSurfaces;
    GridModelNG baseModel = fixture->CreateParityGrid();
    fixture->BuildGrid(baseModel, kind, ParityMode::UNSET, true, true);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    for (float step : steps) {
        fixture->ScrollByStep(step);
        baseSurfaces.emplace_back(fixture->CaptureSurface());
    }

    GridModelNG modeModel = fixture->CreateParityGrid();
    fixture->BuildGrid(modeModel, kind, mode, true, true);
    size_t stepIdx = 0;
    fixture->ExpectSurfaceEqual(baseSurfaces[stepIdx++], fixture->CaptureSurface());
    for (float step : steps) {
        fixture->ScrollByStep(step);
        fixture->ExpectSurfaceEqual(baseSurfaces[stepIdx], fixture->CaptureSurface());
        ++stepIdx;
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollStepsAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        ScrollParitySteps(this, mode, LayoutKind::SCROLL);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollWithOptionsStepsAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        ScrollParitySteps(this, mode, LayoutKind::SCROLL_WITH_OPTIONS);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityIrregularStepsAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        ScrollParitySteps(this, mode, LayoutKind::IRREGULAR);
    }
}

// ===================== 3. Scroll-to-edge parity =====================

void ScrollToEdgeParitySteps(GridContentClipParityTest* fixture, ParityMode mode, LayoutKind kind)
{
    const ScrollEdgeType edges[] = { ScrollEdgeType::SCROLL_BOTTOM, ScrollEdgeType::SCROLL_TOP };
    std::vector<GridContentClipParityTest::Surface> baseSurfaces;
    GridModelNG baseModel = fixture->CreateParityGrid();
    fixture->BuildGrid(baseModel, kind, ParityMode::UNSET, true, true);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    for (auto edge : edges) {
        fixture->ScrollToEdgeStep(edge);
        baseSurfaces.emplace_back(fixture->CaptureSurface());
    }

    GridModelNG modeModel = fixture->CreateParityGrid();
    fixture->BuildGrid(modeModel, kind, mode, true, true);
    size_t stepIdx = 0;
    fixture->ExpectSurfaceEqual(baseSurfaces[stepIdx++], fixture->CaptureSurface());
    for (auto edge : edges) {
        fixture->ScrollToEdgeStep(edge);
        fixture->ExpectSurfaceEqual(baseSurfaces[stepIdx], fixture->CaptureSurface());
        ++stepIdx;
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollToEdgeAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        ScrollToEdgeParitySteps(this, mode, LayoutKind::SCROLL);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollWithOptionsToEdgeAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        ScrollToEdgeParitySteps(this, mode, LayoutKind::SCROLL_WITH_OPTIONS);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityIrregularScrollToEdgeAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        ScrollToEdgeParitySteps(this, mode, LayoutKind::IRREGULAR);
    }
}

// ===================== 3b. ScrollTo(position) landing parity =====================
// ScrollTo the same positions with contentClip set vs unset and assert
// AC-4.1 full-field equality.

void ScrollToPositionParitySteps(GridContentClipParityTest* fixture, ParityMode mode, LayoutKind kind)
{
    const float positions[] = { 500.0f, 1500.0f, 0.0f };
    std::vector<GridContentClipParityTest::Surface> baseSurfaces;
    GridModelNG baseModel = fixture->CreateParityGrid();
    fixture->BuildGrid(baseModel, kind, ParityMode::UNSET, true, true);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    for (float pos : positions) {
        fixture->ScrollToStep(pos);
        baseSurfaces.emplace_back(fixture->CaptureSurface());
    }

    GridModelNG modeModel = fixture->CreateParityGrid();
    fixture->BuildGrid(modeModel, kind, mode, true, true);
    size_t idx = 0;
    fixture->ExpectSurfaceEqual(baseSurfaces[idx++], fixture->CaptureSurface());
    for (float pos : positions) {
        fixture->ScrollToStep(pos);
        fixture->ExpectSurfaceEqual(baseSurfaces[idx], fixture->CaptureSurface());
        ++idx;
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollToPositionAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        ScrollToPositionParitySteps(this, mode, LayoutKind::SCROLL);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollWithOptionsToPositionAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        ScrollToPositionParitySteps(this, mode, LayoutKind::SCROLL_WITH_OPTIONS);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityIrregularScrollToPositionAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        ScrollToPositionParitySteps(this, mode, LayoutKind::IRREGULAR);
    }
}

// ===================== 3c. ScrollPage parity =====================

void ScrollPageParitySteps(GridContentClipParityTest* fixture, ParityMode mode, LayoutKind kind)
{
    const bool steps[] = { false, false, true }; // forward, forward, backward
    std::vector<GridContentClipParityTest::Surface> baseSurfaces;
    GridModelNG baseModel = fixture->CreateParityGrid();
    fixture->BuildGrid(baseModel, kind, ParityMode::UNSET, true, true);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    for (bool reverse : steps) {
        fixture->ScrollPageStep(reverse);
        baseSurfaces.emplace_back(fixture->CaptureSurface());
    }

    GridModelNG modeModel = fixture->CreateParityGrid();
    fixture->BuildGrid(modeModel, kind, mode, true, true);
    size_t idx = 0;
    fixture->ExpectSurfaceEqual(baseSurfaces[idx++], fixture->CaptureSurface());
    for (bool reverse : steps) {
        fixture->ScrollPageStep(reverse);
        fixture->ExpectSurfaceEqual(baseSurfaces[idx], fixture->CaptureSurface());
        ++idx;
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollPageAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        ScrollPageParitySteps(this, mode, LayoutKind::SCROLL);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollWithOptionsPageAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        ScrollPageParitySteps(this, mode, LayoutKind::SCROLL_WITH_OPTIONS);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityIrregularScrollPageAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        ScrollPageParitySteps(this, mode, LayoutKind::IRREGULAR);
    }
}

// ===================== 3d. padding + safeAreaPadding combo parity =====================
// padding and safeAreaPadding set together: content area
// = frame - padding(50/50) - safeAreaPadding(50/50) = 250 (same config for
// base and mode). The BOUNDARY extension spans from clip(frame) to the
// content area.
// Note: SAFE_AREA does not take part in this scenario — its content-area
// computation for the padding+safeAreaPadding combo is not comparable with
// the base (safe-area semantics). Its extension behavior is covered by the
// safeAreaPadding branch scenarios in BuildGrid (a scenario-construction
// constraint, not an assertion exemption).

void BoundaryComboParitySteps(GridContentClipParityTest* fixture, ParityMode mode, LayoutKind kind)
{
    std::vector<GridContentClipParityTest::Surface> baseSurfaces;
    GridModelNG baseModel = fixture->CreateParityGrid();
    fixture->BuildGrid(baseModel, kind, ParityMode::UNSET, false, false, false, false, true);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    fixture->ScrollByStep(SCROLL_TWO_LINES);
    baseSurfaces.emplace_back(fixture->CaptureSurface());

    GridModelNG modeModel = fixture->CreateParityGrid();
    fixture->BuildGrid(modeModel, kind, mode, false, false, false, false, true);
    fixture->ExpectSurfaceEqual(baseSurfaces[0], fixture->CaptureSurface());
    fixture->ScrollByStep(SCROLL_TWO_LINES);
    fixture->ExpectSurfaceEqual(baseSurfaces[1], fixture->CaptureSurface());
}

HWTEST_F(GridContentClipParityTest, GridParityScrollBoundaryPaddingAndSafeAreaAllModes, TestSize.Level1)
{
    for (auto mode : { ParityMode::BOUNDARY, ParityMode::CONTENT_ONLY, ParityMode::DEFAULT, ParityMode::CUSTOM,
                 ParityMode::RESET }) {
        BoundaryComboParitySteps(this, mode, LayoutKind::SCROLL);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityIrregularBoundaryPaddingAndSafeAreaAllModes, TestSize.Level1)
{
    for (auto mode : { ParityMode::BOUNDARY, ParityMode::CONTENT_ONLY, ParityMode::DEFAULT, ParityMode::CUSTOM,
                 ParityMode::RESET }) {
        BoundaryComboParitySteps(this, mode, LayoutKind::IRREGULAR);
    }
}

// ===================== 4. scrollToIndex landing parity (all alignments) =====================

void ScrollToIndexParitySteps(GridContentClipParityTest* fixture, ParityMode mode, LayoutKind kind)
{
    std::vector<GridContentClipParityTest::Surface> baseSurfaces;
    GridModelNG baseModel = fixture->CreateParityGrid();
    fixture->BuildGrid(baseModel, kind, ParityMode::UNSET, true, true);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    for (auto align : { ScrollAlign::START, ScrollAlign::CENTER, ScrollAlign::END, ScrollAlign::AUTO }) {
        fixture->ScrollToIndexStep(JUMP_TARGET_INDEX, align);
        baseSurfaces.emplace_back(fixture->CaptureSurface());
    }

    GridModelNG modeModel = fixture->CreateParityGrid();
    fixture->BuildGrid(modeModel, kind, mode, true, true);
    size_t idx = 0;
    fixture->ExpectSurfaceEqual(baseSurfaces[idx++], fixture->CaptureSurface());
    for (auto align : { ScrollAlign::START, ScrollAlign::CENTER, ScrollAlign::END, ScrollAlign::AUTO }) {
        fixture->ScrollToIndexStep(JUMP_TARGET_INDEX, align);
        fixture->ExpectSurfaceEqual(baseSurfaces[idx], fixture->CaptureSurface());
        ++idx;
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollToIndexAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        ScrollToIndexParitySteps(this, mode, LayoutKind::SCROLL);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollWithOptionsToIndexAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        ScrollToIndexParitySteps(this, mode, LayoutKind::SCROLL_WITH_OPTIONS);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityIrregularScrollToIndexAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        ScrollToIndexParitySteps(this, mode, LayoutKind::IRREGULAR);
    }
}

// ===================== 5. Large-jump (TrySkipping path) parity =====================

void LargeJumpParitySteps(GridContentClipParityTest* fixture, ParityMode mode, LayoutKind kind)
{
    GridModelNG baseModel = fixture->CreateParityGrid();
    fixture->BuildGrid(baseModel, kind, ParityMode::UNSET, true, true);
    auto base = fixture->CaptureSurface();
    fixture->ScrollToIndexStep(LARGE_JUMP_TARGET_INDEX, ScrollAlign::START);
    auto baseJump = fixture->CaptureSurface();

    GridModelNG modeModel = fixture->CreateParityGrid();
    fixture->BuildGrid(modeModel, kind, mode, true, true);
    fixture->ExpectSurfaceEqual(base, fixture->CaptureSurface());
    fixture->ScrollToIndexStep(LARGE_JUMP_TARGET_INDEX, ScrollAlign::START);
    fixture->ExpectSurfaceEqual(baseJump, fixture->CaptureSurface());
}

HWTEST_F(GridContentClipParityTest, GridParityLargeJumpAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        LargeJumpParitySteps(this, mode, LayoutKind::SCROLL);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollWithOptionsLargeJumpAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        LargeJumpParitySteps(this, mode, LayoutKind::SCROLL_WITH_OPTIONS);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityIrregularLargeJumpAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        LargeJumpParitySteps(this, mode, LayoutKind::IRREGULAR);
    }
}

// ===================== 6. Padding-configured parity (extension-prone) =====================

void PaddingParitySteps(GridContentClipParityTest* fixture, ParityMode mode, LayoutKind kind, bool topPad,
    bool bottomPad)
{
    std::vector<GridContentClipParityTest::Surface> baseSurfaces;
    GridModelNG baseModel = fixture->CreateParityGrid();
    fixture->BuildGrid(baseModel, kind, ParityMode::UNSET, topPad, bottomPad);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    fixture->ScrollByStep(SCROLL_THREE_LINES);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    fixture->ScrollToEdgeStep(ScrollEdgeType::SCROLL_TOP);
    baseSurfaces.emplace_back(fixture->CaptureSurface());

    GridModelNG modeModel = fixture->CreateParityGrid();
    fixture->BuildGrid(modeModel, kind, mode, topPad, bottomPad);
    size_t stepIdx = 0;
    fixture->ExpectSurfaceEqual(baseSurfaces[stepIdx++], fixture->CaptureSurface());
    fixture->ScrollByStep(SCROLL_THREE_LINES);
    fixture->ExpectSurfaceEqual(baseSurfaces[stepIdx++], fixture->CaptureSurface());
    fixture->ScrollToEdgeStep(ScrollEdgeType::SCROLL_TOP);
    fixture->ExpectSurfaceEqual(baseSurfaces[stepIdx], fixture->CaptureSurface());
}

// Note: SAFE_AREA does not take part in single-sided padding scenarios —
// its extension config (safeAreaPadding 100/100 on both sides) gives a
// content area different from the single-sided-padding base (200 vs 300),
// which is not comparable (a scenario-construction constraint, not an
// assertion exemption). The SAFE_AREA extension is covered by the other
// scenarios (initial layout / small steps / jumps / edge, via the
// safeAreaPadding branch).
HWTEST_F(GridContentClipParityTest, GridParityTopPaddingAllModes, TestSize.Level1)
{
    for (auto mode : { ParityMode::DEFAULT, ParityMode::CONTENT_ONLY, ParityMode::BOUNDARY, ParityMode::CUSTOM,
                 ParityMode::RESET }) {
        PaddingParitySteps(this, mode, LayoutKind::SCROLL, true, false);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityBottomPaddingAllModes, TestSize.Level1)
{
    for (auto mode : { ParityMode::DEFAULT, ParityMode::CONTENT_ONLY, ParityMode::BOUNDARY, ParityMode::CUSTOM,
                 ParityMode::RESET }) {
        PaddingParitySteps(this, mode, LayoutKind::SCROLL, false, true);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollWithOptionsPaddingAllModes, TestSize.Level1)
{
    for (auto mode : { ParityMode::DEFAULT, ParityMode::CONTENT_ONLY, ParityMode::BOUNDARY, ParityMode::CUSTOM,
                 ParityMode::RESET }) {
        PaddingParitySteps(this, mode, LayoutKind::SCROLL_WITH_OPTIONS, true, false);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityIrregularPaddingAllModes, TestSize.Level1)
{
    for (auto mode : { ParityMode::DEFAULT, ParityMode::CONTENT_ONLY, ParityMode::BOUNDARY, ParityMode::CUSTOM,
                 ParityMode::RESET }) {
        PaddingParitySteps(this, mode, LayoutKind::IRREGULAR, true, false);
    }
}

// ===================== 7. CachedCount parity =====================

void CachedCountParitySteps(GridContentClipParityTest* fixture, ParityMode mode, LayoutKind kind)
{
    std::vector<GridContentClipParityTest::Surface> baseSurfaces;
    GridModelNG baseModel = fixture->CreateParityGrid();
    fixture->BuildGrid(baseModel, kind, ParityMode::UNSET, true, true, true);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    fixture->ScrollByStep(SCROLL_FIVE_LINES);
    baseSurfaces.emplace_back(fixture->CaptureSurface());

    GridModelNG modeModel = fixture->CreateParityGrid();
    fixture->BuildGrid(modeModel, kind, mode, true, true, true);
    fixture->ExpectSurfaceEqual(baseSurfaces[0], fixture->CaptureSurface());
    fixture->ScrollByStep(SCROLL_FIVE_LINES);
    fixture->ExpectSurfaceEqual(baseSurfaces[1], fixture->CaptureSurface());
}

HWTEST_F(GridContentClipParityTest, GridParityCachedCountAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        CachedCountParitySteps(this, mode, LayoutKind::SCROLL);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollWithOptionsCachedCountAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        CachedCountParitySteps(this, mode, LayoutKind::SCROLL_WITH_OPTIONS);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityIrregularCachedCountAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        CachedCountParitySteps(this, mode, LayoutKind::IRREGULAR);
    }
}

// ===================== 8. Dynamic switch parity (post-set behavior identical) =====================
// Switch contentClip at runtime mid-scroll, then keep scrolling: the
// content-area observable surface matches the baseline (AC-3.1/R-7: the
// switch itself fires no scroll callbacks; SAFE_AREA two-pass intermediate
// events are suppressed by the implementation, F-2/ADR-5).

void DynamicSwitchParitySteps(GridContentClipParityTest* fixture, ParityMode mode, LayoutKind kind)
{
    GridModelNG baseModel = fixture->CreateParityGrid();
    fixture->BuildGrid(baseModel, kind, ParityMode::UNSET, true, true);
    fixture->ScrollByStep(SCROLL_FOUR_LINES);
    auto baseBack = fixture->CaptureSurface();
    fixture->ScrollByStep(-SCROLL_TWO_LINES);
    auto baseAfter = fixture->CaptureSurface();

    // Mode instance: switch clip at runtime mid-scroll, then keep scrolling.
    GridModelNG modeModel = fixture->CreateParityGrid();
    fixture->BuildGrid(modeModel, kind, mode, true, true);
    fixture->ScrollByStep(SCROLL_FOUR_LINES);
    fixture->SetMode(mode == ParityMode::BOUNDARY ? ParityMode::SAFE_AREA : ParityMode::BOUNDARY);
    fixture->ScrollByStep(-SCROLL_TWO_LINES);
    fixture->ExpectSurfaceEqual(baseAfter, fixture->CaptureSurface());
}

HWTEST_F(GridContentClipParityTest, GridParityDynamicSwitchScrollAllModes, TestSize.Level1)
{
    for (auto mode : { ParityMode::BOUNDARY, ParityMode::SAFE_AREA, ParityMode::CONTENT_ONLY }) {
        DynamicSwitchParitySteps(this, mode, LayoutKind::SCROLL);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityDynamicSwitchScrollWithOptionsAllModes, TestSize.Level1)
{
    for (auto mode : { ParityMode::BOUNDARY, ParityMode::SAFE_AREA, ParityMode::CONTENT_ONLY }) {
        DynamicSwitchParitySteps(this, mode, LayoutKind::SCROLL_WITH_OPTIONS);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityDynamicSwitchIrregularAllModes, TestSize.Level1)
{
    for (auto mode : { ParityMode::BOUNDARY, ParityMode::SAFE_AREA, ParityMode::CONTENT_ONLY }) {
        DynamicSwitchParitySteps(this, mode, LayoutKind::IRREGULAR);
    }
}

// ===================== 9. Repeat (repeatDifference_ != 0) parity =====================

void RepeatParitySteps(GridContentClipParityTest* fixture, ParityMode mode)
{
    auto getSize = [](uint32_t) { return ITEM_HEIGHT; };
    std::vector<GridContentClipParityTest::Surface> baseSurfaces;
    fixture->ClearOldNodes();
    GridModelNG baseModel = fixture->CreateRepeatGrid(ITEM_COUNT, getSize);
    fixture->BuildGrid(baseModel, LayoutKind::SCROLL, ParityMode::UNSET, true, true, false, true);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    fixture->ScrollByStep(SCROLL_THREE_LINES);
    baseSurfaces.emplace_back(fixture->CaptureSurface());

    fixture->ClearOldNodes();
    GridModelNG modeModel = fixture->CreateRepeatGrid(ITEM_COUNT, getSize);
    fixture->BuildGrid(modeModel, LayoutKind::SCROLL, mode, true, true, false, true);
    fixture->ExpectSurfaceEqual(baseSurfaces[0], fixture->CaptureSurface());
    fixture->ScrollByStep(SCROLL_THREE_LINES);
    fixture->ExpectSurfaceEqual(baseSurfaces[1], fixture->CaptureSurface());
}

HWTEST_F(GridContentClipParityTest, GridParityRepeatAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        RepeatParitySteps(this, mode);
    }
}

// ===================== 10. Common ScrollableModelNG property combos (AC-4.4) =====================

void CommonPropertyParitySteps(GridContentClipParityTest* fixture, ParityMode mode, LayoutKind kind,
    const std::function<void(GridModelNG&)>& applyCommon)
{
    std::vector<GridContentClipParityTest::Surface> baseSurfaces;
    GridModelNG baseModel = fixture->CreateParityGrid();
    applyCommon(baseModel);
    fixture->BuildGrid(baseModel, kind, ParityMode::UNSET, true, true);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    fixture->ScrollByStep(SCROLL_FOUR_LINES);
    baseSurfaces.emplace_back(fixture->CaptureSurface());

    GridModelNG modeModel = fixture->CreateParityGrid();
    applyCommon(modeModel);
    fixture->BuildGrid(modeModel, kind, mode, true, true);
    fixture->ExpectSurfaceEqual(baseSurfaces[0], fixture->CaptureSurface());
    fixture->ScrollByStep(SCROLL_FOUR_LINES);
    fixture->ExpectSurfaceEqual(baseSurfaces[1], fixture->CaptureSurface());
}

HWTEST_F(GridContentClipParityTest, GridParityEdgeEffectSpringAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        CommonPropertyParitySteps(this, mode, LayoutKind::SCROLL,
            [](GridModelNG& model) { model.SetEdgeEffect(EdgeEffect::SPRING, true); });
    }
}

HWTEST_F(GridContentClipParityTest, GridParityNestedScrollAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        NestedScrollOptions nestedOpt;
        nestedOpt.forward = NestedScrollMode::SELF_FIRST;
        nestedOpt.backward = NestedScrollMode::SELF_FIRST;
        CommonPropertyParitySteps(this, mode, LayoutKind::SCROLL,
            [nestedOpt](GridModelNG& model) { model.SetNestedScroll(nestedOpt); });
    }
}

HWTEST_F(GridContentClipParityTest, GridParityFadingEdgeAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        CommonPropertyParitySteps(this, mode, LayoutKind::SCROLL,
            [](GridModelNG& model) { ScrollableModelNG::SetFadingEdge(true); });
    }
}

HWTEST_F(GridContentClipParityTest, GridParityFrictionMouseBackToTopAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        CommonPropertyParitySteps(this, mode, LayoutKind::SCROLL, [](GridModelNG& model) {
            model.SetFriction(0.6);
            ScrollableModelNG::SetEnableScrollWithMouse(true);
            ScrollableModelNG::SetBackToTop(true);
        });
    }
}

// ===================== 11. SAFE_AREA two-pass convergence (F-2 / ADR-5) =====================
// Intermediate passes (snapshot missing or stale) must have their events
// suppressed: the developer only observes the converged event sequence, with
// no extra onScrollBarUpdate beyond the baseline (AC-1.2/R-2, AC-3.1/R-7,
// AC-4.1/R-10).

// SafeAreaPadding value change: the stale-value intermediate pass is
// suppressed; exactly one onScrollBarUpdate after convergence, and the final
// fix offsets use the latest value.
HWTEST_F(GridContentClipParityTest, GridParitySafeAreaPadChangeSingleDispatch001, TestSize.Level1)
{
    GridModelNG model = CreateParityGrid();
    BuildGrid(model, LayoutKind::SCROLL, ParityMode::SAFE_AREA);
    // Reset observation after the initial convergence: count only the events
    // introduced by the pad change
    ResetObservation();

    layoutProperty_->UpdateSafeAreaPadding(CreatePadding(0.0f, 50.0f, 0.0f, 50.0f));
    FlushUITasks();

    const auto& info = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(info.startFixOffset_, 50.0f) << "final layout must use latest safe-area value";
    EXPECT_EQ(info.endFixOffset_, 50.0f) << "final layout must use latest safe-area value";
    EXPECT_EQ(scrollBarUpdates_.size(), 1u)
        << "stale-value pass must be suppressed; exactly one onScrollBarUpdate after convergence";
}

// With the system safe-area unchanged: under the same scroll/flush sequence,
// SAFE_AREA dispatches the same number of rounds as the UNSET baseline (the
// convergence equality check exits early, adding no SAFE_AREA-specific extra
// Measure round).
HWTEST_F(GridContentClipParityTest, GridParitySafeAreaUnchangedNoExtraRound001, TestSize.Level1)
{
    // base: UNSET + the same safeAreaPadding (identical content-area
    // geometry, extension inactive)
    GridModelNG baseModel = CreateParityGrid();
    BuildGrid(baseModel, LayoutKind::SCROLL, ParityMode::UNSET);
    ResetObservation();
    UpdateCurrentOffset(SCROLL_TWO_LINES);
    const size_t baseAfterScroll = scrollBarUpdates_.size();
    FlushUITasks();
    const size_t baseAfterExtraFlush = scrollBarUpdates_.size();

    // mode: SAFE_AREA (after convergence)
    GridModelNG modeModel = CreateParityGrid();
    BuildGrid(modeModel, LayoutKind::SCROLL, ParityMode::SAFE_AREA);
    ResetObservation();
    UpdateCurrentOffset(SCROLL_TWO_LINES);
    const size_t modeAfterScroll = scrollBarUpdates_.size();
    FlushUITasks();
    const size_t modeAfterExtraFlush = scrollBarUpdates_.size();

    EXPECT_EQ(modeAfterScroll, baseAfterScroll)
        << "SAFE_AREA must not add dispatch rounds beyond UNSET baseline after scroll";
    EXPECT_EQ(modeAfterExtraFlush, baseAfterExtraFlush)
        << "unchanged safe-area must not create an extra measure round";
}

// During a measure break: PostponedTaskForIgnore updates safeAreaPad_ without
// forcing CreateLayoutTask (mirroring List's !prevMeasureBreak_ guard, F-2b).
// Discriminator: with the guard the call performs no layout and
// prevMeasureBreak_ stays true; without it CreateLayoutTask -> Measure ->
// OnDirtyLayoutWrapperSwap would rewrite prevMeasureBreak_ to
// MeasureInNextFrame() (no real breakpoints in the mock environment, flipping
// it to false).
HWTEST_F(GridContentClipParityTest, GridParitySafeAreaMeasureBreakNoForcedLayout001, TestSize.Level1)
{
    GridModelNG model = CreateParityGrid();
    BuildGrid(model, LayoutKind::SCROLL, ParityMode::SAFE_AREA);
    ASSERT_TRUE(frameNode_);

    // A safe-area value change keeps the equality check from exiting early;
    // during a measure break only the snapshot is refreshed, with no dirty
    // flag / layout task
    layoutProperty_->UpdateSafeAreaPadding(CreatePadding(0.0f, 50.0f, 0.0f, 50.0f));
    pattern_->prevMeasureBreak_ = true;
    pattern_->PostponedTaskForIgnore(LayoutSafeAreaBundleType::CONTENT_CLIP_SAFE_AREA);
    EXPECT_TRUE(pattern_->safeAreaPad_.has_value()) << "snapshot must still be refreshed during measure break";
    EXPECT_TRUE(pattern_->prevMeasureBreak_)
        << "measure break must not force a nested CreateLayoutTask (align List prevMeasureBreak_ guard)";
}

// ===================== 12. Gap parity (rowsGap / columnsGap != 0) =====================
// All scenarios above run gap-less; with gap the main-axis pitch becomes
// ITEM_HEIGHT + GRID_GAP, so fractional scroll offsets can land mid-item or
// inside a gap, the report-range walk crosses gap boundaries, and the
// extension area (padding 100/100, same construction as the gap-less
// scenarios) starts/ends inside a row or a gap. The AC-4.1 full-field parity
// must hold under the same two-phase driving.

// Step set: pitch-aligned scroll, fractional back-scroll (view boundary
// inside a row), large forward scroll (lands inside a gap), both edges
// (bottom/end and top/start extension against gap-shifted bounds), and
// scrollToIndex with two alignments (jump landing math includes gap).
void GapParitySteps(GridContentClipParityTest* fixture, ParityMode mode, LayoutKind kind)
{
    std::vector<GridContentClipParityTest::Surface> baseSurfaces;
    GridModelNG baseModel = fixture->CreateParityGrid();
    fixture->BuildGrid(baseModel, kind, ParityMode::UNSET, true, true, false, false, false, GRID_GAP, GRID_GAP);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    fixture->ScrollByStep(ITEM_HEIGHT + GRID_GAP);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    fixture->ScrollByStep(-SCROLL_HALF_LINE);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    fixture->ScrollByStep(SCROLL_TEN_LINES);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    fixture->ScrollToEdgeStep(ScrollEdgeType::SCROLL_BOTTOM);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    fixture->ScrollToEdgeStep(ScrollEdgeType::SCROLL_TOP);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    for (auto align : { ScrollAlign::START, ScrollAlign::CENTER }) {
        fixture->ScrollToIndexStep(JUMP_TARGET_INDEX, align);
        baseSurfaces.emplace_back(fixture->CaptureSurface());
    }

    GridModelNG modeModel = fixture->CreateParityGrid();
    fixture->BuildGrid(modeModel, kind, mode, true, true, false, false, false, GRID_GAP, GRID_GAP);
    size_t idx = 0;
    fixture->ExpectSurfaceEqual(baseSurfaces[idx++], fixture->CaptureSurface());
    fixture->ScrollByStep(ITEM_HEIGHT + GRID_GAP);
    fixture->ExpectSurfaceEqual(baseSurfaces[idx++], fixture->CaptureSurface());
    fixture->ScrollByStep(-SCROLL_HALF_LINE);
    fixture->ExpectSurfaceEqual(baseSurfaces[idx++], fixture->CaptureSurface());
    fixture->ScrollByStep(SCROLL_TEN_LINES);
    fixture->ExpectSurfaceEqual(baseSurfaces[idx++], fixture->CaptureSurface());
    fixture->ScrollToEdgeStep(ScrollEdgeType::SCROLL_BOTTOM);
    fixture->ExpectSurfaceEqual(baseSurfaces[idx++], fixture->CaptureSurface());
    fixture->ScrollToEdgeStep(ScrollEdgeType::SCROLL_TOP);
    fixture->ExpectSurfaceEqual(baseSurfaces[idx++], fixture->CaptureSurface());
    for (auto align : { ScrollAlign::START, ScrollAlign::CENTER }) {
        fixture->ScrollToIndexStep(JUMP_TARGET_INDEX, align);
        fixture->ExpectSurfaceEqual(baseSurfaces[idx], fixture->CaptureSurface());
        ++idx;
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollGapAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        GapParitySteps(this, mode, LayoutKind::SCROLL);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollWithOptionsGapAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        GapParitySteps(this, mode, LayoutKind::SCROLL_WITH_OPTIONS);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityIrregularGapAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        GapParitySteps(this, mode, LayoutKind::IRREGULAR);
    }
}

// Gap + cachedCount: the cache extent ahead/behind the view is measured in
// whole line pitches (item height plus gap). The extension side must keep the
// report range content-area-pure with cache rows landing inside gaps.
void GapCachedCountParitySteps(GridContentClipParityTest* fixture, ParityMode mode, LayoutKind kind)
{
    std::vector<GridContentClipParityTest::Surface> baseSurfaces;
    GridModelNG baseModel = fixture->CreateParityGrid();
    fixture->BuildGrid(baseModel, kind, ParityMode::UNSET, true, true, true, false, false, GRID_GAP, GRID_GAP);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    fixture->ScrollByStep(SCROLL_FIVE_LINES);
    baseSurfaces.emplace_back(fixture->CaptureSurface());

    GridModelNG modeModel = fixture->CreateParityGrid();
    fixture->BuildGrid(modeModel, kind, mode, true, true, true, false, false, GRID_GAP, GRID_GAP);
    fixture->ExpectSurfaceEqual(baseSurfaces[0], fixture->CaptureSurface());
    fixture->ScrollByStep(SCROLL_FIVE_LINES);
    fixture->ExpectSurfaceEqual(baseSurfaces[1], fixture->CaptureSurface());
}

HWTEST_F(GridContentClipParityTest, GridParityScrollGapCachedCountAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        GapCachedCountParitySteps(this, mode, LayoutKind::SCROLL);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollWithOptionsGapCachedCountAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        GapCachedCountParitySteps(this, mode, LayoutKind::SCROLL_WITH_OPTIONS);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityIrregularGapCachedCountAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        GapCachedCountParitySteps(this, mode, LayoutKind::IRREGULAR);
    }
}

// ===================== 13. Edge-then-jump parity (gap-less) =====================
// Sequence blind spot of the sections above: they test toIndex from the
// initial state and edges from the initial state, never combined. The
// combination is the corruption path of the irregular jump solver: a
// bottom-edge jump fills the whole matrix while measuring only the view
// heights, a subsequent top-edge jump re-measures from the top, and the
// resulting discontinuous lineHeightMap_ feeds SolveForwardForEndIdx —
// which must stop at the hole instead of skipping it (see
// SolveForwardForEndIdxDiscontinuousHeights001 for the solver-level unit
// test). Runs gap-less so the defect class is guarded independently of the
// gap configuration.
void EdgeThenToIndexParitySteps(GridContentClipParityTest* fixture, ParityMode mode, LayoutKind kind)
{
    std::vector<GridContentClipParityTest::Surface> baseSurfaces;
    GridModelNG baseModel = fixture->CreateParityGrid();
    fixture->BuildGrid(baseModel, kind, ParityMode::UNSET, true, true);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    // land mid-content so the bottom-edge jump rebuilds from far away
    fixture->ScrollByStep(SCROLL_TWO_LINES);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    fixture->ScrollToEdgeStep(ScrollEdgeType::SCROLL_BOTTOM);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    fixture->ScrollToEdgeStep(ScrollEdgeType::SCROLL_TOP);
    baseSurfaces.emplace_back(fixture->CaptureSurface());
    for (auto align : { ScrollAlign::START, ScrollAlign::CENTER }) {
        fixture->ScrollToIndexStep(JUMP_TARGET_INDEX, align);
        baseSurfaces.emplace_back(fixture->CaptureSurface());
    }

    GridModelNG modeModel = fixture->CreateParityGrid();
    fixture->BuildGrid(modeModel, kind, mode, true, true);
    size_t stepIdx = 0;
    fixture->ExpectSurfaceEqual(baseSurfaces[stepIdx++], fixture->CaptureSurface());
    fixture->ScrollByStep(SCROLL_TWO_LINES);
    fixture->ExpectSurfaceEqual(baseSurfaces[stepIdx++], fixture->CaptureSurface());
    fixture->ScrollToEdgeStep(ScrollEdgeType::SCROLL_BOTTOM);
    fixture->ExpectSurfaceEqual(baseSurfaces[stepIdx++], fixture->CaptureSurface());
    fixture->ScrollToEdgeStep(ScrollEdgeType::SCROLL_TOP);
    fixture->ExpectSurfaceEqual(baseSurfaces[stepIdx++], fixture->CaptureSurface());
    for (auto align : { ScrollAlign::START, ScrollAlign::CENTER }) {
        fixture->ScrollToIndexStep(JUMP_TARGET_INDEX, align);
        fixture->ExpectSurfaceEqual(baseSurfaces[stepIdx], fixture->CaptureSurface());
        ++stepIdx;
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollEdgeThenToIndexAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        EdgeThenToIndexParitySteps(this, mode, LayoutKind::SCROLL);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityScrollWithOptionsEdgeThenToIndexAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        EdgeThenToIndexParitySteps(this, mode, LayoutKind::SCROLL_WITH_OPTIONS);
    }
}

HWTEST_F(GridContentClipParityTest, GridParityIrregularEdgeThenToIndexAllModes, TestSize.Level1)
{
    for (auto mode : ALL_MODES) {
        EdgeThenToIndexParitySteps(this, mode, LayoutKind::IRREGULAR);
    }
}
} // namespace OHOS::Ace::NG
