/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/stepper/stepper_item_layout_property.h"
#include "core/components_ng/pattern/stepper/stepper_item_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string LEFT_LABEL = "Previous";
const std::string RIGHT_LABEL = "Next";
const std::string LABEL_STATUS = "normal";
} // namespace

struct TestProperty {
    std::optional<std::string> leftLabelValue = std::nullopt;
    std::optional<std::string> rightLabelValue = std::nullopt;
    std::optional<std::string> labelStatusValue = std::nullopt;
};

class StepperItemPatternTestNg : public testing::Test {
public:
protected:
    static RefPtr<FrameNode> CreateStepperItemNode(TestProperty& testProperty);
};

RefPtr<FrameNode> StepperItemPatternTestNg::CreateStepperItemNode(TestProperty& testProperty)
{
    StepperItemModelNG().Create();
    if (testProperty.labelStatusValue.has_value()) {
        StepperItemModelNG().SetStatus(testProperty.labelStatusValue.value());
    }
    if (testProperty.leftLabelValue.has_value()) {
        StepperItemModelNG().SetPrevLabel(testProperty.leftLabelValue.value());
    }
    if (testProperty.rightLabelValue.has_value()) {
        StepperItemModelNG().SetNextLabel(testProperty.rightLabelValue.value());
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // TextView pop
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: StepperItemFrameNodeCreator001
 * @tc.desc: Test all the properties of StepperItem.
 * @tc.type: FUNC
 */
HWTEST_F(StepperItemPatternTestNg, StepperFrameNodeCreator001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.leftLabelValue = LEFT_LABEL;
    testProperty.rightLabelValue = RIGHT_LABEL;
    testProperty.labelStatusValue = LABEL_STATUS;

    RefPtr<FrameNode> frameNode = CreateStepperItemNode(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<StepperItemLayoutProperty> layoutProperty = frameNode->GetLayoutProperty<StepperItemLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetLeftLabelValue(), LEFT_LABEL);
    EXPECT_EQ(layoutProperty->GetRightLabelValue(), RIGHT_LABEL);
    EXPECT_EQ(layoutProperty->GetLabelStatus(), LABEL_STATUS);
}
} // namespace OHOS::Ace::NG