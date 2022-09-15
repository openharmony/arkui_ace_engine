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

#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_declarative_engine.h"

#include <cstdlib>

#include "native_engine/impl/quickjs/quickjs_native_engine.h"

#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "core/common/ace_view.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/modules/qjs_module_manager.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_helpers.h"
#include "frameworks/bridge/declarative_frontend/frontend_delegate_declarative.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/bridge/js_frontend/engine/common/js_constants.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

namespace OHOS::Ace::Framework {

QJSDeclarativeEngine::~QJSDeclarativeEngine()
{
    if (nativeEngine_ != nullptr) {
#if !defined(PREVIEW)
        nativeEngine_->CancelCheckUVLoop();
#endif
        nativeEngine_->DeleteEngine();
        delete nativeEngine_;
    }
    if (engineInstance_ && engineInstance_->GetQJSRuntime()) {
        JS_RunGC(engineInstance_->GetQJSRuntime());
    }
}

bool QJSDeclarativeEngine::Initialize(const RefPtr<FrontendDelegate>& delegate)
{
    LOGI("QJSDeclarativeEngine initialize");
    JSRuntime* runtime = nullptr;
    JSContext* context = nullptr;

    // put JS_NewContext as early as possible to make stack_top in context
    // closer to the top stack frame pointer of JS thread.
    runtime = JS_NewRuntime();
    if (runtime != nullptr) {
        context = JS_NewContext(runtime);
    }

    engineInstance_ = AceType::MakeRefPtr<QJSDeclarativeEngineInstance>(delegate, instanceId_);
    nativeEngine_ = new QuickJSNativeEngine(runtime, context, static_cast<void*>(this));
    engineInstance_->SetNativeEngine(nativeEngine_);
    bool res = engineInstance_->InitJSEnv(runtime, context, GetExtraNativeObject());
    if (!res) {
        LOGE("QJSDeclarativeEngine initialize failed: %{public}d", instanceId_);
        return false;
    }
    SetPostTask(nativeEngine_);
#if !defined(PREVIEW)
    nativeEngine_->CheckUVLoop();
#endif
    if (delegate && delegate->GetAssetManager()) {
        std::string packagePath = delegate->GetAssetManager()->GetLibPath();
        if (!packagePath.empty()) {
            auto qjsNativeEngine = static_cast<QuickJSNativeEngine*>(nativeEngine_);
            qjsNativeEngine->SetPackagePath(packagePath);
        }
    }
    RegisterWorker();

    return true;
}

void QJSDeclarativeEngine::SetPostTask(NativeEngine* nativeEngine)
{
    LOGI("SetPostTask");
    auto weakDelegate = AceType::WeakClaim(AceType::RawPtr(engineInstance_->GetDelegate()));
    auto&& postTask = [weakDelegate, nativeEngine = nativeEngine_, id = instanceId_](bool needSync) {
        auto delegate = weakDelegate.Upgrade();
        if (delegate == nullptr) {
            LOGE("delegate is nullptr");
            return;
        }
        delegate->PostJsTask([nativeEngine, needSync, id]() {
            ContainerScope scope(id);
            if (nativeEngine == nullptr) {
                return;
            }
            nativeEngine->Loop(LOOP_NOWAIT, needSync);
        });
    };
    nativeEngine_->SetPostTask(postTask);
}

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
    nativeEngine_->SetInitWorkerFunc(initWorkerFunc);
}

void QJSDeclarativeEngine::RegisterAssetFunc()
{
    auto weakDelegate = AceType::WeakClaim(AceType::RawPtr(engineInstance_->GetDelegate()));
    auto&& assetFunc = [weakDelegate](const std::string& uri, std::vector<uint8_t>& content, std::string& ami) {
        LOGI("WorkerCore RegisterAssetFunc called");
        auto delegate = weakDelegate.Upgrade();
        if (delegate == nullptr) {
            LOGE("delegate is nullptr");
            return;
        }
        delegate->GetResourceData(uri, content, ami);
    };
    nativeEngine_->SetGetAssetFunc(assetFunc);
}

void QJSDeclarativeEngine::RegisterWorker()
{
    RegisterInitWorkerFunc();
    RegisterAssetFunc();
}

