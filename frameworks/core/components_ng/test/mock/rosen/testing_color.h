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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_COLOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_COLOR_H

#include <cstdint>

namespace OHOS::Ace::Testing {
class TestingColor {
public:
    constexpr static uint32_t COLOR_TRANSPARENT = 0;
    constexpr static uint32_t COLOR_BLACK = 0xFF000000;
    constexpr static uint32_t COLOR_DKGRAY = 0xFF444444;
    constexpr static uint32_t COLOR_GRAY = 0xFF888888;
    constexpr static uint32_t COLOR_LTGRAY = 0xFFCCCCCC;
    constexpr static uint32_t COLOR_WHITE = 0xFFFFFFFF;
    constexpr static uint32_t COLOR_RED = 0xFFFF0000;
    constexpr static uint32_t COLOR_GREEN = 0xFF00FF00;
    constexpr static uint32_t COLOR_BLUE = 0xFF0000FF;
    constexpr static uint32_t COLOR_YELLOW = 0xFFFFFF00;
    constexpr static uint32_t COLOR_CYAN = 0xFF00FFFF;
    constexpr static uint32_t COLOR_MAGENTA = 0xFFFF00FF;

    TestingColor() = default;
    TestingColor(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha) {}
    explicit TestingColor(uint32_t rgba) {}
    virtual ~TestingColor() = default;

    float GetAlphaF()
    {
        return 1.0f;
    }

    void SetAlphaF(float alpha) {}

    virtual void Color(uint32_t rgba) {}
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_COLOR_H
