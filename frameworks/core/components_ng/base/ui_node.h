/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_performance_check.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/view_data/view_data_wrap.h"
#include "core/common/resource/resource_configuration.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/export_texture_info/export_texture_info.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/property/accessibility_property.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {
class AccessibilityProperty;

struct ExtraInfo {
    std::string page;
    int32_t line = 0;
    int32_t col = 0;
};

enum class NodeStatus : char {
    NORMAL_NODE = 0,               // Indicates it is a normal node;
    BUILDER_NODE_OFF_MAINTREE = 1, // Indicates it is a BuilderNode and is detach from the mainTree;
    BUILDER_NODE_ON_MAINTREE = 2   // Indicates it is a BuilderNode and is attach to the mainTree;
};

enum class RootNodeType : int32_t {
    PAGE_ETS_TAG = 0,
    NAVDESTINATION_VIEW_ETS_TAG = 1,
    WINDOW_SCENE_ETS_TAG = 2
};

class InspectorFilter;
class PipelineContext;
constexpr int32_t DEFAULT_NODE_SLOT = -1;

// UINode is the base class of FrameNode and SyntaxNode.
class ACE_FORCE_EXPORT UINode : public virtual AceType {
    DECLARE_ACE_TYPE(UINode, AceType);

public:
    UINode(const std::string& tag, int32_t nodeId, bool isRoot = false);
    ~UINode() override;

    // atomic node is like button, image, custom node and so on.
    // In ets UI compiler, the atomic node does not Add Pop function, only have Create function.
    virtual bool IsAtomicNode() const = 0;

    virtual void AttachContext(PipelineContext* context, bool recursive = false);
    virtual void DetachContext(bool recursive = false);

    virtual int32_t FrameCount() const;
    virtual int32_t CurrentFrameCount() const;
    virtual RefPtr<LayoutWrapperNode> CreateLayoutWrapper(bool forceMeasure = false, bool forceLayout = false);

    // Tree operation start.
    virtual void AddChild(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT, bool silently = false,
        bool addDefaultTransition = false, bool addModalUiextension = false);
    void AddChildAfter(const RefPtr<UINode>& child, const RefPtr<UINode>& siblingNode);
    void AddChildBefore(const RefPtr<UINode>& child, const RefPtr<UINode>& siblingNode);

    std::list<RefPtr<UINode>>::iterator RemoveChild(const RefPtr<UINode>& child, bool allowTransition = false);
    int32_t RemoveChildAndReturnIndex(const RefPtr<UINode>& child);
    void ReplaceChild(const RefPtr<UINode>& oldNode, const RefPtr<UINode>& newNode);
    void MovePosition(int32_t slot);
    void MountToParent(const RefPtr<UINode>& parent, int32_t slot = DEFAULT_NODE_SLOT, bool silently = false,
        bool addDefaultTransition = false, bool addModalUiextension = false);
    RefPtr<FrameNode> GetParentFrameNode() const;
    RefPtr<CustomNode> GetParentCustomNode() const;
    RefPtr<FrameNode> GetFocusParentWithBoundary() const;
    RefPtr<FrameNode> GetFocusParent() const;
    RefPtr<FocusHub> GetFirstFocusHubChild() const;

    // Only for the currently loaded children, do not expand.
    void GetCurrentChildrenFocusHub(std::list<RefPtr<FocusHub>>& focusNodes);

    void GetFocusChildren(std::list<RefPtr<FrameNode>>& children) const;
    void Clean(bool cleanDirectly = false, bool allowTransition = false, int32_t branchId = -1);
    void RemoveChildAtIndex(int32_t index);
    RefPtr<UINode> GetChildAtIndex(int32_t index) const;
    int32_t GetChildIndex(const RefPtr<UINode>& child) const;
    [[deprecated]] void AttachToMainTree(bool recursive = false);
    void AttachToMainTree(bool recursive, PipelineContext* context);
    void DetachFromMainTree(bool recursive = false);
    virtual void FireCustomDisappear();
    void UpdateConfigurationUpdate(const ConfigurationChange& configurationChange);
    virtual void OnConfigurationUpdate(const ConfigurationChange& configurationChange) {}

    // process offscreen process.
    void ProcessOffscreenTask(bool recursive = false);

