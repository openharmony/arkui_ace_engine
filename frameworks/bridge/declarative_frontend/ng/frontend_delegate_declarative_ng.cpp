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

#include "frameworks/bridge/declarative_frontend/ng/frontend_delegate_declarative_ng.h"

#include "base/i18n/localization.h"
#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/resource/ace_res_config.h"
#include "base/thread/background_task_executor.h"
#include "base/utils/measure_util.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/common/thread_checker.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/render/adapter/component_snapshot.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {

namespace {

const char MANIFEST_JSON[] = "manifest.json";
const char PAGES_JSON[] = "main_pages.json";
constexpr int32_t TOAST_TIME_MAX = 10000;    // ms
constexpr int32_t TOAST_TIME_DEFAULT = 1500; // ms
constexpr int32_t CALLBACK_ERRORCODE_CANCEL = 1;
constexpr int32_t CALLBACK_DATACODE_ZERO = 0;

// helper function to run OverlayManager task
// ensures that the task runs in subwindow instead of main Window
void MainWindowOverlay(std::function<void(RefPtr<NG::OverlayManager>)>&& task)
{
    auto currentId = Container::CurrentId();
    ContainerScope scope(currentId);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    context->GetTaskExecutor()->PostTask(
        [task = std::move(task), weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            task(overlayManager);
        },
        TaskExecutor::TaskType::UI);
}
} // namespace

FrontendDelegateDeclarativeNG::FrontendDelegateDeclarativeNG(const RefPtr<TaskExecutor>& taskExecutor)
    : taskExecutor_(taskExecutor), manifestParser_(AceType::MakeRefPtr<Framework::ManifestParser>()),
      mediaQueryInfo_(AceType::MakeRefPtr<MediaQueryInfo>()),
      jsAccessibilityManager_(AccessibilityNodeManager::Create())
{
    LOGD("FrontendDelegateDeclarativeNG create");
}

void FrontendDelegateDeclarativeNG::SetMediaQueryCallback(MediaQueryCallback&& mediaQueryCallback)
{
    mediaQueryCallback_ = mediaQueryCallback;
}

void FrontendDelegateDeclarativeNG::SetLayoutInspectorCallback(const LayoutInspectorCallback& layoutInspectorCallback)
{
    layoutInspectorCallback_ = layoutInspectorCallback;
}

void FrontendDelegateDeclarativeNG::SetDrawInspectorCallback(const DrawInspectorCallback& drawInspectorCallback)
{
    drawInspectorCallback_ = drawInspectorCallback;
}

void FrontendDelegateDeclarativeNG::SetOnStartContinuationCallBack(
    OnStartContinuationCallBack&& onStartContinuationCallBack)
{
    onStartContinuationCallBack_ = onStartContinuationCallBack;
}

void FrontendDelegateDeclarativeNG::SetOnCompleteContinuationCallBack(
    OnCompleteContinuationCallBack&& onCompleteContinuationCallBack)
{
    onCompleteContinuationCallBack_ = onCompleteContinuationCallBack;
}

void FrontendDelegateDeclarativeNG::SetOnSaveDataCallBack(OnSaveDataCallBack&& onSaveDataCallBack)
{
    onSaveDataCallBack_ = onSaveDataCallBack;
}

void FrontendDelegateDeclarativeNG::SetOnRemoteTerminatedCallBack(
    OnRemoteTerminatedCallBack&& onRemoteTerminatedCallBack)
{
    onRemoteTerminatedCallBack_ = onRemoteTerminatedCallBack;
}

void FrontendDelegateDeclarativeNG::SetOnRestoreDataCallBack(OnRestoreDataCallBack&& onRestoreDataCallBack)
{
    onRestoreDataCallBack_ = onRestoreDataCallBack;
}

void FrontendDelegateDeclarativeNG::SetDestroyApplicationCallback(
    DestroyApplicationCallback&& destroyApplicationCallback)
{
    destroyApplication_ = destroyApplicationCallback;
}

void FrontendDelegateDeclarativeNG::SetUpdateApplicationStateCallback(
    UpdateApplicationStateCallback&& updateApplicationStateCallback)
{
    updateApplicationState_ = updateApplicationStateCallback;
}

