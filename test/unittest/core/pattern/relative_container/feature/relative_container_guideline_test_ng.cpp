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

class RelativeContainerGuidelineTest : public RelativeContainerBaseTestNG {};

/**
 * @tc.name: CalcGuidelineTest1
 * @tc.desc: Test func CalcGuideline, calculate the position of multiple guidelines based on the size of the container
 * and record them in guidelines_ and recordOffsetMap_.
 */
HWTEST_F(RelativeContainerGuidelineTest, CalcGuidelineTest1, TestSize.Level1)
{
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
        std::vector<GuidelineInfo> infos;
        AddGuidelineStart(infos, "guideline1", LineDirection::HORIZONTAL, Dimension(30, DimensionUnit::PX));
        AddGuidelineStart(infos, "guideline2", LineDirection::VERTICAL, Dimension(40, DimensionUnit::PX));
        AddGuidelineEnd(infos, "guideline3", LineDirection::HORIZONTAL, Dimension(30, DimensionUnit::PX));
        AddGuidelineEnd(infos, "guideline4", LineDirection::VERTICAL, Dimension(40, DimensionUnit::PX));
        model.SetGuideline(infos);
    });

    // To generate a guideLine, need to successfully set selfIdealSize.
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    // API > 11
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    layoutAlgorithm.CalcGuideline(Referenced::RawPtr(relativeContainer));
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline1"].first, LineDirection::HORIZONTAL);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline1"].second, 30);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline2"].first, LineDirection::VERTICAL);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline2"].second, 40);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline3"].first, LineDirection::HORIZONTAL);
    // 400 - 30 = 370
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline3"].second, 370);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline4"].first, LineDirection::VERTICAL);
    // 300 - 40 = 260
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline4"].second, 260);
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["guideline1"], OffsetF(0, 30))
        << layoutAlgorithm.recordOffsetMap_["guideline1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["guideline2"], OffsetF(40, 0))
        << layoutAlgorithm.recordOffsetMap_["guideline2"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["guideline3"], OffsetF(0, 370))
        << layoutAlgorithm.recordOffsetMap_["guideline3"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["guideline4"], OffsetF(260, 0))
        << layoutAlgorithm.recordOffsetMap_["guideline4"].ToString();
}

/**
 * @tc.name: CalcGuidelineTest2
 * @tc.desc: test the case where guidelines are expressed in percentage form use and the container width and height are
 * auto.
 */
HWTEST_F(RelativeContainerGuidelineTest, CalcGuidelineTest2, TestSize.Level1)
{
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(0.0f, DimensionUnit::AUTO));
        ViewAbstract::SetHeight(CalcLength(0.0f, DimensionUnit::AUTO));
        std::vector<GuidelineInfo> infos;
        AddGuidelineStart(infos, "guideline1", LineDirection::HORIZONTAL, Dimension(0.1, DimensionUnit::PERCENT));
        AddGuidelineStart(infos, "guideline2", LineDirection::VERTICAL, Dimension(0.1, DimensionUnit::PERCENT));
        AddGuidelineEnd(infos, "guideline3", LineDirection::HORIZONTAL, Dimension(0.1, DimensionUnit::PERCENT));
        AddGuidelineEnd(infos, "guideline4", LineDirection::VERTICAL, Dimension(0.1, DimensionUnit::PERCENT));
        AddGuidelineStart(infos, "guideline5", LineDirection::HORIZONTAL, Dimension(30, DimensionUnit::PX));
        AddGuidelineStart(infos, "guideline6", LineDirection::VERTICAL, Dimension(40, DimensionUnit::PX));
        AddGuidelineEnd(infos, "guideline7", LineDirection::HORIZONTAL, Dimension(30, DimensionUnit::PX));
        AddGuidelineEnd(infos, "guideline8", LineDirection::VERTICAL, Dimension(40, DimensionUnit::PX));
        model.SetGuideline(infos);
    });

    // update selfIdealSize
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    layoutAlgorithm.CalcGuideline(Referenced::RawPtr(relativeContainer));
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline1"].first, LineDirection::HORIZONTAL);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline1"].second, 0);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline2"].first, LineDirection::VERTICAL);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline2"].second, 0);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline3"].first, LineDirection::HORIZONTAL);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline3"].second, 0);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline4"].first, LineDirection::VERTICAL);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline4"].second, 0);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline5"].first, LineDirection::HORIZONTAL);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline5"].second, 30);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline6"].first, LineDirection::VERTICAL);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline6"].second, 40);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline7"].first, LineDirection::HORIZONTAL);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline7"].second, 0);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline8"].first, LineDirection::VERTICAL);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline8"].second, 0);

    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["guideline1"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["guideline1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["guideline2"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["guideline2"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["guideline3"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["guideline3"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["guideline4"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["guideline4"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["guideline5"], OffsetF(0, 30))
        << layoutAlgorithm.recordOffsetMap_["guideline5"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["guideline6"], OffsetF(40, 0))
        << layoutAlgorithm.recordOffsetMap_["guideline6"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["guideline7"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["guideline7"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["guideline8"], OffsetF(0, 0))
        << layoutAlgorithm.recordOffsetMap_["guideline8"].ToString();
}

/**
 * @tc.name: CalcGuidelineTest3
 * @tc.desc: test the case where guidelines are expressed in percentage form use and the container width and height are
 * not auto.
 */
HWTEST_F(RelativeContainerGuidelineTest, CalcGuidelineTest3, TestSize.Level1)
{
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
        std::vector<GuidelineInfo> infos;
        AddGuidelineStart(infos, "guideline1", LineDirection::HORIZONTAL, Dimension(0.1, DimensionUnit::PERCENT));
        AddGuidelineStart(infos, "guideline2", LineDirection::VERTICAL, Dimension(0.1, DimensionUnit::PERCENT));
        AddGuidelineEnd(infos, "guideline3", LineDirection::HORIZONTAL, Dimension(0.1, DimensionUnit::PERCENT));
        AddGuidelineEnd(infos, "guideline4", LineDirection::VERTICAL, Dimension(0.1, DimensionUnit::PERCENT));
        model.SetGuideline(infos);
    });

    // update selfIdealSize
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    layoutAlgorithm.CalcGuideline(Referenced::RawPtr(relativeContainer));
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline1"].first, LineDirection::HORIZONTAL);
    // 400 * 0.1
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline1"].second, 40);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline2"].first, LineDirection::VERTICAL);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline2"].second, 30);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline3"].first, LineDirection::HORIZONTAL);
    // 400 - 40
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline3"].second, 360);
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline4"].first, LineDirection::VERTICAL);
    // 300 - 30
    EXPECT_EQ(layoutAlgorithm.guidelines_["guideline4"].second, 270);
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["guideline1"], OffsetF(0, 40))
        << layoutAlgorithm.recordOffsetMap_["guideline1"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["guideline2"], OffsetF(30, 0))
        << layoutAlgorithm.recordOffsetMap_["guideline2"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["guideline3"], OffsetF(0, 360))
        << layoutAlgorithm.recordOffsetMap_["guideline3"].ToString();
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["guideline4"], OffsetF(270, 0))
        << layoutAlgorithm.recordOffsetMap_["guideline4"].ToString();
}

