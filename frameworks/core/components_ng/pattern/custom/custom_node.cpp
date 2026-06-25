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

#include "core/components_ng/pattern/custom/custom_node.h"

#include "base/log/ace_checker.h"
#include "base/log/ace_performance_check.h"
#include "base/log/ace_performance_monitor.h"
#include "base/log/dump_log.h"
#include "base/thread/task_executor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace {
constexpr int64_t CACHE_TASK_DELAY_TIME = 2000000000;
constexpr int32_t MEMORY_LEVEL_LOW = 1;
constexpr int32_t MEMORY_LEVEL_CRITICAL = 2;
}

namespace OHOS::Ace::NG {
RefPtr<CustomNode> CustomNode::CreateCustomNode(int32_t nodeId, const std::string& viewKey)
{
    ACE_UINODE_TRACE(nodeId);
    auto node = MakeRefPtr<CustomNode>(nodeId, viewKey);
    ElementRegister::GetInstance()->AddUINode(node);
    return node;
}

void CustomNode::Build(std::shared_ptr<std::list<ExtraInfo>> extraInfos)
{
    Render();
    if (extraInfos) {
        extraInfos_ = *extraInfos;
    }
    UINode::Build(extraInfos);
}

void CustomNode::OnAttachToMainTree(bool val)
{
    UINode::OnAttachToMainTree(val);
    auto memopt = GetMemOpt();
    SetStaMemopt(memopt);
    if (staReusableMemOptStrategy_ == StaReusableMemOptStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION) {
        StartMemOpt();
    }
}

bool CustomNode::Render(int64_t deadline)
{
    // NOTE: this function will be re-enter, we need backup needMarkParent_ first and restore it later.
    bool needMarkParentBak = needMarkParent_;
    needMarkParent_ = false;
    if (renderFunction_) {
        RenderFunction renderFunction = nullptr;
        std::swap(renderFunction, renderFunction_);
        if (!CheckFireOnAppear()) {
            ACE_SCOPED_TRACE("CustomNode:OnAppear");
            FireOnAppear();
            FireTriggerLifecycleFunc(LifeCycleEvent::ON_APPEAR);
            if (deadline > 0 && GetSysTimestamp() > deadline) {
                std::swap(renderFunction, renderFunction_);
                return false;
            }
        }
        {
            COMPONENT_CREATION_DURATION();
            std::string reuseId = GetReuseId().empty() ? "-1" : GetReuseId();
            std::string parentInfo = "-1";
            if (SystemProperties::GetDynamicDetectionTraceEnabled()) {
                auto customParent = FindParentCustomNode();
                if (customParent) {
                    parentInfo = customParent->GetJSViewName() + "[" + std::to_string(customParent->GetId()) + "]";
                }
            }
            ACE_SCOPED_TRACE(
                "CustomNode:BuildItem [%s][self:%d][parent:%d][frameRound:%d][reuseId:%s][parentCustomNode:%s]",
                GetJSViewName().c_str(), GetId(), GetParent() ? GetParent()->GetId() : 0,
                prebuildFrameRounds_, reuseId.c_str(), parentInfo.c_str());
            ScopedViewStackProcessor scopedViewStackProcessor(prebuildViewStackProcessor_);
            auto parent = GetParent();
            bool parentNeedExportTexture = parent ? parent->IsNeedExportTexture() : false;
            ViewStackProcessor::GetInstance()->SetIsExportTexture(parentNeedExportTexture || IsNeedExportTexture());
            bool isTimeout = false;
            auto child = renderFunction(deadline, isTimeout);
            if (isTimeout) {
                prebuildFrameRounds_++;
                std::swap(renderFunction, renderFunction_);
                scopedViewStackProcessor.SwapViewStackProcessor(prebuildViewStackProcessor_);
                return false;
            }
            if (child) {
                child->MountToParent(Claim(this));
            }
        }
        NodeDidBuild();
    }
    {
        FireRecycleRenderFunc();
    }
    if (AceChecker::IsPerformanceCheckEnabled()) {
        auto child = GetFirstChild();
        if (child) {
            AceScopedPerformanceCheck::UpdateRecordPath(child->GetFilePath());
            AceScopedPerformanceCheck::ReportAllRecord();
        }
    }
    needMarkParent_ = needMarkParentBak;
    return true;
}

void CustomNode::NodeDidBuild()
{
    ACE_SCOPED_TRACE("CustomNode::DidBuild");
    FireTriggerLifecycleFunc(LifeCycleEvent::ON_BUILD);
    FireDidBuild();
    isDidBuild_ = true;
}

void CustomNode::FireCustomDisappear()
{
    if (!CheckFireOnAppear()) {
        FireOnAppear();
        FireDidBuild();
    }
    FireOnDisappear();
    Reset();
    UINode::FireCustomDisappear();
}

// used in HotReload to update root view @Component
void CustomNode::FlushReload()
{
    ResetNode();
    Build(nullptr);
}

void CustomNode::ResetNode()
{
    CHECK_NULL_VOID(completeReloadFunc_);
    Clean();
    renderFunction_ = completeReloadFunc_;
    executeFireOnAppear_ = false;
}

bool CustomNode::RenderCustomChild(int64_t deadline)
{
    if (GetSysTimestamp() > deadline) {
        return false;
    }
    if (!Render(deadline)) {
        return false;
    }
    return UINode::RenderCustomChild(deadline);
}

void CustomNode::SetJSViewActive(bool active, bool isLazyForEachNode, bool isReuse)
{
    if (GetJsActive() != active) {
        SetJsActive(active);
        FireSetActiveFunc(active, isReuse);
    }
}

void CustomNode::AdjustLayoutWrapperTree(const RefPtr<LayoutWrapperNode>& parent, bool forceMeasure, bool forceLayout)
{
    if (parent->GetHostTag() != V2::TAB_CONTENT_ITEM_ETS_TAG) {
        Render();
        UINode::AdjustLayoutWrapperTree(parent, forceMeasure, forceLayout);
        return;
    }

    if (!renderFunction_ && !HasRecycleRenderFunc()) {
        UINode::AdjustLayoutWrapperTree(parent, forceMeasure, forceLayout);
        return;
    }

    parent->AppendChild(MakeRefPtr<LayoutWrapperNode>(
        [weak = AceType::WeakClaim(this), forceMeasure, forceLayout](RefPtr<LayoutWrapperNode> layoutWrapper) {
            auto customNode = weak.Upgrade();
            CHECK_NULL_VOID(customNode);

            customNode->Render();
            if (customNode->GetChildren().empty()) {
                return;
            }
            auto child = customNode->GetChildren().front();
            while (!InstanceOf<FrameNode>(child)) {
                auto custom = DynamicCast<CustomNode>(child);
                if (custom) {
                    custom->Render();
                }
                auto children = child->GetChildren();
                if (children.empty()) {
                    return;
                }
                child = children.front();
            }
            auto frameChild = DynamicCast<FrameNode>(child);
            CHECK_NULL_VOID(frameChild);
            frameChild->UpdateLayoutWrapper(layoutWrapper, forceMeasure, forceLayout);
        }));
}

RefPtr<LayoutWrapperNode> CustomNode::CreateLayoutWrapper(bool forceMeasure, bool forceLayout)
{
    Build(nullptr);
    return UINode::CreateLayoutWrapper(forceMeasure, forceLayout);
}

void CustomNode::MarkNeedSyncRenderTree(bool needRebuild)
{
    if (needMarkParent_) {
        UINode::MarkNeedSyncRenderTree(needRebuild);
    }
}

RefPtr<UINode> CustomNode::GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    if (!isCache) {
        SetJSViewActive(true);
    }
    Render();
    return UINode::GetFrameChildByIndex(index, needBuild, isCache, addToRenderTree);
}

