/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <cstdint>
#include <list>
#include <memory>
#include <string>
#include <unordered_map>

#include "base/geometry/ng/point_t.h"
#include "base/log/ace_performance_check.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {

class PipelineContext;
constexpr int32_t DEFAULT_NODE_SLOT = -1;

// UINode is the base class of FrameNode and SyntaxNode.
class ACE_EXPORT UINode : public virtual AceType {
    DECLARE_ACE_TYPE(UINode, AceType);

public:
    UINode(const std::string& tag, int32_t nodeId, bool isRoot = false);
    ~UINode() override;

    // atomic node is like button, image, custom node and so on.
    // In ets UI compiler, the atomic node does not Add Pop function, only have Create function.
    virtual bool IsAtomicNode() const = 0;

    virtual int32_t FrameCount() const;

    virtual RefPtr<LayoutWrapperNode> CreateLayoutWrapper(bool forceMeasure = false, bool forceLayout = false);

    // Tree operation start.
    void AddChild(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT, bool silently = false);
    std::list<RefPtr<UINode>>::iterator RemoveChild(const RefPtr<UINode>& child, bool allowTransition = false);
    int32_t RemoveChildAndReturnIndex(const RefPtr<UINode>& child);
    void ReplaceChild(const RefPtr<UINode>& oldNode, const RefPtr<UINode>& newNode);
    void MovePosition(int32_t slot);
    void MountToParent(const RefPtr<UINode>& parent, int32_t slot = DEFAULT_NODE_SLOT, bool silently = false);
    RefPtr<FrameNode> GetFocusParent() const;
    RefPtr<FocusHub> GetFirstFocusHubChild() const;
    void GetFocusChildren(std::list<RefPtr<FrameNode>>& children) const;
    void Clean(bool cleanDirectly = false, bool allowTransition = false);
    void RemoveChildAtIndex(int32_t index);
    RefPtr<UINode> GetChildAtIndex(int32_t index) const;
    int32_t GetChildIndex(const RefPtr<UINode>& child) const;
    void AttachToMainTree(bool recursive = false);
    void DetachFromMainTree(bool recursive = false);
    void UpdateConfigurationUpdate(const OnConfigurationChange& configurationChange);
    virtual void OnConfigurationUpdate(const OnConfigurationChange& configurationChange) {}

    // process offscreen process.
    void ProcessOffscreenTask(bool recursive = false);

    int32_t TotalChildCount() const;

    // Returns index in the flatten tree structure
    // of the node with given id and type
    // Returns std::pair with
    // boolean first - indication of node is found
    // int32_t second - index of the node
    std::pair<bool, int32_t> GetChildFlatIndex(int32_t id);

    virtual const std::list<RefPtr<UINode>>& GetChildren() const
    {
        return children_;
    }

    RefPtr<UINode> GetLastChild()
    {
        if (children_.empty()) {
            return nullptr;
        }
        return children_.back();
    }

    RefPtr<UINode> GetFirstChild()
    {
        if (children_.empty()) {
            return nullptr;
        }
        return children_.front();
    }

    void GenerateOneDepthVisibleFrame(std::list<RefPtr<FrameNode>>& visibleList);
    void GenerateOneDepthVisibleFrameWithTransition(std::list<RefPtr<FrameNode>>& visibleList);
    void GenerateOneDepthAllFrame(std::list<RefPtr<FrameNode>>& visibleList);

    int32_t GetChildIndexById(int32_t id);

    RefPtr<UINode> GetParent() const
    {
        return parent_.Upgrade();
    }

    void SetNeedCallChildrenUpdate(bool needCallChildrenUpdate)
    {
        needCallChildrenUpdate_ = needCallChildrenUpdate;
    }

    void SetParent(const WeakPtr<UINode>& parent)
    {
        parent_ = parent;
    }
    // Tree operation end.

    static RefPtr<PipelineContext> GetContext();

    // When FrameNode creates a layout task, the corresponding LayoutWrapper tree is created, and UINode needs to update
    // the corresponding LayoutWrapper tree node at this time like add self wrapper to wrapper tree.
    virtual void AdjustLayoutWrapperTree(const RefPtr<LayoutWrapperNode>& parent, bool forceMeasure, bool forceLayout);

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

    int32_t GetAccessibilityId() const
    {
        return accessibilityId_;
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
        for (auto& child : children_) {
            child->SetHostPageId(id);
        }
    }

    void SetRemoveSilently(bool removeSilently)
    {
        removeSilently_ = removeSilently;
    }

    void SetUndefinedNodeId()
    {
        nodeId_ = -1;
    }

    bool IsRemoving() const
    {
        return isRemoving_;
    }

    int32_t GetLayoutPriority() const
    {
        return layoutPriority_;
    }

    void SetLayoutPriority(int32_t priority)
    {
        layoutPriority_ = priority;
    }

    void SetInDestroying()
    {
        isInDestroying_ = true;
    }

