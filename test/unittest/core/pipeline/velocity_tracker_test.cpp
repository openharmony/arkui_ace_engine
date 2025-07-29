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

#include "test/unittest/core/pipeline/velocity_tracker_test.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

/**
 * @tc.name: flagShipLowSpeedDatas
 * @tc.desc: Test UpdateVelocity
 * @tc.type: FUNC
 */
HWTEST_F(VelocityTrackerTest, flagShipLowSpeedDatas, TestSize.Level1)
{
    SystemProperties::velocityTrackerPointNumber_ = 5;
    SystemProperties::isVelocityWithinTimeWindow_ = false;
    SystemProperties::isVelocityWithoutUpPoint_ = false;
    VelocityTracker velocityTracker;
    for (auto cnt = 0; cnt < flagShipLowSpeedDatas.size(); ++cnt) {
        velocityTracker.Reset();
        for (auto i = 0; i < flagShipLowSpeedDatas[cnt].size(); ++i) {
            std::vector<int32_t> point = flagShipLowSpeedDatas[cnt][i];
            std::chrono::microseconds microseconds(point[0] * RATIO_MS_TO_US);
            TimeStamp timeStamp(microseconds);
            TouchEvent touchEvent;
            touchEvent.x = point[1] / TO_TRUE_DATA;
            touchEvent.y = point[2] / TO_TRUE_DATA;
            touchEvent.time = timeStamp;
            float range = TOUCH_STILL_THRESHOLD;
            bool end = false;
            if (i == flagShipLowSpeedDatas[cnt].size() - 1)
                end = true;
            velocityTracker.UpdateTouchPoint(touchEvent, end, range);
        }
        velocityTracker.UpdateVelocity();
    }
    EXPECT_NE(velocityTracker.velocity_.GetVelocityX(), 0.0);
}

/**
 * @tc.name: justPanDatas
 * @tc.desc: Test UpdateVelocity
 * @tc.type: FUNC
 */
HWTEST_F(VelocityTrackerTest, justPanDatas, TestSize.Level1)
{
    SystemProperties::velocityTrackerPointNumber_ = 20;
    SystemProperties::isVelocityWithinTimeWindow_ = true;
    SystemProperties::isVelocityWithoutUpPoint_ = true;
    VelocityTracker velocityTracker;
    for (auto cnt = 0; cnt < justPanDatas.size(); ++cnt) {
        velocityTracker.Reset();
        for (auto i = 0; i < justPanDatas[cnt].size(); ++i) {
            std::vector<float> point = justPanDatas[cnt][i];
            std::chrono::microseconds microseconds(static_cast<int64_t>(point[0] / RATIO_NS_TO_US));
            TimeStamp timeStamp(microseconds);
            TouchEvent touchEvent;
            touchEvent.x = point[1];
            touchEvent.y = point[2];
            touchEvent.time = timeStamp;
            float range = TOUCH_STILL_THRESHOLD;
            bool end = false;
            if (i == justPanDatas[cnt].size() - 1)
                end = true;
            velocityTracker.UpdateTouchPoint(touchEvent, end, range);
        }
        velocityTracker.UpdateVelocity();
    }
    EXPECT_NE(velocityTracker.velocity_.GetVelocityX(), 0.0);
}
} // namespace OHOS::Ace::NG