void QJSDeclarativeEngine::LoadJs(const std::string& url, const RefPtr<JsAcePage>& page, bool isMainPage)
{
    LOGD("QJSDeclarativeEngine LoadJs");
    ACE_SCOPED_TRACE("QJSDeclarativeEngine::LoadJS");
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetRunningPage(page);
    JSContext* ctx = engineInstance_->GetQJSContext();
    JS_SetContextOpaque(ctx, reinterpret_cast<void*>(AceType::RawPtr(engineInstance_)));
    if (isMainPage) {
        std::string commonsJsContent;
        if (engineInstance_->GetDelegate()->GetAssetContent("commons.js", commonsJsContent)) {
            auto commonsJsResult = QJSDeclarativeEngineInstance::EvalBuf(
                ctx, commonsJsContent.c_str(), commonsJsContent.length(), "commons.js", JS_EVAL_TYPE_GLOBAL);
            if (commonsJsResult == -1) {
                LOGE("fail to execute load commonsjs script");
                return;
            }
        }
        std::string vendorsJsContent;
        if (engineInstance_->GetDelegate()->GetAssetContent("vendors.js", vendorsJsContent)) {
            auto vendorsJsResult = QJSDeclarativeEngineInstance::EvalBuf(
                ctx, vendorsJsContent.c_str(), vendorsJsContent.length(), "vendors.js", JS_EVAL_TYPE_GLOBAL);
            if (vendorsJsResult == -1) {
                LOGE("fail to execute load vendorsjs script");
                return;
            }
        }
        std::string appjsContent;
        if (!engineInstance_->GetDelegate()->GetAssetContent("app.js", appjsContent)) {
            LOGE("js file load failed!");
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
        } else {
            CallAppFunc("onCreate", 0, nullptr);
        }
    }

    std::string pageMap;
    if (engineInstance_->GetDelegate()->GetAssetContent(url + ".map", pageMap)) {
        page->SetPageMap(pageMap);
    } else {
        LOGI("the source map of page load failed!");
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

    JSValue compiled = engineInstance_->CompileSource(GetInstanceName(), url, jsContent.c_str(), jsContent.size());
    if (JS_IsException(compiled)) {
        LOGE("js compilation failed url=[%{public}s]", url.c_str());
        QJSUtils::JsStdDumpErrorAce(
            ctx, JsErrorType::LOAD_JS_BUNDLE_ERROR, instanceId_, page->GetUrl().c_str(), page, true);
        return;
    }
    engineInstance_->ExecuteDocumentJS(compiled);
    js_std_loop(engineInstance_->GetQJSContext());
}

bool QJSDeclarativeEngine::LoadPageSource(const std::string& url)
{
    LOGI("QJSDeclarativeEngine LoadPageSource");
    ACE_SCOPED_TRACE("QJSDeclarativeEngine::LoadJS");
    ACE_DCHECK(engineInstance_);
    JSContext* ctx = engineInstance_->GetQJSContext();
    JS_SetContextOpaque(ctx, reinterpret_cast<void*>(AceType::RawPtr(engineInstance_)));

    std::string jsContent;
    if (!engineInstance_->GetDelegate()->GetAssetContent(url, jsContent)) {
        LOGE("js file load failed!");
        return false;
    }

    if (jsContent.empty()) {
        LOGE("js file load failed! url=[%{public}s]", url.c_str());
        return false;
    }

    JSValue compiled = engineInstance_->CompileSource(GetInstanceName(), url, jsContent.c_str(), jsContent.size());
    if (JS_IsException(compiled)) {
        LOGE("js compilation failed url=[%{public}s]", url.c_str());
        return false;
    }
    engineInstance_->ExecuteDocumentJS(compiled);
    js_std_loop(engineInstance_->GetQJSContext());
    return true;
}

bool QJSDeclarativeEngine::LoadFaAppSource()
{
    LOGI("QJSDeclarativeEngine LoadFaAppSource");
    ACE_SCOPED_TRACE("QJSDeclarativeEngine::LoadJS");
    ACE_DCHECK(engineInstance_);
    JSContext* ctx = engineInstance_->GetQJSContext();
    std::string commonsJsContent;
    if (engineInstance_->GetDelegate()->GetAssetContent("commons.js", commonsJsContent)) {
        auto commonsJsResult = QJSDeclarativeEngineInstance::EvalBuf(
            ctx, commonsJsContent.c_str(), commonsJsContent.length(), "commons.js", JS_EVAL_TYPE_GLOBAL);
        if (commonsJsResult == -1) {
            LOGE("fail to execute load commonsjs script");
            return false;
        }
    }
    std::string vendorsJsContent;
    if (engineInstance_->GetDelegate()->GetAssetContent("vendors.js", vendorsJsContent)) {
        auto vendorsJsResult = QJSDeclarativeEngineInstance::EvalBuf(
            ctx, vendorsJsContent.c_str(), vendorsJsContent.length(), "vendors.js", JS_EVAL_TYPE_GLOBAL);
        if (vendorsJsResult == -1) {
            LOGE("fail to execute load vendorsjs script");
            return false;
        }
    }
    std::string appjsContent;
    if (!engineInstance_->GetDelegate()->GetAssetContent("app.js", appjsContent)) {
        LOGE("js file load failed!");
    }

    auto result = QJSDeclarativeEngineInstance::EvalBuf(
        ctx, appjsContent.c_str(), appjsContent.length(), "app.js", JS_EVAL_TYPE_GLOBAL);
    if (result == -1) {
        LOGE("failed to execute Loadjs script");
    } else {
        CallAppFunc("onCreate", 0, nullptr);
    }
    return true;
}

#if defined(PREVIEW)
void QJSDeclarativeEngine::ReplaceJSContent(const std::string& url, const std::string componentName)
{
    auto* instance = static_cast<QJSDeclarativeEngineInstance*>(JS_GetContextOpaque(engineInstance_->GetQJSContext()));
    if (instance == nullptr) {
        LOGE("Can not cast Context to QJSDeclarativeEngineInstance object.");
        return;
    }
    instance->SetPreviewFlag(true);
    instance->SetRequiredComponent(componentName);

    instance->GetDelegate()->Replace(url, "");
}
#endif
RefPtr<Component> QJSDeclarativeEngine::GetNewComponentWithJsCode(const std::string& jsCode)
{
#ifdef NG_BUILD
    return nullptr;
#else
    ViewStackProcessor::GetInstance()->ClearStack();
    bool result = engineInstance_->InitAceModules(jsCode.c_str(), jsCode.length(), "AddComponent");
    if (!result) {
        LOGE("execute addComponent failed,script=[%{public}s]", jsCode.c_str());
        return nullptr;
    }
    auto component = ViewStackProcessor::GetInstance()->GetNewComponent();
    return component;
#endif
}

void QJSDeclarativeEngine::UpdateRunningPage(const RefPtr<JsAcePage>& page)
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetRunningPage(page);
    js_std_loop(engineInstance_->GetQJSContext());
}

