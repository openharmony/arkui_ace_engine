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

#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_runtime.h"

#include "ecmascript/napi/include/dfx_jsnapi.h"

#include "frameworks/base/log/log_wrapper.h"
#include "frameworks/base/utils/system_properties.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_value.h"
#include "frameworks/core/common/connect_server_manager.h"

// NOLINTNEXTLINE(readability-identifier-naming)
namespace OHOS::Ace::Framework {
// NOLINTNEXTLINE(readability-identifier-naming)
static constexpr auto PANDA_MAIN_FUNCTION = "_GLOBAL::func_main_0";
#if !defined(PREVIEW)
constexpr int32_t FORMAT_JSON = 1;
#endif

Local<JSValueRef> FunctionCallback(panda::JsiRuntimeCallInfo* info)
{
    auto package = reinterpret_cast<PandaFunctionData*>(info->GetData());
    if (package == nullptr) {
        return JSValueRef::Undefined(info->GetVM());
    }
    return package->Callback(info);
}

void FunctionDeleter(void *nativePointer, void *data)
{
    auto info = reinterpret_cast<PandaFunctionData*>(data);
    if (info != nullptr) {
        delete info;
    }
}

bool ArkJSRuntime::Initialize(const std::string& libraryPath, bool isDebugMode, int32_t instanceId)
{
    RuntimeOption option;
    option.SetGcType(RuntimeOption::GC_TYPE::GEN_GC);
#ifdef OHOS_PLATFORM
    option.SetArkProperties(SystemProperties::GetArkProperties());
    option.SetArkBundleName(SystemProperties::GetArkBundleName());
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
#if !defined(PREVIEW) && !defined(IOS_PLATFORM)
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

bool ArkJSRuntime::StartDebugger()
{
    bool ret = false;
#if !defined(PREVIEW)
    if (!libPath_.empty()) {
    JSNApi::DebugOption debugOption = {libPath_.c_str(), isDebugMode_};
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
        ConnectServerManager::Get().AddInstance(instanceId_, language_);
        ret = JSNApi::StartDebugger(vm_, debugOption, instanceId_, debuggerPostTask_);
#elif defined(ANDROID_PLATFORM)
        ret = JSNApi::StartDebugger(vm_, debugOption, instanceId_, debuggerPostTask_);
#endif
    }
#if defined(IOS_PLATFORM)
    JSNApi::DebugOption debugOption = {nullptr, isDebugMode_};
    ret = JSNApi::StartDebugger(vm_, debugOption, instanceId_, debuggerPostTask_);
#endif
#endif
    return ret;
}

bool ArkJSRuntime::ExecuteModuleBuffer(const uint8_t* data, int32_t size, const std::string& filename, bool needUpdate)
{
#if defined(PREVIEW)
    return JSNApi::ExecuteModuleBuffer(vm_, data, size, filename, needUpdate);
#else
    JSExecutionScope executionScope(vm_);
    LocalScope scope(vm_);
    bool ret = JSNApi::ExecuteModuleBuffer(vm_, data, size, filename, needUpdate);
    HandleUncaughtException();
    return ret;
#endif
}

shared_ptr<JsValue> ArkJSRuntime::EvaluateJsCode([[maybe_unused]] const std::string& src)
{
    return NewUndefined();
}

bool ArkJSRuntime::EvaluateJsCode(const uint8_t* buffer, int32_t size, const std::string& filePath, bool needUpdate)
{
    JSExecutionScope executionScope(vm_);
    LocalScope scope(vm_);
    bool ret = JSNApi::Execute(vm_, buffer, size, PANDA_MAIN_FUNCTION, filePath, needUpdate);
    HandleUncaughtException();
    return ret;
}

bool ArkJSRuntime::ExecuteJsBin(const std::string& fileName,
    const std::function<void(const std::string&, int32_t)>& errorCallback)
{
    JSExecutionScope executionScope(vm_);
    LocalScope scope(vm_);
    bool ret = JSNApi::Execute(vm_, fileName, PANDA_MAIN_FUNCTION);
    HandleUncaughtException(errorCallback);
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
    JSNApi::TriggerGC(vm_);
}

void ArkJSRuntime::RunFullGC()
{
    JSExecutionScope executionScope(vm_);
    LocalScope scope(vm_);
    JSNApi::TriggerGC(vm_, JSNApi::TRIGGER_GC_TYPE::FULL_GC);
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
        FunctionRef::New(vm_, FunctionCallback, FunctionDeleter, data));
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
    uncaughtErrorHandler_ = callback;
}

bool ArkJSRuntime::HasPendingException()
{
    return JSNApi::HasPendingException(vm_);
}

void ArkJSRuntime::HandleUncaughtException(
    const std::function<void(const std::string&, int32_t)>& errorCallback)
{
    if (uncaughtErrorHandler_ == nullptr) {
        LOGE("uncaughtErrorHandler is null.");
        return;
    }

    Local<ObjectRef> exception = JSNApi::GetAndClearUncaughtException(vm_);
    if (!exception.IsEmpty() && !exception->IsHole() && errorCallback != nullptr) {
        errorCallback("loading js file has crash or the uri of router is not exist.", Framework::ERROR_CODE_URI_ERROR);
    }

    if (!exception.IsEmpty() && !exception->IsHole()) {
        LOGI("HandleUncaughtException catch exception.");
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

#if !defined(PREVIEW) && !defined(IOS_PLATFORM)
void ArkJSRuntime::DumpHeapSnapshot(bool isPrivate)
{
    if (vm_ == nullptr) {
        LOGW("vm_ is nullptr.");
    }
    LocalScope scope(vm_);
    panda::DFXJSNApi::DumpHeapSnapshot(vm_, FORMAT_JSON, true, isPrivate);
}
#else
void ArkJSRuntime::DumpHeapSnapshot(bool isPrivate)
{
    LOGE("Do not support Ark DumpHeapSnapshot on Windows or MacOS");
}
#endif

Local<JSValueRef> PandaFunctionData::Callback(panda::JsiRuntimeCallInfo* info) const
{
    auto runtime = runtime_.lock();
    if (runtime == nullptr) {
        LOGE("runtime is nullptr");
        return Local<JSValueRef>();
    }
    EscapeLocalScope scope(runtime->GetEcmaVm());
    shared_ptr<JsValue> thisPtr =
        std::static_pointer_cast<JsValue>(std::make_shared<ArkJSValue>(runtime, info->GetThisRef()));

    std::vector<shared_ptr<JsValue>> argv;
    int32_t length = info->GetArgsNumber();
    argv.reserve(length);
    for (int32_t i = 0; i < length; ++i) {
        argv.emplace_back(
            std::static_pointer_cast<JsValue>(std::make_shared<ArkJSValue>(runtime, info->GetCallArgRef(i))));
    }
    shared_ptr<JsValue> result = func_(runtime, thisPtr, argv, length);
    return scope.Escape(std::static_pointer_cast<ArkJSValue>(result)->GetValue(runtime));
}

} // namespace OHOS::Ace::Framework
