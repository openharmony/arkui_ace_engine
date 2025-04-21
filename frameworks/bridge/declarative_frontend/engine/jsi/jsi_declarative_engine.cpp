/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include <mutex>
#include <optional>
#include <regex>
#include <shared_mutex>
#include <string>
#include <unistd.h>

#include "dfx_jsnapi.h"

#include "base/thread/task_executor.h"
#include "base/utils/utils.h"
#ifdef WINDOWS_PLATFORM
#include <algorithm>
#endif

#include "ace_forward_compatibility.h"
#include "scope_manager/native_scope_manager.h"

#include "base/base64/base64_util.h"
#include "base/i18n/localization.h"
#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/ui_context_helper.h"
#include "core/common/ace_application_info.h"
#include "core/common/ace_view.h"
#include "core/common/card_scope.h"
#include "core/common/connect_server_manager.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/layout_inspector.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "frameworks/bridge/card_frontend/card_frontend_declarative.h"
#include "frameworks/bridge/card_frontend/form_frontend_declarative.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/engine/js_converter.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_group_js_bridge.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_object_template.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_view_register.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/modules/jsi_context_module.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/modules/jsi_module_manager.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/modules/jsi_syscap_module.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/modules/jsi_timer_module.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_local_storage.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_mock.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_stack_processor.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/bridge/js_frontend/engine/common/js_api_perf.h"
#include "frameworks/bridge/js_frontend/engine/common/runtime_constants.h"
#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_runtime.h"
#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_value.h"
#include "frameworks/bridge/js_frontend/engine/jsi/jsi_base_utils.h"
#include "frameworks/core/components/xcomponent/xcomponent_component_client.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"
#include "frameworks/core/components_ng/pattern/xcomponent/xcomponent_pattern.h"

#if defined(PREVIEW)
extern const char _binary_jsMockSystemPlugin_abc_start[];
extern const char _binary_jsMockSystemPlugin_abc_end[];
#endif
extern const char _binary_stateMgmt_abc_start[];
extern const char _binary_jsEnumStyle_abc_start[];
extern const char _binary_jsUIContext_abc_start[];
extern const char _binary_arkComponent_abc_start[];
extern const char _binary_arkTheme_abc_start[];
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
extern const char _binary_jsPreload_abc_start[];
extern const char _binary_jsPreload_abc_end[];
#endif
#if !defined(IOS_PLATFORM)
extern const char _binary_stateMgmt_abc_end[];
extern const char _binary_jsEnumStyle_abc_end[];
extern const char _binary_jsUIContext_abc_end[];
extern const char _binary_arkComponent_abc_end[];
extern const char _binary_arkTheme_abc_end[];
#else
extern const char* _binary_stateMgmt_abc_end;
extern const char* _binary_jsEnumStyle_abc_end;
extern const char* _binary_jsUIContext_abc_end;
extern const char* _binary_arkComponent_abc_end;
extern const char* _binary_arkTheme_abc_end;
#endif

namespace OHOS::Ace::Framework {
namespace {

const std::string OHMURL_START_TAG = "@bundle:";

#if defined(ANDROID_PLATFORM)
const std::string ARK_DEBUGGER_LIB_PATH = "libark_inspector.so";
#elif defined(APP_USE_ARM)
const std::string ARK_DEBUGGER_LIB_PATH = "libark_inspector.z.so";
#else
const std::string ARK_DEBUGGER_LIB_PATH = "libark_inspector.z.so";
#endif
const std::string FORM_ES_MODULE_CARD_PATH = "ets/widgets.abc";
const std::string FORM_ES_MODULE_PATH = "ets/modules.abc";

const std::string ASSET_PATH_PREFIX = "/data/storage/el1/bundle/";

#ifdef PREVIEW
constexpr uint32_t PREFIX_LETTER_NUMBER = 4;
#endif
constexpr uint32_t MAX_STRING_CACHE_SIZE = 100;

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

inline bool PreloadJsEnums(const shared_ptr<JsRuntime>& runtime)
{
    std::string str("arkui_binary_jsEnumStyle_abc_loadFile");
    return runtime->EvaluateJsCode(
        (uint8_t*)_binary_jsEnumStyle_abc_start, _binary_jsEnumStyle_abc_end - _binary_jsEnumStyle_abc_start, str);
}

inline bool PreloadStateManagement(const shared_ptr<JsRuntime>& runtime)
{
    // set __hasUIFramework__
    runtime->GetGlobal()->SetProperty(runtime, "__hasUIFramework__", runtime->NewBoolean(true));
#ifdef STATE_MGMT_USE_AOT
    return runtime->ExecuteJsBinForAOT("/etc/abc/framework/stateMgmt.abc");
#else
    std::string str("arkui_binary_stateMgmt_abc_loadFile");
    return runtime->EvaluateJsCode(
        (uint8_t*)_binary_stateMgmt_abc_start, _binary_stateMgmt_abc_end - _binary_stateMgmt_abc_start, str);
#endif
}

inline bool PreloadUIContent(const shared_ptr<JsRuntime>& runtime)
{
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
    uint8_t* codeStart = const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(_binary_jsUIContext_abc_start));
    int32_t codeLength = _binary_jsUIContext_abc_end - _binary_jsUIContext_abc_start;
#else
    uint8_t* codeStart = const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(_binary_jsPreload_abc_start));
    int32_t codeLength = _binary_jsPreload_abc_end - _binary_jsPreload_abc_start;
#endif
    return runtime->EvaluateJsCode(codeStart, codeLength);
}

inline bool PreloadArkComponent(const shared_ptr<JsRuntime>& runtime)
{
    std::string str("arkui_binary_arkComponent_abc_loadFile");
    return runtime->EvaluateJsCode(
        (uint8_t*)_binary_arkComponent_abc_start, _binary_arkComponent_abc_end - _binary_arkComponent_abc_start, str);
}

inline bool PreloadArkTheme(const shared_ptr<JsRuntime>& runtime)
{
    std::string str("arkui_binary_arkTheme_abc_loadFile");
    return runtime->EvaluateJsCode(
        (uint8_t*)_binary_arkTheme_abc_start, _binary_arkTheme_abc_end - _binary_arkTheme_abc_start, str);
}

bool PreloadConsole(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& global)
{
    shared_ptr<JsValue> consoleObj = runtime->NewObject();
    consoleObj->SetProperty(runtime, "log", runtime->NewFunction(JsiBaseUtils::AppInfoLogPrint));
    consoleObj->SetProperty(runtime, "debug", runtime->NewFunction(JsiBaseUtils::AppDebugLogPrint));
    consoleObj->SetProperty(runtime, "info", runtime->NewFunction(JsiBaseUtils::AppInfoLogPrint));
    consoleObj->SetProperty(runtime, "warn", runtime->NewFunction(JsiBaseUtils::AppWarnLogPrint));
    consoleObj->SetProperty(runtime, "error", runtime->NewFunction(JsiBaseUtils::AppErrorLogPrint));
    return global->SetProperty(runtime, "console", consoleObj);
}

bool PreloadAceConsole(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& global)
{
    shared_ptr<JsValue> aceConsoleObj = runtime->NewObject();
    aceConsoleObj->SetProperty(runtime, "log", runtime->NewFunction(JsiBaseUtils::JsInfoLogPrint));
    aceConsoleObj->SetProperty(runtime, "debug", runtime->NewFunction(JsiBaseUtils::JsDebugLogPrint));
    aceConsoleObj->SetProperty(runtime, "info", runtime->NewFunction(JsiBaseUtils::JsInfoLogPrint));
    aceConsoleObj->SetProperty(runtime, "warn", runtime->NewFunction(JsiBaseUtils::JsWarnLogPrint));
    aceConsoleObj->SetProperty(runtime, "error", runtime->NewFunction(JsiBaseUtils::JsErrorLogPrint));
    return global->SetProperty(runtime, "aceConsole", aceConsoleObj);
}

bool PreloadAceTrace(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& global)
{
    shared_ptr<JsValue> aceTraceObj = runtime->NewObject();
    aceTraceObj->SetProperty(runtime, "begin", runtime->NewFunction(JsiBaseUtils::JsTraceBegin));
    aceTraceObj->SetProperty(runtime, "end", runtime->NewFunction(JsiBaseUtils::JsTraceEnd));
    return global->SetProperty(runtime, "aceTrace", aceTraceObj);
}

bool PreloadPerfutil(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& global)
{
    shared_ptr<JsValue> perfObj = runtime->NewObject();
    perfObj->SetProperty(runtime, "printlog", runtime->NewFunction(JsPerfPrint));
    perfObj->SetProperty(runtime, "sleep", runtime->NewFunction(JsPerfSleep));
    perfObj->SetProperty(runtime, "begin", runtime->NewFunction(JsPerfBegin));
    perfObj->SetProperty(runtime, "end", runtime->NewFunction(JsPerfEnd));
    return global->SetProperty(runtime, "perfutil", perfObj);
}

inline bool PreloadExports(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& global)
{
    shared_ptr<JsValue> exportsUtilObj = runtime->NewObject();
    return global->SetProperty(runtime, "exports", exportsUtilObj);
}

inline bool PreloadRequireNative(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& global)
{
    return global->SetProperty(runtime, "requireNativeModule", runtime->NewFunction(RequireNativeModule));
}

/**
 * The old version of the SDK will not generate the ohmUrl field, so we need to build it ourselves
 * for forward compatibility. The basic ohmUrl formats are as follows:
 *
 * 1. @bundle:{bundleName}/{moduleName}/ets/{pagePath}
 * examples as follow:
 *   @bundle:com.example.app/entry/ets/pages/Index
 *   @bundle:com.example.app/hsp/ets/pages/Second
 *
 * 2. @bundle:{bundleName}/{moduleName}@{harModuleName}/ets/{pagePath}
 * examples as follow:
 *   @bundle:com.example.app/entry@har/ets/pages/Index
 *   @bundle:com.example.app/hsp@har/ets/pages/Second
 * In this case, since the compiler did not generate the harModuleName field and pagePath is a relative path during
 * compilation, wee need to split the harModuleName and normal pathPath fields from the original pagePath.
 * for example:
 *    original pagePath: "../../../../har/src/main/ets/pages/harPageTwo"
 *     -> harModuleName: "har"
 *     -> result pagePath: "pages/harPageTwo"
 *
 * For any other situation, currently only format 1 ohmUrl can be returned.
 */
std::string BuildOhmUrl(const std::string& bundleName, const std::string& moduleName, const std::string& pagePath)
{
    std::string tempUrl = OHMURL_START_TAG + bundleName + "/" + moduleName;
    std::string ohmUrl = tempUrl + "/ets/" + pagePath;
    auto pos = pagePath.rfind("../");
    if (pos == std::string::npos) {
        return ohmUrl;
    }
    std::string newPagePath = pagePath.substr(pos + 3);
    pos = newPagePath.find("/");
    if (pos == std::string::npos) {
        return ohmUrl;
    }
    std::string harModuleName = newPagePath.substr(0, pos);
    pos = newPagePath.find("ets");
    if (pos == std::string::npos) {
        return ohmUrl;
    }
    newPagePath = newPagePath.substr(pos);
    return tempUrl + "@" + harModuleName + "/" + newPagePath;
}

bool ParseNamedRouterParams(const EcmaVM* vm, const panda::Local<panda::ObjectRef>& params, std::string& bundleName,
    std::string& moduleName, std::string& pagePath, std::string& pageFullPath, std::string& ohmUrl)
{
    auto jsBundleName = params->Get(vm, panda::StringRef::NewFromUtf8(vm, "bundleName"));
    auto jsModuleName = params->Get(vm, panda::StringRef::NewFromUtf8(vm, "moduleName"));
    auto jsPagePath = params->Get(vm, panda::StringRef::NewFromUtf8(vm, "pagePath"));
    if (!jsBundleName->IsString(vm) || !jsModuleName->IsString(vm) || !jsPagePath->IsString(vm)) {
        return false;
    }
    bundleName = jsBundleName->ToString(vm)->ToString(vm);
    moduleName = jsModuleName->ToString(vm)->ToString(vm);
    pagePath = jsPagePath->ToString(vm)->ToString(vm);
    bool ohmUrlValid = false;
    if (params->Has(vm, panda::StringRef::NewFromUtf8(vm, "ohmUrl"))) {
        auto jsOhmUrl = params->Get(vm, panda::StringRef::NewFromUtf8(vm, "ohmUrl"));
        if (jsOhmUrl->IsString(vm)) {
            ohmUrl = jsOhmUrl->ToString(vm)->ToString(vm);
            ohmUrlValid = true;
        } else {
            TAG_LOGD(AceLogTag::ACE_ROUTER, "add named router record with invalid ohmUrl!");
        }
    }
    if (!ohmUrlValid) {
        TAG_LOGD(AceLogTag::ACE_ROUTER, "build ohmUrl for forward compatibility");
        ohmUrl = BuildOhmUrl(bundleName, moduleName, pagePath);
    }

    std::string integratedHspName = "false";
    // Integrated hsp adaptation
    if (params->Has(vm, panda::StringRef::NewFromUtf8(vm, "integratedHsp"))) {
        auto integratedHsp = params->Get(vm, panda::StringRef::NewFromUtf8(vm, "integratedHsp"));
        if (integratedHsp->IsString(vm)) {
            integratedHspName = integratedHsp->ToString(vm)->ToString(vm);
        }
    }
    if (integratedHspName == "true") {
        LocalScope scope(vm);
        bundleName = JSNApi::GetBundleName(const_cast<EcmaVM *>(vm));
    }

    if (params->Has(vm, panda::StringRef::NewFromUtf8(vm, "pageFullPath"))) {
        auto pageFullPathInfo = params->Get(vm, panda::StringRef::NewFromUtf8(vm, "pageFullPath"));
        if (pageFullPathInfo->IsString(vm)) {
            pageFullPath = pageFullPathInfo->ToString(vm)->ToString(vm);
        }
    }

    return true;
}
} // namespace

