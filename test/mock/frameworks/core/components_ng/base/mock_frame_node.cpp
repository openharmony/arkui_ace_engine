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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"

#include "base/json/json_util.h"
#include "core/components_ng/property/accessibility_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/extension_handler.h"
#include "core/components_ng/render/adapter/sampler_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/common/recorder/exposure_processor.h"
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
    : UINode(tag, nodeId, isRoot), LayoutWrapper(WeakClaim(this)), pattern_(pattern),isLayoutNode_(isLayoutNode)
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

void FrameNode::OnDelete()
{}

bool FrameNode::IsAtomicNode() const
{
    return false;
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

void FrameNode::AdjustLayoutWrapperTree(
    const RefPtr<LayoutWrapperNode>& parent, bool forceMeasure, bool forceLayout)
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
}


namespace OHOS::Ace::NG {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

void FrameNode::AddCustomProperty(const std::string& key, const std::string& value)
{
}

void FrameNode::AdjustParentLayoutFlag(PropertyChangeFlag& flag)
{
}

void FrameNode::AfterMountToParent()
{
}

uint32_t FrameNode::CallAIFunction(const std::string& functionName, const std::string& params)
{
    static constexpr uint32_t AI_CALL_SUCCESS = 0;
    static constexpr uint32_t AI_CALLER_INVALID = 1;
    static constexpr uint32_t AI_CALL_FUNCNAME_INVALID = 2;
    if (aiCallerHelper_) {
        return aiCallerHelper_->onAIFunctionCaller(functionName, params) ? AI_CALL_SUCCESS : AI_CALL_FUNCNAME_INVALID;
    }
    return AI_CALLER_INVALID;
}

bool FrameNode::CheckAutoSave()
{
    return {};
}

bool FrameNode::CheckNeedForceMeasureAndLayout()
{
    return {};
}

void FrameNode::CollectSelfAxisResult(const PointF& globalPoint, const PointF& localPoint, bool& consumed, const PointF& parentRevertPoint, AxisTestResult& axisResult, bool& preventBubbling, HitTestResult& testResult, TouchRestrict& touchRestrict, bool blockHierarchy)
{
}

void FrameNode::CreateEventHubInner()
{
    if (eventHub_) {
        return;
    }
    if (pattern_) {
        eventHub_ = pattern_->CreateEventHub();
    }
    if (!eventHub_) {
        eventHub_ = MakeRefPtr<EventHub>();
    }
    eventHub_->AttachHost(WeakClaim(this));
}

RefPtr<FrameNode> FrameNode::CreateFrameNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot)
{
    auto frameNode = MakeRefPtr<FrameNode>(tag, nodeId, pattern ? pattern : MakeRefPtr<Pattern>(), isRoot);
    ElementRegister::GetInstance()->AddUINode(frameNode);
    return frameNode;
}

RefPtr<FrameNode> FrameNode::CreateFrameNodeWithTree(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
{
    auto frameNode = CreateFrameNode(tag, nodeId, pattern, true);
    frameNode->SetDepth(1);
    return frameNode;
}

void FrameNode::DoRemoveChildInRenderTree(uint32_t index, bool isAll)
{
}

void FrameNode::DoSetActiveChildRange(int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache)
{
}

void FrameNode::DumpAdvanceInfo()
{
}

void FrameNode::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
}

void FrameNode::DumpInfo()
{
}

void FrameNode::DumpInfo(std::unique_ptr<JsonValue>& json)
{
}

void FrameNode::DumpSimplifyInfo(std::shared_ptr<JsonValue>& json)
{
}

void FrameNode::DumpSimplifyInfoOnlyForParamConfig(std::shared_ptr<JsonValue>& json, ParamConfig config)
{
}

void FrameNode::DumpViewDataPageNode(RefPtr<ViewDataWrap> viewDataWrap, bool needsRecordData)
{
}

void FrameNode::FromJson(const std::unique_ptr<JsonValue>& json)
{
}

namespace {
class MockRecursiveLock : public RecursiveLock {};
} // namespace