    // Determine if the node is a SyntaxNode, default returns false.
    // SyntaxNode classes need to override the method and return true.
    virtual bool IsSyntaxNode() const
    {
        return false;
    }

    void UpdateModalUiextensionCount(bool addNode)
    {
        if (addNode) {
            modalUiextensionCount_++;
        } else {
            modalUiextensionCount_--;
        }
    }

    int32_t TotalChildCount() const;
    virtual void UpdateGeometryTransition();

    // Returns index in the flatten tree structure
    // of the node with given id and type
    // Returns std::pair with
    // boolean first - indication of node is found
    // int32_t second - index of the node
    std::pair<bool, int32_t> GetChildFlatIndex(int32_t id);

    virtual const std::list<RefPtr<UINode>>& GetChildren(bool notDetach = false) const
    {
        return children_;
    }

    RefPtr<UINode> GetLastChild() const
    {
        if (children_.empty()) {
            return nullptr;
        }
        return children_.back();
    }

    RefPtr<UINode> GetFirstChild() const
    {
        if (children_.empty()) {
            return nullptr;
        }
        return children_.front();
    }

    void GenerateOneDepthVisibleFrame(std::list<RefPtr<FrameNode>>& visibleList);
    void GenerateOneDepthVisibleFrameWithTransition(std::list<RefPtr<FrameNode>>& visibleList);
    void GenerateOneDepthVisibleFrameWithOffset(
        std::list<RefPtr<FrameNode>>& visibleList, OffsetF& offset);
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

    virtual void SetParent(const WeakPtr<UINode>& parent, bool needDetect = true);
    // Tree operation end.

    // performance.
    PipelineContext* GetContext() const;
    PipelineContext* GetAttachedContext() const;
    PipelineContext* GetContextWithCheck();

    RefPtr<PipelineContext> GetContextRefPtr() const;

    // When FrameNode creates a layout task, the corresponding LayoutWrapper tree is created, and UINode needs to update
    // the corresponding LayoutWrapper tree node at this time like add self wrapper to wrapper tree.
    virtual void AdjustLayoutWrapperTree(const RefPtr<LayoutWrapperNode>& parent, bool forceMeasure, bool forceLayout);

    bool IsAutoFillContainerNode();
    void DumpViewDataPageNodes(
        RefPtr<ViewDataWrap> viewDataWrap, bool skipSubAutoFillContainer = false, bool needsRecordData = false);
    bool NeedRequestAutoSave();
    // DFX info.
    virtual void DumpTree(int32_t depth, bool hasJson = false);
    void DumpSimplifyTree(int32_t depth, std::unique_ptr<JsonValue>& current);
    virtual bool IsContextTransparent();

    bool DumpTreeById(int32_t depth, const std::string& id, bool hasJson = false);

    const std::string& GetTag() const
    {
        return tag_;
    }

    int32_t GetId() const
    {
        return nodeId_;
    }

