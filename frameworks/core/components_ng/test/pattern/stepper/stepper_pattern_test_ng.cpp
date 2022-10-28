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

#include <cstddef>
#include <optional>
#include <string>
#include <utility>

#include "gtest/gtest.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/stepper/stepper_event_hub.h"
#include "core/components_ng/pattern/stepper/stepper_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const std::string FINISH_EVENT_NAME = "FINISH_EVENT";
const std::string SKIP_EVENT_NAME = "SKIP_EVENT";
const std::string CHANGE_EVENT_NAME = "CHANGE_EVENT";
const std::string NEXT_EVENT_NAME = "NEXT_EVENT";
const std::string PREVIOUS_EVENT_NAME = "PREVIOUS_EVENT";
const uint32_t INDEX = 0;
} // namespace

struct TestProperty {
    StepperModel::RoutineCallbackEvent finishEvent = nullptr;
    StepperModel::RoutineCallbackEvent skipEvent = nullptr;
    StepperModel::IndexCallbackEvent changeEvent = nullptr;
    StepperModel::IndexCallbackEvent nextEvent = nullptr;
    StepperModel::IndexCallbackEvent previousEvent = nullptr;
};

class StepperPatternTestNg : public testing::Test {
public:
protected:
    static RefPtr<FrameNode> CreateTextNode(uint32_t index, TestProperty& testProperty);
};

RefPtr<FrameNode> StepperPatternTestNg::CreateTextNode(uint32_t index, TestProperty& testProperty)
{
    StepperModelNG stepperMode;
    stepperMode.Create(index);
    if (testProperty.changeEvent != nullptr) {
        stepperMode.SetOnChange(std::move(testProperty.changeEvent));
    }
    if (testProperty.finishEvent != nullptr) {
        stepperMode.SetOnFinish(std::move(testProperty.finishEvent));
    }
    if (testProperty.nextEvent != nullptr) {
        stepperMode.SetOnNext(std::move(testProperty.nextEvent));
    }
    if (testProperty.previousEvent != nullptr) {
        stepperMode.SetOnPrevious(std::move(testProperty.previousEvent));
    }
    if (testProperty.skipEvent != nullptr) {
        stepperMode.SetOnSkip(std::move(testProperty.skipEvent));
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // stepper pop
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: StepperFrameNodeCreator001
 * @tc.desc: Test all the event of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperPatternTestNg, StepperFrameNodeCreator001, TestSize.Level1)
{
    TestProperty testProperty;
    std::string eventName;
    int32_t eventParameterA = -1;
    int32_t eventParameterB = -1;
    testProperty.finishEvent = [&eventName]() { eventName = FINISH_EVENT_NAME; };
    testProperty.skipEvent = [&eventName]() { eventName = SKIP_EVENT_NAME; };
    testProperty.changeEvent = [&eventName, &eventParameterA, &eventParameterB](int32_t a, int32_t b) {
        eventName = CHANGE_EVENT_NAME;
        eventParameterA = a;
        eventParameterB = b;
    };
    testProperty.nextEvent = [&eventName, &eventParameterA, &eventParameterB](int32_t a, int32_t b) {
        eventName = NEXT_EVENT_NAME;
        eventParameterA = a;
        eventParameterB = b;
    };
    testProperty.previousEvent = [&eventName, &eventParameterA, &eventParameterB](int32_t a, int32_t b) {
        eventName = PREVIOUS_EVENT_NAME;
        eventParameterA = a;
        eventParameterB = b;
    };

    RefPtr<FrameNode> frameNode = CreateTextNode(INDEX, testProperty);
    EXPECT_EQ(frameNode == nullptr, false);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    EXPECT_EQ(eventHub == nullptr, false);
    eventHub->FireFinishEvent();
    EXPECT_EQ(eventName, FINISH_EVENT_NAME);
    eventHub->FireSkipEvent();
    EXPECT_EQ(eventName, SKIP_EVENT_NAME);
    eventHub->FireChangeEvent(1, 2);
    EXPECT_EQ(eventName, CHANGE_EVENT_NAME);
    EXPECT_EQ(eventParameterA, 1);
    EXPECT_EQ(eventParameterB, 2);
    eventHub->FireNextEvent(2, 3);
    EXPECT_EQ(eventName, NEXT_EVENT_NAME);
    EXPECT_EQ(eventParameterA, 2);
    EXPECT_EQ(eventParameterB, 3);
    eventHub->FirePreviousEvent(3, 4);
    EXPECT_EQ(eventName, PREVIOUS_EVENT_NAME);
    EXPECT_EQ(eventParameterA, 3);
    EXPECT_EQ(eventParameterB, 4);
}

} // namespace OHOS::Ace::NG