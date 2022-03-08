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

#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"

#include <unistd.h>

#include "base/i18n/localization.h"
#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "core/common/ace_application_info.h"
#include "core/common/ace_view.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/engine/content_storage_set.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/ark/ark_js_runtime.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/ark/ark_js_value.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_group_js_bridge.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_utils.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/modules/jsi_module_manager.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/modules/jsi_syscap_module.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/modules/jsi_timer_module.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent.h"
#include "frameworks/bridge/js_frontend/engine/common/js_api_perf.h"
#include "frameworks/bridge/js_frontend/engine/common/runtime_constants.h"

extern const char _binary_stateMgmt_abc_start[];
extern const char _binary_stateMgmt_abc_end[];
extern const char _binary_jsEnumStyle_abc_start[];
extern const char _binary_jsEnumStyle_abc_end[];
extern const char _binary_contentStorage_abc_start[];
extern const char _binary_contentStorage_abc_end[];

namespace OHOS::Ace::Framework {
namespace {

#ifdef APP_USE_ARM
const std::string ARK_DEBUGGER_LIB_PATH = "/system/lib/libark_debugger.z.so";
#else
const std::string ARK_DEBUGGER_LIB_PATH = "/system/lib64/libark_debugger.z.so";
#endif

std::string ParseLogContent(const std::vector<std::string>& params)
{
    std::string ret;
    if (params.empty()) {
        return ret;
    }
    std::string formatStr = params[0];
    int32_t size = static_cast<int32_t>(params.size());
    int32_t len = static_cast<int32_t>(formatStr.size());
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

shared_ptr<JsValue> JsLogPrint(
    const shared_ptr<JsRuntime>& runtime, JsLogLevel level, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    // Should have 1 parameters.
    if (argc == 0) {
        LOGE("the arg is error");
        return runtime->NewUndefined();
    }

    std::string content = GetLogContent(runtime, argv, argc);
    switch (level) {
        case JsLogLevel::DEBUG:
            LOGD("ace Log: %{public}s", content.c_str());
            break;
        case JsLogLevel::INFO:
            LOGI("ace Log: %{public}s", content.c_str());
            break;
        case JsLogLevel::WARNING:
            LOGW("ace Log: %{public}s", content.c_str());
            break;
        case JsLogLevel::ERROR:
            LOGE("ace Log: %{public}s", content.c_str());
            break;
    }

    shared_ptr<JsValue> ret = runtime->NewUndefined();
    return ret;
}

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

// native implementation for js function: aceConsole.debug()
shared_ptr<JsValue> JsDebugLogPrint(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return JsLogPrint(runtime, JsLogLevel::DEBUG, std::move(argv), argc);
}

// native implementation for js function: aceConsole.info()
shared_ptr<JsValue> JsInfoLogPrint(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return JsLogPrint(runtime, JsLogLevel::INFO, std::move(argv), argc);
}

// native implementation for js function: aceConsole.warn()
shared_ptr<JsValue> JsWarnLogPrint(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return JsLogPrint(runtime, JsLogLevel::WARNING, std::move(argv), argc);
}

// native implementation for js function: aceConsole.error()
shared_ptr<JsValue> JsErrorLogPrint(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return JsLogPrint(runtime, JsLogLevel::ERROR, std::move(argv), argc);
}

// native implementation for js function: perfutil.print()
shared_ptr<JsValue> JsPerfPrint(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    std::string ret = JsApiPerf::GetInstance().PrintToLogs();
    return runtime->NewString(ret);
}

// native implementation for js function: perfutil.sleep()
shared_ptr<JsValue> JsPerfSleep(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    int32_t valInt = argv[0]->ToInt32(runtime);
    usleep(valInt);
    return runtime->NewNull();
}

// native implementation for js function: perfutil.begin()
shared_ptr<JsValue> JsPerfBegin(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    int64_t currentTime = GetMicroTickCount();
    JsApiPerf::GetInstance().InsertJsBeginLog(argv[0]->ToString(runtime), currentTime);
    return runtime->NewNull();
}

// native implementation for js function: perfutil.end()
shared_ptr<JsValue> JsPerfEnd(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    int64_t currentTime = GetMicroTickCount();
    JsApiPerf::GetInstance().InsertJsEndLog(argv[0]->ToString(runtime), currentTime);
    return runtime->NewNull();
}

shared_ptr<JsValue> RequireNativeModule(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    std::string moduleName = argv[0]->ToString(runtime);

    // has already init module object
    shared_ptr<JsValue> global = runtime->GetGlobal();
    shared_ptr<JsValue> moduleObject = global->GetProperty(runtime, moduleName);
    if (moduleObject != nullptr && moduleObject->IsObject(runtime)) {
        LOGE("has already init moduleObject %{private}s", moduleName.c_str());
        return moduleObject;
    }

    // init module object first time
    shared_ptr<JsValue> newObject = runtime->NewObject();
    if (ModuleManager::GetInstance()->InitModule(runtime, newObject, moduleName)) {
        global->SetProperty(runtime, moduleName, newObject);
        return newObject;
    }

    return runtime->NewNull();
}

} // namespace

// -----------------------
// Start JsiDeclarativeEngineInstance
// -----------------------
std::map<std::string, std::string> JsiDeclarativeEngineInstance::mediaResourceFileMap_;

std::unique_ptr<JsonValue> JsiDeclarativeEngineInstance::currentConfigResourceData_;

bool JsiDeclarativeEngineInstance::isModulePreloaded_ = false;
bool JsiDeclarativeEngineInstance::isModuleInitialized_ = false;

JsiDeclarativeEngineInstance::~JsiDeclarativeEngineInstance()
{
    CHECK_RUN_ON(JS);
    LOG_DESTROY();

    if (runningPage_) {
        runningPage_->OnJsEngineDestroy();
    }

    if (stagingPage_) {
        stagingPage_->OnJsEngineDestroy();
    }

    if (runtime_) {
        runtime_->RegisterUncaughtExceptionHandler(nullptr);
        // reset runtime in utils
        JsiDeclarativeUtils::SetRuntime(nullptr, runtime_);

        runtime_->Reset();
    }
    runtime_.reset();
    runtime_ = nullptr;
    JsiDeclarativeUtils::SetCurrentState(JsErrorType::DESTROY_PAGE_ERROR, instanceId_, "", nullptr);
}

bool JsiDeclarativeEngineInstance::InitJsEnv(bool debuggerMode,
    const std::unordered_map<std::string, void*>& extraNativeObject, const shared_ptr<JsRuntime>& runtime)
{
    CHECK_RUN_ON(JS);
    ACE_SCOPED_TRACE("JsiDeclarativeEngineInstance::InitJsEnv");
    if (runtime != nullptr) {
        LOGI("JsiDeclarativeEngineInstance InitJsEnv usingSharedRuntime");
        runtime_ = runtime;
        usingSharedRuntime_ = true;
    } else {
        LOGI("JsiDeclarativeEngineInstance InitJsEnv not usingSharedRuntime, create own");
        runtime_.reset(new ArkJSRuntime());
    }

    if (runtime_ == nullptr) {
        LOGE("Js Engine cannot allocate JSI JSRuntime");
        EventReport::SendJsException(JsExcepType::JS_ENGINE_INIT_ERR);
        return false;
    }

    runtime_->SetLogPrint(PrintLog);
    std::string libraryPath = "";
    if (debuggerMode) {
        libraryPath = ARK_DEBUGGER_LIB_PATH;
    }
    if (!usingSharedRuntime_ && !runtime_->Initialize(libraryPath, isDebugMode_)) {
        LOGE("Js Engine initialize runtime failed");
        return false;
    }

    // set new runtime
    JsiDeclarativeUtils::SetRuntime(runtime_);

    runtime_->SetEmbedderData(this);
    runtime_->RegisterUncaughtExceptionHandler(JsiDeclarativeUtils::ReportJsErrorEvent);

#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
    for (const auto& [key, value] : extraNativeObject) {
        shared_ptr<JsValue> nativeValue = runtime_->NewNativePointer(value);
        runtime_->GetGlobal()->SetProperty(runtime_, key, nativeValue);
    }
#endif

    LocalScope socpe(std::static_pointer_cast<ArkJSRuntime>(runtime_)->GetEcmaVm());
    InitGlobalObjectTemplate();

    // no need to initialize functions on global when use shared runtime
    if (usingSharedRuntime_ && isModuleInitialized_) {
        LOGI("InitJsEnv SharedRuntime has initialized, skip...");
    } else {
        InitConsoleModule();
        InitAceModule();
        InitPerfUtilModule();
        InitJsExportsUtilObject();
        InitJsNativeModuleObject();
        InitGroupJsBridge();
    }

    if (usingSharedRuntime_) {
        isModuleInitialized_ = true;
    }

    // load resourceConfig
    currentConfigResourceData_ = JsonUtil::CreateArray(true);
    frontendDelegate_->LoadResourceConfiguration(mediaResourceFileMap_, currentConfigResourceData_);

    return true;
}

bool JsiDeclarativeEngineInstance::FireJsEvent(const std::string& eventStr)
{
    return true;
}

void JsiDeclarativeEngineInstance::InitAceModule()
{
    if (!isModulePreloaded_) {
        bool contentStorageResult = runtime_->EvaluateJsCode((uint8_t*)_binary_contentStorage_abc_start,
            _binary_contentStorage_abc_end - _binary_contentStorage_abc_start);
        if (!contentStorageResult) {
            JsiDeclarativeUtils::SetCurrentState(JsErrorType::LOAD_JS_BUNDLE_ERROR, instanceId_);
            LOGE("EvaluateJsCode stateMgmt failed");
        }
    }

    bool stateMgmtResult = runtime_->EvaluateJsCode(
        (uint8_t*)_binary_stateMgmt_abc_start, _binary_stateMgmt_abc_end - _binary_stateMgmt_abc_start);
    if (!stateMgmtResult) {
        JsiDeclarativeUtils::SetCurrentState(JsErrorType::LOAD_JS_BUNDLE_ERROR, instanceId_);
        LOGE("EvaluateJsCode stateMgmt failed");
    }
    bool jsEnumStyleResult = runtime_->EvaluateJsCode(
        (uint8_t*)_binary_jsEnumStyle_abc_start, _binary_jsEnumStyle_abc_end - _binary_jsEnumStyle_abc_start);
    if (!jsEnumStyleResult) {
        JsiDeclarativeUtils::SetCurrentState(JsErrorType::LOAD_JS_BUNDLE_ERROR, instanceId_);
        LOGE("EvaluateJsCode jsEnumStyle failed");
    }
}

extern "C" ACE_EXPORT void OHOS_ACE_PreInitAceModule(void* runtime)
{
    LOGI("Ace ark lib loaded, PreInitAceModule.");
    JsiDeclarativeEngineInstance::PreInitAceModule(runtime);
}

void JsiDeclarativeEngineInstance::PreInitAceModule(void* runtime)
{
    auto sharedRuntime = reinterpret_cast<NativeEngine*>(runtime);
    std::shared_ptr<ArkJSRuntime> arkRuntime;
    EcmaVM* vm = nullptr;
    if (!sharedRuntime) {
        LOGI("PreInitAceModule will not use sharedRuntime");
    } else {
        arkRuntime = std::make_shared<ArkJSRuntime>();
        auto nativeArkEngine = static_cast<ArkNativeEngine*>(sharedRuntime);
        vm = const_cast<EcmaVM*>(nativeArkEngine->GetEcmaVm());
        if (vm == nullptr) {
            LOGE("PreInitAceModule NativeDeclarativeEngine Initialize, vm is null");
            return;
        }
        if (!arkRuntime->InitializeFromExistVM(vm)) {
            LOGE("PreInitAceModule Ark Engine initialize runtime failed");
            return;
        }
    }

    shared_ptr<JsValue> global = arkRuntime->GetGlobal();
    shared_ptr<JsValue> aceConsoleObj = arkRuntime->NewObject();
    aceConsoleObj->SetProperty(arkRuntime, "log", arkRuntime->NewFunction(JsDebugLogPrint));
    aceConsoleObj->SetProperty(arkRuntime, "debug", arkRuntime->NewFunction(JsDebugLogPrint));
    aceConsoleObj->SetProperty(arkRuntime, "info", arkRuntime->NewFunction(JsInfoLogPrint));
    aceConsoleObj->SetProperty(arkRuntime, "warn", arkRuntime->NewFunction(JsWarnLogPrint));
    aceConsoleObj->SetProperty(arkRuntime, "error", arkRuntime->NewFunction(JsErrorLogPrint));
    global->SetProperty(arkRuntime, "aceConsole", aceConsoleObj);

    bool evalResult = arkRuntime->EvaluateJsCode(
        (uint8_t*)_binary_contentStorage_abc_start, _binary_contentStorage_abc_end - _binary_contentStorage_abc_start);
    if (!evalResult) {
        JsiDeclarativeUtils::SetCurrentState(JsErrorType::LOAD_JS_BUNDLE_ERROR, 0);
        LOGE("PreInitAceModule EvaluateJsCode stateMgmt failed");
    }
    isModulePreloaded_ = evalResult;
}

void JsiDeclarativeEngineInstance::InitConsoleModule()
{
    ACE_SCOPED_TRACE("JsiDeclarativeEngineInstance::InitConsoleModule");
    LOGD("JsiDeclarativeEngineInstance InitConsoleModule");
    shared_ptr<JsValue> global = runtime_->GetGlobal();

    // app log method
    if (!usingSharedRuntime_) {
        shared_ptr<JsValue> consoleObj = runtime_->NewObject();
        consoleObj->SetProperty(runtime_, "log", runtime_->NewFunction(AppDebugLogPrint));
        consoleObj->SetProperty(runtime_, "debug", runtime_->NewFunction(AppDebugLogPrint));
        consoleObj->SetProperty(runtime_, "info", runtime_->NewFunction(AppInfoLogPrint));
        consoleObj->SetProperty(runtime_, "warn", runtime_->NewFunction(AppWarnLogPrint));
        consoleObj->SetProperty(runtime_, "error", runtime_->NewFunction(AppErrorLogPrint));
        global->SetProperty(runtime_, "console", consoleObj);
    }

    if (isModulePreloaded_) {
        LOGD("console module has already inited");
        return;
    }
    // js framework log method
    shared_ptr<JsValue> aceConsoleObj = runtime_->NewObject();
    aceConsoleObj->SetProperty(runtime_, "log", runtime_->NewFunction(JsDebugLogPrint));
    aceConsoleObj->SetProperty(runtime_, "debug", runtime_->NewFunction(JsDebugLogPrint));
    aceConsoleObj->SetProperty(runtime_, "info", runtime_->NewFunction(JsInfoLogPrint));
    aceConsoleObj->SetProperty(runtime_, "warn", runtime_->NewFunction(JsWarnLogPrint));
    aceConsoleObj->SetProperty(runtime_, "error", runtime_->NewFunction(JsErrorLogPrint));
    global->SetProperty(runtime_, "aceConsole", aceConsoleObj);
}

std::string GetLogContent(NativeEngine* nativeEngine, NativeCallbackInfo* info)
{
    std::string content;
    for (size_t i = 0; i < info->argc; ++i) {
        if (info->argv[i]->TypeOf() != NATIVE_STRING) {
            LOGE("argv is not NativeString");
            continue;
        }
        auto nativeString = reinterpret_cast<NativeString*>(info->argv[i]->GetInterface(NativeString::INTERFACE_ID));
        size_t bufferSize = nativeString->GetLength();
        size_t strLength = 0;
        char* buffer = new char[bufferSize + 1] { 0 };
        nativeString->GetCString(buffer, bufferSize + 1, &strLength);
        content.append(buffer);
        delete[] buffer;
    }
    return content;
}

NativeValue* AppLogPrint(NativeEngine* nativeEngine, NativeCallbackInfo* info, JsLogLevel level)
{
    // Should have at least 1 parameters.
    if (info->argc == 0) {
        LOGE("the arg is error");
        return nativeEngine->CreateUndefined();
    }
    std::string content = GetLogContent(nativeEngine, info);
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

    return nativeEngine->CreateUndefined();
}

NativeValue* AppDebugLogPrint(NativeEngine* nativeEngine, NativeCallbackInfo* info)
{
    return AppLogPrint(nativeEngine, info, JsLogLevel::DEBUG);
}

NativeValue* AppInfoLogPrint(NativeEngine* nativeEngine, NativeCallbackInfo* info)
{
    return AppLogPrint(nativeEngine, info, JsLogLevel::INFO);
}

NativeValue* AppWarnLogPrint(NativeEngine* nativeEngine, NativeCallbackInfo* info)
{
    return AppLogPrint(nativeEngine, info, JsLogLevel::WARNING);
}

NativeValue* AppErrorLogPrint(NativeEngine* nativeEngine, NativeCallbackInfo* info)
{
    return AppLogPrint(nativeEngine, info, JsLogLevel::ERROR);
}

void JsiDeclarativeEngineInstance::InitConsoleModule(ArkNativeEngine* engine)
{
    ACE_SCOPED_TRACE("JsiDeclarativeEngineInstance::RegisterConsoleModule");
    LOGD("JsiDeclarativeEngineInstance RegisterConsoleModule to nativeEngine");
    NativeValue* global = engine->GetGlobal();
    if (global->TypeOf() != NATIVE_OBJECT) {
        LOGE("global is not NativeObject");
        return;
    }
    auto nativeGlobal = reinterpret_cast<NativeObject*>(global->GetInterface(NativeObject::INTERFACE_ID));

    // app log method
    NativeValue* console = engine->CreateObject();
    auto consoleObj = reinterpret_cast<NativeObject*>(console->GetInterface(NativeObject::INTERFACE_ID));
    consoleObj->SetProperty("log", engine->CreateFunction("log", strlen("log"), AppDebugLogPrint, nullptr));
    consoleObj->SetProperty("debug", engine->CreateFunction("debug", strlen("debug"), AppDebugLogPrint, nullptr));
    consoleObj->SetProperty("info", engine->CreateFunction("info", strlen("info"), AppInfoLogPrint, nullptr));
    consoleObj->SetProperty("warn", engine->CreateFunction("warn", strlen("warn"), AppWarnLogPrint, nullptr));
    consoleObj->SetProperty("error", engine->CreateFunction("error", strlen("error"), AppErrorLogPrint, nullptr));
    nativeGlobal->SetProperty("console", console);
}

void JsiDeclarativeEngineInstance::InitPerfUtilModule()
{
    ACE_SCOPED_TRACE("JsiDeclarativeEngineInstance::InitPerfUtilModule");
    LOGD("JsiDeclarativeEngineInstance InitPerfUtilModule");
    shared_ptr<JsValue> perfObj = runtime_->NewObject();
    perfObj->SetProperty(runtime_, "printlog", runtime_->NewFunction(JsPerfPrint));
    perfObj->SetProperty(runtime_, "sleep", runtime_->NewFunction(JsPerfSleep));
    perfObj->SetProperty(runtime_, "begin", runtime_->NewFunction(JsPerfBegin));
    perfObj->SetProperty(runtime_, "end", runtime_->NewFunction(JsPerfEnd));

    shared_ptr<JsValue> global = runtime_->GetGlobal();
    global->SetProperty(runtime_, "perfutil", perfObj);
}

void JsiDeclarativeEngineInstance::InitJsExportsUtilObject()
{
    shared_ptr<JsValue> exportsUtilObj = runtime_->NewObject();
    shared_ptr<JsValue> global = runtime_->GetGlobal();
    global->SetProperty(runtime_, "exports", exportsUtilObj);
}

void JsiDeclarativeEngineInstance::InitJsNativeModuleObject()
{
    shared_ptr<JsValue> global = runtime_->GetGlobal();
    global->SetProperty(runtime_, "requireNativeModule", runtime_->NewFunction(RequireNativeModule));

    if (!usingSharedRuntime_) {
        JsiTimerModule::GetInstance()->InitTimerModule(runtime_, global);
        JsiSyscapModule::GetInstance()->InitSyscapModule(runtime_, global);
    }
}

void JsiDeclarativeEngineInstance::InitGlobalObjectTemplate()
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(runtime_);
    JsRegisterViews(JSNApi::GetGlobalObject(runtime->GetEcmaVm()));
}

void JsiDeclarativeEngineInstance::InitGroupJsBridge()
{
    auto groupJsBridge = DynamicCast<JsiDeclarativeGroupJsBridge>(frontendDelegate_->GetGroupJsBridge());
    if (groupJsBridge == nullptr || groupJsBridge->InitializeGroupJsBridge(runtime_) == JS_CALL_FAIL) {
        LOGE("Js Engine Initialize GroupJsBridge failed!");
        EventReport::SendJsException(JsExcepType::JS_ENGINE_INIT_ERR);
    }
}

thread_local std::unordered_map<int32_t, panda::Global<panda::ObjectRef>> JsiDeclarativeEngineInstance::rootViewMap_;

void JsiDeclarativeEngineInstance::RootViewHandle(panda::Local<panda::ObjectRef> value)
{
    LOGD("RootViewHandle");
    RefPtr<JsAcePage> page = JsiDeclarativeEngineInstance::GetStagingPage(Container::CurrentId());
    if (page != nullptr) {
        auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(GetCurrentRuntime());
        if (!arkRuntime) {
            LOGE("ark engine is null");
            return;
        }
        rootViewMap_.emplace(page->GetPageId(), panda::Global<panda::ObjectRef>(arkRuntime->GetEcmaVm(), value));
    }
}

void JsiDeclarativeEngineInstance::DestroyRootViewHandle(int32_t pageId)
{
    CHECK_RUN_ON(JS);
    if (rootViewMap_.count(pageId) != 0) {
        auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime_);
        if (!arkRuntime) {
            LOGE("ark engine is null");
            return;
        }
        panda::Local<panda::ObjectRef> rootView = rootViewMap_[pageId].ToLocal(arkRuntime->GetEcmaVm());
        JSView* jsView = static_cast<JSView*>(rootView->GetNativePointerField(0));
        jsView->Destroy(nullptr);
        rootViewMap_[pageId].FreeGlobalHandleAddr();
        rootViewMap_.erase(pageId);
    }
}

