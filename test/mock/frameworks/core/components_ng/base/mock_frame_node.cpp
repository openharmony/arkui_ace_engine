/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "base/json/json_util.h"
#include "core/common/recorder/exposure_processor.h"
#include "core/components_ng/animation/geometry_transition.h"
#include "core/components_ng/base/extension_handler.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/badge/badge_accessibility_property.h"
#include "core/components_ng/pattern/button/toggle_button_accessibility_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_accessibility_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_accessibility_property.h"
#include "core/components_ng/pattern/container_modal/container_modal_accessibility_property.h"
#include "core/components_ng/pattern/indexer/indexer_accessibility_property.h"
#include "core/components_ng/pattern/list/list_accessibility_property.h"
#include "core/components_ng/pattern/list/list_item_accessibility_property.h"
#include "core/components_ng/pattern/list/list_item_group_accessibility_property.h"
#include "core/components_ng/pattern/marquee/marquee_accessibility_property.h"
#include "core/components_ng/pattern/menu/menu_accessibility_property.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_accessibility_property.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_accessibility_property.h"
#include "core/components_ng/pattern/navigation/title_bar_accessibility_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/date_picker/datepicker_accessibility_property.h"
#include "core/components_ng/pattern/date_picker/datepicker_column_accessibility_property.h"
#include "core/components_ng/pattern/progress/progress_accessibility_property.h"
#include "core/components_ng/pattern/radio/radio_accessibility_property.h"
#include "core/components_ng/pattern/rating/rating_accessibility_property.h"
#include "core/components_ng/pattern/refresh/refresh_accessibility_property.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_accessibility_property.h"
#include "core/components_ng/pattern/scroll/scroll_accessibility_property.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_accessibility_property.h"
#include "core/components_ng/pattern/security_component/security_component_accessibility_property.h"
#include "core/components_ng/pattern/select/select_accessibility_property.h"
#include "core/components_ng/pattern/slider/slider_accessibility_property.h"
#include "core/components_ng/pattern/stepper/stepper_accessibility_property.h"
#include "core/components_ng/pattern/swiper/swiper_accessibility_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_accessibility_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_accessibility_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_item_accessibility_property.h"
#include "core/components_ng/pattern/text/text_accessibility_property.h"
#include "core/components_ng/pattern/text_clock/text_clock_accessibility_property.h"
#include "core/components_ng/pattern/text_field/text_field_accessibility_property.h"
#include "core/components_ng/pattern/text_picker/textpicker_accessibility_property.h"
#include "core/components_ng/pattern/text_picker/textpicker_row_accessibility_property.h"
#include "core/components_ng/pattern/texttimer/text_timer_accessibility_property.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_accessibility_property.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_accessibility_property.h"
#include "core/components_ng/pattern/toast/toast_accessibility_property.h"
#include "core/components_ng/pattern/toggle/switch_accessibility_property.h"
#include "core/components_ng/pattern/video/video_accessibility_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_accessibility_property.h"
#include "core/components_ng/pattern/web/web_accessibility_property.h"
#include "core/components_ng/property/accessibility_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/smart_gesture_property.h"
#include "core/components_ng/render/adapter/sampler_manager.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "core/components_ng/render/render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class FrameNode::FrameProxy final {
public:
    FrameProxy() = default;
    ~FrameProxy() = default;
}; // namespace OHOS::Ace::NG

FrameNode::FrameNode(
    const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot, bool isLayoutNode)
    : UINode(tag, nodeId, isRoot), LayoutWrapper(WeakClaim(this)), pattern_(pattern), isLayoutNode_(isLayoutNode)
{}

FrameNode::~FrameNode() = default;

RefPtr<FrameNode> FrameNode::GetOrCreateFrameNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = ElementRegister::GetInstance()->GetSpecificItemById<FrameNode>(nodeId);
    if (frameNode) {
        return frameNode;
    }
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    return CreateFrameNode(tag, nodeId, pattern);
}

void FrameNode::OnDelete() {}

