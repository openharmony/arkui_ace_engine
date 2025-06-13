/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "core/pipeline_ng/pipeline_context.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/event/event_constants.h"
#include "core/event/key_event.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/transaction/rs_transaction.h"
#include "render_service_client/core/ui/rs_ui_director.h"
#include "render_service_client/core/ui/rs_ui_context.h"
#include "render_service_client/core/ui/rs_surface_node.h"
#endif
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "frameworks/core/components_ng/base/inspector.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/log/ace_performance_monitor.h"
#include "base/log/ace_trace.h"
#include "base/log/ace_tracker.h"
#include "base/log/dump_log.h"
#include "base/log/dump_recorder.h"
#include "base/log/event_report.h"
#include "base/memory/ace_type.h"
#include "base/mousestyle/mouse_style.h"
#include "base/perfmonitor/perf_monitor.h"
#include "base/ressched/ressched_report.h"
#include "base/thread/background_task_executor.h"
#include "core/common/ace_engine.h"
#include "core/common/font_manager.h"
#include "core/common/font_change_observer.h"
#include "core/common/ime/input_method_manager.h"
#include "core/common/layout_inspector.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/stylus/stylus_detector_default.h"
#include "core/common/stylus/stylus_detector_mgr.h"
#include "core/common/text_field_manager.h"
#include "core/components_ng/base/node_render_status_monitor.h"
#include "core/components_ng/base/view_advanced_register.h"
#include "core/components_ng/pattern/container_modal/container_modal_view_factory.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/window_scene/scene/window_scene_layout_manager.h"
#endif
#include "core/image/image_file_cache.h"
#include "core/pipeline/pipeline_context.h"
#ifdef COMPONENT_TEST_ENABLED
#include "component_test/pipeline_status.h"
#endif // COMPONENT_TEST_ENABLED
#include "interfaces/inner_api/ace_kit/src/view/ui_context_impl.h"

namespace {
constexpr uint64_t ONE_MS_IN_NS = 1 * 1000 * 1000;
constexpr int32_t TIME_THRESHOLD = 2 * 1000000; // 3 millisecond
constexpr int32_t PLATFORM_VERSION_TEN = 10;
constexpr int32_t MILLISECONDS_TO_NANOSECONDS = 1000000; // Milliseconds to nanoseconds
constexpr int32_t VSYNC_PERIOD_COUNT = 5;
constexpr int32_t MIN_IDLE_TIME = 1000;
constexpr uint8_t SINGLECOLOR_UPDATE_ALPHA = 75;
constexpr int8_t RENDERING_SINGLE_COLOR = 1;
constexpr int32_t DELAY_TIME = 500;
constexpr int32_t PARAM_NUM = 2;
constexpr int32_t MAX_MISS_COUNT = 3;
constexpr int32_t MAX_FLUSH_COUNT = 2;
constexpr int32_t MAX_RECORD_SECOND = 15;
constexpr int32_t DEFAULT_RECORD_SECOND = 5;
constexpr int32_t SECOND_TO_MILLISEC = 1000;
constexpr int32_t USED_ID_FIND_FLAG = 3;
constexpr int32_t USED_JSON_PARAM = 4;
constexpr int32_t MAX_FRAME_COUNT_WITHOUT_JS_UNREGISTRATION = 100;
constexpr int32_t  RATIO_OF_VSYNC_PERIOD = 2;
constexpr char PID_FLAG[] = "pidflag";
} // namespace

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension CARET_AVOID_OFFSET = 24.0_vp;

void ShouldAddToHistory (
    std::vector<TouchEvent>& history, const TouchEvent& event, const TouchEvent& movePoint)
{
#ifdef ARKUI_WEARABLE
    if (event.x != movePoint.x || event.y != movePoint.y) {
        history.emplace_back(movePoint);
    }
#else
    history.emplace_back(movePoint);
#endif
}

int32_t GetDepthFromParams(const std::vector<std::string>& params)
{
    int32_t depth = 0;
    std::string prefix = "dcDepth_";
    for (const auto& param : params) {
        if (param.find(prefix) == 0) {
            std::string suffix = param.substr(prefix.length());
            int32_t suffixInt = StringUtils::StringToInt(suffix);
            if (suffixInt != 0) {
                depth = suffixInt;
                break;
            }
        }
    }

    return depth;
}
} // namespace

PipelineContext::PipelineContext(std::shared_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
    RefPtr<AssetManager> assetManager, RefPtr<PlatformResRegister> platformResRegister,
    const RefPtr<Frontend>& frontend, int32_t instanceId)
    : PipelineBase(window, std::move(taskExecutor), std::move(assetManager), frontend, instanceId, platformResRegister)
{
    window_->OnHide();
    if (navigationMgr_) {
        navigationMgr_->SetPipelineContext(WeakClaim(this));
    }
    if (avoidInfoMgr_) {
        avoidInfoMgr_->SetPipelineContext(WeakClaim(this));
        avoidInfoMgr_->SetInstanceId(instanceId);
    }
#ifdef WINDOW_SCENE_SUPPORTED
    if (uiExtensionManager_) {
        uiExtensionManager_->SetPipelineContext(WeakClaim(this));
        uiExtensionManager_->SetInstanceId(instanceId);
    }
#endif
}

PipelineContext::PipelineContext(std::shared_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
    RefPtr<AssetManager> assetManager, const RefPtr<Frontend>& frontend, int32_t instanceId)
    : PipelineBase(window, std::move(taskExecutor), std::move(assetManager), frontend, instanceId)
{
    window_->OnHide();
    if (navigationMgr_) {
        navigationMgr_->SetPipelineContext(WeakClaim(this));
    }
    if (avoidInfoMgr_) {
        avoidInfoMgr_->SetPipelineContext(WeakClaim(this));
        avoidInfoMgr_->SetInstanceId(instanceId);
    }
#ifdef WINDOW_SCENE_SUPPORTED
    if (uiExtensionManager_) {
        uiExtensionManager_->SetPipelineContext(WeakClaim(this));
        uiExtensionManager_->SetInstanceId(instanceId);
    }
#endif
}

PipelineContext::PipelineContext()
{
    if (navigationMgr_) {
        navigationMgr_->SetPipelineContext(WeakClaim(this));
    }
    if (avoidInfoMgr_) {
        avoidInfoMgr_->SetPipelineContext(WeakClaim(this));
    }
#ifdef WINDOW_SCENE_SUPPORTED
    if (uiExtensionManager_) {
        uiExtensionManager_->SetPipelineContext(WeakClaim(this));
    }
#endif
}

std::string PipelineContext::GetCurrentPageNameCallback()
{
    CHECK_NULL_RETURN(stageManager_, "");
    RefPtr<FrameNode> pageNode = stageManager_->GetLastPage();
    CHECK_NULL_RETURN(pageNode, "");
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, "");
    CHECK_NULL_RETURN(pagePattern->GetPageInfo(), "");
    int32_t pageId = pagePattern->GetPageInfo()->GetPageId();
    RefPtr<NavigationGroupNode> navigationNode = nullptr;
    CHECK_RUN_ON(UI);
    auto it = pageToNavigationNodes_.find(pageId);
    if (it == pageToNavigationNodes_.end() || it->second.empty()) {
        return "";
    }

    for (auto iter = it->second.begin(); iter != it->second.end() && !navigationNode; ++iter) {
        navigationNode = AceType::DynamicCast<NavigationGroupNode>((*iter).Upgrade());
    }

    CHECK_NULL_RETURN(navigationNode, "");
    CHECK_NULL_RETURN(navigationNode->GetPattern(), "");
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    CHECK_NULL_RETURN(pattern, "");
    const auto& navDestinationNodes = pattern->GetAllNavDestinationNodes();
    int32_t size = static_cast<int32_t>(navDestinationNodes.size());
    if (size == 0) {
        return "";
    }
    auto pageNameObj = navDestinationNodes.back();
    std::string pageName = std::get<0>(pageNameObj);
    return pageName;
}

RefPtr<PipelineContext> PipelineContext::GetCurrentContext()
{
    auto currentContainer = Container::Current();
    CHECK_NULL_RETURN(currentContainer, nullptr);
    return DynamicCast<PipelineContext>(currentContainer->GetPipelineContext());
}

RefPtr<PipelineContext> PipelineContext::GetCurrentContextSafely()
{
    auto currentContainer = Container::CurrentSafely();
    CHECK_NULL_RETURN(currentContainer, nullptr);
    return DynamicCast<PipelineContext>(currentContainer->GetPipelineContext());
}

RefPtr<PipelineContext> PipelineContext::GetCurrentContextSafelyWithCheck()
{
    auto currentContainer = Container::CurrentSafelyWithCheck();
    CHECK_NULL_RETURN(currentContainer, nullptr);
    return DynamicCast<PipelineContext>(currentContainer->GetPipelineContext());
}

PipelineContext* PipelineContext::GetCurrentContextPtrSafely()
{
    auto currentContainer = Container::CurrentSafely();
    CHECK_NULL_RETURN(currentContainer, nullptr);
    const auto& base = currentContainer->GetPipelineContext();
    CHECK_NULL_RETURN(base, nullptr);
    return DynamicCast<PipelineContext>(RawPtr(base));
}

PipelineContext* PipelineContext::GetCurrentContextPtrSafelyWithCheck()
{
    auto currentContainer = Container::CurrentSafelyWithCheck();
    CHECK_NULL_RETURN(currentContainer, nullptr);
    const auto& base = currentContainer->GetPipelineContext();
    CHECK_NULL_RETURN(base, nullptr);
    return DynamicCast<PipelineContext>(RawPtr(base));
}

RefPtr<PipelineContext> PipelineContext::GetMainPipelineContext()
{
    auto pipeline = PipelineBase::GetMainPipelineContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    return DynamicCast<PipelineContext>(pipeline);
}

bool PipelineContext::NeedSoftKeyboard()
{
    auto needSoftKeyboard = InputMethodManager::GetInstance()->NeedSoftKeyboard();
    TAG_LOGI(AceLogTag::ACE_KEYBOARD, "window switch need keyboard %d", needSoftKeyboard);
    return needSoftKeyboard;
}

RefPtr<PipelineContext> PipelineContext::GetContextByContainerId(int32_t containerId)
{
    auto preContainer = Container::GetContainer(containerId);
    CHECK_NULL_RETURN(preContainer, nullptr);
    return DynamicCast<PipelineContext>(preContainer->GetPipelineContext());
}

float PipelineContext::GetCurrentRootWidth()
{
    auto context = GetCurrentContext();
    CHECK_NULL_RETURN(context, 0.0f);
    return static_cast<float>(context->rootWidth_);
}

float PipelineContext::GetCurrentRootHeight()
{
    auto context = GetCurrentContext();
    CHECK_NULL_RETURN(context, 0.0f);
    return static_cast<float>(context->rootHeight_);
}

void PipelineContext::AddDirtyPropertyNode(const RefPtr<FrameNode>& dirtyNode)
{
    if (!CheckThreadSafe()) {
        LOGW("AddDirtyPropertyNode doesn't run on UI thread!");
    }
    dirtyPropertyNodes_.emplace(dirtyNode);
    hasIdleTasks_ = true;
    RequestFrame();
}

void PipelineContext::AddDirtyCustomNode(const RefPtr<UINode>& dirtyNode)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(dirtyNode);
    auto customNode = DynamicCast<CustomNode>(dirtyNode);
    if (customNode && !dirtyNode->GetInspectorIdValue("").empty()) {
        ACE_BUILD_TRACE_BEGIN("AddDirtyCustomNode[%s][self:%d][parent:%d][key:%s]",
            customNode->GetJSViewName().c_str(),
            dirtyNode->GetId(), dirtyNode->GetParent() ? dirtyNode->GetParent()->GetId() : 0,
            dirtyNode->GetInspectorIdValue("").c_str());
        ACE_BUILD_TRACE_END()
    } else if (customNode) {
        ACE_BUILD_TRACE_BEGIN("AddDirtyCustomNode[%s][self:%d][parent:%d]",
            customNode->GetJSViewName().c_str(),
            dirtyNode->GetId(), dirtyNode->GetParent() ? dirtyNode->GetParent()->GetId() : 0);
        ACE_BUILD_TRACE_END()
    }
    dirtyNodes_.emplace(dirtyNode);
    hasIdleTasks_ = true;
    RequestFrame();
}

void PipelineContext::AddDirtyLayoutNode(const RefPtr<FrameNode>& dirty)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(dirty);
    if (IsDestroyed()) {
        LOGW("Cannot add dirty layout node as the pipeline context is destroyed.");
        return;
    }
    if (!dirty->GetInspectorIdValue("").empty()) {
        ACE_BUILD_TRACE_BEGIN("AddDirtyLayoutNode[%s][self:%d][parent:%d][key:%s]",
            dirty->GetTag().c_str(),
            dirty->GetId(), dirty->GetParent() ? dirty->GetParent()->GetId() : 0,
            dirty->GetInspectorIdValue("").c_str());
        ACE_BUILD_TRACE_END()
    } else {
        ACE_BUILD_TRACE_BEGIN("AddDirtyLayoutNode[%s][self:%d][parent:%d]", dirty->GetTag().c_str(),
            dirty->GetId(), dirty->GetParent() ? dirty->GetParent()->GetId() : 0);
        ACE_BUILD_TRACE_END()
    }
    if (!dirty->IsOnMainTree() && predictNode_) {
        predictNode_->AddPredictLayoutNode(dirty);
        return;
    }
    taskScheduler_->AddDirtyLayoutNode(dirty);
    ForceLayoutForImplicitAnimation();
#ifdef UICAST_COMPONENT_SUPPORTED
    do {
        auto container = Container::Current();
        CHECK_NULL_BREAK(container);
        auto distributedUI = container->GetDistributedUI();
        CHECK_NULL_BREAK(distributedUI);
        distributedUI->AddDirtyLayoutNode(dirty->GetId());
    } while (false);
#endif
    hasIdleTasks_ = true;
    if (dirty->GetTag() == V2::ROOT_ETS_TAG && isFirstRootLayout_) {
        isFirstRootLayout_ = false;
        LOGI("Root node request first frame.");
    }
    RequestFrame();
}

void PipelineContext::AddIgnoreLayoutSafeAreaBundle(IgnoreLayoutSafeAreaBundle&& bundle)
{
    CHECK_RUN_ON(UI);
    if (IsDestroyed()) {
        LOGW("Cannot add ignoreSafeArea bundle as the pipeline context is destroyed.");
        return;
    }
    taskScheduler_->AddIgnoreLayoutSafeAreaBundle(std::move(bundle));
}

void PipelineContext::AddLayoutNode(const RefPtr<FrameNode>& layoutNode)
{
    taskScheduler_->AddLayoutNode(layoutNode);
}

void PipelineContext::AddDirtyRenderNode(const RefPtr<FrameNode>& dirty)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(dirty);
    if (IsDestroyed()) {
        LOGW("Cannot add dirty render node as the pipeline context is destroyed.");
        return;
    }
    if (!dirty->GetInspectorIdValue("").empty()) {
        ACE_BUILD_TRACE_BEGIN("AddDirtyRenderNode[%s][self:%d][parent:%d][key:%s]", dirty->GetTag().c_str(),
            dirty->GetId(), dirty->GetParent() ? dirty->GetParent()->GetId() : 0,
            dirty->GetInspectorIdValue("").c_str());
        ACE_BUILD_TRACE_END()
    } else {
        ACE_BUILD_TRACE_BEGIN("AddDirtyRenderNode[%s][self:%d][parent:%d]", dirty->GetTag().c_str(),
            dirty->GetId(), dirty->GetParent() ? dirty->GetParent()->GetId() : 0);
        ACE_BUILD_TRACE_END()
    }
    taskScheduler_->AddDirtyRenderNode(dirty);
    ForceRenderForImplicitAnimation();
#ifdef UICAST_COMPONENT_SUPPORTED
    do {
        auto container = Container::Current();
        CHECK_NULL_BREAK(container);
        auto distributedUI = container->GetDistributedUI();
        CHECK_NULL_BREAK(distributedUI);
        distributedUI->AddDirtyRenderNode(dirty->GetId());
    } while (false);
#endif
    hasIdleTasks_ = true;
    RequestFrame();
}

void PipelineContext::AddDirtyFreezeNode(FrameNode* node)
{
    dirtyFreezeNode_.emplace_back(WeakClaim(node));
    hasIdleTasks_ = true;
    RequestFrame();
}

void PipelineContext::FlushFreezeNode()
{
    std::set<RefPtr<FrameNode>, NodeCompare<RefPtr<FrameNode>>> dirtyFreezeNodeSet;
    auto dirtyFreezeNodes = std::move(dirtyFreezeNode_);
    dirtyFreezeNode_.clear();
    for (auto&& weakNode : dirtyFreezeNodes) {
        auto node = weakNode.Upgrade();
        if (node) {
            dirtyFreezeNodeSet.emplace(node);
        }
    }
    //Process parentNode before childNode
    for (auto&& node : dirtyFreezeNodeSet) {
        node->ProcessFreezeNode();
    }
}

void PipelineContext::AddPendingDeleteCustomNode(const RefPtr<CustomNode>& node)
{
    pendingDeleteCustomNode_.push(node);
    RequestFrame();
}

void PipelineContext::FlushPendingDeleteCustomNode()
{
    auto pendingStack = std::move(pendingDeleteCustomNode_);
    while (!pendingStack.empty()) {
        auto node = pendingStack.top();
        pendingStack.pop();
        if (AceType::InstanceOf<NG::CustomNode>(node)) {
            auto customNode = AceType::DynamicCast<NG::CustomNode>(node);
            if (!customNode->CheckFireOnAppear()) {
                customNode->FireOnAppear();
                customNode->FireDidBuild();
            }
            customNode->FireOnDisappear();
            customNode->Reset();
        }
    }
}

void PipelineContext::FlushDirtyPropertyNodes()
{
    // node api property diff before ets update.
    if (!CheckThreadSafe()) {
        LOGW("FlushDirtyNodeUpdate doesn't run on UI thread!");
    }
    decltype(dirtyPropertyNodes_) dirtyPropertyNodes(std::move(dirtyPropertyNodes_));
    dirtyPropertyNodes_.clear();
    for (const auto& node : dirtyPropertyNodes) {
        node->ProcessPropertyDiff();
    }
}

void PipelineContext::FlushDirtyNodeUpdate()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();
    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().BeginFlushBuild();
    }

    // freeze node unlock before build begin.
    FlushFreezeNode();

    FlushDirtyPropertyNodes();

    FlushPendingDeleteCustomNode();

    if (!ViewStackProcessor::GetInstance()->IsEmpty() && !dirtyNodes_.empty()) {
        ACE_SCOPED_TRACE("Error update, node stack non-empty");
        LOGW("stack is not empty when call FlushDirtyNodeUpdate, node may be mounted to incorrect pos!");
    }
    // SomeTimes, customNode->Update may add some dirty custom nodes to dirtyNodes_,
    // use maxFlushTimes to avoid dead cycle.
    int maxFlushTimes = 3;
    while (!dirtyNodes_.empty() && maxFlushTimes > 0) {
        auto id = GetInstanceId();
        ArkUIPerfMonitor::GetPerfMonitor(id)->RecordStateMgmtNode(dirtyNodes_.size());
        decltype(dirtyNodes_) dirtyNodes(std::move(dirtyNodes_));
        for (const auto& node : dirtyNodes) {
            if (AceType::InstanceOf<NG::CustomNodeBase>(node)) {
                auto customNode = AceType::DynamicCast<NG::CustomNodeBase>(node);
                ACE_SCOPED_TRACE("CustomNodeUpdate name:%s,id:%d", customNode->GetJSViewName().c_str(), node->GetId());
                customNode->Update();
            }
        }
        --maxFlushTimes;
    }

    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().EndFlushBuild();
    }
}

uint32_t PipelineContext::AddScheduleTask(const RefPtr<ScheduleTask>& task)
{
    CHECK_RUN_ON(UI);
    scheduleTasks_.try_emplace(++nextScheduleTaskId_, task);
    RequestFrame();
    return nextScheduleTaskId_;
}

void PipelineContext::RemoveScheduleTask(uint32_t id)
{
    CHECK_RUN_ON(UI);
    scheduleTasks_.erase(id);
}

void PipelineContext::FlushOnceVsyncTask()
{
    if (onceVsyncListener_ != nullptr) {
        onceVsyncListener_();
        onceVsyncListener_ = nullptr;
    }
}

void PipelineContext::FlushDragEvents()
{
    auto manager = GetDragDropManager();
    if (!manager) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "GetDragDrapManager error, manager is nullptr");
        dragEvents_.clear();
        return;
    }
    if (!manager->IsDragFwkShow()) {
        manager->DoDragMoveAnimate(manager->GetDragAnimationPointerEvent());
    }
    std::string extraInfo = manager->GetExtraInfo();
    std::unordered_set<int32_t> moveEventIds;
    decltype(dragEvents_) dragEvents(std::move(dragEvents_));
    if (dragEvents.empty()) {
        canUseLongPredictTask_ = true;
        nodeToPointEvent_.clear();
        return ;
    }
    canUseLongPredictTask_ = false;
    for (auto iter = dragEvents.begin(); iter != dragEvents.end(); ++iter) {
        FlushDragEvents(manager, extraInfo, iter->first, iter->second);
    }
}

void PipelineContext::FlushDragEvents(const RefPtr<DragDropManager>& manager,
    std::string extraInfo,
    const RefPtr<FrameNode>& node,
    const std::list<DragPointerEvent>& pointEvent)
{
    std::unordered_map<int, DragPointerEvent> idToPoints;
    bool needInterpolation = true;
    std::unordered_map<int32_t, DragPointerEvent> newIdPoints;
    for (auto iter = pointEvent.rbegin(); iter != pointEvent.rend(); ++iter) {
        idToPoints.emplace(iter->pointerId, *iter);
        idToPoints[iter->pointerId].history.insert(idToPoints[iter->pointerId].history.begin(), *iter);
        needInterpolation = iter->action != PointerAction::PULL_MOVE ? false : true;
    }
    if (!NeedTouchInterpolation()) {
        needInterpolation = false;
    }
    if (needInterpolation) {
        auto targetTimeStamp = resampleTimeStamp_;
        for (const auto &idIter : idToPoints) {
            auto stamp =
                std::chrono::duration_cast<std::chrono::nanoseconds>(idIter.second.time.time_since_epoch()).count();
            if (targetTimeStamp > static_cast<uint64_t>(stamp)) {
                LOGI("Skip interpolation when there is no touch event after interpolation time point. "
                        "(last stamp:%{public}" PRIu64 ", target stamp:%{public}" PRIu64 ")",
                    static_cast<uint64_t>(stamp), targetTimeStamp);
                continue;
            }
            DragPointerEvent newPointerEvent = eventManager_->GetResamplePointerEvent(
                historyPointsEventById_[idIter.first], idIter.second.history, targetTimeStamp);
            if (newPointerEvent.x != 0 && newPointerEvent.y != 0) {
                newIdPoints[idIter.first] = newPointerEvent;
            }
            historyPointsEventById_[idIter.first] = idIter.second.history;
        }
    }
    FlushDragEvents(manager, newIdPoints, extraInfo, idToPoints, node);
}

void PipelineContext::FlushDragEvents(const RefPtr<DragDropManager>& manager,
    std::unordered_map<int32_t, DragPointerEvent> newIdPoints,
    std::string& extraInfo,
    std::unordered_map<int, DragPointerEvent> &idToPoints,
    const RefPtr<FrameNode>& node)
{
    std::map<WeakPtr<FrameNode>, std::vector<DragPointerEvent>> nodeToPointEvent;
    std::list<DragPointerEvent> dragPoint;
    for (const auto& iter : idToPoints) {
        auto lastDispatchTime = eventManager_->GetLastDispatchTime();
        lastDispatchTime[iter.first] = GetVsyncTime();
        eventManager_->SetLastDispatchTime(std::move(lastDispatchTime));
        auto it = newIdPoints.find(iter.first);
        if (it != newIdPoints.end()) {
            dragPoint.emplace_back(it->second);
            nodeToPointEvent[node].emplace_back(it->second);
        } else {
            dragPoint.emplace_back(iter.second);
            nodeToPointEvent[node].emplace_back(iter.second);
        }
    }
    for (auto iter = dragPoint.rbegin(); iter != dragPoint.rend(); ++iter) {
        manager->OnDragMove(*iter, extraInfo, node);
    }
    nodeToPointEvent_ = std::move(nodeToPointEvent);
}

void PipelineContext::FlushVsync(uint64_t nanoTimestamp, uint32_t frameCount)
{
    CHECK_RUN_ON(UI);
    if (IsDestroyed()) {
        LOGW("Cannot flush vsync as the pipeline context is destroyed.");
        return;
    }
    SetVsyncTime(nanoTimestamp);
    ACE_SCOPED_TRACE_COMMERCIAL("UIVsyncTask[timestamp:%" PRIu64 "][vsyncID:%" PRIu64 "][instanceID:%d]",
        nanoTimestamp, static_cast<uint64_t>(frameCount), instanceId_);
    window_->Lock();
    static const std::string abilityName = AceApplicationInfo::GetInstance().GetProcessName().empty()
                                               ? AceApplicationInfo::GetInstance().GetPackageName()
                                               : AceApplicationInfo::GetInstance().GetProcessName();
    window_->RecordFrameTime(nanoTimestamp, abilityName);
    uint64_t vsyncPeriod = static_cast<uint64_t>(window_->GetVSyncPeriod());
    uint64_t timeStamp = (nanoTimestamp > vsyncPeriod) ? (nanoTimestamp - vsyncPeriod + ONE_MS_IN_NS) : ONE_MS_IN_NS;
    resampleTimeStamp_ = (timeStamp > compensationValue_) ? (timeStamp - compensationValue_) : 0;
#ifdef UICAST_COMPONENT_SUPPORTED
    do {
        auto container = Container::Current();
        CHECK_NULL_BREAK(container);
        auto distributedUI = container->GetDistributedUI();
        CHECK_NULL_BREAK(distributedUI);
        distributedUI->ApplyOneUpdate();
    } while (false);
#endif
    ProcessDelayTasks();
    DispatchDisplaySync(nanoTimestamp);
    FlushAnimation(nanoTimestamp);
    FlushFrameCallback(nanoTimestamp);
    auto hasRunningAnimation = FlushModifierAnimation(nanoTimestamp);
    FlushTouchEvents();
    FlushDragEvents();
    FlushFrameCallbackFromCAPI(nanoTimestamp, frameCount);
    FlushBuild();
    if (isFormRender_ && drawDelegate_ && rootNode_) {
        auto renderContext = AceType::DynamicCast<NG::RenderContext>(rootNode_->GetRenderContext());
        drawDelegate_->DrawRSFrame(renderContext);
        drawDelegate_ = nullptr;
    }
    if (!taskScheduler_->isEmpty()) {
#if !defined(PREVIEW)
        LayoutInspector::SupportInspector();
#endif
    }

    taskScheduler_->StartRecordFrameInfo(GetCurrentFrameInfo(recvTime_, nanoTimestamp));
    taskScheduler_->FlushTask();
    UIObserverHandler::GetInstance().HandleLayoutDoneCallBack();
    if (nodeRenderStatusMonitor_) {
        nodeRenderStatusMonitor_->WalkThroughAncestorForStateListener();
    }
    // flush correct rect again
    taskScheduler_->FlushPersistAfterLayoutTask();
    taskScheduler_->FinishRecordFrameInfo();
    FlushNodeChangeFlag();
    FlushAnimationClosure();
    TryCallNextFrameLayoutCallback();

#ifdef UICAST_COMPONENT_SUPPORTED
    do {
        auto container = Container::Current();
        CHECK_NULL_BREAK(container);
        auto distributedUI = container->GetDistributedUI();
        CHECK_NULL_BREAK(distributedUI);
        distributedUI->OnTreeUpdate();
    } while (false);
#endif

    if (hasRunningAnimation || window_->HasUIRunningAnimation()) {
        RequestFrame();
    }
    window_->FlushModifier();
    FlushFrameRate();
    FlushDragWindowVisibleCallback();
    if (isFirstFlushMessages_) {
        isFirstFlushMessages_ = false;
        LOGI("ArkUi flush first frame messages.");
    }
    // the application is in the background and the dark and light colors are switched.
    if (!onShow_ && backgroundColorModeUpdated_) {
        backgroundColorModeUpdated_ = false;
        FlushMessages([window = window_]() {
            if (window) {
                window->NotifySnapshotUpdate();
            }
        });
    } else {
        FlushMessages();
    }
    FlushWindowPatternInfo();
    InspectDrew();
    UIObserverHandler::GetInstance().HandleDrawCommandSendCallBack();
    if (onShow_ && onFocus_ && isWindowHasFocused_) {
        auto isDynamicRender = Container::Current() == nullptr ? false : Container::Current()->IsDynamicRender();
        if ((!isFormRender_) || isDynamicRender) {
            FlushFocusView();
            FlushFocus();
            FlushFocusScroll();
        }
    }
    HandleOnAreaChangeEvent(nanoTimestamp);
    HandleVisibleAreaChangeEvent(nanoTimestamp);
    FlushMouseEventInVsync();
    eventManager_->FlushCursorStyleRequests();
    if (isNeedFlushAnimationStartTime_) {
        window_->FlushAnimationStartTime(animationTimeStamp_);
        isNeedFlushAnimationStartTime_ = false;
    }
    needRenderNode_.clear();
    taskScheduler_->FlushAfterRenderTask();
    window_->FlushLayoutSize(width_, height_);
    if (IsFocusWindowIdSetted()) {
        FireAllUIExtensionEvents();
    }
    FireAccessibilityEvents();
    // Keep the call sent at the end of the function
    ResSchedReport::GetInstance().LoadPageEvent(ResDefine::LOAD_PAGE_COMPLETE_EVENT);
    TriggerFrameDumpFuncIfExist();
    window_->Unlock();
#ifdef COMPONENT_TEST_ENABLED
    ComponentTest::UpdatePipelineStatus();
#endif // COMPONENT_TEST_ENABLED
}

void PipelineContext::FlushMouseEventVoluntarily()
{
    if (!lastMouseEvent_ || lastMouseEvent_->action == MouseAction::WINDOW_LEAVE ||
        windowSizeChangeReason_ == WindowSizeChangeReason::DRAG) {
        return;
    }
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(rootNode_);
    ACE_SCOPED_TRACE("FlushMouseEventVoluntarily x:%f y:%f", lastMouseEvent_->x, lastMouseEvent_->y);

    MouseEvent event;
    if (isNeedFlushMouseEvent_ == MockFlushEventType::REJECT) {
        event.mockFlushEvent = true;
    }
    event.x = lastMouseEvent_->x;
    event.y = lastMouseEvent_->y;
    event.time = lastMouseEvent_->time;
    event.action = MouseAction::MOVE;
    event.button = MouseButton::NONE_BUTTON;
    event.sourceType = SourceType::MOUSE;
    event.deviceId = lastMouseEvent_->deviceId;
    event.sourceTool = SourceTool::MOUSE;

    auto scaleEvent = event.CreateScaleEvent(viewScale_);
    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = event.sourceType;
    touchRestrict.hitTestType = SourceType::MOUSE;
    touchRestrict.inputEventType = InputEventType::MOUSE_BUTTON;

    eventManager_->MouseTest(scaleEvent, rootNode_, touchRestrict);
    eventManager_->DispatchMouseEventNG(scaleEvent);
    eventManager_->DispatchMouseHoverEventNG(scaleEvent);
    eventManager_->DispatchMouseHoverAnimationNG(scaleEvent);
}

