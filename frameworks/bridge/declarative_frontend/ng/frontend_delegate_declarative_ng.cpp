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

#include "frameworks/bridge/declarative_frontend/ng/frontend_delegate_declarative_ng.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"
#include "core/components_ng/render/adapter/component_snapshot.h"
#include "frameworks/core/common/ace_engine.h"
#include "base/subwindow/subwindow_manager.h"

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
void MainWindowOverlay(std::function<void(RefPtr<NG::OverlayManager>)>&& task, const std::string& name,
    const RefPtr<NG::OverlayManager>& overlay)
{
    auto currentId = Container::CurrentId();
    ContainerScope scope(currentId);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    if (overlay) {
        overlayManager = overlay;
    }
    context->GetTaskExecutor()->PostTask(
        [task = std::move(task), weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            task(overlayManager);
        },
        TaskExecutor::TaskType::UI, name);
}
} // namespace

FrontendDelegateDeclarativeNG::FrontendDelegateDeclarativeNG(const RefPtr<TaskExecutor>& taskExecutor)
    : taskExecutor_(taskExecutor), manifestParser_(AceType::MakeRefPtr<Framework::ManifestParser>()),
      mediaQueryInfo_(AceType::MakeRefPtr<MediaQueryInfo>()),
      jsAccessibilityManager_(AccessibilityNodeManager::Create())
{}

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

void FrontendDelegateDeclarativeNG::SetDrawChildrenInspectorCallback(
    const DrawChildrenInspectorCallback& drawChildrenInspectorCallback)
{
    drawChildrenInspectorCallback_ = drawChildrenInspectorCallback;
}

void FrontendDelegateDeclarativeNG::SetIsDrawChildrenCallbackFuncExistCallback(
    const IsDrawChildrenCallbackFuncExistCallback& IsDrawChildrenCallbackFuncExistCallback)
{
    isDrawChildrenCallbackFuncExistCallback_ = IsDrawChildrenCallbackFuncExistCallback;
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
    jsAccessibilityManager_->RegisterSubWindowInteractionOperation(context->GetWindowId());
}

void FrontendDelegateDeclarativeNG::RunPage(
    const std::string& url, const std::string& params, const std::string& profile, bool isNamedRouter)
{
    ACE_SCOPED_TRACE("FrontendDelegateDeclarativeNG::RunPage");

    LOGI("Frontend delegate declarative run page, url=%{public}s", url.c_str());
    std::string jsonContent;
    if (GetAssetContent(MANIFEST_JSON, jsonContent)) {
        manifestParser_->Parse(jsonContent);
        manifestParser_->Printer();
    } else if (!profile.empty() && GetAssetContent(profile, jsonContent)) {
        manifestParser_->Parse(jsonContent);
    } else if (GetAssetContent(PAGES_JSON, jsonContent)) {
        manifestParser_->Parse(jsonContent);
    }
    std::string mainPagePath;
    if (!url.empty()) {
        mainPagePath = manifestParser_->GetRouter()->GetPagePath(url);
    } else {
        mainPagePath = manifestParser_->GetRouter()->GetEntry();
    }
    taskExecutor_->PostTask(
        [manifestParser = manifestParser_, delegate = Claim(this),
            weakPtr = WeakPtr<NG::PageRouterManager>(pageRouterManager_), url, params, isNamedRouter]() {
            auto pageRouterManager = weakPtr.Upgrade();
            CHECK_NULL_VOID(pageRouterManager);
            pageRouterManager->SetManifestParser(manifestParser);
            if (isNamedRouter) {
                pageRouterManager->RunPageByNamedRouter(url, params);
            } else {
                pageRouterManager->RunPage(url, params);
            }
            auto pipeline = delegate->GetPipelineContext();
            // TODO: get platform version from context, and should stored in AceApplicationInfo.
            if (manifestParser->GetMinPlatformVersion() > 0) {
                pipeline->SetMinPlatformVersion(manifestParser->GetMinPlatformVersion());
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIRunPageUrl");
}

void FrontendDelegateDeclarativeNG::RunPage(
    const std::shared_ptr<std::vector<uint8_t>>& content, const std::string& params, const std::string& profile)
{
    ACE_SCOPED_TRACE("FrontendDelegateDeclarativeNG::RunPage %zu", content->size());
    taskExecutor_->PostTask(
        [delegate = Claim(this), weakPtr = WeakPtr<NG::PageRouterManager>(pageRouterManager_), content, params]() {
            auto pageRouterManager = weakPtr.Upgrade();
            CHECK_NULL_VOID(pageRouterManager);
            pageRouterManager->RunPage(content, params);
            auto pipeline = delegate->GetPipelineContext();
        },
        TaskExecutor::TaskType::JS, "ArkUIRunPageContent");
}

void FrontendDelegateDeclarativeNG::RunIntentPage()
{
    taskExecutor_->PostTask(
        [delegate = Claim(this), weakPtr = WeakPtr<NG::PageRouterManager>(pageRouterManager_)]() {
            auto pageRouterManager = weakPtr.Upgrade();
            CHECK_NULL_VOID(pageRouterManager);
            pageRouterManager->RunIntentPage();
        },
        TaskExecutor::TaskType::JS, "ArkUIRunIntentPage");
}

void FrontendDelegateDeclarativeNG::SetRouterIntentInfo(const std::string& intentInfoSerialized, bool isColdStart,
    const std::function<void()>&& loadPageCallback)
{
    taskExecutor_->PostTask([weakPtr = WeakPtr<NG::PageRouterManager>(pageRouterManager_),
        intentInfoSerialized, isColdStart, callback = std::move(loadPageCallback)]() {
            auto pageRouterManager = weakPtr.Upgrade();
            CHECK_NULL_VOID(pageRouterManager);
            pageRouterManager->SetRouterIntentInfo(intentInfoSerialized, isColdStart, std::move(callback));
        },
        TaskExecutor::TaskType::JS, "ArkUISetRouterIntentInfo");
}

std::string FrontendDelegateDeclarativeNG::GetTopNavDestinationInfo(bool onlyFullScreen, bool needParam)
{
    if (pageRouterManager_) {
        return pageRouterManager_->GetTopNavDestinationInfo(onlyFullScreen, needParam);
    }
    return "{}";
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
        TaskExecutor::TaskType::JS, "ArkUIStartContinuation");
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
        TaskExecutor::TaskType::JS, "ArkUICompleteContinuation");
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
        TaskExecutor::TaskType::JS, "ArkUIRemoteTerminated");
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
        TaskExecutor::TaskType::JS, "ArkUISaveData");
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
        TaskExecutor::TaskType::JS, "ArkUIRestoreData");
    return ret;
}

