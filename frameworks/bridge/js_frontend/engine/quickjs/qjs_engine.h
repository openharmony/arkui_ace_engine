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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_QUICKJS_QJS_ENGINE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_QUICKJS_QJS_ENGINE_H

#include <cstdlib>
#include <mutex>
#include <vector>

#include "third_party/quickjs/quickjs.h"

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/common/ace_page.h"
#include "core/common/js_message_dispatcher.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"
#include "native_engine/impl/quickjs/quickjs_native_engine.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/animation_bridge.h"

namespace OHOS::Ace::Framework {

// Each JsFrontend holds only one QjsEngineInstance.
class QjsEngineInstance final : public AceType, public JsEngineInstance {
public:
    explicit QjsEngineInstance(const RefPtr<FrontendDelegate>& delegate, int32_t instanceId)
        : frontendDelegate_(delegate), instanceId_(instanceId)
    {}
    ~QjsEngineInstance() override;

    void FlushCommandBuffer(void* context, const std::string& command) override;

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

    void CallAnimationFinishJs(JSValue animationContext);
    void CallAnimationCancelJs(JSValue animationContext);
    void CallAnimationRepeatJs(JSValue animationContext);

    JSValue FireJsEvent(const std::string& param);

    void AddAnimationBridge(const WeakPtr<AnimationBridge>& value);
    void RemoveAnimationBridge();
    void FreeAnimationBridges();
    void FreeGroupJsBridge();

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
        std::lock_guard<std::mutex> lock(mutex_);
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

    void ChangeLocale(const std::string& language, const std::string& countryOrRegion)
    {
        if (frontendDelegate_) {
            frontendDelegate_->ChangeLocale(language, countryOrRegion);
        }
    }

private:
    JSRuntime* runtime_ = nullptr;
    JSContext* context_ = nullptr;
    RefPtr<FrontendDelegate> frontendDelegate_;
    int32_t instanceId_;
    std::vector<WeakPtr<AnimationBridge>> animations_;

    // runningPage_ is the page that is loaded and rendered successfully, while stagingPage_ is to
    // handle all page routing situation, which include two stages:
    // - Loading stage: when a new page is loaded by qjs engine but not rendered, stagingPage_ point to
    //   a new created page, which is different with runningPage_, the DOM build operations should call
    //   this one, such as domCreateBody, domAddElement.
    // - Running stage: If the stagingPage_ rendered successfully, the runningPage_ will update to stagingPage_.
    //   If the stagingPage_ render failed, it will reset to runningPage_. So in running stage, runningPage_
    //   and stagingPage_ point to the same page. But it's better to use runningPage_ in dom update tasks,
    //   such as removeElement, updateElementAttrs and updateElementStyles.
    RefPtr<JsAcePage> runningPage_;
    RefPtr<JsAcePage> stagingPage_;

    WeakPtr<JsMessageDispatcher> dispatcher_;
    mutable std::mutex mutex_;

    ACE_DISALLOW_COPY_AND_MOVE(QjsEngineInstance);
};

class QjsEngine : public JsEngine {
public:
    explicit QjsEngine(int32_t instanceId) : instanceId_(instanceId) {};
    ~QjsEngine() override;

    bool Initialize(const RefPtr<FrontendDelegate>& delegate) override;

    // Load and initialize a JS bundle into the JS Framework
    void LoadJs(const std::string& url, const RefPtr<JsAcePage>& page, bool isMainPage) override;

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

    // Timer callback
    void TimerCallback(const std::string& callbackId, const std::string& delay, bool isInterval) override;

    // destroy page instance
    void DestroyPageInstance(int32_t pageId) override;

    virtual void MediaQueryCallback(const std::string& callbackId, const std::string& args) override;

    virtual void RequestAnimationCallback(const std::string& callbackId, uint64_t timeStamp) override;

    virtual void JsCallback(const std::string& callbackId, const std::string& args) override;

    // destroy application instance according packageName
    void DestroyApplication(const std::string& packageName) override;

    void RunGarbageCollection() override;

    RefPtr<GroupJsBridge> GetGroupJsBridge() override;

private:
    void GetLoadOptions(std::string& optionStr, bool isMainPage, const RefPtr<JsAcePage>& page);
    RefPtr<QjsEngineInstance> engineInstance_;
    int32_t instanceId_;
    QuickJSNativeEngine* nativeEngine_ = nullptr;
    ACE_DISALLOW_COPY_AND_MOVE(QjsEngine);
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_QUICKJS_QJS_ENGINE_H
