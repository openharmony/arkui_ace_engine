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
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/property/geometry_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/magic_layout_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/position_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class FrameNode;

class LayoutWrapper : public AceType {
    DECLARE_ACE_TYPE(LayoutWrapper, AceType)
public:
    LayoutWrapper(WeakPtr<FrameNode> hostNode, RefPtr<GeometryNode> geometryNode, RefPtr<LayoutProperty> layoutProperty)
        : hostNode_(std::move(hostNode)), geometryNode_(std::move(geometryNode)),
          layoutProperty_(std::move(layoutProperty))
    {}
    ~LayoutWrapper() override = default;

    void AppendChild(const RefPtr<LayoutWrapper>& child, int32_t slot = -1)
    {
        CHECK_NULL_VOID(child);
        auto result = children_.try_emplace(currentChildCount_, child);
        if (!result.second) {
            LOGE("fail to append child");
            return;
        }
        ++currentChildCount_;
    }

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
    void Layout(const std::optional<OffsetF>& parentGlobalOffset);

    const RefPtr<GeometryNode>& GetGeometryNode() const
    {
        return geometryNode_;
    }

    RefPtr<GeometryNode> MoveGeometryNode()
    {
        return std::move(geometryNode_);
    }

    const RefPtr<LayoutProperty>& GetLayoutProperty() const
    {
        return layoutProperty_;
    }

    // Calling these two method will mark the node as in use by default, nodes marked as use state will be added to the
    // render area, and nodes in the render area will be mounted on the render tree after the layout is complete. You
    // can call the RemoveChildInRenderTree method to explicitly remove the node from the area to be rendered.
    RefPtr<LayoutWrapper> GetOrCreateChildByIndex(int32_t index, bool addToRenderTree = true);
    std::list<RefPtr<LayoutWrapper>> GetAllChildrenWithBuild(bool addToRenderTree = true);
    int32_t GetTotalChildCount() const
    {
        return currentChildCount_;
    }

    std::list<RefPtr<FrameNode>> GetChildrenInRenderArea() const;

    void RemoveChildInRenderTree(const RefPtr<LayoutWrapper>& wrapper);
    void RemoveChildInRenderTree(int32_t index);

    void ResetHostNode();

    RefPtr<FrameNode> GetHostNode() const;
    std::string GetHostTag() const;

    bool IsActive() const
    {
        return isActive_;
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
        for (const auto& [index, child] : children_) {
            taskThread = taskThread | child->CanRunOnWhichThread();
        }
        return taskThread;
    }

    bool SkipMeasureContent() const;

    bool IsContraintNoChanged() const
    {
        return isContraintNoChanged_;
    }

    // dirty layoutBox mount to host and switch layoutBox.
    // Notice: only the cached layoutWrapper (after call GetChildLayoutWrapper) will update the host.
    void MountToHostOnMainThread();
    void SwapDirtyLayoutWrapperOnMainThread();

    bool IsForceSyncRenderTree() const
    {
        return needForceSyncRenderTree_;
    }

    void SetForceSyncRenderTree()
    {
        needForceSyncRenderTree_ = true;
    }

private:
    // Used to save a persist wrapper created by child, ifElse, ForEach, the map stores [index, Wrapper].
    // The Wrapper Created by LazyForEach stores in the LayoutWrapperBuilder object.
    std::map<int32_t, RefPtr<LayoutWrapper>> children_;
    std::map<int32_t, RefPtr<LayoutWrapper>> pendingRender_;
    WeakPtr<FrameNode> hostNode_;
    RefPtr<GeometryNode> geometryNode_;
    RefPtr<LayoutProperty> layoutProperty_;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithm_;
    RefPtr<LayoutWrapperBuilder> layoutWrapperBuilder_;

    int32_t currentChildCount_ = 0;
    bool isContraintNoChanged_ = false;
    bool isActive_ = false;
    bool needForceSyncRenderTree_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(LayoutWrapper);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_WRAPPER_H
