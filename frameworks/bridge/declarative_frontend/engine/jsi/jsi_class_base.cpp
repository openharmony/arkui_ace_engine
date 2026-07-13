/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "jsi_class_base.h"

#include <memory>
#include <unordered_set>

namespace OHOS::Ace::Framework {

namespace {
#ifdef CROSS_PLATFORM
std::unordered_set<JsiClassBase::UnDeclareFunc>& GetUnDeclareRegistry()
{
    static thread_local std::unordered_set<JsiClassBase::UnDeclareFunc> registry;
    return registry;
}
#endif
} // namespace

void JsiClassBase::RegisterUnDeclare(UnDeclareFunc func)
{
#ifdef CROSS_PLATFORM
    if (func == nullptr) {
        return;
    }
    GetUnDeclareRegistry().insert(func);
#endif
}

void JsiClassBase::UnDeclareAll()
{
#ifdef CROSS_PLATFORM
    for (const auto& func : GetUnDeclareRegistry()) {
        if (func != nullptr) {
            func();
        }
    }
#endif
}

void JsiClassBase::DeclareImpl(const char* name, std::string& className,
    JsiFunctionMap& staticFns, JsiFunctionMap& customFns,
    JsiFunctionMap& customGetFns, JsiFunctionMap& customSetFns,
    panda::Global<panda::FunctionRef>& classFn)
{
    className = name;
    for (auto& entry : staticFns) {
        entry.second.FreeGlobalHandleAddr();
    }
    staticFns.clear();
    for (auto& entry : customFns) {
        entry.second.FreeGlobalHandleAddr();
    }
    customFns.clear();
    for (auto& entry : customGetFns) {
        entry.second.FreeGlobalHandleAddr();
    }
    customGetFns.clear();
    for (auto& entry : customSetFns) {
        entry.second.FreeGlobalHandleAddr();
    }
    customSetFns.clear();
    classFn.FreeGlobalHandleAddr();
    classFn.Empty();
}

void JsiClassBase::AddStaticMethodJSImpl(const char* name,
    StaticFunctionBinding<void, const JSCallbackInfo&>* binding,
    JsiFunctionMap& staticFns, FunctionCallback nativeCallback)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    auto vm = const_cast<EcmaVM*>(runtime->GetEcmaVm());
    staticFns.emplace(name,
        panda::Global<panda::FunctionRef>(
            vm, panda::FunctionRef::New(vm, nativeCallback, nullptr, (void*)binding)));
}

void JsiClassBase::AddCustomMethodImpl(const char* name,
    FunctionCallback callback, JsiFunctionMap& customFns)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    auto vm = const_cast<EcmaVM*>(runtime->GetEcmaVm());
    customFns.emplace(name, panda::Global<panda::FunctionRef>(vm, panda::FunctionRef::New(vm, callback)));
}

void JsiClassBase::AddCustomStaticMethodImpl(const char* name,
    FunctionCallback callback, JsiFunctionMap& staticFns)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    auto vm = const_cast<EcmaVM*>(runtime->GetEcmaVm());
    staticFns.emplace(name, panda::Global<panda::FunctionRef>(vm, panda::FunctionRef::New(vm, callback)));
}

void JsiClassBase::BindImpl(BindingTarget t, const char* jsName, const std::string& classDisplayName,
    FunctionCallback classNativeCallback, JsiFunctionMap& staticFns, JsiFunctionMap& customFns,
    JsiFunctionMap& customGetFns, JsiFunctionMap& customSetFns,
    panda::Global<panda::FunctionRef>& classFn)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    auto vm = const_cast<EcmaVM*>(runtime->GetEcmaVm());
    panda::LocalScope scope(vm);
    classFn = panda::Global<panda::FunctionRef>(
        vm, panda::FunctionRef::NewClassFunction(vm, classNativeCallback, nullptr, nullptr));
    classFn->SetName(vm, panda::StringRef::NewFromUtf8(vm, classDisplayName.c_str()));
    auto prototype = panda::Local<panda::ObjectRef>(classFn->GetFunctionPrototype(vm));
    prototype->Set(vm, panda::StringRef::NewFromUtf8(vm, "constructor"),
        panda::Local<panda::JSValueRef>(classFn.ToLocal()));
    for (const auto& [fnName, val] : staticFns) {
        classFn->Set(vm, panda::StringRef::NewFromUtf8(vm, fnName.c_str()), val.ToLocal());
    }
    for (const auto& [fnName, val] : customFns) {
        prototype->Set(vm, panda::StringRef::NewFromUtf8(vm, fnName.c_str()), val.ToLocal());
    }

    for (const auto& [nameGet, valGet] : customGetFns) {
        for (const auto& [nameSet, valSet] : customSetFns) {
            if (nameGet == nameSet) {
                prototype->SetAccessorProperty(
                    vm, panda::StringRef::NewFromUtf8(vm, nameGet.c_str()), valGet.ToLocal(), valSet.ToLocal());
            }
        }
    }

    t->Set(vm, panda::StringRef::NewFromUtf8(vm, jsName),
        panda::Local<panda::JSValueRef>(classFn.ToLocal()));
}
} // namespace OHOS::Ace::Framework
