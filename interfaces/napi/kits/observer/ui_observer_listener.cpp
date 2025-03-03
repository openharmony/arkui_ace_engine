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

#include "ui_observer_listener.h"

namespace OHOS::Ace::Napi {
namespace {
constexpr char NAV_BAR[] = "navBar";
constexpr int32_t PARAM_SIZE_TWO = 2;
constexpr int32_t PARAM_SIZE_SIX = 6;
}

void UIObserverListener::OnNavigationStateChange(const NG::NavDestinationInfo& info)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle navDestination state change failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value argv[] = { CreateNavDestinationInfoObj(info) };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::OnScrollEventStateChange(
    const std::string& id, int32_t uniqueId, NG::ScrollEventType eventType, float offset)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle scrollEvent state change failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value scrollId = nullptr;
    napi_value frameNodeId = nullptr;
    napi_value scrollEventType = nullptr;
    napi_value scrollOffset = nullptr;
    napi_create_string_utf8(env_, id.c_str(), id.length(), &scrollId);
    napi_create_int32(env_, uniqueId, &frameNodeId);
    napi_create_int32(env_, static_cast<int32_t>(eventType), &scrollEventType);
    napi_create_double(env_, offset, &scrollOffset);
    napi_set_named_property(env_, objValue, "id", scrollId);
    napi_set_named_property(env_, objValue, "uniqueId", frameNodeId);
    napi_set_named_property(env_, objValue, "scrollEvent", scrollEventType);
    napi_set_named_property(env_, objValue, "offset", scrollOffset);
    napi_value argv[] = { objValue };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::OnRouterPageStateChange(const NG::RouterPageInfoNG& pageInfo)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle router page state change failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value napiCtx = pageInfo.context;
    napi_value napiIndex = nullptr;
    napi_value napiName = nullptr;
    napi_value napiPath = nullptr;
    napi_value napiState = nullptr;
    napi_value napiPageId = nullptr;
    napi_create_int32(env_, pageInfo.index, &napiIndex);
    napi_create_string_utf8(env_, pageInfo.name.c_str(), pageInfo.name.length(), &napiName);
    napi_create_string_utf8(env_, pageInfo.path.c_str(), pageInfo.path.length(), &napiPath);
    napi_create_int32(env_, static_cast<int32_t>(pageInfo.state), &napiState);
    napi_create_string_utf8(env_, pageInfo.pageId.c_str(), pageInfo.pageId.length(), &napiPageId);
    napi_set_named_property(env_, objValue, "context", napiCtx);
    napi_set_named_property(env_, objValue, "index", napiIndex);
    napi_set_named_property(env_, objValue, "name", napiName);
    napi_set_named_property(env_, objValue, "path", napiPath);
    napi_set_named_property(env_, objValue, "state", napiState);
    napi_set_named_property(env_, objValue, "pageId", napiPageId);
    napi_value argv[] = { objValue };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::OnDensityChange(double density)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle density change failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value napiDensity = nullptr;
    napi_create_double(env_, density, &napiDensity);
    napi_set_named_property(env_, objValue, "density", napiDensity);
    napi_value argv[] = { objValue };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::OnDrawOrLayout()
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER, "Handle draw or layout failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value argv[] = { objValue };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::OnNavDestinationSwitch(const NG::NavDestinationSwitchInfo& switchInfo)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle navDestination switch failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value argv[] = { CreateNavDestinationSwitchInfoObj(switchInfo) };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

napi_value UIObserverListener::CreateNavDestinationSwitchInfoObj(const NG::NavDestinationSwitchInfo& switchInfo)
{
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value napiOperation = nullptr;
    napi_value napiFrom = nullptr;
    if (switchInfo.from.has_value()) {
        napiFrom = CreateNavDestinationInfoObj(switchInfo.from.value());
    } else {
        napi_create_string_utf8(env_, NAV_BAR, NAPI_AUTO_LENGTH, &napiFrom);
    }
    napi_value napiTo = nullptr;
    if (switchInfo.to.has_value()) {
        napiTo = CreateNavDestinationInfoObj(switchInfo.to.value());
    } else {
        napi_create_string_utf8(env_, NAV_BAR, NAPI_AUTO_LENGTH, &napiTo);
    }
    napi_create_int32(env_, static_cast<int32_t>(switchInfo.operation), &napiOperation);
    napi_set_named_property(env_, objValue, "context", switchInfo.context);
    napi_set_named_property(env_, objValue, "from", napiFrom);
    napi_set_named_property(env_, objValue, "to", napiTo);
    napi_set_named_property(env_, objValue, "operation", napiOperation);
    return objValue;
}

void UIObserverListener::OnWillClick(
    const GestureEvent& gestureEventInfo, const ClickInfo& clickInfo, const RefPtr<NG::FrameNode> frameNode)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle density change failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }

    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    
    napi_value objValueClickEvent = nullptr;
    napi_create_object(env_, &objValueClickEvent);

    AddBaseEventInfo(objValueClickEvent, clickInfo);
    AddGestureEventInfoOne(objValueClickEvent, gestureEventInfo);
    AddGestureEventInfoTwo(objValueClickEvent, gestureEventInfo);
    AddGestureEventInfoThree(objValueClickEvent, gestureEventInfo);
    AddClickEventInfoOne(objValueClickEvent, clickInfo);
    AddClickEventInfoTwo(objValueClickEvent, clickInfo);

    napi_value objValueFrameNode = nullptr;
    napi_create_object(env_, &objValueFrameNode);

    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto frontEnd = container->GetFrontend();
    CHECK_NULL_VOID(frontEnd);
    auto nodeId = frameNode->GetId();
    objValueFrameNode = frontEnd->GetFrameNodeValueByNodeId(nodeId);

    napi_value argv[] = { objValueClickEvent, objValueFrameNode };
    napi_call_function(env_, nullptr, callback, PARAM_SIZE_TWO, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::OnDidClick(
    const GestureEvent& gestureEventInfo, const ClickInfo& clickInfo, const RefPtr<NG::FrameNode> frameNode)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle density change failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }

    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    
    napi_value objValueClickEvent = nullptr;
    napi_create_object(env_, &objValueClickEvent);

    AddBaseEventInfo(objValueClickEvent, clickInfo);
    AddGestureEventInfoOne(objValueClickEvent, gestureEventInfo);
    AddGestureEventInfoTwo(objValueClickEvent, gestureEventInfo);
    AddGestureEventInfoThree(objValueClickEvent, gestureEventInfo);
    AddClickEventInfoOne(objValueClickEvent, clickInfo);
    AddClickEventInfoTwo(objValueClickEvent, clickInfo);

    napi_value objValueFrameNode = nullptr;
    napi_create_object(env_, &objValueFrameNode);

    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto frontEnd = container->GetFrontend();
    CHECK_NULL_VOID(frontEnd);
    auto nodeId = frameNode->GetId();
    objValueFrameNode = frontEnd->GetFrameNodeValueByNodeId(nodeId);

    napi_value argv[] = { objValueClickEvent, objValueFrameNode };
    napi_call_function(env_, nullptr, callback, PARAM_SIZE_TWO, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::OnTabContentStateChange(const NG::TabContentInfo& tabContentInfo)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle tabContent state change failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value objValue = nullptr;
    napi_value param1 = nullptr;
    napi_value param2 = nullptr;
    napi_value param3 = nullptr;
    napi_value param4 = nullptr;
    napi_value param5 = nullptr;
    napi_value param6 = nullptr;
    napi_create_string_utf8(env_, tabContentInfo.tabContentId.c_str(), tabContentInfo.tabContentId.length(), &param1);
    napi_create_int32(env_, tabContentInfo.tabContentUniqueId, &param2);
    napi_create_int32(env_, static_cast<int32_t>(tabContentInfo.state), &param3);
    napi_create_int32(env_, tabContentInfo.index, &param4);
    napi_create_string_utf8(env_, tabContentInfo.id.c_str(), tabContentInfo.id.length(), &param5);
    napi_create_int32(env_, tabContentInfo.uniqueId, &param6);
    const char *keys[] = {
        "tabContentId",
        "tabContentUniqueId",
        "state",
        "index",
        "id",
        "uniqueId",
    };
    const napi_value values[] = {
        param1,
        param2,
        param3,
        param4,
        param5,
        param6,
    };
    napi_create_object_with_named_properties(env_, &objValue, PARAM_SIZE_SIX, keys, values);
    napi_value argv[] = { objValue };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

napi_valuetype UIObserverListener::GetValueType(napi_env env, napi_value value)
{
    if (value == nullptr) {
        return napi_undefined;
    }

    napi_valuetype valueType = napi_undefined;
    NAPI_CALL_BASE(env, napi_typeof(env, value, &valueType), napi_undefined);
    return valueType;
}

napi_value UIObserverListener::GetNamedProperty(napi_env env, napi_value object, const std::string& propertyName)
{
    if (GetValueType(env, object) != napi_object) {
        napi_value undefined = nullptr;
        NAPI_CALL(env, napi_get_undefined(env, &undefined));
        return undefined;
    }

    napi_value value = nullptr;
    NAPI_CALL(env, napi_get_named_property(env, object, propertyName.c_str(), &value));
    return value;
}

void UIObserverListener::AddBaseEventInfo(napi_value objValueClickEvent, const ClickInfo& clickInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }

    napi_value napiTimeStamp = nullptr;
    napi_value napiSource = nullptr;
    napi_value napiPressure = nullptr;
    napi_value napiTiltX = nullptr;
    napi_value napiTiltY = nullptr;
    napi_value napiSourceTool = nullptr;

    napi_create_double(env_,
        static_cast<double>(clickInfo.GetTimeStamp().time_since_epoch().count()), &napiTimeStamp);
    napi_create_double(env_, static_cast<int32_t>(clickInfo.GetSourceDevice()), &napiSource);
    napi_create_double(env_, clickInfo.GetForce(), &napiPressure);
    if (clickInfo.GetTiltX().has_value()) {
        napi_create_double(env_, clickInfo.GetTiltX().value(), &napiTiltX);
    }
    if (clickInfo.GetTiltY().has_value()) {
        napi_create_double(env_, clickInfo.GetTiltY().value(), &napiTiltY);
    }
    napi_create_double(env_, static_cast<int32_t>(clickInfo.GetSourceTool()), &napiSourceTool);

    napi_set_named_property(env_, objValueClickEvent, "timestamp", napiTimeStamp);
    napi_set_named_property(env_, objValueClickEvent, "source", napiSource);
    napi_set_named_property(env_, objValueClickEvent, "pressure", napiPressure);
    napi_set_named_property(env_, objValueClickEvent, "tiltX", napiTiltX);
    napi_set_named_property(env_, objValueClickEvent, "tiltY", napiTiltY);
    napi_set_named_property(env_, objValueClickEvent, "sourceTool", napiSourceTool);

    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::AddGestureEventInfoOne(napi_value objValueClickEvent, const GestureEvent& gestureEventInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    double scale = Dimension(1.0, DimensionUnit::VP).ConvertToPx();
    if (NearZero(scale)) {
        scale = 1.0;
    }
    napi_value napiRepeat = GetNamedProperty(env_, objValueClickEvent, "repeat");
    if (GetValueType(env_, napiRepeat) != napi_null) {
        napi_get_boolean(env_, gestureEventInfo.GetRepeat(), &napiRepeat);
        napi_set_named_property(env_, objValueClickEvent, "repeat", napiRepeat);
    }
    napi_value napiOffsetX = GetNamedProperty(env_, objValueClickEvent, "offsetX");
    if (GetValueType(env_, napiOffsetX) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetOffsetX() / scale, &napiOffsetX);
        napi_set_named_property(env_, objValueClickEvent, "offsetX", napiOffsetX);
    }
    napi_value napiOffsetY = GetNamedProperty(env_, objValueClickEvent, "offsetY");
    if (GetValueType(env_, napiOffsetY) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetOffsetY() / scale, &napiOffsetY);
        napi_set_named_property(env_, objValueClickEvent, "offsetY", napiOffsetY);
    }
    napi_value napiScale = GetNamedProperty(env_, objValueClickEvent, "scale");
    if (GetValueType(env_, napiScale) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetScale(), &napiScale);
        napi_set_named_property(env_, objValueClickEvent, "scale", napiScale);
    }
    napi_value napiAngle = GetNamedProperty(env_, objValueClickEvent, "angle");
    if (GetValueType(env_, napiAngle) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetAngle() / scale, &napiAngle);
        napi_set_named_property(env_, objValueClickEvent, "angle", napiAngle);
    }
    napi_value napiSpeed = GetNamedProperty(env_, objValueClickEvent, "speed");
    if (GetValueType(env_, napiSpeed) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetSpeed() / scale, &napiSpeed);
        napi_set_named_property(env_, objValueClickEvent, "speed", napiSpeed);
    }
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::AddGestureEventInfoTwo(napi_value objValueClickEvent, const GestureEvent& gestureEventInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    double scale = Dimension(1.0, DimensionUnit::VP).ConvertToPx();
    if (NearZero(scale)) {
        scale = 1.0;
    }
    napi_value napiGlobalX = GetNamedProperty(env_, objValueClickEvent, "globalX");
    if (GetValueType(env_, napiGlobalX) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetGlobalLocation().GetX() / scale, &napiGlobalX);
        napi_set_named_property(env_, objValueClickEvent, "globalX", napiGlobalX);
    }
    napi_value napiGlobalY = GetNamedProperty(env_, objValueClickEvent, "globalY");
    if (GetValueType(env_, napiGlobalY) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetGlobalLocation().GetY() / scale, &napiGlobalY);
        napi_set_named_property(env_, objValueClickEvent, "globalY", napiGlobalY);
    }
    napi_value napiLocalX = GetNamedProperty(env_, objValueClickEvent, "localX");
    if (GetValueType(env_, napiLocalX) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetLocalLocation().GetX() / scale, &napiLocalX);
        napi_set_named_property(env_, objValueClickEvent, "localX", napiLocalX);
    }
    napi_value napiLocalY = GetNamedProperty(env_, objValueClickEvent, "localY");
    if (GetValueType(env_, napiLocalY) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetLocalLocation().GetY() / scale, &napiLocalY);
        napi_set_named_property(env_, objValueClickEvent, "localY", napiLocalY);
    }
    napi_value napiPinchCenterX = GetNamedProperty(env_, objValueClickEvent, "pinchCenterX");
    if (GetValueType(env_, napiPinchCenterX) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetPinchCenter().GetX() / scale, &napiPinchCenterX);
        napi_set_named_property(env_, objValueClickEvent, "pinchCenterX", napiPinchCenterX);
    }
    napi_value napiPinchCenterY = GetNamedProperty(env_, objValueClickEvent, "pinchCenterY");
    if (GetValueType(env_, napiPinchCenterY) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetPinchCenter().GetY() / scale, &napiPinchCenterY);
        napi_set_named_property(env_, objValueClickEvent, "pinchCenterY", napiPinchCenterY);
    }
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::AddGestureEventInfoThree(napi_value objValueClickEvent, const GestureEvent& gestureEventInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    double scale = Dimension(1.0, DimensionUnit::VP).ConvertToPx();
    if (NearZero(scale)) {
        scale = 1.0;
    }
    napi_value napiVelocityX = GetNamedProperty(env_, objValueClickEvent, "velocityX");
    if (GetValueType(env_, napiVelocityX) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetVelocity().GetVelocityX() / scale, &napiVelocityX);
        napi_set_named_property(env_, objValueClickEvent, "velocityX", napiVelocityX);
    }
    napi_value napiVelocityY = GetNamedProperty(env_, objValueClickEvent, "velocityY");
    if (GetValueType(env_, napiVelocityY) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetVelocity().GetVelocityY() / scale, &napiVelocityY);
        napi_set_named_property(env_, objValueClickEvent, "velocityY", napiVelocityY);
    }
    napi_value napiVelocity = GetNamedProperty(env_, objValueClickEvent, "velocity");
    if (GetValueType(env_, napiVelocity) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetVelocity().GetVelocityValue() / scale, &napiVelocity);
        napi_set_named_property(env_, objValueClickEvent, "velocity", napiVelocity);
    }
    AddFingerListInfo(objValueClickEvent, gestureEventInfo);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::AddFingerListInfo(napi_value objValueClickEvent, const GestureEvent& gestureEventInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }

    const std::list<FingerInfo>& fingerList = gestureEventInfo.GetFingerList();
    napi_value napiFingerList = nullptr;
    napi_create_array(env_, &napiFingerList);
    bool isArray = false;
    if (napi_is_array(env_, napiFingerList, &isArray) != napi_ok || !isArray) {
        return;
    }
    double scale = Dimension(1.0, DimensionUnit::VP).ConvertToPx();
    if (NearZero(scale)) {
        scale = 1.0;
    }
    int32_t index = 0;
    if (fingerList.size() > 0) {
        for (auto finger : fingerList) {
            napi_value napiFinger = nullptr;
            napi_create_object(env_, &napiFinger);

            napi_value napiId = nullptr;
            napi_create_double(env_, finger.fingerId_, &napiId);
            napi_set_named_property(env_, napiFinger, "id", napiId);
            const OHOS::Ace::Offset& globalLocation = finger.globalLocation_;
            const OHOS::Ace::Offset& localLocation = finger.localLocation_;
            napi_value napiGlobalX = nullptr;
            napi_create_double(env_, globalLocation.GetX() / scale, &napiGlobalX);
            napi_set_named_property(env_, napiFinger, "globalX", napiGlobalX);
            napi_value napiGlobalY = nullptr;
            napi_create_double(env_, globalLocation.GetY() / scale, &napiGlobalY);
            napi_set_named_property(env_, napiFinger, "globalY", napiGlobalY);
            napi_value napiLocalX = nullptr;
            napi_create_double(env_, localLocation.GetX() / scale, &napiLocalX);
            napi_set_named_property(env_, napiFinger, "localX", napiLocalX);
            napi_value napiLocalY = nullptr;
            napi_create_double(env_, localLocation.GetY() / scale, &napiLocalY);
            napi_set_named_property(env_, napiFinger, "localY", napiLocalY);
        
            napi_set_element(env_, napiFingerList, index++, napiFinger);
        }
    }
    napi_set_named_property(env_, objValueClickEvent, "fingerList", napiFingerList);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::AddClickEventInfoOne(napi_value objValueClickEvent, const ClickInfo& clickInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }

    double scale = Dimension(1.0, DimensionUnit::VP).ConvertToPx();
    if (NearZero(scale)) {
        scale = 1.0;
    }
    Offset globalOffset = clickInfo.GetGlobalLocation();
    Offset screenOffset = clickInfo.GetScreenLocation();
    napi_value napiDisplayX = GetNamedProperty(env_, objValueClickEvent, "displayX");
    if (GetValueType(env_, napiDisplayX) != napi_null) {
        napi_create_double(env_, screenOffset.GetX() / scale, &napiDisplayX);
        napi_set_named_property(env_, objValueClickEvent, "displayX", napiDisplayX);
    }
    napi_value napiDisplayY = GetNamedProperty(env_, objValueClickEvent, "displayY");
    if (GetValueType(env_, napiDisplayY) != napi_null) {
        napi_create_double(env_, screenOffset.GetY() / scale, &napiDisplayY);
        napi_set_named_property(env_, objValueClickEvent, "displayY", napiDisplayY);
    }
    napi_value napiWindowX = GetNamedProperty(env_, objValueClickEvent, "windowX");
    if (GetValueType(env_, napiWindowX) != napi_null) {
        napi_create_double(env_, globalOffset.GetX() / scale, &napiWindowX);
        napi_set_named_property(env_, objValueClickEvent, "windowX", napiWindowX);
    }
    napi_value napiWindowY = GetNamedProperty(env_, objValueClickEvent, "windowY");
    if (GetValueType(env_, napiWindowY) != napi_null) {
        napi_create_double(env_, globalOffset.GetY() / scale, &napiWindowY);
        napi_set_named_property(env_, objValueClickEvent, "windowY", napiWindowY);
    }
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::AddClickEventInfoTwo(napi_value objValueClickEvent, const ClickInfo& clickInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }

    double scale = Dimension(1.0, DimensionUnit::VP).ConvertToPx();
    if (NearZero(scale)) {
        scale = 1.0;
    }
    Offset globalOffset = clickInfo.GetGlobalLocation();
    Offset localOffset = clickInfo.GetLocalLocation();
    napi_value napiScreenX = GetNamedProperty(env_, objValueClickEvent, "screenX");
    if (GetValueType(env_, napiScreenX) != napi_null) {
        napi_create_double(env_, globalOffset.GetX() / scale, &napiScreenX);
        napi_set_named_property(env_, objValueClickEvent, "screenX", napiScreenX);
    }
    napi_value napiScreenY = GetNamedProperty(env_, objValueClickEvent, "screenY");
    if (GetValueType(env_, napiScreenY) != napi_null) {
        napi_create_double(env_, globalOffset.GetY() / scale, &napiScreenY);
        napi_set_named_property(env_, objValueClickEvent, "screenY", napiScreenY);
    }
    napi_value napiX = GetNamedProperty(env_, objValueClickEvent, "x");
    if (GetValueType(env_, napiX) != napi_null) {
        napi_create_double(env_, localOffset.GetX() / scale, &napiX);
        napi_set_named_property(env_, objValueClickEvent, "x", napiX);
    }
    napi_value napiY = GetNamedProperty(env_, objValueClickEvent, "y");
    if (GetValueType(env_, napiY) != napi_null) {
        napi_create_double(env_, localOffset.GetY() / scale, &napiY);
        napi_set_named_property(env_, objValueClickEvent, "y", napiY);
    }
    AddTargetObject(objValueClickEvent, clickInfo);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::AddTargetObject(napi_value objValueClickEvent, const ClickInfo& clickInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }

    napi_value napiTargetObject = nullptr;
    napi_create_object(env_, &napiTargetObject);
    const auto& localOffset = clickInfo.GetTarget().area.GetOffset();
    const auto& origin = clickInfo.GetTarget().origin;

    napi_value napiOffset = nullptr;
    napi_create_object(env_, &napiOffset);
    napi_value napiX = nullptr;
    napi_create_double(env_, localOffset.GetX().ConvertToVp(), &napiX);
    napi_set_named_property(env_, napiOffset, "x", napiX);
    napi_value napiY = nullptr;
    napi_create_double(env_, localOffset.GetY().ConvertToVp(), &napiY);
    napi_set_named_property(env_, napiOffset, "y", napiY);
    napi_set_named_property(env_, napiTargetObject, "position", napiOffset);

    napi_value napiGlobalOffset = nullptr;
    napi_create_object(env_, &napiGlobalOffset);
    napi_value napiGlobalX = nullptr;
    napi_create_double(env_, localOffset.GetX().ConvertToVp() + origin.GetX().ConvertToVp(),
        &napiGlobalX);
    napi_set_named_property(env_, napiGlobalOffset, "x", napiGlobalX);
    napi_value napiGlobalY = nullptr;
    napi_create_double(env_, localOffset.GetY().ConvertToVp() + origin.GetY().ConvertToVp(),
        &napiGlobalY);
    napi_set_named_property(env_, napiGlobalOffset, "y", napiGlobalY);
    napi_set_named_property(env_, napiTargetObject, "globalPosition", napiGlobalOffset);

    napi_value napiArea = nullptr;
    napi_create_object(env_, &napiArea);
    napi_value napiWidth = nullptr;
    napi_create_double(env_, clickInfo.GetTarget().area.GetWidth().ConvertToVp(), &napiWidth);
    napi_set_named_property(env_, napiArea, "width", napiWidth);
    napi_value napiHeight = nullptr;
    napi_create_double(env_, clickInfo.GetTarget().area.GetHeight().ConvertToVp(), &napiHeight);
    napi_set_named_property(env_, napiArea, "height", napiHeight);
    napi_set_named_property(env_, napiTargetObject, "area", napiArea);

    napi_set_named_property(env_, objValueClickEvent, "target", napiTargetObject);
    napi_close_handle_scope(env_, scope);
}

