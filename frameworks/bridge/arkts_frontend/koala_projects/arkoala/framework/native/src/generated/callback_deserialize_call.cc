/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define KOALA_INTEROP_MODULE NotSpecifiedInteropModule
#include "callback_kind.h"
#include "Serializers.h"
#include "callbacks.h"
#include "common-interop.h"
#include "arkoala_api_generated.h"
void deserializeAndCallAccessibilityCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_AccessibilityHoverEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_AccessibilityHoverEvent event = static_cast<Ark_AccessibilityHoverEvent>(thisDeserializer.readAccessibilityHoverEvent());
    _call(_resourceId, isHover, event);
}
void deserializeAndCallSyncAccessibilityCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_AccessibilityHoverEvent event)>(thisDeserializer.readPointer());
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_AccessibilityHoverEvent event = static_cast<Ark_AccessibilityHoverEvent>(thisDeserializer.readAccessibilityHoverEvent());
    _callSync(vmContext, _resourceId, isHover, event);
}
void deserializeAndCallAsyncCallback_image_PixelMap_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_PixelMap result)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_PixelMap result = static_cast<Ark_PixelMap>(thisDeserializer.readPixelMap());
    _call(_resourceId, result);
}
void deserializeAndCallSyncAsyncCallback_image_PixelMap_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PixelMap result)>(thisDeserializer.readPointer());
    Ark_PixelMap result = static_cast<Ark_PixelMap>(thisDeserializer.readPixelMap());
    _callSync(vmContext, _resourceId, result);
}
void deserializeAndCallButtonTriggerClickCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number xPos, const Ark_Number yPos)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number xPos = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number yPos = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, xPos, yPos);
}
void deserializeAndCallSyncButtonTriggerClickCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number xPos, const Ark_Number yPos)>(thisDeserializer.readPointer());
    Ark_Number xPos = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number yPos = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, xPos, yPos);
}
void deserializeAndCallCallback_Any_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CustomObject info)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_CustomObject info = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("Any"));
    _call(_resourceId, info);
}
void deserializeAndCallSyncCallback_Any_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CustomObject info)>(thisDeserializer.readPointer());
    Ark_CustomObject info = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("Any"));
    _callSync(vmContext, _resourceId, info);
}
void deserializeAndCallCallback_Area_Area_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Area oldValue, const Ark_Area newValue)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Area oldValue = thisDeserializer.readArea();
    Ark_Area newValue = thisDeserializer.readArea();
    _call(_resourceId, oldValue, newValue);
}
void deserializeAndCallSyncCallback_Area_Area_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Area oldValue, const Ark_Area newValue)>(thisDeserializer.readPointer());
    Ark_Area oldValue = thisDeserializer.readArea();
    Ark_Area newValue = thisDeserializer.readArea();
    _callSync(vmContext, _resourceId, oldValue, newValue);
}
void deserializeAndCallCallback_Array_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_Number input)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int32 input_buf_length = thisDeserializer.readInt32();
    Array_Number input_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(input_buf)>::type,
        std::decay<decltype(*input_buf.array)>::type>(&input_buf, input_buf_length);
    for (int input_buf_i = 0; input_buf_i < input_buf_length; input_buf_i++) {
        input_buf.array[input_buf_i] = static_cast<Ark_Number>(thisDeserializer.readNumber());
    }
    Array_Number input = input_buf;
    _call(_resourceId, input);
}
void deserializeAndCallSyncCallback_Array_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_Number input)>(thisDeserializer.readPointer());
    const Ark_Int32 input_buf_length = thisDeserializer.readInt32();
    Array_Number input_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(input_buf)>::type,
        std::decay<decltype(*input_buf.array)>::type>(&input_buf, input_buf_length);
    for (int input_buf_i = 0; input_buf_i < input_buf_length; input_buf_i++) {
        input_buf.array[input_buf_i] = static_cast<Ark_Number>(thisDeserializer.readNumber());
    }
    Array_Number input = input_buf;
    _callSync(vmContext, _resourceId, input);
}
void deserializeAndCallCallback_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_String value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int32 value_buf_length = thisDeserializer.readInt32();
    Array_String value_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(value_buf)>::type,
        std::decay<decltype(*value_buf.array)>::type>(&value_buf, value_buf_length);
    for (int value_buf_i = 0; value_buf_i < value_buf_length; value_buf_i++) {
        value_buf.array[value_buf_i] = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Array_String value = value_buf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Array_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_String value)>(thisDeserializer.readPointer());
    const Ark_Int32 value_buf_length = thisDeserializer.readInt32();
    Array_String value_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(value_buf)>::type,
        std::decay<decltype(*value_buf.array)>::type>(&value_buf, value_buf_length);
    for (int value_buf_i = 0; value_buf_i < value_buf_length; value_buf_i++) {
        value_buf.array[value_buf_i] = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Array_String value = value_buf;
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_TouchTestInfo value, const Callback_TouchResult_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int32 value_buf_length = thisDeserializer.readInt32();
    Array_TouchTestInfo value_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(value_buf)>::type,
        std::decay<decltype(*value_buf.array)>::type>(&value_buf, value_buf_length);
    for (int value_buf_i = 0; value_buf_i < value_buf_length; value_buf_i++) {
        value_buf.array[value_buf_i] = thisDeserializer.readTouchTestInfo();
    }
    Array_TouchTestInfo value = value_buf;
    Callback_TouchResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_TouchResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_TouchResult_Void))))};
    _call(_resourceId, value, _continuation);
}
void deserializeAndCallSyncCallback_Array_TouchTestInfo_TouchResult(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_TouchTestInfo value, const Callback_TouchResult_Void continuation)>(thisDeserializer.readPointer());
    const Ark_Int32 value_buf_length = thisDeserializer.readInt32();
    Array_TouchTestInfo value_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(value_buf)>::type,
        std::decay<decltype(*value_buf.array)>::type>(&value_buf, value_buf_length);
    for (int value_buf_i = 0; value_buf_i < value_buf_length; value_buf_i++) {
        value_buf.array[value_buf_i] = thisDeserializer.readTouchTestInfo();
    }
    Array_TouchTestInfo value = value_buf;
    Callback_TouchResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_TouchResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_TouchResult_Void))))};
    _callSync(vmContext, _resourceId, value, _continuation);
}
void deserializeAndCallCallback_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, _continuation);
}
void deserializeAndCallSyncCallback_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, _continuation);
}
void deserializeAndCallCallback_Boolean_HoverEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_HoverEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(thisDeserializer.readHoverEvent());
    _call(_resourceId, isHover, event);
}
void deserializeAndCallSyncCallback_Boolean_HoverEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_HoverEvent event)>(thisDeserializer.readPointer());
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(thisDeserializer.readHoverEvent());
    _callSync(vmContext, _resourceId, isHover, event);
}
void deserializeAndCallCallback_Boolean_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean parameter = thisDeserializer.readBoolean();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_Boolean_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointer());
    Ark_Boolean parameter = thisDeserializer.readBoolean();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_CalendarRequestedData_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CalendarRequestedData event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_CalendarRequestedData event = thisDeserializer.readCalendarRequestedData();
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_CalendarRequestedData_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CalendarRequestedData event)>(thisDeserializer.readPointer());
    Ark_CalendarRequestedData event = thisDeserializer.readCalendarRequestedData();
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_CalendarSelectedDate_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CalendarSelectedDate event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_CalendarSelectedDate event = thisDeserializer.readCalendarSelectedDate();
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_CalendarSelectedDate_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CalendarSelectedDate event)>(thisDeserializer.readPointer());
    Ark_CalendarSelectedDate event = thisDeserializer.readCalendarSelectedDate();
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_ClickEvent_LocationButtonOnClickResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ClickEvent event, Ark_LocationButtonOnClickResult result)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(thisDeserializer.readClickEvent());
    Ark_LocationButtonOnClickResult result = static_cast<Ark_LocationButtonOnClickResult>(thisDeserializer.readInt32());
    _call(_resourceId, event, result);
}
void deserializeAndCallSyncCallback_ClickEvent_LocationButtonOnClickResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ClickEvent event, Ark_LocationButtonOnClickResult result)>(thisDeserializer.readPointer());
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(thisDeserializer.readClickEvent());
    Ark_LocationButtonOnClickResult result = static_cast<Ark_LocationButtonOnClickResult>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, event, result);
}
void deserializeAndCallCallback_ClickEvent_PasteButtonOnClickResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ClickEvent event, Ark_PasteButtonOnClickResult result)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(thisDeserializer.readClickEvent());
    Ark_PasteButtonOnClickResult result = static_cast<Ark_PasteButtonOnClickResult>(thisDeserializer.readInt32());
    _call(_resourceId, event, result);
}
void deserializeAndCallSyncCallback_ClickEvent_PasteButtonOnClickResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ClickEvent event, Ark_PasteButtonOnClickResult result)>(thisDeserializer.readPointer());
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(thisDeserializer.readClickEvent());
    Ark_PasteButtonOnClickResult result = static_cast<Ark_PasteButtonOnClickResult>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, event, result);
}
void deserializeAndCallCallback_ClickEvent_SaveButtonOnClickResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ClickEvent event, Ark_SaveButtonOnClickResult result)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(thisDeserializer.readClickEvent());
    Ark_SaveButtonOnClickResult result = static_cast<Ark_SaveButtonOnClickResult>(thisDeserializer.readInt32());
    _call(_resourceId, event, result);
}
void deserializeAndCallSyncCallback_ClickEvent_SaveButtonOnClickResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ClickEvent event, Ark_SaveButtonOnClickResult result)>(thisDeserializer.readPointer());
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(thisDeserializer.readClickEvent());
    Ark_SaveButtonOnClickResult result = static_cast<Ark_SaveButtonOnClickResult>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, event, result);
}
void deserializeAndCallCallback_ClickEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ClickEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(thisDeserializer.readClickEvent());
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_ClickEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ClickEvent event)>(thisDeserializer.readPointer());
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(thisDeserializer.readClickEvent());
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_ComputedBarAttribute_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ComputedBarAttribute value = thisDeserializer.readComputedBarAttribute();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_ComputedBarAttribute_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(thisDeserializer.readPointer());
    Ark_ComputedBarAttribute value = thisDeserializer.readComputedBarAttribute();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_CopyEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CopyEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_CopyEvent parameter = thisDeserializer.readCopyEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_CopyEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CopyEvent parameter)>(thisDeserializer.readPointer());
    Ark_CopyEvent parameter = thisDeserializer.readCopyEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_CustomBuilder_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const CustomNodeBuilder value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    CustomNodeBuilder value = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_CustomNodeBuilder)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_CustomNodeBuilder))))};
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_CustomBuilder_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const CustomNodeBuilder value)>(thisDeserializer.readPointer());
    CustomNodeBuilder value = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_CustomNodeBuilder)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_CustomNodeBuilder))))};
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_CutEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CutEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_CutEvent parameter = thisDeserializer.readCutEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_CutEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CutEvent parameter)>(thisDeserializer.readPointer());
    Ark_CutEvent parameter = thisDeserializer.readCutEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_Date_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Date parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Date parameter = thisDeserializer.readInt64();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_Date_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Date parameter)>(thisDeserializer.readPointer());
    Ark_Date parameter = thisDeserializer.readInt64();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_DatePickerResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DatePickerResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DatePickerResult value = thisDeserializer.readDatePickerResult();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_DatePickerResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DatePickerResult value)>(thisDeserializer.readPointer());
    Ark_DatePickerResult value = thisDeserializer.readDatePickerResult();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_DeleteValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DeleteValue parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DeleteValue parameter = thisDeserializer.readDeleteValue();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_DeleteValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DeleteValue parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_DeleteValue parameter = thisDeserializer.readDeleteValue();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_DeleteValue_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DeleteValue parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DeleteValue parameter = thisDeserializer.readDeleteValue();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_DeleteValue_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DeleteValue parameter)>(thisDeserializer.readPointer());
    Ark_DeleteValue parameter = thisDeserializer.readDeleteValue();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_DismissContentCoverAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DismissContentCoverAction parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DismissContentCoverAction parameter = thisDeserializer.readDismissContentCoverAction();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_DismissContentCoverAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DismissContentCoverAction parameter)>(thisDeserializer.readPointer());
    Ark_DismissContentCoverAction parameter = thisDeserializer.readDismissContentCoverAction();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_DismissDialogAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DismissDialogAction parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DismissDialogAction parameter = thisDeserializer.readDismissDialogAction();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_DismissDialogAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DismissDialogAction parameter)>(thisDeserializer.readPointer());
    Ark_DismissDialogAction parameter = thisDeserializer.readDismissDialogAction();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_DismissPopupAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DismissPopupAction parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DismissPopupAction parameter = thisDeserializer.readDismissPopupAction();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_DismissPopupAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DismissPopupAction parameter)>(thisDeserializer.readPointer());
    Ark_DismissPopupAction parameter = thisDeserializer.readDismissPopupAction();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_DismissSheetAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DismissSheetAction parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DismissSheetAction parameter = thisDeserializer.readDismissSheetAction();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_DismissSheetAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DismissSheetAction parameter)>(thisDeserializer.readPointer());
    Ark_DismissSheetAction parameter = thisDeserializer.readDismissSheetAction();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_DragEvent_String_Union_CustomBuilder_DragItemInfo(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams, const Callback_Union_CustomBuilder_DragItemInfo_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DragEvent event = static_cast<Ark_DragEvent>(thisDeserializer.readDragEvent());
    const auto extraParams_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParams_buf = {};
    extraParams_buf.tag = extraParams_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_buf_runtimeType))
    {
        extraParams_buf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParams_buf;
    Callback_Union_CustomBuilder_DragItemInfo_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_CustomBuilder_DragItemInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_CustomBuilder_DragItemInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void))))};
    _call(_resourceId, event, extraParams, _continuation);
}
void deserializeAndCallSyncCallback_DragEvent_String_Union_CustomBuilder_DragItemInfo(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams, const Callback_Union_CustomBuilder_DragItemInfo_Void continuation)>(thisDeserializer.readPointer());
    Ark_DragEvent event = static_cast<Ark_DragEvent>(thisDeserializer.readDragEvent());
    const auto extraParams_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParams_buf = {};
    extraParams_buf.tag = extraParams_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_buf_runtimeType))
    {
        extraParams_buf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParams_buf;
    Callback_Union_CustomBuilder_DragItemInfo_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_CustomBuilder_DragItemInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_CustomBuilder_DragItemInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void))))};
    _callSync(vmContext, _resourceId, event, extraParams, _continuation);
}
void deserializeAndCallCallback_DragEvent_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DragEvent event = static_cast<Ark_DragEvent>(thisDeserializer.readDragEvent());
    const auto extraParams_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParams_buf = {};
    extraParams_buf.tag = extraParams_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_buf_runtimeType))
    {
        extraParams_buf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParams_buf;
    _call(_resourceId, event, extraParams);
}
void deserializeAndCallSyncCallback_DragEvent_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams)>(thisDeserializer.readPointer());
    Ark_DragEvent event = static_cast<Ark_DragEvent>(thisDeserializer.readDragEvent());
    const auto extraParams_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParams_buf = {};
    extraParams_buf.tag = extraParams_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_buf_runtimeType))
    {
        extraParams_buf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParams_buf;
    _callSync(vmContext, _resourceId, event, extraParams);
}
void deserializeAndCallCallback_EnterKeyType_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_EnterKeyType enterKey)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    _call(_resourceId, enterKey);
}
void deserializeAndCallSyncCallback_EnterKeyType_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_EnterKeyType enterKey)>(thisDeserializer.readPointer());
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, enterKey);
}
void deserializeAndCallCallback_Extender_OnFinish(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncCallback_Extender_OnFinish(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    _callSync(vmContext, _resourceId);
}
void deserializeAndCallCallback_Extender_OnProgress(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float32 value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Float32 value = thisDeserializer.readFloat32();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Extender_OnProgress(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float32 value)>(thisDeserializer.readPointer());
    Ark_Float32 value = thisDeserializer.readFloat32();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_FormCallbackInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_FormCallbackInfo parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_FormCallbackInfo parameter = thisDeserializer.readFormCallbackInfo();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_FormCallbackInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_FormCallbackInfo parameter)>(thisDeserializer.readPointer());
    Ark_FormCallbackInfo parameter = thisDeserializer.readFormCallbackInfo();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_FullscreenInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_FullscreenInfo parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_FullscreenInfo parameter = thisDeserializer.readFullscreenInfo();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_FullscreenInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_FullscreenInfo parameter)>(thisDeserializer.readPointer());
    Ark_FullscreenInfo parameter = thisDeserializer.readFullscreenInfo();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_GestureEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_GestureEvent event = static_cast<Ark_GestureEvent>(thisDeserializer.readGestureEvent());
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_GestureEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureEvent event)>(thisDeserializer.readPointer());
    Ark_GestureEvent event = static_cast<Ark_GestureEvent>(thisDeserializer.readGestureEvent());
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureInfo gestureInfo, const Ark_BaseGestureEvent event, const Callback_GestureJudgeResult_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_GestureInfo gestureInfo = thisDeserializer.readGestureInfo();
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(thisDeserializer.readBaseGestureEvent());
    Callback_GestureJudgeResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureJudgeResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureJudgeResult_Void))))};
    _call(_resourceId, gestureInfo, event, _continuation);
}
void deserializeAndCallSyncCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureInfo gestureInfo, const Ark_BaseGestureEvent event, const Callback_GestureJudgeResult_Void continuation)>(thisDeserializer.readPointer());
    Ark_GestureInfo gestureInfo = thisDeserializer.readGestureInfo();
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(thisDeserializer.readBaseGestureEvent());
    Callback_GestureJudgeResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureJudgeResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureJudgeResult_Void))))};
    _callSync(vmContext, _resourceId, gestureInfo, event, _continuation);
}
void deserializeAndCallCallback_GestureJudgeResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_GestureJudgeResult value = static_cast<Ark_GestureJudgeResult>(thisDeserializer.readInt32());
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_GestureJudgeResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointer());
    Ark_GestureJudgeResult value = static_cast<Ark_GestureJudgeResult>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_GestureRecognizer_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_GestureRecognizer value = static_cast<Ark_GestureRecognizer>(thisDeserializer.readGestureRecognizer());
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_GestureRecognizer_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointer());
    Ark_GestureRecognizer value = static_cast<Ark_GestureRecognizer>(thisDeserializer.readGestureRecognizer());
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_HitTestMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_HitTestMode value = static_cast<Ark_HitTestMode>(thisDeserializer.readInt32());
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_HitTestMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointer());
    Ark_HitTestMode value = static_cast<Ark_HitTestMode>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_InsertValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_InsertValue parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_InsertValue parameter = thisDeserializer.readInsertValue();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_InsertValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_InsertValue parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_InsertValue parameter = thisDeserializer.readInsertValue();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_InsertValue_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_InsertValue parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_InsertValue parameter = thisDeserializer.readInsertValue();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_InsertValue_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_InsertValue parameter)>(thisDeserializer.readPointer());
    Ark_InsertValue parameter = thisDeserializer.readInsertValue();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_IsolatedComponentAttribute_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_IsolatedComponentAttribute value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_IsolatedComponentAttribute value = thisDeserializer.readIsolatedComponentAttribute();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_IsolatedComponentAttribute_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_IsolatedComponentAttribute value)>(thisDeserializer.readPointer());
    Ark_IsolatedComponentAttribute value = thisDeserializer.readIsolatedComponentAttribute();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_ItemDragInfo_Number_Number_Boolean_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Number itemIndex, const Ark_Number insertIndex, const Ark_Boolean isSuccess)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = thisDeserializer.readItemDragInfo();
    Ark_Number itemIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number insertIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Boolean isSuccess = thisDeserializer.readBoolean();
    _call(_resourceId, event, itemIndex, insertIndex, isSuccess);
}
void deserializeAndCallSyncCallback_ItemDragInfo_Number_Number_Boolean_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Number itemIndex, const Ark_Number insertIndex, const Ark_Boolean isSuccess)>(thisDeserializer.readPointer());
    Ark_ItemDragInfo event = thisDeserializer.readItemDragInfo();
    Ark_Number itemIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number insertIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Boolean isSuccess = thisDeserializer.readBoolean();
    _callSync(vmContext, _resourceId, event, itemIndex, insertIndex, isSuccess);
}
void deserializeAndCallCallback_ItemDragInfo_Number_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Number itemIndex, const Ark_Number insertIndex)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = thisDeserializer.readItemDragInfo();
    Ark_Number itemIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number insertIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, event, itemIndex, insertIndex);
}
void deserializeAndCallSyncCallback_ItemDragInfo_Number_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Number itemIndex, const Ark_Number insertIndex)>(thisDeserializer.readPointer());
    Ark_ItemDragInfo event = thisDeserializer.readItemDragInfo();
    Ark_Number itemIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number insertIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, event, itemIndex, insertIndex);
}
void deserializeAndCallCallback_ItemDragInfo_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Number itemIndex)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = thisDeserializer.readItemDragInfo();
    Ark_Number itemIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, event, itemIndex);
}
void deserializeAndCallSyncCallback_ItemDragInfo_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Number itemIndex)>(thisDeserializer.readPointer());
    Ark_ItemDragInfo event = thisDeserializer.readItemDragInfo();
    Ark_Number itemIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, event, itemIndex);
}
void deserializeAndCallCallback_ItemDragInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = thisDeserializer.readItemDragInfo();
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_ItemDragInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event)>(thisDeserializer.readPointer());
    Ark_ItemDragInfo event = thisDeserializer.readItemDragInfo();
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_KeyEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_KeyEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_KeyEvent parameter = static_cast<Ark_KeyEvent>(thisDeserializer.readKeyEvent());
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_KeyEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_KeyEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_KeyEvent parameter = static_cast<Ark_KeyEvent>(thisDeserializer.readKeyEvent());
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_KeyEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_KeyEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_KeyEvent event = static_cast<Ark_KeyEvent>(thisDeserializer.readKeyEvent());
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_KeyEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_KeyEvent event)>(thisDeserializer.readPointer());
    Ark_KeyEvent event = static_cast<Ark_KeyEvent>(thisDeserializer.readKeyEvent());
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_Literal_Boolean_isVisible_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Literal_Boolean_isVisible event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Literal_Boolean_isVisible event_buf = {};
    event_buf.isVisible = thisDeserializer.readBoolean();
    Ark_Literal_Boolean_isVisible event = event_buf;
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_Literal_Boolean_isVisible_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Literal_Boolean_isVisible event)>(thisDeserializer.readPointer());
    Ark_Literal_Boolean_isVisible event_buf = {};
    event_buf.isVisible = thisDeserializer.readBoolean();
    Ark_Literal_Boolean_isVisible event = event_buf;
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_Literal_Function_handler_Object_error_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Literal_Function_handler_Object_error event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Literal_Function_handler_Object_error event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        Ark_Literal_Function_handler_Object_error event_buf_ = {};
        event_buf_.handler = static_cast<Ark_Function>(thisDeserializer.readFunction());
        event_buf_.error = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("Object"));
        event_buf.value = event_buf_;
    }
    Opt_Literal_Function_handler_Object_error event = event_buf;
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_Literal_Function_handler_Object_error_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Literal_Function_handler_Object_error event)>(thisDeserializer.readPointer());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Literal_Function_handler_Object_error event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        Ark_Literal_Function_handler_Object_error event_buf_ = {};
        event_buf_.handler = static_cast<Ark_Function>(thisDeserializer.readFunction());
        event_buf_.error = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("Object"));
        event_buf.value = event_buf_;
    }
    Opt_Literal_Function_handler_Object_error event = event_buf;
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_Literal_Number_code_Want_want_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Literal_Number_code_Want_want parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Literal_Number_code_Want_want parameter_buf = {};
    parameter_buf.code = static_cast<Ark_Number>(thisDeserializer.readNumber());
    const auto parameter_buf_want_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Want parameter_buf_want_buf = {};
    parameter_buf_want_buf.tag = parameter_buf_want_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (parameter_buf_want_buf_runtimeType))
    {
        parameter_buf_want_buf.value = thisDeserializer.readWant();
    }
    parameter_buf.want = parameter_buf_want_buf;
    Ark_Literal_Number_code_Want_want parameter = parameter_buf;
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_Literal_Number_code_Want_want_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Literal_Number_code_Want_want parameter)>(thisDeserializer.readPointer());
    Ark_Literal_Number_code_Want_want parameter_buf = {};
    parameter_buf.code = static_cast<Ark_Number>(thisDeserializer.readNumber());
    const auto parameter_buf_want_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Want parameter_buf_want_buf = {};
    parameter_buf_want_buf.tag = parameter_buf_want_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (parameter_buf_want_buf_runtimeType))
    {
        parameter_buf_want_buf.value = thisDeserializer.readWant();
    }
    parameter_buf.want = parameter_buf_want_buf;
    Ark_Literal_Number_code_Want_want parameter = parameter_buf;
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_Literal_Number_errcode_String_msg_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Literal_Number_errcode_String_msg info)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Literal_Number_errcode_String_msg info_buf = {};
    info_buf.errcode = static_cast<Ark_Number>(thisDeserializer.readNumber());
    info_buf.msg = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_Literal_Number_errcode_String_msg info = info_buf;
    _call(_resourceId, info);
}
void deserializeAndCallSyncCallback_Literal_Number_errcode_String_msg_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Literal_Number_errcode_String_msg info)>(thisDeserializer.readPointer());
    Ark_Literal_Number_errcode_String_msg info_buf = {};
    info_buf.errcode = static_cast<Ark_Number>(thisDeserializer.readNumber());
    info_buf.msg = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_Literal_Number_errcode_String_msg info = info_buf;
    _callSync(vmContext, _resourceId, info);
}
void deserializeAndCallCallback_Literal_Number_offsetRemain_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Literal_Number_offsetRemain value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Literal_Number_offsetRemain value_buf = {};
    value_buf.offsetRemain = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Literal_Number_offsetRemain value = value_buf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Literal_Number_offsetRemain_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Literal_Number_offsetRemain value)>(thisDeserializer.readPointer());
    Ark_Literal_Number_offsetRemain value_buf = {};
    value_buf.offsetRemain = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Literal_Number_offsetRemain value = value_buf;
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Literal_Object_detail_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Literal_Object_detail event, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Literal_Object_detail event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        Ark_Literal_Object_detail event_buf_ = {};
        event_buf_.detail = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("Object"));
        event_buf.value = event_buf_;
    }
    Opt_Literal_Object_detail event = event_buf;
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, event, _continuation);
}
void deserializeAndCallSyncCallback_Literal_Object_detail_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Literal_Object_detail event, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Literal_Object_detail event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        Ark_Literal_Object_detail event_buf_ = {};
        event_buf_.detail = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("Object"));
        event_buf.value = event_buf_;
    }
    Opt_Literal_Object_detail event = event_buf;
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, event, _continuation);
}
void deserializeAndCallCallback_Literal_String_plainText_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Literal_String_plainText selectedText)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Literal_String_plainText selectedText_buf = {};
    selectedText_buf.plainText = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_Literal_String_plainText selectedText = selectedText_buf;
    _call(_resourceId, selectedText);
}
void deserializeAndCallSyncCallback_Literal_String_plainText_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Literal_String_plainText selectedText)>(thisDeserializer.readPointer());
    Ark_Literal_String_plainText selectedText_buf = {};
    selectedText_buf.plainText = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_Literal_String_plainText selectedText = selectedText_buf;
    _callSync(vmContext, _resourceId, selectedText);
}
void deserializeAndCallCallback_MouseEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_MouseEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_MouseEvent event = static_cast<Ark_MouseEvent>(thisDeserializer.readMouseEvent());
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_MouseEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_MouseEvent event)>(thisDeserializer.readPointer());
    Ark_MouseEvent event = static_cast<Ark_MouseEvent>(thisDeserializer.readMouseEvent());
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_NativeEmbedDataInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativeEmbedDataInfo event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativeEmbedDataInfo event = thisDeserializer.readNativeEmbedDataInfo();
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_NativeEmbedDataInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativeEmbedDataInfo event)>(thisDeserializer.readPointer());
    Ark_NativeEmbedDataInfo event = thisDeserializer.readNativeEmbedDataInfo();
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_NativeEmbedTouchInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativeEmbedTouchInfo event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativeEmbedTouchInfo event = thisDeserializer.readNativeEmbedTouchInfo();
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_NativeEmbedTouchInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativeEmbedTouchInfo event)>(thisDeserializer.readPointer());
    Ark_NativeEmbedTouchInfo event = thisDeserializer.readNativeEmbedTouchInfo();
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_NavDestinationContext_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NavDestinationContext parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NavDestinationContext parameter = static_cast<Ark_NavDestinationContext>(thisDeserializer.readNavDestinationContext());
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_NavDestinationContext_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NavDestinationContext parameter)>(thisDeserializer.readPointer());
    Ark_NavDestinationContext parameter = static_cast<Ark_NavDestinationContext>(thisDeserializer.readNavDestinationContext());
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_NavigationMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_NavigationMode mode)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NavigationMode mode = static_cast<Ark_NavigationMode>(thisDeserializer.readInt32());
    _call(_resourceId, mode);
}
void deserializeAndCallSyncCallback_NavigationMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_NavigationMode mode)>(thisDeserializer.readPointer());
    Ark_NavigationMode mode = static_cast<Ark_NavigationMode>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, mode);
}
void deserializeAndCallCallback_NavigationTitleMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_NavigationTitleMode titleMode)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NavigationTitleMode titleMode = static_cast<Ark_NavigationTitleMode>(thisDeserializer.readInt32());
    _call(_resourceId, titleMode);
}
void deserializeAndCallSyncCallback_NavigationTitleMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_NavigationTitleMode titleMode)>(thisDeserializer.readPointer());
    Ark_NavigationTitleMode titleMode = static_cast<Ark_NavigationTitleMode>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, titleMode);
}
void deserializeAndCallCallback_NavigationTransitionProxy_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NavigationTransitionProxy transitionProxy)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NavigationTransitionProxy transitionProxy = static_cast<Ark_NavigationTransitionProxy>(thisDeserializer.readNavigationTransitionProxy());
    _call(_resourceId, transitionProxy);
}
void deserializeAndCallSyncCallback_NavigationTransitionProxy_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NavigationTransitionProxy transitionProxy)>(thisDeserializer.readPointer());
    Ark_NavigationTransitionProxy transitionProxy = static_cast<Ark_NavigationTransitionProxy>(thisDeserializer.readNavigationTransitionProxy());
    _callSync(vmContext, _resourceId, transitionProxy);
}
void deserializeAndCallCallback_Number_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, index, _continuation);
}
void deserializeAndCallSyncCallback_Number_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, index, _continuation);
}
void deserializeAndCallCallback_Number_Number_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number from, const Ark_Number to, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number from = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number to = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, from, to, _continuation);
}
void deserializeAndCallSyncCallback_Number_Number_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number from, const Ark_Number to, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number from = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number to = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, from, to, _continuation);
}
void deserializeAndCallCallback_Number_Number_ComputedBarAttribute(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number offset, const Callback_ComputedBarAttribute_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number offset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_ComputedBarAttribute_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_ComputedBarAttribute_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_ComputedBarAttribute_Void))))};
    _call(_resourceId, index, offset, _continuation);
}
void deserializeAndCallSyncCallback_Number_Number_ComputedBarAttribute(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number offset, const Callback_ComputedBarAttribute_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number offset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_ComputedBarAttribute_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_ComputedBarAttribute_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_ComputedBarAttribute_Void))))};
    _callSync(vmContext, _resourceId, index, offset, _continuation);
}
void deserializeAndCallCallback_Number_Number_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number start, const Ark_Number end, const Ark_Number center)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number start = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number end = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number center = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, start, end, center);
}
void deserializeAndCallSyncCallback_Number_Number_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number start, const Ark_Number end, const Ark_Number center)>(thisDeserializer.readPointer());
    Ark_Number start = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number end = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number center = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, start, end, center);
}
void deserializeAndCallCallback_Number_Number_PanelMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number width, const Ark_Number height, Ark_PanelMode mode)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number width = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number height = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_PanelMode mode = static_cast<Ark_PanelMode>(thisDeserializer.readInt32());
    _call(_resourceId, width, height, mode);
}
void deserializeAndCallSyncCallback_Number_Number_PanelMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number width, const Ark_Number height, Ark_PanelMode mode)>(thisDeserializer.readPointer());
    Ark_Number width = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number height = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_PanelMode mode = static_cast<Ark_PanelMode>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, width, height, mode);
}
void deserializeAndCallCallback_Number_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number first, const Ark_Number last)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number first = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number last = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, first, last);
}
void deserializeAndCallSyncCallback_Number_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number first, const Ark_Number last)>(thisDeserializer.readPointer());
    Ark_Number first = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number last = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, first, last);
}
void deserializeAndCallCallback_Number_ScrollState_Literal_Number_offsetRemain(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number offset, Ark_ScrollState state, const Callback_Literal_Number_offsetRemain_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number offset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState state = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Callback_Literal_Number_offsetRemain_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Literal_Number_offsetRemain value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Literal_Number_offsetRemain_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Literal_Number_offsetRemain value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Literal_Number_offsetRemain_Void))))};
    _call(_resourceId, offset, state, _continuation);
}
void deserializeAndCallSyncCallback_Number_ScrollState_Literal_Number_offsetRemain(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number offset, Ark_ScrollState state, const Callback_Literal_Number_offsetRemain_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number offset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState state = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Callback_Literal_Number_offsetRemain_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Literal_Number_offsetRemain value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Literal_Number_offsetRemain_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Literal_Number_offsetRemain value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Literal_Number_offsetRemain_Void))))};
    _callSync(vmContext, _resourceId, offset, state, _continuation);
}
void deserializeAndCallCallback_Number_SliderChangeMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number value, Ark_SliderChangeMode mode)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number value = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SliderChangeMode mode = static_cast<Ark_SliderChangeMode>(thisDeserializer.readInt32());
    _call(_resourceId, value, mode);
}
void deserializeAndCallSyncCallback_Number_SliderChangeMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number value, Ark_SliderChangeMode mode)>(thisDeserializer.readPointer());
    Ark_Number value = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SliderChangeMode mode = static_cast<Ark_SliderChangeMode>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, value, mode);
}
void deserializeAndCallCallback_Number_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_String value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    _call(_resourceId, index, value);
}
void deserializeAndCallSyncCallback_Number_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_String value)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    _callSync(vmContext, _resourceId, index, value);
}
void deserializeAndCallCallback_Number_Tuple_Number_Number(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Callback_Tuple_Number_Number_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Tuple_Number_Number_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Tuple_Number_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Tuple_Number_Number_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_Number_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Tuple_Number_Number_Void))))};
    _call(_resourceId, index, _continuation);
}
void deserializeAndCallSyncCallback_Number_Tuple_Number_Number(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Callback_Tuple_Number_Number_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Tuple_Number_Number_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Tuple_Number_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Tuple_Number_Number_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_Number_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Tuple_Number_Number_Void))))};
    _callSync(vmContext, _resourceId, index, _continuation);
}
void deserializeAndCallCallback_Number_Tuple_Number_Number_Number_Number(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Callback_Tuple_Number_Number_Number_Number_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Tuple_Number_Number_Number_Number_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Tuple_Number_Number_Number_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Tuple_Number_Number_Number_Number_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_Number_Number_Number_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Tuple_Number_Number_Number_Number_Void))))};
    _call(_resourceId, index, _continuation);
}
void deserializeAndCallSyncCallback_Number_Tuple_Number_Number_Number_Number(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Callback_Tuple_Number_Number_Number_Number_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Tuple_Number_Number_Number_Number_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Tuple_Number_Number_Number_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Tuple_Number_Number_Number_Number_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_Number_Number_Number_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Tuple_Number_Number_Number_Number_Void))))};
    _callSync(vmContext, _resourceId, index, _continuation);
}
void deserializeAndCallCallback_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, index);
}
void deserializeAndCallSyncCallback_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, index);
}
void deserializeAndCallCallback_OffsetResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OffsetResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OffsetResult value = thisDeserializer.readOffsetResult();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_OffsetResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OffsetResult value)>(thisDeserializer.readPointer());
    Ark_OffsetResult value = thisDeserializer.readOffsetResult();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_ScrollResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ScrollResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ScrollResult value = thisDeserializer.readScrollResult();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_ScrollResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ScrollResult value)>(thisDeserializer.readPointer());
    Ark_ScrollResult value = thisDeserializer.readScrollResult();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_OnAlertEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnAlertEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnAlertEvent parameter = thisDeserializer.readOnAlertEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_OnAlertEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnAlertEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnAlertEvent parameter = thisDeserializer.readOnAlertEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_OnAudioStateChangedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnAudioStateChangedEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnAudioStateChangedEvent parameter = thisDeserializer.readOnAudioStateChangedEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnAudioStateChangedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnAudioStateChangedEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnAudioStateChangedEvent parameter = thisDeserializer.readOnAudioStateChangedEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnBeforeUnloadEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnBeforeUnloadEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnBeforeUnloadEvent parameter = thisDeserializer.readOnBeforeUnloadEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_OnBeforeUnloadEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnBeforeUnloadEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnBeforeUnloadEvent parameter = thisDeserializer.readOnBeforeUnloadEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_OnClientAuthenticationEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnClientAuthenticationEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnClientAuthenticationEvent parameter = thisDeserializer.readOnClientAuthenticationEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnClientAuthenticationEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnClientAuthenticationEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnClientAuthenticationEvent parameter = thisDeserializer.readOnClientAuthenticationEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnConfirmEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnConfirmEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnConfirmEvent parameter = thisDeserializer.readOnConfirmEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_OnConfirmEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnConfirmEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnConfirmEvent parameter = thisDeserializer.readOnConfirmEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_OnConsoleEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnConsoleEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnConsoleEvent parameter = thisDeserializer.readOnConsoleEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_OnConsoleEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnConsoleEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnConsoleEvent parameter = thisDeserializer.readOnConsoleEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_OnContextMenuShowEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnContextMenuShowEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnContextMenuShowEvent parameter = thisDeserializer.readOnContextMenuShowEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_OnContextMenuShowEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnContextMenuShowEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnContextMenuShowEvent parameter = thisDeserializer.readOnContextMenuShowEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_OnDataResubmittedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnDataResubmittedEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnDataResubmittedEvent parameter = thisDeserializer.readOnDataResubmittedEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnDataResubmittedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnDataResubmittedEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnDataResubmittedEvent parameter = thisDeserializer.readOnDataResubmittedEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnDownloadStartEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnDownloadStartEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnDownloadStartEvent parameter = thisDeserializer.readOnDownloadStartEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnDownloadStartEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnDownloadStartEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnDownloadStartEvent parameter = thisDeserializer.readOnDownloadStartEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnErrorReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnErrorReceiveEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnErrorReceiveEvent parameter = thisDeserializer.readOnErrorReceiveEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnErrorReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnErrorReceiveEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnErrorReceiveEvent parameter = thisDeserializer.readOnErrorReceiveEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnFaviconReceivedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnFaviconReceivedEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnFaviconReceivedEvent parameter = thisDeserializer.readOnFaviconReceivedEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnFaviconReceivedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnFaviconReceivedEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnFaviconReceivedEvent parameter = thisDeserializer.readOnFaviconReceivedEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnFirstContentfulPaintEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnFirstContentfulPaintEvent parameter = thisDeserializer.readOnFirstContentfulPaintEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnFirstContentfulPaintEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnFirstContentfulPaintEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnFirstContentfulPaintEvent parameter = thisDeserializer.readOnFirstContentfulPaintEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnGeolocationShowEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnGeolocationShowEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnGeolocationShowEvent parameter = thisDeserializer.readOnGeolocationShowEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnGeolocationShowEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnGeolocationShowEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnGeolocationShowEvent parameter = thisDeserializer.readOnGeolocationShowEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnHttpAuthRequestEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnHttpAuthRequestEvent parameter = thisDeserializer.readOnHttpAuthRequestEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_OnHttpAuthRequestEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnHttpAuthRequestEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnHttpAuthRequestEvent parameter = thisDeserializer.readOnHttpAuthRequestEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnHttpErrorReceiveEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnHttpErrorReceiveEvent parameter = thisDeserializer.readOnHttpErrorReceiveEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnHttpErrorReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnHttpErrorReceiveEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnHttpErrorReceiveEvent parameter = thisDeserializer.readOnHttpErrorReceiveEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnInterceptRequestEvent_WebResourceResponse(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnInterceptRequestEvent parameter, const Callback_WebResourceResponse_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnInterceptRequestEvent parameter = thisDeserializer.readOnInterceptRequestEvent();
    Callback_WebResourceResponse_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebResourceResponse value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_WebResourceResponse_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebResourceResponse value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_WebResourceResponse_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_OnInterceptRequestEvent_WebResourceResponse(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnInterceptRequestEvent parameter, const Callback_WebResourceResponse_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnInterceptRequestEvent parameter = thisDeserializer.readOnInterceptRequestEvent();
    Callback_WebResourceResponse_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebResourceResponse value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_WebResourceResponse_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebResourceResponse value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_WebResourceResponse_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnLoadInterceptEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnLoadInterceptEvent parameter = thisDeserializer.readOnLoadInterceptEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_OnLoadInterceptEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnLoadInterceptEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnLoadInterceptEvent parameter = thisDeserializer.readOnLoadInterceptEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_OnOverScrollEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnOverScrollEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnOverScrollEvent parameter = thisDeserializer.readOnOverScrollEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnOverScrollEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnOverScrollEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnOverScrollEvent parameter = thisDeserializer.readOnOverScrollEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnPageBeginEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnPageBeginEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnPageBeginEvent parameter = thisDeserializer.readOnPageBeginEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnPageBeginEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPageBeginEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnPageBeginEvent parameter = thisDeserializer.readOnPageBeginEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnPageEndEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnPageEndEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnPageEndEvent parameter = thisDeserializer.readOnPageEndEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnPageEndEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPageEndEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnPageEndEvent parameter = thisDeserializer.readOnPageEndEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnPageVisibleEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnPageVisibleEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnPageVisibleEvent parameter = thisDeserializer.readOnPageVisibleEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnPageVisibleEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPageVisibleEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnPageVisibleEvent parameter = thisDeserializer.readOnPageVisibleEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnPermissionRequestEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnPermissionRequestEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnPermissionRequestEvent parameter = thisDeserializer.readOnPermissionRequestEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnPermissionRequestEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPermissionRequestEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnPermissionRequestEvent parameter = thisDeserializer.readOnPermissionRequestEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnProgressChangeEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnProgressChangeEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnProgressChangeEvent parameter = thisDeserializer.readOnProgressChangeEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnProgressChangeEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnProgressChangeEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnProgressChangeEvent parameter = thisDeserializer.readOnProgressChangeEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnPromptEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnPromptEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnPromptEvent parameter = thisDeserializer.readOnPromptEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_OnPromptEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPromptEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnPromptEvent parameter = thisDeserializer.readOnPromptEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_OnRefreshAccessedHistoryEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnRefreshAccessedHistoryEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnRefreshAccessedHistoryEvent parameter = thisDeserializer.readOnRefreshAccessedHistoryEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnRefreshAccessedHistoryEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnRefreshAccessedHistoryEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnRefreshAccessedHistoryEvent parameter = thisDeserializer.readOnRefreshAccessedHistoryEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnRenderExitedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnRenderExitedEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnRenderExitedEvent parameter = thisDeserializer.readOnRenderExitedEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnRenderExitedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnRenderExitedEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnRenderExitedEvent parameter = thisDeserializer.readOnRenderExitedEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnResourceLoadEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnResourceLoadEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnResourceLoadEvent parameter = thisDeserializer.readOnResourceLoadEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnResourceLoadEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnResourceLoadEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnResourceLoadEvent parameter = thisDeserializer.readOnResourceLoadEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnScaleChangeEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnScaleChangeEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnScaleChangeEvent parameter = thisDeserializer.readOnScaleChangeEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnScaleChangeEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScaleChangeEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnScaleChangeEvent parameter = thisDeserializer.readOnScaleChangeEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnScreenCaptureRequestEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnScreenCaptureRequestEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnScreenCaptureRequestEvent parameter = thisDeserializer.readOnScreenCaptureRequestEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnScreenCaptureRequestEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScreenCaptureRequestEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnScreenCaptureRequestEvent parameter = thisDeserializer.readOnScreenCaptureRequestEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnScrollEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnScrollEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnScrollEvent parameter = thisDeserializer.readOnScrollEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnScrollEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScrollEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnScrollEvent parameter = thisDeserializer.readOnScrollEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnScrollFrameBeginHandlerResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnScrollFrameBeginHandlerResult value = thisDeserializer.readOnScrollFrameBeginHandlerResult();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_OnScrollFrameBeginHandlerResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(thisDeserializer.readPointer());
    Ark_OnScrollFrameBeginHandlerResult value = thisDeserializer.readOnScrollFrameBeginHandlerResult();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_OnSearchResultReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnSearchResultReceiveEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnSearchResultReceiveEvent parameter = thisDeserializer.readOnSearchResultReceiveEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnSearchResultReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnSearchResultReceiveEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnSearchResultReceiveEvent parameter = thisDeserializer.readOnSearchResultReceiveEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnShowFileSelectorEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnShowFileSelectorEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnShowFileSelectorEvent parameter = thisDeserializer.readOnShowFileSelectorEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_OnShowFileSelectorEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnShowFileSelectorEvent parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnShowFileSelectorEvent parameter = thisDeserializer.readOnShowFileSelectorEvent();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_OnSslErrorEventReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnSslErrorEventReceiveEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnSslErrorEventReceiveEvent parameter = thisDeserializer.readOnSslErrorEventReceiveEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnSslErrorEventReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnSslErrorEventReceiveEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnSslErrorEventReceiveEvent parameter = thisDeserializer.readOnSslErrorEventReceiveEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnTitleReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnTitleReceiveEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnTitleReceiveEvent parameter = thisDeserializer.readOnTitleReceiveEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnTitleReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnTitleReceiveEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnTitleReceiveEvent parameter = thisDeserializer.readOnTitleReceiveEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnTouchIconUrlReceivedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnTouchIconUrlReceivedEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnTouchIconUrlReceivedEvent parameter = thisDeserializer.readOnTouchIconUrlReceivedEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnTouchIconUrlReceivedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnTouchIconUrlReceivedEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnTouchIconUrlReceivedEvent parameter = thisDeserializer.readOnTouchIconUrlReceivedEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_OnWindowNewEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnWindowNewEvent parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnWindowNewEvent parameter = thisDeserializer.readOnWindowNewEvent();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_OnWindowNewEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnWindowNewEvent parameter)>(thisDeserializer.readPointer());
    Ark_OnWindowNewEvent parameter = thisDeserializer.readOnWindowNewEvent();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_Opt_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Array_String error)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_buf_runtimeType))
    {
        const Ark_Int32 error_buf__length = thisDeserializer.readInt32();
        Array_String error_buf_ = {};
        thisDeserializer.resizeArray<std::decay<decltype(error_buf_)>::type,
        std::decay<decltype(*error_buf_.array)>::type>(&error_buf_, error_buf__length);
        for (int error_buf__i = 0; error_buf__i < error_buf__length; error_buf__i++) {
            error_buf_.array[error_buf__i] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        error_buf.value = error_buf_;
    }
    Opt_Array_String error = error_buf;
    _call(_resourceId, error);
}
void deserializeAndCallSyncCallback_Opt_Array_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Array_String error)>(thisDeserializer.readPointer());
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_buf_runtimeType))
    {
        const Ark_Int32 error_buf__length = thisDeserializer.readInt32();
        Array_String error_buf_ = {};
        thisDeserializer.resizeArray<std::decay<decltype(error_buf_)>::type,
        std::decay<decltype(*error_buf_.array)>::type>(&error_buf_, error_buf__length);
        for (int error_buf__i = 0; error_buf__i < error_buf__length; error_buf__i++) {
            error_buf_.array[error_buf__i] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        error_buf.value = error_buf_;
    }
    Opt_Array_String error = error_buf;
    _callSync(vmContext, _resourceId, error);
}
void deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_NavigationAnimatedTransition value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_buf_runtimeType))
    {
        value_buf.value = thisDeserializer.readNavigationAnimatedTransition();
    }
    Opt_NavigationAnimatedTransition value = value_buf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_NavigationAnimatedTransition_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointer());
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_NavigationAnimatedTransition value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_buf_runtimeType))
    {
        value_buf.value = thisDeserializer.readNavigationAnimatedTransition();
    }
    Opt_NavigationAnimatedTransition value = value_buf;
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_StyledString value, const Opt_Array_String error)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_StyledString value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_buf_runtimeType))
    {
        value_buf.value = static_cast<Ark_StyledString>(thisDeserializer.readStyledString());
    }
    Opt_StyledString value = value_buf;
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_buf_runtimeType))
    {
        const Ark_Int32 error_buf__length = thisDeserializer.readInt32();
        Array_String error_buf_ = {};
        thisDeserializer.resizeArray<std::decay<decltype(error_buf_)>::type,
        std::decay<decltype(*error_buf_.array)>::type>(&error_buf_, error_buf__length);
        for (int error_buf__i = 0; error_buf__i < error_buf__length; error_buf__i++) {
            error_buf_.array[error_buf__i] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        error_buf.value = error_buf_;
    }
    Opt_Array_String error = error_buf;
    _call(_resourceId, value, error);
}
void deserializeAndCallSyncCallback_Opt_StyledString_Opt_Array_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_StyledString value, const Opt_Array_String error)>(thisDeserializer.readPointer());
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_StyledString value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_buf_runtimeType))
    {
        value_buf.value = static_cast<Ark_StyledString>(thisDeserializer.readStyledString());
    }
    Opt_StyledString value = value_buf;
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_buf_runtimeType))
    {
        const Ark_Int32 error_buf__length = thisDeserializer.readInt32();
        Array_String error_buf_ = {};
        thisDeserializer.resizeArray<std::decay<decltype(error_buf_)>::type,
        std::decay<decltype(*error_buf_.array)>::type>(&error_buf_, error_buf__length);
        for (int error_buf__i = 0; error_buf__i < error_buf__length; error_buf__i++) {
            error_buf_.array[error_buf__i] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        error_buf.value = error_buf_;
    }
    Opt_Array_String error = error_buf;
    _callSync(vmContext, _resourceId, value, error);
}
void deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_TabContentAnimatedTransition value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_buf_runtimeType))
    {
        value_buf.value = thisDeserializer.readTabContentAnimatedTransition();
    }
    Opt_TabContentAnimatedTransition value = value_buf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_TabContentAnimatedTransition_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(thisDeserializer.readPointer());
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_TabContentAnimatedTransition value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_buf_runtimeType))
    {
        value_buf.value = thisDeserializer.readTabContentAnimatedTransition();
    }
    Opt_TabContentAnimatedTransition value = value_buf;
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_PanelMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_PanelMode mode)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_PanelMode mode = static_cast<Ark_PanelMode>(thisDeserializer.readInt32());
    _call(_resourceId, mode);
}
void deserializeAndCallSyncCallback_PanelMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_PanelMode mode)>(thisDeserializer.readPointer());
    Ark_PanelMode mode = static_cast<Ark_PanelMode>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, mode);
}
void deserializeAndCallCallback_PlaybackInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_PlaybackInfo parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_PlaybackInfo parameter = thisDeserializer.readPlaybackInfo();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_PlaybackInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PlaybackInfo parameter)>(thisDeserializer.readPointer());
    Ark_PlaybackInfo parameter = thisDeserializer.readPlaybackInfo();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_Pointer_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer value = thisDeserializer.readPointer();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Pointer_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointer());
    Ark_NativePointer value = thisDeserializer.readPointer();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_PopInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_PopInfo parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_PopInfo parameter = thisDeserializer.readPopInfo();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_PopInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PopInfo parameter)>(thisDeserializer.readPointer());
    Ark_PopInfo parameter = thisDeserializer.readPopInfo();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_PreDragStatus_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_PreDragStatus parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_PreDragStatus parameter = static_cast<Ark_PreDragStatus>(thisDeserializer.readInt32());
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_PreDragStatus_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_PreDragStatus parameter)>(thisDeserializer.readPointer());
    Ark_PreDragStatus parameter = static_cast<Ark_PreDragStatus>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_PreparedInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_PreparedInfo parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_PreparedInfo parameter = thisDeserializer.readPreparedInfo();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_PreparedInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PreparedInfo parameter)>(thisDeserializer.readPointer());
    Ark_PreparedInfo parameter = thisDeserializer.readPreparedInfo();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_RangeUpdate(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_NativePointer mark, const Ark_Int32 end)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_NativePointer mark = thisDeserializer.readPointer();
    Ark_Int32 end = thisDeserializer.readInt32();
    _call(_resourceId, index, mark, end);
}
void deserializeAndCallSyncCallback_RangeUpdate(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_NativePointer mark, const Ark_Int32 end)>(thisDeserializer.readPointer());
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_NativePointer mark = thisDeserializer.readPointer();
    Ark_Int32 end = thisDeserializer.readInt32();
    _callSync(vmContext, _resourceId, index, mark, end);
}
void deserializeAndCallCallback_RefreshStatus_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_RefreshStatus state)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RefreshStatus state = static_cast<Ark_RefreshStatus>(thisDeserializer.readInt32());
    _call(_resourceId, state);
}
void deserializeAndCallSyncCallback_RefreshStatus_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_RefreshStatus state)>(thisDeserializer.readPointer());
    Ark_RefreshStatus state = static_cast<Ark_RefreshStatus>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, state);
}
void deserializeAndCallCallback_ResourceStr_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ResourceStr value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int8 value_buf_selector = thisDeserializer.readInt8();
    Ark_ResourceStr value_buf = {};
    value_buf.selector = value_buf_selector;
    if (value_buf_selector == 0) {
        value_buf.selector = 0;
        value_buf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (value_buf_selector == 1) {
        value_buf.selector = 1;
        value_buf.value1 = thisDeserializer.readResource();
    }
    else {
        INTEROP_FATAL("One of the branches for value_buf has to be chosen through deserialisation.");
    }
    Ark_ResourceStr value = static_cast<Ark_ResourceStr>(value_buf);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_ResourceStr_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ResourceStr value)>(thisDeserializer.readPointer());
    const Ark_Int8 value_buf_selector = thisDeserializer.readInt8();
    Ark_ResourceStr value_buf = {};
    value_buf.selector = value_buf_selector;
    if (value_buf_selector == 0) {
        value_buf.selector = 0;
        value_buf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (value_buf_selector == 1) {
        value_buf.selector = 1;
        value_buf.value1 = thisDeserializer.readResource();
    }
    else {
        INTEROP_FATAL("One of the branches for value_buf has to be chosen through deserialisation.");
    }
    Ark_ResourceStr value = static_cast<Ark_ResourceStr>(value_buf);
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_RichEditorChangeValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorChangeValue parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RichEditorChangeValue parameter = thisDeserializer.readRichEditorChangeValue();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_RichEditorChangeValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorChangeValue parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_RichEditorChangeValue parameter = thisDeserializer.readRichEditorChangeValue();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_RichEditorDeleteValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorDeleteValue parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RichEditorDeleteValue parameter = thisDeserializer.readRichEditorDeleteValue();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_RichEditorDeleteValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorDeleteValue parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_RichEditorDeleteValue parameter = thisDeserializer.readRichEditorDeleteValue();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_RichEditorInsertValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorInsertValue parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RichEditorInsertValue parameter = thisDeserializer.readRichEditorInsertValue();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_RichEditorInsertValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorInsertValue parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_RichEditorInsertValue parameter = thisDeserializer.readRichEditorInsertValue();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_RichEditorRange_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorRange parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RichEditorRange parameter = thisDeserializer.readRichEditorRange();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_RichEditorRange_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorRange parameter)>(thisDeserializer.readPointer());
    Ark_RichEditorRange parameter = thisDeserializer.readRichEditorRange();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_RichEditorSelection_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorSelection parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RichEditorSelection parameter = thisDeserializer.readRichEditorSelection();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_RichEditorSelection_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorSelection parameter)>(thisDeserializer.readPointer());
    Ark_RichEditorSelection parameter = thisDeserializer.readRichEditorSelection();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_RichEditorTextSpanResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorTextSpanResult parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RichEditorTextSpanResult parameter = thisDeserializer.readRichEditorTextSpanResult();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_RichEditorTextSpanResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorTextSpanResult parameter)>(thisDeserializer.readPointer());
    Ark_RichEditorTextSpanResult parameter = thisDeserializer.readRichEditorTextSpanResult();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_SheetDismiss_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SheetDismiss sheetDismiss)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SheetDismiss sheetDismiss = thisDeserializer.readSheetDismiss();
    _call(_resourceId, sheetDismiss);
}
void deserializeAndCallSyncCallback_SheetDismiss_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SheetDismiss sheetDismiss)>(thisDeserializer.readPointer());
    Ark_SheetDismiss sheetDismiss = thisDeserializer.readSheetDismiss();
    _callSync(vmContext, _resourceId, sheetDismiss);
}
void deserializeAndCallCallback_SheetType_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_SheetType parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SheetType parameter = static_cast<Ark_SheetType>(thisDeserializer.readInt32());
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_SheetType_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_SheetType parameter)>(thisDeserializer.readPointer());
    Ark_SheetType parameter = static_cast<Ark_SheetType>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_SpringBackAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SpringBackAction parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SpringBackAction parameter = thisDeserializer.readSpringBackAction();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_SpringBackAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SpringBackAction parameter)>(thisDeserializer.readPointer());
    Ark_SpringBackAction parameter = thisDeserializer.readSpringBackAction();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_String_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String value, const Ark_Number index)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, value, index);
}
void deserializeAndCallSyncCallback_String_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String value, const Ark_Number index)>(thisDeserializer.readPointer());
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, value, index);
}
void deserializeAndCallCallback_String_PasteEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String value, const Ark_PasteEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_PasteEvent event = thisDeserializer.readPasteEvent();
    _call(_resourceId, value, event);
}
void deserializeAndCallSyncCallback_String_PasteEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String value, const Ark_PasteEvent event)>(thisDeserializer.readPointer());
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_PasteEvent event = thisDeserializer.readPasteEvent();
    _callSync(vmContext, _resourceId, value, event);
}
void deserializeAndCallCallback_String_Unknown_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String name, const Ark_CustomObject param)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String name = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_CustomObject param = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("Any"));
    _call(_resourceId, name, param);
}
void deserializeAndCallSyncCallback_String_Unknown_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String name, const Ark_CustomObject param)>(thisDeserializer.readPointer());
    Ark_String name = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_CustomObject param = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("Any"));
    _callSync(vmContext, _resourceId, name, param);
}
void deserializeAndCallCallback_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String breakpoints)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String breakpoints = static_cast<Ark_String>(thisDeserializer.readString());
    _call(_resourceId, breakpoints);
}
void deserializeAndCallSyncCallback_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String breakpoints)>(thisDeserializer.readPointer());
    Ark_String breakpoints = static_cast<Ark_String>(thisDeserializer.readString());
    _callSync(vmContext, _resourceId, breakpoints);
}
void deserializeAndCallCallback_StyledStringChangeValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_StyledStringChangeValue parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_StyledStringChangeValue parameter = thisDeserializer.readStyledStringChangeValue();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_StyledStringChangeValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_StyledStringChangeValue parameter, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_StyledStringChangeValue parameter = thisDeserializer.readStyledStringChangeValue();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_SwipeActionState_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_SwipeActionState state)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SwipeActionState state = static_cast<Ark_SwipeActionState>(thisDeserializer.readInt32());
    _call(_resourceId, state);
}
void deserializeAndCallSyncCallback_SwipeActionState_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_SwipeActionState state)>(thisDeserializer.readPointer());
    Ark_SwipeActionState state = static_cast<Ark_SwipeActionState>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, state);
}
void deserializeAndCallCallback_SwiperContentTransitionProxy_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SwiperContentTransitionProxy parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SwiperContentTransitionProxy parameter = static_cast<Ark_SwiperContentTransitionProxy>(thisDeserializer.readSwiperContentTransitionProxy());
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_SwiperContentTransitionProxy_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SwiperContentTransitionProxy parameter)>(thisDeserializer.readPointer());
    Ark_SwiperContentTransitionProxy parameter = static_cast<Ark_SwiperContentTransitionProxy>(thisDeserializer.readSwiperContentTransitionProxy());
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_TabContentTransitionProxy_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TabContentTransitionProxy parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TabContentTransitionProxy parameter = static_cast<Ark_TabContentTransitionProxy>(thisDeserializer.readTabContentTransitionProxy());
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_TabContentTransitionProxy_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TabContentTransitionProxy parameter)>(thisDeserializer.readPointer());
    Ark_TabContentTransitionProxy parameter = static_cast<Ark_TabContentTransitionProxy>(thisDeserializer.readTabContentTransitionProxy());
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_TerminationInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TerminationInfo parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TerminationInfo parameter = thisDeserializer.readTerminationInfo();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_TerminationInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TerminationInfo parameter)>(thisDeserializer.readPointer());
    Ark_TerminationInfo parameter = thisDeserializer.readTerminationInfo();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_TextPickerResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TextPickerResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TextPickerResult value = thisDeserializer.readTextPickerResult();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_TextPickerResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TextPickerResult value)>(thisDeserializer.readPointer());
    Ark_TextPickerResult value = thisDeserializer.readTextPickerResult();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_TextRange_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TextRange parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TextRange parameter = thisDeserializer.readTextRange();
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_TextRange_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TextRange parameter)>(thisDeserializer.readPointer());
    Ark_TextRange parameter = thisDeserializer.readTextRange();
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_TimePickerResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TimePickerResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TimePickerResult value = thisDeserializer.readTimePickerResult();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_TimePickerResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TimePickerResult value)>(thisDeserializer.readPointer());
    Ark_TimePickerResult value = thisDeserializer.readTimePickerResult();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_TouchEvent_HitTestMode(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TouchEvent parameter, const Callback_HitTestMode_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TouchEvent parameter = static_cast<Ark_TouchEvent>(thisDeserializer.readTouchEvent());
    Callback_HitTestMode_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_HitTestMode_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_HitTestMode_Void))))};
    _call(_resourceId, parameter, _continuation);
}
void deserializeAndCallSyncCallback_TouchEvent_HitTestMode(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchEvent parameter, const Callback_HitTestMode_Void continuation)>(thisDeserializer.readPointer());
    Ark_TouchEvent parameter = static_cast<Ark_TouchEvent>(thisDeserializer.readTouchEvent());
    Callback_HitTestMode_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_HitTestMode_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_HitTestMode_Void))))};
    _callSync(vmContext, _resourceId, parameter, _continuation);
}
void deserializeAndCallCallback_TouchEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TouchEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TouchEvent event = static_cast<Ark_TouchEvent>(thisDeserializer.readTouchEvent());
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_TouchEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchEvent event)>(thisDeserializer.readPointer());
    Ark_TouchEvent event = static_cast<Ark_TouchEvent>(thisDeserializer.readTouchEvent());
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_TouchResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TouchResult value = thisDeserializer.readTouchResult();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_TouchResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointer());
    Ark_TouchResult value = thisDeserializer.readTouchResult();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Tuple_Number_Number_Number_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Tuple_Number_Number_Number_Number value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Tuple_Number_Number_Number_Number value_buf = {};
    value_buf.value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    value_buf.value1 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    value_buf.value2 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    value_buf.value3 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Tuple_Number_Number_Number_Number value = value_buf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Tuple_Number_Number_Number_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_Number_Number_Number_Number value)>(thisDeserializer.readPointer());
    Ark_Tuple_Number_Number_Number_Number value_buf = {};
    value_buf.value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    value_buf.value1 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    value_buf.value2 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    value_buf.value3 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Tuple_Number_Number_Number_Number value = value_buf;
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Tuple_Number_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Tuple_Number_Number value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Tuple_Number_Number value_buf = {};
    value_buf.value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    value_buf.value1 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Tuple_Number_Number value = value_buf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Tuple_Number_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_Number_Number value)>(thisDeserializer.readPointer());
    Ark_Tuple_Number_Number value_buf = {};
    value_buf.value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    value_buf.value1 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Tuple_Number_Number value = value_buf;
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Type_ImageAttribute_onComplete_callback_event_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Type_ImageAttribute_onComplete_callback_event event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Type_ImageAttribute_onComplete_callback_event event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        Ark_Type_ImageAttribute_onComplete_callback_event event_buf_ = {};
        event_buf_.width = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf_.height = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf_.componentWidth = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf_.componentHeight = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf_.loadingStatus = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf_.contentWidth = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf_.contentHeight = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf_.contentOffsetX = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf_.contentOffsetY = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf.value = event_buf_;
    }
    Opt_Type_ImageAttribute_onComplete_callback_event event = event_buf;
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_Type_ImageAttribute_onComplete_callback_event_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Type_ImageAttribute_onComplete_callback_event event)>(thisDeserializer.readPointer());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Type_ImageAttribute_onComplete_callback_event event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        Ark_Type_ImageAttribute_onComplete_callback_event event_buf_ = {};
        event_buf_.width = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf_.height = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf_.componentWidth = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf_.componentHeight = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf_.loadingStatus = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf_.contentWidth = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf_.contentHeight = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf_.contentOffsetX = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf_.contentOffsetY = static_cast<Ark_Number>(thisDeserializer.readNumber());
        event_buf.value = event_buf_;
    }
    Opt_Type_ImageAttribute_onComplete_callback_event event = event_buf;
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_UIExtensionProxy_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_UIExtensionProxy parameter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_UIExtensionProxy parameter = static_cast<Ark_UIExtensionProxy>(thisDeserializer.readUIExtensionProxy());
    _call(_resourceId, parameter);
}
void deserializeAndCallSyncCallback_UIExtensionProxy_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_UIExtensionProxy parameter)>(thisDeserializer.readPointer());
    Ark_UIExtensionProxy parameter = static_cast<Ark_UIExtensionProxy>(thisDeserializer.readUIExtensionProxy());
    _callSync(vmContext, _resourceId, parameter);
}
void deserializeAndCallCallback_Union_CustomBuilder_DragItemInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_CustomBuilder_DragItemInfo value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int8 value_buf_selector = thisDeserializer.readInt8();
    Ark_Union_CustomBuilder_DragItemInfo value_buf = {};
    value_buf.selector = value_buf_selector;
    if (value_buf_selector == 0) {
        value_buf.selector = 0;
        value_buf.value0 = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_CustomNodeBuilder)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_CustomNodeBuilder))))};
    }
    else if (value_buf_selector == 1) {
        value_buf.selector = 1;
        value_buf.value1 = thisDeserializer.readDragItemInfo();
    }
    else {
        INTEROP_FATAL("One of the branches for value_buf has to be chosen through deserialisation.");
    }
    Ark_Union_CustomBuilder_DragItemInfo value = static_cast<Ark_Union_CustomBuilder_DragItemInfo>(value_buf);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Union_CustomBuilder_DragItemInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_CustomBuilder_DragItemInfo value)>(thisDeserializer.readPointer());
    const Ark_Int8 value_buf_selector = thisDeserializer.readInt8();
    Ark_Union_CustomBuilder_DragItemInfo value_buf = {};
    value_buf.selector = value_buf_selector;
    if (value_buf_selector == 0) {
        value_buf.selector = 0;
        value_buf.value0 = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_CustomNodeBuilder)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_CustomNodeBuilder))))};
    }
    else if (value_buf_selector == 1) {
        value_buf.selector = 1;
        value_buf.value1 = thisDeserializer.readDragItemInfo();
    }
    else {
        INTEROP_FATAL("One of the branches for value_buf has to be chosen through deserialisation.");
    }
    Ark_Union_CustomBuilder_DragItemInfo value = static_cast<Ark_Union_CustomBuilder_DragItemInfo>(value_buf);
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Union_Number_Array_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_Number_Array_Number selected)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int8 selected_buf_selector = thisDeserializer.readInt8();
    Ark_Union_Number_Array_Number selected_buf = {};
    selected_buf.selector = selected_buf_selector;
    if (selected_buf_selector == 0) {
        selected_buf.selector = 0;
        selected_buf.value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    }
    else if (selected_buf_selector == 1) {
        selected_buf.selector = 1;
        const Ark_Int32 selected_buf_u_length = thisDeserializer.readInt32();
        Array_Number selected_buf_u = {};
        thisDeserializer.resizeArray<std::decay<decltype(selected_buf_u)>::type,
        std::decay<decltype(*selected_buf_u.array)>::type>(&selected_buf_u, selected_buf_u_length);
        for (int selected_buf_u_i = 0; selected_buf_u_i < selected_buf_u_length; selected_buf_u_i++) {
            selected_buf_u.array[selected_buf_u_i] = static_cast<Ark_Number>(thisDeserializer.readNumber());
        }
        selected_buf.value1 = selected_buf_u;
    }
    else {
        INTEROP_FATAL("One of the branches for selected_buf has to be chosen through deserialisation.");
    }
    Ark_Union_Number_Array_Number selected = static_cast<Ark_Union_Number_Array_Number>(selected_buf);
    _call(_resourceId, selected);
}
void deserializeAndCallSyncCallback_Union_Number_Array_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_Number_Array_Number selected)>(thisDeserializer.readPointer());
    const Ark_Int8 selected_buf_selector = thisDeserializer.readInt8();
    Ark_Union_Number_Array_Number selected_buf = {};
    selected_buf.selector = selected_buf_selector;
    if (selected_buf_selector == 0) {
        selected_buf.selector = 0;
        selected_buf.value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    }
    else if (selected_buf_selector == 1) {
        selected_buf.selector = 1;
        const Ark_Int32 selected_buf_u_length = thisDeserializer.readInt32();
        Array_Number selected_buf_u = {};
        thisDeserializer.resizeArray<std::decay<decltype(selected_buf_u)>::type,
        std::decay<decltype(*selected_buf_u.array)>::type>(&selected_buf_u, selected_buf_u_length);
        for (int selected_buf_u_i = 0; selected_buf_u_i < selected_buf_u_length; selected_buf_u_i++) {
            selected_buf_u.array[selected_buf_u_i] = static_cast<Ark_Number>(thisDeserializer.readNumber());
        }
        selected_buf.value1 = selected_buf_u;
    }
    else {
        INTEROP_FATAL("One of the branches for selected_buf has to be chosen through deserialisation.");
    }
    Ark_Union_Number_Array_Number selected = static_cast<Ark_Union_Number_Array_Number>(selected_buf);
    _callSync(vmContext, _resourceId, selected);
}
void deserializeAndCallCallback_Union_Number_Resource_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_Number_Resource selected)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int8 selected_buf_selector = thisDeserializer.readInt8();
    Ark_Union_Number_Resource selected_buf = {};
    selected_buf.selector = selected_buf_selector;
    if (selected_buf_selector == 0) {
        selected_buf.selector = 0;
        selected_buf.value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    }
    else if (selected_buf_selector == 1) {
        selected_buf.selector = 1;
        selected_buf.value1 = thisDeserializer.readResource();
    }
    else {
        INTEROP_FATAL("One of the branches for selected_buf has to be chosen through deserialisation.");
    }
    Ark_Union_Number_Resource selected = static_cast<Ark_Union_Number_Resource>(selected_buf);
    _call(_resourceId, selected);
}
void deserializeAndCallSyncCallback_Union_Number_Resource_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_Number_Resource selected)>(thisDeserializer.readPointer());
    const Ark_Int8 selected_buf_selector = thisDeserializer.readInt8();
    Ark_Union_Number_Resource selected_buf = {};
    selected_buf.selector = selected_buf_selector;
    if (selected_buf_selector == 0) {
        selected_buf.selector = 0;
        selected_buf.value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    }
    else if (selected_buf_selector == 1) {
        selected_buf.selector = 1;
        selected_buf.value1 = thisDeserializer.readResource();
    }
    else {
        INTEROP_FATAL("One of the branches for selected_buf has to be chosen through deserialisation.");
    }
    Ark_Union_Number_Resource selected = static_cast<Ark_Union_Number_Resource>(selected_buf);
    _callSync(vmContext, _resourceId, selected);
}
void deserializeAndCallCallback_Union_String_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_String_Array_String value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int8 value_buf_selector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String value_buf = {};
    value_buf.selector = value_buf_selector;
    if (value_buf_selector == 0) {
        value_buf.selector = 0;
        value_buf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (value_buf_selector == 1) {
        value_buf.selector = 1;
        const Ark_Int32 value_buf_u_length = thisDeserializer.readInt32();
        Array_String value_buf_u = {};
        thisDeserializer.resizeArray<std::decay<decltype(value_buf_u)>::type,
        std::decay<decltype(*value_buf_u.array)>::type>(&value_buf_u, value_buf_u_length);
        for (int value_buf_u_i = 0; value_buf_u_i < value_buf_u_length; value_buf_u_i++) {
            value_buf_u.array[value_buf_u_i] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        value_buf.value1 = value_buf_u;
    }
    else {
        INTEROP_FATAL("One of the branches for value_buf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String value = static_cast<Ark_Union_String_Array_String>(value_buf);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Union_String_Array_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_String_Array_String value)>(thisDeserializer.readPointer());
    const Ark_Int8 value_buf_selector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String value_buf = {};
    value_buf.selector = value_buf_selector;
    if (value_buf_selector == 0) {
        value_buf.selector = 0;
        value_buf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (value_buf_selector == 1) {
        value_buf.selector = 1;
        const Ark_Int32 value_buf_u_length = thisDeserializer.readInt32();
        Array_String value_buf_u = {};
        thisDeserializer.resizeArray<std::decay<decltype(value_buf_u)>::type,
        std::decay<decltype(*value_buf_u.array)>::type>(&value_buf_u, value_buf_u_length);
        for (int value_buf_u_i = 0; value_buf_u_i < value_buf_u_length; value_buf_u_i++) {
            value_buf_u.array[value_buf_u_i] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        value_buf.value1 = value_buf_u;
    }
    else {
        INTEROP_FATAL("One of the branches for value_buf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String value = static_cast<Ark_Union_String_Array_String>(value_buf);
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncCallback_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    _callSync(vmContext, _resourceId);
}
void deserializeAndCallCallback_WebKeyboardOptions_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_WebKeyboardOptions value = thisDeserializer.readWebKeyboardOptions();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_WebKeyboardOptions_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointer());
    Ark_WebKeyboardOptions value = thisDeserializer.readWebKeyboardOptions();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_WebResourceResponse_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebResourceResponse value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_WebResourceResponse value = static_cast<Ark_WebResourceResponse>(thisDeserializer.readWebResourceResponse());
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_WebResourceResponse_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebResourceResponse value)>(thisDeserializer.readPointer());
    Ark_WebResourceResponse value = static_cast<Ark_WebResourceResponse>(thisDeserializer.readWebResourceResponse());
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_WithThemeAttribute_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WithThemeAttribute value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_WithThemeAttribute value = thisDeserializer.readWithThemeAttribute();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_WithThemeAttribute_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WithThemeAttribute value)>(thisDeserializer.readPointer());
    Ark_WithThemeAttribute value = thisDeserializer.readWithThemeAttribute();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallContentDidScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number selectedIndex, const Ark_Number index, const Ark_Number position, const Ark_Number mainAxisLength)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number selectedIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number position = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number mainAxisLength = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, selectedIndex, index, position, mainAxisLength);
}
void deserializeAndCallSyncContentDidScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number selectedIndex, const Ark_Number index, const Ark_Number position, const Ark_Number mainAxisLength)>(thisDeserializer.readPointer());
    Ark_Number selectedIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number position = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number mainAxisLength = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, selectedIndex, index, position, mainAxisLength);
}
void deserializeAndCallCustomNodeBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, _continuation);
}
void deserializeAndCallSyncCustomNodeBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _callSync(vmContext, _resourceId, parentNode, _continuation);
}
void deserializeAndCallEditableTextOnChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String value, const Opt_PreviewText previewText)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    const auto previewText_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_PreviewText previewText_buf = {};
    previewText_buf.tag = previewText_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (previewText_buf_runtimeType))
    {
        previewText_buf.value = thisDeserializer.readPreviewText();
    }
    Opt_PreviewText previewText = previewText_buf;
    _call(_resourceId, value, previewText);
}
void deserializeAndCallSyncEditableTextOnChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String value, const Opt_PreviewText previewText)>(thisDeserializer.readPointer());
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    const auto previewText_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_PreviewText previewText_buf = {};
    previewText_buf.tag = previewText_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (previewText_buf_runtimeType))
    {
        previewText_buf.value = thisDeserializer.readPreviewText();
    }
    Opt_PreviewText previewText = previewText_buf;
    _callSync(vmContext, _resourceId, value, previewText);
}
void deserializeAndCallErrorCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_BusinessError err)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_BusinessError err = thisDeserializer.readBusinessError();
    _call(_resourceId, err);
}
void deserializeAndCallSyncErrorCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_BusinessError err)>(thisDeserializer.readPointer());
    Ark_BusinessError err = thisDeserializer.readBusinessError();
    _callSync(vmContext, _resourceId, err);
}
void deserializeAndCallGestureRecognizerJudgeBeginCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_BaseGestureEvent event, const Ark_GestureRecognizer current, const Array_GestureRecognizer recognizers, const Callback_GestureJudgeResult_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(thisDeserializer.readBaseGestureEvent());
    Ark_GestureRecognizer current = static_cast<Ark_GestureRecognizer>(thisDeserializer.readGestureRecognizer());
    const Ark_Int32 recognizers_buf_length = thisDeserializer.readInt32();
    Array_GestureRecognizer recognizers_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(recognizers_buf)>::type,
        std::decay<decltype(*recognizers_buf.array)>::type>(&recognizers_buf, recognizers_buf_length);
    for (int recognizers_buf_i = 0; recognizers_buf_i < recognizers_buf_length; recognizers_buf_i++) {
        recognizers_buf.array[recognizers_buf_i] = static_cast<Ark_GestureRecognizer>(thisDeserializer.readGestureRecognizer());
    }
    Array_GestureRecognizer recognizers = recognizers_buf;
    Callback_GestureJudgeResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureJudgeResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureJudgeResult_Void))))};
    _call(_resourceId, event, current, recognizers, _continuation);
}
void deserializeAndCallSyncGestureRecognizerJudgeBeginCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_BaseGestureEvent event, const Ark_GestureRecognizer current, const Array_GestureRecognizer recognizers, const Callback_GestureJudgeResult_Void continuation)>(thisDeserializer.readPointer());
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(thisDeserializer.readBaseGestureEvent());
    Ark_GestureRecognizer current = static_cast<Ark_GestureRecognizer>(thisDeserializer.readGestureRecognizer());
    const Ark_Int32 recognizers_buf_length = thisDeserializer.readInt32();
    Array_GestureRecognizer recognizers_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(recognizers_buf)>::type,
        std::decay<decltype(*recognizers_buf.array)>::type>(&recognizers_buf, recognizers_buf_length);
    for (int recognizers_buf_i = 0; recognizers_buf_i < recognizers_buf_length; recognizers_buf_i++) {
        recognizers_buf.array[recognizers_buf_i] = static_cast<Ark_GestureRecognizer>(thisDeserializer.readGestureRecognizer());
    }
    Array_GestureRecognizer recognizers = recognizers_buf;
    Callback_GestureJudgeResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureJudgeResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureJudgeResult_Void))))};
    _callSync(vmContext, _resourceId, event, current, recognizers, _continuation);
}
void deserializeAndCallGetItemMainSizeByIndex(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Callback_Number_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Number_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Number_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Number_Void))))};
    _call(_resourceId, index, _continuation);
}
void deserializeAndCallSyncGetItemMainSizeByIndex(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Callback_Number_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Number_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Number_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Number_Void))))};
    _callSync(vmContext, _resourceId, index, _continuation);
}
void deserializeAndCallHoverCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_HoverEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(thisDeserializer.readHoverEvent());
    _call(_resourceId, isHover, event);
}
void deserializeAndCallSyncHoverCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_HoverEvent event)>(thisDeserializer.readPointer());
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(thisDeserializer.readHoverEvent());
    _callSync(vmContext, _resourceId, isHover, event);
}
void deserializeAndCallImageCompleteCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ImageLoadResult result)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ImageLoadResult result = thisDeserializer.readImageLoadResult();
    _call(_resourceId, result);
}
void deserializeAndCallSyncImageCompleteCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ImageLoadResult result)>(thisDeserializer.readPointer());
    Ark_ImageLoadResult result = thisDeserializer.readImageLoadResult();
    _callSync(vmContext, _resourceId, result);
}
void deserializeAndCallImageErrorCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ImageError error)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ImageError error = thisDeserializer.readImageError();
    _call(_resourceId, error);
}
void deserializeAndCallSyncImageErrorCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ImageError error)>(thisDeserializer.readPointer());
    Ark_ImageError error = thisDeserializer.readImageError();
    _callSync(vmContext, _resourceId, error);
}
void deserializeAndCallInterceptionModeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_NavigationMode mode)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NavigationMode mode = static_cast<Ark_NavigationMode>(thisDeserializer.readInt32());
    _call(_resourceId, mode);
}
void deserializeAndCallSyncInterceptionModeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_NavigationMode mode)>(thisDeserializer.readPointer());
    Ark_NavigationMode mode = static_cast<Ark_NavigationMode>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, mode);
}
void deserializeAndCallInterceptionShowCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_NavDestinationContext_NavBar from, const Ark_Union_NavDestinationContext_NavBar to, Ark_NavigationOperation operation, const Ark_Boolean isAnimated)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int8 from_buf_selector = thisDeserializer.readInt8();
    Ark_Union_NavDestinationContext_NavBar from_buf = {};
    from_buf.selector = from_buf_selector;
    if (from_buf_selector == 0) {
        from_buf.selector = 0;
        from_buf.value0 = static_cast<Ark_NavDestinationContext>(thisDeserializer.readNavDestinationContext());
    }
    else if (from_buf_selector == 1) {
        from_buf.selector = 1;
        from_buf.value1 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else {
        INTEROP_FATAL("One of the branches for from_buf has to be chosen through deserialisation.");
    }
    Ark_Union_NavDestinationContext_NavBar from = static_cast<Ark_Union_NavDestinationContext_NavBar>(from_buf);
    const Ark_Int8 to_buf_selector = thisDeserializer.readInt8();
    Ark_Union_NavDestinationContext_NavBar to_buf = {};
    to_buf.selector = to_buf_selector;
    if (to_buf_selector == 0) {
        to_buf.selector = 0;
        to_buf.value0 = static_cast<Ark_NavDestinationContext>(thisDeserializer.readNavDestinationContext());
    }
    else if (to_buf_selector == 1) {
        to_buf.selector = 1;
        to_buf.value1 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else {
        INTEROP_FATAL("One of the branches for to_buf has to be chosen through deserialisation.");
    }
    Ark_Union_NavDestinationContext_NavBar to = static_cast<Ark_Union_NavDestinationContext_NavBar>(to_buf);
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Ark_Boolean isAnimated = thisDeserializer.readBoolean();
    _call(_resourceId, from, to, operation, isAnimated);
}
void deserializeAndCallSyncInterceptionShowCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_NavDestinationContext_NavBar from, const Ark_Union_NavDestinationContext_NavBar to, Ark_NavigationOperation operation, const Ark_Boolean isAnimated)>(thisDeserializer.readPointer());
    const Ark_Int8 from_buf_selector = thisDeserializer.readInt8();
    Ark_Union_NavDestinationContext_NavBar from_buf = {};
    from_buf.selector = from_buf_selector;
    if (from_buf_selector == 0) {
        from_buf.selector = 0;
        from_buf.value0 = static_cast<Ark_NavDestinationContext>(thisDeserializer.readNavDestinationContext());
    }
    else if (from_buf_selector == 1) {
        from_buf.selector = 1;
        from_buf.value1 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else {
        INTEROP_FATAL("One of the branches for from_buf has to be chosen through deserialisation.");
    }
    Ark_Union_NavDestinationContext_NavBar from = static_cast<Ark_Union_NavDestinationContext_NavBar>(from_buf);
    const Ark_Int8 to_buf_selector = thisDeserializer.readInt8();
    Ark_Union_NavDestinationContext_NavBar to_buf = {};
    to_buf.selector = to_buf_selector;
    if (to_buf_selector == 0) {
        to_buf.selector = 0;
        to_buf.value0 = static_cast<Ark_NavDestinationContext>(thisDeserializer.readNavDestinationContext());
    }
    else if (to_buf_selector == 1) {
        to_buf.selector = 1;
        to_buf.value1 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else {
        INTEROP_FATAL("One of the branches for to_buf has to be chosen through deserialisation.");
    }
    Ark_Union_NavDestinationContext_NavBar to = static_cast<Ark_Union_NavDestinationContext_NavBar>(to_buf);
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Ark_Boolean isAnimated = thisDeserializer.readBoolean();
    _callSync(vmContext, _resourceId, from, to, operation, isAnimated);
}
void deserializeAndCallIsolatedComponentInterface(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_IsolatedOptions options, const Callback_IsolatedComponentAttribute_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_IsolatedOptions options = thisDeserializer.readIsolatedOptions();
    Callback_IsolatedComponentAttribute_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_IsolatedComponentAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_IsolatedComponentAttribute_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_IsolatedComponentAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_IsolatedComponentAttribute_Void))))};
    _call(_resourceId, options, _continuation);
}
void deserializeAndCallSyncIsolatedComponentInterface(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_IsolatedOptions options, const Callback_IsolatedComponentAttribute_Void continuation)>(thisDeserializer.readPointer());
    Ark_IsolatedOptions options = thisDeserializer.readIsolatedOptions();
    Callback_IsolatedComponentAttribute_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_IsolatedComponentAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_IsolatedComponentAttribute_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_IsolatedComponentAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_IsolatedComponentAttribute_Void))))};
    _callSync(vmContext, _resourceId, options, _continuation);
}
void deserializeAndCallMenuOnAppearCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number start, const Ark_Number end)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number start = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number end = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, start, end);
}
void deserializeAndCallSyncMenuOnAppearCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number start, const Ark_Number end)>(thisDeserializer.readPointer());
    Ark_Number start = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number end = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, start, end);
}
void deserializeAndCallNavExtender_OnUpdateStack(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String name)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String name = static_cast<Ark_String>(thisDeserializer.readString());
    _call(_resourceId, name);
}
void deserializeAndCallSyncNavExtender_OnUpdateStack(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String name)>(thisDeserializer.readPointer());
    Ark_String name = static_cast<Ark_String>(thisDeserializer.readString());
    _callSync(vmContext, _resourceId, name);
}
void deserializeAndCallOnAdsBlockedCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_AdsBlockedDetails details)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_AdsBlockedDetails details = thisDeserializer.readAdsBlockedDetails();
    _call(_resourceId, details);
}
void deserializeAndCallSyncOnAdsBlockedCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_AdsBlockedDetails details)>(thisDeserializer.readPointer());
    Ark_AdsBlockedDetails details = thisDeserializer.readAdsBlockedDetails();
    _callSync(vmContext, _resourceId, details);
}
void deserializeAndCallOnAlphabetIndexerPopupSelectCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, index);
}
void deserializeAndCallSyncOnAlphabetIndexerPopupSelectCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, index);
}
void deserializeAndCallOnAlphabetIndexerRequestPopupDataCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Callback_Array_String_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Array_String_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_String value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Array_String_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_String value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Array_String_Void))))};
    _call(_resourceId, index, _continuation);
}
void deserializeAndCallSyncOnAlphabetIndexerRequestPopupDataCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Callback_Array_String_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Array_String_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_String value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Array_String_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_String value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Array_String_Void))))};
    _callSync(vmContext, _resourceId, index, _continuation);
}
void deserializeAndCallOnAlphabetIndexerSelectCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, index);
}
void deserializeAndCallSyncOnAlphabetIndexerSelectCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, index);
}
void deserializeAndCallOnCheckboxChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean value = thisDeserializer.readBoolean();
    _call(_resourceId, value);
}
void deserializeAndCallSyncOnCheckboxChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value)>(thisDeserializer.readPointer());
    Ark_Boolean value = thisDeserializer.readBoolean();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallOnCheckboxGroupChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CheckboxGroupResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_CheckboxGroupResult value = thisDeserializer.readCheckboxGroupResult();
    _call(_resourceId, value);
}
void deserializeAndCallSyncOnCheckboxGroupChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CheckboxGroupResult value)>(thisDeserializer.readPointer());
    Ark_CheckboxGroupResult value = thisDeserializer.readCheckboxGroupResult();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallOnContentScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number totalOffsetX, const Ark_Number totalOffsetY)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number totalOffsetX = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number totalOffsetY = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, totalOffsetX, totalOffsetY);
}
void deserializeAndCallSyncOnContentScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number totalOffsetX, const Ark_Number totalOffsetY)>(thisDeserializer.readPointer());
    Ark_Number totalOffsetX = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number totalOffsetY = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, totalOffsetX, totalOffsetY);
}
void deserializeAndCallOnContextMenuHideCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncOnContextMenuHideCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    _callSync(vmContext, _resourceId);
}
void deserializeAndCallOnDidChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TextRange rangeBefore, const Ark_TextRange rangeAfter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TextRange rangeBefore = thisDeserializer.readTextRange();
    Ark_TextRange rangeAfter = thisDeserializer.readTextRange();
    _call(_resourceId, rangeBefore, rangeAfter);
}
void deserializeAndCallSyncOnDidChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TextRange rangeBefore, const Ark_TextRange rangeAfter)>(thisDeserializer.readPointer());
    Ark_TextRange rangeBefore = thisDeserializer.readTextRange();
    Ark_TextRange rangeAfter = thisDeserializer.readTextRange();
    _callSync(vmContext, _resourceId, rangeBefore, rangeAfter);
}
void deserializeAndCallOnFirstMeaningfulPaintCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_FirstMeaningfulPaint firstMeaningfulPaint)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_FirstMeaningfulPaint firstMeaningfulPaint = thisDeserializer.readFirstMeaningfulPaint();
    _call(_resourceId, firstMeaningfulPaint);
}
void deserializeAndCallSyncOnFirstMeaningfulPaintCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_FirstMeaningfulPaint firstMeaningfulPaint)>(thisDeserializer.readPointer());
    Ark_FirstMeaningfulPaint firstMeaningfulPaint = thisDeserializer.readFirstMeaningfulPaint();
    _callSync(vmContext, _resourceId, firstMeaningfulPaint);
}
void deserializeAndCallOnFoldStatusChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnFoldStatusChangeInfo event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnFoldStatusChangeInfo event = thisDeserializer.readOnFoldStatusChangeInfo();
    _call(_resourceId, event);
}
void deserializeAndCallSyncOnFoldStatusChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnFoldStatusChangeInfo event)>(thisDeserializer.readPointer());
    Ark_OnFoldStatusChangeInfo event = thisDeserializer.readOnFoldStatusChangeInfo();
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallOnFullScreenEnterCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_FullScreenEnterEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_FullScreenEnterEvent event = thisDeserializer.readFullScreenEnterEvent();
    _call(_resourceId, event);
}
void deserializeAndCallSyncOnFullScreenEnterCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_FullScreenEnterEvent event)>(thisDeserializer.readPointer());
    Ark_FullScreenEnterEvent event = thisDeserializer.readFullScreenEnterEvent();
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallOnHoverStatusChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_HoverEventParam param)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_HoverEventParam param = thisDeserializer.readHoverEventParam();
    _call(_resourceId, param);
}
void deserializeAndCallSyncOnHoverStatusChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_HoverEventParam param)>(thisDeserializer.readPointer());
    Ark_HoverEventParam param = thisDeserializer.readHoverEventParam();
    _callSync(vmContext, _resourceId, param);
}
void deserializeAndCallOnIntelligentTrackingPreventionCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_IntelligentTrackingPreventionDetails details)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_IntelligentTrackingPreventionDetails details = thisDeserializer.readIntelligentTrackingPreventionDetails();
    _call(_resourceId, details);
}
void deserializeAndCallSyncOnIntelligentTrackingPreventionCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_IntelligentTrackingPreventionDetails details)>(thisDeserializer.readPointer());
    Ark_IntelligentTrackingPreventionDetails details = thisDeserializer.readIntelligentTrackingPreventionDetails();
    _callSync(vmContext, _resourceId, details);
}
void deserializeAndCallonItemDragStart_event_type(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Number itemIndex, const Callback_CustomBuilder_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = thisDeserializer.readItemDragInfo();
    Ark_Number itemIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_CustomBuilder_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const CustomNodeBuilder value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_CustomBuilder_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const CustomNodeBuilder value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_CustomBuilder_Void))))};
    _call(_resourceId, event, itemIndex, _continuation);
}
void deserializeAndCallSynconItemDragStart_event_type(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Number itemIndex, const Callback_CustomBuilder_Void continuation)>(thisDeserializer.readPointer());
    Ark_ItemDragInfo event = thisDeserializer.readItemDragInfo();
    Ark_Number itemIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_CustomBuilder_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const CustomNodeBuilder value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_CustomBuilder_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const CustomNodeBuilder value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_CustomBuilder_Void))))};
    _callSync(vmContext, _resourceId, event, itemIndex, _continuation);
}
void deserializeAndCallOnLargestContentfulPaintCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_LargestContentfulPaint largestContentfulPaint)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_LargestContentfulPaint largestContentfulPaint = thisDeserializer.readLargestContentfulPaint();
    _call(_resourceId, largestContentfulPaint);
}
void deserializeAndCallSyncOnLargestContentfulPaintCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_LargestContentfulPaint largestContentfulPaint)>(thisDeserializer.readPointer());
    Ark_LargestContentfulPaint largestContentfulPaint = thisDeserializer.readLargestContentfulPaint();
    _callSync(vmContext, _resourceId, largestContentfulPaint);
}
void deserializeAndCallOnLinearIndicatorChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number progress)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number progress = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, index, progress);
}
void deserializeAndCallSyncOnLinearIndicatorChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number progress)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number progress = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, index, progress);
}
void deserializeAndCallOnMoveHandler(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number from, const Ark_Number to)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number from = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number to = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, from, to);
}
void deserializeAndCallSyncOnMoveHandler(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number from, const Ark_Number to)>(thisDeserializer.readPointer());
    Ark_Number from = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number to = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, from, to);
}
void deserializeAndCallOnNativeEmbedVisibilityChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo = thisDeserializer.readNativeEmbedVisibilityInfo();
    _call(_resourceId, nativeEmbedVisibilityInfo);
}
void deserializeAndCallSyncOnNativeEmbedVisibilityChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo)>(thisDeserializer.readPointer());
    Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo = thisDeserializer.readNativeEmbedVisibilityInfo();
    _callSync(vmContext, _resourceId, nativeEmbedVisibilityInfo);
}
void deserializeAndCallOnNativeLoadCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_CustomObject event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_CustomObject event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        event_buf.value = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("Object"));
    }
    Opt_CustomObject event = event_buf;
    _call(_resourceId, event);
}
void deserializeAndCallSyncOnNativeLoadCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_CustomObject event)>(thisDeserializer.readPointer());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_CustomObject event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        event_buf.value = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("Object"));
    }
    Opt_CustomObject event = event_buf;
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallOnNavigationEntryCommittedCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_LoadCommittedDetails loadCommittedDetails)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_LoadCommittedDetails loadCommittedDetails = thisDeserializer.readLoadCommittedDetails();
    _call(_resourceId, loadCommittedDetails);
}
void deserializeAndCallSyncOnNavigationEntryCommittedCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_LoadCommittedDetails loadCommittedDetails)>(thisDeserializer.readPointer());
    Ark_LoadCommittedDetails loadCommittedDetails = thisDeserializer.readLoadCommittedDetails();
    _callSync(vmContext, _resourceId, loadCommittedDetails);
}
void deserializeAndCallOnOverrideUrlLoadingCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebResourceRequest webResourceRequest, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_WebResourceRequest webResourceRequest = static_cast<Ark_WebResourceRequest>(thisDeserializer.readWebResourceRequest());
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, webResourceRequest, _continuation);
}
void deserializeAndCallSyncOnOverrideUrlLoadingCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebResourceRequest webResourceRequest, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_WebResourceRequest webResourceRequest = static_cast<Ark_WebResourceRequest>(thisDeserializer.readWebResourceRequest());
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, webResourceRequest, _continuation);
}
void deserializeAndCallOnPasteCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String content, const Ark_PasteEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String content = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_PasteEvent event = thisDeserializer.readPasteEvent();
    _call(_resourceId, content, event);
}
void deserializeAndCallSyncOnPasteCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String content, const Ark_PasteEvent event)>(thisDeserializer.readPointer());
    Ark_String content = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_PasteEvent event = thisDeserializer.readPasteEvent();
    _callSync(vmContext, _resourceId, content, event);
}
void deserializeAndCallOnRenderProcessNotRespondingCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RenderProcessNotRespondingData data)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RenderProcessNotRespondingData data = thisDeserializer.readRenderProcessNotRespondingData();
    _call(_resourceId, data);
}
void deserializeAndCallSyncOnRenderProcessNotRespondingCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RenderProcessNotRespondingData data)>(thisDeserializer.readPointer());
    Ark_RenderProcessNotRespondingData data = thisDeserializer.readRenderProcessNotRespondingData();
    _callSync(vmContext, _resourceId, data);
}
void deserializeAndCallOnRenderProcessRespondingCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncOnRenderProcessRespondingCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    _callSync(vmContext, _resourceId);
}
void deserializeAndCallOnSafeBrowsingCheckResultCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_ThreatType threatType)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ThreatType threatType = static_cast<Ark_ThreatType>(thisDeserializer.readInt32());
    _call(_resourceId, threatType);
}
void deserializeAndCallSyncOnSafeBrowsingCheckResultCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_ThreatType threatType)>(thisDeserializer.readPointer());
    Ark_ThreatType threatType = static_cast<Ark_ThreatType>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, threatType);
}
void deserializeAndCallOnScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number scrollOffset, Ark_ScrollState scrollState)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number scrollOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    _call(_resourceId, scrollOffset, scrollState);
}
void deserializeAndCallSyncOnScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number scrollOffset, Ark_ScrollState scrollState)>(thisDeserializer.readPointer());
    Ark_Number scrollOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, scrollOffset, scrollState);
}
void deserializeAndCallOnWillScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_Number scrollOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, const Callback_ScrollResult_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number scrollOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Ark_ScrollSource scrollSource = static_cast<Ark_ScrollSource>(thisDeserializer.readInt32());
    Callback_ScrollResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ScrollResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_ScrollResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ScrollResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_ScrollResult_Void))))};
    _call(_resourceId, scrollOffset, scrollState, scrollSource, _continuation);
}
void deserializeAndCallSyncOnWillScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_Number scrollOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, const Callback_ScrollResult_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number scrollOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Ark_ScrollSource scrollSource = static_cast<Ark_ScrollSource>(thisDeserializer.readInt32());
    Callback_ScrollResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ScrollResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_ScrollResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ScrollResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_ScrollResult_Void))))};
    _callSync(vmContext, _resourceId, scrollOffset, scrollState, scrollSource, _continuation);
}
void deserializeAndCallOnScrollEdgeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_Edge side)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Edge side = static_cast<Ark_Edge>(thisDeserializer.readInt32());
    _call(_resourceId, side);
}
void deserializeAndCallSyncOnScrollEdgeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_Edge side)>(thisDeserializer.readPointer());
    Ark_Edge side = static_cast<Ark_Edge>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, side);
}
void deserializeAndCallOnScrollFrameBeginCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number offset, Ark_ScrollState state, const Callback_OnScrollFrameBeginHandlerResult_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number offset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState state = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Callback_OnScrollFrameBeginHandlerResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnScrollFrameBeginHandlerResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnScrollFrameBeginHandlerResult_Void))))};
    _call(_resourceId, offset, state, _continuation);
}
void deserializeAndCallSyncOnScrollFrameBeginCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number offset, Ark_ScrollState state, const Callback_OnScrollFrameBeginHandlerResult_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number offset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState state = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Callback_OnScrollFrameBeginHandlerResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnScrollFrameBeginHandlerResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnScrollFrameBeginHandlerResult_Void))))};
    _callSync(vmContext, _resourceId, offset, state, _continuation);
}
void deserializeAndCallOnScrollVisibleContentChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_VisibleListContentInfo start, const Ark_VisibleListContentInfo end)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_VisibleListContentInfo start = thisDeserializer.readVisibleListContentInfo();
    Ark_VisibleListContentInfo end = thisDeserializer.readVisibleListContentInfo();
    _call(_resourceId, start, end);
}
void deserializeAndCallSyncOnScrollVisibleContentChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_VisibleListContentInfo start, const Ark_VisibleListContentInfo end)>(thisDeserializer.readPointer());
    Ark_VisibleListContentInfo start = thisDeserializer.readVisibleListContentInfo();
    Ark_VisibleListContentInfo end = thisDeserializer.readVisibleListContentInfo();
    _callSync(vmContext, _resourceId, start, end);
}
void deserializeAndCallOnSslErrorEventCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SslErrorEvent sslErrorEvent)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SslErrorEvent sslErrorEvent = thisDeserializer.readSslErrorEvent();
    _call(_resourceId, sslErrorEvent);
}
void deserializeAndCallSyncOnSslErrorEventCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SslErrorEvent sslErrorEvent)>(thisDeserializer.readPointer());
    Ark_SslErrorEvent sslErrorEvent = thisDeserializer.readSslErrorEvent();
    _callSync(vmContext, _resourceId, sslErrorEvent);
}
void deserializeAndCallOnSubmitCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_EnterKeyType enterKey, const Ark_SubmitEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    Ark_SubmitEvent event = static_cast<Ark_SubmitEvent>(thisDeserializer.readSubmitEvent());
    _call(_resourceId, enterKey, event);
}
void deserializeAndCallSyncOnSubmitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_EnterKeyType enterKey, const Ark_SubmitEvent event)>(thisDeserializer.readPointer());
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    Ark_SubmitEvent event = static_cast<Ark_SubmitEvent>(thisDeserializer.readSubmitEvent());
    _callSync(vmContext, _resourceId, enterKey, event);
}
void deserializeAndCallOnSwiperAnimationEndCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = thisDeserializer.readSwiperAnimationEvent();
    _call(_resourceId, index, extraInfo);
}
void deserializeAndCallSyncOnSwiperAnimationEndCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = thisDeserializer.readSwiperAnimationEvent();
    _callSync(vmContext, _resourceId, index, extraInfo);
}
void deserializeAndCallOnSwiperAnimationStartCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number targetIndex, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number targetIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = thisDeserializer.readSwiperAnimationEvent();
    _call(_resourceId, index, targetIndex, extraInfo);
}
void deserializeAndCallSyncOnSwiperAnimationStartCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number targetIndex, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number targetIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = thisDeserializer.readSwiperAnimationEvent();
    _callSync(vmContext, _resourceId, index, targetIndex, extraInfo);
}
void deserializeAndCallOnSwiperGestureSwipeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = thisDeserializer.readSwiperAnimationEvent();
    _call(_resourceId, index, extraInfo);
}
void deserializeAndCallSyncOnSwiperGestureSwipeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = thisDeserializer.readSwiperAnimationEvent();
    _callSync(vmContext, _resourceId, index, extraInfo);
}
void deserializeAndCallOnTabsAnimationEndCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_TabsAnimationEvent extraInfo = thisDeserializer.readTabsAnimationEvent();
    _call(_resourceId, index, extraInfo);
}
void deserializeAndCallSyncOnTabsAnimationEndCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_TabsAnimationEvent extraInfo = thisDeserializer.readTabsAnimationEvent();
    _callSync(vmContext, _resourceId, index, extraInfo);
}
void deserializeAndCallOnTabsAnimationStartCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number targetIndex, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number targetIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_TabsAnimationEvent extraInfo = thisDeserializer.readTabsAnimationEvent();
    _call(_resourceId, index, targetIndex, extraInfo);
}
void deserializeAndCallSyncOnTabsAnimationStartCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number targetIndex, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number targetIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_TabsAnimationEvent extraInfo = thisDeserializer.readTabsAnimationEvent();
    _callSync(vmContext, _resourceId, index, targetIndex, extraInfo);
}
void deserializeAndCallOnTabsContentWillChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number currentIndex, const Ark_Number comingIndex, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number currentIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number comingIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, currentIndex, comingIndex, _continuation);
}
void deserializeAndCallSyncOnTabsContentWillChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number currentIndex, const Ark_Number comingIndex, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number currentIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number comingIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, currentIndex, comingIndex, _continuation);
}
void deserializeAndCallOnTabsGestureSwipeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_TabsAnimationEvent extraInfo = thisDeserializer.readTabsAnimationEvent();
    _call(_resourceId, index, extraInfo);
}
void deserializeAndCallSyncOnTabsGestureSwipeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_TabsAnimationEvent extraInfo = thisDeserializer.readTabsAnimationEvent();
    _callSync(vmContext, _resourceId, index, extraInfo);
}
void deserializeAndCallOnTextSelectionChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number selectionStart, const Ark_Number selectionEnd)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number selectionStart = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number selectionEnd = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, selectionStart, selectionEnd);
}
void deserializeAndCallSyncOnTextSelectionChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number selectionStart, const Ark_Number selectionEnd)>(thisDeserializer.readPointer());
    Ark_Number selectionStart = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number selectionEnd = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, selectionStart, selectionEnd);
}
void deserializeAndCallOnViewportFitChangedCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_ViewportFit viewportFit)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ViewportFit viewportFit = static_cast<Ark_ViewportFit>(thisDeserializer.readInt32());
    _call(_resourceId, viewportFit);
}
void deserializeAndCallSyncOnViewportFitChangedCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_ViewportFit viewportFit)>(thisDeserializer.readPointer());
    Ark_ViewportFit viewportFit = static_cast<Ark_ViewportFit>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, viewportFit);
}
void deserializeAndCallPageTransitionCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_RouteType type, const Ark_Number progress)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RouteType type = static_cast<Ark_RouteType>(thisDeserializer.readInt32());
    Ark_Number progress = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, type, progress);
}
void deserializeAndCallSyncPageTransitionCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_RouteType type, const Ark_Number progress)>(thisDeserializer.readPointer());
    Ark_RouteType type = static_cast<Ark_RouteType>(thisDeserializer.readInt32());
    Ark_Number progress = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, type, progress);
}
void deserializeAndCallPasteEventCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_PasteEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_PasteEvent event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        event_buf.value = thisDeserializer.readPasteEvent();
    }
    Opt_PasteEvent event = event_buf;
    _call(_resourceId, event);
}
void deserializeAndCallSyncPasteEventCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_PasteEvent event)>(thisDeserializer.readPointer());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_PasteEvent event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        event_buf.value = thisDeserializer.readPasteEvent();
    }
    Opt_PasteEvent event = event_buf;
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallPluginErrorCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_PluginErrorData info)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_PluginErrorData info = thisDeserializer.readPluginErrorData();
    _call(_resourceId, info);
}
void deserializeAndCallSyncPluginErrorCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PluginErrorData info)>(thisDeserializer.readPointer());
    Ark_PluginErrorData info = thisDeserializer.readPluginErrorData();
    _callSync(vmContext, _resourceId, info);
}
void deserializeAndCallScrollOnScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number xOffset, const Ark_Number yOffset, Ark_ScrollState scrollState)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number xOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number yOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    _call(_resourceId, xOffset, yOffset, scrollState);
}
void deserializeAndCallSyncScrollOnScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number xOffset, const Ark_Number yOffset, Ark_ScrollState scrollState)>(thisDeserializer.readPointer());
    Ark_Number xOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number yOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, xOffset, yOffset, scrollState);
}
void deserializeAndCallScrollOnWillScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number xOffset, const Ark_Number yOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, const Callback_OffsetResult_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number xOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number yOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Ark_ScrollSource scrollSource = static_cast<Ark_ScrollSource>(thisDeserializer.readInt32());
    Callback_OffsetResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OffsetResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OffsetResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OffsetResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OffsetResult_Void))))};
    _call(_resourceId, xOffset, yOffset, scrollState, scrollSource, _continuation);
}
void deserializeAndCallSyncScrollOnWillScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number xOffset, const Ark_Number yOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, const Callback_OffsetResult_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number xOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number yOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Ark_ScrollSource scrollSource = static_cast<Ark_ScrollSource>(thisDeserializer.readInt32());
    Callback_OffsetResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OffsetResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OffsetResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OffsetResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OffsetResult_Void))))};
    _callSync(vmContext, _resourceId, xOffset, yOffset, scrollState, scrollSource, _continuation);
}
void deserializeAndCallSearchSubmitCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String searchContent, const Opt_SubmitEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String searchContent = static_cast<Ark_String>(thisDeserializer.readString());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_SubmitEvent event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        event_buf.value = static_cast<Ark_SubmitEvent>(thisDeserializer.readSubmitEvent());
    }
    Opt_SubmitEvent event = event_buf;
    _call(_resourceId, searchContent, event);
}
void deserializeAndCallSyncSearchSubmitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String searchContent, const Opt_SubmitEvent event)>(thisDeserializer.readPointer());
    Ark_String searchContent = static_cast<Ark_String>(thisDeserializer.readString());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_SubmitEvent event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        event_buf.value = static_cast<Ark_SubmitEvent>(thisDeserializer.readSubmitEvent());
    }
    Opt_SubmitEvent event = event_buf;
    _callSync(vmContext, _resourceId, searchContent, event);
}
void deserializeAndCallShouldBuiltInRecognizerParallelWithCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureRecognizer current, const Array_GestureRecognizer others, const Callback_GestureRecognizer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_GestureRecognizer current = static_cast<Ark_GestureRecognizer>(thisDeserializer.readGestureRecognizer());
    const Ark_Int32 others_buf_length = thisDeserializer.readInt32();
    Array_GestureRecognizer others_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(others_buf)>::type,
        std::decay<decltype(*others_buf.array)>::type>(&others_buf, others_buf_length);
    for (int others_buf_i = 0; others_buf_i < others_buf_length; others_buf_i++) {
        others_buf.array[others_buf_i] = static_cast<Ark_GestureRecognizer>(thisDeserializer.readGestureRecognizer());
    }
    Array_GestureRecognizer others = others_buf;
    Callback_GestureRecognizer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureRecognizer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureRecognizer_Void))))};
    _call(_resourceId, current, others, _continuation);
}
void deserializeAndCallSyncShouldBuiltInRecognizerParallelWithCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureRecognizer current, const Array_GestureRecognizer others, const Callback_GestureRecognizer_Void continuation)>(thisDeserializer.readPointer());
    Ark_GestureRecognizer current = static_cast<Ark_GestureRecognizer>(thisDeserializer.readGestureRecognizer());
    const Ark_Int32 others_buf_length = thisDeserializer.readInt32();
    Array_GestureRecognizer others_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(others_buf)>::type,
        std::decay<decltype(*others_buf.array)>::type>(&others_buf, others_buf_length);
    for (int others_buf_i = 0; others_buf_i < others_buf_length; others_buf_i++) {
        others_buf.array[others_buf_i] = static_cast<Ark_GestureRecognizer>(thisDeserializer.readGestureRecognizer());
    }
    Array_GestureRecognizer others = others_buf;
    Callback_GestureRecognizer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureRecognizer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureRecognizer_Void))))};
    _callSync(vmContext, _resourceId, current, others, _continuation);
}
void deserializeAndCallSizeChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SizeOptions oldValue, const Ark_SizeOptions newValue)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SizeOptions oldValue = thisDeserializer.readSizeOptions();
    Ark_SizeOptions newValue = thisDeserializer.readSizeOptions();
    _call(_resourceId, oldValue, newValue);
}
void deserializeAndCallSyncSizeChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SizeOptions oldValue, const Ark_SizeOptions newValue)>(thisDeserializer.readPointer());
    Ark_SizeOptions oldValue = thisDeserializer.readSizeOptions();
    Ark_SizeOptions newValue = thisDeserializer.readSizeOptions();
    _callSync(vmContext, _resourceId, oldValue, newValue);
}
void deserializeAndCallSliderTriggerChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number value, Ark_SliderChangeMode mode)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number value = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SliderChangeMode mode = static_cast<Ark_SliderChangeMode>(thisDeserializer.readInt32());
    _call(_resourceId, value, mode);
}
void deserializeAndCallSyncSliderTriggerChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number value, Ark_SliderChangeMode mode)>(thisDeserializer.readPointer());
    Ark_Number value = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SliderChangeMode mode = static_cast<Ark_SliderChangeMode>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, value, mode);
}
void deserializeAndCallSubmitCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_EnterKeyType enterKey, const Ark_SubmitEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    Ark_SubmitEvent event = static_cast<Ark_SubmitEvent>(thisDeserializer.readSubmitEvent());
    _call(_resourceId, enterKey, event);
}
void deserializeAndCallSyncSubmitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_EnterKeyType enterKey, const Ark_SubmitEvent event)>(thisDeserializer.readPointer());
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    Ark_SubmitEvent event = static_cast<Ark_SubmitEvent>(thisDeserializer.readSubmitEvent());
    _callSync(vmContext, _resourceId, enterKey, event);
}
void deserializeAndCallTabsCustomContentTransitionCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number from, const Ark_Number to, const Callback_Opt_TabContentAnimatedTransition_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number from = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number to = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Opt_TabContentAnimatedTransition_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_TabContentAnimatedTransition_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_TabContentAnimatedTransition_Void))))};
    _call(_resourceId, from, to, _continuation);
}
void deserializeAndCallSyncTabsCustomContentTransitionCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number from, const Ark_Number to, const Callback_Opt_TabContentAnimatedTransition_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number from = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number to = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Opt_TabContentAnimatedTransition_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_TabContentAnimatedTransition_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_TabContentAnimatedTransition_Void))))};
    _callSync(vmContext, _resourceId, from, to, _continuation);
}
void deserializeAndCallTextAreaSubmitCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType, const Opt_SubmitEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_EnterKeyType enterKeyType = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_SubmitEvent event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        event_buf.value = static_cast<Ark_SubmitEvent>(thisDeserializer.readSubmitEvent());
    }
    Opt_SubmitEvent event = event_buf;
    _call(_resourceId, enterKeyType, event);
}
void deserializeAndCallSyncTextAreaSubmitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType, const Opt_SubmitEvent event)>(thisDeserializer.readPointer());
    Ark_EnterKeyType enterKeyType = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_SubmitEvent event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        event_buf.value = static_cast<Ark_SubmitEvent>(thisDeserializer.readSubmitEvent());
    }
    Opt_SubmitEvent event = event_buf;
    _callSync(vmContext, _resourceId, enterKeyType, event);
}
void deserializeAndCallTransitionFinishCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean transitionIn)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean transitionIn = thisDeserializer.readBoolean();
    _call(_resourceId, transitionIn);
}
void deserializeAndCallSyncTransitionFinishCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean transitionIn)>(thisDeserializer.readPointer());
    Ark_Boolean transitionIn = thisDeserializer.readBoolean();
    _callSync(vmContext, _resourceId, transitionIn);
}
void deserializeAndCallType_NavigationAttribute_customNavContentTransition_delegate(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NavContentInfo from, const Ark_NavContentInfo to, Ark_NavigationOperation operation, const Callback_Opt_NavigationAnimatedTransition_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NavContentInfo from = thisDeserializer.readNavContentInfo();
    Ark_NavContentInfo to = thisDeserializer.readNavContentInfo();
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Callback_Opt_NavigationAnimatedTransition_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_NavigationAnimatedTransition_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_NavigationAnimatedTransition_Void))))};
    _call(_resourceId, from, to, operation, _continuation);
}
void deserializeAndCallSyncType_NavigationAttribute_customNavContentTransition_delegate(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NavContentInfo from, const Ark_NavContentInfo to, Ark_NavigationOperation operation, const Callback_Opt_NavigationAnimatedTransition_Void continuation)>(thisDeserializer.readPointer());
    Ark_NavContentInfo from = thisDeserializer.readNavContentInfo();
    Ark_NavContentInfo to = thisDeserializer.readNavContentInfo();
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Callback_Opt_NavigationAnimatedTransition_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_NavigationAnimatedTransition_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_NavigationAnimatedTransition_Void))))};
    _callSync(vmContext, _resourceId, from, to, operation, _continuation);
}
void deserializeAndCallType_TextPickerAttribute_onChange_callback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_String_Array_String value, const Ark_Union_Number_Array_Number index)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int8 value_buf_selector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String value_buf = {};
    value_buf.selector = value_buf_selector;
    if (value_buf_selector == 0) {
        value_buf.selector = 0;
        value_buf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (value_buf_selector == 1) {
        value_buf.selector = 1;
        const Ark_Int32 value_buf_u_length = thisDeserializer.readInt32();
        Array_String value_buf_u = {};
        thisDeserializer.resizeArray<std::decay<decltype(value_buf_u)>::type,
        std::decay<decltype(*value_buf_u.array)>::type>(&value_buf_u, value_buf_u_length);
        for (int value_buf_u_i = 0; value_buf_u_i < value_buf_u_length; value_buf_u_i++) {
            value_buf_u.array[value_buf_u_i] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        value_buf.value1 = value_buf_u;
    }
    else {
        INTEROP_FATAL("One of the branches for value_buf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String value = static_cast<Ark_Union_String_Array_String>(value_buf);
    const Ark_Int8 index_buf_selector = thisDeserializer.readInt8();
    Ark_Union_Number_Array_Number index_buf = {};
    index_buf.selector = index_buf_selector;
    if (index_buf_selector == 0) {
        index_buf.selector = 0;
        index_buf.value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    }
    else if (index_buf_selector == 1) {
        index_buf.selector = 1;
        const Ark_Int32 index_buf_u_length = thisDeserializer.readInt32();
        Array_Number index_buf_u = {};
        thisDeserializer.resizeArray<std::decay<decltype(index_buf_u)>::type,
        std::decay<decltype(*index_buf_u.array)>::type>(&index_buf_u, index_buf_u_length);
        for (int index_buf_u_i = 0; index_buf_u_i < index_buf_u_length; index_buf_u_i++) {
            index_buf_u.array[index_buf_u_i] = static_cast<Ark_Number>(thisDeserializer.readNumber());
        }
        index_buf.value1 = index_buf_u;
    }
    else {
        INTEROP_FATAL("One of the branches for index_buf has to be chosen through deserialisation.");
    }
    Ark_Union_Number_Array_Number index = static_cast<Ark_Union_Number_Array_Number>(index_buf);
    _call(_resourceId, value, index);
}
void deserializeAndCallSyncType_TextPickerAttribute_onChange_callback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_String_Array_String value, const Ark_Union_Number_Array_Number index)>(thisDeserializer.readPointer());
    const Ark_Int8 value_buf_selector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String value_buf = {};
    value_buf.selector = value_buf_selector;
    if (value_buf_selector == 0) {
        value_buf.selector = 0;
        value_buf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (value_buf_selector == 1) {
        value_buf.selector = 1;
        const Ark_Int32 value_buf_u_length = thisDeserializer.readInt32();
        Array_String value_buf_u = {};
        thisDeserializer.resizeArray<std::decay<decltype(value_buf_u)>::type,
        std::decay<decltype(*value_buf_u.array)>::type>(&value_buf_u, value_buf_u_length);
        for (int value_buf_u_i = 0; value_buf_u_i < value_buf_u_length; value_buf_u_i++) {
            value_buf_u.array[value_buf_u_i] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        value_buf.value1 = value_buf_u;
    }
    else {
        INTEROP_FATAL("One of the branches for value_buf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String value = static_cast<Ark_Union_String_Array_String>(value_buf);
    const Ark_Int8 index_buf_selector = thisDeserializer.readInt8();
    Ark_Union_Number_Array_Number index_buf = {};
    index_buf.selector = index_buf_selector;
    if (index_buf_selector == 0) {
        index_buf.selector = 0;
        index_buf.value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    }
    else if (index_buf_selector == 1) {
        index_buf.selector = 1;
        const Ark_Int32 index_buf_u_length = thisDeserializer.readInt32();
        Array_Number index_buf_u = {};
        thisDeserializer.resizeArray<std::decay<decltype(index_buf_u)>::type,
        std::decay<decltype(*index_buf_u.array)>::type>(&index_buf_u, index_buf_u_length);
        for (int index_buf_u_i = 0; index_buf_u_i < index_buf_u_length; index_buf_u_i++) {
            index_buf_u.array[index_buf_u_i] = static_cast<Ark_Number>(thisDeserializer.readNumber());
        }
        index_buf.value1 = index_buf_u;
    }
    else {
        INTEROP_FATAL("One of the branches for index_buf has to be chosen through deserialisation.");
    }
    Ark_Union_Number_Array_Number index = static_cast<Ark_Union_Number_Array_Number>(index_buf);
    _callSync(vmContext, _resourceId, value, index);
}
void deserializeAndCallType_WebAttribute_onFileSelectorShow_callback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Literal_Function_callback__Object_fileSelector event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Literal_Function_callback__Object_fileSelector event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        Ark_Literal_Function_callback__Object_fileSelector event_buf_ = {};
        event_buf_.callback_ = static_cast<Ark_Function>(thisDeserializer.readFunction());
        event_buf_.fileSelector = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("Object"));
        event_buf.value = event_buf_;
    }
    Opt_Literal_Function_callback__Object_fileSelector event = event_buf;
    _call(_resourceId, event);
}
void deserializeAndCallSyncType_WebAttribute_onFileSelectorShow_callback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Literal_Function_callback__Object_fileSelector event)>(thisDeserializer.readPointer());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Literal_Function_callback__Object_fileSelector event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        Ark_Literal_Function_callback__Object_fileSelector event_buf_ = {};
        event_buf_.callback_ = static_cast<Ark_Function>(thisDeserializer.readFunction());
        event_buf_.fileSelector = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("Object"));
        event_buf.value = event_buf_;
    }
    Opt_Literal_Function_callback__Object_fileSelector event = event_buf;
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallType_WebAttribute_onUrlLoadIntercept_callback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Literal_Union_String_WebResourceRequest_data event, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Literal_Union_String_WebResourceRequest_data event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        Ark_Literal_Union_String_WebResourceRequest_data event_buf_ = {};
        const Ark_Int8 event_buf__data_buf_selector = thisDeserializer.readInt8();
        Ark_Union_String_WebResourceRequest event_buf__data_buf = {};
        event_buf__data_buf.selector = event_buf__data_buf_selector;
        if (event_buf__data_buf_selector == 0) {
            event_buf__data_buf.selector = 0;
            event_buf__data_buf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
        }
        else if (event_buf__data_buf_selector == 1) {
            event_buf__data_buf.selector = 1;
            event_buf__data_buf.value1 = static_cast<Ark_WebResourceRequest>(thisDeserializer.readWebResourceRequest());
        }
        else {
            INTEROP_FATAL("One of the branches for event_buf__data_buf has to be chosen through deserialisation.");
        }
        event_buf_.data = static_cast<Ark_Union_String_WebResourceRequest>(event_buf__data_buf);
        event_buf.value = event_buf_;
    }
    Opt_Literal_Union_String_WebResourceRequest_data event = event_buf;
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, event, _continuation);
}
void deserializeAndCallSyncType_WebAttribute_onUrlLoadIntercept_callback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Literal_Union_String_WebResourceRequest_data event, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Literal_Union_String_WebResourceRequest_data event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_buf_runtimeType))
    {
        Ark_Literal_Union_String_WebResourceRequest_data event_buf_ = {};
        const Ark_Int8 event_buf__data_buf_selector = thisDeserializer.readInt8();
        Ark_Union_String_WebResourceRequest event_buf__data_buf = {};
        event_buf__data_buf.selector = event_buf__data_buf_selector;
        if (event_buf__data_buf_selector == 0) {
            event_buf__data_buf.selector = 0;
            event_buf__data_buf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
        }
        else if (event_buf__data_buf_selector == 1) {
            event_buf__data_buf.selector = 1;
            event_buf__data_buf.value1 = static_cast<Ark_WebResourceRequest>(thisDeserializer.readWebResourceRequest());
        }
        else {
            INTEROP_FATAL("One of the branches for event_buf__data_buf has to be chosen through deserialisation.");
        }
        event_buf_.data = static_cast<Ark_Union_String_WebResourceRequest>(event_buf__data_buf);
        event_buf.value = event_buf_;
    }
    Opt_Literal_Union_String_WebResourceRequest_data event = event_buf;
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean parameter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, event, _continuation);
}
void deserializeAndCallVisibleAreaChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean isExpanding, const Ark_Number currentRatio)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean isExpanding = thisDeserializer.readBoolean();
    Ark_Number currentRatio = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, isExpanding, currentRatio);
}
void deserializeAndCallSyncVisibleAreaChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isExpanding, const Ark_Number currentRatio)>(thisDeserializer.readPointer());
    Ark_Boolean isExpanding = thisDeserializer.readBoolean();
    Ark_Number currentRatio = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, isExpanding, currentRatio);
}
void deserializeAndCallVoidCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncVoidCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    _callSync(vmContext, _resourceId);
}
void deserializeAndCallWebKeyboardCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebKeyboardCallbackInfo keyboardCallbackInfo, const Callback_WebKeyboardOptions_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_WebKeyboardCallbackInfo keyboardCallbackInfo = thisDeserializer.readWebKeyboardCallbackInfo();
    Callback_WebKeyboardOptions_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_WebKeyboardOptions_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_WebKeyboardOptions_Void))))};
    _call(_resourceId, keyboardCallbackInfo, _continuation);
}
void deserializeAndCallSyncWebKeyboardCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebKeyboardCallbackInfo keyboardCallbackInfo, const Callback_WebKeyboardOptions_Void continuation)>(thisDeserializer.readPointer());
    Ark_WebKeyboardCallbackInfo keyboardCallbackInfo = thisDeserializer.readWebKeyboardCallbackInfo();
    Callback_WebKeyboardOptions_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_WebKeyboardOptions_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_WebKeyboardOptions_Void))))};
    _callSync(vmContext, _resourceId, keyboardCallbackInfo, _continuation);
}
void deserializeAndCallWithThemeInterface(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WithThemeOptions options, const Callback_WithThemeAttribute_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_WithThemeOptions options = thisDeserializer.readWithThemeOptions();
    Callback_WithThemeAttribute_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WithThemeAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_WithThemeAttribute_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WithThemeAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_WithThemeAttribute_Void))))};
    _call(_resourceId, options, _continuation);
}
void deserializeAndCallSyncWithThemeInterface(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    Deserializer thisDeserializer = Deserializer(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WithThemeOptions options, const Callback_WithThemeAttribute_Void continuation)>(thisDeserializer.readPointer());
    Ark_WithThemeOptions options = thisDeserializer.readWithThemeOptions();
    Callback_WithThemeAttribute_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WithThemeAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_WithThemeAttribute_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WithThemeAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_WithThemeAttribute_Void))))};
    _callSync(vmContext, _resourceId, options, _continuation);
}
void deserializeAndCallCallback(Ark_Int32 kind, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    switch (kind) {
        case 589030517/*Kind_AccessibilityCallback*/: return deserializeAndCallAccessibilityCallback(thisArray, thisLength);
        case 1289587365/*Kind_AsyncCallback_image_PixelMap_Void*/: return deserializeAndCallAsyncCallback_image_PixelMap_Void(thisArray, thisLength);
        case -1964292933/*Kind_ButtonTriggerClickCallback*/: return deserializeAndCallButtonTriggerClickCallback(thisArray, thisLength);
        case 197193081/*Kind_Callback_Any_Void*/: return deserializeAndCallCallback_Any_Void(thisArray, thisLength);
        case -2024393616/*Kind_Callback_Area_Area_Void*/: return deserializeAndCallCallback_Area_Area_Void(thisArray, thisLength);
        case 582384234/*Kind_Callback_Array_Number_Void*/: return deserializeAndCallCallback_Array_Number_Void(thisArray, thisLength);
        case -440782244/*Kind_Callback_Array_String_Void*/: return deserializeAndCallCallback_Array_String_Void(thisArray, thisLength);
        case -547276916/*Kind_Callback_Array_TouchTestInfo_TouchResult*/: return deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(thisArray, thisLength);
        case -1541107680/*Kind_Callback_Boolean*/: return deserializeAndCallCallback_Boolean(thisArray, thisLength);
        case -916602978/*Kind_Callback_Boolean_HoverEvent_Void*/: return deserializeAndCallCallback_Boolean_HoverEvent_Void(thisArray, thisLength);
        case 313269291/*Kind_Callback_Boolean_Void*/: return deserializeAndCallCallback_Boolean_Void(thisArray, thisLength);
        case 1074619005/*Kind_Callback_CalendarRequestedData_Void*/: return deserializeAndCallCallback_CalendarRequestedData_Void(thisArray, thisLength);
        case -289198976/*Kind_Callback_CalendarSelectedDate_Void*/: return deserializeAndCallCallback_CalendarSelectedDate_Void(thisArray, thisLength);
        case -1189087745/*Kind_Callback_ClickEvent_LocationButtonOnClickResult_Void*/: return deserializeAndCallCallback_ClickEvent_LocationButtonOnClickResult_Void(thisArray, thisLength);
        case 659292561/*Kind_Callback_ClickEvent_PasteButtonOnClickResult_Void*/: return deserializeAndCallCallback_ClickEvent_PasteButtonOnClickResult_Void(thisArray, thisLength);
        case 846787331/*Kind_Callback_ClickEvent_SaveButtonOnClickResult_Void*/: return deserializeAndCallCallback_ClickEvent_SaveButtonOnClickResult_Void(thisArray, thisLength);
        case 1097178637/*Kind_Callback_ClickEvent_Void*/: return deserializeAndCallCallback_ClickEvent_Void(thisArray, thisLength);
        case -1270343661/*Kind_Callback_ComputedBarAttribute_Void*/: return deserializeAndCallCallback_ComputedBarAttribute_Void(thisArray, thisLength);
        case -120437466/*Kind_Callback_CopyEvent_Void*/: return deserializeAndCallCallback_CopyEvent_Void(thisArray, thisLength);
        case -721106019/*Kind_Callback_CustomBuilder_Void*/: return deserializeAndCallCallback_CustomBuilder_Void(thisArray, thisLength);
        case -1875695871/*Kind_Callback_CutEvent_Void*/: return deserializeAndCallCallback_CutEvent_Void(thisArray, thisLength);
        case 1405382363/*Kind_Callback_Date_Void*/: return deserializeAndCallCallback_Date_Void(thisArray, thisLength);
        case 1280920532/*Kind_Callback_DatePickerResult_Void*/: return deserializeAndCallCallback_DatePickerResult_Void(thisArray, thisLength);
        case -1357792883/*Kind_Callback_DeleteValue_Boolean*/: return deserializeAndCallCallback_DeleteValue_Boolean(thisArray, thisLength);
        case -126251459/*Kind_Callback_DeleteValue_Void*/: return deserializeAndCallCallback_DeleteValue_Void(thisArray, thisLength);
        case -1283506641/*Kind_Callback_DismissContentCoverAction_Void*/: return deserializeAndCallCallback_DismissContentCoverAction_Void(thisArray, thisLength);
        case -2095828093/*Kind_Callback_DismissDialogAction_Void*/: return deserializeAndCallCallback_DismissDialogAction_Void(thisArray, thisLength);
        case -2004166751/*Kind_Callback_DismissPopupAction_Void*/: return deserializeAndCallCallback_DismissPopupAction_Void(thisArray, thisLength);
        case 889549796/*Kind_Callback_DismissSheetAction_Void*/: return deserializeAndCallCallback_DismissSheetAction_Void(thisArray, thisLength);
        case 480978023/*Kind_Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo*/: return deserializeAndCallCallback_DragEvent_String_Union_CustomBuilder_DragItemInfo(thisArray, thisLength);
        case -17167687/*Kind_Callback_DragEvent_String_Void*/: return deserializeAndCallCallback_DragEvent_String_Void(thisArray, thisLength);
        case -1802605016/*Kind_Callback_EnterKeyType_Void*/: return deserializeAndCallCallback_EnterKeyType_Void(thisArray, thisLength);
        case -733525640/*Kind_Callback_Extender_OnFinish*/: return deserializeAndCallCallback_Extender_OnFinish(thisArray, thisLength);
        case 1264236374/*Kind_Callback_Extender_OnProgress*/: return deserializeAndCallCallback_Extender_OnProgress(thisArray, thisLength);
        case 758395742/*Kind_Callback_FormCallbackInfo_Void*/: return deserializeAndCallCallback_FormCallbackInfo_Void(thisArray, thisLength);
        case 583294398/*Kind_Callback_FullscreenInfo_Void*/: return deserializeAndCallCallback_FullscreenInfo_Void(thisArray, thisLength);
        case -1143194492/*Kind_Callback_GestureEvent_Void*/: return deserializeAndCallCallback_GestureEvent_Void(thisArray, thisLength);
        case 1319043556/*Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult*/: return deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(thisArray, thisLength);
        case -684588584/*Kind_Callback_GestureJudgeResult_Void*/: return deserializeAndCallCallback_GestureJudgeResult_Void(thisArray, thisLength);
        case 776202910/*Kind_Callback_GestureRecognizer_Void*/: return deserializeAndCallCallback_GestureRecognizer_Void(thisArray, thisLength);
        case -1755111025/*Kind_Callback_HitTestMode_Void*/: return deserializeAndCallCallback_HitTestMode_Void(thisArray, thisLength);
        case -383025085/*Kind_Callback_InsertValue_Boolean*/: return deserializeAndCallCallback_InsertValue_Boolean(thisArray, thisLength);
        case -1121207885/*Kind_Callback_InsertValue_Void*/: return deserializeAndCallCallback_InsertValue_Void(thisArray, thisLength);
        case 719029905/*Kind_Callback_IsolatedComponentAttribute_Void*/: return deserializeAndCallCallback_IsolatedComponentAttribute_Void(thisArray, thisLength);
        case -1627362945/*Kind_Callback_ItemDragInfo_Number_Number_Boolean_Void*/: return deserializeAndCallCallback_ItemDragInfo_Number_Number_Boolean_Void(thisArray, thisLength);
        case -918805852/*Kind_Callback_ItemDragInfo_Number_Number_Void*/: return deserializeAndCallCallback_ItemDragInfo_Number_Number_Void(thisArray, thisLength);
        case 296908152/*Kind_Callback_ItemDragInfo_Number_Void*/: return deserializeAndCallCallback_ItemDragInfo_Number_Void(thisArray, thisLength);
        case 137353252/*Kind_Callback_ItemDragInfo_Void*/: return deserializeAndCallCallback_ItemDragInfo_Void(thisArray, thisLength);
        case -2061548092/*Kind_Callback_KeyEvent_Boolean*/: return deserializeAndCallCallback_KeyEvent_Boolean(thisArray, thisLength);
        case 707696468/*Kind_Callback_KeyEvent_Void*/: return deserializeAndCallCallback_KeyEvent_Void(thisArray, thisLength);
        case -1561407084/*Kind_Callback_Literal_Boolean_isVisible_Void*/: return deserializeAndCallCallback_Literal_Boolean_isVisible_Void(thisArray, thisLength);
        case 361012115/*Kind_Callback_Literal_Function_handler_Object_error_Void*/: return deserializeAndCallCallback_Literal_Function_handler_Object_error_Void(thisArray, thisLength);
        case -582934742/*Kind_Callback_Literal_Number_code_Want_want_Void*/: return deserializeAndCallCallback_Literal_Number_code_Want_want_Void(thisArray, thisLength);
        case 1321277443/*Kind_Callback_Literal_Number_errcode_String_msg_Void*/: return deserializeAndCallCallback_Literal_Number_errcode_String_msg_Void(thisArray, thisLength);
        case -251706058/*Kind_Callback_Literal_Number_offsetRemain_Void*/: return deserializeAndCallCallback_Literal_Number_offsetRemain_Void(thisArray, thisLength);
        case 222742448/*Kind_Callback_Literal_Object_detail_Boolean*/: return deserializeAndCallCallback_Literal_Object_detail_Boolean(thisArray, thisLength);
        case -122223466/*Kind_Callback_Literal_String_plainText_Void*/: return deserializeAndCallCallback_Literal_String_plainText_Void(thisArray, thisLength);
        case -1382640094/*Kind_Callback_MouseEvent_Void*/: return deserializeAndCallCallback_MouseEvent_Void(thisArray, thisLength);
        case 477481563/*Kind_Callback_NativeEmbedDataInfo_Void*/: return deserializeAndCallCallback_NativeEmbedDataInfo_Void(thisArray, thisLength);
        case -1090303858/*Kind_Callback_NativeEmbedTouchInfo_Void*/: return deserializeAndCallCallback_NativeEmbedTouchInfo_Void(thisArray, thisLength);
        case -1642725259/*Kind_Callback_NavDestinationContext_Void*/: return deserializeAndCallCallback_NavDestinationContext_Void(thisArray, thisLength);
        case 960690982/*Kind_Callback_NavigationMode_Void*/: return deserializeAndCallCallback_NavigationMode_Void(thisArray, thisLength);
        case 1685437830/*Kind_Callback_NavigationTitleMode_Void*/: return deserializeAndCallCallback_NavigationTitleMode_Void(thisArray, thisLength);
        case -1375731066/*Kind_Callback_NavigationTransitionProxy_Void*/: return deserializeAndCallCallback_NavigationTransitionProxy_Void(thisArray, thisLength);
        case 1054099324/*Kind_Callback_Number_Boolean*/: return deserializeAndCallCallback_Number_Boolean(thisArray, thisLength);
        case -1427334496/*Kind_Callback_Number_Number_Boolean*/: return deserializeAndCallCallback_Number_Number_Boolean(thisArray, thisLength);
        case -3987624/*Kind_Callback_Number_Number_ComputedBarAttribute*/: return deserializeAndCallCallback_Number_Number_ComputedBarAttribute(thisArray, thisLength);
        case -352942292/*Kind_Callback_Number_Number_Number_Void*/: return deserializeAndCallCallback_Number_Number_Number_Void(thisArray, thisLength);
        case 1613628570/*Kind_Callback_Number_Number_PanelMode_Void*/: return deserializeAndCallCallback_Number_Number_PanelMode_Void(thisArray, thisLength);
        case 1894574320/*Kind_Callback_Number_Number_Void*/: return deserializeAndCallCallback_Number_Number_Void(thisArray, thisLength);
        case 2012829508/*Kind_Callback_Number_ScrollState_Literal_Number_offsetRemain*/: return deserializeAndCallCallback_Number_ScrollState_Literal_Number_offsetRemain(thisArray, thisLength);
        case 88697971/*Kind_Callback_Number_SliderChangeMode_Void*/: return deserializeAndCallCallback_Number_SliderChangeMode_Void(thisArray, thisLength);
        case 794065478/*Kind_Callback_Number_String_Void*/: return deserializeAndCallCallback_Number_String_Void(thisArray, thisLength);
        case 1602877440/*Kind_Callback_Number_Tuple_Number_Number*/: return deserializeAndCallCallback_Number_Tuple_Number_Number(thisArray, thisLength);
        case 1618565120/*Kind_Callback_Number_Tuple_Number_Number_Number_Number*/: return deserializeAndCallCallback_Number_Tuple_Number_Number_Number_Number(thisArray, thisLength);
        case 36519084/*Kind_Callback_Number_Void*/: return deserializeAndCallCallback_Number_Void(thisArray, thisLength);
        case 1295952075/*Kind_Callback_OffsetResult_Void*/: return deserializeAndCallCallback_OffsetResult_Void(thisArray, thisLength);
        case 1385252075/*Kind_Callback_ScrollResult_Void*/: return deserializeAndCallCallback_ScrollResult_Void(thisArray, thisLength);
        case 806070428/*Kind_Callback_OnAlertEvent_Boolean*/: return deserializeAndCallCallback_OnAlertEvent_Boolean(thisArray, thisLength);
        case -1559789631/*Kind_Callback_OnAudioStateChangedEvent_Void*/: return deserializeAndCallCallback_OnAudioStateChangedEvent_Void(thisArray, thisLength);
        case -873162122/*Kind_Callback_OnBeforeUnloadEvent_Boolean*/: return deserializeAndCallCallback_OnBeforeUnloadEvent_Boolean(thisArray, thisLength);
        case 608991355/*Kind_Callback_OnClientAuthenticationEvent_Void*/: return deserializeAndCallCallback_OnClientAuthenticationEvent_Void(thisArray, thisLength);
        case 317864672/*Kind_Callback_OnConfirmEvent_Boolean*/: return deserializeAndCallCallback_OnConfirmEvent_Boolean(thisArray, thisLength);
        case 893367077/*Kind_Callback_OnConsoleEvent_Boolean*/: return deserializeAndCallCallback_OnConsoleEvent_Boolean(thisArray, thisLength);
        case 332449533/*Kind_Callback_OnContextMenuShowEvent_Boolean*/: return deserializeAndCallCallback_OnContextMenuShowEvent_Boolean(thisArray, thisLength);
        case 118631204/*Kind_Callback_OnDataResubmittedEvent_Void*/: return deserializeAndCallCallback_OnDataResubmittedEvent_Void(thisArray, thisLength);
        case 1834611702/*Kind_Callback_OnDownloadStartEvent_Void*/: return deserializeAndCallCallback_OnDownloadStartEvent_Void(thisArray, thisLength);
        case -1792851375/*Kind_Callback_OnErrorReceiveEvent_Void*/: return deserializeAndCallCallback_OnErrorReceiveEvent_Void(thisArray, thisLength);
        case -243916553/*Kind_Callback_OnFaviconReceivedEvent_Void*/: return deserializeAndCallCallback_OnFaviconReceivedEvent_Void(thisArray, thisLength);
        case -1852060212/*Kind_Callback_OnFirstContentfulPaintEvent_Void*/: return deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(thisArray, thisLength);
        case -941896815/*Kind_Callback_OnGeolocationShowEvent_Void*/: return deserializeAndCallCallback_OnGeolocationShowEvent_Void(thisArray, thisLength);
        case 780282803/*Kind_Callback_OnHttpAuthRequestEvent_Boolean*/: return deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(thisArray, thisLength);
        case -2066745559/*Kind_Callback_OnHttpErrorReceiveEvent_Void*/: return deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(thisArray, thisLength);
        case 1442698200/*Kind_Callback_OnInterceptRequestEvent_WebResourceResponse*/: return deserializeAndCallCallback_OnInterceptRequestEvent_WebResourceResponse(thisArray, thisLength);
        case 1231444306/*Kind_Callback_OnLoadInterceptEvent_Boolean*/: return deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(thisArray, thisLength);
        case -860386431/*Kind_Callback_OnOverScrollEvent_Void*/: return deserializeAndCallCallback_OnOverScrollEvent_Void(thisArray, thisLength);
        case -2040193994/*Kind_Callback_OnPageBeginEvent_Void*/: return deserializeAndCallCallback_OnPageBeginEvent_Void(thisArray, thisLength);
        case -130135362/*Kind_Callback_OnPageEndEvent_Void*/: return deserializeAndCallCallback_OnPageEndEvent_Void(thisArray, thisLength);
        case 1805946367/*Kind_Callback_OnPageVisibleEvent_Void*/: return deserializeAndCallCallback_OnPageVisibleEvent_Void(thisArray, thisLength);
        case 529980696/*Kind_Callback_OnPermissionRequestEvent_Void*/: return deserializeAndCallCallback_OnPermissionRequestEvent_Void(thisArray, thisLength);
        case 1018740377/*Kind_Callback_OnProgressChangeEvent_Void*/: return deserializeAndCallCallback_OnProgressChangeEvent_Void(thisArray, thisLength);
        case -1826742986/*Kind_Callback_OnPromptEvent_Boolean*/: return deserializeAndCallCallback_OnPromptEvent_Boolean(thisArray, thisLength);
        case 1978364344/*Kind_Callback_OnRefreshAccessedHistoryEvent_Void*/: return deserializeAndCallCallback_OnRefreshAccessedHistoryEvent_Void(thisArray, thisLength);
        case -1413785559/*Kind_Callback_OnRenderExitedEvent_Void*/: return deserializeAndCallCallback_OnRenderExitedEvent_Void(thisArray, thisLength);
        case 793995118/*Kind_Callback_OnResourceLoadEvent_Void*/: return deserializeAndCallCallback_OnResourceLoadEvent_Void(thisArray, thisLength);
        case -1782102148/*Kind_Callback_OnScaleChangeEvent_Void*/: return deserializeAndCallCallback_OnScaleChangeEvent_Void(thisArray, thisLength);
        case -1972321573/*Kind_Callback_OnScreenCaptureRequestEvent_Void*/: return deserializeAndCallCallback_OnScreenCaptureRequestEvent_Void(thisArray, thisLength);
        case -172908881/*Kind_Callback_OnScrollEvent_Void*/: return deserializeAndCallCallback_OnScrollEvent_Void(thisArray, thisLength);
        case 1637092936/*Kind_Callback_OnScrollFrameBeginHandlerResult_Void*/: return deserializeAndCallCallback_OnScrollFrameBeginHandlerResult_Void(thisArray, thisLength);
        case -1495570/*Kind_Callback_OnSearchResultReceiveEvent_Void*/: return deserializeAndCallCallback_OnSearchResultReceiveEvent_Void(thisArray, thisLength);
        case -636069598/*Kind_Callback_OnShowFileSelectorEvent_Boolean*/: return deserializeAndCallCallback_OnShowFileSelectorEvent_Boolean(thisArray, thisLength);
        case 1624791665/*Kind_Callback_OnSslErrorEventReceiveEvent_Void*/: return deserializeAndCallCallback_OnSslErrorEventReceiveEvent_Void(thisArray, thisLength);
        case -318085495/*Kind_Callback_OnTitleReceiveEvent_Void*/: return deserializeAndCallCallback_OnTitleReceiveEvent_Void(thisArray, thisLength);
        case 1657893064/*Kind_Callback_OnTouchIconUrlReceivedEvent_Void*/: return deserializeAndCallCallback_OnTouchIconUrlReceivedEvent_Void(thisArray, thisLength);
        case -2052382574/*Kind_Callback_OnWindowNewEvent_Void*/: return deserializeAndCallCallback_OnWindowNewEvent_Void(thisArray, thisLength);
        case -543655128/*Kind_Callback_Opt_Array_String_Void*/: return deserializeAndCallCallback_Opt_Array_String_Void(thisArray, thisLength);
        case -2035339519/*Kind_Callback_Opt_NavigationAnimatedTransition_Void*/: return deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(thisArray, thisLength);
        case -756319131/*Kind_Callback_Opt_StyledString_Opt_Array_String_Void*/: return deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(thisArray, thisLength);
        case -143931627/*Kind_Callback_Opt_TabContentAnimatedTransition_Void*/: return deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(thisArray, thisLength);
        case 388680218/*Kind_Callback_PanelMode_Void*/: return deserializeAndCallCallback_PanelMode_Void(thisArray, thisLength);
        case -2058966418/*Kind_Callback_PlaybackInfo_Void*/: return deserializeAndCallCallback_PlaybackInfo_Void(thisArray, thisLength);
        case 721562324/*Kind_Callback_Pointer_Void*/: return deserializeAndCallCallback_Pointer_Void(thisArray, thisLength);
        case 624053870/*Kind_Callback_PopInfo_Void*/: return deserializeAndCallCallback_PopInfo_Void(thisArray, thisLength);
        case 463894668/*Kind_Callback_PreDragStatus_Void*/: return deserializeAndCallCallback_PreDragStatus_Void(thisArray, thisLength);
        case 1300890372/*Kind_Callback_PreparedInfo_Void*/: return deserializeAndCallCallback_PreparedInfo_Void(thisArray, thisLength);
        case 797834474/*Kind_Callback_RangeUpdate*/: return deserializeAndCallCallback_RangeUpdate(thisArray, thisLength);
        case 934309126/*Kind_Callback_RefreshStatus_Void*/: return deserializeAndCallCallback_RefreshStatus_Void(thisArray, thisLength);
        case 188373904/*Kind_Callback_ResourceStr_Void*/: return deserializeAndCallCallback_ResourceStr_Void(thisArray, thisLength);
        case 1465860515/*Kind_Callback_RichEditorChangeValue_Boolean*/: return deserializeAndCallCallback_RichEditorChangeValue_Boolean(thisArray, thisLength);
        case 667698748/*Kind_Callback_RichEditorDeleteValue_Boolean*/: return deserializeAndCallCallback_RichEditorDeleteValue_Boolean(thisArray, thisLength);
        case -319221262/*Kind_Callback_RichEditorInsertValue_Boolean*/: return deserializeAndCallCallback_RichEditorInsertValue_Boolean(thisArray, thisLength);
        case -62253375/*Kind_Callback_RichEditorRange_Void*/: return deserializeAndCallCallback_RichEditorRange_Void(thisArray, thisLength);
        case -963852514/*Kind_Callback_RichEditorSelection_Void*/: return deserializeAndCallCallback_RichEditorSelection_Void(thisArray, thisLength);
        case 1980824326/*Kind_Callback_RichEditorTextSpanResult_Void*/: return deserializeAndCallCallback_RichEditorTextSpanResult_Void(thisArray, thisLength);
        case 22609082/*Kind_Callback_SheetDismiss_Void*/: return deserializeAndCallCallback_SheetDismiss_Void(thisArray, thisLength);
        case -224451112/*Kind_Callback_SheetType_Void*/: return deserializeAndCallCallback_SheetType_Void(thisArray, thisLength);
        case 1536231691/*Kind_Callback_SpringBackAction_Void*/: return deserializeAndCallCallback_SpringBackAction_Void(thisArray, thisLength);
        case -879490874/*Kind_Callback_String_Number_Void*/: return deserializeAndCallCallback_String_Number_Void(thisArray, thisLength);
        case -683652998/*Kind_Callback_String_PasteEvent_Void*/: return deserializeAndCallCallback_String_PasteEvent_Void(thisArray, thisLength);
        case -1493806035/*Kind_Callback_String_Unknown_Void*/: return deserializeAndCallCallback_String_Unknown_Void(thisArray, thisLength);
        case 814634522/*Kind_Callback_String_Void*/: return deserializeAndCallCallback_String_Void(thisArray, thisLength);
        case 2116745428/*Kind_Callback_StyledStringChangeValue_Boolean*/: return deserializeAndCallCallback_StyledStringChangeValue_Boolean(thisArray, thisLength);
        case -301561698/*Kind_Callback_SwipeActionState_Void*/: return deserializeAndCallCallback_SwipeActionState_Void(thisArray, thisLength);
        case -416053361/*Kind_Callback_SwiperContentTransitionProxy_Void*/: return deserializeAndCallCallback_SwiperContentTransitionProxy_Void(thisArray, thisLength);
        case -1223938478/*Kind_Callback_TabContentTransitionProxy_Void*/: return deserializeAndCallCallback_TabContentTransitionProxy_Void(thisArray, thisLength);
        case 691098197/*Kind_Callback_TerminationInfo_Void*/: return deserializeAndCallCallback_TerminationInfo_Void(thisArray, thisLength);
        case 1290504509/*Kind_Callback_TextPickerResult_Void*/: return deserializeAndCallCallback_TextPickerResult_Void(thisArray, thisLength);
        case 811915501/*Kind_Callback_TextRange_Void*/: return deserializeAndCallCallback_TextRange_Void(thisArray, thisLength);
        case 1557859605/*Kind_Callback_TimePickerResult_Void*/: return deserializeAndCallCallback_TimePickerResult_Void(thisArray, thisLength);
        case -274419246/*Kind_Callback_TouchEvent_HitTestMode*/: return deserializeAndCallCallback_TouchEvent_HitTestMode(thisArray, thisLength);
        case -1676021850/*Kind_Callback_TouchEvent_Void*/: return deserializeAndCallCallback_TouchEvent_Void(thisArray, thisLength);
        case 1943507619/*Kind_Callback_TouchResult_Void*/: return deserializeAndCallCallback_TouchResult_Void(thisArray, thisLength);
        case 148489367/*Kind_Callback_Tuple_Number_Number_Number_Number_Void*/: return deserializeAndCallCallback_Tuple_Number_Number_Number_Number_Void(thisArray, thisLength);
        case -607365481/*Kind_Callback_Tuple_Number_Number_Void*/: return deserializeAndCallCallback_Tuple_Number_Number_Void(thisArray, thisLength);
        case -1352745727/*Kind_Callback_Type_ImageAttribute_onComplete_callback_event_Void*/: return deserializeAndCallCallback_Type_ImageAttribute_onComplete_callback_event_Void(thisArray, thisLength);
        case -1063506522/*Kind_Callback_UIExtensionProxy_Void*/: return deserializeAndCallCallback_UIExtensionProxy_Void(thisArray, thisLength);
        case -620935067/*Kind_Callback_Union_CustomBuilder_DragItemInfo_Void*/: return deserializeAndCallCallback_Union_CustomBuilder_DragItemInfo_Void(thisArray, thisLength);
        case -1111620998/*Kind_Callback_Union_Number_Array_Number_Void*/: return deserializeAndCallCallback_Union_Number_Array_Number_Void(thisArray, thisLength);
        case -956455499/*Kind_Callback_Union_Number_Resource_Void*/: return deserializeAndCallCallback_Union_Number_Resource_Void(thisArray, thisLength);
        case -720435526/*Kind_Callback_Union_String_Array_String_Void*/: return deserializeAndCallCallback_Union_String_Array_String_Void(thisArray, thisLength);
        case -1867723152/*Kind_Callback_Void*/: return deserializeAndCallCallback_Void(thisArray, thisLength);
        case -1376223390/*Kind_Callback_WebKeyboardOptions_Void*/: return deserializeAndCallCallback_WebKeyboardOptions_Void(thisArray, thisLength);
        case 831645046/*Kind_Callback_WebResourceResponse_Void*/: return deserializeAndCallCallback_WebResourceResponse_Void(thisArray, thisLength);
        case 1436479104/*Kind_Callback_WithThemeAttribute_Void*/: return deserializeAndCallCallback_WithThemeAttribute_Void(thisArray, thisLength);
        case 1532328438/*Kind_ContentDidScrollCallback*/: return deserializeAndCallContentDidScrollCallback(thisArray, thisLength);
        case 1766817632/*Kind_CustomNodeBuilder*/: return deserializeAndCallCustomNodeBuilder(thisArray, thisLength);
        case -1729563209/*Kind_EditableTextOnChangeCallback*/: return deserializeAndCallEditableTextOnChangeCallback(thisArray, thisLength);
        case -1936519453/*Kind_ErrorCallback*/: return deserializeAndCallErrorCallback(thisArray, thisLength);
        case -2119548940/*Kind_GestureRecognizerJudgeBeginCallback*/: return deserializeAndCallGestureRecognizerJudgeBeginCallback(thisArray, thisLength);
        case -2076995110/*Kind_GetItemMainSizeByIndex*/: return deserializeAndCallGetItemMainSizeByIndex(thisArray, thisLength);
        case 68560477/*Kind_HoverCallback*/: return deserializeAndCallHoverCallback(thisArray, thisLength);
        case -1180567691/*Kind_ImageCompleteCallback*/: return deserializeAndCallImageCompleteCallback(thisArray, thisLength);
        case 1906248580/*Kind_ImageErrorCallback*/: return deserializeAndCallImageErrorCallback(thisArray, thisLength);
        case 1502213270/*Kind_InterceptionModeCallback*/: return deserializeAndCallInterceptionModeCallback(thisArray, thisLength);
        case 1852781814/*Kind_InterceptionShowCallback*/: return deserializeAndCallInterceptionShowCallback(thisArray, thisLength);
        case 2139680213/*Kind_IsolatedComponentInterface*/: return deserializeAndCallIsolatedComponentInterface(thisArray, thisLength);
        case -614475458/*Kind_MenuOnAppearCallback*/: return deserializeAndCallMenuOnAppearCallback(thisArray, thisLength);
        case -588228933/*Kind_NavExtender_OnUpdateStack*/: return deserializeAndCallNavExtender_OnUpdateStack(thisArray, thisLength);
        case 1572284740/*Kind_OnAdsBlockedCallback*/: return deserializeAndCallOnAdsBlockedCallback(thisArray, thisLength);
        case 726938390/*Kind_OnAlphabetIndexerPopupSelectCallback*/: return deserializeAndCallOnAlphabetIndexerPopupSelectCallback(thisArray, thisLength);
        case -1956514817/*Kind_OnAlphabetIndexerRequestPopupDataCallback*/: return deserializeAndCallOnAlphabetIndexerRequestPopupDataCallback(thisArray, thisLength);
        case -1189721220/*Kind_OnAlphabetIndexerSelectCallback*/: return deserializeAndCallOnAlphabetIndexerSelectCallback(thisArray, thisLength);
        case -1198592337/*Kind_OnCheckboxChangeCallback*/: return deserializeAndCallOnCheckboxChangeCallback(thisArray, thisLength);
        case -1053064240/*Kind_OnCheckboxGroupChangeCallback*/: return deserializeAndCallOnCheckboxGroupChangeCallback(thisArray, thisLength);
        case -419979106/*Kind_OnContentScrollCallback*/: return deserializeAndCallOnContentScrollCallback(thisArray, thisLength);
        case 1788572278/*Kind_OnContextMenuHideCallback*/: return deserializeAndCallOnContextMenuHideCallback(thisArray, thisLength);
        case 1648184341/*Kind_OnDidChangeCallback*/: return deserializeAndCallOnDidChangeCallback(thisArray, thisLength);
        case 767275770/*Kind_OnFirstMeaningfulPaintCallback*/: return deserializeAndCallOnFirstMeaningfulPaintCallback(thisArray, thisLength);
        case 2050387049/*Kind_OnFoldStatusChangeCallback*/: return deserializeAndCallOnFoldStatusChangeCallback(thisArray, thisLength);
        case 81230317/*Kind_OnFullScreenEnterCallback*/: return deserializeAndCallOnFullScreenEnterCallback(thisArray, thisLength);
        case 9040430/*Kind_OnHoverStatusChangeCallback*/: return deserializeAndCallOnHoverStatusChangeCallback(thisArray, thisLength);
        case -1377876844/*Kind_OnIntelligentTrackingPreventionCallback*/: return deserializeAndCallOnIntelligentTrackingPreventionCallback(thisArray, thisLength);
        case 1340995650/*Kind_onItemDragStart_event_type*/: return deserializeAndCallonItemDragStart_event_type(thisArray, thisLength);
        case 1390640532/*Kind_OnLargestContentfulPaintCallback*/: return deserializeAndCallOnLargestContentfulPaintCallback(thisArray, thisLength);
        case -968773856/*Kind_OnLinearIndicatorChangeCallback*/: return deserializeAndCallOnLinearIndicatorChangeCallback(thisArray, thisLength);
        case -1200281222/*Kind_OnMoveHandler*/: return deserializeAndCallOnMoveHandler(thisArray, thisLength);
        case -1641338704/*Kind_OnNativeEmbedVisibilityChangeCallback*/: return deserializeAndCallOnNativeEmbedVisibilityChangeCallback(thisArray, thisLength);
        case -823037763/*Kind_OnNativeLoadCallback*/: return deserializeAndCallOnNativeLoadCallback(thisArray, thisLength);
        case -398722176/*Kind_OnNavigationEntryCommittedCallback*/: return deserializeAndCallOnNavigationEntryCommittedCallback(thisArray, thisLength);
        case 865258467/*Kind_OnOverrideUrlLoadingCallback*/: return deserializeAndCallOnOverrideUrlLoadingCallback(thisArray, thisLength);
        case 1738363337/*Kind_OnPasteCallback*/: return deserializeAndCallOnPasteCallback(thisArray, thisLength);
        case 47282303/*Kind_OnRenderProcessNotRespondingCallback*/: return deserializeAndCallOnRenderProcessNotRespondingCallback(thisArray, thisLength);
        case 1334389194/*Kind_OnRenderProcessRespondingCallback*/: return deserializeAndCallOnRenderProcessRespondingCallback(thisArray, thisLength);
        case -1099824577/*Kind_OnSafeBrowsingCheckResultCallback*/: return deserializeAndCallOnSafeBrowsingCheckResultCallback(thisArray, thisLength);
        case -160015401/*Kind_OnScrollCallback*/: return deserializeAndCallOnScrollCallback(thisArray, thisLength);
        case -150015401/*Kind_OnWillScrollCallback*/: return deserializeAndCallOnWillScrollCallback(thisArray, thisLength);
        case -1259214476/*Kind_OnScrollEdgeCallback*/: return deserializeAndCallOnScrollEdgeCallback(thisArray, thisLength);
        case -2133791987/*Kind_OnScrollFrameBeginCallback*/: return deserializeAndCallOnScrollFrameBeginCallback(thisArray, thisLength);
        case 625641334/*Kind_OnScrollVisibleContentChangeCallback*/: return deserializeAndCallOnScrollVisibleContentChangeCallback(thisArray, thisLength);
        case -399603614/*Kind_OnSslErrorEventCallback*/: return deserializeAndCallOnSslErrorEventCallback(thisArray, thisLength);
        case -1961646162/*Kind_OnSubmitCallback*/: return deserializeAndCallOnSubmitCallback(thisArray, thisLength);
        case -143686583/*Kind_OnSwiperAnimationEndCallback*/: return deserializeAndCallOnSwiperAnimationEndCallback(thisArray, thisLength);
        case 876602502/*Kind_OnSwiperAnimationStartCallback*/: return deserializeAndCallOnSwiperAnimationStartCallback(thisArray, thisLength);
        case 606029871/*Kind_OnSwiperGestureSwipeCallback*/: return deserializeAndCallOnSwiperGestureSwipeCallback(thisArray, thisLength);
        case 1942856551/*Kind_OnTabsAnimationEndCallback*/: return deserializeAndCallOnTabsAnimationEndCallback(thisArray, thisLength);
        case -147408344/*Kind_OnTabsAnimationStartCallback*/: return deserializeAndCallOnTabsAnimationStartCallback(thisArray, thisLength);
        case -349727249/*Kind_OnTabsContentWillChangeCallback*/: return deserializeAndCallOnTabsContentWillChangeCallback(thisArray, thisLength);
        case 253696833/*Kind_OnTabsGestureSwipeCallback*/: return deserializeAndCallOnTabsGestureSwipeCallback(thisArray, thisLength);
        case 695228737/*Kind_OnTextSelectionChangeCallback*/: return deserializeAndCallOnTextSelectionChangeCallback(thisArray, thisLength);
        case 1847083191/*Kind_OnViewportFitChangedCallback*/: return deserializeAndCallOnViewportFitChangedCallback(thisArray, thisLength);
        case 1627123591/*Kind_PageTransitionCallback*/: return deserializeAndCallPageTransitionCallback(thisArray, thisLength);
        case 919057028/*Kind_PasteEventCallback*/: return deserializeAndCallPasteEventCallback(thisArray, thisLength);
        case -1992671958/*Kind_PluginErrorCallback*/: return deserializeAndCallPluginErrorCallback(thisArray, thisLength);
        case -1265626662/*Kind_ScrollOnScrollCallback*/: return deserializeAndCallScrollOnScrollCallback(thisArray, thisLength);
        case -721521596/*Kind_ScrollOnWillScrollCallback*/: return deserializeAndCallScrollOnWillScrollCallback(thisArray, thisLength);
        case 1717691617/*Kind_SearchSubmitCallback*/: return deserializeAndCallSearchSubmitCallback(thisArray, thisLength);
        case -250780276/*Kind_ShouldBuiltInRecognizerParallelWithCallback*/: return deserializeAndCallShouldBuiltInRecognizerParallelWithCallback(thisArray, thisLength);
        case -1716637992/*Kind_SizeChangeCallback*/: return deserializeAndCallSizeChangeCallback(thisArray, thisLength);
        case 711649376/*Kind_SliderTriggerChangeCallback*/: return deserializeAndCallSliderTriggerChangeCallback(thisArray, thisLength);
        case -712186065/*Kind_SubmitCallback*/: return deserializeAndCallSubmitCallback(thisArray, thisLength);
        case 221706282/*Kind_TabsCustomContentTransitionCallback*/: return deserializeAndCallTabsCustomContentTransitionCallback(thisArray, thisLength);
        case -401980571/*Kind_TextAreaSubmitCallback*/: return deserializeAndCallTextAreaSubmitCallback(thisArray, thisLength);
        case -1878458553/*Kind_TransitionFinishCallback*/: return deserializeAndCallTransitionFinishCallback(thisArray, thisLength);
        case 1044833488/*Kind_Type_NavigationAttribute_customNavContentTransition_delegate*/: return deserializeAndCallType_NavigationAttribute_customNavContentTransition_delegate(thisArray, thisLength);
        case -1078223620/*Kind_Type_TextPickerAttribute_onChange_callback*/: return deserializeAndCallType_TextPickerAttribute_onChange_callback(thisArray, thisLength);
        case 1962174977/*Kind_Type_WebAttribute_onFileSelectorShow_callback*/: return deserializeAndCallType_WebAttribute_onFileSelectorShow_callback(thisArray, thisLength);
        case -985284966/*Kind_Type_WebAttribute_onUrlLoadIntercept_callback*/: return deserializeAndCallType_WebAttribute_onUrlLoadIntercept_callback(thisArray, thisLength);
        case 541663396/*Kind_VisibleAreaChangeCallback*/: return deserializeAndCallVisibleAreaChangeCallback(thisArray, thisLength);
        case -2038961969/*Kind_VoidCallback*/: return deserializeAndCallVoidCallback(thisArray, thisLength);
        case -1829763354/*Kind_WebKeyboardCallback*/: return deserializeAndCallWebKeyboardCallback(thisArray, thisLength);
        case 219587748/*Kind_WithThemeInterface*/: return deserializeAndCallWithThemeInterface(thisArray, thisLength);
    }
    printf("Unknown callback kind\n");
}
KOALA_EXECUTE(deserializeAndCallCallback, setCallbackCaller(static_cast<Callback_Caller_t>(deserializeAndCallCallback)))
void deserializeAndCallCallbackSync(Ark_VMContext vmContext, Ark_Int32 kind, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    switch (kind) {
        case 589030517/*Kind_AccessibilityCallback*/: return deserializeAndCallSyncAccessibilityCallback(vmContext, thisArray, thisLength);
        case 1289587365/*Kind_AsyncCallback_image_PixelMap_Void*/: return deserializeAndCallSyncAsyncCallback_image_PixelMap_Void(vmContext, thisArray, thisLength);
        case -1964292933/*Kind_ButtonTriggerClickCallback*/: return deserializeAndCallSyncButtonTriggerClickCallback(vmContext, thisArray, thisLength);
        case 197193081/*Kind_Callback_Any_Void*/: return deserializeAndCallSyncCallback_Any_Void(vmContext, thisArray, thisLength);
        case -2024393616/*Kind_Callback_Area_Area_Void*/: return deserializeAndCallSyncCallback_Area_Area_Void(vmContext, thisArray, thisLength);
        case 582384234/*Kind_Callback_Array_Number_Void*/: return deserializeAndCallSyncCallback_Array_Number_Void(vmContext, thisArray, thisLength);
        case -440782244/*Kind_Callback_Array_String_Void*/: return deserializeAndCallSyncCallback_Array_String_Void(vmContext, thisArray, thisLength);
        case -547276916/*Kind_Callback_Array_TouchTestInfo_TouchResult*/: return deserializeAndCallSyncCallback_Array_TouchTestInfo_TouchResult(vmContext, thisArray, thisLength);
        case -1541107680/*Kind_Callback_Boolean*/: return deserializeAndCallSyncCallback_Boolean(vmContext, thisArray, thisLength);
        case -916602978/*Kind_Callback_Boolean_HoverEvent_Void*/: return deserializeAndCallSyncCallback_Boolean_HoverEvent_Void(vmContext, thisArray, thisLength);
        case 313269291/*Kind_Callback_Boolean_Void*/: return deserializeAndCallSyncCallback_Boolean_Void(vmContext, thisArray, thisLength);
        case 1074619005/*Kind_Callback_CalendarRequestedData_Void*/: return deserializeAndCallSyncCallback_CalendarRequestedData_Void(vmContext, thisArray, thisLength);
        case -289198976/*Kind_Callback_CalendarSelectedDate_Void*/: return deserializeAndCallSyncCallback_CalendarSelectedDate_Void(vmContext, thisArray, thisLength);
        case -1189087745/*Kind_Callback_ClickEvent_LocationButtonOnClickResult_Void*/: return deserializeAndCallSyncCallback_ClickEvent_LocationButtonOnClickResult_Void(vmContext, thisArray, thisLength);
        case 659292561/*Kind_Callback_ClickEvent_PasteButtonOnClickResult_Void*/: return deserializeAndCallSyncCallback_ClickEvent_PasteButtonOnClickResult_Void(vmContext, thisArray, thisLength);
        case 846787331/*Kind_Callback_ClickEvent_SaveButtonOnClickResult_Void*/: return deserializeAndCallSyncCallback_ClickEvent_SaveButtonOnClickResult_Void(vmContext, thisArray, thisLength);
        case 1097178637/*Kind_Callback_ClickEvent_Void*/: return deserializeAndCallSyncCallback_ClickEvent_Void(vmContext, thisArray, thisLength);
        case -1270343661/*Kind_Callback_ComputedBarAttribute_Void*/: return deserializeAndCallSyncCallback_ComputedBarAttribute_Void(vmContext, thisArray, thisLength);
        case -120437466/*Kind_Callback_CopyEvent_Void*/: return deserializeAndCallSyncCallback_CopyEvent_Void(vmContext, thisArray, thisLength);
        case -721106019/*Kind_Callback_CustomBuilder_Void*/: return deserializeAndCallSyncCallback_CustomBuilder_Void(vmContext, thisArray, thisLength);
        case -1875695871/*Kind_Callback_CutEvent_Void*/: return deserializeAndCallSyncCallback_CutEvent_Void(vmContext, thisArray, thisLength);
        case 1405382363/*Kind_Callback_Date_Void*/: return deserializeAndCallSyncCallback_Date_Void(vmContext, thisArray, thisLength);
        case 1280920532/*Kind_Callback_DatePickerResult_Void*/: return deserializeAndCallSyncCallback_DatePickerResult_Void(vmContext, thisArray, thisLength);
        case -1357792883/*Kind_Callback_DeleteValue_Boolean*/: return deserializeAndCallSyncCallback_DeleteValue_Boolean(vmContext, thisArray, thisLength);
        case -126251459/*Kind_Callback_DeleteValue_Void*/: return deserializeAndCallSyncCallback_DeleteValue_Void(vmContext, thisArray, thisLength);
        case -1283506641/*Kind_Callback_DismissContentCoverAction_Void*/: return deserializeAndCallSyncCallback_DismissContentCoverAction_Void(vmContext, thisArray, thisLength);
        case -2095828093/*Kind_Callback_DismissDialogAction_Void*/: return deserializeAndCallSyncCallback_DismissDialogAction_Void(vmContext, thisArray, thisLength);
        case -2004166751/*Kind_Callback_DismissPopupAction_Void*/: return deserializeAndCallSyncCallback_DismissPopupAction_Void(vmContext, thisArray, thisLength);
        case 889549796/*Kind_Callback_DismissSheetAction_Void*/: return deserializeAndCallSyncCallback_DismissSheetAction_Void(vmContext, thisArray, thisLength);
        case 480978023/*Kind_Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo*/: return deserializeAndCallSyncCallback_DragEvent_String_Union_CustomBuilder_DragItemInfo(vmContext, thisArray, thisLength);
        case -17167687/*Kind_Callback_DragEvent_String_Void*/: return deserializeAndCallSyncCallback_DragEvent_String_Void(vmContext, thisArray, thisLength);
        case -1802605016/*Kind_Callback_EnterKeyType_Void*/: return deserializeAndCallSyncCallback_EnterKeyType_Void(vmContext, thisArray, thisLength);
        case -733525640/*Kind_Callback_Extender_OnFinish*/: return deserializeAndCallSyncCallback_Extender_OnFinish(vmContext, thisArray, thisLength);
        case 1264236374/*Kind_Callback_Extender_OnProgress*/: return deserializeAndCallSyncCallback_Extender_OnProgress(vmContext, thisArray, thisLength);
        case 758395742/*Kind_Callback_FormCallbackInfo_Void*/: return deserializeAndCallSyncCallback_FormCallbackInfo_Void(vmContext, thisArray, thisLength);
        case 583294398/*Kind_Callback_FullscreenInfo_Void*/: return deserializeAndCallSyncCallback_FullscreenInfo_Void(vmContext, thisArray, thisLength);
        case -1143194492/*Kind_Callback_GestureEvent_Void*/: return deserializeAndCallSyncCallback_GestureEvent_Void(vmContext, thisArray, thisLength);
        case 1319043556/*Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult*/: return deserializeAndCallSyncCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(vmContext, thisArray, thisLength);
        case -684588584/*Kind_Callback_GestureJudgeResult_Void*/: return deserializeAndCallSyncCallback_GestureJudgeResult_Void(vmContext, thisArray, thisLength);
        case 776202910/*Kind_Callback_GestureRecognizer_Void*/: return deserializeAndCallSyncCallback_GestureRecognizer_Void(vmContext, thisArray, thisLength);
        case -1755111025/*Kind_Callback_HitTestMode_Void*/: return deserializeAndCallSyncCallback_HitTestMode_Void(vmContext, thisArray, thisLength);
        case -383025085/*Kind_Callback_InsertValue_Boolean*/: return deserializeAndCallSyncCallback_InsertValue_Boolean(vmContext, thisArray, thisLength);
        case -1121207885/*Kind_Callback_InsertValue_Void*/: return deserializeAndCallSyncCallback_InsertValue_Void(vmContext, thisArray, thisLength);
        case 719029905/*Kind_Callback_IsolatedComponentAttribute_Void*/: return deserializeAndCallSyncCallback_IsolatedComponentAttribute_Void(vmContext, thisArray, thisLength);
        case -1627362945/*Kind_Callback_ItemDragInfo_Number_Number_Boolean_Void*/: return deserializeAndCallSyncCallback_ItemDragInfo_Number_Number_Boolean_Void(vmContext, thisArray, thisLength);
        case -918805852/*Kind_Callback_ItemDragInfo_Number_Number_Void*/: return deserializeAndCallSyncCallback_ItemDragInfo_Number_Number_Void(vmContext, thisArray, thisLength);
        case 296908152/*Kind_Callback_ItemDragInfo_Number_Void*/: return deserializeAndCallSyncCallback_ItemDragInfo_Number_Void(vmContext, thisArray, thisLength);
        case 137353252/*Kind_Callback_ItemDragInfo_Void*/: return deserializeAndCallSyncCallback_ItemDragInfo_Void(vmContext, thisArray, thisLength);
        case -2061548092/*Kind_Callback_KeyEvent_Boolean*/: return deserializeAndCallSyncCallback_KeyEvent_Boolean(vmContext, thisArray, thisLength);
        case 707696468/*Kind_Callback_KeyEvent_Void*/: return deserializeAndCallSyncCallback_KeyEvent_Void(vmContext, thisArray, thisLength);
        case -1561407084/*Kind_Callback_Literal_Boolean_isVisible_Void*/: return deserializeAndCallSyncCallback_Literal_Boolean_isVisible_Void(vmContext, thisArray, thisLength);
        case 361012115/*Kind_Callback_Literal_Function_handler_Object_error_Void*/: return deserializeAndCallSyncCallback_Literal_Function_handler_Object_error_Void(vmContext, thisArray, thisLength);
        case -582934742/*Kind_Callback_Literal_Number_code_Want_want_Void*/: return deserializeAndCallSyncCallback_Literal_Number_code_Want_want_Void(vmContext, thisArray, thisLength);
        case 1321277443/*Kind_Callback_Literal_Number_errcode_String_msg_Void*/: return deserializeAndCallSyncCallback_Literal_Number_errcode_String_msg_Void(vmContext, thisArray, thisLength);
        case -251706058/*Kind_Callback_Literal_Number_offsetRemain_Void*/: return deserializeAndCallSyncCallback_Literal_Number_offsetRemain_Void(vmContext, thisArray, thisLength);
        case 222742448/*Kind_Callback_Literal_Object_detail_Boolean*/: return deserializeAndCallSyncCallback_Literal_Object_detail_Boolean(vmContext, thisArray, thisLength);
        case -122223466/*Kind_Callback_Literal_String_plainText_Void*/: return deserializeAndCallSyncCallback_Literal_String_plainText_Void(vmContext, thisArray, thisLength);
        case -1382640094/*Kind_Callback_MouseEvent_Void*/: return deserializeAndCallSyncCallback_MouseEvent_Void(vmContext, thisArray, thisLength);
        case 477481563/*Kind_Callback_NativeEmbedDataInfo_Void*/: return deserializeAndCallSyncCallback_NativeEmbedDataInfo_Void(vmContext, thisArray, thisLength);
        case -1090303858/*Kind_Callback_NativeEmbedTouchInfo_Void*/: return deserializeAndCallSyncCallback_NativeEmbedTouchInfo_Void(vmContext, thisArray, thisLength);
        case -1642725259/*Kind_Callback_NavDestinationContext_Void*/: return deserializeAndCallSyncCallback_NavDestinationContext_Void(vmContext, thisArray, thisLength);
        case 960690982/*Kind_Callback_NavigationMode_Void*/: return deserializeAndCallSyncCallback_NavigationMode_Void(vmContext, thisArray, thisLength);
        case 1685437830/*Kind_Callback_NavigationTitleMode_Void*/: return deserializeAndCallSyncCallback_NavigationTitleMode_Void(vmContext, thisArray, thisLength);
        case -1375731066/*Kind_Callback_NavigationTransitionProxy_Void*/: return deserializeAndCallSyncCallback_NavigationTransitionProxy_Void(vmContext, thisArray, thisLength);
        case 1054099324/*Kind_Callback_Number_Boolean*/: return deserializeAndCallSyncCallback_Number_Boolean(vmContext, thisArray, thisLength);
        case -1427334496/*Kind_Callback_Number_Number_Boolean*/: return deserializeAndCallSyncCallback_Number_Number_Boolean(vmContext, thisArray, thisLength);
        case -3987624/*Kind_Callback_Number_Number_ComputedBarAttribute*/: return deserializeAndCallSyncCallback_Number_Number_ComputedBarAttribute(vmContext, thisArray, thisLength);
        case -352942292/*Kind_Callback_Number_Number_Number_Void*/: return deserializeAndCallSyncCallback_Number_Number_Number_Void(vmContext, thisArray, thisLength);
        case 1613628570/*Kind_Callback_Number_Number_PanelMode_Void*/: return deserializeAndCallSyncCallback_Number_Number_PanelMode_Void(vmContext, thisArray, thisLength);
        case 1894574320/*Kind_Callback_Number_Number_Void*/: return deserializeAndCallSyncCallback_Number_Number_Void(vmContext, thisArray, thisLength);
        case 2012829508/*Kind_Callback_Number_ScrollState_Literal_Number_offsetRemain*/: return deserializeAndCallSyncCallback_Number_ScrollState_Literal_Number_offsetRemain(vmContext, thisArray, thisLength);
        case 88697971/*Kind_Callback_Number_SliderChangeMode_Void*/: return deserializeAndCallSyncCallback_Number_SliderChangeMode_Void(vmContext, thisArray, thisLength);
        case 794065478/*Kind_Callback_Number_String_Void*/: return deserializeAndCallSyncCallback_Number_String_Void(vmContext, thisArray, thisLength);
        case 1602877440/*Kind_Callback_Number_Tuple_Number_Number*/: return deserializeAndCallSyncCallback_Number_Tuple_Number_Number(vmContext, thisArray, thisLength);
        case 1618565120/*Kind_Callback_Number_Tuple_Number_Number_Number_Number*/: return deserializeAndCallSyncCallback_Number_Tuple_Number_Number_Number_Number(vmContext, thisArray, thisLength);
        case 36519084/*Kind_Callback_Number_Void*/: return deserializeAndCallSyncCallback_Number_Void(vmContext, thisArray, thisLength);
        case 1295952075/*Kind_Callback_OffsetResult_Void*/: return deserializeAndCallSyncCallback_OffsetResult_Void(vmContext, thisArray, thisLength);
        case 1385252075/*Kind_Callback_ScrollResult_Void*/: return deserializeAndCallSyncCallback_ScrollResult_Void(vmContext, thisArray, thisLength);
        case 806070428/*Kind_Callback_OnAlertEvent_Boolean*/: return deserializeAndCallSyncCallback_OnAlertEvent_Boolean(vmContext, thisArray, thisLength);
        case -1559789631/*Kind_Callback_OnAudioStateChangedEvent_Void*/: return deserializeAndCallSyncCallback_OnAudioStateChangedEvent_Void(vmContext, thisArray, thisLength);
        case -873162122/*Kind_Callback_OnBeforeUnloadEvent_Boolean*/: return deserializeAndCallSyncCallback_OnBeforeUnloadEvent_Boolean(vmContext, thisArray, thisLength);
        case 608991355/*Kind_Callback_OnClientAuthenticationEvent_Void*/: return deserializeAndCallSyncCallback_OnClientAuthenticationEvent_Void(vmContext, thisArray, thisLength);
        case 317864672/*Kind_Callback_OnConfirmEvent_Boolean*/: return deserializeAndCallSyncCallback_OnConfirmEvent_Boolean(vmContext, thisArray, thisLength);
        case 893367077/*Kind_Callback_OnConsoleEvent_Boolean*/: return deserializeAndCallSyncCallback_OnConsoleEvent_Boolean(vmContext, thisArray, thisLength);
        case 332449533/*Kind_Callback_OnContextMenuShowEvent_Boolean*/: return deserializeAndCallSyncCallback_OnContextMenuShowEvent_Boolean(vmContext, thisArray, thisLength);
        case 118631204/*Kind_Callback_OnDataResubmittedEvent_Void*/: return deserializeAndCallSyncCallback_OnDataResubmittedEvent_Void(vmContext, thisArray, thisLength);
        case 1834611702/*Kind_Callback_OnDownloadStartEvent_Void*/: return deserializeAndCallSyncCallback_OnDownloadStartEvent_Void(vmContext, thisArray, thisLength);
        case -1792851375/*Kind_Callback_OnErrorReceiveEvent_Void*/: return deserializeAndCallSyncCallback_OnErrorReceiveEvent_Void(vmContext, thisArray, thisLength);
        case -243916553/*Kind_Callback_OnFaviconReceivedEvent_Void*/: return deserializeAndCallSyncCallback_OnFaviconReceivedEvent_Void(vmContext, thisArray, thisLength);
        case -1852060212/*Kind_Callback_OnFirstContentfulPaintEvent_Void*/: return deserializeAndCallSyncCallback_OnFirstContentfulPaintEvent_Void(vmContext, thisArray, thisLength);
        case -941896815/*Kind_Callback_OnGeolocationShowEvent_Void*/: return deserializeAndCallSyncCallback_OnGeolocationShowEvent_Void(vmContext, thisArray, thisLength);
        case 780282803/*Kind_Callback_OnHttpAuthRequestEvent_Boolean*/: return deserializeAndCallSyncCallback_OnHttpAuthRequestEvent_Boolean(vmContext, thisArray, thisLength);
        case -2066745559/*Kind_Callback_OnHttpErrorReceiveEvent_Void*/: return deserializeAndCallSyncCallback_OnHttpErrorReceiveEvent_Void(vmContext, thisArray, thisLength);
        case 1442698200/*Kind_Callback_OnInterceptRequestEvent_WebResourceResponse*/: return deserializeAndCallSyncCallback_OnInterceptRequestEvent_WebResourceResponse(vmContext, thisArray, thisLength);
        case 1231444306/*Kind_Callback_OnLoadInterceptEvent_Boolean*/: return deserializeAndCallSyncCallback_OnLoadInterceptEvent_Boolean(vmContext, thisArray, thisLength);
        case -860386431/*Kind_Callback_OnOverScrollEvent_Void*/: return deserializeAndCallSyncCallback_OnOverScrollEvent_Void(vmContext, thisArray, thisLength);
        case -2040193994/*Kind_Callback_OnPageBeginEvent_Void*/: return deserializeAndCallSyncCallback_OnPageBeginEvent_Void(vmContext, thisArray, thisLength);
        case -130135362/*Kind_Callback_OnPageEndEvent_Void*/: return deserializeAndCallSyncCallback_OnPageEndEvent_Void(vmContext, thisArray, thisLength);
        case 1805946367/*Kind_Callback_OnPageVisibleEvent_Void*/: return deserializeAndCallSyncCallback_OnPageVisibleEvent_Void(vmContext, thisArray, thisLength);
        case 529980696/*Kind_Callback_OnPermissionRequestEvent_Void*/: return deserializeAndCallSyncCallback_OnPermissionRequestEvent_Void(vmContext, thisArray, thisLength);
        case 1018740377/*Kind_Callback_OnProgressChangeEvent_Void*/: return deserializeAndCallSyncCallback_OnProgressChangeEvent_Void(vmContext, thisArray, thisLength);
        case -1826742986/*Kind_Callback_OnPromptEvent_Boolean*/: return deserializeAndCallSyncCallback_OnPromptEvent_Boolean(vmContext, thisArray, thisLength);
        case 1978364344/*Kind_Callback_OnRefreshAccessedHistoryEvent_Void*/: return deserializeAndCallSyncCallback_OnRefreshAccessedHistoryEvent_Void(vmContext, thisArray, thisLength);
        case -1413785559/*Kind_Callback_OnRenderExitedEvent_Void*/: return deserializeAndCallSyncCallback_OnRenderExitedEvent_Void(vmContext, thisArray, thisLength);
        case 793995118/*Kind_Callback_OnResourceLoadEvent_Void*/: return deserializeAndCallSyncCallback_OnResourceLoadEvent_Void(vmContext, thisArray, thisLength);
        case -1782102148/*Kind_Callback_OnScaleChangeEvent_Void*/: return deserializeAndCallSyncCallback_OnScaleChangeEvent_Void(vmContext, thisArray, thisLength);
        case -1972321573/*Kind_Callback_OnScreenCaptureRequestEvent_Void*/: return deserializeAndCallSyncCallback_OnScreenCaptureRequestEvent_Void(vmContext, thisArray, thisLength);
        case -172908881/*Kind_Callback_OnScrollEvent_Void*/: return deserializeAndCallSyncCallback_OnScrollEvent_Void(vmContext, thisArray, thisLength);
        case 1637092936/*Kind_Callback_OnScrollFrameBeginHandlerResult_Void*/: return deserializeAndCallSyncCallback_OnScrollFrameBeginHandlerResult_Void(vmContext, thisArray, thisLength);
        case -1495570/*Kind_Callback_OnSearchResultReceiveEvent_Void*/: return deserializeAndCallSyncCallback_OnSearchResultReceiveEvent_Void(vmContext, thisArray, thisLength);
        case -636069598/*Kind_Callback_OnShowFileSelectorEvent_Boolean*/: return deserializeAndCallSyncCallback_OnShowFileSelectorEvent_Boolean(vmContext, thisArray, thisLength);
        case 1624791665/*Kind_Callback_OnSslErrorEventReceiveEvent_Void*/: return deserializeAndCallSyncCallback_OnSslErrorEventReceiveEvent_Void(vmContext, thisArray, thisLength);
        case -318085495/*Kind_Callback_OnTitleReceiveEvent_Void*/: return deserializeAndCallSyncCallback_OnTitleReceiveEvent_Void(vmContext, thisArray, thisLength);
        case 1657893064/*Kind_Callback_OnTouchIconUrlReceivedEvent_Void*/: return deserializeAndCallSyncCallback_OnTouchIconUrlReceivedEvent_Void(vmContext, thisArray, thisLength);
        case -2052382574/*Kind_Callback_OnWindowNewEvent_Void*/: return deserializeAndCallSyncCallback_OnWindowNewEvent_Void(vmContext, thisArray, thisLength);
        case -543655128/*Kind_Callback_Opt_Array_String_Void*/: return deserializeAndCallSyncCallback_Opt_Array_String_Void(vmContext, thisArray, thisLength);
        case -2035339519/*Kind_Callback_Opt_NavigationAnimatedTransition_Void*/: return deserializeAndCallSyncCallback_Opt_NavigationAnimatedTransition_Void(vmContext, thisArray, thisLength);
        case -756319131/*Kind_Callback_Opt_StyledString_Opt_Array_String_Void*/: return deserializeAndCallSyncCallback_Opt_StyledString_Opt_Array_String_Void(vmContext, thisArray, thisLength);
        case -143931627/*Kind_Callback_Opt_TabContentAnimatedTransition_Void*/: return deserializeAndCallSyncCallback_Opt_TabContentAnimatedTransition_Void(vmContext, thisArray, thisLength);
        case 388680218/*Kind_Callback_PanelMode_Void*/: return deserializeAndCallSyncCallback_PanelMode_Void(vmContext, thisArray, thisLength);
        case -2058966418/*Kind_Callback_PlaybackInfo_Void*/: return deserializeAndCallSyncCallback_PlaybackInfo_Void(vmContext, thisArray, thisLength);
        case 721562324/*Kind_Callback_Pointer_Void*/: return deserializeAndCallSyncCallback_Pointer_Void(vmContext, thisArray, thisLength);
        case 624053870/*Kind_Callback_PopInfo_Void*/: return deserializeAndCallSyncCallback_PopInfo_Void(vmContext, thisArray, thisLength);
        case 463894668/*Kind_Callback_PreDragStatus_Void*/: return deserializeAndCallSyncCallback_PreDragStatus_Void(vmContext, thisArray, thisLength);
        case 1300890372/*Kind_Callback_PreparedInfo_Void*/: return deserializeAndCallSyncCallback_PreparedInfo_Void(vmContext, thisArray, thisLength);
        case 797834474/*Kind_Callback_RangeUpdate*/: return deserializeAndCallSyncCallback_RangeUpdate(vmContext, thisArray, thisLength);
        case 934309126/*Kind_Callback_RefreshStatus_Void*/: return deserializeAndCallSyncCallback_RefreshStatus_Void(vmContext, thisArray, thisLength);
        case 188373904/*Kind_Callback_ResourceStr_Void*/: return deserializeAndCallSyncCallback_ResourceStr_Void(vmContext, thisArray, thisLength);
        case 1465860515/*Kind_Callback_RichEditorChangeValue_Boolean*/: return deserializeAndCallSyncCallback_RichEditorChangeValue_Boolean(vmContext, thisArray, thisLength);
        case 667698748/*Kind_Callback_RichEditorDeleteValue_Boolean*/: return deserializeAndCallSyncCallback_RichEditorDeleteValue_Boolean(vmContext, thisArray, thisLength);
        case -319221262/*Kind_Callback_RichEditorInsertValue_Boolean*/: return deserializeAndCallSyncCallback_RichEditorInsertValue_Boolean(vmContext, thisArray, thisLength);
        case -62253375/*Kind_Callback_RichEditorRange_Void*/: return deserializeAndCallSyncCallback_RichEditorRange_Void(vmContext, thisArray, thisLength);
        case -963852514/*Kind_Callback_RichEditorSelection_Void*/: return deserializeAndCallSyncCallback_RichEditorSelection_Void(vmContext, thisArray, thisLength);
        case 1980824326/*Kind_Callback_RichEditorTextSpanResult_Void*/: return deserializeAndCallSyncCallback_RichEditorTextSpanResult_Void(vmContext, thisArray, thisLength);
        case 22609082/*Kind_Callback_SheetDismiss_Void*/: return deserializeAndCallSyncCallback_SheetDismiss_Void(vmContext, thisArray, thisLength);
        case -224451112/*Kind_Callback_SheetType_Void*/: return deserializeAndCallSyncCallback_SheetType_Void(vmContext, thisArray, thisLength);
        case 1536231691/*Kind_Callback_SpringBackAction_Void*/: return deserializeAndCallSyncCallback_SpringBackAction_Void(vmContext, thisArray, thisLength);
        case -879490874/*Kind_Callback_String_Number_Void*/: return deserializeAndCallSyncCallback_String_Number_Void(vmContext, thisArray, thisLength);
        case -683652998/*Kind_Callback_String_PasteEvent_Void*/: return deserializeAndCallSyncCallback_String_PasteEvent_Void(vmContext, thisArray, thisLength);
        case -1493806035/*Kind_Callback_String_Unknown_Void*/: return deserializeAndCallSyncCallback_String_Unknown_Void(vmContext, thisArray, thisLength);
        case 814634522/*Kind_Callback_String_Void*/: return deserializeAndCallSyncCallback_String_Void(vmContext, thisArray, thisLength);
        case 2116745428/*Kind_Callback_StyledStringChangeValue_Boolean*/: return deserializeAndCallSyncCallback_StyledStringChangeValue_Boolean(vmContext, thisArray, thisLength);
        case -301561698/*Kind_Callback_SwipeActionState_Void*/: return deserializeAndCallSyncCallback_SwipeActionState_Void(vmContext, thisArray, thisLength);
        case -416053361/*Kind_Callback_SwiperContentTransitionProxy_Void*/: return deserializeAndCallSyncCallback_SwiperContentTransitionProxy_Void(vmContext, thisArray, thisLength);
        case -1223938478/*Kind_Callback_TabContentTransitionProxy_Void*/: return deserializeAndCallSyncCallback_TabContentTransitionProxy_Void(vmContext, thisArray, thisLength);
        case 691098197/*Kind_Callback_TerminationInfo_Void*/: return deserializeAndCallSyncCallback_TerminationInfo_Void(vmContext, thisArray, thisLength);
        case 1290504509/*Kind_Callback_TextPickerResult_Void*/: return deserializeAndCallSyncCallback_TextPickerResult_Void(vmContext, thisArray, thisLength);
        case 811915501/*Kind_Callback_TextRange_Void*/: return deserializeAndCallSyncCallback_TextRange_Void(vmContext, thisArray, thisLength);
        case 1557859605/*Kind_Callback_TimePickerResult_Void*/: return deserializeAndCallSyncCallback_TimePickerResult_Void(vmContext, thisArray, thisLength);
        case -274419246/*Kind_Callback_TouchEvent_HitTestMode*/: return deserializeAndCallSyncCallback_TouchEvent_HitTestMode(vmContext, thisArray, thisLength);
        case -1676021850/*Kind_Callback_TouchEvent_Void*/: return deserializeAndCallSyncCallback_TouchEvent_Void(vmContext, thisArray, thisLength);
        case 1943507619/*Kind_Callback_TouchResult_Void*/: return deserializeAndCallSyncCallback_TouchResult_Void(vmContext, thisArray, thisLength);
        case 148489367/*Kind_Callback_Tuple_Number_Number_Number_Number_Void*/: return deserializeAndCallSyncCallback_Tuple_Number_Number_Number_Number_Void(vmContext, thisArray, thisLength);
        case -607365481/*Kind_Callback_Tuple_Number_Number_Void*/: return deserializeAndCallSyncCallback_Tuple_Number_Number_Void(vmContext, thisArray, thisLength);
        case -1352745727/*Kind_Callback_Type_ImageAttribute_onComplete_callback_event_Void*/: return deserializeAndCallSyncCallback_Type_ImageAttribute_onComplete_callback_event_Void(vmContext, thisArray, thisLength);
        case -1063506522/*Kind_Callback_UIExtensionProxy_Void*/: return deserializeAndCallSyncCallback_UIExtensionProxy_Void(vmContext, thisArray, thisLength);
        case -620935067/*Kind_Callback_Union_CustomBuilder_DragItemInfo_Void*/: return deserializeAndCallSyncCallback_Union_CustomBuilder_DragItemInfo_Void(vmContext, thisArray, thisLength);
        case -1111620998/*Kind_Callback_Union_Number_Array_Number_Void*/: return deserializeAndCallSyncCallback_Union_Number_Array_Number_Void(vmContext, thisArray, thisLength);
        case -956455499/*Kind_Callback_Union_Number_Resource_Void*/: return deserializeAndCallSyncCallback_Union_Number_Resource_Void(vmContext, thisArray, thisLength);
        case -720435526/*Kind_Callback_Union_String_Array_String_Void*/: return deserializeAndCallSyncCallback_Union_String_Array_String_Void(vmContext, thisArray, thisLength);
        case -1867723152/*Kind_Callback_Void*/: return deserializeAndCallSyncCallback_Void(vmContext, thisArray, thisLength);
        case -1376223390/*Kind_Callback_WebKeyboardOptions_Void*/: return deserializeAndCallSyncCallback_WebKeyboardOptions_Void(vmContext, thisArray, thisLength);
        case 831645046/*Kind_Callback_WebResourceResponse_Void*/: return deserializeAndCallSyncCallback_WebResourceResponse_Void(vmContext, thisArray, thisLength);
        case 1436479104/*Kind_Callback_WithThemeAttribute_Void*/: return deserializeAndCallSyncCallback_WithThemeAttribute_Void(vmContext, thisArray, thisLength);
        case 1532328438/*Kind_ContentDidScrollCallback*/: return deserializeAndCallSyncContentDidScrollCallback(vmContext, thisArray, thisLength);
        case 1766817632/*Kind_CustomNodeBuilder*/: return deserializeAndCallSyncCustomNodeBuilder(vmContext, thisArray, thisLength);
        case -1729563209/*Kind_EditableTextOnChangeCallback*/: return deserializeAndCallSyncEditableTextOnChangeCallback(vmContext, thisArray, thisLength);
        case -1936519453/*Kind_ErrorCallback*/: return deserializeAndCallSyncErrorCallback(vmContext, thisArray, thisLength);
        case -2119548940/*Kind_GestureRecognizerJudgeBeginCallback*/: return deserializeAndCallSyncGestureRecognizerJudgeBeginCallback(vmContext, thisArray, thisLength);
        case -2076995110/*Kind_GetItemMainSizeByIndex*/: return deserializeAndCallSyncGetItemMainSizeByIndex(vmContext, thisArray, thisLength);
        case 68560477/*Kind_HoverCallback*/: return deserializeAndCallSyncHoverCallback(vmContext, thisArray, thisLength);
        case -1180567691/*Kind_ImageCompleteCallback*/: return deserializeAndCallSyncImageCompleteCallback(vmContext, thisArray, thisLength);
        case 1906248580/*Kind_ImageErrorCallback*/: return deserializeAndCallSyncImageErrorCallback(vmContext, thisArray, thisLength);
        case 1502213270/*Kind_InterceptionModeCallback*/: return deserializeAndCallSyncInterceptionModeCallback(vmContext, thisArray, thisLength);
        case 1852781814/*Kind_InterceptionShowCallback*/: return deserializeAndCallSyncInterceptionShowCallback(vmContext, thisArray, thisLength);
        case 2139680213/*Kind_IsolatedComponentInterface*/: return deserializeAndCallSyncIsolatedComponentInterface(vmContext, thisArray, thisLength);
        case -614475458/*Kind_MenuOnAppearCallback*/: return deserializeAndCallSyncMenuOnAppearCallback(vmContext, thisArray, thisLength);
        case -588228933/*Kind_NavExtender_OnUpdateStack*/: return deserializeAndCallSyncNavExtender_OnUpdateStack(vmContext, thisArray, thisLength);
        case 1572284740/*Kind_OnAdsBlockedCallback*/: return deserializeAndCallSyncOnAdsBlockedCallback(vmContext, thisArray, thisLength);
        case 726938390/*Kind_OnAlphabetIndexerPopupSelectCallback*/: return deserializeAndCallSyncOnAlphabetIndexerPopupSelectCallback(vmContext, thisArray, thisLength);
        case -1956514817/*Kind_OnAlphabetIndexerRequestPopupDataCallback*/: return deserializeAndCallSyncOnAlphabetIndexerRequestPopupDataCallback(vmContext, thisArray, thisLength);
        case -1189721220/*Kind_OnAlphabetIndexerSelectCallback*/: return deserializeAndCallSyncOnAlphabetIndexerSelectCallback(vmContext, thisArray, thisLength);
        case -1198592337/*Kind_OnCheckboxChangeCallback*/: return deserializeAndCallSyncOnCheckboxChangeCallback(vmContext, thisArray, thisLength);
        case -1053064240/*Kind_OnCheckboxGroupChangeCallback*/: return deserializeAndCallSyncOnCheckboxGroupChangeCallback(vmContext, thisArray, thisLength);
        case -419979106/*Kind_OnContentScrollCallback*/: return deserializeAndCallSyncOnContentScrollCallback(vmContext, thisArray, thisLength);
        case 1788572278/*Kind_OnContextMenuHideCallback*/: return deserializeAndCallSyncOnContextMenuHideCallback(vmContext, thisArray, thisLength);
        case 1648184341/*Kind_OnDidChangeCallback*/: return deserializeAndCallSyncOnDidChangeCallback(vmContext, thisArray, thisLength);
        case 767275770/*Kind_OnFirstMeaningfulPaintCallback*/: return deserializeAndCallSyncOnFirstMeaningfulPaintCallback(vmContext, thisArray, thisLength);
        case 2050387049/*Kind_OnFoldStatusChangeCallback*/: return deserializeAndCallSyncOnFoldStatusChangeCallback(vmContext, thisArray, thisLength);
        case 81230317/*Kind_OnFullScreenEnterCallback*/: return deserializeAndCallSyncOnFullScreenEnterCallback(vmContext, thisArray, thisLength);
        case 9040430/*Kind_OnHoverStatusChangeCallback*/: return deserializeAndCallSyncOnHoverStatusChangeCallback(vmContext, thisArray, thisLength);
        case -1377876844/*Kind_OnIntelligentTrackingPreventionCallback*/: return deserializeAndCallSyncOnIntelligentTrackingPreventionCallback(vmContext, thisArray, thisLength);
        case 1340995650/*Kind_onItemDragStart_event_type*/: return deserializeAndCallSynconItemDragStart_event_type(vmContext, thisArray, thisLength);
        case 1390640532/*Kind_OnLargestContentfulPaintCallback*/: return deserializeAndCallSyncOnLargestContentfulPaintCallback(vmContext, thisArray, thisLength);
        case -968773856/*Kind_OnLinearIndicatorChangeCallback*/: return deserializeAndCallSyncOnLinearIndicatorChangeCallback(vmContext, thisArray, thisLength);
        case -1200281222/*Kind_OnMoveHandler*/: return deserializeAndCallSyncOnMoveHandler(vmContext, thisArray, thisLength);
        case -1641338704/*Kind_OnNativeEmbedVisibilityChangeCallback*/: return deserializeAndCallSyncOnNativeEmbedVisibilityChangeCallback(vmContext, thisArray, thisLength);
        case -823037763/*Kind_OnNativeLoadCallback*/: return deserializeAndCallSyncOnNativeLoadCallback(vmContext, thisArray, thisLength);
        case -398722176/*Kind_OnNavigationEntryCommittedCallback*/: return deserializeAndCallSyncOnNavigationEntryCommittedCallback(vmContext, thisArray, thisLength);
        case 865258467/*Kind_OnOverrideUrlLoadingCallback*/: return deserializeAndCallSyncOnOverrideUrlLoadingCallback(vmContext, thisArray, thisLength);
        case 1738363337/*Kind_OnPasteCallback*/: return deserializeAndCallSyncOnPasteCallback(vmContext, thisArray, thisLength);
        case 47282303/*Kind_OnRenderProcessNotRespondingCallback*/: return deserializeAndCallSyncOnRenderProcessNotRespondingCallback(vmContext, thisArray, thisLength);
        case 1334389194/*Kind_OnRenderProcessRespondingCallback*/: return deserializeAndCallSyncOnRenderProcessRespondingCallback(vmContext, thisArray, thisLength);
        case -1099824577/*Kind_OnSafeBrowsingCheckResultCallback*/: return deserializeAndCallSyncOnSafeBrowsingCheckResultCallback(vmContext, thisArray, thisLength);
        case -160015401/*Kind_OnScrollCallback*/: return deserializeAndCallSyncOnScrollCallback(vmContext, thisArray, thisLength);
        case -150015401/*Kind_OnWillScrollCallback*/: return deserializeAndCallSyncOnWillScrollCallback(vmContext, thisArray, thisLength);
        case -1259214476/*Kind_OnScrollEdgeCallback*/: return deserializeAndCallSyncOnScrollEdgeCallback(vmContext, thisArray, thisLength);
        case -2133791987/*Kind_OnScrollFrameBeginCallback*/: return deserializeAndCallSyncOnScrollFrameBeginCallback(vmContext, thisArray, thisLength);
        case 625641334/*Kind_OnScrollVisibleContentChangeCallback*/: return deserializeAndCallSyncOnScrollVisibleContentChangeCallback(vmContext, thisArray, thisLength);
        case -399603614/*Kind_OnSslErrorEventCallback*/: return deserializeAndCallSyncOnSslErrorEventCallback(vmContext, thisArray, thisLength);
        case -1961646162/*Kind_OnSubmitCallback*/: return deserializeAndCallSyncOnSubmitCallback(vmContext, thisArray, thisLength);
        case -143686583/*Kind_OnSwiperAnimationEndCallback*/: return deserializeAndCallSyncOnSwiperAnimationEndCallback(vmContext, thisArray, thisLength);
        case 876602502/*Kind_OnSwiperAnimationStartCallback*/: return deserializeAndCallSyncOnSwiperAnimationStartCallback(vmContext, thisArray, thisLength);
        case 606029871/*Kind_OnSwiperGestureSwipeCallback*/: return deserializeAndCallSyncOnSwiperGestureSwipeCallback(vmContext, thisArray, thisLength);
        case 1942856551/*Kind_OnTabsAnimationEndCallback*/: return deserializeAndCallSyncOnTabsAnimationEndCallback(vmContext, thisArray, thisLength);
        case -147408344/*Kind_OnTabsAnimationStartCallback*/: return deserializeAndCallSyncOnTabsAnimationStartCallback(vmContext, thisArray, thisLength);
        case -349727249/*Kind_OnTabsContentWillChangeCallback*/: return deserializeAndCallSyncOnTabsContentWillChangeCallback(vmContext, thisArray, thisLength);
        case 253696833/*Kind_OnTabsGestureSwipeCallback*/: return deserializeAndCallSyncOnTabsGestureSwipeCallback(vmContext, thisArray, thisLength);
        case 695228737/*Kind_OnTextSelectionChangeCallback*/: return deserializeAndCallSyncOnTextSelectionChangeCallback(vmContext, thisArray, thisLength);
        case 1847083191/*Kind_OnViewportFitChangedCallback*/: return deserializeAndCallSyncOnViewportFitChangedCallback(vmContext, thisArray, thisLength);
        case 1627123591/*Kind_PageTransitionCallback*/: return deserializeAndCallSyncPageTransitionCallback(vmContext, thisArray, thisLength);
        case 919057028/*Kind_PasteEventCallback*/: return deserializeAndCallSyncPasteEventCallback(vmContext, thisArray, thisLength);
        case -1992671958/*Kind_PluginErrorCallback*/: return deserializeAndCallSyncPluginErrorCallback(vmContext, thisArray, thisLength);
        case -1265626662/*Kind_ScrollOnScrollCallback*/: return deserializeAndCallSyncScrollOnScrollCallback(vmContext, thisArray, thisLength);
        case -721521596/*Kind_ScrollOnWillScrollCallback*/: return deserializeAndCallSyncScrollOnWillScrollCallback(vmContext, thisArray, thisLength);
        case 1717691617/*Kind_SearchSubmitCallback*/: return deserializeAndCallSyncSearchSubmitCallback(vmContext, thisArray, thisLength);
        case -250780276/*Kind_ShouldBuiltInRecognizerParallelWithCallback*/: return deserializeAndCallSyncShouldBuiltInRecognizerParallelWithCallback(vmContext, thisArray, thisLength);
        case -1716637992/*Kind_SizeChangeCallback*/: return deserializeAndCallSyncSizeChangeCallback(vmContext, thisArray, thisLength);
        case 711649376/*Kind_SliderTriggerChangeCallback*/: return deserializeAndCallSyncSliderTriggerChangeCallback(vmContext, thisArray, thisLength);
        case -712186065/*Kind_SubmitCallback*/: return deserializeAndCallSyncSubmitCallback(vmContext, thisArray, thisLength);
        case 221706282/*Kind_TabsCustomContentTransitionCallback*/: return deserializeAndCallSyncTabsCustomContentTransitionCallback(vmContext, thisArray, thisLength);
        case -401980571/*Kind_TextAreaSubmitCallback*/: return deserializeAndCallSyncTextAreaSubmitCallback(vmContext, thisArray, thisLength);
        case -1878458553/*Kind_TransitionFinishCallback*/: return deserializeAndCallSyncTransitionFinishCallback(vmContext, thisArray, thisLength);
        case 1044833488/*Kind_Type_NavigationAttribute_customNavContentTransition_delegate*/: return deserializeAndCallSyncType_NavigationAttribute_customNavContentTransition_delegate(vmContext, thisArray, thisLength);
        case -1078223620/*Kind_Type_TextPickerAttribute_onChange_callback*/: return deserializeAndCallSyncType_TextPickerAttribute_onChange_callback(vmContext, thisArray, thisLength);
        case 1962174977/*Kind_Type_WebAttribute_onFileSelectorShow_callback*/: return deserializeAndCallSyncType_WebAttribute_onFileSelectorShow_callback(vmContext, thisArray, thisLength);
        case -985284966/*Kind_Type_WebAttribute_onUrlLoadIntercept_callback*/: return deserializeAndCallSyncType_WebAttribute_onUrlLoadIntercept_callback(vmContext, thisArray, thisLength);
        case 541663396/*Kind_VisibleAreaChangeCallback*/: return deserializeAndCallSyncVisibleAreaChangeCallback(vmContext, thisArray, thisLength);
        case -2038961969/*Kind_VoidCallback*/: return deserializeAndCallSyncVoidCallback(vmContext, thisArray, thisLength);
        case -1829763354/*Kind_WebKeyboardCallback*/: return deserializeAndCallSyncWebKeyboardCallback(vmContext, thisArray, thisLength);
        case 219587748/*Kind_WithThemeInterface*/: return deserializeAndCallSyncWithThemeInterface(vmContext, thisArray, thisLength);
    }
    printf("Unknown callback kind\n");
}
KOALA_EXECUTE(deserializeAndCallCallbackSync, setCallbackCallerSync(static_cast<Callback_Caller_Sync_t>(deserializeAndCallCallbackSync)))