void PipelineContext::FlushWindowPatternInfo()
{
#ifdef WINDOW_SCENE_SUPPORTED
    int32_t id = -1;
    if (SystemProperties::GetAcePerformanceMonitorEnabled()) {
        id = Container::CurrentId();
    }
    OTHER_DURATION(id);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (!container->IsSceneBoardWindow()) {
        return;
    }
    auto screenNode = screenNode_.Upgrade();
    if (!screenNode) {
        return;
    }
    ACE_SCOPED_TRACE("FlushWindowPatternInfo");
    auto instance = WindowSceneLayoutManager::GetInstance();
    if (instance != nullptr) {
        instance->FlushWindowPatternInfo(screenNode);
    }
#endif
}

void PipelineContext::InspectDrew()
{
    CHECK_RUN_ON(UI);
    if (!needRenderNode_.empty()) {
        auto needRenderNode = std::move(needRenderNode_);
        for (auto&& nodeWeak : needRenderNode) {
            auto node = nodeWeak.Upgrade();
            if (!node) {
                return;
            }
            if (node->GetInspectorId().has_value()) {
                OnDrawCompleted(node->GetInspectorId()->c_str());
            }
            auto eventHub = node->GetOrCreateEventHub<NG::EventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->FireDrawCompletedNDKCallback(this);
        }
    }
    if (!needRenderForDrawChildrenNodes_.empty()) {
        auto needRenderNodes = std::move(needRenderForDrawChildrenNodes_);
        for (auto&& nodeWeak : needRenderNodes) {
            auto node = nodeWeak.Upgrade();
            if (node == nullptr) {
                continue;
            }
            if (node->GetInspectorId().has_value()) {
                OnDrawChildrenCompleted(node->GetInspectorId().value());
            }
        }
        needRenderForDrawChildrenNodes_.clear();
    }
}

void PipelineContext::ProcessDelayTasks()
{
    if (delayedTasks_.empty()) {
        return;
    }
    auto currentTimeStamp = GetSysTimestamp();
    auto delayedTasks = std::move(delayedTasks_);
    auto result = std::remove_if(delayedTasks.begin(), delayedTasks.end(), [this, currentTimeStamp](const auto& task) {
        if (task.timeStamp + static_cast<int64_t>(task.time) * MILLISECONDS_TO_NANOSECONDS > currentTimeStamp) {
            delayedTasks_.emplace_back(task);
            return true;
        }
        return false;
    });
    delayedTasks.erase(result, delayedTasks.end());
    std::for_each(delayedTasks.begin(), delayedTasks.end(), [this](auto& delayedTask) {
        if (delayedTask.task) {
            delayedTask.task();
        }
    });
}

void PipelineContext::DispatchDisplaySync(uint64_t nanoTimestamp)
{
    int32_t currentId = -1;
    if (SystemProperties::GetAcePerformanceMonitorEnabled()) {
        currentId = Container::CurrentId();
    }
    OTHER_DURATION(currentId);
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();

    const auto& displaySyncManager = GetOrCreateUIDisplaySyncManager();
    if (!displaySyncManager) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[DispatchDisplaySync] displaySyncManager is nullptr.");
        return;
    }

    displaySyncManager->SetRefreshRateMode(window_->GetCurrentRefreshRateMode());
    displaySyncManager->SetVsyncPeriod(window_->GetVSyncPeriod());

    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().BeginFlushAnimation();
    }

    scheduleTasks_.clear();
    displaySyncManager->DispatchFunc(nanoTimestamp);

    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().EndFlushAnimation();
    }

    int32_t displaySyncRate = displaySyncManager->GetDisplaySyncRate();
    frameRateManager_->SetDisplaySyncRate(displaySyncRate);
    auto monitorVsyncRate = displaySyncManager->GetMonitorVsyncRate();
    auto id = GetInstanceId();
    ArkUIPerfMonitor::GetPerfMonitor(id)->RecordDisplaySyncRate(monitorVsyncRate);
}

void PipelineContext::FlushAnimation(uint64_t nanoTimestamp)
{
    int32_t id = -1;
    if (SystemProperties::GetAcePerformanceMonitorEnabled()) {
        id = Container::CurrentId();
    }
    OTHER_DURATION(id);
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();
    if (scheduleTasks_.empty()) {
        return;
    }
}

void PipelineContext::FlushModifier()
{
    window_->FlushModifier();
}

void PipelineContext::HandleSpecialContainerNode()
{
    if (!SystemProperties::GetContainerDeleteFlag()) {
        return;
    }

    auto positionZSet = GetPositionZNodes();
    for (auto positionZNodeId : positionZSet) {
        auto frameNode = DynamicCast<FrameNode>(ElementRegister::GetInstance()->GetUINodeById(positionZNodeId));
        if (!frameNode) {
            continue;
        }
        auto parentNode = frameNode->GetParentFrameNode();
        if (!parentNode) {
            continue;
        }
        if (parentNode->GetRenderContext()) {
            parentNode->GetRenderContext()->SetDrawNode();
        }
        std::list<RefPtr<FrameNode>> childrenList;
        parentNode->GenerateOneDepthVisibleFrameWithTransition(childrenList);
        for (auto& node : childrenList) {
            if (node && node->GetRenderContext()) {
                node->GetRenderContext()->SetDrawNode();
            }
        }
        auto overlayNode = parentNode->GetOverlayNode();
        if (overlayNode && overlayNode->GetRenderContext()) {
            overlayNode->GetRenderContext()->SetDrawNode();
        }
        auto accessibilityFocusPaintNode = parentNode->GetFocusPaintNode();
        if (accessibilityFocusPaintNode && accessibilityFocusPaintNode->GetRenderContext()) {
            accessibilityFocusPaintNode->GetRenderContext()->SetDrawNode();
        }
    }
    ClearPositionZNodes();
}

void PipelineContext::UpdateOcclusionCullingStatus()
{
    for (auto &&[id, enable] : keyOcclusionNodes_) {
        auto frameNode = DynamicCast<FrameNode>(ElementRegister::GetInstance()->GetUINodeById(id));
        if (!frameNode) {
            continue;
        }
        frameNode->UpdateOcclusionCullingStatus(enable);
    }
    keyOcclusionNodes_.clear();
}

void PipelineContext::FlushMessages(std::function<void()> callback)
{
    int32_t id = -1;
    if (SystemProperties::GetAcePerformanceMonitorEnabled()) {
        id = Container::CurrentId();
    }
    OTHER_DURATION(id);
    ACE_FUNCTION_TRACE_COMMERCIAL();
    if (IsFreezeFlushMessage()) {
        SetIsFreezeFlushMessage(false);
        LOGI("Flush message is freezed.");
        return;
    }
    if (navigationMgr_) {
        navigationMgr_->CacheNavigationNodeAnimation();
    }
    if (!window_->GetIsRequestFrame()) {
        ACE_SCOPED_TRACE("smart gc end with no request frame(app_start or push_page)!");
        ResSchedReport::GetInstance().ResSchedDataReport("page_end_flush", {});
    }
    HandleSpecialContainerNode();
    UpdateOcclusionCullingStatus();
    window_->FlushTasks(callback);
}

void PipelineContext::FlushUITasks(bool triggeredByImplicitAnimation)
{
    window_->Lock();
    if (!CheckThreadSafe()) {
        LOGW("FlushUITasks doesn't run on UI thread!");
    }
    decltype(dirtyPropertyNodes_) dirtyPropertyNodes(std::move(dirtyPropertyNodes_));
    dirtyPropertyNodes_.clear();
    for (const auto& dirtyNode : dirtyPropertyNodes) {
        dirtyNode->ProcessPropertyDiff();
    }
    taskScheduler_->FlushTaskWithCheck(triggeredByImplicitAnimation);
    if (AnimationUtils::IsImplicitAnimationOpen()) {
        FlushNodeChangeFlag();
    }
    window_->Unlock();
}

void PipelineContext::FlushUITaskWithSingleDirtyNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    if (IsLayouting()) {
        taskScheduler_->AddSingleNodeToFlush(node);
        return;
    }
    auto layoutProperty = node->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutConstraint = node->GetLayoutConstraint();
    auto originLayoutingFlag = IsLayouting();
    SetIsLayouting(true);
    if (layoutProperty->GetLayoutRect()) {
        node->SetActive(true, true);
        node->Measure(std::nullopt);
        node->Layout();
    } else {
        auto ancestorNodeOfFrame = node->GetAncestorNodeOfFrame(false);
        {
            ACE_SCOPED_TRACE("FlushUITaskWithSingleDirtyNodeMeasure[%s][self:%d][parent:%d][layoutConstraint:%s]"
                             "[pageId:%d][depth:%d]",
                node->GetTag().c_str(), node->GetId(), ancestorNodeOfFrame ? ancestorNodeOfFrame->GetId() : 0,
                layoutConstraint.ToString().c_str(), node->GetPageId(), node->GetDepth());
            node->Measure(layoutConstraint);
        }
        {
            ACE_SCOPED_TRACE("FlushUITaskWithSingleDirtyNodeLayout[%s][self:%d][parent:%d][pageId:%d][depth:%d]",
                node->GetTag().c_str(), node->GetId(), ancestorNodeOfFrame ? ancestorNodeOfFrame->GetId() : 0,
                node->GetPageId(), node->GetDepth());
            node->Layout();
        }
    }
    SetIsLayouting(originLayoutingFlag);
}

void PipelineContext::FlushAfterLayoutCallbackInImplicitAnimationTask()
{
    if (AnimationUtils::IsImplicitAnimationOpen()) {
        TAG_LOGD(AceLogTag::ACE_ANIMATION,
            "Can not flush implicit animation task after layout because implicit animation is open.");
        return;
    }
    window_->Lock();
    taskScheduler_->FlushAfterLayoutCallbackInImplicitAnimationTask();
    window_->Unlock();
}

void PipelineContext::SetNeedRenderNode(const WeakPtr<FrameNode>& node)
{
    CHECK_RUN_ON(UI);
    needRenderNode_.insert(node);
}

void PipelineContext::SetNeedRenderForDrawChildrenNode(const WeakPtr<NG::UINode>& node)
{
    CHECK_NULL_VOID(node.Upgrade());
    needRenderForDrawChildrenNodes_.emplace(node);
}

void PipelineContext::FlushFocus()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACK();
    ACE_FUNCTION_TRACE();

    FlushRequestFocus();

    auto focusNode = dirtyFocusNode_.Upgrade();
    if (!focusNode || focusNode->GetFocusType() != FocusType::NODE) {
        dirtyFocusNode_.Reset();
    } else {
        FlushFocusWithNode(focusNode, false);
        return;
    }
    auto focusScope = dirtyFocusScope_.Upgrade();
    if (!focusScope || focusScope->GetFocusType() != FocusType::SCOPE) {
        dirtyFocusScope_.Reset();
    } else {
        FlushFocusWithNode(focusScope, true);
        return;
    }
    GetOrCreateFocusManager()->WindowFocusMoveEnd();
}

void PipelineContext::FlushFocusWithNode(RefPtr<FrameNode> focusNode, bool isScope)
{
    auto focusNodeHub = focusNode->GetFocusHub();
    if (focusNodeHub && !focusNodeHub->RequestFocusImmediately()) {
        auto unfocusableParentFocusNode = focusNodeHub->GetUnfocusableParentFocusNode().Upgrade();
        if (unfocusableParentFocusNode) {
            TAG_LOGD(AceLogTag::ACE_FOCUS,
                "Request focus on %{public}s: %{public}s/%{public}d return false, unfocusable node: "
                "%{public}s/%{public}d, focusable = %{public}d, shown = %{public}d, enabled = %{public}d",
                isScope ? "scope" : "node", focusNode->GetTag().c_str(), focusNode->GetId(),
                unfocusableParentFocusNode->GetFrameName().c_str(), unfocusableParentFocusNode->GetFrameId(),
                unfocusableParentFocusNode->GetFocusable(), unfocusableParentFocusNode->IsShow(),
                unfocusableParentFocusNode->IsEnabled());
            unfocusableParentFocusNode = nullptr;
        } else {
            TAG_LOGD(AceLogTag::ACE_FOCUS, "Request focus on %{public}s: %{public}s/%{public}d return false",
                isScope ? "scope" : "node", focusNode->GetTag().c_str(), focusNode->GetId());
        }
    }
    dirtyFocusNode_.Reset();
    dirtyFocusScope_.Reset();
    dirtyRequestFocusNode_.Reset();
    GetOrCreateFocusManager()->WindowFocusMoveEnd();
}

void PipelineContext::FlushRequestFocus()
{
    CHECK_RUN_ON(UI);

    auto requestFocusNode = dirtyRequestFocusNode_.Upgrade();
    if (!requestFocusNode) {
        dirtyRequestFocusNode_.Reset();
    } else {
        auto focusNodeHub = requestFocusNode->GetFocusHub();
        if (focusNodeHub && !focusNodeHub->RequestFocusImmediately()) {
            auto unfocusableParentFocusNode = focusNodeHub->GetUnfocusableParentFocusNode().Upgrade();
            if (unfocusableParentFocusNode) {
                TAG_LOGI(AceLogTag::ACE_FOCUS,
                    "Request focus by id on node: %{public}s/%{public}d return false, unfocusable node: "
                    "%{public}s/%{public}d, focusable = %{public}d, shown = %{public}d, enabled = %{public}d",
                    requestFocusNode->GetTag().c_str(), requestFocusNode->GetId(),
                    unfocusableParentFocusNode->GetFrameName().c_str(), unfocusableParentFocusNode->GetFrameId(),
                    unfocusableParentFocusNode->GetFocusable(), unfocusableParentFocusNode->IsShow(),
                    unfocusableParentFocusNode->IsEnabled());
                unfocusableParentFocusNode = nullptr;
            } else {
                TAG_LOGI(AceLogTag::ACE_FOCUS, "Request focus by id on node: %{public}s/%{public}d return false",
                    requestFocusNode->GetTag().c_str(), requestFocusNode->GetId());
            }
        }
        dirtyFocusNode_.Reset();
        dirtyFocusScope_.Reset();
        dirtyRequestFocusNode_.Reset();
        return;
    }
}

void PipelineContext::FlushFocusView()
{
    CHECK_NULL_VOID(focusManager_);
    auto lastFocusView = (focusManager_->GetLastFocusView()).Upgrade();
    CHECK_NULL_VOID(lastFocusView);
    auto lastFocusViewHub = lastFocusView->GetFocusHub();
    CHECK_NULL_VOID(lastFocusViewHub);
    ACE_EVENT_SCOPED_TRACE("FlushFocusView:[%s][%d][enable:%d][show:%d]", lastFocusViewHub->GetFrameName().c_str(),
        lastFocusViewHub->GetFrameId(), lastFocusViewHub->IsEnabled(), lastFocusViewHub->IsShow());
    auto container = Container::Current();
    if (container && (container->IsUIExtensionWindow() || container->IsDynamicRender()) &&
        (!lastFocusView->IsRootScopeCurrentFocus())) {
        lastFocusView->SetIsViewRootScopeFocused(false);
    }
    if (lastFocusView && (!lastFocusView->IsRootScopeCurrentFocus() || !lastFocusView->GetIsViewHasFocused()) &&
        lastFocusViewHub->IsFocusableNode()) {
        lastFocusView->RequestDefaultFocus();
        focusManager_->SetFocusViewStackState(FocusViewStackState::IDLE);
    }
}

void PipelineContext::FlushFocusScroll()
{
    CHECK_NULL_VOID(focusManager_);
    if (!focusManager_->GetNeedTriggerScroll()) {
        return;
    }
    auto lastFocusStateNode = focusManager_->GetLastFocusStateNode();
    CHECK_NULL_VOID(lastFocusStateNode);
    if (!lastFocusStateNode->TriggerFocusScroll()) {
        focusManager_->SetNeedTriggerScroll(false);
    }
}

void PipelineContext::FlushPipelineImmediately()
{
    CHECK_RUN_ON(UI);
    ACE_SCOPED_TRACE("PipelineContext::FlushPipelineImmediately, isLayouting_ %d", taskScheduler_->IsLayouting());
    if (!taskScheduler_->IsLayouting()) {
        FlushPipelineWithoutAnimation();
        return;
    }
    auto task = [weak = WeakClaim(this)]() {
        auto pipeline = weak.Upgrade();
        CHECK_NULL_VOID(pipeline);
        pipeline->FlushPipelineWithoutAnimation();
    };
    AddAfterLayoutTask(task);
}

void PipelineContext::RebuildFontNode()
{
    if (fontManager_) {
        fontManager_->RebuildFontNodeNG();
    }
}

void PipelineContext::FlushPipelineWithoutAnimation()
{
    ACE_FUNCTION_TRACE();
    window_->Lock();
    FlushBuild();
    FlushTouchEvents();
    taskScheduler_->FlushTask();
    FlushAnimationClosure();
    window_->FlushModifier();
    FlushMessages();
    FlushFocus();
    window_->Unlock();
}

void PipelineContext::FlushFrameRate()
{
    frameRateManager_->SetAnimateRate(window_->GetAnimateExpectedRate(), window_->HasFirstFrameAnimation());
    int32_t currAnimatorExpectedFrameRate = GetOrCreateUIDisplaySyncManager()->GetAnimatorRate();
    if (frameRateManager_->IsRateChanged() || currAnimatorExpectedFrameRate != lastAnimatorExpectedFrameRate_) {
        auto [rate, rateType] = frameRateManager_->GetExpectedRate();
        ACE_SCOPED_TRACE("FlushFrameRate Expected frameRate = %d frameRateType = %d "
            "currAnimatorExpectedFrameRate = %d, lastAnimatorExpectedFrameRate = %d",
            rate, rateType, currAnimatorExpectedFrameRate, lastAnimatorExpectedFrameRate_);
        TAG_LOGD(AceLogTag::ACE_DISPLAY_SYNC, "FlushFrameRate Expected frameRate = %{public}d "
            "frameRateType = %{public}d currAnimatorExpectedFrameRate = %{public}d, lastRate = %{public}d",
            rate, rateType, currAnimatorExpectedFrameRate, lastAnimatorExpectedFrameRate_);
        window_->FlushFrameRate(rate, currAnimatorExpectedFrameRate, rateType);
        frameRateManager_->SetIsRateChanged(false);
        lastAnimatorExpectedFrameRate_ = currAnimatorExpectedFrameRate;
    }
}

void PipelineContext::FlushDragWindowVisibleCallback()
{
    if (dragWindowVisibleCallback_) {
        dragWindowVisibleCallback_();
        dragWindowVisibleCallback_ = nullptr;
    }
}

void PipelineContext::FlushBuild()
{
    if (vsyncListener_ != nullptr) {
        ACE_SCOPED_TRACE("arkoala build");
        vsyncListener_();
    }
    FlushOnceVsyncTask();
    isRebuildFinished_ = false;
    FlushDirtyNodeUpdate();
    isRebuildFinished_ = true;
    FlushBuildFinishCallbacks();
}

void PipelineContext::SetVsyncListener(VsyncCallbackFun vsync)
{
    vsyncListener_ = std::move(vsync);
}

void PipelineContext::AddAnimationClosure(std::function<void()>&& animation)
{
    animationClosuresList_.emplace_back(std::move(animation));
}

void PipelineContext::FlushAnimationClosure()
{
    if (animationClosuresList_.empty()) {
        return;
    }
    window_->Lock();
    taskScheduler_->FlushTask();

    decltype(animationClosuresList_) temp(std::move(animationClosuresList_));
    for (const auto& animation : temp) {
        animation();
    }
    window_->Unlock();
}

void PipelineContext::FlushBuildFinishCallbacks()
{
    decltype(buildFinishCallbacks_) buildFinishCallbacks(std::move(buildFinishCallbacks_));
    for (const auto& func : buildFinishCallbacks) {
        if (func) {
            func();
        }
    }
}

void PipelineContext::RegisterRootEvent()
{
    if (!IsFormRender()) {
        return;
    }
    auto accessibilityProperty = rootNode_->GetAccessibilityProperty<AccessibilityProperty>();
    if (accessibilityProperty != nullptr) {
        accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::NO_STR);
    }

    // To avoid conflicts between longPress and click events on the card,
    // use an empty longPress event placeholder in the EtsCard scenario
    auto hub = rootNode_->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(hub);
    auto event = [](const GestureEvent& info) mutable {};
    auto longPress = AceType::MakeRefPtr<NG::LongPressEvent>(std::move(event));
    hub->SetLongPressEvent(longPress, false, true);
}

void PipelineContext::SetupRootElement()
{
    CHECK_RUN_ON(UI);
    auto rootPattern = ViewAdvancedRegister::GetInstance()->GeneratePattern(V2::ROOT_ETS_TAG);
    if (!rootPattern) {
        rootPattern = MakeRefPtr<RootPattern>();
    }
    rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), rootPattern);
    rootNode_->SetHostRootId(GetInstanceId());
    rootNode_->SetHostPageId(-1);
    rootNode_->SetActive(true);
    RegisterRootEvent();
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
    auto stagePattern = ViewAdvancedRegister::GetInstance()->GeneratePattern(V2::STAGE_ETS_TAG);
    if (!stagePattern) {
        stagePattern = MakeRefPtr<StagePattern>();
    }
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), stagePattern);
    RefPtr<AppBarView> appBar = AceType::MakeRefPtr<AppBarView>();
    auto atomicService = installationFree_ ? appBar->Create(stageNode) : nullptr;
    auto container = Container::Current();
    if (container && installationFree_) {
        container->SetAppBar(appBar);
    }
    if (windowModal_ == WindowModal::CONTAINER_MODAL) {
        MaximizeMode maximizeMode = GetWindowManager()->GetWindowMaximizeMode();
        rootNode_->AddChild(
            ContainerModalViewFactory::GetView(atomicService ? atomicService : stageNode, maximizeMode));
    } else {
        rootNode_->AddChild(atomicService ? atomicService : stageNode);
    }
#ifdef ENABLE_ROSEN_BACKEND
    std::shared_ptr<Rosen::RSUIDirector> rsUIDirector;
    if (!IsJsCard() && !isFormRender_) {
        auto window = GetWindow();
        if (window) {
            rsUIDirector = window->GetRSUIDirector();
            if (rsUIDirector) {
                rsUIDirector->SetAbilityBGAlpha(appBgColor_.GetAlpha());
            }
        }
    }
    FlushImplicitTransaction(rsUIDirector);
#endif
    accessibilityManagerNG_ = MakeRefPtr<AccessibilityManagerNG>();
    stageManager_ = ViewAdvancedRegister::GetInstance()->GenerateStageManager(stageNode);
    if (!stageManager_) {
        stageManager_ = MakeRefPtr<StageManager>(stageNode);
    }
    auto getPagePathCallback = [weakFrontend = weakFrontend_](const std::string& url) -> std::string {
        auto frontend = weakFrontend.Upgrade();
        CHECK_NULL_RETURN(frontend, "");
        return frontend->GetPagePathByUrl(url);
    };
    stageManager_->SetGetPagePathCallback(std::move(getPagePathCallback));
    auto frameNode = DynamicCast<FrameNode>(installationFree_ ? atomicService->GetParent() :
        stageNode->GetParent());
    overlayManager_ = MakeRefPtr<OverlayManager>(frameNode);
    fullScreenManager_ = MakeRefPtr<FullScreenManager>(rootNode_);
    selectOverlayManager_ = MakeRefPtr<SelectOverlayManager>(rootNode_);
    fontManager_->AddFontObserver(selectOverlayManager_);
    if (!privacySensitiveManager_) {
        privacySensitiveManager_ = MakeRefPtr<PrivacySensitiveManager>();
    }
    postEventManager_ = MakeRefPtr<PostEventManager>();
    dragDropManager_ = MakeRefPtr<DragDropManager>();
    focusManager_ = GetOrCreateFocusManager();
    sharedTransitionManager_ = MakeRefPtr<SharedOverlayManager>(
        DynamicCast<FrameNode>(installationFree_ ? atomicService->GetParent() : stageNode->GetParent()));

    auto instanceId = container->GetInstanceId();
    OnAreaChangedFunc onAreaChangedFunc = [weakOverlayManger = AceType::WeakClaim(AceType::RawPtr(overlayManager_)),
                                              instanceId](
                                              const RectF& /* oldRect */, const OffsetF& /* oldOrigin */,
                                              const RectF& /* rect */, const OffsetF& /* origin */) {
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "start OnAreaChangedFunc");
        auto overlay = weakOverlayManger.Upgrade();
        CHECK_NULL_VOID(overlay);
        auto container = Container::GetContainer(instanceId);
        // In sceneBoard window, popup and menu need be cleared without animation.
        if (container && container->IsSceneBoardWindow()) {
            overlay->HideAllMenusWithoutAnimation();
            overlay->HideAllPopupsWithoutAnimation();
            SubwindowManager::GetInstance()->ClearAllMenuPopup(instanceId);
        } else {
            overlay->HideAllMenus();
            SubwindowManager::GetInstance()->HideMenuNG(false);
            overlay->HideCustomPopups();
        }
        SubwindowManager::GetInstance()->ClearToastInSubwindow();
        SubwindowManager::GetInstance()->ClearToastInSystemSubwindow();
        overlay->UpdateCustomKeyboardPosition();
    };
    rootNode_->SetOnAreaChangeCallback(std::move(onAreaChangedFunc));
    AddOnAreaChangeNode(rootNode_->GetId());
}

void PipelineContext::SetOnWindowFocused(const std::function<void()>& callback)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask([weak = WeakClaim(this), callback]() {
            auto pipeline = weak.Upgrade();
            CHECK_NULL_VOID(pipeline);
            pipeline->focusOnNodeCallback_ = callback;
        }, TaskExecutor::TaskType::UI, "ArkUISetOnWindowFocusedCallback");
}

void PipelineContext::FlushImplicitTransaction(const std::shared_ptr<Rosen::RSUIDirector>& rsUIDirector)
{
#ifdef ENABLE_ROSEN_BACKEND
    if (SystemProperties::GetMultiInstanceEnabled() && rsUIDirector) {
        auto surfaceNode = rsUIDirector->GetRSSurfaceNode();
        if (surfaceNode) {
            auto rsUIContext = surfaceNode->GetRSUIContext();
            if (rsUIContext) {
                auto rsTransaction = rsUIContext->GetRSTransaction();
                if (rsTransaction) {
                    rsTransaction->FlushImplicitTransaction();
                }
            }
        }
    }
#endif
}

void PipelineContext::SetupSubRootElement()
{
    CHECK_RUN_ON(UI);
    appBgColor_ = Color::TRANSPARENT;
    auto rootPattern = ViewAdvancedRegister::GetInstance()->GeneratePattern(V2::ROOT_ETS_TAG);
    if (!rootPattern) {
        rootPattern = MakeRefPtr<RootPattern>();
    }
    rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), rootPattern);
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

#ifdef ENABLE_ROSEN_BACKEND
    std::shared_ptr<Rosen::RSUIDirector> rsUIDirector;
    if (!IsJsCard()) {
        auto window = GetWindow();
        if (window) {
            rsUIDirector = window->GetRSUIDirector();
            if (rsUIDirector) {
                rsUIDirector->SetAbilityBGAlpha(appBgColor_.GetAlpha());
            }
        }
    }
    FlushImplicitTransaction(rsUIDirector);
#endif
#ifdef WINDOW_SCENE_SUPPORTED
    uiExtensionManager_ = MakeRefPtr<UIExtensionManager>();
#endif
    accessibilityManagerNG_ = MakeRefPtr<AccessibilityManagerNG>();
    // the subwindow for overlay not need stage
    stageManager_ = ViewAdvancedRegister::GetInstance()->GenerateStageManager(nullptr);
    if (!stageManager_) {
        stageManager_ = MakeRefPtr<StageManager>(nullptr);
    }
    auto getPagePathCallback = [weakFrontend = weakFrontend_](const std::string& url) -> std::string {
        auto frontend = weakFrontend.Upgrade();
        CHECK_NULL_RETURN(frontend, "");
        return frontend->GetPagePathByUrl(url);
    };
    stageManager_->SetGetPagePathCallback(std::move(getPagePathCallback));
    overlayManager_ = MakeRefPtr<OverlayManager>(rootNode_);
    fullScreenManager_ = MakeRefPtr<FullScreenManager>(rootNode_);
    selectOverlayManager_ = MakeRefPtr<SelectOverlayManager>(rootNode_);
    fontManager_->AddFontObserver(selectOverlayManager_);
    dragDropManager_ = MakeRefPtr<DragDropManager>();
    focusManager_ = GetOrCreateFocusManager();
    postEventManager_ = MakeRefPtr<PostEventManager>();
}

RefPtr<AccessibilityManagerNG> PipelineContext::GetAccessibilityManagerNG()
{
    return accessibilityManagerNG_;
}

void PipelineContext::SendEventToAccessibilityWithNode(
    const AccessibilityEvent& accessibilityEvent, const RefPtr<FrameNode>& node)
{
    auto accessibilityManager = GetAccessibilityManager();
    if (!accessibilityManager || !AceApplicationInfo::GetInstance().IsAccessibilityEnabled()) {
        return;
    }
    accessibilityManager->SendEventToAccessibilityWithNode(accessibilityEvent, node, Claim(this));
}

const RefPtr<StageManager>& PipelineContext::GetStageManager()
{
    return stageManager_;
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
        RegisterFocusCallback();
    }
    return focusManager_;
}

const RefPtr<SelectOverlayManager>& PipelineContext::GetSelectOverlayManager()
{
    return selectOverlayManager_;
}

const RefPtr<OverlayManager>& PipelineContext::GetOverlayManager()
{
    return overlayManager_;
}

const RefPtr<FullScreenManager>& PipelineContext::GetFullScreenManager()
{
    return fullScreenManager_;
}

void PipelineContext::OnSurfaceChanged(int32_t width, int32_t height, WindowSizeChangeReason type,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    ACE_SCOPED_TRACE("PipelineContext::OnSurfaceChanged");
    CHECK_RUN_ON(UI);
    width_ = width;
    height_ = height;
    if (NearEqual(rootWidth_, width) && NearEqual(rootHeight_, height) &&
        type == WindowSizeChangeReason::CUSTOM_ANIMATION && !isDensityChanged_) {
        TryCallNextFrameLayoutCallback();
        return;
    }
    ExecuteSurfaceChangedCallbacks(width, height, type);
    auto callback = [weakFrontend = weakFrontend_, width, height]() {
        auto frontend = weakFrontend.Upgrade();
        if (frontend) {
            frontend->OnSurfaceChanged(width, height);
        }
    };
    auto container = Container::Current();
    if (!container) {
        return;
    }
    if (container->IsUseStageModel()) {
        callback();
        FlushBuild();
    } else {
        taskExecutor_->PostTask(callback, TaskExecutor::TaskType::JS, "ArkUISurfaceChanged");
    }

    FlushWindowSizeChangeCallback(width, height, type);
    UpdateHalfFoldHoverProperty(width, height);
    UpdateSizeChangeReason(type, rsTransaction);

#ifdef ENABLE_ROSEN_BACKEND
    StartWindowSizeChangeAnimate(width, height, type, rsTransaction);
#else
    SetRootRect(width, height, 0.0);
#endif
}

