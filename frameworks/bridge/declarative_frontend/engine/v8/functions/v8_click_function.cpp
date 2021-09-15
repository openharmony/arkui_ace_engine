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

#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_click_function.h"

#include "base/log/log.h"
#include "core/gestures/click_recognizer.h"
#include "frameworks/bridge/declarative_frontend/engine/v8/v8_declarative_engine.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"

namespace OHOS::Ace::Framework {

void V8ClickFunction::execute()
{
    ACE_DCHECK(isolate_);
    v8::Isolate::Scope isolateScope(isolate_);
    v8::HandleScope handleScope(isolate_);
    auto context = ctx_.Get(isolate_);
    v8::Context::Scope contextScope(context);

    V8Function::executeJS();

    // This is required to request for new frame, which eventually will call
    // FlushBuild, FlushLayout and FlushRender on the dirty elements
    V8DeclarativeEngineInstance::TriggerPageUpdate();
}

void V8ClickFunction::execute(const ClickInfo& info)
{
    ACE_DCHECK(isolate_);
    v8::Isolate::Scope isolateScope(isolate_);
    v8::HandleScope handleScope(isolate_);
    auto context = ctx_.Get(isolate_);
    v8::Context::Scope contextScope(context);
    v8::Local<v8::Object> obj = v8::Object::New(isolate_);
    Offset globalOffset = info.GetGlobalLocation();
    Offset localOffset = info.GetLocalLocation();
    obj->Set(context, v8::String::NewFromUtf8(isolate_, "screenX").ToLocalChecked(),
        v8::Number::New(isolate_, globalOffset.GetX())).ToChecked();
    obj->Set(context, v8::String::NewFromUtf8(isolate_, "screenY").ToLocalChecked(),
        v8::Number::New(isolate_, globalOffset.GetY())).ToChecked();
    obj->Set(context, v8::String::NewFromUtf8(isolate_, "x").ToLocalChecked(),
        v8::Number::New(isolate_, localOffset.GetX())).ToChecked();
    obj->Set(context, v8::String::NewFromUtf8(isolate_, "y").ToLocalChecked(),
        v8::Number::New(isolate_, localOffset.GetY())).ToChecked();
    obj->Set(context, v8::String::NewFromUtf8(isolate_, "timestamp").ToLocalChecked(),
        v8::Number::New(isolate_, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())))
        .ToChecked();
    LOGD("globalOffset.GetX() = %lf, globalOffset.GetY() = %lf, localOffset.GetX() = %lf, localOffset.GetY() = %lf",
        globalOffset.GetX(), globalOffset.GetY(), localOffset.GetX(), localOffset.GetY());
    v8::Local<v8::Value> v8Param = obj;
    V8Function::executeJS(1, &v8Param);

    // This is required to request for new frame, which eventually will call
    // FlushBuild, FlushLayout and FlushRender on the dirty elements
    V8DeclarativeEngineInstance::TriggerPageUpdate();
}

} // namespace OHOS::Ace::Framework
