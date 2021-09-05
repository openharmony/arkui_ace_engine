/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/frontend_delegate_declarative.h"

#include <atomic>
#include <regex>
#include <string>

#ifndef OHOS_STANDARD_SYSTEM
#include "third_party/skia/include/core/SkImage.h"
#endif

#include "ability.h"
#include "ability_info.h"
#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/resource/ace_res_config.h"
#include "base/thread/background_task_executor.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/common/platform_bridge.h"
#include "core/common/thread_checker.h"
#include "core/components/dialog/dialog_component.h"
#include "core/components/toast/toast_component.h"
#include "frameworks/bridge/common/manifest/manifest_parser.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/js_frontend/js_ace_page.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr int32_t INVALID_PAGE_ID = -1;
constexpr int32_t MAX_ROUTER_STACK = 32;
constexpr int32_t TOAST_TIME_MAX = 10000;    // ms
constexpr int32_t TOAST_TIME_DEFAULT = 1500; // ms
constexpr int32_t MAX_PAGE_ID_SIZE = sizeof(uint64_t) * 8;
constexpr int32_t NANO_TO_MILLI = 1000000; // nanosecond to millisecond
constexpr int32_t TO_MILLI = 1000;         // second to millisecond

const char MANIFEST_JSON[] = "manifest.json";
const char FILE_TYPE_JSON[] = ".json";
const char I18N_FOLDER[] = "i18n/";
const char RESOURCES_FOLDER[] = "resources/";
const char STYLES_FOLDER[] = "styles/";
const char I18N_FILE_SUFFIX[] = "/properties/string.json";

} // namespace

int32_t FrontendDelegateDeclarative::GenerateNextPageId()
{
    for (int32_t idx = 0; idx < MAX_PAGE_ID_SIZE; ++idx) {
        uint64_t bitMask = (1ULL << idx);
        if ((bitMask & pageIdPool_.fetch_or(bitMask, std::memory_order_relaxed)) == 0) {
            return idx;
        }
    }
    return INVALID_PAGE_ID;
}

void FrontendDelegateDeclarative::RecyclePageId(int32_t pageId)
{
    if (pageId < 0 && pageId >= MAX_PAGE_ID_SIZE) {
        return;
    }
    uint64_t bitMask = (1ULL << pageId);
    pageIdPool_.fetch_and(~bitMask, std::memory_order_relaxed);
}

FrontendDelegateDeclarative::FrontendDelegateDeclarative(const RefPtr<TaskExecutor>& taskExecutor,
    const LoadJsCallback& loadCallback, const JsMessageDispatcherSetterCallback& transferCallback,
    const EventCallback& asyncEventCallback, const EventCallback& syncEventCallback,
    const UpdatePageCallback& updatePageCallback, const ResetStagingPageCallback& resetLoadingPageCallback,
    const DestroyPageCallback& destroyPageCallback, const DestroyApplicationCallback& destroyApplicationCallback,
    const UpdateApplicationStateCallback& updateApplicationStateCallback,
    const TimerCallback& timerCallback, const MediaQueryCallback& mediaQueryCallback,
    const RequestAnimationCallback& requestAnimationCallback, const JsCallback& jsCallback,
    const OnWindowDisplayModeChangedCallBack& onWindowDisplayModeChangedCallBack,
    const OnConfigurationUpdatedCallBack& onConfigurationUpdatedCallBack)
    : loadJs_(loadCallback), dispatcherCallback_(transferCallback), asyncEvent_(asyncEventCallback),
      syncEvent_(syncEventCallback), updatePage_(updatePageCallback), resetStagingPage_(resetLoadingPageCallback),
      destroyPage_(destroyPageCallback), destroyApplication_(destroyApplicationCallback),
      updateApplicationState_(updateApplicationStateCallback), timer_(timerCallback),
      mediaQueryCallback_(mediaQueryCallback), requestAnimationCallback_(requestAnimationCallback),
      jsCallback_(jsCallback), onWindowDisplayModeChanged_(onWindowDisplayModeChangedCallBack),
      onConfigurationUpdated_(onConfigurationUpdatedCallBack),
      manifestParser_(AceType::MakeRefPtr<ManifestParser>()),
      jsAccessibilityManager_(AccessibilityNodeManager::Create()),
      mediaQueryInfo_(AceType::MakeRefPtr<MediaQueryInfo>()), taskExecutor_(taskExecutor)
{
    LOGD("FrontendDelegateDeclarative create");
}

FrontendDelegateDeclarative::~FrontendDelegateDeclarative()
{
    CHECK_RUN_ON(JS);
    LOG_DESTROY();
}

int32_t FrontendDelegateDeclarative::GetMinPlatformVersion()
{
    return manifestParser_->GetMinPlatformVersion();
}

void FrontendDelegateDeclarative::RunPage(const std::string& url, const std::string& params)
{
    ACE_SCOPED_TRACE("FrontendDelegateDeclarative::RunPage");

    LOGI("FrontendDelegateDeclarative RunPage url=%{private}s", url.c_str());
    std::string jsonContent;
    if (GetAssetContent(MANIFEST_JSON, jsonContent)) {
        manifestParser_->Parse(jsonContent);
        manifestParser_->Printer();
    } else {
        LOGE("RunPage parse manifest.json failed");
        EventReport::SendPageRouterException(PageRouterExcepType::RUN_PAGE_ERR, url);
    }

    if (!url.empty()) {
        mainPagePath_ = manifestParser_->GetRouter()->GetPagePath(url);
    } else {
        mainPagePath_ = manifestParser_->GetRouter()->GetEntry();
    }
    LoadPage(GenerateNextPageId(), PageTarget(mainPagePath_), true, params);
}

void FrontendDelegateDeclarative::ChangeLocale(const std::string& language, const std::string& countryOrRegion)
{
    LOGD("JSFrontend ChangeLocale");
    taskExecutor_->PostTask(
        [language, countryOrRegion]() { AceApplicationInfo::GetInstance().ChangeLocale(language, countryOrRegion); },
        TaskExecutor::TaskType::PLATFORM);
}

void FrontendDelegateDeclarative::GetI18nData(std::unique_ptr<JsonValue>& json)
{
    auto data = JsonUtil::CreateArray(true);
    GetConfigurationCommon(I18N_FOLDER, data);
    auto i18nData = JsonUtil::Create(true);
    i18nData->Put("resources", data);
    json->Put("i18n", i18nData);
}

void FrontendDelegateDeclarative::GetResourceConfiguration(std::unique_ptr<JsonValue>& json)
{
    auto data = JsonUtil::CreateArray(true);
    GetConfigurationCommon(RESOURCES_FOLDER, data);
    json->Put("resourcesConfiguration", data);
}

