/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_CLASS_BASE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_CLASS_BASE_H

#include "frameworks/bridge/declarative_frontend/engine/bindings_defines.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings_implementation.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_value_conversions.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"

namespace OHOS::Ace::Framework {
using JsiFunctionMap = std::unordered_map<std::string, panda::Global<panda::FunctionRef>>;

class JsiClassBase {
public:
    static void DeclareImpl(const char* name, std::string& className,
        JsiFunctionMap& staticFns, JsiFunctionMap& customFns,
        JsiFunctionMap& customGetFns, JsiFunctionMap& customSetFns,
        panda::Global<panda::FunctionRef>& classFn);

    static void AddStaticMethodJSImpl(const char* name,
        StaticFunctionBinding<void, const JSCallbackInfo&>* binding,
        JsiFunctionMap& staticFns, FunctionCallback nativeCallback);

    static void AddCustomMethodImpl(const char* name,
        FunctionCallback callback, JsiFunctionMap& customFns);

    static void AddCustomStaticMethodImpl(const char* name,
        FunctionCallback callback, JsiFunctionMap& staticFns);

    static void BindImpl(BindingTarget t, const char* jsName, const std::string& classDisplayName,
        FunctionCallback classNativeCallback, JsiFunctionMap& staticFns, JsiFunctionMap& customFns,
        JsiFunctionMap& customGetFns, JsiFunctionMap& customSetFns,
        panda::Global<panda::FunctionRef>& classFn);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_CLASS_BASE_H
