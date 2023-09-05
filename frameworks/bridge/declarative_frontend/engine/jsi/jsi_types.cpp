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

#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_types.h"

#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_runtime.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"

namespace OHOS::Ace::Framework {

// -----------------------
// Implementation of JsiValue
// -----------------------
JsiValue::JsiValue(const panda::CopyableGlobal<panda::JSValueRef>& val) : JsiType(val) {}

JsiValue::JsiValue(panda::Local<panda::JSValueRef> val) : JsiType(val) {}

bool JsiValue::IsEmpty() const
{
    if (GetHandle().IsEmpty()) {
        return true;
    }
    return GetHandle()->IsUndefined() || GetHandle()->IsNull();
}

bool JsiValue::IsFunction() const
{
    if (GetHandle().IsEmpty()) {
        return false;
    } else {
        return GetHandle()->IsFunction();
    }
}

bool JsiValue::IsNumber() const
{
    if (GetHandle().IsEmpty()) {
        return false;
    } else {
        return GetHandle()->IsNumber();
    }
}

bool JsiValue::IsString() const
{
    if (GetHandle().IsEmpty()) {
        return false;
    } else {
        return GetHandle()->IsString();
    }
}

bool JsiValue::IsBoolean() const
{
    if (GetHandle().IsEmpty()) {
        return false;
    } else {
        return GetHandle()->IsBoolean();
    }
}

bool JsiValue::IsObject() const
{
    if (GetHandle().IsEmpty()) {
        return false;
    } else {
        return GetHandle()->IsObject();
    }
}

bool JsiValue::IsArray() const
{
    if (GetHandle().IsEmpty()) {
        return false;
    } else {
        return GetHandle()->IsArray(GetEcmaVM());
    }
}

bool JsiValue::IsUint8ClampedArray() const
{
    return (!GetHandle().IsEmpty()) && (GetHandle()->IsUint8ClampedArray());
}

bool JsiValue::IsUndefined() const
{
    if (GetHandle().IsEmpty()) {
        return true;
    } else {
        return GetHandle()->IsUndefined();
    }
}

bool JsiValue::IsNull() const
{
    if (GetHandle().IsEmpty()) {
        return true;
    } else {
        return GetHandle()->IsNull();
    }
}

std::string JsiValue::ToString() const
{
    auto vm = GetEcmaVM();
    panda::LocalScope scope(vm);
    if (IsObject()) {
        return JSON::Stringify(vm, GetLocalHandle())->ToString(vm)->ToString();
    }
    return GetHandle()->ToString(vm)->ToString();
}

bool JsiValue::ToBoolean() const
{
    return GetHandle()->BooleaValue();
}

JsiRef<JsiValue> JsiValue::Undefined()
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    return JsiRef<JsiValue>::Make(panda::JSValueRef::Undefined(runtime->GetEcmaVm()));
}

JsiRef<JsiValue> JsiValue::Null()
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    return JsiRef<JsiValue>::Make(panda::JSValueRef::Null(runtime->GetEcmaVm()));
}

JsiRef<JsiValue> JsiValue::True()
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    return JsiRef<JsiValue>::Make(panda::JSValueRef::True(runtime->GetEcmaVm()));
}

JsiRef<JsiValue> JsiValue::False()
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    return JsiRef<JsiValue>::Make(panda::JSValueRef::False(runtime->GetEcmaVm()));
}

// -----------------------
// Implementation of JsiArray
// -----------------------
JsiArray::JsiArray() {}
JsiArray::JsiArray(const panda::CopyableGlobal<panda::ArrayRef>& val) : JsiType(val) {}
JsiArray::JsiArray(panda::Local<panda::ArrayRef> val) : JsiType(val) {}

JsiRef<JsiValue> JsiArray::GetValueAt(size_t index) const
{
    return JsiRef<JsiValue>::Make(panda::ArrayRef::GetValueAt(GetEcmaVM(), GetLocalHandle(), index));
}

void JsiArray::SetValueAt(size_t index, JsiRef<JsiValue> value) const
{
    panda::ArrayRef::SetValueAt(GetEcmaVM(), GetLocalHandle(), index, value.Get().GetLocalHandle());
}

JsiRef<JsiValue> JsiArray::GetProperty(const char* prop) const
{
    auto vm = GetEcmaVM();
    auto stringRef = panda::StringRef::NewFromUtf8(vm, prop);
    auto value = GetHandle()->Get(vm, stringRef);
    auto func = JsiValue(value);
    auto refValue =  JsiRef<JsiValue>(func);
    return refValue;
}

