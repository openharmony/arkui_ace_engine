/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_CROWN_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_CROWN_FUNCTION_H
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/core/event/crown_event.h"

namespace OHOS::Ace::Framework {

class JsCrownFunction : public JsFunction {
    DECLARE_ACE_TYPE(JsCrownFunction, JsFunction);
public:
    explicit JsCrownFunction(const JSRef<JSFunc>& jsFunction)
        : JsFunction(JSRef<JSObject>(), jsFunction) {}
    ~JsCrownFunction() override = default;
    void Execute()
    {
        ExecuteJS();
    }
    void Execute(OHOS::Ace::CrownEventInfo& event);

    JSRef<JSVal> ExecuteWithValue(OHOS::Ace::CrownEventInfo& event);

private:
    JSRef<JSObject> createCrownEvent(OHOS::Ace::CrownEventInfo& event);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_CROWN_FUNCTION_H