    int64_t GetAccessibilityId() const
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
        const PointF& parentRevertPoint, TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId,
        ResponseLinkResult& responseLinkResult, bool isDispatch = false);
    virtual HitTestMode GetHitTestMode() const
    {
        return HitTestMode::HTMDEFAULT;
    }

    virtual HitTestResult MouseTest(const PointF& globalPoint, const PointF& parentLocalPoint,
        MouseTestResult& onMouseResult, MouseTestResult& onHoverResult, RefPtr<FrameNode>& hoverNode);

    virtual HitTestResult AxisTest(const PointF& globalPoint, const PointF& parentLocalPoint,
        const PointF& parentRevertPoint, TouchRestrict& touchRestrict, AxisTestResult& onAxisResult);

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
    virtual void Build(std::shared_ptr<std::list<ExtraInfo>> extraInfos);

    virtual bool RenderCustomChild(int64_t deadline);

    virtual void OnWindowFocused() {}

    virtual void OnWindowUnfocused() {}

    virtual void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) {}

    virtual void OnNotifyMemoryLevel(int32_t level) {}

    virtual void SetActive(bool active, bool needRebuildRenderContext = false);

    virtual void SetJSViewActive(bool active, bool isLazyForEachNode = false, bool isReuse = false);

    virtual void TryVisibleChangeOnDescendant(VisibleType preVisibility, VisibleType currentVisibility);

    // call by recycle framework.
    virtual void OnRecycle();
    virtual void OnReuse();

    virtual bool MarkRemoving();

    bool IsOnMainTree() const
    {
        return onMainTree_;
    }

    bool UseOffscreenProcess() const
    {
        return useOffscreenProcess_;
    }

    virtual void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}

    virtual void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const {}

    virtual void FromJson(const std::unique_ptr<JsonValue>& json) {}

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(InspectorId, std::string);
    virtual void OnInspectorIdUpdate(const std::string& /*unused*/) {}

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(AutoEventParam, std::string);
    virtual void OnAutoEventParamUpdate(const std::string& /*unused*/) {}

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

    // utility function for adding child to disappearingChildren_
    void AddDisappearingChild(const RefPtr<UINode>& child, uint32_t index = UINT32_MAX, int32_t branchId = -1);
    // utility function for removing child from disappearingChildren_, return true if child is removed
    bool RemoveDisappearingChild(const RefPtr<UINode>& child);
    // return if we are in parent's disappearing children
    bool IsDisappearing() const
    {
        return isDisappearing_;
    }
    RefPtr<UINode> GetDisappearingChildById(const std::string& id, int32_t branchId) const;

    // These two interfaces are only used for fast preview.
    // FastPreviewUpdateChild: Replace the old child at the specified slot with the new created node.
    // FastPreviewUpdateChildDone: the new created node performs some special operations.
    virtual void FastPreviewUpdateChild(int32_t slot, const RefPtr<UINode>& newChild)
    {
        RemoveChildAtIndex(slot);
        newChild->MountToParent(AceType::Claim(this), slot, false);
    }
    virtual void FastPreviewUpdateChildDone() {}
    virtual RefPtr<UINode> GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache = false,
        bool addToRenderTree = false);
    virtual RefPtr<UINode> GetFrameChildByIndexWithoutExpanded(uint32_t index);
    // Get current frameNode index with or without expanded all LazyForEachNode;
    virtual int32_t GetFrameNodeIndex(const RefPtr<FrameNode>& node, bool isExpanded = true);
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

    void* GetExternalData() const
    {
        return externalData_;
    }

    void SetExternalData(void* externalData)
    {
        externalData_ = externalData;
    }

    // --------------------------------------------------------------------------------

    virtual void DoRemoveChildInRenderTree(uint32_t index, bool isAll = false);
    virtual void DoSetActiveChildRange(
        int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache = false);
    virtual void DoSetActiveChildRange(
        const std::set<int32_t>& activeItems, const std::set<int32_t>& cachedItems, int32_t baseIndex)
    {}
    virtual void OnSetCacheCount(int32_t cacheCount, const std::optional<LayoutConstraintF>& itemConstraint);

    // return value: true if the node can be removed immediately.
    virtual bool OnRemoveFromParent(bool allowTransition);

    void MarkForceMeasure()
    {
        MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        for (const auto& child : children_) {
            child->MarkForceMeasure();
        }
    }

    std::string GetCurrentCustomNodeInfo();
    static int64_t GenerateAccessibilityId();

    // used by BuilderNode
    NodeStatus GetNodeStatus() const;
    void UpdateNodeStatus(NodeStatus nodeStatus);
    void SetIsRootBuilderNode(bool isRootBuilderNode);
    bool GetIsRootBuilderNode() const;

    bool IsArkTsFrameNode() const
    {
        return isArkTsFrameNode_;
    }

    void SetIsArkTsFrameNode(bool isArkTsFrameNode)
    {
        isArkTsFrameNode_ = isArkTsFrameNode;
    }

    const RefPtr<ExportTextureInfo>& GetExportTextureInfo() const
    {
        return exportTextureInfo_;
    }

    void CreateExportTextureInfoIfNeeded();

    bool IsNeedExportTexture() const;

    virtual bool SetParentLayoutConstraint(const SizeF& size) const;

    virtual void SetNodeIndexOffset(int32_t start, int32_t count) {}

    bool IsLayoutSeperately() const
    {
        return layoutSeperately_;
    }

    virtual void PaintDebugBoundaryTreeAll(bool flag);
    static void DFSAllChild(const RefPtr<UINode>& root, std::vector<RefPtr<UINode>>& res);
    static void GetBestBreakPoint(RefPtr<UINode>& breakPointChild, RefPtr<UINode>& breakPointParent);

    virtual bool HasVirtualNodeAccessibilityProperty()
    {
        return false;
    }

    void AddFlag(uint32_t flag)
    {
        nodeFlag_ |= flag;
    }

    bool IsNodeHasFlag(uint32_t flag) const
    {
        return (flag & nodeFlag_) == flag;
    }

    void SetAccessibilityNodeVirtual()
    {
        isAccessibilityVirtualNode_ = true;
        for (auto& it : GetChildren()) {
            it->SetAccessibilityNodeVirtual();
        }
    }

    bool IsAccessibilityVirtualNode() const
    {
        return isAccessibilityVirtualNode_;
    }

    void SetAccessibilityVirtualNodeParent(const RefPtr<UINode>& parent)
    {
        parentForAccessibilityVirtualNode_ = parent;
        for (auto& it : GetChildren()) {
            it->SetAccessibilityVirtualNodeParent(parent);
        }
    }

    WeakPtr<UINode> GetVirtualNodeParent() const
    {
        return parentForAccessibilityVirtualNode_;
    }

    bool IsFirstVirtualNode() const
    {
        return isFirstAccessibilityVirtualNode_;
    }

    void SetFirstAccessibilityVirtualNode()
    {
        isFirstAccessibilityVirtualNode_ = true;
    }

    void SetRootNodeId(int32_t rootNodeId)
    {
        rootNodeId_ = rootNodeId;
    }

    int32_t GetRootNodeId() const
    {
        return rootNodeId_;
    }

    bool RootNodeIsPage() const
    {
        return rootNodeType_ == RootNodeType::PAGE_ETS_TAG;
    }

    void SetRootNodeType(RootNodeType rootNodeType)
    {
        rootNodeType_ = rootNodeType;
    }

    RootNodeType GetRootNodeType() const
    {
        return rootNodeType_;
    }

    virtual void ClearSubtreeLayoutAlgorithm(bool includeSelf = true, bool clearEntireTree = false);

    void GetPageNodeCountAndDepth(int32_t* count, int32_t* depth);

    virtual void RegisterUpdateJSInstanceCallback(std::function<void(int32_t)>&& callback)
    {
        updateJSInstanceCallback_ = std::move(callback);
    }

    int32_t GetInstanceId() const
    {
        return instanceId_;
    }

    virtual void SetGeometryTransitionInRecursive(bool isGeometryTransitionIn)
    {
        for (const auto& child : GetChildren()) {
            child->SetGeometryTransitionInRecursive(isGeometryTransitionIn);
        }
    }

    virtual void SetOnNodeDestroyCallback(std::function<void(int32_t)>&& destroyCallback)
    {
        destroyCallback_ = std::move(destroyCallback);
    }

    virtual bool HasOnNodeDestroyCallback()
    {
        return destroyCallback_ != nullptr;
    }

    virtual void FireOnNodeDestroyCallback()
    {
        CHECK_NULL_VOID(destroyCallback_);
        destroyCallback_(GetId());
    }

    bool IsAllowAddChildBelowModalUec() const
    {
        return isAllowAddChildBelowModalUec_;
    }

    void SetIsAllowAddChildBelowModalUec(bool isAllowAddChildBelowModalUec)
    {
        isAllowAddChildBelowModalUec_ = isAllowAddChildBelowModalUec;
    }

    void SetBuilderFunc(std::function<void()>&& lazyBuilderFunc)
    {
        lazyBuilderFunc_ = lazyBuilderFunc;
    }

    std::function<void()> GetBuilderFunc() const
    {
        return lazyBuilderFunc_;
    }

    void SetUpdateNodeFunc(std::function<void(int32_t, RefPtr<UINode>&)>&& updateNodeFunc)
    {
        updateNodeFunc_ = updateNodeFunc;
    }

    std::function<void(int32_t, RefPtr<UINode>&)> GetUpdateNodeFunc()
    {
        return updateNodeFunc_;
    }

    void SetUpdateNodeConfig(std::function<void()>&& updateNodeConfig)
    {
        updateNodeConfig_ = updateNodeConfig;
    }

    std::function<void()> GetUpdateNodeConfig()
    {
        return updateNodeConfig_;
    }

    virtual void GetInspectorValue();
    virtual void NotifyWebPattern(bool isRegister);
    void GetContainerComponentText(std::u16string& text);

    enum class NotificationType : int32_t {
        START_CHANGE_POSITION = 0,
        END_CHANGE_POSITION = 1,
        START_AND_END_CHANGE_POSITION = 2
    };
    /**
     * @brief For a DataChange happened in child [id], notify the corresponding change position to parent.
     *
     * @param changeIdx change index in child [id].
     * @param count change of item count.
     * @param id the accessibilityId of child who call this function.
     * @param notificationType the type of notification.
     */
    virtual void NotifyChange(int32_t changeIdx, int32_t count, int64_t id, NotificationType notificationType);

    int32_t GetThemeScopeId() const;
    void SetThemeScopeId(int32_t themeScopeId);
    virtual void UpdateThemeScopeId(int32_t themeScopeId);
    virtual void UpdateThemeScopeUpdate(int32_t themeScopeId);
    virtual void OnThemeScopeUpdate(int32_t themeScopeId) {}
    void AllowUseParentTheme(bool isAllow);
    bool IsAllowUseParentTheme() const;
    ColorMode GetLocalColorMode() const;

    // Used to mark freeze and block dirty mark.
    virtual void SetFreeze(bool isFreeze, bool isForceUpdateFreezeVaule = false);
    bool IsFreeze() const
    {
        return isFreeze_;
    }

    bool IsCNode() const
    {
        return isCNode_;
    }

    void setIsCNode(bool createByCapi)
    {
        isCNode_ = createByCapi;
    }

    virtual RefPtr<UINode> GetCurrentPageRootNode()
    {
        return nullptr;
    }

    virtual void AddCustomProperty(const std::string& key, const std::string& value) {}
    virtual void RemoveCustomProperty(const std::string& key) {}

    bool IsMoving() const
    {
        return isMoving_;
    }

    void setIsMoving(bool isMoving)
    {
        isMoving_ = isMoving;
    }

    bool isCrossLanguageAttributeSetting() const
    {
        return isCrossLanguageAttributeSetting_;
    }

    void SetIsCrossLanguageAttributeSetting(bool isCrossLanguageAttributeSetting)
    {
        isCrossLanguageAttributeSetting_ = isCrossLanguageAttributeSetting;
    }

    /**
     * flag used by Repeat virtual scroll
     * to mark a child UINode of RepeatVirtualScroll as either allowing or not allowing
     * adding a @ReusableV2 @ComponentV2 CustomNode
     * allowReusableV2Descendant_ default value is true
     */
    void SetAllowReusableV2Descendant(bool allow);
    bool IsAllowReusableV2Descendant() const;