void FrontendDelegateDeclarative::GetConfigurationCommon(const std::string& filePath, std::unique_ptr<JsonValue>& data)
{
    std::vector<std::string> files;
    //if (assetManager_) {
    //    assetManager_->GetAssetList(filePath, files);
    //}
    if (!AceApplicationInfo::GetInstance().GetFiles(filePath, files)) {
        LOGE("Get configuration files fail!");
        return;
    }

    std::vector<std::string> fileNameList;
    for (const auto& file : files) {
        if (EndWith(file, FILE_TYPE_JSON) && !StartWith(file, STYLES_FOLDER)) {
            fileNameList.emplace_back(file.substr(0, file.size() - (sizeof(FILE_TYPE_JSON) - 1)));
        }
    }

    std::vector<std::string> priorityFileName;
    if (filePath.compare(I18N_FOLDER) == 0) {
        auto localeTag = AceApplicationInfo::GetInstance().GetLocaleTag();
        priorityFileName = AceResConfig::GetLocaleFallback(localeTag, fileNameList);
    } else {
        priorityFileName = AceResConfig::GetResourceFallback(fileNameList);
    }

    for (const auto& fileName : priorityFileName) {
        auto fileFullPath = filePath + fileName + std::string(FILE_TYPE_JSON);
        std::string content;
        if (GetAssetContent(fileFullPath, content)) {
            auto fileData = ParseFileData(content);
            if (fileData == nullptr) {
                LOGW("parse %{private}s.json content failed", filePath.c_str());
            } else {
                data->Put(fileData);
            }
        }
    }
}

void FrontendDelegateDeclarative::LoadResourceConfiguration(std::map<std::string, std::string>& mediaResourceFileMap,
    std::unique_ptr<JsonValue>& currentResourceData)
{
    std::vector<std::string> files;
    //if (assetManager_) {
    //    assetManager_->GetAssetList(RESOURCES_FOLDER, files);
    //}
    if (!AceApplicationInfo::GetInstance().GetFiles(RESOURCES_FOLDER, files)) {
        LOGE("Get configuration files fail!");
        return;
    }

    std::set<std::string> resourceFolderName;
    for (const auto& file : files) {
        if (file.find_first_of("/") != std::string::npos) {
            resourceFolderName.insert(file.substr(0, file.find_first_of("/")));
        }
    }

    std::vector<std::string> sortedResourceFolderPath =
        AceResConfig::GetDeclarativeResourceFallback(resourceFolderName);
    for (const auto& folderName : sortedResourceFolderPath) {
        auto fileFullPath = std::string(RESOURCES_FOLDER) + folderName + std::string(I18N_FILE_SUFFIX);
        std::string content;
        if (GetAssetContent(fileFullPath, content)) {
            auto fileData = ParseFileData(content);
            if (fileData == nullptr) {
                LOGW("parse %{private}s i18n content failed", fileFullPath.c_str());
            } else {
                currentResourceData->Put(fileData);
            }
        }
    }

    std::set<std::string> mediaFileName;
    for (const auto& file : files) {
        if (file.find_first_of("/") == std::string::npos) {
            continue;
        }
        auto mediaPathName = file.substr(file.find_first_of("/"));
        std::regex mediaPartten("^\\/media\\/\\w*(\\.jpg|\\.png|\\.gif|\\.svg|\\.webp|\\.bmp)$");
        std::smatch result;
        if (std::regex_match(mediaPathName, result, mediaPartten)) {
            mediaFileName.insert(mediaPathName.substr(mediaPathName.find_first_of("/")));
        }
    }

    auto currentResTag = AceResConfig::GetCurrentDeviceResTag();
    auto currentResolutionTag = currentResTag.substr(currentResTag.find_last_of("-") + 1);
    for (auto folderName : sortedResourceFolderPath) {
        for (auto fileName : mediaFileName) {
            if (mediaResourceFileMap.find(fileName) != mediaResourceFileMap.end()) {
                continue;
            }
            auto fullFileName = folderName + fileName;
            if (std::find(files.begin(), files.end(), fullFileName) != files.end()) {
                mediaResourceFileMap.emplace(fileName.substr(fileName.find_last_of("/") + 1),
                    std::string(RESOURCES_FOLDER).append(fullFileName));
            }
        }
        if (mediaResourceFileMap.size() == mediaFileName.size()) {
            break;
        }
    }
}

