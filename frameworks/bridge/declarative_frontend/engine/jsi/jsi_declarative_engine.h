/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_DECLARATIVE_ENGINE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_DECLARATIVE_ENGINE_H

#include <cstddef>
#include <cstdint>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <vector>

#include "ecmascript/napi/include/jsnapi.h"
#include "native_engine/impl/ark/ark_native_engine.h"

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/common/ace_application_info.h"
#include "core/common/ace_page.h"
#include "core/components/xcomponent/native_interface_xcomponent_impl.h"
#include "core/components_ng/base/ui_node.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"
#include "frameworks/bridge/js_frontend/engine/jsi/js_runtime.h"
#include "frameworks/bridge/js_frontend/js_ace_page.h"

namespace OHOS::Ace::Framework {

struct NamedRouterProperty {
    panda::Global<panda::FunctionRef> pageGenerator;
    std::string bundleName;
    std::string moduleName;
    std::string pagePath;
    std::string ohmUrl;
};

class JsiDeclarativeEngineInstance final : public AceType, public JsEngineInstance {
    DECLARE_ACE_TYPE(JsiDeclarativeEngineInstance, AceType)
public:
    explicit JsiDeclarativeEngineInstance(const RefPtr<FrontendDelegate>& delegate) : frontendDelegate_(delegate) {}
    ~JsiDeclarativeEngineInstance() override;

    void FlushCommandBuffer(void* context, const std::string& command) override;

    bool InitJsEnv(bool debuggerMode, const std::unordered_map<std::string, void*>& extraNativeObject,
        const shared_ptr<JsRuntime>& runtime = nullptr);
    void InitJsObject();
    
    bool FireJsEvent(const std::string& eventStr);

    // add Console object to worker
    void InitConsoleModule(ArkNativeEngine* engine);

    static void RootViewHandle(panda::Local<panda::ObjectRef> value);
    void DestroyRootViewHandle(int32_t pageId);
    void DestroyAllRootViewHandle();
    void FlushReload();
    napi_value GetContextValue();
    napi_value GetFrameNodeValueByNodeId(int32_t nodeId);

    static std::unique_ptr<JsonValue> GetI18nStringResource(
        const std::string& targetStringKey, const std::string& targetStringValue);
    static std::string GetMediaResource(const std::string& targetFileName);

    static RefPtr<JsAcePage> GetRunningPage(int32_t instanceId);
    static RefPtr<JsAcePage> GetStagingPage(int32_t instanceId);
    static shared_ptr<JsRuntime> GetCurrentRuntime();
    static void PostJsTask(const shared_ptr<JsRuntime>&, std::function<void()>&& task, const std::string& name);
    static void TriggerPageUpdate(const shared_ptr<JsRuntime>&);
    static RefPtr<PipelineBase> GetPipelineContext(const shared_ptr<JsRuntime>& runtime);
    static void PreloadAceModule(void* runtime);
    static void PreloadAceModuleWorker(void* runtime);
    // crossPlatform Resets the module pre-load flag
    static void ResetModulePreLoadFlag();
    // crossPlatform Prepares for resetting the module pre-load flag
    static void PrepareForResetModulePreLoadFlag();

    WeakPtr<JsMessageDispatcher> GetJsMessageDispatcher() const
    {
        return dispatcher_;
    }

    void SetRunningPage(const RefPtr<JsAcePage>& page)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        runningPage_ = page;
    }

