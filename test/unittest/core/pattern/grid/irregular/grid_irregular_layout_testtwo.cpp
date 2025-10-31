/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "irregular_matrices.h"
#include "test/unittest/core/pattern/grid/grid_test_ng.h"

#include "core/components_ng/pattern/grid/irregular/grid_irregular_layout_algorithm.h"
#include "core/components_ng/pattern/grid/irregular/grid_layout_range_solver.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"

namespace OHOS::Ace::NG {
class GridIrregularLayoutTestTwo : public GridTestNg {};

/**
 * @tc.name: GridIrregularLayout::SolveForwardForEndIdx001
 * @tc.desc: Test GridLayoutRangeFinder::SolveForwardForEndIdx
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, SolveForwardForEndIdx001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 100.0f }, { 2, 50.0f }, { 3, 50.0f }, { 4, 80.0f } };
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 1 } } },    // 0 | 0 | 1
        { 1, { { 0, 2 }, { 1, -2 }, { 2, -2 } } },  // 2 | 2 | 2
        { 2, { { 0, -2 }, { 1, -2 }, { 2, -2 } } }, // 2 | 2 | 2
        { 3, { { 0, 3 }, { 1, 4 }, { 2, 5 } } },    // 3 | 4 | 5
        { 4, { { 0, 6 }, { 1, -6 }, { 2, -5 } } },  // 6 | 6 | 5
    };

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions({});
    CreateDone();

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));
    auto [endLineIdx, endIdx] = solver.SolveForwardForEndIdx(5.0f, 250.0f, 1);
    EXPECT_EQ(endIdx, 6);
    EXPECT_EQ(endLineIdx, 4);
}

namespace {
void CheckAlignStart(const RefPtr<GridIrregularLayoutAlgorithm>& algorithm, GridLayoutInfo& info)
{
    info.scrollAlign_ = ScrollAlign::START;
    int32_t idx = 0;
    algorithm->PrepareLineHeight(70.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);
    EXPECT_EQ(idx, 0);

    info.scrollAlign_ = ScrollAlign::START;
    idx = 2;
    algorithm->PrepareLineHeight(300.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);
    EXPECT_EQ(idx, 2);

    // can't align start with idx 4
    info.scrollAlign_ = ScrollAlign::START;
    idx = 4;
    algorithm->PrepareLineHeight(300.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::END);
    EXPECT_EQ(idx, 4);
}

void CheckAlignCenter(const RefPtr<GridIrregularLayoutAlgorithm>& algorithm, GridLayoutInfo& info)
{
    // can't align center with idx 0
    info.scrollAlign_ = ScrollAlign::CENTER;
    int32_t idx = 0;
    algorithm->PrepareLineHeight(350.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);
    EXPECT_EQ(idx, 0);

    // can't align center with idx 4
    info.scrollAlign_ = ScrollAlign::CENTER;
    idx = 4;
    algorithm->PrepareLineHeight(350.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::END);
    EXPECT_EQ(idx, 4);

    // align center with idx 4 and len 30.0f
    info.scrollAlign_ = ScrollAlign::CENTER;
    idx = 4;
    algorithm->PrepareLineHeight(30.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::CENTER);
    EXPECT_EQ(idx, 4);
}

void CheckAlignEnd(const RefPtr<GridIrregularLayoutAlgorithm>& algorithm, GridLayoutInfo& info)
{
    // can't align end with idx 1 and len 200.0f
    info.scrollAlign_ = ScrollAlign::END;
    int32_t idx = 1;
    algorithm->PrepareLineHeight(500.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);
    EXPECT_EQ(idx, 0);

    info.scrollAlign_ = ScrollAlign::END;
    idx = 3;
    algorithm->PrepareLineHeight(300.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::END);
    EXPECT_EQ(idx, 3);

    info.scrollAlign_ = ScrollAlign::END;
    idx = 4;
    algorithm->PrepareLineHeight(1000.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::END);
    EXPECT_EQ(idx, 4);

    // can't align end with len 340
    info.scrollAlign_ = ScrollAlign::END;
    idx = 4;
    algorithm->PrepareLineHeight(1040.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);
    EXPECT_EQ(idx, 0);
}
} // namespace

/**
 * @tc.name: GridIrregularLayout::PrepareLineHeights001
 * @tc.desc: Test GridIrregularLayout::PrepareLineHeights001
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, PrepareLineHeights001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions({});
    CreateFixedItems(15);
    CreateDone();

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->wrapper_ = AceType::RawPtr(frameNode_);
    algorithm->crossLens_ = { 1.0f, 1.0f, 1.0f };
    auto& info = algorithm->info_;
    // because measuring children might not generate proper heights in test, we set them manually.
    decltype(info.lineHeightMap_) cmpH = { { 0, 200.0f }, { 1, 200.0f }, { 2, 200.0f }, { 3, 200.0f }, { 4, 200.0f } };
    info.lineHeightMap_ = cmpH;
    decltype(info.gridMatrix_) cmp = {
        { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 } } },
        { 1, { { 0, 3 }, { 1, 4 }, { 2, 5 } } },
        { 2, { { 0, 6 }, { 1, 7 }, { 2, 8 } } },
        { 3, { { 0, 9 }, { 1, 10 }, { 2, 11 } } },
        { 4, { { 0, 12 }, { 1, 13 }, { 2, 14 } } },
    };
    info.gridMatrix_ = cmp;

    info.crossCount_ = 3;
    info.childrenCount_ = 15;

    info.scrollAlign_ = ScrollAlign::START;
    algorithm->overscrollOffsetBeforeJump_ = 300.0f;
    auto idx = 4;
    algorithm->PrepareLineHeight(300.0f, idx);
    // can align start with idx 4 when overscroll
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);
    EXPECT_EQ(idx, 4);

    EXPECT_EQ(cmp, info.gridMatrix_);
    EXPECT_EQ(cmpH, info.lineHeightMap_);
}

/**
 * @tc.name: GridIrregularLayout::PrepareLineHeights002
 * @tc.desc: Test GridIrregularLayout::PrepareLineHeight
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, PrepareLineHeights002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions({});
    CreateFixedItems(15);
    CreateDone();

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->wrapper_ = AceType::RawPtr(frameNode_);
    algorithm->crossLens_ = { 1.0f, 1.0f, 1.0f };
    auto& info = algorithm->info_;
    // because measuring children might not generate proper heights in test, we set them manually.
    decltype(info.lineHeightMap_) cmpH = { { 0, 200.0f }, { 1, 200.0f }, { 2, 200.0f }, { 3, 200.0f }, { 4, 200.0f } };
    info.lineHeightMap_ = cmpH;
    decltype(info.gridMatrix_) cmp = {
        { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 } } },
        { 1, { { 0, 3 }, { 1, 4 }, { 2, 5 } } },
        { 2, { { 0, 6 }, { 1, 7 }, { 2, 8 } } },
        { 3, { { 0, 9 }, { 1, 10 }, { 2, 11 } } },
        { 4, { { 0, 12 }, { 1, 13 }, { 2, 14 } } },
    };
    info.gridMatrix_ = cmp;

    info.crossCount_ = 3;
    info.childrenCount_ = 15;

    CheckAlignStart(algorithm, info);
    CheckAlignCenter(algorithm, info);
    CheckAlignEnd(algorithm, info);

    EXPECT_EQ(cmp, info.gridMatrix_);
    EXPECT_EQ(cmpH, info.lineHeightMap_);
}

/**
 * @tc.name: GridIrregularLayout::SkipLines001
 * @tc.desc: Test GridIrregularLayout::SkipLines001
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, SkipLines001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo1());
    CreateDone();

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->wrapper_ = AceType::RawPtr(frameNode_);

    auto& info = algorithm->info_;
    info.crossCount_ = 3;
    info.lineHeightMap_ = { { 0, 200.0f }, { 1, 200.0f }, { 2, 200.0f } };
    info.gridMatrix_ = MATRIX_DEMO_1;
    info.childrenCount_ = 11;

    info.currentOffset_ = -500.0f;
    EXPECT_EQ(algorithm->SkipLinesForward(), 5);
    info.currentOffset_ = -900.0f;
    EXPECT_EQ(algorithm->SkipLinesForward(), 9);
    info.currentOffset_ = -1500.0f;
    EXPECT_EQ(algorithm->SkipLinesForward(), 10);

    info.lineHeightMap_ = { { 3, 200.0f }, { 4, 200.0f } };
    info.startIndex_ = 5;
    info.startMainLineIndex_ = 3;
    info.endMainLineIndex_ = 4;

    info.currentOffset_ = 400.0f;
    EXPECT_EQ(algorithm->SkipLinesBackward(), 2);

    info.currentOffset_ = 800.0f;
    EXPECT_EQ(algorithm->SkipLinesBackward(), 1);

    info.currentOffset_ = 1500.0f;
    EXPECT_EQ(algorithm->SkipLinesBackward(), 1);
}

/**
 * @tc.name: GridIrregularLayout::SkipLines002
 * @tc.desc: Test GridIrregularLayout::SkipLines backward
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, SkipLines002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo11());
    CreateDone();

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->wrapper_ = AceType::RawPtr(frameNode_);

    auto& info = algorithm->info_;
    info.crossCount_ = 3;
    info.gridMatrix_ = MATRIX_DEMO_11;
    info.childrenCount_ = 10;

    info.lineHeightMap_ = { { 4, 300.0f }, { 5, 300.0f }, { 6, 300.0f } };
    info.startIndex_ = 7;
    info.startMainLineIndex_ = 6;
    info.endMainLineIndex_ = 6;
    info.endIndex_ = 9;

    info.currentOffset_ = 700.0f;
    EXPECT_EQ(algorithm->SkipLinesBackward(), 5);

    info.currentOffset_ = 1300.0f;
    EXPECT_EQ(algorithm->SkipLinesBackward(), 2);

    info.currentOffset_ = 1600.0f;
    EXPECT_EQ(algorithm->SkipLinesBackward(), 1);
}

/**
 * @tc.name: GridIrregularLayout::TrySkipping001
 * @tc.desc: Test GridIrregularLayout::TrySkipping001
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, TrySkipping001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo2());
    CreateFixedItems(8);
    CreateDone();

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->wrapper_ = AceType::RawPtr(frameNode_);
    algorithm->crossLens_ = { 100.0f, 100.0f, 100.0f };

    auto& info = algorithm->info_;
    info.crossCount_ = 3;
    info.childrenCount_ = 8;

    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f } };
    info.gridMatrix_ = MATRIX_DEMO_2;
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 1;
    info.startIndex_ = 0;
    info.endIndex_ = 1;

    info.currentOffset_ = -25.0f;
    EXPECT_FALSE(algorithm->TrySkipping(150.0f));
    info.currentOffset_ = -150.0f;
    EXPECT_FALSE(algorithm->TrySkipping(150.0f));
    info.currentOffset_ = -400.0f;
    EXPECT_FALSE(algorithm->TrySkipping(150.0f));
    info.currentOffset_ = -401.0f;
    EXPECT_TRUE(algorithm->TrySkipping(150.0f));
    EXPECT_EQ(info.startIndex_, 5);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);

    info.scrollAlign_ = ScrollAlign::NONE;
    info.lineHeightMap_ = { { 3, 100.0f }, { 4, 100.0f } };
    info.startMainLineIndex_ = 3;
    info.endMainLineIndex_ = 4;
    info.startIndex_ = 4;
    info.endIndex_ = 7;

    info.currentOffset_ = 25.0f;
    EXPECT_FALSE(algorithm->TrySkipping(150.0f));
    info.currentOffset_ = 150.0f;
    EXPECT_FALSE(algorithm->TrySkipping(150.0f));
    info.currentOffset_ = 400.0f;
    EXPECT_FALSE(algorithm->TrySkipping(150.0f));
    info.currentOffset_ = 401.0f;
    EXPECT_TRUE(algorithm->TrySkipping(150.0f));
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);
}

/**
 * @tc.name: GridIrregularLayout::Integrated001
 * @tc.desc: Test full layout process
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, Integrated001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo8());
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedItems(7);
    model.SetEdgeEffect(EdgeEffect::NONE, true);
    CreateDone();
    const std::map<int32_t, float> HEIGHT_MAP = { { 0, 100.0f }, { 1, 50.0f }, { 2, 50.0f }, { 3, 100.0f },
        { 4, 100.0f }, { 5, 100.0f / 3 } };
    auto& info = pattern_->info_;
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 6);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 4);
    EXPECT_EQ(info.lineHeightMap_, HEIGHT_MAP);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_8);

    UpdateCurrentOffset(-100.0f);
    EXPECT_FLOAT_EQ(info.currentOffset_, -100.0f / 3);
    EXPECT_EQ(info.endIndex_, 6);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 5);
    EXPECT_TRUE(info.offsetEnd_);
    EXPECT_FLOAT_EQ(info.GetIrregularHeight(0.0f), 400 + 100.0f / 3);
    EXPECT_FLOAT_EQ(info.GetIrregularOffset(0.0f), 100.0f / 3);
}

/**
 * @tc.name: GridIrregularLayout::Integrated002
 * @tc.desc: Test full layout process
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, Integrated002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo13());
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 100.0f);
    CreateFixedHeightItems(1, 200.0f);
    CreateFixedHeightItems(1, 600.0f);
    CreateGridItems(5, -2, 100.0f);
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    ViewAbstract::SetHeight(CalcLength(300.0f));
    CreateDone();
    auto& info = pattern_->info_;
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 0);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 2);
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    UpdateCurrentOffset(-5.0f);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 2);
    EXPECT_EQ(info.endMainLineIndex_, 3);
    UpdateCurrentOffset(3.0f);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 2);
    EXPECT_EQ(info.endMainLineIndex_, 3);
    for (int i = 0; i < 5; ++i) {
        UpdateCurrentOffset(3.0f);
        EXPECT_EQ(info.startIndex_, 0);
        EXPECT_EQ(info.endIndex_, 0);
    }
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 2);
    EXPECT_TRUE(info.reachStart_);
}

/**
 * @tc.name: GridIrregularLayout::GetOverScrollOffset001
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, GetOverScrollOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo13());
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 100.0f);
    CreateFixedHeightItems(1, 200.0f);
    CreateFixedHeightItems(1, 600.0f);
    CreateGridItems(5, -2, 100.0f);
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    ViewAbstract::SetHeight(CalcLength(300.0f));
    CreateDone();
    EXPECT_TRUE(pattern_->irregular_);
    auto& info = pattern_->info_;
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    UpdateCurrentOffset(-200.0f);
    // only items 0~2 are known
    EXPECT_EQ(info.GetIrregularHeight(0.0f), 1500.0f);
    EXPECT_EQ(info.GetIrregularOffset(0.0f), 200.0f);
    UpdateCurrentOffset(-200.0f);
    EXPECT_EQ(info.GetIrregularHeight(0.0f), 1100.0f);
    EXPECT_EQ(info.GetIrregularOffset(0.0f), 400.0f);
    UpdateCurrentOffset(-200.0f);
    EXPECT_EQ(info.GetIrregularHeight(0.0f), 1100.0f);
    EXPECT_EQ(info.GetIrregularOffset(0.0f), 600.0f);
    EXPECT_EQ(info.endIndex_, 8);

    UpdateCurrentOffset(-150.0f);
    EXPECT_FALSE(info.offsetEnd_);
    EXPECT_EQ(info.endIndex_, 8);
    EXPECT_EQ(info.startIndex_, 3);
    EXPECT_EQ(info.startMainLineIndex_, 5);
    EXPECT_EQ(info.endMainLineIndex_, 10);
    UpdateCurrentOffset(-50.0f);
    EXPECT_EQ(info.GetIrregularOffset(0.0f), 800.0f);
    EXPECT_TRUE(info.offsetEnd_);
    EXPECT_EQ(pattern_->GetOverScrollOffset(-50).end, -50.0f);
    EXPECT_EQ(pattern_->GetOverScrollOffset(-10).end, -10.0f);
    EXPECT_EQ(
        info.GetDistanceToBottom(info.lastMainSize_, info.totalHeightOfItemsInView_, pattern_->GetMainGap()), 0.0f);
    UpdateCurrentOffset(-50.0f);
    EXPECT_EQ(pattern_->GetOverScrollOffset(60).end, 50.0f);
    EXPECT_EQ(pattern_->GetOverScrollOffset(20).end, 20.0f);
}

/**
 * @tc.name: GridIrregularLayout::Gaps001
 * @tc.desc: Test changing gaps
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, Gaps001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo6());
    model.SetColumnsGap(Dimension { 1.0f });
    model.SetRowsGap(Dimension { 1.0f });
    CreateGridItems(12, -2, 100.0f);
    CreateDone();

    EXPECT_EQ(GetChildRect(frameNode_, 1).GetX(), 120.5f);
    EXPECT_EQ(GetChildRect(frameNode_, 4).GetY(), 202.0f);

    layoutProperty_->UpdateColumnsGap(Dimension { 5.0f });
    FlushUITasks();
    EXPECT_EQ(GetChildRect(frameNode_, 1).GetX(), 122.5f);
    EXPECT_EQ(GetChildSize(frameNode_, 1).Width(), 117.5f);
    EXPECT_EQ(GetChildRect(frameNode_, 4).GetY(), 202.0f);

    layoutProperty_->UpdateRowsGap(Dimension { 3.0f });
    FlushUITasks();
    EXPECT_EQ(GetChildRect(frameNode_, 1).GetX(), 122.5f);
    EXPECT_EQ(GetChildRect(frameNode_, 4).GetY(), 206.0f);
}

/**
 * @tc.name: GridIrregularLayout::TemplateChange001
 * @tc.desc: Test changing template
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, TemplateChange001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo6());
    model.SetColumnsGap(Dimension { 1.0f });
    model.SetRowsGap(Dimension { 10.0f });
    CreateFixedHeightItems(12, 250.0f);
    CreateDone();
    const auto& info = pattern_->info_;
    // only know 3 items
    EXPECT_EQ(info.GetIrregularHeight(10.0f), 8 * 250.0f + 7 * 10.0f);
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(info.offsetEnd_);
    EXPECT_EQ(info.GetIrregularOffset(10.0f), 110.0f + 6 * 260.0f);
    EXPECT_EQ(info.GetIrregularHeight(10.0f), 8 * 250.0f + 7 * 10.0f);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr");
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(info.startIndex_, 9);
    EXPECT_EQ(info.endIndex_, 11);
    EXPECT_EQ(info.currentOffset_, -110.0f);
    EXPECT_EQ(info.startMainLineIndex_, 4);
    EXPECT_EQ(info.endMainLineIndex_, 5);
    EXPECT_EQ(info.GetIrregularOffset(10.0f), 110.0f + 4 * 260.0f);
    EXPECT_EQ(info.GetIrregularHeight(10.0f), 6 * 250.0f + 5 * 10.0f);

    for (int i = 0; i < 20; ++i) {
        UpdateCurrentOffset(100.0f);
    }
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
}

/**
 * @tc.name: GridIrregularLayout::TemplateChange002
 * @tc.desc: Test changing template
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, TemplateChange002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo13());
    model.SetColumnsGap(Dimension { 1.0f });
    model.SetRowsGap(Dimension { 5.0f });
    CreateFixedHeightItems(1, 910.0f);
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 605.0f);
    CreateFixedHeightItems(1, 1825.0f);
    CreateFixedHeightItems(5, 300.0f);
    CreateDone();
    const auto& info = pattern_->info_;
    // only know 1 item
    EXPECT_EQ(info.GetIrregularHeight(5.0f), 27 * 300.0f + 26 * 5.0f);
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(info.offsetEnd_);
    EXPECT_EQ(info.startIndex_, 3);
    EXPECT_EQ(info.endIndex_, 8);
    EXPECT_EQ(info.GetIrregularOffset(5.0f), 11 * 300.0f + 10 * 5.0f - HEIGHT);
    EXPECT_EQ(info.GetIrregularHeight(5.0f), 11 * 300.0f + 10 * 5.0f);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr 1fr 1fr 1fr");
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(info.startMainLineIndex_, 3);
    EXPECT_EQ(info.endMainLineIndex_, 8);
    EXPECT_EQ(info.startIndex_, 3);
    EXPECT_EQ(info.GetIrregularOffset(5.0f), 3 * 305.f - info.currentOffset_);
    EXPECT_EQ(info.GetIrregularHeight(5.0f), 9 * 300.0f + 8 * 5.0f);
}

/**
 * @tc.name: GridIrregularLayout::TemplateChange003
 * @tc.desc: Test changing template
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, TemplateChange003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo13());
    model.SetColumnsGap(Dimension { 1.0f });
    CreateFixedHeightItems(1, 450.0f);
    CreateFixedHeightItems(1, 150.0f);
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 900.0f);
    CreateFixedHeightItems(5, 150.0f);
    CreateDone();
    ScrollToIndex(3, false, ScrollAlign::CENTER);
    EXPECT_EQ(GetChildY(frameNode_, 3), -250.0f);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr 1fr 1fr 1fr");
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    ScrollToIndex(3, true, ScrollAlign::CENTER);
    pattern_->finalPosition_ = Infinity<float>();
    // finalPosition shouldn't be set because targetPos = current pos
    EXPECT_EQ(pattern_->finalPosition_, Infinity<float>());
}

/**
 * @tc.name: DeleteItem001
 * @tc.desc: Test removing item from end
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, DeleteItem001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo13());
    model.SetColumnsGap(Dimension { 1.0f });
    model.SetRowsGap(Dimension { 5.0f });
    CreateFixedHeightItems(1, 910.0f);
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 605.0f);
    CreateFixedHeightItems(1, 1825.0f);
    CreateFixedHeightItems(5, 300.0f);
    ViewAbstract::SetHeight(CalcLength(200.0f));
    CreateDone();
    const auto& info = pattern_->info_;
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(info.offsetEnd_);
    for (int i = 0; i < 6; ++i) {
        frameNode_->RemoveChildAtIndex(3);
    }
    frameNode_->ChildrenUpdatedFrom(3);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    FlushUITasks();
    EXPECT_EQ(info.startMainLineIndex_, 3);
    EXPECT_EQ(info.endMainLineIndex_, 4);
    EXPECT_EQ(info.startIndex_, 2);
    EXPECT_EQ(info.currentOffset_, -405.0f);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_13_AFTER_DELETE);
    EXPECT_TRUE(info.offsetEnd_);

    frameNode_->RemoveChildAtIndex(2);
    frameNode_->ChildrenUpdatedFrom(2);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    FlushUITasks();
    EXPECT_EQ(info.startMainLineIndex_, 3);
    EXPECT_EQ(info.endMainLineIndex_, 3);
    EXPECT_EQ(info.currentOffset_, -100.0f);
}

/**
 * @tc.name: GridIrregularLayout::Width001
 * @tc.desc: Test width priority of gridItem
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, Width001, TestSize.Level1)
{
    // GridItem's own ideal size has higher priority
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo6());
    model.SetColumnsGap(Dimension { 1.0f });
    model.SetRowsGap(Dimension { 1.0f });
    CreateGridItems(12, 150.0f, 100.0f);
    CreateDone();

    FlushUITasks();
    for (int32_t i = 0; i < 6; i++) {
        EXPECT_EQ(GetChildSize(frameNode_, i).Width(), 150.0f);
    }
    EXPECT_EQ(GetChildSize(frameNode_, 1).Width(), 150.0f);
}

/**
 * @tc.name: Horizontal001
 * @tc.desc: Test horizontal layout
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, Horizontal001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo14());
    model.SetRowsGap(Dimension { 1.0f });
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedWidthItems(1, 910.0f);
    CreateFixedWidthItems(1, 300.0f);
    CreateFixedWidthItems(20, 605.0f);
    CreateFixedWidthItems(8, 300.0f);
    CreateDone();
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);

    layoutProperty_->UpdateRowsTemplate("1fr 1fr 1fr 1fr");
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    // print all content of gridMatrix_
    auto& info = pattern_->info_;
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_14_HORIZONTAL);
    for (int i = 0; i < 200; ++i) {
        UpdateCurrentOffset(50.0f);
    }
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.0f);
}

/**
 * @tc.name: ConstraintChange001
 * @tc.desc: Test width update
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, ConstraintChange001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo14());
    model.SetRowsGap(Dimension { 1.0f });
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedWidthItems(1, 460.0f);
    CreateFixedWidthItems(1, 150.0f);
    CreateFixedWidthItems(20, 305.0f);
    CreateFixedWidthItems(8, 150.0f);
    CreateDone();
    EXPECT_EQ(GetChildSize(frameNode_, 0).Height(), 199.5f);
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(200.0f)));
    FlushUITasks();
    EXPECT_EQ(GetChildSize(frameNode_, 0).Height(), 99.5f);
}

/**
 * @tc.name: GridIrregularLayout::OverScroll001
 * @tc.desc: Test overScroll disabled with long item
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, OverScroll001, TestSize.Level1)
{
    // GridItem's own ideal size has higher priority
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo12());
    model.SetColumnsGap(Dimension { 1.0f });
    model.SetEdgeEffect(EdgeEffect::NONE, true);
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 150.0f);
    CreateFixedHeightItems(1, 900.0f);
    CreateGridItems(4, -2, 150.0f);
    CreateDone();

    FlushUITasks();
    UpdateCurrentOffset(-225.0f);
    auto& info = pattern_->info_;
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_12);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.currentOffset_, -225.0f);
    EXPECT_FALSE(info.offsetEnd_);
    EXPECT_TRUE(info.reachEnd_);

    UpdateCurrentOffset(100.0f);
    EXPECT_EQ(info.currentOffset_, -125.0f);
    EXPECT_EQ(info.startIndex_, 0);

    UpdateCurrentOffset(-150.0f);
    EXPECT_EQ(info.currentOffset_, -275.0f);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_FALSE(info.offsetEnd_);
    EXPECT_TRUE(info.reachEnd_);

    UpdateCurrentOffset(100.0f);
    EXPECT_EQ(info.currentOffset_, -175.0f);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.startMainLineIndex_, 0);

    UpdateCurrentOffset(-150.0f);
    EXPECT_EQ(info.startIndex_, 2);
    EXPECT_EQ(info.currentOffset_, -175.0f);
    EXPECT_FALSE(info.offsetEnd_);
    EXPECT_TRUE(info.reachEnd_);
    EXPECT_EQ(info.GetIrregularHeight(0.0f), 1050.0f);
    EXPECT_EQ(info.GetIrregularOffset(0.0f), 325.0f);
}

/**
 * @tc.name: GridIrregularLayout::OverScroll002
 * @tc.desc: Test overScroll until completely out of viewport
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, OverScroll002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo13());
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 100.0f);
    CreateFixedHeightItems(1, 200.0f);
    CreateFixedHeightItems(1, 600.0f);
    CreateGridItems(5, -2, 100.0f);
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    ViewAbstract::SetHeight(CalcLength(300.0f));
    CreateDone();
    auto& info = pattern_->info_;
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    for (int i = 0; i < 10; ++i) {
        UpdateCurrentOffset(200.0f);
        EXPECT_EQ(info.startMainLineIndex_, 0);
        EXPECT_GT(info.currentOffset_, 0.0f);
    }
}

/**
 * @tc.name: GridIrregularLayout::OverScroll003
 * @tc.desc: Test overScroll until completely out of viewport
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, OverScroll003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo13());
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 100.0f);
    CreateFixedHeightItems(1, 200.0f);
    CreateFixedHeightItems(1, 600.0f);
    CreateGridItems(5, -2, 100.0f);
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    ViewAbstract::SetHeight(CalcLength(300.0f));
    CreateDone();
    auto& info = pattern_->info_;
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    // first move to end
    for (int i = 0; i < 4; ++i) {
        UpdateCurrentOffset(-200.0f);
    }
    EXPECT_EQ(info.currentOffset_, -300.0f);
    EXPECT_EQ(info.endMainLineIndex_, 10);
    EXPECT_TRUE(info.offsetEnd_);
    for (int i = 0; i < 10; ++i) {
        UpdateCurrentOffset(-200.0f);
        EXPECT_LT(info.currentOffset_, -499.9f);
        EXPECT_EQ(info.startMainLineIndex_, 5);
        EXPECT_EQ(info.startIndex_, 3);
        EXPECT_EQ(info.endMainLineIndex_, 10);
        EXPECT_EQ(info.endIndex_, 8);
    }
}

namespace {
const decltype(GridLayoutInfo::lineHeightMap_) cmp = { { 0, ITEM_MAIN_SIZE }, { 1, ITEM_MAIN_SIZE },
    { 2, ITEM_MAIN_SIZE }, { 3, ITEM_MAIN_SIZE }, { 6, ITEM_MAIN_SIZE }, { 7, ITEM_MAIN_SIZE }, { 8, ITEM_MAIN_SIZE },
    { 9, ITEM_MAIN_SIZE } };
}
/**
 * @tc.name: GetEndOffset000
 * @tc.desc: Test scrolling past limits
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, GetEndOffset000, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(20, GridItemStyle::NONE);
    CreateDone();

    int32_t targetIndex = 19;
    auto& info = pattern_->info_;
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    ScrollToIndex(targetIndex, false, ScrollAlign::END);
    for (int i = 0; i < 10; ++i) {
        UpdateCurrentOffset(-10000.0f);
    }
    EXPECT_EQ(info.lineHeightMap_, cmp);
    EXPECT_EQ(info.startMainLineIndex_, 9);
    EXPECT_EQ(info.endMainLineIndex_, 9);
    EXPECT_LT(info.currentOffset_, -10000.0f);
}

/**
 * @tc.name: GetEndOffset001
 * @tc.desc: Test GetEndOffset with updated offset
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, GetEndOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    CreateFixedItems(20, GridItemStyle::NONE);
    CreateDone();

    int32_t targetIndex = 19;
    ScrollAlign align = ScrollAlign::AUTO;
    ScrollToIndex(targetIndex, false, align);
    auto& info = pattern_->info_;
    EXPECT_EQ(info.startMainLineIndex_, 6);
    EXPECT_EQ(info.endMainLineIndex_, 9);
    info.currentOffset_ -= 500.0f;
    info.synced_ = false;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    pattern_->GetScrollEdgeEffect()->ProcessScrollOver(-1000.0f);
    EXPECT_TRUE(info.synced_);
    EXPECT_EQ(info.lineHeightMap_, cmp);
    EXPECT_EQ(info.currentOffset_, -200.0f);
    EXPECT_EQ(info.startMainLineIndex_, 9);
    EXPECT_EQ(info.endMainLineIndex_, 9);
    // last item should match up with the bottom again
    EXPECT_EQ(pattern_->GetEndOffset(), HEIGHT - ITEM_MAIN_SIZE);
}

/**
 * @tc.name: Delete001
 * @tc.desc: Test deleting items
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, Delete001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo15());
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedHeightItems(1, 150.0f);
    CreateFixedHeightItems(1, 100.0f);
    CreateGridItems(5, -2, 50.0f);
    CreateFixedHeightItems(1, 100.0f);
    CreateGridItems(9, -2, 50.0f);
    CreateDone();

    ScrollToIndex(9, false, ScrollAlign::CENTER);
    const auto& info = pattern_->info_;
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_15);

    frameNode_->RemoveChildAtIndex(9);
    layoutProperty_->UpdateLayoutOptions(GetOptionDemo16());
    frameNode_->ChildrenUpdatedFrom(0);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_16);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 14);

    ScrollToIndex(0, false, ScrollAlign::CENTER);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 13);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_16);

    frameNode_->ChildrenUpdatedFrom(9);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 13);

    UpdateCurrentOffset(-300.0f);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_16);
}

/**
 * @tc.name: Add001
 * @tc.desc: Test adding items
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, Add001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo15());
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedHeightItems(1, 150.0f);
    CreateFixedHeightItems(1, 100.0f);
    CreateGridItems(5, -2, 50.0f);
    CreateFixedHeightItems(1, 100.0f);
    CreateGridItems(9, -2, 50.0f);
    CreateDone();

    ScrollToIndex(9, false, ScrollAlign::CENTER);
    const auto& info = pattern_->info_;
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 16);

    AddFixedHeightItems(5, 50.0f);
    frameNode_->ChildrenUpdatedFrom(17);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 16);

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(info.startIndex_, 3);
    EXPECT_EQ(info.endIndex_, 21);
}

/**
 * @tc.name: Stretch001
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, Stretch001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        1, // [1 x 2]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 1) {
            return { .rows = 2, .columns = 1 };
        }
        return { .rows = 1, .columns = 1 };
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);

    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(option);

    CreateAdaptChildSizeGridItems(1);
    CreateFixedHeightItems(1, 150);
    CreateAdaptChildSizeGridItems(2);
    CreateFixedHeightItems(1, 150);

    CreateDone();
    FlushUITasks();

    auto childRect0 = pattern_->GetItemRect(0);
    EXPECT_EQ(childRect0.Height(), 0);

    auto childRect2 = pattern_->GetItemRect(2);
    EXPECT_EQ(childRect2.Height(), 0);

    auto childRect3 = pattern_->GetItemRect(3);
    auto childRect4 = pattern_->GetItemRect(4);
    EXPECT_EQ(childRect3.Height(), childRect4.Height());
}

/**
 * @tc.name: Stretch002
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, Stretch002, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 2]
        3, // [2 x 1]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 0) {
            return { .rows = 2, .columns = 2 };
        }
        return { .rows = 1, .columns = 2 };
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);

    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(option);

    CreateFixedHeightItems(1, 150);
    CreateAdaptChildSizeGridItems(2);
    CreateFixedHeightItems(1, 150);
    CreateAdaptChildSizeGridItems(1);

    CreateDone();
    FlushUITasks();

    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect1.Height(), 0);

    auto childRect2 = pattern_->GetItemRect(2);
    EXPECT_EQ(childRect2.Height(), 0);

    auto childRect4 = pattern_->GetItemRect(4);
    EXPECT_EQ(childRect4.Height(), 0);
}

/**
 * @tc.name: Test Skip large offset
 * @tc.desc: Test OnScrollIndex with big cachedCount by skip large offset
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, SkipLargeOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(16, false);
    model.SetLayoutOptions({});
    CreateFixedItems(100);
    CreateDone();

    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.startIndex_, 90);
    EXPECT_EQ(pattern_->info_.endIndex_, 99);

    pattern_->ScrollTo(ITEM_MAIN_SIZE * 5);
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.startIndex_, 15);
    EXPECT_EQ(pattern_->info_.endIndex_, 26);
}


/**
 * @tc.name: KeepFocus
 * @tc.desc: Test Grid focus keep when focused item is removed
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTestTwo, KeepFocus, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [1 x 3]
        2, // [2 x 3]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 0) {
            return { .rows = 1, .columns = 3 };
        }
        return { .rows = 2, .columns = 3 };
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);

    GridModelNG model = CreateRepeatGrid(30, [](uint32_t idx) {
        if (idx == 2) {
            return ITEM_MAIN_SIZE * 2;
        }
        return ITEM_MAIN_SIZE;
    });
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, true);
    model.SetLayoutOptions(option);
    CreateDone();
    FlushUITasks();

    /**
     * @tc.steps: step1. When focus grid from the outside
     * @tc.expected: Will focus first child
     */
    auto gridFocusNode = frameNode_->GetOrCreateFocusHub();
    gridFocusNode->RequestFocusImmediately();
    FlushUITasks();
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());

    /**
     * @tc.steps: step2. Scroll to sixth row
     * @tc.expected: item 0 scrolls out of viewport, lost focus to grid
     */
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE * 6, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetFocusedIndex(), 0);
    EXPECT_FALSE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());

    /**
     * @tc.steps: step3. Scroll to first row
     * @tc.expected: item 0 scrolls into viewport, keep focus
     */
    ScrollTo(0);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());
}
} // namespace OHOS::Ace::NG