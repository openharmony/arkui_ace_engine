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

#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_value.h"

// NOLINTNEXTLINE(readability-identifier-naming)
namespace OHOS::Ace::Framework {
int32_t ArkJSValue::ToInt32(shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    const EcmaVM* vm = pandaRuntime->GetEcmaVm();
    LocalScope scope(vm);
    if (CheckException(pandaRuntime)) {
        LOGE("ArkJSValue::ToInt32 occurs exception, return 0 directly");
        return 0;
    }
    return value_->Int32Value(vm);
}

double ArkJSValue::ToDouble(shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    const EcmaVM* vm = pandaRuntime->GetEcmaVm();
    LocalScope scope(vm);
    if (CheckException(pandaRuntime)) {
        LOGE("ArkJSValue::ToDouble occurs exception, return 0 directly");
        return 0;
    }
    Local<NumberRef> number = value_->ToNumber(vm);
    if (!CheckException(pandaRuntime, number)) {
        return number->Value();
    }
    LOGE("ArkJSValue::ToDouble occurs exception, return 0 directly");
    return 0;
}

std::string ArkJSValue::ToString(shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    const EcmaVM* vm = pandaRuntime->GetEcmaVm();
    LocalScope scope(vm);
    if (CheckException(pandaRuntime)) {
        LOGE("ArkJSValue::ToString occurs exception, return empty string directly");
        return "";
    }
    Local<StringRef> string = value_->ToString(vm);
    if (!CheckException(pandaRuntime, string)) {
        return string->ToString(vm);
    }
    LOGE("ArkJSValue::ToString occurs exception, return empty string directly");
    return "";
}

bool ArkJSValue::ToBoolean(shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    LocalScope scope(pandaRuntime->GetEcmaVm());
    if (!CheckException(pandaRuntime)) {
        return value_->BooleaValue(pandaRuntime->GetEcmaVm());
    }
    LOGE("ArkJSValue::ToBoolean occurs exception, return false directly");
    return false;
}

bool ArkJSValue::IsUndefined([[maybe_unused]] shared_ptr<JsRuntime> runtime)
{
    return !value_.IsEmpty() && value_->IsUndefined();
}

bool ArkJSValue::IsNull([[maybe_unused]] shared_ptr<JsRuntime> runtime)
{
    return !value_.IsEmpty() && value_->IsNull();
}

bool ArkJSValue::IsBoolean([[maybe_unused]] shared_ptr<JsRuntime> runtime)
{
    return !value_.IsEmpty() && value_->IsBoolean();
}

bool ArkJSValue::IsInt32([[maybe_unused]] shared_ptr<JsRuntime> runtime)
{
    return !value_.IsEmpty() && value_->IsInt();
}

bool ArkJSValue::WithinInt32([[maybe_unused]] shared_ptr<JsRuntime> runtime)
{
    return !value_.IsEmpty() && value_->WithinInt32();
}

bool ArkJSValue::IsString([[maybe_unused]] shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    return !value_.IsEmpty() && value_->IsString(pandaRuntime->GetEcmaVm());
}

bool ArkJSValue::IsNumber([[maybe_unused]] shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    return !value_.IsEmpty() && value_->IsNumber();
}

bool ArkJSValue::IsObject([[maybe_unused]] shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    return !value_.IsEmpty() && value_->IsObject(pandaRuntime->GetEcmaVm());
}

bool ArkJSValue::IsArray([[maybe_unused]] shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    return !value_.IsEmpty() && value_->IsArray(pandaRuntime->GetEcmaVm());
}

bool ArkJSValue::IsFunction([[maybe_unused]] shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    return !value_.IsEmpty() && value_->IsFunction(pandaRuntime->GetEcmaVm());
}

// NOLINTNEXTLINE(performance-unnecessary-value-param)
bool ArkJSValue::IsException([[maybe_unused]] shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    return value_.IsEmpty() || pandaRuntime->HasPendingException();
}

shared_ptr<JsValue> ArkJSValue::Call(shared_ptr<JsRuntime> runtime, shared_ptr<JsValue> thisObj,
                                     std::vector<shared_ptr<JsValue>> argv, int32_t argc)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    const EcmaVM* vm = pandaRuntime->GetEcmaVm();
    JSExecutionScope executionScope(vm);
    LocalScope scope(vm);
    panda::TryCatch trycatch(vm);
    if (!IsFunction(pandaRuntime)) {
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(vm));
    }
    std::vector<Local<JSValueRef>> arguments;
    arguments.reserve(argc);
    for (const shared_ptr<JsValue> &arg : argv) {
        arguments.emplace_back(std::static_pointer_cast<ArkJSValue>(arg)->GetValue(pandaRuntime));
    }
    Local<JSValueRef> thisValue = std::static_pointer_cast<ArkJSValue>(thisObj)->GetValue(pandaRuntime);
    Local<FunctionRef> function(GetValue(pandaRuntime));
    Local<JSValueRef> result = function->Call(vm, thisValue, arguments.data(), argc);
    bool hasCaught = trycatch.HasCaught();
    pandaRuntime->HandleUncaughtException(trycatch);
    if (hasCaught) {
        result = JSValueRef::Undefined(vm);
    }
    return std::make_shared<ArkJSValue>(pandaRuntime, result);
}