void PipelineContext::UpdateHalfFoldHoverProperty(int32_t windowWidth, int32_t windowHeight)
{
    isHoverModeChanged_ = false;
    preIsHalfFoldHoverStatus_ = isHalfFoldHoverStatus_;
    UpdateHalfFoldHoverStatus(windowWidth, windowHeight);
    if (preIsHalfFoldHoverStatus_ != isHalfFoldHoverStatus_) {
        isHoverModeChanged_ = true;
    }
}

void PipelineContext::OnLayoutCompleted(const std::string& componentId)
{
    CHECK_RUN_ON(UI);
    auto frontend = weakFrontend_.Upgrade();
    if (frontend) {
        frontend->OnLayoutCompleted(componentId);
    }
}

void PipelineContext::OnDrawCompleted(const std::string& componentId)
{
    CHECK_RUN_ON(UI);
    auto frontend = weakFrontend_.Upgrade();
    if (frontend) {
        frontend->OnDrawCompleted(componentId);
    }
}

void PipelineContext::OnDrawChildrenCompleted(const std::string& componentId)
{
    CHECK_RUN_ON(UI);
    auto frontend = weakFrontend_.Upgrade();
    if (frontend) {
        frontend->OnDrawChildrenCompleted(componentId);
    }
}

void PipelineContext::ExecuteSurfaceChangedCallbacks(int32_t newWidth, int32_t newHeight, WindowSizeChangeReason type)
{
    SurfaceChangedCallbackMap callbackMap;
    std::swap(callbackMap, surfaceChangedCallbackMap_);
    for (auto&& [id, callback] : callbackMap) {
        if (callback) {
            callback(newWidth, newHeight, rootWidth_, rootHeight_, type);
        }
    }
    std::swap(callbackMap, surfaceChangedCallbackMap_);
}

void PipelineContext::OnSurfacePositionChanged(int32_t posX, int32_t posY)
{
    for (auto&& [id, callback] : surfacePositionChangedCallbackMap_) {
        if (callback) {
            callback(posX, posY);
        }
    }
}

void PipelineContext::OnFoldStatusChange(FoldStatus foldStatus)
{
    for (auto&& [id, callback] : foldStatusChangedCallbackMap_) {
        if (callback) {
            callback(foldStatus);
        }
    }
    StartFoldStatusDelayTask(foldStatus);
}

void PipelineContext::OnFoldDisplayModeChange(FoldDisplayMode foldDisplayMode)
{
    for (auto&& [id, callback] : foldDisplayModeChangedCallbackMap_) {
        if (callback) {
            callback(foldDisplayMode);
        }
    }
}

void PipelineContext::OnTransformHintChanged(uint32_t transform)
{
    for (auto&& [id, callback] : transformHintChangedCallbackMap_) {
        if (callback) {
            callback(transform);
        }
    }
    transform_ = transform;
}

void PipelineContext::StartWindowSizeChangeAnimate(int32_t width, int32_t height, WindowSizeChangeReason type,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    static const bool IsWindowSizeAnimationEnabled = SystemProperties::IsWindowSizeAnimationEnabled();
    if (!IsWindowSizeAnimationEnabled) {
        SetRootRect(width, height, 0.0);
        return;
    }
    switch (type) {
        case WindowSizeChangeReason::FULL_TO_SPLIT:
        case WindowSizeChangeReason::FULL_TO_FLOATING: {
            StartFullToMultWindowAnimation(width, height, type, rsTransaction);
            break;
        }
        case WindowSizeChangeReason::RECOVER:
        case WindowSizeChangeReason::MAXIMIZE: {
            StartWindowMaximizeAnimation(width, height, rsTransaction);
            break;
        }
        case WindowSizeChangeReason::MAXIMIZE_TO_SPLIT:
        case WindowSizeChangeReason::SPLIT_TO_MAXIMIZE: {
            StartSplitWindowAnimation(width, height, type, rsTransaction);
            break;
        }
        case WindowSizeChangeReason::MAXIMIZE_IN_IMPLICT:
        case WindowSizeChangeReason::RECOVER_IN_IMPLICIT: {
            MaximizeInImplictAnimation(width, height, type, rsTransaction);
            break;
        }
        case WindowSizeChangeReason::ROTATION: {
            safeAreaManager_->UpdateKeyboardOffset(0.0);
            SetRootRect(width, height, 0.0);
            FlushUITasks();
            if (textFieldManager_) {
                DynamicCast<TextFieldManagerNG>(textFieldManager_)->ScrollTextFieldToSafeArea();
            }
            FlushUITasks();
            if (!textFieldManager_) {
                break;
            }
            PostKeyboardAvoidTask();
            break;
        }
        case WindowSizeChangeReason::RESIZE_WITH_ANIMATION: {
            SetRootRect(width, height, 0.0);
            FlushUITasks();
            break;
        }
        case WindowSizeChangeReason::DRAG_START:
        case WindowSizeChangeReason::DRAG:
        case WindowSizeChangeReason::DRAG_END:
        case WindowSizeChangeReason::RESIZE:
        case WindowSizeChangeReason::UNDEFINED:
        default: {
            SetRootRect(width, height, 0.0f);
        }
    }
}

void PipelineContext::PostKeyboardAvoidTask()
{
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(textFieldManager_);
    CHECK_NULL_VOID(textFieldManager);
    if (textFieldManager->UsingCustomKeyboardAvoid()) {
        taskExecutor_->PostTask(
            [weak = WeakPtr<TextFieldManagerNG>(textFieldManager)] {
                auto manager = weak.Upgrade();
                CHECK_NULL_VOID(manager);
                manager->TriggerCustomKeyboardAvoid();
            },
            TaskExecutor::TaskType::UI, "ArkUICustomKeyboardAvoid");
        return;
    }
    auto container = Container::Current();
    int32_t orientation = -1;
    if (container) {
        auto displayInfo = container->GetDisplayInfo();
        orientation = displayInfo ? (int32_t)displayInfo->GetRotation() : -1;
        if (textFieldManager->GetLaterAvoid() && textFieldManager->GetLaterOrientation() != orientation) {
            TAG_LOGI(AceLogTag::ACE_KEYBOARD, "orientation not match, clear laterAvoid");
            textFieldManager->SetLaterAvoid(false);
            return;
        }
    }
    taskExecutor_->PostTask(
        [weakContext = WeakClaim(this), weakManager = WeakPtr<TextFieldManagerNG>(textFieldManager), orientation] {
            auto manager = weakManager.Upgrade();
            CHECK_NULL_VOID(manager);
            if (!manager->GetLaterAvoid()) {
                manager->SetContextTriggerAvoidTaskOrientation(orientation);
                return;
            }
            auto context = weakContext.Upgrade();
            CHECK_NULL_VOID(context);
            TAG_LOGI(AceLogTag::ACE_KEYBOARD, "after rotation set root, trigger avoid now");
            auto keyboardRect = manager->GetLaterAvoidKeyboardRect();
            auto positionY = manager->GetLaterAvoidPositionY();
            auto height = manager->GetLaterAvoidHeight();
            context->OnVirtualKeyboardAreaChange(keyboardRect, positionY, height, nullptr, true);
            manager->SetLaterAvoid(false);
        },
        TaskExecutor::TaskType::UI, "ArkUIVirtualKeyboardAreaChange");
}

void PipelineContext::StartWindowMaximizeAnimation(
    int32_t width, int32_t height, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    TAG_LOGI(AceLogTag::ACE_ANIMATION,
        "Root node start RECOVER/MAXIMIZE animation, width = %{public}d, height = %{public}d", width, height);
#ifdef ENABLE_ROSEN_BACKEND
    if (rsTransaction) {
        FlushMessages();
        rsTransaction->Begin();
    }
#endif
    AnimationOption option;
    int32_t duration = 400;
    MaximizeMode maximizeMode = GetWindowManager()->GetWindowMaximizeMode();
    bool freeMultiWindowModeEnabled = GetWindowManager()->GetFreeMultiWindowModeEnabledState();
    if (maximizeMode == MaximizeMode::MODE_FULL_FILL || maximizeMode == MaximizeMode::MODE_AVOID_SYSTEM_BAR ||
        freeMultiWindowModeEnabled) {
        duration = 0;
    }
    option.SetDuration(duration);
    auto curve = Curves::EASE_OUT;
    option.SetCurve(curve);
    auto weak = WeakClaim(this);
    Animate(option, curve, [width, height, weak]() {
        auto pipeline = weak.Upgrade();
        CHECK_NULL_VOID(pipeline);
        pipeline->SetRootRect(width, height, 0.0);
        pipeline->FlushUITasks();
    });
#ifdef ENABLE_ROSEN_BACKEND
    if (rsTransaction) {
        rsTransaction->Commit();
    }
#endif
}

void PipelineContext::StartFullToMultWindowAnimation(int32_t width, int32_t height, WindowSizeChangeReason type,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    TAG_LOGI(AceLogTag::ACE_ANIMATION,
        "Root node start multiple window animation, type = %{public}d, width = %{public}d, height = %{public}d", type,
        width, height);
#ifdef ENABLE_ROSEN_BACKEND
    if (rsTransaction) {
        FlushMessages();
        rsTransaction->Begin();
    }
#endif
    float response = 0.5f;
    float dampingFraction = 1.0f;
    AnimationOption option;
    if (type == WindowSizeChangeReason::FULL_TO_FLOATING) {
        response = 0.45f;
        dampingFraction = 0.75f;
    }
    auto springMotion = AceType::MakeRefPtr<ResponsiveSpringMotion>(response, dampingFraction, 0);
    option.SetCurve(springMotion);
    auto weak = WeakClaim(this);
    Animate(option, springMotion, [width, height, weak]() {
        auto pipeline = weak.Upgrade();
        CHECK_NULL_VOID(pipeline);
        pipeline->SetRootRect(width, height, 0.0);
        pipeline->FlushUITasks();
    });
#ifdef ENABLE_ROSEN_BACKEND
    if (rsTransaction) {
        rsTransaction->Commit();
    }
#endif
}

void PipelineContext::StartSplitWindowAnimation(int32_t width, int32_t height, WindowSizeChangeReason type,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
        "Root node start split window animation, type = %{public}d, width = %{public}d, height = %{public}d", type,
        width, height);
#ifdef ENABLE_ROSEN_BACKEND
    if (rsTransaction) {
        FlushMessages();
        rsTransaction->Begin();
    }
#endif
    auto curve = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 300.0f, 33.0f);
    AnimationOption option;
    option.SetCurve(curve);
    Animate(option, curve, [width, height, weak = WeakClaim(this)]() {
        auto pipeline = weak.Upgrade();
        CHECK_NULL_VOID(pipeline);
        pipeline->SetRootRect(width, height, 0.0);
        pipeline->FlushUITasks();
    });
#ifdef ENABLE_ROSEN_BACKEND
    if (rsTransaction) {
        rsTransaction->Commit();
    }
#endif
}

void PipelineContext::MaximizeInImplictAnimation(int32_t width, int32_t height, WindowSizeChangeReason type,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
        "Maximize window in implict animation, type = %{public}d, width = %{public}d, height = %{public}d", type,
        width, height);
#ifdef ENABLE_ROSEN_BACKEND
    if (rsTransaction) {
        FlushMessages();
        rsTransaction->Begin();
    }
#endif
    auto curve = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 300.0f, 33.0f);
    AnimationOption option;
    option.SetCurve(curve);
    Animate(option, curve, [width, height, weak = WeakClaim(this)]() {
        auto pipeline = weak.Upgrade();
        CHECK_NULL_VOID(pipeline);
        pipeline->SetRootRect(width, height, 0.0);
        pipeline->FlushUITasks();
    });
#ifdef ENABLE_ROSEN_BACKEND
    if (rsTransaction) {
        rsTransaction->Commit();
    }
#endif
}

void PipelineContext::SetRootRect(double width, double height, double offset)
{
    CHECK_RUN_ON(UI);
    UpdateRootSizeAndScale(width, height);
    CHECK_NULL_VOID(rootNode_);
    ACE_SCOPED_TRACE("SetRootRect: origin:%s,set width:%f, height:%f, offset:%f",
        rootNode_->GetGeometryNode()->GetFrameRect().ToString().c_str(), width, height, offset);
    if (Container::CurrentId() < MIN_SUBCONTAINER_ID) {
        ScreenSystemManager::GetInstance().SetWindowInfo(rootWidth_, density_, dipScale_);
        ScreenSystemManager::GetInstance().OnSurfaceChanged(width);
    } else {
        ScreenSystemManager::GetInstance().SetWindowInfo(density_, dipScale_);
    }
    SizeF sizeF { static_cast<float>(width), static_cast<float>(height) };
    if (rootNode_->GetGeometryNode()->GetFrameSize() != sizeF || rootNode_->IsLayoutDirtyMarked()) {
        CalcSize idealSize { CalcLength(width), CalcLength(height) };
        MeasureProperty layoutConstraint;
        layoutConstraint.selfIdealSize = idealSize;
        layoutConstraint.maxSize = idealSize;
        rootNode_->UpdateLayoutConstraint(layoutConstraint);
        // reset parentLayoutConstraint to update itself when next measure task
        rootNode_->GetGeometryNode()->ResetParentLayoutConstraint();
        rootNode_->MarkDirtyNode();
    }
    if (rootNode_->GetGeometryNode()->GetFrameOffset().GetY() != offset) {
        OffsetF newOffset = rootNode_->GetGeometryNode()->GetFrameOffset();
        newOffset.SetY(static_cast<float>(offset));
        rootNode_->GetGeometryNode()->SetMarginFrameOffset(newOffset);
        auto rootContext = rootNode_->GetRenderContext();
        rootContext->SyncGeometryProperties(RawPtr(rootNode_->GetGeometryNode()));
        RequestFrame();
    }
    if (isDensityChanged_) {
        rootNode_->GetGeometryNode()->ResetParentLayoutConstraint();
        rootNode_->MarkForceMeasure();
        isDensityChanged_ = false;
    }
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
    // For cross-platform build, flush tasks when first resize, speed up for fisrt frame.
    if (window_ && rootNode_->GetRenderContext() && !NearZero(width) && !NearZero(height)) {
        rootNode_->GetRenderContext()->SetBounds(0.0, 0.0, width, height);
        window_->FlushTasks();
        FlushVsync(GetTimeFromExternalTimer(), 0);
    }
#endif
}

void PipelineContext::UpdateSystemSafeArea(const SafeAreaInsets& systemSafeArea, bool checkSceneBoardWindow)
{
    if (checkSceneBoardWindow) {
        safeAreaManager_->UpdateScbSystemSafeArea(systemSafeArea);
        return;
    }
    CHECK_NULL_VOID(minPlatformVersion_ >= PLATFORM_VERSION_TEN);
    if (safeAreaManager_->UpdateSystemSafeArea(systemSafeArea)) {
        AnimateOnSafeAreaUpdate();
    }
}

void PipelineContext::UpdateCutoutSafeArea(const SafeAreaInsets& cutoutSafeArea, bool checkSceneBoardWindow)
{
    if (checkSceneBoardWindow) {
        safeAreaManager_->UpdateScbCutoutSafeArea(cutoutSafeArea);
        return;
    }
    CHECK_NULL_VOID(minPlatformVersion_ >= PLATFORM_VERSION_TEN);
    if (safeAreaManager_->UpdateCutoutSafeArea(cutoutSafeArea)) {
        AnimateOnSafeAreaUpdate();
    }
}

void PipelineContext::UpdateNavSafeArea(const SafeAreaInsets& navSafeArea, bool checkSceneBoardWindow)
{
    if (checkSceneBoardWindow) {
        safeAreaManager_->UpdateScbNavSafeArea(navSafeArea);
        return;
    }
    CHECK_NULL_VOID(minPlatformVersion_ >= PLATFORM_VERSION_TEN);
    if (safeAreaManager_->UpdateNavSafeArea(navSafeArea)) {
        AnimateOnSafeAreaUpdate();
    }
}

void PipelineContext::UpdateSystemSafeAreaWithoutAnimation(const SafeAreaInsets& systemSafeArea,
    bool checkSceneBoardWindow)
{
    if (checkSceneBoardWindow) {
        safeAreaManager_->UpdateScbSystemSafeArea(systemSafeArea);
        return;
    }
    CHECK_NULL_VOID(minPlatformVersion_ >= PLATFORM_VERSION_TEN);
    if (safeAreaManager_->UpdateSystemSafeArea(systemSafeArea)) {
        SyncSafeArea(SafeAreaSyncType::SYNC_TYPE_AVOID_AREA);
    }
}

void PipelineContext::UpdateCutoutSafeAreaWithoutAnimation(const SafeAreaInsets& cutoutSafeArea,
    bool checkSceneBoardWindow)
{
    if (checkSceneBoardWindow) {
        safeAreaManager_->UpdateScbCutoutSafeArea(cutoutSafeArea);
        return;
    }
    CHECK_NULL_VOID(minPlatformVersion_ >= PLATFORM_VERSION_TEN);
    if (safeAreaManager_->UpdateCutoutSafeArea(cutoutSafeArea)) {
        SyncSafeArea(SafeAreaSyncType::SYNC_TYPE_AVOID_AREA);
    }
}

void PipelineContext::UpdateNavSafeAreaWithoutAnimation(const SafeAreaInsets& navSafeArea,
    bool checkSceneBoardWindow)
{
    if (checkSceneBoardWindow) {
        safeAreaManager_->UpdateScbNavSafeArea(navSafeArea);
        return;
    }
    CHECK_NULL_VOID(minPlatformVersion_ >= PLATFORM_VERSION_TEN);
    if (safeAreaManager_->UpdateNavSafeArea(navSafeArea)) {
        SyncSafeArea(SafeAreaSyncType::SYNC_TYPE_AVOID_AREA);
    }
}

void PipelineContext::CheckAndUpdateKeyboardInset(float keyboardHeight)
{
    safeAreaManager_->UpdateKeyboardSafeArea(keyboardHeight);
}

void PipelineContext::UpdateOriginAvoidArea(const Rosen::AvoidArea& avoidArea, uint32_t type)
{
#ifdef WINDOW_SCENE_SUPPORTED
    CHECK_NULL_VOID(uiExtensionManager_);
    uiExtensionManager_->TransferOriginAvoidArea(avoidArea, type);
#endif
}

void PipelineContext::UpdateSizeChangeReason(
    WindowSizeChangeReason type, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
#ifdef WINDOW_SCENE_SUPPORTED
    CHECK_NULL_VOID(uiExtensionManager_);
    uiExtensionManager_->NotifySizeChangeReason(type, rsTransaction);
#endif
}

void PipelineContext::SetEnableKeyBoardAvoidMode(KeyBoardAvoidMode value)
{
    if (safeAreaManager_->SetKeyBoardAvoidMode(value)) {
        SyncSafeArea(SafeAreaSyncType::SYNC_TYPE_KEYBOARD);
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "keyboardAvoid Mode update:%{public}d", value);
    }
}

KeyBoardAvoidMode PipelineContext::GetEnableKeyBoardAvoidMode()
{
    return safeAreaManager_->GetKeyBoardAvoidMode();
}

bool PipelineContext::IsEnableKeyBoardAvoidMode()
{
    return safeAreaManager_->KeyboardSafeAreaEnabled();
}

void PipelineContext::SetIgnoreViewSafeArea(bool value)
{
    if (safeAreaManager_->SetIgnoreSafeArea(value)) {
        SyncSafeArea(SafeAreaSyncType::SYNC_TYPE_WINDOW_IGNORE);
    }
}

void PipelineContext::SetIsLayoutFullScreen(bool value)
{
    if (safeAreaManager_->SetIsFullScreen(value)) {
        SyncSafeArea(SafeAreaSyncType::SYNC_TYPE_WINDOW_IGNORE);
    }
}

void PipelineContext::SetIsNeedAvoidWindow(bool value)
{
    if (safeAreaManager_->SetIsNeedAvoidWindow(value)) {
        SyncSafeArea(SafeAreaSyncType::SYNC_TYPE_WINDOW_IGNORE);
    }
}

PipelineBase::SafeAreaInsets PipelineContext::GetSafeArea() const
{
    return safeAreaManager_->GetSafeArea();
}

PipelineBase::SafeAreaInsets PipelineContext::GetSafeAreaWithoutProcess() const
{
    return safeAreaManager_->GetSafeAreaWithoutProcess();
}

float PipelineContext::GetPageAvoidOffset()
{
    return safeAreaManager_->GetKeyboardOffset();
}

bool PipelineContext::CheckNeedAvoidInSubWindow()
{
    CHECK_NULL_RETURN(NearZero(GetPageAvoidOffset()), true);
    CHECK_NULL_RETURN(safeAreaManager_->KeyboardSafeAreaEnabled(), false);
    auto KeyboardInsetLength = safeAreaManager_->GetKeyboardInset().Length();
    return GreatNotEqual(KeyboardInsetLength, 0.0f);
}

void PipelineContext::SyncSafeArea(SafeAreaSyncType syncType)
{
    bool keyboardSafeArea =
        syncType == SafeAreaSyncType::SYNC_TYPE_KEYBOARD && !safeAreaManager_->KeyboardSafeAreaEnabled();
    CHECK_NULL_VOID(stageManager_);
    stageManager_->SyncPageSafeArea(keyboardSafeArea);
    SubwindowManager::GetInstance()->MarkDirtyDialogSafeArea();
    if (overlayManager_) {
        overlayManager_->MarkDirty(PROPERTY_UPDATE_MEASURE);
    }
    if (selectOverlayManager_) {
        selectOverlayManager_->MarkDirty(PROPERTY_UPDATE_MEASURE);
    }
    auto&& restoreNodes = safeAreaManager_->GetGeoRestoreNodes();
    for (auto&& wk : restoreNodes) {
        auto node = wk.Upgrade();
        if (node) {
            bool needMeasure = (syncType == SafeAreaSyncType::SYNC_TYPE_KEYBOARD && node->SelfExpansiveToKeyboard()) ||
                               (syncType == SafeAreaSyncType::SYNC_TYPE_AVOID_AREA ||
                                   syncType == SafeAreaSyncType::SYNC_TYPE_WINDOW_IGNORE);
            node->MarkDirtyNode(needMeasure ? PROPERTY_UPDATE_MEASURE : PROPERTY_UPDATE_LAYOUT);
        }
    }
}

void PipelineContext::DetachNode(RefPtr<UINode> uiNode)
{
    auto frameNode = DynamicCast<FrameNode>(uiNode);
    attachedNodeSet_.erase(WeakPtr(uiNode));
    CHECK_NULL_VOID(frameNode);

    RemoveStoredNode(frameNode->GetRestoreId());
    if (frameNode->IsPrivacySensitive()) {
        auto privacyManager = GetPrivacySensitiveManager();
        privacyManager->RemoveNode(AceType::WeakClaim(AceType::RawPtr(frameNode)));
    }

    if (!CheckThreadSafe()) {
        LOGW("DetachNode doesn't run on UI thread!");
    }
    dirtyPropertyNodes_.erase(frameNode);
    needRenderNode_.erase(WeakPtr<FrameNode>(frameNode));

    if (dirtyFocusNode_ == frameNode) {
        dirtyFocusNode_.Reset();
    }

    if (dirtyFocusScope_ == frameNode) {
        dirtyFocusScope_.Reset();
    }

    if (dirtyRequestFocusNode_ == frameNode) {
        dirtyRequestFocusNode_.Reset();
    }

    if (activeNode_ == frameNode) {
        activeNode_.Reset();
    }

    if (focusNode_ == frameNode) {
        focusNode_.Reset();
    }
}

void PipelineContext::OnVirtualKeyboardHeightChange(float keyboardHeight,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction, const float safeHeight, const bool supportAvoidance,
    bool forceChange)
{
    CHECK_RUN_ON(UI);
    // prevent repeated trigger with same keyboardHeight
    if (!forceChange && NearEqual(keyboardHeight, safeAreaManager_->GetKeyboardInset().Length())) {
        return;
    }

    ACE_FUNCTION_TRACE();
#ifdef ENABLE_ROSEN_BACKEND
    if (rsTransaction) {
        FlushMessages();
        rsTransaction->Begin();
    }
#endif

    if (supportAvoidance) {
        AvoidanceLogic(keyboardHeight, rsTransaction, safeHeight, supportAvoidance);
    } else {
        OriginalAvoidanceLogic(keyboardHeight, rsTransaction);
    }

#ifdef ENABLE_ROSEN_BACKEND
    if (rsTransaction) {
        rsTransaction->Commit();
    }
#endif
}

void PipelineContext::AvoidanceLogic(float keyboardHeight, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction,
    float safeHeight, const bool supportAvoidance)
{
    auto func = [this, keyboardHeight, safeHeight]() mutable {
        safeAreaManager_->UpdateKeyboardSafeArea(static_cast<uint32_t>(keyboardHeight));
        keyboardHeight += safeAreaManager_->GetSafeHeight();
        float positionY = 0.0f;
        float keyboardPosition = rootHeight_ - keyboardHeight;
        auto manager = DynamicCast<TextFieldManagerNG>(PipelineBase::GetTextFieldManager());
        float keyboardOffset = manager ? manager->GetClickPositionOffset() : safeAreaManager_->GetKeyboardOffset();
        if (manager) {
            positionY = static_cast<float>(manager->GetClickPosition().GetY()) - keyboardOffset;
        }
        auto bottomLen = safeAreaManager_->GetNavSafeArea().bottom_.IsValid() ?
            safeAreaManager_->GetNavSafeArea().bottom_.Length() : 0;
        if (manager->IsScrollableChild() && rootHeight_ - positionY - safeHeight - bottomLen < 0) {
            safeHeight = rootHeight_ - positionY - bottomLen;
        }
        if (NearZero(keyboardHeight)) {
            safeAreaManager_->UpdateKeyboardOffset(0.0f);
        } else if (LessOrEqual(positionY + safeHeight, rootHeight_ - keyboardHeight)) {
            safeAreaManager_->UpdateKeyboardOffset(0.0f);
        } else if (positionY + safeHeight > rootHeight_ - keyboardHeight) {
            safeAreaManager_->UpdateKeyboardOffset(-(positionY - rootHeight_ + keyboardHeight)- safeHeight);
        } else {
            safeAreaManager_->UpdateKeyboardOffset(0.0f);
        }
        safeAreaManager_->SetLastKeyboardPoistion(keyboardPosition);
        SyncSafeArea(SafeAreaSyncType::SYNC_TYPE_KEYBOARD);
        CHECK_NULL_VOID(manager);
        manager->AvoidKeyBoardInNavigation();
        // layout before scrolling textfield to safeArea, because of getting correct position
        FlushUITasks();
        bool scrollResult = manager->ScrollTextFieldToSafeArea();
        if (scrollResult) {
            FlushUITasks();
        }
        MarkDirtyOverlay();
        SubwindowManager::GetInstance()->FlushSubWindowUITasks(Container::CurrentId());

        TAG_LOGI(AceLogTag::ACE_KEYBOARD,
            "AvoidanceLogic keyboardHeight: %{public}f, positionY: %{public}f, safeHeight: %{public}f, "
            "rootHeight_ %{public}f final calculate keyboard offset is %{public}f",
            keyboardHeight, positionY, safeHeight, rootHeight_, safeAreaManager_->GetKeyboardOffset());
    };
    FlushUITasks();
    DoKeyboardAvoidAnimate(keyboardAnimationConfig_, keyboardHeight, func);
}

void PipelineContext::OriginalAvoidanceLogic(
    float keyboardHeight, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    auto func = [this, keyboardHeight, id = instanceId_]() mutable {
        ContainerScope scope(id);
        safeAreaManager_->UpdateKeyboardSafeArea(static_cast<uint32_t>(keyboardHeight));
        if (keyboardHeight > 0) {
            // add height of navigation bar
            keyboardHeight += safeAreaManager_->GetSystemSafeArea().bottom_.Length();
        }
        auto manager = DynamicCast<TextFieldManagerNG>(PipelineBase::GetTextFieldManager());
        float positionY = manager ? static_cast<float>(manager->GetClickPosition().GetY()) : 0.0f;
        float height = manager ? manager->GetHeight() : 0.0f;
        SizeF rootSize { static_cast<float>(rootWidth_), static_cast<float>(rootHeight_) };
        float keyboardOffset = manager ? manager->GetClickPositionOffset() : safeAreaManager_->GetKeyboardOffset();
        float positionYWithOffset = positionY - keyboardOffset;
        float offsetFix = (rootSize.Height() - positionYWithOffset) > 100.0f
                              ? keyboardHeight - (rootSize.Height() - positionYWithOffset) / 2.0f
                              : keyboardHeight;
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
        if (offsetFix > 0.0f && positionYWithOffset < offsetFix) {
            offsetFix = keyboardHeight - (rootSize.Height() - positionYWithOffset - height);
        }
#endif
        if (NearZero(keyboardHeight)) {
            safeAreaManager_->UpdateKeyboardOffset(0.0f);
        } else if (LessOrEqual(rootSize.Height() - positionYWithOffset - height, height) &&
                   LessOrEqual(rootSize.Height() - positionYWithOffset, keyboardHeight)) {
            safeAreaManager_->UpdateKeyboardOffset(-keyboardHeight);
        } else if (positionYWithOffset + height > (rootSize.Height() - keyboardHeight) && offsetFix > 0.0f) {
            safeAreaManager_->UpdateKeyboardOffset(-offsetFix);
        } else if ((positionYWithOffset + height > rootSize.Height() - keyboardHeight &&
                       positionYWithOffset < rootSize.Height() - keyboardHeight && height < keyboardHeight / 2.0f) &&
                   NearZero(rootNode_->GetGeometryNode()->GetFrameOffset().GetY())) {
            safeAreaManager_->UpdateKeyboardOffset(-height - offsetFix / 2.0f);
        } else {
            safeAreaManager_->UpdateKeyboardOffset(0.0f);
        }
        SyncSafeArea(SafeAreaSyncType::SYNC_TYPE_KEYBOARD);
        CHECK_NULL_VOID(manager);
        manager->AvoidKeyBoardInNavigation();
        // layout before scrolling textfield to safeArea, because of getting correct position
        FlushUITasks();
        bool scrollResult = manager->ScrollTextFieldToSafeArea();
        if (scrollResult) {
            FlushUITasks();
        }
        MarkDirtyOverlay();
        SubwindowManager::GetInstance()->FlushSubWindowUITasks(Container::CurrentId());
    };
    FlushUITasks();
    DoKeyboardAvoidAnimate(keyboardAnimationConfig_, keyboardHeight, func);
}

