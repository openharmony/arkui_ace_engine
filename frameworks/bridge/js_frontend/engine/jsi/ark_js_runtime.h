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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ENGINE_JSI_ARK_JS_RUNTIME_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ENGINE_JSI_ARK_JS_RUNTIME_H

#if defined(PREVIEW)
#include <map>
#include "frameworks/bridge/declarative_frontend/engine/jsi/utils/jsi_module_searcher.h"
#endif
#include <memory>

#include "ecmascript/napi/include/jsnapi.h"
#include "native_engine/impl/ark/ark_native_engine.h"
#include "native_engine/native_engine.h"

#include "base/log/log.h"
#include "frameworks/bridge/js_frontend/engine/jsi/js_runtime.h"

namespace panda::ecmascript {
class EcmaVM;
} // namespace panda::ecmascript

// NOLINTNEXTLINE(readability-identifier-naming)
namespace OHOS::Ace::Framework {
using panda::ArrayRef;
using panda::BooleanRef;
using panda::EscapeLocalScope;
using panda::FunctionRef;
using panda::Global;
using panda::IntegerRef;
using panda::JSExecutionScope;
using panda::JSNApi;
using panda::JSON;
using panda::JSValueRef;
using panda::Local;
using panda::LocalScope;
using panda::NativePointerRef;
using panda::NumberRef;
using panda::ObjectRef;
using panda::RuntimeOption;
using panda::StringRef;
using panda::ecmascript::EcmaVM;
class PandaFunctionData;

using DebuggerPostTask = std::function<void(std::function<void()>&&)>;

// NOLINTNEXTLINE(fuchsia-multiple-inheritance)
class ArkJSRuntime final : public JsRuntime, public std::enable_shared_from_this<ArkJSRuntime> {
public:
    using ErrorEventHandler = std::function<void(const std::string&, const std::string&)>;
#if !defined(PREVIEW)
    void StartDebuggerForSocketPair(std::string& option, uint32_t socketFd);
#endif
    bool Initialize(const std::string& libraryPath, bool isDebugMode, int32_t instanceId) override;
    bool InitializeFromExistVM(EcmaVM* vm);
    void Reset() override;
    void SetLogPrint(LOG_PRINT out) override;
    bool StartDebugger() override;
    shared_ptr<JsValue> EvaluateJsCode(const std::string& src) override;
    bool EvaluateJsCode(
        const uint8_t* buffer, int32_t size, const std::string& filePath = "", bool needUpdate = false) override;
    bool ExecuteJsBin(const std::string& fileName,
        const std::function<void(const std::string&, int32_t)>& errorCallback = nullptr) override;
    bool ExecuteJsBinForAOT(const std::string& fileName,
        const std::function<void(const std::string&, int32_t)>& errorCallback = nullptr) override;
    shared_ptr<JsValue> GetGlobal() override;
    shared_ptr<JsValue> GetGlobal(ArkNativeEngine* nativeArkEngine);
    void RunGC() override;
    void RunFullGC() override;

    shared_ptr<JsValue> NewNumber(double d) override;
    shared_ptr<JsValue> NewInt32(int32_t value) override;
    shared_ptr<JsValue> NewBoolean(bool value) override;
    shared_ptr<JsValue> NewNull() override;
    shared_ptr<JsValue> NewUndefined() override;
    shared_ptr<JsValue> NewString(const std::string& str) override;
    shared_ptr<JsValue> ParseJson(const std::string& str) override;
    shared_ptr<JsValue> NewObject() override;
    shared_ptr<JsValue> NewArray() override;
    shared_ptr<JsValue> NewFunction(RegisterFunctionType func) override;
    shared_ptr<JsValue> NewNativePointer(void* ptr) override;
    void ThrowError(const std::string& msg, int32_t code) override;
    void RegisterUncaughtExceptionHandler(UncaughtExceptionCallback callback) override;
    void HandleUncaughtException(panda::TryCatch& tryCatch,
        const std::function<void(const std::string&, int32_t)>& errorCallback = nullptr) override;
    void HandleUncaughtExceptionWithoutNativeEngine(panda::TryCatch& trycatch,
        const std::function<void(const std::string&, int32_t)>& errorCallback = nullptr) override;
    bool HasPendingException() override;
    void ExecutePendingJob() override;
    void DumpHeapSnapshot(bool isPrivate) override;
    void NotifyUIIdle() override;
    void DestroyHeapProfiler() override;
    bool IsExecuteModuleInAbcFile(
        const std::string &bundleName, const std::string &moduleName, const std::string &ohmurl);
    bool ExecuteModuleBuffer(const uint8_t *data, int32_t size, const std::string &filename, bool needUpdate = false);

    int32_t LoadDestinationFile(const std::string& bundleName, const std::string& moduleName,
        const std::string& pageSourceFile, bool isSingleton);

    const EcmaVM* GetEcmaVm() const override
    {
        return GetThreadVm() ? GetThreadVm() : vm_;
    }

    const EcmaVM* GetThreadVm() const
    {
        return threadVm_;
    }

