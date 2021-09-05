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
#include <dlfcn.h>
#include <string>
#include <unistd.h>
#include <unordered_map>

#include "napi/native_node_api.h"
#include "napi_remote_object.h"

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
FromBindingData::FromBindingData(JSContext* ctx, JSValue value)
{
    ctx_ = ctx;
    valueFromJs_ = value;
}

void FromBindingData::Constructor(const std::string& param)
{
    JSValue paFunc = QJSUtils::GetPropertyStr(ctx_, valueFromJs_, "constructor");
    if (!JS_IsFunction(ctx_, paFunc)) {
        LOGE("Constructor is not found");
        return;
    }

    JSValue jsParam = QJSUtils::NewString(ctx_, param.c_str());
    JSValueConst argv[] = {jsParam};
    JS_Call(ctx_, paFunc, JS_UNDEFINED, countof(argv), argv);

    return;
}

void FromBindingData::UpdateData(const std::string& data)
{
    JSValue paFunc = QJSUtils::GetPropertyStr(ctx_, valueFromJs_, "updateData");
    if (!JS_IsFunction(ctx_, paFunc)) {
        LOGE("UpdateData is not found");
        return;
    }

    JSValue param = QJSUtils::NewString(ctx_, data.c_str());
    JSValueConst argv[] = {param};
    JS_Call(ctx_, paFunc, JS_UNDEFINED, countof(argv), argv);

    return;
}

std::string FromBindingData::GetDataString() const
{
    JSValue paFunc = QJSUtils::GetPropertyStr(ctx_, valueFromJs_, "getDataString");
    if (!JS_IsFunction(ctx_, paFunc)) {
        LOGE("Constructor is not found");
        return "";
    }

    JSValueConst argv[] = {};
    JS_Call(ctx_, paFunc, JS_UNDEFINED, countof(argv), argv);

    return "";
}

void FromBindingData::AddImageData(const std::string& name, void* buffer)
{
    JSValue paFunc = QJSUtils::GetPropertyStr(ctx_, valueFromJs_, "addImageData");
    if (!JS_IsFunction(ctx_, paFunc)) {
        LOGE("AddImageData is not found");
        return;
    }

    JSValue param = QJSUtils::NewString(ctx_, name.c_str());
    JSValueConst argv[] = {param};
    JS_Call(ctx_, paFunc, JS_UNDEFINED, countof(argv), argv);

    return;
}

void FromBindingData::RemoveImageData(const std::string& name)
{
    JSValue paFunc = QJSUtils::GetPropertyStr(ctx_, valueFromJs_, "removeImageData");
    if (!JS_IsFunction(ctx_, paFunc)) {
        LOGE("RemoveImageData is not found");
        return;
    }

    JSValue param = QJSUtils::NewString(ctx_, name.c_str());
    JSValueConst argv[] = {param};
    JS_Call(ctx_, paFunc, JS_UNDEFINED, countof(argv), argv);

    return;
}

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
JSValue QjsPaEngineInstance::FireJsEvent(const std::string &eventId, const std::string &param)
{
    LOGI("FireJsEvent");
    JSContext *ctx = GetQjsContext();
    ACE_DCHECK(ctx);
    QJSHandleScope handleScope(ctx);
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSValue callJsFunc = QJSUtils::GetPropertyStr(ctx, globalObj, "pa");
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
    nativeEngine_ = new QuickJSNativeEngine(runtime, context, static_cast<void*>(this));
    ACE_DCHECK(delegate);
    delegate->AddTaskObserver([nativeEngine = nativeEngine_]() {
        nativeEngine->Loop(LOOP_NOWAIT);
    });

    LoadLibrary();

    engineInstance_ = AceType::MakeRefPtr<QjsPaEngineInstance>(delegate, instanceId_);
    return engineInstance_->InitJsEnv(runtime, context);
}