void PipelineContext::OnVirtualKeyboardHeightChange(float keyboardHeight, double positionY, double height,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction, bool forceChange)
{
    CHECK_RUN_ON(UI);
    // prevent repeated trigger with same keyboardHeight
    CHECK_NULL_VOID(safeAreaManager_);
    if (keyboardHeight >= rootHeight_) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Keyboard higher than whole rootrect, no need to avoid");
        return;
    }

    if (UsingCaretAvoidMode()) {
        OnCaretPositionChangeOrKeyboardHeightChange(keyboardHeight,
            positionY, height, rsTransaction, forceChange);
        return;
    }

    auto manager = DynamicCast<TextFieldManagerNG>(PipelineBase::GetTextFieldManager());
    CHECK_NULL_VOID(manager);
    if (!forceChange && NearEqual(keyboardHeight, safeAreaManager_->GetKeyboardInset().Length()) &&
        prevKeyboardAvoidMode_ == safeAreaManager_->GetKeyBoardAvoidMode() && manager->PrevHasTextFieldPattern()) {
        safeAreaManager_->UpdateKeyboardSafeArea(keyboardHeight);
        TAG_LOGD(
            AceLogTag::ACE_KEYBOARD, "KeyboardHeight as same as last time, don't need to calculate keyboardOffset");
        return;
    }

    if (!forceChange && (NearEqual(keyboardHeight + 1, safeAreaManager_->GetKeyboardInset().Length()) ||
        NearEqual(keyboardHeight - 1, safeAreaManager_->GetKeyboardInset().Length())) &&
        prevKeyboardAvoidMode_ == safeAreaManager_->GetKeyBoardAvoidMode() && manager->PrevHasTextFieldPattern()) {
        TAG_LOGI(
            AceLogTag::ACE_KEYBOARD, "Ignore ileagal keyboard height change");
        return;
    }

    if (manager->UsingCustomKeyboardAvoid()) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Using Custom Avoid Instead");
        return;
    }

    manager->UpdatePrevHasTextFieldPattern();
    prevKeyboardAvoidMode_ = safeAreaManager_->GetKeyBoardAvoidMode();

    ACE_FUNCTION_TRACE();
#ifdef ENABLE_ROSEN_BACKEND
    if (rsTransaction) {
        FlushMessages();
        rsTransaction->Begin();
    }
#endif

    auto weak = WeakClaim(this);
    auto func = [weak, keyboardHeight, positionY, height, manager]() mutable {
        auto context = weak.Upgrade();
        CHECK_NULL_VOID(context);
        context->SetIsLayouting(false);
        context->safeAreaManager_->UpdateKeyboardSafeArea(keyboardHeight);
        if (keyboardHeight > 0) {
            // add height of navigation bar
            keyboardHeight += context->safeAreaManager_->GetSystemSafeArea().bottom_.Length();
        }

        SizeF rootSize { static_cast<float>(context->rootWidth_), static_cast<float>(context->rootHeight_) };

        TAG_LOGI(AceLogTag::ACE_KEYBOARD,
            "origin positionY: %{public}f, height %{public}f", positionY, height);

        float keyboardOffset = manager ? manager->GetClickPositionOffset() :
            context->safeAreaManager_->GetKeyboardOffset();
        float currentPos = manager->GetClickPosition().GetY() - context->GetRootRect().GetOffset().GetY() -
            keyboardOffset;

        auto onFocusField = manager->GetOnFocusTextField().Upgrade();
        float adjust = 0.0f;
        if (onFocusField && onFocusField->GetHost() && onFocusField->GetHost()->GetGeometryNode()) {
            auto adjustRect = onFocusField->GetHost()->GetGeometryNode()->GetParentAdjust();
            adjust = adjustRect.Top();
        }
        currentPos += adjust;

        if (!onFocusField) {
            TAG_LOGI(AceLogTag::ACE_KEYBOARD, "use origin arg from the window");
        } else if (manager->GetIfFocusTextFieldIsInline()) {
            manager->GetInlineTextFieldAvoidPositionYAndHeight(positionY, height);
            positionY -= keyboardOffset;
        } else if (!NearEqual(positionY, currentPos) && !context->IsEnableKeyBoardAvoidMode()) {
            positionY = currentPos;
            height = manager->GetHeight();
        }

        if (rootSize.Height() - positionY - height < 0) {
            height = rootSize.Height() - positionY;
        }
        auto lastKeyboardOffset = context->safeAreaManager_->GetKeyboardOffset();
        float newKeyboardOffset = context->CalcNewKeyboardOffset(keyboardHeight,
            positionY, height, rootSize, onFocusField && manager->GetIfFocusTextFieldIsInline());
        newKeyboardOffset = round(newKeyboardOffset);
        if (NearZero(keyboardHeight) || LessOrEqual(newKeyboardOffset, lastKeyboardOffset) ||
            manager->GetOnFocusTextFieldId() == manager->GetLastAvoidFieldId()) {
            context->safeAreaManager_->UpdateKeyboardOffset(newKeyboardOffset);
        } else {
            TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Different field, Calculated offfset %{public}f is smaller than current"
                "keyboardOffset, so keep current keyboardOffset", newKeyboardOffset);
        }
        manager->SetLastAvoidFieldId(manager->GetOnFocusTextFieldId());

        TAG_LOGI(AceLogTag::ACE_KEYBOARD,
            "keyboardHeight: %{public}f, positionY: %{public}f, textHeight: %{public}f, "
            "rootSize.Height() %{public}f adjust: %{public}f final calculate keyboard offset is %{public}f",
            keyboardHeight, positionY, height, rootSize.Height(), adjust,
            context->safeAreaManager_->GetKeyboardOffset());
        context->SyncSafeArea(SafeAreaSyncType::SYNC_TYPE_KEYBOARD);
        manager->AvoidKeyBoardInNavigation();
        // layout before scrolling textfield to safeArea, because of getting correct position
        context->FlushUITasks();
        bool scrollResult = manager->ScrollTextFieldToSafeArea();
        if (scrollResult) {
            context->FlushUITasks();
        }
        context->MarkDirtyOverlay();
        SubwindowManager::GetInstance()->FlushSubWindowUITasks(Container::CurrentId());
    };
    FlushUITasks();
    FlushDirtyPropertyNodesWhenExist();
    SetIsLayouting(true);
    DoKeyboardAvoidAnimate(keyboardAnimationConfig_, keyboardHeight, func);

#ifdef ENABLE_ROSEN_BACKEND
    if (rsTransaction) {
        rsTransaction->Commit();
    }
#endif
}

void PipelineContext::MarkDirtyOverlay()
{
    CHECK_NULL_VOID(rootNode_);
    auto childNodes = rootNode_->GetChildren();
    for (auto child: childNodes) {
        if (child && child->GetTag() == V2::POPUP_ETS_TAG) {
            child->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        }
    }
}

void PipelineContext::FlushDirtyPropertyNodesWhenExist()
{
    if ((!IsDirtyLayoutNodesEmpty() || !dirtyPropertyNodes_.empty()) && !IsLayouting()) {
        FlushUITasks();
    }
}

bool PipelineContext::UsingCaretAvoidMode()
{
    CHECK_NULL_RETURN(safeAreaManager_, false);
    return safeAreaManager_->GetKeyBoardAvoidMode() == KeyBoardAvoidMode::OFFSET_WITH_CARET ||
        safeAreaManager_->GetKeyBoardAvoidMode() == KeyBoardAvoidMode::RESIZE_WITH_CARET;
}

void PipelineContext::OnCaretPositionChangeOrKeyboardHeightChange(
    float keyboardHeight, double positionY, double height,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction, bool forceChange)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(safeAreaManager_);
    auto manager = DynamicCast<TextFieldManagerNG>(PipelineBase::GetTextFieldManager());
    CHECK_NULL_VOID(manager);
    if (manager->UsingCustomKeyboardAvoid()) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Using Custom Avoid Instead");
        return;
    }
    manager->UpdatePrevHasTextFieldPattern();
    prevKeyboardAvoidMode_ = safeAreaManager_->GetKeyBoardAvoidMode();
    ACE_FUNCTION_TRACE();
#ifdef ENABLE_ROSEN_BACKEND
    if (rsTransaction) {
        FlushMessages();
        rsTransaction->Begin();
    }
#endif
    bool keyboardHeightChanged = NearEqual(keyboardHeight, safeAreaManager_->GetKeyboardInset().Length());
    auto weak = WeakClaim(this);
    auto func = [weak, keyboardHeight, positionY, height, keyboardHeightChanged]() mutable {
        auto context = weak.Upgrade();
        CHECK_NULL_VOID(context);
        context->DoKeyboardAvoidFunc(keyboardHeight, positionY, height, keyboardHeightChanged);
        context->MarkDirtyOverlay();
        SubwindowManager::GetInstance()->FlushSubWindowUITasks(Container::CurrentId());
    };
    FlushUITasks();
    SetIsLayouting(true);
    DoKeyboardAvoidAnimate(keyboardAnimationConfig_, keyboardHeight, func);

#ifdef ENABLE_ROSEN_BACKEND
    if (rsTransaction) {
        rsTransaction->Commit();
    }
#endif
}

void PipelineContext::DoKeyboardAvoidFunc(float keyboardHeight, double positionY, double height,
    bool keyboardHeightChanged)
{
    CHECK_NULL_VOID(safeAreaManager_);
    auto manager = DynamicCast<TextFieldManagerNG>(PipelineBase::GetTextFieldManager());
    CHECK_NULL_VOID(manager);
    SetIsLayouting(false);
    safeAreaManager_->UpdateKeyboardSafeArea(keyboardHeight);
    if (keyboardHeight > 0) {
        // add height of navigation bar
        keyboardHeight += safeAreaManager_->GetSystemSafeArea().bottom_.Length();
    }
    SizeF rootSize { static_cast<float>(rootWidth_), static_cast<float>(rootHeight_) };
    TAG_LOGI(AceLogTag::ACE_KEYBOARD, "origin positionY: %{public}f, height %{public}f", positionY, height);
    float caretPos = manager->GetFocusedNodeCaretRect().Top() - GetRootRect().GetOffset().GetY() -
        GetSafeAreaManager()->GetKeyboardOffset(true);
    auto onFocusField = manager->GetOnFocusTextField().Upgrade();
    float adjust = 0.0f;
    if (onFocusField && onFocusField->GetHost() && onFocusField->GetHost()->GetGeometryNode()) {
        adjust = onFocusField->GetHost()->GetGeometryNode()->GetParentAdjust().Top();
        positionY = caretPos;
        height = manager->GetHeight();
    }
    positionY += adjust;
    if (rootSize.Height() - positionY - height < 0 && manager->IsScrollableChild()) {
        height = rootSize.Height() - positionY;
    }
    auto lastKeyboardOffset = safeAreaManager_->GetKeyboardOffset(true);
    auto newKeyboardOffset = CalcNewKeyboardOffset(keyboardHeight, positionY, height, rootSize);
    if (NearZero(keyboardHeight) || LessOrEqual(newKeyboardOffset, lastKeyboardOffset) ||
        (manager->GetOnFocusTextFieldId() == manager->GetLastAvoidFieldId() && !keyboardHeightChanged)) {
        safeAreaManager_->UpdateKeyboardOffset(newKeyboardOffset);
    } else {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "calc offset %{public}f is smaller, keep current", newKeyboardOffset);
        manager->SetLastAvoidFieldId(manager->GetOnFocusTextFieldId());
        return;
    }
    manager->SetLastAvoidFieldId(manager->GetOnFocusTextFieldId());
    TAG_LOGI(AceLogTag::ACE_KEYBOARD,
        "keyboardHeight: %{public}f, caretPos: %{public}f, caretHeight: %{public}f, "
        "rootSize.Height() %{public}f adjust: %{public}f lastOffset: %{public}f, "
        "final calculate keyboard offset is %{public}f",
        keyboardHeight, positionY, height, rootSize.Height(), adjust, lastKeyboardOffset,
        safeAreaManager_->GetKeyboardOffset());
    SyncSafeArea(SafeAreaSyncType::SYNC_TYPE_KEYBOARD);
    manager->AvoidKeyBoardInNavigation();
    // layout before scrolling textfield to safeArea, because of getting correct position
    FlushUITasks();
    bool scrollResult = manager->ScrollTextFieldToSafeArea();
    if (scrollResult) {
        FlushUITasks();
    }
}

float  PipelineContext::CalcNewKeyboardOffset(float keyboardHeight, float positionY,
    float height, SizeF& rootSize, bool isInline)
{
    auto newKeyboardOffset = CalcAvoidOffset(keyboardHeight, positionY, height, rootSize);
    CHECK_NULL_RETURN(!isInline, newKeyboardOffset);
    CHECK_NULL_RETURN(safeAreaManager_, newKeyboardOffset);
    auto manager = DynamicCast<TextFieldManagerNG>(PipelineBase::GetTextFieldManager());
    CHECK_NULL_RETURN(manager, newKeyboardOffset);
    auto onFocusField = manager->GetOnFocusTextField().Upgrade();
    CHECK_NULL_RETURN(onFocusField, newKeyboardOffset);
    auto host = onFocusField->GetHost();
    CHECK_NULL_RETURN(host, newKeyboardOffset);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, newKeyboardOffset);
    auto paintOffset = host->GetPaintRectOffset(false, true);
    auto frameSize = geometryNode->GetFrameSize();
    auto offset = CalcAvoidOffset(keyboardHeight, paintOffset.GetY() - safeAreaManager_->GetKeyboardOffset(true),
        frameSize.Height() + CARET_AVOID_OFFSET.ConvertToPx(), rootSize);
    return std::max(offset, newKeyboardOffset);
}

float PipelineContext::CalcAvoidOffset(float keyboardHeight, float positionY,
    float height, SizeF rootSize)
{
    float offsetFix = (rootSize.Height() - positionY - height) < keyboardHeight
        ? keyboardHeight - (rootSize.Height() - positionY - height)
        : keyboardHeight;
    if (NearZero(keyboardHeight)) {
        return 0.0f;
    }
    if (positionY + height > (rootSize.Height() - keyboardHeight) && offsetFix > 0.0f) {
        return -offsetFix;
    }
    if (LessOrEqual(rootSize.Height() - positionY - height, height) &&
        LessOrEqual(rootSize.Height() - positionY, keyboardHeight)) {
        return -keyboardHeight;
    }
    if ((positionY + height > rootSize.Height() - keyboardHeight &&
        positionY < rootSize.Height() - keyboardHeight && height < keyboardHeight / 2.0f) &&
        NearZero(rootNode_->GetGeometryNode()->GetFrameOffset().GetY())) {
        return -height - offsetFix / 2.0f;
    }
    return 0.0f;
}

bool PipelineContext::OnBackPressed()
{
    CHECK_RUN_ON(PLATFORM);
    auto frontend = weakFrontend_.Upgrade();
    if (!frontend) {
        // return back.
        return false;
    }

    // If the tag of the last child of the rootnode is video, exit full screen.
    if (fullScreenManager_->OnBackPressed()) {
        LOGI("fullscreen component: video or web consumed backpressed event");
        return true;
    }

    // if has sharedTransition, back press will stop the sharedTransition
    if (sharedTransitionManager_ && sharedTransitionManager_->OnBackPressed()) {
        LOGI("sharedTransition consumed backpressed event");
        return true;
    }

    // if has popup, back press would hide popup and not trigger page back
    auto textfieldMgr = DynamicCast<TextFieldManagerNG>(PipelineBase::GetTextFieldManager());
    if (textfieldMgr) {
        auto lastRequestKeyboardNodeId = textfieldMgr->GetLastRequestKeyboardId();
        auto lastRequestKeyboardNode = DynamicCast<FrameNode>(
            ElementRegister::GetInstance()->GetUINodeById(lastRequestKeyboardNodeId));
        auto hasContainerModal = windowModal_ == WindowModal::CONTAINER_MODAL;
        if (lastRequestKeyboardNode && (lastRequestKeyboardNode->GetPageId() == -1 || (hasContainerModal &&
            lastRequestKeyboardNode->GetPageId() == 0)) && textfieldMgr->OnBackPressed()) {
            LOGI("textfield consumed backpressed event");
            return true;
        }
    }
    auto hasOverlay = false;
    taskExecutor_->PostSyncTask(
        [weakOverlay = AceType::WeakClaim(AceType::RawPtr(overlayManager_)),
            weakSelectOverlay = AceType::WeakClaim(AceType::RawPtr(selectOverlayManager_)), &hasOverlay]() {
            // Destroy behaviour of Select Overlay shouble be adjusted.
            auto overlay = weakOverlay.Upgrade();
            CHECK_NULL_VOID(overlay);
            auto selectOverlay = weakSelectOverlay.Upgrade();
            CHECK_NULL_VOID(selectOverlay);
            hasOverlay = selectOverlay->ResetSelectionAndDestroySelectOverlay(true);
            hasOverlay |= overlay->RemoveOverlay(true);
        },
        TaskExecutor::TaskType::UI, "ArkUIBackPressedRemoveOverlay");
    if (hasOverlay) {
        LOGI("Overlay consumed backpressed event");
        return true;
    }

    auto textfieldManager = DynamicCast<TextFieldManagerNG>(PipelineBase::GetTextFieldManager());
    if (textfieldManager && textfieldManager->OnBackPressed()) {
        LOGI("textfield consumed backpressed event");
        return true;
    }

    auto result = false;
    taskExecutor_->PostSyncTask(
        [weakFrontend = weakFrontend_, weakPipelineContext = WeakClaim(this), stageManager = stageManager_, &result]() {
            auto frontend = weakFrontend.Upgrade();
            if (!frontend) {
                result = false;
                return;
            }
            auto context = weakPipelineContext.Upgrade();
            if (!context) {
                result = false;
                return;
            }
            CHECK_NULL_VOID(stageManager);
            auto lastPage = stageManager->GetLastPage();
            CHECK_NULL_VOID(lastPage);
            bool isEntry = false;
            auto pagePattern = lastPage->GetPattern<NG::PagePattern>();
            if (pagePattern) {
                isEntry = pagePattern->IsNeedCallbackBackPressed();
            }
            auto navigationGroupNode =
                AceType::DynamicCast<NavigationGroupNode>(context->FindNavigationNodeToHandleBack(lastPage, isEntry));
            if (navigationGroupNode) {
                result = true;
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIBackPressedFindNavigationGroup");

    if (result) {
        // user accept
        LOGI("Navigation consumed backpressed event");
        return true;
    }

    taskExecutor_->PostSyncTask(
        [weakFrontend = weakFrontend_, weakPipelineContext = WeakClaim(this), &result]() {
            auto frontend = weakFrontend.Upgrade();
            if (!frontend) {
                result = false;
                return;
            }
            result = frontend->OnBackPressed();
        },
        TaskExecutor::TaskType::JS, "ArkUIBackPressed");

    if (result) {
        // user accept
        LOGI("router consumed backpressed event");
        return true;
    }
    return false;
}

RefPtr<FrameNode> PipelineContext::FindNavigationNodeToHandleBack(const RefPtr<UINode>& node, bool& isEntry)
{
    CHECK_NULL_RETURN(node, nullptr);
    const auto& children = node->GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        if (childNode && childNode->GetLayoutProperty()) {
            auto property = childNode->GetLayoutProperty();
            if (property->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::VISIBLE ||
                !childNode->IsActive()) {
                continue;
            }
        }
        if (childNode && childNode->GetTag() == V2::NAVIGATION_VIEW_ETS_TAG) {
            auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(childNode);
            auto topChild = navigationGroupNode->GetTopDestination();
            // find navigation from top destination
            auto targetNodeFromDestination = FindNavigationNodeToHandleBack(topChild, isEntry);
            if (targetNodeFromDestination) {
                return targetNodeFromDestination;
            }
            if (isEntry) {
                return nullptr;
            }
            targetNodeFromDestination = childNode;
            auto targetNavigation = AceType::DynamicCast<NavigationGroupNode>(targetNodeFromDestination);
            // check if the destination responds
            if (targetNavigation && targetNavigation->CheckCanHandleBack(isEntry)) {
                return targetNavigation;
            }
            if (isEntry) {
                return nullptr;
            }
            // if the destination does not responds, find navigation from navbar
            auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
            auto navigationLayoutProperty = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
            CHECK_NULL_RETURN(navigationLayoutProperty, nullptr);
            if (navigationLayoutProperty->GetHideNavBarValue(false)) {
                return nullptr;
            }
            auto targetNodeFromNavbar = FindNavigationNodeToHandleBack(navBarNode, isEntry);
            if (targetNodeFromNavbar) {
                return targetNodeFromNavbar;
            }
            return nullptr;
        }
        auto target = FindNavigationNodeToHandleBack(child, isEntry);
        if (target) {
            return target;
        }
        if (isEntry) {
            return nullptr;
        }
    }
    return nullptr;
}

bool PipelineContext::SetIsFocusActive(bool isFocusActive, FocusActiveReason reason, bool autoFocusInactive)
{
    auto focusManager = GetOrCreateFocusManager();
    CHECK_NULL_RETURN(focusManager, false);
    return focusManager->SetIsFocusActive(isFocusActive, reason, autoFocusInactive);
}

void PipelineContext::OnTouchEvent(const TouchEvent& point, bool isSubPipe)
{
    OnTouchEvent(point, rootNode_, isSubPipe);
}

void PipelineContext::OnMouseEvent(const MouseEvent& event)
{
    OnMouseEvent(event, rootNode_);
}

void PipelineContext::OnAxisEvent(const AxisEvent& event)
{
    OnAxisEvent(event, rootNode_);
}

void PipelineContext::OnTouchEvent(
    const TouchEvent& point, const RefPtr<FrameNode>& node, bool isSubPipe)
{
    CHECK_RUN_ON(UI);

    HandlePenHoverOut(point);
    auto gestureReferee = eventManager_->GetGestureRefereeNG(nullptr);
    CHECK_NULL_VOID(gestureReferee);
    if (gestureReferee->CheckSourceTypeChange(lastSourceType_)) {
        HandleTouchHoverOut(point);
    }

#ifdef UICAST_COMPONENT_SUPPORTED
    do {
        auto container = Container::Current();
        CHECK_NULL_BREAK(container);
        auto distributedUI = container->GetDistributedUI();
        CHECK_NULL_BREAK(distributedUI);
        if (distributedUI->IsSinkMode()) {
            distributedUI->BypassEvent(point, isSubPipe);
            return;
        }
    } while (false);
#endif

    auto formEventMgr = this->GetFormEventManager();
    SerializedGesture etsSerializedGesture;
    if (point.type != TouchType::DOWN && formEventMgr) {
        formEventMgr->HandleEtsCardTouchEvent(point, etsSerializedGesture);
    }

    if (point.type != TouchType::DOWN && !eventManager_->touchDelegatesMap_.empty()) {
        eventManager_->DelegateTouchEvent(point);
    }
    auto oriPoint = point;
    auto scalePoint = point.CreateScalePoint(GetViewScale());
    eventManager_->CheckDownEvent(scalePoint);
    ReportConfig config;
#if !defined(MAC_PLATFORM) && !defined(IOS_PLATFORM) && defined(OHOS_PLATFORM)
    auto container = Container::GetContainer(instanceId_);
    if (container) {
        config.isReportTid = container->GetUIContentType() == UIContentType::DYNAMIC_COMPONENT;
    }
    if (config.isReportTid) {
        config.tid = static_cast<uint64_t>(pthread_self());
    }
#endif
    ResSchedReport::GetInstance().OnTouchEvent(scalePoint, config);

    if (scalePoint.type != TouchType::MOVE && scalePoint.type != TouchType::PULL_MOVE &&
        scalePoint.type != TouchType::HOVER_MOVE) {
        eventManager_->GetEventTreeRecord(EventTreeType::TOUCH).AddTouchPoint(scalePoint);
#ifdef IS_RELEASE_VERSION
            TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW,
                "ITK Id:%{public}d, fId:%{public}d, T:%{public}d, I=%{public}d, "
                "M=%{public}d",
                scalePoint.touchEventId, scalePoint.id, (int)scalePoint.type, scalePoint.isInjected,
                scalePoint.isPrivacyMode);
#else
            TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW,
                "ITK Id:%{public}d, fId:%{public}d, x=%{public}.3f, y=%{public}.3f T=%{public}d, "
                "I=%{public}d",
                scalePoint.touchEventId, scalePoint.id, scalePoint.x, scalePoint.y, (int)scalePoint.type,
                scalePoint.isInjected);
#endif
    }

    if (scalePoint.type == TouchType::MOVE) {
        for (auto listenerItem : listenerVector_) {
            if (listenerItem) {
                listenerItem->OnTouchEvent();
            }
        }
    }

    eventManager_->SetInstanceId(GetInstanceId());
    if (scalePoint.type != TouchType::MOVE && historyPointsById_.find(scalePoint.id) != historyPointsById_.end()) {
        historyPointsById_.erase(scalePoint.id);
    }
    if (scalePoint.type == TouchType::DOWN) {
        SetUiDvsyncSwitch(false);
        CompensateTouchMoveEventBeforeDown();
        // Set focus state inactive while touch down event received
        SetIsFocusActive(false, FocusActiveReason::POINTER_EVENT);
        TouchRestrict touchRestrict { TouchRestrict::NONE };
        touchRestrict.sourceType = point.sourceType;
        touchRestrict.touchEvent = point;
        touchRestrict.inputEventType = InputEventType::TOUCH_SCREEN;

        eventManager_->TouchTest(scalePoint, node, touchRestrict, GetPluginEventOffset(), viewScale_, isSubPipe);
        if (!touchRestrict.childTouchTestList.empty()) {
            scalePoint.childTouchTestList = touchRestrict.childTouchTestList;
        }
        auto touchTestResults = eventManager_->touchTestResults_;
        if (StylusDetectorMgr::GetInstance()->IsNeedInterceptedTouchEvent(
            scalePoint, eventManager_->touchTestResults_)) {
            eventManager_->ClearTouchTestTargetForPenStylus(scalePoint);
            return;
        }

        if (formEventMgr) {
            formEventMgr->HandleEtsCardTouchEvent(oriPoint, etsSerializedGesture);
        }

        if (!eventManager_->touchDelegatesMap_.empty()) {
            eventManager_->DelegateTouchEvent(point);
        }
        if (etsSerializedGesture.data.size() != 0) {
            GestureGroup rebirth(GestureMode::Exclusive);
            rebirth.Deserialize(etsSerializedGesture.data.data());
            auto recognizer = rebirth.CreateRecognizer();
            if (recognizer) {
                recognizer->SetInnerFlag(true);
                recognizer->BeginReferee(scalePoint.id, true);
                std::list<RefPtr<NGGestureRecognizer>> combined;
                combined.emplace_back(recognizer);
                for (auto iter = touchTestResults[point.id].begin();
                    iter != touchTestResults[point.id].end(); iter++) {
                    auto outRecognizer = AceType::DynamicCast<NGGestureRecognizer>(*iter);
                    if (outRecognizer) {
                        combined.emplace_back(outRecognizer);
                        touchTestResults[point.id].erase(iter);
                        break;
                    }
                }
                auto exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(std::move(combined));
                exclusiveRecognizer->AttachFrameNode(node);
                exclusiveRecognizer->BeginReferee(scalePoint.id);
                touchTestResults[point.id].emplace_back(exclusiveRecognizer);
                eventManager_->touchTestResults_ = touchTestResults;
                eventManager_->SetInnerFlag(true);
            }
        }
        if (IsFormRenderExceptDynamicComponent() && touchTestResults.find(point.id) != touchTestResults.end()) {
            for (const auto& touchResult : touchTestResults[point.id]) {
                auto recognizer = AceType::DynamicCast<NG::RecognizerGroup>(touchResult);
                if (recognizer) {
                    auto gesture = recognizer->CreateGestureFromRecognizer();
                    if (gesture) {
                        serializedGesture_.data = std::vector<char>(gesture->SizeofMe());
                        gesture->Serialize(serializedGesture_.data.data());
                    }
                    break;
                }
            }
        }
        for (const auto& weakContext : touchPluginPipelineContext_) {
            auto pipelineContext = DynamicCast<OHOS::Ace::PipelineBase>(weakContext.Upgrade());
            if (!pipelineContext) {
                continue;
            }
            auto pluginPoint =
                point.UpdateScalePoint(viewScale_, static_cast<float>(pipelineContext->GetPluginEventOffset().GetX()),
                    static_cast<float>(pipelineContext->GetPluginEventOffset().GetY()), point.id);
            // eventManager_ instance Id may changed.
            pipelineContext->OnTouchEvent(pluginPoint, true);
        }

        // restore instance Id.
        eventManager_->SetInstanceId(GetInstanceId());
    }
    auto rootOffset = GetRootRect().GetOffset();
    eventManager_->HandleGlobalEventNG(scalePoint, selectOverlayManager_, rootOffset);

    if (isSubPipe) {
        return;
    }

    // Currently, SetupRootElement is executed later than InitializeCallback in AceContainer.
    // We need to check whether accessibilityManagerNG_ is created.
    if (accessibilityManagerNG_ != nullptr) {
        accessibilityManagerNG_->HandleAccessibilityHoverEvent(node, scalePoint);
    }

    if (scalePoint.type == TouchType::MOVE) {
        if (isEventsPassThrough_ || point.passThrough) {
            scalePoint.isPassThroughMode = true;
            eventManager_->FlushTouchEventsEnd({ scalePoint });
            eventManager_->DispatchTouchEvent(scalePoint);
            hasIdleTasks_ = true;
            if (postEventManager_) {
                postEventManager_->SetPassThroughResult(eventManager_->GetPassThroughResult());
            }
            return;
        }
        if (!eventManager_->GetInnerFlag() && formEventMgr) {
            auto mockPoint = point;
            mockPoint.type = TouchType::CANCEL;
            formEventMgr->HandleEtsCardTouchEvent(mockPoint, etsSerializedGesture);
            formEventMgr->RemoveEtsCardTouchEventCallback(mockPoint.id);
        }
        NotifyDragTouchEvent(scalePoint);
        touchEvents_.emplace_back(point);
        hasIdleTasks_ = true;
        RequestFrame();
        return;
    }

    if (scalePoint.type == TouchType::UP) {
        lastTouchTime_ = GetTimeFromExternalTimer();
        CompensateTouchMoveEvent(scalePoint);
        if (thpExtraMgr_ != nullptr) {
            const uint32_t delay = 800; // 800: ms
            taskExecutor_->RemoveTask(TaskExecutor::TaskType::UI, "NotifyResponseRegionChanged");
            auto task = [weak = WeakClaim(this)]() {
                auto pipeline = weak.Upgrade();
                CHECK_NULL_VOID(pipeline);
                pipeline->NotifyResponseRegionChanged(pipeline->GetRootElement());
            };
            taskExecutor_->PostDelayedTask(task, TaskExecutor::TaskType::UI, delay, "NotifyResponseRegionChanged");
        }
    }

    eventManager_->DispatchTouchEvent(scalePoint);

    if ((scalePoint.type == TouchType::UP) || (scalePoint.type == TouchType::CANCEL)) {
        // need to reset touchPluginPipelineContext_ for next touch down event.
        touchPluginPipelineContext_.clear();
        if (formEventMgr) {
            formEventMgr->RemoveEtsCardTouchEventCallback(point.id);
        }
        if (!eventManager_->touchDelegatesMap_.empty()) {
            eventManager_->UnregisterTouchDelegate(point.id);
        }
        if (scalePoint.type == TouchType::CANCEL) {
            dragEvents_.clear();
        }
        NotifyDragTouchEvent(scalePoint);
    }
    if (scalePoint.type != TouchType::MOVE) {
        auto lastDispatchTime = eventManager_->GetLastDispatchTime();
        lastDispatchTime.erase(scalePoint.id);
        eventManager_->SetLastDispatchTime(std::move(lastDispatchTime));
        eventManager_->EraseFingerId(scalePoint.id);
    }

    hasIdleTasks_ = true;
    RequestFrame();
    if (postEventManager_) {
        postEventManager_->SetPassThroughResult(eventManager_->GetPassThroughResult());
    }
}

