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

#include "adapter/ohos/entrance/pa_engine/engine/jsi/jsi_pa_engine.h"

#include "js_backend_timer_module.h"
#include "js_environment.h"
#include "napi_common_ability.h"

#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_value.h"
#include "frameworks/bridge/js_frontend/engine/jsi/jsi_base_utils.h"

extern const char _binary_paMgmt_abc_start[];
extern const char _binary_paMgmt_abc_end[];

namespace OHOS::Ace {
namespace {
#ifdef APP_USE_ARM
const std::string ARK_DEBUGGER_LIB_PATH = "libark_inspector.z.so";
#else
const std::string ARK_DEBUGGER_LIB_PATH = "libark_inspector.z.so";
#endif
const char TASK_RUNNER[] = "PaEngineRunner";

bool UnwrapRawImageDataMap(napi_env env, napi_value argv, std::map<std::string, int>& rawImageDataMap)
{
    if (!AppExecFwk::IsTypeForNapiValue(env, argv, napi_object)) {
        LOGW("%{public}s failed, param is not napi_object.", __func__);
        return false;
    }

    napi_valuetype jsValueType = napi_undefined;
    napi_value jsProNameList = nullptr;
    uint32_t jsProCount = 0;

    NAPI_CALL_BASE(env, napi_get_property_names(env, argv, &jsProNameList), false);
    NAPI_CALL_BASE(env, napi_get_array_length(env, jsProNameList, &jsProCount), false);
    LOGI("%{public}s called. Property size=%{public}d.", __func__, jsProCount);

    napi_value jsProName = nullptr;
    napi_value jsProValue = nullptr;
    for (uint32_t index = 0; index < jsProCount; index++) {
        NAPI_CALL_BASE(env, napi_get_element(env, jsProNameList, index, &jsProName), false);
        std::string strProName = AppExecFwk::UnwrapStringFromJS(env, jsProName);
        NAPI_CALL_BASE(env, napi_get_named_property(env, argv, strProName.c_str(), &jsProValue), false);
        NAPI_CALL_BASE(env, napi_typeof(env, jsProValue, &jsValueType), false);
        int natValue = AppExecFwk::UnwrapInt32FromJS(env, jsProValue);
        rawImageDataMap.emplace(strProName, natValue);
    }
    return true;
}

// native implementation for js function: Particle.onCreateFinish()
shared_ptr<JsValue> JsOnCreateFinish(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return runtime->NewUndefined();
}

// native implementation for js function: Particle.JsHandleCallback()
shared_ptr<JsValue> JsHandleCallback(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    LOGI("JsHandleCallback");
    return runtime->NewUndefined();
}

// native implementation for js function: Particle.JsRunLoopOnce()
shared_ptr<JsValue> JsRunLoopOnce(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    auto engineInstance = static_cast<JsiPaEngine*>(runtime->GetEmbedderData());
    if (engineInstance == nullptr) {
        LOGE("engineInstance is nullptr");
        return runtime->NewUndefined();
    }
    auto nativeEngine = engineInstance->GetNativeEngine();
    if (nativeEngine == nullptr) {
        LOGE("nativeEngine is nullptr");
        return runtime->NewUndefined();
    }

    nativeEngine->Loop(LOOP_ONCE);
    runtime->ExecutePendingJob();
    return runtime->NewUndefined();
}

// native implementation for js function: Particle.JsRunMicrotasks()
shared_ptr<JsValue> JsRunMicrotasks(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    runtime->ExecutePendingJob();
    return runtime->NewUndefined();
}

shared_ptr<JsValue> AsyncFuncCallBack(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    LOGI("AsyncFuncCallBack");
    auto engineInstance = static_cast<JsiPaEngine*>(runtime->GetEmbedderData());
    if (engineInstance == nullptr) {
        LOGE("engineInstance is nullptr");
        return runtime->NewUndefined();
    }
    if (argc != 2) {
        LOGE("args length is error");
        engineInstance->SetBlockWaiting(true);
        engineInstance->SetAsyncResult(runtime->NewUndefined());
        return runtime->NewUndefined();
    }
    int32_t code = argv[0]->ToInt32(runtime);
    if (code != 0) {
        LOGE("AsyncFuncCallBack error code: %{public}d", code);
    }
    engineInstance->SetBlockWaiting(true);
    engineInstance->SetAsyncResult(argv[1]);
    return runtime->NewUndefined();
}

inline std::string ToJSONStringInt(std::string sKey, std::string sValue)
{
    char szDoubleQuotes[] = "\"";
    char szColon[] = ":";
    std::string strResult;
    strResult.append(szDoubleQuotes);
    strResult.append(sKey);
    strResult.append(szDoubleQuotes);

    strResult.append(szColon);
    strResult.append(sValue);
    return strResult;
}
} // namespace

void JsiPaEngine::RegisterUncaughtExceptionHandler()
{
    ACE_SCOPED_TRACE("JsiPaEngine::RegisterUncaughtExceptionHandler");
    JsEnv::UncaughtExceptionInfo uncaughtExceptionInfo;
    uncaughtExceptionInfo.uncaughtTask = [](std::string summary, const JsEnv::ErrorObject errorObj) {
        std::string packageName = AceApplicationInfo::GetInstance().GetPackageName();
        JsErrorObject errorInfo = {
            .name = errorObj.name,
            .message = errorObj.message,
            .stack = errorObj.stack,
        };
        EventReport::JsErrReport(packageName, "", summary);
        ExceptionHandler::HandleJsException(summary, errorInfo, false);
    };

    jsAbilityRuntime_->RegisterUncaughtExceptionHandler(uncaughtExceptionInfo);
}

void JsiPaEngine::RegisterConsoleModule(ArkNativeEngine* engine)
{
    ACE_SCOPED_TRACE("JsiPaEngine::RegisterConsoleModule");
    CHECK_NULL_VOID(engine);

    napi_env env = reinterpret_cast<napi_env>(engine);
    napi_value globalObj;
    napi_get_global(env, &globalObj);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, globalObj, &valueType);
    if (valueType != napi_object) {
        LOGE("global is not NativeObject");
        return;
    }

    napi_value logValue;
    napi_create_function(env, "log", strlen("log"), AppInfoLogPrint, nullptr, &logValue);
    napi_value debugValue;
    napi_create_function(env, "debug", strlen("debug"), AppDebugLogPrint, nullptr, &debugValue);
    napi_value infoValue;
    napi_create_function(env, "info", strlen("info"), AppInfoLogPrint, nullptr, &infoValue);
    napi_value warnValue;
    napi_create_function(env, "warn", strlen("warn"), AppWarnLogPrint, nullptr, &warnValue);
    napi_value errorValue;
    napi_create_function(env, "error", strlen("error"), AppErrorLogPrint, nullptr, &errorValue);
    napi_value consoleObj = nullptr;
    napi_create_object(env, &consoleObj);
    napi_set_named_property(env, consoleObj, "log", logValue);
    napi_set_named_property(env, consoleObj, "debug", debugValue);
    napi_set_named_property(env, consoleObj, "info", infoValue);
    napi_set_named_property(env, consoleObj, "warn", warnValue);
    napi_set_named_property(env, consoleObj, "error", errorValue);
    napi_set_named_property(env, globalObj, "console", consoleObj);
}