void FrontendDelegateDeclarative::OnJSCallback(const std::string& callbackId, const std::string& data)
{
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), callbackId, args = std::move(data)] {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->jsCallback_(callbackId, args);
            }
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarative::SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const
{
    LOGD("FrontendDelegateDeclarative SetJsMessageDispatcher");
    taskExecutor_->PostTask([dispatcherCallback = dispatcherCallback_, dispatcher] { dispatcherCallback(dispatcher); },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarative::TransferComponentResponseData(int32_t callbackId, int32_t code,
    std::vector<uint8_t>&& data)
{
    LOGD("FrontendDelegateDeclarative TransferComponentResponseData");
    auto pipelineContext = pipelineContextHolder_.Get();
    WeakPtr<PipelineContext> contextWeak(pipelineContext);
    taskExecutor_->PostTask(
        [callbackId, data = std::move(data), contextWeak]() mutable {
            auto context = contextWeak.Upgrade();
            if (!context) {
                LOGE("context is null");
            } else if (!context->GetMessageBridge()) {
                LOGE("messageBridge is null");
            } else {
                context->GetMessageBridge()->HandleCallback(callbackId, std::move(data));
            }
        },
        TaskExecutor::TaskType::UI);
}

void FrontendDelegateDeclarative::TransferJsResponseData(
    int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const
{
    LOGD("FrontendDelegateDeclarative TransferJsResponseData");
    if (groupJsBridge_ && groupJsBridge_->ForwardToWorker(callbackId)) {
        LOGD("FrontendDelegateDeclarative Forward to worker.");
        groupJsBridge_->TriggerModuleJsCallback(callbackId, code, std::move(data));
        return;
    }

    taskExecutor_->PostTask(
        [callbackId, code, data = std::move(data), groupJsBridge = groupJsBridge_]() mutable {
            if (groupJsBridge) {
                groupJsBridge->TriggerModuleJsCallback(callbackId, code, std::move(data));
            }
        },
        TaskExecutor::TaskType::JS);
}

#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
void FrontendDelegateDeclarative::TransferJsResponseDataPreview(
    int32_t callbackId, int32_t code, ResponseData responseData) const
{
    LOGI("FrontendDelegateDeclarative TransferJsResponseDataPreview");
    taskExecutor_->PostTask(
        [callbackId, code, responseData, groupJsBridge = groupJsBridge_]() mutable {
            if (groupJsBridge) {
                groupJsBridge->TriggerModuleJsCallbackPreview(callbackId, code, responseData);
            }
        },
        TaskExecutor::TaskType::JS);
}
#endif

void FrontendDelegateDeclarative::TransferJsPluginGetError(
    int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const
{
    LOGD("FrontendDelegateDeclarative TransferJsPluginGetError");
    taskExecutor_->PostTask(
        [callbackId, errorCode, errorMessage = std::move(errorMessage), groupJsBridge = groupJsBridge_]() mutable {
            if (groupJsBridge) {
                groupJsBridge->TriggerModulePluginGetErrorCallback(callbackId, errorCode, std::move(errorMessage));
            }
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarative::TransferJsEventData(int32_t callbackId, int32_t code,
    std::vector<uint8_t>&& data) const
{
    taskExecutor_->PostTask(
        [callbackId, code, data = std::move(data), groupJsBridge = groupJsBridge_]() mutable {
            if (groupJsBridge) {
                groupJsBridge->TriggerEventJsCallback(callbackId, code, std::move(data));
            }
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarative::LoadPluginJsCode(std::string&& jsCode) const
{
    LOGD("FrontendDelegateDeclarative LoadPluginJsCode");
    taskExecutor_->PostTask(
        [jsCode = std::move(jsCode), groupJsBridge = groupJsBridge_]() mutable {
            if (groupJsBridge) {
                groupJsBridge->LoadPluginJsCode(std::move(jsCode));
            }
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarative::LoadPluginJsByteCode(
    std::vector<uint8_t>&& jsCode, std::vector<int32_t>&& jsCodeLen) const
{
    LOGD("FrontendDelegateDeclarative LoadPluginJsByteCode");
    if (groupJsBridge_ == nullptr) {
        LOGE("groupJsBridge_ is nullptr");
        return;
    }
    taskExecutor_->PostTask(
        [jsCode = std::move(jsCode), jsCodeLen = std::move(jsCodeLen), groupJsBridge = groupJsBridge_]() mutable {
            groupJsBridge->LoadPluginJsByteCode(std::move(jsCode), std::move(jsCodeLen));
        },
        TaskExecutor::TaskType::JS);
}

bool FrontendDelegateDeclarative::OnPageBackPress()
{
    auto result = false;
    taskExecutor_->PostSyncTask(
        [weak = AceType::WeakClaim(this), &result] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            auto pageId = delegate->GetRunningPageId();
            auto page = delegate->GetPage(pageId);
            if (page) {
                result = page->FireDeclarativeOnBackPressCallback();
            }
        },
        TaskExecutor::TaskType::JS);
    return result;
}

void FrontendDelegateDeclarative::NotifyAppStorage(const WeakPtr<Framework::JsEngine>& jsEngineWeak,
    const std::string& key, const std::string& value)
{
    taskExecutor_->PostTask(
        [jsEngineWeak, key, value] {
            auto jsEngine = jsEngineWeak.Upgrade();
            if (!jsEngine) {
                return;
            }
            jsEngine->NotifyAppStorage(key, value);
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarative::OnSuspended()
{
    FireAsyncEvent("_root", std::string("\"viewsuspended\",null,null"), std::string(""));
}

void FrontendDelegateDeclarative::OnBackGround()
{
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this)] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            delegate->OnPageHide();
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarative::OnForground()
{
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this)] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            delegate->OnPageShow();
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarative::OnConfigurationUpdated(const std::string& data)
{
    taskExecutor_->PostSyncTask(
        [onConfigurationUpdated = onConfigurationUpdated_, data] {
            onConfigurationUpdated(data);
        },
        TaskExecutor::TaskType::JS);
}

bool FrontendDelegateDeclarative::OnStartContinuation()
{
    return FireSyncEvent("_root", std::string("\"onStartContinuation\","), std::string(""));
}

void FrontendDelegateDeclarative::OnCompleteContinuation(int32_t code)
{
    FireSyncEvent("_root", std::string("\"onCompleteContinuation\","), std::to_string(code));
}

void FrontendDelegateDeclarative::OnSaveData(std::string& data)
{
    std::string savedData;
    FireSyncEvent("_root", std::string("\"onSaveData\","), std::string(""), savedData);
    std::string pageUri = GetRunningPageUrl();
    data = std::string("{\"url\":\"").append(pageUri).append("\",\"__remoteData\":").append(savedData).append("}");
}

void FrontendDelegateDeclarative::GetPluginsUsed(std::string& data)
{
    if (!GetAssetContentImpl(assetManager_, "module_collection.txt", data)) {
        LOGW("read failed, will load all the system plugin");
        data = "All";
    }
}

bool FrontendDelegateDeclarative::OnRestoreData(const std::string& data)
{
    LOGD("OnRestoreData: restores the user data to shareData from remote ability");
    return FireSyncEvent("_root", std::string("\"onRestoreData\","), data);
}

void FrontendDelegateDeclarative::OnNewRequest(const std::string& data)
{
    FireSyncEvent("_root", std::string("\"onNewRequest\","), data);
}

void FrontendDelegateDeclarative::CallPopPage()
{
    PopPage();
}

void FrontendDelegateDeclarative::ResetStagingPage()
{
    taskExecutor_->PostTask([resetStagingPage = resetStagingPage_] { resetStagingPage(); }, TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarative::OnApplicationDestroy(const std::string& packageName)
{
    taskExecutor_->PostSyncTask(
        [destroyApplication = destroyApplication_, packageName] { destroyApplication(packageName); },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarative::UpdateApplicationState(const std::string& packageName, Frontend::State state)
{
    taskExecutor_->PostSyncTask(
        [updateApplicationState = updateApplicationState_, packageName, state] {
            updateApplicationState(packageName, state);
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarative::OnWindowDisplayModeChanged(bool isShownInMultiWindow, const std::string& data)
{
    taskExecutor_->PostSyncTask(
        [onWindowDisplayModeChanged = onWindowDisplayModeChanged_, isShownInMultiWindow, data] {
            onWindowDisplayModeChanged(isShownInMultiWindow, data);
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarative::FireAsyncEvent(
    const std::string& eventId, const std::string& param, const std::string& jsonArgs)
{
    LOGD("FireAsyncEvent eventId: %{public}s", eventId.c_str());
    std::string args = param;
    args.append(",null").append(",null"); // callback and dom changes
    if (!jsonArgs.empty()) {
        args.append(",").append(jsonArgs); // method args
    }
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), eventId, args = std::move(args)] {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->asyncEvent_(eventId, args);
            }
        },
        TaskExecutor::TaskType::JS);
}

bool FrontendDelegateDeclarative::FireSyncEvent(
    const std::string& eventId, const std::string& param, const std::string& jsonArgs)
{
    std::string resultStr;
    FireSyncEvent(eventId, param, jsonArgs, resultStr);
    return (resultStr == "true");
}

void FrontendDelegateDeclarative::FireSyncEvent(
    const std::string& eventId, const std::string& param, const std::string& jsonArgs, std::string& result)
{
    int32_t callbackId = callbackCnt_++;
    std::string args = param;
    args.append("{\"_callbackId\":\"").append(std::to_string(callbackId)).append("\"}").append(",null");
    if (!jsonArgs.empty()) {
        args.append(",").append(jsonArgs); // method args
    }
    taskExecutor_->PostSyncTask(
        [weak = AceType::WeakClaim(this), eventId, args = std::move(args)] {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->syncEvent_(eventId, args);
            }
        },
        TaskExecutor::TaskType::JS);

    result = jsCallBackResult_[callbackId];
    LOGD("FireSyncEvent eventId: %{public}s, callbackId: %{public}d", eventId.c_str(), callbackId);
    jsCallBackResult_.erase(callbackId);
}

void FrontendDelegateDeclarative::FireAccessibilityEvent(const AccessibilityEvent& accessibilityEvent)
{
    jsAccessibilityManager_->SendAccessibilityAsyncEvent(accessibilityEvent);
}

void FrontendDelegateDeclarative::InitializeAccessibilityCallback()
{
    jsAccessibilityManager_->InitializeCallback();
}

// Start FrontendDelegate overrides.
void FrontendDelegateDeclarative::Push(const std::string& uri, const std::string& params)
{
    Push(PageTarget(uri), params);
}

void FrontendDelegateDeclarative::Replace(const std::string& uri, const std::string& params)
{
    Replace(PageTarget(uri), params);
}

void FrontendDelegateDeclarative::Back(const std::string& uri, const std::string& params)
{
    BackWithTarget(PageTarget(uri), params);
}

void FrontendDelegateDeclarative::Push(const PageTarget& target, const std::string& params)
{
    if (target.url.empty()) {
        LOGE("router.Push uri is empty");
        return;
    }
    if (isRouteStackFull_) {
        LOGE("the router stack has reached its max size, you can't push any more pages.");
        EventReport::SendPageRouterException(PageRouterExcepType::PAGE_STACK_OVERFLOW_ERR, target.url);
        return;
    }

    std::string pagePath = manifestParser_->GetRouter()->GetPagePath(target.url);
    LOGD("router.Push pagePath = %{private}s", pagePath.c_str());
    if (!pagePath.empty()) {
        LoadPage(GenerateNextPageId(), PageTarget(pagePath, target.container), false, params);
    } else {
        LOGW("this uri not support in route push.");
    }
}

void FrontendDelegateDeclarative::Replace(const PageTarget& target, const std::string& params)
{
    if (target.url.empty()) {
        LOGE("router.Replace uri is empty");
        return;
    }

    std::string pagePath = manifestParser_->GetRouter()->GetPagePath(target.url);
    LOGD("router.Replace pagePath = %{private}s", pagePath.c_str());
    if (!pagePath.empty()) {
        LoadReplacePage(GenerateNextPageId(), PageTarget(pagePath, target.container), params);
    } else {
        LOGW("this uri not support in route replace.");
    }
}

void FrontendDelegateDeclarative::BackWithTarget(const PageTarget& target, const std::string& params)
{
    LOGD("router.Back path = %{private}s", target.url.c_str());
    if (target.url.empty()) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (pageRouteStack_.size() > 1) {
                pageId_ = pageRouteStack_[pageRouteStack_.size() - 2].pageId;
            }
            if (!params.empty()) {
                pageParamMap_[pageId_] = params;
            }
        }
        PopPage();
    } else {
        std::string pagePath = manifestParser_->GetRouter()->GetPagePath(target.url);
        LOGD("router.Back pagePath = %{private}s", pagePath.c_str());
        if (!pagePath.empty()) {
            pageId_ = GetPageIdByUrl(target.url);
            if (!params.empty()) {
                std::lock_guard<std::mutex> lock(mutex_);
                pageParamMap_[pageId_] = params;
            }
            PopToPage(pagePath);
        } else {
            LOGW("this uri not support in route Back.");
        }
    }
}

void FrontendDelegateDeclarative::Clear()
{
    ClearInvisiblePages();
}

int32_t FrontendDelegateDeclarative::GetStackSize() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return static_cast<int32_t>(pageRouteStack_.size());
}

void FrontendDelegateDeclarative::GetState(int32_t& index, std::string& name, std::string& path)
{
    std::string url;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pageRouteStack_.empty()) {
            return;
        }
        index = static_cast<int32_t>(pageRouteStack_.size());
        url = pageRouteStack_.back().url;
    }
    auto pos = url.rfind(".js");
    if (pos == url.length() - 3) {
        url = url.substr(0, pos);
    }
    pos = url.rfind("/");
    if (pos != std::string::npos) {
        name = url.substr(pos + 1);
        path = url.substr(0, pos + 1);
    }
}

std::string FrontendDelegateDeclarative::GetParams()
{
    if (pageParamMap_.find(pageId_) != pageParamMap_.end()) {
        return pageParamMap_.find(pageId_)->second;
    } else {
        return "";
    }
}

void FrontendDelegateDeclarative::TriggerPageUpdate(int32_t pageId, bool directExecute)
{
    auto page = GetPage(pageId);
    if (!page) {
        return;
    }

    auto jsPage = AceType::DynamicCast<Framework::JsAcePage>(page);
    ACE_DCHECK(jsPage);

    // Pop all JS command and execute them in UI thread.
    auto jsCommands = std::make_shared<std::vector<RefPtr<JsCommand>>>();
    jsPage->PopAllCommands(*jsCommands);

    auto pipelineContext = pipelineContextHolder_.Get();
    WeakPtr<Framework::JsAcePage> jsPageWeak(jsPage);
    WeakPtr<PipelineContext> contextWeak(pipelineContext);
    auto updateTask = [jsPageWeak, contextWeak, jsCommands] {
        ACE_SCOPED_TRACE("FlushUpdateCommands");
        auto jsPage = jsPageWeak.Upgrade();
        auto context = contextWeak.Upgrade();
        if (!jsPage || !context) {
            LOGE("Page update failed. page or context is null.");
            EventReport::SendPageRouterException(PageRouterExcepType::UPDATE_PAGE_ERR);
            return;
        }
        // Flush all JS commands.
        for (const auto& command : *jsCommands) {
            command->Execute(jsPage);
        }
        if (jsPage->GetDomDocument()) {
            jsPage->GetDomDocument()->HandleComponentPostBinding();
        }
        auto accessibilityManager = context->GetAccessibilityManager();
        if (accessibilityManager) {
            accessibilityManager->HandleComponentPostBinding();
        }

        jsPage->ClearShowCommand();
        std::vector<NodeId> dirtyNodes;
        jsPage->PopAllDirtyNodes(dirtyNodes);
        for (auto nodeId : dirtyNodes) {
            auto patchComponent = jsPage->BuildPagePatch(nodeId);
            if (patchComponent) {
                context->ScheduleUpdate(patchComponent);
            }
        }
    };

    taskExecutor_->PostTask(
        [updateTask, pipelineContext, directExecute]() {
            pipelineContext->AddPageUpdateTask(std::move(updateTask), directExecute);
        },
        TaskExecutor::TaskType::UI);
}

void FrontendDelegateDeclarative::PostJsTask(std::function<void()>&& task)
{
    taskExecutor_->PostTask(task, TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarative::RemoveVisibleChangeNode(NodeId id)
{
    LOGW("RemoveVisibleChangeNode: Not implemented yet.");
}

const std::string& FrontendDelegateDeclarative::GetAppID() const
{
    return manifestParser_->GetAppInfo()->GetAppID();
}

const std::string& FrontendDelegateDeclarative::GetAppName() const
{
    return manifestParser_->GetAppInfo()->GetAppName();
}

const std::string& FrontendDelegateDeclarative::GetVersionName() const
{
    return manifestParser_->GetAppInfo()->GetVersionName();
}

int32_t FrontendDelegateDeclarative::GetVersionCode() const
{
    return manifestParser_->GetAppInfo()->GetVersionCode();
}

void FrontendDelegateDeclarative::ShowToast(const std::string& message, int32_t duration, const std::string& bottom)
{
    LOGD("FrontendDelegateDeclarative ShowToast.");
    int32_t durationTime = std::clamp(duration, TOAST_TIME_DEFAULT, TOAST_TIME_MAX);
    auto pipelineContext = pipelineContextHolder_.Get();
    bool isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    taskExecutor_->PostTask(
        [durationTime, message, bottom, isRightToLeft, context = pipelineContext] {
            ToastComponent::GetInstance().Show(context, message, durationTime, bottom, isRightToLeft);
        },
        TaskExecutor::TaskType::UI);
}

void FrontendDelegateDeclarative::ShowDialog(const std::string& title, const std::string& message,
    const std::vector<std::pair<std::string, std::string>>& buttons, bool autoCancel,
    std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks)
{
    std::unordered_map<std::string, EventMarker> callbackMarkers;
    if (callbacks.find(COMMON_SUCCESS) != callbacks.end()) {
        auto successEventMarker = BackEndEventManager<void(int32_t)>::GetInstance().GetAvailableMarker();
        BackEndEventManager<void(int32_t)>::GetInstance().BindBackendEvent(
            successEventMarker, [callback, taskExecutor = taskExecutor_](int32_t successType) {
                taskExecutor->PostTask(
                    [callback, successType]() { callback(0, successType); }, TaskExecutor::TaskType::JS);
            });
        callbackMarkers.emplace(COMMON_SUCCESS, successEventMarker);
    }

    if (callbacks.find(COMMON_CANCEL) != callbacks.end()) {
        auto cancelEventMarker = BackEndEventManager<void()>::GetInstance().GetAvailableMarker();
        BackEndEventManager<void()>::GetInstance().BindBackendEvent(
            cancelEventMarker, [callback, taskExecutor = taskExecutor_] {
                taskExecutor->PostTask([callback]() { callback(1, 0); }, TaskExecutor::TaskType::JS);
            });
        callbackMarkers.emplace(COMMON_CANCEL, cancelEventMarker);
    }

    if (callbacks.find(COMMON_COMPLETE) != callbacks.end()) {
        auto completeEventMarker = BackEndEventManager<void()>::GetInstance().GetAvailableMarker();
        BackEndEventManager<void()>::GetInstance().BindBackendEvent(
            completeEventMarker, [callback, taskExecutor = taskExecutor_] {
                taskExecutor->PostTask([callback]() { callback(2, 0); }, TaskExecutor::TaskType::JS);
            });
        callbackMarkers.emplace(COMMON_COMPLETE, completeEventMarker);
    }

    DialogProperties dialogProperties = {
        .title = title,
        .content = message,
        .autoCancel = autoCancel,
        .buttons = buttons,
        .callbacks = std::move(callbackMarkers),
    };
    pipelineContextHolder_.Get()->ShowDialog(dialogProperties, AceApplicationInfo::GetInstance().IsRightToLeft());
}


Rect FrontendDelegateDeclarative::GetBoundingRectData(NodeId nodeId)
{
    Rect rect;
    auto task = [context = pipelineContextHolder_.Get(), nodeId, &rect]() {
        context->GetBoundingRectData(nodeId, rect);
    };
    PostSyncTaskToPage(task);
    return rect;
}

void FrontendDelegateDeclarative::SetCallBackResult(const std::string& callBackId, const std::string& result)
{
    jsCallBackResult_.try_emplace(StringToInt(callBackId), result);
}

void FrontendDelegateDeclarative::WaitTimer(
    const std::string& callbackId, const std::string& delay, bool isInterval, bool isFirst)
{
    if (!isFirst) {
        auto timeoutTaskIter = timeoutTaskMap_.find(callbackId);
        // If not find the callbackId in map, means this timer already was removed,
        // no need create a new cancelableTimer again.
        if (timeoutTaskIter == timeoutTaskMap_.end()) {
            return;
        }
    }

    int32_t delayTime = StringToInt(delay);
    // CancelableCallback class can only be executed once.
    CancelableCallback<void()> cancelableTimer;
    cancelableTimer.Reset([callbackId, delay, isInterval, call = timer_] { call(callbackId, delay, isInterval); });
    auto result = timeoutTaskMap_.try_emplace(callbackId, cancelableTimer);
    if (!result.second) {
        result.first->second = cancelableTimer;
    }
    taskExecutor_->PostDelayedTask(cancelableTimer, TaskExecutor::TaskType::JS, delayTime);
}

void FrontendDelegateDeclarative::ClearTimer(const std::string& callbackId)
{
    auto timeoutTaskIter = timeoutTaskMap_.find(callbackId);
    if (timeoutTaskIter != timeoutTaskMap_.end()) {
        timeoutTaskIter->second.Cancel();
        timeoutTaskMap_.erase(timeoutTaskIter);
    } else {
        LOGW("ClearTimer callbackId not found");
    }
}

void FrontendDelegateDeclarative::PostSyncTaskToPage(std::function<void()>&& task)
{
    pipelineContextHolder_.Get(); // Wait until Pipeline Context is attached.
    taskExecutor_->PostSyncTask(task, TaskExecutor::TaskType::UI);
}

void FrontendDelegateDeclarative::AddTaskObserver(std::function<void()>&& task)
{
    taskExecutor_->AddTaskObserver(std::move(task));
}

void FrontendDelegateDeclarative::RemoveTaskObserver()
{
    taskExecutor_->RemoveTaskObserver();
}

bool FrontendDelegateDeclarative::GetAssetContent(const std::string& url, std::string& content)
{
    return GetAssetContentImpl(assetManager_, url, content);
}

bool FrontendDelegateDeclarative::GetAssetContent(const std::string& url, std::vector<uint8_t>& content)
{
    return GetAssetContentImpl(assetManager_, url, content);
}

std::string FrontendDelegateDeclarative::GetAssetPath(const std::string& url)
{
    return GetAssetPathImpl(assetManager_, url);
}

void FrontendDelegateDeclarative::LoadPage(
    int32_t pageId, const PageTarget& target, bool isMainPage, const std::string& params)
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        pageId_ = pageId;
        pageParamMap_[pageId] = params;
    }
    auto url = target.url;
    LOGI("FrontendDelegateDeclarative LoadPage[%{private}d]: %{private}s.", pageId, url.c_str());
    if (pageId == INVALID_PAGE_ID) {
        LOGE("FrontendDelegateDeclarative, invalid page id");
        EventReport::SendPageRouterException(PageRouterExcepType::LOAD_PAGE_ERR, url);
        return;
    }
    if (isStagingPageExist_) {
        LOGE("FrontendDelegateDeclarative, load page failed, waiting for current page loading finish.");
        return;
    }
    isStagingPageExist_ = true;
    auto document = AceType::MakeRefPtr<DOMDocument>(pageId);
    auto page = AceType::MakeRefPtr<JsAcePage>(pageId, document, target.url, target.container);
    page->SetPageParams(params);
    page->SetFlushCallback([weak = AceType::WeakClaim(this), isMainPage](const RefPtr<JsAcePage>& acePage) {
        auto delegate = weak.Upgrade();
        if (delegate && acePage) {
            delegate->FlushPageCommand(acePage, acePage->GetUrl(), isMainPage);
        }
    });
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), page, url, isMainPage] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            delegate->loadJs_(url, page, isMainPage);
            page->FlushCommands();
            // just make sure the pipelineContext is created.
            auto pipeline = delegate->pipelineContextHolder_.Get();
            pipeline->SetMinPlatformVersion(delegate->GetMinPlatformVersion());
            delegate->taskExecutor_->PostTask(
                [weak, page] {
                    auto delegate = weak.Upgrade();
                    if (delegate && delegate->pipelineContextHolder_.Get()) {
                        delegate->pipelineContextHolder_.Get()->FlushFocus();
                    }
                    if (page->GetDomDocument()) {
                        page->GetDomDocument()->HandlePageLoadFinish();
                    }
                },
                TaskExecutor::TaskType::UI);
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarative::OnSurfaceChanged()
{
    if (mediaQueryInfo_->GetIsInit()) {
        mediaQueryInfo_->SetIsInit(false);
    }
    mediaQueryInfo_->EnsureListenerIdValid();
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarative::OnMediaQueryUpdate()
{
    if (mediaQueryInfo_->GetIsInit()) {
        return;
    }

    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this)] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            const auto& info = delegate->mediaQueryInfo_->GetMediaQueryInfo();
            // request css mediaquery
            std::string param("\"viewsizechanged\",");
            param.append(info);
            delegate->asyncEvent_("_root", param);

            // request js mediaquery
            const auto& listenerId = delegate->mediaQueryInfo_->GetListenerId();
            delegate->mediaQueryCallback_(listenerId, info);
            delegate->mediaQueryInfo_->ResetListenerId();
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarative::OnPageReady(
    const RefPtr<JsAcePage>& page, const std::string& url, bool isMainPage)
{
    LOGI("OnPageReady url = %{private}s", url.c_str());
    // Pop all JS command and execute them in UI thread.
    auto jsCommands = std::make_shared<std::vector<RefPtr<JsCommand>>>();
    page->PopAllCommands(*jsCommands);

    auto pipelineContext = pipelineContextHolder_.Get();
    page->SetPipelineContext(pipelineContext);
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), page, url, jsCommands, isMainPage] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            auto pipelineContext = delegate->pipelineContextHolder_.Get();
            // Flush all JS commands.
            for (const auto& command : *jsCommands) {
                command->Execute(page);
            }
            // Just clear all dirty nodes.
            page->ClearAllDirtyNodes();
            if (page->GetDomDocument()) {
                page->GetDomDocument()->HandleComponentPostBinding();
            }
            if (pipelineContext->GetAccessibilityManager()) {
                pipelineContext->GetAccessibilityManager()->HandleComponentPostBinding();
            }
            if (pipelineContext->CanPushPage()) {
                if (!isMainPage) {
                    delegate->OnPageHide();
                }
                pipelineContext->PushPage(page->BuildPage(url), page->GetStageElement());
                delegate->OnPushPageSuccess(page, url);
                delegate->SetCurrentPage(page->GetPageId());
                delegate->OnMediaQueryUpdate();
            } else {
                // This page has been loaded but become useless now, the corresponding js instance
                // must be destroyed to avoid memory leak.
                delegate->OnPageDestroy(page->GetPageId());
                delegate->ResetStagingPage();
            }
            delegate->isStagingPageExist_ = false;
            if (isMainPage) {
                delegate->OnPageShow();
            }
        },
        TaskExecutor::TaskType::UI);
}

void FrontendDelegateDeclarative::FlushPageCommand(
    const RefPtr<JsAcePage>& page, const std::string& url, bool isMainPage)
{
    if (!page) {
        return;
    }
    LOGI("FlushPageCommand FragmentCount(%{public}d)", page->FragmentCount());
    if (page->FragmentCount() == 1) {
        OnPageReady(page, url, isMainPage);
    } else {
        TriggerPageUpdate(page->GetPageId());
    }
}

void FrontendDelegateDeclarative::AddPageLocked(const RefPtr<JsAcePage>& page)
{
    auto result = pageMap_.try_emplace(page->GetPageId(), page);
    if (!result.second) {
        LOGW("the page has already in the map");
    }
}

void FrontendDelegateDeclarative::SetCurrentPage(int32_t pageId)
{
    LOGD("FrontendDelegateDeclarative SetCurrentPage pageId=%{private}d", pageId);
    auto page = GetPage(pageId);
    if (page != nullptr) {
        jsAccessibilityManager_->SetVersion(AccessibilityVersion::JS_DECLARATIVE_VERSION);
        jsAccessibilityManager_->SetRunningPage(page);
        taskExecutor_->PostTask([updatePage = updatePage_, page] { updatePage(page); }, TaskExecutor::TaskType::JS);
    } else {
        LOGE("FrontendDelegateDeclarative SetCurrentPage page is null.");
    }
}

void FrontendDelegateDeclarative::OnPushPageSuccess(
    const RefPtr<JsAcePage>& page, const std::string& url)
{
    std::lock_guard<std::mutex> lock(mutex_);
    AddPageLocked(page);
    pageRouteStack_.emplace_back(PageInfo { page->GetPageId(), url});
    if (pageRouteStack_.size() >= MAX_ROUTER_STACK) {
        isRouteStackFull_ = true;
        EventReport::SendPageRouterException(PageRouterExcepType::PAGE_STACK_OVERFLOW_ERR, page->GetUrl());
    }
    LOGI("OnPushPageSuccess size=%{private}zu,pageId=%{private}d,url=%{private}s", pageRouteStack_.size(),
        pageRouteStack_.back().pageId, pageRouteStack_.back().url.c_str());
}

void FrontendDelegateDeclarative::OnPopToPageSuccess(const std::string& url)
{
    std::lock_guard<std::mutex> lock(mutex_);
    while (!pageRouteStack_.empty()) {
        if (pageRouteStack_.back().url == url) {
            break;
        }
        OnPageDestroy(pageRouteStack_.back().pageId);
        pageMap_.erase(pageRouteStack_.back().pageId);
        pageParamMap_.erase(pageRouteStack_.back().pageId);
        pageRouteStack_.pop_back();
    }

    if (isRouteStackFull_) {
        isRouteStackFull_ = false;
    }
}

void FrontendDelegateDeclarative::PopToPage(const std::string& url)
{
    LOGD("FrontendDelegateDeclarative PopToPage url = %{private}s", url.c_str());
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), url] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            auto pageId = delegate->GetPageIdByUrl(url);
            if (pageId == INVALID_PAGE_ID) {
                return;
            }
            auto pipelineContext = delegate->pipelineContextHolder_.Get();
            if (!pipelineContext->CanPopPage()) {
                delegate->ResetStagingPage();
                return;
            }
            delegate->OnPageHide();
            pipelineContext->RemovePageTransitionListener(delegate->pageTransitionListenerId_);
            delegate->pageTransitionListenerId_ = pipelineContext->AddPageTransitionListener(
                [weak, url, pageId](
                    const TransitionEvent& event, const WeakPtr<PageElement>& in, const WeakPtr<PageElement>& out) {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        delegate->PopToPageTransitionListener(event, url, pageId);
                    }
                });
            pipelineContext->PopToPage(pageId);
        },
        TaskExecutor::TaskType::UI);
}

void FrontendDelegateDeclarative::PopToPageTransitionListener(
    const TransitionEvent& event, const std::string& url, int32_t pageId)
{
    if (event == TransitionEvent::POP_END) {
        OnPopToPageSuccess(url);
        SetCurrentPage(pageId);
        OnPageShow();
        OnMediaQueryUpdate();
    }
}

int32_t FrontendDelegateDeclarative::OnPopPageSuccess()
{
    std::lock_guard<std::mutex> lock(mutex_);
    pageMap_.erase(pageRouteStack_.back().pageId);
    pageParamMap_.erase(pageRouteStack_.back().pageId);
    pageRouteStack_.pop_back();
    if (isRouteStackFull_) {
        isRouteStackFull_ = false;
    }
    if (!pageRouteStack_.empty()) {
        return pageRouteStack_.back().pageId;
    }
    return INVALID_PAGE_ID;
}

void FrontendDelegateDeclarative::PopPage()
{
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this)] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            auto pipelineContext = delegate->pipelineContextHolder_.Get();
            if (delegate->GetStackSize() == 1) {
                if (delegate->disallowPopLastPage_) {
                    LOGW("Not allow back because this is the last page!");
                    return;
                }
                auto ability = static_cast<AppExecFwk::Ability*>(delegate->ability_);
                std::shared_ptr<AppExecFwk::AbilityInfo> info = ability->GetAbilityInfo();
                if (info != nullptr && info->isLauncherAbility) {
                    LOGW("launcher ability, return");
                    return;
                }
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
                delegate->OnPageHide();
                delegate->OnPageDestroy(delegate->GetRunningPageId());
                delegate->OnPopPageSuccess();
                pipelineContext->Finish();
#else
                LOGW("Can't back because this is the last page!");
#endif
                return;
            }
            if (!pipelineContext->CanPopPage()) {
                delegate->ResetStagingPage();
                return;
            }
            delegate->OnPageHide();
            pipelineContext->RemovePageTransitionListener(delegate->pageTransitionListenerId_);
            delegate->pageTransitionListenerId_ = pipelineContext->AddPageTransitionListener(
                [weak, destroyPageId = delegate->GetRunningPageId()](
                    const TransitionEvent& event, const WeakPtr<PageElement>& in, const WeakPtr<PageElement>& out) {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        delegate->PopPageTransitionListener(event, destroyPageId);
                    }
                });
            pipelineContext->PopPage();
        },
        TaskExecutor::TaskType::UI);
}

