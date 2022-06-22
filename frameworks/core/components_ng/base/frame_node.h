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

#include "base/geometry/ng/point_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/thread/cancelable_callback.h"
#include "base/thread/task_executor.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/render_context.h"
#include "core/components_ng/render/render_property.h"
#include "core/components_ng/render/render_wrapper.h"
#include "core/components_v2/inspector/inspector_node.h"

namespace OHOS::Ace::NG {
class PipelineContext;
class Pattern;
class StateModifyTask;
class UITask;

constexpr int32_t DEFAULT_FRAME_SLOT = -1;

// FrameNode will display rendering region in the screen.
class ACE_EXPORT FrameNode : public virtual UiNodeId {
    DECLARE_ACE_TYPE(FrameNode, UiNodeId);

public:
    // create a new child element and mount to element tree.
    static RefPtr<FrameNode> CreateFrameNodeAndMountToParent(const std::string& tag, const std::string& id,
        const RefPtr<Pattern>& pattern, const RefPtr<FrameNode>& parent, int32_t slot);

    // create a new child element with new element tree.
    static RefPtr<FrameNode> CreateFrameNodeWithTree(const std::string& tag, const std::string& id,
        const RefPtr<Pattern>& pattern, const RefPtr<PipelineContext>& context);

    // create a new element with new pattern.
    static RefPtr<FrameNode> CreateFrameNode(
        const std::string& tag, const std::string& id, const RefPtr<Pattern>& pattern, bool isRoot = false);

    // avoid use creator function, use CreateFrameNode
    FrameNode(const std::string& tag, const std::string& id, const RefPtr<Pattern>& pattern, bool isRoot = false);
    ~FrameNode() override;

    void InitializePatternAndContext();

    // Tree operation start.
    void AddChild(const RefPtr<FrameNode>& child, int32_t slot = DEFAULT_FRAME_SLOT);
    void RemoveChild(const RefPtr<FrameNode>& child);
    void MovePosition(uint32_t slot);
    void ClearChildren();
    RefPtr<FrameNode> GetChildBySlot(uint32_t slot);
    void MountToParent(const RefPtr<FrameNode>& parent, int32_t slot = DEFAULT_FRAME_SLOT);

    const std::list<RefPtr<FrameNode>>& GetChildren() const
    {
        return children_;
    }

    const WeakPtr<FrameNode>& GetParent() const
    {
        return parent_;
    }

    void SetParent(const WeakPtr<FrameNode>& parent)
    {
        parent_ = parent;
    }
    // Tree operation end.

    void AttachContextRecursively(const RefPtr<PipelineContext>& context);

    RefPtr<PipelineContext> GetContext() const;

    void MarkDirtyNode(PropertyChangeFlag extraFlag = PROPERTY_UPDATE_NORMAL);

    void MarkDirtyNode(
        bool isMeasureBoundary, bool isRenderBoundary, PropertyChangeFlag extraFlag = PROPERTY_UPDATE_NORMAL);

    void FlushModifyTaskOnCreate(StateModifyTask& stateModifyTask);

    void UpdateLayoutConstraint(const MeasureProperty& calcLayoutConstraint);

    void FlushModifyTaskOnRerender(StateModifyTask& stateModifyTask);

    RefPtr<LayoutWrapper> CreateLayoutWrapperOnCreate();

    std::optional<UITask> CreateLayoutTask(bool onCreate = false, bool forceUseMainThread = false);

    std::optional<UITask> CreateRenderTask(bool forceUseMainThread = false);

    void SwapDirtyLayoutWrapperOnMainThread(const RefPtr<LayoutWrapper>& dirty);

    void RebuildRenderContextTree();

    const RefPtr<GeometryNode>& GetGeometryNode() const
    {
        return geometryNode_;
    }
    void SetGeometryNode(RefPtr<GeometryNode>&& node);

    const RefPtr<RenderContext>& GetRenderContext() const
    {
        return renderContext_;
    }

    const RefPtr<Pattern>& GetPattern() const;

    template<typename T>
    RefPtr<T> GetLayoutProperty() const
    {
        return DynamicCast<T>(layoutProperty_);
    }

    template<typename T>
    RefPtr<T> GetRenderProperty() const
    {
        return DynamicCast<T>(renderProperty_);
    }

    template<typename T>
    RefPtr<T> GetEventHub() const
    {
        return DynamicCast<T>(eventHub_);
    }

    const RefPtr<LayoutProperty>& GetLayoutProperty() const
    {
        return layoutProperty_;
    }

    void PostTask(std::function<void()>&& task, TaskExecutor::TaskType taskType = TaskExecutor::TaskType::UI);

    // DFX info.
    void DumpTree(int32_t depth);

    const std::string& GetTag() const
    {
        return tag_;
    }

    const std::string& GetId() const
    {
        return id_;
    }

    void SetDepth(int32_t depth)
    {
        depth_ = depth;
        for (auto& child : children_) {
            child->SetDepth(depth_ + 1);
        }
    }

    int32_t GetDepth() const
    {
        return depth_;
    }

    bool TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint, const TouchRestrict& touchRestrict,
        TouchTestResult& result);

    bool IsAtomicNode() const;

    void RequestNextFrame();

protected:
    virtual void OnContextAttached() {}
    // dump self info.
    virtual void DumpInfo() {}

    void OnInActive();
    void OnActive();

    std::list<RefPtr<FrameNode>> children_;
    WeakPtr<PipelineContext> context_;
    WeakPtr<FrameNode> parent_;

private:
    void SetPipelineContext(const RefPtr<PipelineContext>& context);

    void UpdateLayoutPropertyFlag();
    RefPtr<LayoutWrapper> CreateLayoutWrapper(bool forceMeasure = false, bool forceLayout = false);
    void UpdateChildrenLayoutWrapper(const RefPtr<LayoutWrapper>& self, bool forceMeasure, bool forceLayout);

    std::optional<LayoutConstraintF> GetLayoutConstraint() const;
    std::optional<OffsetF> GetParentGlobalOffset() const;

    RefPtr<RenderWrapper> CreateRenderWrapper();

    bool IsMeasureBoundary();
    bool IsRenderBoundary();

    std::string tag_ = "FrameNode";
    std::string id_;

    RefPtr<GeometryNode> geometryNode_ = MakeRefPtr<GeometryNode>();

    RefPtr<LayoutProperty> layoutProperty_;
    RefPtr<RenderProperty> renderProperty_;
    RefPtr<Pattern> pattern_;
    RefPtr<EventHub> eventHub_;

    // for state temp node
    RefPtr<LayoutProperty> stateLayoutBox_;
    RefPtr<RenderProperty> stateRenderPropertyNode_;
    RefPtr<Pattern> statePattern_;

    RefPtr<RenderContext> renderContext_ = RenderContext::Create();

    bool needSyncRenderTree_ = false;

    int32_t depth_ = 0;

    bool isLayoutDirtyMarked_ = false;
    bool isRenderDirtyMarked_ = false;
    bool isMeasureBoundary_ = false;
    bool hasPendingRequest_ = false;
    bool isRoot_ = false;

    friend class RosenRenderContext;
    friend class RenderContext;
    friend class Pattern;

    ACE_DISALLOW_COPY_AND_MOVE(FrameNode);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_FRAME_NODE_H
