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

#ifndef FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_ENGINE_JSI_JSI_ENGINE_H
#define FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_ENGINE_JSI_JSI_ENGINE_H

#include <string>

#include "core/common/js_message_dispatcher.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"
#include "frameworks/bridge/js_frontend/engine/jsi/panda_dummy/jsi/include/js_runtime.h"
#include "frameworks/bridge/js_frontend/engine/jsi/panda_dummy/jsi/include/js_value.h"
#include "frameworks/bridge/js_frontend/engine/jsi/jsi_group_js_bridge.h"
#include "frameworks/bridge/js_frontend/engine/jsi/jsi_utils.h"
#include "frameworks/bridge/js_frontend/frontend_delegate.h"
#include "frameworks/bridge/js_frontend/js_ace_page.h"

namespace OHOS::Ace::Framework {
class JsiEngineInstance final : public AceType, public JsEngineInstance {
public:
    explicit JsiEngineInstance(const RefPtr<FrontendDelegate>& delegate, int32_t instanceId)
        : frontendDelegate_(delegate), instanceId_(instanceId)
    {}
    ~JsiEngineInstance() override;

    RefPtr<JsAcePage> GetRunningPage() const;
    void SetRunningPage(const RefPtr<JsAcePage>& page);
    RefPtr<JsAcePage> GetStagingPage() const;
    void SetStagingPage(const RefPtr<JsAcePage>& page);
    void ResetStagingPage(const RefPtr<JsAcePage>& page);
    void SetJsMessageDispatcher(const WeakPtr<JsMessageDispatcher>& dispatcher);
    WeakPtr<JsMessageDispatcher> GetJsMessageDispatcher() const;
    RefPtr<FrontendDelegate> GetFrontendDelegate() const;
    bool FireJsEvent(const std::string& eventStr);
    void CallJs(const std::string& callbackId, const std::string& args, bool keepAlive = false, bool isGlobal = false);
    shared_ptr<JsRuntime> GetJsRuntime() const;
    bool InitJsEnv(bool debugger_mode);

    void FlushCommandBuffer(void* context, const std::string& command) override;

private:
    void RegisterAceModule();             // add ace object to global
    void RegisterConsoleModule();         // add Console object to global
    void RegisterPerfUtilModule();        // add perfutil object to global
    void RegisterHiViewModule();          // add hiView object to global
    void RegisterI18nPluralRulesModule(); // add i18nPluralRules object to global
    void InitGroupJsBridge();

    int32_t GetInstanceId() const
    {
        return instanceId_;
    }

    shared_ptr<JsRuntime> runtime_;
    RefPtr<JsAcePage> runningPage_;
    RefPtr<JsAcePage> stagingPage_;
    WeakPtr<JsMessageDispatcher> dispatcher_;
    RefPtr<FrontendDelegate> frontendDelegate_;
    int32_t instanceId_ = 0;
    mutable std::mutex mutex_;
};

class JsiEngine : public JsEngine {
public:
    explicit JsiEngine(int32_t instanceId) : instanceId_(instanceId) {}
    ~JsiEngine() override = default;

    bool Initialize(const RefPtr<FrontendDelegate>& delegate) override;
    void LoadJs(const std::string& url, const RefPtr<JsAcePage>& page, bool isMainPage) override;
    void UpdateRunningPage(const RefPtr<JsAcePage>& page) override;
    void UpdateStagingPage(const RefPtr<JsAcePage>& page) override;
    void ResetStagingPage() override;
    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) override;
    void DestroyPageInstance(int32_t pageId) override;
    void DestroyApplication(const std::string& packageName) override;
    void FireAsyncEvent(const std::string& eventId, const std::string& param) override;
    void FireSyncEvent(const std::string& eventId, const std::string& param) override;
    void TimerCallback(const std::string& callbackId, const std::string& delay, bool isInterval) override;
    void MediaQueryCallback(const std::string& callbackId, const std::string& args) override;
    void RequestAnimationCallback(const std::string& callbackId, uint64_t timeStamp) override;
    void JsCallback(const std::string& callbackId, const std::string& args) override;
    void RunGarbageCollection() override;
    RefPtr<GroupJsBridge> GetGroupJsBridge() override;

private:
    void GetLoadOptions(std::string& optionStr, bool isMainPage, bool hasAppCode);

    int32_t instanceId_ = 0;
    RefPtr<JsiEngineInstance> engineInstance_;
};
} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_ENGINE_JSI_JSI_ENGINE_H