void FrontendDelegateDeclarative::PopPageTransitionListener(
    const TransitionEvent& event, int32_t destroyPageId)
{
    if (event == TransitionEvent::POP_END) {
        OnPageDestroy(destroyPageId);
        auto pageId = OnPopPageSuccess();
        SetCurrentPage(pageId);
        OnPageShow();
        OnMediaQueryUpdate();
    }
}

int32_t FrontendDelegateDeclarative::OnClearInvisiblePagesSuccess()
{
    std::lock_guard<std::mutex> lock(mutex_);
    PageInfo pageInfo = std::move(pageRouteStack_.back());
    pageRouteStack_.pop_back();
    for (const auto& info : pageRouteStack_) {
        OnPageDestroy(info.pageId);
        pageMap_.erase(info.pageId);
        pageParamMap_.erase(info.pageId);
    }
    pageRouteStack_.clear();
    int32_t resPageId = pageInfo.pageId;
    pageRouteStack_.emplace_back(std::move(pageInfo));
    if (isRouteStackFull_) {
        isRouteStackFull_ = false;
    }
    return resPageId;
}

void FrontendDelegateDeclarative::ClearInvisiblePages()
{
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this)] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            auto pipelineContext = delegate->pipelineContextHolder_.Get();
            if (pipelineContext->ClearInvisiblePages()) {
                auto pageId = delegate->OnClearInvisiblePagesSuccess();
                delegate->SetCurrentPage(pageId);
            }
        },
        TaskExecutor::TaskType::UI);
}