void FrontendDelegateDeclarativeNG::OnApplicationDestroy(const std::string& packageName)
{
    taskExecutor_->PostSyncTask(
        [destroyApplication = destroyApplication_, packageName] { destroyApplication(packageName); },
        TaskExecutor::TaskType::JS, "ArkUIApplicationDestroy");
}

void FrontendDelegateDeclarativeNG::UpdateApplicationState(const std::string& packageName, Frontend::State state)
{
    taskExecutor_->PostTask([updateApplicationState = updateApplicationState_, packageName,
                                state] { updateApplicationState(packageName, state); },
        TaskExecutor::TaskType::JS, "ArkUIUpdateApplicationState");
}

void FrontendDelegateDeclarativeNG::OnWindowDisplayModeChanged(bool isShownInMultiWindow, const std::string& data)
{
    taskExecutor_->PostTask([onWindowDisplayModeChanged = onWindowDisplayModeChanged_, isShownInMultiWindow,
                                data] { onWindowDisplayModeChanged(isShownInMultiWindow, data); },
        TaskExecutor::TaskType::JS, "ArkUIWindowDisplayModeChanged");
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
        TaskExecutor::TaskType::JS, "ArkUINotifyAppStorage");
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
        TaskExecutor::TaskType::JS, "ArkUIFireExternalEvent");
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
    taskExecutor_->PostDelayedTask(cancelableTimer, TaskExecutor::TaskType::JS, delayTime, "ArkUIWaitTimer");
}

void FrontendDelegateDeclarativeNG::ClearTimer(const std::string& callbackId)
{
    auto timeoutTaskIter = timeoutTaskMap_.find(callbackId);
    if (timeoutTaskIter != timeoutTaskMap_.end()) {
        timeoutTaskIter->second.Cancel();
        timeoutTaskMap_.erase(timeoutTaskIter);
    }
}

