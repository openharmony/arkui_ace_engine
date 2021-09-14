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

#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_types.h"

#include "frameworks/bridge/declarative_frontend/engine/jsi/ark/ark_js_runtime.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"

namespace OHOS::Ace::Framework {

// -----------------------
// Implementation of JsiValue
// -----------------------
JsiValue::JsiValue(panda::Local<panda::JSValueRef> val) : JsiType(val) {}

bool JsiValue::IsEmpty() const
{
    return GetHandle().IsEmpty();
}

bool JsiValue::IsFunction() const
{
    return GetHandle()->IsFunction();
}

bool JsiValue::IsNumber() const
{
    return GetHandle()->IsNumber();
}

bool JsiValue::IsString() const
{
    return GetHandle()->IsString();
}

bool JsiValue::IsBoolean() const
{
    return GetHandle()->IsBoolean();
}

bool JsiValue::IsObject() const
{
    return GetHandle()->IsObject();
}

bool JsiValue::IsArray() const
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    return GetHandle()->IsArray(runtime->GetEcmaVm());
}

bool JsiValue::IsUndefined() const
{
    return GetHandle()->IsUndefined();
}

bool JsiValue::IsNull() const
{
    return GetHandle()->IsNull();
}

std::string JsiValue::ToString() const
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    panda::LocalScope scope(runtime->GetEcmaVm());
    return GetHandle()->ToString(runtime->GetEcmaVm())->ToString();
}

bool JsiValue::ToBoolean() const
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    return GetHandle()->BooleaValue();
}

// -----------------------
// Implementation of JsiArray
// -----------------------
JsiArray::JsiArray() {}
JsiArray::JsiArray(panda::Local<panda::ArrayRef> val) : JsiType(val) {}

JsiRef<JsiValue> JsiArray::GetValueAt(size_t index) const
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    return JsiRef<JsiValue>::Make(panda::ArrayRef::GetValueAt(runtime->GetEcmaVm(), GetHandle(), index));
}

void JsiArray::SetValueAt(size_t index, JsiRef<JsiValue> value) const
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    panda::ArrayRef::SetValueAt(runtime->GetEcmaVm(), GetHandle(), index, value.Get().GetHandle());
}

size_t JsiArray::Length() const
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    return GetHandle()->Length(runtime->GetEcmaVm());
}

// -----------------------
// Implementation of JsiObject
// -----------------------
JsiObject::JsiObject() : JsiType() {}
JsiObject::JsiObject(panda::Local<panda::ObjectRef> val) : JsiType(val) {}

JsiRef<JsiArray> JsiObject::GetPropertyNames() const
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    return JsiRef<JsiArray>::Make(GetHandle()->GetOwnPropertyNames(runtime->GetEcmaVm()));
}

JsiRef<JsiValue> JsiObject::GetProperty(const char* prop) const
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    auto stringRef = panda::StringRef::NewFromUtf8(runtime->GetEcmaVm(), prop);
    return JsiRef<JsiValue>::Make(GetHandle()->Get(runtime->GetEcmaVm(), stringRef));
}

void JsiObject::SetPropertyJsonObject(const char* prop, const char* value) const
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    auto vm = runtime->GetEcmaVm();
    auto stringRef = panda::StringRef::NewFromUtf8(vm, prop);
    auto valueRef = JsiValueConvertor::toJsiValue<std::string>(value);
    if (valueRef->IsString()) {
        GetHandle()->Set(vm, stringRef, JSON::Parse(vm, valueRef));
    }
}

void JsiObject::SetPropertyObject(const char* prop, JsiRef<JsiValue> value) const
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    auto vm = runtime->GetEcmaVm();
    auto stringRef = panda::StringRef::NewFromUtf8(vm, prop);
    GetHandle()->Set(vm, stringRef, value.Get().GetHandle());
}

// -----------------------
// Implementation of JsiFunction
// -----------------------
JsiFunction::JsiFunction() {}
JsiFunction::JsiFunction(panda::Local<panda::FunctionRef> val) : JsiType(val)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    vm_ = runtime->GetEcmaVm();
}

JsiRef<JsiValue> JsiFunction::Call(JsiRef<JsiValue> thisVal, int argc, JsiRef<JsiValue> argv[]) const
{
    panda::LocalScope scope(vm_);
    std::vector<panda::Local<panda::JSValueRef>> arguments;
    for (int i = 0; i < argc; ++i) {
        arguments.emplace_back(argv[i].Get().GetHandle());
    }
    auto thisObj = thisVal.Get().GetHandle();
    auto result = GetHandle()->Call(vm_, thisObj, arguments.data(), argc);
    return JsiRef<JsiValue>::Make(result);
}

panda::Local<panda::FunctionRef> JsiFunction::New(JsiFunctionCallback func)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    return panda::FunctionRef::New(runtime->GetEcmaVm(), func, nullptr);
}

// -----------------------
// Implementation of JsiObjectTemplate
// -----------------------
JsiObjTemplate::JsiObjTemplate(panda::Local<panda::ObjectRef> val) : JsiObject(val) {}

void JsiObjTemplate::SetInternalFieldCount(int32_t count) const
{
    GetHandle()->SetNativePointerFieldCount(count);
}

JsiRef<JsiObject> JsiObjTemplate::NewInstance() const
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    return JsiRef<JsiObject>::Make(panda::ObjectRef::New(runtime->GetEcmaVm()));
}

panda::Local<panda::JSValueRef> JsiObjTemplate::New()
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    return panda::JSValueRef::Undefined(runtime->GetEcmaVm());
}

// -----------------------
// Implementation of JsiCallBackInfo
// -----------------------
JsiCallbackInfo::JsiCallbackInfo(panda::ecmascript::EcmaVM* vm, panda::Local<panda::JSValueRef> thisObj, int32_t argc,
    const panda::Local<panda::JSValueRef>* argv)
    : vm_(vm), thisObj_(thisObj), argc_(argc), argv_(const_cast<panda::Local<panda::JSValueRef>*>(argv))
{}

JsiRef<JsiValue> JsiCallbackInfo::operator[](size_t index) const
{
    return JsiRef<JsiValue>::Make(argv_[index]);
}

JsiRef<JsiObject> JsiCallbackInfo::This() const
{
    return JsiRef<JsiObject>::Make(thisObj_);
}

int JsiCallbackInfo::Length() const
{
    return argc_;
}

void JsiCallbackInfo::ReturnSelf() const
{
    retVal_ = thisObj_;
}

} // namespace OHOS::Ace::Framework