void JsiDeclarativeEngineInstance::DestroyAllRootViewHandle()
{
    CHECK_RUN_ON(JS);
    if (rootViewMap_.size() > 0) {
        LOGI("DestroyAllRootViewHandle release left %{private}zu views ", rootViewMap_.size());
    }
    auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime_);
    if (!arkRuntime) {
        LOGE("ark engine is null");
        return;
    }
    for (const auto& pair : rootViewMap_) {
        auto globalRootView = pair.second;
        panda::Local<panda::ObjectRef> rootView = globalRootView.ToLocal(arkRuntime->GetEcmaVm());
        JSView* jsView = static_cast<JSView*>(rootView->GetNativePointerField(0));
        jsView->Destroy(nullptr);
        globalRootView.FreeGlobalHandleAddr();
    }
    rootViewMap_.clear();
}

std::unique_ptr<JsonValue> JsiDeclarativeEngineInstance::GetI18nStringResource(
    const std::string& targetStringKey, const std::string& targetStringValue)
{
    auto resourceI18nFileNum = currentConfigResourceData_->GetArraySize();
    for (int i = 0; i < resourceI18nFileNum; i++) {
        auto priorResource = currentConfigResourceData_->GetArrayItem(i);
        if ((priorResource->Contains(targetStringKey))) {
            auto valuePair = priorResource->GetValue(targetStringKey);
            if (valuePair->Contains(targetStringValue)) {
                return valuePair->GetValue(targetStringValue);
            }
        }
    }

    return JsonUtil::Create(true);
}

