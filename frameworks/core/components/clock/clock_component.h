/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CLOCK_CLOCK_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CLOCK_CLOCK_COMPONENT_H

#include "core/components/clock/clock_element.h"
#include "core/components/clock/render_clock.h"

namespace OHOS::Ace {

class ClockComponent : public ComponentGroup {
    DECLARE_ACE_TYPE(ClockComponent, ComponentGroup);

public:
    ClockComponent() = default;
    ~ClockComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override
    {
        return RenderClock::Create();
    }

    RefPtr<Element> CreateElement() override
    {
        return AceType::MakeRefPtr<ClockElement>();
    }

    void SetClockFaceSrc(const std::string& clockFaceSrc)
    {
        clockFaceSrc_ = clockFaceSrc;
    }

    const std::string& GetClockFaceSrc() const
    {
        return clockFaceSrc_;
    }

    void SetClockFaceNightSrc(const std::string& clockFaceNightSrc)
    {
        clockFaceNightSrc_ = clockFaceNightSrc;
    }

    const std::string& GetClockFaceNightSrc() const
    {
        return clockFaceNightSrc_;
    }

    void SetHourHandSrc(const std::string& hourHandSrc)
    {
        hourHandSrc_ = hourHandSrc;
    }

    const std::string& GetHourHandSrc() const
    {
        return hourHandSrc_;
    }

    void SetHourHandNightSrc(const std::string& hourHandNightSrc)
    {
        hourHandNightSrc_ = hourHandNightSrc;
    }

    const std::string& GetHourHandNightSrc() const
    {
        return hourHandNightSrc_;
    }

    void SetMinuteHandSrc(const std::string& minuteHandSrc)
    {
        minuteHandSrc_ = minuteHandSrc;
    }

    const std::string& GetMinuteHandSrc() const
    {
        return minuteHandSrc_;
    }

    void SetMinuteHandNightSrc(const std::string& minuteHandNightSrc)
    {
        minuteHandNightSrc_ = minuteHandNightSrc;
    }

    const std::string& GetMinuteHandNightSrc() const
    {
        return minuteHandNightSrc_;
    }

    void SetSecondHandSrc(const std::string& secondHandSrc)
    {
        secondHandSrc_ = secondHandSrc;
    }

    const std::string& GetSecondHandSrc() const
    {
        return secondHandSrc_;
    }

    void SetSecondHandNightSrc(const std::string& secondHandNightSrc)
    {
        secondHandNightSrc_ = secondHandNightSrc;
    }

    const std::string& GetSecondHandNightSrc() const
    {
        return secondHandNightSrc_;
    }

    void SetHoursWest(double hoursWest)
    {
        hoursWest_ = hoursWest;
    }

    double GetHoursWest() const
    {
        return hoursWest_;
    }

    void SetDigitColor(const Color& digitColor)
    {
        digitColor_ = digitColor;
    }

    const Color& GetDigitColor() const
    {
        return digitColor_;
    }

    void SetDigitColorNight(const Color& digitColorNight)
    {
        digitColorNight_ = digitColorNight;
    }

    const Color& GetDigitColorNight() const
    {
        return digitColorNight_;
    }

    void SetDefaultSize(const Dimension& defaultSize)
    {
        defaultSize_ = defaultSize;
    }

    const Dimension& GetDefaultSize() const
    {
        return defaultSize_;
    }

    void SetDigitSizeRatio(double digitSizeRatio)
    {
        digitSizeRatio_ = digitSizeRatio;
    }

    double GetDigitSizeRatio() const
    {
        return digitSizeRatio_;
    }

    void SetDigitRadiusRatio(double digitRadiusRatio)
    {
        digitRadiusRatio_ = digitRadiusRatio;
    }

    double GetDigitRadiusRatio() const
    {
        return digitRadiusRatio_;
    }

    const std::vector<std::string>& GetFontFamilies() const
    {
        return fontFamilies_;
    }

    void SetFontFamilies(const std::vector<std::string>& fontFamilies)
    {
        fontFamilies_ = fontFamilies;
    }

    bool GetShowDigit() const
    {
        return showDigit_;
    }

    void SetShowDigit(bool showDigit)
    {
        showDigit_ = showDigit;
    }

    void SetOnHourChangeEvent(const EventMarker& onHourChangeEvent)
    {
        onHourCallback_ = onHourChangeEvent;
    }

    const EventMarker& GetOnHourChangeEvent() const
    {
        return onHourCallback_;
    }

private:
    std::string clockFaceSrc_;
    std::string hourHandSrc_;
    std::string minuteHandSrc_;
    std::string secondHandSrc_;
    std::string clockFaceNightSrc_;
    std::string hourHandNightSrc_;
    std::string minuteHandNightSrc_;
    std::string secondHandNightSrc_;
    // hours west of Greenwich, for e.g., [hoursWest] is [-8] in  GMT+8.
    // Valid range of [hoursWest] is [-12, 14]. Set default value to DBL_MAX to use current time zone by default.
    double hoursWest_ = DBL_MAX;
    Color digitColor_;
    Color digitColorNight_;
    Dimension defaultSize_;
    // ratio of digit-radius and half of side length of clock-face-image.
    // digit-radius is used to calculate digit offset.
    // e.g., when size of clock-face-image is 200 x 200, digit "3" is [200 / 2 x 0.7 = 70] right of the center.
    double digitRadiusRatio_ = 0.7;
    // ratio of digit-size and side length of clock-face-image, which is used to decide font-size of digit.
    // e.g., when size of clock-face-image is 200 x 200, font-size of digit is 200 x 0.08 = 16
    double digitSizeRatio_ = 0.08;
    std::vector<std::string> fontFamilies_;
    bool showDigit_ = true;
    EventMarker onHourCallback_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CLOCK_CLOCK_COMPONENT_H
