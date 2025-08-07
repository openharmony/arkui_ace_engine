/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_ON_CHILD_TOUCH_TEST_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_ON_CHILD_TOUCH_TEST_FUNCTION_H

#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/core/components_ng/event/gesture_event_hub.h"
namespace OHOS::Ace::Framework {
class JsOnChildTouchTestFunction : public JsFunction {
    DECLARE_ACE_TYPE(JsOnChildTouchTestFunction, JsFunction)

public:
    explicit JsOnChildTouchTestFunction(const JSRef<JSFunc>& jsFunction) : JsFunction(JSRef<JSObject>(), jsFunction) {}
    ~JsOnChildTouchTestFunction() override = default;
    void Execute();
    JSRef<JSVal> Execute(const std::vector<NG::TouchTestInfo>& touchInfo);

private:
    JSRef<JSObject> CreateRectangle(const NG::RectF& info);
    JSRef<JSObject> CreateTouchTestInfo(const NG::TouchTestInfo& info);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_PRE_TOUCH_TEST_FUNCTION_H
