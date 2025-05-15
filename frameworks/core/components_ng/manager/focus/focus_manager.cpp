/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/focus/focus_manager.h"

#include "base/log/dump_log.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/components/theme/app_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<FocusManager> GetCurrentFocusManager()
{
    auto context = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(context, nullptr);
    auto focusManager = context->GetFocusManager();
    return focusManager;
}
}

FocusManager::FocusManager(const RefPtr<PipelineContext>& pipeline): pipeline_(pipeline)
{
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetRootElement()) {
        currentFocus_ = pipeline->GetRootElement()->GetFocusHub();
    }
    // After switching between portrait and landscape mode
    // reset the isNeedTriggerScroll parameter to enable screen focus scrolling.
    pipeline->RegisterSurfaceChangedCallback([weak = WeakClaim(this)](int32_t width, int32_t height, int32_t oldWidth,
                                                 int32_t oldHeight, WindowSizeChangeReason type) {
        auto context = weak.Upgrade();
        context->SetNeedTriggerScroll(true);
    });
}

void FocusManager::FocusViewShow(const RefPtr<FocusView>& focusView, bool isTriggerByStep)
{
    CHECK_NULL_VOID(focusView);
    if (!focusView->HasParentFocusHub()) {
        TAG_LOGD(AceLogTag::ACE_FOCUS, "FocusView: %{public}s/%{public}d has no parent. Do not need show.",
            focusView->GetFrameName().c_str(), focusView->GetFrameId());
        return;
    }
    focusView->SetIsViewHasShow(true);
    auto lastFocusView = lastFocusView_.Upgrade();
    if (lastFocusView) {
        if (lastFocusView == focusView || lastFocusView->IsChildFocusViewOf(focusView)) {
            return;
        }
        if (!focusView->IsChildFocusViewOf(lastFocusView) && IsAutoFocusTransfer()) {
            lastFocusView->LostViewFocus();
        }
    }

    auto focusViewWeak = AceType::WeakClaim(AceType::RawPtr(focusView));
    if (std::find(focusViewStack_.begin(), focusViewStack_.end(), focusViewWeak) != focusViewStack_.end()) {
        focusViewStack_.remove(focusViewWeak);
    }
    focusViewStack_.emplace_back(focusViewWeak);
    focusViewStackState_ = FocusViewStackState::SHOW;
    lastFocusView_ = focusViewWeak;

    // do not set LastWeakFocus to Previous node/scope in focusView when FocusViewShow trigger by FocusStep
    if (!isTriggerByStep) {
        lastFocusView = lastFocusView_.Upgrade();
        if (!lastFocusView) {
            return;
        }
        auto lastFocusViewHub = lastFocusView->GetFocusHub();
        if (lastFocusViewHub) {
            lastFocusViewHub->SetLastWeakFocusToPreviousInFocusView();
        }
    }
}

bool FocusManager::RearrangeViewStack()
{
    auto curFocusView = FocusView::GetCurrentFocusView();
    CHECK_NULL_RETURN(curFocusView, false);
    auto curFocusViewHub = curFocusView->GetFocusHub();
    CHECK_NULL_RETURN(curFocusViewHub, false);
    auto curFocusViewWeak = AceType::WeakClaim(AceType::RawPtr(curFocusView));
    if (!curFocusViewHub->IsCurrentFocus() && focusViewStackState_ == FocusViewStackState::SHOW) {
        if (std::find(focusViewStack_.begin(), focusViewStack_.end(), curFocusViewWeak) != focusViewStack_.end()) {
            focusViewStack_.remove(curFocusViewWeak);
        }
        lastFocusView_ = focusViewStack_.back();
        return true;
    }
    if (focusViewStackState_ == FocusViewStackState::CLOSE) {
        auto ret = SetFocusViewRootScope(curFocusView);
        return ret;
    }
    return false;
}

void FocusManager::FocusViewHide(const RefPtr<FocusView>& focusView)
{
    CHECK_NULL_VOID(focusView);
    if (IsAutoFocusTransfer()) {
        focusView->LostViewFocus();
    }
    auto lastFocusView = lastFocusView_.Upgrade();
    if (lastFocusView && (lastFocusView == focusView || lastFocusView->IsChildFocusViewOf(focusView))) {
        lastFocusView_ = nullptr;
    }
}