bool ArkJSValue::GetPropertyNames(shared_ptr<JsRuntime> runtime, shared_ptr<JsValue> &propName, int32_t &len)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    const EcmaVM* vm = pandaRuntime->GetEcmaVm();
    LocalScope scope(vm);
    if (CheckException(pandaRuntime)) {
        LOGE("ArkJSValue::GetPropertyNames occurs exception, return false directly");
        return false;
    }
    Local<ObjectRef> obj = value_->ToObject(vm);
    if (CheckException(pandaRuntime, obj)) {
        LOGE("ArkJSValue::GetPropertyNames occurs exception, return false directly");
        return false;
    }
    Local<ArrayRef> names = obj->GetOwnPropertyNames(vm);
    len = static_cast<int32_t>(names->Length(vm));
    if (!propName) {
        propName = std::make_shared<ArkJSValue>(pandaRuntime, names);
    } else {
        std::static_pointer_cast<ArkJSValue>(propName)->SetValue(pandaRuntime, names);
    }
    return true;
}

bool ArkJSValue::GetEnumerablePropertyNames(shared_ptr<JsRuntime> runtime, shared_ptr<JsValue> &propName, int32_t &len)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    const EcmaVM* vm = pandaRuntime->GetEcmaVm();
    LocalScope scope(vm);
    if (CheckException(pandaRuntime)) {
        LOGE("ArkJSValue::GetEnumerablePropertyNames occurs exception, return false directly");
        return false;
    }
    Local<ObjectRef> obj = value_->ToObject(vm);
    if (CheckException(pandaRuntime, obj)) {
        LOGE("ArkJSValue::GetEnumerablePropertyNames occurs exception, return false directly");
        return false;
    }
    Local<ArrayRef> names = obj->GetOwnEnumerablePropertyNames(vm);
    len = static_cast<int32_t>(names->Length(vm));
    if (!propName) {
        propName = std::make_shared<ArkJSValue>(pandaRuntime, names);
    } else {
        std::static_pointer_cast<ArkJSValue>(propName)->SetValue(pandaRuntime, names);
    }
    return true;
}

shared_ptr<JsValue> ArkJSValue::GetProperty(shared_ptr<JsRuntime> runtime, int32_t idx)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    const EcmaVM* vm = pandaRuntime->GetEcmaVm();
    LocalScope scope(vm);
    if (CheckException(pandaRuntime)) {
        LOGE("ArkJSValue::GetProperty occurs exception, return undefined directly");
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(vm));
    }
    Local<ObjectRef> obj = value_->ToObject(vm);
    if (CheckException(pandaRuntime, obj)) {
        LOGE("ArkJSValue::GetProperty occurs exception, return undefined directly");
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(vm));
    }
    Local<JSValueRef> property = obj->Get(vm, idx);
    if (CheckException(pandaRuntime, property)) {
        LOGE("ArkJSValue::GetProperty occurs exception, return undefined directly");
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(vm));
    }
    return std::make_shared<ArkJSValue>(pandaRuntime, property);
}

