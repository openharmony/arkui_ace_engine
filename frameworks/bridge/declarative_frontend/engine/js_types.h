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

#ifdef USE_ARK_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_types.h"
#endif

namespace OHOS::Ace::Framework {

#ifdef USE_ARK_ENGINE

using JSVal = JsiValue;
using JSObject = JsiObject;
using JSFunc = JsiFunction;
using JSArray = JsiArray;
using JSArrayBuffer = JsiArrayBuffer;
using JSUint8ClampedArray = JsiUint8ClampedArray;
using JSString = JsiString;
using JSCallbackInfo = JsiCallbackInfo;
using JSGCMarkCallbackInfo = JsiGCMarkCallbackInfo;
using JSException = JsiException;
using JSExecutionContext = JsiExecutionContext;
using JSObjTemplate = JsiObjTemplate;
using JSDate = JsiDate;
using JSFastNativeScope = panda::JsiFastNativeScope;

template<class T>
inline auto ToJSValue(T&& val)
{
    return JsiValueConvertor::toJsiValue(std::forward<T>(val));
};

inline const panda::ecmascript::EcmaVM* GetEcmaVm()
{
    return JsiValueConvertor::getEcmaVm();
}

Local<JSValueRef> JsStopPropagation(panda::JsiRuntimeCallInfo *info);
Local<JSValueRef> JsPreventDefault(panda::JsiRuntimeCallInfo *info);
Local<JSValueRef> JsClickPreventDefault(panda::JsiRuntimeCallInfo *info);
Local<JSValueRef> JsTouchPreventDefault(panda::JsiRuntimeCallInfo *info);
Local<JSValueRef> JsGetHistoricalPoints(panda::JsiRuntimeCallInfo *info);
Local<JSValueRef> JsPropagation(panda::JsiRuntimeCallInfo *info);

#endif

}; // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JS_TYPES_H
