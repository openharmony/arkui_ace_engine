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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_V8_FUNCTION_V8_TOUCH_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_V8_FUNCTION_V8_TOUCH_FUNCTION_H

#include "base/geometry/offset.h"
#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/gestures/raw_recognizer.h"

namespace OHOS::Ace::Framework {

class V8TouchFunction : public V8Function {
    DECLARE_ACE_TYPE(V8TouchFunction, V8Function)

public:
    V8TouchFunction(v8::Local<v8::Function> jsFunction)
        : V8Function(v8::Undefined(v8::Isolate::GetCurrent()), jsFunction)
    {}
    ~V8TouchFunction()
    {
        LOGD("Destroy: V8TouchFunction");
    };

    void execute(TouchEventInfo& info);

private:
    v8::Local<v8::Object> CreateTouchEvent(TouchEventInfo& touchInfo);
    v8::Local<v8::Array> CreateTouchObject(const std::list<TouchLocationInfo>& touches);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_V8_FUNCTION_V8_TOUCH_FUNCTION_H