void PipelineContext::CompensateTouchMoveEventBeforeDown()
{
    if (touchEvents_.empty()) {
        return;
    }
    std::unordered_map<int32_t, TouchEvent> historyPointsById;
    for (auto iter = touchEvents_.rbegin(); iter != touchEvents_.rend(); ++iter) {
        auto scalePoint = (*iter).CreateScalePoint(GetViewScale());
        historyPointsById.emplace(scalePoint.id, scalePoint);
        historyPointsById[scalePoint.id].history.insert(historyPointsById[scalePoint.id].history.begin(), scalePoint);
    }
    for (const auto& item : historyPointsById) {
        eventManager_->DispatchTouchEvent(item.second);
    }
    touchEvents_.clear();
}

bool PipelineContext::CompensateTouchMoveEventFromUnhandledEvents(const TouchEvent& event)
{
    std::vector<TouchEvent> history;
    if (!touchEvents_.empty()) {
        for (auto iter = touchEvents_.begin(); iter != touchEvents_.end();) {
            auto movePoint = (*iter).CreateScalePoint(GetViewScale());
            if (event.id == movePoint.id) {
                ShouldAddToHistory(history, event, movePoint);
                iter = touchEvents_.erase(iter);
            } else {
                auto& pointers = iter->pointers;
                for (auto pointerIter = pointers.begin(); pointerIter != pointers.end();) {
                    if (pointerIter->id == event.id) {
                        pointerIter = pointers.erase(pointerIter);
                    } else {
                        ++pointerIter;
                    }
                }
                ++iter;
            }
        }
        if (!history.empty()) {
            TouchEvent lastMoveEvent(history.back());
            lastMoveEvent.history.swap(history);
            eventManager_->SetLastMoveBeforeUp(event.sourceType == SourceType::MOUSE);
            eventManager_->DispatchTouchEvent(lastMoveEvent);
            eventManager_->SetLastMoveBeforeUp(false);
        } else {
            TAG_LOGD(AceLogTag::ACE_INPUTTRACKING,
                "Finger id: %{public}d, not found unhandled move event, compensate failed.", event.id);
        }
        return true;
    }
    return false;
}

void PipelineContext::CompensateTouchMoveEvent(const TouchEvent& event)
{
    if (event.type != TouchType::UP) {
        // If not up, no need to compensate touch move event.
        return;
    }
    if (!CompensateTouchMoveEventFromUnhandledEvents(event)) {
        // Compensate touch move event with all touch move Event before up has been handled.
        auto lastEventIter = eventManager_->GetIdToTouchPoint().find(event.id);
        if (lastEventIter != eventManager_->GetIdToTouchPoint().end()) {
            auto iter = eventManager_->GetLastDispatchTime().find(lastEventIter->first);
            if (iter != eventManager_->GetLastDispatchTime().end()) {
                ACE_SCOPED_TRACE("CompensateTouchMoveEvent last move event time: %s last dispatch time: %s",
                    std::to_string(static_cast<uint64_t>(lastEventIter->second.time.time_since_epoch().count()))
                        .c_str(),
                    std::to_string(iter->second).c_str());
                if (static_cast<uint64_t>(lastEventIter->second.time.time_since_epoch().count()) > iter->second) {
                    eventManager_->SetLastMoveBeforeUp(event.sourceType == SourceType::MOUSE);
                    eventManager_->DispatchTouchEvent(lastEventIter->second);
                    eventManager_->SetLastMoveBeforeUp(false);
                }
            }
        }
    }

    auto lastEventIter = eventManager_->GetIdToTouchPoint().find(event.id);
    if (lastEventIter != eventManager_->GetIdToTouchPoint().end()) {
        ACE_SCOPED_TRACE("Finger id: %d process last move event eventId: %d", lastEventIter->first,
            lastEventIter->second.touchEventId);
    }
}

void PipelineContext::OnSurfaceDensityChanged(double density)
{
    CHECK_RUN_ON(UI);
    if (!NearEqual(density, density_)) {
        isDensityChanged_ = true;
        isNeedReloadDensity_ = true;
    }
    density_ = density;
    if (!NearZero(viewScale_)) {
        dipScale_ = density_ / viewScale_;
    }
    if (isNeedReloadDensity_) {
        UIObserverHandler::GetInstance().NotifyDensityChange(density_);
        PipelineBase::OnSurfaceDensityChanged(density);
    }
}

bool PipelineContext::DumpPageViewData(const RefPtr<FrameNode>& node, RefPtr<ViewDataWrap> viewDataWrap,
    bool skipSubAutoFillContainer, bool needsRecordData)
{
    CHECK_NULL_RETURN(viewDataWrap, false);
    CHECK_NULL_RETURN(rootNode_, false);
    auto rootRect = GetRootRect();
    rootRect.SetOffset(rootNode_->GetPositionToScreenWithTransform());
    viewDataWrap->SetPageRect(rootRect);
    RefPtr<FrameNode> pageNode = nullptr;
    RefPtr<FrameNode> dumpNode = nullptr;
    if (node == nullptr) {
        if (stageManager_) {
            pageNode = stageManager_->GetLastPage();
            dumpNode = pageNode;
        }
    } else {
        pageNode = node->GetPageNode();
        dumpNode = node;
    }
    CHECK_NULL_RETURN(dumpNode, false);
    dumpNode->DumpViewDataPageNodes(viewDataWrap, skipSubAutoFillContainer, needsRecordData);
    // The page path may not be obtained in the container, use the node tag as the page path.
    if (node) {
        const auto& nodeTag = node->GetTag();
        if (nodeTag == V2::DIALOG_ETS_TAG || nodeTag == V2::SHEET_PAGE_TAG ||
            nodeTag == V2::MODAL_PAGE_TAG || nodeTag == V2::POPUP_ETS_TAG) {
            viewDataWrap->SetPageUrl(nodeTag);
            return true;
        }
    }
    CHECK_NULL_RETURN(pageNode, false);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    auto pageInfo = pagePattern->GetPageInfo();
    CHECK_NULL_RETURN(pageInfo, false);
    viewDataWrap->SetPageUrl(pageInfo->GetPageUrl());
    return true;
}

bool PipelineContext::CheckNeedAutoSave()
{
    CHECK_NULL_RETURN(stageManager_, false);
    auto pageNode = stageManager_->GetLastPage();
    CHECK_NULL_RETURN(pageNode, false);
    return pageNode->NeedRequestAutoSave();
}

bool PipelineContext::CheckOverlayFocus()
{
    CHECK_NULL_RETURN(overlayManager_, false);
    auto overlayNode = overlayManager_->GetOverlayNode();
    CHECK_NULL_RETURN(overlayNode, false);
    return overlayNode->GetFocusHub() && overlayNode->GetFocusHub()->IsCurrentFocus();
}

void PipelineContext::NotifyFillRequestSuccess(AceAutoFillType autoFillType, RefPtr<ViewDataWrap> viewDataWrap)
{
    CHECK_NULL_VOID(viewDataWrap);
    auto pageNodeInfoWraps = viewDataWrap->GetPageNodeInfoWraps();
    for (const auto& item : pageNodeInfoWraps) {
        if (item == nullptr) {
            continue;
        }
        auto frameNode = DynamicCast<FrameNode>(ElementRegister::GetInstance()->GetUINodeById(item->GetId()));
        if (frameNode == nullptr) {
            TAG_LOGW(AceLogTag::ACE_AUTO_FILL, "frameNode is not found, id=%{public}d", item->GetId());
            continue;
        }
        frameNode->NotifyFillRequestSuccess(viewDataWrap, item, autoFillType);
    }
}

void PipelineContext::NotifyFillRequestFailed(RefPtr<FrameNode> node, int32_t errCode,
    const std::string& fillContent, bool isPopup)
{
    CHECK_NULL_VOID(node);
    node->NotifyFillRequestFailed(errCode, fillContent, isPopup);
}

void PipelineContext::DumpFocus(bool hasJson) const
{
    auto rootFocusHub = rootNode_->GetFocusHub();
    CHECK_NULL_VOID(rootFocusHub);
    rootFocusHub->DumpFocusTree(0, hasJson);
    if (hasJson) {
        DumpLog::GetInstance().PrintEndDumpInfoNG();
    }
}

void PipelineContext::DumpInspector(const std::vector<std::string>& params, bool hasJson) const
{
    auto accessibilityManager = GetAccessibilityManager();
    if (accessibilityManager) {
        accessibilityManager->OnDumpInfoNG(params, windowId_, hasJson);
        if (hasJson) {
            DumpLog::GetInstance().PrintEndDumpInfoNG();
        }
    }
}

void PipelineContext::DumpData(
    const RefPtr<FrameNode>& node, const std::vector<std::string>& params, bool hasJson) const
{
    CHECK_NULL_VOID(node);
    int32_t depth = 0;
    if (IsDynamicRender()) {
        depth = GetDepthFromParams(params);
    }
    uint32_t used_id_flag = hasJson ? USED_JSON_PARAM : USED_ID_FIND_FLAG;
    auto paramSize = params.size();
    auto container = Container::GetContainer(instanceId_);
    if (container && (container->IsUIExtensionWindow() || container->IsFormRender())) {
        paramSize =
            static_cast<uint32_t>(std::distance(params.begin(), std::find(params.begin(), params.end(), PID_FLAG)));
    }
    if (paramSize < used_id_flag) {
        node->DumpTree(depth, hasJson);
        if (hasJson) {
            DumpLog::GetInstance().PrintEndDumpInfoNG(true);
        }
        DumpLog::GetInstance().OutPutBySize();
    }
    if (paramSize == used_id_flag && !node->DumpTreeById(depth, params[PARAM_NUM], hasJson)) {
        DumpLog::GetInstance().Print(
            "There is no id matching the ID in the parameter, please check whether the id is correct.");
    }
}

void PipelineContext::DumpElement(const std::vector<std::string>& params, bool hasJson) const
{
    if (params.size() > 1 && params[1] == "-lastpage") {
        auto lastPage = stageManager_->GetLastPage();
        DumpData(lastPage, params, hasJson);
    } else {
        DumpData(rootNode_, params, hasJson);
    }
}

void PipelineContext::DumpResLoadError() const
{
    ResourceManager::GetInstance().DumpResLoadError();
}

bool PipelineContext::OnDumpInfo(const std::vector<std::string>& params) const
{
    bool hasJson = params.back() == "-json";
    int32_t depth = 0;
    if (IsDynamicRender()) {
        depth = GetDepthFromParams(params);
    }

    if (window_) {
        DumpLog::GetInstance().Print(1, "LastRequestVsyncTime: " + std::to_string(window_->GetLastRequestVsyncTime()));
#ifdef ENABLE_ROSEN_BACKEND
        auto rsUIDirector = window_->GetRSUIDirector();
        if (rsUIDirector) {
            DumpLog::GetInstance().Print(1, "transactionFlags: [" + std::to_string(getpid()) + "," +
                std::to_string(rsUIDirector->GetIndex()) + "]");
        }
#endif
    }
    DumpLog::GetInstance().Print(1, "last vsyncId: " + std::to_string(GetFrameCount()));
    DumpLog::GetInstance().Print(1, "finishCount:" + GetUnexecutedFinishCount());
    if (params[0] == "-element") {
        DumpElement(params, hasJson);
    } else if (params[0] == "-navigation") {
        auto navigationDumpMgr = GetNavigationManager();
        if (navigationDumpMgr) {
            navigationDumpMgr->OnDumpInfo();
        }
    } else if (params[0] == "-focus") {
        DumpFocus(hasJson);
    } else if (params[0] == "-focuswindowscene") {
        auto windowSceneNode = GetFocusedWindowSceneNode();
        auto windowSceneFocusHub = windowSceneNode ? windowSceneNode->GetFocusHub() : nullptr;
        if (windowSceneFocusHub) {
            windowSceneFocusHub->DumpFocusTree(0);
        }
    } else if (params[0] == "-focusmanager") {
        if (focusManager_) {
            focusManager_->DumpFocusManager();
        }
    } else if (params[0] == "-accessibility") {
        auto accessibilityManager = GetAccessibilityManager();
        if (accessibilityManager) {
            accessibilityManager->OnDumpInfoNG(params, windowId_);
        }
    } else if (params[0] == "-inspector") {
        DumpInspector(params, hasJson);
    } else if (params[0] == "-rotation" && params.size() >= 2) {
    } else if (params[0] == "-animationscale" && params.size() >= 2) {
    } else if (params[0] == "-velocityscale" && params.size() >= 2) {
    } else if (params[0] == "-scrollfriction" && params.size() >= 2) {
    } else if (params[0] == "-threadstuck" && params.size() >= 3) {
    } else if (params[0] == "-pipeline") {
        DumpPipelineInfo();
    } else if (params[0] == "-jsdump") {
        std::vector<std::string> jsParams;
        if (params.begin() != params.end()) {
            jsParams = std::vector<std::string>(params.begin() + 1, params.end());
        }

        auto stageNode = stageManager_->GetStageNode();
        CHECK_NULL_RETURN(stageNode, false);
        auto children = stageNode->GetChildren();
        for (const auto& pageNode : children) {
            auto frameNode = AceType::DynamicCast<FrameNode>(pageNode);
            CHECK_NULL_RETURN(frameNode, false);
            auto pagePattern = frameNode->GetPattern<PagePattern>();
            CHECK_NULL_RETURN(pagePattern, false);
            pagePattern->FireDumpListener(jsParams);
        }
    } else if (params[0] == "-event") {
        if (eventManager_) {
            eventManager_->DumpEventWithCount(params, EventTreeType::TOUCH, hasJson);
        }
        DumpUIExt();
    } else if (params[0] == "-postevent") {
        if (eventManager_) {
            eventManager_->DumpEvent(EventTreeType::POST_EVENT, hasJson);
        }
    } else if (params[0] == "-imagecache") {
        if (imageCache_) {
            imageCache_->DumpCacheInfo();
        }
        DumpUIExt();
    } else if (params[0] == "-imagefilecache") {
        ImageFileCache::GetInstance().DumpCacheInfo();
        DumpUIExt();
    } else if (params[0] == "-allelements") {
        AceEngine::Get().NotifyContainers([](const RefPtr<Container>& container) {
            auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            auto rootNode = pipeline->GetRootElement();
            if (rootNode) {
                DumpLog::GetInstance().Print(0, "ContainerId: " + std::to_string(Container::CurrentId()));
                rootNode->DumpTree(0);
                DumpLog::GetInstance().OutPutBySize();
            }
        });
    } else if (params[0] == "-default") {
        rootNode_->DumpTree(depth);
        DumpLog::GetInstance().OutPutDefault();
    } else if (params[0] == "-overlay") {
        if (overlayManager_) {
            overlayManager_->DumpOverlayInfo();
        }
    } else if (params[0] == "--stylus") {
        StylusDetectorDefault::GetInstance()->ExecuteCommand(params);
    } else if (params[0] == "-simplify") {
        LOGI("start collect simplify dump info");
        rootNode_->DumpTree(0);
        DumpLog::GetInstance().OutPutByCompress();
        LOGI("end collect simplify dump info");
    } else if (params[0] == "-resource") {
        DumpResLoadError();
    } else if (params[0] == "-start") {
        OnDumpRecorderStart(params);
    } else if (params[0] == "-end") {
        DumpRecorder::GetInstance().Stop();
    } else if (params[0] == "-injection" && params.size() > PARAM_NUM) {
#ifndef IS_RELEASE_VERSION
        OnDumpInjection(params);
    } else if (params[0] == "-injectionkeycode" && params.size() > PARAM_NUM) {
        UiSessionManager::GetInstance()->SendCommand(params[1]);
#endif
    }
    return true;
}

void PipelineContext::OnDumpRecorderStart(const std::vector<std::string>& params) const
{
    int32_t recordTime = DEFAULT_RECORD_SECOND;
    if (static_cast<uint32_t>(sizeof(params)) <= 1) {
        return;
    }
    int32_t inputTime = StringUtils::StringToInt(params[1]);
    if (inputTime > 0) {
        recordTime = inputTime;
    }
    recordTime = std::min(recordTime, MAX_RECORD_SECOND);
    int64_t startTime = GetCurrentTimestamp();
    auto taskExecutor = GetTaskExecutor();
    std::function<bool()> dumpFunc = [startTime, recordTime, weakRoot = WeakClaim(RawPtr(rootNode_))]() {
        int64_t currentTime = GetCurrentTimestamp();
        if ((currentTime - startTime) >= recordTime * SECOND_TO_MILLISEC) {
            return false;
        }
        auto root = weakRoot.Upgrade();
        CHECK_NULL_RETURN(root, false);
        auto jsonRoot = JsonUtil::Create(true);
        root->DumpTreeJsonForDiff(jsonRoot);
        DumpRecorder::GetInstance().Record(currentTime, std::move(jsonRoot));
        return true;
    };
    DumpRecorder::GetInstance().Start(std::move(dumpFunc));
}

void PipelineContext::TriggerFrameDumpFuncIfExist() const
{
    auto frameDumpFunc = DumpRecorder::GetInstance().GetFrameDumpFunc();
    CHECK_NULL_VOID(frameDumpFunc);
    if (!frameDumpFunc()) {
        DumpRecorder::GetInstance().Stop();
    }
}

void PipelineContext::DumpUIExt() const
{
#ifdef WINDOW_SCENE_SUPPORTED
    if (uiExtensionManager_) {
        uiExtensionManager_->DumpUIExt();
    }
#endif
}

FrameInfo* PipelineContext::GetCurrentFrameInfo(uint64_t recvTime, uint64_t timeStamp)
{
    if (SystemProperties::GetDumpFrameCount() == 0) {
        return nullptr;
    }
    if (dumpFrameInfos_.size() >= SystemProperties::GetDumpFrameCount()) {
        dumpFrameInfos_.pop_front();
    }

    dumpFrameInfos_.push_back({ .frameRecvTime_ = recvTime, .frameTimeStamp_ = timeStamp });
    return &dumpFrameInfos_.back();
}

void PipelineContext::DumpPipelineInfo() const
{
    DumpLog::GetInstance().Print("PipelineInfo:");
    if (window_) {
        DumpLog::GetInstance().Print(1, "DisplayRefreshRate: " + std::to_string(window_->GetRefreshRate()));
        DumpLog::GetInstance().Print(1, "LastRequestVsyncTime: " + std::to_string(window_->GetLastRequestVsyncTime()));
        DumpLog::GetInstance().Print(1, "NowTime: " + std::to_string(GetSysTimestamp()));
    }
    if (!dumpFrameInfos_.empty()) {
        DumpLog::GetInstance().Print("==================================FrameTask==================================");
        for (const auto& info : dumpFrameInfos_) {
            DumpLog::GetInstance().Print("Task: " + info.GetTimeInfo());
            DumpLog::GetInstance().Print(1, "LayoutTask:");
            for (const auto& layout : info.layoutInfos_) {
                DumpLog::GetInstance().Print(2, layout.ToString());
            }
            DumpLog::GetInstance().Print(1, "RenderTask:");
            for (const auto& layout : info.renderInfos_) {
                DumpLog::GetInstance().Print(2, layout.ToString());
            }
            DumpLog::GetInstance().Print(
                "==================================FrameTask==================================");
        }
    }
}

void PipelineContext::CollectTouchEventsBeforeVsync(std::list<TouchEvent>& touchEvents)
{
    auto targetTimeStamp = compensationValue_ > 0 ? GetVsyncTime() - compensationValue_ : GetVsyncTime();
    if (touchEvents_.size() >= 40) { // TP:140Hz, vsync:30Hz, Fingers:10
        TAG_LOGW(AceLogTag::ACE_INPUTTRACKING,
            "Too many touch events in current vsync.(vsync: %{public}" PRIu64 ", eventsCnt: %{public}u)",
            GetVsyncTime(), static_cast<uint32_t>(touchEvents_.size()));
    }
    for (auto iter = touchEvents_.begin(); iter != touchEvents_.end();) {
        auto timeStamp = std::chrono::duration_cast<std::chrono::nanoseconds>(iter->time.time_since_epoch()).count();
        if (targetTimeStamp < static_cast<uint64_t>(timeStamp)) {
            iter++;
            continue;
        }
        touchEvents.emplace_back(*iter);
        iter = touchEvents_.erase(iter);
    }
}

void PipelineContext::FlushTouchEvents()
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(rootNode_);
    {
        std::list<TouchEvent> touchEvents;
        CollectTouchEventsBeforeVsync(touchEvents);
        if (touchEvents.empty()) {
            canUseLongPredictTask_ = true;
            return;
        }
        canUseLongPredictTask_ = false;
        eventManager_->FlushTouchEventsBegin(touchEvents_);
        std::unordered_map<int, TouchEvent> idToTouchPoints;
        if (touchAccelarate_) {
            AccelerateConsumeTouchEvents(touchEvents, idToTouchPoints);
        } else {
            ConsumeTouchEvents(touchEvents, idToTouchPoints);
        }
        auto maxSize = touchEvents.size();
        for (auto iter = touchEvents.rbegin(); iter != touchEvents.rend(); ++iter) {
            maxSize--;
            if (maxSize == 0) {
                eventManager_->FlushTouchEventsEnd(touchEvents);
            }
            eventManager_->DispatchTouchEvent(*iter);
        }
        eventManager_->SetIdToTouchPoint(std::move(idToTouchPoints));
    }
}


void PipelineContext::SetBackgroundColorModeUpdated(bool backgroundColorModeUpdated)
{
    backgroundColorModeUpdated_ = backgroundColorModeUpdated;
}

void PipelineContext::ConsumeTouchEvents(
    std::list<TouchEvent>& touchEvents, std::unordered_map<int, TouchEvent>& idToTouchPoints)
{
    bool needInterpolation = true;
    std::unordered_map<int32_t, TouchEvent> newIdTouchPoints;
    for (auto iter = touchEvents.rbegin(); iter != touchEvents.rend(); ++iter) {
        auto scalePoint = (*iter).CreateScalePoint(GetViewScale());
        idToTouchPoints.emplace(scalePoint.id, scalePoint);
        idToTouchPoints[scalePoint.id].history.insert(idToTouchPoints[scalePoint.id].history.begin(), scalePoint);
        needInterpolation = iter->type != TouchType::MOVE ? false : true;
    }
    if (!NeedTouchInterpolation()) {
        needInterpolation = false;
    }
    if (needInterpolation) {
        auto targetTimeStamp = resampleTimeStamp_;
        for (const auto& idIter : idToTouchPoints) {
            auto stamp =
                std::chrono::duration_cast<std::chrono::nanoseconds>(idIter.second.time.time_since_epoch()).count();
            if (targetTimeStamp > static_cast<uint64_t>(stamp)) {
                continue;
            }
            TouchEvent newTouchEvent;
            if (eventManager_->GetResampleTouchEvent(
                    historyPointsById_[idIter.first], idIter.second.history, targetTimeStamp, newTouchEvent)) {
                newIdTouchPoints[idIter.first] = newTouchEvent;
            }
            historyPointsById_[idIter.first] = idIter.second.history;
        }
    }
    touchEvents.clear();
    for (const auto& iter : idToTouchPoints) {
        auto lastDispatchTime = eventManager_->GetLastDispatchTime();
        lastDispatchTime[iter.first] = GetVsyncTime() - compensationValue_;
        eventManager_->SetLastDispatchTime(std::move(lastDispatchTime));
        auto it = newIdTouchPoints.find(iter.first);
        if (it != newIdTouchPoints.end()) {
            touchEvents.emplace_back(it->second);
        } else {
            touchEvents.emplace_back(iter.second);
        }
    }
}

uint64_t PipelineContext::GetResampleStamp() const
{
    constexpr uint64_t RESAMPLE_LANTENCY = 5 * ONE_MS_IN_NS;
    uint64_t vsyncTime = GetVsyncTime();
    return std::min(vsyncTime - RESAMPLE_LANTENCY, vsyncTime - compensationValue_);
}

void PipelineContext::AccelerateConsumeTouchEvents(
    std::list<TouchEvent>& touchEvents, std::unordered_map<int, TouchEvent>& idToTouchPoints)
{
    // consume touchEvents and generate idToTouchPoints.
    for (auto iter = touchEvents.rbegin(); iter != touchEvents.rend(); ++iter) {
        auto scalePoint = iter->CreateScalePoint(GetViewScale());
        idToTouchPoints.emplace(scalePoint.id, scalePoint);
        auto& history = idToTouchPoints[scalePoint.id].history;
        history.emplace(history.begin(), std::move(scalePoint));
    }
    bool needInterpolation = (touchEvents.front().type == TouchType::MOVE) && NeedTouchInterpolation();
    auto& lastDispatchTime = eventManager_->GetLastDispatchTime();
    auto curVsyncArrivalTime = GetVsyncTime() - compensationValue_;
    touchEvents.clear();

    // resample and generate event to dispatch in touchEvents
    if (needInterpolation) {
        auto targetTimeStamp = GetResampleStamp();
        for (const auto& idIter : idToTouchPoints) {
            TouchEvent newTouchEvent;
            eventManager_->TryResampleTouchEvent(
                historyPointsById_[idIter.first], idIter.second.history, targetTimeStamp, newTouchEvent);
            lastDispatchTime[idIter.first] = curVsyncArrivalTime;
            touchEvents.emplace_back(newTouchEvent);
        }
    } else {
        for (const auto& idIter : idToTouchPoints) {
            lastDispatchTime[idIter.first] = curVsyncArrivalTime;
            touchEvents.emplace_back(idIter.second);
        }
    }
}

void PipelineContext::OnAccessibilityHoverEvent(const TouchEvent& point, const RefPtr<NG::FrameNode>& node)
{
    CHECK_RUN_ON(UI);
    auto scaleEvent = point.CreateScalePoint(viewScale_);
    if (scaleEvent.type != TouchType::HOVER_MOVE) {
#ifdef IS_RELEASE_VERSION
        TAG_LOGI(AceLogTag::ACE_INPUTTRACKING,
            "OnAccessibilityHoverEvent event id:%{public}d, fingerId:%{public}d,"
            "type=%{public}d, "
            "inject=%{public}d",
            scaleEvent.touchEventId, scaleEvent.id, (int)scaleEvent.type, scaleEvent.isInjected);
#else
        TAG_LOGI(AceLogTag::ACE_INPUTTRACKING,
            "OnAccessibilityHoverEvent event id:%{public}d, fingerId:%{public}d, x=%{public}f y=%{public}f "
            "type=%{public}d, "
            "inject=%{public}d",
            scaleEvent.touchEventId, scaleEvent.id, scaleEvent.x, scaleEvent.y, (int)scaleEvent.type,
            scaleEvent.isInjected);
#endif
    }
    auto targerNode = node ? node : rootNode_;
    if (accessibilityManagerNG_ != nullptr) {
        accessibilityManagerNG_->HandleAccessibilityHoverEvent(targerNode, scaleEvent);
    }
    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = scaleEvent.sourceType;
    // use mouse to collect accessibility hover target
    touchRestrict.hitTestType = SourceType::MOUSE;
    touchRestrict.inputEventType = InputEventType::TOUCH_SCREEN;
    touchRestrict.touchEvent.type = TouchType::HOVER_ENTER;
    eventManager_->AccessibilityHoverTest(scaleEvent, targerNode, touchRestrict);
    eventManager_->DispatchAccessibilityHoverEventNG(scaleEvent);
    RequestFrame();
}

void PipelineContext::OnPenHoverEvent(const TouchEvent& point, const RefPtr<NG::FrameNode>& node)
{
    CHECK_RUN_ON(UI);
    auto scaleEvent = point.CreateScalePoint(viewScale_);
    if (scaleEvent.type != TouchType::MOVE) {
        TAG_LOGI(AceLogTag::ACE_INPUTTRACKING,
            "OnPenHoverEvent event id:%{public}d, fingerId:%{public}d "
            "type=%{public}d, "
            "inject=%{public}d",
            scaleEvent.touchEventId, scaleEvent.id, (int)scaleEvent.type,
            scaleEvent.isInjected);
    }

    auto targerNode = node ? node : rootNode_;
    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = scaleEvent.sourceType;
    touchRestrict.touchEvent.sourceTool = scaleEvent.sourceTool;
    touchRestrict.touchEvent.type = scaleEvent.type;
    touchRestrict.touchEvent.force = scaleEvent.force;

    // use mouse to collect pen hover target
    touchRestrict.hitTestType = SourceType::MOUSE;
    touchRestrict.inputEventType = InputEventType::TOUCH_SCREEN;
    eventManager_->PenHoverTest(scaleEvent, targerNode, touchRestrict);
    eventManager_->DispatchPenHoverEventNG(scaleEvent);
    eventManager_->DispatchPenHoverMoveEventNG(scaleEvent);
    RequestFrame();
}

void PipelineContext::HandlePenHoverOut(const TouchEvent& point)
{
    if (point.sourceTool != SourceTool::PEN || point.type != TouchType::DOWN || NearZero(point.force)) {
        return;
    }

    CHECK_RUN_ON(UI);
    auto oriPoint = point;
    oriPoint.type = TouchType::PROXIMITY_OUT;

    TouchTestResult testResult;
    eventManager_->UpdatePenHoverNode(oriPoint, testResult);
    eventManager_->DispatchPenHoverEventNG(oriPoint);
}

void PipelineContext::UpdateLastMoveEvent(const MouseEvent& event)
{
    if (!lastMouseEvent_) {
        lastMouseEvent_ = std::make_unique<MouseEvent>();
    }
    if (event.mockFlushEvent && event.action == MouseAction::WINDOW_LEAVE) {
        lastMouseEvent_->isMockWindowTransFlag = true;
    }
    lastMouseEvent_->x = event.x;
    lastMouseEvent_->y = event.y;
    lastMouseEvent_->button = event.button;
    lastMouseEvent_->action = event.action;
    lastMouseEvent_->sourceType = event.sourceType;
    lastMouseEvent_->time = event.time;
    lastMouseEvent_->touchEventId = event.touchEventId;
    lastMouseEvent_->mockFlushEvent = event.mockFlushEvent;
    lastMouseEvent_->pointerEvent = event.pointerEvent;
    lastMouseEvent_->deviceId = event.deviceId;
    lastMouseEvent_->sourceTool = event.sourceTool;
    lastSourceType_ = event.sourceType;
}

void PipelineContext::OnMouseEvent(const MouseEvent& event, const RefPtr<FrameNode>& node)
{
    CHECK_RUN_ON(UI);
    UpdateLastMoveEvent(event);
    lastMouseEvent_->node = node;
    if (event.action == MouseAction::PRESS || event.action == MouseAction::RELEASE) {
#ifdef IS_RELEASE_VERSION
        TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW,
            "InputTracking id:%{public}d, mouseId:%{public}d, type=%{public}d, button=%{public}d, inject=%{public}d",
            event.touchEventId, event.id, (int)event.action, (int)event.button, event.isInjected);
#else
        TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW,
            "InputTracking id:%{public}d, mouseId:%{public}d, x=%{public}.3f, y=%{public}.3f, z=%{public}.3f, "
            "type=%{public}d, button=%{public}d"
            "inject=%{public}d",
            event.touchEventId, event.id, event.x, event.y, event.z, (int)event.action, (int)event.button,
            event.isInjected);