// -----------------------
// Start JsiDeclarativeEngineInstance
// -----------------------
std::map<std::string, std::string> JsiDeclarativeEngineInstance::mediaResourceFileMap_;

std::unique_ptr<JsonValue> JsiDeclarativeEngineInstance::currentConfigResourceData_;
std::shared_mutex JsiDeclarativeEngineInstance::sharedMutex_;

bool JsiDeclarativeEngineInstance::isModulePreloaded_ = false;
bool JsiDeclarativeEngineInstance::isModuleInitialized_ = false;
shared_ptr<JsRuntime> JsiDeclarativeEngineInstance::globalRuntime_;
std::shared_mutex JsiDeclarativeEngineInstance::globalRuntimeMutex_;

// for async task callback executed after this instance has been destroyed.
thread_local void* cardRuntime_;
thread_local shared_ptr<JsRuntime> localRuntime_;

// ArkTsCard start
thread_local bool isUnique_ = false;
// ArkTsCard end

thread_local bool isWorker_ = false;

thread_local bool isDynamicModulePreloaded_ = false;

JsiDeclarativeEngineInstance::~JsiDeclarativeEngineInstance()
{
    CHECK_RUN_ON(JS);
    LOGI("Declarative instance destroyed");

    if (runningPage_) {
        runningPage_->OnJsEngineDestroy();
    }

    if (stagingPage_) {
        stagingPage_->OnJsEngineDestroy();
    }

    if (runtime_) {
        runtime_->RegisterUncaughtExceptionHandler(nullptr);
        runtime_->Reset();
    }
    runtime_.reset();
    runtime_ = nullptr;
}

bool JsiDeclarativeEngineInstance::InitJsEnv(bool debuggerMode,
    const std::unordered_map<std::string, void*>& extraNativeObject, const shared_ptr<JsRuntime>& runtime)
{
    CHECK_RUN_ON(JS);
    ACE_SCOPED_TRACE("JsiDeclarativeEngineInstance::InitJsEnv");
    if (runtime != nullptr) {
        runtime_ = runtime;
        usingSharedRuntime_ = true;
    } else {
        runtime_.reset(new ArkJSRuntime());
    }

    if (runtime_ == nullptr) {
        EventReport::SendJsException(JsExcepType::JS_ENGINE_INIT_ERR);
        return false;
    }

#if defined(PREVIEW)
    auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime_);
    arkRuntime->SetPkgNameList(pkgNameMap_);
    arkRuntime->SetPkgAliasList(pkgAliasMap_);
    arkRuntime->SetpkgContextInfoList(pkgContextInfoMap_);
#endif
    auto container = Container::Current();
    if (container) {
        auto uid = container->GetAppRunningUniqueId();
        runtime_->SetUniqueId(uid);
    }
    runtime_->SetLogPrint(PrintLog);
    std::string libraryPath = "";
    if (debuggerMode) {
        libraryPath = ARK_DEBUGGER_LIB_PATH;
        SetDebuggerPostTask();
    }
    if (!usingSharedRuntime_ && !runtime_->Initialize(libraryPath, isDebugMode_, instanceId_)) {
        return false;
    }

    runtime_->SetEmbedderData(this);
    runtime_->RegisterUncaughtExceptionHandler(JsiBaseUtils::ReportJsErrorEvent);

#if !defined(PREVIEW)
    for (const auto& [key, value] : extraNativeObject) {
        shared_ptr<JsValue> nativeValue = runtime_->NewNativePointer(value);
        runtime_->GetGlobal()->SetProperty(runtime_, key, nativeValue);
    }

    auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime_);
    arkRuntime->SetLanguage("ets");
    runtime_->StartDebugger();
#else
    if (usingSharedRuntime_) {
        auto global = runtime_->GetGlobal();
        JsiTimerModule::GetInstance()->InitTimerModule(runtime_, global);
    }
#endif
    return true;
}

void JsiDeclarativeEngineInstance::InitJsObject()
{
    CHECK_RUN_ON(JS);
    LocalScope scope(std::static_pointer_cast<ArkJSRuntime>(runtime_)->GetEcmaVm());
    if (!isModulePreloaded_ || !usingSharedRuntime_) {
        InitGlobalObjectTemplate();
    }

    // no need to initialize functions on global when use shared runtime
    if (!usingSharedRuntime_ || !isModuleInitialized_ || isUnique_) { // ArtTsCard
        InitGroupJsBridge();
        if (!isModulePreloaded_ || !usingSharedRuntime_ || isUnique_) { // ArtTsCard
            InitConsoleModule();
            InitAceModule();
            InitJsExportsUtilObject();
            InitJsNativeModuleObject();
            InitPerfUtilModule();
            InitJsContextModuleObject();
        }
    } else {
        auto container = Container::Current();
        if (container && container->IsDynamicRender() && !isDynamicModulePreloaded_) {
            isDynamicModulePreloaded_ = true;
            LOGD("init ace module for dynamic component");
            auto vm = std::static_pointer_cast<ArkJSRuntime>(runtime_)->GetEcmaVm();
            LocalScope scope(vm);
            RegisterStringCacheTable(vm, MAX_STRING_CACHE_SIZE);
            // preload js views
            JsRegisterViews(JSNApi::GetGlobalObject(vm));

            shared_ptr<JsValue> global = runtime_->GetGlobal();

            PreloadConsole(runtime_, global);
            PreloadAceConsole(runtime_, global);
            PreloadAceTrace(runtime_, global);

            // preload getContext
            JsiContextModule::GetInstance()->InitContextModule(runtime_, global);

            PreloadPerfutil(runtime_, global);
            PreloadExports(runtime_, global);
            PreloadRequireNative(runtime_, global);
            PreloadStateManagement(runtime_);
            PreloadUIContent(runtime_);
            PreloadArkComponent(runtime_);
            PreloadArkTheme(runtime_);
        }
    }

    if (usingSharedRuntime_) {
        isModuleInitialized_ = true;
    }

    // load resourceConfig
    std::unique_lock<std::shared_mutex> lock(sharedMutex_);
    currentConfigResourceData_ = JsonUtil::CreateArray(true);
    frontendDelegate_->LoadResourceConfiguration(mediaResourceFileMap_, currentConfigResourceData_);
    isEngineInstanceInitialized_ = true;
}

bool JsiDeclarativeEngineInstance::FireJsEvent(const std::string& eventStr)
{
    return true;
}

void JsiDeclarativeEngineInstance::InitAceModule()
{
    if (isUnique_ == false) {
        PreloadStateManagement(runtime_);
        PreloadJsEnums(runtime_);
        PreloadArkComponent(runtime_);
        PreloadArkTheme(runtime_);
        PreloadUIContent(runtime_);
    }
#if defined(PREVIEW)
    std::string jsMockSystemPluginString(_binary_jsMockSystemPlugin_abc_start,
        _binary_jsMockSystemPlugin_abc_end - _binary_jsMockSystemPlugin_abc_start);
    runtime_->EvaluateJsCode((uint8_t*)(jsMockSystemPluginString.c_str()), jsMockSystemPluginString.length());
    const std::string filename = "apiMock/jsMockHmos.abc";
    std::string content;
    if (!frontendDelegate_->GetAssetContent(filename, content)) {
        LOGW("Failed to get the content from the file %{public}s", filename.c_str());
        return;
    }
    if (!runtime_->EvaluateJsCode((uint8_t*)(content.c_str()), content.length())) {
        LOGW("EvaluateJsCode jsMockHmos failed");
    }
#endif
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_PreloadAceModuleWorker(void* runtime)
{
    JsiDeclarativeEngineInstance::PreloadAceModuleWorker(runtime);
}

void JsiDeclarativeEngineInstance::PreloadAceModuleWorker(void* runtime)
{
    isWorker_ = true;
    auto sharedRuntime = reinterpret_cast<NativeEngine*>(runtime);

    if (!sharedRuntime) {
        return;
    }
    std::shared_ptr<ArkJSRuntime> arkRuntime = std::make_shared<ArkJSRuntime>();
    auto nativeArkEngine = static_cast<ArkNativeEngine*>(sharedRuntime);
    EcmaVM* vm = const_cast<EcmaVM*>(nativeArkEngine->GetEcmaVm());
    if (vm == nullptr) {
        return;
    }
    if (!arkRuntime->InitializeFromExistVM(vm)) {
        return;
    }
    arkRuntime->SetNativeEngine(nativeArkEngine);
    localRuntime_ = arkRuntime;
    LocalScope scope(vm);

    RegisterStringCacheTable(vm, MAX_STRING_CACHE_SIZE);
    // preload js views
    shared_ptr<JsValue> global = arkRuntime->GetGlobal();
    JsRegisterWorkerViews(JSNApi::GetGlobalObject(vm), runtime);

    // preload js enums
    PreloadJsEnums(arkRuntime);

    // preload requireNative
    JSMock::PreloadWorkerRequireNative(arkRuntime, global);
}

void JsiDeclarativeEngineInstance::ResetModulePreLoadFlag()
{
    isModulePreloaded_ = false;
    isModuleInitialized_ = false;
}

void JsiDeclarativeEngineInstance::PrepareForResetModulePreLoadFlag()
{
    ElementRegister::GetInstance()->RegisterJSCleanUpIdleTaskFunc(nullptr);
    JsiDeclarativeEngine::ResetNamedRouterRegisterMap();
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_PreloadAceModule(void* runtime)
{
    JsiDeclarativeEngineInstance::PreloadAceModule(runtime);
}

void JsiDeclarativeEngineInstance::PreloadAceModule(void* runtime)
{
#ifndef NG_BUILD
    if (AceForwardCompatibility::PipelineChanged()) {
        isModulePreloaded_ = false;
    }
#endif
    if (isModulePreloaded_ && !IsPlugin()) {
        return;
    }
    auto sharedRuntime = reinterpret_cast<NativeEngine*>(runtime);

    if (!sharedRuntime) {
        return;
    }
    std::shared_ptr<ArkJSRuntime> arkRuntime = std::make_shared<ArkJSRuntime>();
    auto nativeArkEngine = static_cast<ArkNativeEngine*>(sharedRuntime);
    EcmaVM* vm = const_cast<EcmaVM*>(nativeArkEngine->GetEcmaVm());
    if (vm == nullptr) {
        return;
    }
    if (!arkRuntime->InitializeFromExistVM(vm)) {
        return;
    }
    LocalScope scope(vm);
    {
        std::unique_lock<std::shared_mutex> lock(globalRuntimeMutex_);
        globalRuntime_ = arkRuntime;
    }

    RegisterStringCacheTable(vm, MAX_STRING_CACHE_SIZE);
    // preload js views
    JsRegisterViews(JSNApi::GetGlobalObject(vm), runtime);

    // preload aceConsole
    shared_ptr<JsValue> global = arkRuntime->GetGlobal();
    PreloadAceConsole(arkRuntime, global);

    // preload aceTrace
    PreloadAceTrace(arkRuntime, global);

    // preload getContext
    JsiContextModule::GetInstance()->InitContextModule(arkRuntime, global);

    // preload perfutil
    PreloadPerfutil(arkRuntime, global);

    // preload exports and requireNative
    PreloadExports(arkRuntime, global);
    PreloadRequireNative(arkRuntime, global);

#ifdef CROSS_PLATFORM
    JsiSyscapModule::GetInstance()->InitSyscapModule(arkRuntime, global);
#endif

    // preload js enums
    bool jsEnumStyleResult = PreloadJsEnums(arkRuntime);
    if (!jsEnumStyleResult) {
        std::unique_lock<std::shared_mutex> lock(globalRuntimeMutex_);
        globalRuntime_ = nullptr;
        return;
    }

    bool evalResult = PreloadStateManagement(arkRuntime);

    PreloadUIContent(arkRuntime);

    // preload ark component
    bool arkComponentResult = PreloadArkComponent(arkRuntime);
    if (!arkComponentResult) {
        std::unique_lock<std::shared_mutex> lock(globalRuntimeMutex_);
        globalRuntime_ = nullptr;
        return;
    }

    // preload ark styles
    bool arkThemeResult = PreloadArkTheme(arkRuntime);
    if (!arkThemeResult) {
        std::unique_lock<std::shared_mutex> lock(globalRuntimeMutex_);
        globalRuntime_ = nullptr;
        return;
    }

    isModulePreloaded_ = evalResult;
    {
        std::unique_lock<std::shared_mutex> lock(globalRuntimeMutex_);
        globalRuntime_ = nullptr;
    }
    localRuntime_ = arkRuntime;
    cardRuntime_ = runtime;
}

void JsiDeclarativeEngineInstance::InitConsoleModule()
{
    ACE_SCOPED_TRACE("JsiDeclarativeEngineInstance::InitConsoleModule");
    shared_ptr<JsValue> global = runtime_->GetGlobal();

    // app log method
    if (!usingSharedRuntime_) {
        PreloadConsole(runtime_, global);
    }

    if (isModulePreloaded_ && usingSharedRuntime_ && !IsPlugin() && !isUnique_) { // ArkTsCard
        return;
    }

    // js framework log method
    PreloadAceConsole(runtime_, global);

    // js framework trace method
    PreloadAceTrace(runtime_, global);
}

void JsiDeclarativeEngineInstance::InitConsoleModule(ArkNativeEngine* engine)
{
    ACE_SCOPED_TRACE("JsiDeclarativeEngineInstance::RegisterConsoleModule");
    napi_env env = reinterpret_cast<napi_env>(engine);
    napi_value globalObj;
    napi_get_global(env, &globalObj);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, globalObj, &valueType);
    if (valueType != napi_object) {
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

void JsiDeclarativeEngineInstance::InitPerfUtilModule()
{
    ACE_SCOPED_TRACE("JsiDeclarativeEngineInstance::InitPerfUtilModule");
    shared_ptr<JsValue> global = runtime_->GetGlobal();
    PreloadPerfutil(runtime_, global);
}

void JsiDeclarativeEngineInstance::InitJsExportsUtilObject()
{
    shared_ptr<JsValue> global = runtime_->GetGlobal();
    PreloadExports(runtime_, global);
}

void JsiDeclarativeEngineInstance::InitJsNativeModuleObject()
{
    shared_ptr<JsValue> global = runtime_->GetGlobal();
    PreloadRequireNative(runtime_, global);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    if (!usingSharedRuntime_) {
        if (!context->IsFormRender()) {
            JsiTimerModule::GetInstance()->InitTimerModule(runtime_, global);
        }

        JsiSyscapModule::GetInstance()->InitSyscapModule(runtime_, global);
    }
}

void JsiDeclarativeEngineInstance::InitJsContextModuleObject()
{
    JsiContextModule::GetInstance()->InitContextModule(runtime_, runtime_->GetGlobal());
}

void JsiDeclarativeEngineInstance::InitGlobalObjectTemplate()
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(runtime_);
    RegisterStringCacheTable(runtime->GetEcmaVm(), MAX_STRING_CACHE_SIZE);
    JsRegisterViews(JSNApi::GetGlobalObject(runtime->GetEcmaVm()), reinterpret_cast<void*>(nativeEngine_));
}

void JsiDeclarativeEngineInstance::InitGroupJsBridge()
{
    auto groupJsBridge = DynamicCast<JsiDeclarativeGroupJsBridge>(frontendDelegate_->GetGroupJsBridge());
    if (groupJsBridge == nullptr || groupJsBridge->InitializeGroupJsBridge(runtime_) == JS_CALL_FAIL) {
        EventReport::SendJsException(JsExcepType::JS_ENGINE_INIT_ERR);
    }
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(runtime_);
    JsUINodeRegisterCleanUp(JSNApi::GetGlobalObject(runtime->GetEcmaVm()));
}

void JsiDeclarativeEngineInstance::RootViewHandle(panda::Local<panda::ObjectRef> value)
{
    RefPtr<JsAcePage> page = JsiDeclarativeEngineInstance::GetStagingPage(Container::CurrentId());
    if (page != nullptr) {
        auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(GetCurrentRuntime());
        if (!arkRuntime) {
            return;
        }
        auto engine = EngineHelper::GetCurrentEngine();
        auto jsiEngine = AceType::DynamicCast<JsiDeclarativeEngine>(engine);
        if (!jsiEngine) {
            return;
        }
        auto engineInstance = jsiEngine->GetEngineInstance();
        if (engineInstance == nullptr) {
            return;
        }
        engineInstance->SetRootView(page->GetPageId(), panda::Global<panda::ObjectRef>(arkRuntime->GetEcmaVm(), value));
    }
}

void JsiDeclarativeEngineInstance::DestroyRootViewHandle(int32_t pageId)
{
    CHECK_RUN_ON(JS);
    JAVASCRIPT_EXECUTION_SCOPE_STATIC;
    auto iter = rootViewMap_.find(pageId);
    if (iter != rootViewMap_.end()) {
        auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime_);
        if (!arkRuntime) {
            return;
        }
        panda::Local<panda::ObjectRef> rootView = iter->second.ToLocal(arkRuntime->GetEcmaVm());
        auto* jsView = JsiObjectTemplate::GetNativeView(rootView, arkRuntime->GetEcmaVm());
        if (jsView != nullptr) {
            jsView->Destroy(nullptr);
        }
        iter->second.FreeGlobalHandleAddr();
        rootViewMap_.erase(pageId);
    }
}

void JsiDeclarativeEngineInstance::DestroyAllRootViewHandle()
{
    CHECK_RUN_ON(JS);
    JAVASCRIPT_EXECUTION_SCOPE_STATIC;
    auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime_);
    if (!arkRuntime) {
        return;
    }
    for (const auto& pair : rootViewMap_) {
        auto globalRootView = pair.second;
        panda::Local<panda::ObjectRef> rootView = globalRootView.ToLocal(arkRuntime->GetEcmaVm());
        auto* jsView = JsiObjectTemplate::GetNativeView(rootView, arkRuntime->GetEcmaVm());
        if (jsView != nullptr) {
            jsView->Destroy(nullptr);
        }
        globalRootView.FreeGlobalHandleAddr();
    }
    rootViewMap_.clear();
}

