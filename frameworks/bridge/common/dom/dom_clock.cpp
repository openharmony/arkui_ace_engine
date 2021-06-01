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

#include "frameworks/bridge/common/dom/dom_clock.h"

#include "base/log/event_report.h"
#include "base/utils/linear_map.h"
#include "base/utils/utils.h"
#include "core/components/clock/clock_theme.h"
#include "frameworks/bridge/common/dom/dom_type.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {

DOMClock::DOMClock(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName)
{
    clockChild_ = AceType::MakeRefPtr<ClockComponent>();
}

bool DOMClock::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    // static linear map must be sorted by key.
    static const LinearMapNode<void (*)(const std::string&, DOMClock&)> clockAttrOperators[] = {
        { DOM_HOURS_WEST,
            [](const std::string& val, DOMClock& clock) { clock.clockChild_->SetHoursWest(StringToDouble(val)); } },
        { DOM_SHOW_DIGIT,
            [](const std::string& val, DOMClock& clock) { clock.clockChild_->SetShowDigit(StringToBool(val)); } },

    };
    auto operatorIter = BinarySearchFindIndex(clockAttrOperators, ArraySize(clockAttrOperators), attr.first.c_str());
    if (operatorIter != -1) {
        clockAttrOperators[operatorIter].value(attr.second, *this);
        return true;
    }
    return false;
}

bool DOMClock::SetSpecializedStyle(const std::pair<std::string, std::string>& style)
{
    // static linear map must be sorted by key.
    static const LinearMapNode<void (*)(const std::string&, DOMClock&)> clockStylesOperators[] = {
        { DOM_DIGIT_FONT_FAMILY,
            [](const std::string& val, DOMClock& clock) {
                clock.clockChild_->SetFontFamilies(ConvertStrToFontFamilies(val));
            } },
    };
    auto operatorIter =
        BinarySearchFindIndex(clockStylesOperators, ArraySize(clockStylesOperators), style.first.c_str());
    if (operatorIter != -1) {
        clockStylesOperators[operatorIter].value(style.second, *this);
        return true;
    }
    return false;
}

bool DOMClock::AddSpecializedEvent(int32_t pageId, const std::string& event)
{
    if (event == "hour") {
        onHourCallback_ = EventMarker(GetNodeIdForEvent(), event, pageId);
        clockChild_->SetOnHourChangeEvent(onHourCallback_);
        return true;
    }
    return false;
}

void DOMClock::PrepareSpecializedComponent()
{
    clockChild_->SetDigitRadiusRatio(clockConfig_.digitRadiusRatio_);
    clockChild_->SetDigitSizeRatio(clockConfig_.digitSizeRatio_);
    clockChild_->SetClockFaceSrc(clockConfig_.clockFaceSrc_);
    clockChild_->SetClockFaceNightSrc(clockConfig_.clockFaceNightSrc_);
    clockChild_->SetHourHandSrc(clockConfig_.hourHandSrc_);
    clockChild_->SetHourHandNightSrc(clockConfig_.hourHandNightSrc_);
    clockChild_->SetMinuteHandSrc(clockConfig_.minuteHandSrc_);
    clockChild_->SetMinuteHandNightSrc(clockConfig_.minuteHandNightSrc_);
    clockChild_->SetSecondHandSrc(clockConfig_.secondHandSrc_);
    clockChild_->SetSecondHandNightSrc(clockConfig_.secondHandNightSrc_);
    clockChild_->SetDigitColor(clockConfig_.digitColor_);
    clockChild_->SetDigitColorNight(clockConfig_.digitColorNight_);
}

void DOMClock::InitializeStyle()
{
    auto theme = GetTheme<ClockTheme>();
    if (!theme) {
        LOGE("ClockTheme is null!");
        EventReport::SendComponentException(ComponentExcepType::GET_THEME_ERR);
        return;
    }
    clockChild_->SetDefaultSize(theme->GetDefaultSize());
}

void DOMClock::ResetInitializedStyle()
{
    InitializeStyle();
}

} // namespace OHOS::Ace::Framework