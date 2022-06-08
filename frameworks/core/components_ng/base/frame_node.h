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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_FRAME_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_FRAME_NODE_H

#include <atomic>
#include <list>
#include <memory>
#include <mutex>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/thread/cancelable_callback.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/element_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/render_context.h"
#include "core/components_ng/render/render_property.h"
#include "core/components_ng/render/render_wrapper.h"
#include "core/components_v2/inspector/inspector_node.h"

namespace OHOS::Ace::NG {
class Pattern;
class StateModifyTask;

constexpr int32_t DEFAULT_FRAME_SLOT = -1;

using LayoutTask = CancelableCallback<void()>;
using RenderTask = CancelableCallback<void()>;

// FrameNode will display rendering region in the screen.
class ACE_EXPORT FrameNode : public ElementNode {
    DECLARE_ACE_TYPE(FrameNode, ElementNode);

public:
    // create a new child element and mount to element tree.
    static RefPtr<FrameNode> CreateFrameNodeAndMounToParent(
        const std::string& tag, const RefPtr<Pattern>& pattern, const RefPtr<ElementNode>& parent, int32_t slot);

    // create a new child element with new element tree.
    static RefPtr<FrameNode> CreateFrameNodeWithTree(
        const std::string& tag, const RefPtr<Pattern>& pattern, const RefPtr<PipelineContext>& context);

    // create a new element with new pattern.
    static RefPtr<FrameNode> CreateFrameNode(
        const std::string& tag, const RefPtr<Pattern>& pattern, bool isRoot = false);

    // avoid use creator function, use CreateFrameNode
    FrameNode(const std::string& tag, const RefPtr<Pattern>& pattern, bool isRoot = false);
    ~FrameNode() override;

    // tree operations start
    void AddFrameChild(const RefPtr<FrameNode>& child, int32_t slot = -1);

    void RemoveFrameChild(const RefPtr<FrameNode>& child);

    void MoveFramePosition(int32_t slot);

    void ClearFrameChildren();

    // unmount from render tree
    void Unmount()
    {
        auto parent = frameParent_.Upgrade();
        if (parent) {
            parent->RemoveFrameChild(AceType::Claim(this));
        }
    }

    void SetFrameParent(const WeakPtr<FrameNode>& parent)
    {
        frameParent_ = parent;
    }

    WeakPtr<FrameNode> GetFrameParent() const
    {
        return frameParent_;
    }

    const std::list<RefPtr<FrameNode>>& GetFrameChildren() const
    {
        return frameChildren_;
    }

    const std::list<RefPtr<FrameNode>>& GetFrameChildrenByZIndex() const
    {
        return frameChildren_;
    }
    // tree operations end

    void FlushModifyTask(StateModifyTask& stateModifyTask);

    std::shared_ptr<LayoutTask> CreateLayoutTask();

    std::shared_ptr<LayoutTask> CreateRenderTask();

    void UpdateLayoutConstraint(const MeasureProperty& calcLayoutConstraint);

    const RefPtr<RenderContext>& GetRenderContext() const
    {
        return renderContext_;
    }

    const RefPtr<Pattern>& GetPattern() const;

    // Called on multi thread.
    RefPtr<GeometryNode> GetGeometryNodeSafe()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return geometryNode_;
    }

    void SetFrameSlot(int32_t slot)
    {
        frameSlot_ = slot;
    }

    int32_t GetFrameSlot() const
    {
        return frameSlot_;
    }

    const RefPtr<LayoutProperty>& GetLayoutProperty() const
    {
        return layoutProperty_;
    }

    void PostUITask(std::function<void()>&& task);

    // ui thread options
    void SwapDirtyLayoutWrapperFromUiThread(const RefPtr<LayoutWrapper>& dirty);
    void RebuildRenderContextTree();
    RefPtr<GeometryNode> GetGeometryNode() const
    {
        return geometryNode_;
    }
    void SetGeometryNode(RefPtr<GeometryNode>&& node)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        geometryNode_.Swap(std::move(node));
    }

private:
    void UpdateLayoutPropertyFlag();
    RefPtr<LayoutWrapper> CreateLayoutWrapper(bool forceMeasure = false, bool forceLayout = false);
    void UpdateChildrenLayoutWrapper(const RefPtr<LayoutWrapper>& self);
    std::optional<LayoutConstraintF> GetLayoutConstraint() const;
    std::optional<OffsetF> GetParentGlobalOffset() const;

    RefPtr<RenderWrapper> CreateRenderWrapper();

    void MarkDirtyRender(bool forceParent = true);
    void MarkDirtyLayoutBox(PropertyChangeFlag propertyChangeFlag = PROPERTY_UPDATE_NORMAL);
    void MarkDirtyLayoutBox(bool selfOnly, PropertyChangeFlag propertyChangeFlag);

    void OnDepthUpdate() override;
    bool IsMeasureBoundary();

    void DumpInfo() override;
    void OnContextAttached() override;
    void OnChildAdded(const RefPtr<ElementNode>& child) override;
    void RequestNextFrame();

    void UpdateAccessibilityNode();

    void UmountRender();

    int32_t CountRenderNode() const override
    {
        return 1;
    }

    std::list<RefPtr<FrameNode>> frameChildren_;
    WeakPtr<FrameNode> frameParent_;

    RefPtr<GeometryNode> geometryNode_ = MakeRefPtr<GeometryNode>();

    RefPtr<LayoutProperty> layoutProperty_;
    RefPtr<RenderProperty> renderProperty_;
    RefPtr<Pattern> pattern_;

    // for state temp node
    RefPtr<LayoutProperty> stateLayoutBox_;
    RefPtr<RenderProperty> stateRenderPropertyNode_;
    RefPtr<Pattern> statePattern_;

    RefPtr<RenderContext> renderContext_ = RenderContext::Create();

    std::mutex mutex_;
    std::atomic<bool> isLayouting_ = false;

    int32_t frameSlot_ = DEFAULT_FRAME_SLOT;
    int32_t depth_ = 0;

    bool isLayoutDirtyMarked_ = false;
    bool isRenderDirtyMarked_ = false;
    bool isMeasureBoundary_ = false;
    bool hasPendingRequest_ = false;

    friend class RosenRenderContext;
    friend class RenderContext;
    friend class Pattern;

    ACE_DISALLOW_COPY_AND_MOVE(FrameNode);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_FRAME_NODE_H
