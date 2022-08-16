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

#include <iostream>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace OHOS::Ace::Framework {
int32_t ArkJSValue::ToInt32(shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    LocalScope scope(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime)) {
        return 0;
    }
    return value_->Int32Value(pandaRuntime->GetEcmaVm());
}

double ArkJSValue::ToDouble(shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    LocalScope scope(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime)) {
        return 0;
    }
    Local<NumberRef> number = value_->ToNumber(pandaRuntime->GetEcmaVm());
    if (!CheckException(pandaRuntime, number)) {
        return number->Value();
    }
    return 0;
}

std::string ArkJSValue::ToString(shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    LocalScope scope(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime)) {
        return "";
    }
    Local<StringRef> string = value_->ToString(pandaRuntime->GetEcmaVm());
    if (!CheckException(pandaRuntime, string)) {
        return string->ToString();
    }
    return "";
}

bool ArkJSValue::ToBoolean(shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    LocalScope scope(pandaRuntime->GetEcmaVm());
    return !CheckException(pandaRuntime) && value_->BooleaValue();
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
    return !value_.IsEmpty() && value_->IsString();
}

bool ArkJSValue::IsNumber([[maybe_unused]] shared_ptr<JsRuntime> runtime)
{
    return !value_.IsEmpty() && value_->IsNumber();
}

bool ArkJSValue::IsObject([[maybe_unused]] shared_ptr<JsRuntime> runtime)
{
    return !value_.IsEmpty() && value_->IsObject();
}

bool ArkJSValue::IsArray([[maybe_unused]] shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    return !value_.IsEmpty() && value_->IsArray(pandaRuntime->GetEcmaVm());
}

bool ArkJSValue::IsFunction([[maybe_unused]] shared_ptr<JsRuntime> runtime)
{
    return !value_.IsEmpty() && value_->IsFunction();
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
    JSExecutionScope executionScope(pandaRuntime->GetEcmaVm());
    LocalScope scope(pandaRuntime->GetEcmaVm());
    if (!IsFunction(pandaRuntime)) {
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(pandaRuntime->GetEcmaVm()));
    }
    std::vector<Local<JSValueRef>> arguments;
    arguments.reserve(argc);
    for (const shared_ptr<JsValue> &arg : argv) {
        arguments.emplace_back(std::static_pointer_cast<ArkJSValue>(arg)->GetValue(pandaRuntime));
    }
    Local<JSValueRef> thisValue = std::static_pointer_cast<ArkJSValue>(thisObj)->GetValue(pandaRuntime);
    Local<FunctionRef> function(GetValue(pandaRuntime));
    Local<JSValueRef> result = function->Call(pandaRuntime->GetEcmaVm(), thisValue, arguments.data(), argc);
    Local<ObjectRef> exception = JSNApi::GetUncaughtException(pandaRuntime->GetEcmaVm());
    pandaRuntime->HandleUncaughtException();
    if (!exception.IsEmpty() && !exception->IsHole()) {
        result = JSValueRef::Undefined(pandaRuntime->GetEcmaVm());
    }
    return std::make_shared<ArkJSValue>(pandaRuntime, result);
}

