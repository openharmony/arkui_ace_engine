/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_runtime.h"

#include <unistd.h>

#include "ecmascript/napi/include/dfx_jsnapi.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_value.h"
#include "frameworks/core/common/ace_application_info.h"
#include "frameworks/core/common/connect_server_manager.h"
#include "frameworks/core/common/hdc_register.h"

// NOLINTNEXTLINE(readability-identifier-naming)
namespace OHOS::Ace::Framework {
// NOLINTNEXTLINE(readability-identifier-naming)
static constexpr auto PANDA_MAIN_FUNCTION = "_GLOBAL::func_main_0";
#if !defined(PREVIEW)
constexpr auto DEBUGGER = "@Debugger";
#endif

Local<JSValueRef> FunctionCallback(panda::JsiRuntimeCallInfo* info)
{
    auto package = reinterpret_cast<PandaFunctionData*>(info->GetData());
    if (package == nullptr) {
        return JSValueRef::Undefined(info->GetVM());
    }
    return package->Callback(info);
}

void FunctionDeleter(void *env, void *nativePointer, void *data)
{
    auto info = reinterpret_cast<PandaFunctionData*>(data);
    if (info != nullptr) {
        delete info;
    }
}

thread_local EcmaVM* ArkJSRuntime::threadVm_ = nullptr;

bool ArkJSRuntime::Initialize(const std::string& libraryPath, bool isDebugMode, int32_t instanceId)
{
    RuntimeOption option;
    option.SetGcType(RuntimeOption::GC_TYPE::GEN_GC);
#ifdef OHOS_PLATFORM
    option.SetArkProperties(SystemProperties::GetArkProperties());
    option.SetArkBundleName(SystemProperties::GetArkBundleName());
    option.SetMemConfigProperty(SystemProperties::GetMemConfigProperty());
    option.SetGcThreadNum(SystemProperties::GetGcThreadNum());
    option.SetLongPauseTime(SystemProperties::GetLongPauseTime());
    option.SetEnableAsmInterpreter(SystemProperties::GetAsmInterpreterEnabled());
    option.SetAsmOpcodeDisableRange(SystemProperties::GetAsmOpcodeDisableRange());
    LOGI("Initialize ark properties = %{public}d, bundlename = %{public}s", SystemProperties::GetArkProperties(),
        SystemProperties::GetArkBundleName().c_str());
#endif
    const int64_t poolSize = 0x10000000; // 256M
    option.SetGcPoolSize(poolSize);
    option.SetLogLevel(RuntimeOption::LOG_LEVEL::FOLLOW);
    option.SetLogBufPrint(print_);
    option.SetDebuggerLibraryPath(libraryPath);
    libPath_ = libraryPath;
    isDebugMode_ = isDebugMode;
    instanceId_ = instanceId;

    vm_ = JSNApi::CreateJSVM(option);
#if defined(PREVIEW)
    if (!pkgNameMap_.empty()) {
        JSNApi::SetPkgNameList(vm_, pkgNameMap_);
    }
    if (!pkgAliasMap_.empty()) {
        JSNApi::SetPkgAliasList(vm_, pkgAliasMap_);
    }
    if (!pkgContextInfoMap_.empty()) {
        JSNApi::SetpkgContextInfoList(vm_, pkgContextInfoMap_);
    }
#endif
    return vm_ != nullptr;
}

bool ArkJSRuntime::InitializeFromExistVM(EcmaVM* vm)
{
    vm_ = vm;
    usingExistVM_ = true;
    return vm_ != nullptr;
}

void ArkJSRuntime::Reset()
{
    if (vm_ != nullptr) {
        if (!usingExistVM_) {
#if !defined(PREVIEW)
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
            HdcRegister::Get().StopHdcRegister(instanceId_);
            ConnectServerManager::Get().RemoveInstance(instanceId_);
#endif
            JSNApi::StopDebugger(vm_);
#endif
            JSNApi::DestroyJSVM(vm_);
            vm_ = nullptr;
        }
    }
#if defined(PREVIEW)
    previewComponents_.clear();
#endif
}

void ArkJSRuntime::SetLogPrint(LOG_PRINT out)
{
    print_ = out;
}

#if !defined(PREVIEW) && !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
static int ParseHdcRegisterOption(std::string& option)
{
    LOGI("hdc option is %{public}s ", option.c_str());
    if (option.find(":") == std::string::npos) {
        return -1;
    }
    std::size_t pos = option.find_first_of(":");
    std::string idStr = option.substr(pos + 1);
    if (idStr.find(DEBUGGER) == std::string::npos) {
        return -1;
    }
    pos = idStr.find(DEBUGGER);
    idStr = idStr.substr(0, pos);
    if (idStr.find("@") != std::string::npos) {
        pos = idStr.find("@");
        idStr = idStr.substr(pos + 1);
    }
    return static_cast<uint32_t>(std::atol(idStr.c_str()));
}

void ArkJSRuntime::StartDebuggerForSocketPair(std::string& option, uint32_t socketFd)
{
    CHECK_NULL_VOID(vm_);
    int identifierId = ParseHdcRegisterOption(option);
    panda::JSNApi::StartDebuggerForSocketPair(identifierId, socketFd);
}
#endif

bool ArkJSRuntime::StartDebugger()
{
    bool ret = false;
#if !defined(PREVIEW)
    if (!libPath_.empty()) {
        bool isDebugApp = AceApplicationInfo::GetInstance().IsDebugVersion();
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
        auto callback = [instanceId = instanceId_,
                            weak = weak_from_this(), isDebugApp](int socketFd, std::string option) {
            LOGI("HdcRegister callback socket %{public}d, option %{public}s.", socketFd, option.c_str());
            if (option.find(DEBUGGER) == std::string::npos) {
                if (isDebugApp) {
                    ConnectServerManager::Get().StopConnectServer();
                }
                ConnectServerManager::Get().StartConnectServerWithSocketPair(socketFd);
            } else {
                auto runtime = weak.lock();
                CHECK_NULL_VOID(runtime);
                if (isDebugApp) {
                    JSNApi::StopDebugger(ParseHdcRegisterOption(option));
                }
                runtime->StartDebuggerForSocketPair(option, socketFd);
            }
        };

        HdcRegister::Get().StartHdcRegister(instanceId_, callback);
        ConnectServerManager::Get().SetDebugMode();
#endif
        //FA:true port:-1
        JSNApi::DebugOption debugOption = { libPath_.c_str(), isDebugApp ? isDebugMode_ : false, -1, true };
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
        ConnectServerManager::Get().AddInstance(gettid(), language_);
        ret = JSNApi::NotifyDebugMode(gettid(), vm_, debugOption, gettid(), debuggerPostTask_, isDebugApp);
#elif defined(ANDROID_PLATFORM)
        ret = JSNApi::StartDebugger(vm_, debugOption, instanceId_, debuggerPostTask_);
#endif
    }
#if defined(IOS_PLATFORM)
    JSNApi::DebugOption debugOption = { nullptr, isDebugMode_, -1, true }; //FA:true port:-1
    ret = JSNApi::StartDebugger(vm_, debugOption, instanceId_, debuggerPostTask_);
#endif
#endif
    return ret;
}

bool ArkJSRuntime::IsExecuteModuleInAbcFile(
    const std::string &bundleName, const std::string &moduleName, const std::string &ohmurl)
{
    JSExecutionScope executionScope(vm_);
    LocalScope scope(vm_);
    panda::TryCatch trycatch(vm_);
    bool ret = JSNApi::IsExecuteModuleInAbcFile(vm_, bundleName, moduleName, ohmurl);
    HandleUncaughtException(trycatch);
    return ret;
}

bool ArkJSRuntime::ExecuteModuleBuffer(const uint8_t* data, int32_t size, const std::string& filename, bool needUpdate)
{
    JSExecutionScope executionScope(vm_);
    LocalScope scope(vm_);
    panda::TryCatch trycatch(vm_);
    bool ret = JSNApi::ExecuteModuleBuffer(vm_, data, size, filename, needUpdate);
    HandleUncaughtException(trycatch);
    return ret;
}

shared_ptr<JsValue> ArkJSRuntime::EvaluateJsCode([[maybe_unused]] const std::string& src)
{
    return NewUndefined();
}

bool ArkJSRuntime::EvaluateJsCode(const uint8_t* buffer, int32_t size, const std::string& filePath, bool needUpdate)
{
    JSExecutionScope executionScope(vm_);
    LocalScope scope(vm_);
    panda::TryCatch trycatch(vm_);
    bool ret = JSNApi::Execute(vm_, buffer, size, PANDA_MAIN_FUNCTION, filePath, needUpdate);
    HandleUncaughtException(trycatch);
    return ret;
}

bool ArkJSRuntime::ExecuteJsBin(const std::string& fileName,
    const std::function<void(const std::string&, int32_t)>& errorCallback)
{
    JSExecutionScope executionScope(vm_);
    LocalScope scope(vm_);
    panda::TryCatch trycatch(vm_);
    bool ret = JSNApi::Execute(vm_, fileName, PANDA_MAIN_FUNCTION);
    HandleUncaughtException(trycatch, errorCallback);
    return ret;
}

bool ArkJSRuntime::ExecuteJsBinForAOT(const std::string& fileName,
    const std::function<void(const std::string&, int32_t)>& errorCallback)
{
    JSExecutionScope executionScope(vm_);
    LocalScope scope(vm_);
    panda::TryCatch trycatch(vm_);
    bool ret = JSNApi::ExecuteForAbsolutePath(vm_, fileName, PANDA_MAIN_FUNCTION);
    HandleUncaughtException(trycatch, errorCallback);
    return ret;
}

shared_ptr<JsValue> ArkJSRuntime::GetGlobal()
{
    LocalScope scope(vm_);
    return std::make_shared<ArkJSValue>(shared_from_this(), JSNApi::GetGlobalObject(vm_));
}

void ArkJSRuntime::RunGC()
{
    JSExecutionScope executionScope(vm_);
    LocalScope scope(vm_);
    JSNApi::HintGC(vm_, JSNApi::MemoryReduceDegree::LOW, panda::ecmascript::GCReason::TRIGGER_BY_ARKUI);
}

void ArkJSRuntime::RunFullGC()
{
    JSExecutionScope executionScope(vm_);
    LocalScope scope(vm_);
    JSNApi::HintGC(vm_, JSNApi::MemoryReduceDegree::HIGH, panda::ecmascript::GCReason::TRIGGER_BY_ARKUI);
}

shared_ptr<JsValue> ArkJSRuntime::NewInt32(int32_t value)
{
    LocalScope scope(vm_);
    return std::make_shared<ArkJSValue>(shared_from_this(), IntegerRef::New(vm_, value));
}

shared_ptr<JsValue> ArkJSRuntime::NewBoolean(bool value)
{
    LocalScope scope(vm_);
    return std::make_shared<ArkJSValue>(shared_from_this(), BooleanRef::New(vm_, value));
}

shared_ptr<JsValue> ArkJSRuntime::NewNumber(double d)
{
    LocalScope scope(vm_);
    return std::make_shared<ArkJSValue>(shared_from_this(), NumberRef::New(vm_, d));
}

shared_ptr<JsValue> ArkJSRuntime::NewNull()
{
    LocalScope scope(vm_);
    return std::make_shared<ArkJSValue>(shared_from_this(), JSValueRef::Null(vm_));
}

shared_ptr<JsValue> ArkJSRuntime::NewUndefined()
{
    LocalScope scope(vm_);
    return std::make_shared<ArkJSValue>(shared_from_this(), JSValueRef::Undefined(vm_));
}

shared_ptr<JsValue> ArkJSRuntime::NewString(const std::string& str)
{
    LocalScope scope(vm_);
    return std::make_shared<ArkJSValue>(shared_from_this(), StringRef::NewFromUtf8(vm_, str.c_str()));
}

shared_ptr<JsValue> ArkJSRuntime::ParseJson(const std::string& str)
{
    LocalScope scope(vm_);
    Local<StringRef> string = StringRef::NewFromUtf8(vm_, str.c_str());
    return std::make_shared<ArkJSValue>(shared_from_this(), JSON::Parse(vm_, string));
}

shared_ptr<JsValue> ArkJSRuntime::NewObject()
{
    LocalScope scope(vm_);
    return std::make_shared<ArkJSValue>(shared_from_this(), ObjectRef::New(vm_));
}

shared_ptr<JsValue> ArkJSRuntime::NewArray()
{
    LocalScope scope(vm_);
    return std::make_shared<ArkJSValue>(shared_from_this(), ArrayRef::New(vm_));
}

shared_ptr<JsValue> ArkJSRuntime::NewFunction(RegisterFunctionType func)
{
    LocalScope scope(vm_);
    auto data = new PandaFunctionData(shared_from_this(), func);
    return std::make_shared<ArkJSValue>(shared_from_this(),
        FunctionRef::NewConcurrent(vm_, FunctionCallback, FunctionDeleter, data));
}

shared_ptr<JsValue> ArkJSRuntime::NewNativePointer(void* ptr)
{
    LocalScope scope(vm_);
    return std::make_shared<ArkJSValue>(shared_from_this(), NativePointerRef::New(vm_, ptr));
}

void ArkJSRuntime::ThrowError(const std::string& msg, int32_t code)
{
    auto errorVal = panda::Exception::Error(vm_, panda::StringRef::NewFromUtf8(vm_, msg.c_str()));
    auto codeVal = panda::Exception::Error(vm_, panda::StringRef::NewFromUtf8(vm_, std::to_string(code).c_str()));
    Local<StringRef> codeKey = StringRef::NewFromUtf8(vm_, "code");
    Local<ObjectRef> errorObj(errorVal);
    errorObj->Set(vm_, codeKey, codeVal);
    panda::JSNApi::ThrowException(vm_, errorObj);
}

void ArkJSRuntime::RegisterUncaughtExceptionHandler(UncaughtExceptionCallback callback)
{
    JSNApi::EnableUserUncaughtErrorHandler(vm_);
    std::weak_ptr<ArkJSRuntime> weakThis = shared_from_this();
    JSNApi::RegisterUncatchableErrorHandler(vm_,
        [weakThis](auto& tryCatch) {
            auto sharedThis = weakThis.lock();
            if (sharedThis) {
                sharedThis->HandleUncaughtExceptionWithoutNativeEngine(tryCatch, nullptr);
            } else {
                LOGE("ArkJSRuntime has been destructed.");
            }
        });
    uncaughtErrorHandler_ = callback;
}

bool ArkJSRuntime::HasPendingException()
{
    return JSNApi::HasPendingException(vm_);
}

void ArkJSRuntime::HandleUncaughtException(panda::TryCatch& trycatch,
    const std::function<void(const std::string&, int32_t)>& errorCallback)
{
    if (errorCallback != nullptr) {
        Local<ObjectRef> exception = trycatch.GetAndClearException();
        if (!exception.IsEmpty() && !exception->IsHole()) {
            errorCallback("loading js file has crash or the uri of router is not exist.",
                ERROR_CODE_URI_ERROR);
            return;
        }
    }

    // Handle the uncaught exception by native engine created by ability runtime in the stage model project.
    if (nativeEngine_) {
        nativeEngine_->HandleUncaughtException();
        return;
    }

    // Handle the uncaught exception without native engine, such as oom error
    HandleUncaughtExceptionWithoutNativeEngine(trycatch, errorCallback);
}

void ArkJSRuntime::HandleUncaughtExceptionWithoutNativeEngine(panda::TryCatch& trycatch,
    const std::function<void(const std::string&, int32_t)>& errorCallback)
{
    if (uncaughtErrorHandler_ == nullptr) {
        return;
    }

    Local<ObjectRef> exception = trycatch.GetAndClearException();
    if (!exception.IsEmpty() && !exception->IsHole()) {
        shared_ptr<JsValue> errorPtr =
            std::static_pointer_cast<JsValue>(std::make_shared<ArkJSValue>(shared_from_this(), exception));
        uncaughtErrorHandler_(errorPtr, shared_from_this());
    }
}

void ArkJSRuntime::ExecutePendingJob()
{
    LocalScope scope(vm_);
    JSNApi::ExecutePendingJob(vm_);
}

void ArkJSRuntime::NotifyUIIdle()
{
    LocalScope scope(vm_);
    panda::JSNApi::NotifyUIIdle(vm_, 0);
}

#if !defined(PREVIEW) && !defined(IOS_PLATFORM)
void ArkJSRuntime::DumpHeapSnapshot(bool isPrivate)
{
    panda::ecmascript::DumpSnapShotOption dumpOption;
    dumpOption.dumpFormat = panda::ecmascript::DumpFormat::JSON;
    dumpOption.isVmMode = true;
    dumpOption.isPrivate = isPrivate;
    dumpOption.isSync = false;
    LocalScope scope(vm_);
    panda::DFXJSNApi::DumpHeapSnapshot(vm_, dumpOption);
}
#else
void ArkJSRuntime::DumpHeapSnapshot(bool isPrivate)
{
    LOGE("Do not support Ark DumpHeapSnapshot on Windows or MacOS");
}
#endif

#if !defined(PREVIEW) && !defined(IOS_PLATFORM)
void ArkJSRuntime::DestroyHeapProfiler()
{
    LocalScope scope(vm_);
    panda::DFXJSNApi::DestroyHeapProfiler(vm_);
}
#else
void ArkJSRuntime::DestroyHeapProfiler()
{
    LOGE("Do not support Ark DestroyHeapProfiler on Windows or MacOS");
}
#endif

Local<JSValueRef> PandaFunctionData::Callback(panda::JsiRuntimeCallInfo* info) const
{
    auto runtime = runtime_.lock();
    if (runtime == nullptr) {
        return Local<JSValueRef>();
    }
    EscapeLocalScope scope(runtime->GetEcmaVm());
    shared_ptr<JsValue> thisPtr =
        std::static_pointer_cast<JsValue>(std::make_shared<ArkJSValue>(runtime, info->GetThisRef()));

    std::vector<shared_ptr<JsValue>> argv;
    uint32_t length = info->GetArgsNumber();
    argv.reserve(length);
    for (uint32_t i = 0; i < length; ++i) {
        argv.emplace_back(
            std::static_pointer_cast<JsValue>(std::make_shared<ArkJSValue>(runtime, info->GetCallArgRef(i))));
    }
    shared_ptr<JsValue> result = func_(runtime, thisPtr, argv, length);
    return scope.Escape(std::static_pointer_cast<ArkJSValue>(result)->GetValue(runtime));
}

int32_t ArkJSRuntime::LoadDestinationFile(const std::string& bundleName, const std::string& moduleName,
    const std::string& pageSourceFile, bool isSingleton)
{
    JSExecutionScope executionScope(vm_);
    LocalScope scope(vm_);
    panda::TryCatch trycatch(vm_);
    std::string module = moduleName;
    int ret = JSNApi::ExecuteWithSingletonPatternFlag(vm_, bundleName, module, pageSourceFile, isSingleton);
    HandleUncaughtException(trycatch);
    if (ret != 0) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "load pageSourceFile failed code is: %{public}d", ret);
    }
    return ret;
}
} // namespace OHOS::Ace::Framework
