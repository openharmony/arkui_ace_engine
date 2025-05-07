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

#include "test/unittest/core/pattern/relative_container/relative_container_base_test_ng.h"
using namespace std;

namespace OHOS::Ace::NG {

class RelativeContainerMeasureTest : public RelativeContainerBaseTestNG {
public:
    static string TestRenderList(std::list<std::string>& renderList)
    {
        string res;
        res += "[";
        for (auto it = renderList.begin(); it != renderList.end(); ++it) {
            res += *it;
            if (std::next(it) != renderList.end()) {
                res += ", ";
            }
        }
        res += "]";
        return res;
    }
};

/**
 * @tc.desc: Test UpdateSizeWhenChildrenEmpty, set width and height.
 */
HWTEST_F(RelativeContainerMeasureTest, UpdateSizeWhenChildrenEmptyTest1, TestSize.Level1)
{
    // step: make node & property
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(20));
        ViewAbstract::SetHeight(CalcLength(20));
    });

    // step: make constraint
    LayoutConstraintF constraint = {
        .percentReference = { 30, 30 }, // {width, height}
        .parentIdealSize = { 40, 40 },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.UpdateSizeWhenChildrenEmpty(Referenced::RawPtr(relativeContainer));
    // expect: widht/height > parentIdealSize > percentReference
    EXPECT_EQ(relativeContainer->GetGeometryNode()->GetFrameSize(), SizeF(20, 20))
        << relativeContainer->GetGeometryNode()->GetFrameSize().ToString();
}

/**
 * @tc.desc: Test UpdateSizeWhenChildrenEmpty, without height and width
 */
HWTEST_F(RelativeContainerMeasureTest, UpdateSizeWhenChildrenEmptyTest2, TestSize.Level1)
{
    // node & property
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {});

    // constraint
    LayoutConstraintF constraint = {
        .percentReference = { 30, 30 }, // {width, height}
        .parentIdealSize = { 40, 40 },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.UpdateSizeWhenChildrenEmpty(Referenced::RawPtr(relativeContainer));
    // expect: widht/height > parentIdealSize > percentReference
    EXPECT_EQ(relativeContainer->GetGeometryNode()->GetFrameSize(), SizeF(40, 40))
        << relativeContainer->GetGeometryNode()->GetFrameSize().ToString();
}

/**
 * @tc.desc: Test UpdateSizeWhenChildrenEmpty, use auto.
 */
HWTEST_F(RelativeContainerMeasureTest, UpdateSizeWhenChildrenEmptyTest3, TestSize.Level1)
{
    // node & property
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(0.0f, DimensionUnit::AUTO));
        ViewAbstract::SetBorderWidth(Dimension(3));
    });

    // constraint
    LayoutConstraintF constraint = {
        .percentReference = { 30, 30 }, // {width, height}
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.UpdateSizeWhenChildrenEmpty(Referenced::RawPtr(relativeContainer));
    // expect: width = left paddingg + right padding = 3 + 3 = 6
    EXPECT_EQ(relativeContainer->GetGeometryNode()->GetFrameSize(), SizeF(6, 30))
        << relativeContainer->GetGeometryNode()->GetFrameSize().ToString();
}

/**
 * @tc.desc: Test Initialize, has width and height.
 */
HWTEST_F(RelativeContainerMeasureTest, InitializeTest, TestSize.Level1)
{
    // node & property
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(20));
        ViewAbstract::SetHeight(CalcLength(20));
        ViewAbstract::SetBorderWidth(Dimension(3));
    });

    // constraint
    LayoutConstraintF constraint = {
        .percentReference = { 30, 30 }, // width/height > percentReference, unused.
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Initialize(Referenced::RawPtr(relativeContainer));
    EXPECT_EQ(relativeContainer->GetGeometryNode()->GetFrameSize(), SizeF(20, 20))
        << relativeContainer->GetGeometryNode()->GetFrameSize().ToString();
    // expect containerSizeWithoutPaddingBorder_.width = width - border.left - border.right = 20 - 6 = 14
    EXPECT_EQ(layoutAlgorithm.containerSizeWithoutPaddingBorder_, SizeF(14, 14))
        << layoutAlgorithm.containerSizeWithoutPaddingBorder_.ToString();
}