    void SetThreadVm(EcmaVM* vm)
    {
        threadVm_ = vm;
    }

    void SetAssetPath(const std::string& assetPath)
    {
        panda::JSNApi::SetAssetPath(vm_, assetPath);
    }

    void SetBundleName(const std::string& bundleName)
    {
        panda::JSNApi::SetBundleName(vm_, bundleName);
    }

    void SetBundle(bool isBundle)
    {
        panda::JSNApi::SetBundle(vm_, isBundle);
    }

    void SetModuleName(const std::string& moduleName)
    {
        panda::JSNApi::SetModuleName(vm_, moduleName);
    }

    void SetDebuggerPostTask(DebuggerPostTask&& task)
    {
        debuggerPostTask_ = std::move(task);
    }

    void SetErrorEventHandler(ErrorEventHandler&& errorCallback) override
    {
        errorCallback_ = std::move(errorCallback);
    }

    const ErrorEventHandler& GetErrorEventHandler()
    {
        return errorCallback_;
    }

    void SetDebugMode(bool isDebugMode)
    {
        isDebugMode_ = isDebugMode;
    }

    void SetInstanceId(int32_t instanceId)
    {
        instanceId_ = instanceId;
    }

    void SetLanguage(const std::string& language)
    {
        language_ = language;
    }

    void SetNativeEngine(NativeEngine* nativeEngine)
    {
        nativeEngine_ = nativeEngine;
    }

    NativeEngine* GetNativeEngine() const
    {
        return nativeEngine_;
    }

#if defined(PREVIEW)
    void SetPkgNameList(const std::map<std::string, std::string>& map)
    {
        pkgNameMap_ = map;
    }

    void SetPkgAliasList(const std::map<std::string, std::string>& map)
    {
        pkgAliasMap_ = map;
    }

    void SetpkgContextInfoList(const std::map<std::string, std::vector<std::vector<std::string>>>& map)
    {
        pkgContextInfoMap_ = map;
    }

    void SetPreviewFlag(bool flag)
    {
        isComponentPreview_ = flag;
    }

    bool GetPreviewFlag() const
    {
        return isComponentPreview_;
    }

    std::string GetRequiredComponent() const
    {
        return requiredComponent_;
    }

    void SetRequiredComponent(const std::string &componentName)
    {
        requiredComponent_ = componentName;
    }

    void AddPreviewComponent(const std::string &componentName, const panda::Global<panda::ObjectRef> &componentObj)
    {
        previewComponents_.emplace(componentName, componentObj);
    }

    panda::Global<panda::ObjectRef> GetPreviewComponent(EcmaVM* vm, const std::string &componentName)
    {
        auto iter = previewComponents_.find(componentName);
        if (iter != previewComponents_.end()) {
            auto retVal = iter->second;
            previewComponents_.erase(iter);
            return retVal;
        }
        panda::Global<panda::ObjectRef> undefined(vm, panda::JSValueRef::Undefined(vm));
        return undefined;
    }

    void AddRootView(const panda::Global<panda::ObjectRef> &RootView)
    {
        RootView_ = RootView;
    }

    panda::Global<panda::ObjectRef> GetRootView()
    {
        return RootView_;
    }
#endif

private:
    EcmaVM* vm_ = nullptr;
    int32_t instanceId_ = 0;
    std::string language_;
    LOG_PRINT print_ { nullptr };
    UncaughtExceptionCallback uncaughtErrorHandler_ { nullptr };
    std::string libPath_ {};
    bool usingExistVM_ = false;
    bool isDebugMode_ = false;
    DebuggerPostTask debuggerPostTask_;
    ErrorEventHandler errorCallback_;
    NativeEngine* nativeEngine_;
#if defined(PREVIEW)
    bool isComponentPreview_ = false;
    std::string requiredComponent_ {};
    std::multimap<std::string, panda::Global<panda::ObjectRef>> previewComponents_;
    panda::Global<panda::ObjectRef> RootView_;
    std::map<std::string, std::string> pkgNameMap_;
    std::map<std::string, std::string> pkgAliasMap_;
    std::map<std::string, std::vector<std::vector<std::string>>> pkgContextInfoMap_;
#endif
    static thread_local EcmaVM* threadVm_;
};

class PandaFunctionData {
public:
    PandaFunctionData(std::weak_ptr<ArkJSRuntime> runtime, RegisterFunctionType func)
        : runtime_(runtime), func_(std::move(func))
    {}

    ~PandaFunctionData() = default;

    PandaFunctionData(const PandaFunctionData&) = delete;
    void operator=(const PandaFunctionData&) = delete;
    PandaFunctionData(PandaFunctionData&&) = delete;
    PandaFunctionData& operator=(PandaFunctionData&&) = delete;

private:
    Local<JSValueRef> Callback(panda::JsiRuntimeCallInfo* info) const;
    std::weak_ptr<ArkJSRuntime> runtime_;
    RegisterFunctionType func_;
    friend Local<JSValueRef> FunctionCallback(panda::JsiRuntimeCallInfo* info);
};
} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ENGINE_JSI_ARK_JS_RUNTIME_H
