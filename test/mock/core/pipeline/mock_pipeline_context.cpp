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

#include "mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/mousestyle/mouse_style.h"
#include "base/utils/utils.h"
#include "core/accessibility/accessibility_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_advanced_register.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {

static bool g_setBoolStatus = false;
class MockAccessibilityManager : public AccessibilityManager {
public:
    MOCK_METHOD(void, SendAccessibilityAsyncEvent, (const AccessibilityEvent& accessibilityEvent), (override));
    MOCK_METHOD(void, SendWebAccessibilityAsyncEvent,
        (const AccessibilityEvent& accessibilityEvent, const RefPtr<NG::WebPattern>& webPattern), (override));
    MOCK_METHOD(void, UpdateVirtualNodeFocus, (), (override));
    MOCK_METHOD(int64_t, GenerateNextAccessibilityId, (), (override));
    MOCK_METHOD(RefPtr<AccessibilityNode>, CreateSpecializedNode,
        (const std::string& tag, int32_t nodeId, int32_t parentNodeId), (override));
    MOCK_METHOD(RefPtr<AccessibilityNode>, CreateAccessibilityNode,
        (const std::string& tag, int32_t nodeId, int32_t parentNodeId, int32_t itemIndex), (override));
    MOCK_METHOD(RefPtr<AccessibilityNode>, GetAccessibilityNodeById, (NodeId nodeId), (const, override));
    MOCK_METHOD(std::string, GetInspectorNodeById, (NodeId nodeId), (const, override));
    MOCK_METHOD(void, RemoveAccessibilityNodes, (RefPtr<AccessibilityNode> & node), (override));
    MOCK_METHOD(void, RemoveAccessibilityNodeById, (NodeId nodeId), (override));
    MOCK_METHOD(void, ClearPageAccessibilityNodes, (int32_t pageId), (override));
    MOCK_METHOD(void, SetRootNodeId, (int32_t nodeId), (override));
    MOCK_METHOD(void, TrySaveTargetAndIdNode,
        (const std::string& id, const std::string& target, const RefPtr<AccessibilityNode>& node), (override));
    MOCK_METHOD(void, HandleComponentPostBinding, (), (override));
    MOCK_METHOD(void, OnDumpInfo, (const std::vector<std::string>& params), (override));
    MOCK_METHOD(
        void, OnDumpInfoNG, (const std::vector<std::string>& params, uint32_t windowId, bool hasJson), (override));
    MOCK_METHOD(void, SetCardViewPosition, (int id, float offsetX, float offsetY), (override));
    MOCK_METHOD(void, SetCardViewParams, (const std::string& key, bool focus), (override));
    MOCK_METHOD(void, SetSupportAction, (uint32_t action, bool isEnable), (override));
    MOCK_METHOD(void, ClearNodeRectInfo, (RefPtr<AccessibilityNode> & node, bool isPopDialog), (override));
    MOCK_METHOD(void, AddComposedElement, (const std::string& key, const RefPtr<ComposedElement>& node), (override));
    MOCK_METHOD(void, RemoveComposedElementById, (const std::string& key), (override));
    MOCK_METHOD(WeakPtr<ComposedElement>, GetComposedElementFromPage, (NodeId nodeId), (override));
    MOCK_METHOD(void, TriggerVisibleChangeEvent, (), (override));
    MOCK_METHOD(void, AddVisibleChangeNode, (NodeId nodeId, double ratio, VisibleRatioCallback callback), (override));
    MOCK_METHOD(void, RemoveVisibleChangeNode, (NodeId nodeId), (override));
    MOCK_METHOD(bool, IsVisibleChangeNodeExists, (NodeId nodeId), (override));
    MOCK_METHOD(void, UpdateEventTarget, (NodeId id, BaseEventInfo& info), (override));
    MOCK_METHOD(void, SetWindowPos, (int32_t left, int32_t top, int32_t windowId), (override));
#ifdef WINDOW_SCENE_SUPPORTED
    MOCK_METHOD(void, SearchElementInfoByAccessibilityIdNG,
        (int64_t elementId, int32_t mode, std::list<Accessibility::AccessibilityElementInfo>& infos,
            const RefPtr<PipelineBase>& context, int64_t uiExtensionOffset),
        (override));
    MOCK_METHOD(void, SearchElementInfosByTextNG,
        (int64_t elementId, const std::string& text, std::list<Accessibility::AccessibilityElementInfo>& infos,
            const RefPtr<PipelineBase>& context, const int64_t uiExtensionOffset),
        (override));
    MOCK_METHOD(void, FindFocusedElementInfoNG,
        (int64_t elementId, int32_t focusType, Accessibility::AccessibilityElementInfo& info,
            const RefPtr<PipelineBase>& context, const int64_t uiExtensionOffset),
        (override));
    MOCK_METHOD(void, FocusMoveSearchNG,
        (int64_t elementId, int32_t direction, Accessibility::AccessibilityElementInfo& info,
            const RefPtr<PipelineBase>& context, const int64_t uiExtensionOffset),
        (override));
    MOCK_METHOD(bool, ExecuteExtensionActionNG,
        (int64_t elementId, const std::map<std::string, std::string>& actionArguments, int32_t action,
            const RefPtr<PipelineBase>& context, int64_t uiExtensionOffset),
        (override));
    MOCK_METHOD(bool, TransferAccessibilityAsyncEvent,
        (const Accessibility::AccessibilityEventInfo& eventInfo, int64_t uiExtensionOffset), (override));
    MOCK_METHOD(void, SendExtensionAccessibilityEvent,
        (const Accessibility::AccessibilityEventInfo& eventInfo, int64_t uiExtensionOffset), (override));
#endif
#ifdef WEB_SUPPORTED
    MOCK_METHOD(bool, RegisterWebInteractionOperationAsChildTree,
        (int64_t accessibilityId, const WeakPtr<NG::WebPattern>& webPattern), (override));
    MOCK_METHOD(bool, DeregisterWebInteractionOperationAsChildTree, (int32_t treeId), (override));
#endif
    void RegisterAccessibilityChildTreeCallback(
        int64_t elementId, const std::shared_ptr<AccessibilityChildTreeCallback>& callback) override
    {}
    void DeregisterAccessibilityChildTreeCallback(int64_t elementId) override {}
    void RegisterInteractionOperationAsChildTree(
        uint32_t parentWindowId, int32_t parentTreeId, int64_t parentElementId) override
    {
        Register(g_setBoolStatus);
    }
    void SetAccessibilityGetParentRectHandler(std::function<void(int32_t&, int32_t&)>&& callback) override {}
    void SetAccessibilityGetParentRectHandler(std::function<void(AccessibilityParentRectInfo&)>&& callback) override {}
    MOCK_METHOD(void, DeregisterInteractionOperationAsChildTree, (), (override));
    MOCK_METHOD(void, SendEventToAccessibilityWithNode,
        (const AccessibilityEvent& accessibilityEvent, const RefPtr<AceType>& node,
            const RefPtr<PipelineBase>& context),
        (override));
    MOCK_METHOD(void, RegisterAccessibilitySAObserverCallback,
        (int64_t elementId, const std::shared_ptr<AccessibilitySAObserverCallback>& callback), (override));
    MOCK_METHOD(void, DeregisterAccessibilitySAObserverCallback, (int64_t elementId), (override));
    MOCK_METHOD(bool, RegisterInteractionOperationAsChildTree, (const Registration& registration), (override));
    MOCK_METHOD(bool, DeregisterInteractionOperationAsChildTree, (uint32_t windowId, int32_t treeId), (override));
    MOCK_METHOD(void, TransferThirdProviderHoverEvent,
        (const WeakPtr<NG::FrameNode>& hostNode, const NG::PointF& point, SourceType source,
            NG::AccessibilityHoverEventType eventType, TimeStamp time),
        (override));
    MOCK_METHOD(bool, OnDumpChildInfoForThird,
        (int64_t hostElementId, const std::vector<std::string>& params, std::vector<std::string>& info), (override));
};
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
constexpr double DISPLAY_WIDTH = 720;
constexpr double DISPLAY_HEIGHT = 1280;
static std::list<PipelineContext::PredictTask> predictTasks_;
static Rect windowRect_;
} // namespace

