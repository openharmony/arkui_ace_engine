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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_V8_FUNCTION_V8_PAN_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_V8_FUNCTION_V8_PAN_FUNCTION_H

#include "base/geometry/offset.h"
#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/gestures/drag_recognizer.h"

namespace OHOS::Ace::Framework {

class V8PanFunction : public V8Function {
    DECLARE_ACE_TYPE(V8PanFunction, V8Function)

public:
    V8PanFunction(v8::Local<v8::Function> jsFunction) : V8Function(v8::Undefined(v8::Isolate::GetCurrent()), jsFunction)
    {}
    ~V8PanFunction()
    {
        LOGD("Destroy: V8PanFunction");
    };

    void execute(const DragStartInfo& info);
    void execute(const DragUpdateInfo& info);
    void execute(const DragEndInfo& info);
    void execute();

private:
    v8::Local<v8::Object> createPanInfo(const TouchLocationInfo& info);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_V8_FUNCTION_V8_PAN_FUNCTION_H