    RefPtr<JsAcePage> GetRunningPage() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return runningPage_;
    }

    void SetStagingPage(const RefPtr<JsAcePage>& page)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stagingPage_ = page;
    }

    RefPtr<JsAcePage> GetStagingPage() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return stagingPage_;
    }

    void ResetStagingPage(const RefPtr<JsAcePage>& page)
    {
        stagingPage_ = page;
    }

    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher)
    {
        dispatcher_ = dispatcher;
    }

    RefPtr<FrontendDelegate> GetDelegate() const
    {
        return frontendDelegate_;
    }

    shared_ptr<JsRuntime> GetJsRuntime()
    {
        return runtime_;
    }

    void SetDebugMode(bool isDebugMode)
    {
        isDebugMode_ = isDebugMode;
    }

    void SetDebuggerPostTask();

    void SetInstanceId(int32_t instanceId)
    {
        instanceId_ = instanceId;
    }

    void SetRootView(int32_t pageId, panda::Global<panda::ObjectRef> value)
    {
        rootViewMap_.emplace(pageId, value);
    }

    bool IsEngineInstanceInitialized()
    {
        return isEngineInstanceInitialized_;
    }

    void RegisterFaPlugin(); // load ReatureAbility plugin

    void SetContextValue(shared_ptr<JsValue> uiContext)
    {
        uiContext_ = uiContext;
    }

#if defined(PREVIEW)
    void SetPkgNameList(const std::map<std::string, std::string>& map)
    {
        pkgNameMap_ = map;
    }

    void SetPkgAliasList(const std::map<std::string, std::string>& map)
    {
        pkgAliasMap_ = map;
    }

    void SetpkgContextInfoList(const std::map<std::string, std::vector<std::vector<std::string>>>& map)
    {
        pkgContextInfoMap_ = map;
    }

    bool CallCurlFunction(const OHOS::Ace::RequestData& requestData, int32_t callbackId)
    {
        auto dispatcher = dispatcher_.Upgrade();
        if (dispatcher) {
            dispatcher->CallCurlFunction(requestData, callbackId);
            return true;
        } else {
            return false;
        }
    }

    bool InitAceModule(const uint8_t* start, size_t length)
    {
        if (!runtime_) {
            return false;
        }
        bool result = runtime_->EvaluateJsCode(start, length);
        if (!result) {
            return false;
        }
        return true;
    }
#endif

    // ArkTsCard start
    static void PreloadAceModuleCard(void* runtime, const std::unordered_set<std::string>& formModuleList);
    static void ReloadAceModuleCard(void* runtime, const std::unordered_set<std::string>& formModuleList);
    // ArkTsCard end
    static bool IsPlugin();
    static bool RegisterStringCacheTable(const EcmaVM* vm, int32_t size);
    static panda::Local<panda::StringRef> GetCachedString(const EcmaVM *vm, int32_t propertyIndex);
    static void SetCachedString(const EcmaVM* vm);

private:
    void InitGlobalObjectTemplate();
    void InitConsoleModule();  // add Console object to global
    void InitAceModule();      // add ace object to global
    void InitPerfUtilModule(); // add perfutil object to global
    void InitJsExportsUtilObject();
    void InitJsNativeModuleObject();
    void InitJsContextModuleObject();
    void InitGroupJsBridge();
    static shared_ptr<JsRuntime> InnerGetCurrentRuntime();
    shared_ptr<JsValue> CallGetUIContextFunc(
        const shared_ptr<JsRuntime>& runtime, const std::vector<shared_ptr<JsValue>>& argv);
    shared_ptr<JsValue> CallGetFrameNodeByNodeIdFunc(
        const shared_ptr<JsRuntime>& runtime, const std::vector<shared_ptr<JsValue>>& argv);
    std::unordered_map<int32_t, panda::Global<panda::ObjectRef>> rootViewMap_;
    static std::unique_ptr<JsonValue> currentConfigResourceData_;
    static std::map<std::string, std::string> mediaResourceFileMap_;
    static std::shared_mutex sharedMutex_;

    // runningPage_ is the page that is loaded and rendered successfully, while stagingPage_ is to
    // handle all page routing situation, which include two stages:
    // - Loading stage: when a new page is loaded by qjs engine but not rendered, stagingPage_ point to
    //   a new created page, which is different with runningPage_, the DOM build operations should call
    //   this one, such as domCreateBody, domAddElement.
    // - Running stage: If the stagingPage_ rendered successfully, the runningPage_ will update to stagingPage_.
    //   If the stagingPage_ render failed, it will reset to runningPage_. So in running stage, runningPage_
    //   and stagingPage_ point to the same page. But it's better to use runningPage_ in dom update tasks,
    //   such as removeElement, updateElementAttrs and updateElementStyles.
