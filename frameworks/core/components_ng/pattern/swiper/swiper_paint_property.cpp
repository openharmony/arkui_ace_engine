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
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"

#include <unordered_map>

#include "base/utils/string_utils.h"

namespace OHOS::Ace::NG {
const int32_t SwiperAnimationStyle::DEFAULT_INTERVAL = 3000;
const int32_t SwiperAnimationStyle::DEFAULT_DURATION = 400;

void SwiperPaintProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    PaintProperty::ToJsonValue(json);

    json->Put("autoPlay", GetAutoPlay().value_or(false) ? "true" : "false");
    json->Put(
        "interval", std::to_string(GetAutoPlayInterval().value_or(SwiperAnimationStyle::DEFAULT_INTERVAL)).c_str());
    json->Put("loop", GetLoop().value_or(true) ? "true" : "false");
    json->Put("duration", std::to_string(GetDuration().value_or(SwiperAnimationStyle::DEFAULT_DURATION)).c_str());
    json->Put("disableSwipe", GetDisableSwipe().value_or(false) ? "true" : "false");
    static const char* EDGE_EFFECT[] = { "EdgeEffect.Spring", "EdgeEffect.Fade", "EdgeEffect.None" };
    json->Put("effectMode", EDGE_EFFECT[static_cast<int32_t>(GetEdgeEffect().value_or(EdgeEffect::SPRING))]);
    json->Put("curve",
        GetCurve().has_value() ? Curves::ToString(GetCurve().value()).c_str() : Curves::DEFAULT_CURVE_NAME.c_str());
}

void SwiperPaintProperty::FromJson(const std::unique_ptr<JsonValue>& json)
{
    UpdateAutoPlay(json->GetBool("autoPlay"));
    UpdateAutoPlayInterval(StringUtils::StringToInt(json->GetString("interval")));
    UpdateLoop(json->GetBool("loop"));
    UpdateDuration(StringUtils::StringToInt(json->GetString("duration")));
    UpdateDisableSwipe(json->GetBool("disableSwipe"));
    static const std::unordered_map<std::string, EdgeEffect> uMap {
        { "EdgeEffect.Spring", EdgeEffect::SPRING },
        { "EdgeEffect.Fade", EdgeEffect::FADE },
        { "EdgeEffect.None", EdgeEffect::NONE },
    };
    auto effectMode = json->GetString("effectMode");
    UpdateEdgeEffect(uMap.count(effectMode) ? uMap.at(effectMode) : EdgeEffect::SPRING);
    PaintProperty::FromJson(json);
}
} // namespace OHOS::Ace::NG