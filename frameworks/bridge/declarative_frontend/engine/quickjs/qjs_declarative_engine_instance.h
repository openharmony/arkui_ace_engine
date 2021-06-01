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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_QJS_DECLARATIVE_ENGINE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_QJS_DECLARATIVE_ENGINE_H

#include <unordered_map>

#include "third_party/quickjs/quickjs.h"

#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"
#include "frameworks/bridge/js_frontend/js_ace_page.h"
#include "native_engine/impl/quickjs/quickjs_native_engine.h"

namespace OHOS::Ace::Framework {

class QJSDeclarativeEngineInstance final : public AceType {
public:
    explicit QJSDeclarativeEngineInstance(const RefPtr<FrontendDelegate>& delegate)
        : runtime_(nullptr), context_(nullptr), frontendDelegate_(delegate), dispatcher_(nullptr)
    {}

    ~QJSDeclarativeEngineInstance() override;

    bool InitJSEnv();

    void loadDocument();

    JSRuntime* GetQJSRuntime() const
    {
        return runtime_;
    }

    JSContext* GetQJSContext() const
    {
        return context_;
    }

    static QJSDeclarativeEngineInstance* UnWrapEngineInstance(JSContext* ctx);

    RefPtr<JsAcePage> GetRunningPage() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return runningPage_;
    }

    static RefPtr<JsAcePage> GetRunningPage(JSContext* ctx);

    void SetStagingPage(const RefPtr<JsAcePage>& page);

    RefPtr<JsAcePage> GetStagingPage() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return stagingPage_;
    }
    void ResetStagingPage(const RefPtr<JsAcePage>& page);

    void SetRunningPage(const RefPtr<JsAcePage>& page);

    static void PostJsTask(JSContext* ctx, std::function<void()>&& task);
    static void TriggerPageUpdate(JSContext* ctx);

    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher)
    {
        dispatcher_ = dispatcher;
    }

    RefPtr<FrontendDelegate> GetDelegate() const
    {
        return frontendDelegate_;
    }

    JSValue CompileSource(std::string url, const char* buf, size_t bufSize);

    void CallPlatformFunction(const std::string& channel, std::vector<uint8_t>&& data, int32_t id, int32_t groupType)
    {
        auto dispatcher = dispatcher_.Upgrade();
        if (dispatcher) {
            dispatcher->Dispatch(channel, std::move(data), id, groupType);
        }
    }

    void CallAnimationFinishJs(JSValue animationContext);
    void CallAnimationCancelJs(JSValue animationContext);

    bool ExecuteDocumentJS(JSValue jsCode);

    void FireAsyncEvent(const std::string& eventId, const std::string& param);

    /** Pushes the given command on the currently loading page
     * if conditions apply also flushesd the command queue
     * if forceFlush=true is specificied the command buffer will be flushed.
     * even if conditions are not met.
     */
    void PushJSCommand(const RefPtr<JsCommand>& jsCommand, bool forceFlush = false) const;
    static void PushJSCommand(JSContext* ctx, const RefPtr<JsCommand>& jsCommand, bool forceFlush = false);

    void PluginErrorCallback(int32_t callbackId, int32_t errorCode, std::string&& errorMessage)
    {
        auto dispatcher = dispatcher_.Upgrade();
        if (dispatcher) {
            dispatcher->DispatchPluginError(callbackId, errorCode, std::move(errorMessage));
        }
    }

    void ChangeLocale(const std::string& language, const std::string& countryOrRegion)
    {
        if (frontendDelegate_) {
            frontendDelegate_->ChangeLocale(language, countryOrRegion);
        }
    }

    void RunGarbageCollection();

private:
    void output_object_code(JSContext* ctx, int fho, JSValueConst obj);
    JSValue eval_binary_buf(JSContext* ctx, const uint8_t* buf, size_t buf_len);

    JSRuntime* runtime_ = nullptr;
    JSContext* context_ = nullptr;
    RefPtr<FrontendDelegate> frontendDelegate_;

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
    QuickJSNativeEngine* nativeEngine_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(QJSDeclarativeEngineInstance);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_QJS_DECLARATIVE_ENGINE_H