#endif
    }

    if (event.button == MouseButton::RIGHT_BUTTON && event.action == MouseAction::PRESS) {
        // Mouse right button press event set focus inactive here.
        // Mouse left button press event will set focus inactive in touch process.
        SetIsFocusActive(false, FocusActiveReason::POINTER_EVENT);
    }

    if (event.action == MouseAction::RELEASE || event.action == MouseAction::CANCEL ||
        event.action == MouseAction::WINDOW_LEAVE) {
        lastMouseTime_ = GetTimeFromExternalTimer();
        CompensateMouseMoveEvent(event, node);
    }
    NotifyDragMouseEvent(event);
    DispatchMouseToTouchEvent(event, node);
    if (event.action == MouseAction::MOVE) {
        if (event.passThrough) {
            DispatchMouseEvent(event, node);
            if (postEventManager_) {
                postEventManager_->SetPassThroughResult(eventManager_->GetPassThroughResult());
            }
            return;
        }
        mouseEvents_[node].emplace_back(event);
        hasIdleTasks_ = true;
        RequestFrame();
        return;
    }
    DispatchMouseEvent(event, node);
    if (postEventManager_) {
        postEventManager_->SetPassThroughResult(eventManager_->GetPassThroughResult());
    }
}

void PipelineContext::DispatchMouseToTouchEvent(const MouseEvent& event, const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    if (((event.action == MouseAction::RELEASE || event.action == MouseAction::PRESS ||
            event.action == MouseAction::MOVE) &&
            (event.button == MouseButton::LEFT_BUTTON || event.pressedButtons == MOUSE_PRESS_LEFT)) ||
        event.action == MouseAction::CANCEL) {
        auto touchPoint = event.CreateTouchPoint();
        if (event.pullAction == MouseAction::PULL_MOVE) {
            touchPoint.pullType = TouchType::PULL_MOVE;
        }
        OnTouchEvent(touchPoint, node);
    } else {
        auto touchPoint = event.CreateTouchPoint();
        auto scalePoint = touchPoint.CreateScalePoint(GetViewScale());
        auto rootOffset = GetRootRect().GetOffset();
        eventManager_->HandleGlobalEventNG(scalePoint, selectOverlayManager_, rootOffset);
    }
}

void PipelineContext::CompensateMouseMoveEvent(const MouseEvent& event, const RefPtr<FrameNode>& node)
{
    if (CompensateMouseMoveEventFromUnhandledEvents(event, node)) {
        return;
    }
    auto lastEventIter = nodeToMousePoints_.find(node);
    if (lastEventIter == nodeToMousePoints_.end() || lastEventIter->second.empty()) {
        return;
    }
    MouseEvent mouseEvent = lastEventIter->second.back();
    auto iter = eventManager_->GetLastDispatchTime().find(mouseEvent.id);
    if (iter != eventManager_->GetLastDispatchTime().end()) {
        if (static_cast<uint64_t>(mouseEvent.time.time_since_epoch().count()) > iter->second) {
            TouchRestrict touchRestrict { TouchRestrict::NONE };
            touchRestrict.sourceType = event.sourceType;
            touchRestrict.hitTestType = SourceType::MOUSE;
            touchRestrict.inputEventType = InputEventType::MOUSE_BUTTON;
            eventManager_->MouseTest(mouseEvent, node, touchRestrict);
            eventManager_->DispatchMouseEventNG(mouseEvent);
            eventManager_->DispatchMouseHoverEventNG(mouseEvent);
            eventManager_->DispatchMouseHoverAnimationNG(mouseEvent);
        }
    }
}

bool PipelineContext::CompensateMouseMoveEventFromUnhandledEvents(
    const MouseEvent& event, const RefPtr<FrameNode>& node)
{
    if (mouseEvents_.empty()) {
        return false;
    }

    auto iter = mouseEvents_.find(node);
    if (iter == mouseEvents_.end()) {
        return false;
    }
    std::vector<MouseEvent> history;
    for (auto mouseIter = iter->second.begin(); mouseIter != iter->second.end();) {
        if (event.id == mouseIter->id) {
            history.emplace_back(*mouseIter);
            mouseIter = iter->second.erase(mouseIter);
        } else {
            mouseIter++;
        }
    }
    mouseEvents_.erase(iter);

    if (history.empty()) {
        return false;
    }

    MouseEvent lastMoveEvent(history.back());
    lastMoveEvent.history.swap(history);
    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = event.sourceType;
    touchRestrict.hitTestType = SourceType::MOUSE;
    touchRestrict.inputEventType = InputEventType::MOUSE_BUTTON;
    eventManager_->MouseTest(lastMoveEvent, node, touchRestrict);
    eventManager_->DispatchMouseEventNG(lastMoveEvent);
    eventManager_->DispatchMouseHoverEventNG(lastMoveEvent);
    eventManager_->DispatchMouseHoverAnimationNG(lastMoveEvent);
    return true;
}

void PipelineContext::DispatchMouseEvent(const MouseEvent& event, const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto scaleEvent = event.CreateScaleEvent(viewScale_);
    if (scaleEvent.action != MouseAction::MOVE &&
        historyMousePointsById_.find(scaleEvent.id) != historyMousePointsById_.end()) {
        historyMousePointsById_.erase(scaleEvent.id);
    }

    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = event.sourceType;
    touchRestrict.hitTestType = SourceType::MOUSE;
    touchRestrict.inputEventType = InputEventType::MOUSE_BUTTON;
    if (event.action != MouseAction::MOVE || event.passThrough) {
        eventManager_->MouseTest(scaleEvent, node, touchRestrict);
        eventManager_->DispatchMouseEventNG(scaleEvent);
        eventManager_->DispatchMouseHoverEventNG(scaleEvent);
        eventManager_->DispatchMouseHoverAnimationNG(scaleEvent);
    }
    accessibilityManagerNG_->HandleAccessibilityHoverEvent(node, scaleEvent);
    RequestFrame();
}

void PipelineContext::FlushMouseEvent()
{
    if (!lastMouseEvent_ || lastMouseEvent_->action == MouseAction::WINDOW_LEAVE) {
        return;
    }
    MouseEvent event;
    event.x = lastMouseEvent_->x;
    event.y = lastMouseEvent_->y;
    event.time = lastMouseEvent_->time;
    event.action = MouseAction::MOVE;
    event.button = MouseButton::NONE_BUTTON;
    event.sourceType = SourceType::MOUSE;
    event.deviceId = lastMouseEvent_->deviceId;
    event.sourceTool = SourceTool::MOUSE;

    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(rootNode_);
    ACE_SCOPED_TRACE("FlushMouseEvent x:%f y:%f", lastMouseEvent_->x, lastMouseEvent_->y);
    auto scaleEvent = event.CreateScaleEvent(viewScale_);
    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = event.sourceType;
    touchRestrict.hitTestType = SourceType::MOUSE;
    touchRestrict.inputEventType = InputEventType::MOUSE_BUTTON;
    OnFlushMouseEvent(touchRestrict);
}

void PipelineContext::OnFlushMouseEvent(TouchRestrict& touchRestrict)
{
    decltype(mouseEvents_) mouseEvents(std::move(mouseEvents_));
    if (mouseEvents.empty()) {
        canUseLongPredictTask_ = true;
        nodeToMousePoints_.clear();
        return;
    }
    canUseLongPredictTask_ = false;
    for (auto iter = mouseEvents.begin(); iter != mouseEvents.end(); ++iter) {
        OnFlushMouseEvent(iter->first, iter->second, touchRestrict);
    }
}

void PipelineContext::OnFlushMouseEvent(
    const RefPtr<FrameNode> &node, const std::list<MouseEvent>& mouseEvents, TouchRestrict& touchRestrict)
{
    if (mouseEvents.empty()) {
        canUseLongPredictTask_ = true;
        return ;
    }
    canUseLongPredictTask_ = false;
    std::unordered_map<int, MouseEvent> idToMousePoints;
    bool needInterpolation = true;
    std::unordered_map<int32_t, MouseEvent> newIdMousePoints;
    std::map<WeakPtr<FrameNode>, std::vector<MouseEvent>> nodeToMousePoints;
    for (auto iter = mouseEvents.rbegin(); iter != mouseEvents.rend(); ++iter) {
        auto scaleEvent = (*iter).CreateScaleEvent(GetViewScale());
        idToMousePoints.emplace(scaleEvent.id, scaleEvent);
        if (!iter->mockFlushEvent) {
            idToMousePoints[scaleEvent.id].history.insert(idToMousePoints[scaleEvent.id].history.begin(), scaleEvent);
        }
        nodeToMousePoints[node].emplace_back(idToMousePoints[scaleEvent.id]);
        needInterpolation = iter->action != MouseAction::MOVE ? false : true;
    }
    if (!NeedTouchInterpolation()) {
        needInterpolation = false;
    }
    if (needInterpolation) {
        auto targetTimeStamp = resampleTimeStamp_;
        for (const auto& idIter : idToMousePoints) {
            auto stamp =
                std::chrono::duration_cast<std::chrono::nanoseconds>(idIter.second.time.time_since_epoch()).count();
            if (targetTimeStamp > static_cast<uint64_t>(stamp)) {
                LOGI("there is no mouse event after interpolation time point. "
                    "(last stamp:%{public}" PRIu64 ", target stamp:%{public}" PRIu64 ")",
                    static_cast<uint64_t>(stamp), targetTimeStamp);
                continue;
            }
            if (idIter.second.button == MouseButton::NONE_BUTTON) {
                continue;
            }
            MouseEvent newMouseEvent = eventManager_->GetResampleMouseEvent(
                historyMousePointsById_[idIter.first], idIter.second.history, targetTimeStamp);
            if (newMouseEvent.x != 0 && newMouseEvent.y != 0) {
                newIdMousePoints[idIter.first] = newMouseEvent;
            }
            historyMousePointsById_[idIter.first] = idIter.second.history;
        }
    }
    nodeToMousePoints_ = std::move(nodeToMousePoints);
    DispatchMouseEvent(idToMousePoints, newIdMousePoints, mouseEvents, touchRestrict, node);
}

void PipelineContext::DispatchMouseEvent(
    std::unordered_map<int, MouseEvent>& idToMousePoints,
    std::unordered_map<int32_t, MouseEvent> &newIdMousePoints,
    const std::list<MouseEvent> &mouseEvents,
    TouchRestrict& touchRestrict,
    const RefPtr<FrameNode> &node)
{
    std::list<MouseEvent> mousePoints;
    for (const auto& iter : idToMousePoints) {
        auto lastDispatchTime = eventManager_->GetLastDispatchTime();
        lastDispatchTime[iter.first] = GetVsyncTime();
        eventManager_->SetLastDispatchTime(std::move(lastDispatchTime));
        auto it = newIdMousePoints.find(iter.first);
        if (it != newIdMousePoints.end()) {
            mousePoints.emplace_back(it->second);
        } else {
            mousePoints.emplace_back(iter.second);
        }
    }
    for (auto iter = mousePoints.rbegin(); iter != mousePoints.rend(); ++iter) {
        auto scaleEvent = iter->CreateScaleEvent(viewScale_);
        eventManager_->MouseTest(scaleEvent, node, touchRestrict);
        eventManager_->DispatchMouseEventNG(scaleEvent);
        eventManager_->DispatchMouseHoverEventNG(scaleEvent);
        eventManager_->DispatchMouseHoverAnimationNG(scaleEvent);
    }
}

bool PipelineContext::ChangeMouseStyle(int32_t nodeId, MouseFormat format, int32_t windowId, bool isByPass,
    MouseStyleChangeReason reason)
{
    auto mouseStyleManager = eventManager_->GetMouseStyleManager();
    CHECK_NULL_RETURN(mouseStyleManager, false);
    if (!windowId) {
        windowId = static_cast<int32_t>(GetFocusWindowId());
    }
    mouseStyleManager->SetMouseFormat(windowId, nodeId, format, isByPass, reason);
    RequestFrame();
    return true;
}

void PipelineContext::ReDispatch(KeyEvent& keyEvent)
{
    CHECK_NULL_VOID(eventManager_);
    TAG_LOGD(AceLogTag::ACE_WEB, "Web ReDispach key event: code:" SEC_PLD(%{public}d) "/action:%{public}d.",
        SEC_PARAM(keyEvent.code), keyEvent.action);
    eventManager_->ReDispatch(keyEvent);
}

bool PipelineContext::OnNonPointerEvent(const NonPointerEvent& event)
{
    return eventManager_->OnNonPointerEvent(event);
}

bool PipelineContext::RequestFocus(const std::string& targetNodeId, bool isSyncRequest)
{
    auto rootNode = GetFocusedWindowSceneNode();
    if (!rootNode) {
        rootNode = rootNode_;
    }
    CHECK_NULL_RETURN(rootNode, false);
    auto focusHub = rootNode->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    auto currentFocusChecked = focusHub->RequestFocusImmediatelyById(targetNodeId, isSyncRequest);
    if (!isSubPipeline_ || currentFocusChecked) {
        return currentFocusChecked;
    }
    auto parentPipelineBase = parentPipeline_.Upgrade();
    CHECK_NULL_RETURN(parentPipelineBase, false);
    auto parentPipelineContext = AceType::DynamicCast<NG::PipelineContext>(parentPipelineBase);
    CHECK_NULL_RETURN(parentPipelineContext, false);
    return parentPipelineContext->RequestFocus(targetNodeId, isSyncRequest);
}

void PipelineContext::AddDirtyFocus(const RefPtr<FrameNode>& node)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(node);
    if (node->GetFocusType() == FocusType::NODE) {
        dirtyFocusNode_ = WeakClaim(RawPtr(node));
    } else {
        dirtyFocusScope_ = WeakClaim(RawPtr(node));
    }
    RequestFrame();
}

void PipelineContext::AddDirtyRequestFocus(const RefPtr<FrameNode>& node)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(node);
    dirtyRequestFocusNode_ = WeakPtr<FrameNode>(node);
    RequestFrame();
}

void PipelineContext::RootLostFocus(BlurReason reason) const
{
    CHECK_NULL_VOID(rootNode_);
    auto focusHub = rootNode_->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->LostFocus(reason);
    CHECK_NULL_VOID(overlayManager_);
    overlayManager_->HideAllMenus();
}

MouseEvent ConvertAxisToMouse(const AxisEvent& event)
{
    MouseEvent result;
    result.x = event.x;
    result.y = event.y;
    result.action = MouseAction::MOVE;
    result.button = MouseButton::NONE_BUTTON;
    result.time = event.time;
    result.deviceId = event.deviceId;
    result.sourceType = event.sourceType;
    result.sourceTool = event.sourceTool;
    result.touchEventId = event.touchEventId;
    result.pointerEvent = event.pointerEvent;
    result.screenX = event.screenX;
    result.screenY = event.screenY;
    return result;
}

void PipelineContext::OnAxisEvent(const AxisEvent& event, const RefPtr<FrameNode>& node)
{
    if (!axisEventChecker_.IsAxisEventSequenceCorrect(event)) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW,
            "AxisEvent error occurred, the currentAction is %{public}d, the preAction is %{public}d", event.action,
            axisEventChecker_.GetPreAction());
    }
    auto scaleEvent = event.CreateScaleEvent(viewScale_);
    if (event.action == AxisAction::BEGIN || event.action == AxisAction::CANCEL || event.action == AxisAction::END) {
        eventManager_->GetEventTreeRecord(EventTreeType::TOUCH).AddAxis(scaleEvent);
    }
    auto formEventMgr = this->GetFormEventManager();
    SerializedGesture etsSerializedGesture;
    if (event.action != AxisAction::BEGIN && formEventMgr) {
        formEventMgr->HandleEtsCardAxisEvent(scaleEvent, etsSerializedGesture);
    }

    DispatchAxisEventToDragDropManager(event, node, etsSerializedGesture);
    // when api >= 15, do not block end and cancel action.
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_FIFTEEN)) {
        if (event.action != AxisAction::NONE) {
            eventManager_->AxisTest(scaleEvent, node);
            eventManager_->DispatchAxisEventNG(scaleEvent);
        }
    } else {
        if (event.action == AxisAction::BEGIN || event.action == AxisAction::UPDATE) {
            eventManager_->AxisTest(scaleEvent, node);
            eventManager_->DispatchAxisEventNG(scaleEvent);
        }
    }
    if (postEventManager_) {
        postEventManager_->SetPassThroughResult(eventManager_->GetPassThroughResult());
    }
    if (event.action == AxisAction::BEGIN && formEventMgr) {
        formEventMgr->HandleEtsCardAxisEvent(scaleEvent, etsSerializedGesture);
    }
    if (scaleEvent.action == AxisAction::BEGIN) {
        TAG_LOGD(AceLogTag::ACE_MOUSE, "Slide Axis Begin");
        ResSchedReport::GetInstance().OnAxisEvent(scaleEvent);
    } else if (scaleEvent.verticalAxis == 0 && scaleEvent.horizontalAxis == 0) {
        TAG_LOGD(AceLogTag::ACE_MOUSE, "Slide Axis End");
        ResSchedReport::GetInstance().ResSchedDataReport("axis_off");
    } else {
        TAG_LOGD(AceLogTag::ACE_MOUSE, "Slide Axis Update");
        ResSchedReport::GetInstance().OnAxisEvent(scaleEvent);
    }
    auto mouseEvent = ConvertAxisToMouse(event);
    OnMouseMoveEventForAxisEvent(mouseEvent, node);
    if (formEventMgr && ((scaleEvent.action == AxisAction::END) || (scaleEvent.action == AxisAction::CANCEL))) {
        formEventMgr->RemoveEtsCardAxisEventCallback(event.id);
        formEventMgr->RemoveEtsCardTouchEventCallback(event.id);
    }
}

void PipelineContext::DispatchAxisEventToDragDropManager(const AxisEvent& event, const RefPtr<FrameNode>& node,
    SerializedGesture& etsSerializedGesture)
{
    auto scaleEvent = event.CreateScaleEvent(viewScale_);
    auto dragManager = GetDragDropManager();
    if (dragManager && !dragManager->IsDragged()) {
        if (event.action == AxisAction::BEGIN) {
            isBeforeDragHandleAxis_ = true;
            TouchRestrict touchRestrict { TouchRestrict::NONE };
            touchRestrict.sourceType = event.sourceType;
            touchRestrict.hitTestType = SourceType::TOUCH;
            touchRestrict.inputEventType = InputEventType::AXIS;
            // If received rotate event, no need to touchtest.
            if (!event.isRotationEvent) {
                eventManager_->TouchTest(scaleEvent, node, touchRestrict);
                auto axisTouchTestResults_ = eventManager_->GetAxisTouchTestResults();
                auto formEventMgr = this->GetFormEventManager();
                if (formEventMgr) {
                    formEventMgr->HandleEtsCardTouchEvent(touchRestrict.touchEvent, etsSerializedGesture);
                }
                auto formGestureMgr =  this->GetFormGestureManager();
                if (formGestureMgr) {
                    formGestureMgr->LinkGesture(event, this, node, axisTouchTestResults_,
                        etsSerializedGesture, eventManager_);
                }
            }
        }
        eventManager_->DispatchTouchEvent(scaleEvent);
    } else if (isBeforeDragHandleAxis_ && (event.action == AxisAction::END || event.action == AxisAction::CANCEL)) {
        eventManager_->DispatchTouchEvent(scaleEvent);
        isBeforeDragHandleAxis_ = false;
    }
}

void PipelineContext::OnMouseMoveEventForAxisEvent(const MouseEvent& event, const RefPtr<NG::FrameNode>& node)
{
    if (event.action != MouseAction::MOVE || event.button != MouseButton::NONE_BUTTON) {
        return;
    }
    CHECK_RUN_ON(UI);
    UpdateLastMoveEvent(event);
    auto manager = GetDragDropManager();
    if (manager) {
        manager->SetIsDragCancel(false);
    } else {
        TAG_LOGW(AceLogTag::ACE_INPUTTRACKING, "InputTracking id:%{public}d, OnMouseEvent GetDragDropManager is null",
            event.touchEventId);
    }
    auto touchPoint = event.CreateTouchPoint();
    auto scalePoint = touchPoint.CreateScalePoint(GetViewScale());
    auto rootOffset = GetRootRect().GetOffset();
    eventManager_->HandleGlobalEventNG(scalePoint, selectOverlayManager_, rootOffset);
    CHECK_NULL_VOID(node);
    auto scaleEvent = event.CreateScaleEvent(viewScale_);
    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = event.sourceType;
    touchRestrict.hitTestType = SourceType::MOUSE;
    touchRestrict.inputEventType = InputEventType::MOUSE_BUTTON;
    eventManager_->MouseTest(scaleEvent, node, touchRestrict);
    eventManager_->DispatchMouseEventNG(scaleEvent);
    eventManager_->DispatchMouseHoverEventNG(scaleEvent);
    eventManager_->DispatchMouseHoverAnimationNG(scaleEvent);
    accessibilityManagerNG_->HandleAccessibilityHoverEvent(node, scaleEvent);
    RequestFrame();
}

bool PipelineContext::HasDifferentDirectionGesture() const
{
    CHECK_NULL_RETURN(eventManager_, false);
    return eventManager_->HasDifferentDirectionGesture();
}

void PipelineContext::AddVisibleAreaChangeNode(const int32_t nodeId)
{
    onVisibleAreaChangeNodeIds_.emplace(nodeId);
}

void PipelineContext::AddVisibleAreaChangeNode(const RefPtr<FrameNode>& node,
    const std::vector<double>& ratios, const VisibleRatioCallback& callback, bool isUserCallback,
    bool isCalculateInnerClip)
{
    CHECK_NULL_VOID(node);
    VisibleCallbackInfo addInfo;
    addInfo.callback = callback;
    addInfo.isCurrentVisible = false;
    onVisibleAreaChangeNodeIds_.emplace(node->GetId());
    if (isUserCallback) {
        node->SetVisibleAreaUserCallback(ratios, addInfo);
    } else {
        node->SetVisibleAreaInnerCallback(ratios, addInfo, isCalculateInnerClip);
    }
}

void PipelineContext::RemoveVisibleAreaChangeNode(int32_t nodeId)
{
    auto frameNode = DynamicCast<FrameNode>(ElementRegister::GetInstance()->GetUINodeById(nodeId));
    if (frameNode) {
        frameNode->ClearCachedIsFrameDisappear();
    }

    onVisibleAreaChangeNodeIds_.erase(nodeId);
}

void PipelineContext::HandleVisibleAreaChangeEvent(uint64_t nanoTimestamp)
{
    ACE_FUNCTION_TRACE();
    if (onVisibleAreaChangeNodeIds_.empty()) {
        return;
    }
    auto nodes = FrameNode::GetNodesById(onVisibleAreaChangeNodeIds_);
    for (auto&& frameNode : nodes) {
        frameNode->TriggerVisibleAreaChangeCallback(nanoTimestamp, false, isDisappearChangeNodeMinDepth_);
    }

    isDisappearChangeNodeMinDepth_ = 0;
}

void PipelineContext::AddOnAreaChangeNode(int32_t nodeId)
{
    onAreaChangeNodeIds_.emplace(nodeId);
    isOnAreaChangeNodesCacheVaild_ = false;
}

void PipelineContext::RemoveOnAreaChangeNode(int32_t nodeId)
{
    auto frameNode = DynamicCast<FrameNode>(ElementRegister::GetInstance()->GetUINodeById(nodeId));
    if (frameNode) {
        frameNode->ClearCachedGlobalOffset();
    }

    onAreaChangeNodeIds_.erase(nodeId);
    isOnAreaChangeNodesCacheVaild_ = false;
}

bool PipelineContext::HasOnAreaChangeNode(int32_t nodeId)
{
    return onAreaChangeNodeIds_.find(nodeId) != onAreaChangeNodeIds_.end();
}

void PipelineContext::HandleOnAreaChangeEvent(uint64_t nanoTimestamp)
{
    ACE_FUNCTION_TRACE();
    if (onAreaChangeNodeIds_.empty()) {
        return;
    }
    auto nodes = FrameNode::GetNodesById(onAreaChangeNodeIds_);
    for (auto&& frameNode : nodes) {
        frameNode->TriggerOnAreaChangeCallback(nanoTimestamp, areaChangeNodeMinDepth_);
    }

    areaChangeNodeMinDepth_ = 0;
    UpdateFormLinkInfos();
}

void PipelineContext::UpdateFormLinkInfos()
{
    if (formLinkInfoUpdateHandler_ && !formLinkInfoMap_.empty()) {
        std::vector<std::string> formLinkInfos;
        for (auto iter = formLinkInfoMap_.rbegin(); iter != formLinkInfoMap_.rend(); ++iter) {
            auto info = iter->second;
            formLinkInfos.push_back(info);
        }
        formLinkInfoUpdateHandler_(formLinkInfos);
    }
}

void PipelineContext::OnShow()
{
    CHECK_RUN_ON(UI);
    onShow_ = true;
    window_->OnShow();
    PerfMonitor::GetPerfMonitor()->SetAppForeground(true);
    RequestFrame();
    FlushWindowStateChangedCallback(true);
    AccessibilityEvent event;
    event.windowChangeTypes = WindowUpdateType::WINDOW_UPDATE_ACTIVE;
    event.type = AccessibilityEventType::PAGE_CHANGE;
    SendEventToAccessibility(event);
}

void PipelineContext::OnHide()
{
    CHECK_RUN_ON(UI);
    NotifyDragOnHide();
    onShow_ = false;
    window_->OnHide();
    PerfMonitor::GetPerfMonitor()->SetAppForeground(false);
    RequestFrame();
    OnVirtualKeyboardAreaChange(Rect());
    FlushWindowStateChangedCallback(false);
    AccessibilityEvent event;
    event.type = AccessibilityEventType::PAGE_CLOSE;
    SendEventToAccessibility(event);
    memoryMgr_->PostMemRecycleTask();
}

void PipelineContext::WindowFocus(bool isFocus)
{
    CHECK_RUN_ON(UI);
    onFocus_ = isFocus;
    if (!isFocus) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "Window: %{public}d lost focus.", windowId_);
        RestoreDefault(0, MouseStyleChangeReason::WINDOW_LOST_FOCUS_RESET_MOUSESTYLE);
        RootLostFocus(BlurReason::WINDOW_BLUR);
        NotifyPopupDismiss();
    } else {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "Window: %{public}d get focus.", windowId_);

        isWindowHasFocused_ = true;
        InputMethodManager::GetInstance()->SetWindowFocus(true);
    }
    GetOrCreateFocusManager()->WindowFocus(isFocus);
    FlushWindowFocusChangedCallback(isFocus);
}

void PipelineContext::WindowActivate(bool isActive)
{
    CHECK_RUN_ON(UI);
    onActive_ = isActive;
    FlushWindowActivateChangedCallback(isActive);
}

void PipelineContext::ContainerModalUnFocus()
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        return;
    }
    CHECK_NULL_VOID(rootNode_);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetChildren().front());
    CHECK_NULL_VOID(containerNode);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_VOID(containerPattern);
    containerPattern->OnWindowForceUnfocused();
}

void PipelineContext::ShowContainerTitle(bool isShow, bool hasDeco, bool needUpdate)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        return;
    }
    CHECK_NULL_VOID(rootNode_);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetChildren().front());
    CHECK_NULL_VOID(containerNode);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_VOID(containerPattern);
    containerPattern->ShowTitle(isShow, hasDeco, needUpdate);
    isShowTitle_ = isShow && hasDeco;
    auto titleMgr = containerPattern->GetTitleManager();
    if (titleMgr) {
        if (isShowTitle_) {
            titleMgr->UpdateTargetNodesBarMargin();
        } else {
            titleMgr->ResetExpandStackNode();
        }
    }
}

void PipelineContext::UpdateTitleInTargetPos(bool isShow, int32_t height)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        return;
    }
    CHECK_NULL_VOID(rootNode_);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetChildren().front());
    CHECK_NULL_VOID(containerNode);
    auto containerPattern = containerNode->GetPattern<ContainerModalPatternEnhance>();
    CHECK_NULL_VOID(containerPattern);
    containerPattern->UpdateTitleInTargetPos(isShow, height);
}


void PipelineContext::SetContainerWindow(bool isShow, RRect& rRect)
{
#ifdef ENABLE_ROSEN_BACKEND
    if (!IsJsCard()) {
        auto window = GetWindow();
        if (window) {
            auto rect = rRect.GetRect();
            OHOS::Rosen::RectF rosenRectF = {rect.GetOffset().GetX(), rect.GetOffset().GetY(),
                rect.Width(), rect.Height()};
            auto radiusValueX = rRect.GetCorner().topLeftRadius.GetX().Value();
            auto radiusValueY = rRect.GetCorner().topLeftRadius.GetY().Value();

            auto rosenRRect = OHOS::Rosen::RRect(rosenRectF, radiusValueX, radiusValueY);
            auto rsUIDirector = window->GetRSUIDirector();
            if (rsUIDirector) {
                // set container window show state to render service
                TAG_LOGD(AceLogTag::ACE_APPBAR, "SetContainerWindow: isShow=%{public}d; "
                    "x=%{public}f, y=%{public}f, width=%{public}f, hight=%{public}f, radiusValueX=%{public}f.",
                    isShow, rect.GetOffset().GetX(), rect.GetOffset().GetY(),
                    rect.Width(), rect.Height(), radiusValueX);
                rsUIDirector->SetContainerWindow(isShow, rosenRRect);
            }
        }
    }
#endif
}

void PipelineContext::SetAppBgColor(const Color& color)
{
    appBgColor_ = color;
#ifdef ENABLE_ROSEN_BACKEND
    std::shared_ptr<Rosen::RSUIDirector> rsUIDirector;
    if (!IsJsCard()) {
        auto window = GetWindow();
        if (window) {
            rsUIDirector = window->GetRSUIDirector();
            if (rsUIDirector) {
                rsUIDirector->SetAbilityBGAlpha(appBgColor_.GetAlpha());
            }
        }
    }
    FlushImplicitTransaction(rsUIDirector);
#endif
    CHECK_NULL_VOID(stageManager_);
    auto stage = stageManager_->GetStageNode();
    CHECK_NULL_VOID(stage);
    auto renderContext = stage->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(color);
}

void PipelineContext::SetAppTitle(const std::string& title)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        return;
    }
    CHECK_NULL_VOID(rootNode_);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetChildren().front());
    CHECK_NULL_VOID(containerNode);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_VOID(containerPattern);
    containerPattern->SetAppTitle(title);
}

void PipelineContext::SetAppIcon(const RefPtr<PixelMap>& icon)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        return;
    }
    CHECK_NULL_VOID(rootNode_);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetChildren().front());
    CHECK_NULL_VOID(containerNode);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_VOID(containerPattern);
    containerPattern->SetAppIcon(icon);
}

void PipelineContext::FlushReload(const ConfigurationChange& configurationChange, bool fullUpdate)
{
     auto changeTask = [weak = WeakClaim(this), configurationChange,
        weakOverlayManager = AceType::WeakClaim(AceType::RawPtr(overlayManager_)), fullUpdate]() {
        auto pipeline = weak.Upgrade();
        CHECK_NULL_VOID(pipeline);
        if (configurationChange.IsNeedUpdate() || configurationChange.iconUpdate) {
            auto rootNode = pipeline->GetRootElement();
            rootNode->UpdateConfigurationUpdate(configurationChange);
            auto overlay = weakOverlayManager.Upgrade();
            if (overlay) {
                overlay->ReloadBuilderNodeConfig();
            }
        }
        if (fullUpdate && configurationChange.IsNeedUpdate()) {
            CHECK_NULL_VOID(pipeline->stageManager_);
            pipeline->SetIsReloading(true);
            pipeline->stageManager_->ReloadStage();
            pipeline->SetIsReloading(false);
            pipeline->FlushUITasks();
        }
    };
    if (!onShow_) {
        changeTask();
        return;
    }
    AnimationOption option;
    const int32_t duration = 400;
    option.SetDuration(duration);
    option.SetCurve(Curves::FRICTION);
    RecycleManager::Notify(configurationChange);
    AnimationUtils::Animate(
        option,
        changeTask,
        [weak = WeakClaim(this)]() {
            auto pipeline = weak.Upgrade();
            CHECK_NULL_VOID(pipeline);
            pipeline->OnFlushReloadFinish();
        });
    auto stage = stageManager_->GetStageNode();
    CHECK_NULL_VOID(stage);
    auto renderContext = stage->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateWindowBlur();
}

