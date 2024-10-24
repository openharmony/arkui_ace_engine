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
            ACE_SCOPED_TRACE("Builder:BuildLazyItem [%d]", index);
            std::pair<std::string, RefPtr<UINode>> itemInfo;
            if (useNewInterface_) {
                itemInfo = OnGetChildByIndexNew(ConvertFormToIndex(index), cachedItems_, expiringItem_);
            } else {
                itemInfo = OnGetChildByIndex(ConvertFormToIndex(index), expiringItem_);
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
                node.first = node.first + static_cast<int32_t>(count);
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

        if (DeleteExpiringItemImmediately()) {
            decltype(expiringItem_) expiringTemp(std::move(expiringItem_));
            for (auto& [key, child] : expiringTemp) {
                if (child.first < 0) {
                    nodeList_.emplace_back(key, child.second);
                    continue;
                }
                if (static_cast<size_t>(child.first) >= index + count) {
                    child.first -= static_cast<int32_t>(count);
                    expiringItem_.try_emplace(key, child);
                    continue;
                }
                if (static_cast<size_t>(child.first) >= index && static_cast<size_t>(child.first) < index + count) {
                    nodeList_.emplace_back(key, child.second);
                } else {
                    expiringItem_.try_emplace(key, child);
                }
            }
        } else {
            for (auto& [key, child] : expiringItem_) {
                if (static_cast<size_t>(child.first) >= index + count) {
                    child.first -= static_cast<int32_t>(count);
                    continue;
                }
                if (static_cast<size_t>(child.first) >= index && static_cast<size_t>(child.first) < index + count) {
                    child.first = -1;
                }
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
        auto iter = cachedItems_.begin();
        while (iter != cachedItems_.end()) {
            auto itemIndex = iter->first;
            const auto& child = iter->second;
            if (static_cast<size_t>(itemIndex) >= index && static_cast<size_t>(itemIndex) < index + count) {
                NotifyDataChanged(index, child.second, false);
                nodeList_.emplace_back(child.first, child.second);
                iter = cachedItems_.erase(iter);
            } else {
                iter++;
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
                if (position > from && position <= to && position >= 1) {
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
            expiringItem_[fromIter->second.first] = LazyForEachCacheChild(to, std::move(fromIter->second.second));
            cachedItems_.erase(fromIter);
        } else if (toIter != cachedItems_.end()) {
            expiringItem_[toIter->second.first] = LazyForEachCacheChild(from, std::move(toIter->second.second));
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

    void LazyForEachBuilder::Transit(std::list<std::pair<std::string, RefPtr<UINode>>>& childList)
    {
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
    }

    std::map<int32_t, LazyForEachChild>& LazyForEachBuilder::GetItems(
        std::list<std::pair<std::string, RefPtr<UINode>>>& childList)
    {
        int32_t startIndex = -1;
        int32_t endIndex = -1;
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
                ACE_SYNTAX_SCOPED_TRACE("LazyForEach not active index[%d]", index);
                frameNode->SetJSViewActive(false, true);
                expiringItem_.try_emplace(node.first, LazyForEachCacheChild(index, std::move(node.second)));
                continue;
            }
            cachedItems_.try_emplace(index, std::move(node));
            if (startIndex == -1) {
                startIndex = index;
            }
            if (isLoop_) {
                if (isCertained) {
                    continue;
                }
                if (lastIndex > -1 && index - lastIndex > 1) {
                    startIndex = index;
                    endIndex = lastIndex;
                    isCertained = true;
                } else {
                    endIndex = std::max(endIndex, index);
                }
            } else {
                endIndex = std::max(endIndex, index);
            }
            lastIndex = index;
        }

        Transit(childList);

        if (startIndex != -1 && endIndex != -1) {
            startIndex_ = startIndex;
            endIndex_ = endIndex;
        }

        return cachedItems_;
    }

    /**
     * Application code normarlly manipulate datasource first then call OnDatasetChange. But there are cases that they
     * call OnDatasetChange first, then manipulate datasource. So the return of function "GetTotalCount" can both be
     * total count of current datasource(manipulate datasource first) and original datasource(call OnDatasetChange
     * first). We need to maintain historicalTotalCount_ to get total count of original datasource.
     */
    int32_t LazyForEachBuilder::GetTotalCountOfOriginalDataset()
    {
        int32_t totalCount = GetTotalCount();
        int32_t totalCountOfOriginalDataset = historicalTotalCount_;
        UpdateHistoricalTotalCount(totalCount);
        return totalCountOfOriginalDataset;
    }

    std::pair<int32_t, std::list<std::pair<std::string, RefPtr<UINode>>>> LazyForEachBuilder::OnDatasetChange(
        std::list<V2::Operation> DataOperations)
    {
        totalCountOfOriginalDataset_ = GetTotalCountOfOriginalDataset();
        int32_t initialIndex = totalCountOfOriginalDataset_;
        std::map<int32_t, LazyForEachChild> expiringTempItem_;
        std::list<std::string> expiringKeys;
        for (auto& [key, cacheChild] : expiringItem_) {
            if (cacheChild.first > -1) {
                expiringTempItem_.try_emplace(cacheChild.first, LazyForEachChild(key, cacheChild.second));
                expiringKeys.emplace_back(key);
            }
        }
        for (auto& key : expiringKeys) {
            expiringItem_.erase(key);
        }
        decltype(expiringTempItem_) expiringTemp(std::move(expiringTempItem_));
        for (auto operation : DataOperations) {
            bool isReload = ClassifyOperation(operation, initialIndex, cachedItems_, expiringTemp);
            if (isReload) {
                initialIndex = 0;
                return std::pair(initialIndex, nodeList_);
            }
        }
        decltype(cachedItems_) cachedTemp(std::move(cachedItems_));
        std::map<int32_t, int32_t> indexChangedMap;
        CollectIndexChangedCount(indexChangedMap);
        RepairDatasetItems(cachedTemp, cachedItems_, indexChangedMap);
        RepairDatasetItems(expiringTemp, expiringTempItem_, indexChangedMap);
        for (auto& [index, node] : expiringTempItem_) {
            if (node.second) {
                expiringItem_.emplace(node.first, LazyForEachCacheChild(index, node.second));
            }
        }
        operationList_.clear();
        return std::pair(initialIndex, nodeList_);
    }

    void LazyForEachBuilder::RepairDatasetItems(std::map<int32_t, LazyForEachChild>& cachedTemp,
        std::map<int32_t, LazyForEachChild>& expiringTempItem_, std::map<int32_t, int32_t>& indexChangedMap)
    {
        int32_t changedIndex = 0;
        for (auto& [index, child] : cachedTemp) {
            auto iter = indexChangedMap.find(index);
            if (iter == indexChangedMap.end()) {
                if (!indexChangedMap.empty()) {
                    iter--;
                    if (iter->first < index) {
                        changedIndex = iter->second;
                    }
                }
            } else {
                changedIndex = iter->second;
            }
            if (operationList_.find(index) == operationList_.end()) {
                expiringTempItem_.try_emplace(index + changedIndex, child);
                continue;
            }
            if (!indexChangedMap.empty()) {
                changedIndex = iter->second;
            }
            auto info = operationList_.find(index)->second;
            if (info.isDeleting) {
                nodeList_.emplace_back(child.first, child.second);
            } else if (info.isChanged) {
                expiringTempItem_.try_emplace(index + changedIndex, LazyForEachChild(info.key, nullptr));
            } else if (!info.extraKey.empty()) {
                expiringTempItem_.try_emplace(index + changedIndex, child);
                int32_t preChangedIndex = 0;
                auto preIter = indexChangedMap.find(index - 1);
                if (preIter != indexChangedMap.end()) {
                    preChangedIndex = preIter->second;
                }
                for (int32_t i = 0; i < static_cast<int32_t>(info.extraKey.size()); i++) {
                    expiringTempItem_.try_emplace(
                        index + preChangedIndex + i, LazyForEachChild(info.extraKey[i], nullptr));
                }
            } else if (info.moveIn || info.isExchange) {
                RepairMoveOrExchange(expiringTempItem_, info, child, index, changedIndex);
            } else {
                expiringTempItem_.try_emplace(index + changedIndex, child);
            }
        }
    }

    void LazyForEachBuilder::RepairMoveOrExchange(std::map<int32_t, LazyForEachChild>& expiringTempItem_,
        OperationInfo& info, LazyForEachChild& child, int32_t index, int32_t changedIndex)
    {
        if (info.isExchange) {
            // if the child will be exchanged with a null node, this child should be deleted
            if (info.node == nullptr && child.second != nullptr) {
                nodeList_.emplace_back(child.first, child.second);
            }
            // null node should not be put in expiringTempItem_ then expiringTempItem_
            if (info.node != nullptr) {
                expiringTempItem_.try_emplace(index + changedIndex, LazyForEachChild(info.key, info.node));
            }
            return;
        }
        if (info.moveIn) {
            int32_t fromIndex = index + changedIndex - 1;
            int32_t toIndex = index + changedIndex;
            if (info.fromDiffTo > 0) {
                fromIndex = index + changedIndex;
                toIndex = index + changedIndex - 1;
            }
            expiringTempItem_.try_emplace(toIndex, LazyForEachChild(info.key, info.node));
            expiringTempItem_.try_emplace(fromIndex, child);
        }
    }

    void LazyForEachBuilder::CollectIndexChangedCount(std::map<int32_t, int32_t>& indexChangedMap)
    {
        int32_t changedIndex = 0;
        for (auto& [index, operationInfo] : operationList_) {
            if (indexChangedMap.size() >= static_cast<size_t>(1)) {
                for (int32_t i = indexChangedMap.rbegin()->first + 1; i < index; i++) {
                    indexChangedMap.try_emplace(i, changedIndex);
                }
            }
            operationInfo.changeCount += changedIndex;
            changedIndex = operationInfo.changeCount;
            indexChangedMap.try_emplace(index, changedIndex);
        }
    }

    bool LazyForEachBuilder::ClassifyOperation(V2::Operation& operation, int32_t& initialIndex,
        std::map<int32_t, LazyForEachChild>& cachedTemp, std::map<int32_t, LazyForEachChild>& expiringTemp)
    {
        switch (operationTypeMap[operation.type]) {
            case OP::ADD:
                OperateAdd(operation, initialIndex);
                break;
            case OP::DEL:
                OperateDelete(operation, initialIndex);
                break;
            case OP::CHANGE:
                OperateChange(operation, initialIndex, cachedTemp, expiringTemp);
                break;
            case OP::MOVE:
                OperateMove(operation, initialIndex, cachedTemp, expiringTemp);
                break;
            case OP::EXCHANGE:
                OperateExchange(operation, initialIndex, cachedTemp, expiringTemp);
                break;
            case OP::RELOAD:
                OperateReload(expiringTemp);
                return true;
        }
        return false;
    }

    bool LazyForEachBuilder::ValidateIndex(int32_t index, const std::string& type)
    {
        bool isValid = true;
        if (operationTypeMap[type] == OP::ADD) {
            // for add operation, the index can equal totalCountOfOriginalDataset_
            isValid = index >= 0 && index <= totalCountOfOriginalDataset_;
        } else {
            isValid = index >= 0 && index < totalCountOfOriginalDataset_;
        }
        if (!isValid) {
            TAG_LOGE(
                AceLogTag::ACE_LAZY_FOREACH, "%{public}s(%{public}d) Operation is out of range", type.c_str(), index);
        }
        return isValid;
    }

    void LazyForEachBuilder::OperateAdd(V2::Operation& operation, int32_t& initialIndex)
    {
        OperationInfo itemInfo;
        if (!ValidateIndex(operation.index, operation.type)) {
            return;
        }
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
        if (!ValidateIndex(operation.index, operation.type)) {
            return;
        }
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
        if (!ValidateIndex(operation.index, operation.type)) {
            return;
        }
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
        if (!ValidateIndex(operation.coupleIndex.first, operation.type) ||
            !ValidateIndex(operation.coupleIndex.second, operation.type)) {
            return;
        }
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
            toInfo.fromDiffTo = operation.coupleIndex.first - operation.coupleIndex.second;
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
        if (!ValidateIndex(operation.coupleIndex.first, operation.type) ||
            !ValidateIndex(operation.coupleIndex.second, operation.type)) {
            return;
        }
        auto startIndexExist = operationList_.find(operation.coupleIndex.first);
        auto endIndexExist = operationList_.find(operation.coupleIndex.second);
        if (startIndexExist == operationList_.end()) {
            auto iter = FindItem(operation.coupleIndex.first, cachedTemp, expiringTemp);
            // if item can't be find in cachedItems_ nor expiringItem_, set UI node to null
            if (iter == expiringTemp.end()) {
                startInfo.node = nullptr;
            } else {
                startInfo.node = iter->second.second;
                if (!operation.coupleKey.first.empty()) {
                    startInfo.key = operation.coupleKey.first;
                } else {
                    startInfo.key = iter->second.first;
                }
            }
            startInfo.isExchange = true;
            initialIndex = std::min(initialIndex, operation.coupleIndex.second);
            operationList_.try_emplace(operation.coupleIndex.second, startInfo);
        } else {
            ThrowRepeatOperationError(operation.coupleIndex.first);
        }
        if (endIndexExist == operationList_.end()) {
            auto iter = FindItem(operation.coupleIndex.second, cachedTemp, expiringTemp);
            // if item can't be find in cachedItems_ nor expiringItem_, set UI node to null
            if (iter == expiringTemp.end()) {
                endInfo.node = nullptr;
            } else {
                endInfo.node = iter->second.second;
                if (!operation.coupleKey.second.empty()) {
                    endInfo.key = operation.coupleKey.second;
                } else {
                    endInfo.key = iter->second.first;
                }
            }
            endInfo.isExchange = true;
            initialIndex = std::min(initialIndex, operation.coupleIndex.first);
            operationList_.try_emplace(operation.coupleIndex.first, endInfo);
        } else {
            ThrowRepeatOperationError(operation.coupleIndex.second);
        }
    }

    std::map<int32_t, LazyForEachChild>::iterator LazyForEachBuilder::FindItem(int32_t index,
        std::map<int32_t, LazyForEachChild>& cachedTemp, std::map<int32_t, LazyForEachChild>& expiringTemp)
    {
        auto iterOfCached = cachedTemp.find(index);
        auto iterOfExpiring = expiringTemp.find(index);
        // if UI node can't be find in cachedTemp, find it in expiringTemp
        if (iterOfCached == cachedTemp.end() || iterOfCached->second.second == nullptr) {
            return iterOfExpiring;
        } else {
            return iterOfCached;
        }
    }

    void LazyForEachBuilder::OperateReload(std::map<int32_t, LazyForEachChild>& expiringTemp)
    {
        for (auto& [index, node] : expiringTemp) {
            expiringItem_.emplace(node.first, LazyForEachCacheChild(index, node.second));
        }
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

    bool LazyForEachBuilder::PreBuild(int64_t deadline, const std::optional<LayoutConstraintF>& itemConstraint,
        bool canRunLongPredictTask)
    {
        ACE_SYNTAX_SCOPED_TRACE("expiringItem_ count:[%zu]", expiringItem_.size());
        outOfBoundaryNodes_.clear();
        if (itemConstraint && !canRunLongPredictTask) {
            return false;
        }
        auto count = OnGetTotalCount();
        std::unordered_map<std::string, LazyForEachCacheChild> cache;
        std::set<int32_t> idleIndexes;
        // if List contains a mixture of ListItem, LazyForeach, and Foreach...
        // Then both startIndex_ and endIndex_ can be -1
        CheckCacheIndex(idleIndexes, count);

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

    void LazyForEachBuilder::UpdateMoveFromTo(int32_t from, int32_t to)
    {
        if (moveFromTo_) {
            moveFromTo_.value().second = to;
        } else {
            moveFromTo_ = { from, to };
        }
    }

    void LazyForEachBuilder::ResetMoveFromTo()
    {
        moveFromTo_.reset();
    }

    int32_t LazyForEachBuilder::ConvertFormToIndex(int32_t index)
    {
        if (!moveFromTo_) {
            return index;
        }
        if (moveFromTo_.value().second == index) {
            return moveFromTo_.value().first;
        }
        if (moveFromTo_.value().first <= index && index < moveFromTo_.value().second) {
            return index + 1;
        }
        if (moveFromTo_.value().second < index && index <= moveFromTo_.value().first) {
            return index - 1;
        }
        return index;
    }
}