void CustomNode::DoSetActiveChildRange(
    int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache)
{
    if (showCache) {
        start -= cacheStart;
        end += cacheEnd;
    }
    if (start <= end) {
        if (start > 0 || end < 0) {
            SetActive(false);
            SetJSViewActive(false);
        } else {
            SetJSViewActive(true);
        }
    } else {
        if (end < 0 && start > 0) {
            SetActive(false);
            SetJSViewActive(false);
        } else {
            SetJSViewActive(true);
        }
    }
}

std::unique_ptr<JsonValue> CustomNode::GetStateInspectorInfo()
{
    std::string res = FireOnDumpInspectorFunc();
    TAG_LOGD(AceLogTag::ACE_STATE_MGMT, "ArkUI State Inspector dump info %{private}s", res.c_str());
    auto json = JsonUtil::ParseJsonString(res);
    return json;
}

void CustomNode::DumpComponentInfo(std::unique_ptr<JsonValue>& componentInfo)
{
    DumpLog::GetInstance().AddDesc("ComponentName: " + componentInfo->GetValue("ComponentName")->ToString());
    DumpLog::GetInstance().AddDesc("isV2: " + componentInfo->GetValue("isV2")->ToString());
    DumpLog::GetInstance().AddDesc("isFreezeAllowed: " + \
                                    componentInfo->GetValue("isCompFreezeAllowed_")->ToString());
    DumpLog::GetInstance().AddDesc("isViewActive: " + componentInfo->GetValue("isViewActive_")->ToString());
}