void PipelineContext::Destroy()
{
    CHECK_RUN_ON(UI);
    SetDestroyed();
    rootNode_->DetachFromMainTree();
    std::set<WeakPtr<UINode>> nodeSet;
    std::swap(nodeSet, attachedNodeSet_);
    for (const auto& node : nodeSet) {
        auto illegalNode = node.Upgrade();
        if (illegalNode) {
            illegalNode->DetachFromMainTree();
        }
    }
    rootNode_->FireCustomDisappear();
    taskScheduler_->CleanUp();
    scheduleTasks_.clear();
    dirtyNodes_.clear();
    rootNode_.Reset();
    accessibilityManagerNG_.Reset();
    stageManager_.Reset();
    if (overlayManager_) {
        overlayManager_->ClearUIExtensionNode();
    }
    overlayManager_.Reset();
    sharedTransitionManager_.Reset();
    dragDropManager_.Reset();
    TAG_LOGI(AceLogTag::ACE_DRAG, "PipelineContext::Destroy Reset dragDropManager_");
    focusManager_.Reset();
    selectOverlayManager_.Reset();
    fullScreenManager_.Reset();
    memoryMgr_.Reset();
    nodeToMousePoints_.clear();
    nodeToPointEvent_.clear();
    touchEvents_.clear();
    mouseEvents_.clear();
    dragEvents_.clear();
    buildFinishCallbacks_.clear();
    onWindowStateChangedCallbacks_.clear();
    onWindowFocusChangedCallbacks_.clear();
    nodesToNotifyMemoryLevel_.clear();
    dirtyFocusNode_.Reset();
    dirtyFocusScope_.Reset();
    needRenderNode_.clear();
    dirtyRequestFocusNode_.Reset();
    auto formEventMgr = this->GetFormEventManager();
    if (formEventMgr) {
        formEventMgr->ClearEtsCardTouchEventCallback();
        formEventMgr->ClearEtsCardAxisEventCallback();
    }
#ifdef WINDOW_SCENE_SUPPORTED
    uiExtensionManager_.Reset();
#endif
    uiContextImpl_.Reset();
    PipelineBase::Destroy();
}

void PipelineContext::AddBuildFinishCallBack(std::function<void()>&& callback)
{
    buildFinishCallbacks_.emplace_back(std::move(callback));
}

void PipelineContext::AddWindowStateChangedCallback(int32_t nodeId)
{
    if (!CheckThreadSafe()) {
        LOGW("AddWindowStateChangedCallback doesn't run on UI thread!");
    }
    onWindowStateChangedCallbacks_.emplace(nodeId);
}

void PipelineContext::RemoveWindowStateChangedCallback(int32_t nodeId)
{
    if (!CheckThreadSafe()) {
        LOGW("RemoveWindowStateChangedCallback doesn't run on UI thread!");
    }
    onWindowStateChangedCallbacks_.erase(nodeId);
}

void PipelineContext::FlushWindowStateChangedCallback(bool isShow)
{
    if (!CheckThreadSafe()) {
        LOGW("FlushWindowStateChangedCallback doesn't run on UI thread!");
    }
    std::set<int32_t> onWindowStateChangedCallbacks;
    std::swap(onWindowStateChangedCallbacks, onWindowStateChangedCallbacks_);
    auto iter = onWindowStateChangedCallbacks.begin();
    while (iter != onWindowStateChangedCallbacks.end()) {
        auto node = ElementRegister::GetInstance()->GetUINodeById(*iter);
        if (!node) {
            iter = onWindowStateChangedCallbacks.erase(iter);
        } else {
            if (isShow) {
                node->OnWindowShow();
            } else {
                node->OnWindowHide();
            }
            ++iter;
        }
    }
    std::swap(onWindowStateChangedCallbacks, onWindowStateChangedCallbacks_);
    HandleVisibleAreaChangeEvent(GetTimeFromExternalTimer());
    HandleSubwindow(isShow);
}

void PipelineContext::AddWindowFocusChangedCallback(int32_t nodeId)
{
    onWindowFocusChangedCallbacks_.emplace(nodeId);
}

void PipelineContext::RemoveWindowFocusChangedCallback(int32_t nodeId)
{
    onWindowFocusChangedCallbacks_.erase(nodeId);
}

void PipelineContext::FlushWindowFocusChangedCallback(bool isFocus)
{
    auto iter = onWindowFocusChangedCallbacks_.begin();
    while (iter != onWindowFocusChangedCallbacks_.end()) {
        auto node = ElementRegister::GetInstance()->GetUINodeById(*iter);
        if (!node) {
            iter = onWindowFocusChangedCallbacks_.erase(iter);
        } else {
            if (isFocus) {
                node->OnWindowFocused();
            } else {
                node->OnWindowUnfocused();
            }
            ++iter;
        }
    }
}

void PipelineContext::AddWindowActivateChangedCallback(int32_t nodeId)
{
    onWindowActivateChangedCallbacks_.emplace(nodeId);
}

void PipelineContext::RemoveWindowActivateChangedCallback(int32_t nodeId)
{
    onWindowActivateChangedCallbacks_.erase(nodeId);
}

void PipelineContext::FlushWindowActivateChangedCallback(bool isActivate)
{
    auto iter = onWindowActivateChangedCallbacks_.begin();
    while (iter != onWindowActivateChangedCallbacks_.end()) {
        auto node = ElementRegister::GetInstance()->GetUINodeById(*iter);
        if (!node) {
            iter = onWindowActivateChangedCallbacks_.erase(iter);
        } else {
            if (isActivate) {
                node->OnWindowActivated();
            } else {
                node->OnWindowDeactivated();
            }
            ++iter;
        }
    }
}

void PipelineContext::AddWindowSizeChangeCallback(int32_t nodeId)
{
    onWindowSizeChangeCallbacks_.emplace_back(nodeId);
}

void PipelineContext::RemoveWindowSizeChangeCallback(int32_t nodeId)
{
    onWindowSizeChangeCallbacks_.remove(nodeId);
}

void PipelineContext::AddWindowSizeDragEndCallback(std::function<void()>&& callback)
{
    onWindowSizeDragEndCallbacks_.emplace_back(std::move(callback));
}

void PipelineContext::SetIsWindowSizeDragging(bool isDragging)
{
    isWindowSizeDragging_ = isDragging;
    if (!isDragging) {
        decltype(onWindowSizeDragEndCallbacks_) dragEndCallbacks(std::move(onWindowSizeDragEndCallbacks_));
        for (const auto& func : dragEndCallbacks) {
            if (func) {
                func();
            }
        }
    }
}

void PipelineContext::AddNavigationNode(int32_t pageId, WeakPtr<UINode> navigationNode)
{
    CHECK_RUN_ON(UI);
    pageToNavigationNodes_[pageId].push_back(navigationNode);
}

void PipelineContext::RemoveNavigationNode(int32_t pageId, int32_t nodeId)
{
    CHECK_RUN_ON(UI);
    auto it = pageToNavigationNodes_.find(pageId);
    if (it != pageToNavigationNodes_.end() && !it->second.empty()) {
        for (auto iter = it->second.begin(); iter != it->second.end();) {
            auto navigationNode = AceType::DynamicCast<NavigationGroupNode>((*iter).Upgrade());
            if (navigationNode && navigationNode->GetId() == nodeId) {
                iter = it->second.erase(iter);
            } else {
                iter++;
            }
        }
    }
}

void PipelineContext::FirePageChanged(int32_t pageId, bool isOnShow)
{
    CHECK_RUN_ON(UI);
    auto iter = pageToNavigationNodes_.find(pageId);
    if (iter == pageToNavigationNodes_.end()) {
        return;
    }
    for (auto navigationNode : iter->second) {
        NavigationPattern::FireNavigationChange(navigationNode.Upgrade(), isOnShow, true);
    }
}

void PipelineContext::FlushWindowSizeChangeCallback(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    std::list<int32_t> callbacks;
    std::swap(callbacks, onWindowSizeChangeCallbacks_);
    auto iter = callbacks.begin();
    while (iter != callbacks.end()) {
        auto node = ElementRegister::GetInstance()->GetUINodeById(*iter);
        if (!node) {
            iter = callbacks.erase(iter);
        } else {
            node->OnWindowSizeChanged(width, height, type);
            ++iter;
        }
    }
    std::swap(callbacks, onWindowSizeChangeCallbacks_);
}

void PipelineContext::OnDragEvent(const DragPointerEvent& pointerEvent, DragEventAction action,
    const RefPtr<NG::FrameNode>& node)
{
    auto manager = GetDragDropManager();
    CHECK_NULL_VOID(manager);
    auto container = Container::Current();
    if (container && container->IsSceneBoardWindow()) {
        if (!manager->IsDragged() && manager->IsWindowConsumed()) {
            manager->SetIsWindowConsumed(false);
            return;
        }
    }

    if (action == DragEventAction::DRAG_EVENT_OUT || action == DragEventAction::DRAG_EVENT_END ||
        action == DragEventAction::DRAG_EVENT_PULL_THROW || action == DragEventAction::DRAG_EVENT_PULL_CANCEL) {
        lastDragTime_ = GetTimeFromExternalTimer();
        CompensatePointerMoveEvent(pointerEvent, node);
        manager->HandleDragEvent(pointerEvent, action, node);
        return;
    }
    manager->HandleDragEvent(pointerEvent, action, node);
    if (action == DragEventAction::DRAG_EVENT_MOVE) {
        manager->SetDragAnimationPointerEvent(pointerEvent);
        dragEvents_[node].emplace_back(pointerEvent);
        RequestFrame();
    }
    if (action != DragEventAction::DRAG_EVENT_MOVE &&
        historyPointsEventById_.find(pointerEvent.pointerId) != historyPointsEventById_.end()) {
        historyPointsEventById_.erase(pointerEvent.pointerId);
    }
}

void PipelineContext::NotifyDragTouchEvent(const TouchEvent& event)
{
    auto manager = GetDragDropManager();
    CHECK_NULL_VOID(manager);
    manager->HandleTouchEvent(event);
}

void PipelineContext::NotifyDragMouseEvent(const MouseEvent& event)
{
    auto manager = GetDragDropManager();
    CHECK_NULL_VOID(manager);
    manager->HandleMouseEvent(event);
}

void PipelineContext::NotifyDragOnHide()
{
    auto manager = GetDragDropManager();
    CHECK_NULL_VOID(manager);
    manager->HandlePipelineOnHide();
    manager->OnDragAsyncEnd();
}

void PipelineContext::CompensatePointerMoveEvent(const DragPointerEvent& event, const RefPtr<FrameNode>& node)
{
    auto manager = GetDragDropManager();
    std::string extraInfo = manager->GetExtraInfo();
    if (CompensatePointerMoveEventFromUnhandledEvents(event, node)) {
        return;
    }
    auto lastEventIter = nodeToPointEvent_.find(node);
    if (lastEventIter == nodeToPointEvent_.end() || lastEventIter->second.empty()) {
        return;
    }
    DragPointerEvent pointerEvent = lastEventIter->second.back();
    auto iter = eventManager_->GetLastDispatchTime().find(pointerEvent.pointerEventId);
    if (iter != eventManager_->GetLastDispatchTime().end()) {
        if (static_cast<uint64_t>(pointerEvent.time.time_since_epoch().count()) > iter->second) {
            manager->OnDragMove(pointerEvent, extraInfo, node);
        }
    }
}

bool PipelineContext::CompensatePointerMoveEventFromUnhandledEvents(
    const DragPointerEvent& event, const RefPtr<FrameNode>& node)
{
    auto manager = GetDragDropManager();
    std::string extraInfo = manager->GetExtraInfo();
    std::vector<DragPointerEvent> history;
    if (dragEvents_.empty()) {
        return false;
    }

    auto iter = dragEvents_.find(node);
    if (iter == dragEvents_.end()) {
        return false;
    }
    for (auto dragIter = iter->second.begin(); dragIter != iter->second.end();) {
        if (event.pointerEventId == dragIter->pointerEventId) {
            history.emplace_back(*dragIter);
            dragIter = iter->second.erase(dragIter);
        } else {
            dragIter++;
        }
    }
    dragEvents_.erase(iter);

    if (history.empty()) {
        return false;
    }

    auto lastePointerEvent(history.back());
    lastePointerEvent.history.swap(history);
    manager->OnDragMove(lastePointerEvent, extraInfo, node);
    return true;
}

void PipelineContext::AddNodesToNotifyMemoryLevel(int32_t nodeId)
{
    nodesToNotifyMemoryLevel_.emplace_back(nodeId);
}

void PipelineContext::RemoveNodesToNotifyMemoryLevel(int32_t nodeId)
{
    nodesToNotifyMemoryLevel_.remove(nodeId);
}

void PipelineContext::NotifyMemoryLevel(int32_t level)
{
    auto iter = nodesToNotifyMemoryLevel_.begin();
    while (iter != nodesToNotifyMemoryLevel_.end()) {
        auto node = ElementRegister::GetInstance()->GetUINodeById(*iter);
        if (!node) {
            iter = nodesToNotifyMemoryLevel_.erase(iter);
        } else {
            node->OnNotifyMemoryLevel(level);
            ++iter;
        }
    }
    if (window_) {
        window_->FlushTasks();
    }
}
void PipelineContext::AddPredictTask(PredictTask&& task)
{
    taskScheduler_->AddPredictTask(std::move(task));
    RequestFrame();
}

void PipelineContext::AddFrameCallback(FrameCallbackFunc&& frameCallbackFunc, IdleCallbackFunc&& idleCallbackFunc,
    int64_t delayMillis)
{
    if (delayMillis <= 0) {
        if (frameCallbackFunc != nullptr) {
            frameCallbackFuncs_.emplace_back(std::move(frameCallbackFunc));
        }
        if (idleCallbackFunc != nullptr) {
            idleCallbackFuncs_.emplace_back(std::move(idleCallbackFunc));
        }
        RequestFrame();
        return;
    }
    auto taskScheduler = GetTaskExecutor();
    CHECK_NULL_VOID(taskScheduler);
    if (frameCallbackFunc != nullptr) {
        taskScheduler->PostDelayedTask(
            [weak = WeakClaim(this), callbackFunc = std::move(frameCallbackFunc)]() -> void {
                auto pipeline = weak.Upgrade();
                CHECK_NULL_VOID(pipeline);
                auto callback = const_cast<FrameCallbackFunc&>(callbackFunc);
                pipeline->frameCallbackFuncs_.emplace_back(std::move(callback));
                pipeline->RequestFrame();
            },
            TaskExecutor::TaskType::UI, delayMillis, "ArkUIPostFrameCallbackFuncDelayed");
    }
    if (idleCallbackFunc != nullptr) {
        taskScheduler->PostDelayedTask(
            [weak = WeakClaim(this), callbackFunc = std::move(idleCallbackFunc)]() -> void {
                auto pipeline = weak.Upgrade();
                CHECK_NULL_VOID(pipeline);
                auto callback = const_cast<IdleCallbackFunc&>(callbackFunc);
                pipeline->idleCallbackFuncs_.emplace_back(std::move(callback));
                pipeline->RequestFrame();
            },
            TaskExecutor::TaskType::UI, delayMillis, "ArkUIPostIdleCallbackFuncDelayed");
    }
}

void PipelineContext::AddCAPIFrameCallback(FrameCallbackFuncFromCAPI&& frameCallbackFuncFromCAPI)
{
    if (frameCallbackFuncFromCAPI != nullptr) {
        frameCallbackFuncsFromCAPI_.emplace_back(std::move(frameCallbackFuncFromCAPI));
    }
}

void PipelineContext::TriggerIdleCallback(int64_t deadline)
{
    if (idleCallbackFuncs_.empty()) {
        return;
    }
    int64_t currentTime = GetSysTimestamp();
    if (deadline - currentTime < MIN_IDLE_TIME) {
        RequestFrame();
        return;
    }
    decltype(idleCallbackFuncs_) tasks(std::move(idleCallbackFuncs_));
    for (const auto& IdleCallbackFunc : tasks) {
        IdleCallbackFunc(deadline - currentTime, GetFrameCount());
        currentTime = GetSysTimestamp();
    }
}

void PipelineContext::OnIdle(int64_t deadline)
{
    int64_t currentTime = GetSysTimestamp();
    if (deadline == 0) {
        int64_t lastTaskEndTimestamp = window_->GetLastVsyncEndTimestamp();
        if (eventManager_) {
            lastTaskEndTimestamp = std::max(lastTaskEndTimestamp, eventManager_->GetLastTouchEventEndTimestamp());
        }
        if (lastTaskEndTimestamp > 0 && currentTime > lastTaskEndTimestamp
            && currentTime - lastTaskEndTimestamp > VSYNC_PERIOD_COUNT * window_->GetVSyncPeriod()) {
            auto frontend = weakFrontend_.Upgrade();
            if (frontend) {
                frontend->NotifyUIIdle();
            }
        }
    }
    if (deadline == 0 || isWindowAnimation_) {
        canUseLongPredictTask_ = false;
        return;
    }
    if (canUseLongPredictTask_) {
        // check new incoming event after vsync.
        if (!touchEvents_.empty()) {
            canUseLongPredictTask_ = false;
        }
    }
    CHECK_RUN_ON(UI);
    ACE_SCOPED_TRACE_COMMERCIAL("OnIdle, targettime:%" PRId64 "", deadline);
    taskScheduler_->FlushPredictTask(deadline - TIME_THRESHOLD, canUseLongPredictTask_);
    canUseLongPredictTask_ = false;
    currentTime = GetSysTimestamp();
    if (currentTime < deadline) {
        ElementRegister::GetInstance()->CallJSCleanUpIdleTaskFunc(deadline - currentTime);
        frameCountForNotCallJSCleanUp_ = 0;
    } else {
        frameCountForNotCallJSCleanUp_++;
    }

    // Check if there is more than 100 frame which does not execute the CallJSCleanUpIdleTaskFunc
    // Force to invoke CallJSCleanUpIdleTaskFunc to make sure no OOM in JS side
    if (frameCountForNotCallJSCleanUp_ >= MAX_FRAME_COUNT_WITHOUT_JS_UNREGISTRATION) {
        // The longest execution time is half of vsync period
        ElementRegister::GetInstance()->CallJSCleanUpIdleTaskFunc(window_->GetVSyncPeriod() / RATIO_OF_VSYNC_PERIOD);
        frameCountForNotCallJSCleanUp_ = 0;
    }

    TriggerIdleCallback(deadline);
}

void PipelineContext::Finish(bool /* autoFinish */) const
{
    CHECK_RUN_ON(UI);
    if (finishEventHandler_) {
        finishEventHandler_();
    }
}

void PipelineContext::AddAfterLayoutTask(std::function<void()>&& task, bool isFlushInImplicitAnimationTask)
{
    taskScheduler_->AddAfterLayoutTask(std::move(task), isFlushInImplicitAnimationTask);
}

void PipelineContext::AddPersistAfterLayoutTask(std::function<void()>&& task)
{
    taskScheduler_->AddPersistAfterLayoutTask(std::move(task));
}

void PipelineContext::AddAfterRenderTask(std::function<void()>&& task)
{
    taskScheduler_->AddAfterRenderTask(std::move(task));
}

void PipelineContext::AddSafeAreaPaddingProcessTask(FrameNode* node)
{
    taskScheduler_->AddSafeAreaPaddingProcessTask(node);
}

void PipelineContext::RemoveSafeAreaPaddingProcessTask(FrameNode* node)
{
    taskScheduler_->RemoveSafeAreaPaddingProcessTask(node);
}

void PipelineContext::FlushSafeAreaPaddingProcess()
{
    taskScheduler_->FlushSafeAreaPaddingProcess();
}

void PipelineContext::RestoreNodeInfo(std::unique_ptr<JsonValue> nodeInfo)
{
    auto child = nodeInfo->GetChild();
    while (child->IsValid()) {
        auto key = child->GetKey();
        auto value = child->GetString();
        restoreNodeInfo_.try_emplace(StringUtils::StringToInt(key), value);
        child = child->GetNext();
    }
}

std::unique_ptr<JsonValue> PipelineContext::GetStoredNodeInfo()
{
    auto jsonNodeInfo = JsonUtil::Create(true);
    auto iter = storeNode_.begin();
    while (iter != storeNode_.end()) {
        auto node = (iter->second).Upgrade();
        if (node) {
            std::string info = node->ProvideRestoreInfo();
            if (!info.empty()) {
                jsonNodeInfo->Put(std::to_string(iter->first).c_str(), info.c_str());
            }
        }
        ++iter;
    }
    return jsonNodeInfo;
}

void PipelineContext::StoreNode(int32_t restoreId, const WeakPtr<FrameNode>& node)
{
    auto ret = storeNode_.try_emplace(restoreId, node);
    if (!ret.second) {
        storeNode_[restoreId] = node;
    }
}

bool PipelineContext::GetRestoreInfo(int32_t restoreId, std::string& restoreInfo)
{
    auto iter = restoreNodeInfo_.find(restoreId);
    if (iter != restoreNodeInfo_.end()) {
        restoreInfo = iter->second;
        restoreNodeInfo_.erase(iter);
        return true;
    }
    return false;
}

void PipelineContext::SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        LOGW("Set app icon failed, Window modal is not container.");
        return;
    }
    CHECK_NULL_VOID(rootNode_);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetChildren().front());
    CHECK_NULL_VOID(containerNode);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_VOID(containerPattern);
    containerPattern->SetContainerButtonHide(hideSplit, hideMaximize, hideMinimize, hideClose);
}

void PipelineContext::EnableContainerModalGesture(bool isEnable)
{
    CHECK_NULL_VOID(rootNode_);
    const auto &children = rootNode_->GetChildren();
    if (children.empty()) {
        LOGW("rootNode children list is empty.");
        return;
    }
    auto containerNode = AceType::DynamicCast<FrameNode>(children.front());
    if (!containerNode) {
        LOGW("container node is null when set event on gesture row");
        return;
    }
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_VOID(containerPattern);
    containerPattern->EnableContainerModalGesture(isEnable);
}

bool PipelineContext::GetContainerFloatingTitleVisible()
{
    CHECK_NULL_RETURN(rootNode_, false);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetChildren().front());
    CHECK_NULL_RETURN(containerNode, false);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_RETURN(containerPattern, false);
    return containerPattern->GetFloatingTitleVisible();
}

bool PipelineContext::GetContainerCustomTitleVisible()
{
    CHECK_NULL_RETURN(rootNode_, false);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetChildren().front());
    CHECK_NULL_RETURN(containerNode, false);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_RETURN(containerPattern, false);
    return containerPattern->GetCustomTitleVisible();
}

bool PipelineContext::GetContainerControlButtonVisible()
{
    CHECK_NULL_RETURN(rootNode_, false);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetChildren().front());
    CHECK_NULL_RETURN(containerNode, false);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_RETURN(containerPattern, false);
    return containerPattern->GetControlButtonVisible();
}

void PipelineContext::SetWindowContainerColor(const Color& activeColor, const Color& inactiveColor)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        LOGW("Set app icon failed, Window modal is not container.");
        return;
    }
    CHECK_NULL_VOID(rootNode_);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetChildren().front());
    CHECK_NULL_VOID(containerNode);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_VOID(containerPattern);
    containerPattern->SetWindowContainerColor(activeColor, inactiveColor);
}

void PipelineContext::AddFontNodeNG(const WeakPtr<UINode>& node)
{
    if (fontManager_) {
        fontManager_->AddFontNodeNG(node);
    }
}

void PipelineContext::RemoveFontNodeNG(const WeakPtr<UINode>& node)
{
    if (fontManager_) {
        fontManager_->RemoveFontNodeNG(node);
    }
}

void PipelineContext::SetWindowSceneConsumed(bool isConsumed)
{
    isWindowSceneConsumed_ = isConsumed;
}

bool PipelineContext::IsWindowSceneConsumed()
{
    return isWindowSceneConsumed_;
}

void PipelineContext::SetCloseButtonStatus(bool isEnabled)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        return;
    }
    CHECK_NULL_VOID(rootNode_);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetChildren().front());
    CHECK_NULL_VOID(containerNode);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_VOID(containerPattern);
    containerPattern->SetCloseButtonStatus(isEnabled);
}

void PipelineContext::AnimateOnSafeAreaUpdate()
{
    // complete other layout tasks before animation
    FlushUITasks();
    AnimationOption option;
    option.SetCurve(safeAreaManager_->GetSafeAreaCurve());
    AnimationUtils::Animate(option, [weak = WeakClaim(this)]() {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        self->SyncSafeArea(SafeAreaSyncType::SYNC_TYPE_AVOID_AREA);
        self->FlushUITasks();
    });
}

void PipelineContext::HandleSubwindow(bool isShow)
{
    // When the main window is applied to the background,
    // there are sub windows that do not immediately hide, such as Toast floating window
    if (!isShow) {
        overlayManager_->ClearToastInSubwindow();
    }
}

void PipelineContext::AddIsFocusActiveUpdateEvent(
    const RefPtr<FrameNode>& node, const std::function<void(bool)>& eventCallback)
{
    CHECK_NULL_VOID(node);
    auto focusManager = GetOrCreateFocusManager();
    CHECK_NULL_VOID(focusManager);
    focusManager->SetIsFocusActiveUpdateEvent(node->GetId(), eventCallback);
}

void PipelineContext::RemoveIsFocusActiveUpdateEvent(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto focusManager = GetOrCreateFocusManager();
    CHECK_NULL_VOID(focusManager);
    focusManager->RemoveIsFocusActiveUpdateEvent(node->GetId());
}

std::shared_ptr<NavigationController> PipelineContext::GetNavigationController(const std::string& id)
{
    std::lock_guard lock(navigationMutex_);
    auto iter = navigationNodes_.find(id);
    if (iter == navigationNodes_.end()) {
        return nullptr;
    }

    auto navigationGroupNode = iter->second.Upgrade();
    CHECK_NULL_RETURN(navigationGroupNode, nullptr);

    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(navigationPattern, nullptr);
    return navigationPattern->GetNavigationController();
}

void PipelineContext::AddOrReplaceNavigationNode(const std::string& id, const WeakPtr<FrameNode>& node)
{
    std::lock_guard lock(navigationMutex_);
    auto frameNode = node.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto oldId = navigationGroupNode->GetCurId();
    if (!oldId.empty() && navigationNodes_.find(oldId) != navigationNodes_.end()) {
        navigationNodes_.erase(oldId);
    }

    if (!id.empty()) {
        navigationNodes_[id] = node;
    }
}

void PipelineContext::DeleteNavigationNode(const std::string& id)
{
    std::lock_guard lock(navigationMutex_);
    if (!id.empty() && navigationNodes_.find(id) != navigationNodes_.end()) {
        navigationNodes_.erase(id);
    }
}

std::string PipelineContext::GetCurrentExtraInfo()
{
    auto node = activeNode_.Upgrade();
    return node ? node->GetCurrentCustomNodeInfo() : std::string();
}

void PipelineContext::SetCursor(int32_t cursorValue)
{
    if (cursorValue >= 0 && cursorValue <= static_cast<int32_t>(MouseFormat::RUNNING)) {
        auto mouseFormat = static_cast<MouseFormat>(cursorValue);
        auto mouseStyleManager = eventManager_->GetMouseStyleManager();
        CHECK_NULL_VOID(mouseStyleManager);
        mouseStyleManager->SetUserSetCursor(true);
        ChangeMouseStyle(-1, mouseFormat, GetFocusWindowId(),
            false, MouseStyleChangeReason::USER_SET_MOUSESTYLE);
    }
}

void PipelineContext::RestoreDefault(int32_t windowId, MouseStyleChangeReason reason)
{
    ChangeMouseStyle(-1, MouseFormat::DEFAULT, windowId > 0 ? windowId : GetFocusWindowId(),
        false, reason);
    auto mouseStyleManager = eventManager_->GetMouseStyleManager();
    CHECK_NULL_VOID(mouseStyleManager);
    mouseStyleManager->SetUserSetCursor(false);
}

void PipelineContext::FlushAnimationDirtysWhenExist(const AnimationOption& option)
{
    int32_t flushCount = 0;
    bool isDirtyLayoutNodesEmpty = IsDirtyLayoutNodesEmpty();
    while (!isDirtyLayoutNodesEmpty && !IsLayouting() && !isReloading_) {
        if (flushCount >= MAX_FLUSH_COUNT || option.GetIteration() != ANIMATION_REPEAT_INFINITE) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION, "animation: option:%{public}s, isDirtyLayoutNodesEmpty:%{public}d",
                option.ToString().c_str(), isDirtyLayoutNodesEmpty);
            break;
        }
        FlushUITasks(true);
        isDirtyLayoutNodesEmpty = IsDirtyLayoutNodesEmpty();
        flushCount++;
    }
}

void PipelineContext::OpenFrontendAnimation(
    const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& finishCallback)
{
    // push false to show we already open a animation closure.
    pendingFrontendAnimation_.push(false);

    // flush ui tasks before open animation closure.
    if (!isReloading_ && !IsLayouting()) {
        FlushUITasks();
    }
    auto wrapFinishCallback = GetWrappedAnimationCallback(option, finishCallback);
    if (IsFormRenderExceptDynamicComponent()) {
        SetIsFormAnimation(true);
        if (!IsFormAnimationFinishCallback()) {
            SetFormAnimationStartTime(GetMicroTickCount());
        }
    }
    FlushAnimationDirtysWhenExist(option);
    AnimationUtils::OpenImplicitAnimation(option, curve, wrapFinishCallback);
}

void PipelineContext::CloseFrontendAnimation()
{
    if (pendingFrontendAnimation_.empty()) {
        return;
    }

    if (pendingFrontendAnimation_.top()) {
        if (!isReloading_ && !IsLayouting()) {
            FlushUITasks();
        } else if (IsLayouting()) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION,
                "IsLayouting, CloseFrontendAnimation has tasks not flushed, maybe some layout animation not generated");
        }
    }
    if (!pendingFrontendAnimation_.empty()) {
        pendingFrontendAnimation_.pop();
    }
    AnimationUtils::CloseImplicitAnimation();
}

bool PipelineContext::IsDragging() const
{
    if (!dragDropManager_) {
        return false;
    }
    bool isDragging = dragDropManager_->IsDragging();
    isDragging = (isDragging || dragDropManager_->IsMSDPDragging());
    return isDragging;
}

void PipelineContext::SetIsDragging(bool isDragging)
{
    if (!eventManager_) {
        return;
    }
    eventManager_->SetIsDragging(isDragging);
}

void PipelineContext::ResetDragging()
{
    CHECK_NULL_VOID(dragDropManager_);
    dragDropManager_->ResetDragging();
}

