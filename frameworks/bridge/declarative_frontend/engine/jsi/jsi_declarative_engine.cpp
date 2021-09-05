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

#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"

#include <unistd.h>

#include "bridge/declarative_frontend/engine/jsi/panda_dummy/jsi/ark_js_runtime.h"

#include "base/i18n/localization.h"
#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_utils.h"
#include "frameworks/bridge/js_frontend/engine/common/js_api_perf.h"
#include "frameworks/bridge/js_frontend/engine/common/runtime_constants.h"

extern const char _binary_stateMgmt_abc_start[];
extern const char _binary_stateMgmt_abc_end[];
extern const char _binary_jsEnumStyle_abc_start[];
extern const char _binary_jsEnumStyle_abc_end[];

namespace OHOS::Ace::Framework {
namespace {

const std::string ARK_DEBUGGER_LIB_PATH = "/system/lib64/libark_debugger.z.so";

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
    // if (ModuleManager::GetInstance()->InitModule(newObject, moduleName, runtime)) {
        global->SetProperty(runtime, moduleName, newObject);
        return newObject;
    // }

    // return runtime->NewNull();
}

} // namespace

// -----------------------
// Start JsiDeclarativeEngineInstance
// -----------------------
std::map<std::string, std::string> JsiDeclarativeEngineInstance::mediaResourceFileMap_;

std::unique_ptr<JsonValue> JsiDeclarativeEngineInstance::currentConfigResourceData_;

thread_local shared_ptr<JsRuntime> JsiDeclarativeEngineInstance::runtime_;

JsiDeclarativeEngineInstance::~JsiDeclarativeEngineInstance()
{
    CHECK_RUN_ON(JS);
    LOG_DESTROY();

    DestroyAllRootViewHandle();

    if (runtime_) {
        runtime_->Reset();
    }
    runtime_.reset();
    JsiDeclarativeUtils::SetCurrentState(nullptr, JsErrorType::JS_CRASH, 0, "", nullptr);
}

bool JsiDeclarativeEngineInstance::InitJsEnv(bool debuggerMode)
{
    CHECK_RUN_ON(JS);
    ACE_SCOPED_TRACE("JsiDeclarativeEngineInstance::InitJsEnv");
    LOGI("JsiDeclarativeEngineInstance InitJsEnv");

    runtime_.reset(new ArkJSRuntime());
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
    if (!runtime_->Initialize(libraryPath)) {
        LOGE("Js Engine initialize runtime failed");
        return false;
    }

    InitGlobalObjectTemplate();
    InitConsoleModule();
    InitAceModule();
    InitPerfUtilModule();
    InitJsExportsUtilObject();
    InitJsNativeModuleObject();
    InitGroupJsBridge();

    runtime_->SetEmbedderData(this);
    runtime_->RegisterUncaughtExceptionHandler(JsiDeclarativeUtils::ReportJsErrorEvent);

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
    bool stateMgmtResult = runtime_->EvaluateJsCode(
        (uint8_t *)_binary_stateMgmt_abc_start, _binary_stateMgmt_abc_end - _binary_stateMgmt_abc_start);
    if (!stateMgmtResult) {
        JsiDeclarativeUtils::SetCurrentState(runtime_, JsErrorType::LOAD_JS_BUNDLE_ERROR, instanceId_);
        LOGE("EvaluateJsCode stateMgmt failed");
    }
    bool jsEnumStyleResult = runtime_->EvaluateJsCode(
        (uint8_t *)_binary_jsEnumStyle_abc_start, _binary_jsEnumStyle_abc_end - _binary_jsEnumStyle_abc_start);
    if (!jsEnumStyleResult) {
        JsiDeclarativeUtils::SetCurrentState(runtime_, JsErrorType::LOAD_JS_BUNDLE_ERROR, instanceId_);
        LOGE("EvaluateJsCode jsEnumStyle failed");
    }
}

void JsiDeclarativeEngineInstance::InitConsoleModule()
{
    ACE_SCOPED_TRACE("JsiDeclarativeEngineInstance::InitConsoleModule");
    LOGD("JsiDeclarativeEngineInstance InitConsoleModule");
    shared_ptr<JsValue> global = runtime_->GetGlobal();

    // app log method
    shared_ptr<JsValue> consoleObj = runtime_->NewObject();
    consoleObj->SetProperty(runtime_, "log", runtime_->NewFunction(AppDebugLogPrint));
    consoleObj->SetProperty(runtime_, "debug", runtime_->NewFunction(AppDebugLogPrint));
    consoleObj->SetProperty(runtime_, "info", runtime_->NewFunction(AppInfoLogPrint));
    consoleObj->SetProperty(runtime_, "warn", runtime_->NewFunction(AppWarnLogPrint));
    consoleObj->SetProperty(runtime_, "error", runtime_->NewFunction(AppErrorLogPrint));
    global->SetProperty(runtime_, "console", consoleObj);

    // js framework log method
    shared_ptr<JsValue> aceConsoleObj = runtime_->NewObject();
    aceConsoleObj->SetProperty(runtime_, "log", runtime_->NewFunction(JsDebugLogPrint));
    aceConsoleObj->SetProperty(runtime_, "debug", runtime_->NewFunction(JsDebugLogPrint));
    aceConsoleObj->SetProperty(runtime_, "info", runtime_->NewFunction(JsInfoLogPrint));
    aceConsoleObj->SetProperty(runtime_, "warn", runtime_->NewFunction(JsWarnLogPrint));
    aceConsoleObj->SetProperty(runtime_, "error", runtime_->NewFunction(JsErrorLogPrint));
    global->SetProperty(runtime_, "aceConsole", aceConsoleObj);
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

    // ModuleManager::GetInstance()->InitTimerModule(localContext);
}

