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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_RECORDING_PATH_EFFECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_RECORDING_PATH_EFFECT_H

#include "testing_path_effect.h"
namespace OHOS::Ace::Testing {
class TestingRecordingPathEffect {
public:
    TestingRecordingPathEffect() = default;
    ~TestingRecordingPathEffect() = default;
    static std::shared_ptr<TestingPathEffect> CreatePathDashEffect(
        const TestingPath& path, float advance, float phase, TestingPathDashStyle style)
    {
        return std::make_shared<TestingPathEffect>();
    }
    static std::shared_ptr<TestingPathEffect> CreateDashPathEffect(const float intervals[], int count, float phase)
    {
        return std::make_shared<TestingPathEffect>();
    }
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_RECORDING_PATH_EFFECT_H