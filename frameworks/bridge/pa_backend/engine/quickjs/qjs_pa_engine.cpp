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

#include "frameworks/bridge/pa_backend/engine/quickjs/qjs_pa_engine.h"

#include <algorithm>
#include <string>
#include <unistd.h>
#include <unordered_map>

#include "third_party/quickjs/message_server.h"

#include "base/i18n/localization.h"
#include "base/json/json_util.h"
#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/linear_map.h"
#include "base/utils/system_properties.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/common/backend.h"
#include "core/event/ace_event_helper.h"
#include "core/event/back_end_event_manager.h"
#include "frameworks/bridge/common/dom/dom_type.h"
#include "frameworks/bridge/common/media_query/media_query_info.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/js_frontend/engine/common/js_constants.h"
#include "frameworks/bridge/js_frontend/engine/common/runtime_constants.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

namespace OHOS::Ace::Framework {
namespace {
#define JS_CFUNC_DEF_CPP(name, length, func)                            \
    {                                                                   \
        name, JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE, JS_DEF_CFUNC, 0, \
        {                                                               \
            {                                                           \
                length, JS_CFUNC_generic,                               \
                {                                                       \
                    func                                                \
                }                                                       \
            }                                                           \
        }                                                               \
    }

JSValue JsOnCreateFinish(JSContext *ctx, JSValueConst value, int32_t argc, JSValueConst *argv)
{
    LOGD("JsOnCreateFinish");
    return JS_NULL;
}

const JSCFunctionListEntry JS_PA_FUNCS[] = {
    JS_CFUNC_DEF_CPP("onCreateFinish", 0, JsOnCreateFinish),
};

JSValue AppLogPrint(JSContext *ctx, JsLogLevel level, JSValueConst value, int32_t argc, JSValueConst *argv)
{
    ACE_SCOPED_TRACE("AppLogPrint(level=%d)", static_cast<int32_t>(level));

    if ((argv == nullptr) || (argc == 0)) {
        LOGE("the arg is error");
        return JS_EXCEPTION;
    }
    ScopedString printLog(ctx, argv[0]);

    switch (level) {
        case JsLogLevel::DEBUG:
            APP_LOGD("app Log: %{public}s", printLog.get());
            break;
        case JsLogLevel::INFO:
            APP_LOGI("app Log: %{public}s", printLog.get());
            break;
        case JsLogLevel::WARNING:
            APP_LOGW("app Log: %{public}s", printLog.get());
            break;
        case JsLogLevel::ERROR:
            APP_LOGE("app Log: %{public}s", printLog.get());
            break;
        default:
            break;
    }

    return JS_NULL;
}

JSValue AppLogPrint(JSContext *ctx, JSValueConst value, int32_t argc, JSValueConst *argv)
{
    return AppLogPrint(ctx, JsLogLevel::DEBUG, value, argc, argv);
}

void InitJsConsoleObject(JSContext *ctx, const JSValue &globalObj)
{
    JSValue console;
    // app log method
    console = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, console, "log", JS_NewCFunction(ctx, AppLogPrint, "log", 1));
    JS_SetPropertyStr(ctx, globalObj, "console", console);
}

int32_t JsPaInit(JSContext* ctx, JSModuleDef* moduleDef)
{
    return JS_SetModuleExportList(ctx, moduleDef, JS_PA_FUNCS, countof(JS_PA_FUNCS));
}

JSModuleDef* InitPaModules(JSContext* ctx)
{
    LOGD("QjsPaEngine: InitPaModules");
    JSModuleDef *jsModule = JS_NewCModule(ctx, "Particle", JsPaInit);
    if (jsModule == nullptr) {
        return nullptr;
    }
    JS_AddModuleExportList(ctx, jsModule, JS_PA_FUNCS, countof(JS_PA_FUNCS));
    return jsModule;
}

bool InitJsContext(JSContext* ctx, size_t maxStackSize, int32_t instanceId,
    const QjsPaEngineInstance* qjsPaEngineInstance)
{
    LOGI("QjsPaEngine: InitJsContext");
    if (ctx == nullptr) {
        LOGE("Qjs cannot allocate JS context");
        EventReport::SendJsException(JsExcepType::JS_ENGINE_INIT_ERR);
        return false;
    }

    // Note: default 256KB is not enough
    JS_SetMaxStackSize(ctx, maxStackSize);

    // Inject pa native functions module
    InitPaModules(ctx);

    JSValue globalObj, perfUtil;
    globalObj = JS_GetGlobalObject(ctx);
    perfUtil = JS_NewObject(ctx);

    InitJsConsoleObject(ctx, globalObj);

    NativeObjectInfo* nativeObjectInfo = new NativeObjectInfo();
    nativeObjectInfo->nativeObject = qjsPaEngineInstance->GetDelegate()->GetAbility();
    JSValue abilityValue = JS_NewExternal(ctx, nativeObjectInfo, [](JSContext* ctx, void *data, void *hint) {
        NativeObjectInfo *info = (NativeObjectInfo *)data;
        if (info) {
            delete info;
        }
    }, nullptr);
    JS_SetPropertyStr(ctx, globalObj, "ability", abilityValue);

    JS_FreeValue(ctx, globalObj);
    return true;
}
} // namespace
// -----------------------
// Start QjsPaEngineInstance
// -----------------------
JSValue QjsPaEngineInstance::FireJsEvent(const std::string &param)
{
    LOGI("FireJsEvent");
    JSContext *ctx = GetQjsContext();
    ACE_DCHECK(ctx);
    QJSHandleScope handleScope(ctx);
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSValue callJsFunc = QJSUtils::GetPropertyStr(ctx, globalObj, "callJS");
    if (!JS_IsFunction(ctx, callJsFunc)) {
        LOGE("cannot find 'callJS' function from global object, this should not happen!");
        JS_FreeValue(ctx, globalObj);
        return JS_UNDEFINED;
    }

    JSValueConst argv[] = {
        QJSUtils::NewString(ctx, std::to_string(0).c_str()),
        QJSUtils::ParseJSON(ctx, param.c_str(), param.size(), nullptr),
    };

    JSValue retVal = JS_Call(ctx, callJsFunc, JS_UNDEFINED, countof(argv), argv);

    JS_FreeValue(ctx, globalObj);

    // It is up to the caller to check this value. No exception checks here.
    return retVal;
}

