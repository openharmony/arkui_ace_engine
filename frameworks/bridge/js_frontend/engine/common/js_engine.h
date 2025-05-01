/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_JS_ENGINE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_JS_ENGINE_H

#include <functional>
#include <set>
#include <string>
#include <memory>
#include <unordered_map>

#include "base/utils/macros.h"
#include "bridge/js_frontend/engine/jsi/js_value.h"
#include "core/common/frontend.h"
#include "core/common/js_message_dispatcher.h"
#include "frameworks/bridge/js_frontend/frontend_delegate.h"

class NativeEngine;
class NativeReference;
typedef struct napi_value__* napi_value;

namespace OHOS::Ace::Framework {
class JsAcePage;
using PixelMapNapiEntry = void* (*)(void*, void*);
struct JsModule {
    const std::string moduleName;
    const std::string methods;
};

struct JsComponent {
    const std::string componentName;
    const std::string methods;
};

class JsEngineInstance {
public:
    JsEngineInstance() = default;
    virtual ~JsEngineInstance() = default;

    virtual void FlushCommandBuffer(void* context, const std::string& command);
    NativeEngine* GetNativeEngine()
    {
        return nativeEngine_;
    }
    void SetNativeEngine(NativeEngine* nativeEngine)
    {
        nativeEngine_ = nativeEngine;
    }

protected:
    NativeEngine* nativeEngine_ = nullptr;
};

using InspectorFunc = std::function<void()>;
class InspectorEvent : public virtual AceType {
    DECLARE_ACE_TYPE(InspectorEvent, AceType)
public:
    explicit InspectorEvent(InspectorFunc&& callback) : callback_(std::move(callback)) {}
    ~InspectorEvent() override = default;

    void operator()() const
    {
        if (callback_) {
            callback_();
        }
    }

private:
    InspectorFunc callback_;
};

using PageUrlCheckFunc = std::function<void(const std::string&, const std::function<void()>&,
    const std::function<void(int32_t, const std::string&)>&)>;

class ACE_FORCE_EXPORT JsEngine : public AceType {
    DECLARE_ACE_TYPE(JsEngine, AceType);

public:
    JsEngine() = default;
    ~JsEngine() override = default;

    void RegisterSingleComponent(std::string& command, const std::string& componentName, const std::string& methods);

    void RegisterSingleModule(std::string& command, const std::string& moduleName, const std::string& methods);

    void RegisterModules(std::string& command);

    void RegisterComponents(std::string& command);

    // Initialize the JS engine.
    virtual bool Initialize(const RefPtr<FrontendDelegate>& delegate) = 0;

    // Destroy the JS engine resource.
    virtual void Destroy() {}

    // Load script in JS engine, and execute in corresponding context.
    virtual void LoadJs(const std::string& url, const RefPtr<JsAcePage>& page, bool isMainPage) = 0;
    // Load ets card script in JS engine, and execute in corresponding context.
    virtual bool LoadCard(const std::string& url, int64_t cardId, const std::string& entryPoint = "")
    {
        return false;
    }

    // Load the app.js file of the FA model in NG structure..
    virtual bool LoadFaAppSource()
    {
        return false;
    }

    // Load the js file of the page in NG structure..
    virtual bool LoadPageSource(
        const std::string& /* url */, const std::function<void(const std::string&, int32_t)>& errorCallback = nullptr)
    {
        return false;
    }

    virtual bool LoadPageSource(
        const std::shared_ptr<std::vector<uint8_t>>& content,
        const std::function<void(const std::string&, int32_t)>& errorCallback = nullptr,
        const std::string& contentName = "")
    {
        return false;
    }

    virtual bool LoadNamedRouterSource(const std::string& namedRoute, bool isTriggeredByJs)
    {
        return false;
    }

    virtual std::unique_ptr<JsonValue> GetFullPathInfo()
    {
        return nullptr;
    }

    virtual void RestoreFullPathInfo(std::unique_ptr<JsonValue> namedRouterInfo) {}

    virtual std::unique_ptr<JsonValue> GetNamedRouterInfo()
    {
        return nullptr;
    }

    virtual void RestoreNamedRouterInfo(std::unique_ptr<JsonValue> namedRouterInfo) {}

    virtual bool IsNamedRouterNeedPreload(const std::string& name)
    {
        return false;
    }

    virtual void PreloadNamedRouter(const std::string& name, std::function<void(bool)>&& loadFinishCallback) {}

    virtual void SetPageUrlCheckFunc(PageUrlCheckFunc&& func)
    {
        pageUrlCheckFunc_ = func;
    }

    virtual std::string SearchRouterRegisterMap(const std::string& pageName)
    {
        return "";
    }

    virtual int32_t LoadNavDestinationSource(const std::string& pageUrl, const std::string& bundleName,
        const std::string& moduleName, bool isSingleton)
    {
        return false;
    }

    virtual bool UpdateRootComponent()
    {
        return false;
    }

