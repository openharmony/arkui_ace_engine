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
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_v2/foreach/lazy_foreach_component.h"

namespace OHOS::Ace::NG {

typedef struct OperationInfo {
    OperationInfo():node(nullptr) {}
    int32_t changeCount = 0;
    std::string key;
    RefPtr<UINode> node;
    bool isDeleting = false;
    bool isChanged = false;
    bool moveIn = false;
    std::vector<std::string> extraKey;
} OperationInfo;

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

    std::pair<std::string, RefPtr<UINode>> GetChildByIndex(int32_t index, bool needBuild, bool isCache = false);

    void ExpandChildrenOnInitial()
    {
        OnExpandChildrenOnInitialInNG();
    }

    void OnDataReloaded();

    bool OnDataAdded(size_t index);

    bool OnDataBulkAdded(size_t index, size_t count);

    RefPtr<UINode> OnDataDeleted(size_t index);

    std::list<std::pair<std::string, RefPtr<UINode>>>& OnDataBulkDeleted(size_t index, size_t count);

    bool OnDataChanged(size_t index);

    std::list<std::pair<std::string, RefPtr<UINode>>>& OnDataBulkChanged(size_t index, size_t count);

    void OnDataMoveToNewPlace(size_t from, size_t to);

    bool OnDataMoved(size_t from, size_t to);

    std::pair<int32_t, std::list<RefPtr<UINode>>> OnDatasetChange(std::list<V2::Operation> DataOperations);

    void RepairDatasetItems(std::map<int32_t, LazyForEachChild>& cachedTemp,
        std::map<int32_t, LazyForEachChild>& expiringTempItem_, std::map<int32_t, int32_t>& indexChangedMap);

    void CollectIndexChangedCount(std::map<int32_t, int32_t>& indexChangedMap);

    bool ClassifyOperation(V2::Operation& operation, int32_t& initialIndex,
        std::map<int32_t, LazyForEachChild>& cachedTemp, std::map<int32_t, LazyForEachChild>& expiringTemp);

    void OperateAdd(V2::Operation& operation, int32_t& initialIndex);

    void OperateDelete(V2::Operation& operation, int32_t& initialIndex);

    void OperateMove(V2::Operation& operation, int32_t& initialIndex,
        std::map<int32_t, LazyForEachChild>& cachedTemp, std::map<int32_t, LazyForEachChild>& expiringTemp);

    void OperateChange(V2::Operation& operation, int32_t& initialIndex,
        std::map<int32_t, LazyForEachChild>& cachedTemp, std::map<int32_t, LazyForEachChild>& expiringTemp);

    void OperateExchange(V2::Operation& operation, int32_t& initialIndex,
        std::map<int32_t, LazyForEachChild>& cachedTemp, std::map<int32_t, LazyForEachChild>& expiringTemp);

    void OperateReload(V2::Operation& operation, int32_t& initialIndex);

    void ThrowRepeatOperationError(int32_t index);

    void RecordOutOfBoundaryNodes(int32_t index);

    void InvalidIndexOfChangedData(size_t index)
    {
        for (auto& [key, child] : expiringItem_) {
            if (static_cast<size_t>(child.first) == index) {
                child.first = -1;
                break;
            }
        }
    }

    RefPtr<UINode> GetChildByKey(const std::string& key)
    {
        return nullptr;
    }

    std::map<int32_t, LazyForEachChild>& GetItems(std::list<std::pair<std::string, RefPtr<UINode>>>& childList)
    {
        startIndex_ = -1;
        endIndex_ = -1;
        int32_t lastIndex = -1;
        bool isCertained = false;

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
            if (isLoop_) {
                if (isCertained) {
                    continue;
                }
                if (lastIndex > -1 && index - lastIndex > 1) {
                    startIndex_ = index;
                    endIndex_ = lastIndex;
                    isCertained = true;
                } else {
                    endIndex_ = std::max(endIndex_, index);
                }
            } else {
                endIndex_ = std::max(endIndex_, index);
            }
            lastIndex = index;
        }

