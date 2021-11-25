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

#include "adapter/ohos/entrance/pa_engine/engine/jsi/jsi_pa_engine.h"

#include <dlfcn.h>

#include "form_provider_info.h"
#include "napi/native_node_api.h"
#include "napi_common_ability.h"
#include "napi_common_want.h"
#include "napi_remote_object.h"

#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "frameworks/bridge/js_frontend/engine/common/runtime_constants.h"
#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_value.h"
#include "frameworks/bridge/js_frontend/engine/jsi/jsi_utils.h"

extern const char _binary_paMgmt_abc_start[];
extern const char _binary_paMgmt_abc_end[];

namespace OHOS::Ace {
namespace {
#ifdef APP_USE_ARM
const std::string ARK_DEBUGGER_LIB_PATH = "/system/lib/libark_debugger.z.so";
#else
const std::string ARK_DEBUGGER_LIB_PATH = "/system/lib64/libark_debugger.z.so";
#endif

int PrintLog(int id, int level, const char* tag, const char* fmt, const char* message)
{
    switch (JsLogLevel(level - 3)) {
        case JsLogLevel::INFO:
            LOGI("%{public}s::%{public}s", tag, message);
            break;
        case JsLogLevel::WARNING:
            LOGW("%{public}s::%{public}s", tag, message);
            break;
        case JsLogLevel::ERROR:
            LOGE("%{public}s::%{public}s", tag, message);
            break;
        case JsLogLevel::DEBUG:
            LOGD("%{public}s::%{public}s", tag, message);
            break;
        default:
            LOGF("%{public}s::%{public}s", tag, message);
            break;
    }
    return 0;
}

std::string ParseLogContent(const std::vector<std::string>& params)
{
    std::string ret;
    if (params.empty()) {
        return ret;
    }
    std::string formatStr = params[0];
    int32_t size = params.size();
    int32_t len = formatStr.size();
    int32_t pos = 0;
    int32_t count = 1;
    for (; pos < len; ++pos) {
        if (count >= size) {
            break;
        }
        if (formatStr[pos] == '%') {
            if (pos + 1 >= len) {
                break;
            }
            switch (formatStr[pos + 1]) {
                case 's':
                case 'j':
                case 'd':
                case 'O':
                case 'o':
                case 'i':
                case 'f':
                case 'c':
                    ret += params[count++];
                    ++pos;
                    break;
                case '%':
                    ret += formatStr[pos];
                    ++pos;
                    break;
                default:
                    ret += formatStr[pos];
                    break;
            }
        } else {
            ret += formatStr[pos];
        }
    }
    if (pos < len) {
        ret += formatStr.substr(pos, len - pos);
    }
    return ret;
}

std::string GetLogContent(
    const shared_ptr<JsRuntime>& runtime, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    if (argc == 1) {
        return argv[0]->ToString(runtime);
    }
    std::vector<std::string> params;
    for (int32_t i = 0; i < argc; ++i) {
        params.emplace_back(argv[i]->ToString(runtime));
    }
    return ParseLogContent(params);
}

shared_ptr<JsValue> AppLogPrint(
    const shared_ptr<JsRuntime>& runtime, JsLogLevel level, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    // Should have at least 1 parameters.
    if (argc == 0) {
        LOGE("the arg is error");
        return runtime->NewUndefined();
    }
    std::string content = GetLogContent(runtime, argv, argc);
    switch (level) {
        case JsLogLevel::DEBUG:
            APP_LOGD("app Log: %{public}s", content.c_str());
            break;
        case JsLogLevel::INFO:
            APP_LOGI("app Log: %{public}s", content.c_str());
            break;
        case JsLogLevel::WARNING:
            APP_LOGW("app Log: %{public}s", content.c_str());
            break;
        case JsLogLevel::ERROR:
            APP_LOGE("app Log: %{public}s", content.c_str());
            break;
    }

    return runtime->NewUndefined();
}

// native implementation for js function: console.debug()
shared_ptr<JsValue> AppDebugLogPrint(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return AppLogPrint(runtime, JsLogLevel::DEBUG, argv, argc);
}

// native implementation for js function: console.info()
shared_ptr<JsValue> AppInfoLogPrint(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return AppLogPrint(runtime, JsLogLevel::INFO, argv, argc);
}

// native implementation for js function: console.warn()
shared_ptr<JsValue> AppWarnLogPrint(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return AppLogPrint(runtime, JsLogLevel::WARNING, argv, argc);
}

// native implementation for js function: console.error()
shared_ptr<JsValue> AppErrorLogPrint(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return AppLogPrint(runtime, JsLogLevel::ERROR, argv, argc);
}

// native implementation for js function: ace.onCreateFinish()
shared_ptr<JsValue> JsOnCreateFinish(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    LOGD("JsOnCreateFinish");
    return runtime->NewUndefined();
}

inline std::string ToJSONStringInt(std::string sKey, std::string sValue)
{
    char szDoubleQutoes[] = "\"";
    char szColon[] = ":";
    std::string strResult;
    strResult.append(szDoubleQutoes);
    strResult.append(sKey);
    strResult.append(szDoubleQutoes);

    strResult.append(szColon);
    strResult.append(sValue);
    return strResult;
}

inline std::string ToJSONString(std::string sKey, std::string sValue)
{
    char szDoubleQutoes[] = "\"";
    char szColon[] = ":";
    std::string strResult;
    strResult.append(szDoubleQutoes);
    strResult.append(sKey);
    strResult.append(szDoubleQutoes);

    strResult.append(szColon);
    strResult.append(szDoubleQutoes);
    strResult.append(sValue);
    strResult.append(szDoubleQutoes);
    return strResult;
}
} // namespace

// -----------------------
// Start JsiPaEngineInstance
// -----------------------
JsiPaEngineInstance::~JsiPaEngineInstance()
{
    if (runtime_) {
        runtime_->RegisterUncaughtExceptionHandler(nullptr);
        // reset runtime in utils
        JsiUtils::SetRuntime(nullptr, runtime_);
        runtime_->Reset();
    }
    runtime_.reset();
    runtime_ = nullptr;
}

void JsiPaEngineInstance::RegisterConsoleModule()
{
    ACE_SCOPED_TRACE("JsiPaEngineInstance::RegisterConsoleModule");
    LOGD("JsiPaEngineInstance RegisterConsoleModule");
    shared_ptr<JsValue> global = runtime_->GetGlobal();

    // app log method
    shared_ptr<JsValue> consoleObj = runtime_->NewObject();
    consoleObj->SetProperty(runtime_, "log", runtime_->NewFunction(AppDebugLogPrint));
    consoleObj->SetProperty(runtime_, "debug", runtime_->NewFunction(AppDebugLogPrint));
    consoleObj->SetProperty(runtime_, "info", runtime_->NewFunction(AppInfoLogPrint));
    consoleObj->SetProperty(runtime_, "warn", runtime_->NewFunction(AppWarnLogPrint));
    consoleObj->SetProperty(runtime_, "error", runtime_->NewFunction(AppErrorLogPrint));
    global->SetProperty(runtime_, "console", consoleObj);
}

void JsiPaEngineInstance::RegisterPaModule()
{
    ACE_SCOPED_TRACE("JsiPaEngineInstance::RegisterAceModule");
    LOGD("JsiPaEngineInstance RegisterAceModule");

    shared_ptr<JsValue> aceObj = runtime_->NewObject();
    if (!aceObj) {
        LOGE("RegisterPaModule failed. aceObj is null");
        return;
    }
    if (!aceObj->SetProperty(runtime_, "onCreateFinish", runtime_->NewFunction(JsOnCreateFinish))) {
        LOGE("RegisterPaModule onCreateFinish failed.");
    }

    shared_ptr<JsValue> global = runtime_->GetGlobal();
    if (!global->SetProperty(runtime_, "ace", aceObj)) {
        LOGE("RegisterPaModule ace failed.");
    }
}

void JsiPaEngineInstance::EvaluateJsCode()
{
    ACE_SCOPED_TRACE("JsiPaEngineInstance::EvaluateJsCode");
    LOGD("JsiPaEngineInstance EvaluateJsCode");

    JsiUtils::SetCurrentState(JsErrorType::LOAD_JS_BUNDLE_ERROR, instanceId_);
    // load jsfwk
    if (!runtime_->ExecuteJsBin("/system/etc/strip.native.min.abc")) {
        LOGE("Failed to load js framework!");
    }

    // load paMgmt.js
    bool result = runtime_->EvaluateJsCode(
        (uint8_t *)_binary_paMgmt_abc_start, _binary_paMgmt_abc_end - _binary_paMgmt_abc_start);
    if (!result) {
        LOGE("EvaluateJsCode paMgmt abc failed");
    }
}

bool JsiPaEngineInstance::InitJsEnv(bool debuggerMode, const std::unordered_map<std::string, void*>& extraNativeObject)
{
    ACE_SCOPED_TRACE("JsiPaEngineInstance::InitJsEnv");
    runtime_.reset(new ArkJSRuntime());
    if (runtime_ == nullptr) {
        LOGE("JsiPaEngineInstance cannot allocate JSI JSRuntime");
        EventReport::SendJsException(JsExcepType::JS_ENGINE_INIT_ERR);
        return false;
    }

    runtime_->SetLogPrint(PrintLog);
    std::string libraryPath = "";
    if (debuggerMode) {
        libraryPath = ARK_DEBUGGER_LIB_PATH;
    }
    if (!runtime_->Initialize(libraryPath)) {
        LOGE("JsiPaEngineInstance initialize runtime failed");
        return false;
    }

    // set new runtime
    JsiUtils::SetRuntime(runtime_);

#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
    for (const auto& [key, value] : extraNativeObject) {
        shared_ptr<JsValue> nativeValue = runtime_->NewNativePointer(value);
        runtime_->GetGlobal()->SetProperty(runtime_, key, nativeValue);
    }
#endif

    // Register pa native functions
    RegisterPaModule();
    RegisterConsoleModule();
    // load abc file
    EvaluateJsCode();

    runtime_->SetEmbedderData(this);
    runtime_->RegisterUncaughtExceptionHandler(JsiUtils::ReportJsErrorEvent);
    LOGI("JsiPaEngineInstance InitJsEnv success");
    return true;
}

bool JsiPaEngineInstance::FireJsEvent(const std::string& eventStr)
{
    LOGI("JsiPaEngineInstance FireJsEvent");

    std::vector<shared_ptr<JsValue>> argv;
    argv.push_back(runtime_->NewString(std::to_string(instanceId_)));
    shared_ptr<JsValue> var1 = runtime_->ParseJson(eventStr);
    argv.push_back(var1);

    shared_ptr<JsValue> global = runtime_->GetGlobal();
    shared_ptr<JsValue> func = global->GetProperty(runtime_, "callJS");

    if (!func->IsFunction(runtime_)) {
        LOGE("\"callJs\" is not a function!");
        return false;
    }

    JsiUtils::SetCurrentState(JsErrorType::FIRE_EVENT_ERROR, instanceId_);
    func->Call(runtime_, global, argv, argv.size());
    return true;
}

void JsiPaEngineInstance::CallJs(const std::string& callbackId, const std::string& args, bool keepAlive, bool isGlobal)
{
    LOGI("JsiPaEngineInstance CallJs");
    std::string keepAliveStr = keepAlive ? "true" : "false";
    std::string callBuff = std::string("[{\"args\": [\"")
                               .append(callbackId)
                               .append("\",")
                               .append(args)
                               .append(",")
                               .append(keepAliveStr)
                               .append("], \"method\":\"callback\"}]");
    LOGD("CallJs string: %{private}s", callBuff.c_str());

    std::vector<shared_ptr<JsValue>> argv;
    argv.push_back(runtime_->NewString(std::to_string(instanceId_)));
    argv.push_back(runtime_->ParseJson(callBuff));

    shared_ptr<JsValue> global = runtime_->GetGlobal();
    shared_ptr<JsValue> func = global->GetProperty(runtime_, "callJS");
    if (!func->IsFunction(runtime_)) {
        LOGE("\"callJs\" is not a function!");
        return;
    }
    func->Call(runtime_, global, argv, argv.size());
}

bool JsiPaEngineInstance::CallPlatformFunction(const std::string& channel, std::vector<uint8_t>&& data, int32_t id)
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

bool JsiPaEngineInstance::PluginErrorCallback(int32_t callbackId, int32_t errorCode, std::string&& errorMessage)
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

RefPtr<BackendDelegate> JsiPaEngineInstance::GetDelegate() const
{
    return backendDelegate_;
}

std::shared_ptr<JsRuntime> JsiPaEngineInstance::GetJsRuntime() const
{
    return runtime_;
}

void JsiPaEngineInstance::SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher)
{
    dispatcher_ = dispatcher;
}

