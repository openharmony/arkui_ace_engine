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
const float ZERO = 0.0f;

const float FIRST_ITEM_WIDTH = 150.0f;
const float FIRST_ITEM_HEIGHT = 75.0f;

const float THIRD_ITEM_WIDTH = 225.0f;
const float THIRD_ITEM_HEIGHT = 75.0f;

const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
const SizeF THIRD_ITEM_SIZE(THIRD_ITEM_WIDTH, THIRD_ITEM_HEIGHT);

const OffsetF OFFSET_TOP_LEFT = OffsetF(ZERO, ZERO);
const OffsetF OFFSET_TOP_MIDDLE = OffsetF(CONTAINER_WIDTH / 2.0f, ZERO);
const OffsetF OFFSET_TOP_RIGHT = OffsetF(CONTAINER_WIDTH, ZERO);

const OffsetF OFFSET_CENTER_LEFT = OffsetF(ZERO, CONTAINER_HEIGHT / 2.0f);
const OffsetF OFFSET_CENTER_MIDDLE = OffsetF(CONTAINER_WIDTH / 2.0f, CONTAINER_HEIGHT / 2.0f);
const OffsetF OFFSET_CENTER_RIGHT = OffsetF(CONTAINER_WIDTH, CONTAINER_HEIGHT / 2.0f);

const OffsetF OFFSET_BOTTOM_LEFT = OffsetF(ZERO, CONTAINER_HEIGHT);
const OffsetF OFFSET_BOTTOM_MIDDLE = OffsetF(CONTAINER_WIDTH / 2.0f, CONTAINER_HEIGHT);
const OffsetF OFFSET_BOTTOM_RIGHT = OffsetF(CONTAINER_WIDTH, CONTAINER_HEIGHT);

const std::string FIRST_ITEM_ID = "bt1";
const std::string SECOND_ITEM_ID = "bt2";
const std::string THIRD_ITEM_ID = "bt3";
const std::string FOURTH_ITEM_ID = "bt4";
const std::string FIFTH_ITEM_ID = "bt5";
const std::string CONTAINER_ID = "__container__";
} // namespace

class RelativeContainerTestTwoNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    void CreateInstance(const std::function<void(RelativeContainerModelNG)>& callback = nullptr);
    void SetComponentParam(TextModelNG& textModelNG, std::string id, float width, float height);
    void SetContainerParam(std::string id, float width, float height);

    static void TearDownTestSuite()
    {
        TestNG::TearDownTestSuite();
    }

    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
    }

    RefPtr<FrameNode> frameNode_;
    RefPtr<RelativeContainerPattern> pattern_;
    RefPtr<RelativeContainerLayoutProperty> layoutProperty_;
};

void RelativeContainerTestTwoNg::SetUp() {}

void RelativeContainerTestTwoNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
}

void RelativeContainerTestTwoNg::CreateInstance(const std::function<void(RelativeContainerModelNG)>& callback)
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

void RelativeContainerTestTwoNg::SetComponentParam(TextModelNG& textModelNG, std::string id, float width, float height)
{
    textModelNG.Create(StringUtils::Str8ToStr16(id));
    ViewAbstract::SetWidth(CalcLength(width));
    ViewAbstract::SetHeight(CalcLength(height));
    ViewAbstract::SetInspectorId(id);
}

void RelativeContainerTestTwoNg::SetContainerParam(std::string id, float width, float height)
{
    ViewAbstract::SetWidth(CalcLength(width));
    ViewAbstract::SetHeight(CalcLength(height));
    ViewAbstract::SetInspectorId(id);
}

/**
 * @tc.name: BarrierTest001
 * @tc.desc: BarrierDirection::LEFT, AlignDirection::LEFT.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, BarrierTest001, TestSize.Level0)
{
    /**
     * set pipeline: api = 11
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(11);
    CreateInstance([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
        ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
        ViewAbstract::SetInspectorId(CONTAINER_ID);
        TextModelNG textModelFirst;
        textModelFirst.Create(u"text1");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text1");
        ViewStackProcessor::GetInstance()->Pop();

        /**
        * add first child
        */
        TextModelNG textModelSecond;
        textModelSecond.Create(u"text2");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text2");
        ViewStackProcessor::GetInstance()->Pop();

        /**
        * add second child
        */
        TextModelNG textModelThird;
        textModelThird.Create(u"text3");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text3");

        /**
        * add third child, set align rules
        */
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "barrier1", AlignDirection::LEFT, HorizontalAlign::START, thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::LEFT;
        firstBarrierInfo.referencedId = std::vector<string> { "text1", "text2" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 0.0f);
}