void FrontendDelegateDeclarativeNG::Push(const std::string& uri, const std::string& params)
{
    CHECK_NULL_VOID(pageRouterManager_);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = uri;
    routerPageInfo.params = params;
    routerPageInfo.recoverable = true;
    pageRouterManager_->Push(routerPageInfo);
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarativeNG::PushWithMode(const std::string& uri, const std::string& params, uint32_t routerMode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = uri;
    routerPageInfo.params = params;
    routerPageInfo.recoverable = true;
    routerPageInfo.routerMode = static_cast<NG::RouterMode>(routerMode);
    pageRouterManager_->Push(routerPageInfo);
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarativeNG::PushWithCallback(const std::string& uri, const std::string& params,
    bool recoverable, const std::function<void(const std::string&, int32_t)>& errorCallback, uint32_t routerMode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = uri;
    routerPageInfo.params = params;
    routerPageInfo.recoverable = recoverable;
    routerPageInfo.routerMode = static_cast<NG::RouterMode>(routerMode);
    routerPageInfo.errorCallback = errorCallback;
    pageRouterManager_->Push(routerPageInfo);
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarativeNG::PushNamedRoute(const std::string& uri, const std::string& params,
    bool recoverable, const std::function<void(const std::string&, int32_t)>& errorCallback, uint32_t routerMode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = uri;
    routerPageInfo.params = params;
    routerPageInfo.recoverable = recoverable;
    routerPageInfo.routerMode = static_cast<NG::RouterMode>(routerMode);
    routerPageInfo.errorCallback = errorCallback;
    pageRouterManager_->PushNamedRoute(routerPageInfo);
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarativeNG::Replace(const std::string& uri, const std::string& params)
{
    CHECK_NULL_VOID(pageRouterManager_);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = uri;
    routerPageInfo.params = params;
    routerPageInfo.recoverable = true;
    pageRouterManager_->Replace(routerPageInfo);
}

void FrontendDelegateDeclarativeNG::ReplaceWithMode(
    const std::string& uri, const std::string& params, uint32_t routerMode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = uri;
    routerPageInfo.params = params;
    routerPageInfo.recoverable = true;
    routerPageInfo.routerMode = static_cast<NG::RouterMode>(routerMode);
    pageRouterManager_->Replace(routerPageInfo);
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarativeNG::ReplaceWithCallback(const std::string& uri, const std::string& params,
    bool recoverable, const std::function<void(const std::string&, int32_t)>& errorCallback, uint32_t routerMode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = uri;
    routerPageInfo.params = params;
    routerPageInfo.recoverable = recoverable;
    routerPageInfo.routerMode = static_cast<NG::RouterMode>(routerMode);
    routerPageInfo.errorCallback = errorCallback;
    pageRouterManager_->Replace(routerPageInfo);
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarativeNG::ReplaceNamedRoute(const std::string& uri, const std::string& params,
    bool recoverable, const std::function<void(const std::string&, int32_t)>& errorCallback, uint32_t routerMode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = uri;
    routerPageInfo.params = params;
    routerPageInfo.recoverable = recoverable;
    routerPageInfo.routerMode = static_cast<NG::RouterMode>(routerMode);
    routerPageInfo.errorCallback = errorCallback;
    pageRouterManager_->ReplaceNamedRoute(routerPageInfo);
    OnMediaQueryUpdate();
}

void FrontendDelegateDeclarativeNG::Back(const std::string& uri, const std::string& params)
{
    CHECK_NULL_VOID(pageRouterManager_);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = uri;
    routerPageInfo.params = params;
    pageRouterManager_->BackWithTarget(routerPageInfo);
}

void FrontendDelegateDeclarativeNG::BackToIndex(int32_t index, const std::string& params)
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->BackToIndexWithTarget(index, params);
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

void FrontendDelegateDeclarativeNG::GetRouterStateByIndex(int32_t& index, std::string& name,
    std::string& path, std::string& params)
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->GetStateByIndex(index, name, path, params);
}

void FrontendDelegateDeclarativeNG::GetRouterStateByUrl(std::string& url, std::vector<StateInfo>& stateArray)
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->GetStateByUrl(url, stateArray);
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
            Back(target.url, params);
    }
}

void FrontendDelegateDeclarativeNG::PostJsTask(std::function<void()>&& task, const std::string& name)
{
    taskExecutor_->PostTask(task, TaskExecutor::TaskType::JS, name);
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

void FrontendDelegateDeclarativeNG::PostSyncTaskToPage(std::function<void()>&& task, const std::string& name)
{
    pipelineContextHolder_.Get(); // Wait until Pipeline Context is attached.
    taskExecutor_->PostSyncTask(task, TaskExecutor::TaskType::UI, name);
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
    taskExecutor_->PostTask(
        [language, countryOrRegion]() { AceApplicationInfo::GetInstance().ChangeLocale(language, countryOrRegion); },
        TaskExecutor::TaskType::PLATFORM, "ArkUIChangeLocale");
}

void FrontendDelegateDeclarativeNG::RegisterFont(const std::string& familyName, const std::string& familySrc,
    const std::string& bundleName, const std::string& moduleName)
{
    pipelineContextHolder_.Get()->RegisterFont(familyName, familySrc, bundleName, moduleName);
}

void FrontendDelegateDeclarativeNG::GetSystemFontList(std::vector<std::string>& fontList)
{
    pipelineContextHolder_.Get()->GetSystemFontList(fontList);
}

bool FrontendDelegateDeclarativeNG::GetSystemFont(const std::string& fontName, FontInfo& fontInfo)
{
    return pipelineContextHolder_.Get()->GetSystemFont(fontName, fontInfo);
}

void FrontendDelegateDeclarativeNG::GetUIFontConfig(FontConfigJsonInfo& fontConfigJsonInfo)
{
    pipelineContextHolder_.Get()->GetUIFontConfig(fontConfigJsonInfo);
}

double FrontendDelegateDeclarativeNG::MeasureText(MeasureContext context)
{
    if (context.isFontSizeUseDefaultUnit && context.fontSize.has_value() &&
        !AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        context.fontSize = Dimension(context.fontSize->Value(), DimensionUnit::VP);
    }
    return MeasureUtil::MeasureText(context);
}

Size FrontendDelegateDeclarativeNG::MeasureTextSize(MeasureContext context)
{
    if (context.isFontSizeUseDefaultUnit && context.fontSize.has_value() &&
        !AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        context.fontSize = Dimension(context.fontSize->Value(), DimensionUnit::VP);
    }
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
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show dialog enter");
    DialogProperties dialogProperties = {
        .type = DialogType::ALERT_DIALOG,
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
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show dialog enter");
    DialogProperties dialogProperties = {
        .type = DialogType::ALERT_DIALOG,
        .title = title,
        .content = message,
        .autoCancel = autoCancel,
        .buttons = buttons,
        .onStatusChanged = std::move(onStatusChanged),
    };
    ShowDialogInner(dialogProperties, std::move(callback), callbacks);
}

void FrontendDelegateDeclarativeNG::ShowDialog(const PromptDialogAttr& dialogAttr,
    const std::vector<ButtonInfo>& buttons, std::function<void(int32_t, int32_t)>&& callback,
    const std::set<std::string>& callbacks)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show dialog enter");
    DialogProperties dialogProperties = {
        .type = DialogType::ALERT_DIALOG,
        .title = dialogAttr.title,
        .content = dialogAttr.message,
        .autoCancel = dialogAttr.autoCancel,
        .buttons = buttons,
        .isShowInSubWindow = dialogAttr.showInSubWindow,
        .isModal = dialogAttr.isModal,
        .enableHoverMode = dialogAttr.enableHoverMode,
        .maskRect = dialogAttr.maskRect,
        .levelOrder = dialogAttr.levelOrder,
        .dialogLevelMode = dialogAttr.dialogLevelMode,
        .dialogLevelUniqueId = dialogAttr.dialogLevelUniqueId,
        .dialogImmersiveMode = dialogAttr.dialogImmersiveMode,
        .onDidAppear = dialogAttr.onDidAppear,
        .onDidDisappear = dialogAttr.onDidDisappear,
        .onWillAppear = dialogAttr.onWillAppear,
        .onWillDisappear = dialogAttr.onWillDisappear,
    };
    if (dialogAttr.alignment.has_value()) {
        dialogProperties.alignment = dialogAttr.alignment.value();
    }
    if (dialogAttr.offset.has_value()) {
        dialogProperties.offset = dialogAttr.offset.value();
    }
    if (dialogAttr.shadow.has_value()) {
        dialogProperties.shadow = dialogAttr.shadow.value();
    }
    if (dialogAttr.backgroundColor.has_value()) {
        dialogProperties.backgroundColor = dialogAttr.backgroundColor.value();
    }
    if (dialogAttr.backgroundBlurStyle.has_value()) {
        dialogProperties.backgroundBlurStyle = dialogAttr.backgroundBlurStyle.value();
    }
    if (dialogAttr.blurStyleOption.has_value()) {
        dialogProperties.blurStyleOption = dialogAttr.blurStyleOption.value();
    }
    if (dialogAttr.effectOption.has_value()) {
        dialogProperties.effectOption = dialogAttr.effectOption.value();
    }
    if (dialogAttr.hoverModeArea.has_value()) {
        dialogProperties.hoverModeArea = dialogAttr.hoverModeArea.value();
    }
    ShowDialogInner(dialogProperties, std::move(callback), callbacks);
}

void FrontendDelegateDeclarativeNG::ShowDialog(const PromptDialogAttr& dialogAttr,
    const std::vector<ButtonInfo>& buttons, std::function<void(int32_t, int32_t)>&& callback,
    const std::set<std::string>& callbacks, std::function<void(bool)>&& onStatusChanged)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show dialog enter");
    DialogProperties dialogProperties = {
        .type = DialogType::ALERT_DIALOG,
        .title = dialogAttr.title,
        .content = dialogAttr.message,
        .autoCancel = dialogAttr.autoCancel,
        .buttons = buttons,
        .isShowInSubWindow = dialogAttr.showInSubWindow,
        .isModal = dialogAttr.isModal,
        .onStatusChanged = std::move(onStatusChanged),
        .maskRect = dialogAttr.maskRect,
        .levelOrder = dialogAttr.levelOrder,
    };
    if (dialogAttr.alignment.has_value()) {
        dialogProperties.alignment = dialogAttr.alignment.value();
    }
    if (dialogAttr.offset.has_value()) {
        dialogProperties.offset = dialogAttr.offset.value();
    }
    ShowDialogInner(dialogProperties, std::move(callback), callbacks);
}

void FrontendDelegateDeclarativeNG::RemoveCustomDialog(int32_t instanceId)
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "Dismiss custom dialog, instanceId: %{public}d", instanceId);
    ContainerScope scope(instanceId);
    NG::ViewAbstract::DismissDialog();
}

void FrontendDelegateDeclarativeNG::ParsePartialPropertiesFromAttr(
    DialogProperties& dialogProperties, const PromptDialogAttr& dialogAttr)
{
#if defined(PREVIEW)
    if (dialogProperties.isShowInSubWindow) {
        LOGW("[Engine Log] Unable to use the SubWindow in the Previewer. Perform this operation on the "
             "emulator or a real device instead.");
        dialogProperties.isShowInSubWindow = false;
    }
#endif
    if (dialogAttr.alignment.has_value()) {
        dialogProperties.alignment = dialogAttr.alignment.value();
    }
    if (dialogAttr.offset.has_value()) {
        dialogProperties.offset = dialogAttr.offset.value();
    }
    if (dialogAttr.hoverModeArea.has_value()) {
        dialogProperties.hoverModeArea = dialogAttr.hoverModeArea.value();
    }
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        dialogProperties.isSysBlurStyle = false;
    } else {
        if (dialogAttr.backgroundBlurStyle.has_value()) {
            dialogProperties.backgroundBlurStyle = dialogAttr.backgroundBlurStyle.value();
        }
    }
}