std::string JsiDeclarativeEngineInstance::GetMediaResource(const std::string& targetFileName)
{
    auto iter = mediaResourceFileMap_.find(targetFileName);

    if (iter != mediaResourceFileMap_.end()) {
        return iter->second;
    }

    return std::string();
}

RefPtr<JsAcePage> JsiDeclarativeEngineInstance::GetRunningPage(int32_t instanceId)
{
    auto engine = EngineHelper::GetEngine(instanceId);
    auto jsiEngine = AceType::DynamicCast<JsiDeclarativeEngine>(engine);
    if (!jsiEngine) {
        LOGE("jsiEngine is null");
        return nullptr;
    }
    auto engineInstance = jsiEngine->GetEngineInstance();
    LOGD("GetRunningPage id:%{public}d instance:%{public}p", instanceId, RawPtr(engineInstance));
    if (engineInstance == nullptr) {
        LOGE("engineInstance is nullptr");
        return nullptr;
    }
    return engineInstance->GetRunningPage();
}

RefPtr<JsAcePage> JsiDeclarativeEngineInstance::GetStagingPage(int32_t instanceId)
{
    auto engine = EngineHelper::GetEngine(instanceId);
    auto jsiEngine = AceType::DynamicCast<JsiDeclarativeEngine>(engine);
    if (!jsiEngine) {
        LOGE("jsiEngine is null");
        return nullptr;
    }
    auto engineInstance = jsiEngine->GetEngineInstance();
    LOGD("GetStagingPage id:%{public}d instance:%{public}p", instanceId, RawPtr(engineInstance));
    if (engineInstance == nullptr) {
        LOGE("engineInstance is nullptr");
        return nullptr;
    }
    return engineInstance->GetStagingPage();
}

