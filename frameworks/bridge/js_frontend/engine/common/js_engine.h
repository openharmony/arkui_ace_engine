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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_JS_ENGINE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_JS_ENGINE_H

#include <string>
#include <unordered_map>

#include "core/common/frontend.h"
#include "core/common/js_message_dispatcher.h"
#include "frameworks/bridge/js_frontend/frontend_delegate.h"
#include "frameworks/bridge/js_frontend/js_ace_page.h"

class NativeEngine;
namespace OHOS::Ace::Framework {
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
};

class JsEngine : public AceType {
    DECLARE_ACE_TYPE(JsEngine, AceType);

public:
    JsEngine() = default;
    virtual ~JsEngine() = default;

    void RegisterSingleComponent(std::string& command, const std::string& componentName, const std::string& methods);

    void RegisterSingleModule(std::string& command, const std::string& moduleName, const std::string& methods);

    void RegisterModules(std::string& command);

    void RegisterComponents(std::string& command);

    // Initialize the JS engine.
    virtual bool Initialize(const RefPtr<FrontendDelegate>& delegate) = 0;

    // Load script in JS engine, and execute in corresponding context.
    virtual void LoadJs(const std::string& url, const RefPtr<JsAcePage>& page, bool isMainPage) = 0;

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
    virtual void FireExternalEvent(const std::string& componentId, const uint32_t nodeId) = 0;

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

    virtual bool OnStartContinuation() { return false; }

    virtual void OnCompleteContinuation(int32_t code) {}

    virtual void OnRemoteTerminated() {}

    virtual void OnSaveData(std::string& data) {}

    virtual bool OnRestoreData(const std::string& data) { return false; }

    virtual void MediaQueryCallback(const std::string& callbackId, const std::string& args)
    {
        if (mediaUpdateCallback_) {
            mediaUpdateCallback_(this);
        }
    }

    virtual void RequestAnimationCallback(const std::string& callbackId, uint64_t timeStamp) = 0;

    virtual void JsCallback(const std::string& callbackId, const std::string& args) = 0;

    virtual void RunGarbageCollection() = 0;

    virtual void NotifyAppStorage(const std::string& key, const std::string& value) {}

    virtual RefPtr<GroupJsBridge> GetGroupJsBridge() = 0;

    virtual ACE_EXPORT FrontendDelegate* GetFrontend() {
        return nullptr;
    }

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

    void SetDialogCallback(const DialogCallback callback)
    {
        dialogCallback_ = callback;
    }

    DialogCallback GetDialogCallback() const
    {
        return dialogCallback_;
    }

    void AddExtraNativeObject(const std::string& key, void* value)
    {
        extraNativeObject_[key] = value;
    }

    const std::unordered_map<std::string, void*>& GetExtraNativeObject() const
    {
        return extraNativeObject_;
    }

    virtual RefPtr<Component> GetNewComponentWithJsCode(const std::string& jsCode)
    {
        return nullptr;
    }

    static NativeEngine* GetNativeEngine()
    {
        return nativeEngine_;
    }

    void ACE_EXPORT RegistMediaUpdateCallback(std::function<void(JsEngine*)> cb)
    {
        mediaUpdateCallback_ = cb;
    }

    void ACE_EXPORT UnregistMediaUpdateCallback()
    {
        mediaUpdateCallback_ = nullptr;
    }

    virtual void RunNativeEngineLoop();

protected:
    static thread_local NativeEngine* nativeEngine_;
    std::function<void(JsEngine*)> mediaUpdateCallback_;

private:
    // weather the app has debugger.so.
    bool isDebugVersion_ = false;

    // if debug, '-D' means need debug breakpoint, by default, do not enter breakpoint.
    bool needDebugBreakPoint_ = false;

    std::string instanceName_;

    std::unordered_map<std::string, void*> extraNativeObject_;
    DialogCallback dialogCallback_;
};

} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_JS_ENGINE_H
