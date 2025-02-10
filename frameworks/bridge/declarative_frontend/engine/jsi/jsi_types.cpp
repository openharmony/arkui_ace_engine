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

#include "base/log/ace_performance_monitor.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_runtime.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"

namespace OHOS::Ace::Framework {

// -----------------------
// Implementation of JsiValue
// -----------------------
JsiValue::JsiValue(const panda::CopyableGlobal<panda::JSValueRef>& val) : JsiType(val) {}

JsiValue::JsiValue(panda::Local<panda::JSValueRef> val) : JsiType(val) {}

JsiValue::JsiValue(const EcmaVM *vm, panda::Local<panda::JSValueRef> val) : JsiType(vm, val) {}

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
        return GetHandle()->IsFunction(GetEcmaVM());
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
        return GetHandle()->IsString(GetEcmaVM());
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
        return GetHandle()->IsObject(GetEcmaVM());
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

bool JsiValue::IsArrayBuffer() const
{
    if (GetHandle().IsEmpty()) {
        return false;
    } else {
        return GetHandle()->IsArrayBuffer(GetEcmaVM());
    }
}

bool JsiValue::IsUint8ClampedArray() const
{
    return (!GetHandle().IsEmpty()) && (GetHandle()->IsUint8ClampedArray(GetEcmaVM()));
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
        return JSON::Stringify(vm, GetLocalHandle())->ToString(vm)->ToString(vm);
    }
    return GetHandle()->ToString(vm)->ToString(vm);
}

std::u16string JsiValue::ToU16String() const
{
    auto vm = GetEcmaVM();
    Local<StringRef> stringRef;
    panda::LocalScope scope(vm);
    if (IsObject()) {
        stringRef = JSON::Stringify(vm, GetLocalHandle())->ToString(vm);
    } else {
        stringRef = GetHandle()->ToString(vm);
    }
    auto utf16Len = stringRef->Length(vm);
    std::unique_ptr<char16_t[]> pBuf16 = std::make_unique<char16_t[]>(utf16Len);
    char16_t *buf16 = pBuf16.get();
    auto resultLen = stringRef->WriteUtf16(vm, buf16, utf16Len);
    return std::u16string(buf16, resultLen);
}