void FocusManager::FocusViewClose(const RefPtr<FocusView>& focusView, bool isDetachFromTree)
{
    if (!IsAutoFocusTransfer() && !isDetachFromTree)  {
        return;
    }
    CHECK_NULL_VOID(focusView);
    focusView->LostViewFocus();
    focusView->SetIsViewHasShow(false);
    for (auto iter = focusViewStack_.begin(); iter != focusViewStack_.end();) {
        auto view = (*iter).Upgrade();
        if (view && (view == focusView || view->IsChildFocusViewOf(focusView))) {
            auto focusHub = view->GetFocusHub();
            if (focusHub) {
                focusHub->RemoveFocusScopeIdAndPriority();
            }
            iter = focusViewStack_.erase(iter);
            focusViewStackState_ = FocusViewStackState::CLOSE;
        } else {
            ++iter;
        }
    }
    if (focusViewStack_.empty()) {
        lastFocusView_ = nullptr;
        return;
    }
    if (focusViewStack_.back() != lastFocusView_) {
        lastFocusView_ = focusViewStack_.back();
    }
}

void FocusManager::FlushFocusView()
{
    auto lastFocusView = lastFocusView_.Upgrade();
    auto lastFocusViewHub = lastFocusView ? lastFocusView->GetFocusHub() : nullptr;
    if (lastFocusViewHub && lastFocusViewHub->IsCurrentFocus()) {
        return;
    }
    RefPtr<FocusView> currFocusView = nullptr;
    for (const auto& weakView : focusViewStack_) {
        auto view = weakView.Upgrade();
        auto viewHub = view ? view->GetFocusHub() : nullptr;
        if (!viewHub || !viewHub->IsCurrentFocus()) {
            continue;
        }
        if (currFocusView && currFocusView->IsChildFocusViewOf(view)) {
            continue;
        }
        currFocusView = view;
    }
    lastFocusView_ = currFocusView ? AceType::WeakClaim(AceType::RawPtr(currFocusView)) : nullptr;
}

void FocusManager::GetFocusViewMap(FocusViewMap& focusViewMap)
{
    for (const auto& focusViewWeak : focusViewStack_) {
        auto focusView = focusViewWeak.Upgrade();
        if (!focusView) {
            continue;
        }
        auto focusViewId = focusView->GetFrameId();
        auto entryFocusView = focusView->GetEntryFocusView();
        if (entryFocusView && entryFocusView != focusView) {
            auto entryFocusViewId = entryFocusView->GetFrameId();
            auto entryFocusViewWeak = AceType::WeakClaim(AceType::RawPtr(entryFocusView));
            auto iter = focusViewMap.find(entryFocusViewId);
            if (iter == focusViewMap.end()) {
                focusViewMap[entryFocusViewId] = { entryFocusViewWeak, { focusViewWeak } };
            } else {
                iter->second.second.emplace_back(focusViewWeak);
            }
        } else {
            focusViewMap[focusViewId] = { focusViewWeak, {} };
        }
    }
}

void FocusManager::PaintFocusState()
{
    auto pipeline = pipeline_.Upgrade();
    CHECK_NULL_VOID(pipeline);
    auto rootNode = pipeline->GetRootElement();
    CHECK_NULL_VOID(rootNode);
    auto rootFocusHub = rootNode->GetFocusHub();
    CHECK_NULL_VOID(rootFocusHub);
    if (!pipeline->GetIsFocusActive()) {
        return;
    }
    rootFocusHub->ClearAllFocusState();
    rootFocusHub->PaintAllFocusState();
}


