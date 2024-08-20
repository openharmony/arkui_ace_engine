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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_SCOPE_UTIL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_SCOPE_UTIL_H

#include "frameworks/bridge/declarative_frontend/engine/bindings_defines.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"

namespace OHOS::Ace::Framework {
class JSScopeUtil : public Referenced {
public:
    JSScopeUtil();
    ~JSScopeUtil() = default;

    static void JSBind(BindingTarget globalObj);
    static void SyncInstanceId(const JSCallbackInfo& info);
    static void RestoreInstanceId(const JSCallbackInfo& info);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_SCOPE_UTIL_H