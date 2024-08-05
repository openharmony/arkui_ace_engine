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

#include <optional>
#include <vector>

#include "gtest/gtest.h"
#include "relative_container_common_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/position_param.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/relative_container/relative_container_layout_property.h"
#include "core/components_ng/pattern/relative_container/relative_container_model_ng.h"
#include "core/components_ng/pattern/relative_container/relative_container_pattern.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "frameworks/core/components/common/layout/position_param.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const float ITEM_WIDTH = 100.0f;
const float GUIDELINE_VALUE = 50.0f;

const std::vector<Dimension> DIMENSIONS = {
    Dimension(50.0, DimensionUnit::VP),
    Dimension(-10.0, DimensionUnit::VP),
    Dimension(0.5, DimensionUnit::PERCENT),
    Dimension(-0.1, DimensionUnit::PERCENT)
};
const std::vector<OffsetF> OFFSETS = {
    OffsetF(50.0f, 0.0f),
    OffsetF(-10.0f, 0.0f),
    OffsetF(150.0f, 0.0f),
    OffsetF(-30.0f, 0.0f)
};

const std::vector<OffsetF> RTLOFFSETS = {
    OffsetF(CONTAINER_WIDTH - ITEM_WIDTH - 50.0f, 0.0f),
    OffsetF(CONTAINER_WIDTH - ITEM_WIDTH - (-10.0f), 0.0f),
    OffsetF(CONTAINER_WIDTH - ITEM_WIDTH - 150.0f, 0.0f),
    OffsetF(CONTAINER_WIDTH - ITEM_WIDTH - (-30.0f), 0.0f)
};

const std::string FIRST_ITEM_ID = "bt1";
const std::string SECOND_ITEM_ID = "bt2";
const std::string GUIDELINE_ID = "guideline";
const std::string CONTAINER_ID = "__container__";
} // namespace

class RelativeContainerGuideTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    void CreateInstance(const std::function<void(RelativeContainerModelNG)>& callback = nullptr);

    static void SetUpTestCase();

    static void TearDownTestSuite();

    RefPtr<FrameNode> frameNode_;
    RefPtr<RelativeContainerPattern> pattern_;
    RefPtr<RelativeContainerLayoutProperty> layoutProperty_;
};

void RelativeContainerGuideTestNg::SetUp() {}

void RelativeContainerGuideTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
}

void RelativeContainerGuideTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void RelativeContainerGuideTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void RelativeContainerGuideTestNg::CreateInstance(const std::function<void(RelativeContainerModelNG)>& callback)
{
    RelativeContainerModelNG model;
    model.Create();
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<RelativeContainerPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<RelativeContainerLayoutProperty>();
}