RefPtr<MockPipelineContext> MockPipelineContext::pipeline_;

// mock_pipeline_context =======================================================
void MockPipelineContext::SetUp()
{
    pipeline_ = AceType::MakeRefPtr<MockPipelineContext>();
    pipeline_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    pipeline_->windowManager_ = AceType::MakeRefPtr<WindowManager>();
    pipeline_->rootWidth_ = DISPLAY_WIDTH;
    pipeline_->rootHeight_ = DISPLAY_HEIGHT;
    pipeline_->SetupRootElement();
    windowRect_ = { 0., 0., NG::DISPLAY_WIDTH, NG::DISPLAY_HEIGHT };
}

void MockPipelineContext::TearDown()
{
    if (pipeline_) {
        pipeline_->Destroy();
        pipeline_ = nullptr;
    }
    predictTasks_.clear();
}

RefPtr<MockPipelineContext> MockPipelineContext::GetCurrent()
{
    return pipeline_;
}

void MockPipelineContext::SetRootSize(double rootWidth, double rootHeight)
{
    rootWidth_ = rootWidth;
    rootHeight_ = rootHeight;
}

void MockPipelineContext::SetInstanceId(int32_t instanceId)
{
    pipeline_->instanceId_ = instanceId;
}

void MockPipelineContext::SetCurrentWindowRect(Rect rect)
{
    windowRect_ = rect;
}
// mock_pipeline_context =======================================================

// pipeline_context ============================================================
PipelineContext::PipelineContext()
{
    if (navigationMgr_) {
        navigationMgr_->SetPipelineContext(WeakClaim(this));
    }
}

float PipelineContext::GetCurrentRootWidth()
{
    return static_cast<float>(MockPipelineContext::GetCurrent()->rootWidth_);
}

void PipelineContext::RegisterTouchEventListener(const std::shared_ptr<ITouchEventCallback>& listener) {}

float PipelineContext::GetCurrentRootHeight()
{
    return static_cast<float>(MockPipelineContext::GetCurrent()->rootHeight_);
}

std::shared_ptr<NavigationController> PipelineContext::GetNavigationController(const std::string& id)
{
    return nullptr;
}

void PipelineContext::AddOrReplaceNavigationNode(const std::string& id, const WeakPtr<FrameNode>& node) {}

void PipelineContext::DeleteNavigationNode(const std::string& id) {}

