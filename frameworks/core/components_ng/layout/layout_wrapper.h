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

#include <list>
#include <memory>
#include <string>
#include <utility>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/thread/cancelable_callback.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/geometry_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/magic_layout_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/position_property.h"
#include "core/pipeline_ng/ui_node_id.h"

namespace OHOS::Ace::NG {

class FrameNode;

class LayoutWrapper : public virtual Referenced {
public:
    LayoutWrapper(WeakPtr<FrameNode> hostNode, RefPtr<GeometryNode> geometryNode, RefPtr<LayoutProperty> layoutProperty)
        : hostNode_(std::move(hostNode)), geometryNode_(std::move(geometryNode)),
          layoutProperty_(std::move(layoutProperty))
    {}
    ~LayoutWrapper() override = default;

    void Reset();

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

    void ReplaceChildren(std::list<RefPtr<LayoutWrapper>>&& children)
    {
        children_ = std::move(children);
    }

    void AddChild(const RefPtr<LayoutWrapper>& child, int32_t slot = -1);

    void RemoveChild(const RefPtr<LayoutWrapper>& child);

    void ClearChildren();

    const std::list<RefPtr<LayoutWrapper>>& GetChildren() const
    {
        return children_;
    }

    void ResetHostNode();

    RefPtr<FrameNode> GetHostNode() const;

    std::string GetHostTag() const;

    // dirty layoutBox mount to host and switch layoutBox.
    void MountToHostOnUiThread();
    void SwapDirtyLayoutWrapperFromUiThread();

private:
    std::list<RefPtr<LayoutWrapper>> children_;
    WeakPtr<FrameNode> hostNode_;
    RefPtr<GeometryNode> geometryNode_;
    RefPtr<LayoutProperty> layoutProperty_;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithm_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_WRAPPER_H
