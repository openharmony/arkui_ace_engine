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

class RelativeContainerBarrierTest : public RelativeContainerBaseTestNG {
public:
    static void AddBarrier(std::vector<BarrierInfo>& barrierInfos, const std::string& id,
        const BarrierDirection& direction, const std::vector<std::string>& referencedId)
    {
        BarrierInfo info = { .id = id, .direction = direction, .referencedId = referencedId };
        barrierInfos.emplace_back(info);
    };

    static string PrintReferencedId(std::unordered_map<std::string, BarrierParams>& barriers, const string& id)
    {
        if (!barriers.count(id)) {
            return "Doesn't exist";
        }
        const auto& referencedId = barriers[id].second;
        string res;
        res += "[";
        for (auto it = referencedId.begin(); it != referencedId.end(); ++it) {
            res += *it;
            if (std::next(it) != referencedId.end()) {
                res += ", ";
            }
        }
        res += "]";
        return res;
    }
};

/**
 * @tc.name: CalcBarrierTest1
 * @tc.desc: Test that barriers_ are created correctly
 */
HWTEST_F(RelativeContainerBarrierTest, CalcBarrierTest1, TestSize.Level0)
{
    auto relativeContainer = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        CreateRow([](RowModelNG model) { ViewAbstract::SetInspectorId("barrier3"); });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT, { "row1", "row2" });
        AddBarrier(barrierInfos, "barrier2", BarrierDirection::START, { "row3", "row4" });
        AddBarrier(barrierInfos, "barrier3", BarrierDirection::START, {});
        AddBarrier(barrierInfos, "barrier4", BarrierDirection::START, {});
        AddBarrier(barrierInfos, "", BarrierDirection::START, {});
        model.SetBarrier(barrierInfos);
        GuidelineInfo guideLineInfo = {
            .id = "barrier4", .direction = LineDirection::HORIZONTAL, .start = Dimension(30, DimensionUnit::PX)
        };
        model.SetGuideline(vector<GuidelineInfo> { guideLineInfo });
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    // To generate a guideLine, need to successfully set selfIdealSize.
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    // API > 11
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    // create idNodeMap_
    layoutAlgorithm.CollectNodesById(layoutWrapper);
    // create guidelines_
    layoutAlgorithm.CalcGuideline(layoutWrapper);
    // test CalcBarrier
    layoutAlgorithm.CalcBarrier(layoutWrapper);
    auto& barriers = layoutAlgorithm.barriers_;

    EXPECT_EQ(PrintReferencedId(barriers, "barrier1"), "[row1, row2]");
    EXPECT_EQ(PrintReferencedId(barriers, "barrier2"), "[row3, row4]");
    EXPECT_EQ(PrintReferencedId(barriers, "barrier3"), "Doesn't exist");
    EXPECT_EQ(PrintReferencedId(barriers, "barrier4"), "Doesn't exist");
    EXPECT_EQ(barriers.size(), 2);
}

/**
 * @tc.name: UpdateDegreeMapWithBarrierTest
 * @tc.desc: Test UpdateDegreeMapWithBarrierTest
 */