void FrontendDelegateDeclarativeNG::SetOnWindowDisplayModeChangedCallback(
    OnWindowDisplayModeChangedCallBack&& onWindowDisplayModeChangedCallBack)
{
    onWindowDisplayModeChanged_ = onWindowDisplayModeChangedCallBack;
}

void FrontendDelegateDeclarativeNG::SetExternalEventCallback(ExternalEventCallback&& externalEventCallback)
{
    externalEvent_ = externalEventCallback;
}

void FrontendDelegateDeclarativeNG::SetTimerCallback(TimerCallback&& timerCallback)
{
    timer_ = timerCallback;
}

void FrontendDelegateDeclarativeNG::AttachPipelineContext(const RefPtr<PipelineBase>& context)
{
    if (!context) {
        return;
    }
    context->SetOnPageShow([weak = AceType::WeakClaim(this)] {
        auto delegate = weak.Upgrade();
        if (delegate) {
            delegate->OnPageShow();
        }
    });

    pipelineContextHolder_.Attach(context);
    jsAccessibilityManager_->SetPipelineContext(context);
    jsAccessibilityManager_->InitializeCallback();
}

void FrontendDelegateDeclarativeNG::AttachSubPipelineContext(const RefPtr<PipelineBase>& context)
{
    if (!context) {
        return;
    }
    jsAccessibilityManager_->AddSubPipelineContext(context);
}