void JsiDeclarativeEngineInstance::FlushReload()
{
    CHECK_RUN_ON(JS);
    JAVASCRIPT_EXECUTION_SCOPE_STATIC;
    if (rootViewMap_.empty()) {
        return;
    }
    auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime_);
    if (!arkRuntime) {
        return;
    }
    for (const auto& pair : rootViewMap_) {
        auto globalRootView = pair.second;
        panda::Local<panda::ObjectRef> rootView = globalRootView.ToLocal(arkRuntime->GetEcmaVm());
        auto* jsView = JsiObjectTemplate::GetNativeView(rootView, arkRuntime->GetEcmaVm());
        if (jsView != nullptr) {
            jsView->MarkNeedUpdate();
        }
    }
}

std::unique_ptr<JsonValue> JsiDeclarativeEngineInstance::GetI18nStringResource(
    const std::string& targetStringKey, const std::string& targetStringValue)
{
    std::shared_lock<std::shared_mutex> lock(sharedMutex_);
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
        return nullptr;
    }
    auto engineInstance = jsiEngine->GetEngineInstance();
    if (engineInstance == nullptr) {
        return nullptr;
    }
    return engineInstance->GetRunningPage();
}

RefPtr<JsAcePage> JsiDeclarativeEngineInstance::GetStagingPage(int32_t instanceId)
{
    auto engine = EngineHelper::GetEngine(instanceId);
    auto jsiEngine = AceType::DynamicCast<JsiDeclarativeEngine>(engine);
    if (!jsiEngine) {
        return nullptr;
    }
    auto engineInstance = jsiEngine->GetEngineInstance();
    if (engineInstance == nullptr) {
        return nullptr;
    }
    return engineInstance->GetStagingPage();
}

shared_ptr<JsRuntime> JsiDeclarativeEngineInstance::GetCurrentRuntime()
{
    auto jsRuntime = InnerGetCurrentRuntime();
    if (isUnique_ && jsRuntime) {
        return jsRuntime;
    }

    // ArkTsCard
    if (isUnique_ && localRuntime_) {
        return localRuntime_;
    }

    if (isWorker_ && localRuntime_) {
        return localRuntime_;
    }

    // Preload
    std::shared_lock<std::shared_mutex> lock(globalRuntimeMutex_);
    if (globalRuntime_) {
        return globalRuntime_;
    }

    return jsRuntime == nullptr ? localRuntime_ : jsRuntime;
}

shared_ptr<JsRuntime> JsiDeclarativeEngineInstance::InnerGetCurrentRuntime()
{
    auto engine = EngineHelper::GetCurrentEngine();
    auto jsiEngine = AceType::DynamicCast<JsiDeclarativeEngine>(engine);
    if (!jsiEngine) {
        return nullptr;
    }

    auto engineInstance = jsiEngine->GetEngineInstance();
    if (engineInstance == nullptr) {
        return nullptr;
    }

    if (isUnique_ && !engineInstance->IsEngineInstanceInitialized()) {
        return nullptr;
    }

    return engineInstance->GetJsRuntime();
}

shared_ptr<JsValue> JsiDeclarativeEngineInstance::CallGetUIContextFunc(
    const shared_ptr<JsRuntime>& runtime, const std::vector<shared_ptr<JsValue>>& argv)
{
    shared_ptr<JsValue> global = runtime->GetGlobal();
    shared_ptr<JsValue> func = global->GetProperty(runtime, "__getUIContext__");
    if (!func->IsFunction(runtime)) {
        return nullptr;
    }

    shared_ptr<JsValue> retVal = func->Call(runtime, global, argv, argv.size());
    if (!retVal) {
        return nullptr;
    }

    return retVal;
}

shared_ptr<JsValue> JsiDeclarativeEngineInstance::CallGetFrameNodeByNodeIdFunc(
    const shared_ptr<JsRuntime>& runtime, const std::vector<shared_ptr<JsValue>>& argv)
{
    shared_ptr<JsValue> global = runtime->GetGlobal();
    shared_ptr<JsValue> func = global->GetProperty(runtime, "__getFrameNodeByNodeId__");
    if (!func->IsFunction(runtime)) {
        return nullptr;
    }

    shared_ptr<JsValue> retVal = func->Call(runtime, global, argv, argv.size());
    if (!retVal) {
        return nullptr;
    }

    return retVal;
}

void JsiDeclarativeEngineInstance::PostJsTask(
    const shared_ptr<JsRuntime>& runtime, std::function<void()>&& task, const std::string& name)
{
    if (runtime == nullptr) {
        return;
    }
    auto engineInstance = static_cast<JsiDeclarativeEngineInstance*>(runtime->GetEmbedderData());
    if (engineInstance == nullptr) {
        return;
    }
    engineInstance->GetDelegate()->PostJsTask(std::move(task), name);
}

void JsiDeclarativeEngineInstance::TriggerPageUpdate(const shared_ptr<JsRuntime>& runtime)
{
    CHECK_NULL_VOID(runtime);
    auto engineInstance = static_cast<JsiDeclarativeEngineInstance*>(runtime->GetEmbedderData());
    CHECK_NULL_VOID(engineInstance);
    auto page = engineInstance->GetRunningPage();
    CHECK_NULL_VOID(page);
    engineInstance->GetDelegate()->TriggerPageUpdate(page->GetPageId());
}

RefPtr<PipelineBase> JsiDeclarativeEngineInstance::GetPipelineContext(const shared_ptr<JsRuntime>& runtime)
{
    if (runtime == nullptr) {
        return nullptr;
    }
    auto engineInstance = static_cast<JsiDeclarativeEngineInstance*>(runtime->GetEmbedderData());
    if (engineInstance == nullptr) {
        return nullptr;
    }
    return engineInstance->GetDelegate()->GetPipelineContext();
}

void JsiDeclarativeEngineInstance::FlushCommandBuffer(void* context, const std::string& command)
{
    return;
}

bool JsiDeclarativeEngineInstance::IsPlugin()
{
    return (ContainerScope::CurrentId() >= MIN_PLUGIN_SUBCONTAINER_ID);
}

void JsiDeclarativeEngineInstance::SetDebuggerPostTask()
{
    auto weakDelegate = AceType::WeakClaim(AceType::RawPtr(frontendDelegate_));
    auto&& postTask = [weakDelegate](std::function<void()>&& task) {
        auto delegate = weakDelegate.Upgrade();
        if (delegate == nullptr) {
            return;
        }
        delegate->PostJsTask(std::move(task), "ArkUIDebuggerTask");
    };
    std::static_pointer_cast<ArkJSRuntime>(runtime_)->SetDebuggerPostTask(postTask);
}

void JsiDeclarativeEngineInstance::RegisterFaPlugin()
{
    shared_ptr<JsValue> global = runtime_->GetGlobal();
    shared_ptr<JsValue> requireNapiFunc = global->GetProperty(runtime_, "requireNapi");
    if (!requireNapiFunc || !requireNapiFunc->IsFunction(runtime_)) {
        return;
    }
    std::vector<shared_ptr<JsValue>> argv = { runtime_->NewString("FeatureAbility") };
    requireNapiFunc->Call(runtime_, global, argv, argv.size());
}

napi_value JsiDeclarativeEngineInstance::GetContextValue()
{
    auto runtime = GetJsRuntime();

    // obtain uiContext instance
    std::vector<shared_ptr<JsValue>> argv = { runtime->NewNumber(instanceId_) };
    shared_ptr<JsValue> uiContext = CallGetUIContextFunc(runtime, argv);
    if (uiContext) {
        SetContextValue(uiContext);
    }

    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (!arkJSRuntime) {
        return nullptr;
    }
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(uiContext_);
    if (!arkJSValue) {
        return nullptr;
    }
    auto arkNativeEngine = static_cast<ArkNativeEngine*>(GetNativeEngine());
    if (!arkNativeEngine) {
        return nullptr;
    }
    napi_value napiValue = ArkNativeEngine::ArkValueToNapiValue(
        reinterpret_cast<napi_env>(GetNativeEngine()), arkJSValue->GetValue(arkJSRuntime));

    return napiValue;
}

napi_value JsiDeclarativeEngineInstance::GetFrameNodeValueByNodeId(int32_t nodeId)
{
    auto runtime = GetJsRuntime();

    // obtain frameNode instance
    std::vector<shared_ptr<JsValue>> argv = { runtime->NewNumber(instanceId_), runtime->NewNumber(nodeId) };
    shared_ptr<JsValue> frameNode = CallGetFrameNodeByNodeIdFunc(runtime, argv);

    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (!arkJSRuntime) {
        return nullptr;
    }
    auto arkJSValue = std::static_pointer_cast<ArkJSValue>(frameNode);
    if (!arkJSValue) {
        return nullptr;
    }
    auto arkNativeEngine = static_cast<ArkNativeEngine*>(GetNativeEngine());
    if (!arkNativeEngine) {
        return nullptr;
    }
    napi_value napiValue = ArkNativeEngine::ArkValueToNapiValue(
        reinterpret_cast<napi_env>(GetNativeEngine()), arkJSValue->GetValue(arkJSRuntime));

    return napiValue;
}

thread_local std::unordered_map<std::string, NamedRouterProperty> JsiDeclarativeEngine::namedRouterRegisterMap_;
thread_local std::unordered_map<std::string, std::string> JsiDeclarativeEngine::routerPathInfoMap_;
thread_local std::unordered_map<std::string, panda::Global<panda::ObjectRef>> JsiDeclarativeEngine::builderMap_;
thread_local panda::Global<panda::ObjectRef> JsiDeclarativeEngine::obj_;