void JsiPaEngine::RegisterPaModule()
{
    ACE_SCOPED_TRACE("JsiPaEngine::RegisterAceModule");

    shared_ptr<JsValue> aceObj = runtime_->NewObject();
    if (!aceObj) {
        LOGE("RegisterPaModule failed. aceObj is null");
        return;
    }
    if (!aceObj->SetProperty(runtime_, "onCreateFinish", runtime_->NewFunction(JsOnCreateFinish))) {
        LOGE("RegisterPaModule onCreateFinish failed.");
    }
    if (!aceObj->SetProperty(runtime_, "handleCallback", runtime_->NewFunction(JsHandleCallback))) {
        LOGE("RegisterPaModule handleCallback failed.");
    }
    if (!aceObj->SetProperty(runtime_, "runLoopOnce", runtime_->NewFunction(JsRunLoopOnce))) {
        LOGE("RegisterPaModule runLoopOnce failed.");
    }
    if (!aceObj->SetProperty(runtime_, "runMicrotasks", runtime_->NewFunction(JsRunMicrotasks))) {
        LOGE("RegisterPaModule runMicrotasks failed.");
    }

    shared_ptr<JsValue> global = runtime_->GetGlobal();
    if (!global->SetProperty(runtime_, "Particle", aceObj)) {
        LOGE("RegisterPaModule ace failed.");
    }
}

void JsiPaEngine::EvaluateJsCode()
{
    ACE_SCOPED_TRACE("JsiPaEngine::EvaluateJsCode");
    CHECK_NULL_VOID(jsAbilityRuntime_);
    // load jsfwk
    if (language_ == SrcLanguage::JS && !jsAbilityRuntime_->LoadScript("/system/etc/strip.native.min.abc")) {
        LOGE("Failed to load js framework!");
    }
    // load paMgmt.js
    std::vector<uint8_t> paMgmt(_binary_paMgmt_abc_start, _binary_paMgmt_abc_end);
    if (!jsAbilityRuntime_->LoadScript("", &paMgmt, true)) {
        LOGE("EvaluateJsCode paMgmt abc failed");
    }
}

void JsiPaEngine::InitJsRuntimeOptions(AbilityRuntime::Runtime::Options& options)
{
    options.lang = AbilityRuntime::Runtime::Language::JS;
    options.eventRunner = eventRunner_;
    options.loadAce = false;
    options.preload = false;
    options.isStageModel = false;
    options.hapPath = GetHapPath();
    options.isDebugVersion = GetDebugMode();
    options.packagePathStr = GetWorkerPath()->packagePathStr;
    options.assetBasePathStr = GetWorkerPath()->assetBasePathStr;
    options.isJsFramework = language_ == SrcLanguage::JS;
}

bool JsiPaEngine::CreateJsRuntime()
{
    AbilityRuntime::Runtime::Options options;
    InitJsRuntimeOptions(options);
    jsAbilityRuntime_ = AbilityRuntime::JsRuntime::Create(options);
    if (jsAbilityRuntime_ == nullptr) {
        LOGE("Create js runtime failed.");
        return false;
    }

    return true;
}

bool JsiPaEngine::InitJsEnv(bool debuggerMode, const std::unordered_map<std::string, void*>& extraNativeObject)
{
    ACE_SCOPED_TRACE("JsiPaEngine::InitJsEnv");
    runtime_.reset(new ArkJSRuntime());
    if (runtime_ == nullptr) {
        LOGE("Can't allocate JSI JSRuntime");
        EventReport::SendJsException(JsExcepType::JS_ENGINE_INIT_ERR);
        return false;
    }

    runtime_->SetLogPrint(PrintLog);
    StartDebugMode(debuggerMode);

    auto ecmaVm = GetEcmaVm();
    CHECK_NULL_RETURN(ecmaVm, false);
    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime_);
    if (!arkJSRuntime->InitializeFromExistVM(ecmaVm)) {
        LOGE("Initialize runtime from exist vm failed.");
        return false;
    }
    arkJSRuntime->SetDebugMode(isDebugMode_);
    arkJSRuntime->SetInstanceId(instanceId_);

#if !defined(PREVIEW)
    for (const auto& [key, value] : extraNativeObject) {
        shared_ptr<JsValue> nativeValue = runtime_->NewNativePointer(value);
        runtime_->GetGlobal()->SetProperty(runtime_, key, nativeValue);
    }
#endif

    // Register pa native functions
    RegisterPaModule();

    // load abc file
    EvaluateJsCode();

    runtime_->SetEmbedderData(this);

    RegisterUncaughtExceptionHandler();
    LOGI("InitJsEnv success");
    return true;
}

std::shared_ptr<JsRuntime> JsiPaEngine::GetJsRuntime() const
{
    return runtime_;
}

inline NativeEngine* JsiPaEngine::GetNativeEngine() const
{
    CHECK_NULL_RETURN(jsAbilityRuntime_, nullptr);
    return jsAbilityRuntime_->GetNativeEnginePointer();
}

inline panda::ecmascript::EcmaVM* JsiPaEngine::GetEcmaVm() const
{
    CHECK_NULL_RETURN(jsAbilityRuntime_, nullptr);
    return jsAbilityRuntime_->GetEcmaVm();
}

void JsiPaEngine::StartDebugMode(bool debuggerMode)
{
    if (debuggerMode && jsAbilityRuntime_ != nullptr) {
#ifdef OHOS_PLATFORM
        jsAbilityRuntime_->StartDebugger(debuggerMode, instanceId_);
#endif
    }
}

// -----------------------
// Start JsiPaEngine
// -----------------------
JsiPaEngine::~JsiPaEngine()
{
    LOGI("JsiPaEngine destructor");
    UnloadLibrary();

    if (runtime_) {
        runtime_->Reset();
    }
    runtime_.reset();
    runtime_ = nullptr;

    // To guarantee the jsruntime released in js thread
    auto jsRuntime = std::move(jsAbilityRuntime_);
    if (!eventHandler_->PostSyncTask([&jsRuntime] { auto runtime = std::move(jsRuntime); })) {
        LOGE("Post sync task failed.");
    }
}