bool FrameNode::IsAtomicNode() const
{
    return false;
}

bool FrameNode::HasPositionProp() const
{
    CHECK_NULL_RETURN(renderContext_, false);
    return renderContext_->HasPosition() || renderContext_->HasOffset() || renderContext_->HasPositionEdges() ||
           renderContext_->HasOffsetEdges() || renderContext_->HasAnchor();
}

bool FrameNode::IsOutOfLayout() const
{
    CHECK_NULL_RETURN(renderContext_, false);
    return renderContext_->HasPosition() || renderContext_->HasPositionEdges();
}

void FrameNode::UpdateOcclusionCullingStatus(bool enable)
{
    if (renderContext_) {
        renderContext_->UpdateOcclusionCullingStatus(enable);
    }
}

void FrameNode::AttachContext(PipelineContext* context, bool recursive)
{
    (void)recursive;
    if (!context) {
        return;
    }
    context_ = context;
    context_->RegisterAttachedNode(this);
}

void FrameNode::DetachContext(bool recursive)
{
    (void)recursive;
    if (!context_) {
        return;
    }
    context_->RemoveAttachedNode(this);
    context_ = nullptr;
}

RefPtr<LayoutWrapperNode> FrameNode::CreateLayoutWrapper(bool forceMeasure, bool forceLayout)
{
    (void)forceMeasure;
    (void)forceLayout;
    return nullptr;
}

void FrameNode::MountToParent(
    const RefPtr<UINode>& parent, int32_t slot, bool silently, bool addDefaultTransition, bool addModalUiextension)
{
    if (!parent) {
        return;
    }
    parent->AddChild(Claim(this), slot, silently, addDefaultTransition, addModalUiextension);
}

void FrameNode::OnChildUpdateDone() {}

int32_t FrameNode::OnRecvCommand(const std::string& command)
{
    (void)command;
    return 0;
}

void FrameNode::OnConfigurationUpdate(const ConfigurationChange& configurationChange)
{
    (void)configurationChange;
}

void FrameNode::UpdateGeometryTransition() {}

void FrameNode::AdjustLayoutWrapperTree(const RefPtr<LayoutWrapperNode>& parent, bool forceMeasure, bool forceLayout)
{
    (void)parent;
    (void)forceMeasure;
    (void)forceLayout;
}

bool FrameNode::IsContextTransparent()
{
    return false;
}

HitTestResult FrameNode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const PointF& parentRevertPoint, TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId,
    ResponseLinkResult& responseLinkResult, bool isDispatch)
{
    (void)globalPoint;
    (void)parentLocalPoint;
    (void)parentRevertPoint;
    (void)touchRestrict;
    (void)result;
    (void)touchId;
    (void)responseLinkResult;
    (void)isDispatch;
    return HitTestResult::BUBBLING;
}

HitTestResult FrameNode::MouseTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    MouseTestResult& onMouseResult, MouseTestResult& onHoverResult, RefPtr<FrameNode>& hoverNode)
{
    (void)globalPoint;
    (void)parentLocalPoint;
    (void)onMouseResult;
    (void)onHoverResult;
    (void)hoverNode;
    return HitTestResult::BUBBLING;
}

HitTestResult FrameNode::AxisTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const PointF& parentRevertPoint, TouchRestrict& touchRestrict, AxisTestResult& axisResult)
{
    (void)globalPoint;
    (void)parentLocalPoint;
    (void)parentRevertPoint;
    (void)touchRestrict;
    (void)axisResult;
    return HitTestResult::BUBBLING;
}

HitTestMode FrameNode::GetHitTestMode() const
{
    return HitTestMode::HTMDEFAULT;
}

void FrameNode::UpdateLayoutPropertyFlag() {}

void FrameNode::ForceUpdateLayoutPropertyFlag(PropertyChangeFlag propertyChangeFlag)
{
    (void)propertyChangeFlag;
}

void FrameNode::ReportSelectedText(bool isRegister)
{
    (void)isRegister;
}

