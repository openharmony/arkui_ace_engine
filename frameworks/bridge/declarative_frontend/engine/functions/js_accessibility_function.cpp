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

#include "js_accessibility_function.h"

#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/functions/js_touch_function.h"

namespace OHOS::Ace::Framework {

AccessibilityActionInterceptResult JsAccessibilityActionInterceptFunction::Execute(AccessibilityInterfaceAction action)
{
    JSRef<JSVal> newJSVal = JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(action)));
    auto jsValue = JsFunction::ExecuteJS(1, &newJSVal);
    auto returnValue = AccessibilityActionInterceptResult::ACTION_CONTINUE;
    if (jsValue->IsNumber()) {
        returnValue = static_cast<AccessibilityActionInterceptResult>(jsValue->ToNumber<int32_t>());
    }
    return returnValue;
}

void JsAccessibilityHoverTransparentFunction::Execute(TouchEventInfo& info)
{
    JSRef<JSVal> param = JSRef<JSObject>::Cast(JsTouchFunction::CreateJSEventInfo(info));
    JsFunction::ExecuteJS(1, &param);
}

} // namespace OHOS::Ace::Framework