/**
 * @tc.name: CalcGuidelineOffsetTest1
 * @tc.desc: Test CalcOffsetParam, use guideline.
 */
HWTEST_F(RelativeContainerGuidelineTest, CalcGuidelineOffsetTest1, TestSize.Level1)
{
    RefPtr<FrameNode> row1;
    auto relativeContainer = CreateRelativeContainer([this, &row1](RelativeContainerModelNG model) {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row1");
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::LEFT, "guideline2", HorizontalAlign::CENTER);
            AddAlignRule(alignRules, AlignDirection::TOP, "guideline1", HorizontalAlign::START);
            ViewAbstract::SetAlignRules(alignRules);
        });
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(400.0f, DimensionUnit::PX));
        std::vector<GuidelineInfo> infos;
        AddGuidelineStart(infos, "guideline1", LineDirection::HORIZONTAL, Dimension(0.1, DimensionUnit::PERCENT));
        AddGuidelineStart(infos, "guideline2", LineDirection::VERTICAL, Dimension(0.1, DimensionUnit::PERCENT));
        model.SetGuideline(infos);
    });
    // update selfIdealSize
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintF {});
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();
    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    PrepareMeasureChild(Referenced::RawPtr(relativeContainer), layoutAlgorithm);
    layoutAlgorithm.MeasureChild(Referenced::RawPtr(relativeContainer));

    // (300 * 0.1, 400 * 0.1)
    EXPECT_EQ(layoutAlgorithm.recordOffsetMap_["row1"], OffsetF(30, 40))
        << layoutAlgorithm.recordOffsetMap_["row1"].ToString();
}

/**
 * @tc.name: ResObjGuidelineTest1
 * @tc.desc: Test ResObjGuidelineTest1 of Relative_Container
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuidelineTest, ResObjGuidelineTest1, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    RelativeContainerModelNG relativeContainerModelNG;
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    auto updateFunc = [](const RefPtr<ResourceObject>& resObj, GuidelineInfo& guidelineInfo) {};
    GuidelineInfo guidelineInfo;
    guidelineInfo.AddResource("relativeContainer.guideLine.position.start", resObj, std::move(updateFunc));
    EXPECT_EQ(guidelineInfo.resMap_.empty(), false);
    std::vector<GuidelineInfo> guidelineInfos;
    guidelineInfos.emplace_back(guidelineInfo);
    relativeContainerModelNG.SetGuideline(guidelineInfos);
    auto layoutProperty = frameNode->GetLayoutProperty<RelativeContainerLayoutProperty>();
    EXPECT_EQ(layoutProperty->HasGuideline(), true);
}

/**
 * @tc.name: ResObjGuidelineTest2
 * @tc.desc: Test ResObjGuidelineTest2 of Relative_Container
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuidelineTest, ResObjGuidelineTest2, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    auto updateFunc = [](const RefPtr<ResourceObject>& resObj, GuidelineInfo& guidelineInfo) {};
    GuidelineInfo guidelineInfo;
    guidelineInfo.AddResource("relativeContainer.guideLine.position.start", resObj, std::move(updateFunc));
    EXPECT_EQ(guidelineInfo.resMap_.empty(), false);
    std::vector<GuidelineInfo> guidelineInfos;
    guidelineInfos.emplace_back(guidelineInfo);
    RelativeContainerModelNG::SetGuideline(frameNode, guidelineInfos);
    auto layoutProperty = frameNode->GetLayoutProperty<RelativeContainerLayoutProperty>();
    EXPECT_EQ(layoutProperty->HasGuideline(), true);
}
} // namespace OHOS::Ace::NG
