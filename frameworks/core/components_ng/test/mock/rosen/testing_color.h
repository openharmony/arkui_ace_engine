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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_COLOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_COLOR_H

#include <cstdint>

namespace OHOS::Ace::Testing {
class TestingColor {
public:
    TestingColor(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha) {}
    explicit TestingColor(uint32_t rgba) {}
    ~TestingColor() = default;

    float GetAlphaF()
    {
        return 1.0f;
    }

    void SetAlphaF(float alpha) {}

    virtual void Color(uint32_t rgba) {}
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_COLOR_H