void FrontendDelegateDeclarative::OnReplacePageSuccess(
    const RefPtr<JsAcePage>& page, const std::string& url)
{
    if (!page) {
        return;
    }
    std::lock_guard<std::mutex> lock(mutex_);
    AddPageLocked(page);
    if (!pageRouteStack_.empty()) {
        pageMap_.erase(pageRouteStack_.back().pageId);
        pageParamMap_.erase(pageRouteStack_.back().pageId);
        pageRouteStack_.pop_back();
    }
    pageRouteStack_.emplace_back(PageInfo { page->GetPageId(), url});
}

void FrontendDelegateDeclarative::ReplacePage(
    const RefPtr<JsAcePage>& page, const std::string& url)
{
    LOGI("ReplacePage url = %{private}s", url.c_str());
    // Pop all JS command and execute them in UI thread.
    auto jsCommands = std::make_shared<std::vector<RefPtr<JsCommand>>>();
    page->PopAllCommands(*jsCommands);

    auto pipelineContext = pipelineContextHolder_.Get();
    page->SetPipelineContext(pipelineContext);
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), page, url, jsCommands] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            auto pipelineContext = delegate->pipelineContextHolder_.Get();
            // Flush all JS commands.
            for (const auto& command : *jsCommands) {
                command->Execute(page);
            }
            // Just clear all dirty nodes.
            page->ClearAllDirtyNodes();
            page->GetDomDocument()->HandleComponentPostBinding();
            pipelineContext->GetAccessibilityManager()->HandleComponentPostBinding();
            if (pipelineContext->CanReplacePage()) {
                delegate->OnPageHide();
                delegate->OnPageDestroy(delegate->GetRunningPageId());
                pipelineContext->ReplacePage(page->BuildPage(url), page->GetStageElement());
                delegate->OnReplacePageSuccess(page, url);
                delegate->SetCurrentPage(page->GetPageId());
                delegate->OnMediaQueryUpdate();
            } else {
                // This page has been loaded but become useless now, the corresponding js instance
                // must be destroyed to avoid memory leak.
                delegate->OnPageDestroy(page->GetPageId());
                delegate->ResetStagingPage();
            }
            delegate->isStagingPageExist_ = false;
        },
        TaskExecutor::TaskType::UI);
}