/**
 * @tc.name: GuidelineTest001
 * @tc.desc: Set an item with Guideline with RelativeContainer and check it.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTest001, TestSize.Level1)
{
    /**
     * set pipeline: api = 11
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(11);
    for (int i = 0; i < 4; i++) {
        CreateInstance([=](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
            ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
            ViewAbstract::SetInspectorId(CONTAINER_ID);
            TextModelNG textModelFirst;
            textModelFirst.Create("text1");
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
            ViewAbstract::SetInspectorId("text1");
            std::map<AlignDirection, AlignRule> firstTextAlignRules;
            RelativeContainerTestUtilsNG::AddAlignRule(
                GUIDELINE_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
            RelativeContainerTestUtilsNG::AddAlignRule(
                CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, firstTextAlignRules);
            ViewAbstract::SetAlignRules(firstTextAlignRules);
            ViewStackProcessor::GetInstance()->Pop();

            GuidelineInfo guidelineInfo1;
            guidelineInfo1.id = GUIDELINE_ID;
            guidelineInfo1.direction = LineDirection::VERTICAL;
            guidelineInfo1.start = DIMENSIONS[i];
            std::vector<GuidelineInfo> GuidelineInfos = {
                guidelineInfo1
            };
            model.SetGuideline(std::vector<GuidelineInfo> { GuidelineInfos });
        });
        frameNode_->SetActive();
        frameNode_->SetLayoutDirtyMarked(true);
        frameNode_->CreateLayoutTask();
        frameNode_->SetActive(false);
        EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset(), OFFSETS[i]);
    }
}

/**
 * @tc.name: GuidelineTest002
 * @tc.desc: Set an item with Guideline with RelativeContainer and check it.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTest002, TestSize.Level1)
{
    std::vector<OffsetF> offsets = {
        OffsetF(250.0f, 0.0f),
        OffsetF(310.0f, 0.0f),
        OffsetF(150.0f, 0.0f),
        OffsetF(330.0f, 0.0f)
    };
    for (int i = 0; i < 4; i++) {
        CreateInstance([=](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
            ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
            ViewAbstract::SetInspectorId(CONTAINER_ID);
            TextModelNG textModelFirst;
            textModelFirst.Create("text1");
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
            ViewAbstract::SetInspectorId("text1");
            std::map<AlignDirection, AlignRule> firstTextAlignRules;
            RelativeContainerTestUtilsNG::AddAlignRule(
                GUIDELINE_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
            RelativeContainerTestUtilsNG::AddAlignRule(
                CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, firstTextAlignRules);
            ViewAbstract::SetAlignRules(firstTextAlignRules);
            ViewStackProcessor::GetInstance()->Pop();

            GuidelineInfo guidelineInfo1;
            guidelineInfo1.id = GUIDELINE_ID;
            guidelineInfo1.direction = LineDirection::VERTICAL;
            guidelineInfo1.end = DIMENSIONS[i];
            std::vector<GuidelineInfo> GuidelineInfos = {
                guidelineInfo1
            };
            model.SetGuideline(std::vector<GuidelineInfo> { GuidelineInfos });
        });
        frameNode_->SetActive();
        frameNode_->SetLayoutDirtyMarked(true);
        frameNode_->CreateLayoutTask();
        frameNode_->SetActive(false);
        EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset(), offsets[i]);
    }
}

/**
 * @tc.name: GuidelineTest003
 * @tc.desc: Set Guideline empty and check it.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTest003, TestSize.Level1)
{
    CreateInstance([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
        ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
        ViewAbstract::SetInspectorId(CONTAINER_ID);
        TextModelNG textModelFirst;
        textModelFirst.Create("text1");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text1");
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            GUIDELINE_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(
            CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        GuidelineInfo guidelineInfo1;
        guidelineInfo1.id = GUIDELINE_ID;
        std::vector<GuidelineInfo> GuidelineInfos = {
            guidelineInfo1
        };
        model.SetGuideline(std::vector<GuidelineInfo> { GuidelineInfos });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);
    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: GuidelineTest004
 * @tc.desc: Set Guideline HORIZONTAL and check it.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTest004, TestSize.Level1)
{
    CreateInstance([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
        ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
        ViewAbstract::SetInspectorId(CONTAINER_ID);
        TextModelNG textModelFirst;
        textModelFirst.Create("text1");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text1");
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            GUIDELINE_ID, AlignDirection::TOP, VerticalAlign::TOP, firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(
            CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        GuidelineInfo guidelineInfo1;
        guidelineInfo1.id = GUIDELINE_ID;
        guidelineInfo1.direction = LineDirection::HORIZONTAL;
        guidelineInfo1.start = Dimension(50.0, DimensionUnit::VP);
        std::vector<GuidelineInfo> GuidelineInfos = {
            guidelineInfo1
        };
        model.SetGuideline(std::vector<GuidelineInfo> { GuidelineInfos });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);
    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 50.0f));
}

/**
 * @tc.name: GuidelineTest005
 * @tc.desc: Set childNode vertical alignment verticalGuideline.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTest005, TestSize.Level1)
{
    CreateInstance([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
        ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
        ViewAbstract::SetInspectorId(CONTAINER_ID);
        TextModelNG textModelFirst;
        textModelFirst.Create("text1");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text1");
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            GUIDELINE_ID, AlignDirection::TOP, VerticalAlign::TOP, firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(
            CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        GuidelineInfo guidelineInfo1;
        guidelineInfo1.id = GUIDELINE_ID;
        guidelineInfo1.direction = LineDirection::VERTICAL;
        guidelineInfo1.start = Dimension(50.0, DimensionUnit::VP);
        std::vector<GuidelineInfo> GuidelineInfos = {
            guidelineInfo1
        };
        model.SetGuideline(std::vector<GuidelineInfo> { GuidelineInfos });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);
    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: GuidelineTest006
 * @tc.desc: Set childNode horizontal alignment horizontalGuideline.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTest006, TestSize.Level1)
{
    CreateInstance([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
        ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
        ViewAbstract::SetInspectorId(CONTAINER_ID);
        TextModelNG textModelFirst;
        textModelFirst.Create("text1");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text1");
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            GUIDELINE_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(
            CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        GuidelineInfo guidelineInfo1;
        guidelineInfo1.id = GUIDELINE_ID;
        guidelineInfo1.direction = LineDirection::HORIZONTAL;
        guidelineInfo1.start = Dimension(50.0, DimensionUnit::VP);
        std::vector<GuidelineInfo> GuidelineInfos = {
            guidelineInfo1
        };
        model.SetGuideline(std::vector<GuidelineInfo> { GuidelineInfos });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);
    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: GuidelineTest007
 * @tc.desc: Align childNode to the left/middle/right of verticalGuideline.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTest007, TestSize.Level1)
{
    std::vector<HorizontalAlign> horizontalAligns = {
        HorizontalAlign::START,
        HorizontalAlign::CENTER,
        HorizontalAlign::END
    };
    for (int i = 0; i < 3; i++) {
        CreateInstance([=](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
            ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
            ViewAbstract::SetInspectorId(CONTAINER_ID);
            TextModelNG textModelFirst;
            textModelFirst.Create("text1");
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
            ViewAbstract::SetInspectorId("text1");
            std::map<AlignDirection, AlignRule> firstTextAlignRules;
            RelativeContainerTestUtilsNG::AddAlignRule(
                GUIDELINE_ID, AlignDirection::LEFT, horizontalAligns[i], firstTextAlignRules);
            RelativeContainerTestUtilsNG::AddAlignRule(
                CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, firstTextAlignRules);
            ViewAbstract::SetAlignRules(firstTextAlignRules);
            ViewStackProcessor::GetInstance()->Pop();

            GuidelineInfo guidelineInfo1;
            guidelineInfo1.id = GUIDELINE_ID;
            guidelineInfo1.direction = LineDirection::VERTICAL;
            guidelineInfo1.start = Dimension(50.0, DimensionUnit::VP);
            std::vector<GuidelineInfo> GuidelineInfos = {
                guidelineInfo1
            };
            model.SetGuideline(std::vector<GuidelineInfo> { GuidelineInfos });
        });
        frameNode_->SetActive();
        frameNode_->SetLayoutDirtyMarked(true);
        frameNode_->CreateLayoutTask();
        frameNode_->SetActive(false);
        EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetX(), 50);
    }
}

/**
 * @tc.name: GuidelineTest008
 * @tc.desc: Align childNode to the center/bottom of horizontalGuideline.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTest008, TestSize.Level1)
{
    std::vector<VerticalAlign> verticalAligns = {
        VerticalAlign::TOP,
        VerticalAlign::CENTER,
        VerticalAlign::BOTTOM
    };
    for (int i = 0; i < 3; i++) {
        CreateInstance([=](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
            ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
            ViewAbstract::SetInspectorId(CONTAINER_ID);
            TextModelNG textModelFirst;
            textModelFirst.Create("text1");
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
            ViewAbstract::SetInspectorId("text1");
            std::map<AlignDirection, AlignRule> firstTextAlignRules;
            RelativeContainerTestUtilsNG::AddAlignRule(
                GUIDELINE_ID, AlignDirection::TOP, verticalAligns[i], firstTextAlignRules);
            RelativeContainerTestUtilsNG::AddAlignRule(
                CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
            ViewAbstract::SetAlignRules(firstTextAlignRules);
            ViewStackProcessor::GetInstance()->Pop();

            GuidelineInfo guidelineInfo1;
            guidelineInfo1.id = GUIDELINE_ID;
            guidelineInfo1.direction = LineDirection::HORIZONTAL;
            guidelineInfo1.start = Dimension(50.0, DimensionUnit::VP);
            std::vector<GuidelineInfo> GuidelineInfos = {
                guidelineInfo1
            };
            model.SetGuideline(std::vector<GuidelineInfo> { GuidelineInfos });
        });
        frameNode_->SetActive();
        frameNode_->SetLayoutDirtyMarked(true);
        frameNode_->CreateLayoutTask();
        frameNode_->SetActive(false);
        EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetY(), 50);
    }
}

/**
 * @tc.name: GuidelineTestRtl001
 * @tc.desc: Align childNode to the left/middle/right of verticalGuideline, direction::RTL.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTestRtl001, TestSize.Level1)
{
    std::vector<HorizontalAlign> horizontalAligns = {
        HorizontalAlign::START,
        HorizontalAlign::CENTER,
        HorizontalAlign::END
    };
    for (int i = 0; i < 3; i++) {
        CreateInstance([=](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
            ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
            ViewAbstract::SetInspectorId(CONTAINER_ID);
            TextModelNG textModelFirst;
            textModelFirst.Create("text1");
            ViewAbstract::SetWidth(CalcLength(ITEM_WIDTH));
            ViewAbstract::SetHeight(CalcLength(50.0f));
            ViewAbstract::SetInspectorId("text1");
            std::map<AlignDirection, AlignRule> firstTextAlignRules;
            RelativeContainerTestUtilsNG::AddAlignRule(
                GUIDELINE_ID, AlignDirection::START, horizontalAligns[i], firstTextAlignRules);
            RelativeContainerTestUtilsNG::AddAlignRule(
                CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, firstTextAlignRules);
            ViewAbstract::SetAlignRules(firstTextAlignRules);
            ViewStackProcessor::GetInstance()->Pop();

            GuidelineInfo guidelineInfo1;
            guidelineInfo1.id = GUIDELINE_ID;
            guidelineInfo1.direction = LineDirection::VERTICAL;
            guidelineInfo1.start = Dimension(GUIDELINE_VALUE, DimensionUnit::VP);
            std::vector<GuidelineInfo> GuidelineInfos = {
                guidelineInfo1
            };
            model.SetGuideline(std::vector<GuidelineInfo> { GuidelineInfos });
        });
        auto relativeContainerLayoutProperty = frameNode_->GetLayoutProperty();
        EXPECT_FALSE(relativeContainerLayoutProperty == nullptr);
        relativeContainerLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
        frameNode_->SetActive();
        frameNode_->SetLayoutDirtyMarked(true);
        frameNode_->CreateLayoutTask();
        frameNode_->SetActive(false);
        EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetX(),
            CONTAINER_WIDTH - ITEM_WIDTH - GUIDELINE_VALUE);
    }
}

/**
 * @tc.name: GuidelineTestRtl002
 * @tc.desc: Set an item with Guideline with RelativeContainer and check it, direction::RTL.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTestRtl002, TestSize.Level1)
{
    /**
     * set pipeline: api = 11
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(11);
    for (int i = 0; i < 4; i++) {
        CreateInstance([=](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
            ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
            ViewAbstract::SetInspectorId(CONTAINER_ID);
            TextModelNG textModelFirst;
            textModelFirst.Create("text1");
            ViewAbstract::SetWidth(CalcLength(ITEM_WIDTH));
            ViewAbstract::SetHeight(CalcLength(50.0f));
            ViewAbstract::SetInspectorId("text1");
            std::map<AlignDirection, AlignRule> firstTextAlignRules;
            RelativeContainerTestUtilsNG::AddAlignRule(
                GUIDELINE_ID, AlignDirection::START, HorizontalAlign::START, firstTextAlignRules);
            RelativeContainerTestUtilsNG::AddAlignRule(
                CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, firstTextAlignRules);
            ViewAbstract::SetAlignRules(firstTextAlignRules);
            ViewStackProcessor::GetInstance()->Pop();

            GuidelineInfo guidelineInfo1;
            guidelineInfo1.id = GUIDELINE_ID;
            guidelineInfo1.direction = LineDirection::VERTICAL;
            guidelineInfo1.start = DIMENSIONS[i];
            std::vector<GuidelineInfo> GuidelineInfos = {
                guidelineInfo1
            };
            model.SetGuideline(std::vector<GuidelineInfo> { GuidelineInfos });
        });
        auto relativeContainerLayoutProperty = frameNode_->GetLayoutProperty();
        EXPECT_FALSE(relativeContainerLayoutProperty == nullptr);
        relativeContainerLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);

        frameNode_->SetActive();
        frameNode_->SetLayoutDirtyMarked(true);
        frameNode_->CreateLayoutTask();
        frameNode_->SetActive(false);
        EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset(), RTLOFFSETS[i]);
    }
}

/**
 * @tc.name: UpdateTwoAlignValues001
 * @tc.desc: Test UpdateTwoAlignValues function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, UpdateTwoAlignValues001, TestSize.Level1)
{
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    std::pair<std::optional<float>, std::optional<float>> twoAlignedValues(1.23f, 4.56f);
    struct AlignRule alignRule;
    layoutAlgorithm->UpdateTwoAlignValues(twoAlignedValues, alignRule, LineDirection::HORIZONTAL);
    EXPECT_EQ(twoAlignedValues.first.value(), 1.23f);
    EXPECT_EQ(twoAlignedValues.second.value(), 4.56f);
}

/**
 * @tc.name: CalcHorizontalGuideline001
 * @tc.desc: Test CalcHorizontalGuideline function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, CalcHorizontalGuideline001, TestSize.Level1)
{
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    std::optional<CalcLength> width = CalcLength(CONTAINER_WIDTH);
    std::optional<CalcLength> height = CalcLength(CONTAINER_HEIGHT, DimensionUnit::AUTO);
    std::optional<CalcSize> selfIdealSize = CalcSize(width, height);
    GuidelineInfo guidelineInfo1;
    guidelineInfo1.id = "guideline";
    guidelineInfo1.direction = LineDirection::VERTICAL;
    guidelineInfo1.start = Dimension(50.0, DimensionUnit::PERCENT);
    guidelineInfo1.end = Dimension(100.0, DimensionUnit::PERCENT);
    layoutAlgorithm->CalcHorizontalGuideline(selfIdealSize, 0.5f, guidelineInfo1);
    EXPECT_EQ(layoutAlgorithm->guidelines_[guidelineInfo1.id].second, 0.0f);
}

/**
 * @tc.name: CalcHorizontalGuideline002
 * @tc.desc: Test CalcHorizontalGuideline function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, CalcHorizontalGuideline002, TestSize.Level1)
{
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    std::optional<CalcLength> width = CalcLength(CONTAINER_WIDTH);
    std::optional<CalcLength> height = CalcLength(CONTAINER_HEIGHT, DimensionUnit::AUTO);
    std::optional<CalcSize> selfIdealSize = CalcSize(width, height);
    GuidelineInfo guidelineInfo1;
    guidelineInfo1.id = "guideline";
    guidelineInfo1.direction = LineDirection::VERTICAL;
    guidelineInfo1.end = Dimension(100.0, DimensionUnit::PERCENT);
    layoutAlgorithm->CalcHorizontalGuideline(selfIdealSize, 0.5f, guidelineInfo1);
    EXPECT_EQ(layoutAlgorithm->guidelines_[guidelineInfo1.id].second, 0.0f);
}

/**
 * @tc.name: CalcHorizontalGuideline003
 * @tc.desc: Test CalcHorizontalGuideline function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, CalcHorizontalGuideline003, TestSize.Level1)
{
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    std::optional<CalcLength> width = CalcLength(CONTAINER_WIDTH);
    std::optional<CalcLength> height = CalcLength(CONTAINER_HEIGHT);
    std::optional<CalcSize> selfIdealSize = CalcSize(width, height);
    GuidelineInfo guidelineInfo1;
    guidelineInfo1.id = "guideline";
    guidelineInfo1.direction = LineDirection::VERTICAL;
    guidelineInfo1.end = Dimension(100.0, DimensionUnit::PERCENT);
    layoutAlgorithm->CalcHorizontalGuideline(selfIdealSize, 100.0f, guidelineInfo1);
    EXPECT_EQ(layoutAlgorithm->guidelines_[guidelineInfo1.id].first, LineDirection::HORIZONTAL);
}

/**
 * @tc.name: CalcVerticalGuideline001
 * @tc.desc: Test CalcVerticalGuideline function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, CalcVerticalGuideline001, TestSize.Level1)
{
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    std::optional<CalcLength> width = CalcLength(CONTAINER_WIDTH, DimensionUnit::AUTO);
    std::optional<CalcLength> height = CalcLength(CONTAINER_HEIGHT);
    std::optional<CalcSize> selfIdealSize = CalcSize(width, height);
    GuidelineInfo guidelineInfo1;
    guidelineInfo1.id = "guideline";
    guidelineInfo1.direction = LineDirection::VERTICAL;
    guidelineInfo1.end = Dimension(100.0, DimensionUnit::PERCENT);
    layoutAlgorithm->CalcVerticalGuideline(selfIdealSize, 100.0f, guidelineInfo1);
    EXPECT_EQ(layoutAlgorithm->guidelines_[guidelineInfo1.id].second, 0.0f);
}

/**
 * @tc.name: CalcVerticalGuideline002
 * @tc.desc: Test CalcVerticalGuideline function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, CalcVerticalGuideline002, TestSize.Level1)
{
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    std::optional<CalcLength> width = CalcLength(CONTAINER_WIDTH, DimensionUnit::AUTO);
    std::optional<CalcLength> height = CalcLength(CONTAINER_HEIGHT);
    std::optional<CalcSize> selfIdealSize = CalcSize(width, height);
    GuidelineInfo guidelineInfo1;
    guidelineInfo1.id = "guideline";
    guidelineInfo1.direction = LineDirection::VERTICAL;
    guidelineInfo1.start = Dimension(50.0, DimensionUnit::PERCENT);
    guidelineInfo1.end = Dimension(100.0, DimensionUnit::PERCENT);
    layoutAlgorithm->CalcVerticalGuideline(selfIdealSize, 100.0f, guidelineInfo1);
    EXPECT_EQ(layoutAlgorithm->guidelines_[guidelineInfo1.id].second, 0.0f);
}

/**
 * @tc.name: CheckNodeInHorizontalChain001
 * @tc.desc: Test CheckNodeInHorizontalChain function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, CheckNodeInHorizontalChain001, TestSize.Level1)
{
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    string currentNode = FIRST_ITEM_ID;
    string nextNode = SECOND_ITEM_ID;
    struct AlignRule alignRule = {"anchor"};
    alignRule.horizontal = HorizontalAlign::END;
    std::map<AlignDirection, AlignRule> currentAlignRules = {
        {AlignDirection::LEFT, alignRule},
        {AlignDirection::RIGHT, alignRule},
    };
    RelativeContainerLayoutAlgorithm::ChildMeasureWrapper childMeasureWrapper;
    layoutAlgorithm->idNodeMap_.insert({SECOND_ITEM_ID, childMeasureWrapper});
    std::vector<std::string> chainNodes;
    layoutAlgorithm->CheckNodeInHorizontalChain(currentNode, nextNode, currentAlignRules, chainNodes, alignRule);
    EXPECT_EQ(nextNode, SECOND_ITEM_ID);
}

/**
 * @tc.name: CheckNodeInHorizontalChain002
 * @tc.desc: Test CheckNodeInHorizontalChain function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, CheckNodeInHorizontalChain002, TestSize.Level1)
{
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    string currentNode = FIRST_ITEM_ID;
    string nextNode = SECOND_ITEM_ID;
    struct AlignRule alignRule = {"anchor"};
    alignRule.horizontal = HorizontalAlign::START;
    std::map<AlignDirection, AlignRule> currentAlignRules = {
        {AlignDirection::LEFT, alignRule},
        {AlignDirection::RIGHT, alignRule},
    };
    RelativeContainerLayoutAlgorithm::ChildMeasureWrapper childMeasureWrapper;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, 0,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    childMeasureWrapper.layoutWrapper = layoutWrapper;
    layoutAlgorithm->idNodeMap_.insert({SECOND_ITEM_ID, childMeasureWrapper});
    std::vector<std::string> chainNodes;
    layoutAlgorithm->CheckNodeInHorizontalChain(currentNode, nextNode, currentAlignRules, chainNodes, alignRule);
    EXPECT_EQ(nextNode.c_str(), SECOND_ITEM_ID);
}

/**
 * @tc.name: GetBarrierRectByReferencedIds001
 * @tc.desc: Test GetBarrierRectByReferencedIds function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, GetBarrierRectByReferencedIds001, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(11);
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    std::optional<CalcLength> width = CalcLength(CONTAINER_WIDTH);
    std::optional<CalcLength> height = CalcLength(CONTAINER_HEIGHT, DimensionUnit::AUTO);
    std::optional<CalcSize> selfIdealSize = CalcSize(width, height);
    GuidelineInfo guidelineInfo1;
    guidelineInfo1.id = FIRST_ITEM_ID;
    guidelineInfo1.direction = LineDirection::VERTICAL;
    guidelineInfo1.start = Dimension(50.0, DimensionUnit::PERCENT);
    guidelineInfo1.end = Dimension(100.0, DimensionUnit::PERCENT);
    layoutAlgorithm->CalcHorizontalGuideline(selfIdealSize, 0.5f, guidelineInfo1);
    EXPECT_EQ(layoutAlgorithm->guidelines_[guidelineInfo1.id].second, 0.0f);
    guidelineInfo1.id = SECOND_ITEM_ID;
    layoutAlgorithm->CalcVerticalGuideline(selfIdealSize, 100.0f, guidelineInfo1);
    std::vector<std::string> referencedIds;
    referencedIds.push_back(FIRST_ITEM_ID);
    referencedIds.push_back(SECOND_ITEM_ID);
    RelativeContainerLayoutAlgorithm::BarrierRect barrierRect =
        layoutAlgorithm->GetBarrierRectByReferencedIds(referencedIds);
    EXPECT_EQ(barrierRect.minLeft, 0.0f);
}

/**
 * @tc.name: GetBarrierRectByReferencedIds002
 * @tc.desc: Test GetBarrierRectByReferencedIds function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, GetBarrierRectByReferencedIds002, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(11);
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    std::vector<std::string> param;
    std::pair<BarrierDirection, std::vector<std::string>> barrierParams(BarrierDirection::BOTTOM, param);
    layoutAlgorithm->barriers_.insert({FIRST_ITEM_ID, barrierParams});
    std::pair<BarrierDirection, std::vector<std::string>> barrierParams1(BarrierDirection::TOP, param);
    layoutAlgorithm->barriers_.insert({SECOND_ITEM_ID, barrierParams1});
    std::vector<std::string> referencedIds;
    referencedIds.push_back(FIRST_ITEM_ID);
    referencedIds.push_back(SECOND_ITEM_ID);
    RelativeContainerLayoutAlgorithm::BarrierRect barrierRect =
        layoutAlgorithm->GetBarrierRectByReferencedIds(referencedIds);
    EXPECT_EQ(barrierRect.minTop, 0.0f);
}

/**
 * @tc.name: GetBarrierRectByReferencedIds003
 * @tc.desc: Test GetBarrierRectByReferencedIds function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, GetBarrierRectByReferencedIds003, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(11);
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    std::vector<std::string> param;
    std::pair<BarrierDirection, std::vector<std::string>> barrierParams(BarrierDirection::LEFT, param);
    layoutAlgorithm->barriers_.insert({FIRST_ITEM_ID, barrierParams});
    std::pair<BarrierDirection, std::vector<std::string>> barrierParams1(BarrierDirection::RIGHT, param);
    layoutAlgorithm->barriers_.insert({SECOND_ITEM_ID, barrierParams1});
    std::pair<BarrierDirection, std::vector<std::string>> barrierParams2(BarrierDirection::END, param);
    layoutAlgorithm->barriers_.insert({GUIDELINE_ID, barrierParams2});
    std::vector<std::string> referencedIds;
    referencedIds.push_back(FIRST_ITEM_ID);
    referencedIds.push_back(SECOND_ITEM_ID);
    referencedIds.push_back(GUIDELINE_ID);
    RelativeContainerLayoutAlgorithm::BarrierRect barrierRect =
        layoutAlgorithm->GetBarrierRectByReferencedIds(referencedIds);
    EXPECT_EQ(barrierRect.minLeft, 0.0f);
}

/**
 * @tc.name: GetHorizontalAnchorValueByAlignRule001
 * @tc.desc: Test GetHorizontalAnchorValueByAlignRule function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, GetHorizontalAnchorValueByAlignRule001, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(11);
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    struct AlignRule alignRule = {FIRST_ITEM_ID};
    alignRule.horizontal = HorizontalAlign::START;
    std::optional<CalcLength> width = CalcLength(CONTAINER_WIDTH);
    std::optional<CalcLength> height = CalcLength(CONTAINER_HEIGHT, DimensionUnit::AUTO);
    std::optional<CalcSize> selfIdealSize = CalcSize(width, height);
    GuidelineInfo guidelineInfo1;
    guidelineInfo1.id = FIRST_ITEM_ID;
    guidelineInfo1.direction = LineDirection::VERTICAL;
    guidelineInfo1.start = Dimension(50.0, DimensionUnit::PERCENT);
    guidelineInfo1.end = Dimension(100.0, DimensionUnit::PERCENT);
    layoutAlgorithm->CalcHorizontalGuideline(selfIdealSize, 0.5f, guidelineInfo1);
    EXPECT_EQ(layoutAlgorithm->guidelines_[guidelineInfo1.id].second, 0.0f);
    std::vector<std::string> param;
    std::pair<BarrierDirection, std::vector<std::string>> barrierParams(BarrierDirection::LEFT, param);
    layoutAlgorithm->barriers_.insert({FIRST_ITEM_ID, barrierParams});

    OffsetF offset(0.0f, 0.0f);
    layoutAlgorithm->recordOffsetMap_.insert({alignRule.anchor, offset});
    float horizontal = layoutAlgorithm->GetHorizontalAnchorValueByAlignRule(alignRule);
    EXPECT_EQ(horizontal, 0.0f);
}

/**
 * @tc.name: GetHorizontalAnchorValueByAlignRule002
 * @tc.desc: Test GetHorizontalAnchorValueByAlignRule function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, GetHorizontalAnchorValueByAlignRule002, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(11);
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    struct AlignRule alignRule = {FIRST_ITEM_ID};
    alignRule.horizontal = HorizontalAlign::START;
    std::optional<CalcLength> width = CalcLength(CONTAINER_WIDTH);
    std::optional<CalcLength> height = CalcLength(CONTAINER_HEIGHT, DimensionUnit::AUTO);
    std::optional<CalcSize> selfIdealSize = CalcSize(width, height);
    GuidelineInfo guidelineInfo1;
    guidelineInfo1.id = SECOND_ITEM_ID;
    guidelineInfo1.direction = LineDirection::VERTICAL;
    guidelineInfo1.start = Dimension(50.0, DimensionUnit::PERCENT);
    guidelineInfo1.end = Dimension(100.0, DimensionUnit::PERCENT);
    layoutAlgorithm->CalcHorizontalGuideline(selfIdealSize, 0.5f, guidelineInfo1);
    EXPECT_EQ(layoutAlgorithm->guidelines_[guidelineInfo1.id].second, 0.0f);
    std::vector<std::string> param;
    std::pair<BarrierDirection, std::vector<std::string>> barrierParams(BarrierDirection::LEFT, param);
    layoutAlgorithm->barriers_.insert({FIRST_ITEM_ID, barrierParams});

    OffsetF offset(0.0f, 0.0f);
    layoutAlgorithm->recordOffsetMap_.insert({alignRule.anchor, offset});
    float horizontal = layoutAlgorithm->GetHorizontalAnchorValueByAlignRule(alignRule);
    EXPECT_EQ(horizontal, 0.0f);
}

/**
 * @tc.name: MeasureSelf001
 * @tc.desc: Test MeasureSelf function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, MeasureSelf001, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(8);
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    LayoutWrapper* layoutWrapper = nullptr;
    layoutAlgorithm->MeasureSelf(layoutWrapper);
    EXPECT_TRUE(layoutWrapper == nullptr);
}

/**
 * @tc.name: CalcHorizontalLayoutParam001
 * @tc.desc: Test CalcHorizontalLayoutParam function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, CalcHorizontalLayoutParam001, TestSize.Level1)
{
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    LayoutWrapper* layoutWrapper = nullptr;
    struct AlignRule alignRule = {FIRST_ITEM_ID};
    layoutAlgorithm->CalcHorizontalLayoutParam(AlignDirection::BOTTOM, alignRule, layoutWrapper, FIRST_ITEM_ID);
    EXPECT_TRUE(layoutWrapper == nullptr);
}

/**
 * @tc.name: CalcVerticalLayoutParam001
 * @tc.desc: Test CalcVerticalLayoutParam function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, CalcVerticalLayoutParam001, TestSize.Level1)
{
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    LayoutWrapper* layoutWrapper = nullptr;
    struct AlignRule alignRule = {FIRST_ITEM_ID};
    layoutAlgorithm->CalcVerticalLayoutParam(AlignDirection::BOTTOM, alignRule, layoutWrapper, FIRST_ITEM_ID);
    EXPECT_TRUE(layoutWrapper == nullptr);
}

/**
 * @tc.name: CalcHorizontalOffsetAlignRight001
 * @tc.desc: Test CalcHorizontalOffsetAlignRight function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, CalcHorizontalOffsetAlignRight001, TestSize.Level1)
{
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    float anchorWidth = 100.0f;
    float flexItemWidth = 20.0f;
    float offet = layoutAlgorithm->CalcHorizontalOffsetAlignRight(HorizontalAlign::CENTER, anchorWidth, flexItemWidth);
    EXPECT_EQ(offet, 30.0f);
}

/**
 * @tc.name: CalcVerticalOffsetAlignBottom001
 * @tc.desc: Test CalcVerticalOffsetAlignBottom function.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerGuideTestNg, CalcVerticalOffsetAlignBottom001, TestSize.Level1)
{
    std::unique_ptr<RelativeContainerLayoutAlgorithm> layoutAlgorithm =
        std::make_unique<RelativeContainerLayoutAlgorithm>();
    float anchorHeight = 100.0f;
    float flexItemHeight = 20.0f;
    float offet = layoutAlgorithm->CalcVerticalOffsetAlignBottom(VerticalAlign::CENTER, anchorHeight, flexItemHeight);
    EXPECT_EQ(offet, 30.0f);
}

} // namespace OHOS::Ace::NG
