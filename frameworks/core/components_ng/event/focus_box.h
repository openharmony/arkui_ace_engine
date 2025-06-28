/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_FOCUS_BOX_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_FOCUS_BOX_H

#include <functional>
#include <optional>

#include "base/geometry/calc_dimension.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/properties/color.h"
namespace OHOS::Ace::NG {

struct FocusBoxStyle {
    std::optional<Color> strokeColor;
    std::optional<CalcDimension> strokeWidth;
    std::optional<CalcDimension> margin;

    struct ResourceUpdater {
        RefPtr<ResourceObject> obj;
        std::function<void(const RefPtr<ResourceObject>&, FocusBoxStyle&)> updateFunc;
    };
    std::unordered_map<std::string, ResourceUpdater> resMap_;

    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, FocusBoxStyle&)>&& updateFunc)
    {
        if (resObj && updateFunc) {
            resMap_[key] = { resObj, std::move(updateFunc) };
        }
    }

    void RemoveResource(const std::string& key)
    {
        auto iter = resMap_.find(key);
        if (iter != resMap_.end()) {
            resMap_.erase(iter);
        }
    }

    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : resMap_) {
            resourceUpdater.updateFunc(resourceUpdater.obj, *this);
        }
    }
};

class ACE_EXPORT FocusBox : public virtual AceType {
    DECLARE_ACE_TYPE(FocusBox, AceType)

public:
    friend class FocusHub;

    void SetStyle(const FocusBoxStyle& style);
    std::optional<FocusBoxStyle> GetStyle() const;
    bool HasCustomStyle() const;
    static std::unique_ptr<JsonValue> ToJsonValue(const FocusBox& box);

private:
    std::optional<FocusBoxStyle> paintStyle_;
};
} // namespace OHOS::Ace::NG

#endif