bool JsiPaEngine::Initialize(BackendType type, SrcLanguage language)
{
    ACE_SCOPED_TRACE("JsiPaEngine::Initialize");
    LOGI("JsiPaEngine initialize");
    SetDebugMode(NeedDebugBreakPoint());
    type_ = type;
    language_ = language;

    eventRunner_ = EventRunner::Create(TASK_RUNNER + std::to_string(instanceId_));
    if (eventRunner_ == nullptr) {
        LOGE("Create runner failed.");
        return false;
    }

    eventHandler_ = std::make_shared<EventHandler>(eventRunner_);
    if (eventHandler_ == nullptr) {
        LOGE("Create handler failed.");
        return false;
    }

    bool ret = false;
    eventHandler_->PostSyncTask([weakEngine = AceType::WeakClaim(this), &ret] {
        auto paEngine = weakEngine.Upgrade();
        if (paEngine != nullptr) {
            ret = paEngine->CreateJsRuntime();
        }
    });
    if (!ret) {
        return false;
    }

    PostTask([weakEngine = AceType::WeakClaim(this), type, language] {
        auto paEngine = weakEngine.Upgrade();
        if (paEngine == nullptr) {
            LOGE("Pa engine is invalid.");
            return;
        }
        paEngine->InitializeInner(type, language);
    }, "ArkUIPaEngineInit");
    return true;
}

bool JsiPaEngine::InitializeInner(BackendType type, SrcLanguage language)
{
    bool result = InitJsEnv(GetDebugMode(), GetExtraNativeObject());
    if (!result) {
        LOGE("Init js env failed");
        return false;
    }

    LoadLibrary();

    auto nativeEngine = GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, false);
    if (language_ == SrcLanguage::JS) {
        InitTimerModule(reinterpret_cast<napi_env>(nativeEngine));
    }

    if (jsBackendAssetManager_) {
        std::vector<std::string> packagePath = jsBackendAssetManager_->GetLibPath();
        auto appLibPathKey = jsBackendAssetManager_->GetAppLibPathKey();
        if (!packagePath.empty()) {
            auto arkNativeEngine = static_cast<ArkNativeEngine*>(nativeEngine);
            arkNativeEngine->SetPackagePath(appLibPathKey, packagePath);
        }
    }
    return true;
}

void JsiPaEngine::SetAssetManager(const RefPtr<AssetManager>& assetManager)
{
    jsBackendAssetManager_ = Referenced::MakeRefPtr<JsBackendAssetManager>(assetManager);
}

void JsiPaEngine::LoadJs(const std::string& url, const OHOS::AAFwk::Want& want)
{
    ACE_SCOPED_TRACE("JsiPaEngine::LoadJs");
    LOGI("JsiPaEngine LoadJs: %{private}s", url.c_str());

    auto runtime = GetJsRuntime();

    // js file to abc file and execute abc file
    const char js_ext[] = ".js";
    const char bin_ext[] = ".abc";
    auto pos = url.rfind(js_ext);
    if (pos != std::string::npos && pos == url.length() - (sizeof(js_ext) - 1)) {
        std::string urlName = url.substr(0, pos) + bin_ext;
        LOGI("GetAssetContent: %{public}s", urlName.c_str());
        std::vector<uint8_t> content;
        if (jsBackendAssetManager_ == nullptr || !jsBackendAssetManager_->GetAssetContent(urlName, content)) {
            LOGE("GetAssetContent \"%{public}s\" failed.", urlName.c_str());
            return;
        }
        std::string abcPath = jsBackendAssetManager_->GetAssetPath(urlName).append(urlName);
        CHECK_NULL_VOID(jsAbilityRuntime_);
        if (!jsAbilityRuntime_->LoadScript(abcPath, &content, true)) {
            LOGE("LoadScript \"%{public}s\" failed.", urlName.c_str());
            return;
        }

        // only ace1.0 need
        shared_ptr<JsValue> mainEntryFunc = runtime->GetGlobal()->GetProperty(runtime, "___mainEntry___");
        if (mainEntryFunc->IsFunction(runtime)) {
            LOGI("JsiPaEngine call mainEntryFunc");
            runtime->GetGlobal()->SetProperty(runtime, "___mainEntry___", runtime->NewUndefined());
            const std::vector<shared_ptr<JsValue>>& argv = { runtime->GetGlobal() };
            shared_ptr<JsValue> retVal = CallFunc(mainEntryFunc, argv);
            auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
            if (arkJSRuntime->HasPendingException()) {
                LOGE("JsiPaEngine call mainEntryFunc FAILED!");
            }
        }
    }

    // call start pa func
    if (type_ == BackendType::SERVICE) {
        StartService();
    } else if (type_ == BackendType::DATA) {
        StartData();
    } else if (type_ == BackendType::FORM) {
        LOGI("Form Ability LoadJS finish.");
    } else {
        LOGE("backend type not support");
    }
}

void JsiPaEngine::LoadLibrary()
{
#ifdef APP_USE_ARM
    const char* rdbPath = "/system/lib/module/data/librdb.z.so";
#else
    const char* rdbPath = "/system/lib64/module/data/librdb.z.so";
#endif
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

#ifdef APP_USE_ARM
    const char* dataAbilityPath = "/system/lib/module/data/libdataability.z.so";
#else
    const char* dataAbilityPath = "/system/lib64/module/data/libdataability.z.so";
#endif
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

void JsiPaEngine::UnloadLibrary()
{
    dlclose(libRdb_);
    dlclose(libDataAbility_);
}

shared_ptr<JsValue> JsiPaEngine::GetPaFunc(const std::string& funcName)
{
    LOGI("JsiPaEngine GetPaFunc funcName: %{public}s", funcName.c_str());
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    ACE_DCHECK(runtime);
    shared_ptr<JsValue> global = runtime->GetGlobal();
    shared_ptr<JsValue> exportsObject = global->GetProperty(runtime, "exports");
    if (!exportsObject->IsObject(runtime)) {
        LOGE("property \"exports\" is not a object");
        return nullptr;
    }
    shared_ptr<JsValue> defaultObject = exportsObject->GetProperty(runtime, "default");
    if (!defaultObject->IsObject(runtime)) {
        LOGE("property \"default\" is not a object");
        return nullptr;
    }

    shared_ptr<JsValue> func = defaultObject->GetProperty(runtime, funcName);
    if (!func->IsFunction(runtime)) {
        LOGE("%{public}s not found or is not a function!", funcName.c_str());
        return nullptr;
    }
    return func;
}

shared_ptr<JsValue> JsiPaEngine::CallFunc(const shared_ptr<JsValue>& func)
{
    const std::vector<shared_ptr<JsValue>>& argv = {};
    return CallFunc(func, argv);
}

shared_ptr<JsValue> JsiPaEngine::CallFunc(const shared_ptr<JsValue>& func, const std::vector<shared_ptr<JsValue>>& argv)
{
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    ACE_DCHECK(runtime);
    if (func == nullptr) {
        LOGE("func is nullptr!");
        return runtime->NewUndefined();
    }
    if (!func->IsFunction(runtime)) {
        LOGE("func is not a function!");
        return runtime->NewUndefined();
    }

    auto nativeEngine = GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, runtime->NewUndefined());
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine CallFunc FAILED!");
        return runtime->NewUndefined();
    }

    auto arkJSFunc = std::static_pointer_cast<ArkJSValue>(func);
    if (arkJSFunc->IsUndefined(runtime)) {
        LOGE("JsiPaEngine CallFunc return value is und efined!");
        return runtime->NewUndefined();
    }

    std::vector<napi_value> nativeArgv;
    int32_t length = 0;
    for (auto item : argv) {
        auto value = std::static_pointer_cast<ArkJSValue>(item);
        auto napiValue = ArkNativeEngine::ArkValueToNapiValue(env, value->GetValue(arkJSRuntime));
        nativeArgv.emplace_back(napiValue);
        length++;
    }

    napi_value nativeFunc = ArkNativeEngine::ArkValueToNapiValue(env, arkJSFunc->GetValue(arkJSRuntime));
    CHECK_NULL_RETURN(nativeFunc, nullptr);
    napi_value globalObj;
    napi_get_global(env, &globalObj);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, globalObj, &valueType);
    if (valueType != napi_object) {
        LOGE("global is not NativeObject");
        return runtime->NewUndefined();
    }
    napi_value ret;
    napi_call_function(env, globalObj, nativeFunc, length, nativeArgv.data(), &ret);
    return NapiValueToJsValue(ret);
}