shared_ptr<JsRuntime> JsiDeclarativeEngineInstance::GetCurrentRuntime()
{
    auto engine = EngineHelper::GetCurrentEngine();
    auto jsiEngine = AceType::DynamicCast<JsiDeclarativeEngine>(engine);
    if (!jsiEngine) {
        LOGE("jsiEngine is null");
        return nullptr;
    }
    auto engineInstance = jsiEngine->GetEngineInstance();
    if (engineInstance == nullptr) {
        LOGE("engineInstance is nullptr");
        return nullptr;
    }
    return engineInstance->GetJsRuntime();
}

void JsiDeclarativeEngineInstance::PostJsTask(const shared_ptr<JsRuntime>& runtime, std::function<void()>&& task)
{
    LOGD("PostJsTask");
    if (runtime == nullptr) {
        LOGE("jsRuntime is nullptr");
        return;
    }
    auto engineInstance = static_cast<JsiDeclarativeEngineInstance*>(runtime->GetEmbedderData());
    if (engineInstance == nullptr) {
        LOGE("engineInstance is nullptr");
        return;
    }
    engineInstance->GetDelegate()->PostJsTask(std::move(task));
}

void JsiDeclarativeEngineInstance::TriggerPageUpdate(const shared_ptr<JsRuntime>& runtime)
{
    LOGD("TriggerPageUpdate");
    if (runtime == nullptr) {
        LOGE("jsRuntime is nullptr");
        return;
    }
    auto engineInstance = static_cast<JsiDeclarativeEngineInstance*>(runtime->GetEmbedderData());
    if (engineInstance == nullptr) {
        LOGE("engineInstance is nullptr");
        return;
    }
    engineInstance->GetDelegate()->TriggerPageUpdate(engineInstance->GetRunningPage()->GetPageId());
}