RefPtr<FrameNode> FrameNode::CreateFrameNode(
    const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot)
{
    (void)isRoot;
    return AceType::MakeRefPtr<FrameNode>(tag, nodeId, pattern);
}

RefPtr<FrameNode> FrameNode::GetFrameNode(const std::string& tag, int32_t nodeId)
{
    return nullptr;
}

void FrameNode::SetGeometryNode(const RefPtr<GeometryNode>& geometryNode)
{
    geometryNode_ = geometryNode;
}

RefPtr<PaintWrapper> FrameNode::CreatePaintWrapper()
{
    return nullptr;
}

std::pair<uint32_t, std::string> FrameNode::CallAIFunction(const std::string& functionName, const std::string& params,
    const sptr<IRemoteObject>& remoteObj)
{
    (void)functionName;
    (void)params;
    (void)remoteObj;
    return { 0, "" };
}

RefPtr<GestureEventHub> FrameNode::GetOrCreateGestureEventHub()
{
    return nullptr;
}

const RefPtr<Pattern>& FrameNode::GetPattern() const
{
    return pattern_;
}

const char* FrameNode::GetLayoutPropertyTypeName() const
{
    return "";
}

const char* FrameNode::GetPaintPropertyTypeName() const
{
    return "";
}

const char* FrameNode::GetPatternTypeName() const
{
    return "";
}

bool FrameNode::ShouldDetectAceObjTypeConvertion()
{
    return false;
}

void FrameNode::MarkDirtyNode(PropertyChangeFlag extraFlag)
{
    (void)extraFlag;
}

void FrameNode::MarkNeedSyncRenderTree(bool needRebuild)
{
    (void)needRebuild;
}

void FrameNode::RebuildRenderContextTree() {}

void FrameNode::OnWindowShow() {}

void FrameNode::OnWindowHide() {}

void FrameNode::OnMountToParentDone() {}

void FrameNode::AdjustParentLayoutFlag(uint32_t& flag)
{
    (void)flag;
}

void FrameNode::FlushUpdateAndMarkDirty() {}

void FrameNode::DumpInfo() {}

void FrameNode::CreateEventHubInner() {}

bool FrameNode::RenderCustomChild(int64_t deadline)
{
    (void)deadline;
    return false;
}

void FrameNode::OnWindowFocused() {}

void FrameNode::OnWindowUnfocused() {}

void FrameNode::OnWindowActivated() {}

void FrameNode::OnWindowDeactivated() {}

void FrameNode::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason reason)
{
    (void)width;
    (void)height;
    (void)reason;
}

void FrameNode::NotifyColorModeChange(uint32_t colorMode)
{
    (void)colorMode;
}

void FrameNode::NotifyColorModeChange(uint32_t colorMode, bool recursive)
{
    (void)colorMode;
    (void)recursive;
}

void FrameNode::OnNotifyMemoryLevel(int32_t level)
{
    (void)level;
}

void FrameNode::OnRecycle() {}

void FrameNode::OnReuse() {}

bool FrameNode::MarkRemoving()
{
    return false;
}

void FrameNode::OnAutoEventParamUpdate(const std::string& param)
{
    (void)param;
}

void FrameNode::OnInspectorIdUpdate(const std::string& id)
{
    (void)id;
}

void FrameNode::SetActive(bool active, bool needRebuildRenderContext)
{
    (void)active;
    (void)needRebuildRenderContext;
}

RefPtr<UINode> FrameNode::GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    (void)index;
    (void)needBuild;
    (void)isCache;
    (void)addToRenderTree;
    return nullptr;
}

void FrameNode::TryVisibleChangeOnDescendant(VisibleType preVisibility, VisibleType currentVisibility)
{
    (void)preVisibility;
    (void)currentVisibility;
}

void FrameNode::FromJson(const std::unique_ptr<JsonValue>& json)
{
    (void)json;
}

void FrameNode::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    (void)json;
    (void)filter;
}

