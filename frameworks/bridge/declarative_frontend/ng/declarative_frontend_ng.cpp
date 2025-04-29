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

#include "frameworks/bridge/declarative_frontend/ng/declarative_frontend_ng.h"

#include "base/log/dump_log.h"
#include "core/common/recorder/node_data_cache.h"
#include "frameworks/bridge/declarative_frontend/ng/page_router_manager_factory.h"

namespace OHOS::Ace {

DeclarativeFrontendNG::~DeclarativeFrontendNG() noexcept
{
    LOGI("DeclarativeFrontend destroyed");
}

void DeclarativeFrontendNG::Destroy()
{
    // The call doesn't change the page pop status
    Recorder::NodeDataCache::Get().OnBeforePagePop(true);
    CHECK_RUN_ON(JS);
    // To guarantee the jsEngine_ and delegate_ released in js thread
    delegate_.Reset();
    jsEngine_->Destroy();
    jsEngine_.Reset();
}

bool DeclarativeFrontendNG::Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor)
{
    type_ = type;
    taskExecutor_ = taskExecutor;
    ACE_DCHECK(type_ == FrontendType::DECLARATIVE_JS);
    InitializeDelegate(taskExecutor);
    bool needPostJsTask = true;
    auto container = Container::Current();
    if (container) {
        const auto& setting = container->GetSettings();
        needPostJsTask = !(setting.usePlatformAsUIThread && setting.useUIAsJSThread);
    }
    auto initJSEngineTask = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_), delegate = delegate_] {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->Initialize(delegate);
    };
    if (needPostJsTask) {
        taskExecutor->PostTask(initJSEngineTask, TaskExecutor::TaskType::JS, "ArkUIInitJsEngine");
    } else {
        initJSEngineTask();
    }
    return true;
}

void DeclarativeFrontendNG::AttachPipelineContext(const RefPtr<PipelineBase>& context)
{
    if (delegate_) {
        delegate_->AttachPipelineContext(context);
    }
}

void DeclarativeFrontendNG::AttachSubPipelineContext(const RefPtr<PipelineBase>& context)
{
    if (!delegate_) {
        return;
    }
    delegate_->AttachSubPipelineContext(context);
}

void DeclarativeFrontendNG::SetAssetManager(const RefPtr<AssetManager>& assetManager)
{
    if (delegate_) {
        delegate_->SetAssetManager(assetManager);
    }
}