// -----------------------
// Start JsiPaEngine
// -----------------------
JsiPaEngine::~JsiPaEngine()
{
    UnloadLibrary();
    engineInstance_->GetDelegate()->RemoveTaskObserver();
    if (nativeEngine_ != nullptr) {
        nativeEngine_->CancelCheckUVLoop();
        delete nativeEngine_;
    }
}

bool JsiPaEngine::Initialize(const RefPtr<BackendDelegate>& delegate)
{
    ACE_SCOPED_TRACE("JsiPaEngine::Initialize");
    LOGD("JsiPaEngine initialize");
    engineInstance_ = AceType::MakeRefPtr<JsiPaEngineInstance>(delegate, instanceId_);
    bool result = engineInstance_->InitJsEnv(IsDebugVersion() && NeedDebugBreakPoint(), GetExtraNativeObject());
    if (!result) {
        LOGE("JsiPaEngine Initialize, init js env failed");
        return false;
    }

    auto runtime = engineInstance_->GetJsRuntime();
    auto vm = std::static_pointer_cast<ArkJSRuntime>(runtime)->GetEcmaVm();
    if (vm == nullptr) {
        LOGE("JsiPaEngine Initialize, vm is null");
        return false;
    }

    LoadLibrary();

    nativeEngine_ = new ArkNativeEngine(const_cast<EcmaVM*>(vm), static_cast<void*>(this));
    ACE_DCHECK(delegate);
    delegate->AddTaskObserver([nativeEngine = nativeEngine_]() {
        nativeEngine->Loop(LOOP_NOWAIT);
    });
    SetPostTask(nativeEngine_);
    nativeEngine_->CheckUVLoop();
    return true;
}