QjsPaEngine::~QjsPaEngine()
{
    UnloadLibrary();
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
    } else if (type == BackendType::FORM) {
        paStartFunc = QJSUtils::GetPropertyStr(ctx, paObj, "onCreate");
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
    if (type == BackendType::FORM) {
        RefPtr<FromBindingData> fromBindingData = AceType::MakeRefPtr<FromBindingData>(ctx, startRetVal);
    }
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
    JSValue cppToJsRet = engineInstance_->FireJsEvent(eventId, callBuf);
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
    JSValue cppToJsRet = engineInstance_->FireJsEvent(eventId, callBuf.c_str());
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

JSValue QjsPaEngine::GetPaFunc(const std::string& funcName)
{
    JSContext *ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);

    QJSHandleScope handleScope(ctx);
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSValue paObj = QJSUtils::GetPropertyStr(ctx, globalObj, "pa");
    if (!JS_IsObject(paObj)) {
        LOGE("get paObj error");
        return JS_UNDEFINED;
    }
    JSValue paFunc = QJSUtils::GetPropertyStr(ctx, paObj, funcName.c_str());
    if (!JS_IsFunction(ctx, paFunc)) {
        LOGE("paFunc is not found, cannot destroy page instance!");
        JS_FreeValue(ctx, globalObj);
        return JS_UNDEFINED;
    }
    LOGI("GetPaFunc: funcName: %{public}s", funcName.c_str());
    JS_FreeValue(ctx, globalObj);
    return paFunc;
}

inline int32_t GetJsInt32Val(JSContext* ctx, JSValueConst value)
{
    int32_t val = 0;
    if (JS_IsNumber(value) && (JS_ToInt32(ctx, &val, value)) < 0) {
        val = 0;
    }
    return val;
}

inline std::string GetJsStringVal(JSContext* ctx, JSValueConst value)
{
    std::string val;
    if (!JS_IsString(value)) {
        return val;
    }

    auto cstr = JS_ToCString(ctx, value);
    if (cstr == nullptr) {
        return val;
    }
    val = cstr;
    JS_FreeCString(ctx, cstr);

    return val;
}

void QjsPaEngine::LoadLibrary()
{
    const char* rdbPath = "/system/lib/module/data/librdb.z.so";
    if (strlen(rdbPath) == 0) {
        LOGE("module path is empty");
        return;
    }

    libRdb_ = dlopen(rdbPath, RTLD_LAZY);
    if (libRdb_ == nullptr) {
        LOGE("dlopen failed: %{public}s", dlerror());
    }

    rdbValueBucketNewInstance_ = reinterpret_cast<RdbValueBucketNewInstance>(
        dlsym(libRdb_, "NAPI_OHOS_Data_RdbJsKit_ValuesBucketProxy_NewInstance"));
    if (rdbValueBucketNewInstance_ == nullptr) {
        LOGE("symbol not found: %{public}s", dlerror());
    }

    rdbValueBucketGetNativeObject_ = reinterpret_cast<RdbValueBucketGetNativeObject>(
        dlsym(libRdb_, "NAPI_OHOS_Data_RdbJsKit_ValuesBucketProxy_GetNativeObject"));
    if (rdbValueBucketGetNativeObject_ == nullptr) {
        LOGE("symbol not found: %{public}s", dlerror());
    }

    rdbResultSetProxyNewInstance_ = reinterpret_cast<RdbResultSetProxyNewInstance>(
        dlsym(libRdb_, "NAPI_OHOS_Data_RdbJsKit_ResultSetProxy_NewInstance"));
    if (rdbResultSetProxyNewInstance_ == nullptr) {
        LOGE("symbol not found: %{public}s", dlerror());
    }

    rdbResultSetProxyGetNativeObject_ = reinterpret_cast<RdbResultSetProxyGetNativeObject>(
        dlsym(libRdb_, "NAPI_OHOS_Data_RdbJsKit_ResultSetProxy_GetNativeObject"));
    if (rdbResultSetProxyGetNativeObject_ == nullptr) {
        LOGE("symbol not found: %{public}s", dlerror());
    }

    const char* dataAbilityPath = "/system/lib/module/data/libdataability.z.so";
    if (strlen(dataAbilityPath) == 0) {
        LOGE("module path is empty");
        return;
    }

    libDataAbility_ = dlopen(dataAbilityPath, RTLD_LAZY);
    if (libDataAbility_ == nullptr) {
        LOGE("dlopen failed: %{public}s", dlerror());
    }

    dataAbilityPredicatesNewInstance_ = reinterpret_cast<DataAbilityPredicatesNewInstance>(
        dlsym(libDataAbility_, "NAPI_OHOS_Data_DataAbilityJsKit_DataAbilityPredicatesProxy_NewInstance"));
    if (dataAbilityPredicatesNewInstance_ == nullptr) {
        LOGE("symbol not found: %{public}s", dlerror());
    }

    dataAbilityPredicatesGetNativeObject_ = reinterpret_cast<DataAbilityPredicatesGetNativeObject>(
        dlsym(libDataAbility_, "NAPI_OHOS_Data_DataAbilityJsKit_DataAbilityPredicatesProxy_GetNativeObject"));
    if (dataAbilityPredicatesGetNativeObject_ == nullptr) {
        LOGE("symbol not found: %{public}s", dlerror());
    }
}

