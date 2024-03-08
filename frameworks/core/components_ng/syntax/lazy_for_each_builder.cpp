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

#include "core/components_ng/syntax/lazy_for_each_builder.h"

namespace OHOS::Ace::NG {
    std::pair<std::string, RefPtr<UINode>> LazyForEachBuilder::GetChildByIndex(int32_t index, bool needBuild)
    {
        auto iter = cachedItems_.find(index);
        if (iter != cachedItems_.end()) {
            if (iter->second.second) {
                return iter->second;
            }
            auto keyIter = expiringItem_.find(iter->second.first);
            if (keyIter != expiringItem_.end() && keyIter->second.second) {
                iter->second.second = keyIter->second.second;
                expiringItem_.erase(keyIter);
                return iter->second;
            }
        }

        if (needBuild) {
            ACE_SCOPED_TRACE("Builder:BuildLazyItem [%d]", index);
            auto itemInfo = OnGetChildByIndex(index, expiringItem_);
            CHECK_NULL_RETURN(itemInfo.second, itemInfo);
            {
                cachedItems_[index] = itemInfo;
            }
            return itemInfo;
        }
        return {};
    }

    void LazyForEachBuilder::OnDataReloaded()
    {
        for (auto& [key, node] : expiringItem_) {
            node.first = -1;
        }
        for (auto& [index, node] : cachedItems_) {
            if (node.second) {
                expiringItem_.try_emplace(node.first, LazyForEachCacheChild(-1, std::move(node.second)));
            }
        }
        cachedItems_.clear();
        needTransition = true;
    }

    bool LazyForEachBuilder::OnDataAdded(size_t index)
    {
        NotifyDataAdded(index);
        if (!cachedItems_.empty() && index <= static_cast<size_t>(cachedItems_.rbegin()->first)) {
            decltype(cachedItems_) temp(std::move(cachedItems_));

            for (auto& [oldindex, id] : temp) {
                cachedItems_.try_emplace(
                    index > static_cast<size_t>(oldindex) ? oldindex : oldindex + 1, std::move(id));
            }
        }
        for (auto& [key, node] : expiringItem_) {
            if (static_cast<size_t>(node.first) >= index && node.first != -1) {
                node.first++;
            }
        }

        return true;
    }

    bool LazyForEachBuilder::OnDataBulkAdded(size_t index, size_t count)
    {
        if (!cachedItems_.empty() && index <= static_cast<size_t>(cachedItems_.rbegin()->first)) {
            decltype(cachedItems_) temp(std::move(cachedItems_));

            for (auto& [oldindex, id] : temp) {
                cachedItems_.try_emplace(
                    index > static_cast<size_t>(oldindex) ? oldindex : oldindex + count, std::move(id));
            }
        }
        for (auto& [key, node] : expiringItem_) {
            if (static_cast<size_t>(node.first) >= index && node.first != -1) {
                node.first = node.first + count;
            }
        }

        return true;
    }

    RefPtr<UINode> LazyForEachBuilder::OnDataDeleted(size_t index)
    {
        RefPtr<UINode> node;
        if (cachedItems_.empty()) {
            return node;
        }
        if (index <= static_cast<size_t>(cachedItems_.rbegin()->first)) {
            decltype(cachedItems_) temp(std::move(cachedItems_));

            for (auto& [oldindex, child] : temp) {
                if (static_cast<size_t>(oldindex) == index) {
                    node = child.second;
                    KeepRemovedItemInCache(child, expiringItem_);
                } else {
                    cachedItems_.try_emplace(
                        index > static_cast<size_t>(oldindex) ? oldindex : oldindex - 1, std::move(child));
                }
            }
        }
        NotifyDataDeleted(node, index, false);
        for (auto& [key, child] : expiringItem_) {
            if (static_cast<size_t>(child.first) > index) {
                child.first--;
                continue;
            }
            if (static_cast<size_t>(child.first) == index) {
                child.first = -1;
                node = child.second;
            }
        }

        return node;
    }

    std::list<RefPtr<UINode>>& LazyForEachBuilder::OnDataBulkDeleted(size_t index, size_t count)
    {
        if (cachedItems_.empty()) {
            return nodeList_;
        }
        if (index <= static_cast<size_t>(cachedItems_.rbegin()->first)) {
            decltype(cachedItems_) temp(std::move(cachedItems_));

            for (auto& [oldindex, child] : temp) {
                if (static_cast<size_t>(oldindex) >= index && static_cast<size_t>(oldindex) < index + count) {
                    nodeList_.push_back(child.second);
                } else {
                    cachedItems_.try_emplace(
                        index > static_cast<size_t>(oldindex) ? oldindex : oldindex - count, std::move(child));
                }
            }
        }
        for (auto& [key, child] : expiringItem_) {
            if (static_cast<size_t>(child.first) > index) {
                child.first -= count;
                continue;
            }
            if (static_cast<size_t>(child.first) >= index && static_cast<size_t>(child.first) < index + count) {
                child.first = -1;
            }
        }

        return nodeList_;
    }

    bool LazyForEachBuilder::OnDataChanged(size_t index)
    {
        auto keyIter = cachedItems_.find(index);
        if (keyIter != cachedItems_.end()) {
            if (keyIter->second.second) {
                NotifyDataChanged(index, keyIter->second.second, false);
                expiringItem_.try_emplace(
                    keyIter->second.first, LazyForEachCacheChild(-1, std::move(keyIter->second.second)));
            } else {
                InvalidIndexOfChangedData(index);
            }
            cachedItems_.erase(keyIter);
            return true;
        }
        return false;
    }

    bool LazyForEachBuilder::OnDataMoved(size_t from, size_t to)
    {
        if (from == to) {
            return false;
        }
        auto fromIter = cachedItems_.find(from);
        auto toIter = cachedItems_.find(to);
        if (fromIter != cachedItems_.end() && toIter != cachedItems_.end()) {
            std::swap(fromIter->second, toIter->second);
        } else if (fromIter != cachedItems_.end()) {
            expiringItem_.try_emplace(
                fromIter->second.first, LazyForEachCacheChild(to, std::move(fromIter->second.second)));
            cachedItems_.erase(fromIter);
        } else if (toIter != cachedItems_.end()) {
            expiringItem_.try_emplace(
                toIter->second.first, LazyForEachCacheChild(from, std::move(toIter->second.second)));
            cachedItems_.erase(toIter);
        }
        return true;
    }
}