void CustomNode::DumpDecoratorInfo(std::unique_ptr<JsonValue>& decoratorInfo)
{
    int size = decoratorInfo->GetArraySize();

    DumpLog::GetInstance().AddDesc("-----start print decoratorInfo");
    for (int i = 0; i < size; i++) {
        auto decoratorItem = decoratorInfo->GetArrayItem(i);
        DumpLog::GetInstance().AddDesc("decorator:" + decoratorItem->GetValue("decorator")->ToString() + \
                                       " propertyName:" + decoratorItem->GetValue("propertyName")->ToString() + \
                                       " value:" + decoratorItem->GetValue("value")->ToString());
        DumpLog::GetInstance().AddDesc("state Variable id: " + decoratorItem->GetValue("id")->ToString());
        DumpLog::GetInstance().AddDesc("inRenderingElementId: " + \
                                        decoratorItem->GetValue("inRenderingElementId")->ToString());
        DumpLog::GetInstance().AddDesc("dependentElementIds: " + \
                                        decoratorItem->GetValue("dependentElementIds")->ToString());
        if (i < size - 1) {
            DumpLog::GetInstance().AddDesc("------------------------------");
        }
    }
    DumpLog::GetInstance().AddDesc("-----end print decoratorInfo");
}

void CustomNode::DumpInfo()
{
    std::string ret = FireOnDumpInspectorFunc();
    TAG_LOGD(AceLogTag::ACE_STATE_MGMT, "ArkUI DumpInfo %{private}s", ret.c_str());
    if (ret != "") {
        auto json = JsonUtil::ParseJsonString(ret);
        if (json == nullptr || !json->IsValid()) {
            TAG_LOGE(AceLogTag::ACE_STATE_MGMT, "ParseJsonString failed");
            return;
        }
        auto componentInfo = json->GetValue("viewInfo");
        if (componentInfo != nullptr) {
            DumpComponentInfo(componentInfo);
        }
        auto decoratorInfo = json->GetValue("observedPropertiesInfo");
        if (decoratorInfo != nullptr) {
            DumpDecoratorInfo(decoratorInfo);
        }
    }
    DumpLog::GetInstance().AddDesc(std::string("CreatorId: ").append(GetCreatorId()));
    FireOnDumpInfoFunc({ "RecyclePool" });
}

void CustomNode::FireClearParentReusePoolIfNeeded()
{
    if (GetMemOpt() <= 0) {
        return;
    }
    FireClearParentReusePoolFunc();
}

void CustomNode::FireRecycleRenderFunc()
{
    if (HasRecycleRenderFunc()) {
        if (SystemProperties::ConfigChangePerform()) {
            // Get the current color mode and notify the node to change the color mode
            auto context = GetContext();
            if (context) {
                auto colorMode = context->GetColorMode();
                SetRerenderable(true);
                SetMeasureAnyway(true);
                NotifyColorModeChange(static_cast<uint32_t>(colorMode));
            }
        }
        std::string reuseId = GetReuseId().empty() ? "-1" : GetReuseId();
        std::string parentInfo = "-1";
        if (SystemProperties::GetDynamicDetectionTraceEnabled()) {
            auto customParent = FindParentCustomNode();
            if (customParent) {
                parentInfo = customParent->GetJSViewName() + "[" + std::to_string(customParent->GetId()) + "]";
            }
        }

        ACE_SCOPED_TRACE("CustomNode:BuildRecycle [%s][self:%d][parent:%d][reuseId:%s][parentCustomNode:%s]",
            GetJSViewName().c_str(), GetId(), GetParent() ? GetParent()->GetId() : 0,
            reuseId.c_str(), parentInfo.c_str());
        CustomNodeBase::FireRecycleRenderFunc();
    }
}