RefPtr<PipelineContext> JsiDeclarativeEngineInstance::GetPipelineContext(const shared_ptr<JsRuntime>& runtime)
{
    LOGD("GetPipelineContext");
    if (runtime == nullptr) {
        LOGE("jsRuntime is nullptr");
        return nullptr;
    }
    auto engineInstance = static_cast<JsiDeclarativeEngineInstance*>(runtime->GetEmbedderData());
    if (engineInstance == nullptr) {
        LOGE("engineInstance is nullptr");
        return nullptr;
    }
    return engineInstance->GetDelegate()->GetPipelineContext();
}

void JsiDeclarativeEngineInstance::FlushCommandBuffer(void* context, const std::string& command)
{
    return;
}

// -----------------------
// Start JsiDeclarativeEngine
// -----------------------
JsiDeclarativeEngine::~JsiDeclarativeEngine()
{
    CHECK_RUN_ON(JS);
    LOG_DESTROY();

    XComponentClient::GetInstance().SetRegisterCallbackToNull();
    XComponentClient::GetInstance().SetJSValCallToNull();

    engineInstance_->GetDelegate()->RemoveTaskObserver();

    if (!runtime_ && nativeEngine_ != nullptr) {
        nativeEngine_->CancelCheckUVLoop();
        engineInstance_->DestroyAllRootViewHandle();
        delete nativeEngine_;
        nativeEngine_ = nullptr;
    }

    if (nativeXComponent_) {
        delete nativeXComponent_;
        nativeXComponent_ = nullptr;
    }
}

bool JsiDeclarativeEngine::Initialize(const RefPtr<FrontendDelegate>& delegate)
{
    CHECK_RUN_ON(JS);
    ACE_SCOPED_TRACE("JsiDeclarativeEngine::Initialize");
    LOGI("JsiDeclarativeEngine Initialize");
    ACE_DCHECK(delegate);
    engineInstance_ = AceType::MakeRefPtr<JsiDeclarativeEngineInstance>(delegate, instanceId_);
    auto sharedRuntime = reinterpret_cast<NativeEngine*>(runtime_);
    std::shared_ptr<ArkJSRuntime> arkRuntime;
    EcmaVM* vm = nullptr;
    if (!sharedRuntime) {
        LOGI("Initialize will not use sharedRuntime");
    } else {
        LOGI("Initialize will use sharedRuntime");
        arkRuntime = std::make_shared<ArkJSRuntime>();
        auto nativeArkEngine = static_cast<ArkNativeEngine*>(sharedRuntime);
        vm = const_cast<EcmaVM*>(nativeArkEngine->GetEcmaVm());
        if (vm == nullptr) {
            LOGE("NativeDeclarativeEngine Initialize, vm is null");
            return false;
        }
        if (!arkRuntime->InitializeFromExistVM(vm)) {
            LOGE("Ark Engine initialize runtime failed");
            return false;
        }
        nativeEngine_ = nativeArkEngine;
    }
    engineInstance_->SetDebugMode(NeedDebugBreakPoint());
    bool result = engineInstance_->InitJsEnv(IsDebugVersion(), GetExtraNativeObject(), arkRuntime);
    if (!result) {
        LOGE("JsiDeclarativeEngine Initialize, init js env failed");
        return false;
    }

    auto runtime = engineInstance_->GetJsRuntime();
    vm = vm ? vm : const_cast<EcmaVM*>(std::static_pointer_cast<ArkJSRuntime>(runtime)->GetEcmaVm());
    if (vm == nullptr) {
        LOGE("JsiDeclarativeEngine Initialize, vm is null");
        return false;
    }

    if (nativeEngine_ == nullptr) {
        nativeEngine_ = new ArkNativeEngine(vm, static_cast<void*>(this));
    }
    engineInstance_->SetNativeEngine(nativeEngine_);
    if (!sharedRuntime) {
        SetPostTask(nativeEngine_);
        nativeEngine_->CheckUVLoop();
    } else {
        LOGI("Using sharedRuntime, UVLoop handled by AbilityRuntime");
    }

    if (delegate && delegate->GetAssetManager()) {
        std::string packagePath = delegate->GetAssetManager()->GetLibPath();
        if (!packagePath.empty()) {
            auto arkNativeEngine = static_cast<ArkNativeEngine*>(nativeEngine_);
            arkNativeEngine->SetPackagePath(packagePath);
        }
    }

    RegisterWorker();
    return result;
}