void FocusManager::DumpFocusManager()
{
    if (!DumpLog::GetInstance().GetDumpFile()) {
        return;
    }
    DumpLog::GetInstance().Print("Focus view:");
    std::unordered_map<int32_t, std::pair<WeakPtr<FocusView>, std::list<WeakPtr<FocusView>>>> focusViewMap;
    GetFocusViewMap(focusViewMap);
    for (const auto& focusViewInfo : focusViewMap) {
        auto focusView = focusViewInfo.second.first.Upgrade();
        if (!focusView) {
            continue;
        }
        auto childFocusViewWeakList = focusViewInfo.second.second;
        bool isFocusedView = false;
        auto lastFocusView = lastFocusView_.Upgrade();
        auto lastEntryFocusView = lastFocusView ? lastFocusView->GetEntryFocusView() : nullptr;
        if (focusView == lastEntryFocusView) {
            isFocusedView = true;
        }
        std::string information = focusView->GetFrameName();
        information += isFocusedView ? "(*)" : "";
        information += " id:" + std::to_string(focusView->GetFrameId());
        DumpLog::GetInstance().Print(0, information, static_cast<int32_t>(childFocusViewWeakList.size()));
        for (const auto& childWeak : childFocusViewWeakList) {
            auto child = childWeak.Upgrade();
            if (!child) {
                continue;
            }
            std::string childInformation = child->GetFrameName();
            childInformation += child == lastFocusView ? "(*)" : "";
            childInformation += " id:" + std::to_string(child->GetFrameId());
            DumpLog::GetInstance().Print(1, childInformation, 0);
        }
    }
}

bool FocusManager::AddFocusScope(const std::string& focusScopeId, const RefPtr<FocusHub>& scopeFocusHub)
{
    auto iter = focusHubScopeMap_.find(focusScopeId);
    if (iter != focusHubScopeMap_.end()) {
        auto focusScope = iter->second.first.Upgrade();
        if (!focusScope) {
            iter->second.first = scopeFocusHub;
            return true;
        }
        return false;
    } else {
        focusHubScopeMap_[focusScopeId] = { scopeFocusHub, {} };
    }
    return true;
}

void FocusManager::RemoveFocusScope(const std::string& focusScopeId)
{
    auto iter = focusHubScopeMap_.find(focusScopeId);
    if (iter != focusHubScopeMap_.end()) {
        if (iter->second.second.empty()) {
            focusHubScopeMap_.erase(iter);
        } else {
            iter->second.first = nullptr;
        }
    }
}

void FocusManager::AddScopePriorityNode(const std::string& focusScopeId, const RefPtr<FocusHub>& priorFocusHub,
    bool pushFront)
{
    auto iter = focusHubScopeMap_.find(focusScopeId);
    if (iter != focusHubScopeMap_.end()) {
        if (pushFront) {
            iter->second.second.emplace_front(priorFocusHub);
        } else {
            iter->second.second.emplace_back(priorFocusHub);
        }
    } else {
        focusHubScopeMap_[focusScopeId] = { nullptr, { priorFocusHub } };
    }
}

void FocusManager::RemoveScopePriorityNode(const std::string& focusScopeId, const RefPtr<FocusHub>& priorFocusHub)
{
    auto iter = focusHubScopeMap_.find(focusScopeId);
    if (iter != focusHubScopeMap_.end()) {
        if (iter->second.second.empty()) {
            return;
        }
        iter->second.second.remove(priorFocusHub);
        auto focusScope = iter->second.first.Upgrade();
        if (!focusScope && iter->second.second.empty()) {
            focusHubScopeMap_.erase(iter);
        }
    }
}

std::optional<std::list<WeakPtr<FocusHub>>*> FocusManager::GetFocusScopePriorityList(const std::string& focusScopeId)
{
    auto iter = focusHubScopeMap_.find(focusScopeId);
    if (iter != focusHubScopeMap_.end()) {
        if (!iter->second.second.empty()) {
            return &(iter->second.second);
        }
    }
    return std::nullopt;
}

void FocusManager::UpdateCurrentFocus(const RefPtr<FocusHub>& current, SwitchingUpdateReason reason)
{
    if (isSwitchingFocus_.value_or(false)) {
        switchingFocus_ = current;
        updateReason_ = reason;
    }
}

RefPtr<FocusHub> FocusManager::GetCurrentFocus()
{
    return currentFocus_.Upgrade();
}

void FocusManager::TriggerAllFocusActiveChangeCallback(bool isFocusActive)
{
    auto focusActiveChangeCallbackManager = GetFocusActiveChangeCallbackManager();
    if (focusActiveChangeCallbackManager) {
        focusActiveChangeCallbackManager->NotifyListener(isFocusActive);
    }
    auto isFocusActiveUpdateEventManager = GetIsFocusActiveUpdateEventManager();
    if (isFocusActiveUpdateEventManager) {
        isFocusActiveUpdateEventManager->NotifyListener(isFocusActive);
    }
}