ChildrenListWithGuard FrameNode::GetAllChildrenWithBuild(bool addToRenderTree)
{
    static MockRecursiveLock lock;
    static const std::list<RefPtr<LayoutWrapper>> children;
    return ChildrenListWithGuard(children, lock);
}

RefPtr<FrameNode> FrameNode::GetAncestorNodeOfFrame(bool checkBoundary) const
{
    return {};
}

float FrameNode::GetBaselineDistance() const
{
    return {};
}

RefPtr<LayoutWrapper> FrameNode::GetChildByIndex(uint32_t index, bool isCache)
{
    return {};
}

const RefPtr<FocusHub>& FrameNode::GetFocusHub() const
{
    return focusHub_;
}

FocusType FrameNode::GetFocusType() const
{
    return focusHub_ ? focusHub_->GetFocusType() : FocusType::DISABLE;
}

RefPtr<UINode> FrameNode::GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache , bool addToRenderTree)
{
    return {};
}

RefPtr<UINode> FrameNode::GetFrameChildByIndexWithoutExpanded(uint32_t index)
{
    return {};
}

void FrameNode::GetInspectorValue()
{
}

const RefPtr<LayoutAlgorithmWrapper>& FrameNode::GetLayoutAlgorithm(bool needReset)
{
    static const RefPtr<LayoutAlgorithmWrapper> value {};
    return value;
}

LayoutConstraintF FrameNode::GetLayoutConstraint() const
{
    return {};
}

std::vector<RefPtr<FrameNode>> FrameNode::GetNodesById(const std::unordered_set<int32_t>& set)
{
    std::vector<RefPtr<FrameNode>> nodes;
    nodes.reserve(set.size());
    auto elementRegister = ElementRegister::GetInstance();
    for (const auto nodeId : set) {
        auto frameNode = elementRegister->GetSpecificItemById<FrameNode>(nodeId);
        if (frameNode) {
            nodes.emplace_back(frameNode);
        }
    }
    return nodes;
}

RefPtr<AccessibilityProperty>& FrameNode::GetOrCreateAccessibilityProperty()
{
    static RefPtr<AccessibilityProperty> value {};
    return value;
}

const RefPtr<FocusHub>& FrameNode::GetOrCreateFocusHub(FocusType type, bool focusable, FocusStyleType focusStyleType, const std::unique_ptr<FocusPaintParam>& paintParamsPtr)
{
    (void)focusStyleType;
    (void)paintParamsPtr;
    if (!focusHub_) {
        focusHub_ = AceType::MakeRefPtr<FocusHub>(WeakClaim(this), type, focusable);
    }
    return focusHub_;
}

RefPtr<FocusHub> FrameNode::GetOrCreateFocusHub()
{
    if (!focusHub_) {
        focusHub_ = AceType::MakeRefPtr<FocusHub>(WeakClaim(this));
    }
    return focusHub_;
}

const RefPtr<FocusHub>& FrameNode::GetOrCreateFocusHub(const FocusPattern& focusPattern)
{
    if (!focusHub_) {
        focusHub_ = AceType::MakeRefPtr<FocusHub>(WeakClaim(this), focusPattern);
    }
    return focusHub_;
}

RefPtr<FrameNode> FrameNode::GetPageNode()
{
    return {};
}

OffsetF FrameNode::GetPaintRectOffsetNG(bool excludeSelf , bool checkBoundary) const
{
    return {};
}

OffsetF FrameNode::GetPositionToScreenWithTransform()
{
    return {};
}

RectF FrameNode::GetRectWithRender()
{
    return {};
}

std::vector<RectF> FrameNode::GetResponseRegionList(const RectF& rect, int32_t sourceType, int32_t sourceTool)
{
    return {};
}

void FrameNode::GetResponseRegionListByTraversal(std::vector<RectF>& responseRegionList, const RectF& windowRect)
{
}

std::vector<RectF> FrameNode::GetResponseRegionListRaw(const RectF& rect, int32_t sourceType)
{
    return {};
}

bool FrameNode::HasVirtualNodeAccessibilityProperty()
{
    return {};
}