#if defined(PREVIEW)
    std::map<std::string, std::string> pkgNameMap_;
    std::map<std::string, std::string> pkgAliasMap_;
    std::map<std::string, std::vector<std::vector<std::string>>> pkgContextInfoMap_;
#endif
    RefPtr<JsAcePage> runningPage_;
    RefPtr<JsAcePage> stagingPage_;

    shared_ptr<JsRuntime> runtime_;
    RefPtr<FrontendDelegate> frontendDelegate_;
    WeakPtr<JsMessageDispatcher> dispatcher_;
    mutable std::mutex mutex_;
    bool isDebugMode_ = true;
    bool usingSharedRuntime_ = false;
    bool isEngineInstanceInitialized_ = false;
    int32_t instanceId_ = 0;
    static bool isModulePreloaded_;
    static bool isModuleInitialized_;
    static shared_ptr<JsRuntime> globalRuntime_;
    shared_ptr<JsValue> uiContext_;
    static std::shared_mutex globalRuntimeMutex_;

    ACE_DISALLOW_COPY_AND_MOVE(JsiDeclarativeEngineInstance);
};

class JsiDeclarativeEngine : public JsEngine {
    DECLARE_ACE_TYPE(JsiDeclarativeEngine, JsEngine)
public:
    JsiDeclarativeEngine(int32_t instanceId, void* runtime) : instanceId_(instanceId), runtime_(runtime) {}
    explicit JsiDeclarativeEngine(int32_t instanceId) : instanceId_(instanceId) {}
    ~JsiDeclarativeEngine() override;

    bool Initialize(const RefPtr<FrontendDelegate>& delegate) override;
    void EngineTask(bool sharedRuntime);

    void Destroy() override;

    // Load and initialize a JS bundle into the JS Framework
    void LoadJs(const std::string& url, const RefPtr<JsAcePage>& page, bool isMainPage) override;
#if !defined(PREVIEW)
    bool IsModule();

    void LoadJsWithModule(
        std::string& urlName, const std::function<void(const std::string&, int32_t)>& errorCallback = nullptr);

    void LoadPluginJsWithModule(std::string& urlName);

#endif
    // Load the app.js file of the FA model in NG structure..
    bool LoadFaAppSource() override;

    // Load the je file of the page in NG structure..
    bool LoadPageSource(const std::string& url,
        const std::function<void(const std::string&, int32_t)>& errorCallback = nullptr) override;
    bool LoadPageSource(const std::shared_ptr<std::vector<uint8_t>>& content,
        const std::function<void(const std::string&, int32_t)>& errorCallback = nullptr,
        const std::string& contentName = "") override;
    int32_t LoadNavDestinationSource(const std::string& pageUrl, const std::string& bundleName,
        const std::string& moduleName, bool isSingleton) override;

    bool LoadCard(const std::string& url, int64_t cardId, const std::string& entryPoint) override;

    // Update running page
    void UpdateRunningPage(const RefPtr<JsAcePage>& page) override;

    // Update staging page
    void UpdateStagingPage(const RefPtr<JsAcePage>& page) override;