void FrontendDelegateDeclarative::LoadReplacePage(int32_t pageId, const PageTarget& target, const std::string& params)
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        pageId_ = pageId;
        pageParamMap_[pageId] = params;
    }
    auto url = target.url;
    LOGD("FrontendDelegateDeclarative LoadReplacePage[%{private}d]: %{private}s.", pageId, url.c_str());
    if (pageId == INVALID_PAGE_ID) {
        LOGE("FrontendDelegateDeclarative, invalid page id");
        EventReport::SendPageRouterException(PageRouterExcepType::REPLACE_PAGE_ERR, url);
        return;
    }
    if (isStagingPageExist_) {
        LOGE("FrontendDelegateDeclarative, replace page failed, waiting for current page loading finish.");
        EventReport::SendPageRouterException(PageRouterExcepType::REPLACE_PAGE_ERR, url);
        return;
    }
    isStagingPageExist_ = true;
    auto document = AceType::MakeRefPtr<DOMDocument>(pageId);
    auto page = AceType::MakeRefPtr<JsAcePage>(pageId, document, target.url, target.container);
    page->SetPageParams(params);
    taskExecutor_->PostTask(
        [page, url, weak = AceType::WeakClaim(this)] {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->loadJs_(url, page, false);
                delegate->ReplacePage(page, url);
            }
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarative::SetColorMode(ColorMode colorMode)
{
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarative::RebuildAllPages()
{
    std::unordered_map<int32_t, RefPtr<JsAcePage>> pages;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        pages.insert(pageMap_.begin(), pageMap_.end());
    }
    for (const auto& [pageId, page] : pages) {
        page->FireDeclarativeOnPageRefreshCallback();
        TriggerPageUpdate(page->GetPageId(), true);
    }
}

void FrontendDelegateDeclarative::OnPageShow()
{
    auto pageId = GetRunningPageId();
    auto page = GetPage(pageId);
    if (page) {
        page->FireDeclarativeOnPageAppearCallback();
    }
    FireAsyncEvent("_root", std::string("\"viewappear\",null,null"), std::string(""));
}

void FrontendDelegateDeclarative::OnPageHide()
{
    auto pageId = GetRunningPageId();
    auto page = GetPage(pageId);
    if (page) {
        page->FireDeclarativeOnPageDisAppearCallback();
    }
    FireAsyncEvent("_root", std::string("\"viewdisappear\",null,null"), std::string(""));
}

void FrontendDelegateDeclarative::OnPageDestroy(int32_t pageId)
{
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), pageId] {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->destroyPage_(pageId);
                delegate->RecyclePageId(pageId);
            }
        },
        TaskExecutor::TaskType::JS);
}

