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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_FRAME_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_FRAME_NODE_H

#include <functional>
#include <list>
#include <utility>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/thread/cancelable_callback.h"
#include "base/thread/task_executor.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/accessibility/accessibility_utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/input_event_hub.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/accessibility_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "core/components_ng/render/render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_v2/inspector/inspector_node.h"

namespace OHOS::Ace::NG {
class PipelineContext;
class Pattern;
class StateModifyTask;
class UITask;
class FramePorxy;

// FrameNode will display rendering region in the screen.
class ACE_FORCE_EXPORT FrameNode : public UINode, public LayoutWrapper {
    DECLARE_ACE_TYPE(FrameNode, UINode, LayoutWrapper);

public:
    // create a new child element with new element tree.
    static RefPtr<FrameNode> CreateFrameNodeWithTree(
        const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern);

    static RefPtr<FrameNode> GetOrCreateFrameNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

    // create a new element with new pattern.
    static RefPtr<FrameNode> CreateFrameNode(
        const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false);

    // get element with nodeId from node map.
    static RefPtr<FrameNode> GetFrameNode(const std::string& tag, int32_t nodeId);

    static void ProcessOffscreenNode(const RefPtr<FrameNode>& node);
    // avoid use creator function, use CreateFrameNode
    FrameNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false);

    ~FrameNode() override;

    int32_t FrameCount() const override
    {
        return 1;
    }

    void InitializePatternAndContext();

    virtual void MarkModifyDone();

    void MarkDirtyNode(PropertyChangeFlag extraFlag = PROPERTY_UPDATE_NORMAL) override;

    void MarkDirtyNode(
        bool isMeasureBoundary, bool isRenderBoundary, PropertyChangeFlag extraFlag = PROPERTY_UPDATE_NORMAL);

    void FlushUpdateAndMarkDirty() override;

    void MarkNeedFrameFlushDirty(PropertyChangeFlag extraFlag = PROPERTY_UPDATE_NORMAL) override
    {
        MarkDirtyNode(extraFlag);
    }

    void OnMountToParentDone();

    void UpdateLayoutConstraint(const MeasureProperty& calcLayoutConstraint);

    RefPtr<LayoutWrapperNode> CreateLayoutWrapper(bool forceMeasure = false, bool forceLayout = false) override;

    RefPtr<LayoutWrapperNode> UpdateLayoutWrapper(
        RefPtr<LayoutWrapperNode> layoutWrapper, bool forceMeasure = false, bool forceLayout = false);

    std::optional<UITask> CreateLayoutTask(bool forceUseMainThread = false);

    std::optional<UITask> CreateRenderTask(bool forceUseMainThread = false);

    void SwapDirtyLayoutWrapperOnMainThread(const RefPtr<LayoutWrapper>& dirty);

    // Clear the user callback.
    void ClearUserOnAreaChange();

    void SetOnAreaChangeCallback(OnAreaChangedFunc&& callback);

    void TriggerOnAreaChangeCallback();

    void OnConfigurationUpdate(const OnConfigurationChange& configurationChange) override;

    void AddVisibleAreaUserCallback(double ratio, const VisibleCallbackInfo& callback)
    {
        visibleAreaUserCallbacks_[ratio] = callback;
    }

    void AddVisibleAreaInnerCallback(double ratio, const VisibleCallbackInfo& callback)
    {
        visibleAreaInnerCallbacks_[ratio] = callback;
    }

    void TriggerVisibleAreaChangeCallback(bool forceDisappear = false);

    void SetGeometryNode(const RefPtr<GeometryNode>& node);

    const RefPtr<RenderContext>& GetRenderContext() const
    {
        return renderContext_;
    }

    const RefPtr<Pattern>& GetPattern() const;

    template<typename T>
    RefPtr<T> GetPattern() const
    {
        return DynamicCast<T>(pattern_);
    }

    template<typename T>
    RefPtr<T> GetAccessibilityProperty() const
    {
        return DynamicCast<T>(accessibilityProperty_);
    }

    template<typename T>
    RefPtr<T> GetLayoutProperty() const
    {
        return DynamicCast<T>(layoutProperty_);
    }

    template<typename T>
    RefPtr<T> GetPaintProperty() const
    {
        return DynamicCast<T>(paintProperty_);
    }

    template<typename T>
    RefPtr<T> GetEventHub() const
    {
        return DynamicCast<T>(eventHub_);
    }

    RefPtr<GestureEventHub> GetOrCreateGestureEventHub() const
    {
        return eventHub_->GetOrCreateGestureEventHub();
    }

    RefPtr<InputEventHub> GetOrCreateInputEventHub() const
    {
        return eventHub_->GetOrCreateInputEventHub();
    }

    RefPtr<FocusHub> GetOrCreateFocusHub() const;