void JsiPaEngine::SetPostTask(NativeEngine* nativeEngine)
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
            if (nativeEngine == nullptr) {
                return;
            }
            nativeEngine->Loop(LOOP_NOWAIT, needSync);
        });
    };
    nativeEngine_->SetPostTask(postTask);
}

void JsiPaEngine::LoadJs(const std::string& url, const OHOS::AAFwk::Want& want)
{
    ACE_SCOPED_TRACE("JsiPaEngine::LoadJs");
    LOGI("JsiPaEngine LoadJs: %{private}s", url.c_str());

    ACE_DCHECK(engineInstance_);
    auto runtime = engineInstance_->GetJsRuntime();
    auto delegate = engineInstance_->GetDelegate();
    JsiUtils::SetCurrentState(JsErrorType::LOAD_JS_BUNDLE_ERROR, instanceId_);

    // js file to abc file and execute abc file
    const char js_ext[] = ".js";
    const char bin_ext[] = ".abc";
    auto pos = url.rfind(js_ext);
    if (pos != std::string::npos && pos == url.length() - (sizeof(js_ext) - 1)) {
        std::string urlName = url.substr(0, pos) + bin_ext;
        std::string assetBasePath = delegate->GetAssetPath(urlName);
        std::string assetPath = assetBasePath.append(urlName);
        LOGI("assetPath is: %{private}s", assetPath.c_str());
        if (!runtime->ExecuteJsBin(assetPath)) {
            LOGE("ExecuteJsBin %{private}s failed.", urlName.c_str());
            return;
        }

        // only ace1.0 need
        shared_ptr<JsValue> mainEntryFunc = runtime->GetGlobal()->GetProperty(runtime, "___mainEntry___");
        if (mainEntryFunc->IsFunction(runtime)) {
            LOGI("JsiPaEngine call mainEntryFunc");
            runtime->GetGlobal()->SetProperty(runtime, "___mainEntry___", runtime->NewUndefined());
            const std::vector<shared_ptr<JsValue>>& argv = { runtime->GetGlobal() };
            shared_ptr<JsValue> retVal = CallFunc(mainEntryFunc, argv);
            auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
            if (arkJSValue->IsException(runtime)) {
                LOGE("JsiPaEngine call mainEntryFunc FAILED!");
            }
        }
    }

    // call start pa func
    BackendType type = delegate->GetType();
    if (type == BackendType::SERVICE) {
        StartService();
    } else if (type == BackendType::DATA) {
        StartData();
    } else if (type == BackendType::FORM) {
        StartForm(want);
    } else {
        LOGE("backend type not support");
    }
}