void FrameNode::ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const
{
    (void)json;
    (void)config;
}
void FrameNode::AddCustomProperty(const std::string&, const std::string&) {}
void FrameNode::RemoveCustomProperty(const std::string&) {}
void FrameNode::ClearSubtreeLayoutAlgorithm(bool, bool) {}
void FrameNode::DoRemoveChildInRenderTree(uint32_t, bool) {}
void FrameNode::DoSetActiveChildRange(int, int, int, int, bool) {}
RefPtr<UINode> FrameNode::GetCurrentPageRootNode()
{
    return nullptr;
}
RefPtr<UINode> FrameNode::GetFrameChildByIndexWithoutExpanded(uint32_t)
{
    return nullptr;
}
void FrameNode::GetInspectorValue() {}
bool FrameNode::HasVirtualNodeAccessibilityProperty()
{
    return false;
}
bool FrameNode::IsVisibleAndActive() const
{
    return false;
}
void FrameNode::NotifyWebPattern(bool) {}
void FrameNode::OnGenerateOneDepthAllFrame(std::list<RefPtr<FrameNode>>&) {}
void FrameNode::OnGenerateOneDepthVisibleFrame(std::list<RefPtr<FrameNode>>&) {}
void FrameNode::OnGenerateOneDepthVisibleFrameWithOffset(std::list<RefPtr<FrameNode>>&, OffsetF&) {}
void FrameNode::OnGenerateOneDepthVisibleFrameWithTransition(std::list<RefPtr<FrameNode>>&) {}
bool FrameNode::OnRemoveFromParent(bool)
{
    return false;
}
void FrameNode::OnThemeScopeUpdate(int) {}
void FrameNode::SetIsFree(bool) {}
bool FrameNode::SetParentLayoutConstraint(const SizeF&) const
{
    return false;
}
void FrameNode::AfterMountToParent() {}
void FrameNode::InitializePatternAndContext() {}
void FrameNode::OnAttachToMainTree(bool) {}
void FrameNode::OnDetachFromMainTree(bool, PipelineContext*) {}
void FrameNode::OnAttachToBuilderNode(NodeStatus) {}
void FrameNode::OnFreezeStateChange() {}
void FrameNode::OnCollectRemoved() {}
void FrameNode::OnOffscreenProcessResource() {}
void FrameNode::SetNodeFreeze(bool) {}
bool FrameNode::RemoveImmediately() const
{
    return false;
}
void FrameNode::PaintDebugBoundary(bool) {}
void FrameNode::MarkModifyDone() {}
void FrameNode::DumpInfo(std::unique_ptr<JsonValue>&) {}
void FrameNode::DumpAdvanceInfo() {}
void FrameNode::DumpAdvanceInfo(std::unique_ptr<JsonValue>&) {}
void FrameNode::DumpSimplifyInfo(std::shared_ptr<JsonValue>&) {}
void FrameNode::DumpSimplifyInfoOnlyForParamConfig(std::shared_ptr<JsonValue>&, ParamConfig) {}
void FrameNode::DumpViewDataPageNode(RefPtr<ViewDataWrap>, bool) {}
bool FrameNode::CheckAutoSave()
{
    return false;
}
void FrameNode::CollectSelfAxisResult(const PointF&, const PointF&, bool&, const PointF&,
    std::list<RefPtr<AxisEventTarget>>&, bool&, HitTestResult&, TouchRestrict&, bool)
{}
bool FrameNode::CheckNeedForceMeasureAndLayout()
{
    return false;
}
float FrameNode::GetBaselineDistance() const
{
    return 0;
}
ChildrenListWithGuard FrameNode::GetAllChildrenWithBuild(bool)
{
    static std::list<RefPtr<LayoutWrapper>> empty;
    static RecursiveLock lock;
    return ChildrenListWithGuard(empty, lock);
}
RefPtr<LayoutWrapper> FrameNode::GetChildByIndex(uint32_t, bool)
{
    return nullptr;
}
const RefPtr<LayoutAlgorithmWrapper>& FrameNode::GetLayoutAlgorithm(bool)
{
    return layoutAlgorithm_;
}
RefPtr<LayoutWrapper> FrameNode::GetOrCreateChildByIndex(uint32_t, bool, bool)
{
    return nullptr;
}
void FrameNode::Measure(const std::optional<LayoutConstraintF>&) {}
void FrameNode::Layout() {}
bool FrameNode::SkipMeasureContent() const
{
    return false;
}
void FrameNode::SetCacheCount(int, const std::optional<LayoutConstraintF>&) {}
void FrameNode::RecycleItemsByIndex(int, int) {}
void FrameNode::SetActiveChildRange(int, int, int, int, bool) {}
void FrameNode::SetActiveChildRange(const std::optional<ActiveChildSets>&, const std::optional<ActiveChildRange>&) {}
void FrameNode::RemoveAllChildInRenderTree() {}
void FrameNode::RemoveChildInRenderTree(uint32_t) {}
bool FrameNode::ReachResponseDeadline() const
{
    return false;
}
bool FrameNode::RequestParentDirty()
{
    return false;
}
std::vector<RectF> FrameNode::GetResponseRegionList(const RectF&, int, int)
{
    return {};
}
std::vector<RectF> FrameNode::GetResponseRegionListRaw(const RectF&, int)
{
    return {};
}
bool FrameNode::IsOutOfTouchTestRegion(const PointF&, const TouchEvent&, std::vector<RectF>*)
{
    return false;
}
RefPtr<FrameNode> FrameNode::GetAncestorNodeOfFrame(bool) const
{
    return nullptr;
}
RectF FrameNode::GetTransformRectRelativeToWindow(bool) const
{
    return {};
}
const RefPtr<FocusHub>& FrameNode::GetOrCreateFocusHub(
    FocusType, bool, FocusStyleType, const std::unique_ptr<FocusPaintParam>&)
{
    static RefPtr<FocusHub> hub = MakeRefPtr<FocusHub>(WeakPtr<FrameNode>());
    return hub;
}
const RefPtr<FocusHub>& FrameNode::GetOrCreateFocusHub(const FocusPattern&)
{
    static RefPtr<FocusHub> hub = MakeRefPtr<FocusHub>(WeakPtr<FrameNode>());
    return hub;
}
RefPtr<FocusHub> FrameNode::GetOrCreateFocusHub()
{
    return MakeRefPtr<FocusHub>(WeakPtr<FrameNode>());
}
const RefPtr<FocusHub>& FrameNode::GetFocusHub() const
{
    static RefPtr<FocusHub> null;
    return null;
}
RefPtr<InputEventHub> FrameNode::GetOrCreateInputEventHub()
{
    return nullptr;
}
OffsetF FrameNode::GetPaintRectOffset(bool, bool, bool) const
{
    return {};
}
RectF FrameNode::GetRectWithRender()
{
    return {};
}
void FrameNode::MarkNeedRenderOnly() {}