/**
 * @tc.name: BarrierTest002
 * @tc.desc: BarrierDirection::RIGHT, AlignDirection::LEFT.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, BarrierTest002, TestSize.Level0)
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
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        textModelSecond.Create(u"text2");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text2");
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        textModelThird.Create(u"text3");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text3");

        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "barrier1", AlignDirection::LEFT, HorizontalAlign::START, thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::RIGHT;
        firstBarrierInfo.referencedId = std::vector<string> { "text1", "text2" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 100.0f);
}

/**
 * @tc.name: BarrierTest003
 * @tc.desc: BarrierDirection::TOP, AlignDirection::TOP.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, BarrierTest003, TestSize.Level0)
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
            CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        textModelSecond.Create(u"text2");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text2");
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "text1", AlignDirection::LEFT, HorizontalAlign::START, secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        textModelThird.Create(u"text3");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text3");
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "barrier1", AlignDirection::TOP, VerticalAlign::TOP, thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::TOP;
        firstBarrierInfo.referencedId = std::vector<string> { "text1", "text2" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
}

/**
 * @tc.name: BarrierTest004
 * @tc.desc: BarrierDirection::BOTTOM, AlignDirection::BOTTOM.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, BarrierTest004, TestSize.Level0)
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
            CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        textModelSecond.Create(u"text2");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text2");
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "text1", AlignDirection::LEFT, HorizontalAlign::START, secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        textModelThird.Create(u"text3");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(20.0f));
        ViewAbstract::SetInspectorId("text3");
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "barrier1", AlignDirection::BOTTOM, VerticalAlign::BOTTOM, thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::BOTTOM;
        firstBarrierInfo.referencedId = std::vector<string> { "text1", "text2" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetY(), 30.0f);
}

/**
 * @tc.name: BarrierTest005
 * @tc.desc: BarrierDirection::LEFT, AlignDirection::LEFT
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, BarrierTest005, TestSize.Level0)
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
            CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        textModelSecond.Create(u"text2");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text2");
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "text1", AlignDirection::LEFT, HorizontalAlign::START, secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        textModelThird.Create(u"text3");
        ViewAbstract::SetWidth(CalcLength(40.0f));
        ViewAbstract::SetHeight(CalcLength(20.0f));
        ViewAbstract::SetInspectorId("text3");
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "barrier1", AlignDirection::LEFT, VerticalAlign::BOTTOM, thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        //.barrier
        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::LEFT;
        firstBarrierInfo.referencedId = std::vector<string> { "text1", "text2" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 0.0f);
}

/**
 * @tc.name: BarrierTest006
 * @tc.desc: don't have reference id.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, BarrierTest006, TestSize.Level0)
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
            CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        textModelSecond.Create(u"text2");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text2");
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "text1", AlignDirection::LEFT, HorizontalAlign::START, secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        textModelThird.Create(u"text3");
        ViewAbstract::SetWidth(CalcLength(40.0f));
        ViewAbstract::SetHeight(CalcLength(20.0f));
        ViewAbstract::SetInspectorId("text3");
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "barrier1", AlignDirection::LEFT, HorizontalAlign::START, thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        /**
        * no referenceId.
        */
        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::LEFT;
        firstBarrierInfo.referencedId = std::vector<string>();
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 0.0f);
}

/**
 * @tc.name: BarrierTest007
 * @tc.desc: test id not exist.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, BarrierTest007, TestSize.Level0)
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
            CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        textModelSecond.Create(u"text2");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text2");
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "text1", AlignDirection::LEFT, HorizontalAlign::START, secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        textModelThird.Create(u"text3");
        ViewAbstract::SetWidth(CalcLength(40.0f));
        ViewAbstract::SetHeight(CalcLength(20.0f));
        ViewAbstract::SetInspectorId("text3");
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "barrier1", AlignDirection::LEFT, HorizontalAlign::START, thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        /**
        * use reference id text4, and text4 not exist, test barrier.
        */
        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::LEFT;
        firstBarrierInfo.referencedId = std::vector<string> { "text4", "text1" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 0.0f);
}