RefPtr<PipelineContext> PipelineContext::GetCurrentContext()
{
    return MockPipelineContext::GetCurrent();
}

RefPtr<PipelineContext> PipelineContext::GetCurrentContextSafely()
{
    return MockPipelineContext::GetCurrent();
}

RefPtr<PipelineContext> PipelineContext::GetCurrentContextSafelyWithCheck()
{
    return MockPipelineContext::GetCurrent();
}

PipelineContext* PipelineContext::GetCurrentContextPtrSafely()
{
    auto context = MockPipelineContext::GetCurrent();
    return AceType::RawPtr(context);
}

PipelineContext* PipelineContext::GetCurrentContextPtrSafelyWithCheck()
{
    auto context = MockPipelineContext::GetCurrent();
    return AceType::RawPtr(context);
}

RefPtr<PipelineContext> PipelineContext::GetMainPipelineContext()
{
    return MockPipelineContext::GetCurrent();
}

RefPtr<PipelineContext> PipelineContext::GetContextByContainerId(int32_t /* containerId */)
{
    return MockPipelineContext::GetCurrent();
}

void PipelineContext::AddWindowFocusChangedCallback(int32_t nodeId) {}

void PipelineContext::RemoveWindowFocusChangedCallback(int32_t nodeId) {}

void PipelineContext::SetupRootElement()
{
    rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<RootPattern>());
    rootNode_->SetHostRootId(GetInstanceId());
    rootNode_->SetHostPageId(-1);
    rootNode_->SetActive(true);
    CalcSize idealSize { CalcLength(rootWidth_), CalcLength(rootHeight_) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    rootNode_->UpdateLayoutConstraint(layoutConstraint);
    auto rootFocusHub = rootNode_->GetOrCreateFocusHub();
    rootFocusHub->SetFocusType(FocusType::SCOPE);
    rootFocusHub->SetFocusable(true);
    rootNode_->AttachToMainTree(false, this);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<StagePattern>());
    rootNode_->AddChild(stageNode);
    stageManager_ = MakeRefPtr<StageManager>(stageNode);
    overlayManager_ = MakeRefPtr<OverlayManager>(rootNode_);
    fullScreenManager_ = MakeRefPtr<FullScreenManager>(rootNode_);
    selectOverlayManager_ = MakeRefPtr<SelectOverlayManager>(rootNode_);
    dragDropManager_ = MakeRefPtr<DragDropManager>();
    focusManager_ = MakeRefPtr<FocusManager>(AceType::Claim(this));
    sharedTransitionManager_ = MakeRefPtr<SharedOverlayManager>(rootNode_);
}

void PipelineContext::SetupSubRootElement()
{
    CHECK_RUN_ON(UI);
    appBgColor_ = Color::TRANSPARENT;
    rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<RootPattern>());
    rootNode_->SetHostRootId(GetInstanceId());
    rootNode_->SetHostPageId(-1);
    rootNode_->SetActive(true);
    CalcSize idealSize { CalcLength(rootWidth_), CalcLength(rootHeight_) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    rootNode_->UpdateLayoutConstraint(layoutConstraint);
    auto rootFocusHub = rootNode_->GetOrCreateFocusHub();
    rootFocusHub->SetFocusType(FocusType::SCOPE);
    rootFocusHub->SetFocusable(true);
    window_->SetRootFrameNode(rootNode_);
    rootNode_->AttachToMainTree(false, this);
    accessibilityManagerNG_ = MakeRefPtr<AccessibilityManagerNG>();
    // the subwindow for overlay not need stage
    stageManager_ = ViewAdvancedRegister::GetInstance()->GenerateStageManager(nullptr);
    if (!stageManager_) {
        stageManager_ = MakeRefPtr<StageManager>(nullptr);
    }
    overlayManager_ = MakeRefPtr<OverlayManager>(rootNode_);
    fullScreenManager_ = MakeRefPtr<FullScreenManager>(rootNode_);
    selectOverlayManager_ = MakeRefPtr<SelectOverlayManager>(rootNode_);
    dragDropManager_ = MakeRefPtr<DragDropManager>();
    focusManager_ = GetOrCreateFocusManager();
    postEventManager_ = MakeRefPtr<PostEventManager>();
}

void PipelineContext::SendEventToAccessibilityWithNode(
    const AccessibilityEvent& accessibilityEvent, const RefPtr<FrameNode>& node)
{}

void PipelineContext::OnTouchEvent(const TouchEvent& point, const RefPtr<FrameNode>& node, bool isSubPipe) {}

void PipelineContext::ReDispatch(KeyEvent& keyEvent) {}

void PipelineContext::OnMouseEvent(const MouseEvent& event, const RefPtr<FrameNode>& node) {}

void PipelineContext::OnMouseMoveEventForAxisEvent(const MouseEvent& event, const RefPtr<NG::FrameNode>& node) {};

void PipelineContext::OnAxisEvent(const AxisEvent& event, const RefPtr<FrameNode>& node) {}

void PipelineContext::OnTouchEvent(const TouchEvent& point, bool isSubPipe) {}

void PipelineContext::OnAccessibilityHoverEvent(const TouchEvent& point, const RefPtr<NG::FrameNode>& node) {}

void PipelineContext::OnPenHoverEvent(const TouchEvent& point, const RefPtr<NG::FrameNode>& node) {}