    RefPtr<FocusHub> GetFocusHub() const
    {
        return eventHub_->GetFocusHub();
    }

    FocusType GetFocusType() const
    {
        FocusType type = FocusType::DISABLE;
        auto focusHub = GetFocusHub();
        if (focusHub) {
            type = focusHub->GetFocusType();
        }
        return type;
    }

    static void PostTask(std::function<void()>&& task, TaskExecutor::TaskType taskType = TaskExecutor::TaskType::UI);

    // If return true, will prevent TouchTest Bubbling to parent and brother nodes.
    HitTestResult TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
        const TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId) override;

    HitTestResult MouseTest(const PointF& globalPoint, const PointF& parentLocalPoint, MouseTestResult& onMouseResult,
        MouseTestResult& onHoverResult, RefPtr<FrameNode>& hoverNode) override;

    HitTestResult AxisTest(
        const PointF& globalPoint, const PointF& parentLocalPoint, AxisTestResult& onAxisResult) override;

    void CheckSecurityComponentStatus(std::vector<RectF>& rect);

    bool HaveSecurityComponent();

    bool IsSecurityComponent();

    void AnimateHoverEffect(bool isHovered) const;

    bool IsAtomicNode() const override;

    void MarkNeedSyncRenderTree(bool needRebuild = false) override;

    void RebuildRenderContextTree() override;

    bool IsVisible() const
    {
        return layoutProperty_->GetVisibility().value_or(VisibleType::VISIBLE) == VisibleType::VISIBLE;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

    void FromJson(const std::unique_ptr<JsonValue>& json) override;

    RefPtr<FrameNode> GetAncestorNodeOfFrame() const;

    std::string& GetNodeName()
    {
        return nodeName_;
    }

    void SetNodeName(std::string& nodeName)
    {
        nodeName_ = nodeName;
    }
    bool IsResponseRegion() const;
    void MarkResponseRegion(bool isResponseRegion);

    void OnWindowShow() override;

    void OnWindowHide() override;

    void OnWindowFocused() override;

    void OnWindowUnfocused() override;

    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;

    void OnNotifyMemoryLevel(int32_t level) override;

    OffsetF GetOffsetRelativeToWindow() const;

    OffsetF GetTransformRelativeOffset() const;

    RectF GetTransformRectRelativeToWindow() const;

    OffsetF GetPaintRectOffset(bool excludeSelf = false) const;

    OffsetF GetPaintRectGlobalOffsetWithTranslate(bool excludeSelf = false) const;

    OffsetF GetPaintRectOffsetToPage() const;

    RectF GetPaintRectWithTransform() const;

    VectorF GetTransformScale() const;

    void AdjustGridOffset();

    bool IsInternal() const
    {
        return isInternal_;
    }

    void SetInternal()
    {
        isInternal_ = true;
    }

    int32_t GetAllDepthChildrenCount();

    void OnAccessibilityEvent(
        AccessibilityEventType eventType, WindowsContentChangeTypes windowsContentChangeType =
                                              WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_INVALID) const;

    void OnAccessibilityEvent(
        AccessibilityEventType eventType, std::string beforeText, std::string latestContent) const;

    void MarkNeedRenderOnly();

    void OnDetachFromMainTree(bool recursive) override;
    void OnAttachToMainTree(bool recursive) override;

    void OnVisibleChange(bool isVisible) override;

    void PushDestroyCallback(std::function<void()>&& callback)
    {
        destroyCallbacks_.emplace_back(callback);
    }

    bool MarkRemoving() override;

    void AddHotZoneRect(const DimensionRect& hotZoneRect) const;
    void RemoveLastHotZoneRect() const;

    virtual bool IsOutOfTouchTestRegion(const PointF& parentLocalPoint, int32_t sourceType);
    bool CheckRectIntersect(const RectF& dest, std::vector<RectF>& origin);

    bool IsLayoutDirtyMarked() const
    {
        return isLayoutDirtyMarked_;
    }

    bool HasPositionProp() const
    {
        CHECK_NULL_RETURN_NOLOG(renderContext_, false);
        return renderContext_->HasPosition() || renderContext_->HasOffset() || renderContext_->HasAnchor();
    }

    // The function is only used for fast preview.
    void FastPreviewUpdateChildDone() override
    {
        OnMountToParentDone();
    }

    bool IsExclusiveEventForChild() const
    {
        return exclusiveEventForChild_;
    }

    void SetExclusiveEventForChild(bool exclusiveEventForChild)
    {
        exclusiveEventForChild_ = exclusiveEventForChild;
    }

    void SetDraggable(bool draggable)
    {
        draggable_ = draggable;
        userSet_ = true;
    }

    void SetBackgroundFunction(std::function<RefPtr<UINode>()>&& buildFunc)
    {
        builderFunc_ = buildFunc;
        backgroundNode_ = nullptr;
    }

    bool IsDraggable() const
    {
        return draggable_;
    }

    bool IsUserSet() const
    {
        return userSet_;
    }

    void SetAllowDrop(const std::set<std::string>& allowDrop)
    {
        allowDrop_ = allowDrop;
    }

    const std::set<std::string>& GetAllowDrop() const
    {
        return allowDrop_;
    }

    void SetOverlayNode(const RefPtr<FrameNode>& overlayNode)
    {
        overlayNode_ = overlayNode;
    }

    RefPtr<FrameNode> GetOverlayNode() const
    {
        return overlayNode_;
    }

    RefPtr<FrameNode> FindChildByPosition(float x, float y);

    void CreateAnimatablePropertyFloat(
        const std::string& propertyName, float value, const std::function<void(float)>& onCallbackEvent);
    void UpdateAnimatablePropertyFloat(const std::string& propertyName, float value);
    void CreateAnimatableArithmeticProperty(const std::string& propertyName, RefPtr<CustomAnimatableArithmetic>& value,
        std::function<void(const RefPtr<CustomAnimatableArithmetic>&)>& onCallbackEvent);
    void UpdateAnimatableArithmeticProperty(const std::string& propertyName, RefPtr<CustomAnimatableArithmetic>& value);

    void SetHitTestMode(HitTestMode mode);
    HitTestMode GetHitTestMode() const override;

    std::string ProvideRestoreInfo();

    static std::vector<RefPtr<FrameNode>> GetNodesById(const std::unordered_set<int32_t>& set);

    void SetViewPort(RectF viewPort)
    {
        viewPort_ = viewPort;
    }

    std::optional<RectF> GetViewPort() const;

    enum class SceneStatus {
        START,
        RUNNING,
        END,
    };
    // Frame Rate Controller(FRC) decides FrameRateRange by scene, speed and scene status
    void AddFRCSceneInfo(const std::string& name, float speed, SceneStatus status);

    OffsetF GetParentGlobalOffsetDuringLayout() const;
    void OnSetCacheCount(int32_t cacheCount, const std::optional<LayoutConstraintF>& itemConstraint) override {};

    // layoutwrapper function override
    const RefPtr<LayoutAlgorithmWrapper>& GetLayoutAlgorithm(bool needReset = false) override;

    void Measure(const std::optional<LayoutConstraintF>& parentConstraint) override;

    // Called to perform layout children.
    void Layout() override;

    int32_t GetTotalChildCount() const override
    {
        return UINode::TotalChildCount();
    }

    const RefPtr<GeometryNode>& GetGeometryNode() const override
    {
        return geometryNode_;
    }

    void SetLayoutProperty(const RefPtr<LayoutProperty>& layoutProperty)
    {
        layoutProperty_ = layoutProperty;
        layoutProperty_->SetHost(WeakClaim(this));
    }

    const RefPtr<LayoutProperty>& GetLayoutProperty() const override
    {
        return layoutProperty_;
    }

    RefPtr<LayoutWrapper> GetOrCreateChildByIndex(uint32_t index, bool addToRenderTree = true) override;
    const std::list<RefPtr<LayoutWrapper>>& GetAllChildrenWithBuild(bool addToRenderTree = true) override;
    void RemoveChildInRenderTree(uint32_t index) override;
    void RemoveAllChildInRenderTree() override;
    void DoRemoveChildInRenderTree(uint32_t index, bool isAll) override;
    const std::string& GetHostTag() const override
    {
        return GetTag();
    }

    bool IsActive() const override
    {
        return isActive_;
    }

    void SetActive(bool active = true) override;

    bool IsOutOfLayout() const override
    {
        return renderContext_->HasPosition();
    }

    bool SkipMeasureContent() const override;
    float GetBaselineDistance() const override;
    void SetCacheCount(
        int32_t cacheCount = 0, const std::optional<LayoutConstraintF>& itemConstraint = std::nullopt) override;

    void SyncGeometryNode();
    RefPtr<UINode> GetFrameChildByIndex(uint32_t index) override;
    bool CheckNeedForceMeasureAndLayout() override;

private:
    void MarkNeedRender(bool isRenderBoundary);
    bool IsNeedRequestParentMeasure() const;
    void UpdateLayoutPropertyFlag() override;
    void ForceUpdateLayoutPropertyFlag(PropertyChangeFlag propertyChangeFlag) override;
    void AdjustParentLayoutFlag(PropertyChangeFlag& flag) override;

    void UpdateChildrenLayoutWrapper(const RefPtr<LayoutWrapperNode>& self, bool forceMeasure, bool forceLayout);
    void AdjustLayoutWrapperTree(const RefPtr<LayoutWrapperNode>& parent, bool forceMeasure, bool forceLayout) override;

    LayoutConstraintF GetLayoutConstraint() const;
    OffsetF GetParentGlobalOffset() const;

    RefPtr<PaintWrapper> CreatePaintWrapper();
    void LayoutOverlay();

    void OnGenerateOneDepthVisibleFrame(std::list<RefPtr<FrameNode>>& visibleList) override;
    void OnGenerateOneDepthVisibleFrameWithTransition(
        std::list<RefPtr<FrameNode>>& visibleList, uint32_t index) override;
    void OnGenerateOneDepthAllFrame(std::list<RefPtr<FrameNode>>& allList) override;

    bool IsMeasureBoundary();
    bool IsRenderBoundary();

    bool OnRemoveFromParent(bool allowTransition) override;
    bool RemoveImmediately() const override;

    // dump self info.
    void DumpInfo() override;

    void DumpOverlayInfo();

    void FocusToJsonValue(std::unique_ptr<JsonValue>& json) const;
    void MouseToJsonValue(std::unique_ptr<JsonValue>& json) const;
    void TouchToJsonValue(std::unique_ptr<JsonValue>& json) const;
    void GeometryNodeToJsonValue(std::unique_ptr<JsonValue>& json) const;

    bool GetTouchable() const;
    virtual std::vector<RectF> GetResponseRegionList(const RectF& rect, int32_t sourceType);
    bool InResponseRegionList(const PointF& parentLocalPoint, const std::vector<RectF>& responseRegionList) const;

    void ProcessAllVisibleCallback(
        std::unordered_map<double, VisibleCallbackInfo>& visibleAreaCallbacks, double currentVisibleRatio);
    void OnVisibleAreaChangeCallback(
        VisibleCallbackInfo& callbackInfo, bool visibleType, double currentVisibleRatio, bool isHandled);
    double CalculateCurrentVisibleRatio(const RectF& visibleRect, const RectF& renderRect);

    // set costom background layoutConstraint
    void SetBackgroundLayoutConstraint(const RefPtr<FrameNode>& customNode);

    struct ZIndexComparator {
        bool operator()(const WeakPtr<FrameNode>& weakLeft, const WeakPtr<FrameNode>& weakRight) const
        {
            auto left = weakLeft.Upgrade();
            auto right = weakRight.Upgrade();
            if (left && right) {
                return left->GetRenderContext()->GetZIndexValue(1) < right->GetRenderContext()->GetZIndexValue(1);
            }
            return false;
        }
    };
    // sort in ZIndex.
    std::multiset<WeakPtr<FrameNode>, ZIndexComparator> frameChildren_;
    RefPtr<GeometryNode> geometryNode_ = MakeRefPtr<GeometryNode>();

    std::list<std::function<void()>> destroyCallbacks_;
    std::unordered_map<double, VisibleCallbackInfo> visibleAreaUserCallbacks_;
    std::unordered_map<double, VisibleCallbackInfo> visibleAreaInnerCallbacks_;

    RefPtr<AccessibilityProperty> accessibilityProperty_;
    RefPtr<LayoutProperty> layoutProperty_;
    RefPtr<PaintProperty> paintProperty_;
    RefPtr<RenderContext> renderContext_ = RenderContext::Create();
    RefPtr<EventHub> eventHub_;
    RefPtr<Pattern> pattern_;

    RefPtr<FrameNode> backgroundNode_;
    std::function<RefPtr<UINode>()> builderFunc_;
    std::unique_ptr<RectF> lastFrameRect_;
    std::unique_ptr<OffsetF> lastParentOffsetToWindow_;
    std::set<std::string> allowDrop_;
    std::optional<RectF> viewPort_;

    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithm_;
    RefPtr<GeometryNode> oldGeometryNode_;
    std::optional<bool> skipMeasureContent_;
    std::unique_ptr<FramePorxy> frameProxy_;

    bool needSyncRenderTree_ = false;

    bool isLayoutDirtyMarked_ = false;
    bool isRenderDirtyMarked_ = false;
    bool isMeasureBoundary_ = false;
    bool hasPendingRequest_ = false;

    // for container, this flag controls only the last child in touch area is consuming event.
    bool exclusiveEventForChild_ = false;
    bool isActive_ = false;
    bool isResponseRegion_ = false;
    bool bypass_ = false;

    double lastVisibleRatio_ = 0.0;

    // internal node such as Text in Button CreateWithLabel
    // should not seen by preview inspector or accessibility
    bool isInternal_ = false;

    std::string nodeName_;

    bool draggable_ = false;
    bool userSet_ = false;

    std::map<std::string, RefPtr<NodeAnimatablePropertyBase>> nodeAnimatablePropertyMap_;

    bool isRestoreInfoUsed_ = false;

    RefPtr<FrameNode> overlayNode_;

    friend class RosenRenderContext;
    friend class RenderContext;
    friend class Pattern;

    ACE_DISALLOW_COPY_AND_MOVE(FrameNode);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_FRAME_NODE_H
