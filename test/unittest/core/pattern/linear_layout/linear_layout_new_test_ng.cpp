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
#include "linear_layout_base_test_ng.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
const int32_t FIRST_CHILD = 0;
const int32_t SECOND_CHILD = 1;
} // namespace
class LinearLayoutNewTestNG : public LinearLayoutBaseTestNG {};

/**
 * @tc.name: Example
 * @tc.desc: Show an example of creating a test case.
 * @tc.type: ETS
 */
HWTEST_F(LinearLayoutNewTestNG, Example, TestSize.Level1)
{
    // If this test is related to api versions, need to SetMinPlatformVersion
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(12);
    /**
    corresponding ets code:

    Column() {
        Column()
         .width('50%')
         .height(30)
         .backgroundColor(0xAFEEEE)
        Column()
        .width('50%')
        .height(30)
        .backgroundColor(0x00FFFF)
      }
       .alignItems(HorizontalAlign.Start)
       .width('300px')
       .height('300px')
    */
    auto frameNode = CreateColumn([this](ColumnModelNG model) {
        // step: set alignItems: HorizontalAlign.Start
        model.SetAlignItems(FlexAlign::FLEX_START);

        // step: set stack common attribute
        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));

        // step: create child nodes
        for (int32_t i = 0; i < 2; i++) {
            CreateColumn([this](ColumnModelNG model) {
                ViewAbstract::SetWidth(CalcLength(Dimension(50 / 100.0, DimensionUnit::PERCENT)));
                ViewAbstract::SetHeight(CalcLength(30.0f));
            });
        }
    });
    ASSERT_EQ(frameNode->GetChildren().size(), 2);
    CreateLayoutTask(frameNode);

    // expect: first column offset (x, y) = (0, 0)
    EXPECT_EQ(frameNode->GetChildByIndex(FIRST_CHILD)->GetGeometryNode()->GetFrameOffset().GetX(), 0.0f);
    EXPECT_EQ(frameNode->GetChildByIndex(FIRST_CHILD)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
    // expect: second column offset (x, y) = (0, 30)
    EXPECT_EQ(frameNode->GetChildByIndex(SECOND_CHILD)->GetGeometryNode()->GetFrameOffset().GetX(), 0.0f);
    EXPECT_EQ(frameNode->GetChildByIndex(SECOND_CHILD)->GetGeometryNode()->GetFrameOffset().GetY(), 30.0f);
}
} // namespace OHOS::Ace::NG