int32_t FrontendDelegateDeclarative::GetRunningPageId() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pageRouteStack_.empty()) {
        return INVALID_PAGE_ID;
    }
    return pageRouteStack_.back().pageId;
}

std::string FrontendDelegateDeclarative::GetRunningPageUrl() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pageRouteStack_.empty()) {
        return std::string();
    }
    const auto& pageUrl = pageRouteStack_.back().url;
    auto pos = pageUrl.rfind(".js");
    if (pos == pageUrl.length() - 3) {
        return pageUrl.substr(0, pos);
    }
    return pageUrl;
}

int32_t FrontendDelegateDeclarative::GetPageIdByUrl(const std::string& url)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto pageIter = std::find_if(std::rbegin(pageRouteStack_), std::rend(pageRouteStack_),
        [&url](const PageInfo& pageRoute) { return url == pageRoute.url; });
    if (pageIter != std::rend(pageRouteStack_)) {
        LOGD("GetPageIdByUrl pageId=%{private}d url=%{private}s", pageIter->pageId, url.c_str());
        return pageIter->pageId;
    }
    return INVALID_PAGE_ID;
}

RefPtr<JsAcePage> FrontendDelegateDeclarative::GetPage(int32_t pageId) const
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto itPage = pageMap_.find(pageId);
    if (itPage == pageMap_.end()) {
        LOGE("the page is not in the map");
        return nullptr;
    }
    return itPage->second;
}

