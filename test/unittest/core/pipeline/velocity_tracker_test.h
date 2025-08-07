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

#ifndef TEST_UNITTEST_CORE_PIPELINE_VELOCITY_TRACKER_TEST_H
#define TEST_UNITTEST_CORE_PIPELINE_VELOCITY_TRACKER_TEST_H

#include <string>
#include <vector>
#include <utility>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/offset.h"
#include "base/geometry/ng/offset_t.h"
#include "core/common/ace_engine.h"
#include "core/event/ace_events.h"
#include "core/event/axis_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/common/event_manager.h"

#include "core/gestures/velocity_tracker.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float TO_TRUE_DATA = 8.0;
constexpr float TOUCH_STILL_THRESHOLD = 0.5;
constexpr int32_t RATIO_MS_TO_US = 1000;
constexpr int32_t RATIO_NS_TO_US = 1000;
} // namespace

class VelocityTrackerTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void VelocityTrackerTest::SetUpTestSuite() {}

void VelocityTrackerTest::TearDownTestSuite() {}

void VelocityTrackerTest::SetUp() {}

void VelocityTrackerTest::TearDown() {}

} // namespace OHOS::Ace::NG

#endif // TEST_UNITTEST_CORE_PIPELINE_VELOCITY_TRACKER_TEST_H