RefPtr<FocusManager> FocusManager::GetFocusManager(RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto context = node->GetContextRefPtr();
    CHECK_NULL_RETURN(context, nullptr);
    auto focusManager = context->GetFocusManager();
    return focusManager;
}

void FocusManager::FocusSwitchingStart(const RefPtr<FocusHub>& focusHub,
    SwitchingStartReason reason)
{
    isSwitchingFocus_ = true;
    switchingFocus_ = focusHub;
    startReason_ = reason;
}

void FocusManager::ReportFocusSwitching(FocusReason focusReason)
{
    auto callbacksManager = GetFocusChangeCallbackManager();
    if (callbacksManager) {
        callbacksManager->NotifyListener(currentFocus_, switchingFocus_, focusReason);
    }
    currentFocus_ = switchingFocus_;
    isSwitchingFocus_.reset();
    startReason_.reset();
    updateReason_.reset();
    endReason_.reset();
}

void FocusManager::FocusSwitchingEnd(SwitchingEndReason reason)
{
    // While switching window, focus may move by steps.(WindowFocus/FlushFocus)
    // Merge all steps together as a single movement.
    if (!isSwitchingFocus_.value_or(false)) {
        return;
    }
    if (!isSwitchingWindow_) {
        auto lastHub = currentFocus_.Upgrade();
        TAG_LOGI(AceLogTag::ACE_FOCUS, "FocusSwitch end, %{public}s/" SEC_PLD(%{public}d) " onBlur, "
            "%{public}s/" SEC_PLD(%{public}d) " onFocus, "
            "start: %{public}d, end: %{public}d, update: %{public}d",
            lastHub ? lastHub->GetFrameName().c_str() : "NULL",
            SEC_PARAM(lastHub ? lastHub->GetFrameId() : -1),
            switchingFocus_ ? switchingFocus_->GetFrameName().c_str() : "NULL",
            SEC_PARAM(switchingFocus_ ? switchingFocus_->GetFrameId() : -1),
            startReason_.value_or(SwitchingStartReason::DEFAULT),
            reason, updateReason_.value_or(SwitchingUpdateReason::DEFAULT));
        if (switchingFocus_ &&
            startReason_.value_or(SwitchingStartReason::DEFAULT) != SwitchingStartReason::LOST_FOCUS_TO_VIEW_ROOT) {
            switchingFocus_->ClearLastFocusNode();
        }
        ReportFocusSwitching(FocusReason::DEFAULT);
        PaintFocusState();
    } else {
        isSwitchingFocus_ = false;
        endReason_ = reason;
    }
}

void FocusManager::WindowFocusMoveStart()
{
    isSwitchingWindow_ = true;
}

void FocusManager::WindowFocusMoveEnd()
{
    isSwitchingWindow_ = false;
    if (!isSwitchingFocus_.value_or(true)) {
        auto lastHub = currentFocus_.Upgrade();
        TAG_LOGI(AceLogTag::ACE_FOCUS, "WinFocusMove end, %{public}s/" SEC_PLD(%{public}d) " onBlur, "
            "%{public}s/" SEC_PLD(%{public}d) " onFocus, "
            "start: %{public}d, end: %{public}d, update: %{public}d",
            lastHub ? lastHub->GetFrameName().c_str() : "NULL",
            SEC_PARAM(lastHub ? lastHub->GetFrameId() : -1),
            switchingFocus_ ? switchingFocus_->GetFrameName().c_str() : "NULL",
            SEC_PARAM(switchingFocus_ ? switchingFocus_->GetFrameId() : -1),
            startReason_.value_or(SwitchingStartReason::DEFAULT),
            endReason_.value_or(SwitchingEndReason::DEFAULT),
            updateReason_.value_or(SwitchingUpdateReason::DEFAULT));
        ReportFocusSwitching(FocusReason::WINDOW_FOCUS);
        PaintFocusState();
    }
}