/**
 * @tc.desc: Test Initialize, use maxSize.
 */
HWTEST_F(RelativeContainerMeasureTest, InitializeTest2, TestSize.Level1)
{
    // node & property
    auto relativeContainer =
        CreateRelativeContainer([this](RelativeContainerModelNG model) { ViewAbstract::SetHeight(CalcLength(20)); });

    // constraint
    LayoutConstraintF constraint = { .parentIdealSize = { 30, 30 }, .maxSize = { 25, 25 } };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Initialize(Referenced::RawPtr(relativeContainer));
    // expect: (maxSize.width, height)
    EXPECT_EQ(relativeContainer->GetGeometryNode()->GetFrameSize(), SizeF(25, 20))
        << relativeContainer->GetGeometryNode()->GetFrameSize().ToString();
}

HWTEST_F(RelativeContainerMeasureTest, CollectNodesByIdTest, TestSize.Level1)
{
    // create three child nodes
    auto relativeContainer = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        CreateText(u"text1", [](TextModelNG model) { ViewAbstract::SetInspectorId("text1"); });
        CreateRow([](RowModelNG model) { ViewAbstract::SetInspectorId("row1"); });
        // column don't have InspectorId
        CreateColumn([](ColumnModelNG model) {});
    });

    const auto&& children = relativeContainer->GetAllChildrenWithBuild();
    ASSERT_EQ(children.size(), 3);

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.CollectNodesById(Referenced::RawPtr(relativeContainer));

    auto&& idNodeMap = layoutAlgorithm.idNodeMap_;
    // expect: text is added to idNodeMap_ , id = "text1".
    EXPECT_NE(idNodeMap.find("text1"), idNodeMap.end());
    // expect: row is added to idNodeMap_, id = "row1".
    EXPECT_NE(idNodeMap.find("row1"), idNodeMap.end());
    // expect: column is added to idNodeMap_ , id = "@concat" + tag + id = "@concatColumn-1".
    EXPECT_NE(idNodeMap.find("@concatColumn-1"), idNodeMap.end());
}

HWTEST_F(RelativeContainerMeasureTest, GetDependencyRelationshipTest, TestSize.Level1)
{
    // create three child nodes with alignRules
    auto relativeContainer = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row1");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
            ViewAbstract::SetAlignRules(alignRules);
        });
        CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row2");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "row1", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::LEFT, "row1", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
        CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row3");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "row2", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::LEFT, "row2", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
    });

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    // create idNodeMap_
    layoutAlgorithm.CollectNodesById(Referenced::RawPtr(relativeContainer));
    // run GetDependencyRelationship()
    layoutAlgorithm.GetDependencyRelationship();
    auto& reliedOnMap = layoutAlgorithm.reliedOnMap_;
    EXPECT_EQ(PrintReliedOnMap(reliedOnMap, "row1"), "[row2]");
    EXPECT_EQ(PrintReliedOnMap(reliedOnMap, "row2"), "[row3]");
    EXPECT_EQ(PrintReliedOnMap(reliedOnMap, "__container__"), "Doesn't exist");
}

/**
 * @tc.desc: Test PreTopologicalLoopDetectionT
    dependence: layoutWrapper, idNodeMap_, reliedOnMap_
    input: loop child nodes
    output: detect whether node loop dependency exists (true or false).
 */
HWTEST_F(RelativeContainerMeasureTest, PreTopologicalLoopDetectionTest, TestSize.Level1)
{
    // create three child nodes with alignRules
    auto relativeContainer = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row1");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
            ViewAbstract::SetAlignRules(alignRules);
        });
        CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row2");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "row3", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::LEFT, "row3", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
        CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row3");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "row2", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::LEFT, "row2", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
    });

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    // create idNodeMap_
    layoutAlgorithm.CollectNodesById(Referenced::RawPtr(relativeContainer));
    // create reliedOnMap_
    layoutAlgorithm.GetDependencyRelationship();
    // run and test PreTopologicalLoopDetection
    // expect: !incomingDegreeMapCopy.empty() == true
    EXPECT_TRUE(!layoutAlgorithm.PreTopologicalLoopDetection(Referenced::RawPtr(relativeContainer)));
}