DialogProperties FrontendDelegateDeclarativeNG::ParsePropertiesFromAttr(const PromptDialogAttr &dialogAttr)
{
    DialogProperties dialogProperties = {
        .autoCancel = dialogAttr.autoCancel, .customStyle = dialogAttr.customStyle,
        .onWillDismiss = dialogAttr.customOnWillDismiss, .maskColor = dialogAttr.maskColor,
        .backgroundColor = dialogAttr.backgroundColor, .borderRadius = dialogAttr.borderRadius,
        .isShowInSubWindow = dialogAttr.showInSubWindow, .isModal = dialogAttr.isModal,
        .enableHoverMode = dialogAttr.enableHoverMode, .customBuilder = dialogAttr.customBuilder,
        .customBuilderWithId = dialogAttr.customBuilderWithId,
        .blurStyleOption = dialogAttr.blurStyleOption,
        .effectOption = dialogAttr.effectOption,
        .borderWidth = dialogAttr.borderWidth,
        .borderColor = dialogAttr.borderColor, .borderStyle = dialogAttr.borderStyle, .shadow = dialogAttr.shadow,
        .width = dialogAttr.width, .height = dialogAttr.height,
        .isUserCreatedDialog = dialogAttr.isUserCreatedDialog,
        .maskRect = dialogAttr.maskRect,
        .transitionEffect = dialogAttr.transitionEffect, .contentNode = dialogAttr.contentNode,
        .onDidAppear = dialogAttr.onDidAppear, .onDidDisappear = dialogAttr.onDidDisappear,
        .onWillAppear = dialogAttr.onWillAppear, .onWillDisappear = dialogAttr.onWillDisappear,
        .keyboardAvoidMode = dialogAttr.keyboardAvoidMode, .dialogCallback = dialogAttr.dialogCallback,
        .keyboardAvoidDistance = dialogAttr.keyboardAvoidDistance,
        .levelOrder = dialogAttr.levelOrder,
        .focusable = dialogAttr.focusable,
        .dialogLevelMode = dialogAttr.dialogLevelMode,
        .dialogLevelUniqueId = dialogAttr.dialogLevelUniqueId,
        .dialogImmersiveMode = dialogAttr.dialogImmersiveMode
    };
    ParsePartialPropertiesFromAttr(dialogProperties, dialogAttr);
    return dialogProperties;
}

