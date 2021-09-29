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

#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_declarative_engine.h"

#include <cstdlib>

#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM) and defined(ENABLE_WORKER)
#include "worker_init.h"
#endif

#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/modules/qjs_module_manager.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_helpers.h"
#include "frameworks/bridge/js_frontend/engine/common/js_constants.h"

namespace OHOS::Ace::Framework {

QJSDeclarativeEngine::~QJSDeclarativeEngine()
{
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
    if (nativeEngine_ != nullptr) {
        nativeEngine_->CancelCheckUVLoop();
        delete nativeEngine_;
    }
#endif
    if (engineInstance_ && engineInstance_->GetQJSRuntime()) {
        JS_RunGC(engineInstance_->GetQJSRuntime());
    }
}

bool QJSDeclarativeEngine::Initialize(const RefPtr<FrontendDelegate>& delegate)
{
    LOGD("QJSDeclarativeEngine initialize");
    JSRuntime* runtime = nullptr;
    JSContext* context = nullptr;

    // put JS_NewContext as early as possible to make stack_top in context
    // closer to the top stack frame pointer of JS thread.
    runtime = JS_NewRuntime();
    if (runtime != nullptr) {
        context = JS_NewContext(runtime);
    }

    engineInstance_ = AceType::MakeRefPtr<QJSDeclarativeEngineInstance>(delegate);
    nativeEngine_ = new QuickJSNativeEngine(runtime, context, static_cast<void*>(this));
    bool res = engineInstance_->InitJSEnv(runtime, context);
    if (!res) {
        LOGE("QJSDeclarativeEngine initialize failed: %{public}d", instanceId_);
        return false;
    }

    SetPostTask(nativeEngine_);
    nativeEngine_->CheckUVLoop();

#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM) and defined(ENABLE_WORKER)
    RegisterWorker();
#endif
    return true;
}

void QJSDeclarativeEngine::SetPostTask(NativeEngine* nativeEngine)
{
    LOGI("SetPostTask");
    auto weakDelegate = AceType::WeakClaim(AceType::RawPtr(engineInstance_->GetDelegate()));
    auto&& postTask = [weakDelegate, nativeEngine = nativeEngine_](bool needSync) {
        auto delegate = weakDelegate.Upgrade();
        if (delegate == nullptr) {
            LOGE("delegate is nullptr");
            return;
        }
        delegate->PostJsTask([nativeEngine, needSync]() {
            nativeEngine->Loop(LOOP_NOWAIT, needSync);
        });
    };
    nativeEngine_->SetPostTask(postTask);
}

#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM) and defined(ENABLE_WORKER)
void QJSDeclarativeEngine::RegisterInitWorkerFunc()
{
    auto&& initWorkerFunc = [](NativeEngine* nativeEngine) {
        LOGI("WorkerCore RegisterInitWorkerFunc called");
        if (nativeEngine == nullptr) {
            LOGE("nativeEngine is nullptr");
            return;
        }
        auto qjsNativeEngine = static_cast<QuickJSNativeEngine*>(nativeEngine);
        if (qjsNativeEngine == nullptr) {
            LOGE("qjsNativeEngine is nullptr");
            return;
        }

        JSContext* ctx = qjsNativeEngine->GetContext();
        if (ctx == nullptr) {
            LOGE("ctx is nullptr");
            return;
        }
        // Note: default 256KB is not enough
        JS_SetMaxStackSize(ctx, MAX_STACK_SIZE);

        InitConsole(ctx);
    };
    OHOS::CCRuntime::Worker::WorkerCore::RegisterInitWorkerFunc(initWorkerFunc);
}

void QJSDeclarativeEngine::RegisterAssetFunc()
{
    auto weakDelegate = AceType::WeakClaim(AceType::RawPtr(engineInstance_->GetDelegate()));
    auto&& assetFunc = [weakDelegate](const std::string& uri, std::vector<uint8_t>& content) {
        LOGI("WorkerCore RegisterAssetFunc called");
        auto delegate = weakDelegate.Upgrade();
        if (delegate == nullptr) {
            LOGE("delegate is nullptr");
            return;
        }
        delegate->GetResourceData(uri, content);
    };
    OHOS::CCRuntime::Worker::WorkerCore::RegisterAssetFunc(assetFunc);
}

void QJSDeclarativeEngine::RegisterWorker()
{
    RegisterInitWorkerFunc();
    RegisterAssetFunc();
}
#endif

void QJSDeclarativeEngine::LoadJs(const std::string& url, const RefPtr<JsAcePage>& page, bool isMainPage)
{
    LOGD("QJSDeclarativeEngine LoadJs");
    ACE_SCOPED_TRACE("QJSDeclarativeEngine::LoadJS");
    ACE_DCHECK(engineInstance_);

    engineInstance_->SetRunningPage(page);
    JSContext* ctx = engineInstance_->GetQJSContext();
    JS_SetContextOpaque(ctx, reinterpret_cast<void*>(AceType::RawPtr(engineInstance_)));

    if (isMainPage) {
        std::string appjsContent;
        if (!engineInstance_->GetDelegate()->GetAssetContent("app.js", appjsContent)) {
            LOGE("js file load failed!");
            return;
        }
        std::string appMap;
        if (engineInstance_->GetDelegate()->GetAssetContent("app.js.map", appMap)) {
            page->SetAppMap(appMap);
        } else {
            LOGI("app map is missing!");
        }
        auto result = QJSDeclarativeEngineInstance::EvalBuf(
            ctx, appjsContent.c_str(), appjsContent.length(), "app.js", JS_EVAL_TYPE_GLOBAL);
        if (result == -1) {
            LOGE("failed to execute Loadjs script");
            return;
        }
        CallAppFunc("onCreate", 0, nullptr);
    }

    std::string jsContent;
    if (!engineInstance_->GetDelegate()->GetAssetContent(url, jsContent)) {
        LOGE("js file load failed!");
        return;
    }

    if (jsContent.empty()) {
        LOGE("js file load failed! url=[%{public}s]", url.c_str());
        return;
    }

    JSValue compiled = engineInstance_->CompileSource(url, jsContent.c_str(), jsContent.size());
    if (JS_IsException(compiled)) {
        LOGE("js compilation failed url=[%{public}s]", url.c_str());
        return;
    }

    // Todo: check the fail.
    engineInstance_->ExecuteDocumentJS(compiled);

    js_std_loop(engineInstance_->GetQJSContext());
}

void QJSDeclarativeEngine::UpdateRunningPage(const RefPtr<JsAcePage>& page)
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetRunningPage(page);
}