void JsiPaEngine::LoadLibrary()
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

void JsiPaEngine::UnloadLibrary()
{
    dlclose(libRdb_);
    dlclose(libDataAbility_);
}

shared_ptr<JsValue> JsiPaEngine::GetPaFunc(const std::string& funcName)
{
    LOGI("JsiPaEngine GetPaFunc funcName: %{public}s", funcName.c_str());
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
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
    const std::vector<shared_ptr<JsValue>>& argv = { };
    return CallFunc(func, argv);
}

shared_ptr<JsValue> JsiPaEngine::CallFunc(const shared_ptr<JsValue>& func,
    const std::vector<shared_ptr<JsValue>>& argv)
{
    LOGD("JsiPaEngine CallFunc");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
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
    return func->Call(runtime, global, argv, argv.size());
}

shared_ptr<JsValue> JsiPaEngine::NativeValueToJsValue(NativeValue* nativeValue)
{
    ACE_DCHECK(engineInstance_);
    if (nativeValue == nullptr) {
        LOGE("nativeValue is nullptr!");
        return engineInstance_->GetJsRuntime()->NewUndefined();
    }
    Global<JSValueRef> globalRef = *nativeValue;
    auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(engineInstance_->GetJsRuntime());
    return std::make_shared<ArkJSValue>(arkRuntime, globalRef.ToLocal(arkRuntime->GetEcmaVm()));
}

shared_ptr<JsValue> JsiPaEngine::WantToJsValue(const OHOS::AAFwk::Want& want)
{
    napi_value napiWant = OHOS::AppExecFwk::WrapWant(reinterpret_cast<napi_env>(nativeEngine_), want);
    NativeValue* nativeWant = reinterpret_cast<NativeValue*>(napiWant);
    return NativeValueToJsValue(nativeWant);
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

    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();

    const std::shared_ptr<AppExecFwk::AbilityInfo> abilityInfo =
        reinterpret_cast<Ability*>(it->second)->GetAbilityInfo();
    const AppExecFwk::AbilityInfo abilityInfoInstance = *(abilityInfo.get());
    napi_value abilityInfoNapi =
        AppExecFwk::ConvertAbilityInfo(reinterpret_cast<napi_env>(nativeEngine_), abilityInfoInstance);
    NativeValue* abilityInfoNative = reinterpret_cast<NativeValue*>(abilityInfoNapi);
    const std::vector<shared_ptr<JsValue>>& argv = { NativeValueToJsValue(abilityInfoNative) };

    auto func = GetPaFunc("onInitialized");
    CallFunc(func, argv);
}

