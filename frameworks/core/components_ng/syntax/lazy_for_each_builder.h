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
#include <unordered_set>
#include <utility>

#include "base/log/ace_trace.h"
#include "base/utils/noncopyable.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_v2/foreach/lazy_foreach_component.h"

namespace OHOS::Ace::NG {

using LazyForEachChild = std::pair<std::string, RefPtr<UINode>>;
using LazyForEachCacheChild = std::pair<int32_t, RefPtr<UINode>>;

class ACE_EXPORT LazyForEachBuilder : public virtual AceType {
    DECLARE_ACE_TYPE(NG::LazyForEachBuilder, AceType)
public:
    LazyForEachBuilder() = default;
    ~LazyForEachBuilder() override = default;

    int32_t GetTotalCount()
    {
        return OnGetTotalCount();
    }

    std::pair<std::string, RefPtr<UINode>> GetChildByIndex(int32_t index, bool needBuild)
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

    void ExpandChildrenOnInitial()
    {
        OnExpandChildrenOnInitialInNG();
    }

    void OnDataReloaded()
    {
        for (auto& [index, node] : cachedItems_) {
            if (node.second) {
                expiringItem_.try_emplace(node.first, LazyForEachCacheChild(-1, std::move(node.second)));
            }
        }
        cachedItems_.clear();
        needTransition = true;
    }

    bool OnDataAdded(size_t index)
    {
        if (cachedItems_.empty()) {
            return true;
        }
        if (index <= static_cast<size_t>(cachedItems_.rbegin()->first) ||
            index >= static_cast<size_t>(cachedItems_.begin()->first)) {
            decltype(cachedItems_) temp(std::move(cachedItems_));

            for (auto& [oldindex, id] : temp) {
                cachedItems_.try_emplace(
                    index >= static_cast<size_t>(oldindex) ? oldindex : oldindex + 1, std::move(id));
            }
        }
        for (auto& [key, node] : expiringItem_) {
            if (static_cast<size_t>(node.first) >= index) {
                node.first++;
            }
        }

        return true;
    }

