/*
* Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "compatible/components/clock/clock_declaration.h"

#include "base/log/event_report.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace {

using namespace Framework;

using ClockMap = std::unordered_map<std::string, void (*)(const std::string&, ClockDeclaration&)>;

const char DOM_HOURS_WEST[] = "hourswest";
const char DOM_SHOW_DIGIT[] = "showdigit";
const char DOM_DIGIT_FONT_FAMILY[] = "fontFamily";

// default value of clock
const std::shared_ptr<ClockAttribute> DEFAULT_CLOCK_ATTR = std::make_shared<ClockAttribute>();
const std::shared_ptr<ClockStyle> DEFAULT_CLOCK_STYLE = std::make_shared<ClockStyle>();
const std::shared_ptr<ClockEvent> DEFAULT_CLOCK_EVENT = std::make_shared<ClockEvent>();
void ClockDeclaration::InitSpecialized()
{
    AddSpecializedAttribute(DEFAULT_CLOCK_ATTR);
    AddSpecializedStyle(DEFAULT_CLOCK_STYLE);
    AddSpecializedEvent(DEFAULT_CLOCK_EVENT);
}

void ClockDeclaration::InitializeStyle()
{
    auto theme = GetTheme<ClockTheme>();
    if (!theme) {
        LOGE("ClockTheme is null!");
        EventReport::SendComponentException(ComponentExcepType::GET_THEME_ERR);
        return;
    }
    defaultSize_ = theme->GetDefaultSize();
}

bool ClockDeclaration::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    static const ClockMap clockAttrMap = {
        { DOM_HOURS_WEST,
            [](const std::string& val, ClockDeclaration& declaration) {
                auto& clockAttr = declaration.MaybeResetAttribute<ClockAttribute>(AttributeTag::SPECIALIZED_ATTR);
                if (clockAttr.IsValid()) {
                    clockAttr.hoursWest = StringToDouble(val);
                }
            } },
        { DOM_SHOW_DIGIT,
            [](const std::string& val, ClockDeclaration& declaration) {
                auto& clockAttr = declaration.MaybeResetAttribute<ClockAttribute>(AttributeTag::SPECIALIZED_ATTR);
                if (clockAttr.IsValid()) {
                    clockAttr.showDigit = StringToBool(val);
                }
            } },
    };
    auto clockAttrIter = clockAttrMap.find(attr.first);
    if (clockAttrIter != clockAttrMap.end()) {
        clockAttrIter->second(attr.second, *this);
        return true;
    }
    return false;
}

bool ClockDeclaration::SetSpecializedStyle(const std::pair<std::string, std::string>& style)
{
    if (style.first == DOM_DIGIT_FONT_FAMILY) {
        auto& clockStyle = MaybeResetStyle<ClockStyle>(StyleTag::SPECIALIZED_STYLE);
        if (clockStyle.IsValid()) {
            clockStyle.fontFamilies = ConvertStrToFontFamilies(style.second);
        }
        return true;
    }
    return false;
}

bool ClockDeclaration::SetSpecializedEvent(int32_t pageId, const std::string& eventId, const std::string& event)
{
    if (event == "hour") {
        auto& clockEvent = MaybeResetEvent<ClockEvent>(EventTag::SPECIALIZED_EVENT);
        if (clockEvent.IsValid()) {
            clockEvent.hourChangeEvent = EventMarker(eventId, event, pageId);
        }
        return true;
    }
    return false;
}

void ClockDeclaration::SetClockConfig(const ClockConfig& clockConfig)
{
    digitRadiusRatio_ = clockConfig.digitRadiusRatio_;
    digitSizeRatio_ = clockConfig.digitSizeRatio_;

    clockFaceSrc_ = ParseImageSrc(clockConfig.clockFaceSrc_);
    hourHandSrc_ = ParseImageSrc(clockConfig.hourHandSrc_);
    minuteHandSrc_ = ParseImageSrc(clockConfig.minuteHandSrc_);
    secondHandSrc_ = ParseImageSrc(clockConfig.secondHandSrc_);
    digitColor_ = ParseColor(clockConfig.digitColor_);

    clockFaceNightSrc_ = ParseImageSrc(clockConfig.clockFaceNightSrc_);
    hourHandNightSrc_ = ParseImageSrc(clockConfig.hourHandNightSrc_);
    minuteHandNightSrc_ = ParseImageSrc(clockConfig.minuteHandNightSrc_);
    secondHandNightSrc_ = ParseImageSrc(clockConfig.secondHandNightSrc_);
    digitColorNight_ = ParseColor(clockConfig.digitColorNight_);
}

} // namespace OHOS::Ace