void PipelineContext::HandlePenHoverOut(const TouchEvent& point) {}

void PipelineContext::OnMouseEvent(const MouseEvent& event) {}

void PipelineContext::FlushTouchEvents() {}

void PipelineContext::OnAxisEvent(const AxisEvent& event) {}

void PipelineContext::OnDragEvent(
    const DragPointerEvent& pointerEvent, DragEventAction action, const RefPtr<NG::FrameNode>& node)
{}

void PipelineContext::OnIdle(int64_t deadline)
{
    const auto tasks(std::move(predictTasks_));
    for (const auto& task : tasks) {
        task(deadline, false);
    }
}

void PipelineContext::Destroy()
{
    dragDropManager_.Reset();
    rootNode_.Reset();
}

void PipelineContext::OnShow() {}

void PipelineContext::OnHide() {}

void PipelineContext::RemoveOnAreaChangeNode(int32_t nodeId) {}

void PipelineContext::AddWindowStateChangedCallback(int32_t nodeId) {}

void PipelineContext::RemoveWindowStateChangedCallback(int32_t nodeId) {}

void PipelineContext::AddNodesToNotifyMemoryLevel(int32_t nodeId) {}

void PipelineContext::RemoveNodesToNotifyMemoryLevel(int32_t nodeId) {}

void PipelineContext::WindowFocus(bool isFocus)
{
    onFocus_ = isFocus;
}

void PipelineContext::ContainerModalUnFocus() {}

void PipelineContext::ShowContainerTitle(bool isShow, bool hasDeco, bool needUpdate) {}

void PipelineContext::UpdateTitleInTargetPos(bool isShow, int32_t height) {}

void PipelineContext::SetContainerWindow(bool isShow, RRect& rRect) {}

void PipelineContext::SetAppBgColor(const Color& color) {}

void PipelineContext::SetWindowContainerColor(const Color& activeColor, const Color& inactiveColor) {};

void PipelineContext::ChangeDarkModeBrightness() {}

void PipelineContext::SetAppTitle(const std::string& title) {}

void PipelineContext::SetAppIcon(const RefPtr<PixelMap>& icon) {}

void PipelineContext::OnSurfaceDensityChanged(double density) {}

void PipelineContext::OnTransformHintChanged(uint32_t transform) {}

void PipelineContext::SetRootRect(double width, double height, double offset) {}

void PipelineContext::FlushBuild() {}

void PipelineContext::FlushBuildFinishCallbacks()
{
    decltype(buildFinishCallbacks_) buildFinishCallbacks(std::move(buildFinishCallbacks_));
    for (const auto& func : buildFinishCallbacks) {
        if (func) {
            func();
        }
    }
}

void PipelineContext::NotifyMemoryLevel(int32_t level) {}

void PipelineContext::FlushMessages() {}

void PipelineContext::FlushModifier() {}

void PipelineContext::FlushUITasks(bool triggeredByImplicitAnimation)
{
    if (!MockPipelineContext::GetCurrent()->UseFlushUITasks()) {
        return;
    }
    decltype(dirtyPropertyNodes_) dirtyPropertyNodes(std::move(dirtyPropertyNodes_));
    dirtyPropertyNodes_.clear();
    for (const auto& dirtyNode : dirtyPropertyNodes) {
        dirtyNode->ProcessPropertyDiff();
    }
    taskScheduler_->FlushTask();
    taskScheduler_->FlushAfterRenderTask();
}

void PipelineContext::FlushAfterLayoutCallbackInImplicitAnimationTask() {}

void PipelineContext::DetachNode(RefPtr<UINode>) {}

void PipelineContext::Finish(bool autoFinish) const {}

void PipelineContext::FlushVsync(uint64_t nanoTimestamp, uint32_t frameCount) {}

void PipelineContext::FlushPipelineWithoutAnimation() {}

void PipelineContext::FlushFocus() {}

void PipelineContext::FlushOnceVsyncTask() {}

void PipelineContext::SetOnWindowFocused(const std::function<void()>& callback) {}

void PipelineContext::DispatchDisplaySync(uint64_t nanoTimestamp) {}

void PipelineContext::FlushAnimation(uint64_t nanoTimestamp) {}

void PipelineContext::FlushRequestFocus() {}

void PipelineContext::CheckNeedUpdateBackgroundColor(Color& color) {}

bool PipelineContext::CheckNeedDisableUpdateBackgroundImage()
{
    return false;
}

void PipelineContext::OnVirtualKeyboardHeightChange(float keyboardHeight,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction, const float safeHeight, const bool supportAvoidance,
    bool forceChange)
{}

void PipelineContext::OnVirtualKeyboardHeightChange(float keyboardHeight, double positionY, double height,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction, bool forceChange)
{}

void PipelineContext::AvoidanceLogic(float keyboardHeight, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction,
    const float safeHeight, const bool supportAvoidance)
{}