// -----------------------
// Start JsiDeclarativeEngine
// -----------------------
JsiDeclarativeEngine::~JsiDeclarativeEngine()
{
    CHECK_RUN_ON(JS);
    LOGI("Declarative engine destroyed");
}

void JsiDeclarativeEngine::Destroy()
{
    CHECK_RUN_ON(JS);

#ifdef USE_ARK_ENGINE
    JSLocalStorage::RemoveStorage(instanceId_);
    JsiContextModule::RemoveContext(instanceId_);
#endif

    engineInstance_->GetDelegate()->RemoveTaskObserver();
    engineInstance_->DestroyAllRootViewHandle();
    if (isUnique_) {
        RunFullGarbageCollection();
    }

    if (!runtime_ && nativeEngine_ != nullptr) {
#if !defined(PREVIEW)
        nativeEngine_->CancelCheckUVLoop();
#endif
        delete nativeEngine_;
        nativeEngine_ = nullptr;
    }
}

bool JsiDeclarativeEngine::Initialize(const RefPtr<FrontendDelegate>& delegate)
{
    CHECK_RUN_ON(JS);
    ACE_SCOPED_TRACE("JsiDeclarativeEngine::Initialize");
    ACE_DCHECK(delegate);
    NG::UIContextHelper::RegisterRemoveUIContextFunc();
    engineInstance_ = AceType::MakeRefPtr<JsiDeclarativeEngineInstance>(delegate);
    auto sharedRuntime = reinterpret_cast<NativeEngine*>(runtime_);
    std::shared_ptr<ArkJSRuntime> arkRuntime;
    EcmaVM* vm = nullptr;
    if (sharedRuntime) {
        arkRuntime = std::make_shared<ArkJSRuntime>();
        if (isUnique_ && reinterpret_cast<NativeEngine*>(cardRuntime_) != nullptr) {
            sharedRuntime = reinterpret_cast<NativeEngine*>(cardRuntime_);
        }
        auto nativeArkEngine = static_cast<ArkNativeEngine*>(sharedRuntime);
        vm = const_cast<EcmaVM*>(nativeArkEngine->GetEcmaVm());
        if (vm == nullptr) {
            return false;
        }
        if (!arkRuntime->InitializeFromExistVM(vm)) {
            return false;
        }
        nativeEngine_ = nativeArkEngine;
        arkRuntime->SetNativeEngine(nativeArkEngine);
    }
    engineInstance_->SetInstanceId(instanceId_);
    engineInstance_->SetDebugMode(NeedDebugBreakPoint());
#if defined(PREVIEW)
    engineInstance_->SetPkgNameList(pkgNameMap_);
    engineInstance_->SetPkgAliasList(pkgAliasMap_);
    engineInstance_->SetpkgContextInfoList(pkgContextInfoMap_);
#endif
    bool result = engineInstance_->InitJsEnv(IsDebugVersion(), GetExtraNativeObject(), arkRuntime);
    if (!result) {
        return false;
    }

    auto runtime = engineInstance_->GetJsRuntime();
    vm = vm ? vm : const_cast<EcmaVM*>(std::static_pointer_cast<ArkJSRuntime>(runtime)->GetEcmaVm());
    if (vm == nullptr) {
        return false;
    }

    if (nativeEngine_ == nullptr) {
        nativeEngine_ = new ArkNativeEngine(vm, static_cast<void*>(this));
    }
    EngineTask(sharedRuntime);
    return result;
}

void JsiDeclarativeEngine::EngineTask(bool sharedRuntime)
{
    engineInstance_->SetNativeEngine(nativeEngine_);
    engineInstance_->InitJsObject();
    if (!sharedRuntime) {
        SetPostTask(nativeEngine_);
#if !defined(PREVIEW)
        nativeEngine_->CheckUVLoop();
#endif
        RegisterWorker();
        engineInstance_->RegisterFaPlugin();
    }
}

void JsiDeclarativeEngine::SetPostTask(NativeEngine* nativeEngine)
{
    auto weakDelegate = WeakPtr(engineInstance_->GetDelegate());
    auto&& postTask = [weakDelegate, weakEngine = AceType::WeakClaim(this), id = instanceId_](bool needSync) {
        auto delegate = weakDelegate.Upgrade();
        if (delegate == nullptr) {
            return;
        }
        delegate->PostJsTask(
            [weakEngine, needSync, id]() {
                auto jsEngine = weakEngine.Upgrade();
                if (jsEngine == nullptr) {
                    return;
                }
                auto nativeEngine = jsEngine->GetNativeEngine();
                if (nativeEngine == nullptr) {
                    return;
                }
                ContainerScope scope(id);
                nativeEngine->Loop(LOOP_NOWAIT, needSync);
            },
            "ArkUISetNativeEngineLoop");
    };
    nativeEngine_->SetPostTask(postTask);
}

void JsiDeclarativeEngine::RegisterInitWorkerFunc()
{
    auto weakInstance = AceType::WeakClaim(AceType::RawPtr(engineInstance_));
    bool debugVersion = IsDebugVersion();
    std::string libraryPath = "";
    if (debugVersion) {
        libraryPath = ARK_DEBUGGER_LIB_PATH;
    }
    auto&& initWorkerFunc = [weakInstance, libraryPath, debugVersion](
                                NativeEngine* nativeEngine) {
        if (nativeEngine == nullptr) {
            return;
        }
        auto arkNativeEngine = static_cast<ArkNativeEngine*>(nativeEngine);
        if (arkNativeEngine == nullptr) {
            return;
        }
        auto instance = weakInstance.Upgrade();
        if (instance == nullptr) {
            return;
        }
#ifdef OHOS_PLATFORM
        auto tid = gettid();
        ConnectServerManager::Get().AddInstance(tid, "ets");
        auto vm = const_cast<EcmaVM*>(arkNativeEngine->GetEcmaVm());
        auto workerPostTask = [nativeEngine](std::function<void()>&& callback) {
            nativeEngine->CallDebuggerPostTaskFunc(std::move(callback));
        };
        bool debugMode = AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint();
        panda::JSNApi::DebugOption debugOption = { libraryPath.c_str(), debugMode, -1, true }; //FA:true port:-1
        JSNApi::NotifyDebugMode(tid, vm, debugOption, tid, workerPostTask, debugVersion);
#endif
        instance->InitConsoleModule(arkNativeEngine);

        std::vector<uint8_t> buffer((uint8_t*)_binary_jsEnumStyle_abc_start, (uint8_t*)_binary_jsEnumStyle_abc_end);
        arkNativeEngine->RunBufferScript(buffer);
    };
    nativeEngine_->SetInitWorkerFunc(initWorkerFunc);
}

#ifdef OHOS_PLATFORM
void JsiDeclarativeEngine::RegisterOffWorkerFunc()
{
    auto weakInstance = AceType::WeakClaim(AceType::RawPtr(engineInstance_));
    bool debugVersion = IsDebugVersion();
    auto&& offWorkerFunc = [debugVersion](NativeEngine* nativeEngine) {
        if (!debugVersion) {
            return;
        }
        if (nativeEngine == nullptr) {
            return;
        }
        auto arkNativeEngine = static_cast<ArkNativeEngine*>(nativeEngine);
        if (arkNativeEngine == nullptr) {
            return;
        }
        ConnectServerManager::Get().RemoveInstance(gettid());
        auto vm = const_cast<EcmaVM*>(arkNativeEngine->GetEcmaVm());
        panda::JSNApi::StopDebugger(vm);
    };
    nativeEngine_->SetOffWorkerFunc(offWorkerFunc);
}
#endif

void JsiDeclarativeEngine::RegisterAssetFunc()
{
    auto weakDelegate = WeakPtr(engineInstance_->GetDelegate());
    auto&& assetFunc = [weakDelegate](const std::string& uri, uint8_t** buff, size_t* buffSize,
        std::vector<uint8_t>& content, std::string& ami, bool& useSecureMem, void** mapper, bool isRestricted) {
        auto delegate = weakDelegate.Upgrade();
        if (delegate == nullptr) {
            return;
        }
        size_t index = uri.find_last_of(".");
        if (index != std::string::npos) {
            delegate->GetResourceData(uri.substr(0, index) + ".abc", content, ami);
            useSecureMem = false;
        }
    };
    nativeEngine_->SetGetAssetFunc(assetFunc);
}

void JsiDeclarativeEngine::RegisterWorker()
{
    RegisterInitWorkerFunc();
#ifdef OHOS_PLATFORM
    RegisterOffWorkerFunc();
#endif
    RegisterAssetFunc();
}

bool JsiDeclarativeEngine::ExecuteAbc(const std::string& fileName)
{
    ACE_SCOPED_TRACE("JsiDeclarativeEngine::ExecuteAbc Execute Page code : %s", fileName.c_str());
    auto runtime = engineInstance_->GetJsRuntime();
    auto delegate = engineInstance_->GetDelegate();
    std::vector<uint8_t> content;
    if (!delegate->GetAssetContent(fileName, content)) {
        return true;
    }
#if !defined(PREVIEW)
    const std::string abcPath = delegate->GetAssetPath(fileName).append(fileName);
#else
    const std::string& abcPath = fileName;
#endif
    if (!runtime->EvaluateJsCode(content.data(), content.size(), abcPath, needUpdate_)) {
        return false;
    }
    return true;
}

bool JsiDeclarativeEngine::ExecuteJs(const uint8_t* content, int32_t size)
{
    auto runtime = engineInstance_->GetJsRuntime();
    CHECK_NULL_RETURN(runtime, false);
    if (!runtime->EvaluateJsCode(content, size)) {
        return false;
    }
    return true;
}

bool JsiDeclarativeEngine::ExecuteCardAbc(const std::string& fileName, int64_t cardId)
{
    auto runtime = engineInstance_->GetJsRuntime();
    CHECK_NULL_RETURN(runtime, false);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    CardScope cardScope(cardId);
    std::string abcPath;
    std::vector<uint8_t> content;
    if (container->IsFRSCardContainer()) {
        auto frontEnd = AceType::DynamicCast<FormFrontendDeclarative>(container->GetCardFrontend(cardId).Upgrade());
        CHECK_NULL_RETURN(frontEnd, false);
        auto delegate = frontEnd->GetDelegate();
        CHECK_NULL_RETURN(delegate, false);
        if (frontEnd->IsBundle()) {
            if (!delegate->GetAssetContent(fileName, content)) {
                return false;
            }
            abcPath = delegate->GetAssetPath(fileName).append(fileName);
            if (!runtime->EvaluateJsCode(content.data(), content.size(), abcPath)) {
                return false;
            }
            return true;
        }
        if (!delegate->GetAssetContent(FORM_ES_MODULE_CARD_PATH, content)) {
            return false;
        }
        const std::string bundleName = frontEnd->GetBundleName();
        std::string moduleName = frontEnd->GetModuleName();
#ifdef PREVIEW
        const std::string assetPath = delegate->GetAssetPath(FORM_ES_MODULE_CARD_PATH).append(FORM_ES_MODULE_CARD_PATH);
#else
        const std::string assetPath =
            ASSET_PATH_PREFIX + bundleName + "/" + moduleName + "/" + FORM_ES_MODULE_CARD_PATH;
#endif
        auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
        CHECK_NULL_RETURN(arkRuntime, false);
        arkRuntime->SetBundleName(bundleName);
        arkRuntime->SetAssetPath(assetPath);
        arkRuntime->SetBundle(false);
        arkRuntime->SetModuleName(moduleName);
#ifdef PREVIEW
        // remove the prefix of "ets/"
        abcPath = fileName.substr(PREFIX_LETTER_NUMBER);
#else
        abcPath = moduleName.append("/").append(fileName);
#endif
        {
            if (!arkRuntime->ExecuteModuleBuffer(content.data(), content.size(), abcPath, true)) {
                return false;
            }
        }
        return true;
    } else {
        auto frontEnd = AceType::DynamicCast<CardFrontendDeclarative>(container->GetCardFrontend(cardId).Upgrade());
        CHECK_NULL_RETURN(frontEnd, false);
        auto delegate = frontEnd->GetDelegate();
        CHECK_NULL_RETURN(delegate, false);
        if (!delegate->GetAssetContent(fileName, content)) {
            return false;
        }
        abcPath = delegate->GetAssetPath(fileName).append(fileName);
    }
    if (!runtime->EvaluateJsCode(content.data(), content.size(), abcPath)) {
        return false;
    }
    return true;
}

bool JsiDeclarativeEngine::ExecuteDynamicAbc(const std::string& fileName, const std::string& entryPoint)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto uiContentType = container->GetUIContentType();
    LOGI("ExecuteDynamicAbc uiContentType: %{public}d", static_cast<int32_t>(uiContentType));
    if (uiContentType == UIContentType::DYNAMIC_COMPONENT) {
        return InnerExecuteDynamicAbc(fileName, entryPoint);
    }

    return InnerExecuteIsolatedAbc(fileName, entryPoint);
}

bool JsiDeclarativeEngine::InnerExecuteIsolatedAbc(
    const std::string& fileName, const std::string& entryPoint)
{
    CHECK_NULL_RETURN(runtime_, false);
    auto engine = reinterpret_cast<NativeEngine*>(runtime_);
    CHECK_NULL_RETURN(engine, false);
    auto vm = engine->GetEcmaVm();
    CHECK_NULL_RETURN(vm, false);
    panda::TryCatch trycatch(vm);

    panda::JSNApi::SetModuleInfo(const_cast<EcmaVM*>(vm), ASSET_PATH_PREFIX + fileName, entryPoint);
    if (trycatch.HasCaught()) {
        engine->lastException_ = trycatch.GetException();
        return false;
    }

    engine->RunScriptForAbc(fileName.c_str(), const_cast<char*>(entryPoint.c_str()));
    if (trycatch.HasCaught()) {
        engine->lastException_ = trycatch.GetException();
        return false;
    }
    return true;
}