shared_ptr<JsValue> ArkJSValue::GetProperty(shared_ptr<JsRuntime> runtime, const std::string &name)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    LocalScope scope(pandaRuntime->GetEcmaVm());
    shared_ptr<JsValue> key = pandaRuntime->NewString(name);
    return GetProperty(runtime, key);
}

shared_ptr<JsValue> ArkJSValue::GetProperty(shared_ptr<JsRuntime> runtime, const shared_ptr<JsValue> &name)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    const EcmaVM* vm = pandaRuntime->GetEcmaVm();
    LocalScope scope(vm);
    if (CheckException(pandaRuntime)) {
        LOGE("ArkJSValue::GetProperty occurs exception, return undefined directly");
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(vm));
    }
    Local<ObjectRef> obj = value_->ToObject(vm);
    if (CheckException(pandaRuntime, obj)) {
        LOGE("ArkJSValue::GetProperty occurs exception, return undefined directly");
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(vm));
    }
    Local<JSValueRef> key = std::static_pointer_cast<ArkJSValue>(name)->GetValue(pandaRuntime);
    Local<JSValueRef> property = obj->Get(vm, key);
    if (CheckException(pandaRuntime, property)) {
        LOGE("ArkJSValue::GetProperty occurs exception, return undefined directly");
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(vm));
    }
    return std::make_shared<ArkJSValue>(pandaRuntime, property);
}

bool ArkJSValue::SetProperty(shared_ptr<JsRuntime> runtime, const std::string &name, const shared_ptr<JsValue> &value)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    LocalScope scope(pandaRuntime->GetEcmaVm());
    shared_ptr<JsValue> key = pandaRuntime->NewString(name);
    return SetProperty(runtime, key, value);
}

bool ArkJSValue::SetProperty(shared_ptr<JsRuntime> runtime, const shared_ptr<JsValue> &name,
                             const shared_ptr<JsValue> &value)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    const EcmaVM* vm = pandaRuntime->GetEcmaVm();
    LocalScope scope(vm);
    if (CheckException(pandaRuntime)) {
        LOGE("ArkJSValue::SetProperty occurs exception, return false directly");
        return false;
    }
    Local<ObjectRef> obj = value_->ToObject(vm);
    if (CheckException(pandaRuntime, obj)) {
        LOGE("ArkJSValue::SetProperty occurs exception, return false directly");
        return false;
    }
    Local<JSValueRef> key = std::static_pointer_cast<ArkJSValue>(name)->GetValue(pandaRuntime);
    Local<JSValueRef> value_ref = std::static_pointer_cast<ArkJSValue>(value)->GetValue(pandaRuntime);
    return obj->Set(vm, key, value_ref);
}

bool ArkJSValue::SetAccessorProperty(shared_ptr<JsRuntime> runtime, const std::string &name,
                                     const shared_ptr<JsValue> &getter, const shared_ptr<JsValue> &setter)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    LocalScope scope(pandaRuntime->GetEcmaVm());
    shared_ptr<JsValue> key = pandaRuntime->NewString(name);
    return SetAccessorProperty(runtime, key, getter, setter);
}

bool ArkJSValue::SetAccessorProperty(shared_ptr<JsRuntime> runtime, const shared_ptr<JsValue> &name,
                                     const shared_ptr<JsValue> &getter, const shared_ptr<JsValue> &setter)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    const EcmaVM* vm = pandaRuntime->GetEcmaVm();
    LocalScope scope(vm);
    if (CheckException(pandaRuntime)) {
        LOGE("ArkJSValue::SetAccessorProperty occurs exception, return false directly");
        return false;
    }
    Local<ObjectRef> obj = value_->ToObject(vm);
    if (CheckException(pandaRuntime, obj)) {
        LOGE("ArkJSValue::SetAccessorProperty occurs exception, return false directly");
        return false;
    }
    Local<JSValueRef> key = std::static_pointer_cast<ArkJSValue>(name)->GetValue(pandaRuntime);
    Local<JSValueRef> getterValue = std::static_pointer_cast<ArkJSValue>(getter)->GetValue(pandaRuntime);
    Local<JSValueRef> setterValue = std::static_pointer_cast<ArkJSValue>(setter)->GetValue(pandaRuntime);
    return obj->SetAccessorProperty(vm, key, getterValue, setterValue);
}

