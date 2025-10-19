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
#include "relative_container_testtwo_ng.h"

namespace OHOS::Ace::NG {
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
}