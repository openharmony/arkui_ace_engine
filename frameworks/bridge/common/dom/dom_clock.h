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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_CLOCK_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_CLOCK_H

#include "core/components/clock/clock_component.h"
#include "frameworks/bridge/common/dom/dom_node.h"

namespace OHOS::Ace::Framework {

struct ClockConfig final {
    // ratio of digit-radius and half of side length of clock-face-image.
    // digit-radius is used to calculate digit offset.
    // e.g., when size of clock-face-image is 200 x 200, digit "3" is [200 / 2 x 0.7 = 70] right of the center.
    double digitRadiusRatio_ = 0.7;
    // ratio of digit-size and side length of clock-face-image, which is used to decide font-size of digit.
    // e.g., when size of clock-face-image is 200 x 200, font-size of digit is 200 x 0.08 = 16
    double digitSizeRatio_ = 0.08;

    // image sources and color for day
    std::string clockFaceSrc_;
    std::string hourHandSrc_;
    std::string minuteHandSrc_;
    std::string secondHandSrc_;
    Color digitColor_;

    // image sources and color for night
    std::string clockFaceNightSrc_;
    std::string hourHandNightSrc_;
    std::string minuteHandNightSrc_;
    std::string secondHandNightSrc_;
    Color digitColorNight_ = Color::TRANSPARENT;
};

class DOMClock final : public DOMNode {
    DECLARE_ACE_TYPE(DOMClock, DOMNode);

public:
    DOMClock(NodeId nodeId, const std::string& nodeName);
    ~DOMClock() override = default;

    RefPtr<Component> GetSpecializedComponent() override
    {
        return clockChild_;
    }
    void ResetInitializedStyle() override;
    void InitializeStyle() override;
    void SetClockConfig(const ClockConfig& clockConfig)
    {
        clockConfig_ = clockConfig;
    }

protected:
    bool SetSpecializedAttr(const std::pair<std::string, std::string>& attr) override;
    bool SetSpecializedStyle(const std::pair<std::string, std::string>& style) override;
    bool AddSpecializedEvent(int32_t pageId, const std::string& event) override;
    void PrepareSpecializedComponent() override;

    bool IsSubscriptEnable() const override
    {
        return true;
    }

private:
    RefPtr<ClockComponent> clockChild_;
    ClockConfig clockConfig_;
    EventMarker onHourCallback_;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_CLOCK_H