bool JsiValue::ToBoolean() const
{
    return GetHandle()->BooleaValue(GetEcmaVM());
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
JsiArray::JsiArray(const EcmaVM *vm, panda::Local<panda::ArrayRef> val) : JsiType(vm, val) {}

JsiRef<JsiValue> JsiArray::GetValueAt(size_t index) const
{
    return JsiRef<JsiValue>::FastMake(GetEcmaVM(), panda::ArrayRef::GetValueAt(GetEcmaVM(), GetLocalHandle(), index));
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
    auto func = JsiValue(vm, value);
    auto refValue =  JsiRef<JsiValue>(func);
    return refValue;
}

JsiRef<JsiValue> JsiArray::GetProperty(int32_t propertyIndex) const
{
    auto vm = GetEcmaVM();
    auto stringRef = panda::ExternalStringCache::GetCachedString(vm, propertyIndex);
    auto value = GetHandle()->Get(vm, stringRef);
    auto func = JsiValue(vm, value);
    auto refValue = JsiRef<JsiValue>(func);
    return refValue;
}

size_t JsiArray::Length() const
{
    size_t length = -1;
    JsiRef<JsiValue> propLength = GetProperty(static_cast<int32_t>(ArkUIIndex::LENGTH));
    if (propLength->IsNumber()) {
        length = propLength->ToNumber<int32_t>();
    }
    return length;
}

void JsiArray::SetLength(size_t length) const
{
    auto stringRef = panda::StringRef::NewFromUtf8(GetEcmaVM(), "length");
    GetHandle()->Set(GetEcmaVM(), stringRef, JsiValueConvertor::toJsiValueWithVM<size_t>(GetEcmaVM(), length));
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
    return GetHandle()->GetBuffer(GetEcmaVM());
}

void JsiArrayBuffer::Detach() const
{
    GetHandle()->Detach(GetEcmaVM());
}

bool JsiArrayBuffer::IsDetach() const
{
    return GetHandle()->IsDetach(GetEcmaVM());
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
JsiObject::JsiObject(const EcmaVM *vm, panda::Local<panda::ObjectRef> val) : JsiType(vm, val) {}

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

JsiRef<JsiValue> JsiObject::GetProperty(int32_t propertyIndex) const
{
    auto vm = GetEcmaVM();
    auto str = panda::ExternalStringCache::GetCachedString(vm, propertyIndex);
    auto value = GetHandle()->Get(vm, str);
    auto func = JsiValue(vm, value);
    auto refValue = JsiRef<JsiValue>(func);
    return refValue;
}

bool JsiObject::HasProperty(int32_t propertyIndex) const
{
    auto vm = GetEcmaVM();
    auto stringRef = panda::ExternalStringCache::GetCachedString(vm, propertyIndex);
    bool has = GetHandle()->Has(vm, stringRef);
    return has;
}

JsiRef<JsiValue> JsiObject::GetProperty(const char* prop) const
{
    auto vm = GetEcmaVM();
    auto stringRef = panda::StringRef::NewFromUtf8(vm, prop);
    auto value = GetHandle()->Get(vm, stringRef);
    auto func = JsiValue(vm, value);
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
    panda::TryCatch trycatch(vm);
    auto valueRef = JsiValueConvertor::toJsiValueWithVM<std::string>(vm, value);
    panda::Local<JSValueRef> result = JSON::Parse(vm, valueRef);
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (result.IsEmpty() || trycatch.HasCaught()) {
        runtime->HandleUncaughtException(trycatch);
        return JsiRef<JsiValue>::Make(JSValueRef::Undefined(vm));
    }

    return JsiRef<JsiValue>::Make(result);
}

void JsiObject::SetPropertyJsonObject(const char* prop, const char* value) const
{
    auto vm = GetEcmaVM();
    auto stringRef = panda::StringRef::NewFromUtf8(vm, prop);
    auto valueRef = JsiValueConvertor::toJsiValueWithVM<std::string>(GetEcmaVM(), value);
    if (valueRef->IsString(vm)) {
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
JsiFunction::JsiFunction(const panda::CopyableGlobal<panda::FunctionRef>& val) : JsiType(val) {}

JsiFunction::JsiFunction(panda::Local<panda::FunctionRef> val) : JsiType(val) {}

JsiFunction::JsiFunction(const EcmaVM *vm, panda::Local<panda::FunctionRef> val) : JsiType(vm, val) {}

JsiRef<JsiValue> JsiFunction::Call(JsiRef<JsiValue> thisVal, int argc, JsiRef<JsiValue> argv[]) const
{
    int32_t id = -1;
    if (SystemProperties::GetAcePerformanceMonitorEnabled()) {
        id = Container::CurrentId();
    }
    JS_CALLBACK_DURATION(id);
    auto vm = GetEcmaVM();
    panda::JsiFastNativeScope fastNativeScope(vm);
    LocalScope scope(vm);
    panda::TryCatch trycatch(vm);
    bool traceEnabled = false;
    if (SystemProperties::GetDebugEnabled()) {
        traceEnabled = AceTraceBeginWithArgs("ExecuteJS[%s]", GetHandle()->GetName(vm)->ToString(vm).c_str());
    }
    std::vector<panda::Local<panda::JSValueRef>> arguments;
    for (int i = 0; i < argc; ++i) {
        arguments.emplace_back(argv[i].Get().GetLocalHandle());
    }
    auto thisObj = thisVal.Get().GetLocalHandle();
    auto result = GetHandle()->Call(vm, thisObj, arguments.data(), argc);
    JSNApi::ExecutePendingJob(vm);
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (result.IsEmpty() || trycatch.HasCaught()) {
        runtime->HandleUncaughtException(trycatch);
        result = JSValueRef::Undefined(vm);
    }
    if (traceEnabled) {
        AceTraceEnd();
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
    GetHandle()->SetNativePointerFieldCount(GetEcmaVM(), count);
}

JsiRef<JsiObject> JsiObjTemplate::NewInstance() const
{
    auto instance = panda::ObjectRef::New(GetEcmaVM());
    instance->SetNativePointerFieldCount(GetEcmaVM(), 1);
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
    if (index < Length()) {
        return JsiRef<JsiValue>::FastMake(info_->GetVM(), info_->GetCallArgRef(index));
    }
    return JsiRef<JsiValue>::FastMake(info_->GetVM(), panda::JSValueRef::Undefined(info_->GetVM()));
}

JsiRef<JsiObject> JsiCallbackInfo::This() const
{
    auto obj = JsiObject { info_->GetVM(), info_->GetThisRef() };
    auto ref = JsiRef<JsiObject>(obj);
    return ref;
}

uint32_t JsiCallbackInfo::Length() const
{
    return info_->GetArgsNumber();
}

void JsiCallbackInfo::ReturnSelf() const
{
    panda::CopyableGlobal<panda::JSValueRef> thisObj(info_->GetVM(), info_->GetThisRef());
    retVal_ = thisObj;
}

bool JsiCallbackInfo::GetBooleanArg(size_t index, bool& value) const
{
    auto arg = info_->GetCallArgRef(index);
    if (arg.IsEmpty() || !arg->IsBoolean()) {
        return false;
    }
    value = arg->ToBoolean(info_->GetVM())->Value();
    return true;
}

bool JsiCallbackInfo::GetInt32Arg(size_t index, int32_t& value) const
{
    auto arg = info_->GetCallArgRef(index);
    if (arg.IsEmpty() || !arg->IsNumber()) {
        return false;
    }
    value = arg->Int32Value(info_->GetVM());
    return true;
}

bool JsiCallbackInfo::GetUint32Arg(size_t index, uint32_t& value) const
{
    auto arg = info_->GetCallArgRef(index);
    if (arg.IsEmpty() || !arg->IsNumber()) {
        return false;
    }
    value = arg->Uint32Value(info_->GetVM());
    return true;
}

bool JsiCallbackInfo::GetDoubleArg(size_t index, double& value, bool isJudgeSpecialValue) const
{
    auto arg = info_->GetCallArgRef(index);
    if (arg.IsEmpty()) {
        return false;
    }
    bool ret = false;
    value = arg->GetValueDouble(ret);
    if (isJudgeSpecialValue) {
        return (std::isnan(value) || std::isinf(value)) ? false : ret;
    }
    return ret;
}

bool JsiCallbackInfo::GetStringArg(size_t index, std::string& value) const
{
    auto arg = info_->GetCallArgRef(index);
    if (arg.IsEmpty() || !arg->IsString(info_->GetVM())) {
        return false;
    }
    value = arg->ToString(info_->GetVM())->ToString(info_->GetVM());
    return true;
}

bool JsiCallbackInfo::GetDoubleArrayArg(size_t index, std::vector<double>& valueArr) const
{
    auto arg = info_->GetCallArgRef(index);
    if (arg.IsEmpty() || !arg->IsArray(info_->GetVM())) {
        return false;
    }
    auto arrayRef = Local<ArrayRef>(arg);
    uint32_t length = arrayRef->Length(info_->GetVM());
    valueArr.reserve(length);
    for (uint32_t i = 0; i < length; ++i) {
        auto jsDouble = panda::ArrayRef::GetValueAt(info_->GetVM(), arrayRef, i);
        if (!jsDouble.IsEmpty() && jsDouble->IsNumber()) {
            valueArr.emplace_back(jsDouble->ToNumber(info_->GetVM())->Value());
        }
    }
    return true;
}

// -----------------------
// Implementation of JsiString
// -----------------------
JsiString::JsiString(const panda::CopyableGlobal<panda::StringRef>& val) : JsiType(val) {}
JsiString::JsiString(panda::Local<panda::StringRef> val) : JsiType(val) {}

panda::Local<panda::StringRef> JsiString::New(const char* str)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    return panda::StringRef::NewFromUtf8(runtime->GetEcmaVm(), str);
}

panda::Local<panda::StringRef> JsiString::New(const std::string& str)
{
    return JsiString::New(str.c_str());
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