protected:
    std::list<RefPtr<UINode>>& ModifyChildren()
    {
        return children_;
    }

    virtual void OnGenerateOneDepthVisibleFrame(std::list<RefPtr<FrameNode>>& visibleList)
    {
        for (const auto& child : GetChildren()) {
            child->OnGenerateOneDepthVisibleFrame(visibleList);
        }
    }

    virtual void OnGenerateOneDepthVisibleFrameWithTransition(std::list<RefPtr<FrameNode>>& visibleList);

    virtual void OnGenerateOneDepthVisibleFrameWithOffset(
        std::list<RefPtr<FrameNode>>& visibleList, OffsetF& offset);

    virtual void OnGenerateOneDepthAllFrame(std::list<RefPtr<FrameNode>>& allList)
    {
        for (const auto& child : GetChildren()) {
            child->OnGenerateOneDepthAllFrame(allList);
        }
    }

    virtual void AfterMountToParent() {}
    virtual void OnContextAttached() {}
    // dump self info.
    virtual void DumpInfo() {}
    virtual void DumpInfo(std::unique_ptr<JsonValue>& json) {}
    virtual void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) {}
    virtual void DumpAdvanceInfo() {}
    virtual void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) {}
    virtual void DumpViewDataPageNode(RefPtr<ViewDataWrap> viewDataWrap, bool needsRecordData = false) {}
    virtual bool CheckAutoSave()
    {
        return false;
    }
    // Mount to the main tree to display.
    virtual void OnAttachToMainTree(bool recursive = false);
    virtual void OnDetachFromMainTree(bool recursive = false, PipelineContext* context = nullptr);
    virtual void OnAttachToBuilderNode(NodeStatus nodeStatus) {}

    virtual void OnFreezeStateChange() {}
    virtual void UpdateChildrenFreezeState(bool isFreeze, bool isForceUpdateFreezeVaule = false);

    // run offscreen process.
    virtual void OnOffscreenProcess(bool recursive) {}

    bool isRemoving_ = false;

    virtual bool RemoveImmediately() const;
    void ResetParent();
    static void RemoveFromParentCleanly(const RefPtr<UINode>& child, const RefPtr<UINode>& parent);

    // update visible change signal to children
    void UpdateChildrenVisible(VisibleType preVisibility, VisibleType currentVisibility) const;

    void CollectRemovedChildren(const std::list<RefPtr<UINode>>& children,
        std::list<int32_t>& removedElmtId, bool isEntry);
    void CollectRemovedChild(const RefPtr<UINode>& child, std::list<int32_t>& removedElmtId);

    bool needCallChildrenUpdate_ = true;

    bool layoutSeperately_ = false;

    virtual void PaintDebugBoundary(bool flag) {}

    void TraversingCheck(RefPtr<UINode> node = nullptr, bool withAbort = false);

    PipelineContext* context_ = nullptr;

    /**
     * @brief Transform the [changeIdx] given by child [id] to corresponding position in [this] node.
     *
     * @param changeIdx change index in child [id].
     * @param id the accessibilityId of child.
     */
    int32_t CalcAbsPosition(int32_t changeIdx, int64_t id) const;