napi_value UIObserverListener::CreateNavDestinationInfoObj(const NG::NavDestinationInfo& info)
{
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value napiNavId = nullptr;
    napi_value napiName = nullptr;
    napi_value napiState = nullptr;
    napi_value napiIdx = nullptr;
    napi_value napiNavDesId = nullptr;
    napi_create_string_utf8(env_, info.navigationId.c_str(), info.navigationId.length(), &napiNavId);
    napi_create_string_utf8(env_, info.name.c_str(), info.name.length(), &napiName);
    napi_create_int32(env_, static_cast<int32_t>(info.state), &napiState);
    napi_create_int32(env_, info.index, &napiIdx);
    napi_create_string_utf8(env_, info.navDestinationId.c_str(), info.navDestinationId.length(), &napiNavDesId);
    napi_set_named_property(env_, objValue, "navigationId", napiNavId);
    napi_set_named_property(env_, objValue, "name", napiName);
    napi_set_named_property(env_, objValue, "state", napiState);
    napi_set_named_property(env_, objValue, "index", napiIdx);
    napi_set_named_property(env_, objValue, "param", info.param);
    napi_set_named_property(env_, objValue, "navDestinationId", napiNavDesId);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FIFTEEN)) {
        napi_value napiMode = nullptr;
        napi_value napiUniqueId = nullptr;
        napi_create_int32(env_, static_cast<int32_t>(info.mode), &napiMode);
        napi_create_int32(env_, static_cast<int32_t>(info.uniqueId), &napiUniqueId);
        napi_set_named_property(env_, objValue, "mode", napiMode);
        napi_set_named_property(env_, objValue, "uniqueId", napiUniqueId);
    }
    return objValue;
}

napi_value UIObserverListener::GetNapiCallback()
{
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    return callback;
}

bool UIObserverListener::NapiEqual(napi_value cb)
{
    bool isEquals = false;
    napi_strict_equals(env_, cb, GetNapiCallback(), &isEquals);
    return isEquals;
}
} // namespace OHOS::Ace::Napi