    // Reset staging page
    void ResetStagingPage() override;

    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) override;

    // Fire AsyncEvent on JS
    void FireAsyncEvent(const std::string& eventId, const std::string& param) override;

    // Fire SyncEvent on JS
    void FireSyncEvent(const std::string& eventId, const std::string& param) override;

    void FireExternalEvent(const std::string& componentId, uint32_t nodeId, bool isDestroy) override;

    // Timer callback
    void TimerCallback(const std::string& callbackId, const std::string& delay, bool isInterval) override;

    // Destroy page instance
    void DestroyPageInstance(int32_t pageId) override;

    void OnActive() override;

    void OnInactive() override;

    void OnNewWant(const std::string& data) override;

    bool OnStartContinuation() override;

    void OnCompleteContinuation(int32_t code) override;

    void OnRemoteTerminated() override;

    void OnSaveData(std::string& data) override;

    bool OnRestoreData(const std::string& data) override;

    // Destroy application instance according to packageName
    void DestroyApplication(const std::string& packageName) override;

    void UpdateApplicationState(const std::string& packageName, Frontend::State state) override;

    void OnWindowDisplayModeChanged(bool isShownInMultiWindow, const std::string& data) override;

    void MediaQueryCallback(const std::string& callbackId, const std::string& args) override;

    void RequestAnimationCallback(const std::string& callbackId, uint64_t timeStamp) override;

    void JsCallback(const std::string& callbackId, const std::string& args) override;

    void RunGarbageCollection() override;

    void RunFullGarbageCollection() override;

    void DumpHeapSnapshot(bool isPrivate) override;

    void NotifyUIIdle() override;

    std::string GetStacktraceMessage() override;

    void GetStackTrace(std::string& trace) override;

    static std::string GetPagePath(const std::string& url);

    static std::string GetFullPathInfo(const std::string& url);

    static std::optional<std::string> GetRouteNameByUrl(
        const std::string& url, const std::string& bundleName, const std::string& moduleName);

    void SetLocalStorage(int32_t instanceId, NativeReference* storage) override;

    void SetContext(int32_t instanceId, NativeReference* context) override;

    std::shared_ptr<Framework::JsValue> GetJsContext() override;

    void SetJsContext(const std::shared_ptr<Framework::JsValue>& jsContext) override;

    void SetErrorEventHandler(std::function<void(const std::string&, const std::string&)>&& errorCallback) override;

    RefPtr<GroupJsBridge> GetGroupJsBridge() override;

    RefPtr<FrontendDelegate> GetFrontend() override
    {
        return engineInstance_->GetDelegate();
    }

    RefPtr<JsiDeclarativeEngineInstance> GetEngineInstance()
    {
        return engineInstance_;
    }

    void FlushReload() override
    {
        if (engineInstance_) {
            engineInstance_->FlushReload();
        }
    }

    void RunNativeEngineLoop() override
    {
        static bool hasPendingExpection = false;
        if (nativeEngine_ && !hasPendingExpection) {
            hasPendingExpection = nativeEngine_->HasPendingException();
            nativeEngine_->Loop(LOOP_NOWAIT, false);
        }
    }

    void SetPluginBundleName(const std::string& pluginBundleName) override
    {
        pluginBundleName_ = pluginBundleName;
    }

    void SetPluginModuleName(const std::string& pluginModuleName) override
    {
        pluginModuleName_ = pluginModuleName;
    }

    napi_value GetContextValue() override
    {
        return engineInstance_->GetContextValue();
    }

    napi_value GetFrameNodeValueByNodeId(int32_t nodeId) override
    {
        return engineInstance_->GetFrameNodeValueByNodeId(nodeId);
    }

    void JsStateProfilerResgiter();

    void JsSetAceDebugMode();

#if defined(PREVIEW)
    void ReplaceJSContent(const std::string& url, const std::string componentName) override;
    RefPtr<Component> GetNewComponentWithJsCode(const std::string& jsCode, const std::string& viewID) override;
    bool ExecuteJsForFastPreview(const std::string& jsCode, const std::string& viewID) override;

    void InitializeModuleSearcher(const std::string& bundleName, const std::string& moduleName,
        const std::string assetPath, bool isBundle) override
    {
        bundleName_ = bundleName;
        moduleName_ = moduleName;
        assetPath_ = assetPath;
        isBundle_ = isBundle;
    }
    // Support the hsp on the previewer
    void SetHspBufferTrackerCallback(
        std::function<bool(const std::string&, uint8_t**, size_t*, std::string&)>&& callback);
    // Support to execute the ets code mocked by developer
    void SetMockModuleList(const std::map<std::string, std::string>& mockJsonInfo);
    bool IsComponentPreview() override;