bool FrameNode::IsOutOfTouchTestRegion(const PointF& parentLocalPoint, const TouchEvent& touchEvent, std::vector<RectF>* regionList)
{
    return {};
}

void FrameNode::Layout()
{
}

void FrameNode::MarkDirtyNode(PropertyChangeFlag extraFlag)
{
    (void)extraFlag;
    isLayoutDirtyMarked_ = true;
}

void FrameNode::MarkDirtyNode(bool isMeasureBoundary, bool isRenderBoundary, PropertyChangeFlag extraFlag)
{
    (void)isMeasureBoundary;
    (void)isRenderBoundary;
    MarkDirtyNode(extraFlag);
}

void FrameNode::MarkModifyDone()
{
}

void FrameNode::MarkNeedSyncRenderTree(bool needRebuild)
{
}

bool FrameNode::MarkRemoving()
{
    return {};
}

void FrameNode::Measure(const std::optional<LayoutConstraintF>& parentConstraint)
{
}

void FrameNode::NotifyChange(int32_t changeIdx, int32_t count, int64_t id, NotificationType notificationType)
{
}

void FrameNode::NotifyColorModeChange(uint32_t colorMode)
{
}

void FrameNode::NotifyColorModeChange(uint32_t colorMode, bool recursive)
{
}

void FrameNode::NotifyFillRequestFailed(int32_t errCode, const std::string& fillContent , bool isPopup)
{
}

void FrameNode::NotifyFillRequestSuccess(RefPtr<ViewDataWrap> viewDataWrap, RefPtr<PageNodeInfoWrap> nodeWrap, AceAutoFillType autoFillType, AceAutoFillTriggerType triggerType)
{
}

void FrameNode::NotifyWebPattern(bool isRegister)
{
}

void FrameNode::OnAccessibilityEvent(AccessibilityEventType eventType, WindowsContentChangeTypes windowsContentChangeType , bool sendByNode)
{
}

void FrameNode::OnAccessibilityEvent(AccessibilityEventType eventType, int32_t startIndex, int32_t endIndex)
{
}

void FrameNode::OnAccessibilityEvent(AccessibilityEventType eventType, const std::string& beforeText, const std::string& latestContent)
{
}

void FrameNode::OnAccessibilityEvent(AccessibilityEventType eventType, int64_t stackNodeId, WindowsContentChangeTypes windowsContentChangeType)
{
}

void FrameNode::OnAccessibilityEvent(AccessibilityEventType eventType, const std::string& textAnnouncedForAccessibility)
{
}

void FrameNode::OnAttachToBuilderNode(NodeStatus nodeStatus)
{
}

void FrameNode::OnAttachToMainTree(bool recursive)
{
}

void FrameNode::OnAutoEventParamUpdate(const std::string& value)
{
}

void FrameNode::OnCollectRemoved()
{
}

void FrameNode::OnDetachFromMainTree(bool recursive, PipelineContext* context)
{
}

void FrameNode::OnFreezeStateChange()
{
}

void FrameNode::OnGenerateOneDepthAllFrame(std::list<RefPtr<FrameNode>>& allList)
{
}

void FrameNode::OnGenerateOneDepthVisibleFrame(std::list<RefPtr<FrameNode>>& visibleList)
{
}

void FrameNode::OnGenerateOneDepthVisibleFrameWithOffset(std::list<RefPtr<FrameNode>>& visibleList, OffsetF& offset)
{
}

void FrameNode::OnGenerateOneDepthVisibleFrameWithTransition(std::list<RefPtr<FrameNode>>& visibleList)
{
}

void FrameNode::OnNotifyMemoryLevel(int32_t level)
{
}

void FrameNode::OnOffscreenProcessResource()
{
}

void FrameNode::OnRecycle()
{
}

bool FrameNode::OnRemoveFromParent(bool allowTransition)
{
    return {};
}

void FrameNode::OnReuse()
{
}

void FrameNode::OnWindowActivated()
{
}

void FrameNode::OnWindowDeactivated()
{
}

void FrameNode::OnWindowFocused()
{
}

void FrameNode::OnWindowHide()
{
}

void FrameNode::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
}

void FrameNode::OnWindowUnfocused()
{
}