bool QjsPaEngineInstance::InitJsEnv(JSRuntime* runtime, JSContext* context)
{
    LOGI("InitJsEnv");
    if (runtime == nullptr) {
        runtime = JS_NewRuntime();
    }
    if (runtime_ != nullptr) {
        JS_FreeRuntime(runtime_);
    }
    runtime_ = runtime;
    if (runtime_ == nullptr) {
        LOGE("Qjs cannot allocate JS runtime");
        EventReport::SendJsException(JsExcepType::JS_ENGINE_INIT_ERR);
        return false;
    }

    if (context == nullptr) {
        context = JS_NewContext(runtime_);
    }
    if (context_ != nullptr) {
        JS_FreeContext(context_);
    } 
    context_ = context;
    if (!InitJsContext(context_, MAX_STACK_SIZE, instanceId_, this)) {
        LOGE("Qjs cannot allocate JS context");
        EventReport::SendJsException(JsExcepType::JS_ENGINE_INIT_ERR);
        JS_FreeRuntime(runtime_);
        return false;
    }

    const char *str = "\n"
                      "var global = globalThis;\n"
                      "globalThis.pa = {};\n"
                      "function $app_define$(page, packageName, parseContent) {\n"
                      "    const module = {exports: {}};\n"
                      "    parseContent({}, module.exports, module);\n"
                      "    globalThis.pa = module.exports;\n"
                      "}\n"
                      "function $app_bootstrap$() {}\n";

    JSValue CppToJSRet = JS_Eval(context_, str, strlen(str), "<evalScript>", JS_EVAL_TYPE_GLOBAL);
    if (JS_IsException(CppToJSRet)) {
        LOGE("eval framework error");
    }

    JS_FreeValue(context_, CppToJSRet);

    return true;
}

