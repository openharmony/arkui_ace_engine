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
#include <cstddef>

#include "stack_base_test_ng.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/animation/geometry_transition.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
const int32_t FIRST_CHILD = 0;
const int32_t SECOND_CHILD = 1;
} // namespace
class StackNewTestNG : public StackBaseTestNG {};

/**
 * @tc.name: Example
 * @tc.desc: Show an example of creating a test case.
 * @tc.type: ETS
 */
HWTEST_F(StackNewTestNG, Example, TestSize.Level1)
{
    // If this test is related to api versions, need to SetMinPlatformVersion
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(12);
    /**
    corresponding ets code:

    Stack({ alignContent: Alignment.Bottom }) {
      Text('First child, show in bottom')
       .width('90%')
       .height('100%')
       .backgroundColor(0xd2cab3)
       .align(Alignment.Top)
      Text('Second child, show in top')
       .width('70%')
       .height('60%')
       .backgroundColor(0xc1cbac)
       .align(Alignment.Top)
    }
     .width('300px')
     .height('300px')
    */
    auto frameNode = CreateStack([this](StackModelNG model) {
        // step: set alignContent: Alignment.Bottom
        ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, Alignment::BOTTOM_CENTER);

        // step: set stack common attribute
        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));

        // step: create child nodes
        auto textBottom = CreateText("First child, show in bottom", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(Dimension(90 / 100.0, DimensionUnit::PERCENT)));
            ViewAbstract::SetHeight(CalcLength(Dimension(100 / 100.0, DimensionUnit::PERCENT)));
            ViewAbstract::SetInspectorId("bottom");
        });
        auto textTop = CreateText("Second child, show in top", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(Dimension(70 / 100.0, DimensionUnit::PERCENT)));
            ViewAbstract::SetHeight(CalcLength(Dimension(60 / 100.0, DimensionUnit::PERCENT)));
            ViewAbstract::SetInspectorId("top");
        });
    });
    ASSERT_EQ(frameNode->GetChildren().size(), 2);
    CreateLayoutTask(frameNode);

    // expect: the second created node is the second child node
    auto second = OHOS::Ace::AceType::DynamicCast<OHOS::Ace::NG::FrameNode>(frameNode->GetChildByIndex(SECOND_CHILD));
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(second->GetInspectorId(), "top");
    // expect: textBottom offset = (x, y) = (300px*(1-0.9)/2, 0) = (15px, 0)
    EXPECT_EQ(frameNode->GetChildByIndex(FIRST_CHILD)->GetGeometryNode()->GetFrameOffset().GetX(), 15.0f);
    EXPECT_EQ(frameNode->GetChildByIndex(FIRST_CHILD)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
    // expect: textTop offset = (x, y) = (300px*0.3/2, 300px*(1-0.6)) = (45px, 120px)
    EXPECT_EQ(frameNode->GetChildByIndex(SECOND_CHILD)->GetGeometryNode()->GetFrameOffset().GetX(), 45.0f);
    EXPECT_EQ(frameNode->GetChildByIndex(SECOND_CHILD)->GetGeometryNode()->GetFrameOffset().GetY(), 120.0f);
}
} // namespace OHOS::Ace::NG