bool ArkJSValue::HasProperty(shared_ptr<JsRuntime> runtime, const std::string &name)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    LocalScope scope(pandaRuntime->GetEcmaVm());
    shared_ptr<JsValue> key = pandaRuntime->NewString(name);
    return HasProperty(runtime, key);
}

bool ArkJSValue::HasProperty(shared_ptr<JsRuntime> runtime, const shared_ptr<JsValue> &name)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    const EcmaVM* vm = pandaRuntime->GetEcmaVm();
    LocalScope scope(vm);
    if (CheckException(pandaRuntime)) {
        LOGE("ArkJSValue::HasProperty occurs exception, return false directly");
        return false;
    }
    Local<ObjectRef> obj = value_->ToObject(vm);
    if (CheckException(pandaRuntime, obj)) {
        LOGE("ArkJSValue::HasProperty occurs exception, return false directly");
        return false;
    }
    Local<JSValueRef> key = std::static_pointer_cast<ArkJSValue>(name)->GetValue(pandaRuntime);
    bool hasProperty = obj->Has(vm, key);
    if (CheckException(pandaRuntime)) {
        LOGE("ArkJSValue::HasProperty occurs exception, return false directly");
        return false;
    }
    return hasProperty;
}

int32_t ArkJSValue::GetArrayLength(shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    const EcmaVM* vm = pandaRuntime->GetEcmaVm();
    LocalScope scope(vm);
    if (CheckException(pandaRuntime)) {
        LOGE("ArkJSValue::GetArrayLength occurs exception, return -1 directly");
        return -1;
    }
    Local<ArrayRef> array(GetValue(pandaRuntime));
    return array->Length(vm);
}

shared_ptr<JsValue> ArkJSValue::GetElement(shared_ptr<JsRuntime> runtime, int32_t idx)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    const EcmaVM* vm = pandaRuntime->GetEcmaVm();
    LocalScope scope(vm);
    if (CheckException(pandaRuntime)) {
        LOGE("ArkJSValue::GetElement occurs exception, return undefined directly");
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(vm));
    }
    Local<ArrayRef> obj(GetValue(pandaRuntime));
    if (CheckException(pandaRuntime, obj)) {
        LOGE("ArkJSValue::GetElement occurs exception, return undefined directly");
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(vm));
    }
    Local<JSValueRef> property = obj->Get(vm, idx);
    if (CheckException(pandaRuntime, property)) {
        LOGE("ArkJSValue::GetElement occurs exception, return undefined directly");
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(vm));
    }
    return std::make_shared<ArkJSValue>(pandaRuntime, property);
}

std::string ArkJSValue::GetJsonString(const shared_ptr<JsRuntime>& runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    const EcmaVM* vm = pandaRuntime->GetEcmaVm();
    LocalScope scope(vm);
    auto stringify = panda::JSON::Stringify(vm, GetValue(pandaRuntime));
    if (CheckException(pandaRuntime, stringify)) {
        LOGE("ArkJSValue::GetJsonString occurs exception, return empty string directly");
        return "";
    }
    auto valueStr = panda::Local<panda::StringRef>(stringify);
    if (CheckException(pandaRuntime, valueStr)) {
        LOGE("ArkJSValue::GetJsonString occurs exception, return empty string directly");
        return "";
    }
    return valueStr->ToString(pandaRuntime->GetEcmaVm());
}

bool ArkJSValue::CheckException(const shared_ptr<ArkJSRuntime> &runtime) const
{
    return value_.IsEmpty() || runtime->HasPendingException();
}

bool ArkJSValue::CheckException(const shared_ptr<ArkJSRuntime> &runtime, const Local<JSValueRef> &value) const
{
    return value.IsEmpty() || runtime->HasPendingException();
}
}  // namespace OHOS::Ace::Framework
