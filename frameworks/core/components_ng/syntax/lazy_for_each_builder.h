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
#include "core/components_v2/foreach/lazy_foreach_component.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

typedef struct OperationInfo {
    OperationInfo():node(nullptr) {}
    int32_t changeCount = 0;
    int32_t fromDiffTo = 0;
    std::string key;
    RefPtr<UINode> node;
    bool isDeleting = false;
    bool isChanged = false;
    bool moveIn = false;
    bool isExchange = false;
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

    void UpdateHistoricalTotalCount(int32_t count)
    {
        historicalTotalCount_ = count;
    }

    int32_t GetTotalCountOfOriginalDataset();

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

    std::pair<int32_t, std::list<std::pair<std::string, RefPtr<UINode>>>> OnDatasetChange(
        std::list<V2::Operation> DataOperations);

    void RepairDatasetItems(std::map<int32_t, LazyForEachChild>& cachedTemp,
        std::map<int32_t, LazyForEachChild>& expiringTempItem_, std::map<int32_t, int32_t>& indexChangedMap);

    void RepairMoveOrExchange(std::map<int32_t, LazyForEachChild>& expiringTempItem_,
        OperationInfo& info, LazyForEachChild& child, int32_t index, int32_t changedIndex);

    void CollectIndexChangedCount(std::map<int32_t, int32_t>& indexChangedMap);

    bool ClassifyOperation(V2::Operation& operation, int32_t& initialIndex,
        std::map<int32_t, LazyForEachChild>& cachedTemp, std::map<int32_t, LazyForEachChild>& expiringTemp);
    
    bool ValidateIndex(int32_t index, const std::string& type);

    void OperateAdd(V2::Operation& operation, int32_t& initialIndex);

    void OperateDelete(V2::Operation& operation, int32_t& initialIndex);

    void OperateMove(V2::Operation& operation, int32_t& initialIndex,
        std::map<int32_t, LazyForEachChild>& cachedTemp, std::map<int32_t, LazyForEachChild>& expiringTemp);

    void OperateChange(V2::Operation& operation, int32_t& initialIndex,
        std::map<int32_t, LazyForEachChild>& cachedTemp, std::map<int32_t, LazyForEachChild>& expiringTemp);

    std::map<int32_t, LazyForEachChild>::iterator FindItem(int32_t index,
        std::map<int32_t, LazyForEachChild>& cachedTemp, std::map<int32_t, LazyForEachChild>& expiringTemp);

    void OperateExchange(V2::Operation& operation, int32_t& initialIndex,
        std::map<int32_t, LazyForEachChild>& cachedTemp, std::map<int32_t, LazyForEachChild>& expiringTemp);

    void OperateReload(std::map<int32_t, LazyForEachChild>& expiringTemp);

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

    void Transit(std::list<std::pair<std::string, RefPtr<UINode>>>& childList);

    std::map<int32_t, LazyForEachChild>& GetItems(std::list<std::pair<std::string, RefPtr<UINode>>>& childList);

    void RemoveAllChild()
    {
        ACE_SYNTAX_SCOPED_TRACE("LazyForEach RemoveAllChild");
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
        ACE_SYNTAX_SCOPED_TRACE("LazyForEach active range start[%d], end[%d]", start, end);
        startIndex_ = start;
        endIndex_ = end;
        int32_t count = GetTotalCount();
        UpdateHistoricalTotalCount(count);
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
        for (auto& [key, node] : expiringItem_) {
            if (!node.second) {
                continue;
            }
            auto frameNode = AceType::DynamicCast<FrameNode>(node.second->GetFrameChildByIndex(0, true));
            if (frameNode && frameNode == targetNode) {
                return node.first;
            }
        }
        return -1;
    }

    void UpdateMoveFromTo(int32_t from, int32_t to);
    void ResetMoveFromTo();
    int32_t ConvertFormToIndex(int32_t index);

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
        auto itemInfo = OnGetChildByIndex(ConvertFormToIndex(index), expiringItem_);
        CHECK_NULL_RETURN(itemInfo.second, nullptr);
        cache.try_emplace(itemInfo.first, LazyForEachCacheChild(index, itemInfo.second));
        auto context = itemInfo.second->GetContext();
        CHECK_NULL_RETURN(context, itemInfo.second);
        auto frameNode = AceType::DynamicCast<FrameNode>(itemInfo.second->GetFrameChildByIndex(0, false, true));
        context->SetPredictNode(frameNode);
        if (!itemInfo.second->RenderCustomChild(deadline)) {
            isTimeout = true;
            context->ResetPredictNode();
            return itemInfo.second;
        }
        ProcessOffscreenNode(itemInfo.second, false);
        itemInfo.second->Build(nullptr);
        context->ResetPredictNode();
        itemInfo.second->SetJSViewActive(false, true);
        cachedItems_[index] = LazyForEachChild(itemInfo.first, nullptr);

        return itemInfo.second;
    }

    void CheckCacheIndex(std::set<int32_t>& idleIndexes, int32_t count)
    {
        for (int32_t i = 1; i <= cacheCount_; i++) {
            if (isLoop_) {
                if ((startIndex_ <= endIndex_ && endIndex_ + i < count) ||
                    startIndex_ > endIndex_ + i) {
                    idleIndexes.emplace(endIndex_ + i);
                } else if ((endIndex_ + i) % count < startIndex_) {
                    idleIndexes.emplace((endIndex_ + i) % count);
                }
            } else {
                if (endIndex_ + i >= 0 && endIndex_ + i < count) {
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
                if (startIndex_ - i >= 0 && startIndex_ - i < count) {
                    idleIndexes.emplace(startIndex_ - i);
                }
            }
        }
    }

    bool PreBuildByIndex(int32_t index, std::unordered_map<std::string, LazyForEachCacheChild>& cache,
        int64_t deadline, const std::optional<LayoutConstraintF>& itemConstraint, bool canRunLongPredictTask)
    {
        if (GetSysTimestamp() > deadline) {
            if (!DeleteExpiringItemImmediately()) {
                cache.merge(expiringItem_);
            }
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

    bool PreBuild(int64_t deadline, const std::optional<LayoutConstraintF>& itemConstraint, bool canRunLongPredictTask);

    void ProcessCachedIndex(std::unordered_map<std::string, LazyForEachCacheChild>& cache,
        std::set<int32_t>& idleIndexes)
    {
        auto expiringIter = expiringItem_.begin();
        while (expiringIter != expiringItem_.end()) {
            const auto& key = expiringIter->first;
            const auto& node = expiringIter->second;
            auto iter = idleIndexes.find(node.first);
            if (iter != idleIndexes.end() && node.second) {
                LoadCacheByIndex(cache, idleIndexes, node, key, iter, expiringIter);
            } else {
                LoadCacheByKey(cache, idleIndexes, node, key, expiringIter);
            }
        }
    }

    void LoadCacheByIndex(std::unordered_map<std::string, LazyForEachCacheChild>& cache, std::set<int32_t>& idleIndexes,
        const LazyForEachCacheChild& node, const std::string& key, const std::set<int32_t>::iterator& iter,
        std::unordered_map<std::string, LazyForEachCacheChild>::iterator& expiringIter)
    {
        ProcessOffscreenNode(node.second, false);

        if (node.first == preBuildingIndex_) {
            cache.try_emplace(key, node);
        } else {
            cache.try_emplace(key, std::move(node));
            cachedItems_.try_emplace(node.first, LazyForEachChild(key, nullptr));
            idleIndexes.erase(iter);
        }

        expiringIter++;
    }

    void LoadCacheByKey(std::unordered_map<std::string, LazyForEachCacheChild>& cache, std::set<int32_t>& idleIndexes,
        const LazyForEachCacheChild& node, const std::string& key,
        std::unordered_map<std::string, LazyForEachCacheChild>::iterator& expiringIter)
    {
        NotifyDataDeleted(node.second, static_cast<size_t>(node.first), true);
        ProcessOffscreenNode(node.second, true);
        NotifyItemDeleted(RawPtr(node.second), key);

        if (DeleteExpiringItemImmediately()) {
            expiringIter = expiringItem_.erase(expiringIter);
        } else {
            expiringIter++;
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
            node.second.second->SetJSViewActive(active, true);
        }
        for (const auto& node : expiringItem_) {
            if (node.second.second == nullptr) {
                continue;
            }
            node.second.second->SetJSViewActive(active, true);
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

    void GetAllItems(std::vector<UINode*>& items);
protected:
    virtual int32_t OnGetTotalCount() = 0;

    virtual void OnItemDeleted(UINode* node, const std::string& key) {};

    virtual bool DeleteExpiringItemImmediately()
    {
        return false;
    }

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

private:
    void RecycleItemsOutOfBoundary();
    void RecycleChildByIndex(int32_t index);

    std::map<int32_t, LazyForEachChild> cachedItems_;
    std::unordered_map<std::string, LazyForEachCacheChild> expiringItem_;
    std::list<std::pair<std::string, RefPtr<UINode>>> nodeList_;
    std::map<int32_t, OperationInfo> operationList_;
    enum class OP { ADD, DEL, CHANGE, MOVE, EXCHANGE, RELOAD };
    std::map<std::string, OP> operationTypeMap = {{"add", OP::ADD},
        {"delete", OP::DEL},
        {"change", OP::CHANGE},
        {"move", OP::MOVE},
        {"exchange", OP::EXCHANGE},
        {"reload", OP::RELOAD}};
    std::list<int32_t> outOfBoundaryNodes_;
    std::optional<std::pair<int32_t, int32_t>> moveFromTo_;

    int32_t startIndex_ = -1;
    int32_t endIndex_ = -1;
    int32_t cacheCount_ = 0;
    int32_t preBuildingIndex_ = -1;
    int32_t totalCountOfOriginalDataset_ = 0;
    int32_t historicalTotalCount_ = 0;
    bool needTransition = false;
    bool isLoop_ = false;
    bool useNewInterface_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(LazyForEachBuilder);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOREACH_LAZY_FOR_EACH_BUILDER_H