void PipelineContext::SetContainerModalTitleVisible(bool customTitleSettedShow, bool floatingTitleSettedShow)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        return;
    }
    CHECK_NULL_VOID(rootNode_);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetFirstChild());
    CHECK_NULL_VOID(containerNode);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_VOID(containerPattern);
    containerPattern->SetContainerModalTitleVisible(customTitleSettedShow, floatingTitleSettedShow);
    customTitleSettedShow_ = customTitleSettedShow;
}

void PipelineContext::SetContainerModalTitleHeight(int32_t height)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        return;
    }
    CHECK_NULL_VOID(rootNode_);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetFirstChild());
    CHECK_NULL_VOID(containerNode);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_VOID(containerPattern);
    containerPattern->SetContainerModalTitleHeight(height);
}

int32_t PipelineContext::GetContainerModalTitleHeight()
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        return -1;
    }
    CHECK_NULL_RETURN(rootNode_, -1);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetFirstChild());
    CHECK_NULL_RETURN(containerNode, -1);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_RETURN(containerPattern, -1);
    return containerPattern->GetContainerModalTitleHeight();
}

RefPtr<FrameNode> PipelineContext::GetContainerModalNode()
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        return nullptr;
    }
    CHECK_NULL_RETURN(rootNode_, nullptr);
    return AceType::DynamicCast<FrameNode>(rootNode_->GetFirstChild());
}

void PipelineContext::DoKeyboardAvoidAnimate(const KeyboardAnimationConfig& keyboardAnimationConfig,
    float keyboardHeight, const std::function<void()>& func)
{
    if (isDoKeyboardAvoidAnimate_) {
        AnimationOption option = AnimationUtil::CreateKeyboardAnimationOption(keyboardAnimationConfig, keyboardHeight);
        Animate(option, option.GetCurve(), func, [weak = WeakClaim(this)]() {
            auto pipeline = weak.Upgrade();
            CHECK_NULL_VOID(pipeline);
            CHECK_NULL_VOID(pipeline->textFieldManager_);
            auto textFieldManagerNg = DynamicCast<TextFieldManagerNG>(pipeline->textFieldManager_);
            CHECK_NULL_VOID(textFieldManagerNg);
            textFieldManagerNg->OnAfterAvoidKeyboard(false);
        });
    } else {
        func();
    }
}

Dimension PipelineContext::GetCustomTitleHeight()
{
    auto containerModal = GetContainerModalNode();
    CHECK_NULL_RETURN(containerModal, Dimension());
    return containerModal->GetPattern<ContainerModalPattern>()->GetCustomTitleHeight();
}

bool PipelineContext::GetContainerModalButtonsRect(RectF& containerModal, RectF& buttons)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        return false;
    }
    CHECK_NULL_RETURN(rootNode_, false);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetFirstChild());
    CHECK_NULL_RETURN(containerNode, false);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_RETURN(containerPattern, false);
    return containerPattern->GetContainerModalButtonsRect(containerModal, buttons);
}

void PipelineContext::SubscribeContainerModalButtonsRectChange(
    std::function<void(RectF& containerModal, RectF& buttons)>&& callback)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        return;
    }
    CHECK_NULL_VOID(rootNode_);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetFirstChild());
    CHECK_NULL_VOID(containerNode);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_VOID(containerPattern);
    containerPattern->SubscribeContainerModalButtonsRectChange(std::move(callback));
}

void PipelineContext::GetWindowPaintRectWithoutMeasureAndLayout(RectInt& rect)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        return;
    }
    CHECK_NULL_VOID(rootNode_);
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetFirstChild());
    CHECK_NULL_VOID(containerNode);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_VOID(containerPattern);
    containerPattern->GetWindowPaintRectWithoutMeasureAndLayout(rect);
}

const RefPtr<PostEventManager>& PipelineContext::GetPostEventManager()
{
    return postEventManager_;
}

const SerializedGesture& PipelineContext::GetSerializedGesture() const
{
    return serializedGesture_;
}

bool PipelineContext::PrintVsyncInfoIfNeed() const
{
    if (dumpFrameInfos_.empty()) {
        return false;
    }
    auto lastFrameInfo = dumpFrameInfos_.back();
    const uint64_t timeout = 1000000000; // unit is ns, 1s
    if (lastFrameInfo.frameRecvTime_ < window_->GetLastRequestVsyncTime() &&
        static_cast<uint64_t>(GetSysTimestamp()) - window_->GetLastRequestVsyncTime() >= timeout) {
        LOGW("lastRequestVsyncTime is %{public}" PRIu64 ", now time is %{public}" PRId64
             ", timeout, window foreground:%{public}d, lastReceiveVsync info:%{public}s",
            window_->GetLastRequestVsyncTime(), GetSysTimestamp(), onShow_, lastFrameInfo.GetTimeInfo().c_str());
        return true;
    }
    return false;
}

void PipelineContext::StopWindowAnimation()
{
    isWindowAnimation_ = false;
    if (taskScheduler_ && !taskScheduler_->IsPredictTaskEmpty()) {
        RequestFrame();
    }
    OnRotationAnimationEnd();
}

void PipelineContext::AddSyncGeometryNodeTask(std::function<void()>&& task)
{
    taskScheduler_->AddSyncGeometryNodeTask(std::move(task));
}

void PipelineContext::FlushSyncGeometryNodeTasks()
{
    taskScheduler_->FlushSyncGeometryNodeTasks();
}

void PipelineContext::SetUIExtensionImeShow(bool imeShow)
{
    textFieldManager_->SetUIExtensionImeShow(imeShow);
}

void PipelineContext::SetOverlayNodePositions(std::vector<Ace::RectF> rects)
{
    overlayNodePositions_ = rects;
}

void PipelineContext::SetCallBackNode(const WeakPtr<NG::FrameNode>& node)
{
    auto frameNode = node.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(node);
}

std::vector<Ace::RectF> PipelineContext::GetOverlayNodePositions()
{
    return overlayNodePositions_;
}

void PipelineContext::RegisterOverlayNodePositionsUpdateCallback(
    const std::function<void(std::vector<Ace::RectF>)>&& callback)
{
    overlayNodePositionUpdateCallback_ = std::move(callback);
}

void PipelineContext::TriggerOverlayNodePositionsUpdateCallback(std::vector<Ace::RectF> rects)
{
    if (overlayNodePositionUpdateCallback_) {
        overlayNodePositionUpdateCallback_(rects);
    }
}

void PipelineContext::CheckNeedUpdateBackgroundColor(Color& color)
{
    if (!isFormRender_ || (renderingMode_ != RENDERING_SINGLE_COLOR)) {
        return;
    }
    Color replaceColor = color.ChangeAlpha(SINGLECOLOR_UPDATE_ALPHA);
    color = replaceColor;
}

bool PipelineContext::CheckNeedDisableUpdateBackgroundImage()
{
    if (!isFormRender_ || (renderingMode_ != RENDERING_SINGLE_COLOR && !enableBlurBackground_)) {
        return false;
    }
    return true;
}

ColorMode PipelineContext::GetColorMode() const
{
    auto container = Container::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, ColorMode::LIGHT);
    return container->GetColorMode();
}

void PipelineContext::ChangeDarkModeBrightness()
{
    auto windowManager = GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    auto mode = windowManager->GetWindowMode();
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto percent = SystemProperties::GetDarkModeBrightnessPercent();
    auto stage = stageManager_->GetStageNode();
    CHECK_NULL_VOID(stage);
    auto renderContext = stage->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    CalcDimension dimension;
    dimension.SetValue(1);
    if (container->GetColorMode() == ColorMode::DARK && appBgColor_.ColorToString().compare("#FF000000") == 0 &&
        mode != WindowMode::WINDOW_MODE_FULLSCREEN && !container->IsUIExtensionWindow() &&
        !container->IsDynamicRender() && !container->IsFormRender() && !IsJsCard()) {
        if (!onFocus_ && mode == WindowMode::WINDOW_MODE_FLOATING) {
            dimension.SetValue(1 + percent.second);
        } else {
            dimension.SetValue(1 + percent.first);
        }
    }
    renderContext->UpdateFrontBrightness(dimension);
}

bool PipelineContext::IsContainerModalVisible()
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        return false;
    }
    auto windowManager = GetWindowManager();
    bool isFloatingWindow = windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
    return isShowTitle_ && isFloatingWindow && customTitleSettedShow_;
}

void PipelineContext::PreLayout(uint64_t nanoTimestamp, uint32_t frameCount)
{
    FlushVsync(nanoTimestamp, frameCount);
}

void PipelineContext::CheckAndLogLastReceivedTouchEventInfo(int32_t eventId, TouchType type)
{
    eventManager_->CheckAndLogLastReceivedTouchEventInfo(eventId, type);
}

void PipelineContext::CheckAndLogLastConsumedTouchEventInfo(int32_t eventId, TouchType type)
{
    eventManager_->CheckAndLogLastConsumedTouchEventInfo(eventId, type);
}

void PipelineContext::CheckAndLogLastReceivedMouseEventInfo(int32_t eventId, MouseAction action)
{
    eventManager_->CheckAndLogLastReceivedMouseEventInfo(eventId, action);
}

void PipelineContext::CheckAndLogLastConsumedMouseEventInfo(int32_t eventId, MouseAction action)
{
    eventManager_->CheckAndLogLastConsumedMouseEventInfo(eventId, action);
}

void PipelineContext::CheckAndLogLastReceivedAxisEventInfo(int32_t eventId, AxisAction action)
{
    eventManager_->CheckAndLogLastReceivedAxisEventInfo(eventId, action);
}

void PipelineContext::CheckAndLogLastConsumedAxisEventInfo(int32_t eventId, AxisAction action)
{
    eventManager_->CheckAndLogLastConsumedAxisEventInfo(eventId, action);
}

void PipelineContext::FlushFrameCallback(uint64_t nanoTimestamp)
{
    if (!frameCallbackFuncs_.empty()) {
        decltype(frameCallbackFuncs_) tasks(std::move(frameCallbackFuncs_));
        for (const auto& frameCallbackFunc : tasks) {
            frameCallbackFunc(nanoTimestamp);
        }
    }
}

void PipelineContext::FlushFrameCallbackFromCAPI(uint64_t nanoTimestamp, uint32_t frameCount)
{
    if (!frameCallbackFuncsFromCAPI_.empty()) {
        decltype(frameCallbackFuncsFromCAPI_) tasks;
        std::swap(tasks, frameCallbackFuncsFromCAPI_);
        for (const auto& frameCallbackFuncFromCAPI : tasks) {
            frameCallbackFuncFromCAPI(nanoTimestamp, frameCount);
        }
    }
}

void PipelineContext::RegisterTouchEventListener(const std::shared_ptr<ITouchEventCallback>& listener)
{
    if (!listener) {
        return;
    }
    listenerVector_.emplace_back(listener);
}

void PipelineContext::UnregisterTouchEventListener(const WeakPtr<NG::Pattern>& pattern)
{
    for (auto iter = listenerVector_.begin(); iter != listenerVector_.end();) {
        auto patternPtr = (*iter)->GetPatternFromListener();
        if (patternPtr.Invalid() || patternPtr == pattern) {
            iter = listenerVector_.erase(iter);
        } else {
            iter++;
        }
    }
}

void PipelineContext::RegisterFocusCallback()
{
    focusManager_->AddFocusChangeCallback([](const WeakPtr<FocusHub>& last, const RefPtr<FocusHub>& current,
        FocusReason focusReason) {
        CHECK_NULL_VOID(current);
        auto node = current->GetFrameNode();
        CHECK_NULL_VOID(node);
        InputMethodManager::GetInstance()->OnFocusNodeChange(node, focusReason);
    });
}

void PipelineContext::GetInspectorTree(bool onlyNeedVisible)
{
    if (onlyNeedVisible) {
        auto root = JsonUtil::Create(true);
        RefPtr<NG::FrameNode> topNavNode;
        uiTranslateManager_->FindTopNavDestination(rootNode_, topNavNode);
        if (topNavNode != nullptr) {
            topNavNode->DumpSimplifyTree(0, root);
        } else {
            rootNode_->DumpSimplifyTree(0, root);
        }
        auto json = root->ToString();
        json.erase(std::remove(json.begin(), json.end(), ' '), json.end());
        auto res = JsonUtil::Create(true);
        res->Put("0", json.c_str());
        UiSessionManager::GetInstance()->ReportInspectorTreeValue(res->ToString());
    } else {
        bool needThrow = false;
        NG::InspectorFilter filter;
        filter.AddFilterAttr("content");
        auto nodeInfos = NG::Inspector::GetInspector(false, filter, needThrow);
        UiSessionManager::GetInstance()->AddValueForTree(0, nodeInfos);
        rootNode_->GetInspectorValue();
    }
}

void PipelineContext::AddFrameNodeChangeListener(const WeakPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node.Upgrade());
    if (std::find(changeInfoListeners_.begin(), changeInfoListeners_.end(), node) == changeInfoListeners_.end()) {
        changeInfoListeners_.push_back(node);
    }
}

void PipelineContext::RemoveFrameNodeChangeListener(int32_t nodeId)
{
    if (changeInfoListeners_.empty()) {
        return;
    }
    changeInfoListeners_.remove_if([nodeId](const WeakPtr<FrameNode>& node) {
        return !node.Upgrade() || nodeId == node.Upgrade()->GetId();
    });
}

bool PipelineContext::AddChangedFrameNode(const WeakPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node.Upgrade(), false);
    if (changeInfoListeners_.empty()) {
        return false;
    }
    if (std::find(changedNodes_.begin(), changedNodes_.end(), node) == changedNodes_.end()) {
        changedNodes_.push_back(node);
    }
    return true;
}

void PipelineContext::RemoveChangedFrameNode(int32_t nodeId)
{
    if (changedNodes_.empty()) {
        return;
    }
    changedNodes_.remove_if([nodeId](const WeakPtr<FrameNode>& node) {
        return !node.Upgrade() || nodeId == node.Upgrade()->GetId();
    });
}

void PipelineContext::FlushNodeChangeFlag()
{
    ACE_FUNCTION_TRACE();
    if (!changeInfoListeners_.empty()) {
        for (const auto& it : changeInfoListeners_) {
            auto listener = it.Upgrade();
            if (listener) {
                listener->ProcessFrameNodeChangeFlag();
            }
        }
    }
    CleanNodeChangeFlag();
}

void PipelineContext::CleanNodeChangeFlag()
{
    auto cleanNodes = std::move(changedNodes_);
    for (const auto& it : cleanNodes) {
        auto changeNode = it.Upgrade();
        if (changeNode) {
            changeNode->ClearChangeInfoFlag();
        }
    }
}

void PipelineContext::NotifyAllWebPattern(bool isRegister)
{
    rootNode_->NotifyWebPattern(isRegister);
}

void PipelineContext::NotifyColorModeChange(uint32_t colorMode)
{
    AnimationOption option;
    const int32_t duration = 400;
    option.SetDuration(duration);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        option,
        [weakPipelineContext = WeakClaim(this), weak = WeakPtr<FrameNode>(rootNode_),
            colorMode, rootColorMode = GetColorMode()]() {
            auto pipeline = weakPipelineContext.Upgrade();
            CHECK_NULL_VOID(pipeline);
            auto rootNode = weak.Upgrade();
            CHECK_NULL_VOID(rootNode);
            pipeline->SetIsReloading(true);
            rootNode->SetDarkMode(rootColorMode == ColorMode::DARK);
            rootNode->NotifyColorModeChange(colorMode);
            pipeline->SetIsReloading(false);
            pipeline->FlushUITasks();
        },
        [weak = WeakClaim(this)]() {
            auto pipeline = weak.Upgrade();
            CHECK_NULL_VOID(pipeline);
            pipeline->OnFlushReloadFinish();
        });
    CHECK_NULL_VOID(stageManager_);
    auto stage = stageManager_->GetStageNode();
    CHECK_NULL_VOID(stage);
    auto renderContext = stage->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateWindowBlur();
}

void PipelineContext::UpdateHalfFoldHoverStatus(int32_t windowWidth, int32_t windowHeight)
{
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_THIRTEEN)) {
        isHalfFoldHoverStatus_ = false;
        return;
    }
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    bool isFoldable = container->IsFoldable();
    if (!isFoldable && !SystemProperties::IsSmallFoldProduct()) {
        isHalfFoldHoverStatus_ = false;
        return;
    }
    auto displayInfo = container->GetDisplayInfo();
    CHECK_NULL_VOID(displayInfo);
    auto windowManager = GetWindowManager();
    auto windowMode = windowManager->GetWindowMode();
    auto isHalfFolded = displayInfo->GetFoldStatus() == FoldStatus::HALF_FOLD;
    auto displayWidth = displayInfo->GetWidth();
    auto displayHeight = displayInfo->GetHeight();
    auto isFullScreen = windowMode == WindowMode::WINDOW_MODE_FULLSCREEN ||
        (NearEqual(displayWidth, windowWidth) && NearEqual(displayHeight, windowHeight));
    if (!isFullScreen || !isHalfFolded) {
        isHalfFoldHoverStatus_ = false;
        return;
    }
    auto rotation = displayInfo->GetRotation();
    if (SystemProperties::IsSmallFoldProduct()) {
        isHalfFoldHoverStatus_ = rotation == Rotation::ROTATION_0 || rotation == Rotation::ROTATION_180;
    } else {
        isHalfFoldHoverStatus_ = rotation == Rotation::ROTATION_90 || rotation == Rotation::ROTATION_270;
    }
}

void PipelineContext::OnHalfFoldHoverChangedCallback()
{
    auto tempHalfFoldHoverChangedCallbackMap = halfFoldHoverChangedCallbackMap_;
    for (auto&& [id, callback] : tempHalfFoldHoverChangedCallbackMap) {
        if (callback) {
            callback(isHalfFoldHoverStatus_);
        }
    }
}

void PipelineContext::StartFoldStatusDelayTask(FoldStatus foldStatus)
{
    if (foldStatusDelayTask_) {
        foldStatusDelayTask_.Cancel();
    }
    foldStatusDelayTask_.Reset([weak = WeakClaim(this)]() {
        auto context = weak.Upgrade();
        CHECK_NULL_VOID(context);
        context->UpdateHalfFoldHoverProperty(context->GetRootWidth(), context->GetRootHeight());
        context->OnHalfFoldHoverChangedCallback();
    });
    taskExecutor_->PostDelayedTask(
        foldStatusDelayTask_, TaskExecutor::TaskType::UI, DELAY_TIME, "ArkUIHalfFoldHoverStatusChange");
}

std::string PipelineContext::GetResponseRegion(const RefPtr<FrameNode>& rootNode)
{
    CHECK_NULL_RETURN(rootNode, "");
    std::vector<RectF> responseRegionList;
    auto window = GetCurrentWindowRect();
    RectF windowRect{window.Left(), window.Top(), window.Width(), window.Height()};
    rootNode->GetResponseRegionListByTraversal(responseRegionList, windowRect);
    std::string responseRegionStrOrigin;
    std::string responseRegionStrFilter;
    for (const auto& rect : responseRegionList) {
        int32_t left = static_cast<int32_t>(rect.Left());
        int32_t top = static_cast<int32_t>(rect.Top());
        int32_t width = static_cast<int32_t>(rect.Width());
        int32_t height = static_cast<int32_t>(rect.Height());
        int32_t right = static_cast<int32_t>(rect.Right());
        int32_t bottom = static_cast<int32_t>(rect.Bottom());
        std::string rectStr = std::to_string(left) + "," +
                              std::to_string(top) + "," +
                              std::to_string(right) + "," +
                              std::to_string(bottom);

        responseRegionStrOrigin += rectStr + "#";
        if (thpExtraMgr_ && width <= thpExtraMgr_->GetWidth() && height <= thpExtraMgr_->GetHeight()) {
            responseRegionStrFilter += rectStr + "#";
        }
    }
    if (!responseRegionStrFilter.empty()) {
        responseRegionStrFilter.pop_back();
    }
    LOGD("THP_UpdateViewsLocation origin responseRegion = %{public}s", responseRegionStrOrigin.c_str());
    return responseRegionStrFilter;
}

void PipelineContext::NotifyResponseRegionChanged(const RefPtr<FrameNode>& rootNode)
{
    ACE_FUNCTION_TRACE();
    if (!thpExtraMgr_) {
        return;
    }
    std::string responseRegion = GetResponseRegion(rootNode);
    std::string parameters = "thp#Location#" + responseRegion;
    LOGD("THP_UpdateViewsLocation responseRegion = %{public}s", parameters.c_str());
    auto task = [weak = WeakClaim(this), parameters]() {
        ACE_SCOPED_TRACE("ThpExtraRunCommand");
        auto pipeline = weak.Upgrade();
        CHECK_NULL_VOID(pipeline);
        CHECK_NULL_VOID(pipeline->thpExtraMgr_);
        pipeline->thpExtraMgr_->ThpExtraRunCommand("THP_UpdateViewsLocation", parameters.c_str());
    };
    BackgroundTaskExecutor::GetInstance().PostTask(task);
}
#if defined(SUPPORT_TOUCH_TARGET_TEST)

bool PipelineContext::OnTouchTargetHitTest(const TouchEvent& point, bool isSubPipe, const std::string& target)
{
    auto scalePoint = point.CreateScalePoint(GetViewScale());
    if (scalePoint.type == TouchType::DOWN) {
        TouchRestrict touchRestrict { TouchRestrict::NONE };
        touchRestrict.sourceType = point.sourceType;
        touchRestrict.touchEvent = point;
        bool isTouchTarget = eventManager_->TouchTargetHitTest(
            scalePoint, rootNode_, touchRestrict, GetPluginEventOffset(), viewScale_, isSubPipe, target);
        return isTouchTarget;
    }
    return false;
}
#endif

bool PipelineContext::CatchInteractiveAnimations(const std::function<void()>& animationCallback)
{
    CHECK_NULL_RETURN(navigationMgr_, false);
    if (navigationMgr_->IsInteractive()) {
        return navigationMgr_->AddInteractiveAnimation(animationCallback);
    }
    return false;
}

bool PipelineContext::CheckThreadSafe()
{
    CHECK_NULL_RETURN(taskExecutor_, true);
    if (!isFormRender_ && !taskExecutor_->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
        LogBacktrace();
        return false;
    }
    return true;
}

uint64_t PipelineContext::AdjustVsyncTimeStamp(uint64_t nanoTimestamp)
{
    auto period = window_->GetVSyncPeriod();
    if (period > 0 && recvTime_ > static_cast<int64_t>(nanoTimestamp) + MAX_MISS_COUNT * period) {
        return static_cast<uint64_t>(recvTime_ - ((recvTime_ - static_cast<int64_t>(nanoTimestamp)) % period));
    }
    return nanoTimestamp;
}

bool PipelineContext::FlushModifierAnimation(uint64_t nanoTimestamp)
{
    auto animationTimeStamp = AdjustVsyncTimeStamp(nanoTimestamp);
    if (animationTimeStamp < animationTimeStamp_) {
        ACE_SCOPED_TRACE("skip ModifierAnimation");
        TAG_LOGW(AceLogTag::ACE_ANIMATION,
            "Time decreases, skip ModifierAnimation, lastTime:%{public}" PRIu64 ", nowTime:%{public}" PRIu64,
            animationTimeStamp_, animationTimeStamp);
        return true;
    }
    animationTimeStamp_ = animationTimeStamp;
    return window_->FlushAnimation(animationTimeStamp);
}

void PipelineContext::RegisterAttachedNode(UINode* uiNode)
{
    attachedNodeSet_.emplace(WeakClaim(uiNode));
}

void PipelineContext::RemoveAttachedNode(UINode* uiNode)
{
    attachedNodeSet_.erase(WeakClaim(uiNode));
}

ScopedLayout::ScopedLayout(PipelineContext* pipeline)
{
    if (!pipeline) {
        return;
    }
    // save flag before measure
    pipeline_ = pipeline;
    isLayouting_ = pipeline_->IsLayouting();
    pipeline_->SetIsLayouting(true);
}

ScopedLayout::~ScopedLayout()
{
    if (!pipeline_) {
        return;
    }
    // set layout flag back
    pipeline_->SetIsLayouting(isLayouting_);
}

std::string PipelineContext::GetBundleName()
{
    auto container = Container::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, "");
    return container->GetBundleName();
}

std::string PipelineContext::GetModuleName()
{
    auto container = Container::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, "");
    return container->GetModuleName();
}

void PipelineContext::SetEnableSwipeBack(bool isEnable)
{
    CHECK_NULL_VOID(rootNode_);
    auto rootPattern = rootNode_->GetPattern<RootPattern>();
    CHECK_NULL_VOID(rootPattern);
    rootPattern->SetEnableSwipeBack(isEnable);
}

void PipelineContext::SetHostParentOffsetToWindow(const Offset& offset)
{
    lastHostParentOffsetToWindow_ = offset;
    CHECK_NULL_VOID(rootNode_);
    auto renderContext = rootNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->RequestNextFrame();
}

RefPtr<Kit::UIContext> PipelineContext::GetUIContext()
{
    if (uiContextImpl_) {
        return uiContextImpl_;
    }
    uiContextImpl_ = AceType::MakeRefPtr<Kit::UIContextImpl>(this);
    return uiContextImpl_;
}

void PipelineContext::GetAllPixelMap()
{
    CHECK_NULL_VOID(stageManager_);
    auto pageNode = stageManager_->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    CHECK_NULL_VOID(uiTranslateManager_);
    uiTranslateManager_->GetAllPixelMap(pageNode);
}

void PipelineContext::SetDisplayWindowRectInfo(const Rect& displayWindowRectInfo)
{
    auto offSetPosX_ = displayWindowRectInfo_.Left() - displayWindowRectInfo.Left();
    auto offSetPosY_ = displayWindowRectInfo_.Top() - displayWindowRectInfo.Top();
    if (!NearZero(offSetPosX_) || !NearZero(offSetPosY_)) {
        if (lastMouseEvent_) {
            lastMouseEvent_->x += offSetPosX_;
            lastMouseEvent_->y += offSetPosY_;
        }
    }
    displayWindowRectInfo_ = displayWindowRectInfo;
}

void PipelineContext::SetIsTransFlag(bool result)
{
    isTransFlag_ = result;
}

void PipelineContext::FlushMouseEventForHover()
{
    if (!isTransFlag_ || !lastMouseEvent_ || lastMouseEvent_->sourceType != SourceType::MOUSE ||
        lastMouseEvent_->action == MouseAction::PRESS || lastSourceType_ == SourceType::TOUCH) {
        return;
    }
    CHECK_NULL_VOID(rootNode_);
    if (lastMouseEvent_->isMockWindowTransFlag || windowSizeChangeReason_ == WindowSizeChangeReason::DRAG) {
        return;
    }
    CHECK_RUN_ON(UI);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    ACE_SCOPED_TRACE("FlushMouseEventForHover x:%f y:%f", lastMouseEvent_->x, lastMouseEvent_->y);
    MouseEvent event;
    event.x = lastMouseEvent_->x;
    event.y = lastMouseEvent_->y;
    event.screenX = lastMouseEvent_->screenX;
    event.screenY = lastMouseEvent_->screenY;
    event.button = lastMouseEvent_->button;
    event.deviceId = lastMouseEvent_->deviceId;
    event.sourceTool = lastMouseEvent_->sourceTool;
    event.sourceType = lastMouseEvent_->sourceType;
    event.action = lastMouseEvent_->action;
    event.time = lastMouseEvent_->time;
    event.touchEventId = lastMouseEvent_->touchEventId;
    event.mockFlushEvent = true;
    event.pointerEvent = lastMouseEvent_->pointerEvent;
    TAG_LOGD(AceLogTag::ACE_MOUSE,
        "the mock mouse event action: %{public}d x: %{public}f y: %{public}f", event.action, event.x, event.y);
    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = event.sourceType;
    touchRestrict.hitTestType = SourceType::MOUSE;
    touchRestrict.inputEventType = InputEventType::MOUSE_BUTTON;
    if (container->IsSceneBoardWindow()) {
        eventManager_->MouseTest(event, lastMouseEvent_->node.Upgrade(), touchRestrict);
    } else {
        eventManager_->MouseTest(event, rootNode_, touchRestrict);
    }
    eventManager_->DispatchMouseHoverEventNG(event);
    eventManager_->DispatchMouseHoverAnimationNG(event, true);
}

void PipelineContext::HandleTouchHoverOut(const TouchEvent& point)
{
    if (point.sourceTool != SourceTool::FINGER || NearZero(point.force)) {
        return;
    }
    lastSourceType_ = SourceType::TOUCH;
    CHECK_RUN_ON(UI);
    eventManager_->CleanHoverStatusForDragBegin();
}

void PipelineContext::FlushMouseEventInVsync()
{
    auto mouseEventSize = mouseEvents_.size();
    if (!mouseEvents_.empty()) {
        FlushMouseEvent();
        isNeedFlushMouseEvent_ = MockFlushEventType::NONE;
        mouseEvents_.clear();
    } else if (isNeedFlushMouseEvent_ == MockFlushEventType::REJECT ||
               isNeedFlushMouseEvent_ == MockFlushEventType::EXECUTE) {
        FlushMouseEventVoluntarily();
        isNeedFlushMouseEvent_ = MockFlushEventType::NONE;
    }
    if (lastMouseEvent_ && isTransFlag_ && (mouseEventSize == 0 || lastMouseEvent_->mockFlushEvent)) {
        FlushMouseEventForHover();
    }
    isTransFlag_ = false;
    windowSizeChangeReason_ = WindowSizeChangeReason::UNDEFINED;
}

void PipelineContext::SetWindowSizeChangeReason(WindowSizeChangeReason reason)
{
    windowSizeChangeReason_ = reason;
}

void PipelineContext::OnDumpInjection(const std::vector<std::string>& params) const
{
    int32_t nodeId = StringUtils::StringToInt(params[PARAM_NUM], -1);
    if (nodeId < 0) {
        return;
    }
    auto frameNode = DynamicCast<FrameNode>(ElementRegister::GetInstance()->GetUINodeById(nodeId));
    CHECK_NULL_VOID(frameNode);
    frameNode->OnRecvCommand(params[1]);
}

void PipelineContext::OnRotationAnimationEnd()
{
    for (auto&& [id, callback] : rotationEndCallbackMap_) {
        if (callback) {
            callback();
        }
    }
}

std::shared_ptr<Rosen::RSUIDirector> PipelineContext::GetRSUIDirector()
{
#ifdef ENABLE_ROSEN_BACKEND
    auto window = GetWindow();
    if (window) {
        return window->GetRSUIDirector();
    }
#endif
    return nullptr;
}

const RefPtr<NodeRenderStatusMonitor>& PipelineContext::GetNodeRenderStatusMonitor()
{
    if (!nodeRenderStatusMonitor_) {
        nodeRenderStatusMonitor_ = AceType::MakeRefPtr<NodeRenderStatusMonitor>();
    }
    return nodeRenderStatusMonitor_;
}

void PipelineContext::RemoveNodeFromDirtyRenderNode(int32_t nodeId, int32_t pageId)
{
    taskScheduler_->RemoveNodeFromDirtyRender(nodeId, pageId);
}
 
void PipelineContext::GetRemovedDirtyRenderAndErase(uint32_t id)
{
    taskScheduler_->RemoveDirtyRenderNodes(id);
}
} // namespace OHOS::Ace::NG
