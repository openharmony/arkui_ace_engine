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
HWTEST_F(RelativeContainerBarrierTest, CalcBarrierTest1, TestSize.Level1)
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
HWTEST_F(RelativeContainerBarrierTest, UpdateDegreeMapWithBarrierTest, TestSize.Level1)
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
HWTEST_F(RelativeContainerBarrierTest, MeasureBarrierTest1, TestSize.Level1)
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
HWTEST_F(RelativeContainerBarrierTest, MeasureBarrierTest2, TestSize.Level1)
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
HWTEST_F(RelativeContainerBarrierTest, MeasureBarrierTest3, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