bool JsiDeclarativeEngine::InnerExecuteDynamicAbc(
    const std::string& fileName, const std::string& entryPoint)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    CHECK_NULL_RETURN(runtime_, false);
    auto engine = reinterpret_cast<NativeEngine*>(runtime_);
    CHECK_NULL_RETURN(engine, false);
    auto vm = engine->GetEcmaVm();
    CHECK_NULL_RETURN(vm, false);
    CHECK_NULL_RETURN(engineInstance_, false);
    auto runtime = engineInstance_->GetJsRuntime();
    CHECK_NULL_RETURN(runtime, false);
    auto arkJsRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    CHECK_NULL_RETURN(arkJsRuntime, false);
    auto frontend = AceType::DynamicCast<FormFrontendDeclarative>(container->GetFrontend());
    CHECK_NULL_RETURN(frontend, false);
    auto bundleName = frontend->GetBundleName();
    auto moduleName = frontend->GetModuleName();
    if (bundleName.empty() || moduleName.empty()) {
        LOGW("Get bundleName(%{public}s) or moduleName(%{public}s) failed",
            bundleName.c_str(), moduleName.c_str());
        return false;
    }

    std::string assetPath = ASSET_PATH_PREFIX + moduleName + "/" + FORM_ES_MODULE_PATH;
    LOGD("InnerExecuteDynamicAbc bundleName: %{public}s, moduleName: %{public}s, assetPath: %{public}s",
        bundleName.c_str(), moduleName.c_str(), assetPath.c_str());
    panda::TryCatch trycatch(vm);
    panda::JSNApi::SetModuleInfo(const_cast<EcmaVM*>(vm), assetPath.c_str(), entryPoint);
    if (trycatch.HasCaught()) {
        engine->lastException_ = trycatch.GetException();
        return false;
    }

    const char binExt[] = ".abc";
    std::string urlName = entryPoint.substr(bundleName.size() + 1) + binExt;
    LOGD("InnerExecuteDynamicAbc ExecuteJsBin urlName: %{public}s", urlName.c_str());
    runtime->ExecuteJsBin(urlName);
    if (trycatch.HasCaught()) {
        engine->lastException_ = trycatch.GetException();
        return false;
    }

    return true;
}

bool JsiDeclarativeEngine::UpdateRootComponent()
{
    if (!JsiDeclarativeEngine::obj_.IsEmpty()) {
        LOGI("update rootComponent start");
        LocalScope scope(obj_.GetEcmaVM());
        Framework::UpdateRootComponent(obj_.GetEcmaVM(), JsiDeclarativeEngine::obj_.ToLocal());
        // Clear the global object to avoid load this obj next time
        JsiDeclarativeEngine::obj_.FreeGlobalHandleAddr();
        JsiDeclarativeEngine::obj_.Empty();
        return true;
    }
    return false;
}

bool JsiDeclarativeEngine::LoadPluginComponent(const std::string &url, const RefPtr<JsAcePage>& page, bool isMainPage)
{
    LoadJs(url, page, isMainPage);
    if (!UpdateRootComponent()) {
        auto pagePath = url;
        if (pagePath.rfind(".js") != std::string::npos) {
            pagePath = pagePath.substr(0, pagePath.length() - strlen(".js"));
        }
        std::string pluginUrlName = OHMURL_START_TAG + pluginBundleName_ + "/" + pluginModuleName_ + "/ets/" + pagePath;
        return LoadNamedRouterSource(pluginUrlName, false);
    }
    return true;
}

void JsiDeclarativeEngine::LoadJs(const std::string& url, const RefPtr<JsAcePage>& page, bool isMainPage)
{
    ACE_SCOPED_TRACE("JsiDeclarativeEngine::LoadJs url : %s", url.c_str());
    LOGI("LoadJs page:%{public}d", page->GetPageId());
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetStagingPage(page);
    if (isMainPage) {
        ACE_DCHECK(!engineInstance_->GetRunningPage());
        engineInstance_->SetRunningPage(page);
    }
    auto runtime = engineInstance_->GetJsRuntime();
    auto delegate = engineInstance_->GetDelegate();
    auto vm = const_cast<EcmaVM*>(std::static_pointer_cast<ArkJSRuntime>(runtime)->GetEcmaVm());
    // get source map
    std::string jsSourceMap;
    if (JSNApi::IsBundle(vm)) {
        if (delegate->GetAssetContent(url + ".map", jsSourceMap)) {
            page->SetPageMap(jsSourceMap);
        }
    }
    // get js bundle content
    shared_ptr<JsValue> jsCode = runtime->NewUndefined();
    shared_ptr<JsValue> jsAppCode = runtime->NewUndefined();
    const char js_ext[] = ".js";
    const char bin_ext[] = ".abc";
    auto pos = url.rfind(js_ext);
    if (pos != std::string::npos && pos == url.length() - (sizeof(js_ext) - 1)) {
        std::string urlName = url.substr(0, pos) + bin_ext;
#if !defined(PREVIEW)
        if (IsModule()) {
            if (!engineInstance_->IsPlugin()) {
                LoadJsWithModule(urlName);
                return;
            }
            if (!pluginModuleName_.empty()) {
                LoadPluginJsWithModule(urlName);
                return;
            }
        }
#endif
        if (isMainPage) {
            if (!ExecuteAbc("commons.abc")) {
                return;
            }
            if (!ExecuteAbc("vendors.abc")) {
                return;
            }
            std::string appMap;
            if (delegate->GetAssetContent("app.js.map", appMap)) {
                page->SetAppMap(appMap);
            }
            if (ExecuteAbc("app.abc")) {
                CallAppFunc("onCreate");
            }
        }
#if !defined(PREVIEW)
        if (!ExecuteAbc(urlName)) {
            return;
        }
#else
        if (!assetPath_.empty() && !isBundle_) {
            auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
            arkRuntime->SetBundleName(bundleName_);
            arkRuntime->SetAssetPath(assetPath_);
            arkRuntime->SetBundle(isBundle_);
            arkRuntime->SetModuleName(moduleName_);
            std::vector<uint8_t> content;
            if (!delegate->GetAssetContent("modules.abc", content)) {
                LOGW("GetAssetContent \"%{public}s\" failed.", urlName.c_str());
                return;
            }
            if (!arkRuntime->ExecuteModuleBuffer(content.data(), content.size(), urlName)) {
                LOGW("EvaluateJsCode \"%{public}s\" failed.", urlName.c_str());
                return;
            }
        } else {
            ExecuteAbc(urlName);
        }
#endif
    }
}
#if !defined(PREVIEW)
bool JsiDeclarativeEngine::IsModule()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    return container->IsModule();
}

void JsiDeclarativeEngine::LoadPluginJsWithModule(std::string& urlName)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(engineInstance_->GetJsRuntime());
    auto delegate = engineInstance_->GetDelegate();
    auto pluginUrlName = OHMURL_START_TAG + pluginBundleName_ + "/" + pluginModuleName_ + "/ets/" + urlName;
    std::vector<uint8_t> content;
    if (!delegate->GetAssetContent("ets/modules.abc", content)) {
        return;
    }
    if (!runtime->ExecuteModuleBuffer(content.data(), content.size(), pluginUrlName, true)) {
        return;
    }
}

void JsiDeclarativeEngine::LoadJsWithModule(
    std::string& urlName, const std::function<void(const std::string&, int32_t)>& errorCallback)
{
    ACE_SCOPED_TRACE("JsiDeclarativeEngine::LoadJsWithModule Execute Page code : %s", urlName.c_str());
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(engineInstance_->GetJsRuntime());
    const std::string moduleName = container->GetModuleName();
    const std::string assetPath = ASSET_PATH_PREFIX + moduleName + "/" + FORM_ES_MODULE_PATH;
    runtime->SetAssetPath(assetPath);
    runtime->SetModuleName(moduleName);
    if (urlName.substr(0, strlen(BUNDLE_TAG)) != BUNDLE_TAG) {
        urlName = container->GetModuleName() + "/ets/" + urlName;
    }
    runtime->ExecuteJsBin(urlName, errorCallback);
}
#endif
// Load the app.js file of the FA model in NG structure.
bool JsiDeclarativeEngine::LoadFaAppSource()
{
    ACE_SCOPED_TRACE("JsiDeclarativeEngine::LoadFaAppSource");
    if (!ExecuteAbc("commons.abc") || !ExecuteAbc("vendors.abc") || !ExecuteAbc("app.abc")) {
        return false;
    }
    CallAppFunc("onCreate");
    return true;
}

// Load the js file of the page in NG structure..
bool JsiDeclarativeEngine::LoadPageSource(
    const std::string& url, const std::function<void(const std::string&, int32_t)>& errorCallback)
{
    ACE_SCOPED_TRACE("JsiDeclarativeEngine::LoadPageSource");
    ACE_DCHECK(engineInstance_);
    // get js bundle content
    const char jsExt[] = ".js";
    const char binExt[] = ".abc";
    std::optional<std::string> urlName;
    auto pos = url.rfind(jsExt);
    if (pos != std::string::npos && pos == url.length() - (sizeof(jsExt) - 1)) {
        urlName = url.substr(0, pos) + binExt;
    }
    if (!urlName.has_value()) {
        return false;
    }

#if !defined(PREVIEW)
    if (IsModule()) {
        LoadJsWithModule(urlName.value(), errorCallback);
        return true;
    }
#else
    auto runtime = engineInstance_->GetJsRuntime();
    auto delegate = engineInstance_->GetDelegate();
    if (!assetPath_.empty() && !isBundle_) {
        auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
        arkRuntime->SetBundleName(bundleName_);
        arkRuntime->SetAssetPath(assetPath_);
        arkRuntime->SetBundle(isBundle_);
        arkRuntime->SetModuleName(moduleName_);
        std::vector<uint8_t> content;
        if (!delegate->GetAssetContent("modules.abc", content)) {
            return false;
        }
        if (!arkRuntime->ExecuteModuleBuffer(content.data(), content.size(), urlName.value())) {
            return false;
        }
        return true;
    }
#endif
    return ExecuteAbc(urlName.value());
}

bool JsiDeclarativeEngine::LoadPageSource(
    const std::shared_ptr<std::vector<uint8_t>>& content,
    const std::function<void(const std::string&, int32_t)>& errorCallback,
    const std::string& contentName)
{
    ACE_SCOPED_TRACE("JsiDeclarativeEngine::LoadPageSource");
    LOGI("LoadJs by buffer");
    ACE_DCHECK(engineInstance_);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto runtime = engineInstance_->GetJsRuntime();
    auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (!arkRuntime->EvaluateJsCode(content->data(), content->size(), contentName)) {
        return false;
    }
    return true;
}

int32_t JsiDeclarativeEngine::LoadNavDestinationSource(const std::string& bundleName,
    const std::string& moduleName, const std::string& pageSourceFile, bool isSingleton)
{
    auto runtime = engineInstance_->GetJsRuntime();
    CHECK_NULL_RETURN(runtime, false);
    auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    return arkRuntime->LoadDestinationFile(bundleName, moduleName, pageSourceFile, isSingleton);
}

void JsiDeclarativeEngine::AddToNamedRouterMap(const EcmaVM* vm, panda::Global<panda::FunctionRef> pageGenerator,
    const std::string& namedRoute, panda::Local<panda::ObjectRef> params)
{
    std::string bundleName;
    std::string moduleName;
    std::string pagePath;
    std::string pageFullPath;
    std::string ohmUrl;
    if (!ParseNamedRouterParams(vm, params, bundleName, moduleName, pagePath, pageFullPath, ohmUrl)) {
        return;
    }

    TAG_LOGI(AceLogTag::ACE_ROUTER,
        "add named router record, name: %{public}s, bundleName: %{public}s, moduleName: %{public}s, "
        "pagePath: %{public}s, pageFullPath: %{public}s, ohmUrl: %{public}s",
        namedRoute.c_str(), bundleName.c_str(), moduleName.c_str(), pagePath.c_str(), pageFullPath.c_str(),
        ohmUrl.c_str());
    NamedRouterProperty namedRouterProperty({ pageGenerator, bundleName, moduleName, pagePath, ohmUrl });
    auto ret = namedRouterRegisterMap_.insert(std::make_pair(namedRoute, namedRouterProperty));
    if (!ret.second) {
        ret.first->second.pageGenerator.FreeGlobalHandleAddr();
        namedRouterRegisterMap_[namedRoute] = namedRouterProperty;
    }
    auto pagePathKey = moduleName + pagePath;
    auto pageRet = routerPathInfoMap_.insert(std::make_pair(pagePathKey, pageFullPath));
    if (!pageRet.second) {
        routerPathInfoMap_[pagePathKey] = pageFullPath;
    }
    if (!namedRoute.empty()) {
        auto ret = routerPathInfoMap_.insert(std::make_pair(namedRoute, pageFullPath));
        if (!ret.second) {
            routerPathInfoMap_[namedRoute] = pageFullPath;
        }
    }
}

std::string JsiDeclarativeEngine::SearchRouterRegisterMap(const std::string& pageName)
{
    auto it = namedRouterRegisterMap_.find(pageName);
    if (it != namedRouterRegisterMap_.end()) {
        return it->second.moduleName;
    }
    return "";
}

