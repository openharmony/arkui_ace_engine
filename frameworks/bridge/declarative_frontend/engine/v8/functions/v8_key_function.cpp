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

#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_key_function.h"

#include "base/log/log.h"

namespace OHOS::Ace::Framework {

v8::Local<v8::Object> V8KeyFunction::createKeyEvent(const KeyEventInfo& event)
{
    auto context = isolate_->GetCurrentContext();
    v8::Local<v8::Object> keyEventObj = v8::Object::New(isolate_);
    keyEventObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "type").ToLocalChecked(),
              v8::Number::New(isolate_, event.GetKeyType()))
        .ToChecked();
    keyEventObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "keyCode").ToLocalChecked(),
              v8::Number::New(isolate_, static_cast<int32_t>(event.GetKeyCode())))
        .ToChecked();
    keyEventObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "keyText").ToLocalChecked(),
              v8::String::NewFromUtf8(isolate_, event.GetKeyText()).ToLocalChecked())
        .ToChecked();
    keyEventObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "keySource").ToLocalChecked(),
              v8::Number::New(isolate_, event.GetKeySource()))
        .ToChecked();
    keyEventObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "deviceId").ToLocalChecked(),
              v8::Number::New(isolate_, event.GetDeviceId()))
        .ToChecked();
    keyEventObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "metaKey").ToLocalChecked(),
              v8::Number::New(isolate_, event.GetMetaKey()))
        .ToChecked();
    keyEventObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "timestamp").ToLocalChecked(),
              v8::Number::New(isolate_, event.GetTimeStamp().time_since_epoch().count()))
        .ToChecked();
    return keyEventObj;
}

void V8KeyFunction::execute(const OHOS::Ace::KeyEventInfo& event)
{
    ACE_DCHECK(isolate_);
    v8::Isolate::Scope isolateScope(isolate_);
    v8::HandleScope handleScope(isolate_);
    auto context = ctx_.Get(isolate_);
    v8::Context::Scope contextScope(context);
    v8::Local<v8::Value> param = createKeyEvent(event);
    V8Function::executeJS(1, &param);
}

} // namespace OHOS::Ace::Framework
