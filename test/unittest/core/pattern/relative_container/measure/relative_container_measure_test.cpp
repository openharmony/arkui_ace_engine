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

#include "../relative_container_base_test_ng.h"
using namespace std;

namespace OHOS::Ace::NG {

class RelativeContainerMeasureTest : public RelativeContainerBaseTestNG {
public:
    // help test reliedOnMap.
    // if find print reliedList, else ret "Doesn't exist".
    // output has lexicographic order
    static string TestReliedOnMap(unordered_map<string, set<string>>& reliedOnMap, string anchor)
    {
        string res;
        auto iter = reliedOnMap.find(anchor);
        if (iter != reliedOnMap.end()) {
            res += "[";
            auto& reliedList = reliedOnMap[anchor];
            for (auto it = reliedList.begin(); it != reliedList.end(); ++it) {
                res += *it;
                if (std::next(it) != reliedList.end()) {
                    res += ", ";
                }
            }
            res += "]";
        } else {
            res = "Doesn't exist";
        }
        return res;
    }

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

    static void PrepareMeasureChild(LayoutWrapper* layoutWrapper, RelativeContainerLayoutAlgorithm& layoutAlgorithm)
    {
        layoutAlgorithm.Initialize(layoutWrapper);
        // create idNodeMap_
        layoutAlgorithm.CollectNodesById(layoutWrapper);
        // create reliedOnMap_
        layoutAlgorithm.GetDependencyRelationship();
        // create incomingDegreeMap_
        layoutAlgorithm.PreTopologicalLoopDetection(layoutWrapper);
        // create renderList_
        layoutAlgorithm.TopologicalSort(layoutAlgorithm.renderList_);
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
    layoutAlgorithm.UpdateSizeWhenChildrenEmpty(relativeContainer.GetRawPtr());
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
    layoutAlgorithm.UpdateSizeWhenChildrenEmpty(relativeContainer.GetRawPtr());
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
    layoutAlgorithm.UpdateSizeWhenChildrenEmpty(relativeContainer.GetRawPtr());
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
    layoutAlgorithm.Initialize(relativeContainer.GetRawPtr());
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
    layoutAlgorithm.Initialize(relativeContainer.GetRawPtr());
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
    layoutAlgorithm.CollectNodesById(relativeContainer.GetRawPtr());

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
    layoutAlgorithm.CollectNodesById(relativeContainer.GetRawPtr());
    // run GetDependencyRelationship()
    layoutAlgorithm.GetDependencyRelationship();
    auto& reliedOnMap = layoutAlgorithm.reliedOnMap_;
    EXPECT_STREQ(TestReliedOnMap(reliedOnMap, "row1").c_str(), "[row2]");
    EXPECT_STREQ(TestReliedOnMap(reliedOnMap, "row2").c_str(), "[row3]");
    EXPECT_STREQ(TestReliedOnMap(reliedOnMap, "__container__").c_str(), "Doesn't exist");
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
    layoutAlgorithm.CollectNodesById(relativeContainer.GetRawPtr());
    // create reliedOnMap_
    layoutAlgorithm.GetDependencyRelationship();
    // run and test PreTopologicalLoopDetection
    // expect: !incomingDegreeMapCopy.empty() == true
    EXPECT_TRUE(!layoutAlgorithm.PreTopologicalLoopDetection(relativeContainer.GetRawPtr()));
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
    layoutAlgorithm.CollectNodesById(relativeContainer.GetRawPtr());
    // create reliedOnMap_
    layoutAlgorithm.GetDependencyRelationship();
    // run PreTopologicalLoopDetection, create incomingDegreeMap_
    // expect: incomingDegreeMapCopy.empty() == true
    EXPECT_TRUE(layoutAlgorithm.PreTopologicalLoopDetection(relativeContainer.GetRawPtr()));

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
    PrepareMeasureChild(relativeContainer.GetRawPtr(), layoutAlgorithm);

    // run MeasureChild
    layoutAlgorithm.MeasureChild(relativeContainer.GetRawPtr());
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

} // namespace OHOS::Ace::NG