void QjsPaEngine::UnloadLibrary()
{
    dlclose(libRdb_);
    dlclose(libDataAbility_);
}

int32_t QjsPaEngine::Insert(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value)
{
    LOGI("Insert");
    JSContext *ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);

    QJSHandleScope handleScope(ctx);
    JSValue paFunc = GetPaFunc("insert");

    JSValue argUriJSValue = JS_NewString(ctx, uri.ToString().c_str());

    napi_env env = reinterpret_cast<napi_env>(nativeEngine_);
    napi_value argNapiValue = rdbValueBucketNewInstance_(env, const_cast<OHOS::NativeRdb::ValuesBucket&>(value));
    NativeValue* argNapiNativeValue = reinterpret_cast<NativeValue*>(argNapiValue);
    JSValue argNapiJSValue = (JSValue)*argNapiNativeValue;
    JSValueConst argv[] = { argUriJSValue, argNapiJSValue };
    JSValue retVal = QJSUtils::Call(ctx, paFunc, JS_UNDEFINED, countof(argv), argv);
    if (JS_IsException(retVal)) {
        LOGE("Qjs paFunc FAILED!");
        return 0;
    }
    return GetJsInt32Val(ctx, retVal);
}

std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet> QjsPaEngine::Query(
    const Uri& uri, const std::vector<std::string>& columns, const OHOS::NativeRdb::DataAbilityPredicates& predicates)
{
    LOGI("Query");
    std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet> resultSet = nullptr;
    JSContext *ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);

    QJSHandleScope handleScope(ctx);
    JSValue paFunc = GetPaFunc("query");

    JSValue argUriJSValue = JS_NewString(ctx, uri.ToString().c_str());

    napi_env env = reinterpret_cast<napi_env>(nativeEngine_);
    napi_value argColumnsNapiValue = nullptr;
    napi_create_array(env, &argColumnsNapiValue);
    bool isArray = false;
    if (napi_is_array(env, argColumnsNapiValue, &isArray) != napi_ok || !isArray) {
        LOGE("create array failed");
        return resultSet;
    }

    int32_t index = 0;
    for (auto column : columns) {
        napi_value result = nullptr;
        napi_create_string_utf8(env, column.c_str(), column.length(), &result);
        napi_set_element(env, argColumnsNapiValue, index++, result);
    }

    NativeValue* argColumnsNativeValue = reinterpret_cast<NativeValue*>(argColumnsNapiValue);
    JSValue argColumnsJSValue = (JSValue)*argColumnsNativeValue;

    OHOS::NativeRdb::DataAbilityPredicates* predicatesPtr = new OHOS::NativeRdb::DataAbilityPredicates();
    napi_value argPredicatesNapiValue = dataAbilityPredicatesNewInstance_(env, predicatesPtr);
    NativeValue* argPredicatesNativeValue = reinterpret_cast<NativeValue*>(argPredicatesNapiValue);
    if (argPredicatesNativeValue == nullptr) {
        LOGE("Query argPredicatesNativeValue is nullptr");
        return resultSet;
    }
    JSValue argPredicatesJSValue = (JSValue)*argPredicatesNativeValue;

    JSValueConst argv[] = { argUriJSValue, argColumnsJSValue, argPredicatesJSValue };
    JSValue retVal = QJSUtils::Call(ctx, paFunc, JS_UNDEFINED, countof(argv), argv);
    if (JS_IsException(retVal)) {
        LOGE("Qjs paFunc FAILED!");
        return resultSet;
    }

    auto nativeObject = rdbResultSetProxyGetNativeObject_(env,
        reinterpret_cast<napi_value>(QuickJSNativeEngine::JSValueToNativeValue(nativeEngine_, retVal)));
    if (nativeObject == nullptr) {
        LOGE("AbsSharedResultSet from JS to Native failed");
        return resultSet;
    }

    resultSet.reset(nativeObject);
    return resultSet;
}

