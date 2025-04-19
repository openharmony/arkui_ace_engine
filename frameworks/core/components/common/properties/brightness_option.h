/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BRIGHTNESS_OPTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BRIGHTNESS_OPTION_H

#include <vector>

#include "base/json/json_util.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {

struct BrightnessOption {
    double rate { 1.0f };
    double lightUpDegree { 0.0f };
    double cubicCoeff { 0.0f };
    double quadCoeff { 0.0f };
    double saturation { 1.0f };
    std::vector<float> posRGB = { 0.0f, 0.0f, 0.0f };
    std::vector<float> negRGB = { 0.0f, 0.0f, 0.0f };
    double fraction { 1.0f };
    bool operator==(const BrightnessOption& other) const
    {
        return NearEqual(rate, other.rate) && NearEqual(lightUpDegree, other.lightUpDegree) &&
               NearEqual(cubicCoeff, other.cubicCoeff) && NearEqual(quadCoeff, other.quadCoeff) &&
               NearEqual(saturation, other.saturation) && posRGB == other.posRGB && negRGB == other.negRGB &&
               NearEqual(fraction, other.fraction);
    }
    std::unique_ptr<JsonValue> GetJsonObject() const;
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const NG::InspectorFilter& filter, std::string key) const;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BRIGHTNESS_OPTION_H