void JsiPaEngine::StartForm(const OHOS::AAFwk::Want& want)
{
    LOGI("JsiPaEngine StartForm");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();

    const std::vector<shared_ptr<JsValue>>& argv = { WantToJsValue(want) };
    auto func = GetPaFunc("onCreate");
    auto result = CallFunc(func, argv);
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(result);
    if (arkJSValue->IsException(runtime)) {
        LOGE("JsiPaEngine CallFunc FAILED!");
        return;
    }

    shared_ptr<JsValue> propertyNames;
    int32_t len = 0;
    if (!arkJSValue->GetPropertyNames(runtime, propertyNames, len)) {
        LOGE("JsiPaEngine StartForm GetPropertyNames error");
        return;
    }
    LOGI("JsiPaEngine onCreate return property num %{public}d", len);

    std::string jsonStr = "{";
    std::string valueStr = "";
    for (int32_t i = 0; i < len; i++) {
        shared_ptr<JsValue> key = propertyNames->GetElement(runtime, i);
        if (key == nullptr) {
            LOGW("JsiPaEngine key is null. Ignoring!");
            continue;
        }
        std::string keyStr = key->ToString(runtime);
        shared_ptr<JsValue> value = arkJSValue->GetProperty(runtime, key);
        if (value == nullptr) {
            LOGW("JsiPaEngine value is null. Ignoring!");
            continue;
        }
        std::string valStr = value->ToString(runtime);
        LOGI("JsiPaEngine onCreate return key:%{public}s value:%{public}s", keyStr.c_str(), valueStr.c_str());
        jsonStr.append(ToJSONString(keyStr, valueStr));
        if (i != len - 1) {
            jsonStr.append(",");
        }
    }
    jsonStr.append("}");
    LOGI("JsiPaEngine jsonStr:%{public}s", jsonStr.c_str());

    AppExecFwk::FormProviderData formData = AppExecFwk::FormProviderData(jsonStr);
    SetFormData(formData);

    len = valueStr.length();
    char* image = (char*)malloc((len + 1) * sizeof(char));
    if (image) {
        valueStr.copy(image, len, 0);
        formData.AddImageData("image1", image);
        LOGI("JsiPaEngine image.size:%{public}d", len);
    }
    // free(pImage); // image need be freed by FormProviderData;
}

RefPtr<GroupJsBridge> JsiPaEngine::GetGroupJsBridge()
{
    return nullptr;
}

void JsiPaEngine::SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher)
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetJsMessageDispatcher(dispatcher);
}

void JsiPaEngine::FireAsyncEvent(const std::string& eventId, const std::string& param)
{
    LOGD("JsiPaEngine FireAsyncEvent");
    std::string callBuf = std::string("[{\"args\": [\"")
                              .append(eventId)
                              .append("\",")
                              .append(param)
                              .append("], \"method\":\"fireEvent\"}]");
    LOGD("FireASyncEvent string: %{private}s", callBuf.c_str());

    ACE_DCHECK(engineInstance_);
    if (!engineInstance_->FireJsEvent(callBuf.c_str())) {
        LOGE("Js Engine FireSyncEvent FAILED!");
    }
}

void JsiPaEngine::FireSyncEvent(const std::string& eventId, const std::string& param)
{
    LOGD("JsiPaEngine FireSyncEvent");
    std::string callBuf = std::string("[{\"args\": [\"")
                              .append(eventId)
                              .append("\",")
                              .append(param)
                              .append("], \"method\":\"fireEventSync\"}]");
    LOGD("FireSyncEvent string: %{private}s", callBuf.c_str());

    ACE_DCHECK(engineInstance_);
    if (!engineInstance_->FireJsEvent(callBuf.c_str())) {
        LOGE("Js Engine FireSyncEvent FAILED!");
    }
}

void JsiPaEngine::DestroyApplication(const std::string& packageName)
{
    LOGI("JsiPaEngine DestroyApplication");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = { runtime->NewString(packageName) };
    auto func = GetPaFunc("onStop");
    CallFunc(func, argv);
}

void JsiPaEngine::OnCommandApplication(const std::string& intent, int startId)
{
    LOGI("JsiPaEngine OnCommandApplication");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = {
        runtime->NewString(intent),
        runtime->NewInt32(startId)
    };
    auto func = GetPaFunc("onCommand");
    CallFunc(func, argv);
}

