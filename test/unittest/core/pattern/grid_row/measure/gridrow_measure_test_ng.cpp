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
#include "test/unittest/core/pattern/grid_row/grid_row_base_test_ng.h"
#include "core/components_v2/grid_layout/grid_container_utils.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr double DEFAULT_CHILD_HEIGHT = 30.0f;
} // namespace
class GridRowMeasureTestNG : public GridRowBaseTestNG {
public:
    string DumpChildrenInfo(std::list<ChildrenRow>& listOfChildren)
    {
        string result;
        for (auto &row : listOfChildren) {
            for (auto &child : row) {
                result += child.second.ToString();
            }
        }
        return result;
    }

    void CreateNewLineOffset(int32_t newLineCount, int32_t offset, int32_t span, float offsetY, NewLineOffset &result)
    {
        result.newLineCount = newLineCount;
        result.offset = offset;
        result.span = span;
        result.offsetY = offsetY;
    }
};

/**
 * @tc.name: GetSizeTypeAndMaxSizeTest01
 * @tc.desc: Test GetSizeTypeAndMaxSizeTest()
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, GetSizeTypeAndMaxSizeTest01, TestSize.Level0)
{
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        V2::BreakPoints breakpoints;
        breakpoints.reference = V2::BreakPointsReference::ComponentSize;
        breakpoints.breakpoints.assign({ "100px", "200px", "300px", "400px", "500px" });
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, breakpoints);
        ViewAbstract::SetBorderWidth(Dimension(5));
        ViewAbstract::SetPadding(CalcLength(5));
    });
    GridRowLayoutAlgorithm algorithm;
    LayoutConstraintF parentConstraint;
    SizeF maxSize;
    V2::GridSizeType sizeType;
    auto layoutProperty = gridRow->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    /**
     * @tc.expected: maxSize.Width = 100 - border - padding = 90
     *               sizeType = xs
     */
    parentConstraint.selfIdealSize = OptionalSizeF(100, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(80, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::XS);
    /**
     * @tc.expected: maxSize.Width = 200 - border - padding = 190
     *               sizeType = sm
     */
    parentConstraint.selfIdealSize = OptionalSizeF(200, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(180, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::SM);
    /**
     * @tc.expected: maxSize.Width = 300 - border - padding = 290
     *               sizeType = md
     */
    parentConstraint.selfIdealSize = OptionalSizeF(300, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(280, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::MD);
    /**
     * @tc.expected: maxSize.Width = 400 - border - padding = 390
     *               sizeType = lg
     */
    parentConstraint.selfIdealSize = OptionalSizeF(400, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(380, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::LG);
    /**
     * @tc.expected: maxSize.Width = 500 - border - padding = 490
     *               sizeType = xl
     */
    parentConstraint.selfIdealSize = OptionalSizeF(500, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(480, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::XL);
    /**
     * @tc.expected: maxSize.Width = 600 - border - padding = 590
     *               sizeType = xxl
     */
    parentConstraint.selfIdealSize = OptionalSizeF(600, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(580, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::XXL);
}

/**
 * @tc.name: GetSizeTypeAndMaxSizeTest02
 * @tc.desc: Test GetSizeTypeAndMaxSizeTest()
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, GetSizeTypeAndMaxSizeTest02, TestSize.Level0)
{
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        V2::BreakPoints breakpoints;
        breakpoints.reference = V2::BreakPointsReference::ComponentSize;
        breakpoints.breakpoints.assign({ "100px", "200px", "300px", "400px", "500px" });
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, breakpoints);
        ViewAbstract::SetBorderWidth(Dimension(5));
        ViewAbstract::SetPadding(CalcLength(5));
    });
    GridRowLayoutAlgorithm algorithm;
    SizeF maxSize;
    V2::GridSizeType sizeType;
    auto layoutProperty = gridRow->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    LayoutConstraintF parentConstraint;
    /**
     * @tc.expected: maxSize.Width = 100 - border - padding = 90
     *               sizeType = xs
     */
    parentConstraint.parentIdealSize = OptionalSizeF(100, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(80, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::XS);
    /**
     * @tc.expected: maxSize.Width = 200 - border - padding = 190
     *               sizeType = sm
     */
    parentConstraint.parentIdealSize = OptionalSizeF(200, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(180, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::SM);
    /**
     * @tc.expected: maxSize.Width = 300 - border - padding = 290
     *               sizeType = md
     */
    parentConstraint.parentIdealSize = OptionalSizeF(300, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(280, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::MD);
    /**
     * @tc.expected: maxSize.Width = 400 - border - padding = 390
     *               sizeType = lg
     */
    parentConstraint.parentIdealSize = OptionalSizeF(400, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(380, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::LG);
    /**
     * @tc.expected: maxSize.Width = 500 - border - padding = 490
     *               sizeType = xl
     */
    parentConstraint.parentIdealSize = OptionalSizeF(500, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(480, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::XL);
    /**
     * @tc.expected: maxSize.Width = 600 - border - padding = 590
     *               sizeType = xxl
     */
    parentConstraint.parentIdealSize = OptionalSizeF(600, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(580, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::XXL);
}

/**
 * @tc.name: ParseGridRowParamsTest01
 * @tc.desc: Test ParseGridRowParams()
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, ParseGridRowParamsTest01, TestSize.Level0)
{
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        V2::GridContainerSize columns;
        columns.xs = 2;
        columns.sm = 4;
        columns.md = 6;
        columns.lg = 8;
        columns.xl = 10;
        columns.xxl = 12;
        V2::Gutter gutter;
        gutter.xXs = gutter.yXs = Dimension(10);
        gutter.xSm = gutter.ySm = Dimension(20);
        gutter.xMd = gutter.yMd = Dimension(30);
        gutter.xLg = gutter.yLg = Dimension(40);
        gutter.xXl = gutter.yXl = Dimension(50);
        gutter.xXXl = gutter.yXXl = Dimension(60);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Columns, columns);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, gutter);
    });
    GridRowLayoutAlgorithm algorithm;
    /**
     * @tc.expected: columnUnitWidth_ = (100 - (2 - 1) * 10) / 2 = 45.f
     */
    algorithm.ParseGridRowParams(Referenced::RawPtr(gridRow), V2::GridSizeType::XS, SizeF(100, 30));
    EXPECT_EQ(algorithm.gutterInDouble_.first, 10);
    EXPECT_EQ(algorithm.gutterInDouble_.second, 10);
    EXPECT_EQ(algorithm.columnNum_, 2);
    EXPECT_EQ(algorithm.columnUnitWidth_, 45.0f);
    /**
     * @tc.expected: columnUnitWidth_ = (220 - (4 - 1) * 20) / 4 = 40.f
     */
    algorithm.ParseGridRowParams(Referenced::RawPtr(gridRow), V2::GridSizeType::SM, SizeF(220, 30));
    EXPECT_EQ(algorithm.gutterInDouble_.first, 20);
    EXPECT_EQ(algorithm.gutterInDouble_.second, 20);
    EXPECT_EQ(algorithm.columnNum_, 4);
    EXPECT_EQ(algorithm.columnUnitWidth_, 40.0f);
    /**
     * @tc.expected: columnUnitWidth_ = (300 - (6 - 1) * 30) / 6 = 25.0f
     */
    algorithm.ParseGridRowParams(Referenced::RawPtr(gridRow), V2::GridSizeType::MD, SizeF(300, 30));
    EXPECT_EQ(algorithm.gutterInDouble_.first, 30);
    EXPECT_EQ(algorithm.gutterInDouble_.second, 30);
    EXPECT_EQ(algorithm.columnNum_, 6);
    EXPECT_EQ(algorithm.columnUnitWidth_, 25.0f);
}

/**
 * @tc.name: ParseGridRowParamsTest02
 * @tc.desc: Test ParseGridRowParams()
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, ParseGridRowParamsTest02, TestSize.Level0)
{
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        V2::GridContainerSize columns;
        columns.xs = 2;
        columns.sm = 4;
        columns.md = 6;
        columns.lg = 8;
        columns.xl = 10;
        columns.xxl = 12;
        V2::Gutter gutter;
        gutter.xXs = gutter.yXs = Dimension(10);
        gutter.xSm = gutter.ySm = Dimension(20);
        gutter.xMd = gutter.yMd = Dimension(30);
        gutter.xLg = gutter.yLg = Dimension(40);
        gutter.xXl = gutter.yXl = Dimension(50);
        gutter.xXXl = gutter.yXXl = Dimension(60);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Columns, columns);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, gutter);
    });
    GridRowLayoutAlgorithm algorithm;
    /**
     * @tc.expected: columnUnitWidth_ = (400 - (8 - 1) * 40) / 8 = 15.f
     */
    algorithm.ParseGridRowParams(Referenced::RawPtr(gridRow), V2::GridSizeType::LG, SizeF(400, 30));
    EXPECT_EQ(algorithm.gutterInDouble_.first, 40);
    EXPECT_EQ(algorithm.gutterInDouble_.second, 40);
    EXPECT_EQ(algorithm.columnNum_, 8);
    EXPECT_EQ(algorithm.columnUnitWidth_, 15.0f);
    /**
     * @tc.expected: columnUnitWidth_ = (500 - (10 - 1) * 50) / 10 = 5.f
     */
    algorithm.ParseGridRowParams(Referenced::RawPtr(gridRow), V2::GridSizeType::XL, SizeF(500, 30));
    EXPECT_EQ(algorithm.gutterInDouble_.first, 50);
    EXPECT_EQ(algorithm.gutterInDouble_.second, 50);
    EXPECT_EQ(algorithm.columnNum_, 10);
    EXPECT_EQ(algorithm.columnUnitWidth_, 5.0f);
    /**
     * @tc.expected: columnUnitWidth_ = (1260 - (12 - 1) * 60) / 12 = 50.f
     */
    algorithm.ParseGridRowParams(Referenced::RawPtr(gridRow), V2::GridSizeType::XXL, SizeF(1260, 30));
    EXPECT_EQ(algorithm.gutterInDouble_.first, 60);
    EXPECT_EQ(algorithm.gutterInDouble_.second, 60);
    EXPECT_EQ(algorithm.columnNum_, 12);
    EXPECT_EQ(algorithm.columnUnitWidth_, 50.0f);
}

/**
 * @tc.name: MeasureSelfTest
 * @tc.desc: Test MeasureSelf
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, MeasureSelfTest, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
    });
    LayoutConstraintF constraint;
    constraint.UpdateIllegalSelfIdealSizeWithCheck({std::nullopt, 60.f});
    auto layoutProperty = gridRow->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(constraint);
    pipeline->SetMinPlatformVersion(9);
    GridRowLayoutAlgorithm algorithm;
    algorithm.MeasureSelf(Referenced::RawPtr(gridRow), 30.f, 60.f);
    auto gridRowHeight = gridRow->GetGeometryNode()->GetFrameSize().Height();
    /**
     * @tc.expected: gridRowHeight equal to childHeight 30.0f when API < 10
     */
    EXPECT_EQ(gridRowHeight, 30.0f) << gridRowHeight;
    pipeline->SetMinPlatformVersion(12);
    algorithm.MeasureSelf(Referenced::RawPtr(gridRow), 30.f, 60.f);
    gridRowHeight = gridRow->GetGeometryNode()->GetFrameSize().Height();
    /**
     * @tc.expected: gridRowHeight equal to selfHeight 60.0f when API >= 11
     */
    EXPECT_EQ(gridRowHeight, 60.f) << gridRowHeight;

    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
    algorithm.MeasureSelf(Referenced::RawPtr(gridRow), 90.f, 60.f);
    /**
     * @tc.expected: gridRowHeight is equal to the childHeight
     */
    gridRowHeight = gridRow->GetGeometryNode()->GetFrameSize().Height();
    EXPECT_EQ(gridRowHeight, 90.f) << gridRowHeight;

    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
    algorithm.MeasureSelf(Referenced::RawPtr(gridRow), 90.f, 60.f);
    /**
     * @tc.expected: gridRowHeight equal to the childHeight, which ignores parent constraint
     */
    gridRowHeight = gridRow->GetGeometryNode()->GetFrameSize().Height();
    EXPECT_EQ(gridRowHeight, 90.f) << gridRowHeight;

    constraint.UpdateParentIdealSizeWithCheck({std::nullopt, 90.f});
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    layoutProperty->ClearUserDefinedIdealSize(true, true);
    algorithm.MeasureSelf(Referenced::RawPtr(gridRow), 30.f, 90.f);
    gridRowHeight = gridRow->GetGeometryNode()->GetFrameSize().Height();
    /**
     * @tc.expected: gridRow matchParent height = 90
     */
    EXPECT_EQ(gridRowHeight, 90.f) << gridRowHeight;
}

/**
 * @tc.name: MeasureChildrenTest
 * @tc.desc: Test MeasureChildren function
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, MeasureChildrenTest, TestSize.Level0)
{
    RefPtr<FrameNode> gridCol1, gridCol2, gridCol3, gridCol4, gridCol5;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2, &gridCol3, &gridCol4, &gridCol5](GridRowModelNG model) {
        ViewAbstract::SetHeight(CalcLength(180.0f));
        ViewAbstract::SetWidth(CalcLength(350.0f));
        V2::Gutter gutter(Dimension(10));
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, gutter);
        gridCol1 = CreateGridColWithProperty(2, 0, 10);
        gridCol2 = CreateGridColWithProperty(4, 2, 20);
        gridCol3 = CreateGridColWithProperty(6, 26, 30);
        gridCol4 = CreateGridColWithProperty(6, 20, 40);
        gridCol5 = CreateGridColWithProperty(2, 0, 30);
    });
    GridRowLayoutAlgorithm algorithm;
    algorithm.gutterInDouble_ = std::make_pair(10, 10);
    algorithm.columnUnitWidth_ = 20.0f;
    algorithm.columnNum_ = 12;
    /**
     * @tc.expected: totalHeight = (3 * 20 + 10) + (2 * 30 + 10) + 40
     */
    auto gutter = std::make_pair<double, double>(10, 10);
    auto totalHeight = algorithm.MeasureChildren(Referenced::RawPtr(gridRow), 20.0f, 0, gutter,
        V2::GridSizeType::XS, 12);
    EXPECT_EQ(totalHeight, 180) << totalHeight;
    auto result = DumpChildrenInfo(algorithm.gridColChildrenRows_);
    std::string expected;
    NewLineOffset expectResult;
    CreateNewLineOffset(0, 0, 2, 0, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 4, 4, 0, expectResult);
    expected += expectResult.ToString();
    /**
     * @tc.expected: the offsetY of the second line should be 3 * firstlineHeight + gutter.y
     */
    CreateNewLineOffset(3, 0, 6, 70, expectResult);
    expected += expectResult.ToString();
    /**
     * @tc.expected: the offsetY of the third line should be 2 * secondlineHeight + gutter.y
     */
    CreateNewLineOffset(2, 2, 6, 140, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 8, 2, 140, expectResult);
    expected += expectResult.ToString();
    EXPECT_EQ(result, expected) << result;
    /**
     * @tc.expected: the frameSize of each child is correct
     */
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetFrameSize(), SizeF(50, 10))
        << gridCol1->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol2->GetGeometryNode()->GetFrameSize(), SizeF(110, 20))
        << gridCol2->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol3->GetGeometryNode()->GetFrameSize(), SizeF(170, 30))
        << gridCol3->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol4->GetGeometryNode()->GetFrameSize(), SizeF(170, 40))
        << gridCol4->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol5->GetGeometryNode()->GetFrameSize(), SizeF(50, 30))
        << gridCol5->GetGeometryNode()->GetFrameSize().ToString();
}

/**
 * @tc.name: MeasureChildTest
 * @tc.desc: MeasureChild should measure children correctly according to the layout constraint
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, MeasureChildTest, TestSize.Level0)
{
    RefPtr<FrameNode> gridCol1;
    auto gridRow = CreateGridRow([this, &gridCol1](GridRowModelNG model) {
        ViewAbstract::SetHeight(CalcLength(40.0f));
        ViewAbstract::SetWidth(CalcLength(350.0f));
        V2::Gutter gutter(Dimension(10));
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, gutter);
        gridCol1 = CreateGridCol([this](GridColModelNG model) {
            CreateRow([this](RowModelNG model) {
                ViewAbstract::SetHeight(CalcLength(30.0f));
                ViewAbstract::SetWidth(CalcLength(10.0f));
            });
        });
    });
    GridRowLayoutAlgorithm algorithm;
    algorithm.columnUnitWidth_ = 20.0f;
    algorithm.columnNum_ = 12;
    LayoutConstraintF parentConstraint;
    auto layoutProperty = gridRow->GetLayoutProperty();
    parentConstraint.maxSize = SizeF(100, 40.0f);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    layoutProperty->UpdateContentConstraint();
    auto childLayoutWrapper = AceType::DynamicCast<LayoutWrapper>(gridCol1);
    algorithm.MeasureChild(Referenced::RawPtr(gridRow), childLayoutWrapper,
        V2::GridSizeType::XS, 30.0f);
    /**
     * @tc.expected: child height is constrained by maxheight = 40 - totalheight(30) = 10
     */
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetFrameSize(), SizeF(20, 10))
        << gridCol1->GetGeometryNode()->GetFrameSize().ToString();
}
} // namespace OHOS::Ace::NG
