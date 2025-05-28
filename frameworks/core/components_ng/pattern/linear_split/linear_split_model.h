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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_SPLIT_LINEAR_SPLIT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_SPLIT_LINEAR_SPLIT_MODEL_H

#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace::NG {

enum class SplitType {
    ROW_SPLIT,
    COLUMN_SPLIT,
};

struct ItemDivider final {
    Dimension startMargin = 0.0_vp;
    Dimension endMargin = 0.0_vp;
    struct resourceUpdater {
        RefPtr<ResourceObject> resObj;
        std::function<void(const RefPtr<ResourceObject>&, NG::ItemDivider&)> updateFunc;
    };
    std::unordered_map<std::string, resourceUpdater> resMap_;
    bool operator==(const ItemDivider& itemDivider) const
    {
        return (startMargin == itemDivider.startMargin) && (endMargin == itemDivider.endMargin);
    }

    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, NG::ItemDivider&)>&& updateFunc)
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

} // namespace OHOS::Ace::NG

namespace OHOS::Ace {

class ACE_FORCE_EXPORT LinearSplitModel {
public:
    static LinearSplitModel* GetInstance();
    virtual ~LinearSplitModel() = default;

    virtual void Create(NG::SplitType splitType) = 0;
    virtual void SetResizable(NG::SplitType splitType, bool resizable) = 0;
    virtual void SetDivider(NG::SplitType splitType, const NG::ItemDivider& divider) = 0;

private:
    static std::unique_ptr<LinearSplitModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_SPLIT_LINEAR_SPLIT_MODEL_H