size_t JsiArray::Length() const
{
    size_t length = -1;
    JsiRef<JsiValue> propLength = GetProperty("length");
    if (propLength->IsNumber()) {
        length = propLength->ToNumber<int32_t>();
    }
    return length;
}

bool JsiArray::IsArray() const
{
    if (GetHandle().IsEmpty()) {
        return false;
    } else {
        return GetHandle()->IsArray(GetEcmaVM());
    }
}

// -----------------------
// Implementation of JsiArrayBuffer
// -----------------------
JsiArrayBuffer::JsiArrayBuffer(panda::Local<panda::ArrayBufferRef> val) : JsiType(val) {}
JsiArrayBuffer::JsiArrayBuffer(const panda::CopyableGlobal<panda::ArrayBufferRef>& val) : JsiType(val) {}

int32_t JsiArrayBuffer::ByteLength() const
{
    return GetHandle()->ByteLength(GetEcmaVM());
}

void* JsiArrayBuffer::GetBuffer() const
{
    return GetHandle()->GetBuffer();
}

void JsiArrayBuffer::Detach() const
{
    GetHandle()->Detach(GetEcmaVM());
}

bool JsiArrayBuffer::IsDetach() const
{
    return GetHandle()->IsDetach();
}

// -----------------------
// Implementation of JsiArrayBufferRef
// -----------------------
JsiUint8ClampedArray::JsiUint8ClampedArray(panda::Local<panda::Uint8ClampedArrayRef> val) : JsiType(val) {}
JsiUint8ClampedArray::JsiUint8ClampedArray(const panda::CopyableGlobal<panda::Uint8ClampedArrayRef>& val) : JsiType(val)
{}

JsiRef<JsiArrayBuffer> JsiUint8ClampedArray::GetArrayBuffer() const
{
    return JsiRef<JsiArrayBuffer>(JsiArrayBuffer(GetHandle()->GetArrayBuffer(GetEcmaVM())));
}

// -----------------------
// Implementation of JsiObject
// -----------------------
JsiObject::JsiObject() : JsiType() {}
JsiObject::JsiObject(const panda::CopyableGlobal<panda::ObjectRef>& val) : JsiType(val) {}
JsiObject::JsiObject(panda::Local<panda::ObjectRef> val) : JsiType(val) {}

bool JsiObject::IsUndefined() const
{
    if (GetHandle().IsEmpty()) {
        return true;
    } else {
        return GetHandle()->IsUndefined();
    }
}

JsiRef<JsiArray> JsiObject::GetPropertyNames() const
{
    auto vm = GetEcmaVM();
    return JsiRef<JsiArray>::Make(GetHandle()->GetOwnPropertyNames(vm));
}

JsiRef<JsiValue> JsiObject::GetProperty(const char* prop) const
{
    auto vm = GetEcmaVM();
    auto stringRef = panda::StringRef::NewFromUtf8(vm, prop);
    auto value = GetHandle()->Get(vm, stringRef);
    auto func = JsiValue(value);
    auto refValue =  JsiRef<JsiValue>(func);
    return refValue;
}

bool JsiObject::HasProperty(const char* prop) const
{
    auto vm = GetEcmaVM();
    auto stringRef = panda::StringRef::NewFromUtf8(vm, prop);
    bool has = GetHandle()->Has(vm, stringRef);
    return has;
}

JsiRef<JsiValue> JsiObject::ToJsonObject(const char* value) const
{
    auto vm = GetEcmaVM();
    auto valueRef = JsiValueConvertor::toJsiValueWithVM<std::string>(vm, value);
    panda::Local<JSValueRef> result = JSON::Parse(vm, valueRef);
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (result.IsEmpty() || runtime->HasPendingException()) {
        runtime->HandleUncaughtException();
        return JsiRef<JsiValue>::Make(JSValueRef::Undefined(vm));
    }

    return JsiRef<JsiValue>::Make(result);
}

void JsiObject::SetPropertyJsonObject(const char* prop, const char* value) const
{
    auto vm = GetEcmaVM();
    auto stringRef = panda::StringRef::NewFromUtf8(vm, prop);
    auto valueRef = JsiValueConvertor::toJsiValueWithVM<std::string>(GetEcmaVM(), value);
    if (valueRef->IsString()) {
        GetHandle()->Set(vm, stringRef, JSON::Parse(vm, valueRef));
    }
}

