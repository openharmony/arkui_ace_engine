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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_TEST_UNITTEST_VIBRATOR_MOCK_VIBRATOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_TEST_UNITTEST_VIBRATOR_MOCK_VIBRATOR_H
#include "gmock/gmock.h"
#include "core/common/vibrator/vibrator.h"
#include "core/common/vibrator/vibrator_interface.h"

namespace OHOS::Ace {
class MockVibrator : public Vibrator {
    DECLARE_ACE_TYPE(MockVibrator, Vibrator);
public:
    ~MockVibrator() override = default;

    MOCK_METHOD(void, Vibrate, (int32_t duration), (override));
    MOCK_METHOD(void, Vibrate, (const std::string& effectId), (override));
};

class MockVibratorProxy : public Singleton<VibratorProxy>, public VibratorInterface {
public:
    ~MockVibratorProxy() = default;
    static RefPtr<MockVibratorProxy> GetCurrent();

    MOCK_METHOD(RefPtr<Vibrator>, GetVibrator, (const RefPtr<TaskExecutor>& taskExecutor), (override));
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_TEST_UNITTEST_VIBRATOR_MOCK_VIBRATOR_H