void QJSDeclarativeEngine::UpdateStagingPage(const RefPtr<JsAcePage>& page)
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetStagingPage(page);
}

void QJSDeclarativeEngine::ResetStagingPage()
{
    ACE_DCHECK(engineInstance_);
    auto runningPage = engineInstance_->GetRunningPage();
    engineInstance_->ResetStagingPage(runningPage);
}

void QJSDeclarativeEngine::DestroyPageInstance(int32_t pageId)
{
    LOGE("Not implemented!");
}

JSValue QJSDeclarativeEngine::CallAppFunc(std::string appFuncName, int argc, JSValueConst* argv)
{
    JSContext* ctx = engineInstance_->GetQJSContext();
    if (!ctx) {
        LOGE("context is null");
        return JS_UNDEFINED;
    }
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSValue exportobj = JS_GetPropertyStr(ctx, globalObj, "exports");
    JSValue defaultobj = JS_GetPropertyStr(ctx, exportobj, "default");

    JSValue appFunc = JS_GetPropertyStr(ctx, defaultobj, appFuncName.c_str());
    if (!JS_IsFunction(ctx, appFunc)) {
        LOGE("cannot find %s function", appFuncName.c_str());
        return JS_UNDEFINED;
    }
    JSValue ret = JS_Call(ctx, appFunc, defaultobj, argc, argv);
    js_std_loop(ctx);
    JS_FreeValue(ctx, appFunc);
    JS_FreeValue(ctx, defaultobj);
    JS_FreeValue(ctx, exportobj);
    JS_FreeValue(ctx, globalObj);
    return ret;
}