RefPtr<CustomNode> CustomNode::FindParentCustomNode() const
{
    auto current = GetParent();
    while (current) {
        auto customParent = DynamicCast<CustomNode>(current);
        if (customParent) {
            return customParent;
        }
        current = current->GetParent();
    }
    return nullptr;
}

void CustomNode::SetDestroying(bool isDestroying, bool cleanStatus)
{
    UINode::SetDestroying(isDestroying, cleanStatus);
    if (isDestroying && cleanStatus) {
        auto context = GetContext();
        CHECK_NULL_VOID(context);
        // add customnode to pipeline when state change, destroy them next vsync
        context->AddPendingDeleteCustomNode(Claim(this));
    }
}

bool CustomNode::FireOnCleanup()
{
    auto callback = onCleanupFunc_;
    if (callback) {
        callback();
        return true;
    }
    return false;
}

ReusableMemOptStrategy CustomNode::GetMemOptStrategy()
{
    return memOptStrategy_;
}

void CustomNode::OnWindowHide()
{
    CleanCache(true);
}

void CustomNode::OnNotifyMemoryLevel(int32_t level)
{
    if (level == MEMORY_LEVEL_LOW || level == MEMORY_LEVEL_CRITICAL) {
        CleanCache(false);
    }
}

void CustomNode::RegisterWindowStateChangedCallback()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->AddWindowStateChangedCallback(GetId());
}

void CustomNode::UnregisterWindowStateChangedCallback()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->RemoveWindowStateChangedCallback(GetId());
}

void CustomNode::RegisterMemoryLevelChangedCallback()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->AddNodesToNotifyMemoryLevel(GetId());
}

void CustomNode::UnregisterMemoryLevelChangedCallback()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->RemoveNodesToNotifyMemoryLevel(GetId());
}

bool CustomNode::CheckParentFrameNodeVisibility()
{
    auto parent = GetParentFrameNode();
    CHECK_NULL_RETURN(parent, false);
    auto context = GetContext();
    CHECK_NULL_RETURN(context, false);
    return !(parent->IsDisappearOrNoVisibleArea(context->GetVsyncTime()));
}

void CustomNode::ScheduleCleanCacheTask()
{
    CHECK_EQUAL_VOID(pendingCleanCache_, true);
    TAG_LOGI(AceLogTag::ACE_STATE_MGMT, "CustomNode.ScheduleCleanCacheTask id[%{public}d]", GetId());
    ACE_SCOPED_TRACE("CustomNode.ScheduleCleanCacheTask id[%d]", GetId());
    pendingCleanCache_ = true;
    cacheTaskPostTime_ = GetSysTimestamp();
}

void CustomNode::CancelScheduledCleanCacheTask()
{
    TAG_LOGI(AceLogTag::ACE_STATE_MGMT, "CustomNode.CancelScheduledCleanCacheTask id[%{public}d]", GetId());
    ACE_SCOPED_TRACE("CustomNode.CancelScheduledCleanCacheTask id[%d]", GetId());
    pendingCleanCache_ = false;
}

void CustomNode::TryExecuteScheduledCacheTask()
{
    CHECK_EQUAL_VOID(pendingCleanCache_, false);
    auto timeStamp = GetSysTimestamp();
    CHECK_EQUAL_VOID(timeStamp - cacheTaskPostTime_ < CACHE_TASK_DELAY_TIME, true);
    CleanCache(false);
}

void CustomNode::CleanCache(bool syncClean, bool clearAll)
{
    TAG_LOGI(AceLogTag::ACE_STATE_MGMT,
        "CustomNode.CleanCache id[%{public}d] syncClean[%{public}d]", GetId(), syncClean);
    ACE_SCOPED_TRACE("CustomNode.CleanCache id[%d] syncClean[%d]", GetId(), syncClean);
    if (staReusableMemOptStrategy_ == StaReusableMemOptStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION) {
        FireClearParentReusePoolIfNeeded();
    }
    if (!syncClean) {
        needCleanCacheOnIdle_ = true;
        stopMemOptAfterRelease_ = clearAll;
        hasPreparedProgressiveRelease_ = !clearAll;
        PostIdleTask();
        return;
    }
    if (releaseRecyclePoolFunc_) {
        // Sync mode: no time limit, batch release, collect nodes
        releaseRecyclePoolFunc_(0, false, true);
    }
    FinishMemOpt();
}