void JsiObject::SetPropertyObject(const char* prop, JsiRef<JsiValue> value) const
{
    auto vm = GetEcmaVM();
    auto stringRef = panda::StringRef::NewFromUtf8(vm, prop);
    GetHandle()->Set(vm, stringRef, value.Get().GetLocalHandle());
}

// -----------------------
// Implementation of JsiFunction
// -----------------------
JsiFunction::JsiFunction() {}
JsiFunction::JsiFunction(const panda::CopyableGlobal<panda::FunctionRef>& val) : JsiType(val)
{
}

JsiFunction::JsiFunction(panda::Local<panda::FunctionRef> val) : JsiType(val)
{
}

JsiRef<JsiValue> JsiFunction::Call(JsiRef<JsiValue> thisVal, int argc, JsiRef<JsiValue> argv[]) const
{
    auto vm = GetEcmaVM();
    LocalScope scope(vm);
    std::vector<panda::Local<panda::JSValueRef>> arguments;
    for (int i = 0; i < argc; ++i) {
        arguments.emplace_back(argv[i].Get().GetLocalHandle());
    }
    auto thisObj = thisVal.Get().GetLocalHandle();
    auto result = GetHandle()->Call(vm, thisObj, arguments.data(), argc);
    JSNApi::ExecutePendingJob(vm);
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (result.IsEmpty() || runtime->HasPendingException()) {
        runtime->HandleUncaughtException();
        result = JSValueRef::Undefined(vm);
    }
    return JsiRef<JsiValue>::Make(result);
}

panda::Local<panda::FunctionRef> JsiFunction::New(JsiFunctionCallback func)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    return panda::FunctionRef::New(const_cast<EcmaVM*>(runtime->GetEcmaVm()), func);
}

// -----------------------
// Implementation of JsiObjectTemplate
// -----------------------
JsiObjTemplate::JsiObjTemplate(const panda::CopyableGlobal<panda::ObjectRef>& val) : JsiObject(val) {}
JsiObjTemplate::JsiObjTemplate(panda::Local<panda::ObjectRef> val) : JsiObject(val) {}

void JsiObjTemplate::SetInternalFieldCount(int32_t count) const
{
    GetHandle()->SetNativePointerFieldCount(count);
}

JsiRef<JsiObject> JsiObjTemplate::NewInstance() const
{
    auto instance = panda::ObjectRef::New(GetEcmaVM());
    instance->SetNativePointerFieldCount(1);
    return JsiRef<JsiObject>::Make(instance);
}

panda::Local<panda::JSValueRef> JsiObjTemplate::New()
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    return panda::ObjectRef::New(runtime->GetEcmaVm());
}

// -----------------------
// Implementation of JsiCallBackInfo
// -----------------------
JsiCallbackInfo::JsiCallbackInfo(panda::JsiRuntimeCallInfo* info) : info_(info) {}

JsiRef<JsiValue> JsiCallbackInfo::operator[](size_t index) const
{
    if (static_cast<int32_t>(index) < Length()) {
        return JsiRef<JsiValue>::Make(info_->GetCallArgRef(index));
    }
    return JsiRef<JsiValue>::Make(panda::JSValueRef::Undefined(info_->GetVM()));
}

JsiRef<JsiObject> JsiCallbackInfo::This() const
{
    auto obj = JsiObject { info_->GetThisRef() };
    auto ref = JsiRef<JsiObject>(obj);
    return ref;
}

int JsiCallbackInfo::Length() const
{
    return info_->GetArgsNumber();
}

void JsiCallbackInfo::ReturnSelf() const
{
    panda::CopyableGlobal<panda::JSValueRef> thisObj(info_->GetVM(), info_->GetThisRef());
    retVal_ = thisObj;
}

// -----------------------
// Implementation of JsiString
// -----------------------
JsiString::JsiString(const char* str) : JsiValue(StringRef::NewFromUtf8(GetEcmaVM(), str)) {}
JsiString::JsiString(JsiValue str) : JsiValue(str) {}

JsiString JsiString::New(const char* str)
{
    return JsiString(str);
}

// -----------------------
// Implementation of JsiDate
// -----------------------
JsiDate::JsiDate(const panda::CopyableGlobal<panda::DateRef>& val) : JsiType(val) {}
JsiDate::JsiDate(panda::Local<panda::DateRef> val) : JsiType(val) {}

JsiRef<JsiValue> JsiDate::New(double value)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    return JsiRef<JsiValue>::Make(panda::DateRef::New(runtime->GetEcmaVm(), value));
}

} // namespace OHOS::Ace::Framework