private:
    void DoAddChild(std::list<RefPtr<UINode>>::iterator& it, const RefPtr<UINode>& child, bool silently = false,
        bool addDefaultTransition = false);
    bool CanAddChildWhenTopNodeIsModalUec(std::list<RefPtr<UINode>>::iterator& curIter);

    std::list<RefPtr<UINode>> children_;
    // disappearingChild、index、branchId
    std::list<std::tuple<RefPtr<UINode>, uint32_t, int32_t>> disappearingChildren_;
    std::unique_ptr<PerformanceCheckNode> nodeInfo_;
    WeakPtr<UINode> parent_;
    std::string tag_ = "UINode";
    int32_t depth_ = 1;
    int32_t hostRootId_ = 0;
    int32_t hostPageId_ = 0;
    int32_t nodeId_ = 0;
    int64_t accessibilityId_ = -1;
    int32_t layoutPriority_ = 0;
    int32_t rootNodeId_ = 0; // host is Page or NavDestination
    int32_t themeScopeId_ = 0;
    bool isRoot_ = false;
    bool onMainTree_ = false;
    bool removeSilently_ = true;
    bool isInDestroying_ = false;
    bool isDisappearing_ = false;
    bool isBuildByJS_ = false;
    bool isRootBuilderNode_ = false;
    bool isArkTsFrameNode_ = false;
    bool isTraversing_ = false;
    bool isAllowUseParentTheme_ = true;
    NodeStatus nodeStatus_ = NodeStatus::NORMAL_NODE;
    RootNodeType rootNodeType_ = RootNodeType::PAGE_ETS_TAG;
    RefPtr<ExportTextureInfo> exportTextureInfo_;
    int32_t instanceId_ = -1;
    uint32_t nodeFlag_ { 0 };

    int32_t restoreId_ = -1;

    bool useOffscreenProcess_ = false;

    bool isCNode_ = false;
    bool isAllowAddChildBelowModalUec_ = true;

    std::function<void(int32_t)> updateJSInstanceCallback_;
    std::function<void()> lazyBuilderFunc_;
    std::function<void(int32_t, RefPtr<UINode>&)> updateNodeFunc_;
    std::function<void()> updateNodeConfig_;

    std::string debugLine_;
    std::string viewId_;
    void* externalData_ = nullptr;
    std::function<void(int32_t)> destroyCallback_;
    // Other components cannot be masked above the modal uiextension,
    // except for the modal uiextension
    // Used to mark modal uiextension count below the root node
    int32_t modalUiextensionCount_ = 0;
    bool isAccessibilityVirtualNode_ = false;
    WeakPtr<UINode> parentForAccessibilityVirtualNode_;
    bool isFirstAccessibilityVirtualNode_ = false;
    // the flag to block dirty mark.
    bool isFreeze_ = false;
    bool allowReusableV2Descendant_ = true;
    friend class RosenRenderContext;
    ACE_DISALLOW_COPY_AND_MOVE(UINode);
    bool isMoving_ = false;
    bool isCrossLanguageAttributeSetting_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_UI_NODE_H