void JsiDeclarativeEngine::SetPostTask(NativeEngine* nativeEngine)
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

void JsiDeclarativeEngine::RegisterInitWorkerFunc()
{
    auto weakInstance = AceType::WeakClaim(AceType::RawPtr(engineInstance_));
    auto&& initWorkerFunc = [weakInstance](NativeEngine* nativeEngine) {
        LOGI("WorkerCore RegisterInitWorkerFunc called");
        if (nativeEngine == nullptr) {
            LOGE("nativeEngine is nullptr");
            return;
        }
        auto arkNativeEngine = static_cast<ArkNativeEngine*>(nativeEngine);
        if (arkNativeEngine == nullptr) {
            LOGE("arkNativeEngine is nullptr");
            return;
        }
        auto instance = weakInstance.Upgrade();
        if (instance == nullptr) {
            LOGE("instance is nullptr");
            return;
        }
        instance->InitConsoleModule(arkNativeEngine);

        std::vector<uint8_t> buffer((uint8_t*)_binary_jsEnumStyle_abc_start, (uint8_t*)_binary_jsEnumStyle_abc_end);
        auto stateMgmtResult = arkNativeEngine->RunBufferScript(buffer);
        if (stateMgmtResult == nullptr) {
            LOGE("init worker error");
        }
    };
    nativeEngine_->SetInitWorkerFunc(initWorkerFunc);
}

void JsiDeclarativeEngine::RegisterAssetFunc()
{
    auto weakDelegate = AceType::WeakClaim(AceType::RawPtr(engineInstance_->GetDelegate()));
    auto&& assetFunc = [weakDelegate](const std::string& uri, std::vector<uint8_t>& content, std::string &ami) {
        LOGI("WorkerCore RegisterAssetFunc called");
        auto delegate = weakDelegate.Upgrade();
        if (delegate == nullptr) {
            LOGE("delegate is nullptr");
            return;
        }
        size_t index = uri.find_last_of(".");
        if (index == std::string::npos) {
            LOGE("invalid uri");
        } else {
            delegate->GetResourceData(uri.substr(0, index) + ".abc", content, ami);
        }
    };
    nativeEngine_->SetGetAssetFunc(assetFunc);
}

void JsiDeclarativeEngine::RegisterWorker()
{
    RegisterInitWorkerFunc();
    RegisterAssetFunc();
}

void JsiDeclarativeEngine::LoadJs(const std::string& url, const RefPtr<JsAcePage>& page, bool isMainPage)
{
    ACE_SCOPED_TRACE("JsiDeclarativeEngine::LoadJs");
    LOGI("JsiDeclarativeEngine %{private}p LoadJs page:%{public}d", RawPtr(engineInstance_), page->GetPageId());
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetStagingPage(page);
    if (isMainPage) {
        ACE_DCHECK(!engineInstance_->GetRunningPage());
        engineInstance_->SetRunningPage(page);
    }

    auto runtime = engineInstance_->GetJsRuntime();
    auto delegate = engineInstance_->GetDelegate();
    JsiDeclarativeUtils::SetCurrentState(JsErrorType::LOAD_JS_BUNDLE_ERROR, instanceId_, page->GetUrl(), page);

    // get source map
    std::string jsSourceMap;
    if (delegate->GetAssetContent(url + ".map", jsSourceMap)) {
        page->SetPageMap(jsSourceMap);
    } else {
        LOGW("js source map load failed!");
    }
    // get js bundle content
    shared_ptr<JsValue> jsCode = runtime->NewUndefined();
    shared_ptr<JsValue> jsAppCode = runtime->NewUndefined();
    const char js_ext[] = ".js";
    const char bin_ext[] = ".abc";
    auto pos = url.rfind(js_ext);
    if (pos != std::string::npos && pos == url.length() - (sizeof(js_ext) - 1)) {
        std::string urlName = url.substr(0, pos) + bin_ext;
        std::string assetBasePath = delegate->GetAssetPath(urlName);
        std::string assetPath = assetBasePath.append(urlName);
        LOGI("assetPath is: %{private}s", assetPath.c_str());

        if (isMainPage) {
            std::string commonsBasePath = delegate->GetAssetPath("commons.abc");
            if (!commonsBasePath.empty()) {
                std::string commonsPath = commonsBasePath.append("commons.abc");
                if (!runtime->ExecuteJsBin(commonsPath)) {
                    LOGE("ExecuteJsBin \"commons.js\" failed.");
                    return;
                }
            }
            std::string vendorsBasePath = delegate->GetAssetPath("vendors.abc");
            if (!vendorsBasePath.empty()) {
                std::string vendorsPath = vendorsBasePath.append("vendors.abc");
                if (!runtime->ExecuteJsBin(vendorsPath)) {
                    LOGE("ExecuteJsBin \"vendors.js\" failed.");
                    return;
                }
            }
            std::string appMap;
            if (delegate->GetAssetContent("app.js.map", appMap)) {
                page->SetAppMap(appMap);
            } else {
                LOGW("app map load failed!");
            }
            std::string appBasePath = delegate->GetAssetPath("app.abc");
            std::string appPath = appBasePath.append("app.abc");
            LOGI("appPath is: %{private}s", appPath.c_str());
            if (runtime->ExecuteJsBin(appPath)) {
                CallAppFunc("onCreate");
            } else {
                LOGW("ExecuteJsBin \"app.js\" failed.");
            }
        }
        if (!runtime->ExecuteJsBin(assetPath)) {
            LOGE("ExecuteJsBin %{public}s failed.", urlName.c_str());
            return;
        }
    }
}

