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

#include "test/unittest/core/pattern/relative_container/relative_container_base_test_ng.h"
using namespace std;

namespace OHOS::Ace::NG {

class RelativeContainerLayoutTest : public RelativeContainerBaseTestNG {
public:
    static void PrepareLayout(LayoutWrapper* layoutWrapper, RelativeContainerLayoutAlgorithm& layoutAlgorithm)
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
        // create recordOffsetMap_
        layoutAlgorithm.MeasureChild(layoutWrapper);
    }
};

/**
 * @tc.desc: Test Layout
    dependence: recordOffsetMap_
    output: MarginFrameOffset of each childnode
 */
HWTEST_F(RelativeContainerLayoutTest, LayoutTest, TestSize.Level1)
{
    // create three child nodes with alignRules
    RefPtr<FrameNode> row1, row2, row3;
    auto relativeContainer = CreateRelativeContainer([this, &row1, &row2, &row3](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(100));
        ViewAbstract::SetBorderWidth(Dimension(3));
        ViewAbstract::SetPadding(CalcLength(1));
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

    // dependence: recordOffsetMap_
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);
    // test Layout
    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));
    // expect: row1.offset = (center, padding+border) = (100/2, 3+1) = (50, 4)
    EXPECT_EQ(row1->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(50, 4))
        << row1->GetGeometryNode()->GetMarginFrameOffset().ToString();
    // expect: row2.offset = (row1+30, padding+border) = (50+30, 4) = (80, 4)
    EXPECT_EQ(row2->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(80, 4))
        << row2->GetGeometryNode()->GetMarginFrameOffset().ToString();
    // expect: row3.offset = (row2+30, padding+border) = (80+30, 4) = (80, 4)
    EXPECT_EQ(row3->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(110, 4))
        << row3->GetGeometryNode()->GetMarginFrameOffset().ToString();
}
} // namespace OHOS::Ace::NG