void QJSDeclarativeEngine::DestroyApplication(const std::string& packageName)
{
    LOGI("Enter DestroyApplication: destroy, packageName %{public}s", packageName.c_str());
    CallAppFunc("onDestroy", 0, nullptr);
    js_std_loop(engineInstance_->GetQJSContext());
}

void QJSDeclarativeEngine::UpdateApplicationState(const std::string& packageName, Frontend::State state)
{
    LOGD("Enter UpdateApplicationState: destroy, packageName %{public}s", packageName.c_str());

    if (state == Frontend::State::ON_SHOW) {
        CallAppFunc("onShow", 0, nullptr);
    } else if (state == Frontend::State::ON_HIDE) {
        CallAppFunc("onHide", 0, nullptr);
    }

    js_std_loop(engineInstance_->GetQJSContext());
}

void QJSDeclarativeEngine::OnWindowDisplayModeChanged(bool isShownInMultiWindow, const std::string& data)
{
    JSContext* ctx = engineInstance_->GetQJSContext();
    if (!ctx) {
        LOGE("context is null");
        return;
    }

    JSValueConst callBackResult[] = {
        callBackResult[0] = JS_NewBool(ctx, isShownInMultiWindow),
        callBackResult[1] = JS_ParseJSON(ctx, data.c_str(), data.length(), "")
    };
    CallAppFunc("onWindowDisplayModeChanged", 2, callBackResult);

    js_std_loop(engineInstance_->GetQJSContext());
}

void QJSDeclarativeEngine::OnConfigurationUpdated(const std::string& data)
{
    JSContext* ctx = engineInstance_->GetQJSContext();
    if (!ctx) {
        LOGE("context is null");
        return;
    }

    JSValueConst callBackResult[] = { JS_ParseJSON(ctx, data.c_str(), data.length(), "") };
    CallAppFunc("onConfigurationUpdated", 1, callBackResult);

    js_std_loop(engineInstance_->GetQJSContext());
}

bool QJSDeclarativeEngine::OnStartContinuation()
{
    JSContext* ctx = engineInstance_->GetQJSContext();
    if (!ctx) {
        LOGE("context is null");
        return false;
    }
    JSValue ret = CallAppFunc("onStartContinuation", 0, nullptr);
    std::string result = JS_ToCString(ctx, ret);
    js_std_loop(engineInstance_->GetQJSContext());
    return (result == "true");
}

void QJSDeclarativeEngine::OnCompleteContinuation(int32_t code)
{
    JSContext* ctx = engineInstance_->GetQJSContext();
    if (!ctx) {
        LOGE("context is null");
        return;
    }
    JSValueConst callBackResult[] = { JS_NewInt32(ctx, code) };
    CallAppFunc("onCompleteContinuation", 1, callBackResult);
    js_std_loop(engineInstance_->GetQJSContext());
}

void QJSDeclarativeEngine::OnRemoteTerminated()
{
    JSContext* ctx = engineInstance_->GetQJSContext();
    if (!ctx) {
        LOGE("context is null");
        return;
    }
    CallAppFunc("onRemoteTerminated", 0, nullptr);
    js_std_loop(engineInstance_->GetQJSContext());
}

void QJSDeclarativeEngine::OnSaveData(std::string& data)
{
    JSContext* ctx = engineInstance_->GetQJSContext();
    if (!ctx) {
        LOGE("context is null");
        return;
    }
    JSValue object = JS_NewObject(ctx);
    JSValueConst callBackResult[] = { object };
    JSValue ret = CallAppFunc("onSaveData", 1, callBackResult);
    if (JS_ToCString(ctx, ret) == std::string("true")) {
        data = ScopedString::Stringify(ctx, object);
    }
    js_std_loop(engineInstance_->GetQJSContext());
}