void JsiDeclarativeEngineInstance::InitGlobalObjectTemplate()
{
    // JsRegisterViews
}

void JsiDeclarativeEngineInstance::InitGroupJsBridge()
{

}

thread_local std::unordered_map<int32_t, shared_ptr<JsValue>&> JsiDeclarativeEngineInstance::rootViewMap_;

void JsiDeclarativeEngineInstance::RootViewHandle(JsRuntime* runtime, shared_ptr<JsValue>& value)
{
    LOGD("RootViewHandle");
    if (runtime == nullptr) {
        LOGE("jsRuntime is nullptr");
        return;
    }
    RefPtr<JsAcePage> page = JsiDeclarativeEngineInstance::GetStagingPage(runtime);
    if (page != nullptr) {
        rootViewMap_.emplace(page->GetPageId(), value);
    }
}

void JsiDeclarativeEngineInstance::DestroyRootViewHandle(int32_t pageId)
{
    CHECK_RUN_ON(JS);
    if (rootViewMap_.count(pageId) != 0) {
        // shared_ptr<JsValue>& rootView = rootViewMap_[pageId];
        // JSView* jsView = static_cast<JSView*>(rootView->GetAlignedPointerFromInternalField(0));
        // jsView->Destroy(nullptr);
        rootViewMap_.erase(pageId);
    }
}

void JsiDeclarativeEngineInstance::DestroyAllRootViewHandle()
{
    CHECK_RUN_ON(JS);
    if (rootViewMap_.size() > 0) {
        LOGI("DestroyAllRootViewHandle release left %{private}zu views ", rootViewMap_.size());
    }
    // for (const auto& pair : rootViewMap_) {
        // shared_ptr<JsValue>& rootView = pair.second;
        // JSView* jsView = static_cast<JSView*>(rootView->GetAlignedPointerFromInternalField(0));
        // jsView->Destroy(nullptr);
    // }
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

RefPtr<JsAcePage> JsiDeclarativeEngineInstance::GetRunningPage(JsRuntime* runtime)
{
    LOGD("GetRunningPage");
    if (runtime == nullptr) {
        LOGE("jsRuntime is nullptr");
        return nullptr;
    }
    auto engineInstance = static_cast<JsiDeclarativeEngineInstance*>(runtime->GetEmbedderData());
    if (engineInstance == nullptr) {
        LOGE("engineInstance is nullptr");
        return nullptr;
    }
    return engineInstance->GetRunningPage();
}

RefPtr<JsAcePage> JsiDeclarativeEngineInstance::GetStagingPage(JsRuntime* runtime)
{
    LOGD("GetStagingPage");
    if (runtime == nullptr) {
        LOGE("jsRuntime is nullptr");
        return nullptr;
    }
    auto engineInstance = static_cast<JsiDeclarativeEngineInstance*>(runtime->GetEmbedderData());
    if (engineInstance == nullptr) {
        LOGE("engineInstance is nullptr");
        return nullptr;
    }
    return engineInstance->GetStagingPage();
}

void JsiDeclarativeEngineInstance::PostJsTask(JsRuntime* runtime, std::function<void()>&& task)
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

void JsiDeclarativeEngineInstance::TriggerPageUpdate(JsRuntime* runtime)
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

RefPtr<PipelineContext> JsiDeclarativeEngineInstance::GetPipelineContext(JsRuntime* runtime)
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
}

bool JsiDeclarativeEngine::Initialize(const RefPtr<FrontendDelegate>& delegate)
{
    CHECK_RUN_ON(JS);
    ACE_SCOPED_TRACE("JsiDeclarativeEngine::Initialize");
    LOGI("JsiDeclarativeEngine Initialize");
    ACE_DCHECK(delegate);
    engineInstance_ = AceType::MakeRefPtr<JsiDeclarativeEngineInstance>(delegate, instanceId_);
    return engineInstance_->InitJsEnv(IsDebugVersion() && NeedDebugBreakPoint());
}

