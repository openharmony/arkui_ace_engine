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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JS_TYPES_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JS_TYPES_H

#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_types.h"

namespace OHOS::Ace::Framework {

using JSVal = QJSValue;
using JSObject = QJSObject;
using JSFunc = QJSFunction;
using JSArray = QJSArray;
using JSCallbackInfo = QJSCallbackInfo;
using JSGCMarkCallbackInfo = QJSGCMarkCallbackInfo;
using JSException = QJSException;
using JSExecutionContext = QJSExecutionContext;
using JSObjTemplate = QJSObjTemplate;

template<class T>
inline auto ToJSValue(T&& val)
{
    return QJSValueConvertor::toQJSValue(std::forward<T>(val));
};

JSValue JsStopPropagation(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* arg);

}; // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JS_TYPES_H