/**
 * @tc.desc: Test PreTopologicalLoopDetectionT
    dependence: idNodeMap_, reliedOnMap_ , incomingDegreeMap_
    output: renderList
 */
HWTEST_F(RelativeContainerMeasureTest, TopologicalSortTest, TestSize.Level1)
{
    // create three child nodes with alignRules
    auto relativeContainer = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row1");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
            ViewAbstract::SetAlignRules(alignRules);
        });
        CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row2");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "row1", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::LEFT, "row1", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
        CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row3");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "row2", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::LEFT, "row2", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
    });

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    // create idNodeMap_
    layoutAlgorithm.CollectNodesById(Referenced::RawPtr(relativeContainer));
    // create reliedOnMap_
    layoutAlgorithm.GetDependencyRelationship();
    // run PreTopologicalLoopDetection, create incomingDegreeMap_
    // expect: incomingDegreeMapCopy.empty() == true
    EXPECT_TRUE(layoutAlgorithm.PreTopologicalLoopDetection(Referenced::RawPtr(relativeContainer)));

    std::list<std::string> renderList;
    // run TopologicalSort
    layoutAlgorithm.TopologicalSort(renderList);
    // expect nodes in renderList:
    EXPECT_STREQ(TestRenderList(renderList).c_str(), "[row1, row2, row3]");
}

/**
 * @tc.desc: Test MeasureChild
    dependence: renderList_, reliedOnMap_ , incomingDegreeMap_
    output: renderList、recordOffsetMap_
 */