    virtual bool LoadPluginComponent(const std::string &url, const RefPtr<JsAcePage>& page, bool isMainPage)
    {
        return false;
    }

    virtual bool ExecuteJs(const uint8_t* content, int32_t size)
    {
        return false;
    }

    // Update running page
    virtual void UpdateRunningPage(const RefPtr<JsAcePage>& page) = 0;

    // Update staging page
    virtual void UpdateStagingPage(const RefPtr<JsAcePage>& page) = 0;

    // Reset loading page
    virtual void ResetStagingPage() = 0;

    virtual void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) = 0;

    // Fire AsyncEvent on JS
    virtual void FireAsyncEvent(const std::string& eventId, const std::string& param) = 0;

    // Fire SyncEvent on JS
    virtual void FireSyncEvent(const std::string& eventId, const std::string& param) = 0;

    // Fire external event on JS thread
    virtual void FireExternalEvent(const std::string& componentId, uint32_t nodeId, bool isDestroy = false) = 0;

    // Timer callback on JS
    virtual void TimerCallback(const std::string& callbackId, const std::string& delay, bool isInterval) = 0;

    // Destroy page instance on JS
    virtual void DestroyPageInstance(int32_t pageId) = 0;

    // destroy application instance according packageName
    virtual void DestroyApplication(const std::string& packageName) = 0;

    // update application State according packageName
    virtual void UpdateApplicationState(const std::string& packageName, Frontend::State state) {}

    virtual void OnWindowDisplayModeChanged(bool isShownInMultiWindow, const std::string& data) {}

    virtual void OnNewWant(const std::string& data) {}

    virtual void OnSaveAbilityState(std::string& data) {}

    virtual void OnRestoreAbilityState(const std::string& data) {}

    virtual void OnConfigurationUpdated(const std::string& data) {}

    virtual void OnActive() {}

    virtual void OnInactive() {}

    virtual void OnMemoryLevel(const int32_t code) {}

    virtual bool OnStartContinuation()
    {
        return false;
    }

    virtual void OnCompleteContinuation(int32_t code) {}

    virtual void OnRemoteTerminated() {}

    virtual void OnSaveData(std::string& data) {}

    virtual bool OnRestoreData(const std::string& data)
    {
        return false;
    }

    virtual void MediaQueryCallback(const std::string& callbackId, const std::string& args)
    {
        if (mediaUpdateCallback_) {
            mediaUpdateCallback_(this);
        }
    }

    void LayoutInspectorCallback(const std::string& componentId)
    {
        auto iter = layoutEvents_.find(componentId);
        if (iter != layoutEvents_.end()) {
            for (auto&& observer : iter->second) {
                (*observer)();
            }
        }
    }

    void DrawInspectorCallback(const std::string& componentId)
    {
        auto iter = drawEvents_.find(componentId);
        if (iter != drawEvents_.end()) {
            for (auto&& observer : iter->second) {
                (*observer)();
            }
        }
    }

    virtual void RequestAnimationCallback(const std::string& callbackId, uint64_t timeStamp) = 0;

    virtual void JsCallback(const std::string& callbackId, const std::string& args) = 0;

    virtual void SetErrorEventHandler(std::function<void(const std::string&, const std::string&)>&& errorCallback) {}

    virtual void RunGarbageCollection() = 0;

    virtual void RunFullGarbageCollection() {}

    virtual void DumpHeapSnapshot(bool isPrivate) {}

    virtual void DestroyHeapProfiler() {}

    virtual void ForceFullGC() {}

    virtual void NotifyUIIdle() {}

    virtual std::string GetStacktraceMessage()
    {
        return "";
    }

    virtual void GetStackTrace(std::string& trace) {}

    virtual void NotifyAppStorage(const std::string& key, const std::string& value) {}

    virtual RefPtr<GroupJsBridge> GetGroupJsBridge() = 0;

    virtual ACE_EXPORT RefPtr<FrontendDelegate> GetFrontend()
    {
        return nullptr;
    }

    virtual void SetLocalStorage(int32_t instanceId, NativeReference* storage) {}

    virtual void SetContext(int32_t instanceId, NativeReference* context) {}

    virtual std::shared_ptr<Framework::JsValue> GetJsContext() { return nullptr; }

    virtual void SetJsContext(const std::shared_ptr<Framework::JsValue>& jsContext) {}

    virtual std::shared_ptr<void> SerializeValue(
        const std::shared_ptr<Framework::JsValue>& jsValue) { return nullptr; }

    virtual void SetJsContextWithDeserialize(const std::shared_ptr<void>& recoder) {}

    virtual void SetPkgNameList(const std::map<std::string, std::string>& map) {}

    virtual void SetPkgAliasList(const std::map<std::string, std::string>& map) {}

    virtual void SetpkgContextInfoList(const std::map<std::string, std::vector<std::vector<std::string>>>& map) {}

    bool IsDebugVersion() const
    {
        return isDebugVersion_;
    }