FocusType FrameNode::GetFocusType() const
{
    return FocusType::DISABLE;
}

RefPtr<FrameNode> FrameNode::CreateFrameNodeWithTree(
    const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
{
    return nullptr;
}

void FrameNode::UpdateLayoutConstraint(const MeasureProperty& calcLayoutConstraint)
{
    (void)calcLayoutConstraint;
}

LayoutConstraintF FrameNode::GetLayoutConstraint() const
{
    LayoutConstraintF layoutConstraint;
    return layoutConstraint;
}

void FrameNode::FireLpxUpdateCallbacks() {}

std::vector<RefPtr<FrameNode>> FrameNode::GetNodesById(const std::unordered_set<int32_t>& set)
{
    std::vector<RefPtr<FrameNode>> nodes;
    return nodes;
}

void FrameNode::OnMixedMountChildAdded(const RefPtr<UINode>& child)
{
    (void)child;
}

void FrameNode::NotifyChange(int32_t index, int32_t count, int64_t id, NotificationType notificationType)
{
    (void)index;
    (void)count;
    (void)id;
    (void)notificationType;
}

void FrameNode::ProcessFreezeNode() {}

void FrameNode::ProcessFrameNodeChangeFlag() {}

void FrameNode::TriggerVisibleAreaChangeCallback(
    uint64_t timestamp, bool forceDisappear, int32_t isVisibleChangeMinDepth)
{
    (void)timestamp;
    (void)forceDisappear;
    (void)isVisibleChangeMinDepth;
}

void FrameNode::TriggerOnAreaChangeCallback(uint64_t nanoTimestamp, int32_t areaChangeMinDepth)
{
    (void)nanoTimestamp;
    (void)areaChangeMinDepth;
}

void FrameNode::SetOnAreaChangeCallback(OnAreaChangedFunc&& callback)
{
    (void)callback;
}

bool FrameNode::SelfExpansiveToKeyboard()
{
    return false;
}

void FrameNode::OnMixedMountChildRemoved(const RefPtr<UINode>& child)
{
    (void)child;
}

OffsetF FrameNode::GetPaintRectOffsetNG(bool excludeSelf, bool checkBoundary) const
{
    (void)excludeSelf;
    (void)checkBoundary;
    return {};
}

OffsetF FrameNode::GetPositionToScreenWithTransform()
{
    return {};
}

RefPtr<FrameNode> FrameNode::GetPageNode()
{
    return nullptr;
}

void FrameNode::NotifyFillRequestSuccess(RefPtr<ViewDataWrap> viewDataWrap, RefPtr<PageNodeInfoWrap> nodeWrap,
    AceAutoFillType autoFillType, AceAutoFillTriggerType triggerType)
{
    (void)viewDataWrap;
    (void)nodeWrap;
    (void)autoFillType;
    (void)triggerType;
}

void FrameNode::NotifyFillRequestSuccess(
    RefPtr<ViewDataWrap> viewDataWrap, RefPtr<PageNodeInfoWrap> nodeWrap, AceAutoFillType autoFillType)
{
    (void)viewDataWrap;
    (void)nodeWrap;
    (void)autoFillType;
}

void FrameNode::NotifyFillRequestFailed(int32_t errCode, const std::string& fillContent, bool isPopup)
{
    (void)errCode;
    (void)fillContent;
    (void)isPopup;
}

void FrameNode::SetAICallerHelper(const std::shared_ptr<AICallerHelper>& aiCallerHelper)
{
    (void)aiCallerHelper;
}

void FrameNode::OnAccessibilityEvent(
    AccessibilityEventType eventType, WindowsContentChangeTypes windowsContentChangeType, bool sendByNode)
{
    (void)eventType;
    (void)windowsContentChangeType;
    (void)sendByNode;
}

std::string FrameNode::ProvideRestoreInfo()
{
    return "";
}

void FrameNode::GetResponseRegionListByTraversal(std::vector<RectF>& responseRegionList, const RectF& windowRect)
{
    (void)responseRegionList;
    (void)windowRect;
}

void FrameNode::ChangeSensitiveStyle(bool isSensitive)
{
    (void)isSensitive;
}

void FrameNode::SetOverlayNode(const RefPtr<FrameNode>& overlayNode)
{
    (void)overlayNode;
}

void FrameNode::SetFocusPaintNode(const RefPtr<FrameNode>& accessibilityFocusPaintNode) {}

RefPtr<AccessibilityProperty>& FrameNode::GetOrCreateAccessibilityProperty()
{
    if (!accessibilityProperty_) {
        accessibilityProperty_ = MakeRefPtr<AccessibilityProperty>();
        accessibilityProperty_->SetHost(WeakClaim(this));
    }
    isAccessibilityPropertyInitialized_ = true;
    return accessibilityProperty_;
}

template<typename T>
ACE_FORCE_EXPORT RefPtr<T> FrameNode::GetAccessibilityProperty() const
{
    return DynamicCast<T>(const_cast<FrameNode*>(this)->GetOrCreateAccessibilityProperty());
}

template RefPtr<AccessibilityProperty> FrameNode::GetAccessibilityProperty<AccessibilityProperty>() const;

} // namespace OHOS::Ace::NG