void QJSDeclarativeEngine::UpdateStagingPage(const RefPtr<JsAcePage>& page)
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetStagingPage(page);
    js_std_loop(engineInstance_->GetQJSContext());
}

void QJSDeclarativeEngine::ResetStagingPage()
{
    ACE_DCHECK(engineInstance_);
    auto runningPage = engineInstance_->GetRunningPage();
    engineInstance_->ResetStagingPage(runningPage);
    js_std_loop(engineInstance_->GetQJSContext());
}

void QJSDeclarativeEngine::DestroyPageInstance(int32_t pageId)
{
    LOGE("Not implemented!");
    js_std_loop(engineInstance_->GetQJSContext());
}

void QJSDeclarativeEngine::CallAppFunc(const std::string& appFuncName, int argc, JSValueConst* argv)
{
    JSContext* ctx = engineInstance_->GetQJSContext();
    if (!ctx) {
        LOGE("context is null");
        return;
    }
    JSValue ret = JS_NULL;
    CallAppFunc(appFuncName, argc, argv, ret);
    js_std_loop(ctx);
    JS_FreeValue(ctx, ret);
}

void QJSDeclarativeEngine::CallAppFunc(const std::string& appFuncName, int argc, JSValueConst* argv, JSValue& ret)
{
    JSContext* ctx = engineInstance_->GetQJSContext();
    if (!ctx) {
        LOGE("context is null");
        return;
    }
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSValue exportobj = JS_GetPropertyStr(ctx, globalObj, "exports");
    JSValue defaultobj = JS_GetPropertyStr(ctx, exportobj, "default");

    JSValue appFunc = JS_GetPropertyStr(ctx, defaultobj, appFuncName.c_str());
    if (!JS_IsFunction(ctx, appFunc)) {
        LOGE("cannot find %s function", appFuncName.c_str());
        return;
    }
    ret = JS_Call(ctx, appFunc, defaultobj, argc, argv);
    js_std_loop(ctx);
    JS_FreeValue(ctx, appFunc);
    JS_FreeValue(ctx, defaultobj);
    JS_FreeValue(ctx, exportobj);
    JS_FreeValue(ctx, globalObj);
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

    JSValueConst callBackResult[] = { JS_NewBool(ctx, isShownInMultiWindow),
        JS_ParseJSON(ctx, data.c_str(), data.length(), "") };
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
    JSValue ret = JS_NULL;
    CallAppFunc("onStartContinuation", 0, nullptr, ret);
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
    JSValue ret = JS_NULL;
    CallAppFunc("onSaveData", 1, callBackResult, ret);
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
    JSValue ret = JS_NULL;
    CallAppFunc("onRestoreData", 1, callBackResult, ret);
    std::string result = JS_ToCString(ctx, ret);
    js_std_loop(engineInstance_->GetQJSContext());
    return (result == "true");
}

