/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_WRAPPER_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_WRAPPER_NODE_H

#include <map>
#include <optional>
#include <string>
#include <unordered_map>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/thread/cancelable_callback.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/property/geometry_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/magic_layout_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/position_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
class FrameNode;
class LayoutWrapperNode;

using LazyBuildFunction = std::function<void(RefPtr<LayoutWrapperNode>)>;

class ACE_EXPORT LayoutWrapperNode : public LayoutWrapper {
    DECLARE_ACE_TYPE(LayoutWrapperNode, LayoutWrapper);
public:
    LayoutWrapperNode(
        WeakPtr<FrameNode> hostNode, RefPtr<GeometryNode> geometryNode, RefPtr<LayoutProperty> layoutProperty);

    LayoutWrapperNode(LazyBuildFunction&& fun)
        : LayoutWrapper(nullptr), geometryNode_(MakeRefPtr<GeometryNode>()),
          layoutProperty_(MakeRefPtr<LayoutProperty>()), lazyBuildFunction_(fun)
    {}
    ~LayoutWrapperNode() override = default;

    void Update(WeakPtr<FrameNode> hostNode, RefPtr<GeometryNode> geometryNode, RefPtr<LayoutProperty> layoutProperty);

    void AppendChild(const RefPtr<LayoutWrapperNode>& child, bool isOverlayNode = false);

    void SetLayoutWrapperBuilder(const RefPtr<LayoutWrapperBuilder>& builder)
    {
        CHECK_NULL_VOID(builder);
        builder->SetStartIndex(currentChildCount_);
        currentChildCount_ += builder->GetTotalCount();
        layoutWrapperBuilder_ = builder;
    }

    void SetLayoutAlgorithm(const RefPtr<LayoutAlgorithmWrapper>& layoutAlgorithm)
    {
        layoutAlgorithm_ = layoutAlgorithm;
    }

    const RefPtr<LayoutAlgorithmWrapper>& GetLayoutAlgorithm(bool needReset = false) override
    {
        return layoutAlgorithm_;
    }

    // This will call child and self measure process.
    void Measure(const std::optional<LayoutConstraintF>& parentConstraint) override;

    // Called to perform layout children.
    void Layout() override;

    const RefPtr<GeometryNode>& GetGeometryNode() const override
    {
        return geometryNode_;
    }

    const RefPtr<LayoutProperty>& GetLayoutProperty() const override
    {
        return layoutProperty_;
    }

    // Calling these two method will mark the node as in use by default, nodes marked as use state will be added to the
    // render area, and nodes in the render area will be mounted on the render tree after the layout is complete. You
    // can call the RemoveChildInRenderTree method to explicitly remove the node from the area to be rendered.
    RefPtr<LayoutWrapper> GetOrCreateChildByIndex(
        uint32_t index, bool addToRenderTree = true, bool isCache = false) override;
    ChildrenListWithGuard GetAllChildrenWithBuild(bool addToRenderTree = true) override;
    RefPtr<LayoutWrapper> GetChildByIndex(uint32_t index, bool isCache = false) override
    {
        return nullptr;
    }

    int32_t GetTotalChildCount() const override
    {
        return currentChildCount_;
    }

    std::list<RefPtr<FrameNode>> GetChildrenInRenderArea() const;

    void RemoveChildInRenderTree(uint32_t index) override;
    void RemoveAllChildInRenderTree() override;
    void SetActiveChildRange(
        int32_t start, int32_t end, int32_t cacheStart = 0, int32_t cacheEnd = 0, bool showCached = false) override
    {}
    void RecycleItemsByIndex(int32_t start, int32_t end) override {}

    void ResetHostNode();

    const std::string& GetHostTag() const override;
    int32_t GetHostDepth() const;

    bool IsActive() const override
    {
        return isActive_;
    }

    void SetActive(bool active = true, bool needRebuildRenderContext = false) override
    {
        isActive_ = active;
    }