    bool IsInDestroying() const
    {
        return isInDestroying_;
    }

    void SetChildrenInDestroying();

    virtual HitTestResult TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
        const TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId);
    virtual HitTestMode GetHitTestMode() const
    {
        return HitTestMode::HTMDEFAULT;
    }

    virtual HitTestResult MouseTest(const PointF& globalPoint, const PointF& parentLocalPoint,
        MouseTestResult& onMouseResult, MouseTestResult& onHoverResult, RefPtr<FrameNode>& hoverNode);

    virtual HitTestResult AxisTest(
        const PointF& globalPoint, const PointF& parentLocalPoint, AxisTestResult& onAxisResult);

    // In the request to re-layout the scene, needs to obtain the changed state of the child node for the creation
    // of parent's layout wrapper
    virtual void UpdateLayoutPropertyFlag();

    virtual void ForceUpdateLayoutPropertyFlag(PropertyChangeFlag propertyChangeFlag) {}

    virtual void AdjustParentLayoutFlag(PropertyChangeFlag& flag);

    virtual void MarkDirtyNode(PropertyChangeFlag extraFlag = PROPERTY_UPDATE_NORMAL);

    virtual void MarkNeedFrameFlushDirty(PropertyChangeFlag extraFlag = PROPERTY_UPDATE_NORMAL);

    virtual void FlushUpdateAndMarkDirty()
    {
        for (const auto& child : children_) {
            child->FlushUpdateAndMarkDirty();
        }
    }

    virtual void MarkNeedSyncRenderTree(bool needRebuild = false);

    virtual void RebuildRenderContextTree();

    virtual void OnWindowShow() {}

    virtual void OnWindowHide() {}
    virtual void Build();

    virtual void OnWindowFocused() {}

    virtual void OnWindowUnfocused() {}

    virtual void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) {}

    virtual void OnNotifyMemoryLevel(int32_t level) {}

    virtual void SetActive(bool active);

    virtual void SetJSViewActive(bool active);

    virtual void OnVisibleChange(bool isVisible);

    virtual bool MarkRemoving();

    bool IsOnMainTree() const
    {
        return onMainTree_;
    }

    bool UseOffscreenProcess() const
    {
        return useOffscreenProcess_;
    }

    virtual void ToJsonValue(std::unique_ptr<JsonValue>& json) const {}

    virtual void FromJson(const std::unique_ptr<JsonValue>& json) {}

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(InspectorId, std::string);
    virtual void OnInspectorIdUpdate(const std::string& /*unused*/) {}

    template<typename T>
    RefPtr<T> FindChildNodeOfClass()
    {
        const auto& children = GetChildren();
        for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
            auto& child = *iter;

            auto target = child->FindChildNodeOfClass<T>();
            if (target) {
                return target;
            }
        }

        RefPtr<UINode> uiNode = AceType::Claim<UINode>(this);
        if (AceType::InstanceOf<T>(uiNode)) {
            return AceType::DynamicCast<T>(uiNode);
        }
        return nullptr;
    }

    void ChildrenUpdatedFrom(int32_t index);
    int32_t GetChildrenUpdated() const
    {
        return childrenUpdatedFrom_;
    }

    // utility function for adding child to disappearingChildren_
    void AddDisappearingChild(const RefPtr<UINode>& child, uint32_t index = UINT32_MAX);
    // utility function for removing child from disappearingChildren_, return true if child is removed
    bool RemoveDisappearingChild(const RefPtr<UINode>& child);
    // return if we are in parent's disappearing children
    bool IsDisappearing() const
    {
        return isDisappearing_;
    }
    RefPtr<UINode> GetDisappearingChildById(const std::string& id) const;

    // These two interfaces are only used for fast preview.
    // FastPreviewUpdateChild: Replace the old child at the specified slot with the new created node.
    // FastPreviewUpdateChildDone: the new created node performs some special operations.
    virtual void FastPreviewUpdateChild(int32_t slot, const RefPtr<UINode>& newChild)
    {
        RemoveChildAtIndex(slot);
        newChild->MountToParent(AceType::Claim(this), slot, false);
    }
    virtual void FastPreviewUpdateChildDone() {}
    virtual RefPtr<UINode> GetFrameChildByIndex(uint32_t index);

#ifdef PREVIEW
    void SetDebugLine(const std::string& line)
    {
        debugLine_ = line;
    }
    std::string GetDebugLine() const
    {
        return debugLine_;
    }

    void SetViewId(const std::string& viewId)
    {
        viewId_ = viewId;
    }

    std::string GetViewId() const
    {
        return viewId_;
    }
