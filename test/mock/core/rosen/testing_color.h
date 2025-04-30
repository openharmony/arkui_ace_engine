/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <algorithm>
#include <cstdint>
#include <string>

namespace OHOS::Ace::Testing {
namespace {
constexpr int32_t ZERO = 0;
constexpr int32_t EIGHT = 8;
constexpr int32_t SIXTEEN = 16;
constexpr int32_t TWENTY_FOUR = 24;
constexpr int32_t BIT_LENGTH = 8;
constexpr int32_t CALC_BIT_LENGTH = 4;
constexpr uint32_t COLOR_DEFAULT = 0xff;
constexpr char HEX[] = "0123456789ABCDEF";
} // namespace
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
    TestingColor(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha)
        : red_(red), green_(green), blue_(blue), alpha_(alpha)
    {}
    TestingColor(uint32_t rgba)
        : red_((rgba >> SIXTEEN) & COLOR_DEFAULT), green_((rgba >> EIGHT) & COLOR_DEFAULT),
          blue_((rgba >> ZERO) & COLOR_DEFAULT), alpha_(rgba >> TWENTY_FOUR)
    {}
    virtual ~TestingColor() = default;

    bool operator==(const TestingColor& rhs) const
    {
        return red_ == rhs.red_ && green_ == rhs.green_ && blue_ == rhs.blue_ && alpha_ == rhs.alpha_;
    }

    virtual float GetAlphaF()
    {
        return 1.0f;
    }

    uint32_t GetRed() const
    {
        return red_;
    }

    uint32_t GetGreen() const
    {
        return green_;
    }

    uint32_t GetBlue() const
    {
        return blue_;
    }

    void SetAlphaF(float alpha) {}

    virtual void Color(uint32_t rgba)
    {
        alpha_ = rgba >> TWENTY_FOUR;
        red_ = (rgba >> SIXTEEN) & 0xff;
        green_ = (rgba >> EIGHT) & 0xff;
        blue_ = (rgba >> ZERO) & 0xff;
    }

    uint32_t GetValue() const
    {
        return (static_cast<uint32_t>(std::clamp<int16_t>(blue_, 0, UINT8_MAX))) |
               (static_cast<uint32_t>((std::clamp<int16_t>(green_, 0, UINT8_MAX)) << 8)) |
               (static_cast<uint32_t>((std::clamp<int16_t>(red_, 0, UINT8_MAX)) << 16)) |
               (static_cast<uint32_t>((std::clamp<int16_t>(alpha_, 0, UINT8_MAX)) << 24));
    }

    std::string ColorToString() const
    {
        std::string colorStr;
        int count = 0;
        uint32_t value = GetValue();
        while (count++ < BIT_LENGTH) {
            colorStr = HEX[(value & 0xf)] + colorStr;
            value >>= CALC_BIT_LENGTH;
        }
        colorStr = "#" + colorStr;
        return colorStr;
    }

    uint32_t red_;
    uint32_t green_;
    uint32_t blue_;
    uint32_t alpha_;
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_COLOR_H