shared_ptr<JsValue> JsiPaEngine::CallFuncWithDefaultThis(
    const shared_ptr<JsValue>& func, const std::vector<shared_ptr<JsValue>>& argv)
{
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    ACE_DCHECK(runtime);
    if (func == nullptr) {
        LOGE("func is nullptr!");
        return runtime->NewUndefined();
    }
    if (!func->IsFunction(runtime)) {
        LOGE("func is not a function!");
        return runtime->NewUndefined();
    }

    shared_ptr<JsValue> global = runtime->GetGlobal();
    shared_ptr<JsValue> thisObject = global;
    do {
        shared_ptr<JsValue> exportsObject = global->GetProperty(runtime, "exports");
        if (!exportsObject->IsObject(runtime)) {
            LOGW("property \"exports\" is not a object");
            break;
        }
        shared_ptr<JsValue> defaultObject = exportsObject->GetProperty(runtime, "default");
        if (!defaultObject->IsObject(runtime)) {
            LOGE("property \"default\" is not a object");
            break;
        }
        thisObject = defaultObject;
    } while (false);

    auto nativeEngine = GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, runtime->NewUndefined());
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine CallFunc FAILED!");
        return runtime->NewUndefined();
    }

    auto arkJSThis = std::static_pointer_cast<ArkJSValue>(thisObject);
    if (arkJSThis->IsUndefined(runtime)) {
        LOGE("JsiPaEngine CallFunc return value is undefined!");
        return runtime->NewUndefined();
    }

    auto arkJSFunc = std::static_pointer_cast<ArkJSValue>(func);
    if (arkJSFunc->IsUndefined(runtime)) {
        LOGE("JsiPaEngine CallFunc return value is und efined!");
        return runtime->NewUndefined();
    }

    std::vector<napi_value> nativeArgv;
    int32_t length = 0;
    for (auto item : argv) {
        auto value = std::static_pointer_cast<ArkJSValue>(item);
        auto nativeVal = ArkNativeEngine::ArkValueToNapiValue(env, value->GetValue(arkJSRuntime));
        nativeArgv.emplace_back(nativeVal);
        length++;
    }

    napi_value nativeFunc = ArkNativeEngine::ArkValueToNapiValue(env, arkJSFunc->GetValue(arkJSRuntime));
    CHECK_NULL_RETURN(nativeFunc, nullptr);

    napi_value nativeThis = ArkNativeEngine::ArkValueToNapiValue(env, arkJSThis->GetValue(arkJSRuntime));
    CHECK_NULL_RETURN(nativeThis, nullptr);

    napi_value ret;
    napi_call_function(env, nativeThis, nativeFunc, length, nativeArgv.data(), &ret);

    return NapiValueToJsValue(ret);
}

shared_ptr<JsValue> JsiPaEngine::CallFunc(
    const shared_ptr<JsValue>& func, const std::vector<shared_ptr<JsValue>>& argv, const CallingInfo& callingInfo)
{
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    ACE_DCHECK(runtime);
    if (func == nullptr) {
        LOGE("func is nullptr!");
        return runtime->NewUndefined();
    }
    if (!func->IsFunction(runtime)) {
        LOGE("func is not a function!");
        return runtime->NewUndefined();
    }
    shared_ptr<JsValue> global = runtime->GetGlobal();

    auto nativeEngine = GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, runtime->NewUndefined());
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    NAPI_CallingInfo oldCallingInfo;
    NAPI_RemoteObject_saveOldCallingInfo(env, oldCallingInfo);
    NAPI_RemoteObject_setNewCallingInfo(env, callingInfo);
    NAPI_RemoteObject_resetOldCallingInfo(env, oldCallingInfo);

    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine CallFunc FAILED!");
        return runtime->NewUndefined();
    }

    auto arkJSFunc = std::static_pointer_cast<ArkJSValue>(func);
    if (arkJSFunc->IsUndefined(runtime)) {
        LOGE("JsiPaEngine CallFunc return value is und efined!");
        return runtime->NewUndefined();
    }

    std::vector<napi_value> nativeArgv;
    int32_t length = 0;

    for (auto item : argv) {
        auto value = std::static_pointer_cast<ArkJSValue>(item);
        auto napiValue = ArkNativeEngine::ArkValueToNapiValue(env, value->GetValue(arkJSRuntime));
        nativeArgv.emplace_back(napiValue);
        length++;
    }

    napi_value nativeFunc = ArkNativeEngine::ArkValueToNapiValue(env, arkJSFunc->GetValue(arkJSRuntime));
    CHECK_NULL_RETURN(nativeFunc, nullptr);

    napi_value globalObj;
    napi_get_global(env, &globalObj);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, globalObj, &valueType);
    if (valueType != napi_object) {
        LOGE("global is not NativeObject");
        return runtime->NewUndefined();
    }
    napi_value ret;
    napi_call_function(env, globalObj, nativeFunc, length, nativeArgv.data(), &ret);
    return NapiValueToJsValue(ret);
}

