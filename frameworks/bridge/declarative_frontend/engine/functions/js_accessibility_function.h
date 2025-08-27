/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_ACCESSIBILITY_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_ACCESSIBILITY_FUNCTION_H

#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"

namespace OHOS::Ace::Framework {
class JsAccessibilityActionInterceptFunction : public JsFunction {
    DECLARE_ACE_TYPE(JsAccessibilityActionInterceptFunction, JsFunction);

public:
    explicit JsAccessibilityActionInterceptFunction(const JSRef<JSFunc>& jsFunction)
        : JsFunction(JSRef<JSObject>(), jsFunction) {}

    ~JsAccessibilityActionInterceptFunction() override = default;

    void Execute()
    {
        ExecuteJS();
    }

    AccessibilityActionInterceptResult Execute(AccessibilityInterfaceAction action);
};

class JsAccessibilityHoverTransparentFunction : public JsFunction {
    DECLARE_ACE_TYPE(JsAccessibilityHoverTransparentFunction, JsFunction);

public:
    explicit JsAccessibilityHoverTransparentFunction(const JSRef<JSFunc>& jsFunction)
        : JsFunction(JSRef<JSObject>(), jsFunction) {}

    ~JsAccessibilityHoverTransparentFunction() override = default;

    void Execute()
    {
        ExecuteJS();
    }

    void Execute(TouchEventInfo& info);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_ACCESSIBILITY_FUNCTION_H