void FrameNode::PaintDebugBoundary(bool flag)
{
}

void FrameNode::ProcessFrameNodeChangeFlag()
{
}

void FrameNode::ProcessFreezeNode()
{
}

std::string FrameNode::ProvideRestoreInfo()
{
    if (pattern_) {
        return pattern_->ProvideRestoreInfo();
    }
    return "";
}

bool FrameNode::ReachResponseDeadline() const
{
    return {};
}

void FrameNode::RebuildRenderContextTree()
{
}

void FrameNode::RecycleItemsByIndex(int32_t start, int32_t end)
{
}

void FrameNode::RemoveAllChildInRenderTree()
{
}

void FrameNode::RemoveChildInRenderTree(uint32_t index)
{
}

void FrameNode::RemoveCustomProperty(const std::string& key)
{
}

bool FrameNode::RemoveImmediately() const
{
    return {};
}

bool FrameNode::RenderCustomChild(int64_t deadline)
{
    return {};
}

bool FrameNode::RequestParentDirty()
{
    return {};
}

bool FrameNode::SelfExpansiveToKeyboard()
{
    return {};
}

void FrameNode::SetActiveChildRange(int32_t start, int32_t end, int32_t cacheStart , int32_t cacheEnd , bool showCached)
{
}

void FrameNode::SetActiveChildRange(const std::optional<ActiveChildSets>& activeChildSets, const std::optional<ActiveChildRange>& activeChildRange)
{
}

void FrameNode::SetCacheCount(int32_t cacheCount , const std::optional<LayoutConstraintF>& itemConstraint)
{
}

void FrameNode::SetIsFree(bool isFree)
{
}

void FrameNode::SetNodeFreeze(bool isFreeze)
{
}

void FrameNode::SetOnAreaChangeCallback(OnAreaChangedFunc&& callback)
{
}

bool FrameNode::SetParentLayoutConstraint(const SizeF& size) const
{
    return {};
}

bool FrameNode::SkipMeasureContent() const
{
    return {};
}

void FrameNode::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
}

void FrameNode::ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const
{
}

void FrameNode::TriggerOnAreaChangeCallback(uint64_t nanoTimestamp, int32_t areaChangeMinDepth)
{
}

void FrameNode::TryVisibleChangeOnDescendant(VisibleType preVisibility, VisibleType currentVisibility)
{
}

void FrameNode::UpdateLayoutConstraint(const MeasureProperty& calcLayoutConstraint)
{
}

void FrameNode::ChangeSensitiveStyle(bool isSensitive)
{
}

void FrameNode::ClearSubtreeLayoutAlgorithm(bool includeSelf, bool clearEntireTree)
{
}

void FrameNode::FlushUpdateAndMarkDirty()
{
}

RefPtr<UINode> FrameNode::GetCurrentPageRootNode()
{
    return {};
}

RefPtr<LayoutWrapper> FrameNode::GetOrCreateChildByIndex(uint32_t index, bool addToRenderTree, bool isCache)
{
    return {};
}

const RefPtr<Pattern>& FrameNode::GetPattern() const
{
    return pattern_;
}

void FrameNode::InitializePatternAndContext()
{
}

bool FrameNode::IsVisibleAndActive() const
{
    return {};
}

void FrameNode::OnInspectorIdUpdate(const std::string& id)
{
}

void FrameNode::OnMountToParentDone()
{
}

void FrameNode::OnThemeScopeUpdate(int32_t themeScopeId)
{
}

void FrameNode::OnWindowShow()
{
}

void FrameNode::SetAICallerHelper(const std::shared_ptr<AICallerHelper>& aiCallerHelper)
{
    aiCallerHelper_ = aiCallerHelper;
}

void FrameNode::SetActive(bool active, bool needRebuildRenderContext)
{
}

void FrameNode::SetOverlayNodeIsFree(bool isFree)
{
}

void FrameNode::TriggerVisibleAreaChangeCallback(uint64_t timestamp, bool forceDisappear, int32_t isVisibleChangeMinDepth)
{
}
#pragma clang diagnostic pop
} // namespace OHOS::Ace::NG