bool QJSDeclarativeEngine::OnRestoreData(const std::string& data)
{
    JSContext* ctx = engineInstance_->GetQJSContext();
    if (!ctx) {
        LOGE("context is null");
        return false;
    }
    JSValue jsonObj = JS_ParseJSON(ctx, data.c_str(), data.length(), "");
    if (JS_IsUndefined(jsonObj) || JS_IsException(jsonObj)) {
        LOGE("Parse json for restore data failed.");
        return false;
    }
    JSValueConst callBackResult[] = { jsonObj };
    JSValue ret = CallAppFunc("onRestoreData", 1, callBackResult);
    std::string result = JS_ToCString(ctx, ret);
    js_std_loop(engineInstance_->GetQJSContext());
    return (result == "true");
}

void QJSDeclarativeEngine::TimerCallback(const std::string& callbackId, const std::string& delay, bool isInterval)
{
    // string with function source
    LOGD("CallbackId %s", callbackId.c_str());

    if (isInterval) {
        TimerCallJs(callbackId, isInterval);
        engineInstance_->GetDelegate()->WaitTimer(callbackId, delay, isInterval, false);
    } else {
        TimerCallJs(callbackId, isInterval);
        JSContext* ctx = engineInstance_->GetQJSContext();
        if (!ctx) {
            LOGE("TimerCallback no context");
            return;
        }
        ModuleManager::GetInstance()->RemoveCallbackFunc(ctx, std::stoi(callbackId), isInterval);
        engineInstance_->GetDelegate()->ClearTimer(callbackId);
    }
}

void QJSDeclarativeEngine::TimerCallJs(const std::string& callbackId, bool isInterval)
{
    JSContext* ctx = engineInstance_->GetQJSContext();
    if (!ctx) {
        LOGE("TimerCallJs no context");
        return;
    }

    JSValue jsFunc = ModuleManager::GetInstance()->GetCallbackFunc(std::stoi(callbackId), isInterval);
    if (!JS_IsFunction(ctx, jsFunc)) {
        LOGE("TimerCallJs is not func");
        return;
    }
    std::vector<JSValue> jsargv = ModuleManager::GetInstance()->GetCallbackArray(std::stoi(callbackId), isInterval);
    if (jsargv.empty()) {
        LOGI("jsargv is empty");
        JS_Call(ctx, jsFunc, JS_UNDEFINED, 0, nullptr);
    } else {
        LOGI("jsargv's size is %{private}zu", jsargv.size());
        JSValue* argv = new JSValue[jsargv.size()];
        uint32_t index = 0;
        while (index < jsargv.size()) {
            argv[index] = jsargv[index];
            ++index;
        }
        JS_Call(ctx, jsFunc, JS_UNDEFINED, jsargv.size(), argv);
    }
    js_std_loop(ctx);
}

void QJSDeclarativeEngine::MediaQueryCallback(const std::string& callbackId, const std::string& args)
{
    JsEngine::MediaQueryCallback(callbackId, args);
}

void QJSDeclarativeEngine::RequestAnimationCallback(const std::string& callbackId, uint64_t timeStamp)
{
    LOGD("Enter RequestAnimationCallback");
}

void QJSDeclarativeEngine::JsCallback(const std::string& callbackId, const std::string& args)
{
    LOGD("Enter JSCallback");
}

void QJSDeclarativeEngine::FireAsyncEvent(const std::string& eventId, const std::string& param)
{
    LOGW("QJSDeclarativeEngine FireAsyncEvent is unusable");
}

void QJSDeclarativeEngine::FireSyncEvent(const std::string& eventId, const std::string& param)
{
    LOGW("QJSDeclarativeEngine FireSyncEvent is unusable");
}

void QJSDeclarativeEngine::FireExternalEvent(const std::string& componentId, const uint32_t nodeId)
{

}

void QJSDeclarativeEngine::SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher)
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetJsMessageDispatcher(dispatcher);
}

void QJSDeclarativeEngine::RunGarbageCollection()
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->RunGarbageCollection();
}

RefPtr<GroupJsBridge> QJSDeclarativeEngine::GetGroupJsBridge()
{
    return AceType::MakeRefPtr<QuickJsGroupJsBridge>();
}

} // namespace OHOS::Ace::Framework