void FrontendDelegateDeclarative::RegisterFont(const std::string& familyName, const std::string& familySrc)
{
    pipelineContextHolder_.Get()->RegisterFont(familyName, familySrc);
}

void FrontendDelegateDeclarative::HandleImage(
    const std::string& src, std::function<void(int32_t)>&& callback, const std::set<std::string>& callbacks)
{
    if (src.empty() || !callback) {
        return;
    }
    std::map<std::string, EventMarker> callbackMarkers;
    if (callbacks.find("success") != callbacks.end()) {
        auto successEventMarker = BackEndEventManager<void()>::GetInstance().GetAvailableMarker();
        successEventMarker.SetPreFunction([callback, taskExecutor = taskExecutor_]() {
            taskExecutor->PostTask([callback] { callback(0); }, TaskExecutor::TaskType::JS);
        });
        callbackMarkers.emplace("success", successEventMarker);
    }

    if (callbacks.find("fail") != callbacks.end()) {
        auto failEventMarker = BackEndEventManager<void()>::GetInstance().GetAvailableMarker();
        failEventMarker.SetPreFunction([callback, taskExecutor = taskExecutor_]() {
            taskExecutor->PostTask([callback] { callback(1); }, TaskExecutor::TaskType::JS);
        });
        callbackMarkers.emplace("fail", failEventMarker);
    }
    pipelineContextHolder_.Get()->CanLoadImage(src, callbackMarkers);
}

void FrontendDelegateDeclarative::PushJsCallbackToRenderNode(NodeId id, double ratio,
    std::function<void(bool, double)>&& callback)
{
    LOGW("Not implement in declarative frontend.");
}

void FrontendDelegateDeclarative::RequestAnimationFrame(const std::string& callbackId)
{
    CancelableCallback<void()> cancelableTask;
    cancelableTask.Reset([callbackId, call = requestAnimationCallback_, weak = AceType::WeakClaim(this)] {
        auto delegate = weak.Upgrade();
        if (delegate && call) {
            call(callbackId, delegate->GetSystemRealTime());
        }
    });
    animationFrameTaskMap_.try_emplace(callbackId, cancelableTask);
    animationFrameTaskIds_.emplace(callbackId);
}

uint64_t FrontendDelegateDeclarative::GetSystemRealTime()
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec * TO_MILLI + ts.tv_nsec / NANO_TO_MILLI;
}

void FrontendDelegateDeclarative::CancelAnimationFrame(const std::string& callbackId)
{
    auto animationTaskIter = animationFrameTaskMap_.find(callbackId);
    if (animationTaskIter != animationFrameTaskMap_.end()) {
        animationTaskIter->second.Cancel();
        animationFrameTaskMap_.erase(animationTaskIter);
    } else {
        LOGW("cancelAnimationFrame callbackId not found");
    }
}

void FrontendDelegateDeclarative::FlushAnimationTasks()
{
    while (!animationFrameTaskIds_.empty()) {
        const auto& callbackId = animationFrameTaskIds_.front();
        if (!callbackId.empty()) {
            auto taskIter = animationFrameTaskMap_.find(callbackId);
            if (taskIter != animationFrameTaskMap_.end()) {
                taskExecutor_->PostTask(taskIter->second, TaskExecutor::TaskType::JS);
            }
        }
        animationFrameTaskIds_.pop();
    }
}

SingleTaskExecutor FrontendDelegateDeclarative::GetAnimationJsTask()
{
    return SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::JS);
}

SingleTaskExecutor FrontendDelegateDeclarative::GetUiTask()
{
    return SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::UI);
}

void FrontendDelegateDeclarative::AttachPipelineContext(const RefPtr<PipelineContext>& context)
{
    context->SetOnPageShow([weak = AceType::WeakClaim(this)] {
        auto delegate = weak.Upgrade();
        if (delegate) {
            delegate->OnPageShow();
        }
    });
    context->SetAnimationCallback([weak = AceType::WeakClaim(this)] {
        auto delegate = weak.Upgrade();
        if (delegate) {
            delegate->FlushAnimationTasks();
        }
    });
    pipelineContextHolder_.Attach(context);
    jsAccessibilityManager_->SetPipelineContext(context);
    jsAccessibilityManager_->InitializeCallback();
}

void FrontendDelegateDeclarative::SetAssetManager(const RefPtr<AssetManager>& assetManager)
{
    assetManager_ = assetManager;
}

RefPtr<AssetManager> FrontendDelegateDeclarative::GetAssetManager() const
{
    return assetManager_;
}

RefPtr<PipelineContext> FrontendDelegateDeclarative::GetPipelineContext()
{
    return pipelineContextHolder_.Get();
}

} // namespace OHOS::Ace::Framework