void FocusManager::FocusGuard::CreateFocusGuard(const RefPtr<FocusHub>& focusHub,
    const RefPtr<FocusManager>& focusManager, SwitchingStartReason reason)
{
    CHECK_NULL_VOID(focusManager);
    if (focusManager->isSwitchingFocus_.value_or(false)) {
        return;
    }
    focusManager->FocusSwitchingStart(focusHub, reason);
    focusMng_ = focusManager;
}

FocusManager::FocusGuard::FocusGuard(const RefPtr<FocusHub>& focusHub,
    SwitchingStartReason reason)
{
    RefPtr<FocusHub> hub = focusHub;
    if (!hub || !hub->GetFocusManager()) {
        auto curFocusView = FocusView::GetCurrentFocusView();
        hub = curFocusView ? curFocusView->GetFocusHub() : nullptr;
    }

    auto mng = hub ? hub->GetFocusManager() : GetCurrentFocusManager();
    CreateFocusGuard(hub, mng, reason);
}

FocusManager::FocusGuard::~FocusGuard()
{
    if (focusMng_) {
        focusMng_->FocusSwitchingEnd();
    }
}

bool FocusManager::SetFocusViewRootScope(const RefPtr<FocusView>& focusView)
{
    auto focusViewRootScope = focusView->GetViewRootScope();
    focusView->SetIsViewRootScopeFocused(true);
    return focusViewRootScope->RequestFocusImmediatelyInner();
}

void FocusManager::WindowFocus(bool isFocus)
{
    if (!isFocus) {
        return;
    }
    WindowFocusMoveStart();
    FocusManager::FocusGuard guard(GetCurrentFocus(), SwitchingStartReason::WINDOW_FOCUS);
    auto curFocusView = GetLastFocusView().Upgrade();
    auto curFocusViewHub = curFocusView ? curFocusView->GetFocusHub() : nullptr;
    if (!curFocusViewHub) {
        TAG_LOGW(AceLogTag::ACE_FOCUS, "Current focus view can not found!");
    } else if (curFocusView->GetIsViewHasFocused() && !curFocusViewHub->IsCurrentFocus()) {
        TAG_LOGD(AceLogTag::ACE_FOCUS, "Request current focus view: %{public}s/%{public}d",
            curFocusView->GetFrameName().c_str(), curFocusView->GetFrameId());
        if (!IsAutoFocusTransfer()) {
            SetFocusViewRootScope(curFocusView);
        } else {
            auto lastViewFocusNode = curFocusViewHub->GetFocusLeaf();
            lastViewFocusNode->RequestFocusImmediatelyInner(FocusReason::WINDOW_FOCUS);
        }
    } else {
        auto container = Container::Current();
        if (container && (container->IsUIExtensionWindow() || container->IsDynamicRender())) {
            TAG_LOGD(AceLogTag::ACE_FOCUS,
                "Request default focus on current focus view: %{public}s/%{public}d",
                curFocusView->GetFrameName().c_str(),
                curFocusView->GetFrameId());
            curFocusView->SetIsViewRootScopeFocused(false);
            curFocusView->RequestDefaultFocus();
        }
    }

    auto pipeline = pipeline_.Upgrade();
    CHECK_NULL_VOID(pipeline);
    auto root = pipeline->GetRootElement();
    CHECK_NULL_VOID(root);
    auto rootFocusHub = root->GetFocusHub();
    CHECK_NULL_VOID(rootFocusHub);
    if (!rootFocusHub->IsCurrentFocus()) {
        TAG_LOGD(AceLogTag::ACE_FOCUS,
            "Request focus on rootFocusHub: %{public}s/%{public}d",
            rootFocusHub->GetFrameName().c_str(),
            rootFocusHub->GetFrameId());
        auto focusDepend = rootFocusHub->GetFocusDependence();
        rootFocusHub->SetFocusDependence(FocusDependence::SELF);
        rootFocusHub->RequestFocusImmediatelyInner(FocusReason::WINDOW_FOCUS);
        rootFocusHub->SetFocusDependence(focusDepend);
    }
    pipeline->RequestFrame();
}

