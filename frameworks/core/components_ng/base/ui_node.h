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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_UI_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_UI_NODE_H

#include <list>

#include "base/geometry/ng/point_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {

class PipelineContext;
constexpr int32_t DEFAULT_NODE_SLOT = -1;

// UINode is the base class of FrameNode and SyntaxNode.
class ACE_EXPORT UINode : public virtual AceType {
    DECLARE_ACE_TYPE(UINode, AceType);

public:
    UINode(const std::string& tag, int32_t nodeId, bool isRoot = false) : tag_(tag), nodeId_(nodeId), isRoot_(isRoot) {}
    ~UINode() override;

    // atomic node is like button, image, custom node and so on.
    // In ets UI compiler, the atomic node does not Add Pop function, only have Create function.
    virtual bool IsAtomicNode() const = 0;

    virtual int32_t FrameCount() const;

    // Tree operation start.
    void AddChild(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT);
    std::list<RefPtr<UINode>>::iterator RemoveChild(const RefPtr<UINode>& child);
    void ReplaceChild(const RefPtr<UINode>& oldNode, const RefPtr<UINode>& newNode);
    void MovePosition(int32_t slot);
    void MountToParent(const RefPtr<UINode>& parent, int32_t slot = DEFAULT_NODE_SLOT);
    void Clean();
    void RemoveChildAtIndex(int32_t index);

    void AttachToMainTree();
    void DetachFromMainTree();

    int32_t TotalChildCount() const;

    const std::list<RefPtr<UINode>>& GetChildren() const
    {
        return children_;
    }

    void GenerateOneDepthVisibleFrame(std::list<RefPtr<FrameNode>>& visibleList);

    RefPtr<UINode> GetParent() const
    {
        return parent_.Upgrade();
    }

    void SetParent(const WeakPtr<UINode>& parent)
    {
        parent_ = parent;
    }
    // Tree operation end.

    static RefPtr<PipelineContext> GetContext();

    // When FrameNode creates a layout task, the corresponding LayoutWrapper tree is created, and UINode needs to update
    // the corresponding LayoutWrapper tree node at this time like add self wrapper to wrapper tree.
    virtual void AdjustLayoutWrapperTree(const RefPtr<LayoutWrapper>& parent, bool forceMeasure, bool forceLayout);

    // DFX info.
    void DumpTree(int32_t depth);

    const std::string& GetTag() const
    {
        return tag_;
    }

    int32_t GetId() const
    {
        return nodeId_;
    }

    void SetDepth(int32_t depth)
    {
        depth_ = depth;
        for (auto& child : children_) {
            child->SetDepth(depth_ + 1);
        }
    }

    bool IsRootNode() const
    {
        return isRoot_;
    }

    int32_t GetDepth() const
    {
        return depth_;
    }

    int32_t GetRootId() const
    {
        return hostRootId_;
    }

    int32_t GetPageId() const
    {
        return hostPageId_;
    }

    // TODO: SetHostRootId step on create node.
    void SetHostRootId(int32_t id)
    {
        hostRootId_ = id;
    }

    // TODO: SetHostPageId step on mount to page.
    void SetHostPageId(int32_t id)
    {
        hostPageId_ = id;
    }

    virtual HitTestResult TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
        const TouchRestrict& touchRestrict, TouchTestResult& result);

    // In the request to re-layout the scene, needs to obtain the changed state of the child node for the creation of
    // parent's layout wrapper
    virtual void UpdateLayoutPropertyFlag();

    virtual void AdjustParentLayoutFlag(PropertyChangeFlag& flag);

    virtual void MarkDirtyNode(PropertyChangeFlag extraFlag = PROPERTY_UPDATE_NORMAL);

    virtual void MarkNeedFrameFlushDirty(PropertyChangeFlag extraFlag = PROPERTY_UPDATE_NORMAL);

    virtual void FlushUpdateAndMarkDirty()
    {
        for (const auto& child : children_) {
            child->FlushUpdateAndMarkDirty();
        }
    }

protected:
    virtual void MarkNeedSyncRenderTree();

    virtual void OnGenerateOneDepthVisibleFrame(std::list<RefPtr<FrameNode>>& visibleList)
    {
        for (const auto& child : children_) {
            child->OnGenerateOneDepthVisibleFrame(visibleList);
        }
    }

    virtual void OnContextAttached() {}
    // dump self info.
    virtual void DumpInfo() {}

    // Mount to the main tree to display.
    virtual void OnAttachToMainTree();
    virtual void OnDetachFromMainTree();

    std::list<RefPtr<UINode>> children_;
    WeakPtr<UINode> parent_;
    std::string tag_ = "UINode";
    int32_t depth_ = 0;
    int32_t hostRootId_ = 0;
    int32_t hostPageId_ = 0;
    int32_t nodeId_ = 0;
    bool isRoot_ = false;
    bool onMainTree_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(UINode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_UI_NODE_H