void CustomNode::CleanCacheOnIdle(int32_t remainingTimeMs)
{
    CHECK_EQUAL_VOID(needCleanCacheOnIdle_, false);

    TAG_LOGI(AceLogTag::ACE_STATE_MGMT,
        "CustomNode.CleanCacheOnIdle id[%{public}d] remainingTimeMs[%{public}d]", GetId(), remainingTimeMs);
    ACE_SCOPED_TRACE("CustomNode.CleanCacheOnIdle id[%d] remainingTimeMs[%d]", GetId(), remainingTimeMs);
    if (releaseRecyclePoolFunc_) {
        if (releaseRecyclePoolFunc_(remainingTimeMs, true, !hasPreparedProgressiveRelease_)) {
            if (stopMemOptAfterRelease_) {
                FinishMemOpt();
            }
        } else {
            // Timeout occurred, repost idle task to continue cleanup in next frame
            hasPreparedProgressiveRelease_ = true;
            PostIdleTask();
        }
    } else {
        FinishMemOpt();
    }
}

void CustomNode::SetParentVisibility(bool visibility)
{
    isParentVisible_ = visibility;
}

bool CustomNode::GetParentVisibility()
{
    return isParentVisible_;
}

void CustomNode::StartMemOpt()
{
    CHECK_EQUAL_VOID(runningMemOpt_, true);
    runningMemOpt_ = true;
    RegisterWindowStateChangedCallback();
    RegisterMemoryLevelChangedCallback();
    PostMemOptTask();
}

void CustomNode::FinishMemOpt()
{
    CHECK_EQUAL_VOID(runningMemOpt_, false);
    runningMemOpt_ = false;
    needCleanCacheOnIdle_ = false;
    hasPreparedProgressiveRelease_ = false;
    UnregisterWindowStateChangedCallback();
    UnregisterMemoryLevelChangedCallback();
}

void CustomNode::PostMemOptTask()
{
    CHECK_EQUAL_VOID(runningMemOpt_, false);
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    const uint32_t delay = 1000; // 1 seconds in milliseconds
    auto weakNode = AceType::WeakClaim(this);
    taskExecutor->PostDelayedTask(
        [weakNode]() {
            auto node = weakNode.Upgrade();
            CHECK_NULL_VOID(node);
            auto pipeline = node->GetContext();
            CHECK_NULL_VOID(pipeline);
            CHECK_EQUAL_VOID(pipeline->GetOnShow(), false);
            auto visible = node->CheckParentFrameNodeVisibility();
            if (visible != node->GetParentVisibility()) {
                node->SetParentVisibility(visible);
                visible ? node->CancelScheduledCleanCacheTask() : node->ScheduleCleanCacheTask();
            }
            if (node->staReusableMemOptStrategy_ == StaReusableMemOptStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION) {
                node->CancelScheduledCleanCacheTask();
                auto parentNode = node->GetParentCustomNode();
                CHECK_NULL_VOID(parentNode);
                if (!parentNode->CheckParentFrameNodeVisibility()) {
                    node->FireClearParentReusePoolIfNeeded();
                }
            }
            node->TryExecuteScheduledCacheTask();
            node->PostMemOptTask();
        },
        TaskExecutor::TaskType::UI,
        delay,
        "CustomNodeMemOptTask");
}

void CustomNode::PostIdleTask()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->AddPredictTask([weak = AceType::WeakClaim(this)] (int64_t deadline, bool /*canUseLongPredictTask*/) {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        TAG_LOGI(AceLogTag::ACE_STATE_MGMT, "CustomNode.OnIdle id[%{public}d]", node->GetId());
        ACE_SCOPED_TRACE("CustomNode.OnIdle id[%d]", node->GetId());

        // Calculate remaining time in milliseconds
        int64_t currentTime = GetSysTimestamp();
        int64_t remainingTimeMs = 0;
        int64_t nsToMs = 1000000;
        remainingTimeMs = (deadline - currentTime) / nsToMs; // Convert nanoseconds to milliseconds

        // Call CleanCacheOnIdle with remaining time
        node->CleanCacheOnIdle(static_cast<int32_t>(remainingTimeMs));
    });
}

} // namespace OHOS::Ace::NG