int32_t QjsPaEngine::Update(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value,
    const OHOS::NativeRdb::DataAbilityPredicates& predicates)
{
    LOGI("Update");
    JSContext *ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);

    QJSHandleScope handleScope(ctx);
    JSValue paFunc = GetPaFunc("update");
    JSValueConst argv[] = {};
    JSValue retVal = QJSUtils::Call(ctx, paFunc, JS_UNDEFINED, countof(argv), argv);
    if (JS_IsException(retVal)) {
        LOGE("Qjs paFunc FAILED!");
        return 0;
    }
    return GetJsInt32Val(ctx, retVal);
}

int32_t QjsPaEngine::Delete(const Uri& uri, const OHOS::NativeRdb::DataAbilityPredicates& predicates)
{
    LOGI("Delete");
    JSContext *ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);

    QJSHandleScope handleScope(ctx);
    JSValue paFunc = GetPaFunc("delete");
    JSValueConst argv[] = {};
    JSValue retVal = QJSUtils::Call(ctx, paFunc, JS_UNDEFINED, countof(argv), argv);
    if (JS_IsException(retVal)) {
        LOGE("Qjs paFunc FAILED!");
        return 0;
    }
    return GetJsInt32Val(ctx, retVal);
}

int32_t QjsPaEngine::BatchInsert(const Uri& uri, const std::vector<OHOS::NativeRdb::ValuesBucket>& values)
{
    LOGI("BatchInsert");
    JSContext *ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);

    QJSHandleScope handleScope(ctx);
    JSValue paFunc = GetPaFunc("batchInsert");
    JSValueConst argv[] = {};
    JSValue retVal = QJSUtils::Call(ctx, paFunc, JS_UNDEFINED, countof(argv), argv);
    if (JS_IsException(retVal)) {
        LOGE("Qjs paFunc FAILED!");
        return 0;
    }
    return GetJsInt32Val(ctx, retVal);
}

std::string QjsPaEngine::GetType(const Uri& uri)
{
    LOGI("GetType");
    JSContext *ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);

    QJSHandleScope handleScope(ctx);
    JSValue paFunc = GetPaFunc("getType");
    JSValueConst argv[] = {};
    JSValue retVal = QJSUtils::Call(ctx, paFunc, JS_UNDEFINED, countof(argv), argv);
    if (JS_IsException(retVal)) {
        LOGE("Qjs paFunc FAILED!");
        return std::string();
    }
    return GetJsStringVal(ctx, retVal);
}

std::vector<std::string> QjsPaEngine::GetFileTypes(const Uri& uri, const std::string& mimeTypeFilter)
{
    LOGI("GetFileTypes");
    JSContext *ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);

    std::vector<std::string> ret;
    QJSHandleScope handleScope(ctx);
    JSValue paFunc = GetPaFunc("getFileTypes");
    JSValueConst argv[] = {};
    JSValue retVal = QJSUtils::Call(ctx, paFunc, JS_UNDEFINED, countof(argv), argv);
    if (JS_IsException(retVal)) {
        LOGE("Qjs paFunc FAILED!");
        return ret;
    }

    if (!JS_IsArray(ctx, retVal)) {
        LOGE("GetFileTypes return not array");
        return ret;
    }

    int32_t length = QJSUtils::JsGetArrayLength(ctx, retVal);
    for (int i = 0; i < length; i++) {
        JSValue itemVal = JS_GetPropertyUint32(ctx, retVal, i);
        ret.push_back(GetJsStringVal(ctx, itemVal));
    }

    return ret;
}

int32_t QjsPaEngine::OpenFile(const Uri& uri, const std::string& mode)
{
    LOGI("OpenFile");
    JSContext *ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);

    QJSHandleScope handleScope(ctx);
    JSValue paFunc = GetPaFunc("openFile");
    JSValueConst argv[] = {};
    JSValue retVal = QJSUtils::Call(ctx, paFunc, JS_UNDEFINED, countof(argv), argv);
    if (JS_IsException(retVal)) {
        LOGE("Qjs paFunc FAILED!");
        return 0;
    }
    return GetJsInt32Val(ctx, retVal);
}

int32_t QjsPaEngine::OpenRawFile(const Uri& uri, const std::string& mode)
{
    LOGI("OpenRawFile");
    JSContext *ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);

    QJSHandleScope handleScope(ctx);
    JSValue paFunc = GetPaFunc("openRawFile");
    JSValueConst argv[] = {};
    JSValue retVal = QJSUtils::Call(ctx, paFunc, JS_UNDEFINED, countof(argv), argv);
    if (JS_IsException(retVal)) {
        LOGE("Qjs paFunc FAILED!");
        return 0;
    }
    return GetJsInt32Val(ctx, retVal);
}

