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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOREACH_LAZY_FOR_EACH_BUILDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOREACH_LAZY_FOR_EACH_BUILDER_H

#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "base/log/ace_trace.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_v2/foreach/lazy_foreach_component.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT LazyForEachBuilder : public virtual AceType {
    DECLARE_ACE_TYPE(NG::LazyForEachBuilder, AceType)
public:
    LazyForEachBuilder() = default;
    ~LazyForEachBuilder() override = default;

    int32_t GetTotalCount()
    {
        return OnGetTotalCount();
    }

    std::pair<std::string, RefPtr<UINode>> CreateChildByIndex(int32_t index)
    {
        {
            ACE_SCOPED_TRACE("Builder:BuildLazyItem [%d]", index);
            auto itemInfo = OnGetChildByIndex(index, generatedItem_);
            CHECK_NULL_RETURN(itemInfo.second, itemInfo);
            auto result = generatedItem_.try_emplace(itemInfo.first, itemInfo.second);
            if (!result.second) {
                LOGD("already has same key %{private}s child", itemInfo.first.c_str());
            }
            return *(result.first);
        }
    }

    RefPtr<UINode> GetChildByKey(const std::string& key)
    {
        auto iter = generatedItem_.find(key);
        if (iter != generatedItem_.end()) {
            return iter->second;
        }
        return nullptr;
    }

    void UpdateCachedItems(const std::list<std::optional<std::string>>& nodeIds,
        std::unordered_map<int32_t, std::optional<std::string>>&& cachedItems)
    {
        // use active ids to update cached items.
        std::unordered_map<std::string, RefPtr<UINode>> generatedItem;
        std::swap(generatedItem, generatedItem_);
        for (const auto& id : nodeIds) {
            if (!id) {
                continue;
            }
            auto iter = generatedItem.find(*id);
            if (iter != generatedItem.end()) {
                generatedItem_.try_emplace(iter->first, iter->second);
                generatedItem.erase(iter);
            }
        }
        // store cached items.
        for (auto& [index, id] : cachedItems) {
            if (!id) {
                // get id from old cachedItems which stores the idle task generate result.
                auto iter = cachedItems_.find(index);
                if (iter == cachedItems_.end()) {
                    continue;
                }
                id = iter->second;
            }
            if (id) {
                auto iter = generatedItem.find(*id);
                if (iter != generatedItem.end()) {
                    iter->second->SetActive(false);
                    generatedItem_.try_emplace(iter->first, iter->second);
                }
            }
        }
        std::swap(cachedItems_, cachedItems);
        LOGD("LazyForEach cached size : %{public}d", static_cast<int32_t>(generatedItem_.size()));
    }

    void SetCacheItemInfo(int32_t index, const std::string& info)
    {
        cachedItems_[index] = info;
    }

    std::optional<std::string> GetCacheItemInfo(int32_t index) const
    {
        auto iter = cachedItems_.find(index);
        if (iter != cachedItems_.end()) {
            return iter->second;
        }
        return std::nullopt;
    }

    void Clean()
    {
        generatedItem_.clear();
    }

    void RemoveChild(const std::string& id)
    {
        generatedItem_.erase(id);
    }

    void ExpandChildrenOnInitial()
    {
        OnExpandChildrenOnInitialInNG();
    }

    void SetFlagForGeneratedItem(PropertyChangeFlag propertyChangeFlag)
    {
        for (const auto& item : generatedItem_) {
            item.second->ForceUpdateLayoutPropertyFlag(propertyChangeFlag);
        }
    }

    virtual void ReleaseChildGroupById(const std::string& id) = 0;
    virtual void RegisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener) = 0;
    virtual void UnregisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener) = 0;

protected:
    virtual int32_t OnGetTotalCount() = 0;
    virtual std::pair<std::string, RefPtr<UINode>> OnGetChildByIndex(
        int32_t index, const std::unordered_map<std::string, RefPtr<UINode>>& cachedItems) = 0;
    virtual void OnExpandChildrenOnInitialInNG() = 0;

private:
    // [key, UINode]
    std::unordered_map<std::string, RefPtr<UINode>> generatedItem_;
    // [index, key]
    std::unordered_map<int32_t, std::optional<std::string>> cachedItems_;

    ACE_DISALLOW_COPY_AND_MOVE(LazyForEachBuilder);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOREACH_LAZY_FOR_EACH_BUILDER_H