void DeclarativeFrontendNG::InitializeDelegate(const RefPtr<TaskExecutor>& taskExecutor)
{
    auto pageRouterManager = NG::PageRouterManagerFactory::CreateManager();
    auto loadPageCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](const std::string& url,
                                const std::function<void(const std::string&, int32_t)>& errorCallback) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return false;
        }
        return jsEngine->LoadPageSource(url, errorCallback);
    };

    auto loadPageByBufferCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                        const std::shared_ptr<std::vector<uint8_t>>& content,
                                        const std::function<void(const std::string&, int32_t)>& errorCallback,
                                        const std::string& contentName) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return false;
        }
        return jsEngine->LoadPageSource(content, errorCallback, contentName);
    };

    auto mediaQueryCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                         const std::string& callbackId, const std::string& args) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->MediaQueryCallback(callbackId, args);
    };

    auto layoutInspectorCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                       const std::string& componentId) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->LayoutInspectorCallback(componentId);
    };

    auto drawInspectorCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                     const std::string& componentId) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->DrawInspectorCallback(componentId);
    };

    auto onStartContinuationCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)]() -> bool {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return false;
        }
        return jsEngine->OnStartContinuation();
    };

    auto onCompleteContinuationCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](int32_t code) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->OnCompleteContinuation(code);
    };

    auto onSaveDataCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](std::string& savedData) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->OnSaveData(savedData);
    };

    auto onRemoteTerminatedCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)]() {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->OnRemoteTerminated();
    };

    auto onRestoreDataCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                            const std::string& data) -> bool {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return false;
        }
        return jsEngine->OnRestoreData(data);
    };

    auto destroyApplicationCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                                 const std::string& packageName) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->DestroyApplication(packageName);
    };

    auto updateApplicationStateCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                                     const std::string& packageName, Frontend::State state) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->UpdateApplicationState(packageName, state);
    };

    auto onWindowDisplayModeChangedCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                                         bool isShownInMultiWindow, const std::string& data) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->OnWindowDisplayModeChanged(isShownInMultiWindow, data);
    };

    auto externalEventCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                            const std::string& componentId, const uint32_t nodeId,
                                            const bool isDestroy) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->FireExternalEvent(componentId, nodeId, isDestroy);
    };

    auto timerCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                    const std::string& callbackId, const std::string& delay, bool isInterval) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->TimerCallback(callbackId, delay, isInterval);
    };

    auto loadNamedRouterCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                       const std::string& namedRouter, bool isTriggeredByJs) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return false;
        }
        return jsEngine->LoadNamedRouterSource(namedRouter, isTriggeredByJs);
    };

    auto updateRootComponentCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)]() {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return false;
        }
        return jsEngine->UpdateRootComponent();
    };

    pageRouterManager->SetLoadJsCallback(std::move(loadPageCallback));
    pageRouterManager->SetLoadJsByBufferCallback(std::move(loadPageByBufferCallback));
    pageRouterManager->SetLoadNamedRouterCallback(std::move(loadNamedRouterCallback));
    pageRouterManager->SetUpdateRootComponentCallback(std::move(updateRootComponentCallback));

    delegate_ = AceType::MakeRefPtr<Framework::FrontendDelegateDeclarativeNG>(taskExecutor);
    delegate_->SetMediaQueryCallback(std::move(mediaQueryCallback));
    delegate_->SetLayoutInspectorCallback(std::move(layoutInspectorCallback));
    delegate_->SetDrawInspectorCallback(std::move(drawInspectorCallback));
    delegate_->SetOnStartContinuationCallBack(std::move(onStartContinuationCallBack));
    delegate_->SetOnCompleteContinuationCallBack(std::move(onCompleteContinuationCallBack));
    delegate_->SetOnSaveDataCallBack(std::move(onSaveDataCallBack));
    delegate_->SetOnRemoteTerminatedCallBack(std::move(onRemoteTerminatedCallBack));
    delegate_->SetOnRestoreDataCallBack(std::move(onRestoreDataCallBack));
    delegate_->SetDestroyApplicationCallback(std::move(destroyApplicationCallback));
    delegate_->SetUpdateApplicationStateCallback(std::move(updateApplicationStateCallback));
    delegate_->SetOnWindowDisplayModeChangedCallback(std::move(onWindowDisplayModeChangedCallBack));
    delegate_->SetExternalEventCallback(std::move(externalEventCallback));
    delegate_->SetTimerCallback(std::move(timerCallback));

    delegate_->SetPageRouterManager(pageRouterManager);
    if (jsEngine_) {
        delegate_->SetGroupJsBridge(jsEngine_->GetGroupJsBridge());
    }
    auto moduleNamecallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](const std::string& pageName)->
    std::string {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return "";
        }
        return jsEngine->SearchRouterRegisterMap(pageName);
    };
    auto navigationLoadCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
        const std::string bundleName, const std::string& moduleName, const std::string& pageSourceFile,
        bool isSingleton) -> int32_t {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return -1;
        }
        return jsEngine->LoadNavDestinationSource(bundleName, moduleName, pageSourceFile, isSingleton);
    };
    auto container = Container::Current();
    if (container) {
        auto pageUrlChecker = container->GetPageUrlChecker();
        // ArkTSCard container no SetPageUrlChecker
        if (pageUrlChecker != nullptr) {
            pageUrlChecker->SetModuleNameCallback(std::move(moduleNamecallback));
        }
        auto navigationRoute = container->GetNavigationRoute();
        if (navigationRoute) {
            navigationRoute->SetLoadPageCallback(std::move(navigationLoadCallback));
        }
    }
}

RefPtr<NG::PageRouterManager> DeclarativeFrontendNG::GetPageRouterManager() const
{
    CHECK_NULL_RETURN(delegate_, nullptr);
    return delegate_->GetPageRouterManager();
}

void DeclarativeFrontendNG::UpdateState(Frontend::State state)
{
    if (!delegate_ || state == Frontend::State::ON_CREATE) {
        return;
    }
    bool needPostJsTask = true;
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    const auto& setting = container->GetSettings();
    needPostJsTask = !(setting.usePlatformAsUIThread && setting.useUIAsJSThread);
    if (needPostJsTask) {
        delegate_->UpdateApplicationState(delegate_->GetAppID(), state);
        return;
    }
    if (jsEngine_) {
        jsEngine_->UpdateApplicationState(delegate_->GetAppID(), state);
    }
}

void DeclarativeFrontendNG::OnConfigurationUpdated(const std::string& data)
{
    if (delegate_) {
        delegate_->OnConfigurationUpdated(data);
    }
}

void DeclarativeFrontendNG::OnActive()
{
    if (delegate_) {
        foregroundFrontend_ = true;
        delegate_->InitializeAccessibilityCallback();
    }
}