void JsiDeclarativeEngine::UpdateRunningPage(const RefPtr<JsAcePage>& page)
{
    LOGD("JsiDeclarativeEngine UpdateRunningPage");
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetRunningPage(page);
}

void JsiDeclarativeEngine::UpdateStagingPage(const RefPtr<JsAcePage>& page)
{
    LOGI("JsiDeclarativeEngine UpdateStagingPage %{public}d", page->GetPageId());
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetStagingPage(page);
}

void JsiDeclarativeEngine::ResetStagingPage()
{
    LOGD("JsiDeclarativeEngine ResetStagingPage");
    ACE_DCHECK(engineInstance_);
    auto runningPage = engineInstance_->GetRunningPage();
    engineInstance_->ResetStagingPage(runningPage);
}

void JsiDeclarativeEngine::SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher)
{
    LOGD("JsiDeclarativeEngine SetJsMessageDispatcher");
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetJsMessageDispatcher(dispatcher);
}

void JsiDeclarativeEngine::FireAsyncEvent(const std::string& eventId, const std::string& param)
{
    LOGD("JsiDeclarativeEngine FireAsyncEvent");
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

void JsiDeclarativeEngine::FireSyncEvent(const std::string& eventId, const std::string& param)
{
    LOGD("JsiDeclarativeEngine FireSyncEvent");
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

void JsiDeclarativeEngine::InitXComponent()
{
    ACE_DCHECK(engineInstance_);

    nativeXComponentImpl_ = AceType::MakeRefPtr<NativeXComponentImpl>();
    nativeXComponent_ = new OH_NativeXComponent(AceType::RawPtr(nativeXComponentImpl_));
}

void JsiDeclarativeEngine::FireExternalEvent(const std::string& componentId, const uint32_t nodeId)
{
    CHECK_RUN_ON(JS);
    InitXComponent();
    RefPtr<XComponentComponent> xcomponent;
    OHOS::Ace::Framework::XComponentClient::GetInstance().GetXComponent(xcomponent);
    if (!xcomponent) {
        LOGE("FireExternalEvent xcomponent is null.");
        return;
    }

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

    void* nativeWindow = nullptr;
#ifdef OHOS_STANDARD_SYSTEM
    nativeWindow = const_cast<void*>(xcomponent->GetNativeWindow());
#else
    auto textureId = static_cast<int64_t>(xcomponent->GetTextureId());
    nativeWindow = const_cast<void*>(nativeView->GetNativeWindowById(textureId));
#endif

    if (!nativeWindow) {
        LOGE("FireExternalEvent nativeWindow invalid");
        return;
    }
    nativeXComponentImpl_->SetSurface(nativeWindow);
    nativeXComponentImpl_->SetXComponentId(xcomponent->GetId());

    auto arkNativeEngine = static_cast<ArkNativeEngine*>(nativeEngine_);
    if (arkNativeEngine == nullptr) {
        LOGE("FireExternalEvent arkNativeEngine is nullptr");
        return;
    }

    std::string arguments;
    auto arkObjectRef = arkNativeEngine->LoadModuleByName(xcomponent->GetLibraryName(), true, arguments,
        OH_NATIVE_XCOMPONENT_OBJ, reinterpret_cast<void*>(nativeXComponent_));

    if (arkObjectRef.CheckException()) {
        LOGE("LoadModuleByName failed.");
        return;
    }

    auto runtime = engineInstance_->GetJsRuntime();
    renderContext_ = runtime->NewObject();
    auto renderContext = std::static_pointer_cast<ArkJSValue>(renderContext_);
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    LocalScope scope(pandaRuntime->GetEcmaVm());
    Local<ObjectRef> objXComp = arkObjectRef->ToObject(pandaRuntime->GetEcmaVm());
    if (objXComp.CheckException()) {
        LOGE("Get local object failed.");
        return;
    }
    renderContext->SetValue(pandaRuntime, objXComp);

    auto objContext = JsiObject(objXComp);
    JSRef<JSObject> obj = JSRef<JSObject>::Make(objContext);
    auto getJSValCallback = [obj](JSRef<JSVal>& jsVal) {
        jsVal = obj;
        return true;
    };
    XComponentClient::GetInstance().RegisterJSValCallback(getJSValCallback);

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
}

void JsiDeclarativeEngine::TimerCallback(const std::string& callbackId, const std::string& delay, bool isInterval)
{
    TimerCallJs(callbackId);
    auto runtime = JsiDeclarativeEngineInstance::GetCurrentRuntime();
    auto instance = static_cast<JsiDeclarativeEngineInstance*>(runtime->GetEmbedderData());
    if (instance == nullptr) {
        LOGE("get jsi engine instance failed");
        return;
    }
    auto delegate = instance->GetDelegate();
    if (!delegate) {
        LOGE("get frontend delegate failed");
        return;
    }

    if (isInterval) {
        delegate->WaitTimer(callbackId, delay, isInterval, false);
    } else {
        JsiTimerModule::GetInstance()->RemoveCallBack(std::stoi(callbackId));
        delegate->ClearTimer(callbackId);
    }
}

void JsiDeclarativeEngine::TimerCallJs(const std::string& callbackId) const
{
    shared_ptr<JsValue> func;
    std::vector<shared_ptr<JsValue>> params;
    if (!JsiTimerModule::GetInstance()->GetCallBack(std::stoi(callbackId), func, params)) {
        LOGE("get callback failed");
        return;
    }
    auto runtime = JsiDeclarativeEngineInstance::GetCurrentRuntime();
    func->Call(runtime, runtime->GetGlobal(), params, params.size());
}

void JsiDeclarativeEngine::DestroyPageInstance(int32_t pageId)
{
    LOGI("JsiDeclarativeEngine DestroyPageInstance %{public}d", pageId);
    ACE_DCHECK(engineInstance_);

    engineInstance_->DestroyRootViewHandle(pageId);
}

void JsiDeclarativeEngine::DestroyApplication(const std::string& packageName)
{
    LOGI("JsiDeclarativeEngine DestroyApplication, packageName %{public}s", packageName.c_str());
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    JsiDeclarativeUtils::SetCurrentState(
        JsErrorType::DESTROY_APP_ERROR, instanceId_, "", engineInstance_->GetStagingPage());

    CallAppFunc("onDestroy");
}

void JsiDeclarativeEngine::UpdateApplicationState(const std::string& packageName, Frontend::State state)
{
    LOGD("JsiDeclarativeEngine UpdateApplicationState, packageName %{public}s", packageName.c_str());
    if (state == Frontend::State::ON_SHOW) {
        CallAppFunc("onShow");
    } else if (state == Frontend::State::ON_HIDE) {
        CallAppFunc("onHide");
    } else {
        LOGW("unsupported state");
    }
}

void JsiDeclarativeEngine::OnWindowDisplayModeChanged(bool isShownInMultiWindow, const std::string& data)
{
    LOGI("JsiDeclarativeEngine OnWindowDisplayModeChanged");
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    std::vector<shared_ptr<JsValue>> argv = { runtime->NewBoolean(isShownInMultiWindow), runtime->NewString(data) };
    CallAppFunc("onWindowDisplayModeChanged", argv);
}

bool JsiDeclarativeEngine::CallAppFunc(const std::string& appFuncName)
{
    std::vector<shared_ptr<JsValue>> argv = {};
    return CallAppFunc(appFuncName, argv);
}

bool JsiDeclarativeEngine::CallAppFunc(const std::string& appFuncName, std::vector<shared_ptr<JsValue>>& argv)
{
    LOGD("JsiDeclarativeEngine CallAppFunc");
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    ACE_DCHECK(runtime);
    shared_ptr<JsValue> global = runtime->GetGlobal();
    shared_ptr<JsValue> exportsObject = global->GetProperty(runtime, "exports");
    if (!exportsObject->IsObject(runtime)) {
        LOGE("property \"exports\" is not a object");
        return false;
    }
    shared_ptr<JsValue> defaultObject = exportsObject->GetProperty(runtime, "default");
    if (!defaultObject->IsObject(runtime)) {
        LOGE("property \"default\" is not a object");
        return false;
    }
    shared_ptr<JsValue> func = defaultObject->GetProperty(runtime, appFuncName);
    if (!func || !func->IsFunction(runtime)) {
        LOGE("%{public}s not found or is not a function!", appFuncName.c_str());
        return false;
    }
    shared_ptr<JsValue> result;
    result = func->Call(runtime, defaultObject, argv, argv.size());
    return (result->ToString(runtime) == "true");
}

void JsiDeclarativeEngine::MediaQueryCallback(const std::string& callbackId, const std::string& args)
{
    JsEngine::MediaQueryCallback(callbackId, args);
}

void JsiDeclarativeEngine::RequestAnimationCallback(const std::string& callbackId, uint64_t timeStamp) {}

void JsiDeclarativeEngine::JsCallback(const std::string& callbackId, const std::string& args) {}

void JsiDeclarativeEngine::RunGarbageCollection()
{
    if (engineInstance_ && engineInstance_->GetJsRuntime()) {
        engineInstance_->GetJsRuntime()->RunGC();
    }
}

void JsiDeclarativeEngine::SetContentStorage(int32_t instanceId, NativeReference* nativeValue)
{
    ContentStorageSet::SetCurrentStorage(instanceId, nativeValue);
}

void JsiDeclarativeEngine::SetContext(int32_t instanceId, NativeReference* context)
{
    ContentStorageSet::SetCurrentContext(instanceId, context);
}

RefPtr<GroupJsBridge> JsiDeclarativeEngine::GetGroupJsBridge()
{
    return AceType::MakeRefPtr<JsiDeclarativeGroupJsBridge>();
}

void JsiDeclarativeEngine::OnActive()
{
    LOGI("JsiDeclarativeEngine onActive called.");
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        LOGE("onActive failed, runtime is null.");
        return;
    }

    CallAppFunc("onActive");
}

void JsiDeclarativeEngine::OnInactive()
{
    LOGI("JsiDeclarativeEngine OnInactive called.");
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        LOGE("OnInactive failed, runtime is null.");
        return;
    }

    CallAppFunc("onInactive");
}