    bool IsRootMeasureNode() const
    {
        return isRootNode_;
    }

    void SetRootMeasureNode()
    {
        isRootNode_ = true;
    }

    bool CheckShouldRunOnMain() override
    {
        return (CanRunOnWhichThread() & MAIN_TASK) == MAIN_TASK;
    }

    TaskThread CanRunOnWhichThread()
    {
        if (layoutWrapperBuilder_) {
            return MAIN_TASK;
        }
        TaskThread taskThread = UNDEFINED_TASK;
        if (layoutAlgorithm_) {
            taskThread = taskThread | layoutAlgorithm_->CanRunOnWhichThread();
        }
        if ((taskThread & MAIN_TASK) == MAIN_TASK) {
            return MAIN_TASK;
        }
        for (const auto& child : children_) {
            taskThread = taskThread | child->CanRunOnWhichThread();
        }
        return taskThread;
    }

    bool SkipMeasureContent() const override;

    bool ConstraintChanged() const
    {
        return !isConstraintNotChanged_;
    }

    // dirty layoutBox mount to host and switch layoutBox.
    // Notice: only the cached layoutWrapper (after call GetChildLayoutWrapper) will update the host.
    void MountToHostOnMainThread();
    void SwapDirtyLayoutWrapperOnMainThread();
    void SwapDirtyLayoutWrapperOnMainThreadForChild(RefPtr<LayoutWrapperNode> child);

    bool IsForceSyncRenderTree() const
    {
        return needForceSyncRenderTree_;
    }

    float GetBaselineDistance() const override
    {
        if (children_.empty()) {
            return geometryNode_->GetBaselineDistance();
        }
        float distance = 0.0;
        for (const auto& child : children_) {
            float childBaseline = child->GetBaselineDistance();
            distance = NearZero(distance) ? childBaseline : std::min(distance, childBaseline);
        }
        return distance;
    }

    bool IsOutOfLayout() const override
    {
        return outOfLayout_;
    }

    void SetOutOfLayout(bool outOfLayout)
    {
        outOfLayout_ = outOfLayout;
    }

    // Check the flag attribute with descendant node
    bool CheckNeedForceMeasureAndLayout() override;

    bool CheckChildNeedForceMeasureAndLayout();

    void SetCacheCount(
        int32_t cacheCount = 0, const std::optional<LayoutConstraintF>& itemConstraint = std::nullopt) override;

    void BuildLazyItem() override;

    std::pair<int32_t, int32_t> GetLazyBuildRange();
    void SetLongPredictTask() override;

private:
    void Build(bool addToRenderTree);
    void LayoutOverlay();
    // Used to save a persist wrapper created by child, ifElse, ForEach, the map stores [index, Wrapper].
    std::list<RefPtr<LayoutWrapperNode>> children_;
    // Speed up the speed of getting child by index.
    std::unordered_map<int32_t, RefPtr<LayoutWrapperNode>> childrenMap_;
    RefPtr<LayoutWrapperNode> overlayChild_;
    // cached for GetAllChildrenWithBuild function.
    std::list<RefPtr<LayoutWrapper>> cachedList_;

    // The Wrapper Created by LazyForEach stores in the LayoutWrapperBuilder object.
    RefPtr<LayoutWrapperBuilder> layoutWrapperBuilder_;

    RefPtr<GeometryNode> geometryNode_;
    RefPtr<LayoutProperty> layoutProperty_;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithm_;

    int32_t currentChildCount_ = 0;
    bool isActive_ = false;
    bool needForceSyncRenderTree_ = false;
    bool isRootNode_ = false;
    std::optional<bool> skipMeasureContent_;
    std::optional<bool> needForceMeasureAndLayout_;

    LazyBuildFunction lazyBuildFunction_;

    // When the location property is set, it departs from the layout flow.
    bool outOfLayout_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(LayoutWrapperNode);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_WRAPPER_NODE_H