        if (needTransition) {
            for (auto& [key, node] : expiringItem_) {
                if (!node.second) {
                    continue;
                }
                auto frameNode = AceType::DynamicCast<FrameNode>(node.second->GetFrameChildByIndex(0, true));
                if (frameNode && frameNode->IsOnMainTree()) {
                    childList.emplace_back(key, node.second);
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
            auto pair = expiringItem_.try_emplace(node.first, LazyForEachCacheChild(index, std::move(node.second)));
            if (!pair.second) {
                TAG_LOGW(AceLogTag::ACE_LAZY_FOREACH, "Use repeat key for index: %{public}d", index);
            }
        }
    }

    bool SetActiveChildRange(int32_t start, int32_t end)
    {
        int32_t count = GetTotalCount();
        bool needBuild = false;
        for (auto& [index, node] : cachedItems_) {
            if ((index < count) && ((start <= end && start <= index && end >= index) ||
                (start > end && (index <= end || index >= start)))) {
                if (node.second) {
                    auto frameNode = AceType::DynamicCast<FrameNode>(node.second->GetFrameChildByIndex(0, true));
                    if (frameNode) {
                        frameNode->SetActive(true);
                    }
                    continue;
                }
                auto keyIter = expiringItem_.find(node.first);
                if (keyIter != expiringItem_.end() && keyIter->second.second) {
                    node.second = keyIter->second.second;
                    expiringItem_.erase(keyIter);
                    auto frameNode = AceType::DynamicCast<FrameNode>(node.second->GetFrameChildByIndex(0, true));
                    if (frameNode) {
                        frameNode->SetActive(true);
                    }
                }
                needBuild = true;
                continue;
            }
            if (!node.second) {
                continue;
            }
            auto frameNode = AceType::DynamicCast<FrameNode>(node.second->GetFrameChildByIndex(0, true));
            if (frameNode) {
                frameNode->SetActive(false);
            }
            auto pair = expiringItem_.try_emplace(node.first, LazyForEachCacheChild(index, std::move(node.second)));
            if (!pair.second) {
                TAG_LOGW(AceLogTag::ACE_LAZY_FOREACH, "Use repeat key for index: %{public}d", index);
            }
            needBuild = true;
        }
        return needBuild;
    }

    int32_t GetChildIndex(const RefPtr<FrameNode>& targetNode)
    {
        for (auto& [index, node] : cachedItems_) {
            if (node.second) {
                auto frameNode = AceType::DynamicCast<FrameNode>(node.second->GetFrameChildByIndex(0, true));
                if (frameNode == targetNode) {
                    return index;
                }
            }
        }
        return -1;
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
        const std::optional<LayoutConstraintF>& itemConstraint, int64_t deadline, bool& isTimeout)
    {
        ACE_SCOPED_TRACE("Builder:BuildLazyItem [%d]", index);
        auto itemInfo = OnGetChildByIndex(index, expiringItem_);
        CHECK_NULL_RETURN(itemInfo.second, nullptr);
        cache.try_emplace(itemInfo.first, LazyForEachCacheChild(index, itemInfo.second));
        if (!itemInfo.second->RenderCustomChild(deadline)) {
            isTimeout = true;
            return itemInfo.second;
        }
        ProcessOffscreenNode(itemInfo.second, false);
        ViewStackProcessor::GetInstance()->SetPredict(itemInfo.second);
        itemInfo.second->Build(nullptr);
        auto frameNode = AceType::DynamicCast<FrameNode>(itemInfo.second->GetFrameChildByIndex(0, false, true));
        if (frameNode && frameNode->GetTag() == V2::LIST_ITEM_ETS_TAG) {
            frameNode->GetPattern<ListItemPattern>()->BeforeCreateLayoutWrapper();
        }
        ViewStackProcessor::GetInstance()->ResetPredict();
        itemInfo.second->SetJSViewActive(false);
        cachedItems_[index] = LazyForEachChild(itemInfo.first, nullptr);

        return itemInfo.second;
    }

    void CheckCacheIndex(std::set<int32_t>& idleIndexes, int32_t count) {
        for (int32_t i = 1; i <= cacheCount_; i++) {
            if (isLoop_) {
                if ((startIndex_ <= endIndex_ && endIndex_ + i < count) ||
                    startIndex_ > endIndex_ + i) {
                    idleIndexes.emplace(endIndex_ + i);
                } else if ((endIndex_ + i) % count < startIndex_) {
                    idleIndexes.emplace((endIndex_ + i) % count);
                }
            } else {
                if (endIndex_ + i < count) {
                    idleIndexes.emplace(endIndex_ + i);
                }
            }
        }
        for (int32_t i = 1; i <= cacheCount_; i++) {
            if (isLoop_) {
                if ((startIndex_ <= endIndex_ && startIndex_ >= i) ||
                    startIndex_ > endIndex_ + i) {
                    idleIndexes.emplace(startIndex_ - i);
                } else if ((startIndex_ - i + count) % count > endIndex_) {
                    idleIndexes.emplace((startIndex_ - i + count) % count);
                }
            } else {
                if (startIndex_ >= i) {
                    idleIndexes.emplace(startIndex_ - i);
                }
            }
        }
    }

    bool PreBuildByIndex(int32_t index, std::unordered_map<std::string, LazyForEachCacheChild>& cache,
        int64_t deadline, const std::optional<LayoutConstraintF>& itemConstraint, bool canRunLongPredictTask)
    {
        if (GetSysTimestamp() > deadline) {
            return false;
        }
        bool isTimeout = false;
        preBuildingIndex_ = -1;
        auto uiNode = CacheItem(index, cache, itemConstraint, deadline, isTimeout);
        if (isTimeout) {
            preBuildingIndex_ = index;
            return false;
        }
        if (!canRunLongPredictTask && itemConstraint) {
            return false;
        }
        if (canRunLongPredictTask && uiNode && itemConstraint) {
            RefPtr<FrameNode> frameNode = DynamicCast<FrameNode>(uiNode);
            while (!frameNode) {
                auto tempNode = uiNode;
                uiNode = tempNode->GetFirstChild();
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
        return true;
    }

    bool ProcessPreBuildingIndex(std::unordered_map<std::string, LazyForEachCacheChild>& cache, int64_t deadline,
        const std::optional<LayoutConstraintF>& itemConstraint, bool canRunLongPredictTask,
        std::set<int32_t>& idleIndexes)
    {
        if (idleIndexes.find(preBuildingIndex_) == idleIndexes.end()) {
            preBuildingIndex_ = -1;
            return true;
        }
        idleIndexes.erase(preBuildingIndex_);
        return PreBuildByIndex(preBuildingIndex_, cache, deadline, itemConstraint, canRunLongPredictTask);
    }

    bool PreBuild(int64_t deadline, const std::optional<LayoutConstraintF>& itemConstraint, bool canRunLongPredictTask)
    {
        ACE_SCOPED_TRACE("expiringItem_ count:[%zu]", expiringItem_.size());
        outOfBoundaryNodes_.clear();
        if (itemConstraint && !canRunLongPredictTask) {
            return false;
        }
        auto count = OnGetTotalCount();
        std::unordered_map<std::string, LazyForEachCacheChild> cache;
        std::set<int32_t> idleIndexes;
        if (startIndex_ != -1 && endIndex_ != -1) {
            CheckCacheIndex(idleIndexes, count);
        }

        ProcessCachedIndex(cache, idleIndexes);

        bool result = true;
        result = ProcessPreBuildingIndex(cache, deadline, itemConstraint, canRunLongPredictTask, idleIndexes);
        if (!result) {
            expiringItem_.swap(cache);
            return result;
        }

        for (auto index : idleIndexes) {
            result = PreBuildByIndex(index, cache, deadline, itemConstraint, canRunLongPredictTask);
            if (!result) {
                break;
            }
        }
        expiringItem_.swap(cache);
        return result;
    }

    void ProcessCachedIndex(std::unordered_map<std::string, LazyForEachCacheChild>& cache,
        std::set<int32_t>& idleIndexes)
    {
        auto expiringIter = expiringItem_.begin();
        while (expiringIter != expiringItem_.end()) {
            const auto& key = expiringIter->first;
            const auto& node = expiringIter->second;
            auto iter = idleIndexes.find(node.first);
            if (iter != idleIndexes.end() && node.second) {
                ProcessOffscreenNode(node.second, false);
                if (node.first == preBuildingIndex_) {
                    cache.try_emplace(key, node);
                } else {
                    cache.try_emplace(key, std::move(node));
                    cachedItems_.try_emplace(node.first, LazyForEachChild(key, nullptr));
                    idleIndexes.erase(iter);
                }
                expiringIter++;
            } else {
                NotifyDataDeleted(node.second, static_cast<size_t>(node.first), true);
                ProcessOffscreenNode(node.second, true);
                NotifyItemDeleted(RawPtr(node.second), key);
                expiringIter = expiringItem_.erase(expiringIter);
            }
        }
    }

    void ProcessOffscreenNode(RefPtr<UINode> uiNode, bool remove)
    {
        if (uiNode) {
            auto frameNode = DynamicCast<FrameNode>(uiNode);
            while (!frameNode) {
                auto tempNode = uiNode;
                uiNode = tempNode->GetFirstChild();
                if (!uiNode) {
                    break;
                }
                frameNode = DynamicCast<FrameNode>(uiNode);
            }
            if (frameNode) {
                if (!remove) {
                    Inspector::AddOffscreenNode(frameNode);
                } else {
                    Inspector::RemoveOffscreenNode(frameNode);
                }
            }
        }
    }

    void ClearAllOffscreenNode()
    {
        for (auto& [key, node] : expiringItem_) {
            ProcessOffscreenNode(node.second, true);
        }
        for (auto& [key, node] : cachedItems_) {
            ProcessOffscreenNode(node.second, true);
        }
    }

    virtual void ReleaseChildGroupById(const std::string& id) = 0;

    virtual void RegisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener) = 0;

    virtual void UnregisterDataChangeListener(V2::DataChangeListener* listener) = 0;

    void SetCacheCount(int32_t cacheCount)
    {
        cacheCount_ = cacheCount;
    }

    void SetIsLoop(bool isLoop)
    {
        isLoop_ = isLoop;
    }

    void clearDeletedNodes()
    {
        nodeList_.clear();
    }

    void SetUseNewInterface(bool useNewInterface)
    {
        useNewInterface_ = useNewInterface;
    }

    const std::unordered_map<std::string, LazyForEachCacheChild>& GetCachedUINodeMap()
    {
        return expiringItem_;
    }

    const std::map<int32_t, LazyForEachChild>& GetAllChildren()
    {
        if (!cachedItems_.empty()) {
            startIndex_ = cachedItems_.begin()->first;
            endIndex_ = cachedItems_.rbegin()->first;
        }
        if (isLoop_ && !cachedItems_.empty()) {
            int32_t lastIndex = -1;
            for (auto& [index, node] : cachedItems_) {
                if (lastIndex > -1 && index - lastIndex > 1) {
                    startIndex_ = index;
                    endIndex_ = lastIndex;
                    break;
                }
            }
        }
        return cachedItems_;
    }

    void SetJSViewActive(bool active)
    {
        for (const auto& node : cachedItems_) {
            if (node.second.second == nullptr) {
                continue;
            }
            node.second.second->SetJSViewActive(active);
        }
        for (const auto& node : expiringItem_) {
            node.second.second->SetJSViewActive(active);
        }
    }

    void PaintDebugBoundaryTreeAll(bool flag)
    {
        for (const auto& node : cachedItems_) {
            if (node.second.second == nullptr) {
                continue;
            }
            node.second.second->PaintDebugBoundaryTreeAll(flag);
        }
        for (const auto& node : expiringItem_) {
            if (node.second.second == nullptr) {
                continue;
            }
            node.second.second->PaintDebugBoundaryTreeAll(flag);
        }
    }

    void NotifyItemDeleted(UINode* node, const std::string& key)
    {
        OnItemDeleted(node, key);
    }

protected:
    virtual int32_t OnGetTotalCount() = 0;

    virtual void OnItemDeleted(UINode* node, const std::string& key) {};

    virtual LazyForEachChild OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, LazyForEachCacheChild>& cachedItems) = 0;
    
    virtual LazyForEachChild OnGetChildByIndexNew(int32_t index,
        std::map<int32_t, LazyForEachChild>& cachedItems,
        std::unordered_map<std::string, LazyForEachCacheChild>& expiringItems) = 0;

    virtual void OnExpandChildrenOnInitialInNG() = 0;

    virtual void NotifyDataChanged(size_t index, const RefPtr<UINode>& lazyForEachNode, bool isRebuild = true) = 0;

    virtual void NotifyDataDeleted(const RefPtr<UINode>& lazyForEachNode, size_t index, bool removeIds) = 0;

    virtual void NotifyDataAdded(size_t index) = 0;

    virtual void KeepRemovedItemInCache(NG::LazyForEachChild node,
        std::unordered_map<std::string, NG::LazyForEachCacheChild>& cachedItems) = 0;

    void GetAllItems(std::vector<UINode*>& items);

private:
    void RecycleItemsOutOfBoundary();
    void RecycleChildByIndex(int32_t index);

    std::map<int32_t, LazyForEachChild> cachedItems_;
    std::unordered_map<std::string, LazyForEachCacheChild> expiringItem_;
    std::list<std::pair<std::string, RefPtr<UINode>>> nodeList_;
    std::map<int32_t, OperationInfo> operationList_;
    std::map<std::string, int32_t> operationTypeMap = {
        {"add", 1},
        {"delete", 2},
        {"change", 3},
        {"move", 4},
        {"exchange", 5},
        {"reload", 6}
    };
    std::list<int32_t> outOfBoundaryNodes_;

    int32_t startIndex_ = -1;
    int32_t endIndex_ = -1;
    int32_t cacheCount_ = 0;
    int32_t preBuildingIndex_ = -1;
    bool needTransition = false;
    bool isLoop_ = false;
    bool useNewInterface_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(LazyForEachBuilder);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOREACH_LAZY_FOR_EACH_BUILDER_H