bool JsiDeclarativeEngine::OnStartContinuation()
{
    LOGI("JsiDeclarativeEngine OnStartContinuation");
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        LOGE("OnStartContinuation failed, runtime is null.");
        return false;
    }

    return CallAppFunc("onStartContinuation");
}

void JsiDeclarativeEngine::OnCompleteContinuation(int32_t code)
{
    LOGI("JsiDeclarativeEngine OnCompleteContinuation");
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        LOGE("OnCompleteContinuation failed, runtime is null.");
        return;
    }

    std::vector<shared_ptr<JsValue>> argv = { runtime->NewNumber(code) };
    CallAppFunc("onCompleteContinuation", argv);
}

void JsiDeclarativeEngine::OnRemoteTerminated()
{
    LOGI("JsiDeclarativeEngine OnRemoteTerminated");
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        LOGE("OnRemoteTerminated failed, runtime is null.");
        return;
    }

    CallAppFunc("onRemoteTerminated");
}

void JsiDeclarativeEngine::OnSaveData(std::string& data)
{
    LOGI("JsiDeclarativeEngine OnSaveData");
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        LOGE("OnSaveData failed, runtime is null.");
        return;
    }

    shared_ptr<JsValue> object = runtime->NewObject();
    std::vector<shared_ptr<JsValue>> argv = { object };
    if (CallAppFunc("onSaveData", argv)) {
        data = object->GetJsonString(runtime);
    }
}
bool JsiDeclarativeEngine::OnRestoreData(const std::string& data)
{
    LOGI("JsiDeclarativeEngine OnRestoreData");
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        LOGE("OnRestoreData failed, runtime is null.");
        return false;
    }
    shared_ptr<JsValue> result;
    shared_ptr<JsValue> jsonObj = runtime->ParseJson(data);
    if (jsonObj->IsUndefined(runtime) || jsonObj->IsException(runtime)) {
        LOGE("JsiDeclarativeEngine: Parse json for restore data failed.");
        return false;
    }
    std::vector<shared_ptr<JsValue>> argv = { jsonObj };
    return CallAppFunc("onRestoreData", argv);
}

} // namespace OHOS::Ace::Framework
