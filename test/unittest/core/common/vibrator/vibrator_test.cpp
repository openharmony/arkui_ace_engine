/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "base/utils/utils.h"
#define protected public
#define private public
#include "core/common/vibrator/vibrator.h"
#include "core/common/vibrator/vibrator_interface.h"
#include "core/common/vibrator/vibrator_proxy.h"
#undef private
#undef protected
#include "mock_vibrator.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class VibratorTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: CastToVibratorTest001
 * @tc.desc: Test cast to VibratorTest
 * @tc.type: FUNC
 */
HWTEST_F(VibratorTest, CastToDebugTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback SetDelegate
     */
    VibratorProxy vibratorProxy;
    vibratorProxy.SetDelegate(nullptr);

    /**
     * @tc.steps: step2. build a object to GetVibrator
     * @tc.expected: step2. expect The return nullptr is same with vibrator.
     **/
    RefPtr<TaskExecutor> taskExecutor;
    RefPtr<Vibrator> vibrator = vibratorProxy.GetVibrator(taskExecutor);
    EXPECT_EQ(vibrator, nullptr);

    /**
     * @tc.steps: step3. build a object to GetVibrator
     * @tc.expected: step3. expect The return 1 is same with vibrator.
     **/
    auto mockVibratorProxy = std::make_unique<MockVibratorProxy>();
    EXPECT_CALL(*mockVibratorProxy, GetVibrator(_)).WillOnce(Return(nullptr));
    vibratorProxy.SetDelegate(std::move(mockVibratorProxy));
    RefPtr<Vibrator> vibrator1 = vibratorProxy.GetVibrator(taskExecutor);
    EXPECT_EQ(vibrator, nullptr);
}
} // namespace OHOS::Ace
