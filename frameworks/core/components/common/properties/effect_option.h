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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_EFFECT_OPTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_EFFECT_OPTION_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/json/json_util.h"
#include "base/utils/utils.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace {

enum class ACE_EXPORT ClickEffectLevel {
    UNDEFINED = -1,
    LIGHT = 0,
    MIDDLE,
    HEAVY,
};

struct ClickEffectInfo {
    ClickEffectLevel level = ClickEffectLevel::LIGHT;
    float scaleNumber = 0.0f;
    bool operator==(const ClickEffectInfo& other) const
    {
        return level == other.level && NearEqual(scaleNumber, other.scaleNumber);
    }
};

struct PixStretchEffectOption {
    Dimension left;
    Dimension top;
    Dimension right;
    Dimension bottom;
    bool operator==(const PixStretchEffectOption& other) const
    {
        return left == other.left && top == other.top && right == other.right && bottom == other.bottom;
    }

    bool IsPercentOption() const
    {
        return (left.Unit() == DimensionUnit::PERCENT && top.Unit() == DimensionUnit::PERCENT &&
                right.Unit() == DimensionUnit::PERCENT && bottom.Unit() == DimensionUnit::PERCENT);
    }

    void ResetValue()
    {
        left = Dimension(0.0f);
        top = Dimension(0.0f);
        right = Dimension(0.0f);
        bottom = Dimension(0.0f);
    }

    std::string ToString() const
    {
        return std::string("PixStretchEffectOption (")
            .append(left.ToString())
            .append(",")
            .append(top.ToString())
            .append(",")
            .append(right.ToString())
            .append(",")
            .append(bottom.ToString())
            .append(")");
    }

    struct resourceUpdater {
        RefPtr<ResourceObject> resObj;
        std::function<void(const RefPtr<ResourceObject>&, PixStretchEffectOption&)> updateFunc;
    };
    std::unordered_map<std::string, resourceUpdater> resMap_;

    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, PixStretchEffectOption&)>&& updateFunc)
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
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_EFFECT_OPTION_H