Uri QjsPaEngine::NormalizeUri(const Uri& uri)
{
    LOGI("NormalizeUri");
    JSContext *ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);

    Uri ret("");
    QJSHandleScope handleScope(ctx);
    JSValue paFunc = GetPaFunc("normalizeUri");
    JSValueConst argv[] = {};
    JSValue retVal = QJSUtils::Call(ctx, paFunc, JS_UNDEFINED, countof(argv), argv);
    if (JS_IsException(retVal)) {
        LOGE("Qjs paFunc FAILED!");
        return ret;
    }

    // TODO: retVal to uri;
    return ret;
}

Uri QjsPaEngine::DenormalizeUri(const Uri& uri)
{
    LOGI("DenormalizeUri");
    JSContext *ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);

    Uri ret("");
    QJSHandleScope handleScope(ctx);
    JSValue paFunc = GetPaFunc("denormalizeUri");
    JSValueConst argv[] = {};
    JSValue retVal = QJSUtils::Call(ctx, paFunc, JS_UNDEFINED, countof(argv), argv);
    if (JS_IsException(retVal)) {
        LOGE("Qjs paFunc FAILED!");
        return ret;
    }

    // TODO: retVal to uri;
    return ret;
}

sptr<IRemoteObject> QjsPaEngine::OnConnectService(const std::string &want)
{
    LOGI("OnConnectService");
    JSContext *ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);
    QJSHandleScope handleScope(ctx);
    QJSContext::Scope scope(ctx);
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSValue paObj = QJSUtils::GetPropertyStr(ctx, globalObj, "pa");
    if (!JS_IsObject(paObj)) {
        LOGE("get onConnectFunc  error");
        return nullptr;
    }
    JSValue onConnectFunc = QJSUtils::GetPropertyStr(ctx, paObj, "OnConnect");
    if (!JS_IsFunction(ctx, onConnectFunc)) {
        LOGE("onConnectFunc is not found!");
        JS_FreeValue(ctx, globalObj);
        return nullptr;
    }

    JSValueConst argv[] = { QJSUtils::ParseJSON(ctx, want.c_str(), want.size(), nullptr) };
    JSValue retVal = QJSUtils::Call(ctx, onConnectFunc, JS_UNDEFINED, countof(argv), argv);
    js_std_loop(ctx);
    if (JS_IsException(retVal)) {
        LOGE("Qjs onConnectService FAILED!");
        JS_FreeValue(ctx, globalObj);
        JS_FreeValue(ctx, retVal);
        return nullptr;
    } else {
        NativeValue* nativeValue = QuickJSNativeEngine::JSValueToNativeValue(nativeEngine_, retVal);
        auto remoteObj = NAPI_ohos_rpc_getNativeRemoteObject(reinterpret_cast<napi_env>(nativeEngine_), 
                     reinterpret_cast<napi_value>(nativeValue));
        JS_FreeValue(ctx, globalObj);
        JS_FreeValue(ctx, retVal);
        return remoteObj;
    }
}

void QjsPaEngine::OnDisconnectService(const std::string &want)
{
    LOGI("OnConnectService");
    JSContext *ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);

    QJSHandleScope handleScope(ctx);
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSValue paObj = QJSUtils::GetPropertyStr(ctx, globalObj, "pa");
    if (!JS_IsObject(paObj)) {
        LOGE("get OnDisconnect error");
        return;
    }
    JSValue onDisConnectFunc = QJSUtils::GetPropertyStr(ctx, paObj, "OnDisConnect");
    if (!JS_IsFunction(ctx, onDisConnectFunc)) {
        LOGE("onDisConnectFunc is not found!");
        JS_FreeValue(ctx, globalObj);
        return;
    }
    JSValueConst argv[] = { QJSUtils::ParseJSON(ctx, want.c_str(), want.size(), nullptr) };
    JSValue retVal = QJSUtils::Call(ctx, onDisConnectFunc, JS_UNDEFINED, countof(argv), argv);
    if (JS_IsException(retVal)) {
        LOGE("Qjs OnDisconnectService FAILED!");
    }
    JS_FreeValue(ctx, globalObj);
}

} // namespace OHOS::Ace::Framework