/**
 * @tc.name: BarrierTest008
 * @tc.desc: BarrierDirection::TOP, AlignDirection::LEFT.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, BarrierTest008, TestSize.Level0)
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
            CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        textModelSecond.Create(u"text2");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text2");
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "text1", AlignDirection::LEFT, HorizontalAlign::START, secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        textModelThird.Create(u"text3");
        ViewAbstract::SetWidth(CalcLength(40.0f));
        ViewAbstract::SetHeight(CalcLength(20.0f));
        ViewAbstract::SetInspectorId("text3");
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "barrier1", AlignDirection::LEFT, HorizontalAlign::START, thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::TOP;
        firstBarrierInfo.referencedId = std::vector<string> { "text1", "text2" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 0.0f);
}

/**
 * @tc.name: BarrierTest009
 * @tc.desc: BarrierDirection::RIGHT, AlignDirection::TOP.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, BarrierTest009, TestSize.Level0)
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
            CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        textModelSecond.Create(u"text2");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text2");
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "text1", AlignDirection::LEFT, VerticalAlign::TOP, secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        textModelThird.Create(u"text3");
        ViewAbstract::SetWidth(CalcLength(40.0f));
        ViewAbstract::SetHeight(CalcLength(20.0f));
        ViewAbstract::SetInspectorId("text3");
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "barrier1", AlignDirection::TOP, HorizontalAlign::START, thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::RIGHT;
        firstBarrierInfo.referencedId = std::vector<string> { "text1", "text2" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
}

/**
 * @tc.name: BarrierTest010
 * @tc.desc: BarrierDirection::RIGHT, AlignDirection::LEFT, HorizontalAlign::START.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, BarrierTest010, TestSize.Level0)
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
            CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        textModelSecond.Create(u"text2");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text2");
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "text1", AlignDirection::LEFT, HorizontalAlign::START, secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        textModelThird.Create(u"text3");
        ViewAbstract::SetWidth(CalcLength(40.0f));
        ViewAbstract::SetHeight(CalcLength(20.0f));
        ViewAbstract::SetInspectorId("text3");
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "barrier1", AlignDirection::LEFT, HorizontalAlign::START, thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::RIGHT;
        firstBarrierInfo.referencedId = std::vector<string> { "text1", "text2" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 100.0f);
}

/**
 * @tc.name: BarrierTest011
 * @tc.desc: BarrierDirection::RIGHT, AlignDirection::LEFT, HorizontalAlign::CENTER.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, BarrierTest011, TestSize.Level0)
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
            CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        textModelSecond.Create(u"text2");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text2");
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "text1", AlignDirection::LEFT, HorizontalAlign::START, secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        textModelThird.Create(u"text3");
        ViewAbstract::SetWidth(CalcLength(40.0f));
        ViewAbstract::SetHeight(CalcLength(20.0f));
        ViewAbstract::SetInspectorId("text3");
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "barrier1", AlignDirection::LEFT, HorizontalAlign::CENTER, thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::RIGHT;
        firstBarrierInfo.referencedId = std::vector<string> { "text1", "text2" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 100.0f);
}

/**
 * @tc.name: BarrierTest012
 * @tc.desc: BarrierDirection::RIGHT, AlignDirection::LEFT, HorizontalAlign::END.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, BarrierTest012, TestSize.Level0)
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
            CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        textModelSecond.Create(u"text2");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text2");
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "text1", AlignDirection::LEFT, HorizontalAlign::START, secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        textModelThird.Create(u"text3");
        ViewAbstract::SetWidth(CalcLength(40.0f));
        ViewAbstract::SetHeight(CalcLength(20.0f));
        ViewAbstract::SetInspectorId("text3");
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "barrier1", AlignDirection::LEFT, HorizontalAlign::END, thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::RIGHT;
        firstBarrierInfo.referencedId = std::vector<string> { "text1", "text2" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 100.0f);
}

/**
 * @tc.name: BarrierTest013
 * @tc.desc: BarrierDirection::TOP, AlignDirection::TOP, VerticalAlign::TOP.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, BarrierTest013, TestSize.Level0)
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
            CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        textModelSecond.Create(u"text2");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text2");
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "text1", AlignDirection::LEFT, HorizontalAlign::START, secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        textModelThird.Create(u"text3");
        ViewAbstract::SetWidth(CalcLength(40.0f));
        ViewAbstract::SetHeight(CalcLength(20.0f));
        ViewAbstract::SetInspectorId("text3");
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "barrier1", AlignDirection::TOP, VerticalAlign::TOP, thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::RIGHT;
        firstBarrierInfo.referencedId = std::vector<string> { "text1", "text2" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
}

/**
 * @tc.name: BarrierTest014
 * @tc.desc: BarrierDirection::TOP, AlignDirection::TOP, VerticalAlign::CENTER.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, BarrierTest014, TestSize.Level0)
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
            CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        textModelSecond.Create(u"text2");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text2");
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "text1", AlignDirection::LEFT, HorizontalAlign::START, secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        textModelThird.Create(u"text3");
        ViewAbstract::SetWidth(CalcLength(40.0f));
        ViewAbstract::SetHeight(CalcLength(20.0f));
        ViewAbstract::SetInspectorId("text3");
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "barrier1", AlignDirection::TOP, VerticalAlign::CENTER, thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::TOP;
        firstBarrierInfo.referencedId = std::vector<string> { "text1", "text2" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
}

/**
 * @tc.name: BarrierTest015
 * @tc.desc: BarrierDirection::TOP, AlignDirection::TOP, VerticalAlign::BOTTOM.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, BarrierTest015, TestSize.Level0)
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
            CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        textModelSecond.Create(u"text2");
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(50.0f));
        ViewAbstract::SetInspectorId("text2");
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "text1", AlignDirection::LEFT, HorizontalAlign::START, secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        textModelThird.Create(u"text3");
        ViewAbstract::SetWidth(CalcLength(40.0f));
        ViewAbstract::SetHeight(CalcLength(20.0f));
        ViewAbstract::SetInspectorId("text3");
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(
            "barrier1", AlignDirection::TOP, VerticalAlign::BOTTOM, thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::TOP;
        firstBarrierInfo.referencedId = std::vector<string> { "text1", "text2" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
}

/**
 * @tc.name: ChainTest001
 * @tc.desc: chainMode direction LineDirection::HORIZONTAL style ChainStyle::SPREAD
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTest001, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 80.0f, 50.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::START,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::HORIZONTAL;
        chainInfo.style = ChainStyle::SPREAD;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 80.0f, 50.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(FIRST_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(THIRD_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::START,
            secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 80.0f, 50.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END,
            thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetX(), 15.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetX(), 110.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 205.0f);
}

/**
 * @tc.name: ChainTest002
 * @tc.desc: chainMode direction LineDirection::HORIZONTAL style ChainStyle::SPREAD_INSIDE
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTest002, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 80.0f, 50.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::START,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::HORIZONTAL;
        chainInfo.style = ChainStyle::SPREAD_INSIDE;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 80.0f, 50.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(FIRST_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(THIRD_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::START,
            secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 80.0f, 50.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END,
            thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetX(), 0.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetX(), 110.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 220.0f);
}

/**
 * @tc.name: ChainTest003
 * @tc.desc: chainMode direction LineDirection::HORIZONTAL style ChainStyle::PACKED
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTest003, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 80.0f, 50.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::START,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::HORIZONTAL;
        chainInfo.style = ChainStyle::PACKED;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 80.0f, 50.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(FIRST_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(THIRD_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::START,
            secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 80.0f, 50.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END,
            thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetX(), 30.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetX(), 110.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 190.0f);
}

/**
 * @tc.name: ChainTest004
 * @tc.desc: chainMode direction LineDirection::HORIZONTAL style ChainStyle::PACKED bias(0,0)
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTest004, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 80.0f, 50.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::START,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewAbstract::SetBias(std::make_pair(0.0f, 0.0f));
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::HORIZONTAL;
        chainInfo.style = ChainStyle::PACKED;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 80.0f, 50.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(FIRST_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(THIRD_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::START,
            secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 80.0f, 50.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END,
            thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetX(), 0.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetX(), 80.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 160.0f);
}

/**
 * @tc.name: ChainTest005
 * @tc.desc: chainMode direction LineDirection::VERTICAL style ChainStyle::SPREAD
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTest005, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::BOTTOM, VerticalAlign::TOP,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::VERTICAL;
        chainInfo.style = ChainStyle::SPREAD;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(FIRST_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(THIRD_ITEM_ID, AlignDirection::BOTTOM, VerticalAlign::TOP,
            secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM,
            thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetY(), 15.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetY(), 110.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetY(), 205.0f);
}

/**
 * @tc.name: ChainTest006
 * @tc.desc: chainMode direction LineDirection::VERTICAL style ChainStyle::SPREAD_INSIDE
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTest006, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::BOTTOM, VerticalAlign::TOP,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::VERTICAL;
        chainInfo.style = ChainStyle::SPREAD_INSIDE;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(FIRST_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(THIRD_ITEM_ID, AlignDirection::BOTTOM, VerticalAlign::TOP,
            secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM,
            thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetY(), 110.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetY(), 220.0f);
}

/**
 * @tc.name: ChainTest007
 * @tc.desc: chainMode direction LineDirection::VERTICAL style ChainStyle::PACKED
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTest007, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::BOTTOM, VerticalAlign::TOP,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::VERTICAL;
        chainInfo.style = ChainStyle::PACKED;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(FIRST_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(THIRD_ITEM_ID, AlignDirection::BOTTOM, VerticalAlign::TOP,
            secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM,
            thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetY(), 30.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetY(), 110.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetY(), 190.0f);
}

/**
 * @tc.name: ChainTest008
 * @tc.desc: chainMode direction LineDirection::VERTICAL style ChainStyle::PACKED bias(0,0)
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTest008, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::BOTTOM, VerticalAlign::TOP,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewAbstract::SetBias(std::make_pair(0.0f, 0.0f));
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::VERTICAL;
        chainInfo.style = ChainStyle::PACKED;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(FIRST_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(THIRD_ITEM_ID, AlignDirection::BOTTOM, VerticalAlign::TOP,
            secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM,
            thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetY(), 80.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetY(), 160.0f);
}

/**
 * @tc.name: ChainTest009
 * @tc.desc: chainMode without chain relationship
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTest009, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewAbstract::SetBias(std::make_pair(0.0f, 0.0f));
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::VERTICAL;
        chainInfo.style = ChainStyle::PACKED;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
}

/**
 * @tc.name: ChainTest010
 * @tc.desc: chain without start anchor
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTest010, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::BOTTOM, VerticalAlign::TOP,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewAbstract::SetBias(std::make_pair(0.0f, 0.0f));
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::VERTICAL;
        chainInfo.style = ChainStyle::PACKED;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(FIRST_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(THIRD_ITEM_ID, AlignDirection::BOTTOM, VerticalAlign::TOP,
            secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM,
            thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
}

/**
 * @tc.name: ChainTest011
 * @tc.desc: chain without end anchor
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTest011, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::BOTTOM, VerticalAlign::TOP,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewAbstract::SetBias(std::make_pair(0.0f, 0.0f));
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::VERTICAL;
        chainInfo.style = ChainStyle::PACKED;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(FIRST_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(THIRD_ITEM_ID, AlignDirection::BOTTOM, VerticalAlign::TOP,
            secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM,
            thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
}

/**
 * @tc.name: ChainTest012
 * @tc.desc: chainMode with broken chain relationship
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTest012, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::BOTTOM, VerticalAlign::TOP,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewAbstract::SetBias(std::make_pair(0.0f, 0.0f));
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::VERTICAL;
        chainInfo.style = ChainStyle::PACKED;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(THIRD_ITEM_ID, AlignDirection::BOTTOM, VerticalAlign::TOP,
            secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 80.0f, 80.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM,
            thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
}

/**
 * @tc.name: ChainTest0013
 * @tc.desc: content of spread chain is outside the constraints of the anchor
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTest0013, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 110.0f, 50.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::START,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::HORIZONTAL;
        chainInfo.style = ChainStyle::SPREAD;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 110.0f, 50.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(FIRST_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(THIRD_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::START,
            secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 110.0f, 50.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END,
            thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetX(), -15.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetX(), 95.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 205.0f);
}

/**
 * @tc.name: ChainTest0014
 * @tc.desc: content of spread_inside chain is outside the constraints of the anchor
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTest0014, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 110.0f, 50.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::START,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::HORIZONTAL;
        chainInfo.style = ChainStyle::SPREAD_INSIDE;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 110.0f, 50.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(FIRST_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(THIRD_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::START,
            secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 110.0f, 50.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END,
            thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetX(), -15.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetX(), 95.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 205.0f);
}

/**
 * @tc.name: ChainTest0015
 * @tc.desc: content of packed chain is outside the constraints of the anchor
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTest0015, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 110.0f, 50.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::START,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::HORIZONTAL;
        chainInfo.style = ChainStyle::PACKED;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 110.0f, 50.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(FIRST_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(THIRD_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::START,
            secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 110.0f, 50.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END,
            thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetX(), -15.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetX(), 95.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 205.0f);
}

/**
 * @tc.name: ChainTest0016
 * @tc.desc: content of packed chain with bias is outside the constraints of the anchor
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTest0016, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 110.0f, 50.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START,
            firstTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::START,
            firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewAbstract::SetBias(std::make_pair(0.0f, 0.0f));
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::HORIZONTAL;
        chainInfo.style = ChainStyle::PACKED;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 110.0f, 50.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(FIRST_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END,
            secondTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(THIRD_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::START,
            secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 110.0f, 50.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(SECOND_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END,
            thirdTextAlignRules);
        RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END,
            thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetX(), 0.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetX(), 110.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 220.0f);
}

static void AddAlignRule(const std::string& id, const AlignDirection& direction,
    const HorizontalAlign& horizontalRule, std::map<AlignDirection, AlignRule>& alignRules)
{
    RelativeContainerTestUtilsNG::AddAlignRule(id, direction, horizontalRule, alignRules);
}

static void AddAlignRule(const std::string& id, const AlignDirection& direction,
    const VerticalAlign& verticalRule, std::map<AlignDirection, AlignRule>& alignRules)
{
    RelativeContainerTestUtilsNG::AddAlignRule(id, direction, verticalRule, alignRules);
}

/**
 * @tc.name: ChainTestRtl001
 * @tc.desc: content of packed chain with bias is outside the constraints of the anchor, direction::RTL.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestTwoNg, ChainTestRtl001, TestSize.Level0)
{
    CreateInstance([=](RelativeContainerModelNG model) {
        SetContainerParam(CONTAINER_ID, CONTAINER_WIDTH, CONTAINER_HEIGHT);
        TextModelNG textModelFirst;
        SetComponentParam(textModelFirst, FIRST_ITEM_ID, 100.0f, 50.0f);
        std::map<AlignDirection, AlignRule> firstTextAlignRules;
        AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, firstTextAlignRules);
        AddAlignRule(CONTAINER_ID, AlignDirection::START, HorizontalAlign::START, firstTextAlignRules);
        AddAlignRule(SECOND_ITEM_ID, AlignDirection::END, HorizontalAlign::START, firstTextAlignRules);
        ViewAbstract::SetAlignRules(firstTextAlignRules);
        ViewAbstract::SetBias(std::make_pair(0.0f, 0.0f));
        ChainInfo chainInfo;
        chainInfo.direction = LineDirection::HORIZONTAL;
        chainInfo.style = ChainStyle::PACKED;
        ViewAbstract::SetChainStyle(chainInfo);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelSecond;
        SetComponentParam(textModelSecond, SECOND_ITEM_ID, 100.0f, 50.0f);
        std::map<AlignDirection, AlignRule> secondTextAlignRules;
        AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, secondTextAlignRules);
        AddAlignRule(FIRST_ITEM_ID, AlignDirection::START, HorizontalAlign::END, secondTextAlignRules);
        AddAlignRule(THIRD_ITEM_ID, AlignDirection::END, HorizontalAlign::START, secondTextAlignRules);
        ViewAbstract::SetAlignRules(secondTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();

        TextModelNG textModelThird;
        SetComponentParam(textModelThird, THIRD_ITEM_ID, 100.0f, 50.0f);
        std::map<AlignDirection, AlignRule> thirdTextAlignRules;
        AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, thirdTextAlignRules);
        AddAlignRule(SECOND_ITEM_ID, AlignDirection::START, HorizontalAlign::END, thirdTextAlignRules);
        AddAlignRule(CONTAINER_ID, AlignDirection::END, HorizontalAlign::END, thirdTextAlignRules);
        ViewAbstract::SetAlignRules(thirdTextAlignRules);
        ViewStackProcessor::GetInstance()->Pop();
    });
    auto relativeContainerLayoutProperty = frameNode_->GetLayoutProperty();
    EXPECT_FALSE(relativeContainerLayoutProperty == nullptr);
    relativeContainerLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    frameNode_->SetActive();
    frameNode_->SetLayoutDirtyMarked(true);
    frameNode_->CreateLayoutTask();
    frameNode_->SetActive(false);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetX(),
        CONTAINER_WIDTH - 100.0f - 0.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset().GetX(),
        CONTAINER_WIDTH - 100.0f - 100.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(),
        CONTAINER_WIDTH - 100.0f - 200.0f);
}

} // namespace OHOS::Ace::NG