HWTEST_F(RelativeContainerBarrierTest, UpdateDegreeMapWithBarrierTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer([this, &row1](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        std::vector<GuidelineInfo> guideLineInfos;
        AddGuidelineStart(guideLineInfos, "guideline1", LineDirection::HORIZONTAL, Dimension(30, DimensionUnit::PX));
        model.SetGuideline(guideLineInfos);
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::LEFT, { "row1", "row2", "guideline1" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    // API > 11
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    layoutAlgorithm.CollectNodesById(layoutWrapper);
    layoutAlgorithm.CalcGuideline(layoutWrapper);
    layoutAlgorithm.CalcBarrier(layoutWrapper);
    layoutAlgorithm.GetDependencyRelationship();
    layoutAlgorithm.PreTopologicalLoopDetection(layoutWrapper);
    EXPECT_EQ(layoutAlgorithm.incomingDegreeMap_["barrier1"], 1);
}

/**
 * @tc.name: MeasureBarrierTest1
 * @tc.desc: Test MeasureBarrier
 */
HWTEST_F(RelativeContainerBarrierTest, MeasureBarrierTest1, TestSize.Level0)
{
    RefPtr<FrameNode> row1, row2, row3;
    auto relativeContainer = CreateRelativeContainer([this, &row1, &row2, &row3](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row2");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "row1", VerticalAlign::BOTTOM);
            AddAlignRule(alignRules, AlignDirection::MIDDLE, "row1", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
        row3 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row3");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::CENTER, "__container__", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::MIDDLE, "__container__", HorizontalAlign::START);
            ViewAbstract::SetAlignRules(alignRules);
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT, { "row1", "row2", "row3" });
        AddBarrier(barrierInfos, "barrier2", BarrierDirection::LEFT, { "row1", "row2", "row3" });
        AddBarrier(barrierInfos, "barrier3", BarrierDirection::TOP, { "row1", "row2", "row3" });
        AddBarrier(barrierInfos, "barrier4", BarrierDirection::BOTTOM, { "row1", "row2", "row3" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    // API > 11
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    // create idNodeMap_
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    // Test intermediate step: GetDependencyRelationshipInBarrier(), reliedOnMap_ is generated correctly.
    EXPECT_EQ(PrintReliedOnMap(layoutAlgorithm.reliedOnMap_, "row1"), "[barrier1, barrier2, barrier3, barrier4, row2]");
    EXPECT_EQ(PrintReliedOnMap(layoutAlgorithm.reliedOnMap_, "row2"), "[barrier1, barrier2, barrier3, barrier4]");
    EXPECT_EQ(PrintReliedOnMap(layoutAlgorithm.reliedOnMap_, "__container__"), "Doesn't exist");
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier1"], OffsetF(150, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier2"], OffsetF(-50, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier2"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier3"], OffsetF(0, -50))
        << layoutAlgorithm.recordOffsetMap_["barrier3"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier4"], OffsetF(0, 200))
        << layoutAlgorithm.recordOffsetMap_["barrier4"].ToString();
}

/**
 * @tc.name: MeasureBarrierTest2
 * @tc.desc: Test MeasureBarrier, barrier depends on guideLine.
 */
HWTEST_F(RelativeContainerBarrierTest, MeasureBarrierTest2, TestSize.Level0)
{
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer([this, &row1](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });

        std::vector<GuidelineInfo> guideLineInfos;
        AddGuidelineStart(guideLineInfos, "guideline1", LineDirection::HORIZONTAL, Dimension(-30, DimensionUnit::PX));
        AddGuidelineEnd(guideLineInfos, "guideline2", LineDirection::VERTICAL, Dimension(30, DimensionUnit::PX));
        model.SetGuideline(guideLineInfos);

        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT, { "row1", "guideline1", "guideline2" });
        AddBarrier(barrierInfos, "barrier2", BarrierDirection::LEFT, { "row1", "guideline1", "guideline2" });
        AddBarrier(barrierInfos, "barrier3", BarrierDirection::TOP, { "row1", "guideline1", "guideline2" });
        AddBarrier(barrierInfos, "barrier4", BarrierDirection::BOTTOM, { "row1", "guideline1", "guideline2" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    // API > 11
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    // create idNodeMap_
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier1"], OffsetF(270, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier2"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier2"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier3"], OffsetF(0, -30))
        << layoutAlgorithm.recordOffsetMap_["barrier3"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier4"], OffsetF(0, 100))
        << layoutAlgorithm.recordOffsetMap_["barrier4"].ToString();
}

/**
 * @tc.name: MeasureBarrierTest3
 * @tc.desc: Test MeasureBarrier, barrier A depends on barrier B.
 */
HWTEST_F(RelativeContainerBarrierTest, MeasureBarrierTest3, TestSize.Level0)
{
    RefPtr<FrameNode> row1, row2, row3;
    auto relativeContainer = CreateRelativeContainer([this, &row1, &row2, &row3](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row2");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "row1", VerticalAlign::BOTTOM);
            AddAlignRule(alignRules, AlignDirection::MIDDLE, "row1", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
        row3 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row3");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::CENTER, "__container__", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::MIDDLE, "__container__", HorizontalAlign::START);
            ViewAbstract::SetAlignRules(alignRules);
        });

        std::vector<GuidelineInfo> guideLineInfos;
        AddGuidelineStart(guideLineInfos, "guideline1", LineDirection::HORIZONTAL, Dimension(-30, DimensionUnit::PX));
        AddGuidelineEnd(guideLineInfos, "guideline2", LineDirection::VERTICAL, Dimension(30, DimensionUnit::PX));
        model.SetGuideline(guideLineInfos);

        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT, { "row1", "row2" });
        AddBarrier(barrierInfos, "barrier2", BarrierDirection::LEFT, { "row1", "row2" });
        AddBarrier(barrierInfos, "barrier3", BarrierDirection::TOP, { "row1", "row2" });
        AddBarrier(barrierInfos, "barrier4", BarrierDirection::BOTTOM, { "row1", "row2" });

        AddBarrier(barrierInfos, "barrier5", BarrierDirection::RIGHT,
            { "barrier1", "barrier2", "barrier3", "barrier4", "row3" });
        AddBarrier(barrierInfos, "barrier6", BarrierDirection::LEFT,
            { "barrier1", "barrier2", "barrier3", "barrier4", "row3" });
        AddBarrier(barrierInfos, "barrier7", BarrierDirection::TOP,
            { "barrier1", "barrier2", "barrier3", "barrier4", "row3" });
        AddBarrier(barrierInfos, "barrier8", BarrierDirection::BOTTOM,
            { "barrier1", "barrier2", "barrier3", "barrier4", "row3" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    // API > 11
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    // create idNodeMap_
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier5"], OffsetF(150, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier5"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier6"], OffsetF(-50, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier6"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier7"], OffsetF(0, -50))
        << layoutAlgorithm.recordOffsetMap_["barrier7"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier8"], OffsetF(0, 200))
        << layoutAlgorithm.recordOffsetMap_["barrier8"].ToString();
}

/**
 * @tc.name: CalcBarrierTest2
 * @tc.desc: Test CalcBarrier with empty referencedId list
 */
HWTEST_F(RelativeContainerBarrierTest, CalcBarrierTest2, TestSize.Level0)
{
    auto relativeContainer = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_empty", BarrierDirection::RIGHT, {});
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    layoutAlgorithm.CollectNodesById(layoutWrapper);
    layoutAlgorithm.CalcBarrier(layoutWrapper);
    auto& barriers = layoutAlgorithm.barriers_;

    EXPECT_EQ(PrintReferencedId(barriers, "barrier_empty"), "[]");
}

/**
 * @tc.name: CalcBarrierTest3
 * @tc.desc: Test CalcBarrier with non-existent referenced nodes
 */
HWTEST_F(RelativeContainerBarrierTest, CalcBarrierTest3, TestSize.Level0)
{
    auto relativeContainer = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT,
            { "non_existent_node1", "non_existent_node2" });
        AddBarrier(barrierInfos, "barrier2", BarrierDirection::LEFT, { "row1", "ghost_node" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    layoutAlgorithm.CollectNodesById(layoutWrapper);
    layoutAlgorithm.CalcBarrier(layoutWrapper);
    auto& barriers = layoutAlgorithm.barriers_;

    EXPECT_EQ(barriers.size(), 2);
    EXPECT_EQ(PrintReferencedId(barriers, "barrier1"),
        "[non_existent_node1, non_existent_node2]");
    EXPECT_EQ(PrintReferencedId(barriers, "barrier2"), "[row1, ghost_node]");
}

/**
 * @tc.name: CalcBarrierTest4
 * @tc.desc: Test CalcBarrier filters out duplicate barrier IDs
 */
HWTEST_F(RelativeContainerBarrierTest, CalcBarrierTest4, TestSize.Level0)
{
    auto relativeContainer = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT, { "row1" });
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::LEFT, { "row1" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    layoutAlgorithm.CollectNodesById(layoutWrapper);
    layoutAlgorithm.CalcBarrier(layoutWrapper);
    auto& barriers = layoutAlgorithm.barriers_;

    EXPECT_EQ(barriers.size(), 1);
}

/**
 * @tc.name: MeasureBarrierTest4
 * @tc.desc: Test MeasureBarrier with GONE visibility nodes
 */
HWTEST_F(RelativeContainerBarrierTest, MeasureBarrierTest4, TestSize.Level0)
{
    std::array<RefPtr<FrameNode>, 3> rows;
    auto relativeContainer = CreateRelativeContainer([this, &rows](RelativeContainerModelNG model) {
        rows[0] = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        rows[1] = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(150.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row2");
            ViewAbstract::SetVisibility(VisibleType::GONE);
        });
        rows[2] = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(120.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(90.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row3");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT, { "row1", "row2", "row3" });
        AddBarrier(barrierInfos, "barrier2", BarrierDirection::BOTTOM, { "row1", "row2", "row3" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier1"], OffsetF(120, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier2"], OffsetF(0, 100))
        << layoutAlgorithm.recordOffsetMap_["barrier2"].ToString();
}

/**
 * @tc.name: MeasureBarrierTest5
 * @tc.desc: Test MeasureBarrier with START and END directions
 */
HWTEST_F(RelativeContainerBarrierTest, MeasureBarrierTest5, TestSize.Level0)
{
    RefPtr<FrameNode> row1, row2;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1, &row2](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row2");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_start", BarrierDirection::START, { "row1" });
        AddBarrier(barrierInfos, "barrier_end", BarrierDirection::END, { "row2" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_start"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_start"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_end"], OffsetF(80, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_end"].ToString();
}

/**
 * @tc.name: MeasureBarrierTest6
 * @tc.desc: Test MeasureBarrier with single node reference
 */
HWTEST_F(RelativeContainerBarrierTest, MeasureBarrierTest6, TestSize.Level0)
{
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_r", BarrierDirection::RIGHT, { "row1" });
        AddBarrier(barrierInfos, "barrier_l", BarrierDirection::LEFT, { "row1" });
        AddBarrier(barrierInfos, "barrier_t", BarrierDirection::TOP, { "row1" });
        AddBarrier(barrierInfos, "barrier_b", BarrierDirection::BOTTOM, { "row1" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_r"], OffsetF(100, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_r"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_l"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_l"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_t"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_t"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_b"], OffsetF(0, 100))
        << layoutAlgorithm.recordOffsetMap_["barrier_b"].ToString();
}

/**
 * @tc.name: MeasureBarrierTest7
 * @tc.desc: Test MeasureBarrier with offset nodes
 */
HWTEST_F(RelativeContainerBarrierTest, MeasureBarrierTest7, TestSize.Level0)
{
    std::array<RefPtr<FrameNode>, 3> rows;
    auto relativeContainer = CreateRelativeContainer([this, &rows](RelativeContainerModelNG model) {
        rows[0] = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        rows[1] = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row2");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "row1", VerticalAlign::BOTTOM);
            AddAlignRule(alignRules, AlignDirection::LEFT, "row1", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
        rows[2] = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(60.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(60.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row3");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "row2", VerticalAlign::BOTTOM);
            AddAlignRule(alignRules, AlignDirection::LEFT, "row2", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::BOTTOM, { "row1", "row2", "row3" });
        AddBarrier(barrierInfos, "barrier2", BarrierDirection::RIGHT, { "row1", "row2", "row3" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier1"], OffsetF(0, 240))
        << layoutAlgorithm.recordOffsetMap_["barrier1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier2"], OffsetF(240, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier2"].ToString();
}

/**
 * @tc.name: MeasureBarrierTest8
 * @tc.desc: Test barrier with circular dependency detection
 */
HWTEST_F(RelativeContainerBarrierTest, MeasureBarrierTest8, TestSize.Level0)
{
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_a", BarrierDirection::RIGHT, { "row1" });
        AddBarrier(barrierInfos, "barrier_b", BarrierDirection::RIGHT, { "barrier_a" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_a"], OffsetF(100, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_a"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_b"], OffsetF(100, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_b"].ToString();
}

/**
 * @tc.name: MeasureBarrierTest9
 * @tc.desc: Test barrier with three levels of nesting
 */
HWTEST_F(RelativeContainerBarrierTest, MeasureBarrierTest9, TestSize.Level0)
{
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT, { "row1" });
        AddBarrier(barrierInfos, "barrier2", BarrierDirection::BOTTOM,
            { "barrier1" });
        AddBarrier(barrierInfos, "barrier3", BarrierDirection::RIGHT,
            { "barrier1", "barrier2" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier1"], OffsetF(100, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier2"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier2"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier3"], OffsetF(100, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier3"].ToString();
}

/**
 * @tc.name: MeasureBarrierTest10
 * @tc.desc: Test barrier with all four directions on same nodes
 */
HWTEST_F(RelativeContainerBarrierTest, MeasureBarrierTest10, TestSize.Level0)
{
    RefPtr<FrameNode> row1, row2;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1, &row2](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(50.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row2");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::LEFT, "row1", HorizontalAlign::END);
            AddAlignRule(alignRules, AlignDirection::TOP, "row1", VerticalAlign::BOTTOM);
            ViewAbstract::SetAlignRules(alignRules);
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_left", BarrierDirection::LEFT,
            { "row1", "row2" });
        AddBarrier(barrierInfos, "barrier_right", BarrierDirection::RIGHT,
            { "row1", "row2" });
        AddBarrier(barrierInfos, "barrier_top", BarrierDirection::TOP,
            { "row1", "row2" });
        AddBarrier(barrierInfos, "barrier_bottom", BarrierDirection::BOTTOM,
            { "row1", "row2" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_left"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_left"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_right"], OffsetF(130, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_right"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_top"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_top"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_bottom"], OffsetF(0, 130))
        << layoutAlgorithm.recordOffsetMap_["barrier_bottom"].ToString();
}

/**
 * @tc.name: BarrierDependencyTest1
 * @tc.desc: Test barrier reliedOnMap is built correctly
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierDependencyTest1, TestSize.Level0)
{
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT,
            { "row1" });
        AddBarrier(barrierInfos, "barrier2", BarrierDirection::LEFT,
            { "row1", "barrier1" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    layoutAlgorithm.CollectNodesById(layoutWrapper);
    layoutAlgorithm.CalcBarrier(layoutWrapper);
    layoutAlgorithm.GetDependencyRelationship();

    EXPECT_EQ(PrintReliedOnMap(layoutAlgorithm.reliedOnMap_, "row1"),
        "[barrier1, barrier2]");
    EXPECT_EQ(PrintReliedOnMap(layoutAlgorithm.reliedOnMap_, "barrier1"),
        "[barrier2]");
    EXPECT_EQ(PrintReliedOnMap(layoutAlgorithm.reliedOnMap_, "barrier2"),
        "Doesn't exist");
}

/**
 * @tc.name: BarrierWithContainerTest
 * @tc.desc: Test barrier with container references
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierWithContainerTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::MIDDLE, "__container__",
                HorizontalAlign::CENTER);
            AddAlignRule(alignRules, AlignDirection::CENTER, "__container__",
                VerticalAlign::CENTER);
            ViewAbstract::SetAlignRules(alignRules);
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT,
            { "row1" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    auto row1Offset = layoutAlgorithm.recordOffsetMap_["row1"];
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier1"],
        OffsetF(row1Offset.GetX() + 100, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier1"].ToString();
}

/**
 * @tc.name: BarrierMultipleGuidelinesTest
 * @tc.desc: Test barrier with multiple guideline references
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierMultipleGuidelinesTest, TestSize.Level0)
{
    auto relativeContainer = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        std::vector<GuidelineInfo> guideLineInfos;
        AddGuidelineStart(guideLineInfos, "guide_h1", LineDirection::HORIZONTAL,
            Dimension(50, DimensionUnit::PX));
        AddGuidelineStart(guideLineInfos, "guide_h2", LineDirection::HORIZONTAL,
            Dimension(100, DimensionUnit::PX));
        AddGuidelineStart(guideLineInfos, "guide_v1", LineDirection::VERTICAL,
            Dimension(80, DimensionUnit::PX));
        AddGuidelineEnd(guideLineInfos, "guide_v2", LineDirection::VERTICAL,
            Dimension(120, DimensionUnit::PX));
        model.SetGuideline(guideLineInfos);

        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_h", BarrierDirection::BOTTOM,
            { "guide_h1", "guide_h2" });
        AddBarrier(barrierInfos, "barrier_v", BarrierDirection::RIGHT,
            { "guide_v1", "guide_v2" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_h"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_h"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_v"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_v"].ToString();
}

/**
 * @tc.name: BarrierDegreeMapTest
 * @tc.desc: Test UpdateDegreeMapWithBarrier updates degrees correctly
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierDegreeMapTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1, row2;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1, &row2](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row2");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "row1", VerticalAlign::BOTTOM);
            ViewAbstract::SetAlignRules(alignRules);
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT,
            { "row1", "row2" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    layoutAlgorithm.CollectNodesById(layoutWrapper);
    layoutAlgorithm.CalcBarrier(layoutWrapper);
    layoutAlgorithm.GetDependencyRelationship();
    layoutAlgorithm.PreTopologicalLoopDetection(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.incomingDegreeMap_["barrier1"], 2);
}

/**
 * @tc.name: BarrierWithComplexOffsetsTest
 * @tc.desc: Test barrier with nodes having complex offsets
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierWithComplexOffsetsTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1, row2, row3, row4;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1, &row2, &row3, &row4](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(60.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(60.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(70.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(70.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row2");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::LEFT, "row1", HorizontalAlign::END);
            AddAlignRule(alignRules, AlignDirection::TOP, "row1", VerticalAlign::BOTTOM);
            ViewAbstract::SetAlignRules(alignRules);
        });
        row3 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(50.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row3");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::LEFT, "row2", HorizontalAlign::END);
            AddAlignRule(alignRules, AlignDirection::TOP, "row2", VerticalAlign::BOTTOM);
            ViewAbstract::SetAlignRules(alignRules);
        });
        row4 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row4");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::LEFT, "row3", HorizontalAlign::END);
            AddAlignRule(alignRules, AlignDirection::TOP, "row3", VerticalAlign::BOTTOM);
            ViewAbstract::SetAlignRules(alignRules);
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_all", BarrierDirection::BOTTOM,
            { "row1", "row2", "row3", "row4" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_all"], OffsetF(0, 260))
        << layoutAlgorithm.recordOffsetMap_["barrier_all"].ToString();
}

/**
 * @tc.name: BarrierWithNegativeGuidelineTest
 * @tc.desc: Test barrier with negative guideline offset
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierWithNegativeGuidelineTest, TestSize.Level0)
{
    auto relativeContainer = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        std::vector<GuidelineInfo> guideLineInfos;
        AddGuidelineStart(guideLineInfos, "guide_neg", LineDirection::HORIZONTAL,
            Dimension(-50, DimensionUnit::PX));
        AddGuidelineStart(guideLineInfos, "guide_pos", LineDirection::HORIZONTAL,
            Dimension(100, DimensionUnit::PX));
        model.SetGuideline(guideLineInfos);

        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_top", BarrierDirection::TOP,
            { "guide_neg", "guide_pos" });
        AddBarrier(barrierInfos, "barrier_bottom", BarrierDirection::BOTTOM,
            { "guide_neg", "guide_pos" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_top"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_top"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_bottom"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_bottom"].ToString();
}

/**
 * @tc.name: BarrierEmptyReferenceListTest
 * @tc.desc: Test barrier behavior with empty reference list
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierEmptyReferenceListTest, TestSize.Level0)
{
    auto relativeContainer = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_empty_right", BarrierDirection::RIGHT, {});
        AddBarrier(barrierInfos, "barrier_empty_left", BarrierDirection::LEFT, {});
        AddBarrier(barrierInfos, "barrier_empty_top", BarrierDirection::TOP, {});
        AddBarrier(barrierInfos, "barrier_empty_bottom", BarrierDirection::BOTTOM, {});
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_empty_right"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_empty_right"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_empty_left"],
        OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_empty_left"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_empty_top"],
        OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_empty_top"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_empty_bottom"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_empty_bottom"].ToString();
}

/**
 * @tc.name: BarrierDuplicateReferencesTest
 * @tc.desc: Test barrier with duplicate references in list
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierDuplicateReferencesTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_dup", BarrierDirection::RIGHT,
            { "row1", "row1", "row1" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_dup"], OffsetF(100, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_dup"].ToString();
}

/**
 * @tc.name: BarrierWidthVariationTest
 * @tc.desc: Test barrier with nodes of varying widths
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierWidthVariationTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1, row2, row3;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1, &row2, &row3](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(20.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(150.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row2");
        });
        row3 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row3");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_max", BarrierDirection::RIGHT,
            { "row1", "row2", "row3" });
        AddBarrier(barrierInfos, "barrier_min", BarrierDirection::LEFT,
            { "row1", "row2", "row3" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_max"], OffsetF(150, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_max"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_min"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_min"].ToString();
}

/**
 * @tc.name: BarrierHeightVariationTest
 * @tc.desc: Test barrier with nodes of varying heights
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierHeightVariationTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1, row2, row3;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1, &row2, &row3](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(50.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(30.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(50.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(120.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row2");
        });
        row3 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(50.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(70.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row3");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_max", BarrierDirection::BOTTOM,
            { "row1", "row2", "row3" });
        AddBarrier(barrierInfos, "barrier_min", BarrierDirection::TOP,
            { "row1", "row2", "row3" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_max"], OffsetF(0, 120))
        << layoutAlgorithm.recordOffsetMap_["barrier_max"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_min"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_min"].ToString();
}

/**
 * @tc.name: BarrierGuidelineComboTest
 * @tc.desc: Test barrier with mixed node and guideline references
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierGuidelineComboTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        std::vector<GuidelineInfo> guideLineInfos;
        AddGuidelineStart(guideLineInfos, "guide_h", LineDirection::HORIZONTAL,
            Dimension(60, DimensionUnit::PX));
        AddGuidelineStart(guideLineInfos, "guide_v", LineDirection::VERTICAL,
            Dimension(150, DimensionUnit::PX));
        model.SetGuideline(guideLineInfos);

        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT,
            { "row1", "guide_v" });
        AddBarrier(barrierInfos, "barrier2", BarrierDirection::BOTTOM,
            { "row1", "guide_h" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier1"], OffsetF(150, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier2"], OffsetF(0, 100))
        << layoutAlgorithm.recordOffsetMap_["barrier2"].ToString();
}

/**
 * @tc.name: BarrierFourLevelNestingTest
 * @tc.desc: Test barrier with four levels of barrier nesting
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierFourLevelNestingTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(50.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT, { "row1" });
        AddBarrier(barrierInfos, "barrier2", BarrierDirection::RIGHT,
            { "barrier1" });
        AddBarrier(barrierInfos, "barrier3", BarrierDirection::RIGHT,
            { "barrier2" });
        AddBarrier(barrierInfos, "barrier4", BarrierDirection::RIGHT,
            { "barrier3" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier1"], OffsetF(50, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier2"], OffsetF(50, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier2"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier3"], OffsetF(50, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier3"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier4"], OffsetF(50, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier4"].ToString();
}

/**
 * @tc.name: BarrierAllGoneNodesTest
 * @tc.desc: Test barrier when all referenced nodes are GONE
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierAllGoneNodesTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1, row2;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1, &row2](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
            ViewAbstract::SetVisibility(VisibleType::GONE);
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row2");
            ViewAbstract::SetVisibility(VisibleType::GONE);
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT,
            { "row1", "row2" });
        AddBarrier(barrierInfos, "barrier2", BarrierDirection::BOTTOM,
            { "row1", "row2" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier1"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier2"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier2"].ToString();
}

/**
 * @tc.name: BarrierWithEndGuidelineTest
 * @tc.desc: Test barrier with end-positioned guideline
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierWithEndGuidelineTest, TestSize.Level0)
{
    auto relativeContainer = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        std::vector<GuidelineInfo> guideLineInfos;
        AddGuidelineEnd(guideLineInfos, "guide_end_h", LineDirection::HORIZONTAL,
            Dimension(100, DimensionUnit::PX));
        AddGuidelineEnd(guideLineInfos, "guide_end_v", LineDirection::VERTICAL,
            Dimension(150, DimensionUnit::PX));
        model.SetGuideline(guideLineInfos);

        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_top", BarrierDirection::TOP,
            { "guide_end_h" });
        AddBarrier(barrierInfos, "barrier_bottom", BarrierDirection::BOTTOM,
            { "guide_end_h" });
        AddBarrier(barrierInfos, "barrier_left", BarrierDirection::LEFT,
            { "guide_end_v" });
        AddBarrier(barrierInfos, "barrier_right", BarrierDirection::RIGHT,
            { "guide_end_v" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_top"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_top"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_bottom"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_bottom"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_left"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_left"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_right"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_right"].ToString();
}

/**
 * @tc.name: BarrierWithPercentGuidelineTest
 * @tc.desc: Test barrier with percentage-based guideline
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierWithPercentGuidelineTest, TestSize.Level0)
{
    auto relativeContainer = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        std::vector<GuidelineInfo> guideLineInfos;
        AddGuidelineStart(guideLineInfos, "guide_percent", LineDirection::HORIZONTAL,
            Dimension(0.5f, DimensionUnit::PERCENT));
        AddGuidelineStart(guideLineInfos, "guide_v_percent", LineDirection::VERTICAL,
            Dimension(0.3f, DimensionUnit::PERCENT));
        model.SetGuideline(guideLineInfos);

        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_h", BarrierDirection::BOTTOM,
            { "guide_percent" });
        AddBarrier(barrierInfos, "barrier_v", BarrierDirection::RIGHT,
            { "guide_v_percent" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_h"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_h"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_v"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_v"].ToString();
}

/**
 * @tc.name: BarrierCrossDependencyTest
 * @tc.desc: Test barriers with cross-direction dependencies
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierCrossDependencyTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_h", BarrierDirection::BOTTOM, { "row1" });
        AddBarrier(barrierInfos, "barrier_v", BarrierDirection::RIGHT,
            { "row1", "barrier_h" });
        AddBarrier(barrierInfos, "barrier_final", BarrierDirection::BOTTOM,
            { "barrier_v" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_h"], OffsetF(0, 100))
        << layoutAlgorithm.recordOffsetMap_["barrier_h"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_v"], OffsetF(100, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_v"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_final"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_final"].ToString();
}

/**
 * @tc.name: BarrierDependencyWithAlignRulesTest
 * @tc.desc: Test barrier dependency with nodes using align rules
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierDependencyWithAlignRulesTest,
    TestSize.Level0)
{
    RefPtr<FrameNode> row1, row2;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1, &row2](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(60.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(60.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row2");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::MIDDLE, "row1",
                HorizontalAlign::CENTER);
            AddAlignRule(alignRules, AlignDirection::CENTER, "row1",
                VerticalAlign::CENTER);
            ViewAbstract::SetAlignRules(alignRules);
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT,
            { "row1", "row2" });
        AddBarrier(barrierInfos, "barrier2", BarrierDirection::BOTTOM,
            { "row1", "row2" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier1"], OffsetF(80, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier2"], OffsetF(0, 80))
        << layoutAlgorithm.recordOffsetMap_["barrier2"].ToString();
}

/**
 * @tc.name: BarrierZeroSizeNodesTest
 * @tc.desc: Test barrier with zero-size nodes
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierZeroSizeNodesTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1, row2;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1, &row2](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(0.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(0.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row2");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT,
            { "row1", "row2" });
        AddBarrier(barrierInfos, "barrier2", BarrierDirection::BOTTOM,
            { "row1", "row2" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier1"], OffsetF(100, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier2"], OffsetF(0, 100))
        << layoutAlgorithm.recordOffsetMap_["barrier2"].ToString();
}

/**
 * @tc.name: BarrierNodeAndBarrierRefTest
 * @tc.desc: Test barrier referencing both nodes and barriers
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierNodeAndBarrierRefTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1, row2;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1, &row2](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(60.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(60.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row2");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::LEFT, "row1",
                HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_a", BarrierDirection::RIGHT,
            { "row1", "row2" });
        AddBarrier(barrierInfos, "barrier_b", BarrierDirection::BOTTOM,
            { "barrier_a", "row1" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_a"], OffsetF(140, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_a"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_b"], OffsetF(0, 60))
        << layoutAlgorithm.recordOffsetMap_["barrier_b"].ToString();
}

/**
 * @tc.name: BarrierLargeContainerTest
 * @tc.desc: Test barrier in large container
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierLargeContainerTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(200.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(150.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier1", BarrierDirection::RIGHT, { "row1" });
        AddBarrier(barrierInfos, "barrier2", BarrierDirection::BOTTOM, { "row1" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(1000.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(800.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier1"], OffsetF(200, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier2"], OffsetF(0, 150))
        << layoutAlgorithm.recordOffsetMap_["barrier2"].ToString();
}

/**
 * @tc.name: BarrierStartEndDirectionTest
 * @tc.desc: Test barrier with START and END directions
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierStartEndDirectionTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1, row2;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1, &row2](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row2");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::LEFT, "row1",
                HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_start", BarrierDirection::START,
            { "row1", "row2" });
        AddBarrier(barrierInfos, "barrier_end", BarrierDirection::END,
            { "row1", "row2" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_start"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_start"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_end"], OffsetF(180, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_end"].ToString();
}

/**
 * @tc.name: BarrierMultipleSameDirectionTest
 * @tc.desc: Test multiple barriers with same direction
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierMultipleSameDirectionTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1, row2, row3;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1, &row2, &row3](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(60.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(60.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(80.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row2");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::LEFT, "row1",
                HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
        row3 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(70.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(70.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row3");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::LEFT, "row2",
                HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_r1", BarrierDirection::RIGHT, { "row1" });
        AddBarrier(barrierInfos, "barrier_r2", BarrierDirection::RIGHT, { "row2" });
        AddBarrier(barrierInfos, "barrier_r3", BarrierDirection::RIGHT, { "row3" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_r1"], OffsetF(60, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_r1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_r2"], OffsetF(140, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_r2"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_r3"], OffsetF(210, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_r3"].ToString();
}

/**
 * @tc.name: BarrierLayoutAfterNodeUpdateTest
 * @tc.desc: Test barrier layout after node position update
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierLayoutAfterNodeUpdateTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::MIDDLE, "__container__",
                HorizontalAlign::CENTER);
            AddAlignRule(alignRules, AlignDirection::CENTER, "__container__",
                VerticalAlign::CENTER);
            ViewAbstract::SetAlignRules(alignRules);
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_left", BarrierDirection::LEFT, { "row1" });
        AddBarrier(barrierInfos, "barrier_right", BarrierDirection::RIGHT,
            { "row1" });
        AddBarrier(barrierInfos, "barrier_top", BarrierDirection::TOP, { "row1" });
        AddBarrier(barrierInfos, "barrier_bottom", BarrierDirection::BOTTOM,
            { "row1" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    auto row1Offset = layoutAlgorithm.recordOffsetMap_["row1"];
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_left"],
        OffsetF(row1Offset.GetX(), 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_left"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_right"],
        OffsetF(row1Offset.GetX() + 100, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_right"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_top"],
        OffsetF(0, row1Offset.GetY()))
        << layoutAlgorithm.recordOffsetMap_["barrier_top"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_bottom"],
        OffsetF(0, row1Offset.GetY() + 100))
        << layoutAlgorithm.recordOffsetMap_["barrier_bottom"].ToString();
}

/**
 * @tc.name: BarrierWithRTLTest
 * @tc.desc: Test barrier behavior in RTL layout
 */
HWTEST_F(RelativeContainerBarrierTest, BarrierWithRTLTest, TestSize.Level0)
{
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer(
        [this, &row1](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetInspectorId("row1");
        });
        std::vector<BarrierInfo> barrierInfos;
        AddBarrier(barrierInfos, "barrier_start", BarrierDirection::START, { "row1" });
        AddBarrier(barrierInfos, "barrier_end", BarrierDirection::END, { "row1" });
        model.SetBarrier(barrierInfos);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
    });

    auto layoutProperty = relativeContainer->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(LayoutConstraintF {});
    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    layoutProperty->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    auto layoutWrapper = Referenced::RawPtr(relativeContainer);
    PrepareMeasureChild(layoutWrapper, layoutAlgorithm);
    layoutAlgorithm.MeasureChild(layoutWrapper);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_start"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_start"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["barrier_end"], OffsetF(100, 0))
        << layoutAlgorithm.recordOffsetMap_["barrier_end"].ToString();
}

} // namespace OHOS::Ace::NG
