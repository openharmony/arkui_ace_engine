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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_LAZY_FOR_EACH_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_LAZY_FOR_EACH_NODE_H

#include <list>
#include <optional>
#include <string>

#include "base/utils/utils.h"
#include "core/common/resource/resource_configuration.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/syntax/for_each_base_node.h"
#include "core/components_ng/syntax/lazy_for_each_builder.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT LazyForEachNode : public ForEachBaseNode, public V2::DataChangeListener {
    DECLARE_ACE_TYPE(LazyForEachNode, ForEachBaseNode, DataChangeListener);

public:
    static RefPtr<LazyForEachNode> GetOrCreateLazyForEachNode(
        int32_t nodeId, const RefPtr<LazyForEachBuilder>& forEachBuilder);

    static RefPtr<LazyForEachNode> CreateLazyForEachNode(
        int32_t nodeId, const RefPtr<LazyForEachBuilder>& forEachBuilder);

    LazyForEachNode(int32_t nodeId, const RefPtr<LazyForEachBuilder>& forEachBuilder)
        : ForEachBaseNode(V2::JS_LAZY_FOR_EACH_ETS_TAG, nodeId, false), builder_(forEachBuilder) {}

    ~LazyForEachNode() override;

    void OnDelete() override;

    bool IsAtomicNode() const override
    {
        return false;
    }

    int32_t FrameCount() const override
    {
        return builder_ ? builder_->GetTotalCount() : 0;
    }

    void NotifyColorModeChange(uint32_t colorMode) override;

    void AdjustLayoutWrapperTree(const RefPtr<LayoutWrapperNode>& parent, bool forceMeasure, bool forceLayout) override;

    void UpdateLazyForEachItems(int32_t newStartIndex, int32_t newEndIndex,
        std::list<std::optional<std::string>>&& nodeIds,
        std::unordered_map<int32_t, std::optional<std::string>>&& cachedItems);

    void OnDataReloaded() override;
    void OnDataAdded(size_t index) override;
    void OnDataBulkAdded(size_t index, size_t count) override;
    void OnDataDeleted(size_t index) override;
    void OnDataBulkDeleted(size_t index, size_t count) override;
    void OnDataChanged(size_t index) override;
    void OnDataMoved(size_t from, size_t to) override;
    void OnDatasetChange(const std::list<V2::Operation>& DataOperations) override;

    void OnDataBulkChanged(size_t index, size_t count) override;
    void OnDataMoveToNewPlace(size_t from, size_t to) override;

    void PostIdleTask(std::list<int32_t>&& items, const std::optional<LayoutConstraintF>& itemConstraint = std::nullopt,
        bool longPredictTask = false);

    void SetRequestLongPredict(bool requestLongPredict)
    {
        requestLongPredict_ = requestLongPredict;
    }

    void SetFlagForGeneratedItem(PropertyChangeFlag propertyChangeFlag)
    {
        builder_->SetFlagForGeneratedItem(propertyChangeFlag);
    }

    void SetIsLoop(bool isLoop)
    {
        isLoop_ = isLoop;
        if (builder_) {
            builder_->SetIsLoop(isLoop);
        }
    }

    bool GetIsLoop() const
    {
        return isLoop_;
    }
    void PostIdleTask();
    void OnConfigurationUpdate(const ConfigurationChange& configurationChange) override;
    void MarkNeedSyncRenderTree(bool needRebuild = false) override;

    void BuildAllChildren();
    RefPtr<UINode> GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache = false,
        bool addToRenderTree = false) override;
    void DoRemoveChildInRenderTree(uint32_t index, bool isAll) override;
    void DoSetActiveChildRange(
        int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache = false) override;

    const std::list<RefPtr<UINode>>& GetChildren(bool notDetach = false) const override;
    void LoadChildren(bool notDetach) const;

    const std::list<RefPtr<UINode>>& GetChildrenForInspector(bool needCacheNode = false) const override;

    void OnSetCacheCount(int32_t cacheCount, const std::optional<LayoutConstraintF>& itemConstraint) override
    {
        itemConstraint_ = itemConstraint;
        if (builder_) {
            builder_->SetCacheCount(cacheCount);
        }
    }
    void SetJSViewActive(bool active = true, bool isLazyForEachNode = false, bool isReuse = false) override
    {
        if (builder_) {
            builder_->SetJSViewActive(active);
            isActive_ = active;
        }
    }
    void SetDestroying(bool isDestroying = true, bool cleanStatus = true) override
    {
        if (builder_) {
            builder_->SetDestroying(isDestroying, cleanStatus);
        }
    }
    void PaintDebugBoundaryTreeAll(bool flag) override
    {
        if (builder_) {
            builder_->PaintDebugBoundaryTreeAll(flag);
        }
    }
    int32_t GetIndexByUINode(const RefPtr<UINode>& uiNode) const;
    void SetNodeIndexOffset(int32_t start, int32_t count) override
    {
        startIndex_ = start;
        count_ = count;
    }
    void RecycleItems(int32_t from, int32_t to) override;

    const RefPtr<LazyForEachBuilder>& GetBuilder() const
    {
        return builder_;
    }

    void RegisterBuilderListener() {
        CHECK_NULL_VOID(builder_);
        if (!isRegisterListener_) {
            builder_->RegisterDataChangeListener(Claim(this));
            isRegisterListener_ = true;
        }
    }

    void SetItemDragHandler(std::function<void(int32_t)>&& onLongPress, std::function<void(int32_t)>&& onDragStart,
        std::function<void(int32_t, int32_t)>&& onMoveThrough, std::function<void(int32_t)>&& onDrop);
    void SetOnMove(std::function<void(int32_t, int32_t)>&& onMove);
    void MoveData(int32_t from, int32_t to) override;
    void FireOnMove(int32_t from, int32_t to) override;
    RefPtr<FrameNode> GetFrameNode(int32_t index) override;
    int32_t GetFrameNodeIndex(const RefPtr<FrameNode>& node, bool isExpanded = true) override;
    void InitDragManager(const RefPtr<FrameNode>& childNode);
    void InitAllChilrenDragManager(bool init);

    /**
     * @brief Notify the change of dataSource to parent.
     *
     * @param index the position of change.
     * @param count the count of change in [index].
     * @param notificationType the type of notification.
     */
    void NotifyChangeWithCount(int32_t index, int32_t count, NotificationType notificationType) const;

    /**
     * @brief Parse OnDatasetChange for NotifyCountChange.
     *
     * @param dataOperations bulk change operations.
     */
    void ParseOperations(const std::list<V2::Operation>& dataOperations);

    void EnablePreBuild(bool enable);