void DeclarativeFrontendNG::OnCompleteContinuation(int32_t code)
{
    if (delegate_) {
        delegate_->OnCompleteContinuation(code);
    }
}

void DeclarativeFrontendNG::OnSaveData(std::string& data)
{
    if (delegate_) {
        delegate_->OnSaveData(data);
    }
}

void DeclarativeFrontendNG::OnRemoteTerminated()
{
    if (delegate_) {
        delegate_->OnRemoteTerminated();
    }
}

void DeclarativeFrontendNG::NotifyAppStorage(const std::string& key, const std::string& value)
{
    if (!delegate_) {
        return;
    }
    delegate_->NotifyAppStorage(jsEngine_, key, value);
}

int32_t DeclarativeFrontendNG::GetRouterSize() const
{
    if (delegate_) {
        return delegate_->GetStackSize();
    }
    return -1;
}

bool DeclarativeFrontendNG::OnStartContinuation()
{
    if (!delegate_) {
        return false;
    }
    return delegate_->OnStartContinuation();
}

bool DeclarativeFrontendNG::OnRestoreData(const std::string& data)
{
    if (!delegate_) {
        return false;
    }
    return delegate_->OnRestoreData(data);
}

UIContentErrorCode DeclarativeFrontendNG::RunPage(const std::string& url, const std::string& params)
{
    auto container = Container::Current();
    auto isStageModel = container ? container->IsUseStageModel() : false;
    if (!isStageModel) {
        // In NG structure and fa mode, first load app.js
        auto taskExecutor = container ? container->GetTaskExecutor() : nullptr;
        CHECK_NULL_RETURN(taskExecutor, UIContentErrorCode::NULL_POINTER);
        taskExecutor->PostTask(
            [weak = AceType::WeakClaim(this)]() {
                auto frontend = weak.Upgrade();
                CHECK_NULL_VOID(frontend);
                CHECK_NULL_VOID(frontend->jsEngine_);
                frontend->jsEngine_->LoadFaAppSource();
            },
            TaskExecutor::TaskType::JS, "ArkUILoadFaAppSource");
    }
    // Not use this pageId from backend, manage it in FrontendDelegateDeclarativeNg.
    if (delegate_) {
        delegate_->RunPage(url, params, pageProfile_);
        return UIContentErrorCode::NO_ERRORS;
    }

    return UIContentErrorCode::NULL_POINTER;
}

UIContentErrorCode DeclarativeFrontendNG::RunPage(
    const std::shared_ptr<std::vector<uint8_t>>& content, const std::string& params)
{
    auto container = Container::Current();
    auto isStageModel = container ? container->IsUseStageModel() : false;
    if (!isStageModel) {
        LOGE("RunPage by buffer must be run under stage model.");
        return UIContentErrorCode::NO_STAGE;
    }

    if (delegate_) {
        delegate_->RunPage(content, params, pageProfile_);
        return UIContentErrorCode::NO_ERRORS;
    }

    return UIContentErrorCode::NULL_POINTER;
}

UIContentErrorCode DeclarativeFrontendNG::RunPageByNamedRouter(const std::string& name, const std::string& params)
{
    if (delegate_) {
        delegate_->RunPage(name, params, pageProfile_, true);
        return UIContentErrorCode::NO_ERRORS;
    }
    return UIContentErrorCode::NULL_POINTER;
}

void DeclarativeFrontendNG::ReplacePage(const std::string& url, const std::string& params)
{
    if (delegate_) {
        delegate_->Replace(url, params);
    }
}

void DeclarativeFrontendNG::PushPage(const std::string& url, const std::string& params)
{
    if (delegate_) {
        delegate_->Push(url, params);
    }
}


napi_value DeclarativeFrontendNG::GetContextValue()
{
    return jsEngine_->GetContextValue();
}

napi_value DeclarativeFrontendNG::GetFrameNodeValueByNodeId(int32_t nodeId)
{
    return jsEngine_->GetFrameNodeValueByNodeId(nodeId);
}

void DeclarativeFrontendNG::NavigatePage(uint8_t type, const PageTarget& target, const std::string& params)
{
    if (delegate_) {
        delegate_->NavigatePage(type, target, params);
    }
}

void DeclarativeFrontendNG::OnWindowDisplayModeChanged(bool isShownInMultiWindow, const std::string& data)
{
    delegate_->OnWindowDisplayModeChanged(isShownInMultiWindow, data);
}

RefPtr<AccessibilityManager> DeclarativeFrontendNG::GetAccessibilityManager() const
{
    if (!delegate_) {
        return nullptr;
    }
    return delegate_->GetJSAccessibilityManager();
}