void FrontendDelegateDeclarativeNG::OpenCustomDialog(const PromptDialogAttr &dialogAttr,
    std::function<void(int32_t)> &&callback)
{
    DialogProperties dialogProperties = ParsePropertiesFromAttr(dialogAttr);
    if (Container::IsCurrentUseNewPipeline()) {
        auto task = [dialogAttr, dialogProperties, callback](const RefPtr<NG::OverlayManager>& overlayManager) mutable {
            CHECK_NULL_VOID(overlayManager);
            TAG_LOGD(AceLogTag::ACE_OVERLAY, "Begin to open custom dialog ");
            if (dialogProperties.isShowInSubWindow) {
                SubwindowManager::GetInstance()->OpenCustomDialogNG(dialogProperties, std::move(callback));
                if (dialogProperties.isModal) {
                    TAG_LOGW(AceLogTag::ACE_OVERLAY, "temporary not support isShowInSubWindow and isModal");
                }
            } else {
                overlayManager->OpenCustomDialog(dialogProperties, std::move(callback));
            }
        };
        if (dialogProperties.dialogLevelMode == LevelMode::EMBEDDED) {
            NG::DialogManager::ShowInEmbeddedOverlay(
                std::move(task), "ArkUIOverlayShowDialog", dialogProperties.dialogLevelUniqueId);
        } else {
            MainWindowOverlay(std::move(task), "ArkUIOverlayOpenCustomDialog", nullptr);
        }
        return;
    } else {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "not support old pipeline");
    }
}

void FrontendDelegateDeclarativeNG::CloseCustomDialog(const int32_t dialogId)
{
    auto task = [dialogId](const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "begin to close custom dialog.");
        overlayManager->CloseCustomDialog(dialogId);
        SubwindowManager::GetInstance()->CloseCustomDialogNG(dialogId);
    };
    auto dialogNode = NG::FrameNode::GetFrameNodeOnly(V2::DIALOG_ETS_TAG, dialogId);
    auto currentOverlay = NG::DialogManager::GetInstance().GetEmbeddedOverlayWithNode(dialogNode);
    MainWindowOverlay(std::move(task), "ArkUIOverlayCloseCustomDialog", currentOverlay);
    return;
}

void FrontendDelegateDeclarativeNG::CloseCustomDialog(const WeakPtr<NG::UINode>& node,
    std::function<void(int32_t)> &&callback)
{
    auto nodePtr = node.Upgrade();
    CHECK_NULL_VOID(nodePtr);
    auto context = nodePtr->GetContextWithCheck();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    auto parent = NG::DialogManager::GetInstance().GetDialogNodeByContentNode(nodePtr);
    if (parent) {
        auto currentOverlay = NG::DialogManager::GetInstance().GetEmbeddedOverlayWithNode(parent);
        if (currentOverlay) {
            overlayManager = currentOverlay;
        }
    }
    context->GetTaskExecutor()->PostTask(
        [node, callback, weak = WeakPtr<NG::OverlayManager>(overlayManager)]() mutable {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            TAG_LOGI(AceLogTag::ACE_OVERLAY, "begin to close custom dialog.");
            overlayManager->CloseCustomDialog(node, std::move(callback));
        },
        TaskExecutor::TaskType::UI, "ArkUIOverlayCloseCustomDialog");
}