void PipelineContext::OriginalAvoidanceLogic(
    float keyboardHeight, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{}

void PipelineContext::OnFoldStatusChange(FoldStatus foldStatus) {}

void PipelineContext::OnFoldDisplayModeChange(FoldDisplayMode foldDisplayMode) {}

void PipelineContext::OnSurfaceChanged(int32_t width, int32_t height, WindowSizeChangeReason type,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{}

void PipelineContext::OnLayoutCompleted(const std::string& componentId) {}

bool PipelineContext::CheckOverlayFocus()
{
    return false;
}

void PipelineContext::OnDrawCompleted(const std::string& componentId) {}

void PipelineContext::SetNeedRenderNode(const WeakPtr<FrameNode>& node) {}

void PipelineContext::OnSurfacePositionChanged(int32_t posX, int32_t posY) {}

void PipelineContext::FlushReload(const ConfigurationChange& configurationChange, bool fullUpdate) {}

void PipelineContext::SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose) {}

void PipelineContext::AddAnimationClosure(std::function<void()>&& animation) {}

void PipelineContext::SetCloseButtonStatus(bool isEnabled) {}

const RefPtr<SelectOverlayManager>& PipelineContext::GetSelectOverlayManager()
{
    return selectOverlayManager_;
}

const RefPtr<DragDropManager>& PipelineContext::GetDragDropManager()
{
    return dragDropManager_;
}

const RefPtr<FocusManager>& PipelineContext::GetFocusManager() const
{
    return focusManager_;
}

const RefPtr<FocusManager>& PipelineContext::GetOrCreateFocusManager()
{
    if (!focusManager_) {
        focusManager_ = MakeRefPtr<FocusManager>(AceType::Claim(this));
    }
    return focusManager_;
}

const RefPtr<StageManager>& PipelineContext::GetStageManager()
{
    return stageManager_;
}

const RefPtr<FullScreenManager>& PipelineContext::GetFullScreenManager()
{
    return fullScreenManager_;
}

const RefPtr<OverlayManager>& PipelineContext::GetOverlayManager()
{
    return overlayManager_;
}

uint32_t PipelineContext::AddScheduleTask(const RefPtr<ScheduleTask>& task)
{
    return 0;
}

void PipelineContext::RemoveScheduleTask(uint32_t id) {}

void PipelineContext::AddOnAreaChangeNode(int32_t nodeId) {}

bool PipelineContext::OnNonPointerEvent(const NonPointerEvent& event)
{
    return false;
}

bool PipelineContext::RequestFocus(const std::string& targetNodeId, bool isSyncRequest)
{
    return false;
}

bool PipelineContext::OnDumpInfo(const std::vector<std::string>& params) const
{
    return false;
}

bool PipelineContext::OnBackPressed()
{
    return false;
}

void PipelineContext::AddDirtyFocus(const RefPtr<FrameNode>& node) {}

void PipelineContext::AddDirtyPropertyNode(const RefPtr<FrameNode>& dirty)
{
    dirtyPropertyNodes_.emplace(dirty);
}

void PipelineContext::AddDirtyRequestFocus(const RefPtr<FrameNode>& node) {}

void PipelineContext::AddDirtyFreezeNode(FrameNode* node) {}

void PipelineContext::AddDirtyLayoutNode(const RefPtr<FrameNode>& dirty)
{
    if (MockPipelineContext::GetCurrent()->UseFlushUITasks()) {
        taskScheduler_->AddDirtyLayoutNode(dirty);
    }
}

void PipelineContext::AddLayoutNode(const RefPtr<FrameNode>& layoutNode) {}

void PipelineContext::AddDirtyRenderNode(const RefPtr<FrameNode>& dirty)
{
    if (MockPipelineContext::GetCurrent()->UseFlushUITasks()) {
        taskScheduler_->AddDirtyRenderNode(dirty);
    }
}

void PipelineContext::AddBuildFinishCallBack(std::function<void()>&& callback)
{
    buildFinishCallbacks_.emplace_back(std::move(callback));
}

void PipelineContext::AddPredictTask(PredictTask&& task)
{
    predictTasks_.emplace_back(task);
}

void PipelineContext::AddAfterLayoutTask(std::function<void()>&& task, bool isFlushInImplicitAnimationTask)
{
    if (MockPipelineContext::GetCurrent()->UseFlushUITasks()) {
        taskScheduler_->AddAfterLayoutTask(std::move(task), isFlushInImplicitAnimationTask);
    } else if (task) {
        task();
    }
}

void PipelineContext::AddSyncGeometryNodeTask(std::function<void()>&& task)
{
    if (task) {
        task();
    }
}

void PipelineContext::StopWindowAnimation() {}

void PipelineContext::FlushSyncGeometryNodeTasks() {}

void PipelineContext::AddAfterRenderTask(std::function<void()>&& task)
{
    if (MockPipelineContext::GetCurrent()->UseFlushUITasks()) {
        taskScheduler_->AddAfterRenderTask(std::move(task));
    } else if (task) {
        task();
    }
}

void PipelineContext::FlushPipelineImmediately() {}

void PipelineContext::RebuildFontNode() {}

FrameInfo* PipelineContext::GetCurrentFrameInfo(uint64_t /* recvTime */, uint64_t /* timeStamp */)
{
    return nullptr;
}

void PipelineContext::DumpPipelineInfo() const {}

void PipelineContext::AddVisibleAreaChangeNode(int32_t nodeId) {}

void PipelineContext::AddVisibleAreaChangeNode(const RefPtr<FrameNode>& node, const std::vector<double>& ratio,
    const VisibleRatioCallback& callback, bool isUserCallback, bool isCalculateInnerClip)
{
    CHECK_NULL_VOID(callback);
    callback(false, 0.0);
    callback(true, ratio[0]);
}

void PipelineContext::RemoveVisibleAreaChangeNode(int32_t nodeId) {}

void PipelineContext::HandleVisibleAreaChangeEvent(uint64_t nanoTimestamp) {}

bool PipelineContext::ChangeMouseStyle(int32_t nodeId, MouseFormat format, int32_t windowId,
    bool isBypass, MouseStyleChangeReason reason)
{
    return true;
}

void PipelineContext::RestoreNodeInfo(std::unique_ptr<JsonValue> nodeInfo) {}

std::unique_ptr<JsonValue> PipelineContext::GetStoredNodeInfo()
{
    return nullptr;
}

void PipelineContext::StoreNode(int32_t restoreId, const WeakPtr<FrameNode>& node) {}

bool PipelineContext::GetRestoreInfo(int32_t restoreId, std::string& restoreInfo)
{
    return false;
}

void PipelineContext::AddDirtyCustomNode(const RefPtr<UINode>& dirtyNode) {}

void PipelineContext::AddWindowSizeChangeCallback(int32_t nodeId) {}

void PipelineContext::RemoveWindowSizeChangeCallback(int32_t nodeId) {}

void PipelineContext::AddNavigationNode(int32_t pageId, WeakPtr<UINode> navigationNode) {}

void PipelineContext::RemoveNavigationNode(int32_t pageId, int32_t nodeId) {}
void PipelineContext::FirePageChanged(int32_t pageId, bool isOnShow) {}
void PipelineContext::UpdateSystemSafeArea(const SafeAreaInsets& systemSafeArea)
{
    safeAreaManager_->UpdateSystemSafeArea(systemSafeArea);
}
void PipelineContext::UpdateCutoutSafeArea(const SafeAreaInsets& cutoutSafeArea)
{
    safeAreaManager_->UpdateCutoutSafeArea(cutoutSafeArea);
}
void PipelineContext::UpdateNavSafeArea(const SafeAreaInsets& navSafeArea) {};
KeyBoardAvoidMode PipelineContext::GetEnableKeyBoardAvoidMode()
{
    return KeyBoardAvoidMode::OFFSET;
}
void PipelineContext::SetEnableKeyBoardAvoidMode(KeyBoardAvoidMode value) {};
bool PipelineContext::UsingCaretAvoidMode()
{
    return false;
}
bool PipelineContext::IsEnableKeyBoardAvoidMode()
{
    return false;
}
void PipelineContext::RequireSummary() {};
void PipelineContext::SetIgnoreViewSafeArea(bool value) {};
void PipelineContext::SetIsLayoutFullScreen(bool value) {};
void PipelineContext::SetIsNeedAvoidWindow(bool value) {};

SafeAreaInsets PipelineContext::GetSafeArea() const
{
    // top inset = 1
    return SafeAreaInsets({}, { 0, 1 }, {}, {});
}

SafeAreaInsets PipelineContext::GetSafeAreaWithoutProcess() const
{
    return SafeAreaInsets({}, { 0, 1 }, {}, {});
}

float PipelineContext::GetPageAvoidOffset()
{
    return 0.0f;
}

bool PipelineContext::CheckNeedAvoidInSubWindow()
{
    return false;
}

std::string PipelineContext::GetResponseRegion(const RefPtr<NG::FrameNode>& rootNode)
{
    return "";
}

void PipelineContext::NotifyResponseRegionChanged(const RefPtr<NG::FrameNode>& rootNode) {};

void PipelineContext::AddFontNodeNG(const WeakPtr<UINode>& node) {}

void PipelineContext::RemoveFontNodeNG(const WeakPtr<UINode>& node) {}

void PipelineContext::SetWindowSceneConsumed(bool isConsumed) {}

void PipelineContext::AddIsFocusActiveUpdateEvent(
    const RefPtr<FrameNode>& node, const std::function<void(bool)>& eventCallback)
{}

void PipelineContext::RemoveIsFocusActiveUpdateEvent(const RefPtr<FrameNode>& node) {}

bool PipelineContext::HasDifferentDirectionGesture() const
{
    return false;
}

void PipelineContext::SetJSViewActive(bool active, WeakPtr<CustomNode> custom) {}

RefPtr<FrameNode> PipelineContext::FindNavigationNodeToHandleBack(const RefPtr<UINode>& node, bool& isEntry)
{
    return nullptr;
}

bool PipelineContext::SetIsFocusActive(bool isFocusActive, FocusActiveReason reason, bool autoFocusInactive)
{
    return false;
}

bool PipelineContext::NeedSoftKeyboard()
{
    return false;
}

void PipelineContext::SetCursor(int32_t cursorValue) {}

void PipelineContext::RestoreDefault(int32_t windowId) {}

void PipelineContext::HandleSubwindow(bool isShow) {}

std::string PipelineContext::GetCurrentExtraInfo()
{
    return std::string();
}

void PipelineContext::CloseFrontendAnimation() {}

void PipelineContext::OpenFrontendAnimation(
    const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& finishCallback)
{}

bool PipelineContext::IsDragging() const
{
    return false;
}

void PipelineContext::SetIsDragging(bool isDragging) {}

void PipelineContext::ResetDragging() {}

void PipelineContext::UpdateOriginAvoidArea(const Rosen::AvoidArea& avoidArea, uint32_t type) {}

void PipelineContext::CheckAndUpdateKeyboardInset(float keyboardHeight) {}

bool PipelineContext::PrintVsyncInfoIfNeed() const
{
    return false;
}

const SerializedGesture& PipelineContext::GetSerializedGesture() const
{
    return serializedGesture_;
}

void PipelineContext::FlushFocusView()
{
    CHECK_NULL_VOID(focusManager_);
    auto lastFocusView = (focusManager_->GetLastFocusView()).Upgrade();
    CHECK_NULL_VOID(lastFocusView);
    auto lastFocusViewHub = lastFocusView->GetFocusHub();
    CHECK_NULL_VOID(lastFocusViewHub);
    if (lastFocusView && (!lastFocusViewHub->IsCurrentFocus() || !lastFocusView->GetIsViewHasFocused()) &&
        lastFocusViewHub->IsFocusableNode()) {
        lastFocusView->RequestDefaultFocus();
    }
}

void PipelineContext::SetOverlayNodePositions(std::vector<Ace::RectF> rects) {}

std::vector<Ace::RectF> PipelineContext::GetOverlayNodePositions()
{
    return {};
}

void PipelineContext::RegisterOverlayNodePositionsUpdateCallback(
    const std::function<void(std::vector<Ace::RectF>)>&& callback)
{}

void PipelineContext::TriggerOverlayNodePositionsUpdateCallback(std::vector<Ace::RectF> rects) {}

bool PipelineContext::IsContainerModalVisible()
{
    return false;
}

void PipelineContext::CheckAndLogLastReceivedTouchEventInfo(int32_t eventId, TouchType type) {}

void PipelineContext::CheckAndLogLastConsumedTouchEventInfo(int32_t eventId, TouchType type) {}

void PipelineContext::CheckAndLogLastReceivedMouseEventInfo(int32_t eventId, MouseAction action) {}

void PipelineContext::CheckAndLogLastConsumedMouseEventInfo(int32_t eventId, MouseAction action) {}

void PipelineContext::CheckAndLogLastReceivedAxisEventInfo(int32_t eventId, AxisAction action) {}

void PipelineContext::CheckAndLogLastConsumedAxisEventInfo(int32_t eventId, AxisAction action) {}

void PipelineContext::PreLayout(uint64_t nanoTimestamp, uint32_t frameCount) {}

void PipelineContext::AddFrameNodeChangeListener(const WeakPtr<FrameNode>& node) {}

void PipelineContext::RemoveFrameNodeChangeListener(int32_t nodeId) {}

bool PipelineContext::AddChangedFrameNode(const WeakPtr<FrameNode>& node)
{
    return true;
}

void PipelineContext::RemoveChangedFrameNode(int32_t nodeId) {}

void PipelineContext::FlushNodeChangeFlag() {}

void PipelineContext::CleanNodeChangeFlag() {}

bool PipelineContext::HasOnAreaChangeNode(int32_t nodeId)
{
    return false;
}

void PipelineContext::UnregisterTouchEventListener(const WeakPtr<NG::Pattern>& pattern) {}

int32_t PipelineContext::GetContainerModalTitleHeight()
{
    return 0;
}

bool PipelineContext::GetContainerModalButtonsRect(RectF& containerModal, RectF& buttons)
{
    return true;
}
} // namespace OHOS::Ace::NG
// pipeline_context ============================================================

