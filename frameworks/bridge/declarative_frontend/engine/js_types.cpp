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

namespace {
bool IsClickPreventDefaultSupported(const std::string& patternName)
{
    return patternName == "RichEditor" || patternName == "Hyperlink";
}

bool IsTouchPreventDefaultSupported(const std::string& patternName)
{
    return patternName == "Hyperlink";
}
} // namespace

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
        if (!IsClickPreventDefaultSupported(patternName)) {
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
        if (!IsTouchPreventDefaultSupported(patternName)) {
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
    const auto& history = eventInfo->GetHistory();
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
        touchObject->Set(info->GetVM(), ToJSValue("getCurrentLocalPosition"),
            panda::FunctionRef::New(info->GetVM(), JsGetCurrentLocalPosition));
        touchObject->SetNativePointerFieldCount(info->GetVM(), 1);
        touchObject->SetNativePointerField(
            info->GetVM(), 0, static_cast<void*>(const_cast<TouchLocationInfo*>(&point)));

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

Local<JSValueRef> JsGetMouseHistoricalPoints(panda::JsiRuntimeCallInfo* info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo =
        static_cast<MouseInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(info->GetVM(), 0));
    if (!eventInfo) {
        return JSValueRef::Undefined(info->GetVM());
    }

    const auto& history = eventInfo->GetHistory();
    Local<ArrayRef> valueArray = ArrayRef::New(info->GetVM(), history.size());
    uint32_t index = 0;
    for (const auto& point : history) {
        Local<ObjectRef> historyObject = ObjectRef::New(info->GetVM());
        historyObject->Set(info->GetVM(), ToJSValue("x"),
            ToJSValue(PipelineBase::Px2VpWithCurrentDensity(point.localLocation.GetX())));
        historyObject->Set(info->GetVM(), ToJSValue("y"),
            ToJSValue(PipelineBase::Px2VpWithCurrentDensity(point.localLocation.GetY())));
        historyObject->Set(info->GetVM(), ToJSValue("displayX"),
            ToJSValue(PipelineBase::Px2VpWithCurrentDensity(point.screenLocation.GetX())));
        historyObject->Set(info->GetVM(), ToJSValue("displayY"),
            ToJSValue(PipelineBase::Px2VpWithCurrentDensity(point.screenLocation.GetY())));
        historyObject->Set(info->GetVM(), ToJSValue("windowX"),
            ToJSValue(PipelineBase::Px2VpWithCurrentDensity(point.globalLocation.GetX())));
        historyObject->Set(info->GetVM(), ToJSValue("windowY"),
            ToJSValue(PipelineBase::Px2VpWithCurrentDensity(point.globalLocation.GetY())));
        historyObject->Set(info->GetVM(), ToJSValue("globalDisplayX"),
            ToJSValue(PipelineBase::Px2VpWithCurrentDensity(point.globalDisplayLocation.GetX())));
        historyObject->Set(info->GetVM(), ToJSValue("globalDisplayY"),
            ToJSValue(PipelineBase::Px2VpWithCurrentDensity(point.globalDisplayLocation.GetY())));
        historyObject->Set(info->GetVM(), ToJSValue("timestamp"),
            ToJSValue(static_cast<double>(point.time.time_since_epoch().count())));
        ArrayRef::SetValueAt(info->GetVM(), valueArray, index++, historyObject);
    }

    return valueArray;
}

namespace {
bool FindTouchCurrentLocal(const std::list<TouchLocationInfo>& touchList, int32_t fingerId, Offset& out)
{
    if (fingerId < 0) {
        return false;
    }
    auto iter = std::find_if(touchList.begin(), touchList.end(), [fingerId](const TouchLocationInfo& item) {
        return item.GetFingerId() == fingerId;
    });
    if (iter == touchList.end()) {
        return false;
    }
    out = iter->GetCurrentLocalLocation();
    return true;
}

bool GetTouchEventCurrentLocal(TouchEventInfo* touchEventInfo, Offset& currentLocal)
{
    int32_t fingerId = -1;
    if (!touchEventInfo->GetChangedTouches().empty()) {
        fingerId = touchEventInfo->GetChangedTouches().back().GetFingerId();
    } else if (!touchEventInfo->GetTouches().empty()) {
        fingerId = touchEventInfo->GetTouches().back().GetFingerId();
    }
    if (!FindTouchCurrentLocal(touchEventInfo->GetChangedTouches(), fingerId, currentLocal) &&
        !FindTouchCurrentLocal(touchEventInfo->GetTouches(), fingerId, currentLocal)) {
        currentLocal = Offset::Zero();
        return false;
    }
    return true;
}

bool GetBaseGestureEventCurrentLocal(BaseGestureEvent* baseGestureEvent, Offset& currentLocal)
{
    const auto& fingerList = baseGestureEvent->GetFingerList();
    if (fingerList.empty()) {
        currentLocal = Offset::Zero();
        return false;
    }

    if (fingerList.back().currentLocalLocation_) {
        currentLocal = fingerList.back().currentLocalLocation_();
        return true;
    }
    return false;
}

bool GetCurrentLocalFromEventInfo(panda::EcmaVM* vm, const panda::Local<panda::ObjectRef>& thisObjRef,
    BaseEventInfo* eventInfo, Offset& currentLocal)
{
    if (auto touchLocationInfo = TypeInfoHelper::DynamicCast<TouchLocationInfo>(eventInfo); touchLocationInfo) {
        currentLocal = touchLocationInfo->GetCurrentLocalLocation();
        return true;
    }
    if (auto gestureEvent = TypeInfoHelper::DynamicCast<GestureEvent>(eventInfo); gestureEvent) {
        currentLocal = gestureEvent->GetCurrentLocalLocation();
        return true;
    }
    if (auto baseGestureEvent = TypeInfoHelper::DynamicCast<BaseGestureEvent>(eventInfo); baseGestureEvent) {
        return GetBaseGestureEventCurrentLocal(baseGestureEvent, currentLocal);
    }
    if (auto mouseInfo = TypeInfoHelper::DynamicCast<MouseInfo>(eventInfo); mouseInfo) {
        currentLocal = mouseInfo->GetCurrentLocalLocation();
        return true;
    }
    if (auto axisInfo = TypeInfoHelper::DynamicCast<AxisInfo>(eventInfo); axisInfo) {
        currentLocal = axisInfo->GetCurrentLocalLocation();
        return true;
    }
    if (auto touchEventInfo = TypeInfoHelper::DynamicCast<TouchEventInfo>(eventInfo); touchEventInfo) {
        return GetTouchEventCurrentLocal(touchEventInfo, currentLocal);
    }
    if (auto clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(eventInfo); clickInfo) {
        currentLocal = clickInfo->GetCurrentLocalLocation();
        return true;
    }
    return false;
}
} // namespace

Local<JSValueRef> JsGetCurrentLocalPositionForFinger(panda::JsiRuntimeCallInfo *info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto thisObjRef = panda::Local<panda::ObjectRef>(thisObj);
    if (thisObjRef.IsEmpty()) {
        return JSValueRef::Undefined(info->GetVM());
    }
    auto fingerInfo = static_cast<FingerInfo*>(thisObjRef->GetNativePointerField(info->GetVM(), 0));
    Offset currentLocal = Offset::Zero();

    if (fingerInfo) {
        if (!fingerInfo->currentLocalLocation_) {
            return JSValueRef::Undefined(info->GetVM());
        }
        currentLocal = fingerInfo->currentLocalLocation_();
    }
    
    auto retObj = ObjectRef::New(info->GetVM());
    retObj->Set(info->GetVM(), ToJSValue("x"), ToJSValue(PipelineBase::Px2VpWithCurrentDensity(currentLocal.GetX())));
    retObj->Set(info->GetVM(), ToJSValue("y"), ToJSValue(PipelineBase::Px2VpWithCurrentDensity(currentLocal.GetY())));
    return retObj;
}

Local<JSValueRef> JsGetCurrentLocalPosition(panda::JsiRuntimeCallInfo *info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto thisObjRef = panda::Local<panda::ObjectRef>(thisObj);
    if (thisObjRef.IsEmpty()) {
        return JSValueRef::Undefined(info->GetVM());
    }
    auto eventInfo = static_cast<BaseEventInfo*>(thisObjRef->GetNativePointerField(info->GetVM(), 0));
    Offset currentLocal = Offset::Zero();

    if (eventInfo) {
        if (!GetCurrentLocalFromEventInfo(info->GetVM(), thisObjRef, eventInfo, currentLocal)) {
            return JSValueRef::Undefined(info->GetVM());
        }
    }
    
    auto retObj = ObjectRef::New(info->GetVM());
    retObj->Set(info->GetVM(), ToJSValue("x"), ToJSValue(PipelineBase::Px2VpWithCurrentDensity(currentLocal.GetX())));
    retObj->Set(info->GetVM(), ToJSValue("y"), ToJSValue(PipelineBase::Px2VpWithCurrentDensity(currentLocal.GetY())));
    return retObj;
}
#endif

} // namespace OHOS::Ace::Framework