void FrontendDelegateDeclarativeNG::UpdateCustomDialog(
    const WeakPtr<NG::UINode>& node, const PromptDialogAttr &dialogAttr, std::function<void(int32_t)> &&callback)
{
    DialogProperties dialogProperties = {
        .autoCancel = dialogAttr.autoCancel,
        .maskColor = dialogAttr.maskColor,
        .isSysBlurStyle = false
    };
    if (dialogAttr.alignment.has_value()) {
        dialogProperties.alignment = dialogAttr.alignment.value();
    }
    if (dialogAttr.offset.has_value()) {
        dialogProperties.offset = dialogAttr.offset.value();
    }

    auto nodePtr = node.Upgrade();
    CHECK_NULL_VOID(nodePtr);
    auto context = nodePtr->GetContextWithCheck();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    context->GetTaskExecutor()->PostTask(
        [dialogProperties, node, callback, weak = WeakPtr<NG::OverlayManager>(overlayManager)]() mutable {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            TAG_LOGI(AceLogTag::ACE_OVERLAY, "begin to update custom dialog.");
            overlayManager->UpdateCustomDialog(node, dialogProperties, std::move(callback));
        },
        TaskExecutor::TaskType::UI, "ArkUIOverlayUpdateCustomDialog");
}

std::optional<double> FrontendDelegateDeclarativeNG::GetTopOrder()
{
    auto currentId = Container::CurrentId();
    ContainerScope scope(currentId);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, std::nullopt);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, std::nullopt);
    return overlayManager->GetTopOrder();
}

std::optional<double> FrontendDelegateDeclarativeNG::GetBottomOrder()
{
    auto currentId = Container::CurrentId();
    ContainerScope scope(currentId);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, std::nullopt);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, std::nullopt);
    return overlayManager->GetBottomOrder();
}

void FrontendDelegateDeclarativeNG::ShowActionMenu(
    const std::string& title, const std::vector<ButtonInfo>& button, std::function<void(int32_t, int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show action menu enter");
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
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show action menu enter");
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
        TaskExecutor::TaskType::JS, "ArkUIMediaQueryUpdate");
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
        TaskExecutor::TaskType::JS, "ArkUILayoutCompleted");
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
        TaskExecutor::TaskType::JS, "ArkUIDrawCompleted");
}

void FrontendDelegateDeclarativeNG::OnDrawChildrenCompleted(const std::string& componentId)
{
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), componentId] {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->drawChildrenInspectorCallback_) {
                delegate->drawChildrenInspectorCallback_(componentId);
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIDrawChildrenCompleted");
}

bool FrontendDelegateDeclarativeNG::IsDrawChildrenCallbackFuncExist(const std::string& componentId)
{
    if (isDrawChildrenCallbackFuncExistCallback_) {
        return isDrawChildrenCallbackFuncExistCallback_(componentId);
    }
    return false;
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
    }
}

void FrontendDelegateDeclarativeNG::CallPopPage()
{
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
        TaskExecutor::TaskType::UI, "ArkUIPostponePageTransition");
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
        TaskExecutor::TaskType::UI, "ArkUILaunchPageTransition");
}

size_t FrontendDelegateDeclarativeNG::GetComponentsCount()
{
    CHECK_NULL_RETURN(pageRouterManager_, 0);
    auto pageNode = pageRouterManager_->GetCurrentPageNode();
    CHECK_NULL_RETURN(pageNode, 0);
    return pageNode->GetAllDepthChildrenCount();
}

void FrontendDelegateDeclarativeNG::ShowToast(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show toast enter");
    NG::ToastInfo updatedToastInfo = toastInfo;
    updatedToastInfo.duration = std::clamp(toastInfo.duration, TOAST_TIME_DEFAULT, TOAST_TIME_MAX);
    updatedToastInfo.isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto task = [updatedToastInfo, callbackParam = std::move(callback), containerId = Container::CurrentId()](
                    const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        ContainerScope scope(containerId);
        overlayManager->ShowToast(
            updatedToastInfo, std::move(const_cast<std::function<void(int32_t)>&&>(callbackParam)));
    };
    MainWindowOverlay(std::move(task), "ArkUIOverlayShowToast", nullptr);
}

void FrontendDelegateDeclarativeNG::CloseToast(const int32_t toastId, std::function<void(int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "close toast enter");
    auto currentId = Container::CurrentId();
    ContainerScope scope(currentId);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->CloseToast(toastId, std::move(callback));
}

