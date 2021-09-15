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

#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_gesture_function.h"

#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/engine/v8/v8_declarative_engine.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"

namespace OHOS::Ace::Framework {

void V8GestureFunction::execute()
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

void V8GestureFunction::execute(const GestureEvent& info)
{
    ACE_DCHECK(isolate_);
    v8::Isolate::Scope isolateScope(isolate_);
    v8::HandleScope handleScope(isolate_);
    auto context = ctx_.Get(isolate_);
    v8::Context::Scope contextScope(context);
    v8::Local<v8::Object> obj = v8::Object::New(isolate_);
    obj->Set(context, v8::String::NewFromUtf8(isolate_, "repeat").ToLocalChecked(),
        v8::Boolean::New(isolate_, info.GetRepeat())).ToChecked();
    obj->Set(context, v8::String::NewFromUtf8(isolate_, "offsetX").ToLocalChecked(),
        v8::Number::New(isolate_, info.GetOffsetX())).ToChecked();
    obj->Set(context, v8::String::NewFromUtf8(isolate_, "offsetY").ToLocalChecked(),
        v8::Number::New(isolate_, info.GetOffsetY())).ToChecked();
    obj->Set(context, v8::String::NewFromUtf8(isolate_, "scale").ToLocalChecked(),
        v8::Number::New(isolate_, info.GetScale())).ToChecked();
    obj->Set(context, v8::String::NewFromUtf8(isolate_, "angle").ToLocalChecked(),
        v8::Number::New(isolate_, info.GetAngle())).ToChecked();
    obj->Set(context, v8::String::NewFromUtf8(isolate_, "timestamp").ToLocalChecked(),
        v8::Number::New(isolate_, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())))
        .ToChecked();
    v8::Local<v8::Value> v8Param = obj;
    V8Function::executeJS(1, &v8Param);

    // This is required to request for new frame, which eventually will call
    // FlushBuild, FlushLayout and FlushRender on the dirty elements
    V8DeclarativeEngineInstance::TriggerPageUpdate();
}

} // namespace OHOS::Ace::Framework