bool FocusManager::SetIsFocusActive(bool isFocusActive, FocusActiveReason reason, bool autoFocusInactive)
{
    if (!NeedChangeFocusAvtive(isFocusActive, reason, autoFocusInactive)) {
        return false;
    }
    TAG_LOGI(AceLogTag::ACE_FOCUS, "focusActive turns:%{public}d, reason:%{public}d", isFocusActive, reason);
    isFocusActive_ = isFocusActive;

    auto pipeline = pipeline_.Upgrade();
    CHECK_NULL_RETURN(pipeline, false);
    auto containerId = Container::CurrentId();
    auto subWindowContainerId = SubwindowManager::GetInstance()->GetSubContainerId(containerId);
    if (subWindowContainerId >= 0) {
        auto subPipeline = pipeline->GetContextByContainerId(subWindowContainerId);
        CHECK_NULL_RETURN(subPipeline, false);
        ContainerScope scope(subWindowContainerId);
        auto subFocusManager = subPipeline->GetOrCreateFocusManager();
        CHECK_NULL_RETURN(subFocusManager, false);
        subFocusManager->SetIsFocusActive(isFocusActive, reason, autoFocusInactive);
    }

    TriggerAllFocusActiveChangeCallback(isFocusActive);

    auto rootNode = pipeline->GetRootElement();
    CHECK_NULL_RETURN(rootNode, false);
    auto rootFocusHub = rootNode->GetFocusHub();
    CHECK_NULL_RETURN(rootFocusHub, false);
    if (isFocusActive_) {
        return rootFocusHub->PaintAllFocusState();
    }
    rootFocusHub->ClearAllFocusState();
    return true;
}

bool FocusManager::NeedChangeFocusAvtive(bool isFocusActive, FocusActiveReason reason, bool autoFocusInactive)
{
    if (reason == FocusActiveReason::USE_API) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "autoFocusInactive turns to %{public}d", autoFocusInactive);
        autoFocusInactive_ = autoFocusInactive;
    }
    if (isFocusActive_ == isFocusActive) {
        return false;
    }
    if (reason == FocusActiveReason::ACTIVE_MARK) {
        return true;
    }
    if (isFocusActive) {
        if (!SystemProperties::GetFocusCanBeActive()) {
            TAG_LOGI(AceLogTag::ACE_FOCUS, "FocusActive false");
            return false;
        }
        auto pipeline = pipeline_.Upgrade();
        auto appTheme = pipeline ? pipeline->GetTheme<AppTheme>() : nullptr;
        if (reason == FocusActiveReason::KEY_TAB && appTheme && !appTheme->NeedFocusActiveByTab()) {
            return false;
        }
    }
    if (!isFocusActive && reason == FocusActiveReason::POINTER_EVENT && !autoFocusInactive_) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "focus cannot be deactived automaticly by pointer event");
        return false;
    }
    return true;
}

bool FocusManager::HandleKeyForExtendOrActivateFocus(const KeyEvent& event, const RefPtr<FocusView>& curFocusView)
{
    if (event.action == KeyAction::DOWN) {
        if (event.activeMark.has_value()) {
            if (event.activeMark.value()) {
                return ExtendOrActivateFocus(curFocusView, FocusActiveReason::ACTIVE_MARK);
            } else {
                return SetIsFocusActive(false, FocusActiveReason::ACTIVE_MARK);
            }
        }
        if (event.IsKey({ KeyCode::KEY_TAB })) {
            return ExtendOrActivateFocus(curFocusView, FocusActiveReason::KEY_TAB);
        }
        auto curEntryFocusView = curFocusView ? curFocusView->GetEntryFocusView() : nullptr;
        auto curEntryFocusHub = curEntryFocusView ? curFocusView->GetFocusHub() : nullptr;
        if (event.IsDirectionalKey() && curEntryFocusHub && curEntryFocusHub->GetDirectionalKeyFocus()) {
            return ExtendOrActivateFocus(curFocusView);
        }
    }
    return false;
}

bool FocusManager::ExtendOrActivateFocus(const RefPtr<FocusView>& curFocusView, FocusActiveReason reason)
{
    auto isViewRootScopeFocused = curFocusView ? curFocusView->GetIsViewRootScopeFocused() : true;
    auto isExtend = false;
    if (curFocusView && isViewRootScopeFocused) {
        isExtend = curFocusView->TriggerFocusMove();
    }
    auto isActive = SetIsFocusActive(true, reason);
    return isExtend || isActive;
}
} // namespace OHOS::Ace::NG