bool ArkJSValue::GetPropertyNames(shared_ptr<JsRuntime> runtime, shared_ptr<JsValue> &propName, int32_t &len)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    LocalScope scope(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime)) {
        return false;
    }
    Local<ObjectRef> obj = value_->ToObject(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime, obj)) {
        return false;
    }
    Local<ArrayRef> names = obj->GetOwnPropertyNames(pandaRuntime->GetEcmaVm());
    len = names->Length(pandaRuntime->GetEcmaVm());
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
    LocalScope scope(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime)) {
        return false;
    }
    Local<ObjectRef> obj = value_->ToObject(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime, obj)) {
        return false;
    }
    Local<ArrayRef> names = obj->GetOwnEnumerablePropertyNames(pandaRuntime->GetEcmaVm());
    len = names->Length(pandaRuntime->GetEcmaVm());
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
    LocalScope scope(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime)) {
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(pandaRuntime->GetEcmaVm()));
    }
    Local<ObjectRef> obj = value_->ToObject(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime, obj)) {
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(pandaRuntime->GetEcmaVm()));
    }
    Local<JSValueRef> property = obj->Get(pandaRuntime->GetEcmaVm(), idx);
    if (CheckException(pandaRuntime, property)) {
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(pandaRuntime->GetEcmaVm()));
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
    LocalScope scope(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime)) {
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(pandaRuntime->GetEcmaVm()));
    }
    Local<ObjectRef> obj = value_->ToObject(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime, obj)) {
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(pandaRuntime->GetEcmaVm()));
    }
    Local<JSValueRef> key = std::static_pointer_cast<ArkJSValue>(name)->GetValue(pandaRuntime);
    Local<JSValueRef> property = obj->Get(pandaRuntime->GetEcmaVm(), key);
    if (CheckException(pandaRuntime, property)) {
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(pandaRuntime->GetEcmaVm()));
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
    LocalScope scope(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime)) {
        return false;
    }
    Local<ObjectRef> obj = value_->ToObject(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime, obj)) {
        return false;
    }
    Local<JSValueRef> key = std::static_pointer_cast<ArkJSValue>(name)->GetValue(pandaRuntime);
    Local<JSValueRef> value_ref = std::static_pointer_cast<ArkJSValue>(value)->GetValue(pandaRuntime);
    return obj->Set(pandaRuntime->GetEcmaVm(), key, value_ref);
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
    LocalScope scope(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime)) {
        return false;
    }
    Local<ObjectRef> obj = value_->ToObject(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime, obj)) {
        return false;
    }
    Local<JSValueRef> key = std::static_pointer_cast<ArkJSValue>(name)->GetValue(pandaRuntime);
    Local<JSValueRef> getterValue = std::static_pointer_cast<ArkJSValue>(getter)->GetValue(pandaRuntime);
    Local<JSValueRef> setterValue = std::static_pointer_cast<ArkJSValue>(setter)->GetValue(pandaRuntime);
    return obj->SetAccessorProperty(pandaRuntime->GetEcmaVm(), key, getterValue, setterValue);
}

int32_t ArkJSValue::GetArrayLength(shared_ptr<JsRuntime> runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    LocalScope scope(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime)) {
        return -1;
    }
    Local<ArrayRef> array(GetValue(pandaRuntime));
    return array->Length(pandaRuntime->GetEcmaVm());
}

shared_ptr<JsValue> ArkJSValue::GetElement(shared_ptr<JsRuntime> runtime, int32_t idx)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    LocalScope scope(pandaRuntime->GetEcmaVm());
    if (CheckException(pandaRuntime)) {
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(pandaRuntime->GetEcmaVm()));
    }
    Local<ArrayRef> obj(GetValue(pandaRuntime));
    if (CheckException(pandaRuntime, obj)) {
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(pandaRuntime->GetEcmaVm()));
    }
    Local<JSValueRef> property = obj->Get(pandaRuntime->GetEcmaVm(), idx);
    if (CheckException(pandaRuntime, property)) {
        return std::make_shared<ArkJSValue>(pandaRuntime, JSValueRef::Undefined(pandaRuntime->GetEcmaVm()));
    }
    return std::make_shared<ArkJSValue>(pandaRuntime, property);
}

std::string ArkJSValue::GetJsonString(const shared_ptr<JsRuntime>& runtime)
{
    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    LocalScope scope(pandaRuntime->GetEcmaVm());
    auto stringify = panda::JSON::Stringify(pandaRuntime->GetEcmaVm(), GetValue(pandaRuntime));
    if (CheckException(pandaRuntime, stringify)) {
        return "";
    }
    auto valueStr = panda::Local<panda::StringRef>(stringify);
    if (CheckException(pandaRuntime, valueStr)) {
        return "";
    }
    return valueStr->ToString();
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