HWTEST_F(RelativeContainerMeasureTest, MeasureChildTest, TestSize.Level1)
{
    // create three child nodes with alignRules
    RefPtr<FrameNode> row1, row2, row3;
    auto relativeContainer = CreateRelativeContainer([this, &row1, &row2, &row3](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(100));
        ViewAbstract::SetBorderWidth(Dimension(3));
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row1");
            ViewAbstract::SetWidth(CalcLength(30));
            ViewAbstract::SetHeight(CalcLength(30));
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::CENTER);
            ViewAbstract::SetAlignRules(alignRules);
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row2");
            ViewAbstract::SetWidth(CalcLength(30));
            ViewAbstract::SetHeight(CalcLength(30));
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "row1", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::LEFT, "row1", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
        row3 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row3");
            ViewAbstract::SetWidth(CalcLength(30));
            ViewAbstract::SetHeight(CalcLength(30));
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "row2", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::LEFT, "row2", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
    });

    // constraint
    LayoutConstraintF constraint = {
        .percentReference = { 100, 100 }, // {width, height}
        .parentIdealSize = { 100, 100 },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    // used when creating child constraint
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;

    // dependence: renderList_, reliedOnMap_ , incomingDegreeMap_
    PrepareMeasureChild(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // run MeasureChild
    layoutAlgorithm.MeasureChild(Referenced::RawPtr(relativeContainer));
    // expect: when child has alignRules and position, the universal-attribute position property do not work.
    EXPECT_FALSE(row1->GetLayoutProperty()->IsUsingPosition());
    EXPECT_FALSE(row2->GetLayoutProperty()->IsUsingPosition());
    EXPECT_FALSE(row3->GetLayoutProperty()->IsUsingPosition());

    // expect row1 GetAlignLeftValue() = containerSizeWithoutPaddingBorder_ = 0.5 * (width - 2 * borderwidth)
    EXPECT_EQ(row1->GetLayoutProperty()->GetFlexItemProperty()->GetAlignLeftValue(), 47);
    EXPECT_EQ(row2->GetLayoutProperty()->GetFlexItemProperty()->GetAlignLeftValue(), 77);
    EXPECT_EQ(row3->GetLayoutProperty()->GetFlexItemProperty()->GetAlignLeftValue(), 107);

    // expect: all child nodes are aligned to the top
    EXPECT_EQ(row1->GetLayoutProperty()->GetFlexItemProperty()->GetAlignTopValue(), 0);
    EXPECT_EQ(row2->GetLayoutProperty()->GetFlexItemProperty()->GetAlignTopValue(), 0);
    EXPECT_EQ(row3->GetLayoutProperty()->GetFlexItemProperty()->GetAlignTopValue(), 0);

    // expect: all child nodes offset are stored in the recordOffsetMap_.
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["row1"], OffsetF(47, 0))
        << layoutAlgorithm.recordOffsetMap_["row1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["row2"], OffsetF(77, 0))
        << layoutAlgorithm.recordOffsetMap_["row2"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["row3"], OffsetF(107, 0))
        << layoutAlgorithm.recordOffsetMap_["row3"].ToString();
}

/**
 * @tc.desc: Test MeasureChild2, test child has two alignRules, RIGHT&LEFT, TOP&BOTTOM
    dependence: renderList_
    output: recordOffsetMap_, child measure.
 */
HWTEST_F(RelativeContainerMeasureTest, MeasureChildTest2, TestSize.Level1)
{
    // create three child nodes with alignRules
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer([this, &row1](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(100));
        ViewAbstract::SetBorderWidth(Dimension(3));
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row1");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::RIGHT, "__container__", HorizontalAlign::CENTER);
            AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
            AddAlignRule(alignRules, AlignDirection::BOTTOM, "__container__", VerticalAlign::CENTER);
            AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
            ViewAbstract::SetAlignRules(alignRules);
        });
    });

    // constraint
    LayoutConstraintF constraint = {
        .percentReference = { 100, 100 }, // {width, height}
        .parentIdealSize = { 100, 100 },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    // used when creating child constraint
    // containerSizeWithoutPaddingBorder_ = (width, height) = (100 - 2 * borderwidth, 100 - 2 * borderwidth) = (94, 94)
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;

    // prepare renderList_
    PrepareMeasureChild(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // run MeasureChild
    layoutAlgorithm.MeasureChild(Referenced::RawPtr(relativeContainer));

    // expect row1 GetAlignLeftValue() = 0.0f
    EXPECT_EQ(row1->GetLayoutProperty()->GetFlexItemProperty()->GetAlignLeftValue(), 0);
    // expect row1 GetAlignRightValue() = containerSizeWithoutPaddingBorder_.width * 0.5 = 47
    EXPECT_EQ(row1->GetLayoutProperty()->GetFlexItemProperty()->GetAlignRightValue(), 47);
    // expect row1 GetAlignTopValue() = 0.0f
    EXPECT_EQ(row1->GetLayoutProperty()->GetFlexItemProperty()->GetAlignTopValue(), 0);
    // expect row1 GetAlignBottomValue() = containerSizeWithoutPaddingBorder_.height * 0.5 = 47
    EXPECT_EQ(row1->GetLayoutProperty()->GetFlexItemProperty()->GetAlignBottomValue(), 47);

    // expect: CalcSizeParam -> = (right - left, bottom - top) = (47, 47)
    EXPECT_EQ(row1->GetGeometryNode()->GetMarginFrameSize(), SizeF(47, 47))
        << row1->GetGeometryNode()->GetMarginFrameSize().ToString();

    // expect: all child nodes offset are stored in the recordOffsetMap_.
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["row1"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["row1"].ToString();
}

/**
 * @tc.desc: Test MeasureChild3, test child has two alignRules, MIDDLE&LEFT, CENTER&TOP
    dependence: renderList_
    output: recordOffsetMap_, child measure.
 */
HWTEST_F(RelativeContainerMeasureTest, MeasureChildTest3, TestSize.Level1)
{
    // create three child nodes with alignRules
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer([this, &row1](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(100));
        ViewAbstract::SetBorderWidth(Dimension(3));
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row1");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::MIDDLE, "__container__", HorizontalAlign::CENTER);
            AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
            AddAlignRule(alignRules, AlignDirection::CENTER, "__container__", VerticalAlign::CENTER);
            AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
            ViewAbstract::SetAlignRules(alignRules);
        });
    });

    // constraint
    LayoutConstraintF constraint = {
        .percentReference = { 100, 100 }, // {width, height}
        .parentIdealSize = { 100, 100 },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    // used when creating child constraint
    // containerSizeWithoutPaddingBorder_ = (width, height) = (100 - 2 * borderwidth, 100 - 2 * borderwidth) = (94, 94)
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;

    // prepare renderList_
    PrepareMeasureChild(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // run MeasureChild
    layoutAlgorithm.MeasureChild(Referenced::RawPtr(relativeContainer));

    // expect row1 GetAlignLeftValue() = 0.0f
    EXPECT_EQ(row1->GetLayoutProperty()->GetFlexItemProperty()->GetAlignLeftValue(), 0);
    // expect row1 GetAlignMiddleValue() = containerSizeWithoutPaddingBorder_.width * 0.5 = 47
    EXPECT_EQ(row1->GetLayoutProperty()->GetFlexItemProperty()->GetAlignMiddleValue(), 47);
    // expect row1 GetAlignTopValue() = 0.0f
    EXPECT_EQ(row1->GetLayoutProperty()->GetFlexItemProperty()->GetAlignTopValue(), 0);
    // expect row1 GetAlignCenterValue() = containerSizeWithoutPaddingBorder_.height * 0.5 = 47
    EXPECT_EQ(row1->GetLayoutProperty()->GetFlexItemProperty()->GetAlignCenterValue(), 47);

    // expect: CalcSizeParam -> = ((midde - left)*2, (bottom - top)*2) = (94, 94)
    EXPECT_EQ(row1->GetGeometryNode()->GetMarginFrameSize(), SizeF(94, 94))
        << row1->GetGeometryNode()->GetMarginFrameSize().ToString();

    // expect: CalcOffsetParam -> all child nodes offset are stored in the recordOffsetMap_.
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["row1"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["row1"].ToString();
}

/**
 * @tc.desc: Test MeasureChild, test child has two alignRules, MIDDLE&RIGHT, CENTER&BOTTOM
    dependence: renderList_
    output: recordOffsetMap_, measure child.
 */
HWTEST_F(RelativeContainerMeasureTest, MeasureChildTest4, TestSize.Level1)
{
    // create three child nodes with alignRules
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer([this, &row1](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(100));
        ViewAbstract::SetBorderWidth(Dimension(3));
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row1");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::MIDDLE, "__container__", HorizontalAlign::CENTER);
            AddAlignRule(alignRules, AlignDirection::RIGHT, "__container__", HorizontalAlign::END);
            AddAlignRule(alignRules, AlignDirection::CENTER, "__container__", VerticalAlign::CENTER);
            AddAlignRule(alignRules, AlignDirection::BOTTOM, "__container__", VerticalAlign::BOTTOM);
            ViewAbstract::SetAlignRules(alignRules);
        });
    });

    // constraint
    LayoutConstraintF constraint = {
        .percentReference = { 100, 100 }, // {width, height}
        .parentIdealSize = { 100, 100 },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    // used when creating child constraint
    // containerSizeWithoutPaddingBorder_ = (width, height) = (100 - 2 * borderwidth, 100 - 2 * borderwidth) = (94, 94)
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;

    // prepare renderList_
    PrepareMeasureChild(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // run MeasureChild
    layoutAlgorithm.MeasureChild(Referenced::RawPtr(relativeContainer));

    // expect row1 GetAlignRightValue() = containerSizeWithoutPaddingBorder_.width = 94
    EXPECT_EQ(row1->GetLayoutProperty()->GetFlexItemProperty()->GetAlignRightValue(), 94);
    // expect row1 GetAlignRightValue() = containerSizeWithoutPaddingBorder_.width * 0.5 = 47
    EXPECT_EQ(row1->GetLayoutProperty()->GetFlexItemProperty()->GetAlignMiddleValue(), 47);
    // expect row1 GetAlignBottomValue() = containerSizeWithoutPaddingBorder_.height = 94
    EXPECT_EQ(row1->GetLayoutProperty()->GetFlexItemProperty()->GetAlignBottomValue(), 94);
    // expect row1 GetAlignCenterValue() = containerSizeWithoutPaddingBorder_.height * 0.5 = 47
    EXPECT_EQ(row1->GetLayoutProperty()->GetFlexItemProperty()->GetAlignCenterValue(), 47);

    // expect: CalcSizeParam -> = ((midde - left)*2, (bottom - top)*2) = (94, 94)
    EXPECT_EQ(row1->GetGeometryNode()->GetMarginFrameSize(), SizeF(94, 94))
        << row1->GetGeometryNode()->GetMarginFrameSize().ToString();

    // expect: CalcOffsetParam -> all child nodes offset are stored in the recordOffsetMap_.
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["row1"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["row1"].ToString();
}

/**
 * @tc.desc: Test MeasureChild, test the offsets of different pairs of alignRules.
    dependence: renderList_
    output: recordOffsetMap_, measure child.
 */
HWTEST_F(RelativeContainerMeasureTest, MeasureChildTest5, TestSize.Level1)
{
    // create three child nodes with alignRules
    RefPtr<FrameNode> row1, row2, row3;
    auto relativeContainer = CreateRelativeContainer([this, &row1, &row2, &row3](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(100));
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row1");
            ViewAbstract::SetWidth(CalcLength(50));
            ViewAbstract::SetHeight(CalcLength(50));
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::CENTER);
            AddAlignRule(alignRules, AlignDirection::MIDDLE, "__container__", HorizontalAlign::START);
            ViewAbstract::SetAlignRules(alignRules);
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row2");
            ViewAbstract::SetWidth(CalcLength(50));
            ViewAbstract::SetHeight(CalcLength(50));
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::BOTTOM);
            AddAlignRule(alignRules, AlignDirection::MIDDLE, "__container__", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
        row3 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row3");
            ViewAbstract::SetWidth(CalcLength(50));
            ViewAbstract::SetHeight(CalcLength(50));
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::CENTER, "__container__", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::RIGHT, "__container__", HorizontalAlign::START);
            ViewAbstract::SetAlignRules(alignRules);
        });
    });

    // constraint
    LayoutConstraintF constraint = {
        .percentReference = { 100, 100 }, // {width, height}
        .parentIdealSize = { 100, 100 },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    // used when creating child constraint
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;

    // prepare renderList_
    PrepareMeasureChild(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // run MeasureChild
    layoutAlgorithm.MeasureChild(Referenced::RawPtr(relativeContainer));

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["row1"], OffsetF(-25, 50))
        << layoutAlgorithm.recordOffsetMap_["row1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["row2"], OffsetF(75, 100))
        << layoutAlgorithm.recordOffsetMap_["row2"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["row3"], OffsetF(-50, -25))
        << layoutAlgorithm.recordOffsetMap_["row3"].ToString();
}

/**
 * @tc.desc: Test MeasureChild, test the offsets of different pairs of alignRules.
    dependence: renderList_
    output: recordOffsetMap_, measure child.
 */
HWTEST_F(RelativeContainerMeasureTest, MeasureChildTest6, TestSize.Level1)
{
    // create three child nodes with alignRules
    RefPtr<FrameNode> row1, row2;
    auto relativeContainer = CreateRelativeContainer([this, &row1, &row2](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(100));
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row1");
            ViewAbstract::SetWidth(CalcLength(50));
            ViewAbstract::SetHeight(CalcLength(50));
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::CENTER, "__container__", VerticalAlign::BOTTOM);
            AddAlignRule(alignRules, AlignDirection::RIGHT, "__container__", HorizontalAlign::CENTER);
            ViewAbstract::SetAlignRules(alignRules);
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row2");
            ViewAbstract::SetWidth(CalcLength(50));
            ViewAbstract::SetHeight(CalcLength(50));
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::BOTTOM, "__container__", VerticalAlign::BOTTOM);
            AddAlignRule(alignRules, AlignDirection::RIGHT, "__container__", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
    });

    // constraint
    LayoutConstraintF constraint = {
        .percentReference = { 100, 100 }, // {width, height}
        .parentIdealSize = { 100, 100 },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    // used when creating child constraint
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;

    // prepare renderList_
    PrepareMeasureChild(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // run MeasureChild
    layoutAlgorithm.MeasureChild(Referenced::RawPtr(relativeContainer));

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["row1"], OffsetF(0, 75))
        << layoutAlgorithm.recordOffsetMap_["row1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["row2"], OffsetF(50, 50))
        << layoutAlgorithm.recordOffsetMap_["row2"].ToString();
}

/**
 * @tc.name: MeasureSelfTest1
 * @tc.desc: Test relative container with auto height or auto width.
 */
HWTEST_F(RelativeContainerMeasureTest, MeasureSelfTest1, TestSize.Level1)
{
    // create three child nodes with alignRules
    RefPtr<FrameNode> row1, row2;
    auto relativeContainer = CreateRelativeContainer([this, &row1, &row2](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(0.0f, DimensionUnit::AUTO));
        ViewAbstract::SetHeight(CalcLength(0.0f, DimensionUnit::AUTO));
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row1");
            ViewAbstract::SetWidth(CalcLength(50));
            ViewAbstract::SetHeight(CalcLength(50));
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::CENTER, "__container__", VerticalAlign::BOTTOM);
            AddAlignRule(alignRules, AlignDirection::RIGHT, "__container__", HorizontalAlign::CENTER);
            ViewAbstract::SetAlignRules(alignRules);
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row2");
            ViewAbstract::SetWidth(CalcLength(10));
            ViewAbstract::SetHeight(CalcLength(10));
        });
    });

    // constraint
    LayoutConstraintF constraint = {
        .percentReference = { 80, 80 }, // {width, height}
        .parentIdealSize = { 90, 90 },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    // used when creating child constraint
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    // prepare renderList_
    PrepareMeasureChild(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // run MeasureChild
    layoutAlgorithm.MeasureChild(Referenced::RawPtr(relativeContainer));
    layoutAlgorithm.MeasureSelf(Referenced::RawPtr(relativeContainer));

    EXPECT_TRUE(layoutAlgorithm.isVerticalRelyOnContainer_);
    EXPECT_TRUE(layoutAlgorithm.isHorizontalRelyOnContainer_);

    EXPECT_EQ(relativeContainer->GetGeometryNode()->GetFrameSize(), SizeF(90.0f, 90.0f))
        << relativeContainer->GetGeometryNode()->GetFrameSize().ToString();
}

/**
 * @tc.name: MeasureSelfTest2
 * @tc.desc: Test relative container with auto height or auto width.
 */
HWTEST_F(RelativeContainerMeasureTest, MeasureSelfTest2, TestSize.Level1)
{
    // create three child nodes with alignRules
    RefPtr<FrameNode> row1, row2;
    auto relativeContainer = CreateRelativeContainer([this, &row1, &row2](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row1");
            ViewAbstract::SetWidth(CalcLength(50));
            ViewAbstract::SetHeight(CalcLength(50));
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row2");
            ViewAbstract::SetWidth(CalcLength(10));
            ViewAbstract::SetHeight(CalcLength(10));
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::LEFT, "row1", HorizontalAlign::END);
            AddAlignRule(alignRules, AlignDirection::TOP, "row1", VerticalAlign::TOP);
            ViewAbstract::SetAlignRules(alignRules);
        });
        ViewAbstract::SetWidth(CalcLength(0.0f, DimensionUnit::AUTO));
        ViewAbstract::SetHeight(CalcLength(0.0f, DimensionUnit::AUTO));
    });

    // constraint
    LayoutConstraintF constraint = {
        .percentReference = { 80, 80 }, // {width, height}
        .parentIdealSize = { 90, 90 },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    // used when creating child constraint
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    // prepare renderList_
    PrepareMeasureChild(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // run MeasureChild
    layoutAlgorithm.MeasureChild(Referenced::RawPtr(relativeContainer));
    layoutAlgorithm.MeasureSelf(Referenced::RawPtr(relativeContainer));

    EXPECT_FALSE(layoutAlgorithm.isVerticalRelyOnContainer_);
    EXPECT_FALSE(layoutAlgorithm.isHorizontalRelyOnContainer_);
    EXPECT_EQ(relativeContainer->GetGeometryNode()->GetFrameSize(), SizeF(60.0f, 50.0f))
        << relativeContainer->GetGeometryNode()->GetFrameSize().ToString();
}
} // namespace OHOS::Ace::NG