QjsPaEngineInstance::~QjsPaEngineInstance()
{
    if (context_) {
        JS_FreeContext(context_);
    }
    if (runtime_) {
        JS_FreeRuntime(runtime_);
    }
}
// -----------------------
// Start QjsPaEngine
// -----------------------

bool QjsPaEngine::Initialize(const RefPtr<BackendDelegate>& delegate)
{
    ACE_SCOPED_TRACE("QjsPaEngine::Initialize");
    LOGI("Initialize");

    JSRuntime* runtime = nullptr;
    JSContext* context = nullptr;

    // put JS_NewContext as early as possible to make stack_top in context
    // closer to the top stack frame pointer of JS thread.
    runtime = JS_NewRuntime();
    if (runtime != nullptr) {
        context = JS_NewContext(runtime);
    }
    LOGD("QjsPaEngine initialize");
#ifdef ENABLE_JS_DEBUG
    LOGI("QjsPaEngine debug mode");
    std::string instanceName = GetInstanceName();
    if (instanceName.empty()) {
        LOGE("GetInstanceName fail, %s", instanceName.c_str());
        return false;
    }
    constexpr int32_t COMPONENT_NAME_MAX_LEN = 100;
    char componentName[COMPONENT_NAME_MAX_LEN];
    if (!DBG_CopyComponentNameFromAce(instanceName.c_str(), componentName, COMPONENT_NAME_MAX_LEN)) {
        LOGE("GetInstanceName strcpy_s fail");
        return false;
    }
    DBG_SetComponentName(componentName, strlen(componentName));
#endif
    nativeEngine_ = new QuickJSNativeEngine(runtime, context);
    ACE_DCHECK(delegate);
    delegate->AddTaskObserver([nativeEngine = nativeEngine_]() {
        nativeEngine->Loop(LOOP_NOWAIT);
    });

    engineInstance_ = AceType::MakeRefPtr<QjsPaEngineInstance>(delegate, instanceId_);
    return engineInstance_->InitJsEnv(runtime, context);
}

QjsPaEngine::~QjsPaEngine()
{
    engineInstance_->GetDelegate()->RemoveTaskObserver();
    if (nativeEngine_ != nullptr) {
        delete nativeEngine_;
    }
    ACE_DCHECK(engineInstance_);
    JS_RunGC(engineInstance_->GetQjsRuntime());
}

void QjsPaEngine::LoadJs(const std::string& url)
{
    LOGI("QjsPaEngine LoadJs");
    ACE_SCOPED_TRACE("QjsPaEngine::LoadJs");
    ACE_DCHECK(engineInstance_);

    JSContext* ctx = engineInstance_->GetQjsContext();

    // Create a stack-allocated handle scope.
    QJSHandleScope handleScope(ctx);

    // Memorize the context that this JSContext is working with.
    JS_SetContextOpaque(ctx, reinterpret_cast<void*>(AceType::RawPtr(engineInstance_)));

    JSValue globalObj = JS_GetGlobalObject(ctx);

    std::string jsContent;
    if (!engineInstance_->GetDelegate()->GetAssetContent(url, jsContent)) {
        LOGE("js file load failed!");
        JS_FreeValue(ctx, globalObj);
        return;
    }

    JSValue instanceId = QJSUtils::NewString(ctx, std::to_string(0).c_str());

    JSValue CppToJSRet = JS_Eval(ctx, jsContent.c_str(), jsContent.size(), url.c_str(), JS_EVAL_TYPE_GLOBAL);

    JS_FreeValue(ctx, CppToJSRet);

    // call onstart
    JSValue paObj;
    paObj = QJSUtils::GetPropertyStr(ctx, globalObj, "pa");
    if (!JS_IsObject(paObj)) {
        LOGE("get paObj error");
    }

    BackendType type = engineInstance_->GetDelegate()->GetType();
    JSValue paStartFunc = JS_NULL;
    if (type == BackendType::SERVICE) {
        paStartFunc = QJSUtils::GetPropertyStr(ctx, paObj, "onStart");
    } else if (type == BackendType::DATA) {
        paStartFunc = QJSUtils::GetPropertyStr(ctx, paObj, "onInitalized");
    } else {
        LOGE("backend type not support");
    }

    if (!JS_IsFunction(ctx, paStartFunc)) {
        LOGE("paStartFunc is not found");
        JS_FreeValue(ctx, globalObj);
        return;
    }
    JSValueConst startArgv[] = {instanceId};
    JSValue startRetVal = QJSUtils::Call(ctx, paStartFunc, JS_UNDEFINED, countof(startArgv), startArgv);
    JS_FreeValue(ctx, startRetVal);
    JS_FreeValue(ctx, globalObj);
    js_std_loop(ctx);
}

