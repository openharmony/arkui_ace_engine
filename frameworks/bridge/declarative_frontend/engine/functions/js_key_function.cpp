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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_key_function.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::Framework {

void JsKeyFunction::Execute(EcmaVM* vm, OHOS::Ace::KeyEventInfo& event)
{
    // The infoPtr can only be bound to a JS object, and its lifetime belongs to that object.
    // It is not allowed to hold this address elsewhere.
    auto infoPtr = new KeyEventInfo(event);
    auto obj = NG::FrameNodeBridge::CreateKeyEventInfoObj(vm, infoPtr);
    JSRef<JSVal> param = JSRef<JSVal>::Make(obj);
    JsFunction::ExecuteJS(1, &param);
    event.SetStopPropagation(infoPtr->IsStopPropagation());
}

JSRef<JSVal> JsKeyFunction::ExecuteWithValue(EcmaVM* vm, OHOS::Ace::KeyEventInfo& event)
{
    // The infoPtr can only be bound to a JS object, and its lifetime belongs to that object.
    // It is not allowed to hold this address elsewhere.
    auto infoPtr = new KeyEventInfo(event);
    auto obj = NG::FrameNodeBridge::CreateKeyEventInfoObj(vm, infoPtr);
    JSRef<JSVal> param = JSRef<JSVal>::Make(obj);
    ACE_BENCH_MARK_TRACE("OnKeyEvent_end type:%d", infoPtr->GetKeyType());
    JSRef<JSVal> result = JsFunction::ExecuteJS(1, &param);
    event.SetStopPropagation(infoPtr->IsStopPropagation());
    return result;
}

} // namespace OHOS::Ace::Framework
