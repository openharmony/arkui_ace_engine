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

#include "core/components_ng/pattern/badge/badge_layout_property.h"

namespace OHOS::Ace::NG {

namespace {

const int DEFAULT_COUNT = 0;
const int DEFAULT_MAX_COUNT = 99;
const Color DEFAULT_TEXT_COLOR = Color::WHITE;
const Color DEFAULT_BADGE_COLOR = Color::RED;
const Dimension DEFAULT_FONT_SIZE = 10.0_vp;
const Dimension DEFAULT_CIRCLE_SIZE = 16.0_vp;

} // namespace

void BadgeLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    LayoutProperty::ToJsonValue(json);
    json->Put("count", std::to_string(GetBadgeCount().value_or(DEFAULT_COUNT)).c_str());
    json->Put("maxCount", std::to_string(GetBadgeMaxCount().value_or(DEFAULT_MAX_COUNT)).c_str());
    auto position = BadgeLayoutProperty::GetBadgePosition();
    json->Put("position", GetBadgePositionString(position).c_str());
    json->Put("value", GetBadgeValue().value_or("").c_str());

    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("color", GetBadgeTextColor().value_or(DEFAULT_TEXT_COLOR).ColorToString().c_str());
    jsonValue->Put("fontSize", GetBadgeFontSize().value_or(DEFAULT_FONT_SIZE).ToString().c_str());
    jsonValue->Put("badgeColor", GetBadgeColor().value_or(DEFAULT_BADGE_COLOR).ColorToString().c_str());
    jsonValue->Put("badgeSize", GetBadgeCircleSize().value_or(DEFAULT_CIRCLE_SIZE).ToString().c_str());
    json->Put("style", jsonValue->ToString().c_str());
}

} // namespace OHOS::Ace::NG
