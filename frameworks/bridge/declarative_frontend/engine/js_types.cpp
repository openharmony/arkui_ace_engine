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

static const std::unordered_set<std::string> g_clickPreventDefPattern = { "RichEditor", "Hyperlink" };
static const std::unordered_set<std::string> g_touchPreventDefPattern = { "Hyperlink" };

#ifdef USE_ARK_ENGINE
Local<JSValueRef> JsStopPropagation(panda::JsiRuntimeCallInfo *info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo = static_cast<BaseEventInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(
        info->GetVM(), 0));
    if (eventInfo) {
        eventInfo->SetStopPropagation(true);
    }
    return JSValueRef::Undefined(info->GetVM());
}

Local<JSValueRef> JsPropagation(panda::JsiRuntimeCallInfo* info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo =
        static_cast<BaseEventInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(info->GetVM(), 0));
    if (eventInfo) {
        eventInfo->SetStopPropagation(false);
    }
    return JSValueRef::Undefined(info->GetVM());
}

Local<JSValueRef> JsPreventDefault(panda::JsiRuntimeCallInfo *info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo = static_cast<BaseEventInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(
        info->GetVM(), 0));
    if (eventInfo) {
        eventInfo->SetPreventDefault(true);
    }
    return JSValueRef::Undefined(info->GetVM());
}

Local<JSValueRef> JsClickPreventDefault(panda::JsiRuntimeCallInfo *info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo = static_cast<BaseEventInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(
        info->GetVM(), 0));
    if (eventInfo) {
        auto patternName = eventInfo->GetPatternName();
        if (g_clickPreventDefPattern.find(patternName.c_str()) == g_clickPreventDefPattern.end()) {
            JSException::Throw(ERROR_CODE_COMPONENT_NOT_SUPPORTED_PREVENT_FUNCTION, "%s",
                "Component does not support prevent function.");
            return JSValueRef::Undefined(info->GetVM());
        }
        eventInfo->SetPreventDefault(true);
    }
    return JSValueRef::Undefined(info->GetVM());
}

Local<JSValueRef> JsTouchPreventDefault(panda::JsiRuntimeCallInfo *info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo = static_cast<BaseEventInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(
        info->GetVM(), 0));
    if (eventInfo) {
        auto patternName = eventInfo->GetPatternName();
        if (g_touchPreventDefPattern.find(patternName.c_str()) == g_touchPreventDefPattern.end()) {
            JSException::Throw(ERROR_CODE_COMPONENT_NOT_SUPPORTED_PREVENT_FUNCTION, "%s",
                "Component does not support prevent function.");
            return JSValueRef::Undefined(info->GetVM());
        }
        eventInfo->SetPreventDefault(true);
    }
    return JSValueRef::Undefined(info->GetVM());
}

Local<JSValueRef> JsGetHistoricalPoints(panda::JsiRuntimeCallInfo *info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo = static_cast<TouchEventInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(
        info->GetVM(), 0));
    if (!eventInfo) {
        return JSValueRef::Undefined(info->GetVM());
    }
    std::list<TouchLocationInfo> history = eventInfo->GetHistory();
    Local<ArrayRef> valueArray = ArrayRef::New(info->GetVM(), history.size());
    auto index = 0;
    for (auto const &point : history) {
        Local<ObjectRef> touchObject = ObjectRef::New(info->GetVM());
        const OHOS::Ace::Offset& globalLocation = point.GetGlobalLocation();
        const OHOS::Ace::Offset& localLocation = point.GetLocalLocation();
        const OHOS::Ace::Offset& screenLocation = point.GetScreenLocation();
        const OHOS::Ace::Offset& globalDisplayLocation = point.GetGlobalDisplayLocation();
        auto x = PipelineBase::Px2VpWithCurrentDensity(localLocation.GetX());
        auto y = PipelineBase::Px2VpWithCurrentDensity(localLocation.GetY());
        auto globalX = PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetX());
        auto globalY = PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetY());
        auto displayX = PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetX());
        auto displayY = PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetY());
        auto globalDisplayX = PipelineBase::Px2VpWithCurrentDensity(globalDisplayLocation.GetX());
        auto globalDisplayY = PipelineBase::Px2VpWithCurrentDensity(globalDisplayLocation.GetY());
        touchObject->Set(info->GetVM(), ToJSValue("id"), ToJSValue(point.GetFingerId()));
        touchObject->Set(info->GetVM(), ToJSValue("type"), ToJSValue(static_cast<int32_t>(point.GetTouchType())));
        touchObject->Set(info->GetVM(), ToJSValue("x"), ToJSValue(x));
        touchObject->Set(info->GetVM(), ToJSValue("y"), ToJSValue(y));
        touchObject->Set(info->GetVM(), ToJSValue("screenX"), ToJSValue(globalX));
        touchObject->Set(info->GetVM(), ToJSValue("screenY"), ToJSValue(globalY));
        touchObject->Set(info->GetVM(), ToJSValue("windowX"), ToJSValue(globalX));
        touchObject->Set(info->GetVM(), ToJSValue("windowY"), ToJSValue(globalY));
        touchObject->Set(info->GetVM(), ToJSValue("displayX"), ToJSValue(displayX));
        touchObject->Set(info->GetVM(), ToJSValue("displayY"), ToJSValue(displayY));
        touchObject->Set(info->GetVM(), ToJSValue("globalDisplayX"), ToJSValue(globalDisplayX));
        touchObject->Set(info->GetVM(), ToJSValue("globalDisplayY"), ToJSValue(globalDisplayY));
        touchObject->Set(info->GetVM(), ToJSValue("pressedTime"),
            ToJSValue(static_cast<double>(point.GetPressedTime().time_since_epoch().count())));
        touchObject->Set(info->GetVM(), ToJSValue("pressure"), ToJSValue(point.GetForce()));
        touchObject->Set(info->GetVM(),
            ToJSValue("width"), ToJSValue(PipelineBase::Px2VpWithCurrentDensity(point.GetWidth())));
        touchObject->Set(info->GetVM(),
            ToJSValue("height"), ToJSValue(PipelineBase::Px2VpWithCurrentDensity(point.GetHeight())));
        touchObject->Set(info->GetVM(), ToJSValue("hand"), ToJSValue(point.GetOperatingHand()));

        Local<ObjectRef> objRef = ObjectRef::New(info->GetVM());
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