void FrontendDelegateDeclarativeNG::ShowDialogInner(DialogProperties& dialogProperties,
    std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show dialog inner enter");
    dialogProperties.onSuccess = std::move(callback);
    dialogProperties.onCancel = [callback, taskExecutor = taskExecutor_] {
        taskExecutor->PostTask(
            [callback]() { callback(CALLBACK_ERRORCODE_CANCEL, CALLBACK_DATACODE_ZERO); },
            TaskExecutor::TaskType::JS, "ArkUIOverlayShowDialogCancel");
    };
    auto task = [dialogProperties](const RefPtr<NG::OverlayManager>& overlayManager) {
        LOGI("Begin to show dialog ");
        CHECK_NULL_VOID(overlayManager);
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        if (container->IsSubContainer()) {
            auto currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
            container = AceEngine::Get().GetContainer(currentId);
            CHECK_NULL_VOID(container);
        }
        RefPtr<NG::FrameNode> dialog;
        if (dialogProperties.isShowInSubWindow) {
            dialog = SubwindowManager::GetInstance()->ShowDialogNG(dialogProperties, nullptr);
            CHECK_NULL_VOID(dialog);
            if (dialogProperties.isModal && !container->IsUIExtensionWindow()) {
                DialogProperties Maskarg;
                Maskarg.isMask = true;
                Maskarg.autoCancel = dialogProperties.autoCancel;
                auto mask = overlayManager->ShowDialog(Maskarg, nullptr, false);
                CHECK_NULL_VOID(mask);
                overlayManager->SetMaskNodeId(dialog->GetId(), mask->GetId());
            }
        } else {
            dialog = overlayManager->ShowDialog(
                dialogProperties, nullptr, AceApplicationInfo::GetInstance().IsRightToLeft());
            CHECK_NULL_VOID(dialog);
        }
    };
    if (dialogProperties.dialogLevelMode == LevelMode::EMBEDDED) {
        NG::DialogManager::ShowInEmbeddedOverlay(
            std::move(task), "ArkUIOverlayShowDialog", dialogProperties.dialogLevelUniqueId);
    } else {
        MainWindowOverlay(std::move(task), "ArkUIOverlayShowDialog", nullptr);
    }
    return;
}

