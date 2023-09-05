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

#include "frameworks/bridge/declarative_frontend/engine/js_types.h"

namespace OHOS::Ace::Framework {

#ifdef USE_ARK_ENGINE
Local<JSValueRef> JsStopPropagation(panda::JsiRuntimeCallInfo *info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo = static_cast<BaseEventInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(0));
    if (eventInfo) {
        LOGD("JsStopPropagation is trigger");
        eventInfo->SetStopPropagation(true);
    }
    return JSValueRef::Undefined(info->GetVM());
}

Local<JSValueRef> JsPreventDefault(panda::JsiRuntimeCallInfo *info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo = static_cast<BaseEventInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(0));
    if (eventInfo) {
        LOGD("JsPreventDefault is trigger");
        eventInfo->SetPreventDefault(true);
    }
    return JSValueRef::Undefined(info->GetVM());
}

Local<JSValueRef> JsGetHistoricalPoints(panda::JsiRuntimeCallInfo *info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo = static_cast<TouchEventInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(0));
    if (!eventInfo) {
        return JSValueRef::Undefined(info->GetVM());
    }
    std::list<TouchLocationInfo> history;
    history = eventInfo->GetHistory();
    Local<ArrayRef> valueArray = ArrayRef::New(info->GetVM(), history.size());
    auto index = 0;
    Local<ObjectRef> objRef = ObjectRef::New(info->GetVM());
    for (auto const &point : history) {
        Local<ObjectRef> touchObject = ObjectRef::New(info->GetVM());
        const OHOS::Ace::Offset& globalLocation = point.GetGlobalLocation();
        const OHOS::Ace::Offset& localLocation = point.GetLocalLocation();
        touchObject->Set(info->GetVM(), ToJSValue("id"), ToJSValue(point.GetFingerId()));
        touchObject->Set(info->GetVM(), ToJSValue("type"),
            ToJSValue(static_cast<int32_t>(point.GetTouchType())));
        touchObject->Set(info->GetVM(), ToJSValue("x"), ToJSValue(localLocation.GetX()));
        touchObject->Set(info->GetVM(), ToJSValue("y"), ToJSValue(localLocation.GetX()));
        touchObject->Set(info->GetVM(), ToJSValue("screenX"), ToJSValue(globalLocation.GetX()));
        touchObject->Set(info->GetVM(), ToJSValue("scrennY"), ToJSValue(globalLocation.GetX()));

        objRef->Set(info->GetVM(), ToJSValue("touchObject"), (touchObject));
        objRef->Set(info->GetVM(), ToJSValue("size"), ToJSValue(point.GetSize()));
        objRef->Set(info->GetVM(), ToJSValue("force"), ToJSValue(static_cast<double>(point.GetForce())));
        objRef->Set(info->GetVM(), ToJSValue("timestamp"),
            ToJSValue(static_cast<double>(point.GetTimeStamp().time_since_epoch().count())));
        
        ArrayRef::SetValueAt(info->GetVM(), valueArray, index++, objRef);
    }

    return valueArray;
}
#endif

} // namespace OHOS::Ace::Framework