#endif

    void SetRestoreId(int32_t restoreId)
    {
        restoreId_ = restoreId;
    }

    int32_t GetRestoreId()
    {
        return restoreId_;
    }

    void UpdateRecycleElmtId(int32_t newElmtId)
    {
        nodeId_ = newElmtId;
    }

    // --------------------------------------------------------------------------------
    // performance check get child count, depth, flex layout times and layout time
    void GetPerformanceCheckData(PerformanceCheckNodeMap& nodeMap);
    void SetLayoutTime(int64_t time)
    {
        if (nodeInfo_) {
            nodeInfo_->layoutTime = time;
        }
    }
    int64_t GetLayoutTime()
    {
        if (nodeInfo_) {
            return nodeInfo_->layoutTime;
        }
        return 0;
    }
    int32_t GetFlexLayouts()
    {
        if (nodeInfo_) {
            return nodeInfo_->flexLayouts;
        }
        return 0;
    }
    int32_t GetRow() const
    {
        if (nodeInfo_) {
            return nodeInfo_->codeRow;
        }
        return 0;
    }
    int32_t GetCol() const
    {
        if (nodeInfo_) {
            return nodeInfo_->codeCol;
        }
        return 0;
    }
    void SetRow(const int32_t row)
    {
        if (nodeInfo_) {
            nodeInfo_->codeRow = row;
        }
    }
    void SetCol(const int32_t col)
    {
        if (nodeInfo_) {
            nodeInfo_->codeCol = col;
        }
    }
    void SetForeachItem()
    {
        if (nodeInfo_) {
            nodeInfo_->isForEachItem = true;
        }
    }
    void AddFlexLayouts()
    {
        if (nodeInfo_) {
            nodeInfo_->flexLayouts++;
        }
    }
    virtual std::string GetCustomTag()
    {
        return GetTag();
    }
    void SetBuildByJs(bool isBuildByJS)
    {
        isBuildByJS_ = isBuildByJS;
    }
    void AddAttachToMainTreeTask(std::function<void()>&& func) {
        attachToMainTreeTasks_.emplace_back(std::move(func));
    }

    // --------------------------------------------------------------------------------

    virtual void DoRemoveChildInRenderTree(uint32_t index, bool isAll = false);
    virtual void OnSetCacheCount(int32_t cacheCount, const std::optional<LayoutConstraintF>& itemConstraint);

protected:
    std::list<RefPtr<UINode>>& ModifyChildren()
    {
        return children_;
    }

    virtual void OnGenerateOneDepthVisibleFrame(std::list<RefPtr<FrameNode>>& visibleList)
    {
        for (const auto& child : children_) {
            child->OnGenerateOneDepthVisibleFrame(visibleList);
        }
    }

    virtual void OnGenerateOneDepthVisibleFrameWithTransition(
        std::list<RefPtr<FrameNode>>& visibleList, uint32_t index = UINT_MAX);

    virtual void OnGenerateOneDepthAllFrame(std::list<RefPtr<FrameNode>>& allList)
    {
        for (const auto& child : children_) {
            child->OnGenerateOneDepthAllFrame(allList);
        }
    }

    virtual void OnContextAttached() {}
    // dump self info.
    virtual void DumpInfo() {}

    // Mount to the main tree to display.
    virtual void OnAttachToMainTree(bool recursive = false);
    virtual void OnDetachFromMainTree(bool recursive = false);

    // run offscreen process.
    virtual void OnOffscreenProcess(bool recursive) {}

    bool isRemoving_ = false;

    // return value: true if the node can be removed immediately.
    virtual bool OnRemoveFromParent(bool allowTransition);
    virtual bool RemoveImmediately() const;
    void ResetParent();

    // update visible change signal to children
    void UpdateChildrenVisible(bool isVisible) const;

protected:
    bool needCallChildrenUpdate_ = true;

private:
    void DoAddChild(std::list<RefPtr<UINode>>::iterator& it, const RefPtr<UINode>& child, bool silently = false,
        bool allowTransition = true);

    std::list<RefPtr<UINode>> children_;
    std::list<std::pair<RefPtr<UINode>, uint32_t>> disappearingChildren_;
    std::unique_ptr<PerformanceCheckNode> nodeInfo_;
    WeakPtr<UINode> parent_;
    std::string tag_ = "UINode";
    int32_t depth_ = 0;
    int32_t hostRootId_ = 0;
    int32_t hostPageId_ = 0;
    int32_t nodeId_ = 0;
    int32_t accessibilityId_ = -1;
    int32_t layoutPriority_ = 0;
    bool isRoot_ = false;
    bool onMainTree_ = false;
    bool removeSilently_ = true;
    bool isInDestroying_ = false;
    bool isDisappearing_ = false;
    bool isBuildByJS_ = false;

    int32_t childrenUpdatedFrom_ = -1;
    static thread_local int32_t currentAccessibilityId_;
    int32_t restoreId_ = -1;

    bool useOffscreenProcess_ = false;

    std::list<std::function<void()>> attachToMainTreeTasks_;

#ifdef PREVIEW
    std::string debugLine_;
    std::string viewId_;
#endif
    friend class RosenRenderContext;
    ACE_DISALLOW_COPY_AND_MOVE(UINode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_UI_NODE_H
