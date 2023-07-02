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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_WRAPPER_H

#include <map>
#include <optional>
#include <string>
#include <unordered_map>

#include "base/memory/referenced.h"
#include "base/thread/cancelable_callback.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
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

using LazyBuildFunction = std::function<void(RefPtr<LayoutWrapper>)>;

class ACE_FORCE_EXPORT LayoutWrapper : public AceType {
    DECLARE_ACE_TYPE(LayoutWrapper, AceType)
public:
    LayoutWrapper(
        WeakPtr<FrameNode> hostNode, RefPtr<GeometryNode> geometryNode, RefPtr<LayoutProperty> layoutProperty);
    LayoutWrapper(LazyBuildFunction&& fun)
        : geometryNode_(MakeRefPtr<GeometryNode>()), layoutProperty_(MakeRefPtr<LayoutProperty>()),
          lazyBuildFunction_(fun)
    {}
    ~LayoutWrapper() override = default;

    void Update(WeakPtr<FrameNode> hostNode, RefPtr<GeometryNode> geometryNode, RefPtr<LayoutProperty> layoutProperty);

    void AppendChild(const RefPtr<LayoutWrapper>& child, bool isOverlayNode = false);

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

    const RefPtr<LayoutAlgorithmWrapper>& GetLayoutAlgorithm() const
    {
        return layoutAlgorithm_;
    }

    // This will call child and self measure process.
    void Measure(const std::optional<LayoutConstraintF>& parentConstraint);

    // Called to perform layout children.
    void Layout();

    const RefPtr<GeometryNode>& GetGeometryNode() const
    {
        return geometryNode_;
    }

    const RefPtr<LayoutProperty>& GetLayoutProperty() const
    {
        return layoutProperty_;
    }

    // Calling these two method will mark the node as in use by default, nodes marked as use state will be added to the
    // render area, and nodes in the render area will be mounted on the render tree after the layout is complete. You
    // can call the RemoveChildInRenderTree method to explicitly remove the node from the area to be rendered.
    RefPtr<LayoutWrapper> GetOrCreateChildByIndex(int32_t index, bool addToRenderTree = true);
    const std::list<RefPtr<LayoutWrapper>>& GetAllChildrenWithBuild(bool addToRenderTree = true);

    int32_t GetTotalChildCount() const
    {
        return currentChildCount_;
    }

    std::list<RefPtr<FrameNode>> GetChildrenInRenderArea() const;

    static void RemoveChildInRenderTree(const RefPtr<LayoutWrapper>& wrapper);
    void RemoveChildInRenderTree(int32_t index);
    void RemoveAllChildInRenderTree();

    void ResetHostNode();

    RefPtr<FrameNode> GetHostNode() const;
    WeakPtr<FrameNode> GetWeakHostNode() const;
    std::string GetHostTag() const;
    int32_t GetHostDepth() const;

    bool IsActive() const
    {
        return isActive_;
    }

    void SetActive(bool active = true)
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

    bool CheckShouldRunOnMain()
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

    bool SkipMeasureContent() const;

    bool IsContraintNoChanged() const
    {
        return isConstraintNotChanged_;
    }

    // dirty layoutBox mount to host and switch layoutBox.
    // Notice: only the cached layoutWrapper (after call GetChildLayoutWrapper) will update the host.
    void MountToHostOnMainThread();
    void SwapDirtyLayoutWrapperOnMainThread();
    void SwapDirtyLayoutWrapperOnMainThreadForChild(RefPtr<LayoutWrapper> child);

    bool IsForceSyncRenderTree() const
    {
        return needForceSyncRenderTree_;
    }

    float GetBaselineDistance() const
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

    bool IsOutOfLayout() const
    {
        return outOfLayout_;
    }

    void SetOutOfLayout(bool outOfLayout)
    {
        outOfLayout_ = outOfLayout;
    }

    void SetIsOverlayNode(bool isOverlayNode)
    {
        isOverylayNode_ = isOverlayNode;
    }

    // ------------------------------------------------------------------------
    // performance check
    void AddNodeFlexLayouts();
    void AddNodeLayoutTime(int64_t time);
    // ------------------------------------------------------------------------

    // Check the flag attribute with descendant node
    bool CheckNeedForceMeasureAndLayout();

    bool CheckChildNeedForceMeasureAndLayout();

    void SetCacheCount(int32_t cacheCount = 0, const std::optional<LayoutConstraintF>& itemConstraint = std::nullopt);

    void SetLongPredictTask();

    void BuildLazyItem();

    std::pair<int32_t, int32_t> GetLazyBuildRange();

    static void ApplySafeArea(const SafeAreaInsets& insets, LayoutConstraintF& constraint);

    // apply keyboard avoidance on content rootNodes
    static void AvoidKeyboard();
    // expand the SafeArea of expansive nodes, which are previously recorded during Layout traversal
    static void ExpandSafeArea();

    // save geometry states before SafeArea expansion / keyboard avoidance
    static void SaveGeoState();
    // restore to the geometry state after last Layout and before SafeArea expansion and keyboard avoidance
    void RestoreGeoState();

private:
    void CreateRootConstraint();
    void ApplyConstraint(LayoutConstraintF constraint);

    void ExpandSafeAreaInner();
    // keyboard avoidance is done by offsetting, to expand into keyboard area, reverse the offset.
    void ExpandIntoKeyboard();
    void LayoutOverlay();

    // Used to save a persist wrapper created by child, ifElse, ForEach, the map stores [index, Wrapper].
    std::list<RefPtr<LayoutWrapper>> children_;
    // Speed up the speed of getting child by index.
    std::unordered_map<int32_t, RefPtr<LayoutWrapper>> childrenMap_;
    
    RefPtr<LayoutWrapper> overlayChild_;

    // cached for GetAllChildrenWithBuild function.
    std::list<RefPtr<LayoutWrapper>> cachedList_;

    // The Wrapper Created by LazyForEach stores in the LayoutWrapperBuilder object.
    RefPtr<LayoutWrapperBuilder> layoutWrapperBuilder_;

    WeakPtr<FrameNode> hostNode_;
    RefPtr<GeometryNode> geometryNode_;
    RefPtr<LayoutProperty> layoutProperty_;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithm_;

    int32_t currentChildCount_ = 0;
    bool isConstraintNotChanged_ = false;
    bool isActive_ = false;
    bool needForceSyncRenderTree_ = false;
    bool isRootNode_ = false;
    bool isOverylayNode_ = false;
    std::optional<bool> skipMeasureContent_;
    std::optional<bool> needForceMeasureAndLayout_;

    LazyBuildFunction lazyBuildFunction_;

    // When the location property is set, it departs from the layout flow.
    bool outOfLayout_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(LayoutWrapper);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_WRAPPER_H