void QjsPaEngine::SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher)
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetJsMessageDispatcher(dispatcher);
}

void QjsPaEngine::FireAsyncEvent(const std::string &eventId, const std::string &param)
{
    std::string callBuf = std::string("[{\"args\": [\"")
                              .append(eventId)
                              .append("\",")
                              .append(param)
                              .append("], \"method\":\"fireEvent\"}]");
    LOGD("FireAsyncEvent string: %{private}s", callBuf.c_str());

    ACE_DCHECK(engineInstance_);
    JSValue cppToJsRet = engineInstance_->FireJsEvent(callBuf);
    if (JS_IsException(cppToJsRet)) {
        LOGE("Qjs FireAsyncEvent FAILED !! jsCall: %{private}s", callBuf.c_str());
    }
    JS_FreeValue(engineInstance_->GetQjsContext(), cppToJsRet);
}

void QjsPaEngine::FireSyncEvent(const std::string &eventId, const std::string &param)
{
    std::string callBuf = std::string("[{\"args\": [\"")
                              .append(eventId)
                              .append("\",")
                              .append(param)
                              .append("], \"method\":\"fireEventSync\"}]");
    LOGD("FireSyncEvent string: %{private}s", callBuf.c_str());

    ACE_DCHECK(engineInstance_);
    JSValue cppToJsRet = engineInstance_->FireJsEvent(callBuf.c_str());
    if (JS_IsException(cppToJsRet)) {
        LOGE("Qjs FireSyncEvent FAILED !! jsCall: %{private}s", callBuf.c_str());
    }
    JS_FreeValue(engineInstance_->GetQjsContext(), cppToJsRet);
}

void QjsPaEngine::DestroyApplication(const std::string &packageName)
{
    LOGI("DestroyApplication: destroy app instance from jsfwk");
    JSContext *ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);

    QJSHandleScope handleScope(ctx);
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSValue paObj = QJSUtils::GetPropertyStr(ctx, globalObj, "pa");
    if (!JS_IsObject(paObj)) {
        LOGE("get paObj error");
    }
    JSValue paDestroyFunc = QJSUtils::GetPropertyStr(ctx, paObj, "onStop");
    if (!JS_IsFunction(ctx, paDestroyFunc)) {
        LOGE("paDestroyFunc is not found, cannot destroy page instance!");
        JS_FreeValue(ctx, globalObj);
        return;
    }

    JSValue name = QJSUtils::NewString(ctx, packageName.c_str());
    JSValueConst argv[] = {name};
    JSValue retVal = QJSUtils::Call(ctx, paDestroyFunc, JS_UNDEFINED, countof(argv), argv);
    if (JS_IsException(retVal)) {
        LOGE("Qjs paDestroyFunc FAILED!");
    }

    JS_FreeValue(ctx, globalObj);
}
} // namespace OHOS::Ace::Framework