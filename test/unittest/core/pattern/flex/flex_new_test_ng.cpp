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
#include "flex_base_test_ng.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

namespace {
const int32_t SECOND_CHILD = 1;
} // namespace
class FlexNewTestNG : public FlexBaseTestNG {};

/**
 * @tc.name: Template
 * @tc.desc: Show an example of creating a test case.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, Example, TestSize.Level1)
{
    // If this test is related to api versions, need to SetMinPlatformVersion
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(12);

    /**
    corresponding ets code:
       Flex({direction: FlexDirection.Row}){
          Text().width(100).height(50)
          Text().width(100).height(50)
      }.width(300).height(300)
    */
    auto frameNode = CreateFlexRow([this](FlexModelNG model) {
        // step: set direction: FlexDirection.Row
        model.SetDirection(FlexDirection::ROW);

        // step: set flex common attribute
        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));

        // // step: create child nodes
        auto text1 = CreateText("text1", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        auto text2 = CreateText("text2", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
    });
    ASSERT_EQ(frameNode->GetChildren().size(), 2);
    CreateLayoutTask(frameNode);

    // expect: second text offset x = 100.0f
    EXPECT_EQ(frameNode->GetChildByIndex(SECOND_CHILD)->GetGeometryNode()->GetFrameOffset().GetX(), 100.0f);
}
} // namespace OHOS::Ace::NG