void FrontendDelegateDeclarativeNG::RunPage(
    const std::string& url, const std::string& params, const std::string& profile)
{
    ACE_SCOPED_TRACE("FrontendDelegateDeclarativeNG::RunPage");

    LOGI("FrontendDelegateDeclarativeNG RunPage url=%{public}s", url.c_str());
    std::string jsonContent;
    if (GetAssetContent(MANIFEST_JSON, jsonContent)) {
        manifestParser_->Parse(jsonContent);
        manifestParser_->Printer();
    } else if (!profile.empty() && GetAssetContent(profile, jsonContent)) {
        LOGI("Parse profile %{public}s", profile.c_str());
        manifestParser_->Parse(jsonContent);
    } else if (GetAssetContent(PAGES_JSON, jsonContent)) {
        LOGI("Parse main_pages.json");
        manifestParser_->Parse(jsonContent);
    } else {
        LOGE("RunPage parse manifest.json failed");
    }
    std::string mainPagePath;
    if (!url.empty()) {
        mainPagePath = manifestParser_->GetRouter()->GetPagePath(url);
    } else {
        mainPagePath = manifestParser_->GetRouter()->GetEntry();
    }
    taskExecutor_->PostTask(
        [manifestParser = manifestParser_, delegate = Claim(this),
            weakPtr = WeakPtr<NG::PageRouterManager>(pageRouterManager_), url, params]() {
            auto pageRouterManager = weakPtr.Upgrade();
            CHECK_NULL_VOID(pageRouterManager);
            pageRouterManager->SetManifestParser(manifestParser);
            pageRouterManager->RunPage(url, params);
            auto pipeline = delegate->GetPipelineContext();
            // TODO: get platform version from context, and should stored in AceApplicationInfo.
            if (manifestParser->GetMinPlatformVersion() > 0) {
                pipeline->SetMinPlatformVersion(manifestParser->GetMinPlatformVersion());
            }
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarativeNG::OnConfigurationUpdated(const std::string& data)
{
    // only support mediaQueryUpdate
    OnMediaQueryUpdate();
}

bool FrontendDelegateDeclarativeNG::OnStartContinuation()
{
    bool ret = false;
    taskExecutor_->PostSyncTask(
        [weak = AceType::WeakClaim(this), &ret] {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->onStartContinuationCallBack_) {
                ret = delegate->onStartContinuationCallBack_();
            }
        },
        TaskExecutor::TaskType::JS);
    return ret;
}

void FrontendDelegateDeclarativeNG::OnCompleteContinuation(int32_t code)
{
    taskExecutor_->PostSyncTask(
        [weak = AceType::WeakClaim(this), code] {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->onCompleteContinuationCallBack_) {
                delegate->onCompleteContinuationCallBack_(code);
            }
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarativeNG::OnRemoteTerminated()
{
    taskExecutor_->PostSyncTask(
        [weak = AceType::WeakClaim(this)] {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->onRemoteTerminatedCallBack_) {
                delegate->onRemoteTerminatedCallBack_();
            }
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarativeNG::OnSaveData(std::string& data)
{
    std::string savedData;
    taskExecutor_->PostSyncTask(
        [weak = AceType::WeakClaim(this), &savedData] {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->onSaveDataCallBack_) {
                delegate->onSaveDataCallBack_(savedData);
            }
        },
        TaskExecutor::TaskType::JS);
    std::string pageUri = GetCurrentPageUrl();
    data = std::string("{\"url\":\"").append(pageUri).append("\",\"__remoteData\":").append(savedData).append("}");
}

bool FrontendDelegateDeclarativeNG::OnRestoreData(const std::string& data)
{
    bool ret = false;
    taskExecutor_->PostSyncTask(
        [weak = AceType::WeakClaim(this), &data, &ret] {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->onRestoreDataCallBack_) {
                ret = delegate->onRestoreDataCallBack_(data);
            }
        },
        TaskExecutor::TaskType::JS);
    return ret;
}

void FrontendDelegateDeclarativeNG::OnApplicationDestroy(const std::string& packageName)
{
    taskExecutor_->PostSyncTask(
        [destroyApplication = destroyApplication_, packageName] { destroyApplication(packageName); },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarativeNG::UpdateApplicationState(const std::string& packageName, Frontend::State state)
{
    taskExecutor_->PostTask([updateApplicationState = updateApplicationState_, packageName,
                                state] { updateApplicationState(packageName, state); },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarativeNG::OnWindowDisplayModeChanged(bool isShownInMultiWindow, const std::string& data)
{
    taskExecutor_->PostTask([onWindowDisplayModeChanged = onWindowDisplayModeChanged_, isShownInMultiWindow,
                                data] { onWindowDisplayModeChanged(isShownInMultiWindow, data); },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarativeNG::NotifyAppStorage(
    const WeakPtr<Framework::JsEngine>& jsEngineWeak, const std::string& key, const std::string& value)
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

void FrontendDelegateDeclarativeNG::FireAccessibilityEvent(const AccessibilityEvent& accessibilityEvent)
{
    jsAccessibilityManager_->SendAccessibilityAsyncEvent(accessibilityEvent);
}

void FrontendDelegateDeclarativeNG::InitializeAccessibilityCallback()
{
    jsAccessibilityManager_->InitializeCallback();
}

void FrontendDelegateDeclarativeNG::FireExternalEvent(
    const std::string& /* eventId */, const std::string& componentId, const uint32_t nodeId, const bool isDestroy)
{
    taskExecutor_->PostSyncTask(
        [weak = AceType::WeakClaim(this), componentId, nodeId, isDestroy] {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->externalEvent_(componentId, nodeId, isDestroy);
            }
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarativeNG::WaitTimer(
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

void FrontendDelegateDeclarativeNG::ClearTimer(const std::string& callbackId)
{
    auto timeoutTaskIter = timeoutTaskMap_.find(callbackId);
    if (timeoutTaskIter != timeoutTaskMap_.end()) {
        timeoutTaskIter->second.Cancel();
        timeoutTaskMap_.erase(timeoutTaskIter);
    } else {
        LOGW("ClearTimer callbackId not found");
    }
}

void FrontendDelegateDeclarativeNG::Push(const std::string& uri, const std::string& params)
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->Push(NG::RouterPageInfo({ uri, params }));
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarativeNG::PushWithMode(const std::string& uri, const std::string& params, uint32_t routerMode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->Push(NG::RouterPageInfo({ uri, params, static_cast<NG::RouterMode>(routerMode) }));
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarativeNG::PushWithCallback(const std::string& uri, const std::string& params,
    const std::function<void(const std::string&, int32_t)>& errorCallback, uint32_t routerMode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->Push(
        NG::RouterPageInfo({ uri, params, static_cast<NG::RouterMode>(routerMode), errorCallback }));
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarativeNG::PushNamedRoute(const std::string& uri, const std::string& params,
    const std::function<void(const std::string&, int32_t)>& errorCallback, uint32_t routerMode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->PushNamedRoute(
        NG::RouterPageInfo({ uri, params, static_cast<NG::RouterMode>(routerMode), errorCallback }));
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarativeNG::Replace(const std::string& uri, const std::string& params)
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->Replace(NG::RouterPageInfo({ uri, params }));
}

void FrontendDelegateDeclarativeNG::ReplaceWithMode(
    const std::string& uri, const std::string& params, uint32_t routerMode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->Replace(NG::RouterPageInfo({ uri, params, static_cast<NG::RouterMode>(routerMode) }));
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarativeNG::ReplaceWithCallback(const std::string& uri, const std::string& params,
    const std::function<void(const std::string&, int32_t)>& errorCallback, uint32_t routerMode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->Replace(
        NG::RouterPageInfo({ uri, params, static_cast<NG::RouterMode>(routerMode), errorCallback }));
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarativeNG::ReplaceNamedRoute(const std::string& uri, const std::string& params,
    const std::function<void(const std::string&, int32_t)>& errorCallback, uint32_t routerMode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->ReplaceNamedRoute(
        NG::RouterPageInfo({ uri, params, static_cast<NG::RouterMode>(routerMode), errorCallback }));
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarativeNG::Back(const std::string& uri, const std::string& params)
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->BackWithTarget(NG::RouterPageInfo({ uri, params }));
}

void FrontendDelegateDeclarativeNG::Clear()
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->Clear();
}

int32_t FrontendDelegateDeclarativeNG::GetStackSize() const
{
    CHECK_NULL_RETURN(pageRouterManager_, 0);
    return pageRouterManager_->GetStackSize();
}

void FrontendDelegateDeclarativeNG::GetState(int32_t& index, std::string& name, std::string& path)
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->GetState(index, name, path);
}

std::string FrontendDelegateDeclarativeNG::GetParams()
{
    CHECK_NULL_RETURN(pageRouterManager_, "");
    return pageRouterManager_->GetParams();
}

void FrontendDelegateDeclarativeNG::NavigatePage(uint8_t type, const PageTarget& target, const std::string& params)
{
    switch (static_cast<NavigatorType>(type)) {
        case NavigatorType::PUSH:
            Push(target.url, params);
            break;
        case NavigatorType::REPLACE:
            Replace(target.url, params);
            break;
        case NavigatorType::BACK:
            Back(target.url, params);
            break;
        default:
            LOGE("Navigator type is invalid!");
            Back(target.url, params);
    }
}

void FrontendDelegateDeclarativeNG::PostJsTask(std::function<void()>&& task)
{
    taskExecutor_->PostTask(task, TaskExecutor::TaskType::JS);
}

const std::string& FrontendDelegateDeclarativeNG::GetAppID() const
{
    return manifestParser_->GetAppInfo()->GetAppID();
}

const std::string& FrontendDelegateDeclarativeNG::GetAppName() const
{
    return manifestParser_->GetAppInfo()->GetAppName();
}

const std::string& FrontendDelegateDeclarativeNG::GetVersionName() const
{
    return manifestParser_->GetAppInfo()->GetVersionName();
}

int32_t FrontendDelegateDeclarativeNG::GetVersionCode() const
{
    return manifestParser_->GetAppInfo()->GetVersionCode();
}

void FrontendDelegateDeclarativeNG::PostSyncTaskToPage(std::function<void()>&& task)
{
    pipelineContextHolder_.Get(); // Wait until Pipeline Context is attached.
    taskExecutor_->PostSyncTask(task, TaskExecutor::TaskType::UI);
}

bool FrontendDelegateDeclarativeNG::GetAssetContent(const std::string& url, std::string& content)
{
    return GetAssetContentImpl(assetManager_, url, content);
}

bool FrontendDelegateDeclarativeNG::GetAssetContent(const std::string& url, std::vector<uint8_t>& content)
{
    return GetAssetContentImpl(assetManager_, url, content);
}

std::string FrontendDelegateDeclarativeNG::GetAssetPath(const std::string& url)
{
    return GetAssetPathImpl(assetManager_, url);
}

void FrontendDelegateDeclarativeNG::ChangeLocale(const std::string& language, const std::string& countryOrRegion)
{
    LOGD("JSFrontend ChangeLocale");
    taskExecutor_->PostTask(
        [language, countryOrRegion]() { AceApplicationInfo::GetInstance().ChangeLocale(language, countryOrRegion); },
        TaskExecutor::TaskType::PLATFORM);
}

void FrontendDelegateDeclarativeNG::RegisterFont(const std::string& familyName, const std::string& familySrc)
{
    pipelineContextHolder_.Get()->RegisterFont(familyName, familySrc);
}

void FrontendDelegateDeclarativeNG::GetSystemFontList(std::vector<std::string>& fontList)
{
    pipelineContextHolder_.Get()->GetSystemFontList(fontList);
}

bool FrontendDelegateDeclarativeNG::GetSystemFont(const std::string& fontName, FontInfo& fontInfo)
{
    return pipelineContextHolder_.Get()->GetSystemFont(fontName, fontInfo);
}

double FrontendDelegateDeclarativeNG::MeasureText(const MeasureContext& context)
{
    return MeasureUtil::MeasureText(context);
}

Size FrontendDelegateDeclarativeNG::MeasureTextSize(const MeasureContext& context)
{
    return MeasureUtil::MeasureTextSize(context);
}

SingleTaskExecutor FrontendDelegateDeclarativeNG::GetAnimationJsTask()
{
    return SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::JS);
}

SingleTaskExecutor FrontendDelegateDeclarativeNG::GetUiTask()
{
    return SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::UI);
}

RefPtr<PipelineBase> FrontendDelegateDeclarativeNG::GetPipelineContext()
{
    return pipelineContextHolder_.Get();
}

bool FrontendDelegateDeclarativeNG::OnPageBackPress()
{
    CHECK_NULL_RETURN(pageRouterManager_, false);
    auto pageNode = pageRouterManager_->GetCurrentPageNode();
    CHECK_NULL_RETURN(pageNode, false);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    if (pagePattern->OnBackPressed()) {
        return true;
    }
    return pageRouterManager_->Pop();
}

void FrontendDelegateDeclarativeNG::OnSurfaceChanged()
{
    if (mediaQueryInfo_->GetIsInit()) {
        mediaQueryInfo_->SetIsInit(false);
    }
    mediaQueryInfo_->EnsureListenerIdValid();
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarativeNG::ShowDialog(const std::string& title, const std::string& message,
    const std::vector<ButtonInfo>& buttons, bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
    const std::set<std::string>& callbacks)
{
    DialogProperties dialogProperties = {
        .title = title,
        .content = message,
        .autoCancel = autoCancel,
        .buttons = buttons,
    };
    ShowDialogInner(dialogProperties, std::move(callback), callbacks);
}

void FrontendDelegateDeclarativeNG::ShowDialog(const std::string& title, const std::string& message,
    const std::vector<ButtonInfo>& buttons, bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
    const std::set<std::string>& callbacks, std::function<void(bool)>&& onStatusChanged)
{
    DialogProperties dialogProperties = {
        .title = title,
        .content = message,
        .autoCancel = autoCancel,
        .buttons = buttons,
        .onStatusChanged = std::move(onStatusChanged),
    };
    ShowDialogInner(dialogProperties, std::move(callback), callbacks);
}

void FrontendDelegateDeclarativeNG::ShowActionMenu(
    const std::string& title, const std::vector<ButtonInfo>& button, std::function<void(int32_t, int32_t)>&& callback)
{
    DialogProperties dialogProperties = {
        .title = title,
        .autoCancel = true,
        .isMenu = true,
        .buttons = button,
    };
    ShowActionMenuInner(dialogProperties, button, std::move(callback));
}

void FrontendDelegateDeclarativeNG::ShowActionMenu(const std::string& title, const std::vector<ButtonInfo>& button,
    std::function<void(int32_t, int32_t)>&& callback, std::function<void(bool)>&& onStatusChanged)
{
    DialogProperties dialogProperties = {
        .title = title,
        .autoCancel = true,
        .isMenu = true,
        .buttons = button,
        .onStatusChanged = std::move(onStatusChanged),
    };
    ShowActionMenuInner(dialogProperties, button, std::move(callback));
}

void FrontendDelegateDeclarativeNG::OnMediaQueryUpdate(bool isSynchronous)
{
    auto containerId = Container::CurrentId();
    if (containerId < 0) {
        auto container = Container::GetActive();
        if (container) {
            containerId = container->GetInstanceId();
        }
    }
    bool isInSubwindow = containerId >= 1000000;
    if (isInSubwindow) {
        return;
    }
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

            // request js media query
            const auto& listenerId = delegate->mediaQueryInfo_->GetListenerId();
            delegate->mediaQueryCallback_(listenerId, info);
            delegate->mediaQueryInfo_->ResetListenerId();
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarativeNG::OnLayoutCompleted(const std::string& componentId)
{
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), componentId] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            delegate->layoutInspectorCallback_(componentId);
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarativeNG::OnDrawCompleted(const std::string& componentId)
{
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), componentId] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            delegate->drawInspectorCallback_(componentId);
        },
        TaskExecutor::TaskType::JS);
}

void FrontendDelegateDeclarativeNG::SetColorMode(ColorMode colorMode)
{
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarativeNG::OnForeground()
{
    if (!isFirstNotifyShow_) {
        OnPageShow();
    }
    isFirstNotifyShow_ = false;
}

std::string FrontendDelegateDeclarativeNG::GetCurrentPageUrl()
{
    CHECK_NULL_RETURN(pageRouterManager_, "");
    return pageRouterManager_->GetCurrentPageUrl();
}

// Get the currently running JS page information in NG structure.
RefPtr<RevSourceMap> FrontendDelegateDeclarativeNG::GetCurrentPageSourceMap()
{
    CHECK_NULL_RETURN(pageRouterManager_, nullptr);
    return pageRouterManager_->GetCurrentPageSourceMap(assetManager_);
}

// Get the currently running JS page information in NG structure.
RefPtr<RevSourceMap> FrontendDelegateDeclarativeNG::GetFaAppSourceMap()
{
    if (appSourceMap_) {
        return appSourceMap_;
    }
    std::string appMap;
    if (GetAssetContent("app.js.map", appMap)) {
        appSourceMap_ = AceType::MakeRefPtr<RevSourceMap>();
        appSourceMap_->Init(appMap);
    } else {
        LOGW("app map load failed!");
    }
    return appSourceMap_;
}

void FrontendDelegateDeclarativeNG::GetStageSourceMap(
    std::unordered_map<std::string, RefPtr<Framework::RevSourceMap>>& sourceMaps)
{
    std::string maps;
    if (GetAssetContent(MERGE_SOURCEMAPS_PATH, maps)) {
        auto SourceMap = AceType::MakeRefPtr<RevSourceMap>();
        SourceMap->StageModeSourceMapSplit(maps, sourceMaps);
    } else {
        LOGW("app map load failed!");
    }
}

void FrontendDelegateDeclarativeNG::CallPopPage()
{
    LOGI("CallPopPage begin");
    Back("", "");
}

void FrontendDelegateDeclarativeNG::PostponePageTransition()
{
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this)] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            auto pipelineContext = delegate->pipelineContextHolder_.Get();
            pipelineContext->PostponePageTransition();
        },
        TaskExecutor::TaskType::UI);
}

void FrontendDelegateDeclarativeNG::LaunchPageTransition()
{
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this)] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            auto pipelineContext = delegate->pipelineContextHolder_.Get();
            pipelineContext->LaunchPageTransition();
        },
        TaskExecutor::TaskType::UI);
}

size_t FrontendDelegateDeclarativeNG::GetComponentsCount()
{
    CHECK_NULL_RETURN(pageRouterManager_, 0);
    auto pageNode = pageRouterManager_->GetCurrentPageNode();
    CHECK_NULL_RETURN(pageNode, 0);
    return pageNode->GetAllDepthChildrenCount();
}

void FrontendDelegateDeclarativeNG::ShowToast(const std::string& message, int32_t duration, const std::string& bottom)
{
    LOGD("FrontendDelegateDeclarativeNG ShowToast.");

    int32_t durationTime = std::clamp(duration, TOAST_TIME_DEFAULT, TOAST_TIME_MAX);
    bool isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto task = [durationTime, message, bottom, isRightToLeft, containerId = Container::CurrentId()](
                    const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        ContainerScope scope(containerId);
        LOGI("Begin to show toast message %{public}s, duration is %{public}d", message.c_str(), durationTime);
        overlayManager->ShowToast(message, durationTime, bottom, isRightToLeft);
    };
    MainWindowOverlay(std::move(task));
    return;
}

void FrontendDelegateDeclarativeNG::ShowDialogInner(DialogProperties& dialogProperties,
    std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks)
{
    dialogProperties.onSuccess = std::move(callback);
    dialogProperties.onCancel = [callback, taskExecutor = taskExecutor_] {
        taskExecutor->PostTask(
            [callback]() { callback(CALLBACK_ERRORCODE_CANCEL, CALLBACK_DATACODE_ZERO); }, TaskExecutor::TaskType::JS);
    };
    auto task = [dialogProperties](const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        LOGI("Begin to show dialog ");
        overlayManager->ShowDialog(dialogProperties, nullptr, AceApplicationInfo::GetInstance().IsRightToLeft());
    };
    MainWindowOverlay(std::move(task));
    return;
}

void FrontendDelegateDeclarativeNG::ShowActionMenuInner(DialogProperties& dialogProperties,
    const std::vector<ButtonInfo>& button, std::function<void(int32_t, int32_t)>&& callback)
{
    ButtonInfo buttonInfo = { .text = Localization::GetInstance()->GetEntryLetters("common.cancel"), .textColor = "" };
    dialogProperties.buttons.emplace_back(buttonInfo);
    dialogProperties.onSuccess = std::move(callback);
    dialogProperties.onCancel = [callback, taskExecutor = taskExecutor_] {
        taskExecutor->PostTask(
            [callback]() { callback(CALLBACK_ERRORCODE_CANCEL, CALLBACK_DATACODE_ZERO); }, TaskExecutor::TaskType::JS);
    };
    auto context = DynamicCast<NG::PipelineContext>(pipelineContextHolder_.Get());
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    taskExecutor_->PostTask(
        [dialogProperties, weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowDialog(dialogProperties, nullptr, AceApplicationInfo::GetInstance().IsRightToLeft());
        },
        TaskExecutor::TaskType::UI);
    return;
}

void FrontendDelegateDeclarativeNG::EnableAlertBeforeBackPage(
    const std::string& message, std::function<void(int32_t)>&& callback)
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->EnableAlertBeforeBackPage(message, std::move(callback));
    return;
}

void FrontendDelegateDeclarativeNG::DisableAlertBeforeBackPage()
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->DisableAlertBeforeBackPage();
    return;
}

void FrontendDelegateDeclarativeNG::RebuildAllPages()
{
    CHECK_NULL_VOID(pageRouterManager_);
    auto url = pageRouterManager_->GetCurrentPageUrl();
    pageRouterManager_->Clear();
    pageRouterManager_->RunPage(url, "");
    return;
}

void FrontendDelegateDeclarativeNG::OnPageShow()
{
    CHECK_NULL_VOID(pageRouterManager_);
    auto pageNode = pageRouterManager_->GetCurrentPageNode();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->OnShow();
}

void FrontendDelegateDeclarativeNG::OnPageHide()
{
    CHECK_NULL_VOID(pageRouterManager_);
    auto pageNode = pageRouterManager_->GetCurrentPageNode();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->OnHide();
}

void FrontendDelegateDeclarativeNG::GetSnapshot(
    const std::string& componentId, NG::ComponentSnapshot::JsCallback&& callback)
{
#ifdef ENABLE_ROSEN_BACKEND
    NG::ComponentSnapshot::Get(componentId, std::move(callback));
#endif
}

std::string FrontendDelegateDeclarativeNG::GetContentInfo()
{
    auto jsonContentInfo = JsonUtil::Create(true);
    auto pipelineContext = pipelineContextHolder_.Get();
    CHECK_NULL_RETURN(pipelineContext, jsonContentInfo->ToString());
    jsonContentInfo->Put("nodeInfo", pipelineContext->GetStoredNodeInfo());

    return jsonContentInfo->ToString();
}

void FrontendDelegateDeclarativeNG::CreateSnapshot(
    std::function<void()>&& customBuilder, NG::ComponentSnapshot::JsCallback&& callback)
{
#ifdef ENABLE_ROSEN_BACKEND
    ViewStackModel::GetInstance()->NewScope();
    CHECK_NULL_VOID(customBuilder);
    customBuilder();
    auto customNode = ViewStackModel::GetInstance()->Finish();

    NG::ComponentSnapshot::Create(customNode, std::move(callback));
#endif
}

} // namespace OHOS::Ace::Framework