protected:
    void UpdateChildrenFreezeState(bool isFreeze, bool isForceUpdateFreezeVaule = false) override;
private:
    void OnAttachToMainTree(bool recursive) override
    {
        UINode::OnAttachToMainTree(recursive);
        RegisterBuilderListener();
        if (builder_) {
            for (const auto& item : builder_->GetCachedUINodeMap()) {
                if (item.second.second != nullptr) {
                    builder_->ProcessOffscreenNode(item.second.second, false);
                }
            }
        }
    }

    void OnDetachFromMainTree(bool recursive, PipelineContext* context = nullptr) override
    {
        UINode::OnDetachFromMainTree(recursive, context);
        if (builder_) {
            auto tempExpiringItem = builder_->GetCachedUINodeMap();
            for (const auto& [key, child] : tempExpiringItem) {
                if (child.second != nullptr) {
                    child.second->DetachFromMainTree(recursive);
                    builder_->ProcessOffscreenNode(child.second, true);
                }
            }
        }
    }

    void OnOffscreenProcess(bool recursive) override
    {
        UINode::OnOffscreenProcess(recursive);
        RegisterBuilderListener();
    }

    void OnGenerateOneDepthVisibleFrameWithTransition(std::list<RefPtr<FrameNode>>& visibleList) override
    {
        // LazyForEachNode::GetChildren() may add some children to disappearingChildren_, execute earlier to ensure
        // disappearingChildren_ is correct before calling GenerateOneDepthVisibleFrameWithTransition.
        GetChildren();
        UINode::GenerateOneDepthVisibleFrameWithTransition(visibleList);
    }

    // The index values of the start and end of the current children nodes and the corresponding keys.
    std::list<std::optional<std::string>> ids_;
    std::list<int32_t> predictItems_;
    std::optional<LayoutConstraintF> itemConstraint_;
    bool requestLongPredict_ = true;
    bool isRegisterListener_ = false;
    bool isLoop_ = false;

    mutable std::list<RefPtr<UINode>> tempChildren_;
    mutable std::list<RefPtr<UINode>> children_;
    mutable bool needPredict_ = false;
    mutable std::list<RefPtr<UINode>> childrenWithCache_;
    bool needMarkParent_ = true;
    bool isActive_ = true;
    int32_t startIndex_ = 0;
    int32_t count_ = 0;

    RefPtr<LazyForEachBuilder> builder_;

    ACE_DISALLOW_COPY_AND_MOVE(LazyForEachNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_LAZY_FOR_EACH_NODE_H