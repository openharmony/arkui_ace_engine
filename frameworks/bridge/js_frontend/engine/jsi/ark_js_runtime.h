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
#include <unordered_map>
#include "frameworks/bridge/declarative_frontend/engine/jsi/utils/jsi_module_searcher.h"
#endif
#include <memory>

#include "ecmascript/napi/include/jsnapi.h"

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
#if !defined(WINDOWS_PLATFORM)
    bool StartDebugger(const char* libraryPath, EcmaVM* vm) const;
#endif
    bool Initialize(const std::string& libraryPath, bool isDebugMode, int32_t instanceId) override;
    bool InitializeFromExistVM(EcmaVM* vm);
    void Reset() override;
    void SetLogPrint(LOG_PRINT out) override;
    bool StartDebugger() override;
    shared_ptr<JsValue> EvaluateJsCode(const std::string& src) override;
    bool EvaluateJsCode(const uint8_t* buffer, int32_t size, const std::string& filePath = "") override;
    bool ExecuteJsBin(const std::string& fileName) override;
    shared_ptr<JsValue> GetGlobal() override;
    void RunGC() override;

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
    void RegisterUncaughtExceptionHandler(UncaughtExceptionCallback callback) override;
    void HandleUncaughtException() override;
    bool HasPendingException() override;
    void ExecutePendingJob() override;
    void DumpHeapSnapshot(bool isPrivate) override;

    const EcmaVM* GetEcmaVm() const
    {
        return vm_;
    }

    void SetDebuggerPostTask(DebuggerPostTask&& task)
    {
        debuggerPostTask_ = std::move(task);
    }

#if defined(PREVIEW)
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
        previewComponents_.insert_or_assign(componentName, componentObj);
    }

    panda::Global<panda::ObjectRef> GetPreviewComponent(EcmaVM* vm, const std::string &componentName)
    {
        auto iter = previewComponents_.find(componentName);
        if (iter != previewComponents_.end()) {
            return iter->second;
        }
        panda::Global<panda::ObjectRef> undefined(vm, panda::JSValueRef::Undefined(vm));
        return undefined;
    }

    void SetPathResolveCallback(const std::string& bundleName, const std::string& assetPath)
    {
        panda::JSNApi::SetHostResolvePathTracker(vm_, JsiModuleSearcher(bundleName, assetPath));
        panda::JSNApi::SetAssetPath(vm_, assetPath);
    }

    void SetBundle(bool isBundle)
    {
        panda::JSNApi::SetBundle(vm_, isBundle);
    }

    bool ExecuteModuleBuffer(const uint8_t *data, int32_t size, const std::string &filename);
#endif

private:
    EcmaVM* vm_ = nullptr;
    int32_t instanceId_ = 0;
    std::vector<PandaFunctionData*> dataList_;
    LOG_PRINT print_ { nullptr };
    UncaughtExceptionCallback uncaughtErrorHandler_ { nullptr };
    std::string libPath_ {};
    bool usingExistVM_ = false;
    bool isDebugMode_ = true;
    DebuggerPostTask debuggerPostTask_;
#if defined(PREVIEW)
    bool isComponentPreview_ = false;
    std::string requiredComponent_ {};
    std::unordered_map<std::string, panda::Global<panda::ObjectRef>> previewComponents_;
#endif
};

class PandaFunctionData {
public:
    PandaFunctionData(shared_ptr<ArkJSRuntime> runtime, RegisterFunctionType func)
        : runtime_(std::move(runtime)), func_(std::move(func))
    {}

    ~PandaFunctionData() = default;

    NO_COPY_SEMANTIC(PandaFunctionData);
    NO_MOVE_SEMANTIC(PandaFunctionData);

private:
    Local<JSValueRef> Callback(panda::JsiRuntimeCallInfo* info) const;
    shared_ptr<ArkJSRuntime> runtime_;
    RegisterFunctionType func_;
    friend Local<JSValueRef> FunctionCallback(panda::JsiRuntimeCallInfo* info);
};
} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ENGINE_JSI_ARK_JS_RUNTIME_H