bool JsiDeclarativeEngine::LoadNamedRouterSource(const std::string& namedRoute, bool isTriggeredByJs)
{
    CHECK_NULL_RETURN(!namedRouterRegisterMap_.empty(), false);
    auto iter = namedRouterRegisterMap_.find(namedRoute);
    if (isTriggeredByJs && iter == namedRouterRegisterMap_.end()) {
        LOGW("named route %{public}s not found!", namedRoute.c_str());
        return false;
    }
    // if this triggering is not from js named router api,
    // 'namedRoute' will be used as url to find the page in 'main_pages.json'
    if (!isTriggeredByJs) {
        std::string bundleName;
        std::string moduleName;
        std::string url = namedRoute;
#if !defined(PREVIEW)
        if (namedRoute.substr(0, strlen(BUNDLE_TAG)) == BUNDLE_TAG) {
            size_t bundleEndPos = namedRoute.find('/');
            bundleName = namedRoute.substr(strlen(BUNDLE_TAG), bundleEndPos - strlen(BUNDLE_TAG));
            size_t moduleStartPos = bundleEndPos + 1;
            size_t moduleEndPos = namedRoute.find('/', moduleStartPos);
            moduleName = namedRoute.substr(moduleStartPos, moduleEndPos - moduleStartPos);
            url = namedRoute.substr(moduleEndPos + strlen("/ets/"));
        } else {
            bundleName = AceApplicationInfo::GetInstance().GetPackageName();
            auto container = Container::Current();
            CHECK_NULL_RETURN(container, false);
            moduleName = container->GetModuleName();
        }
#else
        bundleName = bundleName_;
        moduleName = moduleName_;
#endif
        // when need to locate page in main_pages.json, url shouldn't be empty
        if (url == "") {
            LOGW("page not found! bundleName: %{public}s, moduleName: %{public}s, url: %{public}s",
                bundleName.c_str(), moduleName.c_str(), url.c_str());
            return false;
        }
        iter = std::find_if(namedRouterRegisterMap_.begin(), namedRouterRegisterMap_.end(),
            [&bundleName, &moduleName, &url](const auto& item) {
                return item.second.bundleName == bundleName && item.second.moduleName == moduleName &&
                       item.second.pagePath == url;
            });
        if (iter == namedRouterRegisterMap_.end()) {
            LOGW("page not found! bundleName: %{public}s, moduleName: %{public}s, url: %{public}s",
                bundleName.c_str(), moduleName.c_str(), url.c_str());
            return false;
        }
    }

    /**
     * The pageGenerator may be filled in two situations: one is when the developer explicitly imports it(
     * dynamic import in ets, eg: import("hsp"); ), and the other is when the PageRouterManager preload namedRoute
     * in Backup&Restore scenario.
     */
    if (iter->second.pageGenerator.IsEmpty()) {
        LOGE("Named router %{public}s has no PageGenerator", iter->first.c_str());
        return false;
    }

    CHECK_NULL_RETURN(engineInstance_, false);
    auto runtime = engineInstance_->GetJsRuntime();
    auto vm = const_cast<EcmaVM*>(std::static_pointer_cast<ArkJSRuntime>(runtime)->GetEcmaVm());
    std::vector<Local<JSValueRef>> argv;
    LocalScope scope(vm);
    JSViewStackProcessor::JsStartGetAccessRecordingFor(JSViewStackProcessor::JsAllocateNewElmetIdForNextComponent());
    auto ret = iter->second.pageGenerator->Call(vm, JSNApi::GetGlobalObject(vm), argv.data(), 0);
    if (!ret->IsObject(vm)) {
        return false;
    }
#if defined(PREVIEW)
    panda::Global<panda::ObjectRef> rootView(vm, ret->ToObject(vm));
    shared_ptr<ArkJSRuntime> arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    arkRuntime->AddRootView(rootView);
#endif
    Framework::UpdateRootComponent(vm, ret->ToObject(vm));
    JSViewStackProcessor::JsStopGetAccessRecording();
    return true;
}

std::unique_ptr<JsonValue> JsiDeclarativeEngine::GetFullPathInfo()
{
    auto jsonFullPathInfo = JsonUtil::CreateArray(true);
    auto recordIter = routerPathInfoMap_.begin();
    while (recordIter != routerPathInfoMap_.end()) {
        auto jsonItem = JsonUtil::Create(true);
        jsonItem->Put("url", recordIter->first.c_str());
        jsonItem->Put("fullPathInfo", recordIter->second.c_str());
        jsonFullPathInfo->Put(jsonItem);
        ++recordIter;
    }
    return jsonFullPathInfo;
}

void JsiDeclarativeEngine::RestoreFullPathInfo(std::unique_ptr<JsonValue> fullPathInfo)
{
    std::unordered_map<std::string, std::string> routerPathInfoMap;
    if (!fullPathInfo || !fullPathInfo->IsValid() || !fullPathInfo->IsArray()) {
        LOGW("Invalid fullPathInfo");
        return;
    }

    NamedRouterProperty property;
    int32_t size = fullPathInfo->GetArraySize();
    for (int32_t i = 0; i < size; ++i) {
        auto item = fullPathInfo->GetArrayItem(i);
        if (!item) {
            LOGW("failed to get fullPathInfo item");
            continue;
        }
        auto urlJsonValue = item->GetValue("url");
        auto fullPathInfoJsonValue = item->GetValue("fullPathInfo");
        if (!urlJsonValue || !urlJsonValue->IsString() ||
            !fullPathInfoJsonValue || !fullPathInfoJsonValue->IsString()) {
            LOGW("Invalid fullPathInfo item");
            continue;
        }

        std::string url = urlJsonValue->GetString();
        std::string pathInfo = fullPathInfoJsonValue->GetString();
        routerPathInfoMap.emplace(url, pathInfo);
    }

    std::swap(routerPathInfoMap_, routerPathInfoMap);
}

std::unique_ptr<JsonValue> JsiDeclarativeEngine::GetNamedRouterInfo()
{
    auto jsonNamedRouterInfo = JsonUtil::CreateArray(true);
    auto recordIter = namedRouterRegisterMap_.begin();
    while (recordIter != namedRouterRegisterMap_.end()) {
        auto jsonItem = JsonUtil::Create(true);
        jsonItem->Put("name", recordIter->first.c_str());
        const auto& property = recordIter->second;
        jsonItem->Put("bundleName", property.bundleName.c_str());
        jsonItem->Put("moduleName", property.moduleName.c_str());
        jsonItem->Put("pagePath", property.pagePath.c_str());
        jsonItem->Put("ohmUrl", property.ohmUrl.c_str());
        jsonNamedRouterInfo->Put(jsonItem);
        ++recordIter;
    }
    return jsonNamedRouterInfo;
}

void JsiDeclarativeEngine::RestoreNamedRouterInfo(std::unique_ptr<JsonValue> namedRouterInfo)
{
    std::unordered_map<std::string, NamedRouterProperty> namedRouterMap;
    if (!namedRouterInfo || !namedRouterInfo->IsValid() || !namedRouterInfo->IsArray()) {
        LOGW("Invalid namedRouterInfo");
        return;
    }

    NamedRouterProperty property;
    int32_t size = namedRouterInfo->GetArraySize();
    for (int32_t i = 0; i < size; ++i) {
        auto item = namedRouterInfo->GetArrayItem(i);
        if (!item) {
            LOGW("failed to get namedRouterInfo item");
            continue;
        }
        auto nameJsonValue = item->GetValue("name");
        auto bundleNameJsonValue = item->GetValue("bundleName");
        auto moduleNameJsonValue = item->GetValue("moduleName");
        auto pagePathJsonValue = item->GetValue("pagePath");
        auto ohmUrlJsonValue = item->GetValue("ohmUrl");
        if (!nameJsonValue || !nameJsonValue->IsString() ||
            !bundleNameJsonValue || !bundleNameJsonValue->IsString() ||
            !moduleNameJsonValue || !moduleNameJsonValue->IsString() ||
            !pagePathJsonValue || !pagePathJsonValue->IsString() ||
            !ohmUrlJsonValue || !ohmUrlJsonValue->IsString()) {
            LOGW("Invalid NamedRouterInfo item");
            continue;
        }

        std::string name = nameJsonValue->GetString();
        property.bundleName = bundleNameJsonValue->GetString();
        property.moduleName = moduleNameJsonValue->GetString();
        property.pagePath = pagePathJsonValue->GetString();
        property.ohmUrl = ohmUrlJsonValue->GetString();
        namedRouterMap.emplace(name, property);
    }

    std::swap(namedRouterRegisterMap_, namedRouterMap);
}

bool JsiDeclarativeEngine::IsNamedRouterNeedPreload(const std::string& name)
{
    auto it = namedRouterRegisterMap_.find(name);
    if (it == namedRouterRegisterMap_.end()) {
        return false;
    }
    return it->second.pageGenerator.IsEmpty();
}

void JsiDeclarativeEngine::PreloadNamedRouter(const std::string& name, std::function<void(bool)>&& loadFinishCallback)
{
    if (!pageUrlCheckFunc_) {
        LOGW("JSEngine didn't set PageUrlCheckFunc");
        if (loadFinishCallback) {
            loadFinishCallback(false);
        }
        return;
    }
    auto it = namedRouterRegisterMap_.find(name);
    if (it == namedRouterRegisterMap_.end() || !it->second.pageGenerator.IsEmpty()) {
        if (loadFinishCallback) {
            loadFinishCallback(true);
        }
        return;
    }
    const auto& bundleName = it->second.bundleName;
    const auto& moduleName = it->second.moduleName;
    const auto& pagePath = it->second.pagePath;
    std::string ohmUrl = it->second.ohmUrl + ".js";
    TAG_LOGI(AceLogTag::ACE_ROUTER, "preload named rotuer, bundleName:"
        "%{public}s, moduleName: %{public}s, pagePath: %{public}s, ohmUrl: %{public}s",
        bundleName.c_str(), moduleName.c_str(), pagePath.c_str(), ohmUrl.c_str());

    auto callback = [weak = AceType::WeakClaim(this), ohmUrl, finishCallback = loadFinishCallback]() {
        auto jsEngine = weak.Upgrade();
        CHECK_NULL_VOID(jsEngine);
        bool loadSuccess = true;
        jsEngine->LoadPageSource(ohmUrl, [ohmUrl, &loadSuccess](const std::string& errorMsg, int32_t errorCode) {
            TAG_LOGW(AceLogTag::ACE_ROUTER,
                "Failed to load page source: %{public}s, errorCode: %{public}d, errorMsg: %{public}s", ohmUrl.c_str(),
                errorCode, errorMsg.c_str());
            loadSuccess = false;
        });
        if (finishCallback) {
            finishCallback(loadSuccess);
        }
    };
    auto silentInstallErrorCallBack = [finishCallback = loadFinishCallback](
                                          int32_t errorCode, const std::string& errorMsg) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "Failed to preload named router, error = %{public}d, errorMsg = %{public}s",
            errorCode, errorMsg.c_str());
        if (finishCallback) {
            finishCallback(false);
        }
    };
    pageUrlCheckFunc_(ohmUrl, callback, silentInstallErrorCallBack);
}

bool JsiDeclarativeEngine::LoadCard(const std::string& url, int64_t cardId, const std::string& entryPoint)
{
    ACE_SCOPED_TRACE("JsiDeclarativeEngine::LoadCard");
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    return container->IsDynamicRender() ? ExecuteDynamicAbc(url, entryPoint) : ExecuteCardAbc(url, cardId);
}

#if defined(PREVIEW)
void JsiDeclarativeEngine::ReplaceJSContent(const std::string& url, const std::string componentName)
{
    ACE_DCHECK(engineInstance_);
    if (engineInstance_ == nullptr) {
        return;
    }
    auto runtime = engineInstance_->GetJsRuntime();
    std::static_pointer_cast<ArkJSRuntime>(runtime)->SetPreviewFlag(true);
    std::static_pointer_cast<ArkJSRuntime>(runtime)->SetRequiredComponent(componentName);
    engineInstance_->GetDelegate()->Replace(url, "");
}

RefPtr<Component> JsiDeclarativeEngine::GetNewComponentWithJsCode(const std::string& jsCode, const std::string& viewID)
{
    std::string dest;
    if (!Base64Util::Decode(jsCode, dest)) {
        return nullptr;
    }

    ViewStackProcessor::GetInstance()->ClearStack();
    ViewStackProcessor::GetInstance()->PushKey(viewID);
    bool result = engineInstance_->InitAceModule((uint8_t*)dest.data(), dest.size());
    ViewStackProcessor::GetInstance()->PopKey();
    if (!result) {
        return nullptr;
    }
    auto component = ViewStackProcessor::GetInstance()->GetNewComponent();
    return component;
}

bool JsiDeclarativeEngine::ExecuteJsForFastPreview(const std::string& jsCode, const std::string& viewID)
{
    std::string dest;
    if (!Base64Util::Decode(jsCode, dest)) {
        return false;
    }
    NG::ViewStackProcessor::GetInstance()->ClearStack();
    NG::ViewStackProcessor::GetInstance()->PushKey(viewID);
    bool result = engineInstance_->InitAceModule((uint8_t*)dest.data(), dest.size());
    NG::ViewStackProcessor::GetInstance()->PopKey();
    return result;
}

void JsiDeclarativeEngine::SetHspBufferTrackerCallback(
    std::function<bool(const std::string&, uint8_t**, size_t*, std::string&)>&& callback)
{
    CHECK_NULL_VOID(engineInstance_);
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(engineInstance_->GetJsRuntime());
    CHECK_NULL_VOID(runtime);
    auto vm = const_cast<EcmaVM*>(runtime->GetEcmaVm());
    panda::JSNApi::SetHostResolveBufferTracker(vm, std::move(callback));
}

void JsiDeclarativeEngine::SetMockModuleList(const std::map<std::string, std::string>& mockJsonInfo)
{
    CHECK_NULL_VOID(engineInstance_);
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(engineInstance_->GetJsRuntime());
    CHECK_NULL_VOID(runtime);
    auto vm = const_cast<EcmaVM*>(runtime->GetEcmaVm());
    panda::JSNApi::SetMockModuleList(vm, mockJsonInfo);
}

bool JsiDeclarativeEngine::IsComponentPreview()
{
    auto runtime = engineInstance_->GetJsRuntime();
    CHECK_NULL_RETURN(runtime, false);
    shared_ptr<ArkJSRuntime> arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    CHECK_NULL_RETURN(arkRuntime, false);
    return arkRuntime->GetPreviewFlag();
}
#endif