int32_t JsiPaEngine::Insert(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value)
{
    LOGI("JsiPaEngine Insert");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    napi_env env = reinterpret_cast<napi_env>(nativeEngine_);
    napi_value argNapiValue = rdbValueBucketNewInstance_(env, const_cast<OHOS::NativeRdb::ValuesBucket&>(value));
    NativeValue* argNapiNativeValue = reinterpret_cast<NativeValue*>(argNapiValue);
    const std::vector<shared_ptr<JsValue>>& argv = {
        runtime->NewString(uri.ToString()),
        NativeValueToJsValue(argNapiNativeValue)
    };
    auto func = GetPaFunc("insert");
    shared_ptr<JsValue> retVal = CallFunc(func, argv);

    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    if (arkJSValue->IsException(runtime)) {
        LOGE("JsiPaEngine Insert FAILED!");
        return 0;
    }
    return arkJSValue->ToInt32(runtime);
}

int32_t JsiPaEngine::BatchInsert(const Uri& uri, const std::vector<OHOS::NativeRdb::ValuesBucket>& values)
{
    LOGI("JsiPaEngine BatchInsert");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();

    napi_env env = reinterpret_cast<napi_env>(nativeEngine_);
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
    NativeValue* argColumnsNativeValue = reinterpret_cast<NativeValue*>(argColumnsNapiValue);

    const std::vector<shared_ptr<JsValue>>& argv = {
        runtime->NewString(uri.ToString()),
        NativeValueToJsValue(argColumnsNativeValue)
    };
    auto func = GetPaFunc("batchInsert");
    shared_ptr<JsValue> retVal = CallFunc(func, argv);

    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    if (arkJSValue->IsException(runtime)) {
        LOGE("JsiPaEngine BatchInsert FAILED!");
        return 0;
    }
    return arkJSValue->ToInt32(runtime);
}

std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet> JsiPaEngine::Query(
    const Uri& uri, const std::vector<std::string>& columns, const OHOS::NativeRdb::DataAbilityPredicates& predicates)
{
    LOGI("JsiPaEngine Query");
    ACE_DCHECK(engineInstance_);
    std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet> resultSet = nullptr;
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();

    napi_env env = reinterpret_cast<napi_env>(nativeEngine_);
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
    NativeValue* argColumnsNativeValue = reinterpret_cast<NativeValue*>(argColumnsNapiValue);

    OHOS::NativeRdb::DataAbilityPredicates* predicatesPtr = new OHOS::NativeRdb::DataAbilityPredicates();
    *predicatesPtr = predicates;
    napi_value argPredicatesNapiValue = dataAbilityPredicatesNewInstance_(env, predicatesPtr);
    NativeValue* argPredicatesNativeValue = reinterpret_cast<NativeValue*>(argPredicatesNapiValue);
    if (argPredicatesNativeValue == nullptr) {
        LOGE("JsiPaEngine Query argPredicatesNativeValue is nullptr");
        return resultSet;
    }

    const std::vector<shared_ptr<JsValue>>& argv = {
        runtime->NewString(uri.ToString()),
        NativeValueToJsValue(argColumnsNativeValue),
        NativeValueToJsValue(argPredicatesNativeValue)
    };
    auto func = GetPaFunc("query");
    shared_ptr<JsValue> retVal = CallFunc(func, argv);

    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    if (arkJSValue->IsException(runtime)) {
        LOGE("JsiPaEngine Query FAILED!");
        return resultSet;
    }
    if (arkJSValue->IsUndefined(runtime)) {
        LOGE("JsiPaEngine Query return value is undefined!");
        return resultSet;
    }

    auto arkJsRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    NativeValue* nativeValue = ArkNativeEngine::ArkValueToNativeValue(
        nativeEngine_, arkJSValue->GetValue(arkJsRuntime));
    if (nativeValue == nullptr) {
        LOGE("JsiPaEngine nativeValue is nullptr");
        return resultSet;
    }
    auto nativeObject = rdbResultSetProxyGetNativeObject_(env, reinterpret_cast<napi_value>(nativeValue));
    if (nativeObject == nullptr) {
        LOGE("JsiPaEngine AbsSharedResultSet from JS to Native failed");
        return resultSet;
    }

    resultSet.reset(nativeObject);
    return resultSet;
}

int32_t JsiPaEngine::Update(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value,
    const OHOS::NativeRdb::DataAbilityPredicates& predicates)
{
    LOGI("JsiPaEngine Update");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();

    napi_env env = reinterpret_cast<napi_env>(nativeEngine_);
    napi_value argNapiValue = rdbValueBucketNewInstance_(env, const_cast<OHOS::NativeRdb::ValuesBucket&>(value));
    NativeValue* argNapiNativeValue = reinterpret_cast<NativeValue*>(argNapiValue);

    OHOS::NativeRdb::DataAbilityPredicates* predicatesPtr = new OHOS::NativeRdb::DataAbilityPredicates();
    *predicatesPtr = predicates;
    napi_value argPredicatesNapiValue = dataAbilityPredicatesNewInstance_(env, predicatesPtr);
    NativeValue* argPredicatesNativeValue = reinterpret_cast<NativeValue*>(argPredicatesNapiValue);
    if (argPredicatesNativeValue == nullptr) {
        LOGE("JsiPaEngine Update argPredicatesNativeValue is nullptr");
        return 0;
    }

    const std::vector<shared_ptr<JsValue>>& argv = {
        runtime->NewString(uri.ToString()),
        NativeValueToJsValue(argNapiNativeValue),
        NativeValueToJsValue(argPredicatesNativeValue)
    };
    auto func = GetPaFunc("update");
    shared_ptr<JsValue> retVal = CallFunc(func, argv);

    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    if (arkJSValue->IsException(runtime)) {
        LOGE("JsiPaEngine Update FAILED!");
        return 0;
    }
    return arkJSValue->ToInt32(runtime);
}