void FrontendDelegateDeclarativeNG::ShowActionMenuInner(DialogProperties& dialogProperties,
    const std::vector<ButtonInfo>& button, std::function<void(int32_t, int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show action menu inner enter");
    dialogProperties.onSuccess = std::move(callback);
    dialogProperties.onCancel = [callback, taskExecutor = taskExecutor_] {
        taskExecutor->PostTask(
            [callback]() { callback(CALLBACK_ERRORCODE_CANCEL, CALLBACK_DATACODE_ZERO); },
            TaskExecutor::TaskType::JS, "ArkUIOverlayShowActionMenuCancel");
    };
    auto context = DynamicCast<NG::PipelineContext>(pipelineContextHolder_.Get());
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    taskExecutor_->PostTask(
        [dialogProperties, weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowDialog(dialogProperties, nullptr, AceApplicationInfo::GetInstance().IsRightToLeft());
        },
        TaskExecutor::TaskType::UI, "ArkUIOverlayShowActionMenu");
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
    const std::string& componentId, NG::ComponentSnapshot::JsCallback&& callback, const NG::SnapshotOptions& options)
{
#ifdef ENABLE_ROSEN_BACKEND
    NG::ComponentSnapshot::Get(componentId, std::move(callback), options);
#endif
}

std::pair<int32_t, std::shared_ptr<Media::PixelMap>> FrontendDelegateDeclarativeNG::GetSyncSnapshot(
    RefPtr<NG::FrameNode>& node, const NG::SnapshotOptions& options)
{
#ifdef ENABLE_ROSEN_BACKEND
    return NG::ComponentSnapshot::GetSync(node, options);
#endif
    return { ERROR_CODE_INTERNAL_ERROR, nullptr };
}

std::pair<int32_t, std::shared_ptr<Media::PixelMap>> FrontendDelegateDeclarativeNG::GetSyncSnapshot(
    const std::string& componentId, const NG::SnapshotOptions& options)
{
#ifdef ENABLE_ROSEN_BACKEND
    return NG::ComponentSnapshot::GetSync(componentId, options);
#endif
    return {ERROR_CODE_INTERNAL_ERROR, nullptr};
}

void FrontendDelegateDeclarativeNG::GetSnapshotByUniqueId(int32_t uniqueId,
    std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
    const NG::SnapshotOptions& options)
{
#ifdef ENABLE_ROSEN_BACKEND
    NG::ComponentSnapshot::GetByUniqueId(uniqueId, std::move(callback), options);
#endif
}

std::pair<int32_t, std::shared_ptr<Media::PixelMap>> FrontendDelegateDeclarativeNG::GetSyncSnapshotByUniqueId(
    int32_t uniqueId, const NG::SnapshotOptions& options)
{
#ifdef ENABLE_ROSEN_BACKEND
    return NG::ComponentSnapshot::GetSyncByUniqueId(uniqueId, options);
#endif
    return {ERROR_CODE_INTERNAL_ERROR, nullptr};
}

void FrontendDelegateDeclarativeNG::GetSnapshotWithRange(const NG::NodeIdentity& startID, const NG::NodeIdentity& endID,
    const bool isStartRect,
    std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
    const NG::SnapshotOptions& options)
{
#ifdef ENABLE_ROSEN_BACKEND
    NG::ComponentSnapshot::GetWithRange(startID, endID, isStartRect, std::move(callback), options);
#endif
}

void FrontendDelegateDeclarativeNG::CreateSnapshotFromComponent(const RefPtr<NG::UINode>& nodeWk,
    NG::ComponentSnapshot::JsCallback&& callback, bool enableInspector, const NG::SnapshotParam& param)
{
#ifdef ENABLE_ROSEN_BACKEND
    ViewStackModel::GetInstance()->NewScope();
    NG::ComponentSnapshot::Create(nodeWk, std::move(callback), enableInspector, param);
#endif
}

std::string FrontendDelegateDeclarativeNG::GetContentInfo(ContentInfoType type)
{
    auto jsonContentInfo = JsonUtil::Create(true);

    CHECK_NULL_RETURN(pageRouterManager_, "");
    jsonContentInfo->Put("stackInfo", pageRouterManager_->GetStackInfo(type));
    if (type == ContentInfoType::RESOURCESCHEDULE_RECOVERY) {
        auto namedRouterInfo = pageRouterManager_->GetNamedRouterInfo();
        if (namedRouterInfo) {
            jsonContentInfo->Put("namedRouterInfo", std::move(namedRouterInfo));
        }
    }

    if (type == ContentInfoType::CONTINUATION || type == ContentInfoType::APP_RECOVERY) {
        auto pipelineContext = pipelineContextHolder_.Get();
        CHECK_NULL_RETURN(pipelineContext, jsonContentInfo->ToString());
        jsonContentInfo->Put("nodeInfo", pipelineContext->GetStoredNodeInfo());
    }

    return jsonContentInfo->ToString();
}

void FrontendDelegateDeclarativeNG::CreateSnapshot(
    std::function<void()>&& customBuilder, NG::ComponentSnapshot::JsCallback&& callback, bool enableInspector,
    const NG::SnapshotParam& param)
{
#ifdef ENABLE_ROSEN_BACKEND
    ViewStackModel::GetInstance()->NewScope();
    CHECK_NULL_VOID(customBuilder);
    customBuilder();
    auto customNode = ViewStackModel::GetInstance()->Finish();

    NG::ComponentSnapshot::Create(customNode, std::move(callback), enableInspector, param);
#endif
}

void FrontendDelegateDeclarativeNG::AddFrameNodeToOverlay(
    const RefPtr<NG::FrameNode>& node, std::optional<int32_t> index)
{
    auto task = [node, index, containerId = Container::CurrentId()](const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        ContainerScope scope(containerId);
        overlayManager->AddFrameNodeToOverlay(node, index);
    };
    MainWindowOverlay(std::move(task), "ArkUIOverlayAddFrameNode", nullptr);
}

void FrontendDelegateDeclarativeNG::AddFrameNodeWithOrder(
    const RefPtr<NG::FrameNode>& node, std::optional<double> levelOrder)
{
    CHECK_NULL_VOID(node);
    auto pipelineContext = node->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto overlayManager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->AddFrameNodeWithOrder(node, levelOrder);
}

void FrontendDelegateDeclarativeNG::RemoveFrameNodeOnOverlay(const RefPtr<NG::FrameNode>& node)
{
    auto task = [node, containerId = Container::CurrentId()](const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        ContainerScope scope(containerId);
        overlayManager->RemoveFrameNodeOnOverlay(node);
    };
    MainWindowOverlay(std::move(task), "ArkUIOverlayRemoveFrameNode", nullptr);
}

void FrontendDelegateDeclarativeNG::ShowNodeOnOverlay(const RefPtr<NG::FrameNode>& node)
{
    auto task = [node, containerId = Container::CurrentId()](const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        ContainerScope scope(containerId);
        overlayManager->ShowNodeOnOverlay(node);
    };
    MainWindowOverlay(std::move(task), "ArkUIOverlayShowNode", nullptr);
}

void FrontendDelegateDeclarativeNG::HideNodeOnOverlay(const RefPtr<NG::FrameNode>& node)
{
    auto task = [node, containerId = Container::CurrentId()](const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        ContainerScope scope(containerId);
        overlayManager->HideNodeOnOverlay(node);
    };
    MainWindowOverlay(std::move(task), "ArkUIOverlayHideNode", nullptr);
}

void FrontendDelegateDeclarativeNG::ShowAllNodesOnOverlay()
{
    auto task = [containerId = Container::CurrentId()](const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        ContainerScope scope(containerId);
        overlayManager->ShowAllNodesOnOverlay();
    };
    MainWindowOverlay(std::move(task), "ArkUIOverlayShowAllNodes", nullptr);
}

void FrontendDelegateDeclarativeNG::HideAllNodesOnOverlay()
{
    auto task = [containerId = Container::CurrentId()](const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        ContainerScope scope(containerId);
        overlayManager->HideAllNodesOnOverlay();
    };
    MainWindowOverlay(std::move(task), "ArkUIOverlayHideAllNodes", nullptr);
}

bool FrontendDelegateDeclarativeNG::SetOverlayManagerOptions(const NG::OverlayManagerInfo& overlayInfo)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, false);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    return overlayManager->SetOverlayManagerOptions(overlayInfo);
};
std::optional<NG::OverlayManagerInfo> FrontendDelegateDeclarativeNG::GetOverlayManagerOptions()
{
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, std::nullopt);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_RETURN(context, std::nullopt);
    return overlayManager->GetOverlayManagerOptions();
};
} // namespace OHOS::Ace::Framework
