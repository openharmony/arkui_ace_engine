/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "bridge/plugin_frontend/plugin_frontend_delegate.h"

namespace OHOS::Ace::Framework {
PluginFrontendDelegate::PluginFrontendDelegate(const RefPtr<TaskExecutor>& taskExecutor,
    const LoadJsCallback& loadCallback, const JsMessageDispatcherSetterCallback& transferCallback,
    const EventCallback& asyncEventCallback, const EventCallback& syncEventCallback,
    const UpdatePageCallback& updatePageCallback, const ResetStagingPageCallback& resetLoadingPageCallback,
    const DestroyPageCallback& destroyPageCallback, const DestroyApplicationCallback& destroyApplicationCallback,
    const UpdateApplicationStateCallback& updateApplicationStateCallback, const TimerCallback& timerCallback,
    const MediaQueryCallback& mediaQueryCallback, const RequestAnimationCallback& requestAnimationCallback,
    const JsCallback& jsCallback, const OnWindowDisplayModeChangedCallBack& onWindowDisplayModeChangedCallBack,
    const OnConfigurationUpdatedCallBack& onConfigurationUpdatedCallBack,
    const OnSaveAbilityStateCallBack& onSaveAbilityStateCallBack,
    const OnRestoreAbilityStateCallBack& onRestoreAbilityStateCallBack, const OnNewWantCallBack& onNewWantCallBack,
    const OnActiveCallBack& onActiveCallBack, const OnInactiveCallBack& onInactiveCallBack,
    const OnMemoryLevelCallBack& onMemoryLevelCallBack, const OnStartContinuationCallBack& onStartContinuationCallBack,
    const OnCompleteContinuationCallBack& onCompleteContinuationCallBack,
    const OnRemoteTerminatedCallBack& onRemoteTerminatedCallBack, const OnSaveDataCallBack& onSaveDataCallBack,
    const OnRestoreDataCallBack& onRestoreDataCallBack)
    : loadJs_(loadCallback), dispatcherCallback_(transferCallback), asyncEvent_(asyncEventCallback),
      syncEvent_(syncEventCallback), updatePage_(updatePageCallback), resetStagingPage_(resetLoadingPageCallback),
      destroyPage_(destroyPageCallback), destroyApplication_(destroyApplicationCallback),
      updateApplicationState_(updateApplicationStateCallback), timer_(timerCallback),
      mediaQueryCallback_(mediaQueryCallback), requestAnimationCallback_(requestAnimationCallback),
      jsCallback_(jsCallback), onWindowDisplayModeChanged_(onWindowDisplayModeChangedCallBack),
      onConfigurationUpdated_(onConfigurationUpdatedCallBack), onSaveAbilityState_(onSaveAbilityStateCallBack),
      onRestoreAbilityState_(onRestoreAbilityStateCallBack), onNewWant_(onNewWantCallBack), onActive_(onActiveCallBack),
      onInactive_(onInactiveCallBack), onMemoryLevel_(onMemoryLevelCallBack),
      onStartContinuationCallBack_(onStartContinuationCallBack),
      onCompleteContinuationCallBack_(onCompleteContinuationCallBack),
      onRemoteTerminatedCallBack_(onRemoteTerminatedCallBack), onSaveDataCallBack_(onSaveDataCallBack),
      onRestoreDataCallBack_(onRestoreDataCallBack), manifestParser_(AceType::MakeRefPtr<ManifestParser>()),
      jsAccessibilityManager_(AccessibilityNodeManager::Create()),
      mediaQueryInfo_(AceType::MakeRefPtr<MediaQueryInfo>()), taskExecutor_(taskExecutor)
{}

PluginFrontendDelegate::~PluginFrontendDelegate() = default;

void PluginFrontendDelegate::RunPage(const std::string& url, const std::string& params) {}

void PluginFrontendDelegate::Push(const std::string& uri, const std::string& params)
{
    Push(PageTarget(uri), params);
}

void PluginFrontendDelegate::Replace(const std::string& uri, const std::string& params)
{
    Replace(PageTarget(uri), params);
}

void PluginFrontendDelegate::Back(const std::string& uri, const std::string& params)
{
    BackWithTarget(PageTarget(uri), params);
}

void PluginFrontendDelegate::Push(const PageTarget& target, const std::string& params) {}

void PluginFrontendDelegate::Replace(const PageTarget& target, const std::string& params) {}

void PluginFrontendDelegate::BackWithTarget(const PageTarget& target, const std::string& params) {}

void PluginFrontendDelegate::OnJSCallback(const std::string& callbackId, const std::string& data) {}

void PluginFrontendDelegate::LoadResourceConfiguration(
    std::map<std::string, std::string>& mediaResourceFileMap, std::unique_ptr<JsonValue>& currentResourceData)
{}

void PluginFrontendDelegate::SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const {}

void PluginFrontendDelegate::TransferComponentResponseData(
    int32_t callbackId, int32_t code, std::vector<uint8_t>&& data)
{}

void PluginFrontendDelegate::TransferJsResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const
{}

void PluginFrontendDelegate::TransferJsPluginGetError(
    int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const
{}

void PluginFrontendDelegate::TransferJsEventData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const {}

void PluginFrontendDelegate::LoadPluginJsCode(std::string&& jsCode) const {}

void PluginFrontendDelegate::LoadPluginJsByteCode(std::vector<uint8_t>&& jsCode, std::vector<int32_t>&& jsCodeLen) const
{}

void PluginFrontendDelegate::NotifyAppStorage(
    const WeakPtr<Framework::JsEngine>& jsEngineWeak, const std::string& key, const std::string& value)
{}

void PluginFrontendDelegate::OnSuspended() {}

void PluginFrontendDelegate::OnBackGround() {}

void PluginFrontendDelegate::OnForeground() {}

void PluginFrontendDelegate::OnConfigurationUpdated(const std::string& data) {}

bool PluginFrontendDelegate::OnStartContinuation()
{
    bool ret = false;

    return ret;
}

void PluginFrontendDelegate::OnCompleteContinuation(int32_t code) {}

void PluginFrontendDelegate::OnRemoteTerminated() {}

void PluginFrontendDelegate::OnSaveData(std::string& data) {}

bool PluginFrontendDelegate::OnRestoreData(const std::string& data)
{
    bool ret = false;

    return ret;
}

void PluginFrontendDelegate::OnMemoryLevel(const int32_t level) {}

void PluginFrontendDelegate::GetPluginsUsed(std::string& data) {}

void PluginFrontendDelegate::OnActive() {}

void PluginFrontendDelegate::OnInactive() {}

void PluginFrontendDelegate::OnNewRequest(const std::string& data) {}

void PluginFrontendDelegate::CallPopPage() {}

void PluginFrontendDelegate::ResetStagingPage() {}

void PluginFrontendDelegate::OnApplicationDestroy(const std::string& packageName) {}

void PluginFrontendDelegate::UpdateApplicationState(const std::string& packageName, Frontend::State state) {}

void PluginFrontendDelegate::OnWindowDisplayModeChanged(bool isShownInMultiWindow, const std::string& data) {}

void PluginFrontendDelegate::OnSaveAbilityState(std::string& data) {}

void PluginFrontendDelegate::OnRestoreAbilityState(const std::string& data) {}

void PluginFrontendDelegate::OnNewWant(const std::string& data) {}

void PluginFrontendDelegate::FireAsyncEvent(
    const std::string& eventId, const std::string& param, const std::string& jsonArgs)
{}

bool PluginFrontendDelegate::FireSyncEvent(
    const std::string& eventId, const std::string& param, const std::string& jsonArgs)
{
    return true;
}

void PluginFrontendDelegate::FireSyncEvent(
    const std::string& eventId, const std::string& param, const std::string& jsonArgs, std::string& result)
{}

void PluginFrontendDelegate::FireAccessibilityEvent(const AccessibilityEvent& accessibilityEvent) {}

void PluginFrontendDelegate::InitializeAccessibilityCallback() {}

void PluginFrontendDelegate::PostponePageTransition() {}

void PluginFrontendDelegate::LaunchPageTransition() {}

void PluginFrontendDelegate::Clear() {}

int32_t PluginFrontendDelegate::GetStackSize() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return static_cast<int32_t>(pageRouteStack_.size());
}

void PluginFrontendDelegate::GetState(int32_t& index, std::string& name, std::string& path) {}

size_t PluginFrontendDelegate::GetComponentsCount()
{
    return 0;
}

std::string PluginFrontendDelegate::GetParams()
{
    return "";
}

void PluginFrontendDelegate::TriggerPageUpdate(int32_t pageId, bool directExecute) {}

void PluginFrontendDelegate::PostJsTask(std::function<void()>&& task, const std::string& name) {}

const std::string& PluginFrontendDelegate::GetAppID() const
{
    return "";
}

const std::string& PluginFrontendDelegate::GetAppName() const
{
    return "";
}

const std::string& PluginFrontendDelegate::GetVersionName() const
{
    return "";
}

int32_t PluginFrontendDelegate::GetVersionCode() const
{
    return 0;
}

double PluginFrontendDelegate::MeasureText(const MeasureContext& context)
{
    return 0;
}

void PluginFrontendDelegate::ShowToast(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback)
{}

void PluginFrontendDelegate::ShowDialog(const std::string& title, const std::string& message,
    const std::vector<ButtonInfo>& buttons, bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
    const std::set<std::string>& callbacks)
{}

Rect PluginFrontendDelegate::GetBoundingRectData(NodeId nodeId)
{
    Rect rect;
    return rect;
}

std::string PluginFrontendDelegate::GetInspector(NodeId nodeId)
{
    std::string attrs;

    return attrs;
}

void PluginFrontendDelegate::SetCallBackResult(const std::string& callBackId, const std::string& result) {}

void PluginFrontendDelegate::WaitTimer(
    const std::string& callbackId, const std::string& delay, bool isInterval, bool isFirst)
{}

void PluginFrontendDelegate::ClearTimer(const std::string& callbackId) {}

void PluginFrontendDelegate::PostSyncTaskToPage(std::function<void()>&& task, const std::string& name) {}

void PluginFrontendDelegate::AddTaskObserver(std::function<void()>&& task) {}

void PluginFrontendDelegate::RemoveTaskObserver() {}

bool PluginFrontendDelegate::GetAssetContent(const std::string& url, std::string& content)
{
    return GetAssetContentImpl(assetManager_, url, content);
}

bool PluginFrontendDelegate::GetAssetContent(const std::string& url, std::vector<uint8_t>& content)
{
    return GetAssetContentImpl(assetManager_, url, content);
}

std::string PluginFrontendDelegate::GetAssetPath(const std::string& url)
{
    return GetAssetPathImpl(assetManager_, url);
}

void PluginFrontendDelegate::LoadPage(
    int32_t pageId, const PageTarget& target, bool isMainPage, const std::string& params)
{}

void PluginFrontendDelegate::LoadJS(const RefPtr<Framework::JsAcePage>& page, const std::string& url, bool isMainPage)
{}

void PluginFrontendDelegate::OnSurfaceChanged() {}

void PluginFrontendDelegate::OnPageReady(const RefPtr<JsAcePage>& page, const std::string& url, bool isMainPage) {}

void PluginFrontendDelegate::OnPrePageChange(const RefPtr<JsAcePage>& page)
{
    if (page && page->GetDomDocument() && jsAccessibilityManager_) {
        jsAccessibilityManager_->SetRootNodeId(page->GetDomDocument()->GetRootNodeId());
    }
}

void PluginFrontendDelegate::FlushPageCommand(const RefPtr<JsAcePage>& page, const std::string& url, bool isMainPage) {}

void PluginFrontendDelegate::AddPageLocked(const RefPtr<JsAcePage>& page) {}

void PluginFrontendDelegate::SetCurrentPage(int32_t pageId) {}

void PluginFrontendDelegate::OnPushPageSuccess(const RefPtr<JsAcePage>& page, const std::string& url) {}

void PluginFrontendDelegate::OnPopToPageSuccess(const std::string& url) {}

void PluginFrontendDelegate::PopToPage(const std::string& url) {}

void PluginFrontendDelegate::PopToPageTransitionListener(
    const TransitionEvent& event, const std::string& url, int32_t pageId)
{}

void PluginFrontendDelegate::OnPageShow() {}

void PluginFrontendDelegate::OnPageHide() {}

void PluginFrontendDelegate::OnPageDestroy(int32_t pageId) {}

int32_t PluginFrontendDelegate::GetPageIdByUrl(const std::string& url)
{
    return 0;
}

RefPtr<JsAcePage> PluginFrontendDelegate::GetPage(int32_t pageId) const
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto itPage = pageMap_.find(pageId);
    if (itPage == pageMap_.end()) {
        LOGE("the page is not in the map");
        return nullptr;
    }
    return itPage->second;
}

bool PluginFrontendDelegate::OnPageBackPress()
{
    auto result = false;
    return result;
}

void PluginFrontendDelegate::SetColorMode(ColorMode colorMode) {}

void PluginFrontendDelegate::FlushAnimationTasks() {}

void PluginFrontendDelegate::AttachPipelineContext(const RefPtr<PipelineBase>& context) {}

RefPtr<PipelineBase> PluginFrontendDelegate::GetPipelineContext()
{
    return pipelineContextHolder_.Get();
}

void PluginFrontendDelegate::RebuildAllPages() {}

void PluginFrontendDelegate::UpdatePlugin(const std::string& content) {}
} // namespace OHOS::Ace::Framework