    RefPtr<UINode> OnDataDeleted(size_t index)
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
                } else {
                    cachedItems_.try_emplace(
                        index > static_cast<size_t>(oldindex) ? oldindex : oldindex - 1, std::move(child));
                }
            }
        }
        for (auto& [key, child] : expiringItem_) {
            if (static_cast<size_t>(child.first) > index) {
                child.first--;
            }
            if (static_cast<size_t>(child.first) == index) {
                child.first = -1;
                node = child.second;
            }
        }

        return node;
    }

    bool OnDataChanged(size_t index)
    {
        auto keyIter = cachedItems_.find(index);
        if (keyIter != cachedItems_.end()) {
            if (keyIter->second.second) {
                expiringItem_.try_emplace(
                    keyIter->second.first, LazyForEachCacheChild(-1, std::move(keyIter->second.second)));
            }
            cachedItems_.erase(keyIter);
            return true;
        }
        return false;
    }

    bool OnDataMoved(size_t from, size_t to)
    {
        return true;
    }

    RefPtr<UINode> GetChildByKey(const std::string& key)
    {
        return nullptr;
    }

    std::map<int32_t, LazyForEachChild>& GetItems(std::list<RefPtr<UINode>>& childList)
    {
        startIndex_ = -1;
        endIndex_ = -1;

        decltype(cachedItems_) items(std::move(cachedItems_));

        for (auto& [index, node] : items) {
            if (!node.second) {
                cachedItems_.try_emplace(index, std::move(node));
                continue;
            }

            auto frameNode = AceType::DynamicCast<FrameNode>(node.second->GetFrameChildByIndex(0, true));
            if (frameNode && !frameNode->IsActive()) {
                frameNode->SetJSViewActive(false);
                expiringItem_.try_emplace(node.first, LazyForEachCacheChild(index, std::move(node.second)));
                continue;
            }
            cachedItems_.try_emplace(index, std::move(node));
            if (startIndex_ == -1) {
                startIndex_ = index;
            }
            endIndex_ = std::max(endIndex_, index);
        }

        if (needTransition) {
            for (auto& [key, node] : expiringItem_) {
                if (!node.second) {
                    continue;
                }
                auto frameNode = AceType::DynamicCast<FrameNode>(node.second->GetFrameChildByIndex(0, true));
                if (frameNode && frameNode->IsOnMainTree()) {
                    childList.push_back(node.second);
                }
            }
            needTransition = false;
        }

        return cachedItems_;
    }

    void RemoveAllChild()
    {
        for (auto& [index, node] : cachedItems_) {
            if (!node.second) {
                continue;
            }
            auto frameNode = AceType::DynamicCast<FrameNode>(node.second->GetFrameChildByIndex(0, true));
            if (frameNode) {
                frameNode->SetActive(false);
            }
            node.second->SetJSViewActive(false);
            expiringItem_.try_emplace(node.first, LazyForEachCacheChild(index, std::move(node.second)));
        }
    }

    void SetFlagForGeneratedItem(PropertyChangeFlag propertyChangeFlag)
    {
        for (const auto& item : cachedItems_) {
            if (!item.second.second) {
                continue;
            }
            item.second.second->ForceUpdateLayoutPropertyFlag(propertyChangeFlag);
        }
    }

    RefPtr<UINode> CacheItem(int32_t index, std::unordered_map<std::string, LazyForEachCacheChild>& cache,
        const std::optional<LayoutConstraintF>& itemConstraint)
    {
        ACE_SCOPED_TRACE("Builder:BuildLazyItem [%d]", index);
        auto itemInfo = OnGetChildByIndex(index, expiringItem_);
        CHECK_NULL_RETURN(itemInfo.second, nullptr);
        cache.try_emplace(itemInfo.first, LazyForEachCacheChild(index, itemInfo.second));
        ViewStackProcessor::GetInstance()->SetPredict(itemInfo.second);
        itemInfo.second->Build();
        ViewStackProcessor::GetInstance()->ResetPredict();
        itemInfo.second->SetJSViewActive(false);
        cachedItems_[index] = LazyForEachChild(itemInfo.first, nullptr);

        return itemInfo.second;
    }

    bool PreBuild(int64_t deadline, const std::optional<LayoutConstraintF>& itemConstraint, bool canRunLongPredictTask)
    {
        ACE_SCOPED_TRACE("expiringItem_ count:[%zu]", expiringItem_.size());
        auto count = OnGetTotalCount();
        std::unordered_map<std::string, LazyForEachCacheChild> cache;
        std::unordered_set<int32_t> idleIndexes;
        if (startIndex_ != -1 && endIndex_ != -1) {
            for (int32_t i = 1; i <= cacheCount_; i++) {
                if (startIndex_ >= i) {
                    idleIndexes.emplace(startIndex_ - i);
                }
                if (endIndex_ + i < count) {
                    idleIndexes.emplace(endIndex_ + i);
                }
            }
        }

        for (auto& [key, node] : expiringItem_) {
            auto iter = idleIndexes.find(node.first);
            if (iter != idleIndexes.end() && node.second) {
                cache.try_emplace(key, std::move(node));
                cachedItems_.try_emplace(node.first, LazyForEachChild(key, nullptr));
                idleIndexes.erase(iter);
            }
        }

        bool result = true;
        for (auto index : idleIndexes) {
            if (GetSysTimestamp() > deadline) {
                result = false;
                continue;
            }
            auto uiNode = CacheItem(index, cache, itemConstraint);
            if (!canRunLongPredictTask && itemConstraint) {
                result = false;
                continue;
            }
            if (canRunLongPredictTask && uiNode && itemConstraint) {
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
        return result;
    }

    virtual void ReleaseChildGroupById(const std::string& id) = 0;

    virtual void RegisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener) = 0;

    virtual void UnregisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener) = 0;

    void SetCacheCount(int32_t cacheCount)
    {
        cacheCount_ = cacheCount;
    }

    const std::map<int32_t, LazyForEachChild>& GetAllChildren()
    {
        if (!cachedItems_.empty()) {
            startIndex_ = cachedItems_.begin()->first;
            endIndex_ = cachedItems_.rbegin()->first;
        }
        return cachedItems_;
    }

protected:
    virtual int32_t OnGetTotalCount() = 0;

    virtual LazyForEachChild OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, LazyForEachCacheChild>& cachedItems) = 0;

    virtual void OnExpandChildrenOnInitialInNG() = 0;

private:
    std::map<int32_t, LazyForEachChild> cachedItems_;
    std::unordered_map<std::string, LazyForEachCacheChild> expiringItem_;

    int32_t startIndex_ = -1;
    int32_t endIndex_ = -1;
    int32_t cacheCount_ = 0;
    bool needTransition = false;
    ACE_DISALLOW_COPY_AND_MOVE(LazyForEachBuilder);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOREACH_LAZY_FOR_EACH_BUILDER_H