WindowConfig& DeclarativeFrontendNG::GetWindowConfig()
{
    if (!delegate_) {
        static WindowConfig windowConfig;
        return windowConfig;
    }
    return delegate_->GetWindowConfig();
}

bool DeclarativeFrontendNG::OnBackPressed()
{
    CHECK_NULL_RETURN(delegate_, false);
    return delegate_->OnPageBackPress();
}

void DeclarativeFrontendNG::OnShow()
{
    foregroundFrontend_ = true;
    CHECK_NULL_VOID(delegate_);
    delegate_->OnPageShow();
}

void DeclarativeFrontendNG::OnHide()
{
    foregroundFrontend_ = false;
    CHECK_NULL_VOID(delegate_);
    delegate_->OnPageHide();
}

void DeclarativeFrontendNG::CallRouterBack()
{
    if (delegate_) {
        if (delegate_->GetStackSize() == 1 && isSubWindow_) {
            LOGW("Can't back because this is the last page of sub window!");
            return;
        }
        delegate_->Back("", "");
    }
}

void DeclarativeFrontendNG::OnSurfaceChanged(int32_t width, int32_t height)
{
    // TODO: update media query infos
    if (delegate_) {
        delegate_->OnSurfaceChanged();
    }
}

void DeclarativeFrontendNG::OnLayoutCompleted(const std::string& componentId)
{
    if (delegate_) {
        delegate_->OnLayoutCompleted(componentId);
    }
}

void DeclarativeFrontendNG::OnDrawCompleted(const std::string& componentId)
{
    if (delegate_) {
        delegate_->OnDrawCompleted(componentId);
    }
}

void DeclarativeFrontendNG::DumpFrontend() const
{
    if (!delegate_) {
        return;
    }
    int32_t routerIndex = 0;
    std::string routerName;
    std::string routerPath;
    delegate_->GetState(routerIndex, routerName, routerPath);

    if (DumpLog::GetInstance().GetDumpFile()) {
        DumpLog::GetInstance().AddDesc("Components: " + std::to_string(delegate_->GetComponentsCount()));
        DumpLog::GetInstance().AddDesc("Path: " + routerPath);
        DumpLog::GetInstance().AddDesc("Length: " + std::to_string(routerIndex));
        DumpLog::GetInstance().Print(0, routerName, 0);
    }
}

std::string DeclarativeFrontendNG::GetPagePath() const
{
    if (!delegate_) {
        return "";
    }
    int32_t routerIndex = 0;
    std::string routerName;
    std::string routerPath;
    delegate_->GetState(routerIndex, routerName, routerPath);
    return routerPath + routerName;
}

void DeclarativeFrontendNG::TriggerGarbageCollection()
{
    if (jsEngine_) {
        jsEngine_->RunGarbageCollection();
    }
}

void DeclarativeFrontendNG::DumpHeapSnapshot(bool isPrivate)
{
    if (jsEngine_) {
        jsEngine_->DumpHeapSnapshot(isPrivate);
    }
}

void DeclarativeFrontendNG::NotifyUIIdle()
{
    if (jsEngine_) {
        jsEngine_->NotifyUIIdle();
    }
}

std::pair<RouterRecoverRecord, UIContentErrorCode> DeclarativeFrontendNG::RestoreRouterStack(
    const std::string& contentInfo, ContentInfoType type)
{
    if (delegate_) {
        return delegate_->RestoreRouterStack(contentInfo, type);
    }
    return std::make_pair(RouterRecoverRecord(), UIContentErrorCode::NULL_POINTER);
}

std::string DeclarativeFrontendNG::GetContentInfo(ContentInfoType type) const
{
    if (delegate_) {
        return delegate_->GetContentInfo(type);
    }
    return "";
}

void DeclarativeFrontendNG::SetColorMode(ColorMode colorMode)
{
    // TODO: update media query infos
    if (delegate_) {
        delegate_->SetColorMode(colorMode);
    }
}

void DeclarativeFrontendNG::RebuildAllPages()
{
    if (delegate_) {
        delegate_->RebuildAllPages();
    }
}

void DeclarativeFrontendNG::FlushReload()
{
    if (jsEngine_) {
        jsEngine_->FlushReload();
    }
}

void DeclarativeFrontendNG::HotReload()
{
    auto manager = GetPageRouterManager();
    CHECK_NULL_VOID(manager);
    manager->FlushFrontend();
}

std::string DeclarativeFrontendNG::GetCurrentPageUrl() const
{
    auto pageRouterManager = GetPageRouterManager();
    if (pageRouterManager) {
        return pageRouterManager->GetCurrentPageUrl();
    }
    return "";
}
} // namespace OHOS::Ace
