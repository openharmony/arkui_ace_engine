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
#include <list>
#include <map>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "base/log/ace_trace.h"
#include "base/utils/noncopyable.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
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
        auto keyIter = cachedItems_.find(index);
        if (keyIter != cachedItems_.end()) {
            {
                auto iter = generatedItem_.find(keyIter->second);
                if (iter != generatedItem_.end()) {
                    return std::pair<std::string, RefPtr<NG::UINode>>(iter->first, iter->second);
                }
            }
            {
                auto iter = expiringItem_.find(keyIter->second);
                if (iter != expiringItem_.end()) {
                    generatedItem_.try_emplace(iter->first, iter->second);
                    return std::pair<std::string, RefPtr<NG::UINode>>(iter->first, iter->second);
                }
            }
        }

        ACE_SCOPED_TRACE("Builder:BuildLazyItem [%d]", index);
        auto itemInfo = OnGetChildByIndex(index, expiringItem_);
        CHECK_NULL_RETURN(itemInfo.second, itemInfo);
        {
            auto result = generatedItem_.try_emplace(itemInfo.first, itemInfo.second);
            if (!result.second) {
                LOGD("already has same key %{private}s child", itemInfo.first.c_str());
            }
        }
        cachedItems_[index] = itemInfo.first;
        return std::pair<std::string, RefPtr<NG::UINode>>(itemInfo.first, itemInfo.second);
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
    {}

    void SetCacheItemInfo(int32_t index, const std::string& info) {}

    std::optional<std::string> GetCacheItemInfo(int32_t index) const
    {
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

    void OnDataReloaded()
    {
        cachedItems_.clear();
        expiringItem_.merge(generatedItem_);
        generatedItem_.clear();
    }

    bool OnDataAdded(size_t index)
    {
        if (cachedItems_.empty()) {
            return true;
        }
        if (index > cachedItems_.rbegin()->first || index < cachedItems_.begin()->first) {
            return false;
        }
        decltype(cachedItems_) temp(std::move(cachedItems_));

        for (auto& [oldindex, id] : temp) {
            cachedItems_.try_emplace(index > oldindex ? oldindex : oldindex + 1, std::move(id));
        }
        return true;
    }

    bool OnDataDeleted(size_t index)
    {
        if (cachedItems_.empty()) {
            return false;
        }
        if (index > cachedItems_.rbegin()->first) {
            return false;
        }
        decltype(cachedItems_) temp(std::move(cachedItems_));

        for (auto& [oldindex, id] : temp) {
            cachedItems_.try_emplace(index > oldindex ? oldindex : oldindex - 1, std::move(id));
        }
        return true;
    }

    bool OnDataChanged(size_t index)
    {
        auto keyIter = cachedItems_.find(index);
        if (keyIter != cachedItems_.end()) {
            auto iter = generatedItem_.find(keyIter->second);
            cachedItems_.erase(keyIter);
            if (iter != generatedItem_.end()) {
                expiringItem_.try_emplace(iter->first, std::move(iter->second));
                generatedItem_.erase(iter);
                return true;
            }
        }
        return false;
    }

    bool OnDataMoved(size_t from, size_t to)
    {
        return true;
    }

    void UpdateCachedItems(int start, int end) {}

    std::map<int32_t, RefPtr<UINode>> GetItems() const
    {
        std::map<int32_t, RefPtr<UINode>> items;
        for (auto& [index, key] : cachedItems_) {
            auto itor = generatedItem_.find(key);
            if (itor == generatedItem_.end()) {
                continue;
            }
            items.try_emplace(index, itor->second);
        }

        return items;
    }

    void RemoveAllChild()
    {
        ACE_SCOPED_TRACE("RemoveAllChild");
        expiringItem_.merge(generatedItem_);
        generatedItem_.clear();
    }

    RefPtr<UINode> RemoveChildByIndex(int32_t index)
    {
        ACE_SCOPED_TRACE("RemoveChildByIndex %d", index);
        RefPtr<UINode> child;
        auto keyIter = cachedItems_.find(index);
        if (keyIter != cachedItems_.end()) {
            auto iter = generatedItem_.find(keyIter->second);
            if (iter != generatedItem_.end()) {
                child = iter->second;
                expiringItem_.try_emplace(iter->first, std::move(iter->second));
                generatedItem_.erase(iter);
            }
        }
        return child;
    }

    void ClearExpiringItem()
    {
        expiringItem_.clear();
    }

    void SetFlagForGeneratedItem(PropertyChangeFlag propertyChangeFlag)
    {
        for (const auto& item : generatedItem_) {
            item.second->ForceUpdateLayoutPropertyFlag(propertyChangeFlag);
        }
    }

    RefPtr<UINode> CacheItem(int32_t index, std::unordered_map<std::string, RefPtr<UINode>>& cache,
        const std::optional<LayoutConstraintF>& itemConstraint)
    {
        auto keyIter = cachedItems_.find(index);
        if (keyIter != cachedItems_.end()) {
            auto iter = expiringItem_.find(keyIter->second);
            if (iter != expiringItem_.end()) {
                cache.try_emplace(iter->first, iter->second);
                return iter->second;
            }
        }
        ACE_SCOPED_TRACE("Builder:BuildLazyItem [%d]", index);
        auto itemInfo = OnGetChildByIndex(index, expiringItem_);
        CHECK_NULL_RETURN(itemInfo.second, nullptr);
        cache.try_emplace(itemInfo.first, itemInfo.second);
        itemInfo.second->Build();
        return itemInfo.second;
    }

    bool PreBuild(int32_t start, int32_t end, int32_t cacheCount, int64_t deadline,
        const std::optional<LayoutConstraintF>& itemConstraint, bool canRunLongPredictTask)
    {
        auto count = OnGetTotalCount();
        std::unordered_map<std::string, RefPtr<UINode>> cache;
        std::list<int32_t> idleIndexes;
        if (start != -1 && end != -1) {
            for (int32_t i = 1; i <= cacheCount; i++) {
                if (start >= i) {
                    idleIndexes.emplace_back(start - i);
                }
                if (end + i < count) {
                    idleIndexes.emplace_back(end + i);
                }
            }
        }

        for (auto index : idleIndexes) {
            if ((GetSysTimestamp() > deadline) || (itemConstraint && !canRunLongPredictTask)) {
                expiringItem_.swap(cache);
                return false;
            }
            auto uiNode = CacheItem(index, cache, itemConstraint);
            if (uiNode && itemConstraint) {
                RefPtr<FrameNode> frameNode = DynamicCast<FrameNode>(uiNode);
                while (!frameNode) {
                    uiNode = uiNode->GetFirstChild();
                    if (!uiNode) {
                        break;
                    }
                    frameNode = DynamicCast<FrameNode>(uiNode);
                }
                if (frameNode) {
                    frameNode->GetGeometryNode()->SetParentLayoutConstraint(itemConstraint.value());
                    FrameNode::ProcessOffscreenNode(frameNode);
                }
            }
        }

        expiringItem_.swap(cache);
        return true;
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
    std::map<int32_t, std::string> cachedItems_;

    std::unordered_map<std::string, RefPtr<UINode>> expiringItem_;

    ACE_DISALLOW_COPY_AND_MOVE(LazyForEachBuilder);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOREACH_LAZY_FOR_EACH_BUILDER_H