shared_ptr<JsValue> JsiPaEngine::CallAsyncFunc(
    const shared_ptr<JsValue>& func, std::vector<shared_ptr<JsValue>>& argv, const CallingInfo& callingInfo)
{
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    ACE_DCHECK(runtime);
    if (func == nullptr) {
        LOGE("func is nullptr!");
        return runtime->NewUndefined();
    }
    if (!func->IsFunction(runtime)) {
        LOGE("func is not a function!");
        return runtime->NewUndefined();
    }
    shared_ptr<JsValue> global = runtime->GetGlobal();

    auto nativeEngine = GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, runtime->NewUndefined());
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    NAPI_CallingInfo oldCallingInfo;
    NAPI_RemoteObject_saveOldCallingInfo(env, oldCallingInfo);
    NAPI_RemoteObject_setNewCallingInfo(env, callingInfo);

    argv.push_back(runtime->NewFunction(AsyncFuncCallBack));

    SetBlockWaiting(false);

    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine CallFunc FAILED!");
        return runtime->NewUndefined();
    }

    auto arkJSFunc = std::static_pointer_cast<ArkJSValue>(func);
    if (arkJSFunc->IsUndefined(runtime)) {
        LOGE("JsiPaEngine CallFunc return value is und efined!");
        return runtime->NewUndefined();
    }

    std::vector<napi_value> nativeArgv;
    int32_t length = 0;
    for (auto item : argv) {
        auto value = std::static_pointer_cast<ArkJSValue>(item);
        auto napiValue = ArkNativeEngine::ArkValueToNapiValue(env, value->GetValue(arkJSRuntime));
        nativeArgv.emplace_back(napiValue);
        length++;
    }

    napi_value nativeFunc = ArkNativeEngine::ArkValueToNapiValue(env, arkJSFunc->GetValue(arkJSRuntime));
    CHECK_NULL_RETURN(nativeFunc, nullptr);
    napi_value globalObj;
    napi_get_global(env, &globalObj);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, globalObj, &valueType);
    if (valueType != napi_object) {
        LOGE("global is not NativeObject");
        return runtime->NewUndefined();
    }
    napi_value ret;
    napi_call_function(env, globalObj, nativeFunc, length, nativeArgv.data(), &ret);

    runtime->ExecutePendingJob();
    while (!GetBlockWaiting()) {
        nativeEngine->Loop(LOOP_ONCE);
        runtime->ExecutePendingJob();
    }
    NAPI_RemoteObject_resetOldCallingInfo(env, oldCallingInfo);
    return GetAsyncResult();
}

shared_ptr<JsValue> JsiPaEngine::NapiValueToJsValue(napi_value napiValue)
{
    if (napiValue == nullptr) {
        LOGE("napiValue is nullptr!");
        return GetJsRuntime()->NewUndefined();
    }
    auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(GetJsRuntime());
    return std::make_shared<ArkJSValue>(arkRuntime, NapiValueToLocalValue(napiValue));
}

shared_ptr<JsValue> JsiPaEngine::WantToJsValue(const OHOS::AAFwk::Want& want)
{
    napi_value napiWant = OHOS::AppExecFwk::WrapWant(reinterpret_cast<napi_env>(GetNativeEngine()), want);
    return NapiValueToJsValue(napiWant);
}

void JsiPaEngine::StartService()
{
    LOGI("JsiPaEngine StartService");
    auto func = GetPaFunc("onStart");
    CallFunc(func);
}

void JsiPaEngine::StartData()
{
    LOGI("JsiPaEngine StartData");

    const auto& nativeObjects = GetExtraNativeObject();
    auto it = nativeObjects.find("ability");
    if (it == nativeObjects.end() || it->second == nullptr) {
        LOGE("Can't find ability object");
        return;
    }

    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    auto nativeEngine = GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    const std::shared_ptr<AppExecFwk::AbilityInfo> abilityInfo =
        reinterpret_cast<Ability*>(it->second)->GetAbilityInfo();
    const AppExecFwk::AbilityInfo abilityInfoInstance = *(abilityInfo.get());
    napi_value abilityInfoNapi =
        AppExecFwk::ConvertAbilityInfo(reinterpret_cast<napi_env>(nativeEngine), abilityInfoInstance);
    const std::vector<shared_ptr<JsValue>>& argv = { NapiValueToJsValue(abilityInfoNapi) };

    auto func = GetPaFunc("onInitialized");
    CallFunc(func, argv);
}

void JsiPaEngine::DestroyApplication(const std::string& packageName)
{
    LOGI("JsiPaEngine DestroyApplication");
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = { runtime->NewString(packageName) };
    auto func = GetPaFunc("onStop");
    CallFunc(func, argv);
}

int32_t JsiPaEngine::Insert(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value, const CallingInfo& callingInfo)
{
    LOGI("JsiPaEngine Insert");
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    auto nativeEngine = GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, 0);
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    napi_value argNapiValue = rdbValueBucketNewInstance_(env, const_cast<OHOS::NativeRdb::ValuesBucket&>(value));
    std::vector<shared_ptr<JsValue>> argv;
    argv.push_back(runtime->NewString(uri.ToString()));
    argv.push_back(NapiValueToJsValue(argNapiValue));
    auto func = GetPaFunc("insert");
    shared_ptr<JsValue> retVal = CallAsyncFunc(func, argv, callingInfo);

    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine Insert FAILED!");
        return 0;
    }
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    return arkJSValue->ToInt32(runtime);
}

std::string JsiPaEngine::ExcludeTag(const std::string& jsonString, const std::string& tagString)
{
    size_t pos = jsonString.find(tagString);
    if (pos == std::string::npos) {
        return jsonString;
    }
    std::string valueString = jsonString.substr(pos);
    pos = valueString.find(":");
    if (pos == std::string::npos) {
        return "";
    }
    size_t valuePos = pos + 1;
    while (valuePos < valueString.size()) {
        if (valueString.at(valuePos) != ' ' && valueString.at(valuePos) != '\t') {
            break;
        }
        valuePos++;
    }
    if (valuePos >= valueString.size()) {
        return "";
    }
    valueString = valueString.substr(valuePos);
    return valueString.substr(0, valueString.size() - 1);
}

std::string JsiPaEngine::IncludeTag(const std::string& jsonString, const std::string& tagString)
{
    std::string result = "{\"" + tagString + "\":";
    result += jsonString;
    result += "}";
    return result;
}

