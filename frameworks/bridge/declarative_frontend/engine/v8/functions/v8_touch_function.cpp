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

#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_touch_function.h"

#include "base/log/log.h"
#include "core/gestures/raw_recognizer.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"

namespace OHOS::Ace::Framework {

v8::Local<v8::Array> V8TouchFunction::CreateTouchObject(const std::list<TouchLocationInfo>& touches)
{
    auto context = isolate_->GetCurrentContext();
    auto touchArray = v8::Array::New(isolate_);
    int index = 0;
    for (const auto& info : touches) {
        v8::Local<v8::Object> touchObj = v8::Object::New(isolate_);
        touchObj
            ->Set(context, v8::String::NewFromUtf8(isolate_, "type").ToLocalChecked(),
                v8::Number::New(isolate_, static_cast<int32_t>(info.GetTouchType())))
            .ToChecked();
        touchObj
            ->Set(context, v8::String::NewFromUtf8(isolate_, "id").ToLocalChecked(),
                v8::Number::New(isolate_, info.GetFingerId()))
            .ToChecked();
        touchObj
            ->Set(context, v8::String::NewFromUtf8(isolate_, "screenX").ToLocalChecked(),
                v8::Number::New(isolate_, static_cast<int32_t>(info.GetGlobalLocation().GetX())))
            .ToChecked();
        touchObj
            ->Set(context, v8::String::NewFromUtf8(isolate_, "screenY").ToLocalChecked(),
                v8::Number::New(isolate_, info.GetGlobalLocation().GetY()))
            .ToChecked();
        touchObj
            ->Set(context, v8::String::NewFromUtf8(isolate_, "x").ToLocalChecked(),
                v8::Number::New(isolate_, info.GetLocalLocation().GetX()))
            .ToChecked();
        touchObj
            ->Set(context, v8::String::NewFromUtf8(isolate_, "y").ToLocalChecked(),
                v8::Number::New(isolate_, info.GetLocalLocation().GetY()))
            .ToChecked();
        touchArray->Set(context, index, touchObj).ToChecked();
        index++;
    }
    return touchArray;
}

v8::Local<v8::Object> V8TouchFunction::CreateTouchEvent(TouchEventInfo& touchInfo)
{
    auto context = isolate_->GetCurrentContext();
    v8::Local<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(isolate_);
    objectTemplate->SetInternalFieldCount(1);
    v8::Local<v8::Object> touchInfoObj = objectTemplate->NewInstance(context).ToLocalChecked();
    touchInfoObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "timestamp").ToLocalChecked(),
              v8::Number::New(isolate_, static_cast<double>(touchInfo.GetTimeStamp().time_since_epoch().count())))
        .ToChecked();
    touchInfoObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "touches").ToLocalChecked(),
            CreateTouchObject(touchInfo.GetTouches()))
        .ToChecked();
    const std::list<TouchLocationInfo>& changedTouches = touchInfo.GetChangedTouches();
    touchInfoObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "changedTouches").ToLocalChecked(),
            CreateTouchObject(changedTouches))
        .ToChecked();
    if (changedTouches.size() > 0) {
        touchInfoObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "type").ToLocalChecked(),
              v8::Number::New(isolate_, static_cast<int32_t>(changedTouches.front().GetTouchType())))
        .ToChecked();
    }
    touchInfoObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "changedTouches").ToLocalChecked(),
            CreateTouchObject(changedTouches))
        .ToChecked();
    touchInfoObj
        ->Set(context, v8::String::NewFromUtf8(isolate_, "stopPropagation").ToLocalChecked(),
              v8::Function::New(context, V8Function::JsStopPropagation).ToLocalChecked())
        .ToChecked();
    touchInfoObj->SetAlignedPointerInInternalField(0, static_cast<void*>(&touchInfo));
    return touchInfoObj;
}

void V8TouchFunction::execute(TouchEventInfo& info)
{
    ACE_DCHECK(isolate_);
    v8::Isolate::Scope isolateScope(isolate_);
    v8::HandleScope handleScope(isolate_);
    auto context = ctx_.Get(isolate_);
    v8::Context::Scope contextScope(context);
    v8::Local<v8::Value> param = CreateTouchEvent(info);
    V8Function::executeJS(1, &param);
}

} // namespace OHOS::Ace::Framework