#endif
    static void AddToNamedRouterMap(const EcmaVM* vm, panda::Global<panda::FunctionRef> pageGenerator,
        const std::string& namedRoute, panda::Local<panda::ObjectRef> params);
    static void AddToNavigationBuilderMap(std::string name,
        panda::Global<panda::ObjectRef> builderFunc);
    bool LoadNamedRouterSource(const std::string& namedRoute, bool isTriggeredByJs) override;
    std::unique_ptr<JsonValue> GetFullPathInfo() override;
    void RestoreFullPathInfo(std::unique_ptr<JsonValue> namedRouterInfo) override;
    std::unique_ptr<JsonValue> GetNamedRouterInfo() override;
    void RestoreNamedRouterInfo(std::unique_ptr<JsonValue> namedRouterInfo) override;
    bool IsNamedRouterNeedPreload(const std::string& name) override;
    void PreloadNamedRouter(const std::string& name, std::function<void(bool)>&& loadFinishCallback) override;
    std::string SearchRouterRegisterMap(const std::string& pageName) override;
    bool UpdateRootComponent() override;
    bool LoadPluginComponent(const std::string& url, const RefPtr<JsAcePage>& page, bool isMainPage) override;
    static void SetEntryObject(const panda::Global<panda::ObjectRef>& obj)
    {
        obj_ = obj;
    }
    bool ExecuteJs(const uint8_t* content, int32_t size) override;

    panda::Global<panda::ObjectRef> GetNavigationBuilder(std::string name);

    // crossPlatform Clears the 'namedRouterRegisterMap_'
    static void ResetNamedRouterRegisterMap();
private:
    bool CallAppFunc(const std::string& appFuncName);

    bool CallAppFunc(const std::string& appFuncName, std::vector<shared_ptr<JsValue>>& argv);

    void SetPostTask(NativeEngine* nativeEngine);

    void TimerCallJs(const std::string& callbackId) const;

    void InitXComponent(const std::string& componentId);

    void RegisterWorker();
    void RegisterInitWorkerFunc();
    void RegisterOffWorkerFunc();
    void RegisterAssetFunc();
    bool ExecuteAbc(const std::string& fileName);
    bool ExecuteCardAbc(const std::string& fileName, int64_t cardId);
    bool ExecuteDynamicAbc(const std::string& fileName, const std::string& entryPoint);
    bool InnerExecuteIsolatedAbc(const std::string& fileName, const std::string& entryPoint);
    bool InnerExecuteDynamicAbc(const std::string& fileName, const std::string& entryPoint);

    RefPtr<JsiDeclarativeEngineInstance> engineInstance_;

    RefPtr<NativeXComponentImpl> nativeXComponentImpl_;

    OH_NativeXComponent* nativeXComponent_ = nullptr;

    int32_t instanceId_ = 0;
    void* runtime_ = nullptr;
#if defined(PREVIEW)
    void SetPkgNameList(const std::map<std::string, std::string>& map) override
    {
        pkgNameMap_ = map;
    }

    void SetPkgAliasList(const std::map<std::string, std::string>& map) override
    {
        pkgAliasMap_ = map;
    }

    void SetpkgContextInfoList(const std::map<std::string, std::vector<std::vector<std::string>>>& map) override
    {
        pkgContextInfoMap_ = map;
    }

    std::map<std::string, std::string> pkgNameMap_;
    std::map<std::string, std::string> pkgAliasMap_;
    std::map<std::string, std::vector<std::vector<std::string>>> pkgContextInfoMap_;

    std::string assetPath_;
    std::string bundleName_;
    std::string moduleName_;
    bool isBundle_ = true;
#endif
    std::string pluginBundleName_;
    std::string pluginModuleName_;
    static thread_local std::unordered_map<std::string, NamedRouterProperty> namedRouterRegisterMap_;
    static thread_local std::unordered_map<std::string, std::string> routerPathInfoMap_;
    static thread_local std::unordered_map<std::string, panda::Global<panda::ObjectRef>> builderMap_;
    bool isFirstCallShow_ = true;
    static thread_local panda::Global<panda::ObjectRef> obj_;
    ACE_DISALLOW_COPY_AND_MOVE(JsiDeclarativeEngine);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_DECLARATIVE_ENGINE_H