std::shared_ptr<AppExecFwk::PacMap> JsiPaEngine::Call(
    const std::string& method, const std::string& arg, const AppExecFwk::PacMap& pacMap, const CallingInfo& callingInfo)
{
    std::string pacString = const_cast<AppExecFwk::PacMap&>(pacMap).ToString();
    std::string params = ExcludeTag(pacString, "pacmap");
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    std::vector<shared_ptr<JsValue>> argv;
    argv.push_back(runtime->NewString(method));
    argv.push_back(runtime->NewString(arg));
    argv.push_back(runtime->NewString(params));
    auto func = GetPaFunc("call");
    if (func == nullptr) {
        return nullptr;
    }
    shared_ptr<JsValue> retVal = CallFunc(func, argv, callingInfo);
    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine Query FAILED!");
        return nullptr;
    }
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    if (arkJSValue->IsUndefined(runtime)) {
        LOGE("JsiPaEngine Query return value is undefined!");
        return nullptr;
    }
    std::string retStr = IncludeTag(arkJSValue->ToString(runtime), "pacmap");
    auto result = std::make_shared<AppExecFwk::PacMap>();
    if (result == nullptr) {
        LOGE("fail to create PacMap");
        return nullptr;
    }
    result->FromString(retStr);
    return result;
}

int32_t JsiPaEngine::BatchInsert(
    const Uri& uri, const std::vector<OHOS::NativeRdb::ValuesBucket>& values, const CallingInfo& callingInfo)
{
    LOGI("JsiPaEngine BatchInsert");
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    auto nativeEngine = GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, 0);
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    napi_value argColumnsNapiValue = nullptr;
    napi_create_array(env, &argColumnsNapiValue);
    bool isArray = false;
    if (napi_is_array(env, argColumnsNapiValue, &isArray) != napi_ok || !isArray) {
        LOGE("JsiPaEngine create array failed");
        return 0;
    }
    int32_t index = 0;
    for (auto value : values) {
        napi_value result = rdbValueBucketNewInstance_(env, const_cast<OHOS::NativeRdb::ValuesBucket&>(value));
        napi_set_element(env, argColumnsNapiValue, index++, result);
    }

    std::vector<shared_ptr<JsValue>> argv;
    argv.push_back(runtime->NewString(uri.ToString()));
    argv.push_back(NapiValueToJsValue(argColumnsNapiValue));
    auto func = GetPaFunc("batchInsert");
    shared_ptr<JsValue> retVal = CallAsyncFunc(func, argv, callingInfo);
    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine BatchInsert FAILED!");
        return 0;
    }
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    return arkJSValue->ToInt32(runtime);
}

std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet> JsiPaEngine::Query(const Uri& uri,
    const std::vector<std::string>& columns, const OHOS::NativeRdb::DataAbilityPredicates& predicates,
    const CallingInfo& callingInfo)
{
    LOGI("JsiPaEngine Query");
    std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet> resultSet = nullptr;
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    auto nativeEngine = GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, resultSet);
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    napi_value argColumnsNapiValue = nullptr;
    napi_create_array(env, &argColumnsNapiValue);
    bool isArray = false;
    if (napi_is_array(env, argColumnsNapiValue, &isArray) != napi_ok || !isArray) {
        LOGE("JsiPaEngine create array failed");
        return resultSet;
    }
    int32_t index = 0;
    for (auto column : columns) {
        napi_value result = nullptr;
        napi_create_string_utf8(env, column.c_str(), column.length(), &result);
        napi_set_element(env, argColumnsNapiValue, index++, result);
    }

    OHOS::NativeRdb::DataAbilityPredicates* predicatesPtr = new OHOS::NativeRdb::DataAbilityPredicates();
    *predicatesPtr = predicates;
    napi_value argPredicatesNapiValue = dataAbilityPredicatesNewInstance_(env, predicatesPtr);
    if (argPredicatesNapiValue == nullptr) {
        LOGE("JsiPaEngine Query argPredicatesNapiValue is nullptr");
        return resultSet;
    }

    std::vector<shared_ptr<JsValue>> argv;
    argv.push_back(runtime->NewString(uri.ToString()));
    argv.push_back(NapiValueToJsValue(argColumnsNapiValue));
    argv.push_back(NapiValueToJsValue(argPredicatesNapiValue));
    auto func = GetPaFunc("query");
    shared_ptr<JsValue> retVal = CallAsyncFunc(func, argv, callingInfo);

    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine Query FAILED!");
        return resultSet;
    }
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    if (arkJSValue->IsUndefined(runtime)) {
        LOGE("JsiPaEngine Query return value is undefined!");
        return resultSet;
    }

    napi_value napiValue = ArkNativeEngine::ArkValueToNapiValue(env, arkJSValue->GetValue(arkJSRuntime));
    if (napiValue == nullptr) {
        LOGE("JsiPaEngine nativeValue is nullptr");
        return resultSet;
    }
    resultSet = rdbResultSetProxyGetNativeObject_(env, napiValue);
    if (resultSet == nullptr) {
        LOGE("JsiPaEngine AbsSharedResultSet from JS to Native failed");
    }
    return resultSet;
}

int32_t JsiPaEngine::Update(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value,
    const OHOS::NativeRdb::DataAbilityPredicates& predicates, const CallingInfo& callingInfo)
{
    LOGI("JsiPaEngine Update");
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    auto nativeEngine = GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, 0);
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    napi_value argNapiValue = rdbValueBucketNewInstance_(env, const_cast<OHOS::NativeRdb::ValuesBucket&>(value));

    OHOS::NativeRdb::DataAbilityPredicates* predicatesPtr = new OHOS::NativeRdb::DataAbilityPredicates();
    *predicatesPtr = predicates;
    napi_value argPredicatesNapiValue = dataAbilityPredicatesNewInstance_(env, predicatesPtr);
    if (argPredicatesNapiValue == nullptr) {
        LOGE("JsiPaEngine Update argPredicatesNativeValue is nullptr");
        return 0;
    }

    std::vector<shared_ptr<JsValue>> argv;
    argv.push_back(runtime->NewString(uri.ToString()));
    argv.push_back(NapiValueToJsValue(argNapiValue));
    argv.push_back(NapiValueToJsValue(argPredicatesNapiValue));
    auto func = GetPaFunc("update");
    shared_ptr<JsValue> retVal = CallAsyncFunc(func, argv, callingInfo);

    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine Update FAILED!");
        return 0;
    }
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    return arkJSValue->ToInt32(runtime);
}

int32_t JsiPaEngine::Delete(
    const Uri& uri, const OHOS::NativeRdb::DataAbilityPredicates& predicates, const CallingInfo& callingInfo)
{
    LOGI("JsiPaEngine Delete");
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    auto nativeEngine = GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, 0);
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    OHOS::NativeRdb::DataAbilityPredicates* predicatesPtr = new OHOS::NativeRdb::DataAbilityPredicates();
    *predicatesPtr = predicates;
    napi_value argPredicatesNapiValue = dataAbilityPredicatesNewInstance_(env, predicatesPtr);
    if (argPredicatesNapiValue == nullptr) {
        LOGE("JsiPaEngine Delete argPredicatesNativeValue is nullptr");
        return 0;
    }

    std::vector<shared_ptr<JsValue>> argv;
    argv.push_back(runtime->NewString(uri.ToString()));
    argv.push_back(NapiValueToJsValue(argPredicatesNapiValue));
    auto func = GetPaFunc("delete");
    shared_ptr<JsValue> retVal = CallAsyncFunc(func, argv, callingInfo);

    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine Delete FAILED!");
        return 0;
    }
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    return arkJSValue->ToInt32(runtime);
}