void JsiDeclarativeEngine::UpdateRunningPage(const RefPtr<JsAcePage>& page)
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetRunningPage(page);
}

void JsiDeclarativeEngine::UpdateStagingPage(const RefPtr<JsAcePage>& page)
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetStagingPage(page);
}

void JsiDeclarativeEngine::ResetStagingPage()
{
    ACE_DCHECK(engineInstance_);
    auto runningPage = engineInstance_->GetRunningPage();
    engineInstance_->ResetStagingPage(runningPage);
}

void JsiDeclarativeEngine::SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher)
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetJsMessageDispatcher(dispatcher);
}

void JsiDeclarativeEngine::FireAsyncEvent(const std::string& eventId, const std::string& param)
{
    std::string callBuf = std::string("[{\"args\": [\"")
                              .append(eventId)
                              .append("\",")
                              .append(param)
                              .append("], \"method\":\"fireEvent\"}]");

    ACE_DCHECK(engineInstance_);
    engineInstance_->FireJsEvent(callBuf.c_str());
}

void JsiDeclarativeEngine::FireSyncEvent(const std::string& eventId, const std::string& param)
{
    std::string callBuf = std::string("[{\"args\": [\"")
                              .append(eventId)
                              .append("\",")
                              .append(param)
                              .append("], \"method\":\"fireEventSync\"}]");

    ACE_DCHECK(engineInstance_);
    engineInstance_->FireJsEvent(callBuf.c_str());
}

void JsiDeclarativeEngine::InitXComponent(const std::string& componentId)
{
    ACE_DCHECK(engineInstance_);
    std::tie(nativeXComponentImpl_, nativeXComponent_) =
        XComponentClient::GetInstance().GetNativeXComponentFromXcomponentsMap(componentId);
}

void JsiDeclarativeEngine::FireExternalEvent(
    const std::string& componentId, const uint32_t nodeId, const bool isDestroy)
{
    CHECK_RUN_ON(JS);

    if (Container::IsCurrentUseNewPipeline()) {
        ACE_DCHECK(engineInstance_);
        auto xcFrameNode = NG::FrameNode::GetFrameNode(V2::XCOMPONENT_ETS_TAG, static_cast<int32_t>(nodeId));
        if (!xcFrameNode) {
            return;
        }
        auto xcPattern = DynamicCast<NG::XComponentPattern>(xcFrameNode->GetPattern());
        CHECK_NULL_VOID(xcPattern);
        CHECK_EQUAL_VOID(xcPattern->GetLibraryName().has_value(), false);
        std::weak_ptr<OH_NativeXComponent> weakNativeXComponent;
        RefPtr<OHOS::Ace::NativeXComponentImpl> nativeXComponentImpl = nullptr;
        std::tie(nativeXComponentImpl, weakNativeXComponent) = xcPattern->GetNativeXComponent();
        auto nativeXComponent = weakNativeXComponent.lock();
        CHECK_NULL_VOID(nativeXComponent);
        CHECK_NULL_VOID(nativeXComponentImpl);

        nativeXComponentImpl->SetXComponentId(componentId);
#ifdef XCOMPONENT_SUPPORTED
        xcPattern->SetExpectedRateRangeInit();
        xcPattern->OnFrameEventInit();
        xcPattern->UnregisterOnFrameEventInit();
#endif
        auto* arkNativeEngine = static_cast<ArkNativeEngine*>(nativeEngine_);
        if (arkNativeEngine == nullptr) {
            return;
        }

        napi_handle_scope handleScope;
        napi_status status = napi_open_handle_scope(reinterpret_cast<napi_env>(nativeEngine_), &handleScope);
        if (status != napi_ok) {
            return;
        }

        std::string arguments;
        auto soPath = xcPattern->GetSoPath().value_or("");
        auto runtime = engineInstance_->GetJsRuntime();
        shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
        LocalScope scope(pandaRuntime->GetEcmaVm());
        auto objXComp = arkNativeEngine->LoadModuleByName(xcPattern->GetLibraryName().value(), true, arguments,
            OH_NATIVE_XCOMPONENT_OBJ, reinterpret_cast<void*>(nativeXComponent.get()), soPath);
        if (objXComp.IsEmpty() || pandaRuntime->HasPendingException()) {
            napi_close_handle_scope(reinterpret_cast<napi_env>(nativeEngine_), handleScope);
            return;
        }
        auto objContext = JsiObject(objXComp);
        JSRef<JSObject> obj = JSRef<JSObject>::Make(objContext);
        OHOS::Ace::Framework::XComponentClient::GetInstance().AddJsValToJsValMap(componentId, obj);
        napi_close_handle_scope(reinterpret_cast<napi_env>(nativeEngine_), handleScope);

        auto type = xcPattern->GetType();
        if (type == XComponentType::SURFACE || type == XComponentType::TEXTURE) {
            auto task = [weak = WeakClaim(this), weakPattern = AceType::WeakClaim(AceType::RawPtr(xcPattern))]() {
                auto pattern = weakPattern.Upgrade();
                if (!pattern) {
                    return;
                }
                auto bridge = weak.Upgrade();
                if (bridge) {
#ifdef XCOMPONENT_SUPPORTED
                    pattern->NativeXComponentInit();
#endif
                }
            };

            auto delegate = engineInstance_->GetDelegate();
            if (!delegate) {
                return;
            }
            delegate->PostSyncTaskToPage(task, "ArkUINativeXComponentInit");
        }
        return;
    }
#ifndef NG_BUILD
    if (isDestroy) {
        XComponentComponentClient::GetInstance().DeleteFromXcomponentsMapById(componentId);
        XComponentClient::GetInstance().DeleteControllerFromJSXComponentControllersMap(componentId);
        XComponentClient::GetInstance().DeleteFromNativeXcomponentsMapById(componentId);
        XComponentClient::GetInstance().DeleteFromJsValMapById(componentId);
        return;
    }
    InitXComponent(componentId);
    RefPtr<XComponentComponent> xcomponent =
        XComponentComponentClient::GetInstance().GetXComponentFromXcomponentsMap(componentId);
    if (!xcomponent) {
        return;
    }

    void* nativeWindow = nullptr;
#ifdef OHOS_STANDARD_SYSTEM
    nativeWindow = const_cast<void*>(xcomponent->GetNativeWindow());
#else
    auto container = Container::Current();
    if (!container) {
        return;
    }
    auto nativeView = container->GetAceView();
    if (!nativeView) {
        return;
    }
    auto textureId = static_cast<int64_t>(xcomponent->GetTextureId());
    nativeWindow = const_cast<void*>(nativeView->GetNativeWindowById(textureId));
#endif

    if (!nativeWindow) {
        return;
    }
    nativeXComponentImpl_->SetSurface(nativeWindow);
    nativeXComponentImpl_->SetXComponentId(xcomponent->GetId());

    auto arkNativeEngine = static_cast<ArkNativeEngine*>(nativeEngine_);
    if (arkNativeEngine == nullptr) {
        return;
    }

    napi_handle_scope handleScope;
    napi_status status = napi_open_handle_scope(reinterpret_cast<napi_env>(nativeEngine_), &handleScope);
    if (status != napi_ok) {
        return;
    }
    std::string arguments;
    auto soPath = xcomponent->GetSoPath().value_or("");
    auto runtime = engineInstance_->GetJsRuntime();
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    LocalScope scope(pandaRuntime->GetEcmaVm());
    auto objXComp = arkNativeEngine->LoadModuleByName(xcomponent->GetLibraryName(), true, arguments,
        OH_NATIVE_XCOMPONENT_OBJ, reinterpret_cast<void*>(nativeXComponent_), soPath);
    if (objXComp.IsEmpty() || pandaRuntime->HasPendingException()) {
        napi_close_handle_scope(reinterpret_cast<napi_env>(nativeEngine_), handleScope);
        return;
    }

    auto objContext = JsiObject(objXComp);
    JSRef<JSObject> obj = JSRef<JSObject>::Make(objContext);
    XComponentClient::GetInstance().AddJsValToJsValMap(componentId, obj);
    napi_close_handle_scope(reinterpret_cast<napi_env>(nativeEngine_), handleScope);

    auto task = [weak = WeakClaim(this), xcomponent]() {
        auto pool = xcomponent->GetTaskPool();
        if (!pool) {
            return;
        }
        auto bridge = weak.Upgrade();
        if (bridge) {
#ifdef XCOMPONENT_SUPPORTED
            pool->NativeXComponentInit(
                bridge->nativeXComponent_, AceType::WeakClaim(AceType::RawPtr(bridge->nativeXComponentImpl_)));
#endif
        }
    };

    auto delegate = engineInstance_->GetDelegate();
    if (!delegate) {
        return;
    }
    delegate->PostSyncTaskToPage(task, "ArkUINativeXComponentInit");
#endif
}

void JsiDeclarativeEngine::TimerCallback(const std::string& callbackId, const std::string& delay, bool isInterval)
{
    TimerCallJs(callbackId);
    auto runtime = JsiDeclarativeEngineInstance::GetCurrentRuntime();
    if (!runtime) {
        return;
    }
    auto instance = static_cast<JsiDeclarativeEngineInstance*>(runtime->GetEmbedderData());
    if (instance == nullptr) {
        return;
    }
    auto delegate = instance->GetDelegate();
    if (!delegate) {
        return;
    }

    if (isInterval) {
        delegate->WaitTimer(callbackId, delay, isInterval, false);
    } else {
        JsiTimerModule::GetInstance()->RemoveCallBack(StringUtils::StringToInt(callbackId));
        delegate->ClearTimer(callbackId);
    }
}

void JsiDeclarativeEngine::TimerCallJs(const std::string& callbackId) const
{
    shared_ptr<JsValue> func;
    std::vector<shared_ptr<JsValue>> params;
    if (!JsiTimerModule::GetInstance()->GetCallBack(StringUtils::StringToInt(callbackId), func, params)) {
        return;
    }
    auto runtime = JsiDeclarativeEngineInstance::GetCurrentRuntime();
    if (func) {
        func->Call(runtime, runtime->GetGlobal(), params, params.size());
    }
}

void JsiDeclarativeEngine::DestroyPageInstance(int32_t pageId)
{
    ACE_DCHECK(engineInstance_);

    engineInstance_->DestroyRootViewHandle(pageId);
}

void JsiDeclarativeEngine::DestroyApplication(const std::string& packageName)
{
    if (engineInstance_) {
        shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
        CallAppFunc("onDestroy");
    }
}

void JsiDeclarativeEngine::UpdateApplicationState(const std::string& packageName, Frontend::State state)
{
    LOGI("Update application state %{public}s, state: %{public}s", packageName.c_str(),
        Frontend::stateToString(state).c_str());
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        return;
    }
    switch (state) {
        case Frontend::State::ON_SHOW:
            if (isFirstCallShow_) {
                isFirstCallShow_ = false;
                break;
            }
            CallAppFunc("onShow");
            break;
        case Frontend::State::ON_HIDE:
            CallAppFunc("onHide");
            break;
        case Frontend::State::ON_ACTIVE:
            CallAppFunc("onActive");
            break;
        case Frontend::State::ON_INACTIVE:
            CallAppFunc("onInactive");
            break;
        case Frontend::State::ON_DESTROY:
            CallAppFunc("onDestroy");
            break;
        default:
            return;
    }
}