int32_t JsiPaEngine::Delete(const Uri& uri, const OHOS::NativeRdb::DataAbilityPredicates& predicates)
{
    LOGI("JsiPaEngine Delete");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();

    napi_env env = reinterpret_cast<napi_env>(nativeEngine_);
    OHOS::NativeRdb::DataAbilityPredicates* predicatesPtr = new OHOS::NativeRdb::DataAbilityPredicates();
    *predicatesPtr = predicates;
    napi_value argPredicatesNapiValue = dataAbilityPredicatesNewInstance_(env, predicatesPtr);
    NativeValue* argPredicatesNativeValue = reinterpret_cast<NativeValue*>(argPredicatesNapiValue);
    if (argPredicatesNativeValue == nullptr) {
        LOGE("JsiPaEngine Delete argPredicatesNativeValue is nullptr");
        return 0;
    }
    const std::vector<shared_ptr<JsValue>>& argv = {
        runtime->NewString(uri.ToString()),
        NativeValueToJsValue(argPredicatesNativeValue)
    };
    auto func = GetPaFunc("delete");
    shared_ptr<JsValue> retVal = CallFunc(func, argv);

    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    if (arkJSValue->IsException(runtime)) {
        LOGE("JsiPaEngine Delete FAILED!");
        return 0;
    }
    return arkJSValue->ToInt32(runtime);
}

std::string JsiPaEngine::GetType(const Uri& uri)
{
    LOGI("JsiPaEngine GetType");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = { runtime->NewString(uri.ToString()) };
    auto func = GetPaFunc("getType");
    shared_ptr<JsValue> retVal = CallFunc(func, argv);

    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    if (arkJSValue->IsException(runtime)) {
        LOGE("JsiPaEngine GetType FAILED!");
        return std::string();
    }
    return arkJSValue->ToString(runtime);
}

