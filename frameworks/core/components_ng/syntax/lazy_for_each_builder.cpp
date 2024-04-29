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
#include "core/components_ng/pattern/recycle_view/recycle_dummy_node.h"

namespace OHOS::Ace::NG {
    std::pair<std::string, RefPtr<UINode>> LazyForEachBuilder::GetChildByIndex(
        int32_t index, bool needBuild, bool isCache)
    {
        auto iter = cachedItems_.find(index);
        if (iter != cachedItems_.end()) {
            if (iter->second.second) {
                return iter->second;
            }
            auto keyIter = expiringItem_.find(iter->second.first);
            if (keyIter != expiringItem_.end() && keyIter->second.second) {
                if (!isCache) {
                    iter->second.second = keyIter->second.second;
                    expiringItem_.erase(keyIter);
                    return iter->second;
                } else {
                    return { keyIter->first, keyIter->second.second };
                }
            }
        }

        if (needBuild) {
            RecycleItemsOutOfBoundary();
            ACE_SCOPED_TRACE("Builder:BuildLazyItem [%d]", index);
            std::pair<std::string, RefPtr<UINode>> itemInfo;
            if (useNewInterface_) {
                itemInfo = OnGetChildByIndexNew(index, cachedItems_, expiringItem_);
            } else {
                itemInfo = OnGetChildByIndex(index, expiringItem_);
            }
            CHECK_NULL_RETURN(itemInfo.second, itemInfo);
            if (isCache) {
                expiringItem_.emplace(itemInfo.first, LazyForEachCacheChild(index, itemInfo.second));
                cachedItems_[index] = LazyForEachChild(itemInfo.first, nullptr);
            } else {
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

    std::list<std::pair<std::string, RefPtr<UINode>>>& LazyForEachBuilder::OnDataBulkDeleted(size_t index, size_t count)
    {
        if (cachedItems_.empty()) {
            return nodeList_;
        }
        if (index <= static_cast<size_t>(cachedItems_.rbegin()->first)) {
            decltype(cachedItems_) temp(std::move(cachedItems_));

            for (auto& [oldindex, child] : temp) {
                if (static_cast<size_t>(oldindex) >= index && static_cast<size_t>(oldindex) < index + count) {
                    nodeList_.emplace_back(child.first, child.second);
                } else {
                    cachedItems_.try_emplace(
                        index > static_cast<size_t>(oldindex) ? oldindex : oldindex - count, std::move(child));
                }
            }
        }
        for (auto& [key, child] : expiringItem_) {
            if (static_cast<size_t>(child.first) >= index + count) {
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

    std::list<std::pair<std::string, RefPtr<UINode>>>& LazyForEachBuilder::OnDataBulkChanged(size_t index, size_t count)
    {
        if (cachedItems_.empty()) {
            return nodeList_;
        }
        if (static_cast<size_t>(cachedItems_.rbegin()->first) < index) {
            return nodeList_;
        }
        for (const auto& [itemIndex, child] : cachedItems_) {
            if (static_cast<size_t>(itemIndex) >= index && static_cast<size_t>(itemIndex) < index + count) {
                NotifyDataChanged(index, child.second, false);
                nodeList_.emplace_back(child.first, child.second);
            }
        }
        for (auto& [key, node] : expiringItem_) {
            if (static_cast<size_t>(node.first) >= index && static_cast<size_t>(node.first) < index + count) {
                node.first = -1;
            }
        }
        return nodeList_;
    }

    void LazyForEachBuilder::OnDataMoveToNewPlace(size_t from, size_t to)
    {
        if (from == to) {
            return;
        }
        decltype(cachedItems_) temp(std::move(cachedItems_));
        if (from < to) {
            for (const auto& [itemIndex, child] : temp) {
                auto position = static_cast<size_t>(itemIndex);
                if (position > from && position <= to) {
                    cachedItems_.emplace(position - 1, child);
                } else if (position == from) {
                    cachedItems_.emplace(to, child);
                } else {
                    cachedItems_.emplace(itemIndex, child);
                }
            }
        } else {
            for (const auto& [itemIndex, child] : temp) {
                auto position = static_cast<size_t>(itemIndex);
                if (position >= to && position < from) {
                    cachedItems_.emplace(position + 1, child);
                } else if (position == from) {
                    cachedItems_.emplace(to, child);
                } else {
                    cachedItems_.emplace(itemIndex, child);
                }
            }
        }
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

    void LazyForEachBuilder::GetAllItems(std::vector<UINode*>& items)
    {
        for (const auto& item : cachedItems_) {
            items.emplace_back(RawPtr(item.second.second));
        }
        for (const auto& item : expiringItem_) {
            items.emplace_back(RawPtr(item.second.second));
        }
        for (const auto& item : nodeList_) {
            items.emplace_back(RawPtr(item.second));
        }
    }

    std::pair<int32_t, std::list<RefPtr<UINode>>> LazyForEachBuilder::OnDatasetChange(
        std::list<V2::Operation> DataOperations)
    {
        int32_t initialIndex = GetTotalCount();
        decltype(cachedItems_) cachedTemp(std::move(cachedItems_));
        std::map<int32_t, LazyForEachChild> expiringTempItem_;
        for (auto& [key, cacheChild] : expiringItem_) {
            expiringTempItem_.try_emplace(cacheChild.first, LazyForEachChild(key, cacheChild.second));
        }
        decltype(expiringTempItem_) expiringTemp(std::move(expiringTempItem_));
        std::list<RefPtr<UINode>> nodeList;
        for (const auto& item : nodeList_) {
            nodeList.emplace_back(item.second);
        }

        for (auto operation : DataOperations) {
            bool isReload = ClassifyOperation(operation, initialIndex, cachedTemp, expiringTemp);
            if (isReload) {
                return std::pair(initialIndex, std::move(nodeList));
            }
        }
        std::map<int32_t, int32_t> indexChangedMap;
        CollectIndexChangedCount(indexChangedMap);
        RepairDatasetItems(cachedTemp, cachedItems_, indexChangedMap);
        RepairDatasetItems(expiringTemp, expiringTempItem_, indexChangedMap);
        for (auto& [index, node] : expiringTempItem_) {
            expiringItem_.emplace(node.first, LazyForEachCacheChild(index, node.second));
        }
        operationList_.clear();
        return std::pair(initialIndex, std::move(nodeList));
    }

    void LazyForEachBuilder::RepairDatasetItems(std::map<int32_t, LazyForEachChild>& cachedTemp,
        std::map<int32_t, LazyForEachChild>& expiringTempItem_, std::map<int32_t, int32_t>& indexChangedMap)
    {
        int32_t changedIndex = 0;
        for (auto& [index, child] : cachedTemp) {
            if (operationList_.find(index) == operationList_.end()) {
                expiringTempItem_.try_emplace(index + changedIndex, child);
                continue;
            }

            auto info = operationList_.find(index)->second;
            changedIndex = indexChangedMap.find(index)->second;
            if (info.isDeleting) {
                nodeList_.emplace_back(child.first, child.second);
            } else if (info.isChanged) {
                expiringTempItem_.try_emplace(index, LazyForEachChild(info.key, nullptr));
            } else if (!info.extraKey.empty()) {
                expiringTempItem_.try_emplace(index + changedIndex, child);
                for (int32_t i = 0; i < static_cast<int32_t>(info.extraKey.size()); i++) {
                    expiringTempItem_.try_emplace(index + i, LazyForEachChild(info.extraKey[i], nullptr));
                }
            } else if (info.node != nullptr) {
                expiringTempItem_.try_emplace(index, LazyForEachChild(info.key, info.node));
                if (info.moveIn) {
                    expiringTempItem_.try_emplace(index - 1, child);
                }
            } else {
                expiringTempItem_.try_emplace(index + changedIndex, child);
            }
        }
    }

    void LazyForEachBuilder::CollectIndexChangedCount(std::map<int32_t, int32_t>& indexChangedMap)
    {
        int32_t changedIndex = 0;
        for (auto& [index, operationInfo] : operationList_) {
            operationInfo.changeCount += changedIndex;
            changedIndex = operationInfo.changeCount;
            if (indexChangedMap.size() >= static_cast<size_t>(1)) {
                for (int32_t i = indexChangedMap.rbegin()->first + 1; i < index; i++) {
                    indexChangedMap.try_emplace(i, changedIndex);
                }
            }
            indexChangedMap.try_emplace(index, changedIndex);
        }
    }

    bool LazyForEachBuilder::ClassifyOperation(V2::Operation& operation, int32_t& initialIndex,
        std::map<int32_t, LazyForEachChild>& cachedTemp, std::map<int32_t, LazyForEachChild>& expiringTemp)
    {
        const int ADDOP = 1;
        const int DELETEOP = 2;
        const int CHANGEOP = 3;
        const int MOVEOP = 4;
        const int EXCHANGEOP = 5;
        const int RELOADOP = 6;
        switch (operationTypeMap[operation.type]) {
            case ADDOP:
                OperateAdd(operation, initialIndex);
                break;
            case DELETEOP:
                OperateDelete(operation, initialIndex);
                break;
            case CHANGEOP:
                OperateChange(operation, initialIndex, cachedTemp, expiringTemp);
                break;
            case MOVEOP:
                OperateMove(operation, initialIndex, cachedTemp, expiringTemp);
                break;
            case EXCHANGEOP:
                OperateExchange(operation, initialIndex, cachedTemp, expiringTemp);
                break;
            case RELOADOP:
                OperateReload(operation, initialIndex);
                return true;
        }
        return false;
    }

    void LazyForEachBuilder::OperateAdd(V2::Operation& operation, int32_t& initialIndex)
    {
        OperationInfo itemInfo;
        auto indexExist = operationList_.find(operation.index);
        if (indexExist == operationList_.end()) {
            itemInfo.changeCount = operation.count;
            if (!operation.key.empty()) {
                itemInfo.extraKey.push_back(operation.key);
            } else if (operation.keyList.size() >= static_cast<size_t>(1)) {
                for (std::string key : operation.keyList) {
                    itemInfo.extraKey.push_back(key);
                }
            }
            initialIndex = std::min(initialIndex, operation.index);
            operationList_.try_emplace(operation.index, itemInfo);
        } else {
            ThrowRepeatOperationError(operation.index);
        }
    }

    void LazyForEachBuilder::OperateDelete(V2::Operation& operation, int32_t& initialIndex)
    {
        OperationInfo itemInfo;
        auto indexExist = operationList_.find(operation.index);
        if (indexExist == operationList_.end()) {
            itemInfo.changeCount = -operation.count;
            itemInfo.isDeleting = true;
            initialIndex = std::min(initialIndex, operation.index);
            operationList_.try_emplace(operation.index, itemInfo);
            for (int32_t i = operation.index + 1; i < operation.index + operation.count; i++) {
                OperationInfo extraInfo;
                if (operationList_.find(i) == operationList_.end()) {
                    extraInfo.isDeleting = true;
                    operationList_.try_emplace(i, extraInfo);
                } else {
                    ThrowRepeatOperationError(i);
                }
            }
        } else {
            ThrowRepeatOperationError(operation.index);
        }
    }

    void LazyForEachBuilder::OperateChange(V2::Operation& operation, int32_t& initialIndex,
        std::map<int32_t, LazyForEachChild>& cachedTemp, std::map<int32_t, LazyForEachChild>& expiringTemp)
    {
        OperationInfo itemInfo;
        auto indexExist = operationList_.find(operation.index);
        if (indexExist == operationList_.end()) {
            itemInfo.isChanged = true;
            auto iter = cachedTemp.find(operation.index);
            if (iter == cachedTemp.end()) {
                iter = expiringTemp.find(operation.index);
            }
            if (iter == expiringTemp.end()) {
                return;
            }
            if (!operation.key.empty()) {
                itemInfo.key = operation.key;
            } else {
                itemInfo.key = iter->second.first;
            }
            initialIndex = std::min(initialIndex, operation.index);
            operationList_.try_emplace(operation.index, itemInfo);
        } else {
            ThrowRepeatOperationError(operation.index);
        }
    }

    void LazyForEachBuilder::OperateMove(V2::Operation& operation, int32_t& initialIndex,
        std::map<int32_t, LazyForEachChild>& cachedTemp, std::map<int32_t, LazyForEachChild>& expiringTemp)
    {
        OperationInfo fromInfo;
        OperationInfo toInfo;
        auto fromIndexExist = operationList_.find(operation.coupleIndex.first);
        auto toIndexExist = operationList_.find(operation.coupleIndex.second);
        if (fromIndexExist == operationList_.end()) {
            fromInfo.changeCount = -1;
            fromInfo.isDeleting = true;
            initialIndex = std::min(initialIndex, operation.coupleIndex.first);
            operationList_.try_emplace(operation.coupleIndex.first, fromInfo);
        } else {
            ThrowRepeatOperationError(operation.coupleIndex.first);
        }
        if (toIndexExist == operationList_.end()) {
            toInfo.changeCount = 1;
            auto iter = cachedTemp.find(operation.coupleIndex.first);
            if (iter == cachedTemp.end()) {
                iter = expiringTemp.find(operation.coupleIndex.first);
            }
            if (iter == expiringTemp.end()) {
                return;
            }
            toInfo.node = iter->second.second;
            toInfo.moveIn = true;
            if (!operation.key.empty()) {
                toInfo.key = operation.key;
            } else {
                toInfo.key = iter->second.first;
            }
            initialIndex = std::min(initialIndex, operation.coupleIndex.second);
            operationList_.try_emplace(operation.coupleIndex.second, toInfo);
        } else {
            ThrowRepeatOperationError(operation.coupleIndex.second);
        }
    }

    void LazyForEachBuilder::OperateExchange(V2::Operation& operation, int32_t& initialIndex,
        std::map<int32_t, LazyForEachChild>& cachedTemp, std::map<int32_t, LazyForEachChild>& expiringTemp)
    {
        OperationInfo startInfo;
        OperationInfo endInfo;
        auto startIndexExist = operationList_.find(operation.coupleIndex.first);
        auto endIndexExist = operationList_.find(operation.coupleIndex.second);
        if (startIndexExist == operationList_.end()) {
            auto iter = cachedTemp.find(operation.coupleIndex.first);
            if (iter == cachedTemp.end()) {
                iter = expiringTemp.find(operation.coupleIndex.first);
            }
            if (iter == expiringTemp.end()) {
                return;
            }
            startInfo.node = iter->second.second;
            if (!operation.coupleKey.first.empty()) {
                startInfo.key = operation.coupleKey.first;
            } else {
                startInfo.key = iter->second.first;
            }
            initialIndex = std::min(initialIndex, operation.coupleIndex.second);
            operationList_.try_emplace(operation.coupleIndex.second, startInfo);
        } else {
            ThrowRepeatOperationError(operation.coupleIndex.first);
        }
        if (endIndexExist == operationList_.end()) {
            auto iter = cachedTemp.find(operation.coupleIndex.second);
            if (iter == cachedTemp.end()) {
                iter = expiringTemp.find(operation.coupleIndex.second);
            }
            if (iter == expiringTemp.end()) {
                return;
            }
            endInfo.node = iter->second.second;
            if (!operation.coupleKey.second.empty()) {
                endInfo.key = operation.coupleKey.second;
            } else {
                endInfo.key = iter->second.first;
            }
            initialIndex = std::min(initialIndex, operation.coupleIndex.first);
            operationList_.try_emplace(operation.coupleIndex.first, endInfo);
        } else {
            ThrowRepeatOperationError(operation.coupleIndex.second);
        }
    }

    void LazyForEachBuilder::OperateReload(V2::Operation& operation, int32_t& initialIndex)
    {
        operationList_.clear();
        OnDataReloaded();
    }

    void LazyForEachBuilder::ThrowRepeatOperationError(int32_t index)
    {
        TAG_LOGE(AceLogTag::ACE_LAZY_FOREACH, "Repeat Operation for index: %{public}d", index);
    }

    void LazyForEachBuilder::RecycleChildByIndex(int32_t index)
    {
        auto iter = cachedItems_.find(index);
        if (iter != cachedItems_.end()) {
            if (!iter->second.second) {
                return;
            }
            auto dummyNode = AceType::DynamicCast<RecycleDummyNode>(iter->second.second);
            if (!dummyNode) {
                return;
            }
            auto keyIter = expiringItem_.find(iter->second.first);
            if (keyIter != expiringItem_.end() && keyIter->second.second) {
                expiringItem_.erase(keyIter);
            }
            cachedItems_.erase(index);
        }
    }

    void LazyForEachBuilder::RecordOutOfBoundaryNodes(int32_t index)
    {
        outOfBoundaryNodes_.emplace_back(index);
    }

    void LazyForEachBuilder::RecycleItemsOutOfBoundary()
    {
        for (const auto& i: outOfBoundaryNodes_) {
            RecycleChildByIndex(i);
        }
        outOfBoundaryNodes_.clear();
    }
}
