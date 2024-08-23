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
#include "relative_container_base_test_ng.h"

#include "core/components/common/layout/position_param.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const std::string CONTAINER_ID = "__container__";
} // namespace
class RelativeContainerNewTestNG : public RelativeContainerBaseTestNG {};

/**
 * @tc.name: Example
 * @tc.desc: Show an example of creating a test case to test barrier.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, BarrierAttrTest001, TestSize.Level1)
{
    // If this test is related to api versions, need to SetMinPlatformVersion
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(11);

    /**
    corresponding ets code:
       RelativeContainer(){
        Text('text1').width(100).height(50).id("text1")
          .alignRules({
            left: {anchor: "__container__", align: HorizontalAlign.Start},
          }).backgroundColor(Color.Green)
        Text('text2').width(100).height(50).id("text2")
          .alignRules({
            left: {anchor: "text1", align: HorizontalAlign.End},
          }).backgroundColor(Color.Green)

        Text('text3').width(100).height(50).id("text3")
          .alignRules({
            left: {anchor: "barrier1", align: HorizontalAlign.Start},
          }).backgroundColor(Color.Yellow)
      }.width(300).height(300).backgroundColor(Color.Red)
      .barrier([{id: "barrier1", direction: BarrierDirection.RIGHT, referencedId:["text1", "text2"]}])
    */
    auto frameNode = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
        ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
        ViewAbstract::SetInspectorId(CONTAINER_ID);
        auto text1 = CreateText("text1", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
            ViewAbstract::SetInspectorId("text1");
            std::map<AlignDirection, AlignRule> firstTextAlignRules;
            RelativeContainerTestUtilsNG::AddAlignRule(
                CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
            ViewAbstract::SetAlignRules(firstTextAlignRules);
        });
        auto text2 = CreateText("text2", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
            ViewAbstract::SetInspectorId("text2");
            std::map<AlignDirection, AlignRule> secondTextAlignRules;
            RelativeContainerTestUtilsNG::AddAlignRule(
                "text1", AlignDirection::LEFT, HorizontalAlign::END, secondTextAlignRules);
            ViewAbstract::SetAlignRules(secondTextAlignRules);
        });
        auto text3 = CreateText("text3", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
            ViewAbstract::SetInspectorId("text3");
            std::map<AlignDirection, AlignRule> thirdTextAlignRules;
            RelativeContainerTestUtilsNG::AddAlignRule(
                "barrier1", AlignDirection::LEFT, HorizontalAlign::START, thirdTextAlignRules);
            ViewAbstract::SetAlignRules(thirdTextAlignRules);
        });
        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::RIGHT;
        firstBarrierInfo.referencedId = std::vector<string> { "text1", "text2" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    ASSERT_EQ(frameNode->GetChildren().size(), 3);
    CreateLayoutTask(frameNode);

    // expect: text3 is next to the right of text2
    EXPECT_EQ(frameNode->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 200.0f);
}
} // namespace OHOS::Ace::NG