void JsiDeclarativeEngine::LoadJs(const std::string& url, const RefPtr<JsAcePage>& page, bool isMainPage)
{
    ACE_SCOPED_TRACE("JsiDeclarativeEngine::LoadJs");
    LOGD("JsiDeclarativeEngine LoadJs");
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetStagingPage(page);
    if (isMainPage) {
        ACE_DCHECK(!engineInstance_->GetRunningPage());
        engineInstance_->SetRunningPage(page);
    }

    auto runtime = engineInstance_->GetJsRuntime();
    auto delegate = engineInstance_->GetDelegate();
    JsiDeclarativeUtils::SetCurrentState(
        runtime, JsErrorType::LOAD_JS_BUNDLE_ERROR, instanceId_, page->GetUrl(), page);

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
            std::string appMap;
            if (delegate->GetAssetContent("app.js.map", appMap)) {
                page->SetAppMap(appMap);
            } else {
                LOGW("app map load failed!");
            }
            std::string appBasePath = delegate->GetAssetPath("app.abc");
            std::string appPath = appBasePath.append("app.abc");
            LOGI("appPath is: %{private}s", appPath.c_str());
            if (!runtime->ExecuteJsBin(appPath)) {
                LOGE("ExecuteJsBin \"app.js\" failed.");
                return;
            }
            CallAppFunc("onCreate");
        }
        if (!runtime->ExecuteJsBin(assetPath)) {
            LOGE("ExecuteJsBin %{private}s failed.", urlName.c_str());
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
    LOGD("JsiDeclarativeEngine UpdateStagingPage");
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

void JsiDeclarativeEngine::TimerCallback(const std::string& callbackId, const std::string& delay, bool isInterval)
{

}

void JsiDeclarativeEngine::DestroyPageInstance(int32_t pageId)
{
    LOGI("JsiDeclarativeEngine DestroyPageInstance");
    ACE_DCHECK(engineInstance_);

    engineInstance_->DestroyRootViewHandle(pageId);
}

void JsiDeclarativeEngine::DestroyApplication(const std::string& packageName)
{
    LOGI("JsiDeclarativeEngine DestroyApplication, packageName %{public}s", packageName.c_str());
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    JsiDeclarativeUtils::SetCurrentState(runtime, JsErrorType::DESTROY_APP_ERROR, instanceId_, "",
        engineInstance_->GetStagingPage());

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
        LOGW("unsupport state");
    }
}

void JsiDeclarativeEngine::OnWindowDisplayModeChanged(bool isShownInMultiWindow, const std::string& data)
{
    LOGI("JsiDeclarativeEngine OnWindowDisplayModeChanged");
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    const std::vector<shared_ptr<JsValue>>& argv = {
        runtime->NewBoolean(isShownInMultiWindow), runtime->NewString(data) };
    CallAppFunc("onWindowDisplayModeChanged", argv);
}

void JsiDeclarativeEngine::CallAppFunc(const std::string& appFuncName)
{
    const std::vector<shared_ptr<JsValue>>& argv = { };
    CallAppFunc(appFuncName, argv);
}

void JsiDeclarativeEngine::CallAppFunc(const std::string& appFuncName, const std::vector<shared_ptr<JsValue>>& argv)
{
    LOGD("JsiDeclarativeEngine CallAppFunc");
    shared_ptr<JsRuntime> runtime = engineInstance_->GetJsRuntime();
    ACE_DCHECK(runtime);
    shared_ptr<JsValue> global = runtime->GetGlobal();
    shared_ptr<JsValue> exportsObject = global->GetProperty(runtime, "exports");
    if (!exportsObject->IsObject(runtime)) {
        LOGE("property \"exports\" is not a object");
        return;
    }
    shared_ptr<JsValue> defaultObject = exportsObject->GetProperty(runtime, "default");
    if (!defaultObject->IsObject(runtime)) {
        LOGE("property \"default\" is not a object");
        return;
    }
    shared_ptr<JsValue> func = defaultObject->GetProperty(runtime, appFuncName);
    if (!func || !func->IsFunction(runtime)) {
        LOGE("%{public}s not found or is not a function!", appFuncName.c_str());
        return;
    }
    func->Call(runtime, global, argv, argv.size());
}

void JsiDeclarativeEngine::MediaQueryCallback(const std::string& callbackId, const std::string& args)
{
    JsEngine::MediaQueryCallback(callbackId, args);
}

void JsiDeclarativeEngine::RequestAnimationCallback(const std::string& callbackId, uint64_t timeStamp)
{

}

void JsiDeclarativeEngine::JsCallback(const std::string& callbackId, const std::string& args)
{

}

void JsiDeclarativeEngine::RunGarbageCollection()
{
    if (engineInstance_ && engineInstance_->GetJsRuntime()) {
        engineInstance_->GetJsRuntime()->RunGC();
    }
}

RefPtr<GroupJsBridge> JsiDeclarativeEngine::GetGroupJsBridge()
{
    return nullptr;
    // return AceType::MakeRefPtr<JsiGroupJsBridge>();
}

} // namespace OHOS::Ace::Framework