std::string JsiPaEngine::GetType(const Uri& uri, const CallingInfo& callingInfo)
{
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    std::vector<shared_ptr<JsValue>> argv;
    argv.push_back(runtime->NewString(uri.ToString()));
    auto func = GetPaFunc("getType");
    shared_ptr<JsValue> retVal = CallAsyncFunc(func, argv, callingInfo);

    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine GetType FAILED!");
        return std::string();
    }
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    return arkJSValue->ToString(runtime);
}

std::vector<std::string> JsiPaEngine::GetFileTypes(
    const Uri& uri, const std::string& mimeTypeFilter, const CallingInfo& callingInfo)
{
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    std::vector<shared_ptr<JsValue>> argv;
    argv.push_back(runtime->NewString(uri.ToString()));
    argv.push_back(runtime->NewString(mimeTypeFilter));
    auto func = GetPaFunc("getFileTypes");
    shared_ptr<JsValue> retVal = CallAsyncFunc(func, argv, callingInfo);

    std::vector<std::string> ret;
    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine GetFileTypes FAILED!");
        return ret;
    }
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    if (!arkJSValue->IsArray(runtime)) {
        LOGE("JsiPaEngine GetFileTypes return not array!");
        return ret;
    }
    int32_t length = arkJSValue->GetArrayLength(runtime);
    LOGI("JsiPaEngine GetFileTypes array length %{public}d", length);
    for (int i = 0; i < length; i++) {
        auto itemVal = arkJSValue->GetProperty(runtime, i);
        ret.push_back(itemVal->ToString(runtime));
    }
    return ret;
}

int32_t JsiPaEngine::OpenFile(const Uri& uri, const std::string& mode, const CallingInfo& callingInfo)
{
    LOGI("JsiPaEngine OpenFile");
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    std::vector<shared_ptr<JsValue>> argv;
    argv.push_back(runtime->NewString(uri.ToString()));
    argv.push_back(runtime->NewString(mode));
    auto func = GetPaFunc("openFile");
    shared_ptr<JsValue> retVal = CallAsyncFunc(func, argv, callingInfo);

    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine OpenFile FAILED!");
        return 0;
    }
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    return arkJSValue->ToInt32(runtime);
}

int32_t JsiPaEngine::OpenRawFile(const Uri& uri, const std::string& mode, const CallingInfo& callingInfo)
{
    LOGI("JsiPaEngine OpenRawFile");
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    std::vector<shared_ptr<JsValue>> argv;
    argv.push_back(runtime->NewString(uri.ToString()));
    argv.push_back(runtime->NewString(mode));
    auto func = GetPaFunc("openRawFile");
    shared_ptr<JsValue> retVal = CallAsyncFunc(func, argv, callingInfo);

    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine OpenRawFile FAILED!");
        return 0;
    }
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    return arkJSValue->ToInt32(runtime);
}

Uri JsiPaEngine::NormalizeUri(const Uri& uri, const CallingInfo& callingInfo)
{
    LOGI("JsiPaEngine NormalizeUri");
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    std::vector<shared_ptr<JsValue>> argv;
    argv.push_back(runtime->NewString(uri.ToString()));
    auto func = GetPaFunc("normalizeUri");
    shared_ptr<JsValue> retVal = CallAsyncFunc(func, argv, callingInfo);

    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine NormalizeUri FAILED!");
        return Uri("");
    }
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    return Uri(arkJSValue->ToString(runtime));
}

Uri JsiPaEngine::DenormalizeUri(const Uri& uri, const CallingInfo& callingInfo)
{
    LOGI("JsiPaEngine DenormalizeUri");
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    std::vector<shared_ptr<JsValue>> argv;
    argv.push_back(runtime->NewString(uri.ToString()));
    auto func = GetPaFunc("denormalizeUri");
    shared_ptr<JsValue> retVal = CallAsyncFunc(func, argv, callingInfo);

    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine DenormalizeUri FAILED!");
        return Uri("");
    }
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    return Uri(arkJSValue->ToString(runtime));
}

sptr<IRemoteObject> JsiPaEngine::OnConnectService(const OHOS::AAFwk::Want& want)
{
    ContainerScope scope(instanceId_);
    LOGI("JsiPaEngine OnConnectService");
    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(GetJsRuntime());
    const std::vector<shared_ptr<JsValue>>& argv = { WantToJsValue(want) };
    auto func = GetPaFunc("onConnect");
    shared_ptr<JsValue> retVal = CallFunc(func, argv);

    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine onConnectService FAILED!");
        return nullptr;
    }

    auto nativeEngine = GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, nullptr);
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    napi_value nativeValue = ArkNativeEngine::ArkValueToNapiValue(env, arkJSValue->GetValue(arkJSRuntime));
    if (nativeValue == nullptr) {
        LOGE("JsiPaEngine nativeValue is nullptr");
        return nullptr;
    }
    auto remoteObj = NAPI_ohos_rpc_getNativeRemoteObject(env, nativeValue);
    return remoteObj;
}

void JsiPaEngine::OnDisconnectService(const OHOS::AAFwk::Want& want)
{
    ContainerScope scope(instanceId_);
    LOGI("JsiPaEngine OnDisconnectService");
    const std::vector<shared_ptr<JsValue>>& argv = { WantToJsValue(want) };
    auto func = GetPaFunc("onDisconnect");
    CallFunc(func, argv);
}

void JsiPaEngine::OnCommand(const OHOS::AAFwk::Want& want, int startId)
{
    ContainerScope scope(instanceId_);
    LOGI("JsiPaEngine OnCommand");
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = { WantToJsValue(want), runtime->NewInt32(startId) };
    auto func = GetPaFunc("onCommand");
    CallFunc(func, argv);
}