void QJSDeclarativeEngine::TimerCallback(const std::string& callbackId, const std::string& delay, bool isInterval)
{
    // string with function source
    LOGD("CallbackId %s", callbackId.c_str());
    JSContext* ctx = engineInstance_->GetQJSContext();
    QJSContext::Scope scp(ctx);

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
    js_std_loop(engineInstance_->GetQJSContext());
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
        JS_Call(ctx, jsFunc, JS_UNDEFINED, 0, nullptr);
    } else {
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

void QJSDeclarativeEngine::FireExternalEvent(
    const std::string& componentId, const uint32_t nodeId, const bool isDestroy)
{
#ifndef NG_BUILD
#ifdef XCOMPONENT_SUPPORTED
    if (isDestroy) {
        XComponentClient::GetInstance().DeleteFromXcomponentsMapById(componentId);
        XComponentClient::GetInstance().DeleteControllerFromJSXComponentControllersMap(componentId);
        XComponentClient::GetInstance().DeleteFromNativeXcomponentsMapById(componentId);
        XComponentClient::GetInstance().DeleteFromJsValMapById(componentId);
        return;
    }
    std::tie(nativeXComponentImpl_, nativeXComponent_) =
        XComponentClient::GetInstance().GetNativeXComponentFromXcomponentsMap(componentId);

    RefPtr<XComponentComponent> xcomponent =
        XComponentClient::GetInstance().GetXComponentFromXcomponentsMap(componentId);
    if (!xcomponent) {
        LOGE("FireExternalEvent xcomponent is null.");
        return;
    }

    void* nativeWindow = nullptr;
#ifdef OHOS_STANDARD_SYSTEM
    nativeWindow = const_cast<void*>(xcomponent->GetNativeWindow());
#else
    auto container = Container::Current();
    if (!container) {
        LOGE("FireExternalEvent Current container null");
        return;
    }
    auto nativeView = static_cast<AceView*>(container->GetView());
    if (!nativeView) {
        LOGE("FireExternalEvent nativeView null");
        return;
    }
    auto textureId = static_cast<uint64_t>(xcomponent->GetTextureId());
    LOGE("Kee FireExternalEvent textureId = %{public}d", (int)textureId);
    nativeWindow = const_cast<void*>(nativeView->GetNativeWindowById(textureId));
#endif

    if (!nativeWindow) {
        LOGE("FireExternalEvent nativeWindow invalid");
        return;
    }
    nativeXComponentImpl_->SetSurface(nativeWindow);
    nativeXComponentImpl_->SetXComponentId(xcomponent->GetId());

    auto nativeEngine = static_cast<QuickJSNativeEngine*>(nativeEngine_);
    if (nativeEngine == nullptr) {
        LOGE("nativeEngine is null");
        return;
    }

    std::string args;
    auto renderContext = nativeEngine->LoadModuleByName(
        xcomponent->GetLibraryName(), true, args, OH_NATIVE_XCOMPONENT_OBJ, reinterpret_cast<void*>(nativeXComponent_));

    JSRef<JSObject> obj = JSRef<JSObject>::Make(renderContext);
    XComponentClient::GetInstance().AddJsValToJsValMap(componentId, obj);

    auto task = [weak = WeakClaim(this), xcomponent]() {
        auto pool = xcomponent->GetTaskPool();
        if (!pool) {
            return;
        }
        auto bridge = weak.Upgrade();
        if (bridge) {
            pool->NativeXComponentInit(
                bridge->nativeXComponent_, AceType::WeakClaim(AceType::RawPtr(bridge->nativeXComponentImpl_)));
        }
    };

    auto delegate = engineInstance_->GetDelegate();
    if (!delegate) {
        LOGE("Delegate is null");
        return;
    }
    delegate->PostSyncTaskToPage(task);
#endif
#endif
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