// pipeline_base ===============================================================
namespace OHOS::Ace {
class ManagerInterface : public AceType {
    DECLARE_ACE_TYPE(ManagerInterface, AceType);
};

void PipelineBase::OpenImplicitAnimation(
    const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& finishCallBack)
{}

bool PipelineBase::CloseImplicitAnimation()
{
    return true;
}

bool PipelineBase::IsDestroyed()
{
    return false;
}

void PipelineBase::SetDestroyed() {}

RefPtr<Frontend> PipelineBase::GetFrontend() const
{
    return nullptr;
}

void PipelineBase::SetTouchPipeline(const WeakPtr<PipelineBase>& context) {}

RefPtr<ImageCache> PipelineBase::GetImageCache() const
{
    return nullptr;
}

void PipelineBase::OnVirtualKeyboardAreaChange(Rect keyboardArea,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction, const float safeHeight, const bool supportAvoidance,
    bool forceChange)
{}
void PipelineBase::OnVirtualKeyboardAreaChange(Rect keyboardArea, double positionY, double height,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction, bool forceChange)
{}

void PipelineBase::OnVsyncEvent(uint64_t nanoTimestamp, uint32_t frameCount) {}

void PipelineBase::SendEventToAccessibility(const AccessibilityEvent& accessibilityEvent) {}

void PipelineBase::OnActionEvent(const std::string& action) {}

void PipelineBase::SetRootSize(double density, float width, float height) {}

RefPtr<PipelineBase> PipelineBase::GetCurrentContext()
{
    return NG::MockPipelineContext::GetCurrent();
}

RefPtr<PipelineBase> PipelineBase::GetCurrentContextSafely()
{
    return NG::MockPipelineContext::GetCurrent();
}

RefPtr<PipelineBase> PipelineBase::GetCurrentContextSafelyWithCheck()
{
    return NG::MockPipelineContext::GetCurrent();
}

double PipelineBase::GetCurrentDensity()
{
    auto pipelineContext = NG::MockPipelineContext::GetCurrentContext();
    return pipelineContext ? pipelineContext->GetDensity() : 1.0;
}

double PipelineBase::Px2VpWithCurrentDensity(double px)
{
    double density = GetCurrentDensity();
    return px / density;
}

double PipelineBase::Vp2PxWithCurrentDensity(double vp)
{
    double density = GetCurrentDensity();
    return vp * density;
}

double PipelineBase::NormalizeToPx(const Dimension& dimension) const
{
    if ((dimension.Unit() == DimensionUnit::VP) || (dimension.Unit() == DimensionUnit::FP)) {
        return (dimension.Value() * dipScale_);
    }
    if (dimension.Unit() == DimensionUnit::LPX) {
        return (dimension.Value() * designWidthScale_);
    }
    return dimension.Value();
}

PipelineBase::~PipelineBase() = default;

uint64_t PipelineBase::GetTimeFromExternalTimer()
{
    return 1;
}

void PipelineBase::PostAsyncEvent(TaskExecutor::Task&& task, const std::string& name, TaskExecutor::TaskType type)
{
    if (taskExecutor_) {
        taskExecutor_->PostTask(std::move(task), type, name);
    }
}

void PipelineBase::PostAsyncEvent(const TaskExecutor::Task& task, const std::string& name, TaskExecutor::TaskType type)
{}

void PipelineBase::PostSyncEvent(const TaskExecutor::Task& task, const std::string& name, TaskExecutor::TaskType type)
{}

RefPtr<AccessibilityManager> PipelineBase::GetAccessibilityManager() const
{
    return AceType::MakeRefPtr<MockAccessibilityManager>();
}

#ifdef WINDOW_SCENE_SUPPORTED
const RefPtr<UIExtensionManager>& GetUIExtensionManager()
{
    return AceType::MakeRefPtr<UIExtensionManager>();
}
#endif

bool PipelineBase::Animate(const AnimationOption& option, const RefPtr<Curve>& curve,
    const std::function<void()>& propertyCallback, const std::function<void()>& finishCallback)
{
    return true;
}

void PipelineBase::Destroy() {}
bool PipelineBase::MaybeRelease()
{
    return AceType::MaybeRelease();
}

double PipelineBase::ConvertPxToVp(const Dimension& dimension) const
{
    if (dimension.Unit() == DimensionUnit::PX) {
        return dimension.Value() / dipScale_;
    }
    return dimension.Value();
}

void PipelineBase::HyperlinkStartAbility(const std::string& address) const {}

void PipelineBase::StartAbilityOnQuery(const std::string& queryWord) const {}

void PipelineBase::RequestFrame() {}

Rect PipelineBase::GetCurrentWindowRect() const
{
    return NG::windowRect_;
}

void PipelineBase::SetTextFieldManager(const RefPtr<ManagerInterface>& manager)
{
    textFieldManager_ = manager;
}

bool PipelineBase::HasFloatTitle() const
{
    return true;
}

void PipelineBase::AddUIExtensionCallbackEvent(NG::UIExtCallbackEventId eventId)
{
    uiExtensionEvents_.insert(NG::UIExtCallbackEvent(eventId));
}

Dimension NG::PipelineContext::GetCustomTitleHeight()
{
    return Dimension();
}

void PipelineBase::SetFontScale(float fontScale)
{
    fontScale_ = fontScale;
}

bool NG::PipelineContext::CatchInteractiveAnimations(const std::function<void()>& animationCallback)
{
    return false;
}

void PipelineBase::SetUiDvsyncSwitch(bool on) {}

bool NG::PipelineContext::CheckThreadSafe()
{
    return false;
}

#ifdef NEED_PIPELINE_CONTEXT_BE_NULLPTR
PipelineContext* TextPattern::GetContext()
{
    return nullptr;
}
#endif

void NG::PipelineContext::FlushUITaskWithSingleDirtyNode(const RefPtr<NG::FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto layoutProperty = node->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutConstraint = node->GetLayoutConstraint();
    if (layoutProperty->GetLayoutRect()) {
        node->SetActive(true, true);
        node->Measure(std::nullopt);
        node->Layout();
    } else {
        auto ancestorNodeOfFrame = node->GetAncestorNodeOfFrame();
        node->Measure(layoutConstraint);
        node->Layout();
    }
}

void SetBoolStatus(bool value)
{
    g_setBoolStatus = value;
}

void NG::PipelineContext::DumpUIExt() const {}

void NG::PipelineContext::RegisterAttachedNode(UINode* uiNode) {}

void NG::PipelineContext::RemoveAttachedNode(UINode* uiNode) {}

void NG::PipelineContext::EnableContainerModalGesture(bool isEnable) {}

bool NG::PipelineContext::GetContainerFloatingTitleVisible()
{
    return false;
}

bool NG::PipelineContext::GetContainerCustomTitleVisible()
{
    return false;
}

bool NG::PipelineContext::GetContainerControlButtonVisible()
{
    return false;
}

void NG::PipelineContext::SetEnableSwipeBack(bool isEnable) {}

NG::ScopedLayout::ScopedLayout(PipelineContext* pipeline) {}
NG::ScopedLayout::~ScopedLayout() {}
} // namespace OHOS::Ace
// pipeline_base ===============================================================
