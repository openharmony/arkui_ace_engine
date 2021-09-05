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

#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_pan_function.h"

#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"

namespace OHOS::Ace::Framework {

v8::Local<v8::Object> V8PanFunction::createPanInfo(const TouchLocationInfo& info)
{
    auto context = isolate_->GetCurrentContext();
    v8::Local<v8::Object> panInfoObj = v8::Object::New(isolate_);
    const OHOS::Ace::Offset& globalLocation = info.GetGlobalLocation();
    const OHOS::Ace::Offset& localLocation = info.GetLocalLocation();
    panInfoObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "globalX").ToLocalChecked(),
              v8::Number::New(isolate_, globalLocation.GetX()))
        .ToChecked();
    panInfoObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "globalY").ToLocalChecked(),
              v8::Number::New(isolate_, globalLocation.GetY()))
        .ToChecked();
    panInfoObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "localX").ToLocalChecked(),
              v8::Number::New(isolate_, localLocation.GetX()))
        .ToChecked();
    panInfoObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "localY").ToLocalChecked(),
              v8::Number::New(isolate_, localLocation.GetY()))
        .ToChecked();
    return panInfoObj;
}

void V8PanFunction::execute(const DragStartInfo& info)
{
    LOGD("V8PanFunction: eventType[%s]", info.GetType().c_str());
    ACE_DCHECK(isolate_);
    v8::Isolate::Scope isolateScope(isolate_);
    v8::HandleScope handleScope(isolate_);
    auto context = ctx_.Get(isolate_);
    v8::Context::Scope contextScope(context);

    v8::Local<v8::Value> param = createPanInfo(static_cast<TouchLocationInfo>(info));
    V8Function::executeJS(1, &param);
}

void V8PanFunction::execute(const DragUpdateInfo& info)
{
    LOGD("V8PanFunction: eventType[%s]", info.GetType().c_str());
    ACE_DCHECK(isolate_);
    v8::Isolate::Scope isolateScope(isolate_);
    v8::HandleScope handleScope(isolate_);
    auto context = ctx_.Get(isolate_);
    v8::Context::Scope contextScope(context);

    v8::Local<v8::Object> paramObj = createPanInfo(static_cast<TouchLocationInfo>(info));
    const OHOS::Ace::Offset& deltaLocation = info.GetDelta();
    v8::Local<v8::Object> deltaInfoObj = v8::Object::New(isolate_);
    deltaInfoObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "x").ToLocalChecked(),
              v8::Number::New(isolate_, deltaLocation.GetX()))
        .ToChecked();
    deltaInfoObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "y").ToLocalChecked(),
              v8::Number::New(isolate_, deltaLocation.GetY()))
        .ToChecked();
    paramObj->Set(context, v8::String::NewFromUtf8(isolate_, "delta").ToLocalChecked(), deltaInfoObj).ToChecked();
    paramObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "mainDelta").ToLocalChecked(),
              v8::Number::New(isolate_, info.GetMainDelta()))
        .ToChecked();

    v8::Local<v8::Value> param = paramObj;
    V8Function::executeJS(1, &param);
}

void V8PanFunction::execute(const DragEndInfo& info)
{
    LOGD("V8PanFunction: eventType[%s]", info.GetType().c_str());
    ACE_DCHECK(isolate_);
    v8::Isolate::Scope isolateScope(isolate_);
    v8::HandleScope handleScope(isolate_);
    auto context = ctx_.Get(isolate_);
    v8::Context::Scope contextScope(context);

    v8::Local<v8::Object> paramObj = createPanInfo(static_cast<TouchLocationInfo>(info));
    const OHOS::Ace::Velocity& velocityLocation = info.GetVelocity();
    v8::Local<v8::Object> velocityInfoObj = v8::Object::New(isolate_);
    velocityInfoObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "x").ToLocalChecked(),
              v8::Number::New(isolate_, velocityLocation.GetVelocityX()))
        .ToChecked();
    velocityInfoObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "y").ToLocalChecked(),
              v8::Number::New(isolate_, velocityLocation.GetVelocityY()))
        .ToChecked();
    paramObj->Set(context, v8::String::NewFromUtf8(isolate_, "velocity").ToLocalChecked(), velocityInfoObj).ToChecked();
    paramObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "mainVelocity").ToLocalChecked(),
              v8::Number::New(isolate_, info.GetMainVelocity()))
        .ToChecked();

    v8::Local<v8::Value> param = paramObj;
    V8Function::executeJS(1, &param);
}

void V8PanFunction::execute()
{
    ACE_DCHECK(isolate_);
    v8::Isolate::Scope isolateScope(isolate_);
    v8::HandleScope handleScope(isolate_);
    auto context = ctx_.Get(isolate_);
    v8::Context::Scope contextScope(context);
    V8Function::executeJS();
}

} // namespace OHOS::Ace::Framework