std::vector<std::string> JsiPaEngine::GetFileTypes(const Uri& uri, const std::string& mimeTypeFilter)
{
    LOGI("JsiPaEngine GetFileTypes");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = {
        runtime->NewString(uri.ToString()),
        runtime->NewString(mimeTypeFilter)
    };
    auto func = GetPaFunc("getFileTypes");
    shared_ptr<JsValue> retVal = CallFunc(func, argv);

    std::vector<std::string> ret;
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    if (arkJSValue->IsException(runtime)) {
        LOGE("JsiPaEngine GetFileTypes FAILED!");
        return ret;
    }
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

int32_t JsiPaEngine::OpenFile(const Uri& uri, const std::string& mode)
{
    LOGI("JsiPaEngine OpenFile");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = {
        runtime->NewString(uri.ToString()),
        runtime->NewString(mode)
    };
    auto func = GetPaFunc("openFile");
    shared_ptr<JsValue> retVal = CallFunc(func, argv);

    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    if (arkJSValue->IsException(runtime)) {
        LOGE("JsiPaEngine OpenFile FAILED!");
        return 0;
    }
    return arkJSValue->ToInt32(runtime);
}

int32_t JsiPaEngine::OpenRawFile(const Uri& uri, const std::string& mode)
{
    LOGI("JsiPaEngine OpenRawFile");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = {
        runtime->NewString(uri.ToString()),
        runtime->NewString(mode)
    };
    auto func = GetPaFunc("openRawFile");
    shared_ptr<JsValue> retVal = CallFunc(func, argv);

    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    if (arkJSValue->IsException(runtime)) {
        LOGE("JsiPaEngine OpenRawFile FAILED!");
        return 0;
    }
    return arkJSValue->ToInt32(runtime);
}

Uri JsiPaEngine::NormalizeUri(const Uri& uri)
{
    LOGI("JsiPaEngine NormalizeUri");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = { runtime->NewString(uri.ToString()) };
    auto func = GetPaFunc("normalizeUri");
    shared_ptr<JsValue> retVal = CallFunc(func, argv);

    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    if (arkJSValue->IsException(runtime)) {
        LOGE("JsiPaEngine NormalizeUri FAILED!");
        return Uri("");
    }
    return Uri(arkJSValue->ToString(runtime));
}

Uri JsiPaEngine::DenormalizeUri(const Uri& uri)
{
    LOGI("JsiPaEngine DenormalizeUri");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = { runtime->NewString(uri.ToString()) };
    auto func = GetPaFunc("denormalizeUri");
    shared_ptr<JsValue> retVal = CallFunc(func, argv);

    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    if (arkJSValue->IsException(runtime)) {
        LOGE("JsiPaEngine DenormalizeUri FAILED!");
        return Uri("");
    }
    return Uri(arkJSValue->ToString(runtime));
}

sptr<IRemoteObject> JsiPaEngine::OnConnectService(const OHOS::AAFwk::Want& want)
{
    LOGI("JsiPaEngine OnConnectService");
    ACE_DCHECK(engineInstance_);
    auto arkJsRuntime = std::static_pointer_cast<ArkJSRuntime>(engineInstance_->GetJsRuntime());
    const std::vector<shared_ptr<JsValue>>& argv = { WantToJsValue(want) };
    auto func = GetPaFunc("onConnect");
    shared_ptr<JsValue> retVal = CallFunc(func, argv);

    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(retVal);
    if (arkJSValue->IsException(arkJsRuntime)) {
        LOGE("JsiPaEngine onConnectService FAILED!");
        return nullptr;
    }

    NativeValue* nativeValue = ArkNativeEngine::ArkValueToNativeValue(
        nativeEngine_, arkJSValue->GetValue(arkJsRuntime));
    if (nativeValue == nullptr) {
        LOGE("JsiPaEngine nativeValue is nullptr");
        return nullptr;
    }
    auto remoteObj = NAPI_ohos_rpc_getNativeRemoteObject(
        reinterpret_cast<napi_env>(nativeEngine_), reinterpret_cast<napi_value>(nativeValue));
    return remoteObj;
}

void JsiPaEngine::OnDisconnectService(const OHOS::AAFwk::Want& want)
{
    LOGI("JsiPaEngine OnDisconnectService");
    const std::vector<shared_ptr<JsValue>>& argv = { WantToJsValue(want) };
    auto func = GetPaFunc("onDisconnect");
    CallFunc(func, argv);
}

void JsiPaEngine::OnCommand(const OHOS::AAFwk::Want &want, int startId)
{
    LOGI("JsiPaEngine OnCommand");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = {
        WantToJsValue(want),
        runtime->NewInt32(startId)
    };
    auto func = GetPaFunc("onCommand");
    CallFunc(func, argv);
}

void JsiPaEngine::OnDelete(const int64_t formId)
{
    LOGI("JsiPaEngine OnDelete");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = { runtime->NewInt32(formId) };
    auto func = GetPaFunc("onDelete");
    CallFunc(func, argv);
}

void JsiPaEngine::OnTriggerEvent(const int64_t formId, const std::string& message)
{
    LOGI("JsiPaEngine OnTriggerEvent");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = {
        runtime->NewInt32(formId),
        runtime->NewString(message)
    };
    auto func = GetPaFunc("onTriggerEvent");
    CallFunc(func, argv);
}

void JsiPaEngine::OnUpdate(const int64_t formId)
{
    LOGI("JsiPaEngine OnUpdate");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = { runtime->NewInt32(formId) };
    auto func = GetPaFunc("onUpdate");
    CallFunc(func, argv);
}

void JsiPaEngine::OnCastTemptoNormal(const int64_t formId)
{
    LOGI("JsiPaEngine OnCastTemptoNormal");
    ACE_DCHECK(engineInstance_);
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = { runtime->NewInt32(formId) };
    auto func = GetPaFunc("onCastTemp");
    CallFunc(func, argv);
}

void JsiPaEngine::OnVisibilityChanged(const std::map<int64_t, int32_t>& formEventsMap)
{
    LOGI("JsiPaEngine OnVisibilityChanged");
    ACE_DCHECK(engineInstance_);

    std::string strJsonResult("{");
    for (auto item = formEventsMap.begin(); item != formEventsMap.end(); item++) {
        strJsonResult.append(ToJSONStringInt(std::to_string(item->first), std::to_string(item->second)));
        strJsonResult.append(",");
    }
    strJsonResult = strJsonResult.substr(0, strJsonResult.size() - 1);
    strJsonResult.append("}");
    LOGI("JsiPaEngine strJsonResult = %{public}s", strJsonResult.c_str());

    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = { runtime->ParseJson(strJsonResult) };
    auto func = GetPaFunc("onVisibilityChanged");
    CallFunc(func, argv);
}

void JsiPaEngine::OnAcquireState(const OHOS::AAFwk::Want &want)
{
    LOGI("JsiPaEngine OnAcquireState");
    const std::vector<shared_ptr<JsValue>>& argv = { WantToJsValue(want) };
    auto func = GetPaFunc("onAcquireState");
    CallFunc(func, argv);
}

} // namespace OHOS::Ace
