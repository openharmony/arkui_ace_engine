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
}
