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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "base/utils/system_properties.h"
#include "base/utils/utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class SystemPropertiesTest : public testing::Test {};

/**
 * @tc.name: SystemPropertiesTest001
 * @tc.desc: Test InitDeviceInfo init
 * @tc.type: FUNC
 */
HWTEST_F(SystemPropertiesTest, SystemPropertiesTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call InitDeviceInfo
     * @tc.expected: step1. device param init success.
     */
    SystemProperties::InitDeviceInfo(1000, 2760, 0, 3.0, false);

    EXPECT_EQ(SystemProperties::deviceWidth_, 1000);
    EXPECT_EQ(SystemProperties::deviceHeight_, 2760);
    EXPECT_TRUE(NearEqual(SystemProperties::resolution_, 3.0));
    EXPECT_EQ(SystemProperties::screenShape_, ScreenShape::NOT_ROUND);
}

/**
 * @tc.name: ContainerTest002
 * @tc.desc: Test ReadSystemParametersCallOnce init only once
 * @tc.type: FUNC
 */
HWTEST_F(SystemPropertiesTest, SystemPropertiesTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call ReadSystemParametersCallOnce
     * @tc.expected: step1. developerModeOn_ init false.
     */
    SystemProperties::ReadSystemParametersCallOnce();
    EXPECT_EQ(SystemProperties::developerModeOn_, false);

    /**
     * @tc.steps: step2. set developerModeOn_ to true, call ReadSystemParametersCallOnce again.
     * @tc.expected: step2. developerModeOn_ init only once, it will not be set to false by ReadSystemParametersCallOnce
     */
    SystemProperties::developerModeOn_ = true;
    SystemProperties::ReadSystemParametersCallOnce();
    EXPECT_EQ(SystemProperties::developerModeOn_, true);
}

/**
 * @tc.name: SystemPropertiesTest003
 * @tc.desc: Test InitDeviceInfo init
 * @tc.type: FUNC
 */
HWTEST_F(SystemPropertiesTest, SystemPropertiesTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call get methods.
     * @tc.expected: step1. check default value is right.
     */
    EXPECT_EQ(SystemProperties::GetComponentLoadNumber(), 1);
    EXPECT_FALSE(SystemProperties::GetRecycleImageEnabled());
    EXPECT_TRUE(NearEqual(SystemProperties::GetAnimationScale(), 1.0f));
    EXPECT_TRUE(SystemProperties::GetContainerDeleteFlag());
    EXPECT_FALSE(SystemProperties::GetMultiInstanceEnabled());
    EXPECT_FALSE(SystemProperties::GetAllowWindowOpenMethodEnabled());
}

/**
 * @tc.name: SystemPropertiesTest004
 * @tc.desc: Test GetTransformEnabled init
 * @tc.type: FUNC
 */
HWTEST_F(SystemPropertiesTest, SystemPropertiesTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetTransformEnabled
     * @tc.expected: step1. getTransformEnabled param init success.
     */
    EXPECT_EQ(SystemProperties::GetTransformEnabled(), true);
}

/**
 * @tc.name: SystemPropertiesTest005
 * @tc.desc: Test GetStopCollectTimeWait returns default value when system parameter is not set
 * @tc.type: FUNC
 */
HWTEST_F(SystemPropertiesTest, SystemPropertiesTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetStopCollectTimeWait without setting system parameter
     * @tc.expected: step1. returns default value 800 milliseconds
     */
    constexpr int32_t DEFAULT_STOP_COLLECT_TIME_WAIT = 800;
    EXPECT_EQ(SystemProperties::GetStopCollectTimeWait(), DEFAULT_STOP_COLLECT_TIME_WAIT);
}

/**
 * @tc.name: SystemPropertiesTest006
 * @tc.desc: Test GetStopCollectTimeWait returns consistent value across multiple calls
 * @tc.type: FUNC
 */
HWTEST_F(SystemPropertiesTest, SystemPropertiesTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetStopCollectTimeWait multiple times
     * @tc.expected: step1. all calls return the same value due to static variable caching
     */
    constexpr int32_t DEFAULT_STOP_COLLECT_TIME_WAIT = 800;
    int32_t firstCall = SystemProperties::GetStopCollectTimeWait();
    int32_t secondCall = SystemProperties::GetStopCollectTimeWait();
    int32_t thirdCall = SystemProperties::GetStopCollectTimeWait();

    EXPECT_EQ(firstCall, DEFAULT_STOP_COLLECT_TIME_WAIT);
    EXPECT_EQ(secondCall, DEFAULT_STOP_COLLECT_TIME_WAIT);
    EXPECT_EQ(thirdCall, DEFAULT_STOP_COLLECT_TIME_WAIT);
    EXPECT_EQ(firstCall, secondCall);
    EXPECT_EQ(secondCall, thirdCall);
}

/**
 * @tc.name: SystemPropertiesTest007
 * @tc.desc: Test GetStopCollectTimeWait returns positive value for delayed task scheduling
 * @tc.type: FUNC
 */
HWTEST_F(SystemPropertiesTest, SystemPropertiesTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetStopCollectTimeWait
     * @tc.expected: step1. returns positive value suitable for PostDelayedTask delay parameter
     */
    int32_t stopCollectTimeWait = SystemProperties::GetStopCollectTimeWait();

    // Verify the value is positive (required for delayed task scheduling)
    EXPECT_GT(stopCollectTimeWait, 0);

    // Verify the value is reasonable (not too large, e.g., less than 1 minute)
    constexpr int32_t MAX_REASONABLE_DELAY_MS = 60000; // 60 seconds in milliseconds
    EXPECT_LT(stopCollectTimeWait, MAX_REASONABLE_DELAY_MS);
}
}
