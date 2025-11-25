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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_NG_TRANSITION_PROPERTY_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_NG_TRANSITION_PROPERTY_H

#include "ui/base/geometry/calc_dimension.h"
#include "ui/resource/resource_object.h"

namespace OHOS::Ace::NG {

struct TranslateOptions {
    CalcDimension x;
    CalcDimension y;
    CalcDimension z;
    struct resourceUpdater {
        RefPtr<ResourceObject> resObj;
        std::function<void(const RefPtr<ResourceObject>&, NG::TranslateOptions&)> updateFunc;
    };
    std::unordered_map<std::string, resourceUpdater> resMap_;

    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, NG::TranslateOptions&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        resMap_[key] = {resObj, std::move(updateFunc)};
    }

    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : resMap_) {
            resourceUpdater.updateFunc(resourceUpdater.resObj, *this);
        }
    }

    TranslateOptions() = default;
    TranslateOptions(const CalcDimension& x, const CalcDimension& y, const CalcDimension& z) : x(x), y(y), z(z) {}
    // for inner construct, default unit is PX
    TranslateOptions(float x, float y, float z) : x(x), y(y), z(z) {}
    bool operator==(const TranslateOptions& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
    std::string ToString() const
    {
        return "translate:[" + x.ToString() + ", " + y.ToString() + ", " + z.ToString() + "]";
    }
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_NG_TRANSITION_PROPERTY_H
