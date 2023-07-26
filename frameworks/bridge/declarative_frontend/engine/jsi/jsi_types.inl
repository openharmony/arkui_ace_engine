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

#include "frameworks/base/utils/string_utils.h"
#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_runtime.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_ref.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_types.h"

namespace OHOS::Ace::Framework {

template<typename T>
JsiType<T>::JsiType(panda::Local<T> val)
{
    if (!val.IsEmpty()) {
        auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
        handle_ = panda::CopyableGlobal(runtime->GetEcmaVm(), val);
    }
}

template<typename T>
template<typename S>
JsiType<T>::JsiType(panda::Local<S> val)
{
    if (!val.IsEmpty()) {
        auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
        handle_ = panda::CopyableGlobal(runtime->GetEcmaVm(), val);
    }
}

template<typename T>
JsiType<T>::JsiType(const panda::CopyableGlobal<T>& other) : handle_(other)
{
}

template<typename T>
JsiType<T>::JsiType(const JsiType<T>& rhs) : handle_(rhs.handle_)
{
}

template<typename T>
JsiType<T>::JsiType(JsiType<T>&& rhs) : handle_(std::move(rhs.handle_))
{
}

template<typename T>
JsiType<T>& JsiType<T>::operator=(const JsiType<T>& rhs)
{
    handle_ = rhs.handle_;
    return *this;
}

template<typename T>
JsiType<T>& JsiType<T>::operator=(JsiType<T>&& rhs)
{
    handle_ = std::move(rhs.handle_);
    return *this;
}

template<typename T>
void JsiType<T>::SetWeakCallback(void *ref, panda::WeakRefClearCallBack callback)
{
    if (!handle_.IsEmpty()) {
        handle_.SetWeakCallback(ref, callback, nullptr);
    }
}

template<typename T>
const EcmaVM* JsiType<T>::GetEcmaVM() const
{
    return handle_.GetEcmaVM();
}

template<typename T>
const panda::CopyableGlobal<T>& JsiType<T>::GetHandle() const
{
    return handle_;
}

template<typename T>
panda::Local<T> JsiType<T>::GetLocalHandle() const
{
    return handle_.ToLocal();
}

template<typename T>
bool JsiType<T>::IsEmpty() const
{
    return handle_.IsEmpty();
}

template<typename T>
bool JsiType<T>::IsWeak() const
{
    return handle_.IsWeak();
}

template<typename T>
void JsiType<T>::Reset()
{
    handle_.Reset();
}

template<typename T>
const panda::CopyableGlobal<T>& JsiType<T>::operator->() const
{
    return handle_;
}

template<typename T>
JsiType<T>::operator panda::CopyableGlobal<T>() const
{
    return handle_;
}

template<typename T>
template<class... Args>
JsiType<T> JsiType<T>::New(Args&&... args)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    return JsiType<T>(T::New(runtime->GetEcmaVm(), std::forward<Args>(args)...));
}

template<typename T>
T JsiValue::ToNumber() const
{
    return JsiValueConvertor::fromJsiValue<T>(GetEcmaVM(), GetLocalHandle());
}

template<typename T>
T* JsiObject::Unwrap() const
{
    if (GetHandle()->GetNativePointerFieldCount() < 1) {
        return nullptr;
    }
    return static_cast<T*>(GetHandle()->GetNativePointerField(INSTANCE));
}

template<typename T>
void JsiObject::Wrap(T* data) const
{
    GetHandle()->SetNativePointerField(INSTANCE, static_cast<void*>(data));
}

template<typename T>
void JsiObject::SetProperty(const char* prop, T value) const
{
    auto stringRef = panda::StringRef::NewFromUtf8(GetEcmaVM(), prop);
    GetHandle()->Set(GetEcmaVM(), stringRef, JsiValueConvertor::toJsiValueWithVM<T>(GetEcmaVM(), value));
}

template<typename T>
void JsiCallbackInfo::SetReturnValue(T* instance) const
{
    retVal_ = instance;
}

template<typename T>
void JsiCallbackInfo::SetReturnValue(JsiRef<T> val) const
{
    retVal_ = panda::CopyableGlobal<panda::JSValueRef>(val.Get().GetHandle());
}

template<typename... Args>
void JsiException::Throw(const char* format, Args... args)
{
    const std::string str = StringUtils::FormatString(format, args...);
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    auto vm = runtime->GetEcmaVm();
    panda::JSNApi::ThrowException(vm, panda::Exception::Error(vm, panda::StringRef::NewFromUtf8(vm, str.c_str())));
}

template<typename... Args>
void JsiException::ThrowRangeError(const char* format, Args... args)
{
    const std::string str = StringUtils::FormatString(format, args...);
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    auto vm = runtime->GetEcmaVm();
    panda::JSNApi::ThrowException(vm, panda::Exception::RangeError(vm, panda::StringRef::NewFromUtf8(vm, str.c_str())));
}

template<typename... Args>
void JsiException::ThrowReferenceError(const char* format, Args... args)
{
    const std::string str = StringUtils::FormatString(format, args...);
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    auto vm = runtime->GetEcmaVm();
    panda::JSNApi::ThrowException(
        vm, panda::Exception::ReferenceError(vm, panda::StringRef::NewFromUtf8(vm, str.c_str())));
}

template<typename... Args>
void JsiException::ThrowSyntaxError(const char* format, Args... args)
{
    const std::string str = StringUtils::FormatString(format, args...);
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    auto vm = runtime->GetEcmaVm();
    panda::JSNApi::ThrowException(
        vm, panda::Exception::SyntaxError(vm, panda::StringRef::NewFromUtf8(vm, str.c_str())));
}

template<typename... Args>
void JsiException::ThrowTypeError(const char* format, Args... args)
{
    const std::string str = StringUtils::FormatString(format, args...);
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    auto vm = runtime->GetEcmaVm();
    panda::JSNApi::ThrowException(vm, panda::Exception::TypeError(vm, panda::StringRef::NewFromUtf8(vm, str.c_str())));
}

template<typename... Args>
void JsiException::ThrowEvalError(const char* format, Args... args)
{
    const std::string str = StringUtils::FormatString(format, args...);
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    auto vm = runtime->GetEcmaVm();
    panda::JSNApi::ThrowException(vm, panda::Exception::EvalError(vm, panda::StringRef::NewFromUtf8(vm, str.c_str())));
}
} // namespace OHOS::Ace::Framework