void JsiPaEngine::OnCreate(const OHOS::AAFwk::Want& want)
{
    ContainerScope scope(instanceId_);
    shared_ptr<JsRuntime> runtime = GetJsRuntime();

    const std::vector<shared_ptr<JsValue>>& argv = { WantToJsValue(want) };
    auto func = GetPaFunc("onCreate");
    auto result = CallFuncWithDefaultThis(func, argv);
    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException() || result->IsUndefined(runtime)) {
        LOGE("JsiPaEngine CallFunc FAILED!");
        return;
    }

    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(result);
    shared_ptr<JsValue> propertyNames;
    int32_t len = 0;
    if (!arkJSValue->GetPropertyNames(runtime, propertyNames, len)) {
        LOGE("JsiPaEngine StartForm GetPropertyNames error");
        return;
    }
    LOGI("JsiPaEngine onCreate return property num %{public}d", len);

    std::string jsonStr;
    shared_ptr<JsValue> formJsonData = arkJSValue->GetProperty(runtime, "data");
    if (formJsonData != nullptr) {
        jsonStr = formJsonData->ToString(runtime);
        LOGI("Add FormBindingData json:%{public}s", jsonStr.c_str());
    }
    AppExecFwk::FormProviderData formData = AppExecFwk::FormProviderData(jsonStr);
    shared_ptr<JsValue> formImageData = arkJSValue->GetProperty(runtime, "image");
    if (formImageData != nullptr) {
        std::map<std::string, int> rawImageDataMap;
        auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
        auto nativeEngine = GetNativeEngine();
        CHECK_NULL_VOID(nativeEngine);
        napi_env env = reinterpret_cast<napi_env>(nativeEngine);
        napi_value napiValue = ArkNativeEngine::ArkValueToNapiValue(
            env, std::static_pointer_cast<ArkJSValue>(formImageData)->GetValue(arkJSRuntime));
        UnwrapRawImageDataMap(env, napiValue, rawImageDataMap);
        for (const auto& data : rawImageDataMap) {
            formData.AddImageData(data.first, data.second);
        }
    }
    SetFormData(formData);
}

void JsiPaEngine::OnDelete(const int64_t formId)
{
    LOGI("JsiPaEngine OnDelete");
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = { runtime->NewString(std::to_string(formId)) };
    auto func = GetPaFunc("onDestroy");
    CallFuncWithDefaultThis(func, argv);
}

void JsiPaEngine::OnTriggerEvent(const int64_t formId, const std::string& message)
{
    LOGI("JsiPaEngine OnTriggerEvent");
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = { runtime->NewString(std::to_string(formId)),
        runtime->NewString(message) };
    auto func = GetPaFunc("onEvent");
    CallFuncWithDefaultThis(func, argv);
}

void JsiPaEngine::OnUpdate(const int64_t formId)
{
    LOGI("JsiPaEngine OnUpdate");
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = { runtime->NewString(std::to_string(formId)) };
    auto func = GetPaFunc("onUpdate");
    CallFuncWithDefaultThis(func, argv);
}

void JsiPaEngine::OnCastTemptoNormal(const int64_t formId)
{
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = { runtime->NewString(std::to_string(formId)) };
    auto func = GetPaFunc("onCastToNormal");
    CallFuncWithDefaultThis(func, argv);
}

void JsiPaEngine::OnVisibilityChanged(const std::map<int64_t, int32_t>& formEventsMap)
{
    std::string strJsonResult("{");
    for (auto item = formEventsMap.begin(); item != formEventsMap.end(); item++) {
        strJsonResult.append(ToJSONStringInt(std::to_string(item->first), std::to_string(item->second)));
        strJsonResult.append(",");
    }
    strJsonResult = strJsonResult.substr(0, strJsonResult.size() - 1);
    strJsonResult.append("}");
    LOGI("JsiPaEngine strJsonResult = %{public}s", strJsonResult.c_str());

    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = { runtime->ParseJson(strJsonResult) };
    auto func = GetPaFunc("onVisibilityChange");
    CallFuncWithDefaultThis(func, argv);
}

int32_t JsiPaEngine::OnAcquireFormState(const OHOS::AAFwk::Want& want)
{
    shared_ptr<JsRuntime> runtime = GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = { WantToJsValue(want) };
    auto func = GetPaFunc("onAcquireFormState");
    if (func == nullptr) {
        LOGW("no OnAcquireFormState!");
        return (int32_t)AppExecFwk::FormState::DEFAULT;
    }

    auto result = CallFuncWithDefaultThis(func, argv);
    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine CallFunc FAILED!");
        return (int32_t)AppExecFwk::FormState::DEFAULT;
    }

    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(result);
    if (!arkJSValue->IsInt32(runtime)) {
        LOGE("invalid return value!");
        return (int32_t)AppExecFwk::FormState::DEFAULT;
    }

    int32_t formState = arkJSValue->ToInt32(runtime);
    LOGI("JsiPaEngine OnAcquireFormState, formState: %{public}d", formState);
    return formState;
}

bool JsiPaEngine::OnShare(int64_t formId, OHOS::AAFwk::WantParams& wantParams)
{
    auto runtime = GetJsRuntime();
    if (runtime == nullptr) {
        LOGE("JsiPaEngine JsRuntime Get nullptr!");
        return false;
    }

    const std::vector<shared_ptr<JsValue>> argv = { runtime->NewString(std::to_string(formId)) };
    auto func = GetPaFunc("onShareForm");
    if (func == nullptr) {
        func = GetPaFunc("onShare");
    }
    auto result = CallFuncWithDefaultThis(func, argv);
    if (result == nullptr) {
        LOGE("JsiPaEngine Call function result is nullptr!");
        return false;
    }

    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(result);
    if (arkJSValue == nullptr) {
        LOGE("JsiPaEngine JsValue convert failed!");
        return false;
    }

    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime == nullptr) {
        LOGE("JsiPaEngine JSRuntime convert failed!");
        return false;
    }

    if (arkJSRuntime->HasPendingException()) {
        LOGE("JsiPaEngine CallFunc FAILED!");
        return false;
    }

    auto nativeEngine = GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, false);
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    auto napiValue = ArkNativeEngine::ArkValueToNapiValue(env, arkJSValue->GetValue(arkJSRuntime));
    if (napiValue == nullptr) {
        LOGE("JsiPaEngine nativeValue convert failed!");
        return false;
    }
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, napiValue, &valueType);
    if (valueType != napi_object) {
        LOGE("napiValue is not napiObject");
        return false;
    }

    if (!OHOS::AppExecFwk::UnwrapWantParams(env, napiValue, wantParams)) {
        LOGE("%{public}s OnShare UnwrapWantParams failed, return false", __func__);
        return false;
    }
    return true;
}

void JsiPaEngine::PostTask(const std::function<void()>& task, const std::string& name, int64_t delayTime)
{
    if (!jsAbilityRuntime_) {
        LOGE("Ability runtime is invalid.");
        return;
    }

    jsAbilityRuntime_->PostTask(task, name, delayTime);
}

void JsiPaEngine::PostSyncTask(const std::function<void()>& task, const std::string& name)
{
    if (!jsAbilityRuntime_) {
        LOGE("Ability runtime is invalid.");
        return;
    }

    jsAbilityRuntime_->PostSyncTask(task, name);
}

void JsiPaEngine::RemoveTask(const std::string& name)
{
    if (!jsAbilityRuntime_) {
        LOGE("Ability runtime is invalid.");
        return;
    }

    jsAbilityRuntime_->RemoveTask(name);
}
} // namespace OHOS::Ace
