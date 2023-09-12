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

#include "frameworks/bridge/plugin_frontend/plugin_frontend.h"

namespace OHOS::Ace {
PluginFrontend::~PluginFrontend() = default;

void PluginFrontend::Destroy() {}

bool PluginFrontend::Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor)
{
    type_ = type;
    taskExecutor_ = taskExecutor;
    return true;
}

void PluginFrontend::AttachPipelineContext(const RefPtr<PipelineBase>& context) {}

void PluginFrontend::SetAssetManager(const RefPtr<AssetManager>& assetManager) {}

void PluginFrontend::InitializeFrontendDelegate(const RefPtr<TaskExecutor>& taskExecutor) {}

void PluginFrontend::RunPage(const std::string& url, const std::string& params) {}
void PluginFrontend::ReplacePage(const std::string& url, const std::string& params) {}

void PluginFrontend::PushPage(const std::string& url, const std::string& params) {}

// navigator component call router
void PluginFrontend::NavigatePage(uint8_t type, const PageTarget& target, const std::string& params) {}

void PluginFrontend::SendCallbackMessage(const std::string& callbackId, const std::string& data) const {}

void PluginFrontend::SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const {}

void PluginFrontend::TransferComponentResponseData(int callbackId, int32_t code, std::vector<uint8_t>&& data) const {}

void PluginFrontend::TransferJsResponseData(int callbackId, int32_t code, std::vector<uint8_t>&& data) const {}

#if defined(PREVIEW)
void PluginFrontend::TransferJsResponseDataPreview(int callbackId, int32_t code, ResponseData responseData) const
{
    delegate_->TransferJsResponseDataPreview(callbackId, code, responseData);
}
#endif

void PluginFrontend::TransferJsPluginGetError(int callbackId, int32_t errorCode, std::string&& errorMessage) const {}

void PluginFrontend::TransferJsEventData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const {}

void PluginFrontend::LoadPluginJsCode(std::string&& jsCode) const {}

void PluginFrontend::LoadPluginJsByteCode(std::vector<uint8_t>&& jsCode, std::vector<int32_t>&& jsCodeLen) const {}

void PluginFrontend::UpdateState(Frontend::State state) {}

void PluginFrontend::OnWindowDisplayModeChanged(bool isShownInMultiWindow, const std::string& data) {}

void PluginFrontend::OnSaveAbilityState(std::string& data) {}

void PluginFrontend::OnRestoreAbilityState(const std::string& data) {}

void PluginFrontend::OnNewWant(const std::string& data) {}

RefPtr<AccessibilityManager> PluginFrontend::GetAccessibilityManager() const
{
    return nullptr;
}

WindowConfig& PluginFrontend::GetWindowConfig()
{
    static WindowConfig windowConfig;
    return windowConfig;
}

bool PluginFrontend::OnBackPressed()
{
    return true;
}

void PluginFrontend::OnShow() {}

void PluginFrontend::OnHide() {}

void PluginFrontend::OnConfigurationUpdated(const std::string& data) {}

void PluginFrontend::OnActive() {}

void PluginFrontend::OnInactive() {}

bool PluginFrontend::OnStartContinuation()
{
    return true;
}

void PluginFrontend::OnCompleteContinuation(int32_t code) {}

void PluginFrontend::OnMemoryLevel(const int32_t level) {}

void PluginFrontend::OnSaveData(std::string& data) {}

void PluginFrontend::GetPluginsUsed(std::string& data) {}

bool PluginFrontend::OnRestoreData(const std::string& data)
{
    return true;
}

void PluginFrontend::OnRemoteTerminated() {}

void PluginFrontend::OnNewRequest(const std::string& data) {}

void PluginFrontend::CallRouterBack() {}

void PluginFrontend::OnSurfaceChanged(int32_t width, int32_t height) {}

void PluginFrontend::DumpFrontend() const {}

std::string PluginFrontend::GetPagePath() const
{
    return "";
}

void PluginFrontend::TriggerGarbageCollection() {}

void PluginFrontend::SetColorMode(ColorMode colorMode) {}

void PluginFrontend::RebuildAllPages() {}

void PluginFrontend::NotifyAppStorage(const std::string& key, const std::string& value) {}

void PluginFrontend::UpdatePlugin(const std::string& content) {}

void PluginEventHandler::HandleAsyncEvent(const EventMarker& eventMarker) {}

void PluginEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info) {}

void PluginEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, const std::shared_ptr<BaseEventInfo>& info) {}

void PluginEventHandler::HandleSyncEvent(const EventMarker& eventMarker, const KeyEvent& info, bool& result) {}

void PluginEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, int32_t param) {}

void PluginEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, const KeyEvent& info) {}

void PluginEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, const std::string& param) {}

void PluginEventHandler::HandleSyncEvent(const EventMarker& eventMarker, bool& result) {}

void PluginEventHandler::HandleSyncEvent(const EventMarker& eventMarker, const std::shared_ptr<BaseEventInfo>& info) {}

void PluginEventHandler::HandleSyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info, bool& result) {}

void PluginEventHandler::HandleSyncEvent(const EventMarker& eventMarker, const std::string& param, std::string& result)
{}

void PluginEventHandler::HandleSyncEvent(
    const EventMarker& eventMarker, const std::string& componentId, const int32_t nodeId, const bool isDestroy)
{}
} // namespace OHOS::Ace
