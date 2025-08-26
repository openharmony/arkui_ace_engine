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
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/relative_container/old_cases/relative_container_common_ng.h"
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
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTest001, TestSize.Level0)
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
            textModelFirst.Create(u"text1");
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
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTest002, TestSize.Level0)
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
            textModelFirst.Create(u"text1");
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
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTest003, TestSize.Level0)
{
    CreateInstance([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
        ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
        ViewAbstract::SetInspectorId(CONTAINER_ID);
        TextModelNG textModelFirst;
        textModelFirst.Create(u"text1");
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
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTest004, TestSize.Level0)
{
    CreateInstance([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
        ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
        ViewAbstract::SetInspectorId(CONTAINER_ID);
        TextModelNG textModelFirst;
        textModelFirst.Create(u"text1");
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
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTest005, TestSize.Level0)
{
    CreateInstance([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
        ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
        ViewAbstract::SetInspectorId(CONTAINER_ID);
        TextModelNG textModelFirst;
        textModelFirst.Create(u"text1");
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
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTest006, TestSize.Level0)
{
    CreateInstance([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
        ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
        ViewAbstract::SetInspectorId(CONTAINER_ID);
        TextModelNG textModelFirst;
        textModelFirst.Create(u"text1");
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
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTest007, TestSize.Level0)
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
            textModelFirst.Create(u"text1");
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
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTest008, TestSize.Level0)
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
            textModelFirst.Create(u"text1");
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
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTestRtl001, TestSize.Level0)
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
            textModelFirst.Create(u"text1");
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
HWTEST_F(RelativeContainerGuideTestNg, GuidelineTestRtl002, TestSize.Level0)
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
            textModelFirst.Create(u"text1");
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
} // namespace OHOS::Ace::NG
