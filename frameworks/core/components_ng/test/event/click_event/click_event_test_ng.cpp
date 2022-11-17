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

#include "core/components_ng/event/click_event.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double GESTURE_EVENT_PROPERTY_VALUE = 10.0;
} // namespace

class ClickEventTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void ClickEventTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "ClickEventTestNg SetUpTestCase";
}

void ClickEventTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "ClickEventTestNg TearDownTestCase";
}

void ClickEventTestNg::SetUp()
{
    GTEST_LOG_(INFO) << "ClickEventTestNg SetUp";
}

void ClickEventTestNg::TearDown()
{
    GTEST_LOG_(INFO) << "ClickEventTestNg TearDown";
}

/**
 * @tc.name: ClickEventTest001
 * @tc.desc: Create ClickEvent and execute its functions.
 * @tc.type: FUNC
 */
HWTEST_F(ClickEventTestNg, ClickEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventFunc as the arguments of the construction of ClickEvent.
     * @tc.expected: clickEvent is not nullptr.
     */
    double unknownPropertyValue = 0.0;
    GestureEventFunc callback = [&unknownPropertyValue](GestureEvent& info) { unknownPropertyValue = info.GetScale(); };
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(callback));
    EXPECT_FALSE(clickEvent == nullptr);

    /**
     * @tc.steps: step2. Get callback function and execute.
     * @tc.expected: Execute ActionUpdateEvent which unknownPropertyValue is assigned in.
     */
    GestureEvent info = GestureEvent();
    info.SetScale(GESTURE_EVENT_PROPERTY_VALUE);
    clickEvent->GetGestureEventFunc()(info);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
}
} // namespace OHOS::Ace::NG