void JsiDeclarativeEngine::OnWindowDisplayModeChanged(bool isShownInMultiWindow, const std::string& data)
{
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
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    ACE_DCHECK(runtime);
    shared_ptr<JsValue> global = runtime->GetGlobal();
    shared_ptr<JsValue> exportsObject = global->GetProperty(runtime, "exports");
    if (!exportsObject->IsObject(runtime)) {
        return false;
    }
    shared_ptr<JsValue> defaultObject = exportsObject->GetProperty(runtime, "default");
    if (!defaultObject->IsObject(runtime)) {
        return false;
    }
    shared_ptr<JsValue> func = defaultObject->GetProperty(runtime, appFuncName);
    if (!func || !func->IsFunction(runtime)) {
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

void JsiDeclarativeEngine::RunFullGarbageCollection()
{
    if (engineInstance_ && engineInstance_->GetJsRuntime()) {
        engineInstance_->GetJsRuntime()->RunFullGC();
    }
}

void JsiDeclarativeEngine::DumpHeapSnapshot(bool isPrivate)
{
    if (engineInstance_ && engineInstance_->GetJsRuntime()) {
        engineInstance_->GetJsRuntime()->DumpHeapSnapshot(isPrivate);
    }
}

void JsiDeclarativeEngine::NotifyUIIdle()
{
    if (engineInstance_ && engineInstance_->GetJsRuntime()) {
        engineInstance_->GetJsRuntime()->NotifyUIIdle();
    }
}

std::string JsiDeclarativeEngine::GetStacktraceMessage()
{
    auto arkNativeEngine = static_cast<ArkNativeEngine*>(nativeEngine_);
    if (!arkNativeEngine) {
        return "";
    }
    std::string stack;
    arkNativeEngine->SuspendVM();
    bool getStackSuccess = arkNativeEngine->BuildJsStackTrace(stack);
    arkNativeEngine->ResumeVM();
    if (!getStackSuccess) {
        return "JS stacktrace is empty";
    }

    auto runningPage = engineInstance_ ? engineInstance_->GetRunningPage() : nullptr;
    return JsiBaseUtils::TransSourceStack(runningPage, stack);
}

void JsiDeclarativeEngine::GetStackTrace(std::string& trace)
{
    auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (!arkRuntime) {
        return;
    }
    auto vm = arkRuntime->GetEcmaVm();
    if (!vm) {
        return;
    }
    panda::DFXJSNApi::BuildJsStackTrace(vm, trace);
}

std::string JsiDeclarativeEngine::GetPagePath(const std::string& url)
{
    auto iter = namedRouterRegisterMap_.find(url);
    if (iter != namedRouterRegisterMap_.end()) {
        return iter->second.pagePath;
    }
    return "";
}

void JsiDeclarativeEngine::ResetNamedRouterRegisterMap()
{
    namedRouterRegisterMap_.clear();
}

std::string JsiDeclarativeEngine::GetFullPathInfo(const std::string& url)
{
    auto iter = routerPathInfoMap_.find(url);
    if (iter != routerPathInfoMap_.end()) {
        return iter->second;
    }
    return "";
}

std::optional<std::string> JsiDeclarativeEngine::GetRouteNameByUrl(
    const std::string& url, const std::string& bundleName, const std::string& moduleName)
{
    auto iter = std::find_if(namedRouterRegisterMap_.begin(), namedRouterRegisterMap_.end(),
        [&bundleName, &moduleName, &url](const auto& item) {
            return item.second.bundleName == bundleName && item.second.moduleName == moduleName &&
                    item.second.pagePath == url;
        });
    if (iter != namedRouterRegisterMap_.end()) {
        return iter->first;
    }
    return std::nullopt;
}

void JsiDeclarativeEngine::SetLocalStorage(int32_t instanceId, NativeReference* nativeValue)
{
#ifdef USE_ARK_ENGINE
    auto jsValue = JsConverter::ConvertNapiValueToJsVal(nativeValue->GetNapiValue());
    if (jsValue->IsObject()) {
        auto storage = JSRef<JSObject>::Cast(jsValue);
        JSLocalStorage::AddStorage(instanceId, storage);
    }
    delete nativeValue;
    nativeValue = nullptr;
#endif
}

std::shared_ptr<Framework::JsValue> JsiDeclarativeEngine::GetJsContext()
{
    auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(
        JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (!arkRuntime || !arkRuntime->GetEcmaVm()) {
        LOGW("arkRuntime or vm is null.");
        return nullptr;
    }

    return JsiContextModule::GetContext(arkRuntime, nullptr, {}, 0);
}

void JsiDeclarativeEngine::SetJsContext(const std::shared_ptr<Framework::JsValue>& jsContext)
{
    JsiContextModule::AddContext(instanceId_, jsContext);
}

void JsiDeclarativeEngine::SetContext(int32_t instanceId, NativeReference* nativeValue)
{
#ifdef USE_ARK_ENGINE
    napi_handle_scope scope;
    napi_status status = napi_open_handle_scope(reinterpret_cast<napi_env>(GetNativeEngine()), &scope);
    if (status != napi_ok) {
        return;
    }
    auto arkRuntime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (!arkRuntime || !arkRuntime->GetEcmaVm()) {
        napi_close_handle_scope(reinterpret_cast<napi_env>(GetNativeEngine()), scope);
        return;
    }
    JAVASCRIPT_EXECUTION_SCOPE_STATIC;
    auto localRef = NapiValueToLocalValue(nativeValue->GetNapiValue());
    std::shared_ptr<JsValue> jsValue = std::make_shared<ArkJSValue>(arkRuntime, localRef);
    if (jsValue->IsObject(arkRuntime)) {
        JsiContextModule::AddContext(instanceId_, jsValue);
    }
    napi_close_handle_scope(reinterpret_cast<napi_env>(GetNativeEngine()), scope);
#endif
}

RefPtr<GroupJsBridge> JsiDeclarativeEngine::GetGroupJsBridge()
{
    return AceType::MakeRefPtr<JsiDeclarativeGroupJsBridge>();
}

void JsiDeclarativeEngine::OnActive()
{
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        return;
    }
    CallAppFunc("onActive");
}

void JsiDeclarativeEngine::OnInactive()
{
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        return;
    }
    CallAppFunc("onInactive");
}

void JsiDeclarativeEngine::OnNewWant(const std::string& data)
{
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        return;
    }

    shared_ptr<JsValue> object = runtime->ParseJson(data);
    std::vector<shared_ptr<JsValue>> argv = { object };
    CallAppFunc("onNewWant", argv);
}

bool JsiDeclarativeEngine::OnStartContinuation()
{
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        return false;
    }

    return CallAppFunc("onStartContinuation");
}

void JsiDeclarativeEngine::OnCompleteContinuation(int32_t code)
{
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        return;
    }

    std::vector<shared_ptr<JsValue>> argv = { runtime->NewNumber(code) };
    CallAppFunc("onCompleteContinuation", argv);
}

void JsiDeclarativeEngine::OnRemoteTerminated()
{
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        return;
    }

    CallAppFunc("onRemoteTerminated");
}

void JsiDeclarativeEngine::OnSaveData(std::string& data)
{
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        return;
    }

    shared_ptr<JsValue> object = runtime->NewObject();
    std::vector<shared_ptr<JsValue>> argv = { object };
    if (CallAppFunc("onSaveData", argv)) {
        data = object->GetJsonString(runtime);
    }
}

void JsiDeclarativeEngine::SetErrorEventHandler(
    std::function<void(const std::string&, const std::string&)>&& errorCallback)
{
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        return;
    }

    runtime->SetErrorEventHandler(std::move(errorCallback));
}

bool JsiDeclarativeEngine::OnRestoreData(const std::string& data)
{
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    if (!runtime) {
        return false;
    }
    shared_ptr<JsValue> result;
    shared_ptr<JsValue> jsonObj = runtime->ParseJson(data);
    if (jsonObj->IsUndefined(runtime) || jsonObj->IsException(runtime)) {
        return false;
    }
    std::vector<shared_ptr<JsValue>> argv = { jsonObj };
    return CallAppFunc("onRestoreData", argv);
}

void JsiDeclarativeEngine::AddToNavigationBuilderMap(std::string name,
    panda::Global<panda::ObjectRef> builderFunc)
{
    auto ret = builderMap_.insert(std::pair<std::string, panda::Global<panda::ObjectRef>>(name, builderFunc));
    if (!ret.second) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "insert builder failed, update builder: %{public}s", name.c_str());
        builderMap_[name] = builderFunc;
    }
}

panda::Global<panda::ObjectRef> JsiDeclarativeEngine::GetNavigationBuilder(std::string name)
{
    auto targetBuilder = builderMap_.find(name);
    if (targetBuilder == builderMap_.end()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "get navDestination builder failed: %{public}s", name.c_str());
        return panda::Global<panda::ObjectRef>();
    }
    return targetBuilder->second;
}

void JsiDeclarativeEngine::JsStateProfilerResgiter()
{
#if defined(PREVIEW)
    return;
#else
    CHECK_NULL_VOID(runtime_);
    auto engine = reinterpret_cast<NativeEngine*>(runtime_);
    CHECK_NULL_VOID(engine);
    auto vm = engine->GetEcmaVm();
    CHECK_NULL_VOID(vm);
    auto globalObj = JSNApi::GetGlobalObject(vm);
    const auto globalObject = JSRef<JSObject>::Make(globalObj);

    const JSRef<JSVal> setProfilerStatus = globalObject->GetProperty("setProfilerStatus");
    if (!setProfilerStatus->IsFunction()) {
        return;
    }

    const auto globalFunc = JSRef<JSFunc>::Cast(setProfilerStatus);
    std::function<void(bool)> callback = [globalFunc, globalObject, instanceId = instanceId_](
                                             bool enableStateProfiler) {
        ContainerScope scope(instanceId);

        const std::function<void()> task = [globalFunc, globalObject, enableStateProfiler]() {
            auto isInStateProfiler = JSRef<JSVal>::Make(ToJSValue(enableStateProfiler));
            globalFunc->Call(globalObject, 1, &isInStateProfiler);
        };

        auto executor = Container::CurrentTaskExecutor();
        CHECK_NULL_VOID(executor);
        executor->PostSyncTask(task, TaskExecutor::TaskType::UI, "setProfilerStatus");
    };

    LayoutInspector::SetJsStateProfilerStatusCallback(std::move(callback));
#endif
}

void JsiDeclarativeEngine::JsSetAceDebugMode()
{
#if defined(PREVIEW)
    return;
#else
    if (!SystemProperties::GetDebugEnabled()) {
        return;
    }
    CHECK_NULL_VOID(runtime_);
    auto engine = reinterpret_cast<NativeEngine*>(runtime_);
    CHECK_NULL_VOID(engine);
    auto vm = engine->GetEcmaVm();
    CHECK_NULL_VOID(vm);
    auto globalObj = JSNApi::GetGlobalObject(vm);
    const auto globalObject = JSRef<JSObject>::Make(globalObj);
    const JSRef<JSVal> setAceDebugMode = globalObject->GetProperty("setAceDebugMode");
    if (!setAceDebugMode->IsFunction()) {
        return;
    }
    const auto func = JSRef<JSFunc>::Cast(setAceDebugMode);
    ContainerScope scope(instanceId_);
    func->Call(globalObject);
#endif
}

// ArkTsCard start
#ifdef FORM_SUPPORTED
void JsiDeclarativeEngineInstance::PreloadAceModuleCard(
    void* runtime, const std::unordered_set<std::string>& formModuleList)
{
    isUnique_ = true;
    if (isModulePreloaded_ && !IsPlugin() && !isUnique_) {
        return;
    }
    auto sharedRuntime = reinterpret_cast<NativeEngine*>(runtime);

    if (!sharedRuntime) {
        return;
    }
    std::shared_ptr<ArkJSRuntime> arkRuntime = std::make_shared<ArkJSRuntime>();
    localRuntime_ = arkRuntime;
    auto nativeArkEngine = static_cast<ArkNativeEngine*>(sharedRuntime);
    EcmaVM* vm = const_cast<EcmaVM*>(nativeArkEngine->GetEcmaVm());
    if (vm == nullptr) {
        return;
    }
    if (arkRuntime->InitializeFromExistVM(vm)) {
        arkRuntime->SetThreadVm(vm);
    } else {
        return;
    }
    LocalScope scope(vm);
    {
        std::unique_lock<std::shared_mutex> lock(globalRuntimeMutex_);
        globalRuntime_ = arkRuntime;
    }

    RegisterStringCacheTable(vm, MAX_STRING_CACHE_SIZE);
    // preload js views
    JsRegisterFormViews(JSNApi::GetGlobalObject(vm), formModuleList, false, runtime);
    // preload aceConsole
    shared_ptr<JsValue> global = arkRuntime->GetGlobal();
    PreloadAceConsole(arkRuntime, global);
    // preload aceTrace
    PreloadAceTrace(arkRuntime, global);
    // preload getContext
    JsiContextModule::GetInstance()->InitContextModule(arkRuntime, global);
    // preload exports
    PreloadExports(arkRuntime, global);

    // preload js enums
    bool jsEnumStyleResult = PreloadJsEnums(arkRuntime);
    if (!jsEnumStyleResult) {
        std::unique_lock<std::shared_mutex> lock(globalRuntimeMutex_);
        globalRuntime_ = nullptr;
        return;
    }

    // preload ark component
    bool arkComponentResult = PreloadArkComponent(arkRuntime);
    if (!arkComponentResult) {
        std::unique_lock<std::shared_mutex> lock(globalRuntimeMutex_);
        globalRuntime_ = nullptr;
        return;
    }

    // preload state management
    isModulePreloaded_ = PreloadStateManagement(arkRuntime);

    // preload ark styles
    bool arkThemeResult = PreloadArkTheme(arkRuntime);
    if (!arkThemeResult) {
        std::unique_lock<std::shared_mutex> lock(globalRuntimeMutex_);
        globalRuntime_ = nullptr;
        return;
    }

    {
        std::unique_lock<std::shared_mutex> lock(globalRuntimeMutex_);
        globalRuntime_ = nullptr;
    }
    cardRuntime_ = runtime;
    TAG_LOGI(AceLogTag::ACE_FORM, "Card model is preloaded successfully.");
}

void JsiDeclarativeEngineInstance::ReloadAceModuleCard(
    void* runtime, const std::unordered_set<std::string>& formModuleList)
{
    auto sharedRuntime = reinterpret_cast<NativeEngine*>(runtime);

    if (!sharedRuntime) {
        return;
    }
    auto nativeArkEngine = static_cast<ArkNativeEngine*>(sharedRuntime);
    EcmaVM* vm = const_cast<EcmaVM*>(nativeArkEngine->GetEcmaVm());
    if (vm == nullptr) {
        return;
    }
    LocalScope scope(vm);
    RegisterStringCacheTable(vm, MAX_STRING_CACHE_SIZE);
    // reload js views
    JsRegisterFormViews(JSNApi::GetGlobalObject(vm), formModuleList, true);
    JSNApi::HintGC(vm, JSNApi::MemoryReduceDegree::MIDDLE, panda::ecmascript::GCReason::TRIGGER_BY_ARKUI);
    TAG_LOGI(AceLogTag::ACE_FORM, "Card model was reloaded successfully.");
}
#endif

panda::Local<panda::StringRef> JsiDeclarativeEngineInstance::GetCachedString(const EcmaVM *vm, int32_t propertyIndex)
{
    return panda::ExternalStringCache::GetCachedString(vm, propertyIndex);
}

void JsiDeclarativeEngineInstance::SetCachedString(const EcmaVM* vm)
{
    #define REGISTER_ALL_CACHE_STRING(name, index)              \
        panda::ExternalStringCache::SetCachedString(vm, name, static_cast<int32_t>(ArkUIIndex::index));
    ARK_UI_KEY(REGISTER_ALL_CACHE_STRING)
    #undef REGISTER_ALL_CACHE_STRING
}

bool JsiDeclarativeEngineInstance::RegisterStringCacheTable(const EcmaVM* vm, int32_t size)
{
    if (vm == nullptr) {
        return false;
    }
    if (static_cast<uint32_t>(size) > MAX_STRING_CACHE_SIZE) {
        return false;
    }

    bool res = panda::ExternalStringCache::RegisterStringCacheTable(vm, size);
    if (!res) {
        return false;
    }
    SetCachedString(vm);
    return true;
}

// ArkTsCard end
} // namespace OHOS::Ace::Framework
