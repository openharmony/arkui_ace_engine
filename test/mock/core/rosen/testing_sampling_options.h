/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_SAMPLING_OPTIONS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_SAMPLING_OPTIONS_H

namespace OHOS::Ace::Testing {
enum class FilterMode {
    NEAREST,
    LINEAR,
};

enum class MipmapMode {
    NONE,
    NEAREST,
    LINEAR,
};

struct TestingCubicResampler {
    float cubicCoffB = 0;
    float cubicCoffC = 0;
    static constexpr TestingCubicResampler Mitchell()
    {
        return { 1 / 3.0f, 1 / 3.0f };
    }
    static constexpr TestingCubicResampler CatmullRom()
    {
        return { 0.0f, 1 / 2.0f };
    }
};

class TestingSamplingOptions {
public:
    TestingSamplingOptions() = default;
    TestingSamplingOptions(FilterMode fm, MipmapMode mm) {}
    TestingSamplingOptions(const TestingCubicResampler& c) {}
    ~TestingSamplingOptions() = default;
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_SAMPLING_OPTIONS_H