    void SetDebugVersion(bool value)
    {
        isDebugVersion_ = value;
    }

    bool NeedDebugBreakPoint() const
    {
        return needDebugBreakPoint_;
    }

    void SetNeedDebugBreakPoint(bool value)
    {
        needDebugBreakPoint_ = value;
    }

    const std::string& GetInstanceName() const
    {
        return instanceName_;
    }

    void SetInstanceName(const std::string& name)
    {
        instanceName_ = name;
    }

    void AddExtraNativeObject(const std::string& key, void* value)
    {
        extraNativeObject_[key] = value;
    }

    const std::unordered_map<std::string, void*>& GetExtraNativeObject() const
    {
        return extraNativeObject_;
    }

    void SetForceUpdate(bool needUpdate)
    {
        needUpdate_ = needUpdate;
    }

    NativeEngine* GetNativeEngine()
    {
        return nativeEngine_;
    }

    void ACE_EXPORT RegisterMediaUpdateCallback(std::function<void(JsEngine*)> cb)
    {
        mediaUpdateCallback_ = std::move(cb);
    }

    void ACE_EXPORT UnregisterMediaUpdateCallback()
    {
        mediaUpdateCallback_ = nullptr;
    }

    void ACE_EXPORT RegisterLayoutInspectorCallback(
        const RefPtr<InspectorEvent>& layoutEvent, const std::string& componentId)
    {
        layoutEvents_[componentId].emplace(layoutEvent);
    }

    void ACE_EXPORT UnregisterLayoutInspectorCallback(
        const RefPtr<InspectorEvent>& layoutEvent, const std::string& componentId)
    {
        auto iter = layoutEvents_.find(componentId);
        if (iter != layoutEvents_.end()) {
            iter->second.erase(layoutEvent);
            if (iter->second.empty()) {
                layoutEvents_.erase(componentId);
            }
        }
    }

    void ACE_EXPORT RegisterDrawInspectorCallback(
        const RefPtr<InspectorEvent>& drawEvent, const std::string& componentId)
    {
        drawEvents_[componentId].emplace(drawEvent);
    }

    void ACE_EXPORT UnregisterDrawInspectorCallback(
        const RefPtr<InspectorEvent>& drawEvent, const std::string& componentId)
    {
        auto iter = drawEvents_.find(componentId);
        if (iter != drawEvents_.end()) {
            iter->second.erase(drawEvent);
            if (iter->second.empty()) {
                drawEvents_.erase(componentId);
            }
        }
    }

    bool IsLayoutCallBackFuncExist(const std::string& componentId) const
    {
        if (layoutEvents_.find(componentId) != layoutEvents_.end()) {
            return true;
        }
        return false;
    }

    bool IsDrawCallBackFuncExist(const std::string& componentId) const
    {
        if (drawEvents_.find(componentId) != drawEvents_.end()) {
            return true;
        }
        return false;
    }

    virtual void RunNativeEngineLoop();

    virtual void SetPluginBundleName(const std::string& pluginBundleName) {}

    virtual void SetPluginModuleName(const std::string& pluginModuleName) {}

#if !defined(PREVIEW)
    static PixelMapNapiEntry GetPixelMapNapiEntry();
#endif
#if defined(PREVIEW)
    virtual RefPtr<Component> GetNewComponentWithJsCode(const std::string& jsCode, const std::string& viewID)
    {
        return nullptr;
    }

    virtual bool ExecuteJsForFastPreview(const std::string& jsCode, const std::string& viewID)
    {
        return true;
    }

    virtual void ReplaceJSContent(const std::string& url, const std::string componentName)
    {
        LOGE("Ark does not support replaceJSContent");
        return;
    }

    virtual void InitializeModuleSearcher(
        const std::string& bundleName, const std::string& moduleName, const std::string assetPath, bool isBundle)
    {
        LOGE("Ark does not support InitializeModuleSearcher");
    }

    virtual bool IsComponentPreview()
    {
        return false;
    }
#endif
    virtual void FlushReload() {}
    virtual napi_value GetContextValue()
    {
        napi_value value = nullptr;
        return value;
    }

    virtual napi_value GetFrameNodeValueByNodeId(int32_t nodeId)
    {
        return nullptr;
    }

protected:
    NativeEngine* nativeEngine_ = nullptr;
    std::function<void(JsEngine*)> mediaUpdateCallback_;
    std::map<std::string, std::set<RefPtr<InspectorEvent>>> layoutEvents_;
    std::map<std::string, std::set<RefPtr<InspectorEvent>>> drawEvents_;
    bool needUpdate_ = false;
    PageUrlCheckFunc pageUrlCheckFunc_;

private:
    // weather the app has debugger.so.
    bool isDebugVersion_ = false;

    // if debug, '-D' means need debug breakpoint, by default, do not enter breakpoint.
    bool needDebugBreakPoint_ = false;

    std::string instanceName_;

    std::unordered_map<std::string, void*> extraNativeObject_;
};
} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_JS_ENGINE_H
