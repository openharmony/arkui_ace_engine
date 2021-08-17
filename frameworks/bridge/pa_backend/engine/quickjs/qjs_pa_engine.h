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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_ENGINE_QUICKJS_QJS_PA_ENGINE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_ENGINE_QUICKJS_QJS_PA_ENGINE_H

#include <cstdlib>
#include <mutex>
#include <vector>

#include "third_party/quickjs/quickjs.h"

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/common/ace_page.h"
#include "core/common/js_message_dispatcher.h"
#include "native_engine/impl/quickjs/quickjs_native_engine.h"

#include "frameworks/bridge/pa_backend/engine/common/js_backend_engine.h"
#include "frameworks/bridge/pa_backend/backend_delegate.h"

namespace OHOS::Ace::Framework {
// Each JsFrontend holds only one QjsPaEngineInstance.
class QjsPaEngineInstance final : public AceType, public JsBackendEngineInstance {
public:
    explicit QjsPaEngineInstance(const RefPtr<BackendDelegate>& delegate, int32_t instanceId)
        : backendDelegate_(delegate), instanceId_(instanceId)
    {}
    ~QjsPaEngineInstance() override;

    bool InitJsEnv(JSRuntime* runtime, JSContext* context);

    JSRuntime* GetQjsRuntime() const
    {
        return runtime_;
    }

    JSContext* GetQjsContext() const
    {
        return context_;
    }

    void CallJs(const std::string& callbackId, const std::string& args, bool keepAlive = false, bool isGlobal = false);

    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher)
    {
        dispatcher_ = dispatcher;
    }

    RefPtr<BackendDelegate> GetDelegate() const
    {
        return backendDelegate_;
    }

    bool CallPlatformFunction(const std::string& channel, std::vector<uint8_t>&& data, int32_t id)
    {
        auto dispatcher = dispatcher_.Upgrade();
        if (dispatcher) {
            dispatcher->Dispatch(channel, std::move(data), id);
            return true;
        } else {
            LOGW("Dispatcher Upgrade fail when dispatch request mesaage to platform");
            return false;
        }
    }

    bool PluginErrorCallback(int32_t callbackId, int32_t errorCode, std::string&& errorMessage)
    {
        auto dispatcher = dispatcher_.Upgrade();
        if (dispatcher) {
            dispatcher->DispatchPluginError(callbackId, errorCode, std::move(errorMessage));
            return true;
        } else {
            LOGW("Dispatcher Upgrade fail when dispatch error mesaage to platform");
            return false;
        }
    }

    JSValue FireJsEvent(const std::string &param);

private:
    JSRuntime* runtime_ = nullptr;
    JSContext* context_ = nullptr;
    RefPtr<BackendDelegate> backendDelegate_;
    int32_t instanceId_;

    WeakPtr<JsMessageDispatcher> dispatcher_;
    mutable std::mutex mutex_;

    ACE_DISALLOW_COPY_AND_MOVE(QjsPaEngineInstance);
};

class QjsPaEngine : public JsBackendEngine {
public:
    explicit QjsPaEngine(int32_t instanceId) : instanceId_(instanceId) {};
    ~QjsPaEngine() override;

    bool Initialize(const RefPtr<BackendDelegate>& delegate) override;

    // Load and initialize a JS bundle into the JS Framework
    void LoadJs(const std::string& url) override;

    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) override;

    // destroy application instance according packageName
    void DestroyApplication(const std::string &packageName) override;

    // Fire AsyncEvent on JS
    void FireAsyncEvent(const std::string &eventId, const std::string &param) override;

    // Fire SyncEvent on JS
    void FireSyncEvent(const std::string &eventId, const std::string &param) override;

private:
    void GetLoadOptions(std::string& optionStr);
    RefPtr<QjsPaEngineInstance> engineInstance_;
    int32_t instanceId_;
    QuickJSNativeEngine* nativeEngine_ = nullptr;
    ACE_DISALLOW_COPY_AND_MOVE(QjsPaEngine);
};
} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_ENGINE_QUICKJS_QJS_PA_ENGINE_H
